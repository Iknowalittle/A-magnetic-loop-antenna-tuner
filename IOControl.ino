#include "HardwareStuff.h"
#include "IOControl.h"
#include "RotaryEncoder.h"
PCA9555 ioex;
//PCA9555* PCA9555::instancePointer = 0;
extern  AuxRotEncoder rotaryEncoder;
extern  ExtButton PowerOffKey;
extern bool UseInternalClkSrc;
uint16_t ioex_state;
volatile uint16_t ioex_int_flag;
volatile  uint8_t MotorStallFlag;
volatile uint8_t MotorEnabled;
extern int32_t FreqScaleFactor ;

uint16_t dir_setting=0;
uint8_t  ioex_bit_set[16]={ 1,      /*rotary encoder A*/
                            1,      /*rotary encoder B*/
                            1,      /*rotary encoder SW*/
                            0,      /*TRX_BFO_SW*/
                            0,      /*FC_RELAY0*/
                            0,      /*FC_RELAY1*/
                            0,      /*SYS_PWR_ON*/
                            1,      /*OFF_KEY_DET*/
                            0,      /*ANT_SEL_0*/
                            0,      /*ANT_SEL_1*/
                            1,      /*motor diag*/
                            0,
                            0,
                            0,
                            0,
                            0
                            };
uint8_t ioex_bit_shaddow[16]={0}; 

                          
void IRAM_ATTR IOEX_ISR();

void IntializeIOEX()
{
    Serial.print("initialize IO extender...");
    Wire.begin();
    Wire.setClock(400000);
 
      // Query a status update and wait a bit to let the Si5351 populate the
      // status flags correctly.
     //Wire.begin();



  for (int bit=0;bit<16;bit++)
  {
        if (ioex_bit_set[bit] == PCA95x5::Direction::IN) {
            dir_setting |= (1 << bit);
        } else {
            dir_setting &= ~(1 << bit);
        }
  }
  ioex.attach(Wire);

  ioex.polarity(PCA95x5::Polarity::ORIGINAL_ALL);
  ioex.direction(dir_setting);
  //ioex_state=ioex.read();
  ProcessIOEXEvent(true);
 
  MaintainPowerOn();
  ClearFreqCounter();
  MotorEnControl(false);
  Switch2TRXChan();
  SelectFreqChan(FC_CHAN_X1);      //0: basic ch <15M....   1:    /4  

  ioex_int_flag=0;
  pinMode(IOEX_INT_PIN,INPUT);
  attachInterrupt(digitalPinToInterrupt(IOEX_INT_PIN), IOEX_ISR, FALLING); // Set to low for button presses


 
}

void IRAM_ATTR IOEX_ISR()
{
     ioex_int_flag=1;
           
}
void ProcessIOEXEvent(bool firstread)
{
     ioex_state=ioex.read(); // Points to the actual ISR
     ioex_int_flag=0;

     //Serial.print("IO : ");
     //Serial.print(ioex_state,BIN);
     //Serial.println("");
     uint8_t i;
     uint8_t bit_v;
     uint8_t io_bits[16];
     uint8_t input_mask[16];
     memset(input_mask,0,16);
     for (i=0;i<16;i++)
     {
          if (ioex_bit_set[i]==PCA95x5::Direction::IN)
          {
             io_bits[i]=ioex_state & (1 << i);
             if (!firstread)
             {
                if (ioex_bit_shaddow[i]!=io_bits[i])     input_mask[i]=1;   
             }
              ioex_bit_shaddow[i]=io_bits[i];

          }
     }

   if (!firstread)
   {
      if (input_mask[ROTARY_A_PIN] | input_mask[ROTARY_B_PIN])
      {
        //encoder event.
        rotaryEncoder.UpdateEncoder(ioex_bit_shaddow[ROTARY_A_PIN], ioex_bit_shaddow[ROTARY_B_PIN]);
      }
      if (input_mask[ROTARY_SW_PIN])
      {
        rotaryEncoder.UpdateButton(ioex_bit_shaddow[ROTARY_SW_PIN]);
      }
      if (input_mask[OFF_KEY_DET])
      {
          PowerOffKey.UpdateButton(ioex_bit_shaddow[OFF_KEY_DET]);
      }
      if (input_mask[STEPPER_DIAG])
      {
          //Stepper.UpdateStallFlag.   
          MotorStallFlag=ioex_bit_shaddow[STEPPER_DIAG];       
      }
  //     
   }  


}
void IOEXWrite(uint8_t bit,uint8_t dat)
{
    ioex.write((PCA95x5::Port::Port) bit, dat?OUTPUT_H:OUTPUT_L);
}
uint16_t IOEXRead(uint8_t bit)
{
    if (bit>16) return ioex.read();
    
    return ioex.read((PCA95x5::Port::Port) bit);
}
void Switch2BFOChan()
{
  ioex.write(TRX_BFO_SW,OUTPUT_H);
  UseInternalClkSrc=true;
}
void Switch2TRXChan()
{
  ioex.write(TRX_BFO_SW,OUTPUT_L);
  UseInternalClkSrc=false;
 
}
 void MaintainPowerOn()
 {
    ioex.write(SYS_PWR_ON,OUTPUT_H);
 }
 void SwitchPowerOff()
 {
     ioex.write(SYS_PWR_ON,OUTPUT_L);
 }
void  ClearFreqCounter()
{
  ioex.write(FC_CLR, OUTPUT_H);
  ioex.write(FC_CLR, OUTPUT_L);
}

int SelectFreqChan(FC_CHAN_DEF chan)
{
  ClearFreqCounter();
 // int FreqScaleFactor=1;
  switch (chan)
  {
    case FC_CHAN_X4:
      //FC_RELAY0
      ioex.write(FC_RELAY1, OUTPUT_L);
     // ioex.write(FC_RELAY0, OUTPUT_H);
      FreqScaleFactor=2;
      //Serial.println("select FX4 chan");
      break;
    case FC_CHAN_X16:
      ioex.write(FC_RELAY1, OUTPUT_H);
      //ioex.write(FC_RELAY0, OUTPUT_H); 
      FreqScaleFactor=16;
     // Serial.println("select FX16 chan");
     
      break;
    default:          //X1 chan
      ioex.write(FC_RELAY1, OUTPUT_L);
      FreqScaleFactor=2;
     // Serial.println("select FX1 chan");

      break;  
  }
   return FreqScaleFactor;
}

void MotorEnControl(bool Enable)
{
      ioex.write(STEPPER_EN, Enable?OUTPUT_L:OUTPUT_H);
      MotorEnabled=Enable;
}
uint8_t ReadMotorDiagFlag()
{
  return ioex.read(STEPPER_DIAG);
}
void MotorSpreadControl(bool Mode)
{
    ioex.write(STEPPER_SPREAD, Mode?OUTPUT_H:OUTPUT_L);  
} 

void ConfigStepperAddress(uint8_t addr)
{
    switch (addr)
    {
      case 00:
        ioex.write(STEPPER_MS1,OUTPUT_L);
        ioex.write(STEPPER_MS2,OUTPUT_L);
        break;
      case 01:
        ioex.write(STEPPER_MS1,OUTPUT_L);
        ioex.write(STEPPER_MS2,OUTPUT_H);
         break;
      case 02:
        ioex.write(STEPPER_MS1,OUTPUT_H);
        ioex.write(STEPPER_MS2,OUTPUT_L);
        break;
      case 03:
        ioex.write(STEPPER_MS1,OUTPUT_H);
        ioex.write(STEPPER_MS2,OUTPUT_H);
        break;
    }
}
