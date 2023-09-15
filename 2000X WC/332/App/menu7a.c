/* $Header:   D:/SWLab/VMdb/2000Series/App/MENU7A.C_V   1.87.1.8   08 Jun 2010 14:11:56   NHahmed  $ */
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
/*************************                         **************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menu7a.c

   Function name:

                                     
 --------------------------------- REVISIONS --------------------------------

   Revision #      Date         Author      Description
   ==========     ========      ======      ===========
      0                                     Initial Version
                                            Strings in menutext.c
      1.00        06/20/96       PJ         Moved Counter Submenus to
                                            Systems Info(Menu7).
      1.01        07/02/96       PJ         Argument added UpdateCurrentPreset
      1.02        07/02/96       PJ         Added submenu for Custom Act Logic
      1.03        07/19/96       PhilJ      Deleted MESSAGESIZE from StrOff
                                            and StrOn to reduce ROM size.
      1.10        08/01/96       PhilJ      Added/Changed menus per Spec Rev
                                            1.C
      1.20        09/04/96       PhilJ      Added PSOS Set Time/Date function. 
      1.30        10/09/96       PhilJ      Changed Menus to type const. 
      1.40        10/19/96       PhilJ      Added ActClrFlag to OutPutAtPosSw
                                            menu. 
      1.50        10/22/96       PhilJ      Modified GetTimeAndDate.
      2.00        10-23-96       BEKymer    Use CurrentSetup.ActClrDistance in
                                            const VARIABLE Distance structure
                                            Added initial value to Min/Max for
                                            ActClrDistance
      2.10        10/29/96       PhilJ      Deleted AmpControlExternal and
                                            FreqControlExternal, Never Used.
      2.11        11/02/96       PaulG      Enable GoBack before saving a selection.
      2.12        11/08/96       PhilJ      UpdateCurrentSetup function called
                                            for Language, BaudRate, Weld Scale,
                                            and Test scale menus.
      3.00        01/28/97       LAM        deleted unused variables       
      4.00        02/07/97       LAM        moved actclr to preset             
      4.10        02/13/97       PhilJ      Deleted UpdateCurrentSetup from
                                            Weld and Test Scale functions.
      4.20        02/24/97       PhilJ      Modified SetDateAndTime for new
                                            Timekeeping Ram.
      4.30        03/13/97       PhilJ      Changed string in Day menu to M7A_31A.
      4.40        03/17/97       BEKymer    Added string for Remote Terminal
      4.50        06/16/97       PhilJ      Added new parameter ID's to menus
      5.1.24      06/18/97       PhilJ      Changed Weld and TestTime menus
                                            from CHOICE to RADIO.
      5.1.25      06/19/97       PhilJ      Changed BaudRate & Language menus
                                            from CHOICE to RADIO.
      5.1.26      06/23/97       PhilJ      Redefined BaudRates in menu7a.h.
      5.1.28      07/09/97       PhilJ      Restructured Serial Port menu
      5.1.29      07/11/97       PhilJ      Deleted SWHandshake from menu.
      5.1.30      07/18/97       PhilJ      Added cylinder size & stroke length
                                            menus.
      5.1.31      07/18/97       PhilJ      Deleted Call to DTEnabled in SetRemote
      5.1.32      07/21/97       PhilJ      Enabled Call to DTEnabled in SetRemote
      5.1.33      08/13/97       PhilJ      Added Beepers and Scaling menus.
      5.1.34      08/15/97       PhilJ      Deleted Echo mode menu.
      5.1.35      08.26.97       JBerman    1) Comment out: StrM7_18[]
                                                            StrM7_19[]
                                               I couldn't find it anywhere else.
                                            2) WeldScaleChoice\
                                               TestScaleChoice/Module4 -> Module1
      5.1.36      08.27.97       JBerman    Added: #include <prepc.h>
                                                   CylDiamBuffer[MESSAGESIZE]; 
                                                   StrokeBuffer[MESSAGESIZE];
                                                   CylnBufferPrnt[PRTMSGBUFF];   
                                                   StrkBufferPrnt[PRTMSGBUFF];  
      5.1.37      08.29.97       JBerman    Corrected Cyln/Strk BufferPrnt
      5.1.38      09.04.97       JBerman    Replaced ADVANCED with NORMAL
      1.39        09.10.97       LAM        added dtoutput.h              
      1.40        09.10.97       LAM        deleted unused prototype
      1.41        10.03.97       JBerman    Added Cyln Dia(mm) & Stroke(mm)
                                            into Radio Menues.
      1.42        10.07.97       JBerman    Typo Storke -> Stroke
      1.43        10.08.97       JBerman    Replaced Strings in GetCylinderIndex
                                            and in GetStrokeLenIndex
      1.44        10.13.97       JBerman    Removed 19200 BaudRate from menu                                       
      1.45        10.30.97       LAM        Removed BaudRate from remoteterm menus                           
      1.46        11.13.97       JBerman    Added BaudRate 19200 to Serial Com
      1.47        11.18.97       JBerman    Change TITLE BOAUDRATE to MODEL 1
      1.48        11.24.97       LAM        deleted unused currentsetup elements
      1.49        12.29.97       BJB        Deleted "extern DTEnabled", not used.
      1.50        12.31.97       BJB        SetDumbTerminal() calls
                                             SerialIntBaud() directly.
                                            Modified SetRemote(), SetHost() for
                                             new terminal code.
                                            Added comment terminators to satisfy
                                             compiler.
      1.51        12.31.97       BJB        Deleted include of dtoutput.h!
      1.52        01.26.98       BJB        Calls GetCylinderIndex(),
                                             GetStrokeLenIndex() on exit from
                                             their radio menus as well as on
                                             entry.
      1.53        02.02.98       JBerman    In "CHOICE HostComputer", changed
                                            HostComputerMenu to NULL.
                                            In that way the user can't access
                                            and change the BaudRate.  
      1.54        03.10.98       JBerman    Changed all CurrentPreset.StrokeLen
                                            to CurrentSetup.StrokeLen
      1.55        04.28.98       BJB        Deleted unused Vptr[] array, unused
                                             ID   ID in RADIOMENU items.
      1.56        05-06-98       BEKymer    Call SetMaxMinValues() when either
                                            GetCylinderIndex or GetStrokeLenIndex
                                            is called
      1.57        05-08-98       BEKymer    SetCylSize in GetCylinderIndex.
                                            SetStrokeLength in GetStrokeLenIndex
      1.58        07-30-98       BJB        Split up GetCylinderIndex(),
                                             GetStrokeLenIndex() into functions
                                             that get indices, functions that
                                             format strings, and functions that
                                             change settings.
                                            Calls new "Set" functions when menus
                                             used to change settings.
      1.59        08-19-98       BJB        Changed some terminal function calls
                                             to their new names.
                                            Uses new EnableRemoteTerminal() to
                                             turn terminal on.
      1.60        09-01-98       BEKymer    Call SetCylinderIndex whenever cylinder
                                            size is changed and SetStrokeLenIndex
                                            whenever stroke is changed.  Was
                                            called from RADIOMENU, but was too
                                            late for VerifyPreset.
      1.61        10-22-98       LAM        do not try to write to actuator nvram
                                            with an ae actuator
      1.62        10-29-98       BJB        Removed cyl diameter and stroke len
                                             settings that should not be available
                                             until Release 3.
      1.63        10-08-99       BEKymer    Call InitializePV when cylinder size
                                            has been changed
      1.64        10-25-99       JZ         removed SetDateAndTime() used RTCMenu for date and time                                           
      1.64.6.1    02-07-00       JZ         removed DVS, added Mask1, Cond1, Mask2, Cond2 
      1.64.6.2    02-23-00       OFI        removed 'User experience level' from menu strucutures                                      
      1.64.6.3    02-29-00       JLH        Added Spanish and Italian choices to submenus.
      1.65        04-05-00       JZ         merged Lang to trunk  
      1.66        05-26-00       SCM        Checked in for testing by Laura, John. 
      1.67        06-14-00       SCM        Replaced array index-20 with 'define' LINESIZE.                                                
      1.68        06-16-00       LAM        Language starts at a Level "t".  
      1.69        06-28-00     BEKymer      Changed all MODEL to LEVEL
      1.70        08/15/00       SCM        Commented out OutputAtPosSw (Ver9 requirement)
      1.71        08/16/00       AT         Fixed GetCylinderStrings() and GetStrokeLenStrings() #3315
      1.72        08/16/00       AT         Fixed language indexing in the above
      1.73        08/17/00       AT         Fixed language indexing once more
      1.74        08/18/00       LAM        updated defaults on a cylinder change(Issue 3276)
      1.75        11-28-00       BEKymer    Modify UpdateCylDefaults() for 4" cylinder
                                            Modify GetCylinderStrings() for 4" cylinder
                                            Added 4" cylinder to CyclSizeMenu[]
                                            Modify GetCylinderIndex() for 4" cylinder
      1.75.1.0    08-20-01       BEKymer    Removed Sethost() and SetRemote() and inserted SetRS232()
                                             Modified menu structures to support RS232 radio menus
      1.75.1.1    08-21-01       BEKymer    Detab
      1.75.1.2    08-15-03       BEKymer    Add Custom logic submenu to act settings
      1.76        01-19-01       BEKymer    Use StrM7A_52X in place of duplicate StrM7A_53N
      1.77        10-08-01       LAM        merged preset cleanup with 8.Specials 
      1.78        12-04-03       BEKymer    Merged 1.77 & 1.75.1.2 to create 1.78
                                             for Ver9.00b build
      1.79        02-20-04       VSharma    Added CHOICE 'BeeperRelease' in 'BeeperSubmenu'.
                                            Added DisplayUserIOMenu(), QVGADisplayUserIOMenu() &
                                            ExitUserIOMenu().
      1.81        04-06-04       VSharma    Added EnterUserIOAlarmsMenu().
      1.82        04-19-04       VSharma    Modified UserIO related function.
                                            Added QVGAActSettingsMenu.
      1.83        05-17-04       VSharma    Removed extern of unused strings.             
      1.84        07-25-05       Bwadia     Added new languages and support for Asian 
                                            Language for cylinder size, stroke length strings
      1.185       09-10-05       Bwadia     Cylinder string and stroke length strings
                                            function changed to support VGA printing
      1.186       12-22-06       NHAhmed    Added Decimal choice to Actuator Settings.
      2.187       01-31-07       NHAhmed    Changes related to Changed Structure variables of CHOICE and TOGGLE.
      2.188       10-22-07       NHAhmed    Changes done for LangTest phase 0
      2.189       01-11-08       NHAhmed    Some functions are replicated to a none argument type, 
                                            keeping all functionality same.
                                            Added new functions SetWeldScaleIndex and SetTestScaleIndex.
      2.190       04-14-08       NHAhmed    Renamed some functions.
      2.191       09-02-08       NHAhmed    CleanUp for multi-language support.    
      2.192       09-04-08       YGupta     CleanUp for LangTest Project.   
      2.193       09-09-08       NHAhmed    CleanUp for multi-language support.    
      2.194       10-20-08       NHAhmed    Replaced stroke length LENGTH_7 by LENGTH_2.    
      1.87.1.7    09-10-09       BEkymer    Add new define MICRO where needed
      1.87.1.8    06-08-10       PDwivedi   Modify GetStrokeLenIndex for configure standard MICRO.      
      
------------------------------- DESCRIPTION ---------------------------------
*/
 
