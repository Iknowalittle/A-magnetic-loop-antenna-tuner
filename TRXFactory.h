#ifndef _TRXFACTORY_HEADER
#define _TRXFACTORY_HEADER
#include "TRXDev.h"


class TRXFactory
{
  public:
      TRXFactory()
      {
        p_Dev=NULL;
        };
   
      ~TRXFactory()
      {
        if (p_Dev)
          delete p_Dev;
        }; 
  public:
      
      TRXDevice* SetTRXType(SUPPORTED_TRX_TYPE TRX_dev);     //TRX Type.
     
  private:
       SUPPORTED_TRX_TYPE  m_SelectedTRX;
       TRXDevice* p_Dev;
};



#endif
