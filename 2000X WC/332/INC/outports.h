/* $Header:   D:/SWLab/VMdb/2000Series/INC/OUTPORTS.H_V   2.17   Aug 03 2004 13:12:42   BWadia  $ */
#ifndef OUT_PORTS_H
#define OUT_PORTS_H
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96,97           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/

/*
 ---------------------------- MODULE DESCRIPTION -------------------------------


--------------------------------- REVISIONS -----------------------------------

   Revision #   Date       Author          Description
   ==========   ========   ======          ===========
      0         12/12/94   Mark Lazarewicz Initial release 
      1         04-04-96   BEKymer         PSIDLE was inverted
      2         05-15-96   BEKymer         Add proper function prototyping
      3         09-11-96   LAM             renamed sv_signal to pemd
      4         01-20-97   LAM             Added trsenable, trigswactv
      5         01-26-97   LAM             chged systemfault to pbrelease
      6.2.6     06-24-97   LAM             chged userout3 to missingpartoutput
      6.2.7     06-24-97   LAM             chged userout3 to missingpartoutput
      6.2.8     08-07-97   BEKymer         For now, use user1, user2 & user3
                                           for warning output
                                           (Eventually just user3)
      6.2.9     08.12.97   JBerman         Adding BIT_45CLR for SVOff
                                           And some more defined bits
	  3.0       04.20.99   OFI             Changed for DIAB
	  3.1       08-13-99   JZ              deleted AccessControlOutputPorts and
										   OutPortOn, chngd to void type proto of
										   InitializeOutputPorts
      2.12      11-30-99   BEKymer         Changed bit assignment for:
                                           USEROUT1_SIG_ON_VAL   to BIT_5_SET   from BIT_4_SET                                       
                                           USEROUT1_SIG_OFF_VAL  to BIT_5_CLEAR from BIT_4_CLR
                                           USEROUT2_SIG_ON_VAL   to BIT_6_SET   from BIT_5_SET  
                                           USEROUT2_SIG_OFF_VAL  to BIT_6_CLEAR from BIT_5_CLR
      2.13      02-18-04   VSharma         Added defines for user configurable output.
                                           Added enum OUTPUT_PINS.
      2.14      04-27-04   VSharma         Added prototype for IsOutConfigured().
      2.15      05-03-04   VSharma         Added define for OUTPUT_SYNC_OUT.
      2.16      08-02-04   BEKymer         Add define for OUTPUT_DISABLED
      2.17      08-03-04   JOY             Dummy checkout.
      
                                           

 ------------------------------- DESCRIPTION -----------------------------------

   This file defines the global shadow registers for the write-only
   registers and the routines used to access the registers. Since the registers
   are write-only, an image of what has been put out needs to be continuously 
   maintained.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"             /* extensions to the 'C' Language    */
#include "memap.h"                /* contains defines for startup init */

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/

/* Port definitions */
/* NOTE: port addresses are assigned in access_control_output_port routine   */
/* This is an enumeration of all the memory mapped hardware ports that exist */
/* on the board, which may be accessed via the access control output ports   */
/* library function                                                          */

typedef enum
    {
    CTRL_PORT_0,
    CTRL_PORT_1,
    CTRL_PORT_2,
    } CONTROL_OUTPUT_PORTS_TYPE;

/* mask type definition used for the eight bit output ports */
typedef UINT8 OUTPUT_PORTS_MASK_TYPE;

/* bit settings type definition used for the eight bit output ports */
typedef UINT8 OUTPUT_PORTS_BIT_SETTINGS_TYPE;


/*
 ------------------------------- DEFINES ---------------------------------------
*/                                                                                    

/*
 * These defines contain which port the bit is located in, port mask, and bit settings
 * for the bit(s).
 */

/* Bit mask definitions */
/* NOTE: These represent the bit(s) to be masked, the routine will perform a bit-wise */
/*  inversion to obtain the actual mask used */


/*====================================================================*/               
/* Bit mask definitions                                               */
/*====================================================================*/               

