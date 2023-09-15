/* $Header:   D:/SWLab/VMdb/2000Series/INC/SELCTKEY.H_V   2.22   09 Sep 2008 20:42:12   nhahmed  $ */
#ifndef SELCTKEY_H
#define SELCTKEY_H
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

   Filename:      selctkey.h



 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      1            10/14/96      LAM         cleanup warnings         
      2            10/18/96      PhilJ       Delete GoBackToMenu Prototype.
      3            04/28/97      LAM         added include files that are needed
      4.2.10       06/17/97      Philj       added EDIT_PARAM_MSG_QUEUE_TYPE
      2.11         10/16/97      BJB         Added def of AlphaEntryDone.
      2.12         11/10/97      BJB         Got rid of unused InitSelectKey().
      2.13         12/29/97      BJB         SendFakeKeyPress() now returns pSOS
                                              error code.
      2.14         04/28/98      BJB         Added prototype for AlphaEntry().
      2.15         05-15-98      BJB         Deleted prototypes for
                                              DisplayMinMaxError(),
                                              DisplayLastValue(), which are now
                                              local to SELCTKEY.C
      2.16         05-28-98      BJB         Deleted prototypes for
                                              IncrementFreqOffset(),
                                              DecrementFreqOffset().
      2.17         07/31/98      BJB         SendFakeKeyPress() moved to
                                              GETMSG.C
      2.18         09/27/99      LAM         make sure file is linked in once per module
      2.20         06/10/03      bWadia      "VarInfo" struct defenition is added.
	   2.21         09-04-08		ygupta      Cleanup for Multilanguage project.
	   2.22         09-09-08		NHAhmed     Cleanup for multi-language support.


 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  

#include "commnmsg.h"
#include "menu.h"
#include "param.h"
#include "keypad.h"
#include "error.h"


/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           



typedef struct
   {
   COMMON_MSG_FIELD_TYPE    common;
   EDIT_PARAM_TYPE          param_id;
   SINT32                   value1;
   UINT16                   value2;
   UINT16                   value3;
   } EDIT_PARAM_MSG_QUEUE_TYPE;

/*
 --------------------------- GLOBAL VARIABLES ----------------------------------
*/


/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

void UpdateCurrentPreset(enum PARAM Id, SINT32 Value1, UINT16 Value2);

#endif
