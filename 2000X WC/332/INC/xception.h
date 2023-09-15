/* $Header:   L:/pvcs/1000/psos332/archives/inc/xception.h_v   2.2   16 Jun 1997 18:09:48   lmarkure  $ */
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
 --------------------------------- MODULE DESCRIPTION ------------------------------------

   Module  name: EXCEPTION_HANDLER  

   Filename: xception.c  



            Written by: Mark Lazarewicz  
                  Date: 1/20/96 
              Language:  "C"

 ------------------------------------- REVISIONS -----------------------------------------

   Revision #   Date       Author   Description
   ==========   ========   ======   ===========
      0         05-15-96   BEKymer  Initial Version, added function prototyping
      1.2.2     06-16-96   LAM      added interrupt prototypes                  
      

*/
/*--------------------------- Function Prototypes --------------------------*/


void    ExceptionHandler (void);
BOOLEAN IsStartModeMinMode(void);
void BusInt(void);
void AddInt(void);
void SpurInt(void);
void IllegalInstr(void);
void CHKCHK2(void);
void ZeroDivide(void);
void TRAPccTRAPv(void);
void PrivilegeVio(void);
void Vector10Int(void);
void ReservedInt(void);
void UserInt(void);
