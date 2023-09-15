/* $Header:   D:/SWLab/VMdb/2000Series/App/qvgapreset.c_v   1.29.1.7   09 Sep 2008 20:40:04   nhahmed  $ */
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
---------------------------- MODULE DESCRIPTION ------------------------------

     Module name: Save/Recall Presets

        Filename: QVGAPreset.c

      Written by: JOY MD 
            Date: 06/06/2003 
        Language: "C"

--------------------------------- REVISIONS ----------------------------------

   Revision #      Date          Author      Description
  ==========      ========       ======      ===========
      1.0          04/17/03       JOY        Initial Version
      1.1          06/23/03       JOY        Moved Language strings to "menutext.c".
                                             Added Auto Preset Saving. 
      1.2          07/18/03       JOY        Preset Save Header is updated with Preset Number.
      1.3          08/18/03       JOY        Fill color of 'Recall1_StrProp', 'Recall2_StrProp',
                                             'Recall3_StrProp' made COLOR_BLUE.
      1.4          08/24/03       JOY        Added Alarm Button in preset Screen.
      1.5          09/22/03       JOY        VFD Error Beeps are added.
                                             '*' is displayed, if preset has been changed.
      1.6          10/14/03       JOY        CkQsend() is replaced by the q_send().
      1.7          10/16/03       JOY        MiddleSeg. is erased by QVGA ROM image.
      1.8          10/23/03       JOY        Added Button Release Beep.
      1.9          12-09-03       BEKymer    Add arguments as now required by
                                              SUBMENU and TEXt structures
      1.10         02-02-04       VSharma    Update the DUPS parameters from compressed preset
                                             in QVGARecallPreset().
      1.12         02-20-04       VSharma    Changed DrawPresetMiddleSeg() to display preset 
                                             Inforamtion. Added 'Verify' button in Preset Screen.
      1.13         03-03-04       VSharma    Added 'SaveSpecialPreset()'.
      1.15         04-06-04       VSharma    Changed extern of PresetEnableFlags. 
      1.16         05-17-04       VSharma    Removed extern of unused strings.
                                             Modified SavePreset functions.
      1.17         06-04-04       VSharma    Removed ClearHistoryInBbram() from QVGARecallPreset().
      1.18         08-03-04       JOY        The flag 'IsRecalledPreset' made FALSE in SavSpecialPreset().
      1.19         09-14-04       JOY        Set flag 'ResetRecall_UpdateFlag' in QVGARecallPreset().
      1.20         07-25-05       Bwadia     QVAG clean up and VGA preset implementation for 
                                             Ver10.0e
      1.21         10-28-05       Bwadia     VGA sequencing feature added                                       
      1.22         02-07-06       Bwadia     Dummy check in
      1.23         02-22-06       Bwadia     Insert, Replace and delete button on 
                                             Sequencing menu rearranged. Modified
                                             for tracker issue 4078 
      1.24         02-07-07       NHAhmed    Changed display format of date for Asian languages(yyyy/mm/dd).
      1.25         02-07-07       NHAhmed    Check-in after code review.
      1.26         04-16-07       NHAhmed    Added LimitChanged to ProcessVGAPresetRecall().
      1.27         04-18-07       NHAhmed    Password protection of Preset Sequencing.
      1.28         04-19-07       NHAhmed    Removed LimitChanged to ProcessVGAPresetRecall().
      1.29         04-27-07       YGupta     Added LimitChanged to ProcessVGAPresetRecall() function to handle the
                                             condition when user is recalling the same preset with limits changed.
      1.30         10-22-07       NHAhmed    Changes done for LangTest phase 0
      1.31         01-11-07       NHAhmed    Added new function EraseSeqList() and some functions were replicated
                                             to a non argument type ones.
      1.32         04-14-08       NHAhmed    Renamed some functions and added a function EraseSeqList1().
      1.33         06-06-08       NHAhmed    Removed some defines that are not in use.
      1.34         08-01-08       NHAhmed    Modified functions PreparePrstInfoString(), ProcessPresetRecall(),
                                             SaveNamedPreset().
      1.35         09-02-08       NHAhmed    CleanUp for multi-language support.
      1.36         09-04-08       YGupta     CleanUp for LangTest Project.
      1.37         09-09-08       NHAhmed    CleanUp for multi-language support.
