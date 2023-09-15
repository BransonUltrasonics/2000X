/* $Header:   D:/SWLab/VMdb/2000Series/App/PR_LABEL.C_V   1.71   Oct 22 2007 19:05:22   YGupta  $ */
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

 Name: pr_label.c
   
 ----------------------------- REVISIONS ------------------------------------

   Revision #     Date        Author               Description
   ----------     -------     ------               -----------
    0             09/14/96    GR                   Initial
    1.00          01/22/97    PaulG                Removed line after graph prints.
    1.01          01/27/97    PaulG                Modify min/max label for velocity
                                                   changed 500/2000 to 125/500.
    1.02          02/14/97    PaulG                Changed Horizontal label printout.
    1.03          02/27/97    PaulG                Changed Vertical label for distance.
    1.04          03/07/97    PaulG                Changed Vertical label for velocity.
    1.05          03/11/97    PaulG                Changed Vertical label for distance.
    1.06          03/11/97    PaulG                Adjust function to accomodate metric.
    1.07          05/08/97    PaulG                Change FLOAT to DFLOAT for FValue.
    2.00          06/06/97    LAM                  Change yscales                    
    2.01          06/06/97    LAM                  Change y Dist scale                   
    2.1.11        06/06/97    PaulG                Change y Dist scale                   
    2.1.12        06/27/97    PaulG                Change y Vel and Dist scale                   
    2.1.13        08/08/97    PaulG                Added printer driver info.
    2.1.14        08/23/97    PaulG                Modify printer driver info.
    2.1.15        08/27/97    PaulG                Modify Auto scale for graphs.
    2.1.16        08/29/97    PaulG                Modify Auto scale for graphs.
    2.1.17        09/05/97    PaulG                Cleanup data.
    2.1.18        09/08/97    PaulG                Cleanup data.
    2.1.19        09/18/97    PaulG                Modified POWERGRAPH to POWGRAPH.
    2.1.20        11/07/97    PaulG                Added PrintCPIMode.
    2.1.21        11/11/97    PaulG                Cleanup data.
    2.1.22        11/17/97    PaulG                Changed from 10 cpi to 12 cpi.
    1.23          12/14/97    LAM                  Changed amp scale to 0.1% resolution
    1.24          12/18/97    LAM                  fixed min amp scale 
    1.25          02/06/98    LAM                  chged sethorizpos values to * 30
    1.26          02/18/98    LAM                  deleted setprintercalls          
    1.27          03/06/98    PaulG                Replace -0.100 with 0.000 based on weldtime.   
    1.28          03/16/98    PaulG                Converted tempval and tempInt from SINT16 to UINT32.
    1.29          03/17/98    PaulG                Replace 0.000 with -0.100 based on weldtime.   
    1.30          03/26/98    PaulG                Added 0.00001 to value for x-axis scale.
    1.31          04/21/98    PaulG                Modify vertical scales for velocity, distance, and frequency.
    1.32          04/28/98    PaulG                Modify calculation of velocity max point after trigger. 
    1.33          05/15/98    PaulG                Modify vertical scale for Force graph.
    1.34          05/18/98    PaulG                Added Abs Distance to table.
    1.35          05/29/98    PaulG                Modified points values for velocity.
    1.36          06/15/98    PaulG                Removed hard code numbers and replace with defines.
    1.37          06/25/98    PaulG                Modified velocity vertical label
    1.38          06/26/98    PaulG                Modified absolute distance values in table.
    1.39          06/30/98    PaulG                Modified velocity values based on vertical scale.
    1.40          07/01/98    PaulG                Removed MaxVelPoint from file.
    1.41          07/15/98    PaulG                Add min label to force in the table, new min is 40.
    1.42          07/22/98    PaulG                Modified distance graph vertical label from 3 decimal point to 4.
    1.43          07/24/98    PaulG                Added new defines POSTION10, POSTION16.
    1.44          07/29/98    PaulG                Separate frequency into 20k and 40k.
    1.45          09/04/98    PaulG                Modified printout of graph label.
    1.46          09/09/98    PaulG                Modified label at bottom of graph. Correct overwritting of memmory.
    1.47          10/14/98    PaulG                Modify velocity graph.
    1.48          10/14/98    PaulG                Modify velocity graph variable.
    1.49          10/15/98    PaulG                Cleanup hard coded values creating defines.
    1.50          10/20/98    PaulG                Modified Velocity graph before trigger, print real values
                                                   instead of fake line.
    1.51          11/09/98    PaulG                Combine frequency for 40k and 20k, also added 30k and 15k.
    1.52          11/20/98    PaulG                Cleanup code.
    1.53          11/20/98    PaulG                Removed TempBeforeTrigValue from code.
    1.54          11/20/98    PaulG                Removed 0.1000 in/s scale from velocity graph.
    1.54.4.1      08/28/99    JLH                  Updates for wider IBM Pro plots.
    1.56          10-11-99    JZ                   made GetMaxMinLabel() and PrintEscSequ() type void 
    1.57          10-11-99    JZ                   made INum in PrintGraphVLabel(), UINumber on GetMaxMinLabel() type UINT16
    1.58          10-12-99    JLH                  Deleted unused variable ActualGraphVel.  Changed GetMaxMinLabes() to
                                                    convert maximum force in 10ths of pounds to pounds before deciding on the
                                                    maximum and minimum labels to use.  Force is not converted to pounds until
                                                    the RecalibVal function (in 1ms_data.c).
    1.59          02-23-00    JLH                  Added HP and Epson ESC/P printer capability.
                                                   merged 7.f4CHp to trunk
    1.60          03-21-00    JLH                  Removed IBM proprinter option.
    1.61          05-01-00    JLH                  Changed val to val1.  Added extern for LangIndex.
    1.62          05-26-00    JLH                  Changed LASERJET printer type to HPPCL.
    1.63          06-13-00    JLH                  Removed tabs.
    1.64          06-14-00    SCM                  Removed unused variable 'LangIndex'.
    1.65          07-07-00    BEKymer/DJL         fixed SETUPS
    1.66          07-20-00    JLH                 Changed frequency vertical labels in response to tracker
	                                               issue 3335.  Changed limits for 15KHz, 30KHz, and 40KHz.  
    1.67          11-28-00    BEKymer             Added another scale to UILabels[LABELNUM][LABELSIZE]
    1.68          06-28-01    BEKymer             In PrintGraphHLabel handle scale when handheld is TRUE
    1.69          09-01-03    JOY                 Added graph points array pointer to the argument list of
                                                  -the 'GetMaxMinLabel()', since graph Data point array for printing
                                                  -and QVGA display are different.
    1.70          07-28-03    JOY                 Added Min/Max Label values for 60KHZ in UILabels[][].
    1.71          10-22-07    NHAhmed             Changes done for LangTest phase 0




 ---------------------------- DESCRIPTION -----------------------------------
