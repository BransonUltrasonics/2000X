/* $Header:   K:/APPS/PVCS Pro/332new/INC/BEEP.H_V   2.8   29 Mar 2001 15:21:02   BKymer  $ */
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

   Module name:  

   Filename:      beep.h


            Written by: Laura Markure  
                  Date: 4/23/96  
              Language:  "C"

----------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            4/18/96       BEK         Initial Release
      1            4/23/96       LAM         Rewritten for PSOS
      2            10/21/96      LAM         added PSOS beep
      3            01/06/97      LAM         chged prototype
      2.8          03-29-01      BEKymer     Added CONFIRMBEEP
      

----------------------------- DESCRIPTION -----------------------------------

*/

/***   ***   Things needed by all files to deal with Beeper   ***   ***/

 
/*
 ------------------------------ INCLUDE FILES ----------------------------------
*/  

/*
 ------------------------------- DEFINES ---------------------------------------
*/

enum BEEPS { ALARMBEEP, ERRORBEEP, TRIGGERBEEP, PSOSBEEP, CONFIRMBEEP, ALLBEEP };

#define ALARMBEEPTIME          5        /* ON time for alarm beep (ms)   */
#define ERRORBEEPTIME          5        /* ON time for error beep (ms)   */
#define TRIGGERBEEPTIME        7        /* ON time for trigger beep (ms) */
#define PSOSBEEPTIME           20       /* ON time for trigger beep (ms) */
#define BEEPOFFTIME            10       /* OFF time for all beepers (ms) */
#define CONFIRMBEEPTIME        3        /* ON time for alarm beep (ms)   */

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           



/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void CheckBeeper(void);
void TurnOffBeeper(void);
void Beep(enum BEEPS Type);


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/