/* This file is used in conjunction with menu7.c (system options).  The    */
/* sub menus will be handled here.                                         */






//-----------------------------LOCAL_EQUATES---------------------------------


#define PRTMSGBUFF 24


// ------------------------------ INCLUDE FILES --------------------------------

#include <psos.h>
#include "time.h"
#include "string.h"
#include "menu.h"
#include "rtclock.h"
#include "error.h"
#include "preset.h"
#include "param.h"
#include "kpresmsg.h"             /* key pressed message definition   */
#include "selctkey.h"
#include "menu7.h"
#include "menu7a.h"
#include "sysmangr.h"
#include "state.h"
#include "util.h"
#include "statedrv.h"
#include "serial.h"
#include "actnvram.h"
#include "mansensr.h"
#include "beep.h"
#include "qvgamenu.h"
#include "display.h"
#include "outports.h"
#include "ready.h"
#include "alarms.h"

/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------
*/


/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern BUCMENU_800 BUCMenuRAM, *BUCMenuBBR;
extern BOOLEAN IsThereDataPrinting;
extern BOOLEAN IsGraphDrawing;
extern UINT32 KeyMask;
extern UINT32   Ticks;
extern UINT16 DisplayNextMenu;
extern CONFIGSETUP CurrentSetup;
extern SETUPS_Ver800 CurrentPreset;
extern SETUPS_Ver800 MinLimit;
extern SETUPS_Ver800 MaxLimit;
extern UINT8  GoBackFlag;
extern RTC RTCMenu;
extern QVGA_MENU_INFO MenuLevelInfo[];
extern REDRAW_SEG RedrawSeg;
extern enum WELDSTATES WeldState;
void LangStrCpy(SINT8 * to, SINT8 * from);
void SetWeldScaleIndex (void);
void SetTestScaleIndex (void);




