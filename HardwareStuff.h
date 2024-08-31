#include <sys/_stdint.h>
#ifndef MLAT22_HW_STUFF_HEADER
#define MLAT22_HW_STUFF_HEADER

 

#include <Ticker.h>            
#include "AntennaParaMgr.h"
                 
#include  "soc/pcnt_struct.h"
#include "driver/pcnt.h"  // ESP32 library for pulse count




#define UART1_TX    33
#define UART1_RX    32

#define DEFAULT_MOTOR_CURRENT   1500
#define DEFAULT_MOTOR_STALL_TH  150
#define DEFAULT_MOTOR_MICROSTEP 2
#define DEFAULT_MOTOR_FINESTEP  8
#define DEFAULT_MOTOT_INT_TIME  800

typedef enum MOT_STEP_MODE_DEF
{
   MOT_0_0_OFF=0,
   MOT_1_1_STEP ,        //Full
   MOT_1_2_STEP ,          //Half
   MOT_1_4_STEP ,          //Quater
   MOT_1_8_STEP ,          //Eighth
   MOT_1_16_STEP ,          //Sixteenth
   MOT_1_32_STEP ,          //Sixteenth
   MOT_1_64_STEP ,          //Sixteenth
   MOT_1_128_STEP ,          //Sixteenth
   MOT_1_256_STEP           //Sixteenth
}MOT_MAN_MODE;

MOT_MAN_MODE Current_MOT_MODE;

typedef enum 
{
    MT_COUNTER_MODE=0,
    MT_SWR_MODE=1  
}MOTOR_TASK;
//tune mode 
/*
  1) in steps
  2) seeking minimum swr for current frequency.

*/
typedef struct _MotorRunningMsg_
{
    //just do step pin puls
    MOTOR_TASK TaskMode;     
    union Parameters 
    {
      struct 
      {
        int32_t Steps2Run;
        int32_t StepsPulsed;
        int32_t DelayTimes;		//min delay time in microseconds.
      }CounterModes;
      struct  
      {
        uint16_t SwrInterval;  
        uint16_t min_swr_tuned;        //X10
        float   SWRTarget;  
        int32_t PresetPositon;
      }SWRModes;
    }TaskParameters;
    int32_t DelayTimes;		//min delay time in microseconds.
    bool Running;     
    bool EnableTask;
    bool ExitService;
    bool TuneOK;
}MotorRunningMsg;

void rotary_onButtonClick();
void SetupRotaryEncoder();
void EncoderTask();
void RotaryModeProcess();

//Stepper Motor related 
void StartMotorService(void);
void MotorTaskRunner(void *parameter);

void SetupStepperMotor();

void ConfigStepperMicroStep(uint8_t steps);

void MotorEnControl(bool Enable);
void UpdateMotorStepperSetting();
bool MoveToLimitPosition(int8_t direction,uint32_t * TotalSteps,int32_t MinRunningSteps=-1);

bool FindHomePosition(uint32_t *TotalSteps0,uint32_t *TotalSteps1);

bool FindMovingRanges();

void MoveMotorInSteps0(int32_t steps,uint32_t delayInMicroSeconds);
uint32_t MoveMotorInSteps(int32_t steps,uint32_t delayInMicroSeconds);
//bool FindBestSWR(float BFOFrequency);
bool FindBestSWR(float BFOFrequency,uint32_t presetpos,uint16_t &swr_v);
bool SeekPosForFreq(uint32_t freq);

bool Move2RightPositionByFreq(uint32_t freq);

//float SWRMeasureAndDelay(uint32_t MaxDelayTimesInUs);
void SetMotorTask(int32_t steps,uint32_t delayInMicroSeconds);
void SetMotorSWRModeTask(uint32_t presetPos,uint32_t delayInMicorSeconds);

void MotorSWRModeProcess(MotorRunningMsg *ThreadMsg);
void MotorCounterModeProcess(MotorRunningMsg *ThreadMsg);
void MotorTaskProcess(MotorRunningMsg *ThreadMsg);
uint32_t MoveMotors(int32_t StepsInCount,int8_t SeekingDir, uint16_t SWR_interval, float * p_min_swr_value);
//bool MotorConnected();
void SetMotorDir(uint8_t dir);

void SetTOff(uint8_t t_Off);
void SetMotorRefSource(bool UseExternal);

