//<App !Start!>
// FILE: [Arduino.ino]
// Created by GUIslice Builder version: [0.17.b12]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>
#include "HardwareStuff.h"
#include "MovingAverage.h"
#include "MLAT22.h"
#include "AntennaParaMgr.h"
#include <FS.h>
#include <SPIFFS.h>
#include <TMCStepper.h>
#include "MLAT22UI_GSLC.h"
#include <TFT_eSPI.h>
#include "RotaryEncoder.h"
#include "ChartPlotter.h"
#include "ShortWaveBands.h"
#include "ESPTelnet.h"
#include <vector>
extern ESPTelnet telnet;
extern bool TelnetConnected;
extern volatile uint32_t ActiveFrequency;
extern bool UseInternalClkSrc;

bool OTAModeEnabled = false;
bool TelnetEnabled = false;
bool TrxSignalExists = false;
uint8_t clk_src = 0;
bool MsgBoxOK=false;
char MsgBoxBuffer[512];
//String inputString = "";          // a String to hold incoming data
enum CMD_SOURCE {
  NO_COMMAND = 0,
  SERIAL_INPUT = 1,
  TELNET_INPUT = 2,
  UICMD_INPUT,
};
CMD_SOURCE StringCommandInput = NO_COMMAND;  // whether the string is complete

bool Taskrunning = false;

#define MAX_MSG_LENGTH 250
uint16_t current_rx_ptr = 0;
char rx_buffer[MAX_MSG_LENGTH];

extern MOT_MAN_MODE Current_MOT_MODE;
extern MotorRunningMsg MotorMsg;  // for service mode task.
extern volatile uint8_t MotorEnabled;

extern TMC2209Stepper MotorDriver;

uint16_t OldStallDetected = 0;
uint16_t StallCount = 0;
uint16_t old_busy_prg_val = 0;  // busy box indicator
uint32_t tmr_watch_count;       //timer watch for finding motor home position progress
int16_t TrxSelected, FreqSelected, WiFiSelected;

uint32_t MaxMotorMoveSteps = 0;
int32_t CurrentMotorPosition = 0;
int8_t MotorDir;
uint32_t CurrentSelectedFrequency = 0;
std::vector<uint16_t> PageStacks;
AuxRotEncoder rotaryEncoder;
ExtButton PowerOffKey;

LineChart mChart;
float FreqDetected;
#define PRESET_FREQ_PER_PAGE 4

uint16_t MaxPresetFreqs = 0;
uint16_t MaxPresetPages = 0;
uint16_t CurrentPresetPage;
//extern ESP_FlexyStepper stepper;
//unsigned    m_nCount = 0;
extern volatile uint16_t ioex_int_flag;
extern volatile uint8_t MotorStallFlag;
// move to antenna
MotorInformationDef MotorRunningConfig;
SWR_METER_OFFSET SWRMeterParas;
bool SwrMeterMode = false;
bool WifiInformationValid = false;

String PageID = "";  //user defined PageID. which can be displayed on the up right corner of Main UI
// record last actived Antenna and Position.
PositionInfomation OldAntennaPosInfo;

AntennaParaManager ML_ANT[4];  //support 4 antenna max.
float Freq_Delta[2]={0,0};
float FREF_Set[2]={0,0};
float FCorr_K=0,FCorr_B=0;
FREQ_CAL_OFFSET FreqCalPara;
float old_disp_freq=0.0f;
uint32_t  theTickOfBoot=0;
uint32_t  theMinOfBoot=0;
uint32_t  theSecOfBoot=0;
uint32_t  theHoursOfBoot=0;
// ------------------------------------------------
// Headers to include
// ------------------------------------------------



// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_eleSWRFWD = NULL;
gslc_tsElemRef* m_eleSWRREV = NULL;
gslc_tsElemRef* m_ele_ANTID116 = NULL;
gslc_tsElemRef* m_ele_BTN_TRX115 = NULL;
gslc_tsElemRef* m_ele_SWR = NULL;
gslc_tsElemRef* m_ele_TRXFreq = NULL;
gslc_tsElemRef* m_pElemANTC0 = NULL;
gslc_tsElemRef* m_pElemANTC1 = NULL;
gslc_tsElemRef* m_pElemANTC2 = NULL;
gslc_tsElemRef* m_pElemAddFreq = NULL;
gslc_tsElemRef* m_pElemAntIndex = NULL;
gslc_tsElemRef* m_pElemAntPage1 = NULL;
gslc_tsElemRef* m_pElemAntPage2 = NULL;
gslc_tsElemRef* m_pElemAntPage3 = NULL;
gslc_tsElemRef* m_pElemBand = NULL;
gslc_tsElemRef* m_pElemBandMeter = NULL;
gslc_tsElemRef* m_pElemBtn72 = NULL;
gslc_tsElemRef* m_pElemBtn72_125 = NULL;
gslc_tsElemRef* m_pElemBtn72_139 = NULL;
gslc_tsElemRef* m_pElemBtnBFO = NULL;
gslc_tsElemRef* m_pElemBtnBFOCH1 = NULL;
gslc_tsElemRef* m_pElemBtnBFOCH2 = NULL;
gslc_tsElemRef* m_pElemBtnMenu = NULL;
gslc_tsElemRef* m_pElemCBCheckBox = NULL;
gslc_tsElemRef* m_pElemChartTitle = NULL;
gslc_tsElemRef* m_pElemCurrentPos = NULL;
gslc_tsElemRef* m_pElemFWDUnit = NULL;
gslc_tsElemRef* m_pElemFreqSrc = NULL;
gslc_tsElemRef* m_pElemFstep = NULL;
gslc_tsElemRef* m_pElemFstep214 = NULL;
gslc_tsElemRef* m_pElemGraph_FreqScan = NULL;
gslc_tsElemRef* m_pElemIPAddr0 = NULL;
gslc_tsElemRef* m_pElemLinkTest = NULL;
gslc_tsElemRef* m_pElemListbox1_3 = NULL;
gslc_tsElemRef* m_pElemListboxFreq = NULL;
gslc_tsElemRef* m_pElemListboxWifi = NULL;
gslc_tsElemRef* m_pElemMsgBoxText = NULL;
gslc_tsElemRef* m_pElemNextPage = NULL;
gslc_tsElemRef* m_pElemOTA129 = NULL;
gslc_tsElemRef* m_pElemOTA129_136 = NULL;
gslc_tsElemRef* m_pElemOldTRX = NULL;
gslc_tsElemRef* m_pElemOutTxt185 = NULL;
gslc_tsElemRef* m_pElemOutTxt186 = NULL;
gslc_tsElemRef* m_pElemOutTxt250 = NULL;
gslc_tsElemRef* m_pElemOutTxt250_251 = NULL;
gslc_tsElemRef* m_pElemOutTxt250_252 = NULL;
gslc_tsElemRef* m_pElemOutTxt259_261 = NULL;
gslc_tsElemRef* m_pElemPF0 = NULL;
gslc_tsElemRef* m_pElemPF1 = NULL;
gslc_tsElemRef* m_pElemPF2 = NULL;
gslc_tsElemRef* m_pElemPF3 = NULL;
gslc_tsElemRef* m_pElemPSKConf229_233 = NULL;
gslc_tsElemRef* m_pElemPrevPage = NULL;
gslc_tsElemRef* m_pElemProgress1 = NULL;
gslc_tsElemRef* m_pElemRBFreqSrc = NULL;
gslc_tsElemRef* m_pElemRBRadioButton2_4 = NULL;
gslc_tsElemRef* m_pElemRBRadioButton3 = NULL;
gslc_tsElemRef* m_pElemREFunit = NULL;
gslc_tsElemRef* m_pElemRemFreq = NULL;
gslc_tsElemRef* m_pElemSSIDConf227_231 = NULL;
gslc_tsElemRef* m_pElemSWRSetting = NULL;
gslc_tsElemRef* m_pElemSWRSetting154 = NULL;
gslc_tsElemRef* m_pElemSeekbarRMS = NULL;
gslc_tsElemRef* m_pElemSeekbarSPEED = NULL;
gslc_tsElemRef* m_pElemSeekbarSTALL = NULL;
gslc_tsElemRef* m_pElemSigSrc146 = NULL;
gslc_tsElemRef* m_pElemSliderBand = NULL;
gslc_tsElemRef* m_pElemSwitchFreq = NULL;
gslc_tsElemRef* m_pElemTRXOK = NULL;
gslc_tsElemRef* m_pElemTipInfo = NULL;
gslc_tsElemRef* m_pElemVal17_18_24 = NULL;
gslc_tsElemRef* m_pElemVal17_19_25 = NULL;
gslc_tsElemRef* m_pElemVal17_20_26 = NULL;
gslc_tsElemRef* m_pElemVal17_23 = NULL;
gslc_tsElemRef* m_pElemValBFO0 = NULL;
gslc_tsElemRef* m_pElemValBFO1 = NULL;
gslc_tsElemRef* m_pElemValBFO2 = NULL;
gslc_tsElemRef* m_pElemValFS0 = NULL;
gslc_tsElemRef* m_pElemValFSE = NULL;
gslc_tsElemRef* m_pElemValFStep = NULL;
gslc_tsElemRef* m_pElemValFreq = NULL;
gslc_tsElemRef* m_pElemWiFiSave = NULL;
gslc_tsElemRef* m_pElemXRingGauge1 = NULL;
gslc_tsElemRef* m_pElem_ICOM_Addr8 = NULL;
gslc_tsElemRef* m_pElem_MaxPos = NULL;
gslc_tsElemRef* m_pElem_MotorPos = NULL;
gslc_tsElemRef* m_pElem_MotorPos213 = NULL;
gslc_tsElemRef* m_pElem_SSID0 = NULL;
gslc_tsElemRef* m_pElem_TrxName = NULL;
gslc_tsElemRef* m_pElemtxtPSK = NULL;
gslc_tsElemRef* m_pListSlider1 = NULL;
gslc_tsElemRef* m_pListSlider2 = NULL;
gslc_tsElemRef* m_pListSlider4 = NULL;
gslc_tsElemRef* p_ElemSteps = NULL;
gslc_tsElemRef* p_ElemStepsCur = NULL;
gslc_tsElemRef* p_Elem_InputString = NULL;
gslc_tsElemRef* p_Elem_Unit = NULL;
gslc_tsElemRef* p_elem_IP_addr165_179_188 = NULL;
gslc_tsElemRef* p_elem_IP_addr165_183 = NULL;
gslc_tsElemRef* m_pElemKeyPadNum = NULL;
gslc_tsElemRef* m_pElemKeyPadAlpha = NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) {
  if (ch == (char)'\n') Serial.println("");
  else Serial.write(ch);
  return 0;
}

//uint16_t last_act_page=E_PG_MAIN;

HARD_CONFIG_DATA mlat_cfg_data;
SYSTEM_CFG mlat_act_setting;

void resprintf(char* format, ...) {
  char resp[MAX_STR];
  va_list aptr;
  va_start(aptr, format);
  vsprintf(resp, format, aptr);
  va_end(aptr);
  if (TelnetConnected) telnet.print(resp);
  Serial.print(resp);
}

