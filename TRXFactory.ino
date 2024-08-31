#include "TRXFactory.h"
#include "ICOM_Dev.h"
 //// Default Serial Port Rates
// (valid rates are 0=1200, 1=2400, 2=4800, 3=9600, 4=19200, 5=38400, 6=57600 and 7=115200)

 TRXDevice* TRXFactory::SetTRXType(SUPPORTED_TRX_TYPE TRX_dev) 
 {
    //if (
    if (p_Dev) 
    {
        delete p_Dev;
        p_Dev=NULL;
    }
    switch(TRX_dev)
    {
      case ICOM_CI_V_AUTO:
       p_Dev=new ICOM_Dev();
       break;
       
      default:
        break; 
    }
    return p_Dev; 
 }
