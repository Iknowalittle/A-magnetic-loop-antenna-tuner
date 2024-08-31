#include "HardwareStuff.h"
#include <Arduino.h>
#include "MovingAverage.h"
#include "MLAT22.h"
#define SWR_FWD_IN  39//36                // not good to use 2 pins.
#define SWR_REV_IN  36//39

#define DEFAULT_DC_OFFSET_FWD   230.0f      //1043mV...
#define DEFAULT_DC_OFFSET_REV   265.0f      //983
#define DEFAULT_MV_PERDB_FWD    25     
#define DEFAULT_MV_PERDB_REV    25     

#define DEFAULT_OFFSET_FWD    -35     // 
#define DEFAULT_OFFSET_REV    -35     // 
#define ADC_JITCH_SWR         10

#define SWR_READ_SIZE           20
#define SWR_BUFFER_SIZE         20
#define DBM_POWER_DELTA         0.1f
#define SWR_BUFFER_DELTA        0.01f

extern SWR_METER_OFFSET  SWRMeterParas;
//MovingAverageFilter             avgVSWR(SWR_READ_SIZE);
ARMovingAverageFilter           avgVSWRv(SWR_BUFFER_SIZE);
ARMovingAverageFilter           avgFwdPower(SWR_BUFFER_SIZE);
ARMovingAverageFilter           avgRefPower(SWR_BUFFER_SIZE);
void SetupSWRMeter()
{
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  avgVSWRv.SetDelta(SWR_BUFFER_DELTA);
  avgFwdPower.SetDelta(DBM_POWER_DELTA);
  avgRefPower.SetDelta(DBM_POWER_DELTA);
  //read calibration file...
}

float GetFWDValue()
{
      // offset should read from EEPROM.
     float volt=analogReadMilliVolts(SWR_FWD_IN)-DEFAULT_DC_OFFSET_FWD; 
     volt=analogReadMilliVolts(SWR_FWD_IN)-DEFAULT_DC_OFFSET_FWD;
     return DEFAULT_OFFSET_FWD+volt/DEFAULT_MV_PERDB_FWD;
}
float GetREVValue()
{
  float volt= analogReadMilliVolts(SWR_REV_IN)-DEFAULT_DC_OFFSET_REV;
   volt= analogReadMilliVolts(SWR_REV_IN)-DEFAULT_DC_OFFSET_REV;
   return DEFAULT_OFFSET_REV+volt/DEFAULT_MV_PERDB_REV;
}
//  measured_swr = (1+(v_ref/v_fwd))/(1-(v_ref/v_fwd));
//    if (measured_swr < 0) measured_swr = 9999;

 void ResetSWR()
 {
    // avgVSWR.Reset();
    avgVSWRv.BufferReset();
    avgFwdPower.BufferReset();
    avgRefPower.BufferReset();
 }
 //		var lngInput1 = parseFloat(elInput1.value);
//		var lngInput2 = parseFloat(elInput2.value);
//		var lngResult = (1 + (Math.sqrt((Math.pow(10,(lngInput2/10))/1000)/ (Math.pow(10,(lngInput1/10))/1000)))) / (1 - (Math.sqrt((Math.pow(10,(lngInput2/10))/1000)/ (Math.pow(10,(lngInput1/10))/1000))));
//    P(mW) = 1mW ⋅ 10(P(dBm)/ 10)
inline float dbm2mW(float dbmIn)
{
  return pow(10,dbmIn/10);
}