void EnableButton(gslc_tsElemRef* Button, gslc_tsColor color = GSLC_COL_RED) {
  gslc_ElemSetClickEn(&m_gui, Button, true);
  gslc_ElemSetCol(&m_gui, Button, GSLC_COL_BLUE_DK2, color, GSLC_COL_BLUE_DK1);
}
void DisableButton(gslc_tsElemRef* Button) {
  gslc_ElemSetClickEn(&m_gui, Button, false);
  gslc_ElemSetCol(&m_gui, Button, GSLC_COL_BLUE_DK2, GSLC_COL_GRAY_DK1, GSLC_COL_BLUE_DK1);
}
void SetCtrlValueInt(gslc_tsElemRef* Ctl, int32_t V) {
  char acTxt[10];
  sprintf(acTxt, "%d", V);
  gslc_ElemSetTxtStr(&m_gui, Ctl, acTxt);
}
int32_t GetCtrlValueInt(gslc_tsElemRef* Ctl) {
  return atoi(gslc_ElemGetTxtStr(&m_gui, Ctl));
}
void RemovePresetFreq() {
  if (FreqSelected >= 0) {
    char acTxt[MAX_STR];
    uint32_t freq;
    gslc_ElemXListboxGetItem(&m_gui, m_pElemListboxFreq, FreqSelected, acTxt, MAX_STR);
    freq = atof(acTxt) * 1e6;

    ML_ANT[mlat_act_setting.last_actived_ant].RemovePosition(freq);
    // gslc_ElemXListboxDeleteItemAt(&m_gui, m_pElemListboxFreq,FreqSelected);
    //SetUICommand("loadant");
    LoadAntennaDataOnUI(mlat_act_setting.last_actived_ant);
    // gslc_ElemXListboxDeleteItemAt(&m_gui, m_pElemListboxFreq,FreqSelected);
  }
}
void UpdateKeypadInput(uint8_t keyIndex) {
  char sBuffer[30];
  char tmp[2];
  char sUnit[10];
  uint16_t l;
  float f_coeff = 1;
  uint32_t targetfreq;
  memset(sBuffer, 0, 30);
  memset(tmp, 0, 2);
  sprintf(sBuffer, "%s", gslc_ElemGetTxtStr(&m_gui, p_Elem_InputString));
  sprintf(sUnit, "%s", gslc_ElemGetTxtStr(&m_gui, p_Elem_Unit));
  if (strcmp(sUnit, "MHz") == 0) {
    f_coeff = 1e6;
  } else if (strcmp(sUnit, "KHz") == 0) {
    f_coeff = 1e3;
  }

  l = strlen(sBuffer);
  switch (keyIndex) {
    case 0 ... 9:
      sprintf(tmp, "%d", keyIndex);
      strcat(sBuffer, tmp);
      gslc_ElemSetTxtStr(&m_gui, p_Elem_InputString, sBuffer);
      break;
    case 10:
      if (strstr(sBuffer, ".")) return;
      strcat(sBuffer, ".");
      gslc_ElemSetTxtStr(&m_gui, p_Elem_InputString, sBuffer);
      break;
    case 11:
      //<-
      if (l) memset(sBuffer + l - 1, 0, 1);
      gslc_ElemSetTxtStr(&m_gui, p_Elem_InputString, sBuffer);
      break;
    case 12:
      //clear all
      gslc_ElemSetTxtStr(&m_gui, p_Elem_InputString, "");
      break;
    case 13:
      targetfreq = atof(sBuffer) * f_coeff;
      if (targetfreq > 0) {
        if (ML_ANT[mlat_act_setting.last_actived_ant].GetSavePositionFromFrequency(targetfreq) == -1) {
          Serial.printf("user set frequency to %d \r\n", targetfreq);
          SetUICommand("fswr %d", targetfreq);
        } else {
          Serial.printf("Frequency %d is already set\r\n", targetfreq);
        }
      }
      PageHide(E_PG_NUMKEYPAD);
      break;
    case 14:
      gslc_ElemSetTxtStr(&m_gui, p_Elem_Unit, "MHz");
      break;
    case 15:
      gslc_ElemSetTxtStr(&m_gui, p_Elem_Unit, "KHz");
      break;
    case 16:
      gslc_ElemSetTxtStr(&m_gui, p_Elem_Unit, "Hz");
      break;
  };
  return;
}

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui, void* pvElemRef, gslc_teTouch eTouch, int16_t nX, int16_t nY) {
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
  char acTxt[MAX_STR];
   //  Serial.printf("%d> pressed\r\n",pElem->nId);

  if (eTouch == GSLC_TOUCH_UP_IN) {
    // From the element's ID we can determine which button was pressed.

    switch (pElem->nId) {
        //<Button Enums !Start!>
      case E_ELEM_BTN118:
        PageShow(E_PG_MENU);
        break;
      case E_ELEM_BTN119:
        ProcessPresetButton(0);
        break;
      case E_ELEM_BTN120:
        ProcessPresetButton(1);
        break;
      case E_ELEM_BTN121:
        ProcessPresetButton(2);
        break;
      case E_ELEM_BTN122:
        ProcessPresetButton(3);
        break;
      case E_ELEM_BTN123:
        break;
      case E_ELEM_BTN124:
        break;  
      case E_ELEM_BTN156:       // pos ++
         SetUICommand("move 1 800");
        break;
      case E_ELEM_BTN155:       // pos --
 
         SetUICommand("move -1 800");
        break;
      case E_ELEM_BTN_LINKTEST:

        break;
      case E_ELEM_BTN_TRXOK:
        PageHide(E_PG_RADIO);
        //save Selected TRX...
        if (TrxSelected >= 0) {
          mlat_act_setting.LastSelectedTRX = (SUPPORTED_TRX_TYPE)TrxSelected;
          mlat_act_setting.TrxAddress = atoi(gslc_ElemGetTxtStr(&m_gui, m_pElem_ICOM_Addr8));
          Serial.printf("will save Trx to %d, addr:%d\r\n", mlat_act_setting.LastSelectedTRX, mlat_act_setting.TrxAddress);
          SaveCommonConfiguration();

        } else {
          Serial.printf("no valid TRX selected.\r\n");
        }

        break;
      case E_ELEM_NUMINPUT8:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElem_ICOM_Addr8);
        break;
      case E_ELEM_BTN64:
        PageHide(E_PG_ANT);
        break;
      case E_ELEM_BTN69:
        PageHide(E_PG_RADIO);
        break;
      case E_ELEM_BTN70:
        PageHide(E_PG_MENU);
        break;
      case E_ELEM_BTN66:
        PageHide(E_PG_SWR_CHART);
        SwrMeterMode = false;
        
        break;

      case E_ELEM_MSG_OK:
         MsgBoxOK=true;
        PageHide(E_PG_MSBOX);
        //MsgOK
        break;
      case E_ELEM_BTN_SWITCH_ANT:
        // gslc_SetPageCur(&m_gui, E_PG_MAIN);

        break;
      case E_ELEM_BTN54:  //Add freq
        PageShow(E_PG_NUMKEYPAD);
        break;
      case E_ELEM_BTN55:  //remove freq
        RemovePresetFreq();
        break;
      case E_ELEM_BTN56:  //page ant 1
        break;
      case E_ELEM_BTN57:  //page ant 2
        break;
      case E_ELEM_BTN58:  //page ant 3
        break;
      case E_ELEM_BTN72:
        PageShow(E_PG_WIFI);
        break;
      case E_ELEM_BTN115:
        PageShow(E_PG_RADIO);
        break;
      case E_ELEM_BTN116:
        PageShow(E_PG_ANT);
        break;
      case E_ELEM_BTN125:
        PageShow(E_PG_SWR_CHART);
        break;
      case E_ELEM_BTN129:
        DoOTAUpgrade();
        break;
      case E_ELEM_BTN114:
        SwrMeterMode = false;
        PageShow(E_PG_POPUP_FS);
        break;
      case E_ELEM_TEXTINPUT2:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadAlpha, E_POP_KEYPAD_ALPHA, m_pElemtxtPSK);
        break;
      case E_ELEM_BTN74:
        PageHide(E_PG_WIFI);
        break;
      case E_ELEM_BTN113:  //refresh wifi
        RefreshWifiList();
        break;
      case E_ELEM_BTN128:  //E_ELEM_BTN128
        //save Wifi.
        //mlat_act_setting.WifiSSID
        //m_pElemtxtPSK
        SaveWifi();
        break;
      case E_ELEM_BTN_NUM1:
        UpdateKeypadInput(1);
        break;
      case E_ELEM_BTN_NUM2:
        UpdateKeypadInput(2);
        break;
      case E_ELEM_BTN_NUM3:
        UpdateKeypadInput(3);
        break;
      case E_ELEM_BTN_NUM4:
        UpdateKeypadInput(4);
        break;
      case E_ELEM_BTN_NUM5:
        UpdateKeypadInput(5);
        break;
      case E_ELEM_BTN_NUM6:
        UpdateKeypadInput(6);
        break;
      case E_ELEM_BTN_NUM7:
        UpdateKeypadInput(7);
        break;
      case E_ELEM_BTN_NUM8:
        UpdateKeypadInput(8);
        break;
      case E_ELEM_BTN_NUM9:
        UpdateKeypadInput(9);
        break;
      case E_ELEM_BTN_NUMDOT:
        UpdateKeypadInput(10);
        break;
      case E_ELEM_BTN_NUM0:
        UpdateKeypadInput(0);
        break;
      case E_ELEM_BTN_MHZ:
        UpdateKeypadInput(14);
        break;
      case E_ELEM_BTN_BKSP:
        UpdateKeypadInput(11);
        break;
      case E_ELEM_BTN_ENT:
        UpdateKeypadInput(13);
        break;
      case E_ELEM_BTN_CLR:
        UpdateKeypadInput(12);
        break;
      case E_ELEM_BTN112:
        PageHide(E_PG_NUMKEYPAD);
        break;
      case E_ELEM_BTN_FREQOK:
        //get fs, fe, fstep,
        Config2SwrMode();
        PageHide(E_PG_POPUP_FS);
        break;
      case E_ELEM_NUMINPUT11:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemValFS0);
        break;
      case E_ELEM_NUMINPUT12:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemValFSE);
        break;
      case E_ELEM_NUMINPUT13:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemValFStep);
        break;
      case E_ELEM_BTN133:
        PageHide(E_PG_MOTOR_CFG);
        break;
      case E_ELEM_BTN131:
        PageShow(E_PG_MOTOR_CFG);
        break;
      case E_ELEM_BTN65:
        //Find Home...
        SetUICommand("findhome");
        break;
      case E_ELEM_BTN134:
        //Save Motor Parameters.
        MotorInformationDef motinf;
        ML_ANT[mlat_act_setting.last_actived_ant].GetMotorParameters(&motinf);
        motinf.MaxCurrent = gslc_ElemXSeekbarGetPos(&m_gui, m_pElemSeekbarRMS);
        motinf.min_delay_us = gslc_ElemXSeekbarGetPos(&m_gui, m_pElemSeekbarSPEED);
        motinf.StallTH = gslc_ElemXSeekbarGetPos(&m_gui, m_pElemSeekbarSTALL);
        ML_ANT[mlat_act_setting.last_actived_ant].SaveMotorParameters(&motinf);
        break;
      case E_ELEM_BTN135:
        gslc_ElemXSeekbarSetPos(&m_gui, m_pElemSeekbarRMS, DEFAULT_MOTOR_CURRENT);
        gslc_ElemXSeekbarSetPos(&m_gui, m_pElemSeekbarSPEED, DEFAULT_MOTOT_INT_TIME);
        gslc_ElemXSeekbarSetPos(&m_gui, m_pElemSeekbarSTALL, DEFAULT_MOTOR_STALL_TH);
        break;
      case E_ELEM_BTN136:  //BFO Ctrl
        PageShow(E_PG_BFO);
        break;
      case E_ELEM_BTN137:  //Save Basic setting...
        break;
      case E_ELEM_BTN138:
        PageHide(E_PG_BASIC_SETTING);
        break;
      case E_ELEM_BTN139:
        PageShow(E_PG_BASIC_SETTING);
        break;
      case E_ELEM_NUMINPUT14:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemValBFO0);
        break;
      case E_ELEM_BTN140:
        //toggle BFO OnOff
        break;
      case E_ELEM_BTN142:
        PageHide(E_PG_BFO);
        break;
      case E_ELEM_NUMINPUT15:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemValBFO1);
        break;
      case E_ELEM_BTN144:
        break;
      case E_ELEM_NUMINPUT16:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemValBFO2);
        break;
      case E_ELEM_BTN145:
        break;
      case E_ELEM_BTN146:
        ToggleFreqSource();
        break;
      case E_ELEM_NUMINPUT23:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemVal17_23);
        break;
      case E_ELEM_NUMINPUT24:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemVal17_18_24);
        break;
      case E_ELEM_NUMINPUT25:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemVal17_19_25);
        break;
      case E_ELEM_NUMINPUT26:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemVal17_20_26);
        break;
      case E_ELEM_BTN152:
        SaveSWRDataFromUI();
        PageHide(E_PG_SWR_CAL);  //save meter cal parameters
        break;
      case E_ELEM_BTN153:  //load meter cal parameters default.
                           // PageHide(E_PG_SWR_CAL);
        SetSwrDefault();
        LoadSWRData2UI();
        break;
      case E_ELEM_BTN154:
        LoadSWRData2UI();
        PageShow(E_PG_SWR_CAL);
        break;
        //<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}