*/

/*
 -------------------------------- DESCRIPTION --------------------------------
*/


/*
 ------------------------------ INCLUDE FILES --------------------------------
*/
#include <prepc.h>
#include "qvgamenu.h"
#include "DrawScrn.h"
#include "touchmsg_qvga.h"
#include "ck_qsend.h"
#include "menu3.h"
#include "preset.h"
#include "param.h"
#include "dups_api.h"
#include "ready.h"
#include "alarms.h"
#include "statedrv.h"
#include "state.h"
#include "selctkey.h"
#include "ipsatype.h"
#include "beep.h"
#include "fmtstrs.h"
#include "command.h"

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
#define CENTURY         2000

/*
 ------------------------------- GLOBAL DATA ---------------------------------
*/
/*                       (scope is global to ALL files)                     */

CONFIRM_SCREEN_TYPE ConfirmType;
UINT32 QVGASavePresetOption=0;
BOOLEAN QVGAPresetSaveAborted = FALSE;
UINT16 VGAPresetNum;
UINT16 TempSequenceNos; 


/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern STR *PresetName[];
extern STR *PresetBuffer[];

extern STR Preset1EngName[QVGA_LINESIZE];
extern STR Preset2EngName[QVGA_LINESIZE];
extern STR Preset3EngName[QVGA_LINESIZE];
extern STR Preset4EngName[QVGA_LINESIZE];
extern STR Preset5EngName[QVGA_LINESIZE];
extern STR Preset6EngName[QVGA_LINESIZE];
extern STR Preset7EngName[QVGA_LINESIZE];
extern STR Preset8EngName[QVGA_LINESIZE];
extern STR Preset9EngName[QVGA_LINESIZE];
extern STR Preset10EngName[QVGA_LINESIZE];
extern STR Preset11EngName[QVGA_LINESIZE];
extern STR Preset12EngName[QVGA_LINESIZE];
extern STR Preset13EngName[QVGA_LINESIZE];     
extern STR Preset14EngName[QVGA_LINESIZE];
extern STR Preset15EngName[QVGA_LINESIZE];
extern STR Preset16EngName[QVGA_LINESIZE];


extern SINT32 InfoMonth;
extern SINT32 InfoDay;
extern SINT32 InfoYear;
extern SINT32 InfoHour;
extern SINT32 InfoMinute;
extern SINT32 InfoCount;
extern UINT32 PresetAddress[];
extern UINT16 LangIndex;
extern UINT8 ActivePreset;
extern UINT16  PresetNeedsToBeUpdated;
extern enum WELDSTATES WeldState;
extern BOOLEAN IsThereDataPrinting;
extern BOOLEAN IsGraphDrawing;
extern BOOLEAN IsAlarmActive;
extern BOOLEAN IsRecalledPreset;
extern SETUPS_Ver800 CurrentPreset;
extern CONFIGSETUP CurrentSetup;
extern UINT8 UpdateRunningPreset;
extern WELD_DATA_MSG   WeldHistoryMsg;
extern UINT32 SysmQueueId;
extern UINT16 PresetEnableFlags[TOTAL_PRESETS];
extern SINT8 AssignNamePresetBuffer[MESSAGESIZE];
extern UINT16  OldSameNameAvailable;              /* TRUE: writing to existing preset */
extern UINT16  NewSameNameAvailable;              /* FALSE: writing to clear preset   */

extern BUTTON_STATE TouchedButtonState;
extern REDRAW_SEG  RedrawSeg;
extern QVGA_MENU_INFO MenuLevelInfo[];
extern BOOLEAN ResetRecall_UpdateFlag;
extern UINT8  LimitChanged;

extern UINT32 NackError, ErrorResponseMinLimit, ErrorResponseMaxLimit;
extern UINT16 GlobalCommandID;
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/
UINT8 ReadOnlyFlag = FALSE;     /* Presets updating Running Preset in nvmanger */
STR InfoLine3[QVGA_LINESIZE];      /* Verified line      */
STR InfoLine4[QVGA_LINESIZE];      /* Date line         */
STR InfoLine5[QVGA_LINESIZE];      /* Time */
STR InfoLine6[QVGA_LINESIZE];      /* Cycle Run      */

