/* $Header:   D:/SWLab/VMdb/2000Series/App/qvgakeypad.c_v   1.29   Oct 22 2007 19:05:56   YGupta  $ */
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

     Module name: Keypad Screen

        Filename: qvgakeypad.c

      Written by: Bwadia 
            Date: 04/28/2003 
        Language: "C"

--------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
  ==========      ========       ======      ===========
      1.0          04/28/03                  Initial Version
      1.6          06/23/03      JOY         Moved Language strings to "menutext.c". 
                                             Increased Fontsize of the Point(.) on the button.
                                             Changed Cursor from '|' to '_'.
                                             Min/Max Values are Displayed always.
      1.7          07/22/03      JOY         Added AlphaNumeric Entry Screen.
      1.8          08/13/03      JOY         Added Current/New Value strings for P/S, Act.
                                             serial number ALPHA types in 'DrawKeypadScreen()'. 
      1.9          08/24/03      JOY         Alarms/Estop is added in keypad Screen.     
      1.10         09/07/03      JOY         Added OFF Button in keypad Screen.
                                             Added TIME, DATE, PASSWORD processing in
                                             -'QVGAAlphaEntry()'.
      1.11         09/18/03      JOY         Added Error Rectangle.
                                             Added VFD Error Beeps.
                                             Button Stuck problem is solved.
      1.12         09/26/03      JOY         Max Val Display is corrected in case of
                                             -ENERGY Format.
      1.13         10/13/03      JOY         Cursor is displayed before next char is accepted.
      1.14         10/16/03      JOY         MiddleSeg is erased by QVGA ROM image.
      1.15         10/23/03      JOY         AlphaNum Key toggling state time is reduced.
                                             Added Touch Release Beep.
      1.16         10/24/03      JOY         Illegal value is retained when error
                                             -popup comes up, 'New value' is replaced with
                                             -'Reenter Value'.    
      1.17         11/14/03      JOY         Removed'OFF' button from keypad in stepping screen.
      1.18         11/26/03      JOY         ESTOP exit related changes.
      1.19         12/03/03      JOY         'OnKeypadScreen' flag is set on keypad screen,
                                             -this flag is used in weldmngr to stop Test.
      1.20         02/20/04      VSharma     Modified DrawKeypadScreen() & QVGAAlphaEntry() for
                                             WriteInFields.
      1.21         07/30/04      JOY         In case of Alpha-Numeric keypad, cursor is moved right
                                             on INC key press.
      1.22         08/24/04      JOY         keypad screen title is cleared.
      1.23         09/01/04      JOY         Added TITLE to all the keypad pop-ups.
      1.24         09/03/04      JOY         Modified Keypad-popup title.
      1.25         09/09/04      JOY         OFF button is not proccessed, when it is not displayed.
      1.26         09/21/04      JOY         OFF button is removed from Amplitude step, Force step, pretrig menu variables.
      1.27         07-25-05      Bwadia      Dummy check in 
      1.28         02-07-07      NHAhmed     Changed display format of date for Asian languages(yyyy/mm/dd).
      1.29         10-22-07      NHAhmed     Changes done for LangTest phase 0


*/
/*
 ------------------------------- DESCRIPTION ---------------------------------    
*/


/*
 ------------------------------ INCLUDE FILES --------------------------------
*/
