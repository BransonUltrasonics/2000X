/* $Header:   D:/SWLab/VMdb/2000Series/App/graphs.c_v   1.33   10 Sep 2009 15:59:30   bkymer  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 2003, 2009           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
/*
---------------------------- MODULE DESCRIPTION -------------------------------

     Module name:

        Filename: graphs.c

      Written by:  
            Date: 04/28/2003 
        Language: "C"

--------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
  ==========      ========       ======      ===========
      1.0          04/28/03       JOY        Initial Version
      1.5          06/23/03       JOY        Moved Language strings to "menutext.c".
                                             Added HornScan Graph Screen.    
                                             Alternative X-axis labels are removed.
                                             Back Button is added to the HornScan Graph.
      1.6          07/22/03       JOY        'PrevHornState' is set to 'REFRESH_SCAN_STATUS'-
                                             when 'Prev' button is pressed in Horn Scan graph screen,
                                             which is used to update Horn scan Screen bottom part
                                             with scan status.
      1.8          09/04/03       JOY        Added Dual Graph && Print Button.
      1.9          09/19/03       JOY        Tick Mark Labels moved to the Top.
      1.10         09/27/03       JOY        X-label(last) truncation is solved.
      1.11         10/05/03       AT         Middle Seg of graph Screen is refreshed by rom image
                                             -to fast up the display.
      1.12         10/06/03       JOY        Code review/Checking.
      1.13         10/16/03       JOY        Speed up graph Drawing.
      1.14         10/23/03       JOY        Added Button Release Beep.
      1.15         10/29/03       JOY        Made sure that label 'H' is displayed.
      1.16         12-08-03       BEKymer    Add arguments to function calls that
                                              now need them because of the menu
                                              cleanup change.
      1.17         07-02-04       JOY        Horizontal LABEL of graphs started from "0.00"
                                             in case of Handheld actuators.
      1.18         07-29-04       JOY        Print button is not displayed on particular graph, 
                                              if system Ctrl_Level is less than one required to print.
      1.19         07-25-05       Bwadia     QVGA clean up and graph implementation for SBC
                                             for Ver10.0e
      1.20         09-10-05       Bwadia     Added Resonant frequencies and Digital tune
                                             values in horn scan graph object
      1.21         09-16-05       Bwadia     Weld history data support for 1017 host command                                         
                                             in 'ProcessWeldGraphCommand' function
      1.22         10-24-05       Bwadia     PMC feature related functions added 
      1.23         12-07-05       Bwadia     Tick values to be shown on print graph added
                                             in VGAGRAPH object. Also added are the indicators
                                             to display manual notes at the end of the print
                                             graph. Modified for tracker issue 4031, 4009, 4024
	  1.24         02-07-06       Bwadia     Added guage pressure for AEF/AED actuator 
	                                         in VGAGRAPH object. Modified for tracker issue
	                                         4066 
      1.25         02-14-06       Bwadia     Added manual scale note in VGAGRAPH object. 
                                             Modified for tracker 4024
      1.26         03-12-07       NHAhmed    Modified code to allow Add To Average only once 
                                             for a particular weld cycle.
      1.27         05-23-07       NHAhmed    Redefined MAX_TICK_MARKS to 7.
      1.28         06-06-08       NHAhmed    Added new functions SendGraphData(), ProcessWeldGraphValue(),
                                             DrawHSGraph() and SendPMCValue().
      1.29         08-01-08       NHAhmed    Modified functions SendGraphData() & ProcessWeldGraphValue().
      1.30         09-02-08       NHAhmed    CleanUp for multi-language support.
      1.31         09-04-08       YGupta     CleanUp for LangTest Project.
      1.32         09-09-08       NHAhmed    CleanUp for multi-language support.
      1.33         09-10-09       BEkymer    Add new define MICRO where needed
      
      
*/

/*
 ------------------------------- DESCRIPTION ---------------------------------
*/


/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include <string.h>
#include "dups_api.h"
#include "menu.h"
#include "menu4.h"
#include "preset.h"
#include "util.h"
#include "portable.h"
#include "graphs.h"
#include "DRAWSCRN.h"
#include "Qvgamenu.h"
#include "battram.h"
#include "param.h"
#include "weld_obj.h"

#include "beep.h"
/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
#define LABELVAL 12
#define METRICRESOLUTION  10000
#define ENGRESOLUTION  1000
#define STARTBOTTOMGRAPH "-0.1"
#define LONGWELDTIME  20000
#define LONGSTARTGRAPH "0.00"
#define MINUSSTR  "-"
#define HS_GRAPH_HEIGHT 136
#define MAX_TICK_MARKS  7 

