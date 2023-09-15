/* $Header:   L:/pvcs/1000/psos332/archives/inc/objects.h_v   2.6   28 Apr 1997 08:22:58   lmarkure  $ */
#ifndef CREATE_PSOS_OBJECTS_H
#define CREATE_PSOS_OBJECTS_H
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

   Module name: Create_pSOS_Objects

   Filename:  objects.h


            Written by: Mark Lazarewicz 
                  Date: 12/31/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
        0           12/31/96      Mark L      Initial 
        1           04/18/96      Mark L      Bump MAD_ALLOC_SIZE * 4
        2           08/03/96      Mark L      Define WELD_DATA_ALLOC_SIZE
        3           02/10/97      LAM         doubled mad_buffer_size     
        4           04/01/97      LAM         deleted unused defines      
        5           04/28/97      LAM         cleanup            

 ------------------------------- DESCRIPTION -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"          /* for BOOLEAN TYPE */
#include "root.h"              /* contains defines for startup initialization */

/*
 --------------------------------- DEFINES -------------------------------------
*/

#define BUFFER_SIZE                    128
#define NUMBER_OF_BUFFERS              16

#define MAD_BUFFER_SIZE                BUFFER_SIZE * 8
#define MAD_ALLOC_SIZE                 BUFFER_SIZE * NUMBER_OF_BUFFERS * 16

#define READ_LOG_BUFFER_SIZE           BUFFER_SIZE * 8
#define READ_LOG_ALLOC_SIZE            BUFFER_SIZE * NUMBER_OF_BUFFERS * 8

#define SOFTWARE_DOWNLOAD_BUFFER_SIZE  256
#define SOFTWARE_DOWNLOAD_ALLOC_SIZE   SOFTWARE_DOWNLOAD_BUFFER_SIZE * NUMBER_OF_BUFFERS


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

SYS_STARTUP_STATUS_TYPE CreatePsosObjects(
   void
   );

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* CREATE_PSOS_OBJECTS_H */
