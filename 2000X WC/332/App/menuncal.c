/* $Header:   D:/SWLab/VMdb/2000Series/App/MENUNCAL.C_V   1.10   02 Sep 2008 21:05:38   nhahmed  $ */
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

/*   Module name:     NOCYCLE_ALARMS_TEXT                                   */
/*                                                                          */
/*   Filename:        menuncal.c                                            */
/*                                                                          */
/*   Function name:                                                         */
/*                                                                          */
                                      
/*------------------------------- REVISIONS --------------------------------*/

/*   Revision #   Date       Author      Description                        */
/*   ==========   ========   ======      ===========                        */
/*      1.0       07-11-97   BEKymer     Initial Version                    */
/*      1.1       09-02-97   BEKymer     Changed TriggerLostMenu to         */
/*                                       TriggerLostMenuWeld                */
/*      1.2       09-11-97   LAM         unit test version                  */
/*      1.3       11-18-97   LAM         chged welddata to finalresults     */
/*      1.4       01-29-98   BEKymer     Use TriggerLostTime instead of     */
/*                                       WeldingResults.ActualWeldTime in   */
/*                                       TrigLostTime                       */
/*      1.4.6.1   02-08-00   JZ          removed DVS, added Mask1, Cond1,   */
/*                                       Mask2, Cond2                       */
/*      1.4.6.2   02-23-00   OFI         removed 'User experience level' from menu strucutures*/
/*      1.5       04-06-00   JZ          merged Lang to trunk               */
/*      1.6       05-26-00   SCM        Checked in for testing by Laura, John.*/
/*      1.7      06-28-00  BEKymer      Changed all MODEL to LEVEL           */
/*      1.8      06-10-05  Aare         Commented out unused alarms.        */
/*      1.9      01-12-06    Bwadia     Added VGAExit button                */
/*      1.10     09-02-08    NHAhmed    CleanUp for multi-language support. */
/*------------------------------ DESCRIPTION -------------------------------*/


/* This file deals with the no cycle Alarms and their submenus              */



/*----------------------------- INCLUDE FILES ------------------------------*/
