/* $Header:   L:/pvcs/1000/psos332/archives/inc/PSOS_TBL.H_v   2.1   01 Aug 1996 14:50:46   BKYMER  $ */
#ifndef DETERMINE_SYSTEM_OBJECT_ID_H
#define DETERMINE_SYSTEM_OBJECT_ID_H 
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

   Module name:   Determine_System_Object_ID

   Filename:      psos_tbl.h


            Written by: Mark Lazarewicz 
                  Date: 1/15/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========

 
 ------------------------------- DESCRIPTION -----------------------------------

   This file contains definitions for determine_system_object_id.c

*/

/*
 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"


/*
-------------------------------LOCAL DEFINES-------------------------------------
 */

#define END_OF_TABLE_MARKER	0	/*invalid psos task/queue name */


/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/

typedef packed enum
   {
   RETURN_SOURCE_TASK_ID = 6,
   RETURN_PSOS_TASK_ID = 7,
   RETURN_PSOS_QUEUE_ID = 8
   } RETURN_ID_KIND_TYPE;


typedef packed enum
   {
   PROVIDED_SOURCE_TASK_ID = 9,
   PROVIDED_PSOS_TASK_ID = 10,
   PROVIDED_PSOS_QUEUE_ID = 11
   } PROVIDED_ID_KIND_TYPE;

 
typedef union
   {
   UINT32 	        psos_task_id;
   UINT32	        psos_queue_id;
   SOURCE_TASK_ID_TYPE	source_task_id;
   } SYSTEM_OBJECT_ID_KIND_TYPE;
 

typedef enum
   {
   ID_FOUND,
   ID_NOT_FOUND
   }SYSTEM_STATUS_TYPE;


typedef enum
   {
   UPDATE_TABLE_STATUS_OK,
   UPDATE_TABLE_STATUS_NOT_OK
   }UPDATE_TABLE_STATUS_TYPE;


typedef struct
   {
   UINT32 	        psos_task_id;
   UINT32	        psos_queue_id;
   } OBJECT_ID_TABLE_TYPE;

typedef enum
   {
   TASK_CREATE,
   QUEUE_CREATE,
   TASK_DELETE,
   QUEUE_DELETE
   }UPDATE_TABLE_ACTION_TYPE;

/*
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


SYSTEM_STATUS_TYPE DetermineSystemObjectId(
                                     RETURN_ID_KIND_TYPE	return_id,
		                     PROVIDED_ID_KIND_TYPE      provided_id,
			             SYSTEM_OBJECT_ID_KIND_TYPE	system_object_id,
			             SYSTEM_OBJECT_ID_KIND_TYPE	*requested_id);
				              

UPDATE_TABLE_STATUS_TYPE DetermineObjectIdTableUpdate(
                                     UPDATE_TABLE_ACTION_TYPE        action_type,
                                     SOURCE_TASK_ID_TYPE             source_task_id,
                                     UINT32                          psos_id);

#endif   /* DETERMINE_SYSTEM_OBJECT_ID_H */
