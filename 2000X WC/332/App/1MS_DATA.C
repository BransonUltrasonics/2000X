/* $Header:   K:/APPS/PVCS Pro/332new/App/1MS_DATA.C_V   1.103   Sep 15 2003 03:08:18   BWadia  $ */
/******************************************************************************/ 
/*                                                                            */
/*                                                                            */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                   */
/*     This program is the property of Branson Ultrasonics Corporation        */
/*   Copying of this software is expressly forbidden, without the prior       */
/*   written consent of Branson Ultrasonics Corporation.                      */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/* ------------------------- MODULE DESCRIPTION ------------------------------*/
/*                                                                            */
/* Name: 1ms_data.c                                                           */     
/*                                                                            */     
/* ----------------------------- REVISIONS -------------------------------------------------------*/     
/*   Revision # Date        Author   Description                                                  */
/*   ---------- -------     ------   -----------                                                  */
/*    0         09-14-96    GR       Initial                                                      */
/*    1.01      09-30-96    PaulG    Modified test data                                           */
/*    1.02      10-15-96    PaulG    Added 4 mSObject templates                                   */
/*                                   And several 1ms data functions.                              */
/*    1.03      11-13-96    PaulG    Modified WELD_OBJECT struct.                                 */
/*    1.04      01-31-97    PaulG    Modified UIWeldtime.                                         */
/*    1.05      02-14-97    PaulG    Added code for welding in a mode                             */
/*                                   Other than time mode.                                        */
/*    1.04      02-21-97    PaulG    Modified collection of data.                                 */
/*    1.05      03-03-97    PaulG    Added header.                                                */
/*    1.06      03-06-97    PaulG    Removed DataTime and DataState.                              */
/*    1.07      03-11-97    PaulG    Removed test data.                                           */
/*    1.08      03-20-97    PaulG    Modified Data collection.                                    */
/*    1.09      03-21-97    PaulG    Included round error .                                       */
/*    1.10      03-27-97    PaulG    Replaced FinalResults with                                   */
/*                                   PrintFinalResult.                                            */
/*    1.11      04-04-97    PaulG    Recalibrated velocity graph                                  */
/*    1.12      04-08-97    PaulG    Updated metric printing                                      */
/*    2.00      04-10-97    LAM      Added weldtime2state                                         */
/*    2.01      04-16-97    PaulG    Added Auto Scale                                             */
/*    2.02      04-16-97    PaulG    Modified Auto Scale                                          */
/*    2.03      05-02-97    PaulG    Modified Distance graph.                                     */
/*    2.04      05-05-97    PaulG    Modified Expansion of Graph.                                 */
/*    2.05      05-09-97    PaulG    Modified Expansion data.                                     */
/*    2.06      05-13-97    PaulG    Modified auto scale data.                                    */
/*    2.07      05-15-97    PaulG    Changed  graph XScale.                                       */
/*    2.08      05-16-97    PaulG    Changed  graph XScale.                                       */
/*    2.09      05-27-97    LAM      Temporary put back                                           */
/*    3.00      05-28-97    LAM      Redid expanding points                                       */
/*    4.00      05-20-97    LAM      Chged datacount                                              */
/*    4.01      05-30-97    PaulG    Cast floats to int                                           */
/*    1.39      06-06-97    LAM      Made min xscale = 2.000                                      */
/*    1.40      06-27-97    PaulG    Modifiy Distance mm vs Inches                                */
/*    1.41      08-13-97    PaulG    Added pointer to 400 points data                             */
/*    1.42      08-23-97    PaulG    Cleanup data                                                 */
/*    1.43      08-29-97    PaulG    Modified Power Graph                                         */
/*    1.44      09-04-97    PaulG    Modified Frequency Graph                                     */
/*    1.45      09-05-97    PaulG    Added 100ms to TotalPts in mode                              */
/*                                   other than time.                                             */
/*    1.46      10-28-97    PaulG    Added  DataCollection flag to test                           */
/*                                   when 1ms data is totally collected                           */
/*    1.47      11-14-97    PaulG    Modified data collection less than 100ms                     */
/*    1.48      11-17-97    PaulG    Modified data colection                                      */
/*    1.49      11-18-97    LAM      chged printfinalresults to finalresults                      */
/*    1.50      12-02-97    PaulG    Moved CheckCollection to new location                        */
/*    1.51      12-04-97    PaulG    Changed TotalPts from UINT16 to UINT32                       */
/*    1.52      12-09-97    PaulG    Added new WeldDataCount, replaced DataCount                  */
/*    1.53      02-06-98    PaulG    Modified y-axis of the graph based on max value.             */
/*    1.54      02-13-98    PaulG    Modified Power graph based on max value.                     */
/*    1.55      03-24-98    PaulG    Replaced TotalPts with MsPointer->TotalPts.                  */
/*    1.56      03-27-98    PaulG    Added IncrementPts, CopyPts, NewPreCt                        */
/*    1.57      04-06-98    PaulG    Added BufferWrapFlag to WELD_OBJECT                          */
/*    1.58      04-24-98    PaulG    Modify distance graph points.                                */
/*    1.59      04-28-98    PaulG    Modify velocity graph points.                                */
/*    1.60      05-06-98    PaulG    Added Digital filtering for velocity graph.                  */
/*    1.61      05-15-98    PaulG    Added Digital filtering for Force graph.                     */
/*    1.62      05-18-98    PaulG    Modified Digital filtering for Force graph.                  */
/*    1.65      05-28-98    PaulG    Modified Digital filtering for Velocity graph.               */
/*    1.66      06-05-98    PaulG    Modified DISTANCE points after hold time.                    */
/*    1.67      06-12-98    PaulG    Modified VELOCITY points before trigger.                     */
/*    1.68      06-15-98    PaulG    Modified VELOCITY and FORCE points before trigger.           */
/*    1.69      06-25-98    PaulG    Modified FORCE algorithm.                                    */
/*    1.70      06-29-98    PaulG    Modified Velocity algorithm.                                 */
/*    1.71      06-30-98    PaulG    Modified Velocity algorithm, chop off data beyond holdtime.  */
/*    1.72      07-01-98    PaulG    Adjusted Velocity algorithm to reflect data up til hold.     */
/*    1.73      07-17-98    PaulG    Velocity graph will be digitally filtered automatically.     */
/*    1.74      07-20-98    PaulG    Digital filter for Velocity graph will be actvated only when */
/*                                   digital filtering is on.                                     */
/*    1.75      07-23-98    PaulG    Modified Amplitude graph to reflect cutoff at holdtime.      */
/*    1.76      07-24-98    PaulG    Modified Force graph to reflect higher resolution in digital filtering.*/
/*    1.77      07-30-98    PaulG    Added case for frequency 40k            */
/*    1.78      07-30-98    PaulG    General modification...                 */
/*    1.79      08-06-98    PaulG    Added PointsUpTillHold and EndOfSonicCt to WELD_OBJ struct*/
/*    1.80      08-07-98    PaulG    Power, amplitude will stop a weldtime. */
/*    1.81      08-17-98    PaulG    Added new function DigitalFilterForce  */
/*    1.82      08-27-98    PaulG    General cleanup - Initialize all local */
/*                                   variables to zero.                     */                                
/*    1.83      09-04-98    PaulG    Added extern variable GraphCurrentlySelected */
/*    1.84      09-10-98    PaulG    Modified graph printing to reflect points when hold in on or off. */
/*    1.85      09-23-98    PaulG    Rename DigitalFilterForce to DigitalFilterFunction. */
/*    1.86      09-25-98    PaulG    Modified DigitalFilterFunction() to handle large values. Replaced UINT16 with SINT32 */
/*    1.87      11-09-98    PaulG    Removed FREQGRAPH40 and FREQGRAPH20 and replace with FREQGRAPH.
/*    1.88      11-20-98    PaulG    Check if  points up till hold or end of sonics is greater than 0.
/*    1.89      11-20-98    PaulG    Before I get the points up till hold, I will check if hold id on or off.
/*    1.90      12-15-98    PaulG    Modified velocity algorithm for METRIC calculation.
/*    1.91      09-28-99    JZ       Fixed typecasting
/*    1.92      10-07-99    JLH      Eliminated negative collapse distances. */
/*    1.93      10-12-99    JLH      Eliminated conversion of 10ths of pounds to pounds in SetupVals.  This */
/*                                   was losing resolution needed for plotting.  Conversion is now done in  */
/*                                   RecalibVal, which converts data to pixels for plotting.                */
/*    1.95      04-14-00    JLH      Replaced Kalib function with PlotSort in preparation for Horn Scan plotting. */
/*    1.96      05-01-00    JLH      Changed calling sequences for SetupVals and RecalibVal.  Added */
/*                                    HORNSCANGRAPH case to SetupVals.  It presently returns force  */
/*                                    data for testing.                                             */
/*    1.97      05-01-00    JLH      Replaced case HORNSCANGRAPH with case PHASEGRAPH and case CURRENTGRAPH.  */
/*    1.98      06-13-00    JLH      Removed tabs. */
/*    1.99      06-14-00    JLH      Tried to remove tabs again. */
/*    1.100     06-15-00    LAM      removed tabs again. */
/*    1.101     06-21-00    DJL      made a few global changes from DigitalFilter to DigitalFilterFlag  */
/*    1.102     08-09-00    JLH      Changed horn scan PHASEGRAPH and CURRENTGRAPH to return actual data  */
/*                                     rather than force data.  */
/*    1.103     09-08-03    JOY      Added 'CurrentGraph', VmaxLabel, & VminLabel arguments */
/*                                   to the 'RecalibVal()'.*/
       
