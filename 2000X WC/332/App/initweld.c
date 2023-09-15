/* $Header:   D:/SWLab/VMdb/2000Series/App/INITWELD.C_V   2.12   Oct 22 2007 19:04:10   YGupta  $ */
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

   Module name: StartWelder

   Filename:  initweld.c

   Function name: StartWelder


            Written by: Mark Lazarewicz  
                  Date:  1/24/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author   Description
   ==========   ========   ======   ===========
      0         1/24/96    Mark L   Initial Version
      1         02/11/96   Mark L   Add DPRM,WMGR,WDPM
      2         05-15-96   BEKymer  Include proper files for function prototypes
                                    Comment out extern functions
                                    Comment out unused variable
      3         01-05-97   LAM      deleted portmanager
      4         02-10-97   LAM      deleted wdpm replaced with pmgr
      5         02-25-97   LAM      fixed enabling pmgr
      6.2.8     06-16-97   LAM      deleted starting of portmangr
      6.2.9     06-17-97   LAM      deleted starting of outbound task
      3.0       10-05-98   LAM      fixed run_task.h   
      2.11      04/30/99   LAM      deleted dual port task  
      2.12      10-22-07   NHAhmed  Changes done for LangTest phase 0


 ------------------------------- DESCRIPTION -----------------------------------

This function , called by ROOT starts the remote processors and tasks related
to the welder.

 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "portable.h"
#include "run_task.h"
#include "command.h"
#include "sysmangr.h"
#include "prnmangr.h"
#include "weldmngr.h"

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

CREATE_AND_START_TASK_STATUS_TYPE StartWelder(void)
   {
   SYS_STARTUP_STATUS_TYPE            SysStartupStatus;
   CREATE_AND_START_TASK_STATUS_TYPE  CreateAndStartTaskStatus = CREATE_AND_START_TASK_PASS;
      
      
   /* if task was started successfully, continue. */
   if (CreateAndStartTaskStatus == CREATE_AND_START_TASK_PASS)              
      {
      CreateAndStartTaskStatus = StartTask(SYSM_TASK,
                                       (void(*)) SystemManager);
      }
   else
      {
      CreateAndStartTaskStatus = CREATE_AND_START_TASK_FAIL;
      }
         
     /* if task was started successfully, continue. */
   if (CreateAndStartTaskStatus == CREATE_AND_START_TASK_PASS)              
      {
      CreateAndStartTaskStatus = StartTask(RSCH_TASK,
                                         (void(*)) RemoteSerialCommandHandler);
      }
     
   else
      {
      CreateAndStartTaskStatus = CREATE_AND_START_TASK_FAIL;
      }


   /* if task was started successfully, continue. */
   if (CreateAndStartTaskStatus == CREATE_AND_START_TASK_PASS)              
      {
      CreateAndStartTaskStatus = StartTask(WMGR_TASK,
                                    (void(*)) WeldManager);
      }
   else
      {
      CreateAndStartTaskStatus = CREATE_AND_START_TASK_FAIL;
      }               

   return( SysStartupStatus );

}  /* end of start_welder */
