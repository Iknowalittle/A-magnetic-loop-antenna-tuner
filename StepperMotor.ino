#include "HardwareStuff.h"
#include <TMCStepper.h>
#include "ChartPlotter.h"
//extern PCA9555 ioex;
//#include <ESP_FlexyStepper.h>
 
 
 
#define MOT_DIR_PIN        4          // Direction
#define MOT_STEP_PIN       2          // Step

#define MOT_DRIVER_ADDRESS   0b00       // TMC2209 Driver address according to MS1 and MS2

#define MOT_R_SENSE          0.10f      // E_SENSE for current calc.  
#define STALL_VALUE          150         // [0..255]


TMC2209Stepper MotorDriver(&Serial2, MOT_R_SENSE , MOT_DRIVER_ADDRESS);
//ESP_FlexyStepper   Stepper;

MotorRunningMsg     	MotorMsg;       // for service mode task.
extern volatile uint8_t MotorStallFlag; 

extern uint16_t OldStallDetected;
extern uint16_t StallCount;

extern uint32_t  MaxMotorMoveSteps;
extern int32_t   CurrentMotorPosition;          //always save the position relative 0...
 
extern MotorInformationDef  MotorRunningConfig; //
extern LineChart mChart;

TaskHandle_t 		MotorTaskHandle = NULL;
void SetupStepperMotor()
{
  // setup IO extender PCA9555.
     MaxMotorMoveSteps=0;
     CurrentMotorPosition=0;      

      MotorEnControl(true);
     // Serial.println("-done");
      Serial.print("initialize stepper motor");
 

     // Stepper.connectToPins(MOT_STEP_PIN, MOT_DIR_PIN);
     // Stepper.setStepsPerRevolution(200);
      pinMode(MOT_STEP_PIN,OUTPUT);
      pinMode(MOT_DIR_PIN,OUTPUT); 

      ConfigStepperAddress(MOT_DRIVER_ADDRESS);

      Serial2.begin(500000);
      MotorDriver.begin();

      Serial.printf("connection test: %d\n",MotorDriver.test_connection());
      MotorSpreadControl(false);             
      MotorDriver.I_scale_analog(true);  // must be true ?
      MotorDriver.toff(4);              /*TOFF off time and driver enable*/
                                        /*Off time setting controls duration of slow decay phase
                                          N CLK = 24 + 32*TOFF
                                          %0000: Driver disable, all bridges off
                                          %0001: 1 – use only with TBL ≥ 2
                                          %0010 … %1111: 2 … 15
                                          (Default: OTP, resp. 3 in StealthChop mode)*/

      MotorDriver.dedge(true);            //double edge 

      MotorDriver.blank_time(24);       /*blank time select*/
                                        /*%00 … %11: Set comparator blank time to 16, 24, 32 or 40 clocks
                                         Hint: %00 or %01 is recommended for most applications
                                         (Default: OTP)*/
      SetMotorCurrent(1500);         //TBD configuration file
      MotorDriver.microsteps(2);
      //MotorDriver.TCOOLTHRS(0xFFFFF); // 20bit max
      MotorDriver.TCOOLTHRS(0xFFFFF); // 20bit max  ..doesnt matter.s
      MotorDriver.semin(0);             /*minimum StallGuard value for smart current control and smart current enable*/
                                        /*If the StallGuard4 result falls below SEMIN*32, 
                                        the motor current becomes increased to reduce motor load angle.
                                        %0000:          smart current control CoolStep off 
                                        %0001 … %1111:  1 … 15*/
      MotorDriver.semax(2);             /*StallGuard hysteresis value for smart current control*/
                                        /*If the StallGuard4 result is equal to or above (SEMIN+SEMAX+1)*32, 
                                        the motor current becomes decreased to save energy.
                                         %0000 … %1111: 0 … 15*/
      
      MotorDriver.sedn(0b01);           /*current down step speed*/

      SetStallTH(STALL_VALUE);
      //MotorDriver.SGTHRS(STALL_VALUE);       //read from configuration file..

     // Serial.print("diag result: ");
      //Serial.print(MotorDriver.SG_RESULT(), DEC);
     // Serial.print("  GCONF: ");
       //Serial.print(MotorDriver.GCONF(),BIN);

      Serial.println("start motor service...");
      StartMotorService();
      Serial.println("-done");
    //Test code
  /*
   Stepper.setSpeedInStepsPerSecond(1600);
   Stepper.setAccelerationInStepsPerSecondPerSecond(1600);
   Stepper.moveRelativeInSteps(1600);
   */
}
void SetTOff(uint8_t t_Off)
{
  MotorDriver.toff(t_Off);  
}