// Checkbox / radio callbacks
// - Creating a callback function is optional, but doing so enables you to
//   detect changes in the state of the elements.
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState) {
  gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
  if (pElemRef == NULL) {
    return false;
  }

  boolean bChecked = gslc_ElemXCheckboxGetState(pGui, pElemRef);

  // Determine which element issued the callback
  switch (pElem->nId) {
      //<Checkbox Enums !Start!>
    case E_ELEM_CHECK2:
      break;

    case E_ELEM_RADIO3:
      break;
    case E_ELEM_RADIO4:
      break;
    case E_ELEM_RADIO5:
      break;
    case E_ELEM_CHECK3:
      break;
      //<Checkbox Enums !End!>
    default:
      break;
  }  // switch
  return true;
}
// KeyPad Input Ready callback
bool CbKeypad(void* pvGui, void* pvElemRef, int16_t nState, void* pvData) {
  gslc_tsGui* pGui = (gslc_tsGui*)pvGui;
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);

  // From the pvData we can get the ID element that is ready.
  int16_t nTargetElemId = gslc_ElemXKeyPadDataTargetIdGet(pGui, pvData);
  if (nState == XKEYPAD_CB_STATE_DONE) {
    // User clicked on Enter to leave popup
    // - If we have a popup active, pass the return value directly to
    //   the corresponding value field
    switch (nTargetElemId) {
        //<Keypad Enums !Start!>
      case E_ELEM_NUMINPUT8:
        gslc_ElemXKeyPadInputGet(pGui, m_pElem_ICOM_Addr8, pvData);
        gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_TEXTINPUT2:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemtxtPSK, pvData);
        gslc_PopupHide(&m_gui);
        break;

      case E_ELEM_NUMINPUT11:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemValFS0, pvData);
        gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_NUMINPUT12:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemValFSE, pvData);
        gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_NUMINPUT13:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemValFStep, pvData);
        gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_NUMINPUT14:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemValBFO0, pvData);
        gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_NUMINPUT15:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemValBFO1, pvData);
        gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_NUMINPUT16:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemValBFO2, pvData);
        gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_NUMINPUT23:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemVal17_23, pvData);
        gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_NUMINPUT24:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemVal17_18_24, pvData);
        gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_NUMINPUT25:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemVal17_19_25, pvData);
        gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_NUMINPUT26:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemVal17_20_26, pvData);
        gslc_PopupHide(&m_gui);
        break;
        //<Keypad Enums !End!>
      default:
        break;
    }
  } else if (nState == XKEYPAD_CB_STATE_CANCEL) {
    // User escaped from popup, so don't update values
    gslc_PopupHide(&m_gui);
  }
  return true;
}
// Spinner Input Ready callback
bool CbSpinner(void* pvGui, void* pvElemRef, int16_t nState, void* pvData) {
  gslc_tsGui* pGui = (gslc_tsGui*)pvGui;
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);

  // NOTE: pvData is NULL
}
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId) {
  gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
  char acTxt[MAX_STR + 1];

  if (pElemRef == NULL) {
    return false;
  }
  //int16_t   TrxSelected,FreqSelected,WiFiSelected;

  // From the element's ID we can determine which listbox was active.
  switch (pElem->nId) {
      //<Listbox Enums !Start!>
    case E_ELEM_LISTBOX_FREQ:  //Radio
      FreqSelected = nSelId;
      if (nSelId != XLISTBOX_SEL_NONE) {
        SelectFreqItem(nSelId);
        //gslc_ElemXListboxGetItem(&m_gui, pElemRef, nSelId, acTxt, MAX_STR);
        //Serial.printf("Select: %s\n",acTxt);
      }
      break;
    case E_ELEM_LISTBOX3:  //Radio List
      if (nSelId != XLISTBOX_SEL_NONE) {
        // gslc_ElemXListboxGetItem(&m_gui, pElemRef, nSelId, acTxt, MAX_STR);
        TrxSelected = nSelId;
        //   mlat_act_setting.LastSelectedTRX=(SUPPORTED_TRX_TYPE)nSelId;
      } else
        TrxSelected = -100;
      break;
    case E_ELEM_LISTBOX4:  //WIFI

      if (nSelId != XLISTBOX_SEL_NONE) {
        //gslc_ElemXListboxGetItem(&m_gui, pElemRef, nSelId, acTxt, MAX_STR);
        // Serial.printf("Select: %s\n",acTxt);
        WiFiSelected = nSelId;
      } else
        WiFiSelected = -100;

      break;
      //<Listbox Enums !End!>
    default:
      break;
  }
  return true;
}
//<Draw Callback !Start!>
//<Draw Callback !End!>

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui, void* pvElemRef, int16_t nPos) {
  gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
  int16_t nVal;
  char acTxt[10];
  // From the element's ID we can determine which slider was updated.
  switch (pElem->nId) {
      //<Slider Enums !Start!>
    case E_LISTSCROLL1:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui, m_pListSlider1);
      gslc_ElemXListboxSetScrollPos(pGui, m_pElemListbox1_3, nVal);
      break;

    case E_LISTSCROLL2:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui, m_pListSlider2);
      gslc_ElemXListboxSetScrollPos(pGui, m_pElemListboxFreq, nVal);

      break;
    case E_LISTSCROLL4:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui, m_pListSlider4);
      gslc_ElemXListboxSetScrollPos(pGui, m_pElemListboxWifi, nVal);
      break;
    case E_ELEM_SLIDER2:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui, m_pElemSliderBand);
      ShowSWBands(nVal);
      break;
    case E_ELEM_SEEKBAR2:
      // Fetch the slider position
      nVal = gslc_ElemXSeekbarGetPos(pGui, m_pElemSeekbarRMS);
      sprintf(acTxt, "%d", nVal);
      gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt250, acTxt);
      break;
    case E_ELEM_SEEKBAR3:
      // Fetch the slider position
      nVal = gslc_ElemXSeekbarGetPos(pGui, m_pElemSeekbarSPEED);
      sprintf(acTxt, "%d", nVal);
      gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt250_251, acTxt);
      break;
    case E_ELEM_SEEKBAR4:
      // Fetch the slider position
      nVal = gslc_ElemXSeekbarGetPos(pGui, m_pElemSeekbarSTALL);
      sprintf(acTxt, "%d", nVal);
      gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt250_252, acTxt);
      break;
      //<Slider Enums !End!>
    default:
      break;
  }

  return true;
}
//<Tick Callback !Start!>
//<Tick Callback !End!>
void Config2SwrMode() {

  //gslc_ElemGetTxtStr(&m_gui,m_pElemValFS0)
  //m_pElemValFS0,m_pElemValFSE,m_pElemValFStep
  gslc_ElemSetTxtStr(&m_gui, m_pElemValFreq, gslc_ElemGetTxtStr(&m_gui, m_pElemValFS0));
  gslc_ElemSetTxtStr(&m_gui, m_pElem_MotorPos, gslc_ElemGetTxtStr(&m_gui, m_pElemValFSE));
  gslc_ElemSetTxtStr(&m_gui, m_pElem_MotorPos213, gslc_ElemGetTxtStr(&m_gui, m_pElemValFStep));

  Switch2BFOChan();
  UpdateFreqSource(1);

  SwrMeterMode = true;
}
void SaveWifi() {
  char acTxt[MAX_STR];
  if (WiFiSelected >= 0) {
    gslc_ElemXListboxGetItem(&m_gui, m_pElemListboxWifi, WiFiSelected, acTxt, MAX_STR);
    gslc_ElemSetTxtStr(&m_gui, m_pElemSSIDConf227_231, acTxt);
    gslc_ElemSetTxtStr(&m_gui, m_pElemPSKConf229_233, gslc_ElemGetTxtStr(&m_gui, m_pElemtxtPSK));
    sprintf(mlat_act_setting.WifiSSID, "%s", acTxt);
    sprintf(mlat_act_setting.WifiPsk, "%s", gslc_ElemGetTxtStr(&m_gui, m_pElemtxtPSK));
    SaveCommonConfiguration();
  }
}

void ToggleFreqSource(uint8_t Trx) {
  static uint8_t Old_trx = 0;
  if (Trx == 3) {
    if (Old_trx == 0) {
      Old_trx = 1;
      Switch2BFOChan();
    } else {
      Old_trx = 0;
      Switch2TRXChan();
    }
  } else {
    if (Trx == 0) {
      Switch2TRXChan();
      Old_trx = 0;
    } else {
      Switch2BFOChan();
      Old_trx = 1;
    }
  }
  UpdateFreqSource(Old_trx);
}

void ShowSWBands(uint16_t iVal) {
  char acBuf[6];
  uint8_t index = iVal / 10;
  static uint8_t old_index = 100;
  if (index == old_index) return;
  if (index <= MAX_SUPPORT_SW_BANDS - 1) {
    sprintf(acBuf, "%d", Supported_bands[index].band);
    gslc_ElemSetTxtStr(&m_gui, m_pElemBand, acBuf);
    sprintf(acBuf, "%.2f", Supported_bands[index].min_freq);
    gslc_ElemSetTxtStr(&m_gui, m_pElemValFS0, acBuf);
    sprintf(acBuf, "%.2f", Supported_bands[index].max_freq);
    gslc_ElemSetTxtStr(&m_gui, m_pElemValFSE, acBuf);
  } else {
    gslc_ElemSetTxtStr(&m_gui, m_pElemBand, "N/A");
  }
  old_index = index;
}
void ResetRadioListBox()  //void gslc_ElemXListboxReset(gslc_tsGui* pGui, gslc_tsElemRef* pElemRef);
{
  gslc_ElemXListboxReset(&m_gui, m_pElemListbox1_3);
}
void ResetWifiListBox() {
  gslc_ElemXListboxReset(&m_gui, m_pElemListboxWifi);
}
void ResetFreqListBox() {
  gslc_ElemXListboxReset(&m_gui, m_pElemListboxFreq);
}
//  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "Yaesu FT990");

void Add2UIFreqList(uint32_t freq) {
  char buffer[30];
  float f = freq;
  f = f / 1e6;
  sprintf(buffer, "%.3f", f);
  gslc_ElemXListboxAddItem(&m_gui, m_pElemListboxFreq, buffer);
  //Serial.printf("Add Freq: %d\r\n",freq);
}

void Add2UIWifiList(const char* ssid, int32_t rssi) {
  char buffer[50];
  memset(buffer, 0, 49);
  sprintf(buffer, "%s", ssid);
  gslc_ElemXListboxAddItem(&m_gui, m_pElemListboxWifi, buffer);
}
void Add2UIRadioList(const char* RadioType) {
  gslc_ElemXListboxAddItem(&m_gui, m_pElemListbox1_3, RadioType);
}
void SelectFreqItem(int16_t nID) {
  FreqSelected = nID;
  char acTxt[MAX_STR];
  uint32_t freq = 0;
  gslc_ElemXListboxGetItem(&m_gui, m_pElemListboxFreq, FreqSelected, acTxt, MAX_STR);
  freq = atof(acTxt) * 1e6;
  uint32_t pos = ML_ANT[mlat_act_setting.last_actived_ant].FindFreqFromList(freq);
  Serial.printf("Freq selected: %d, pos %d\r\n", freq, pos);

  sprintf(acTxt, "%d", pos);
  //p_ElemStepsCur
  gslc_ElemSetTxtStr(&m_gui, p_ElemStepsCur, acTxt);
  //p_ElemSteps

  //               ML_ANT[mlat_act_setting.last_actived_ant].GetPostionInformation(&posi, i);
}

