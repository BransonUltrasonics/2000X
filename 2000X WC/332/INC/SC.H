/* $Header:   K:/APPS/PVCS Pro/332new/INC/SC.H_V   1.24   29 Mar 2001 14:40:52   BKymer  $ */
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
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      sc.h


            Written by: Laura Markure 
                  Date: 6/20/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             6/30/96      LAM         Initial
      1             7/30/96      LAM         added function prototypes
      2             8/05/96      LAM         added scfinalcleanup     
      3             8/09/96      LAM         added UpdateSpringRateTable     
      4             8/13/96      LAM         added deflection prototypes     
      5             8/22/96      LAM         added function prototypes
      6             10/03/96     LAM         delete function prototype
      7             12/06/96     LAM         added forcetable offset  
      8             01/07/97     LAM         added function prototype
   1.14             04.23.98     LAM         chged get max & min force to calculate 
                                             max & min force                        
   1.15             05.05.98     LAM         added requestactcal prototype          
   1.16             05.20.98     LAM         added waitforspringrate prototype          
   1.17             06.11.98     LAM         added manualmode prototype                 
   1.18             07.01.98     LAM         added startcalpb prototype                 
   1.19             07.15.98     LAM         added updatemessage prototype                 
   1.20             07.21.98     LAM         moved mode defines to here from sc.c
   1.21             08.01.98     LAM         added prototype to test for stagger time
   1.22             09.07.99     LAM         deleted unused prototypes
   1.23             04-17-00     JLH         deleted SCRestart prototype
   1.24             01-08-01     BEKymer     Added argument to RequestActCal as now
                                              required by the menu structure SUBMENU

 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  


/*
 ------------------------------- DEFINES ---------------------------------------
*/
#define MANUAL 1
#define STARTSWITCHES 2
/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
 
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void SCInit(UINT32);
void ManualSCInit(UINT32);
void SCEnterReady(void);
void RequestActCal(UINT32);
void InitSpringRate(void);
void WaitForSpringRate(void);
void CreateSpringRate(void);
void UpdateMessage(void);
void BuildPVPTable(void);
void GetY2Dist(void);
void InitY2Deflection(void);
void CalDeflection(void);
void VerifyCalib(void);
void UpdateSpringRateTable(void);
void SelectManualSCSequence(void);
void SelectSCSequence(void);
void SCFinalCleanupArg(UINT32);
void SCFinalCleanup(void);
void StartCalPB(void);
void TestCalPB(void);

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/


