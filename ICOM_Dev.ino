#include "ICOM_Dev.h"

//    // ICOM Address can be any value between 0x01 and 0xef
      int ICOM_Dev::set_pwr(uint16_t pwr)
      {
        // // Set RF Power Level setting
        char cmdBuffer[9]={0xfe,
                           0xfe,
                           0x00,      //ICOM_addre
                           0xe0,
                           0x14,    // Set Level
                           0x0a,    // level type = RF power
                           0x00,    //power level
                           0x00,    
                           0xfd
                           };
        cmdBuffer[2]=ICOM_Addr;
        cmdBuffer[6]=pwr/100;
        cmdBuffer[7]=pwr%100;
        transceiver_write(cmdBuffer, 9);
   
      }
      int ICOM_Dev::set_mode(uint8_t mode)
      {
         char cmdBuffer[8]={0xfe,
                           0xfe,
                           0x00,      //ICOM_addre
                           0xe0,
                           0x01,    // 01 = Set Mode and FilterLevel
                           0x0a,    // mode
                           0x00,    // filter
                           0xfd
                           };
        cmdBuffer[2]=ICOM_Addr;
        cmdBuffer[5]=mode;
        cmdBuffer[6]=icom_filter;
        transceiver_write(cmdBuffer, 8);
      }
      int ICOM_Dev::set_tx()
      {
          char cmdBuffer[8]={0xfe,
                           0xfe,
                           0x00,       
                           0xe0,
                           0x1c,    // Set Transmit on/off
                           0x00,    //  
                           0x00,    //  
                           0xfd
                           };
        cmdBuffer[2]=ICOM_Addr;
        cmdBuffer[6]=1; //  1 = TX, 0 = RX
        transceiver_write(cmdBuffer, 8);       
      }
      int ICOM_Dev::set_rx(void)
      {
             char cmdBuffer[8]={0xfe,
                           0xfe,
                           0x00,       
                           0xe0,
                           0x1c,    // Set Transmit on/off
                           0x00,    //  
                           0x00,    //  
                           0xfd
                           };
        cmdBuffer[2]=ICOM_Addr;
        cmdBuffer[6]=0; //  1 = TX, 0 = RX
        transceiver_write(cmdBuffer, 8);           
      }
      
      int ICOM_Dev::request_status(void)
      {
        
      }
      int ICOM_Dev::request_mode(void)
      {
          char cmdBuffer[6]={0xfe,
                            0xfe,
                            0x00,
                            0xe0,
                            0xe4, // 04 = Request Mode and Filter
                            0xfd};
          cmdBuffer[2]=ICOM_Addr;
          transceiver_write( cmdBuffer, 6 );

      }
      int ICOM_Dev::request_pwr(void)
      {
          char cmdBuffer[7]={0xfe,
                            0xfe,
                            0x00,
                            
                            0xe0,
                            0x14, // Request Level
                            0x0a, // level type = RF power
                            0xfd};
          cmdBuffer[2]=ICOM_Addr;     
          transceiver_write( cmdBuffer, 7 );

      }
      int ICOM_Dev::request_frequency(void)
      {
         char cmdBuffer[6]={0xfe,
                            0xfe,
                            ICOM_Addr,
                            0xe0,
                            0x03, // 04 = Request Mode and Filter
                            0xfd};
          cmdBuffer[2]=ICOM_Addr;
          transceiver_write( cmdBuffer, 6 );

      }
      
      void ICOM_Dev::parse_serial_input(void)
      {
         uint32_t civ_value; // CI-V data as a 32bit integer
      
        // Check for valid beginning of an incoming message
        // starts with <fe><fe><e0> (normal mode) or <fe><fe><00> (CIV Transceive Mode)
        if ( ((transceiver_in_string[0]==0xfe) && (transceiver_in_string[1]==0xfe)) &&
             ((transceiver_in_string[2]==0xe0) || (transceiver_in_string[2]==0x00)) )
        {                                          // start parsing
          // Check if this is indicated as a Frequency message
          // 0x00=Transfer operating frq, 0x03/0x05=Read/Write operating frq
          if ((transceiver_in_string[4] == 0x00) || (transceiver_in_string[4] == 0x03) || (transceiver_in_string[4] == 0x05))
          {
            // Convert BCD to value
            civ_value = (transceiver_in_string[5] & 0x0f);                                  // Hz
            civ_value += 10 * ((transceiver_in_string[5] & 0xf0) >> 4);                     // 10 x Hz
      
            civ_value += 100 *  (transceiver_in_string[6] & 0x0f);                          // 100 x Hz
            civ_value += 1000 * ((transceiver_in_string[6] & 0xf0) >> 4);                   // kHz
      
            civ_value += (uint32_t) 10000 * (transceiver_in_string[7] & 0x0f);              // 10 x kHz
            civ_value += (uint32_t) 100000 * ((transceiver_in_string[7] & 0xf0) >> 4);      // 100 x kHz
      
            civ_value += (uint32_t) 1000000 * (transceiver_in_string[8] & 0x0f);            // MHz
            civ_value += (uint32_t) 10000000 * ((transceiver_in_string[8] & 0xf0) >> 4);    // 10 x MHz
      
            civ_value += (uint32_t) 100000000 * (transceiver_in_string[9] & 0x0f);          // 100 x MHz
            civ_value += (uint32_t) 1000000000 * ((transceiver_in_string[9] & 0xf0) >> 4);  // GHz
      
            //
            // Update running frequency of the application
            //
            if ((civ_value > 1000000) && (civ_value < 31000000)) // Impose some sane boundaries
            {
             // antenna_select(civ_value);                         // Antenna switchover, if frequency applies to the other antenna  
             // running[ant].Frq = civ_value;
            //  radio.timer = true;                                // Indicate that we are receiving frq data from Radio
             // radio.online = true;  
            }
            //radio.ack = true;
          }
          // Check if this is an incoming Power Level Indication message
          else if ((transceiver_in_string[4] == 0x14) && (transceiver_in_string[5] == 0x0a))
          {
            //trx_pwr = 100 * transceiver_in_string[6];
            //trx_pwr += transceiver_in_string[7];
            //radio.pwr = true;                              // Indicate that we have successfully read power control level
            //radio.ack = true;
          }
          // Check if this is an incoming Mode and Filter Indication message
          else if (transceiver_in_string[4] == 0x04)       // Read active Mode (LSB, USB etc)
          {
            trx_mode = transceiver_in_string[5];           // 0=LSB 1=USB 2=AM 3=CW... 
            icom_filter = transceiver_in_string[6];
            //radio.mode = true;                             // Indicate that we have successfully read active mode
            //radio.ack = true;
          }
          // Check if this is a Positive acknowlegement message
          else if (transceiver_in_string[4] == 0xfb)       // OK
          {
            //radio.ack = true;
          }
          // Check if this is a Negative acknowlegement message
          else if (transceiver_in_string[4] == 0xfa)       // OK
          {
            //radio.ack = false;
          }
        }     
      }