/*---------------------------- DESCRIPTION -----------------------------------*/

#include <psos.h>
#include "preset.h"
#include <math.h>
#include "weld_obj.h"
#include "state.h"
#include "util.h"
#include "graphs.h"
#include "menu4.h"
#include "dups_api.h"
#include "command.h"

//#define TEST_DATA 1
#define MAXSAMPLE   400



/*---------------------------- EXTERNAL INFO -------------------------------*/

extern enum WELDSTATES MsState;
extern SETUPS_Ver800    RunningPreset;
extern WELD_DATA FinalResults;
extern UINT16    CurrentSetupChgedFlag;
extern WELD_DATA *PrintFinalPtr;
extern UINT16    GraphCurrentlySelected;


/*---------------------------- GLOBAL DATA ---------------------------------*/

WELD_OBJECT *MsPointer;
SINT32  DistTime[MAX_WELD_SAMPLES];
SINT32  TempDistTime;
UINT16  WeldDataCount;
SINT32  val1[MAX_WELD_SAMPLES];
SINT32  val2[MAX_WELD_SAMPLES];
BOOLEAN CheckCollection = TRUE;    /* TRUE: data copied to val array */
UINT16  GreaterPt;
SINT32  ForceDigValue = DIGITALFORCEVALUE;

/**-------------------------------------------------------------------------**
 ** For the PC version the array val[MAX_WELD_SAMPLES] is filled with test  **
 ** values and are recalibrated, if not input units (in,lb) are to be used. **                                                  
 **-------------------------------------------------------------------------**/
