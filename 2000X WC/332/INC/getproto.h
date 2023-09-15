/* $Header:   L:/pvcs/1000/psos332/archives/inc/getproto.h_v   2.2   04 Dec 1996 08:21:02   lmarkure  $ */
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

   Module name:  

   Filename:      getproto.h


            Written by: Laura Markure 
                  Date: 5/16/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             5/16/96      LAM         Initial
      1             11/22/96     LAM         cleanup warnings
 
 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  

#include "timers.h"                          /* setting and clearing timers          */
#include "parametr.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
 

/*--------------------------- Function Prototypes --------------------------*/

SHELL_STATUS_TYPE ShellProtocolSelection(
    CIB_PROTOCOL_TYPE_TYPE              *protocol_ptr,
    UINT32                              protocol_mngr_qid,      /* Protocol Manager QID       */
    CIB_INTERFACE_TYPE_TYPE             *session_port_ptr,      /* CIB port designation       */
    UINT32                              shell_qid,              /* Shell Queue ID             */
    PARAMETER_ID_TYPE                   timer_param_id,         /* Parameter ID for timer     */
    TIMER_NAME_TYPE                     timer_name,             /* Timer designator           */
    UAR_MSG                             *uar_msg_ptr );         /* Returns UAR message        */


void PromptForProtocol(
    UINT32                              protocol_mngr_qid,      /* Protocol Manager QID       */
    CIB_INTERFACE_TYPE_TYPE             comm_port,              /* CIB port designation       */
    UINT32                              shell_qid,              /* Shell Queue ID             */
    TIME_REMAINING_TYPE                 duration,
    TIMER_NAME_TYPE                     timer_name );           /* Timer designator           */


SHELL_STATUS_TYPE ProtocolSelection(
    UINT8                                 * str_ptr,            /* String received from SCC     */
    CIB_PROTOCOL_TYPE_TYPE                * protocol_ptr );     /* Return protocol specifier    */