float GetSWRValue(uint8_t AvgCount,float *fwd,float *rev,bool dbmMode)
{
    float swr,rev0,fwd0;
    float fwd_dbm,rev_dbm;
    float vv;
    float fwd_mw,rev_mw;
    uint8_t cc=0;
    while (SWRADCRead(AvgCount, &fwd0, &rev0)==0)
    {
        cc++;
        if (cc>3) break;
    }
       fwd0-=SWRMeterParas.FWDOffset.ZeroOffset;//   DEFAULT_DC_OFFSET_FWD;
       rev0-=SWRMeterParas.REFOffset.ZeroOffset;//   DEFAULT_DC_OFFSET_REV;
       //convert to dbm
       fwd_dbm=SWRMeterParas.FWDOffset.PowerThreshold+fwd0/DEFAULT_MV_PERDB_FWD;
       rev_dbm=SWRMeterParas.REFOffset.PowerThreshold+rev0/DEFAULT_MV_PERDB_REV;

        fwd_mw=dbm2mW(fwd_dbm);
        rev_mw=dbm2mW(rev_dbm);
         
        if (dbmMode){
            *fwd=fwd_dbm;
            *rev=rev_dbm;
        }else
        {
            *fwd=fwd_mw;
            *rev=rev_mw;
        }



        vv=(rev_mw/(fwd_mw));      

        if (vv==1.00000f) vv=1.00001f;
       float assert0=1-sqrtf(vv);
       if (assert0){
          swr=(1+sqrtf(vv))/assert0;
         
       }else
       {
          swr=6.0f;///
       }

      if (swr<0) swr=swr*-10; 
      
      swr=avgVSWRv.PushSample(swr);
   // Serial.printf("FWD: %.2fdbm, REV: %.2fdbm, SWR: %.2f\n",fwd,rev, swr );
   //Serial.println("");
  
  return swr;
}   
float GetSWRValueAvg(uint8_t AvgCount,float *fwd,float *rev,bool dbmMode)
{
    float swr,rev0,fwd0;
    float fwd_dbm,rev_dbm;
    float vv;
    float fwd_mw,rev_mw;
    uint8_t cc=0;
    SWRADCReadAVG(AvgCount, &fwd0, &rev0);
 
       fwd0-=SWRMeterParas.FWDOffset.ZeroOffset;//   DEFAULT_DC_OFFSET_FWD;
       rev0-=SWRMeterParas.REFOffset.ZeroOffset;//   DEFAULT_DC_OFFSET_REV;
       //convert to dbm
       fwd_dbm=SWRMeterParas.FWDOffset.PowerThreshold+fwd0/DEFAULT_MV_PERDB_FWD;
       rev_dbm=SWRMeterParas.REFOffset.PowerThreshold+rev0/DEFAULT_MV_PERDB_REV;

        fwd_mw=dbm2mW(fwd_dbm);
        rev_mw=dbm2mW(rev_dbm);
         
        if (dbmMode){
            *fwd=fwd_dbm;
            *rev=rev_dbm;
        }else
        {
            *fwd=fwd_mw;
            *rev=rev_mw;
        }



        vv=(rev_mw/(fwd_mw));      
        if (vv==1.00000f) vv=1.00001f;


       swr=(1+sqrtf(vv))/(1-sqrtf(vv));

      if (swr<0) swr=swr*-10; 
      
     // swr=avgVSWRv.PushSample(swr);
   // Serial.printf("FWD: %.2fdbm, REV: %.2fdbm, SWR: %.2f\n",fwd,rev, swr );
   //Serial.println("");
  
  return swr;
}  
float GetSWRValue_old(float &fwd,float &rev)
{
 
  fwd=GetFWDValue();
  rev=GetREVValue();
  if (fwd<0.00001) fwd=0.00001;
  if (rev<0.00001) rev=0.00001;   
  float swr=0.00;
  
    if (rev==fwd) rev=rev+0.01;         
    swr=(1+sqrtf(rev/fwd))/(1-sqrtf(rev/fwd));
    if (swr<0) swr=swr*-1;       
   // swr=avgVSWR.process(swr);
   // Serial.printf("FWD: %.2fdbm, REV: %.2fdbm, SWR: %.2f\n",fwd,rev, swr );
   //Serial.println("");
  
  return swr;
}
typedef struct _ValueCategory
{
	float avg;
	uint32_t count;
  float sum;

}VALCATEGORY ;

