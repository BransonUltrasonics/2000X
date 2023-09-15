/* $Header:   D:/SWLab/VMdb/2000Series/App/PR_PRINT.C_V   1.259   22 Sep 2009 11:59:28   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 2009           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: pr_print.c
       
 ----------------------------- REVISIONS ------------------------------------

   Revision #     Date        Author  Description
   ----------     -------     ------  -----------
   0              09-14-96    GR      Initial
   1.01           09-30-96    PaulG   Add FinalData function.
   1.02           10-22-96    PaulG   Modified PrintSheet().
   1.03           10-24-96    PaulG   Set UNITS to either Metric
                                      or USCS whichever is active.
   1.04           10-31-96    PaulG   Modified System Alarms
   1.05           11-07-96    PaulG   Modified PrintAlarms
   1.06           11-13-96    PaulG   Added PRESETPRN case, and check
                                      for GlobalSample and GlobalAlarm.   
   1.07           11-14-96    PaulG   Added messages if printer flags were off.
   1.08           11-20-96    PaulG   Added GlobalSampleFlag and GlobalAlarmFlag.
   1.09           12-03-96    PaulG   Removed messages from switch statement.
   1.10           12-10-96    PaulG   Added PrintAnyway flag.
   1.11           12-17-96    PaulG   Removed Prsetprn.h.
   1.12           12-19-96    PaulG   Added form feed feature
   1.13           01-10-97    PaulG   Changed ActualCollapse to TriggerForce.
   1.14           01-21-97    PaulG   Modify Graph printout so graph fits on 1 page.
   1.15           01-31-97    PaulG   Modify 1 line data printout.
   1.16           02-05-97    PaulG   Modify printout of summary in graphs.
   1.17           02-14-97    PaulG   Modify alarms.
   1.18           02-18-97    PaulG   Modified printout of Metric vs inches.
   1.19           02-21-97    PaulG   Modified printout of Actual Velocity.
   1.20           02-27-97    PaulG   Remove graphics mode printing so line
   1.21           03-07-97    PaulG   Modified weld history printout.
   1.22           03-07-97    PaulG   Replaced "." in Time to ":".
   1.23           03-11-97    PaulG   Removed PrintFinalResults
   1.24           03-20-97    PaulG   Modified PRINT RESULTS...
   1.25           04-08-97    PaulG   Updated Weld History..
   1.27           04-16-97    PaulG   Added flag TestLineData...
   1.28           04-29-97    PaulG   Removed PMess[].
   1.29           05-02-97    PaulG   Collapse and absolute were changed to 3 digits
   1.30           05-06-97    PaulG   Modified Actual Velocity.
   2.00           05-07-97    LAM     deleted finalresults & memset     
   2.01           05-08-97    PaulG   Modified Tick Marks
   2.02           05-09-97    PaulG   Inserted ZERO value on vertical line.   
   3.00           05-12-97    LAM     added PrintingGraphFlag & deleted memset
   3.01           05-15-97    LAM     added AbortPrintingFlag
   3.02           05-16-97    PaulG   modify tick marks when auto scaling.                 
   3.03           05-20-97    PaulG   Modify the 1 line data cpi .                 
   3.04           05-22-97    PaulG   Added ColdStartDone flag and CheckUnitChanged.                 
   3.05           05-28-97    PaulG   Cleanup code.                 
   3.06           06-06-97    LAM     Cleanup code,chged unit check 
   4.00           06-16-97    PaulG   Cleanup code - remove memcpy                 
   5.1.59         06-19-97    PhilJ   Chngd Language vars to enum
   5.1.60         06-20-97    PaulG   Cleanup code. Modified power graph. 
   6.1.61         06-20-97    LAM     added new alarm structure, deleted
   6.1.62         06-23-97    PaulG   Modified Printer types. 
   6.1.64         07-01-97    LAM     Made UILines global     
   6.1.65         07-15-97    PaulG   Modified 1 line data based on Control Level.                   
   6.1.66         08-08-97    PaulG   Added printer driver
   6.1.67         08-23-97    PaulG   Modified printer driver strings.
   1.68           08-23-97    LAM     Deleted triggerattime       
   1.69           08-27-97    LAM     Changed SonicsEndAt to ActualWeldTime.       
   1.70           08-27-97    PaulG   Modified Tick marks.
   1.71           08-28-97    PaulG   Added special text string for X scale.
   1.72           09-04-97    PaulG   Removed AbortPrintingFlag
   1.73           09-05-97    PaulG   Modifiy GraphActive variable.
   1.74           09-06-97    PaulG   Initialize UILines to 0 in FormFeedPage.
   1.75           09-09-97    PaulG   Cleanup Data.
   1.76           09-16-97    PaulG   Changed LinesPerPage to WeldsPerPage.
   1.77           09-23-97    PaulG   Implemented formfeed and Linesper page.
   1.78           09-24-97    PaulG   Modified formfeed and Linesper page.
   1.79           09-25-97    PaulG   Added WeldCounter to check number of cycles to print.
   1.80           09-26-97    PaulG   Updated control level 4 w/encoder print summary printout.
   1.81           09-30-97    PaulG   Modified WeldHistory function.
   1.82           10-06-97    PaulG   Modified WeldsPerPage in PrintFinalData.
   1.83           10-07-97    PaulG   Modified string in PrintBotton.
   1.84           10-09-97    PaulG   Modified DateString for alarm printout.
   1.85           10-16-97    PaulG   Modified Added PageSize code to InitPrinterFlags()
   1.86           10-28-97    PaulG   Added PrintCPIMode flag to check cpi.
   1.87           10-30-97    PaulG   Removed TotalTimeWeld for auto scale.
   1.88           11-05-97    PaulG   Modified check for formfeed based on
                                      WeldsPerPage value.
   1.89           11-10-97    PaulG   Added function SendPageSizeToPrinter().
   1.90           11-11-97    PaulG   Added function SendPageSizeToPrinter().
   1.91           11-14-97    PaulG   Modified IBM mode printing.
   1.92           11-17-97    PaulG   Modified IBM mode printing.
   1.93           11-19-97    LAM     chged printfinalresults to finalresults                    
   1.94           11-24-97    LAM     deleted unused currentsetup elements                    
   1.95           11-24-97    LAM     need to keep prototype local                            
   1.96           12-04-97    PaulG   Changed TotalPts from UINT16 to UINT32.  
   1.97           12-05-97    PaulG   CHeck for divide by zeros.
   1.98           12-09-97    PaulG   Added WeldDataCount and modified History printout.
   1.99           12-10-97    PaulG   Modified 1 line printout to make more efficient.
   1.100          12-12-97    PaulG   Added count to PrintAlarms().
   1.101          12-15-97    PaulG   Modified graph printout for Print Now.
   1.102          12-19-97    PaulG   Modified 1 Line data when Print Now is pressed.
   1.103          12-22-97    LAM     deleted printerbufferreadyflag                  
                                      deleted printtest already done in prnweld
   1.104          01-16-98    PaulG   Modify metric data
   1.105          01-23-98    PaulG   General cleanup. 
   1.106          01-29-98    PaulG   Added string "Alarm" for  AmpSetAlTime, HoldEndAtTime,
                                      SeekEndAtTime not reached due to cutoff.
   1.107          02-02-98    PaulG   Removed unused code from PrepTickMarks().
   1.108          02-04-98    PaulG   Modified code so SeekEndAtTime shows "ALARM" when cycle
                                      aborts before seek.
                                                                                     
   1.109          02-04-98    BEKymer Move 'AtTime' values from WELD_DATA to
                                      WELD_OBJECT structure
                                      Changed SeekEnd constant from 1310 to 1300 (300ms delay
                                      plus 1000ms actual seek)
   1.110          02-04-97    LAM     deleted right 1/4" of graph, cleanup sethorizpos
   1.111          02-06-97    PaulG   Modified PeakPower on 1 line data and Print Summary.
   1.112          02-06-97    PaulG   Modified 1 line data to facillitate PeakPower > 100 %.
   1.113          02-09-97    PaulG   General cleanup and alignment of code.
   1.114          02-11-98    LAM     tried to eliminate string copies,etc.
   1.115          02-12-98    PaulG   Added code to formfeed appropriately
                                      when alarms are present.  
   1.116          02-13-98    LAM     fixed bottom hash marks, fix alarms not in
                                      condensed mode
   1.117          02-18-98    LAM     started to delete setprinter calls        
   1.118          02-23-98    PaulG   Added ESC code to InitIBMPRO() for 1/6 inch line feed.
   1.119          02-24-98    LAM     cleanup deleted code                   
   1.118          02-24-98    PaulG   Added ESC code for A4 (70 Lines is equivalent to 11 5/8").
   1.121          03-03-98    LAM     fixed offset in x-axis hash marks      
   1.122          03-03-98    PaulG   Adjust Alarms so they don't formfeed
                                      during printing of graph.
   1.123          03-13-98    PaulG   Adjust Alarms so they don't formfeed
                                      Added a flag that recognizes when graphs
                                      are printing.
   1.124          03-17-98    PaulG   Removed pause from PrintWeldHistory().
   1.125          03-18-98    PaulG   Added note on all Amplitude graph.
   1.126          03-19-98    PaulG   Modify Amp A and Amp B based on External/Internal Amp.
   1.127          03-20-98    PaulG   Replaced AmpControl with AmpControlFlag.
   1.128          03-23-98    LAM     added bottom seek tick mark              
   1.129          03-26-98    PaulG   Added TotalPts to WELD_OBJECT structure and removed TestPoints1.
                                      also remove all reference to RunningPreset from printing graph.
   1.130?         03-27-98    PaulG   Changed RunningPreset.WeldMode to MsPointer->Weldmode.
   1.131?         04-03-98    PaulG   Changed CycleCount to hold up to 8 digits.
   1.132?         04-24-98    PaulG   Changed alignment of 1 line and summary data.
   1.133?         04-28-98    PaulG   Changed alignment of 1 line and summary data for metric.                 
   1.134?         05-15-98    PaulG   Activated Force graph printing.
   1.135?         05-15-98    LAM     temporarily added trigforce to weld data
   1.136?         05-21-98    PaulG   Modified Alarm printout.
   1.137?         05-22-98    LAM     temporarily added trigforce to weld data line
   1.137          05-22-98    BJB     Extracted main part of PrintData() into function
                                       FormatDataLine() for sharing with TERMINAL.C
                                      Modified TrigForce, ActualMaxForce printing code for
                                       tenths of pounds in PrintSummary(), FormatDataLine().
   1.138          05-22-98    PaulG   Modified Alarm printout.
   1.139          05-22-98    BJB     Modified ActualForceEnd in PrintSummary(),
                                       PrintData() for tenths of pounds.
   1.140          05-26-98    BJB     FormatDataLine() uses routines in MENU.C to display
                                       distance, velocity. Should now always match screen.
   1.141          06-01-98    PaulG   Changed EP to AEF...
   1.142          06-03-98    BEKymer Change AmpControlFlags to
                                      PowerSupplyControlFlags
   1.143          06-05-98    PaulG   Remove assignment of FALSE to ColdStartDone after printing History.
   1.144          06-12-98    PaulG   Modified tick marks on graph; Also add dotted line trough graph for trigger.
   1.145          06-12-98    BJB     Made spacing of max force in FormatDataLine() the same
                                      for both English & Metric units.
   1.146          06-19-98    PaulG   Modified PrintGraph adding defines for graph box.
   1.147          06-19-98    BJB     Created general routine GetLastWeldData() to get
                                      last line of weld data buffer, use for terminal &
                                      screen as well as printer.
                                      Fixed bug in FormatDataLine(), it left one space unwritten.
   1.148          06-22-98    PaulG   Added variable ActualGraphVel to store Actual Velocity.
   1.149          06-22-98    BEKymer Change member ActualForceMax to
                                      to WeldForceMax
   1.150          07-17-98    PaulG   Modified 1 line data to match displayed weld results.
   1.151          07-24-98    PaulG   Modified TotalEnergy from PrintFinalPtr to Results.
   1.152          07-30-98    PaulG   Added testcode for all graphs.
   1.153          08-05-98    PaulG   Added Gauge Pressure value to graph printout.
   1.154          08-06-98    PaulG   Modified Gauge Pressure value to graph printout.
   1.155          08-11-98    PaulG   Colapse distance now broken into 2 variables
                                      ActualWeldCollapse and ActualTotalCollapse. Both added to WELD_OBJ struct.
   1.156          08-12-98    PaulG   Modified Metric data d/m/y.
   1.157          08-17-98    PaulG   Modified Gauge Pressure on graph.
   1.158          08-18-98    PaulG   Modified Gauge Pressure on graph when model less than AED.
   1.159          08-19-98    PaulG   Modified Collaspe distance variables.
   1.160          08-19-98    PaulG   Modified printout of 1 line data and print summary.
   1.161          09-04-98    PaulG   Added variable GraphCurrentlySelected from graphs.h.
   1.162          09-18-98    PaulG   Replace MsPointer->TotalPts with UIWeldtime.
   1.163          10-13-98    PaulG   Modified print summary in AE mode to reflect amp readings.
   1.164          10-27-98    PaulG   Modify code to calculate welds per page.
   1.165          10-28-98    PaulG   Modify code to display "Note" instead of "Alarm" on alarm printout
                                      if warning occurred.
   1.166          11-09-98    PaulG   Modify PrintSummary() replacing SPrintf() function with FormatVariable().
   1.167          12-07-98    BEKymer Use end force instead of max force
   1.168          12-14-98    PaulG   Modify PrintSummary() and PrintData() modifying level 3 to include Amp B.
   1.169          04-23-99    OFI     Changed for Diab
   1.170          05-14-99    JZ      changed WeldForceMax to SetForceB, ActualForceStart to SetForceA, ActualForceEnd
                                      to WeldForceEnd, PowerSupplyControlFlags to PSActControlFlags
   1.170.4.1      08-28-99    JLH     Modified summary printouts to include Set ForceA and Set ForceB.  Made various
                                       changes for use of IBM Pro mode of printer.
   1.170.4.2      09-08-99    JLH     Changed printer inits and made various other changes.
   1.170.4.3      09-16-99    JLH     Removed code to execute printer command sequence in PUCNonGraphics.  It was
                                       not needed since printer is initialized immediately after that point in
                                      PrintBottom.
   1.170.4.4      09-17-99    JLH     Changed force step n/a printout decision to be based on previous weld results
                                       rather than current preset.
   1.170.4.5      09-23-99    JLH     Changes to PrintBottom, PrintSummary, and other functions.
   1.170.4.6      09-24-99    OFI     Merged revisions 1.170.4.5 and 1.171
   1.173          10-11-99    JLH     Modified SPrintf conversions to account for floating point conversion errors.
   1.174          10-11-99    JZ      made PPrint(), PrintSheet(), PrintMessText() type void
                                      moved PrintEscSequ() to pr_label.c
   1.175          10-12-99    JLH     Eliminated unused variable ActualGraphVel.
   1.176          10-14-99    JLH     Changed floating point rounup constants .05 and .0005 to .01 and .0001.
   1.177          10-23-99    JLH     Eliminated floating point rounding by replacing various SPrintf calls
                                       with FormatVariable calls.
   1.178          11-01-99    JLH     Printer code review changes.
   1.179          11-02-99    LAM     fixed no force step alarm, deleted all tabs
   1.180          11-15-99    JLH     Fixed field widths for times at bottom of graphs.
   1.181          11-16-99    LAM     replaced formatvariable with sprintf to temporarily
                                      solve the problem where the string is not terminated
   1.181.2.1      12-03-99    JLH     Print SetForceA and SetForceB only for control level 5 with AEF actuator.
                                       Eliminate amplitude step at: if control level < 3.  Eliminate force step
                                       at: if not control level 5 with AEF.  Eliminate force graph comment for
                                       all except control level 5 with AEF.
   1.182          11-18-99    LAM     made i_index a local uint16 to prevent preptickmarks to fill
                                      in UCLINE passed its end point 
   1.183          12-17-99    OFI     Merged 1.181.2.1 and 1.182
   1.184          12-20-99    OFI     Updated revision history after merge 
   1.185          12-21-99    OFI     Fixed printing of Amplitude and Force Graph 
   1.186          02-23-00    JZ/JLH  merged 7.f4CHp to trunk, added HP printer with PCL control 
                                      also added Epson ESC/P printer capability 
   1.187          02-28-00    JZ      removed tabs                                                                    
   1.188          03-21-00    JLH     Removed IBM proprinter option.
   1.189          03-23-00    JLH     Added GetLangArrayIndex function call to code executed when 
                                       InitPrinterOnceOnPowerup is true.
   1.190          03-24-00    JLH     Included MODEL3 in amplitude graph disclaimer,  Moved function headers before
                                       comments describing function.
   1.191          03-29-00    JLH     Other cleanup requested by code review.
   1.192          04-04-00    JLH     Added #defines as requested by code review.
   1.193          04-10-00    JLH     Merged with Lang branch revision 1.187.1.1.
   1.194          04-14-00    JLH     Replaced Kalib function with PlotSort in preparation for Horn Scan plotting.
   1.195          05-01-00    JLH     Added externs for new text strings.  Added prototypes for new functions
                                       PrintHSTop, PrintHSGraph, PrintHSBottom, LineUpNotes.  Added HORNSCAN case
                                       to PrintSheet.  Added new functions PrintHSTop, PrintHSGraph, PrintHSBottom,
                                       and LineUpNotes.
   1.196          05-01-00    JLH     Changed PrintHSGraph to request values from PHASEGRAPH and then CURRENTGRAPH. 
   1.197          05-05-00    JLH     Added printing resonance frequencies to PrintHSBottom.  Added case for
                                       DupsPresetReport to PrintSheet.
   1.198          05-12-00    JLH     Fixed bug in PrintBottom that caused "Force Step At" to be printed when
                                       it should not be printed.
   1.199          05-17-00    JLH     Added extra constant declaration for string extern declarations.
   1.200          05-26-00    JLH     Changed printer type designations to OKI520, EPSONCOMP, and HPPCL.
   1.201          06-02-00    JLH     Form feed after printing 1-line data for HP printer when Print Now is pressed.
   1.202          06-06-00    JLH     Fixed bug in 1.201 - it was form feeding after each line of history data 
                                       printout.
   1.203          06-13-00    JLH     Deleted IAnzahl variable.
   1.204          06-13-00    JLH     Removed tabs.
   1.205,1.206    06-13-00    JLH     Added multilanguage support for some remaining strings.
   1.207,1.208    06-14-00    JLH     Added more multilanguage support.
   1.209          06-27-00    SCM     Changed the variable name ActualTotalAbs in the functions
                                      PrintSummary() and FormatDataLine(). 
   1.210          06-28-00    BEKymer Changed all MODEL to LEVEL
   1.211          07-25-00    JLH     Made changes to treat LEVEL_TEST the same as LEVEL_f.
   1.212          08-09-00    JLH     Changed horn scan graph to print real resonant frequencies, rather than dummy data.                                      
   1.213          08-10-00    JLH     Interim checkin for testing by Laura.
   1.214          08-10-00    JLH     Corrected number of points designation for Horn Scan Graph (was 0). 
   1.215          08-10-00    JLH     Corrected designation of Horn Scan Graph points to DUPS_HORNSCANPOINTS. 
   1.216          08-15-00    AT      Fixed phase graph scaling for negative values.
   1.217          08-15-00    AT      Horn scan graph - print zero crossing points as lines.
   1.218          08-22-00    AT      Horn scan graph - print 'Phase' instead of 'Amplitude (%)'
   1.219          08-22-00    AT      Horn scan graph - updated frequency spacing on X axis
   1.220          08-25-00    AT      Reset graph printing flag at the end of horn scan graph
   1.221          08-31-00    SRP     Vertical compression made 12 in Print HS graph
   1.222          09-06-00    SRP     In HSPrintGraph horizontal labels for start, stop HS freq. is aligned with x axis.
   1.223          09-14-00    JLH     Changed position of Frequency (Hz) at bottom of Horn Scan graph to begin in column 41.     
   1.224          09-21-00    JLH     Changed variable spacing for 1-line data when printout is in Spanish.
   1.225          09-22-00    JLH     Refined variable spacing for 1-line data when printout is in Spanish.   
   1.226          09-26-00    JLH     Added test of ActuatorChanged BOOLEAN variable in PrintFinalData function. If
                                       ActuatorChanged is true, the 1-line data printout does a form feed and prints
                                       a new heading before printing more data.  
   1.227          09-29-00    SCM     Fixed the issue abt tickmarks appearing on a HornScan graph. Issue no:3601.                                                       
   1.228          10-05-00    JLH     Removed Spanish-specific variable spacing for 1-line data. 
   1.229          10-11-00    JLH     Fixed HP horn scan graph.
   1.230          10-13-00    JLH     Issue #3628 - widen field for peak power in 1-line data to allow
                                       peak power greater than 99.9 percent, e.g. 101.5 percent.                                            
   1.231          10-16-00    JLH     Fixed horn scan graph so vertical labels are printed without clipping
                                       for 672c printers and hopefully the 610c.  Still works ok for laserjet 6L.
   1.232          10-17-00    JLH     Added DisablePerforationSkip and EnablePerforationSkip functions (#3636).
   1.233          10-17-00    JLH     Changed SetHorizPos function calls to used symbolic column positions.
   1.234          10-19-00    JLH     Changed PrintFinalData function to form feed 1-line data after WeldsPerPage.
                                       Previously an additional 1-line data printout was required to get the form feed. 
   1.235          10-23-00    SCM     Changed the line no.(from 35 to 92) used in printing the special note associated 
                                      with the force graph in function PrintSummary().
   1.236          11-03-00    AT      Removed PrintLf(LFCR6) in PrintWeldHistory.
   1.236.1.0      04-18-01    BEKymer In PrepTickMarks() only print trigger if there is no handheld system
   1.236.1.1      05-14-01    BEKymer In PrepTickMakrs() add some paren's to make certain of precedence
   1.239          05-02-03    BEKymer Move 1.236.1.1 onto tip for 8.10 build
                                      Use alternate strings with velocity missing when 
                                       VelocityReporting to FALSE
   1.240          08-04-03    BEKymer Merged 1.238 and 1.239 to create 2.240 for build 9.00A
                                       -between graph printing & display. 
   1.239.1.1      10-03-03    JOY     Modified HornScan Graph as per ORS.
   1.239.1.2      10-13-03    JOY     Added (S), (P), HornScan Freq's Tracker issue #3785.
   1.239.1.3      10-24-03    JOY     'Fr' replaced to 'Resonance Frequency'.
   1.241          12-04-03    BEKymer Merged 1.239.1.3 & 1.240 to create 1.241
                                       for Ver9.00b build
   1.242          06-04-04    VSharma Modified PrintWeldHistory(),PrintFinalData() &
                                      GetPresetNameFunc() to print preset name in header.
                                      Added CheckForPrintHeader().
   1.243          06-15-04    VSharma Added GetPresetNameHeader().
   1.244          06-29-04    JOY     Form feed removed as preset changes(Weld Summary),
                                      from PrintFinalData().
   1.245          07-02-04    JOY     Velocity value is printed only if velocity header is
                                      printed in printSummary().
   1.246          07-12-04    JOY     synchronized Velocity value printing in graph & one line data.
   1.247          06-10-05    Aare    Renamed AlarmText to Alarm and Alarm to Alarm1.
   1.248          12-07-05    Bwadia  Tick mark stored to be sent in VGAGRAPH object.
                                      Modified for tracker issue 4031, 4009
   1.249          12-20-05    Bwadia  Sequence Printing related code added
                                      Modified for tracker issue 3976
   1.250          02-07-07    NHAhmed Changed display format of date for Asian languages(yyyy/mm/dd).
   1.251          02-07-07    NHAhmed Check-in after code review.
   1.252          05-23-07    NHAhmed Added Tick (G) to Graph in Ground Detect mode 
   1.253          06-05-07    NHAhmed Changes for Tick (G).
   1.254          10-22-07    NHAhmed Changes done for LangTest phase 0
   1.255          09-02-08    NHAhmed CleanUp for multi-language support.
   1.256          09-04-08    YGupta  CleanUp for LangTest Project.
   1.257          09-09-08    NHAhmed CleanUp for multi-language support.
   1.258          09-10-09    BEkymer Add new define MICRO where needed
	1.259          09-22-09    YGupta  Removed Syntax error coming from previous check in.
   
   

 ---------------------------- DESCRIPTION ----------------------------------**/
