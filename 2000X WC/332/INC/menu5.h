/* $Header:   D:/SWLab/VMdb/2000Series/INC/MENU5.H_V   2.22   Oct 22 2007 19:01:00   YGupta  $ */
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

   Filename: menu5.h

   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #     Date            Author     Description
   ==========     ========        ======     ===========
      0                                      Initial Version
      1           4/29/96         PJ         First release
      2           6/28/96         LAM        added missing prototypes
      3           6/30/96         PJ         added CancelColdStart prototype
      2.12       08/04/97         PJ         added IncDigitalPot & DecDigitalPot
      2.13       11/10/97         LAM        added cleardiagflag
      2.14       06/04/98         BJB        Deleted unused prototypes,
                                              added prototypes for
                                              DigitalTuneEntryScreen().
      2.15       06/23/98         LAM        added initscmenu prototype
      2.16       07/02/98         LAM        added initmanualscmenu prototype
      2.17       10/06/00         LAM        added enablewelding prototype
      2.18       01-09-01         BEKYmer    Added argument to calls for menu system
      2.19       04-11-03         BEKymer    Move 2.17.1.0 to tip as 2.19 for build 8.10
      2.20       08-05-03         BEKymer    Merged 2.18 and 2.19 to create 2.20 for 9.00A build
                                             - added  iotestdata function prototype
      2.21       05-17-04         VSharma    Added function prototype UpdateResonanceStr(),
                                             DigitalFreqEntry() & RequestHornScan().
      2.22       10-22-07         NHAhmed    Changes done for LangTest phase 0

      
      

 ------------------------------- DESCRIPTION ---------------------------------
*/ 

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                   
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------
*/

/*
 ---------------------------------- CODE -------------------------------------
*/

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/
void EnableWelding(void);
void InitSCMenus(void);
void InitManualSCMenus(void);
void SetCalDistanceFlag(UINT32);
void ClearCalDistanceFlag(UINT32);
void DryCycleSetup(UINT32);
void DryCycleCleanup(void);
void CancelColdStart(UINT32);
BOOLEAN DigitalPotEntry(void);
void DigitalTuneEntryScreen(void);
void IoTestData(UINT8);
extern void HornScanFunc(UINT32);
void RequestHornScan(UINT32);
BOOLEAN DigitalFreqEntry(void);
void UpdateResonanceStr(void);