/*
 --------------------------LOCAL DATA------------------------------------------
*/
UINT16 DisplayRefreshButton = TRUE;
SINT32 ActualValuePMC1;
SINT32 ActualValuePMC2;
BOOLEAN IsGraphDrawing = FALSE;
BOOLEAN VGAHistoryData = FALSE;
BOOLEAN PMCPlusBandFlag;
BOOLEAN PMCMinusBandFlag;
UINT16  QVGATickmarks[MAX_TICK_MARKS];
UINT16  VGATickInfo[MAX_TICK_MARKS];
UINT32 QVGAUIVmaxlabel;
UINT32 QVGAUIVminlabel;
UINT32 VGAUIVmaxlabel;
UINT32 VGAUIVminlabel;
static SINT16 GraphColor;
static UINT8 GraphCount;                                  
static UINT16  VGAGraphCurrentlySelected;
SINT32 StoreCycleCount;
const STR *const Str_TickLabel[] = { "T", "A", "F", "W", "H", " ", "G"};
                                   
/*
 -------------------------EXTERNAL DATA----------------------------------------
*/

extern WELD_DATA WeldingResults;
extern BUTTON_STATE TouchedButtonState;
extern UINT16  WeldDataCount;
extern WELD_OBJECT *MsPointer;
extern WELD_DATA *PrintFinalPtr;
extern SINT32 val1[];
extern SINT32 val2[];
extern BOOLEAN IsGraphDataAvail;
extern REDRAW_SEG RedrawSeg;
extern SINT32 DigPotValue;
extern CONFIGSETUP CurrentSetup;
extern UINT16 SendPowerGraph;
extern UINT16 SendFrequencyGraph;
extern UINT16 SendAmplitudeGraph;
extern UINT16 SendForceGraph;
extern UINT16 SendVelocityGraph;
extern UINT16 SendColDistGraph;
extern UINT16 SendWeldData;
extern UINT16 SendHSGraph;
extern UINT16 TotalCycle;
extern BOOLEAN AllParamColumnFlag;
extern UINT16 ResonanceFreqEnable[];

extern UINT8 VGAAckBuf[];
/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/

static void GraphVLabel(UINT16 CWhichGraph, UINT32 UIMaxlabel,
                        UINT32 UIMinlabel, UINT16 INum, SINT8 CMess[] );
static void GraphHLabel(UINT32 UIHmaxlabel, SINT8 Hlabel[]); 
WELD_DATA * GetLastWeldResultPtr(void);
void SetDisplayRefreshButton(void);
UINT16 VGASendGraphData(UINT8 * * Response, EDIT_PARAM_TYPE ParamID);
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);
UINT16 AddToBufferString(UINT8 * * to, SINT8 * string, UINT16 length);
void ProcessWeldGraphCommand (UINT8 WeldGraphDataReq, UINT8 WeldCount);
UINT16 LangStrLen(SINT8 * str); 
BOOLEAN LangCheckNull(SINT8 * Line);
void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void StrCatTwoBytes(SINT8 * to, SINT8 * from);
void AddToPMCData(void);
UINT16 SendPMCData(UINT8 * AckBuf);

UINT16 DrawHSGraph(UINT8 * * Response, UINT16 GraphID);
UINT16 WeldParams(UINT8  * *Response, UINT16 WeldCount, BOOLEAN ParamFlag);
/*
 ---------------------------------- CODE -------------------------------------
*/

/**--------------------------------------------------------------**
 ** While drawing of the graph the vertical labels have to       **
 ** be printed in every 5th line. This function calculates the   **
 ** value of the actual label and prints it.                     **
 ** IN: Maxlabel, Minlabel, index of the actual label            **
 ** OUT:                                                         **
 **--------------------------------------------------------------**/
static void GraphVLabel(UINT16 CWhichGraph, UINT32 UIMaxlabel,
      UINT32 UIMinlabel, UINT16 INum, SINT8 CMess[] ){
   
   UINT32 UIValue;

   UIValue = (( 4 - INum) * ( UIMaxlabel - UIMinlabel))
             / 4 + UIMinlabel;

   switch(CWhichGraph)
   {
      case DISTINGRAPH:
      case ABSINGRAPH:
      case ABSMMGRAPH:
      case DISTMMGRAPH:
         /* If collapse, absolute distance, label is float */
         SPrintf(CMess,"%5.3f", (float)UIValue/10000.0);
         break;

      case VELINGRAPH:
      case VELMMGRAPH:
         SPrintf(CMess,"%5.2f", (float)UIValue/10000.0);
         break;

      case POWGRAPH:
    	 if(CurrentSetup.PeakPowerWattsFlag == TRUE)
     	 {
     		 SPrintf(CMess,"%5u", UIValue);
     	 }
     	 else
     	 {
     		 SPrintf(CMess,"%5.1f", (float)UIValue/10.0);
     	 }
         break;
         
      case AMPLIGRAPH:
   	 	 SPrintf(CMess,"%5u", UIValue/10);
         break;
         
      default:
         SPrintf(CMess,"%5u", UIValue);
         break;
   }
   
}

                                 
/**----------------------------------------------------**
 ** The horizontal labels are calculated, written in a **
 ** buffer line and printed.                           **
 ** IN: maximum horizontal label.                      **
 ** OUT:                                               **
 **----------------------------------------------------**/