#include <stdlib.h>
#include "graphs.h"
#include "string.h"
#include "weld_obj.h"
#include "util.h"
#include "fmtstrs.h" 
#include "ticks.h"
#include "keypad.h"
#include "selctkey.h"
#include "battram.h"
#include "menu7a.h"
#include "menu4.h"
#include "alarms.h"
#include "menu.h"
#include "dups_api.h"
#include "rtclock.h"

#define EMPTYLINESATBOTTOM 3
#define ALARMMESS 0
#define NOTEMESS  1

#define POSBUFFERLEN 11
#define POSITIONMULTIPLIER 30.0
#define INCREMENTSPERINCH 57.0
#define DECIPOINTSPERINCH 720.0
#define COMMANDLEN 10
#define RASTERLEN 53

/**-------------------------EXTERNAL DATA------------------------------------**/

extern UINT16         QVGATickmarks[];
extern UINT16         VGATickInfo[];
extern UINT16         AbortPrintingFlag;
extern CONFIGSETUP    CurrentSetup;
extern SETUPS_Ver800  RunningPreset;
extern BUCMENU_800    BUCMenuRAM;
extern WELD_DATA      FinalResults;
extern WELD_OBJECT    *MsPointer;
extern UINT16         WeldDataCount;
extern SINT32         MaxLinesPerPage;
extern SINT32         DigPotValue;
extern UINT16         PrintAnyway;              /*--  TRUE: Print Now is Pressed    --*/ 
extern SINT32         MaxWeldsPerPage;
extern SINT8          buffer[];                 /*--  Holds string to be printed    --*/
extern UINT16         AmpCntrlExt;
extern struct SummaryStruct SummaryInfo;
/**-------------------------LOCAL GLOBAL DATA---------------------------------**/

