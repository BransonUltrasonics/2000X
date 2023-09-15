/* $Header:   D:/SWLab/VMdb/2000Series/App/qvgarunresultoption.c_v   1.26   25 Sep 2009 15:07:20   ygupta  $ */
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

     Module name:

        Filename: qvgarunresultoption.c

      Written by:  
            Date:  
        Language: "C"

--------------------------------- REVISIONS ------------------------------------

   Revision #      Date     Author   Description
  ==========      ========  ======   ===========
     1.0          03/05/03  SCM      Initial Version.
     1.2          09/03/03  JOY      Initialized Weld Param: options with one 
                                     -stored in BBRAM.
     1.3          09/19/03  JOY      Set ForceA/B buttons are, displayed 
                                     -only if AEF act. is present.
     1.4          10/03/03  JOY      In AEF actuator velocity option is removed, in
                                     'InitWeldParamOption()'       
     1.5          10/06/03  JOY      Weld Result options are Initialized.
     1.6          10/13/03  JOY      RVELOCTY param, is added in param list,
                                     -if velocity reporting is enabled.
     1.7          10/24/03  JOY      Added popup confirm Screen, while chaniging
                                     -column which is already selected. 
     1.8          12-09-03  BEKymer  Add argument member to SUBMENU & TEXT
                                      structures as needed.  Add argument
                                      to functions called from SUBMENU
                                      and TEXT structures.
     1.9          02-20-04  VSharma  Added RADIOMENU 'PresetNumDisplay' in WeldResultSetupMenu.
                                     Added RPRESETNUM to Weld Result Screen.

     1.11         04-06-04  VSharma  Replace number 22 with define MAXSCROLLMENUS.
     1.12         05-07-04  LAM      merged with 8.22
     1.13         06-15-04  Bekymer  Changed RVELOCITY to either RVELOCITY_AED or
                                      RVELOCITY_AEF as appropiate.
     1.14         07-25-05  Bwadia   VGA weld results column support added.
                                     Asian Language support for th eweld results column
                                     VGA exit and save button added
     1.15         11-02-05  Aare     Added code to display total cycle time on VGA.
     1.16         11-22-05  Bwadia   InitWeldParamOption() modified for total
                                     cycle time parameter check at power up
     1.17         01-20-06  Bwadia   Weld Results setup string changed to Column Setup
                                     Modified for tracker issue 4059 
     1.18        10-22-07   NHAhmed  Changes done for LangTest phase 0
     1.19        01-11-08   NHAhmed  Some functions are replicated to a none argument type, 
                                     keeping all functionality same.
     1.20        04-14-08   NHAhmed  Renamed some functions.
     1.21        08-01-08   NHAhmed  Renamed function GetSelectedResultParam1() as GetSelectedDisplayParam().
     1.22        09-02-08   NHAhmed  CleanUp for multi-language support.
     1.23        09-04-08   YGupta   CleanUp for LangTest Project.
     1.24        09-09-08   NHAhmed  CleanUp for multi-language support.
     1.25        10-01-08   NHAhmed  Merged Ver10.40 changes.
	  1.26        09-25-09   YGupta   Added new define MICRO where needed.

*/

/*
 -------------------------------- DESCRIPTION --------------------------------
*/                         





/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include <string.h>
#include "menu.h"
#include "param.h"
#include "portable.h"
#include "preset.h"
#include "beep.h"
#include "DrawScrn.h"
#include "menu1.h"
#include "battram.h"
#include "qvgamenu.h" 
#include "graphs.h"
#include "command.h"

/*------------------------------- LOCAL DEFINES ----------------------------*/
#define INDEX_START     2
#define MAX_DISPLAYED_PARAM  5 

/*------------------------------- GLOBAL DATA ------------------------------*/
/*                       (scope is global to ALL files)                     */
enum WeldParamColoum  { NOT_DISPLAY = BIT0,    /*Display position on RunResultScreen.*/
                            COLUMN1 =BIT1,
                            COLUMN2 =BIT2,
                            COLUMN3 =BIT3,
                            COLUMN4 =BIT4
                            };

UINT16 StoreSelectedItem;
SINT8 QVGAWeldParamStr[QVGA_LINESIZE];
/*InitializeRunResultParameters*/               
//UINT16 ResultDisplayPos[MAXSCROLLMENUS];
UINT16 ResultDisplayPos[RMAXPARAMETERS];
	/* 0---*/
	/* 1---*/
	/* 2 -Display postion of Time        */
	/* 3 -Display postion of PeakPwr     */
	/* 4 -Display postion of Energy      */
	/* 5 -Display postion of Velocity Aed*/
	/* 6 -Display postion of Velocity Aef*/
	/* 7 -Display postion of Weld Abs    */
	/* 8 -Display postion of Total Abs   */
	/* 9 -Display postion of Weld Col    */
	/* 10-Display postion of Total Col   */
	/* 11-Display postion of Set Amp A   */
	/* 12-Display postion of Set Amp B   */
	/* 13-Display postion of Set Force A */
	/* 14-Display postion of Set Force B */
	/* 15-Display postion of Weld Force  */
	/* 16-Display postion of Act Press   */
	/* 17-Display postion of Freq Min    */
	/* 18-Display postion of Freq Max    */
	/* 19-Display postion of Freq Start  */
	/* 20-Display postion of Freq End    */
	/* 21-Display postion of Freq Chg    */
    /* 22-Display postion of PresetNum   */	      

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

