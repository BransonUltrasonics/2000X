/* $Header:   D:/SWLab/VMdb/2000Series/App/PR_TEXT.C_V   1.187   Feb 23 2005 18:54:50   ATali  $ */
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
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: pr_text.c
  
 ----------------------------- REVISIONS ------------------------------------

   Revision #     Date        Author   Description
   ----------     -------     ------   -----------
    0             09-14-96    GR        Initial
    1.01          09-30-96    PaulG     Added General Alarms
    1.02          09-30-96    PaulG     Modified test data
    1.03          10-14-96    LAM       added system fault 22
    1.04          10-31-96    PaulG     Added System Faults SF23-SF27
    1.05          11-06-96    PaulG     Modify General Alarms
    1.06          11-13-96    PaulG     Added general Alarm - G81
    1.07          11-15-96    PaulG     Added general Alarm - G82
    1.08          11-22-96    PaulG     Added general Alarm - G46
    1.09          12-11-96    PaulG     Added Preset# to string.
    1.10          01-07-97    PaulG     Added WeldHistory info.
    1.11          01-15-97    PaulG     Modified WeldHistory info.
    1.12          01-20-97    PaulG     Added WeldHistory text at end.
    1.13          01-21-97    PaulG     Modified Alarm text for AE actuator.
    1.14          02-07-97    PaulG     Changed Down Speed to  Actual Velocity.
    1.15          03-06-97    PaulG     Changed Time in s to Time in sec
    1.16          03-07-97    PaulG     Added TRS text.
    1.17          03-20-97    PaulG     Modified text time (second).
    1.18          04-03-97    PaulG     Update Peak Power Reject Limit.
    1.19          04-08-97    PaulG     Removed G40 and G45..
    1.20          04-16-97    PaulG     Modified finalData line..
    1.21          04-17-97    PaulG     Changed Amp Start and Amp End to Amp. A
    1.22          04-28-97    PaulG     Cleanup array declarations - removed const.
    1.28          06-12-97    PaulG     Changed Extern Cycle Abort to external Cycle Abort.
    1.29          06-13-97    PaulG     Changed Distance to Col Dist.
    1.30          07-15-97    PaulG     Added subscript strings for 1 line data to array structure.
    1.31          07-17-97    BEKymer   Add new alarm group text
    1.32          07-18-97    PaulG     Modified new alarm group text
    1.33          08-08-97    PaulG     Added printer driver info.
    1.34          08-13-97    PaulG     Added Alarm text for printout.
    1.35          08-23-97    PaulG     Modified Alarm text for printout.
    1.36          08-29-97    PaulG     Added text string 119 thru 121 in array MessEng.
    1.37          09-03-97    LAM       made text const                                  
    1.38          09-08-97    PaulG     Remove *const from text strings.
    1.39          09-09-97    PaulG     Modified Text string for CL4/w encoder
    1.42          09-11-97    LAM       unit test version                      
    1.43          10-07-97    PaulG     Added string to MessEng string.
    1.44          10-30-97    PaulG     Modified auto scale message.
    1.45          11-07-97    PaulG     Modified gauge pressure text message.
    1.46          11-13-97    PaulG     Added Printbuffer 80% full message
    1.47          11-19-97    PaulG     Ajusted string text for manual scale.
    1.48          12-03-97    PaulG     Modified string for weld history.
    1.49          12-03-97    PaulG     Modified Frequ to Freq.
    1.50          12-10-97    PaulG     Modified AlarmMessEng.
    1.51          01-15-98    PaulG     Added (m/d/y) and (d/m/y) to text.
    1.52          01-20-98    PaulG     Changed EQ20 TO SE270 for Printer offline.
    1.53          01-29-98    PaulG     Added string constant to replace hard code.
    1.54          02-03-98    BEKymer   Changed alarm NC5 to CM14.
                                        Expanded Ground Detect Cutoff to NC12 & CM2
                                        Expanded Ext Cycle Abort to NC7 & CM15
    1.55          02-04-98    PaulG     Modified "Time(sec)" so it centers on the graph.
    1.56          02-17-98    BEkymer   Add in alarms CM15-CM20
    1.57          03-10-98    LAM       chged ground detect cutoff to abort
    1.58          03-10-98    LAM       chged ground detect cutoff to abort(rel2.5)
    1.59          03-11-98    LAM       fixed ground detect cutoff again
    1.60          03-13-98    BJB       Changed text of special note when no auto-scale.
    1.61          03-18-98    PaulG     Changed all Amp As and Amp Bs to Set AmpAs and Set AmpBs.
    1.62          03-19-98    PaulG     Align text for graph.
    1.63          04-03-98    PaulG     Align text to hold up to 8 digits of 1 line data.
    1.64          04-09-98    PaulG     Align text of entire 1 line data.
    1.65          04-17-98    LAM       chged ground detect cutoff to abort
    1.66          04-24-98    PaulG     Align text of entire 1 line data.
    1.67          04-25-98    PaulG     Align text for metric 1 line data.
    1.68          04-30-98    BEKymer   Add text for alarms SE271-SE277.
                                        Remove SE277.
    1.69          05-13-98    BEKymer   Add text for alarm SE43
    1.70          05-20-98    PaulG     Modified text for printsummary ctl. level 4.
    1.71          05-20-98    BEkymer   Moved Energy Not Reached from PR15
                                        to CM21
                                        Added EQ24 - Actuator Type
    1.72          05-16-98    BEKymer   Added text for WA1
                                        Added text for SE120
    1.73          06-11-98    PaulG     Modified amplitude special note.
    1.74          06-17-98    BEKymer   Moved CA1 to EQ20
    1.75          06-23-98    BEKymer   Change text for SE13, SE14, SE99, SE100
                                        SE101, SE102, PS11, PS12, PR11, PR12
                                        SE258
    1.76          06-25-98    PaulG     Changed all occurances of Max. Force to Weld Force.
    1.77          07-07-98    PaulG     Received PrintMessage text array from menu4 file.
    1.78          07-29-98    PaulG     Added Frequency label for 40K.
    1.79          08-04-98    PaulG     Replaced Actual Velocity with Down Speed and add value
                                        for gauge pressure.
    1.80          08-11-98    PaulG     Replaced Collapse Distance with Collapse Weld and Distance Total.
    1.81          08-15-98    PaulG     Added Gauge Pressure text line when model less than AED.
    1.82          08-17-98    PaulG     Modified Gauge Pressure text.
    1.83          08-18-98    PaulG     No changes update label.
    1.84          08-19-98    PaulG     Modified text strings...
    1.85          09-18-98    PaulG     Modified text strings by removing Freq. Start and End from headers.
    1.86          10-14-98    PaulG     Modified text strings by changing COLLAP to COL etc.
    1.87          10-30-98    PaulG     Added "Note" for a warning alarms. Also removed "Act." from "Act. Vel"
    1.88          11-04-98    PaulG     Modified "Gauge Pressure" to "Act. Gauge Pressure"
    1.89          11-09-98    PaulG     Modified Text strings for PrintSummary printout.
    1.90          11-23-98    BEKymer   Add CM22 text (at the last minute, again)
    1.91          11-25-98    LAM       chged CM22 text again
    1.92          12-14-98    PaulG     Modified level 3 to contain Amp A and Amp B.
    1.92.1.1      07-07-99    JZ        edited EQ25   
    1.93.4.1      08-28-99    JLH       Modified text for summary printout headings to contain Set ForceA
                                         and Set ForceB.
    1.93.4.2      09-16-99    JLH       Updated Cycle Modified alarm text.
    1.93.4.3      09-23-99    JLH       Added text for force graph advisory message.
    1.95          10-25-99    OFI       Deleted SE46 alarm from Group two
    1.96          12-06-99    JLH       For actuator gauge pressure, any graph, actuator AE, delete extra
                                         space before semicolon.
    1.97          02-09-00    OFI       Took out alarm descriptions for SE22,23,68,69
    1.98          02-23-00    JZ/JLH    merged 7.f4CHp to trunk  
    1.99          02-28-00    JZ        removed tabs                         
    1.100         02-28-00    JLH       Renamed "PeakPower" array to "PkPower" to avoid conflict with
                                         PeakPower declaration in ready.c.
    1.101         04-11-00    JLH       Merged with Lang branch revision 1.96.6.3.
    1.102         04-24-00    JLH       Moved most remaining strings out of prsetprn.h into this file.
    1.104         05-01-00    JLH       Added new strings for HORNSCAN graph.  Ignore 1.103 -- operator error.
    1.105         05-05-00    JLH       Added more new strings for PrintHSBottom.  Added new strings for DupsPresetReport.
    1.106         05-12-00    JLH       Added multilanguage strings for English, German, Spanish, Italian, and French.
    1.107         05-17-00    JLH       Added extra const declaration for strings to put them into flash memory.
    1.108         05-20-00    SCM       Checked in for foreign language translation purposes.
    1.109         06-07-00    JLH       Changed DUPS to DUPSStr to get rid of doubly defined symbol error.
    1.110         06-13-00    JLH       Replaced SINT8 with STR for string declarations.
    1.111,1.112   06-13-00    JLH       Replaced weld max force with weld force in alarm definitions.
    1.113         06-14-00    JLH       Removed tabs.
    1.114         07-12-00    LAM/BEK   added foreign language strings    
    1.115         07-12-00    LAM       Removed tabs.
    1.117         07-19-00    BEKymer   Changed Config0013 from real text to blank lines
    1.118         08-03-00    JLH       Replaced "" in NotApp with "n/a" for all 4 foreign languages.
    1.119         08-08-00    JLH       Abbreviated words in several Italian strings.  Replaced null Step Force Rate Italian
                                         string with English as a temporary fix.
    1.120         08-10-00    JLH       Added Horn Scan Graph text to PrintMess text arrays.
    1.121         08-16-00    JLH       Added English strings temporarily for various foreign language strings so setup
                                         printout will not have blank spaces.  Also added 1 space to French mode string
                                         to fix prematurely ending line on Weld History Data printout.                                                  
    1.122         08-17-00    JLH       Replaced all remaining null foreign language strings with English until the proper
                                         translation is obtained.
    1.123         08-26-00    AT        Changed Notes[] to lower case (#3470)
    1.124         08-29-00    DJL       Made changes from omnilingua's final  version of the file
    1.125         08-29-00    AT        removed end-of-comment at line 538
    1.126         08-30-00    AT        Added 'Horn Scan Graph" to PrintMess___ (need translation)
    1.127         09-06-00    BEKymer   Make translations consistant (maybe not right, but consistant)
                                        DCS issues # 3545, 3546, 3547, 3548, 3549, 3551
    1.129         09-06-00    SCM       Made modifications to the Amplitude Graph strings.(Merged with Barry's changes)
    1.130         09-06-00    AT        Added 1 space to french TPS string again
    1.131         09-06-00    JLH       Changes English 'Notes:' to 'NOTES' and made equivalent changes for other languages.                                        
    1.132         09-06-00    BEKymer   Missed 1 translation making it consistant String Setup0057 and Setup0058
    1.133         09-08-00    BEKymer   Remove period on French version of French[] string  DCS # 3551
    1.134         09-20-00    JLH       Various language-related changes.
    1.135         09-21-00    SCM       Changed the string info. SelectStr[].
    1.136         09-22-00    JLH       More language-related changes.
    1.137         09-27-00    SCM       Fixed problems relating to graphs in foreign languages.
    1.138         09-27-00    JLH       Eliminated extra spaces in Spanish title for Control Level 5 with Encoder.
    1.139         09-27-00    JLH       Added 2 extra spaces in English title for Control Level 5(f) without Encoder.
    1.140         10-02-00    SCM       Fixed minor string related problems.
    1.141         10-04-00    BEKymer   Changed all references to manual section 7.6 to 7.5
    1.142         10-04-00    JLH       "Kraft" changed to "Leist" for German power graph.
    1.143         10-09-00    JLH       Updated German 1-line data heading for AED level f and for AEF level f.
    1.144         10-10-00    JLH       Made German 1-line data headings consistent with summaries.
    1.145         10-12-00    JLH       Made many language updates.
    1.146         10-18-00    SCM       Fixed minor issues.
    1.147         10-19-00    JLH       Added "DUPS Preset Report" to PrintMessEng, PrintMessGer, ... .  This was done
                                         as part of resolving tracker issue #3638.
    1.148         10-20-00    SCM       Fixed printing related language problems.
    1.149         10-23-00    SCM       Fixed printing related issues from 8L12 build.
    1.150         10-31-00    AT        Fixed printing related issues.
    1.151         10-31-00    AT        Fixed one-line print spacing for languages.
    1.152         10-31-00    AT        Fixed 'forza' in one-line for spanish.
    1.153         10-31-00    AT        Changed to fuerza for above (i'm no spanish expert).
    1.154         10-31-00    AT        Fixed 'bei Auswahl' for german.
    1.155         10-31-00    AT        Forgot to save file before checking in.
    1.156         10-31-00    AT        Changed Gren<whatever> to grenzwertz for german.
    1.157         11-01-00    AT        Grenzwertz to grenzwert.
    1.158         11-01-00    AT        Italian, spanish fixes.
    1.159         11-01-00    AT        More language fixes.
    1.160         11-01-00    AT        Printer Online messages, other cleanup.
    1.161         11-01-00    AT        More german and french fixes.
    1.162         11-02-00    AT        More language fixes.
    1.163         11-02-00    AT        More language fixes.
    1.164         11-02-00    AT        More language fixes.
    1.165         11-14-00    AT        More translations
    1.166         11-14-00    LAM       More language fixes(+- swapped)
    1.167         11-14-00    AT        Spanish, german fixes
    1.169         03-08-01    LAM/AT    updated french
    1.170         03-14-01    LAM/AT    updated french & german
    1.171         03-20-01    LAM/AT    all foreign language updates
    1.172         04-24-01    LAM       added SE46 Preset Not Available text
    1.173         08-14-01    BEKYmer   Change string from "G DET" to GNDDET" so ASCII
                                        with space separated variables works correctly.
    1.174         08-21-01    BEKymer   Add underscore to ground detect mode strings for
                                        languages.  Detab where needed.
    1.174.1.0     11-21-02    SCM       Made changes to various strings for German Language as part 
                                        of version 8.07.                                         
    1.174.1.1     01-15-03    SCM       Made further changes to various strings for German 
                                        Language as part of version A808.
    1.174.1.2     03-21-03    SCM       Made further changes to various strings for German 
                                        Language as part of version A808.                                                                                 
    1.175         04-11-03    BEKymer   Move 1.174.1.2 to tip as 1.175 for build 8.10
    1.176         05-02-03    BEKymer   Duplicate strings without Velocity reporting
    1.177         09-06-03    JOY       Added Dual Graph Header texts.
    1.178         04-06-04    VSharma   Update alarms text for Ver9.00 alarms.
    1.179         06-04-04    VSharma   Added strings for UserIO and WeldMode.
    1.180         06-15-04    VSharma   Removed WeldMode from WeldHistory Header strings.
    1.181         06-17-04    VSharma   Made many language updates for Ver9.00 strings.
    1.182         07-26-04    BEKymer   Remove EQ19 J3-1 Configuration error
    1.183         07-27-04    JOY       Added string Khz60Str[]. 
    1.184         08-03-04    BEKymer   Change Ext Trigger to Ext Signal
    1.185         08-24-04    JOY       String 'SV Interlock' is replaced to 'External Start'.
                                        String 'External Trig Delay' is replaced to 'External U/S Delay'.
    1.186         08-26-04    JOY       String 'Ext Trig Delay' is replaced to 'Ext U/S Delay'.
    1.187         02-23-05    AT        Move all data into .lang section for 4-flash build
                
                                
-------------------------- DESCRIPTION -------------------------------------*/
#define BORLAND_CPP
#ifndef BORLAND_CPP
#include "graphs.h"
#include "alarms.h"
#else

#include "portable.h"
#endif

/* This section will go into flash that starts at 2MB. */
#pragma section CONST  ".lang"
#pragma section STRING ".lang"
#pragma section CODE   ".lang"

const STR *const MessEng[] = {

       /* Header Info Index 0*/
/*0*/  "  Preset# and Preset Name   : ",

        /* Control Level 5 with Encoder */
        /* Measurement Values Index 1 CONDENSED MODE*/
/*1*/   "  Cycle                     Act.    Peak   Act. Absolute   Weld    Total   Trig.  Set    Set    Weld  Freq.  Set   Set", 
/*2*/   "  Number   Time     Date    Time    Power  Ener Distance Collapse Collapse Force  ForceA ForceB Force Chg    AmpA  AmpB  Vel", 
/*3*/   "                   (m/d/y)  (sec)    (%)   (J)    (in)     (in)     (in)   (lb)   (lb)   (lb)   (lb)  (Hz)   (%)   (%)  (in/s)", 
/*4*/   "                   (d/m/y)  (sec)    (%)   (J)    (mm)     (mm)     (mm)   (N)    (N)    (N)    (N)   (Hz)   (%)   (%)  (mm/s)",

/* Graph label Index 5*/
/*5 */  "  Cycle                     Act.    Peak   Act. Absolute   Weld    Total   Trig.  Set    Set    Weld  Freq.  Set   Set",
/*6 */  "  Number   Time     Date    Time    Power  Ener Distance Collapse Collapse Force  ForceA ForceB Force Chg    AmpA  AmpB",
/*7 */  "                   (m/d/y)  (sec)    (%)   (J)    (in)     (in)     (in)   (lb)   (lb)   (lb)   (lb)  (Hz)   (%)   (%) ",
/*8 */  "                   (d/m/y)  (sec)    (%)   (J)    (mm)     (mm)     (mm)   (N)    (N)    (N)    (N)   (Hz)   (%)   (%) ",
/*9 */  "/* UNUSED */",
/*10*/  "/* UNUSED */","/* UNUSED */","/* UNUSED */","/* UNUSED */",
        /* Below graph Index 14*/
/*14*/  "Alarm Message    :",
/*15*/  "Trigger (----)   :         Amp. Step At :         Force Step At    :",
/*16*/  "End of Sonics At :         End of Hold  :         End of Weld Seek :",
/*17*/  "NOTES             ",
/*18*/  "Trigger Pressure        :  ____________________________________",
/*19*/  "Downspeed               :  ____________________________________",
/*20*/  "Act. Gauge Pressure     :",
/*21*/  "Position Switch Flag 1  :  ____________________________________",
/*22*/  "Position Switch Flag 2  :  ____________________________________",
/*23*/  "Column Position         :  ____________________________________",
/*24*/  "       Time (sec)",            /* 24, bottom line of graphics*/

        /* not condensed weld summary*/
        /* Print Summary --> Control Level 5 with Encoder */


/*25*/  "  Cycle Number  : ",
/*26*/  "  Time          : ",
/*27*/  "  Date          : ",
/*28*/  "  Mode          : ",


/*29*/ "Special Note:",
/*30*/ "Manual Scale: This graph may show part of the cycle. To see the    ",
/*31*/ "entire cycle set the x-axis to your weld time + hold time +        ",
/*32*/ "afterburst if used. This change will take effect on the next cycle.",

/*33*/ "** ------------------------- Last 50  Weld History Data (contd.) ------------------------ **",

/*34*/ "Set Amp. values may not be reached due to short weld times, amplitude steps",
/*35*/ "near the start or finish of the weld or starting ramp of the system.",
/*36*/ "",/* UNUSED */

/*37*/  "TIME","ENERGY","PEAK POWER","COLLAPSE","ABSOLUTE","GROUND DETECT","TECMODE","CONTINUOUS",
/*45*/  "TIME  ","ENERGY","PKPWR "," COL  "," ABS  ","GNDDET ","TECMOD","CONTIN",

/*53*/  "** ------------------------------ Last 50  Weld History Data ---------------------------- **",
/*54*/  "** ----------------------- End of Last 50  Weld History Data ---------------------------- **",

/*55*/  "TRS",
    
        /* Control Level 1(t) */
/*56*/  "  Cycle                     Act.     Freq. Set", /* first line*/
/*57*/  "  Number     Time    Date   Time     Chg   Amp", /* second line*/
/*58*/  "                    (m/d/y) (sec)    (Hz)  (%)", /* third line lb*/
/*59*/  "                    (d/m/y) (sec)    (Hz)  (%)", /* third line lb*/

        /* Control Level 2(e) */
/*60*/  "  Cycle                     Act.    Peak   Act.  Freq.  Set", /* first line*/
/*61*/  "  Number    Time    Date    Time    Power  Ener  Chg    Amp.", /* second line*/
/*62*/  "                   (m/d/y)  (sec)    (%)   (J)   (Hz)   (%)", /* third line lb*/
/*63*/  "                   (d/m/y)  (sec)    (%)   (J)   (Hz)   (%)", /* third line lb*/
/*64*/  "Act. Gauge Pressure     :  ____________________________________",
/*65*/  "",/* UNUSED */ 

        /* Control Level 4(d) with Encoder */
/*66*/  "  Cycle                     Act.    Peak  Act.  Absolute    Weld    Total   Trig. Weld   Freq. Set   Set", /* first line*/
/*67*/  "  Number   Time    Date     Time    Power Ener  Distance  Collapse Collapse Force Force  Chg   AmpA  AmpB  Vel",  /* second line*/
/*68*/  "                  (m/d/y)   (sec)    (%)  (J)     (in)      (in)     (in)   (lb)  (lb)   (Hz)  (%)   (%)  (in/s)", /* third line lb*/
/*69*/  "                  (d/m/y)   (sec)    (%)  (J)     (mm)      (mm)     (mm)   (N)   (N)    (Hz)  (%)   (%)  (mm/s)", /* third line mm*/

                        
        /* Control Level 3(a)  */
/*70*/  "  Cycle                     Act.    Peak   Act.  Freq. Set   Set",  /* first line   */
/*71*/  "  Number   Time    Date     Time    Power  Ener  Chg   AmpA  AmpB", /* second line  */
/*72*/  "                  (m/d/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",  /* third line lb*/
/*73*/  "                  (d/m/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",  /* third line mm*/
       
        /* Control Level 4(d) without Encoder */                                              
/*74*/  "  Cycle                     Act.    Peak   Act.  Freq. Set   Set",   /* first line   */
/*75*/  "  Number   Time    Date     Time    Power  Ener  Chg   AmpA  AmpB",  /* second line  */
/*76*/  "                  (m/d/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",   /* third line lb*/
/*77*/  "                  (d/m/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",   /* third line mm*/

        /* Control Level 5(f) without Encoder */                                                                
/*78*/  "  Cycle                     Act.    Peak   Act.  Freq. Set   Set",  /* first line   */
/*79*/  "  Number   Time    Date     Time    Power  Ener  Chg   AmpA  AmpB", /* second line  */
/*80*/  "                  (m/d/y)   (sec)   (%)    (J)   (Hz)  (%)   (%)",  /* third line lb*/
/*81*/  "                  (d/m/y)   (sec)   (%)    (J)   (Hz)  (%)   (%)",  /* third line mm*/
/*82*/  "Trigger (----)   :         Amp. step at :        ",

                                    


/* --------- NOT CONDENSED GRAPH WELD SUMMARY ------------*/

/* Print Summary --> Control Level 1(t) */
/*83*/  "",/* UNUSED */
/*84*/  "",/* UNUSED */
/*85*/  "",/* UNUSED */
/*86*/  "",/* UNUSED */

        /* Print Summary --> Control Level 2(e) */
/*87*/  "  Act.   Peak   Act.    Freq.  Freq.  Freq. Set",
/*88*/  "  Time   Power Energy   Start  End    Chg   Amp.",
/*89*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)",
/*90*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)",

/*91*/ "Set Force values may not be reached due to short weld times, force steps",
/*92*/ "near the start or finish of the weld or starting ramp of the system.",
/*93*/  "",/* UNUSED */
/*94*/  "",/* UNUSED */

        /* Print Summary --> Control Level 3(a) */
/*95*/  "  Act.   Peak   Act.    Freq.  Freq.  Freq. Set   Set", 
/*96*/  "  Time   Power Energy   Start  End    Chg   AmpA  AmpB",
/*97*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)   (%)", 
/*98*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)   (%)", 

        /* Print Summary --> Control Level 4(d) with AED Actuator */
/*99 */ "  Act.   Peak   Act.   Absolute   Weld    Total   Trig.  Weld  Freq.  Freq.  Freq.",
/*100*/ "  Time   Power Energy  Distance Collapse Collapse Force  Force Start  End    Chg",  
/*101*/ "  (sec)   (%)   (J)      (in)     (in)     (in)   (lb)   (lb)  (Hz)   (Hz)   (Hz)",
/*102*/ "  (sec)   (%)   (J)      (mm)     (mm)     (mm)    (N)    (N)  (Hz)   (Hz)   (Hz)",
/*103*/ "  Set   Set",
/*104*/ "  AmpA  AmpB   Vel",
/*105*/ "  (%)   (%)  (in/s)",
/*106*/ "  (%)   (%)  (mm/s)",

        /* Print Summary --> Control Level 4(d) without Encoder */
/*107*/ "  Act.   Peak    Act.  Freq.  Freq.  Freq.  Set   Set",
/*108*/ "  Time   Power  Energy Start  End    Chg    AmpA  AmpB",
/*109*/ "  (sec)  (%)     (J)   (Hz)   (Hz)   (Hz)   (%)   (%)",
/*110*/ "  (sec)  (%)     (J)   (Hz)   (Hz)   (Hz)   (%)   (%)",

                                                                                      
/* Print Summary --> Control Level 5(f) without Encoder */                 
/*111*/ "  Act.   Peak    Act.  Freq.  Freq.  Freq.  Set   Set", 
/*112*/ "  Time   Power  Energy Start  End    Chg    AmpA  AmpB",
/*113*/ "  (sec)   (%)     (J)  (Hz)   (Hz)   (Hz)   (%)   (%)", 
/*114*/ "  (sec)   (%)     (J)  (Hz)   (Hz)   (Hz)   (%)   (%)", 
/*115*/ "  AmpA  AmpB",
/*116*/ "  (%)   (%) ",
/*117*/ "  (%)   (%) ",
/*118*/ "",/* UNUSED */
/* Print Summary --> Control Level 5(f) with Encoder */                 
/*119*/  "  Act.   Peak   Act.   Absolute   Weld    Total   Trig.  Set    Set    Weld  Freq.  Freq.  Freq.",
/*120*/  "  Time   Power Energy  Distance Collapse Collapse Force  ForceA ForceB Force Start  End    Chg  ",
/*121*/  "  (sec)   (%)   (J)      (in)     (in)     (in)   (lb)   (lb)   (lb)   (lb)  (Hz)   (Hz)   (Hz) ",
/*122*/  "  (sec)   (%)   (J)      (mm)     (mm)     (mm)    (N)    (N)    (N)    (N)  (Hz)   (Hz)   (Hz) ",
/*123*/  "  Set   Set",
/*124*/  "  AmpA  AmpB   Vel  ",
/*125*/  "  (%)   (%)  (in/s) ",
/*126*/  "  (%)   (%)  (mm/s) ",
/*127*/  "Amplitude (%)","Power (%)","Frequency (Hz)","Col Dist (in)","Force (lb)",
/*132*/  "Velocity (in/s)","Col Dist (mm)","Force (N)","Velocity (mm/s)", "Abs Dist (in)",
/*137*/  "Abs Dist (mm)","Phase", "Current", "P(%)/Col Dist(mm)","P(%)/Col Dist(in)",
/*142*/  "P(%)/Force(N)", "P(%)/Force(lb)",
/*144*/  "Force(N)/Col(mm)", "Force(lb)/Col(in)"
};

// OmniLingua - Start to insert German strings here
const STR *const MessGer[] = { 
       /* Header Info Index 0*/
/*0*/  "  Param.# und Param. Name   : ",

        /* Control Level 5 with Encoder */
        /* Measurement Values Index 1 CONDENSED MODE*/
/*1*/   "  Zykl                      Akt.    Spitz Akt.    Abs      Rel     Rel     Trig.   Soll   Soll  Schw. Freq.  Soll  Soll", 
/*2*/   "  Nummer   Zeit    Datum    Zeit    Leist Energ   Weg      Weg     Ges     Kraft  KraftA KraftB Kraft Aend.  AmpA  AmpB Geschw", 
/*3*/   "                   (M/T/J)  (sec)    (%)   (J)    (in)     (in)    (in)    (lb)    (lb)   (lb)   (lb) (Hz)   (%)   (%)  (in/s)", 
/*4*/   "                   (T/M/J)  (sec)    (%)   (J)    (mm)     (mm)    (mm)    (N)     (N)    (N)    (N)  (Hz)   (%)   (%)  (mm/s)",

/* Graph label Index 5*/
/*5 */  "  Zykl                      Akt.    Spitz Akt.    Abs      Rel     Rel     Trig.   Soll   Soll  Schw. Freq.  Soll  Soll",
/*6 */  "  Nummer   Zeit    Datum    Zeit    Leist Energ   Weg      Weg     Ges     Kraft  KraftA KraftB Kraft Aend.  AmpA  AmpB",
/*7 */  "                   (M/T/J)  (sec)    (%)   (J)    (in)     (in)    (in)    (lb)    (lb)   (lb)   (lb) (Hz)   (%)   (%) ",
/*8 */  "                   (T/M/J)  (sec)    (%)   (J)    (mm)     (mm)    (mm)    (N)     (N)    (N)    (N)  (Hz)   (%)   (%) ",
/*9 */  "/* UNUSED */", 
/*10*/  "/* UNUSED */","/* UNUSED */","/* UNUSED */","/* UNUSED */",
        /* Below graph Index 14*/
/*14*/  "Alarmmeldung     :", 
/*15*/  "Trigger (----)   :         Spitz st. bei:         Kraftstufe:", 
/*16*/  "Ende Ultraschall:         Ende Halten  :         Ende Schw-Suche  :",
/*17*/  "ANMERKUNG        ",
/*18*/  "Trigger Druck             :  ____________________________________",
/*19*/  "Abfahrgeschwindigkeit     :  ____________________________________",
/*20*/  "Aktueller Manometer Druck :",
/*21*/  "Positionsschalt Kennz 1   :  ____________________________________", 
/*22*/  "Positionsschalt Kennz 2   :  ____________________________________", 
/*23*/  "Saeulen Position          :  ____________________________________",
/*24*/  "       Zeit (sec)",            /* 24, bottom line of graphics*/

        /* not condensed weld summary*/
        /* Print Summary --> Control Level 5 with Encoder */

/*25*/  "  Zyklusnummer  : ",
/*26*/  "  Zeit          : ",
/*27*/  "  Datum         : ",
/*28*/  "  Mod           : ",


/*29*/ "Spez Hinweis:",  
/*30*/ "Man Skalierung: Grafik zeigt ggf einen Teil des Zyklus. Um den    ",  
/*31*/ "Um ganzen Zyklus zu sehen, die X-Achse auf Schweisszeit + Haltezeit + setzen       ",  
/*32*/ "Nachimpuls einst falls verw. Diese Aend tritt beim naechst Zyklus in Kraft.",  

/*33*/ "** ------------------------- Letzte 50 Schweissdaten (Forts.) ------------------------ **",  

/*34*/ "Schweisszeit zu kurz, Ampl. ggf nicht erreicht; Ampl.stufen",  
/*35*/ "bei Start od Ende Schweissung od Startrampe des Systems erreicht",  
/*36*/ "",/* UNUSED */

/*37*/  "ZEIT","ENERG","SPITZENLEISTUNG","REL.","ABSOLUT","METALLKONTAKT","TECMOD","KONT",  
/*45*/  "ZEIT  ","ENERG ","SPLST "," REL  "," ABS  "," M_K  ","TECMOD","KONT  ",

/*53*/  "** ----------------------------- Letzte 50 Schweissdaten ---------------------------- **",  
/*54*/  "** ----------------------- Ende der letzten 50 Schweissdaten ------------------------- **",  

/*55*/  "TRS",
    
        /* Control Level 1(t) */
/*56*/  "  Zykl                      Akt.     Freq. Soll", /* first line*/
/*57*/  "  Nummer     Zeit   Datum   Zeit     Aend. Amp", /* second line*/
/*58*/  "                    (M/T/J) (sec)    (Hz)  (%)", /* third line lb*/
/*59*/  "                    (T/M/J) (sec)    (Hz)  (%)", /* third line lb*/

        /* Control Level 2(e) */
/*60*/  "  Zykl                      Akt.   Spitz  Akt.   Freq.  Soll", /* first line*/
/*61*/  "  Nummer    Zeit   Datum    Zeit   Leist  Energ  Aend.  Amp.", /* second line*/
/*62*/  "                   (M/T/J)  (sec)    (%)   (J)   (Hz)   (%)", /* third line lb*/
/*63*/  "                   (T/M/J)  (sec)    (%)   (J)   (Hz)   (%)", /* third line lb*/
/*64*/  "Aktueller Manometer Druck :  ____________________________________",

/*65*/  "",/* UNUSED */ 

        /* Control Level 4(d) with Encoder */
/*66*/  "  Zykl                      Akt.    Spitz Akt.    Abs     Rel      Rel      Trig.  Schw. Freq. Soll  Soll", /* first line*/ 
/*67*/  "  Nummer   Zeit   Datum     Zeit    Leist Energ   Weg     Weg      Ges      Kraft  Kraft Aend. AmpA  AmpB Geschw",  /* second line*/ 
/*68*/  "                  (M/T/J)   (sec)    (%)  (J)     (in)    (in)     (in)     (lb)   (lb)  (Hz)  (%)   (%)  (in/s)", /* third line lb*/
/*69*/  "                  (T/M/J)   (sec)    (%)  (J)     (mm)    (mm)     (mm)     (N)    (N)   (Hz)  (%)   (%)  (mm/s)", /* third line mm*/

                        
        /* Control Level 3(a)  */
/*70*/  "  Zykl                      Akt.    Spitz  Akt.  Freq. Soll  Soll",  /* first line   */
/*71*/  "  Nummer   Zeit   Datum     Zeit    Leist  Energ Aend. AmpA  AmpB", /* second line  */
/*72*/  "                  (M/T/J)   (sec)    (%)   (J)   (Hz)  (%)   (%)",  /* third line lb*/
/*73*/  "                  (T/M/J)   (sec)    (%)   (J)   (Hz)  (%)   (%)",  /* third line mm*/
       
        /* Control Level 4(d) without Encoder */                                              
/*74*/  "  Zykl                      Akt.    Spitz Akt.   Freq. Soll  Soll",   /* first line   */
/*75*/  "  Nummer   Zeit   Datum     Zeit    Leist Energ  Aend. AmpA  AmpB",  /* second line  */
/*76*/  "                  (M/T/J)   (sec)    (%)   (J)   (Hz)  (%)   (%)",   /* third line lb*/
/*77*/  "                  (T/M/J)   (sec)    (%)   (J)   (Hz)  (%)   (%)",   /* third line mm*/

        /* Control Level 5(f) without Encoder */                                                                
/*78*/  "  Zykl                      Akt.  Spitz  Akt.  Freq. Soll  Soll",  /* first line   */
/*79*/  "  Nummer   Zeit   Datum     Zeit  Leist  Energ Aend. AmpA  AmpB", /* second line  */
/*80*/  "                  (M/T/J)   (sec) (%)    (J)   (Hz)  (%)   (%)",  /* third line lb*/
/*81*/  "                  (T/M/J)   (sec) (%)    (J)   (Hz)  (%)   (%)",  /* third line mm*/
/*82*/  "Trigger (----)   :         Amp Stuf be :        ",




/* --------- NOT CONDENSED GRAPH WELD SUMMARY ------------*/

/* Print Summary --> Control Level 1(t) */
/*83*/  "",/* UNUSED */
/*84*/  "",/* UNUSED */
/*85*/  "",/* UNUSED */
/*86*/  "",/* UNUSED */

        /* Print Summary --> Control Level 2(e) */
/*87*/  "  Akt.   Spitz Akt.    Freq.  Freq.  Freq. Soll",
/*88*/  "  Zeit   Leist Energ   Start  Ende   Aend. Amp.", 
/*89*/  "  (sec)   (%)   (J)    (Hz)   (Hz)   (Hz)  (%)",
/*90*/  "  (sec)   (%)   (J)    (Hz)   (Hz)   (Hz)  (%)",

/*91*/ "Eingest Kraft-Werte werd moegl. aufgr der kurz Schweisszeit, Kraft-Schrit ni erreicht", 
/*92*/ "bei Start od Ende Schweissung od Startrampe des Systems erreicht",
/*93*/  "",/* UNUSED */
/*94*/  "",/* UNUSED */

        /* Print Summary --> Control Level 3(a) */
/*95*/  "  Akt.   Spitz Akt.     Freq.  Freq.  Freq. Soll  Soll", 
/*96*/  "  Zeit   Leist Energ    Start  Ende   Aend. AmpA  AmpB", 
/*97*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)   (%)", 
/*98*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)   (%)", 

        /* Print Summary --> Control Level 4(d) with AED Actuator */
/*99 */ "  Akt.   Spitz Akt.      Abs       Rel      Rel   Trig.  Schw  Freq.  Freq.  Freq.",
/*100*/ "  Zeit   Leist Energ     Weg       Weg      Ges   Kraft  Kraft Start  Ende   Aend.", 
/*101*/ "  (sec)   (%)   (J)      (in)      (in)     (in)  (lb)   (lb)  (Hz)   (Hz)   (Hz)",
/*102*/ "  (sec)   (%)   (J)      (mm)      (mm)     (mm)  (N)    (N)   (Hz)   (Hz)   (Hz)",
/*103*/ "  Soll  Soll",
/*104*/ "  AmpA  AmpB   Geschw",
/*105*/ "  (%)   (%)    (in/s)",
/*106*/ "  (%)   (%)    (mm/s)",

        /* Print Summary --> Control Level 4(d) without Encoder */
/*107*/ "  Akt.   Spitz Akt.   Freq.  Freq.  Freq.  Soll  Soll",
/*108*/ "  Zeit   Leist Energ  Start  Ende   Aend.  AmpA  AmpB",    
/*109*/ "  (sec)  (%)    (J)   (Hz)   (Hz)   (Hz)   (%)   (%)",
/*110*/ "  (sec)  (%)    (J)   (Hz)   (Hz)   (Hz)   (%)   (%)",

                                                                                      
/* Print Summary --> Control Level 5(f) without Encoder */                 
/*111*/ "  Akt.  Spitz  Akt.   Freq.  Freq.  Freq.  Soll  Soll", 
/*112*/ "  Zeit  Leist  Energ  Start  Ende   Aend.  AmpA  AmpB",    
/*113*/ "  (sec)   (%)   (J)   (Hz)   (Hz)   (Hz)   (%)   (%)", 
/*114*/ "  (sec)   (%)   (J)   (Hz)   (Hz)   (Hz)   (%)   (%)", 
/*115*/ "  AmpA  AmpB",
/*116*/ "  (%)   (%) ",
/*117*/ "  (%)   (%) ",
/*118*/ "",/* UNUSED */
/* Print Summary --> Control Level 5(f) with Encoder */                 
/*119*/  "   Akt.  Spitz  Akt.      Abs      Rel    Rel    Trig.   Soll   Soll  Schw   Freq.  Freq. Freq.",
/*120*/  "   Zeit  Leist  Energ     Weg      Weg    Ges    Kraft  KraftA KraftB Kraft  Start  Ende  Aend.", 
/*121*/  "   (sec)   (%)   (J)      (in)     (in)   (in)    (lb)   (lb)   (lb)   (lb)  (Hz)   (Hz)  (Hz) ",
/*122*/  "   (sec)   (%)   (J)      (mm)     (mm)   (mm)    (N)    (N)    (N)    (N)   (Hz)   (Hz)  (Hz) ",
/*123*/  "  Soll  Soll",
/*124*/  "  AmpA  AmpB  Geschw  ",
/*125*/  "  (%)   (%)   (in/s) ",
/*126*/  "  (%)   (%)   (mm/s) ",
/*127*/  "Amplitude (%)","Leist (%)","Frequenz (Hz)","Weg rel (in)","Kraft (lb)",
/*132*/  "Geschwin (in/s)","Weg rel (mm)","Kraft (N)","Geschwin (mm/s)", "Weg abs (in)",
/*137*/  "Weg abs (mm)","Phasen", "Current", "P(%)/Col Dist(mm)","P(%)/Col Dist(in)",
/*142*/  "P(%)/Force(N)", "P(%)/Force(lb)",
/*144*/  "Force(N)/Col(mm)", "Force(lb)/Col(in)"
};

// OmniLingua - End insert German strings here

// OmniLingua - Start to insert Spanish strings here
const STR *const MessSpn[] = {
       /* Header Info Index 0*/
/*0*/  "  Numero y Nombre Preselecc:  ",

        /* Control Level 5 with Encoder */
        /* Measurement Values Index 1 CONDENSED MODE*/
/*1*/   "  Ciclo                     Act.    Pico   Act.  Dist.     Sold    Total   Fuerz  Ajs    Ajs    Fuerz  Cam   Ajs   Ajs",        /*  : weld collapse, total collapse, set force, set amp */
/*2*/   "  Numero   Tiempo   Fecha   Tiem    Poten. Ener. Absoluto  Colapso Colapso Disp   FuerzA FuerzB Sold   Frec  AmpA  AmpB  Vel", 
/*3*/   "                   (m/d/y)  (sec)    (%)    (J)    (in)     (in)    (in)   (lb)   (lb)   (lb)   (lb)   (Hz)  (%)   (%)   (in/s)", 
/*4*/   "                   (d/m/y)  (sec)    (%)    (J)    (mm)     (mm)    (mm)   (N)    (N)    (N)    (N)    (Hz)  (%)   (%)   (mm/s)",

/* Graph label Index 5*/
/*5 */  "  Ciclo                     Act.    Pico   Act.  Dist.     Sold    Total   Fuerz  Ajs    Ajs    Fuerz  Cam   Ajs   Ajs",
/*6 */  "  Numero   Tiempo   Fecha   Tiem    Poten. Ener. Absoluto  Colapso Colapso Disp   FuerzA FuerzB Sold   Frec  AmpA  AmpB",
/*7 */  "                   (m/d/y)  (sec)    (%)    (J)    (in)     (in)    (in)   (lb)   (lb)   (lb)   (lb)   (Hz)  (%)   (%) ",
/*8 */  "                   (d/m/y)  (sec)    (%)    (J)    (mm)     (mm)    (mm)   (N)    (N)    (N)    (N)    (Hz)  (%)   (%) ",
/*9 */  "/* SIN USR */",  
/*10*/  "/* UNUSED */","/* UNUSED */","/* UNUSED */","/* UNUSED */",
        /* Below graph Index 14*/
/*14*/  "Mensaje alarm     :", 
/*15*/  "Disparo (----)   :         Paso Pot. a  :         Paso Fuerza a    :",
/*16*/  "Fin de US en :             Fin de Mant  :         Fin Busca Sold   :",
/*17*/  "NOTAS             ",
/*18*/  "Presion Disparo         :  ____________________________________",
/*19*/  "Vel. Lenta              :  ____________________________________",
/*20*/  "Presion Manom Actdr     :",
/*21*/  "Indicad 1 inter posic   :  ____________________________________", 
/*22*/  "Indicad 2 inter posic   :  ____________________________________", 
/*23*/  "Posicion Column         :  ____________________________________",
/*24*/  "       Tiem (sec)",            /* 24, bottom line of graphics*/

        /* not condensed weld summary*/
        /* Print Summary --> Control Level 5 with Encoder */

/*25*/  "  Numero Ciclo  : ",
/*26*/  "  Tiempo        : ",
/*27*/  "  Fecha         : ",
/*28*/  "  Modo          : ",


/*29*/ "Nota especi:", 
/*30*/ "Escala manual: Este grafo puede mostrar parte del ciclo. Para ver el    ", 
/*31*/ "ciclo entero, situe el eje X en su tiempo de sold + tiem esp +      ", 
/*32*/ "expl post si se usa. Este cambio se aplicara desde el ciclo siguiente.", 

/*33*/ "** ------------------------- Ult 50  datos histor sold (cont.) ------------------------     **",

/*34*/ "El valor de amp. elegido puede no lograrse por el breve tiempo de sold., pasos de ampl.", 
/*35*/ "prox al princ. o al fin de la sold. o inic. de lanzam del sist.", 
/*36*/ "",/* UNUSED */

/*37*/  "TIEM","ENERGIA","PICOPOT","COLAPSO","ABSOLUTO","DETECC TIERRA","MODOTEC","CONTINUO", 
/*45*/  "TIEM  ","ENERG ","PICOPOT"," COL  "," ABS  ","DET_T ","MODTEC","CONTIN",

/*53*/  "** ------------------------------ Ultim 50 Dat Histor Sold ---------------------------- **", 
/*54*/  "** ------------------------- Fin Ultimos 50 Dat Hist Sold ----------------------------- **", 

/*55*/  "DSP",
    
        /* Control Level 1(t) */
/*56*/  "  Ciclo                     Act.     Cam   Ajs", /* first line*/    
/*57*/  "  Numero     Tiempo  Fecha  Tiem     Frec  Amp", /* second line*/
/*58*/  "                    (m/d/y) (sec)    (Hz)  (%)", /* third line lb*/
/*59*/  "                    (d/m/y) (sec)    (Hz)  (%)", /* third line lb*/

        /* Control Level 2(e) */
/*60*/  "  Ciclo                     Act.    Pico   Act.  Cam    Ajs", /* first line*/  
/*61*/  "  Numero    Tiempo  Fecha   Tiem    Poten  Ener  Frec   Amp.", /* second line*/
/*62*/  "                   (m/d/y)  (sec)    (%)   (J)   (Hz)   (%)", /* third line lb*/
/*63*/  "                   (d/m/y)  (sec)    (%)   (J)   (Hz)   (%)", /* third line lb*/
/*64*/  "Presion Manom Actdr     :  ____________________________________",
/*65*/  "",/* UNUSED */ 

        /* Control Level 4(d) with Encoder */
/*66*/  "  Ciclo                     Act.    Pico  Act.  Dist.     Sold     Total    Fuerz  Fuerz Cam    Ajs   Ajs",         /* first line*/  
/*67*/  "  Numero   Tiempo  Fecha    Tiem    Poten Ener  Absoluto  Colapso Collapso  Disp   Sold  Frec   AmpA  AmpB  Vel",   /* second line*/
/*68*/  "                  (m/d/y)   (sec)    (%)  (J)     (in)      (in)     (in)   (lb)   (lb)  (Hz)   (%)   (%)  (in/s)", /* third line lb*/
/*69*/  "                  (d/m/y)   (sec)    (%)  (J)     (mm)      (mm)     (mm)   (N)    (N)   (Hz)   (%)   (%)  (mm/s)", /* third line mm*/

                        
        /* Control Level 3(a)  */
/*70*/  "  Ciclo                     Act.    Pico   Act.  Cam   Ajs   Ajs",  /* first line   */   
/*71*/  "  Numero   Tiempo  Fecha    Tiem    Poten  Ener  Frec  AmpA  AmpB", /* second line  */
/*72*/  "                  (m/d/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",  /* third line lb*/
/*73*/  "                  (d/m/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",  /* third line mm*/
       
        /* Control Level 4(d) without Encoder */                                              
/*74*/  "  Ciclo                     Act.    Pico   Act.  Cam   Ajs   Ajs",   /* first line   */  
/*75*/  "  Numero   Tiempo  Fecha    Tiem    Poten  Ener  Frec  AmpA  AmpB",  /* second line  */
/*76*/  "                  (m/d/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",   /* third line lb*/
/*77*/  "                  (d/m/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",   /* third line mm*/

        /* Control Level 5(f) without Encoder */                                                                
/*78*/  "  Ciclo                     Act.   Pico   Act.  Cam   Ajs   Ajs",  /* first line   */  
/*79*/  "  Numero   Tiempo  Fecha    Tiem   Poten  Ener  Frec  AmpA  AmpB", /* second line  */
/*80*/  "                  (m/d/y)   (sec)  (%)    (J)   (Hz)  (%)   (%)",  /* third line lb*/
/*81*/  "                  (d/m/y)   (sec)  (%)    (J)   (Hz)  (%)   (%)",  /* third line mm*/
/*82*/  "Trigger (----)   :         Amp. step at :        ",




/* --------- NOT CONDENSED GRAPH WELD SUMMARY ------------*/

/* Print Summary --> Control Level 1(t) */
/*83*/  "",/* UNUSED */
/*84*/  "",/* UNUSED */
/*85*/  "",/* UNUSED */
/*86*/  "",/* UNUSED */

        /* Print Summary --> Control Level 2(e) */
/*87*/  "  Act.   Pico   Act.   Inic   Fin    Cam   Ajs",  
/*88*/  "  Tiem   Poten  Ener   Frec   Frec   Frec  Amp.",
/*89*/  "  (sec)   (%)   (J)    (Hz)   (Hz)   (Hz)  (%)",
/*90*/  "  (sec)   (%)   (J)    (Hz)   (Hz)   (Hz)  (%)",

/*91*/ "Los valores de Fuerza pueden no alcanz. por los tiempos breves de sold, pasos fuerza", 
/*92*/ "prox al princ. o al fin de la sold. o inic. de lanzam del sist.",
/*93*/  "",/* UNUSED */
/*94*/  "",/* UNUSED */

        /* Print Summary --> Control Level 3(a) */
/*95*/  "  Act.   Pico   Act.    Inic  Fin    Cam   Ajs   Ajs",  
/*96*/  "  Tiem   Poten  Ener    Frec  Frec   Frec  AmpA  AmpB",
/*97*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)   (%)", 
/*98*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)   (%)", 

        /* Print Summary --> Control Level 4(d) with AED Actuator */
/*99 */ "  Act.   Pico   Act.  Dist.     Sold      Total   Fuerz Fuerz Inic   Fin    Cam", 
/*100*/ "  Tiem   Poten  Ener  Absoluto  Colapso   Colapso Disp  Sold  Frec   Frec   Frec",  
/*101*/ "  (sec)   (%)   (J)      (in)     (in)     (in)   (lb)  (lb)  (Hz)   (Hz)   (Hz)",
/*102*/ "  (sec)   (%)   (J)      (mm)     (mm)     (mm)    (N)   (N)  (Hz)   (Hz)   (Hz)",
/*103*/ "  Ajs   Ajs",
/*104*/ "  AmpA  AmpB   Vel",
/*105*/ "  (%)   (%)  (in/s)",
/*106*/ "  (%)   (%)  (mm/s)",

        /* Print Summary --> Control Level 4(d) without Encoder */
/*107*/ "  Act.  Pico     Act.  Inic   Fin    Cam    Ajs   Ajs",  
/*108*/ "  Tiem  Poten    Ener  Frec   Frec   Frec   AmpA  AmpB",
/*109*/ "  (sec)  (%)     (J)   (Hz)   (Hz)   (Hz)   (%)   (%)",
/*110*/ "  (sec)  (%)     (J)   (Hz)   (Hz)   (Hz)   (%)   (%)",

                                                                                      
/* Print Summary --> Control Level 5(f) without Encoder */                 
/*111*/ "  Act.   Pico    Act.  Inic   Fin    Cam    Ajs   Ajs",  
/*112*/ "  Tiem   Poten   Ener  Frec   Frec   Frec   AmpA  AmpB",
/*113*/ "  (sec)   (%)     (J)  (Hz)   (Hz)   (Hz)   (%)   (%)", 
/*114*/ "  (sec)   (%)     (J)  (Hz)   (Hz)   (Hz)   (%)   (%)", 
/*115*/ "  AmpA  AmpB",
/*116*/ "  (%)   (%) ",
/*117*/ "  (%)   (%) ",
/*118*/ "",/* UNUSED */
/* Print Summary --> Control Level 5(f) with Encoder */                 
/*119*/  "  Act.   Pico   Act.  Dist.     Sold     Total    Fuerz Ajs     Ajs     Fuerz Inic   Fin    Cam ",  
/*120*/  "  Tiem   Poten  Ener  Absoluto  Colapso  Colapso  Disp  FuerzaA FuerzaB Sold  Frec   Frec   Frec", 
/*121*/  "  (sec)   (%)   (J)      (in)   (in)     (in)      (lb) (lb)    (lb)    (lb)  (Hz)   (Hz)   (Hz)",
/*122*/  "  (sec)   (%)   (J)      (mm)   (mm)     (mm)      (N)  (N)     (N)     (N)   (Hz)   (Hz)   (Hz)",
/*123*/  "  Ajs   Ajs",
/*124*/  "  AmpA  AmpB   Vel  ",
/*125*/  "  (%)   (%)  (in/s) ",
/*126*/  "  (%)   (%)  (mm/s) ",
/*127*/  "Amplitud (%)","Potencia (%)","Frecuencia (Hz)","Dist Col (in)","Fuerza (lb)",
/*132*/  "Velocidad (in/s)","Dist Col (mm)","Fuerza (N)","Velocidad (mm/s)", "Dist Abs (in)",
/*137*/  "Dist Abs (mm)","Fase", "Current", "P(%)/Col Dist(mm)","P(%)/Col Dist(in)",
/*142*/  "P(%)/Force(N)", "P(%)/Force(lb)",
/*144*/  "Force(N)/Col Dist(mm)", "Force(lb)/Col Dist(in)"
};

// OmniLingua - End insert Spanish strings here

// OmniLingua - Start to insert Italian strings here
const STR *const MessItl[] = {
       /* Header Info Index 0*/
/*0*/  "  Preset# e nome preset   : ",

        /* Control Level 5 with Encoder */
        /* Measurement Values Index 1 CONDENSED MODE*/
/*1*/   "  Numero                    Reale   Picco Reale Distanza   Sald    Total   Forza  Set     Set    Forza  Camb Set   Set",          
/*2*/   "  Ciclo    Tempo    Data    Tempo   Pot.  Ener. Assoluta Collasso Collasso Trig. ForzaA  ForzaB  Sald   Freq AmpA  AmpB  Vel",     
/*3*/   "                   (m/d/y)  (sec)    (%)   (J)    (in)      (in)    (in)    (lb)  (lb)    (lb)    (lb)  (Hz) (%)   (%)  (in/s)", 
/*4*/   "                   (d/m/y)  (sec)    (%)   (J)    (mm)      (mm)    (mm)    (N)   (N)     (N)     (N)   (Hz) (%)   (%)  (mm/s)",

/* Graph label Index 5*/
/*5 */  "  Numero                    Reale   Picco Reale Distanza   Sald    Total   Forza  Set     Set    Forza  Camb Set   Set",
/*6 */  "  Ciclo    Tempo    Data    Tempo   Pot.  Ener. Assoluta Collasso Collasso Trig. ForzaA  ForzaB  Sald   Freq AmpA  AmpB",
/*7 */  "                   (m/d/y)  (sec)    (%)   (J)    (in)      (in)    (in)    (lb)  (lb)    (lb)    (lb)  (Hz) (%)   (%) ",
/*8 */  "                   (d/m/y)  (sec)    (%)   (J)    (mm)      (mm)    (mm)    (N)   (N)     (N)     (N)   (Hz) (%)   (%) ",
/*0 */  "/* INUTILIZ. */",  
/*10*/  "/* UNUSED */","/* UNUSED */","/* UNUSED */","/* UNUSED */",
        /* Below graph Index 14*/
/*14*/  "Mess. Allarme    :", 
/*15*/  "Trigger (----)   :         Amp. Step al :         Step forza a     :",
/*16*/  "Fine ultrasuoni a:         Fine raffredd:         Fine ricerca sald:",
/*17*/  "NOTE              ",
/*18*/  "Pressione Trigger       :  ____________________________________",
/*19*/  "Vel discs               :  ____________________________________",
/*20*/  "Pressione relativa att. :",
/*21*/  "Int. posizione Flag 1   :  ____________________________________", 
/*22*/  "Int. posizione Flag 2   :  ____________________________________", 
/*23*/  "Posizione colonna       :  ____________________________________",
/*24*/  "       Tempo (sec)",            /* 24, bottom line of graphics*/

        /* not condensed weld summary*/
        /* Print Summary --> Control Level 5 with Encoder */

/*25*/  "  Numero Ciclo  : ",
/*26*/  "  Tempo         : ",
/*27*/  "  Data          : ",
/*28*/  "  Modo          : ",                         


/*29*/ "Nota speciale:", 
/*30*/ "Scala manuale: Questa grafico puo visualizzare parte del ciclo.  ", 
/*31*/ "per visual. l'intero ciclo impostare l'asse X sul tempo saldatura + tempo tenuta + ", 
/*32*/ "afterburst se usato. La modifica avra effetto con il  prossimo ciclo.", 

/*33*/ "**  ------------------------- Cronologia sald. ultimi 50 dati (cont.) ------------------------  **", 

/*34*/ "Valori imp. Amp. Non raggiunti causa tempi sald. brevi, pass. Amp.", 
/*35*/ "vicino inizio o fine sald. O inizio rampa sistema.", 
/*36*/ "",/* UNUSED */

/*37*/  "TEMPO","ENERGIA","PICCO POT","COLLASSO","ASSOLUTO","RILEVA TERA","TECMODE","CONTIN",   
/*45*/  "TEMPO  ","ENERGIA ","PICPOT"," COL  "," ASS  ","RILTER","TECMOD","CONTIN",             

/*53*/  "** -------------------------- Ultimo 50 Dati storici saldature -------------------------- **", 
/*54*/  "** --------------------- Fine durata 50 Dati storici saldature -------------------------- **", 

/*55*/  "TRS",
    
        /* Control Level 1(t) */
/*56*/  "  Numero                    Reale   Camb   Set", /* first line*/         
/*57*/  "  Ciclo      Tempo   Data   Tempo   Freq.  Amp", /* second line*/    
/*58*/  "                    (m/d/y) (sec)   (Hz)   (%)", /* third line lb*/
/*59*/  "                    (d/m/y) (sec)   (Hz)   (%)", /* third line lb*/

        /* Control Level 2(e) */
/*60*/  "  Numero                    Reale   Picco Reale  Camb   Set", /* first line*/ 
/*61*/  "  Ciclo     Tempo   Data    Tempo   Pot.  Ener   Freq.  Amp.", /* second line*/ 
/*62*/  "                   (m/d/y)  (sec)    (%)   (J)   (Hz)   (%)", /* third line lb*/
/*63*/  "                   (d/m/y)  (sec)    (%)   (J)   (Hz)   (%)", /* third line lb*/
/*64*/  "Pressione relativa att.   :  ____________________________________",
/*65*/  "",/* UNUSED */ 


        /* Control Level 4(d) with Encoder */
/*66*/  "  Numero                    Reale   Picco Reale Distanza   Sald.    Total   Forza Forza  Camb  Set   Set", /* first line*/   
/*67*/  "  Ciclo    Tempo   Data     Tempo   Pot.  Ener  Assoluta  Collasso Collasso Trig. Sald   Freq. AmpA  AmpB  Vel",  /* second line*/ 
/*68*/  "                  (m/d/y)   (sec)    (%)  (J)     (in)      (in)     (in)   (lb)  (lb)   (Hz)  (%)   (%)  (in/s)", /* third line lb*/
/*69*/  "                  (d/m/y)   (sec)    (%)  (J)     (mm)      (mm)     (mm)   (N)   (N)    (Hz)  (%)   (%)  (mm/s)", /* third line mm*/

                        
        /* Control Level 3(a)  */
/*70*/  "  Numero                    Reale   Picco  Reale Camb  Set   Set",  /* first line   */   
/*71*/  "  Ciclo    Tempo   Data     Tempo   Pot.   Ener  Freq. AmpA  AmpB", /* second line  */ 
/*72*/  "                  (m/d/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",  /* third line lb*/
/*73*/  "                  (d/m/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",  /* third line mm*/
       
        /* Control Level 4(d) without Encoder */                                              
/*74*/  "  Numero                    Reale   Picco Reale Camb   Set   Set",   /* first line   */  
/*75*/  "  Ciclo    Tempo   Data     Tempo   Pot.  Ener  Freq.  AmpA  AmpB",  /* second line  */ 
/*76*/  "                  (m/d/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",   /* third line lb*/
/*77*/  "                  (d/m/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",   /* third line mm*/

        /* Control Level 5(f) without Encoder */                                                                
/*78*/  "  Numero                    Reale Picco Reale Camb   Set   Set",  /* first line   */     
/*79*/  "  Ciclo    Tempo   Data     Tempo Pot.  Ener  Freq.  AmpA  AmpB", /* second line  */ 
/*80*/  "                  (m/d/y)   (sec) (%)    (J)   (Hz)  (%)   (%)",  /* third line lb*/
/*81*/  "                  (d/m/y)   (sec) (%)    (J)   (Hz)  (%)   (%)",  /* third line mm*/
/*82*/  "Trigger (----)   :         Amp. Step al :       ", 




/* --------- NOT CONDENSED GRAPH WELD SUMMARY ------------*/

/* Print Summary --> Control Level 1(t) */
/*83*/  "",/* UNUSED */
/*84*/  "",/* UNUSED */
/*85*/  "",/* UNUSED */
/*86*/  "",/* UNUSED */

        /* Print Summary --> Control Level 2(e) */
/*87*/  "  Reale  Picco Reale    Iniz.  Fine   Camb   Set",   
/*88*/  "  Tempo  Pot.  Energ    Freq   Freq   Freq.  Amp.", 
/*89*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)   (%)",
/*90*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)   (%)",

/*91*/ "Valori forza impostati non raggiunti causa tempi sald. brevi, forza pass.",   
/*92*/ "vicino inizio o fine sald. O inizio rampa sistema.",
/*93*/  "",/* UNUSED */
/*94*/  "",/* UNUSED */

        /* Print Summary --> Control Level 3(a) */
/*95*/  "  Reale  Picco Reale   Iniz.  Fine   Camb   Set   Set",  
/*96*/  "  Tempo  Pot.  Energ   Freq   Freq   Freq.  AmpA  AmpB",   
/*97*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)   (%)", 
/*98*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)   (%)", 

        /* Print Summary --> Control Level 4(d) with AED Actuator */
/*99 */ "  Reale  Picco  Reale  Distanza  Sald.    Total   Forza  Forza Iniz.  Fine   Camb",  
/*100*/ "  Tempo   Pot.  Energ  Assoluta Collasso Collasso Trig.  Sald  Freq.  Freq.  Freq.",  
/*101*/ "  (sec)   (%)   (J)      (in)     (in)     (in)   (lb)   (lb)  (Hz)   (Hz)   (Hz)",
/*102*/ "  (sec)   (%)   (J)      (mm)     (mm)     (mm)    (N)    (N)  (Hz)   (Hz)   (Hz)",
/*103*/ "  Set   Set",
/*104*/ "  AmpA  AmpB   Vel",
/*105*/ "  (%)   (%)  (in/s)",
/*106*/ "  (%)   (%)  (mm/s)",

        /* Print Summary --> Control Level 4(d) without Encoder */
/*107*/ "  Reale  Picco  Reale  Iniz.  Fine   Camb   Set   Set",   
/*108*/ "  Tempo  Pot.   Energ  Freq   Freq   Freq.  AmpA  AmpB", 
/*109*/ "  (sec)  (%)     (J)   (Hz)   (Hz)   (Hz)   (%)   (%)",
/*110*/ "  (sec)  (%)     (J)   (Hz)   (Hz)   (Hz)   (%)   (%)",

                                                                                      
/* Print Summary --> Control Level 5(f) without Encoder */                 
/*111*/ "  Reale  Picco  Reale  Iniz.  Fine   Camb   Set   Set",  
/*112*/ "  Tempo  Pot.   Energ  Freq   Freq   Freq.  AmpA  AmpB",   
/*113*/ "  (sec)   (%)     (J)  (Hz)   (Hz)   (Hz)   (%)   (%)", 
/*114*/ "  (sec)   (%)     (J)  (Hz)   (Hz)   (Hz)   (%)   (%)", 
/*115*/ "  AmpA  AmpB",
/*116*/ "  (%)   (%) ",
/*117*/ "  (%)   (%) ",
/*118*/ "",/* UNUSED */
/* Print Summary --> Control Level 5(f) with Encoder */                 
/*119*/  "  Reale  Picco Reale  Distanza   Sald.    Total   Forza  Set    Set   Forza  Iniz.  Fine  Camb",     
/*120*/  "  Tempo  Pot.  Energ  Assoluta  Collasso Collasso Trig. ForzaA ForzaB disald Freq.  Freq. Freq.", 
/*121*/  "  (sec)   (%)   (J)      (in)     (in)     (in)    (lb)  (lb)   (lb)   (lb)   (Hz)   (Hz) (Hz)",
/*122*/  "  (sec)   (%)   (J)      (mm)     (mm)     (mm)    (N)   (N)    (N)    (N)    (Hz)   (Hz) (Hz)",
/*123*/  "  Set   Set", 
/*124*/  "  AmpA  AmpB   Vel  ", 
/*125*/  "  (%)   (%)  (in/s) ",
/*126*/  "  (%)   (%)  (mm/s) ",
/*127*/  "Ampiezza (%)","Potenza (%)","Frequenza (Hz)","Dist Col (in)","Forza (lb)",
/*132*/  "Velocita (in/s)","Dist Col (mm)","Forza (N)","Velocita (mm/s)", "Dist Ass (in)",
/*137*/  "Dist Ass (mm)","Fase", "Current", "P(%)/Col Dist(mm)","P(%)/Col Dist(in)",
/*142*/  "P(%)/Force(N)", "P(%)/Force(lb)",
/*144*/  "Force(N)/Col Dist(mm)", "Force(lb)/Col Dist(in)"
};

// OmniLingua - End insert Italian strings here

// OmniLingua - Start to insert French strings here
const STR *const MessFr[] = {
       /* Header Info Index 0*/
/*0*/  "  Num et Nom Preset       : ",

        /* Control Level 5 with Encoder */
        /* Measurement Values Index 1 CONDENSED MODE*/
/*1*/   "  Numero                    Act.    Pui.   Act. Distance   Soud    Total   Force  Reg    Reg    Force Chg    Reg   Reg",
/*2*/   "  Cycle   Temps     Date    Tps     Crete  Ener Absolue  Dist.Rel Dist.Rel Trig.  ForceA ForceB Soud  Freq   AmpA  AmpB Vit.", 
/*3*/   "                   (m/d/y)  (sec)    (%)   (J)    (in)     (in)     (in)   (lb)   (lb)   (lb)   (lb)  (Hz)   (%)   (%)  (in/s)", 
/*4*/   "                   (d/m/y)  (sec)    (%)   (J)    (mm)     (mm)     (mm)   (N)    (N)    (N)    (N)   (Hz)   (%)   (%)  (mm/s)",

/* Graph label Index 5*/
/*5 */  "  Numero                    Act.    Pui.   Act. Distance   Soud    Total   Force  Reg    Reg    Force Chg    Reg   Reg",
/*6 */  "  Cycle   Temps     Date    Tps     Crete  Ener Absolue  Dist.Rel Dist.Rel Trig.  ForceA ForceB Soud  Freq   AmpA  AmpB",
/*7 */  "                   (m/d/y)  (sec)    (%)   (J)    (in)     (in)     (in)   (lb)   (lb)   (lb)   (lb)  (Hz)   (%)   (%) ",
/*8 */  "                   (d/m/y)  (sec)    (%)   (J)    (mm)     (mm)     (mm)   (N)    (N)    (N)    (N)   (Hz)   (%)   (%) ",
/*9 */  "/* UNUSED */",    
/*10*/  "/* UNUSED */","/* UNUSED */","/* UNUSED */","/* UNUSED */",
        /* Below graph Index 14*/
/*14*/  "Message Alarme   :",  
/*15*/  "Trigger (----)   :         Saut Amp.    :         Saut Force       :",
/*16*/  "Fin Ultrasons    :         Fin Maint.   :         Fin de Rech Soud :",
/*17*/  "NOTES             ",
/*18*/  "Pression Trigger        :  ____________________________________",
/*19*/  "Vit. Desc               :  ____________________________________",
/*20*/  "Pression Actuator       :",
/*21*/  "Drapeau1 comm. de pos.  :  ____________________________________",  
/*22*/  "Drapeau2 comm. de pos.  :  ____________________________________",  
/*23*/  "Position Colonn         :  ____________________________________",
/*24*/  "       Tps (sec)",            /* 24, bottom line of graphics*/

        /* not condensed weld summary*/
        /* Print Summary --> Control Level 5 with Encoder */

/*25*/  "  Numero Cycle  : ",
/*26*/  "  Temps         : ",
/*27*/  "  Date          : ",
/*28*/  "  Mode          : ",


/*29*/ "Note Speciale:", 
/*30*/ "Ech. Manuelle: Ce graph. Montre des parties du cycle. Pour voir le    ",
/*31*/ "cycle complet, reg. axe x sur tps soud. + Duree Mnt +        ", 
/*32*/ "Imp P-Oper utilise. Ce changement prendra effet au proch. Cycle.", 

/*33*/ "** ------------------------- Dernier 50  Donnees Hist. soud (contd.) ----------------------     **", 

/*34*/ "Les val. De reg. Amp ne peuvent pas etre atteintes en raison des tps de soud. Courts, pas", 
/*35*/ "amplitude pres du deb. Ou de la fin de soud. Ou dem. Ramp. Du syst.", 
/*36*/ "",/* UNUSED */

/*37*/  "TEMPS","ENERGIE","PUI. CRETE", "DIST.REL.","ABSOLUE","DETEC. MASSE","TECMODE","CONTINU", 
/*45*/  "TEMPS ","ENERGI","PUICRE"," D_R  "," ABS  ","DMASSE","TECMOD","CONTIN", 
// leave TPS string at 6 chars length! John fixed once, now I (Aare) had to do this over again

/*53*/  "** --------------------------- Dernier Donnees Hist. Soud 50 ---------------------------- **", 
/*54*/  "** ------------------------ Donnees Hist. Soud. 50 Fin de Chge -------------------------- **", 

/*55*/  "TRS",
    
        /* Control Level 1(t) */
/*56*/  "  Numero                    Act.     Chg   Reg", /* first line*/       
/*57*/  "  Cycle     Temps    Date   Temps    Freq  Amp", /* second line*/        
/*58*/  "                    (m/d/y) (sec)    (Hz)  (%)", /* third line lb*/
/*59*/  "                    (d/m/y) (sec)    (Hz)  (%)", /* third line lb*/

        /* Control Level 2(e) */
/*60*/  "  Numero                    Act.    Pui.   Act.  Chg   Reg", /* first line*/    
/*61*/  "  Cycle     Temps   Date    Temps   Crete  Ener  Freq  Amp.", /* second line*/  
/*62*/  "                   (m/d/y)  (sec)    (%)   (J)   (Hz)   (%)", /* third line lb*/
/*63*/  "                   (d/m/y)  (sec)    (%)   (J)   (Hz)   (%)", /* third line lb*/
/*64*/  "Pression Actuator      :  ____________________________________",
/*65*/  "",/* UNUSED */ 

        /* Control Level 4(d) with Encoder */
/*66*/  "  Numero                    Act.    Pui.  Act.  Distance  Soud     Total    Force Force  Chg   Reg   Reg", /* first line*/             
/*67*/  "  Cycle    Temps   Date     Temps   Crete Ener  Absolue   Dist.Rel.Dist.Rel.Trig. Soud   Freq  AmpA  AmpB Vit.",  /* second line*/ 
/*68*/  "                  (m/d/y)   (sec)    (%)  (J)     (in)      (in)     (in)   (lb)  (lb)   (Hz)  (%)   (%)  (in/s)", /* third line lb*/
/*69*/  "                  (d/m/y)   (sec)    (%)  (J)     (mm)      (mm)     (mm)   (N)   (N)    (Hz)  (%)   (%)  (mm/s)", /* third line mm*/

                        
        /* Control Level 3(a)  */
/*70*/  "  Numero                    Act.    Pui.   Act.  Chg   Reg   Reg",  /* first line   */  
/*71*/  "  Cycle    Temps   Date     Temps   Crete  Ener  Freq  AmpA  AmpB", /* second line  */
/*72*/  "                  (m/d/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",  /* third line lb*/
/*73*/  "                  (d/m/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",  /* third line mm*/
       
        /* Control Level 4(d) without Encoder */                                              
/*74*/  "  Numero                    Act.    Pui.   Act.  Chg   Reg   Reg",   /* first line   */ 
/*75*/  "  Cycle    Temps   Date     Temps   Crete  Ener  Freq  AmpA  AmpB",  /* second line  */ 
/*76*/  "                  (m/d/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",   /* third line lb*/
/*77*/  "                  (d/m/y)   (sec)    (%)   (J)   (Hz)  (%)   (%)",   /* third line mm*/

        /* Control Level 5(f) without Encoder */                                                                
/*78*/  "  Numero                    Act.  Pui.   Act.  Chg   Reg   Reg",  /* first line   */    
/*79*/  "  Cycle    Temps   Date     Temps Crete  Ener  Freq  AmpA  AmpB", /* second line  */  
/*80*/  "                  (m/d/y)   (sec) (%)    (J)   (Hz)  (%)   (%)",  /* third line lb*/
/*81*/  "                  (d/m/y)   (sec) (%)    (J)   (Hz)  (%)   (%)",  /* third line mm*/
/*82*/  "Trigger (----)   :         Saut Amp. :           ",




/* --------- NOT CONDENSED GRAPH WELD SUMMARY ------------*/

/* Print Summary --> Control Level 1(t) */
/*83*/  "",/* UNUSED */
/*84*/  "",/* UNUSED */
/*85*/  "",/* UNUSED */
/*86*/  "",/* UNUSED */

        /* Print Summary --> Control Level 2(e) */
/*87*/  "  Act.   Pui.   Act.    Freq   Freq   Chg   Reg",  
/*88*/  "  Temps  Crete Energie  Debut  Fin.   Freq  Amp.",
/*89*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)",
/*90*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)",

/*91*/ "Les val. De reg. Force ne peuvent pas etre atteintes en raison des tps de soud. Courts, et.",  
/*92*/ "force pres du deb. Ou de la fin de soud. Ou dem. Ramp. Du syst.",
/*93*/  "",/* UNUSED */
/*94*/  "",/* UNUSED */

        /* Print Summary --> Control Level 3(a) */
/*95*/  "  Act.   Pui.  Act.     Freq   Freq   Chg   Reg   Reg",   
/*96*/  "  Temps  Crete Energie  Debut  Fin.   Freq  AmpA  AmpB",   
/*97*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)   (%)", 
/*98*/  "  (sec)   (%)   (J)     (Hz)   (Hz)   (Hz)  (%)   (%)", 

        /* Print Summary --> Control Level 4(d) with AED Actuator */
/*99 */ "  Act.   Pui.  Act.    Distance Soud     Total    Force  Force Freq   Freq   Chg  ",   
/*100*/ "  Temps  Crete Energie Absolue  Dist.Rel.Dist.Rel.Trig.  Soud  Debut  Fin.   Freq",  
/*101*/ "  (sec)   (%)   (J)      (in)     (in)     (in)   (lb)   (lb)  (Hz)   (Hz)   (Hz)",
/*102*/ "  (sec)   (%)   (J)      (mm)     (mm)     (mm)    (N)    (N)  (Hz)   (Hz)   (Hz)",
/*103*/ "  Reg   Reg",
/*104*/ "  AmpA  AmpB   Vit.",
/*105*/ "  (%)   (%)  (in/s)",
/*106*/ "  (%)   (%)  (mm/s)",

        /* Print Summary --> Control Level 4(d) without Encoder */
/*107*/ "  Act.   Pui.   Act.   Freq   Freq   Chg   Reg   Reg",  
/*108*/ "  Temps  Crete Energie Debut  Fin.   Freq  AmpA  AmpB",    
/*109*/ "  (sec)  (%)     (J)   (Hz)   (Hz)   (Hz)   (%)   (%)",
/*110*/ "  (sec)  (%)     (J)   (Hz)   (Hz)   (Hz)   (%)   (%)",

                                                                                      
/* Print Summary --> Control Level 5(f) without Encoder */                 
/*111*/ "  Act.   Pui.   Act.   Freq   Freq   Chg   Reg   Reg",   
/*112*/ "  Temps  Crete Energie Debut  Fin.  Freq   AmpA  AmpB", 
/*113*/ "  (sec)   (%)     (J)  (Hz)   (Hz)   (Hz)   (%)   (%)", 
/*114*/ "  (sec)   (%)     (J)  (Hz)   (Hz)   (Hz)   (%)   (%)", 
/*115*/ "  AmpA  AmpB",
/*116*/ "  (%)   (%) ",
/*117*/ "  (%)   (%) ",
/*118*/ "",/* UNUSED */
/* Print Summary --> Control Level 5(f) with Encoder */                 
/*119*/  "  Act.   Pui.   Act.   Distance Soud      Total     Force Reg    Reg    Force Freq   Freq  Chg  ",   
/*120*/  "  Temps  Crete Energie  Absolu  Dist.Rel. Dist.Rel. Trig. ForceA ForceB Soud  Debut  Fin.  Freq ", 
/*121*/  "  (sec)   (%)   (J)      (in)     (in)     (in)     (lb)  (lb)   (lb)   (lb)  (Hz)   (Hz)  (Hz) ",
/*122*/  "  (sec)   (%)   (J)      (mm)     (mm)     (mm)     (N)   (N)    (N)    (N)   (Hz)   (Hz)  (Hz) ",
/*123*/  "  Reg   Reg",
/*124*/  "  AmpA  AmpB   Vit. ",
/*125*/  "  (%)   (%)  (in/s) ",
/*126*/  "  (%)   (%)  (mm/s) ",
/*127*/  "Amplitude (%)","Puiss (%)","Frequence (Hz)","Dist Rel (in)","Force (lb)",
/*132*/  "Vitesse (in/s)","Dist Rel (mm)","Force (N)","Vitesse (mm/s)", "Dist Abs (in)",
/*137*/  "Dist Abs (mm)","Phase", "Current", "P(%)/Col Dist(mm)","P(%)/Col Dist(in)",
/*142*/  "P(%)/Force(N)", "P(%)/Force(lb)",
/*144*/  "Force(N)/Col Dist(mm)", "Force(lb)/Col Dist(in)"
};

//OmniLingua - End insert French strings here

const STR **Mess[] = { MessEng, MessGer, MessSpn, MessItl, MessFr };

STR *PrintMessEng[]=               {/*0*/  " Current Setup      ",  /*-- Display 20 char on screen --*/ 
                                    /*1*/  " Last 50 Weld Data  ",  /*-- any less than 20 will be garbled --*/
                                    /*2*/  "   Weld Data        ",  
                                    /*3*/  "  Power Graph       ",  
                                    /*4*/  "  Amplitude Graph   ",  
                                    /*5*/  "  Frequency Graph   ",  
                                    /*6*/  "Collapse Dist. Graph",  
                                    /*7*/  "  Velocity  Graph   ",  
                                    /*8*/  "  Force Graph       ",   
                                    /*9*/  "    Printing        ",
                                    /*10*/ "   Abort Printing   ",
                                    /*11*/ "Printer is offline  ", 
                                    /*12*/ "Print Page Conflict ",
                                    /*13*/ "WeldsPerPage Updated",
                                    /*14*/ "  Graph data not    ",
                                    /*15*/ "  available see     ",
                                    /*16*/ " manual Section 7.5 ",
                                    /*17*/ "Absolute Dist. Graph",
                                    /*18*/ "  History data not  ",
                                    /*19*/ "Printer is    Online",
                                    /*20*/ "Printer is   Offline",
                                    /*21*/ "Printer  Powered Off",
                                    /*22*/ "Printer is      Busy",
                                    /*23*/ "Printer Out Of Paper",
                                    /*24*/ "  Horn Scan Graph   ",
                                    /*25*/ " DUPS Preset Report "
                                   };

//OmniLingua - Start German insertion here

STR *PrintMessGer[]=               {/*0*/  " Aktuell Einr.      ",  /*-- Display 20 char on screen --*/         
                                    /*1*/  " Letzt 50 Schw Daten",  /*-- any less than 20 will be garbled --*/  
                                    /*2*/  "   Schweissdaten    ",  
                                    /*3*/  "  Leistungsgrafik   ",  
                                    /*4*/  "  Amplituden Grafik ",  
                                    /*5*/  "  Frequenz Grafik   ",  
                                    /*6*/  "  Weg rel. Grafik   ",  
                                    /*7*/  "  Geschw. Grafik    ",
                                    /*8*/  "  Kraft Grafik      ",   
                                    /*9*/  "    Drucken         ",
                                    /*10*/ "  Drucken abbrechen ",
                                    /*11*/ "Drucker aus         ",
                                    /*12*/ "Seitenformat falsch ",  
                                    /*13*/ "SchwProSeite aktuell",  
                                    /*14*/ " Grafikdaten nicht  ",  
                                    /*15*/ " Verfuegbar siehe   ",  
                                    /*16*/ " Handb. Abschn. 7.5 ",
                                    /*17*/ "Weg abs Grafik      ",  
                                    /*18*/ "Keine Daten vorhand.",  // 21 characters?? Ask Barry
                                    /*19*/ "Drucker       Online",
                                    /*20*/ "Drucker aus         ",
                                    /*21*/ "Drucker          Aus",
                                    /*22*/ "Drucker       belegt",  
                                    /*23*/ "Drucker ohne Papier ",  
                                    /*24*/ "   Resonanzanalyse  ", //detrans
                                    /*25*/ " DUPS Preset Report "  //detrans
                                   };

//OmniLingua - End German insertion here
//OmniLingua - Start Spanish insertion here

STR *PrintMessSpn[]=               {/*0*/  " Config actual      ",  /*-- Display 20 char on screen --*/          
                                    /*1*/  " Ult 50 datos sold  ",  /*-- any less than 20 will be garbled --*/   
                                    /*2*/  "   Dats Sold        ",  
                                    /*3*/  "  Graf. Poten       ",  
                                    /*4*/  "  Graf. Amplitud    ",  
                                    /*5*/  "  Graf. Frecuencia  ",  
                                    /*6*/  "Grafo dist.colapso  ",  
                                    /*7*/  "  Graf. Velocidad   ",  
                                    /*8*/  "  Graf. Fuerza      ",   
                                    /*9*/  "    Imprimiendo     ",
                                    /*10*/ "   Cancelar Impres  ",
                                    /*11*/ "Impresor Fuera Linea",  
                                    /*12*/ "Impr. Conflicto Pag ",
                                    /*13*/ "SoldsPorPag Actualiz",  
                                    /*14*/ "  Datos grafo no    ",  
                                    /*15*/ "  disponib. Vea     ",  
                                    /*16*/ " seccion 7.5 manual ",  
                                    /*17*/ "Grafo dist.absolut  ",  
                                    /*18*/ "  Datos historial no",  
                                    /*19*/ "Impresora en   linea",
                                    /*20*/ "Impresor Fuera Linea",  
                                    /*21*/ "Impr.   desconectada",
                                    /*22*/ "Impresora    ocupada",  
                                    /*23*/ "Impresora  sin papel",  
                                    /*24*/ "Graf. Diagnosis Sono", //estrans
                                    /*25*/ " DUPS Preset Report "  //estrans
                                   };

//OmniLingua - End Spanish insertion here
//OmniLingua - Start Italian insertion here


STR *PrintMessItl[]=               {/*0*/  " Imp. corrente      ",  /*-- Display 20 char on screen --*/        
                                    /*1*/  " Ultimi 50 dati sald",  /*-- any less than 20 will be garbled --*/ 
                                    /*2*/  "   Dati sald.       ",  
                                    /*3*/  "  Graf. potenza     ",  
                                    /*4*/  "  Graf. ampiezza    ",  
                                    /*5*/  "  Graf. frequenza   ",  
                                    /*6*/  "Collassa Graf. Dist.",  
                                    /*7*/  "  Graf. velocita    ",  
                                    /*8*/  "  Graf. forza       ",   
                                    /*9*/  "    Stampa          ",
                                    /*10*/ "   Annulla stampa   ",
                                    /*11*/ "Stampnt non in linea",  
                                    /*12*/ "Stampa conflitto pag",
                                    /*13*/ "Sald.A Pagina Agg.  ",  
                                    /*14*/ "  Dati grafico non  ",  
                                    /*15*/ "  disponibili vedere",  
                                    /*16*/ " manuale Sezione 7.5",  
                                    /*17*/ "Graf Dist. Ass.     ",  
                                    /*18*/ "  Dati Crono. Non   ",  
                                    /*19*/ "Stampante   in linea",
                                    /*20*/ "Stampnt non in linea",  
                                    /*21*/ "Alim.  stampante Off",
                                    /*22*/ "Stampante   occupata",  
                                    /*23*/ "Stamp.   Senza carta",  
                                    /*24*/ "Graf. analisi sonot.", //ittrans
                                    /*25*/ " DUPS Preset Report "  //ittrans
                                   };

//OmniLingua - End Italian insertion here
//OmniLingua - Start French insertion here


STR *PrintMessFr[]=                {/*0*/  " Reg. actuel        ",  /*-- Display 20 char on screen --*/         
                                    /*1*/  " Dern. 50 dones soud",  /*-- any less than 20 will be garbled --*/  
                                    /*2*/  "   Donnes Soud      ",  
                                    /*3*/  "  Graph Puiss       ",  
                                    /*4*/  "  Graph Amplitude   ",  
                                    /*5*/  "  Graph Frequence   ",  
                                    /*6*/  "Graph Dist Relative ",  
                                    /*7*/  "  Graph Vitesse     ",  
                                    /*8*/  "  Graph Force       ",   
                                    /*9*/  "    Impressn        ",
                                    /*10*/ "   Annuler Impr.    ",
                                    /*11*/ "Imprimte Hrs Tension", 
                                    /*12*/ "Conflit Page Imprmt ",
                                    /*13*/ "Soud par page actuel",  
                                    /*14*/ "  Donnees graph non ",  
                                    /*15*/ "  disponible, voir  ",  
                                    /*16*/ " manuel, section 7.5",  
                                    /*17*/ "Graph Dist Absolue  ",  
                                    /*18*/ "  Donnees hist. non ",  
                                    /*19*/ "Imprimte    en ligne",
                                    /*20*/ "Imprimte Hrs Tension",
                                    /*21*/ "Imprim  hors tension",
                                    /*22*/ "Imprimante    occup.",  
                                    /*23*/ "Pas papier ds imprim",  
                                    /*24*/ "  Horn Scan Graph   ", //frtrans
                                    /*25*/ " DUPS Preset Report "  //frtrans
                                   };

//OmniLingua - End French insertion here

const STR **PrintMess[] = { PrintMessEng, PrintMessGer, PrintMessSpn, PrintMessItl, PrintMessFr };

const STR *const AlarmEng[] = {
                                                                                  

/**--------------------------------------------------**
 **        This group is the No Cycle Alarms         **
 **--------------------------------------------------**/

"NC0",                                                       /*0  NC0  RESERVED             */
"Upper Limit Timeout",                                       /*1  NC1  Upper Limit Timeout  */
"NC2",                                                       /*2  NC2                       */
"Trigger before Pretrigger",                                 /*3  NC3  Trg before Pretrg    */
"Trigger Timeout",                                           /*4  NC4  Trigger Timeout      */
"NC5",                                                       /*5  NC5                       */
"LLS abort before TRS",                                      /*6  NC6  LLS abort before TRS */
"External Cycle Abort",                                      /*7  NC7  External Cycle Abort */
"Missing Part Abort",                                        /*8  NC8  Missing Part Abort   */
"Abs Before Trg",                                            /*9  NC9  Absolute before Trg  */
"Amp Step before Trigger",                                   /*10 NC10 Amp Step before Trg  */
"Force Step before Trigger",                                 /*11 NC11 Frc Step before Trg  */
"Ground Detect Abort",                                       /*12 NC12 Ground Detect Abort  */
"External U/S Delay Timeout",                                /*13 NC13 ExtTrgDelay Timeout  */
"External Start Signal lost before cycle complete",          /*14 NC14 SVInterlock Lost     */
"External Start Input Timed out",                            /*15 NC15 SVInterlock Timeout  */
"NC16",                                                      /*16 NC16                      */
"NC17",                                                      /*17 NC17                      */
"NC18",                                                      /*18 NC18                      */
"NC19",                                                      /*19 NC19                      */
"NC20",                                                      /*20 NC20                      */
"NC21",                                                      /*21 NC21                      */
"NC22",                                                      /*22 NC22                      */
"NC23",                                                      /*23 NC23                      */
"NC24",                                                      /*24 NC24                      */
"NC25",                                                      /*25 NC25                      */
"NC26",                                                      /*26 NC26                      */
"NC27",                                                      /*27 NC27                      */
"NC28",                                                      /*28 NC28 RESERVED             */
"NC29",                                                      /*29 NC29 RESERVED             */
"NC30",                                                      /*30 NC30 RESERVED             */
"NC31",                                                      /*31 NC31 RESERVED             */






/**--------------------------------------------------**
 **        This group is the Overload Alarms         **
 **--------------------------------------------------**/

"OL0",                                                       /*32 OL0  RESERVED             */
"Test Overload",                                             /*33 OL1  Test Overload        */
"Pretrigger Overload",                                       /*34 OL2  Pretrigger Overload  */
"Seek Overload",                                             /*35 OL3  Seek Overload        */
"Power Supply Overload",                                     /*36 OL4  Power Supply O/L     */
"Continuous Power Exceeded",                                 /*37 OL5  Cont Pwr Limit       */
"Afterburst Overload",                                       /*38 OL6  Afterburst Overload  */
"Pre-Weld Seek Overload",                                    /*39 OL7  Pre-Weld Seek O/L    */
"Post Weld Seek Overload",                                   /*40 OL8  Post Weld Seek O/L   */
"OL9",                                                       /*41 OL9                       */
"Energy Brake Overload",                                     /*42 OL10 Energy Brake O/L     */
"OL11",                                                      /*43 OL11                      */
"OL12",                                                      /*44 OL12                      */
"OL13",                                                      /*45 OL13                      */
"OL14",                                                      /*46 OL14                      */
"OL15",                                                      /*47 OL15                      */
"OL16",                                                      /*48 OL16                      */
"OL17",                                                      /*49 OL17                      */
"OL18",                                                      /*50 OL18                      */
"OL19",                                                      /*51 OL19                      */
"OL20",                                                      /*52 OL20                      */
"OL21",                                                      /*53 OL21                      */
"OL22",                                                      /*54 OL22                      */
"OL23",                                                      /*55 OL23                      */
"OL24",                                                      /*56 OL24                      */
"OL25",                                                      /*57 OL25                      */
"OL26",                                                      /*58 OL26                      */
"OL27",                                                      /*59 OL27                      */
"OL28",                                                      /*60 OL28 RESERVED             */
"OL29",                                                      /*61 OL29 RESERVED             */
"OL30",                                                      /*62 OL30 RESERVED             */
"OL31",                                                      /*63 OL31 RESERVED             */


                                                             
                                                             
                                                             
/**---------------------------------------------------------*
 **    The next new group is Equipment Failure Alarms       *
 **---------------------------------------------------------*/

"EQ0",                                                           /*64 EQ0  RESERVED             */
"Encoder Failure",                                               /*65 EQ1  Encoder Fail         */
"Upper Limit Switch Failed",                                     /*66 EQ2  Upper Limit Switch   */
"Upper Limit Switch Failed",                                     /*67 EQ3  Upper Limit Switch   */
"Door/Trigger Switch Failure",                                   /*68 EQ4  Door Sw Fail         */
"Loadcell Failure",                                              /*69 EQ5  Loadcell Fail        */
"Solenoid Drive Failure",                                        /*70 EQ6  Solenoid Drive Fail  */
"Thermal Overload",                                              /*71 EQ7  Thermal Overload     */
"Failure of Preset Data or Battery Backed Ram",                  /*72 EQ8  Preset Data/BBR      */
"Horn Return Timeout",                                           /*73 EQ9  Horn Return Timeout  */
"Actuator NovRam Failed",                                        /*74 EQ10 Actuator NovRam      */
"Power Supply NovRam Failed",                                    /*75 EQ11 P/S NovRam           */
"Start Switch Stagger Time Missed",                              /*76 EQ12 Start Sw Time        */
"Multi Purpose Switch Failed",                                   /*77 EQ13 MPS Switch Failed    */
"Wrong Actuator AEF/AOP Cannot be used with This Level Control", /*78 EQ14 Wrong Actuator       */
"Ultrasonic Power Supply Not Present or Failed",                 /*79 EQ15 Ultrasonics P/S      */
"Printer Buffer Full",                                           /*80 EQ16 Printer Buffer Full  */
"Start Switch Closed Failure",                                   /*81 EQ17 Start Switch Closed  */
"Pretrigger Timeout",                                            /*82 EQ18 Pretrigger Timeout   */
"EQ19",                                                          /*83 EQ19                      */
"Recalibrate Actuator",                                          /*84 EQ20 Recalibrate Actuator */
"Actuator Clear Function Failure",                               /*85 EQ21 Act Clear Function   */
"Failure of R/F loop",                                           /*86 EQ22 Stack                */
"Start Switches Lost",                                           /*87 EQ23 Start Switches Lost  */
"The actuator type was changed since last weld cycle",           /*88 EQ24 Actuator Type        */
"System Pressure Setting Incorrect",                             /*89 EQ25 Sys. Pres. Incorrect */
"EQ26",                                                          /*90 EQ26                      */
"EQ27",                                                          /*91 EQ27                      */
"EQ28",                                                          /*92 EQ28 RESERVED             */
"EQ29",                                                          /*93 EQ29 RESERVED             */
"EQ30",                                                          /*94 EQ30 RESERVED             */
"EQ31",                                                          /*95 EQ31 RESERVED             */





                           
/**---------------------------------------------------**
 **    The next new group is Cycle Modified Alarms    **
 **---------------------------------------------------**/

"CM0",                                                           /*96  CM0  RESERVED             */
"Trigger Lost during Hold",                                      /*97  CM1  Trigger Lost in Hold */
"Ground Detect Abort",                                           /*98  CM2  Ground Detect Abort  */
"Max Timeout",                                                   /*99  CM3  Max Timeout          */
"Time Value for Amplitude Step not Reached",                     /*100 CM4  No Amplitude Step    */
"Time Value for Force Step not Reached",                         /*101 CM5  No Force Step        */
"Energy Value for Amplitude Step not Reached",                   /*102 CM6  No Amplitude Step    */
"Energy Value for Force Step not Reached",                       /*103 CM7  No Force Step        */
"Collapse Distance for Amplitude Step not Reached",              /*104 CM8  No Amplitude Step    */
"Absolute Distance for Amplitude Step not Reached",              /*105 CM9  No Amplitude Step    */
"Power Level for Force Step not Reached",                        /*106 CM10 No Force Step        */
"Power Level for Amplitude Step not Reached",                    /*107 CM11 No Amplitude Step    */
"External signal for Amplitude Step did not occur",              /*108 CM12 No Amplitude Step    */
"External signal for Force Step did not occur",                  /*109 CM13 No Force Step        */
"Trigger Lost during Weld",                                      /*110 CM14 Trg Lost during Weld */
"External Cycle Abort",                                          /*111 CM15 External Cycle Abort */
"Amplitude B was not reached because the weld was too short",    /*112 CM16 Amp B Not Reached    */
"Memory DIP Switch on P/S may be off",                           /*113 CM17 Memory Reset         */
"Amplitude A not reached because weld was too short",            /*114 CM18 Amp B Not Reached    */
"Amplitude B was not reached because the weld was too short",    /*115 CM19 Amp B Not Reached    */
"Amplitude exceeded because the weld was too short",             /*116 CM20 Amp Exceeded         */
"Energy Not Reached",                                            /*117 CM21 Energy Not Reached   */
"Trigger Force is Greater Than the End Force",                   /*118 CM22 Trigger > End Force  */
"Collapse Distance for Force Step not Reached",                  /*119 CM23 No Force Step        */
"CM24",                                                          /*120 CM24                      */
"CM25",                                                          /*121 CM25                      */
"CM26",                                                          /*122 CM26                      */
"CM27",                                                          /*123 CM27                      */
"CM28",                                                          /*124 CM28                      */
"CM29",                                                          /*125 CM29 RESERVED             */
"CM30",                                                          /*126 CM30 RESERVED             */
"CM31",                                                          /*127 CM31 RESERVED             */
                                                                   



/**----------------------------------------------**
 **  The next new group is Calibrate Alarms      **
 **----------------------------------------------**/

"CA0",                                                           /*128 CA0  RESERVED             */
"CA1 ",                                                          /*129 CA1                       */
"CA2 ",                                                          /*130 CA2                       */
"CA3 ",                                                          /*131 CA3                       */
"CA4 ",                                                          /*132 CA4                       */
"CA5 ",                                                          /*133 CA5                       */
"CA6 ",                                                          /*134 CA6                       */
"CA7 ",                                                          /*135 CA7                       */
"CA8 ",                                                          /*136 CA8                       */
"CA9 ",                                                          /*137 CA9                       */
"CA10",                                                          /*138 CA10                      */
"CA11",                                                          /*139 CA11                      */
"CA12",                                                          /*140 CA12                      */
"CA13",                                                          /*141 CA13                      */
"CA14",                                                          /*142 CA14                      */
"CA15",                                                          /*143 CA15                      */
"CA16",                                                          /*144 CA16                      */
"CA17",                                                          /*145 CA17                      */
"CA18",                                                          /*146 CA18                      */
"CA19",                                                          /*147 CA19                      */
"CA20",                                                          /*148 CA20                      */
"CA21",                                                          /*149 CA21                      */
"CA22",                                                          /*150 CA22                      */
"CA23",                                                          /*151 CA23                      */

"CA24",                                                          /*152 CA24                      */
"CA25",                                                          /*153 CA25                      */
"CA26",                                                          /*154 CA26                      */
"CA27",                                                          /*155 CA27                      */
"CA28",                                                          /*156 CA28 RESERVED             */
"CA29",                                                          /*157 CA29 RESERVED             */
"CA30",                                                          /*158 CA30 RESERVED             */
"CA31",                                                          /*159 CA31 RESERVED             */
                                                                   


/**--------------------------------------------**
 **       The next new group is Warnings       **
 **--------------------------------------------**/

"WA0",                                                           /*160 WA0  RESERVED             */
"Actuator Clear distance not reached",                           /*161 WA1                       */
"Energy Compensation Maximum Energy Reached",                    /*162 WA2  Max Energy Reached   */
"",                                                              /*163 WA3  Printer Buffer 80%   */
"WA4",                                                           /*164 WA4  Cont Pwr Limit       */
"Peak Power Cutoff",                                             /*165 WA5  Peak Power Cutoff    */
"Absolute Distance Cutoff",                                      /*166 WA6  Absolute Cutoff      */
"Weld Time was Extended for Energy Compensation",                /*167 WA7  Time Extended        */
"WA8",                                                           /*168 WA8                       */
"Collapse Cutoff",                                               /*169 WA9  Collapse Cutoff      */
"WA10",                                                          /*170 WA10                      */
"Ultrasonics Disabled by user input",                            /*171 WA11 Sonics Disabled      */
"WA12",                                                          /*172 WA12                      */
"WA13",                                                          /*173 WA13                      */
"WA14",                                                          /*174 WA14                      */
"WA15",                                                          /*175 WA15                      */
"WA16",                                                          /*176 WA16                      */
"WA17",                                                          /*177 WA17                      */
"WA18",                                                          /*178 WA18                      */
"WA19",                                                          /*179 WA19                      */
"WA20",                                                          /*180 WA20                      */
"WA21",                                                          /*181 WA21                      */
"WA22",                                                          /*182 WA22                      */
"WA23",                                                          /*183 WA23                      */
"WA24",                                                          /*184 WA24                      */
"WA25",                                                          /*185 WA25                      */
"WA26",                                                          /*186 WA26                      */
"WA27",                                                          /*187 WA27                      */
"WA28",                                                          /*188 WA28 RESERVED             */
"WA29",                                                          /*189 WA29 RESERVED             */
"WA30",                                                          /*190 WA30 RESERVED             */
"WA31",                                                          /*191 WA31 RESERVED             */



/**------------------------------------------------------------**
 **        The next new group is Process Reject Alarms         **
 **------------------------------------------------------------**/

"PR0",                                                            /*192 PR0  RESERVED             */
"-Reject Energy Limit",                                           /*193 PR1  -R Energy Limit      */
"+Reject Energy Limit",                                           /*194 PR2  +R Energy Limit      */
"-Reject Peak Power Limit",                                       /*195 PR3  -R Pk Power Limit    */
"+Reject Peak Power Limit",                                       /*196 PR4  +R Pk Power Limit    */
"-Reject Collapse Distance Limit",                                /*197 PR5  -R Col Dist Limit    */
"+Reject Collapse Distance Limit",                                /*198 PR6  +R Col Dist Limit    */
"-Reject Absolute Distance Limit",                                /*199 PR7  -R Abs Dist Limit    */
"+Reject Absolute Distance Limit",                                /*200 PR8  +R Abs Dist Limit    */
"-Reject Trigger Distance Limit",                                 /*201 PR9  -R Trig Dist Limit   */
"+Reject Trigger Distance Limit",                                 /*202 PR10 +R Trig Dist Limit   */
"-Reject Weld Force Limit",                                       /*203 PR11 -R Max Force Limit   */
"+Reject Weld Force Limit",                                       /*204 PR12 +R Max Force Limit   */
"-Reject Time Limit",                                             /*205 PR13 -R Time Limit        */
"+Reject Time Limit",                                             /*206 PR14 +R Time Limit        */
"PR15",                                                           /*207 PR15                      */
"PR16",                                                           /*208 PR16                      */
"PR17",                                                           /*209 PR17                      */
"Lower Limit not Reached",                                        /*210 PR18 LL Not Reached       */
"PR19",                                                           /*211 PR19                      */
"PR20",                                                           /*212 PR20                      */
"PR21",                                                           /*213 PR21                      */
"PR22",                                                           /*214 PR22                      */
"PR23",                                                           /*215 PR23                      */
"PR24",                                                           /*216 PR24                      */
"PR25",                                                           /*217 PR25                      */
"PR26",                                                           /*218 PR26                      */
"PR27",                                                           /*219 PR27                      */
"PR28",                                                           /*220 PR28 RESERVED             */
"PR29",                                                           /*221 PR29 RESERVED             */
"PR30",                                                           /*222 PR30 RESERVED             */
"PR31",                                                           /*223 PR31 RESERVED             */
                                                                    



/**-----------------------------------------------------------**
 **        The next new group is Process Suspect Alarms       **
 **-----------------------------------------------------------**/

"PS0",                                                            /*224 PS0  RESERVED             */
"-Suspect Energy Limit",                                          /*225 PS1  -S Energy Limit      */
"+Suspect Energy Limit",                                          /*226 PS2  +S Energy Limit      */
"-Suspect Peak Power Limit",                                      /*227 PS3  -S Pk Power Limit    */
"+Suspect Peak Power Limit",                                      /*228 PS4  +S Pk Power Limit    */
"-Suspect Collapse Distance Limit",                               /*229 PS5  -S Col Dist Limit    */
"+Suspect Collapse Distance Limit",                               /*230 PS6  +S Col Dist Limit    */
"-Suspect Absolute Distance Limit",                               /*231 PS7  -S Abs Dist Limit    */
"+Suspect Absolute Distance Limit",                               /*232 PS8  +S Abs Dist Limit    */
"-Suspect Trigger Distance Limit",                                /*233 PS9  -S Trig Dist Limit   */
"+Suspect Trigger Distance Limit",                                /*234 PS10 +S Trig Dist Limit   */
"-Suspect Weld Force Limit",                                      /*235 PS11 -S Max Force Limit   */
"+Suspect Weld Force Limit",                                      /*236 PS12 +S Max Force Limit   */
"-Suspect Time Limit",                                            /*237 PS13 -S Time Limit        */
"+Suspect Time Limit",                                            /*238 PS14 +S Time Limit        */
"PS15",                                                           /*239 PS15                      */
"PS16",                                                           /*240 PS16                      */
"PS17",                                                           /*241 PS17                      */
"PS18",                                                           /*242 PS18                      */
"PS19",                                                           /*243 PS19                      */
"PS20",                                                           /*244 PS20                      */
"PS21",                                                           /*245 PS21                      */
"PS22",                                                           /*246 PS22                      */
"PS23",                                                           /*247 PS23                      */
"PS24",                                                           /*248 PS24                      */
"PS25",                                                           /*249 PS25                      */
"PS26",                                                           /*250 PS26                      */
"PS27",                                                           /*251 PS27                      */
"PS28",                                                           /*252 PS28 RESERVED             */
"PS29",                                                           /*253 PS29 RESERVED             */
"PS30",                                                           /*254 PS30 RESERVED             */
"PS31"                                                            /*255 PS31 RESERVED             */
                                                                    
};


//OmniLingua - Start German insertion here

const STR *const AlarmGer[] = {
                                                                                  

/**--------------------------------------------------**
 **        This group is the No Cycle Alarms         **
 **--------------------------------------------------**/

"NC0",                                               /*0  NC0  RESERVED             */
"Oberer Grenzwert Zeitueberschreitung",              /*1  NC1  Upper Limit Timeout  */
"NC2",                                               /*2  NC2                       */
"Trigger vor Pretrigger",                            /*3  NC3  Trg before Pretrg    */
"Trigger Zeitueberschreitung",                       /*4  NC4  Trigger Timeout      */
"NC5",                                               /*5  NC5                       */
"LLS Abbruch vor Trigger",                           /*6  NC6  LLS abort before TRS */
"Externer Zyklusabbruch",                            /*7  NC7  External Cycle Abort */
"Fehlendes Teil Abbruch",                            /*8  NC8  Missing Part Abort   */
"Abs. vor Trigger",                                  /*9  NC9  Absolute before Trg  */
"Amplituden Profil vor Trigger",                     /*10 NC10 Amp Step before Trg  */
"Kraft Profil vor Trigger",                          /*11 NC11 Frc Step before Trg  */
"Abbruch Metallkontakt",                             /*12 NC12 Ground Detect Abort  */
"Zeitueberschreitung Ext Trigger Verzoegerung",      /*13 NC13 Trg Delay Timeout    */
"Signal fuer ext Magnetventil vor Zyklusende verloren",/*14 NC14 SV Interlock Lost    */
"Zeitueberschreitung Eingang fuer ext Magnetventil", /*15 NC15 SV Interlock Timeout */
"NC16",                                              /*16 NC16                      */
"NC17",                                              /*17 NC17                      */
"NC18",                                              /*18 NC18                      */
"NC19",                                              /*19 NC19                      */
"NC20",                                              /*20 NC20                      */
"NC21",                                              /*21 NC21                      */
"NC22",                                              /*22 NC22                      */
"NC23",                                              /*23 NC23                      */
"NC24",                                              /*24 NC24                      */
"NC25",                                              /*25 NC25                      */
"NC26",                                              /*26 NC26                      */
"NC27",                                              /*27 NC27                      */
"NC28",                                              /*28 NC28 RESERVED             */
"NC29",                                              /*29 NC29 RESERVED             */
"NC30",                                              /*30 NC30 RESERVED             */
"NC31",                                              /*31 NC31 RESERVED             */






/**--------------------------------------------------**
 **        This group is the Overload Alarms         **
 **--------------------------------------------------**/

"OL0",                                               /*32 OL0  RESERVED             */
"Test Ueberlast",                                    /*33 OL1  Test Overload        */
"Pretrigger Ueberlast",                              /*34 OL2  Pretrigger Overload  */
"Ueberlastsuche Param. Schweissung",                 /*35 OL3  Seek Overload        */
"Stromversorgung Ueberlast",                         /*36 OL4  Power Supply O/L     */
"Kontinuierliche Leistung ueberschritten",           /*37 OL5  Cont Pwr Limit       */
"Nachimpuls Ueberlast",                              /*38 OL6  Afterburst Overload  */
"Such-Ueberlast vor Schweissung",                    /*39 OL7  Pre-Weld Seek O/L    */
"Ueberlast nach Frequenzsuche nach Schweissung",     /*40 OL8  Post Weld Seek O/L   */
"OL9",                                               /*41 OL9                       */
"Ueberlast waehrend Energieunterbrechung",           /*42 OL10 Energy Brake O/L     */
"OL11",                                              /*43 OL11                      */
"OL12",                                              /*44 OL12                      */
"OL13",                                              /*45 OL13                      */
"OL14",                                              /*46 OL14                      */
"OL15",                                              /*47 OL15                      */
"OL16",                                              /*48 OL16                      */
"OL17",                                              /*49 OL17                      */
"OL18",                                              /*50 OL18                      */
"OL19",                                              /*51 OL19                      */
"OL20",                                              /*52 OL20                      */
"OL21",                                              /*53 OL21                      */
"OL22",                                              /*54 OL22                      */
"OL23",                                              /*55 OL23                      */
"OL24",                                              /*56 OL24                      */
"OL25",                                              /*57 OL25                      */
"OL26",                                              /*58 OL26                      */
"OL27",                                              /*59 OL27                      */
"OL28",                                              /*60 OL28 RESERVED             */
"OL29",                                              /*61 OL29 RESERVED             */
"OL30",                                              /*62 OL30 RESERVED             */
"OL31",                                              /*63 OL31 RESERVED             */


                                                             
                                                             
                                                             
/**---------------------------------------------------------*
 **    The next new group is Equipment Failure Alarms       *
 **---------------------------------------------------------*/


"EQ0",                                                   /*64 EQ0  RESERVED             */
"Codierfehler",                                          /*65 EQ1  Encoder Fail         */
"ULS ausgefallen",                                       /*66 EQ2  Upper Limit Switch   */
"ULS ausgefallen",                                       /*67 EQ3  Upper Limit Switch   */
"Tuer/Trigger Schalter Ausfall",                         /*68 EQ4  Door Sw Fail         */
"Fehler Kraftaufnehmer",                                 /*69 EQ5  Loadcell Fail        */
"Fehler Magnetventil",                                   /*70 EQ6  Solenoid Drive Fail  */
"Thermische Ueberlast",                                  /*71 EQ7  Thermal Overload     */
"Fehler Voreinstelldaten oder Puffer-Batterie Ram",      /*72 EQ8  Preset Data/BBR      */
"Horn zurueck Zeitueberschreitung",                      /*73 EQ9  Horn Return Timeout  */
"VE NovRam Ausfall",                                     /*74 EQ10 Actuator NovRam      */
"Ausfall Stromversorgung NovRam",                        /*75 EQ11 P/S NovRam           */
"Starttaster nicht gleichzeitig betaetigt",              /*76 EQ12 Start Sw Time        */
"MPS Ausfall",                                           /*77 EQ13 MPS Switch Failed    */
"Falscher AEF/AOF, kann nicht mit diesem Level benutzt werden", /*78 EQ14 Wrong Actuator       */
"Generator nicht vorhanden oder ausgefallen",            /*79 EQ15 Ultrasonics P/S      */
"Druckerpuffer voll",                                    /*80 EQ16 Printer Buffer Full  */
"Fehler Starttaster geschlossen",                        /*81 EQ17 Start Switch Closed  */
"Pretrigger Zeitueberschreitung",                        /*82 EQ18 Pretrigger Timeout   */
"",                                                      /*83 EQ19                      */
"VE neu kalibrieren",                                    /*84 EQ20 Recalibrate Actuator */
"VE Ausfall Loeschfunktion",                             /*85 EQ21 Act Clear Function   */
"Fehler H/F-Schleife",                                   /*86 EQ22 Stack                */
"Starttaster verloren",                                  /*87 EQ23 Start Switches Lost  */
"Der VE-Typ wurde seit letztem Schweisszyklus geaendert",/*88 EQ24 Actuator Type        */
"Systemdruckeinstellung falsch",                         /*89 EQ25 Sys. Pres. Incorrect */
"EQ26",                                                  /*90 EQ26                      */
"EQ27",                                                  /*91 EQ27                      */
"EQ28",                                                  /*92 EQ28 RESERVED             */
"EQ29",                                                  /*93 EQ29 RESERVED             */
"EQ30",                                                  /*94 EQ30 RESERVED             */
"EQ31",                                                  /*95 EQ31 RESERVED             */





                           
/**---------------------------------------------------**
 **    The next new group is Cycle Modified Alarms    **
 **---------------------------------------------------**/

"CM0",                                                   /*96  CM0  RESERVED             */
"Trigger waehrend der Haltezeit verloren",               /*97  CM1  Trigger Lost in Hold */
"Abbruch Metallkontakt",                                 /*98  CM2  Ground Detect Abort  */
"Max Zeitueberschreitung",                               /*99  CM3  Max Timeout          */
"Zeitwert fuer Amplitudenprofil nicht erreicht",         /*100 CM4  No Amplitude Step    */
"Zeitwert fuer Kraftprofil nicht erreicht",              /*101 CM5  No Force Step        */
"Energiewert fuer Amplitudenprofil nicht erreicht",      /*102 CM6  No Amplitude Step    */
"Energiewert fuer Kraftprofil nicht erreicht",           /*103 CM7  No Force Step        */
"Weg rel. fuer Amplitudenprofil nicht erreicht",         /*104 CM8  No Amplitude Step    */
"Abs. fuer Amplitudenprofil nicht erreicht",             /*105 CM9  No Amplitude Step    */
"Leistung fuer Kraftprofil nicht erreicht",              /*106 CM10 No Force Step        */
"Leistung fuer Amplitudenprofil nicht erreicht",         /*107 CM11 No Amplitude Step    */
"Externes Signal fuer Amplitudenprofil nicht aufgetreten",/*108 CM12 No Amplitude Step    */
"Externes Signal fuer Kraftstufe nicht aufgetreten",     /*109 CM13 No Force Step        */
"Trigger waehrend der Schweissung verloren",             /*110 CM14 Trg Lost during Weld */
"Externer Zyklusabbruch",                                /*111 CM15 External Cycle Abort */
"Amplitude B wurde nicht erreicht, da Schweissung zu kurz",/*112 CM16 Amp B Not Reached    */
"Jumper J55 des Generator falsch eingestellt",             /*113 CM17 Amp Not Reached      */
"Amplitude A wurde nicht erreicht, da Schweissung zu kurz",/*114 CM18 Amp B Not Reached    */
"Amplitude B wurde nicht erreicht, da Schweissung zu kurz",/*115 CM19 Amp B Not Reached    */
"Amplitude ueberschritten, da Schweissung zu kurz",      /*116 CM20 Amp Exceeded         */
"Energie nicht erreicht",                                /*117 CM21 Energy Not Reached   */
"Triggerkraft groesser als Endkraft",                    /*118 CM22 Trigger > End Force  */
"Weg rel. fuer Kraftprofil nicht erreicht",              /*119 CM23 No Force Step        */
"CM24",                                                  /*120 CM24                      */
"CM25",                                                  /*121 CM25                      */
"CM26",                                                  /*122 CM26                      */
"CM27",                                                  /*123 CM27                      */
"CM28",                                                  /*124 CM28                      */
"CM29",                                                  /*125 CM29 RESERVED             */
"CM30",                                                  /*126 CM30 RESERVED             */
"CM31",                                                  /*127 CM31 RESERVED             */
                                                                   



/**----------------------------------------------**
 **  The next new group is Calibrate Alarms      **
 **----------------------------------------------**/

"CA0",                                                   /*128 CA0  RESERVED             */
"CA1 ",                                                  /*129 CA1                       */
"CA2 ",                                                  /*130 CA2                       */
"CA3 ",                                                  /*131 CA3                       */
"CA4 ",                                                  /*132 CA4                       */
"CA5 ",                                                  /*133 CA5                       */
"CA6 ",                                                  /*134 CA6                       */
"CA7 ",                                                  /*135 CA7                       */
"CA8 ",                                                  /*136 CA8                       */
"CA9 ",                                                  /*137 CA9                       */
"CA10",                                                  /*138 CA10                      */
"CA11",                                                  /*139 CA11                      */
"CA12",                                                  /*140 CA12                      */
"CA13",                                                  /*141 CA13                      */
"CA14",                                                  /*142 CA14                      */
"CA15",                                                  /*143 CA15                      */
"CA16",                                                  /*144 CA16                      */
"CA17",                                                  /*145 CA17                      */
"CA18",                                                  /*146 CA18                      */
"CA19",                                                  /*147 CA19                      */
"CA20",                                                  /*148 CA20                      */
"CA21",                                                  /*149 CA21                      */
"CA22",                                                  /*150 CA22                      */
"CA23",                                                  /*151 CA23                      */
"CA24",                                                  /*152 CA24                      */
"CA25",                                                  /*153 CA25                      */
"CA26",                                                  /*154 CA26                      */
"CA27",                                                  /*155 CA27                      */
"CA28",                                                  /*156 CA28 RESERVED             */
"CA29",                                                  /*157 CA29 RESERVED             */
"CA30",                                                  /*158 CA30 RESERVED             */
"CA31",                                                  /*159 CA31 RESERVED             */
                                                                   


/**--------------------------------------------**
 **       The next new group is Warnings       **
 **--------------------------------------------**/

"WA0",                                                   /*160 WA0  RESERVED             */
"VE Loeschdistanz nicht erreicht",                       /*161 WA1                       */
"Energieausgleich Max Energie erreicht",                 /*162 WA2  Max Energy Reached   */
"",                                                      /*163 WA3  Printer Buffer 80%   */
"WA4",                                                   /*164 WA4  Cont Pwr Limit       */
"Spitzenleist. Abschaltung",                             /*165 WA5  Peak Power Cutoff    */
"Abschaltung Weg absolut",                               /*166 WA6  Absolute Cutoff      */
"Schweisszeit ueberschritten fuer Energieausgleich",     /*167 WA7  Time Extended        */
"WA8",                                                   /*168 WA8                       */
"Rel. Abschaltung",                                      /*169 WA9  Collapse Cutoff      */
"WA10",                                                  /*170 WA10                      */
"Ultraschall durch Benutzereingabe deaktiviert",         /*171 WA11  Sonics Disabled     */
"WA12",                                                  /*172 WA12                      */
"WA13",                                                  /*173 WA13                      */
"WA14",                                                  /*174 WA14                      */
"WA15",                                                  /*175 WA15                      */
"WA16",                                                  /*176 WA16                      */
"WA17",                                                  /*177 WA17                      */
"WA18",                                                  /*178 WA18                      */
"WA19",                                                  /*179 WA19                      */
"WA20",                                                  /*180 WA20                      */
"WA21",                                                  /*181 WA21                      */
"WA22",                                                  /*182 WA22                      */
"WA23",                                                  /*183 WA23                      */
"WA24",                                                  /*184 WA24                      */
"WA25",                                                  /*185 WA25                      */
"WA26",                                                  /*186 WA26                      */
"WA27",                                                  /*187 WA27                      */
"WA28",                                                  /*188 WA28 RESERVED             */
"WA29",                                                  /*189 WA29 RESERVED             */
"WA30",                                                  /*190 WA30 RESERVED             */
"WA31",                                                  /*191 WA31 RESERVED             */



/**------------------------------------------------------------**
 **        The next new group is Process Reject Alarms         **
 **------------------------------------------------------------**/

"PR0",                                                    /*192 PR0  RESERVED             */
"-Aussch Energie Grenzwert",                              /*193 PR1  -R Energy Limit      */
"+Aussch Energie Grenzwert",                              /*194 PR2  +R Energy Limit      */
"-Aussch Spitzenleist. Grenzwert",                        /*195 PR3  -R Pk Power Limit    */
"+Aussch Spitzenleistung Grenzwert",                      /*196 PR4  +R Pk Power Limit    */
"-Aussch Weg rel. Grenzwert",                             /*197 PR5  -R Col Dist Limit    */
"+Aussch Rel. Grenzwert",                                 /*198 PR6  +R Col Dist Limit    */
"-Aussch Weg abs. Grenzwert",                             /*199 PR7  -R Abs Dist Limit    */
"+Aussch Abs. Grenzwert",                                 /*200 PR8  +R Abs Dist Limit    */
"-Aussch Triggerweg Grenzwert",                           /*201 PR9  -R Trig Dist Limit   */
"+Aussch Triggerweg Grenzwert",                           /*202 PR10 +R Trig Dist Limit   */
"-Aussch Schweisskraft Grenzwert",                        /*203 PR11 -R Max Force Limit   */
"+Aussch Schweisskraft Grenzwert",                        /*204 PR12 +R Max Force Limit   */
"-Aussch Zeit Grenzwert",                                 /*205 PR13 -R Time Limit        */
"+Aussch Zeit Grenzwert",                                 /*206 PR14 +R Time Limit        */
"PR15",                                                   /*207 PR15                      */
"PR16",                                                   /*208 PR16                      */
"PR17",                                                   /*209 PR17                      */
"Unterer Grenzwert nicht erreicht",                       /*210 PR18 LL Not Reached       */
"PR19",                                                   /*211 PR19                      */
"PR20",                                                   /*212 PR20                      */
"PR21",                                                   /*213 PR21                      */
"PR22",                                                   /*214 PR22                      */
"PR23",                                                   /*215 PR23                      */
"PR24",                                                   /*216 PR24                      */
"PR25",                                                   /*217 PR25                      */
"PR26",                                                   /*218 PR26                      */
"PR27",                                                   /*219 PR27                      */
"PR28",                                                   /*220 PR28 RESERVED             */
"PR29",                                                   /*221 PR29 RESERVED             */
"PR30",                                                   /*222 PR30 RESERVED             */
"PR31",                                                   /*223 PR31 RESERVED             */
                                                                    



/**-----------------------------------------------------------**
 **        The next new group is Process Suspect Alarms       **
 **-----------------------------------------------------------**/

"PS0",                                                    /*224 PS0  RESERVED             */
"-Pruefe Energie Grenzwert",                              /*225 PS1  -S Energy Limit      */
"+Pruefe Energie Grenzwert",                              /*226 PS2  +S Energy Limit      */
"-Pruefe Spitzenleist. Grenzwert",                        /*227 PS3  -S Pk Power Limit    */
"+Pruefe Spitzenleistung Grenzwert",                      /*228 PS4  +S Pk Power Limit    */
"-Pruefe Weg rel. Grenzwert",                             /*229 PS5  -S Col Dist Limit    */
"+Pruefe Rel. Grenzwert",                                 /*230 PS6  +S Col Dist Limit    */
"-Pruefe Weg abs. Grenzwert",                             /*231 PS7  -S Abs Dist Limit    */
"+Pruefe Abs. Grenzwert",                                 /*232 PS8  +S Abs Dist Limit    */
"-Pruefe Triggerweg Grenzwert",                           /*233 PS9  -S Trig Dist Limit   */
"+Pruefe Triggerweg Grenzwert",                           /*234 PS10 +S Trig Dist Limit   */
"-Pruefe Schweisskraft Grenzwert",                        /*235 PS11 -S Max Force Limit   */
"+Pruefe Schweisskraft Grenzwert",                        /*236 PS12 +S Max Force Limit   */
"-Pruefe Zeit Grenzwert",                                 /*237 PS13 -S Time Limit        */
"+Pruefe Zeit Grenzwert",                                 /*238 PS14 +S Time Limit        */
"PS15",                                                   /*239 PS15                      */
"PS16",                                                   /*240 PS16                      */
"PS17",                                                   /*241 PS17                      */
"PS18",                                                   /*242 PS18                      */
"PS19",                                                   /*243 PS19                      */
"PS20",                                                   /*244 PS20                      */
"PS21",                                                   /*245 PS21                      */
"PS22",                                                   /*246 PS22                      */
"PS23",                                                   /*247 PS23                      */
"PS24",                                                   /*248 PS24                      */
"PS25",                                                   /*249 PS25                      */
"PS26",                                                   /*250 PS26                      */
"PS27",                                                   /*251 PS27                      */
"PS28",                                                   /*252 PS28 RESERVED             */
"PS29",                                                   /*253 PS29 RESERVED             */
"PS30",                                                   /*254 PS30 RESERVED             */
"PS31"                                                    /*255 PS31 RESERVED             */
                                                                    
};

//OmniLingua - End German insertion here
//OmniLingua - Start Spanish insertion here

const STR *const AlarmSpn[] = {
                                                                                  


/**--------------------------------------------------**
 **        This group is the No Cycle Alarms         **
 **--------------------------------------------------**/

"NC0",                                                   /*0  NC0  RESERVED             */
"Cuenta atras lt sup",                                   /*1  NC1  Upper Limit Timeout  */
"NC2",                                                   /*2  NC2                       */
"Disparo previo a Predisparo",                           /*3  NC3  Trg before Pretrg    */
"Disparo fuera  de Tiempo",                              /*4  NC4  Trigger Timeout      */
"NC5",                                                   /*5  NC5                       */
"LI cancelado antes de Disparo",                         /*6  NC6  LLS abort before TRS */
"Ciclo Cancelado Ext.",                                  /*7  NC7  External Cycle Abort */
"Cancelado por falta de Pieza",                          /*8  NC8  Missing Part Abort   */
"D.Abs ant de Dsp",                                      /*9  NC9  Absolute before Trg  */
"Paso Amplitud prev a Disparo",                          /*10 NC10 Amp Step before Trg  */
"Paso Fuerza previo a Dispro",                           /*11 NC11 Frc Step before Trg  */
"Deteccion Tierra Cancelada",                            /*12 NC12 Ground Detect Abort  */
"Final tiempo disparo externo",                          /*13 NC13                      */
"Señal EV puerta perdida antes final ciclo",             /*14 NC14                      */
"Entrada EV puerta fuera de tiempo",                     /*15 NC15                      */
"NC16",                                                  /*16 NC16                      */
"NC17",                                                  /*17 NC17                      */
"NC18",                                                  /*18 NC18                      */
"NC19",                                                  /*19 NC19                      */
"NC20",                                                  /*20 NC20                      */
"NC21",                                                  /*21 NC21                      */
"NC22",                                                  /*22 NC22                      */
"NC23",                                                  /*23 NC23                      */
"NC24",                                                  /*24 NC24                      */
"NC25",                                                  /*25 NC25                      */
"NC26",                                                  /*26 NC26                      */
"NC27",                                                  /*27 NC27                      */
"NC28",                                                  /*28 NC28 RESERVED             */
"NC29",                                                  /*29 NC29 RESERVED             */
"NC30",                                                  /*30 NC30 RESERVED             */
"NC31",                                                  /*31 NC31 RESERVED             */






/**--------------------------------------------------**
 **        This group is the Overload Alarms         **
 **--------------------------------------------------**/

"OL0",                                                   /*32 OL0  RESERVED             */
"Test Sobrecarga",                                       /*33 OL1  Test Overload        */
"Sobrecarga Predisparo",                                 /*34 OL2  Pretrigger Overload  */
"Sobrecarga Busc",                                       /*35 OL3  Seek Overload        */
"Sobrecarga sum energ",                                  /*36 OL4  Power Supply O/L     */
"Tension continua excedida",                             /*37 OL5  Cont Pwr Limit       */
"Sobrecarga Disparo Post US",                            /*38 OL6  Afterburst Overload  */
"Sobrecarga durante busqueda  Frecuencia",               /*39 OL7  Pre-Weld Seek O/L    */
"Sobrecraga busc post Soldadura",                        /*40 OL8  Post Weld Seek O/L   */
"OL9",                                                   /*41 OL9                       */
"Sobrecarga frenado por energía",                        /*42 OL10                      */
"OL11",                                                  /*43 OL11                      */
"OL12",                                                  /*44 OL12                      */
"OL13",                                                  /*45 OL13                      */
"OL14",                                                  /*46 OL14                      */
"OL15",                                                  /*47 OL15                      */
"OL16",                                                  /*48 OL16                      */
"OL17",                                                  /*49 OL17                      */
"OL18",                                                  /*50 OL18                      */
"OL19",                                                  /*51 OL19                      */
"OL20",                                                  /*52 OL20                      */
"OL21",                                                  /*53 OL21                      */
"OL22",                                                  /*54 OL22                      */
"OL23",                                                  /*55 OL23                      */
"OL24",                                                  /*56 OL24                      */
"OL25",                                                  /*57 OL25                      */
"OL26",                                                  /*58 OL26                      */
"OL27",                                                  /*59 OL27                      */
"OL28",                                                  /*60 OL28 RESERVED             */
"OL29",                                                  /*61 OL29 RESERVED             */
"OL30",                                                  /*62 OL30 RESERVED             */
"OL31",                                                  /*63 OL31 RESERVED             */


                                                             
                                                             
                                                             
/**---------------------------------------------------------*
 **    The next new group is Equipment Failure Alarms       *
 **---------------------------------------------------------*/

"EQ0",                                                   /*64 EQ0  RESERVED             */
"Fallo codific",                                         /*65 EQ1  Encoder Fail         */
"Fallo interr lim sup",                                  /*66 EQ2  Upper Limit Switch   */
"Fallo interr lim sup",                                  /*67 EQ3  Upper Limit Switch   */
"Fallo Conmut Puerta/Disparo",                           /*68 EQ4  Door Sw Fail         */
"Fallo cel. carga",                                      /*69 EQ5  Loadcell Fail        */
"Fallo impul. solenoide",                                /*70 EQ6  Solenoid Drive Fail  */
"Temperatura Excesiva",                                  /*71 EQ7  Thermal Overload     */
"Fallo en los datos preajuste o en la bateria de la RAM",/*72 EQ8  Preset Data/BBR      */
"Retorno Sonot Fuera Tiem",                              /*73 EQ9  Horn Return Timeout  */
"Fallo actuador NovRam",                                 /*74 EQ10 Actuator NovRam      */
"Fallo sumin energ NovRam",                              /*75 EQ11 P/S NovRam           */
"Tiempo Escal Conmut Inic Perdido",                      /*76 EQ12 Start Sw Time        */
"Fallo Conmut Multifuncion",                             /*77 EQ13 MPS Switch Failed    */
"Error actuador AEF/AOP No se puede usar con este contr de niv",   /*78 EQ14 Wrong Actuator       */
"Sumin. energ. ultrason ausente o con fallo",            /*79 EQ15 Ultrasonics P/S      */
"Memoria Imprsra Llena",                                 /*80 EQ16 Printer Buffer Full  */
"Fallo Conmut Inicio Cerrado",                           /*81 EQ17 Start Switch Closed  */
"Predisparo fuera de Tiempo",                            /*82 EQ18 Pretrigger Timeout   */
"",                                                      /*83 EQ19                      */
"Recalibrar Actuador",                                   /*84 EQ20 Recalibrate Actuator */
"Fallo funcion liberacion actuador",                     /*85 EQ21 Act Clear Function   */
"Fallo bucle R/F",                                       /*86 EQ22 Stack                */
"Senal de inicio Perdida",                               /*87 EQ23 Start Switches Lost  */
"Tipo actuad ha cambiado desde el ult ciclo de sold ",   /*88 EQ24 Actuator Type        */
"Ajuste incorrecto Presion Sistema",                     /*89 EQ25 Sys. Pres. Incorrect */
"EQ26",                                                  /*90 EQ26                      */
"EQ27",                                                  /*91 EQ27                      */
"EQ28",                                                  /*92 EQ28 RESERVED             */
"EQ29",                                                  /*93 EQ29 RESERVED             */
"EQ30",                                                  /*94 EQ30 RESERVED             */
"EQ31",                                                  /*95 EQ31 RESERVED             */






                           
/**---------------------------------------------------**
 **    The next new group is Cycle Modified Alarms    **
 **---------------------------------------------------**/

"CM0",                                                   /*96  CM0  RESERVED             */
"Disparo perdido durante Mantenimiento",                 /*97  CM1  Trigger Lost in Hold */
"Deteccion Tierra Cancelada",                            /*98  CM2  Ground Detect Abort  */
"Tiempo Max Excedido",                                   /*99  CM3  Max Timeout          */
"Valor tiem para paso amplitud no alcanz",               /*100 CM4  No Amplitude Step    */
"Valor Tiempo para Paso Fuerza no alcanzdo",             /*101 CM5  No Force Step        */
"Valor Energia para Paso Amplitud no alcanzado",         /*102 CM6  No Amplitude Step    */
"Valor Energia para Paso Fuerza no alcanzado",           /*103 CM7  No Force Step        */
"Distancia Colapso para Paso Amplitud no alcanzada",     /*104 CM8  No Amplitude Step    */
"Distancia Absoluta para Paso Amplitud no alcanzada",    /*105 CM9  No Amplitude Step    */
"Nivel Potencia para Paso Fueza no alcanzado",           /*106 CM10 No Force Step        */
"Nivel Potencia para Paso Amplitud no alcanzdo",         /*107 CM11 No Amplitude Step    */
"No se recibio senal externa para Paso Amplitud",        /*108 CM12 No Amplitude Step    */
"No se recibio senal externa para Paso Fuerza",          /*109 CM13 No Force Step        */
"Disparo perdido durante Soldadura",                     /*110 CM14 Trg Lost during Weld */
"Ciclo Cancelado Ext.",                                  /*111 CM15 External Cycle Abort */
"No se alcanzo la Amplitud B - Por Soldadura corta",     /*112 CM16 Amp B Not Reached    */
"Puente en J55 en generador en posición incorrecta",     /*113 CM17                      */
"Amplitud A no alcanz porque sold demasiado breve",      /*114 CM18 Amp B Not Reached    */
"No se alcanzo la Amplitud B - Por Soldadura corta",     /*115 CM19 Amp B Not Reached    */
"Amplitud excedida - Por Soldadudra corta",              /*116 CM20 Amp Exceeded         */
"Energia No alcanzada",                                  /*117 CM21 Energy Not Reached   */
"La Fuerza Disparo mayor que la Fuerza Final",           /*118 CM22 Trigger > End Force  */
"Distancia Colapso para Paso Fuerza no alcanzada",       /*119 CM23 No Force Step        */
"CM24",                                                  /*120 CM24                      */
"CM25",                                                  /*121 CM25                      */
"CM26",                                                  /*122 CM26                      */
"CM27",                                                  /*123 CM27                      */
"CM28",                                                  /*124 CM28                      */
"CM29",                                                  /*125 CM29 RESERVED             */
"CM30",                                                  /*126 CM30 RESERVED             */
"CM31",                                                  /*127 CM31 RESERVED             */
                                                                   



/**----------------------------------------------**
 **  The next new group is Calibrate Alarms      **
 **----------------------------------------------**/

"CA0",                                                   /*128 CA0  RESERVED             */
"CA1 ",                                                  /*129 CA1                       */
"CA2 ",                                                  /*130 CA2                       */
"CA3 ",                                                  /*131 CA3                       */
"CA4 ",                                                  /*132 CA4                       */
"CA5 ",                                                  /*133 CA5                       */
"CA6 ",                                                  /*134 CA6                       */
"CA7 ",                                                  /*135 CA7                       */
"CA8 ",                                                  /*136 CA8                       */
"CA9 ",                                                  /*137 CA9                       */
"CA10",                                                  /*138 CA10                      */
"CA11",                                                  /*139 CA11                      */
"CA12",                                                  /*140 CA12                      */
"CA13",                                                  /*141 CA13                      */
"CA14",                                                  /*142 CA14                      */
"CA15",                                                  /*143 CA15                      */
"CA16",                                                  /*144 CA16                      */
"CA17",                                                  /*145 CA17                      */
"CA18",                                                  /*146 CA18                      */
"CA19",                                                  /*147 CA19                      */
"CA20",                                                  /*148 CA20                      */
"CA21",                                                  /*149 CA21                      */
"CA22",                                                  /*150 CA22                      */
"CA23",                                                  /*151 CA23                      */
"CA24",                                                  /*152 CA24                      */
"CA25",                                                  /*153 CA25                      */
"CA26",                                                  /*154 CA26                      */
"CA27",                                                  /*155 CA27                      */
"CA28",                                                  /*156 CA28 RESERVED             */
"CA29",                                                  /*157 CA29 RESERVED             */
"CA30",                                                  /*158 CA30 RESERVED             */
"CA31",                                                  /*159 CA31 RESERVED             */
                                                                   


/**--------------------------------------------**
 **       The next new group is Warnings       **
 **--------------------------------------------**/

"WA0",                                                   /*160 WA0  RESERVED             */
"Distancia Liber Actuador no alcanzada",                 /*161 WA1                       */
"Maxima Energia de Compensacion alcanzada",              /*162 WA2  Max Energy Reached   */
"",                                                      /*163 WA3  Printer Buffer 80%   */
"WA4",                                                   /*164 WA4  Cont Pwr Limit       */
"Corte por Pico de Potencia",                            /*165 WA5  Peak Power Cutoff    */
"Corte Absoluto Distancia",                              /*166 WA6  Absolute Cutoff      */
"Tiempo Soldadura excedido por compensacion de Energia", /*167 WA7  Time Extended        */
"WA8",                                                   /*168 WA8                       */
"Corte por Colapso",                                     /*169 WA9  Collapse Cutoff      */
"WA10",                                                  /*170 WA10                      */
"Ultrasonidos deshabilitados por entrada de usuario",    /*171 WA11                      */
"WA12",                                                  /*172 WA12                      */
"WA13",                                                  /*173 WA13                      */
"WA14",                                                  /*174 WA14                      */
"WA15",                                                  /*175 WA15                      */
"WA16",                                                  /*176 WA16                      */
"WA17",                                                  /*177 WA17                      */
"WA18",                                                  /*178 WA18                      */
"WA19",                                                  /*179 WA19                      */
"WA20",                                                  /*180 WA20                      */
"WA21",                                                  /*181 WA21                      */
"WA22",                                                  /*182 WA22                      */
"WA23",                                                  /*183 WA23                      */
"WA24",                                                  /*184 WA24                      */
"WA25",                                                  /*185 WA25                      */
"WA26",                                                  /*186 WA26                      */
"WA27",                                                  /*187 WA27                      */
"WA28",                                                  /*188 WA28 RESERVED             */
"WA29",                                                  /*189 WA29 RESERVED             */
"WA30",                                                  /*190 WA30 RESERVED             */
"WA31",                                                  /*191 WA31 RESERVED             */



/**------------------------------------------------------------**
 **        The next new group is Process Reject Alarms         **
 **------------------------------------------------------------**/

"PR0",                                                   /*192 PR0  RESERVED             */
"Lte Rechazo- Energia",                                  /*193 PR1  -R Energy Limit      */
"Lte Rechazo+ Energia",                                  /*194 PR2  +R Energy Limit      */
"Lte Rechazo- Pico Potencia",                            /*195 PR3  -R Pk Power Limit    */
"Lte Rechazo+ Pico Potencia",                            /*196 PR4  +R Pk Power Limit    */
"Lte Rechazo- Distancia Colapso",                        /*197 PR5  -R Col Dist Limit    */
"Lte Rechazo+ Distancia Colapso",                        /*198 PR6  +R Col Dist Limit    */
"Lte Rechazo- Distancia Absoluta",                       /*199 PR7  -R Abs Dist Limit    */
"Lte Rechazo+ Distancia Absoluta",                       /*200 PR8  +R Abs Dist Limit    */
"Lte Rechazo- Distancia Disparo",                        /*201 PR9  -R Trig Dist Limit   */
"Lte Rechazo+ Distancia Disparo",                        /*202 PR10 +R Trig Dist Limit   */
"-Rechz lim fuerza sold",                                /*203 PR11 -R Max Force Limit   */
"+Rechz lim fuerza sold",                                /*204 PR12 +R Max Force Limit   */
"Lte Rechzo- Tiempo",                                    /*205 PR13 -R Time Limit        */
"Lte Rechzo+ Tiempo",                                    /*206 PR14 +R Time Limit        */
"PR15",                                                  /*207 PR15                      */
"PR16",                                                  /*208 PR16                      */
"PR17",                                                  /*209 PR17                      */
"Lim inferior no alcanz",                                /*210 PR18 LL Not Reached       */
"PR19",                                                  /*211 PR19                      */
"PR20",                                                  /*212 PR20                      */
"PR21",                                                  /*213 PR21                      */
"PR22",                                                  /*214 PR22                      */
"PR23",                                                  /*215 PR23                      */
"PR24",                                                  /*216 PR24                      */
"PR25",                                                  /*217 PR25                      */
"PR26",                                                  /*218 PR26                      */
"PR27",                                                  /*219 PR27                      */
"PR28",                                                  /*220 PR28 RESERVED             */
"PR29",                                                  /*221 PR29 RESERVED             */
"PR30",                                                  /*222 PR30 RESERVED             */
"PR31",                                                  /*223 PR31 RESERVED             */
                                                                    



/**-----------------------------------------------------------**
 **        The next new group is Process Suspect Alarms       **
 **-----------------------------------------------------------**/

"PS0",                                                   /*224 PS0  RESERVED             */
"Lte Sospech- Energia",                                  /*225 PS1  -S Energy Limit      */
"Lte Sospech+ Energia",                                  /*226 PS2  +S Energy Limit      */
"Lte Sospech- Pico Potencia",                            /*227 PS3  -S Pk Power Limit    */
"Lte Sospech+ Pico Potencia",                            /*228 PS4  +S Pk Power Limit    */
"Lte Sospech- Distancia Colapso",                        /*229 PS5  -S Col Dist Limit    */
"Lte Sospech+ Distancia Colapso",                        /*230 PS6  +S Col Dist Limit    */
"Lte Sospech- Distancia Absoluta",                       /*231 PS7  -S Abs Dist Limit    */
"Lte Sospech+ Distancia Absoluta",                       /*232 PS8  +S Abs Dist Limit    */
"Lte Sospech- Distancia Disparo Rebasados",              /*233 PS9  -S Trig Dist Limit   */
"Lte Sospech+ Distancia Disparo Rebasados",              /*234 PS10 +S Trig Dist Limit   */
"-Sospch lim fuerza sold",                               /*235 PS11 -S Max Force Limit   */
"+Sospch lim fuerza sold",                               /*236 PS12 +S Max Force Limit   */
"Lte Sospech- Tiempo",                                   /*237 PS13 -S Time Limit        */
"Lte Sospech+ Tiempo",                                   /*238 PS14 +S Time Limit        */
"PS15",                                                  /*239 PS15                      */
"PS16",                                                  /*240 PS16                      */
"PS17",                                                  /*241 PS17                      */
"PS18",                                                  /*242 PS18                      */
"PS19",                                                  /*243 PS19                      */
"PS20",                                                  /*244 PS20                      */
"PS21",                                                  /*245 PS21                      */
"PS22",                                                  /*246 PS22                      */
"PS23",                                                  /*247 PS23                      */
"PS24",                                                  /*248 PS24                      */
"PS25",                                                  /*249 PS25                      */
"PS26",                                                  /*250 PS26                      */
"PS27",                                                  /*251 PS27                      */
"PS28",                                                  /*252 PS28 RESERVED             */
"PS29",                                                  /*253 PS29 RESERVED             */
"PS30",                                                  /*254 PS30 RESERVED             */
"PS31"                                                   /*255 PS31 RESERVED             */
                                                                    
};

//OmniLingua - End Spanish insertion here
//OmniLingua - Start Italian insertion here

const STR *const AlarmItl[] = {
                                                                                  

/**--------------------------------------------------**
 **        This group is the No Cycle Alarms         **
 **--------------------------------------------------**/

"NC0",                                                   /*0  NC0  RESERVED             */
"Timeout limite sup.",                                   /*1  NC1  Upper Limit Timeout  */
"NC2",                                                   /*2  NC2                       */
"Trigr prima di pretrigger",                             /*3  NC3  Trg before Pretrg    */
"Timeout trigger",                                       /*4  NC4  Trigger Timeout      */
"NC5",                                                   /*5  NC5                       */
"Int lim inf prima int Trg",                             /*6  NC6  LLS abort before TRS */
"Annulla ciclo esterno",                                 /*7  NC7  External Cycle Abort */
"Annulla parte mancante",                                /*8  NC8  Missing Part Abort   */
"Dist ass prima Trg",                                    /*9  NC9  Absolute before Trg  */
"Step amp prima di trig",                                /*10 NC10 Amp Step before Trg  */
"Step forza prima di trig",                              /*11 NC11 Frc Step before Trg  */
"Annulla Ground Detect",                                 /*12 NC12 Ground Detect Abort  */
"Ritardo Trigger esterno terminato",                     /*13 NC13                      */
"SV segnale di blocco perso prima di completare il ciclo",/*14 NC14                      */
"SV blocco ingresso terminato",                          /*15 NC15                      */
"NC16",                                                  /*16 NC16                      */
"NC17",                                                  /*17 NC17                      */
"NC18",                                                  /*18 NC18                      */
"NC19",                                                  /*19 NC19                      */
"NC20",                                                  /*20 NC20                      */
"NC21",                                                  /*21 NC21                      */
"NC22",                                                  /*22 NC22                      */
"NC23",                                                  /*23 NC23                      */
"NC24",                                                  /*24 NC24                      */
"NC25",                                                  /*25 NC25                      */
"NC26",                                                  /*26 NC26                      */
"NC27",                                                  /*27 NC27                      */
"NC28",                                                  /*28 NC28 RESERVED             */
"NC29",                                                  /*29 NC29 RESERVED             */
"NC30",                                                  /*30 NC30 RESERVED             */
"NC31",                                                  /*31 NC31 RESERVED             */






/**--------------------------------------------------**
 **        This group is the Overload Alarms         **
 **--------------------------------------------------**/

"OL0",                                                   /*32 OL0  RESERVED             */
"Sovrac. test",                                          /*33 OL1  Test Overload        */
"Sovraccarico pretrigger",                               /*34 OL2  Pretrigger Overload  */
"Sovrac. Seek",                                          /*35 OL3  Seek Overload        */
"Sovraccarico aliment.",                                 /*36 OL4  Power Supply O/L     */
"Superam potenza continua",                              /*37 OL5  Cont Pwr Limit       */
"Sovrac. afterburst",                                    /*38 OL6  Afterburst Overload  */
"Overload Seek pre-sald",                                /*39 OL7  Pre-Weld Seek O/L    */
"Overload Seek post-sald",                               /*40 OL8  Post Weld Seek O/L   */
"OL9",                                                   /*41 OL9                       */
"Sovraccarico energia frenante",                         /*42 OL10                      */
"OL11",                                                  /*43 OL11                      */
"OL12",                                                  /*44 OL12                      */
"OL13",                                                  /*45 OL13                      */
"OL14",                                                  /*46 OL14                      */
"OL15",                                                  /*47 OL15                      */
"OL16",                                                  /*48 OL16                      */
"OL17",                                                  /*49 OL17                      */
"OL18",                                                  /*50 OL18                      */
"OL19",                                                  /*51 OL19                      */
"OL20",                                                  /*52 OL20                      */
"OL21",                                                  /*53 OL21                      */
"OL22",                                                  /*54 OL22                      */
"OL23",                                                  /*55 OL23                      */
"OL24",                                                  /*56 OL24                      */
"OL25",                                                  /*57 OL25                      */
"OL26",                                                  /*58 OL26                      */
"OL27",                                                  /*59 OL27                      */
"OL28",                                                  /*60 OL28 RESERVED             */
"OL29",                                                  /*61 OL29 RESERVED             */
"OL30",                                                  /*62 OL30 RESERVED             */
"OL31",                                                  /*63 OL31 RESERVED             */


                                                             
                                                             
                                                             
/**---------------------------------------------------------*
 **    The next new group is Equipment Failure Alarms       *
 **---------------------------------------------------------*/

"EQ0",                                                   /*64 EQ0  RESERVED             */
"Encoder Failure",                                       /*65 EQ1  Encoder Fail         */
"Guasto int. Limite sup. ",                              /*66 EQ2  Upper Limit Switch   */
"Guasto int. Limite sup. ",                             /*67 EQ3  Upper Limit Switch   */
"Inter porta/trigger guasto",                            /*68 EQ4  Door Sw Fail         */
"Guasto caric. cella",                                   /*69 EQ5  Loadcell Fail        */
"Guasto guida solenoide",                                /*70 EQ6  Solenoid Drive Fail  */
"Sovracc. termico",                                      /*71 EQ7  Thermal Overload     */
"Anomalia dati di impostaz o batteria RAM tampone",      /*72 EQ8  Preset Data/BBR      */
"Timeout ritorno sonotrodo",                             /*73 EQ9  Horn Return Timeout  */
"Guasto NovRam att.",                                    /*74 EQ10 Actuator NovRam      */
"Guasto alim. NovRam",                                   /*75 EQ11 P/S NovRam           */
"Tempo di ritardo interr gen manc",                      /*76 EQ12 Start Sw Time        */
"Guasto interrutore multifun",                           /*77 EQ13 MPS Switch Failed    */
"Att. AEF/AOP Errato, imposs. Usare con questo controllo livello",  /*78 EQ14 Wrong Actuator       */
"Alim. Ultrasonic. Assente o guasto",                    /*79 EQ15 Ultrasonics P/S      */
"Buffer stampante pieno",                                /*80 EQ16 Printer Buffer Full  */
"Anom chiusura interrutt gen",                           /*81 EQ17 Start Switch Closed  */
"Timeout pretrigger",                                    /*82 EQ18 Pretrigger Timeout   */
"",                                                      /*83 EQ19                      */
"Ricalibra attuatore",                                   /*84 EQ20 Recalibrate Actuator */
"Anomalia funzione apertura att",                        /*85 EQ21 Act Clear Function   */
"Guasto di ciclo R/F",                                   /*86 EQ22 Stack                */
"Int. avvio perduti",                                    /*87 EQ23 Start Switches Lost  */
"Tipo att. modificato da ultimo ciclo sald.",            /*88 EQ24 Actuator Type        */
"Impostaz pressione di sistema err",                     /*89 EQ25 Sys. Pres. Incorrect */
"EQ26",                                                  /*90 EQ26                      */
"EQ27",                                                  /*91 EQ27                      */
"EQ28",                                                  /*92 EQ28 RESERVED             */
"EQ29",                                                  /*93 EQ29 RESERVED             */
"EQ30",                                                  /*94 EQ30 RESERVED             */
"EQ31",                                                  /*95 EQ31 RESERVED             */





                           
/**---------------------------------------------------**
 **    The next new group is Cycle Modified Alarms    **
 **---------------------------------------------------**/

"CM0",                                                  /*96  CM0  RESERVED             */
"Trig perso durante raf",                               /*97  CM1  Trigger Lost in Hold */
"Annulla Ground Detect",                                /*98  CM2  Ground Detect Abort  */
"Timeout max",                                          /*99  CM3  Max Timeout          */
"Valore temp. per pass. amp. non raggiunto",            /*100 CM4  No Amplitude Step    */
"Val di tempo per step forza non ragg",                 /*101 CM5  No Force Step        */
"Valore energia per step di ampiezza non ragg",         /*102 CM6  No Amplitude Step    */
"Valore energia per step di forza non ragg",            /*103 CM7  No Force Step        */
"Distanza contrazione per step di ampiezza non ragg",   /*104 CM8  No Amplitude Step    */
"Distanza assoluta per step di ampiezza non ragg",      /*105 CM9  No Amplitude Step    */
"Liv di pot per step di forza non ragg",                /*106 CM10 No Force Step        */
"Liv di pot per step di ampiezza non ragg",             /*107 CM11 No Amplitude Step    */
"Non ricevuto segnale esterno su step di ampiezza",     /*108 CM12 No Amplitude Step    */
"Non ricevuto segnale esterno su step di forza",        /*109 CM13 No Force Step        */
"Trig perso durante sald",                              /*110 CM14 Trg Lost during Weld */
"Annulla ciclo esterno",                                /*111 CM15 External Cycle Abort */
"L'amp B non e stata ragg perche la sald era troppo corta", /*112 CM16 Amp B Not Reached    */
"Jumper J55 del generatore posizionato in modo errato", /*113 CM17                      */
"Amp. non ragg. sald. troppo breve",                    /*114 CM18 Amp B Not Reached    */
"L'amp B non e stata ragg perche la sald era troppo corta", /*115 CM19 Amp B Not Reached    */
"L'amp e stata sup perche sald era troppo corta",       /*116 CM20 Amp Exceeded         */
"Energia non raggiunta",                                /*117 CM21 Energy Not Reached   */
"Forza trigger maggiore della forza finale",            /*118 CM22 Trigger > End Force  */
"Distanza collasso per step di forza non ragg",         /*119 CM23 No Force Step        */
"CM24",                                                 /*120 CM24                      */
"CM25",                                                 /*121 CM25                      */
"CM26",                                                 /*122 CM26                      */
"CM27",                                                 /*123 CM27                      */
"CM28",                                                 /*124 CM28                      */
"CM29",                                                 /*125 CM29 RESERVED             */
"CM30",                                                 /*126 CM30 RESERVED             */
"CM31",                                                 /*127 CM31 RESERVED             */
                                                                   



/**----------------------------------------------**
 **  The next new group is Calibrate Alarms      **
 **----------------------------------------------**/

"CA0",                                                  /*128 CA0  RESERVED             */
"CA1 ",                                                 /*129 CA1                       */
"CA2 ",                                                 /*130 CA2                       */
"CA3 ",                                                 /*131 CA3                       */
"CA4 ",                                                 /*132 CA4                       */
"CA5 ",                                                 /*133 CA5                       */
"CA6 ",                                                 /*134 CA6                       */
"CA7 ",                                                 /*135 CA7                       */
"CA8 ",                                                 /*136 CA8                       */
"CA9 ",                                                 /*137 CA9                       */
"CA10",                                                 /*138 CA10                      */
"CA11",                                                 /*139 CA11                      */
"CA12",                                                 /*140 CA12                      */
"CA13",                                                 /*141 CA13                      */
"CA14",                                                 /*142 CA14                      */
"CA15",                                                 /*143 CA15                      */
"CA16",                                                 /*144 CA16                      */
"CA17",                                                 /*145 CA17                      */
"CA18",                                                 /*146 CA18                      */
"CA19",                                                 /*147 CA19                      */
"CA20",                                                 /*148 CA20                      */
"CA21",                                                 /*149 CA21                      */
"CA22",                                                 /*150 CA22                      */
"CA23",                                                 /*151 CA23                      */
"CA24",                                                 /*152 CA24                      */
"CA25",                                                 /*153 CA25                      */
"CA26",                                                 /*154 CA26                      */
"CA27",                                                 /*155 CA27                      */
"CA28",                                                 /*156 CA28 RESERVED             */
"CA29",                                                 /*157 CA29 RESERVED             */
"CA30",                                                 /*158 CA30 RESERVED             */
"CA31",                                                 /*159 CA31 RESERVED             */
                                                                   


/**--------------------------------------------**
 **       The next new group is Warnings       **
 **--------------------------------------------**/

"WA0",                                                  /*160 WA0  RESERVED             */
"Posiz di apertura att non raggiunta",                  /*161 WA1                       */
"Compensaz energia: energia max raggiunta",             /*162 WA2  Max Energy Reached   */
"",                                                     /*163 WA3  Printer Buffer 80%   */
"WA4",                                                  /*164 WA4  Cont Pwr Limit       */
"Interr pic pot",                                       /*165 WA5  Peak Power Cutoff    */
"Arresto distanza ass",                                 /*166 WA6  Absolute Cutoff      */
"Tempo di sald prolung per compensaz di energia",       /*167 WA7  Time Extended        */
"WA8",                                                  /*168 WA8                       */
"Interruzione collasso",                                /*169 WA9  Collapse Cutoff      */
"WA10",                                                 /*170 WA10                      */
"Disattivazione u/s da parte dell'operatore",           /*171 WA11                      */
"WA12",                                                 /*172 WA12                      */
"WA13",                                                 /*173 WA13                      */
"WA14",                                                 /*174 WA14                      */
"WA15",                                                 /*175 WA15                      */
"WA16",                                                 /*176 WA16                      */
"WA17",                                                 /*177 WA17                      */
"WA18",                                                 /*178 WA18                      */
"WA19",                                                 /*179 WA19                      */
"WA20",                                                 /*180 WA20                      */
"WA21",                                                 /*181 WA21                      */
"WA22",                                                 /*182 WA22                      */
"WA23",                                                 /*183 WA23                      */
"WA24",                                                 /*184 WA24                      */
"WA25",                                                 /*185 WA25                      */
"WA26",                                                 /*186 WA26                      */
"WA27",                                                 /*187 WA27                      */
"WA28",                                                 /*188 WA28 RESERVED             */
"WA29",                                                 /*189 WA29 RESERVED             */
"WA30",                                                 /*190 WA30 RESERVED             */
"WA31",                                                 /*191 WA31 RESERVED             */



/**------------------------------------------------------------**
 **        The next new group is Process Reject Alarms         **
 **------------------------------------------------------------**/

"PR0",                                                  /*192 PR0  RESERVED             */
"Lim - energia scarto",                                 /*193 PR1  -R Energy Limit      */
"Lim + energia scarto",                                 /*194 PR2  +R Energy Limit      */
"Lim - di pic di pot scarto",                           /*195 PR3  -R Pk Power Limit    */
"Lim + di pic di pot scarto",                           /*196 PR4  +R Pk Power Limit    */
"Lim - distanza collasso scarto",                       /*197 PR5  -R Col Dist Limit    */
"Lim + distanza collasso scarto",                       /*198 PR6  +R Col Dist Limit    */
"Lim - distanza assoluta scarto",                       /*199 PR7  -R Abs Dist Limit    */
"Lim + distanza assoluta scarto",                       /*200 PR8  +R Abs Dist Limit    */
"Lim - distanza trigger scarto",                        /*201 PR9  -R Trig Dist Limit   */
"Lim + distanza trigger scarto",                        /*202 PR10 +R Trig Dist Limit   */
"-Scarto sald. limite forza",                           /*203 PR11 -R Max Force Limit   */
"+Scarto sald. limite forza",                           /*204 PR12 +R Max Force Limit   */
"Lim - tempo scarto",                                   /*205 PR13 -R Time Limit        */
"Lim + tempo scarto",                                   /*206 PR14 +R Time Limit        */
"PR15",                                                 /*207 PR15                      */
"PR16",                                                 /*208 PR16                      */
"PR17",                                                 /*209 PR17                      */
"Li mite inf. Non raggiunto",                           /*210 PR18 LL Not Reached       */
"PR19",                                                 /*211 PR19                      */
"PR20",                                                 /*212 PR20                      */
"PR21",                                                 /*213 PR21                      */
"PR22",                                                 /*214 PR22                      */
"PR23",                                                 /*215 PR23                      */
"PR24",                                                 /*216 PR24                      */
"PR25",                                                 /*217 PR25                      */
"PR26",                                                 /*218 PR26                      */
"PR27",                                                 /*219 PR27                      */
"PR28",                                                 /*220 PR28 RESERVED             */
"PR29",                                                 /*221 PR29 RESERVED             */
"PR30",                                                 /*222 PR30 RESERVED             */
"PR31",                                                 /*223 PR31 RESERVED             */
                                                                    



/**-----------------------------------------------------------**
 **        The next new group is Process Suspect Alarms       **
 **-----------------------------------------------------------**/

"PS0",                                                  /*224 PS0  RESERVED             */
"Limite - energia sosp",                                /*225 PS1  -S Energy Limit      */
"Limite + energia sosp",                                /*226 PS2  +S Energy Limit      */
"Lim - picco di pot sosp",                              /*227 PS3  -S Pk Power Limit    */
"Lim + picco di pot sosp",                              /*228 PS4  +S Pk Power Limit    */
"Lim - distanza collasso sospetto",                     /*229 PS5  -S Col Dist Limit    */
"Lim + distanza collasso sospetto",                     /*230 PS6  +S Col Dist Limit    */
"Lim - distanza assoluta sospetto",                     /*231 PS7  -S Abs Dist Limit    */
"Lim + distanza assoluta sospetto",                     /*232 PS8  +S Abs Dist Limit    */
"Limite - distanza trigger sospetto",                   /*233 PS9  -S Trig Dist Limit   */
"limite + distanza trigger sospetto",                   /*234 PS10 +S Trig Dist Limit   */
"-Sosp. limit e forza sald.",                           /*235 PS11 -S Max Force Limit   */
"+Sosp. limit e forza sald.",                           /*236 PS12 +S Max Force Limit   */
"Limite - tempo sosp",                                  /*237 PS13 -S Time Limit        */
"Limite + tempo sosp",                                  /*238 PS14 +S Time Limit        */
"PS15",                                                 /*239 PS15                      */
"PS16",                                                 /*240 PS16                      */
"PS17",                                                 /*241 PS17                      */
"PS18",                                                 /*242 PS18                      */
"PS19",                                                 /*243 PS19                      */
"PS20",                                                 /*244 PS20                      */
"PS21",                                                 /*245 PS21                      */
"PS22",                                                 /*246 PS22                      */
"PS23",                                                 /*247 PS23                      */
"PS24",                                                 /*248 PS24                      */
"PS25",                                                 /*249 PS25                      */
"PS26",                                                 /*250 PS26                      */
"PS27",                                                 /*251 PS27                      */
"PS28",                                                 /*252 PS28 RESERVED             */
"PS29",                                                 /*253 PS29 RESERVED             */
"PS30",                                                 /*254 PS30 RESERVED             */
"PS31"                                                  /*255 PS31 RESERVED             */
                                                                    
};

//OmniLingua - End Italian insertion here
//OmniLingua - Start French insertion here

const STR *const AlarmFr[] = {
                                                                                  

/**--------------------------------------------------**
 **        This group is the No Cycle Alarms         **
 **--------------------------------------------------**/

"NC0",                                                   /*0  NC0  RESERVED             */
"Del. Max ULS depasse",                                  /*1  NC1  Upper Limit Timeout  */
"NC2",                                                   /*2  NC2                       */
"Trigg. avant Pretrigg.",                                /*3  NC3  Trg before Pretrg    */
"Trigg Non Enclenc",                                     /*4  NC4  Trigger Timeout      */
"NC5",                                                   /*5  NC5                       */
"LLS atteint avnt TRS",                                  /*6  NC6  LLS abort before TRS */
"Interrupt Cycle Ext.",                                  /*7  NC7  External Cycle Abort */
"Interrupt Piece Mqte",                                  /*8  NC8  Missing Part Abort   */
"Abs avant Trigg",                                       /*9  NC9  Absolute before Trg  */
"Saut  Amp. avant Trigg",                                /*10 NC10 Amp Step before Trg  */
"Saut Force avant Trigg.",                               /*11 NC11 Frc Step before Trg  */
"Arret Detec. Masse",                                    /*12 NC12 Ground Detect Abort  */
"Delai de Trigger exterieur depasse",                    /*13 NC13                      */
"Signal Verrou EV perdu durant le cycle",                /*14 NC14                      */
"Delai Signal Verrou EV dépasse",                        /*15 NC15                      */
"NC16",                                                  /*16 NC16                      */
"NC17",                                                  /*17 NC17                      */
"NC18",                                                  /*18 NC18                      */
"NC19",                                                  /*19 NC19                      */
"NC20",                                                  /*20 NC20                      */
"NC21",                                                  /*21 NC21                      */
"NC22",                                                  /*22 NC22                      */
"NC23",                                                  /*23 NC23                      */
"NC24",                                                  /*24 NC24                      */
"NC25",                                                  /*25 NC25                      */
"NC26",                                                  /*26 NC26                      */
"NC27",                                                  /*27 NC27                      */
"NC28",                                                  /*28 NC28 RESERVED             */
"NC29",                                                  /*29 NC29 RESERVED             */
"NC30",                                                  /*30 NC30 RESERVED             */
"NC31",                                                  /*31 NC31 RESERVED             */






/**--------------------------------------------------**
 **        This group is the Overload Alarms         **
 **--------------------------------------------------**/

"OL0",                                                   /*32 OL0  RESERVED             */
"Surchrge Test",                                         /*33 OL1  Test Overload        */
"Surchrge Pretrigger",                                   /*34 OL2  Pretrigger Overload  */
"Surchrge Rech",                                         /*35 OL3  Seek Overload        */
"Surchge generateur",                                    /*36 OL4  Power Supply O/L     */
"Puiss. Cont. Depassee",                                 /*37 OL5  Cont Pwr Limit       */
"Surchrge Imp p-oper",                                   /*38 OL6  Afterburst Overload  */
"Srchge Rech. Pre-Soud.",                                /*39 OL7  Pre-Weld Seek O/L    */
"Srchge Rech. Post-Soud.",                               /*40 OL8  Post Weld Seek O/L   */
"OL9",                                                   /*41 OL9                       */
"Surcharge en Frein Energie",                            /*42 OL10                      */
"OL11",                                                  /*43 OL11                      */
"OL12",                                                  /*44 OL12                      */
"OL13",                                                  /*45 OL13                      */
"OL14",                                                  /*46 OL14                      */
"OL15",                                                  /*47 OL15                      */
"OL16",                                                  /*48 OL16                      */
"OL17",                                                  /*49 OL17                      */
"OL18",                                                  /*50 OL18                      */
"OL19",                                                  /*51 OL19                      */
"OL20",                                                  /*52 OL20                      */
"OL21",                                                  /*53 OL21                      */
"OL22",                                                  /*54 OL22                      */
"OL23",                                                  /*55 OL23                      */
"OL24",                                                  /*56 OL24                      */
"OL25",                                                  /*57 OL25                      */
"OL26",                                                  /*58 OL26                      */
"OL27",                                                  /*59 OL27                      */
"OL28",                                                  /*60 OL28 RESERVED             */
"OL29",                                                  /*61 OL29 RESERVED             */
"OL30",                                                  /*62 OL30 RESERVED             */
"OL31",                                                  /*63 OL31 RESERVED             */


                                                             
                                                             
                                                             
/**---------------------------------------------------------*
 **    The next new group is Equipment Failure Alarms       *
 **---------------------------------------------------------*/

"EQ0",                                                    /*64 EQ0  RESERVED             */
"Encodeur defect.",                                       /*65 EQ1  Encoder Fail         */
"Upper limit Switch Defect.",                             /*66 EQ2  Upper Limit Switch   */
"Upper limit Switch Defect.",                             /*67 EQ3  Upper Limit Switch   */
"Contac. Porte/Triggl. Defect.",                          /*68 EQ4  Door Sw Fail         */
"Jauge Contr. defect.",                                   /*69 EQ5  Loadcell Fail        */
"Circuit E.Vanne Defect.",                                /*70 EQ6  Solenoid Drive Fail  */
"Surchg Thermique",                                       /*71 EQ7  Thermal Overload     */
"Donnees Preset ou BBRAM Defect.",                        /*72 EQ8  Preset Data/BBR      */
"Delai max Retour Sono",                                  /*73 EQ9  Horn Return Timeout  */
"NovRam Actuator defect.",                                /*74 EQ10 Actuator NovRam      */
"NovRam Generateur defect.",                              /*75 EQ11 P/S NovRam           */
"Mauvaise Synchro Bout. Start",                           /*76 EQ12 Start Sw Time        */
"Inter. Multifonct. Defect.",                             /*77 EQ13 MPS Switch Failed    */
"Act. AEF/AOP non utilisable avec ce niveau de controle", /*78 EQ14 Wrong Actuator       */
"Generateur absent ou defectueux",                        /*79 EQ15 Ultrasonics P/S      */
"Mem Tpon Imp Pleine",                                    /*80 EQ16 Printer Buffer Full  */
"Bout. de Lanc. Ferme Defec.",                            /*81 EQ17 Start Switch Closed  */
"Pretrigg Non Enclenc",                                   /*82 EQ18 Pretrigger Timeout   */
"",                                                       /*83 EQ19                      */
"Recalibrer Actuator",                                    /*84 EQ20 Recalibrate Actuator */
"Fonct. Degag. Actuator Defect.",                         /*85 EQ21 Act Clear Function   */
"Boucle R/F Defect.",                                     /*86 EQ22 Stack                */
"Boutons Start Perdus",                                   /*87 EQ23 Start Switches Lost  */
"Type actuator modifie depuis dernier cycle soudure",     /*88 EQ24 Actuator Type        */
"Reglage Pression Syst. Incorrect",                       /*89 EQ25 Sys. Pres. Incorrect */
"EQ26",                                                   /*90 EQ26                      */
"EQ27",                                                   /*91 EQ27                      */
"EQ28",                                                   /*92 EQ28 RESERVED             */
"EQ29",                                                   /*93 EQ29 RESERVED             */
"EQ30",                                                   /*94 EQ30 RESERVED             */
"EQ31",                                                   /*95 EQ31 RESERVED             */





                           
/**---------------------------------------------------**
 **    The next new group is Cycle Modified Alarms    **
 **---------------------------------------------------**/

"CM0",                                                            /*96  CM0  RESERVED             */
"Trigg. perdu pdt maint.",                                        /*97  CM1  Trigger Lost in Hold */
"Arret Detec. Masse",                                             /*98  CM2  Ground Detect Abort  */
"Delai Max",                                                      /*99  CM3  Max Timeout          */
"Valeur Temps pour niv. Amplitude non atteinte",                  /*100 CM4  No Amplitude Step    */
"Valeur Temps de Saut Force non Atteinte",                        /*101 CM5  No Force Step        */
"Valeur Energ. de Saut d'Amplitude non Atteinte",                 /*102 CM6  No Amplitude Step    */
"Valeur Energ. de saut de Force non Atteinte",                    /*103 CM7  No Force Step        */
"Distance Relative de Saut Amplitude non Atteinte",               /*104 CM8  No Amplitude Step    */
"Distance Absolue de Saut Amplitude non Atteinte",                /*105 CM9  No Amplitude Step    */
"Niveau Puiss. de Saut Force non Atteint",                        /*106 CM10 No Force Step        */
"Niveau Puiss. de Saut Amplitude non Atteint",                    /*107 CM11 No Amplitude Step    */
"Signal Externe de Saut Amplitude Absent",                        /*108 CM12 No Amplitude Step    */
"Signal Externe de Saut Force Absent",                            /*109 CM13 No Force Step        */
"Trigg. perdu pdt soudage",                                       /*110 CM14 Trg Lost during Weld */
"Interrupt Cycle Ext.",                                           /*111 CM15 External Cycle Abort */
"Amplitude B non atteinte car le soudage etait trop court",       /*112 CM16 Amp B Not Reached    */
"Jumper J55 pas en position correcte",                            /*113 CM17                      */
"Amplitude A non atteinte car le soudage etait trop court",       /*114 CM18 Amp B Not Reached    */
"Amplitude B non atteinte car le soudage etait trop court",       /*115 CM19 Amp B Not Reached    */
"Amplit. depassee car le soudage etait trop court",               /*116 CM20 Amp Exceeded         */
"Energ. Non Attein.",                                             /*117 CM21 Energy Not Reached   */
"Force Trigg. Superieure a Force Finale",                         /*118 CM22 Trigger > End Force  */
"Distance Relative de Saut Force non Atteinte",                   /*119 CM23 No Force Step        */
"CM24",                                                           /*120 CM24                      */
"CM25",                                                           /*121 CM25                      */
"CM26",                                                           /*122 CM26                      */
"CM27",                                                           /*123 CM27                      */
"CM28",                                                           /*124 CM28                      */
"CM29",                                                           /*125 CM29 RESERVED             */
"CM30",                                                           /*126 CM30 RESERVED             */
"CM31",                                                           /*127 CM31 RESERVED             */
                                                                   



/**----------------------------------------------**
 **  The next new group is Calibrate Alarms      **
 **----------------------------------------------**/

"CA0",                                                  /*128 CA0  RESERVED             */
"CA1 ",                                                 /*129 CA1                       */
"CA2 ",                                                 /*130 CA2                       */
"CA3 ",                                                 /*131 CA3                       */
"CA4 ",                                                 /*132 CA4                       */
"CA5 ",                                                 /*133 CA5                       */
"CA6 ",                                                 /*134 CA6                       */
"CA7 ",                                                 /*135 CA7                       */
"CA8 ",                                                 /*136 CA8                       */
"CA9 ",                                                 /*137 CA9                       */
"CA10",                                                 /*138 CA10                      */
"CA11",                                                 /*139 CA11                      */
"CA12",                                                 /*140 CA12                      */
"CA13",                                                 /*141 CA13                      */
"CA14",                                                 /*142 CA14                      */
"CA15",                                                 /*143 CA15                      */
"CA16",                                                 /*144 CA16                      */
"CA17",                                                 /*145 CA17                      */
"CA18",                                                 /*146 CA18                      */
"CA19",                                                 /*147 CA19                      */
"CA20",                                                 /*148 CA20                      */
"CA21",                                                 /*149 CA21                      */
"CA22",                                                 /*150 CA22                      */
"CA23",                                                 /*151 CA23                      */
"CA24",                                                 /*152 CA24                      */
"CA25",                                                 /*153 CA25                      */
"CA26",                                                 /*154 CA26                      */
"CA27",                                                 /*155 CA27                      */
"CA28",                                                 /*156 CA28 RESERVED             */
"CA29",                                                 /*157 CA29 RESERVED             */
"CA30",                                                 /*158 CA30 RESERVED             */
"CA31",                                                 /*159 CA31 RESERVED             */
                                                                   


/**--------------------------------------------**
 **       The next new group is Warnings       **
 **--------------------------------------------**/

"WA0",                                                  /*160 WA0  RESERVED             */
"Dist. Degag. Actuator non Atteinte",                   /*161 WA1                       */
"Energie Maximum de Compensation Atteinte",             /*162 WA2  Max Energy Reached   */
"",                                                     /*163 WA3  Printer Buffer 80%   */
"WA4",                                                  /*164 WA4  Cont Pwr Limit       */
"Cpure Pui. Crete",                                     /*165 WA5  Peak Power Cutoff    */
"Coupure Distance Absolue",                             /*166 WA6  Absolute Cutoff      */
"Temps Soudage Etendu pour Compensation d'Energie",     /*167 WA7  Time Extended        */
"WA8",                                                  /*168 WA8                       */
"Cpure Dist Rel.",                                      /*169 WA9  Collapse Cutoff      */
"WA10",                                                 /*170 WA10                      */
"Ultrasons hors fonction par Entrée Utilisateur",       /*171 WA11                      */
"WA12",                                                 /*172 WA12                      */
"WA13",                                                 /*173 WA13                      */
"WA14",                                                 /*174 WA14                      */
"WA15",                                                 /*175 WA15                      */
"WA16",                                                 /*176 WA16                      */
"WA17",                                                 /*177 WA17                      */
"WA18",                                                 /*178 WA18                      */
"WA19",                                                 /*179 WA19                      */
"WA20",                                                 /*180 WA20                      */
"WA21",                                                 /*181 WA21                      */
"WA22",                                                 /*182 WA22                      */
"WA23",                                                 /*183 WA23                      */
"WA24",                                                 /*184 WA24                      */
"WA25",                                                 /*185 WA25                      */
"WA26",                                                 /*186 WA26                      */
"WA27",                                                 /*187 WA27                      */
"WA28",                                                 /*188 WA28 RESERVED             */
"WA29",                                                 /*189 WA29 RESERVED             */
"WA30",                                                 /*190 WA30 RESERVED             */
"WA31",                                                 /*191 WA31 RESERVED             */



/**------------------------------------------------------------**
 **        The next new group is Process Reject Alarms         **
 **------------------------------------------------------------**/

"PR0",                                                   /*192 PR0  RESERVED             */
"Lim.- Energie Rej.",                                    /*193 PR1  -R Energy Limit      */
"Lim.+ Energie Rej.",                                    /*194 PR2  +R Energy Limit      */
"Lim.- Puiss. Crete Rej.",                               /*195 PR3  -R Pk Power Limit    */
"Lim.+ Puiss. Crete Rej.",                               /*196 PR4  +R Pk Power Limit    */
"Lim.- Distance Relative Rej.",                          /*197 PR5  -R Col Dist Limit    */
"Lim.+ Distance Relative Rej.",                          /*198 PR6  +R Col Dist Limit    */
"Lim.- Distance Absolue Rej.",                           /*199 PR7  -R Abs Dist Limit    */
"Lim.+ Distance Absolue Rej.",                           /*200 PR8  +R Abs Dist Limit    */
"Lim.- Distance Trigg. Rej.",                            /*201 PR9  -R Trig Dist Limit   */
"Lim.+ Distance Trigg. Rej.",                            /*202 PR10 +R Trig Dist Limit   */
"Lim.- Force Soud Rej.",                                 /*203 PR11 -R Max Force Limit   */
"Lim.+ Force Soud Rej.",                                 /*204 PR12 +R Max Force Limit   */
"Lim.- Temps Rej.",                                      /*205 PR13 -R Time Limit        */
"Lim.+ Temps Rej.",                                      /*206 PR14 +R Time Limit        */
"PR15",                                                  /*207 PR15                      */
"PR16",                                                  /*208 PR16                      */
"PR17",                                                  /*209 PR17                      */
"Limite inf. non atteinte",                              /*210 PR18 LL Not Reached       */
"PR19",                                                  /*211 PR19                      */
"PR20",                                                  /*212 PR20                      */
"PR21",                                                  /*213 PR21                      */
"PR22",                                                  /*214 PR22                      */
"PR23",                                                  /*215 PR23                      */
"PR24",                                                  /*216 PR24                      */

"PR25",                                                  /*217 PR25                      */
"PR26",                                                  /*218 PR26                      */
"PR27",                                                  /*219 PR27                      */
"PR28",                                                  /*220 PR28 RESERVED             */
"PR29",                                                  /*221 PR29 RESERVED             */
"PR30",                                                  /*222 PR30 RESERVED             */
"PR31",                                                  /*223 PR31 RESERVED             */
                                                                   



/**-----------------------------------------------------------**
 **        The next new group is Process Suspect Alarms       **
 **-----------------------------------------------------------**/

"PS0",                                                   /*224 PS0  RESERVED             */
"Lim.- Energie Susp.",                                   /*225 PS1  -S Energy Limit      */
"Lim.+ Energie Susp.",                                   /*226 PS2  +S Energy Limit      */
"Lim.- Puiss. Crete Susp.",                              /*227 PS3  -S Pk Power Limit    */
"Lim.+ Puiss. Crete Susp.",                              /*228 PS4  +S Pk Power Limit    */
"Lim.- Distance Relative Susp.",                         /*229 PS5  -S Col Dist Limit    */
"Lim.+ Distance Relative Susp.",                         /*230 PS6  +S Col Dist Limit    */
"Lim.- Distance Absolue Susp.",                          /*231 PS7  -S Abs Dist Limit    */
"Lim.+ Distance Absolue Susp.",                          /*232 PS8  +S Abs Dist Limit    */
"Lim.- Distance Trigg. Susp.",                           /*233 PS9  -S Trig Dist Limit   */
"Lim.+ Distance Trigg. Susp.",                           /*234 PS10 +S Trig Dist Limit   */
"Lim.- Force Soud Susp.",                                /*235 PS11 -S Max Force Limit   */
"Lim.+ Force Soud Susp.",                                /*236 PS12 +S Max Force Limit   */
"Lim.- Temps Susp.",                                     /*237 PS13 -S Time Limit        */
"Lim.+ Temps Susp.",                                     /*238 PS14 +S Time Limit        */
"PS15",                                                  /*239 PS15                      */
"PS16",                                                  /*240 PS16                      */
"PS17",                                                  /*241 PS17                      */
"PS18",                                                  /*242 PS18                      */
"PS19",                                                  /*243 PS19                      */
"PS20",                                                  /*244 PS20                      */
"PS21",                                                  /*245 PS21                      */
"PS22",                                                  /*246 PS22                      */
"PS23",                                                  /*247 PS23                      */
"PS24",                                                  /*248 PS24                      */
"PS25",                                                  /*249 PS25                      */
"PS26",                                                  /*250 PS26                      */
"PS27",                                                  /*251 PS27                      */
"PS28",                                                  /*252 PS28 RESERVED             */
"PS29",                                                  /*253 PS29 RESERVED             */
"PS30",                                                  /*254 PS30 RESERVED             */
"PS31"                                                   /*255 PS31 RESERVED             */
                                                                    
};

//OmniLingua - End French insertion here

const STR ** AlarmText[] = { AlarmEng, AlarmGer, AlarmSpn, AlarmItl, AlarmFr };


const STR *const AlarmMessEng[] = { "Alarm: ",
                                    "Note : "};


const STR *const AlarmMessGer[] = { "Alarm: ",
                                    "Anmerkung: "}; 


const STR *const AlarmMessSpn[] = { "Alarma: ",
                                    "Nota : "};


const STR *const AlarmMessItl[] = { "Allarme: ",
                                    "Note : "};


const STR *const AlarmMessFr[]  = { "Alarme: ",
                                    "Note : "};

const STR **AlarmMess[] = { AlarmMessEng, AlarmMessGer, AlarmMessSpn, AlarmMessItl, AlarmMessFr };








const STR *const Alarm1Eng[] = {


/**------------------------------------------------**
 **        This group is the Setup Alarms          **
 **------------------------------------------------**/


/** ----  SETUP GROUP 1  ---- **/


"SE0",                                                                                /*0   SE0   RESERVED            */
"+-Pruefe Zeit Grenzwert ueberschritten",                                             /*1   SE1   RESERVED            */
"+-Aussch Zeit Grenzwert ueberschritten",                                             /*2   SE2   +-Time Limit Crossed*/
"+-Pruefe Energie Grenzwert ueberschritten",                                          /*3   SE3   +-Time Limit Crossed*/
"+-Aussch Energie Grenzwert ueberschritten",                                          /*4   SE4   +-Eng Limit Crossed */
"+-Pruefe Leist. Grenzwert ueberschritten",                                           /*5   SE5   +-Eng Limit Crossed */
"+-Aussch Leist. Grenzwert ueberschritten",                                           /*6   SE6   +-Pwr Limit Crossed */
"+-Pruefe Frequenz Grenzwert ueberschritten",                                         /*7   SE7   +-Pwr Limit Crossed */
"+-Aussch Frequenz Grenzwert ueberschritten",                                         /*8   SE8   +-Freq Limit Crossed*/
"+-Pruefe Abs. Grenzwert ueberschritten",                                             /*9   SE9   +-Freq Limit Crossed*/
"+-Aussch Abs. Grenzwert ueberschritten",                                             /*10  SE10  +-Abs Limit Crossed */
"+-Pruefe Rel. Grenzwert ueberschritten",                                             /*11  SE11  +-Abs Limit Crossed */
"+-Aussch Rel. Grenzwert ueberschritten",                                             /*12  SE12  +-Col Limit Crossed */
"+-Pruefe Schweisskraft Grenzwert ueberschritten",                                    /*13  SE13  +-Col Limit Crossed */
"+-Aussch Schweisskraft Grenzwert ueberschritten",                                    /*14  SE14  +-Frc Limit Crossed */
"Amplitudenprofil Konflikt mit Schweisszeit",                                         /*15  SE15  +-Frc Limit Crossed */
"Amplitudenprofil Konflikt mit +Aussch Spitzenleist. Grenzwert",                      /*16  SE16  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Pruefe Spitzenleist. Grenzwert",                      /*17  SE17  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Aussch Energie Grenzwert",                            /*18  SE18  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Pruefe Energie Grenzwert",                            /*19  SE19  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Aussch Abs. Grenzwert",                               /*20  SE20  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Pruefe Abs. Grenzwert",                               /*21  SE21  Amp Step Conflict   */
"SE22",                                                                               /*22  SE22  Amp Step Conflict   */
"SE23",                                                                               /*23  SE23  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit -Aussch Triggerweg Grenzwert",                         /*24  SE24  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit -Pruefe Triggerweg Grenzwert",                         /*25  SE25  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Aussch Triggerweg Grenzwert",                         /*26  SE26  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Pruefe Triggerweg Grenzwert",                         /*27  SE27  Amp Step Conflict   */
"SE28",                                                                               /*28  SE28  RESERVED            */
"SE29",                                                                               /*29  SE29  RESERVED            */
"SE30",                                                                               /*30  SE30  RESERVED            */
"SE31",                                                                               /*31  SE31  RESERVED            */
                                                                                        
                                                                                        
                                                                                        
                                                                                        
/** ----  SETUP GROUP 2  ---- **/


"SE32",                                                                               /*32  SE32  RESERVED            */
"Amplitude Step at Absolute Distance Conflicts with Pretrigger Distance",             /*33  SE33  Amp Step Conflict   */
"Amplitude Step at Absolute Distance Conflicts with Absolute Distance Cutoff",        /*34  SE34  Amp Step Conflict   */
"Amplitude Step at Absolute Distance Cutoff Conflicts with Missing Part Cycle Abort", /*35  SE35  Amp Step Conflict   */
"Amplitude Step at Absolute Distance Cutoff Conflicts with Missing Part Cycle Abort", /*36  SE36  Amp Step Conflict   */
"Amplitude Step at Power Conflicts with Peak Power Setting",                          /*37  SE37  Amp Step Conflict   */
"Amplitude Step at Energy Conflicts with Energy Compensation",                        /*38  SE38  Amp Step Conflict   */
"Amplitude Step at Force Conflicts with Force Setting",                               /*39  SE39  Amp Step Conflict   */
"Amplitude Step at Power Conflicts with Peak Power Cutoff",                           /*40  SE40  Amp Step Conflict   */
"Amplitude Step at Collapse Conflicts with Collapse Distance Cutoff",                 /*41  SE41  Amp Step Conflict   */
"Amplitude Step at Collapse Conflicts with Collapse Distance",                        /*42  SE42  Amp Step Conflict   */
"Amplitude Step at Time Conflicts with Timeout",                                      /*43  SE43  Amp Step Conflict   */
"+-Trigger Distance Reject Limit Crossed",                                            /*44  SE44  +-Trig Limit Crossed*/
"+-Trigger Distance Suspect Limit Crossed",                                           /*45  SE45  +-Trig Limit Crossed*/
"The preset recalled is either clear or not available for control level.",            /*46  SE46  Preset Not Available*/
"Amplitude Step at Absolute Distance Conflicts with Absolute Distance Setting",       /*47  SE47  Amp Step Conflict   */
"Amplitude Step at Energy Conflicts with Energy Setting",                             /*48  SE48  Amp Step Conflict   */
"+Reject Time Limit and Timeout Crossed",                                             /*49  SE49  Timeout Conflict    */
"-Suspect Time Limit and Timeout Crossed",                                            /*50  SE50  Timeout Conflict    */
"-Reject Time Limit and Timeout Crossed",                                             /*51  SE51  Timeout Conflict    */
"Amplitude Step on Force equal to or greater than all force values",                  /*52  SE52  Amp Step on Force   */
"Amplitude Step on Amplitude equal to or greater than all amp values",                /*53  SE53  Force Step on Amp   */
"-Suspect Trigger Limit is greater Than +Suspect Absolute Limit",                     /*54  SE54  -S Trg > -S Abs     */
"+Suspect Trigger Distance Limit is greater than +Suspect Absolute Distance Limit",   /*55  SE55  +S Trg > +S Abs     */
"-Reject Trigger Limit is greater than -Reject Absolute Limit",                       /*56  SE56  -R Trg > -R Abs     */
"+Reject Trigger Limit is greater than +Reject Absolute Limit",                       /*57  SE57  +R Trg > +R Abs     */
"+Suspect Time Limit and Timeout Crossed",                                            /*58  SE58  Timeout Conflict    */
"-Reject Power Limit and Peak Power Cutoff Crossed",                                  /*59  SE59  Cutoff Conflict     */
"SE60",                                                                               /*60  SE60  RESERVED            */
"SE61",                                                                               /*61  SE61  RESERVED            */
"SE62",                                                                               /*62  SE62  RESERVED            */
"SE63",                                                                               /*63  SE63  RESERVED            */




/** ----  SETUP GROUP 3  ---- **/


"SE64",                                                                               /*64  SE64  RESERVED            */
"+Reject Power Limit and Peak Power Cutoff Crossed",                                  /*65  SE65  Cutoff Conflict     */
"-Suspect Power Limit and Peak Power Cutoff Crossed",                                 /*66  SE66  Cutoff Conflict     */
"+Suspect Power Limit and Peak Power Cutoff Crossed",                                 /*67  SE67  Cutoff Conflict     */
"SE68",                                                                               /*68  SE68  Cutoff Conflict     */
"SE69",                                                                               /*69  SE69  Cutoff Conflict     */
"SE70",                                                                               /*70  SE70                      */
"SE71",                                                                               /*71  SE71                      */
"Both Trigger Delay and Pre-trigger are on",                                          /*72  SE72  Trig Delay & Pretrig*/
"Trigger force equal to or greater than weld force",                                  /*73  SE73  Trig > Weld Force   */
"+Reject Time Limit and -Suspect Time Limit Crossed",                                 /*74  SE74  Time S/R Limit Cross*/
"+Suspect Time Limit and -Reject Time Limit Crossed",                                 /*75  SE75  Time S/R Limit Cross*/
"+Reject Time Limit and +Suspect Time Limit Crossed",                                 /*76  SE76  Time S/R Limit Cross*/
"-Reject Time Limit and -Suspect Time Limit Crossed",                                 /*77  SE77  Time S/R Limit Cross*/
"+Reject Energy Limit and -Suspect Energy Limit Crossed",                             /*78  SE78  Eng S/R Limit Cross */
"+Suspect Energy Limit and -Reject Energy Limit Crossed",                             /*79  SE79  Eng S/R Limit Cross */
"+Reject Energy Limit and +Suspect Energy Limit Crossed",                             /*80  SE80  Eng S/R Limit Cross */
"-Reject Energy Limit and -Suspect Energy Limit Crossed",                             /*81  SE81  Eng S/R Limit Cross */
"+Reject Peak Power Limit and -Suspect Peak Power Limit Crossed",                     /*82  SE82  Pwr S/R Limit Cross */
"+Suspect Peak Power Limit and -Reject Peak Power Limit Crossed",                     /*83  SE83  Pwr S/R Limit Cross */
"+Reject Peak Power Limit and +Suspect Peak Power Limit Crossed",                     /*84  SE84  Pwr S/R Limit Cross */
"-Reject Peak Power Limit and -Suspect Peak Power Limit Crossed",                     /*85  SE85  Pwr S/R Limit Cross */
"+Reject Absolute Distance Limit and -Suspect Absolute Distance Limit Crossed",       /*86  SE86  Abs S/R Limit Cross */
"+Suspect Absolute Distance Limit and -Reject Absolute Distance Limit Crossed",       /*87  SE87  Abs S/R Limit Cross */
"+Reject Absolute Distance Limit and +Suspect Absolute Distance Limit Crossed",       /*88  SE88  Abs S/R Limit Cross */
"-Reject Absolute Distance Limit and -Suspect Absolute Distance Limit Crossed",       /*89  SE89  Abs S/R Limit Cross */
"+Reject Collapse Distance Limit and -Suspect Collapse Distance Limit Crossed",       /*90  SE90  Col S/R Limit Cross */
"+Suspect Collapse Distance Limit and -Reject Collapse Distance Limit Crossed",       /*91  SE91  Col S/R Limit Cross */
"SE92",                                                                               /*92  SE92  RESERVED        */
"SE93",                                                                               /*93  SE93  RESERVED        */
"SE94",                                                                               /*94  SE94  RESERVED        */
"SE95",                                                                               /*95  SE95  RESERVED        */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 4  ---- **/                                                       
                                                                                        
                                                                                        
"SE96",                                                                               /*96   SE96  RESERVED            */
"+Reject Collapse Distance Limit and +Suspect Collapse Distance Limit Crossed",       /*97   SE97  Col S/R Limit Cross */
"-Reject Collapse Distance Limit and -Suspect Collapse Distance Limit Crossed",       /*98   SE98  Col S/R Limit Cross */
"+Reject Weld Force Limit and -Suspect Weld Force Limit Crossed",                     /*99   SE99  Frc S/R Limit Cross */
"+Suspect Weld Force Limit and -Reject Weld Force Limit Crossed",                     /*100  SE100 Frc S/R Limit Cross */
"+Reject Weld Force Limit and +Suspect Weld Force Limit Crossed",                     /*101  SE101 Frc S/R Limit Cross */
"-Reject Weld Force Limit and -Suspect Weld Force Limit Crossed",                     /*102  SE102 Frc S/R Limit Cross */
"+Reject Frequency Limit and -Suspect Frequency Limit Crossed",                       /*103  SE103 Freq S/R Limit Cross*/
"+Suspect Frequency Limit and -Reject Frequency Limit Crossed",                       /*104  SE104 Freq S/R Limit Cross*/
"+Reject Frequency Limit and +Suspect Frequency Limit Crossed",                       /*105  SE105 Freq S/R Limit Cross*/
"-Reject Frequency Limit and -Suspect Frequency Limit Crossed",                       /*106  SE106 Freq S/R Limit Cross*/
"+Reject Trigger Distance Limit and -Suspect Trigger Distance Limit Crossed",         /*107  SE107 Trig S/R Limit Cross*/
"+Suspect Trigger Distance Limit and -Reject Trigger Distance Limit Crossed",         /*108  SE108 Trig S/R Limit Cross*/
"+Reject Trigger Distance Limit and +Suspect Trigger Distance Limit Crossed",         /*109  SE109 Trig S/R Limit Cross*/
"-Reject Trigger Distance Limit and -Suspect Trigger Distance Limit Crossed",         /*110  SE110 Trig S/R Limit Cross*/
"Force Step Conflicts with Collapse Cutoff",                                          /*111  SE111 Force Step Cutoff   */
"Force Step Conflicts with Collapse Cutoff",                                          /*112  SE112 Force Step Cutoff   */
"Force Step Conflicts with Collapse Cutoff",                                          /*113  SE113 Force Step Cutoff   */
"Force Step Conflicts with Collapse Cutoff",                                          /*114  SE114 Force Step Cutoff   */
"Force Step Conflicts with Collapse Cutoff",                                          /*115  SE115 Force Step Cutoff   */
"Force Step Conflicts with Collapse Cutoff",                                          /*116  SE116 Force Step Cutoff   */
"Force Step Conflicts with Collapse Cutoff",                                          /*117  SE117 Force Step Cutoff   */
"Force Step Conflicts with Collapse Cutoff",                                          /*118  SE118 Force Step Cutoff   */
"Energy Compensation Minimum and Maximum Settings Crossed",                           /*119  SE119 Energy Comp Crossed */
"Missing Part Minimum and Maximum Settings Crossed",                                  /*120  SE120 Missing Part Crossed*/
"Pretrigger Distance and Force Step at Absolute Distance Limit Crossed",              /*121  SE121 Pretrigger Conflict */
"Pretrigger Distance and Amplitude Step at Absolute Distance Limit Crossed",          /*122  SE122 Pretrigger Conflict */
"Pretrigger Distance and -Reject Absolute Distance Limit Crossed",                    /*123  SE123 Pretrigger Conflict */
"SE124",                                                                              /*124  SE124 RESERVED            */
"SE125",                                                                              /*125  SE125 RESERVED            */
"SE126",                                                                              /*126  SE126 RESERVED            */
"SE127",                                                                              /*127  SE127 RESERVED            */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 5  ---- **/


"SE128",                                                                              /*128  SE128 RESERVED            */
"Pretrigger Distance and -Suspect Absolute Distance Limit Crossed",                   /*129  SE129 Pretrigger Conflict */
"Pretrigger Distance and +Reject Absolute Distance Limit Crossed",                    /*130  SE130 Pretrigger Conflict */
"Pretrigger Distance and +Suspect Absolute Distance Limit Crossed",                   /*131  SE131 Pretrigger Conflict */
"Pretrigger Distance and +Reject Trigger Distance Limit Crossed",                     /*132  SE132 Pretrigger Conflict */
"Pretrigger Distance and +Suspect Trigger Distance Limit Crossed",                    /*133  SE133 Pretrigger Conflict */
"Pretrigger Distance and -Reject Trigger Distance Limit Crossed",                     /*134  SE134 Pretrigger Conflict */
"Pretrigger Distance and -Suspect Trigger Distance Limit Crossed",                    /*135  SE135 Pretrigger Conflict */
"Pretrigger Distance and Absolute Cutoff Distance Crossed",                           /*136  SE136 Pretrigger Conflict */
"Pretrigger Distance and Absolute Distance Crossed",                                  /*137  SE137 Pretrigger Conflict */
"Absolute Distance Cutoff and -Reject Absolute Distance Limit Crossed",               /*138  SE138 Abs Cutoff Conflict */
"Absolute Distance Cutoff and -Reject Trigger Distance Limit Crossed",                /*139  SE139 Abs Cutoff Conflict */
"Absolute Distance Cutoff and -Suspect Absolute Distance Limit Crossed",              /*140  SE140 Abs Cutoff Conflict */
"Absolute Distance Cutoff and -Suspect Trigger Distance Limit Crossed",               /*141  SE141 Abs Cutoff Conflict */
"Absolute Distance Cutoff and +Reject Absolute Distance Limit Crossed",               /*142  SE142 Abs Cutoff Conflict */
"Absolute Distance Cutoff and +Reject Trigger Distance Limit Crossed",                /*143  SE143 Abs Cutoff Conflict */
"Absolute Distance Cutoff and +Suspect Absolute Distance Limit Crossed",              /*144  SE144 Abs Cutoff Conflict */
"Absolute Distance Cutoff and +Suspect Trigger Distance Limit Crossed",               /*145  SE145 Abs Cutoff Conflict */
"Missing Part Maximum Distance and -Reject Absolute Distance Limit Crossed",          /*146  SE146 Missing Part Conflct*/
"Missing Part Minimum Distance and -Reject Absolute Distance Limit Crossed",          /*147  SE147 Missing Part Conflct*/
"Missing Part Maximum Distance and -Reject Trigger Distance Limit Crossed",           /*148  SE148 Missing Part Conflct*/
"Missing Part Minimum Distance and -Reject Trigger Distance Limit Crossed",           /*149  SE149 Missing Part Conflct*/
"Missing Part Minimum Distance and -Suspect Absolute Distance Limit Crossed",         /*150  SE150 Missing Part Conflct*/
"Missing Part Maximum Distance and -Suspect Trigger Distance Limit Crossed",          /*151  SE151 Missing Part Conflct*/
"Missing Part Minimum Distance and -Suspect Trigger Distance Limit Crossed",          /*152  SE152 Missing Part Conflct*/
"Missing Part Maximum Distance and +Reject Absolute Distance Limit Crossed",          /*153  SE153 Missing Part Conflct*/
"Missing Part Minimum Distance and +Reject Absolute Distance Limit Crossed",          /*154  SE154 Missing Part Conflct*/
"Missing Part Maximum Distance and +Reject Trigger Distance Limit Crossed",           /*155  SE155 Missing Part Conflct*/
"SE156",                                                                              /*156  SE156 RESERVED            */
"SE157",                                                                              /*157  SE157 RESERVED            */
"SE158",                                                                              /*158  SE158 RESERVED            */
"SE159",                                                                              /*159  SE159 RESERVED            */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 6  ---- **/


"SE160",                                                                              /*160  SE160 RESERVED            */
"Missing Part Minimum Distance and +Reject Trigger Distance Limit Crossed",           /*161  SE161 Missing Part Conflct*/
"Missing Part Maximum Distance and +Suspect Absolute Distance Limit Crossed",         /*162  SE162 Missing Part Conflct*/
"Missing Part Minimum Distance and +Suspect Absolute Distance Limit Crossed",         /*163  SE163 Missing Part Conflct*/
"Missing Part Maximum Distance and +Suspect Trigger Distance Limit Crossed",          /*164  SE164 Missing Part Conflct*/
"Missing Part Minimum Distance and +Suspect Trigger Distance Limit Crossed",          /*165  SE165 Missing Part Conflct*/
"Missing Part Minimum Distance and Absolute Distance Cutoff Crossed",                 /*166  SE166 Missing Part Conflct*/
"Missing Part Maximum Distance and Absolute Distance Cutoff Crossed",                 /*167  SE167 Missing Part Conflct*/
"Missing Part Minimum Distance and Absolute Distance Setting Crossed",                /*168  SE168 Missing Part Conflct*/
"Missing Part Maximum Distance and Absolute Distance Setting Crossed",                /*169  SE169 Missing Part Conflct*/
"Energy Compensation Minimum Value and +Reject Energy Limit Crossed",                 /*170  SE170 Energy Comp Conflict*/
"Energy Compensation Minimum Value and +Suspect Energy Limit Crossed",                /*171  SE171 Energy Comp Conflict*/
"Energy Compensation Maximum Value and -Reject Energy Limit Crossed",                 /*172  SE172 Energy Comp Conflict*/
"Energy Compensation Maximum Value and -Suspect Energy Limit Crossed",                /*173  SE173 Energy Comp Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*174  SE174 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*175  SE175 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*176  SE176 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*177  SE177 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*178  SE178 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*179  SE179 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*180  SE180 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*181  SE181 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*182  SE182 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*183  SE183 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*184  SE184 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*185  SE185 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*186  SE186 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*187  SE187 Rapid Trav. Conflict*/

"SE188",                                                                              /*188  SE188 RESERVED            */
"SE189",                                                                              /*189  SE189 RESERVED            */
"SE190",                                                                              /*190  SE190 RESERVED            */
"SE191",                                                                              /*191  SE191 RESERVED            */



/** ----  SETUP GROUP 7  ---- **/

                                                                                      
"SE192",                                                                              /*192 SE192 RESERVED            */
"Rapid Traverse Setup Conflict",                                                      /*193 SE193 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*194 SE194 Rapid Trav. Conflict*/
"Rapid Traverse Setup Conflict",                                                      /*195 SE195 Rapid Trav. Conflict*/
"Hold Force and Limits Crossed",                                                      /*196 SE196 Hold Force Conflict */
"Hold Force and Limits Crossed",                                                      /*197 SE197 Hold Force Conflict */
"Hold Force and Limits Crossed",                                                      /*198 SE198 Hold Force Conflict */
"Hold Force and Limits Crossed",                                                      /*199 SE199 Hold Force Conflict */
"Force A and Limits Crossed",                                                         /*200 SE200 Force/Lmt Conflict  */
"Force A and Limits Crossed",                                                         /*201 SE201 Force/Lmt Conflict  */
"Force A and Limits Crossed",                                                         /*202 SE202 Force/Lmt Conflict  */
"Force A and Limits Crossed",                                                         /*203 SE203 Force/Lmt Conflict  */
"Force B and Limits Crossed",                                                         /*204 SE204 Force/Lmt Conflict  */
"Force B and Limits Crossed",                                                         /*205 SE205 Force/Lmt Conflict  */
"Force B and Limits Crossed",                                                         /*206 SE206 Force/Lmt Conflict  */
"Force B and Limits Crossed",                                                         /*207 SE207 Force/Lmt Conflict  */
"Force Step Conflicts with Limits",                                                   /*208 SE208 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*209 SE209 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*210 SE210 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*211 SE211 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*212 SE212 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*213 SE213 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*214 SE214 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*215 SE215 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*216 SE216 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*217 SE217 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*218 SE218 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*219 SE219 Force Step Conflict */
"SE220",                                                                              /*220 SE220 RESERVED            */
"SE221",                                                                              /*221 SE221 RESERVED            */
"SE222",                                                                              /*222 SE222 RESERVED            */
"SE223",                                                                              /*223 SE223 RESERVED            */



        
/** ----  SETUP GROUP 8  ---- **/

                                                                              
"SE224",                                                                              /*224  SE224 RESERVED            */
"Force Step Conflicts with Limits",                                                   /*225  SE225 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*226  SE226 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*227  SE227 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*228  SE228 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*229  SE229 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*230  SE230 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*231  SE231 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*232  SE232 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*233  SE233 Force Step Conflict */
"Force Step Conflicts with Limits",                                                   /*234  SE234 Force Step Conflict */
"Force Step Conflicts with Absolute Distance Setting",                                /*235  SE235 Force Step Conflict */
"Force Step Conflicts with Pretrigger Distance Setting",                              /*236  SE236 Force Step Conflict */
"Force Step Conflicts with Absolute Distance Cutoff",                                 /*237  SE237 Force Step Conflict */
"Force Step Conflicts with Trigger Cutoff Setting",                                   /*238  SE238 Force Step Conflict */
"Force Step Conflicts with Peak Power Cutoff",                                        /*239  SE239 Force Step Conflict */
"Force Step Conflicts with Peak Power Setting",                                       /*240  SE240 Force Step Conflict */
"Force Step Conflicts with Energy Setting",                                           /*241  SE241 Force Step Conflict */
"Force Step Conflicts with Energy Compensation",                                      /*242  SE242 Force Step Conflict */
"Force Step Conflicts with Weld Time",                                                /*243  SE243 Force Step Conflict */
"Force Step at Amplitude Conflicts with Amplitude Setting",                           /*244  SE244 Amp/F Step Conflict */
"Weld Force A Can Not Be Reached Because Inlet Pressure is Low",                      /*245  SE245 Weld Force>Pressure */
"Weld Force B Can Not Be Reached Because Inlet Pressure is Low",                      /*246  SE246 Force B>Pressure    */
"Hold Force Can Not Be Reached Because Inlet Pressure is Low",                        /*247  SE247 Hold Force>Pressure */
"Inlet Pressure Is Too High for Specified Weld Force",                                /*248  SE248 Pressure>Weld Force */
"Inlet Pressure Is Too High for Specified Weld Force B",                              /*249  SE249 Pressure>Force B    */
"Inlet Pressure Is Too High for Specified Hold Force",                                /*250  SE250 Pressure>Hold Force */
"Trigger Force Conflicts with Suspect Limits",                                        /*251  SE251 Trig Force Conflict */
"SE252",                                                                              /*252  SE252 RESERVED            */
"SE253",                                                                              /*253  SE253 RESERVED            */
"SE254",                                                                              /*254  SE254 RESERVED            */
"SE255",                                                                              /*255  SE255 RESERVED            */
 



/** ----  SETUP GROUP 9  ---- **/

                                                                                     
"SE156",                                                                              /*256 SE256 RESERVED            */
"Trigger Force Conflicts with Reject Limits",                                         /*257 SE257 Trig Force Conflict */
"SE258",                                                                              /*258 SE258                     */
"This Preset requires an Encoder to run",                                             /*259 SE259 Encoder Required    */
"SE260",                                                                              /*260 SE260                     */
"SE261",                                                                              /*261 SE261                     */
"SE262",                                                                              /*262 SE262                     */
"SE263",                                                                              /*263 SE263                     */
"Energy Compensation minimum Value and -Reject Energy Limit Crossed",                 /*264 SE264 Energy Comp Conflict*/
"Energy Compensation minimum Value and -Suspect Energy Limit Crossed",                /*265 SE265 Energy Comp Conflict*/
"Energy Compensation maximum Value and +Reject Energy Limit Crossed",                 /*266 SE266 Energy Comp Conflict*/
"Energy Compensation maximum Value and +Suspect Energy Limit Crossed",                /*267 SE267 Energy Comp Conflict*/
"Feature(s) selected are not available in this model",                                /*268 SE268 Invalid Preset      */
"An undefined preset has been requested for use in a sequence",                       /*269 SE269 Undefined Preset    */
"",                                                                                   /*270 SE270 Printer Offline     */
"-Suspect Trigger Limit and +Suspect Absolute Distance Limit Crossed",                /*271 SE271 -S Trg > +S Abs     */
"-Suspect Trigger Limit and +Reject Absolute Distance Limit Crossed",                 /*272 SE272 -S Trg > +R Abs     */
"-Reject Trigger Limit and +Suspect Absolute Distance Limit Crossed",                 /*273 SE273 -R Trg > +S Abs     */
"-Reject Trigger Limit and +Reject Absolute Distance Limit Crossed",                  /*274 SE274 -R Trg > +R Abs     */
"-Suspect Trigger Limit and Absolute Distance Crossed",                               /*275 SE275 -S Trg > Abs        */
"-Reject Trigger Limit and Absolute Distance Crossed",                                /*276 SE276 -R Trg > Abs        */
"SE277",                                                                              /*277 SE277 -R Trg > Abs Cutoff */
"SE278",                                                                              /*278 SE278                     */
"SE279",                                                                              /*279 SE279                     */
"SE280",                                                                              /*280 SE280                     */
"SE281",                                                                              /*281 SE281                     */
"SE282",                                                                              /*282 SE282                     */
"SE283",                                                                              /*283 SE283                     */
"SE284",                                                                              /*284 SE284 RESERVED            */
"SE285",                                                                              /*285 SE285 RESERVED            */
"SE286",                                                                              /*286 SE286 RESERVED            */
"SE287",                                                                              /*287 SE287 RESERVED            */
 



/** ----  SETUP GROUP 10  ---- **/

                                                                                     
"External U/S Delay and Pretrigger both on",                                          /*289 Trigger Delay Conflict    */
"External U/S Delay input pin not defined",                                           /*290 Trigger Delay Conflict    */
"Either External Start output or input pin is not defined",                           /*291 SV Interlock Setup        */
"Missing Part Output defined but function not turned on",                             /*292 Missing Part Conflict     */
"Energy Braking Setup",                                                               /*293 Energy Braking setup      */
"Input Pin Conflict",                                                                 /*294 Input Pin Conflict        */
"SE295",                                                                              /*295 SE295                     */
"Ext Signal Setup",                                                                   /*296 SE296                     */
"SE297",                                                                              /*297 SE297                     */
"SE298",                                                                              /*298 SE298                     */
"SE299",                                                                              /*299 SE299                     */
"SE300",                                                                              /*300 SE300                     */
"SE301",                                                                              /*301 SE301                     */
"SE302",                                                                              /*302 SE302                     */
"SE303",                                                                              /*303 SE303                     */
"SE304",                                                                              /*304 SE304                     */
"SE305",                                                                              /*305 SE305                     */
"SE306",                                                                              /*306 SE306                     */
"SE307",                                                                              /*307 SE307                     */
"SE308",                                                                              /*308 SE308                     */
"SE309",                                                                              /*309 SE309                     */
"SE310",                                                                              /*310 SE310                     */
"SE311",                                                                              /*311 SE311                     */
"SE312",                                                                              /*312 SE312                     */
"SE313",                                                                              /*313 SE313                     */
"SE314",                                                                              /*314 SE314                     */
"SE315",                                                                              /*315 SE315                     */
"SE316",                                                                              /*316 SE316 RESERVED            */
"SE317",                                                                              /*317 SE317 RESERVED            */
"SE318",                                                                              /*318 SE318 RESERVED            */
"SE319",                                                                              /*319 SE319 RESERVED            */

};

//OmniLingua - Start German insertion here

const STR *const Alarm1Ger[] = {


/**------------------------------------------------**
 **        This group is the Setup Alarms          **
 **------------------------------------------------**/


/** ----  SETUP GROUP 1  ---- **/


"SE0",                                                                                /*0   SE0   RESERVED            */
"+-Pruefe Zeit Grenzwert ueberschritten",                                                       /*1   SE1   RESERVED            */
"+-Aussch Zeit Grenzwert ueberschritten",                                                        /*2   SE2   +-Time Limit Crossed*/
"+-Pruefe Energie Grenzwert ueberschritten",                                                     /*3   SE3   +-Time Limit Crossed*/
"+-Aussch Energie Grenzwert ueberschritten",                                                      /*4   SE4   +-Eng Limit Crossed */
"+-Pruefe Leist. Grenzwert ueberschritten",                                                      /*5   SE5   +-Eng Limit Crossed */
"+-Aussch Leist. Grenzwert ueberschritten",                                                       /*6   SE6   +-Pwr Limit Crossed */
"+-Pruefe Frequenz Grenzwert ueberschritten",                                                  /*7   SE7   +-Pwr Limit Crossed */
"+-Aussch Frequenz Grenzwert ueberschritten",                                                   /*8   SE8   +-Freq Limit Crossed*/
"+-Pruefe Abs. Grenzwert ueberschritten",                                          /*9   SE9   +-Freq Limit Crossed*/
"+-Aussch Abs. Grenzwert ueberschritten",                                           /*10  SE10  +-Abs Limit Crossed */
"+-Pruefe Rel. Grenzwert ueberschritten",                                          /*11  SE11  +-Abs Limit Crossed */
"+-Aussch Rel. Grenzwert ueberschritten",                                           /*12  SE12  +-Col Limit Crossed */
"+-Pruefe Schweisskraft Grenzwert ueberschritten",                                             /*13  SE13  +-Col Limit Crossed */
"+-Aussch Schweisskraft Grenzwert ueberschritten",                                              /*14  SE14  +-Frc Limit Crossed */
"Amplitudenprofil Konflikt mit Schweisszeit",                                            /*15  SE15  +-Frc Limit Crossed */
"Amplitudenprofil Konflikt mit +Aussch Spitzenleist. Grenzwert",                             /*16  SE16  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Pruefe Spitzenleist. Grenzwert",                            /*17  SE17  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Aussch Energie Grenzwert",                                 /*18  SE18  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Pruefe Energie Grenzwert",                                /*19  SE19  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Aussch Abs. Grenzwert",                      /*20  SE20  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Pruefe Abs. Grenzwert",                     /*21  SE21  Amp Step Conflict   */
"SE22",                                                                               /*22  SE22  Amp Step Conflict   */
"SE23",                                                                               /*23  SE23  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit -Aussch Triggerweg Grenzwert",                       /*24  SE24  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit -Pruefe Triggerweg Grenzwert",                      /*25  SE25  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Aussch Triggerweg Grenzwert",                       /*26  SE26  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit +Pruefe Triggerweg Grenzwert",                      /*27  SE27  Amp Step Conflict   */
"SE28",                                                                               /*28  SE28  RESERVED            */
"SE29",                                                                               /*29  SE29  RESERVED            */
"SE30",                                                                               /*30  SE30  RESERVED            */
"SE31",                                                                               /*31  SE31  RESERVED            */
                                                                                        
                                                                                        
                                                                                        
                                                                                        
/** ----  SETUP GROUP 2  ---- **/


"SE32",                                                                               /*32  SE32  RESERVED            */
"Amplitudenprofil Konflikt mit Pretriggerweg bei Abs.",             /*33  SE33  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit Weg abs. Einstellung bei Abs.",        /*34  SE34  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit fehlendem Teil bei Abs. Abschaltung",  /*35  SE35  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit fehlendem Teil bei Abs. Abschaltung", /*36  SE36  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit Spitzenleist. Einstellung bei Leistung",                          /*37  SE37  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit Energie Ausgleich bei Energie",                        /*38  SE38  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit Kraft Einstellung bei Kraft",                               /*39  SE39  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit Spitzenleist. Abschaltung bei Leistung",                           /*40  SE40  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit Rel. Abschaltung bei Rel.",                 /*41  SE41  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit Weg rel. bei Rel.",                        /*42  SE42  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit Zeitueberschreitung bei Zeit",                                      /*43  SE43  Amp Step Conflict   */
"+-Aussch Triggerweg Grenzwert ueberschritten",                                            /*44  SE44  +-Trig Limit Crossed*/
"+-Pruefe Triggerweg Grenzwert ueberschritten",                                           /*45  SE45  +-Trig Limit Crossed*/
"The preset recalled is either clear or not available for control level.",            /*46  SE46  Preset Not Available*/
"Amplitudenprofil Konflikt mit Abs. Weg Einstellung bei Abs.",       /*47  SE47  Amp Step Conflict   */
"Amplitudenprofil Konflikt mit Energie Einstellung bei Energie",                             /*48  SE48  Amp Step Conflict   */
"+Aussch Zeit Grenzwert und Zeitueberschreitung ueberschritten",                                             /*49  SE49  Timeout Conflict    */
"-Pruefe Zeit Grenzwert und Zeitueberschreitung ueberschritten",                                            /*50  SE50  Timeout Conflict    */
"-Aussch Zeit Grenzwert und Zeitueberschreitung ueberschritten",                                             /*51  SE51  Timeout Conflict    */
"Amplitudenprofil bei Kraft gleich oder groesser als alle Kraftwerte",                  /*52  SE52  Amp Step on Force   */
"Amplitudenprofil bei Amplitude gleich oder groesser als alle Ampl. Werte",                /*53  SE53  Force Step on Amp   */
"-Pruefe Trigger Grenzwert groesser als +Pruefe Abs. Grenzwert",                     /*54  SE54  -S Trg > -S Abs     */
"+Pruefe Triggerweg Grenzwert groesser als +Pruefe Abs. Grenzwert",   /*55  SE55  +S Trg > +S Abs     */
"-Aussch Trigger Grenzwert ist groesser als -Aussch Weg abs. Grenzwert",                       /*56  SE56  -R Trg > -R Abs     */
"+Aussch Trigger Grenzwert groesser als +Aussch Abs. Grenzwert",                       /*57  SE57  +R Trg > +R Abs     */
"+Pruefe Zeit Grenzwert und Zeitueberschreitung ueberschritten",                                            /*58  SE58  Timeout Conflict    */
"-Aussch Leistung Grenzwert und Spitzenleist. Abschaltung ueberschritten",                                  /*59  SE59  Cutoff Conflict     */
"SE60",                                                                               /*60  SE60  RESERVED            */
"SE61",                                                                               /*61  SE61  RESERVED            */
"SE62",                                                                               /*62  SE62  RESERVED            */
"SE63",                                                                               /*63  SE63  RESERVED            */




/** ----  SETUP GROUP 3  ---- **/


"SE64",                                                                               /*64  SE64  RESERVED            */
"+Aussch Leist. Grenzwert und Spitzenleist. Abschaltung ueberschritten",                                  /*65  SE65  Cutoff Conflict     */
"-Pruefe Leist. Grenzwert und Spitzenleist. Abschaltung ueberschritten",                                 /*66  SE66  Cutoff Conflict     */
"+Pruefe Leist. Grenzwert und Spitzenleist. Abschaltung ueberschritten",                                 /*67  SE67  Cutoff Conflict     */
"SE68",                                                                               /*68  SE68  Cutoff Conflict     */
"SE69",                                                                               /*69  SE69  Cutoff Conflict     */
"SE70",                                                                               /*70  SE70                      */
"SE71",                                                                               /*71  SE71                      */
"Triggerverzoegerung und Pretrigger sind ein",                                          /*72  SE72  Trig Delay & Pretrig*/
"Triggerkraft gleich oder groesser als Schweisskraft",                                  /*73  SE73  Trig > Weld Force   */
"+Aussch Zeit und -Pruefe Zeit Grenzwert ueberschritten",                                 /*74  SE74  Time S/R Limit Cross*/
"+Pruefe Zeit und -Aussch Zeit Grenzwert ueberschritten",                                 /*75  SE75  Time S/R Limit Cross*/
"+Aussch Zeit und +Pruefe Zeit Grenzwert ueberschritten",                                 /*76  SE76  Time S/R Limit Cross*/
"-Aussch Zeit Grenzwert und -Pruefe Zeit Grenzwert ueberschritten",                                 /*77  SE77  Time S/R Limit Cross*/
"+Aussch Energie und -Pruefe Energie Grenzwert ueberschritten",                             /*78  SE78  Eng S/R Limit Cross */
"+Pruefe Energie und -Aussch Energie Grenzwert ueberschritten",                             /*79  SE79  Eng S/R Limit Cross */
"+Aussch Energie und +Pruefe Energie Grenzwert ueberschritten",                             /*80  SE80  Eng S/R Limit Cross */
"-Aussch Energie Grenzwert und -Pruefe Energie Grenzwert ueberschritten",                             /*81  SE81  Eng S/R Limit Cross */
"+Aussch Spitzenleistung und -Pruefe Spitzenleistung Grenzwert ueberschritten",                       /*82  SE82  Pwr S/R Limit Cross */
"+Pruefe Spitzenleist. und -Aussch Spitzenleist. Grenzwert ueberschritten",                        /*83  SE83  Pwr S/R Limit Cross */
"+Aussch Spitzenleistung und +Pruefe Spitzenleistung Grenzwert ueberschritten",                       /*84  SE84  Pwr S/R Limit Cross */
"+Aussch Spitzenleist. Grenzwert und -Pruefe Spitzenleist. Grenzwert ueberschritten",                       /*85  SE85  Pwr S/R Limit Cross */
"+Aussch Abs. und -Pruefe Abs. Grenzwert ueberschritten",       /*86  SE86  Abs S/R Limit Cross */
"+Pruefe Abs. und -Aussch Abs. Grenzwert ueberschritten",       /*87  SE87  Abs S/R Limit Cross */
"+Aussch Abs. und +Pruefe Abs. Grenzwert ueberschritten",       /*88  SE88  Abs S/R Limit Cross */
"-Aussch Weg abs. Grenzwert und -Pruefe Weg abs. Grenzwert ueberschritten",       /*89  SE89  Abs S/R Limit Cross */
"+Aussch Rel. und -Pruefe Rel. Grenzwert ueberschritten",       /*90  SE90  Col S/R Limit Cross */
"+Pruefe Rel. und -Aussch Rel. Grenzwert ueberschritten",       /*91  SE91  Col S/R Limit Cross */
"SE92",                                                                               /*92  SE92  RESERVED        */
"SE93",                                                                               /*93  SE93  RESERVED        */
"SE94",                                                                               /*94  SE94  RESERVED        */
"SE95",                                                                               /*95  SE95  RESERVED        */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 4  ---- **/                                                       
                                                                                        
                                                                                        
"SE96",                                                                               /*96   SE96  RESERVED            */
"+Aussch Rel. und +Pruefe Rel. Grenzwert ueberschritten",       /*97   SE97  Col S/R Limit Cross */
"-Aussch Weg rel. Grenzwert und -Pruefe Weg rel. Grenzwert ueberschritten",       /*98   SE98  Col S/R Limit Cross */
"+Aussch Schweisskraft und -Pruefe Schweisskraft Grenzwert ueberschritten",               /*99   SE99  Frc S/R Limit Cross */
"+Pruefe Schweisskraft und -Aussch Schweisskraft Grenzwert ueberschritten",               /*100  SE100 Frc S/R Limit Cross */
"+Aussch Schweisskraft und +Pruefe Schweisskraft Grenzwert ueberschritten",               /*101  SE101 Frc S/R Limit Cross */
"-Aussch Schweisskraft Grenzwert und -Pruefe Schweisskraft Grenzwert ueberschritten",               /*102  SE102 Frc S/R Limit Cross */
"+Aussch Frequenz und -Pruefe Frequenz Grenzwert ueberschritten",                       /*103  SE103 Freq S/R Limit Cross*/
"+Pruefe Frequenz und -Aussch Frequenz Grenzwert ueberschritten",                       /*104  SE104 Freq S/R Limit Cross*/
"+Aussch Frequenz und +Pruefe Frequenz Grenzwert ueberschritten",                       /*105  SE105 Freq S/R Limit Cross*/
"-Aussch Frequenz Grenzwert und -Pruefe Frequenz Grenzwert ueberschritten",                       /*106  SE106 Freq S/R Limit Cross*/
"+Aussch Triggerweg und -Pruefe Triggerweg Grenzwert ueberschritten",         /*107  SE107 Trig S/R Limit Cross*/
"+Pruefe Triggerweg und -Aussch Triggerweg Grenzwert ueberschritten",         /*108  SE108 Trig S/R Limit Cross*/
"+Aussch Triggerweg und +Pruefe Triggerweg Grenzwert ueberschritten",         /*109  SE109 Trig S/R Limit Cross*/
"-Aussch Triggerweg Grenzwert und -Pruefe Triggerweg Grenzwert ueberschritten",         /*110  SE110 Trig S/R Limit Cross*/
"Kraftprofil Konflikt mit Weg rel. Abschaltung",                                          /*111  SE111 Force Step Cutoff   */
"Kraftprofil Konflikt mit Weg rel. Abschaltung",                                          /*112  SE112 Force Step Cutoff   */
"Kraftprofil Konflikt mit Weg rel. Abschaltung",                                          /*113  SE113 Force Step Cutoff   */
"Kraftprofil Konflikt mit Weg rel. Abschaltung",                                          /*114  SE114 Force Step Cutoff   */
"Kraftprofil Konflikt mit Weg rel. Abschaltung",                                          /*115  SE115 Force Step Cutoff   */
"Kraftprofil Konflikt mit Weg rel. Abschaltung",                                          /*116  SE116 Force Step Cutoff   */
"Kraftprofil Konflikt mit Weg rel. Abschaltung",                                          /*117  SE117 Force Step Cutoff   */
"Kraftprofil Konflikt mit Weg rel. Abschaltung",                                          /*118  SE118 Force Step Cutoff   */
"Energieausgleich Min und Max Einstellung ueberschritten",                           /*119  SE119 Energy Comp Crossed */
"Fehlendes Teil Min und Max Einstellung ueberschritten",                                  /*120  SE120 Missing Part Crossed*/
"Pretriggerweg und Kraftprofil bei Weg abs. Grenzwert ueberschritten",              /*121  SE121 Pretrigger Conflict */
"Pretriggerweg und Amplitudenprofil bei Weg abs. Grenzwert ueberschritten",          /*122  SE122 Pretrigger Conflict */
"Pretriggerweg und -Aussch Weg abs. Grenzwert ueberschritten",                    /*123  SE123 Pretrigger Conflict */
"SE124",                                                                              /*124  SE124 RESERVED            */
"SE125",                                                                              /*125  SE125 RESERVED            */
"SE126",                                                                              /*126  SE126 RESERVED            */
"SE127",                                                                              /*127  SE127 RESERVED            */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 5  ---- **/


"SE128",                                                                              /*128  SE128 RESERVED            */
"Pretriggerweg und -Pruefe Weg abs. Grenzwert ueberschritten",                   /*129  SE129 Pretrigger Conflict */
"Pretriggerweg und +Aussch Weg abs. Grenzwert ueberschritten",                    /*130  SE130 Pretrigger Conflict */
"Pretriggerweg und +Pruefe Weg abs. Grenzwert ueberschritten",                   /*131  SE131 Pretrigger Conflict */
"Pretriggerweg und +Aussch Triggerweg Grenzwert ueberschritten",                     /*132  SE132 Pretrigger Conflict */
"Pretriggerweg und +Pruefe Triggerweg Grenzwert ueberschritten",                    /*133  SE133 Pretrigger Conflict */
"Pretriggerweg und -Aussch Triggerweg Grenzwert ueberschritten",                     /*134  SE134 Pretrigger Conflict */
"Pretriggerweg und -Pruefe Triggerweg Grenzwert ueberschritten",                    /*135  SE135 Pretrigger Conflict */
"Pretriggerweg und Weg abs. Abschaltung ueberschritten",                           /*136  SE136 Pretrigger Conflict */
"Pretriggerweg und Weg abs. ueberschritten",                                 /*137  SE137 Pretrigger Conflict */
"Abs. Abschaltung und -Aussch Abs. Grenzwert ueberschritten",               /*138  SE138 Abs Cutoff Conflict */
"Abs. Abschaltung und -Aussch Triggerweg Grenzwert ueberschritten",                /*139  SE139 Abs Cutoff Conflict */
"Abs. Abschaltung und -Pruefe Abs. Grenzwert ueberschritten",              /*140  SE140 Abs Cutoff Conflict */
"Abs. Abschaltung und -Pruefe Triggerweg Grenzwert ueberschritten",               /*141  SE141 Abs Cutoff Conflict */
"Abs. Abschaltung und +Aussch Abs. Grenzwert ueberschritten",               /*142  SE142 Abs Cutoff Conflict */
"Abs. Abschaltung und +Aussch Triggerweg Grenzwert ueberschritten",                /*143  SE143 Abs Cutoff Conflict */
"Abs. Abschaltung und +Pruefe Abs. Grenzwert ueberschritten",              /*144  SE144 Abs Cutoff Conflict */
"Abs. Abschaltung und +Pruefe Triggerweg Grenzwert ueberschritten",               /*145  SE145 Abs Cutoff Conflict */
"Fehlendes Teil Max Weg und -Aussch Weg abs. Grenzwert ueberschritten",          /*146  SE146 Missing Part Conflct*/
"Fehlendes Teil Min Weg und -Aussch Weg abs. Grenzwert ueberschritten",          /*147  SE147 Missing Part Conflct*/
"Fehlendes Teil Max Weg und -Aussch Triggerweg Grenzwert ueberschritten",           /*148  SE148 Missing Part Conflct*/
"Fehlendes Teil Min Weg und -Aussch Triggerweg Grenzwert ueberschritten",           /*149  SE149 Missing Part Conflct*/
"Fehlendes Teil Min Weg und -Pruefe Weg abs. Grenzwert ueberschritten",         /*150  SE150 Missing Part Conflct*/
"Fehlendes Teil Max Weg und -Pruefe Triggerweg Grenzwert ueberschritten",          /*151  SE151 Missing Part Conflct*/
"Fehlendes Teil Min Weg und -Pruefe Triggerweg Grenzwert ueberschritten",          /*152  SE152 Missing Part Conflct*/
"Fehlendes Teil Max Weg und +Aussch Weg abs. Grenzwert ueberschritten",          /*153  SE153 Missing Part Conflct*/
"Fehlendes Teil Min Weg und +Aussch Weg abs. Grenzwert ueberschritten",          /*154  SE154 Missing Part Conflct*/
"Fehlendes Teil Max Weg und +Aussch Triggerweg Grenzwert ueberschritten",           /*155  SE155 Missing Part Conflct*/
"SE156",                                                                              /*156  SE156 RESERVED            */
"SE157",                                                                              /*157  SE157 RESERVED            */
"SE158",                                                                              /*158  SE158 RESERVED            */
"SE159",                                                                              /*159  SE159 RESERVED            */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 6  ---- **/


"SE160",                                                                              /*160  SE160 RESERVED            */
"Fehlendes Teil Min Weg und +Aussch Triggerweg Grenzwert ueberschritten",           /*161  SE161 Missing Part Conflct*/
"Fehlendes Teil Max Weg und +Pruefe Weg abs. Grenzwert ueberschritten",         /*162  SE162 Missing Part Conflct*/
"Fehlendes Teil Min Weg und +Pruefe Weg abs. Grenzwert ueberschritten",         /*163  SE163 Missing Part Conflct*/
"Fehlendes Teil Max Weg und +Pruefe Triggerweg Grenzwert ueberschritten",          /*164  SE164 Missing Part Conflct*/
"Fehlendes Teil Min Weg und +Pruefe Triggerweg Grenzwert ueberschritten",          /*165  SE165 Missing Part Conflct*/
"Fehlendes Teil Min Weg und Weg abs. Abschaltung ueberschritten",                 /*166  SE166 Missing Part Conflct*/
"Fehlendes Teil Max Weg und Weg abs. Abschaltung ueberschritten",                 /*167  SE167 Missing Part Conflct*/
"Fehlendes Teil Min Weg und Weg abs. Einstellung ueberschritten",                /*168  SE168 Missing Part Conflct*/
"Fehlendes Teil Max Weg und Weg abs. Einstellung ueberschritten",                /*169  SE169 Missing Part Conflct*/
"Energieausgleich Min Wert und +Aussch Energie Grenzwert ueberschritten",                  /*170  SE170 Energy Comp Conflict*/
"Energieausgleich Min Wert und +Pruefe Energie Grenzwert ueberschritten",                 /*171  SE171 Energy Comp Conflict*/
"Energieausgleich Max Wert und -Aussch Energie Grenzwert ueberschritten",                  /*172  SE172 Energy Comp Conflict*/
"Energieausgleich Max Wert und -Pruefe Energie Grenzwert ueberschritten",                 /*173  SE173 Energy Comp Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*174  SE174 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*175  SE175 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*176  SE176 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*177  SE177 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*178  SE178 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*179  SE179 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*180  SE180 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*181  SE181 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*182  SE182 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*183  SE183 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*184  SE184 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*185  SE185 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*186  SE186 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*187  SE187 Rapid Trav. Conflict*/
"SE188",                                                                              /*188  SE188 RESERVED            */
"SE189",                                                                              /*189  SE189 RESERVED            */
"SE190",                                                                              /*190  SE190 RESERVED            */
"SE191",                                                                              /*191  SE191 RESERVED            */



/** ----  SETUP GROUP 7  ---- **/

                                                                                      
"SE192",                                                                              /*192 SE192 RESERVED            */
"Eilgang Einstellung Konflikt",                                                      /*193 SE193 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*194 SE194 Rapid Trav. Conflict*/
"Eilgang Einstellung Konflikt",                                                      /*195 SE195 Rapid Trav. Conflict*/
"Haltekraft und Grenzwert ueberschritten",                                                      /*196 SE196 Hold Force Conflict */
"Haltekraft und Grenzwert ueberschritten",                                                      /*197 SE197 Hold Force Conflict */
"Haltekraft und Grenzwert ueberschritten",                                                      /*198 SE198 Hold Force Conflict */
"Haltekraft und Grenzwert ueberschritten",                                                      /*199 SE199 Hold Force Conflict */
"Kraft A und Grenzwert ueberschritten",                                                         /*200 SE200 Force/Lmt Conflict  */
"Kraft A und Grenzwert ueberschritten",                                                         /*201 SE201 Force/Lmt Conflict  */
"Kraft A und Grenzwert ueberschritten",                                                         /*202 SE202 Force/Lmt Conflict  */
"Kraft A und Grenzwert ueberschritten",                                                         /*203 SE203 Force/Lmt Conflict  */
"Kraft B und Grenzwert ueberschritten",                                                         /*204 SE204 Force/Lmt Conflict  */
"Kraft B und Grenzwert ueberschritten",                                                         /*205 SE205 Force/Lmt Conflict  */
"Kraft B und Grenzwert ueberschritten",                                                         /*206 SE206 Force/Lmt Conflict  */
"Kraft B und Grenzwert ueberschritten",                                                         /*207 SE207 Force/Lmt Conflict  */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*208 SE208 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*209 SE209 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*210 SE210 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*211 SE211 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*212 SE212 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*213 SE213 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*214 SE214 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*215 SE215 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*216 SE216 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*217 SE217 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*218 SE218 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*219 SE219 Force Step Conflict */
"SE220",                                                                              /*220 SE220 RESERVED            */
"SE221",                                                                              /*221 SE221 RESERVED            */
"SE222",                                                                              /*222 SE222 RESERVED            */
"SE223",                                                                              /*223 SE223 RESERVED            */



        
/** ----  SETUP GROUP 8  ---- **/

                                                                              
"SE224",                                                                              /*224  SE224 RESERVED            */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*225  SE225 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*226  SE226 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*227  SE227 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*228  SE228 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*229  SE229 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*230  SE230 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*231  SE231 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*232  SE232 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*233  SE233 Force Step Conflict */
"Kraftprofil Konflikt mit Grenzwert",                                                   /*234  SE234 Force Step Conflict */
"Kraftprofil Konflikt mit Weg abs. Einstellung",                                /*235  SE235 Force Step Conflict */
"Kraftprofil Konflikt mit Pretriggerweg Einstellung",                              /*236  SE236 Force Step Conflict */
"Kraftprofil Konflikt mit Weg rel. Abschaltung",                                 /*237  SE237 Force Step Conflict */
"Kraftprofil Konflikt mit Trigger-Abschaltungseinstellung",                                   /*238  SE238 Force Step Conflict */
"Kraftprofil Konflikt mit Spitzenleist. Abschaltung",                                        /*239  SE239 Force Step Conflict */
"Kraftprofil Konflikt mit Spitzenleist. Einstellung",                                       /*240  SE240 Force Step Conflict */
"Kraftprofil Konflikt mit Energieeinstellung",                                           /*241  SE241 Force Step Conflict */
"Kraftprofil Konflikt mit Energieausgleich",                                      /*242  SE242 Force Step Conflict */
"Kraftprofil Konflikt mit Schweisszeit",                                                /*243  SE243 Force Step Conflict */
"Kraft Profil Konflikt mit Amplituden Einstellung bei Amplitude",                           /*244  SE244 Amp/F Step Conflict */
"Schweisskraft A nicht erreichbar, da Einlassdruck zu niedrig",                      /*245  SE245 Weld Force>Pressure */
"Schweisskraft B nicht erreichbar, da Einlassdruck zu niedrig",                      /*246  SE246 Force B>Pressure    */
"Haltekraft kann nicht erreicht werden, da Einlassdruck niedrig",                        /*247  SE247 Hold Force>Pressure */
"Einlassdruck ist zu hoch fuer festgelegte Schweisskraft",                                /*248  SE248 Pressure>Weld Force */
"Einlassdruck ist zu hoch fuer festgelegte Schweisskraft B",                              /*249  SE249 Pressure>Force B    */
"Einlassdruck ist zu hoch fuer festgelegte Schweisskraft",                                /*250  SE250 Pressure>Hold Force */
"Triggerkraft Konflikt mit Pruefe Grenzwert",                                        /*251  SE251 Trig Force Conflict */
"SE252",                                                                              /*252  SE252 RESERVED            */
"SE253",                                                                              /*253  SE253 RESERVED            */
"SE254",                                                                              /*254  SE254 RESERVED            */
"SE255",                                                                              /*255  SE255 RESERVED            */
 



/** ----  SETUP GROUP 9  ---- **/

                                                                                     
"SE156",                                                                              /*256 SE256 RESERVED            */
"Triggerkraft Konflikt mit Aussch Grenzwert",                                         /*257 SE257 Trig Force Conflict */
"SE258",                                                                              /*258 SE258                     */
"Diese Voreinstellung erfordert eine Wegmessung",                                             /*259 SE259 Encoder Required    */
"SE260",                                                                              /*260 SE260                     */
"SE261",                                                                              /*261 SE261                     */
"SE262",                                                                              /*262 SE262                     */
"SE263",                                                                              /*263 SE263                     */
"Energieausgleich Min Wert und -Aussch Energie Grenzwert ueberschritten",                 /*264 SE264 Energy Comp Conflict*/
"Energieausgleich Min Wert und -Pruefe Energie Grenzwert ueberschritten",                /*265 SE265 Energy Comp Conflict*/
"Energieausgleich Max Wert und +Aussch Energie Grenzwert ueberschritten",                 /*266 SE266 Energy Comp Conflict*/
"Energieausgleich Max Wert und +Pruefe Energie Grenzwert ueberschritten",                /*267 SE267 Energy Comp Conflict*/
"Merkmal(e) nicht verfuegbar in diesem Modell.",                                /*268 SE268 Invalid Preset      */
"Ein undefinierter Parameter wurde fur diesen Takt angefordert.",                       /*269 SE269 Undefined Preset    */
"",                                                                                   /*270 SE270 Printer Offline     */
"-Pruefe Trigger Grenzwert und +Pruefe Weg abs. Grenzwert ueberschritten",                /*271 SE271 -S Trg > +S Abs     */
"-Pruefe Trigger Grenzwert und +Aussch Weg abs. Grenzwert ueberschritten",                 /*272 SE272 -S Trg > +R Abs     */
"-Aussch Trigger Grenzwert und +Pruefe Weg abs. Grenzwert ueberschritten",                 /*273 SE273 -R Trg > +S Abs     */
"-Aussch Trigger Grenzwert und +Aussch Weg abs. Grenzwert ueberschritten",                  /*274 SE274 -R Trg > +R Abs     */
"-Pruefe Trigger Grenzwert und Weg abs. ueberschritten",                               /*275 SE275 -S Trg > Abs        */
"-Aussch Trigger Grenzwert und Weg abs. ueberschritten",                                /*276 SE276 -R Trg > Abs        */
"SE277",                                                                              /*277 SE277 -R Trg > Abs Cutoff */
"SE278",                                                                              /*278 SE278                     */
"SE279",                                                                              /*279 SE279                     */
"SE280",                                                                              /*280 SE280                     */
"SE281",                                                                              /*281 SE281                     */
"SE282",                                                                              /*282 SE282                     */
"SE283",                                                                              /*283 SE283                     */
"SE284",                                                                              /*284 SE284 RESERVED            */
"SE285",                                                                              /*285 SE285 RESERVED            */
"SE286",                                                                              /*286 SE286 RESERVED            */
"SE287",                                                                              /*287 SE287 RESERVED            */
 



/** ----  SETUP GROUP 10  ---- **/

                                                                                     
"SE288",                                                                              /*288 SE288 RESERVED            */
"Ext Trigger Verzoegerung und Vorausloesung an",                                      /*289 SE289                     */
"Eingang Ext Trigger Verzoegerung nicht definiert ",                                  /*290 SE290                     */
"weder externes Magnetventil noch Eingang definiert",                                 /*291 SE291                     */
"SE292",                                                                              /*292 SE292                     */
"SE293",                                                                              /*293 SE293                     */
"SE294",                                                                              /*294 SE294                     */
"SE295",                                                                              /*295 SE295                     */
"Ext Signal Setup",                                                                   /*296 SE296                     */
"SE297",                                                                              /*297 SE297                     */
"SE298",                                                                              /*298 SE298                     */
"SE299",                                                                              /*299 SE299                     */
"SE300",                                                                              /*300 SE300                     */
"SE301",                                                                              /*301 SE301                     */
"SE302",                                                                              /*302 SE302                     */
"SE303",                                                                              /*303 SE303                     */
"SE304",                                                                              /*304 SE304                     */
"SE305",                                                                              /*305 SE305                     */
"SE306",                                                                              /*306 SE306                     */
"SE307",                                                                              /*307 SE307                     */
"SE308",                                                                              /*308 SE308                     */
"SE309",                                                                              /*309 SE309                     */
"SE310",                                                                              /*310 SE310                     */
"SE311",                                                                              /*311 SE311                     */
"SE312",                                                                              /*312 SE312                     */
"SE313",                                                                              /*313 SE313                     */
"SE314",                                                                              /*314 SE314                     */
"SE315",                                                                              /*315 SE315                     */
"SE316",                                                                              /*316 SE316 RESERVED            */
"SE317",                                                                              /*317 SE317 RESERVED            */
"SE318",                                                                              /*318 SE318 RESERVED            */
"SE319",                                                                              /*319 SE319 RESERVED            */

};

//OmniLingua - End German insertion here
//OmniLingua - Start Spanish insertion here

const STR *const Alarm1Spn[] = {


/**------------------------------------------------**
 **        This group is the Setup Alarms          **
 **------------------------------------------------**/


/** ----  SETUP GROUP 1  ---- **/


"SE0",                                                                                /*0   SE0   RESERVED            */
"Lte Sospech Tiempo +- Rebasado",                                                       /*1   SE1   RESERVED            */
"Lte Rechzo Tiempo +- Rebasado",                                                        /*2   SE2   +-Time Limit Crossed*/
"Lte Sospech Energia +- Rebasado",                                                     /*3   SE3   +-Time Limit Crossed*/
"+-Cruce lim rechz energia",                                                      /*4   SE4   +-Eng Limit Crossed */
"Lte Sospch +- Potencia Rebasado",                                                      /*5   SE5   +-Eng Limit Crossed */
"Lte Rchzo +- Potencia Rebasado",                                                       /*6   SE6   +-Pwr Limit Crossed */
"Lte Sospch +- Frecuencia Rebasado",                                                  /*7   SE7   +-Pwr Limit Crossed */
"Lte Rchzo +- Frecuencia Rebasado",                                                   /*8   SE8   +-Freq Limit Crossed*/
"Lte Sospch +- Distancia Absoluta Rebasado",                                          /*9   SE9   +-Freq Limit Crossed*/
"Lte Rchzo +- Distancia Absoluta Rebasado",                                           /*10  SE10  +-Abs Limit Crossed */
"Lte Sospech +- Distancia Colapso Rebasado",                                          /*11  SE11  +-Abs Limit Crossed */
"Lte Rechzo +- Distancia Colapso Rebasado",                                           /*12  SE12  +-Col Limit Crossed */
"+-Cruce lim sospch fuerza sold",                                             /*13  SE13  +-Col Limit Crossed */
"+-Cruce lim rechz fuerza sold",                                              /*14  SE14  +-Frc Limit Crossed */
"Paso Amplitud en conflcto con Tiempo Soldura",                                            /*15  SE15  +-Frc Limit Crossed */
"Paso Amplitud en conflto con Lte Rechzo+ Pico Potencia",                             /*16  SE16  Amp Step Conflict   */
"Paso Amplitud en conflto con Lte Sospech+ Pico Potencia",                             /*17  SE17  Amp Step Conflict   */
"Paso Amplitud en conflto con Lte Rechazo+ Energia",                                 /*18  SE18  Amp Step Conflict   */
"Paso Amplitud en conflto con Lte Sospech+ Energia",                                /*19  SE19  Amp Step Conflict   */
"Paso Amplitud en conflto con Lte Rechazo+ Distancia Absoluta",                      /*20  SE20  Amp Step Conflict   */
"Paso Amplitud en conflto con Lte Sospecha+ Distancia Absoluta",                     /*21  SE21  Amp Step Conflict   */
"SE22",                                                                               /*22  SE22  Amp Step Conflict   */
"SE23",                                                                               /*23  SE23  Amp Step Conflict   */
"Paso Amplitud en conflto con Lte Rechazo- Distancia Disparo",                       /*24  SE24  Amp Step Conflict   */
"Paso Amplitud en conflto con Lte Sospech- Distancia Disparo",                      /*25  SE25  Amp Step Conflict   */
"Paso Amplitud en conflto con Lte Rechazo+ Distancia Disparo",                       /*26  SE26  Amp Step Conflict   */
"Paso Amplitud en conflto con Lte Sospech+ Distancia Disparo",                      /*27  SE27  Amp Step Conflict   */
"SE28",                                                                               /*28  SE28  RESERVED            */
"SE29",                                                                               /*29  SE29  RESERVED            */
"SE30",                                                                               /*30  SE30  RESERVED            */
"SE31",                                                                               /*31  SE31  RESERVED            */
                                                                                        
                                                                                        
                                                                                        
                                                                                        
/** ----  SETUP GROUP 2  ---- **/


"SE32",                                                                               /*32  SE32  RESERVED            */
"Paso Amplitud a Distancia Absoluta en conflto con Distancia Predisparo",             /*33  SE33  Amp Step Conflict   */
"Paso Amplitud a Distancia Absoluta en conflto con Corte Distancia Absoluta",        /*34  SE34  Amp Step Conflict   */
"Paso amplitud en corte dist absoluta en confl con Abortar ciclo parte perd",  /*35  SE35  Amp Step Conflict   */
"Paso amplitud en corte dist absoluta en confl con Abortar ciclo parte perd",  /*36  SE36  Amp Step Conflict   */
"Paso Amplitud a Potencia en conflto con Ajuste Pico Potencia",                          /*37  SE37  Amp Step Conflict   */
"Paso amplitud en Energ en confl con compens energia",                        /*38  SE38  Amp Step Conflict   */
"Paso Amplitud a Fuerza en conflto con Ajuste Fuerza",                               /*39  SE39  Amp Step Conflict   */
"Paso Amplitud a Potencia en conflto con Corte Pico Potencia",                           /*40  SE40  Amp Step Conflict   */
"Paso Amplitud a Colapso en conflto con Corte Distancia Colapso",                 /*41  SE41  Amp Step Conflict   */
"Paso Amplitud a Colapso en conflto con Distancia Colapso",                        /*42  SE42  Amp Step Conflict   */
"Paso Amplitud a Tiempo en conflto con Cta atras",                                      /*43  SE43  Amp Step Conflict   */
"Lte Rechzo+- Distancia Disparo Rebasado",                                            /*44  SE44  +-Trig Limit Crossed*/
"Lte Sospch+- Distancia Disparo Rebasado",                                           /*45  SE45  +-Trig Limit Crossed*/
"The preset recalled is either clear or not available for control level.",            /*46  SE46  Preset Not Available*/
"Paso Amplitud a Distancia Absoluta en conflto con Ajuste Distancia Absoluta",       /*47  SE47  Amp Step Conflict   */
"Paso Amplitud a Energia en conflto con Ajuste Energia",                             /*48  SE48  Amp Step Conflict   */
"Lte Rchzo+ Tiempo y Cta atras Rebasados",                                             /*49  SE49  Timeout Conflict    */
"Lte Sopch-Tiempo y Cta atras Rebasados",                                            /*50  SE50  Timeout Conflict    */
"Lte Rchzo- Tiempo y Cta atras Rebasados",                                             /*51  SE51  Timeout Conflict    */
"Paso Amplitud en Fuerza mayor o igual que todos los Valores de Fuerza",                  /*52  SE52  Amp Step on Force   */
"Paso amplitud en Amplitud igual o mayor que todos los val de amp",                /*53  SE53  Force Step on Amp   */
"-Sospch lim disp es mayor que +lim absoluto sospch ",                     /*54  SE54  -S Trg > -S Abs     */
"+Sospch lim dist disp mayor que +lim dist absoluta sospch",   /*55  SE55  +S Trg > +S Abs     */
"-Lim disp rechz mayor que -lim absoluto rechz",                       /*56  SE56  -R Trg > -R Abs     */
"+Lim disp rechz mayor que +lim absoluto rechz",                       /*57  SE57  +R Trg > +R Abs     */
"Lte Sospech+ Tiempo y Cta atras Rebasados",                                            /*58  SE58  Timeout Conflict    */
"Lte Rechazo- Potencia y Corte Pico Potencia Rebasados",                                  /*59  SE59  Cutoff Conflict     */
"SE60",                                                                               /*60  SE60  RESERVED            */
"SE61",                                                                               /*61  SE61  RESERVED            */
"SE62",                                                                               /*62  SE62  RESERVED            */
"SE63",                                                                               /*63  SE63  RESERVED            */




/** ----  SETUP GROUP 3  ---- **/


"SE64",                                                                               /*64  SE64  RESERVED            */
"Lte Rechazo+ Potencia y Corte Pico Potencia Rebasados",                                  /*65  SE65  Cutoff Conflict     */
"Lte Sospech- Potencia y Corte Pico Potencia Rebasados",                                 /*66  SE66  Cutoff Conflict     */
"Lte Sospech+ Potencia y Corte Pico Potencia Rebasados",                                 /*67  SE67  Cutoff Conflict     */
"SE68",                                                                               /*68  SE68  Cutoff Conflict     */
"SE69",                                                                               /*69  SE69  Cutoff Conflict     */
"SE70",                                                                               /*70  SE70                      */
"SE71",                                                                               /*71  SE71                      */
"Retardo Disparo y Predisparo conectados",                                          /*72  SE72  Trig Delay & Pretrig*/
"Fuerza Disparo mayor o igual que Fuerza Soldadura",                                  /*73  SE73  Trig > Weld Force   */
"Lte Rechzo+ Tiempo y Lte Sospech- Tiempo Rebasados",                                 /*74  SE74  Time S/R Limit Cross*/
"+Sospch lim tiem y -cruce lim tiem rechz",                                 /*75  SE75  Time S/R Limit Cross*/
"Lte Rechzo+ Tiempo y Lte Sospech+ Tiempo Rebasados",                                 /*76  SE76  Time S/R Limit Cross*/
"Lte Rechzo- Tiempo y Lte Sospech- Tiempo Rebasados",                                 /*77  SE77  Time S/R Limit Cross*/
"Lte Rechazo+ Energia y Lte Sospech- Energia Rebasados",                             /*78  SE78  Eng S/R Limit Cross */
"Lte Sospech+ Energia y Lte Rechazo- Energia Rebasados",                             /*79  SE79  Eng S/R Limit Cross */
"Lte Rechazo+ Energia y Lte Sospech+ Energia Rebasados",                             /*80  SE80  Eng S/R Limit Cross */
"Lte Rechazo- Energia y Lte Sospech- Energia Rebasados",                             /*81  SE81  Eng S/R Limit Cross */
"+Rechz lim potenc pico y -Sospch cruce lim pot pico",                      /*82  SE82  Pwr S/R Limit Cross */
"+Sospch lim pot pico y -Rechz cruce lim pot pico",                       /*83  SE83  Pwr S/R Limit Cross */
"+Rechz lim pot pico y +Sospch cruce lim pot pico",                       /*84  SE84  Pwr S/R Limit Cross */
"-Rechz lim pot pico y -Sospch cruce lim pot pico",                       /*85  SE85  Pwr S/R Limit Cross */
"Lte Rechazo+ Distancia Absoluta y Lte Sospech- Distancia Absoluta Rebasados",       /*86  SE86  Abs S/R Limit Cross */
"Lte Sospech+ Distancia Absoluta y Lte Rechazo- Distancia Absoluta Rebasados",       /*87  SE87  Abs S/R Limit Cross */
"Lte Rechazo+ Distancia Absoluta y Lte Sospech+ Distancia Absoluta Rebasados",       /*88  SE88  Abs S/R Limit Cross */
"Lte Rechazo- Distancia Absoluta y Lte Sospech- Distancia Absoluta Rebasados",       /*89  SE89  Abs S/R Limit Cross */
"+Rechz lim dist colaps y -Sospch cruce lim distancia colaps",        /*90  SE90  Col S/R Limit Cross */
"Lte Sospech+ Distancia Colapso y Lte Rechazo- Distancia Colapso Rebasados",       /*91  SE91  Col S/R Limit Cross */
"SE92",                                                                               /*92  SE92  RESERVED        */
"SE93",                                                                               /*93  SE93  RESERVED        */
"SE94",                                                                               /*94  SE94  RESERVED        */
"SE95",                                                                               /*95  SE95  RESERVED        */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 4  ---- **/                                                       
                                                                                        
                                                                                        
"SE96",                                                                               /*96   SE96  RESERVED            */
"Lte Rechazo+ Distancia Colapso y Lte Sospech+ Distancia Colapso Rebasados",       /*97   SE97  Col S/R Limit Cross */
"Lte Rechazo- Distancia Colapso y Lte Sospech- Distancia Colapso Rebasados",       /*98   SE98  Col S/R Limit Cross */
"Lte Rechazo+ Fuerza Soldadura y Lte Sospech- Fuerza Soldadura Rebasdos",               /*99   SE99  Frc S/R Limit Cross */
"Lte Sospech+ Fuerza Soldadura y Lte Rechazo- Fuerza Soldadura Rebasdos",               /*100  SE100 Frc S/R Limit Cross */
"Lte Rechazo+ Fuerza Soldadura y Lte Sospech+ Fuerza Soldadura Rebasdos",               /*101  SE101 Frc S/R Limit Cross */
"Lte Rechazo- Fuerza Soldadura y Lte Sospech- Fuerza Soldadura Rebasdos",               /*102  SE102 Frc S/R Limit Cross */
"Lte Rechazo+ Frecuencia y Lte Sospech- Frecuencia Rebasados",                       /*103  SE103 Freq S/R Limit Cross*/
"+Sospch lim frecuencia y -Rechz cruce lim frecuencia",                       /*104  SE104 Freq S/R Limit Cross*/
"Lte Rechazo+ Frecuencia y Lte Sospech+ Frecuencia Rebasados",                       /*105  SE105 Freq S/R Limit Cross*/
"Lte Rechazo- Frecuencia y Lte Sospech- Frecuencia Rebasados",                       /*106  SE106 Freq S/R Limit Cross*/
"Lte Rechazo+ Distancia Disparo y Lte Sospech- Distancia Disparo Rebasados",         /*107  SE107 Trig S/R Limit Cross*/
"Lte Sospech+ Distancia Disparo y Lte Rechazo- Distancia Disparo Rebasados",         /*108  SE108 Trig S/R Limit Cross*/
"Lte Rechazo+ Distancia Disparo y Lte Sospech+ Distancia Disparo Rebasados",         /*109  SE109 Trig S/R Limit Cross*/

"Lte Rechazo- Distancia Disparo y Lte Sospech- Distancia Disparo Rebasados",         /*110  SE110 Trig S/R Limit Cross*/
"Paso Fuerza en conflto con Corte Colapso",                                          /*111  SE111 Force Step Cutoff   */
"Paso Fuerza en conflto con Corte Colapso",                                          /*112  SE112 Force Step Cutoff   */
"Paso Fuerza en conflto con Corte Colapso",                                          /*113  SE113 Force Step Cutoff   */
"Paso Fuerza en conflto con Corte Colapso",                                          /*114  SE114 Force Step Cutoff   */
"Paso Fuerza en conflto con Corte Colapso",                                          /*115  SE115 Force Step Cutoff   */
"Paso Fuerza en conflto con Corte Colapso",                                          /*116  SE116 Force Step Cutoff   */
"Paso Fuerza en conflto con Corte Colapso",                                          /*117  SE117 Force Step Cutoff   */
"Paso Fuerza en conflto con Corte Colapso",                                          /*118  SE118 Force Step Cutoff   */
"Ajustes Max y Min de Compensacion de Energia Rebasados",                           /*119  SE119 Energy Comp Crossed */
"Ajusts Max y Min de Pieza Perdida Rebasados",                                  /*120  SE120 Missing Part Crossed*/
"Distancia Predisparo y Paso Fuerza en Lte Distancia Absoluta Rebasdos",              /*121  SE121 Pretrigger Conflict */
"Distancia Predisparo y Paso Amplitud en Lte Distancia Absoluta Rebasados",          /*122  SE122 Pretrigger Conflict */
"Distancia Predisparo y Lte Rechazo- Distancia Absoluta Rebasdos",                    /*123  SE123 Pretrigger Conflict */
"SE124",                                                                              /*124  SE124 RESERVED            */
"SE125",                                                                              /*125  SE125 RESERVED            */
"SE126",                                                                              /*126  SE126 RESERVED            */
"SE127",                                                                              /*127  SE127 RESERVED            */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 5  ---- **/


"SE128",                                                                              /*128  SE128 RESERVED            */
"Distancia Predisparo y Lte Sospech- Distancia Absoluta Rebasdos",                   /*129  SE129 Pretrigger Conflict */
"Distancia Predisparo y Lte Rechazo+ Distancia Absoluta Rebasdos",                    /*130  SE130 Pretrigger Conflict */
"Distancia Predisparo y Lte Sospech+ Distancia Absoluta Rebasdos",                   /*131  SE131 Pretrigger Conflict */
"Distancia Predisparo y Lte Rechazo+ Distancia Disparo Rebasdos",                     /*132  SE132 Pretrigger Conflict */
"Distancia Predisparo y Lte Sospech+ Distancia Disparo Rebasdos",                    /*133  SE133 Pretrigger Conflict */
"Distancia Predisparo y Lte Rechazo- Distancia Disparo Rebasdos",                     /*134  SE134 Pretrigger Conflict */
"Distancia Predisparo y Lte Sospech- Distancia Disparo Rebasdos",                    /*135  SE135 Pretrigger Conflict */
"Distancia predisp y cruce distancia corte absoluta",                            /*136  SE136 Pretrigger Conflict */
"Distancia Predisparo y Distancia Absoluta Rebasadas",                                  /*137  SE137 Pretrigger Conflict */
"Distancia Absoluta Corte y Lte Rechazo- Distancia Absoluta Rebasados",               /*138  SE138 Abs Cutoff Conflict */
"Distancia Absoluta Corte y Lte Rechazo- Distancia Disparo Rebasados",                /*139  SE139 Abs Cutoff Conflict */
"Distancia Absoluta Corte y Lte Sospech- Distancia Absoluta Rebasados",              /*140  SE140 Abs Cutoff Conflict */
"Distancia Absoluta Corte y Lte Sospech- Distancia Disparo Rebasados",               /*141  SE141 Abs Cutoff Conflict */
"Distancia Absoluta Corte y Lte Rechazo+ Distancia Absoluta Rebasados",               /*142  SE142 Abs Cutoff Conflict */
"Distancia Absoluta Corte y Lte Rechazo+ Distancia Disparo Rebasados",                /*143  SE143 Abs Cutoff Conflict */
"Corte distancia absoluta y +Sospch cruce lim distancia absoluta",              /*144  SE144 Abs Cutoff Conflict */
"Corte distancia absoluta y +Sospch cruce lim distancia disp",               /*145  SE145 Abs Cutoff Conflict */
"Distancia max parte perdida y -Rechz cruce lim distancia absoluta",          /*146  SE146 Missing Part Conflct*/
"Distancia Min Pieza Perdida y Lte Rechazo- Distancia Absoluta Rebasados",          /*147  SE147 Missing Part Conflct*/
"Distancia Max Pieza Perdida y Lte Rechazo- Distancia Disparo Rebasados",           /*148  SE148 Missing Part Conflct*/
"Distancia min parte perdida y -Rechz cruce lim distancia disp",           /*149  SE149 Missing Part Conflct*/
"Distancia min parte perdida y -Sospch cruce lim distancia absoluta",         /*150  SE150 Missing Part Conflct*/
"Distancia Max Pieza Perdida y Lte Sospech- Distancia Disparo Rebasados",          /*151  SE151 Missing Part Conflct*/
"Distancia Min Pieza Perdida y Lte Sospech- Distancia Disparo Rebasados",          /*152  SE152 Missing Part Conflct*/
"Distancia min parte perdida y +Rechz cruce lim distancia absoluta",          /*153  SE153 Missing Part Conflct*/
"Distancia min parte perdida y +Rechz cruce lim distancia absoluta",          /*154  SE154 Missing Part Conflct*/
"Distancia Max Pieza Perdida y Lte Rechazo+ Distancia Disparo Rebasados",           /*155  SE155 Missing Part Conflct*/
"SE156",                                                                              /*156  SE156 RESERVED            */
"SE157",                                                                              /*157  SE157 RESERVED            */
"SE158",                                                                              /*158  SE158 RESERVED            */
"SE159",                                                                              /*159  SE159 RESERVED            */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 6  ---- **/


"SE160",                                                                              /*160  SE160 RESERVED            */
"Distancia Min Pieza Perdida y Lte Rechazo+ Distancia Disparo Rebasados",           /*161  SE161 Missing Part Conflct*/
"Distancia Max Pieza Perdida y Lte Sospech+ Distancia Absoluta Rebasados",         /*162  SE162 Missing Part Conflct*/
"Distancia Min Pieza Perdida y Lte Sospech+ Distancia Absoluta Rebasados",         /*163  SE163 Missing Part Conflct*/
"Distancia Max Pieza Perdida y Lte Sospech+ Distancia Disparo Rebasados",          /*164  SE164 Missing Part Conflct*/
"Distancia Min Pieza Perdida y Lte Sospech+ Distancia Disparo Rebasados",          /*165  SE165 Missing Part Conflct*/
"Distancia Min Pieza Perdida y Corte Distancia Absoluta Rebasados",                 /*166  SE166 Missing Part Conflct*/
"Distancia Max Pieza Perdida y Corte Distancia Absoluta Rebasados",                 /*167  SE167 Missing Part Conflct*/
"Distancia Min Pieza Perdida y Ajuste Distancia Absoluta Rebasados",                /*168  SE168 Missing Part Conflct*/
"Distancia max parte perdida y cruce valor distancia absoluta",                /*169  SE169 Missing Part Conflct*/
"Valor min compensacion energia y +Rechz cruce lim energia",                  /*170  SE170 Energy Comp Conflict*/
"Valor min compensacion energia y +Sospch cruce lim energia",                 /*171  SE171 Energy Comp Conflict*/
"Valor max compensacion energia y -Rechz cruce lim energia",                  /*172  SE172 Energy Comp Conflict*/
"Valor max compensacion energia y -Sospch cruce lim energia",                 /*173  SE173 Energy Comp Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*174  SE174 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*175  SE175 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*176  SE176 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*177  SE177 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*178  SE178 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*179  SE179 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*180  SE180 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*181  SE181 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*182  SE182 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*183  SE183 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*184  SE184 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*185  SE185 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*186  SE186 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*187  SE187 Rapid Trav. Conflict*/

"SE188",                                                                              /*188  SE188 RESERVED            */
"SE189",                                                                              /*189  SE189 RESERVED            */
"SE190",                                                                              /*190  SE190 RESERVED            */
"SE191",                                                                              /*191  SE191 RESERVED            */



/** ----  SETUP GROUP 7  ---- **/

                                                                                      
"SE192",                                                                              /*192 SE192 RESERVED            */
"Conflicto Config Vel. Rapida",                                                      /*193 SE193 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*194 SE194 Rapid Trav. Conflict*/
"Conflicto Config Vel. Rapida",                                                      /*195 SE195 Rapid Trav. Conflict*/
"Mantener cruce fuerza y lims",                                                      /*196 SE196 Hold Force Conflict */
"Mantener cruce fuerza y lims",                                                      /*197 SE197 Hold Force Conflict */
"Mantener cruce fuerza y lims",                                                      /*198 SE198 Hold Force Conflict */
"Mantener cruce fuerza y lims",                                                      /*199 SE199 Hold Force Conflict */
"Cruzados Fza A y lims",                                                         /*200 SE200 Force/Lmt Conflict  */
"Cruzados Fza A y lims",                                                         /*201 SE201 Force/Lmt Conflict  */
"Cruzados Fza A y lims",                                                         /*202 SE202 Force/Lmt Conflict  */
"Cruzados Fza A y lims",                                                         /*203 SE203 Force/Lmt Conflict  */
"Cruzados Fza B y lims",                                                         /*204 SE204 Force/Lmt Conflict  */
"Cruzados Fza B y lims",                                                         /*205 SE205 Force/Lmt Conflict  */
"Cruzados Fza B y lims",                                                         /*206 SE206 Force/Lmt Conflict  */
"Cruzados Fza B y lims",                                                         /*207 SE207 Force/Lmt Conflict  */
"Paso fza en confl con lims",                                                   /*208 SE208 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*209 SE209 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*210 SE210 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*211 SE211 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*212 SE212 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*213 SE213 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*214 SE214 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*215 SE215 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*216 SE216 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*217 SE217 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*218 SE218 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*219 SE219 Force Step Conflict */
"SE220",                                                                              /*220 SE220 RESERVED            */
"SE221",                                                                              /*221 SE221 RESERVED            */
"SE222",                                                                              /*222 SE222 RESERVED            */
"SE223",                                                                              /*223 SE223 RESERVED            */



        
/** ----  SETUP GROUP 8  ---- **/

                                                                              
"SE224",                                                                              /*224  SE224 RESERVED            */
"Paso fza en confl con lims",                                                   /*225  SE225 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*226  SE226 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*227  SE227 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*228  SE228 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*229  SE229 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*230  SE230 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*231  SE231 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*232  SE232 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*233  SE233 Force Step Conflict */
"Paso fza en confl con lims",                                                   /*234  SE234 Force Step Conflict */
"Paso Fuerza en conflto con Ajuste Distancia Absoluta",                                /*235  SE235 Force Step Conflict */
"Paso Fuerza en conflto con Ajuste Distancia Predisparo",                              /*236  SE236 Force Step Conflict */
"Paso fuerza en conflto con Corte Distancia Absoluta",                                 /*237  SE237 Force Step Conflict */
"Paso Fuerza en conflto con Ajuste Corte Disparo",                                   /*238  SE238 Force Step Conflict */
"Paso Fuerza en conflto con Corte Pico Potencia",                                        /*239  SE239 Force Step Conflict */
"Paso Fuerza en conflto con Ajuste Pico Potencia",                                       /*240  SE240 Force Step Conflict */
"Paso Fuerza en conflto con Ajuste Energia",                                           /*241  SE241 Force Step Conflict */
"Paso Fuerza en conflto con Compensacion Energia",                                      /*242  SE242 Force Step Conflict */
"Paso Fuerza en conflto con Tiempo Soldadura",                                                /*243  SE243 Force Step Conflict */
"Paso Fuerza en Amplitud en conflto con Ajuste Amplitud",                           /*244  SE244 Amp/F Step Conflict */
"Fza sold A no se puede alcanz porq pres entrada es baja",                      /*245  SE245 Weld Force>Pressure */
"Fza sold B no se puede alcanz porq pres entrada es baja",                      /*246  SE246 Force B>Pressure    */
"Fza mant no se puede alcanz porque pres entrada es baja",                        /*247  SE247 Hold Force>Pressure */
"Pres entrada demas alta para fza sold especif",                                /*248  SE248 Pressure>Weld Force */
"Pres entrada demas alta para fza sold B especif",                              /*249  SE249 Pressure>Force B    */
"Pres entrada demas alta para fza sold especif",                                /*250  SE250 Pressure>Hold Force */
"Fza dispar en confl con lims. sospch",                                        /*251  SE251 Trig Force Conflict */
"SE252",                                                                              /*252  SE252 RESERVED            */
"SE253",                                                                              /*253  SE253 RESERVED            */
"SE254",                                                                              /*254  SE254 RESERVED            */
"SE255",                                                                              /*255  SE255 RESERVED            */
 



/** ----  SETUP GROUP 9  ---- **/

                                                                                     
"SE156",                                                                              /*256 SE256 RESERVED            */
"Fza dispar en confl con lims. rechz",                                         /*257 SE257 Trig Force Conflict */
"SE258",                                                                              /*258 SE258                     */
"Esta preselcion funciona solo con el Encoder",                                             /*259 SE259 Encoder Required    */
"SE260",                                                                              /*260 SE260                     */
"SE261",                                                                              /*261 SE261                     */
"SE262",                                                                              /*262 SE262                     */
"SE263",                                                                              /*263 SE263                     */
"Valor Min de Compensacion Energia y Lte Rechazo- Energia Rebasados",                 /*264 SE264 Energy Comp Conflict*/
"Valor Min de Compensacion Energia y Lte Sospech- Energia Rebasados",                /*265 SE265 Energy Comp Conflict*/
"Valor Min de Compensacion Energia y Lte Rechazo+ Energia Rebasados",                 /*266 SE266 Energy Comp Conflict*/
"Valor Min de Compensacion Energia y Lte Sospech+ Energia Rebasados",                /*267 SE267 Energy Comp Conflict*/
"Caracts seleccionadas no disponibles en este modelo.",                                /*268 SE268 Invalid Preset      */
"Se ha intentado emplear una preselecccion desconocida en 1 secuencia",                       /*269 SE269 Undefined Preset    */
"",                                                                                   /*270 SE270 Printer Offline     */
"Lte Sospech- Disparo y Lte Sospech+ Distancia Absoluta Rebasados",                /*271 SE271 -S Trg > +S Abs     */
"Lte Sospech- Disparo y Lte Rechazo+ Distancia Absoluta Rebasados",                 /*272 SE272 -S Trg > +R Abs     */
"Lte Rechazo- Disparo y Lte Sospech+ Distancia Absoluta Rebasados",                 /*273 SE273 -R Trg > +S Abs     */
"Lte Rechazo- Disparo y Lte Rechazo+ Distancia Absoluta Rebasados",                  /*274 SE274 -R Trg > +R Abs     */
"Lte Sospech- Disparo y Distancia Absoluta Rebasados",                               /*275 SE275 -S Trg > Abs        */
"Lte Rechazo- Disparo y Distancia Absoluta Rebasados",                                /*276 SE276 -R Trg > Abs        */
"SE277",                                                                              /*277 SE277 -R Trg > Abs Cutoff */
"SE278",                                                                              /*278 SE278                     */
"SE279",                                                                              /*279 SE279                     */
"SE280",                                                                              /*280 SE280                     */
"SE281",                                                                              /*281 SE281                     */
"SE282",                                                                              /*282 SE282                     */
"SE283",                                                                              /*283 SE283                     */
"SE284",                                                                              /*284 SE284 RESERVED            */
"SE285",                                                                              /*285 SE285 RESERVED            */
"SE286",                                                                              /*286 SE286 RESERVED            */
"SE287",                                                                              /*287 SE287 RESERVED            */
 



/** ----  SETUP GROUP 10  ---- **/

                                                                                     
"SE288",                                                                              /*288 SE288 RESERVED            */
"Retardo disparo ext. y predisparo encendidos a la vez",                              /*289 SE289                     */
"Entrada retardo disparo ext. no definido",                                           /*290 SE290                     */
"Salida EV puerta o pin entrada no definidos",                                        /*291 SE291                     */
"SE292",                                                                              /*292 SE292                     */
"SE293",                                                                              /*293 SE293                     */
"SE294",                                                                              /*294 SE294                     */
"SE295",                                                                              /*295 SE295                     */
"Ext Signal Setup",                                                                   /*296 SE296                     */
"SE297",                                                                              /*297 SE297                     */
"SE298",                                                                              /*298 SE298                     */
"SE299",                                                                              /*299 SE299                     */
"SE300",                                                                              /*300 SE300                     */
"SE301",                                                                              /*301 SE301                     */
"SE302",                                                                              /*302 SE302                     */
"SE303",                                                                              /*303 SE303                     */
"SE304",                                                                              /*304 SE304                     */
"SE305",                                                                              /*305 SE305                     */
"SE306",                                                                              /*306 SE306                     */
"SE307",                                                                              /*307 SE307                     */
"SE308",                                                                              /*308 SE308                     */
"SE309",                                                                              /*309 SE309                     */
"SE310",                                                                              /*310 SE310                     */
"SE311",                                                                              /*311 SE311                     */
"SE312",                                                                              /*312 SE312                     */
"SE313",                                                                              /*313 SE313                     */
"SE314",                                                                              /*314 SE314                     */
"SE315",                                                                              /*315 SE315                     */
"SE316",                                                                              /*316 SE316 RESERVED            */
"SE317",                                                                              /*317 SE317 RESERVED            */
"SE318",                                                                              /*318 SE318 RESERVED            */
"SE319",                                                                              /*319 SE319 RESERVED            */


};

//OmniLingua - End Spanish insertion here
//OmniLingua - Start Italian insertion here

const STR *const Alarm1Itl[] = {


/**------------------------------------------------**
 **        This group is the Setup Alarms          **
 **------------------------------------------------**/


/** ----  SETUP GROUP 1  ---- **/


"SE0",                                                                                /*0   SE0   RESERVED            */
"Sup Lim +- tempo sospetti",                                                       /*1   SE1   RESERVED            */
"Sup Lim +- tempo scarto",                                                        /*2   SE2   +-Time Limit Crossed*/
"Sup Lim +- energia sospetti",                                                     /*3   SE3   +-Time Limit Crossed*/
"+-Limite scarto energia pass.",                                                      /*4   SE4   +-Eng Limit Crossed */
"Sup Lim +- potenza sospetti",                                                      /*5   SE5   +-Eng Limit Crossed */
"Sup Lim +- potenza scarto",                                                       /*6   SE6   +-Pwr Limit Crossed */
"Sup Lim +- frequenza sospetti",                                                  /*7   SE7   +-Pwr Limit Crossed */
"Sup Lim +- frequenza scarto",                                                   /*8   SE8   +-Freq Limit Crossed*/
"Sup Lim +- distanza assoluta sospetti",                                          /*9   SE9   +-Freq Limit Crossed*/
"Sup Lim +- distanza assoluta scarto",                                           /*10  SE10  +-Abs Limit Crossed */
"Sup Lim +- distanza collasso sospetti",                                          /*11  SE11  +-Abs Limit Crossed */
"Sup Lim +- distanza collasso scarto",                                           /*12  SE12  +-Col Limit Crossed */
"+-Limite sosp. forza sald super.",                                             /*13  SE13  +-Col Limit Crossed */
"+-Limite sosp. forza sald super",                                              /*14  SE14  +-Frc Limit Crossed */
"Conf step ampiezza con tempo di sald",                                            /*15  SE15  +-Frc Limit Crossed */
"Conf step ampiezza con limite + Picco Potenza scarto",                             /*16  SE16  Amp Step Conflict   */
"Conf step ampiezza con limite + PiccoPotenza sosp",                             /*17  SE17  Amp Step Conflict   */
"Conf step ampiezza con limite + energia scarto",                                 /*18  SE18  Amp Step Conflict   */
"Conf step ampiezza con limite + energia sospetto",                                /*19  SE19  Amp Step Conflict   */
"Conf step ampiezza con limite + distanza assoluta scarto",                      /*20  SE20  Amp Step Conflict   */
"Conf step ampiezza con limite + distanza assoluta sospetto",                     /*21  SE21  Amp Step Conflict   */
"SE22",                                                                               /*22  SE22  Amp Step Conflict   */
"SE23",                                                                               /*23  SE23  Amp Step Conflict   */
"Conf step ampiezza con limite - distanza trigger scarto",                       /*24  SE24  Amp Step Conflict   */
"Conf step ampiezza con limite - distanza trigger sospetto",                      /*25  SE25  Amp Step Conflict   */
"Conf step ampiezza con limite + distanza trigger scarto",                       /*26  SE26  Amp Step Conflict   */
"Conf step ampiezza con limite + distanza trigger sospetto",                      /*27  SE27  Amp Step Conflict   */
"SE28",                                                                               /*28  SE28  RESERVED            */
"SE29",                                                                               /*29  SE29  RESERVED            */
"SE30",                                                                               /*30  SE30  RESERVED            */
"SE31",                                                                               /*31  SE31  RESERVED            */
                                                                                        
                                                                                        
                                                                                        
                                                                                        
/** ----  SETUP GROUP 2  ---- **/


"SE32",                                                                               /*32  SE32  RESERVED            */
"Conf step ampiezza su distanza assoluta con distanza pretrigger",             /*33  SE33  Amp Step Conflict   */
"Conf step ampiezza su distanza assoluta con cutoff distanza assoluta",        /*34  SE34  Amp Step Conflict   */
"Passo amp. a distanza assoluta interr. In conflitto con ann. Ciclo parte manc.",  /*35  SE35  Amp Step Conflict   */
"Passo amp. a distanza assoluta interr. In conflitto con ann. Ciclo parte manc.",  /*36  SE36  Amp Step Conflict   */
"Conf step ampiezza su pot con impostaz picco di potenza",                          /*37  SE37  Amp Step Conflict   */
"Passo amp. conflitto energia con comp. energia",                        /*38  SE38  Amp Step Conflict   */
"Conf step ampiezza su forza con impostazione forza",                               /*39  SE39  Amp Step Conflict   */
"Conf step amp su potenza con cutoff picco di potenza",                           /*40  SE40  Amp Step Conflict   */
"Conf step ampiezza su dist collasso con cutoff dist collasso",                 /*41  SE41  Amp Step Conflict   */
"Conf step ampiezza su dist collasso con distanza collasso",                        /*42  SE42  Amp Step Conflict   */
"Conf step ampiezza su tempo con timeout",                                      /*43  SE43  Amp Step Conflict   */
"Superati Lim +- distanza trigger scarto",                                            /*44  SE44  +-Trig Limit Crossed*/
"Sup Lim +- distanza trigger sospetti",                                           /*45  SE45  +-Trig Limit Crossed*/
"The preset recalled is either clear or not available for control level.",            /*46  SE46  Preset Not Available*/
"Conf step ampiezza su distanza assoluta con impostazione distanza assoluta",       /*47  SE47  Amp Step Conflict   */
"Conf step ampiezza su energia con impostaz energia",                             /*48  SE48  Amp Step Conflict   */
"Superati Lim + tempo scarto e timeout",                                             /*49  SE49  Timeout Conflict    */
"Superati Lim - tempo sospetto e timeout",                                            /*50  SE50  Timeout Conflict    */
"Superati Lim - tempo scarto e timeout",                                             /*51  SE51  Timeout Conflict    */
"Step ampiezza su forza uguale o maggiore a tutti i val di forza",                  /*52  SE52  Amp Step on Force   */
"Passo amp. su amo. Uguale o magg. A tutti valori amp.",                /*53  SE53  Force Step on Amp   */
"-Limite trigger sosp. ,maggiore di + lim. Assoluto sosp.",                     /*54  SE54  -S Trg > -S Abs     */
"+Lim. Distanza trigger sosp. maggiore di + lmite distanza assoluta sosp.",   /*55  SE55  +S Trg > +S Abs     */
"-Scarto limite trigger magg. Di - scarto limite ass.",                       /*56  SE56  -R Trg > -R Abs     */
"+Scarto limite trigger magg. Di +scarto limite ass",                       /*57  SE57  +R Trg > +R Abs     */
"Superati Lim + tempo sospetto e timeout",                                            /*58  SE58  Timeout Conflict    */
"Sup Lim - pot scarto e cutoff picco di potenza",                                  /*59  SE59  Cutoff Conflict     */
"SE60",                                                                               /*60  SE60  RESERVED            */
"SE61",                                                                               /*61  SE61  RESERVED            */
"SE62",                                                                               /*62  SE62  RESERVED            */
"SE63",                                                                               /*63  SE63  RESERVED            */




/** ----  SETUP GROUP 3  ---- **/


"SE64",                                                                               /*64  SE64  RESERVED            */

"Sup Lim + pot scarto e cutoff picco di potenza",                                  /*65  SE65  Cutoff Conflict     */
"Superati Lim - pot sosp e cutoff picco di potenza",                                 /*66  SE66  Cutoff Conflict     */
"Superati Lim + pot sosp e cutoff picco di potenza",                                 /*67  SE67  Cutoff Conflict     */
"SE68",                                                                               /*68  SE68  Cutoff Conflict     */
"SE69",                                                                               /*69  SE69  Cutoff Conflict     */
"SE70",                                                                               /*70  SE70                      */
"SE71",                                                                               /*71  SE71                      */
"Attivi sia ritardo del trigger che il pretrigger",                                          /*72  SE72  Trig Delay & Pretrig*/
"Forza trig uguale o magg della forza di saldatura",                                  /*73  SE73  Trig > Weld Force   */
"Sup Lim + tempo scarto e  limite - tempo sospetto",                                 /*74  SE74  Time S/R Limit Cross*/
"+limite tempo sospetto e -scarto limite tempo superato",                                 /*75  SE75  Time S/R Limit Cross*/
"Sup Lim + tempo scarto e limite + tempo sospetto",                                 /*76  SE76  Time S/R Limit Cross*/
"Sup Lim - tempo scarto e  limite - tempo sospetto",                                 /*77  SE77  Time S/R Limit Cross*/
"Sup Lim + energia scarto e  lim - energia sosp",                             /*78  SE78  Eng S/R Limit Cross */
"Sup Lim + energia sospetto e limite - energia scarto",                             /*79  SE79  Eng S/R Limit Cross */
"Sup Lim + energia scarto e limite + energia sospetto",                             /*80  SE80  Eng S/R Limit Cross */
"Sup Lim - energia scarto e limite - energia sospetto",                             /*81  SE81  Eng S/R Limit Cross */
"+Scarto picco limite alim. e -picco limite pot. Sosp. superato",                      /*82  SE82  Pwr S/R Limit Cross */
"+Picco lim. alim. sosp. e -scarto picco lim. alimen. superato",                       /*83  SE83  Pwr S/R Limit Cross */
"+Scarto picco limite alim. and +Sosp. picco limite alim. superato",                       /*84  SE84  Pwr S/R Limit Cross */
"-Scarto picco limite alim. and -Sosp. picco limite alim. superato",                       /*85  SE85  Pwr S/R Limit Cross */
"Sup Lim + distanza assoluta scarto e limite - distanza assoluta sospetto",       /*86  SE86  Abs S/R Limit Cross */
"Sup Lim + distanza assoluta sospetto e limite - distanza assoluta scarto",       /*87  SE87  Abs S/R Limit Cross */
"Sup Lim + distanza assoluta scarto e limite + distanza assoluta sospetto",       /*88  SE88  Abs S/R Limit Cross */
"Sup Lim - distanza assoluta scarto e limite - distanza assoluta sospetto",       /*89  SE89  Abs S/R Limit Cross */
"Sup Lim + distanza collasso scarto e limite - distanza collasso sospetto",       /*90  SE90  Col S/R Limit Cross */
"Sup Lim + distanza collasso sospetto e lim - distanza collasso scarto",       /*91  SE91  Col S/R Limit Cross */
"SE92",                                                                               /*92  SE92  RESERVED        */
"SE93",                                                                               /*93  SE93  RESERVED        */
"SE94",                                                                               /*94  SE94  RESERVED        */
"SE95",                                                                               /*95  SE95  RESERVED        */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 4  ---- **/                                                       
                                                                                        
                                                                                        
"SE96",                                                                               /*96   SE96  RESERVED            */
"Sup Lim + distanza collasso scarto e lim + distanza collasso sospetto",       /*97   SE97  Col S/R Limit Cross */
"Sup Lim - distanza collasso scarto e lim - distanza collasso sospetto",       /*98   SE98  Col S/R Limit Cross */
"Sup Lim + forza di sald scarto e lim -forza di sald sospetto",               /*99   SE99  Frc S/R Limit Cross */
"Sup Lim + forza di sald sospetto e lim - forza di sald scarto",               /*100  SE100 Frc S/R Limit Cross */
"Sup Lim + forza di sald scarto e lim + forza di sald sospetto",               /*101  SE101 Frc S/R Limit Cross */
"Sup Lim - forza di sald scarto e lim - forza di sald sospetto",               /*102  SE102 Frc S/R Limit Cross */
"Sup Limite + frequenza scarto e limite - frequenza sospetto",                       /*103  SE103 Freq S/R Limit Cross*/
"+Limite frequenza sospetto e -scarto limite frequenza superato",                       /*104  SE104 Freq S/R Limit Cross*/
"Sup Limite + frequenza scarto e limite + frequenza sospetto",                       /*105  SE105 Freq S/R Limit Cross*/
"Sup Limite - frequenza scarto e limite - frequenza sospetto",                       /*106  SE106 Freq S/R Limit Cross*/
"Sup Limite + distanza trigger scarto e limite - distanza trigger sospetto",         /*107  SE107 Trig S/R Limit Cross*/
"Sup Limite + distanza trigger sospetto e limite - distanza trigger scarto",         /*108  SE108 Trig S/R Limit Cross*/
"Sup Limite + distanza trigger scarto e limite + distanza trigger sospetto",         /*109  SE109 Trig S/R Limit Cross*/
"Sup Limite - distanza trigger scarto e limite - distanza trigger sospetto",         /*110  SE110 Trig S/R Limit Cross*/
"Confl step forza con cutoff collasso",                                          /*111  SE111 Force Step Cutoff   */
"Confl step forza con cutoff collasso",                                          /*112  SE112 Force Step Cutoff   */
"Confl step forza con cutoff collasso",                                          /*113  SE113 Force Step Cutoff   */
"Confl step forza con cutoff collasso",                                          /*114  SE114 Force Step Cutoff   */
"Confl step forza con cutoff collasso",                                          /*115  SE115 Force Step Cutoff   */
"Confl step forza con cutoff collasso",                                          /*116  SE116 Force Step Cutoff   */
"Confl step forza con cutoff collasso",                                          /*117  SE117 Force Step Cutoff   */
"Confl step forza con cutoff collasso",                                          /*118  SE118 Force Step Cutoff   */
"Superate impostaz di compensaz energia massima e minima",                           /*119  SE119 Energy Comp Crossed */
"Superati impostaz limiti max e min. parti mancanti",                                  /*120  SE120 Missing Part Crossed*/
"Superati dist pretrigger e step di forza su limite distanza assoluta",              /*121  SE121 Pretrigger Conflict */
"Superati dist pretrigger e step di ampiezza su limite distanza assoluta",          /*122  SE122 Pretrigger Conflict */
"Superati dist pretrigger e limite - distanza assoluta scarto",                    /*123  SE123 Pretrigger Conflict */
"SE124",                                                                              /*124  SE124 RESERVED            */
"SE125",                                                                              /*125  SE125 RESERVED            */
"SE126",                                                                              /*126  SE126 RESERVED            */
"SE127",                                                                              /*127  SE127 RESERVED            */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 5  ---- **/


"SE128",                                                                              /*128  SE128 RESERVED            */
"Superati dist pretrigger e limite - distanza assoluta sospetto",                   /*129  SE129 Pretrigger Conflict */
"Superato dist pretrigger e limite + distanza assoluta scarto",                    /*130  SE130 Pretrigger Conflict */
"Superati dist pretrigger e limite + distanza assoluta sospetto",                   /*131  SE131 Pretrigger Conflict */
"Superati dist pretrigger e limite + distanza trigger scarto",                     /*132  SE132 Pretrigger Conflict */
"Superati dist pretrigger e limite + distanza trigger sospetto",                    /*133  SE133 Pretrigger Conflict */
"Superati dist pretrigger e limite - distanza trigger scarto",                     /*134  SE134 Pretrigger Conflict */
"Superati dist pretrigger e limite - distanza trigger sospetto",                    /*135  SE135 Pretrigger Conflict */
"Distanza pretrigger e distanza interr. Assoluta super",                           /*136  SE136 Pretrigger Conflict */
"Superati distanza pretrigger e distanza assoluta",                                  /*137  SE137 Pretrigger Conflict */
"Sup arresto distanza assoluta e limite - distanza assoluta scarto",               /*138  SE138 Abs Cutoff Conflict */
"Sup arresto distanza assoluta e limite - distanza trigger scarto",                /*139  SE139 Abs Cutoff Conflict */
"Sup arresto distanza assoluta e limite - distanza assoluta sospetto",              /*140  SE140 Abs Cutoff Conflict */
"Superati arresto interruz dist ass e lim - distanza trigger sospetto",               /*141  SE141 Abs Cutoff Conflict */
"Superati arresto interruz dist ass e lim + distanza assoluta scarto",               /*142  SE142 Abs Cutoff Conflict */
"Superati arresto interruz dist ass e lim + distanza trigger scarto",                /*143  SE143 Abs Cutoff Conflict */
"Interruzione dist. assoluta e +limite distanza assoluta sops. sup.",              /*144  SE144 Abs Cutoff Conflict */
"Interruzione dist. assoluta e +Limite distanza sosp. trigger superata",               /*145  SE145 Abs Cutoff Conflict */
"Parte manc. Distanza massima e -Scarto distanza ass. superati",          /*146  SE146 Missing Part Conflct*/
"Sup distanza minima parti mancanti e limite - distanza assoluta scarto",          /*147  SE147 Missing Part Conflct*/
"Sup distanza massima parti mancanti e limite - distanza trigger scarto",           /*148  SE148 Missing Part Conflct*/
"Parte manc. Distanza minima e  -Limte distanza scarto trigger sup.",           /*149  SE149 Missing Part Conflct*/
"Parte manc. Distanza massima e -Suspect Absolute Distance Limit Crossed",         /*150  SE150 Missing Part Conflct*/
"Sup distanza massima parti mancanti e limite - distanza trigger sospetto",          /*151  SE151 Missing Part Conflct*/
"Sup distanza minima parti mancanti e  limite - distanza trigger sospetto",          /*152  SE152 Missing Part Conflct*/
"Parte mancante distanza max. e +scarto limite assoluto distanza super.",          /*153  SE153 Missing Part Conflct*/
"Parte manc. Distanza minima e +scarto limite assoluto distanza super.",          /*154  SE154 Missing Part Conflct*/

"Sup distanza massima parti mancanti e limite + distanza trigger scarto",           /*155  SE155 Missing Part Conflct*/
"SE156",                                                                              /*156  SE156 RESERVED            */
"SE157",                                                                              /*157  SE157 RESERVED            */
"SE158",                                                                              /*158  SE158 RESERVED            */
"SE159",                                                                              /*159  SE159 RESERVED            */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 6  ---- **/


"SE160",                                                                              /*160  SE160 RESERVED            */
"Sup distanza minima parti mancanti e limite + distanza trigger scarto",           /*161  SE161 Missing Part Conflct*/
"Sup distanza massima parti mancanti e limite + distanza assoluta sospetto",         /*162  SE162 Missing Part Conflct*/
"Sup distanza minima parti mancanti e limite + distanza assoluta sospetto",         /*163  SE163 Missing Part Conflct*/
"Sup distanza massima parti mancanti e limite + distanza trigger sospetto",          /*164  SE164 Missing Part Conflct*/
"Sup distanza minima parti mancanti e limite + distanza trigger sospetto",          /*165  SE165 Missing Part Conflct*/
"Sup distanza min parti mancanti e limite di arresto distanza ass",                 /*166  SE166 Missing Part Conflct*/
"Sup distanza max parti mancanti e lim di arresto distanza ass",                 /*167  SE167 Missing Part Conflct*/
"Sup distanza minima parti mancanti e impostazione distanza assoluta",                /*168  SE168 Missing Part Conflct*/
"Parte manc. Distanza massima e impostazione distanza assolu. Super.",                /*169  SE169 Missing Part Conflct*/
"Valore min. compensazione energia and +Limite energia scarto super.",                  /*170  SE170 Energy Comp Conflict*/
"Valore min. compensazione energia and +Limite energia sospetto super.",                 /*171  SE171 Energy Comp Conflict*/
"Valore max. compensazione energia and -Limite energia scarto super.",                  /*172  SE172 Energy Comp Conflict*/
"Valore max. compensazione energia and -Limite energia sospetto super.",                 /*173  SE173 Energy Comp Conflict*/
"Conflitto impostazione spost rap",                                                      /*174  SE174 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*175  SE175 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*176  SE176 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*177  SE177 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*178  SE178 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*179  SE179 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*180  SE180 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*181  SE181 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*182  SE182 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*183  SE183 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*184  SE184 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*185  SE185 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*186  SE186 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*187  SE187 Rapid Trav. Conflict*/
"SE188",                                                                              /*188  SE188 RESERVED            */
"SE189",                                                                              /*189  SE189 RESERVED            */
"SE190",                                                                              /*190  SE190 RESERVED            */
"SE191",                                                                              /*191  SE191 RESERVED            */



/** ----  SETUP GROUP 7  ---- **/

                                                                                      
"SE192",                                                                              /*192 SE192 RESERVED            */
"Conflitto impostazione spost rap",                                                      /*193 SE193 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*194 SE194 Rapid Trav. Conflict*/
"Conflitto impostazione spost rap",                                                      /*195 SE195 Rapid Trav. Conflict*/
"Forza mant e limiti superati",                                                      /*196 SE196 Hold Force Conflict */
"Forza mant e limiti superati",                                                      /*197 SE197 Hold Force Conflict */
"Forza mant e limiti superati",                                                      /*198 SE198 Hold Force Conflict */
"Forza mant e limiti superati",                                                      /*199 SE199 Hold Force Conflict */
"Forza A  e limiti superati",                                                         /*200 SE200 Force/Lmt Conflict  */
"Forza A  e limiti superati",                                                         /*201 SE201 Force/Lmt Conflict  */
"Forza A  e limiti superati",                                                         /*202 SE202 Force/Lmt Conflict  */
"Forza A  e limiti superati",                                                         /*203 SE203 Force/Lmt Conflict  */
"Forza B  e limiti superati",                                                         /*204 SE204 Force/Lmt Conflict  */
"Forza B  e limiti superati",                                                         /*205 SE205 Force/Lmt Conflict  */
"Forza B  e limiti superati",                                                         /*206 SE206 Force/Lmt Conflict  */
"Forza B  e limiti superati",                                                         /*207 SE207 Force/Lmt Conflict  */
"Passo forza in conflitto con lim.",                                                   /*208 SE208 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*209 SE209 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*210 SE210 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*211 SE211 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*212 SE212 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*213 SE213 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*214 SE214 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*215 SE215 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*216 SE216 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*217 SE217 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*218 SE218 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*219 SE219 Force Step Conflict */
"SE220",                                                                              /*220 SE220 RESERVED            */
"SE221",                                                                              /*221 SE221 RESERVED            */
"SE222",                                                                              /*222 SE222 RESERVED            */
"SE223",                                                                              /*223 SE223 RESERVED            */



        
/** ----  SETUP GROUP 8  ---- **/

                                                                              
"SE224",                                                                              /*224  SE224 RESERVED            */
"Passo forza in conflitto con lim.",                                                   /*225  SE225 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*226  SE226 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*227  SE227 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*228  SE228 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*229  SE229 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*230  SE230 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*231  SE231 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*232  SE232 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*233  SE233 Force Step Conflict */
"Passo forza in conflitto con lim.",                                                   /*234  SE234 Force Step Conflict */
"Conflitto step di forza con impostazione distanza ass",                                /*235  SE235 Force Step Conflict */
"Conf step di forza con impostaz distanza pretrigger",                              /*236  SE236 Force Step Conflict */
"Conf step di forza con distanza di arresto assoluta",                                 /*237  SE237 Force Step Conflict */
"Conflitto step di forza con arresto trigger",                                   /*238  SE238 Force Step Conflict */
"Conf step forza con impostaz arr pic di pot",                                        /*239  SE239 Force Step Conflict */
"Conf step di forza con impostaz picco di pot",                                       /*240  SE240 Force Step Conflict */
"Conf step di forza con impostaz energia",                                           /*241  SE241 Force Step Conflict */
"Conf step di forza con compensaz di energia",                                      /*242  SE242 Force Step Conflict */
"Conf step di forza con tempo di sald",                                                /*243  SE243 Force Step Conflict */
"Confb step di forza su ampiezza con impostazione ampiezza",                           /*244  SE244 Amp/F Step Conflict */
"Forza sald. A non raggiunta causa bassa pressione ingresso",                      /*245  SE245 Weld Force>Pressure */
"Forza sald. B non raggiunta causa bassa pressione ingresso",                      /*246  SE246 Force B>Pressure    */
"Forza mant. Non raggiunta causa bassa pressione ingresso",                        /*247  SE247 Hold Force>Pressure */
"Pressione ingresso troppo alta per forza sald. specificata",                                /*248  SE248 Pressure>Weld Force */
"Pressione ingresso troppo alta per forza sald. B specificata",                              /*249  SE249 Pressure>Force B    */
"Pressione ingresso troppo alta per forza mant. specificata",                                /*250  SE250 Pressure>Hold Force */
"Froza trigger in conflitto con limiti sospetti",                                        /*251  SE251 Trig Force Conflict */
"SE252",                                                                              /*252  SE252 RESERVED            */
"SE253",                                                                              /*253  SE253 RESERVED            */
"SE254",                                                                              /*254  SE254 RESERVED            */
"SE255",                                                                              /*255  SE255 RESERVED            */
 



/** ----  SETUP GROUP 9  ---- **/

                                                                                     
"SE156",                                                                              /*256 SE256 RESERVED            */
"Forza trigger in conflitto con limiti scarto",                                         /*257 SE257 Trig Force Conflict */
"SE258",                                                                              /*258 SE258                     */
"Questa predis richiede la pres di encoder",                                             /*259 SE259 Encoder Required    */
"SE260",                                                                              /*260 SE260                     */
"SE261",                                                                              /*261 SE261                     */
"SE262",                                                                              /*262 SE262                     */
"SE263",                                                                              /*263 SE263                     */
"Sup valore minimo compensazione energia e limite - energia scarto",                 /*264 SE264 Energy Comp Conflict*/
"Sup valore minimo compensazione energia e limite - energia sospetto",                /*265 SE265 Energy Comp Conflict*/
"Sup valore massimo compensazione energia e limite + energia scarto",                 /*266 SE266 Energy Comp Conflict*/
"Sup valore massimo compensazione energia e limite + energia sosp",                /*267 SE267 Energy Comp Conflict*/
"Opzione selezionata non dispon. su questo modello",                                /*268 SE268 Invalid Preset      */
"E stata richiesta una predis non definita da usare in una seq",                       /*269 SE269 Undefined Preset    */
"",                                                                                   /*270 SE270 Printer Offline     */
"Sup limite - trigger sospetto e limite + distanza assoluta sospetto",                /*271 SE271 -S Trg > +S Abs     */
"Sup limite - trigger sospetto e limite + distanza assoluta scarto",                 /*272 SE272 -S Trg > +R Abs     */
"Sup limite - trigger scarto e limite + distanza assoluta sospetto",                 /*273 SE273 -R Trg > +S Abs     */
"Sup limite - trigger scarto e limite + distanza assoluta scarto",                  /*274 SE274 -R Trg > +R Abs     */
"Sup limite - trigger sospetto e distanza assoluta",                               /*275 SE275 -S Trg > Abs        */
"Sup limite - trigger scarto e distanza assoluta",                                /*276 SE276 -R Trg > Abs        */
"SE277",                                                                              /*277 SE277 -R Trg > Abs Cutoff */
"SE278",                                                                              /*278 SE278                     */
"SE279",                                                                              /*279 SE279                     */
"SE280",                                                                              /*280 SE280                     */
"SE281",                                                                              /*281 SE281                     */
"SE282",                                                                              /*282 SE282                     */
"SE283",                                                                              /*283 SE283                     */
"SE284",                                                                              /*284 SE284 RESERVED            */
"SE285",                                                                              /*285 SE285 RESERVED            */
"SE286",                                                                              /*286 SE286 RESERVED            */
"SE287",                                                                              /*287 SE287 RESERVED            */
 



/** ----  SETUP GROUP 10  ---- **/

                                                                                     
"SE288",                                                                              /*288 SE288 RESERVED            */
"Ritardo Trigger esterno e Pretrigger attivo per entrambi",                           /*289 SE289                     */
"Ritardo Trigger esterno ingresso spinotto non definito",                             /*290 SE290                     */
"Entrambi non definiti SV blocco uscita e ingresso spinotto ",                        /*291 SE291                     */
"SE292",                                                                              /*292 SE292                     */
"SE293",                                                                              /*293 SE293                     */
"SE294",                                                                              /*294 SE294                     */
"SE295",                                                                              /*295 SE295                     */
"Ext Signal Setup",                                                                   /*296 SE296                     */
"SE297",                                                                              /*297 SE297                     */
"SE298",                                                                              /*298 SE298                     */
"SE299",                                                                              /*299 SE299                     */
"SE300",                                                                              /*300 SE300                     */
"SE301",                                                                              /*301 SE301                     */
"SE302",                                                                              /*302 SE302                     */
"SE303",                                                                              /*303 SE303                     */
"SE304",                                                                              /*304 SE304                     */
"SE305",                                                                              /*305 SE305                     */
"SE306",                                                                              /*306 SE306                     */
"SE307",                                                                              /*307 SE307                     */
"SE308",                                                                              /*308 SE308                     */
"SE309",                                                                              /*309 SE309                     */
"SE310",                                                                              /*310 SE310                     */
"SE311",                                                                              /*311 SE311                     */
"SE312",                                                                              /*312 SE312                     */
"SE313",                                                                              /*313 SE313                     */
"SE314",                                                                              /*314 SE314                     */
"SE315",                                                                              /*315 SE315                     */
"SE316",                                                                              /*316 SE316 RESERVED            */
"SE317",                                                                              /*317 SE317 RESERVED            */
"SE318",                                                                              /*318 SE318 RESERVED            */
"SE319",                                                                              /*319 SE319 RESERVED            */

};

//OmniLingua - End Italian insertion here
//OmniLingua - Start French insertion here

const STR *const Alarm1Fr[] = {


/**------------------------------------------------**
 **        This group is the Setup Alarms          **
 **------------------------------------------------**/


/** ----  SETUP GROUP 1  ---- **/


"SE0",                                                                                /*0   SE0   RESERVED            */
"Lim.+/- Susp. Temps Croisees",                                                       /*1   SE1   RESERVED            */
"Lim.+/- Rej. Temps Croisees",                                                        /*2   SE2   +-Time Limit Crossed*/
"Lim.+/- Susp. Energie croisees",                                                     /*3   SE3   +-Time Limit Crossed*/
"Lim.+/- Rej. Energie croisees",                                                      /*4   SE4   +-Eng Limit Crossed */
"Lim.+/- Susp. Puiss. Croisees",                                                      /*5   SE5   +-Eng Limit Crossed */
"Lim.+/- Rej. Puiss. Croisees",                                                       /*6   SE6   +-Pwr Limit Crossed */
"Lim.+/- Susp. Frequence Croisees",                                                  /*7   SE7   +-Pwr Limit Crossed */
"Lim.+/- Rej. Frequence Croisees",                                                   /*8   SE8   +-Freq Limit Crossed*/
"Lim.+/- Susp. Distance Absolue Croisees",                                          /*9   SE9   +-Freq Limit Crossed*/
"Lim.+/- Rej. Distance Absolue Croisees",                                           /*10  SE10  +-Abs Limit Crossed */
"Lim.+/- Susp. Dist. Rel. Croisees",                                          /*11  SE11  +-Abs Limit Crossed */
"Lim.+/- Rej. Dist. Rel. Croisees",                                           /*12  SE12  +-Col Limit Crossed */
"Lim.+/- Susp Force Soud. Croisees",                                             /*13  SE13  +-Col Limit Crossed */
"Lim.+/- Rej. Force Soud. Croisees",                                              /*14  SE14  +-Frc Limit Crossed */
"Conflit Saut Amplitude/Temps Soudage",                                            /*15  SE15  +-Frc Limit Crossed */
"Conflit Saut Amplitude/Lim.+ Puiss. Crete Rej.",                             /*16  SE16  Amp Step Conflict   */
"Conflit Saut Amplitude/Lim.+ Puiss. Crete Susp.",                            /*17  SE17  Amp Step Conflict   */
"Conflit Saut Amplitude/Lim.+ Energie Rej.",                                 /*18  SE18  Amp Step Conflict   */
"Conflit Saut Amplitude/Lim.+ Energie Susp.",                                /*19  SE19  Amp Step Conflict   */
"Conflit Saut Amplitude/Lim.+ Distance Absolue Rej.",                      /*20  SE20  Amp Step Conflict   */
"Conflit Saut Amplitude/Lim.+ Distance Absolue Susp.",                     /*21  SE21  Amp Step Conflict   */
"SE22",                                                                               /*22  SE22  Amp Step Conflict   */
"SE23",                                                                               /*23  SE23  Amp Step Conflict   */
"Conflit Saut Amplitude/Lim.- Distance Trigg. Rej.",                       /*24  SE24  Amp Step Conflict   */
"Conflit Saut Amplitude/Lim.- Distance Trigg. Susp.",                      /*25  SE25  Amp Step Conflict   */
"Conflit Saut Amplitude/Lim.+ Distance Trigg. Rej.",                       /*26  SE26  Amp Step Conflict   */
"Conflit Saut Amplitude/Lim.+ Distance Trigg. Susp.",                      /*27  SE27  Amp Step Conflict   */
"SE28",                                                                               /*28  SE28  RESERVED            */
"SE29",                                                                               /*29  SE29  RESERVED            */
"SE30",                                                                               /*30  SE30  RESERVED            */
"SE31",                                                                               /*31  SE31  RESERVED            */
                                                                                        
                                                                                        
                                                                                        
                                                                                        
/** ----  SETUP GROUP 2  ---- **/


"SE32",                                                                               /*32  SE32  RESERVED            */
"Conflit Saut Amplitude a Distance Abs./Distance Pretrigger",             /*33  SE33  Amp Step Conflict   */
"Conflit Saut Amplitude a Distance Abs./Cpure Distance Abs.",        /*34  SE34  Amp Step Conflict   */
"Conflit Saut Amplitude a Distance Abs. Cpre avec interr. Cycle piece mqte",  /*35  SE35  Amp Step Conflict   */
"Conflit Saut Amplitude a Distance Abs. Cpre avec interr. Cycle piece mqte",  /*36  SE36  Amp Step Conflict   */
"Conflit Saut Amplitude a Puiss./Reglage Puiss. Crete",                          /*37  SE37  Amp Step Conflict   */
"Conflit Saut amplitude a Energie avec compensation Energie",                        /*38  SE38  Amp Step Conflict   */
"Conflit Saut Amplitude a Force/Reglage Force",                               /*39  SE39  Amp Step Conflict   */
"Conflit Saut Amplitude a Puiss./Cpure Puiss Crete.",                           /*40  SE40  Amp Step Conflict   */
"Conflit Saut Amplitude a D. Rel./Cpure Distance Relative",                 /*41  SE41  Amp Step Conflict   */
"Conflit Saut Amplitude a D. Rel./Distance Relative",                        /*42  SE42  Amp Step Conflict   */
"Conflit Saut Amplitude a Temps/Delai d'Att.",                                      /*43  SE43  Amp Step Conflict   */
"Lim.+/-  Rej. Distance Trigg croisees",                                            /*44  SE44  +-Trig Limit Crossed*/
"Lim.+/- Susp. Distance Trigg croisees",                                           /*45  SE45  +-Trig Limit Crossed*/
"The preset recalled is either clear or not available for control level.",            /*46  SE46  Preset Not Available*/
"Conflit Saut Amplitude a Distance Absolue/Reglage Distance Absolue",       /*47  SE47  Amp Step Conflict   */
"Conflit Saut Amplitude a Energie/Reglage Energie",                             /*48  SE48  Amp Step Conflict   */
"Lim.+ Temps Rej. et Delai maxi croisees",                                             /*49  SE49  Timeout Conflict    */
"Lim. Temps Susp.- et Del. Att. Croisees",                                            /*50  SE50  Timeout Conflict    */
"Lim. Temps Rej.- et Del. Att. Croisees",                                             /*51  SE51  Timeout Conflict    */
"Saut Amplitude sur force egal ou sup. a ttes les valeurs de force",                  /*52  SE52  Amp Step on Force   */
"Saut Amplitude a amplitude egale a ou sup. a ttes valeurs amp",                /*53  SE53  Force Step on Amp   */
"Lim.- Trigg. Susp. sup. a Lim.+ Absolue Susp.",                     /*54  SE54  -S Trg > -S Abs     */
"Lim.+ Distance Trigg. Susp. sup. a Lim.+ Distance Absolue Susp.",       /*55  SE55  +S Trg > +S Abs     */
"Lim.- Trigg. Rejet. sup. a Lim.- Absolue Rej.",                       /*56  SE56  -R Trg > -R Abs     */
"Lim.+ Trigg. Rejet. sup. a Lim.+ Absolue Rej.",                       /*57  SE57  +R Trg > +R Abs     */
"Lim.+ Temps Susp. et Del. d'Att. Croisees",                                            /*58  SE58  Timeout Conflict    */
"Lim.- Puiss. Rej. et Cpure Puiss. Crete Croisees",                                  /*59  SE59  Cutoff Conflict     */
"SE60",                                                                               /*60  SE60  RESERVED            */
"SE61",                                                                               /*61  SE61  RESERVED            */
"SE62",                                                                               /*62  SE62  RESERVED            */
"SE63",                                                                               /*63  SE63  RESERVED            */




/** ----  SETUP GROUP 3  ---- **/


"SE64",                                                                               /*64  SE64  RESERVED            */
"Lim.+ Puiss. Rej. et Cpure sur Puiss. Crete Croisees",                                  /*65  SE65  Cutoff Conflict     */
"Lim.- Puiss. Susp. et Cpure Puiss. Crete Croisees",                                 /*66  SE66  Cutoff Conflict     */
"Lim.+ Puiss. Susp. et Cpure Puiss. Crete Croisees",                                 /*67  SE67  Cutoff Conflict     */
"SE68",                                                                               /*68  SE68  Cutoff Conflict     */
"SE69",                                                                               /*69  SE69  Cutoff Conflict     */
"SE70",                                                                               /*70  SE70                      */
"SE71",                                                                               /*71  SE71                      */
"Delai Trigg. et Pretrigg. ts les 2 actives",                                          /*72  SE72  Trig Delay & Pretrig*/
"Force Trigg. egale ou sup. a Force de Soudage",                                  /*73  SE73  Trig > Weld Force   */
"Lim.+ Temps Rej. et Lim.- Temps Susp. Croisees",                                 /*74  SE74  Time S/R Limit Cross*/
"Lim.+ Temps Susp. et Lim.- Temps Rej. Croisees",                                 /*75  SE75  Time S/R Limit Cross*/
"Lim.+ Temps Rej. et Lim.+ Temps Susp. Croisees",                                 /*76  SE76  Time S/R Limit Cross*/
"Lim.- Temps Rej. et Lim.- Temps Susp. Croisees",                                 /*77  SE77  Time S/R Limit Cross*/
"Lim.+ Energie Rej. et Lim.- Energie Susp. Croisees",                             /*78  SE78  Eng S/R Limit Cross */
"Lim.+ Energie Susp. et Lim.- Energie Rej. Croisees",                             /*79  SE79  Eng S/R Limit Cross */
"Lim.+ Energie Rej. et Lim.+ Energie Susp. Croisees",                             /*80  SE80  Eng S/R Limit Cross */
"Lim.- Energie Rej. et Lim.- Energie Susp. Croisees",                             /*81  SE81  Eng S/R Limit Cross */
"Lim.+ Puiss. Crete Rej. et Lim.- Puiss. Crete Susp. Croisees",                      /*82  SE82  Pwr S/R Limit Cross */
"Lim.+ Puiss. Crete Susp. et Lim.- Puiss. Crete Rej. Croisees",                       /*83  SE83  Pwr S/R Limit Cross */
"Lim.+ Puiss. Crete Rej. et Lim.+ Puiss. Crete Susp. Croisees",                       /*84  SE84  Pwr S/R Limit Cross */
"Lim.- Puiss. Crete Rej. et Lim.- Puiss. Crete Susp. Croisees",                       /*85  SE85  Pwr S/R Limit Cross */
"Lim.+ Distance Absolue Rej. et Lim.- Distance Absolue Susp. Croisees",       /*86  SE86  Abs S/R Limit Cross */
"Lim.+ Distance Absolue Susp. et Lim.- Distance Absolue Rej. Croisees",       /*87  SE87  Abs S/R Limit Cross */
"Lim.+ Distance Absolue Rej. et Lim.+ Distance Absolue Susp. Croisees",       /*88  SE88  Abs S/R Limit Cross */
"Lim.- Distance Absolue Rej. et Lim.- Distance Absolue Susp. Croisees",       /*89  SE89  Abs S/R Limit Cross */
"Lim.+ Distance Relative Rej. et Lim.- Distance Relative Susp Croisees",       /*90  SE90  Col S/R Limit Cross */
"Lim.+ Distance Relative Susp. et Lim.- Distance Relative Rej. Croisees",       /*91  SE91  Col S/R Limit Cross */
"SE92",                                                                               /*92  SE92  RESERVED        */
"SE93",                                                                               /*93  SE93  RESERVED        */
"SE94",                                                                               /*94  SE94  RESERVED        */
"SE95",                                                                               /*95  SE95  RESERVED        */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 4  ---- **/                                                       
                                                                                        
                                                                                        
"SE96",                                                                               /*96   SE96  RESERVED            */
"Lim.+ Distance Relative Rej. et Lim.+ Distance Relative Susp. Croisees",       /*97   SE97  Col S/R Limit Cross */
"Lim.- Distance Relative Rej. et Lim.- Distance Relative Susp. Croisees",       /*98   SE98  Col S/R Limit Cross */
"Lim.+ Force Soud. Rej. et Lim.- Force Soud. Susp. Croisees",               /*99   SE99  Frc S/R Limit Cross */
"Lim.+ Force Soud. Rej. et Lim.- Force Soud. Susp. Croisees",               /*100  SE100 Frc S/R Limit Cross */
"Lim.+ Force Soud. Rej. et Lim.+ Force Soud. Susp. Croisees",               /*101  SE101 Frc S/R Limit Cross */
"Lim.- Force Soud. Rej. et Lim.- Force Soud. Susp. Croisees",               /*102  SE102 Frc S/R Limit Cross */
"Lim.+ Frequence Rej. et Lim.- Frequence Susp. Croisees",                       /*103  SE103 Freq S/R Limit Cross*/
"Lim.+ Frequence Susp. et Lim. Frequence Rej. Croisees",                       /*104  SE104 Freq S/R Limit Cross*/
"Lim.+ Frequence Rej. et Lim.+ Frequence Susp. Croisees",                       /*105  SE105 Freq S/R Limit Cross*/
"Lim.- Frequence Rej. et Lim.- Frequence Susp. Croisees",                       /*106  SE106 Freq S/R Limit Cross*/
"Lim.+ Distance Trig. Rej. et Lim.- Distance Trig. Susp. Croisees",         /*107  SE107 Trig S/R Limit Cross*/
"Lim.+ Distance Trig. Susp. et Lim.- Distance Trig. Rej. Croisees",         /*108  SE108 Trig S/R Limit Cross*/
"Lim.+ Distance Trig. Rej. et Lim.+ Distance Trig. Susp. Croisees",         /*109  SE109 Trig S/R Limit Cross*/
"Lim.- Distance Trig. Rej. et Lim.- Distance Trig. Susp. Croisees",         /*110  SE110 Trig S/R Limit Cross*/
"Conflit Saut Force/Coupure Dist. Rel.",                                          /*111  SE111 Force Step Cutoff   */
"Conflit Saut Force/Coupure Dist. Rel.",                                          /*112  SE112 Force Step Cutoff   */
"Conflit Saut Force/Coupure Dist. Rel.",                                          /*113  SE113 Force Step Cutoff   */
"Conflit Saut Force/Coupure Dist. Rel.",                                          /*114  SE114 Force Step Cutoff   */
"Conflit Saut Force/Coupure Dist. Rel.",                                          /*115  SE115 Force Step Cutoff   */
"Conflit Saut Force/Coupure Dist. Rel.",                                          /*116  SE116 Force Step Cutoff   */
"Conflit Saut Force/Coupure Dist. Rel.",                                          /*117  SE117 Force Step Cutoff   */
"Conflit Saut Force/Coupure Dist. Rel.",                                          /*118  SE118 Force Step Cutoff   */
"Reglages Min. et Max. de Compensation d'Energie Croisees",                           /*119  SE119 Energy Comp Crossed */
"Reglages Mini. et Maxi. de Pce Manquante croisees",                                  /*120  SE120 Missing Part Crossed*/
"Distance Pretrigger et Lim. Saut Force a Distance Absolue Croisees",              /*121  SE121 Pretrigger Conflict */
"Distance Pretrigger et Lim. Saut Amplitude a Distance Absolue Croisees",          /*122  SE122 Pretrigger Conflict */
"Distance Pretrigger et Lim.- Distance Absolue Rej. Croisees",                    /*123  SE123 Pretrigger Conflict */
"SE124",                                                                              /*124  SE124 RESERVED            */
"SE125",                                                                              /*125  SE125 RESERVED            */
"SE126",                                                                              /*126  SE126 RESERVED            */
"SE127",                                                                              /*127  SE127 RESERVED            */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 5  ---- **/


"SE128",                                                                              /*128  SE128 RESERVED            */
"Distance Pretrigger et Lim.- Distance Absolue Susp. Croisees",                   /*129  SE129 Pretrigger Conflict */
"Distance Pretrigger et Lim.+ Distance Absolue Rej. Croisees",                    /*130  SE130 Pretrigger Conflict */
"Distance Pretrigger et Lim.+ Distance Absolue Susp. Croisees",                   /*131  SE131 Pretrigger Conflict */
"Distance Pretrigger et Lim.+ Distance Trigg. Rej. Croisees",                     /*132  SE132 Pretrigger Conflict */
"Distance Pretrigger et Lim.+ Distance Trigg. Susp. Croisees",                    /*133  SE133 Pretrigger Conflict */
"Distance Pretrigger et Lim.- Distance Trigg. Rej. Croisees",                     /*134  SE134 Pretrigger Conflict */
"Distance Pretrigger et Lim.- Distance Trigg. Susp. Croisees",                    /*135  SE135 Pretrigger Conflict */
"Distance Pretrigger et Distance Absolue Cpre Croisees",                           /*136  SE136 Pretrigger Conflict */
"Distance Pretrigger et Distance Absolue Croisees",                                  /*137  SE137 Pretrigger Conflict */
"Cpure Distance Absolue et Lim.- Distance Absolue Rej. Croisees",               /*138  SE138 Abs Cutoff Conflict */
"Cpure Distance Absolue et Lim.- Distance Trigg. Rej. Croisees",                /*139  SE139 Abs Cutoff Conflict */
"Cpure Distance Absolue et Lim.- Distance Absolue Susp. Croisees",              /*140  SE140 Abs Cutoff Conflict */
"Cpure Distance Absolue et Lim.- Distance Trigg. Susp. Croisees",               /*141  SE141 Abs Cutoff Conflict */
"Cpure Distance Absolue et Lim.+ Distance Absolue Rej. Croisees",               /*142  SE142 Abs Cutoff Conflict */
"Cpure Distance Absolue et Lim.+ Distance Trigg Rej. Croisees",                /*143  SE143 Abs Cutoff Conflict */
"Coup. Distance absolue et Lim.+ Distance Absolue Susp. Croisees",              /*144  SE144 Abs Cutoff Conflict */
"Coupure distance absolue et Lim.+ Distance Triggl. Susp. Croisees",               /*145  SE145 Abs Cutoff Conflict */
"Distance Maxi. Piece Manquante et Lim.- Distance Absolue Rej. Croisees",          /*146  SE146 Missing Part Conflct*/
"Distance Mini. Piece Manquante et Lim.- Distance Absolue Rej. Croisees",          /*147  SE147 Missing Part Conflct*/
"Distance Maxi. Piece Manquante et Lim.- Distance Trigg. Rej. Croisees",           /*148  SE148 Missing Part Conflct*/
"Distance Mini. Piece Manquante et Lim.- Distance Trigg. Rej. Croisees",           /*149  SE149 Missing Part Conflct*/
"Distance Mini. Piece Manquante et Lim.- Distance Absolue Susp. Croisees",         /*150  SE150 Missing Part Conflct*/
"Distance Maxi. Piece Manquante et Lim.- Distance Trigg. Susp. Croisees",          /*151  SE151 Missing Part Conflct*/
"Distance Mini. Piece Manquante et Lim.- Distance Trigg. Susp. Croisees",          /*152  SE152 Missing Part Conflct*/
"Distance Maxi. Piece Manquante et Lim.+ Distance Absolue Rej. Croisees",          /*153  SE153 Missing Part Conflct*/
"Distance Mini. Piece manquante et Lim.+ Distance Absolue Rej. Croisees",          /*154  SE154 Missing Part Conflct*/
"Distance Maxi. Piece Manquante et Lim.+ Distance Trigg. Rej. Croisees",           /*155  SE155 Missing Part Conflct*/
"SE156",                                                                              /*156  SE156 RESERVED            */
"SE157",                                                                              /*157  SE157 RESERVED            */
"SE158",                                                                              /*158  SE158 RESERVED            */
"SE159",                                                                              /*159  SE159 RESERVED            */
                                                                                        
                                                                                        

/** ----  SETUP GROUP 6  ---- **/


"SE160",                                                                              /*160  SE160 RESERVED            */
"Distance Mini. Piece Manquante et Lim.+ Distance Trigg. Rej. Croisees",           /*161  SE161 Missing Part Conflct*/
"Distance Maxi. Piece Manquante et Lim.+ Distance Absolue Susp. Croisees",         /*162  SE162 Missing Part Conflct*/
"Distance Mini. Piece Manquante et Lim.+ Distance Absolue Susp. Croisees",         /*163  SE163 Missing Part Conflct*/
"Distance Maxi. Piece Manquante et Lim.+ Distance Trigg. Susp. Croisees",          /*164  SE164 Missing Part Conflct*/
"Distance Mini. Piece Manquante et Lim.+ Distance Trigg. Susp. Croisees",          /*165  SE165 Missing Part Conflct*/
"Distance Mini. Piece Manquante et Cpure Distance Absolue Croisees",                 /*166  SE166 Missing Part Conflct*/
"Distance Maxi. Piece Manquante et Cpure Distance Absolue Croisees",                 /*167  SE167 Missing Part Conflct*/
"Distance Mini. Piece Manquante et Reglage Distance Absolue Croisees",                /*168  SE168 Missing Part Conflct*/
"Distance Mini. Piece Manquante et Reglage Distance Absolue Croisees",                /*169  SE169 Missing Part Conflct*/
"Valeur Maxi. Compensation Energie et Lim.+ Energie Rej. Croisees",                  /*170  SE170 Energy Comp Conflict*/
"Valeur Mini. Compensation Energie et Lim.+ Energie Susp. Croisees",                 /*171  SE171 Energy Comp Conflict*/
"Valeur Maxi. Compensation Energie et Lim.- Energie Rej. Croisees",                  /*172  SE172 Energy Comp Conflict*/
"Valeur Maxi. Compensation Energie et Lim.- Energie Susp. Croisees",                 /*173  SE173 Energy Comp Conflict*/
"Conflit Config. Course Rapide",                                                      /*174  SE174 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*175  SE175 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*176  SE176 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*177  SE177 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*178  SE178 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*179  SE179 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*180  SE180 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*181  SE181 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*182  SE182 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*183  SE183 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*184  SE184 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*185  SE185 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*186  SE186 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*187  SE187 Rapid Trav. Conflict*/
"SE188",                                                                              /*188  SE188 RESERVED            */
"SE189",                                                                              /*189  SE189 RESERVED            */
"SE190",                                                                              /*190  SE190 RESERVED            */
"SE191",                                                                              /*191  SE191 RESERVED            */



/** ----  SETUP GROUP 7  ---- **/

                                                                                      
"SE192",                                                                              /*192 SE192 RESERVED            */
"Conflit Config. Course Rapide",                                                      /*193 SE193 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*194 SE194 Rapid Trav. Conflict*/
"Conflit Config. Course Rapide",                                                      /*195 SE195 Rapid Trav. Conflict*/
"Fce maint. Et limites croisees",                                                      /*196 SE196 Hold Force Conflict */
"Fce maint. Et limites croisees",                                                      /*197 SE197 Hold Force Conflict */
"Fce maint. Et limites croisees",                                                      /*198 SE198 Hold Force Conflict */
"Fce maint. Et limites croisees",                                                      /*199 SE199 Hold Force Conflict */
"Force A et limites croisees",                                                         /*200 SE200 Force/Lmt Conflict  */
"Force A et limites croisees",                                                         /*201 SE201 Force/Lmt Conflict  */
"Force A et limites croisees",                                                         /*202 SE202 Force/Lmt Conflict  */
"Force A et limites croisees",                                                         /*203 SE203 Force/Lmt Conflict  */
"Force B et limites croisees",                                                         /*204 SE204 Force/Lmt Conflict  */
"Force B et limites croisees",                                                         /*205 SE205 Force/Lmt Conflict  */
"Force B et limites croisees",                                                         /*206 SE206 Force/Lmt Conflict  */
"Force B et limites croisees",                                                         /*207 SE207 Force/Lmt Conflict  */
"Conflit saut force avec limites",                                                   /*208 SE208 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*209 SE209 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*210 SE210 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*211 SE211 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*212 SE212 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*213 SE213 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*214 SE214 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*215 SE215 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*216 SE216 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*217 SE217 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*218 SE218 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*219 SE219 Force Step Conflict */
"SE220",                                                                              /*220 SE220 RESERVED            */
"SE221",                                                                              /*221 SE221 RESERVED            */
"SE222",                                                                              /*222 SE222 RESERVED            */
"SE223",                                                                              /*223 SE223 RESERVED            */



        
/** ----  SETUP GROUP 8  ---- **/

                                                                              
"SE224",                                                                              /*224  SE224 RESERVED            */
"Conflit saut force avec limites",                                                   /*225  SE225 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*226  SE226 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*227  SE227 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*228  SE228 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*229  SE229 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*230  SE230 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*231  SE231 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*232  SE232 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*233  SE233 Force Step Conflict */
"Conflit saut force avec limites",                                                   /*234  SE234 Force Step Conflict */
"Conflit Saut Force/Reglage Distance Absolue",                                /*235  SE235 Force Step Conflict */
"Conflit Saut Force/Reglage Distance Pretrigg.",                              /*236  SE236 Force Step Conflict */
"Conflit Saut Force/Cpure Distance Absolue",                                 /*237  SE237 Force Step Conflict */
"Conflit Saut Force/Reglage Coupure Trigg.",                                   /*238  SE238 Force Step Conflict */
"Conflit Saut Force/Coupure Puiss. Crete",                                        /*239  SE239 Force Step Conflict */
"Conflit Saut Force/Reglage Puiss. Crete",                                       /*240  SE240 Force Step Conflict */
"Conflit Saut Force/Reglage Energie",                                           /*241  SE241 Force Step Conflict */
"Conflit Saut Force/Compensation d'Energie",                                      /*242  SE242 Force Step Conflict */
"Conflit Saut Force/Temps de soudage",                                                /*243  SE243 Force Step Conflict */
"Conflit Saut Force a Amplitude/Reglage Amplitude",                           /*244  SE244 Amp/F Step Conflict */
"Force soud A non atteinte car pression entree trop faible",                      /*245  SE245 Weld Force>Pressure */
"Force soud B non atteinte car pression entree trop faible",                      /*246  SE246 Force B>Pressure    */
"Force maint non atteinte car pression entree trop faible",                        /*247  SE247 Hold Force>Pressure */
"Pression entree trop elevee pour force soud specifiee",                                /*248  SE248 Pressure>Weld Force */
"Pression entree trop elevee pour force soud B specifiee",                              /*249  SE249 Pressure>Force B    */
"Pression entree trop elevee pour force maint. specifiee",                                /*250  SE250 Pressure>Hold Force */
"Conflit Force Trigg. avec limites Susp.",                                        /*251  SE251 Trig Force Conflict */
"SE252",                                                                              /*252  SE252 RESERVED            */
"SE253",                                                                              /*253  SE253 RESERVED            */
"SE254",                                                                              /*254  SE254 RESERVED            */
"SE255",                                                                              /*255  SE255 RESERVED            */
 



/** ----  SETUP GROUP 9  ---- **/

                                                                                     
"SE156",                                                                              /*256 SE256 RESERVED            */
"Conflit Force Trigg. avec Limites Rej.",                                         /*257 SE257 Trig Force Conflict */
"SE258",                                                                              /*258 SE258                     */
"Encodeur requis pr executer ce preset",                                             /*259 SE259 Encoder Required    */
"SE260",                                                                              /*260 SE260                     */
"SE261",                                                                              /*261 SE261                     */
"SE262",                                                                              /*262 SE262                     */
"SE263",                                                                              /*263 SE263                     */
"Valeur Mini. Compensation Energie et Lim.- Energie Rej. Croisees",                 /*264 SE264 Energy Comp Conflict*/
"Valeur Mini. Compensation Energie et Lim.- Energie Susp. Croisees",                /*265 SE265 Energy Comp Conflict*/
"Valeur Maxi. Compensation Energie et Lim.+ Energie Rej. Croisees",                 /*266 SE266 Energy Comp Conflict*/
"Valeur Maxi. Compensation Energie et Lim.+ Energie Susp. Croisees",                /*267 SE267 Energy Comp Conflict*/
"Fonction(s) selectionn. non dispon. dans ce module.",                                /*268 SE268 Invalid Preset      */
"Prereglage non defini requis dans une sequence.",                       /*269 SE269 Undefined Preset    */
"",                                                                                   /*270 SE270 Printer Offline     */
"Lim.- Trigg. Susp. et Lim.+ Distance Absolue Susp. Croisees",                /*271 SE271 -S Trg > +S Abs     */
"Lim.- Trigg. Susp. et Lim.+ Distance Absolue Rej. Croisees",                 /*272 SE272 -S Trg > +R Abs     */
"Lim.- Trigg. Rej. et Lim.+ Distance Absolue Susp. Croisees",                 /*273 SE273 -R Trg > +S Abs     */
"Lim.- Trigg. Rej. et Lim.+ Distance Absolue Rej. Croisees",                  /*274 SE274 -R Trg > +R Abs     */
"Lim.- Trigg. Susp. et Distance Absolue Croisees",                               /*275 SE275 -S Trg > Abs        */
"Lim.- Trigg. Rej. et Distance Absolue Croisees",                                /*276 SE276 -R Trg > Abs        */
"SE277",                                                                              /*277 SE277 -R Trg > Abs Cutoff */
"SE278",                                                                              /*278 SE278                     */
"SE279",                                                                              /*279 SE279                     */
"SE280",                                                                              /*280 SE280                     */
"SE281",                                                                              /*281 SE281                     */
"SE282",                                                                              /*282 SE282                     */
"SE283",                                                                              /*283 SE283                     */
"SE284",                                                                              /*284 SE284 RESERVED            */
"SE285",                                                                              /*285 SE285 RESERVED            */
"SE286",                                                                              /*286 SE286 RESERVED            */
"SE287",                                                                              /*287 SE287 RESERVED            */
 



/** ----  SETUP GROUP 10  ---- **/

                                                                                     
"SE288",                                                                              /*288 SE288 RESERVED            */
"Delai Trigg Ext et Fonction Pretrigg Incompatibles",                                 /*289 SE289                     */
"Broche d'entrée de Delai de Trigg ext. non defini",                                  /*290 SE290                     */
"Broche E/S de verrou electovanne non définie",                                       /*291 SE291                     */
"SE292",                                                                              /*292 SE292                     */
"SE293",                                                                              /*293 SE293                     */
"SE294",                                                                              /*294 SE294                     */
"SE295",                                                                              /*295 SE295                     */
"Ext Signal Setup",                                                                   /*296 SE296                     */
"SE297",                                                                              /*297 SE297                     */
"SE298",                                                                              /*298 SE298                     */
"SE299",                                                                              /*299 SE299                     */
"SE300",                                                                              /*300 SE300                     */
"SE301",                                                                              /*301 SE301                     */
"SE302",                                                                              /*302 SE302                     */
"SE303",                                                                              /*303 SE303                     */
"SE304",                                                                              /*304 SE304                     */
"SE305",                                                                              /*305 SE305                     */
"SE306",                                                                              /*306 SE306                     */
"SE307",                                                                              /*307 SE307                     */
"SE308",                                                                              /*308 SE308                     */
"SE309",                                                                              /*309 SE309                     */
"SE310",                                                                              /*310 SE310                     */
"SE311",                                                                              /*311 SE311                     */
"SE312",                                                                              /*312 SE312                     */
"SE313",                                                                              /*313 SE313                     */
"SE314",                                                                              /*314 SE314                     */
"SE315",                                                                              /*315 SE315                     */
"SE316",                                                                              /*316 SE316 RESERVED            */
"SE317",                                                                              /*317 SE317 RESERVED            */
"SE318",                                                                              /*318 SE318 RESERVED            */
"SE319",                                                                              /*319 SE319 RESERVED            */

};

//OmniLingua - End French insertion here

/**------------------------------------------**
 **       SETUPS CONSTANT STRINGS            **
 **------------------------------------------**/

const STR *const Setup0001[]=  {"PRESET = [ ","Parameter = [ ","PRESEL = [","PRESET = [ ","PRESET = ["};
const STR *const Setup0002[]=  {"Weld Mode","Modus","Modo Soldura","Mod. di sald.","Mode Soud"};
const STR *const Setup0003[]=  {"Weld Time","Schweisszeit","Tiem Sold","Tempo di sald.","Temps Soud"};
const STR *const Setup0004[]=  {"Hold Time","Haltezeit","Mant Tiem","Tempo Raff","Temps Mnt"};
const STR *const Setup0005[]=  {"Trig Force","Triggerkraft","Fuerza Disp","Forza trig","Force Trig"};
const STR *const Setup0006[]=  {"Trig Delay","Triggerverzoegerung","Retardo Disparo","Ritardo Trigger","Delai trigger"};
const STR *const Setup0007[]=  {"Weld Force","Schweisskraft","Frueza Sold","Forza di sald.","Force Soud"};
const STR *const Setup0008[]=  {"Weld Force(A)","Schweisskraft(A)","Fuerza Sold(A)","Forza di sald.(A)","Force Soud(A)"};
const STR *const Setup0009[]=  {"Weld Force(B)","Schweisskraft(B)","Fuerza Sold(B)","Forza di sald.(B)","Force Soud(B)"};
const STR *const Setup0010[]=  {"Step at Time","Profil bei Zeit","Paso a Tiem","Step a tempo","Saut a Temps"};
const STR *const Setup0011[]=  {"Hold Force","Haltekraft","Fuerza Manten","Forza di Raff","Force Mtn"};
const STR *const Setup0012[]=  {"Rapid Traverse","Eilgang","Vel. Rapida","Spost. Rapido","Mouvemt Rapide"};
const STR *const Setup0013[]=  {"RT Distance","Eilgang Weg","Distanc CR","Distanza RT","Distance CR"};
const STR *const Setup0014[]=  {"Downspeed","Abfahrgeschwindigkeit","Vel. Lenta","Vel discs","Vit. Desc"};
const STR *const Setup0015[]=  {"Amplitude","Amplitude","Amplitud","Ampiezza","Amplitude"};
const STR *const Setup0016[]=  {"Amplitude(A)","Amplitude(A)","Amplitud(A)","Ampiezza(A)","Amplitude(A)"};
const STR *const Setup0017[]=  {"Amplitude(B)","Amplitude(B)","Amplitud(B)","Ampiezza(B)","Amplitude(B)"};
const STR *const Setup0018A[]= {"Step at Time","Profil bei Zeit","Paso a Tiem","Step a tempo","Saut a Temps"};
const STR *const Setup0018B[]= {"Step at Energy","Profil bei Energie","Paso a Energia","Step su energ","Saut a Energie"};
const STR *const Setup0018C[]= {"Step at Power","Profil bei Leistung","Paso a Potencia","Step su potenza","Saut a Puiss."};
const STR *const Setup0018D[]= {"Step at Distance","Profil bei Weg","Paso a Distancia","Step su distanza","Saut a Distance"};
const STR *const Setup0018E[]= {"Step at Force","Profil bei Kraft","Paso a Fuerza","Step su forza","Saut a Force"};
const STR *const Setup0018F[]= {"Step at External Signal","Profil bei externem Signal","Paso a Senal Externa","Step su segnale esterno","Saut a Signal Externe"};
const STR *const Setup0019[]=  {"Pretrigger","Pretrigger","Predisparo","Pretrigger","Pretrigger"};
const STR *const Setup0019A[]= {"Pretrigger At Distance","Pretrigger bei Weg","Predisparo a Distancia","Pretrigger a distanza","Pretrigger a Distance"};
const STR *const Setup0019B[]= {"Auto Pretrigger","Auto Vorausloesung","Predisparo Auto","Auto pretrigger","Pretrigger Auto"};
const STR *const Setup0020[]=  {"External Pretrigger","External Pretrigger","Predisparo externo ","Pre-trigger esterno","Pretrigger externe"};
const STR *const Setup0021[]=  {"Pretrigger Amplitude","Pretrigger Amplitude","Amplitud Predisparo","Ampiezza pretrigger","Amplitude Pretrigger"};
const STR *const Setup0021A[]= {"Time on","Zeit ein","En Tiempo","Inizio Tempo","Temps on"};
const STR *const Setup0022[]=  {"Afterburst","Nachimpuls","Dis.Post.US","Afterburst","Postimpulsion"};
const STR *const Setup0023[]=  {"Afterburst Delay","Nachimpuls Verzoegerung","Ret. DPUS","Ritardo Afterburst","Delai Postimpulsion"};
const STR *const Setup0024[]=  {"Afterburst Time ","Nachimpuls Zeit ","Tiempo DPUS ","Durata Afterburst ","Dur. Postimpulsion"};
const STR *const Setup0025[]=  {"Afterburst Amplitude","Nachimpuls Amplitude","Amplitud DPUS","Ampiezza Afterburst","Amplitude Postimpulsion"};
const STR *const Setup0026[]=  {"Post Weld Seek","Frequenzsuche nach Schweissung","Busc Pos Sold","Seek post-sald","Rech Post Soud"};
const STR *const Setup0027[]=  {"Frequency Offset","Freq.aenderung","Desvio Frecuenc","Offset frequenza","Decal. Frequence"};
const STR *const Setup0028[]=  {"Control Limits","Steuer Grenzwerte","Ltes Control","Limiti controllo","Limites Comde"};
const STR *const Setup0029[]=  {"Energy Compensation","Energieausgleich","Compensacion Energia","Compensazione energia","Compensation Energ."};
const STR *const Setup0030[]=  {"Min. Energy","Min Energie","Energia Min","Energia min.","Energ. Min"};  
const STR *const Setup0031[]=  {"Max. Energy","Max Energie","Energia Max","Energia max.","Energ. Max"};
const STR *const Setup0032[]=  {"Peak Power Cutoff","Spitzenleist. Abschaltung","Corte por Pico de Potencia","Interruzioni pic pot","Cpure Pui. Crete"};
const STR *const Setup0033[]=  {"Ground Detect Abort","Abbruch Metallkontakt","Deteccion Tierra Cancelada","Annulla Ground Detect","Arret Detec. Masse"};
const STR *const Setup0034A[]= {"Absolute Cutoff","Abschaltung Weg absolut","Corte Absoluto","Interruzione distanza assoluta","Arret sur Absolue"};
const STR *const Setup0034B[]= {"Collapse Cutoff","Rel. Abschaltung","Corte por Colapso","Interruzione collasso","Cpure Dist Rel."};
const STR *const Setup0035[]=  {"Suspect Limits","Pruefe Grenzwerte","Limites Sospech","Limiti sospetti","Limites Suspect"};
const STR *const Setup0036[]=  {"Suspect Reset Required","Pruefe Reset erforderlich","Se precisa Reset sosp.","Richiesto possibile reset","RAZ Susp. Requise"};
const STR *const Setup0037[]=  {"+ S Time Limit","+ P Zeit Grenzwert","+ S Lte Tiempo","+ S Limite tempo","Lim.+ Temps S"};
const STR *const Setup0038[]=  {"- S Time Limit","- P Zeit Grenzwert","- S Lte Tiempo","- S Limite tempo","Lim.- Temps S"};
const STR *const Setup0039[]=  {"+ S Energy Limit","+ P Energie Grenzwert","+ S Lte Energia","+ S Limite energia","Lim.+ Energie S"};
const STR *const Setup0040[]=  {"- S Energy Limit","- P Energie Grenzwert","- S Lte Energia","- S Limite energia","Lim.- Energie S"};
const STR *const Setup0041[]=  {"+ S Power Limit","+ P Leist. Grenzwert","+ S Lte Potencia","+ S Limite potenza","Lim.+ Puiss. S"};
const STR *const Setup0042[]=  {"- S Power Limit","- P Leist. Grenzwert","- S Lte Potencia","- S Limite potenza","Lim.- Puiss. S"};
const STR *const Setup0043[]=  {"+ S Collapse Limit","+ P Rel. Grenzwert","+ S Lte Colapso","+ S Limite collasso","Lim.+ D. Rel. S"};
const STR *const Setup0044[]=  {"- S Collapse Limit","- P Rel. Grenzwert","- S Lte Colapso","- S Limite collasso","Lim.- D. Rel. S"};
const STR *const Setup0045[]=  {"+ S Absolute Limit","+ P Abs. Grenzwert","+ S Lte Absoluto","+ S Limite dist ass.","Lim.+ Absolue S"};
const STR *const Setup0046[]=  {"- S Absolute Limit","- P Abs. Grenzwert","- S Lte Absoluto","- S Limite dist ass.","Lim.- Absolue S"};
const STR *const Setup0047[]=  {"+ S Trigger Distance Limit","+ P Triggerweg Grenzwert","+ S Lte Distancia Disparo","+ S Limite dist. trigger","Lim.+ Dist. Trigger S"};
const STR *const Setup0048[]=  {"- S Trigger Distance Limit","- P Triggerweg Grenzwert","- S Lte Distancia Disparo","- S Limite dist. trigger","Lim.- Dist. Trigger S"};
const STR *const Setup0049[]=  {"+ S Weld Force Limit","+ P Schweisskraft Grenzwert","+ S Lte Fuerza Soldad","+ S Limite forza sald.","Lim.+ Force Soud. S"};
const STR *const Setup0050[]=  {"- S Weld Force Limit","- P Schweisskraft Grenzwert","- S Lte Fuerza Soldad","- S Limite forza sald.","Lim.- Force Soud. S"};
const STR *const Setup0051[]=  {"Reject Limits","Aussch Grenzwerte","Limites Rechazo","Limiti scarto","Limites Rejet"};
const STR *const Setup0052[]=  {"Reject Reset Required","Aussch Reset erforderlich","Preciso Reset Rechazo","Richiesto Reset scarto","RAZ Rejet Requise"};
const STR *const Setup0053[]=  {"+ R Time Limit","+ A Zeit Grenzwert","+ R Lte Tiempo","+ R Limite tempo","Lim.+ Temps R"};
const STR *const Setup0054[]=  {"- R Time Limit","- A Zeit Grenzwert","- R Lte Tiempo","- R Limite tempo","Lim.- Temps R"};
const STR *const Setup0055[]=  {"+ R Energy Limit","+ A Energie Grenzwert","+ R Lte Energia","+ R Limite energia","Lim.+ Energie R"};
const STR *const Setup0056[]=  {"- R Energy Limit","- A Energie Grenzwert","- R Lte Energia","- R Limite energia","Lim.- Energie R"};
const STR *const Setup0057[]=  {"+ R Power Limit","+ A Leist. Grenzwert","+ R Lte Potencia","+ R Limite potenza","Lim.+ Puiss. R"};                      
const STR *const Setup0058[]=  {"- R Power Limit","- A Leist. Grenzwert","- R Lte Potencia","- R Limite potenza","Lim.- Puiss. R"};                      
const STR *const Setup0059[]=  {"+ R Collapse Limit","+ A Rel. Grenzwert","+ R Lte Colapso","+ R Limite collasso","Lim.+ D. Rel. R"};                   
const STR *const Setup0060[]=  {"- R Collapse Limit","- A Rel. Grenzwert","- R Lte Colapso","- R Limite collasso","Lim.- D. Rel. R"};                   
const STR *const Setup0061[]=  {"+ R Absolute Limit","+ A Abs. Grenzwert","+ R Lte Absoluto","+ R Limite dist ass.","Lim.+ Absolue R"};
const STR *const Setup0062[]=  {"- R Absolute Limit","- A Abs. Grenzwert","- R Lte Absoluto","- R Limite dist ass.","Lim.- Absolue R"};
const STR *const Setup0063[]=  {"+ R Trigger Distance Limit","+ A Triggerweg Grenzwert","+ R Lte Distancia Disparo","+ R Limite dist. trigger","Lim.+ Dist. Trigger R"};                 
const STR *const Setup0064[]=  {"- R Trigger Distance Limit","- A Triggerweg Grenzwert","- R Lte Distancia Disparo","- R Limite dist. trigger","Lim.- Dist. Trigger R"};                 
const STR *const Setup0065[]=  {"+ R Weld Force Limit","+ A Schweisskraft Grenzwert","+ R Lte Fuerza Soldad","+ R Limite forza sald.","Lim.+ Force Soud. R"};
const STR *const Setup0066[]=  {"- R Weld Force Limit","- A Schweisskraft Grenzwert","- R Lte Fuerza Soldad","- R Limite forza sald.","Lim.- Force Soud. R"};                   
const STR *const Setup0067[]=  {"Test Amplitude","Test Amplitude","Test Amplitud","Test Ampiezza","Amplitude Test"};
const STR *const Setup0068[]=  {"Absolute Column Dist","Max. Verfahrweg","Dist absoluta column","Distanza ass colonna","Dist absolue colonne"};
const STR *const Setup0070[]=  {"Max Timeout","Max Zeitueberschreitung","Tiempo Max Excedido","Timeout max","Delai Max"};
const STR *const Setup0071[]=  {"Cycle Aborts","Zyklusabbruch","Cancel. Ciclo","Interruzioni Ciclo","Arret Cycle"};
const STR *const Setup0079[]=  {"X Axis Auto Scale","X-Achse Auto Skala","Autoescala Eje X","Auto Scala asse X","Ech. Auto Axe X"};
const STR *const Setup0080[]=  {"X Axis Scale","X-Achsenmassstab","Escala Eje X","Scala asse X","Ech. Axe X"};

/**---------------------------------------**
 **           aef SETTINGS                **
 **---------------------------------------**/ 

STR *aefSetting2[] = {"aef/aof Settings","Einstellung aef/aof","Ajustes aef/aof","Impostazioni aef/aof","Reglages aef/aof"};


/**--------------------------------------**
 **           ae SETTINGS                **
 **--------------------------------------**/ 

STR *aeSetting2[]     = {"ae/ao Settings","Einstellung ae/ao","Ajustes ae/ao","Impostazioni ae/ao","Reglages ae/ao"};


/**--------------------------------------**
 **           aed SETTINGS               **
 **--------------------------------------**/ 

STR *aedSetting[]          = {"aed/aod Settings","Einstellung aed/aod","Ajustes aed/aod","Impostazioni aed/aod","Reglages aed/aod"};
STR *aedForceSetting[]     = {"Trigger Force","Triggerkraft","Fuerza Disparo","Forza Trigger","Force Trigger"};
STR *aedGaugeSetting[]     = {"Act. Gauge Pressure","Aktueller Manometer Druck","Presion Manom Actdr","Pressione relativa att.","Pression Actuator"};


/**---------------------------------------**
 **           MISC STRINGS                **
 **---------------------------------------**/ 

const STR *const LimitsString[]      = {"LIMITS","GRENZWERTE","LTES","LIMITI","LIMITES"};
const STR *const SysConfigString[]   = {"SYSTEM CONFIGURATION","SYSTEMKONFIGURATION","CONFIGURACION SISTEMA","CONFIGURAZIONE SISTEMA","CONFIGURATION SYST."};
const STR *const SysInfoString[]     = {"SYSTEM INFORMATION","SYSTEMINFORMATION","INFORMACION SISTEMA","INFORMAZIONI SISTEMA","INFORMATION SYST."};
const STR *const PrintInfoString[]   = {"PRINTER","DRUCKER","IMPRESORA","STAMPANTE","IMPRMTE"};
const STR *const CalStr[]      = {"Calibration","Kalibrierung","Calibracion","Calibrazione","Calibration"};
const STR *const CalDateRun[]  = {"Calibration Date Run","Kalibrierungsdatum","Fecha de Calibracion","Data Calibrazione","Date dern.Calibrat."};
const STR *const Fixture[]     = {"Fixture","Aufnahme","Utillaje","Possaggio","Posage"};
const STR *const Horn[]        = {"Horn","Horn","Sonotrodo","Sonotodo","SONO"};
const STR *const VelocityStr[] = {"Velocity","Geschwindigkeit","Velocidad","Velocita","Vitesse"};
const STR *const Booster[]     = {"Booster","Booster","Booster","Booster","Booster"};
const STR *const ForceRamps[]  = {"Force Ramps","Kraft Rampe","Rampas Fuerza","Rampe forza","Rampes Force"};
const STR *const WeldForceRate[] = {"   Weld Force Rate","   Schweisskraftrampe","   Tasa Fuerza Sold","   Vel. forza di sald.","   Taux Force Soud"};
const STR *const StepForceRate[] = {"   Step Force Rate","   Stufenkraftrampe","   Tasa Fuerza Paso","   Vel. Step forza","   Taux Saut Force"};
const STR *const HoldForceRate[] = {"   Hold Force Rate","   Haltekraftrampe","   Tasa Fuerza Mant","   Vel. forza di raffredd.","   Taux Force Maint."};
const STR *const SystemPressure[]   = {"System Pressure","Systemdruck","Presion Sistema","Pressione sist.","Pression Syst."};
const STR *const ColumnPosition[]   = {"Column Position","Saeulen Position","Posicion Column","Posizione colonna","Position Colonn"};
const STR *const DownspeedSetting[] = {"Downspeed Setting","Abf.Geschwindigkeit Einstellung","Ajuste Vel. Lenta","Impostazione velocita discesa","Reglage Vit. Desc"};
const STR *const SetGaugePressure[] = {"Set Gauge Pressure","Manometerdruck einstellen","Fijar Presion Man","Imposta press. manometro","Regler Pression"};
const STR *const TriggerSetting[]   = {"Trigger Setting","Trigger Einstellung","Ajuste Disparo","Impost. Trigger","Reglage Trigger"};
const STR *const GaugePressure[]    = {"Gauge Pressure","Manometerdruck","Presion Manom Actdr","Pressione relativa att.","Pression Actuator"};
const STR *const MPSSwitchFlag1[]   = {"MPS Switch Flag1","MPS Schalter Flag1","MPS Switch Flag1","MPS Switch Flag1","MPS Switch Flag1"}; 
const STR *const MPSSwitchFlag2[]   = {"MPS Switch Flag2","MPS Schalter Flag2","MPS Switch Flag2","MPS Switch Flag2","MPS Switch Flag2"};
const STR *const CreatedOn[]        = {"Created On:","Erstellt am:","Creado el:","Creato su:","Cree le:"};
const STR *const External[]         = {"External","Extern","Externa","Esterno","Externe"};
const STR *const Internal[]         = {"Internal","Intern","Interno","Interno","Interne"};
const STR *const CollapseDistance[] = {"Collapse Distance","Weg rel.","Distancia Colapso","Distanza collasso","Distance Relative"};
const STR *const WriteIn1Str[]      = {"WriteIn Field1","Schre in Feld1","Escr. Campo1","Scrivere nel campo1","Saisie ds Chp1"  };
const STR *const WriteIn2Str[]      = {"WriteIn Field2","Schre in Feld2","Escr. Campo2","Scrivere nel campo2","Saisie ds Chp2"  };

const STR *const AbsoluteDistance[] = {"Absolute Distance","Weg absolut","Distancia Absoluta","Distanza assoluta","Distance Absolue"};
const STR *const PkPower[]          = {"Peak Power","Spitzenleistung","Pico Potencia","Picco pot.","Pui. Crete"};
const STR *const WeldEnergy[]       = {"Weld Energy","Schweissenergie","Energ Sold","Energia sald","Energ. Soud"};
const STR *const ScrubTime[]        = {"Scrub Time","Verzoegerungszeit","Tiempo Rsrva","Tempo lavaggio","Temps Retard."};
const STR *const Continuous[]       = {"Continuous","Kontinuierlich","Continua","Continua","Continu"}; 
const STR *const Allmodes[]         = {"All Modes","Alle Modi"," Todos mod","Tutte le modalita","Tous modes"}; 
const STR *const Sus[]              = {"Suspended","aufgeschoben"," Suspndido","Sospeso","Suspendu"};
//const STR *const Computer[]         = {"Computer","Computer","Ordenador","Computer","Ordinat."};
const STR *const Computer[]         = {"Compuweld","Compuweld","Compuweld","Compuweld","Compuweld"};
const STR *const Terminal[]         = {"Terminal","Klemme","Terminal","Terminale","Terminal"};
const STR *const StepAt[]           = {"Step At","Profil bei","Paso a","Step a","Saut"};
const STR *const Step[]             = {"Step","Profil","Paso","Step","Saut"};
const STR *const GroundDetect[]     = {"Ground Detect","Metallkontakt","Deteccion Tierra","Ground Detect","Detec. Masse"};
const STR *const Absolute[]         = {"Absolute","Absolut","Absoluto","Assoluto","Absolue"};
const STR *const Collapse[]         = {"Collapse","Rel.","Colapso","Collasso","Relative"};
const STR *const Energy[]           = {"Energy","Energie","Energia","Energia","Energie"};
const STR *const TimeStr[]          = {"Time","Zeit","Tiempo","Tempo","Temps"};
const STR *const All[]              = {"All","Alle","Todos","Tutti","Tous"};
const STR *const Basic[]            = {"Basic","Basis","Basic","Basic","Basic"};   
const STR *const Current[]          = {"CURRENT","AKTUELL","CORRNTE","CORRENTE","ACTUEL."};
const STR *const Page[]             = {"Page","Seite","Pagina","Pagina","Page"};
const STR *const TriggerStr[]       = {"Trigger","Trigger","Disparo","Trigger","Trigger"};
const STR *const Pretrigger[]       = {"Pretrigger","Pretrigger","Predisparo","Pretrigger","Pretrigger"};
const STR *const ExtTrigDly[]       = {"External U/S Delay","External U/S Delay","External U/S Delay","External U/S Delay","External U/S Delay"};
const STR *const EnergyBraking[]    = {"Energy Braking","Energieunterbrechung","Frenado Energ.","Interr. energia","Freinage d'Energ."};
const STR *const DUPSTxt[]          = {"Digital UPS","Digital UPS","F/A. Digital","UPS digitale","GUD"};
const STR *const Ramptime[]         = {"Ramp Time","Rampen Zeit","Tiempo Rampa","Tempo Rampa","Temps Montee"};
const STR *const Seektime[]         = {"Seek Time","Such-Zeit","Busc Tiempo","Durata Seek","Temps Rech."};
const STR *const Memory[]           = {"Memory","Speicher","Memoria","Memoria","Memoi."};
const STR *const WeldStatus[]       = {"Weld Status","Schweiss-Status","Estado Sold","Stato sald.","Etat Soud"};
const STR *const SelectStr[]        = {"Preset Name","Param. Name","Nombre Presel","Nomare Preset","Nom Preset"};
const STR *const SeekTimeStr[]      = {"Seek Time","Such-Zeit","Tiempo Busqueda","Durata Seek","Temps Rech."};
const STR *const TimedSeek[]        = {"Timed Seek","Suchperiode","Busc Temp","Ricerca progr.","Rech. Tempo."};
const STR *const ExtraCooling[]     = {"Extra Cooling","Zusatzkuehlung","Refrig Extra","Raffred. Extra","Refroid. Supp"};
const STR *const ExtPreset[]        = {"Ext Presets","Ext. Vorein","Persel Ext.","Preset Est.","Preset Ext."  };
const STR *const UserIO[]           = {"User Inputs/Outputs","Benutzer Eingabe/Ausgabe","E/S del Usuario","Input/Output Utilizzatore","Entr./Sorties Utili"};
const STR *const ExtTrgDelay[]      = {"Ext U/S Delay","Ext U/S Delay","Ext U/S Delay","Ext U/S Delay","Ext U/S Delay"};
const STR *const UserInJ3_32[]      = {"J3-32 Input","J3-32 Eingang","Entrada J3-32","Ingresso J3-32","Entrée J3-32"  };
const STR *const UserInJ3_33[]      = {"J3-33 Input","J3-33 Eingang","Entrada J3-33","Ingresso J3-33","Entrée J3-33"  };
const STR *const UserInJ3_19[]      = {"J3-19 Input","J3-19 Eingang","Entrada J3-19","Ingresso J3-19","Entrée J3-19"  };
const STR *const UserInJ3_17[]      = {"J3-17 Input","J3-17 Eingang","Entrada J3-17","Ingresso J3-17","Entrée J3-17"  };
const STR *const UserInJ3_31[]      = {"J3-31 Input","J3-31 Eingang","Entrada J3-31","Ingresso J3-31","Entrée J3-31"  };
const STR *const UserInJ3_01[]      = {"J3-1  Input","J3-1 Eingang","Entrada J3-1","Ingresso J3-1","Entrée J3-1"  };
const STR *const UserOutJ3_36[]     = {"J3-36 Output","J3-36 Ausgang","Salida J3-36","Uscita J3-36","Sortie J3-36"  };
const STR *const UserOutJ3_8[]      = {"J3-8  Output","J3-8  Ausgang","Salida J3-8","Uscita J3-8","Sortie J3-8"  }; 
const STR *const UserOutJ3_22[]     = {"J3-22 Output","J3-22 Ausgang","Salida J3-22","Uscita J3-22","Sortie J3-22"  };
const STR *const Preset1Str[]       = {"Select Preset1","Waehle Voreinst.1","Selecc Presel1","Selez. Preset1","Select Preset1"  };
const STR *const Preset2Str[]       = {"Select Preset2","Waehle Voreinst.2","Selecc Presel2","Selez. Preset2","Select Preset2"  };
const STR *const Preset4Str[]       = {"Select Preset4","Waehle Voreinst.4","Selecc Presel4","Selez. Preset4","Select Preset4"  };
const STR *const Preset8Str[]       = {"Select Preset8","Waehle Voreinst.8","Selecc Presel8","Selez. Preset8","Select Preset8"  };
const STR *const Preset16Str[]      = {"Select Preset16","Waehle Voreinst.16","Selecc Presel16","Selez. Preset16","Select Preset16"  };
const STR *const InpDisable[]       = {"Disabled","Unbrauchbar","Incapacitar","Incapacita","Incapacite"  }; 
const STR *const ExtTrigStr[]       = {"Ext Signal","Ext Signal","Ext Signal","Ext Signal","Ext Signal" };
const STR *const InpDisplyLock[]    = {"Display Lock","Eingabe Verriegl","Bloquear pantalla","Display spento","Bloquage clavier"  };
const STR *const InpSonicDsbl[]     = {"Sonics Disable","Schall deaktiv","Desactivar ultr.","Sonics Disable","Interruption us"  };
const STR *const InpMemReset[]      = {"Memory Reset","Speicher loesch","Reset memoria","Reset memoria","Reset memoire"  };
const STR *const SVInLock[]         = {"External Start","External Start","External Start","External Start","External Start"  };
const STR *const ConfirmPreset[]    = {"Confirm Preset","Voreinstellung bestaetigen","Confirme Presel","Conferma preset","Conf. Preset"};
const STR *const NoCyclStr[]        = {"No Cycle Alarm","Kein Zyklusalarm","No alar. Ciclo","No Cycle Alarm","Pas d'alarme"  };
const STR *const CycleOkStr[]       = {"Cycle Okay","Zyklus ok","Ciclo correcto","Ciclo ok","Cycle OK"  };
const STR *const AmpDecayStr[]      = {"Amplitude Decay","Ampl Reduzierung","Descenso Amp.","Smorzamento ampiezza","amplit.retombee"  };
const STR *const ExtBeeperStr[]     = {"Ext Beeper","Ext akust Signal","Ext Beeper","Segnale esterno","Beeper externe"  };
const STR *const OLAlarmStr[]       = {"Overload Alarm","Ueberlast Alarm","Alar. sobrecarga","Overload Alarm","Alarme surcharge"  };
const STR *const CMAlarmStr[]       = {"Modified Alarm", "Zyklusaenderung","Alar. Modificada","Allarme modificato","Alarme modifiee"  };
const STR *const NoteStr[]          = {"Note","Hinweis","Nota","Note","Note"  };
const STR *const SyncInStr[]        = {"Sync In","Sync In","Sync In","Sync In","Sync In"  };
const STR *const SyncOutStr[]       = {"Sync Out","Sync Out","Sync Out","Sync Out","Sync Out"  };
const STR *const Str_0V[]           = {"0V","0V","0V","0V","0V"  };
const STR *const Str_24V[]          = {"24V","24V","24V","24V","24V" };
const STR *const StrHandheld[]      = {"Hand Held ","Handgeraet","Portatil","Portatil","Portativ"  };
const STR *const CycleStart[]       = {"Cycle Start","Zyklusstart","Inicio Ciclo","Inizio ciclo","Start Cycle"};
const STR *const UserInputs[]       = {"User Inputs","Benutzer Eingabe","Entdas Usuario","Input utente","Entrees Uti"}; 
const STR *const PS[]               = {"Power Supply","Generator","Fuente Alimtacion","Alimentatore","Generateur"};
const STR *const Digital[]          = {"Digital","Digitale","Digital","Digitale","Digital"};
const STR *const Analog[]           = {"Analog","Analog","Analog","Analog","Analogique"};
const STR *const Custom[]           = {"Custom","Spezial","Person","Person","Special"};
const STR *const ExternalSignal[]   = {"External Signal","Externes Signal","Senal Externa","Segnale esterno","Signal Externe"};
const STR *const NotApp[]           = {"n/a","n/a","n/a","n/a","n/a"};   
const STR *const PercentStr[]       = {"%","%","%","%","%"};
const STR *const MillimeterStr[]    = {"mm","mm","mm","mm","mm"};
const STR *const InchesStr[]        = {"in","in","in","in","in"};   
const STR *const HertzStr[]         = {"Hz","Hz","Hz","Hz","Hz"};
const STR *const Watt[]             = {"W","W","W","W","W"};
const STR *const NewtonsStr[]       = {"N","N","N","N","N"};
const STR *const PoundsStr[]        = {"Lbs","Lbs","Lbs","Lbs","Lbs"};   
const STR *const JoulesStr[]        = {"J","J","J","J","J"};
const STR *const Khz20Str[]         = {"20 kHz","20 kHz","20 kHz","20 kHz","20 kHz"};
const STR *const Khz15Str[]         = {"15 kHz","15 kHz","15 kHz","15 kHz","15 kHz"};
const STR *const Khz30Str[]         = {"30 kHz","30 kHz","30 kHz","30 kHz","30 kHz"};
const STR *const Khz40Str[]         = {"40 kHz","40 kHz","40 kHz","40 kHz","40 kHz"};
const STR *const Khz60Str[]         = {"60 kHz","60 kHz","60 kHz","60 kHz","60 kHz"};
const STR *const UnitM[]            = {"Metric","Metrisch","Metrico","Metrico","Metr."};
const STR *const UnitE[]            = {"USCS","USCS","USCS","USCS","USCS"};   
const STR *const High24V[]          = {"High 24V","24V High","Alto 24V","24V Alto","Haut 24V"};
const STR *const Low0V[]            = {"Low 0V","0V Low","Baj 0V","0V Basso","Bas 0V"};
const STR *const MainStrt[]         = {"Main","Haupt","Principal","Principale","Princip."};
const STR *const RunStrt[]          = {"Run","Schweissen","Ejecutar","Esegui","Exe"};
const STR *const CurrentDUPSPreset[]= {"Current DUPS Preset #","Aktueller DUPS Parameter #","FAUD  Preseleccionada num","Predisposizione # DUPS corrente","Preset GUD Actuel"};
const STR *const WeldFunctions[]    = {"WELD FUNCTIONS","SCHWEISSFUNKTIONEN","FUNCIONES SOLD","FUNZIONI SALD.","FONCTIONS SOUD"};
const STR *const PhaseLoop[]        = {"Phase Loop","Phasenschleife","Bucle Fase","Loop di fase","Bcle Phase"};
const STR *const AmpLoopC1[]        = {"Amp Loop C1","Amplituden Schleife C1","Lazo Amp C1","Loop amp C1","Bcle Amp C1"};
const STR *const WeldHigh[]         = {"Weld High","Schweissung High","Soldadura Alta","Salda alto","Soud Haut"};
const STR *const PhaseLimit[]       = {"Phase Limit","Phasengrenze","Limite Fase","Limite di fase","Lim. Phase"};
const STR *const PhaseLoopCF[]      = {"Phase Loop CF","Phasenschleife CF","Bucle Fase CF","Loop di fase CF","Bcle Phase CF"};
const STR *const AmpLoopC2[]        = {"Amp Loop C2","Amplituden Schleife C2","Lazo Amp C2","Loop amp C2","Bcle Amp C2"};
const STR *const WeldLow[]          = {"Weld Low","Schweissung Low","Soldura Baja","Salda basso","Soud Bas"};
const STR *const HornScanFunctions[]= {"HORN SCAN FUNCTIONS","HORN SCAN FUNKTIONEN","FUN. DIAGNOSIS SONO","FUNZIONI ANALISI SONOTRODO","FONCTIONS SCAN SONO"};
const STR *const FreqStart[]        = {"Freq Start","Frequenzstart","Inic Frec","Avvio freq","Freq Debut"};
const STR *const FreqEnd[]          = {"Freq End","Frequenzende","Fin Frec","Interr freq","Freq Fin."};
const STR *const FreqLow[]          = {"Freq Low","Frequenz Low","Frec Baj","Bassa fre","Freq Basse"};
const STR *const FreqHigh[]         = {"Freq High","Frequenz High","Frec Alta","Alta freq","Freq Hte"};
const STR *const HzStr[]            = {"Hz","Hz","Hz","Hz","Hz"};
const STR *const FreqStr[]          = {"Freq","Frequenz","Frec","Freq.","Freq"};                     
const STR *const TimeDelay[]        = {"Time Delay","Zeitverzoegerung","Retardo Tiempo","Ritardo tempo","Dur Delai"};
const STR *const SeekFunctions[]    = {"SEEK FUNCTIONS","SUCH-FUNKTIONEN","BUSC FUNCIONES","FUNZIONI SEEK","FONCT. DE RECH"};
const STR *const SoftwareDIPSettings[] = {"SOFTWARE DIP SETTINGS","SOFTWARE-DIP-EINSTELLUNGEN","Ajustes Software DIP","Impostazioni software DIP","Reglages DIP Logiciel"};
const STR *const OtherDUPSPresets[] = {"OTHER DUPS PRESETS","ANDERE DUPS PARAMETER","Otras Presel FAUD","Altri preset DUPS","Autres Preset GUD"};
const STR *const Comments[]         = {"Comments:","Anmerkung:","Notas:","Commenti:","Comment.:"};
const STR *const SecondsStr[]       = {"s","s","s","s","s"}; 
const STR *const Inductive[]        = {"Inductive","Induktiv","Inductivo","Induttivo","Inductif"};
const STR *const Capacitive[]       = {"Capacitive","Kapazitiv","Capacitivo","Capacitivo","Capacitif"};
const STR *const HornScanGraph[]    = {"Horn Scan Graph","Horn Scan Grafik","Graf. Diagnosis Sono","Graf. analisi sonotrodo","Graph Scan Sono"};
const STR *const Frequency[]        = {"Frequency (Hz)","Frequenz (Hz)","Frecuencia(Hz)","Frequenza (Hz)","Frequence (Hz)"};
const STR *const Current1[]         = {"Current","Aktuell","Corrnte","Corrente","Actuel."};
const STR *const Notes[]            = {"NOTES","ANMERKUNG","NOTAS","NOTE","NOTES"};
const STR *const Converter[]        = {"Converter","Konverter","Convertidor","Convertitore","Convertis"};
const STR *const DUPSSetup[]        = {"DUPS SETUP","DUPS EINRICHTEN","Config FAUD","Setup DUPS corrente","Conf. GUD"};
const STR *const Locked[]           = {"  Locked","  Gesperrt",   "  Bloqueado","  Bloccato","  Verrou"};
const STR *const Saved[]            = {"  Saved", "  Gespeichert","  Guardado", "  Salvato", "  Sauveg."};
const STR *const Avail[]            = {"  Avail", "  Verfuegbar", "  Dispo",    "  Dispon.", "  Dispo"};   
const STR *const ResonanceFreq[]    = {"Resonance Frequencies:","Resonanzfrequenzen:","Frecuencia Resonancia:","Frequenze di risonanza:","Frequences de Reson.:"};
const STR *const English[]          = {"English","Englisch","Ingles","Inglese","Anglais"};
const STR *const German[]           = {"German","Deutsch","Aleman","Tedesco","Allemand"};
const STR *const Spanish[]          = {"Spanish","Spanisch","Espanol","Spagnolo","Espagn."};
const STR *const Italian[]          = {"Italian","Italienisch","Italiano","Italiano","Italien"};
const STR *const French[]           = {"French","Franzoesisch","Frances","Francese","Francais"};
const STR *const AlarmStr[]         = {"Alarm","Alarm","Alarm","Allarme","Alarme"};
const STR *const PresetStr[]        = {"Preset","Parameter","Presel","Preset","Preset"};
const STR *const ExtStr[]           = {"Ext","Ext","Ext","Ext","Ext"};
const STR *const OffStr[]           = {"Off","Aus","0","0","0"};
const STR *const StrFreqSeries[]    = {"Series F(Hz) =","Series F(Hz) =","Series F(Hz) =","Series F(Hz) =","Series F(Hz) =" };
const STR *const StrFreqParallel[]  = {"Parallel F(Hz) =","Parallel F(Hz) =","Parallel F(Hz) =","Parallel F(Hz) =","Parallel F(Hz) =" };
const STR *const TimeModeStr[]      = {"Time Mode","Zeit Modus","Modo Tiem","Modal Time","Mode Temps"  };
const STR *const EnergyModeStr[]    = {"Energy Mode","Energie Modus","Modo Energi","Modal Energi","Mode Energie"  };
const STR *const PkPowerModeStr[]   = {"PeakPower Mode","Sp.Leistung Modus","Modo Pico Poten","Modal Picco Pot.","Mode Pui.-Crete"  };
const STR *const CollapseModeStr[]  = {"Collapse Mode","Weg relativ Modus","Modo Colapso  ","Modal Collasso","Mode D. Relat"  };
const STR *const AbsoluteModeStr[]  = {"Absolute Mode","Weg absolut Modus","Modo Absoluto ","Modal Assoluta","Mode D.Abs"  };
const STR *const GroundDetectModeStr[]= {"Ground Detect Mode","Metallkont. Modus","Modo Detecc Tierra","Modal Ground Detect","Mode Detec.Masse"  };
const STR *const ContinuousModeStr[]= {"Continuous Mode","Kontinuier Modus","Modo Continuo","Modal Continua", "Mode Continu"  };    

/**------------------------------------------**
 **      CONFIGSETUP CONSTANT STRING         **
 **------------------------------------------**/

const STR *const Config0001[]= {"WELDER SETUP CONDITIONS","SCHWEISSEINRICHTUNG ZUSTAND","COND CONFIG SOLDADOR","CONDIZIONI IMPOST. SALDATURE","CONFIGUR. SYST. SOUD"};
const STR *const Config0004[]= {"PS Lifetime Counter","Generator Lebensdauer Zaehler","Contador Durac F/A","Contatore durata generatore","Compt. Dur Vie Gene"};
const STR *const Config0005[]= {"Overloads","Ueberlast","Sobrecarga","Sovraccarichi","Surcharges"};
const STR *const Config0006[]= {"General Alarm","Allgemeiner Alarm","Alarma Gral","Allarme generale","Alar. Gener."};
const STR *const Config0007[]= {"Actuator Lifetime","VE Lebensdauer","Duracion actuador","Vita attuatore","Duree vie actuator"};
const STR *const Config0008[]= {"Frequency","Frequenz","Frecuencia","Frequenza","Frequence"};
const STR *const Config0009[]= {"Power Supply","Generator","Fuente Alimtacion","Alimentatore","Generateur"};
const STR *const Config0010[]= {"Actuator","VE","Actuador","Attuatore","Actuator"};
const STR *const Config0011[]= {"Control Level","Steuer Level","Nivel Control","Livello controllo","Niveau Comde"};
const STR *const Config0012[]= {"SW Version","SW-Version","Version SW","Versione int.","Version Lg"};
const STR *const Config0013[]= {"                ","                ","                ","                ","                "};
const STR *const Config0014[]= {"PS Serial Number","Generator Seriennummer","Numero Serie F/A","Num serie generatore","Num Serie Generat"};
const STR *const Config0015[]= {"Act Serial Number","VE Seriennummer","Nu de Serie Actuador","Numero di serie attuatore","Numero Serie Actuator"};
const STR *const Config0016[]= {"Cylinder Diameter","Zylinderdurchmesser","Diametro Cilindro","Diametro cilindro","Diametre Cylindre"};
const STR *const Config0017[]= {"Cylinder Stroke","Zylinderhub","Carrera Cilindro","Corsa cilindro","Course Cylindre"};
const STR *const Config0018[]= {"Language","Sprache","Idioma","Lingua","Langue"};
const STR *const Config0019[]= {"Units","Einheiten","Unidades","Unita","Untes"};
const STR *const Config0020[]= {"Password","Passwort","Contrasena","Password","Mt de passe"};
const STR *const Config0022[]= {"Preset Count","Parameter Zaehler","Contd Presel","Preset Cont.","Compt Preset"};
//const STR *const Config0023[]= {"Serial Port","Serielle Schnittstelle","Puerto Serie","Porta seriale","Port Serie"};
const STR *const Config0023[]= {"RS232","Serielle Schnittstelle","Puerto Serie","Porta seriale","Port Serie"};
const STR *const Config0024[]= {"Baud Rate","Baudrate","Tasa Baud","Baud rate","Taux Baud"};
const STR *const Config0025[]= {"Software Hand Shake","Software Hand Shake","Conectividad softwr","Software Hand Shake","Software Hand Shake"};   
const STR *const Config0026[]= {"Echo","Echo","Eco","Eco","Echo"}; 
const STR *const Config0027[]= {"General Alarm Reset Required","Allgemeiner Alarm Reset erforderlich","Preciso Reset Alarma Gral","Richiesta reset allarme generale","RAZ Alarme Generale Requise"};
const STR *const Config0028[]= {"Trigger Beeper","Triggersignal akustisch","S Acus Disparo","Segnal Trigger","Biper Trigger"};
const STR *const Config0028A[]={"Release Beeper","Release Beeper","Release Beeper","Release Beeper","Release Beeper" };
const STR *const Config0029[]= {"Error Beeper","Fehlersignal","S Acus Error","Segnal errore","Biper Erreur"};
const STR *const Config0030[]= {"Alarm Beeper","Alarmsignal","Alarma Acust","Segnale allarme","Biper Alarme"};
const STR *const Config0031[]= {"Hand Held System","Hand Held System","Hand Held System","Hand Held System","Hand Held System"};   
const STR *const Config0032[]= {"Amplitude Control","Amplitudensteuerung","Control Amplitud","Controllo ampiezza","Comde Amplitude"};
const STR *const Config0033[]= {"Actuator Clear Output","VE Loesche Ausgang","Salida Actuador Libre","Uscita apertura attuatore","Sortie Deg. Actuator"};
const STR *const Config0033A[]={"Distance","Weg","Distancia","Distanza","Distance"};
const STR *const Config0034[]= {"Upper Limit","Oberer Grenzwert","Lte Suprior","Limite superiore","Limite Sup."};
const STR *const Config0035[]= {"Trigger Switch","Trigger Schalter","Conmut Puerta/Dspro","Porta/Int. trigger","Contact. Porte/Trigg"};
const STR *const Config0036[]= {"Lower Limit","Unterer Grenzwert","Lte Infer","Lim inf","Lim. Inf."};
const STR *const Config0037[]= {"MPS Switch","MPS Schalter","Conmut MPS","MF fallito","Inter. Multifonctions"};
const STR *const Config0037A[]={"MPS Switch Flag1","MPS Schalter Flag1","MPS Switch Flag1","MPS Switch Flag1","Inter. Multifonctions Flag1"};   
const STR *const Config0037B[]={"MPS Switch Flag2","MPS Schalter Flag2","MPS Switch Flag2","MPS Switch Flag2","Inter. Multifonctions Flag2"};   
const STR *const Config0038[]= {"Actuator Return on PS","VE zurueck zu Generator","Retorno actuador a FA","Ritorno attuatore su PS","Retour actuator sur PS"};
const STR *const Config0039[]= {"Pretrigger on PS","Pretrigger on PS","Predispro en FA","Pre-triger su PS","Pretrigger sur PS"};
const STR *const Config0040[]= {"Rapid Traverse on PS","Rapid Traverse on PS","Vel. rapida en FA","Spost. rapido su PS","Course rapide sur PS"}; 
const STR *const Config0041[]= {"Weld Scale","Schweiss-Skala","Escal Sold","Scala sald.","Ech. Soud"};
const STR *const Config0042[]= {"Test Scale","Test Skala","Escala Prueba","Scala Test","Ech. Test"};
const STR *const Config0043[]= {"Digital Filter","Digitalfilter","Filtro Digital","Filtro digitale","Filtre Digital"};
const STR *const Config0044[]= {"Frequency Offset","Freq.aenderung","Desvio Frecuenc","Offset frequenza","Decal. Frequence"};
const STR *const Config0046[]= {"Missing Part Output","Ausgang Fehlendes Teil","Salida parte perdid","Parte non espulsa","Sortie Piece Manquante"};
const STR *const Config0047[]= {"Advance Counters","Zaehler vorsetzen","Contadores avnce","Contatori avanzati","Avancer compteurs"};
const STR *const Config0049[]= {"Printer","Drucker","Impresora","Stampante","Imprmte"};
const STR *const Config0050[]= {"Setup on Alarm","Einrichten bei Alarm","Confg si Alarm","Setup su allarme","Confg sur Alarme"};
const STR *const Config0051[]= {"Setup on Sample","Einrichten bei Auswahl","Confg si Muestra","Setup su campione","Confg sur Echant"};
const STR *const Config0052[]= {"Weld History on Alarm","Schweiss-Datenbank bei Alarm","Historl Alarma Sold","Storia saldature su allarme","Hist. Soud sur Alarme"};
const STR *const Config0053[]= {"Weld History on Sample","Schweissdatenbank bei Auswahl","Historl Muestra Sold","Storia saldature su campione","Hist. Soud sur Echant"};
const STR *const Config0054[]= {"Weld Data on Alarm","Schweissdaten bei Alarm","Dat Alarma Sold","Dati sald. su allarme","Don. Soud sur Alarme"};

const STR *const Config0055[]= {"Weld Data on Sample","Schweissdaten bei Auswahl","Dat Muestra Sold","Dati sald. su campione","Don. Soud sur Echant"};
const STR *const Config0056[]= {"Power Graph on Alarm","Leistung Grafik bei Alarm","Grafico Alarma Pot","Grafico potenza su allarme","Graph Puis sur Alarme"};
const STR *const Config0057[]= {"Power Graph on Sample","Leistung Grafik bei Auswahl","Grafico Muestra Pot","Grafico potenza su campione","Graph Puis sur Echant"};
const STR *const Config0058[]= {"Amplitude Graph on Alarm","Amplituden-Grafik bei Alarm","Grafico Alarma Amplitud","Grafico ampiezza su allarme","Graph Amplitude sur Alarme"};
const STR *const Config0059[]= {"Amplitude Graph on Sample","Amplituden-Grafik bei Auswahl","Grafico Muestra Amplitud","Grafico ampiezza su campione","Graph Amplitude sur Echant"};
const STR *const Config0060[]= {"Frequency Graph on Alarm","Frequenzgrafik bei Alarm","Grafico Alarma Frecuencia","Grafico frequenza su allarme","Graph Frequence sur Alarme"};
const STR *const Config0061[]= {"Frequency Graph on Sample","Frequenzgrafik bei Auswahl","Grafico Muestra Frecuencia","Grafico frequenza su campione","Graph Frequence sur Echant"};
const STR *const Config0062A[]={"Col Distance Graph on Alarm","Weg rel. Grafik bei Alarm","Grafico Alarma Distancia col","Grafico distanza col su allarme","Graph Distance Rel. sur Alarme"}; 
const STR *const Config0062B[]={"Col Distance Graph on Sample","Weg rel. Grafik bei Auswahl","Grafico Muestra Distancia col","Grafico distanza col su campione","Graph Distance Rel. sur Echant"};
const STR *const Config0064[]= {"Velocity Graph on Alarm","Geschwindigkeit Grafik bei Alarm","Grafico Alarma Velocidad","Grafico velocita su allarme","Graph Vitesse sur Alarme"};
const STR *const Config0065[]= {"Velocity Graph on Sample","Geschwindigkeit Grafik bei Auswahl","Grafico Muestra Velocidad","Grafico velocita su campione","Graph Vitesse sur Echant"};
const STR *const Config0066[]= {"Force Graph on Alarm","Kraft Grafik bei Alarm","Grafico Alarma Fuerza ","Grafico forza su allarme","Graph Force sur Alarme"};
const STR *const Config0067[]= {"Force Graph on Sample","Kraft Grafik bei Auswahl","Grafico Muestra Fuerza ","Grafico forza su campione","Graph Force sur Echant"};
const STR *const Config0068[]= {"Printer","Drucker","Impresora","Stampante","Imprmte"};
const STR *const Config0069[]= {"Formfeed","Einfuehrung","Intrform","Alimentazionepagina","Form. Feuille"};
const STR *const Config0070[]= {"Welds per Page","Schweissung pro Seite","Solds por Pag","Sald. per pag.","Soud par Page"};
const STR *const Config0071[]= {"Missing Part","Fehlendes Teil","Falta Pieza","Parti mancanti","Piece Manquante"};
const STR *const Config0072[]= {"Missing Part Abort Min", "Fehlendes Teil Abbruch Min","Cancel Min Parte Perdid","Annulla parte mancante min.","Arret Piece Manqte Min"};
const STR *const Config0073[]= {"Missing Part Abort Max","Fehlendes Teil Abbruch Max","Cancel Max Parte Perdid","Annulla parte mancante max.","Arret Piece Manqte Max"};
const STR *const Config0074[]= {"Horn Down Force","Horn Ab Kraft","Fuerza sono. Abajo","Forza riduzione sonotrodo","Force desc. sonotr"};
const STR *const Config0075[]= {"Horn Downspeed","Horn Abfahrtsgeschwindigkeit","Vel desc. Sono.","Decelerazione sonotrodo","Vit. Desc. Sonotr."};
const STR *const Config0076[]= {"Multi-Purpose Switch","MPS","Multi-Purpose Switch","Multi-Purpose Switch","Multi-Purpose Switch"};   
const STR *const Config0077[]= {"Actuator Counter","VE Zaehler","Contador actuadr","Contatore attuatore","Compt. actuator"};
const STR *const Config0078[]= {"Printing","Drucken","Imprimiendo","Stampa","Impressn"};
const STR *const Config0079[]= {"Page Size","Seitengroesse","Tam Pagin","Dimens. pag.","Format Pg"};
const STR *const Config0080[]= {"Start Screen","Start Bild","Inic Pantlla","Avvia Screen","Ecran Demarr"};
const STR *const Config0081[]= {"Digital Tune","Digitale Abstimmung","Sint Digital","Sint. Digitale","Accord. Digit."};