#define BIT_0_MASK       0x0001
#define BIT_1_MASK       0x0002
#define BIT_2_MASK       0x0004
#define BIT_3_MASK       0x0008
#define BIT_4_MASK       0x0010
#define BIT_5_MASK       0x0020
#define BIT_6_MASK       0x0040
#define BIT_7_MASK       0x0080

/*====================================================================*/               
/* Bit Set/Clear definitions                                          */
/*====================================================================*/               
//                                            76543210

#define BIT_0_CLR           0x00FE         // 11111110  J.B
#define BIT_1_CLR           0x00FD         // 11111101  J.B
#define BIT_2_CLR           0x00FB         // 11111011  J.B
#define BIT_3_CLR           0x00F7         // 11110111  J.B
#define BIT_4_CLR           0x00EF         // 11101111  J.B
#define BIT_5_CLR           0x00DF         // 11011111  J.B
#define BIT_6_CLR           0x00BF         // 10111111  J.B
#define BIT_7_CLR           0x007F         // 01111111  J.B

#define BIT_13CLR           0x00F5         // 11110101  J.B
#define BIT_23CLR           0x00F3         // 11110011  J.B
#define BIT_123CR           0x00F1         // 11110001  J.B
#define BIT_45CLR           0x00CF         // 11001111  J.B

#define BIT_13SET           0x000A         // 00001010  J.B

#define BIT_CLEAR           0x0000
#define BIT_0_CLEAR         0x0000
#define BIT_0_SET           0x0001
#define BIT_1_CLEAR         0x0000
#define BIT_1_SET           0x0002
#define BIT_2_CLEAR         0x0000
#define BIT_2_SET           0x0004
#define BIT_3_CLEAR         0x0000
#define BIT_3_SET           0x0008
#define BIT_4_CLEAR         0x0000
#define BIT_4_SET           0x0010
#define BIT_5_CLEAR         0x0000
#define BIT_5_SET           0x0020
#define BIT_6_CLEAR         0x0000
#define BIT_6_SET           0x0040
#define BIT_7_CLEAR         0x0000
#define BIT_7_SET           0x0080

/* 
 * Defines for port access, these defines supply all parameters for the
 * access_control_output_ports routine.
 */

/*====================================================================*/               
/* P0_OUT DEFINITIONS                                                 */
/*====================================================================*/               
/* BITS 0                                                             */
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
                                      
#define EXTERNAL_SEEK_ON_VAL      BIT_0_SET    /* ????????? */
#define EXTERNAL_SEEK_OFF_VAL     BIT_0_CLEAR
/*====================================================================*/               
/* MACROS USED BY CALLERS OF ACCESS CONTROL OUTPUT PORTS              */
/*====================================================================*/


/*====================================================================*/               
/* BITS  1                                                            */
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define RUN_SONICS_SIGNAL_OFF_VAL   BIT_1_CLEAR  /* ?????????? */
#define RUN_SONICS_SIGNAL_ON_VAL    BIT_1_SET


/*====================================================================*/               
/* BITS  2                                                            */
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define OVERLOAD_RESET_SIGNAL_ON_VAL     BIT_2_SET    /* ???????????? */
#define OVERLOAD_RESET_SIGNAL_OFF_VAL    BIT_2_CLEAR


/*====================================================================*/               
/* BITS  3                                                            */
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define TEST_SIGNAL_ON_VAL   BIT_3_SET    /* ???????????? */
#define TEST_SIGNAL_OFF_VAL  BIT_3_CLEAR


/*====================================================================*/                                                                          
/* BIT 4                                                              */
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define SV1_ON_VAL   BIT_4_SET    /* ???????????? */
#define SV1_OFF_VAL  BIT_4_CLEAR

/*====================================================================*/               
/* BIT 5                                                              */
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define SV2_ON_VAL   BIT_5_SET  /* ???????????? */
#define SV2_OFF_VAL  BIT_5_CLEAR

/*====================================================================*/               
/* BITS 6                                                             */
/*====================================================================*/               
#define SV3_ON_VAL   BIT_6_SET  /* ???????????? */
#define SV3_OFF_VAL  BIT_6_CLEAR

/*====================================================================*/               
/* BITS 7                                                             */
/*====================================================================*/               
#define SV4_ON_VAL   BIT_7_SET  /* ???????????? */
#define SV4_OFF_VAL  BIT_7_CLEAR


