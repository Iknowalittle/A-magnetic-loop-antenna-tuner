#include "HardwareStuff.h"
#include "MovingAverage.h" 
#include "si5351.h"
Si5351 FreqGen;


#define PCNT_FREQ_UNIT      PCNT_UNIT_0                      // select ESP32 pulse counter unit 0 (out of 0 to 7 indipendent counting units)
                                                               // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/pcnt.html

 #define  FREQ_INPUT_PIN   35                                   

  int16_t PulseCounter =     0;                                     // pulse counter, max. value is 65536
  int32_t OverflowCounter =      0;                                // pulse counter overflow counter
  float   PCNT_H_LIM_VAL =       32000;                            // upper limit of counting  max. 32767, write +1 to overflow counter, when reached 
  uint16_t PCNT_FILTER_VAL=  1;                                // filter (damping, inertia) value for avoiding glitches in the count, max. 1023
  pcnt_isr_handle_t user_isr_handle = NULL;                    // interrupt handler - not used
  hw_timer_t * timer = NULL;                                   // Instancia do timer

 float time_gate= 1;    //1 seconds.

 
//volatile      SemaphoreHandle_t timerSemaphore;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

si5351_clock  SI_CLK_SRC; 

ARMovingAverageFilter   avgFreqMeter(100);
 
bool UseInternalClkSrc=false;
volatile uint32_t  ActiveFrequency=0;
volatile  uint8_t  data_updated=0;
int32_t FreqScaleFactor =1 ;

void ARDUINO_ISR_ATTR onTimer(){
  // Increment the counter and set the time of ISR
  portENTER_CRITICAL_ISR(&timerMux);
  ActiveFrequency=Read_Reset_PCNT();
  data_updated=1;
  portEXIT_CRITICAL_ISR(&timerMux);
  // Give a semaphore that we can check in the loop
 // xSemaphoreGiveFromISR(timerSemaphore, NULL);
  // It is safe to use digitalRead/Write here if you want to toggle an output
}

void IRAM_ATTR CounterOverflow(void *arg) {                  // Interrupt for overflow of pulse counter
    OverflowCounter = OverflowCounter + 1;                     // increase overflow counter
    PCNT.int_clr.val = BIT(PCNT_FREQ_UNIT);                    // clean overflow flag
    pcnt_counter_clear(PCNT_FREQ_UNIT);                        // zero and reset of pulse counter unit
  }
  
  void initPulseCounter (){                                    // initialise pulse counter
    pcnt_config_t pcntFreqConfig = { };                        // Instance of pulse counter
    pcntFreqConfig.pulse_gpio_num = FREQ_INPUT_PIN;        // pin assignment for pulse counter = GPIO 15
    pcntFreqConfig.pos_mode = PCNT_COUNT_INC;                  // count rising edges (=change from low to high logical level) as pulses
    pcntFreqConfig.counter_h_lim = PCNT_H_LIM_VAL;             // set upper limit of counting 
    pcntFreqConfig.unit = PCNT_FREQ_UNIT;                      // select ESP32 pulse counter unit 0
    pcntFreqConfig.channel = PCNT_CHANNEL_0;                   // select channel 0 of pulse counter unit 0
    pcnt_unit_config(&pcntFreqConfig);                         // configur rigisters of the pulse counter
  
    pcnt_counter_pause(PCNT_FREQ_UNIT);                        // pause puls counter unit
    pcnt_counter_clear(PCNT_FREQ_UNIT);                        // zero and reset of pulse counter unit
  
    pcnt_event_enable(PCNT_FREQ_UNIT, PCNT_EVT_H_LIM);         // enable event for interrupt on reaching upper limit of counting
    pcnt_isr_register(CounterOverflow, NULL, 0, &user_isr_handle);  // configure register overflow interrupt handler
    pcnt_intr_enable(PCNT_FREQ_UNIT);                          // enable overflow interrupt

    pcnt_set_filter_value(PCNT_FREQ_UNIT, PCNT_FILTER_VAL);    // set damping, inertia 
    pcnt_filter_enable(PCNT_FREQ_UNIT);                        // enable counter glitch filter (damping)
  
    pcnt_counter_resume(PCNT_FREQ_UNIT);                       // resume counting on pulse counter unit
  }
  
  int32_t Read_Reset_PCNT() {   
    PulseCounter=0;
    pcnt_counter_pause(PCNT_FREQ_UNIT);                        // pause puls counter unit
    pcnt_get_counter_value(PCNT_FREQ_UNIT, &PulseCounter);     // get pulse counter value - maximum value is 16 bits
    int32_t act_count=OverflowCounter*PCNT_H_LIM_VAL+PulseCounter;

    OverflowCounter = 0;                                       // set overflow counter to zero
    pcnt_counter_clear(PCNT_FREQ_UNIT);                        // zero and reset of pulse counter unit
    pcnt_counter_resume(PCNT_FREQ_UNIT);
   

    return act_count/time_gate;
  }