static void GraphHLabel(UINT32 UIHmaxlabel, SINT8 Hlabel[])              
{
   float  FValue = 0.0, FIncValue = 0.0;
   SINT8 CVal[10], Minus[1];
   SINT8 ComboVal[LABELVAL];
   UINT16 i;
   SINT32 tempInt;
   SINT32 tempval;
   SINT32 count;
    
   /*-- Calculate x-axis scale --*/
   FIncValue = (UIHmaxlabel) / VALUEDIV;  /*-- 10000 points per 10 seconds --*/

   tempInt =  (UIHmaxlabel/INCLABEL);
   FValue  = 0.0;
   
   for(count = 0; count <= INCLABEL; count++)
   {
      if(count == 0)
      {
         if (CurrentSetup.HandHeld == TRUE) {
            strcpy(CVal, LONGSTARTGRAPH);
            FValue  = 0.000;
            tempval = 0;
         }
         else {
            if(UIHmaxlabel < LONGWELDTIME)
            {
               strcpy(CVal, STARTBOTTOMGRAPH);
            }
            else
            {
               strcpy(CVal, LONGSTARTGRAPH);
            }

            FValue  = STARTLABEL;
            tempval = LABELINT;
         }
      }
      else
      {
         FValue  += (FLOAT)0.00001;
         FValue  += FIncValue;
         tempval += tempInt;

         if(tempval  < 0)
         {
            strcpy(Minus, MINUSSTR);
            SPrintf(CVal, "%3.2f", FValue);
            strcpy(ComboVal, Minus);
            strncat(ComboVal, CVal, strlen(CVal));
            strcpy(CVal, ComboVal);
         }
         else
         {  
            SPrintf(CVal, "%3.2f", FValue);
         }
      }
      strcpy (&Hlabel[count*7], CVal);
            
   } /* end of for */
  
}/*-- void PrintGraphHLabel(UINT32 UIWeldtime)--*/


WELD_DATA * GetLastWeldResultPtr(void)
/****************************************************************************/
/*Description:-                                                             */
/* Returns Last Weld Data pointer                                           */
/****************************************************************************/
{
   SINT32 Addr;
   UINT8  *BatHistoryPtr;
   WELD_DATA * LastWeldResultPtr;
   
   BatHistoryPtr = (UINT8 *)(BBR800_HISTORY_START);
   Addr = (SINT32)BatHistoryPtr;   

   /*-- Get the last Weld Data position --*/
   if(CurrentSetup.WeldHistoryPtr != Addr)
      LastWeldResultPtr = (WELD_DATA *)(CurrentSetup.WeldHistoryPtr - (sizeof(WELD_DATA)));
   else
      LastWeldResultPtr = (WELD_DATA *)(Addr + ((HISTORYDATA-1) * sizeof(WELD_DATA)));

   PrintFinalPtr = LastWeldResultPtr;
   return(LastWeldResultPtr);   
}


void SetDisplayRefreshButton(void)
/***************************************************************************/
/*Sets flag that shall not display Refresh button if Auto refresh selected */
/***************************************************************************/
{
   DisplayRefreshButton = ~CurrentSetup.AutoRefresh;   
}