/*====================================================================*/               
/* MACROS                                                             */
/*====================================================================*/               

#define RUN_SONICS      CTRL_PORT_0 , BIT_1_MASK , RUN_SONICS_SIGNAL_ON_VAL
#define ENABLE_OVERLOAD_RESET CTRL_PORT_0, BIT_2_MASK,OVERLOAD_RESET_SIGNAL_ON_VAL 
#define CLEAR_AUX_ALARMS_PORT0 ~(BAD_PART_SIGNAL_ON_VAL | SUSPECT_PART_SIGNAL_ON_VAL | \
                     ACT_RET_SIGNAL_ON_VAL)
#define SET_AUX_ALARMS_PORT0 (BAD_PART_SIGNAL_ON_VAL | SUSPECT_PART_SIGNAL_ON_VAL | \
                    ACT_RET_SIGNAL_ON_VAL)


#define ALARM_PORT0_MASK (BIT_0_SET | BIT_3_SET | BIT_4_SET | BIT_5_SET)

#define CLEAR_AUX_ALARMS_PORT2 ~(USEROUT1_SIG_ON_VAL | USEROUT2_SIG_ON_VAL)

#define SET_AUX_ALARMS_PORT2 (USEROUT1_SIG_ON_VAL | USEROUT2_SIG_ON_VAL)


#define ALARM_PORT1_MASK (BIT_4_SET | BIT_5_SET | BIT_6_SET)

// #define PSIDLE_VAL BIT_CLEAR

// #define PSIDLE_MASK (BIT_2_SET | BIT_1_SET | BIT_3_SET)
/*====================================================================*/               
/* P1_OUT DEFINITIONS                                                 */
/*====================================================================*/                                                                                                      
/* BITS 0                                                             */               
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define ACT_RET_SIGNAL_ON_VAL   BIT_0_SET    
#define ACT_RET_SIGNAL_OFF_VAL  BIT_0_CLEAR


/*====================================================================*/               
/* MACROS                                                             */
/*====================================================================*/               

/*====================================================================*/               
/* BITS  1                                                            */
/*====================================================================*/               

#define TRIG_SW_ACTV_ON_VAL   BIT_1_SET    
#define TRIG_SW_ACTV_OFF_VAL  BIT_1_CLEAR

/*====================================================================*/               


/*====================================================================*/               
/* BITS  2                                                            */
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define PEMD_ON_VAL   BIT_2_CLEAR    /* ???????????? */
#define PEMD_OFF_VAL  BIT_2_SET

/*====================================================================*/               
/* BITS 3                                                             */                                             
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define BAD_PART_SIGNAL_ON_VAL   BIT_3_SET    /* ???????????? */
#define BAD_PART_SIGNAL_OFF_VAL  BIT_3_CLEAR

/*====================================================================*/               
/* BITS 4                                                             */                                             
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define SUSPECT_PART_SIGNAL_ON_VAL   BIT_4_SET    /* ???????????? */
#define SUSPECT_PART_SIGNAL_OFF_VAL  BIT_4_CLEAR

/*====================================================================*/               
/* BITS 5                                                             */                                             
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define PB_RELEASE_ON_VAL   BIT_5_SET    /* ???????????? */
#define PB_RELEASE_OFF_VAL  BIT_5_CLEAR


/*====================================================================*/               
/* MACROS                                                             */
/*====================================================================*/               


/*====================================================================*/                                                       
/* BIT 6                                                              */
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define POWER_OFF_DELAY_ON_VAL   BIT_6_SET    /* ???????????? */
#define POWER_OFF_DELAY_OFF_VAL  BIT_6_CLEAR


/*====================================================================*/               
/* MACROS                                                             */
/*====================================================================*/               

/*====================================================================*/                                                       
/* BIT 7                                                              */
/*====================================================================*/               
#define TRSENABLE_ON_VAL      BIT_7_SET    
#define TRSENABLE_OFF_VAL     BIT_7_CLEAR

/*====================================================================*/               

   
  
                                         