void SelectWifiItem(int16_t nID) {
  WiFiSelected = nID;
}
void ShowTipMsg(const char* msg) {
  gslc_ElemSetTxtStr(&m_gui, m_pElemTipInfo, msg);
}
void UpdateIpAddr(const char* ipaddr, bool Valid) {
  gslc_ElemSetTxtStr(&m_gui, m_pElemIPAddr0, ipaddr);
  if (Valid) {
    gslc_ElemSetTxtCol(&m_gui, m_pElemIPAddr0, GSLC_COL_GREEN_DK2);
  } else {
    gslc_ElemSetTxtCol(&m_gui, m_pElemIPAddr0, GSLC_COL_GRAY_DK3);
  }
}
void ShowPageID(const char* ID) {
}
void DoOTAUpgrade() {
  char msgbuf[300];
  memset(msgbuf, 0, 300);
  strcat(msgbuf, "Please open the URL:\n");
  strcat(msgbuf, "http://");
  strcat(msgbuf, gslc_ElemGetTxtStr(&m_gui, m_pElemIPAddr0));
  strcat(msgbuf, "\n");
  strcat(msgbuf, "Then follow the instruction to upgrade firmware via WiFi\n");
  strcat(msgbuf, "The device will automatic restart after upgrade.");
  DoWebUpdate();
  OTAModeEnabled = true;
  MsgBox(msgbuf);
}

void ShowWifiSSID(const char* ssid) {
  char acTxt[30];
  //strcpy(acTxt,ssid);
  sprintf(acTxt, "%s", ssid);
  if (strlen(acTxt) > 13) acTxt[14] = 0;
  gslc_ElemSetTxtStr(&m_gui, m_pElem_SSID0, acTxt);
}
void SetChartTitle(const char* title) {
  gslc_ElemSetTxtStr(&m_gui, m_pElemChartTitle, title);
}

void listFilesInDir(File dir, int numTabs) {
  while (true) {

    File entry = dir.openNextFile();
    if (!entry) {
      // no more files in the folder
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      listFilesInDir(entry, numTabs + 1);
    } else {
      // display zise for file, nothing for directory
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
void ShowFSInfo() {
  unsigned int totalBytes = SPIFFS.totalBytes();
  unsigned int usedBytes = SPIFFS.usedBytes();

  Serial.println("===== File system info =====");

  Serial.print("Total space:      ");
  Serial.print(totalBytes);
  Serial.println("byte");

  Serial.print("Total space used: ");
  Serial.print(usedBytes);
  Serial.println("byte");

  Serial.println();

  // Open dir folder
  File dir = SPIFFS.open("/");
  // List file at root
  listFilesInDir(dir, 1);
}
//HARD_CONFIG_DATA    mlat_cfg_data;
//SYSTEM_CFG          mlat_act_setting;
void LoadCommonConfiguration() {
  int flen;
  int size0, size1,size2;
  size0 = sizeof(HARD_CONFIG_DATA);
  size1 = sizeof(SYSTEM_CFG);
  size2= sizeof(FREQ_CAL_OFFSET);
  memset(&mlat_cfg_data, 0, size0);
  memset(&mlat_act_setting, 0, size1);
  memset(&FreqCalPara,0,size2);

  char* pathcfg0 = "/hardwareconfig.dat";
  char* pathcfg1 = "/activeconfig.dat";
  
  char *pathFreqCal="/counter_cal.dat";

  bool load_ok = false;

  Serial.printf("load common config, %d, %d\n", size0, size1);

  File file = SPIFFS.open(pathcfg0, FILE_READ);
  if (!file) {
    Serial.printf("- failed to open file %s for reading\n", pathcfg0);
    //return ;
  } else if (!file.isDirectory()) {
    flen = file.size();
    if (flen >= size0) {
      file.read((uint8_t*)&mlat_cfg_data, size0);
      load_ok = true;
    } else {
      Serial.printf("file size is not right %d,%d:\n", flen, size0);
    }
    file.close();
  } else {
    //no file found, it means this is a new machine.
    //set default....

    mlat_cfg_data.AntSWType = ONE_CHANNEL;
    mlat_cfg_data.support_freq_measurement = true;
    mlat_cfg_data.support_stall_detection = true;
  }

  file = SPIFFS.open(pathcfg1, FILE_READ);
  if (!file) {
    Serial.printf("- failed to open file %s for reading\n", pathcfg1);
    return;
  } else if (!file.isDirectory()) {
    flen = file.size();
    if (flen >= size1) {
      file.read((uint8_t*)&mlat_act_setting, size1);
      load_ok = true;
    } else {
      Serial.printf("file size is not right %d,%d:\n", flen, size1);
    }
    file.close();
  } else {
    mlat_act_setting.last_actived_ant = 0;  //TRX_UNKNOWN
    mlat_act_setting.PowerDispMode = 0;     //in W /dbm
    mlat_act_setting.SWRTuneThreshold = 1.5;
    mlat_act_setting.LastSelectedTRX = TRX_UNKNOWN;
  }
  
      FreqCalPara.K=1;
      FreqCalPara.B=0;

  file=SPIFFS.open(pathFreqCal,FILE_READ);
  if (file)
  {
      flen=file.size();
      if (flen>=size2)
        file.read((uint8_t*)&FreqCalPara,size2);
  }
  file.close();
  Serial.printf("Freq counter K: %f, B: %f\r\n",FreqCalPara.K,FreqCalPara.B);

}
void ShowFreqSrcState(bool IsOn) {
  if (IsOn) {
    gslc_ElemSetCol(&m_gui, m_pElemRBFreqSrc, GSLC_COL_GRAY, GSLC_COL_GREEN, GSLC_COL_BLACK);

  } else
    gslc_ElemSetCol(&m_gui, m_pElemRBFreqSrc, GSLC_COL_GRAY, GSLC_COL_RED, GSLC_COL_BLACK);
}

void ShowCommonConfig() {
  //m_pElem_TrxName,m_pElemAntIndex,m_pElem_SSID0,m_pElemIPAddr0
  char acTxt[20];
  sprintf(acTxt, "%s", GetTrxDeviceName(mlat_act_setting.LastSelectedTRX));
  gslc_ElemSetTxtStr(&m_gui, m_pElem_TrxName, acTxt);

  //m_pElemOldTRX
  gslc_ElemSetTxtStr(&m_gui, m_pElemOldTRX, acTxt);

  sprintf(acTxt, "%d", mlat_act_setting.last_actived_ant + 1);
  gslc_ElemSetTxtStr(&m_gui, m_pElemAntIndex, acTxt);
  //m_pElemSSIDConf227_231,m_pElemPSKConf229_233

  gslc_ElemSetTxtStr(&m_gui, m_pElemSSIDConf227_231, mlat_act_setting.WifiSSID);
  gslc_ElemSetTxtStr(&m_gui, m_pElemPSKConf229_233, mlat_act_setting.WifiPsk);

  gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt259_261, versionstring());

  WifiInformationValid = (strlen(mlat_act_setting.WifiSSID) && strlen(mlat_act_setting.WifiPsk));
}
bool SaveFreqCalData()
{
   bool file_ok = false;
   char *pathFreqCal="/counter_cal.dat";
 
  File file = SPIFFS.open(pathFreqCal, FILE_WRITE);
  if (!file) {
    Serial.printf("- failed to open file %s for writing\n", pathFreqCal);
    return file_ok;
  } else if (!file.isDirectory()) {
    file.write((uint8_t*)&FreqCalPara, sizeof(FREQ_CAL_OFFSET));
    file.close();
  }
  return true;
}
bool SaveCommonConfiguration() {
  bool file_ok = false;

  char* pathcfg0 = "/hardwareconfig.dat";
  char* pathcfg1 = "/activeconfig.dat";

  File file = SPIFFS.open(pathcfg0, FILE_WRITE);
  if (!file) {
    Serial.printf("- failed to open file %s for writing\n", pathcfg0);
    return file_ok;
  } else if (!file.isDirectory()) {
    file.write((uint8_t*)&mlat_cfg_data, sizeof(HARD_CONFIG_DATA));
    file.close();
  }

  file = SPIFFS.open(pathcfg1, FILE_WRITE);
  if (!file) {
    Serial.printf("- failed to open file %s for writing\n", pathcfg1);
    return file_ok;
  } else if (!file.isDirectory()) {
    file.write((uint8_t*)&mlat_act_setting, sizeof(SYSTEM_CFG));
    file.close();
  }
  Serial.printf("common configuration file saved completed\r\n");
  return true;
}
void LoadSWROffsetData() {
  //SWR_METER_OFFSET  SWRMeterParas;
  int flen;
  int size0;
  size0 = sizeof(SWR_METER_OFFSET);

  memset(&SWRMeterParas, 0, size0);

  char* pathcfg0 = "/swrmeter.dat";

  bool load_ok = false;

  Serial.printf("load swr meter config, %d \n", size0);

  File file = SPIFFS.open(pathcfg0, FILE_READ);
  if (!file) {
    Serial.printf("- failed to open file %s for reading\n", pathcfg0);
    //return ;
  } else if (!file.isDirectory()) {
    flen = file.size();
    if (flen >= size0) {
      file.read((uint8_t*)&SWRMeterParas, size0);
      load_ok = true;
    } else {
      Serial.printf("file size is not right %d,%d:\n", flen, size0);
    }
    file.close();
  } else {
    //no file found, it means this is a new machine.
    //set default....
    SetSwrDefault();
  }
  //fill
}

void SetSwrDefault() {
  SWRMeterParas.FWDOffset.ZeroOffset = 230;
  SWRMeterParas.FWDOffset.PowerThreshold = -35;
  SWRMeterParas.REFOffset.ZeroOffset = 265;
  SWRMeterParas.REFOffset.PowerThreshold = -35;
}

void SaveSWROffsetData() {
  bool file_ok = false;

  char* pathcfg0 = "/swrmeter.dat";

  File file = SPIFFS.open(pathcfg0, FILE_WRITE);
  if (!file) {
    Serial.printf("- failed to open file %s for writing\n", pathcfg0);
    return;
  } else if (!file.isDirectory()) {
    file.write((uint8_t*)&SWRMeterParas, sizeof(SWR_METER_OFFSET));
    file.close();
  }
}
void LoadSWRData2UI() {

  SetCtrlValueInt(m_pElemVal17_23, SWRMeterParas.FWDOffset.ZeroOffset);
  SetCtrlValueInt(m_pElemVal17_18_24, SWRMeterParas.REFOffset.ZeroOffset);
  SetCtrlValueInt(m_pElemVal17_19_25, SWRMeterParas.FWDOffset.PowerThreshold);
  SetCtrlValueInt(m_pElemVal17_20_26, SWRMeterParas.REFOffset.PowerThreshold);
}
void SaveSWRDataFromUI() {
  SWRMeterParas.FWDOffset.ZeroOffset = GetCtrlValueInt(m_pElemVal17_23);
  SWRMeterParas.REFOffset.ZeroOffset = GetCtrlValueInt(m_pElemVal17_18_24);
  SWRMeterParas.FWDOffset.PowerThreshold = GetCtrlValueInt(m_pElemVal17_19_25);
  SWRMeterParas.REFOffset.PowerThreshold = GetCtrlValueInt(m_pElemVal17_20_26);
  SaveSWROffsetData();
}
void ShowPresetFreqList() {
  /*
          MaxPresetFreqs=ML_ANT[which_ant].GetTunedPositionCount();
         MaxPresetPages=MaxPresetFreqs / 4;
         CurrentPresetPage=0;
    */

  char captions[20];
  uint8_t i;
  uint8_t st_index = CurrentPresetPage * 4;
  uint8_t ed_index;
  float f;
  //64,64,64 //invalid color.
  gslc_tsElemRef* BtnList[] = { m_pElemPF0, m_pElemPF1, m_pElemPF2, m_pElemPF3 };
  ed_index = st_index + 4;
  PositionInfomation posi, posi_0;
  uint32_t pos_0;

  //resprintf("MaxFreqs: %d, Current Page: %d,%d,%d\r\n",MaxPresetFreqs,CurrentPresetPage,st_index,ed_index);

  if (CurrentPresetPage == MaxPresetPages) {
    gslc_ElemSetClickEn(&m_gui, m_pElemNextPage, false);
    gslc_ElemSetCol(&m_gui, m_pElemNextPage, GSLC_COL_BLUE_DK2, GSLC_COL_GRAY_DK1, GSLC_COL_BLUE_DK1);

  } else {
    gslc_ElemSetClickEn(&m_gui, m_pElemNextPage, true);
    gslc_ElemSetCol(&m_gui, m_pElemNextPage, GSLC_COL_BLUE_DK2, GSLC_COL_BLUE_DK4, GSLC_COL_BLUE_DK1);
  }
  if (CurrentPresetPage > 0) {
    gslc_ElemSetClickEn(&m_gui, m_pElemPrevPage, true);
    gslc_ElemSetCol(&m_gui, m_pElemPrevPage, GSLC_COL_BLUE_DK2, GSLC_COL_BLUE_DK4, GSLC_COL_BLUE_DK1);

  } else {
    gslc_ElemSetClickEn(&m_gui, m_pElemPrevPage, false);
    gslc_ElemSetCol(&m_gui, m_pElemPrevPage, GSLC_COL_BLUE_DK2, GSLC_COL_GRAY_DK1, GSLC_COL_BLUE_DK1);
  }

  if (mlat_act_setting.LastFrequencySelected > 0) {
    pos_0 = ML_ANT[mlat_act_setting.last_actived_ant].FindFreqFromList(mlat_act_setting.LastFrequencySelected);
  } else
    pos_0 = 0;

  for (i = st_index; i < ed_index; i++) {
    if (i > MaxPresetFreqs - 1) {
      sprintf(captions, "+");
      gslc_ElemSetCol(&m_gui, BtnList[i - st_index], GSLC_COL_BLUE_DK2, GSLC_COL_GRAY_DK2, GSLC_COL_BLUE_DK1);

    } else {
      ML_ANT[mlat_act_setting.last_actived_ant].GetPostionInformation(&posi, i);
      f = posi.PresetFrequency;
      sprintf(captions, "%.3f", f / 1e6);

      if ((posi.PresetFrequency == mlat_act_setting.LastFrequencySelected) && (posi.StepperPosition == pos_0) && (pos_0))  //CurrentSelectedFrequency
        gslc_ElemSetCol(&m_gui, BtnList[i - st_index], GSLC_COL_GRAY_DK2, GSLC_COL_GREEN_DK3, GSLC_COL_BLUE_DK1);
      else
        gslc_ElemSetCol(&m_gui, BtnList[i - st_index], GSLC_COL_GRAY_DK2, GSLC_COL_RED_DK2, GSLC_COL_BLUE_DK1);
    }

    gslc_ElemSetTxtStr(&m_gui, BtnList[i - st_index], captions);
  }

  //gslc_Update(&m_gui);
}
void ProcessPresetButton(uint8_t index) {
  char captions[20];
  gslc_tsElemRef* BtnList[] = { m_pElemPF0, m_pElemPF1, m_pElemPF2, m_pElemPF3 };

  //gslc_Update(&m_gui);

  //Serial.printf("Preset Button %d pressed\r\n",index);
  //return ;
  if (index >= 0 && index <= 3) {
    //captions[0]=gslc_ElemGetTxtStr(&m_gui,BtnList[index]);
    sprintf(captions, "%s", gslc_ElemGetTxtStr(&m_gui, BtnList[index]));
    if (strcmp(captions, "+") == 0) {

      PageShow(E_PG_NUMKEYPAD);

    } else {
      uint32_t freq = atof(captions) * 1e6;
      Serial.printf("move to frequency...%s Mhz\r\n", captions);
      // Move2RightPositionByFreq(freq);
      SetUICommand("fmove %d", freq);
    }
  }
}
void ShowBusyBox() {
  PageShow(E_PG_POP_PRG);
  old_busy_prg_val = 0;
  tmr_watch_count = millis();
}
void RefreshBusyBox() {
  if (gslc_GetPageCur(&m_gui) != E_PG_POP_PRG) return;
  old_busy_prg_val++;
  if (old_busy_prg_val > 100) old_busy_prg_val = 0;
  uint32_t elasped = (millis() - tmr_watch_count) / 1000;
  char acTxt[10];
  sprintf(acTxt, "%d", elasped);
  gslc_ElemSetTxtStr(&m_gui, m_pElemXRingGauge1, acTxt);
  gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemXRingGauge1, old_busy_prg_val);
}
void HideBusyBox() {
  PageHide(E_PG_POP_PRG);
}
void PageShow(uint16_t pageid) {
  uint16_t page = gslc_GetPageCur(&m_gui);

  if (page == pageid) return;

  if (page != E_PG_MAIN) PageStacks.push_back(page);
  gslc_SetPageCur(&m_gui, pageid);
}
void PageHide(uint16_t pageid) {
  if ((gslc_GetPageCur(&m_gui) == pageid)
      && (pageid != E_PG_MAIN)) {
    unsigned short pos = PageStacks.size() - 1;
    uint16_t page = PageStacks[pos];

    if (page != E_PG_MAIN) PageStacks.pop_back();
    gslc_SetPageCur(&m_gui, page);
  }
}
void LoadAntennaDataOnUI(uint8_t which_ant) {
  //ant>=0 and ant_<=3
  PositionInfomation posi;
  Serial.printf("Load antenna parameters: %d\r\n", which_ant);
  if (which_ant >= 0 && which_ant <= 3) {

    if (ML_ANT[which_ant].Initialize(which_ant)) {
      //now config motor with motor parameters.
      //MotorRunningConfig;
      MaxMotorMoveSteps = ML_ANT[which_ant].GetTotalSteps();
      CurrentMotorPosition = ML_ANT[which_ant].GetMotorPosition();

      MaxPresetFreqs = ML_ANT[which_ant].GetTunedPositionCount();
      MaxPresetPages = MaxPresetFreqs / 4;
      CurrentPresetPage = 0;
      //uint16_t MaxPresetPages=0;
      uint8_t i;
      ResetFreqListBox();
      for (i = 0; i < MaxPresetFreqs; i++) {
        if (ML_ANT[which_ant].GetPostionInformation(&posi, i)) Add2UIFreqList(posi.PresetFrequency);
      }
      ShowPresetFreqList();
    } else {
      Serial.printf("The antenna %d was not configed yet!\r\n", which_ant);
    }
    if (ML_ANT[which_ant].GetMotorParameters(&MotorRunningConfig)) {
      //show default parameters...
      Serial.printf("Motor running parameters\r\n");
      Serial.printf(" RMS Current: %d\r\n", MotorRunningConfig.MaxCurrent);
      Serial.printf(" Stall TH:  %d\r\n", MotorRunningConfig.StallTH);
      Serial.printf(" running interval(1/f): %d\r\n", MotorRunningConfig.min_delay_us);
      Serial.printf(" running microsteps: %d\r\n", MotorRunningConfig.HomeDetectionMicroStep);
      //m_pElemSeekbarRMS,m_pElemSeekbarSPEED,m_pElemSeekbarSTALL
      gslc_ElemXSeekbarSetPos(&m_gui, m_pElemSeekbarRMS, MotorRunningConfig.MaxCurrent);
      gslc_ElemXSeekbarSetPos(&m_gui, m_pElemSeekbarSPEED, MotorRunningConfig.min_delay_us);
      gslc_ElemXSeekbarSetPos(&m_gui, m_pElemSeekbarSTALL, MotorRunningConfig.StallTH);

      char acTxt[10];
      sprintf(acTxt, "%d", MotorRunningConfig.MaxCurrent);
      gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt250, acTxt);

      sprintf(acTxt, "%d", MotorRunningConfig.min_delay_us);
      gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt250_251, acTxt);

      sprintf(acTxt, "%d", MotorRunningConfig.StallTH);
      gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt250_252, acTxt);

      SetMotorCurrent(MotorRunningConfig.MaxCurrent);
      SetStallTH(MotorRunningConfig.StallTH);
    }
  } else
    Serial.printf("Antenna index %d is out of range\r\n", which_ant);
}