UINT16 SendGraphData(UINT8 * * Response, UINT16 GraphID)
/****************************************************************************/
/*Description:-                                                             */
/* Sends Graph Object                                                       */
/* Response - Buffer to which data is written                               */                                                      
/* Returns Length of the buffer                                             */
/****************************************************************************/
{
   WELD_DATA *LastWeldPtr; 
   SINT8 HlabelBuffer[100];   
   SINT8 TempStr[QVGA_LINESIZE];
   SINT16 Index;
   UINT16 Index1 = 0;
   UINT16 SampleCount;
   UINT16 length = 0;
   UINT16 GraphColor = 0;
   SINT8 Str_Vlabel[QVGA_LINESIZE];  
   

   if (GraphID == VGAPOWERGRAPH)
   {
      VGAGraphCurrentlySelected = POWGRAPH;
      GraphColor=COLOR_BLUE;
   }
   else if (GraphID == VGAFREQUENCYGRAPH)
   {
      VGAGraphCurrentlySelected = FREQUGRAPH;
      GraphColor=COLOR_BLACK;
   }
   else if (GraphID == VGAAMPLITUDEGRAPH)
   {
      VGAGraphCurrentlySelected = AMPLIGRAPH;
      GraphColor=COLOR_BROWN;
   }
   else if (GraphID == VGAFORCEGRAPH)   
   {
      VGAGraphCurrentlySelected = CurrentSetup.Units ? FORCENGRAPH : FORCELBGRAPH;
      GraphColor=COLOR_RED;
   }
   else if (GraphID == VGAVELOCITYGRAPH) 
   {
      VGAGraphCurrentlySelected = CurrentSetup.Units ? VELMMGRAPH : VELINGRAPH;  
       GraphColor=COLOR_MAGENTA;
   }
   else if(GraphID == VGACOLDISTGRAPH) 
   {
      VGAGraphCurrentlySelected = CurrentSetup.Units ? DISTMMGRAPH : DISTINGRAPH;
      GraphColor=COLOR_GREEN;
   }
   else;
   
   /*Get Last Weld Data pointer*/
   LastWeldPtr = GetLastWeldResultPtr();
   
   if((MsPointer->TotalPts !=0) && (MsPointer->DontPrintGraph == FALSE))
   {

     /*Test*/
      length += AddToBuffer(Response, (UINT8)(VGAGraphCurrentlySelected>>8));			           
      length += AddToBuffer(Response, (UINT8)VGAGraphCurrentlySelected);			           

     /*Get Graph Data*/
      length += AddToBuffer(Response, (UINT8)(GraphColor));
      SetupVals( VGAGraphCurrentlySelected, val2 );   
   
      GetMaxMinLabel(VGAGraphCurrentlySelected, val2, WeldDataCount,
                        &VGAUIVmaxlabel, &VGAUIVminlabel);

      /*Calibrate the Graph data*/
      RecalibVal( val2, VGAGraphCurrentlySelected, VGAUIVmaxlabel,
                  VGAUIVminlabel);   
      
      /*Send Graph Data*/
      IsGraphDrawing = TRUE;          
      if(WeldDataCount < MAX_WELD_SAMPLES)
         SampleCount = WeldDataCount;
      else
         SampleCount = MAX_WELD_SAMPLES;
      length += AddToBuffer(Response, (UINT8)(SampleCount>>8));			           
      length += AddToBuffer(Response, (UINT8)SampleCount);			           
         
      for (Index = 0; Index < SampleCount; Index++ ) {
         if(val2[Index] < 0) 
            val2[Index] = 0;
         else if(val2[Index] > 160)
            val2[Index] = 160;
         length += AddToBuffer(Response, (UINT8)val2[Index]);			           
      }
      IsGraphDrawing = FALSE;          
   
      /*Send Vertical Labels*/
                        
      for (Index = 3; Index >= 0; Index--) {
         GraphVLabel(VGAGraphCurrentlySelected, VGAUIVmaxlabel,
                     VGAUIVminlabel, Index, Str_Vlabel); 
         StrCpyTwoBytes(TempStr, Str_Vlabel);                                   
         length += AddToBuffer(Response, LangStrLen(TempStr));            
         length += AddToBufferString(Response, TempStr, LangStrLen(TempStr));
      }
   
      UIHmaxlabel = UIWeldtime;
      QVGAPrepTickMarks();

      /*Send Horizontal Labels*/
      GraphHLabel(UIHmaxlabel, HlabelBuffer); 
      for (Index = 0; Index <= INCLABEL; Index++) {
         StrCpyTwoBytes(TempStr, &HlabelBuffer[Index*7]);
         length += AddToBuffer(Response, LangStrLen(TempStr));            
         length += AddToBufferString(Response, TempStr, LangStrLen(TempStr));
      }    

      /* insert the tickmarks of FinalResults in Graph */
      for(Index = 0; Index < MAX_TICK_MARKS; Index++) {
         if(QVGATickmarks[Index] != 0) /*Check for valid Tick Mark*/
            Index1++;
      }   
	  length += AddToBuffer(Response, (UINT8)Index1);			           
	  
      for(Index = 0; Index < MAX_TICK_MARKS; Index++) {
         if(QVGATickmarks[Index] != 0) /*Check for valid Tick Mark*/
         {
            length += AddToBufferString(Response, Str_TickLabel[Index], 1);
            length += AddToBuffer(Response, (UINT8)(QVGATickmarks[Index]>>8));			           
            length += AddToBuffer(Response, (UINT8)QVGATickmarks[Index]);			           
         }
      } /*End of for loop*/

      /* Send Tick info to be displayed on the bottom part of print graph*/
      for(Index = 0; Index < MAX_TICK_MARKS; Index++) {
         length += AddToBuffer(Response, (UINT8)(VGATickInfo[Index]>>8));			           
	     length += AddToBuffer(Response, (UINT8)VGATickInfo[Index]);			           
      } /*End of for loop*/

      if (GraphID == VGAAMPLITUDEGRAPH)
	  {
	    /*Send Info for special note to be printed for Amp graph*/
         if(CurrentSetup.ControlLevel >= LEVEL_ea)
            length += AddToBuffer(Response, 1);
         else   
            length += AddToBuffer(Response, 0);
	  }
      else if (GraphID == VGAFORCEGRAPH)   
	  {
	   /*Send Info for special note to be printed for Force graph*/
         if((CurrentSetup.ControlLevel == LEVEL_f || CurrentSetup.ControlLevel == LEVEL_TEST)
            && CurrentSetup.Actuator == AEF) 
            length += AddToBuffer(Response, 1);
         else   
            length += AddToBuffer(Response, 0);
	  }
	  else
	     length += AddToBuffer(Response, 0);

	  /*Manual scale*/
      if(((LastWeldPtr->Weldmode == TIMEMODE) &&
        (MsPointer->PrintBottomFlags & MANUALSCALEFLAG)) ||
        (LastWeldPtr->Weldmode != TIMEMODE))
	     length += AddToBuffer(Response, 1);
	  else
		 length += AddToBuffer(Response, 0);

      /*Cycle count text*/   
      SPrintf(TempStr, "%d", LastWeldPtr->CycleCount);
      length += AddToBuffer(Response, LangStrLen(TempStr));            
      length += AddToBufferString(Response, TempStr, LangStrLen(TempStr));

      /*Guage pressure*/
      if ( ( (CurrentSetup.Actuator == AED) ||
             (CurrentSetup.Actuator == AEF) ||
             (CurrentSetup.Actuator == MICRO) ) &&
          (CurrentSetup.ControlLevel >= LEVEL_d)){   
         FormatVariables(LastWeldPtr->WeldPressure, PRESSURE, 
                         TempStr, 6, CurrentSetup.Units );
         TempStr[6] = 0;
            
         length += AddToBuffer(Response, LangStrLen(TempStr));            
         length += AddToBufferString(Response, TempStr, LangStrLen(TempStr));
  
      }
	  else
	    length += AddToBuffer(Response, 0);            
           
   }
   else 
   {
      VGAGraphCurrentlySelected = NO_VALID_GRAPH;
      length += AddToBuffer(Response, (UINT8)(VGAGraphCurrentlySelected>>8));			           
      length += AddToBuffer(Response, (UINT8)VGAGraphCurrentlySelected);			           
   }
   return length;
}

