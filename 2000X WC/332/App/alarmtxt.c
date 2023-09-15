/* $Header:   D:/SWLab/VMdb/2000Series/App/ALARMTXT.C_V   1.86   Feb 23 2005 18:52:58   ATali  $ */
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

   Filename: alarmtxt.c                        

   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #  Date      Author   Description
   ==========  ========  =======  ===========
      1.0      10/11/96  PhilJ    Initial Version
      2.0      10/14/96  LAM      added system fault22
      3.0      10/16/96  PhilJ    added StrSystemFault & StrAlarmMsg
      4.0      10/19/96  PhilJ    Updated Alarmtxt to spec R:0.E
      5.0      10/24/96  PhilJ    Added StrGenAlarm_90 and 91.
      6.0      10/25/96  PhilJ    Added StrGenAlarm_65 thru 80.
      7.0      10-30-96  BEKymer  Changed StrSysFault_20 text
                                  Added system faults msg's to 63
      8.0      11/14/96  PhilJ    Added StrGenAlarm_81 & 82.
      8.1      11/15/96  PhilJ    Changed sign in StrGenAlarm_81.
      8.2      11/21/96  PhilJ    Added StrGenAlarm_46.
      8.3      01-23-97  PhilJ    Updated alarms per BETA Rel.1
      8.4      02-25-97  LAM      fixed reject time limits      
      8.5      04-08-97  PhilJ    Removed StrGenalarm_40 & 45. Added
                                  StrWarning_5 & 6.
      8.6      04-10-97  PhilJ    Fixed text in SystemFault strings
                                  20 & 21.
      8.7      04-15-97  PhilJ    Fixed one more time text in
                                  SystemFault strings 20 & 21.
      8.8      04-23-97  PhilJ    Chngd StrSysFault_4.
      8.9      04-29-97  BEKymer  Added text for Warning 7
      9.0      05-29-97  LAM      Added text for Warning 8
     10.1.18   07.01.97  J.B.     Changed alarm codes
     10.1.20   07-11-97  BEKymer  New alarm strings
     10.1.21   07-24-97  BEKymer  Remove old alarm strings
     10.1.22   07-30-97  BEKymer  Add StrSetupAlarms, remove old
                                  alarm strings
     10.1.23   08-01-97  BEKymer  Change text for EQ_4
                                  Make Alarm ** text (no s)
                                  Separate message for each alarm group
     10.1.24   08-12-97  BEKymer  Add StrEQ_4A, StrEQ_1A, StrEq_1B text

     10.1.24   08-22-97  NWu      Modified Alarm Msg. to match Alarm Doc1.01
     1.26      09-02-97  BEKymer  Change StrTime from 'At Time'
                                  to '@ Time'.
                                  Added StrCM12info
     1.27      09-08-97  BEKymer  File checked & cleaned up for unit test
     1.28      ?
     1.29      10.30.97  JBerman  Reject/Suspect Alarm. Fixed DCS#1957.
                                  Changed the following strings:
                                  StrM1F_0[] = "REJECT ALARM";
                                  StrM1F_1[] = "SUSPECT ALARM";
     1.30      11-03-97  BEKymer  Changed text for StrEQ_4A & B, Added StrEQ_4C
     1.31      01-20-98  PaulG    Added printer offline to SE270.
     1.32      02-03-98  BEKymer  Moved NC5 to CM14, expanded Ground Detect
                                  Cutoff to NC12 & CM2, and External Cycle
                                  Abort to NC7 & CM15.
     1.33      02-17-98  BEKymer  Added alarms CM16-CM20
                                  Added Actual string for Amplitude
     1.34      03-10-98  LAM      chged ground detect cutoff to abort
     1.35      03-10-98  LAM      chged ground detect cutoff to abort(rel2.5) only
     1.36      03-10-98  BEKymer  Add new string StrNC_1A
     1.37      04-17-98  LAM      chged ground detect cutoff to abort
     1.38      04-29-98  BEKymer  Added text for alarms W1, W8 and W10.
                                  Added text for alarms SE171 - SE177.
     1.39      05-20-98  BEKymer  Moved Energy Not Reached alarm from PR15
                                  to CM21  DCS # 2494
                                  Added EQ24 - Actuator Type
     1.40      05-27-98  BEKymer  Added SE120 - Missing Part Crossed
     1.41      06-12-98  BEKymer  Added StrEQ_4D string for alarm EQ4
     1.42      06-17-98  BEKymer  Moved CA1 to EQ20
     1.43      06-22-98  BJB      Changed Max Force text to Weld Force.
     1.44      06-23-98  BEKymer  Changed text for alarms SE13, SE14, SE99
                                  SE100, SE101, SE102  (Frc->F), SE258
     1.45      09-17-98  BEKymer  Add new string to handle alarm EQ4 on AE
     1.46      11-23-98  BEKymer  Add CM22 text (at the last minute, again)
                                  and StrActualWeldForce for addel info
     1.47      11-25-98  LAM      changed CM22 text
     1.48      05-12-99  OFI      Changed SE245,SE260,SE261,SE262,SE277,CM13,CM23 text
     1.49      05-27-99  OFI      Creted new strings StrMaximumForce,
                                  StrSE277GoToHornDown,
                                  StrSE277AdjSystemRegulatorconst,StrSE268ErrorCode 
     1.49.1.1  07-07-99  JZ       edited EQ25
     1.51      09-01-99  JZ       changed StrSE277GoToHornDown to Pres Horndown
     1.52      11-04-99  OFI      converted tabs into spaces
     1.53      02-09-00  OFI      Emptied out strings that wwere displayd with alarms SE22,23,68,69
     1.54      04-05-00  JZ       Emptied out string that was displayd with alarm SE258
                                  merged Lang to trunk
     1.55      05-20-00  SCM      Changed String definition to accomodate foreign language 
                                  definition.
     1.56      07-12-00  BEKymer  Added foreign language strings
     1.58      07-18-00  JLH      Added overload text strings.
     1.59      08-01-00  BEKymer  Fix string length of StrAlarmMsgS, StrAlarmMsg,
                                   StrAlarmOverload,

                                  Temp truncated strings: StrSE_1, StrSE_2, StrSE_3, StrSE_4,
                                   StrSE_5,  StrSE_6,  StrSE_7,  StrSE_8,  StrSE_9,
                                   StrSE_10, StrSE_11, StrSE_12, StrSE_44, StrSE_45,
                                   StrSE_49, StrSE_50, StrSE_51, StrSE_58, StrSE_72,
                                   StrSE_73, StrSE_74, StrSE_75, StrSE_76, StrSE_77,
                                   StrSE_78, StrSE_79, StrSE_80, StrSE_81, StrSE_82,
                                   StrSE_83, StrSE_84, StrSE_85, StrSE_86, StrSE_87,
                                   StrSE_88, StrSE_89, StrSE_138, StrSE_139, StrSE_140,
                                   StrSE_141, StrSE_142, StrSE_143, StrSE_144, StrSE_145,
                                   StrSE_146, StrSE_147, StrSE_148, StrSE_149, StrSE_150,
                                   StrSE_151, StrSE_152, StrSE_153, StrSE_154, StrSE_155,
                                   StrSE_161, StrSE_162, StrSE_163, StrSE_164, StrSE_165,
                                   StrSE_166, StrSE_167, StrSE_168, StrSE_169, StrSE_170,
                                   StrSE_171, StrSE_172, StrSE_173, StrSE_174, StrSE_175,
                                   StrSE_176, StrSE_177, StrSE_178, StrSE_179, StrSE_180,
                                   StrSE_181, StrSE_182, StrSE_183, StrSE_184, StrSE_185,
                                   StrSE_186, StrSE_187, StrSE_193, StrSE_194, StrSE_195,
                                   StrSE_196, StrSE_197, StrSE_198, StrSE_199, StrSE_208,
                                   StrSE_209, StrSE_210, StrSE_211, StrSE_212, StrSE_213,
                                   StrSE_214, StrSE_215, StrSE_216, StrSE_217, StrSE_218,
                                   StrSE_219, StrSE_225, StrSE_226, StrSE_227, StrSE_228,
                                   StrSE_229, StrSE_230, StrSE_231, StrSE_232, StrSE_233,
                                   StrSE_234, StrSE_235, StrSE_236, StrSE_237, StrSE_238,
                                   StrSE_239, StrSE_240, StrSE_241, StrSE_242, StrSE_243,
                                   StrSE_247, StrSE_248, StrSE_250, StrSE_260, StrSE_262,
                                   StrSE_264, StrSE_265, StrSE_266, StrSE_267, StrSE_270,
                                   StrNC_4,   StrNC_6,   StrNC_7,   StrNC_8,   StrNC_12,
                                   StrNC_12,  StrOL_2,   StrOL_6,   StrOL_8,   StrEQ_2,
                                   StrEQ_3,   StrEQ_6,   StrEQ_9,   StrEQ_16,  StrEQ_18,
                                   StrEQ_23,  StrCM_2,   StrCM_14,  StrCM_15,  StrCM_21,
                                   StrCM_22,  StrWA_2,   StrWA_3,   StrWA_8,   StrPR_11,
                                   StrPR_12,
                                   
      1.60        08-15-00       DJL        Made changes to the file from the new 8-03 Omnilangual file
      1.61        08-15-00       LAM        shortened overload DUPS titles
      1.62        08-16-00       DJL        Took away some to the comments that Barry made about the strings
                                            that were to long.
     1.63        08-16-00        DJL        fixed minor synthax errors
     1.64        08-16-00        DJL        changed OVERLOAD back to O/L 
     1.65        08-23-00        DJL        Made changes from Omnilingua's final version of alarmtxt.c       
     1.66        09-06-00        BEKymer    Made Overload = O/L in English
     1.67        10-04-00        BEKymer    Change all manual references from 7.6 to 7.5
     1.68        10-16-00        AT         2519 - changed StrAlarmPhaseOverload to phase/power (#3620)
                                            fixed StrSE_82 - had only 4 languages
     1.69        10-20-00        AT         Cut StrAlarmPhaseOverload to 13 characters (#3620)
     1.70        11-01-00        AT         Alarm menu title fixes.
     1.71        11-06-00        AT         Spanish fixes
     1.72        11-14-00        AT         More translations
     1.74        03-08-01        LAM/AT     french update
     1.75        03-14-01        LAM/AT     french & german update   
     1.76        03-20-01        LAM/AT     all foreign language updates
     1.77        04-23-01        LAM        added text for Preset Not Available SE46 Alarm 
     1.77.1.0    11-21-02        SCM        Made changes to various strings for German Language as part 
                                            of version 8.07.
     1.77.1.1    01-15-03        SCM        Made further changes to various strings for German Language 
                                            as part of version A808.                                            
     1.78        04-11-03        BEKymer    Move 1.77.1.1 to tip as 1.78 for build 8.10
     1.79        04-06-04        VSharma    Changed StrSE_289,StrSE_290,StrSE_291,StrSE_293,StrSE_294
                                             StrSE_292,StrNC_13,StrNC_14,StrNC_15,StrOL_10,StrCM_17,
                                             StrWA_11.
                                            Added StrCM_17A,StrCM_17B,StrCM_17C.
     1.80        04-19-04        VSharma    Modified text for EQ19 alarm.
     1.81        05-04-04        VSharma    Changed StrSE_295.
     1.82        06-17-04        VSharma    Made many language updates for Ver9.00 strings.                                            
     1.83        07-26-04        BEKymer    Remove EQ19 J3-1 Configuration error.
     1.84        07-29-04        JOY        Modified string StrSE_296[].
     1.85        08-24-04        JOY        String 'SV Interlock' is replaced to 'External Start'.
     1.86        02-23-05        AT         Move all data into .lang section for 4-flash build
     
     
*/                                  
/*------------------------------- DESCRIPTION ------------------------------*/
 
/*    This file will contain all the text for any given language.           */
/*    ENGLISH version.                                                      */


/*------------------------------ INCLUDE FILES -----------------------------*/

#include "portable.h"
#include "menu.h"

/* This section will go into flash that starts at 2MB. */
#pragma section CONST  ".lang"
#pragma section STRING ".lang"
#pragma section CODE   ".lang"

/*------------------------------ EXTERNAL DATA -----------------------------*/


/*------------------------------ LOCAL DEFINES -----------------------------*/
                                   

/*------------------------- LOCAL TYPE DECLARATIONS ------------------------*/


/*------------------------------ GLOBAL DATA -------------------------------*/
/*                      (scope is global to ALL files)                      */

/******************************************************************************/
/*   The languages will be defined in the following order:                    */
/*       English                                                              */
/*       German                                                               */
/*       Spanish                                                              */
/*       Italian                                                              */
/*       French                                                               */
/*                                                                            */
/******************************************************************************/


const STR *const StrAlarmStart[]   = { "  **   ",
                                       "  **   ",
                                       "  **   ",
                                       "  **   ",
                                       "  **   "  };

const STR *const StrAlarmMsgS[]  =  {  " ALARMS **   ",
                                       " ALARME **   ",
                                       " ALARMAR **  ",
                                       " ALLARMES ** ",
                                       " ALARMES **  "  };

const STR *const StrAlarmMsg[]   =  {  " ALARM  **   ",
                                       " ALARM  **   ",
                                       " ALARMA  **  ",
                                       " ALLARME  ** ",
                                       " ALARME  **  "  };


const STR *const StrAlarms[]      = {  "ALARMS",
                                       "ALARME",
                                       "ALARMAR",
                                       "ALLARMES",
                                       "ALARMES"  };

const STR *const StrSetupAlarms[] = {  "SETUP ALARMS",
                                       "EINR. ALARME",
                                       "CONF ALARMAR",
                                       "SETUP ALLARM",
                                       "CONFG ALARM"  };  



const STR *const StrActualTime[]  = {  "Actual(&)",
                                       "Akt.(&)",
                                       "Actual(&)",
                                       "Reale(&)",
                                       "Reelle(&)"  };

const STR *const StrActualEnergy[] = { "Actual(&)",
                                       "Akt.(&)",
                                       "Actual(&)",
                                       "Reale(&)",
                                       "Reelle(&)"  };

const STR *const StrActualDistance[] = {
                                       "Actual(&&)",
                                       "Akt.(&&)",
                                       "Actual(&&)",
                                       "Reale(&&)",
                                       "Reelle(&&)"  };

const STR *const StrActualPower[]  = { "Actual(&)",
                                       "Akt.(&)",
                                       "Actual(&)",
                                       "Reale(&)",
                                       "Reelle(&)"  };

const STR *const StrActualForce[]  = { "Actual(&&)",
                                       "Akt.(&&)",
                                       "Actual(&&)",
                                       "Reale(&&)",
                                       "Reelle(&&)"  };

const STR *const StrActualWeldForce[] = {
                                       "End Force(&&)",
                                       "Endkraft(&&)",
                                       "Fuerz Fin(&&)",
                                       "Forza Fin(&&)",
                                       "Force Fin(&&)"  };

const STR *const StrActualFreq[]   = { "Actual(&&)",
                                       "Akt.(&&)",
                                       "Actual(&&)",
                                       "Reale(&&)",
                                       "Reelle(&&)"  };

const STR *const StrActualAmp[]    = { "Actual Amp(&)",
                                       "Akt. Ampl.(&)",
                                       "Actual Amp(&)", 
                                       "Actual Amp(&)", 
                                       "Amp Effect(&)"  }; 

const STR *const StrActualAmpA[]   = { "Actual Amp A(&)",
                                       "Akt. Ampl. A(&)",
                                       "Amp actual A(&)",
                                       "Amp A effetv(&)",
                                       "Amp Effect A(&)"  };

const STR *const StrActualAmpB[]   = { "Actual Amp B(&)",
                                       "Akt. Ampl. B(&)",
                                       "Amp actual B(&)",
                                       "Amp B effetv(&)",
                                       "Amp Effect B(&)"  };

const STR *const StrCM12info[]     = { "Ext sig not Received",
                                       "Ext. Sig. nicht empf",
                                       "No se recibe sol ext",
                                       "Segnal est non ricev",
                                       "Sig Ext non recu"  };




/*  -----  These string are still needed with the new alarms  -----  */

/* SUSPECT/REJECT LIMIT TEXT SUBMENUS */
const STR *const StrM1F_0[]        = { "REJECT ALARM",
                                       "AUSSCH ALARM",
                                       "RECHZ ALARMA",
                                       "RES ALLARME",
                                       "ALARM REJET"  };

const STR *const StrM1F_1[]        = { "SUSPECT ALARM",
                                       "PRUEFE ALARM",
                                       "SOSPCH ALARMA",
                                       "ALLARM SOSP",
                                       "ALARME SUSP."  }; 


const STR *const StrRejAlarm[]     = { "REJ ALARMS",
                                       "A ALARME",
                                       "RECH ALRMS",
                                       "RES ALLARM",
                                       "ALARM. REJ"  };

const STR *const StrSuspAlarm[]    = { "SUSP ALARMS",
                                       "P ALARME",
                                       "SOSP ALARMS",
                                       "ALLARMI SOS",
                                       "ALARM. SUSP."  };


const STR *const StrAlarmOverload[]= { "OVERLOAD            ",
                                       "UEBERLAST           ",
                                       "SOBRECARGA          ",
                                       "SOVRCCRC            ",
                                       "SURCHRGE            "  };

const STR *const StrTime[]        = {  "@ Time(&)",
                                       "@ Zeit(&)",
                                       "@ Tiem(&)",
                                       "@ Temp(&)",
                                       "@ Tps(&)"  };

const STR *const StrPkPwrOverload[]= { "Peak Power(&)",
                                       "Spitz.Lst.(&)",
                                       "Pico Potenc(&)",
                                       "Picco pot.(&)",
                                       "Pui. Crete(&)"  };

const STR *const StrDeltaFreq[]    = { "Freq Chg(&&)",
                                       "Freq.Aend.(&&)",
                                       "Cam Frec(&&)",
                                       "Cam freq(&&)",
                                       "Chg Freq(&&)"  };

const STR *const StrFreq1[]        = { "Freq (&&)",
                                       "Freq.(&&)",
                                       "Frec (&&)",
                                       "Freq (&&)",
                                       "Freq (&&)"  };

const STR *const StrTrigLost[]     = { "TRIGGER LOST        ",
                                       "TRIGGER VERL.       ",
                                       "DISPARO PERDIDO     ",
                                       "TRIG PERSO          ",
                                       "TRIGG PERDU         "  };




/*---------------  Here are all the new alarm strings  ---------------*/

const STR *const StrSE_0A []   = {     "Setup Alarm",
                                       "Alarm einr.", 
                                       "Conf alarma",
                                       "Setup allrm",
                                       "Confg Alarm"  };

const STR *const StrSE_0B []      = {  "1 See Manual",
                                       "1 Siehe Handbuch",
                                       "1 Ver Manual",
                                       "1 Ved Manual",
                                       "1 Cf. Manuel"  };

            /* Alarm SE259   */      
const STR *const StrSE_0C []   =   {   "section 7.5",
                                       "Abschn 7.5",
                                       "seccion 7.5",
                                       "sezione 7.5",
                                       "section 7.5"  };

const STR *const StrSE_0D []   = {     "Feature/Model Wrong",
                                       "Merkmal/Mod. falsch",
                                       "Error carac/modelo ",
                                       "Carat/Model errati",
                                       "Caracter/modle faux" };

/* Alarm EQ4     */
const STR *const StrEQ_4A []   = {     "1 Press Reset, then",
                                       "1 Reset, dann",
                                       "1 Pulse Reset, y   ",
                                       "1 Prem Reset, quind",
                                       "1 Press. Reset, puis"  };

/* Alarm EQ4     */
const STR *const StrEQ_4B []   =   {   "Test",
                                       "Test",
                                       "Test",
                                       "Test",
                                       "Test"  };

/* Alarm EQ4     */
const STR *const StrEQ_4D []   = {     "2 Recal Actuator",
                                       "2 Neukal. VE",
                                       "2 Recal actuador", 
                                       "2 Rical attuator",
                                       "2 Recal actuator"  }; 

/* Alarm EQ4 AED */
const STR *const StrEQ_4C []   = {     "3 See 7.5 in Manual",
                                       "3 Siehe 7.5 Handbuch", 
                                       "3 Ver 7.5 en Manual",
                                       "3 Ved 7.5 nl Manual",
                                       "3 Voir 7.5 manuel"  };

      /* Alarm EQ4 AE  */
const STR *const StrEQ_4E []   = {     "2 See 7.5 in Manual",
                                       "2 Siehe 7.5 Handbuch",
                                       "2 Ver 7.5 en Manual",
                                       "2 Ved 7.5 nl Manual",
                                       "2 Voir 7.5 manuel"  };

       /* Alarm EQ1     */
const STR *const StrEQ_1B []   = {     "1 Save Your Preset",
                                       "1 Param. speichern",
                                       "1 Guarde su presel",
                                       "1 Salvare preset",
                                       "1 Enrg votr prereg"  };

             /* Alarm EQ1     */
const STR *const StrEQ_1A []   = {     "2 See Manual",
                                       "2 siehe Handbuch",
                                       "2 Ver Manual",
                                       "2 Ved Manual",
                                       "2 Cf. Manuel" };

            /* Several alarms*/
const STR *const StrEQ_1C []   =   {   "section 7.5",
                                       "Abschn 7.5",
                                       "seccion 7.5",
                                       "sezione 7.5",
                                       "section 7.5"  };

             /* Alarm EQ5     */
const STR *const StrEQ_5A []   = {     "2 Press Test",
                                       "2 Test betaet.",
                                       "2 Puls Prueb",
                                       "2 Premi test",
                                       "2 Press. Test"  };

      /* Alarm EQ21    */
const STR *const StrEQ_21A[]   = {     "2 Turn off function",
                                       "2 Funkt. Ausschalt.",
                                       "2 Apagar la funcion",
                                       "2 Disattvr funzione",
                                       "2 Fonction eteindre"  };

               /* Alarm NC1     */
const STR *const StrNC_1A []   = {     "See Manual",
                                       "Siehe Handbuch",
                                       "Ver Manual",
                                       "Ved manual",
                                       "Cf. Manuel"  };

               /* Alarm NC1     */
const STR *const StrNC_1B []   = {     "section 7.5",
                                       "Abschn 7.5",
                                       "Seccion 7.5",
                                       "sezione 7.5",
                                       "section 7.5"  };


//                                     "1234567890123 Pg1of1";
const STR *const NoCycleStr[]  = {     "No Cycle",
                                       "Kein Zyklus",
                                       "No ciclo",
                                       "Nes ciclo",
                                       "Pas cycle"  };

const STR *const OverloadStr[] = {     "Overload",
                                       "Ueberlast",
                                       "Sobrecar",
                                       "Svrccrco",
                                       "Surchrge"  };

const STR *const EQFailStr[]   = {     "Failure of:",
                                       "Ausfall an:",
                                       "Fallo en:",
                                       "Guasto di:",
                                       "Echec de:"  };

const STR *const CycleModStr[] = {     "Modified",
                                       "Geaend.", 
                                       "Modificd",
                                       "Modifica", 
                                       "Modifie"  }; 

/* Requested by Kevin 04-08-98 */
const STR *const WarningStr[]  = {     "Note",
                                       "Hinweis", 
                                       "Nota",
                                       "Note",
                                       "Note"  };

const STR *const CalibStr[]    = {     "Calib. Alarm",
                                       "Kal. Alarm",
                                       "Calib alarma",
                                       "Calib Allarm",
                                       "Calib Alarme"  };

const STR *const SuspectStr[]  = {     "Suspect Alarm",
                                       "Pruefe Alarm",
                                       "Sospch alarma",
                                       "Allarme sosp",
                                       "Alarme Susp."  };

const STR *const RejectStr[]   = {     "Reject Alarm",
                                       "Aussch Alarm",
                                       "Rechz alarma",
                                       "Resp allarme",
                                       "Alarme Rej."  };



/* ----  This group contains the setup strings  ---- */

const STR *const StrSE_1 [] =    {     "+-Time Limit Crossed",
                                       "+-Zeitgrenze ueber.",
                                       "+-Lte T rebasado", 
                                       "+-Limite tempo supeo", 
                                       "Lim. Temps+- crois."  };

const STR *const StrSE_2 [] =    {     "+-Time Limit Crossed",
                                       "+-Zeitgrenze ueber.",
                                       "+-Lte T rebasado", 
                                       "+-Limite tempo super",     
                                       "Lim. Temps+- crois."  };

const STR *const StrSE_3 []    =    {  "+-Eng Limit Crossed",
                                       "+-Energ.Grnz.ueber.",
                                       "+-Lte Eng rebasada",
                                       "+-Limit energ super",      
                                       "Lim. En.+- croisees"  };

const STR *const StrSE_4 [] =    {     "+-Eng Limit Crossed",
                                       "+-Energ.Grnz.ueber.",
                                       "+-Lte Eng rebasada",
                                       "+-Limit energ super",   
                                       "Lim. En.+- croisees"  };

const STR *const StrSE_5 [] =    {     "+-Pwr Limit Crossed",
                                       "+-Leist.Grnz.ueber.",
                                       "+-Lte Pot rebasada",
                                       "+-Limit pot superat",   
                                       "Lim. Pui+- croisees"  };

const STR *const StrSE_6 [] =    {     "+-Pwr Limit Crossed",
                                       "+-Leist.Grnz.ueber.",
                                       "+-Lte Pot rebasada",
                                       "+-Limit pot superat",
                                       "Lim. Pui+- croisees"  };

const STR *const StrSE_7 [] =    {     "+-Freq Limit Crossed",
                                       "+-Freq.Grnz.ueber.",
                                       "+-Lte Frec rebasada",
                                       "+-Limite freq supero", 
                                       "Lim. Freq+- croisees"  };

const STR *const StrSE_8 [] =   {      "+-Freq Limit Crossed",
                                       "+-Freq.Grnz.ueber.",
                                       "+-Lte Frec rebasada",
                                       "+-Limite freq supero", 
                                       "Lim. Freq+- croisees"  };

const STR *const StrSE_9 [] =    {     "+-Abs Limit Crossed",  
                                       "+-Abs.Grnz.ueber.",
                                       "+-Lte Abs rebasada",
                                       "+-Limit dist ass su",  
                                       "Lim. Abs+- croisees"  };

const STR *const StrSE_10[] =    {     "+-Abs Limit Crossed",
                                       "+-Abs.Grnz.ueber.",
                                       "+-Lte Abs rebasada",
                                       "+-Limit dist ass su",  
                                       "Lim. Abs+- croisees"  };

const STR *const StrSE_11[] =    {     "+-Col Limit Crossed",
                                       "+-Rel.Grnz.ueber.",
                                       "+-Lte Col rebasada",
                                       "+-Limit col superat",  
                                       "Lim. Rel+- croisees"  };

const STR *const StrSE_12[] =    {     "+-Col Limit Crossed",
                                       "+-Rel.Grnz.ueber.",
                                       "+-Lte Col rebasada",
                                       "+-Limit col superat",   
                                       "Lim. Rel+- croisees"  };

const STR *const StrSE_13[] =    {     "+-F Limit Crossed",
                                       "+-Krft.Grnz.ueber.",
                                       "+-Lte F rebasada",
                                       "+-Limit F superat",
                                       "Lim. F+- croisees"  };

const STR *const StrSE_14[] =    {     "+-F Limit Crossed",
                                       "+-Krft.Grnz.ueber.",
                                       "+-Lte F rebasada",
                                       "+-Limit F superat",
                                       "Lim. F+- croisees"  };

const STR *const StrSE_15[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_16[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_17[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_18[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_19[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_20[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_21[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_22[] = {        "",
                                       "",
                                       "",
                                       "",
                                       "" };

const STR *const StrSE_23[] = {        "",
                                       "",
                                       "",
                                       "",
                                       "" };
     
const STR *const StrSE_24[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_25[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_26[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_27[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };


const STR *const StrSE_33[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_34[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_35[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_36[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_37[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_38[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_39[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_40[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_41[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_42[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_43[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_44[] =   {      "+-Trg Limit Crossed",
                                       "+-Trig.Grnz.ueber.",
                                       "+-Lte Dsp rebasado",
                                       "+-Limit Trg superat",   
                                       "Lim. Trig+- croisees"  };

const STR *const StrSE_45[] =    {     "+-Trg Limit Crossed",
                                       "+-Trig.Grnz.ueber.",
                                       "+-Lte Dsp rebasado",
                                       "+-Limit Trg superat",   
                                       "Lim. Trig+- croisees"  };

const STR *const StrSE_46[] =   {      "Preset Not Available",
                                       "Vorein ni verfuegbar",
                                       "Persel no dispon.",
                                       "Preset non dispon.",                    
                                       "Preset non dispon."  };

const STR *const StrPresetRecalled[] = { "Preset recalled",
                                         "Vorein abruf",
                                         "Persel volver",
                                         "Preset richia",
                                         "Preset rappel"    };   

const STR *const StrSE_47[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_48[] =   {      "Amp Step Conflict",
                                       "Ampl.profil Konflikt",
                                       "Conflict Paso Amp",
                                       "Conflitt step Amp",
                                       "Conflit Saut Ampl"  };

const STR *const StrSE_49[] =   {      "Timeout Conflict",
                                       "Zeitueber. Konflikt",
                                       "Confl Fuera Tiem",      
                                       "Conflitt Timeout",
                                       "Conflit Del. Max"  };

const STR *const StrSE_50[] =   {      "Timeout Conflict",
                                       "Zeitueber. Konflikt",
                                       "Confl Fuera Tiem",      
                                       "Conflitt Timeout",
                                       "Conflit Del. Max"  };

const STR *const StrSE_51[] =   {      "Timeout Conflict",
                                       "Zeitueber. Konflikt",
                                       "Confl Fuera Tiem",      
                                       "Conflitt Timeout",
                                       "Conflit Del. Max"  };

const STR *const StrSE_52[] =   {      "Amp Step on Force",
                                       "Ampl.prof. bei Kraft",
                                       "Paso Amp c/Fuerza",
                                       "Step Amp su Forza",
                                       "Saut Amp sur Force"  };

const STR *const StrSE_53[] =   {      "Force Step on Amp",
                                       "Kraftprofil bei Amp.",
                                       "Paso Fuerza c/Amp",
                                       "Step forza su Amp",
                                       "Saut Force sur Amp"  };

const STR *const StrSE_54[] =    {     "-S Trg > -S Abs",
                                       "-P Trig. > -P Abs.",
                                       "-S Dsp > -S Abs",
                                       "-S Trg > -S Ass",
                                       "-S Trg > -S Abs"  };

const STR *const StrSE_55[] =    {     "+S Trg > +S Abs",
                                       "+P Trig. > +P Abs.",
                                       "+S Dsp > +S Abs",
                                       "+S Trg > +S Ass",
                                       "+S Trg > +S Abs"  };

const STR *const StrSE_56[] =    {     "-R Trg > -R Abs",
                                       "-A Trig. > -A Abs.",
                                       "-R Dsp > -R Abs",
                                       "-R Trg > -R Ass",
                                       "-R Trg > -R Abs"  };

const STR *const StrSE_57[] =    {     "+R Trg > +R Abs",
                                       "+A Trig. > +A Abs.",
                                       "+R Dsp > +R Abs",
                                       "+R Trg > +R Ass",
                                       "+R Trg > +R Abs"  };

const STR *const StrSE_58[] =   {      "Timeout Conflict",
                                       "Zeitueber. Konflikt",
                                       "Confl Fuera Tiem",  
                                       "Conflitt Timeout",
                                       "Conflit Del. Max"  };

const STR *const StrSE_59[] =   {      "Cutoff Conflict",
                                       "Absch. Konflikt",
                                       "Conflict Corte",
                                       "Conflitt arrest",
                                       "Conflit Coupure"  };


const STR *const StrSE_65[] =   {      "Cutoff Conflict",
                                       "Absch. Konflikt",
                                       "Conflict Corte",
                                       "Conflitt arrest",
                                       "Conflit Coupure"  };

const STR *const StrSE_66[] =   {      "Cutoff Conflict",
                                       "Absch. Konflikt",
                                       "Conflict Corte",
                                       "Conflitt arrest",
                                       "Conflit Coupure"  };

const STR *const StrSE_67[] =   {      "Cutoff Conflict",
                                       "Absch. Konflikt",
                                       "Conflict Corte",
                                       "Conflitt arrest",
                                       "Conflit Coupure"  };

const STR *const StrSE_68[] =  {       "",
                                       "",
                                       "",
                                       "",
                                       "" };

const STR *const StrSE_69[] =  {       "",
                                       "",
                                       "",
                                       "",
                                       "" };

const STR *const StrSE_70[] =   {      "SE70",
                                       "SE70", 
                                       "SE70", 
                                       "SE70", 
                                       "SE70"  };

const STR *const StrSE_71[] =   {      "SE71",
                                       "SE71",
                                       "SE71",
                                       "SE71",
                                       "SE71"  }; 

const STR *const StrSE_72[] =   {      "Trg Delay & Pretrig",
                                       "Trig Verz & Pretrig.",
                                       "Retardo Dsp y Prdsp",
                                       "Ritardo Trg & Prtrg",     
                                       "Delai Trg & PreTrgl"  };

const STR *const StrSE_73[] =   {      "Trg > Weld Force",
                                       "Trig. > Schw. Kraft",
                                       "Dsp > Fuerz Sldr",    
                                       "Trg > Frz di sld",
                                       "Trg > Force Soud"  };

const STR *const StrSE_74[] =   {      "Time S/R Limit Cross",
                                       "Zeit V/W Grnz.Ueber.",
                                       "Lte S/R Tiempo Rebas",
                                       "Limite S/R tempo sup",  
                                       "Lim. Tps S/R Crois."  };

const STR *const StrSE_75[] =   {      "Time S/R Limit Cross",
                                       "Zeit V/W Grnz.Ueber.",
                                       "Lte S/R Tiempo Rebas",
                                       "Limite S/R tempo sup",   
                                       "Lim. Tps S/R Crois."  };

const STR *const StrSE_76[] =   {      "Time S/R Limit Cross",
                                       "Zeit V/W Grnz.Ueber.",
                                       "Lte S/R Tiempo Rebas",
                                       "Limite S/R tempo sup",   
                                       "Lim. Tps S/R Crois."  };

const STR *const StrSE_77[] =   {      "Time S/R Limit Cross",
                                       "Zeit V/W Grnz.Ueber.",
                                       "Lte S/R Tiempo Rebas",
                                       "Limite S/R tempo sup",   
                                       "Lim. Tps S/R Crois."  };

const STR *const StrSE_78[] =   {      "Eng S/R Limit Cross",
                                       "Enr. V/W Grnz.Ueber.",
                                       "Lte S/R Energia Rba",    
                                       "Limite S/R energ su",  
                                       "Lim. En S/R Crois."  };

const STR *const StrSE_79[] =   {      "Eng S/R Limit Cross",
                                       "Enr. V/W Grnz.Ueber.",
                                       "Lte S/R Energia Rba",  
                                       "Limite S/R energ su",  
                                       "Lim. En S/R Crois."  };

const STR *const StrSE_80[] =   {      "Eng S/R Limit Cross",
                                       "Enr. V/W Grnz.Ueber.",
                                       "Lte S/R Energia Rba",    
                                       "Limite S/R energ su", 
                                       "Lim. En S/R Crois."  };

const STR *const StrSE_81[] =   {      "Eng S/R Limit Cross",
                                       "Enr. V/W Grnz.Ueber.",
                                       "Lte S/R Energia Rba",  
                                       "Limite S/R energ su",  
                                       "Lim. En S/R Crois."  };

const STR *const StrSE_82[] =   {      "Pwr S/R Limit Cross",
                                       "Lst. V/W Grnz.Ueber.",
                                       "Lte S/R Potenci Rba",  
                                       "Limite S/R pot sup.",
                                       "Lim. Pui S/R Crois."  };

const STR *const StrSE_83[] =   {      "Pwr S/R Limit Cross",
                                       "Lst. V/W Grnz.Ueber.",
                                       "Lte S/R Potenci Rba",   
                                       "Limite S/R pot sup.",
                                       "Lim. Pui S/R Crois."  };

const STR *const StrSE_84[] =   {      "Pwr S/R Limit Cross",
                                       "Lst. V/W Grnz.Ueber.",
                                       "Lte S/R Potenci Rba",   
                                       "Limite S/R pot sup.",
                                       "Lim. Pui S/R Crois."  };

const STR *const StrSE_85[] =   {      "Pwr S/R Limit Cross",
                                       "Lst. V/W Grnz.Ueber.",
                                       "Lte S/R Potenci Rba",   
                                       "Limite S/R pot sup.",
                                       "Lim. Pui S/R Crois."  };

const STR *const StrSE_86[] =   {      "Abs S/R Limit Cross",
                                       "Abs. V/W Grnz.Ueber.",
                                       "Lte S/R Abs Rebas",
                                       "Lim S/R Dist ass sp", 
                                       "Lim. Abs S/R Crois."  };

const STR *const StrSE_87[] =   {      "Abs S/R Limit Cross",
                                       "Abs. V/W Grnz.Ueber.",
                                       "Lte S/R Abs Rebas",
                                       "Lim S/R Dist ass sp",   
                                       "Lim. Abs S/R Crois."  };

const STR *const StrSE_88[] =   {      "Abs S/R Limit Cross",
                                       "Abs. V/W Grnz.Ueber.",
                                       "Lte S/R Abs Rebas",
                                       "Lim S/R Dist ass sp",   
                                       "Lim. Abs S/R Crois."  };

const STR *const StrSE_89[] =   {      "Abs S/R Limit Cross",
                                       "Abs. V/W Grnz.Ueber.",
                                       "Lte S/R Abs Rebas",
                                       "Lim S/R Dist ass sp",   
                                       "Lim. Abs S/R Crois."  };

const STR *const StrSE_90[] =   {      "Col S/R Limit Cross",
                                       "Rel. V/W Grnz.Ueber.",
                                       "Lte S/R Col Rebasad",
                                       "Limite S/R col sup.",
                                       "Lim. Rel S/R Crois."  };

const STR *const StrSE_91[] =   {      "Col S/R Limit Cross",
                                       "Rel. V/W Grnz.Ueber.",
                                       "Lte S/R Col Rebasad",
                                       "Limite S/R col sup.",
                                       "Lim. Rel S/R Crois."  };

const STR *const StrSE_97 [] =  {      "Col S/R Limit Cross",
                                       "Rel. V/W Grnz.Ueber.",
                                       "Lte S/R Col Rebasad",
                                       "Limite S/R col sup.",
                                       "Lim. Rel S/R Crois."  };

const STR *const StrSE_98 [] =  {      "Col S/R Limit Cross",
                                       "Rel. V/W Grnz.Ueber.",
                                       "Lte S/R Col Rebasad",
                                       "Limite S/R col sup.",
                                       "Lim. Rel S/R Crois."  };

const STR *const StrSE_99 [] =  {      "F S/R Limit Cross",
                                       "Krft V/W Grnz.Ueber.",
                                       "Lte S/R F Rebas",
                                       "Limite S/R F sup.",
                                       "Lim. F S/R Crois."  };

const STR *const StrSE_100[] =  {      "F S/R Limit Cross",
                                       "Krft V/W Grnz.Ueber.",
                                       "Lte S/R F Rebas",
                                       "Limite S/R F sup.",
                                       "Lim. F S/R Crois."  };

const STR *const StrSE_101[] =  {      "F S/R Limit Cross",
                                       "Krft V/W Grnz.Ueber.",
                                       "Lte S/R F Rebas",
                                       "Limite S/R F sup.",
                                       "Lim. F S/R Crois."  };

const STR *const StrSE_102[] =  {      "F S/R Limit Cross",
                                       "Krft V/W Grnz.Ueber.",
                                       "Lte S/R F Rebas",
                                       "Limite S/R F sup.",
                                       "Lim. F S/R Crois."  };

const STR *const StrSE_103[] =  {      "Freq S/R Limit Cross",
                                       "Freq V/W Grnz.Ueber.",
                                       "Lte S/R Frec Rebas",
                                       "Limite S/R freq sup.",
                                       "Lim. Freq S/R Crois."  };

const STR *const StrSE_104[] =  {      "Freq S/R Limit Cross",
                                       "Freq V/W Grnz.Ueber.",
                                       "Lte S/R Frec Rebas",
                                       "Limite S/R freq sup.",
                                       "Lim. Freq S/R Crois."  };

const STR *const StrSE_105[] =  {      "Freq S/R Limit Cross",
                                       "Freq V/W Grnz.Ueber.",
                                       "Lte S/R Frec Rebas",
                                       "Limite S/R freq sup.",
                                       "Lim. Freq S/R Crois."  };

const STR *const StrSE_106[] =  {      "Freq S/R Limit Cross",
                                       "Freq V/W Grnz.Ueber.",
                                       "Lte S/R Frec Rebas",
                                       "Limite S/R freq sup.",
                                       "Lim. Freq S/R Crois."  };

const STR *const StrSE_107[] =  {      "Trg S/R Limit Cross",
                                       "Trig P/A Grnz.Ueber.",
                                       "Lte S/R Dsp Rebasad",
                                       "Limite S/R Trg sup.",
                                       "Lim. Dec S/R Crois."  };

const STR *const StrSE_108[] =  {      "Trg S/R Limit Cross",
                                       "Trig P/A Grnz.Ueber.",
                                       "Lte S/R Dsp Rebasad",
                                       "Limite S/R Trg sup.",
                                       "Lim. Dec S/R Crois."  };

const STR *const StrSE_109[] =  {      "Trg S/R Limit Cross",
                                       "Trig P/A Grnz.Ueber.",
                                       "Lte S/R Dsp Rebasad",
                                       "Limite S/R Trg sup.",
                                       "Lim. Dec S/R Crois."  };

const STR *const StrSE_110[] =  {      "Trg S/R Limit Cross",
                                       "Trig P/A Grnz.Ueber.",
                                       "Lte S/R Dsp Rebasad",
                                       "Limite S/R Trg sup.",
                                       "Lim. Dec S/R Crois."  };

const STR *const StrSE_111[] =  {      "Force Step Cutoff",
                                       "Kraftprofil Absch.",
                                       "Corte Paso Fuerza",
                                       "Arrest step forza",
                                       "Coupure Saut Force"  };

const STR *const StrSE_112[] =  {      "Force Step Cutoff",
                                       "Kraftprofil Absch.",
                                       "Corte Paso Fuerza",
                                       "Arrest step forza",
                                       "Coupure Saut Force"  };

const STR *const StrSE_113[] =  {      "Force Step Cutoff",
                                       "Kraftprofil Absch.",
                                       "Corte Paso Fuerza",
                                       "Arrest step forza",
                                       "Coupure Saut Force"  };

const STR *const StrSE_114[] =  {      "Force Step Cutoff",
                                       "Kraftprofil Absch.",
                                       "Corte Paso Fuerza",
                                       "Arrest step forza",
                                       "Coupure Saut Force"  };

const STR *const StrSE_115[] =  {      "Force Step Cutoff",
                                       "Kraftprofil Absch.",
                                       "Corte Paso Fuerza",
                                       "Arrest step forza",
                                       "Coupure Saut Force"  };

const STR *const StrSE_116[] =  {      "Force Step Cutoff",
                                       "Kraftprofil Absch.",
                                       "Corte Paso Fuerza",
                                       "Arrest step forza",
                                       "Coupure Saut Force"  };

const STR *const StrSE_117[] =  {      "Force Step Cutoff",
                                       "Kraftprofil Absch.",
                                       "Corte Paso Fuerza",
                                       "Arrest step forza",
                                       "Coupure Saut Force"  };

const STR *const StrSE_118[] =  {      "Force Step Cutoff",
                                       "Kraftprofil Absch.",
                                       "Corte Paso Fuerza",
                                       "Arrest step forza",
                                       "Coupure Saut Force"  };

const STR *const StrSE_119[] =  {      "Energy Comp Crossed",
                                       "Energiekomp. ueber.",
                                       "Comp Energ Rebasada",
                                       "Comp ener superata",
                                       "Comp. Energie Crois."  };

const STR *const StrSE_120[] =  {      "Missing Part Crossed",
                                       "Fehlend. Teil ueber.", 
                                       "Cruce parte perdida ",
                                       "Part mancant superat",
                                       "Pce manqte Crois."  };

const STR *const StrSE_121[] =  {      "Pretrigger Conflict",
                                       "Pretrigger Konflikt",
                                       "Conflcto Predisparo",
                                       "Conflitt pretrigger",
                                       "Conflit Pretrigger"  };

const STR *const StrSE_122[] =  {      "Pretrigger Conflict",
                                       "Pretrigger Konflikt",
                                       "Conflcto Predisparo",
                                       "Conflitt pretrigger",
                                       "Conflit Pretrigger"  };

const STR *const StrSE_123[] =  {      "Pretrigger Conflict",
                                       "Pretrigger Konflikt",
                                       "Conflcto Predisparo",
                                       "Conflitt pretrigger",
                                       "Conflit Pretrigger"  };

const STR *const StrSE_129[] =  {      "Pretrigger Conflict",
                                       "Pretrigger Konflikt",
                                       "Conflcto Predisparo",
                                       "Conflitt pretrigger",
                                       "Conflit Pretrigger"  };

const STR *const StrSE_130[] =  {      "Pretrigger Conflict",
                                       "Pretrigger Konflikt",
                                       "Conflcto Predisparo",
                                       "Conflitt pretrigger",
                                       "Conflit Pretrigger"  };

const STR *const StrSE_131[] =  {      "Pretrigger Conflict",
                                       "Pretrigger Konflikt",
                                       "Conflcto Predisparo",
                                       "Conflitt pretrigger",
                                       "Conflit Pretrigger"  };

const STR *const StrSE_132[] =  {      "Pretrigger Conflict",
                                       "Pretrigger Konflikt",
                                       "Conflcto Predisparo",
                                       "Conflitt pretrigger",
                                       "Conflit Pretrigger"  };

const STR *const StrSE_133[] =  {      "Pretrigger Conflict",
                                       "Pretrigger Konflikt",
                                       "Conflcto Predisparo",
                                       "Conflitt pretrigger",
                                       "Conflit Pretrigger"  };

const STR *const StrSE_134[] =  {      "Pretrigger Conflict",
                                       "Pretrigger Konflikt",
                                       "Conflcto Predisparo",
                                       "Conflitt pretrigger",
                                       "Conflit Pretrigger"  };

const STR *const StrSE_135[] =  {      "Pretrigger Conflict",
                                       "Pretrigger Konflikt",
                                       "Conflcto Predisparo",
                                       "Conflitt pretrigger",
                                       "Conflit Pretrigger"  };

const STR *const StrSE_136[] =  {      "Pretrigger Conflict",
                                       "Pretrigger Konflikt",
                                       "Conflcto Predisparo",
                                       "Conflitt pretrigger",
                                       "Conflit Pretrigger"  };

const STR *const StrSE_137[] =  {      "Pretrigger Conflict",
                                       "Pretrigger Konflikt",
                                       "Conflcto Predisparo",
                                       "Conflitt pretrigger",
                                       "Conflit Pretrigger"  };

const STR *const StrSE_138[] =  {      "Abs Cutoff Conflict",
                                       "Abs.Absch. Konflikt",
                                       "Conflict Corte Abs",
                                       "Confl inter Dis ass",    
                                       "Conflit Coupure Abs"  };

const STR *const StrSE_139[] =  {      "Abs Cutoff Conflict",
                                       "Abs.Absch. Konflikt",
                                       "Conflict Corte Abs",
                                       "Confl inter Dis ass",    
                                       "Conflit Coupure Abs"  };

const STR *const StrSE_140[] =  {      "Abs Cutoff Conflict",
                                       "Abs.Absch. Konflikt",
                                       "Conflict Corte Abs",
                                       "Confl inter Dis ass",    
                                       "Conflit Coupure Abs"  };

const STR *const StrSE_141[] =  {      "Abs Cutoff Conflict",
                                       "Abs.Absch. Konflikt",
                                       "Conflict Corte Abs",
                                       "Confl inter Dis ass",    
                                       "Conflit Coupure Abs"  };

const STR *const StrSE_142[] =  {      "Abs Cutoff Conflict",
                                       "Abs.Absch. Konflikt",
                                       "Conflict Corte Abs",
                                       "Confl inter Dis ass",    
                                       "Conflit Coupure Abs"  };

const STR *const StrSE_143[] =  {      "Abs Cutoff Conflict",
                                       "Abs.Absch. Konflikt",
                                       "Conflict Corte Abs",
                                       "Confl inter Dis ass",    
                                       "Conflit Coupure Abs"  };

const STR *const StrSE_144[] =  {      "Abs Cutoff Conflict",
                                       "Abs.Absch. Konflikt",
                                       "Conflict Corte Abs",
                                       "Confl inter Dis ass",    
                                       "Conflit Coupure Abs"  };

const STR *const StrSE_145[] =  {      "Abs Cutoff Conflict",
                                       "Abs.Absch. Konflikt",
                                       "Conflict Corte Abs",
                                       "Confl inter Dis ass",    
                                       "Conflit Coupure Abs"  };

const STR *const StrSE_146[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_147[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_148[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_149[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_150[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_151[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_152[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_153[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_154[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_155[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };


const STR *const StrSE_161[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_162[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_163[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_164[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_165[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_166[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_167[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_168[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_169[] =  {      "Missing Part Conflct",
                                       "Fehlend. Teil Konfl.",
                                       "Conflict Pieza Perd",
                                       "Confl part mancante",   
                                       "Conflit Pce Manqte"  };

const STR *const StrSE_170[] =  {      "Energy Comp Conflict",
                                       "Energiekomp. Konfl.",
                                       "Confl Comp Energia",
                                       "Conflitt comp energ",    
                                       "Conflit Comp Energie"  };

const STR *const StrSE_171[] =  {      "Energy Comp Conflict",
                                       "Energiekomp. Konfl.",
                                       "Confl Comp Energia",
                                       "Conflitt comp energ",    
                                       "Conflit Comp Energie"  };

const STR *const StrSE_172[] =  {      "Energy Comp Conflict",
                                       "Energiekomp. Konfl.",
                                       "Confl Comp Energia",
                                       "Conflitt comp energ",    
                                       "Conflit Comp Energie"  };

const STR *const StrSE_173[] =  {      "Energy Comp Conflict",
                                       "Energiekomp. Konfl.",
                                       "Confl Comp Energia",
                                       "Conflitt comp energ",    
                                       "Conflit Comp Energie"  };

const STR *const StrSE_174[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_175[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_176[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_177[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_178[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_179[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_180[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_181[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_182[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_183[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_184[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_185[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_186[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_187[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_193[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_194[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_195[] =  {      "Rapid Trav. Conflict",
                                       "EILGANG Konflikt",
                                       "Conflict Cruve Rapd",
                                       "Confl spost. rapido",   
                                       "Conflit Mvmt Rapide"  };

const STR *const StrSE_196[] =  {      "Hold Force Conflict",
                                       "Haltekraft Konflikt",
                                       "Confl Fuerza Mant",
                                       "Confl forza di raff", 
                                       "Conflit Frce Maint."  };

const STR *const StrSE_197[] =  {      "Hold Force Conflict",
                                       "Haltekraft Konflikt",
                                       "Confl Fuerza Mant",    
                                       "Confl forza di raff", 
                                       "Conflit Frce Maint."  };

const STR *const StrSE_198[] =  {      "Hold Force Conflict",
                                       "Haltekraft Konflikt",
                                       "Confl Fuerza Mant",    
                                       "Confl forza di raff", 
                                       "Conflit Frce Maint."  };

const STR *const StrSE_199[] =  {      "Hold Force Conflict",
                                       "Haltekraft Konflikt",
                                       "Confl Fuerza Mant",   
                                       "Confl forza di raff",  
                                       "Conflit Frce Maint."  };

const STR *const StrSE_200[] =  {      "Force/Lmt Conflict",
                                       "Kraft/Grz. Konflikt",
                                       "Conflict Fuerz/Lte",
                                       "Conflitt forza/lim",
                                       "Conflit Force/Lmt"  };

const STR *const StrSE_201[] =  {      "Force/Lmt Conflict",
                                       "Kraft/Grz. Konflikt",
                                       "Conflict Fuerz/Lte",
                                       "Conflitt forza/lim",
                                       "Conflit Force/Lmt"  };

const STR *const StrSE_202[] =  {      "Force/Lmt Conflict",
                                       "Kraft/Grz. Konflikt",
                                       "Conflict Fuerz/Lte",
                                       "Conflitt forza/lim",
                                       "Conflit Force/Lmt"  };

const STR *const StrSE_203[] =  {      "Force/Lmt Conflict",
                                       "Kraft/Grz. Konflikt",
                                       "Conflict Fuerz/Lte",
                                       "Conflitt forza/lim",
                                       "Conflit Force/Lmt"  };

const STR *const StrSE_204[] =  {      "Force/Lmt Conflict",
                                       "Kraft/Grz. Konflikt",
                                       "Conflict Fuerz/Lte",
                                       "Conflitt forza/lim",
                                       "Conflit Force/Lmt"  };

const STR *const StrSE_205[] =  {      "Force/Lmt Conflict",
                                       "Kraft/Grz. Konflikt",
                                       "Conflict Fuerz/Lte",
                                       "Conflitt forza/lim",
                                       "Conflit Force/Lmt"  };

const STR *const StrSE_206[] =  {      "Force/Lmt Conflict",
                                       "Kraft/Grz. Konflikt",
                                       "Conflict Fuerz/Lte",
                                       "Conflitt forza/lim",
                                       "Conflit Force/Lmt"  };

const STR *const StrSE_207[] =  {      "Force/Lmt Conflict",
                                       "Kraft/Grz. Konflikt",
                                       "Conflict Fuerz/Lte",
                                       "Conflitt forza/lim",
                                       "Conflit Force/Lmt"  };

const STR *const StrSE_208[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_209[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza", 
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_210[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza", 
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_211[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza", 
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_212[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza", 
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_213[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza", 
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_214[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza", 
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_215[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza", 
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_216[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza", 
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_217[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza", 
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_218[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza", 
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_219[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_225[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_226[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_227[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_228[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_229[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_230[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_231[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_232[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_233[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_234[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_235[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_236[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_237[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_238[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_239[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_240[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_241[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_242[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_243[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl Paso Fuerza",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_244[] =  {      "Amp/F Step Conflict",
                                       "Ampl./K Prof. Konfl.",
                                       "Conflcto Amp/Paso F",
                                       "Conflitt Amp/Step F",
                                       "Conflit Amp/Saut F"  };

const STR *const StrSE_245[] =  {      "ForceA > Pressure",
                                       "KraftA > Druck",
                                       "FuerzaA > Presion",
                                       "ForzaA > Pression",
                                       "ForceA > Pression"  };

const STR *const StrSE_246[] =  {      "ForceB > Pressure",
                                       "KraftB > Druck",
                                       "FuerzaB > Presion",
                                       "ForzaB > Pression",
                                       "ForceB > Pression"  };

const STR *const StrSE_247[] =  {      "Hold Force>Pressure",
                                       "Haltekraft > Druck",
                                       "Fuerza Mant>Presion",
                                       "Forz di raff.>Press", 
                                       "Frce Maint>Pression"  };

const STR *const StrSE_248[] =  {      "Pressure>Weld Force",
                                       "Druck > Schw. Kraft",
                                       "Presion>Fuerz Solda",
                                       "Press>Forz di sald", 
                                       "Pression>Force Soud"  };

const STR *const StrSE_249[] =  {      "Pressure>Force B",
                                       "Druck > Kraft B",
                                       "Presion>Fuerza B",
                                       "Pression>Forza B",
                                       "Pression>Force B"  };

const STR *const StrSE_250[] =  {      "Pressure>Hold Force",
                                       "Druck > Haltekraft",
                                       "Presion>Fuerza Mant",
                                       "Press>Forz di raff",
                                       "Pression>Frce Maint"  };

const STR *const StrSE_251[] =  {      "Trg Force Conflict",
                                       "Trig. Kraft Konflikt",
                                       "Conflict Fuerz Dsp",
                                       "Conflitt forza Trg",
                                       "Conflit Force Trig"  };


const STR *const StrSE_257[] =  {      "Trg Force Conflict",
                                       "Trig. Kraft Konflikt",
                                       "Conflict Fuerz Dsp",
                                       "Conflitt forza Trg",
                                       "Conflit Force Trig"  };

const STR *const StrSE_258[] = {       "",
                                       "",
                                       "",
                                       "",
                                       "" };

const STR *const StrSE_259[] =  {      "Encoder Required",
                                       "Wegmess. erforderl.",
                                       "Se Precis Encodr",
                                       "Richiesto encodr",
                                       "Encodeur Requis"  };

const STR *const StrSE_260[] =  {      "Force Step Conflict",
                                       "Kraftprofil Konflikt",
                                       "Confl. Paso Fuerz",  
                                       "Conflitt step forza",
                                       "Conflit Saut Force"  };

const STR *const StrSE_261[] =  {      "Sys. Pres. Incorrect",
                                       "Systemdruck falsch",
                                       "Pres Sist Incorrecta",
                                       "Pres. sist. errata",
                                       "Press. Syst. Incorr."  };

const STR *const StrSE_262[] =  {      "Weld Force>Pressure",
                                       "Schw. Kraft > Druck",
                                       "Fuerz Soldad>Presio", 
                                       "Forza di sald>Press",  
                                       "Force Soud>Pression"  };

const STR *const StrSE_263[] =  {      "SE263",
                                       "SE263",  
                                       "SE263", 
                                       "SE263", 
                                       "SE263"  }; 

const STR *const StrSE_264[] =  {      "Energy Comp Conflict",
                                       "Energiekomp. Konfl.",
                                       "Confl Comp Energia",
                                       "Confl comp energia",   
                                       "Conflit Comp Energie"  };

const STR *const StrSE_265[] =  {      "Energy Comp Conflict",
                                       "Energiekomp. Konfl.",
                                       "Confl Comp Energia",
                                       "Confl comp energia",   
                                       "Conflit Comp Energie"  };

const STR *const StrSE_266[] =  {      "Energy Comp Conflict",
                                       "Energiekomp. Konfl.",
                                       "Confl Comp Energia",
                                       "Confl comp energia",   
                                       "Conflit Comp Energie"  };

const STR *const StrSE_267[] =  {      "Energy Comp Conflict",
                                       "Energiekomp. Konfl.",
                                       "Confl Comp Energia",
                                       "Confl comp energia", 
                                       "Conflit Comp Energie"  };

const STR *const StrSE_268[] =  {      "Invalid Preset",
                                       "Unguelt. Voreinst.",
                                       "Preslc No Vali",
                                       "Preset non val",
                                       "Preset Invalide"  };

const STR *const StrSE_269[] =  {      "Undefined Preset",
                                       "Undef. Voreinst.",
                                       "Preslc No Defini",
                                       "Preset non defin",
                                       "Preset Non Defini"  };

const STR *const StrSE_270[] =  {      "Printer Offline",
                                       "Drucker aus",
                                       "Imprsra Fuer Ln",  
                                       "Stmpnt non ln",  
                                       "Imp Hrs Tension"  };

const STR *const StrSE_271[] =   {     "-S Trg > +S Abs",
                                       "-P Trig. > +P Abs.",
                                       "-S Dsp > +S Abs",
                                       "-S Trg > +S Ass",
                                       "-S Trg > +S Abs"  };

const STR *const StrSE_272[] =   {     "-S Trg > +R Abs",
                                       "-P Trig. > +A Abs.",
                                       "-S Dsp > +R Abs",
                                       "-S Trg > +R Ass",
                                       "-S Trg > +R Abs"  };

const STR *const StrSE_273[] =   {     "-R Trg > +S Abs",
                                       "-A Trig. > +P Abs.",
                                       "-R Dsp > +S Abs",
                                       "-R Trg > +S Ass",
                                       "-R Trg > +S Abs"  };

const STR *const StrSE_274[] =   {     "-R Trg > +R Abs",
                                       "-A Trig. > +A Abs.",
                                       "-R Dsp > +R Abs",
                                       "-R Trg > +R Ass",
                                       "-R Trg > +R Abs"  };

const STR *const StrSE_275[] =   {     "-S Trg > Abs",
                                       "-P Trig. > Abs.",
                                       "-S Dsp > Abs",
                                       "-S Trg > Ass",
                                       "-S Trg > Abs"  };

const STR *const StrSE_276[] =   {     "-R Trg > Abs",
                                       "-A Trig. > Abs.",
                                       "-R Dsp > Abs",
                                       "-R Trg > Ass",
                                       "-R Trg > Abs"  };

const STR *const StrSE_277[] =  {      "Sys. Pres. Incorrect",
                                       "Systemdruck falsch",
                                       "Pres Sist Incorrecta",
                                       "Pres. sist. errata",
                                       "Press. Syst. Incorr."  };

const STR *const StrSE_278[] =  {      "SE278",
                                       "SE278",  
                                       "SE278", 
                                       "SE278", 
                                       "SE278"  }; 

const STR *const StrSE_279[] =  {      "SE279",
                                       "SE279",   
                                       "SE279", 
                                       "SE279", 
                                       "SE279"  }; 

const STR *const StrSE_280[] =  {      "SE280",
                                       "SE280",   
                                       "SE280", 
                                       "SE280", 
                                       "SE280"  }; 

const STR *const StrSE_281[] =  {      "SE281",
                                       "SE281",   
                                       "SE281", 
                                       "SE281", 
                                       "SE281"  }; 

const STR *const StrSE_282[] =  {      "SE282",    
                                       "SE282", 
                                       "SE282", 
                                       "SE282", 
                                       "SE282"  }; 

const STR *const StrSE_283[] =  {      "SE283",
                                       "SE283",   
                                       "SE283", 
                                       "SE283", 
                                       "SE283"  }; 

const STR *const StrSE_289[] =  {      "Trg Delay Conflict",
                                       "Konflikt Trg Verzoeg",
                                       "Conf. retardo disp.", 
                                       "Conflitto Trg ritardo", 
                                       "Conflit Delai Trig"  }; 

const STR *const StrSE_290[] =  {      "Trg Delay Conflict",
                                       "Konflikt Trg Verzoeg",
                                       "Conf. retardo disp.", 
                                       "Conflitto Trg ritardo", 
                                       "Conflit Delai Trig"  }; 

const STR *const StrSE_291[] =  {      "External Start Setup",
                                       "External Start Setup", 
                                       "External Start Setup", 
                                       "External Start Setup", 
                                       "External Start Setup"  }; 

const STR *const StrSE_292[] =  {      "Missing Part Conflct",
                                       "Missing Part Conflct",  
                                       "Missing Part Conflct", 
                                       "Missing Part Conflct", 
                                       "Missing Part Conflct"  }; 

const STR *const StrSE_293[] =  {      "Energy Braking Setup",
                                       "Einst Energ Unterbre",
                                       "Conf. Frenado energ.", 
                                       "Energy Braking Setup", 
                                       "Regler Frein Energie"  }; 

const STR *const StrSE_294[] =  {      "Input Pin Conflict",
                                       "Konflikt Eingangspin", 
                                       "Conflicto pin I", 
                                       "Input Pin Conflict", 
                                       "Conflit sur Entrees"  }; 

const STR *const StrSE_295[] =  {      "Sync Setup",
                                       "Sync Setup",  
                                       "Sync Setup", 
                                       "Sync Setup", 
                                       "Sync Setup"  }; 

const STR *const StrSE_296[] =  {      "Ext Signal Setup",
                                       "Ext Signal Setup",  
                                       "Ext Signal Setup", 
                                       "Ext Signal Setup", 
                                       "Ext Signal Setup" }; 

const STR *const StrSE_297[] =  {      "SE297",
                                       "SE297",  
                                       "SE297", 
                                       "SE297", 
                                       "SE297"  }; 

const STR *const StrSE_298[] =  {      "SE298",
                                       "SE298",  
                                       "SE298", 
                                       "SE298", 
                                       "SE298"  }; 

const STR *const StrSE_299[] =  {      "SE299",
                                       "SE299",  
                                       "SE299", 
                                       "SE299", 
                                       "SE299"  }; 

const STR *const StrSE_300[] =  {      "SE300",
                                       "SE300",  
                                       "SE300", 
                                       "SE300", 
                                       "SE300"  }; 

const STR *const StrSE_301[] =  {      "SE301",
                                       "SE301",  
                                       "SE301", 
                                       "SE301", 
                                       "SE301"  }; 

const STR *const StrSE_302[] =  {      "SE302",
                                       "SE302",  
                                       "SE302", 
                                       "SE302", 
                                       "SE302"  }; 

const STR *const StrSE_303[] =  {      "SE303",
                                       "SE303",  
                                       "SE303", 
                                       "SE303", 
                                       "SE303"  }; 

const STR *const StrSE_304[] =  {      "SE304",
                                       "SE304",  
                                       "SE304", 
                                       "SE304", 
                                       "SE304"  }; 

const STR *const StrSE_305[] =  {      "SE305",
                                       "SE305",  
                                       "SE305",
                                       "SE305",
                                       "SE305"  }; 

const STR *const StrSE_306[] =  {      "SE306",
                                       "SE306",  
                                       "SE306", 
                                       "SE306", 
                                       "SE306"  }; 

const STR *const StrSE_307[] =  {      "SE307",
                                       "SE307",  
                                       "SE307", 
                                       "SE307", 
                                       "SE307"  }; 

const STR *const StrSE_308[] =  {      "SE308",
                                       "SE308",  
                                       "SE308", 
                                       "SE308", 
                                       "SE308"  }; 

const STR *const StrSE_309[] =  {      "SE309",
                                       "SE309",  
                                       "SE309", 
                                       "SE309", 
                                       "SE309"  }; 

const STR *const StrSE_310[] =  {      "SE310",
                                       "SE310",  
                                       "SE310", 
                                       "SE310", 
                                       "SE310"  }; 

const STR *const StrSE_311[] =  {      "SE311",
                                       "SE311",  
                                       "SE311", 
                                       "SE311", 
                                       "SE311"  }; 

const STR *const StrSE_312[] =  {      "SE312",
                                       "SE312",  
                                       "SE312", 
                                       "SE312", 
                                       "SE312"  }; 

const STR *const StrSE_313[] =  {      "SE313",
                                       "SE313",  
                                       "SE313", 
                                       "SE313", 
                                       "SE313"  }; 

const STR *const StrSE_314[] =  {      "SE314",
                                       "SE314",  
                                       "SE314", 
                                       "SE314", 
                                       "SE314"  }; 

const STR *const StrSE_315[] =  {      "SE315",
                                       "SE315",  
                                       "SE315", 
                                       "SE315", 
                                       "SE315"  }; 


/* ----  This group contains the no cycle strings  ---- */

const STR *const StrNC_0 [] =   {      "No Cycle Alarm",
                                       "Kein Zykl. Alarm",
                                       "Alrma no ciclo",
                                       "Nssn alrme clo",
                                       "Pas alrme cycl"  };

const STR *const StrNC_1 [] =   {      "Upper Limit Timeout",
                                       "ULS Zeitueber.",  
                                       "Cuenta atras lt sup", 
                                       "Timeout lim superir", 
                                       "Del. Max. Lim. Sup."  }; 

const STR *const StrNC_2 [] =   {      "NC2",
                                       "NC2", 
                                       "NC2", 
                                       "NC2", 
                                       "NC2"  };

const STR *const StrNC_3 [] =   {      "Trg before Pretrg",
                                       "Trig. vor Pretrig.",
                                       "Dsp ant de Predsp",
                                       "Trg prima Pretrg",
                                       "Trig avant Pretrigl"  };

const STR *const StrNC_4 [] =    {     "Trigger Timeout",
                                       "Trig. Zeitueberschr.",
                                       "Disp fuer de Ti", 
                                       "Timeout trigger",
                                       "Del MaxTrig"  };

const STR *const StrNC_5 [] =  {       "",
                                       "",
                                       "",
                                       "",
                                       ""  };

const STR *const StrNC_6 [] =   {      "LLS abort before TRS",
                                       "LLS Abbr. vor Trig.",
                                       "LI cancel ant dispar",  
                                       "Int lim inf prma Trg",
                                       "LLS atteint avnt TRS"  };

const STR *const StrNC_7 [] =   {      "External Cycle Abort",
                                       "Extern Zykl. Abbruch",
                                       "Ciclo Cancelado Ext.",
                                       "Annulla ciclo estern",  
                                       "Interrupt Cycle Ext."  };

const STR *const StrNC_8 [] =   {      "Missing Part Abort",
                                       "Fehlend. Teil Abbr.",
                                       "Cancel por falta ",  
                                       "Annll part mancnte",
                                       "Interrupt Pce Mqte"  };

const STR *const StrNC_9 [] =   {      "Abs before Trg",
                                       "Abs. vor Trig.",
                                       "D.Abs ant Dsp",
                                       "D.Ass prma Trg",
                                       "Abs avant Trig"  };

const STR *const StrNC_10[] =   {      "Amp Step before Trg",
                                       "Ampl.profil vor Trig",
                                       "Paso Amp ant de Dsp",
                                       "Step Amp prima Trg",
                                       "Saut Amp avant Trig"  };

const STR *const StrNC_11[] =   {      "Frc Step before Trg",
                                       "Kraftprof. vor Trig.",
                                       "Paso Frc antes Disp",
                                       "Passo Frc prima Trg",
                                       "Saut Frc avant Trig."  };

const STR *const StrNC_12[] =   {      "Ground Detect Abort",
                                       "Metallkont. Abbr.",
                                       "Detecion Tierra Can",  
                                       "Ground Detect Inter",  
                                       "Interrup Detec Masse"  };

const STR *const StrNC_13[] =   {      "Trg Delay Timeout",
                                       "Zeitueb Trg Verzoeg",
                                       "Final ret. Disparo", 
                                       "Trg Delay Timeout", 
                                       "Delai Trigg. Depasse"  }; 

const STR *const StrNC_14[] =   {      "External Start Lost",
                                       "External Start Lost",
                                       "External Start Lost", 
                                       "External Start Lost", 
                                       "External Start Lost"  }; 

const STR *const StrNC_15[] =   {      "Ext Start Timeout",
                                       "Ext Start Timeout", 
                                       "Ext Start Timeout", 
                                       "Ext Start Timeout", 
                                       "Ext Start Timeout" }; 

const STR *const StrNC_16[] =   {      "NC16",
                                       "NC16", 
                                       "NC16", 
                                       "NC16", 
                                       "NC16"  }; 

const STR *const StrNC_17[] =   {      "NC17",
                                       "NC17", 
                                       "NC17", 
                                       "NC17", 
                                       "NC17"  }; 

const STR *const StrNC_18[] =   {      "NC18",
                                       "NC18", 
                                       "NC18", 
                                       "NC18", 
                                       "NC18"  }; 

const STR *const StrNC_19[] =   {      "NC19",
                                       "NC19", 
                                       "NC19", 
                                       "NC19", 
                                       "NC19"  }; 

const STR *const StrNC_20[] =   {      "NC20",
                                       "NC20", 
                                       "NC20", 
                                       "NC20", 
                                       "NC20"  }; 

const STR *const StrNC_21[] =   {      "NC21",
                                       "NC21", 
                                       "NC21", 
                                       "NC21", 
                                       "NC21"  }; 

const STR *const StrNC_22[] =   {      "NC22",
                                       "NC22", 
                                       "NC22", 
                                       "NC22", 
                                       "NC22"  }; 

const STR *const StrNC_23[] =   {      "NC23",
                                       "NC23", 
                                       "NC23", 
                                       "NC23", 
                                       "NC23"  }; 

const STR *const StrNC_24[] =   {      "NC24",
                                       "NC24", 
                                       "NC24", 
                                       "NC24", 
                                       "NC24"  }; 

const STR *const StrNC_25[] =   {      "NC25",
                                       "NC25", 
                                       "NC25", 
                                       "NC25", 
                                       "NC25"  }; 

const STR *const StrNC_26[] =   {      "NC26",
                                       "NC26", 
                                       "NC26", 
                                       "NC26", 
                                       "NC26"  }; 

const STR *const StrNC_27[] =   {      "NC27",
                                       "NC27", 
                                       "NC27", 
                                       "NC27", 
                                       "NC27"  }; 

/* ----  This group contains the overload strings  ---- */

const STR *const StrOL_0 [] =   {      "Overloads",
                                       "Ueberlast",
                                       "Sobrecrga",
                                       "Sovrcrchi",
                                       "Surchrges"  };


const STR *const StrOL_1 [] =   {      "Test Overload",
                                       "Test Ueberlast",
                                       "Test Sobrecar",
                                       "Sovrac. test",
                                       "Surchrge Test"  };

const STR *const StrOL_2 [] =   {      "Pretrigger Overload",
                                       "Pretrigger Ueberlast",
                                       "Sobrecarg Predispar",  
                                       "Sovraccaric pretrig",  
                                       "Surchrge Pretrigg"  };

const STR *const StrOL_3 [] =   {      "Seek Overload",
                                       "Such Ueberlast",
                                       "Sobrec. Busc",
                                       "Sovrac. Seek",
                                       "Surchrge Rech"  };

const STR *const StrOL_4 [] =   {      "Power Supply O/L",
                                       "Generator Ueberlast",
                                       "SC Fte Alimentac",
                                       "Sovra. Generatre",
                                       "Surchrge G'nerat"  };

const STR *const StrOL_5 [] =   {      "Cont Pwr Limit",
                                       "Kont. Leist. Grnz.",
                                       "Lte Poten Cont",
                                       "Limit pot cont",
                                       "Lim. Puis Cont"  };

const STR *const StrOL_6 [] =   {      "Afterburst Overload",
                                       "Nachimp. Ueberlast",
                                       "Sbrcrg Dspro Pst US",  
                                       "Sovrac. afterburst",
                                       "Surchrge Imp p-oper"  };

const STR *const StrOL_7 [] =   {      "Pre-Weld Seek O/L",
                                       "Such Ueb. vor Schw.",
                                       "Busc prv sold O/L",
                                       "Cerc pre-sald O/L",
                                       "Srch Rch Pre-soud"  };

const STR *const StrOL_8 [] =   {      "Post Weld Seek O/L",
                                       "Such Ueb. nach Schw.",
                                       "SC Busca Post Sold",
                                       "Sovrac seek pst-sa",  
                                       "Surchg Rech P-Soud"  };

const STR *const StrOL_9 [] =   {      "OL9",
                                       "OL9",  
                                       "OL9", 
                                       "OL9", 
                                       "OL9"  }; 

const STR *const StrOL_10[] =   {      "Energy Braking O/L",
                                       "O/L Energ Unterbrech",  
                                       "Frenado energ. O/L", 
                                       "Energia frenante O/L", 
                                       "Surch. Frein Energie"  }; 

const STR *const StrOL_11[] =   {      "OL11",
                                       "OL11",  
                                       "OL11", 
                                       "OL11", 
                                       "OL11"  }; 

const STR *const StrOL_12[] =   {      "OL12",
                                       "OL12",  
                                       "OL12", 
                                       "OL12", 
                                       "OL12"  }; 

const STR *const StrOL_13[] =   {      "OL13",
                                       "OL13",  
                                       "OL13", 
                                       "OL13", 
                                       "OL13"  }; 

const STR *const StrOL_14[] =   {      "OL14",
                                       "OL14",  
                                       "OL14", 
                                       "OL14", 
                                       "OL14"  }; 

const STR *const StrOL_15[] =   {      "OL15",
                                       "OL15",  
                                       "OL15", 
                                       "OL15", 
                                       "OL15"  }; 

const STR *const StrOL_16[] =   {      "OL16",
                                       "OL16",  
                                       "OL16", 
                                       "OL16", 
                                       "OL16"  }; 

const STR *const StrOL_17[] =   {      "OL17",
                                       "OL17",  
                                       "OL17", 
                                       "OL17", 
                                       "OL17"  }; 

const STR *const StrOL_18[] =   {      "OL18",
                                       "OL18",  
                                       "OL18", 
                                       "OL18", 
                                       "OL18"  }; 

const STR *const StrOL_19[] =   {      "OL19",
                                       "OL19",  
                                       "OL19", 
                                       "OL19", 
                                       "OL19"  }; 

const STR *const StrOL_20[] =   {      "OL20",
                                       "OL20",  
                                       "OL20", 
                                       "OL20", 
                                       "OL20"  }; 

const STR *const StrOL_21[] =   {      "OL21",
                                       "OL21",  
                                       "OL21", 
                                       "OL21", 
                                       "OL21"  }; 

const STR *const StrOL_22[] =   {      "OL22",
                                       "OL22",  
                                       "OL22", 
                                       "OL22", 
                                       "OL22"  }; 

const STR *const StrOL_23[] =   {      "OL23",
                                       "OL23",  
                                       "OL23", 
                                       "OL23", 
                                       "OL23"  }; 

const STR *const StrOL_24[] =   {      "OL24",
                                       "OL24",  
                                       "OL24", 
                                       "OL24", 
                                       "OL24"  }; 

const STR *const StrOL_25[] =   {      "OL25",
                                       "OL25",  
                                       "OL25", 
                                       "OL25", 
                                       "OL25"  }; 

const STR *const StrOL_26[] =   {      "OL26",
                                       "OL26",  
                                       "OL26", 
                                       "OL26", 
                                       "OL26"  }; 

const STR *const StrOL_27[] =   {      "OL27",
                                       "OL27",  
                                       "OL27", 
                                       "OL27", 
                                       "OL27"  }; 

const STR *const StrAlarmVoltageOverload[] = {
                                       "VOLTAGE O/L",
                                       "SPANN. UEBERLAST",
                                       "VOLTAJE EXCES",
                                       "SOUVRACC VOLTAGI",
                                       "SRCH TENSION" };

const STR *const StrAlarmCurrentOverload[] = {
                                       "CURRENT O/L",
                                       "STROM UEBERLAST",
                                       "CORRIENTE EXCES",
                                       "SOUVRACC CORRENT",
                                       "SRCH COURANT" };

const STR *const StrAlarmFreqOverload[] = {
                                       "FREQ O/L",
                                       "FREQ. UEBERLAST",
                                       "FREC EXCESIVA",
                                       "SOUVRACC FREQ",
                                       "SRCH FREQ" };

const STR *const StrAlarmPhaseOverload[] =  {
                                       "PHASE/PWR O/L",
                                       "PHASE UEBERLAST",
                                       "FASE/POT EXCES ",
                                       "SOUV FASE/POT",
                                       "SRCH PH/PUI." };

/* ----  This group contains the equipment failure strings  ---- */

const STR *const StrEQ_0 [] =   {      "Equipment Failure",
                                       "Geraetefehler",  
                                       "Fallo del equipo", 
                                       "Guast attrezzatur", 
                                       "Equipement defect"  }; 


const STR *const StrEQ_1 [] =   {      "Encoder Failed",
                                       "Laengmess. def.",
                                       "Fallo Encoder",
                                       "Encoder rotto",
                                       "Encodeur Defect."  };

const STR *const StrEQ_2 [] =   {      "Upper Limit Switch",
                                       "ULS",
                                       "Conmt Lte Superior",
                                       "Sensor limit super",  
                                       "Cont. Posit. Haute"  };

const STR *const StrEQ_3 [] =   {      "Upper Limit Switch",
                                       "ULS",
                                       "Conmt Lte Superior",
                                       "Sensor limit super",  
                                       "Cont. Posit. Haute"  };

const STR *const StrEQ_4 [] =   {      "Door/Trigger Switch",
                                       "Tuer/Trig. Schalter",
                                       "Conmut Puerta/Dspro",
                                       "Porta/Int. trigger",
                                       "Contact. Porte/Trig"  };

const STR *const StrEQ_5 [] =   {      "Loadcell Failed",
                                       "Kraftmessfehler",  
                                       "Fallo cel carga", 
                                       "Crcmnl non rius", 
                                       "Jauge Cont. dfect"  }; 

const STR *const StrEQ_6 [] =   {      "Solenoid Drive Fail",
                                       "Magnetventil defekt",
                                       "Fallo Electrvlvula",
                                       "Azion elettro fall ", 
                                       "Circ. E.Vanne Defect"  };

const STR *const StrEQ_7 [] =   {      "Thermal Overload",
                                       "Therm. Ueberlast",
                                       "Temp Excesiva",
                                       "Sovracc. termico",
                                       "Surchg Thermique"  };

const STR *const StrEQ_8 [] =   {      "Preset Data/BBR",
                                       "Voreinst. Dat/BBR",
                                       "BBR/Dat Presel",
                                       "Dati preset/BBR",
                                       "Don. Preset/BBR"  };

const STR *const StrEQ_9 [] =   {      "Horn Return Timeout",
                                       "Rueckhub Zeitueber.",
                                       "Retorno Sonot Fuer ",
                                       "Timeout ritorno son",
                                       "Del Max Retour Sono"  };

const STR *const StrEQ_10[] =   {      "Actuator NovRam",
                                       "VE NovRam",
                                       "NovRam Actuador",
                                       "NovRam attuator",
                                       "NovRam Actuator"  };

const STR *const StrEQ_11[] =   {      "P/S NovRam",
                                       "Gen. NovRam",
                                       "F/A NovRam",
                                       "NovRam gen",
                                       "NovRam P/S"  };

const STR *const StrEQ_12[] =   {      "Start Sw Time",
                                       "Start Sch. Zeit",
                                       "Inic Tiemp Sw",
                                       "Tempo int avi",
                                       "Tps Bout Start"  };

const STR *const StrEQ_13[] =   {      "MPS Switch Failed",
                                       "MPS Fehler",
                                       "Fallo Conmut MPS",
                                       "Int. MF fallito",
                                       "Switch MF Defect"  };

const STR *const StrEQ_14[] =   {      "Wrong Actuator",
                                       "Falsche VE",
                                       "Actudor Eroneo",
                                       "Atuatore erato",
                                       "Mauv. Actuator"  };

const STR *const StrEQ_15[] =   {      "Ultrasonics P/S",
                                       "Generator",
                                       "/A ultrasonido", 
                                       "Ultrasonics P/S", 
                                       "Gen.Ultrason."  }; 

const STR *const StrEQ_16[] =   {      "Printer Buffer Full",
                                       "Druckerspeicher voll",
                                       "Memori Imprsra Llen",
                                       "Buffer stampant pie",
                                       "Mem Tpon Imp Pleine"  };

const STR *const StrEQ_17[] =   {      "Start Switch Closed",
                                       "Start geschloss.",
                                       "Conmut Inic Cerrado",
                                       "Int. avvio chiuso",
                                       "Bouton Start Fermes"  };

const STR *const StrEQ_18[] =   {      "Pretrigger Timeout",
                                       "Pretrig. Zeitueber.",
                                       "Prdspro fuer tiem",  
                                       "Timeout pretrigger",
                                       "Pretrig Non Enclenc"  };

const STR *const StrEQ_19[] =   {      "EQ19",
                                       "EQ19",
                                       "EQ19",
                                       "EQ19",
                                       "EQ19"   };

const STR *const StrEQ_20[] =   {      "Recalibrate Actuator",
                                       "VE neu kalibrier.",
                                       "Recalibrar Actuador",
                                       "Ricalibra attuatore",
                                       "Recalibrer Actuator"  };

const STR *const StrEQ_21[] =   {      "Act Clear Function",
                                       "Funktion VE frei",
                                       "Funcion Liber Actd",
                                       "Funzion svuot. att",
                                       "Fonction Degmt Act"  };

const STR *const StrEQ_22[] =   {      "Stack",
                                       "Akust.",
                                       "Pila",
                                       "Stack",
                                       "Stack"  };

const STR *const StrEQ_23[] =   {      "Start Switches Lost",
                                       "Startsignal verlor.",
                                       "Seyal inicio Perd",  
                                       "Int. avvio perduti",
                                       "Boutons Start Perdus"  };

const STR *const StrEQ_24[] =   {      "Actuator Type",
                                       "VE Typ",
                                       "Tipo Actuador",
                                       "Tipo attuator",
                                       "Type Actuator"  };

const STR *const StrEQ_25[] =   {      "Sys. Pres. Incorrect",
                                       "Systemdruck falsch",
                                       "Pres Sist Incorrecta",
                                       "Pres. sist. errata",
                                       "Press. Syst. Incorr."  };

const STR *const StrEQ_26[] =   {      "EQ26",
                                       "EQ26",  
                                       "EQ26", 
                                       "EQ26", 
                                       "EQ26"  }; 

const STR *const StrEQ_27[] =   {      "EQ27",
                                       "EQ27",  
                                       "EQ27", 
                                       "EQ27", 
                                       "EQ27"  }; 



/* ----  This group contains the cycle modified strings  ---- */

const STR *const StrCM_1 [] =   {      "Trigger Lost in Hold",
                                       "Haltezeit Trig. verl",
                                       "Disp Perdido en Mant",
                                       "Trigger perduto raff",
                                       "Trig Perdu en Maint."  };

const STR *const StrCM_2 [] =   {      "Ground Detect Abort",
                                       "Metallkont. Abbr.",
                                       "Detec Tierra Cancel", 
                                       "Ground Detect Inter",
                                       "Interrup Detec Masse"  };

const STR *const StrCM_3 [] =   {      "Max Timeout",
                                       "Max Zeitueber.",
                                       "Tmp Max Exc",
                                       "Timeout max",
                                       "Delai Max"  };

const STR *const StrCM_4 [] =   {      "No Amplitude Step",
                                       "Kein Ampl. Prof.",
                                       "Sin Paso Amplitud",
                                       "No Step ampiezza",
                                       "Aucun Saut d'Ampl"  };

const STR *const StrCM_5 [] =   {      "No Force Step",
                                       "Kein Kraftprof.",
                                       "Sin Pso Fuerz",
                                       "No Step forza",
                                       "Aucun Saut Fce"  };

const STR *const StrCM_6 [] =   {      "No Amplitude Step",
                                       "Kein Ampl. Prof.",
                                       "Sin Paso Amplitud",
                                       "No Step ampiezza",
                                       "Aucun Saut d'Ampl"  };

const STR *const StrCM_7 [] =   {      "No Force Step",
                                       "Kein Kraftprof.",
                                       "Sin Pso Fuerz",
                                       "No Step forza",
                                       "Aucun Saut Fce"  };

const STR *const StrCM_8 [] =   {      "No Amplitude Step",
                                       "Kein Ampl. Prof.",
                                       "Sin Paso Amplitud",
                                       "No Step ampiezza",
                                       "Aucun Saut d'Ampl"  };

const STR *const StrCM_9 [] =   {      "No Amplitude Step",
                                       "Kein Ampl. Prof.",
                                       "Sin Paso Amplitud",
                                       "No Step ampiezza",
                                       "Aucun Saut d'Ampl"  };

const STR *const StrCM_10[] =   {      "No Force Step",
                                       "Kein Kraftprof.",
                                       "Sin Pso Furza",
                                       "No Step forza",
                                       "Aucun Saut Fce"  };

const STR *const StrCM_11[] =   {      "No Amplitude Step",
                                       "Kein Ampl. Prof.",
                                       "Sin Paso Amplitud",
                                       "No Step ampiezza",
                                       "Aucun Saut d'Ampl"  };

const STR *const StrCM_12[] =   {      "No Amplitude Step",
                                       "Kein Ampl. Prof.",
                                       "Sin Paso Amplitud",
                                       "No Step ampiezza",
                                       "Aucun Saut d'Ampl"  };

const STR *const StrCM_13[] =   {      "No Force Step",
                                       "Kein Kraftprof.",
                                       "Sin Pso Fuerz",
                                       "No Step forza",
                                       "Aucun Saut Fce"  };

const STR *const StrCM_14[] =   {      "Trigger Lost in Weld",
                                       "Trig. bei Schw. verl",
                                       "Disp perdido en sold",
                                       "Trig pers drnt sald",
                                       "Trigg. Perdu en Soud"  };

const STR *const StrCM_15[] =   {      "External Cycle Abort",
                                       "Extern Zykl. Abbruch",
                                       "External Cycle Abort",
                                       "Annulla ciclo estern",
                                       "Interrupt Cycle Ext."  };

const STR *const StrCM_16[] =   {      "Amp B Not Reached",
                                       "Amp B ni erreicht",
                                       "Amp B No Alcanzad",
                                       "Amp B non ragiunt",
                                       "Amp B Non Attein."  };

const STR *const StrCM_17[] =   {      "Memory Reset",
                                       "Speicher loesch",
                                       "Reset memoria",
                                       "Reset memoria",
                                       "Reset memoire"  };

const STR *const StrCM_17A[] =  {      "Short pins 1 & 2",
                                       "Short pins 1 & 2",
                                       "Short pins 1 & 2",
                                       "Short pins 1 & 2",
                                       "Short pins 1 & 2" };

const STR *const StrCM_17B[] =   {     "with jumper J55",
                                       "with jumper J55",
                                       "with jumper J55",
                                       "with jumper J55",
                                       "with jumper J55"  };                                       

const STR *const StrCM_17C[] =   {     "on power supply.",
                                       "on power supply.",
                                       "on power supply.",
                                       "on power supply.",
                                       "on power supply."  };                                       

const STR *const StrCM_18[] =   {      "Amp A Not Reached",
                                       "Amp A ni erreicht",
                                       "Amp A No Alcanzad",
                                       "Amp A non ragiunt",
                                       "Amp B Non Attein."  };

const STR *const StrCM_19[] =   {      "Amp B Not Reached",
                                       "Amp B ni erreicht",
                                       "Amp B No Alcanzad",
                                       "Amp B non ragiunt",
                                       "Amp B Non Attein."  };

const STR *const StrCM_20[] =   {      "Amp Exceeded",
                                       "Ampl. Ueberschr.",
                                       "Amp Superada",
                                       "Amp superata",
                                       "Amp Depassee"  };

const STR *const StrCM_21[] =   {      "Energy Not Reached",
                                       "Energie ni erreicht",
                                       "Energi No alcanzad",
                                       "Energ non raggiunt", 
                                       "Energ. Non Attein."  };

const STR *const StrCM_22[] =   {      "Trigger > End Force",
                                       "Trigger > Endkraft",                                                   
                                       "Disparo > Fuerz Fin",
                                       "Trigger > Forz fina",
                                       "Trigger > Force Fin"  };

const STR *const StrCM_23[] =   {      "No Force Step",
                                       "Kein Kraftprof.",
                                       "Sin Pso Fuerz",
                                       "No Step forza",
                                       "Aucun Saut Fce"  };

const STR *const StrCM_24[] =   {      "CM24",
                                       "CM24",  
                                       "CM24", 
                                       "CM24", 
                                       "CM24"  }; 

const STR *const StrCM_25[] =   {      "CM25",
                                       "CM25",  
                                       "CM25", 
                                       "CM25", 
                                       "CM25"  }; 

const STR *const StrCM_26[] =   {      "CM26",
                                       "CM26",  
                                       "CM26", 
                                       "CM26", 
                                       "CM26"  }; 

const STR *const StrCM_27[] =   {      "CM27",
                                       "CM27",  
                                       "CM27", 
                                       "CM27", 
                                       "CM27"  }; 



/* ----  This group contains the calibrate strings  ---- */

const STR *const StrCA_1 [] =   {      "CA1", 
                                       "CA1",  
                                       "CA1", 
                                       "CA1", 
                                       "CA1"  }; 

const STR *const StrCA_2 [] =   {      "CA2",
                                       "CA2",  
                                       "CA2", 
                                       "CA2", 
                                       "CA2"  }; 

const STR *const StrCA_3 [] =   {      "CA3",
                                       "CA3",  
                                       "CA3", 
                                       "CA3", 
                                       "CA3"  }; 

const STR *const StrCA_4 [] =   {      "CA4",
                                       "CA4",  
                                       "CA4", 
                                       "CA4", 
                                       "CA4"  }; 

const STR *const StrCA_5 [] =   {      "CA5",
                                       "CA5",  
                                       "CA5", 
                                       "CA5", 
                                       "CA5"  }; 

const STR *const StrCA_6 [] =   {      "CA6",
                                       "CA6",  
                                       "CA6", 
                                       "CA6", 
                                       "CA6"  }; 

const STR *const StrCA_7 [] =   {      "CA7",
                                       "CA7",  
                                       "CA7", 
                                       "CA7", 
                                       "CA7"  }; 

const STR *const StrCA_8 [] =   {      "CA8",
                                       "CA8",  
                                       "CA8", 
                                       "CA8", 
                                       "CA8"  }; 

const STR *const StrCA_9 [] =   {      "CA9",
                                       "CA9",  
                                       "CA9", 
                                       "CA9", 
                                       "CA9"  }; 

const STR *const StrCA_10[] =   {      "CA10",
                                       "CA10",  
                                       "CA10", 
                                       "CA10", 
                                       "CA10"  }; 

const STR *const StrCA_11[] =   {      "CA11",
                                       "CA11",  
                                       "CA11", 
                                       "CA11", 
                                       "CA11"  }; 

const STR *const StrCA_12[] =   {      "CA12",
                                       "CA12",  
                                       "CA12", 
                                       "CA12", 
                                       "CA12"  }; 

const STR *const StrCA_13[] =   {      "CA13",
                                       "CA13",  
                                       "CA13", 
                                       "CA13", 
                                       "CA13"  }; 

const STR *const StrCA_14[] =   {      "CA14",
                                       "CA14",  
                                       "CA14", 
                                       "CA14", 
                                       "CA14"  }; 

const STR *const StrCA_15[] =   {      "CA15",
                                       "CA15",  
                                       "CA15", 
                                       "CA15", 
                                       "CA15"  }; 

const STR *const StrCA_16[] =   {      "CA16",
                                       "CA16",  
                                       "CA16", 
                                       "CA16", 
                                       "CA16"  }; 

const STR *const StrCA_17[] =   {      "CA17",
                                       "CA17",  
                                       "CA17", 
                                       "CA17", 
                                       "CA17"  }; 

const STR *const StrCA_18[] =   {      "CA18",
                                       "CA18",  
                                       "CA18", 
                                       "CA18", 
                                       "CA18"  }; 

const STR *const StrCA_19[] =   {      "CA19",
                                       "CA19",  
                                       "CA19", 
                                       "CA19", 
                                       "CA19"  }; 

const STR *const StrCA_20[] =   {      "CA20",
                                       "CA20",  
                                       "CA20", 
                                       "CA20", 
                                       "CA20"  }; 

const STR *const StrCA_21[] =   {      "CA21",
                                       "CA21",  
                                       "CA21", 
                                       "CA21", 
                                       "CA21"  }; 

const STR *const StrCA_22[] =   {      "CA22",
                                       "CA22",  
                                       "CA22", 
                                       "CA22", 
                                       "CA22"  }; 

const STR *const StrCA_23[] =   {      "CA23",
                                       "CA23",  
                                       "CA23", 
                                       "CA23", 
                                       "CA23"  }; 

const STR *const StrCA_24[] =   {      "CA24",
                                       "CA24",  
                                       "CA24", 
                                       "CA24", 
                                       "CA24"  }; 

const STR *const StrCA_25[] =   {      "CA25",
                                       "CA25",  
                                       "CA25", 
                                       "CA25", 
                                       "CA25"  }; 

const STR *const StrCA_26[] =   {      "CA26",
                                       "CA26",  
                                       "CA26", 
                                       "CA26", 
                                       "CA26"  }; 

const STR *const StrCA_27[] =   {      "CA27",
                                       "CA27",  
                                       "CA27", 
                                       "CA27", 
                                       "CA27"  }; 



/* ----  This group contains the warning strings  ---- */


const STR *const StrWA_1 [] =   {      "Act Clr Not Reached",
                                       "VE frei ni erreicht",
                                       "Lbr Act No Alcanzad",
                                       "Svuot. att non ragg",
                                       "Deg Act Non Attein."  };

const STR *const StrWA_2 [] =   {      "Max Energy Reached",
                                       "Max Energ. Erreicht",
                                       "Max Enrg Alcanzada",
                                       "Energ max raggiunt",  
                                       "Ener. Max Atteinte"  };

const STR *const StrWA_3 [] =   {      "Printer Buffer 80%",
                                       "Druckerpuffer 80%",
                                       "Memo Impresora 80%",
                                       "Buffer stmpnt 80%",
                                       "Mm Tpn Imp Pln 80%"  }; 

const STR *const StrWA_4 [] =   {      "Cont Pwr Limit",
                                       "Kont. Leist. Grnz.",
                                       "Lte Poten Cont",
                                       "Limit pot cont",
                                       "Lim. Puis Cont"  };

const STR *const StrWA_5 [] =   {      "Peak Power Cutoff",
                                       "Spitzenleist. Absch.",
                                       "Corte Pico Poten",
                                       "Interr pic pot",
                                       "Interrup.Pui. Crete"  };

const STR *const StrWA_6 [] =   {      "Absolute Cutoff",
                                       "Abs. Absch.",
                                       "Corte Absoluto",
                                       "Cutoff Dist Ass",
                                       "Arret sur Absol"  };

const STR *const StrWA_6A[] =   {      "Actual = End of hold",
                                       "Akt. = Ende Halten",
                                       "Actual = Fin de Mant",
                                       "Reale = Fine raffred",
                                       "Reelle = Fin Maint."  };

const STR *const StrWA_7 [] =   {      "Time Extended",
                                       "Zeit verlaeng.",
                                       "Tmpo Ampliado",
                                       "Prolung tempo",
                                       "Temps Etendu"  };

const STR *const StrWA_8 [] =   {      "Act Recal Suggested",
                                       "VE Neukal vorgeschl.",
                                       "Memori Act Recomend",
                                       "Consigliat rich att",
                                       "Recalibrer Act"  };

const STR *const StrWA_8A[] =   {      "Do Calibration Now",
                                       "Kalibriere jetzt",
                                       "Calibre ahora     ",
                                       "Eseg calibra subit",
                                       "Calibrer maintenant"  };

const STR *const StrWA_9 [] =   {      "Collapse Cutoff",
                                       "Rel. Abschaltung",
                                       "Corte por Colps",
                                       "Interzne Collasso",
                                       "Cpure Dist Rel."  };

const STR *const StrWA_10[] =   {      "Act Clr Not Reached",
                                       "VE frei ni erreicht",
                                       "Lbr Act No Alcanzad",
                                       "Svuot. att non ragg",
                                       "Deg Act Non Attein."  };

const STR *const StrWA_11[] =   {      "Sonics Disabled",
                                       "Schall deaktiviert",  
                                       "Desactivar ultr.", 
                                       "Sonics Disabled", 
                                       "US Desactivés"  }; 

const STR *const StrWA_12[] =   {      "WA12",
                                       "WA12",  
                                       "WA12", 
                                       "WA12", 
                                       "WA12"  }; 

const STR *const StrWA_13[] =   {      "WA13",
                                       "WA13",  
                                       "WA13", 
                                       "WA13", 
                                       "WA13"  }; 

const STR *const StrWA_14[] =   {      "WA14",
                                       "WA14",  
                                       "WA14", 
                                       "WA14", 
                                       "WA14"  }; 

const STR *const StrWA_15[] =   {      "WA15",
                                       "WA15",  
                                       "WA15", 
                                       "WA15", 
                                       "WA15"  }; 

const STR *const StrWA_16[] =   {      "WA16",
                                       "WA16",  
                                       "WA16", 
                                       "WA16", 
                                       "WA16"  }; 

const STR *const StrWA_17[] =   {      "WA17",
                                       "WA17",  
                                       "WA17", 
                                       "WA17", 
                                       "WA17"  }; 

const STR *const StrWA_18[] =   {      "WA18",
                                       "WA18",  
                                       "WA18", 
                                       "WA18", 
                                       "WA18"  }; 

const STR *const StrWA_19[] =   {      "WA19",
                                       "WA19",  
                                       "WA19", 
                                       "WA19", 
                                       "WA19"  }; 

const STR *const StrWA_20[] =   {      "WA20",
                                       "WA20",  
                                       "WA20", 
                                       "WA20", 
                                       "WA20"  }; 

const STR *const StrWA_21[] =   {      "WA21",
                                       "WA21",  
                                       "WA21", 
                                       "WA21", 
                                       "WA21"  }; 

const STR *const StrWA_22[] =   {      "WA22",
                                       "WA22",  
                                       "WA22", 
                                       "WA22", 
                                       "WA22"  }; 

const STR *const StrWA_23[] =   {      "WA23",
                                       "WA23",  
                                       "WA23", 
                                       "WA23", 
                                       "WA23"  };

const STR *const StrWA_24[] =   {      "WA24",
                                       "WA24",  
                                       "WA24", 
                                       "WA24", 
                                       "WA24"  }; 

const STR *const StrWA_25[] =   {      "WA25",
                                       "WA25",  
                                       "WA25", 
                                       "WA25", 
                                       "WA25"  }; 

const STR *const StrWA_26[] =   {      "WA26",
                                       "WA26",
                                       "WA26", 
                                       "WA26", 
                                       "WA26"  }; 

const STR *const StrWA_27[] =   {      "WA27",
                                       "WA27",   
                                       "WA27", 
                                       "WA27", 
                                       "WA27"  }; 




/* ----  This group contains the process reject strings  ---- */

const STR *const StrPR_1 [] =    {     "-R Energy Limit",
                                       "-A Energiegrnz.",
                                       "-R Lte Energia",
                                       "-R Lim dist ass",
                                       "Lim.R- Energie"  };

const STR *const StrPR_2 [] =    {     "+R Energy Limit",
                                       "+A Energiegrnz.",
                                       "+R Lte Energia",
                                       "+R Lim dist ass",
                                       "Lim.R+ Energie"  };

const STR *const StrPR_3 [] =    {     "-R Pk Power Limit",
                                       "-A Spitzenlst. Grnz.",
                                       "-R Lte Pico Ptncia",
                                       "-R Limite pic pot",
                                       "Lim.R- Pui.Crete"  };

const STR *const StrPR_4 [] =    {     "+R Pk Power Limit",
                                       "+A Spitzenlst. Grnz.",
                                       "+R Lte Pico Ptncia",
                                       "+R Limite pic pot",
                                       "Lim.R+ Pui.Crete"  };

const STR *const StrPR_5 [] =    {     "-R Col Dist Limit",
                                       "-A Weg rel Grnz.",
                                       "-R Lte Dist Col",
                                       "-R Lim dist col",
                                       "Lim.R- Dist Rel"  };

const STR *const StrPR_6 [] =    {     "+R Col Dist Limit",
                                       "+A Weg rel Grnz.",
                                       "+R Lte Dist Col",
                                       "+R Lim dist col",
                                       "Lim.R+ Dist Rel"  };

const STR *const StrPR_7 [] =    {     "-R Abs Dist Limit",
                                       "-A Weg abs Grnz.",
                                       "-R Lte Dist Abs",
                                       "-R Lim dist ass",
                                       "Lim.R- Dist Abs"  };

const STR *const StrPR_8 [] =    {     "+R Abs Dist Limit",
                                       "+A Weg abs Grnz.",
                                       "+R Lte Dist Abs",
                                       "+R Lim dist ass",
                                       "Lim.R+ Dist Abs"  };

const STR *const StrPR_9 [] =    {     "-R Trg Dist Limit",
                                       "-A Trig. Weg Grnz.",
                                       "-R Lte Dist Dsp",
                                       "-R Trg Dist Limit",
                                       "Lim.R- Dist Trg"  };

const STR *const StrPR_10[] =    {     "+R Trg Dist Limit",
                                       "+A Trig. Weg Grnz.",
                                       "+R Lte Dist Dsp",
                                       "+R Lim dist Trg",
                                       "Lim.R+ Dist Trg"  };

const STR *const StrPR_11[] =    {     "-R Weld Force Limit",
                                       "-A Schw.Kraft Grnz.",
                                       "-R Lte Frza Soldad",
                                       "-R Limite forz sald",  
                                       "Lim.R- Force Soud."  };

const STR *const StrPR_12[] =    {     "+R Weld Force Limit",
                                       "+A Schw.Kraft Grnz.",
                                       "+R Lte Frza Soldad",
                                       "+R Limite forz sald",  
                                       "Lim.R+ Force Soud."  };

const STR *const StrPR_13[] =    {     "-R Time Limit",
                                       "-A Zeitgrenz.",
                                       "-R Lte Tiempo",
                                       "-R Lim tempo",
                                       "Lim.R- Tps"  };

const STR *const StrPR_14[] =    {     "+R Time Limit",
                                       "+A Zeitgrenz.",
                                       "+R Lte Tiempo",
                                       "+R Lim tempo",
                                       "Lim.R+ Tps"  };

const STR *const StrPR_15[] =   {      "PR15",
                                       "PR15",   
                                       "PR15",
                                       "PR15",
                                       "PR15"  };

const STR *const StrPR_16[] =   {      "PR16",
                                       "PR16",   
                                       "PR16",
                                       "PR16",
                                       "PR16"  };

const STR *const StrPR_17[] =   {      "PR17",
                                       "PR17", 
                                       "PR17",
                                       "PR17",
                                       "PR17"  };

const STR *const StrPR_18[] =   {      "LL Not Reached",
                                       "LL nicht erreicht",
                                       "LL No Alcnzada",
                                       "LL non ragg.",
                                       "LL Non Attein."  };

const STR *const StrPR_19[] =   {      "PR19",
                                       "PR19",
                                       "PR19",
                                       "PR19",
                                       "PR19"  };

const STR *const StrPR_20[] =   {      "PR20",
                                       "PR20",
                                       "PR20",
                                       "PR20",
                                       "PR20"  };

const STR *const StrPR_21[] =   {      "PR21",
                                       "PR21",
                                       "PR21",
                                       "PR21",
                                       "PR21"  };

const STR *const StrPR_22[] =   {      "PR22",
                                       "PR22",
                                       "PR22",
                                       "PR22",
                                       "PR22"  };

const STR *const StrPR_23[] =   {      "PR23",
                                       "PR23",
                                       "PR23",
                                       "PR23",
                                       "PR23"  };

const STR *const StrPR_24[] =   {      "PR24",
                                       "PR24",
                                       "PR24",
                                       "PR24",
                                       "PR24"  };

const STR *const StrPR_25[] =   {      "PR25",
                                       "PR25",
                                       "PR25",
                                       "PR25",
                                       "PR25"  };

const STR *const StrPR_26[] =   {      "PR26",
                                       "PR26",
                                       "PR26",
                                       "PR26",
                                       "PR26"  };

const STR *const StrPR_27[] =   {      "PR27",
                                       "PR27",
                                       "PR27",
                                       "PR27",
                                       "PR27"  };




/* ----  This group contains the process suspect strings  ---- */

const STR *const StrPS_1 [] =    {     "-S Energy Limit",
                                       "-P Energiegrnz.",
                                       "-S Lte Energia",
                                       "-S Lim energia",
                                       "Lim.S- Energie"  };

const STR *const StrPS_2 [] =    {     "+S Energy Limit",
                                       "+P Energiegrnz.",
                                       "+S Lte Energia",
                                       "+S Lim energia",
                                       "Lim.S+ Energie"  };

const STR *const StrPS_3 [] =    {     "-S Pk Power Limit",
                                       "-P Spitzenlst. Grnz.",
                                       "-S Lte Pico Ptncia",
                                       "-S Limite pic pot",
                                       "Lim.S- Pui.Crete"  };

const STR *const StrPS_4 [] =    {     "+S Pk Power Limit",
                                       "+P Spitzenlst. Grnz.",
                                       "+S Lte Pico Ptncia",
                                       "+S Limite pic pot",
                                       "Lim.S+ Pui.Crete"  };

const STR *const StrPS_5 [] =    {     "-S Col Dist Limit",
                                       "-P Weg rel Grnz.",
                                       "-S Lte Dist Col",
                                       "-S Lim dist col",
                                       "Lim.S- Dist Rel"  };

const STR *const StrPS_6 [] =    {     "+S Col Dist Limit",
                                       "+P Weg rel Grnz.",
                                       "+S Lte Dist Col",
                                       "+S Lim dist col",
                                       "Lim.S+ Dist Rel"  };

const STR *const StrPS_7 [] =    {     "-S Abs Dist Limit",
                                       "-P Weg abs Grnz.",
                                       "-S Lte Dist Abs",
                                       "-S Lim dist ass",
                                       "Lim.S- Dist Abs"  };

const STR *const StrPS_8 [] =    {     "+S Abs Dist Limit",
                                       "+P Weg abs Grnz.",
                                       "+S Lte Dist Abs",
                                       "+S Lim dist ass",
                                       "Lim.S+ Dist Abs"  };

const STR *const StrPS_9 [] =    {     "-S Trg Dist Limit",
                                       "-P Trig. Weg Grnz.",
                                       "-S Lte Dist Dsp",
                                       "-S Lim dist Trg",
                                       "Lim.S- Dist. Trg"  };

const STR *const StrPS_10[] =    {     "+S Trg Dist Limit",
                                       "+P Trig. Weg Grnz.",
                                       "+S Lte Dist Dsp",
                                       "+S Lim dist Trg",
                                       "Lim.S+ Dist. Trg"  };

const STR *const StrPS_11[] =    {     "-S Weld Force Limit",
                                       "-P Schw. Kraft Grnz.",
                                       "-S Lte Frza Soldad",
                                       "-S Lim forza sald",
                                       "Lim.S- Force Soud."  };

const STR *const StrPS_12[] =    {     "+S Weld Force Limit",
                                       "+P Schw. Kraft Grnz.",
                                       "+S Lte Frza Soldad",
                                       "+S Lim forza sald",
                                       "Lim.S+ Force Soud."  };

const STR *const StrPS_13[] =    {     "-S Time Limit",
                                       "-P Zeitgrenz.",
                                       "-S Lte Tiempo",
                                       "-S Lim tempo",
                                       "Lim.S- Tps"  };

const STR *const StrPS_14[] =    {     "+S Time Limit",
                                       "+P Zeitgrenz.",
                                       "+S Lte Tiempo",
                                       "+S Lim tempo",
                                       "Lim.S+ Tps"  };

const STR *const StrPS_15[] =   {      "PS15",
                                       "PS15", 
                                       "PS15",
                                       "PS15",
                                       "PS15"  };

const STR *const StrPS_16[] =   {      "PS16",
                                       "PS16", 
                                       "PS16",
                                       "PS16",
                                       "PS16"  };

const STR *const StrPS_17[] =   {      "PS17",
                                       "PS17", 
                                       "PS17",
                                       "PS17",
                                       "PS17"  };

const STR *const StrPS_18[] =   {      "PS18",
                                       "PS18", 
                                       "PS18",
                                       "PS18",
                                       "PS18"  };

const STR *const StrPS_19[] =   {      "PS19",
                                       "PS19", 
                                       "PS19",
                                       "PS19",
                                       "PS19"  };

const STR *const StrPS_20[] =   {      "PS20",
                                       "PS20", 
                                       "PS20",
                                       "PS20",
                                       "PS20"  };

const STR *const StrPS_21[] =   {      "PS21",
                                       "PS21", 
                                       "PS21",
                                       "PS21",
                                       "PS21"  };

const STR *const StrPS_22[] =   {      "PS22",
                                       "PS22", 
                                       "PS22",
                                       "PS22",
                                       "PS22"  };

const STR *const StrPS_23[] =   {      "PS23",
                                       "PS23", 
                                       "PS23",
                                       "PS23",
                                       "PS23"  };

const STR *const StrPS_24[] =   {      "PS24",
                                       "PS24", 
                                       "PS24",
                                       "PS24",
                                       "PS24"  };

const STR *const StrPS_25[] =   {      "PS25",
                                       "PS25", 
                                       "PS25",
                                       "PS25",
                                       "PS25"  };

const STR *const StrPS_26[] =   {      "PS26",
                                       "PS26", 
                                       "PS26",
                                       "PS26",
                                       "PS26"  };

const STR *const StrPS_27[] =   {      "PS27",
                                       "PS27", 
                                       "PS27",
                                       "PS27",
                                       "PS27"  };


/* ----  This group contains the strings for new variables in new alarms created by Barry Kymer ---- */

const STR *const StrMaximumForce []= { "Max Force(&&)",
                                       "Max. Kraft(&&)",
                                       "Max Force(&&)",
                                       "Max Force(&&)",
                                       "Max Force(&&)"  };

const STR *const StrSE277GoToHornDown [] =   {
                                       "Press Horndown",
                                       "Druecke Horn down",
                                       "Pulse Horndown",
                                       "Prem Rid sono",
                                       "Press. Dsc Sontr"  };

const STR *const StrSE277AdjSystemRegulator[] = {
                                       "Adj. Sys. Regulator",
                                       "Syst. Regler einst.",
                                       "Ajste regulador sis",
                                       "Reg. regolatore sis",
                                       "Ajust. Regul. Syst."  };

const STR *const StrSE268ErrorCode[] = {
                                       "Error Code",
                                       "Fehlercode",
                                       "Cod errore",
                                       "Cod errore",
                                       "Cod Erreur"  };








/*--------------------------------- CODE -----------------------------------*/