long getint(char* str) {
  int base = 10;
  if (strstr(str, "0x") || strstr(str, "0X")) base = 16;

  return strtol(str, NULL, base);
}


void SetUICommand(char* format, ...) {
  va_list aptr;
  va_start(aptr, format);
  vsprintf(rx_buffer, format, aptr);
  va_end(aptr);
  StringCommandInput = UICMD_INPUT;
}

int MsgBox(const char* Msg) {

  //gslc_ElemXTextboxAdd(&m_gui,pElemTextbox,(char*)"Welcome\n");
  //gslc_ElemXTextboxReset(&m_gui,m_pElemTextbox1);
  MsgBoxOK=false;
  gslc_ElemXTextboxAdd(&m_gui, m_pElemMsgBoxText, (char*)Msg);
  PageShow(E_PG_MSBOX);

  while(!MsgBoxOK)
  {
    gslc_Update(&m_gui);
    usleep(1000);
  }
  //gslc_Update(&m_gui);
  return 0;
}
int DoFreqScan(char** args, uint8_t argc) {

  unsigned long Fstart = atof(args[1]) * 100;
  unsigned long Fend = atof(args[2]) * 100;
  unsigned long FStep = 0;
  if (argc < 4)
    FStep = (Fend - Fstart) / 100;
  else
    FStep = atof(args[3]) * 100;


  resprintf("do frequency scan from %d to %d, step in %d\n", Fstart, Fend, FStep);

  return ScanBestFrequencyForCurrentPosition(Fstart, Fend, FStep);
}

void DoFreqScanOnScreen() {
  unsigned long Fstart;
  unsigned long Fend;
  unsigned long FStep;

  Fstart = atof(gslc_ElemGetTxtStr(&m_gui, m_pElemValFreq)) * 1e8;
  Fend = atof(gslc_ElemGetTxtStr(&m_gui, m_pElem_MotorPos)) * 1e8;
  FStep = atof(gslc_ElemGetTxtStr(&m_gui, m_pElem_MotorPos213)) * 1e5;

  //Switch2BFOChan();
  // Serial.printf("do freq scan ...%d, %d, %d\r\n",Fstart,Fend,FStep);
  ScanBestFrequencyForCurrentPosition(Fstart, Fend, FStep);
  return;
}