UINT16 ProcessWeldGraphValue (UINT8 WeldGraphDataReq, UINT8 WeldCount)
/***************************************************************************/
/*Processes Request for weld and graph data to be sent                     */ 
/*WeldGraphDataReq - Byte that decides what graphs are to be sent as well  */
/*                   as well as weld data to be sent                       */
/*WeldCount - Number of Weld cycle data to be sent                         */
/***************************************************************************/
{
   UINT8 index;
   UINT8 j= 1;
   UINT16 length = 0;
   UINT8 * PointertoAckBuf;

   PointertoAckBuf = (VGAAckBuf+8);
   VGAHistoryData = FALSE;  // History dat for last 25 weld cycles
   for (index = 0; index < 8; index++)
   {
      switch (index)
      {
         case 0:
         if (WeldGraphDataReq & j)  // Weld Data to be sent
         {
            TotalCycle = WeldCount & 0x7F;  // Nos of cycles requested for
            if (WeldCount & 0x80)
               VGAHistoryData = TRUE;  //History data for first 25 cycles to be sent
            AllParamColumnFlag = TRUE;
            length += WeldParams(&PointertoAckBuf,TotalCycle,AllParamColumnFlag);

         }   
         break;
         
         case 1:
         if (WeldGraphDataReq & j)  // Power graph data
            length += SendGraphData(&PointertoAckBuf,VGAPOWERGRAPH);
         break;
         
         case 2:
         if (WeldGraphDataReq & j)  // Frequency graph data 
            length += SendGraphData(&PointertoAckBuf,VGAFREQUENCYGRAPH);
         break;
         
         case 3:
         if (WeldGraphDataReq & j)  // Amplitude graph data
            length += SendGraphData(&PointertoAckBuf,VGAAMPLITUDEGRAPH);
         break;
         
         case 4:
         if (WeldGraphDataReq & j) // Force graph data
            length += SendGraphData(&PointertoAckBuf,VGAFORCEGRAPH);
         break;
         
         case 5:
         if (WeldGraphDataReq & j) // Velocity graph data
            length += SendGraphData(&PointertoAckBuf,VGAVELOCITYGRAPH);
         break;
         
         case 6:
         if (WeldGraphDataReq & j)  // Collapse graph data
            length += SendGraphData(&PointertoAckBuf,VGACOLDISTGRAPH);
         break;

         case 7:
         if (WeldGraphDataReq & j)  // HS graph data
            length += DrawHSGraph(&PointertoAckBuf,VGAHORNSCANGRAPH);
         break;
      } 
      j = j * 2;
   }
   return (length);
}



