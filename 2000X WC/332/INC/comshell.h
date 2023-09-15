/* $Header:   L:/pvcs/1000/psos332/archives/inc/COMSHELL.H_v   2.1   01 Aug 1996 14:48:32   BKYMER  $ */
#ifndef COMM_SHELL_H
#define COMM_SHELL_H
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

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Communication Shell

   Filename:    comm_shell.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0            02/08/96      Mark Lazarewicz Initial release 
 ------------------------------- DESCRIPTION -----------------------------------

 This header contains all the information needed by comm_shell.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "comparam.h"


/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/



/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/
void CommShell( COMM_TASK_PARAMS_TYPE task_params );

#endif






