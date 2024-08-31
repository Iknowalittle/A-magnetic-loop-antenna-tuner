#include <sys/_stdint.h>
#ifndef _MLAT22_HEADER_
#define _MLAT22_HEADER_
#include "TRXDev.h"

#define MAJOR_VER 1
#define MINOR_VER 0
#define REVISION  0

typedef enum _ANT_SWITCH_TYPE_
{
    ONE_CHANNEL=0,
    TWO_CHANNEL,             //direct control 2 relays
    FOUR_CHANNEL             //use 2-4 encoder to switch 4 channels.
}ANT_SWITCH_TYPE;

typedef struct _hd_config_
{
    ANT_SWITCH_TYPE   AntSWType;            
    bool    support_freq_measurement;     
    bool    support_stall_detection;      
    char    SerialNumber[20];             //for service 
}HARD_CONFIG_DATA;

typedef struct _METER_CAL_
{
    int16_t  ZeroOffset;       //  adc offset
    int16_t  PowerThreshold;   //  low than this is treated as noise. +/- 128 db
}AD8307_OFFSET;

typedef struct _FREQ_COUNTER_CAL_
{
  float K;
  float B;
}FREQ_CAL_OFFSET;

typedef struct _SWR_OFFSET_
{
    AD8307_OFFSET FWDOffset;
    AD8307_OFFSET REFOffset;    
}SWR_METER_OFFSET;
typedef struct _WiFiInfos_
{
    char                    WifiSSID[20];
    char                    WifiPsk[20];            //  
    //last connected date.
}WIFI_INFO,*pWIFI_INFO;

typedef struct _system_cfg_
{
    uint8_t                 last_actived_ant;
    uint8_t                 PowerDispMode;          //0:  linear mode(W), 1: log (dbm)
    SUPPORTED_TRX_TYPE      LastSelectedTRX;        //trx type.
    float                   SWRTuneThreshold;       //acceptable SWR value.   Higher than this value will generate alarm output to rear pannel
    uint32_t                LastFrequencySelected;  //
    char                    PageID[16];             //
    char                    WifiSSID[20];
    char                    WifiPsk[20];            //  
    uint8_t                 TrxAddress;       
}SYSTEM_CFG;


void LoadCommonConfiguration();
bool SaveCommonConfiguration();
bool SaveFreqCalData();

void LoadAntennaDataOnUI(uint8_t which_ant);

void LoadSWROffsetData();
void SaveSWROffsetData();

void LoadSWRData2UI();
void SaveSWRDataFromUI();
void SetSwrDefault();
int MsgBox(const char* Msg);
void DoFreqScanOnScreen();
int ScanBestFrequencyForCurrentPosition(unsigned long StartFrequency,unsigned long StopFrequency,unsigned long StepFreq);
int UartDispatchMsg();
void ResetUartMsg();
void resprintf(char *format,...);
void SetUICommand(char *format,...);
// File System information
void ShowFSInfo();
void ProcessPresetButton(uint8_t index);
void UpdateKeypadInput(uint8_t keyIndex); 
void ShowSWBands(uint16_t iVal);
void ToggleFreqSource(uint8_t Trx=3);
 
void SaveWifi();
const char *versionstring();
void ShowFreqSrcState(bool IsOn);
#ifdef __cplusplus
extern "C" {
#endif

typedef  int (* uart_msg_pipe) (char **args,uint8_t argc);

struct _uartcmd2func 
{
  char *pInputStr;
  uart_msg_pipe pFunc;
};





int ShowVersion(char **args,uint8_t argc);

int DoFreqScan(char **args, uint8_t argc);
int SetFrequencyGenerator(char **args,uint8_t argc);
int ClearAllFreqs(uint8_t antIndex);

#ifdef __cplusplus
}
#endif
#endif
