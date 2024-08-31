#ifndef __MLAT22_SW_BANDS_HEADER
#define __MLAT22_SW_BANDS_HEADER



typedef struct __band_range
{
  uint16_t band;
  float min_freq;
  float max_freq;
  uint8_t Ham;
  float tune_offset;
}band_range;
//The Ham (Amateur Radio) bands.
#define MAX_SUPPORT_SW_BANDS  9
static band_range Supported_bands[]={
                    {160, 1.8,    2.0,    1,0},
                    {80,  3.5,    4.0,    1,0},
                    {40,  7.0,    7.3,    1,0},
                    {30,  10.1,   10.15,  1,0},
                    {20,  14.0,   14.350, 1,0},
                    {18,  18.068, 18.168, 1,0},
                    {15,  21.0,   21.450, 1,0},
                    {12,  24.890, 24.990, 1,0},                   
                    {10,  28.0,   29.70,  1,0},
};



#endif