/* $Header:   D:/SWLab/VMdb/2000Series/INC/LIMARRAY.H_V   1.48   May 04 2007 16:46:40   nhahmed  $ */
#ifndef _LIMARRAY_H
#define _LIMARRAY_H

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

 /*---------------------------- MODULE DESCRIPTION --------------------------

    Module name: limarray

    Filename: limarray.h

    Function name:

 --------------------------------- REVISIONS --------------------------------

 Revision #  Date        Author   Description
 ==========  ========    ======   ===========
 0                       PaulG    Initial Version                   
  1.1.3      07/21/97    LAM      added enum for control level table
  1.1.6      07/23/97    LAM      added normal enums to  control level table
  1.1.10     07/24/97    LAM      chged amplitudea                          
  1.1.12     07/24/97    LAM      updated limits tables                    
  1.1.13     07/24/97    PaulG    Updated limits tables(contd1.)                    
  1.1.14     07/25/97    PaulG    Updated limits tables(contd2.)                    
  1.1.15     09.04.97    JBerman  DCS# 1948 corrections
  1.1.16     09.18.97    JBerman  DCS# 1948 corrections
  1.1.17     09-24-97    PaulG    Made FORMFEED NOTAVAIL.
  1.1.18     10-09-97    PaulG    Lineup rows and columns.
  1.1.19     12.04.97    JBerman  Added STRTSCREEN
  1.1.20     12.11.97    JBerman  Added TMODONLY
  1.1.22     02.02.98    JBerman  AVAIL PPOWERGRAPH from level 2(E).  
  1.1.23     02.05.98    JBerman  Setup On Sample: Changed PSETUP to be 
                                                          AVAIL for all levels.
  1.1.24     03.10.98    JBerman  PFEATURES-> Fixed to NOTAVAIL in level 1.
  1.1.25     05.13.98    JBerman  Changeg to AVAIL at level 4 & 5
  1.1.26     05.14.98    PaulG    Added  DIGITALTUNE for Digital Tune.
  1.1.27     05.18.98    JBerman  Changed PACTLIFETIME/level 4&5 to NOTAVAIL; 
                                                       ActLifeTime is a future Rel.
  1.1.28     06.04.98    JBerman  Changed PAMPLITUDEA1, AND PAMPLITUDEB from
                                  NOTAVAIL to AVAIL. 
  1.1.29     06.05.98    JBerman  PFEATURES  from level t; DCS 2567.
  1.1.30     06.08.98    JBerman  PritOut Setup; DCS 2608.
  1.1.31     06.12.98    JBerman  Force Graph on Sample/Alarm from level 4; DCS 2639.
  1.1.32     06.25.98    JBerman  Clean printout setup.
  1.1.33     06.26.98    JBerman  Clean printout setup.
  1.1.34     07.02.98    JBerman  Clean printout setup.
  1.1.35     10.29.98    PaulG    Replace AVAIL with ACTDF for PACTSERNUM.
  1.35.4.1   08.19.99    JLH      Replace PFORCEHORNDOWN with PCALINFO.
                                  Replace PDOWNSPEEDHORNDOWN with PCALDATE.
  1.35.4.2   09.08.99    JLH      Allow rapid traverse printing for level 5.
  1.37       12.06.99    JLH      Allow weld history printing for level 3.
  1.38       01-26-00    JZ       fixed rejects and suspects for AE/f case in printout setup 
  1.39       02-09-00    OFI      Made "+" and "-" Rej. and Sus. printable in Collapse Mode
  1.40       02-17-00    JZ       enabled  PFREQUENCYGRAPH for control level a
  1.41       03-27-00    JZ       changed PNORMALE to AVAILLE in SUSPECT  CONTROL LEVEL #4 and cleaned tabs
  1.42       04-11-00    JLH      Merged with Lang branch revision 1.38.6.2.
  1.43       05-26-00    JLH      Set collapse limits to AVAILLE when in collapse mode for Suspect #4 and
                                   Suspect #5 tables, and also for Reject #4 and Reject #5 tables.
  1.44       09-06-01    BEKymer  Make changes for 8.3S (Energy limits in energy mode)
                                   Clean up control levels 1,2,3 vs t,e,d
  1.45       06-02-04    VSharma  Modified parameterControlLevel[].
                                  Added PRELEASEBEEPER,PEXTPRESETS & PWRITEINFIELD
                                   in enum PARAMNUM.                                                       
  1.46       03-27-07    NHAhmed  Modified parameterControlLevel[] for VQSDatalimit 
                                  Modified Enum PARAMNUM for VQSData limits functions
                                  ID from 144-159
  1.47       04-18-07    NHAhmed  Modified parameterControlLevel[] for Scrub Amplitude.
  1.48       05-04-07    NHAhmed  Modified parameterControlLevel[] for Peak Power(Tracker #4110).
 ------------------------------- DESCRIPTION --------------------------------*/


