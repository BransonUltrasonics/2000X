/* $Header:   L:/pvcs/1000/psos332/archives/inc/CVTERROR.H_v   2.2   01 Aug 1996 14:48:42   BKYMER  $ */
#ifndef CVT_ERROR_TO_STRING_H
#define CVT_ERROR_TO_STRING_H
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96              */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/


/*
-------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name:  cvt_error_to_string
  
   File   name:  cvterror


   Filename: Mark Lazarewicz      

            Written by: Mark Lazarewicz 
                  Date: 03/11/96 
              Language:  "C"

------------------------------ REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
       0           03/11/96      Mark L      Initial Version
       1           07/06/96      LAM         cleanup warnings

----------------------------- DESCRIPTION -----------------------------------

   This is the prototype for converting log entries to strings.

---------------------------- INCLUDE FILES ----------------------------------
*/

#include "swaredat.h"
#include "err_data.h"

/*
 --------------------------------- DEFINES -------------------------------------
*/

#define  MAX_ERR_LINE_LEN    172

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

SIZE_T CvtErrorLogEntry(
   ERROR_LOG_DATA_TYPE *error_log_entry,
   BYTE                *converted_string
   );

SIZE_T CvtSwareLogEntry(
   SWARE_LOG_DATA_TYPE *sware_log_entry,
   BYTE                *converted_string
   );  

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/


#endif /* CVT_ERROR_TO_STRING_H */