*/

#include "string.h"
#include "preset.h"
#include "util.h"
#include "portable.h"
#include "graphs.h"
#include "command.h"

#define LABELVAL 12
#define METRICRESOLUTION  10000
#define ENGRESOLUTION  1000
#define STARTBOTTOMGRAPH "-0.100"
#define LONGWELDTIME  20000
#define LONGSTARTGRAPH "0.000"
#define MINUSSTR  "-"

/**-------------------------LOCAL DATA------------------------------------**/

UINT32 UIValue;
SINT32 tempval;
UINT32 UIMax = 0, UIMin = 0;
SINT8 CVal[10], Minus[1];
SINT8 ComboVal[LABELVAL];


/**-------------------------EXTERNAL DATA------------------------------------**/

extern SINT8  buffer[];
extern UINT16 PrintCPIMode;                   
extern UINT16 PrinterType;
extern WELD_OBJECT *MsPointer;
extern SETUPS_Ver800 RunningPreset;


/**--------------------------------------------------------------**
 ** Constant global array to hold information for the  vertical  **
 ** labels. The first array subscript is the  number of labels   **
 ** available. The following items are the maximum labels, then  ** 
 ** the minimum labels follow. This information is held for each **
 ** possible graph.                                              **
 **--------------------------------------------------------------**/