void SetMotorSpeed(uint32_t speed)
{
    MotorDriver.VACTUAL(speed);
}
void ShowMotorDriverStatus()
{
       Serial.printf("Driver status: %d\r\n",MotorDriver.DRV_STATUS());
       Serial.printf("driver spread_en : %d ",MotorDriver.spread_en());
       Serial.printf("driver stealth: %d\n",MotorDriver.stealth());
       Serial.printf("Open ola: %d, olb: %d\n",MotorDriver.ola(),MotorDriver.olb());
       Serial.printf("Short s2ga:%d,s2vsa: %d, s2gb: %d,s2vsb :%d\r\n",MotorDriver.s2ga(),MotorDriver.s2vsa(),MotorDriver.s2gb(),MotorDriver.s2vsb());
       Serial.printf("cs actual: %d\r\n",MotorDriver.cs_actual());
}
void SetStallTH(uint8_t v)
{
    Serial.printf("set motor stall th :%d\r\n",v);
    MotorDriver.SGTHRS(v);       //read from configuration file..
}
void SetMotorCurrent(uint16_t rms_max)
{
    Serial.printf("set motor rms current to %d\r\n",rms_max);
    MotorDriver.rms_current(rms_max);         //TBD configuration file
}

void  StartMotorService(void)
{

  MotorMsg.ExitService=false;
  MotorMsg.EnableTask =false;
  	
  disableCore1WDT(); 		// we have to disable the Watchdog timer to prevent it from rebooting the ESP all the time another option would be to add a vTaskDelay but it would slow down the stepper
  xTaskCreatePinnedToCore(
      MotorTaskRunner, 		/* Task function. */
      "MotorTaskRunner",             /* String with name of task (by default max 16 characters long) */
      2000,                          /* Stack size in bytes. */
      &MotorMsg,                    /* Parameter passed as input of the task */
      1,                            /* Priority of the task, 1 seems to work just fine for us */
      &MotorTaskHandle,            /* Task handle. */
      1 /* the cpu core to use */
  );
}
void MotorTaskRunner(void *parameter)
{
  MotorRunningMsg *ThreadMsg = static_cast<MotorRunningMsg*>(parameter);
  for (;;)
  {
     //
     vTaskDelay(1); // This would be a working solution to prevent the WDT to fire (if not disabled, yet it will cause noticeably less smooth stepper movements / lower frequencies)
    if (ThreadMsg->EnableTask)      MotorTaskProcess(ThreadMsg);       
    if (ThreadMsg->ExitService)     break;
    	
  }
  Serial.printf("Exit Motor service task...\r\n");
}

#define  SWR_SWING_RANGE         700
#define  SWR_QUICK_MODE_SIZE     3
#define  SWR_FINE_MODE_SIZE      20
#define  ACCEL_RATE              40
uint32_t MoveMotors(int32_t StepsInCount,int8_t SeekingDir, uint16_t SWR_interval,float * p_min_swr_value)
{
  int32_t c=StepsInCount;
  uint16_t CheckInterval;
  uint32_t swr_min_pos=0;  
  uint32_t ts0=millis();

  float swr,fwd,rev,swr_min;
  bool update1=true;
  /*
  if (p_min_swr_value)
    swr_min=*p_min_swr_value+2;
  else 
  */
  swr_min=1000;
  digitalWrite(MOT_DIR_PIN,(SeekingDir==1)?1:0);        //update UI ...
  while (c>0)
   {
                    digitalWrite(MOT_STEP_PIN, !digitalRead(MOT_STEP_PIN));
                    delayMicroseconds(MotorMsg.DelayTimes);        
                    CurrentMotorPosition+=SeekingDir;
                    c--;
                    if (SWR_interval)
                    {
                      ResetSWR();
                      CheckInterval++;
                      if (CheckInterval>SWR_interval)
                      {
                            swr=GetSWRValue(SWR_QUICK_MODE_SIZE,&fwd,&rev);
                            if (swr<swr_min)
                            {
                                  swr_min=swr;
                                  swr_min_pos=CurrentMotorPosition;
                            }
                            mChart.UpdateTrace((double)CurrentMotorPosition,swr,  update1,  GREEN);
                            CheckInterval=0;
                      }
                      
                    }
                   if (!MotorMsg.EnableTask) break;
  }
 
        

   //    if (SWR_interval)
   //       Serial.printf("min SWR=%.2f,time cost: %d\r\n",swr_min,millis()-ts0);  
   //    else
   Serial.printf("time cost: %d\r\n",millis()-ts0);  

  if (p_min_swr_value!=NULL) *p_min_swr_value=swr_min;
  UpdateMotorPosition();
  return swr_min_pos;
}