/* Pointer to the Preset names */
const STR *PresetNameArray1[] = {
                                 Preset1EngName,
                                 Preset2EngName,
                                 Preset3EngName,
                                 Preset4EngName,
                                 Preset5EngName,
                                 Preset6EngName,
                                 Preset7EngName,
                                 Preset8EngName,
                                 Preset9EngName,
                                 Preset10EngName,
                                 Preset11EngName,
                                 Preset12EngName,
                                 Preset13EngName,
                                 Preset14EngName,
                                 Preset15EngName,
                                 Preset16EngName
                                };
/*
 --------------------------- EXTERNAL FUNCTION PROTOTYPES --------------------
*/
SINT16 SPrintf(SINT8* pc_buf, const SINT8* pc_format,...);
UINT16 CheckForDups(void);
SINT8 * Trim_FillChar(SINT8 Str_temp[]);
extern void LastDatePresetWasSaved(void);
BOOLEAN QVGAAlphaEntry( const void *active, UINT8 type );
void DrawAlarmButton(void);
void SaveDUPSParameters(UINT16 ActivePreset);
void RefreshDUPSParam (PRESET_COMPRESSED* CompPreset);
void UpdateDUPSRAMParamSet(void);
void Numout1(UINT32 Value, UINT16 Base, STR LC, UINT8 Width, STR *StrAdr);
void UseSameNamePreset(UINT32 Cond);
BOOLEAN RecallAndVerifyPreset (UINT32 PresetNum);
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);
UINT16 AddToBufferString(UINT8 * * to, SINT8 * string, UINT16 length);
UINT16 LangStrLen(SINT8 * str); 
BOOLEAN LangCheckNull(SINT8 * Line);
void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void StrCatTwoBytes(SINT8 * to, SINT8 * from);
void FormatDateStr1( SINT8 String[], SINT8 Delimiter1, UINT8 NumDisplayChar1,
                    SINT32 Month, SINT8 Delimiter2, UINT8 NumDisplayChar2,
                    SINT32 Day, SINT8 Delimiter3, UINT8 NumDisplayChar3,
                    SINT32 Year );
void FormatTimeStr1( SINT8 String[], SINT8 Delimiter1, UINT8 NumDisplayChar1,
                    SINT32 Hour, SINT8 Delimiter2, UINT8 NumDisplayChar2,
                    SINT32 Minute );


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -----------------------
*/
void GetPresetNum (void);

/*
 ---------------------------------- CODE -------------------------------------
*/

void GetPresetNum (void)
/*****************************************************************************/
/*Description:                                                               */
/*   This function gets current preset number                                */
/*****************************************************************************/
{
   VGAPresetNum = (UINT8)CurrentSetup.ActivePreset;
}
void GetSequenceNos (void)
/*****************************************************************************/
/*Description:                                                               */
/*   This function gets current sequence number                              */
/*****************************************************************************/
{
   if (CurrentSetup.SequenceEnable == FALSE || 
       CurrentSetup.SequenceCount == 0 )
      TempSequenceNos = 0;
   else
      TempSequenceNos = CurrentSetup.SequenceNos + 1;   
}

