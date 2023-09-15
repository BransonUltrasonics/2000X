/* $Header:   D:/SWLab/VMdb/2000Series/App/FPSMANGR.C_V   2.73.1.2   09 Sep 2008 20:39:56   nhahmed  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                           */
/*************************                         **************************/

/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:

   Filename:  fpsmangr.c

   Function name: void FrontPanelStateCoordinator(void);
 
 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
  ==========      ========       ======      ===========
      0            1/30/96        ML         Initial
      1            4/29/96        PJ         Added task initializations
                                             Stopped sending Timer Info to
                                             DisplayMenu.
      2            5/15/96        PJ         Fixed warnings
      2.10         8/14/96        PJ         Added GetPresetNames to scan for
                                             valid presets.
      2.20         8/23/96        LAM        deleted menu3.h
      3.00         9/17/96        LAM        added initialize flag                                                     
      3.10         10/16/96       PJ         Goto Run screen on Power Up.
      3.20         10/18/96       PJ         Blanked MainMenu prior to
                                             displaying Run screen.
      3.30         10-19-96       BEKymer    Display power up menu before main
                                             menu
      3.40         10/24/96       PhilJ      Moved SelectWeldMode prior to
                                             displaying Main Menu.
      3.50         10/29/96       PhilJ      Added SetAmpControl and
                                             SetFreqControl initialization.
      4.00         11/29/96       LAM        chged q_send         
      4.10         12/23/96       PhilJ      Added 1 second delay priot to
                                             calling PowerOnMenu. 
      5.00         01/29/97       LAM        moved getpresetnames to sysmanger
      5.01         01/29/97       LAM        added delay
      6.00         03/07/97       LAM        added powerup cold start
      6.10         04/15/97       PhilJ      added CycleCount update at PowerUp.
      6.20         04/18/97       PhilJ      Chngd PowerUpColdStart to UINT8.
      6.30         04/21/97       PhilJ      added KeyLockOutFlag.
      6.40         05/19/97       PhilJ      added ColdStartFlag to DoColdStart.
      6.50         06/13/97       PhilJ      added SetDTBaudRate prototype.
      6.2.32       06/13/97       PhilJ      Changed BaudRate variables to enum
      6.2.33       06/23/97       PhilJ      Deleted buadtype.h.
      6.2.34       06/24/97       LAM        Deleted initdisplaymenu
      7.2.34       07.07.97       J.B.       Adding selection between Run/Main
      7.2.36       07/08/97       LAM        added ampcontrol/freqcontrol functions
      7.2.37       07/09/97       LAM        added powerup check for displaying mainmenu
      7.2.38       07/09/97       LAM        fixed message structure for powerup
      7.2.39       07/11/97       LAM        fixed cold start at power up        
      8.2.40       07/17/97       LAM        added dtenabled = false,deleted baudrate
      8.2.41       08/01/97       PhilJ      Key type selected depending on Powerup
                                             screen.
      2.42         09/10/97       LAM        added dtoutput.h                        
      2.43         09/11/97       PaulG      Unit  test and cleanup
      2.44         11/07/97       BJB        Empties keypad buffer after cold
                                              start so fake SetupKey isn't lost.
                                             Hides Main Menu unless it's the
                                              start screen.
      2.45         11/08/97       BJB        Passes argument to ClearKeypadBuffer().
      2.46         11-18-97       LAM        replaced finalresults with weldingresults
      2.47         12/1/97        KGD        fix for dcs # 1083
      2.48         12/1/97        KGD        fix for dcs # 1083
      2.49         12/29/97       BJB        Deleted uses of DTEnabled, DTStartup.
                                             Doesn't include dtoutput.h.
      2.50         02/02/98       LAM        deleted updating weldcounter
      2.51         04/27/98       BJB        Allows more time for preset, setup to load.
      2.52         05/14/98       LAM        added more time for main menu
      2.53         06/11/98       BJB        Checks password, if enabled, before
                                              power-up cold start.
      2.54         06/15/98       BJB        Fixed error in 2.53; Now does cold start
                                              without asking for password if passwords
                                              are off.
      2.55         06/18/98       BJB        Added code to stop state machine during
                                              power-up cold start.
      2.56         07/30/98       BJB        Moved in code to init start-up strings,
                                              start state machine on power-up.
                                             Moved code to init FpscQid to root().
      2.57         07/30/98       BJB        Doesn't need to write SysInfoBuffer2 on
                                              startup; this done when menu selected.
      2.58         07/31/98       BJB        Uses SendFakeKeyPress() to send first
                                              menu selection key.
      2.59         05-27-99       JZ         changed FrontPanelStateCoordinator
      2.60         12/16/99       LAM        removed unused error handling code
      2.60.6.1     02-22-00       OFI        Removed features.h from include files and removed call to BootSF().
      2.60.6.2     03-17-00       JLH        Added GetLangArrayIndex function call.
      2.61         04-05-00       JZ         merged Lang to Trunk
      2.62         05-26-00       SCM        Checked in for testing by Laura, John.
      2.63         06-07-00       LAM        replaced initializingmsg2 with strblankline
      2.64         06-14-00       SCM        Replaced array index-20 with 'define' LINESIZE.
      2.65         07-07-00       BEKymer    Took away  encoder.
      2.67         06-10-03       bWadia     Added Flags "QVGAColdStart" & "QVGAPowerUpDelay"
                                             which is used in "qvga_task.c".
      2.68         07-14-03       JOY        Removed temporary commentings.
      2.69         09-30-03       JOY        Added Coldstart security check.
      2.70         10-23-03       JOY        Replaced 'QVGAHwAvail'flag by  'QVGAHwPowerup'.
      2.71         10-30-03       JOY        Removed above change.
      2.72         07-08-04       BEKymer    Remove calls to start/stop state
                                              machine for DoColdStart because
                                              DoColdStart does it now.
      2.73         08-19-05       Bwadia     Power up strings to support asian language
                                             String size increased to QVGA_LINESIZE
      2.74         10-22-07       NHAhmed    Changes done for LangTest phase 0
      2.75         09-04-08       YGupta     CleanUp for LangTest Project.
      2.76         09-09-08       NHahmed    CleanUp for multi-language support.
                                             

      
 ------------------------------- DESCRIPTION -----------------------------------


 ------------------------------- PSEUDO CODE -----------------------------------


 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include <psos.h>