void MotorSWRModeProcess(MotorRunningMsg *ThreadMsg)
{
    ThreadMsg->TuneOK=false;
    int32_t steps=0;
    float swr;
    float swr_min=1000;
    int32_t swr_min_pos=0;
    int32_t c;
    //uint8_t checkInterval=0;
    int8_t SeekingDir=0;
    int8_t preset_mode_dir=0;
    float fwd,rev;
    float swr_target;
    uint16_t swing_range=0;
    int swrx10;

    int32_t old_pos=CurrentMotorPosition;
    int32_t preset_pos=0;

   // float swr;
   // uint32_t StepsInCount=0;
   // bool update1=true;
   // checkInterval=0;


    MotorEnControl(true);
    Serial.printf("Current Motor position: %d, Max Position : %d\r\n",CurrentMotorPosition,MaxMotorMoveSteps);

    if (ThreadMsg->TaskParameters.SWRModes.PresetPositon>0)
    {
       swr_min_pos=ThreadMsg->TaskParameters.SWRModes.PresetPositon;
       swr_target=ThreadMsg->TaskParameters.SWRModes.SWRTarget;
       swing_range=SWR_SWING_RANGE ;
      // Serial.printf("1) Preset position is exists, %d steps to move\r\n",CurrentMotorPosition-swr_min_pos);   
       preset_pos=ThreadMsg->TaskParameters.SWRModes.PresetPositon;
    }else
    {
        if (CurrentMotorPosition>MaxMotorMoveSteps/2)
        {
             c=MaxMotorMoveSteps-CurrentMotorPosition;  //move to limit position
             digitalWrite(MOT_DIR_PIN,1);        //update UI ...
             SeekingDir=-1;
        }else
        {
            c=CurrentMotorPosition;             //roll back to 0 position.
            digitalWrite(MOT_DIR_PIN,0);        //update UI ...
            SeekingDir=1;
       }
      // Serial.printf("1) move to a known home position first in steps %d,Max: %d,  dir=%d\r\n",c,MaxMotorMoveSteps,SeekingDir);
       //if (c){
          UpdateMotorPosition();
          while (c>0)
            {
                           digitalWrite(MOT_STEP_PIN, !digitalRead(MOT_STEP_PIN));
                           delayMicroseconds(ThreadMsg->DelayTimes);        
                           CurrentMotorPosition-=SeekingDir;
                           c--;
                           if (!ThreadMsg->EnableTask) break;
            } 
           UpdateMotorPosition();
      // }
        c=MaxMotorMoveSteps;
      //  Serial.printf("2) Ready to go through the whole position range steps: %d, pos: %d, dir=%d\r\n",c,CurrentMotorPosition,SeekingDir);
        //digitalWrite(MOT_DIR_PIN,(SeekingDir==1)?1:0);        //update UI ...
        swr_min_pos=MoveMotors(c, SeekingDir, SWR_FINE_MODE_SIZE, &swr);            //TBF: modify it to adapt Air Capacitor
        //Serial.printf("---OK\r\n");
        swr_target=swr;
        
        preset_pos=swr_min_pos;
        swing_range=SWR_SWING_RANGE;
       // Serial.printf("---OK...target: %d, current: %d\r\n",swr_min_pos,CurrentMotorPosition);

    }


    swrx10=swr_target*10;
    int dist0,dist1;
    bool changedir=false;
    dist0=(swr_min_pos-SWR_SWING_RANGE/2)-CurrentMotorPosition;
    dist1=(swr_min_pos+SWR_SWING_RANGE/2)-CurrentMotorPosition ;

    if (abs(dist0)<=abs(dist1))
    {
         c=dist0 ;
         changedir=true;
    }else
    {
         c=dist1;
    }
   // c=swr_min_pos-CurrentMotorPosition;
/*
    Serial.printf("3) The minimum SWR[%d] position is located at: %d steps,Motor Pos: %d, try move: %d steps\r\n",
                                                   swrx10,
                                                   swr_min_pos,
                                                   CurrentMotorPosition,
                                                   c
                                                   );
                                                   */
    SeekingDir=(c>0)?1:-1;              //when c==0 the dir is -1 ...

   // digitalWrite(MOT_DIR_PIN,(SeekingDir==1)?1:0);        //update UI ...
    c=abs(c);
    MoveMotors(c, SeekingDir, 0,NULL);
 
    c=swing_range;
    
    if (CurrentMotorPosition<swr_min_pos)
    {
         SeekingDir=1;
    }else
    {
        SeekingDir=-1;      
    }
    //digitalWrite(MOT_DIR_PIN,(SeekingDir==1)?1:0);        //update UI ...

   // Serial.printf("4) now try to do fine tune....from %d to %d\r\n",CurrentMotorPosition,CurrentMotorPosition+c*SeekingDir);
    
    //TBD: set dir...
    double x0,x1,xinc;
    x0=swr_min_pos;
    x1=CurrentMotorPosition;
    xinc=(x1-x0)/10;
    if (xinc>0)    
    {
      mChart.Clear();
      mChart.GraphFrame(x0,x1,xinc,1,20,1,"SWR Tune","Step","VSWR"); 
    }


    swr=swr_target;  
    swr_min_pos=MoveMotors(c, SeekingDir, SWR_QUICK_MODE_SIZE, &swr);
    swrx10=swr*10;
    if (swr>swr_target)       Serial.printf("the fine tune result it not correct.. %d---%d\r\n",CurrentMotorPosition,swrx10);
  



    c=swr_min_pos-CurrentMotorPosition;


    //Serial.printf("5) back to the minimum SWR[%d] position from %d  to %d\r\n",swrx10,CurrentMotorPosition,CurrentMotorPosition+c);
    SeekingDir=(c>0)?1:-1;
   // digitalWrite(MOT_DIR_PIN,(SeekingDir==1)?1:0);        //update UI ...
    //c=abs(c);
    MoveMotors(abs(c), SeekingDir, 0,NULL);              
    
    ThreadMsg->TaskParameters.SWRModes.min_swr_tuned=swr;

    mChart.MarkPeakMin();

    MotorEnControl(false);
    Serial.printf(" swr task completed, orignal position:%d, target:%d, %d\r\n",old_pos,preset_pos,CurrentMotorPosition);
    ThreadMsg->EnableTask=false;    
    ThreadMsg->TuneOK=true;
   // UpdateMotorProgress(100);

}
void MotorSWRModeProcess_V00(MotorRunningMsg *ThreadMsg)
{
    ThreadMsg->TuneOK=false;
    int32_t steps=0;
    float swr;
    float swr_min=1000;
    int32_t swr_min_pos=0;
    int32_t c;
    //uint8_t checkInterval=0;
    int8_t SeekingDir=0;
    int8_t preset_mode_dir=0;
    float fwd,rev;
    float swr_target;
    uint16_t swing_range=0;
            int swrx10;

   // float swr;
   // uint32_t StepsInCount=0;
   // bool update1=true;
   // checkInterval=0;


    MotorEnControl(true);
    Serial.printf("Current Motor position: %d, Max Position : %d\r\n",CurrentMotorPosition,MaxMotorMoveSteps);

    if (ThreadMsg->TaskParameters.SWRModes.PresetPositon>0)
    {
       swr_min_pos=ThreadMsg->TaskParameters.SWRModes.PresetPositon;
       swr_target=ThreadMsg->TaskParameters.SWRModes.SWRTarget;
       swing_range=SWR_SWING_RANGE;
       Serial.printf("1) Preset position is exists, %d steps to move\r\n",swr_min_pos);   
       
    }else
    {
        if (CurrentMotorPosition>MaxMotorMoveSteps/2)
        {
             c=MaxMotorMoveSteps-CurrentMotorPosition;  //move to limit position
             digitalWrite(MOT_DIR_PIN,1);        //update UI ...
             SeekingDir=-1;
        }else
        {
            c=CurrentMotorPosition;             //roll back to 0 position.
            digitalWrite(MOT_DIR_PIN,0);        //update UI ...
            SeekingDir=1;
       }
       Serial.printf("1) move to a known home position first in steps %d,Max: %d,  dir=%d\r\n",c,MaxMotorMoveSteps,SeekingDir);
       //if (c){
          UpdateMotorPosition();
          while (c>0)
            {
                           digitalWrite(MOT_STEP_PIN, !digitalRead(MOT_STEP_PIN));
                           delayMicroseconds(ThreadMsg->DelayTimes);        
                           CurrentMotorPosition-=SeekingDir;
                           c--;
                           if (!ThreadMsg->EnableTask) break;
            } 
           UpdateMotorPosition();
      // }
        c=MaxMotorMoveSteps;
        Serial.printf("2) Ready to go through the whole position range steps: %d, pos: %d, dir=%d\r\n",c,CurrentMotorPosition,SeekingDir);
        digitalWrite(MOT_DIR_PIN,(SeekingDir==1)?1:0);        //update UI ...
        swr_min_pos=MoveMotors(c, SeekingDir, 20, &swr);            //TBF: modify it to adapt Air Capacitor
        //Serial.printf("---OK\r\n");
        swr_target=swr;
        

        swing_range=SWR_SWING_RANGE;
        Serial.printf("---OK...target: %d, current: %d\r\n",swr_min_pos,CurrentMotorPosition);

    }


    swrx10=swr_target*10;
    
    c=swr_min_pos-CurrentMotorPosition;

    Serial.printf("3) The minimum SWR[%d] position is located at: %d steps,Motor Pos: %d, try move: %d\r\n",swrx10,
                                                   swr_min_pos,
                                                   CurrentMotorPosition,
                                                   c
                                                   );
    SeekingDir=(c>0)?1:-1;              //when c==0 the dir is -1 ...
    digitalWrite(MOT_DIR_PIN,(SeekingDir==1)?1:0);        //update UI ...
    c=abs(c);

    if (c>swing_range/2)   
    {
        c=c-swing_range/2;
        Serial.printf("modify moving steps to %d,%d \r\n",c,CurrentMotorPosition);
        MoveMotors(c, SeekingDir, 0,NULL);
    }else{
        Serial.printf(" Fast steps mode...from %d ", CurrentMotorPosition);
        if (c==0)
        {
            MoveMotors(swing_range/2,  1, 0, NULL);
        }else
            MoveMotors(swing_range/2-c,  SeekingDir*(-1), 0, NULL);
        Serial.printf(" to %d \r\n", CurrentMotorPosition);

     }  
     
 
    // for getting more precision result, we need measure swr in each step...
  
    
    c=swing_range;
    Serial.printf("4) now try to do fine tune....from %d to %d\r\n",CurrentMotorPosition,CurrentMotorPosition+c*SeekingDir);
    
    double x0,x1,xinc;
    x0=swr_min_pos;
    x1=CurrentMotorPosition;
    xinc=(x1-x0)/10;
    if (xinc>0)    
    {
      mChart.Clear();
      mChart.GraphFrame(x0,x1,xinc,1,20,1,"SWR Tune","Step","VSWR"); 
    }

    swr=swr_target;  
    swr_min_pos=MoveMotors(c, SeekingDir, 10, &swr);
    swrx10=swr*10;
    if (swr>swr_target)
    {
       Serial.printf("the fine tune result it not correct.. %d---%d\r\n",CurrentMotorPosition,swrx10);
    }



    c=swr_min_pos-CurrentMotorPosition;


    Serial.printf("5) back to the minimum SWR[%d] position from %d  to %d\r\n",swrx10,CurrentMotorPosition,CurrentMotorPosition+c);
    SeekingDir=(c>0)?1:-1;
    digitalWrite(MOT_DIR_PIN,(SeekingDir==1)?1:0);        //update UI ...
    //c=abs(c);
    MoveMotors(abs(c), SeekingDir, 0,NULL);              
    
    ThreadMsg->TaskParameters.SWRModes.min_swr_tuned=swr;

    mChart.MarkPeakMin();

    MotorEnControl(false);
    Serial.printf("6) swr task completed, %d\r\n",CurrentMotorPosition);
    ThreadMsg->EnableTask=false;    
    ThreadMsg->TuneOK=true;
   // UpdateMotorProgress(100);

}
void MotorCounterModeProcess(MotorRunningMsg *ThreadMsg)
{
       ThreadMsg->TuneOK=false;
       int32_t steps=0;
       int8_t seekingdir=0;
       steps=ThreadMsg->TaskParameters.CounterModes.Steps2Run;

       MotorEnControl(true);

       if (steps>0){
            digitalWrite(MOT_DIR_PIN,1);        //update UI ...
            seekingdir=1;
       }
        else{
            digitalWrite(MOT_DIR_PIN,0);        //update UI ...
            seekingdir=-1;          
        }

      uint32_t c=abs(steps);
      uint32_t c1=c;
      ThreadMsg->TaskParameters.CounterModes.StepsPulsed=0;
      
      //if (ThreadMsg->SWRTarget<0.5) ThreadMsg->SWRTarget=1.5;  //
     // UpdateMotorProgress(1);
      while (c>0)
        {
              digitalWrite(MOT_STEP_PIN, !digitalRead(MOT_STEP_PIN));
              //SwrInterval
              delayMicroseconds(ThreadMsg->DelayTimes);        
              c--;
              ThreadMsg->TaskParameters.CounterModes.StepsPulsed++; 
             // UpdateMotorProgress((ThreadMsg->TaskParameters.CounterModes.StepsPulsed*100)/c1);
             if (!ThreadMsg->EnableTask) break;
        }
       // UpdateMotorProgress(100);
        Serial.printf("counter mode task completed \r\n");
        ThreadMsg->EnableTask=false;		//we have done.
        MotorEnControl(false);  
}
void MotorTaskProcess(MotorRunningMsg *ThreadMsg)
{
   switch(ThreadMsg->TaskMode)
   {
     case MT_COUNTER_MODE:
      MotorCounterModeProcess(ThreadMsg);
      break;
     case MT_SWR_MODE:
      MotorSWRModeProcess(ThreadMsg);
      break;  
   };
}
/*
bool CheckSWRTune(float SWRThreshold )
{
   float swr,fwd,rev;
   swr=GetSWRValue(&fwd,&rev);
   RefreshSWRMeter( swr, fwd,  rev);
     
   return (swr<SWRThreshold)?true:false;
}
*/
void AbortMotorTask()
{
   MotorMsg.EnableTask =false;	
}
uint32_t MotorMicroSteps()
{
  return MotorDriver.microsteps();
}
void PulseMotorSteps()
{
   digitalWrite(MOT_STEP_PIN, !digitalRead(MOT_STEP_PIN));
}
void SetMotorDir(uint8_t dir)
{
    digitalWrite(MOT_DIR_PIN,dir);        //update UI ...
}
// Tune Parameters:
//  dir. steps. command_flag.
//
void SetMotorTask(int32_t steps,uint32_t delayInMicroSeconds)
{
   OldStallDetected=0;
   StallCount=0;
   Serial.printf("task : %d steps in %d us interval\r\n",steps,delayInMicroSeconds);
   MotorMsg.TaskParameters.CounterModes.Steps2Run=steps;
   MotorMsg.DelayTimes=delayInMicroSeconds;
   MotorMsg.TaskMode=MT_COUNTER_MODE;
   MotorMsg.EnableTask=true;
   return;
}
void SetMotorSWRModeTask(uint32_t presetPos,uint32_t delayInMicorSeconds)
{
   MotorMsg.DelayTimes=delayInMicorSeconds;
   MotorMsg.TaskParameters.SWRModes.PresetPositon=presetPos;
   MotorMsg.TaskMode=MT_SWR_MODE;
   MotorMsg.EnableTask=true;
}
/*
   MotorMsg.DelayTimes=800;
   MotorMsg.TaskParameters.SWRModes.PresetPositon=0;
   MotorMsg.TaskMode=MT_SWR_MODE;
   MotorMsg.EnableTask=true;
*/
/*
void MoveMotorInSteps0(int32_t steps,uint32_t delayInMicroSeconds)
{

   MotorEnControl(true);

   //Serial.printf("will move %d steps\n",steps);

   if (steps>0)
      digitalWrite(MOT_DIR_PIN,1);        //update UI ...
  else
      digitalWrite(MOT_DIR_PIN,0);        //update UI ...

   uint32_t c=abs(steps);
   
   
   while (c>0)
   {
     PulseMotorSteps();
   //  vv=!vv;
      c--;
   
      //delayMicroseconds(50);
     // delay(1);
      //Serial.printf("Stall: %d, Curr A: %d\r\n",MotorDriver.SG_RESULT(),MotorDriver.cur_a()); 
    
      if (c % 5 ==0)
        Serial.printf("Stall: %d, A: %d,  B: %d   \r\n",MotorDriver.SG_RESULT(), MotorDriver.cur_a(),MotorDriver.cur_b());   
          
    delayMicroseconds(delayInMicroSeconds);
    }
   MotorEnControl(false);
}
*/
uint32_t MoveMotorInSteps(int32_t steps,uint32_t delayInMicroSeconds)
{
      
   if (MotorMsg.EnableTask)
   {
     Serial.printf("Last Motor task is not completed yet\r\n");
     return 0;
   }   
   SetMotorTask(steps,  delayInMicroSeconds);
   /*
   unsigned int c=0;
   while (MotorMsg.EnableTask)
   {
       
       Serial.printf("Guard:%d,A:%d\r\n",MotorDriver.SG_RESULT(),MotorDriver.cur_a()); 
       //when stall detected, just set EnableTaskFlag to false.
      // delay(1);
      c++;
     }
    // Serial.printf("toal %d read during %d steps\r\n",c,steps);
    */
    return MotorMsg.TaskParameters.CounterModes.StepsPulsed;
	
}
#define MAX_MOTOR_STEPS   20000
#define STALL_DETECTION_TH  30
#define DELAY_IN_FINDING_HOME 800   //800 looks good,600 is fast but the torch is too low
#define NORMAL_MOVING_TH    4
#define STALL_VALID_RATE    50.0f
#define STALL_DETECT_BATCH 2  
#define DETECTION_BATCH 100 
bool MoveToLimitPosition(int8_t direction,uint32_t * TotalSteps,int32_t MinRunningSteps)
{
    uint32_t StepsTH;
    uint32_t ms0 = millis();
    
    int32_t steps=direction*MAX_MOTOR_STEPS;        //
    uint32_t c=0;
    int16_t stall_result,Zero_stall_result;
    int32_t stall_count=0;
    uint32_t first_stall_pos=0;
    uint8_t DiagResult=0;
    uint32_t rough_steps=0;
    if (MinRunningSteps==-1) 
      StepsTH=200;
    else
      StepsTH=MinRunningSteps;
    
    Serial.printf("set move min threshold to %d\r\n",StepsTH);

    SetMotorTask(steps,  DELAY_IN_FINDING_HOME);
   
   Zero_stall_result=0;
   stall_count=0;
   bool update1=true;
   uint16_t counter_20,stall1;
   uint16_t stall_check_count=0;
   float rate0=0.0f;
   

   //each 30 steps ///
   
   counter_20=0; stall1=0; 

   while (MotorMsg.EnableTask)
   {
      //stall_result=MotorDriver.SG_RESULT();
       delayMicroseconds(DELAY_IN_FINDING_HOME);
       stall_check_count++;
       if (stall_check_count>=STALL_DETECT_BATCH)
       {
          DiagResult=ReadMotorDiagFlag();       
          rough_steps+=STALL_DETECT_BATCH;
          counter_20++;
          stall_check_count=0;
          mChart.UpdateTrace(rough_steps,DiagResult,  update1,  RED);

       
          if (DiagResult==0)
          {
            Zero_stall_result++;
            if (Zero_stall_result>NORMAL_MOVING_TH)           stall_count=0;
              
          }else{
              
              Zero_stall_result=0;
              stall_count++;
              stall1++;           
              
              if (stall1==1) first_stall_pos=MotorMsg.TaskParameters.CounterModes.StepsPulsed;
              /*
              if ((stall_count>=STALL_DETECTION_TH) && (rate0>STALL_VALID_RATE))
              {
                if (MotorMsg.TaskParameters.CounterModes.StepsPulsed>StepsTH)
                {
                    MotorMsg.EnableTask=false;
                    break;
                }               
              }
              */
          }
          if (counter_20>=DETECTION_BATCH)
          {
              if (stall1)
              {
                rate0=stall1*100/counter_20;
                Serial.printf("stall : %.2f %\r\n",rate0); 
                if (rate0>STALL_VALID_RATE)
                {
                  if (MotorMsg.TaskParameters.CounterModes.StepsPulsed>StepsTH)
                  {
                      MotorMsg.EnableTask=false;
                      break;
                  }               
                }

              }
              counter_20=0;
              stall1=0;
          }
       }
       //old_stall_result=stall_result;
      c++;
      ProcessIOTask();
      //RefreshBusyBox();      
     // Serial.printf("stall : %d,  %d\r\n",stall_count,DiagResult);    
    }

    *TotalSteps= MotorMsg.TaskParameters.CounterModes.StepsPulsed-DETECTION_BATCH*( rate0 /100);   //fist stall position...
    Serial.printf("total cost %d S to move %d steps ,stall count: %d,  total steps: %d,stall1: %d\r\n",(millis()-ms0)/1000,first_stall_pos,stall_count,MotorMsg.TaskParameters.CounterModes.StepsPulsed,stall1);
    MotorEnControl(false);
    delay(20);
    MotorEnControl(true);
    
    return false;
}
bool FindHomePosition(uint32_t *TotalSteps0,uint32_t *TotalSteps1)
{


   MoveToLimitPosition(1,TotalSteps0);
   delay(20);
   MoveToLimitPosition(-1,TotalSteps1,*TotalSteps0);

   MotorEnControl(false);
   //Serial.printf("Total motor steps: %d\r\n",totalsteps);
   //*TotalSteps1 should great than *TotalSteps0
   uint32_t ss=max(*TotalSteps0,*TotalSteps1);
   if (*TotalSteps1>*TotalSteps0) 
      return (ss>200)?true:false;
   else
      return false;


}