UINT16 DrawHSGraph(UINT8 * * Response, UINT16 GraphID)
/***************************************************************************/
/*Sends Horn Scan Graph Data to SBC                                        */ 
/***************************************************************************/
{
   SINT8 TempStr[QVGA_LINESIZE];
   SINT8 TempStr1 [QVGA_LINESIZE];
   UINT16 Index;
   UINT16 Count;
   SINT32 tempVal;   
   SINT32 tempMaxval;
   float  maxval;
   float  minval;
   float  scale;    /* scaling maximum value */
   UINT16 length = 0;
   UINT16 GraphColor=COLOR_BLUE;
   UINT8 NumHSFreqAvail = 0;
   
   
   if(HornScanInfo. ScanStatus == DUPS_SCANDATAAVAIL)
   {
      VGAGraphCurrentlySelected = PHASEGRAPH;
      length += AddToBuffer(Response, (UINT8)(VGAGraphCurrentlySelected>>8));			           
      length += AddToBuffer(Response, (UINT8)VGAGraphCurrentlySelected);			           
      /*Get Graph Data*/
      length += AddToBuffer(Response, (UINT8)(GraphColor));
      SetupVals( PHASEGRAPH, val1 );
      
      /*Find Max: Phase Value*/
      tempMaxval = (float)val1[0];
      for (Index = 0; Index < DUPS_HORNSCANPOINTS; Index++)
      {
         if( tempMaxval < val1[Index]) tempMaxval = val1[Index];
      }       
      maxval = (float)tempMaxval;
      /*Find Min: Phase Value*/
      minval = maxval;
      for (Index = 0; Index < DUPS_HORNSCANPOINTS; Index++)
      {
         if (val1[Index] < minval)
            minval = val1[Index];                                      
      }

      /* scale val for plot */
      if (minval > 0)                  /* all positive */
         scale = maxval;
      else if (maxval < 0)             /* all negative */
         scale = -minval;
      else                             /* on both sides of 0 */
      {
         scale = maxval;               /* real limit could be minval or maxval, */
         if (-minval > scale)          /* whichever's absolute value is larger */
            scale = -minval;
      }
      
      length += AddToBuffer(Response, (UINT8)(DUPS_HORNSCANPOINTS >> 8));            
      length += AddToBuffer(Response,(UINT8)DUPS_HORNSCANPOINTS);            
      for (Index = 0; Index < DUPS_HORNSCANPOINTS; Index++)
      {
         val1[Index] = HS_GRAPH_HEIGHT / 2 + (SINT32)((float)(val1[Index] * HS_GRAPH_HEIGHT / 2) / scale);
         if (val1[Index] > 136)
            val1[Index] = 136; 
         else if (val1[Index] < 0)
            val1[Index] = 0;
         length += AddToBuffer(Response, (UINT8)val1[Index]);            
      }   
      
      /*Draw the Horizontal Label 1*/
      SPrintf(TempStr, "%5d",HornScanInfo.StartFreq );
      StrCpyTwoBytes(TempStr1, TempStr);
      length += AddToBuffer(Response, LangStrLen(TempStr1));            
      length += AddToBufferString(Response, TempStr1, LangStrLen(TempStr1));
      /*Draw the Horizontal Label 2*/
      SPrintf(TempStr, "%5d",
           (HornScanInfo.StopFreq - HornScanInfo.StartFreq)/2 + HornScanInfo.StartFreq );
      StrCpyTwoBytes(TempStr1, TempStr);
      length += AddToBuffer(Response, LangStrLen(TempStr1));            
      length += AddToBufferString(Response, TempStr1, LangStrLen(TempStr1));
      /*Draw the Horizontal Label 3*/ 
      SPrintf(TempStr, "%5d",HornScanInfo.StopFreq);
      StrCpyTwoBytes(TempStr1, TempStr);
      length += AddToBuffer(Response, LangStrLen(TempStr1));            
      length += AddToBufferString(Response, TempStr1, LangStrLen(TempStr1));
      
      for (Index = 0; Index < DUPS_NUMRESONANCES; Index++)            
      {
         if (ResonanceFreqEnable[Index])
            NumHSFreqAvail++;
      }
      length += AddToBuffer(Response, NumHSFreqAvail);            
      for (Index = 0; Index < DUPS_NUMRESONANCES; Index++)            
      {
         if (ResonanceFreqEnable[Index])
         {
            length += AddToBuffer(Response, (UINT8)(HornScanInfo.ResonanceFreqs[Index] >> 24));            
            length += AddToBuffer(Response, (UINT8)(HornScanInfo.ResonanceFreqs[Index] >> 16));            
            length += AddToBuffer(Response, (UINT8)(HornScanInfo.ResonanceFreqs[Index] >> 8));            
            length += AddToBuffer(Response,(UINT8)HornScanInfo.ResonanceFreqs[Index]);            
            length += AddToBuffer(Response, (UINT8)HornScanInfo.ResonanceFreqType[Index]);
         }
      }
      length += AddToBuffer(Response, (UINT8)(DigPotValue >> 24));            
      length += AddToBuffer(Response, (UINT8)(DigPotValue >> 16));            
      length += AddToBuffer(Response, (UINT8)(DigPotValue >> 8));            
      length += AddToBuffer(Response,(UINT8)DigPotValue);            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Year >> 24));            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Year >> 16));            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Year >> 8));            
      length += AddToBuffer(Response,(UINT8)HornScanInfo.Year);            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Month >> 24));            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Month >> 16));            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Month >> 8));            
      length += AddToBuffer(Response,(UINT8)HornScanInfo.Month);            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Day >> 24));            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Day >> 16));            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Day >> 8));            
      length += AddToBuffer(Response,(UINT8)HornScanInfo.Day);            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Hour >> 24));            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Hour >> 16));            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Hour >> 8));            
      length += AddToBuffer(Response,(UINT8)HornScanInfo.Hour);            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Minute >> 24));            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Minute >> 16));            
      length += AddToBuffer(Response, (UINT8)(HornScanInfo.Minute >> 8));            
      length += AddToBuffer(Response,(UINT8)HornScanInfo.Minute);            

   }
   else
   {
      VGAGraphCurrentlySelected = NO_VALID_GRAPH;
      length += AddToBuffer(Response, (UINT8)(VGAGraphCurrentlySelected>>8));			           
      length += AddToBuffer(Response, (UINT8)VGAGraphCurrentlySelected);			           
   } 
   return length;
}


