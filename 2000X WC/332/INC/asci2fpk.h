/* $Header:   L:/pvcs/1000/psos332/archives/inc/ASCI2FPK.H_v   2.2   01 Aug 1996 14:52:30   BKYMER  $ */
#ifndef TRANSLATE_ASCII_TO_FP_KP_H
#define TRANSLATE_ASCII_TO_FP_KP_H
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

   Module name: TRANSLATE_ASCII_TO_FP_KP

   Filename: asci2fpk.h 


            Written by:  Mark Lazarewicz
                  Date:  03/22/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

  Revision #   Date       Author   Description
  ==========   ========   ======   ===========
     0         03/22/96   Mark L   Initial

 ------------------------------- DESCRIPTION -----------------------------------
  This file defines the interface to the executable function of the same
  name. 

 ------------------------------ INCLUDE FILES ----------------------------------
*/ 

#include "ascii.h"	        /* hex for ascii characters */
#include "fpkptype.h"	     /* definitions for fp_keypress */

/*
 --------------------------------- DEFINES -------------------------------------
*/                                   

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/ 
/* returned processing  status */

typedef UINT8 ASCII_CHAR_TYPE;

typedef packed enum
   {
   TRANSLATION_OK = 0u,
   TRANSLATION_ERROR,
   TRANSLATION_IN_PROGRESS
   }  ASCII_TRANSLATION_STATUS_TYPE;
                         
#endif /* TRANSLATE_ASCII_TO_FP_KEYPRESS_H */

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/  
ASCII_TRANSLATION_STATUS_TYPE 
     translate_ascii_to_fp_kp(ASCII_CHAR_TYPE ascii_char,    
                              FP_KEY_PAD_TYPE *fp_keypress); 
               
void TranslateAsciiToFpInit(void);
/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/    

