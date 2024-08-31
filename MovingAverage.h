/*
https://github.com/sebnil/Moving-Avarage-Filter--Arduino-Library-
*/
#ifndef MovingAverageFilter_h
#define MovingAverageFilter_h

#define MAX_DATA_POINTS 200

class MovingAverageFilter
{
public:
  //construct without coefs
  MovingAverageFilter(unsigned int newDataPointsCount);       

  float process(float in);
  void Reset()
  {
      k=0;
  }
private:
  float values[MAX_DATA_POINTS];
  int k; // k stores the index of the current array read to create a circular memory through the array
  int dataPointsCount;
  float out;
  int i; // just a loop counter
};
//automatic reset moving average buffer..
class ARMovingAverageFilter
{
public:
  ARMovingAverageFilter(unsigned int avg_count)
  {
      AvgBuffer=(float*)malloc(avg_count*sizeof(float));
      mAverageCount=avg_count;
      BufferReset();
  }
  void BufferReset()
  {
    mValidCount=0;
    LastSample=0.000f;
    memset(AvgBuffer,0,mAverageCount*sizeof(float));
  }
  //<template_t>PushSample(<template_t t);
  float PushSample(float sample)
  {
    float result;
    int32_t i=0;
    float accumlated=0;

    if (fabs(LastSample)<1)
    {
           // _printf("set last sample \r\n");
          LastSample=sample;
    }

   // float Delta0=fabs(sample.Image-pWhich->LastSample.Image);

    float Delta1=fabs(sample-LastSample);

 
    if (Delta1> Delta )
    {
          mValidCount=0;
    }

    if ( mValidCount)
    {
        mValidCount++;
        if ( mValidCount> mAverageCount)  mValidCount= mAverageCount;


        for ( i= mValidCount-1;i>0;i--){
             AvgBuffer[i]= AvgBuffer[i-1];
        }
        AvgBuffer[0]=sample;

        for ( i=0;i< mValidCount;i++){
            accumlated+= AvgBuffer[i];
        }

        accumlated/= mValidCount;
        result=accumlated;
    }else
    {
        AvgBuffer[0]=sample;
        mValidCount++;
        result=sample;
    }
    AvgResult=result;

    LastSample=sample;

    return result;
  }
  float GetAvg()
  {
    return AvgResult;
  }
  void  SetDelta(float delta)
  {
    Delta=delta;
  }
  bool  IsStable()
  {
    uint16_t chk_point= mAverageCount/2;  
    return  (mValidCount>chk_point)?1:0;    
  }
 
private:
  float *AvgBuffer;
  float LastSample;
  float AvgResult;
  float Delta;
  unsigned int mAverageCount,mValidCount;

};
#endif
