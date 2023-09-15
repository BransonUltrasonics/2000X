/* $Header:   L:/pvcs/1000/psos332/archives/inc/INITWELD.H_v   2.2   31 Dec 1997 11:54:52   bbarrows  $ */

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

   Module name: StartWelder

   Filename:  initweld.c

   Function name: StartWelder


            Written by: Mark Lazarewicz  
                  Date:  1/24/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #  Date       Author   Description
   ==========  ========   ======   ===========
      0        1/24/96    Mark L   Initial Version
      1        02/11/96   Mark L   Add DPRM,WMGR,WDPM
      2        05-15-96   BEKymer  Add proper function prototyping
		2.2      12-30-97   BJB      Terminated comment to prevent compiler msg


*/
/*--------------------------- Function Prototypes --------------------------*/

CREATE_AND_START_TASK_STATUS_TYPE StartWelder(void);