UINT16 SelectedDisplayItem = 0;/*Stores the value of currently selected    */
                             /*RADIOMENU item.*/

UINT16 IsDisplay;  /*VPtr of all RADIO items, Store current display */
                          /*position of selected item.                     */
UINT16 IsDisplay1;

UINT32 RadioPointer = 0;
/*

 ----------------------------- EXTERNAL FUNCTIONS ----------------------------
*/
BOOLEAN IsSWConfigured(UINT32 SWType);

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern UINT16 RadioIndex;
extern UINT16 GlobalCommandID;

extern BUCMENU_800 *BUCMenuBBR;
extern CONFIGSETUP CurrentSetup;
extern CONFIRM_SCREEN_TYPE ConfirmType;

extern UINT32 NackError, ErrorResponseMinLimit, ErrorResponseMaxLimit;
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

MENUEND endWeldResultSetup = {TRUE};/*Local Type variables*/

/*
 --------------------------- GLOBAL FUNCTION PROTOTYPES -------------------------
*/

extern void GetUnit_Value(SINT8 StrUnit_Value[], UINT16 Param, UINT8 Flag);
UINT16 LangStrLen(SINT8 * str); 
BOOLEAN LangCheckNull(SINT8 * Line);
void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void StrCatTwoBytes(SINT8 * to, SINT8 * from);

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/

BOOLEAN CheckForEmptyColumn(UINT16 SelectedItem);

void SaveWeldParamState(void);
void ChangeDisplayColumn (void);
void GetSelectedDisplayParam(UINT16 TempGlobalCommandID);

/*
 ---------------------------------- CODE -------------------------------------
*/


//Change in GetCurrentscreenType() and make currentscreen=MENU_SCREEN for  WeldResultsSumbmenu.

/*==========================================================================*/
/*     RADIO STRUCTURE FOR RADIO SCREEN TO SELECT DISPLAY POSITION          */
/*==========================================================================*/



/*==========================================================================*/
/*          FUNCTIONS TO PROCESS WELD RESULT SETUP SCREEN                   */
/*==========================================================================*/


void SaveWeldParamState(void)
/***************************************************************************/
/*Description:                                                             */
/*   This function will be called by the radio structure if the value is   */
/*   changed successfully and user exited the screen by pressing Save      */
/*   button.It stores the currently selected position of parameter in      */
/*   respective array.                                                     */
/***************************************************************************/
{
    UINT16 index, SelectedItem;
    CONFIGSETUP *BBRPtr;
      
    BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
    
    switch (RadioIndex)
    {
       case 0:
          IsDisplay1 = RADIO_0;
          SelectedItem = 0;         
       break;
       case 1:
          IsDisplay1 = RADIO_1;
          SelectedItem = 1;         
       break;
       case 2:
          IsDisplay1 = RADIO_2;
          SelectedItem = 2;         
       break;
       case 3:
          IsDisplay1 = RADIO_3;
          SelectedItem = 3;         
       break;
       case 4:
          IsDisplay1 = RADIO_4;
          SelectedItem = 4;         
       break;
    }
    if(!((SelectedItem) &&   ( CurrentSetup.WeldParamOption[SelectedItem] != 0 ))) 
    {
       GetSelectedDisplayParam(GlobalCommandID);
       ResultDisplayPos[SelectedDisplayItem] = IsDisplay1;   
       for(index=1;index < MAX_DISPLAYED_PARAM; index++)
          CurrentSetup.WeldParamOption[index]=0;
       
       for(index=INDEX_START; index < RMAXPARAMETERS; index++)
       {
           if(ResultDisplayPos[index] == COLUMN1)
              CurrentSetup.WeldParamOption[1]= index;
           else if(ResultDisplayPos[index] == COLUMN2)
              CurrentSetup.WeldParamOption[2]= index;
           else if(ResultDisplayPos[index] == COLUMN3)
              CurrentSetup.WeldParamOption[3]= index;
           else if(ResultDisplayPos[index] == COLUMN4)
              CurrentSetup.WeldParamOption[4]= index;   
       }
      /*Update all the current setup and BUCMenu variables */
      BBRPtr->WeldParamOption[1] = CurrentSetup.WeldParamOption[1];
      BBRPtr->WeldParamOption[2] = CurrentSetup.WeldParamOption[2];
      BBRPtr->WeldParamOption[3] = CurrentSetup.WeldParamOption[3];
      BBRPtr->WeldParamOption[4] = CurrentSetup.WeldParamOption[4];
    }
    else
    {
       GetSelectedDisplayParam(GlobalCommandID);
       NackError = WELDER_PROCESS_ERROR;
       ErrorResponseMinLimit = COLSETUP_MSG_SCREEN;
       ErrorResponseMaxLimit = 0;    
    }
}

