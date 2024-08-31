//<File !Start!>
// FILE: [MLAT22UI_GSLC.h]
// Created by GUIslice Builder version: [0.17.b12]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XCheckbox.h"
#include "elem/XKeyPad_Alpha.h"
#include "elem/XKeyPad_Num.h"
#include "elem/XListbox.h"
#include "elem/XProgress.h"
#include "elem/XRingGauge.h"
#include "elem/XSeekbar.h"
#include "elem/XSlider.h"
#include "elem/XTextbox.h"

// Ensure optional features are enabled in the configuration
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if !defined(DRV_DISP_TFT_ESPI)
  #error E_PROJECT_OPTIONS tab->Graphics Library should be Adafruit_GFX
#endif
#include <TFT_eSPI.h>
#include "NotoSerif8pt7b.h"
#include "Seven_Segment10pt7b.h"
#include "Seven_Segment12pt7b.h"
#include "Seven_Segment18pt7b.h"
#include "Seven_Segment8pt7b.h"
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN,E_PG_RADIO,E_PG_ANT,E_PG_MENU,E_PG_SWR_CHART,E_PG_MSBOX
      ,E_PG_WIFI,E_PG_NUMKEYPAD,E_PG_POPUP_FS,E_PG_MOTOR_CFG
      ,E_PG_BASIC_SETTING,E_PG_POP_PRG,E_PG_BFO,E_PG_SWR_CAL
      ,E_POP_KEYPAD_NUM,E_POP_KEYPAD_ALPHA};
enum {E_DRAW_LINE5,E_DRAW_LINE6,E_DRAW_LINE7,E_ELEM_BOX13,E_ELEM_BOX14
      ,E_ELEM_BOX15,E_ELEM_BOX16,E_ELEM_BOX17,E_ELEM_BOX18,E_ELEM_BOX19
      ,E_ELEM_BOX21,E_ELEM_BOX22,E_ELEM_BOX23,E_ELEM_BOX24,E_ELEM_BOX25
      ,E_ELEM_BOX3,E_ELEM_BOX6,E_ELEM_BOX7,E_ELEM_BOX8,E_ELEM_BTN112
      ,E_ELEM_BTN113,E_ELEM_BTN114,E_ELEM_BTN115,E_ELEM_BTN116
      ,E_ELEM_BTN118,E_ELEM_BTN119,E_ELEM_BTN120,E_ELEM_BTN121
      ,E_ELEM_BTN122,E_ELEM_BTN123,E_ELEM_BTN124,E_ELEM_BTN125
      ,E_ELEM_BTN128,E_ELEM_BTN129,E_ELEM_BTN131,E_ELEM_BTN133
      ,E_ELEM_BTN134,E_ELEM_BTN135,E_ELEM_BTN136,E_ELEM_BTN137
      ,E_ELEM_BTN138,E_ELEM_BTN139,E_ELEM_BTN140,E_ELEM_BTN142
      ,E_ELEM_BTN144,E_ELEM_BTN145,E_ELEM_BTN146,E_ELEM_BTN147
      ,E_ELEM_BTN148,E_ELEM_BTN149,E_ELEM_BTN152,E_ELEM_BTN153
      ,E_ELEM_BTN154,E_ELEM_BTN155,E_ELEM_BTN156,E_ELEM_BTN54
      ,E_ELEM_BTN55,E_ELEM_BTN56,E_ELEM_BTN57,E_ELEM_BTN58,E_ELEM_BTN64
      ,E_ELEM_BTN65,E_ELEM_BTN66,E_ELEM_BTN69,E_ELEM_BTN70,E_ELEM_BTN72
      ,E_ELEM_BTN74,E_ELEM_BTN_BKSP,E_ELEM_BTN_CLR,E_ELEM_BTN_ENT
      ,E_ELEM_BTN_FREQOK,E_ELEM_BTN_LINKTEST,E_ELEM_BTN_MHZ
      ,E_ELEM_BTN_NUM0,E_ELEM_BTN_NUM1,E_ELEM_BTN_NUM2,E_ELEM_BTN_NUM3
      ,E_ELEM_BTN_NUM4,E_ELEM_BTN_NUM5,E_ELEM_BTN_NUM6,E_ELEM_BTN_NUM7
      ,E_ELEM_BTN_NUM8,E_ELEM_BTN_NUM9,E_ELEM_BTN_NUMDOT
      ,E_ELEM_BTN_SWITCH_ANT,E_ELEM_BTN_TRXOK,E_ELEM_CHECK2
      ,E_ELEM_CHECK3,E_ELEM_LISTBOX3,E_ELEM_LISTBOX4
      ,E_ELEM_LISTBOX_FREQ,E_ELEM_MSG_OK,E_ELEM_NUMINPUT11
      ,E_ELEM_NUMINPUT12,E_ELEM_NUMINPUT13,E_ELEM_NUMINPUT14
      ,E_ELEM_NUMINPUT15,E_ELEM_NUMINPUT16,E_ELEM_NUMINPUT23
      ,E_ELEM_NUMINPUT24,E_ELEM_NUMINPUT25,E_ELEM_NUMINPUT26
      ,E_ELEM_NUMINPUT8,E_ELEM_PROGRESS1,E_ELEM_RADIO3,E_ELEM_RADIO4
      ,E_ELEM_RADIO5,E_ELEM_RINGGAUGE1,E_ELEM_SEEKBAR2,E_ELEM_SEEKBAR3
      ,E_ELEM_SEEKBAR4,E_ELEM_SLIDER2,E_ELEM_TEXT110,E_ELEM_TEXT122
      ,E_ELEM_TEXT123,E_ELEM_TEXT141,E_ELEM_TEXT153,E_ELEM_TEXT154
      ,E_ELEM_TEXT155,E_ELEM_TEXT156,E_ELEM_TEXT157,E_ELEM_TEXT158
      ,E_ELEM_TEXT159,E_ELEM_TEXT160,E_ELEM_TEXT161,E_ELEM_TEXT162
      ,E_ELEM_TEXT171,E_ELEM_TEXT174,E_ELEM_TEXT178,E_ELEM_TEXT182
      ,E_ELEM_TEXT183,E_ELEM_TEXT184,E_ELEM_TEXT185,E_ELEM_TEXT186
      ,E_ELEM_TEXT187,E_ELEM_TEXT188,E_ELEM_TEXT189,E_ELEM_TEXT194
      ,E_ELEM_TEXT195,E_ELEM_TEXT196,E_ELEM_TEXT197,E_ELEM_TEXT198
      ,E_ELEM_TEXT199,E_ELEM_TEXT200,E_ELEM_TEXT201,E_ELEM_TEXT202
      ,E_ELEM_TEXT203,E_ELEM_TEXT204,E_ELEM_TEXT205,E_ELEM_TEXT206
      ,E_ELEM_TEXT207,E_ELEM_TEXT208,E_ELEM_TEXT209,E_ELEM_TEXT210
      ,E_ELEM_TEXT211,E_ELEM_TEXT212,E_ELEM_TEXT213,E_ELEM_TEXT214
      ,E_ELEM_TEXT215,E_ELEM_TEXT216,E_ELEM_TEXT217,E_ELEM_TEXT218
      ,E_ELEM_TEXT220,E_ELEM_TEXT221,E_ELEM_TEXT230,E_ELEM_TEXT231
      ,E_ELEM_TEXT232,E_ELEM_TEXT233,E_ELEM_TEXT234,E_ELEM_TEXT235
      ,E_ELEM_TEXT236,E_ELEM_TEXT237,E_ELEM_TEXT238,E_ELEM_TEXT240
      ,E_ELEM_TEXT241,E_ELEM_TEXT242,E_ELEM_TEXT243,E_ELEM_TEXT244
      ,E_ELEM_TEXT245,E_ELEM_TEXT246,E_ELEM_TEXT247,E_ELEM_TEXT248
      ,E_ELEM_TEXT249,E_ELEM_TEXT250,E_ELEM_TEXT251,E_ELEM_TEXT252
      ,E_ELEM_TEXT253,E_ELEM_TEXT254,E_ELEM_TEXT255,E_ELEM_TEXT256
      ,E_ELEM_TEXT257,E_ELEM_TEXT260,E_ELEM_TEXT261,E_ELEM_TEXT262
      ,E_ELEM_TEXT263,E_ELEM_TEXT264,E_ELEM_TEXT265,E_ELEM_TEXT266
      ,E_ELEM_TEXT267,E_ELEM_TEXT268,E_ELEM_TEXT269,E_ELEM_TEXT270
      ,E_ELEM_TEXT278,E_ELEM_TEXT279,E_ELEM_TEXT280,E_ELEM_TEXT281
      ,E_ELEM_TEXT282,E_ELEM_TEXT283,E_ELEM_TEXT284,E_ELEM_TEXTBOX3
      ,E_ELEM_TEXTINPUT2,E_LISTSCROLL1,E_LISTSCROLL2,E_LISTSCROLL4
      ,E_ELEM_KEYPAD_NUM,E_ELEM_KEYPAD_ALPHA};
enum {GSLC_GROUP_ID_PWR_DISP};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN10X16,E_BUILTIN5X8,E_NOTOSERIF8,E_SEVEN_SEGMENT10
      ,E_SEVEN_SEGMENT12,E_SEVEN_SEGMENT18,E_SEVEN_SEGMENT8,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                16

#define MAX_ELEM_PG_MAIN 37 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_PG_RADIO 12 // # Elems total on page
#define MAX_ELEM_PG_RADIO_RAM MAX_ELEM_PG_RADIO // # Elems in RAM

#define MAX_ELEM_PG_ANT 19 // # Elems total on page
#define MAX_ELEM_PG_ANT_RAM MAX_ELEM_PG_ANT // # Elems in RAM