#define GRAPH_LENGTH  402
#define HASH_MARK 40
#define TICKMARKS 6
#define HS_GRAPHHEIGHT 136                /* 136 pixels from rail to rail */

UINT16    Tickmarks[TICKMARKS];
UINT16    LineLength  = LINE135;
UINT32    UILines     = 0;                /*--  Line counter, every CR increments      --*/
UINT32    UIAlarms    = 0;                /*--  Number of Alarms                       --*/
SINT32    SizeToPtr   = 0;                /*--  weldHistory variable                   --*/ 
SINT32    AddrBattram = 0;                /*--  weldHistory variable                   --*/ 
SINT32    bytecount   = 0, checkcount= 0; /*--  counter variables                      --*/ 
UINT8     *PUCLine;                       /*--  pointer to 1 line data array           --*/ 
SINT8     DateString[DATESIZE];           /*--  Stores the date section of 1 line data --*/ 
UINT8     *BattramHistoryPtr;             /*--  pointer to BATTRAM                     --*/ 
static SINT8     PresetString[MISCLINE];  /*--  stores preset name; MISCLINE = 24      --*/ 
UINT16    NumSize = 0;                    /*--  no. of of weldhisory records up to cur.--*/ 
UINT16    HistoryActive = FALSE;          /*--  Printing weld History                  --*/ 
UINT16    InitPrinterOnceOnPowerup = TRUE;/*--  TRUE: Printer init. once               --*/ 
UINT16    ColdStartDone = FALSE;          /*--  FALSE: cold start not done             --*/ 
UINT16    CheckUnitChanged = FALSE;       /*--  FALSE: unit was not changed            --*/ 
UINT16    PresetCheck = 0;                /*--  Check if preset was changed            --*/ 
UINT16    ResetCounterCheck = 0;          /*--  Check if preset was changed            --*/ 
DFLOAT    TempValue , TempValue2;         /*--  Both used to cal.Ticks marks           --*/ 
WELD_DATA TotalResults[HISTORYDATA];      /*--  Store 50 weldhistory data              --*/ 
UINT8     TickMarkerLine[FIELD_LENGTH+1]; /*--  buffer line of the graph printing      --*/ 
SINT32    WeldCounter;                    /*--  Counts the weld cycles        --*/
UINT16    TempPrinter = SINTINEL;         /*--  temp printer type: 0 = epson, 1 = ibm, 3 = sentinal --*/
UINT16    CheckPageSizeFlag = FALSE;      /*--  TRUE: Page size was changed            --*/
UINT16    PrintCPIMode;                   /*-- CPI12 = 12 cpi, CPI10, CPI17            --*/
UINT16    TempCPIMode;                    /*-- CPI12(1)  = 12 cpi, CPI10(0), CPI17(2)  --*/
                                          /*-- (100) sentinel value                    --*/