void SetupVals( enum WHICHGRAPH GraphSelected, SINT32 *Data )
{
  UINT16  DiffCt = 0;         /*-- start point in circular buffer         --*/
  UINT16  InsertFakePt = 0;   /*-- insert fake point for peak power       --*/
  UINT16  count = 0;

  UINT16  TempCopyPts = 0;    /*-- All these Temp variable is simply for  --*/
  UINT16  TempNewPreCt = 0;   /*-- faster processing. Accessing MsPOinter --*/
  SINT32  TempActTrigDist = 0;/*-- in a for loop uses much more time.     --*/ 
  SINT32  TempConvertVal = 0;
  UINT16  TempPeakPower = 0;         
  DFLOAT  TempIncrementPts = 0;    /*-- number of point to skip collecting--*/
  BOOLEAN TempBufferWrap = 0;      /*-- did the 100ms buffer overflow?    --*/ 
  UINT16  TempPointsUpTillHold = 0;/*-- points up till holdtime           --*/             
  UINT16  TempEndOfSonicCt = 0;    /*-- points un till weldtime           --*/                 

  /*-- Temporary values initialized --*/
  TempCopyPts = MsPointer->CopyPts;
  TempNewPreCt = MsPointer->NewPreCt;
  TempIncrementPts = MsPointer->IncrementPts;
  TempActTrigDist = FinalResults.ActualTriggerDistance;
  TempPeakPower = FinalResults.PeakPower;
  TempBufferWrap = MsPointer->BufferWrapFlag;
  TempPointsUpTillHold = MsPointer->PointsUpTillHold;            
  TempEndOfSonicCt = MsPointer->EndOfSonicCt;                  

  /*-- If points before trigger is less than 100ms --*/
  /*-- then we need to pad difference with zeros   --*/

  DiffCt = TempCopyPts - TempNewPreCt;

  CheckCollection = FALSE;
  UIWeldtime = MsPointer->TotalPts;
  WeldDataCount = MsPointer->count;


  switch(GraphSelected)
  {


     case AMPLIGRAPH:          
  
                     /*-- AMPLITUDE IN PERCENTAGE  --*/

       if(CurrentSetup.AmpMicronsFlag==FALSE)
       {

    	 /*-- Reorder Circular Buffer --*/
    	 if(TempBufferWrap == TRUE){
    		 for(count = 0; count < TempCopyPts; count++){
    			 Data[count] = MsPointer->Amp[(count + TempNewPreCt) % TempCopyPts];
    		 }
    	 }
    	 else{
    		 /*-- pad with zeros --*/
    		 for(count = 0; count < DiffCt; count++){
    			 Data[count] = 0;
    		 }

    		 for(count = DiffCt; count < TempCopyPts; count++){
    			 Data[count] = MsPointer->Amp[count - DiffCt];
    		 }
    	 }

    	 for(count = TempCopyPts; count < WeldDataCount; count++){
    		 Data[count] = MsPointer->Amp[count];
    	 }

       }
       else //get micron graph
       {

    	 if(TempBufferWrap == TRUE){
    	 	 for(count = 0; count < TempCopyPts; count++){
    	 		 //Data[count] = MsPointer->Amp[(count + TempNewPreCt) % TempCopyPts];
    	 		 //Data[count] = ThreeRulePorcentageToMicrons(Data[count],CurrentSetup.AmpMicronsValue);

    	 		 TempConvertVal = MsPointer->Amp[(count + TempNewPreCt) % TempCopyPts];
    	 		 Data[count] = (SINT32)ThreeRulePorcentageToMicrons(TempConvertVal,CurrentSetup.AmpMicronsValue);
    	 	 }
    	 }
    	 else{
    	     for(count = 0; count < DiffCt; count++){
    	    	 Data[count] = 0;
    	     }

    	     for(count = DiffCt; count < TempCopyPts; count++){
    	    	 //Data[count] = 0;

    	    	 //Data[count] = MsPointer->Amp[count - DiffCt];
    	    	 //Data[count] = ThreeRulePorcentageToMicrons(Data[count],CurrentSetup.AmpMicronsValue);

    	    	 TempConvertVal = MsPointer->Amp[count - DiffCt];
    	    	 Data[count] = (SINT32)ThreeRulePorcentageToMicrons(TempConvertVal,CurrentSetup.AmpMicronsValue);
    	     }
    	 }

    	 //WeldDataCount = MAX_WELD_SAMPLES;
    	 for(count = TempCopyPts; count < WeldDataCount; count++){
    	 	 //Data[count] = MsPointer->Amp[count];
    	 	 //Data[count] = ThreeRulePorcentageToMicrons(Data[count],CurrentSetup.AmpMicronsValue);
    		 TempConvertVal = MsPointer->Amp[count];
    		 Data[count] = (SINT32)ThreeRulePorcentageToMicrons(TempConvertVal,CurrentSetup.AmpMicronsValue);

    	 }

       }

      break;

    case POWGRAPH:

                     /*-- POWER IN PERCENTAGE --*/
      

      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){ 
          Data[count] = MsPointer->Power[(count + TempNewPreCt) % TempCopyPts];
         }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           Data[count] = 0;
        }

        for(count = DiffCt; count < TempCopyPts; count++){ 
          Data[count] = MsPointer->Power[count - DiffCt];
         }
      }


      for(count = TempCopyPts; count < WeldDataCount; count++){
         Data[count] = MsPointer->Power[count];
      }


      /*-- Check and insert a point on the Peak Power graph      --*/
      /*-- This will assure  that the Peak Power value displayed --*/
      /*-- on the one line data will be in the graph. This is    --*/
      /*-- unorthodox, but I was forced by the powers that be.   --*/

      InsertFakePt = (UINT16)((MsPointer->PeakPowerAtTime + 100) /
                     TempIncrementPts);
      Data[InsertFakePt] = TempPeakPower;
      GreaterPt = TempPeakPower;

      /*-- Make sure no number is greater than the PeakPower --*/
      for(count = 0; count < WeldDataCount; count++){
        if(Data[count] > GreaterPt)
           Data[count] = GreaterPt;
      }

      break;




    case  FREQUGRAPH:

                     /*-- FREQUENCY IN HERTZ --*/
      
      
      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
          for(count = 0; count < TempCopyPts; count++){ 
           Data[count] = MsPointer->Freq[(count + TempNewPreCt) %
                        TempCopyPts];
         }
      }
      else{
         /*-- pad with zeros --*/
         for(count = 0; count < DiffCt; count++){
            Data[count] = 0;
         }

         for(count = DiffCt; count < TempCopyPts; count++){ 
            Data[count] = MsPointer->Freq[count - DiffCt];
          }
      }


       for(count = TempCopyPts; count < WeldDataCount; count++){
         Data[count] = MsPointer->Freq[count];
      }
      break;





    case DISTINGRAPH:

      
                  /*-- COLLAPSE DISTANCE IN INCHES --*/

      for(count = 0; count < TempCopyPts; count++){
        Data[count] = 0;
      }

      for(count = TempCopyPts; count < WeldDataCount; count++){
         Data[count] = (MsPointer->Dist[count] - TempActTrigDist);
         if(Data[count] < 0) Data[count] = 0;
      }

      break;



     case FORCELBGRAPH:

           
                     /*-- FORCE IN POUNDS --*/

      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){
           Data[count] = MsPointer->Force[(count + TempNewPreCt) % TempCopyPts];
        }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           Data[count] = 0;
        }
        for(count = DiffCt; count < TempCopyPts; count++){ 
          Data[count] = MsPointer->Force[count - DiffCt];
         }
      }

      for(count = TempCopyPts; count < WeldDataCount; count++){
         Data[count] = MsPointer->Force[count];
      }

      /* Change resolution if digital filtering is on */
      if(RunningPreset.DigitalFilterFlag == TRUE){
        DigitalFilterFunction(Data, ForceDigValue);
      }                                   
      break;




    case VELINGRAPH:    
      
                     /*-- VELOCITY IN INCHES PER SECOND --*/
      
      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){ 
          DistTime[count] = MsPointer->Dist[(count + TempNewPreCt) %
                            TempCopyPts];
         }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           DistTime[count] = 0;
        }

        for(count = DiffCt; count < TempCopyPts; count++){ 
          DistTime[count] = MsPointer->Dist[count - DiffCt];
         }
      }


      for(count = TempCopyPts; count < WeldDataCount; count++){
          DistTime[count] = MsPointer->Dist[count];
      }



      for(count = OFFSET3; count <  WeldDataCount; count++){
         TempDistTime = (DistTime[count] - DistTime[count - OFFSET3]);
         if(TempDistTime >= 0)
            Data[count] = ((TempDistTime * VALUEDIV) /
                                (OFFSET3 * RESOLUTION * TempIncrementPts));
         else
            Data[count] = 0;
      }

      Data[0] = Data[1] = Data[2] = Data[3];


      /* Change resolution if digital filtering is on */
      DigitalFilterFunction(Data, ForceDigValue);
      break;




    case DISTMMGRAPH:    
 
                     /*-- COLLAPSE DISTANCE IN MILLIMETERS --*/
      
      for(count = 0; count < TempCopyPts; count++){
        Data[count] = 0;
      }


      for(count = TempCopyPts; count < WeldDataCount; count++){
         Data[count] =((MsPointer->Dist[count] - TempActTrigDist) * 254) / 10;
         if(Data[count] < 0) Data[count] = 0;
      }
      break;



    case FORCENGRAPH:    
                     /*-- FORCE IN NEWTONS --*/
   
      
      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){
          TempConvertVal = MsPointer->Force[(count + TempNewPreCt) %
                           TempCopyPts];
           Data[count] = (SINT32)PoundToNewton(TempConvertVal);
        }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           Data[count] = 0;
        }

        for(count = DiffCt; count < TempCopyPts; count++){ 
          TempConvertVal = MsPointer->Force[(count - DiffCt)];
          Data[count] = (SINT32)PoundToNewton(TempConvertVal);
         }
      }


      for(count = TempCopyPts; count < WeldDataCount; count++){
         TempConvertVal = MsPointer->Force[count];
         Data[count] = (SINT32)PoundToNewton(TempConvertVal);
      }

      /* Change resolution if digital filtering is on */
      if(RunningPreset.DigitalFilterFlag == TRUE){
         DigitalFilterFunction(Data, ForceDigValue);
      }
      break;




    case VELMMGRAPH:    
                     /*-- VELOCITY IN MILLIMETERS PER SECOND --*/
      
      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){ 
          DistTime[count] = ((MsPointer->Dist[(count + TempNewPreCt) %
                              TempCopyPts] * CONV254) / INCLABEL);
         }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           DistTime[count] = 0;
        }

        for(count = DiffCt; count < TempCopyPts; count++){ 
          DistTime[count] = ((MsPointer->Dist[count - DiffCt] * CONV254) /
                              INCLABEL);
         }
      }


       for(count = TempCopyPts; count < WeldDataCount; count++){
          DistTime[count] = ((MsPointer->Dist[count] * CONV254) / INCLABEL);
       }


      for(count = OFFSET3; count <  WeldDataCount; count++){
         TempDistTime = (DistTime[count] - DistTime[count - OFFSET3]);
         if(TempDistTime >= 0)
            Data[count] = ((TempDistTime * VALUEDIV) /
                                (OFFSET3 * RESOLUTION * TempIncrementPts));
         else
            Data[count] = 0;
      }
      
      Data[0] = Data[1] = Data[2] = Data[3];
      
      /* Change resolution if digital filtering is on */
      DigitalFilterFunction(Data, ForceDigValue);
      break;



    case ABSINGRAPH:

                           /*-- ABSOLUTE DISTANCE IN INCHES --*/

      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){ 
          Data[count] = MsPointer->Dist[(count + TempNewPreCt) %
                            TempCopyPts];
         }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           Data[count] = 0;
        }

        for(count = DiffCt; count < TempCopyPts; count++){ 
          Data[count] = MsPointer->Dist[count - DiffCt];
         }
      }

      for(count = TempCopyPts; count < WeldDataCount; count++){
         if(MsPointer->Dist[count] > 0)  /* dist is 0 after holdtime */
           Data[count] = MsPointer->Dist[count];
         else
           Data[count] = 0;
      }


      for(count = 0; count < WeldDataCount; count++){
         Data[count] -= (TempActTrigDist - 500);
         if(Data[count] < 0)
            Data[count] = 0;
      }


      break;





    case ABSMMGRAPH:    
 
                     /*-- ABSOLUTE DISTANCE IN MILLIMETERS --*/
      
      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){ 
          Data[count] = ((MsPointer->Dist[(count + TempNewPreCt) %
                         TempCopyPts] * CONV254) / INCLABEL);
         }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           Data[count] = 0;
        }

        for(count = DiffCt; count < TempCopyPts; count++){ 
          Data[count] = ((MsPointer->Dist[count - DiffCt] * CONV254) /
                              INCLABEL);
         }
      }

      for(count = TempCopyPts; count < WeldDataCount; count++){
         if(MsPointer->Dist[count] > 0)  /* dist is 0 after holdtime */
           Data[count] =((MsPointer->Dist[count] * CONV254) /
                                  INCLABEL);
         else
           Data[count] = 0;

      }
      break;


     case PHASEGRAPH:
     
        for(count = 0; count < DUPS_HORNSCANPOINTS; count++)
           Data[count] = (UINT32)HornScanPhase[count];
        break;   


     case CURRENTGRAPH:
                                  
        for(count = 0; count < DUPS_HORNSCANPOINTS; count++)
           Data[count] = (UINT32)HornScanCurrent[count];
      break;


    default:
      break;


  }/* switch..*/


    /*-- If digital filtering is ON stop use points up til hold --*/
    /*-- otherwise, use total points collected --*/

    if((GraphSelected == AMPLIGRAPH)   ||
       (GraphSelected == POWGRAPH)     ||
       (GraphSelected == FREQUGRAPH)){
       if((RunningPreset.DigitalFilterFlag == TRUE) &&
          (TempEndOfSonicCt > 0)){
          WeldDataCount = TempEndOfSonicCt;
       }
    }
    else
    if((GraphSelected == FORCELBGRAPH) ||
       (GraphSelected == FORCENGRAPH) ||
       (GraphSelected == VELINGRAPH)  ||
       (GraphSelected == VELMMGRAPH)){

       if((RunningPreset.DigitalFilterFlag == TRUE) &&
          (TempPointsUpTillHold > 0)){
          if((RunningPreset.HoldTimeFlag & BIT0) == FALSE)
            WeldDataCount = TempPointsUpTillHold;  /*-- STOP AT HOLDTIME --*/
          else
            WeldDataCount = TempEndOfSonicCt;
       }
    }


    /*-- Data collected so now you are --*/
    /*-- free to start next cycle      --*/
    CheckCollection = TRUE;



}/* setup_vals(..*/




