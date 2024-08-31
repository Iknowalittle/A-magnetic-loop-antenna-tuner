
#include "AntennaParaMgr.h"
#include "HardwareStuff.h"
#include "FS.h"
#include "SPIFFS.h"

 
bool AntennaParaManager::Initialize(uint8_t index)
{
   //
    PosChanged=false;
    AntennaIndex=index;
    memset(&mlat_info,0,sizeof(AntConfigInfo));

    memset(&PresetList[0],0,sizeof(PositionInfomation)*MAX_TUNED_FREQ_PAIRS);
    
    sprintf(header_file_path,"/mlat%02d_define.dat",AntennaIndex);
    sprintf(config_file_path,"/mlat%02d_freq_pairs.dat",AntennaIndex);
    sprintf(position_file,"/mlat%02d_pos.dat",AntennaIndex);
    
    bool initialized=false;
    initialized=LoadHeaders();
    if (initialized)
    {
        LoadParaPairs();  
        ReadTrackPosition();
        ShowAntInfo();
    }else
    {
       //set default.
      mlat_info.MotorInfo.MaxCurrent=DEFAULT_MOTOR_CURRENT;
      mlat_info.MotorInfo.StallTH=DEFAULT_MOTOR_STALL_TH;
      mlat_info.MotorInfo.min_delay_us=DEFAULT_MOTOT_INT_TIME;
      mlat_info.MotorInfo.HomeDetectionMicroStep=DEFAULT_MOTOR_MICROSTEP;
      mlat_info.MotorInfo.FineTuneMicroSteps=DEFAULT_MOTOR_FINESTEP;
      mlat_info.TunedFrequencyCount=0;
      mlat_info.DistanceInSteps=0;

      Serial.printf("No valid configuration file was found, use default\r\n");
    }
    
    return initialized;

}
void AntennaParaManager::ShowAntInfo()
{
   if (mlat_info.valid==1)
   {
      char *CAP_type[]={"Vacuum","Air Cap"};
      
      Serial.printf("ANT %d information\n",AntennaIndex);
      if (mlat_info.CAPType<=1)
        Serial.printf("Capacitor:   %s\n",(char*)CAP_type[mlat_info.CAPType]);
      else
        Serial.printf("Capacitor:  ? %d\n", mlat_info.CAPType);
      
      Serial.printf("Motor steps :%d/%d\r\n",LastTrackedPosition,mlat_info.DistanceInSteps);




      //  Serial.printf("MAX  Freq:   %ul",mlat_info.MaxTuneFreq);
       // Serial.printf("MIN  Freq:   %ul",mlat_info.MinTuneFreq);

     if (1)//(mlat_info.TunedFrequencyCount<=MAX_TUNED_FREQ_PAIRS)
     {
        Serial.println("Tuned Frequency pairs list");
        Serial.println("----------------------------------------\n");
        Serial.printf(" Frequency        Position       SWR(ref)\n");
        Serial.println("-----------------------------------------\n");

        uint8_t i;
        uint8_t c=0;
        for (i=0;i<MAX_TUNED_FREQ_PAIRS;i++)
        {
          if (PresetList[i].PresetFrequency && PresetList[i].StepperPosition)
          {
             Serial.printf("%d      %d        %d\n",PresetList[i].PresetFrequency,PresetList[i].StepperPosition,PresetList[i].swr_reference);
             c++;
          }
        }
        mlat_info.TunedFrequencyCount=c;
     }
   }else
   {
      Serial.printf("ANT %d was not configured\n",AntennaIndex);
   }
   
}
bool  AntennaParaManager::SaveMotorParameters(MotorInformationDef *pMotorInfo)
{
  mlat_info.MotorInfo.FineTuneMicroSteps=pMotorInfo->FineTuneMicroSteps;
  mlat_info.MotorInfo.HomeDetectionMicroStep=pMotorInfo->FineTuneMicroSteps;
  mlat_info.MotorInfo.MaxCurrent=pMotorInfo->MaxCurrent;
  mlat_info.MotorInfo.min_delay_us=pMotorInfo->min_delay_us;
  mlat_info.MotorInfo.StallTH=pMotorInfo->StallTH;
  return SaveHeaders(); 
 }
