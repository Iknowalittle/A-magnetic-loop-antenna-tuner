#ifndef MLAT_TRX_DEV_HEADER
#define MLAT_TRX_DEV_HEADER

// 0  = ICOM CI-V Auto
// 1  = ICOM CI-V Poll
// 2  = Kenwood TS-440
// 3 =  Kenwood TS-870
// 4  = Kenwood TS-480/TS-590/TS-2000
// 5  = Yaesu FT-100
// 6  = Yaesu FT-7X7 (747...)
// 7  = Yaesu FT-8x7 (817,847,857,897)
// 8  = Yaesu FT-920
// 9  = Yaesu FT-990
// 10 = Yaesu FT-1000MP
// 11 = Yaesu FT-1000MP Mk-V
// 12 = Yaesu FT-450/950/1200/2000/3000/5000
// 13 = Elecraft K3/KX3 Auto
// 14 = Elecraft K3/KX3 Poll
// 15 = TenTec binary mode
// 16 = TenTec ascii mode

typedef enum _TRX_LIST_
{
  ICOM_CI_V_AUTO=0,
  ICOM_CI_V_POLL,   //1
  KENWOOD_TS_440,   //2
  KENWOOD_TS_870,   //3
  KENWOOD_TS_480,   //4 TS-590/TS-2000
  YAESU_FT_100,     //5
  YAESU_FT_7X7,     //6 747
  YAESU_FT_8X7,     //7
  YAESU_FT_920,     //8
  YAESU_FT_990,     //9
  YAESU_FT_1000MP,  //10  
  YAESU_FT_1000MO_MKV,  //11
  YAESU_FT_450,     //12    950/1200/2000/3000/5000
  ELECRAFT_K3_KX3_AUTO, //13
  ELECRAFT_K3_KX3_POLL, //14
  TENTEC_BIN_MODE,      //15
  TENTEC_ASCII_MODE,     //16
  TRX_UNKNOWN=255
}SUPPORTED_TRX_TYPE;
const char *GetTrxDeviceName(uint8_t i);
class TRXDevice
{
  public:
    
     int8_t transceiver_async_read(void);            
     String GetTRXName(SUPPORTED_TRX_TYPE dev);      //return TRX model name.
     int    transceiver_write(char *buf,uint8_t length);
    virtual  int set_pwr(uint16_t pwr); 
    virtual  int set_mode(uint8_t mode);
    virtual  int set_tx(void);
    virtual  int set_rx(void);
      
    virtual  int request_status(void);
    virtual  int request_mode(void);
    virtual  int request_pwr(void);
    virtual  int request_frequency(void);
      
    virtual  void parse_serial_input(void);
    virtual  int InitializeSerialPort(void);
    virtual  bool linktest();

  protected:
     char transceiver_in_string[2048]; // Incoming serial string to parse
     char end_delimeter;
     uint8_t default_power_level;        //default power level.
//
};



#endif