#include <prepc.h>

/* inbound intertask message */
#include "fpkp_msg.h"
#include "commnmsg.h"             /* common msg definition            */
#include "kpresmsg.h"             /* key pressed message definition   */
#include "menu.h"
#include "preset.h"
#include "error.h"
#include "keypad.h"
#include "genrlmsg.h"
#include "fpsmangr.h"
#include "ck_qsend.h"           /* contains function interface           */
#include "ticks.h"
#include "menu7a.h"
#include "display.h"
#include "getmsg.h"
#include "menu7.h"
#include "selctkey.h"
#include "spidd.h"
#include "wldstate.h"
#include "statedrv.h"
#include "util.h"

/*
 ---------------------------- FUNCTIONS PROTOTYPES -------------------------
*/
void GetLangArrayIndex(void);

/*
 ------------------------------- EXTERNAL DATA ---------------------------------
*/ 

extern SINT16 BlankMenuCounter;
extern SINT16 MenuCounter;

extern SINT32 ReadOnlyTimer;

extern MENU TheMainMenu[];
extern BOOLEAN JustPoweredUpFlag;

extern enum   WELD_SEQUENCE_TYPE CurrentSequence;
                   
/***********/
extern BOOLEAN QVGAHwAvail;
extern BOOLEAN QVGAColdStart;
extern BOOLEAN QVGAPowerUpDelay;
/**********/

/*
 ------------------------------- LOCAL DEFINES ---------------------------------
*/

#define WAIT_FOR_WELD_SEQ_DELAY  2000  /* Max time to wait for WELD sequence */
                                       /* to start, in ms. */

/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/                   
                       
/*
 -------------------------------- GLOBAL DATA ----------------------------------
*/

UINT32 FpscQid; 
UINT8 InitFlag = FALSE;
UINT8 ColdStartFlag = FALSE;
UINT8 KeyLockOutFlag = TRUE;

