/* $Header:   D:/SWLab/VMdb/2000Series/App/BEEP.C_V   1.20   Apr 30 2004 09:04:38   BWadia  $ */
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

 Name: beep.c

 ----------------------------- REVISIONS ------------------------------------

   Revision #     Date        Author   Description
   ----------     -------     ------   -----------
    0             16/22/95    BEK      Initial
    1             4/18/96     LAM      Converted for PSOS
    2             09-09-96    BEKymer  Uncommented test for beep disable
    3             09/18/96    LAM      added number of beeps
    4             10/20/96    LAM      added psos beep
    5             11-21-96    BEKymer  Make NumberOfBeeps SINT16 & set to 0 
                                       when beeper is off
    6             12/30/96    LAM      check trigger beeper off only during weld
    7             01/06/97    LAM      deleted unused Number                    
    8.1.15        07-23-97    LAM      replaced move.w with ori.w  
    1.16          08-25-98    LAM      trigger beep during calibration even
                                       when calibration is disabled
    1.18          03-29-01    BEKymer  Added Confirm beep
    1.19          04-06-04    VSharma  Added code for External beeper Output On/Off.
                                       Modified 'Beep()' for ReleaseBeeper.
    1.20          04-30-04    VSharma  External beeper made work in sync. with
                                        internal beep.


 ---------------------------- DESCRIPTION -----------------------------------
*/

#include "portable.h"
#include "beep.h"
#include "preset.h"
#include "state.h"
#include "statedrv.h"
#include "digout.h"
#include "outports.h"

#define INCLUDE_BEEP_UNIT_TEST

/**  **  Variables and things for beeper  **  **/
/*  This module contains the routines for dealing with the beeper.         */
/*                                                                         */
/*     Beep -  high level routine to indicate which beeper should */
/*        sound and also turns on beeper                                   */

/* Number of beeps in queue   */
SINT16 NumberOfBeeps;    
static UINT16 BeeperOn = FALSE;     /* Flag for timer routine to clear   */
SINT16  BeepOnTime;                /* Flag for timer routine to clear       */
extern CONFIGSETUP CurrentSetup;
extern enum   WELD_SEQUENCE_TYPE CurrentSequence;

void Beep(enum BEEPS Type)
/**************************************************************************/
/*                                                                         */
/*  This function will take the passed parameters and saved them so that   */
/*  ProcessBeeper can actually turn the beeper on and off.   The first     */
/*  parameter, nmbr, is the number of times the beeper should beep.  The   */
/*  second parameter is what kind of sound is it(ALARM, ERROR or TRIGGER). */
/*  The beeper will not sound if this kind of sound has been disabled.     */
/*                                                                         */
/***************************************************************************/
{
   switch (Type) {
      case ALARMBEEP:
         if ((CurrentSetup.BeeperAlarm & BIT0) == BIT0) {
            BeepOnTime = ALARMBEEPTIME;
            asm(" ori.w #$8,$fffe1C");    /* Turn Beeper on         */
            UserCfgOutputOn(OUTPUT_EXT_BEEPER);
            NumberOfBeeps = 5;
            BeeperOn = TRUE;
         }
         break;

      case PSOSBEEP:
         BeepOnTime = PSOSBEEPTIME;
         asm(" ori.w #$8,$fffe1C");    /* Turn Beeper on         */
         UserCfgOutputOn(OUTPUT_EXT_BEEPER);
         NumberOfBeeps = 1;
         BeeperOn = TRUE;
         break;

      case ERRORBEEP:
         if ((CurrentSetup.BeeperError & BIT0) == BIT0) {
            BeepOnTime = ERRORBEEPTIME;
            asm(" ori.w #$8,$fffe1C");    /* Turn Beeper on         */
            UserCfgOutputOn(OUTPUT_EXT_BEEPER);
            NumberOfBeeps = 3;   
            BeeperOn = TRUE;
         }
         break;

      case TRIGGERBEEP:
         if (((CurrentSetup.BeeperTrigger & BIT0) == BIT0)
              || (CurrentSequence == CALIBRATION)) /* Beep during calibration*/
         {                                         /* even when disabled     */
            BeepOnTime = TRIGGERBEEPTIME;
            asm(" ori.w #$8,$fffe1C");    /* Turn Beeper on         */
            UserCfgOutputOn(OUTPUT_EXT_BEEPER);
            NumberOfBeeps = 1;   
            BeeperOn = TRUE;
         }
         break;

      case CONFIRMBEEP:
            BeepOnTime = CONFIRMBEEPTIME;
            asm(" ori.w #$8,$fffe1C");    /* Turn Beeper on         */
            NumberOfBeeps = 3;
            BeeperOn = TRUE; 
            UserCfgOutputOn(OUTPUT_EXT_BEEPER);
            break;

      default:
         BeepOnTime = 0;
         BeeperOn = FALSE;
         break;
   }
}



void CheckBeeper(void)
{
   if (NumberOfBeeps > 0) {
      if (--BeepOnTime <= 0) {
         TurnOffBeeper();
      }
   }
}



void TurnOffBeeper(void){

   if(NumberOfBeeps-- <= 1){
      asm(" andi.w #$fff7,$fffe1C");       /* Turn Beeper off       */
      BeepOnTime = 0;
      BeeperOn = FALSE;
      NumberOfBeeps = 0;
      UserCfgOutputOff(OUTPUT_EXT_BEEPER);
   }
   else{
      BeepOnTime = ERRORBEEPTIME;
      if(BeeperOn == TRUE){
         asm(" andi.w #$fff7,$fffe1C");       /* Turn Beeper off       */
         BeeperOn = FALSE;
         UserCfgOutputOff(OUTPUT_EXT_BEEPER);
      }
      else{
         asm(" ori.w #$8,$fffe1C");    /* Turn Beeper on         */
         BeeperOn = TRUE;
         UserCfgOutputOn(OUTPUT_EXT_BEEPER);
      }
   }
}

 

/* Include for Unit test */
#ifdef INCLUDE_BEEP_UNIT_TEST
/*    #include "..\ut\beep.ut"   */
#endif
/* End of include for unit test */