#define MAX_ELEM_PG_MENU 11 // # Elems total on page
#define MAX_ELEM_PG_MENU_RAM MAX_ELEM_PG_MENU // # Elems in RAM

#define MAX_ELEM_PG_SWR_CHART 14 // # Elems total on page
#define MAX_ELEM_PG_SWR_CHART_RAM MAX_ELEM_PG_SWR_CHART // # Elems in RAM

#define MAX_ELEM_PG_MSBOX 3 // # Elems total on page
#define MAX_ELEM_PG_MSBOX_RAM MAX_ELEM_PG_MSBOX // # Elems in RAM

#define MAX_ELEM_PG_WIFI 16 // # Elems total on page
#define MAX_ELEM_PG_WIFI_RAM MAX_ELEM_PG_WIFI // # Elems in RAM

#define MAX_ELEM_PG_NUMKEYPAD 20 // # Elems total on page
#define MAX_ELEM_PG_NUMKEYPAD_RAM MAX_ELEM_PG_NUMKEYPAD // # Elems in RAM

#define MAX_ELEM_PG_POPUP_FS 17 // # Elems total on page
#define MAX_ELEM_PG_POPUP_FS_RAM MAX_ELEM_PG_POPUP_FS // # Elems in RAM

#define MAX_ELEM_PG_MOTOR_CFG 20 // # Elems total on page
#define MAX_ELEM_PG_MOTOR_CFG_RAM MAX_ELEM_PG_MOTOR_CFG // # Elems in RAM

#define MAX_ELEM_PG_BASIC_SETTING 18 // # Elems total on page
#define MAX_ELEM_PG_BASIC_SETTING_RAM MAX_ELEM_PG_BASIC_SETTING // # Elems in RAM

#define MAX_ELEM_PG_POP_PRG 1 // # Elems total on page
#define MAX_ELEM_PG_POP_PRG_RAM MAX_ELEM_PG_POP_PRG // # Elems in RAM

#define MAX_ELEM_PG_BFO 15 // # Elems total on page
#define MAX_ELEM_PG_BFO_RAM MAX_ELEM_PG_BFO // # Elems in RAM

