/* $Header:   D:/SWLab/VMdb/2000Series/INC/INPORTS.H_V   2.8   May 12 2004 00:14:22   BWadia  $ */
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
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

------------------------------ REVISIONS --------------------------------------

   Revision #      Date          Author          Description
   ==========      ========      ======          ===========
      0            02/08/96      Mark Lazarewicz Initial release 
      1.2.3        07/01/97      LAM             added storeint prototype
      2.4          11-01-00      AT              EStop - added ESTOP_STATE enum
                                                 and variable
      2.5          02-18-04      VSharma         Added defines for User configurable Inputs.
                                                 Added enum INPUT_PINS.
      2.6          04-27-04      VSharma         Added prototype for IsConfigured().
      2.7          05-03-04      VSharma         Added define for INPUT_SYNC_IN.
      2.8          05-11-04      VSharma         Changed comments from ExtCycleAbort to ExtTrigger.

------------------------------- DESCRIPTION -----------------------------------

   This file defines language extensions for use with the Microtec "C" compiler.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#ifndef _INPORTS_H_INCLUDED_
#define _INPORTS_H_INCLUDED_

#include "portable.h"
#include "state.h"
#include "memap.h"


typedef enum     { ESTOPBTN_RESET,              // alarm not active
                   ESTOPBTN_PRESSED,            // button pressed
                   ESTOPBTN_RELEASED            // button released but
								// alarm still active
                   } ESTOP_STATE;

extern ESTOP_STATE EStopState;

/* User Configurable Inputs */
#define INPUT_DISABLED            BIT0   // Disabled
#define INPUT_PRESET1             BIT1   // Select preset 1
#define INPUT_PRESET2             BIT2   // Select Preset 2
#define INPUT_PRESET3             BIT3   // Select Preset 3
#define INPUT_PRESET4             BIT4   // Select Preset 4
#define INPUT_PRESET5             BIT5   // Select Preset 5
#define INPUT_EXT_TRIGDELAY       BIT6   // External Trigger Delay.
#define INPUT_DISP_LOCK           BIT7   // Display Lock.
#define INPUT_EXT_TRIGGER         BIT8   // External Trigger
#define INPUT_SONICS_DISABLE      BIT9   // Sonics Disable.
#define INPUT_MEM_RESET           BIT10  // Memory Reset.
#define INPUT_SV_INTERLOCK        BIT11  // SV Inter Lock
#define INPUT_SYNC_IN             BIT12  // Sync In 

enum INPUT_PINS {
   J3PIN32 = 1,
   J3PIN33,
   J3PIN19,
   J3PIN17,
   J3PIN31,
   J3PIN1    };


/*
 --------------------------------- DEFINES -------------------------------------
*/

void  MonitorInputPorts(void);
UINT8 InitMonitorInputPorts(void);
void  GetInputData(INBITS *InputPort);
void StoreInt(void);
BOOLEAN IsConfigured (UINT16 SelectedInput);

#endif
