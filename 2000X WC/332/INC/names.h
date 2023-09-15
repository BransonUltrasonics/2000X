/* $Header:   D:/SWLab/VMdb/2000Series/INC/NAMES.H_V   2.11   May 12 2005 12:24:32   atali  $ */
#ifndef PSOS_NAMES_H
#define PSOS_NAMES_H
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
                                                  
  Module name: psos_names.h

  Filename:  names.h


           Written by: Mark Lazarewicz 
                 Date: 1/21/96 
             Language:  68000 Microtec "C" Compiler

--------------------------------- REVISIONS -----------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            01/21/96      Mark L      Initial Version
      1            02/02/96      Mark L      Added READ_LOG_PARTITION
      2            02/09/96      Mark L      Added RSDM
      3            03/06/96      Mark L      Added Ascii Diagnostics partitions
      4a           06/12/96      LAM         Added WC ISR TASK ID              
      4b           08/05/96      Mark L      Added WELD_DATA_PARTITION
      5            09/04/96      PMG         Added PMGR_SOURCE_TASK to enum
      6            04/01/97      LAM         deleted unused variables          
      7.2.12       06/17/97      LAM         deleted unused defines
      2.7		   04/20/99		 OFI		 Changed for DIAB
	  2.8          05/10/99      LAM         added packed for DIAB
	  2.9          06/21/00      AS          Added DUPS Task ID
      2.9.1.0      03/20/03      SCM         Added task/queue definitions for QVGA task
                                             and touch screen tasks; Also added semaphore 
                                             definitions for both QVGA and touch screen
                                             handlers.
      2.10         12-08-03      BEKymer     Move 2.9.1.0 to tip as 2.10 for
                                              Ver9.00b build
      2.11         05-12-05      Aare        Added RVTS task and queue names and enum definition.
                 
                                             
                                             
--------------------------------- DESCRIPTION -----------------------------------

   This file defines PSOS+ task names, region names, partition names, queue names,
   and semaphore names.

--------------------------------- INCLUDE FILES ---------------------------------

   NONE

---------------------------------- DEFINITIONS ----------------------------------
*/

/*
 *  region zero name
 */

#define ROOT_REGION_ZERO_NAME           "RN#0"
              

/*
*==============================================================================
*==============================================================================
*
* The following convention has been adopted for psos object names :
* 
**
*==============================================================================
*==============================================================================
*/


/*===========================================================================*/
/* QUEUE DEFINITIONS                                                         */
/*===========================================================================*/

#define DIAG_Q                   "DIAG"   /* Diagnostics Manager  queue                */
                                                                                         
#define FPKP_Q                   "FPKP"   /* Front Panel Key Pad queue                 */

#define FPSC_Q                   "FPSC"   /* Front Panel State Coordinator queue       */

#define RSCH_Q                   "RSCH"   /* Remote Serial Command Handler             */

#define ROOT_Q                   "ROOT"   /* The ROOT task input queue                 */

#define SYSM_Q                   "SYSM"   /* System Manager Task                       */

#define WDTK_Q                   "WDTK"   /* welder WatchDog TicK queue                */

#define WMGR_Q                   "WMGR"   /* Welder Manager queue                      */

#define PMGR_Q                   "PMGR"   /* Printer Manager queue                     */ 

#define DUPS_Q                   "DUPS"   /* DUPS manager queue                        */

#define QVGA_Q                   "QVGA"   /* QVGA input queue                          */

#define TSRN_Q                   "TSRN"   /* Touch Screen queue                        */

#define RVTS_Q                   "RVTS"   /* Remote VGA/touchscreen queue              */

/*===========================================================================*/
/* TASK DEFINITIONS                                                          */
/*===========================================================================*/

#define DIAG_TASK                "diag"   /* Diagnostics Manager                       */

#define FPKP_TASK                "fpkp"   /* Front Panel State Manager task            */

#define FPSC_TASK                "fpsc"   /* Front Panel State Coordinator task        */

#define ROOT_TASK                "root"   /* The ROOT task                             */

#define RSCH_TASK                "rsch"   /* Remote Serial Command Handler             */

#define SYSM_TASK                "sysm"   /* SYStem Manager task                       */             

#define WDTK_TASK                "wdtk"   /* WatchDog TicK task                        */

#define WMGR_TASK                "wmgr"   /* Weld ManaGeR  task                        */

#define PMGR_TASK                "pmgr"   /* Printer Manager task                      */

#define DUPS_TASK                "dups"   /* DUPS Manager task                         */

#define QVGA_TASK                "qvga"   /* QVGA task                                 */

#define TSRN_TASK                "tsrn"   /* Touch Screen task                         */

#define RVTS_TASK                "rvts"   /* Remote VGA/touchscreen tack               */

/*===========================================================================*/
/* SOURCE TASK DEFINITIONS                                                   */
/*===========================================================================*/
/* for all task names added above, add to this enumeration */
/*NOTE:  ALL NEW TASKS AND QUEUES NEED TO BE ADDED TO THIS LIST AND TO THE */
/*       TASK_QUEUE_NAME_TABLE IN DETERMINE_SYSTEM_OBJECT_ID.C IN THE SAME ORDER */

typedef __packed__ enum
        {
        DIAG_SOURCE_TASK = 0u,
        FPKP_SOURCE_TASK,   
        FPSC_SOURCE_TASK,
        QVGA_SOURCE_TASK,
        ROOT_SOURCE_TASK,
        RSCH_SOURCE_TASK,
        SYSM_SOURCE_TASK,
        TSRN_SOURCE_TASK, 
        WDTK_SOURCE_TASK,
        WMGR_SOURCE_TASK,
        PMGR_SOURCE_TASK,
		DUPS_SOURCE_TASK,
        WC_ISR_TASK,
        RVTS_SOURCE_TASK,
        MAX_NUMBER_OF_TASKS,
        SOURCE_TASK_SIZER = 255
        } SOURCE_TASK_ID_TYPE;

/*===========================================================================*/
/* SEMAPHORE  DEFINITIONS                                                    */
/*===========================================================================*/

#define QVGA_SM                "qvsm"  /*  QVGA Transmit semaphore            */
#define TSRN_SM                "tssm"  /*  Touch Screen Transmit semaphore    */

/*===========================================================================*/
/* PARTITION  DEFINITIONS                                                    */
/*===========================================================================*/

#define MAD_PARTITION                "MAD "     /* used for  messages */

#define READ_LOG_PARTITION           "RLOG"     /* used for reading sware log */

#define SOFTWARE_DOWNLOAD_PARTITION  "RSDM"     /* used by Remote Software Download      */


/*===========================================================================*/
/* EVENT DEFINITIONS                                                         */
/*===========================================================================*/

                    
/*--------------------------- TYPE DECLARATIONS -----------------------------*/
                                                                               
/* none */

/*------------------------ FUNCTION PROTOTYPES ------------------------------*/
          
/* none */

#endif /* PSOS_NAMES_H */





