/* $Header:   L:/pvcs/1000/psos332/archives/inc/ADINITYP.H_v   2.1   01 Aug 1996 14:52:20   BKYMER  $ */
#ifndef ASCII_DIAGS_INITIATOR_TYPE_H
#define ASCII_DIAGS_INTITIATOR_TYPE_H
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

   Module name: ASCII_DIAGS_INITIATOR_TYPE

   Filename: adinityp.h 


            Written by: Mark Lazarewicz
                  Date: 03/22/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

  Revision #   Date       Author   Description
  ==========   ========   ======   ===========
      0        03/22/96   Mark L   Initial

 ------------------------------- DESCRIPTION -----------------------------------
  This file defines the ascii diags initiator type. This type is used in
  ascii_diags_interface_manager.c and send_screen_data.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/ 

/*
 --------------------------------- DEFINES -------------------------------------
*/                                   

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/ 

typedef packed enum
   {
   AIPS_INITIATED_ASCII = 0u,
   FPSP_INITIATED_ASCII
   } ASCII_DIAGS_INITIATOR_TYPE;

#endif /* ASCII_DIAGS_INITIATOR_TYPE_H */

