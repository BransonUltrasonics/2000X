/* $Header:   D:/SWLab/VMdb/2000Series/App/FPK_TASK.C_V   2.58   11 Nov 2009 20:03:44   pdwivedi  $ */
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
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:     front_panel_keypad_task fpkp

   Filename:        fpk_task.c

   Function name:   FrontPanelKeypadTask


            Written by: Mark Lazarewicz  
                  Date:  01/10/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            01/10/96      Mark L      Initial Version
      1            03/22/96      Mark L      Timeout and off switch for FPSC
      2            04/25/96      LAM         Removed switch on key check in
                                             getmsg
      3            04/29/96      Mark L      Init FpscMsg at startup time 
      4            10/18/96      PhilJ       Temporary fix for bad hardware.
                                             All 0x1B(UnAssigned3 keys) on 2C
                                             boards are thrown away.
      5            10/22/96      PhilJ       Keyboard controller chip fixed
                                             Removed temporary fix..
      6            11/15/96      LAM         chged q_send
      7            11-21-96      BEKymer     Added test for GoBack & Main keys
      8            02/12/97      PhilJ       Added test for HornDownMenu.
      9            03/07/97      PhilJ       Added Error Beep for invalid key
                                             hits in HornDownMenu.
      10           04/21/97      PhilJ       Added test on KeyLockOutFlag for
                                             PowerUp key lockout.
      11           05/02/97      LAM         cleanup      
      13           05-07-97      LAM         deleted unused fpscqid
      14           06-04-97      J.B         Free running kb clock
      15.2.22      07-10-97      LAM         set powerupcoldstartflag
      15.2.23      07-22-97      PhilJ       Added test on SetupKey
      15.2.24      07-28-97      PhilJ       Put back with no change
      15.2.25      09.09.97      JBerman     Added default to the case statement
      2.26         09.19.97      LAM         started to add keymask             
      2.27         09.24.97      LAM         fixed calibration keymask             
      2.29         09.30.97      LAM         fixed calibration keymask again
      2.30         10.3.97       kgd         fixed  keymask for remote terminal
      2.32         10.14.97      LAM         added power abort mask
      2.33         10/28/97      BJB         Sends HornDownKey directly to menu
                                              system, not to WeldManager().
                                             Doesn't check for Horn Down mode
                                              before passing keys to menu.
                                             Masks off only RESET and TEST keys
                                              in Horn Down mode.
      2.34         11/4/97       BJB         Sends SetupKey directly to menu
                                              system, not to WeldManager().
                                             SetupKey allowed in test mode.
      2.35         11.20.97      LAM         added digpot mask

      2.36         12.29.97      BJB         Deleted use of DTEnalbed.
      2.37         04.30.98      LAM         added calibration mask
      2.38         06.11.98      LAM         added disable select keys 1 & 3 for
                                             calibration
      2.39         06.30.98      LAM         added calibration aborted when in
                                             calibration and a main or goback key
                                             is pressed.
      2.40         07.15.98      LAM         added calibration aborted when in
                                             act calibration and a main or goback key
                                             is pressed.
      2.41         07.31.98      BJB         Uses SendFakeKeyPress() to send key
                                             messages to menu task.
      2.42         12/16/99      LAM         Removed unused errorhandling code   
      2.43         08/28/00      SCM         Added code for Horn Scan abort functionality. 
      2.44         08/28/00      SCM         Added code to turn off beepers during an ABORT HORNSCAN.
      2.45         10/04/00      LAM         Added case to disable keys when entering the HORNSCAN
                                             submenu. ISSUE(3597)
      2.46         11-06-00      BEKymer     Require reset after estop removed.  Reset led  
                                              blinks after estop removed.  Now, while estop 
                                              active, navigation can occur and values can be
                                              changed.  In future, consider masking all keys
                                              but reset after estop removed, until reset    
                                              is pressed. Issue # 3659                      
      2.47         11-07-00      BEKymer     Add new case for ESTOPMASK (disable all but
                                              reset key)
      2.48         11-09-00      AT          Switched back to version 2.45 (8L12)
      2.49         11-09-00      AT          Update the source to be 2.45
      2.50         11-09-00      AT          EStop fix - FrontPanelKeypadTask - handle
                                              Reset and other keys when 'Reset required'
                                              is flashing
      2.51         11-09-00      AT          Turn Reset LED off if there were no alarms
                                             Removed 'continue'
      2.53         04-30-03      BEKymer     Put back on tip for 8.10 build
                                             Add OnBoardDiagnostic and set at power up
                                              if Go Back or Esc is pressed.
      2.51.2.1     06-10-03      bWadia      Power Up cold start is added for Reset Button also. 
      2.51.2.2     08-22-03      LAM         Power Up cold start is not from external Reset. 
      2.54         09-17-03      LAM         merged 8.10 with TS01                                       
      2.55         09-17-03      LAM         fixed compiler error                                       
      2.56         01-11-06      LAM         added PSIdle after reset key pressed.                                       
      2.57         01-13-06      LAM         removed Reset key                                       
      2.58         11-11-09      PDwivedi    Enable Reset key on Horn Down Screen.                                      

 ------------------------------- DESCRIPTION -----------------------------------


 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include <psos.h>                         /* psos definitions                 */