/*====================================================================*/               
/* P2_OUT                                                             */
/*====================================================================*/               
/* BIT 0                                                              */               
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define G_ALARM_SIG_ON_VAL   BIT_0_SET    /* ???????????? */
#define G_ALARM_SIG_OFF_VAL  BIT_0_CLEAR


/*====================================================================*/               
/* MACROS                                                             */
/*====================================================================*/               


/*====================================================================*/               
/* BIT 1 -                                                            */
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define READY_SIG_ON_VAL   BIT_1_SET    /* ???????????? */
#define READY_SIG_OFF_VAL  BIT_1_CLEAR


/*====================================================================*/               
/* MACROS                                                             */
/*====================================================================*/               


/*====================================================================*/               
/* BITS 2                                                             */               
/*====================================================================*/                                             
/*                                                                    */
/*====================================================================*/               
#define WELD_ON_SIGNAL_VAL   BIT_2_SET    /* ???????????? */
#define WELD_OFF_SIGNAL_VAL  BIT_2_CLEAR

/*====================================================================*/               
/* BIT 3                                                              */
/*====================================================================*/               
/*NOT USED                                                            */
/*====================================================================*/               


/*====================================================================*/               
/* MACROS                                                             */
/*====================================================================*/               


/*====================================================================*/               
/* BITS 4                                                             */
/*====================================================================*/               
/*                                                   `                 */
/*====================================================================*/               
#define USEROUT1_SIG_ON_VAL   BIT_5_SET    /* ???????????? */
#define USEROUT1_SIG_OFF_VAL  BIT_5_CLR

/*====================================================================*/               
/* BIT 5                                                            */
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define USEROUT2_SIG_ON_VAL   BIT_6_SET    /* ???????????? */
#define USEROUT2_SIG_OFF_VAL  BIT_6_CLR


/*====================================================================*/               
/* MACROS                                                             */
/*====================================================================*/               

/*====================================================================*/                                                       
/* BIT 6                                                              */
/*====================================================================*/               
/*                                                                    */
/*====================================================================*/               
#define MISSING_PART_ON_VAL   (BIT_4_CLEAR | BIT_5_CLEAR | BIT_6_CLEAR)
#define MISSING_PART_OFF_VAL  (BIT_4_SET | BIT_5_SET | BIT_6_SET)


/*====================================================================*/               
/* MACROS                                                             */
/*====================================================================*/               

/*====================================================================*/                                                       
/* BIT 7                                                              */
/*====================================================================*/               
/* NOT USED                                                           */
/*====================================================================*/               



/*====================================================================*/               
/*
 * These are the default settings for each of the ports
 */
/*====================================================================*/               
#define CTRL_PORT_0_DEFAULT 0x00
#define CTRL_PORT_1_DEFAULT 0x00
#define CTRL_PORT_2_DEFAULT 0x00

/* Return codes */
#define CONTROL_PORT_NOERROR   0
#define ILLEGAL_PORT_NUMBER    1

/* User Configureabe Output*/
#define OUTPUT_DISABLED         BIT0  // Output disabled
#define OUTPUT_CFMPRESET        BIT1  // Confirm Preset
#define OUTPUT_AMPDECAY         BIT2  // Amplitude Decay
#define OUTPUT_EXT_BEEPER       BIT3  //  External Beeper
#define OUTPUT_CYCLE_OK         BIT4  //  Cycle OK
#define OUTPUT_NO_CYCLEALARM    BIT5  //  No Cycle Alarm
#define OUTPUT_OLDALARM         BIT6  //  Overload Alarm
#define OUTPUT_MDFY_ALARM       BIT7  //  Modify Alarm
#define OUTPUT_NOTE             BIT8  //  Note
#define OUTPUT_MISSING_PART     BIT9  //  Missing Part
#define OUTPUT_SV_INTERLOCK     BIT10 //   SV Inter Lock
#define OUTPUT_SYNC_OUT         BIT11 //   Sync Out

enum OUTPUT_PINS {
   J3PIN36 = 1,
   J3PIN8,
   J3PIN22   };





/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


void InitializeOutputPorts(void);
BOOLEAN IsOutConfigured (UINT16 SelectedOutput);


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* ACCESS_CONTROL_OUTPUT_PORTS_H */
