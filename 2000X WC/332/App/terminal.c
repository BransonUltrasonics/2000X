/* $Header:   D:/SWLab/VMdb/2000Series/App/TERMINAL.C_V   1.39   04 Sep 2008 20:16:40   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1997                 */
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

   Filename: terminal.c


 --------------------------------- REVISIONS --------------------------------

 Rev # Date     Author Description
 ===== ======== ====== ======================================================
 1.0   12/29/97  BJB   Original Version
 1.1   01/05/98  BJB   Added function TermInputBufferCleared().
                       Added delay after clearing screen so terminal has time
                        to do this.
 1.2   01/12/98  BJB   Added function TermSyncMenus(), containing code that
                        was previously at the end of TermDataModeToggle().
 1.3   01/12/98  BJB   Writes message to terminal screen when it turns off.
 1.4   01/15/98  BJB   Added some protection code: Functions that respond to
                        messages to output data line, switch to data mode, and
                        show alarms do nothing if terminal not being used.
                        Also, if there is a data line ready to go, switch out
                        of data mode will clear TermDataAvailable.
                       Added space between date and alarm text on terminal.
                       When switching to data mode, gets last results from
                        weld history, not FinalResults structure.
 1.5   01/16/98  BJB   Outputs scroll lock command with every data line
 1.6   01/22/98  BJB   Added codes to reset display when toggling data mode
 1.7   01/26/98  BJB   Added function GetTermScreenWindowPos().
                       Turns cursor off when doing UpdateTermLine().
                       Created function FillInTermChrs() to format menu lines
                        with special characters.
                       Passes FillInTermChrs() when calling FormatMenuLine().
 1.8   02/04/98  BJB   RemoteTermOn() will switch to data mode if
                        CurrentSetup.RemoteData is TRUE.
                       Fills in bargraphs with underscores instead of = signs.
 1.9   02/06/98  BJB   Displays peak power to one decimal place in
                        TermFormatDataLine().
 1.10  03/19/98  BJB   Writes "Ext" to weld data line for Amp A if amp
                        external, writes "n/a" to Amp B if external.
 1.11  03/20/98  BJB   Looks at new flag in FinalResults to see if stepping is
                        on, instead of RunningPreset.
 1.12  04/05/98  BJB   Clears "print buffer 80% full" alarm bit before
                        printing alarms on terminal (no text for this alarm).
 1.13  04/09/98  BJB   Added formatting changes to weld data output.
 1.14  04/21/98  BJB   Calls simpler version of FormatMenuLine().
 1.15  05/22/98  BJB   Deleted TermFormatDataLine() function, now shares
                        FormatDataLine() with PrintData().
 1.16  06/12/98  BJB   Added function TermUpdateDataHeader().
                       Added some comments to TermDataModeString definition.
 1.17  06/19/98  BJB   Uses common function GetLastWeldData() to get last weld
                        data.
                       Gets latest weld data again in TermUpdateDataHeader(),
                        works to show zeroes after cold start.
 1.18  07-31-98  BJB   Includes kpresmsg.h, getmsg.h
 1.19  08-19-98  BJB   Rewrote as type of standard display/input device.
 1.20  08-21-98  BJB   Added function TermConvertLineToItem().
                       TermSetCurrentItems() doesn't clear screen.
                       CursorOn moved from TermSetCurrentItems() to
                        TermShowMenu(), so not needed in ShowTermMenuItems().
 1.21  09-10-98  BJB   Modified TerminalInput() to use new message format.
 1.22  04-26-99  OFI   Changed for diab
 1.23  05-26-99  LAM   fixed the assembler conversion from microtec to diab
 1.24  05-26-00  SCM   Checked in for testing by Laura, John.
 1.25  06-14-00  LAM   fixed headings for aed vs aef.
 1.26  06-28-00  BEKymer Changed all MODEL to LEVEL
 1.27  09-26-00  JLH   Implemented multilingual support to satisfy tracker issue #3595.
 1.28  09-27-00  JLH   Added GetLangArrayIndex call to DTControlLevelText function.  This was needed for the proper language to
                        be used for 1-line data title lines displayed immediately after power up.
 1.29  11-14-00  BEKymer Make tests for LEVEL_f >= to take into account LEVEL_TEST                     
 1.32  05-02-03  BEKymer Move 1.29 to tip for 8.10 build
                         Use alternate strings when VelocityReporting is FALSE
 1.33  10-15-03  BEKymer Merged 1.32 and 1.29 to create 1.33 for 9.00A build
 1.34  12-19-03  BEKymer Added piece of code in DTControlLevelText() that was
                          missed during the merge.
 1.35  06-15-04  VSharma Modified TermOutputDataLine() to print PresetName in Header.
 1.36  07-21-04  JOY     Removed duplicated weld results on terminal at power up. issue #3811
 1.37  06-10-05  Aare    Renamed AlarmText to Alarm.                     
 1.38  09-02-08  NHAhmed CleanUp for multi-language support.                     
 1.39  09-04-08  YGupta  CleanUp for LangTest Project.
                          
*/

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/


/*------------------------------- LOCAL DEFINES ----------------------------*/

/*------------------------------- GLOBAL DATA ------------------------------*/
/*                       (scope is global to ALL files)                     */


/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/
