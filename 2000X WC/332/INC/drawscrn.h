/* $Header:   D:/SWLab/VMdb/2000Series/INC/drawscrn.h_v   1.5   Oct 22 2007 19:00:52   YGupta  $ */
#ifndef DRAWSCRN_H
#define DRAWSCRN_H
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
------------------------------ MODULE DESCRIPTION -----------------------------

------------------------------ REVISIONS --------------------------------------

   Revision #      Date          Author          Description
   ==========      ========      ======          ===========
     1.0           04/17/03       SCM            Initial release
     1.2           07/10/03       SCM            Added PVCS Header.
     1.3           10-22-07       NHAhmed        Changes done for LangTest phase 0

      
      
*/      

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/
#include "portable.h"

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
#define CHANNEL_A        0
#define CHANNEL_B        1
#define MAX_BUFFER_SIZE  100
/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

      
/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/


void TouchScrnBeep (UINT16 Count);



#endif