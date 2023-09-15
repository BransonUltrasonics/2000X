/* $Header:   L:/pvcs/1000/psos332/archives/app/features.h_v   1.7   11 Aug 1998 13:18:44   jberman  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/***************************************************************************/
/*                                                                         */
/*  These defines are the bit assignments for both Reject and Suspect      */
/*  limits.  BIT0 is reserved for globally enabling or disabling all       */
/*  limits within the group.  BIT15 is unused.                             */
/*                                                                         */
/*  Notes: The M prefix in each name stands for Minus and the P stands     */
/*         for Plus.  For example, MTIMEBIT is the minus time bit.         */
/*                                                                         */
/*         The FORCE define is for Max Force during the weld cycle.        */
/*                                                                         */
/***************************************************************************/

/*
 --------------------------------- REVISIONS --------------------------------

   Revision #     Date            Author     Description
   ==========     ========        ======     ===========
      0                                      Initial Version
      1.50        07/28/97        PJ         Added IfFeatureEnabled prototype
      1.6         06/15/98        BJB        Added bit for Digital Filter
   	  1.7         08.05.98        JBerman  	 Removed Digital Filter from features

*/

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "param.h"

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/

#define TrgDelBit BIT0          // Trigger Delay 
#define FrcStpBit BIT1          // Force2, Force Step
#define AmpStpBit BIT2          // Amplitude Step
#define PstWldBit BIT3          // Post Weld Seek
#define FrqOfsBit BIT4          // Freq Offset
#define CycAbtBit BIT5          // Cycle Abort
#define ActClrBit BIT6          // Actuator Clear
#define SusLmtBit BIT7          // Suspect Limits 
#define AmpCrlBit BIT8          // Amp Control
#define FrqCrlBit BIT9          // Freq Control
#define AdjWleBit BIT10         // Adjust While Run
#define AdvCnrBit BIT11         // Advanced Counters
#define CrlLmtBit BIT12         // Control Limits
#define SeqOnfBit BIT13         // Sequence Flag, On/Off

 
/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

void UpdateSf(enum PARAM id);  
void BootSf(void);

BOOLEAN GetSF(void);
UINT8 IfFeatureEnabled(UINT32 , UINT32);