/*------------------------------ LOCAL DEFINES ------------------------------*/


#define MAXLEVELS       5
#define MAXLEVELL       10
#define MAXLIMITS       17
#define MAXWELDMODES    7

enum PRINTFLAG{             /* Checked to see if should be printed   */
   ACTDF,                   // Print if AED|AOD|AEF|AOF
   NOTAVAIL,                /* not printed                           */
   AVAIL,                   /* printed                               */
   AVAILLE,                 /* printed when encoder present          */
   TMODONLY };              /* Print while in TimeMode Only */




extern UINT16 ControlLevelLimit(UINT16);
extern UINT16 CheckIfPrintable(UINT16);


// Welder Control Level Limits
const UINT16 controlLevel[MAXLEVELL][MAXLIMITS][MAXWELDMODES] = {

// Suspect Limits
// Time    Energy    Pk. Pwr.  Collapse Absolute Grd.Detect  Cont.
// Mode     Mode      Mode       Mode     Mode      Mode     Mode

   {  // SUSPECT CONTROL LEVEL t (old level #1)

 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //0  Time + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //1  Time - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //2  Energy + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //3  Energy - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //4  Power + Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //5  Power - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //6  Collapse + Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //7  Collapse - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //8  Absolute + Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //9  Absolute - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //10 Trig. Dist + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //11 Trig. Dist - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //12 Max Force + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //13 Max Force - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //14 Freq. + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //15 Freq. - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL  //16 Max Force +/- R Limit
   },

// Suspect Limits
//   Time     Energy   Pk. Pwr. Collaps  Absolute   Gr. Det.    Cont.
//   Mode     Mode     Mode      Mode    Mode        Mode        Mode

   {  // SUSPECT CONTROL LEVEL e (old level #2 no longer used)

 NOTAVAIL, AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, AVAIL,    NOTAVAIL, //0  Time + Limit
 NOTAVAIL, AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, AVAIL,    NOTAVAIL, //1  Time - Limit
 AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //2  Energy + Limit
 AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //3  Energy - Limit
 AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //4  Power + Limit 
 AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //5  Power - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //6  Collapse + Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //7  Collapse - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //8  Absolute + Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //9  Absolute - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //10 Trig. Dist + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //11 Trig. Dist - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //12 Max Force + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //13 Max Force - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //14 Freq. + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //15 Freq. - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL  //16	Max Force +/- R Limit
   },

// Suspect Limits
//	Time     Energy   Pk. Pwr. Collaps    Absolute  Gr. Det.   Cont
//	Mode     Mode     Mode     Mode       Mode      Mode       Mode
  
     { // SUSPECT CONTROL LEVEL ea (old level #3 and a)

 NOTAVAIL, AVAIL,    AVAIL,    AVAILLE, AVAILLE,  AVAIL,    NOTAVAIL, //0  Time + Limit
 NOTAVAIL, AVAIL,    AVAIL,    AVAILLE, AVAILLE,  AVAIL,    NOTAVAIL, //1  Time - Limit
 AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE,  NOTAVAIL, NOTAVAIL, //2  Energy + Limit
 AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE,  NOTAVAIL, NOTAVAIL, //3  Energy - Limit
 AVAIL,    AVAIL,    NOTAVAIL, AVAILLE, AVAILLE,  NOTAVAIL, NOTAVAIL, //4  Power + Limit 
 AVAIL,    AVAIL,    NOTAVAIL, AVAILLE, AVAILLE,  NOTAVAIL, NOTAVAIL, //5  Power - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL, //6  Collapse + Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL, //7  Collapse - Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, NOTAVAIL, AVAILLE,  NOTAVAIL, //8  Absolute + Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, NOTAVAIL, AVAILLE,  NOTAVAIL, //9  Absolute - Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE,  NOTAVAIL, NOTAVAIL, //10 Trig. Dist + Limit
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE,  NOTAVAIL, NOTAVAIL, //11 Trig. Dist - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL, //12 Max Force + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL, //13 Max Force - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL, //14 Freq. + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL, //15 Freq. - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL  //16	Max Force +/- R Limit
   },

// Suspect Limits
//	Time     Energy   Pk. Pwr. Collaps    Absolute  Gr. Det.   Cont
//	Mode     Mode     Mode     Mode       Mode      Mode       Mode

   { // SUSPECT  CONTROL LEVEL d (old level #4 )

 NOTAVAIL, AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL, //0  Time + Limit
 NOTAVAIL, AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL, //1  Time - Limit
 AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL, //2  Energy + Limit
 AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL, //3  Energy - Limit
 AVAIL,    AVAIL,    NOTAVAIL, AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL, //4  Power + Limit 
 AVAIL,    AVAIL,    NOTAVAIL, AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL, //5  Power - Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL, //6  Collapse + Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL, //7  Collapse - Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, NOTAVAIL,AVAILLE,  NOTAVAIL, //8  Absolute + Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, NOTAVAIL,AVAILLE,  NOTAVAIL, //9  Absolute - Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL, //10 Trig. Dist + Limit
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL, //11 Trig. Dist - Limit
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL, //12 Max Force + Limit
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL, //13 Max Force - Limit
 AVAIL ,   AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL, //14 Freq. + Limit
 AVAIL ,   AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL ,   NOTAVAIL, //15 Freq. - Limit
 ACTDF   , ACTDF   , ACTDF   , ACTDF   , ACTDF   , ACTDF   , ACTDF     //16	Max Force +/- R Limit
   },


// Suspect Limits
//	Time     Energy   Pk. Pwr. Collaps    Absolute  Gr. Det.   Cont
//	Mode     Mode     Mode     Mode       Mode      Mode       Mode

   { // SUSPECT CONTROL LEVEL f (old level #5 (EP))

	NOTAVAIL, AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL, //0  Time + Limit
	NOTAVAIL, AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL, //1  Time - Limit
	AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL, //2  Energy + Limit
	AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL, //3  Energy - Limit
	AVAIL,    AVAIL,    NOTAVAIL, AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL, //4  Power + Limit 
	AVAIL,    AVAIL,    NOTAVAIL, AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL, //5  Power - Limit 
	AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL, //6  Collapse + Limit 
	AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL, //7  Collapse - Limit 
	AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, NOTAVAIL,AVAILLE,  NOTAVAIL, //8  Absolute + Limit 
	AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, NOTAVAIL,AVAILLE,  NOTAVAIL, //9  Absolute - Limit 
	AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL, //10 Trig. Dist + Limit
	AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL, //11 Trig. Dist - Limit
	AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL, //12 Max Force + Limit
	AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL, //13 Max Force - Limit
	AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, AVAILLE,  NOTAVAIL, //14 Freq. + Limit
	AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, AVAILLE,  NOTAVAIL, //15 Freq. - Limit
    ACTDF   , ACTDF   , ACTDF   , ACTDF   , ACTDF   , ACTDF   , ACTDF     //16 Max Force +/- R Limit
   },

// Reject Limits
//  Time     Energy   Pk. Pwr.  Collaps   Absolute   Gr. Det.   Cont.     
//  Mode     Mode     Mode      Mode      Mode        Mode      Mode      
                                                                          
   {  // REJECT CONTROL LEVEL t (old level #1)
                                                                          
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //0  Time + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //1  Time - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //2  Energy + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //3  Energy - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //4  Power + Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //5  Power - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //6  Collapse + Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //7  Collapse - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //8  Absolute + Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //9  Absolute - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //10 Trig. Dist + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //11 Trig. Dist - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //12 Max Force + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //13 Max Force - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //14 Freq. + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //15 Freq. - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL  //16	Max Force +/- R Limit
   },

// Reject Limits
//   Time     Energy   Pk. Pwr. Collaps  Absolute   Gr. Det.    Cont.
//   Mode     Mode     Mode      Mode    Mode        Mode        Mode

   {  // REJECT CONTROL LEVEL e (old level #2, no longer used)

 NOTAVAIL, AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, AVAIL,    NOTAVAIL, //0  Time + Limit
 NOTAVAIL, AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, AVAIL,    NOTAVAIL, //1  Time - Limit
 AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //2  Energy + Limit
 AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //3  Energy - Limit
 AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //4  Power + Limit 
 AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //5  Power - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //6  Collapse + Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //7  Collapse - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //8  Absolute + Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //9  Absolute - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //10 Trig. Dist + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //11 Trig. Dist - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //12 Max Force + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //13 Max Force - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //14 Freq. + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //15 Freq. - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL //16	Max Force +/- R Limit
   },

// Reject Limits
//	Time     Energy   Pk. Pwr. Collaps    Absolute  Gr. Det.   Cont
//	Mode     Mode     Mode     Mode       Mode      Mode       Mode
  
     { // REJECT CONTROL LEVEL ea (old level #3 and a)

 NOTAVAIL, AVAIL,    AVAIL,    AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, //0  Time + Limit
 NOTAVAIL, AVAIL,    AVAIL,    AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, //1  Time - Limit
 AVAIL,    AVAIL,    AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, //2  Energy + Limit
 AVAIL,    AVAIL,    AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, //3  Energy - Limit
 AVAIL,    AVAIL,    NOTAVAIL, AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, //4  Power + Limit 
 AVAIL,    AVAIL,    NOTAVAIL, AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, //5  Power - Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //6  Collapse + Limit 
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //7  Collapse - Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, AVAILLE,  NOTAVAIL, //8  Absolute + Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, AVAILLE,  NOTAVAIL, //9  Absolute - Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //10 Trig. Dist + Limit
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //11 Trig. Dist - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //12 Max Force + S Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //13 Max Force - S Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //14 Freq. + Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, //15 Freq. - Limit
 NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL  //16	Max Force +/- R Limit
   },	   

// Reject Limits															  
//	Time     Energy   Pk. Pwr. Collaps    Absolute  Gr. Det.   Cont
//	Mode     Mode     Mode     Mode       Mode      Mode       Mode

   { // REJECT CONTROL LEVEL d (old level #4) 

 NOTAVAIL, AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL, //0  Time + Limit
 NOTAVAIL, AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL, //1  Time - Limit
 AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //2  Energy + Limit
 AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //3  Energy - Limit
 AVAIL,    AVAIL,    NOTAVAIL, AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //4  Power + Limit 
 AVAIL,    AVAIL,    NOTAVAIL, AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //5  Power - Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //6  Collapse + Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //7  Collapse - Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, AVAILLE , NOTAVAIL, //8  Absolute + Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, AVAILLE , NOTAVAIL, //9  Absolute - Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL, //10 Trig. Dist + Limit
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL, //11 Trig. Dist - Limit
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL, //12 Max Force + Limit
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL, //13 Max Force - Limit
 AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL, //14 Freq. + Limit
 AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL, //15 Freq. - Limit
 ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF   , ACTDF     //16	Max Force +/- R Limit
   },


// Reject Limits
//	Time     Energy   Pk. Pwr. Collaps    Absolute  Gr. Det.   Cont
//	Mode     Mode     Mode     Mode       Mode      Mode       Mode

   { // REJECT CONTROL LEVEL f (old level #5(EP))

 NOTAVAIL, AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL ,   NOTAVAIL, //0  Time + Limit
 NOTAVAIL, AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL ,   NOTAVAIL, //1  Time - Limit
 AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //2  Energy + Limit
 AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //3  Energy - Limit
 AVAIL,    AVAIL,    NOTAVAIL, AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //4  Power + Limit 
 AVAIL,    AVAIL,    NOTAVAIL, AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //5  Power - Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //6  Collapse + Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL, //7  Collapse - Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, AVAILLE , NOTAVAIL, //8  Absolute + Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, AVAILLE , NOTAVAIL, //9  Absolute - Limit 
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL, //10 Trig. Dist + Limit
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL, //11 Trig. Dist - Limit
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL, //12 Max Force + S Limit
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL, //13 Max Force - S Limit
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE , NOTAVAIL, //14 Freq. + Limit
 AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE , NOTAVAIL, //15 Freq. - Limit
 ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF   , ACTDF     //16	Max Force +/- R Limit

   }																   
};




