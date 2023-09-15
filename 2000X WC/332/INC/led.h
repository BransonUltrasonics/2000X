/* $Header:   K:/APPS/PVCS Pro/332new/INC/LED.H_V   2.11   Nov 15 2000 09:45:10   atali  $ */
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

   Module name:  

   Filename:      led.h


            Written by: Laura Markure 
                  Date: 5/13/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             5/13/96      LAM         Initial
      1             8/22/96      LAM         chged prototypes
      2             9/11/96      LAM         added led defines
      3             10/11/96     PhilJ       Switch LEFTLED and RIGHTLED defines
      4             01/31/97     PhilJ       Added defines for LEFTRIGHT LED.
      5             05-01-97     BEKymer     Add defines for BLINKON, BLINKOFF
      6.2.8         08-21-97     LAM         Add defines for 0% LED           
      2.9           09-09-97     BEKymer     Remove BlinkCondition argument
                                             from UpdateBarGraph
                                             Change led defines to enum's
      2.10          09-02-98     BJB         Added definitions for up/down LED
                                              bits.
      2.11          11-15-00     AT          Added ResetLedRequiredState definition (was static before)

 
 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  


/*------------------------------- DEFINES ----------------------------------*/

enum LEDS {

   RESETLED = 0,
   UPLED,
   DOWNLED,
   RIGHTLED,
   LEFTLED,
   OFFLED,
   LEFTRIGHTLEDON,
   ZEROPERCENTLED,
   ALLLEDS        };        /* This must be last, it is used as index check */


#define UPLEDBIT     0x200
#define DOWNLEDBIT   0x400

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           


/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


void UpdateLED(enum LEDS, UINT8 OffOn);
void UpdateBarGraph(SINT16 PowerPercent);
void GetLedStatus(void);

extern UINT16 ResetLedRequiredState;