void GetSelectedDisplayParam(UINT16 TempGlobalCommandID)
/***************************************************************************/
/*Description:                                                             */
/*   When user selects any of the RADIOMENU paramenter in WeldResultSetup  */
/*   Menu then this function will be called.It will store the value of     */
/*   selected parameter into a variable for altering its display position. */
/***************************************************************************/

{
   StoreSelectedItem = 0;
   SelectedDisplayItem = 0;/*Initializing the selected variable.*/

   switch(TempGlobalCommandID)
   {
   case TIMEDISPLAY:
         SelectedDisplayItem = RTIME;
         break;
   case PKPWRDISPLAY:
         SelectedDisplayItem = RPKPWR;
         break;
   case ENERGYDISPLAY:
         SelectedDisplayItem = RENERGY;
         break;
   case VELOCITYDISPLAYAED:
         SelectedDisplayItem = RVELOCITY_AED;
         break;
   case VELOCITYDISPLAYAEF:
         SelectedDisplayItem = RVELOCITY_AEF;
         break;
   case FREQMINDISPLAY:
         SelectedDisplayItem = RFREQMIN;
         break;
   case FREQMAXDISPLAY:
         SelectedDisplayItem = RFREQMAX;
         break;
   case FREQSTARTDISPLAY:
         SelectedDisplayItem = RFREQSTART;
         break;
   case FREQENDDISPLAY:
         SelectedDisplayItem = RFREQEND;
         break;
   case FREQCHGDISPLAY:
         SelectedDisplayItem = RFREQCHG;
         break;
   case SETAMPADISPLAY:
         SelectedDisplayItem = RAMPSTART;
         break;
   case SETAMPBDISPLAY:
         SelectedDisplayItem = RAMPEND;
         break;
   case WELDABSDISPLAY:
         SelectedDisplayItem = RWABSDIST;
         break;
   case ACTPRESSDISPLAY:
         SelectedDisplayItem = RSYSPRESS;
         break;
   case TOTALABSDISPLAY:
         SelectedDisplayItem = RTABSDIST;
         break;
   case WELDCOLDISPLAY:
         SelectedDisplayItem = RWCOLDIST;
         break;
   case TOTALCOLDISPLAY:
         SelectedDisplayItem = RTCOLDIST;
         break;
   case WELDFORCEDISPLAY:
         SelectedDisplayItem = RFORCE;
         break;
   case SETFORCEADISPLAY:
         SelectedDisplayItem = RFORCEA;
         break;
   case SETFORCEBDISPLAY:
         SelectedDisplayItem = RFORCEB;
         break;
   case PRESETNUMDISPLAY:
         SelectedDisplayItem = RPRESETNUM;
         break;
   case CYCLETIMEDISPLAY:
         SelectedDisplayItem = RCYCLETIME;
         break;
   }
}/*end of GetSelectedDisplayParam()*/


void BuildWeldColumnStr(void)
/****************************************************************************/
/*Description:                                                              */
/*   This function preapares the display coloumn for each Weld parameter    */
/*   to show on the weld results options screen. This function is called    */
/*   before display the menu weld result options.                           */
/****************************************************************************/
{
    GetSelectedDisplayParam(GlobalCommandID);
    switch(ResultDisplayPos[SelectedDisplayItem])
    {
        case NOT_DISPLAY:
           RadioIndex = 0;
        break;
        case COLUMN1:
           RadioIndex = 1;
        break;
        case COLUMN2:
           RadioIndex = 2;
        break;
        case COLUMN3:
           RadioIndex = 3;
        break;
        case COLUMN4:
           RadioIndex = 4;
        break;
        default:
        break;
    }
    
}

