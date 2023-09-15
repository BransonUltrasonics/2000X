/* $Header:   D:/SWLab/VMdb/2000Series/App/MIN_MODE.C_V   2.11   Oct 22 2007 19:05:14   YGupta  $ */
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

   Module name: Start_Minimal_Task_Set

   Filename:  min_mode.c

   Function name: StartMinimalTaskset


            Written by: Mark Lazarewicz 
                  Date: 1/19/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            01/19/96      Mark L      Initial Version
      1            03/19/96      Mark L      A test after every task start
      12           03/30/97      LAM         welddata test
      2.4          06/17/97      PhilJ       Deleted CreateandStart NVMM_TASK
      2.5          06/17/97      PhilJ       Deleted include file nvmanger.h
      2.6          07/30/98      BJB         Makes sure return value is set in
                                              StartMinimalTaskSet().
      2.7          12/16/99      LAM         deleted unused error handling code
	  2.8          06/21/00      AS          Added DUPS task
      2.8.1.0      03/20/03      SCM         Start new tasks QVGA Handler and Touch 
                                             Screen handler tasks.
      2.9          12-04-03      BEKymer     Moved 2.8.1.0 to tip for Ver9.00b
                                              build
      2.10         05-12-05      Aare        Start RVTS task, don't start QVGA and TSRN.
      2.11         10-22-07      NHAhmed     Changes done for LangTest phase 0


 ------------------------------- DESCRIPTION -----------------------------------

 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include <psos.h>        /* pSOS+ operating system information        */
#include "names.h"       /* contains pSOS object names                */


#include "min_mode.h"
#include "run_task.h"    /* define start_task function interface */

/* include all task function prototypes */
#include "fpsmangr.h"
#include "fpk_task.h"
#include "dups.h"
#include "qvga_task.h"



/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

void RvtsHandlerTask(void);

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

SYS_STARTUP_STATUS_TYPE StartMinimalTaskSet(
   void
   )
   {
   SYS_STARTUP_STATUS_TYPE           SysStartupStatus = SYS_STARTUP_PASS;

   CREATE_AND_START_TASK_STATUS_TYPE CreateAndStartTaskStatus; 

                                                    
   CreateAndStartTaskStatus = StartTask(FPKP_TASK,FrontPanelKeypadTask);

   if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
      {
      SysStartupStatus = SYS_STARTUP_FAIL;
      }
      
   if (CreateAndStartTaskStatus == CREATE_AND_START_TASK_PASS)
      {                                                          
      CreateAndStartTaskStatus = StartTask(FPSC_TASK,FrontPanelStateCoordinator);
      }
   if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
      {
      SysStartupStatus = SYS_STARTUP_FAIL;
      }

   if (CreateAndStartTaskStatus == CREATE_AND_START_TASK_PASS)
      {                                                          
      CreateAndStartTaskStatus = StartTask(DUPS_TASK,DUPS_Manager);
      }
   if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
      {
      SysStartupStatus = SYS_STARTUP_FAIL;
      }
   /***** Start QVGA Handler Task *****/
   if (CreateAndStartTaskStatus == CREATE_AND_START_TASK_PASS)
      {                                                          
      CreateAndStartTaskStatus = StartTask (RVTS_TASK, RvtsHandlerTask);
      }
   if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
      {
      SysStartupStatus = SYS_STARTUP_FAIL;       
      }
#if 0
   /***** Start QVGA Handler Task *****/
   if (CreateAndStartTaskStatus == CREATE_AND_START_TASK_PASS)
      {                                                          
      CreateAndStartTaskStatus = StartTask (QVGA_TASK, QvgaHandlerTask);
      }
   if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
      {
      SysStartupStatus = SYS_STARTUP_FAIL;       
      }


#endif
     return( SysStartupStatus );
   }  /* end of start_application_tasks */