float  GetAndCheckFreq()
{
  if (!data_updated) return avgFreqMeter.GetAvg();

  float vv=ActiveFrequency;
  
  float freq= vv*FreqScaleFactor/1e6 ; 
  freq=avgFreqMeter.PushSample(freq);
  //  portENTER_CRITICAL_ISR(&timerMux);

  data_updated=0;
   // portEXIT_CRITICAL_ISR(&timerMux);

  return freq;
}

void SetupFreqTimer()
{
  initPulseCounter();
 
  FreqScaleFactor=SelectFreqChan(FC_CHAN_X16);
  OverflowCounter=0;
  
  avgFreqMeter.SetDelta(0.001);

  //timerSemaphore = xSemaphoreCreateBinary();
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, time_gate*1000000, true);      //Fixed 1 seconds.
  timerAlarmEnable(timer);
  timerStart(timer);

}

bool SetupFrequencyGenerator()
{
     Serial.printf("Initialize Frequency Generator....\n ");
     bool i2c_found;
     //if there is cal factor, the read it first.
     i2c_found = FreqGen.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
      if(!i2c_found)
      {
        Serial.println("FreqGen not found on I2C bus!");
       } else
       {
          SelectFrequencyChan(0);
          SetFG_Level(SI5351_DRIVE_8MA);      //set to max power.
       }
      
      // Set CLK0 to output 14 MHz
     // FreqGen.set_freq(700000000ULL, SI5351_CLK0);
     // FreqGen.drive_strength(SI5351_CLK0,SI5351_DRIVE_8MA);    //max power output ...
      // Set CLK1 to output 175 MHz
      //si5351.set_ms_source(SI5351_CLK1, SI5351_PLLB);
     // si5351.set_freq_manual(4500000000ULL, 70000000000ULL, SI5351_CLK1);
     
     return i2c_found;
}
void SelectFrequencyChan(uint8_t src)
{
  //SI5351_CLK0, SI5351_CLK1, SI5351_CLK2
    if (src>SI5351_CLK2) src=SI5351_CLK2;      
    SI_CLK_SRC=(si5351_clock)src;
    Serial.printf("select clk source: %d\r\n",SI_CLK_SRC);
}
int SetFG_Frequency(uint64_t Freq)
{
   return FreqGen.set_freq(Freq, SI_CLK_SRC);
}
int SetFG_Level(uint8_t Level)
{
  switch (Level)
  {
    case SI5351_DRIVE_2MA:
    case SI5351_DRIVE_4MA:
    case SI5351_DRIVE_6MA:
    case SI5351_DRIVE_8MA:
      FreqGen.drive_strength(SI_CLK_SRC,(si5351_drive)Level);    //max power output ...
      break;
    default:   
      FreqGen.drive_strength(SI_CLK_SRC,SI5351_DRIVE_2MA);    //max power output ...
      break;  
  }
  return 0;
}
void TurnFGOn()
{
   FreqGen.output_enable(SI_CLK_SRC, 1);
   if (UseInternalClkSrc)
   {
      UpdateFreqSource(SI_CLK_SRC+1) ;    
      ShowFreqSrcState(true);
   }
}
void TurnFGOff()
{
    FreqGen.output_enable(SI_CLK_SRC, 0);
    ShowFreqSrcState(false);
}