void PreparePrstInfoString (void)                                     
/*****************************************************************************/
/*Description:                                                               */
/*   This function prepares the information strings to display in the        */
/*   Information box in Save/Recall Preset screen.                           */
/*****************************************************************************/
{
   UINT16 SelectedPresetNum;
   PRESET_COMPRESSED *PresetPtr, *CurrentPresetPtr;
   UINT16 Length1, Length2, i;
   SINT8 DisplayStr[QVGA_LINESIZE];
   
   SelectedPresetNum = VGAPresetNum;
   CurrentPresetPtr = (PRESET_COMPRESSED *) PresetAddress[0];  /* Current preset in case needed */
   
   PresetPtr = (PRESET_COMPRESSED *) PresetAddress[SelectedPresetNum]; /* Preset of interest */
   
   InfoMonth = 0;   /* Clear stuff in case preset is cleared */
   InfoDay = 0; 
   InfoYear = 0; 
   InfoHour = 0;                                                    
   InfoMinute = 0;
   InfoCount = 0;

   /* Prepare Date line   */
   InfoMonth = (SINT32) PresetPtr->Month; 
   InfoDay = (SINT32) PresetPtr->Day; 
   InfoYear = (SINT32) PresetPtr->Year; 
   
   for(i = 0; (i < QVGA_LINESIZE - 2); i++)
         DisplayStr[i] = FILLCHAR;
  
    if (CurrentSetup.Units == FALSE)
      /*Display Time in MM/DD/YY format*/
      FormatDateStr1(DisplayStr,0, 2, InfoMonth,
                       '/', 2, InfoDay,
                       '/', 2, InfoYear);
   else
      /*Display Time in the DD/MM/YY format.*/
      FormatDateStr1(DisplayStr,0, 2, InfoDay,
                       '/', 2, InfoMonth,
                       '/', 2, InfoYear);
                                     
   strcpy(InfoLine4,Trim_FillChar(DisplayStr) );
      
         
   /* Prepare Time line   */
   InfoHour = (SINT32) PresetPtr->Hour;                                                    
   InfoMinute = (SINT32) PresetPtr->Minute;
   
   for(i = 0; (i < QVGA_LINESIZE - 2); i++)
         DisplayStr[i] = FILLCHAR;
       

   FormatTimeStr1(DisplayStr, 0, 2, InfoHour,':', 2, InfoMinute);
   strcpy(InfoLine5,Trim_FillChar(DisplayStr) );
   /* Prepare cycle count */
   if ((CurrentSetup.ActivePreset == (UINT8)SelectedPresetNum) 
        && (CurrentPreset.PresetUpdateComplete == TRUE))
      InfoCount = CurrentPresetPtr->WeldCount;  /* Preset asked for is current preset so */   
   else                                         /* include cycles run since recalled     */
      InfoCount = PresetPtr->WeldCount; 
  
   SPrintf (DisplayStr, "%d", InfoCount );                                                   
   strcpy(InfoLine6, DisplayStr);
         
   /* Prepare 'Verified'  */
   if (PresetPtr->Verified) 
      strcpy(InfoLine3, "1");    /*Yes*/
   else 
      strcpy(InfoLine3, "0");     /*No*/
}

void SetPresetClearFlags (void)
/****************************************************************************/
/*Description:                                                              */
/* Clears VGA preset clear flags                                            */
/****************************************************************************/
{
   if(PresetEnableFlags[VGAPresetNum])
   {
       NackError = WELDER_PROCESS_ERROR;
       ErrorResponseMinLimit = SHOW_MSG_SCREEN;
       ErrorResponseMaxLimit = 0;
   }
     
}

/****************************************************************************/
/*Description:                                                              */
/* Rearranges sequence list when a preset is deleted                        */
/* Input - preset nos                                                       */
/****************************************************************************/

void RearrangeSeqList(UINT16 PresetNos)
{
   UINT8 TempSeqList[MAX_SEQUENCE_NOS];
   UINT16 i; 
   UINT8 j = 0;
   
   for(i = 0; i < CurrentSetup.SequenceCount; i++)
   {
      if(CurrentSetup.SequenceList[i] != (UINT8)PresetNos)
         TempSeqList[j++] = CurrentSetup.SequenceList[i];
   }

   CurrentSetup.SequenceCount = j;
   for(i = 0; i < CurrentSetup.SequenceCount; i++)
      CurrentSetup.SequenceList[i] = TempSeqList[i];
   if (CurrentSetup.SequenceNos >= CurrentSetup.SequenceCount)   
      CurrentSetup.SequenceNos = 0;
      
   
}
void ProcessPresetClear(void)
/****************************************************************************/
/*Description:                                                              */
/* Clears selected preset                                                   */
/****************************************************************************/
{
   SINT8 TempStr[10];
   SPrintf(TempStr, "%2d", (VGAPresetNum));
   strcpy(PresetNameArray1[VGAPresetNum-1], TempStr);
   PresetEnableFlags[VGAPresetNum] = FALSE;
   PresetClear(VGAPresetNum);
   GetPresetNames(); 
   RearrangeSeqList(VGAPresetNum);
    
}