int CountingArray(float  *array,float *MainV,uint16_t size,float delta,bool showDetail)
{
   VALCATEGORY *pCate=NULL;
   VALCATEGORY  PeakData;
   int counter=0;
   uint8_t found=0;
   float val_delta;	
   int i,c;
 
   PeakData.count=0;
   PeakData.avg=0;
   for (i=0;i<size;i++)
   {
      found=0;
      for (c=0;c<counter;c++)
      {
        val_delta=abs(array[i]-pCate[c].avg);
        if (val_delta<=delta)	
        {
          found=1;
          break;	
        }
      }
      if (found)
      {
        pCate[c].count++;
        pCate[c].sum+=array[i];
        pCate[c].avg=pCate[c].sum/pCate[c].count;

        if (pCate[c].count>PeakData.count)
        {
          PeakData.count=pCate[c].count;
          PeakData.avg=pCate[c].avg;          //avg..
        }
      
      }else
      {
        counter++;
        if (!pCate) 
          pCate=( VALCATEGORY *) malloc(counter*sizeof(VALCATEGORY));
        else
          pCate=( VALCATEGORY *) realloc(pCate,counter*sizeof(VALCATEGORY));
        pCate[counter-1].sum=array[i];
        pCate[counter-1].count=1;
        pCate[counter-1].avg=pCate[counter-1].sum;
      }
   }
   //find the maximum count and return the value..
   	 if (showDetail)
      {
        Serial.printf("after sorting\r\n");
        for (c=0;c<counter;c++)
        {
            Serial.printf("%f\t%d\r\n",pCate[c].avg,pCate[c].count);
        }
      }

   //Serial.printf("the Main data is %f with %d samples\r\n",PeakData.count,PeakData.val);
    
   *MainV=PeakData.avg;
   

   if (pCate) free(pCate);	
   return PeakData.count;
} 
uint16_t SWRADCReadAVG(uint16_t count,float *fwd,float *rev)
{
   uint32_t measure_count=count;

  if (measure_count==0) measure_count=1;

  uint32_t i;
  float acc_fwd=0;
  float acc_rev=0; 
  analogReadMilliVolts(SWR_FWD_IN);
  for (i=0;i<measure_count;i++)
  {
    acc_fwd+=analogReadMilliVolts(SWR_FWD_IN);
  }
  analogReadMilliVolts(SWR_REV_IN);
  for (i=0;i<measure_count;i++)
  {
      acc_rev+=analogReadMilliVolts(SWR_REV_IN);
  } 
 
  *fwd=acc_fwd/measure_count;
  *rev=acc_rev/measure_count;
   return measure_count;
}
uint16_t SWRADCRead(uint16_t count,float *fwd,float *rev)
{
   uint32_t measure_count=0;

   if (count<5) count=5;

  float   *fwd_buf =(float*)malloc(count*sizeof(float));
  float   *rev_buf =(float*)malloc(count*sizeof(float));  

  uint32_t i;
  uint16_t c0,c1;
  uint16_t c_th=count*0.4;
  for (i=0;i<count;i++)
  {
    fwd_buf[i]=analogReadMilliVolts(SWR_FWD_IN);
    rev_buf[i]=analogReadMilliVolts(SWR_REV_IN);
  }
   
  c0=CountingArray(fwd_buf,fwd,count,ADC_JITCH_SWR);
  c1=CountingArray(rev_buf,rev,count,ADC_JITCH_SWR);

  free(fwd_buf);
  free(rev_buf);

  return ((c0>c_th)  & (c1>c_th) )?1:0;
}
void SWREva(uint8_t buffer_size,uint8_t delta)
{
  //do a simple statistics. count for 1 second. check how many times measurement were done.
  uint32_t start_tick=millis();
  float fwd,min_fwd,max_fwd;
  float rev,min_rev,max_rev;
  float swr,min_swr,max_swr;
  uint32_t measure_count=0;
//#define MAX_BUF_SIZE    80 
  float fwd0,rev0;

  uint32_t readsize=20;
  float d_delta=10;

  if (buffer_size>0 ) readsize=buffer_size;
  if (delta>0) d_delta=delta;
  
  float   fwd_buf[256];
  float   rev_buf[256];  
  
  fwd=max_fwd=0.00001f;
  rev=max_rev=0.00001f;
 // swr=max_swr=0.00001f;
  
  Serial.printf("swr function eva: buffer size: %d, delta %f\r\n",readsize,d_delta);
  min_fwd=min_rev=min_swr=1000.f;
  while(millis()-start_tick<1000)
  {
  	//swr=GetSWRValue(fwd,rev);
    fwd=analogReadMilliVolts(SWR_FWD_IN);
    rev=analogReadMilliVolts(SWR_REV_IN);
   // fwd=analogRead(SWR_FWD_IN);
    //rev=analogRead(SWR_FWD_IN);
    fwd_buf[measure_count]=fwd;
    rev_buf[measure_count]=rev;
         
  	if (fwd>max_fwd) max_fwd=fwd;
  	if (fwd<min_fwd) min_fwd=fwd;
  	if (rev>max_rev) max_rev=rev;
  	if (rev<min_rev) min_rev=rev;
  	measure_count++;
    if (measure_count>readsize)
    {
       // output buffer 
        break;
    }
  }
  
 
  Serial.printf("now try to counting data...\r\n");

  CountingArray(fwd_buf,&fwd,readsize,d_delta,true);
  CountingArray(rev_buf,&rev,readsize,d_delta,true);

//float fwd0,rev0;
float fwd_dbm,rev_dbm;
float fwd_mw,rev_mw;
       fwd0=fwd;
       rev0=rev;

       fwd0-=DEFAULT_DC_OFFSET_FWD;
       rev0-= DEFAULT_DC_OFFSET_REV;
       //convert to dbm
       fwd_dbm=DEFAULT_OFFSET_FWD+fwd0/DEFAULT_MV_PERDB_FWD;
       rev_dbm=DEFAULT_OFFSET_REV+rev0/DEFAULT_MV_PERDB_REV;


       //if (rev_dbm==fwd_dbm) rev_dbm=rev_dbm-0.001;     
       //convert to watt...
        fwd_mw=dbm2mW(fwd_dbm);
        rev_mw=dbm2mW(rev_dbm);
       
     

       float vv=(rev_mw/(fwd_mw));      
         


       swr=(1+sqrtf(vv))/(1-sqrtf(vv));
      Serial.printf("Task time: %d\r\n",millis()-start_tick);
      Serial.printf("the filtered FWD: %f, REV: %f\r\n",fwd,rev);
      Serial.printf("Power in dbm: FWD: %f, REV: %f\r\n",fwd_dbm,rev_dbm);
      Serial.printf("Power in mw:  FWD: %f, REV:%f\r\n",fwd_mw,rev_mw);
      Serial.printf("calculated swr: %f\r\n",swr);

}