#include "names.h"                        /* psos object definitions          */
#include "opcodes.h"                      /* station opcodes                  */
#include "commnmsg.h"                     /* common msg definition            */
#include "kpresmsg.h"                     /* key pressed message definition   */
#include "ticks.h"
#include "fpk_task.h"
#include "ck_qsend.h"                     /* contains function interface      */
#include "beep.h"
#include "state.h"
#include "statedrv.h"
#include "snsrcalb.h"
#include "keypad.h" 
#include "getmsg.h"
#include "inports.h"
#include "led.h"
#include "digout.h"

/* outbound message */
#include "fpkp_msg.h"

/* inbound message  */
#include "genrlmsg.h"

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/

#define MESSAGE_DELAY    400
#define ALLKEYSENABLED   0xffffffff

/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/                     

static GENERIC_MSG            WeldMsgOut;

typedef union
   {
   GENERIC_MSG                generic;
   FP_KEY_PRESSED_MSG         FpKeyPressedMsg;   
   }  FPKP_MSG_QUEUE_TYPE;

UINT32 KeyMask;
const UINT32 KeyBitAssigned[] = { KEY_0MASK, KEY_1MASK, KEY_2MASK, KEY_3MASK,      
         KEY_4MASK, KEY_5MASK, KEY_6MASK, KEY_7MASK, KEY_8MASK, KEY_9MASK,      
         DPOINTKEYMASK, INCKEYMASK, DECKEYMASK, CLEARKEYMASK, ENTERKEYMASK,   
         SETUPKEYMASK, RESETKEYMASK, TESTKEYMASK, MAINKEYMASK, GOBACKKEYMASK,  
         OFFKEYMASK, PRINTKEYMASK, HORNDOWNKEYMASK, RUNKEYMASK, SELECT1KEYMASK, 
         SELECT2KEYMASK, SELECT3KEYMASK, UNASSIGNED3MASK, RIGHTKEYMASK,   
         LEFTKEYMASK, UPKEYMASK, DOWNKEYMASK};    

UINT8    HS_KeyPressed;
BOOLEAN  HS_status;

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern UINT16  CalibrationPassed;
extern UINT8   KeyLockOutFlag;
extern UINT8   PowerUpColdStart;
extern UINT16  EstopHistoryFlag;
extern SINT16  MenuCounter;
extern UINT32  WmgrQid;
extern UINT32  FpscQid;
extern BOOLEAN TestSonicsFlag;
extern BOOLEAN HornDownFlag;
extern UINT16 TotalAlarmCount;
extern BOOLEAN OnboardDiag;
extern UINT16 ExternalResetHistory;



/*
 ---------------------------------- CODE ---------------------------------------
*/

