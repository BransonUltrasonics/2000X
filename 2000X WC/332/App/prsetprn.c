/* $Header:   D:/SWLab/VMdb/2000Series/App/prsetprn.c_v   1.225   08 Jun 2010 14:11:58   NHahmed  $ */
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name:       :   Prsetprn                                          */
/*                                                                          */
/* Filename           :   Prsetprn.c                                        */
/*                                                                          */
/* Function Name      :   Allow Preset printing capabilities                */
/* Function Prototypes:                                                     */
/*                                                                          */
/*                        void SystemPresetReport(void);                    */
/*                        void FormatString( SINT8 *, SINT8 *, SINT8 *)     */
/*                        void FormatHeader( SINT8 *, SINT8 *)              */
/*                        void FormatNumber( SINT8 *, SINT32, SINT8 *)      */
/*                        void SendACharToPrint(UINT8);                     */
/*                        void InitMessage(UINT8);                          */
/*                        SINT32 SeqToPrinter(const UINT8 *, SINT32);       */
/*                        void InitPresetPrinter(void);                     */
/*                        void FormatRightJ(SINT8 *, SINT8 *);              */
/*                                                                          */
/*          Written by:   Paul M. Garvey                                    */
/*                Date:   08-01-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*
                                                                          
  Revision#  Date       Author     Description                            
  =========  ========   =========  ===========                            
     0       09/10/96    PaulG     Initial                                
     1.01    09/23/96    PaulG     Added Metric units using InchToMm      
                                   and PoundToNewton. Also convert        
                                   date when metric option is selected.       
     1.02   09/24/96     PaulG     Modified time display from integer     
                                   to float.                              
     1.03   09/30/96     PaulG     Highlight header on each page
     1.04   10/31/96     PaulG     Modified Reject and Suspect limits
     1.05   11/07/96     PaulG     Added SAMPLE and ALARMS flags
     1.06   11/15/96     PaulG     Modified PressureGauge output.
     1.07   12/03/96     PaulG     Added InitPresetData function to initalize variables.
     1.08   12/12/96     LAM       deleted unused variable updating defaults in weld_obj 
     1.09   12/19/96     PaulM     Added Global Print On Sample and Alarm.
     2.00   12/22/96     LAM       chged strokelen struct                  
     2.01   01/10/97     PaulG     Added preset number and *.                  
     3.00   01/29/97     LAM       chged missingpart member                
     3.01   01/31/97     PaulG     clear PrestString after printing.                
     3.02   02/03/97     PaulG     Added MaxTimeout to printout and modified
                                   Inch to Metric conversion.                
     3.03   02/05/97     PaulG     Changed printing format from 6.2f to 6.4f.                
     3.04   02/06/97     PaulG     Changed Force variables to n/a.                
     4.00   02/07/97     LAM       moved actclr to preset             
     4.01   02/10/97     PaulG     Changed format for metric printout             
     4.02   02/25/97     PaulG     Changed DownSpeed to n/a if AE.             
     4.03   02/26/97     PaulG     Added header.             
     4.04   03/05/97     PaulG     Modified date and time.             
     4.05   03/11/97     PaulG     Cleanup  date and time.
     4.06   04/03/97     PaulG     Modified PeakPwr from W to %.             
     4.07   05/08/97     PaulG     Cleanup code
     4.08   05/27/97     PaulG     Print 10cpi.     
     4.09   05/30/97     PaulG     Changed Energy values to UINT32 from UINT16.     
     5.00   06/06/97     LAM       Cleanup code
     6.1.36 06/16/97     LAM       deleted weldmodesflag
     6.1.37 06/18/97     philj     Changed CurrentSetup.WeldTimes and TestTimes
                                   to CurrentSetup.TimeMultiplier & TestMultiplier
     6.1.38 06/18/97     PaulG     Changed PrintOnSample to PrintOnSampleSetup
     6.1.39 06/19/97     PhilJ     Changed Language vars to enum
     6.1.40 06/26/97     PaulG     Restructure setup print out. 
     6.1.41 07/18/97     PaulG     Restructure setup print out (contd.1)
     6.1.49 07/23/97     PaulG     Restructure setup print out (contd.2)
     6.1.51 07/24/97     PaulG     Restructure setup print out (contd.3)
     6.1.52 07/24/97     PaulG     Restructure setup print out (contd.4)
     6.1.53 07/29/97     PaulG     Modified Seial Port function.
     6.1.54 07/30/97     PaulG     Modified Energy Comp to print only in timemode.
     6.1.55 08/08/97     PaulG     Added printer driver.
     6.1.56 08/28/97     PaulG     Modified Cylinder Diameter and Stroke Length.
     6.1.57 08/28/97     PaulG     Modified UILines.
     6.1.59 08.29.97     JBerman   Page Size, Removed Echo, Missing Part
     6.1.60 09-05-97     PaulG     Reset UILines to 0 at beginning of report.
     6.1.61 09-11-97     PaulG     Check if formfeed is on before printing page 2.
     6.1.62 09-15-97     PaulG     Changed LinesPerPage to WeldsPerPage.
     6.1.64 09.18.97     JBerman   DCS# 1948 issues.                              
     6.1.65 09.23.97     JBerman   Check if Feature is on, printout accordingly.                              
     6.1.66 09-24-97     PaulG     Modified Page printing.
     6.1.67 09.24.97     JBerman   Added default to Page Size: 11". 
                                   Ground Detect Abort prints n/a at Normal
     6.1.68 09.25.97     JBerman   Modified Peak Power Cutoff & Missing Part
     6.1.69 10-06-97     PaulG     Modified CheckToPrintPageTwo().
     6.1.70 10.07.97     JBerman   Moved PageSxx definitions to preset.h
     6.1.71 10-08-97     PaulG     Dont print Limits header if controllevel is 1. 
     6.1.73 10.14.97     JBerman   Removed 19200 serial BaudRate from printout
     6.1.74 10-31-97     PaulG     Modified page feed.
     6.1.74 11-06-97     PaulG     Modified formfeed in reference to pagesize.
     6.1.75 11-14-97     PaulG     Removed InitEPSON and InitIBMPRO from code.
     6.1.76 11-17-97     PaulG     Changed from 10 cpi to 12 cpi. Also modified
                                   XAutoScale for modes other than Time.
     6.1.77 11-24-97     LAM       deleted unused currentsetup elements         
     6.1.79 12.02.97     JBerman   In PrintConfig0020 I changed PASSWD -> VALUEON
     6.1.80 12.03.97     JBerman   Fixed "X Axis Scale" lookout.
     6.1.81 12.04.97     JBerman   Added Start Screen to the setup
     6.1.82 12.22.97     JBerman   Added TMODONLY to print on timemode only
     6.1.83 01.19.98     BJB       Always prints MaxTimeout, never shows "Off"
     6.1.84 01.22.98     BJB       Uses StrOn[], StrOff[], not YESSTR, NOSTR
     6.1.85 01-28-98     PaulG     Added 3 LF from Page 1 to Page 2 of Setup printout.
     6.1.86 02.12.98     JBerman   1) Showing the values of +/- R Energy Limit 
                                      and +/- R Power Limit, when RejectLimit=Off
                                   2) Showing the values of +/- S Energy Limit 
                                      and +/- S Power Limit, when RejectLimit=Off
     6.1.87 02.19.98     JBerman   CurrentSetup.Features->CurrentPreset.Features
     6.1.88 02.23.98     PaulG     Removed ESC code from InitPresetPrinter().
     6.1.89 02.24.98     PaulG     Before printing Header in the center of the page
                                   check if you need to formfeed to next page.
     6.1.90 03.06.98     JBerman   Fixed: +/- S Power/Energy "n/aJ" issue
     6.1.91 03.10.98     JBerman   Fixed: Max Timeout "n/as".
     6.1.92 03-26-98     PaulG     Replace AutoScaleFlag with PrintBottomFlags.
     6.1.93 04-06-98     PaulG     Remove Control Limits in Peak Power mode.
                                    Move MaxTimeout from under Controls limits menu.
     4.1.94 05.13.98     JBerman   Print the approptiate actuator.
     4.1.95 05.15.98     PaulG     Change all AED to AEF|AED, also added Digital Tune.
                                   Changed "Page of" to "Page".
     4.1.96  05.15.98     PaulG     Switch controllevel 3 & 4 from "a" to "d".
     4.1.97  05.18.98     PaulG     Reset PageNumber variable on completion of report.
     4.1.98  05.22.98     PaulG     Modified  Gauge pressure by dividing by 10
     4.1.99  05.22.98     BJB       Prints force values stored as tenths of pounds.
     4.1.100 05.22.98     PaulG     Add sysbols for Force values i.e "N" and "Lbs".
     4.1.101 05.22.98     BJB       Removed extra divide by 10 in calls to
                                    PoundToNewton().
     4.1.102 06.04.98     JBerman   In PrintConfig0010, I converted GetActId
                                    with the appropriate BITx
     4.1.103 06.04.98     BJB       Modified output of CurrentSetup.DigPot, format
                                    of this variable has changed.
     4.1.104 06.08.98     JBerman   Printout Setup, DCS 2608.
     4.1.105 06.09.98     JBerman   Printout Setup, DCS 2608.
     4.1.106 06.25.98     JBerman   Printout setup.
     4.1.107 06.26.98     JBerman   Printout setup, PMAXTIMEOUT.
     4.1.108 06-29-98     PaulG     Added Function LastDatePresetWasSaved() to capture date.
                                    Also changed distances to 2 decimal places from 4.
     4.1.109 07.02.98     JBerman   Printout setup, Control Limits title.   
     4.1.110 07.15.98     JBerman   All Suspect Limits to be N/A for basic.   
     4.1.111 07.22.98     PaulG     Modified function PrintConfig0010 to select proper actuator type.
     4.1.112 07.30.98     BJB       Deleted act_nvr definition, uses actnvram.h.
     4.1.113 08-11-98     PaulG     Replace CurrentPressure with GaugePressure.
     4.1.114 08-24-98     PaulG     Change PresetCheck to extern, already defined in pr_print.c
     4.1.115 09-03-98     PaulG     Modified system pressure to a reduced resolution.
     4.1.116 09-09-98     PaulG     Modified peak power and step at power resolution.
     4.1.117 09-17-98     PaulG     Modified gauge pressure printout on setup to round off at 1 dec. place.
     4.1.118 09-25-98     PaulG     Modified string from Power Graph on Sample to + R Power Limit.
     1.119   10-05-98     LAM       deleted duplicate PSITOKPA from graphs.h                       
     1.120   10-30-98     PaulG     Remove test code (TestVal).
     1.121   11-04-98     PaulG     Added text string "Set Gauge Pressure", also modified
                                    "Gauge Pressure" to "Act. Gauge Pressure" for AED mode.
     1.122   12-07-98     BJB       Modified output of digital tune freq for 15/30KHz support.
     1.123   12-09-98     LAM       Modified output of freq for 15/30KHz support.
     1.124   04-23-99     OFI       Changed for diab
     1.125   05-25-99     JZ        Changed AENVR to NVR_AE, AEDNVR to NVR_AED, AEFNVR to NVR_AEF
                                    modified if statements using CurrentSetup.Actuator instead of NVR.ActId
     1.125.4.1 08-19-99   JLH       Modified aef/aof Settings section of printout.  Added calibration
                                    info to System Information section of printout.
     1.125.4.2 09-08-99   JLH       Changed printer init sequences and removed decimal point from Newtons
                                    printed when in metric mode.
     1.125.4.3 09-10-99   JLH       Print System Pressure even if weld cycle count is 0.  Delete duplicate
                                    Rapid Traverse printout.  Print Rapid Traverse Distance even if Rapid
                                    Traverse is off. 
     1.125.4.4 09-14-99   JLH       Numerous functions to print text followed by an underline replaced
                                    with one function called Fillin.
     1.125.4.5 09-23-99   JLH       Corrected format of force step at power value.
     1.127     09-24-99   JLH       Eliminate use of CalDateStr which is defined 2 places.
     1.128     10-08-99   JLH       Adjust SPrintf floating point conversions so floating point conversion
                                    error is eliminated.  Eliminate "SETUP" line and some blank lines so
                                    printout will fit on two pages.  Fix paging so top-of-page margin does
                                    not grow bigger with each page printed.
     1.129     10-13-99   JLH       Revised floating point roundup constants to .01, .001, .0001, and .00001.
     1.130     10-19-99   JLH       Substituted FormatVariable and FormatNumber calls for SPrintf calls so
                                    numbers would print the same way they are displayed on menus.  Also
                                    initiated general cleanup (much remains to be done).
     1.131     10-26-99   JZ        modofied PrintCalibrationDate() and PrintDateTime()
     1.132     11-01-99   JLH       Printer code review changes and more general cleanup.
     1.133     11-05-99   JLH       Changed Velocity variable name to VelocityStr.  Velocity was also
                                     declared in sc.c.  
     1.133.1.1 12-17-99   JLH       Added HP printer and Epson ESC/P printer capability.  Replaced switch in
                                     PrintPageNumber with SPrintf.  Deleted FormatLeftJ function.
     1.134     11-18-99   LAM       fixed step at energy format
     1.135     02-23-00   JZ        merged 7.f4CHp to trunk 
     1.136     02-28-00   JZ        removed tabs
     1.137     02-28-00   JLH       Renamed "PeakPower" array to "PkPower" to avoid redefinition of PeakPower
                                     found in ready.c.
     1.138     03-23-00   JLH       Removed InitPrinterOnceOnPowerup test since this is done in PrintSheet 
                                     in file pr_print.
     1.139     04-03-00   JLH       Move Fixture and Horn to left column of aef printout.  Changed ChecktoStartNewPage
                                     so it does form feed 1 line sooner to try to correct blank page on aed printout
                                     using HP laserjet printer.
     1.140     04-03-00   JLH       Fixed bug in 1.139.  It did not move Fixture and Horn to left column of printout.
     1.141     04-04-00   JZ        moved fixture back to right column, and changed order of print for horn, booster
     1.142     04-10-00   JLH       Merged with Lang branch revision 1.134.6.4.
     1.143     04-24-00   JLH       Changed most remaining strings to multilanguage, indexed by LangIndex.
     1.144     05-05-00   JLH       Added DupsPresetReport.
     1.145     05-05-00   JLH       Fixed SystemPresetReport to blank out half-page spaces for version 9 items.
     1.146     05-12-00   JLH       Changed English, German, Spanish, Italian, and French strings to multilanguage.
     1.148     05-17-00   JLH       Changed multilanguage extern string declarations to put strings in flash.     
     1.149     05-19-00   JLH       More multilanguage fixes.  Condensed Setup printout heading to 3 lines. 
     1.150     05-26-00   JLH       Change printer naming - delete LaserJet and Inkjet, and add OKI520 and HPPCL.
     1.151     06-06-00   JLH       Eliminate Force Ramps printout if control level != 5.
     1.152     06-07-00   JLH       Changed DUPS to DUPSStr to get rid of doubly defined symbol error.
     1.153     06-09-00   JLH       Added 2 lines of printout per page to get LIMITS section on first page.
     1.154,1.155,1.156
               06-13-00   JLH       Added multilanguage support for some remaining strings.
     1.157     06-15-00   JLH       Tweaked System Configuration heading printout to move it to page 2.  It was at the
                                     bottom of page 1.
     1.158     06-16-00   LAM       Forced System Configuration heading printout to move it to page 2.  It was at the
     1.159     06-16-00   LAM       Added fix from rev 1.153.
     1.160     06-26-00   DJL      Made a few global name changes from Preset.MaxForce to Preset.Weldforce
                                   from RejResetRequired to RejResetRequiredFlag; GlobalPrinting to GlobalPrintingFlag
                                   from GeneralAlarmL to GeneralAlarmLFlag
                                  changed MODEL to LEVEL
                                   Added formatting for extra cooling
     1.159.1.2 07-14-00   BEKymer  Added cases for CONTROLEA and CONTROLTEST
     1.159.1.3 08-07-00   JLH      Interim checkin so Laura can compile.
     1.159.1.4 08-07-00   JLH      Erroneous blank line between Pretrigger At Distance and Pretrigger Amplitude removed.
                                    Adjustments made to keep LIMITS section all on first page.
     1.159.1.5 08-08-00   JLH      Changed FormatString and FormatNumber to automatically truncate strings that are too long.
                                    Attempting to process these strings with their original length was locking up the system.
     1.159.1.6 08-09-00   JLH      Force SYSTEM CONFIGURATION section to begin on page 2.   
     1.159.1.7 08-14-00   AT       DupsPresetReport - print real values instead of test data
     1.159.1.8 08-14-00   AT       SystemPresetReport - Fixed some FormatVariable() calls
                                   Went through all 'Needs fixup' and added comments if the fixup belongs to Ver9
     1.159.1.9 08-15-00   AT       Removed space from Ar rayPrint() (hmpf...)
    1.159.1.10 08-16-00   AT       Fixed FormatString and FormatNumber to handle NULL delimiters
    1.159.1.11 08-16-00   AT       Typo in Numblank
    1.159.1.12 08-23-00   AT       Weld status is printed from CurrentPreset
    1.159.1.13 08-23-00   AT       Ramp time, Memory, Wels status are indented (ORS 4726-4728)
    1.159.1.14 08-29-00   AT       changed DUPSStr to DUPSTxt
    1.159.1.15 08-30-00   JLH      Added option of Depot level to control level printout (PrintConfig0011). 
    1.159.1.16 08-30-00   JLH      Fixed bug in Depot level printout (1.159.1.15).
    1.162      03-31-00   LAM      merged back to trunk
    1.163      09-08-00   JLH      Changed CheckIfPrintable to always print for LEVEL_TEST.
    1.164      09-08-00   JLH      Fixed missing break in LEVEL_TEST addition of 1.163.
    1.165      09-15-00   SCM      Changed the value of DupsPresetNum to 20 in function DupsPresetNum().
    1.166      09-22-00   SCM      Changed the string usage in SelectStr().
    1.167      09-26-00   BEKymer  Changed from SeekRampTime to WeldRampTime when printing
                                    Ramp Time in the DUPS section of weld setup  Issue #3596
    1.168      09-27-00   JLH      Changed FormatNumber to truncate strings at 28 characters (was 25).
    1.169      09-27-00   BEKymer  On DUPS Setup printout inthe Software DIP section
                                    print WeldRampTime instead of SeekRampTime (#3598)
    1.170      10-13-00   JLH      Issue #3631 - Reduced 3 pages setup printout on HP610c to two pages.
    1.171      10-17-00   JLH      Called DisablePerforationSkip in InitPrinterNow to get rid of extra
                                    page in setup printout. (#3636)
    1.172      10-19-00   JLH      Replaced dummy value for current DUPS preset number in DUPS preset
                                    report with DUPS_CURRPARAMSET+1. 
    1.173      11-13-00   JLH      Change to print Limits when in LEVEL_TEST.  Limits are printed as 
                                    if level = LEVEL_f. 
    1.174      11-13-00   JLH      Always begin System Configuration on 2nd page, regardless of amount
                                    of 1st page that is used. 
    1.175      11-14-00   BEKymer  Fixed 1 occurance of missed test for LEVEL_TEST vs LEVEL_f
    1.176      08-06-01   BEKymer  Modified PrintConfig0023 so it can handle ASCII output
    1.177      08-21-01   BEKymer  Detab    
    1.178      12-27-03   VSharma  Save the Hour and Min value in 'LastDatePresetWasSaved'.
    1.179      06-04-04   VSharma  Print the UserIO & custom menu values in System configuration.
                                   Print the global values of SampleValue and AlarmFlag when external
                                    preset is enabled.
    1.180      06-22-04   JOY      WriteInField 1 & 2 are printed for both analog/Digital PS in SystemPresetReport().
    1.181      07-27-04   JOY      Updated PrintConfig0081() & PrintConfig0008() with FREQ60KHZ.
    1.182      08-03-04   JOY      Added disable string in GetSelectedOutStr().
    1.183      08-26-04   JOY      Added 'Ext Start Delay' in weld setup printout.
    1.184      09-06-04   JOY      Modified Preset name in PrintHeader().
    1.185      09-21-04   JOY      Added Welder Address to the system report.
    1.186      09-21-04   JOY      Corrected Welder address printing.
                                   Corrected indenting.          
    1.187      06-10-05   Aare     Commented out PrintConfig0013 because strings disappeared from Excel.
    1.188      07-25-05   Bwadia   GetLangArrayIndex modified for Asian langugaes.
                                   RunBuffer1 and Runbuffer2 strings initialized onlangugae change
    1.189      09-10-05   Bwadia   Preset printing for VGA supported 
    1.189.1.0  09-16-05   Bwadia   Pretrigger delay added for VGA in preset printing
                                   Limits section alignment doen for VGA
    1.191      09-18-05   Aare     Merged pretrigger delay printing for VGA and VFD.
    1.192      10-11-05   Bwadia   PSI units corrected in asian language 
    1.193      10-21-05   Aare     Pretrigger delay printing fixed for both VFD and VGA.
    1.194      10-21-05   Aare     Corrected printing for Pretrigger Off.
    1.195      10-24-05   Bwadia   Amplitude printed twice on the print setup screen taken care of
    1.196      10-28-05   Bwadia   Sequencing item added to system configuration print section
    1.197      12-07-05   Bwadia   Added distance, decimal place and +/- PMC limit to
                                   Welder set up printout. Modified for tracker 4028, 3996
    1.198      12-20-05   Bwadia   Sequence printing 'SequencePresetReport' function added.
                                   Also added code function 'VGAPrintSeqPresetInfo' for VGA
                                   Modified for tracker issue 3976
    1.199      01-03-05   Bwadia   Sequence print setup modified and phase loop CF for seek 
                                   function added in printing. Modified for tracker 3976, 3961  
    1.200      01-12-06   Bwadia   Tracker issue 4017, 4018, 4049 for view preset
                                   from USB or P/S worked upon.               
    1.201      01-12-06   Bwadia   Modified start coordinates of View preset data
    1.202      02-07-06   Bwadia   PMC +/- strings changed. Modified for tracker issue 4065 
    1.203      02-07-07   NHAhmed  Changed display format of date for Asian languages(yyyy/mm/dd).
    1.204      02-07-07   NHAhmed  Check-in after code review.
    1.205      03-12-07   NHAhmed  Added SBC Version information in the Setup Print.
    1.206      03-27-07   NHAhmed  Added Functions to print VQSData in the Setup Print.
    1.207      04-16-07   NHAhmed  Modified unit of Peak Power in the Setup Print.
    1.208      04-18-07   NHAhmed  Added VQS Data, Scrub Amplitude in View Setup 
                                   and Scrub Amplitude in Setup Print.
    1.209      10-22-07   NHAhmed  Changes done for LangTest phase 0
    1.210      06-06-08   NHAhmed  Replicated a no. of functions to support a new function
                                   SystemViewPresetReport() associated with command PSPRESET_COMMAND.
    1.211      08-01-08   NHAhmed  Replicated a no. of functions to support added new functions
                                   SystemPresetReport1(), SystemPresetReport2(), SystemPresetReport3(),
                                   SystemPresetReport4(),SystemPresetReport5(),DupsPresetReport1(),
                                   DupsPresetReport2() and PrintSeqPresetInfo() associated with 
                                   command SEND_SETUPPRINT_DATA.
    1.212      08-08-08   NHAhmed  Modified some functions used in printing.
    1.213      09-02-08   NHAhmed  CleanUp for multi-language support.
    1.214      09-04-08   YGupta   CleanUp for LangTest Project.
    1.215      09-09-08   NHAhmed  CleanUp for multi-language support.
    1.216      09-12-08   NHAhmed  Updated functions PrintSetup0049(), PrintSetup0040(),PrintConfig0091()
                                   and PrintConfig0092().
    1.217      09-24-08   NHAhmed  Modified function PrintSeqPresetInfo().
    1.218      10-17-08   NHAhmed  Modified some functions used in printing.
    1.219      10-20-08   NHAhmed  Replaced stroke length LENGTH_7 by LENGTH_2.
    1.220      09-10-09   BEkymer  Add new define MICRO where needed
	 1.221      09-22-09   YGupta   Added Printing support for MICRO Actuator.
	 1.222      09-22-09   YGupta   Modified code for MICRO Sttings in Printing.
	 1.223      09-25-09   YGupta   Modified code to show correct values of different items,
												on ViewPreset Screen and in Setup Printing.
	 1.224      09-25-09   YGupta   Replace AED_SETTINGS_TXT with number as enum value is different on SBC side.
    1.225      06-08-10   PDwivedi Modify GetStrokeLenStr for standard MICRO.    
    

*----------------------------- DESCRIPTION --------------------------------*/


/*----------------------------- GLOBAL FUNCTION ----------------------------*/
void LastDatePresetWasSaved(void);

/*---------------------------- LOCAL EQUATES-------------------------------*/



/*----------------------------INCLUDES--------------------------------------*/

#include <psos.h>    /* Interface environment for PSOS+ routines             */
#include "string.h"
#include <math.h>    /* Math routines.                                       */
#include "preset.h"  /* Defines structs for 1000 series                      */
#include "menu.h"    /* Variable types, structs, enum types for 1000 series  */
#include "util.h"
#include "limits.h"
#include "menu7a.h"
#include "menu4.h"
#include "graphs.h"
#include "prsetprn.h"   
#include "limarray.h"
#include "pr_var.h"
#include "weld_obj.h"
#include "actnvram.h"
#include "rtclock.h"
#include "dups_api.h"
#include "battram.h"
#include "dups_api.h"
#include "inports.h"
#include "outports.h"
#include "command.h"
     
/**-------------------------FUNCTION PROTOTYPE-----------------------------**/
void VGA_PresetSetup1(UINT8 * *AckBuf, SINT8 String[], UINT16 param, UINT8 Data, UINT16 ID);
void VGA_PresetSetup2(UINT8 * *AckBuf, SINT8 String[], UINT16 param, UINT8 Data, UINT16 ID);
void VGA_RejLimPresetSetup1(UINT8 * *AckBuf, SINT8 String[], UINT16 param, UINT8 Data, UINT16 ID);
void VGA_SusLimPresetSetup2(UINT8 * *AckBuf, SINT8 String[], UINT16 param, UINT8 Data, UINT16 ID);
void PrintVQSData0101(void);
void PrintVQSData0102(void);
void PrintVQSData0103(void);
void PrintVQSData0104(void);
void PrintVQSData0105(void);
void PrintVQSData0107(void);
void PrintVQSData0108(void);
void PrintVQSData0109(void);
void PrintVQSData0110(void);
void PrintVQSData0111(void);
void PrintVQSData0112(void);
void PrintVQSData0113(void);
void PrintVQSData0114(void);
void PrintVQSData0116(void);
void PrintVQSData0117(void);
void PrintVQSData0118(void);


/**-------------------------EXTERNAL DATA----------------------------------**/
extern UINT16  ViewDupsPresent;                                                                                                                                                                                                                                                                                                                                                                                                                 

extern STR DUPS_ParamSetName[DUPS_NUMPARAMSET][DUPS_PARAMSETNAMELEN + 1];
extern DEPOT_FLAGS *DepotFlag;
extern CONFIGSETUP CurrentSetup;
extern SETUPS_Ver800      CurrentPreset;
extern UINT32      UILines;            /*-- Line count                     --*/
extern SINT32      MaxWeldsPerPage;    /*-- Maximun welds per page         --*/
extern UINT16      PresetCheck;        /*-- Checks for preset change       --*/
extern UINT32      PresetAddress[];
extern DUPS_CURRENTPARAMSET DUPS_HostParamSet; 
extern STR DUPS_HostParamSetName[DUPS_PARAMSETNAMELEN + 1]; 
extern SINT8 SBCVersionLabel[SBC_SW_VERSION_LENTGH+1];
extern SINT8 SWVersionLabel[SW_VERSION_LENTGH+1];
/**------------------------------------------**
 **       SETUPS CONSTANT STRINGS            **
 **------------------------------------------**/

extern SETUPS_Ver800   MinLimit;
extern SETUPS_Ver800   MaxLimit;
/*--------------------------LOCAL DATA--------------------------------------*/


/* Stores strings that are printed on the left side of the page  */
SINT8   PresetSetup1[ARRYSIZE][SIZEOFBUF];

/* Stores strings that are printed on the right side of the page */
SINT8   PresetSetup2[ARRYSIZE][SIZEOFBUF];

UINT16  GetArrayValue = 0;
SINT8   buffer[LINELEN];        /*-- Holds string to be printed         --*/
SINT8   AltString[LINELEN];     /*-- Holds string to be printed         --*/
SINT8   indentbuf[LINELEN];     /*-- Holds string to be printed         --*/
SINT8   datestr[DATELEN];       /*-- Stores date string                 --*/
SINT8   timestr[TIMELEN];       /*-- Stores time string                 --*/
SINT8   misc[MISCLEN];          /*-- Stores miscelaneous string         --*/
static SINT8   PresetString[SIZEOFBUF];/*-- Stores new preset                  --*/
UINT16  blockArraySize = 0;     /*-- Larger of SetupCt1 or SetupCt2     --*/
UINT16  SetupCt1   = 0;         /*-- Counter for PresetSetup1 array     --*/
UINT16  SetupCt2   = 0;         /*-- Counter for PresetSetup2 array     --*/
UINT16  SusRejFlag = SUSACTIVE; /*-- REJACTIVE: Printing reject limits  --*/
                                /*-- SUSACTIVE: Printing suspect limits --*/
UINT16  PageNumber = 1;         /*-- Inital page# = 1, incremented as pages print --*/
UINT16  LangIndex =0;              /*-- Language array index               --*/
SINT8   LangText[15];
SINT32  LastSavedYear;
SINT32  LastSavedMonth;
SINT32  LastSavedDay;
WELD_DATA SetupPrint;           /*--  Store last weld history cycle     --*/ 
SINT8 VGABuffer[LINELEN*2];
SINT8 TempVGABuffer[LINELEN*2];
SINT8 VGAIndentBuf[LINELEN*2];
SINT8 VGAMisc[VGAMISCLEN+2];
UINT8  Font_Print;
UINT16 LeftPrintXCoordinate;
UINT16 LeftPrintYCoordinate;
UINT16 RightPrintXCoordinate;
UINT16 RightPrintYCoordinate;
UINT16 VGAPrintLength;
UINT16 VGAPrintParam;
SETUPS_Ver800 CurrentViewPreset;
UINT8 Value;
BOOLEAN ValueFlag;
UINT16 Val_ID;



#define MAXSTRLEN 28
/*------------------------------------------------------------------------------*/
/* These are needed to reference into the arrays in limarray.h */
#define INDEX_t 0
#define INDEX_e 1
#define INDEX_ea 2
#define INDEX_d 3
#define INDEX_f 4
#define VGAPRESETNOSTART 4
#define VGAPRESETNAMESTART 16
#define VGAPRESETMODESTART 33
#define VGAPRESETVALUESTART  55
/**------------------------- EXTERNAL FUNCTION -------------------------------**/

UINT16 LangStrLen(SINT8 * str); 
BOOLEAN LangCheckNull(SINT8 * Line);
void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void StrCatTwoBytes(SINT8 * to, SINT8 * from);
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);
UINT16 AddToBufferString(UINT8 * * to, SINT8 * string, UINT16 length);
void Numout1(UINT32 Value, UINT16 Base, STR LC, UINT8 Width, STR *StrAdr);

/**----------------------------------------------------**
 ** This function displays the System (gauge) Pressure.**
 **----------------------------------------------------**/
void PrintSetupSystemPressure(void)
{
   FormatVariables(CurrentPreset.GaugePressure, PRESSURE, VGAMisc, 6, CurrentSetup.Units );
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 74;
   VGAPrintParam = ALWAYS; 
}

/**----------------------------------------------**
 ** This function displays the Scrub Amplitude.  **
 **----------------------------------------------**/