void SWREvaV1()
{
  //do a simple statistics. count for 1 second. check how many times measurement were done.
  uint32_t start_tick=millis();
  float fwd,min_fwd,max_fwd;
  float rev,min_rev,max_rev;
  float swr,min_swr,max_swr;
  uint32_t measure_count=0;


  fwd=max_fwd=0.00001f;
  rev=max_rev=0.00001f;
  swr=max_swr=0.00001f;
  min_fwd=min_rev=min_swr=1000.f;
  while(millis()-start_tick<1000)
  {
  	swr=GetSWRValue(20,&fwd,&rev);

  	if (swr>max_swr) max_swr=swr;
  	if (swr<min_swr) min_swr=swr;
  	if (fwd>max_fwd) max_fwd=fwd;
  	if (fwd<min_fwd) min_fwd=fwd;
  	if (rev>max_rev) max_rev=rev;
  	if (rev<min_rev) min_rev=rev;
  	measure_count++;
  }
  Serial.printf("Total %d measurements were done \r\n",measure_count);
  Serial.printf("SWR  : %.2f   [%.2f---%.2f]\r\n",swr,min_swr,max_swr);
  Serial.printf("FWD  : %.2f   [%.2f---%.2f]\r\n",fwd,min_fwd,max_fwd);
  Serial.printf("REV  : %.2f   [%.2f---%.2f]\r\n",rev,min_rev,max_rev);
  
}