void FrontPanelKeypadTask(void)
{ 
   UINT8                        KeyPressed;
   UINT16                       KeyFlag;
   UINT32                       PsosStatus;
   UINT32                       FpkpQid;      
   FPKP_MSG_QUEUE_TYPE          FpkpQueue;            
   FRONT_PANEL_USER_REQUEST_MSG FpscMsg;

   /*----------------------------------------------------------------------*/
   /* identify psos objects                                                */
   /*----------------------------------------------------------------------*/

   /* Get queue id of FpkpQueue */
   PsosStatus = q_ident(FPKP_Q, Q_NODE_0, &FpkpQid);

   FpscMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
   FpscMsg.common.pointer_flag = NO_DATA_PTR;
   FpscMsg.common.source_task  = FPKP_SOURCE_TASK;

   /* next, install and initialize the fp keypad vector */   
   InitProcessFpKeypadInterrupt() ;

   /*----------------------------------------------------------------------*/
   /* Loop forever                                                         */
   /*----------------------------------------------------------------------*/

   while (TRUE)
   {                            

      /* block on empty queue */
      PsosStatus = q_receive(FpkpQid, Q_WAIT, Q_WAIT_FOREVER, &FpkpQueue);

      // this code handles Reset and ignores all other keys
      if (EStopState != ESTOPBTN_RESET)
         {
      // if EStop is released and alarm is active, process only Reset key
         if (EStopState == ESTOPBTN_RELEASED)
            {
            KeyPressed = FpkpQueue.FpKeyPressedMsg.key;
            if (KeyPressed == ResetKey) // handle only Reset key
               {
               PSIdle();
               EStopState = ESTOPBTN_RESET;
               // if no alarms - turn the LED off
               if (TotalAlarmCount == 0)
                  UpdateLED(RESETLED, OFF);
               }
            else
               Beep(ERRORBEEP);   // beep at any other key
            }
            else
            Beep(ERRORBEEP);   // beep at any key while EStop is pressed
         }
      else
         {

   /* if estop is active donot process the key */
         if(EstopHistoryFlag == FALSE) {   

            KeyPressed = FpkpQueue.FpKeyPressedMsg.key;
            HS_KeyPressed = KeyPressed;
            if ((KeyBitAssigned[KeyPressed] & KeyMask) != 0)
            {
               switch (FpkpQueue.generic.common.opcode)
               {


            /* Process FP Keypresses */
                  case OP_FRONT_PANEL_KEYPRESS:
                     /* get key pad input */
                     FpscMsg.user_request = KeyPressed;
                     KeyFlag = FALSE;
            
                     if(KeyLockOutFlag)
                     {
                        if(KeyPressed == ClearKey){
                           SendFakeKeyPress(ClearKey);
                           PowerUpColdStart = TRUE;
                        }   
                        else if(KeyPressed == GoBackKey){
                           OnboardDiag = TRUE;             /* diagnostics through the serial port enabled */
                        }
                     }
                     else
                     {
                        if (KeyPressed == TestKey) {
                           WeldMsgOut.common.opcode = OP_TEST_KEY_PRESSED;
                           KeyFlag = TRUE;
                        }
                        else if (KeyPressed == ResetKey) {
                           WeldMsgOut.common.opcode = OP_RESET_KEY_PRESSED;
                           KeyFlag = TRUE;
                        }
                        else if (KeyPressed == MainKey) {
                           if((GetCurrentSequenceType() == CALIBRATION) ||
                              (GetCurrentSequenceType() == SC))
                           {                  
                              CalibrationPassed = CAL_ABORTED;
                           }
                           WeldMsgOut.common.opcode = OP_MAIN_KEY_PRESSED;
                           KeyFlag = TRUE;
                        }
                        else if (KeyPressed == GoBackKey) {
                           if((GetCurrentSequenceType() == CALIBRATION) ||
                              (GetCurrentSequenceType() == SC))
                           {                  
                              CalibrationPassed = CAL_ABORTED;
                           }
                           WeldMsgOut.common.opcode = OP_GOBACK_KEY_PRESSED;
                           KeyFlag = TRUE;
                        }
                        else if (KeyPressed == RunKey) {
                           WeldMsgOut.common.opcode = OP_RUN_KEY_PRESSED;
                           KeyFlag = TRUE;
                        }
                        if (KeyFlag == TRUE) {
                           CkQSend (WmgrQid,&WeldMsgOut,FRONT_PANEL_KEY_PAD_TASK,__LINE__,        
                                               MILLS_TO_TICKS(50)      /* 100 ms        */
                                               );
                        }
                        else
                        {
                           SendFakeKeyPress( KeyPressed );
                        }
                     } /* end of switch opcode */
                     break;
            
                  default:
                     break;

                  }  /* end switch FpkpQueue.common.opcode */
              }
              else
              {
                 if(HS_status == TRUE)
                 Beep(ERRORBEEP);
              }
           }  // end of 'continue' workaround
       } /* estop end */
                                               
   }  /* end while forever */
     
}  /* End function FrontPanelKeypadTask */


void UpdateKeyMask(UINT32 KeyMode)
{

   switch (KeyMode)
   {
      case POWERCALMODEMASK:
         HS_status = TRUE;  
         KeyMask = ~(HORNDOWNKEYMASK | SETUPKEYMASK | PRINTKEYMASK
                     | RUNKEYMASK | UPKEYMASK | DOWNKEYMASK);
         break;

      case POWERABORTMASK:
         HS_status = TRUE;
         KeyMask = GOBACKKEYMASK;
         break;

      case CALMODEMASK:
         HS_status = TRUE;
         KeyMask = ~(HORNDOWNKEYMASK | SETUPKEYMASK | PRINTKEYMASK
                     | RUNKEYMASK | UPKEYMASK | DOWNKEYMASK 
                     | TESTKEYMASK | LEFTKEYMASK | RIGHTKEYMASK);
         break;

      case DISABLESEL3:
         HS_status = TRUE;
         KeyMask = ~(HORNDOWNKEYMASK | SETUPKEYMASK | PRINTKEYMASK
                     | RUNKEYMASK | UPKEYMASK | DOWNKEYMASK 
                     | SELECT3KEYMASK | SELECT1KEYMASK | TESTKEYMASK
                     | LEFTKEYMASK | RIGHTKEYMASK);
         break;

      case DIGPOTMASK:
         HS_status = TRUE;
         KeyMask = GOBACKKEYMASK | SELECT2KEYMASK | SELECT3KEYMASK;
         break;

      case HDMODEMASK:
         HS_status = TRUE;
         KeyMask = ALLKEYSENABLED & ~( TESTKEYMASK);//RESETKEYMASK |
         break;

      case TESTMODEMASK:
         HS_status = TRUE;
         KeyMask = ALLKEYSENABLED & (~HORNDOWNKEYMASK);
         break;

      case WELDMODEMASK:
      default:
         HS_status = TRUE;
         KeyMask = ALLKEYSENABLED;
         break;

      case HSMASK:      
         HS_status = FALSE;
         KeyMask =  GOBACKKEYMASK;
         break;
      case HSSUBMENUMASK:      
         HS_status = TRUE;
         KeyMask =  GOBACKKEYMASK | SELECT1KEYMASK | SELECT2KEYMASK | SELECT3KEYMASK |
                    UPKEYMASK | DOWNKEYMASK ;
         break;
   }
 
}