/*------------------------------- GLOBAL DATA -------------------------------*/
/*                      (scope is global to ALL files)                       */


MENUEND endlist7A = { TRUE };
BOOLEAN StateMachineDisabled = FALSE;
UINT32  TempStoreKeyMask;
UINT16  RadioIndex;
BOOLEAN  HHInactive = FALSE;
BOOLEAN UserIOAlarmMenu = FALSE;
BOOLEAN WeldingStopInsideMenu = FALSE;

/*---------------------------------- CODE -----------------------------------*/



/***   ***   Language Submenu   ***   ***/


void SetDumbTerminal(void)
{  
   switch(CurrentSetup.BaudRate){
      case BAUD_4800:
         SerialIntBaud(4800);
         break;
      case BAUD_9600:
         SerialIntBaud(9600);
         break;
      case BAUD_19200:
         SerialIntBaud(19200);
         break;
   
      default:
         SerialIntBaud(9600);
         break;
   }
}



void GetBaudIndex(void){
   if(CurrentSetup.BaudRate == BAUD_4800)
      RadioIndex = 0;
   else if(CurrentSetup.BaudRate == BAUD_9600)
      RadioIndex = 1;
   else if(CurrentSetup.BaudRate == BAUD_19200)
      RadioIndex = 2;
   else RadioIndex = 1;     // (CurrentSetup.BaudRate == BAUD_9600)
}



