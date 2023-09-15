/* $Header:   K:\APPS\PVCS Pro\332new\INC\COMMNMSG.H_V   2.4   May 10 1999 14:55:20   lmarkure  $ */
#ifndef COMMON_MSG_FIELD_H
#define COMMON_MSG_FIELD_H
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

   Module name: NA

   Filename:    commnmsg.h


            Written by: Mark Lazarewicz 
                  Date: 02/08/96 
              Language:  "C"

 -------------------------------- REVISIONS -----------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0            02/08/96      Mark Lazarewicz Initial release 
      2.3 		   04/19/99		 OFI			 Changed for DIAB
	  2.4          05/10/99      LAM          added max and min for packed

 ------------------------------- DESCRIPTION -----------------------------------
  COMMON_MSG_FIELD_TYPE incorporates common information required for all pSos+
  messages queue messages.
*/

/*
 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "opcodes.h"              /* typedef enum for all message opcodes  */
#include "names.h"
/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/ 
/* An indication of whether the provided pointer (if any) should be deallocated as a  */
/* pSos buffer                                                                        */
typedef __packed__ enum 
   {
   DATA_PTR_DEALLOC    = 0u,
   DATA_PTR_NO_DEALLOC = 1,
   NO_DATA_PTR         = 255
   } QUEUE_POINTER_FLAG_TYPE;

/* This common field shall appear at the start of all pSos+ queue messages */
/* This type is 32-bits in size                                            */
typedef __packed__(2,1) struct
    {   
    QUEUE_POINTER_FLAG_TYPE pointer_flag;   
    SOURCE_TASK_ID_TYPE     source_task;
    MSG_OPCODE_TYPE         opcode;
    } COMMON_MSG_FIELD_TYPE;

#endif /* COMMON_MSG_FIELD_H */
