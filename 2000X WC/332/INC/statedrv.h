/* $Header:   D:/SWLab/VMdb/2000Series/INC/STATEDRV.H_V   2.23   Nov 30 2007 11:52:48   bkymer  $ */
#ifndef STATEDRV_H
#define STATEDRV_H
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96              */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/

/*
-------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      statedrv.h



------------------------------ REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      1            7/10/96       LAM         added SC weldsequence
      2            07-27-96      BEKymer     Add debug sequence
      3            08-07-96      BEKymer     Prototype for ResetStateMachine
      4            09-21-96      BEKymer     Prototype for SelectTestSequence
      5            10-30-96      BEKymer     Change prototype for SendData
      6            02-06-97      LAM         added prototype popindex    
      7            04-01-97      LAM         added powerup sequence type 
      8            04-29-97      LAM         Change prototype for SendData
      9.2.16       07-28-97      LAM         added powercalibration sequence
      9.2.17       08-12-97      PaulG       Added prototype for ChangeDataStorage.
      2.18         08-26-97      LAM         moved prototype for init1mspts         
      2.19         12-02-97      BEKymer     Add prototype for CheckStateMachine
	  2.20         04-20-99      OFI         Changed for DIAB

	  2.21         05-28-99      LAM         deleted unused horndown prototypes
      2.21.1.0     09-24-07      BEKymer     Add prototype for SetIndex (Ver 9.07)
      2.23         11-30-07      BEKymer     Check in on tip as 2.23

 
----------------------------- DESCRIPTION -----------------------------------




---------------------------- INCLUDE FILES ----------------------------------
*/  


/*
----------------------------- DEFINES ---------------------------------------
*/

enum WELD_SEQUENCE_TYPE {
     NONEDEFINED,                 /* Default when nothing defined yet       */
     WELD,                        /* Any weld sequence                      */
     CALIBRATION,                 /* Force or distance calibration          */
     SC,                          /* added actuator system calibration      */
     POWERCAL,                    /* added power calibration                */
     DEBUG,                       /* Debug sequence                         */
     HORNDOWN,                    /* Horn down sequence                     */
     TESTMODE,                    /* Test Mode sequence                     */
     POWERDOWN,                   /* Power down sequence                    */
     POWERUP  };                  /* Power up sequence                      */
                                 



/*-------------------------- Function Prototypes ---------------------------*/

void   StopAtEndOfCycle(void);
void   StartDataCollection(void);
void   StopDataCollection(void);
void   SendData(enum WELDSTATES State);
void   StateMachine(void);
void   PushIndex(void);
void   PopIndex(void);
void   SetIndex(SINT16);
void   StartStateMachine(void);
void   StopStateMachine(void);
UINT16 CheckStateMachine(void);
void   ResetStateMachine(void);
UINT16 GetStateMachineFlag(void);
UINT16 SetStateMachineFlag(UINT16 Flag);
void   ResetStateMachineIndex(void);
void   SetCurrentSequenceType(enum WELD_SEQUENCE_TYPE Type);
enum   WELD_SEQUENCE_TYPE GetCurrentSequenceType(void);
void   ResetCycleTimer(void);
void   InitWeldSequencer(void);
void   SelectWeldSequence(void);
void   SelectTestSequence(void);
void   Restart(void);
void   Nothing(void);
void   SelectSensorCalSequence(void);
void   SelectDistanceCalSequence(void);
void   SelectPowerDownSequence(void);
void   ChangeDataStorage(void);
void   Init1msPts(void);

#endif