void SetRS232Terminal(void)
/*****************************************************************************/
/*  This function handles turning on and off the terminal, Compuweld and     */
/*  each of the ASCII output choices.  This is called from the menu system   */
/*  whenever a change is made to the serial port and what it is connected to.*/
/*  There are no arguments.  It uses the global in CurrentSetup.SerialPort   */
/*  to decide what to do.                                                    */
/*****************************************************************************/
{
   switch (RadioIndex) {
      case 0:
         CurrentSetup.SerialPort = COMPUWELD;
         SerialIntRxion();    /* Turn on receive ints for host comm */
         break;

      case 1:
         CurrentSetup.SerialPort = TERMINAL;
         break;

      case 2:
         CurrentSetup.SerialPort = ASCIICOMMA;
         SerialIntRxioff();   /* Turn host mode off */
         break;

      case 3:
         CurrentSetup.SerialPort = ASCIITAB;
         SerialIntRxioff();   /* Turn host mode off */
         break;

      case 4:
         CurrentSetup.SerialPort = ASCIISPACE;
         SerialIntRxioff();   /* Turn host mode off */
         break;

      case 5:
         CurrentSetup.SerialPort = RS232DISABLED;
         SerialIntRxioff();   /* Turn host mode off */
         break;
    }
}

void SetRS232(void)
/*****************************************************************************/
/*  This function handles turning on and off the terminal, Compuweld and     */
/*  each of the ASCII output choices.  This is called from the menu system   */
/*  whenever a change is made to the serial port and what it is connected to.*/
/*  There are no arguments.  It uses the global in CurrentSetup.SerialPort   */
/*  to decide what to do.                                                    */
/*****************************************************************************/
{
   switch (CurrentSetup.SerialPort) {
      case COMPUWELD:
         SerialIntRxion();    /* Turn on receive ints for host comm */
         break;

      case TERMINAL:
         break;

      case ASCIICOMMA:
         SerialIntRxioff();   /* Turn host mode off */
         break;

      case ASCIITAB:
         SerialIntRxioff();   /* Turn host mode off */
         break;

      case ASCIISPACE:
         SerialIntRxioff();   /* Turn host mode off */
         break;

      case RS232DISABLED:
         SerialIntRxioff();   /* Turn host mode off */
         break;
    }
}

