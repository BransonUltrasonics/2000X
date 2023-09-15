/* $Header:   D:/SWLab/VMdb/2000Series/INC/iotest332.h-arc   1.5   Oct 22 2007 19:00:56   YGupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*   Copyright (c) Branson Ultrasonics Corporation, 2002                    */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/*                                                                          */
/*   Module name:   On board Diagnostics                                    */
/*                                                                          */
/*   Filename:      iotest332.h                                             */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*   Revision #  Date      Author   Description                             */
/*   ==========  ========  ======   ===========                             */
/*      1.0      10-04-02  BEKymer  Original Release                        */
/*      1.2      01-14-03  DJL      Added Read8 function prototype          */
/*      1.3      09-17-03  BEKymer  Add prototype for ShutOffFT() and       */
/*                                   RestoreUserIO()                        */
/*      1.4      03-26-04  BEKymer  Add prototypes for all new functions    */
/*      1.5      10-22-07  NHAhmed  Changes done for LangTest phase 0       */
/*                                                                          */

/*----------------------------- DESCRIPTION --------------------------------*/




/*---------------------------- INCLUDE FILES -------------------------------*/  



/*------------------------- Function Prototypes ----------------------------*/  

void DiagnosticInput(UINT8 ByteReceived);
void DiagnosticsCmd(void);
void Read32(void);                   
void Read16(void);
void Read8(void);
void MyReadNVR(void);
void EraseNVR(void);
void TestBattRam(void);
void TurnOnBeep(void);
void TurnOffBeep(void);
void WritePrinterData(void);
void WritePrinterControl(void);
void WriteBargraph(void);
void WritePortA(void);
void WritePortB(void);
void WritePortC(void);
void ReadPortA(void);
void ReadPortB(void);
void ReadPortC(void);
void ReadKeypad(void);
void DiagFreqOffset(void);
void DiagAmplitude(void);
void DiagDigPot(void);
void EraseVFScreen(void);
void WriteLeds(void);
void ReadTPU(void);
void WriteTPU(void);
void DiagReady(void);
void ShutOffFT(void);
void RestoreUserIO(void);
void RestoreUserIO(void);
void DisableBeepers(void);
void EnableBeepers(void);
void SetTime(void);
void SetDate(void);
void DumpCalibrationData(void);
void DumpAllCalibrationData(void);
void ReadMemory(void);
void WriteMemory(void);
void StartDUPS(void);
void CheckDUPS(void);
UINT32 Numin(UINT16, STR Bufferpointer[]);
void CheckIOTest(void);
void DisplayHelp(void);



/*-------------------------------- DEFINES ---------------------------------*/


