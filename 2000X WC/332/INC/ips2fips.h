/* $Header:   L:/pvcs/1000/psos332/archives/inc/IPS2FIPS.H_v   2.1   01 Aug 1996 14:51:42   BKYMER  $ */
#ifndef RSSN_XLATE_IPS_TO_FIPS_H
#define RSSN_XLATE_IPS_TO_FIPS_H
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

   Module name:   rssn_xlate_ips_to_fips

   Filename:      rsnxlate.h


            Written by: Mark Lazarewicz 
                  Date: 03/14/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            03/14/96      Mark L      Initial Version

 ------------------------------- DESCRIPTION -----------------------------------

 Function prototype for utility that converts IPS resposne message to FIPS response string

 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "portable.h"            /* normal file-includes                 */



/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


UINT16 RssnxlateIpsToFips(
   char                                *response_string_ptr,       /* Put ASCII conversion here      */
   IPS_COMMAND_TYPE                    *ips_cmnd_ptr );            /* IPS command                    */


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif  
