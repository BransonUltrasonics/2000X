/* $Header:   D:/SWLab/VMdb/2000Series/INC/DIGOUT.H_V   2.23   Jan 09 2006 13:56:34   lmarkure  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,1996,97         */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/

/*
 ---------------------------- MODULE DESCRIPTION ---------------------------

   Module name:  

   Filename:      digout.h


            Written by: Laura Markure  
                  Date: 3/24/96  
              Language:  "C"

 -------------------------------- REVISIONS ---------------------------------

   Revision #  Date      Author   Description
   ==========  ========  ======   ===========
     1         07/03/96  LAM      removed unused prototypes   
     2         08-07-96  BEKymer  Prototypes for new functions SeekOn & SeekOff
     3         08-08-96  BEKymer  Prototype for PSSeek
     4         08-12-96  LAM      Prototype for getreadystatus
     5         08-27-96  BEKymer  Prototype for CheckGeneralAlarmFlag
     6         9/09/96   LAM      removed unused SV set & clear functions    
     7         10-03-96  BEKymer  Prototype for Reject/Suspect Off/On
     8         01-20-97  LAM      added prototype for trigswactive            
     9         01-26-97  LAM      chged systemprototypes to pbrelease         
     10        01-07-97  J.B.     Comment prototype MissingPart On/Off
     11.2.14   07-14-97  BEKymer  Renamed Missing part to Warning
     2.15      11-18-97  LAM      deleted unused seek functions   
     2.16      12.01.97  JBerman  Modified: 1) SV3Off with CoolValOff.
                                            2) SV3On with CoolValOn.
     2.17      11-30-99  BEKymer  Added prototypes for SetUser1(), SetUser2(),
                                  ClearUser1(), ClearUser2(),
                                  ToggleUser1() and TpggleUser2().
     2.18      08/29/00  SCM      Added function prototype HSReset().
     2.19      05-29-02  BEKymer  Add prototype for ClearFreq()
     2.20      04/06/04  VSharma  Added function prototype for User configurable
                                   outputs.
     2.21      04/27/04  VSharma  Removed WarningOn() & WarningOff() prototypes.
     2.22      05/17/04  VSharma  Removed ToggleUser1(),ToggleUser2(),SetUser1(),SetUser2(),
                                  ClearUser1() & ClearUser2() function prototypes.
     2.23      01/09/06  LAM      Added EStopReset prototype

 ------------------------------- DESCRIPTION --------------------------------



 ------------------------------ INCLUDE FILES -------------------------------
*/  


/*
 ------------------------------- DEFINES -----------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ------------------------------
*/                           


/*  
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

void LockPowerOn(void);
void PowerDownSystem(void);
void SetGeneralAlarm(void);
void ClearAuxAlarms(void);
void ClearGeneralAlarm(void);
BOOLEAN CheckGeneralAlarmFlag(void);
void SetAuxAlarms(void);
void SetReady(void);
void ClearReady(void);
BOOLEAN GetReadyStatus(void);
void ClearSAS(void);
void SetSAS(void);
void PSIdle(void);
void PSReset(void);
void EStopReset(void);
void HSReset(void);
void MemoryReset(void);
void ClearFreq(void);
void PSTest(void);
void PSSeek(void);
void PSRun(void);
void SVOff(void);
void SV2Off(void);
void CoolValOff(void);
void EnableSVOn(void);
void SVOn(void);
void SV1On(void);
void SV2On(void);
void CoolValOn(void);
void RejectOff(void);
void RejectOn(void);
void SuspectOff(void);
void SuspectOn(void);
void ActClrOn(void);
void ActClrOff(void);
void PBReleaseOn(void);
void PBReleaseOff(void);
void TrigSwActv(void);
void TrigSwInactv(void);
void TrsEnabled(void);
void TrsDisabled(void);

void UserCfgOutputOn (UINT16 OutputConfigured);
void UserCfgOutputOff (UINT16 OutputConfigured);
void ConfirmPresetOn(void);
void ConfirmPresetOff(void);
void SVOutOn(void);
void RefreshOutputStatus(UINT16);

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/


