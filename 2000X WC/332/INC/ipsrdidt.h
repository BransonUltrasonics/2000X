/* $Header:   L:/pvcs/1000/psos332/archives/inc/IPSRDIDT.H_v   2.1   01 Aug 1996 14:52:24   BKYMER  $ */

#ifndef IPS_READ_ID_TYPE_H
#define IPS_READ_ID_TYPE_H
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

   Module name:ips_read_id_type 

   Filename: ipsrdidt.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0             03/04/96      Mark L      Initial

 ------------------------------- DESCRIPTION -----------------------------------

 This header contains the definitions of Command Ids when the IPS Type Id indicates
 the IPS is an Read type. 

 ------------------------------ INCLUDE FILES ----------------------------------
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/

/* Define ranges for each of the Read commands */
#define FIRST_READ_CMD     0
#define LAST_READ_CMD      1023

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

#endif /* IPS_READ_ID_TYPE_H */
