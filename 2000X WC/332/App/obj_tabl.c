/* $Header:   K:\APPS\PVCS Pro\332new\App\OBJ_TABL.C_V   2.6   Aug 13 1999 09:37:50   jzimny  $ */
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

   Filename:     obj_tabl.c


            Written by: Mark lazarewicz 
                  Date: 1/17/96 
              Language:  "C"

 ----------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author   Description
   ==========   ========   ======   ===========
      0         01/17/96   Mark L   Initial Version
      1         05-16-96   BEKymer  Add proper function prototyping
      2         07/01/96   Lam      deleted determinesystemobjectinit
      3.2.4     07-07-97   LAM      deleted psos_tbl.h                     
      2.5       09-11-97   PaulG    Unit test and data cleanup.
      2.6       08-13-99   JZ       Removed function DetermineSystemObjectId                     


---------------------------- DESCRIPTION -----------------------------------

   This library routine gets called whenever any application needs to access the
   SYSTEM_OBJECT_ID_TYPE.  The SYSTEM_OBJECT_ID_TYPE may be the psos_queue_id, the psos_task_id,
   or the source_task_type.

----------------------------- PSEUDO CODE -----------------------------------

---------------------------- LOCAL EQUATES ----------------------------------

----------------------------- EXPORT DATA -----------------------------------

----------------------------- IMPORT DATA -----------------------------------
   
---------------------------- INCLUDE FILES ----------------------------------
*/
                                                                    
#include <psos.h>                  /* psos defines and prototypes, etc..     */
#include "names.h"                 /* psos object defines                    */
#include "obj_tabl.h"

/*
---------------------------- EXTERNAL DATA ----------------------------------

---------------------------- LOCAL DEFINES ----------------------------------
*/
 
#define FIRST_ENTRY_IN_TABLE    0
#define INIT_TASK_VALUE         0       /* initial value for tasks */
#define INIT_QUEUE_VALUE        0       /* initial value for queues */

/*
------------------------- LOCAL TYPE DECLARATIONS ---------------------------

-------------------------- PRIVATE GLOBAL DATA ------------------------------
*/

/* Create the System Object ID Table with initial values. */
static OBJECT_ID_TABLE_TYPE    system_object_id_table[MAX_NUMBER_OF_TASKS]; 

/*
----------------------------- LOCAL DATA ------------------------------------

-------------------- IMPORT SUBROUTINES REFERENCED --------------------------
                              
-------------------------------- CODE ---------------------------------------
*/
 

/* ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  Determine_System_Object_Id_Table

   Filename:         obj_tabl.c

   Function name:    DetermineObjectIdTableUpdate


            Written by: Mark Lazarewicz 
                  Date: 01/18/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
       0           01/18/96      Mark L      Initial Version

 ------------------------------- DESCRIPTION -----------------------------------


 ------------------------------- PSEUDO CODE -----------------------------------
                                                                          
   This function is called by the following library functions: t_create.c , 
   t_delete.c, q_create.c and q_delete.c. It is called whenever a task or a queue 
   is created or deleted.  This function updates the system_object_id_table with 
   the appropriate psos task and psos queue ids.

 ---------------------------------- CODE ---------------------------------------
*/  

UPDATE_TABLE_STATUS_TYPE DetermineObjectIdTableUpdate(
   UPDATE_TABLE_ACTION_TYPE        ActionType,
   SOURCE_TASK_ID_TYPE             SourceTaskId,
   UINT32                          PsosId)
   {

   UPDATE_TABLE_STATUS_TYPE UpdateTableStatus=UPDATE_TABLE_STATUS_OK;
   /*Initialize return status */

   if (SourceTaskId < MAX_NUMBER_OF_TASKS) 
      {

      switch (ActionType)
        {
        case TASK_CREATE:
           system_object_id_table[SourceTaskId].psos_task_id = PsosId;
           break;

        case QUEUE_CREATE:
           system_object_id_table[SourceTaskId].psos_queue_id = PsosId;
           break;

        case TASK_DELETE:
           system_object_id_table[SourceTaskId].psos_task_id = INIT_TASK_VALUE;
           break;

        case QUEUE_DELETE:
           system_object_id_table[SourceTaskId].psos_queue_id = INIT_TASK_VALUE;
           break;

        default:  
           UpdateTableStatus =  UPDATE_TABLE_STATUS_NOT_OK;

           /* Log any software errors */

           break;


     }  /* End of Switch */
   
   }
   else
      {
      UpdateTableStatus =  UPDATE_TABLE_STATUS_NOT_OK;

      /* Log any software errors */
      }

   return(UpdateTableStatus);
   }  


/* FOR UNIT TEST ONLY */
#ifdef INCLUDE_UNIT_TEST
#include "obj_tabl.ut"  
#endif
/* FOR UNIT TEST ONLY */