void InitWeldParamOption(void)
/***************************************************************************/
/*Description:                                                             */
/* Initializes the Weld Parameter Option                                   */
/***************************************************************************/
{
   UINT8 Index;
   UINT8 Index1;
   BOOLEAN SetFlag;
         
   
   /* Check the current Weld Param options, if they are corrupted
      or not valid then initialize*/
   CurrentSetup.WeldParamOption[0] = RCYCLECOUNT;
   for(Index = 1; Index < MAX_DISPLAYED_PARAM; Index++)
   {
      if((CurrentSetup.WeldParamOption[Index] < RTIME) ||
         (CurrentSetup.WeldParamOption[Index] > RCYCLETIME))
         CurrentSetup.WeldParamOption[Index] = 0;
   }
   
//   for(Index=INDEX_START; Index < MAXSCROLLMENUS; Index++)
   for(Index=INDEX_START; Index < RMAXPARAMETERS; Index++)
    {
        SetFlag = FALSE;
        
        for(Index1 = 1; Index1 < MAX_DISPLAYED_PARAM; Index1++)
        {
           if(Index == CurrentSetup.WeldParamOption[Index1])
           {
              if(Index == RVELOCITY_AEF && (CurrentSetup.Actuator == AEF) &&
                 (BUCMenuBBR->VelocityReporting == FALSE))
              {
                 SetFlag = FALSE;
                 CurrentSetup.WeldParamOption[Index1] = 0;
              }
              else if(((CurrentSetup.Actuator == AED)||(CurrentSetup.Actuator == MICRO)) &&
                  (Index == RFORCEA   || Index == RFORCEB))
              {
                 SetFlag = FALSE;
                 CurrentSetup.WeldParamOption[Index1] = 0;
              }
              else if((CurrentSetup.Actuator == AE) &&
                  (Index == RWABSDIST || Index == RTABSDIST ||
                   Index == RWCOLDIST || Index == RTCOLDIST ||
                   Index == RFORCEA   || Index == RFORCEB   ||
                   Index == RFORCE))
              {
                 SetFlag = FALSE;
                 CurrentSetup.WeldParamOption[Index1] = 0;
              }
              else  SetFlag = TRUE;
              break;
           }
           
        }
        
        if(SetFlag)
        {
           if(Index1 == 1)
              ResultDisplayPos[Index] = COLUMN1;
           else if(Index1 == 2)
              ResultDisplayPos[Index] = COLUMN2;
           else if(Index1 == 3)
              ResultDisplayPos[Index] = COLUMN3;
           else if(Index1 == 4)
              ResultDisplayPos[Index] = COLUMN4;
        }
        else
           ResultDisplayPos[Index] = NOT_DISPLAY;        
        
    }
}

void ChangeDisplayColumn (void)
/***************************************************************************/
/*Description:                                                             */
/*   This function will replace the current column with selected parameter */
/*   if any other parameter is already displayed on the same column. This  */
/*   function is called when user pressed 'Ok' button on the Confirm screen*/
/***************************************************************************/
{
   UINT16 index, SelectedItem;
   CONFIGSETUP *BBRPtr;
   
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;

   SelectedItem = RadioIndex;
   if((SelectedItem) && ( CurrentSetup.WeldParamOption[SelectedItem] != 0 )) 
   {
      StoreSelectedItem = SelectedItem;
      /*Store the Off in currently display parameter*/
      ResultDisplayPos[CurrentSetup.WeldParamOption[StoreSelectedItem]] = NOT_DISPLAY;

      /*Store the desired column on the selected parameter.*/
      switch(StoreSelectedItem)
      {
         case 1:/*Store Column1*/
            ResultDisplayPos[SelectedDisplayItem] = COLUMN1;
         break;
         case 2:/*Store Column2*/
            ResultDisplayPos[SelectedDisplayItem] = COLUMN2;
         break;
         case 3:/*Store Column3*/
            ResultDisplayPos[SelectedDisplayItem] = COLUMN3;
         break;
         case 4:/*Store Column4*/
            ResultDisplayPos[SelectedDisplayItem] = COLUMN4;
         break;
         default:
            ResultDisplayPos[SelectedDisplayItem] = NOT_DISPLAY;
         break;
       
      }
      for(index=1;index < MAX_DISPLAYED_PARAM;index++)
         CurrentSetup.WeldParamOption[index]=0;
      for(index=INDEX_START; index < RMAXPARAMETERS; index++)
      {
         if(ResultDisplayPos[index] == COLUMN1)
         CurrentSetup.WeldParamOption[1]= index;
         else if(ResultDisplayPos[index] == COLUMN2)
         CurrentSetup.WeldParamOption[2]= index;
         else if(ResultDisplayPos[index] == COLUMN3)
         CurrentSetup.WeldParamOption[3]= index;
         else if(ResultDisplayPos[index] == COLUMN4)
         CurrentSetup.WeldParamOption[4]= index;   
      }
      /*Update all the current setup and BUCMenu variables */
      BBRPtr->WeldParamOption[1] = CurrentSetup.WeldParamOption[1];
      BBRPtr->WeldParamOption[2] = CurrentSetup.WeldParamOption[2];
      BBRPtr->WeldParamOption[3] = CurrentSetup.WeldParamOption[3];
      BBRPtr->WeldParamOption[4] = CurrentSetup.WeldParamOption[4];
   }
}

/*==========================================================================*/
/*                         END                                              */
/*==========================================================================*/






