/* $Header:   D:/SWLab/VMdb/2000Series/App/MENUEQAL.C_V   1.6   02 Sep 2008 21:05:38   nhahmed  $ */
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

/*--------------------------- MODULE DESCRIPTION ---------------------------*/

/*   Module name:     EQUIPMENT_FAILURE_ALARMS_TEXT                         */
/*                                                                          */
/*   Filename:        menueqal.c                                            */
/*                                                                          */
/*   Function name:                                                         */
/*                                                                          */
                                    
/*------------------------------- REVISIONS --------------------------------*/

/*   Revision #   Date       Author      Description                        */
/*   ==========   ========   ======      ===========                        */
/*      1.0       07-11-97   BEKymer     Initial Version                    */
/*      1.1       11-18-97   LAM         chged welddata to finalresults     */
/*      1.1.6.1   02-08-00   JZ          removed DVS, added Mask1, Cond1,   */
/*                                       Mask2, Cond2                       */
/*      1.1.6.2   02-23-00   OFI         removed 'User experience level' from menu strucutures*/                                                                    
/*      1.2       04-06-00   JZ          merged Lang to trunk               */
/*      1.3       05-26-00   SCM         Checked in for testing by Laura, John.*/
/*      1.4       06-14-00   SCM         Removed tabs and checked in for build.*/
/*      1.5       06-28-00  BEKymer     Changed all MODEL to LEVEL            */
/*      1.6       09-02-08  NHAhmed     CleanUp for multi-language support.  */

/*------------------------------ DESCRIPTION -------------------------------*/


/* This file deals with the equipment failure Alarms and their submenus     */



/*----------------------------- INCLUDE FILES ------------------------------*/