const UINT32 UILabels[LABELNUM][LABELSIZE] =
{

/*  number of labels, 1st label_high, 2nd label_high...label_low..*/
/*0  AMPLITUDE        */   { 9,    40,    100,    200,    400,    800,    1000,   1300, 1500, 2000, 0, 0, 0, 0,0},
/*1  POWER            */   { 6,   100,    200,    400,    800,   1000,    1200, 0, 0, 0,  0, 0, 0},   
/*2 FREQ 60/40/30/20/15k*/ { 5, 15375,  20450,  30750,  40900,   61500,   14625,   19450, 29250, 38900, 58500}, 
/*3  COLLAPSE  USCS   */   { 7,   100,    200,    600,   1200,   2400,    6000,   10000, 0, 0, 0, 0, 0, 0, 0},  
/*4  FORCE     Pound  */   { 7,    40,    100,    200,    400,    800,    1000,   1300, 0, 0, 0, 0, 0, 0,0},  
/*5  VELOCITY  USCS   */   { 2,  3000,   6000,      0,      0},                                                      
/*6  COLLAPSE  Metric */   { 7,  2500,   5000,  15000,  30000,  60000,  150000,  250000, 0, 0, 0, 0, 0, 0, 0},  
/*7  FORCE     Newton */   { 7,   200,    400,    800,   1600,   3200,    4400,  5500, 0, 0, 0, 0, 0, 0, 0},  
/*8  VELOCITY  Metric */   { 2,100000, 150000,      0,      0},
/*9  ABSOLUTE  USCS   */   { 7,  2500,   5000,   7500,  10000,  20000,   40000,   60000, 0, 0, 0, 0, 0, 0, 0},  
/*10 ABSOLUTE Metric  */   { 7, 60000, 130000, 190000, 250000, 500000, 1000000, 1500000, 0, 0, 0, 0, 0, 0, 0},
/*11 HORN SCAN (use force for debug) */ { 6,    40,    100,    200,    400,    800,    1000, 0, 0, 0, 0, 0, 0}  
};



/**--------------------------------------------------------**
 ** This function searches for the maximum and the minimum **
 ** label of the choosen graph.                            **
 ** IN: index of the choosen graph c_which_graph           **
 ** index of the maximum value of the input value array    **
 ** ui_number pointer to maximum and minimum label         **
 ** p_maxlabel,p_minlabel.                                 **
 ** OUT: maxlabel                                          **
 **--------------------------------------------------------**/
void   GetMaxMinLabel(UINT16 CWhichGraph,
                      SINT32 *Data,
                      UINT16 UINumber,
                      UINT32 *PMaxlabel,
                      UINT32 *PMinlabel)
{
   UINT32 UIMaxIndex, *PUIValue;
   SINT32 UIMaxval = 0;
   UINT16 count;

   /* find maximum value of data */
   for(count = 0; count < UINumber; count++)
	   if(Data[count] > UIMaxval) UIMaxval = Data[count];

   /* convert tenths of pounds to pounds for label selection */
   if(CWhichGraph == FORCELBGRAPH)
      UIMaxval = (UIMaxval + 5) / 10;

   /*-- find the appropriate vert. label --*/
   UIMaxIndex = UILabels[CWhichGraph][0];
   PUIValue = (UINT32 *)UILabels[CWhichGraph];

   for(count = 1; count <= UIMaxIndex; count++){
      UIMax = *(PUIValue + count);
      UIMin = *(PUIValue + UIMaxIndex + count);
      if( UIMaxval <= UIMax) break;
   }

   *PMaxlabel = UIMax;
   *PMinlabel = UIMin;

}