uint8_t ReadMotorDiagFlag();
void ConfigStepperAddress(uint8_t addr);
void MotorSpreadControl(bool Mode);
uint32_t MotorMicroSteps();
void PulseMotorSteps();
void SetStallTH(uint8_t v);
void SetMotorCurrent(uint16_t rms_max);
void AbortMotorTask();
void ShowMotorDriverStatus();
void SetMotorSpeed(uint32_t speed);
void UpdateMotorProgress(uint8_t val);
void UpdateMotorPosition(bool save=false);


//Frequency Generator
void SelectFrequencyChan(uint8_t src);
bool SetupFrequencyGenerator();
int SetFG_Frequency(uint64_t Freq);
int SetFG_Level(uint8_t Level);  
void TurnFGOn();
void TurnFGOff();

//Frequency Counter
typedef enum FC_CHANNEL_DEF
{
  FC_CHAN_X1=0,
  FC_CHAN_X4,
  FC_CHAN_X16
}FC_CHAN_DEF;
void      SetupFreqTimer();
int32_t   Read_Reset_PCNT();
int      SelectFreqChan(FC_CHAN_DEF chan);      //0: basic ch <15M....   1:    /4  
float     GetAndCheckFreq();
void      UpdateFrequencyCounter();
void      ClearFreqCounter();


void Switch2TRXChan();
void Switch2BFOChan();

//SWR meter
float dbm2mW(float dbmIn);

void SetupSWRMeter();
float GetFWDValue();
float GetREVValue();
float GetSWRValue(uint8_t AvgCount,float *fwd,float *rev,bool dbmMode=true);
float GetSWRValueAvg(uint8_t AvgCount,float *fwd,float *rev,bool dbmMode=true);

void UpdateSWRMeter();
void ResetSWR();
void SWREva(uint8_t buffer_size,uint8_t delta);

uint16_t SWRADCRead(uint16_t count,float *fwd,float *rev);
uint16_t SWRADCReadAVG(uint16_t count,float *fwd,float *rev);

int CountingArray(float  *array,float *MainV,uint16_t size,float delta,bool showDetail=false);
void RefreshSWRMeter(float swr,float fwd, float rev);
bool CheckSWRTune(float SWRThreshold,float &swr_actual);

//plotter related
void swrfindChartInit();
//void swrfindAddPoint(uint32_t step,float swr);
                      
//Serial command process
void SerialTask();
//OTA related;
//==========================
// read default SSID and PSK
//==========================
// so user can do OTA update
// 
int LoadOTASetting(String& ssid,String& psk);
int SaveOTASetting(String ssid,String psk);


 //===system power control=========
 void IntializeIOEX();
 void ProcessIOEXEvent(bool firstread=false);
 void MaintainPowerOn();
 void SwitchPowerOff();
 void IOEXWrite(uint8_t bit,uint8_t dat);
uint16_t IOEXRead(uint8_t Bit);
void ProcessIOTask();

void ProcessWiFiTask();
void WebPolling();
void WifiInit();
void RefreshWifiList();
bool WiFiTryConnect(char *ssid,char *password);
bool IsWiFiConnected();
String GetIpAddress();

void DoWebUpdate();
void setupTelnet();
void ProcessTelnetCommand(String strcmd);

void PageShow(uint16_t pageid);   // stack it.
void PageHide(uint16_t pageid);

void ShowBusyBox();
void RefreshBusyBox();
void HideBusyBox();

void Add2UIFreqList(uint32_t freq);
void Add2UIWifiList(const char *ssid,int32_t rssi);
void Add2UIRadioList(const char *RadioType);

void SelectFreqItem(int16_t nID);
void SelectTRXItem(int16_t nID);
void SelectWifiItem(int16_t nID);

void InitializeRadioList();
void ResetRadioListBox();  //void gslc_ElemXListboxReset(gslc_tsGui* pGui, gslc_tsElemRef* pElemRef);
void ResetWifiListBox();
void ResetFreqListBox();

void ShowTipMsg(const char *msg);
void UpdateIpAddr(const char *ipaddr,bool Valid=false);
void ShowPageID(const char *id);
void ShowWifiSSID(const char *ssid);
void SetChartTitle(const char *title);

void ShowPresetFreqList();

void UpdateFreqSource(uint8_t src);
void RemovePresetFreq();
void Config2SwrMode();
void DoOTAUpgrade();
#endif