void ProcessPresetRecall (void)
/****************************************************************************/
/*Description:                                                              */
/* Sets selected Preset parameters to the Welder.                           */
/*NOTE: Preset is Recalled only if Welder is either Ready or Pre-ready state*/
/*      and No Graph/Data Printing is going on..                            */
/****************************************************************************/
{
   UINT16 DUPS_paramsetno = DUPS_SUCCESS;

   if(PresetEnableFlags[VGAPresetNum])
   {
      if ( ( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
        &&(IsThereDataPrinting == FALSE) && (IsGraphDrawing == FALSE))
      {  // Ok to recall preset since no weld in progress
         StopStateMachine();

         if(CurrentPreset.PresetUpdateComplete == TRUE)
            WritePreset(CurrentSetup.ActivePreset);   /* Save Current Preset   */
      
         // Now if the user makes any changes and doesn't want to save the changes, he can do a recall preset 
         // which will discard the changes he made and will restore the original values. 

         // If there is a DUPS then    
         // Find the associated DUPS param set number and do an upload Parameter set.
         if (CheckForDups())
         {
            if( (DUPS_paramsetno = DUPS_FindDUPS4COP(VGAPresetNum)) == DUPS_PARAMSETUNDEF)
            {  //no associated Parameter set means invalid preset
               RecordSetupAlarm(SE268);
               RecordErrorCode( ERRORCODE9_SE268 );
               ResetStateMachine(); /* We must restart the state machine even if an error */
               StartStateMachine();
            }  // fatal error, invalid preset since there is no associated DUPS Parameter Set
            else  // get the associated DUPS Parameter Set
            {
               //DUPS_QueuedUploadPS(DUPS_paramsetno);
               //DUPS_QueuedDownloadPS();
               DUPS_SelectParamSetNum(DUPS_paramsetno);
               RefreshDUPSParam ((PRESET_COMPRESSED *) PresetAddress[VGAPresetNum]);
            }  // end of else -- get the associated DUPS Parameter Set
         }  // end of if (CheckDups())

        if (DUPS_paramsetno != DUPS_PARAMSETUNDEF)
        {  // if there was an associated Parameter set or if this is an analog power supply
           CurrentSetup.ActivePreset = VGAPresetNum;        
           UpdateRunningPreset = TRUE;
           ReadPreset(CurrentSetup.ActivePreset, FALSE);
           WritePreset(0);                           /* Update Running Preset */
           UpdateCurrentPreset(ACTIVEPRESET, 0, 0);
//         FinalResults.CycleCount = CurrentPreset.WeldCount;
           ResetStateMachine();
           StartStateMachine();
           ResetRecall_UpdateFlag = TRUE;
           LimitChanged = TRUE;
           /*Go Back to the Run Result Screen*/

        }  // if there was an associated Parameter set or if this is an analog power supply
     } // end of -- Ok to recall preset since no weld in progress
     else  // can't recall preset right now because weld in progress
     {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_WELDINGON_MESSAGE;
         ErrorResponseMaxLimit = 0;
     }  // else can't recall preset right now because weld in progress
   }
}  // end of RecallPreset( UINT16 PresetNum )

UINT16 ProcessPresetVerify(UINT8 ** to)
/*****************************************************************************/
/*Description:                                                               */
/*   This function verify the preset in Ready or Pre-Ready state and display */
/*   the respective results for two seconds. Else this will display an error */
/*   message to wait for ready state.                                        */  
/*****************************************************************************/
{
   UINT16 len = 0;
   if ( ( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
        &&(IsThereDataPrinting == FALSE) && (IsGraphDrawing == FALSE))
   {
       if(RecallAndVerifyPreset(VGAPresetNum))
       {
          if(CurrentPreset.Verified)
             len += AddToBuffer(to, 1);
          else
             len += AddToBuffer(to, 0);
       }
   } 
   else 
      len += AddToBuffer(to, 2);
   return (len);
}

void PreparePrstSaveTitle (void)
/****************************************************************************/
/*Description:                                                              */
/* Sets Save Preset title                                                   */
/****************************************************************************/
{
   ActivatePreset (VGAPresetNum);
}

static void ChangePresetName(void)
/****************************************************************************/
/*Description:                                                              */
/* Save the Welder setting Automatically generated and manual Preset name   */
/****************************************************************************/
{
   UINT16 DUPS_Ascval = DUPS_SUCCESS;
   PRESET_COMPRESSED *PresetPtr;
   
   if(CheckForDups())
   {
      DUPS_Ascval = DUPS_FindDUPS4COP(VGAPresetNum);
      if(DUPS_Ascval == DUPS_PARAMSETUNDEF)
      DUPS_Ascval = DUPS_SetDUPSParamSet(VGAPresetNum);
      if(DUPS_Ascval!= DUPS_PARAMSETUNDEF)
      {
         UpdateDUPSRAMParamSet();
         DUPS_CurrPSStatus = DUPS_PENDING;
         DUPS_DownloadParamSet(DUPS_Ascval);
         DUPS_Wait4CurrPS();
         DUPS_SelectParamSetNum(DUPS_Ascval);
         DUPS_Wait4CurrPS();

      }  // Download DupsCurrPS
   }  // if(CheckForDups)    
       
   if(DUPS_Ascval != DUPS_PARAMSETUNDEF)
   {     
      if(CurrentPreset.PresetUpdateComplete == TRUE)
         WritePreset(CurrentSetup.ActivePreset);   /* Save Current Preset   */
             
      if(QVGASavePresetOption == NAME_MODE)
         AutoNamePreset();
      else if ((QVGASavePresetOption == NAME_NEW)||
               (QVGASavePresetOption == NAME_CURRENT))
         UseSameNamePreset(QVGASavePresetOption);
      else
         strcpy(CurrentPreset.PresetID, AssignNamePresetBuffer);
   
      LastDatePresetWasSaved();
      WritePreset(VGAPresetNum);                  /* Save Active Preset */
      CurrentSetup.ActivePreset = (UINT8)VGAPresetNum;
      SaveDUPSParameters(VGAPresetNum);
      UpdateCurrentPreset(ACTIVEPRESET, 0, 0);
      WritePreset(0);                             /* Save Preset Zero */
      PresetNeedsToBeUpdated = TRUE;              /* need to verify the preset */

     // strcpy(PresetBuffer[0], CurrentPreset.PresetID);

      PresetEnableFlags[VGAPresetNum] = TRUE;

      PresetPtr = (PRESET_COMPRESSED *) PresetAddress[VGAPresetNum];
      if ((QVGASavePresetOption == NAME_NEW)||
          (QVGASavePresetOption == NAME_CURRENT)||
          (QVGASavePresetOption == NAME_MODE))
         strcpy(PresetPtr->PresetID, CurrentPreset.PresetID);
      else
         strcpy(PresetPtr->PresetID,  AssignNamePresetBuffer);
      GetPresetNames();          /* Update all language structures with new name */
   }  // else DUPS Paramset was available
}//End of Function.

void SaveNamedPreset(void)
/****************************************************************************/
/*Description:                                                              */
/* Saves the Currently available Welder parameters in manually generated    */
/* generated Preset name.                                                   */
/****************************************************************************/
{   
   BOOLEAN IsConfirmRqd = FALSE;
   QVGAPresetSaveAborted = FALSE;
   switch(GlobalCommandID){
   case AUTO_NAME:
      QVGASavePresetOption = NAME_MODE;
      break;
   case SAME_NAMEAS_OLD:
      QVGASavePresetOption = NAME_CURRENT;
      break;
   case SAME_NAMEAS_NEW:
      QVGASavePresetOption = NAME_NEW;
      break;
   case ASSIGN_NAME:
      QVGASavePresetOption = 0;
      break;
   }
   // Ok to save preset since no weld in progress and there is a DUPS
   if(CheckForDups() == TRUE)
   {
      if( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
         StopStateMachine();
      else
      {
         QVGAPresetSaveAborted = TRUE;
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_WELDINGON_MESSAGE;
         ErrorResponseMaxLimit = 0; // for sending Welding on process

      } // else can't recall preset right now because weld in progress
   }
   
   if( QVGAPresetSaveAborted == FALSE)
   {
      if(IsPresetEnabled((UINT8)VGAPresetNum))
      {
         IsConfirmRqd = TRUE;
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_MSG_SCREEN;
         ErrorResponseMaxLimit = 0; 

      }
      else //Confirmation is TRUE
      {         
         ChangePresetName();         
      }  
      
   }  // end of QVGAPresetSaveAborted == FALSE
   if(CheckForDups() == TRUE && !IsConfirmRqd)
   {
      if( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) {
         ClearAbort();
         ResetStateMachine();
         StartStateMachine();
      }
   } 
}  // end of VGASaveAutoNamedPreset(void)

void PresetSaveOk(void)
/*****************************************************************************/
/*Description:                                                               */
/* If confirmation is OK save the Preset && make it active Preset.           */
/*****************************************************************************/
{
  ChangePresetName();
  ReadOnlyFlag = FALSE;
  if(CheckForDups() == TRUE)
   {
      if( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) {
         ClearAbort();
         ResetStateMachine();
         StartStateMachine();
      }
   }
}

void PresetSaveCancel(void)
/*****************************************************************************/
/*Description:                                                               */
/* If confirmation is Cancel then don't save the preset & bring PRESET_SCREEN*/
/*****************************************************************************/
{
  ReadOnlyFlag = FALSE;
  if(CheckForDups() == TRUE)
   {
      if( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) {
         ClearAbort();
         ResetStateMachine();
         StartStateMachine();
      }
   }
}

void SaveSpecialPreset (UINT32 SaveCond)
/****************************************************************************/
/*Description:                                                              */
/* Saves the Currently available Welder parameters with the name of the     */
/* CurrentPreset.PresetID.                                                  */
/****************************************************************************/
{
   UINT16 DUPS_Ascval = DUPS_SUCCESS;
   PRESET_COMPRESSED *PresetPtr;
      
   if (CheckForDups())
   {
      DUPS_Ascval = DUPS_FindDUPS4COP(ActivePreset);
      if (DUPS_Ascval == DUPS_PARAMSETUNDEF)
         DUPS_Ascval = DUPS_SetDUPSParamSet(ActivePreset);
      if (DUPS_Ascval!= DUPS_PARAMSETUNDEF)
      {         
         UpdateDUPSRAMParamSet();
         DUPS_CurrPSStatus = DUPS_PENDING;
         DUPS_DownloadParamSet(DUPS_Ascval);
         DUPS_Wait4CurrPS();
         DUPS_SelectParamSetNum(DUPS_Ascval);
         DUPS_Wait4CurrPS();
         IsRecalledPreset = FALSE; /*DUPS & RAM Param list are same.*/                  
      }  // Download DupsCurrPS
   }  // if(CheckForDups)    
       
   if (DUPS_Ascval == DUPS_PARAMSETUNDEF)
   {
   }
    else
    {
       UseSameNamePreset(SaveCond);  /*Save name as CURRENT_NAME*/
       LastDatePresetWasSaved();
       WritePreset(ActivePreset);           /* Save Active Preset */       
       SaveDUPSParameters(ActivePreset);
       UpdateCurrentPreset(ACTIVEPRESET, 0, 0);
       WritePreset(0);                      /* Save Preset Zero */
       PresetNeedsToBeUpdated = TRUE;        /* need to verify the preset */
       strcpy(PresetBuffer[LangIndex], CurrentPreset.PresetID);
       PresetEnableFlags[ActivePreset] = TRUE;
       PresetPtr = (PRESET_COMPRESSED *)PresetAddress[ActivePreset];
       strcpy(PresetPtr->PresetID, PresetBuffer[LangIndex]);
       GetPresetNames();          /* Update all language structures with new name */
   }

}

void EraseSeqList (void)
{
   CurrentSetup.SequenceNos = 0;
   CurrentSetup.SequenceCount = 0;
}

void EraseSeqList1 (void)
{
   if(CurrentSetup.SequenceCount != 0)
   {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = SHOW_MSG_SCREEN;
      ErrorResponseMaxLimit = 0; 
   }
}
