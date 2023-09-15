/* $Header:   L:/pvcs/1000/psos332/archives/inc/NVMTYPE.H_v   2.1   01 Aug 1996 14:51:20   BKYMER  $ */
#ifndef NVM_TYPE_H
#define NVM_TYPE_H
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
------------------------------ MODULE DESCRIPTION -----------------------------

------------------------------ REVISIONS --------------------------------------

----------------------------- DESCRIPTIONS ------------------------------------

   This file contains parameter definitions used in function prototype of nvm
area.

---------------------------- INCLUDE FILES ------------------------------------
*/
#include "portable.h"

/*
-------------------------------- DEFINES  -------------------------------------
*/

/*
---------------------------- TYPE DECLARATIONS --------------------------------
*/
                                                                            
typedef UINT16  DATA_BYTE_COUNT_TYPE;    /* Number of bytes to access     */

typedef UINT16  DATA_BYTE_OFFSET_TYPE;   /* Offset from the start of DRAM */  

/*
--------------------------- FUNCTION PROTOTYPES -------------------------------
*/

#endif /* NVMTYPE_H */