void AddToPMCData(void)
/****************************************************************************/
/*Description:-                                                             */
/* This function averages Power match curve data                            */
/****************************************************************************/
{
   UINT16 Index;
   UINT16 TempPMCVal;
   UINT16 SampleCount;
   UINT16 PrevMaxPowerVal;
   UINT16 CurrentMaxPowerVal;
   

   VGAGraphCurrentlySelected = POWGRAPH;
   
   if((MsPointer->TotalPts !=0)&&(StoreCycleCount != WeldingResults.CycleCount))
   {

      /*Get Graph Data*/
      SetupVals( VGAGraphCurrentlySelected, val2 );  
       
      GetMaxMinLabel(VGAGraphCurrentlySelected, val2, WeldDataCount,
                        &VGAUIVmaxlabel, &VGAUIVminlabel);

      /*Calibrate the Graph data*/
      RecalibVal( val2, VGAGraphCurrentlySelected, VGAUIVmaxlabel,
                  VGAUIVminlabel);   
      
      if(WeldDataCount < MAX_WELD_SAMPLES)
         SampleCount = WeldDataCount;
      else
         SampleCount = MAX_WELD_SAMPLES;


      if(CurrentPreset.PMCCycleCount)
         PrevMaxPowerVal = (UINT16)CurrentPreset.PMCData[PMCDATAPOINTS-2];
      else
         PrevMaxPowerVal = 0;
      CurrentMaxPowerVal = (UINT16)(VGAUIVmaxlabel/10);
      
      if (PrevMaxPowerVal > CurrentMaxPowerVal)
      {
         for (Index = 0; Index < SampleCount; Index++ ) {
            if(val2[Index] < 0) 
               val2[Index] = 0;
            val2[Index] = ((val2[Index] * CurrentMaxPowerVal) 
                            / PrevMaxPowerVal);   
         }
      }
      else if (PrevMaxPowerVal < CurrentMaxPowerVal)   
      {
         for (Index = 0; Index < PMCDATAPOINTS-2; Index++ ) {
            if(CurrentPreset.PMCData[Index] != 0xFF)   
               CurrentPreset.PMCData[Index] = ((CurrentPreset.PMCData[Index]
                                               * PrevMaxPowerVal) 
                                               / CurrentMaxPowerVal);   
         }
         CurrentPreset.PMCData[PMCDATAPOINTS-2] = (UINT8)CurrentMaxPowerVal;
      }
      
      for (Index = 0; Index < SampleCount; Index++ ) {
         if(val2[Index] < 0) 
            val2[Index] = 0;
         if(CurrentPreset.PMCData[Index] == 0xFF)   
            CurrentPreset.PMCData[Index] =  val2[Index];  
         else
         {
            TempPMCVal = val2[Index] + 
                         (CurrentPreset.PMCData[Index] * CurrentPreset.PMCCycleCount);
            CurrentPreset.PMCData[Index] = (UINT8)(TempPMCVal
                                             / (CurrentPreset.PMCCycleCount+1));
         }
      }
      CurrentPreset.PMCCycleCount++;
      StoreCycleCount = WeldingResults.CycleCount;
   }  
   else
      Beep(ERRORBEEP);
}