/*
  try to move motor and try to find best SWR, then stay 
*/
bool FindBestSWR(float BFOFrequency,uint32_t presetpos,uint16_t &swr_v)
{

    if (MaxMotorMoveSteps<200)
    {
       Serial.printf("the moving range is not set correctly %d\r\n", MaxMotorMoveSteps);
       return false;
    }
     uint32_t ms0 = millis();
        // now setup thread message
        double x0,x1,xinc;
        double y0,y1,yinc;
        bool disp=true;
        bool update1=true;
        bool bfo_used=false;
        x0=0;
        x1=(double)MaxMotorMoveSteps;
        xinc=x1/5;
        y0=1;
        y1=15.0;
        yinc=1.0;

        swrfindChartInit();
        mChart.Clear();
        mChart.GraphFrame(x0,x1,xinc,y0,y1,yinc,"SWR Tune","Step","VSWR"); 

    if (BFOFrequency>100)
    {
      uint64_t freq=BFOFrequency;
      Serial.printf("target frequency : %f Hz\r\n",BFOFrequency);
      freq=freq*100;
      SelectFrequencyChan(0);
      TurnFGOn();
      Switch2BFOChan();
      SetFG_Frequency(freq);
      SetFG_Level(3);
      bfo_used=true;
   }
   
   SetMotorSWRModeTask(presetpos,800);
   MotorMsg.TaskParameters.SWRModes.SWRTarget=swr_v; 
   while (MotorMsg.EnableTask)
   {
      delayMicroseconds(DELAY_IN_FINDING_HOME);
      ProcessIOTask();
   }
   swr_v=MotorMsg.TaskParameters.SWRModes.min_swr_tuned*10;
   Serial.printf("total cost %d S to seeking swr \r\n",(millis()-ms0)/1000 );
   Serial.printf("Final position: %d with swr=%d\r\n",CurrentMotorPosition,swr_v);
   UpdateMotorPosition(true);

 //  MotorEnControl(false);
 //  delay(20);
  // MotorEnControl(true);
   if (bfo_used)
   {
         TurnFGOff();
         Switch2TRXChan();
   }
   return true;
}
void ConfigStepperMicroStep(uint8_t steps)
{
    MotorDriver.microsteps(steps);
}
void SetMotorRefSource(bool UseExternal)
{
    MotorDriver.I_scale_analog(UseExternal);  // must be true ?
}
