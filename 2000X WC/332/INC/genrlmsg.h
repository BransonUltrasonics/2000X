/* $Header:   K:\APPS\PVCS Pro\332\INC\GENRLMSG.H_V   2.2   Apr 19 1999 15:35:10   ofingere  $ */
#ifndef GENERIC_MSG_H
#define GENERIC_MSG_H
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

   Module name: GENERIC_MSG

   Filename: genrlmsg.h 

 -------------------------------- REVISIONS ------------------------------------

	   2.2      04/19/99      OFI       Changed for DIAB
 ------------------------------- DESCRIPTION -----------------------------------


*/

/*
 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "commnmsg.h"  

/*
 ------------------------------- DEFINES ---------------------------------------
*/

									       

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/

typedef struct 
    {  
    COMMON_MSG_FIELD_TYPE common;             
    ULONG lword1;
    ULONG lword2;
    ULONG lword3;
    } GENERIC_MSG;

#endif /*  GENERIC_MSG_H */
