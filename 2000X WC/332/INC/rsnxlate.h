/* $Header:   L:/pvcs/1000/psos332/archives/inc/RSNXLATE.H_v   2.3   01 Aug 1996 14:51:02   BKYMER  $ */
#ifndef RSSN_XLATE_IPS_TO_FIPS_H
#define RSSN_XLATE_IPS_TO_FIPS_H
/*
 ------------------------ MODULE DESCRIPTION -------------------------------

   Module name:   rssn_xlate_ips_to_fips

   Filename:      rssn_xlate_ips_to_fips.h


            Written by: 
                  Date:  
              Language:  "C"

 ---------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author   Description
   ==========   ========   ======   ===========
       1        05-15-96   BEKymer  Remove underscores and add cap's in prototype
       2        07-04-96   LAM      cleanup 


 ------------------------------- DESCRIPTION -------------------------------

 Function prototype for utility that converts IPS resposne message to FIPS response string

 ------------------------------ INCLUDE FILES -------------------------------
*/


/*-------------------------------- DEFINES ---------------------------------*/


/*--------------------------- TYPE DECLARATIONS ----------------------------*/                           

#endif  

/*-------------------------- FUNCTION PROTOTYPES ---------------------------*/

UINT16 RssnXlateIpsToFips(
   BYTE                                *response_string_ptr,       /* Put ASCII conversion here      */
   IPS_COMMAND_TYPE                    *ips_cmnd_ptr );            /* IPS command                    */


/*----------------------------- EXTERNAL DATA ------------------------------*/