void GetCylinderIndex(void)     // For Information & PrintOut
{
   switch(CurrentSetup.CylinDiameter)
   {
      case CUSTOMSIZE:
         RadioIndex = 9;        
         break;
      
      case SIZE1_5:
         RadioIndex = 0;
         break;
      
      case SIZE2_0:
         RadioIndex = 1;
         break;
     
      case SIZE2_5:
         RadioIndex = 2;
         break;
      
      case SIZE3_0:
         RadioIndex = 3;
         break;
      
      case SIZE3_25:
         RadioIndex = 4;
         break;
      
      case SIZE_40:
         RadioIndex = 5;
         break;
      
      case SIZE_50:
         RadioIndex = 6;
         break;
      
      case SIZE_63:
         RadioIndex = 7;
         break;
      
      case SIZE_80:
         RadioIndex = 8;
         break;
      
      case SIZE4_0:
         RadioIndex = 10;
         break;
      
      default:
         break;
   }
}


void SetCylinderDiameter(void)
/****************************************************************************/ 
/*                                                                          */
/* This updates the cylinder size in the actuator novram and sets the min & */
/* max force values. If an ae is installed it updates the strings only.     */
/*                                                                          */
/* Inputs :  CurrentSetup.Actuator                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/****************************************************************************/ 
{
   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == MICRO) )
   {
      switch(RadioIndex) {
         case 9:
            CurrentSetup.CylinDiameter = CUSTOMSIZE;
            break;
      
         case 0:
            CurrentSetup.CylinDiameter = SIZE1_5;
            break;
      
         case 1:
            CurrentSetup.CylinDiameter = SIZE2_0;
            break;
     
         case 2:
            CurrentSetup.CylinDiameter = SIZE2_5;
            break;
      
         case 3:
            CurrentSetup.CylinDiameter = SIZE3_0;
            break;
      
         case 4:
            CurrentSetup.CylinDiameter = SIZE3_25;
            break;
      
         case 5:
            CurrentSetup.CylinDiameter = SIZE_40;
            break;
      
         case 6:
            CurrentSetup.CylinDiameter = SIZE_50;
            break;
      
         case 7:
            CurrentSetup.CylinDiameter = SIZE_63;
            break;
      
         case 8:
            CurrentSetup.CylinDiameter = SIZE_80;
            break;
      
         case 10:
            CurrentSetup.CylinDiameter = SIZE4_0;
            break;
      
         default:
            break;
      }
      SetCylSize(CurrentSetup.CylinDiameter);
   }
   UpdateCylDefaults();
   SetMaxMinValues();                /* Force maximum values to be updated */
   InitializePV();                   /* Re-establish steplimit for new size*/
}