UINT16 PlotSort( SINT32 *Data, struct STRComp *DataOrder, UINT16 NumSamp )
/**-------------------------------------------------------------------------**
 ** The input array Data has random numbers. These numbers are to be sorted **
 ** by value. The input array is not changed, a new array DataOrder[] holds **
 ** the indices for the row of values. It is built as a double index array  **
 ** with reference to the next higher and the next lower value.             **
 ** OUTPUT: index to maximum value                                          **
 **-------------------------------------------------------------------------**/
{
   SINT32 IVal, IOrder, IOrder1, i;
   SINT8 CFlag;

   /* prep of data*/
   for(i = 0; i < NumSamp; i++)
      DataOrder[i].higher = DataOrder[i].lower = i;

    /* init of sort algorithm*/
   if(Data[0] > Data[1]){
       DataOrder[0].lower = 1;
       DataOrder[1].higher = 0;
   }
   else{
       DataOrder[0].higher = 1;
       DataOrder[1].lower = 0;
   }

    /* start of sort algorithm*/
    IOrder = 0;
    for(IVal = 2; IVal < NumSamp; IVal++)
    {
       CFlag = 0;
       if(Data[IVal] > Data[IOrder]) {
          do{
             if(IOrder == DataOrder[IOrder].higher){
                /* insert at top*/
                DataOrder[IOrder].higher = IVal;
                DataOrder[IVal].lower = IOrder;
                CFlag = 1;
                break;
             }
             IOrder = DataOrder[IOrder].higher;
          } while(Data[IVal] > Data[IOrder]);
       }/* if(Data[IVal] > Data[IOrder])*/
       else{
          do{
             if(IOrder == DataOrder[IOrder].lower){
                /* insert at bottom*/
                DataOrder[IOrder].lower = IVal;
                DataOrder[IVal].higher = IOrder;
                CFlag = 1;
                break;
             }
             IOrder = DataOrder[IOrder].lower;
          } while(Data[IVal] <= Data[IOrder]);
          IOrder = DataOrder[IOrder].higher;
       }
       if(!CFlag){
          /* insert between two values*/
          IOrder1 = DataOrder[IOrder].lower;
          DataOrder[IOrder].lower = IVal;
          DataOrder[IVal].higher = IOrder;
          DataOrder[IOrder1].higher = IVal;
          DataOrder[IVal].lower = IOrder1;
       }
    }

    /* search for maximum value*/
    IVal = 0;
    do{
        IVal = DataOrder[IVal].higher;
    } while(IVal != DataOrder[IVal].higher);

    return(IVal);    /* return index of maximum*/
}


