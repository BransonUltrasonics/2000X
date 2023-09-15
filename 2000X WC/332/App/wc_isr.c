/* $Header:   D:/databases/VMdb/2000Series/App/WC_ISR.C_V   2.43.1.2   Jan 03 2018 11:15:22   RCHAPA  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1996                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 

/*
-------------------------- MODULE DESCRIPTION -------------------------------

  This module sets the interrupt vector for the 1ms loop and processes the
  interrupt request.

----------------------------- REVISIONS ------------------------------------

   Revision #  Date     Author   Description
   ----------  -------  ------   -----------
    0          4/18/96  LAM      initial release                                    
    1          8/13/96  LAM      added deflection                                   
    2          8/16/96  LAM      added writetovf                                    
    3          9/03/96  LAM      moved monitorinputs                                
    4          09-25-96 BEKymer  Remove (SINT32) type casting from EncoderPos
                                 and change to UINT32 using separate variables
    5          12-06-97 LAM      added deflection with EP
    6          02-21-97 LAM      fixed encoder > 3.200 in
    7          04-24-97 LAM      read PS ADC every ms     
    8          04-28-97 LAM      fixed warning            
    9          05-02-97 PhilJ    Added OneMilTimer counter
    10         05-02-97 PhilJ    Deleted OneMilTimer counter
    11         05-05-97 LAM      moved managesensors after statemachine
    12         05-30-97 PhilJ    added SerialTimer counter
    2.16       07-08-97 PhilJ    Changed SerialTimer to OneMilTimer
    2.17       08.15.97 JBerman  Comment out: MonitorInputPorts()
    2.18       09.04.97 LAM      Commented out vf addr            
    2.19       10.15.97 LAM      added diagscreen test            
    2.20       11.10.97 LAM      added estop test to diagscreen test
    2.21       12.01.97 BJB      Clears TPU IRQ bit at end of MsInt() as well
                                  as at the beginning.
                                 Fixed comment so no compiler informational.
    2.22       01.05.98 LAM      added test to make sure the QSPI conversion is complete.
    2.23       03.20.98 LAM      fixed test for encoder deleted test code
    2.24       04.06.98 BJB      Added ReadOnlyTimer, like OneMilTimer but it
                                  should never be written to (except here).
    2.25       04.22.98 BJB      Added code to call HornDownISR() instead of
                                  state machine if in HD mode.
    2.26       05.14.98 LAM      chg deflection table to NVR structure
    2.27       07.30.98 BJB      Doesn't do QSPI transfers (ReadPSADC()) if
                                  foreground is using QSPI.
                                 Added MinMsInt() for use in power-up.
                                 Deleted act_nvr definition, uses actnvram.h.
    2.28       08.19.98 BJB      Calls TermMsInt() every ms to support term
                                  blinking ALARM message.
    2.29       05/07/99 LAM      commented out deflection compensation
    2.30       08/24/99 LAM      Will wait until QSPI flag is cleared.
    2.31       10-11-99 JZ       removed typecasting for EncoderPos assignment
    2.32       06-21-00 AS       Areas of code that use QSPI in ms ISR disabled
                                 when DUPS is being accessed
    2.33       08-15-00 AT       included menutest.h for UpdateDiagScreen
    2.34       10-03-00 LAM      moved DupsBid flag to allow reading of inputs
                                 Issue(3597)
    2.35       01-09-01 LAM      added complier switch for throughput analysis
    2.36       04-11-03 BEKymer  Call Onboard Diag funcion if enabled
    2.37       11-05-03 JOY      QVGA Diag Screen is updated. Tracker #3806.
    2.38       03-26-04 BEKymer  Rename DisplayHelp related variables to 
                                 IOTest because they are more generic now.
    2.38.1.1   09-10-05 Aare     Call VerifySBL in each pass through the interrupt handler.
    2.39       09-11-05 Aare     Merged 10f and 10h
    2.40       01-11-06 LAM      Updated for metric encoder
    2.41       02-22-06 Bwadia   Removed VerifySBL() from MsInt()
    2.42       10-22-07 NHAhmed  Changes done for LangTest phase 0
    2.43       09-04-08 YGupta   CleanUp for LangTest Project.
    2.43.1.0   10-26-13 GButron  MsInt() function changed. It will check if the offset has
                                 already been applied (HandHeld mode only). As soon as the
                                 offset is applied, the sonics is enabled in a different state.
	2.43.1.2	1/3/2018	RChapa	Removed validation DUPS Timer To disable DUPSWaitFlag if DUPS do not send the CMD	
------------------------------- DESCRIPTION -----------------------------------*/

 


/*----------------------------- INCLUDE FILES ----------------------------------*/

#include "portable.h"
#include "encoder.h"
#include "mansensr.h"
#include "preset.h"
#include "state.h"
#include "menutest.h"
#include "statedrv.h"
#include "interpol.h"
#include "inports.h"
#include "timer.h"
#include "menuhorn.h"
#include "qsm.h"
#include "332.h"
#include "actnvram.h"
#include "spidd.h"
#include "iotest332.h"
#include "qvgamenu.h"
#include "rdyweld1.h"


/* This is only set for testing purposes */
//#define INCLUDE_THROUGHPUTTEST 1



/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