void SetCylinderIndex(void)
/****************************************************************************/ 
/*                                                                          */
/* This updates the cylinder size in the actuator novram and sets the min & */
/* max force values. If an ae is installed it updates the strings only.     */
/*                                                                          */
/* Inputs :  CurrentSetup.Actuator                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/****************************************************************************/ 
{
   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == MICRO) )
   {
      SetCylSize(CurrentSetup.CylinDiameter);
   }
   UpdateCylDefaults();
   SetMaxMinValues();                /* Force maximum values to be updated */
   InitializePV();                   /* Re-establish steplimit for new size*/
}


 
void UpdateCylDefaults(void)
/****************************************************************************/ 
/*                                                                          */
/* This updates the defaults when the cylinder size is changed or when the  */
/* DoColdStartPlus function is run.                                         */
/*                                                                          */
/* Inputs :  CurrentSetup.CylinDiameter                                     */
/*                                                                          */
/****************************************************************************/ 
{ 
   switch(CurrentSetup.CylinDiameter){          /* cylinder diameter */
        case SIZE2_0:                                     /*   2"  */
        case SIZE_50:                                     /*  50mm */
        case SIZE1_5:                                     /* 1.5"  */
        case SIZE_40:                                     /*  40mm */
           CurrentSetup.MinTrigForce = MIN_TRIGGER_FORCE_DEFAULT_2IN;
           BUCMenuRAM.ForcePC = FORCE_PC_DEFAULT_2IN;
           BUCMenuBBR->ForcePC = FORCE_PC_DEFAULT_2IN;
           break;

        case SIZE3_0:                                     /*   3"  */
        case SIZE2_5:                                     /* 2.5"  */
        case SIZE3_25:                                    /* 3.25" */
        case SIZE4_0:                                     /* 4.0"  */
        case SIZE_63:                                     /*  63mm */
        case SIZE_80:                                     /*  80mm */
        default:
           CurrentSetup.MinTrigForce = MIN_TRIGGER_FORCE_DEFAULT_3IN;
           BUCMenuRAM.ForcePC = FORCE_PC_DEFAULT_3IN;
           BUCMenuBBR->ForcePC = FORCE_PC_DEFAULT_3IN;
           break;
   }
}

void GetStrokeLenIndex(void)
{
   switch(CurrentSetup.StrokeLen)
   {
      case CUSTOMLEN:
         RadioIndex = 9;         
         break;
      
      case LENGTH_4:
         RadioIndex = 0;
         break;
      
      case LENGTH_5:
         RadioIndex = 1;
         break;
      
      case LENGTH_6:
         RadioIndex = 2;
         break;
      
      case LENGTH_2:
         RadioIndex = 3;
         break;
     case LENGTH_8:
         RadioIndex = 4;
         break;
      
      case LENGTH_80:
         RadioIndex = 5;
         break;
      
      case LENGTH_100:
         RadioIndex = 6;
         break;
      
      case LENGTH_125:
         RadioIndex = 7;
         break;
      
      /*case LENGTH_160:
         RadioIndex = 8;
         break;*/
      case LENGTH_50:
         RadioIndex = 8;
         break;
      default:
         break;
   }
}


void SetStrokeLen(void)
/****************************************************************************/ 
/*                                                                          */
/* This updates the cylinder size in the actuator novram and sets the min & */
/* max force values. If an ae is installed it updates the strings only.     */
/*                                                                          */
/* Inputs :  CurrentSetup.Actuator                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/****************************************************************************/ 
{
   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == MICRO) )
   {
      switch(RadioIndex)
      {
      case 9:
         CurrentSetup.StrokeLen = CUSTOMLEN;
         break;
      
      case 0:
         CurrentSetup.StrokeLen = LENGTH_4;
         break;
      
      case 1:
        CurrentSetup.StrokeLen = LENGTH_5;
         break;
     
      case 2:
         CurrentSetup.StrokeLen = LENGTH_6;
         break;
      
      case 3:
         CurrentSetup.StrokeLen = LENGTH_2;
        break;
      
      case 4:
         CurrentSetup.StrokeLen = LENGTH_8;
         break;
      
      case 5:
         CurrentSetup.StrokeLen = LENGTH_80;
         break;
      
      case 6:
         CurrentSetup.StrokeLen = LENGTH_100;
         break;
      
      case 7:
         CurrentSetup.StrokeLen = LENGTH_125;
         break;
      
     /* case 8:
         CurrentSetup.StrokeLen = LENGTH_160;
         break;*/
      case 8:
         CurrentSetup.StrokeLen = LENGTH_50;
         break;
      default:
         break;
      }
      SetStrokeLength(CurrentSetup.StrokeLen);
   }
   SetMaxMinValues();                /* Force maximum values to be updated */
}

