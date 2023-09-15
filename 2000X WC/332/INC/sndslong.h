/* $Header:   L:/pvcs/1000/psos332/archives/inc/SNDSLONG.H_v   2.1   01 Aug 1996 14:49:02   BKYMER  $ */
#ifndef SEND_COMM_STRING_LONG_H
#define SEND_COMM_STRING_LONG_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: 

   Filename:    send_comm_string_long.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========

 ------------------------------- DESCRIPTION -----------------------------------

 This header contains  the interface needed by send_comm_string_long.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "portable.h"             /* normal file-includes                 */


/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/


/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/
void send_comm_string_long(
    char                                *string_ptr,                /* String to transmit            */
    UINT32                              partition_id,               /* partition id of buffer        */
    UINT32                              qid );                      /* Protocol Manager Queue ID     */

void send_comm_str_with_length(
    char                                *string_ptr,                /* String to transmit            */
    UINT32                              partition_id,               /* partition id of buffer        */
    UINT32                              qid,                        /* Protocol Manager Qu
eue ID     */
    UINT16                              buf_length );               /* Protocol Manager Queue ID     */

#endif