/*
 * do frequency sweep at a fixed Capacitor position, try to find the matched frequency with minimum SWR. 
*/
int ScanBestFrequencyForCurrentPosition(unsigned long StartFrequency,
                                        unsigned long StopFrequency,
                                        unsigned long StepFreq) {

  unsigned long freq;
  unsigned long freqstep;
  if (StopFrequency <= StartFrequency) {
    resprintf("Stop frequency must great than start frequency!\n");
    return 0;
  }

  float fwd, rev;
  float swr;
  float MinSWR = 9999.0f;
  float MaxSWR = 0;
  int16_t nY;
  unsigned long BestFreq = 0;

  uint32_t st_tick = millis();
  uint32_t end_tick = 0;


  float x0 = StartFrequency / 1e8;
  float x1 = StopFrequency / 1e8;
  float xinc = (x1 - x0) / 5;

  float yl = 1;
  float yh = 10;
  float yinc = 1;
  bool disp = true;
  bool update1 = true;
  float f;
  float* swrv = NULL;

  Taskrunning = true;


  swrfindChartInit();


  SetFG_Level(3);

  TurnFGOn();


  freqstep = (StopFrequency - StartFrequency) / StepFreq;
  //Serial.printf("%.2f-%.2f Mhz ,steps: %d\n",x0,x1,freqstep);
  swrv = new float[freqstep + 1];



  for (int i = 0; i < freqstep; i++) {
    freq = StartFrequency + (StepFreq * i);
    f = freq / 1e8;
    SetFG_Frequency(freq);
    ResetSWR();

    swr = GetSWRValue(20, &fwd, &rev);

    swrv[i] = swr;
    if (i % 5 == 0) gslc_Update(&m_gui);
    //Serial.printf("SWR:%.3f,FWD:%.3f, REV:%.3f\r\n",swr,fwd,rev);
    if (swr > 0 && swr < MinSWR) {
      MinSWR = swr;
      BestFreq = freq;
    }
    if (swr > MaxSWR) MaxSWR = swr;
  }

  //5-10-15-20-25-30-35-
  yh = ceil(MaxSWR * 1.2);

  uint8_t l0 = (uint8_t)yh / 5;
  uint8_t l1 = (uint8_t)yh % 5;
  if (l1) yh = (l0 + 1) * 5;

  yinc = (yh - yl) / 10;

  /*
      static double old_x0=0;
      static double old_x1=0;
      static double old_xinc=0;
      static double old_yl=0;
      static double old_yh=0;
      static double old_yinc=0;
      bool redraw=false;
      redraw =((old_x0!=x0) |  (old_x1!=x1)   | (old_yl != yl) | (old_yh !=yh));
      old_x0=x0;
      old_x1=x1;
      old_yl=yl;
      old_yh=yh;
      */
  if (gslc_GetPageCur(&m_gui) == E_PG_SWR_CHART) {
    mChart.Clear();
    mChart.GraphFrame(x0, x1, xinc,
                      yl, yh, yinc,
                      "VSWR Scan", "MHz", "VSWR");
    for (int i = 0; i < freqstep; i++) {
      freq = StartFrequency + (StepFreq * i);
      f = freq / 1e8;
      mChart.UpdateTrace(f, swrv[i], update1, RED);
      //  if (!SwrMeterMode)        break;
    }
    mChart.MarkPeakMin();
  }



  end_tick = millis();



  SetFG_Frequency(BestFreq);


  //resprintf("minimum swr=%.2f @ Frequency %u within %d ms\n",MinSWR,BestFreq,end_tick-st_tick);
  // Serial.printf("Find Best Frequency %u with swr=%.2f\n",BestFreq,MinSWR);
  // now tune to here...


  delete[] swrv;
  swrv = NULL;
  //TurnFGOff();
  return 0;
}
void swrfindChartInit() {

  PageShow(E_PG_SWR_CHART);
  //gslc_Update(&m_gui);
  static bool initialized = false;
  if (initialized) return;
  mChart.InitObject(&m_gui, m_pElemGraph_FreqScan);
  //TBD add clear screen function...
  initialized = true;
}
void UpdateFreqSource(uint8_t src) {
  char* disp_src[] = { "TRX", "BFO0", "BFO1", "BFO2" };
  if (src > 0)
    clk_src = 1;
  else
    clk_src = 0;

  if (clk_src == 1)  //Internal
  {
    gslc_ElemSetCol(&m_gui, m_pElemSigSrc146, GSLC_COL_BLUE_DK2, GSLC_COL_BLUE_DK1, GSLC_COL_RED);
    gslc_ElemSetTxtStr(&m_gui, m_pElemSigSrc146, disp_src[src]);
  } else {
    gslc_ElemSetCol(&m_gui, m_pElemSigSrc146, GSLC_COL_BLUE_DK2, GSLC_COL_RED, GSLC_COL_BLUE_DK1);
    gslc_ElemSetTxtStr(&m_gui, m_pElemSigSrc146, disp_src[0]);
  }
}

int SetFrequencyGenerator(char** args, uint8_t argc) {
  long freq = atof(args[1]) * 100;
  uint8_t level;
  if (argc > 2) {
    level = getint(args[2]);
  } else
    level = 3;
  if (freq <= 0) {
    TurnFGOff();
    resprintf("turn off frequency generator");
  } else {
    resprintf("set FG output to %d hz\n", freq);
    SetFG_Frequency(freq);
    SetFG_Level(level);
    TurnFGOn();
  }

  resprintf("set BFO frequency to %d\n", freq);

  return 0;
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  // String inputString="";
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read();
    switch (inChar) {
      case 32 ... 127:
        rx_buffer[current_rx_ptr] = inChar;
        current_rx_ptr++;
        break;
      case 10:
        rx_buffer[current_rx_ptr] = 0;
        StringCommandInput = SERIAL_INPUT;
        break;
      case 13:
        StringCommandInput = SERIAL_INPUT;
        break;
      default:
        break;
    }
    if (current_rx_ptr >= MAX_MSG_LENGTH) {
      //buffer overflow...
      Serial.printf("Serial Buffer overflow!\n");
      current_rx_ptr = 0;
    }
  }
}
const char* versionstring() {
  //  Serial.printf("MLAT22 %d.%d.%d Compiled on:  %s %s\n",MAJOR_VER,MINOR_VER,REVISION,__DATE__,__TIME__);
  static char version[100];
  sprintf(version, "MLAT22 %d.%d.%d Compiled on:  %s %s", MAJOR_VER, MINOR_VER, REVISION, __DATE__, __TIME__);
  return version;
}

int ShowVersion(char** args, uint8_t argc) {

  resprintf("%s\n", versionstring());

  return 0;
}
void ResetUartMsg() {
  memset(rx_buffer, 0, MAX_MSG_LENGTH);
  current_rx_ptr = 0;
  StringCommandInput = NO_COMMAND;
}
int testmsg(char** args, uint8_t argc) {
  memset(MsgBoxBuffer,0,512);
  strcpy(MsgBoxBuffer,args[1]);
  MsgBox(MsgBoxBuffer);
  return 0;
}
int switchoff(char** args, uint8_t argc) {

  resprintf("turn device off\n");

  SwitchPowerOff();

  return 0;
}
int DoSWRSpeedTest(char** args, uint8_t argc) {
  uint8_t buffer_size = 100;
  uint8_t delta = 10;
  if (argc >= 2)
    buffer_size = getint(args[1]);
  if (argc >= 3)
    delta = getint(args[2]);
  SWREva(buffer_size, delta);
  return 0;
}
#define CALIBRATION_FILE0 "/TouchCalData3"
void touch_calibrate() {
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  TFT_eSPI m_disp = *(TFT_eSPI*)gslc_GetDriverDisp(&m_gui);

  m_disp.fillScreen(TFT_BLACK);
  m_disp.setCursor(20, 120);
  m_disp.setTextFont(2);
  m_disp.setTextSize(1);

  m_disp.setTextColor(TFT_GREEN, TFT_BLACK);
  m_disp.println("System starting...");
  // check file system exists



  //m_disp.println("Touch corners as indicated");
  // check if calibration file exists and size is correct
  if (SPIFFS.exists(CALIBRATION_FILE0)) {

    File f = SPIFFS.open(CALIBRATION_FILE0, "r");
    if (f) {
      if (f.readBytes((char*)calData, 14) == 14)
        calDataOK = 1;
      f.close();
    }
  }

  if (calDataOK) {
    // calibration data valid
    m_disp.setTouch(calData);
  } else {
    // data not valid so recalibrate
    m_disp.fillScreen(TFT_BLACK);
    m_disp.setCursor(20, 0);
    m_disp.setTextFont(2);
    m_disp.setTextSize(1);
    m_disp.setTextColor(TFT_WHITE, TFT_BLACK);

    m_disp.println("Touch corners as indicated");

    m_disp.setTextFont(1);
    m_disp.println();

    m_disp.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    m_disp.setTextColor(TFT_GREEN, TFT_BLACK);
    m_disp.println("Calibration complete!");

    // store data
    File f = SPIFFS.open(CALIBRATION_FILE0, "w");
    if (f) {
      f.write((const unsigned char*)calData, 14);
      f.close();
    }
  }
}

int touchcal(char** args, uint8_t argc) {

  resprintf("do touch screen calibration\n");

  touch_calibrate();
  return 0;
}
int readio(char** args, uint8_t argc) {
  uint8_t pin = atoi(args[1]);
  if (pin < 40)
    resprintf("PIN: %d state: %d\r\n", pin, digitalRead(pin));
  else {
    resprintf("IOEXPIN: %d->%d\n", pin, IOEXRead(pin - 40));
  }
  return 0;
}
int readadc(char** args, uint8_t argc) {
  uint8_t pin = atoi(args[1]);
  resprintf("PIN %d  %d mV\r\n", pin, analogReadMilliVolts(pin));
  return 0;
}
int setbfo(char** args, uint8_t argc) {
  uint8_t mode = atoi(args[1]);
  if (mode) {
    uint64_t freq = 6e6;
    uint8_t power = 0;
    if (argc > 2)
      freq = (uint64_t)atof(args[2])*100;
    if (argc == 4)
      power = atoi(args[3]);

    resprintf("Set freq: %fHz, Power: %d\n", atof(args[2]), power);
    SetFG_Frequency(freq  );
    SetFG_Level(power);

    TurnFGOn();
  } else {
    TurnFGOff();
  }

  return 0;
}
int switchbfo(char** args, uint8_t argc) {
  uint8_t sw = atoi(args[1]);
  if (sw > 0) {
    resprintf("switch to BFO channel\n");
    Switch2BFOChan();
  }

  else {
    resprintf("switch to TRX channel\n");
    Switch2TRXChan();
  }
  return 0;
}
int readswr(char** args, uint8_t argc) {
  float fwd_volt = (float)analogReadMilliVolts(36) - 282;
  float rev_volt = (float)analogReadMilliVolts(39) - 268;
  float fwd_in_dbm = fwd_volt / 25;
  float rev_in_dbm = rev_volt / 25;
  if (fwd_in_dbm > 0.0001f && rev_in_dbm > 0.0001f) {
    float swr = (1 + sqrtf(rev_in_dbm / fwd_in_dbm)) / (1 - sqrtf(rev_in_dbm / fwd_in_dbm));
    Serial.printf("fwd volt: %.2f, rev volt: %.2f\n", fwd_volt, rev_volt);
    Serial.printf("SWR: %.2f,   fwd: %.2f dbm, rev: %.2f dbm\n", swr, fwd_in_dbm, rev_in_dbm);

  } else {
    Serial.printf("invalid value\n");
  }


  return 0;
}
int writeioex(char** args, uint8_t argc) {
  uint8_t bit = atoi(args[1]);
  uint8_t dat = atoi(args[2]);
  IOEXWrite(bit, dat);
  return 0;
}
int move(char** args, uint8_t argc) {
  int32_t steps = getint(args[1]);
  uint32_t delays = 150;  //
  if (argc > 2) delays = getint(args[2]);
  MoveMotorInSteps(steps, delays);
  CurrentMotorPosition+=steps;
   UpdateMotorPosition(true);
  return 0;
}
int freqcounterselect(char** args, uint8_t argc) {
  //move to seeking a minim swr.
  uint8_t chan = getint(args[1]);
  SelectFreqChan((FC_CHAN_DEF)chan);

  return 0;
}
int setms(char** args, uint8_t argc) {
  uint8_t ms = getint(args[1]);
  ConfigStepperMicroStep(ms);
  return 0;
}
int setstall(char** args, uint8_t argc) {
  uint8_t stall_v = getint(args[1]);
  resprintf("stall th: %d\r\n", stall_v);
  MotorRunningConfig.StallTH = stall_v;
  ML_ANT[mlat_act_setting.last_actived_ant].SaveMotorParameters(&MotorRunningConfig);
  SetStallTH(stall_v);
  return 0;
}
int set_motor_rms(char** args, uint8_t argc) {
  uint16_t rms = getint(args[1]);
  if (rms <= 2200) {
    resprintf("set motor rms current: %d\r\n", rms);
    MotorRunningConfig.MaxCurrent = rms;
    ML_ANT[mlat_act_setting.last_actived_ant].SaveMotorParameters(&MotorRunningConfig);

    SetMotorCurrent(rms);
  } else {
  }


  return 0;
}
int showmotstat(char** args, uint8_t argc) {
  ShowMotorDriverStatus();
  return 0;
}
int moten(char** args, uint8_t argc) {
  uint8_t mode = getint(args[1]);
  MotorEnControl(mode);
  return 0;
}
int setmotref(char** args, uint8_t argc) {
  bool UseExt = getint(args[1]);
  SetMotorRefSource(UseExt);
  return 0;
}
int setmotoff(char** args, uint8_t argc) {
  uint8_t t_off = getint(args[1]);
  SetTOff(t_off);
  return 0;
}
int setclksrc(char** args, uint8_t argc) {
  uint8_t src = getint(args[1]);
  SelectFrequencyChan(src);
  return 0;
}
int findhome(char** args, uint8_t argc) {
  char* msg = "This operation will re-map motor moving range.\n You have to reset all pre-defined freqs.";
  MsgBox(msg);
  
  ClearAllFreqs(mlat_act_setting.last_actived_ant);  
  FindMovingRanges();
  //MaxMotorMoveSteps
  memset(MsgBoxBuffer,0,512);
  sprintf(MsgBoxBuffer,"Task completed \n, Please clear and re-map all freqs.");
  MsgBox(MsgBoxBuffer);
  return 0;
}
bool FindMovingRanges() {
  uint32_t totalsteps0 = 0;
  uint32_t totalsteps1 = 0;

  resprintf("try to find motor limit range, it maybe take several minutes,please be patient.. \n");
  //ShowBusyBox();

  uint32_t ms0 = millis();
  // now setup thread message
  double x0, x1, xinc;
  double y0, y1, yinc;
  bool disp = true;
  bool update1 = true;

  x0 = 0;
  x1 = 12000;
  xinc = x1 / 10;
  y0 = 0;
  y1 = 2.0;
  yinc = 0.2;

  swrfindChartInit();
  mChart.Clear();
  mChart.GraphFrame(x0, x1, xinc, y0, y1, yinc, "Moving Range Dect", "Step", "STALL");

  FindHomePosition(&totalsteps0, &totalsteps1);


  MaxMotorMoveSteps = totalsteps1;
  CurrentMotorPosition = 0;

  resprintf("%d steps in dir 0, %d steps in dir 1\r\n", totalsteps0, totalsteps1);
  resprintf("set max move steps to %d\r\n", MaxMotorMoveSteps);

  ML_ANT[mlat_act_setting.last_actived_ant].SaveTotalSteps(MaxMotorMoveSteps);
  ML_ANT[mlat_act_setting.last_actived_ant].SaveMotorPostion(CurrentMotorPosition);
  PageHide(E_PG_SWR_CHART);

  //HideBusyBox();
  return 0;
}

