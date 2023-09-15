/* $Header:   K:\APPS\PVCS Pro\332\INC\ERROR.H_V   2.4   Apr 19 1999 14:37:50   ofingere  $ */
#ifndef ERROR_H
#define ERROR_H
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
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: error.h

 --------------------------------- REVISIONS --------------------------------

   Revision #  Date      Author   Description
   ==========  ========  ======   ===========
   0                              Initial Version                   
   2.3         11-11-97  BJB      Added new error, NOVALUE.
   2.4		   04-19-99	 OFI	  Changed for DIAB
*/


#define MAXNMBRERRORS      1000

enum ERRORCODES { TIMERFAILED1 = 1,    /* No timers available             */
                  TIMERFAILED2,        /* Time requested was 0            */
                  MINRANGE,
                  MAXRANGE,
                  IDXRANGE,            /* Index out of range              */
                  PTRRANGE,            /* Pointer out of range            */
                  NOVALUE  };          /* No value entered after ClearKey */


#endif