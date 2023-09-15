/* $Header:   D:/SWLab/VMdb/2000Series/App/ESTOP.C_V   1.16   04 Sep 2008 20:16:22   ygupta  $ */
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
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: estop.c

 ---------------------------- REVISIONS ------------------------------------

   Revision #  Date      Author    Description
   ----------  -------   ------    -----------
   1.00        7/23/95   BEK       Original write of code
   2.00        10/08/96  LAM       convert to psos       
   3.00        10/25/96  LAM       made beep consistent  
   4.00        01-06-97  LAM       redefined beep prototype                
   5.00        04-29-97  LAM       fixed powering up with estop            
   6.00        05-02-97  LAM       clear screen first                      
   7.1.5       07-31-97  LAM       clear ready                             
   8.1.6       08-13-97  LAM       moved clear ready to statedrv                             
   8.1.7       09-11-97  PaulG     Unit test
   1.8         01-12-98  BJB       Doesn't write directly to display, sends
                                    messages to menu task.
   1.9         07-31-98  BJB       Includes kpresmsg.h, getmsg.h
   1.10        11-06-00  BEKymer   Require reset after estop removed.  Reset led
                                    blinks after estop removed.  Now, while estop
                                    active, navigation can occur and values can be
                                    changed.  In future, consider masking all keys
                                    but reset after estop removed, until reset
                                    is pressed.
   1.11        11-09-00  AT        Switched back to version 1.10 (8L12)
   1.12        11-26-03  JOY       ESTOP Message is send to OVGA queue also.
   1.13        07-25-05  Bwadia    ESTOP message sent ot RVTS queue
   1.14        08-19-05  Bwadia    ESTOP message sent only when VGA hardware present 
   2.69        05-29-06  YGupta    IsHWConfigured function used to check for 
                                   VGA Hardware present
   2.70        09-04-08  YGupta    CleanUp for LangTest Project. 
 ---------------------------- DESCRIPTION -----------------------------------


 This module contains the functions for dealing with E-stop.             


 --------------------------- INCLUDE FILES --------------------------------
*/

#include "portable.h"
#include "state.h"
#include "menu.h"
#include "beep.h"
#include "digout.h"
#include "statedrv.h"
#include "keypad.h"
#include "selctkey.h"
#include "kpresmsg.h"
#include "getmsg.h"
#include "ticks.h"
#include "ck_qsend.h"
#include "opcodes.h"
#include "qvgamenu.h"

/*
  ------------------------- EXTERNAL DATA ----------------------------------
*/

extern INBITS Inp;
extern UINT16 EstopHistoryFlag;
extern UINT32 QvgaQid;
extern SCREEN_TYPE CurrentScrnType;
extern UINT32 RvtsQid;
/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/                                                              

#define ESTOPBLINKONTIME    200       /* Emergency stop blink on time      */
#define ESTOPBLINKOFFTIME   200       /* Emergency stop blink off time     */


/*
 ------------------------------- LOCAL DATA ------------------------------------
*/

SINT16 EstopCountDown = ESTOPBLINKONTIME;
SINT16 EstopState = OFF;

/*
 ------------------------------- CODE ------------------------------------
*/


void ProcessEstop(void)
/***************************************************************************/
/*                                                                         */
/*  This function will actually blink Emergency Stop on the display if it  */
/*  is needed.  All timing will be done here.                              */
/*                                                                         */
/*  Currently, the display will be restored to the previous menu when Estop*/
/*  is removed.                                                            */
/*                                                                         */
/***************************************************************************/
{

   FP_KEY_PRESSED_MSG           FPKeyMsg;
   
   if ((Inp.Estop == TRUE) && (EstopHistoryFlag == TRUE)){
      if(EstopCountDown-- < 0)
      {
         switch (EstopState)
         {
            case OFF:                            /* Estop was off          */
               EstopState = ON;
               SendFakeKeyPress(ESTOPMSGON);
               if(IsHWConfigured(VGA))
               {
                  FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                  FPKeyMsg.key = ESTOPMSGON;                        
                  CkQSend (RvtsQid, &FPKeyMsg, WELD_MGR,
                           __LINE__, MILLS_TO_TICKS(10));      /* 10 ms       */
               }
               break;
      
            case ON:                             /* Estop was on           */
               EstopState = OFF;
               SendFakeKeyPress(ESTOPMSGOFF);
               if(IsHWConfigured(VGA))
               {
                  FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                  FPKeyMsg.key = ESTOPMSGOFF;                        
                  CkQSend (RvtsQid, &FPKeyMsg, WELD_MGR,
                           __LINE__, MILLS_TO_TICKS(10));      /* 10 ms       */
               }
               break;
         }
         EstopCountDown = ESTOPBLINKONTIME;

      }
   }
}
