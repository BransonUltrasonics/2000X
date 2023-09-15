/* $Header:   D:/databases/VMdb/2000Series/INC/WC_ISR.H_V   2.5   Jan 03 2018 13:03:44   RCHAPA  $ */
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

   Filename:      wc_isr.h


            Written by: Laura Markure 
                  Date: 5/13/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             5/13/96      LAM         Initial
      2.2          07/30/98      BJB         Added prototype for MinMsInt().
      2.4		   10/18/17		 RChapa		 Add variable DUPSMsTmr for DUPS Parameters refresh
      2.5		   01/03/18		 RChapa		 Removed variable DUPSMsTmr for DUPS Parameters refresh
 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  


/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
 
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void MsInt(void);
void MinMsInt(void);

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/
