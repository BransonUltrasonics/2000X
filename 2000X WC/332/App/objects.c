/* $Header:   D:/SWLab/VMdb/2000Series/App/OBJECTS.C_V   2.38   Oct 22 2007 19:05:16   YGupta  $ */
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
 ---------------------------- MODULE DESCRIPTION -----------------------------

   Module name:   Objects

   Filename:      objects.c

   Function name: CreatePsosObjects


            Written by: Mark Lazarewicz 
                  Date: 1/3/96 
              Language:  "C"

 -------------------------------- REVISIONS ----------------------------------

   Revision #   Date       Author      Description
   ==========   ========   ======      ===========
      0         1/3/96     Mark L      Initial Version
      1         1/31/96    Mark L      Added DIAG task
      2         2/02/96    Mark L      Create READ_LOG
      3         2/10/96    Mark L      Add WDPM,WMGR,DPRM tasks
      4         2/26/96    Mark L      Add FPCH,FPPM  task
      5         3/06/96    Mark L      Add COMR task
      6         3/08/96    Mark L      ADIM,ADSC partitions added
      7         3/19/96    Mark L      ADIM,ADSC tasks added
      8         3/28/96    Mark L      Increase FPSC stack
      9         05-03-96   BEKymer     Increase FPSC_SOURCE_TASK stack
     10         05-15-96   BEKymer     Eliminate PsosStatus, SmId, PsosQid
     11         6/25/96    LAM         Increase sysm&nvmm stack
     12         09/10/96   PaulG       Created task with queue (PMGR_SOURCE_TASK).
     13         10/29/96   PaulG       Increased queue size from Q_CNT to PMGR_Q_CNT
                                       (16 messages capacity to 32).
     13         12/20/96   PaulG       Increased queue size PMGR_Q_CNT to 64.
     14         02/10/97   LAM         dleted wdpm task,made printqueue = 32                      
     15         04/18/97   PhilJ       Deleted ADSC_TASK and FPDM_TASK.
     16         04/21/97   LAM         deleted unused partitions
     17         04/28/97   LAM         cleanup      
     18         05/05/97   PhilJ       Chngd Q_CNT in FPSC & FPKP tasks to 8.
     19         05/08/97   LAM         Chngd Q_CNT in FPKP task to 4.
     2.21       06/10/97   LAM         deleted portmngr task
     2.22       06/17/97   PhilJ       deleted nvmm_task
     2.23       06/17/97   LAM         deleted echo_qid,adim queue,rsdm,comr
     3.2.24     07-07-97   LAM         deleted psos_tbl.h
     2.25       12-29-97   BJB         Increased size of fpsc_queue to 16.
     2.26       02-19-98   BJB         Added BIDL_Task() and code to start it.
     2.27       05/05/99   LAM         deleted DPRAM task
     2.28       06/21/00   AS          Added DUPS task
     2.29       09/08/00   LAM         removed tabs
     2.29.1.0   03/20/03   SCM         Created new tasks QVGA task and 
                                       Touch screen task.
     2.29.1.2   07/11/03   JOY         Increased QVGA task stack to 4k size.
     2.30       12-04-03   BEKymer     Moved 2.29.1.2 to tip as 2.30
                                        for Ver9.00b build
     2.31       12-27-03   VSharma     Increased RSCH task stack to 2k size.
     2.32       04-16-05   Aare        Commented out QVGA and TSRN task creation.
     2.33       05-12-05   Aare        Create RVTS task and also QVGA and TSRN,
                                       but with smaller stacks. This is safe
                                       because QVGA and RVTS tasks are not
                                       actually started.
     2.34       05-13-05   Aare        Commented QVGA and TSRN out again,
                                       increased RVTS stack size.
     2.35       05-17-05   Aare        Increased RSCH task stack to 8K.
     2.36       07-25-05   Bwadia      Reduced RVTS and remote serial handler
                                       task size to 4K instead of 8K
     2.37       09-10-05   Bwadia      RVTS stack size changed to 8K  
     2.38       10-22-07   NHAhmed     Changes done for LangTest phase 0
     
     
*****************************************************************************/ 

   
   
/*
 ------------------------------ EXTERNAL DATA --------------------------------
*/

/*
 ------------------------------ LOCAL DEFINES --------------------------------
*/

#include "run_task.h"
#include <psos.h>
#include "obj_tabl.h"
#include "objects.h"
#include "names.h"

/*
 --------------------------- LOCAL TYPE DECLARATIONS -------------------------
*/

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/

static void BIDL_Task(void);      

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/
       
/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/
                              
/*
 ---------------------------------- CODE -------------------------------------
*/

