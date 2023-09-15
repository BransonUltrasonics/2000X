/* $Header:   D:/SWLab/VMdb/2000Series/App/menu8.c_v   1.16   04 Sep 2008 20:16:30   ygupta  $ */
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
 ---------------------------- MODULE DESCRIPTION ----------------------------
                        
   Module name:          View Setup

   Filename:             Menu8.c

   Function name:                      


 --------------------------------- REVISIONS --------------------------------

   Revision #  Date      Author   Description
   ==========  ========  ======   ===========
      1.0      09-07-01  BEK      Initial Version (copied from menu2.c)
      1.1      09-25-01  BEKymer  Removed unused ViewPretrigExt
      1.2      09-25-01  BEKymer  Change Distance structure name to ViewDistance      
      1.3      10-09-01  LAM      Added argument to TEXT and SUBMENU structure calls  
      1.4      10-16-03  BEKymer  Call no function in ViewChangeFreqSign, 
                                   otherwise change sign would be allowed on
                                   View Setup (a no no!!!)
                                  Change TOGGLEs to use XXCANTCHANGEXX
                                  Add EnergyBraking and Ext Trigger delay
      1.5      02-20-04  VSharma  Change ID of RADIOLARGE to XXCANTCHANGEXX.
                                  Added ViewSetupBeep.
      1.6      05-17-04  VSharma  Removed extern of unused strings.                    
      1.7      09-09-04  BEkymer  Add Energy Brake variable as submenu
      1.8      07-25-05  Bwadia   VGA Exit and Save button added  
      1.9      11-02-05  Aare     Removed call to SelectDistPretrig function,
                                  function is not needed to view setup and
                                  was removed from menu2.c
      1.10     02-22-06  Bwadia   View menu implemented for memory reset toggle button 
      1.11     01-31-07  NHAhmed  Changes related to Changed Structure variables of CHOICE and TOGGLE.
      1.12     03-12-07  NHAhmed  Changes for Force/Amp Step.
      2.13     04-24-07  NHAhmed  Changes related to Force and Amplitude Step/Fixed.
      2.14     10-22-07  NHAhmed  Changes done for LangTest phase 0
      2.15     09-02-08  NHAhmed  CleanUp for multi-language support.    
      2.16     09-04-08  YGupta   CleanUp for LangTest Project.

      ------------------------------- DESCRIPTION ---------------------------------

       This file will deal with the the view setup submenu.
*/

/*----------------------------- INCLUDE FILES ------------------------------*/

#include <psos.h>
#include "portable.h"
#include "menu.h"
#include "preset.h"
#include "param.h"
#include "limits.h"
#include "keypad.h"
#include "selctkey.h"
#include "beep.h"
#include "kpresmsg.h"
#include "getmsg.h"
#include "ready.h"
#include "menu1.h"
#include "menu2.h"
#include "menu3.h"
#include "dups_api.h"
#include "state.h"
#include "ticks.h"

/*----------------------------- EXTERNAL FUNCTIONS --------------------------*/



/*------------------------------- EXTERNAL DATA -----------------------------*/

extern UNION_BOOL_UINT16 FreqControlInternal;
extern UINT16 FreqControlExternal;
extern UNION_BOOL_UINT16 AmpControlInternal;
extern UINT16 RadioIndex;
extern UINT16 LangIndex;

extern SETUPS_Ver800 CurrentPreset;    /* from SETUP to SETUPS_Ver800 */
extern SETUPS_Ver800 MaxLimit;         /* from SETUP to SETUPS_Ver800 */

extern SETUPS_Ver800 MinLimit;         /* from SETUP to SETUPS_Ver800 */

extern UINT16 ForceFixedEnableFlag;
extern enum  WELDSTATES WeldState;

extern CONFIGSETUP CurrentSetup;

extern UINT8 SetupFlag;
/*------------------------------- GLOBAL DATA -------------------------------*/
/*                      (scope is global to ALL files)                       */


/*------------------------------- LOCAL DEFINES -----------------------------*/

#define AMPSTEPMASK   0xFFFE  /* Changed from 7C to FFFE V11.2.44 BEK 05-09-97 */
#define FORCESTEPMASK 0xFFFE

/* This variable needs to be defined later on. For now this is used by default */
//extern SINT32 TOBEDEFINED;

/* This FUNCTION needs to be defined later on. For now this is used by default */
//void TOBEDEFINEDFN(void);


/*---------------------------------- CODE -----------------------------------*/
#include "display.h"


void ErrorBeep(void)
/*****************************************************************************/
/* This function will beep (ERROR).  It should be called whenever it is      */
/* illegal to select a submenu or other select key.                          */
/*****************************************************************************/
{
   Beep(ERRORBEEP);
}

void ViewSetupBeep(UINT32 Dummy)
/*****************************************************************************/
/* This function will beep (ERROR).  It should be called whenever it is      */
/* illegal to select a submenu or other select key.                          */
/*****************************************************************************/
{
   Beep(ERRORBEEP);
}

void RestorePreset(void)
/*****************************************************************************/
/* This function is used to restore preset 0 back into the running preset.   */
/* This is the magic that is used to make this menu read-only (changes are   */
/* thrown away).                                                             */
/*****************************************************************************/
{
   RecallCompressedPreset( (PRESET_COMPRESSED *) PRESET_0_START);   /* Decompress preset 0 back into current preset    */
}



