/* $Header:   D:/SWLab/VMdb/2000Series/INC/MENU1.H_V   2.16   Jun 18 2004 13:51:40   BKymer  $ */

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

   Filename: menu1.h

   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #     Date      Author   Description
   ==========     ========  =======  ===========
      0                              Initial Version
      1.0         09/19/96  PhilJ    Deleted and added prototypes.
      2.9         07/17/97  PhilJ    Added SetOneLineDataBit prototype
      2.10        07/28/97  PhilJ    Added ClearWeldData prototype
      2.11        06/17/98  BJB      Modified prototype for
                                      DisplayCurrentPreset().
	  2.12        08-16-99  JZ       added SelectWeldSetupMenu2
      2.12.1.1    06/10/03  bWadia   Struct Type "BIT_FLAGS" are defined.
      2.13        01-08-01  BEKymer  Added argument to  GetCurrentWeldData(0) prototype
      2.14        12-08-03  BEKymer  Merged 2.13 & 2.12.1.1 to create
                                      2.14 for Ver9.00b build
      2.15        02-19-04  VSharma  Added PresetNum in BIT_FLAGS struct.
      2.16        06-15-04  BEKymer  Added VelocityAedbit & VelocityAefbit.
                                      This allows velocity reporting on AED
                                      actuators to be independent of whether
                                      reporting is on or off for AEF actuators.
                                                                                 
      
*/
/*
  --------------------------- TYPE DEFINITIONS-----------------------------
*/
typedef struct {
              UINT32 WRbit:1;
              UINT32 Cyclebit:1;
              UINT32 Timebit:1;
              UINT32 PkPwrbit:1;                     
              UINT32 Energybit:1;
              UINT32 VelocityAedbit:1;
              UINT32 VelocityAefbit:1;
              UINT32 WeldAbsbit:1;
              UINT32 Absbit:1;
              UINT32 WeldCollbit:1;
              UINT32 TtlCollbit:1;
              UINT32 AmpAbit:1;
              UINT32 AmpBbit:1;
              UINT32 SetFAbit:1;        //FStartbit
              UINT32 SetFBbit:1;        //FEndbit
              UINT32 SetFEndbit:1;      //FMaxbit
              UINT32 Pressbit:1;
              UINT32 FreqMinbit:1;
              UINT32 FreqMaxbit:1;
              UINT32 FreqStartbit:1;
              UINT32 FreqEndbit:1;
              UINT32 FreqChgbit:1;
              UINT32 CycleTimebit:1;
              UINT32 PresetNum:1;
              } BIT_FLAGS;
/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

void DisplayCurrentPreset( SINT8 TextLine[] );
void FormatScrollingBuffer(UINT16 Index);
void GetCurrentWeldData(UINT32);
void SelectWeldSetupMenu(UINT32);
void ClearRunScreenFlag(void);
void UpdateParam(void);
void SoundBeeper(UINT32);
void SetOneLineDataBit(UINT16 OneLineIndex, UINT8 ActiveFlag);
void ClearWeldData(void);
void SelectWeldSetupMenu2(void);
