/* $Header:   D:/SWLab/VMdb/2000Series/App/MENU1C.C_V   1.18.2.0   02 Sep 2008 21:05:30   nhahmed  $ */
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

   Filename: menu1c.c

   Function name:

                                      
 --------------------------------- REVISIONS --------------------------------

   Revision #      Date          Author      Description
   ==========     ========       ======      ===========
      1.0         10-08-96       PhilJ       Initial Version
      1.10        11-08-96       PhilJ       Changed name of enable/disable
                                             flag in Suspect & Reject menus.
      1.20        11-13-96       PhilJ       Changed Param ID from XXCANTCHANGEXX
                                             to SUSPECT or REJECTLIMITSFLAG.
      1.30        12-06-96       PhilJ       Added Min/Max Limits to menus.
      1.40        12-13-96       PhilJ       Correct minus limits BitMask.
      1.50        01-28-97       PhilJ       Corrected error in +Coll Limit menu.
      1.60        03-17-97       PhilJ       Corrected error in Param ID's.
      1.70        04-28-97       PhilJ       Added global suspect and reject
                                             limits enable flag.
      1.8         08-29-97       BEKymer     Fix strings for rej & susp alarm
      1.9         09-02-97       BEKymer     Change actual string to include
                                             units
      1.10        10.30.97       JBerman     Created new title Suspect/Reject
                                             Deleted previous titles; DCS 1957
      1.11        11-18-97       LAM         chged welddata to finalresults     
      1.12        08-10-98       BEKymer     Rename ActualCollapse to Actual
                                             TotalCollapse
      1.13        10-09-98       BEKymer     Create new structure for WeldCol
                                             DistActual
      1.13.6.1    02-07-99       JZ          removed DVS added Mask1, Cond1, Mask2, Cond2
      1.13.6.2    02-23-00       OFI         removed 'User experience level' from menu strucutures
      1.14        04-05-00       JZ          merged Lang to trunk
      1.15        05-26-00       SCM         Checked in for testing by Laura, John.
      1.16        06-14-00       SCM         Removed tabs and checked in for build.
      1.17        06-28-00      BEKymer      Changed all MODEL to LEVEL
	   1.18        01-12-06      Bwadia       Added VGAExit button 
      1.19        09-02-08      NHAhmed      CleanUp for multi-language support.


 ------------------------------- DESCRIPTION ---------------------------------
*/


/* This file deals with Alarm submenus for the +/- Collapse Distance Limit  */


/*
 ------------------------------ INCLUDE FILES -------------------------------- */
