/* $Header:   L:/pvcs/1000/psos332/archives/inc/rssnline.h_v   2.3   15 Apr 1997 11:20:44   lmarkure  $ */
#ifndef RSSN_LINE_MODE
#define RSSN_LINE_MODE
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
------------------------------ MODULE DESCRIPTION -----------------------------

------------------------------ REVISIONS --------------------------------------

   Revision #      Date          Author          Description
   ==========      ========      ======          ===========
      0            02/22/96      Mark Lazarewicz Initial release 
      1            05-15-96      BEKymer         Add proper function prototyping
      2            04/21/97      LAM             1line data version


 ------------------------------- DESCRIPTION -----------------------------------



 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include  <psos.h>
#include  "return.h"
#include  "ipscmdty.h"
#include  "ipscdmsg.h"

/*
 --------------------------------- DEFINES -------------------------------------
*/

#define   RSSN_MIN_LINE_LENGTH     4

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef enum {

               RSSN_LINE_OK=0,
               RSSN_LINE_CMND_ERR,
               RSSN_LINE_DATA_ERR,
               RSSN_LINE_ARG_ERR,
               RSSN_LINE_UKWN_ERR

             } RSSN_LINE_MODE_STATUS;

#endif /* RSSN_LINE_MODE */


/*--------------------------- FUNCTION PROTOTYPES --------------------------*/

RSSN_LINE_MODE_STATUS    RssnLineMode(UINT8 *, IPS_COMMAND_TYPE *, UINT16);
RSSN_LINE_MODE_STATUS    RssnLineMode(
    UINT8                            *line_ptr,         /* input                             */
    IPS_COMMAND_TYPE                 *ips_cmnd_ptr,     /* output                            */
    UINT16                           line_length);       /* length of line_ptr string         */


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

