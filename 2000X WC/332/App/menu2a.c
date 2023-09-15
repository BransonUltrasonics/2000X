/* $Header:   D:/SWLab/VMdb/2000Series/App/MENU2A.C_V   2.38   02 Sep 2008 21:05:32   nhahmed  $ */
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

   Filename: menu2a.c

   Function name:

                            
 --------------------------------- REVISIONS --------------------------------

   Revision #     Date          Author       Description
   ==========     ========      ======       ===========
      0                                      Initial Version
      1.00        04/29/96       PJ          Modified for PSOS version
      2.00        05/14/96       PJ          Prototypes in menu2.h
                                             Strings in menutext.c
      3.00        06/20/96       PJ          Changed Title Line.
      3.10        07/01/96       PJ          Enabled Energy Mode menu.
      3.20        07/19/96       PJ          Was Menu2 Now Menu2a
      4.00        07/26/96       PJ          Changed Menus from type SUBMENU
                                             to type CHOICE.
      4.10        08/01/96       PJ          Added/Changed menus per Spec Rev
                                             1.C
      4.20        08/21/96       PJ          Changed WeldModeSelectFlag to
                                             DisplayBlankFlag.
      4.30        08/23/96       PJ          Added function SelectWeldMode.
      4.40        09/19/96       PJ          Modification to SelectWeldMode
                                             and all SelectWeldMode functions.
      4.50        10/04/96       PJ          Reduced the number of FakeKeys
                                             sent on a WeldModeSelection.
      4.60        10/09/96       PhilJ       Changed Menus to type const. 
      4.70        10/24/96       PhilJ       Masked CurrentPreset.WeldMode
              .                              in SelectWeldMode().
      4.80        10/30/96       PhilJ       Added MainKey and GoBackKey checks
                                             to all SelectWeldModes. 
      4.90        11/08/96       PhilJ       Corrected bug in WeldMode selection
                                             when in the Run Screen.
      5.00        04/10/97       PhilJ       Chngd Menus from CHOICE to RADIO.
      6.2.22      06/11/97       LAM         deleted continuous mode            
      6.2.23      07/10/97       PhilJ       Changed MODEL numbers per SRS            
      6.2.24      07/23/97       PhilJ       Modified ReturnToRunscreen            
      6.2.25      07/23/97       PhilJ       Corrected unresolved external            
      6.2.26      07/28/97       PhilJ       Modified ReturnToRunScreen() to
                                             update weldmode variable.
      2.27        11/4/97        BJB         Doesn't use BlankMenuFlag.
                                             ReturnToRunScreen() uses RunKey,
                                              not MainKey + INDEX0 + Sel1,
                                              to get to Run Screen.  Also
                                              keeps screen blank across
                                              MainMenu.
      2.28        11/5/97        BJB         Oops! ReturnToRunScreen() shouldn't
                                              go to run screen, should go to
                                              Weld Setup.  Fixed this.
      2.29        07/31/98       BJB          Includes kpresmsg.h, getmsg.h
      2.29.6.1    02-07-99       JZ           removed DVS, added Mask1, Cond1, Mask2, Cond2
      2.29.6.2    02-23-00       OFI          removed 'User experience level' from menu strucutures
      2.30        04-05-00       JZ           merged Lang to trunk
      2.31        05-26-00       SCM          Checked in for testing by Laura, John.
      2.32        06-14-00       SCM          Removed tabs and checked in for build.
      2.33        06-28-00       BEKymer      Changed all MODEL to LEVEL
      2.34        08-24-00       JLH          Changed RADIO structures for collapse mode and absolute mode choices
                                               to eliminate them if acutator is AE (require AED|AEF actuator).
      2.35        07-25-05       Bwadia       Added VGA Exit and Save Buttons  
      2.36        01-11-08       NHAhmed      New functions GetWeldMode and SetWeldMode were added.
      2.37        04-16-08       NHAhmed      Modified Function SetWeldMode().
      2.38        09-02-08       NHAhmed      CleanUp for multi-language support.    
 ------------------------------- DESCRIPTION ---------------------------------
*/

      /* This file will deal with the weld setup modes. */

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include <prepc.h>
#include "portable.h"
#include "menu.h"
#include "preset.h"
#include "keypad.h"
#include "error.h"
#include "param.h"                      
#include "selctkey.h"
#include "kpresmsg.h"
#include "getmsg.h"

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern SETUPS_Ver800 CurrentPreset;

extern UINT8 MainKeyFlag;
extern UINT8 GoBackFlag;
extern UINT8 RunScreenFlag;

extern UINT8 ExitMenuCounter;
extern SINT16 BlankMenuCounter;
extern UINT16 RadioIndex;
/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                   
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/
/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/


/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------
*/
void FormatRunScreenTopLine(void);


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/



/*
 ---------------------------------- CODE -------------------------------------
*/

void GetWeldMode(void)
{
   switch(CurrentPreset.WeldMode){
   case TIMEMODE:
      RadioIndex = 0;
      break;
    case ENERGYMODE:
      RadioIndex = 1;
      break;
    case PKPOWERMODE:
      RadioIndex = 2;
      break;
    case COLLAPSEMODE:
      RadioIndex = 3;
      break;
    case ABSOLUTEMODE:
      RadioIndex = 4;
      break;
    case GRDDETECTMODE:
      RadioIndex = 5;
      break;
   }
}

void SetWeldMode(void)
{
   switch(RadioIndex){
   case 0:
      CurrentPreset.WeldMode = TIMEMODE;
      break;
   case 1:
      CurrentPreset.WeldMode = ENERGYMODE;
      break;
   case 2:
      CurrentPreset.WeldMode = PKPOWERMODE;
      break;
   case 3:
      CurrentPreset.WeldMode = COLLAPSEMODE;
      break;
   case 4:
      CurrentPreset.WeldMode = ABSOLUTEMODE;
      break;
   case 5:
      CurrentPreset.WeldMode = GRDDETECTMODE;
      break;
   }
   FormatRunScreenTopLine();
  // ReturnToRunScreen();
}


