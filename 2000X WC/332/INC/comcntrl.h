/* $Header:   K:\APPS\PVCS Pro\332new\INC\COMCNTRL.H_V   2.4   May 05 1999 13:41:56   lmarkure  $ */
#ifndef COMM_CONTROL_MSG_H
#define COMM_CONTROL_MSG_H
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
-------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name:  n/a

   Filename:     comm_control_msg.h


            Written by: Mark Lazarewicz 
                  Date: 02/08/96 
              Language:  "C"

----------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0            02/08/96      Mark Lazarewicz Initial release 
	  2.3		   04/19/99		 OFI			 Changed for DIAB
	  2.4          05/04/99      LAM          fixed packed for DIAB
---------------------------- DESCRIPTION -----------------------------------

 Used by protocol manager, port manager and shell to change the communication
 mode, line termination character or protocol.


--------------------------- INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "cibinfo.h"
#include "commnmsg.h"


/*
------------------------------- DEFINES -------------------------------------
*/

/*
-------------------------- TYPE DECLARATIONS --------------------------------
*/


typedef __packed__ enum
   {
   COMM_CHANGE_PROTOCOL_CMND         = 0,
   COMM_CHANGE_MODE_CMND             = 1,
   COMM_CHANGE_TERMINATOR            = 2,
   COMM_COMMAND_RESPONSE_SIZER       = 255u
   } COMM_COMMAND_RESPONSE_TYPE;

typedef __packed__ enum
   {
   COMM_ASCII_LINE_MODE    = 0,
   COMM_ASCII_LINE_NO_ECHO = 1,
   COMM_ASCII_CHAR_MODE    = 2,
   COMM_MODE_SIZER         = 255u
   } COMM_MODE_TYPE;

typedef __packed__ struct
   {
   COMMON_MSG_FIELD_TYPE             common;
   COMM_COMMAND_RESPONSE_TYPE        cmnd_resp;
   CIB_PROTOCOL_TYPE_TYPE            protocol;
   COMM_MODE_TYPE                    mode;
   UINT8                             term_char;
   UINT8                             spare[8];
   } COMM_CONTROL_MSG;

/*
------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
---------------------------- EXTERNAL DATA ----------------------------------
*/

#endif