#define MAX_ELEM_PG_SWR_CAL 14 // # Elems total on page
#define MAX_ELEM_PG_SWR_CAL_RAM MAX_ELEM_PG_SWR_CAL // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage3Elem[MAX_ELEM_PG_RADIO_RAM];
gslc_tsElemRef                  m_asPage3ElemRef[MAX_ELEM_PG_RADIO];
gslc_tsElem                     m_asPage4Elem[MAX_ELEM_PG_ANT_RAM];
gslc_tsElemRef                  m_asPage4ElemRef[MAX_ELEM_PG_ANT];
gslc_tsElem                     m_asPage5Elem[MAX_ELEM_PG_MENU_RAM];
gslc_tsElemRef                  m_asPage5ElemRef[MAX_ELEM_PG_MENU];
gslc_tsElem                     m_asPage7Elem[MAX_ELEM_PG_SWR_CHART_RAM];
gslc_tsElemRef                  m_asPage7ElemRef[MAX_ELEM_PG_SWR_CHART];
gslc_tsElem                     m_asPopup1Elem[MAX_ELEM_PG_MSBOX_RAM];
gslc_tsElemRef                  m_asPopup1ElemRef[MAX_ELEM_PG_MSBOX];
gslc_tsElem                     m_asPage8Elem[MAX_ELEM_PG_WIFI_RAM];
gslc_tsElemRef                  m_asPage8ElemRef[MAX_ELEM_PG_WIFI];
gslc_tsElem                     m_asPopup2Elem[MAX_ELEM_PG_NUMKEYPAD_RAM];
gslc_tsElemRef                  m_asPopup2ElemRef[MAX_ELEM_PG_NUMKEYPAD];
gslc_tsElem                     m_asPopup3Elem[MAX_ELEM_PG_POPUP_FS_RAM];
gslc_tsElemRef                  m_asPopup3ElemRef[MAX_ELEM_PG_POPUP_FS];
gslc_tsElem                     m_asPage9Elem[MAX_ELEM_PG_MOTOR_CFG_RAM];
gslc_tsElemRef                  m_asPage9ElemRef[MAX_ELEM_PG_MOTOR_CFG];
gslc_tsElem                     m_asPage10Elem[MAX_ELEM_PG_BASIC_SETTING_RAM];
gslc_tsElemRef                  m_asPage10ElemRef[MAX_ELEM_PG_BASIC_SETTING];
gslc_tsElem                     m_asPopup4Elem[MAX_ELEM_PG_POP_PRG_RAM];
gslc_tsElemRef                  m_asPopup4ElemRef[MAX_ELEM_PG_POP_PRG];
gslc_tsElem                     m_asPage11Elem[MAX_ELEM_PG_BFO_RAM];
gslc_tsElemRef                  m_asPage11ElemRef[MAX_ELEM_PG_BFO];
gslc_tsElem                     m_asPage12Elem[MAX_ELEM_PG_SWR_CAL_RAM];
gslc_tsElemRef                  m_asPage12ElemRef[MAX_ELEM_PG_SWR_CAL];
gslc_tsElem                     m_asKeypadNumElem[1];
gslc_tsElemRef                  m_asKeypadNumElemRef[1];
gslc_tsElem                     m_asKeypadAlphaElem[1];
gslc_tsElemRef                  m_asKeypadAlphaElemRef[1];
gslc_tsXKeyPad                  m_sKeyPadNum;
gslc_tsXKeyPad                  m_sKeyPadAlpha;
gslc_tsXProgress                m_sXBarGauge1;
gslc_tsXCheckbox                m_asXRadio5;
gslc_tsXListbox                 m_sListbox3;
// - Note that XLISTBOX_BUF_OH_R is extra required per item
char                            m_acListboxBuf3[512 + XLISTBOX_BUF_OH_R];
gslc_tsXSlider                  m_sListScroll3;
gslc_tsXListbox                 m_sListbox2;
// - Note that XLISTBOX_BUF_OH_R is extra required per item
char                            m_acListboxBuf2[100 + XLISTBOX_BUF_OH_R];
gslc_tsXSlider                  m_sListScroll2;
gslc_tsXCheckbox                m_asXCheck2;
gslc_tsXTextbox                 m_sTextbox3;
char                            m_acTextboxBuf3[240]; // NRows=8 NCols=30
gslc_tsXListbox                 m_sListbox4;
// - Note that XLISTBOX_BUF_OH_R is extra required per item
char                            m_acListboxBuf4[1024 + XLISTBOX_BUF_OH_R];
gslc_tsXSlider                  m_sListScroll4;
gslc_tsXSlider                  m_sXSlider2;
gslc_tsXSeekbar                 m_sXSeekbar2;
gslc_tsXSeekbar                 m_sXSeekbar3;
gslc_tsXSeekbar                 m_sXSeekbar4;
gslc_tsXCheckbox                m_asXRadio3;
gslc_tsXCheckbox                m_asXRadio4;
gslc_tsXCheckbox                m_asXCheck3;
gslc_tsXRingGauge               m_sXRingGauge1;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_eleSWRFWD;
extern gslc_tsElemRef* m_eleSWRREV;
extern gslc_tsElemRef* m_ele_ANTID116;
extern gslc_tsElemRef* m_ele_BTN_TRX115;
extern gslc_tsElemRef* m_ele_SWR;
extern gslc_tsElemRef* m_ele_TRXFreq;
extern gslc_tsElemRef* m_pElemANTC0;
extern gslc_tsElemRef* m_pElemANTC1;
extern gslc_tsElemRef* m_pElemANTC2;
extern gslc_tsElemRef* m_pElemAddFreq;
extern gslc_tsElemRef* m_pElemAntIndex;
extern gslc_tsElemRef* m_pElemAntPage1;
extern gslc_tsElemRef* m_pElemAntPage2;
extern gslc_tsElemRef* m_pElemAntPage3;
extern gslc_tsElemRef* m_pElemBand;
extern gslc_tsElemRef* m_pElemBandMeter;
extern gslc_tsElemRef* m_pElemBtn72;
extern gslc_tsElemRef* m_pElemBtn72_125;
extern gslc_tsElemRef* m_pElemBtn72_139;
extern gslc_tsElemRef* m_pElemBtnBFO;
extern gslc_tsElemRef* m_pElemBtnBFOCH1;
extern gslc_tsElemRef* m_pElemBtnBFOCH2;
extern gslc_tsElemRef* m_pElemBtnMenu;
extern gslc_tsElemRef* m_pElemCBCheckBox;
extern gslc_tsElemRef* m_pElemCBCheckBox;
extern gslc_tsElemRef* m_pElemChartTitle;
extern gslc_tsElemRef* m_pElemCurrentPos;
extern gslc_tsElemRef* m_pElemFWDUnit;
extern gslc_tsElemRef* m_pElemFreqSrc;
extern gslc_tsElemRef* m_pElemFstep;
extern gslc_tsElemRef* m_pElemFstep214;
extern gslc_tsElemRef* m_pElemGraph_FreqScan;
extern gslc_tsElemRef* m_pElemIPAddr0;
extern gslc_tsElemRef* m_pElemLinkTest;
extern gslc_tsElemRef* m_pElemListbox1_3;
extern gslc_tsElemRef* m_pElemListboxFreq;
extern gslc_tsElemRef* m_pElemListboxWifi;
extern gslc_tsElemRef* m_pElemMotorPos;
extern gslc_tsElemRef* m_pElemMsgBoxText;
extern gslc_tsElemRef* m_pElemNextPage;
extern gslc_tsElemRef* m_pElemOTA129;
extern gslc_tsElemRef* m_pElemOTA129_136;
extern gslc_tsElemRef* m_pElemOldTRX;
extern gslc_tsElemRef* m_pElemOutTxt185;
extern gslc_tsElemRef* m_pElemOutTxt186;
extern gslc_tsElemRef* m_pElemOutTxt250;
extern gslc_tsElemRef* m_pElemOutTxt250_251;
extern gslc_tsElemRef* m_pElemOutTxt250_252;
extern gslc_tsElemRef* m_pElemOutTxt259_261;
extern gslc_tsElemRef* m_pElemPF0;
extern gslc_tsElemRef* m_pElemPF1;
extern gslc_tsElemRef* m_pElemPF2;
extern gslc_tsElemRef* m_pElemPF3;
extern gslc_tsElemRef* m_pElemPSKConf229_233;
extern gslc_tsElemRef* m_pElemPrevPage;
extern gslc_tsElemRef* m_pElemProgress1;
extern gslc_tsElemRef* m_pElemRBFreqSrc;
extern gslc_tsElemRef* m_pElemRBRadioButton2_4;
extern gslc_tsElemRef* m_pElemRBRadioButton3;
extern gslc_tsElemRef* m_pElemREFunit;
extern gslc_tsElemRef* m_pElemRemFreq;
extern gslc_tsElemRef* m_pElemSSIDConf227_231;
extern gslc_tsElemRef* m_pElemSWRSetting;
extern gslc_tsElemRef* m_pElemSWRSetting154;
extern gslc_tsElemRef* m_pElemSeekbarRMS;
extern gslc_tsElemRef* m_pElemSeekbarSPEED;
extern gslc_tsElemRef* m_pElemSeekbarSTALL;
extern gslc_tsElemRef* m_pElemSigSrc146;
extern gslc_tsElemRef* m_pElemSliderBand;
extern gslc_tsElemRef* m_pElemSwitchFreq;
extern gslc_tsElemRef* m_pElemTRXOK;
extern gslc_tsElemRef* m_pElemTipInfo;
extern gslc_tsElemRef* m_pElemVal17_18_24;
extern gslc_tsElemRef* m_pElemVal17_19_25;
extern gslc_tsElemRef* m_pElemVal17_20_26;
extern gslc_tsElemRef* m_pElemVal17_23;
extern gslc_tsElemRef* m_pElemValBFO0;
extern gslc_tsElemRef* m_pElemValBFO1;
extern gslc_tsElemRef* m_pElemValBFO2;
extern gslc_tsElemRef* m_pElemValFS0;
extern gslc_tsElemRef* m_pElemValFSE;
extern gslc_tsElemRef* m_pElemValFStep;
extern gslc_tsElemRef* m_pElemValFreq;
extern gslc_tsElemRef* m_pElemWiFiSave;
extern gslc_tsElemRef* m_pElemXRingGauge1;
extern gslc_tsElemRef* m_pElem_ICOM_Addr8;
extern gslc_tsElemRef* m_pElem_MaxPos;
extern gslc_tsElemRef* m_pElem_MotorPos;
extern gslc_tsElemRef* m_pElem_MotorPos213;
extern gslc_tsElemRef* m_pElem_SSID0;
extern gslc_tsElemRef* m_pElem_TrxName;
extern gslc_tsElemRef* m_pElemtxtPSK;
extern gslc_tsElemRef* m_pListSlider1;
extern gslc_tsElemRef* m_pListSlider2;
extern gslc_tsElemRef* m_pListSlider4;
extern gslc_tsElemRef* m_pTextSlider3;
extern gslc_tsElemRef* p_ElemSteps;
extern gslc_tsElemRef* p_ElemStepsCur;
extern gslc_tsElemRef* p_Elem_InputString;
extern gslc_tsElemRef* p_Elem_Unit;
extern gslc_tsElemRef* p_elem_IP_addr165_179_188;
extern gslc_tsElemRef* p_elem_IP_addr165_183;
extern gslc_tsElemRef* m_pElemKeyPadNum;
extern gslc_tsElemRef* m_pElemKeyPadAlpha;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN10X16,GSLC_FONTREF_PTR,NULL,2)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOSERIF8,GSLC_FONTREF_PTR,&NotoSerif8pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_SEVEN_SEGMENT10,GSLC_FONTREF_PTR,&Seven_Segment10pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_SEVEN_SEGMENT12,GSLC_FONTREF_PTR,&Seven_Segment12pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_SEVEN_SEGMENT18,GSLC_FONTREF_PTR,&Seven_Segment18pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_SEVEN_SEGMENT8,GSLC_FONTREF_PTR,&Seven_Segment8pt7b,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_PG_RADIO,m_asPage3Elem,MAX_ELEM_PG_RADIO_RAM,m_asPage3ElemRef,MAX_ELEM_PG_RADIO);
  gslc_PageAdd(&m_gui,E_PG_ANT,m_asPage4Elem,MAX_ELEM_PG_ANT_RAM,m_asPage4ElemRef,MAX_ELEM_PG_ANT);
  gslc_PageAdd(&m_gui,E_PG_MENU,m_asPage5Elem,MAX_ELEM_PG_MENU_RAM,m_asPage5ElemRef,MAX_ELEM_PG_MENU);
  gslc_PageAdd(&m_gui,E_PG_SWR_CHART,m_asPage7Elem,MAX_ELEM_PG_SWR_CHART_RAM,m_asPage7ElemRef,MAX_ELEM_PG_SWR_CHART);
  gslc_PageAdd(&m_gui,E_PG_MSBOX,m_asPopup1Elem,MAX_ELEM_PG_MSBOX_RAM,m_asPopup1ElemRef,MAX_ELEM_PG_MSBOX);
  gslc_PageAdd(&m_gui,E_PG_WIFI,m_asPage8Elem,MAX_ELEM_PG_WIFI_RAM,m_asPage8ElemRef,MAX_ELEM_PG_WIFI);
  gslc_PageAdd(&m_gui,E_PG_NUMKEYPAD,m_asPopup2Elem,MAX_ELEM_PG_NUMKEYPAD_RAM,m_asPopup2ElemRef,MAX_ELEM_PG_NUMKEYPAD);
  gslc_PageAdd(&m_gui,E_PG_POPUP_FS,m_asPopup3Elem,MAX_ELEM_PG_POPUP_FS_RAM,m_asPopup3ElemRef,MAX_ELEM_PG_POPUP_FS);
  gslc_PageAdd(&m_gui,E_PG_MOTOR_CFG,m_asPage9Elem,MAX_ELEM_PG_MOTOR_CFG_RAM,m_asPage9ElemRef,MAX_ELEM_PG_MOTOR_CFG);
  gslc_PageAdd(&m_gui,E_PG_BASIC_SETTING,m_asPage10Elem,MAX_ELEM_PG_BASIC_SETTING_RAM,m_asPage10ElemRef,MAX_ELEM_PG_BASIC_SETTING);
  gslc_PageAdd(&m_gui,E_PG_POP_PRG,m_asPopup4Elem,MAX_ELEM_PG_POP_PRG_RAM,m_asPopup4ElemRef,MAX_ELEM_PG_POP_PRG);
  gslc_PageAdd(&m_gui,E_PG_BFO,m_asPage11Elem,MAX_ELEM_PG_BFO_RAM,m_asPage11ElemRef,MAX_ELEM_PG_BFO);
  gslc_PageAdd(&m_gui,E_PG_SWR_CAL,m_asPage12Elem,MAX_ELEM_PG_SWR_CAL_RAM,m_asPage12ElemRef,MAX_ELEM_PG_SWR_CAL);
  gslc_PageAdd(&m_gui,E_POP_KEYPAD_NUM,m_asKeypadNumElem,1,m_asKeypadNumElemRef,1);  // KeyPad
  gslc_PageAdd(&m_gui,E_POP_KEYPAD_ALPHA,m_asKeypadAlphaElem,1,m_asKeypadAlphaElemRef,1);  // KeyPad

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
   
  // Create E_ELEM_BOX16 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX16,E_PG_MAIN,(gslc_tsRect){2,2,316,38});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLUE_DK4,GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT182 runtime modifiable text
  static char m_sDisplayText182[21] = "192.168.1.100";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT182,E_PG_MAIN,(gslc_tsRect){150,22,80,12},
    (char*)m_sDisplayText182,21,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_ORANGE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  m_pElemIPAddr0 = pElemRef;
  
  // Create E_ELEM_TEXT183 runtime modifiable text
  static char m_sDisplayText183[6] = "IP:";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT183,E_PG_MAIN,(gslc_tsRect){120,22,31,10},
    (char*)m_sDisplayText183,6,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3);
  p_elem_IP_addr165_183 = pElemRef;
  
  // Create E_ELEM_TEXT184 runtime modifiable text
  static char m_sDisplayText184[31] = "-------";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT184,E_PG_MAIN,(gslc_tsRect){150,9,80,12},
    (char*)m_sDisplayText184,31,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_ORANGE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  m_pElem_SSID0 = pElemRef;
  
  // Create E_ELEM_TEXT185 runtime modifiable text
  static char m_sDisplayText185[6] = "TRX:";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT185,E_PG_MAIN,(gslc_tsRect){6,9,31,10},
    (char*)m_sDisplayText185,6,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3);
  m_pElemOutTxt185 = pElemRef;
  
  // Create E_ELEM_TEXT186 runtime modifiable text
  static char m_sDisplayText186[6] = "Ant:";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT186,E_PG_MAIN,(gslc_tsRect){6,22,31,10},
    (char*)m_sDisplayText186,6,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3);
  m_pElemOutTxt186 = pElemRef;
  
  // Create E_ELEM_TEXT187 runtime modifiable text
  static char m_sDisplayText187[6] = "1";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT187,E_PG_MAIN,(gslc_tsRect){36,22,80,12},
    (char*)m_sDisplayText187,6,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_ORANGE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLUE_DK4,GSLC_COL_TEAL);
  m_pElemAntIndex = pElemRef;
  
  // Create E_ELEM_TEXT188 runtime modifiable text
  static char m_sDisplayText188[6] = "WiFi";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT188,E_PG_MAIN,(gslc_tsRect){120,9,31,10},
    (char*)m_sDisplayText188,6,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3);
  p_elem_IP_addr165_179_188 = pElemRef;
  
  // Create E_ELEM_TEXT189 runtime modifiable text
  static char m_sDisplayText189[31] = "-------";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT189,E_PG_MAIN,(gslc_tsRect){36,9,80,10},
    (char*)m_sDisplayText189,31,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_ORANGE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  m_pElem_TrxName = pElemRef;
  
  // Create E_ELEM_BTN118 button with modifiable text label
  static char m_strbtn118[6] = "MENU";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN118,E_PG_MAIN,
    (gslc_tsRect){258,4,58,32},
    (char*)m_strbtn118,6,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_RED_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  m_pElemBtnMenu = pElemRef;
   
  // Create E_ELEM_BOX17 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX17,E_PG_MAIN,(gslc_tsRect){1,200,318,39});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLUE_DK4,GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  
  // create E_ELEM_BTN119 button with text label
  static char m_strbtnF0[16] = "+";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN119,E_PG_MAIN,
    (gslc_tsRect){40,202,61,34},(char*)m_strbtnF0,16,E_SEVEN_SEGMENT8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_GRAY_DK2,GSLC_COL_BLUE_DK1);
  m_pElemPF0 = pElemRef;
  
  // create E_ELEM_BTN120 button with text label
  static char m_strbtnF1[16] = "+";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN120,E_PG_MAIN,
    (gslc_tsRect){101,202,61,34},(char*)m_strbtnF1,16,E_SEVEN_SEGMENT8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_GRAY_DK2,GSLC_COL_BLUE_DK1);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  m_pElemPF1 = pElemRef;
  
  // create E_ELEM_BTN121 button with text label
   static char m_strbtnF2[16] = "+";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN121,E_PG_MAIN,
    (gslc_tsRect){161,202,61,34},(char*)m_strbtnF2,16,E_SEVEN_SEGMENT8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3,GSLC_COL_GRAY_DK2,GSLC_COL_BLUE_DK1);
  m_pElemPF2 = pElemRef;
  
  // create E_ELEM_BTN122 button with text label
   static char m_strbtnF3[16] = "+";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN122,E_PG_MAIN,
    (gslc_tsRect){221,202,61,34},(char*)m_strbtnF3,16,E_SEVEN_SEGMENT8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_GRAY_DK2,GSLC_COL_BLUE_DK1);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  m_pElemPF3 = pElemRef;
  
 
  // create E_ELEM_BTN123 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN123,E_PG_MAIN,
    (gslc_tsRect){285,202,35,35},(char*)">",0,E_BUILTIN5X8,&CbBtnCommon);
  m_pElemNextPage = pElemRef;
   
  // Create E_ELEM_BOX18 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX18,E_PG_MAIN,(gslc_tsRect){1,41,318,148});
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  
  // create E_ELEM_BTN124 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN124,E_PG_MAIN,
    (gslc_tsRect){1,202,35,35},(char*)"<",0,E_BUILTIN5X8,&CbBtnCommon);
  m_pElemPrevPage = pElemRef;

 
   // create E_ELEM_BTN155 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN155,E_PG_MAIN,
    (gslc_tsRect){300,140,20,20},(char*)"-",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_ORANGE,GSLC_COL_GREEN_DK2,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN156 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN156,E_PG_MAIN,
    (gslc_tsRect){300,70,20,20},(char*)"+",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_ORANGE,GSLC_COL_RED,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
 

 

  // Create E_ELEM_TEXT194 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT194,E_PG_MAIN,(gslc_tsRect){35,45,100,10},
    (char*)"FREQUENCY",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK4);
  
  // Create E_ELEM_TEXT195 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT195,E_PG_MAIN,(gslc_tsRect){35,110,100,10},
    (char*)"SWR",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK4);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT196 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT196,E_PG_MAIN,(gslc_tsRect){185,45,130,10},
    (char*)"FORWARD POWER",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK4);
  
  // Create E_ELEM_TEXT197 runtime modifiable text
  static char m_sDisplayText197[11] = "1024";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT197,E_PG_MAIN,(gslc_tsRect){170,120,110,50},
    (char*)m_sDisplayText197,11,E_SEVEN_SEGMENT18);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_CYAN);
  m_eleSWRREV = pElemRef;
  
  // Create E_ELEM_TEXT198 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT198,E_PG_MAIN,(gslc_tsRect){130,55,20,50},
    (char*)"Mhz",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2);
  
  // Create E_ELEM_TEXT199 runtime modifiable text
  static char m_sDisplayText199[6] = "mW";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT199,E_PG_MAIN,(gslc_tsRect){280,120,20,50},
    (char*)m_sDisplayText199,6,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2);
  m_pElemREFunit = pElemRef;
  
  // Create E_ELEM_TEXT200 runtime modifiable text
  static char m_sDisplayText200[6] = "TRX";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT200,E_PG_MAIN,(gslc_tsRect){130,45,31,10},
    (char*)m_sDisplayText200,6,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED_DK3);
  m_pElemFreqSrc = pElemRef;
  
  // Create E_ELEM_TEXT201 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT201,E_PG_MAIN,(gslc_tsRect){185,110,130,10},
    (char*)"REFLECTION POWER",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK4);
  
  // Create E_ELEM_TEXT202 runtime modifiable text
  static char m_sDisplayText202[11] = "0.000";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT202,E_PG_MAIN,(gslc_tsRect){20,55,110,50},
    (char*)m_sDisplayText202,11,E_SEVEN_SEGMENT18);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_CYAN);
  m_ele_TRXFreq = pElemRef;
  
  // Create E_ELEM_TEXT203 runtime modifiable text
  static char m_sDisplayText203[11] = "1";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT203,E_PG_MAIN,(gslc_tsRect){20,120,130,50},
    (char*)m_sDisplayText203,11,E_SEVEN_SEGMENT18);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_CYAN);
  m_ele_SWR = pElemRef;
  
  // Create E_ELEM_TEXT204 runtime modifiable text
  static char m_sDisplayText204[11] = "0.000";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT204,E_PG_MAIN,(gslc_tsRect){170,55,110,50},
    (char*)m_sDisplayText204,11,E_SEVEN_SEGMENT18);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_CYAN);
  m_eleSWRFWD = pElemRef;
  
  // Create E_ELEM_TEXT205 runtime modifiable text
  static char m_sDisplayText205[6] = "mW";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT205,E_PG_MAIN,(gslc_tsRect){280,55,20,50},
    (char*)m_sDisplayText205,6,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2);
  m_pElemFWDUnit = pElemRef;
  
  // Create E_ELEM_TEXT171 runtime modifiable text
  static char m_sDisplayText171[101] = "tip";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT171,E_PG_MAIN,(gslc_tsRect){1,188,318,11},
    (char*)m_sDisplayText171,101,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLUE_LT1,GSLC_COL_BLACK);
  m_pElemTipInfo = pElemRef;

  // Create progress bar E_ELEM_PROGRESS1 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_PROGRESS1,E_PG_MAIN,&m_sXBarGauge1,
    (gslc_tsRect){58,178,210,8},0,100,0,GSLC_COL_RED,false);
  m_pElemProgress1 = pElemRef;
  
  // Create E_ELEM_TEXT206 runtime modifiable text
  static char m_sDisplayText206[7] = "000000";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT206,E_PG_MAIN,(gslc_tsRect){20,177,37,10},
    (char*)m_sDisplayText206,7,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  m_pElemCurrentPos = pElemRef;
  
  // Create E_ELEM_TEXT207 runtime modifiable text
  static char m_sDisplayText207[7] = "000000";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT207,E_PG_MAIN,(gslc_tsRect){270,176,37,10},
    (char*)m_sDisplayText207,7,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  m_pElem_MaxPos = pElemRef;
  
  // Create radio button E_ELEM_RADIO5
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO5,E_PG_MAIN,&m_asXRadio5,
    (gslc_tsRect){155,70,10,10},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_GREEN,true);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRBFreqSrc = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_RADIO
  
   
  // Create E_ELEM_BOX8 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX8,E_PG_RADIO,(gslc_tsRect){0,0,320,240});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  
  // create E_ELEM_BTN_LINKTEST button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_LINKTEST,E_PG_RADIO,
    (gslc_tsRect){240,150,70,30},(char*)"Link test",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_GREEN_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemLinkTest = pElemRef;
  
  // create E_ELEM_BTN_TRXOK button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_TRXOK,E_PG_RADIO,
    (gslc_tsRect){240,200,70,30},(char*)"SAVE",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemTRXOK = pElemRef;
   
  // Create wrapping box for listbox E_ELEM_LISTBOX3 and scrollbar
  pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_RADIO,(gslc_tsRect){16,24,200,205});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_BLACK,GSLC_COL_GREEN_DK4);
  
  // Create listbox
  pElemRef = gslc_ElemXListboxCreate(&m_gui,E_ELEM_LISTBOX3,E_PG_RADIO,&m_sListbox3,
    (gslc_tsRect){16+2,24+4,200-4-20,205-7},E_BUILTIN5X8,
    (uint8_t*)&m_acListboxBuf3,sizeof(m_acListboxBuf3),0);
  gslc_ElemXListboxSetSize(&m_gui, pElemRef, 13, 1); // 13 rows, 1 columns
  gslc_ElemXListboxItemsSetSize(&m_gui, pElemRef, -1, 10);
  gslc_ElemSetTxtMarginXY(&m_gui, pElemRef, 5, 5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_BLACK,GSLC_COL_GREEN_DK4);
  gslc_ElemXListboxSetSelFunc(&m_gui, pElemRef, &CbListbox);
  gslc_ElemXListboxItemsSetGap(&m_gui, pElemRef, 5,GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pElemListbox1_3 = pElemRef;

  // Create vertical scrollbar for listbox
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_LISTSCROLL1,E_PG_RADIO,&m_sListScroll3,
          (gslc_tsRect){16+200-2-20,24+4,20,205-8},0,20,0,5,true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BROWN,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pListSlider1 = pElemRef;
  
  // Create E_ELEM_TEXT122 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT122,E_PG_RADIO,(gslc_tsRect){16,14,61,10},
    (char*)"RADIO LIST",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_TEXT123 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT123,E_PG_RADIO,(gslc_tsRect){240,30,43,10},
    (char*)"ADDRESS",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_NUMINPUT8 numeric input field
  static char m_sInputNumber8[5] = "00";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT8,E_PG_RADIO,(gslc_tsRect){240,50,70,25},
    (char*)m_sInputNumber8,5,E_SEVEN_SEGMENT8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElem_ICOM_Addr8 = pElemRef;
  
  // create E_ELEM_BTN69 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN69,E_PG_RADIO,
    (gslc_tsRect){285,0,35,25},(char*)"X",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT264 runtime modifiable text
  static char m_sDisplayText264[31] = " ";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT264,E_PG_RADIO,(gslc_tsRect){240,100,70,15},
    (char*)m_sDisplayText264,31,E_BUILTIN5X8);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  m_pElemOldTRX = pElemRef;
  
  // Create E_ELEM_TEXT265 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT265,E_PG_RADIO,(gslc_tsRect){240,90,73,10},
    (char*)"TRX Selected",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);

  // -----------------------------------
  // PAGE: E_PG_ANT
  
   
  // Create E_ELEM_BOX3 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX3,E_PG_ANT,(gslc_tsRect){0,0,320,240});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  
  // create E_ELEM_BTN_SWITCH_ANT button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_SWITCH_ANT,E_PG_ANT,
    (gslc_tsRect){210,200,80,30},(char*)"SWITCH !",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_BLUE,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemSwitchFreq = pElemRef;
   
  // Create wrapping box for listbox E_ELEM_LISTBOX_FREQ and scrollbar
  pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_ANT,(gslc_tsRect){20,53,160,120});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_GREEN_DK4);
  
  // Create listbox
  pElemRef = gslc_ElemXListboxCreate(&m_gui,E_ELEM_LISTBOX_FREQ,E_PG_ANT,&m_sListbox2,
    (gslc_tsRect){20+2,53+4,160-4-20,120-7},E_NOTOSERIF8,
    (uint8_t*)&m_acListboxBuf2,sizeof(m_acListboxBuf2),0);
  gslc_ElemXListboxSetSize(&m_gui, pElemRef, 5, 1); // 5 rows, 1 columns
  gslc_ElemXListboxItemsSetSize(&m_gui, pElemRef, -1, 10);
  gslc_ElemSetTxtMarginXY(&m_gui, pElemRef, 5, 5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_GREEN_DK4);
  gslc_ElemXListboxSetSelFunc(&m_gui, pElemRef, &CbListbox);
  gslc_ElemXListboxItemsSetGap(&m_gui, pElemRef, 5,GSLC_COL_BLACK);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pElemListboxFreq = pElemRef;

  // Create vertical scrollbar for listbox
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_LISTSCROLL2,E_PG_ANT,&m_sListScroll2,
          (gslc_tsRect){20+160-2-20,53+4,20,120-8},0,11,0,5,true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pListSlider2 = pElemRef;
  
  // Create E_ELEM_TEXT110 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT110,E_PG_ANT,(gslc_tsRect){20,33,127,10},
    (char*)"PRESET FREQUENCY LIST",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // create E_ELEM_BTN54 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN54,E_PG_ANT,
    (gslc_tsRect){10,200,70,30},(char*)"ADD FREQ",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemAddFreq = pElemRef;
  
  // create E_ELEM_BTN55 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN55,E_PG_ANT,
    (gslc_tsRect){90,200,70,30},(char*)"DEL FREQ",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_ORANGE,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemRemFreq = pElemRef;
  
  // create E_ELEM_BTN56 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN56,E_PG_ANT,
    (gslc_tsRect){9,3,68,20},(char*)"ANT 1",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_YELLOW,GSLC_COL_RED,GSLC_COL_BLUE_DK1);
  m_pElemAntPage1 = pElemRef;
  
  // create E_ELEM_BTN57 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN57,E_PG_ANT,
    (gslc_tsRect){79,3,68,20},(char*)"ANT 2",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_GRAY,GSLC_COL_BLUE_DK1);
  m_pElemAntPage2 = pElemRef;
  
  // create E_ELEM_BTN58 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN58,E_PG_ANT,
    (gslc_tsRect){149,3,68,20},(char*)"ANT 3",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_GRAY,GSLC_COL_BLUE_DK1);
  m_pElemAntPage3 = pElemRef;
  
  // create E_ELEM_BTN64 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN64,E_PG_ANT,
    (gslc_tsRect){285,0,35,25},(char*)"X",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN65 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN65,E_PG_ANT,
    (gslc_tsRect){210,100,80,35},(char*)"FIND HOME",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_YELLOW,GSLC_COL_GREEN_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
   
  // create checkbox E_ELEM_CHECK2
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK2,E_PG_ANT,&m_asXCheck2,
    (gslc_tsRect){220,160,12,12},false,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_RED,true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemCBCheckBox = pElemRef;
  
  // Create E_ELEM_TEXT155 runtime modifiable text
  static char m_sDisplayText155[7] = "------";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT155,E_PG_ANT,(gslc_tsRect){260,180,37,10},
    (char*)m_sDisplayText155,7,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  p_ElemSteps = pElemRef;
  
  // Create E_ELEM_TEXT156 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT156,E_PG_ANT,(gslc_tsRect){180,180,67,10},
    (char*)"Total steps",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK4);
  
  // Create E_ELEM_TEXT208 runtime modifiable text
  static char m_sDisplayText208[7] = "------";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT208,E_PG_ANT,(gslc_tsRect){110,180,37,10},
    (char*)m_sDisplayText208,7,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  p_ElemStepsCur = pElemRef;
  
  // Create E_ELEM_TEXT209 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT209,E_PG_ANT,(gslc_tsRect){10,180,91,10},
    (char*)"Target position",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK4);
  
  // create E_ELEM_BTN131 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN131,E_PG_ANT,
    (gslc_tsRect){210,50,80,35},(char*)"MOTOR CFG",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_YELLOW,GSLC_COL_RED,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

  // -----------------------------------
  // PAGE: E_PG_MENU
  
   
  // Create E_ELEM_BOX6 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX6,E_PG_MENU,(gslc_tsRect){0,0,320,240});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  
  // create E_ELEM_BTN70 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN70,E_PG_MENU,
    (gslc_tsRect){285,0,35,25},(char*)"X",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_BTN72 button with modifiable text label
  static char m_strbtn72[21] = "WIFI SETTING";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN72,E_PG_MENU,
    (gslc_tsRect){123,115,80,40},
    (char*)m_strbtn72,21,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_ORANGE,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtn72 = pElemRef;
  
  // Create E_ELEM_BTN115 button with modifiable text label
  static char m_strbtn115[21] = "TRX  SETTING";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN115,E_PG_MENU,
    (gslc_tsRect){23,56,130,40},
    (char*)m_strbtn115,21,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT2,GSLC_COL_RED,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_ele_BTN_TRX115 = pElemRef;
  
  // Create E_ELEM_BTN116 button with modifiable text label
  static char m_strbtn116[21] = "ANT SETTING";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN116,E_PG_MENU,
    (gslc_tsRect){168,56,130,40},
    (char*)m_strbtn116,21,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLUE_DK3,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_ele_ANTID116 = pElemRef;
  
  // Create E_ELEM_BTN125 button with modifiable text label
  static char m_strbtn125[21] = "SWR ANALYZER";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN125,E_PG_MENU,
    (gslc_tsRect){23,115,80,40},
    (char*)m_strbtn125,21,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_MAGENTA,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtn72_125 = pElemRef;
  
  // create E_ELEM_BTN129 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN129,E_PG_MENU,
    (gslc_tsRect){228,115,70,100},(char*)"OTA UPGRADE",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GREEN_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemOTA129 = pElemRef;
  
  // create E_ELEM_BTN136 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN136,E_PG_MENU,
    (gslc_tsRect){23,174,80,40},(char*)"FREQ GEN",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemOTA129_136 = pElemRef;
  
  // Create E_ELEM_BTN139 button with modifiable text label
  static char m_strbtn139[21] = "MISC SETTING";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN139,E_PG_MENU,
    (gslc_tsRect){123,174,80,40},
    (char*)m_strbtn139,21,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_PURPLE,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtn72_139 = pElemRef;
  
  // Create E_ELEM_TEXT260 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT260,E_PG_MENU,(gslc_tsRect){20,15,97,10},
    (char*)"Firmware Version",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT261 runtime modifiable text
  static char m_sDisplayText261[61] = "--";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT261,E_PG_MENU,(gslc_tsRect){20,30,280,15},
    (char*)m_sDisplayText261,61,E_BUILTIN5X8);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_GRAY_DK3,GSLC_COL_BLACK);
  m_pElemOutTxt259_261 = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_SWR_CHART
  
   
  // Create E_ELEM_BOX13 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX13,E_PG_SWR_CHART,(gslc_tsRect){0,0,320,240});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  
  // create E_ELEM_BTN66 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN66,E_PG_SWR_CHART,
    (gslc_tsRect){285,0,35,25},(char*)"X",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT157 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT157,E_PG_SWR_CHART,(gslc_tsRect){6,213,31,10},
    (char*)"Start",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_TEXT158 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT158,E_PG_SWR_CHART,(gslc_tsRect){6,223,55,10},
    (char*)"Freq(Mhz)",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_TEXT159 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT159,E_PG_SWR_CHART,(gslc_tsRect){100,216,25,10},
    (char*)"Stop",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_TEXT160 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT160,E_PG_SWR_CHART,(gslc_tsRect){100,226,55,10},
    (char*)"Freq(Mhz)",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_TEXT161 runtime modifiable text
  static char m_sDisplayText161[16] = "7.3";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT161,E_PG_SWR_CHART,(gslc_tsRect){150,220,40,15},
    (char*)m_sDisplayText161,16,E_BUILTIN5X8);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pElem_MotorPos = pElemRef;
  
  // Create E_ELEM_TEXT162 runtime modifiable text
  static char m_sDisplayText162[81] = "SWR Meter";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT162,E_PG_SWR_CHART,(gslc_tsRect){80,5,160,15},
    (char*)m_sDisplayText162,81,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemChartTitle = pElemRef;
  
  // create E_ELEM_BTN114 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN114,E_PG_SWR_CHART,
    (gslc_tsRect){265,213,50,25},(char*)"SET",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_ORANGE,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT211 runtime modifiable text
  static char m_sDisplayText211[16] = "7.0";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT211,E_PG_SWR_CHART,(gslc_tsRect){60,220,40,15},
    (char*)m_sDisplayText211,16,E_BUILTIN5X8);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pElemValFreq = pElemRef;
  
  // Create E_ELEM_TEXT212 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT212,E_PG_SWR_CHART,(gslc_tsRect){196,218,31,10},
    (char*)"FStep",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  m_pElemFstep = pElemRef;
  
  // Create E_ELEM_TEXT213 runtime modifiable text
  static char m_sDisplayText213[16] = "5";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT213,E_PG_SWR_CHART,(gslc_tsRect){230,220,30,15},
    (char*)m_sDisplayText213,16,E_BUILTIN5X8);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pElem_MotorPos213 = pElemRef;
  
  // Create E_ELEM_TEXT214 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT214,E_PG_SWR_CHART,(gslc_tsRect){196,228,31,10},
    (char*)"(Khz)",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  m_pElemFstep214 = pElemRef;
   
  // Create E_ELEM_BOX24 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX24,E_PG_SWR_CHART,(gslc_tsRect){1,25,318,185});
  m_pElemGraph_FreqScan = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_MSBOX
  
   
  // Create E_ELEM_BOX7 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX7,E_PG_MSBOX,(gslc_tsRect){0,0,320,240});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  
  // create E_ELEM_MSG_OK button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_MSG_OK,E_PG_MSBOX,
    (gslc_tsRect){110,200,80,25},(char*)"OK",0,E_NOTOSERIF8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
   
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_TEXTBOX3,E_PG_MSBOX,&m_sTextbox3,
    (gslc_tsRect){10,20,320,184},E_NOTOSERIF8,
    (char*)&m_acTextboxBuf3,8,30);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  m_pElemMsgBoxText = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_WIFI
  
   
  // Create E_ELEM_BOX14 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX14,E_PG_WIFI,(gslc_tsRect){0,0,320,240});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT141 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT141,E_PG_WIFI,(gslc_tsRect){9,206,55,10},
    (char*)"WIFI PSK:",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_TEXTINPUT2 text input field
  static char m_sInputText2[21] = "123456789";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXTINPUT2,E_PG_WIFI,(gslc_tsRect){80,200,130,25},
    (char*)m_sInputText2,21,E_BUILTIN5X8);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemtxtPSK = pElemRef;
  
  // create E_ELEM_BTN74 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN74,E_PG_WIFI,
    (gslc_tsRect){285,0,35,25},(char*)"X",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
   
  // Create wrapping box for listbox E_ELEM_LISTBOX4 and scrollbar
  pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_WIFI,(gslc_tsRect){10,40,200,150});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_GREEN_DK3);
  
  // Create listbox
  pElemRef = gslc_ElemXListboxCreate(&m_gui,E_ELEM_LISTBOX4,E_PG_WIFI,&m_sListbox4,
    (gslc_tsRect){10+2,40+4,200-4-20,150-7},E_BUILTIN5X8,
    (uint8_t*)&m_acListboxBuf4,sizeof(m_acListboxBuf4),0);
  gslc_ElemXListboxSetSize(&m_gui, pElemRef, 8, 1); // 8 rows, 1 columns
  gslc_ElemXListboxItemsSetSize(&m_gui, pElemRef, -1, -1);
  gslc_ElemSetTxtMarginXY(&m_gui, pElemRef, 5, 5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_GREEN_DK3);
  gslc_ElemXListboxSetSelFunc(&m_gui, pElemRef, &CbListbox);
  gslc_ElemXListboxItemsSetGap(&m_gui, pElemRef, 5,GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pElemListboxWifi = pElemRef;

  // Create vertical scrollbar for listbox
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_LISTSCROLL4,E_PG_WIFI,&m_sListScroll4,
          (gslc_tsRect){10+200-2-20,40+4,20,150-8},0,30,0,5,true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pListSlider4 = pElemRef;
  
  // create E_ELEM_BTN113 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN113,E_PG_WIFI,
    (gslc_tsRect){240,40,70,25},(char*)"Refresh",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_ORANGE,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT174 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT174,E_PG_WIFI,(gslc_tsRect){10,15,121,10},
    (char*)"Wifi List(2.4G only)",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // create E_ELEM_BTN128 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN128,E_PG_WIFI,
    (gslc_tsRect){240,200,70,30},(char*)"Save",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemWiFiSave = pElemRef;
  
  // Create E_ELEM_TEXT230 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT230,E_PG_WIFI,(gslc_tsRect){236,136,61,10},
    (char*)"WIFI SSID:",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_TEXT231 runtime modifiable text
  static char m_sDisplayText231[21] = "123456ABCDEF";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT231,E_PG_WIFI,(gslc_tsRect){236,146,75,15},
    (char*)m_sDisplayText231,21,E_BUILTIN5X8);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pElemSSIDConf227_231 = pElemRef;
  
  // Create E_ELEM_TEXT232 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT232,E_PG_WIFI,(gslc_tsRect){237,163,19,10},
    (char*)"PSK",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_TEXT233 runtime modifiable text
  static char m_sDisplayText233[21] = "123456ABCDEF";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT233,E_PG_WIFI,(gslc_tsRect){236,175,75,15},
    (char*)m_sDisplayText233,21,E_BUILTIN5X8);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pElemPSKConf229_233 = pElemRef;
  
  // Create E_ELEM_TEXT234 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT234,E_PG_WIFI,(gslc_tsRect){235,106,43,10},
    (char*)"System ",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_TEXT235 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT235,E_PG_WIFI,(gslc_tsRect){235,117,43,10},
    (char*)"setting",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);

  // -----------------------------------
  // PAGE: E_PG_NUMKEYPAD
  
   
  // Create E_ELEM_BOX15 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX15,E_PG_NUMKEYPAD,(gslc_tsRect){1,1,318,238});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  
  // create E_ELEM_BTN_NUM1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_NUM1,E_PG_NUMKEYPAD,
    (gslc_tsRect){34,84,45,25},(char*)"1",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_NUM2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_NUM2,E_PG_NUMKEYPAD,
    (gslc_tsRect){94,84,45,25},(char*)"2",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_NUM3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_NUM3,E_PG_NUMKEYPAD,
    (gslc_tsRect){154,84,45,25},(char*)"3",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_NUM4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_NUM4,E_PG_NUMKEYPAD,
    (gslc_tsRect){34,124,45,25},(char*)"4",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_NUM5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_NUM5,E_PG_NUMKEYPAD,
    (gslc_tsRect){94,124,45,25},(char*)"5",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_NUM6 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_NUM6,E_PG_NUMKEYPAD,
    (gslc_tsRect){154,124,45,25},(char*)"6",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_NUM7 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_NUM7,E_PG_NUMKEYPAD,
    (gslc_tsRect){34,164,45,25},(char*)"7",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_NUM8 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_NUM8,E_PG_NUMKEYPAD,
    (gslc_tsRect){94,164,45,25},(char*)"8",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_NUM9 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_NUM9,E_PG_NUMKEYPAD,
    (gslc_tsRect){154,164,45,25},(char*)"9",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_NUMDOT button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_NUMDOT,E_PG_NUMKEYPAD,
    (gslc_tsRect){34,204,45,25},(char*)".",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_NUM0 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_NUM0,E_PG_NUMKEYPAD,
    (gslc_tsRect){94,204,45,25},(char*)"0",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_MHZ button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_MHZ,E_PG_NUMKEYPAD,
    (gslc_tsRect){214,84,45,25},(char*)"MHZ",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_GREEN_DK3,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_BKSP button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_BKSP,E_PG_NUMKEYPAD,
    (gslc_tsRect){214,125,45,25},(char*)"BKSP",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_RED_DK2,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_ENT button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_ENT,E_PG_NUMKEYPAD,
    (gslc_tsRect){154,204,105,25},(char*)"Enter",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_ORANGE,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT153 runtime modifiable text
  static char m_sDisplayText153[21] = " ";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT153,E_PG_NUMKEYPAD,(gslc_tsRect){34,25,200,45},
    (char*)m_sDisplayText153,21,E_SEVEN_SEGMENT12);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN);
  p_Elem_InputString = pElemRef;
  
  // Create E_ELEM_TEXT154 runtime modifiable text
  static char m_sDisplayText154[5] = "MHz";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT154,E_PG_NUMKEYPAD,(gslc_tsRect){234,25,25,45},
    (char*)m_sDisplayText154,5,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  p_Elem_Unit = pElemRef;
  
  // create E_ELEM_BTN_CLR button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_CLR,E_PG_NUMKEYPAD,
    (gslc_tsRect){214,165,45,25},(char*)"CLR",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_RED_DK2,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN112 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN112,E_PG_NUMKEYPAD,
    (gslc_tsRect){285,0,35,25},(char*)"X",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK1,GSLC_COL_BLUE_DK3,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT178 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT178,E_PG_NUMKEYPAD,(gslc_tsRect){40,10,181,10},
    (char*)"Please enter frequency number:",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK4);

  // -----------------------------------
  // PAGE: E_PG_POPUP_FS
  
   
  // Create E_ELEM_BOX19 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX19,E_PG_POPUP_FS,(gslc_tsRect){1,80,318,160});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT210 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT210,E_PG_POPUP_FS,(gslc_tsRect){2,90,25,10},
    (char*)"BAND",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  
  // create E_ELEM_BTN_FREQOK button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_FREQOK,E_PG_POPUP_FS,
    (gslc_tsRect){230,198,80,30},(char*)"OK",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_RED,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemSWRSetting = pElemRef;

  // Create slider E_ELEM_SLIDER2 
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_ELEM_SLIDER2,E_PG_POPUP_FS,&m_sXSlider2,
          (gslc_tsRect){30,85,280,40},0,100,30,8,false);
  gslc_ElemXSliderSetStyle(&m_gui,pElemRef,true,GSLC_COL_RED,10,15,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_GRAY_DK3,GSLC_COL_BLACK);
  m_pElemSliderBand = pElemRef;
  
  // Create E_ELEM_TEXT215 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT215,E_PG_POPUP_FS,(gslc_tsRect){75,134,25,10},
    (char*)"Band",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_TEXT216 runtime modifiable text
  static char m_sDisplayText216[5] = "----";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT216,E_PG_POPUP_FS,(gslc_tsRect){110,132,50,18},
    (char*)m_sDisplayText216,5,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  m_pElemBand = pElemRef;
  
  // Create E_ELEM_TEXT217 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT217,E_PG_POPUP_FS,(gslc_tsRect){160,134,7,10},
    (char*)"m",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemBandMeter = pElemRef;
  
  // Create E_ELEM_TEXT218 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT218,E_PG_POPUP_FS,(gslc_tsRect){8,163,91,10},
    (char*)"Start Frequency",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_NUMINPUT11 numeric input field
  static char m_sInputNumber11[6] = "7.0";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT11,E_PG_POPUP_FS,(gslc_tsRect){110,158,80,18},
    (char*)m_sInputNumber11,6,E_BUILTIN10X16);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN_DK2);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemValFS0 = pElemRef;
  
  // Create E_ELEM_TEXT220 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT220,E_PG_POPUP_FS,(gslc_tsRect){12,185,85,10},
    (char*)"Stop Frequency",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_NUMINPUT12 numeric input field
  static char m_sInputNumber12[6] = "7.3";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT12,E_PG_POPUP_FS,(gslc_tsRect){110,183,80,18},
    (char*)m_sInputNumber12,6,E_BUILTIN10X16);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN_DK2);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemValFSE = pElemRef;
  
  // Create E_ELEM_TEXT221 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT221,E_PG_POPUP_FS,(gslc_tsRect){45,208,55,10},
    (char*)"Freq Step",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_NUMINPUT13 numeric input field
  static char m_sInputNumber13[6] = "5";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT13,E_PG_POPUP_FS,(gslc_tsRect){110,208,50,18},
    (char*)m_sInputNumber13,6,E_BUILTIN10X16);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN_DK2);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemValFStep = pElemRef;
  
  // Create E_ELEM_TEXT236 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT236,E_PG_POPUP_FS,(gslc_tsRect){190,162,19,10},
    (char*)"Mhz",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT237 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT237,E_PG_POPUP_FS,(gslc_tsRect){190,185,19,10},
    (char*)"Mhz",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT238 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT238,E_PG_POPUP_FS,(gslc_tsRect){160,210,19,10},
    (char*)"KHz",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // create E_ELEM_BTN154 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN154,E_PG_POPUP_FS,
    (gslc_tsRect){230,150,80,30},(char*)"Meter Adjust",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3,GSLC_COL_GREEN_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemSWRSetting154 = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_MOTOR_CFG
  
   
  // Create E_ELEM_BOX21 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX21,E_PG_MOTOR_CFG,(gslc_tsRect){1,1,318,238});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  
  // create E_ELEM_BTN133 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN133,E_PG_MOTOR_CFG,
    (gslc_tsRect){285,0,35,25},(char*)"X",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN134 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN134,E_PG_MOTOR_CFG,
    (gslc_tsRect){230,190,80,40},(char*)"Save & Close",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

  // Create seekbar E_ELEM_SEEKBAR2 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_SEEKBAR2,E_PG_MOTOR_CFG,&m_sXSeekbar2,
    (gslc_tsRect){86,58,150,30},50,2000,1500,
    4,2,8,GSLC_COL_RED,GSLC_COL_GRAY,GSLC_COL_RED,false);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,GSLC_COL_BLUE_LT4,false,GSLC_COL_GRAY,
    0,10,GSLC_COL_GRAY);
  m_pElemSeekbarRMS = pElemRef;

  // Create seekbar E_ELEM_SEEKBAR3 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_SEEKBAR3,E_PG_MOTOR_CFG,&m_sXSeekbar3,
    (gslc_tsRect){86,98,150,30},500,2000,800,
    4,2,8,GSLC_COL_YELLOW,GSLC_COL_GRAY,GSLC_COL_YELLOW,false);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,GSLC_COL_BLUE_LT4,false,GSLC_COL_GRAY,
    0,10,GSLC_COL_GRAY);
  m_pElemSeekbarSPEED = pElemRef;

  // Create seekbar E_ELEM_SEEKBAR4 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_SEEKBAR4,E_PG_MOTOR_CFG,&m_sXSeekbar4,
    (gslc_tsRect){86,138,150,30},50,255,145,
    4,2,8,GSLC_COL_BLUE,GSLC_COL_GRAY,GSLC_COL_BLUE_DK2,false);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,GSLC_COL_BLUE_LT4,false,GSLC_COL_GRAY,
    0,10,GSLC_COL_GRAY);
  m_pElemSeekbarSTALL = pElemRef;
  
  // Create E_ELEM_TEXT240 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT240,E_PG_MOTOR_CFG,(gslc_tsRect){20,66,25,10},
    (char*)"RMS ",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT241 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT241,E_PG_MOTOR_CFG,(gslc_tsRect){14,9,181,10},
    (char*)"Don't change these parameters ",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_TEXT242 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT242,E_PG_MOTOR_CFG,(gslc_tsRect){14,19,163,10},
    (char*)"unless you know its meaning",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_TEXT243 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT243,E_PG_MOTOR_CFG,(gslc_tsRect){275,65,13,10},
    (char*)"mA",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  
  // Create E_ELEM_TEXT244 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT244,E_PG_MOTOR_CFG,(gslc_tsRect){275,105,13,10},
    (char*)"ms",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  
  // Create E_ELEM_TEXT245 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT245,E_PG_MOTOR_CFG,(gslc_tsRect){20,151,55,10},
    (char*)"Threshold",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT246 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT246,E_PG_MOTOR_CFG,(gslc_tsRect){20,101,25,10},
    (char*)"Step",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT247 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT247,E_PG_MOTOR_CFG,(gslc_tsRect){20,141,31,10},
    (char*)"Stall",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT248 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT248,E_PG_MOTOR_CFG,(gslc_tsRect){20,111,49,10},
    (char*)"Interval",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT249 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT249,E_PG_MOTOR_CFG,(gslc_tsRect){20,76,43,10},
    (char*)"Current",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT250 runtime modifiable text
  static char m_sDisplayText250[7] = "00000";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT250,E_PG_MOTOR_CFG,(gslc_tsRect){235,58,37,30},
    (char*)m_sDisplayText250,7,E_BUILTIN5X8);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  m_pElemOutTxt250 = pElemRef;
  
  // Create E_ELEM_TEXT251 runtime modifiable text
  static char m_sDisplayText251[7] = "00000";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT251,E_PG_MOTOR_CFG,(gslc_tsRect){235,98,37,30},
    (char*)m_sDisplayText251,7,E_BUILTIN5X8);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pElemOutTxt250_251 = pElemRef;
  
  // Create E_ELEM_TEXT252 runtime modifiable text
  static char m_sDisplayText252[7] = "00000";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT252,E_PG_MOTOR_CFG,(gslc_tsRect){235,138,37,30},
    (char*)m_sDisplayText252,7,E_BUILTIN5X8);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE);
  m_pElemOutTxt250_252 = pElemRef;
  
  // create E_ELEM_BTN135 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN135,E_PG_MOTOR_CFG,
    (gslc_tsRect){10,190,80,40},(char*)"Default",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

  // -----------------------------------
  // PAGE: E_PG_BASIC_SETTING
  
   
  // Create E_ELEM_BOX22 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX22,E_PG_BASIC_SETTING,(gslc_tsRect){1,1,318,238});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);

  // Create E_DRAW_LINE5 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE5,E_PG_BASIC_SETTING,25,33,305,33);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2);
  
  // Create radio button E_ELEM_RADIO3
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO3,E_PG_BASIC_SETTING,&m_asXRadio3,
    (gslc_tsRect){161,38,20,20},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_ORANGE,true);
  gslc_ElemSetGroup(&m_gui,pElemRef,GSLC_GROUP_ID_PWR_DISP);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRBRadioButton3 = pElemRef;
  
  // Create E_ELEM_TEXT253 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT253,E_PG_BASIC_SETTING,(gslc_tsRect){181,41,43,10},
    (char*)"in Watt",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create radio button E_ELEM_RADIO4
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO4,E_PG_BASIC_SETTING,&m_asXRadio4,
    (gslc_tsRect){231,38,20,20},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_ORANGE,false);
  gslc_ElemSetGroup(&m_gui,pElemRef,GSLC_GROUP_ID_PWR_DISP);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRBRadioButton2_4 = pElemRef;
  
  // Create E_ELEM_TEXT254 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT254,E_PG_BASIC_SETTING,(gslc_tsRect){251,41,37,10},
    (char*)"in dbm",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT255 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT255,E_PG_BASIC_SETTING,(gslc_tsRect){26,43,115,10},
    (char*)"Power display mode:",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT256 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT256,E_PG_BASIC_SETTING,(gslc_tsRect){28,104,85,10},
    (char*)"Antenna Count:",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);

  // Create E_DRAW_LINE6 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE6,E_PG_BASIC_SETTING,25,60,305,60);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2);
  
  // create E_ELEM_BTN137 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN137,E_PG_BASIC_SETTING,
    (gslc_tsRect){230,190,80,40},(char*)"Save",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT257 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT257,E_PG_BASIC_SETTING,(gslc_tsRect){25,20,79,10},
    (char*)"Basic setting",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // create E_ELEM_BTN138 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN138,E_PG_BASIC_SETTING,
    (gslc_tsRect){285,0,35,25},(char*)"X",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN147 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN147,E_PG_BASIC_SETTING,
    (gslc_tsRect){162,99,40,20},(char*)"1",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_GREEN_DK3,GSLC_COL_BLUE_DK1);
  m_pElemANTC0 = pElemRef;
  
  // create E_ELEM_BTN148 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN148,E_PG_BASIC_SETTING,
    (gslc_tsRect){202,99,40,20},(char*)"2",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_GRAY_DK2,GSLC_COL_BLUE_DK1);
  m_pElemANTC1 = pElemRef;
  
  // create E_ELEM_BTN149 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN149,E_PG_BASIC_SETTING,
    (gslc_tsRect){242,99,40,20},(char*)"3",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_GRAY_DK2,GSLC_COL_BLUE_DK1);
  m_pElemANTC2 = pElemRef;
  
  // Create E_ELEM_TEXT270 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT270,E_PG_BASIC_SETTING,(gslc_tsRect){27,72,109,10},
    (char*)"Motor Stood still:",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
   
  // create checkbox E_ELEM_CHECK3
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK3,E_PG_BASIC_SETTING,&m_asXCheck3,
    (gslc_tsRect){161,67,20,20},false,GSLCX_CHECKBOX_STYLE_BOX,GSLC_COL_RED,true);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemCBCheckBox = pElemRef;

  // Create E_DRAW_LINE7 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE7,E_PG_BASIC_SETTING,25,90,305,90);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2);

  // -----------------------------------
  // PAGE: E_PG_POP_PRG
  

  // Create ring gauge E_ELEM_RINGGAUGE1 
  static char m_sRingText1[11] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE1,E_PG_POP_PRG,&m_sXRingGauge1,
          (gslc_tsRect){110,70,100,100},
          (char*)m_sRingText1,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value
  gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui,pElemRef, GSLC_COL_GREEN_DK3);
  m_pElemXRingGauge1 = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_BFO
  
   
  // Create E_ELEM_BOX23 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX23,E_PG_BFO,(gslc_tsRect){1,1,318,180});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  
  // Create E_ELEM_NUMINPUT14 numeric input field
  static char m_sInputNumber14[10] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT14,E_PG_BFO,(gslc_tsRect){52,22,99,35},
    (char*)m_sInputNumber14,10,E_SEVEN_SEGMENT10);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemValBFO0 = pElemRef;
  
  // Create E_ELEM_TEXT262 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT262,E_PG_BFO,(gslc_tsRect){12,32,19,10},
    (char*)"CH0",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_BTN140 button with modifiable text label
  static char m_strbtn140[11] = "On";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN140,E_PG_BFO,
    (gslc_tsRect){180,20,70,40},
    (char*)m_strbtn140,11,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED_DK3,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnBFO = pElemRef;
  
  // Create E_ELEM_TEXT263 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT263,E_PG_BFO,(gslc_tsRect){155,32,13,10},
    (char*)"Hz",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // create E_ELEM_BTN142 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN142,E_PG_BFO,
    (gslc_tsRect){285,0,35,25},(char*)"X",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_NUMINPUT15 numeric input field
  static char m_sInputNumber15[10] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT15,E_PG_BFO,(gslc_tsRect){52,78,99,35},
    (char*)m_sInputNumber15,10,E_SEVEN_SEGMENT10);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemValBFO1 = pElemRef;
  
  // Create E_ELEM_TEXT266 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT266,E_PG_BFO,(gslc_tsRect){12,88,19,10},
    (char*)"CH1",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_BTN144 button with modifiable text label
  static char m_strbtn144[11] = "On";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN144,E_PG_BFO,
    (gslc_tsRect){180,76,70,40},
    (char*)m_strbtn144,11,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_ORANGE,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnBFOCH1 = pElemRef;
  
  // Create E_ELEM_TEXT267 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT267,E_PG_BFO,(gslc_tsRect){155,88,13,10},
    (char*)"Hz",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_NUMINPUT16 numeric input field
  static char m_sInputNumber16[10] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT16,E_PG_BFO,(gslc_tsRect){52,134,99,35},
    (char*)m_sInputNumber16,10,E_SEVEN_SEGMENT10);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemValBFO2 = pElemRef;
  
  // Create E_ELEM_TEXT268 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT268,E_PG_BFO,(gslc_tsRect){12,144,19,10},
    (char*)"CH2",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3);
  
  // Create E_ELEM_BTN145 button with modifiable text label
  static char m_strbtn145[11] = "On";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN145,E_PG_BFO,
    (gslc_tsRect){180,132,70,40},
    (char*)m_strbtn145,11,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_BLUE_DK3,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnBFOCH2 = pElemRef;
  
  // Create E_ELEM_TEXT269 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT269,E_PG_BFO,(gslc_tsRect){155,144,13,10},
    (char*)"Hz",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_BTN146 button with modifiable text label
  static char m_strbtn146[6] = "TRX";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN146,E_PG_BFO,
    (gslc_tsRect){270,80,40,90},
    (char*)m_strbtn146,6,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemSigSrc146 = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_SWR_CAL
  
   
  // Create E_ELEM_BOX25 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX25,E_PG_SWR_CAL,(gslc_tsRect){1,1,318,238});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_TEAL,GSLC_COL_BLACK);
  
  // create E_ELEM_BTN152 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN152,E_PG_SWR_CAL,
    (gslc_tsRect){220,180,80,40},(char*)"Save",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_NUMINPUT23 numeric input field
  static char m_sInputNumber23[6] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT23,E_PG_SWR_CAL,(gslc_tsRect){181,45,50,20},
    (char*)m_sInputNumber23,6,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemVal17_23 = pElemRef;
  
  // Create E_ELEM_NUMINPUT24 numeric input field
  static char m_sInputNumber24[6] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT24,E_PG_SWR_CAL,(gslc_tsRect){181,75,50,20},
    (char*)m_sInputNumber24,6,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemVal17_18_24 = pElemRef;
  
  // Create E_ELEM_NUMINPUT25 numeric input field
  static char m_sInputNumber25[6] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT25,E_PG_SWR_CAL,(gslc_tsRect){181,105,50,20},
    (char*)m_sInputNumber25,6,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemVal17_19_25 = pElemRef;
  
  // Create E_ELEM_NUMINPUT26 numeric input field
  static char m_sInputNumber26[6] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT26,E_PG_SWR_CAL,(gslc_tsRect){181,135,50,20},
    (char*)m_sInputNumber26,6,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemVal17_20_26 = pElemRef;
  
  // Create E_ELEM_TEXT278 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT278,E_PG_SWR_CAL,(gslc_tsRect){43,47,109,10},
    (char*)"Forward ADC Offset",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT279 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT279,E_PG_SWR_CAL,(gslc_tsRect){43,77,109,10},
    (char*)"Reflect ADC Offset",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT280 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT280,E_PG_SWR_CAL,(gslc_tsRect){43,107,121,10},
    (char*)"Forward Power Offset",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT281 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT281,E_PG_SWR_CAL,(gslc_tsRect){43,137,121,10},
    (char*)"Reflect Power Offset",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT282 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT282,E_PG_SWR_CAL,(gslc_tsRect){233,109,19,10},
    (char*)"dbm",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT283 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT283,E_PG_SWR_CAL,(gslc_tsRect){233,137,19,10},
    (char*)"dbm",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // create E_ELEM_BTN153 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN153,E_PG_SWR_CAL,
    (gslc_tsRect){20,180,80,40},(char*)"Default",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_ORANGE,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT284 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT284,E_PG_SWR_CAL,(gslc_tsRect){80,20,121,10},
    (char*)"SWR Meter Parameters",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_NUM
  
  static gslc_tsXKeyPadCfg_Num sCfg;
  sCfg = gslc_ElemXKeyPadCfgInit_Num();
  gslc_ElemXKeyPadCfgSetFloatEn_Num(&sCfg, true);
  gslc_ElemXKeyPadCfgSetSignEn_Num(&sCfg, true);
  m_pElemKeyPadNum = gslc_ElemXKeyPadCreate_Num(&m_gui, E_ELEM_KEYPAD_NUM, E_POP_KEYPAD_NUM,
    &m_sKeyPadNum, 65, 80, E_BUILTIN5X8, &sCfg);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadNum, &CbKeypad);

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_ALPHA
  
  static gslc_tsXKeyPadCfg_Alpha sCfgTx;
  sCfgTx = gslc_ElemXKeyPadCfgInit_Alpha();
  m_pElemKeyPadAlpha = gslc_ElemXKeyPadCreate_Alpha(&m_gui, E_ELEM_KEYPAD_ALPHA, E_POP_KEYPAD_ALPHA,
    &m_sKeyPadAlpha, 65, 80, E_BUILTIN5X8, &sCfgTx);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadAlpha, &CbKeypad);
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
