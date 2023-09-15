/* $Header:   D:/SWLab/VMdb/2000Series/App/POWRDWN.C_V   1.24   Aug 02 2004 09:14:32   BWadia  $ */
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
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: powrdwn.c

 ----------------------------- REVISIONS ------------------------------------

   Revision #     Date        Author             Description
   ----------     -------     ------             -----------
   0              02-04-97    PaulG              Initial
   1.00           02-10-97    PaulG              Add Flags SetupDone and PresetDone.
   2.00           04-16-97    LAM                call update preset & setup directly
   2.10           04-16-97    PhilJ              Set PresetUpdateComplete.
   3.1.3          07-10-97    LAM                chged saving of currentsetup
   4.1.4          07.20.97    LAM                fixed sizeof currentsetup
   4.1.9          07.28.97    PhilJ              Eliminated GetPointer
   1.10           08.29.97    LAM                fixed power down     
   1.11           09.02.97    LAM                cleanup power down     
   1.12           11-07-97    PaulG              Reset a printer flag InitPrinterOnceOnPowerup.      
   1.13           11-18-97    LAM                deleted prepc.h                                     
   1.14           08-16-99    LAM                set PV to 0                                     
   1.15           07-12-00    BEKymer            Changed SETUPS to SETUPS_Ver800
   1.16           07-18-00    BEKymer            Fix bug, need to pass BBR800_CONFIG_START in call
                                                  to BattramAccess()
                                                 Save contents of BUCMenuRAM into BBR
   1.17           08-08-00    BEKymer            Save dups related stuff at power down
   1.18           08-23-00    BEkymer            Included string.h for memcpy prototype
   1.19           08-28-00    BEKymer            Directly save preset0 instead of going through pSOS
                                                  Also save it first instead of last
   1.20           08-29-00    AT                 Removed some unneeded declarations, added sizeof()
   1.21           10-18-00    BEKymer            Added 2nd arg to SaveCompressedPreset call
                                                  to fix issue # 3387
   1.22           11-17-00    BEKymer            During power down only save the weld count
                                                  from the current preset.  Everything else
                                                  has already been saved some time before.
   1.23           12-13-00    BEKymer            Release power relay in PrePowerDown function.  This 
                                                  removes the delay between pressing the button and
                                                  power actually being removed.
   1.24           07-28-04    JOY                Turn OFF sonics & solenoid valve at power down.


 ---------------------------- DESCRIPTION ----------------------------------**/
#include <psos.h>                          /* for access to pSOS routines    */
#include "preset.h"
#include "battram.h"
#include "powrdwn.h"
#include "mansensr.h"
#include "dups_api.h"
#include "string.h"
#include "digout.h"



/**-------------------------EXTERNAL DATA------------------------------------**/

extern SETUPS_Ver800  CurrentPreset;
extern CONFIGSETUP    CurrentSetup;
extern BOOLEAN        PDownDelay;
extern UINT16         InitPrinterOnceOnPowerup;
extern BUCMENU_800    BUCMenuRAM, *BUCMenuBBR;

/**-------------------------LOCAL GLOBAL DATA--------------------------------**/


void PrePowerDown(void)
/*-----------------------------------------------*/
/* This function saves all necessary information */
/* before physically shutting off the system     */
/*-----------------------------------------------*/
{
   UINT32 BattramStatus;
   PRESET_COMPRESSED* CompressPreset;

/* Put the proportional valve into a safe mode before power is lost */
   SetPV(SHUT_DOWN_VALUE, FORCE_CALIBRATION);

/* First save the weld counter in the current preset */
   CompressPreset = (PRESET_COMPRESSED*) PRESET_0_START;
   CompressPreset->WeldCount = CurrentPreset.WeldCount;

/* Store CurrentSetup Parameter Change from DRAM to BATTRAM */
   BattramStatus = BattramAccess(BBR_WRITE, CONFIG_SECTION,(UINT8 *)&CurrentSetup, BBR800_CONFIG_START, sizeof(CurrentSetup));

/* Save the BUCMENU stuff into BATTRAM now */
   memcpy(BUCMenuBBR, &BUCMenuRAM, sizeof(BUCMENU_800) );

/* Save all the DUPS related stuff into BATTRAM */
   memcpy((UINT8*)BBR800_DUPS2COP_START, DUPS2COP, sizeof(DUPS2COP));
   memcpy((UINT8*)BBR800_COP2DUPS_START, COP2DUPS, sizeof(COP2DUPS));
   memcpy((UINT16*)BBR800_DUPSLOCK_START, DUPS_Lock, sizeof(DUPS_Lock));
   

   PDownDelay = TRUE;
   SVOff();                           /* Release SV, send horn home   */
   PSIdle();                          /* Turn off the sonics          */

/* TRUE: This will reset printer flags when */
/* the system is powered up the next time.  */
 
   InitPrinterOnceOnPowerup = TRUE;

   PowerDownSystem();  /* Release the power relay here */
      while(TRUE);  /* Wait here pretty much forever, after all someone did power down, right? */

} /* PrePowerDown */
