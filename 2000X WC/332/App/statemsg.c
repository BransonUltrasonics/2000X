/* $Header:   D:/SWLab/VMdb/2000Series/App/STATEMSG.C_V   1.16   04 Sep 2008 20:16:38   ygupta  $ */
/****************************************************************************/ 
/*                                                                           */
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
                                          
   Module name:  Display_State_Message

   Filename:  statemsg.c                  

   Function name: DisplayStateMessage


            Written by: Mark Lazarewicz  
                  Date: 05/01/96 
              Language:  "C"


 -------------------------------- REVISIONS ------------------------------------

   Revision #  Date       Author   Description
   ==========  ========   ======   ===========
      0        05/01/96   Mark L   April Fooled Ya
      1        09-12-96   BEKymer  Moved message into RunBuffer so Run screen
                                   handler can deal with it
      2        11-05-96   BEKymer  No longer scroll dry cycle messages down   
      1.7      09-09-97   LAM      chged function prototype
      1.8      07-31-98   BJB      Includes kpresmsg.h, getmsg.h
      1.9      05-26-00   SCM      Checked in for testing by Laura, John.
      1.10     06-14-00   SCM      Removed tabs and checked in for build.
      1.11     07-30-00   LAM      Fixed updating the first line of the run 
                                   with multiple languages.
      1.12     07-25-05  Bwadia    Added support for Asian Languages for
                                   DisplayStateMessage function.
      1.13     08-19-05  Bwadia    DisplayStateMessage to support all language
                                   strings for different states
      1.14     04-05-07  NHAhmed   Modified DisplayStateMessage() for Weld Result Screen.
      1.15     09-02-08  NHAhmed   CleanUp for multi-language support.
      1.16     09-04-08  YGupta    CleanUp for LangTest Project.
 ------------------------------- DESCRIPTION -----------------------------------

   This module will display/scroll startup messages during welder initialization

 ------------------------------- PSEUDO CODE -----------------------------------

 
 ------------------------------ INCLUDE FILES ----------------------------------
*/ 


/*----------------------------- EXTERNAL DATA ------------------------------*/


/*----------------------------- LOCAL DEFINES ------------------------------*/


/*------------------------ LOCAL TYPE DECLARATIONS -------------------------*/                  


/*------------------------------ GLOBAL DATA -------------------------------*/
/*                      (scope is global to ALL files)                      */




/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/
/*                      (scope is global to THIS file)                      */


/*--------------------------- EXTERNAL FUNCTIONS ---------------------------*/


/*----------------------- LOCAL FUNCTION PROTOTYPES ------------------------*/


/*--------------------------------- CODE -----------------------------------*/