void ViewPresetSetup0003A(void)
{
   FormatVariables(CurrentViewPreset.AmpScrubTime, PERCENT, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value =0;
   ValueFlag = FALSE;
   Val_ID = SCRUBAMP_TXT;
   VGAPrintParam = PSCRUBAMPLITUDE;
}

void PrintForceRamps(void)
{
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 75;
   VGAPrintParam = ALWAYS;                   /* Print in right half-page */   
}

void VGAPresetWeldRate(void)
{
   switch(CurrentPreset.WeldFR)
   {
      case RATE_SLOWEST:
         Value = 0;
         break;

      case RATE_SLOW:
         Value = 1;
         break;
         
      case RATE_NORMAL:
         Value = 2;
         break;

      case RATE_FAST:
         Value = 3;
         break;

      case RATE_FASTEST:
         Value = 4;
         break;
   }
   ValueFlag = TRUE;
   Val_ID = 76;
   VGAPrintParam = ALWAYS;                   /* Print in right half-page */   
}

void VGAPresetStepRate(void)
{
	switch(CurrentPreset.StepFR)
   {
      case RATE_SLOWEST:
         Value = 0;
         break;

      case RATE_SLOW:
         Value = 1;
         break;
         
      case RATE_NORMAL:
         Value = 2;
         break;

      case RATE_FAST:
         Value = 3;
         break;

      case RATE_FASTEST:
         Value = 4;
         break;
   }
   ValueFlag = TRUE;
   Val_ID = 77;
   VGAPrintParam = ALWAYS;                   /* Print in right half-page */   
}


void VGAPresetHoldRate(void)
{
	switch(CurrentPreset.HoldFR)
   {
      case RATE_SLOWEST:
         Value = 0;
         break;

      case RATE_SLOW:
         Value = 1;
         break;
         
      case RATE_NORMAL:
         Value = 2;
         break;

      case RATE_FAST:
         Value = 3;
         break;

      case RATE_FASTEST:
         Value = 4;
         break;
   }
   ValueFlag = TRUE;
   Val_ID = 78;
   VGAPrintParam = ALWAYS;                   /* Print in right half-page */   
}




/**-----------------------------------------------**
 ** This function gets the time and date strings. **
 **-----------------------------------------------**/
void GetDateTime(void)
{
   RTC RTCPrinter;
   /* Get the current time and date from clock in BBRAM */
   RTCPrinter = RtcReadDateandTime();

   if(SummaryInfo.b_unit)
      SPrintf(datestr, "%02u/%02u/%02u", RTCPrinter.Day, RTCPrinter.Month, RTCPrinter.Year);
   else
      SPrintf(datestr,"%02u/%02u/%02u", RTCPrinter.Month, RTCPrinter.Day, RTCPrinter.Year);

   SPrintf(timestr,"%02u:%02u",RTCPrinter.Hour, RTCPrinter.Minute);
}
/**----------------------------------------------**
 ** This function displays the Scrub Amplitude.  **
 **----------------------------------------------**/
void PrintSetup0003A(void)
{
   FormatVariables(CurrentPreset.AmpScrubTime, MICRONS, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value =0;
   ValueFlag = FALSE;
   Val_ID = 15;
   VGAPrintParam = PSCRUBAMPLITUDE;
}
/**-----------------------------**
 **  Array Group 1 and Group 2  **
 **-----------------------------**/


/**------------------------------------------**
 ** This function  Checks an array structure **
 ** to see what parameters should print.     **
 **------------------------------------------**/
UINT16 CheckIfPrintable(UINT16 VarType)
{

   switch(CurrentSetup.ControlLevel)
   {
      case LEVEL_t:
         GetArrayValue = parameterControlLevel[VarType][INDEX_t];
         break;

      case LEVEL_e:
         GetArrayValue = parameterControlLevel[VarType][INDEX_e];
         break;

      case LEVEL_ea:
      case LEVEL_a:
         GetArrayValue = parameterControlLevel[VarType][INDEX_ea];
         break;

      case LEVEL_d:             
         GetArrayValue = parameterControlLevel[VarType][INDEX_d];
         break;

      case LEVEL_f:
         GetArrayValue = parameterControlLevel[VarType][INDEX_f];
         break;

      case LEVEL_TEST:
         GetArrayValue = AVAIL;
         break;

      default:
         GetArrayValue = parameterControlLevel[VarType][INDEX_t];
         break;
   }

   switch(GetArrayValue)
   {
      case ACTDF:   // Print if:  aed|aod|aef|aof|MICRO
         if ( (CurrentSetup.Actuator==AED) || (CurrentSetup.Actuator==AEF) ||
              (CurrentSetup.Actuator==AOD) || (CurrentSetup.Actuator==AOF) ||
              (CurrentSetup.Actuator==MICRO) )
            VarType = TRUE;
         else
            VarType = FALSE;
         break;
      case AVAIL:
         VarType = TRUE;
         break;
      case AVAILLE:
         if ( (CurrentSetup.Actuator==AED) ||
              (CurrentSetup.Actuator==AEF) ||
              (CurrentSetup.Actuator==MICRO) )
            VarType = TRUE;
         else
            VarType = FALSE;
         break;

     case NOTAVAIL:
          VarType = FALSE;
          break;

      case TMODONLY:
         if(CurrentPreset.WeldMode == TIMEMODE)
            VarType = TRUE;
         else
            VarType = FALSE;
         break;
      default :
         VarType = FALSE;
         break;
   }
   return(VarType);
}


  
/**---------------------------------------------**
 ** This function checks an array structure     **
 ** to see what Limits should print.            **
 ** Based on the controllevels, weldmodes and   **
 ** and the Limits. It then returns a selection **
 ** from the array table.                       **
 **---------------------------------------------**/
UINT16 ControlLevelLimit(UINT16 Limit)
{
   UINT16 ControlLevel = 1, Weldmode = 0;
   UINT16 RetVal = 0;

   // Must setup array index values to correspond to the Control Level tables
   // ControlLevels     0..9  -> 5 levels  0..4 -> Suspect, 5-9 -> Reject 
   // Weldmodes         0..6  -> 7 weldmodes
   // Limits            0..15 -> 16 limits
   
   
   /* First get Control Level index into the table */
   /* based on the if limit is reject or suspect   */
  switch(CurrentSetup.ControlLevel)
   {
      case LEVEL_t:
         ControlLevel = INDEX_t;
         break;

      case LEVEL_e:
         ControlLevel = INDEX_e;
         break;

      case LEVEL_ea:
         ControlLevel = INDEX_ea;
         break;

      case LEVEL_d:             
         ControlLevel = INDEX_d;
         break;

      case LEVEL_f:
         ControlLevel = INDEX_f;
         break;

      case LEVEL_TEST:
         ControlLevel = INDEX_f;
         break;

      default:
         ControlLevel = INDEX_t;
         break;
   }
   

   if(SusRejFlag != SUSACTIVE)
      ControlLevel += SUSREJDIFF;


   /* Next get the Weldmode index into the table */
   switch(CurrentPreset.WeldMode)
   {
      case TIMEMODE:
         Weldmode = TIMEMLIM;
         break;

      case ENERGYMODE:
         Weldmode = ENERGYMLIM;
         break;
         
      case PKPOWERMODE:
         Weldmode = PKPOWERMLIM;
         break;

      case COLLAPSEMODE:
         Weldmode = COLMLIM;
         break;

      case ABSOLUTEMODE:
         Weldmode = ABSMLIM;
         break;

      case GRDDETECTMODE:
         Weldmode = GRDDETMLIM;
         break;

      case CONTINUOUSMODE:
         Weldmode = CONTMLIM;
         break;

      default:
         Weldmode = TIMEMLIM;
         break;
   }

   /* Value is selected from the TABLE */
   GetArrayValue = controlLevel[ControlLevel][Limit][Weldmode];

   /* Should we print this string? */
   switch(GetArrayValue)
   {
      case ACTDF:        // Print if:  aed|aod|aef|aof|MICRO
         if ( (CurrentSetup.Actuator==AED) ||
              (CurrentSetup.Actuator==AEF) ||
              (CurrentSetup.Actuator==MICRO) )
            RetVal = TRUE;
         else
            RetVal = FALSE;
         break;
     
      case AVAIL:
         RetVal = TRUE;
         break;

      case AVAILLE:

         if ( (CurrentSetup.Actuator==AED) ||
              (CurrentSetup.Actuator==AEF) ||
              (CurrentSetup.Actuator==MICRO) )
            RetVal = TRUE;
         else
            RetVal = FALSE;
         break;

      case NOTAVAIL:

         RetVal = FALSE;
         break;

      case TMODONLY:
         if(CurrentPreset.WeldMode == TIMEMODE)
            RetVal = TRUE;
         else
            RetVal = FALSE;
         break;

      default:
         RetVal = FALSE;
         break;
   }
   return(RetVal);
}




void LastDatePresetWasSaved(void)
{
   RTC RTCPrinter;

   RTCPrinter = RtcReadDateandTime();
   CurrentPreset.Year = RTCPrinter.Year;
   CurrentPreset.Month = RTCPrinter.Month;
   CurrentPreset.Day = RTCPrinter.Day;
   CurrentPreset.Hour = RTCPrinter.Hour;
   CurrentPreset.Minute = RTCPrinter.Minute;
}


/**----------------------------------------------**
 ** This function displays the current weld mode.**
 **----------------------------------------------**/
UINT16 PrintSetup0002(void)
{
   UINT16 param;
   const SINT8  *str;

   switch(CurrentPreset.WeldMode)
   {
      case TIMEMODE:
         Value = 0;
         param = PWELDTIME;
         break;
         
      case ENERGYMODE:
         Value = 1;
         param = PENERGY;
         break;
         
      case PKPOWERMODE:
         Value = 2;
         param = PPEAKPOWER;
         break;
         
      case COLLAPSEMODE:
         Value = 3;
         param = PCOLDIST;
         break;
         
      case ABSOLUTEMODE:
         Value = 4;
         param = PABSDIST;
         break;
         
      case GRDDETECTMODE:
         Value = 5;
         param = PGROUNDDETECTCUTOFF;
         break;
         
      case CONTINUOUSMODE:
         Value = 6;
         param = PCONTINUOUS;
         break;
         
      default:
         Value = 0;
         param = PWELDTIME;
         break;   
   }
	ValueFlag = TRUE;
	Val_ID = 6;
   VGAPrintParam = param;
   return (param);
}


/**-----------------------------------------------**
 ** This function displays the current Hold Time. **
 **-----------------------------------------------**/
void PrintSetup0004(void)
{
  
  /* Hold Time */
  if((CurrentPreset.HoldTimeFlag & BIT0) == FALSE) {

    FormatVariables(CurrentPreset.HoldTime, TIME, VGAMisc, 6, CurrentSetup.Units);
    strcpy(VGABuffer, VGAMisc);
    Value = 0;
	 ValueFlag = FALSE;
	 Val_ID =33;
  }
  else
  {
     Value = 0;
	  ValueFlag = TRUE;
	  Val_ID =34;
  }
   VGAPrintParam = PHOLDTIME;
}

////////////////////////////////////////////////////////////////////////////
 //					FUNCTION TO CONVERT VALUE TO A STRING                    //
 ////////////////////////////////////////////////////////////////////////////

void ConvertNumberToString( SINT32 Value)
{
   SINT16 i,j;
   SINT32 Temp;
   SINT8 NumDisplayChar = DISPLAYCHAR;
   UINT16 StringEnd, neg= 0;
   StringEnd = PRINTSPACEPAGE;

   if(Value < 0){
      neg = 1;
      Value = (Value*(-1));
   }
   
   for(i=0; i < StringEnd; i++)
	   VGABuffer[i] = FILLCHAR;

   VGABuffer[StringEnd] = '\0';
   i = StringEnd - 1;
   if(Value > 0)
   {
	  while((NumDisplayChar > 0) && (Value != 0))
      {
         Temp = Value % 10;
         VGABuffer[i--] = Temp + '0';
         Value /= 10;
         NumDisplayChar--;
      }
      if(neg)
            VGABuffer[i] = '-';
   } 
   else
   {
         VGABuffer[StringEnd - 1] = '0';
   }

   j = 0;
   while(VGABuffer[j++] == FILLCHAR);
   j--;

   for(i=0; j<= StringEnd; i++)
   {
	   VGABuffer[i] = VGABuffer[j];
	   j++;
   }
   for(; i <= StringEnd; i++)
	   VGABuffer[i] = FILLCHAR;
}


/**------------------------------------------------**
 ** This function displays the current value based **
 ** on the weld mode.                              **
 **------------------------------------------------**/
UINT16 PrintSetup0003(void)
{
   UINT16 param = 0;

   switch(CurrentPreset.WeldMode)         
   { 
      case TIMEMODE:
         FormatVariables(CurrentPreset.WeldTime, TIME, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         param = PWELDTIME;
         Val_ID = 7;
         break;

      case ENERGYMODE:
         FormatVariables(CurrentPreset.WeldEnergy,
            /* cont'd */   CurrentPreset.WeldEnergy > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
            /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
         strcpy(VGABuffer, VGAMisc);
         param = PENERGY;
         Val_ID = 8;
         break;

      case PKPOWERMODE:
         FormatVariables(CurrentPreset.PeakPwr, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         param = PPEAKPOWER;
         Val_ID = 9;
         break;

      case COLLAPSEMODE:
         FormatVariables(CurrentPreset.ColDist, DISTANCE, VGAMisc, 6, CurrentSetup.Units );
         LangStrCpy(VGABuffer, VGAMisc);
         param = PCOLDIST;
         Val_ID = 10;
         break;

      case ABSOLUTEMODE:
         FormatVariables(CurrentPreset.AbsDist, DISTANCE, VGAMisc, 6, CurrentSetup.Units );
         strcpy(VGABuffer, VGAMisc);
         param = PABSDIST;
         Val_ID = 11;
         break;

      case GRDDETECTMODE:
         FormatVariables(CurrentPreset.ScrubTime, TIME, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         param = PSCRUBTIME;
         Val_ID = 12;
         break;

      case CONTINUOUSMODE:
         param = ALWAYS;
         Val_ID = 13;
         break;

      default:
         param = ALWAYS;
         Val_ID = 14;
         break;
   }
   Value =0;
   ValueFlag = FALSE;
   VGAPrintParam = param;
   return(param);
}


/**----------------------------------------**
 ** This function displays the Afterburst. **
 **----------------------------------------**/
void PrintSetup0022(void)
{
   Value = (UINT8)CurrentPreset.AbFlag;
   ValueFlag = TRUE;
   Val_ID = 35;
   VGAPrintParam = PAFTERBURST;
}

/**----------------------------------------**
 ** This function displays the Amplitude.  **
 **----------------------------------------**/
void PrintSetup0015(void)
{
   if(CurrentSetup.AmpControl == TRUE){

      /* BIT0 = FIXED, BIT2-BIT6 = STEP */
      if((CurrentPreset.Amp2Flag & BIT0) == TRUE) 
	  {
		  Value =CurrentSetup.AmpControl;
		  ValueFlag = TRUE;
		  Val_ID = 16;
	  }
      else   
	  {
    	  FormatVariables(CurrentPreset.Amp1, MICRONS, VGAMisc, 6, CurrentSetup.Units);
    	      	  	   strcpy(VGABuffer, VGAMisc);
    	  //ConvertNumberToString(CurrentPreset.Amp1);
        Value = 0;
		  ValueFlag = FALSE;
		  Val_ID = 287;
	  }
   }
   else
   {
	   Value = CurrentSetup.AmpControl;
	   ValueFlag = TRUE;
	   Val_ID = 16;
   }
   VGAPrintParam = PAMPLITUDEA;
}

/**----------------------------------------------**
 ** This function displays the Afterburst Delay. **
 **----------------------------------------------**/
void PrintSetup0023(void)
{
   FormatVariables(CurrentPreset.AbDelay, TIME, VGAMisc, 6, CurrentSetup.Units);
   LangStrCpy(VGABuffer, VGAMisc);
	ValueFlag = FALSE;
	Val_ID =36;
   VGAPrintParam = PAFTERBURSTDELAY;
}



/**-----------------------------------------**
 ** This function displays the Amplitude(A) **
 ** indented if the Amplitude is ON.        **
 **-----------------------------------------**/
void PrintSetup0016(void)
{
   if( ((CurrentPreset.Amp2Flag & BIT0) == TRUE) &&
       ((CurrentSetup.AmpControl& BIT0) == TRUE) ){   // Internal
	   FormatVariables(CurrentPreset.Amp1, MICRONS, VGAMisc, 6, CurrentSetup.Units);
	       	  	   strcpy(VGABuffer, VGAMisc);
	   //ConvertNumberToString(CurrentPreset.Amp1);
	   Value = 0;
	   ValueFlag = FALSE;
	   Val_ID = 17;
      VGAPrintParam = PAMPLITUDEA1;
       
   }
}

/**--------------------------------------------**
 ** This function displays the Afterburst time **
 ** indented if Afterburst is on.              **
 **--------------------------------------------**/
void PrintSetup0024(void)
{
   FormatVariables(CurrentPreset.AbTime, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
	ValueFlag = FALSE;
	Val_ID =37;
   VGAPrintParam = PAFTERBURSTTIME;
}


/**-----------------------------------------**
 ** This function displays the Amplitude(B) **
 ** indented if Amplitude Step is on.       **    
 **-----------------------------------------**/
void PrintSetup0017(void)
{
   if( ((CurrentPreset.Amp2Flag & BIT0)  == TRUE) &&
      ((CurrentSetup.AmpControl & BIT0) == TRUE) ){   // Internal
	   FormatVariables(CurrentPreset.Amp2, MICRONS, VGAMisc, 6, CurrentSetup.Units);
	       	  	   strcpy(VGABuffer, VGAMisc);
	   //ConvertNumberToString(CurrentPreset.Amp2);
	   Value = 0;
	   ValueFlag = FALSE;
	   Val_ID = 18;
      VGAPrintParam = PAMPLITUDEB;
   }
}



 /**-----------------------------------------**
 ** This function displays the Afterburst   **
 **  Amplitude indented if Afterburst is on.**
 **
-----------------------------------------**/
 void PrintSetup0025(void)
{
   if((CurrentSetup.AmpControl & BIT0) == TRUE){   // Internal
	   FormatVariables(CurrentPreset.AbAmp, MICRONS, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	   //ConvertNumberToString(CurrentPreset.AbAmp);
   Value = 0;
	ValueFlag = FALSE;
	Val_ID =38;
	VGAPrintParam = PAFTERBURSTAMP;
   }   
}



 /**---------------------------------------------**
 ** This function displays the Energy Braking   **
 ** state - On or Off                           **
 **---------------------------------------------**/
 void PrintSetup0025A(void)
{
   Value = (UINT8)CurrentPreset.EnergyBraking;
   ValueFlag = TRUE;
   Val_ID =39;
   VGAPrintParam = PENERGYBRAKING;                
}



/**-----------------------------------------------**
 ** This function displays the Amplitude Step  At.**
 **-----------------------------------------------**/
UINT16 PrintSetup0018A(void)
{
   UINT16 param = PAMPLITUDEA;

   if((CurrentSetup.AmpControl & BIT0) == TRUE) {   // Internal

      if((CurrentPreset.Amp2Flag & BIT0) == TRUE){
         /* Stepping enabled on time          */
         if((CurrentPreset.Amp2Flag & BIT2) == FALSE) {
            FormatVariables(CurrentPreset.AmpTrigTimeValue, TIME, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value =0;
		      ValueFlag = FALSE;
            Val_ID = 19;
         }
         /* Stepping enabled on energy        */
         else if((CurrentPreset.Amp2Flag & BIT3) == FALSE) {
            FormatVariables(CurrentPreset.AmpTrigEnerValue, 
                           CurrentPreset.AmpTrigEnerValue > ENERGYPOINT ? ENERGYDIV10 : ENERGY, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value =0;
		      ValueFlag = FALSE;
            Val_ID = 20;
         }
         /* Stepping enabled on peak power    */
         else if((CurrentPreset.Amp2Flag & BIT4) == FALSE) { 
            FormatVariables(CurrentPreset.AmpTrigPowerValue, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value =0;
		      ValueFlag = FALSE;
            Val_ID = 21;
         }
         /* Stepping enabled on collapse dist */
         else if((CurrentPreset.Amp2Flag & BIT5) == FALSE) {
            FormatVariables(CurrentPreset.AmpTrigColValue,DISTANCE,VGAMisc,6,CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value =0;
		      ValueFlag = FALSE;
            Val_ID = 22;
         }
         /* Stepping enabled on force */
         else if((CurrentPreset.Amp2Flag & BIT6) == FALSE) {
            FormatVariables(CurrentPreset.AmpTrigForceValue, FORCE, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value =0;
		      ValueFlag = FALSE;
            Val_ID = 23;
         }
         /* Stepping enabled on External Signal */
         else if((CurrentPreset.Amp2Flag & BIT7) == FALSE) {
		      Value =0;
            ValueFlag = TRUE;
            Val_ID = 24;
         }
         else {
            Value =0;
		      ValueFlag = TRUE;
            Val_ID = 25;
         }
         VGAPrintParam = param;
      }
   }   
   return (param);
}

/**--------------------------------------------**
 ** This function displays the Post Weld Seek. **
 **-------------------------------------------**/
void PrintSetup0026(void)
{
   Value = (UINT8)(CurrentPreset.SeekFunFlag & BIT0);
    ValueFlag = TRUE;
    Val_ID =40;
    VGAPrintParam = PPOSTWELDSEEK;
}



/**---------------------------------------------**
 ** This function displays the Pretrigger flag. **
 **---------------------------------------------**/
void PrintSetup0019(void)
{
   Value = (UINT8)CurrentPreset.PreTrigFlag;
	ValueFlag = TRUE;
	Val_ID = 26;
	VGAPrintParam = PPRETRIGGER;
}

/**----------------------------------------------**
 ** This function displays the Frequency Offset. **
 **----------------------------------------------**/
void PrintSetup0027(void)
{
   if(CurrentSetup.FreqControl == TRUE){
      if((CurrentPreset.FreqOffsetFlag & BIT0) == BIT0)
	  {
       ConvertNumberToString(CurrentPreset.FreqOffset);
		 Value =0;
		 ValueFlag = FALSE;
		 Val_ID =288;
	  }
      else 
	  {
		  Value =0;
		  ValueFlag = TRUE;
		  Val_ID = 41;
	  }
   }
   else{
	  Value = 1;
	  ValueFlag = TRUE;
	  Val_ID = 41;

   }
   VGAPrintParam = PFREQCONTROL;
}



/**-------------------------------------------------**
 ** This function displays the Pretrigger mode.     **
 **-------------------------------------------------**/
void PrintSetup0019B(void)
{
   if (CurrentPreset.PreTrigFlag == FALSE)             // Pretrigger off
   {
	  Value = 0;
     Val_ID = 289;
   }
   else if (CurrentPreset.PreTrigDistFlag == FALSE)    // Pretrigger on distance
   {
	  Value = 0;
     Val_ID = 27;
   }
   else if (CurrentPreset.PreTrigDelayFlag == FALSE)   // Pretrigger on delay
   {
	  Value = 1;
     Val_ID = 27;
   }
   else                                                // None of the above, auto
   {
	  Value = 2;
     Val_ID = 27;
   }
   ValueFlag = TRUE;
   
   VGAPrintParam = PAUTOPRETRIGGER;
}

/**----------------------------------------**
 ** This function displays the Max Timeout **
 **----------------------------------------**/
void PrintSetup0070(void){
   if((CurrentPreset.WeldMode==GRDDETECTMODE) ||   
       (((CurrentPreset.WeldMode==ENERGYMODE)||
         (CurrentPreset.WeldMode==COLLAPSEMODE))&&
         (CurrentSetup.ControlLevel>=LEVEL_e))||
       
       (((CurrentPreset.WeldMode==PKPOWERMODE)||
         (CurrentPreset.WeldMode==ABSOLUTEMODE))&&
         (CurrentSetup.ControlLevel>=LEVEL_ea))){
      FormatVariables(CurrentPreset.MaxTimeout, TIME, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
	   Value = 0;
	   ValueFlag = FALSE;
	   Val_ID = 31;
      VGAPrintParam = PMAXTIMEOUT;
   }
}



/**----------------------------------------**
 ** This function displays the External    **
 ** Trigger Delay - on or off              **
 **----------------------------------------**/
void PrintSetup0070A(void)
{
   Value = (UINT8)(CurrentPreset.ExtTrgDelay);
   ValueFlag = TRUE;
   Val_ID =32;
   VGAPrintParam = PEXTTRIGDLY;
}



/**--------------------------------------------**
 ** This function displays the Digital Tune    **
 **--------------------------------------------**/
void PrintConfig0081(void)
{
   UINT32 DigPotVal;

   DigPotVal = GetPowerSupplyFrequency();

   switch (CurrentSetup.PSFreq)
   {
      case FREQ15KHZ:
         DigPotVal += CurrentSetup.DigPot/8;
         break;
      case FREQ20KHZ:
         DigPotVal += CurrentSetup.DigPot/6;
         break;
      case FREQ30KHZ:
         DigPotVal += CurrentSetup.DigPot/4;
         break;
      case FREQ60KHZ:
         DigPotVal += CurrentSetup.DigPot/2;
         break;
      case FREQ40KHZ:
      default:
         DigPotVal += CurrentSetup.DigPot/2;
         break;
   }

   if(CurrentSetup.DigPotFlag == TRUE)
   {
      ConvertNumberToString(DigPotVal);
		Value = 2;
      ValueFlag = FALSE;
      Val_ID = 42;
   }
   else
   {
	   Value = (UINT8)CurrentSetup.DigPotFlag;
      ValueFlag = TRUE;
      Val_ID = 42;
   }
   VGAPrintParam = DIGITALTUNE;   
}




/**--------------------------------------------------------**
 ** This function displays the Pretrigger At Distance/Time **
 **--------------------------------------------------------**/
void PrintSetup0019A(void)
{
   if (CurrentPreset.PreTrigFlag == TRUE)
   {
      if((CurrentPreset.PreTrigDistFlag & BIT0) == FALSE) {
         FormatVariables(CurrentPreset.PreTrigDist, DISTANCE, VGAMisc, 6, CurrentSetup.Units );
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = 28;
      }
      else if((CurrentPreset.PreTrigDelayFlag & BIT0) == FALSE) {
         FormatVariables(CurrentPreset.PreTrigDelay, TIME, VGAMisc, 6, CurrentSetup.Units );
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = 29;
      }
   }
   VGAPrintParam = PPRETRIGGERDISTANCE;   
}


/**--------------------------------------------**
 ** This function displays the Test Amplitude. **
 **--------------------------------------------**/
void PrintSetup0067(void)
{
	   FormatVariables(CurrentPreset.TestAmp, MICRONS, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	//ConvertNumberToString(CurrentPreset.TestAmp);
   Value = 0;
	ValueFlag = FALSE;
	Val_ID = 43;
	VGAPrintParam = PTESTAMPLITUDE;
}

/**--------------------------------------------------**
 ** This function displays the Pretrigger Amplitude. **
 **--------------------------------------------------**/
void PrintSetup0021(void)
{
   if(((CurrentSetup.AmpControl & BIT0) == TRUE) &&
      ((CurrentPreset.PreTrigFlag & BIT0) == TRUE))
   {   // Internal
	   FormatVariables(CurrentPreset.PreTrigAmp, MICRONS, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	   //ConvertNumberToString(CurrentPreset.PreTrigAmp);
      Value = 0;
	   ValueFlag = FALSE;
	   Val_ID = 30;
	   VGAPrintParam = PPRETRIGGERAMP;
   }
}

/**-------------------------------------------**
 ** This function displays the Rapid Traverse **
 **-------------------------------------------**/
void PrintSetup0012(void)
{
   Value = (UINT8)CurrentPreset.RTFlag;
   ValueFlag = TRUE;
   Val_ID = 64;
   VGAPrintParam = PRAPIDTRAVS;
}

/**---------------------------------------------**
 ** This function displays the R/T At Distance. **
 **---------------------------------------------**/
void PrintSetup0013(void)
{
   FormatVariables(CurrentPreset.RTDist, DISTANCE, VGAMisc, 6, CurrentSetup.Units );
   strcpy(VGABuffer, VGAMisc);
   Value = 0 ;
   ValueFlag = FALSE;
   Val_ID = 65;
   VGAPrintParam = PRAPIDTRAVS;
}

/**---------------------------------------------------**
 ** This function displays the Actuator Clear Output. **
 **---------------------------------------------------**/
void PrintConfig0033(void)
{
   Value = (UINT8)(CurrentPreset.ActClrFlag & BIT0); 
   ValueFlag = TRUE;
   Val_ID = 44;
	VGAPrintParam = PACTCLEAROUTPUT;
}

/**--------------------------------------**
 ** This function displays the Distance. **
 **--------------------------------------**/
void PrintConfig0033A(void)
{
   if (CurrentSetup.HandHeld == FALSE) {
      FormatVariables(CurrentPreset.ActClrDistance, DISTANCE, VGAMisc, 6, CurrentSetup.Units );
	  strcpy(VGABuffer, VGAMisc);
     Value = 0;
	  ValueFlag = FALSE;
	  Val_ID = 45;
      VGAPrintParam = PACTCLEARDISTANCE;
   }
   else 
   {
      RightPrintYCoordinate = RightPrintYCoordinate + PRINT_LINE_HEIGHT;
   }   
} 

/**----------------------------------------------**
 ** This function displays the Cycle Abort Flag. **
 **----------------------------------------------**/
void PrintSetup0071(void){                                          // ae
  
   if(!((CurrentPreset.WeldMode==GRDDETECTMODE)&&(CurrentSetup.Actuator == AE))){
      Value = (UINT8)CurrentPreset.CycleAbortFlag;
      ValueFlag = TRUE;
      Val_ID = 46;
      RightPrintYCoordinate = RightPrintYCoordinate + PRINT_LINE_HEIGHT;  /* leave right half-page blank */
      VGAPrintParam = PCYCLEABORTS;
   }
}

/**------------------------------------------------------**
 ** This function displays the Ground Detect Abort Flag. **
 **------------------------------------------------------**/
void PrintSetup0033(void)
{
   if(CurrentPreset.WeldMode != GRDDETECTMODE){
      Value = (UINT8)CurrentPreset.GndDetectFlag;
      ValueFlag = TRUE;
      Val_ID = 47;
      VGAPrintParam = PSCRUBTIME;
   }
}

/**-----------------------------------------------**
 ** This function displays the Missing Part Flag. **
 **-----------------------------------------------**/
void PrintConfig0071(void)
{
   Value = (UINT8)CurrentPreset.MissingPartFlag;
   ValueFlag = TRUE;
   Val_ID = 48;
   VGAPrintParam = PMISSINGPARTFLAG;
}

/**---------------------------------------------------**
 ** This function displays the Missing Part Abort Max **
 **---------------------------------------------------**/
void PrintConfig0073(void)
{
   if(CurrentPreset.MissingMaxFlag)
   {
	  Value = 0;
     ValueFlag = TRUE;
	  Val_ID = 51;
   }
   else
   {
     FormatVariables(CurrentPreset.MissingPartMax, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
	  ValueFlag = FALSE;
	  Val_ID = 52;
   }
   VGAPrintParam = PMISSINGPARTMAX; 
}

/**---------------------------------------------------**
 ** This function displays the Missing Part Abort Min **
 **---------------------------------------------------**/
void PrintConfig0072(void)
{
   if(CurrentPreset.MissingMinFlag)
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 49;
   }
   else
   {
      FormatVariables(CurrentPreset.MissingPartMin, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 50;
   }   
   VGAPrintParam = PMISSINGPARTMIN;
}

/**--------------------------------------------**
 ** This function displays the Control Limits. **
 **--------------------------------------------**/
void PrintSetup0028(void)
{                                       // ae   
   if(!((CurrentPreset.WeldMode==PKPOWERMODE) && (CurrentSetup.Actuator== AE)))
   {    
      Value = (UINT8)(CurrentPreset.ControlLimitsFlag & BIT0);
      ValueFlag = TRUE;
	   Val_ID = 53;
	   VGAPrintParam = PCONTROLLIMITS;
      RightPrintYCoordinate = RightPrintYCoordinate + PRINT_LINE_HEIGHT;  /* leave right half-page blank */
   }
}

/**---------------------------------------------**
 ** This function displays the Collapse Cutoff. **
 **---------------------------------------------**/
void PrintSetup0034B(void){
   if ( (CurrentSetup.Actuator==AED) ||
        (CurrentSetup.Actuator==AEF) ||
        (CurrentSetup.Actuator==MICRO) )
   {
      if(CurrentPreset.WeldMode != COLLAPSEMODE)
      {
        if(CurrentPreset.ColCutoffFlag)
		{
            Value = 0 ;
            ValueFlag = TRUE;
            Val_ID = 54;
		}
        else
		{
            FormatVariables(CurrentPreset.ColCutoffDist, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = 55;
		}
      }
      VGAPrintParam = PCOLLAPSECUTOFF;
   }
}

/**-------------------------------------------------**
 ** This function displays the Energy Compensation. **
 **-------------------------------------------------**/
void PrintSetup0029(void)
{
   if(CurrentPreset.WeldMode != PKPOWERMODE)
   { // until 2.5
      if(CurrentPreset.WeldMode == TIMEMODE)
      {
         Value = (UINT8)(CurrentPreset.EnergyCompFlag & BIT0);
         ValueFlag = TRUE;
         Val_ID = 60;
         VGAPrintParam = PENERGYCOMP;
      }
   }
}

/**---------------------------------------------**
 ** This function displays the Absolute Cutoff. **
 **---------------------------------------------**/
void PrintSetup0034A(void){
   if ( (CurrentSetup.Actuator==AED) ||
        (CurrentSetup.Actuator==AEF) ||
        (CurrentSetup.Actuator==MICRO) )
   {
      if(CurrentPreset.WeldMode != ABSOLUTEMODE)
      {
         if(CurrentPreset.ABSCutoffFlag)
		 {
            Value = 0 ;
            ValueFlag = TRUE;
            Val_ID = 56;
		 }
         else
         {
            FormatVariables(CurrentPreset.ABSCutoffDist, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0 ;
            ValueFlag = FALSE;
            Val_ID = 57;
         }
         VGAPrintParam = PABSOLUTECUTOFF;
      }
   }
}

void PrintSetup0031(void)
{
   if(CurrentPreset.WeldMode != PKPOWERMODE)
   {
      if(CurrentPreset.WeldMode == TIMEMODE)
      {
         FormatVariables(CurrentPreset.EnergyPL,
            /* cont'd */   CurrentPreset.EnergyPL > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
            /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
         strcpy(VGABuffer, VGAMisc);
         Value = 0 ;
         ValueFlag = FALSE;
         Val_ID = 61;
         VGAPrintParam = PENERGYMAX;
      }
   }
} 

/**-----------------------------------------------**
 ** This function displays the Peak Power Cutoff. **
 **-----------------------------------------------**/
void PrintSetup0032(void)
{
   if(CurrentPreset.WeldMode != PKPOWERMODE)
   {
      if(CurrentPreset.PeakPwrCutoffFlag)  /* FALSE = on */
	  {
         Value = 0 ;
         ValueFlag = TRUE;
         Val_ID = 58;
	  }
      else
      {
         FormatVariables(CurrentPreset.PeakPwrCutoff, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0 ;
         ValueFlag = FALSE;
         Val_ID = 59;
      }
      VGAPrintParam = PPKPOWERCUTOFF;
   }
}

/**----------------------------------------**
 ** This function displays the Min Energy. **
 **----------------------------------------**/
void PrintSetup0030(void)
{
   if(CurrentPreset.WeldMode != PKPOWERMODE)
   {
      if(CurrentPreset.WeldMode == TIMEMODE)
      {
         FormatVariables(CurrentPreset.EnergyML,
            /* cont'd */   CurrentPreset.EnergyML > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
            /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
         strcpy(VGABuffer, VGAMisc);
         Value = 0 ;
         ValueFlag = FALSE;
         Val_ID = 62;
         VGAPrintParam = PENGERGYMIN;
      }
   }
}

/**--------------------------------------------------**
 ** This function displays the aef Settings message. **
 **--------------------------------------------------**/
void PrintAEFSetting(void)
{
   
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 63;
   VGAPrintParam = ALWAYS;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
}

/**-------------------------------------------**
 ** This function displays the Trigger Force. **
 **-------------------------------------------**/
void PrintSetup0005(void)
{
   FormatVariables(CurrentPreset.TriggerForce, FORCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 67;
   VGAPrintParam = PTRIGGERFORCE;
}

/**---------------------------------------**
 ** This function displays the Downspeed. **
 **---------------------------------------**/
void PrintSetup0014(void)
{
   ConvertNumberToString(CurrentPreset.DownSpdStart);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 66;
   VGAPrintParam = PDOWNSPEED;
}

/**-------------------------------------------**
 ** This function displays the Trigger Delay. **
 **-------------------------------------------**/
void PrintSetup0006(void)
{
   if((CurrentPreset.TriggerDelayFlag & /*TriggerDelay.BitMask*/BIT0) == FALSE) {
      FormatVariables(CurrentPreset.TriggerDelay, TIME, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0 ;
      ValueFlag = FALSE;
      Val_ID = PKPOWERCUTOFF_VAL_TXT;
   }
   else
   {
      Value = 0 ;
      ValueFlag = TRUE;
      Val_ID = PKPOWERCUTOFF_TXT;
   }

   VGAPrintParam = PTRIGGERDELAY;
}

/**----------------------------------------**
 ** This function displays the Hold Force. **
 **----------------------------------------**/
void PrintSetup0011(void)
{
   FormatVariables(CurrentPreset.HoldForce, FORCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 73;
   VGAPrintParam = PHOLDFORCE;
}

/**---------------------------------------**
 ** This function displays the Weld Force.**
 **---------------------------------------**/
void PrintSetup0007(void)
{
   if((CurrentPreset.Force2Flag & BIT0) == TRUE) 
   {
      Value = (UINT8)(CurrentPreset.Force2Flag & BIT0);
      ValueFlag = TRUE;
      Val_ID = 68;
   }
   else
   {
      FormatVariables(CurrentPreset.WeldForce, FORCE, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 69;
   }
   VGAPrintParam = PWELDFORCEA;
}

/**------------------------------------------**
 ** This function displays the Weld Force(A).**
 **------------------------------------------**/
void PrintSetup0008(void)
{
   if((CurrentPreset.Force2Flag & BIT0) == TRUE){ 

      FormatVariables(CurrentPreset.WeldForce, FORCE, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 70;

      VGAPrintParam = PWELDFORCEA1;
   }
}


/**------------------------------------------**
 ** This function displays the Weld Force(B).**
 **------------------------------------------**/
void PrintSetup0009(void)
{
   if((CurrentPreset.Force2Flag & BIT0) == TRUE) {

      FormatVariables(CurrentPreset.Force2, FORCE, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 71;

      VGAPrintParam = PWELDFORCEB;
   }
}

/**--------------------------------**
 ** This function displays Step At **
 **--------------------------------**/
UINT16 PrintSetup0018B(void)
{
   UINT16 param = ALWAYS;

   if((CurrentPreset.Force2Flag & BIT0) == TRUE) {
      /* Stepping enabled on time          */
      if((CurrentPreset.Force2Flag & BIT2) == FALSE) {
         FormatVariables(CurrentPreset.ForceTrigTimeValue, TIME, VGAMisc, 6, CurrentSetup.Units);
          strcpy(VGABuffer, VGAMisc);
          Value = 0;
          ValueFlag = FALSE;
          Val_ID = 19;
      }
      /* Stepping enabled on energy        */
      else
      if((CurrentPreset.Force2Flag & BIT3) == FALSE) {
         FormatVariables(CurrentPreset.ForceTrigEnerValue,
                        CurrentPreset.ForceTrigEnerValue > ENERGYPOINT ? ENERGYDIV10 : ENERGY, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = 20;
      }
      /* Stepping enabled on peak power    */
      else
      if((CurrentPreset.Force2Flag & BIT4) == FALSE) { 
         FormatVariables(CurrentPreset.ForceTrigPowerValue, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = 21;
      }
      /* Stepping enabled on collapse dist */
      else
      if((CurrentPreset.Force2Flag & BIT5) == FALSE) {
         FormatVariables(CurrentPreset.ForceTrigColValue, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = 22;
      }
      /* Stepping enabled on force */
      else if((CurrentPreset.Force2Flag & BIT6) == FALSE) {
         FormatVariables(CurrentPreset.ForceTrigAmpValue, MICRONS, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = 23;
      }
      /* Stepping enabled on external signal */
      else
      if((CurrentPreset.Force2Flag & BIT7) == FALSE) {
         Value = 1;
         ValueFlag = TRUE;
         Val_ID = 24;
      }
      else {
         Value = 0;
         ValueFlag = TRUE;
         Val_ID = 25;
      }
      VGAPrintParam = param;
   }
   return (param);
}

void PrintAEDTrigForce(void)
{
   FormatVariables(CurrentPreset.TriggerForce, FORCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 82;
   VGAPrintParam = ALWAYS;
}

/**----------------------------------------------------**
 ** This function displays the System (gauge) Pressure.**
 **----------------------------------------------------**/
void PrintSystemGaugePressure(void)
{
   FormatVariables(CurrentPreset.GaugePressure, PRESSURE, VGAMisc, 6, CurrentSetup.Units );
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 87;
   VGAPrintParam = ALWAYS; 
}

/**------------------------------------------**
 ** This function displays the Reject Limits.**
 **------------------------------------------**/
void PrintSetup0051(void)
{
   Value = (UINT8)(CurrentPreset.RejectLimitsFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = 103;
   VGAPrintParam = PREJECTLIMITS;
}

/**-------------------------------------------**
 ** This function displays the Suspect Limits.**
 **-------------------------------------------**/
void PrintSetup0035(void)
{
    Value = (UINT8)(CurrentPreset.SuspectLimitsFlag & BIT0);   
    ValueFlag = TRUE;
    Val_ID = 105;
    VGAPrintParam = PSUSPECTLIMITS;
}

/**--------------------------------------------------**
 ** This function displays the Reject Reset Required.**
 **--------------------------------------------------**/
void PrintSetup0052(void)
{
   Value = (UINT8)(CurrentPreset.RejResetRequiredFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = 104;
   VGAPrintParam = PREJRESETREQ;
}

/**---------------------------------------------------**
 ** This function displays the Suspect Reset Required.**
 **---------------------------------------------------**/
void PrintSetup0036(void)
{
    Value = (UINT8)(CurrentPreset.SusResetRequired & BIT0);
    ValueFlag = TRUE;
    Val_ID = 106;
    VGAPrintParam = PSUSPRESETREQ;
}

/**-----------------------------------------------**
 ** This function displays the + Collapse R Limit.**
 **-----------------------------------------------**/
void PrintSetup0059(void)
{
   if((CurrentPreset.RejectLimits & PCOLDISTBIT) != PCOLDISTBIT) { 
      FormatVariables(CurrentPreset.ColPLR, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 107;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 108;
   }
   VGAPrintParam = LCOLLAPSEPLUS;

}

/**-----------------------------------------------**
 ** This function displays the + Collapse S Limit.**
 **-----------------------------------------------**/
void PrintSetup0043(void)
{
   if((CurrentPreset.SuspectLimits & PCOLDISTBIT) != PCOLDISTBIT)
   {
     FormatVariables(CurrentPreset.ColPLS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
     ValueFlag = FALSE;
     Val_ID = 143;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 144;
   }

   VGAPrintParam = LCOLLAPSEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the - Collapse R Limit.**
 **-----------------------------------------------**/
void PrintSetup0060(void)
{
   if((CurrentPreset.RejectLimits & MCOLDISTBIT) != MCOLDISTBIT)
   {
      FormatVariables(CurrentPreset.ColMLR, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 109;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 110;
   }
   VGAPrintParam = LCOLLAPSEMINUS;
}

/**-----------------------------------------------**
 ** This function displays the - Collapse S Limit.**
 **-----------------------------------------------**/
void PrintSetup0044(void)
{
   if((CurrentPreset.SuspectLimits & MCOLDISTBIT) != MCOLDISTBIT)
   {
      FormatVariables(CurrentPreset.ColMLS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 145;
   }
   else
      
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 146;
   }

   VGAPrintParam = LCOLLAPSEMINUS;
}
  
/**---------------------------------------------**
 ** This function displays the + Energy R Limit.**
 **---------------------------------------------**/
void PrintSetup0055(void)
{
   if((CurrentPreset.RejectLimits & PENERGYBIT) != PENERGYBIT)
   {
      FormatVariables(CurrentPreset.EnergyPLR,
         /* cont'd */   CurrentPreset.EnergyPLR > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
         /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 111;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 112;
   }
   VGAPrintParam = LENERGYPLUS;

}

/**---------------------------------------------**
 ** This function displays the + Energy S Limit.**
 **---------------------------------------------**/
void PrintSetup0039(void)
{
   if((CurrentPreset.SuspectLimits & PENERGYBIT) != PENERGYBIT)
   {
      FormatVariables(CurrentPreset.EnergyPLS,
         /* cont'd */   CurrentPreset.EnergyPLS > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
         /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
		 strcpy(VGABuffer, VGAMisc);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 147;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 148;
   }

   VGAPrintParam = LENERGYPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Energy R Limit.**
 **---------------------------------------------**/
void PrintSetup0056(void)
{
   if((CurrentPreset.RejectLimits & MENERGYBIT) != MENERGYBIT)
   {
      FormatVariables(CurrentPreset.EnergyMLR,
         /* cont'd */   CurrentPreset.EnergyMLR > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
         /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 113;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 114;
   }
   VGAPrintParam = LENERGYMINUS;
}

/**---------------------------------------------**
 ** This function displays the - Energy S Limit.**
 **---------------------------------------------**/
void PrintSetup0040(void)
{
   if((CurrentPreset.SuspectLimits & MENERGYBIT) != MENERGYBIT)
   {
      FormatVariables(CurrentPreset.EnergyMLS,
         /* cont'd */   CurrentPreset.EnergyMLS > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
         /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
		 strcpy(VGABuffer, VGAMisc);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 149;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 150;
   }
   VGAPrintParam = LENERGYMINUS;
}

/**-----------------------------------------------**
 ** This function displays the + Absolute R Limit.**
 **-----------------------------------------------**/
void PrintSetup0061(void)
{
   if((CurrentPreset.RejectLimits & PABSDISTBIT) != PABSDISTBIT)
   { 
      FormatVariables(CurrentPreset.AbsPLR, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 115;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 116;
   }

   VGAPrintParam = LABSOLUTEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the + Absolute S Limit.**
 **-----------------------------------------------**/
void PrintSetup0045(void)
{
   if((CurrentPreset.SuspectLimits & PABSDISTBIT) != PABSDISTBIT)
   {
      FormatVariables(CurrentPreset.AbsPLS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 151;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 152;
   }

   VGAPrintParam = LABSOLUTEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the - Absolute R Limit.**
 **-----------------------------------------------**/
void PrintSetup0062(void)
{
   if((CurrentPreset.RejectLimits & MABSDISTBIT) != MABSDISTBIT)
   {
      FormatVariables(CurrentPreset.AbsMLR, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 117;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 118;
   }
   VGAPrintParam = LABSOLUTEMINUS;
}

/**-----------------------------------------------**
 ** This function displays the - Absolute S Limit.**
 **-----------------------------------------------**/
void PrintSetup0046(void)
{
   if((CurrentPreset.SuspectLimits & MABSDISTBIT) != MABSDISTBIT)
   { 
      FormatVariables(CurrentPreset.AbsMLS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 153;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 154;
   }

   VGAPrintParam = LABSOLUTEMINUS;
}

/**---------------------------------------------**
 ** This function displays the + Power  R Limit.**
 **---------------------------------------------**/
void PrintSetup0057(void)
{
   if((CurrentPreset.RejectLimits & PPKPOWERBIT) != PPKPOWERBIT)
   {
      FormatVariables(CurrentPreset.PowerPLR, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 119;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 120;
   }

   VGAPrintParam = LPOWERPLUS;
}


/**---------------------------------------------**
 ** This function displays the + Power  S Limit.**
 **---------------------------------------------**/
void PrintSetup0041(void)
{
   if((CurrentPreset.SuspectLimits & PPKPOWERBIT) != PPKPOWERBIT)
   {
      FormatVariables(CurrentPreset.PowerPLS, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 155;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 156;
   }

   VGAPrintParam = LPOWERPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Power  R Limit.**
 **---------------------------------------------**/
void PrintSetup0058(void)
{
    if((CurrentPreset.RejectLimits & MPKPOWERBIT) != MPKPOWERBIT)
   {
      FormatVariables(CurrentPreset.PowerMLR, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 121;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 122;
   }

   VGAPrintParam = LPOWERMINUS;
}

/**---------------------------------------------**
 ** This function displays the - Power  S Limit.**
 **---------------------------------------------**/
void PrintSetup0042(void)
{
    if((CurrentPreset.SuspectLimits & MPKPOWERBIT) != MPKPOWERBIT)
   {
      FormatVariables(CurrentPreset.PowerMLS, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 157;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 158;
   }

   VGAPrintParam = LPOWERMINUS;
}

/**---------------------------------------------**
 ** This function displays the + Time   R Limit.**
 **---------------------------------------------**/
void PrintSetup0053(void)
{
   if((CurrentPreset.RejectLimits & PTIMEBIT) != PTIMEBIT)
   {
      FormatVariables(CurrentPreset.TimePLR, TIME, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 123;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 124;
   }

   VGAPrintParam = LTIMEPLUS;
}

/**---------------------------------------------**
 ** This function displays the + Time   S Limit.**
 **---------------------------------------------**/
void PrintSetup0037(void)
{
   if((CurrentPreset.SuspectLimits & PTIMEBIT) != PTIMEBIT)
   {
      FormatVariables(CurrentPreset.TimePLS, TIME, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 159;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 160;
   }

   VGAPrintParam = LTIMEPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Time   R Limit.**
 **---------------------------------------------**/
void PrintSetup0054(void)
{
   if((CurrentPreset.RejectLimits & MTIMEBIT) != MTIMEBIT)
   {
      FormatVariables(CurrentPreset.TimeMLR, TIME, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 125;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 126;
   }

   VGAPrintParam = LTIMEMINUS;
}

/**---------------------------------------------**
 ** This function displays the - Time   S Limit.**
 **---------------------------------------------**/
void PrintSetup0038(void)
{
   if((CurrentPreset.SuspectLimits & MTIMEBIT) != MTIMEBIT)
   { 
      FormatVariables(CurrentPreset.TimeMLS, TIME, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 161;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 162;
   }

   VGAPrintParam = LTIMEMINUS;
}

/**-------------------------------------------------**
 ** This function displays the + Weld Force R Limit.**
 **-------------------------------------------------**/
void PrintSetup0065(void)
{
   if((CurrentPreset.RejectLimits & PFORCEBIT) != PFORCEBIT)
   {
      FormatVariables(CurrentPreset.WeldForcePLR, FORCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 127;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 128;
   }

   VGAPrintParam = LRMAXFORCE;  // LCOLLAPSEPLUS the same group
}

/**-------------------------------------------------**
 ** This function displays the + Weld Force S Limit.**
 **-------------------------------------------------**/
void PrintSetup0049(void)
{
   if((CurrentPreset.SuspectLimits & PFORCEBIT) != PFORCEBIT)
   {
      FormatVariables(CurrentPreset.WeldForcePLS, FORCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 163;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 164;
   }
   VGAPrintParam = LMAXFORCEPLUS;
}

/**-------------------------------------------------**
 ** This function displays the - Weld Force R Limit.**
 **-------------------------------------------------**/
void PrintSetup0066(void)
{
   if((CurrentPreset.RejectLimits & MFORCEBIT) != MFORCEBIT)
   {
      FormatVariables(CurrentPreset.WeldForceMLR, FORCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 129;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 130;
   }

   VGAPrintParam = LRMAXFORCE;
}

/**-------------------------------------------------**
 ** This function displays the - Weld Force S Limit.**
 **-------------------------------------------------**/
void PrintSetup0050(void)
{
   if((CurrentPreset.SuspectLimits & MFORCEBIT) != MFORCEBIT)
   {
      FormatVariables(CurrentPreset.WeldForceMLS, FORCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 165;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 166;
   }
      
   VGAPrintParam = LMAXFORCEMINUS;
}
/**-------------------------------------------------------**
 ** This function displays the + Trigger Distance R Limit.**
 **-------------------------------------------------------**/
void PrintSetup0063(void)
{
   if((CurrentPreset.RejectLimits & PTRIGDISTBIT) != PTRIGDISTBIT)
   { 
      FormatVariables(CurrentPreset.TrsDistPLR, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 131;
  }
   else 
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 132;
   }

   VGAPrintParam = LTRIGGERDISTPLUS;
}

/**-------------------------------------------------------**
 ** This function displays the + Trigger Distance S Limit.**
 **-------------------------------------------------------**/
void PrintSetup0047(void)
{
   if((CurrentPreset.SuspectLimits & PTRIGDISTBIT) != PTRIGDISTBIT)
   { 
      FormatVariables(CurrentPreset.TrsDistPLS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 167;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 168;
   }

   VGAPrintParam = LTRIGGERDISTPLUS;
}

/**-------------------------------------------------------**
 ** This function displays the - Trigger Distance R Limit.**
 **-------------------------------------------------------**/
void PrintSetup0064(void)
{
   if((CurrentPreset.RejectLimits & MTRIGDISTBIT) != MTRIGDISTBIT)
   { 
      FormatVariables(CurrentPreset.TrsDistMLR, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 133;
   }
   else 
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 134;
   }

   VGAPrintParam = LTRIGGERDISTMINUS;
}

/**-------------------------------------------------------**
 ** This function displays the + Power Band R Limit.**
 **-------------------------------------------------------**/
void PrintSetup0081(void)
{
   if(!CurrentPreset.PMCPlusBandFlag)
   {
      ConvertNumberToString(CurrentPreset.PMCHighLimit);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 135;
   }
   else 
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 136;
   }
   VGAPrintParam = ALWAYS;
}

/**-------------------------------------------------------**
 ** This function displays the - Power Band R Limit.**
 **-------------------------------------------------------**/
void PrintSetup0082(void)
{
   if(!CurrentPreset.PMCMinusBandFlag)
   {
      ConvertNumberToString(CurrentPreset.PMCLowLimit);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 137;
   }
   else 
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 138;
   }

   VGAPrintParam = ALWAYS;
}

/**-------------------------------------------------------**
 ** This function displays the + R SBL Frequency Limit.   **
 **-------------------------------------------------------**/
void PrintSetup0083(void)
{
   if(!(CurrentPreset.SBLFreqFlags & BIT1))
   {
      ConvertNumberToString(CurrentPreset.SBLMaxFreq);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 139;
   }
   else 
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 140;
   }
   VGAPrintParam = ALWAYS;
}

 /**-------------------------------------------------------**
 ** This function displays the - R SBL Frequency Limit.   **
 **-------------------------------------------------------**/
void PrintSetup0084(void)
{
   if(!(CurrentPreset.SBLFreqFlags & BIT0))
   {
      ConvertNumberToString(CurrentPreset.SBLMinFreq);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 141;
   }
   else 
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 142;
   }

   VGAPrintParam = ALWAYS;
}

/**-------------------------------------------------------**
 ** This function displays the - Trigger Distance S Limit.**
 **-------------------------------------------------------**/
void PrintSetup0048(void)
{
   if((CurrentPreset.SuspectLimits & MTRIGDISTBIT) != MTRIGDISTBIT)
   { 
      FormatVariables(CurrentPreset.TrsDistMLS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 169;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 170;
   }
   VGAPrintParam = LTRIGGERDISTMINUS;
}

/**-----------------------------------------------------**
 ** This function prints the page number left justified **
 ** at top of page.                                     **
 **-----------------------------------------------------**/
void PrintHeader1(UINT8 PageNumber)
{
   SINT8 TempStr[20];

   /* print page number */
   SPrintf(TempStr, " %d", PageNumber);
   strcpy(VGABuffer, TempStr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 0;
   VGAPrintParam = ALWAYS;
}
   
/**------------------------------------------------------------------**
 ** This function prints date                                        **
 **------------------------------------------------------------------**/
void PrintHeader2(void)
{
   SINT8 TempStr[20];

   /* send date strings */
   GetDateTime();
   strcpy(VGABuffer, datestr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 2;
   VGAPrintParam = ALWAYS;

}


/**------------------------------------------------------------------**
 ** This function prints preset number and date                      **
 **------------------------------------------------------------------**/
void PrintSubHeader2(void)
{
   SINT8 TempStr[20];

   /* format PRESET =, etc. */
   PresetCheck = CurrentSetup.ActivePreset;
   if(PresetCheck)
   {
      strcpy(TempVGABuffer, "PRESET = [ ");
      strcat(TempVGABuffer, "Preset");  
      SPrintf(TempStr, "%d - ", PresetCheck);
      strcat(TempVGABuffer, TempStr);
      strcat(TempVGABuffer, CurrentPreset.PresetID);
   }
   else
      strcpy(TempVGABuffer, "Preset0 ");   

   /* if preset not updated then flag it with an "*" */
   if(!CurrentPreset.PresetUpdateComplete)
       strcat(TempVGABuffer, "*");
   strcat(TempVGABuffer, " ]");

  /* print PRESET =, etc. */
   strcpy(VGABuffer, TempVGABuffer);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 3;
   VGAPrintParam = ALWAYS;

}

/**------------------------------------------------------------------**
 ** This function prints time and preset creation date               **
 **------------------------------------------------------------------**/
void PrintHeader3(void)
{
   /* print time string, left-adjusted */
   strcpy(VGABuffer, timestr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 4;
   VGAPrintParam = ALWAYS;
}


/**------------------------------------------------------------------**
 ** This function prints time and preset creation date               **
 **------------------------------------------------------------------**/
void PrintSubHeader3(void)
{
   SINT16 i, x, start;
   
  
   if(SummaryInfo.b_unit)
      SPrintf((SINT8*)datestr, " %02u/%02u/%02u", CurrentPreset.Day,
                                                 CurrentPreset.Month,
                                                 CurrentPreset.Year);
   else
      SPrintf((SINT8*)datestr," %02u/%02u/%02u",  CurrentPreset.Month,
                                                    CurrentPreset.Day,
                                                    CurrentPreset.Year);
    /* print Created On:... */
   strcpy(VGABuffer, datestr);

   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 5;
   VGAPrintParam = ALWAYS;
}


void AssignYCoordinate(void)
{
   if (RightPrintYCoordinate > LeftPrintYCoordinate)
      LeftPrintYCoordinate = RightPrintYCoordinate;
   else if (RightPrintYCoordinate < LeftPrintYCoordinate)
      RightPrintYCoordinate = LeftPrintYCoordinate;       
}


/********************************** SystemPresetReport3 *********************************/

/**----------------------------------------------**
 ** This function returns the input string ptr,  **
 ** selected on the input port.                  ** 
 **----------------------------------------------**/
UINT8 GetSelectInStr (UINT16 InputBit)
{
 	UINT8 Value;

    switch (InputBit)
    {
        case INPUT_DISABLED:
           Value = 0;
           break;
        case INPUT_PRESET1:
        /* If 'Select Preset1' is selcted to J3_32 port pin.*/
           Value = 1;
		   break;
        case INPUT_PRESET2:
        /* If 'Select Preset2' is selcted to J3_33 port pin.*/
           Value = 2;
		   break;       
        case INPUT_PRESET3:
        /* If 'Select Preset4' is selcted to J3_19 port pin.*/
           Value = 3;
		   break;       
        case INPUT_PRESET4:
        /* If 'Select Preset8' is selcted to J3_17 port pin.*/
           Value = 4;
		   break;       
        case INPUT_PRESET5:
        /* If 'Select Preset16' is selcted to J3_31 port pin.*/
           Value = 5;
		   break;       
        case INPUT_EXT_TRIGDELAY:
        /* Return External Trigger Delay pointer */
           Value = 6;
		   break; 
        case INPUT_DISP_LOCK:
        /* Return DisplayLock pointer */
           Value = 7;
		   break;     
        case INPUT_EXT_TRIGGER:
        /* Return Ext Cycle Abort ponter. */
           Value = 8;
		   break;
        case INPUT_SONICS_DISABLE:
        /* Return SonicDisable pointer*/
           Value = 9;
		   break;
        case INPUT_MEM_RESET:
        /* Return Menmory Reset pointer. */
           Value = 10;
		   break;     
        case INPUT_SV_INTERLOCK:
        /* Return SVInterlock pointer. */
           Value = 11;
		   break;  
        case INPUT_SYNC_IN:
        /* Return SyncIn pointer. */
           Value = 12;
		   break; 
        default:
           Value = 0;
		   break;
         
      }
      return (Value);
}

/**----------------------------------------------**
 ** This function returns the output string ptr, **
 ** selected on the output port.                 ** 
 **----------------------------------------------**/
UINT8 GetSelectOutStr (UINT16 OutputBit)
{
 	UINT8 Value;

    switch (OutputBit)
    {    /* Get the selected output string. */
        case OUTPUT_DISABLED:
           Value = 0;
		   break;
        case OUTPUT_CFMPRESET:
           Value = 1;
		   break;
        case OUTPUT_AMPDECAY:
           Value = 2;
		   break;
        case OUTPUT_EXT_BEEPER:
           Value = 3;
		   break;       
        case OUTPUT_CYCLE_OK:
           Value = 4;
		   break;       
        case OUTPUT_NO_CYCLEALARM:
           Value = 5;
		   break;       
        case OUTPUT_OLDALARM:
           Value = 6;
		   break;       
        case OUTPUT_MDFY_ALARM:
           Value = 7;
		   break; 
        case OUTPUT_NOTE:
           Value = 8;
		   break;     
        case OUTPUT_MISSING_PART:
           Value = 9;
		   break;
        case OUTPUT_SV_INTERLOCK:
           Value = 10;
		   break;
        case OUTPUT_SYNC_OUT:
           Value = 11;
		   break;
        default:
           Value = 0;
		   break;
        
      }
      return (Value);
}

void GetCylinderStr(void)
/****************************************************************************/
/*                                                                          */
/* Update Cylinder diameter strings. Same algorithm applies to stroke       */
/* length strings.                                                          */
/*                                                                          */
/****************************************************************************/
{
	switch(CurrentSetup.CylinDiameter) {
		case CUSTOMSIZE:
			Value = 10;
			break;

		case SIZE1_5:
			Value = 0;
			break;

		case SIZE2_0:
			Value = 1;
			break;

		case SIZE2_5:
			Value = 2;
			break;

		case SIZE3_0:
			Value = 3;
			break;

		case SIZE3_25:
			Value = 4;
			break;

		case SIZE4_0:
			Value = 5;
			break;

		case SIZE_40:
			Value = 6;
			break;

		case SIZE_50:
			Value = 7;
			break;

		case SIZE_63:
			Value = 8;
			break;

		case SIZE_80:
			Value = 9;
			break;

		default:
			break;
	}
}


void GetStrokeLenStr(void)
{
	switch(CurrentSetup.StrokeLen)
		{
		case CUSTOMLEN:
			Value = 9;
			break;

		case LENGTH_4:
			Value = 0;
			break;

		case LENGTH_5:
			Value = 1;
			break;

		case LENGTH_6:
			Value = 2;
			break;

		case LENGTH_2:
			Value = 3;
			break;
     
      case LENGTH_8:
			Value = 4;
			break;

		case LENGTH_80:
			Value = 5;
			break;

		case LENGTH_100:
			Value = 6;
			break;

		case LENGTH_125:
			Value = 7;
			break;

	/*	case LENGTH_160:
			Value = 8;
			break;*/
      case LENGTH_50:
			Value = 8;
			break;

		default:
			break;
		}
}

/**-----------------------------------------------**
 ** This function displays  the selected Language **
 **-----------------------------------------------**/
void PrintConfig0018(void)
{
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 172;
   VGAPrintParam = PLANGUAGE;
}
/**-----------------------------------**
 ** This function displays  the Units **
 **-----------------------------------**/
void PrintConfig0019(void)
{
   Value = (UINT8)(CurrentSetup.Units);
   ValueFlag = TRUE;
   Val_ID = 173;
   VGAPrintParam = PUNITS;
}

/**-----------------------------------**
 ** This function displays 			  **
 **  the Amplitude Units um/%		  **
 **-----------------------------------**/
void PrintConfig0019A(void)
{
   Value = (UINT8)(CurrentSetup.AmpMicronsFlag);
   ValueFlag = TRUE;
   Val_ID = 290;
   VGAPrintParam = PAMPUNITS;
}

/**-----------------------------------**
 ** This function displays  		  **
 ** the Power Units W/%				  **
 **-----------------------------------**/
void PrintConfig0019B(void)
{
   Value = (UINT8)(CurrentSetup.PeakPowerWattsFlag);
   ValueFlag = TRUE;
   Val_ID = 291;
   VGAPrintParam = PPOWERUNITS;
}

/**--------------------------------------**
 ** This function displays  the Password **
 **--------------------------------------**/
void PrintConfig0020(void)
{
   Value = (UINT8)(CurrentSetup.PassWordFlag);
   ValueFlag = TRUE;
   Val_ID = 174;
   VGAPrintParam = PPASSWORD;
}
// --------------------------------------------
//  This function displays  the Srart Screen 
// --------------------------------------------

void PrintStartScreen(void)
{
   Value = (UINT8)(CurrentSetup.StartScreen);
   ValueFlag = TRUE;
   Val_ID = 175;
   VGAPrintParam = STRTSCREEN;
}
/**-------------------------------------**
 ** This function displays  Serial Port **
 **-------------------------------------**/
void PrintConfig0023(void)
{
   switch (CurrentSetup.SerialPort) {
      case COMPUWELD:
         Value = 0;
		 break;

      case TERMINAL:
         Value = 1;
		 break;

      case ASCIICOMMA:
		 Value = 2;
         break;

      case ASCIITAB:
         Value = 3;
		 break;

      case ASCIISPACE:
         Value = 4;
		 break;

      case RS232DISABLED:
         Value = 5;
		 break;
   }
   ValueFlag = TRUE;
   Val_ID = 176;
   VGAPrintParam = PSERIALPORT;
}
/**-----------------------------------**
 ** This function displays  Baud Rate **
 **-----------------------------------**/
void PrintConfig0024(void)
{
   if(CurrentSetup.BaudRate == BAUD_4800)
   {
	   Value = 0;
      ValueFlag = TRUE;
      Val_ID = 177;
   }
   else
   if(CurrentSetup.BaudRate == BAUD_9600)
   {
	   Value = 1;
      ValueFlag = TRUE;
      Val_ID = 177;
   }
   else
   if(CurrentSetup.BaudRate == BAUD_19200)
   {
	   Value = 2;
      ValueFlag = TRUE;
      Val_ID = 177;
   }
   else
   {
	   Value = 0;
	   ValueFlag = TRUE;
	   Val_ID = 178;
   }
   VGAPrintParam = PBAUDRATE;
}
 /**---------------------------------------**
  ** This function displays  General Alarm **
  ** Reset Required                        **
  **---------------------------------------**/
void PrintConfig0027(void)
{
   Value = (UINT8)(CurrentPreset.GeneralAlarmLFlag);
   ValueFlag = TRUE;
   Val_ID = 179;
   VGAPrintParam = PGENALARMRESET;
}
/**-------------------------------------------**
 ** This function displays the Trigger Beeper **
 **-------------------------------------------**/
UINT16 PrintConfig0028(void)
{
   UINT16 param;
   if (CurrentSetup.HandHeld == FALSE) {  
	  Value = (UINT8)(CurrentSetup.BeeperTrigger);
	  ValueFlag = TRUE;
	  Val_ID = 180;
      param = PTRIGGERBEEPER;
   }
   else
   {
	  Value = (UINT8)(CurrentSetup.BeeperRelease);
	  ValueFlag = TRUE;
	  Val_ID = 181;
      param = PRELEASEBEEPER; 
   }
   VGAPrintParam = param;
   return (param);
}
/**------------------------------------------**
 ** This function displays  the Error Beeper **
 **------------------------------------------**/
void PrintConfig0029(void)
{
   Value = (UINT8)(CurrentSetup.BeeperError);
   ValueFlag = TRUE;
   Val_ID = 182;
   VGAPrintParam = PERRORBEEPER;
}
/**------------------------------------------**
 ** This function displays  the Alarm Beeper **
 **------------------------------------------**/
void PrintConfig0030(void)
{
   Value = (UINT8)(CurrentSetup.BeeperAlarm);
   ValueFlag = TRUE;
   Val_ID = 183;
   VGAPrintParam = PALARMBEEPER;
}
/**-----------------------------------------------**
 ** This function displays  the Amplitude Control **
 **-----------------------------------------------**/
void PrintConfig0032(void)
{
   Value = (UINT8)(CurrentSetup.AmpControl);
   ValueFlag = TRUE;
   Val_ID = 184;
   VGAPrintParam = PAMPCONTROL;
}
/**---------------------------------------------------**
 ** This function displays the extra cooling.         **
 **---------------------------------------------------**/
void PrintConfig0040(void)
{
   Value = (UINT8)(CurrentSetup.AmpControl);
   ValueFlag = TRUE;
   Val_ID = 185;
   VGAPrintParam = PEXTRACOOLING;
}
/**----------------------------------------**
 ** This function displays  the Weld Scale **
 **----------------------------------------**/
void PrintConfig0041(void)
{
   if(CurrentSetup.TimeMultiplier == WELDTIMEx1)
      Value = 0;
   else
   if(CurrentSetup.TimeMultiplier == WELDTIMEx2)
	  Value = 1;
   else
	  Value = 2;
   ValueFlag = TRUE;
   Val_ID = 186;   
   VGAPrintParam = PWELDSCALE;
}
/**----------------------------------------**
 ** This function displays  the Test Scale **
 **----------------------------------------**/
void PrintConfig0042(void)
{
   if(CurrentSetup.TestMultiplier == TESTTIMEx1)
	  Value = 0;
   else
   if(CurrentSetup.TestMultiplier == TESTTIMEx2)
	  Value = 1;
   else
      Value = 2;
   ValueFlag = TRUE;
   Val_ID = 187;   
   VGAPrintParam = PTESTSCALE;
}
/**--------------------------------------------**
 ** This function displays  the Digital Filter **
 **--------------------------------------------**/
void PrintConfig0043(void)
{
   Value = (UINT8)(CurrentPreset.DigitalFilterFlag);
   ValueFlag = TRUE;
   Val_ID = 188;
   VGAPrintParam = PDIGFILTER;
}
/**---------------------------------------------------**
 ** This function displays the Ext Presets.           **
 **---------------------------------------------------**/
void PrintConfig0045(void)
{
   Value = (UINT8)(CurrentSetup.ExtPresets);
   ValueFlag = TRUE;
   Val_ID = 189;
   VGAPrintParam = PEXTPRESETS;
}
/**---------------------------------------------**
 ** This function displays Decimal place 2 or 3 **
 **---------------------------------------------**/
void PrintConfig0099(void)
{
   Value = (UINT8)(CurrentSetup.Metric3Flag);
   ValueFlag = TRUE;
   Val_ID = 190;
   VGAPrintParam = ALWAYS;
}
/**-------------------------------------------**
 ** This function displays  Sequencing on/off **
 **-------------------------------------------**/
void PrintConfig0098(void)
{
   Value = (UINT8)(CurrentSetup.SequenceEnable);
   ValueFlag = TRUE;
   Val_ID = 191;
   VGAPrintParam = ALWAYS;
}
/**--------------------------------------------**
 ** This function displays  Input J3_32        **
 **--------------------------------------------**/
void PrintConfig0085 (void) {
    Value = GetSelectInStr(CurrentSetup.J3_32In);
   ValueFlag = TRUE;
   Val_ID = 192;
   VGAPrintParam = PUSERIO;
}    
/**--------------------------------------------**
 ** This function displays  Input J3_33        **
 **--------------------------------------------**/
void PrintConfig0086 (void) {
   Value = GetSelectInStr(CurrentSetup.J3_33In);
   ValueFlag = TRUE;
   Val_ID = 193;
   VGAPrintParam = PUSERIO;
}
    
/**--------------------------------------------**
 ** This function displays  Input J3_19        **
 **--------------------------------------------**/
void PrintConfig0087 (void) {
   Value = GetSelectInStr(CurrentSetup.J3_19In);
   ValueFlag = TRUE;
   Val_ID = 194;
   VGAPrintParam = PUSERIO;
}
    
/**--------------------------------------------**
 ** This function displays  Input J3_17        **
 **--------------------------------------------**/
void PrintConfig0088 (void) {
   Value = GetSelectInStr(CurrentSetup.J3_17In);
   ValueFlag = TRUE;
   Val_ID = 195;
   VGAPrintParam = PUSERIO;
} 
   
/**--------------------------------------------**
 ** This function displays  Input J3_31        **
 **--------------------------------------------**/
void PrintConfig0089 (void) {
   Value = GetSelectInStr(CurrentSetup.J3_31In);
   ValueFlag = TRUE;
   Val_ID = 196;
   VGAPrintParam = PUSERIO;
}
    
/**--------------------------------------------**
 ** This function displays  Input J3_1        **
 **--------------------------------------------**/
void PrintConfig0090 (void) {
   Value = GetSelectInStr(CurrentSetup.J3_1In);
   ValueFlag = TRUE;
   Val_ID = 197;
   VGAPrintParam = PUSERIO;
}    
/**--------------------------------------------**
 ** This function displays  Output J3_36       **
 **--------------------------------------------**/
void PrintConfig0091 (void) {
   UINT16 OutputBit;
   if (CurrentSetup.SystemControllerFlag == TRUE)
      OutputBit = CurrentSetup.J3_8Out; //for new controller board
   else
      OutputBit = CurrentSetup.J3_36Out;//for old controller board
   Value = GetSelectOutStr(OutputBit);
   ValueFlag = TRUE;
   Val_ID = 198;
   VGAPrintParam = PUSERIO;
}
    
/**--------------------------------------------**
 ** This function displays  Output J3_8        **
 **--------------------------------------------**/
void PrintConfig0092 (void) {
   UINT16 OutputBit;
   if (CurrentSetup.SystemControllerFlag == TRUE)
      OutputBit = CurrentSetup.J3_36Out;//for new controller board   
   else
      OutputBit = CurrentSetup.J3_8Out; //for old controller board
   Value = GetSelectOutStr(OutputBit);
   ValueFlag = TRUE;
   Val_ID = 199;
   VGAPrintParam = PUSERIO;
}
    
/**--------------------------------------------**
 ** This function displays  Output J3_22       **
 **--------------------------------------------**/
void PrintConfig0093 (void) {
   Value = GetSelectOutStr(CurrentSetup.J3_22Out);
   ValueFlag = TRUE;
   Val_ID = 200;
   VGAPrintParam = PUSERIO;
}    

/**--------------------------------------------**
 ** This function displays  User Input Logic   **
 **--------------------------------------------**/
void PrintConfig0094 (void) {
   /* display user inputs */
   Value = (UINT8)(CurrentSetup.UserInLogic);
   ValueFlag = TRUE;
   Val_ID = 201;
   VGAPrintParam = PUSERIO;
}

/**--------------------------------------------**
 ** This function displays  Ext.Start Delay    **
 **--------------------------------------------**/
void PrintConfig0094A (void) {
   FormatVariables(CurrentSetup.SVDelay, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 202;
   VGAPrintParam = ALWAYS;
}
/**--------------------------------------------**
 ** This function displays  Upper Limit Switch **
 **--------------------------------------------**/
void PrintConfig0034(void)
{
   Value = (UINT8)(CurrentSetup.ULSLogicCustom);
   ValueFlag = TRUE;
   Val_ID = 203;
   VGAPrintParam = PULSLOGIC;
}
/**----------------------------------------**
 ** This function displays  Gnd Det Switch **
 **----------------------------------------**/
void PrintConfig0095 (void) {
   /* display user inputs */
   Value = (UINT8)(CurrentSetup.GndDetLogicCustom);
   ValueFlag = TRUE;
   Val_ID = 204;
   VGAPrintParam = PCUSTOMACT; 
}

/**----------------------------------------**
 ** This function displays  Welder Address **
 **----------------------------------------**/
void PrintConfig0096 (void) {
 
 if((CurrentSetup.WelderAddrFlag & BIT0) == FALSE) {

    FormatVariables(CurrentSetup.WelderAddrValue, INTEGER, VGAMisc, 6, CurrentSetup.Units);
	 strcpy(VGABuffer, VGAMisc);
	 Value = 0;
    ValueFlag = FALSE;
    Val_ID = 205;
  }
  else
  {
	 Value = 0;
    ValueFlag = TRUE;
    Val_ID = 206;
  }	  
  VGAPrintParam = ALWAYS; 
}
/**-------------------------------------------**
 ** This function displays  Frequency Offset  **
 **-------------------------------------------**/
void PrintConfig0044(void)
{
   Value = (UINT8)(CurrentSetup.FreqControl);
   ValueFlag = TRUE;
   Val_ID = 207;
   VGAPrintParam = PFREQCONTROL;
}
/**----------------------------------------**
 ** This function displays  Handheld       **
 **----------------------------------------**/
void PrintConfig0097 (void) {
   /* display user inputs */
   Value = (UINT8)(CurrentSetup.HandHeld);
   ValueFlag = TRUE;
   Val_ID = 208;
   VGAPrintParam = PHANDHELDSYSTEM; 
}
/**-------------------------------------------------**
 ** This function displays Distance as ULS/Start Sw **
 **-------------------------------------------------**/
void PrintConfig0100(void)
{
   Value = (UINT8)(CurrentSetup.DistanceULS);
   ValueFlag = TRUE;
   Val_ID = 209;
   VGAPrintParam = ALWAYS;
}
/**----------------------------------------**
 ** This function displays CalibrationInfo **
 **----------------------------------------**/
void PrintCalibrationInfo(void)
{
   if (NVR.CalibPass == CALIBPASSED)
     Value = 1;														/* Pass */
   else if (NVR.CalibPass == CALIBFAILED)
	  Value = 2;														/* Fail */
   else
	  Value = 3;														/* Factory */
   ValueFlag = TRUE;
   Val_ID = 211;
   VGAPrintParam = PCALINFO;                 /* Print in left half-page */
}

/**-------------------------------------**
 ** This function displays Power Supply **
 **-------------------------------------**/
void PrintConfig0009(void)
{
   ConvertNumberToString(CurrentSetup.PSWatt);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 212;
   VGAPrintParam = PPSSUPPLY;
}
/**--------------------------------------**
 ** This function displays Control Level **
 **--------------------------------------**/
void PrintConfig0011(void)
{

   if(DepotFlag->IsADepot)
	  Value = 7;
   else
   {      
      switch(CurrentSetup.ControlLevel)
      {
         case LEVEL_t:
            Value = 0;
			break;

         case LEVEL_e:
            Value = 1;
			break;

         case LEVEL_ea:
            Value = 2;
			break;

         case LEVEL_a:
            Value = 3;
			break;

         case LEVEL_d:             
            Value = 4;
			break;

         case LEVEL_f:
            Value = 5;
			break;

         case LEVEL_TEST:
            Value = 6;
			break;

         default:
            Value = 0;
			break;
      }
   }   
   ValueFlag = TRUE;
   Val_ID = 213;
   VGAPrintParam = PCONTROLLEVEL;
}
/**----------------------------------**
 ** This function displays Frequency **
 **----------------------------------**/
void PrintConfig0008(void)
{
   switch (CurrentSetup.PSFreq)
   {
      case FREQ15KHZ:
         Value = 0;
		 break;
      case FREQ20KHZ:
         Value = 1;
		 break;
      case FREQ30KHZ:
         Value = 2;
		 break;
      case FREQ40KHZ:
         Value = 3;
		 break;
      case FREQ60KHZ:
         Value = 4;
		 break;   
      default:
         Value = 1;
       break;
   }

   ValueFlag = TRUE;
   Val_ID = 214;
   VGAPrintParam = PFREQUENCY;
}
/**-----------------------------------**
 ** This function displays SW Version **
 **-----------------------------------**/
void PrintConfig0012(void)
{
   Value = 0;
   ValueFlag = FALSE;
   strcpy(VGABuffer, SWVersionLabel);
   Val_ID = 215;
   VGAPrintParam = PSWVERSION;
}
/**---------------------------------------**
 ** This function displays SBC SW Version **
 **---------------------------------------**/
void PrintConfig0012A(void)
{
   Value = 0;
   ValueFlag = FALSE;
   strcpy(VGABuffer, SBCVersionLabel);
   Val_ID = 216;
   VGAPrintParam = PSWVERSION;
}
void PrintCalibrationDate(void)
{ 
   RTC RTCPrinter;
   
   if (NVR.CalibPass == CALIBPASSED || NVR.CalibPass == CALIBFAILED)
   {
      RTCPrinter.Day = NVR.CalDate[1];
      RTCPrinter.Month = NVR.CalDate[0];
      RTCPrinter.Year = NVR.CalDate[2];
   }
   else
   {
      RTCPrinter.Day = NVR.DefCalDate[1];
      RTCPrinter.Month = NVR.DefCalDate[0];
      RTCPrinter.Year = NVR.DefCalDate[2];
   }
   
   if (SummaryInfo.b_unit)
      SPrintf ((SINT8 *)datestr, "%02u/%02u/%02u", RTCPrinter.Day, RTCPrinter.Month, RTCPrinter.Year);
   else
      SPrintf ((SINT8 *)datestr, "%02u/%02u/%02u", RTCPrinter.Month, RTCPrinter.Day, RTCPrinter.Year);

   strcpy(VGABuffer, datestr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 222;
   VGAPrintParam = PCALDATE;                 /* Print in right half-page */
}
/**---------------------------------**
 ** This function displays Actuator **
 **---------------------------------**/
void PrintConfig0010(void){

   switch( CurrentSetup.Actuator )
   {
      case AE :
         Value = 0;
		       break;

      case AO :
         Value = 1;
		       break;

      case AED:
         Value = 2;
		       break;

      case AOD:
         Value = 3;
		       break;

      case AEF:
         Value = 4;
		       break;

      case AOF:
         Value = 5;
		       break;

      case MICRO:
         Value = 7;    /* MICRO_11.10A */
		       break;

      default:
         Value = 0;
		       break;
   }
   if (CurrentSetup.CustomAct) Value = 6;
   ValueFlag = TRUE;
   Val_ID = 223;
   VGAPrintParam = PACTUATOR;
}
/**-------------------------------------------**
 ** This function displays  Cylinder Diameter **
 **-------------------------------------------**/
void PrintConfig0016(void)
{
   GetCylinderStr();
   ValueFlag = TRUE;
   Val_ID = 224;
   VGAPrintParam = PCYLDIAMETER;
}
/**----------------------------------------**
 ** This function displays Cylinder Stroke **
 **----------------------------------------**/
void PrintConfig0017(void)
{
   GetStrokeLenStr();
   ValueFlag = TRUE;
   Val_ID = 225;
   VGAPrintParam = PCYLSTROKE;
}

/********************************** end of SystemPresetReport3 *********************************/

/********************************** SystemPresetReport4 *********************************/

/**--------------------------------------------**
 ** This function displays PS Lifetime Counter **
 **--------------------------------------------**/
void PrintConfig0004(void)
{
   ConvertNumberToString(CurrentSetup.PSLifetime);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 217;
   VGAPrintParam = PPSLIFETIME;
}
/**---------------------------------------**
 ** This function displays Preset Counter **
 **---------------------------------------**/
void PrintConfig0022(void)
{
   ConvertNumberToString(CurrentPreset.WeldCount);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 218;
   VGAPrintParam = PPRESETCOUNTER;
}
/**-----------------------------------------**
 ** This function displays Actuator Counter **
 **-----------------------------------------**/
void PrintConfig0077(void)
{
   ConvertNumberToString(CurrentSetup.ActLifetime);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 221;
   VGAPrintParam = PACTLIFETIME;
}



/**----------------------------------**
 ** This function displays Overloads **
 **----------------------------------**/
void PrintConfig0005(void)
{
   ConvertNumberToString(CurrentSetup.Overload);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 219;
   VGAPrintParam = POVERLCOUNTER;
}
/**--------------------------------------**
 ** This function displays General Alarm **
 **--------------------------------------**/
void PrintConfig0006(void)
{
   ConvertNumberToString(CurrentSetup.GenAlarmCount);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 220;
   VGAPrintParam = PGENALARMCNTR;
}
/**-----------------------------------------**
 ** This function displays PS Serial Number **
 **-----------------------------------------**/
void PrintConfig0014(void)
{
   strcpy(VGABuffer,CurrentSetup.PSSerialNumber);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 226;
   VGAPrintParam = PPSSERNUM;
}

/**------------------------------------------**
 ** This function displays ACT Serial Number **
 **------------------------------------------**/
void PrintConfig0015(void)
{
   strcpy(VGABuffer,CurrentSetup.ActSerialNumber);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 227;
   VGAPrintParam = PACTSERNUM;
}

/**-------------------------------------------------**
 ** This function displays Printing On or Suspended **
 **-------------------------------------------------**/
void PrintConfig0078(void)
{
   if(CurrentSetup.ExtPresets == TRUE)  // External preset enabled byte
      Value = (UINT8)(CurrentSetup.ExtGlobalPrintFlag);
   else
      Value = (UINT8)(CurrentPreset.GlobalPrintingFlag);
   ValueFlag = TRUE;
   Val_ID = 230;
   VGAPrintParam = ALWAYS;
}
/**-----------------------------------------------**
 ** This function displays Weld Summary On Sample **
 **-----------------------------------------------**/
void PrintConfig0055(void)
{
   /* Print the Global Sample Value if external preset is enabled. */
   if(CurrentSetup.ExtPresets == FALSE)
   {
      if((CurrentPreset.WeldSummarySFlag & /*PrintOnSampleSummary.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentPreset.WeldSummaryValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else 
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   else
   {
      if((CurrentSetup.WSExtSampleFlag & /*ExtPrintOnSampleSummary.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentSetup.WSExtSampleValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else 
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   Val_ID = 231;
   VGAPrintParam = PWELDDATA;
}
/**----------------------------------------------**
 ** This function displays Power Graph On Sample **
 **----------------------------------------------**/
void PrintConfig0057(void)
{
   /* Print the Global Sample Value if external preset is enabled. */
   if(CurrentSetup.ExtPresets == FALSE)
   {
      if((CurrentPreset.PowerGraphSFlag & /*PrintOnSamplePower.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentPreset.PowerGraphValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else 
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   else
   {
      if((CurrentSetup.PGExtSampleFlag & /*ExtPrintOnSamplePower.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentSetup.PGExtSampleValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else 
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   Val_ID = 232;
   VGAPrintParam = PPOWERGRAPH;
}

/**-------------------------------------------------**
 ** This function displays Amplitude Graph On Sample**
 **-------------------------------------------------**/
void PrintConfig0059(void)
{
   /* Print the Global Sample Value if external preset is enabled. */
   if(CurrentSetup.ExtPresets == FALSE)
   {
      if((CurrentPreset.AmplitudeGraphSFlag & /*PrintOnSampleAmplitude.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentPreset.AmplitudeGraphValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else 
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   else
   {
      if((CurrentSetup.AGExtSampleFlag & /*ExtPrintOnSampleAmplitude.BitMask&*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentSetup.AGExtSampleValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else 
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   Val_ID = 233;
   VGAPrintParam = PAMPLITUDEGRAPH;
}

/**-------------------------------------------------**
 ** This function displays Frequency Graph On Sample**
 **-------------------------------------------------**/
void PrintConfig0061(void)
{
   /* Print the Global Sample Value if external preset is enabled. */
   if(CurrentSetup.ExtPresets == FALSE)
   {
      if((CurrentPreset.FrequencyGraphSFlag & /*PrintOnSampleFreq.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentPreset.FrequencyGraphValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else 
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   else
   {
      if((CurrentSetup.FreqGExtSampleFlag & /*ExtPrintOnSampleFreq.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentSetup.FreqGExtSampleValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else 
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   Val_ID = 234;
   VGAPrintParam = PFREQUENCYGRAPH;
}



/**-----------------------------------------------------**
 ** This function displays Col Distance Graph On Sample **
 **-----------------------------------------------------**/
void PrintConfig0062B(void)
{
   /* Print the Global Sample Value if external preset is enabled. */
   if(CurrentSetup.ExtPresets == FALSE)
   {
      if((CurrentPreset.ColDistanceGraphSFlag & /*PrintOnSampleDistance.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentPreset.ColDistanceGraphValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else 
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   else
   {
      if((CurrentSetup.CDGExtSampleFlag & /*ExtPrintOnSampleDistance.BitMask*/BIT0) == FALSE)
      {
		    ConvertNumberToString(CurrentSetup.CDGExtSampleValue);
		    Value = 2;
          ValueFlag = FALSE;
      }
      else 
      {
		    Value = 0;
          ValueFlag = TRUE;
      }
   }
   Val_ID = 235;
   VGAPrintParam = PDISTANCEGRAPH;
}

/**------------------------------------------------**
 ** This function displays Velocity Graph On Sample**
 **------------------------------------------------**/
void PrintConfig0065(void)
{
   /* Print the Global Sample Value if external preset is enabled. */
   if(CurrentSetup.ExtPresets == FALSE)
   {
      if((CurrentPreset.VelocityGraphSFlag & /*PrintOnSampleVelocity.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentPreset.VelocityGraphValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else 
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   else
   {
      if((CurrentSetup.VGExtSampleFlag & /*ExtPrintOnSampleVelocity.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentSetup.VGExtSampleValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else 
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   Val_ID = 236;
   VGAPrintParam = PVELOCITYGRAPH;
}
/**----------------------------------------------**
 ** This function displays Force Graph On Sample **
 **----------------------------------------------**/
void PrintConfig0067(void)
{
   if ( (CurrentSetup.Actuator==AED) ||
        (CurrentSetup.Actuator==AEF) ||
        (CurrentSetup.Actuator==MICRO) )
   {  /* Print the Global Sample Value if external preset is enabled. */
      if(CurrentSetup.ExtPresets == FALSE)
      {
         if(CurrentPreset.ForceGraphSFlag & /*PrintOnSampleForce.BitMask*/BIT0)
		 {
		   Value = 0;
		   ValueFlag = TRUE;
		 }
         else
		 {
		   ConvertNumberToString(CurrentPreset.ForceGraphValue);
		   Value = 2;
         ValueFlag = FALSE;
		 }
      }
      else
      {
         if(CurrentSetup.FGExtSampleFlag & /*ExtPrintOnSampleForce.BitMask*/BIT0)
		 {
		   Value = 0;
		   ValueFlag = TRUE;
		 }
         else
		 {
		   ConvertNumberToString(CurrentSetup.FGExtSampleValue);
		   Value = 2;
         ValueFlag = FALSE;
		 }
      }
   Val_ID = 237;
   VGAPrintParam = PFORCEGRAPH;
   }
}
/**----------------------------------------------**
 ** This function displays Weld History On Sample**
 **----------------------------------------------**/
void PrintConfig0053(void)
{
   /* Print the Global Sample Value if external preset is enabled. */
   if(CurrentSetup.ExtPresets == FALSE)
   {
      if((CurrentPreset.WeldHistorySFlag & /*PrintOnSampleHistory.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentPreset.WeldHistoryValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else 
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   else
   {
      if((CurrentSetup.WHExtSampleFlag & /*ExtPrintOnSampleHistory.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentSetup.WHExtSampleValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else 
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   Val_ID = 238;
   VGAPrintParam = PWELDHISTORY;
}
/**----------------------------------------**
 ** This function displays Setup On Sample **
 **----------------------------------------**/
void PrintConfig0051(void)
{
   /* Print the Global Sample Value if external preset is enabled. */
   if(CurrentSetup.ExtPresets == FALSE)
   {
      if((CurrentPreset.SetupPresetSFlag & /*PrintOnSampleSetup.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentPreset.SetupPresetValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   else
   {
      if((CurrentSetup.SPExtSampleFlag & /*ExtPrintOnSampleSetup.BitMask*/BIT0) == FALSE)
	  {
		   ConvertNumberToString(CurrentSetup.SPExtSampleValue);
		   Value = 2;
         ValueFlag = FALSE;
	  }
      else
	  {
		  Value = 0;
        ValueFlag = TRUE;
	  }
   }
   Val_ID = 239;
   VGAPrintParam = PSETUP;
}
/**-----------------------------------------------**
 ** This function displays Weld Summary On Alarm  **
 **-----------------------------------------------**/
void PrintConfig0054(void)
{
   if(CurrentSetup.ExtPresets == FALSE)
	  Value = (UINT8)(CurrentPreset.WeldSummaryAFlag);
   else /* Print the Global AlarmFlag if external preset is enabled. */
	  Value = (UINT8)(CurrentSetup.WSExtAlarmFlag);
   ValueFlag = TRUE;
   Val_ID = 240;
   VGAPrintParam = PWELDDATA;
}

/**----------------------------------------------**
 ** This function displays Power Graph On Alarm  **
 **----------------------------------------------**/
void PrintConfig0056(void)
{
   if(CurrentSetup.ExtPresets == FALSE)
	  Value = (UINT8)(CurrentPreset.PowerGraphAFlag);
   else /* Print the Global AlarmFlag if external preset is enabled. */
	  Value = (UINT8)(CurrentSetup.PGExtAlarmFlag);
   ValueFlag = TRUE;
   Val_ID = 241;
   VGAPrintParam = PPOWERGRAPH;
}
/**-------------------------------------------------**
 ** This function displays Amplitude Graph On Alarm **
 **-------------------------------------------------**/
void PrintConfig0058(void)
{
   if(CurrentSetup.ExtPresets == FALSE)
      Value = (UINT8)(CurrentPreset.AmplitudeGraphAFlag);
   else /* Print the Global AlarmFlag if external preset is enabled. */
	  Value = (UINT8)(CurrentSetup.AGExtAlarmFlag);
   ValueFlag = TRUE;
   Val_ID = 242;
   VGAPrintParam = PAMPLITUDEGRAPH;
}
/**-------------------------------------------------**
 ** This function displays Frequency Graph On Alarm **
 **-------------------------------------------------**/
void PrintConfig0060(void)
{
   if(CurrentSetup.ExtPresets == FALSE)
	  Value = (UINT8)(CurrentPreset.FrequencyGraphAFlag);
   else  /* Print the Global AlarmFlag if external preset is enabled. */
	  Value = (UINT8)(CurrentSetup.FreqGExtAlarmFlag);
   ValueFlag = TRUE;
   Val_ID = 243;
   VGAPrintParam = PFREQUENCYGRAPH;
}
/**----------------------------------------------------**
 ** This function displays Col Distance Graph On Alarm **
 **----------------------------------------------------**/
void PrintConfig0062A(void)
{
   if(CurrentSetup.ExtPresets == FALSE)
	  Value = (UINT8)(CurrentPreset.ColDistanceGraphAFlag);
   else /* Print the Global AlarmFlag if external preset is enabled. */
   	  Value = (UINT8)(CurrentSetup.CDGExtAlarmFlag);
   ValueFlag = TRUE;
   Val_ID = 244;
   VGAPrintParam = PDISTANCEGRAPH;
}
/**------------------------------------------------**
 ** This function displays Velocity Graph On Alarm **
 **------------------------------------------------**/
void PrintConfig0064(void)
{
   if(CurrentSetup.ExtPresets == FALSE)
	  Value = (UINT8)(CurrentPreset.VelocityGraphAFlag);
   else /* Print the Global AlarmFlag if external preset is enabled. */
	  Value = (UINT8)(CurrentSetup.VGExtAlarmFlag);
   ValueFlag = TRUE;
   Val_ID = 245;
   VGAPrintParam = PVELOCITYGRAPH;
}
/**---------------------------------------------**
 ** This function displays Force Graph On Alarm **
 **---------------------------------------------**/
void PrintConfig0066(void){
   if ( (CurrentSetup.Actuator==AED) ||
        (CurrentSetup.Actuator==AEF) ||
        (CurrentSetup.Actuator==MICRO) )
   {
      if(CurrentSetup.ExtPresets == FALSE)
	     Value = (UINT8)(CurrentPreset.ForceGraphAFlag);
      else  /* Print the Global AlarmFlag if external preset is enabled. */
	     Value = (UINT8)(CurrentSetup.FGExtAlarmFlag);
     ValueFlag = TRUE;
     Val_ID = 246;
     VGAPrintParam = PFORCEGRAPH;
   }
}

/**----------------------------------------------**
 ** This function displays Weld History On Alarm **
 **----------------------------------------------**/
void PrintConfig0052(void)
{
   if(CurrentSetup.ExtPresets == FALSE)
	   Value = (UINT8)(CurrentPreset.WeldHistoryAFlag);
   else /* Print the Global AlarmFlag if external preset is enabled. */
	  Value = (UINT8)(CurrentSetup.WHExtAlarmFlag);
   ValueFlag = TRUE;
   Val_ID = 248;
   VGAPrintParam = PWELDHISTORY;
}

/**---------------------------------------**
 ** This function displays Setup On Alarm **
 **---------------------------------------**/
void PrintConfig0050(void)
{
   if(CurrentSetup.ExtPresets == FALSE)
	  Value = (UINT8)(CurrentPreset.SetupPresetAFlag);
   else /* Print the Global AlarmFlag if external preset is enabled. */
	  Value = (UINT8)(CurrentSetup.SPExtAlarmFlag);
   ValueFlag = TRUE;
   Val_ID = 247;
   VGAPrintParam = PSETUP;
}

/**------------------------------------------**
 ** This function displays X Axis Auto Scale **
 **------------------------------------------**/
void PrintSetup0079(void)
{
   Value = (UINT8)(CurrentPreset.AutoScaleFlag);
   ValueFlag = TRUE;
   Val_ID = 249;
   VGAPrintParam = PAUTOXSCALE;
}
/**-------------------------------------**
 ** This function displays X Axis Scale **
 **-------------------------------------**/
void PrintSetup0080(void){

   /*-- TIMEMODE and Auto scale inactive--*/
   if((CurrentPreset.WeldMode == TIMEMODE) && CurrentPreset.AutoScaleFlag)
      /* Auto scale on */    
   {
	  Value = 0;
	  ValueFlag = TRUE;
	  Val_ID = 251;
   }
   else
   {  /* Auto scale off */
      FormatVariables(CurrentPreset.XScaleTime, TIME, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 250;
   }

   VGAPrintParam = PXSCALE;
}
/**---------------------------------------**
 ** This function displays Welds Per Page **
 **---------------------------------------**/
void PrintConfig0070(void)
{
   ConvertNumberToString(CurrentSetup.WeldsPerPage);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 252;
   VGAPrintParam = PLINESPERPAGE;
}

/********************************** end of SystemPresetReport4 *********************************/

UINT16 SystemPresetReport1(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints one half of 1st preset page report          **
 **------------------------------------------------------------------**/
{
   UINT8 VGAPageNumber = 1;
   UINT16 param;
   
   VGAPrintLength = 0;
   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   LeftPrintYCoordinate = LEFT_YCOORDINATE;
   RightPrintYCoordinate = RIGHT_YCOORDINATE;
   Font_Print = FONT_PRINTBOLD;
   VGAMisc[VGAMISCLEN] = 0x00; 
   VGAMisc[VGAMISCLEN+1] = 0x00; 
   
   PrintHeader1(VGAPageNumber);
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   PrintHeader2();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   PrintHeader3();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   RightPrintYCoordinate = RightPrintYCoordinate + 1;
   RightPrintXCoordinate = MID_XCOORDINATE - 40;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 1;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   RightPrintXCoordinate = MID_XCOORDINATE + 20;
   PrintSubHeader2();
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   RightPrintXCoordinate = MID_XCOORDINATE;
   PrintSubHeader3();
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   /* Left half-page */
   LeftPrintYCoordinate += (PRINT_LINE_HEIGHT);
   RightPrintYCoordinate += (PRINT_LINE_HEIGHT);
   Font_Print = FONT_PRINT;
   
   param = PrintSetup0002();     /* Weld Time or Weld Energy or ..., based on Weld Mode */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param,Value, Val_ID);
   param = PrintSetup0003();     /* Weld Time or Weld Energy or ..., based on Weld Mode */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param,Value, Val_ID);
   if(CurrentPreset.WeldMode == GRDDETECTMODE)
   {
      PrintSetup0003A();
      VGA_PresetSetup1(&AckBuf, VGABuffer, PSCRUBAMPLITUDE,Value, Val_ID);
   }
   PrintSetup0015();     /* Amplitude */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEA,Value, Val_ID);
   VGAPrintParam = ALWAYS;
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   PrintSetup0016();     /* Amplitude(A) if amplitude step is on */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEA1,Value, Val_ID);
   PrintSetup0017();     /* Amplitude(B) if amplitude step is on */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEB,Value, Val_ID);
   param = PrintSetup0018A();    /* Amplitude Step at Time, Step at Energy, ... */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param,Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   PrintSetup0019();     /* Pretrigger Flag - On or Off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRETRIGGER,Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   PrintSetup0019B();    /* Auto Pretrigger Flag - On or Off, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAUTOPRETRIGGER,Value, Val_ID);
   PrintSetup0019A();    /* Pretrigger Distance, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRETRIGGERDISTANCE,Value, Val_ID);
   PrintSetup0021();     /* Pretrigger Amplitude, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRETRIGGERAMP,Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   PrintSetup0070();     /* Max Timeout */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PMAXTIMEOUT,Value, Val_ID);
   PrintSetup0070A();    /* External Trigger Delay */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PEXTTRIGDLY,Value, Val_ID);

   /* Right half-page */
   PrintSetup0004();     /* Hold Time */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PHOLDTIME,Value, Val_ID);
   PrintSetup0022();     /* Afterburst - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURST,Value, Val_ID);

   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   PrintSetup0023();     /* Afterburst Delay, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURSTDELAY,Value, Val_ID);
   PrintSetup0024();     /* Afterburst Time, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURSTTIME,Value, Val_ID);
   PrintSetup0025();     /* Afterburst Amplitude, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURSTAMP,Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   PrintSetup0025A();    /* Energy Braking - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYBRAKING,Value, Val_ID);
   PrintSetup0026();     /* Post Weld Seek - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPOSTWELDSEEK,Value, Val_ID);
   PrintSetup0027();     /* Frequency Offset */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PFREQCONTROL,Value, Val_ID);
   PrintConfig0081();    /* Digital Tune */
   VGA_PresetSetup2(&AckBuf, VGABuffer, DIGITALTUNE,Value, Val_ID);
   PrintSetup0067();     /* Test Amplitude */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PTESTAMPLITUDE,Value, Val_ID);
   PrintConfig0033();    /* Actuator Clear Output - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PACTCLEAROUTPUT,Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   PrintConfig0033A();   /* Actuator Clear Distance, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PACTCLEARDISTANCE,Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   
   /* Left half-page */
   PrintSetup0071();     /* Cycle Abort - On or Off (forces blank line in right half-page) */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCYCLEABORTS,Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   PrintSetup0033();     /* Ground Detect Abort - On or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PSCRUBTIME,Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   /* Right half-page */
   PrintConfig0071();    /* Missing Part - On or Off or N/A */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PMISSINGPARTFLAG,Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   PrintConfig0072();    /* Missing Part Abort Min - Distance or Off or N/A, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PMISSINGPARTMIN,Value, Val_ID);
   PrintConfig0073();    /* Missing Part Abort Max - Distance or Off or N/A, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PMISSINGPARTMAX,Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;

   /* Left half-page */
   PrintSetup0028();     /* Control Limits - On or Off (forces blank line in right half-page) */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCONTROLLIMITS,Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   PrintSetup0034B();    /* Collapse Cutoff - Distance or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCOLLAPSECUTOFF,Value, Val_ID);
   PrintSetup0034A();    /* Absolute Cutoff - Distance or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PABSOLUTECUTOFF,Value, Val_ID);
   PrintSetup0032();     /* Peak Power Cutoff - Percent or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPKPOWERCUTOFF,Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   /* Right half-page */
   PrintSetup0029();     /* Energy Compensation - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYCOMP,Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   PrintSetup0031();     /* Max. Energy - in Joules, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYMAX,Value, Val_ID);
   PrintSetup0030();     /* Min. Energy - in Joules, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENGERGYMIN,Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   
   if(CurrentSetup.Actuator == AEF){

      /* Left half-page */  
      PrintAEFSetting();  /* aef/aof message (forces blank line in right half-page) */
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
      PrintSetup0012();   /* Rapid Traverse - On or Off */ 
      VGA_PresetSetup1(&AckBuf, VGABuffer, PRAPIDTRAVS,Value, Val_ID);
      LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
      PrintSetup0013();   /* Rapid Traverse Distance, indented */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PRAPIDTRAVS,Value, Val_ID);
      LeftPrintXCoordinate = LEFT_XCOORDINATE;

      PrintSetup0014();   /* Downspeed percent */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PDOWNSPEED,Value, Val_ID);
      PrintSetup0005();   /* Trigger Force */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PTRIGGERFORCE,Value, Val_ID);
      PrintSetup0007();   /* Weld Force - force or step */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDFORCEA,Value, Val_ID);
      PrintSetup0008();   /* Weld Force(A), indented */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDFORCEA1,Value, Val_ID);
      PrintSetup0009();   /* Weld Force(B), indented */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDFORCEB,Value, Val_ID);
      param = PrintSetup0018B();  /* Step at Time/Energy/Power/Distance/Force/External Signal, indented */ 
      VGA_PresetSetup1(&AckBuf, VGABuffer, param,Value, Val_ID);
     /* Booster ____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 72;
      strcpy(VGABuffer, DRAWLINE);
      //VGAPrintParam = ALWAYS;
     // RightPrintYCoordinate += PRINT_LINE_HEIGHT;
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);

      /* Right half-page */
      PrintSetup0011();   /* Hold Force */
      VGA_PresetSetup2(&AckBuf, VGABuffer, PHOLDFORCE,Value, Val_ID);
      PrintSetupSystemPressure();
      VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
      if(CurrentSetup.ControlLevel >= LEVEL_f)
      {
         PrintForceRamps();  /* Force Ramps heading */
         VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
         RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
         VGAPresetWeldRate();     /* Weld Force Rate, indented */
         VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
         VGAPresetStepRate();     /* Step Force Rate, indented */
         VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
         VGAPresetHoldRate();     /* Hold Force Rate, indented */
         VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
         RightPrintXCoordinate = RIGHT_XCOORDINATE;
      }
      /* Fixture ___________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 79;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
      /* Horn ______________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 80;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
   }
   else
   if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) ) {
      
      /* Left half-page */
      /* aed/aod message (forces blank line in right half-page) */
      Value = 0;
      ValueFlag = TRUE;
		if(CurrentSetup.Actuator == MICRO)
			Val_ID = MICRO_SETTINGS_TXT;
		else
			Val_ID = 81;
      VGAPrintParam = ALWAYS;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
      PrintAEDTrigForce();    /* Trigger Force */
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
      /* Velocity ______________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 83;
      VGAPrintParam = DRAWLINEFIELD;
      strcpy(VGABuffer, DRAWLINE);
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
      /* Column Position __________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 84;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
      /* Horn _____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 80;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
      /* Booster _____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 72;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
      
      RightPrintYCoordinate += PRINT_LINE_HEIGHT;
      /* Right half-page */
      /* Downspeed Setting ____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 85;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
      /* Set Gauge Pressure ____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 86;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
      /* Act. Gauge Pressure */
      PrintSystemGaugePressure();
      VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
       /* Fixture _____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 79;
      VGAPrintParam = DRAWLINEFIELD;
      strcpy(VGABuffer, DRAWLINE);
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
   }
   else{

      /* Left half-page */
      /* ae/ao message (forces blank line in right half-page) */
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = AED_SETTINGS_TXT;
      VGAPrintParam = ALWAYS;
     // RightPrintYCoordinate += PRINT_LINE_HEIGHT;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
      /* Trigger Setting ________________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 89;
      strcpy(VGABuffer, DRAWLINE);
     // VGAPrintParam = ALWAYS;
     // RightPrintYCoordinate += PRINT_LINE_HEIGHT;
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
      /* Velocity _______________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 83;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
      /* Column Position ________________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 84;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
      /* Horn ________________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 80;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
      /* Booster _________________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 72;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);

      /* Right half-page */
      /* Downspeed Setting ____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 85;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
      /* Gauge Pressure ____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 90;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
      /* MPS Switch Flag1 ______________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 91;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = PMPSLOGIC;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PMPSLOGIC,Value, Val_ID);
      /* MPS Switch Flag2 ______________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 92;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = PMPSLOGIC;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PMPSLOGIC,Value, Val_ID);
      /* Fixture _________________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 79;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD,Value, Val_ID);
   }


   return (VGAPrintLength);

}
UINT16 SystemPresetReport2(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints second half of 1st preset page report       **
 **------------------------------------------------------------------**/
{
   UINT16 param;
   
   VGAPrintLength = 0;
   VGAMisc[VGAMISCLEN] = 0x00; 
   VGAMisc[VGAMISCLEN+1] = 0x00; 

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;

   if(DUPS_Info.DUPSFlag)
   {
      /* Print Digital UPS subheading */
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 93;
      VGAPrintParam = ALWAYS;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      /* Put blank line in right half-page */
      RightPrintYCoordinate += PRINT_LINE_HEIGHT;

      /*--           *left half-page*           --*/
      /* Ramp Time */
      LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
      FormatVariables(DUPS_CurrentParamSet.WeldRampTime, TIME, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 94;
      VGAPrintParam = PDUPSRAMPTIME;
      VGA_PresetSetup1(&AckBuf, VGABuffer, PDUPSRAMPTIME, Value, Val_ID);

      /* Memory - On or Off */
	   Value = (UINT8)DUPS_Info.DUPSMemFlag;
      ValueFlag = TRUE;
      Val_ID = 95;
      VGAPrintParam = PMEMORY;
      VGA_PresetSetup1(&AckBuf, VGABuffer, PMEMORY, Value, Val_ID);
   
      /* Weld Status - On or Off */
	   Value = (UINT8)CurrentPreset.WeldStatusFlag;
      ValueFlag = TRUE;
      Val_ID = 96;
      VGAPrintParam = PWELDSTATUS;
      VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDSTATUS, Value, Val_ID);   
      LeftPrintXCoordinate = LEFT_XCOORDINATE;

      /*--           *right half-page*           --*/
      /* Select - Name */
      strcpy(VGABuffer, DUPS_ParamSetName[19]);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 97;
      VGAPrintParam = PSELECTNAME;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PSELECTNAME, Value, Val_ID);

      /* Seek Time */
      FormatVariables(DUPS_CurrentParamSet.SeekTime, TIME, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 98;
      VGAPrintParam = PSEEKTIME;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PSEEKTIME, Value, Val_ID);

      /* Timed Seek - On or Off */
      Value = DUPS_Info.DUPSSeekFlag;
      ValueFlag = TRUE;
      Val_ID = 99;
	   VGAPrintParam = PTIMEDSEEK;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PTIMEDSEEK, Value, Val_ID);

   }
   
   /* Print Write In Fields for both Analog/Digital PS */
   /* WriteIn Field1 */
   strcpy(VGABuffer, CurrentPreset.WriteIn1);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 100;
   VGAPrintParam = PWRITEINFIELD;
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWRITEINFIELD, Value, Val_ID);
   
   /* WriteIn Field2 */
   strcpy(VGABuffer, CurrentPreset.WriteIn2);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 101;
   VGAPrintParam = PWRITEINFIELD;
   VGA_PresetSetup2(&AckBuf, VGABuffer, PWRITEINFIELD, Value, Val_ID);



   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   
   if(CurrentSetup.ControlLevel > LEVEL_t){
      Font_Print = FONT_PRINTBOLD;
      RightPrintXCoordinate = MID_XCOORDINATE;
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = 102;
      VGAPrintParam = ALWAYS;
      VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      RightPrintXCoordinate = RIGHT_XCOORDINATE;
      AssignYCoordinate();
   }

   /* Left half-page */
   Font_Print = FONT_PRINT;
   PrintSetup0051();          /* Reject Limits - On or Off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PREJECTLIMITS, Value, Val_ID);
   PrintSetup0052();          /* Reject Reset Required - On or Off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PREJRESETREQ, Value, Val_ID);
   
   /* Right half-page */
   PrintSetup0035();          /* Suspect Limits - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PSUSPECTLIMITS, Value, Val_ID);
   PrintSetup0036();          /* Suspect Reset Required - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PSUSPRESETREQ, Value, Val_ID);

   /* left half-page */
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE - 25;
   PrintSetup0059();          /* display the + Collapse R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LCOLLAPSEPLUS, Value, Val_ID);
   PrintSetup0060();          /* display the - Collapse R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LCOLLAPSEMINUS, Value, Val_ID);
   PrintSetup0055();          /* display the + Energy R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LENERGYPLUS, Value, Val_ID);
   PrintSetup0056();          /* display the - Energy R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LENERGYMINUS, Value, Val_ID);
   PrintSetup0061();          /* display the + Absolute R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LABSOLUTEPLUS, Value, Val_ID);
   PrintSetup0062();          /* display the - Absolute R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LABSOLUTEMINUS, Value, Val_ID);
   PrintSetup0057();          /* display the + Power  R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LPOWERPLUS, Value, Val_ID);
   PrintSetup0058();          /* display the - Power  R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LPOWERMINUS, Value, Val_ID);
   PrintSetup0053();          /* display the + Time   R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTIMEPLUS, Value, Val_ID);
   PrintSetup0054();          /* display the - Time   R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTIMEMINUS, Value, Val_ID);
   PrintSetup0065();          /* display the + Weld Force R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LRMAXFORCE, Value, Val_ID);
   PrintSetup0066();          /* display the - Weld Force R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LRMAXFORCE, Value, Val_ID);
   PrintSetup0063();          /* display the + Trigger Distance R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTRIGGERDISTPLUS, Value, Val_ID);
   PrintSetup0064();          /* display the - Trigger Distance R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTRIGGERDISTMINUS, Value, Val_ID);
   PrintSetup0081();          /* display the +Power band R Limit */
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintSetup0082();          /* display the - Power band R Limit */
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   if (DUPS_Info.DUPSFlag && CurrentSetup.SBLEnable)
   {
      PrintSetup0083();          /* display the +SBL Freq R Limit */
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      PrintSetup0084();          /* display the -SBL Freq R Limit */
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   }
   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   
   /* right half-page */
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE - 25;
   PrintSetup0043();          /* display the + Collapse S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LCOLLAPSEPLUS, Value, Val_ID);
   PrintSetup0044();          /* display the - Collapse S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LCOLLAPSEMINUS, Value, Val_ID);
   PrintSetup0039();          /* display the + Energy S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LENERGYPLUS, Value, Val_ID);
   PrintSetup0040();          /* display the - Energy S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LENERGYMINUS, Value, Val_ID);
   PrintSetup0045();          /* display the + Absolute S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LABSOLUTEPLUS, Value, Val_ID);
   PrintSetup0046();          /* display the - Absolute S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LABSOLUTEMINUS, Value, Val_ID);
   PrintSetup0041();          /* display the + Power  S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LPOWERPLUS, Value, Val_ID);
   PrintSetup0042();          /* display the - Power  S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LPOWERMINUS, Value, Val_ID);
   PrintSetup0037();          /* display the + Time   S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTIMEPLUS, Value, Val_ID);
   PrintSetup0038();          /* display the - Time   S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTIMEMINUS, Value, Val_ID);
   PrintSetup0049();          /* display the + Weld Force S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LMAXFORCEPLUS, Value, Val_ID);
   PrintSetup0050();          /* display the - Weld Force S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LMAXFORCEMINUS, Value, Val_ID);
   PrintSetup0047();          /* display the + Trigger Distance S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTRIGGERDISTPLUS, Value, Val_ID);
   PrintSetup0048();          /* display the - Trigger Distance S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTRIGGERDISTMINUS, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   return (VGAPrintLength);
}

UINT16 SystemPresetReport3(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints one half of 2ndt preset page report          **
 **------------------------------------------------------------------**/
{
   UINT8 VGAPageNumber = 2;
   UINT16 param;
   
   VGAPrintLength = 0;
   VGAMisc[VGAMISCLEN] = 0x00; 
   VGAMisc[VGAMISCLEN+1] = 0x00; 

   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   LeftPrintYCoordinate = LEFT_YCOORDINATE;
   RightPrintYCoordinate = RIGHT_YCOORDINATE;
   Font_Print = FONT_PRINTBOLD;
   
   PrintHeader1(VGAPageNumber);
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   PrintHeader2();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   PrintHeader3();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   RightPrintYCoordinate = RightPrintYCoordinate + 1;
   RightPrintXCoordinate = MID_XCOORDINATE - 40;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 1;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   RightPrintXCoordinate = MID_XCOORDINATE + 20;
   PrintSubHeader2();
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   RightPrintXCoordinate = MID_XCOORDINATE;
   PrintSubHeader3();
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 171;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Font_Print = FONT_PRINT;

   /* left half-page */

   //PrintConfig0018();        /* display selected language */
   //VGA_PresetSetup1(&AckBuf, VGABuffer, PLANGUAGE, Value, Val_ID);
   PrintConfig0019();        /* display the units - metric or english */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PUNITS, Value, Val_ID);
   if(CurrentSetup.ControlLevel >= LEVEL_ea){
	   PrintConfig0019A();        /* display the amplitude units - microns or percent */
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPUNITS, Value, Val_ID);
	   PrintConfig0019B();        /* display the power units - watts or percent */
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PPOWERUNITS, Value, Val_ID);
   }
   PrintConfig0020();        /* display password - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPASSWORD, Value, Val_ID);
   PrintStartScreen();       /* display start screen - run or main */
   VGA_PresetSetup1(&AckBuf, VGABuffer, STRTSCREEN, Value, Val_ID);
   PrintConfig0023();        /* display serial port status */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PSERIALPORT, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   PrintConfig0024();        /* display baud rate, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PBAUDRATE, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   PrintConfig0027();        /* display general alarm reset required - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PGENALARMRESET, Value, Val_ID);
   param = PrintConfig0028();        /* display trigger beeper - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);
   PrintConfig0029();        /* display error beeper - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PERRORBEEPER, Value, Val_ID);
   PrintConfig0030();        /* dispaly alarm beeper - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PALARMBEEPER, Value, Val_ID);
   PrintConfig0032();        /* display amplitude control */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPCONTROL, Value, Val_ID);
   PrintConfig0040();        /* display extra cooling */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PEXTRACOOLING, Value, Val_ID);
   PrintConfig0041();        /* display weld scale */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDSCALE, Value, Val_ID);
   PrintConfig0042();        /* display test scale */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PTESTSCALE, Value, Val_ID);
   PrintConfig0043();        /* display digital filter - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PDIGFILTER, Value, Val_ID);
   PrintConfig0045();        /* display Ext Presets - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PEXTPRESETS, Value, Val_ID);
   PrintConfig0099();        /* Decimal place 2 or 3*/
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintConfig0098();        /* display Sequencing - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   
    /* right half-page */   
  
   PrintConfig0085();        /* display Input J3_32 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0086();        /* display Input J3_33 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0087();        /* display Input J3_19 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0088();        /* display Input J3_17 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0089();        /* display Input J3_31 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0090();        /* display Input J3_2 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0091();        /* display Output J3_36 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0092();        /* display Output J3_8 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0093();        /* display Output J3_22 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0094();        /* display User Input Logic */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0094A();       /* display Ext.Start Delay */
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintConfig0034();        /* display Upper Limit Switch */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PULSLOGIC, Value, Val_ID);
   PrintConfig0095();        /* display Gnd Det Switch */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PCUSTOMACT, Value, Val_ID);
   PrintConfig0096();        /* display Welder address */
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintConfig0044();        /* display frequency offset */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PFREQCONTROL, Value, Val_ID);
   PrintConfig0097();        /* display HandHeld - Off/On*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, PHANDHELDSYSTEM, Value, Val_ID);
   PrintConfig0100();        /* display Distance as ULS/ Start Sw*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Font_Print = FONT_PRINTBOLD;
   
   /*System Information Header*/
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 210;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Font_Print = FONT_PRINT;
   
   /* left half-page */
   PrintCalibrationInfo();   /* display calibration status - pass/fail/factory */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCALINFO, Value, Val_ID);
   PrintConfig0009();        /* display power supply watts */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPSSUPPLY, Value, Val_ID);
   PrintConfig0011();        /* display control level */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCONTROLLEVEL, Value, Val_ID);
   PrintConfig0008();        /* display power supply frequency */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PFREQUENCY, Value, Val_ID);
   PrintConfig0012();        /* display software version */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PSWVERSION, Value, Val_ID);
   PrintConfig0012A();        /* display SBC software version */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PSWVERSION, Value, Val_ID);

   /* right half-page */
   PrintCalibrationDate();   /* display year, month, and day of calibration */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PCALDATE, Value, Val_ID);
   PrintConfig0010();        /* display actuator type */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PACTUATOR, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   PrintConfig0016();        /* display cylinder diameter, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PCYLDIAMETER, Value, Val_ID);
   PrintConfig0017();        /* display cylinder stroke, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PCYLSTROKE, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;


   return (VGAPrintLength);
}

UINT16 SystemPresetReport4(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints second half of 2nd preset page report       **
 **------------------------------------------------------------------**/
{
   UINT16 param;
   
   VGAPrintLength = 0;
   VGAMisc[VGAMISCLEN] = 0x00; 
   VGAMisc[VGAMISCLEN+1] = 0x00; 

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
    
   /* left half-page */
   PrintConfig0004();        /* display power supply lifetime counter */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPSLIFETIME, Value, Val_ID);
   PrintConfig0022();        /* display weld cycle counter */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRESETCOUNTER, Value, Val_ID);
   PrintConfig0077();        /* display actuator lifetime counter */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PACTLIFETIME, Value, Val_ID);
   PrintConfig0005();        /* display overload counter */
   VGA_PresetSetup1(&AckBuf, VGABuffer, POVERLCOUNTER, Value, Val_ID);
   PrintConfig0006();        /* display general alarm counter */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PGENALARMCNTR, Value, Val_ID);

   /* right half-page */
   PrintConfig0014();        /* display power supply serial number */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPSSERNUM, Value, Val_ID);
   //PrintConfig0013();        /* display software serial number */ not being used
   PrintConfig0015();        /* display actuator serial number */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PACTSERNUM, Value, Val_ID);

   /* display power supply type */
   Value = (UINT8)(DUPS_Info.DUPSFlag);
   ValueFlag = TRUE;
   Val_ID = 228;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Font_Print = FONT_PRINTBOLD;
   /* Print "PRINTER" header. */
   RightPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 229;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Font_Print = FONT_PRINT;
   /* left half-page */
   PrintConfig0078();        /* display printing on or suspended */
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;

   /* left half-page */
   PrintConfig0055();        /* display weld summary on sample - count or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDDATA, Value, Val_ID);
   PrintConfig0057();        /* display power graph on sample - count or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPOWERGRAPH, Value, Val_ID);
   PrintConfig0059();        /* display amplitude graph on sample - count or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEGRAPH, Value, Val_ID);
   PrintConfig0061();        /* display frequency graph on sample - count or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PFREQUENCYGRAPH, Value, Val_ID);
   PrintConfig0062B();       /* display collapse distance graph on sample - count or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PDISTANCEGRAPH, Value, Val_ID);
   PrintConfig0065();        /* display velocity graph on sample - count or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PVELOCITYGRAPH, Value, Val_ID);
   PrintConfig0067();        /* display force graph on sample - count or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PFORCEGRAPH, Value, Val_ID);
   PrintConfig0053();        /* display weld history on sample - count or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDHISTORY, Value, Val_ID);
   PrintConfig0051();        /* display setup on sample - count or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUP, Value, Val_ID);

   /* right half-page */
   PrintConfig0054();        /* display weld summary on alarm - on or off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PWELDDATA, Value, Val_ID);
   PrintConfig0056();        /* display power graph on alarm - on or off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPOWERGRAPH, Value, Val_ID);
   PrintConfig0058();        /* display amplitude graph on alarm - on or off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAMPLITUDEGRAPH, Value, Val_ID);
   PrintConfig0060();        /* display frequency graph on alarm - on or off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PFREQUENCYGRAPH, Value, Val_ID);
   PrintConfig0062A();       /* display collapse distance graph on alarm - on or off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PDISTANCEGRAPH, Value, Val_ID);
   PrintConfig0064();        /* display velocity graph on alarm - on or off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PVELOCITYGRAPH, Value, Val_ID);
   PrintConfig0066();        /* display force graph on alarm - on or off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PFORCEGRAPH, Value, Val_ID);
   PrintConfig0052();        /* display weld history on alarm - on or off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PWELDHISTORY, Value, Val_ID);
   PrintConfig0050();        /* display setup on alarm - on or off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUP, Value, Val_ID);
   
   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   /* left half-page */
   PrintSetup0079();         /* display x-axis auto scale - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAUTOXSCALE, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   PrintSetup0080();         /* display x-axis time or ***, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PXSCALE, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   /* right half-page */
   PrintConfig0070();        /* display welds per page count */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PLINESPERPAGE, Value, Val_ID);

   return (VGAPrintLength);

}

UINT16 SystemPresetReport5(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints one half of 3rdt preset page report          **
 **------------------------------------------------------------------**/
{
   UINT8 VGAPageNumber = 3;
   UINT16 param;
   
   VGAPrintLength = 0;
   VGAMisc[VGAMISCLEN] = 0x00; 
   VGAMisc[VGAMISCLEN+1] = 0x00; 

   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   LeftPrintYCoordinate = LEFT_YCOORDINATE;
   RightPrintYCoordinate = RIGHT_YCOORDINATE;
   Font_Print = FONT_PRINTBOLD;
   
   PrintHeader1(VGAPageNumber);
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   PrintHeader2();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   PrintHeader3();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   RightPrintYCoordinate = RightPrintYCoordinate + 1;
   RightPrintXCoordinate = MID_XCOORDINATE - 40;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 1;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   RightPrintXCoordinate = MID_XCOORDINATE + 20;
   PrintSubHeader2();
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   RightPrintXCoordinate = MID_XCOORDINATE;
   PrintSubHeader3();
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS,Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   /*------------------------------------------------------------*/
   
   /*VQS Data Limit Header*/
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 253;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Font_Print = FONT_PRINT;

   /* left half-page */

   PrintVQSData0101();        /* display Weld Time Min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDTIMEMIN, Value, Val_ID);
   PrintVQSData0102();        /* display the Energy Min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PENERGYMIN, Value, Val_ID);
   PrintVQSData0103();        /* display Peak Power Min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPEAKPOWERMIN, Value, Val_ID);
   PrintVQSData0104();       /* display Weld Collapse Min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDCOLLAPSEMIN, Value, Val_ID);
   PrintVQSData0105();        /* display total collapse min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PTOTALCOLLAPSEMIN, Value, Val_ID);
   PrintVQSData0107();        /* display Total Absolute Min*/
   VGA_PresetSetup1(&AckBuf, VGABuffer, PTOTALABSOLUTEMIN, Value, Val_ID);
   PrintVQSData0108();        /* display weld force Min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDFORCEMIN, Value, Val_ID);
   PrintVQSData0109();        /* dispaly Total cycle min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PTOTALCYCLETIMEMIN, Value, Val_ID);
    
    /* right half-page */   
  
   
   PrintVQSData0110();        /* display Weld Time Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PWELDTIMEMAX, Value, Val_ID);
   PrintVQSData0111();        /* display the Energy Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYMAXIMUM, Value, Val_ID);
   PrintVQSData0112();        /* display Peak Power Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPEAKPOWERMAX, Value, Val_ID);
   PrintVQSData0113();       /* display Weld Collapse Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PWELDCOLLAPSEMAX, Value, Val_ID);
   PrintVQSData0114();        /* display total collapse Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PTOTALCOLLAPSEMAX, Value, Val_ID);
   PrintVQSData0116();        /* display Total Absolute Max*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, PTOTALABSOLUTEMAX, Value, Val_ID);
   PrintVQSData0117();        /* display weld force Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PWELDFORCEMAX, Value, Val_ID);
   PrintVQSData0118();        /* dispaly Total cycle Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PTOTALCYCLETIMEMAX, Value, Val_ID);

   return (VGAPrintLength);
}

/**-----------------------------------------------------**
 ** This function prints the page number left justified **
 ** at top of page.                                     **
 **-----------------------------------------------------**/
void PrintDupsPageNumber1(void)
{
   SINT8 TempStr[20];

   SPrintf(TempStr, " %d", 1);
   strcpy(VGABuffer, TempStr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 1;   
}

void PrintDupsPageNumber2(void)
{
   GetDateTime();
   strcpy(VGABuffer, datestr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 2;      
}

void PrintDupsPageNumber3(void)
{
   SINT16 i, x, start;

   strcpy(VGABuffer, timestr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 3;   
}

UINT16 DupsPresetReport1(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints one half of Dups  preset page report        **
 **------------------------------------------------------------------**/
{
   UINT16 DupsPresetNum = DUPS_CURRPARAMSET+1;     
   UINT16 param;
   SINT8* Str;

   VGAPrintLength = 0;
   VGAMisc[VGAMISCLEN] = 0x00; 
   VGAMisc[VGAMISCLEN+1] = 0x00; 

   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   LeftPrintYCoordinate = LEFT_YCOORDINATE;
   RightPrintYCoordinate = RIGHT_YCOORDINATE;
   Font_Print = FONT_PRINTBOLD;
   VGAPrintParam = ALWAYS;
   
   PrintDupsPageNumber1();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintDupsPageNumber2();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintDupsPageNumber3();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   RightPrintYCoordinate += (PRINT_LINE_HEIGHT * 2);
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 4;   
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Print current DUPS preset number */
   SPrintf(TempVGABuffer, " %d", DupsPresetNum); 
   strcpy(VGABuffer, TempVGABuffer);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 5;   
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Print Weld Functions header */
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 6;   
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Font_Print = FONT_PRINT;

   /*--           *left half-page*           --*/
   /* Amplitude */
   ConvertNumberToString(DUPS_CurrentParamSet.WeldAmplitude);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 7;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Phase Loop */
   ConvertNumberToString(DUPS_CurrentParamSet.WeldPhaseLoop);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 8;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   
   /* Amp Loop C1 */
   ConvertNumberToString(DUPS_CurrentParamSet.WeldAmplitudeLoopC1);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 9;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   
   /* Weld High */
   ConvertNumberToString(DUPS_CurrentParamSet.WeldFreqLimitHigh);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 10;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   
   /* Phase Limit */
   ConvertNumberToString(DUPS_CurrentParamSet.WeldPhaseLimit);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 11;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      
   /*--           *right half-page*           --*/
   /* Ramp Time */
   FormatVariables(DUPS_CurrentParamSet.WeldRampTime, TIME, VGAMisc, 6, CurrentSetup.Units);
	strcpy(VGABuffer, VGAMisc);
	Value = 0;
   ValueFlag = FALSE;
   Val_ID = 12;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Phase Loop CF */
   ConvertNumberToString(DUPS_CurrentParamSet.WeldPhaseLoopCF);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 13;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   
   /* Amp Loop C2 */
   ConvertNumberToString(DUPS_CurrentParamSet.WeldAmplitudeLoopC2);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 14;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   
   /* Weld Low */
   ConvertNumberToString(DUPS_CurrentParamSet.WeldFreqLimitLow);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 15;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   
   /* Phase Limit */
   FormatVariables(DUPS_CurrentParamSet.WeldPhaseLimitTime, TIME, VGAMisc, 6, CurrentSetup.Units);
	strcpy(VGABuffer, VGAMisc);
	Value = 0;
   ValueFlag = FALSE;
   Val_ID = 16;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Font_Print = FONT_PRINTBOLD;
   /**********************************************************************************/

   /* Print Horn Scan Functions header */
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 17;   
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Font_Print = FONT_PRINT;

   /*--           *left half-page*           --*/
   /* Amplitude */
   ConvertNumberToString(HornScanInfo.MaximumAmplitude);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 18;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Freq Start */
   ConvertNumberToString(HornScanInfo.StartFreq);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 19;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   
   /* Phase Limit */  //fixme: AT - no phase limit? onlu time delay
   FormatVariables(HornScanInfo.TimeDelay, TIME, VGAMisc, 6, CurrentSetup.Units);
	strcpy(VGABuffer, VGAMisc);
	Value = 0;
   ValueFlag = FALSE;
   Val_ID = 20;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /*--           *right half-page*           --*/
   ConvertNumberToString(HornScanInfo.MaximumCurrent);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 21;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   
   ConvertNumberToString(HornScanInfo.StopFreq);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 22;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Font_Print = FONT_PRINTBOLD;
   /**********************************************************************************/

   /* Print Seek Functions header */
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 23;   
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   Font_Print = FONT_PRINT;
   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;

   /*--           *left half-page*           --*/
   /* Amplitude */
   ConvertNumberToString(DUPS_CurrentParamSet.SeekAmplitude);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 24;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Phase Loop CF*/
   ConvertNumberToString(DUPS_CurrentParamSet.SeekPhaseLoopCF);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 25;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Freq High */   
   ConvertNumberToString(DUPS_CurrentParamSet.SeekFreqLimitHigh);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 26;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Amp Loop C2 */
   ConvertNumberToString(DUPS_CurrentParamSet.SeekAmplitudeLoopC2);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 27;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /*--           *right half-page*           --*/
   /* Phase Loop */
   ConvertNumberToString(DUPS_CurrentParamSet.SeekPhaseLoop);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 28;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Freq Low */
   ConvertNumberToString(DUPS_CurrentParamSet.SeekFreqLimitLow);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 29;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Amp Loop C1 */
   ConvertNumberToString(DUPS_CurrentParamSet.SeekAmplitudeLoopC1);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = 30;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   
   return(VGAPrintLength);
}

UINT16 DupsPresetReport2(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints second half of Dups  preset page report     **
 **------------------------------------------------------------------**/
{
   UINT16 i,x;
   UINT16 param;

   VGAPrintLength = 0;
   VGAMisc[VGAMISCLEN] = 0x00; 
   VGAMisc[VGAMISCLEN+1] = 0x00; 

   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Font_Print = FONT_PRINTBOLD;
   /**********************************************************************************/

   /* Print Software DIP Settings header */
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 31;   
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   Font_Print = FONT_PRINT;
   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;

   /*--           *left half-page*           --*/
   /* Memory - On or Off */
   Value = (UINT8)(DUPS_Info.DUPSMemFlag);
   ValueFlag = TRUE;
   Val_ID = 32;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   
   /* Timed Seek - On or Off */
   Value = (UINT8)(DUPS_Info.DUPSMemFlag);
   ValueFlag = TRUE;
   Val_ID = 33;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /*--           *right half-page*           --*/
   /* Ramp Time */
   FormatVariables(DUPS_CurrentParamSet.WeldRampTime, TIME, VGAMisc, 6, CurrentSetup.Units);
	strcpy(VGABuffer, VGAMisc);
	Value = 0;
   ValueFlag = FALSE;
   Val_ID = 34;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Seek Time */
   FormatVariables(DUPS_CurrentParamSet.SeekTime, TIME, VGAMisc, 6, CurrentSetup.Units);
	strcpy(VGABuffer, VGAMisc);
	Value = 0;
   ValueFlag = FALSE;
   Val_ID = 35;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Font_Print = FONT_PRINTBOLD;

   /**********************************************************************************/

   /* Print comments/status header for other DUPS presets */
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 36;   
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Font_Print = FONT_PRINT;

   for(i=0; i<20; i++)
   {
      SPrintf(TempVGABuffer, "%d", i+1); /*Index no. */
      strcpy(VGABuffer, TempVGABuffer);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 40;   
      if (i%2)
      {
         VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
         RightPrintYCoordinate -= PRINT_LINE_HEIGHT;
      }
      else
      {
         VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
         LeftPrintYCoordinate -= PRINT_LINE_HEIGHT;
      }

      strcpy(TempVGABuffer, DUPS_ParamSetName[i] ); /* DUPS Name*/
      strcpy(VGABuffer, TempVGABuffer);
	   Value = 0;
      ValueFlag = FALSE;
      Val_ID = 37;
      if (i%2)
      {
         RightPrintXCoordinate = RIGHT_XCOORDINATE + 230;
         VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
         RightPrintYCoordinate -= PRINT_LINE_HEIGHT;
         RightPrintXCoordinate = RIGHT_XCOORDINATE;
      }
      else
      {
         LeftPrintXCoordinate = LEFT_XCOORDINATE + 230;
         VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
         LeftPrintYCoordinate -= PRINT_LINE_HEIGHT;
         LeftPrintXCoordinate = LEFT_XCOORDINATE;
      }

      switch (DUPS_Lock[i])
        {
        case DUPS_PARAMSETLOCKED :
            Value = 0;
            break;

        case DUPS_PARAMSETSAVED :
            Value = 1;
            break;
      
        case DUPS_PARAMSETAVAIL :
            Value = 2;
            break;

        default :
           Value =3;
        }
      ValueFlag = TRUE;
      Val_ID = 38;         
      if (i%2)
      {
         VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      }
      else
      {
         VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      }
   }

   LeftPrintYCoordinate += (PRINT_LINE_HEIGHT*4);
   RightPrintYCoordinate += (PRINT_LINE_HEIGHT*4);
   Font_Print = FONT_PRINTBOLD;
   /**********************************************************************************/
   
   Value = 0;                  /*Comments */
   ValueFlag = TRUE;
   Val_ID = 39;   
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   return(VGAPrintLength);
}

UINT8 GetWeldMode_Str(UINT16 WeldMode)
/*--------------------------------------------*
 * Prpare the Preset Header string to display *
 * WeldMode,PresetNum & PresetName.           *
 *--------------------------------------------*/ 
{
   UINT8 Value;

   switch(WeldMode)
   {  /* Get the weld mode string.  */
      case TIMEMODE:
         Value = 0;
         break;
         
      case ENERGYMODE:
         Value = 1;
         break;
         
      case PKPOWERMODE:
         Value = 2;
         break;
         
      case COLLAPSEMODE:
         Value = 3;
         break;
         
      case ABSOLUTEMODE:
         Value = 4;
         break;
         
      case GRDDETECTMODE:
         Value = 5;
         break;
         
      case CONTINUOUSMODE:
         Value = 6;
         break;
         
      default:
         Value = 7;
         break;   
   }
   return (Value);
}

void GetWeldMode_Value(PRESET_COMPRESSED* TempPreset, UINT16 WeldMode)
/****************************************************************************/
/*                                                                          */
/* Creates the text that should appear on the top line of the run screen.   */
/* StrTopLine must be updated for all the languages                      */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Index;
   SINT8* StrTemp;
   SINT8 Str[QVGA_LINESIZE];
   
      for(Index = 0; Index < LINESIZE; Index++)
         Str[Index] = FILLCHAR;
      Str[LINESIZE] = 0;

   switch (WeldMode)
   {
      case TIMEMODE:
         FormatVariables( TempPreset->WeldTime, TIME, Str, LINESIZE,
                          CurrentSetup.Units );
         strcpy(TempVGABuffer, Str);
         break;

      case ENERGYMODE:
         if(TempPreset->WeldEnergy < 10000)
            FormatVariables( TempPreset->WeldEnergy, ENERGY,
                            Str, LINESIZE, CurrentSetup.Units );
         else
            FormatVariables( TempPreset->WeldEnergy, ENERGYDIV10,
                            Str, LINESIZE, CurrentSetup.Units );
            strcpy(TempVGABuffer, Str);
         break;

      case PKPOWERMODE:
         FormatVariables( TempPreset->PeakPwr, PERCENTX10,
                          Str, LINESIZE, CurrentSetup.Units );            
         strcpy(TempVGABuffer, Str);
         break;
       
      case COLLAPSEMODE:
         if ( (CurrentSetup.Actuator == AED) ||
              (CurrentSetup.Actuator == AEF) ||
              (CurrentSetup.Actuator == MICRO) )
         {
            FormatVariables( TempPreset->ColDist, DISTANCE, Str,
                            LINESIZE, CurrentSetup.Units );
            strcpy(TempVGABuffer, Str);
         }
         else
            strcpy(TempVGABuffer, " ");
         break;
    
      case ABSOLUTEMODE:
         if ( (CurrentSetup.Actuator == AED) ||
              (CurrentSetup.Actuator == AEF) ||
              (CurrentSetup.Actuator == MICRO) )
         {
            FormatVariables( TempPreset->AbsDist, DISTANCE, Str,
                            LINESIZE, CurrentSetup.Units );
            strcpy(TempVGABuffer, Str);
         }
         else
            strcpy(TempVGABuffer, " ");
         break;
       
      case GRDDETECTMODE:
         strcpy(TempVGABuffer, " ");
         break;
      
      case CONTINUOUSMODE:
         strcpy(TempVGABuffer, " ");
         break;
         
      default:             
         strcpy(TempVGABuffer, " ");
         break;
   }
}

UINT16 PrintSeqPresetInfo(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints Sequence Preset information                **
 **------------------------------------------------------------------**/
{
   UINT16 Index, Index1,x;
   UINT16 Coloumn1XCoordinate;
   UINT16 Coloumn2XCoordinate;
   UINT16 Coloumn3XCoordinate;
   UINT16 Coloumn4XCoordinate;   
   PRESET_COMPRESSED  *TempPreset;
   VGAPrintLength = 0;

   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   LeftPrintYCoordinate = LEFT_YCOORDINATE;
   RightPrintYCoordinate = RIGHT_YCOORDINATE;
   Font_Print = FONT_PRINTBOLD;
   VGAPrintParam = ALWAYS;
   
   Coloumn1XCoordinate = LeftPrintXCoordinate + 80;
   Coloumn2XCoordinate = LeftPrintXCoordinate + 250;
   Coloumn3XCoordinate = LeftPrintXCoordinate + 550;
   Coloumn4XCoordinate = LeftPrintXCoordinate + 800;

   PrintDupsPageNumber1();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintDupsPageNumber2();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintDupsPageNumber3();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   RightPrintYCoordinate += (PRINT_LINE_HEIGHT * 2);
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 4;   
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   AssignYCoordinate();
   LeftPrintYCoordinate += (PRINT_LINE_HEIGHT*3);
   RightPrintYCoordinate += (PRINT_LINE_HEIGHT*3);
   Font_Print = FONT_PRINT;

   /*Prepare Sequence Setup Header*/
   LeftPrintXCoordinate = Coloumn1XCoordinate;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 5;   
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintYCoordinate -= PRINT_LINE_HEIGHT;

   LeftPrintXCoordinate = Coloumn2XCoordinate;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 6;   
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintYCoordinate -= PRINT_LINE_HEIGHT;

   LeftPrintXCoordinate = Coloumn3XCoordinate;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 7;   
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintYCoordinate -= PRINT_LINE_HEIGHT;

   LeftPrintXCoordinate = Coloumn4XCoordinate;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = 8;   
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT; 


   for(Index=0; Index < CurrentSetup.SequenceCount; Index++)
   {
      Index1 = CurrentSetup.SequenceList[Index];
      /*Index No.*/
      LeftPrintXCoordinate = LEFT_XCOORDINATE;
      Numout1(Index+1, 10, '0', 2, TempVGABuffer);
      strcpy(VGABuffer, TempVGABuffer);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 9;   
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      LeftPrintYCoordinate -= PRINT_LINE_HEIGHT;
      
      /* Preset No.*/
      Numout1(Index1, 10, '0', 2, TempVGABuffer);
      strcpy(VGABuffer, TempVGABuffer);
      LeftPrintXCoordinate = Coloumn1XCoordinate;
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 10;   
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      LeftPrintYCoordinate -= PRINT_LINE_HEIGHT;

      /*Preset  Name */
      TempPreset = (PRESET_COMPRESSED *)PresetAddress[Index1];
      StrCpyTwoBytes(TempVGABuffer, TempPreset->PresetID);  
      strcpy(VGABuffer, TempVGABuffer);
      LeftPrintXCoordinate = Coloumn2XCoordinate;
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 11;   
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      LeftPrintYCoordinate -= PRINT_LINE_HEIGHT;

      /*Weld Mode */
      //LeftPrintXCoordinate = Coloumn3XCoordinate;
       LeftPrintXCoordinate = Coloumn2XCoordinate - 40;
      Value = GetWeldMode_Str(TempPreset->WeldMode);
      ValueFlag = TRUE;
      Val_ID = 12;   
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      LeftPrintYCoordinate -= PRINT_LINE_HEIGHT;

      /*Value */
      GetWeldMode_Value(TempPreset, TempPreset->WeldMode);
      strcpy(VGABuffer, TempVGABuffer);
      LeftPrintXCoordinate = Coloumn4XCoordinate;
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = 13;   
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   }

   return(VGAPrintLength);
}

void RecallViewCompressedPreset(PRESET_COMPRESSED* CompressPreset)
/*****************************************************************************/
/*                                                                           */
/* This brings the preset out of the battery backed up ram, uncompresses it  */
/* and puts it into the  current preset.                                     */
/*                                                                           */
/*****************************************************************************/
{
   UINT16 x;
   BOOLEAN PMCPresetFlag = FALSE;
   UINT8 *TempPtr;
   
   CurrentViewPreset.AbFlag = ((CompressPreset->Word1 >> SHIFT1_ABFLAG) & BIT0);
   CurrentViewPreset.ABSCutoffFlag = ((CompressPreset->Word1 >> SHIFT1_ABSCUTOFFFLAG) & BIT0);
   CurrentViewPreset.AbsDistanceGraphAFlag = ((CompressPreset->Word1 >> SHIFT1_ABSDISTANCEGRAPHAFLAG) & BIT0);
   CurrentViewPreset.AbsDistanceGraphSFlag = ((CompressPreset->Word1 >> SHIFT1_ABSDISTANCEGRAPHSFLAG) & BIT0);
   CurrentViewPreset.ActClrFlag = ((CompressPreset->Word1 >> SHIFT1_ACTCLRFLAG) & BIT0);
   CurrentViewPreset.AmplitudeGraphAFlag = ((CompressPreset->Word1 >> SHIFT1_AMPLITUDEGRAPHAFLAG) & BIT0);
   CurrentViewPreset.AmplitudeGraphSFlag = ((CompressPreset->Word1 >> SHIFT1_AMPLITUDEGRAPHSFLAG) & BIT0);
   CurrentViewPreset.AmpTrigExtFlag = ((CompressPreset->Word1 >> SHIFT1_AMPTRIGEXTFLAG) & BIT0);
   CurrentViewPreset.AutoScaleFlag = ((CompressPreset->Word1 >> SHIFT1_AUTOSCALEFLAG) & BIT0);
   CurrentViewPreset.AutoTrigFlag = ((CompressPreset->Word1 >> SHIFT1_AUTOTRIGFLAG) & BIT0);
   CurrentViewPreset.ColCutoffFlag = ((CompressPreset->Word1 >> SHIFT1_COLCUTOFFFLAG) & BIT0);
   CurrentViewPreset.ColDistanceGraphAFlag = ((CompressPreset->Word1 >> SHIFT1_COLDISTANCEGRAPHAFLAG) & BIT0);
   CurrentViewPreset.ColDistanceGraphSFlag = ((CompressPreset->Word1 >> SHIFT1_COLDISTANCEGRAPHSFLAG) & BIT0);
   CurrentViewPreset.ControlLimitsFlag = ((CompressPreset->Word1 >> SHIFT1_CONTROLLIMITSFLAG) & BIT0);
   CurrentViewPreset.CycleAbortFlag = ((CompressPreset->Word1 >> SHIFT1_CYCLEABORTFLAG) & BIT0);
   CurrentViewPreset.DigitalFilterFlag = ((CompressPreset->Word1 >> SHIFT1_DIGITALFILTERFLAG) & BIT0);
   CurrentViewPreset.EnergyCompFlag = ((CompressPreset->Word1 >> SHIFT1_ENERGYCOMPFLAG) & BIT0);
   CurrentViewPreset.FreqOffsetFlag = ((CompressPreset->Word1 >> SHIFT1_FREQOFFSETFLAG) & BIT0);
   CurrentViewPreset.FrequencyGraphAFlag = ((CompressPreset->Word1 >> SHIFT1_FREQUENCYGRAPHAFLAG) & BIT0);
   CurrentViewPreset.FrequencyGraphSFlag = ((CompressPreset->Word1 >> SHIFT1_FREQUENCYGRAPHSFLAG) & BIT0);
   CurrentViewPreset.ForceGraphAFlag = ((CompressPreset->Word1 >> SHIFT1_FORCEGRAPHAFLAG) & BIT0);
   CurrentViewPreset.ForceGraphSFlag = ((CompressPreset->Word1 >> SHIFT1_FORCEGRAPHSFLAG) & BIT0);
   CurrentViewPreset.ForceTrigExtFlag = ((CompressPreset->Word1 >> SHIFT1_FORCETRIGEXTFLAG) & BIT0);
   CurrentViewPreset.GeneralAlarmLFlag = ((CompressPreset->Word1 >> SHIFT1_GENERALALARMLFLAG) & BIT0);
   CurrentViewPreset.GlobalPrintingFlag = ((CompressPreset->Word1 >> SHIFT1_GLOBALPRINTINGFLAG) & BIT0);
   CurrentViewPreset.GndDetectFlag = ((CompressPreset->Word1 >> SHIFT1_GNDDETECTFLAG) & BIT0);
   CurrentViewPreset.HoldTimeFlag = ((CompressPreset->Word1 >> SHIFT1_HOLDTIMEFLAG) & BIT0);
   CurrentViewPreset.MissingPartFlag = ((CompressPreset->Word1 >> SHIFT1_MISSINGPARTFLAG) & BIT0);
   CurrentViewPreset.MissingMinFlag = ((CompressPreset->Word1 >> SHIFT1_MISSINGMINFLAG) & BIT0);
   CurrentViewPreset.MissingMaxFlag = ((CompressPreset->Word1 >> SHIFT1_MISSINGMAXFLAG) & BIT0);
   CurrentViewPreset.PMCEnabled = ((CompressPreset->Word1 >> SHIFT1_PMCENABLED) & BIT0);

   CurrentViewPreset.PeakPwrCutoffFlag = ((CompressPreset->Word2 >> SHIFT2_PEAKPWRCUTOFFFLAG) & BIT0);
   CurrentViewPreset.PowerGraphAFlag = ((CompressPreset->Word2 >> SHIFT2_POWERGRAPHAFLAG) & BIT0);
   CurrentViewPreset.PowerGraphSFlag = ((CompressPreset->Word2 >> SHIFT2_POWERGRAPHSFLAG) & BIT0);
   CurrentViewPreset.PreTrigDistFlag = ((CompressPreset->Word2 >> SHIFT2_PRETRIGDISTFLAG) & BIT0);
   CurrentViewPreset.PreTrigFlag = ((CompressPreset->Word2 >> SHIFT2_PRETRIGFLAG) & BIT0);
   CurrentViewPreset.RejectLimitsFlag = ((CompressPreset->Word2 >> SHIFT2_REJECTLIMITSFLAG) & BIT0);
   CurrentViewPreset.RejResetRequiredFlag = ((CompressPreset->Word2 >> SHIFT2_REJRESETREQUIREDFLAG) & BIT0);
   CurrentViewPreset.RTFlag = ((CompressPreset->Word2 >> SHIFT2_RTFLAG) & BIT0);
   CurrentViewPreset.ScrubTimeFlag = ((CompressPreset->Word2 >> SHIFT2_SCRUBTIMEFLAG) & BIT0);
   CurrentViewPreset.SeekFunFlag = ((CompressPreset->Word2 >> SHIFT2_SEEKFUNFLAG) & BIT0);
   CurrentViewPreset.SetPressure = ((CompressPreset->Word2 >> SHIFT2_SETPRESSUREFLAG) & BIT0);
   CurrentViewPreset.SetupPresetAFlag = ((CompressPreset->Word2 >> SHIFT2_SETUPPRESETAFLAG) & BIT0);
   CurrentViewPreset.SetupPresetSFlag = ((CompressPreset->Word2 >> SHIFT2_SETUPPRESETSFLAG) & BIT0);
   CurrentViewPreset.SuspectLimitsFlag = ((CompressPreset->Word2 >> SHIFT2_SUSPECTLIMITSFLAG) & BIT0);
   CurrentViewPreset.SusResetRequired = ((CompressPreset->Word2 >> SHIFT2_SUSRESETREQUIREDFLAG) & BIT0);
   CurrentViewPreset.TimingOnTrgFlag = ((CompressPreset->Word2 >> SHIFT2_TIMINGONTRGFLAG) & BIT0);
   CurrentViewPreset.TriggerDelayFlag = ((CompressPreset->Word2 >> SHIFT2_TRIGGERDELAYFLAG) & BIT0);
   CurrentViewPreset.VelocityGraphAFlag = ((CompressPreset->Word2 >> SHIFT2_VELOCITYGRAPHAFLAG) & BIT0);
   CurrentViewPreset.VelocityGraphSFlag = ((CompressPreset->Word2 >> SHIFT2_VELOCITYGRAPHSFLAG) & BIT0);
   CurrentViewPreset.WeldHistoryAFlag = ((CompressPreset->Word2 >> SHIFT2_WELDHISTORYAFLAG) & BIT0);
   CurrentViewPreset.WeldHistorySFlag = ((CompressPreset->Word2 >> SHIFT2_WELDHISTORYSFLAG) & BIT0);
   CurrentViewPreset.WeldStatusFlag = ((CompressPreset->Word2 >> SHIFT2_WELDSTATUSFLAG) & BIT0);
   CurrentViewPreset.WeldSummaryAFlag = ((CompressPreset->Word2 >> SHIFT2_WELDSUMMARYAFLAG) & BIT0);
   CurrentViewPreset.WeldSummarySFlag = ((CompressPreset->Word2 >> SHIFT2_WELDSUMMARYSFLAG) & BIT0);
   CurrentViewPreset.EnergyBraking = ((CompressPreset->Word2 >> SHIFT2_ENERGYBRAKINGFLAG) & BIT0);
   CurrentViewPreset.ExtTrgDelay = ((CompressPreset->Word2 >> SHIFT2_EXTTRGDELAYFLAG) & BIT0);
   CurrentViewPreset.PreTrigDelayFlag = ((CompressPreset->Word2 >> SHIFT2_PRETRIGDELAYFLAG) & BIT0);
   CurrentViewPreset.SeqPresetAFlag = ((CompressPreset->Word2 >> SHIFT2_SEQUENCINGAFLAG) & BIT0);
   CurrentViewPreset.SeqPresetSFlag = ((CompressPreset->Word2 >> SHIFT2_SEQUENCINGSFLAG) & BIT0);
   CurrentViewPreset.PMCPlusBandFlag = ((CompressPreset->Word2 >> SHIFT2_PMCPLUSBANDFLAG) & BIT0);
   CurrentViewPreset.PMCMinusBandFlag = ((CompressPreset->Word2 >> SHIFT2_PMCMINUSBANDFLAG) & BIT0);


   CurrentViewPreset.AbAmp = (UINT32) CompressPreset->AbAmp;
   CurrentViewPreset.AbDelay = (UINT32)CompressPreset->AbDelay;
   CurrentViewPreset.AbTime = (UINT32) CompressPreset->AbTime;
   CurrentViewPreset.Amp1 = (UINT32) CompressPreset->Amp1;
   CurrentViewPreset.Amp2 = (UINT32) CompressPreset->Amp2;
   CurrentViewPreset.AmpScrubTime = (SINT32) CompressPreset->AmpScrubTime;
   CurrentViewPreset.AmpTrigColValue = (UINT32)CompressPreset->AmpTrigColValue;
   CurrentViewPreset.AmpTrigForceValue = (UINT32)CompressPreset->AmpTrigForceValue;
   CurrentViewPreset.AmpTrigPowerValue = (UINT32) CompressPreset->AmpTrigPowerValue;
   CurrentViewPreset.AmpTrigTimeValue = (UINT32) CompressPreset->AmpTrigTimeValue;
   CurrentViewPreset.ColCutoffDist = (UINT32) CompressPreset->ColCutoffDist;
   CurrentViewPreset.ColDist = (UINT32) CompressPreset->ColDist;
   CurrentViewPreset.ColMLR = (UINT32) CompressPreset->ColMLR;
   CurrentViewPreset.ColMLS = (UINT32) CompressPreset->ColMLS;
   CurrentViewPreset.ColPLR = (UINT32) CompressPreset->ColPLR;
   CurrentViewPreset.ColPLS = (UINT32) CompressPreset->ColPLS;
   CurrentViewPreset.Day = (UINT32) CompressPreset->Day;
   CurrentViewPreset.DownSpdStart = (UINT32) CompressPreset->DownSpdStart;
   CurrentViewPreset.EBTime = (UINT32) CompressPreset->EBTime;
   CurrentViewPreset.Force2 = (UINT32) CompressPreset->Force2;
   CurrentViewPreset.ForceTrigAmpValue = (UINT32) CompressPreset->ForceTrigAmpValue;
   CurrentViewPreset.ForceTrigColValue = (UINT32) CompressPreset->ForceTrigColValue;
   CurrentViewPreset.ForceTrigPowerValue = (UINT32) CompressPreset->ForceTrigPowerValue;
   CurrentViewPreset.ForceTrigTimeValue = (UINT32) CompressPreset->ForceTrigTimeValue ;
   CurrentViewPreset.FreqOffset = (UINT32) CompressPreset->FreqOffset;
   CurrentViewPreset.FreqMLR = (UINT32) CompressPreset->FreqMLR;
   CurrentViewPreset.FreqMLS = (UINT32) CompressPreset->FreqMLS;
   CurrentViewPreset.FreqPLR = (UINT32) CompressPreset->FreqPLR;
   CurrentViewPreset.FreqPLS = (UINT32) CompressPreset->FreqPLS ;
   CurrentViewPreset.HoldTime = (UINT32) CompressPreset->HoldTime;
   CurrentViewPreset.HoldForce = (UINT32) CompressPreset->HoldForce;
   CurrentViewPreset.Hour = (UINT32) CompressPreset->Hour;
   CurrentViewPreset.MaxTimeout = (UINT32) CompressPreset->MaxTimeout;
   CurrentViewPreset.MinTrigForce = (UINT32) CompressPreset->MinTrigForce;
   CurrentViewPreset.Minute = (UINT32) CompressPreset->Minute;
   CurrentViewPreset.Month = (UINT32) CompressPreset->Month;
   CurrentViewPreset.PeakPwr = (UINT32) CompressPreset->PeakPwr;
   CurrentViewPreset.PeakPwrCutoff = (UINT32) CompressPreset->PeakPwrCutoff;
   CurrentViewPreset.PowerMLR = (UINT32) CompressPreset->PowerMLR;
   CurrentViewPreset.PowerMLS = (UINT32) CompressPreset->PowerMLS;
   CurrentViewPreset.PowerPLR = (UINT32) CompressPreset->PowerPLR;
   CurrentViewPreset.PowerPLS = (UINT32) CompressPreset->PowerPLS;
   CurrentViewPreset.PreTrigAmp = (UINT32) CompressPreset->PreTrigAmp;
   CurrentViewPreset.RejectLimits = (UINT32) CompressPreset->RejectLimits;
   CurrentViewPreset.ScrubTime = (UINT32) CompressPreset->ScrubTime;
   CurrentViewPreset.SetRTComp = (UINT32) CompressPreset->SetRTComp;
   CurrentViewPreset.SuspectLimits = (UINT32) CompressPreset->SuspectLimits;
   CurrentViewPreset.TestAmp = (UINT32) CompressPreset->TestAmp;
   CurrentViewPreset.TimeMLR = (UINT32) CompressPreset->TimeMLR;
   CurrentViewPreset.TimeMLS = (UINT32) CompressPreset->TimeMLS;
   CurrentViewPreset.TimePLR = (UINT32) CompressPreset->TimePLR;
   CurrentViewPreset.TimePLS = (UINT32) CompressPreset->TimePLS;
   CurrentViewPreset.TriggerDelay = (UINT32) CompressPreset->TriggerDelay;
   CurrentViewPreset.TriggerForce = (UINT32) CompressPreset->TriggerForce;
   CurrentViewPreset.WeldForce = (UINT32) CompressPreset->WeldForce;
   CurrentViewPreset.WeldForceMLR = (UINT32) CompressPreset->WeldForceMLR;
   CurrentViewPreset.WeldForceMLS = (UINT32) CompressPreset->WeldForceMLS;
   CurrentViewPreset.WeldForcePLR = (UINT32) CompressPreset->WeldForcePLR;
   CurrentViewPreset.WeldForcePLS = (UINT32) CompressPreset->WeldForcePLS;
   CurrentViewPreset.WeldTime = (UINT32) CompressPreset->WeldTime;
   CurrentViewPreset.XScaleTime = (UINT32)CompressPreset->XScaleTime;
   CurrentViewPreset.Year = (UINT32) CompressPreset->Year; 
   CurrentViewPreset.ABSCutoffDist = CompressPreset->ABSCutoffDist;
   CurrentViewPreset.AbsDist = CompressPreset->AbsDist;
   CurrentViewPreset.AbsDistanceGraphValue = CompressPreset->AbsDistanceGraphValue; 
   CurrentViewPreset.AbsMLR = CompressPreset->AbsMLR;
   CurrentViewPreset.AbsMLS = CompressPreset->AbsMLS;
   CurrentViewPreset.AbsPLR = CompressPreset->AbsPLR;
   CurrentViewPreset.AbsPLS = CompressPreset->AbsPLS;
   CurrentViewPreset.ActClrDistance = CompressPreset->ActClrDistance;
   CurrentViewPreset.Amp2Flag = CompressPreset->Amp2Flag;                  
   CurrentViewPreset.AmpTrigAbsValue = CompressPreset->AmpTrigAbsValue;
   CurrentViewPreset.AmpTrigEnerValue = CompressPreset->AmpTrigEnerValue;
   CurrentViewPreset.AmplitudeGraphValue = CompressPreset->AmplitudeGraphValue;
   CurrentViewPreset.ColDistanceGraphValue = CompressPreset->ColDistanceGraphValue;   
   CurrentViewPreset.DUPSPreset = CompressPreset->DUPSPreset;
   CurrentViewPreset.EnergyML = CompressPreset->EnergyML;
   CurrentViewPreset.EnergyPL = CompressPreset->EnergyPL;
   CurrentViewPreset.EnergyMLR = CompressPreset->EnergyMLR;
   CurrentViewPreset.EnergyMLS = CompressPreset->EnergyMLS;
   CurrentViewPreset.EnergyPLR = CompressPreset->EnergyPLR;
   CurrentViewPreset.EnergyPLS = CompressPreset->EnergyPLS;
   CurrentViewPreset.Force2Flag = CompressPreset->Force2Flag;                 
   CurrentViewPreset.ForceGraphValue = CompressPreset->ForceGraphValue; 
   CurrentViewPreset.ForceTrigAbsValue = CompressPreset->ForceTrigAbsValue;
   CurrentViewPreset.ForceTrigEnerValue = CompressPreset->ForceTrigEnerValue;
   CurrentViewPreset.FrequencyGraphValue = CompressPreset->FrequencyGraphValue;
   CurrentViewPreset.GaugePressure = CompressPreset->GaugePressure;
   CurrentViewPreset.HoldFR = CompressPreset->HoldFR;
   CurrentViewPreset.MissingPartMin = CompressPreset->MissingPartMin;
   CurrentViewPreset.MissingPartMax = CompressPreset->MissingPartMax;
   CurrentViewPreset.PowerGraphValue = CompressPreset->PowerGraphValue;     
   for (x=0; x<PRESETLEN; x++) {
      CurrentViewPreset.PresetID[x] = CompressPreset->PresetID[x];
   }
   CurrentViewPreset.PresetUpdateComplete = CompressPreset->PresetUpdateComplete;
   CurrentViewPreset.PreTrigDist = CompressPreset->PreTrigDist;
   CurrentViewPreset.PreTrigDelay = CompressPreset->PreTrigDelay;
   CurrentViewPreset.ReturnRamp = CompressPreset->ReturnRamp;  
   CurrentViewPreset.RTDist = CompressPreset->RTDist;
   CurrentViewPreset.RTRamp = CompressPreset->RTRamp;  
   CurrentViewPreset.SetupPresetValue = CompressPreset->SetupPresetValue; 
   CurrentViewPreset.StartRamp = CompressPreset->StartRamp;
   CurrentViewPreset.StepFR = CompressPreset->StepFR;
   CurrentViewPreset.SuspectLimits = CompressPreset->SuspectLimits;              
   CurrentViewPreset.TrsDistMLR = CompressPreset->TrsDistMLR;
   CurrentViewPreset.TrsDistMLS = CompressPreset->TrsDistMLS;
   CurrentViewPreset.TrsDistPLR = CompressPreset->TrsDistPLR; 
   CurrentViewPreset.TrsDistPLS = CompressPreset->TrsDistPLS;
   CurrentViewPreset.VelocityGraphValue = CompressPreset->VelocityGraphValue; 
   CurrentViewPreset.Verified = CompressPreset->Verified;
   CurrentViewPreset.WeldCount = CompressPreset->WeldCount;
   CurrentViewPreset.WeldEnergy = CompressPreset->WeldEnergy;
   CurrentViewPreset.WeldFR = CompressPreset->WeldFR;
   CurrentViewPreset.WeldHistoryValue = CompressPreset->WeldHistoryValue;
   CurrentViewPreset.WeldMode = CompressPreset->WeldMode;
   CurrentViewPreset.WeldSummaryValue = CompressPreset->WeldSummaryValue;
   CurrentViewPreset.HwCnfg = CompressPreset->HwCnfg;
   for (x=0; x<WRITEINLEN; x++) {
      CurrentViewPreset.WriteIn1[x] = CompressPreset->ZWriteIn1[x];
      CurrentViewPreset.WriteIn2[x] = CompressPreset->ZWriteIn2[x];
   }

   /* Terminate strings with NULL */
   CurrentViewPreset.PresetID[PRESETLEN-2]  = 0;
   CurrentViewPreset.WriteIn1[WRITEINLEN-2] = 0;
   CurrentViewPreset.WriteIn2[WRITEINLEN-2] = 0;

   CurrentViewPreset.SBLMinFreqLim = CompressPreset->SBLMinFreqLim;
   CurrentViewPreset.SBLMaxFreqLim = CompressPreset->SBLMaxFreqLim;
   CurrentViewPreset.SBLMinFreq = CompressPreset->SBLMinFreq;
   CurrentViewPreset.SBLMaxFreq = CompressPreset->SBLMaxFreq;
   CurrentViewPreset.SBLFreqFlags = CompressPreset->SBLFreqFlags;
   CurrentViewPreset.PMCTimeout = (UINT32)CompressPreset->PMCTimeout;
   CurrentViewPreset.PMCLowLimit = (UINT32)CompressPreset->PMCLowLimit;
   CurrentViewPreset.PMCHighLimit = (UINT32)CompressPreset->PMCHighLimit;
   CurrentViewPreset.PMCCycleCount = CompressPreset->PMCCycleCount;

	CurrentViewPreset.EnergyMaxVQS = (UINT32)CompressPreset->EnergyMaxVQS ;
	CurrentViewPreset.PeakPowerMaxVQS = (UINT32)CompressPreset->PeakPowerMaxVQS ;
	CurrentViewPreset.TotalAbsMaxVQS = (UINT32)CompressPreset->TotalAbsMaxVQS ;
	CurrentViewPreset.TotalColMaxVQS = (UINT32)CompressPreset->TotalColMaxVQS ;
	CurrentViewPreset.TotalCycleTimeMaxVQS = (UINT32)CompressPreset->TotalCycleTimeMaxVQS ;
	CurrentViewPreset.WeldColMaxVQS = (UINT32)CompressPreset->WeldColMaxVQS ;
	CurrentViewPreset.WeldForceMaxVQS = (UINT32)CompressPreset->WeldForceMaxVQS ;
	CurrentViewPreset.WeldTimeMaxVQS = (UINT32)CompressPreset->WeldTimeMaxVQS ;

	CurrentViewPreset.EnergyMinVQS = (UINT32)CompressPreset->EnergyMinVQS ;
	CurrentViewPreset.PeakPowerMinVQS = (UINT32)CompressPreset->PeakPowerMinVQS ;
	CurrentViewPreset.TotalAbsMinVQS = (UINT32)CompressPreset->TotalAbsMinVQS ;
	CurrentViewPreset.TotalColMinVQS = (UINT32)CompressPreset->TotalColMinVQS ;
	CurrentViewPreset.TotalCycleTimeMinVQS = (UINT32)CompressPreset->TotalCycleTimeMinVQS ;
	CurrentViewPreset.WeldColMinVQS = (UINT32)CompressPreset->WeldColMinVQS ;
	CurrentViewPreset.WeldForceMinVQS = (UINT32)CompressPreset->WeldForceMinVQS ;
	CurrentViewPreset.WeldTimeMinVQS = (UINT32)CompressPreset->WeldTimeMinVQS ;
	CurrentViewPreset.VQSLimit = (UINT16) CompressPreset->VQSLimit;
  
}

/**----------------------------------------------**
 ** This function displays the current weld mode.**
 **----------------------------------------------**/
UINT16 ViewPresetSetup0002(void)
{
   UINT16 param;
   const SINT8  *str;

   switch(CurrentViewPreset.WeldMode)
   {
      case TIMEMODE:
         Value = 0;
         param = PWELDTIME;
         break;
         
      case ENERGYMODE:
         Value = 1;
         param = PENERGY;
         break;
         
      case PKPOWERMODE:
         Value = 2;
         param = PPEAKPOWER;
         break;
         
      case COLLAPSEMODE:
         Value = 3;
         param = PCOLDIST;
         break;
         
      case ABSOLUTEMODE:
         Value = 4;
         param = PABSDIST;
         break;
         
      case GRDDETECTMODE:
         Value = 5;
         param = PGROUNDDETECTCUTOFF;
         break;
         
      case CONTINUOUSMODE:
         Value = 6;
         param = PCONTINUOUS;
         break;
         
      default:
         Value = 0;
         param = PWELDTIME;
         break;   
   }
	ValueFlag = TRUE;
	Val_ID = WELDMODE_TXT;
   VGAPrintParam = param;
   return (param);
}
/**------------------------------------------------**
 ** This function displays the current value based **
 ** on the weld mode.                              **
 **------------------------------------------------**/
UINT16 ViewPresetSetup0003(void)
{
   UINT16 param = 0;

   switch(CurrentViewPreset.WeldMode)         
   { 
      case TIMEMODE:
         FormatVariables(CurrentViewPreset.WeldTime, TIME, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         param = PWELDTIME;
         Val_ID = TIME_TXT;
         break;

      case ENERGYMODE:
         FormatVariables(CurrentViewPreset.WeldEnergy,
            /* cont'd */   CurrentViewPreset.WeldEnergy > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
            /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
         strcpy(VGABuffer, VGAMisc);
         param = PENERGY;
         Val_ID = ENRGY_TXT;
         break;

      case PKPOWERMODE:
         FormatVariables(CurrentViewPreset.PeakPwr, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         param = PPEAKPOWER;
         Val_ID = PKPOWR_TXT;
         break;

      case COLLAPSEMODE:
         FormatVariables(CurrentViewPreset.ColDist, DISTANCE, VGAMisc, 6, CurrentSetup.Units );
         strcpy(VGABuffer, VGAMisc);
         param = PCOLDIST;
         Val_ID = COLLAPSE_TXT;
         break;

      case ABSOLUTEMODE:
         FormatVariables(CurrentViewPreset.AbsDist, DISTANCE, VGAMisc, 6, CurrentSetup.Units );
         strcpy(VGABuffer, VGAMisc);
         param = PABSDIST;
         Val_ID = ABSOLUTE_TXT;
         break;

      case GRDDETECTMODE:
         FormatVariables(CurrentViewPreset.ScrubTime, TIME, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         param = PSCRUBTIME;
         Val_ID = GRDDETECT_TXT;
         break;

      case CONTINUOUSMODE:
         param = ALWAYS;
         Val_ID = CONTINOUS_TXT;
         break;

      default:
         param = ALWAYS;
         Val_ID = ALLMODE_TXT;
         break;
   }
   Value =0;
   ValueFlag = FALSE;
   VGAPrintParam = param;
   return(param);
}


/**----------------------------------------**
 ** This function displays the Amplitude.  **  
 **----------------------------------------**/
void ViewPresetSetup0015(void)
{
   if(CurrentSetup.AmpControl == TRUE){

      /* BIT0 = FIXED, BIT2-BIT6 = STEP */
      if((CurrentViewPreset.Amp2Flag & BIT0) == TRUE) 
	  {
		  Value =CurrentSetup.AmpControl;
		  ValueFlag = TRUE;
		  Val_ID = AMPLITUDE_TXT;
	  }
      else   
	  {
    	  FormatVariables(CurrentViewPreset.Amp1, MICRONS, VGAMisc, 6, CurrentSetup.Units);
    	  	   strcpy(VGABuffer, VGAMisc);
    	 // ConvertNumberToString(CurrentViewPreset.Amp1);
	     Value = 0;
		  ValueFlag = FALSE;
		  Val_ID = 155;
	  }
   }
   else
   {
	   Value = CurrentSetup.AmpControl;
	   ValueFlag = TRUE;
	   Val_ID = AMPLITUDE_TXT;
   }
   VGAPrintParam = PAMPLITUDEA;
}


/**-----------------------------------------**
 ** This function displays the Amplitude(A) **
 ** indented if the Amplitude is ON.        **
 **-----------------------------------------**/
void ViewPresetSetup0016(void)
{
   if( ((CurrentViewPreset.Amp2Flag & BIT0) == TRUE) &&
       ((CurrentSetup.AmpControl& BIT0) == TRUE) ){   // Internal
	   FormatVariables(CurrentViewPreset.Amp1, MICRONS, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
	         
	   
	  // ConvertNumberToString(CurrentViewPreset.Amp1);
	   Value = 0;
	   ValueFlag = FALSE;
	   Val_ID = AMPA_TXT;
      VGAPrintParam = PAMPLITUDEA1;
       
   }
}


/**-----------------------------------------**
 ** This function displays the Amplitude(B) **
 ** indented if Amplitude Step is on.       **    
 **-----------------------------------------**/
void ViewPresetSetup0017(void)
{
   if( ((CurrentViewPreset.Amp2Flag & BIT0)  == TRUE) &&
      ((CurrentSetup.AmpControl & BIT0) == TRUE) ){   // Internal
	   FormatVariables(CurrentViewPreset.Amp2, MICRONS, VGAMisc, 6, CurrentSetup.Units);
	       	  	   strcpy(VGABuffer, VGAMisc);
	   Value = 0;
	   ValueFlag = FALSE;
	   Val_ID = AMPB_TXT;
      VGAPrintParam = PAMPLITUDEB;
   }
}


/**-----------------------------------------------**
 ** This function displays the Amplitude Step  At.**
 **-----------------------------------------------**/
UINT16 ViewPresetSetup0018A(void)
{
   UINT16 param = PAMPLITUDEA;

   if((CurrentSetup.AmpControl & BIT0) == TRUE) {   // Internal

      if((CurrentViewPreset.Amp2Flag & BIT0) == TRUE){
         /* Stepping enabled on time          */
         if((CurrentViewPreset.Amp2Flag & BIT2) == FALSE) {
            FormatVariables(CurrentViewPreset.AmpTrigTimeValue, TIME, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value =0;
		      ValueFlag = FALSE;
            Val_ID = STEP_TIME_TXT;
         }
         /* Stepping enabled on energy        */
         else if((CurrentViewPreset.Amp2Flag & BIT3) == FALSE) {
            FormatVariables(CurrentViewPreset.AmpTrigEnerValue, 
                           CurrentViewPreset.AmpTrigEnerValue > ENERGYPOINT ? ENERGYDIV10 : ENERGY, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value =0;
		      ValueFlag = FALSE;
            Val_ID = STEP_ENRGY_TXT;
         }
         /* Stepping enabled on peak power    */
         else if((CurrentViewPreset.Amp2Flag & BIT4) == FALSE) { 
            FormatVariables(CurrentViewPreset.AmpTrigPowerValue, PERCENTX10, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value =0;
		      ValueFlag = FALSE;
            Val_ID = STEP_PKPOWEER_TXT;
         }
         /* Stepping enabled on collapse dist */
         else if((CurrentViewPreset.Amp2Flag & BIT5) == FALSE) {
            FormatVariables(CurrentViewPreset.AmpTrigColValue,DISTANCE,VGAMisc,6,CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value =0;
		      ValueFlag = FALSE;
            Val_ID = STEP_COLDIST_TXT;
         }
         /* Stepping enabled on force */
         else if((CurrentViewPreset.Amp2Flag & BIT6) == FALSE) {
            FormatVariables(CurrentViewPreset.AmpTrigForceValue, FORCE, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value =0;
		      ValueFlag = FALSE;
            Val_ID = STEP_FORCE_TXT;
         }
         /* Stepping enabled on External Signal */
         else if((CurrentViewPreset.Amp2Flag & BIT7) == FALSE) {
		      ValueFlag = TRUE;
            Val_ID = STEP_EXTSIGNAL_TXT;
         }
         else {
            Value =0;
		      ValueFlag = TRUE;
            Val_ID = STEP_OFF_TXT;
         }
         VGAPrintParam = param;
      }
   }   
   return (param);
}


/**---------------------------------------------**
 ** This function displays the Pretrigger flag. ** 
 **---------------------------------------------**/
void ViewPresetSetup0019(void)
{
	Value = (UINT8)CurrentViewPreset.PreTrigFlag;
	ValueFlag = TRUE;
	Val_ID = PRETRIG_TXT;
	VGAPrintParam = PPRETRIGGER;
}

/**-------------------------------------------------**
 ** This function displays the Pretrigger mode.     **
 **-------------------------------------------------**/
void ViewPresetSetup0019B(void)
{
   UINT8 Temp[30];
   if (CurrentViewPreset.PreTrigFlag == FALSE)             // Pretrigger off
   {
	  Value = 0;
     Val_ID = PRETRIG_OFF_TXT;
   }
   else if (CurrentViewPreset.PreTrigDistFlag == FALSE)    // Pretrigger on distance
   {
	  Value = 0;
     Val_ID = PRETRIG_TYPE_TXT;
   }
   else if (CurrentViewPreset.PreTrigDelayFlag == FALSE)   // Pretrigger on delay
   {
	  Value = 1;
     Val_ID = PRETRIG_TYPE_TXT;
   }
   else                                                // None of the above, auto
   {
	  Value = 2;
     Val_ID = PRETRIG_TYPE_TXT;
   }
   ValueFlag = TRUE;
   
   VGAPrintParam = PAUTOPRETRIGGER;
}

/**--------------------------------------------------------**
 ** This function displays the Pretrigger At Distance/Time **
 **--------------------------------------------------------**/
void ViewPresetSetup0019A(void)
{
   if (CurrentViewPreset.PreTrigFlag == TRUE)
   {
      if((CurrentViewPreset.PreTrigDistFlag & BIT0) == FALSE) {
         FormatVariables(CurrentViewPreset.PreTrigDist, DISTANCE, VGAMisc, 6, CurrentSetup.Units );
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRETRIG_DIST_TXT;
         VGAPrintParam = PPRETRIGGERDISTANCE;   
      }
      else if((CurrentViewPreset.PreTrigDelayFlag & BIT0) == FALSE) {
         FormatVariables(CurrentViewPreset.PreTrigDelay, TIME, VGAMisc, 6, CurrentSetup.Units );
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRETRIG_DLY_TXT;
         VGAPrintParam = PPRETRIGGERDISTANCE;   
      }
   }
}

/**--------------------------------------------------**
 ** This function displays the Pretrigger Amplitude. **
 **--------------------------------------------------**/
void ViewPresetSetup0021(void)
{
   if(((CurrentSetup.AmpControl & BIT0) == TRUE) &&
      ((CurrentViewPreset.PreTrigFlag & BIT0) == TRUE))
   {   // Internal
	   ConvertNumberToString(CurrentViewPreset.PreTrigAmp);
      Value = 0;
	   ValueFlag = FALSE;
	   Val_ID = PRETRIG_AMP_TXT;
	   VGAPrintParam = PPRETRIGGERAMP;
   }
}

/**----------------------------------------**
 ** This function displays the Max Timeout **
 **----------------------------------------**/
void ViewPresetSetup0070(void){
   if((CurrentViewPreset.WeldMode==GRDDETECTMODE) ||   
       (((CurrentViewPreset.WeldMode==ENERGYMODE)||
         (CurrentViewPreset.WeldMode==COLLAPSEMODE))&&
         (CurrentSetup.ControlLevel>=LEVEL_e))||
       
       (((CurrentViewPreset.WeldMode==PKPOWERMODE)||
         (CurrentViewPreset.WeldMode==ABSOLUTEMODE))&&
         (CurrentSetup.ControlLevel>=LEVEL_ea))){
      FormatVariables(CurrentViewPreset.MaxTimeout, TIME, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
	   Value = 0;
	   ValueFlag = FALSE;
	   Val_ID = MAX_TIMEOUT_TXT;
      VGAPrintParam = PMAXTIMEOUT;
   }
}

/**----------------------------------------**
 ** This function displays the External    **
 ** Trigger Delay - on or off              **
 **----------------------------------------**/
void ViewPresetSetup0070A(void)
{
   Value = (UINT8)CurrentViewPreset.ExtTrgDelay;
   ValueFlag = TRUE;
   Val_ID = EXTTRIG_DLY_TXT;
   VGAPrintParam = PEXTTRIGDLY;             
}

/* -------------------------------------------------------Right Half Page functions---------------------------------- */


/**-----------------------------------------------**
 ** This function displays the current Hold Time. **
 **-----------------------------------------------**/
void ViewPresetSetup0004(void)
{
  /* Hold Time */
  if((CurrentViewPreset.HoldTimeFlag & BIT0) == FALSE) {

    FormatVariables(CurrentViewPreset.HoldTime, TIME, VGAMisc, 6, CurrentSetup.Units);
    strcpy(VGABuffer, VGAMisc);
    Value = 0;
	 ValueFlag = FALSE;
	 Val_ID =HOLDTIME_TXT;
  }
  else
  {
     Value = 0;
	  ValueFlag = TRUE;
	  Val_ID =HOLDTIME_OFF_TXT;
  }
   VGAPrintParam = PHOLDTIME;  
}


/**----------------------------------------**
 ** This function displays the Afterburst. **
 **----------------------------------------**/
void ViewPresetSetup0022(void)
{
   Value = (UINT8)CurrentViewPreset.AbFlag;
   ValueFlag = TRUE;
   Val_ID = ABRUST_TXT;
   VGAPrintParam = PAFTERBURST;
}


/**----------------------------------------------**
 ** This function displays the Afterburst Delay. **
 **----------------------------------------------**/
void ViewPresetSetup0023(void)
{
   FormatVariables(CurrentViewPreset.AbDelay, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
	ValueFlag = FALSE;
	Val_ID =ABRUST_DLY_TXT;
   VGAPrintParam = PAFTERBURSTDELAY;
}

/**--------------------------------------------**
 ** This function displays the Afterburst time **
 ** indented if Afterburst is on.              **
 **--------------------------------------------**/
void ViewPresetSetup0024(void)
{
   FormatVariables(CurrentViewPreset.AbTime, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
	ValueFlag = FALSE;
	Val_ID =ABTIME_TXT;
   VGAPrintParam = PAFTERBURSTTIME;
}



/**-----------------------------------------**
 ** This function displays the Afterburst   **
 **  Amplitude indented if Afterburst is on.**
 **
-----------------------------------------**/
 void ViewPresetSetup0025(void)
{
   if((CurrentSetup.AmpControl & BIT0) == TRUE){   // Internal
   //ConvertNumberToString(CurrentViewPreset.AbAmp);
   FormatVariables(CurrentViewPreset.AbAmp, MICRONS, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
	ValueFlag = FALSE;
	Val_ID =ABAMP_TXT;
	VGAPrintParam = PAFTERBURSTAMP;
   }   
}


/**---------------------------------------------**
 ** This function displays the Energy Braking   **
 ** state - On or Off                           **
 **---------------------------------------------**/
 void ViewPresetSetup0025A(void)
{
   Value = (UINT8)CurrentViewPreset.EnergyBraking;
   ValueFlag = TRUE;
   Val_ID =ENRGYBRAKING_TXT;
   VGAPrintParam = PENERGYBRAKING;               
}



/**--------------------------------------------**
 ** This function displays the Post Weld Seek. **
 **-------------------------------------------**/
void ViewPresetSetup0026(void)
{
	 Value = (UINT8)(CurrentViewPreset.SeekFunFlag & BIT0);
    ValueFlag = TRUE;
    Val_ID =POSTWELD_TXT;
    VGAPrintParam = PPOSTWELDSEEK;
}





/**----------------------------------------------**
 ** This function displays the Frequency Offset. **  
 **----------------------------------------------**/
void ViewPresetSetup0027(void)
{
   if(CurrentSetup.FreqControl == TRUE){
      if((CurrentViewPreset.FreqOffsetFlag & BIT0) == BIT0)
	  {
       ConvertNumberToString(CurrentViewPreset.FreqOffset);
		 Value = 0;
		 ValueFlag = FALSE;
		 Val_ID =156;
	  }
      else 
	  {
		  Value =0;
		  ValueFlag = TRUE;
		  Val_ID = FREQ_OFFSET_TXT;
	  }
   }
   else{
	  Value = 1;
	  ValueFlag = TRUE;
	  Val_ID = FREQ_OFFSET_TXT;

   }
   VGAPrintParam = PFREQCONTROL;
}

/**--------------------------------------------**
 ** This function displays the Digital Tune    **
 **--------------------------------------------**/
void ViewPresetConfig0081(void)
{
   UINT32 DigPotVal;

   DigPotVal = GetPowerSupplyFrequency();

   switch (CurrentSetup.PSFreq)
   {
      case FREQ15KHZ:
         DigPotVal += CurrentSetup.DigPot/8;
         break;
      case FREQ20KHZ:
         DigPotVal += CurrentSetup.DigPot/6;
         break;
      case FREQ30KHZ:
         DigPotVal += CurrentSetup.DigPot/4;
         break;
      case FREQ60KHZ:
         DigPotVal += CurrentSetup.DigPot/2;
         break;
      case FREQ40KHZ:
      default:
         DigPotVal += CurrentSetup.DigPot/2;
         break;
   }

   if(CurrentSetup.DigPotFlag == TRUE)
   {
      ConvertNumberToString(DigPotVal);
		Value = 2;
      ValueFlag = FALSE;
      Val_ID = DIGITALTUNE_TXT;
   }
   else
   {
	   Value = (UINT8)CurrentSetup.DigPotFlag;
      ValueFlag = TRUE;
      Val_ID = DIGITALTUNE_TXT;
   }
   VGAPrintParam = DIGITALTUNE;   
}


/**--------------------------------------------**
 ** This function displays the Test Amplitude. **
 **--------------------------------------------**/
void ViewPresetSetup0067(void)
{
   //ConvertNumberToString(CurrentViewPreset.TestAmp);
   FormatVariables(CurrentViewPreset.TestAmp, MICRONS, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
	ValueFlag = FALSE;
	Val_ID = TESTAMP_TXT;
	VGAPrintParam = PTESTAMPLITUDE;
}


/**---------------------------------------------------**
 ** This function displays the Actuator Clear Output. **
 **---------------------------------------------------**/
void ViewPresetConfig0033(void)
{
	Value = (UINT8)(CurrentViewPreset.ActClrFlag & BIT0); 
   ValueFlag = TRUE;
   Val_ID = ACTCLEAR_OUT_TXT;
	VGAPrintParam = PACTCLEAROUTPUT;
}

/**--------------------------------------**
 ** This function displays the Distance. **
 **--------------------------------------**/
void ViewPresetConfig0033A(void)
{
   if (CurrentSetup.HandHeld == FALSE) {
      FormatVariables(CurrentViewPreset.ActClrDistance, DISTANCE, VGAMisc, 6, CurrentSetup.Units );
	  strcpy(VGABuffer, VGAMisc);
     Value = 0;
	  ValueFlag = FALSE;
	  Val_ID = ACTCLEAR_DIST_TXT;
      VGAPrintParam = PACTCLEARDISTANCE;
   }
   else 
   {
      RightPrintYCoordinate = RightPrintYCoordinate + PRINT_LINE_HEIGHT;
   }   
}
 
/**----------------------------------------------**
 ** This function displays the Cycle Abort Flag. **
 **----------------------------------------------**/
void ViewPresetSetup0071(void){                                          // ae
  
   if(!((CurrentViewPreset.WeldMode==GRDDETECTMODE)&&(CurrentSetup.Actuator == AE))){
      Value = (UINT8)CurrentViewPreset.CycleAbortFlag;
      ValueFlag = TRUE;
      Val_ID = CYCLEABORT_TXT;
      RightPrintYCoordinate = RightPrintYCoordinate + PRINT_LINE_HEIGHT;  /* leave right half-page blank */
      VGAPrintParam = PCYCLEABORTS;
   }
}

/**------------------------------------------------------**
 ** This function displays the Ground Detect Abort Flag. **
 **------------------------------------------------------**/
void ViewPresetSetup0033(void)
{
   if(CurrentViewPreset.WeldMode != GRDDETECTMODE){
      Value = (UINT8)CurrentViewPreset.GndDetectFlag;
      ValueFlag = TRUE;
      Val_ID = GRDDETECT_ABORT_TXT;
      VGAPrintParam = PSCRUBTIME;
   }
}

/**-----------------------------------------------**
 ** This function displays the Missing Part Flag. **
 **-----------------------------------------------**/
void ViewPresetConfig0071(void)
{
   Value = (UINT8)CurrentViewPreset.MissingPartFlag;
   ValueFlag = TRUE;
   Val_ID = MISSINGPART_TXT;
   VGAPrintParam = PMISSINGPARTFLAG;
}

/**---------------------------------------------------**
 ** This function displays the Missing Part Abort Min **
 **---------------------------------------------------**/
void ViewPresetConfig0072(void)
{
   if(CurrentViewPreset.MissingMinFlag)
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MISSINGPART_MINOFF_TXT;
   }
   else
   {
      FormatVariables(CurrentViewPreset.MissingPartMin, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MISSINGPART_MIN_TXT;
   }   
   VGAPrintParam = PMISSINGPARTMIN;
}

/**---------------------------------------------------**
 ** This function displays the Missing Part Abort Max **
 **---------------------------------------------------**/
void ViewPresetConfig0073(void)
{
   if(CurrentViewPreset.MissingMaxFlag)
   {
	  Value = 0;
     ValueFlag = TRUE;
	  Val_ID = MISSINGPART_MAXOFF_TXT;
   }
   else
   {
     FormatVariables(CurrentViewPreset.MissingPartMax, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
	  ValueFlag = FALSE;
	  Val_ID = MISSINGPART_MAX_TXT;
   }
   VGAPrintParam = PMISSINGPARTMAX;   
}

/* ----------- Left Half Page ----------------- */

/**--------------------------------------------**
 ** This function displays the Control Limits. **
 **--------------------------------------------**/
void ViewPresetSetup0028(void)
{                                       // ae   
   if(!((CurrentViewPreset.WeldMode==PKPOWERMODE) && (CurrentSetup.Actuator== AE)))
   {    
      Value = (UINT8)(CurrentViewPreset.ControlLimitsFlag & BIT0);
      ValueFlag = TRUE;
	   Val_ID = CTRL_LIMITS_TXT;
	   VGAPrintParam = PCONTROLLIMITS;
      RightPrintYCoordinate = RightPrintYCoordinate + PRINT_LINE_HEIGHT;  /* leave right half-page blank */
   }
}

/**---------------------------------------------**
 ** This function displays the Collapse Cutoff. **
 **---------------------------------------------**/
void ViewPresetSetup0034B(void) {
   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == MICRO) )
   {
      if(CurrentViewPreset.WeldMode != COLLAPSEMODE) {
         if(CurrentViewPreset.ColCutoffFlag)	{
            Value = 0 ;
            ValueFlag = TRUE;
            Val_ID = COLCUTOFF_TXT;
		       }
         else {
            FormatVariables(CurrentViewPreset.ColCutoffDist, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = COLCUTOFF_DIST_TXT;
		       }
      }
      VGAPrintParam = PCOLLAPSECUTOFF;
   }
}


void ViewPresetSetup0034A(void)
/**---------------------------------------------**
 ** This function displays the Absolute Cutoff. **
 **---------------------------------------------**/
{
   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == MICRO) )
   {
      if (CurrentViewPreset.WeldMode != ABSOLUTEMODE) {
         if (CurrentViewPreset.ABSCutoffFlag) {
            Value = 0 ;
            ValueFlag = TRUE;
            Val_ID = ABSCUTOFF_TXT;
	      	 }
         else {
            FormatVariables(CurrentViewPreset.ABSCutoffDist, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0 ;
            ValueFlag = FALSE;
            Val_ID = ABSCUTOFF_DIST_TXT;
         }
         VGAPrintParam = PABSOLUTECUTOFF;
      }
   }
}


/**-----------------------------------------------**
 ** This function displays the Peak Power Cutoff. **
 **-----------------------------------------------**/
void ViewPresetSetup0032(void)
{
   if(CurrentViewPreset.WeldMode != PKPOWERMODE)
   {
      if(CurrentViewPreset.PeakPwrCutoffFlag)  /* FALSE = on */
	  {
         Value = 0 ;
         ValueFlag = TRUE;
         Val_ID = PKPOWERCUTOFF_TXT;
	  }
      else
      {
         FormatVariables(CurrentViewPreset.PeakPwrCutoff, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0 ;
         ValueFlag = FALSE;
         Val_ID = PKPOWERCUTOFF_VAL_TXT;
      }
      VGAPrintParam = PPKPOWERCUTOFF;
   }
}

/* ----------- Right Half Page ----------------- */

/**-------------------------------------------------**
 ** This function displays the Energy Compensation. **
 **-------------------------------------------------**/
void ViewPresetSetup0029(void)
{
   if(CurrentViewPreset.WeldMode != PKPOWERMODE)
   { // until 2.5
      if(CurrentViewPreset.WeldMode == TIMEMODE)
      {
         Value = (UINT8)(CurrentViewPreset.EnergyCompFlag & BIT0);
         ValueFlag = TRUE;
         Val_ID = ENRGYCOMP_TXT;
         VGAPrintParam = PENERGYCOMP;
      }
   }
}


/**----------------------------------------**
 ** This function displays the Max Energy. **
 **----------------------------------------**/

void ViewPresetSetup0031(void)
{
   if(CurrentViewPreset.WeldMode != PKPOWERMODE)
   {
      if(CurrentViewPreset.WeldMode == TIMEMODE)
      {
         FormatVariables(CurrentViewPreset.EnergyPL,
            /* cont'd */   CurrentViewPreset.EnergyPL > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
            /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
         strcpy(VGABuffer, VGAMisc);
         Value = 0 ;
         ValueFlag = FALSE;
         Val_ID = MAXENRGY_TXT;
         VGAPrintParam = PENERGYMAX;
      }
   }
} 

/**----------------------------------------**
 ** This function displays the Min Energy. **
 **----------------------------------------**/
void ViewPresetSetup0030(void)
{
   if(CurrentViewPreset.WeldMode != PKPOWERMODE)
   {
      if(CurrentViewPreset.WeldMode == TIMEMODE)
      {
         FormatVariables(CurrentViewPreset.EnergyML,
            /* cont'd */   CurrentViewPreset.EnergyML > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
            /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
         strcpy(VGABuffer, VGAMisc);
         Value = 0 ;
         ValueFlag = FALSE;
         Val_ID = MINENRGY_TXT;
         VGAPrintParam = PENGERGYMIN;
      }
   }
}

/**--------------------------------------------------**
 ** This function displays the aef Settings message. **
 **--------------------------------------------------**/
void DisplayAEFSetting(void)
{
   
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = AEF_SETTINGS_TXT;
   VGAPrintParam = ALWAYS;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
}

/**-------------------------------------------**
 ** This function displays the Rapid Traverse **
 **-------------------------------------------**/
void ViewPresetSetup0012(void)
{
   Value = (UINT8)CurrentViewPreset.RTFlag;
   ValueFlag = TRUE;
   Val_ID = RAPIDTRAVS_TXT;
   VGAPrintParam = PRAPIDTRAVS;
}

/**---------------------------------------------**
 ** This function displays the R/T At Distance. **
 **---------------------------------------------**/
void ViewPresetSetup0013(void)
{
   FormatVariables(CurrentViewPreset.RTDist, DISTANCE, VGAMisc, 6, CurrentSetup.Units );
   strcpy(VGABuffer, VGAMisc);
   Value = 0 ;
   ValueFlag = FALSE;
   Val_ID = RAPIDTRAVS_DIST_TXT;
   VGAPrintParam = PRAPIDTRAVS;
}

/**---------------------------------------**
 ** This function displays the Downspeed. **
 **---------------------------------------**/
void ViewPresetSetup0014(void)
{
   ConvertNumberToString(CurrentViewPreset.DownSpdStart);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = DOWNSPEED_TXT;
   VGAPrintParam = PDOWNSPEED;
}


/**-------------------------------------------**
 ** This function displays the Trigger Force. **
 **-------------------------------------------**/
void ViewPresetSetup0005(void)
{
   FormatVariables(CurrentViewPreset.TriggerForce, FORCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = TRIGFORCE_TXT;
   VGAPrintParam = PTRIGGERFORCE;
}


/**---------------------------------------**
 ** This function displays the Weld Force.**
 **---------------------------------------**/
void ViewPresetSetup0007(void)
{
   /* BIT0 = FIXED, BIT2-BIT6 = STEP */
   if((CurrentViewPreset.Force2Flag & BIT0) == TRUE) 
   {
      Value = (UINT8)(CurrentViewPreset.Force2Flag & BIT0);
      ValueFlag = TRUE;
      Val_ID = WELDFORCE_OFF_TXT;
   }
   else
   {
      FormatVariables(CurrentViewPreset.WeldForce, FORCE, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = WELDFORCE_TXT;
   }
   VGAPrintParam = PWELDFORCEA;
}

/**------------------------------------------**
 ** This function displays the Weld Force(A).**
 **------------------------------------------**/
void ViewPresetSetup0008(void)
{
   if((CurrentViewPreset.Force2Flag & BIT0) == TRUE){ 

      FormatVariables(CurrentViewPreset.WeldForce, FORCE, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = WELDFORCEA_TXT;

      VGAPrintParam = PWELDFORCEA1;
   }
}

/**------------------------------------------**
 ** This function displays the Weld Force(B).**
 **------------------------------------------**/
void ViewPresetSetup0009(void)
{
   if((CurrentViewPreset.Force2Flag & BIT0) == TRUE) {

      FormatVariables(CurrentViewPreset.Force2, FORCE, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = WELDFORCEB_TXT;

      VGAPrintParam = PWELDFORCEB;
   }
}

/**--------------------------------**
 ** This function displays Step At **
 **--------------------------------**/
UINT16 ViewPresetSetup0018B(void)
{
   UINT16 param = ALWAYS;

   if((CurrentViewPreset.Force2Flag & BIT0) == TRUE) {
      /* Stepping enabled on time          */
      if((CurrentViewPreset.Force2Flag & BIT2) == FALSE) {
         FormatVariables(CurrentViewPreset.ForceTrigTimeValue, TIME, VGAMisc, 6, CurrentSetup.Units);
          strcpy(VGABuffer, VGAMisc);
          Value = 0;
          ValueFlag = FALSE;
          Val_ID = STEP_TIME_TXT;
      }
      /* Stepping enabled on energy        */
      else
      if((CurrentViewPreset.Force2Flag & BIT3) == FALSE) {
         FormatVariables(CurrentViewPreset.ForceTrigEnerValue,
                        CurrentViewPreset.ForceTrigEnerValue > ENERGYPOINT ? ENERGYDIV10 : ENERGY, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = STEP_ENRGY_TXT;
      }
      /* Stepping enabled on peak power    */
      else
      if((CurrentViewPreset.Force2Flag & BIT4) == FALSE) { 
         FormatVariables(CurrentViewPreset.ForceTrigPowerValue, PERCENTX10, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = STEP_PKPOWEER_TXT;
      }
      /* Stepping enabled on collapse dist */
      else
      if((CurrentViewPreset.Force2Flag & BIT5) == FALSE) {
         FormatVariables(CurrentViewPreset.ForceTrigColValue, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = STEP_COLDIST_TXT;
      }
      /* Stepping enabled on force */
      else if((CurrentViewPreset.Force2Flag & BIT6) == FALSE) {
         FormatVariables(CurrentViewPreset.ForceTrigAmpValue, PERCENT, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = STEP_FORCE_TXT;
      }
      /* Stepping enabled on external signal */
      else
      if((CurrentViewPreset.Force2Flag & BIT7) == FALSE) {
         Value = 1;
         ValueFlag = TRUE;
         Val_ID = STEP_EXTSIGNAL_TXT;
      }
      else {
         Value = 0;
         ValueFlag = TRUE;
         Val_ID = STEP_OFF_TXT;
      }
      VGAPrintParam = param;
   }
   return (param);
}


/**----------------------------------------**
 ** This function displays the Hold Force. **
 **----------------------------------------**/
void ViewPresetSetup0011(void)
{
   FormatVariables(CurrentViewPreset.HoldForce, FORCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = HOLDFORCE_TXT;
   VGAPrintParam = PHOLDFORCE;
}

/**----------------------------------------------------**
 ** This function displays the System (gauge) Pressure.**
 **----------------------------------------------------**/
void ViewPresetSystemPressure(void)
{
   FormatVariables(CurrentViewPreset.GaugePressure, PRESSURE, VGAMisc, 6, CurrentSetup.Units );
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = GAUGEPRESSURE_TXT;
   VGAPrintParam = ALWAYS; 
}

void PrintForceRamp(void)
{
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = FORCERAMPS_TXT;
   VGAPrintParam = ALWAYS;                   /* Print in right half-page */   
}

void ViewPresetWeldRate(void)
{
   switch(CurrentViewPreset.WeldFR)
   {
      case RATE_SLOWEST:
         Value = 0;
         break;

      case RATE_SLOW:
         Value = 1;
         break;
         
      case RATE_NORMAL:
         Value = 2;
         break;

      case RATE_FAST:
         Value = 3;
         break;

      case RATE_FASTEST:
         Value = 4;
         break;
   }
   ValueFlag = TRUE;
   Val_ID = WELDFORCERATE_TXT;
   VGAPrintParam = ALWAYS;                   /* Print in right half-page */   
}

void ViewPresetStepRate(void)
{
	switch(CurrentViewPreset.StepFR)
   {
      case RATE_SLOWEST:
         Value = 0;
         break;

      case RATE_SLOW:
         Value = 1;
         break;
         
      case RATE_NORMAL:
         Value = 2;
         break;

      case RATE_FAST:
         Value = 3;
         break;

      case RATE_FASTEST:
         Value = 4;
         break;
   }
   ValueFlag = TRUE;
   Val_ID = STEPFORCERATE_TXT;
   VGAPrintParam = ALWAYS;                   /* Print in right half-page */   
}


void ViewPresetHoldRate(void)
{
	switch(CurrentViewPreset.HoldFR)
   {
      case RATE_SLOWEST:
         Value = 0;
         break;

      case RATE_SLOW:
         Value = 1;
         break;
         
      case RATE_NORMAL:
         Value = 2;
         break;

      case RATE_FAST:
         Value = 3;
         break;

      case RATE_FASTEST:
         Value = 4;
         break;
   }
   ValueFlag = TRUE;
   Val_ID = HOLDFORCERATE_TXT;
   VGAPrintParam = ALWAYS;                   /* Print in right half-page */   
}




/**-----------------------------------------**
 ** This function displays the aed Settings. **
 **-----------------------------------------**/
void PrintAEDSetting(void)
{
   Value = 0;
	ValueFlag = TRUE;
	if(CurrentSetup.Actuator == MICRO)
		Val_ID = MICRO_SETTINGS_TXT;
	else
		Val_ID = AED_SETTINGS_TXT;
   VGAPrintParam = ALWAYS;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
}

/**----------------------------------------------**
 ** This function displays the aed Trigger Force.**
 **----------------------------------------------**/
void ViewPresetAEDTrigForce(void)
{
   FormatVariables(CurrentViewPreset.TriggerForce, FORCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = AEDTRIGFORCE_TXT;
   VGAPrintParam = ALWAYS;
}

/**----------------------------------------------------**
 ** This function displays the System (gauge) Pressure.**
 **----------------------------------------------------**/
void PrintSystemPressure(void)
{
   FormatVariables(CurrentViewPreset.GaugePressure, PRESSURE, VGAMisc, 6, CurrentSetup.Units );
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = SYSTEMPRESSURE_TXT;
   VGAPrintParam = ALWAYS; 
}


///////////////////////////////////////////////////////////////////////////////////////
//                      SYSTEM VIEW PRESET REPORT2                                   //
///////////////////////////////////////////////////////////////////////////////////////

/**------------------------------------------**
 ** This function displays the Reject Limits.**
 **------------------------------------------**/
void ViewPresetSetup0051(void)
{
   Value = (UINT8)(CurrentViewPreset.RejectLimitsFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = REJLIMITS_TXT;
   VGAPrintParam = PREJECTLIMITS;
}

/**--------------------------------------------------**
 ** This function displays the Reject Reset Required.**
 **--------------------------------------------------**/
void ViewPresetSetup0052(void)
{
   Value = (UINT8)(CurrentViewPreset.RejResetRequiredFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = REJRESET_TXT;
   VGAPrintParam = PREJRESETREQ;
}

/**-------------------------------------------**
 ** This function displays the Suspect Limits.**
 **-------------------------------------------**/
void ViewPresetSetup0035(void)
{
    Value = (UINT8)(CurrentViewPreset.SuspectLimitsFlag & BIT0);   
    ValueFlag = TRUE;
    Val_ID = SUSPTLIMITS_TXT;
    VGAPrintParam = PSUSPECTLIMITS;
}



/**---------------------------------------------------**
 ** This function displays the Suspect Reset Required.**
 **---------------------------------------------------**/
void ViewPresetSetup0036(void)
{
    Value = (UINT8)(CurrentViewPreset.SusResetRequired & BIT0);
    ValueFlag = TRUE;
    Val_ID = SUSPTRESET_TXT;
    VGAPrintParam = PSUSPRESETREQ;
}

// Left page---
/**-----------------------------------------------**
 ** This function displays the + Collapse R Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0059(void)
{
   if((CurrentViewPreset.RejectLimits & PCOLDISTBIT) != PCOLDISTBIT) { 
      FormatVariables(CurrentViewPreset.ColPLR, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PCOL_RLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PCOL_RLIMT_OFF_TXT;
   }
   VGAPrintParam = LCOLLAPSEPLUS;
}


/**-----------------------------------------------**
 ** This function displays the - Collapse R Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0060(void)
{
   if((CurrentViewPreset.RejectLimits & MCOLDISTBIT) != MCOLDISTBIT)
   {
      FormatVariables(CurrentViewPreset.ColMLR, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MCOL_RLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MCOL_RLIMT_OFF_TXT;
   }
   VGAPrintParam = LCOLLAPSEMINUS;
}


/**---------------------------------------------**
 ** This function displays the + Energy R Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0055(void)
{
   if((CurrentViewPreset.RejectLimits & PENERGYBIT) != PENERGYBIT)
   {
      FormatVariables(CurrentViewPreset.EnergyPLR,
         /* cont'd */   CurrentViewPreset.EnergyPLR > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
         /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PENRGY_RLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PENRGY_RLIMT_OFF_TXT;
   }
   VGAPrintParam = LENERGYPLUS;
}
  
/**---------------------------------------------**
 ** This function displays the - Energy R Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0056(void)
{
   if((CurrentViewPreset.RejectLimits & MENERGYBIT) != MENERGYBIT)
   {
      FormatVariables(CurrentViewPreset.EnergyMLR,
         /* cont'd */   CurrentViewPreset.EnergyMLR > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
         /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MENRGY_RLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MENRGY_RLIMT_OFF_TXT;
   }
   VGAPrintParam = LENERGYMINUS;
}

/**-----------------------------------------------**
 ** This function displays the + Absolute R Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0061(void)
{
   if((CurrentViewPreset.RejectLimits & PABSDISTBIT) != PABSDISTBIT)
   { 
      FormatVariables(CurrentViewPreset.AbsPLR, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PABSOLUTE_RLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PABSOLUTE_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LABSOLUTEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the - Absolute R Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0062(void)
{
   if((CurrentViewPreset.RejectLimits & MABSDISTBIT) != MABSDISTBIT)
   {
      FormatVariables(CurrentViewPreset.AbsMLR, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MABSOLUTE_RLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MABSOLUTE_RLIMT_OFF_TXT;
   }
   VGAPrintParam = LABSOLUTEMINUS;
}
/**---------------------------------------------**
 ** This function displays the + Power  R Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0057(void)
{
   if((CurrentViewPreset.RejectLimits & PPKPOWERBIT) != PPKPOWERBIT)
   {
      FormatVariables(CurrentViewPreset.PowerPLR, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PPKPOWER_RLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PPKPOWER_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LPOWERPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Power  R Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0058(void)
{
   if((CurrentViewPreset.RejectLimits & MPKPOWERBIT) != MPKPOWERBIT)
   {
      FormatVariables(CurrentViewPreset.PowerMLR, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MPKPOWER_RLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MPKPOWER_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LPOWERMINUS;
}
/**---------------------------------------------**
 ** This function displays the + Time   R Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0053(void)
{
   if((CurrentViewPreset.RejectLimits & PTIMEBIT) != PTIMEBIT)
   {
      FormatVariables(CurrentViewPreset.TimePLR, TIME, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PTIME_RLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PTIME_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LTIMEPLUS;
}
  
/**---------------------------------------------**
 ** This function displays the - Time   R Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0054(void)
{
   if((CurrentViewPreset.RejectLimits & MTIMEBIT) != MTIMEBIT)
   {
      FormatVariables(CurrentViewPreset.TimeMLR, TIME, VGAMisc, 6, CurrentSetup.Units);
	   strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MTIME_RLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MTIME_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LTIMEMINUS;
}
 
/**-------------------------------------------------**
 ** This function displays the + Weld Force R Limit.**
 **-------------------------------------------------**/
void ViewPresetSetup0065(void)
{
   if((CurrentViewPreset.RejectLimits & PFORCEBIT) != PFORCEBIT)
   {
      FormatVariables(CurrentViewPreset.WeldForcePLR, FORCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PWELDFORCE_RLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PWELDFORCE_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LRMAXFORCE;  // LCOLLAPSEPLUS the same group
}
  
/**-------------------------------------------------**
 ** This function displays the - Weld Force R Limit.**
 **-------------------------------------------------**/
void ViewPresetSetup0066(void)
{
   if((CurrentViewPreset.RejectLimits & MFORCEBIT) != MFORCEBIT)
   {
      FormatVariables(CurrentViewPreset.WeldForceMLR, FORCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MWELDFORCE_RLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MWELDFORCE_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LRMAXFORCE;
}
  
/**-------------------------------------------------------**
 ** This function displays the + Trigger Distance R Limit.**
 **-------------------------------------------------------**/
void ViewPresetSetup0063(void)
{
   if((CurrentViewPreset.RejectLimits & PTRIGDISTBIT) != PTRIGDISTBIT)
   { 
      FormatVariables(CurrentViewPreset.TrsDistPLR, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PTRIGDIST_RLIMT_TXT;
  }
   else 
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PTRIGDIST_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LTRIGGERDISTPLUS;
}


/**-------------------------------------------------------**
 ** This function displays the - Trigger Distance R Limit.**
 **-------------------------------------------------------**/
void ViewPresetSetup0064(void)
{
   if((CurrentViewPreset.RejectLimits & MTRIGDISTBIT) != MTRIGDISTBIT)
   { 
      FormatVariables(CurrentViewPreset.TrsDistMLR, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MTRIGDIST_RLIMT_TXT;
   }
   else 
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MTRIGDIST_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LTRIGGERDISTMINUS;
}

/**-------------------------------------------------------**
 ** This function displays the + Power Band R Limit.**
 **-------------------------------------------------------**/
void ViewPresetSetup0081(void)
{
   if(!CurrentViewPreset.PMCPlusBandFlag)
   {
      ConvertNumberToString(CurrentViewPreset.PMCHighLimit);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = PPOWERBAND_RLIMT_TXT;
   }
   else 
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PPOWERBAND_RLIMT_OFF_TXT;
   }
   VGAPrintParam = ALWAYS;
}


/**-------------------------------------------------------**
 ** This function displays the - Power Band R Limit.**
 **-------------------------------------------------------**/
void ViewPresetSetup0082(void)
{
   if(!CurrentViewPreset.PMCMinusBandFlag)
   {
      ConvertNumberToString(CurrentViewPreset.PMCLowLimit);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = MPOWERBAND_RLIMT_TXT;
   }
   else 
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MPOWERBAND_RLIMT_OFF_TXT;
   }

   VGAPrintParam = ALWAYS;
}

/**-------------------------------------------------------**
 ** This function displays the + R SBL Frequency Limit.   **
 **-------------------------------------------------------**/
void ViewPresetSetup0083(void)
{
   if(!(CurrentViewPreset.SBLFreqFlags & BIT1))
   {
      ConvertNumberToString(CurrentViewPreset.SBLMaxFreq);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = PSBLFREQ_RLIMT_TXT;
   }
   else 
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PSBLFREQ_RLIMT_OFF_TXT;
   }

   VGAPrintParam = ALWAYS;
}

/**-------------------------------------------------------**
 ** This function displays the - R SBL Frequency Limit.   **
 **-------------------------------------------------------**/
void ViewPresetSetup0084(void)
{
   if(!(CurrentViewPreset.SBLFreqFlags & BIT0))
   {
      ConvertNumberToString(CurrentViewPreset.SBLMinFreq);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = MSBLFREQ_RLIMT_TXT;
   }
   else 
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MSBLFREQ_RLIMT_OFF_TXT;
   }

   VGAPrintParam = ALWAYS;
}
/**-----------------------------------------------**
 ** This function displays the + Collapse S Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0043(void)
{
   if((CurrentViewPreset.SuspectLimits & PCOLDISTBIT) != PCOLDISTBIT)
   {
      FormatVariables(CurrentViewPreset.ColPLS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = PCOL_SLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PCOL_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LCOLLAPSEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the - Collapse S Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0044(void)
{
   if((CurrentViewPreset.SuspectLimits & MCOLDISTBIT) != MCOLDISTBIT)
   {
      FormatVariables(CurrentViewPreset.ColMLS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = MCOL_SLIMT_TXT;
   }
   else
      
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MCOL_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LCOLLAPSEMINUS;
}

/**---------------------------------------------**
 ** This function displays the + Energy S Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0039(void)
{
   if((CurrentViewPreset.SuspectLimits & PENERGYBIT) != PENERGYBIT)
   {
      FormatVariables(CurrentViewPreset.EnergyPLS,
         /* cont'd */   CurrentViewPreset.EnergyPLS > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
         /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
		 strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = PENRGY_SLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PENRGY_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LENERGYPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Energy S Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0040(void)
{
   if((CurrentViewPreset.SuspectLimits & MENERGYBIT) != MENERGYBIT)
   {
      FormatVariables(CurrentViewPreset.EnergyMLS,
         /* cont'd */   CurrentViewPreset.EnergyMLS > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
         /* cont'd */   VGAMisc, 6, CurrentSetup.Units );
		 strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = MENRGY_SLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MENRGY_SLIMT_OFF_TXT;
   }
   VGAPrintParam = LENERGYMINUS;
}

/**-----------------------------------------------**
 ** This function displays the + Absolute S Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0045(void)
{
   if((CurrentViewPreset.SuspectLimits & PABSDISTBIT) != PABSDISTBIT)
   {
      FormatVariables(CurrentViewPreset.AbsPLS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = PABSOLUTE_SLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PABSOLUTE_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LABSOLUTEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the - Absolute S Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0046(void)
{
   if((CurrentViewPreset.SuspectLimits & MABSDISTBIT) != MABSDISTBIT)
   { 
      FormatVariables(CurrentViewPreset.AbsMLS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = MABSOLUTE_SLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MABSOLUTE_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LABSOLUTEMINUS;
}

/**---------------------------------------------**
 ** This function displays the + Power  S Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0041(void)
{
   if((CurrentViewPreset.SuspectLimits & PPKPOWERBIT) != PPKPOWERBIT)
   {
      FormatVariables(CurrentViewPreset.PowerPLS, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = PPKPOWER_SLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PPKPOWER_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LPOWERPLUS;
}


/**---------------------------------------------**
 ** This function displays the - Power  S Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0042(void)
{
   if((CurrentViewPreset.SuspectLimits & MPKPOWERBIT) != MPKPOWERBIT)
   {
      FormatVariables(CurrentViewPreset.PowerMLS, POWERWATTS, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = MPKPOWER_SLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MPKPOWER_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LPOWERMINUS;
}

/**---------------------------------------------**
 ** This function displays the + Time   S Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0037(void)
{
   if((CurrentViewPreset.SuspectLimits & PTIMEBIT) != PTIMEBIT)
   {
      FormatVariables(CurrentViewPreset.TimePLS, TIME, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = PTIME_SLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PTIME_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LTIMEPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Time   S Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0038(void)
{
   if((CurrentViewPreset.SuspectLimits & MTIMEBIT) != MTIMEBIT)
   { 
      FormatVariables(CurrentViewPreset.TimeMLS, TIME, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = MTIME_SLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MTIME_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LTIMEMINUS;
}

/**-------------------------------------------------**
 ** This function displays the + Weld Force S Limit.**
 **-------------------------------------------------**/
void ViewPresetSetup0049(void)
{
   if((CurrentViewPreset.SuspectLimits & PFORCEBIT) != PFORCEBIT)
   {
      FormatVariables(CurrentViewPreset.WeldForcePLS, FORCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = PWELDFORCE_SLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PWELDFORCE_SLIMT_OFF_TXT;
   }
   VGAPrintParam = LMAXFORCEPLUS;
}

/**-------------------------------------------------**
 ** This function displays the - Weld Force S Limit.**
 **-------------------------------------------------**/
void ViewPresetSetup0050(void)
{
   if((CurrentViewPreset.SuspectLimits & MFORCEBIT) != MFORCEBIT)
   {
      FormatVariables(CurrentViewPreset.WeldForceMLS, FORCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = MWELDFORCE_SLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MWELDFORCE_SLIMT_OFF_TXT;
   }
      
   VGAPrintParam = LMAXFORCEMINUS;
}

/**-------------------------------------------------------**
 ** This function displays the + Trigger Distance S Limit.**
 **-------------------------------------------------------**/
void ViewPresetSetup0047(void)
{
   if((CurrentViewPreset.SuspectLimits & PTRIGDISTBIT) != PTRIGDISTBIT)
   { 
      FormatVariables(CurrentViewPreset.TrsDistPLS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = PTRIGDIST_SLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PTRIGDIST_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LTRIGGERDISTPLUS;
}
  
/**-------------------------------------------------------**
 ** This function displays the - Trigger Distance S Limit.**
 **-------------------------------------------------------**/
void ViewPresetSetup0048(void)
{
   if((CurrentViewPreset.SuspectLimits & MTRIGDISTBIT) != MTRIGDISTBIT)
   { 
      FormatVariables(CurrentViewPreset.TrsDistMLS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = MTRIGDIST_SLIMT_TXT;
   }
   else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MTRIGDIST_SLIMT_OFF_TXT;
   }
   VGAPrintParam = LTRIGGERDISTMINUS;
}


/* ------- VQS Data -------------------- */


/**-----------------------------------------------**
 ** This function displays  the Weld Min Time **
 **-----------------------------------------------**/
void PrintVQSData0101(void)
{  
  if((CurrentPreset.VQSLimit & MTIMEBIT) != MTIMEBIT)
  {
   FormatVariables(CurrentPreset.WeldTimeMinVQS, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_WELDTIMEMIN_TXT;
  }
  else
  {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = VQS_WELDTIMEMIN_OFF_TXT;
   }
  VGAPrintParam = PWELDTIMEMIN;

}


/**-----------------------------------------------**
 ** This function displays  the Energy Min        **
 **-----------------------------------------------**/
void PrintVQSData0102(void)
{
  if((CurrentPreset.VQSLimit & MENERGYBIT) != MENERGYBIT)
  {
   FormatVariables(CurrentPreset.EnergyMinVQS, ENERGYDIV10, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_ENRGYMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_ENRGYMIN_OFF_TXT;
  }
  VGAPrintParam = PENERGYMIN;

}

/**-----------------------------------------------**
 ** This function displays  the Peak Power Min        **
 **-----------------------------------------------**/
void PrintVQSData0103(void)
{
  if((CurrentPreset.VQSLimit & MPKPOWERBIT) != MPKPOWERBIT)
  {
   FormatVariables(CurrentPreset.PeakPowerMinVQS, PERCENTX10, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_PKPOWERMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_PKPOWERMIN_OFF_TXT;
  }
  VGAPrintParam = PPEAKPOWERMIN;

}


/**-----------------------------------------------**
 ** This function displays  the Weld Collapse Min **
 **-----------------------------------------------**/
void PrintVQSData0104(void)
{
  if((CurrentPreset.VQSLimit & MWELDCOLLAPSEBIT) != MWELDCOLLAPSEBIT)
  {
   FormatVariables(CurrentPreset.WeldColMinVQS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_WELDCOLMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_WELDCOLMIN_OFF_TXT;
  }
  VGAPrintParam = PWELDCOLLAPSEMIN;
}

/**-----------------------------------------------**
 ** This function displays  the Total Collapse Min **
 **-----------------------------------------------**/
void PrintVQSData0105(void)
{
  if((CurrentPreset.VQSLimit & MCOLDISTBIT) != MCOLDISTBIT)
  {
   FormatVariables(CurrentPreset.TotalColMinVQS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_TOTALCOLMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_TOTALCOLMIN_OFF_TXT;
  }
  VGAPrintParam = PTOTALCOLLAPSEMIN;
}



/**-----------------------------------------------**
 ** This function displays  the Total Absolute Min **
 **-----------------------------------------------**/
void PrintVQSData0107(void)
{
  if((CurrentPreset.VQSLimit & MABSDISTBIT) != MABSDISTBIT)
  { 
   FormatVariables(CurrentPreset.TotalAbsMinVQS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_TOTALABSMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_TOTALABSLMIN_OFF_TXT;
  }
  VGAPrintParam = PTOTALABSOLUTEMIN;
}

/**-----------------------------------------------**
 ** This function displays  the Weld Force  Min   **
 **-----------------------------------------------**/
void PrintVQSData0108(void)
{
  if((CurrentPreset.VQSLimit & MFORCEBIT) != MFORCEBIT)
  {
   FormatVariables(CurrentPreset.WeldForceMinVQS, FORCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_WELDFORCEMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_WELDFORCEMIN_OFF_TXT;
  }
  VGAPrintParam = PWELDFORCEMIN;
}

/**-----------------------------------------------**
 ** This function displays  the Total Cycle Time Min **
 **-----------------------------------------------**/
void PrintVQSData0109(void)
{
  if((CurrentPreset.VQSLimit & MTOTCYCLETIMEBIT) != MTOTCYCLETIMEBIT)
  {
   FormatVariables(CurrentPreset.TotalCycleTimeMinVQS, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_TOTALCYCLETIMEMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_TOTALCYCLETIMEMIN_OFF_TXT;
  }
  VGAPrintParam = PTOTALCYCLETIMEMIN;
}


/**-----------------------------------------------**
 ** This function displays  the Weld Max Time **
 **-----------------------------------------------**/
void PrintVQSData0110(void)
{
  if((CurrentPreset.VQSLimit & PTIMEBIT) != PTIMEBIT)
  {
   FormatVariables(CurrentPreset.WeldTimeMaxVQS, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_WELDTIMEMAX_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_WELDTIMEMAX_OFF_TXT;
  }
  VGAPrintParam = PWELDTIMEMAX;
}


/**-----------------------------------------------**
 ** This function displays  the Energy Max        **
 **-----------------------------------------------**/
void PrintVQSData0111(void)
{
  if((CurrentPreset.VQSLimit & PENERGYBIT) != PENERGYBIT)
  {
   FormatVariables(CurrentPreset.EnergyMaxVQS, ENERGYDIV10, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_ENRGYMAX_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_ENRGYMAX_OFF_TXT;
  }
  VGAPrintParam = PENERGYMAXIMUM;
}


/**-----------------------------------------------**
 ** This function displays  the Peak Power Max        **
 **-----------------------------------------------**/
void PrintVQSData0112(void)
{
  if((CurrentPreset.VQSLimit & PPKPOWERBIT) != PPKPOWERBIT)
  {
   FormatVariables(CurrentPreset.PeakPowerMaxVQS, PERCENTX10, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_PKPOWERMAX_TXT;
   
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_PKPOWERMAX_OFF_TXT;
  }
  VGAPrintParam = PPEAKPOWERMAX;
}

 /** This function displays  the Weld Collapse Max **
 **-----------------------------------------------**/
void PrintVQSData0113(void)
{
  if((CurrentPreset.VQSLimit & PWELDCOLLAPSEBIT) != PWELDCOLLAPSEBIT)
  {
   FormatVariables(CurrentPreset.WeldColMaxVQS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_WELDCOLMAX_TXT;
   
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_WELDCOLMAX_OFF_TXT;
  }
  VGAPrintParam = PWELDCOLLAPSEMAX;
}

/**-----------------------------------------------**
 ** This function displays  the Total Collapse Max **
 **-----------------------------------------------**/
void PrintVQSData0114(void)
{
  if((CurrentPreset.VQSLimit & PCOLDISTBIT) != PCOLDISTBIT)
  {
   FormatVariables(CurrentPreset.TotalColMaxVQS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_TOTALCOLMAX_TXT;
   
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_TOTALCOLMAX_OFF_TXT;
  }
  VGAPrintParam = PTOTALCOLLAPSEMAX;
}


/**-----------------------------------------------**
 ** This function displays  the Total Absolute Max **
 **-----------------------------------------------**/
void PrintVQSData0116(void)
{
  if((CurrentPreset.VQSLimit & PABSDISTBIT) != PABSDISTBIT)
  {
   FormatVariables(CurrentPreset.TotalAbsMaxVQS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_TOTALABSMAX_TXT;
  
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_TOTALABSLMAX_OFF_TXT;
  }
  VGAPrintParam = PTOTALABSOLUTEMAX;
}

/**-----------------------------------------------**
 ** This function displays  the Weld Force  Max   **
 **-----------------------------------------------**/
void PrintVQSData0117(void)
{
  if((CurrentPreset.VQSLimit & PFORCEBIT) != PFORCEBIT)
  {
   FormatVariables(CurrentPreset.WeldForceMaxVQS, FORCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_WELDFORCEMAX_TXT;
   
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_WELDFORCEMAX_OFF_TXT;
  }

  VGAPrintParam = PWELDFORCEMAX;
}

/**-----------------------------------------------**
 ** This function displays  the Total Cycle Time Max **
 **-----------------------------------------------**/
void PrintVQSData0118(void)
{
  if((CurrentPreset.VQSLimit & PTOTCYCLETIMEBIT) != PTOTCYCLETIMEBIT)
  {
   FormatVariables(CurrentPreset.TotalCycleTimeMaxVQS, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_TOTALCYCLETIMEMAX_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_TOTALCYCLETIMEMAX_OFF_TXT;
  }
  VGAPrintParam = PTOTALCYCLETIMEMAX;
}

/* ------- View Preset VQS Data -------------------- */


/**-----------------------------------------------**
 ** This function displays  the Weld Min Time **
 **-----------------------------------------------**/
void ViewPrintVQSData0101(void)
{  
  if((CurrentViewPreset.VQSLimit & MTIMEBIT) != MTIMEBIT)
  {
   FormatVariables(CurrentViewPreset.WeldTimeMinVQS, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_WELDTIMEMIN_TXT;
  }
  else
  {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = VQS_WELDTIMEMIN_OFF_TXT;
   }
  VGAPrintParam = PWELDTIMEMIN;

}


/**-----------------------------------------------**
 ** This function displays  the Energy Min        **
 **-----------------------------------------------**/
void ViewPrintVQSData0102(void)
{
  if((CurrentViewPreset.VQSLimit & MENERGYBIT) != MENERGYBIT)
  {
   FormatVariables(CurrentViewPreset.EnergyMinVQS, ENERGYDIV10, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_ENRGYMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_ENRGYMIN_OFF_TXT;
  }
  VGAPrintParam = PENERGYMIN;

}

/**-----------------------------------------------**
 ** This function displays  the Peak Power Min        **
 **-----------------------------------------------**/
void ViewPrintVQSData0103(void)
{
  if((CurrentViewPreset.VQSLimit & MPKPOWERBIT) != MPKPOWERBIT)
  {
   FormatVariables(CurrentViewPreset.PeakPowerMinVQS, PERCENTX10, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_PKPOWERMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_PKPOWERMIN_OFF_TXT;
  }
  VGAPrintParam = PPEAKPOWERMIN;

}


/**-----------------------------------------------**
 ** This function displays  the Weld Collapse Min **
 **-----------------------------------------------**/
void ViewPrintVQSData0104(void)
{
  if((CurrentViewPreset.VQSLimit & MWELDCOLLAPSEBIT) != MWELDCOLLAPSEBIT)
  {
   FormatVariables(CurrentViewPreset.WeldColMinVQS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_WELDCOLMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_WELDCOLMIN_OFF_TXT;
  }
  VGAPrintParam = PWELDCOLLAPSEMIN;
}

/**-----------------------------------------------**
 ** This function displays  the Total Collapse Min **
 **-----------------------------------------------**/
void ViewPrintVQSData0105(void)
{
  if((CurrentViewPreset.VQSLimit & MCOLDISTBIT) != MCOLDISTBIT)
  {
   FormatVariables(CurrentViewPreset.TotalColMinVQS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_TOTALCOLMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_TOTALCOLMIN_OFF_TXT;
  }
  VGAPrintParam = PTOTALCOLLAPSEMIN;
}



/**-----------------------------------------------**
 ** This function displays  the Total Absolute Min **
 **-----------------------------------------------**/
void ViewPrintVQSData0107(void)
{
  if((CurrentViewPreset.VQSLimit & MABSDISTBIT) != MABSDISTBIT)
  { 
   FormatVariables(CurrentViewPreset.TotalAbsMinVQS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_TOTALABSMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_TOTALABSLMIN_OFF_TXT;
  }
  VGAPrintParam = PTOTALABSOLUTEMIN;
}

/**-----------------------------------------------**
 ** This function displays  the Weld Force  Min   **
 **-----------------------------------------------**/
void ViewPrintVQSData0108(void)
{
  if((CurrentViewPreset.VQSLimit & MFORCEBIT) != MFORCEBIT)
  {
   FormatVariables(CurrentViewPreset.WeldForceMinVQS, FORCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_WELDFORCEMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_WELDFORCEMIN_OFF_TXT;
  }
  VGAPrintParam = PWELDFORCEMIN;
}

/**-----------------------------------------------**
 ** This function displays  the Total Cycle Time Min **
 **-----------------------------------------------**/
void ViewPrintVQSData0109(void)
{
  if((CurrentViewPreset.VQSLimit & MTOTCYCLETIMEBIT) != MTOTCYCLETIMEBIT)
  {
   FormatVariables(CurrentViewPreset.TotalCycleTimeMinVQS, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_TOTALCYCLETIMEMIN_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_TOTALCYCLETIMEMIN_OFF_TXT;
  }
  VGAPrintParam = PTOTALCYCLETIMEMIN;
}


/**-----------------------------------------------**
 ** This function displays  the Weld Max Time **
 **-----------------------------------------------**/
void ViewPrintVQSData0110(void)
{
  if((CurrentViewPreset.VQSLimit & PTIMEBIT) != PTIMEBIT)
  {
   FormatVariables(CurrentViewPreset.WeldTimeMaxVQS, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_WELDTIMEMAX_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_WELDTIMEMAX_OFF_TXT;
  }
  VGAPrintParam = PWELDTIMEMAX;
}


/**-----------------------------------------------**
 ** This function displays  the Energy Max        **
 **-----------------------------------------------**/
void ViewPrintVQSData0111(void)
{
  if((CurrentViewPreset.VQSLimit & PENERGYBIT) != PENERGYBIT)
  {
   FormatVariables(CurrentViewPreset.EnergyMaxVQS, ENERGYDIV10, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_ENRGYMAX_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_ENRGYMAX_OFF_TXT;
  }
  VGAPrintParam = PENERGYMAXIMUM;
}


/**-----------------------------------------------**
 ** This function displays  the Peak Power Max        **
 **-----------------------------------------------**/
void ViewPrintVQSData0112(void)
{
  if((CurrentViewPreset.VQSLimit & PPKPOWERBIT) != PPKPOWERBIT)
  {
   FormatVariables(CurrentViewPreset.PeakPowerMaxVQS, PERCENTX10, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_PKPOWERMAX_TXT;
   
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_PKPOWERMAX_OFF_TXT;
  }
  VGAPrintParam = PPEAKPOWERMAX;
}

 /** This function displays  the Weld Collapse Max **
 **-----------------------------------------------**/
void ViewPrintVQSData0113(void)
{
  if((CurrentViewPreset.VQSLimit & PWELDCOLLAPSEBIT) != PWELDCOLLAPSEBIT)
  {
   FormatVariables(CurrentViewPreset.WeldColMaxVQS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_WELDCOLMAX_TXT;
   
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_WELDCOLMAX_OFF_TXT;
  }
  VGAPrintParam = PWELDCOLLAPSEMAX;
}

/**-----------------------------------------------**
 ** This function displays  the Total Collapse Max **
 **-----------------------------------------------**/
void ViewPrintVQSData0114(void)
{
  if((CurrentViewPreset.VQSLimit & PCOLDISTBIT) != PCOLDISTBIT)
  {
   FormatVariables(CurrentViewPreset.TotalColMaxVQS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_TOTALCOLMAX_TXT;
   
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_TOTALCOLMAX_OFF_TXT;
  }
  VGAPrintParam = PTOTALCOLLAPSEMAX;
}


/**-----------------------------------------------**
 ** This function displays  the Total Absolute Max **
 **-----------------------------------------------**/
void ViewPrintVQSData0116(void)
{
  if((CurrentViewPreset.VQSLimit & PABSDISTBIT) != PABSDISTBIT)
  {
   FormatVariables(CurrentViewPreset.TotalAbsMaxVQS, DISTANCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_TOTALABSMAX_TXT;
  
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_TOTALABSLMAX_OFF_TXT;
  }
  VGAPrintParam = PTOTALABSOLUTEMAX;
}

/**-----------------------------------------------**
 ** This function displays  the Weld Force  Max   **
 **-----------------------------------------------**/
void ViewPrintVQSData0117(void)
{
  if((CurrentViewPreset.VQSLimit & PFORCEBIT) != PFORCEBIT)
  {
   FormatVariables(CurrentViewPreset.WeldForceMaxVQS, FORCE, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_WELDFORCEMAX_TXT;
   
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_WELDFORCEMAX_OFF_TXT;
  }

  VGAPrintParam = PWELDFORCEMAX;
}

/**-----------------------------------------------**
 ** This function displays  the Total Cycle Time Max **
 **-----------------------------------------------**/
void ViewPrintVQSData0118(void)
{
  if((CurrentViewPreset.VQSLimit & PTOTCYCLETIMEBIT) != PTOTCYCLETIMEBIT)
  {
   FormatVariables(CurrentViewPreset.TotalCycleTimeMaxVQS, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = VQS_TOTALCYCLETIMEMAX_TXT;
  }
  else
  {
     Value = 0;
     ValueFlag = TRUE;
     Val_ID = VQS_TOTALCYCLETIMEMAX_OFF_TXT;
  }
  VGAPrintParam = PTOTALCYCLETIMEMAX;
}

/**------------------------------------------------------------------**
 ** This function prepares left section of preset parameter printing **
 **------------------------------------------------------------------**/
void VGA_PresetSetup1(UINT8 * *AckBuf, SINT8 String[], UINT16 param, UINT8 Data, UINT16 ID)
{
   if(CheckIfPrintable(param) && (VGAPrintParam == param))  
   {
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(ID >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(ID));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(LeftPrintXCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(LeftPrintXCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(LeftPrintYCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(LeftPrintYCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf, Font_Print);

	  if(ValueFlag == TRUE)
	  {
		  VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(Data));
	  }
	  else
	  {
        if(Data == 2)
            VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(Data));
		  VGAPrintLength += AddToBuffer(AckBuf, LangStrLen(String));			           
		  VGAPrintLength += AddToBufferString(AckBuf, String, LangStrLen(String));
	  }
      LeftPrintYCoordinate = LeftPrintYCoordinate + PRINT_LINE_HEIGHT;
   }
} 


/**------------------------------------------------------------------**
 ** This function prepares right section of preset parameter printing **
 **------------------------------------------------------------------**/
void VGA_PresetSetup2(UINT8 * *AckBuf, SINT8 String[], UINT16 param, UINT8 Data, UINT16 ID)
{
   if(CheckIfPrintable(param) && (VGAPrintParam == param))  
   {
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(ID >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(ID));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(RightPrintXCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(RightPrintXCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(RightPrintYCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(RightPrintYCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf, Font_Print);

	  if(ValueFlag == TRUE)
	  {
		  VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(Data));
	  }
	  else
	  {
        if(Data == 2)
           VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(Data));

		  VGAPrintLength += AddToBuffer(AckBuf, LangStrLen(String));			           
		  VGAPrintLength += AddToBufferString(AckBuf, String, LangStrLen(String));
	  }
      RightPrintYCoordinate = RightPrintYCoordinate + PRINT_LINE_HEIGHT;

   }
}

/**------------------------------------------------------------------**
 ** This function prepares Reject limit parameter printing section   **
 **------------------------------------------------------------------**/
void VGA_RejLimPresetSetup1(UINT8 * *AckBuf, SINT8 String[], UINT16 param, UINT8 Data, UINT16 ID)
{
   if(ControlLevelLimit(param) && (VGAPrintParam == param))  
   {
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(ID >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(ID));

      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(LeftPrintXCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(LeftPrintXCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(LeftPrintYCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(LeftPrintYCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf, Font_Print);

	  if(ValueFlag)
		  VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(Data));
	  else
	  {
        if(Data == 2)
            VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(Data));
		  VGAPrintLength += AddToBuffer(AckBuf, LangStrLen(String));			           
		  VGAPrintLength += AddToBufferString(AckBuf, String, LangStrLen(String));
	  }
      LeftPrintYCoordinate = LeftPrintYCoordinate + PRINT_LINE_HEIGHT;
   }
}

void VGA_SusLimPresetSetup2(UINT8 * *AckBuf, SINT8 String[], UINT16 param, UINT8 Data, UINT16 ID)
/**------------------------------------------------------------------**
 ** This function prepares Suspect limit parameter printing section  **
 **------------------------------------------------------------------**/
{
   if(ControlLevelLimit(param) && (VGAPrintParam == param))  
   {
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(ID >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(ID));

      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(RightPrintXCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(RightPrintXCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(RightPrintYCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(RightPrintYCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf, Font_Print);

	   if(ValueFlag)
		  VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(Data));
	   else
      {
        if(Data == 2)
           VGAPrintLength += AddToBuffer(AckBuf, (UINT8)(Data));

		  VGAPrintLength += AddToBuffer(AckBuf, LangStrLen(String));			           
		  VGAPrintLength += AddToBufferString(AckBuf, String, LangStrLen(String));
      }
      RightPrintYCoordinate = RightPrintYCoordinate + PRINT_LINE_HEIGHT;
   }
}
/**********************************************************************/

UINT16 SystemViewPresetReport(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints one half of 1st preset page report          **
 **------------------------------------------------------------------**/
{
   UINT8 VGAPageNumber = 1;
   UINT16 param;
   
   VGAPrintLength = 0;
   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   LeftPrintYCoordinate = LEFT_YCOORDINATE;
   RightPrintYCoordinate = RIGHT_YCOORDINATE;
   Font_Print = FONT_PRINTBOLD;
   VGAMisc[VGAMISCLEN] = 0x00; 
   VGAMisc[VGAMISCLEN+1] = 0x00; 
   
  

   /* Left half-page */
   LeftPrintYCoordinate += (PRINT_LINE_HEIGHT*4);
   RightPrintYCoordinate += (PRINT_LINE_HEIGHT*4);
   Font_Print = FONT_PRINT;
   
   param = ViewPresetSetup0002();     /* Weld Time or Weld Energy or ..., based on Weld Mode */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);
   param = ViewPresetSetup0003();     /* Weld Time or Weld Energy or ..., based on Weld Mode */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);
   if(CurrentViewPreset.WeldMode == GRDDETECTMODE)
   {
      ViewPresetSetup0003A();
      VGA_PresetSetup1(&AckBuf, VGABuffer, PSCRUBAMPLITUDE,Value, Val_ID);
   }
   ViewPresetSetup0015();     /* Amplitude */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEA,Value, Val_ID);
   VGAPrintParam = ALWAYS;
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   ViewPresetSetup0016();     /* Amplitude(A) if amplitude step is on */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEA1, Value, Val_ID);
   ViewPresetSetup0017();     /* Amplitude(B) if amplitude step is on */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEB, Value, Val_ID);
   param = ViewPresetSetup0018A();    /* Amplitude Step at Time, Step at Energy, ... */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   ViewPresetSetup0019();     /* Pretrigger Flag - On or Off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRETRIGGER, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   ViewPresetSetup0019B();    /* Auto Pretrigger Flag - On or Off, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAUTOPRETRIGGER, Value, Val_ID);
   ViewPresetSetup0019A();    /* Pretrigger Distance, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRETRIGGERDISTANCE, Value, Val_ID);
   ViewPresetSetup0021();     /* Pretrigger Amplitude, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRETRIGGERAMP, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   ViewPresetSetup0070();     /* Max Timeout */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PMAXTIMEOUT, Value, Val_ID);
    ViewPresetSetup0070A();    /* External Trigger Delay */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PEXTTRIGDLY, Value, Val_ID);

   /* Right half-page */
   ViewPresetSetup0004();     /* Hold Time */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PHOLDTIME, Value, Val_ID);
   ViewPresetSetup0022();     /* Afterburst - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURST, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   ViewPresetSetup0023();     /* Afterburst Delay, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURSTDELAY, Value, Val_ID);
   ViewPresetSetup0024();     /* Afterburst Time, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURSTTIME, Value, Val_ID);
   ViewPresetSetup0025();     /* Afterburst Amplitude, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURSTAMP, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   ViewPresetSetup0025A();    /* Energy Braking - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYBRAKING, Value, Val_ID);
   ViewPresetSetup0026();     /* Post Weld Seek - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPOSTWELDSEEK, Value, Val_ID);
   ViewPresetSetup0027();     /* Frequency Offset */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PFREQCONTROL, Value, Val_ID);
   ViewPresetConfig0081();    /* Digital Tune */
   VGA_PresetSetup2(&AckBuf, VGABuffer, DIGITALTUNE, Value, Val_ID);
   ViewPresetSetup0067();     /* Test Amplitude */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PTESTAMPLITUDE, Value, Val_ID);
   ViewPresetConfig0033();    /* Actuator Clear Output - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PACTCLEAROUTPUT, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   ViewPresetConfig0033A();   /* Actuator Clear Distance, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PACTCLEARDISTANCE, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   
   /* Left half-page */
   ViewPresetSetup0071();     /* Cycle Abort - On or Off (forces blank line in right half-page) */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCYCLEABORTS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   ViewPresetSetup0033();     /* Ground Detect Abort - On or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PSCRUBTIME, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   /* Right half-page */
   ViewPresetConfig0071();    /* Missing Part - On or Off or N/A */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PMISSINGPARTFLAG, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   ViewPresetConfig0072();    /* Missing Part Abort Min - Distance or Off or N/A, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PMISSINGPARTMIN, Value, Val_ID);
   ViewPresetConfig0073();    /* Missing Part Abort Max - Distance or Off or N/A, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PMISSINGPARTMAX, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;

   /* Left half-page */
   ViewPresetSetup0028();     /* Control Limits - On or Off (forces blank line in right half-page) */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCONTROLLIMITS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   ViewPresetSetup0034B();    /* Collapse Cutoff - Distance or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCOLLAPSECUTOFF, Value, Val_ID);
   ViewPresetSetup0034A();    /* Absolute Cutoff - Distance or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PABSOLUTECUTOFF, Value, Val_ID);
   ViewPresetSetup0032();     /* Peak Power Cutoff - Percent or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPKPOWERCUTOFF, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   /* Right half-page */
   ViewPresetSetup0029();     /* Energy Compensation - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYCOMP, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   ViewPresetSetup0031();     /* Max. Energy - in Joules, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYMAX, Value, Val_ID);
   ViewPresetSetup0030();     /* Min. Energy - in Joules, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENGERGYMIN, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   
   if(CurrentSetup.Actuator == AEF){

      /* Left half-page */  
      DisplayAEFSetting();  /* aef/aof message (forces blank line in right half-page) */
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      ViewPresetSetup0012();   /* Rapid Traverse - On or Off */ 
      VGA_PresetSetup1(&AckBuf, VGABuffer, PRAPIDTRAVS, Value, Val_ID);
      LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
      ViewPresetSetup0013();   /* Rapid Traverse Distance, indented */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PRAPIDTRAVS, Value, Val_ID);
      LeftPrintXCoordinate = LEFT_XCOORDINATE;

      ViewPresetSetup0014();   /* Downspeed percent */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PDOWNSPEED, Value, Val_ID);
      ViewPresetSetup0005();   /* Trigger Force */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PTRIGGERFORCE, Value, Val_ID);
      ViewPresetSetup0007();   /* Weld Force - force or step */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDFORCEA, Value, Val_ID);
      LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
      ViewPresetSetup0008();   /* Weld Force(A), indented */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDFORCEA1, Value, Val_ID);
      ViewPresetSetup0009();   /* Weld Force(B), indented */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDFORCEB, Value, Val_ID);
      param = ViewPresetSetup0018B();  /* Step at Time/Energy/Power/Distance/Force/External Signal, indented */ 
      VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);
      LeftPrintXCoordinate = LEFT_XCOORDINATE;
     
	 /* Right half-page */
      ViewPresetSetup0011();   /* Hold Force */
      VGA_PresetSetup2(&AckBuf, VGABuffer, PHOLDFORCE, Value, Val_ID);
      ViewPresetSystemPressure();
      VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      if(CurrentSetup.ControlLevel >= LEVEL_f)
      {
         PrintForceRamp();  /* Force Ramps heading */
         VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
         RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
         ViewPresetWeldRate();     /* Weld Force Rate, indented */
         VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
         ViewPresetStepRate();     /* Step Force Rate, indented */
         VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
         ViewPresetHoldRate();     /* Hold Force Rate, indented */
         VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
         RightPrintXCoordinate = RIGHT_XCOORDINATE;
      }
   }
   else if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) ) {
      
      /* Left half-page */
      PrintAEDSetting();      /* aed/aod/MICRO message (forces blank line in right half-page) */
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      ViewPresetAEDTrigForce();    /* Trigger Force */
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
     
      
      /* Right half-page */
      PrintSystemPressure();      /* Act. Gauge Pressure */
      VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   }

   /*---------------------------------- SystemViewPresetReport2------------------------ */
   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;

   if((DUPS_Info.DUPSFlag)&&(ViewDupsPresent))
   {
      /* Print Digital UPS subheading */
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = DUPS_TXT;
      VGAPrintParam = ALWAYS;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      /* Put blank line in right half-page */
      RightPrintYCoordinate += PRINT_LINE_HEIGHT;

      /*--           *left half-page*           --*/
      /* Ramp Time */
      FormatVariables(DUPS_HostParamSet.WeldRampTime, TIME, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = DUPS_RAMPTIME_TXT;
      VGAPrintParam = PDUPSRAMPTIME;
      VGA_PresetSetup1(&AckBuf, VGABuffer, PDUPSRAMPTIME, Value, Val_ID);

      /* Memory - On or Off */
	     Value = (UINT8)DUPS_Info.DUPSMemFlag;
      ValueFlag = TRUE;
      Val_ID = DUPS_MEMRY_TXT;
      VGAPrintParam = PMEMORY;
      VGA_PresetSetup1(&AckBuf, VGABuffer, PMEMORY, Value, Val_ID);
   
      /* Weld Status - On or Off */
	     Value = (UINT8)CurrentViewPreset.WeldStatusFlag;
      ValueFlag = TRUE;
      Val_ID = WELDSTATUS_TXT;
      VGAPrintParam = PWELDSTATUS;
      VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDSTATUS, Value, Val_ID);   

      /*--           *right half-page*           --*/
      /* Select - Name */ 
      strcpy(VGABuffer, DUPS_HostParamSetName);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = SELECTNAME_TXT;
      VGAPrintParam = PSELECTNAME;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PSELECTNAME, Value, Val_ID);

      /* Seek Time */
      FormatVariables(DUPS_HostParamSet.SeekTime, TIME, VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = SEEKTIME_TXT;
      VGAPrintParam = PSEEKTIME;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PSEEKTIME, Value, Val_ID);

      /* Timed Seek - On or Off */
      Value = DUPS_Info.DUPSSeekFlag;
      ValueFlag = TRUE;
      Val_ID = TIMEDSEEK_TXT;
	     VGAPrintParam = PTIMEDSEEK;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PTIMEDSEEK, Value, Val_ID);
   }
   /* Print Write In Fields for both Analog/Digital PS * /
   /* WriteIn Field1 */
   strcpy(VGABuffer, CurrentViewPreset.WriteIn1);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = WRITEINFLD1_TXT;
   VGAPrintParam = PWRITEINFIELD;
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWRITEINFIELD, Value, Val_ID);
   
   /* WriteIn Field2 */ 
   strcpy(VGABuffer, CurrentViewPreset.WriteIn2);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = WRITEINFLD2_TXT;
   VGAPrintParam = PWRITEINFIELD;
   VGA_PresetSetup2(&AckBuf, VGABuffer, PWRITEINFIELD, Value, Val_ID);


   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   
   if (CurrentSetup.ControlLevel > LEVEL_t){ //only string is here.
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = LIMITS_TXT;
      VGAPrintParam = ALWAYS;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      AssignYCoordinate();
   }

   /* Left half-page */
   ViewPresetSetup0051();          /* Reject Limits - On or Off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PREJECTLIMITS, Value, Val_ID);
   ViewPresetSetup0052();          /* Reject Reset Required - On or Off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PREJRESETREQ, Value, Val_ID);
   
   /* Right half-page */
   ViewPresetSetup0035();          /* Suspect Limits - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PSUSPECTLIMITS, Value, Val_ID);
   ViewPresetSetup0036();          /* Suspect Reset Required - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PSUSPRESETREQ, Value, Val_ID);

   /* left half-page */
   ViewPresetSetup0059();          /* display the + Collapse R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LCOLLAPSEPLUS, Value, Val_ID);
   ViewPresetSetup0060();          /* display the - Collapse R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LCOLLAPSEMINUS, Value, Val_ID);
   ViewPresetSetup0055();          /* display the + Energy R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LENERGYPLUS, Value, Val_ID);
   ViewPresetSetup0056();          /* display the - Energy R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LENERGYMINUS, Value, Val_ID);
   ViewPresetSetup0061();          /* display the + Absolute R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LABSOLUTEPLUS, Value, Val_ID);
   ViewPresetSetup0062();          /* display the - Absolute R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LABSOLUTEMINUS, Value, Val_ID);
   ViewPresetSetup0057();          /* display the + Power  R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LPOWERPLUS, Value, Val_ID);
   ViewPresetSetup0058();          /* display the - Power  R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LPOWERMINUS, Value, Val_ID);
   ViewPresetSetup0053();          /* display the + Time   R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTIMEPLUS, Value, Val_ID);
   ViewPresetSetup0054();          /* display the - Time   R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTIMEMINUS, Value, Val_ID);
   ViewPresetSetup0065();          /* display the + Weld Force R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LRMAXFORCE, Value, Val_ID);
   ViewPresetSetup0066();          /* display the - Weld Force R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LRMAXFORCE, Value, Val_ID);
   ViewPresetSetup0063();          /* display the + Trigger Distance R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTRIGGERDISTPLUS, Value, Val_ID);
   ViewPresetSetup0064();          /* display the - Trigger Distance R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTRIGGERDISTMINUS, Value, Val_ID);
   ViewPresetSetup0081();          /* display the +Power band R Limit */
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   ViewPresetSetup0082();          /* display the - Power band R Limit */
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   if (DUPS_Info.DUPSFlag && CurrentSetup.SBLEnable)
   {
      ViewPresetSetup0083();          /* display the +SBL Freq R Limit */
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      ViewPresetSetup0084();          /* display the -SBL Freq R Limit */
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   }

   /* right half-page */
   ViewPresetSetup0043();          /* display the + Collapse S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LCOLLAPSEPLUS, Value, Val_ID);
   ViewPresetSetup0044();          /* display the - Collapse S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LCOLLAPSEMINUS, Value, Val_ID);
   ViewPresetSetup0039();          /* display the + Energy S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LENERGYPLUS, Value, Val_ID);
   ViewPresetSetup0040();          /* display the - Energy S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LENERGYMINUS, Value, Val_ID);
   ViewPresetSetup0045();          /* display the + Absolute S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LABSOLUTEPLUS, Value, Val_ID);
   ViewPresetSetup0046();          /* display the - Absolute S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LABSOLUTEMINUS, Value, Val_ID);
   ViewPresetSetup0041();          /* display the + Power  S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LPOWERPLUS, Value, Val_ID);
   ViewPresetSetup0042();          /* display the - Power  S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LPOWERMINUS, Value, Val_ID);
   ViewPresetSetup0037();          /* display the + Time   S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTIMEPLUS, Value, Val_ID);
   ViewPresetSetup0038();          /* display the - Time   S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTIMEMINUS, Value, Val_ID);
   ViewPresetSetup0049();          /* display the + Weld Force S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LMAXFORCEPLUS, Value, Val_ID);
   ViewPresetSetup0050();          /* display the - Weld Force S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LMAXFORCEMINUS, Value, Val_ID);
   ViewPresetSetup0047();          /* display the + Trigger Distance S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTRIGGERDISTPLUS, Value, Val_ID);
   ViewPresetSetup0048();          /* display the - Trigger Distance S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTRIGGERDISTMINUS, Value, Val_ID);


   /* left half-page */

   AssignYCoordinate();
   LeftPrintYCoordinate += PRINT_LINE_HEIGHT;
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = VQS_TXT;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   RightPrintYCoordinate += PRINT_LINE_HEIGHT;

   ViewPrintVQSData0101();        /* display Weld Time Min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDTIMEMIN, Value, Val_ID);
   ViewPrintVQSData0102();        /* display the Energy Min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PENERGYMIN, Value, Val_ID);
   ViewPrintVQSData0103();        /* display Peak Power Min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPEAKPOWERMIN, Value, Val_ID);
   ViewPrintVQSData0104();       /* display Weld Collapse Min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDCOLLAPSEMIN, Value, Val_ID);
   ViewPrintVQSData0105();        /* display total collapse min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PTOTALCOLLAPSEMIN, Value, Val_ID);
   ViewPrintVQSData0107();        /* display Total Absolute Min*/
   VGA_PresetSetup1(&AckBuf, VGABuffer, PTOTALABSOLUTEMIN, Value, Val_ID);
   ViewPrintVQSData0108();        /* display weld force Min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDFORCEMIN, Value, Val_ID);
   ViewPrintVQSData0109();        /* dispaly Total cycle min */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PTOTALCYCLETIMEMIN, Value, Val_ID);
    
    /* right half-page */   
  
   
   ViewPrintVQSData0110();        /* display Weld Time Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PWELDTIMEMAX, Value, Val_ID);
   ViewPrintVQSData0111();        /* display the Energy Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYMAXIMUM, Value, Val_ID);
   ViewPrintVQSData0112();        /* display Peak Power Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPEAKPOWERMAX, Value, Val_ID);
   ViewPrintVQSData0113();       /* display Weld Collapse Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PWELDCOLLAPSEMAX, Value, Val_ID);
   ViewPrintVQSData0114();        /* display total collapse Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PTOTALCOLLAPSEMAX, Value, Val_ID);
   ViewPrintVQSData0116();        /* display Total Absolute Max*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, PTOTALABSOLUTEMAX, Value, Val_ID);
   ViewPrintVQSData0117();        /* display weld force Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PWELDFORCEMAX, Value, Val_ID);
   ViewPrintVQSData0118();        /* dispaly Total cycle Max */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PTOTALCYCLETIMEMAX, Value, Val_ID);

   return (VGAPrintLength);

}