void SetStrokeLenIndex(void)
/****************************************************************************/ 
/*                                                                          */
/* This updates the stroke length in the actuator novram and sets the min & */
/* max stroke values. If an ae is installed it updates the strings only.    */
/*                                                                          */
/* Inputs :  CurrentSetup.Actuator                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/****************************************************************************/ 
 {
   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == MICRO) )
   {
      SetStrokeLength(CurrentSetup.StrokeLen);
   }
   SetMaxMinValues();                /* Force maximum values to be updated */
}

void GetWeldScaleIndex(void)
{
   if(CurrentSetup.TimeMultiplier == WELDTIMEx1)
      RadioIndex = 0;
   else if(CurrentSetup.TimeMultiplier == WELDTIMEx2)
      RadioIndex = 1;
   else if(CurrentSetup.TimeMultiplier == WELDTIMEx3)
      RadioIndex = 2;
}

void SetWeldScaleIndex (void)
{
   if(RadioIndex == 0)
      CurrentSetup.TimeMultiplier = WELDTIMEx1;
   else if(RadioIndex == 1)
      CurrentSetup.TimeMultiplier = WELDTIMEx2;
   else if(RadioIndex == 2)
     CurrentSetup.TimeMultiplier = WELDTIMEx3;
}

void GetTestScaleIndex(void)
{
   if(CurrentSetup.TestMultiplier == TESTTIMEx1)
      RadioIndex = 0;
   else if(CurrentSetup.TestMultiplier == TESTTIMEx2)
      RadioIndex = 1;
   else if(CurrentSetup.TestMultiplier == TESTTIMEx3)
      RadioIndex = 2;
}

void SetTestScaleIndex (void)
{
   if(RadioIndex == 0)
      CurrentSetup.TestMultiplier = TESTTIMEx1;
   else if(RadioIndex == 1)
      CurrentSetup.TestMultiplier = TESTTIMEx2;
   else if(RadioIndex == 2)
     CurrentSetup.TestMultiplier = TESTTIMEx3;
}

void CheckForPrintingOrWelding(void)
/****************************************************************************/
/*Descriptions:-                                                            */
/*   This function will Check for the ready or pre-ready state. If the      */
/*   system is in ready state then stop the state machine and disable the   */
/*   HornDown and Test key and the next menu will be displayed, else the    */
/*   system will beep and don't display the next menu for selected Submenu. */  
/****************************************************************************/
{
   /* Check for the Ready or Pre-Ready state. */
   if ( ( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
         &&(IsThereDataPrinting == FALSE) && (IsGraphDrawing == FALSE))
   {
      StopStateMachine(); /* Stop the State machine*/
      StateMachineDisabled = TRUE;
      TempStoreKeyMask = KeyMask; /* Don't allow Test key  */
      KeyMask &= ~(TESTKEYMASK | HORNDOWNKEYMASK); 
      DisplayNextMenu = TRUE;   
   }
   else
      DisplayNextMenu = FALSE; // Checked  in ProcessMenuItem().
   
}


void  ExitMenuAndEnableWeld (void)
/****************************************************************************/
/*Descriptions:-                                                            */
/*   This function will Reset & Start the state machine & Enable the Test   */
/*   key, when exit from the UserIO menu or custom menu.                    */
/****************************************************************************/
{
   if(StateMachineDisabled)
   {
      KeyMask = TempStoreKeyMask;//Enable the Test and HornDown key.
      StateMachineDisabled = FALSE;
      DisplayNextMenu = TRUE; 
      if(UserIOAlarmMenu)  
         UserIOAlarmMenu = FALSE;
      ResetStateMachine(); // Reset and start the state machine.
      StartStateMachine();
   }
}

