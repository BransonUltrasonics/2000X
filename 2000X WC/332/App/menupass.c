/* $Header:   D:/SWLab/VMdb/2000Series/App/MENUPASS.C_V   1.37.1.6   21 Oct 2009 16:33:42   bkymer  $ */
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

   Filename: menupass.c

   Function name:

                                       
 --------------------------------- REVISIONS --------------------------------

 Rev # Date     Author Description
 ===== ======== ====== ======================================================
 0                     Initial Version
 1.00  05/22/96 PhilJ  Enabled PassWord Menu.  Similar to Preset description.
                        Can use Alpha/Numeric characters.
 2.00  08/22/96 LAM    deleted portable.h
 2.10  08/23/96 PJ     Changed Password Accepted menu text.
 2.20  10/10/96 PhilJ  Changed menus to type const.
 2.30  10/18/96 PhilJ  Added EnterPassword menu for security check.
 2.40  01/07/97 PhilJ  Corrected aborting Password menu.
 3.00  01/28/97 LAM    deleted unused vars              
 4.1.7 06/17/97 PhilJ  Chngd UpdateCurrentSetup to UpdateCurrentPreset.
 4.1.8 07/31/97 PhilJ  Modified AssignPasswordName if GoBack or MainKey
                        pressed.
 4.1.9 08/06/97 PhilJ  Added IncorrectPasswordMenu
 1.10  10-16-97 BJB    Includes vf.h
                       Deleted flags PasswordEnableFlag, PasswordOkFlag.
                       Deleted menu PasswordOkFlag.
                       Deleted functions SetPasswordFlag(), StartOver(),
                        SendSelect1Key(), TryAgain().
                       Added function ExitMenuFunction().
                       Rewrote AssignPasswordName().
                       Got rid of AssignPassword1..3, RetypePassword1..Name
                        menu items.
                       Menus use EnterPassword1..3. Note this means no call to
                        SendSelect1Key() when last line of retype menu
                        selected.
                       Changed call to StartOver() to call to
                        ExitMenuFunction() in PasswordIncorrect menu.
                       Changed call to TryAgain() to call to
                        ExitMenuFunction() in IncorrectPassword menu.
                       Added new ALPHA elements to EnterPassword1..3
                       Deleted PasswordIncorrectMenu[],
                        IncorrectPasswordMenu[], and all associated menu
                        items.
 1.11  10-21-97 BJB    Uses uppercase PASSWORD title when "password accepted"
                        screen shown.
                       Includes "security.h"
                       Sets security level to MAINTAINENCE when new password
                        entered.
 1.12  11-4-97  BJB    Doesn't use BlankMenuFlag, MainKeyFlag
                       Doesn't send fake "NOKEY" before displaying menus.
                       MainKey not allowed to exit "password incorrect"
                        screen.
 1.13  11-08-97 BJB    Uses StrAlpha1[], StrAlpha2[] instead of StrM3_5[],
                        StrM3_6[].
 1.14  11-11-97 BJB    Responds to ResetKey from WaitKeyPress()
 1.15  12-10-97 BJB    Uses WorkingPasswordFlag in AssignPasswordName() to see
                        if user wants passwords, copies to CurrentSetup only
                        when valid password is entered.
                       Calls UpdateCurrentPreset() from in here when
                        CurrentSetup actually changed.
                       Don't need SavedPasswordFlag.
 1.16  12-11-97 BJB    Writes new password to preset only after it has been
                        verified.
 1.17  04-06-98 BJB    Calls WaitMessage() instead of tm_wkafter().
 1.18  04-28-98 BJB    Replaced AssignPasswordMenu[], RetypePasswordMenu[]
                        with AssignPassword, RetypePassword items.
                       Deleted EnterPasswordItem[], put EnterPassword in
                        SECURITY.C
                       Uses AlphaEntry() function to read passwords.
 1.19  09-03-98 BJB    Some code to react to ResetKey removed, will be
                        executed inside DisplayResetMsg().
 1.19.6.1 02-08-00 JZ   removed DVS, added Mask1, Cond1, Mask2, Cond2
 1.19.6.2 02-23-00 OFI  removed 'User experience level' from menu strucutures
 1.20     04-06-00 JZ   merged Lang to trunk
 1.21     05-26-00 SCM      Checked in for testing by Laura, John.
 1.22     06-07-00 LAM      deleted unused extern
 1.23     06-28-00 BEKymer  Changed all MODEL to LEVEL
 1.24     09-09-03 JOY      Added 'QVGAAssignPasswordName()'&& 'CheckForSecretMenu()'. 
 1.25     09-27-03 JOY      Restricted Maintainance password to six chars.
 1.26     09-30-03 JOY      Confirmation of passwords removed for Secret Functions. 
 1.27     10-03-03 JOY      Added Wait message while accessing secret function
                            -(one which takes long time to execute).
 1.28     10-16-03 JOY      MiddleSeg. Erased by QVGA ROM image.
 1.29     02-25-04 VSharma  Added 'INDEX_RESTORE_DEFAULTS'.
                            Modified CheckForSecretMenu().
 1.30     07-12-04 LAM      Deleted duplicate NUMBER_OF_CODES define
 1.31     04-15-05 LAM      added AED/AEF SBeam defines
 1.32     07-25-05 Bwadia   QVGA clean up and password support for VGA
 1.33     01-03-06 Bwadia   DUPS secret menu menu items added. Modified for tracker 3963  
 1.34     01-12-06 Bwadia   DUPS menu as under BUC menu shown when secret code entered
                            Modified for tracker issue 3963
 1.35     01-24-06 Bwadia   Modified for tracker issue 4058. New User I/O default
                            settting menus added                                  
 1.36     03-02-06 Bwadia   Trigger force secret menu in VGA implemented
 1.37     22-12-06 NHAhmed  Changed the #define value INDEX_TRIGGERFORCE from 30 to 28 
                            to unhide the DUPS HSC, Min. Trigger and Part Contact.
 1.38     10-22-07 NHAhmed  Changes done for LangTest phase 0
 1.39     01-11-08 NHAhmed  Added new function VGAPasswordEntry and updated VGAPasswordSave.
 1.40     04-14-08 NHAhmed  Renamed some Functions.
 1.41     08-26-08 NHAhmed  Modified function PasswordSave().
 1.42     09-02-08 NHAhmed  CleanUp for multi-language support.
 1.43     09-04-08 YGupta   CleanUp for LangTest Project.
 1.37.1.6 10-21-09 BEKymer  Eliminate indices for secret codes
                            Make code handle all secret codes without special cases
                            
 


 ------------------------------- DESCRIPTION ---------------------------------
