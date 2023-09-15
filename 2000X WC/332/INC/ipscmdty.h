/* $Header:   K:\APPS\PVCS Pro\332\INC\IPSCMDTY.H_V   2.4   Apr 19 1999 15:55:34   ofingere  $ */
#ifndef IPS_COMMAND_TYPE_H
#define IPS_COMMAND_TYPE_H
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

   Module name: ips_command_type.h

   Filename: ipscmdty.h


            Written by: Mark Lazarewicz 
                  Date: 03/21/96 
              Language:  "C"

------------------------------ REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
        0           03/21/96      Mark L      Initial Version
        1           07/05/96      LAM         cleanup warnings
		2.4			04/19/99	  OFI		  Changed for DIAB
 ------------------------------- DESCRIPTION --------------------------------
 All the type definitions in this file support the definition of the
 IPS_COMMAND_TYPE.  This type consists of a byte count indicating the number
 of bytes of data and status, a direction field characterizing the message 
 as a command or a response, a command identification field pair indicating
 the type of the message and the specific message within that type, status,
 and the data associated with the message. The data field is defined as an
 array of one byte.  As IPS data will range from none to a possible 64K bytes,
 the data typing is designed so the data element of the IPS_COMMAND_TYPE is
 used as a start address of the IPS data.  See IPS Command Specification.

 ------------------------------ INCLUDE FILES -------------------------------
*/
#include "portable.h"
/*
 --------------------------------- DEFINES -------------------------------------
*/

#define START_OF_IPS_DATA       8
#define IPS_CMD_HEADER_INFO_SIZE    2  /* IPS Command header size */
#define IPS_RSP_HEADER_INFO_SIZE    4  /* IPS Response header size, incl. status */

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/                              

/* The byte count field indicates the bytes of data an status */
typedef UINT16 IPS_BYTE_COUNT_TYPE;                                             

/* Valid information for response messages, it is a status indication of the */
/* processing associated with a previous IPS command.                        */
/* This type must be 16 bit in size.                                          */
typedef enum
   {           
   IPS_MIN_STATUS_SIZER      = 0u,
   IPS_PROCESSING_OK         = 1,
   IPS_PROCESSING_ERROR      = 2,
   IPS_ALIGNMENT_UNAVAILABLE = 3,
   IPS_MAX_STATUS_SIZER      = 65535
   } IPS_STATUS_TYPE;
                        
/* An indication of the station-to-station direction of the ips message. */
/* This type must be defined as no more than two enumerations (one bit).          */
typedef enum
   {
   IPS_COMMAND = 0u,
   IPS_RESPONSE = 1
   } IPS_DIRECTION_TYPE;                                       

/* An indication of the type of ips command.                      */
/* This type must have no more than four enumerations (two bits). */
typedef enum
   {
   IPS_READ_PARAMETER  = 0u,
   IPS_WRITE_PARAMETER = 1,
   IPS_ACTION          = 2,
   IPS_DRC             = 3
   } IPS_TYPE_ID_TYPE;

                         
/* This structure provides message identification information and is assigned */
/* values from indicated enumerations. See IPS Command Specification.         */
typedef struct
   {
   UINT16 direction  : 1;    /* IPS_DIRECTION_TYPE */
   UINT16 not_used   : 3;       
   UINT16 type_id    : 2;    /* IPS_TYPE_TYPE      */
   UINT16 command_id : 10;   /* PARAMETER_ID_TYPE,IPS_ACTION_TYPE,IPS_DRC_TYPE */
   } IPS_COMMAND_ID_TYPE;                                                             
       
typedef UINT8  IPS_DATA_TYPE[START_OF_IPS_DATA];

typedef struct              
   {
   IPS_STATUS_TYPE status;     /* 16 bits */
   IPS_DATA_TYPE   data;       /* 1 to oo */
   } IPS_RESPONSE_DATA_TYPE;
             
typedef IPS_DATA_TYPE IPS_COMMAND_DATA_TYPE;

typedef union
   {
   IPS_COMMAND_DATA_TYPE   command;
   IPS_RESPONSE_DATA_TYPE response;    
   } IPS_COMMAND_RESPONSE_DATA_TYPE;
                      
/* This type is constructs a complete IPS Message */
typedef struct
   {
   IPS_BYTE_COUNT_TYPE            byte_count; /* 16 bits */
   IPS_COMMAND_ID_TYPE            id;         /* 16 bits */
   IPS_COMMAND_RESPONSE_DATA_TYPE data;       /* 1 to oo */
   } IPS_COMMAND_TYPE;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* IPS_COMMAND_TYPE_H */
