/* $Header:   D:/SWLab/VMdb/2000Series/INC/ENCODER.H_V   2.3   Jan 09 2006 13:55:34   lmarkure  $ */
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

   Filename:      encoder.h


            Written by: Laura Markure 
                  Date: 5/13/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             5/13/96      LAM         Initial
      2.3          12/14/05      LAM         changed prototype for metric encoder
 
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

UINT32 ReadEncoder(void);
UINT16 GetCycleDist(void);
UINT32 VelocityEstimator(UINT32 NewEncoderPosition);
void ZeroEncoder(void);

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/


