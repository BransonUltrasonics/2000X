/* $Header:   L:/pvcs/1000/psos332/archives/app/run_task.c_v   2.4   08 Jul 1997 09:47:18   lmarkure  $ */
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

   Module name: Create_and_Start_Tasks

   Filename:  run_task.c

   Function name: CreateTaskWithQueue


            Written by: Mark Lazarewicz 
                  Date: 1/18/96  
              Language: MRI "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            01/18/96      Mark L      Initial Version
      1            06/12/96      Lam         deleted create and start task.
      2.2.4        07-07-97      LAM         deleted psos_tbl.h                     

 ------------------------------- DESCRIPTION -----------------------------------

 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include <psos.h>       /* pSOS+ operating system information        */
#include "names.h"      /* contains pSOS object names                */
#include "root.h"       /* contains task level defines               */
#include "run_task.h"   /* contains function prototype               */
#include "obj_tabl.h"   /* contains function prototype               */

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/

/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/

/*
 ------------------------------- GLOBAL DATA -----------------------------------
                        (scope is global to ALL files)
*/
       

/*
 ---------------------------- PRIVATE GLOBAL DATA ------------------------------
                        (scope is global to THIS file)
*/
                              
/*
 ---------------------------------- CODE ---------------------------------------
*/

CREATE_AND_START_TASK_STATUS_TYPE CreateTaskWithQueue(
   SOURCE_TASK_ID_TYPE SourceTaskId,
   char                *TaskName,
   UINT8               TPriority,
   T_STACK_SIZE_TYPE   SsStackSize,
   char                *InputQueueName,
   UINT8               QueueSize
   )
   {
   CREATE_AND_START_TASK_STATUS_TYPE CreateAndStartTaskStatus;  
   UINT32                            PsosStatus;
   UINT32                            PsosQid;
   UINT32                            PsosTid;
   UPDATE_TABLE_STATUS_TYPE          UpdateTableStatus;

   /* initialize local status to PASS */

   CreateAndStartTaskStatus = CREATE_AND_START_TASK_PASS;

   /* create task */
   PsosStatus = t_create(TaskName,
                          TPriority,
                          SsStackSize, 
                          T_SIZE_0,
                          T_LOCAL,
                          &PsosTid
                          );

   /* all errors are fatal */
   if (PsosStatus != PSOS_OK)
      CreateAndStartTaskStatus = CREATE_AND_START_TASK_FAIL;
      
   else
      {
      UpdateTableStatus = DetermineObjectIdTableUpdate(TASK_CREATE,
                                                             SourceTaskId,PsosTid);
      if (UpdateTableStatus != UPDATE_TABLE_STATUS_OK)
         CreateAndStartTaskStatus = CREATE_AND_START_TASK_FAIL;
      }

   if (CreateAndStartTaskStatus == CREATE_AND_START_TASK_PASS)

      {
      /* check if queue already exists */
      PsosStatus = q_ident(InputQueueName, Q_NODE_0, &PsosQid);
      
      /* queue does not exist, so create the queue */
      if (PsosStatus == ERR_OBJNF) 
         {
         PsosStatus = q_create(InputQueueName, 
                                QueueSize, 
                                Q_LOCAL+Q_FIFO+Q_LIMIT+Q_PRIBUF,
                                &PsosQid);

         /* all errors are fatal */
         if (PsosStatus != PSOS_OK)
            CreateAndStartTaskStatus = CREATE_AND_START_TASK_FAIL;

         else
            {
            UpdateTableStatus = DetermineObjectIdTableUpdate(QUEUE_CREATE,
                                                                   SourceTaskId,
                                                                   PsosQid);
            if (UpdateTableStatus != UPDATE_TABLE_STATUS_OK)
               CreateAndStartTaskStatus = CREATE_AND_START_TASK_FAIL;
            }
         }
      /* all other error conditions are fatal */
      else if (PsosStatus != PSOS_OK)
         CreateAndStartTaskStatus = CREATE_AND_START_TASK_FAIL;

      }

   return CreateAndStartTaskStatus;  
   }  /* end of create_task_with_queue */

/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name: Create_and_Start_Tasks

   Filename:  create_and_start_tasks.c

   Function name: start_task

            Written by: 
                  Date:  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========

 ------------------------------- DESCRIPTION -----------------------------------

                                          

 ------------------------------- PSEUDO CODE -----------------------------------

 ---------------------------------- CODE ---------------------------------------
*/

CREATE_AND_START_TASK_STATUS_TYPE StartTask(
   char                *TaskName,
   void                TaskStartAddr() 
   )
   {
   CREATE_AND_START_TASK_STATUS_TYPE CreateAndStartTaskStatus;  
   UINT32                            PsosStatus;
   UINT32                            PsosTid;

   /* initialize local status */
   CreateAndStartTaskStatus = CREATE_AND_START_TASK_PASS;

   /* get the pSOS id for the task to start */
   PsosStatus = t_ident(TaskName, T_NODE_0, &PsosTid); 

   /* all errors are fatal */
   if (PsosStatus != PSOS_OK)
      CreateAndStartTaskStatus = CREATE_AND_START_TASK_FAIL;

   if (CreateAndStartTaskStatus == CREATE_AND_START_TASK_PASS)
      {
      /* start the created task */
      PsosStatus = t_start(PsosTid, 
                            T_PREEMPT+T_NOTSLICE+T_NOASR+T_SUPV, 
                            TaskStartAddr,
                            NULL_PTR
                            ); 

      /* all errors are fatal */
      if (PsosStatus != PSOS_OK)
         CreateAndStartTaskStatus = CREATE_AND_START_TASK_FAIL;
      }

   return CreateAndStartTaskStatus;  
   }  /* end of start_task */ 

