/* $Header:   D:/SWLab/VMdb/2000Series/INC/qvga_task.h_v   1.9   Oct 22 2007 19:01:08   YGupta  $ */
#ifndef QVGA_TASK_H
#define QVGA_TASK_H
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

   Module name:   
   Filename:      qvga_task.h


            Written by: Shishir Madhugiri 
                  Date: 03/06/03 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========

   1.0             03/05/03      SCM         Initial Version.
   1.1             03/20/03      SCM         Added function prototypes for qvga_task.c.
   1.4             06/16/03      JOY         Front panel Key message is added to the 
                                             QVGA task queue.    
   1.5             08/04/03      JOY         Added 'QVGAMENUTASK_MSG' to the QVGA queue.
   1.6             06/25/04      JOY         Added function prototype 'QVGAStoreScrnImage()'. 
   1.7             07/25/05      Bwadia      RVTS message queue added
   1.8             07/28/05      Bwadia      Host command message added to RVTS queue
   1.9             10-22-07      NHAhmed     Changes done for LangTest phase 0

 ------------------------------- DESCRIPTION -----------------------------------
        
                                      
 ------------------------------ INCLUDE FILES ----------------------------------
*/  

#include "root.h"
#include "portable.h"
#include "genrlmsg.h"   
#include "touchmsg_qvga.h"
#include "weld_msg.h"
#include "kpresmsg.h"
#include "qvga_uart.h"
#include "ipscdmsg.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

// QVGA Menu Task message.
typedef struct {
   COMMON_MSG_FIELD_TYPE  common;
   UINT32  message;
   }QVGAMENUTASK_MSG;
   
//Message queue definition for QVGA Handler
typedef union
   {
     GENERIC_MSG               generic;
     WELD_DATA_MSG             WeldMsg;     
     FP_KEY_PRESSED_MSG        FPKeyMsg;
     TOUCH_HANDLER_MSG         Touchmsg;
     QVGAMENUTASK_MSG          MenuTaskMsg;
   }  QVGA_MSG_QUEUE_TYPE;

//Message queue definition for QVGA Handler
typedef union
   {
     GENERIC_MSG               generic;
     WELD_DATA_MSG             WeldMsg;     
     FP_KEY_PRESSED_MSG        FPKeyMsg;
     RVTS_MSG                  RvtsMsg;
     HOST_COMMAND_MSG          host_cmd;
     QVGAMENUTASK_MSG          MenuTaskMsg;
   }  RVTS_MSG_QUEUE_TYPE;

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           


/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void QvgaHandlerTask(void);
void InitQvgainterrupt(void);
void Buffer_Populate(BOOLEAN dest, SINT8 *Ptr);
void QVGAStoreScrnImage(void);


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif  
