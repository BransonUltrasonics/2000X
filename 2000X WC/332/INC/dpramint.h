/* $Header:   L:/pvcs/1000/psos332/archives/inc/DPRAMINT.H_v   2.1   01 Aug 1996 14:50:10   BKYMER  $ */
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

   Filename:      dpramint.h


            Written by: Laura Markure 
                  Date: 5/13/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             5/13/96      LAM         Initial
 
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

void DpramInit(void);
void IsrDpram(void);

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/