UINT16    PrinterType;                    /*--  Epson, IBM pro etc.                    --*/
UINT16    WeldOnceOnPowerup = TRUE;       /*--  TRUE: reset WeldsPerPage               --*/ 
WELD_DATA TempFinalResults;
SINT16    HistoryPageCt;
UINT16    LastHistoryCycle;
WELD_DATA *PrintFinalPtr;
WELD_DATA *LastPrintResultPtr;
BOOLEAN   IsThereAGraphPrinting = FALSE;
BOOLEAN   ActuatorChanged = FALSE;
UINT16    testAlarm;
UINT32    TempUIAlarms = 0;  /*--  temp storage for the number of Alarms                       --*/
UINT16    ShouldWeFormfeedFirst;
UINT16    GraphCurrentlySelected;
UINT16    mytest;
UINT8     UCLine[FIELD_LENGTH+1]; /*--  buffer line of the graph printing--*/
WELD_DATA TestResults;

static void PPrint(UINT8* PUCLine);
void GetLangArrayIndex(void);
void PrintHSTop(void);
void PrintHSGraph(void);
void PrintHSBottom(void);
void LineUpNotes(SINT8 *string);

/**-------------------------------------------------------------------------------------**/




void QVGAPrepTickMarks(void)
{
   UINT16 index;
   UINT16 TickMarkIndex     = 0;                /*--  index position on graph line           --*/  
   UINT16 TriggerOffset;
   TempValue = 400.0 / (float)UIHmaxlabel;
   
   /*-- save tick marks for bottom of graph --*/
   for(index=0; index < TICKMARKS; index++)
      QVGATickmarks[index] = 0;

   if (CurrentSetup.HandHeld == FALSE) {       /* Only print this tick mark if no handheld */
      TickMarkIndex = ((DFLOAT)PRETRIGMAXLIM * TempValue);
      if(TickMarkIndex < ENDGRAPH)         
         QVGATickmarks[TICKTRIG] = TickMarkIndex;      
      TriggerOffset = PRETRIGMAXLIM;
      VGATickInfo[TICKTRIG] = 0;     // Trigger starts at 0 sec
   }
   else {
      TriggerOffset = 0;
      VGATickInfo[TICKTRIG] = 0xFFFE;  // Show the trigger value as OFF
   }
   /*-- If there were no alarm print tick mark --*/
   if(CurrentSetup.ControlLevel >= LEVEL_ea){
      if((PrintFinalPtr->PSActControlFlags & BIT1) == BIT1){ /* STEP */
         if(!(MsPointer->PrintBottomFlags & AMPSTEPALARMMASK)){
            TickMarkIndex = (((DFLOAT)(MsPointer->AmpStepAtTime + TriggerOffset)) * TempValue);
            if(TickMarkIndex < ENDGRAPH)         
               QVGATickmarks[TICKAMP] = TickMarkIndex;
            VGATickInfo[TICKAMP] = (UINT16)MsPointer->AmpStepAtTime;         
         }
         else
            VGATickInfo[TICKAMP] = 0xFFFD;
      }
      else
         VGATickInfo[TICKAMP] = 0xFFFE;
   }
   else
      VGATickInfo[TICKAMP] = 0xFFFF; 
   
   if((CurrentSetup.ControlLevel == LEVEL_f || CurrentSetup.ControlLevel == LEVEL_TEST)
      && CurrentSetup.Actuator == AEF){
      if((PrintFinalPtr->PSActControlFlags & BIT4) == BIT4){
         if(!(MsPointer->PrintBottomFlags & FORCESTEPALARMMASK)){
            TickMarkIndex = (((DFLOAT)(MsPointer->ForceStepAtTime + TriggerOffset)) * TempValue);
            if(TickMarkIndex < ENDGRAPH)         
               QVGATickmarks[TICKFORCE] = TickMarkIndex; 
            VGATickInfo[TICKFORCE] = (UINT16)MsPointer->ForceStepAtTime;        
         }
         else
            VGATickInfo[TICKFORCE] = 0xFFFD;
      }
      else
         VGATickInfo[TICKFORCE] = 0xFFFE;
   }
   else
      VGATickInfo[TICKFORCE] = 0xFFFF; 


   if(PrintFinalPtr->ActualWeldTime){
      TickMarkIndex = (((DFLOAT)(PrintFinalPtr->ActualWeldTime + TriggerOffset)) * TempValue);
      if(TickMarkIndex < ENDGRAPH)         
         QVGATickmarks[TICKSONIC] = TickMarkIndex;
      VGATickInfo[TICKSONIC] = (UINT16)PrintFinalPtr->ActualWeldTime;         
   }
   else
      VGATickInfo[TICKSONIC] = 0xFFFE;


   if((MsPointer->HoldEndAtTime != PrintFinalPtr->ActualWeldTime)){
      if(!(MsPointer->PrintBottomFlags & HOLDALARMMASK)){
         TickMarkIndex = (((DFLOAT)(MsPointer->HoldEndAtTime + TriggerOffset)) * TempValue);
         if(TickMarkIndex < ENDGRAPH)            
            QVGATickmarks[TICKHOLD] = TickMarkIndex; 
         VGATickInfo[TICKHOLD] = (UINT16)MsPointer->HoldEndAtTime;           
      }
      else
         VGATickInfo[TICKHOLD] = 0xFFFD;
   }
   else
      VGATickInfo[TICKHOLD] = 0xFFFE;
   

   if(MsPointer->SeekEndAtTime != 0){
     /*-- 1300ms is the delay time for seek and 10ms is minimum holdtime--*/
      if(!(MsPointer->PrintBottomFlags & SEEKALARMMASK)){
         TickMarkIndex = (((DFLOAT)(MsPointer->SeekEndAtTime + TriggerOffset)) * TempValue);
         if(TickMarkIndex < ENDGRAPH)            
            QVGATickmarks[TICKSEEK] = TickMarkIndex;         
         VGATickInfo[TICKSEEK] = (UINT16)MsPointer->SeekEndAtTime;           
      }
      else
         VGATickInfo[TICKSEEK] = 0xFFFD;
   }
   else
      VGATickInfo[TICKSEEK] = 0xFFFE;

   if((RunningPreset.WeldMode==GRDDETECTMODE)&&(MsPointer->ScrubStartAtTime)){
      TickMarkIndex = (((DFLOAT)(MsPointer->ScrubStartAtTime + TriggerOffset)) * TempValue);
      if(TickMarkIndex < ENDGRAPH)
         QVGATickmarks[TICKSCRUB] = TickMarkIndex;
         VGATickInfo[TICKSCRUB] = (UINT16)MsPointer->ScrubStartAtTime;           
   }
   else
   {
      QVGATickmarks[TICKSCRUB] = 0;
      VGATickInfo[TICKSEEK] = 0xFFFE;
   }
}