bool  AntennaParaManager::GetMotorParameters(MotorInformationDef *pMotorInfo)
{
   pMotorInfo->FineTuneMicroSteps=mlat_info.MotorInfo.FineTuneMicroSteps;
   pMotorInfo->HomeDetectionMicroStep=mlat_info.MotorInfo.HomeDetectionMicroStep;
   pMotorInfo->MaxCurrent=mlat_info.MotorInfo.MaxCurrent;
   pMotorInfo->min_delay_us=mlat_info.MotorInfo.min_delay_us;
   pMotorInfo->StallTH=mlat_info.MotorInfo.StallTH;
   return true;
}
uint8_t AntennaParaManager::ClearAllPosition()
{
  SPIFFS.remove(config_file_path);
  memset(&PresetList[0],0,sizeof(PositionInfomation)*MAX_TUNED_FREQ_PAIRS);
  return 0;
}
bool AntennaParaManager::LoadHeaders()
{
      //mlat_info
    bool header_ok=false;
    File file = SPIFFS.open(header_file_path, FILE_READ);
    if(!file){
        Serial.printf("- failed to open file %s for reading\n",header_file_path);
        return header_ok;
    }    
    if(file && !file.isDirectory()){
        int flen = file.size();
        int header_len=sizeof(AntConfigInfo);
        if (flen>=header_len)
        {
          file.read((uint8_t*)&mlat_info, header_len);
           
          header_ok=true;
        }else
        {
           Serial.printf("file size is not right %d,%d:\n",flen,header_len);
        }
        file.close();
     }
   
    return header_ok;
}
bool  AntennaParaManager::SaveTotalSteps(uint32_t TotalMotorSteps)
{
  mlat_info.DistanceInSteps=TotalMotorSteps;
   //judge capacitor type automatically.
  if (TotalMotorSteps>200)   //more than 1 turn
  {
      mlat_info.CAPType=VACUUM_CAP;
  }else
  {
      mlat_info.CAPType=AIR_CAP;
  }
  mlat_info.valid=1;  
  return SaveHeaders(); 
}

bool AntennaParaManager::SaveHeaders()
{
    size_t len = 0;
    File file = SPIFFS.open(header_file_path, FILE_WRITE);
    if(!file){
        Serial.printf("- failed to open file %s for writing\n",header_file_path);
        return false;
    }
    size_t i;
    Serial.print("- writing -" ); 
    file.write((uint8_t*)&mlat_info, sizeof(AntConfigInfo));  
    file.close();
    Serial.println("- done -");

    return false; 
}
bool AntennaParaManager::LoadParaPairs()
{
    bool config_ok=false;
    File file = SPIFFS.open(config_file_path, FILE_READ);
    if(!file){
        Serial.printf("- failed to open file %s for reading\n",config_file_path);
        return config_ok;
    }    
    if(file && !file.isDirectory()){
        int flen = file.size();
        int readlen=MAX_TUNED_FREQ_PAIRS*sizeof(PositionInfomation);
        // assert flen=MAX_TUNED_FREQ_PAIRS*sizeof(PositionInfomation);
        if (flen>=readlen)
        {
            file.read((uint8_t*)&PresetList[0], readlen);
            config_ok=true;
        }else
        {
            Serial.printf("file size is not right %d,%d:\n",flen,readlen);
        }
         file.close();
     }     
     return config_ok;
}

bool AntennaParaManager::SaveParaPairs()
{
    bool config_ok=false;
    File file = SPIFFS.open(config_file_path, FILE_WRITE);
    if(!file){
        Serial.printf("- failed to open file %s for writing\n",config_file_path);
        return config_ok;
    }    
    if(file && !file.isDirectory()){
         int writelen=MAX_TUNED_FREQ_PAIRS*sizeof(PositionInfomation);
        // assert flen=MAX_TUNED_FREQ_PAIRS*sizeof(PositionInfomation);
         file.write((uint8_t*)&PresetList[0], writelen);
         config_ok=true;
         file.close();
     }     
     return config_ok;
}
bool AntennaParaManager::SaveTrackPosition()
{
    bool file_ok=false;
    File file = SPIFFS.open(position_file, FILE_WRITE);
    if(!file){
        Serial.printf("- failed to open file %s for wrting\n",position_file);
        return file_ok;
    }    
    if(file && !file.isDirectory()){
        file.write((uint8_t*)&LastTrackedPosition, sizeof(long));
        file.close();
        PosChanged=false;
    }else
    {
      Serial.printf("failed to write position tracking file\r\n");
    }
    return file_ok; 
}
bool AntennaParaManager::ReadTrackPosition()
{
     //  position_file 
    bool file_ok=false;
    LastTrackedPosition=0;
    File file = SPIFFS.open(position_file, FILE_READ);
    if(!file){
        Serial.printf("- failed to open file %s for reading\n",position_file);
        return file_ok;
    }    
    if(file && !file.isDirectory()){
        int flen = file.size();
        if (flen)
        {
          file.read((uint8_t*)&LastTrackedPosition, sizeof(long));
        }
        file.close();
        PosChanged=false;
    }
    return file_ok;
}
void AntennaParaManager::SaveMotorPostion(uint32_t CurrentMotorPosition)
{
   LastTrackedPosition=CurrentMotorPosition;       //s
   //save 
   //PosChanged=true;
   Serial.printf("save tracking position: %d\r\n",LastTrackedPosition);
   SaveTrackPosition();
}
uint8_t AntennaParaManager::SetAsActiveAntenna(bool mode)
{
  // switch  the antenna...
  if (!mode)
  {
    // if delata changed, save it.
    if (PosChanged) SaveTrackPosition();
  }else
  {
    
  }
  return 0;
  
}
uint8_t AntennaParaManager::GetTunedPositionCount()
{
      return mlat_info.TunedFrequencyCount;
}
uint16_t  AntennaParaManager::GetPostionInformation(PositionInfomation *p_pos,uint8_t index)
{
  uint16_t result=0;
  uint8_t i=0;
  uint8_t c=0;
   for (i=0;i<MAX_TUNED_FREQ_PAIRS;i++){
      if (PresetList[i].PresetFrequency  && PresetList[i].StepperPosition )
      {
         if (c==index)
         {
            //p_pos->PresetFrequency=PresetList[i].PresetFrequency;
            //p_pos->StepperPosition=PresetList[i].StepperPosition;
            //p_pos->swr_reference=PresetList[i].swr_reference;
            memcpy(p_pos,&PresetList[i],sizeof(PositionInfomation));
            result=1;
            break;
         }   
         c++;
      } 
   }

  
  return result;
}
int16_t  AntennaParaManager::GetSavePositionFromFrequency(uint32_t freq)
{
  int16_t  pos=-1;
  uint16_t i=0;
  for (i=0;i<MAX_TUNED_FREQ_PAIRS;i++)
  {
      if (PresetList[i].PresetFrequency==freq)
      {
         pos=i;
         break;
      }
   }    
  return pos;
}