UINT16 SendPMCValue(UINT8 * AckBuf)
/****************************************************************************/
/*Description:-                                                             */
/* This function sends Power match curve data                               */
/*Input Parameters:-                                                        */
/* AckBuf:  Pointer to the buffer where data is to be written               */  
/*Output:-                                                                  */
/* Length of the bytes written to the buffer                                */
/****************************************************************************/
{
   UINT16 length = 0;
   UINT16 Index;
   UINT16  VGAGraphCurrentlySelected;
   if(CurrentPreset.PMCCycleCount !=0)
   {
      
      length += AddToBuffer(&AckBuf, (UINT8)(PMC_GRAPH >> 8));            
      length += AddToBuffer(&AckBuf,(UINT8)PMC_GRAPH);            
      length += AddToBuffer(&AckBuf,(UINT8)CurrentPreset.PMCEnabled);            
      length += AddToBuffer(&AckBuf, (UINT8)(CurrentPreset.PMCCycleCount >> 8));            
      length += AddToBuffer(&AckBuf,(UINT8)CurrentPreset.PMCCycleCount);            
      length += AddToBuffer(&AckBuf, (UINT8)(CurrentPreset.PMCTimeout >> 8));            
      length += AddToBuffer(&AckBuf,(UINT8)CurrentPreset.PMCTimeout);            
      if(!CurrentPreset.PMCMinusBandFlag)
         length += AddToBuffer(&AckBuf,(UINT8)CurrentPreset.PMCLowLimit);            
      else
         length += AddToBuffer(&AckBuf, 0);
      if(!CurrentPreset.PMCPlusBandFlag)
         length += AddToBuffer(&AckBuf,(UINT8)CurrentPreset.PMCHighLimit);            
      else
         length += AddToBuffer(&AckBuf, 0);
      if (CurrentPreset.PMCCycleCount)
      {
         for (Index = 0; Index < PMCDATAPOINTS; Index++){
            length += AddToBuffer(&AckBuf,(UINT8)CurrentPreset.PMCData[Index]);            
         }
      } 
   }
   else
   {
      VGAGraphCurrentlySelected = NO_VALID_GRAPH;
      length += AddToBuffer(&AckBuf, (UINT8)(VGAGraphCurrentlySelected>>8));			           
      length += AddToBuffer(&AckBuf, (UINT8)VGAGraphCurrentlySelected);
   }
   return (length);
}

void CheckPMCWithPwrGraph(void)
/****************************************************************************/
/*Description:-                                                             */
/* This function compares average power curve with current Power graph data */
/* and sets +R PMC and -R PMC band flags.                                   */
/****************************************************************************/
{
   UINT16 Index;
   SINT32 TempVal;
   UINT16 SampleCount;
   UINT16 PMCPlusLimitCount;
   UINT16 PMCMinusLimitCount;
   UINT16 TempHighLimit;
   UINT16 TempLowLimit;
   UINT16 TempPrevVal;

   VGAGraphCurrentlySelected = POWGRAPH;
   PMCPlusBandFlag = FALSE;
   PMCMinusBandFlag = FALSE;
   PMCPlusLimitCount = 0;
   PMCMinusLimitCount = 0;
   if((MsPointer->TotalPts !=0) && (CurrentPreset.PMCCycleCount !=0)
       && (CurrentPreset.PMCEnabled == TRUE)) 
   {

      /*Get Graph Data*/
      SetupVals( VGAGraphCurrentlySelected, val2 );   

      GetMaxMinLabel(VGAGraphCurrentlySelected, val2, WeldDataCount,
                        &VGAUIVmaxlabel, &VGAUIVminlabel);

      /*Calibrate the Graph data*/
      RecalibVal( val2, VGAGraphCurrentlySelected, VGAUIVmaxlabel,
                  VGAUIVminlabel);   
   
      
      TempHighLimit = (CurrentPreset.PMCHighLimit * 160) 
                       / (VGAUIVmaxlabel/10);
      TempLowLimit = (CurrentPreset.PMCLowLimit * 160) 
                       / (VGAUIVmaxlabel/10);
      
      if(WeldDataCount < MAX_WELD_SAMPLES)
         SampleCount = WeldDataCount;
      else
         SampleCount = MAX_WELD_SAMPLES;
         
      for (Index = 0; Index < SampleCount; Index++ ) {
         if(val2[Index] < 0) 
            val2[Index] = 0;
         
         if(CurrentPreset.PMCData[Index] != 0xFF) 
         {
            TempPrevVal = (UINT16)((CurrentPreset.PMCData[Index] 
                                   * CurrentPreset.PMCData[PMCDATAPOINTS-2]) 
                                   / (VGAUIVmaxlabel/10));
            if (val2[Index] > (SINT32)(TempPrevVal
                                + TempHighLimit)) // + R PMC band check
            {
               ActualValuePMC1 = val2[Index];
               ActualValuePMC1 = (ActualValuePMC1 / 160.0)* (VGAUIVmaxlabel/10);
      
               PMCPlusLimitCount++;
               if (PMCPlusLimitCount >= CurrentPreset.PMCTimeout) 
               {
                  PMCPlusBandFlag = TRUE;
                  break;
               }
            }
            else
               PMCPlusLimitCount = 0;

            TempVal = (SINT32)(TempPrevVal - TempLowLimit);
            if(TempVal < 0)
               TempVal = 0;

            if (val2[Index] < TempVal)  // -R PMC band check
            {
               ActualValuePMC2 = val2[Index];
               ActualValuePMC2 = (ActualValuePMC2 / 160.0)* (VGAUIVmaxlabel/10);
               PMCMinusLimitCount++;
               if (PMCMinusLimitCount >= CurrentPreset.PMCTimeout) 
               {
                  PMCMinusBandFlag = TRUE;
                  break;
               }
            }
            else
               PMCMinusLimitCount = 0;
         }  
      }
   }  

}
/***************************************END***********************************/
