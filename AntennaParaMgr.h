#include <sys/_stdint.h>
#ifndef _ANTENNA_PARA_MGR_HEADER_
#define _ANTENNA_PARA_MGR_HEADER_
/*
typedef struct  {
          int32_t  PresetFrequency;                  // Frequency information in Hz        
          int32_t  StepperPosition;                  // Position Information, 
} PositionInfomation;                                // 64 bits, 8 bytes
*/
typedef struct  {
          uint32_t  PresetFrequency;                  // Frequency information in Hz        
          uint16_t  StepperPosition;                  // Position Information, 
          uint16_t  swr_reference;                    // the swr value ever tuned
} PositionInfomation; 
//
typedef enum _CapacitorType
{
    VACUUM_CAP=0,
   // AIR_CAP_WITH_SW,
   // AIR_CAP_NO_SW
   AIR_CAP
}CapacitorTypeDef;

typedef struct _MotorInfo_
{
    uint16_t min_delay_us;                 //running  step frequency...
    uint8_t  StallTH;           
    uint8_t  HomeDetectionMicroStep;       //microstep setting that home detection 
    uint8_t  FineTuneMicroSteps;           //
    uint16_t MaxCurrent;                   //Max RMS current.
}MotorInformationDef;

typedef struct _ant_info_
{
    uint8_t       AntennaIndex;   
    uint8_t       valid;
    CapacitorTypeDef CAPType;     

    MotorInformationDef MotorInfo;

    uint32_t      DistanceInSteps;
    
    //uint8_t       PollingFinished;      //set to 1 when we have already scan over the antenna.

    uint8_t       TunedFrequencyCount;  //    

    //int8_t        FreqUpDir;
    //int8_t        FreqDownDir;          //
    
    //unsigned long MaxTuneFreq;          
    //unsigned long MinTuneFreq;   
}AntConfigInfo;

#define MAX_TUNED_FREQ_PAIRS    20

class AntennaParaManager
{
  public:
     AntennaParaManager(){};
    ~AntennaParaManager(){};
    
  public:
    bool    Initialize(uint8_t index);                   //get default position... 

    void     SaveMotorPostion(uint32_t CurrentPosition);     //  
    uint32_t GetMotorPosition()
    {
        return LastTrackedPosition;
    }

    uint8_t SetAsActiveAntenna(bool mode);               //if true...switch the stepper and RF channel.
    bool    SetCapacitorType(CapacitorTypeDef CapType);
   
    bool    SaveTotalSteps(uint32_t DistanceInSteps);

    uint32_t GetTotalSteps()
    {
        return mlat_info.DistanceInSteps;
    }
    bool    SaveMotorParameters(MotorInformationDef *pMotorInfo);
    bool    GetMotorParameters(MotorInformationDef *pMotorInfo);
    
    uint8_t GetTunedPositionCount();

    uint8_t    AddPosition(PositionInfomation Pos);
    uint8_t    RemovePosition(uint32_t PresetFrequency);
    uint8_t    ClearAllPosition();
    //bool       CalculatePostion4Freq(unsigned long TargetFreq,long &Steps2Move);
    //bool       MoveToHomePosition(uint8_t direction,uint32_t * TotalSteps);
    uint32_t   FindFreqFromList(uint32_t freq);
    uint16_t   GetPostionInformation(PositionInfomation *p_pos,uint8_t index);
    int16_t    GetSavePositionFromFrequency(uint32_t freq);

 private:
      //Stepper Motor Position    ---Current Position.
    bool LoadHeaders();
    bool SaveHeaders();
    bool LoadParaPairs();
    bool SaveParaPairs();
    void ShowAntInfo();
    bool SaveTrackPosition();
    bool ReadTrackPosition();
     AntConfigInfo mlat_info;
    char header_file_path[50];
    char config_file_path[50];
    char  position_file[50];
    int   AntennaIndex;
    long  LastTrackedPosition;
    bool  PosChanged;
    PositionInfomation PresetList[MAX_TUNED_FREQ_PAIRS]; //
};

#endif