//this will overwrite the position if the frequency is same.. 
uint8_t AntennaParaManager::AddPosition(PositionInfomation Pos)
{
  
  //get next empty position...
  //frequency is the index, make sure frequency is not duplicated.
  int16_t pos=GetSavePositionFromFrequency(Pos.PresetFrequency);
  if (pos==-1) pos=GetSavePositionFromFrequency(0);
  if (pos>=0)
  {
     memcpy(&PresetList[pos],&Pos,sizeof(PositionInfomation));
     SaveParaPairs();
  }

  return 0;
}
uint8_t AntennaParaManager::RemovePosition(uint32_t PresetFrequency)
{
  int16_t pos=GetSavePositionFromFrequency(PresetFrequency);
  if (pos>=0)
  {
     PresetList[pos].PresetFrequency=0;
     PresetList[pos].StepperPosition=0;
     PresetList[pos].swr_reference=0;
     SaveParaPairs();
  }
  return 0;
}
uint32_t   AntennaParaManager::FindFreqFromList(uint32_t freq)
{
  uint32_t act_pos=0;
  int16_t pos=GetSavePositionFromFrequency(freq);
  if (pos>=0)
  {
      act_pos=PresetList[pos].StepperPosition;
  }
  return act_pos;
}      
bool AntennaParaManager::SetCapacitorType(CapacitorTypeDef CapType)
{
      mlat_info.CAPType=CapType;      
      SaveHeaders();
      return true;
}
/* 
bool AntennaParaManager::SetMaxTuneFreq(unsigned long freq)
{
      //mlat_info.MaxTuneFreq=freq;
      SaveHeaders();
      return true;
}
bool AntennaParaManager::SetMinTuneFreq(unsigned long freq)
{
     // mlat_info.MinTuneFreq=freq;
      SaveHeaders();
      return true;
}

bool AntennaParaManager::CalculatePostion4Freq(unsigned long TargetFreq,long &Steps2Move)
{
    //go through the frequency list,find the most near point, do a linear calculation to get a approximated steps.
    //then move to this position +/- TH choose the minimum SWR point.
     return true;
}
bool AntennaParaManager::MoveToHomePosition(uint8_t direction,uint32_t * TotalSteps)
{
    uint32_t StepsInCount=0;
    uint32_t ms0 = millis();
    uint32_t ms1;
    uint32_t StallCheck=0;
    uint32_t chk_interval=0;
    uint32_t chk_threshold=0;
    uint32_t first_stall_pos=0;

    SetMotorDir(direction);        //update UI ...

    uint32_t StallFlag;//=ioex.read(STALL_DET);
    while(StallCheck<15)
    {
       // PulseMotorSteps();
        StepsInCount++;
         
        ms1=millis();
        if (ms1-ms0>20000)
        {
          Serial.printf("timeout....\n");
          break;
        }
        //chk_interval++;
        //if (chk_interval>chk_threshold) {      
            StallFlag=ReadMotorDiagFlag();
            if (StallFlag) {
              StallCheck++;
              chk_threshold=0;
              if (StallCheck==1) first_stall_pos=StepsInCount;
            }else
            {
              if (StallCheck){ 
                Serial.printf("drop stall: %d-%d\n",StallCheck,StepsInCount);
                StallCheck=0;
                }
              chk_threshold=1;
            }
       
    }
    *TotalSteps=StepsInCount;
    Serial.printf("total time: %d,  steps: %d,StallFlag:%d, first: %d\n",ms1-ms0,StepsInCount,StallCheck,first_stall_pos);
    //Serial.print(driver2.SG_RESULT(), DEC);
    Serial.printf("\r\n");
    return StallFlag?true:false;

}
*/