const UINT16 parameterControlLevel[][MAXLEVELS] = {
//  t          e           ea          d           f    

 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //0   ALWAYS,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //1   PWELDMODE,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //2   PHOLDTIME,

// only one is picked from mode list        
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //3   PWELDTIME,
 NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      //4   PENERGY,
 NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      //5   PPEAKPOWER,
 NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    //6   PABSDIST,
 NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    //7   PCOLDIST,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //8   PSCRUBTIME,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   //9   PFREQUENCYCOUNT,

// end of mode list
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //10  PAFTERBURST,

// next entry either amplitude or amplitude stepping
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //11  PAMPLITUDEA,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      //12  PAMPLITUDESTEP,

// end

 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //13  PAFTERBURSTDELAY,
 NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      //14  PAMPLITUDEA1,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //15  PAFTERBURSTTIME,
 NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      //16  PAMPLITUDEB,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //17  PAFTERBURSTAMP,

// pick only one step
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      //18  PSTEPTRIGGERTIME,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      //19  PSTEPTRIGGERENERGY,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      //20  PSTEPTRIGGERPKPOWER,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    //21  PSTEPTRIGGERDISTANCE,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //22  PSTEPTRIGGERFORCE,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      //23  PSTEPTRIGGEREXTSIGNAL,
// end

 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //24  PPOSTWELDSEEK,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //25  PPRETRIGGER,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //26  PFREQUENCYOFFSET,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //27  PAUTOPRETRIGGER,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //28  PTESTAMPLITUDE,
 NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    //29  PPRETRIGGERDISTANCE,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      //30  PRAPIDTRAVS,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //31  PPRETRIGGERAMP,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   //32  PRTDISTANCE,
 NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    //33  PACTCLEAROUTPUT,
 NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    //34  PACTCLEARDISTANCE,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //35  PCYCLEABORTS,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //36  PGROUNDDETECTCUTOFF,
 NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    //37  PMISSINGPARTFLAG,
 NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    //38  PMISSINGPARTMAX,
 NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    //39  PMISSINGPARTMIN,
 NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      //40  PCONTROLLIMITS,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    //41  PCOLLAPSECUTOFF,
 NOTAVAIL,   AVAIL ,     AVAIL,      AVAIL,      AVAIL,      //42  PENERGYCOMP,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    //43  PABSOLUTECUTOFF,
 NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      //44  PENERGYMAX,
 NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      //45  PPKPOWERCUTOFF,
 NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      //46  PENGERGYMIN,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //47  PMAXTIMEOUT,

//aef actuator group
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAILLE,    //48  PTRIGGERFORCE,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //49  PDOWNSPEED,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //50  PTRIGGERDELAY,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //51  PGAUGEPSI,

// next entry either amplitude or amplitude stepping
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //52  PWELDFORCEA,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //53  PFORCESTEP,
// end

 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    //54  PCALINFO,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //55  PWELDFORCEA1,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    //56  PCALDATE,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //57  PWELDFORCEB,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //58  DRAWLINEFIELD,

// pick only one step
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //59  PFSTEPTRIGGERTIME,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //60  PFSTEPTRIGGERENERGY,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //61  PFSTEPTRIGGERPEAKPOER,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //62  PFSTEPTRIGGERDISTANCE,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //63  PFSTEPTRIGGERAMPLITUDE,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //64  PFSTEPTRIGGEREXTSIGNAL,
// end
// end of aef

// ae are all writeinfields
 NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      //65  PSUSPECTLIMITS,
 NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      //66  PREJECTLIMITS,
 NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      //67  PSUSPRESETREQ,
 NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      //68  PREJRESETREQ,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //69  PLANGUAGE,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //70  PTRIGGERBEEPER,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //71  PUNITS
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //72  PERRORBEEPER,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //73  PPASSWORD,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //74  PALARMBEEPER,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //75  PFEATURES,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //76  PWELDSCALE,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //77  PADVCOUNTER,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //78  PTESTSCALE,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //79  PHANDHELDSYSTEM,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //80  PDIGFILTER,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //81  PAMPCONTROL,		 
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //82  PFREQCONTROL,		 
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   //83  PSEQUENCING,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //84  PCUSTOMACT,

// display one entry
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //85  PSERIALPORT,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //86  PREMOTETERMINAL,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      //87  PHOSTCOMMANDS,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //88  PULSLOGIC,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //89  PBAUDRATE,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   //90  PTRSLOGIC,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   //91  PSWHANDSHAKE,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   //92  PMPSLOGIC,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //93  PECHO,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //94  PGENALARMRESET,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //95  PPSSUPPLY,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //96  PACTUATOR,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //97  PCONTROLLEVEL,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //98  PCYLDIAMETER,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //99  PFREQUENCY,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //100 PCYLSTROKE,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //101 PSWVERSION,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //102 PPSLIFETIME,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //103 PPSSERNUM,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //104 PPRESETCOUNTER,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //105 PSWSERNUM,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   //106 PACTLIFETIME,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      //107 PACTSERNUM,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //108 POVERLCOUNTER,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //109 PGENALARMCNTR,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //110 PPRINTERING,
                                                             // use for print on sample and print on alarm
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //111 PWELDDATA,
 NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      //112 PPOWERGRAPH,
 NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      //113 PAMPLITUDEGRAPH,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      //114 PFREQUENCYGRAPH,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    //115 PDISTANCEGRAPH,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    //116 PVELOCITYGRAPH,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAILLE,    //117 PFORCEGRAPH,
 NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      //118 PWELDHISTORY,
 AVAIL,   	 AVAIL,      AVAIL,      AVAIL,      AVAIL,      //119 PSETUP,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //120 PPRINTERS,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   //121 PFORMFEED,
 NOTAVAIL,   TMODONLY,   TMODONLY,   TMODONLY,   TMODONLY,   //122 PAUTOXSCALE,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //123 PPAGESIZE,
 NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      //124 PXSCALE,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //125 PLINESPERPAGE,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   //126 NEVERPRINT,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   //127 PCONTINUOUS,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    //128 PHOLDFORCE,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //129 STARTSCREEN,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //130 DIGITALTUNE,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //131 PEXTTRIGDLY,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //132 PDUPSRAMPTIME,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //133 PMEMORY,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //134 PWELDSTATUS,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //135 PSELECTNAME,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //136 PSEEKTIME,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //137 PTIMEDSEEK,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //138 PEXTRACOOLING,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //139 PUSERIO,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //140 PENERGYBRAKING,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //141 PRELEASEBEEPER,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //142 PEXTPRESETS,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //143 PWRITEINFIELD,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //144 PWELDTIMEMIN,
 NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      //145 PENERGYMIN,
 NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      //146 PPEAKPOWERMIN,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      //147 PWELDCOLLAPSEMIN,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      //148 PTOTALCOLLAPSEMIN,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      //149 PTOTALABSOLUTEMIN,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      //150 PWELDFORCEMIN,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //151 PTOTALCYCLETIMEMIN,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //152 PWELDTIMEMAX,
 NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      //153 PENERGYMAXIMUM,
 NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      //154 PPEAKPOWERMAX,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      //155 PWELDCOLLAPSEMAX,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      //156 PTOTALCOLLAPSEMAX, 
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      //157 PTOTALABSOLUTEMAX,
 NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      //158 PWELDFORCEMAX,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //159 PTOTALCYCLETIMEMAX,
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //160 PSCRUBAMPLITUDE
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      //161 PAMPUNITS
 AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL       //162 PPOWERUNITS
};
  
  

