/* $Header:   L:/pvcs/1000/psos332/archives/inc/COMMTASK.H_v   2.2   01 Aug 1996 14:48:26   BKYMER  $ */
#ifndef COMM_TASK_PARAMS_TYPE_H
#define COMM_TASK_PARAMS_TYPE_H
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

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: NA

   Filename:    commtask.h


            Written by:  
                  Date:  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #   Date       Author          Description
    ==========   ========   ======          ===========
       0         02/08/96   Mark Lazarewicz Initial release 
       1         05-16-96   BEKymer         Add proper function prototyping



------------------------------- DESCRIPTION -----------------------------------

 This file defines a structure used for passing parameters to communication tasks
 when they are started.

 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "cibinfo.h"

/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/*
 * This structure is used to pass parameters to communication tasks when they
 * are started.
 *
 * NOTE: This structure is limited to 16 bytes by pSOS
 */
typedef struct
   {
   UINT32                              port_mngr_qid;              /* QID for Port Manager       */
   UINT32                              protocol_mngr_qid;          /* QID for Protocol Manager   */
   UINT32                              shell_qid;                  /* QID for Nucleus Shell      */
   CIB_INTERFACE_TYPE_TYPE             comm_port;                  /* Communication port         */
   UINT8                               unused[3];                  /* Not currently defined      */
   } COMM_TASK_PARAMS_TYPE;



/*-------------------------- FUNCTION PROTOTYPES ---------------------------*/

void RemoteSerialDataManager(void);



/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif


