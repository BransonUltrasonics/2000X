/* $Header:   K:/APPS/PVCS Pro/332new/INC/KEYPAD.H_V   2.25   Dec 05 2003 15:45:34   BKymer  $ */
#ifndef FP_KEY_PAD_H
#define FP_KEY_PAD_H
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*
------------------------------ MODULE DESCRIPTION -----------------------------

------------------------------ REVISIONS --------------------------------------

   Revision #      Date          Author          Description
   ==========      ========      ======          ===========
      0            02/08/96      Mark Lazarewicz Initial release 
      1            05-01-96      BEKymer         Added 'StateChangeFakeOut'
      2            06-12-96      LAM             deleted unused prototypes added
                                                 2c keys                                                                                                                                                                                       
      3            09-19-96      PhilJ           Deleted define NOKEY and
                                                 UPDATEDISP. Added above and
                                                 MENUINDEX0 to KEY_CODE_TYPE.
      4            10-19-96      PhilJ           Changed Run key code to RunKey
      5            12-12-96      PhilJ           Added UPDATETOPLINE, UPDATELINE2,
                                                 UPDATELINE3, UPDATELINE4. Changed
                                                 UPDATEDISP to UPDATEDISPLAY.
      2.10         07-17-97      PhilJ           Chngd UnAssigned1 to SetupKey
      2.11         09-12-97      LAM             added fakekeyint prototype
      2.12         09-19-97      LAM             added keybit mask
      2.13         11-4-97       BJB             Deleted MENUINDEX0
                                                 Added comment that Sel1, 2, 3
                                                  need to be together and in
                                                  order.
      2.14         12/29/97      BJB             Added new messages/keys to
                                                  support remote terminal.
      2.15         01/12/98      BJB             Added messages to support
                                                  "Emergency Stop" text output.
      2.16         04/24/98      BJB             Added many new messages to
                                                  support events in new HD mode.
      2.17         04/30/98      BJB             Added comment that KEY_0 - KEY_9
                                                  must be together.
      2.18         07/02/98      BJB             Added BAD_TRIGGER message.
      2.19         08/21/98      LAM             Added CALIBRATION_ABORTED message.
      2.20         08/28/98      BJB             Removed "key" definitions for
                                                  HD mode messages, now HD uses
                                                  new message format.
      2.21         04/19/99      OFI             Changed for DIAB
      2.22         05/10/99      LAM             added packed for DIAB
      2.23         06-14-00      SCM             Added Restartmenu under KEY_CODE_TYPE.
      2.23.1.0     07/31/03      JOY             Added 'QVGACALIB_KEY' under KEY_CODE_TYPE. 
      2.23.1.1     11/26/03      JOY             Added 'ESTOPMSGRESET' under KEY_CODE_TYPE. 
      2.25         12-05-03      BEKymer         Move 2.23.1.1 to tip as 2.5 for
                                                  Ver9.00b build
                                                  

----------------------------- DESCRIPTIONS ------------------------------------

    
   

---------------------------- INCLUDE FILES ------------------------------------
*/
#include "portable.h"
#include "root.h"




#define KEY_0MASK       BIT0       
#define KEY_1MASK       BIT1        
#define KEY_2MASK       BIT2        
#define KEY_3MASK       BIT3        
#define KEY_4MASK       BIT4        
#define KEY_5MASK       BIT5        
#define KEY_6MASK       BIT6        
#define KEY_7MASK       BIT7        
#define KEY_8MASK       BIT8        
#define KEY_9MASK       BIT9        
#define DPOINTKEYMASK   BIT10       
#define INCKEYMASK      BIT11       
#define DECKEYMASK      BIT12       
#define CLEARKEYMASK    BIT13       
#define ENTERKEYMASK    BIT14       
#define SETUPKEYMASK    BIT15       
#define RESETKEYMASK    BIT16       
#define TESTKEYMASK     BIT17       
#define MAINKEYMASK     BIT18       
#define GOBACKKEYMASK   BIT19       
#define OFFKEYMASK      BIT20       
#define PRINTKEYMASK    BIT21       
#define HORNDOWNKEYMASK BIT22       
#define RUNKEYMASK      BIT23       
#define SELECT1KEYMASK  BIT24       
#define SELECT2KEYMASK  BIT25       
#define SELECT3KEYMASK  BIT26       
#define UNASSIGNED3MASK BIT27       
#define RIGHTKEYMASK    BIT28       
#define LEFTKEYMASK     BIT29       
#define UPKEYMASK       BIT30       
#define DOWNKEYMASK     BIT31       





/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


typedef __packed__ enum         /*  classification of errors in terms of  */
   {                            /*  hardware or software components       */

    KEY_0,                       /* 0x00 */ /* Keys 0-9 must be in sequence */
    KEY_1,                       /* 0x01 */
    KEY_2,                       /* 0x02 */
    KEY_3,                       /* 0x03 */
    KEY_4,                       /* 0x04 */
    KEY_5,                       /* 0x05 */
    KEY_6,                       /* 0x06 */
    KEY_7,                       /* 0x07 */
    KEY_8,                       /* 0x08 */
    KEY_9,                       /* 0x09 */
    DPointKey,                   /* 0x0a */
    IncKey,                      /* 0x0b */
    DecKey,                      /* 0x0c */
    ClearKey,                    /* 0x0d */
    EnterKey,                    /* 0x0e */
    SetupKey,                    /* 0x0f */
    ResetKey,                    /* 0x10 */
    TestKey,                     /* 0x11 */
    MainKey,                     /* 0x12 */
    GoBackKey,                   /* 0x13 */
    OffKey,                      /* 0x14 */
    PrintKey,                    /* 0x15 */
    HornDownKey,                 /* 0x16 */
    RunKey,                      /* 0x17 */
    Select1Key,                  /* 0x18 */  /* Select1, 2, 3 keys must be in sequence */
    Select2Key,                  /* 0x19 */
    Select3Key,                  /* 0x1a */
    UnAssigned3,                 /* 0x1b */
    RightKey,                    /* 0x1c */
    LeftKey,                     /* 0x1d */
    UpKey,                       /* 0x1e */
    DownKey,                     /* 0x1f */
    TermDataKey,                 /* 0x20 */
    TermSelectKey,               /* 0x21 */
    TermUpKey,                   /* 0x22 */
    TermDownKey,                 /* 0x23 */
    StateChangeFakeOut,          /* 0x24 */
    FIRSTCONTROLMESSAGE,         /* 0x25 */ /* Not sent, just a partition */
    NOKEY,                       /* 0x26 */
    UPDATEDISPLAY,               /* 0x27 */
    UPDATETOPLINE,               /* 0x28 */
    UPDATELINE2,                 /* 0x29 */
    UPDATELINE3,                 /* 0x2A */
    UPDATELINE4,                 /* 0x2B */
    TERMDATAOUTPUT,              /* 0x2C */
    UPDATETERMALARM,             /* 0x2D */
    ESTOPMSGON,                  /* 0x2E */
    ESTOPMSGOFF,                 /* 0x2F */
    CALIBRATION_ABORTED,         /* 0x30 */
    RestartMenu,                 /* 0x31 */
    QVGACALIB_KEY,               /* 0X32 */ 
    ESTOPMSGRESET,               /* 0x33 */
    MAX_NUMBER_OF_KEY_CODES,     /* 0x33 */
   } KEY_CODE_TYPE;

#endif


SYS_STARTUP_STATUS_TYPE InitProcessFpKeypadInterrupt(void);
void KeyInt(void);
void FakeKeyInt(KEY_CODE_TYPE key);