enum LIMITPARAM {
/*0 */    LTIMEPLUS,
/*1 */    LTIMEMINUS,
/*2 */    LENERGYPLUS,
/*3 */    LENERGYMINUS,
/*4 */    LPOWERPLUS,
/*5 */    LPOWERMINUS,
/*6 */    LCOLLAPSEPLUS,
/*7 */    LCOLLAPSEMINUS,
/*8 */    LABSOLUTEPLUS,
/*9 */    LABSOLUTEMINUS,
/*10*/    LTRIGGERDISTPLUS,
/*11*/    LTRIGGERDISTMINUS,
/*12*/    LMAXFORCEPLUS,          // + S Max Force Limit
/*13*/    LMAXFORCEMINUS,         // + S Max Force Limit
/*14*/    LFREQPLUS,                 
/*15*/    LFREQMINUS,
/*16*/    LRMAXFORCE,             // +/- R Max Force Limit 
};



enum PARAMNUM{
/*0 */  ALWAYS,
/*1 */  PWELDMODE,
/*2 */  PHOLDTIME,
/*3 */  PWELDTIME,
/*4 */  PENERGY, 
/*5 */  PPEAKPOWER,  
/*6 */  PABSDIST,  
/*7 */  PCOLDIST,  
/*8 */  PSCRUBTIME,  
/*9 */  PFREQUENCYCOUNT, 
/*10*/  PAFTERBURST, 
/*11*/  PAMPLITUDEA,
/*12*/  PAMPLITUDESTEP,
/*13*/  PAFTERBURSTDELAY,  
/*14*/  PAMPLITUDEA1,  
/*15*/  PAFTERBURSTTIME,  
/*16*/  PAMPLITUDEB,  
/*17*/  PAFTERBURSTAMP,  
/*18*/  PSTEPTRIGGERTIME,  
/*19*/  PSTEPTRIGGERENERGY,  
/*20*/  PSTEPTRIGGERPKPOWER, 
/*21*/  PSTEPTRIGGERDISTANCE,
/*22*/  PSTEPTRIGGERFORCE,  
/*23*/  PSTEPTRIGGEREXTSIGNAL,  
/*24*/  PPOSTWELDSEEK,  
/*25*/  PPRETRIGGER,
/*26*/  PFREQUENCYOFFSET, 
/*27*/  PAUTOPRETRIGGER,  
/*28*/  PTESTAMPLITUDE,  
/*29*/  PPRETRIGGERDISTANCE,
/*30*/  PRAPIDTRAVS,  
/*31*/  PPRETRIGGERAMP,  
/*32*/  PRTDISTANCE,  
/*33*/  PACTCLEAROUTPUT,  
/*34*/  PACTCLEARDISTANCE,  
/*35*/  PCYCLEABORTS,  
/*36*/  PGROUNDDETECTCUTOFF,
/*37*/  PMISSINGPARTFLAG,	 
/*38*/  PMISSINGPARTMAX,  
/*39*/  PMISSINGPARTMIN,  
/*40*/  PCONTROLLIMITS, 
/*41*/  PCOLLAPSECUTOFF,  
/*42*/  PENERGYCOMP,  
/*43*/  PABSOLUTECUTOFF,  
/*44*/  PENERGYMAX,	 
/*45*/  PPKPOWERCUTOFF,  
/*46*/  PENGERGYMIN,  
/*47*/  PMAXTIMEOUT,  
/*48*/  PTRIGGERFORCE,
/*49*/  PDOWNSPEED,  
/*50*/  PTRIGGERDELAY,
/*51*/  PGAUGEPSI,  
/*52*/  PWELDFORCEA,  
/*53*/  PFORCESTEP,
/*54*/  PCALINFO,
/*55*/  PWELDFORCEA1,             
/*56*/  PCALDATE,	 
/*57*/  PWELDFORCEB,         
/*58*/  DRAWLINEFIELD,        
/*59*/  PFSTEPTRIGGERTIME,      
/*60*/  PFSTEPTRIGGERENERGY,    
/*61*/  PFSTEPTRIGGERPEAKPOER,	 
/*62*/  PFSTEPTRIGGERDISTANCE,  
/*63*/  PFSTEPTRIGGERAMPLITUDE, 
/*64*/  PFSTEPTRIGGEREXTSIGNAL, 
/*65*/  PSUSPECTLIMITS, 
/*66*/  PREJECTLIMITS,  
/*67*/  PSUSPRESETREQ, 
/*68*/  PREJRESETREQ,	 
/*69*/  PLANGUAGE,      
/*70*/  PTRIGGERBEEPER,
/*71*/  PUNITS,        
/*72*/  PERRORBEEPER,  
/*73*/  PPASSWORD,     
/*74*/  PALARMBEEPER,  
/*75*/  PFEATURES,      
/*76*/  PWELDSCALE,     
/*77*/  PADVCOUNTER,    
/*78*/  PTESTSCALE,     
/*79*/  PHANDHELDSYSTEM,
/*80*/  PDIGFILTER,	    
/*81*/  PAMPCONTROL,		   
/*82*/  PFREQCONTROL,		  
/*83*/  PSEQUENCING,     
/*84*/  PCUSTOMACT,       
/*85*/  PSERIALPORT,	   
/*86*/  PREMOTETERMINAL,
/*87*/  PHOSTCOMMANDS,  
/*88*/  PULSLOGIC,  
/*89*/  PBAUDRATE,  
/*90*/  PTRSLOGIC,  
/*91*/  PSWHANDSHAKE,  
/*92*/  PMPSLOGIC,     
/*93*/  PECHO,         
/*94*/  PGENALARMRESET,
/*95*/  PPSSUPPLY,     
/*96*/  PACTUATOR, 
/*97*/  PCONTROLLEVEL,	 
/*98*/  PCYLDIAMETER, 
/*99*/  PFREQUENCY,
/*100*/ PCYLSTROKE,	 
/*101*/ PSWVERSION,
/*102*/ PPSLIFETIME, 
/*103*/ PPSSERNUM,
/*104*/ PPRESETCOUNTER,	 
/*105*/ PSWSERNUM,
/*106*/ PACTLIFETIME,	 
/*107*/ PACTSERNUM,  
/*108*/ POVERLCOUNTER,  
/*109*/ PGENALARMCNTR, 
/*110*/ PPRINTERING,    
/*111*/ PWELDDATA,      
/*112*/ PPOWERGRAPH,    
/*113*/ PAMPLITUDEGRAPH,
/*114*/ PFREQUENCYGRAPH,
/*115*/ PDISTANCEGRAPH, 
/*116*/ PVELOCITYGRAPH, 
/*117*/ PFORCEGRAPH,  
/*118*/ PWELDHISTORY, 
/*119*/ PSETUP,  
/*120*/ PPRINTERS,  
/*121*/ PFORMFEED,  
/*122*/ PAUTOXSCALE,  
/*123*/ PPAGESIZE,  
/*124*/ PXSCALE,  
/*125*/ PLINESPERPAGE,  
/*126*/ NEVERPRINT,
/*127*/ PCONTINUOUS,
/*128*/ PHOLDFORCE,
/*129*/ STRTSCREEN,
/*130*/ DIGITALTUNE,
/*131*/ PEXTTRIGDLY,
/*132*/ PDUPSRAMPTIME,
/*133*/ PMEMORY,
/*134*/ PWELDSTATUS,
/*135*/ PSELECTNAME,
/*136*/ PSEEKTIME,
/*137*/ PTIMEDSEEK,
/*138*/ PEXTRACOOLING,
/*139*/ PUSERIO,
/*140*/ PENERGYBRAKING,
/*141*/ PRELEASEBEEPER,
/*142*/ PEXTPRESETS,
/*143*/ PWRITEINFIELD,
/*144*/ PWELDTIMEMIN,
/*145*/ PENERGYMIN,
/*146*/ PPEAKPOWERMIN,
/*147*/ PWELDCOLLAPSEMIN,
/*148*/ PTOTALCOLLAPSEMIN,
/*149*/ PTOTALABSOLUTEMIN,
/*150*/ PWELDFORCEMIN,
/*151*/ PTOTALCYCLETIMEMIN,
/*152*/ PWELDTIMEMAX,
/*153*/ PENERGYMAXIMUM,
/*154*/ PPEAKPOWERMAX,
/*155*/ PWELDCOLLAPSEMAX,
/*156*/ PTOTALCOLLAPSEMAX,
/*157*/ PTOTALABSOLUTEMAX,
/*158*/ PWELDFORCEMAX,
/*159*/ PTOTALCYCLETIMEMAX,
/*160*/ PSCRUBAMPLITUDE,
/*161*/PAMPUNITS,
/*162*/PPOWERUNITS
};

/* Parameter */
#define   PRESETSETUPLOAD1(a)    if(CheckIfPrintable(a)) {strncpy(PresetSetup1[SetupCt1++],   buffer, SIZEOFBUF); }
#define   PRESETSETUPLOAD2(a)    if(CheckIfPrintable(a)) {strncpy(PresetSetup2[SetupCt2++],   buffer, SIZEOFBUF); }

/* Limits */
#define   REJLIMPRESETSETUPLOAD1(a)    SusRejFlag = REJACTIVE; if(ControlLevelLimit(a)) {strncpy(PresetSetup1[SetupCt1++],   buffer, SIZEOFBUF); }
#define   SUSLIMPRESETSETUPLOAD2(a)    SusRejFlag = SUSACTIVE; if(ControlLevelLimit(a)) {strncpy(PresetSetup2[SetupCt2++],   buffer, SIZEOFBUF); }

#endif /* _LIMARRAY_H */



 
   
   
   
   
   
     
   
   
   
   
   
   
   
   
   
   
   
     
   
     
   
   
     
     
   
   
   
     
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   




















      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      