*/
 
   /* This file will deal with the menus for all password interaction. */

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include <psos.h>                     /* for access to pSOS routines          */
#include <prepc.h>
#include "ticks.h"                    /* Defines system tick values           */
#include "menu.h"
#include "kpresmsg.h"
#include "error.h"
#include "param.h"
#include "preset.h"
#include "display.h"
#include "getmsg.h"
#include "selctkey.h"
#include "menupass.h"
#include "qvgamenu.h"
#include "drawscrn.h"
#include "ascii.h"
#include "command.h"

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern CONFIGSETUP   CurrentSetup;

extern UINT32 NackError;
extern UINT32 ErrorResponseMinLimit;
extern UINT32 ErrorResponseMaxLimit;

extern struct Codes SecretCode[];

extern STR LineBuffer[LINESIZE +1];
extern UINT8 PasswdEntryFlag;
extern enum LEVEL AccessLevel;
/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/
#define MAX_PASSWORD_CHAR       6

UINT16 WorkingPasswordFlag;   /* So real flag in CurrentSetup not changed */
                              /* until valid password is entered. */



/*
 ---------------------------- EXTERNAL FUNCTIONS -----------------------------
*/
void UpdateDUPSRAMParamSet(void);
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);


/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/
void VGAPasswordEntry(void)
/****************************************************************************/
/* Description:                                                             */
/*   Provides NACK to SBC when password becomes ON.                         */
/****************************************************************************/
{
      if(WorkingPasswordFlag == TRUE)
      {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_PASSWORD_ENTRY1;
         ErrorResponseMaxLimit = 0;
      }
      else
      {
         CurrentSetup.PassWordFlag = 0;      /* User disabled passwords */
      }
} 

UINT16 PasswordSave(UINT8 ** to)
/****************************************************************************/
/* Description:                                                             */
/*   Saves password in current preset                                       */
/****************************************************************************/
{
   SINT8 PasswordBuffer[MESSAGESIZE];   /* Longer than it needs to be */
   UINT8 MisMatch;
   UINT8 Index;
   UINT16 len = 0;
   
   if(PasswdEntryFlag == 1)
   {

      for (Index=0; Index < NUMBER_OF_CODES; Index++)
      {
        if( strcmp(LineBuffer, SecretCode[Index].Password) == 0 )
         break;
      }
   
      if (Index < NUMBER_OF_CODES)
      {
         SecretCode[Index].func();
         if (SecretCode[Index].ID == NULL) {
            len += AddToBuffer(to, (UINT8)3);
         }
         else {
            len += AddToBuffer(to, (UINT8)4);
            len += AddToBuffer(to, (UINT8)(SecretCode[Index].ID>>8));
            len += AddToBuffer(to, (UINT8)SecretCode[Index].ID);
         }
      }
      else
      {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_PASSWORD_ENTRY2;
         ErrorResponseMaxLimit = 0;
      }
   }
   else if(PasswdEntryFlag == 2)
   {
         AccessLevel = MAINTAINENCE;
         strcpy (PasswordBuffer, LineBuffer);
         CurrentSetup.PassWordFlag = WorkingPasswordFlag;  /* Turn on for real now */
         /* Limit the maintainance password to six Chars */
         if(strlen(PasswordBuffer) > MAX_PASSWORD_CHAR)
            PasswordBuffer[MAX_PASSWORD_CHAR] = NUL;
         strcpy(CurrentSetup.PassWordID,PasswordBuffer); /* Set to new password */

         len += AddToBuffer(to, (UINT8)1);      /* Password accepted */
   }
   else
   {
         if(strlen(LineBuffer) > MAX_PASSWORD_CHAR)
            LineBuffer[MAX_PASSWORD_CHAR] = NUL;
         MisMatch = strcmp(LineBuffer, CurrentSetup.PassWordID);
         if (MisMatch)   /*Dummy password if user forgot the password.*/
            MisMatch = strcmp(LineBuffer, "#MAZN#");

         if (!MisMatch)            /* Password accepted */
         {
            AccessLevel = MAINTAINENCE;
            len += AddToBuffer(to, (UINT8)1);
         }
         else                    /* Tell user password was wrong */
         {
            len += AddToBuffer(to, (UINT8)2);
         }
   }
  return (len);
}            

/****************************************************************************/
/*================================END=======================================*/
/****************************************************************************/