void GetLastWeldData( WELD_DATA *Results )
/****************************************************************************/
/*                                                                          */
/* Fetches the last weld's data from the history buffer, copies to          */
/* "Results".                                                               */
/*                                                                          */
/****************************************************************************/
{
   UINT8  *NextWeld, *LastWeld;

   /*-- Calculate where Weld History starts in BBRAM --*/
   NextWeld = (UINT8 *)(BBR800_HISTORY_START);

   /*-- Get the last data position --*/
   if (((UINT8*)CurrentSetup.WeldHistoryPtr) != NextWeld)
      LastWeld = (((UINT8*)CurrentSetup.WeldHistoryPtr) - (sizeof(WELD_DATA)));
   else
      LastWeld = NextWeld + ((HISTORYDATA-1) * sizeof(WELD_DATA));

   /*--  Instantly copy last cycle weld results --*/ 
   memcpy( Results, LastWeld, (sizeof(WELD_DATA)));

   /*-- Always print time mode after cold start --*/
   /*-- Also print 0 for Amp A and Amp B        --*/
   if(!Results->CycleCount){
      Results->Weldmode = TIMEMODE;
      Results->PSActControlFlags |= (BIT0 | BIT1 | BIT2);
      Results->ActualAmplitudeStart = 0;
      Results->ActualAmplitudeEnd = 0;
   }
}


