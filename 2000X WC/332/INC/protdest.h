/* $Header:   L:/pvcs/1000/psos332/archives/inc/PROTDEST.H_v   2.1   01 Aug 1996 14:50:38   BKYMER  $ */
#ifndef PROTOCOL_DEST_INFO_MSG_H
#define PROTOCOL_DEST_INFO_MSG_H
       
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name: 

   Filename: protocol_dest_info_msg.h 

 
            Written by:  
                  Date: 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author           Description
   ==========      ========      ===========      ==============

 ------------------------------- DESCRIPTION -----------------------------------

 This message is sent by a protocol to the Comm_Outbound_Msg_Router to inform it
 that a new protocol is running on a port.

*/

/*
 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "commnmsg.h"  
#include "cibinfo.h"      /* for CIB_INTERFACE_TYPE, and CIB_PROTOCOL_TYPE */

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/* value for the queue in the router table which indicates that no protocol is active */
#define INACTIVE_PROTOCOL_INDICATION    0
                                   
/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/

typedef struct 
    {  
    COMMON_MSG_FIELD_TYPE   common;             /* 32 bits */
    CIB_INTERFACE_TYPE_TYPE cib_interface_type; /*  8 bits */
    CIB_PROTOCOL_TYPE_TYPE  cib_protocol_type;  /*  8 bits */
    UINT16                  spare;              /* 16 bits */
    UINT32                  psos_queue_id;      /* 32 bits */
    UINT32                  psos_partition_id;  /* 32 bits */
    } PROTOCOL_DEST_INFO_MSG;

#endif /*  PROTOCOL_DEST_INFO_MSG_H */