int dirmove(char** args, uint8_t argc) {
  uint32_t steps = 0;
  int8_t dir = getint(args[1]);
  MoveToLimitPosition(dir, &steps);
  resprintf("completed in %d steps\r\n", steps);
  return 0;
}
int findswr(char** args, uint8_t argc) {
  float bfofreq = atof(args[1]);
  SeekPosForFreq((uint32_t)bfofreq);
  //save frequency position....
  return 0;
}

int savepos(char** args, uint8_t argc) {
  //save position information for current selected antenna.
  //MaxMotorMoveSteps
  //CurrentMotorPosition
  ML_ANT[mlat_act_setting.last_actived_ant].SaveTotalSteps(MaxMotorMoveSteps);
  ML_ANT[mlat_act_setting.last_actived_ant].SaveMotorPostion(CurrentMotorPosition);

  resprintf("save motor range position information.\n");

  return 0;
}
int showpos(char** args, uint8_t argc) {

  resprintf("Max steps %d, current steps: %d, current frequency:  %d\r\n", MaxMotorMoveSteps, CurrentMotorPosition, mlat_act_setting.LastFrequencySelected);

  return 0;
}
int remfreq(char** args, uint8_t argc) {
  uint32_t freq = atof(args[1]);
  Serial.printf("Remove freq %d \r\n", freq);
  ML_ANT[mlat_act_setting.last_actived_ant].RemovePosition(freq);
  LoadAntennaDataOnUI(mlat_act_setting.last_actived_ant);

  return 0;
}

bool SeekPosForFreq(uint32_t freq) {

  uint16_t swr_v = 0;
  bool result = FindBestSWR(freq, 0, swr_v);

  if (result == true) {
    PositionInfomation pos;
    pos.PresetFrequency = freq;
    pos.StepperPosition = CurrentMotorPosition;
    pos.swr_reference = swr_v;
    resprintf("save preset freq :%d at %d\r\n", pos.PresetFrequency, pos.StepperPosition);
    ML_ANT[mlat_act_setting.last_actived_ant].AddPosition(pos);
    LoadAntennaDataOnUI(mlat_act_setting.last_actived_ant);
  } else {
    resprintf("not save \r\n");
  }
  PageHide(E_PG_SWR_CHART);

  return result;
}

bool Move2RightPositionByFreq(uint32_t freq) {

  //uint32_t preset_pos= ML_ANT[mlat_act_setting.last_actived_ant].FindFreqFromList(freq);
  int16_t f_pos = ML_ANT[mlat_act_setting.last_actived_ant].GetSavePositionFromFrequency(freq);
  bool result = false;
  uint16_t swr_v = 0;
  uint16_t swr0 = 0;
  bool save_result = false;
  PositionInfomation posi;

  if (f_pos < 0) {
    resprintf("No preset position exists for freq:%d\r\n", freq);
    result = FindBestSWR(freq, 0, swr_v);
    if (CurrentMotorPosition > 0) save_result = true;
  } else {
    ML_ANT[mlat_act_setting.last_actived_ant].GetPostionInformation(&posi, f_pos);
    swr0 = posi.swr_reference;
    swr_v = swr0;
    result = FindBestSWR(TrxSignalExists ? 0 : freq, posi.StepperPosition, swr_v);
  }
  if (f_pos >= 0) {
    if (swr_v <= swr0) {
      save_result = true;
      Serial.printf("will update position information with better swr(X10): %d,%d\r\n", swr0, swr_v);
    } else
      Serial.printf("seems that the seeking result it not incorrect! %d,will not save\r\n", swr_v);
  }
  if (save_result) {
    posi.PresetFrequency = freq;
    posi.StepperPosition = CurrentMotorPosition;
    posi.swr_reference = swr_v;
    resprintf("save preset freq :%d at %d, ref swr: %d\r\n", posi.PresetFrequency, posi.StepperPosition, swr_v);
    ML_ANT[mlat_act_setting.last_actived_ant].AddPosition(posi);
    //ML_ANT[mlat_act_setting.last_actived_ant].SaveMotorPostion(CurrentMotorPosition);
    mlat_act_setting.LastFrequencySelected = freq;
    SaveCommonConfiguration();

    LoadAntennaDataOnUI(mlat_act_setting.last_actived_ant);
  } else {
    Serial.printf("no result will be saved!\r\n");
  }
  //ShowPresetFreqList();
  UpdateMotorPosition(false);
  PageHide(E_PG_SWR_CHART);

  return result;
}

int freqmove(char** args, uint8_t argc) {
  float bfofreq = atof(args[1]);


  resprintf("Move to positon for freq: %.2fMhz\n", bfofreq);
  
  Move2RightPositionByFreq((uint32_t)bfofreq);

  resprintf("done");

  return 0;
}
int loadant(char** args, uint8_t argc) {
  LoadAntennaDataOnUI(mlat_act_setting.last_actived_ant);
  return 0;
}
int ClearAllPresetFreqs(char **args,uint8_t argc)
{
    ClearAllFreqs(mlat_act_setting.last_actived_ant);
    return 0;
}
int ClearAllFreqs(uint8_t antIndex)
{
  //
   ML_ANT[antIndex].ClearAllPosition();
   LoadAntennaDataOnUI(mlat_act_setting.last_actived_ant);
   return 0;
}

int reset(char** args, uint8_t argc) {
  resprintf("restart device\r\n");
  ESP.restart();
  return 0;
}
int showprg(char** args, uint8_t argc) {
  uint8_t mode = getint(args[1]);
  if (mode)
    ShowBusyBox();
  else
    HideBusyBox();
  return 0;
}
int forceposition(char** args, uint8_t c) {
  uint32_t pos = getint(args[1]);

  CurrentMotorPosition = pos;
  UpdateMotorPosition();
  Serial.printf("Force current position to %d\r\n", CurrentMotorPosition);

  return 0;
}
int showfv(char** args, uint8_t c) {

  float f_now=GetAndCheckFreq();

  if (c>=2)
  {
    float ref_freq=atof(args[1]);
    //make calibration....
    float delta=ref_freq-f_now;
    int cal_index=-1;
    if (c>=3)
    {
      cal_index=getint(args[2]);  
    }
    Serial.printf("f raw %f,delta:%f relative to F0:%f, %d\r\n", f_now,delta,ref_freq,c);
    switch(cal_index)
    {
      case 0:
      case 1:
        Freq_Delta[cal_index]=f_now;
        FREF_Set[cal_index]=ref_freq;
        break;
      case 2:
        //do calibration...
        FCorr_K=(FREF_Set[1]-FREF_Set[0])/(Freq_Delta[1]-Freq_Delta[0]);
        FCorr_B=FREF_Set[0]-FCorr_K*Freq_Delta[0];
        FreqCalPara.K=FCorr_K;
        FreqCalPara.B=FCorr_B;
        Serial.printf("K=%f, B=%f:  after correct freq is: %f\r\n",FCorr_K,FCorr_B,  FCorr_K*f_now+FCorr_B);

        SaveFreqCalData();
        break;
      default:
      break;
    }
    // frequency is come from 1 second counter.. the error is come from timebase.    
  }else
  {
        Serial.printf("f raw %f\r\n", f_now);

  }

  return 0;
}
void ShowUpTime()
{
    Serial.printf("Up time: %d Hours %d min %d sec\r\n",theHoursOfBoot,theMinOfBoot,theSecOfBoot);
    return ;
}
 int showuptimes(char**args,uint8_t argc)
 {
    ShowUpTime();
    return 0;
 }
static struct _uartcmd2func defined_uart_cmds[] = {
  { "ver", ShowVersion },
  { "fscan", DoFreqScan },
  { "setfg", SetFrequencyGenerator },
  { "off", switchoff },
  { "tcal", touchcal },
  { "rio", readio },
  { "adc", readadc },
  { "bfo", setbfo },
  { "trx", switchbfo },
  { "swr", readswr },
  { "ioex", writeioex },
  { "move", move },
  { "setms", setms },
  { "swreva", DoSWRSpeedTest },
  { "fcs", freqcounterselect },
  { "fff", showfv },
  { "stall", setstall },
  { "motorrms", set_motor_rms },
  { "motstat", showmotstat },
  { "moten", moten },
  { "motref", setmotref },
  { "motoff", setmotoff },
  { "clksrc", setclksrc },
  { "findhome", findhome },
  { "dmove", dirmove },
  { "fswr", findswr },
  { "savepos", savepos },
  { "getpos", showpos },
  { "fmove", freqmove },
  { "loadant", loadant },
  { "reset", reset },
  { "showprg", showprg },
  { "fpos", forceposition },
  { "remfreq", remfreq },
  {"remall",ClearAllPresetFreqs},
  {"msg",testmsg},
  {"uptime",showuptimes}
};
int UartDispatchMsg() {
#define kMaxArgs 100


  uint8_t argc = 0;
  int result = 100;
  char* argv[kMaxArgs];
  uart_msg_pipe routine_entry = NULL;

  char* token = ":";
  if (!strstr(rx_buffer, token)) token = " ";

  argc = 0;
  memset(argv, 0, kMaxArgs);
  char* p2 = strtok(rx_buffer, token);
  while (p2 && argc < kMaxArgs - 1) {
    argv[argc++] = p2;
    p2 = strtok(0, token);
  }

  argv[argc] = 0;

  char* cmd = NULL;
  if (argc == 0)
    cmd = rx_buffer;
  else
    cmd = argv[0];

  if (strlen(cmd)) {
    int16_t i;
    int size = sizeof(defined_uart_cmds) / sizeof(struct _uartcmd2func);
    for (i = 0; i < size; i++) {
      if (strcmp(defined_uart_cmds[i].pInputStr, cmd) == 0) {
        routine_entry = defined_uart_cmds[i].pFunc;
        break;
      }
    }

    if (routine_entry) {
      (routine_entry)(argv, argc);
    } else {
      resprintf("unhandled command! %s\n", rx_buffer);
    }
  }
  return 0;
}
//define function list here
void SerialTask() {
  // print the string when a newline arrives:
  if (StringCommandInput != NO_COMMAND) {
    // Serial.println(inputString);
    Serial.print("3");
    if (strlen(rx_buffer) > 1) {
      UartDispatchMsg();
      ResetUartMsg();
    }
  }
}
void ProcessTelnetCommand(String strcmd) {
  sprintf(rx_buffer, "%s", strcmd.c_str());
  StringCommandInput = TELNET_INPUT;
}