void FormatDataLine( UINT8 DataLine[LINELENGTH], WELD_DATA *Results, UINT16 Metric )
{
   SINT8 UCChar;
   UINT16 USMode,i;
   UINT8 *LinePtr;

   /*--  load pointer to language of texts--*/ 

   LinePtr = DataLine;

   for (i=0; i<LINELENGTH; i++)
      *LinePtr++ = SP;            /*--  fill line with blanks--*/

   LinePtr = DataLine;
   SPrintf((SINT8*)LinePtr, "%8u", (SINT32)Results->CycleCount); 
   LinePtr += 8;
   SPrintf((SINT8*)LinePtr, " %02u:%02u:%02u", Results->CycleTime.hour,
                                             Results->CycleTime.minute,
                                             Results->CycleTime.second);
   LinePtr += 9;
   if(Metric == TRUE){        /*--  european date--*/ 
      SPrintf((SINT8*)LinePtr, " %02u/%02u/%02u ", Results->CycleDate.day,
            Results->CycleDate.month, Results->CycleDate.year);
   }
   else{                /*--  american date--*/ 
      SPrintf((SINT8*)LinePtr, " %02u/%02u/%02u ", Results->CycleDate.month,
            Results->CycleDate.day, Results->CycleDate.year);
   }
   LinePtr += 10;

   FormatVariables(Results->ActualWeldTime, TIME, (SINT8*)LinePtr, 6, Metric);
   LinePtr += 8;

   if(CurrentSetup.ControlLevel > LEVEL_t)
   {

	  if(CurrentSetup.PeakPowerWattsFlag == TRUE)
		  FormatVariables(Results->PeakPower, WATTS, (SINT8*)LinePtr, 5, Metric);
	  else
		  FormatVariables(Results->PeakPower, PERCENTX10, (SINT8*)LinePtr, 5, Metric);
	  LinePtr += 6;

      if(Results->TotalEnergy > ENERGYPOINT)
         FormatVariables(Results->TotalEnergy, ENERGYDIV10, (SINT8*)LinePtr, 5, Metric);
      else
         FormatVariables(Results->TotalEnergy, ENERGY, (SINT8*)LinePtr, 5, Metric);
      LinePtr += 6;
   }

   if ( ( (CurrentSetup.Actuator == AED)  ||
          (CurrentSetup.Actuator == AEF)  ||
          (CurrentSetup.Actuator == MICRO) ) &&
          (CurrentSetup.ControlLevel >= LEVEL_d) ) {
      FormatVariables( Results->ActualTotalAbs, DISTANCE, (SINT8*)LinePtr, 8, Metric );
      LinePtr += 8;
      FormatVariables( Results->ActualWeldCollapse, DISTANCE, (SINT8*)LinePtr, 9, Metric );
      LinePtr += 9;
      FormatVariables( Results->ActualTotalCollapse, DISTANCE, (SINT8*)LinePtr, 9, Metric );
      LinePtr += 9;
      *LinePtr++ = ' ';
      *LinePtr = 0;
   }
   
   if ( ( (CurrentSetup.Actuator == AED)  ||
          (CurrentSetup.Actuator == AEF)  ||
          (CurrentSetup.Actuator == MICRO) ) &&
          (CurrentSetup.ControlLevel >= LEVEL_d) ) {

      FormatVariables(Results->TrigForce, FORCE, (SINT8*)LinePtr, 5, Metric);
      LinePtr += 6;

      if((CurrentSetup.ControlLevel == LEVEL_f || CurrentSetup.ControlLevel == LEVEL_TEST)
         && CurrentSetup.Actuator == AEF)
      {
         FormatVariables(Results->SetForceA, FORCE, (SINT8*)LinePtr, 7, Metric);
         LinePtr += 7;

         /* Test if weld step is enabled to print SetForceB */
         if((Results->PSActControlFlags & BIT4) == BIT4)
            FormatVariables(Results->SetForceB, FORCE, (SINT8*)LinePtr, 7, Metric);
         else
            /* Print n/a if weld step is not enabled */
            SPrintf((SINT8*)LinePtr, "   %3s ", "n/a");

         LinePtr += 7;
      }

      FormatVariables(Results->WeldForceEnd, FORCE, (SINT8*)LinePtr, 5, Metric);
      LinePtr += 7;

   }

   SPrintf((SINT8*)LinePtr, " %+3u  ", Results->FrequencyChange);
   LinePtr += 7;

   if((Results->PSActControlFlags & BIT0) == BIT0) /* INT  */
      SPrintf((SINT8*)LinePtr, " %3u   ", Results->ActualAmplitudeStart);
   else
      SPrintf((SINT8*)LinePtr, " %3s ", "Ext");
   LinePtr += 5;

   if(CurrentSetup.ControlLevel > LEVEL_e){
      if((Results->PSActControlFlags & BIT0) == BIT0) {    /* INT  */
         if((Results->PSActControlFlags & BIT1) == BIT1){   /* STEP */
            SPrintf((SINT8*)LinePtr, "  %3u  ", Results->ActualAmplitudeEnd);
            LinePtr += 7;
         }
         else{
            SPrintf((SINT8*)LinePtr, "  %3s  ", "n/a");
            LinePtr += 7;
         }
      }
      else{
         SPrintf((SINT8*)LinePtr, "  %3s  ", "n/a");
         LinePtr += 7;
      }
   }

   if ( (( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) ) &&
          (CurrentSetup.ControlLevel >= LEVEL_d) ) ||
        ((CurrentSetup.Actuator == AEF) && (CurrentSetup.ControlLevel >= LEVEL_f) && (BUCMenuRAM.VelocityReporting == TRUE)) ) {

      FormatVariables( Results->ActualVelocity, VELOCITY, (SINT8*)LinePtr, 5, Metric );
      LinePtr[5] = 0;   /* Make sure string is terminated */
   }
}