typedef union
   {                     
   GENERIC_MSG                   GenericMsg;
   FRONT_PANEL_USER_REQUEST_MSG  KeyPress;
   } FPSC_QUEUE_MSG_TYPE;

FPSC_QUEUE_MSG_TYPE FpscQueue;

/*
 ------------------------------- EXTERNAL DATA --------------------------------- 
*/ 
extern enum LEVEL AccessLevel;
extern UINT8 PowerUpColdStart;
extern CONFIGSETUP CurrentSetup;

/*
 --------------------------------- CODE ----------------------------------------
*/  

void FrontPanelStateCoordinator(void)
{

/* >>> -----------------  Task Initialization  -------------------- <<< */

   UINT8      FirstKey;
   SINT32     WaitStartTime;      /* Used to measure time delay */

   FpscQueue.GenericMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;

   /* -------------------------------------------- */
   /* Initialize front panel for startup messaging */
   /* -------------------------------------------- */
   /* Start front panel display manager task */
   /* set interrupt mask level in mode to disable everything below level 4 */
   /* this will cause the system to start ticking */
      
   QVGAColdStart = FALSE;
   QVGAPowerUpDelay = TRUE;
      

   /* ---------------------------------------------- */
   /* suspend and let application tasks have control */
   /* ---------------------------------------------- */

   StartStateMachine();    /* Begin start-up sequence */

   InitFlag = TRUE;
   tm_wkafter(MS_TO_TICKS(1000)); /* Wait for CurrentSetup and Preset
                                           to load */

// need to remove and change in ready
   JustPoweredUpFlag = FALSE;


   MenuCounter = -1;

/* make sure power up sequence done */
   while(JustPoweredUpFlag == FALSE){
      tm_wkafter(MILLS_TO_TICKS(1000));
   }

 /* >>> ----------------- END Task Initialization  -------------------- <<< */

   while (FOREVER)
   {
      KeyLockOutFlag = FALSE;

      if (PowerUpColdStart == TRUE)    /* Special test for coldstart */
      {
         PowerUpColdStart = FALSE;

         /* Wait here for state machine to run WELD sequence.  This is */
         /* important before we're going to stop the state machine here to */
         /* do a cold start and we don't want to interrupt the power-up */
         /* sequence, which comes first. */

         WaitStartTime = ReadOnlyTimer;   /* Provides timeout in case WELD */
                                          /* sequence never happens. */

         while ((CurrentSequence != WELD) &&
          (ReadOnlyTimer - WaitStartTime < WAIT_FOR_WELD_SEQ_DELAY))
            ;

         ClearKeypadBuffer(TRUE);/* Toss ClearKey presses so not processed, */
                                 /* make sure room in buffer for other. */

         if (CurrentSequence == WELD)  /* If still no WELD, just skip cold start */
         {
            QVGAColdStart = TRUE;
            if (CurrentSetup.PassWordFlag & BIT0) /* If pwords on, make user */
            {                                     /* enter one before clearing */
               do                                 /* parameters. */
                  if(!QVGAHwAvail)
                     AccessLevel = OPERATOR;
               while (AccessLevel < MAINTAINENCE );
         
               if (AccessLevel >= MAINTAINENCE)
               {                  
                  ColdStartFlag = TRUE;
                  DoColdStart();                  
               }
            }
            else
            {               
               ColdStartFlag = TRUE;
               DoColdStart();               
            }
         }
      }
      SetAmpControl();
      SetFreqControl();

      if(ColdStartFlag)
      {
         FirstKey = SetupKey;                // Go to Weld Setup screen
         ColdStartFlag = FALSE;
      }
      else if(CurrentSetup.StartScreen)
      {
         FirstKey = RunKey;
      }
      else                              // For the Main   J.B.
         FirstKey = NOKEY;
      
      QVGAPowerUpDelay = FALSE;      
      SendFakeKeyPress( FirstKey );

      BlankMenuCounter = 1;  /* prevent DisplayMenu from displaying extra MainMenu */
      DisplayMenu(TheMainMenu);


   }  /* end while FOREVER loop */
}  /* <<< end task FrontPanelStateCoordinator.c >>> */
