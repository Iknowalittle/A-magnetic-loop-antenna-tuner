#include <HardwareSerial.h>
#include "TRXDev.h"
const char *radiotext[] = { "ICOM generic CI-V",
                            "ICOM CI-V poll",
                            "Kenwood TS-440",
                            "Kenwood TS-870",
                            "Kenwood TS-480/2000",
                            "Yaesu FT-100",
                            "Yaesu FT-747",
                            "Yaesu FT-8X7",
                            "Yaesu FT-920",
                            "Yaesu FT-990",
                            "Yaesu FT-1000MP",
                            "Yaesu FT-1000MP Mk-V",
                            "Yaesu FT-450/950...",
                            "Elecraft K3/KX3 Auto",
                            "Elecraft K3/KX3 Poll",
                            "TenTec binary mode",
                            "TenTec ascii mode",
                            "unknown"  };

const char *GetTrxDeviceName(uint8_t i)
{
  if (i>=ICOM_CI_V_AUTO && i<=TENTEC_ASCII_MODE)
  {
    return radiotext[i];
  }else
    return "unknown";
}

 void InitializeRadioList()
 {
    uint16_t i;
    ResetRadioListBox();    
    for (i=0;i<=TENTEC_ASCII_MODE;i++)
    {
        Add2UIRadioList(radiotext[i]);      
    }
 }
 String TRXDevice::GetTRXName(SUPPORTED_TRX_TYPE dev)      //return TRX model name.
 {
   if (dev>=ICOM_CI_V_AUTO && dev<=TENTEC_ASCII_MODE)
   {
      return String(radiotext[dev]);
   }else
      return "unknown";
 }

int TRXDevice::transceiver_write(char *buf,uint8_t length)
 {
    Serial1.write(buf,length);
    return 0;  
 }

int8_t TRXDevice::transceiver_async_read(void)
{
  static uint16_t i;                            // message character count
  int8_t  Incoming;                             // Flag - Is there is a message ready to parse
  
  Incoming = false;
  
  while((Serial1.available()>0) && !Incoming)      // Are incoming characters waiting to be processed?
  {
    if (i>= 255)                                // A long string of garbage detected
    {
      i = 0;                                    // set character count to zero
      transceiver_in_string[0] = 0;             // Terminate string with a zero
    }

    else                                        // Read the incoming message
    {
      transceiver_in_string[i] = Serial2.read();   // Read the character from UART buffer
      transceiver_in_string[i+1] = 0;           // Terminate string with a zero
     // End of string - Indicate that we have stuff to process
      if (transceiver_in_string[i] == end_delimeter)//;//[controller_settings.trx[controller_settings.radioprofile].radio])
      {
        i = 0;                                  // set character count to zero
        Incoming = true;                        // Indicate that we have a new message to parse
        // Debug stuff - Print Newline to debug to denote end of message received
        //debug_println_serial();
        //debug_writeln_lcd();
      }
      else i++;                                 // character count +1
    }
  }
  return Incoming;           
}