/**-------------------------------------------------------------------------**
 ** The input array has to be recalibrated. 172 dots is the maximum vertical**
 ** dot value which is equal to the maximum vertical label value.           **
 ** IN: maximum label, minimum label                                        **
 **-------------------------------------------------------------------------**/
void RecalibVal( SINT32 *Data, UINT16 CurrentGraph, UINT32 VmaxLabel,
                 UINT32 VminLabel )
{
   SINT32 i, IVal, Scale = 1;

   if(CurrentGraph == FORCELBGRAPH) Scale = 10;
   //if(CurrentGraph == AMPLIGRAPH && CurrentSetup.AmpMicronsFlag==TRUE) Scale = 2;

   for (i = 0; i < MAX_WELD_SAMPLES; i++){
      /* calculate to 160 pixels equal to 20 lines at 8 dots*/

      IVal = 160L * (Data[i] - (SINT32)VminLabel*Scale);
      IVal /= Scale * (VmaxLabel - VminLabel);
      if(IVal <= 0) IVal = 1;
      Data[i] = IVal;
    }

} /* end of RecalibVal */



/**-------------------------------------------------------------------------**
 ** This is the digital filter routine. Its main function is to take an     **
 ** existing array of numbers and filter it. In doing so the new values are **
 ** stored in the same array. It can be called from any module in the code. **          
 ** INPUT : ForceDigValue, which is a global value that can be set from the **
 **         menu screen under the print option.                             **
 ** OUTPUT: This function returns no data.                                  **                                              **
 **-------------------------------------------------------------------------**/
