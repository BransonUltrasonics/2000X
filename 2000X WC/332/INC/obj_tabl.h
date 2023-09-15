/* $Header:   K:\APPS\PVCS Pro\332new\INC\OBJ_TABL.H_V   2.5   Aug 13 1999 09:36:04   jzimny  $ */
#ifndef OBJECT_H
#define OBJECT_H
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

/* ----------------------- MODULE DESCRIPTION -------------------------------

   Module name:  Determine_System_Object_Id

   Filename:     obj_tabl.h


            Written by: Mark lazarewicz 
                  Date: 1/17/96 
              Language:  "C"

 ---------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author   Description
   ==========   ========   ======   ===========
      0         01/17/96   Mark L   Initial Version
      1         05-16-96   BEKymer  Add proper function prototyping
      2         07-01-96   LAM      deleted unused prototyping
      3.2.3     07-07-97   LAM      added psos_tabl.h           
	  2.4		04-20-99   OFI		Changed for DIAB
	  2.5       08-13-99   JZ       Removed DetermineSystemObjectId proto

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

typedef enum
   {
   RETURN_SOURCE_TASK_ID = 6,
   RETURN_PSOS_TASK_ID = 7,
   RETURN_PSOS_QUEUE_ID = 8
   } RETURN_ID_KIND_TYPE;


typedef enum
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

#endif   /* DETERMINE_SYSTEM_OBJECT_ID_H */

/*--------------------------- Function Prototypes --------------------------*/

UPDATE_TABLE_STATUS_TYPE DetermineObjectIdTableUpdate(
   UPDATE_TABLE_ACTION_TYPE        ActionType,
   SOURCE_TASK_ID_TYPE             SourceTaskId,
   UINT32                          PsosId);
