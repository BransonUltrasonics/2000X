/* $Header:   D:/SWLab/VMdb/2000Series/INC/RUN_TASK.H_V   2.18   May 12 2005 12:21:12   atali  $ */
#ifndef CREATE_AND_START_TASKS_H
#define CREATE_AND_START_TASKS_H
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

   Module name: Create_and_Start_Tasks

   Filename:    run_task.h


            Written by: Mark Lazarewicz  
                  Date: 1/12/96 
              Language:  "C"                           

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0             1/12/96      Mark L      Initial Version
       1.00          6/25/96      Lam         chged fpsc task,deleted
                                              createandstarttasks  
       1.02          09/10/96     PaulG       Added PMGR_PRIORITY
       1.03          10/29/96     PaulG       Added PMGR_Q_CNT
       1.04          11/22/96     PaulG       Increased PMGR_Q_CNT from 32 to 64
       1.05          12/04/96     PaulG       Increased priority from 80 to 99
       2.00          12/31/96     LAM         chged priority back to 80   
       2.10          05/05/97     PhilJ       Added Q_CNT1
       3.2.12        06/17/97     LAM         deleted unused defines
       2.13          02/19/98     BJB         Added priority for BIDL task
       2.14          08/26/98     BJB         Moved keypad task priority above
                                               printer
	   2.15          06/21/00     AS          Moved keypad prioity from 81 to 90 and
	                                           defined DUPS task at priority 85
       2.16          08/03/00     JLH         Swapped psos priorities of print manager and dups manager.
       2.16.1.0      03/20/03     SCM         Added priorities for QVGA task and Touch screen task.
       2.17          12-08-03     BEKymer     Moved 2.16.1.1 to tip as 2.17 for
                                               Ver9.00b build
       2.18          05-12-05     Aare        Added RVTS_PRIORITY define.
                                               
                                               
                                        
 ------------------------------- DESCRIPTION -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "root.h"                /* contains defines for startup              */
#include <psos.h>                /* defines T_STACK_SIZE_TYPE                 */
#include "names.h"               /* defines SOURCE_TASK_ID_TYPE               */

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 * Generic Queue size definition
 */
#define Q_CNT                    16   /* defines number of queue messages allowed   */
#define Q_CNT1                    8   /* defines number of queue messages allowed   */



/*****************************************************/

#define  HIGHEST_PRIORITY       255

#define  WMGR_PRIORITY          253   /* Welder Manager                */

#define  FATAL_ERROR_PRIORITY   251

#define  ROOT_PRIORITY          230   /* Welder_root                   */

#define  SYSM_PRIORITY          225   /* System Manager                */

#define  RVTS_PRIORITY          220   /* Remote VGA/touch screen       */

#define  QVGA_PRIORITY          200   /* QVGA Task Priority            */

#define  FPSC_PRIORITY          100   /* Front Panel State Coordinator */

#define  TSRN_PRIORITY          210   /* Touch Screen Task Priority    */

#define  FPKP_PRIORITY           90   /* Key pad                       */

#define  PMGR_PRIORITY           85   /* Printer Manager               */

#define  DUPS_PRIORITY           80   /* DUPS Manager                  */

#define  RSCH_PRIORITY           57   /* Remote Serial Command Handler */

#define  DIAG_PRIORITY           30   /* Diagnostics  Manager          */

#define  DPRM_PRIORITY           10   /* Dual Port Ram Manager         */

#define  WDTK_PRIORITY            3   /* Watch Dog                     */

#define  BIDL_PRIORITY            2   /* Branson Idle Task             */



/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef enum
   {
   CREATE_AND_START_TASK_PASS,
   CREATE_AND_START_TASK_FAIL
   } CREATE_AND_START_TASK_STATUS_TYPE;
   
/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

CREATE_AND_START_TASK_STATUS_TYPE CreateTaskWithQueue(
   SOURCE_TASK_ID_TYPE source_task_id,
   char                *task_name,
   UINT8               t_priority,
   T_STACK_SIZE_TYPE   ss_stack_size,
   char                *input_queue_name,
   UINT8               queue_size
   );

CREATE_AND_START_TASK_STATUS_TYPE StartTask(
   char                *task_name,
   void                task_start_addr()
   );

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* CREATE_AND_START_TASKS_H */


