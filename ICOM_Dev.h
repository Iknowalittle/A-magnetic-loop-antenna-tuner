#ifndef _ICOM_DEV_HEADER
#define _ICOM_DEV_HEADER
#include "TRXDev.h"
#define CIV_TRX_ADDRESS       0x64

class ICOM_Dev : public TRXDevice
{
    public:
      ICOM_Dev()
      {
        end_delimeter=0xfd;
        default_power_level=30;
        ICOM_Addr=CIV_TRX_ADDRESS;
        InitializeSerialPort();
      }
    
    public:
      
      int set_pwr(uint16_t pwr); 
      int set_mode(uint8_t mode);
      int set_tx(void);
      int set_rx(void);
      
      int request_status(void);
      int request_mode(void);
      int request_pwr(void);
      int request_frequency(void);
      
      void parse_serial_input(void);
      int InitializeSerialPort(void);
      bool linktest();

 private:
      
        uint8_t ICOM_Addr;
        uint8_t icom_filter;
        uint8_t trx_mode;
};

#endif