void CheckPowerKey() {
  uint16_t Pressed = PowerOffKey.ButtonClicked();
  if (Pressed > 2000) {
    resprintf("Power Off...\r\n");
    ShowTipMsg("switching off...");
    SwitchPowerOff();
  } else {
    //<0 pushed but not released.
    // ShowTipMsg("press 2 seconds to power off");
  }
}
void RotaryModeProcess() {
  static unsigned long lastRotaryValue = 0;
  int32_t vv = rotaryEncoder.readEncoder();
  int32_t Delta = vv - lastRotaryValue;
  // Serial.printf("vv=%d, Move Delta=%d\r\n",vv,Delta);
  //stepper.moveRelativeInSteps(Delta);

  MoveMotorInSteps(Delta * MotorMicroSteps() * 5, 200);

  //ActivedAntenna.SetActivePosition.
  lastRotaryValue = vv;
}
void UpdateMotorStepperSetting() {
  //
}

void rotary_onButtonClick() {
  static unsigned long lastTimePressed = 0;
  if (millis() - lastTimePressed < 100) return;
  lastTimePressed = millis();
}

// TBD:

void EncoderTask() {
  static unsigned long lastTimeTrigged = 0;
  unsigned long now = millis();

  //if (now-lastTimeTrigged <100) return;

  if (rotaryEncoder.encoderChanged()) {
    if (Current_MOT_MODE != MOT_0_0_OFF) {
      RotaryModeProcess();
      lastTimeTrigged = now;
    }
  } else {
    // check
    if (millis() - lastTimeTrigged > 2000)  //reset to idle mode...
    {
      Current_MOT_MODE = MOT_0_0_OFF;
      UpdateMotorStepperSetting();
    }
  }

  if (rotaryEncoder.EncoderButtonClicked()) {
    rotary_onButtonClick();  //on idle UI, this let it rolling in Off/Full/Half/Four/Sixteen/ micorsteps.
    lastTimeTrigged = now;
  }
}

void UpdateFrequencyCounter() {
  //  get TRX frequency. read Local freqeucny Counter...
  static uint32_t sync_time=0;
  static bool need_swr_tune=false;
  float this_freq;
  //
 // Serial.print("1");
 
  static unsigned long LastUpdateTick = 0;
  if (millis() - LastUpdateTick < 500) return;

  FreqDetected = GetAndCheckFreq();
 


  FreqDetected=FreqDetected*FreqCalPara.K+FreqCalPara.B;
   
     
 
  //last update time...>3 seconds
  // old_disp_freq=FreqDetected;  
 // swr_tune_done=false;
  // sync_time=millis();
  char cBuffer[9];
  memset(cBuffer,0,9);

  snprintf(cBuffer, 9, "%.3f\0", FreqDetected);
  this_freq=atof(cBuffer);
  gslc_ElemSetTxtStr(&m_gui, m_ele_TRXFreq, cBuffer);
  //switch disp freq...
  if (fabs(this_freq-old_disp_freq)>0.01) 
  {
      // time to change...
      Serial.printf("old freq: %f, current freq: %f\r\n",old_disp_freq,this_freq);
      old_disp_freq=this_freq;

      if (old_disp_freq>1.5)
      {
        sync_time=millis();
        need_swr_tune=true;
      }else
      {
        need_swr_tune=false;
      }

  } 

  if (need_swr_tune)
  {
    if (millis()-sync_time>5000)
    {
        Serial.printf("move for freq: %f Mhz\r\n",old_disp_freq);
        need_swr_tune=false;
        sync_time=millis()+5000;
        SetUICommand("fmove %f", old_disp_freq*1e6);
    }
  }
}
void ProcessWiFiTask() {
  static uint32_t old_tick = 0;
  static uint8_t connect_try = 0;
  static uint8_t state=0;       //0:ilde. 1 scaning...
  
  WebPolling();  //handle OTA update event.


  if (millis() - old_tick < 3000) return;
  
  // TBD: the SSID is exists....
  if (WifiInformationValid) {
    if (connect_try == 0) {
      WiFiTryConnect(mlat_act_setting.WifiSSID, mlat_act_setting.WifiPsk);
      connect_try = 1;
    } else {
      if (IsWiFiConnected()) {
        //update IPAddress...
        UpdateIpAddr(GetIpAddress().c_str(), true);
        //enable OTA button
        //gslc_ElemSetClickEn(&m_gui, m_pElemOTA129, true);
        EnableButton(m_pElemOTA129);
        if (!TelnetEnabled) {
          TelnetEnabled = true;
          setupTelnet();
        }
      } else {
        UpdateIpAddr("----");
        //Disable OTA
        //gslc_ElemSetClickEn(&m_gui, m_pElemOTA129, false);
        DisableButton(m_pElemOTA129);
      }
    }

  } else {
    UpdateIpAddr("----");
  }
  old_tick = millis();
}


void setup() {
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  theTickOfBoot=millis();
  ResetUartMsg();

  Serial.begin(921600);

  gslc_InitDebug(&DebugOut);

  IntializeIOEX();
  WifiInit();

  // Wait for USB Serial
  //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used
  Serial.printf("Firmware version: %s\r\n", versionstring());

  if (!SPIFFS.begin()) {
    //give some tip;

    Serial.println("Formating file system...please wait");
    SPIFFS.format();
    SPIFFS.begin();
  }
  ShowFSInfo();

  LoadCommonConfiguration();
  LoadSWROffsetData();

  InitGUIslice_gen();

  ShowTipMsg("Starting...");
  //ShowPageID();
  ShowWifiSSID(mlat_act_setting.WifiSSID);

  UpdateIpAddr("N/A");

  //ShowPageID(mlat_act_setting.PageID);

  PageStacks.push_back(E_PG_MAIN);


  UpdateMotorProgress(0);


  InitializeRadioList();

  gslc_Update(&m_gui);
  //SetupRotaryEncoder();
  rotaryEncoder.begin();
  // rotaryEncoder.setBoundaries(-20000, 20000, true); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
  // rotaryEncoder.setAcceleration(50);
  rotaryEncoder.setEncoderValue(0);

  SetupStepperMotor();  //start a runing service...
  //MotorRunningMsg     	MotorMsg;       // for service mode task.
  SetupSWRMeter();
  SetupFreqTimer();

  SetupFrequencyGenerator();
  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------

  //  gslc_Update(&m_gui);
  // UpdateMotorStepperSetting();
  ResetUartMsg();

  ShowCommonConfig();
  LoadAntennaDataOnUI(mlat_act_setting.last_actived_ant);


  UpdateMotorPosition();
  if (WifiInformationValid) {
    ShowTipMsg("try wifi connection.");
    WiFiTryConnect(mlat_act_setting.WifiSSID, mlat_act_setting.WifiPsk);
  }
  MotorEnControl(false);
  ShowTipMsg("ready.");
}

void UpdateSWRMeter() {
  static unsigned long LastUpdateTick = 0;

  if (millis() - LastUpdateTick < 100) return;
//Serial.print("2");

  float fwd, rev;

  float swr = GetSWRValue(50, &fwd, &rev, mlat_act_setting.PowerDispMode);

  RefreshSWRMeter(swr, fwd, rev);

  if (!UseInternalClkSrc)  //trx ==0
  {
    if (fwd < 2)
      TrxSignalExists = false;
    else
      TrxSignalExists = true;
  }else
  {
 
      TrxSignalExists = false;
 
  }

  LastUpdateTick = millis();
}
void UpdateMotorProgress(uint8_t vv) {
  if (vv > 100) vv = 100;
  gslc_ElemXProgressSetVal(&m_gui, m_pElemProgress1, vv);
}
void UpdateMotorPosition(bool save) {
  if (MaxMotorMoveSteps == 0) return;

  char sV[10];
  sprintf(sV, "%d", CurrentMotorPosition);
  gslc_ElemSetTxtStr(&m_gui, m_pElemCurrentPos, sV);

  sprintf(sV, "%d", MaxMotorMoveSteps);
  gslc_ElemSetTxtStr(&m_gui, m_pElem_MaxPos, sV);

  gslc_ElemSetTxtStr(&m_gui, p_ElemSteps, sV);

  if (save) ML_ANT[mlat_act_setting.last_actived_ant].SaveMotorPostion(CurrentMotorPosition);

  float vv = (float)CurrentMotorPosition * 100 / MaxMotorMoveSteps;
  UpdateMotorProgress(vv);
  return;
}
void RefreshSWRMeter(float swr, float fwd, float rev) {
  char cBuffer[10];
  char unit[10];
  bool SignalExists=false;
  
  memset(cBuffer,0,10);
  memset(unit,0,10);

  if (mlat_act_setting.PowerDispMode) {
    
    if (fwd>-5) SignalExists=true;

    snprintf(cBuffer, 4, "%.1f\0", fwd);
    gslc_ElemSetTxtStr(&m_gui, m_eleSWRFWD, cBuffer);

    gslc_ElemSetTxtStr(&m_gui, m_pElemFWDUnit, "dbm");

    snprintf(cBuffer, 4, "%.1f\0", rev);
    gslc_ElemSetTxtStr(&m_gui, m_eleSWRREV, cBuffer);

    gslc_ElemSetTxtStr(&m_gui, m_pElemREFunit, "dbm");

  } else {
    //we read in  mW.
    if (fwd>1) SignalExists=true;
 
    if (fwd > 1000) {
      snprintf(cBuffer, 4, "%.1f\0", fwd / 1000);
      sprintf(unit, "W\0");
    } else {
      snprintf(cBuffer, 4, "%.1f\0", fwd);
      sprintf(unit, "mW\0");
    }
    gslc_ElemSetTxtStr(&m_gui, m_eleSWRFWD, cBuffer);
    gslc_ElemSetTxtStr(&m_gui, m_pElemFWDUnit, unit);

    if (rev > 1000) {
      snprintf(cBuffer, 4, "%.1f\0", rev / 1000);
      sprintf(unit, "W\0");
    } else {
      snprintf(cBuffer, 4, "%.1f\0", rev);
      sprintf(unit, "mW\0");
    }
    gslc_ElemSetTxtStr(&m_gui, m_eleSWRREV, cBuffer);

    gslc_ElemSetTxtStr(&m_gui, m_pElemREFunit, unit);
  }


  if (SignalExists)
    snprintf(cBuffer, 6, "%.2f\0", swr);
  else
    snprintf(cBuffer, 6, "----\0" );

  gslc_ElemSetTxtStr(&m_gui, m_ele_SWR, cBuffer);
  //ElemSetVisible(&m_gui,)
  return;
}

void ProcessIOTask() {
  if (ioex_int_flag) {
    Serial.print("4");
    ProcessIOEXEvent();
    //EncoderTask();
    CheckPowerKey();
  }
}
// -----------------------------------
// Main event loop
// -----------------------------------
void loop() {
   //theMinOfBoot=
  if (millis()-theTickOfBoot>1000)
  {
    theSecOfBoot++;    
    theTickOfBoot=millis();
    if (theSecOfBoot>60)
    {
      theSecOfBoot=0;
      theMinOfBoot++;
       ShowUpTime();
      if (theMinOfBoot>60)
      {
        theMinOfBoot=0;
        theHoursOfBoot++;
      }
    }
  } 
  if (SwrMeterMode) {
      DoFreqScanOnScreen();
  } else {
 
      UpdateFrequencyCounter();
      UpdateSWRMeter();
   }

  SerialTask();
  ProcessIOTask();
  ProcessWiFiTask();
  //RefreshBusyBox();
  //check TRX ..
  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------

  //TODO - Add update code for any text, gauges, or sliders
  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
}