UINT16   OneMilTimer;
SINT32   ReadOnlyTimer;    /* Added this because tasks write to OneMilTimer */
SINT32   EncoderPos;
UINT16   LIMIT_TIME = 2;

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern BOOLEAN PoweredUp;
extern SINT32      CurrentForce;
extern CONFIGSETUP CurrentSetup;
extern UINT16      DiagFlag;
extern INBITS      Inp;
extern UINT8   NovramEnable;
extern BOOLEAN HornDownFlag;
extern UINT16  DupsBid;
extern BOOLEAN IOTestFlag;
extern SCREEN_TYPE CurrentScrnType;
extern UINT32 TotalCycleTime;
extern BOOLEAN Flag_Start_Sonic1HH;   
extern BOOLEAN Flag_Start_NonTimeHH;    
extern UINT16 Two_Msec;



void MsInt(void)
/****************************************************************************/ 
/*                                                                          */    
/* The interrupt is generated on the rising edge of the 1ms pulse. The state*/
/* machine is updated. Then the timers are updated then the qspi is enabled.*/
/* After 5ms the bargraph parameters are updated.                           */    
/*                                                                          */    
/* Inputs: DupsBid - Set when the DUPS is using the QSPI                    */    
/*                                                                          */    
/****************************************************************************/ 
{
   UINT16   InterValue;
   
   
 
   asm(" andi.w #$fffe,$fffe0a");         /* disable interrupts on the channel */
   asm(" move.w $fffe20,d0");
   asm(" andi.w #$fffe,$fffe20");         /* clear interrupt request bit */

#if INCLUDE_THROUGHPUTTEST                /* toggle digpot output */
   asm(" ori.w #$10,$fffe18");            /* drive pin low */
#endif

   OneMilTimer++;
   ReadOnlyTimer++;
   TotalCycleTime++;

/* Read the Power supply ADC every ms */

   if (!DupsBid)
   {
      if(PoweredUp == TRUE){              /* check for encoder preset */
         while(QsmMap->Spsr.Spif == 0);
      }

      if (NovramEnable == FALSE)
         ReadPSADC();
   }

   /*--- Make sure actuator AED or AEF ---*/
   if (CurrentSetup.Actuator != AE) {
      EncoderPos = ReadEncoder();
   }

  
   if (HornDownFlag)                      /* Horn Down mode doesn't use state */
   {                                      /* machine, instead checks for its */
      HornDownISR();                      /* own events. */
   }
   else
   {
      if (UpdateTimers() == TRUE)
         StateMachine();
      if((DiagFlag == TRUE || CurrentScrnType == DIAG_SCREEN) &&
         (Inp.Estop == FALSE))
         UpdateDiagScreen();
   }
   if (IOTestFlag == TRUE) CheckIOTest();
   ManageSensors();
   
   
   /**********************************************************************************************************/
   /*                                                                                                        */
   /*    This section will check if the offset has already been applied. As soon as the offset is applied,   */
   /*                       the sonics is enabled. HandHeld mode only                                        */
   /*                                                                                                        */
   /**********************************************************************************************************/
   
   if(Flag_Start_Sonic1HH == TRUE){       /* Has the offset Already been applied for HH mode?     */ 
      SonicsAbort = FALSE;

      Two_Msec++;                         /* Apply the sonics nmSec After the offset was applied  */
         if(Two_Msec >= LIMIT_TIME){      /* Have nmSec elapsed since the offset was applied?     */
            StartSonic1HH_1msec_Later();  /* If yes, Sonics is enabled                            */
            Flag_Start_Sonic1HH = FALSE;  /* Restart conditions                                   */
            Two_Msec = 0;                 /* Reset the counter                                    */
         }
   }
   

   if(Flag_Start_NonTimeHH == TRUE){      /* Has the offset Already been applied for HH mode?     */ 
      SonicsAbort = FALSE;

      Two_Msec++;                         /* Apply the sonics nmSec After the offset was applied  */                   
         if(Two_Msec >= LIMIT_TIME){      /* Have nmSec elapsed since the offset was applied?     */
            StartNonTimeHH_1msec_Later(); /* If yes, Sonics is enabled                            */  	
            Flag_Start_NonTimeHH = FALSE; /* Restart conditions                                   */    
            Two_Msec = 0;                 /* Reset the counter                                    */
         }
   }

 
   

#if INCLUDE_THROUGHPUTTEST                /* toggle digpot output */
   asm(" ori.w #$20,$fffe18");            /* drive pin high */
#endif
 
   asm(" andi.w #$fffe,$fffe20");         /* Clear interrupt request bit again */
                                          /* in case were in here more than 1ms. */
   asm(" ori.w #$01,$fffe0a");            /* Enable interrupts on the channel */
}

void MinMsInt(void)
/****************************************************************************/ 
/*                                                                          */    
/* Minimal 1ms interrupt service routine, used during startup when not      */
/* enough of the system is initialized to call the real thing.  Provides    */
/* display and timing support.                                              */    
/*                                                                          */    
/****************************************************************************/ 
{
   asm(" andi.w #$fffe,$fffe0a");    /* disable interrupts on the channel */
   asm(" move.w $fffe20,d0");
   asm(" andi.w #$fffe,$fffe20");    /* clear interrupt request bit */

   OneMilTimer++;


   asm(" andi.w #$fffe,$fffe20");   /* Clear interrupt request bit again */
                                    /* in case were in here more than 1ms. */
   asm(" ori.w #$01,$fffe0a");      /* Enable interrupts on the channel */
}
