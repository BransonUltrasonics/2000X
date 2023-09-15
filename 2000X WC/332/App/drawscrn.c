/* $Header:   D:/SWLab/VMdb/2000Series/App/drawscrn.c_v   1.11   Oct 22 2007 19:03:46   YGupta  $ */
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
/****************************************************************************/
/*
---------------------------- MODULE DESCRIPTION -------------------------------

     Module name:

        Filename: drawscrn.c

      Written by:  
            Date: 04/17/2003 
        Language: "C"

--------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
  ==========      ========       ======      ===========
      1.0          04/17/03       SCM        Initial Version
      1.3          05/28/03       SCM        Modified files to use Qvga_Transmit instead of 
                                             SendDatatoSem()
      1.4          05/28/03       SCM        Removed reference to txafifo in this module.
      1.5          07/10/03       SCM        Added PVCS Header.
      1.6          07/31/03       JOY        Added Function Headers.
                                             H/W availability checking has been done
                                             before sending commands to the QVGA.
      1.7          08/28/03       JOY        TouchScreen beep is disabled.
      1.10         06-10-05       Aare       Renamed Str_Text to Str_Textstring
                                             because of name conflict in Excel.
      1.11         10-22-07       NHAhmed    Changes done for LangTest phase 0

*/
/*
 ------------------------------- DESCRIPTION ---------------------------------
*/


/*
 ------------------------------ INCLUDE FILES --------------------------------
*/
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <psos.h>
#include "menu.h"
#include "drawscrn.h"
#include "qvga_uart.h"
#include "names.h"

/*------------------------------- LOCAL DEFINES ----------------------------*/

/*------------------------------- GLOBAL DATA ------------------------------*/
  const SINT8 Str_ClrScrn[]   = "clearscreen;"; 
  const SINT8 Str_Textstring[]      = "textstring";
  const SINT8 Str_Rect[]      = "rectangle";
  const SINT8 Str_Line[]      = "line";
  const SINT8 Str_BgColor[]   = "setbackground";
  const SINT8 Str_Beep[]      = "beep";
  const SINT8 Str_VeeUp[]     = "vee_up";
  const SINT8 Str_VeeDown[]   = "vee_down";
  const SINT8 Str_SemiColon[] = ";";
  const SINT8 Str_EraseFlash[]= "ef;";
  const SINT8 Str_SaveImage[] = "lf";
  const SINT8 Str_DispImage[] = "sf";
  
/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern UINT32 qvgasemid;

/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -----------------------
*/
SINT16 SPrintf(SINT8* pc_buf, const SINT8* pc_format,...);
/*
 ---------------------------------- CODE -------------------------------------
*/


void TouchScrnBeep (UINT16 Count)
/****************************************************************************/
/*Description:                                                              */
/* Makes Beep                                                               */
/*Input Parameters:                                                         */
/* Count- Beep duration, each count corresponds to 100ms                    */
/****************************************************************************/
{
   SINT8 buffer[MAX_BUFFER_SIZE];
   if(Count == 6)
   {
   /* send commands to QVGA, if it is available */
   if(IsHWConfigured(QVGA))
   {
      /*Create the Command string*/
      SPrintf (buffer, "%s %d%s", Str_Beep, Count, Str_SemiColon);
      QVGA_Transmit(buffer);
   }
   }
  
}



/*==========================================================================*/
/*****************************End********************************************/
/*==========================================================================*/