#ifndef _MLAT22_IO_CTRL_HEADER_
#define _MLAT22_IO_CTRL_HEADER_
#include <PCA95x5.h>


//=======ROTARY INPUT===================
#define ROTARY_A_PIN    PCA95x5::Port::P00        /*in*/
#define ROTARY_B_PIN    PCA95x5::Port::P01        /*in*/
#define ROTARY_SW_PIN   PCA95x5::Port::P02        /*in*/
//======BFO / TRX swtich=================
#define TRX_BFO_SW      PCA95x5::Port::P03        /*out*/

//======Frequency counter divider=======
#define FC_RELAY0       PCA95x5::Port::P04      /*out*/
#define FC_RELAY1       PCA95x5::Port::P05      /*out*/
//=====SYS POWER RELATE=================
#define SYS_PWR_ON      PCA95x5::Port::P06      /*out*/
#define OFF_KEY_DET     PCA95x5::Port::P07      /*in*/

#define ANT_SEL_0       PCA95x5::Port::P10    /*out*/
#define ANT_SEL_1       PCA95x5::Port::P11    /*out*/
#define STEPPER_DIAG    PCA95x5::Port::P12    /*in*/
#define STEPPER_MS1     PCA95x5::Port::P13    /*out*/
#define STEPPER_MS2     PCA95x5::Port::P14    /*out*/
#define STEPPER_EN      PCA95x5::Port::P15    /*out*/
#define STEPPER_SPREAD  PCA95x5::Port::P16    /*out    Low=StealthChop, High=SpreadCycle*/
#define FC_CLR          PCA95x5::Port::P17    /*out*/

#define IOEX_INT_PIN    34                     //IOEX INT pin connected to this pin... 
 

#define OUTPUT_H    PCA95x5::Level::H
#define OUTPUT_L    PCA95x5::Level::L
 


#endif