void DigitalFilterFunction(SINT32 * Data, SINT32 ForceDigFilter)
{

   SINT32 ForcePivot = 0;   /*-- Average of values stored here             --*/
   SINT32 TempTotalVal = 0; /*-- Temporarily stores total of values added  --*/
   SINT32 TempForceValue= 0;/*-- The original ForceDigFilter is stored here--*/
   UINT16 count = 0;        /*-- Used for incrementing                     --*/


   /*-- If printing a VELOCITY graph filter points whether digital filtering --*/
   /*-- is ON or OFF. Otherwise, for any other graph check is digital filter --*/
   /*-- -ing is ON or OFF before filtering points. --*/

   if((RunningPreset.DigitalFilterFlag == TRUE) ||
      (GraphCurrentlySelected == VELINGRAPH)||
      (GraphCurrentlySelected == VELMMGRAPH)){
      
      /*-- initialize variables --*/
      TempForceValue = ForceDigFilter;
      TempTotalVal = 0;
      ForcePivot = ForceDigFilter/2; /*-- pivot is the mid point of ForceDigFilter--*/
      

      /*-- digitally filter array val contain at most 400 points --*/
      for(count = ForceDigFilter-1; count < WeldDataCount; count++){
      

         /*-- Calulate average of N points where N is ForceDigFilter --*/
         while(ForceDigFilter > 0){
           TempTotalVal += Data[count - (UINT16)(ForceDigFilter-1)];
           ForceDigFilter--;
         }
      

         /*-- Once Average is calculated store at pivot point --*/
         Data[ForcePivot++] = TempTotalVal / TempForceValue;
         TempTotalVal = 0;
         ForceDigFilter = TempForceValue;
      }
    }
}  



