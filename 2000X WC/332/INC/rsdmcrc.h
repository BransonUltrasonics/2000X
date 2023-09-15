/* $Header:   L:/pvcs/1000/psos332/archives/inc/RSDMCRC.H_v   2.1   01 Aug 1996 14:51:02   BKYMER  $ */

#ifndef RDSM_CHECK_CRC_H
#define RSDM_CHECK_CRC_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: RSDM Check CRC

   Filename: rsdmcrc.h


 -------------------------------- REVISIONS ------------------------------------

    Rev #      Date      Author      Description
    =====    ========    ======      ===========

------------------------------- DESCRIPTION -----------------------------------

   This file contains interface for checking s-record CRC.

 ------------------------------ INCLUDE FILES ----------------------------------
*/
/*
 --------------------------------- DEFINES -------------------------------------
*/
/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/
typedef enum { CRC_GOOD, 
               CRC_BAD 
} CRC_STATUS_TYPE;
   
/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

CRC_STATUS_TYPE RsmCheckCrc (UINT8 *string, UINT16 count);

#endif /* RSDM_CHECK_CRC_H */
