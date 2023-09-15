/* $Header:   D:/SWLab/VMdb/2000Series/App/MENUOLAL.C_V   1.20   02 Sep 2008 21:05:38   nhahmed  $ */
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

/*   Module name:     OVERLOAD_ALARMS_TEXT                                  */
/*                                                                          */
/*   Filename:        menuolal.c                                            */
/*                                                                          */
/*   Function name:                                                         */
/*                                                                          */
                                    
/*------------------------------- REVISIONS --------------------------------*/

/*   Revision #   Date       Author      Description                        */
/*   ==========   ========   ======      ===========                        */
/*      1.0       07-11-97   BEKymer     Initial Version                    */
/*      1.1       09-02-97   BEKymer     Add additional overload information*/
/*      1.2       10-07-97   BEKymer     In OverloadFreqChg change FREQUENCY*/
/*                                       to FREQOFFSET to allow for minus   */
/*      1.3       11-18-97   LAM         replaced finalresults with weldingresults*/
/*      1.4       02-06-98   BJB         Changed type of OverloadPeakPwr to */
/*                                        PERCENTX10.                       */
/*      1.5       08-14-98   BEKymer     Change variables used for PT O/L   */
/*                                       so real values are displayed       */
/*                                       Also change AB overload power value*/
/*      1.5.6.1   02-08-00   JZ          removed DVS, added Mask1, Cond1,   */
/*                                       Mask2, Cond2                       */
/*                                                                          */
/*      1.5.6.2   02-23-00   OFI         removed 'User experience level' from menu strucutures*/
/*      1.6       04-06-00   JZ          merged Lang to trunk               */
/*      1.7       05-26-00   SCM      Checked in for testing by Laura, John.*/
/*      1.8      06-28-00  BEKymer    Changed all MODEL to LEVEL            */
/*      1.9      07-18-00    JLH      Added DUPS to menus.                  */  
/*      1.10     08-09-00    JLH      Changed TestBuffer to WeldOLStatus.   */
/*      1.11     08-10-00    JLH      Added new menu structures.            */
/*      1.11     08-10-00    JLH      Added new menu structures.            */
/*      1.12     08-16-00    LAM      fixed title lines for ol structures.  */
/*      1.13     08-28-00    LAM      fixed title lines when ws is off      */
/*      1.14     08-30-00    AT       fixed titleOverloadMenu               */
/*                                    created titleOverloadAnalogMenu       */
/*      1.15     08-30-00    AT       added titleOverloadAnalogMenu to other menus */
/*      1.16     04-06-04  VSharma    Added 'OverloadEnergyBraking' menu.   */
/*      1.17     04-19-04  VSharma    Added OverloadTestDUPSTemp in OverloadMenuTest. */
/*      1.18     01-12-06   Bwadia    Added VGAExit button                  */
/*      1.19     08-11-06   LAM       removed temp in test OL info          */
/*      1.20     09-02-08   NHAhmed   CleanUp for multi-language support.     */
/*------------------------------ DESCRIPTION -------------------------------*/


/* This file deals with the overload Alarms and their submenus              */



/*----------------------------- INCLUDE FILES ------------------------------*/
