/* $Header:   K:\APPS\PVCS Pro\332new\INC\CKPTGBUF.H_V   2.2   Dec 16 1999 15:41:26   lmarkure  $ */
#ifndef CK_PT_GETBUF_H
#define CK_PT_GETBUF_H
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
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Ck_Pt_Getbuf

   Filename: ckptgbuf.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0            02/08/96      Mark Lazar   Initial release 
     2.2           12/16/99      LAM          removed unused error handling code


------------------------------- DESCRIPTION -----------------------------------

 This header contains all the information needed by ckptgbuf.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include  "portable.h"      /* general hardware defines...   */
#include  "ck_qsend.h"     
#include  "ticks.h"         /* use of MILLS_TO_TICKS in call */

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

void CkPtGetbuf(
   UINT32              partition_id,
   void              **psos_buffer_ptr,
   ERROR_CALLER_TYPE   caller_module_id,
   UINT32              caller_line_number,
   UINT32              psos_error_retry_count /* MILLS_TO_TICK convertion expected before call */
   ); 

#endif /* CK_PT_GETBUF_H */