SYS_STARTUP_STATUS_TYPE CreatePsosObjects(
   void
   )
   {
   SYS_STARTUP_STATUS_TYPE           SysStartupStatus = SYS_STARTUP_PASS;
   CREATE_AND_START_TASK_STATUS_TYPE CreateAndStartTaskStatus;  

   UINT32                  PsosStatus;
   UINT32                  PsosRegionId;
   UINT32                  PsosPtId;
   UINT32                  NumberOfBuffers;
   UINT32                  BIDL_Id;
   void                    *SegAddr;   /* Miscellaneous temporary pointer */

 

  /* Identify REGION 0 */
   PsosStatus = rn_ident(ROOT_REGION_ZERO_NAME, &PsosRegionId);

   if (PsosStatus != PSOS_NOERROR)
      SysStartupStatus = SYS_STARTUP_FAIL;


   /* <<<<<<<<<<<< MAD PARTITION >>>>>>>>>>>>> */

   if (SysStartupStatus == SYS_STARTUP_PASS)
      {
      /* Get some memory from REGION 0 */
      PsosStatus = rn_getseg(PsosRegionId, 
                              MAD_ALLOC_SIZE,
                              RN_NOWAIT,
                              RN_WAIT_FOREVER,
                              &SegAddr);

      if (PsosStatus != PSOS_NOERROR)
         SysStartupStatus = SYS_STARTUP_FAIL;

      else
         PsosStatus = pt_create(MAD_PARTITION, 
                                 SegAddr, 
                                 SegAddr,
                                 MAD_ALLOC_SIZE, 
                                 MAD_BUFFER_SIZE,
                                 PT_LOCAL+PT_NODEL, 
                                 &PsosPtId, 
                                 &NumberOfBuffers);
         
      if (PsosStatus != PSOS_NOERROR)
         SysStartupStatus = SYS_STARTUP_FAIL;
      }


      /* Get some memory from REGION 0 */
      PsosStatus = rn_getseg(PsosRegionId, 
                              READ_LOG_ALLOC_SIZE,
                              RN_NOWAIT,
                              RN_WAIT_FOREVER,
                              &SegAddr);

      if (PsosStatus != PSOS_NOERROR)
         SysStartupStatus = SYS_STARTUP_FAIL;

      else{
         PsosStatus = pt_create(READ_LOG_PARTITION, 
                                 SegAddr, 
                                 SegAddr,
                                 READ_LOG_ALLOC_SIZE,
                                 READ_LOG_BUFFER_SIZE,
                                 PT_LOCAL+PT_NODEL, 
                                 &PsosPtId, 
                                 &NumberOfBuffers);
      }
      if (PsosStatus != PSOS_NOERROR){
         SysStartupStatus = SYS_STARTUP_FAIL;
      }

     if (SysStartupStatus == SYS_STARTUP_PASS)
      {
      /* Get some memory from REGION 0 */
      PsosStatus = rn_getseg(PsosRegionId, 
                              SOFTWARE_DOWNLOAD_ALLOC_SIZE,
                              RN_NOWAIT,
                              RN_WAIT_FOREVER,
                              &SegAddr);

      if (PsosStatus != PSOS_NOERROR)
         SysStartupStatus = SYS_STARTUP_FAIL;

      else
         {
         PsosStatus = pt_create(SOFTWARE_DOWNLOAD_PARTITION, 
                                 SegAddr, 
                                 SegAddr,
                                 SOFTWARE_DOWNLOAD_ALLOC_SIZE, 
                                 SOFTWARE_DOWNLOAD_BUFFER_SIZE,
                                 PT_LOCAL+PT_NODEL, 
                                 &PsosPtId, 
                                 &NumberOfBuffers);
         
         if (PsosStatus != PSOS_NOERROR)
            SysStartupStatus = SYS_STARTUP_FAIL;
         }
      }


   if (SysStartupStatus == SYS_STARTUP_PASS) 
      {
      /* create the DIAG task and it's queue */
      CreateAndStartTaskStatus = CreateTaskWithQueue(DIAG_SOURCE_TASK,
                                                            DIAG_TASK,
                                                            DIAG_PRIORITY,
                                                            T_SIZE_512,
                                                            DIAG_Q,
                                                            Q_CNT
                                                            );
     /* check if queue was created successfully */
      if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
         SysStartupStatus = SYS_STARTUP_FAIL;
      }
                                                            

                                                            
   if (SysStartupStatus == SYS_STARTUP_PASS) 
      {
      /* create the FPKP task and it's queue */
      CreateAndStartTaskStatus = CreateTaskWithQueue(FPKP_SOURCE_TASK,
                                                            FPKP_TASK,
                                                            FPKP_PRIORITY,
                                                            T_SIZE_512,
                                                            FPKP_Q,
                                                            4
                                                            );   

      /* check if queue was created successfully */
      if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
         SysStartupStatus = SYS_STARTUP_FAIL;
      }

 
   if (SysStartupStatus == SYS_STARTUP_PASS) 
      {
      /* create the FPSC task and it's queue */
      CreateAndStartTaskStatus = CreateTaskWithQueue(FPSC_SOURCE_TASK,
                                                            FPSC_TASK,
                                                            FPSC_PRIORITY,
                                                            T_SIZE_16384,
                                                            FPSC_Q,
                                                            Q_CNT
                                                            );


      /* check if queue was created successfully */
      if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
         SysStartupStatus = SYS_STARTUP_FAIL;
      }


   if (SysStartupStatus == SYS_STARTUP_PASS) 
      {
      /* create the remote serial command handler task and it's queue */
      CreateAndStartTaskStatus = CreateTaskWithQueue(RSCH_SOURCE_TASK,
                                                            RSCH_TASK,
                                                            RSCH_PRIORITY,
                                                            T_SIZE_4096,
                                                            RSCH_Q,
                                                            Q_CNT
                                                            );

      /* check if queue was created successfully */
      if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
         SysStartupStatus = SYS_STARTUP_FAIL;
      }


   if (SysStartupStatus == SYS_STARTUP_PASS) 
      {
      /* create the SYSM task and it's queue */
      CreateAndStartTaskStatus = CreateTaskWithQueue(SYSM_SOURCE_TASK,
                                                            SYSM_TASK,
                                                            SYSM_PRIORITY,
                                                            T_SIZE_2048,
                                                            SYSM_Q,
                                                            Q_CNT
                                                            );   

      /* check if queue was created successfully */
      if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
         SysStartupStatus = SYS_STARTUP_FAIL;
      }


   if (SysStartupStatus == SYS_STARTUP_PASS)
      {
      CreateAndStartTaskStatus = CreateTaskWithQueue(WDTK_SOURCE_TASK,
                                                            WDTK_TASK,
                                                            WDTK_PRIORITY, 
                                                            T_SIZE_512,
                                                            WDTK_Q,
                                                            Q_CNT
                                                            );
      /* check if queue was created successfully */
      if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
         SysStartupStatus = SYS_STARTUP_FAIL;
      }



   if (SysStartupStatus == SYS_STARTUP_PASS)
      {
      CreateAndStartTaskStatus = CreateTaskWithQueue(WMGR_SOURCE_TASK,
                                                            WMGR_TASK,
                                                            WMGR_PRIORITY, 
                                                            T_SIZE_4096,
                                                            WMGR_Q,
                                                            Q_CNT
                                                            );
      /* check if queue was created successfully */
      if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
         SysStartupStatus = SYS_STARTUP_FAIL;
      }


   if (SysStartupStatus == SYS_STARTUP_PASS)
   {
      CreateAndStartTaskStatus = CreateTaskWithQueue(DUPS_SOURCE_TASK,
                                                     DUPS_TASK,
                                                     DUPS_PRIORITY, 
                                                     T_SIZE_1024,
                                                     DUPS_Q,
                                                     Q_CNT );

      /* check if queue was created successfully */
      if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
         SysStartupStatus = SYS_STARTUP_FAIL;
   }

   /******Create the QVGA Task *****/
   if (SysStartupStatus == SYS_STARTUP_PASS)
   {
      CreateAndStartTaskStatus = CreateTaskWithQueue (RVTS_SOURCE_TASK,                                                             
                                                      RVTS_TASK,
                                                      RVTS_PRIORITY,
                                                      T_SIZE_8192,
                                                      RVTS_Q,
                                                      Q_CNT);
                                                      
        /* check if queue was created successfully */
        if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
         SysStartupStatus = SYS_STARTUP_FAIL;                                         
   }
#if 0
   /******Create the QVGA Task *****/
   if (SysStartupStatus == SYS_STARTUP_PASS)
   {
      CreateAndStartTaskStatus = CreateTaskWithQueue (QVGA_SOURCE_TASK,                                                             
                                                      QVGA_TASK,
                                                      QVGA_PRIORITY,
                                                      T_SIZE_128, //T_SIZE_4096,
                                                      QVGA_Q,
                                                      Q_CNT);
                                                      
        /* check if queue was created successfully */
        if (CreateAndStartTaskStatus != CREATE_AND_START_TASK_PASS)
         SysStartupStatus = SYS_STARTUP_FAIL;                                         
   }
#endif
   if (SysStartupStatus == SYS_STARTUP_PASS)
   {
      if (!t_create( "BIDL", BIDL_PRIORITY, T_SIZE_128, T_SIZE_0,
       T_LOCAL, &BIDL_Id ))   /* If task created OK */
      {
         if (t_start( BIDL_Id, T_PREEMPT+T_NOTSLICE+T_NOASR+T_SUPV,
          BIDL_Task,  NULL_PTR ))   /* If task not started OK */
            SysStartupStatus = SYS_STARTUP_FAIL;
      }
      else
         SysStartupStatus = SYS_STARTUP_FAIL;
   }

   return SysStartupStatus;
}  /* end of create_psos_objects */

static void BIDL_Task(void)
{
   while(TRUE);   /* This task just sits in a loop until a higher priority */
                  /* task needs to run.  This keeps pSOS IDLE task from */
                  /* running, which interferes with background debug. */
}
