/* $Header:   D:/SWLab/VMdb/2000Series/INC/UTIL.H_V   2.27   20 Oct 2009 13:55:34   bkymer  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Util                                                        */
/*                                                                          */
/* Filename:    Util.h                                                      */
/*                                                                          */
/* Function Name: Function prototypes for util.c                            */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   06-28-95                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date       Author       Description                          */
/*  =========  =========  ===========  ===========                          */
/*     0       03-22-96   BEKymer      Convert to run under pSOS            */
/*     1       06-27-96   BEKymer      Added prototype for GetPowerSupply.. */
/*     2       09-23-96   PAULG        Added functions InchToMm and         */
/*                                     PoundToNewton for conversion from    */
/*                                     USCS to Metric.                      */
/*     3       10-29-96   BEKymer      Add prototype for Get...Frequency    */
/*     4       04-25-97   LAM          added prototype myatoi               */
/*     5       05-02-97   PhilJ        added ReadOneMiltimer and Timedelay  */
/*                                     prototypes                           */
/*     6       05-02-97   PhilJ        deleted Rev.5 change                 */
/*     2.8     07-03-97   PhilJ        Added PowerSupply Info functions     */
/*     2.9     07-08-97   PhilJ        Modified PowerSupply Info functions  */
/*     2.10    07-10-98   BJB          No parameter to GetActuatorInfo()    */
/*     2.11    07-15-98   BEKymer      Add prototype for GetMaxStrokeLength */
/*     2.12    07-30-98   BJB          Deleted prototype GetActuatorInfo(). */
/*     2.13    12-11-98   BJB          Changed "new" in strsub() to "newstr"*/
/*                                      since "new" is a reserved word in   */
/*                                      C++.                                */
/*     2.14    06-03-99   JHenry       Added GetMinStrokeLength for menuhorn*/
/*     2.15    06-10-99   JHenry       Deleted GetMinStrokeLength prototype */
/*                                      as required by Horndown code review.*/
/*     2.16    08-23-99   JZ           added UpdatePressureOffset,          */
/*                                     UpdateDistanceOffset                 */
/*     2.17    09-09-99   JZ           added CheckPressure                  */  
/*     2.18    11-30-99   BEKymer      Added ClearPressureArray() prototype */
/*     2.19    08-24-00   BEKymer      Added prototype for MoveToCurrentPreset*/
/*     2.20    08-10-01   BEKymer      Add prototype for RemoveExtraSpaces  */
/*     2.21    04-03-02   BEKymer      Add prototype for Numout             */
/*     2.22    04-03-02   BEKymer      Change argument for Numout           */
/*     2.23    04-05-02   LAM          Add prototype for AtLeastVersion806  */
/*     2.24    04-24-02   BEKymer      Add prototype for ConfigureAef and   */
/*                                      ConfigureAed                        */
/*                                                                          */
/*                                                                          */
/*     2.25    10-22-07   NHAhmed      Changes done for LangTest phase 0    */
/*     2.26    ?                                                            */
/*     2.27    10-16-09   BEKymer      Change protype for                   */
/*                                      ConfigureActuatorBoard()            */


/*----------------------------- DESCRIPTION --------------------------------*/

/* This module contains the function prototypes for utl.c.                  */


#include "stddef.h"
#include "preset.h"

/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

void   strupr(SINT8 string[], SINT16 length);
void   strctr(SINT8 string1[], SINT8 string2[], SINT16 size);
void   strnset(SINT8 string[], SINT8 text, SINT16 size);
void   strsub(SINT8 string[], SINT8 old, SINT8 newstr);
void   RemoveExtraSpaces(UINT8 string[]);
void   MoveToCurrentPreset(SETUPS_Ver800 *Pt1);
enum   PARAM GetParamChanged(void);
UINT16 GetPowerSupplyFrequency(void);
UINT16 GetPowerSupplyFrequencyOffset(void);
void   PutParamChanged(enum PARAM NewID);
float  PoundToNewton(SINT32 ILbs);
float  InchToMm(SINT32 IInches);
UINT16 myatoi(SINT8 s[]);
void   GetModelNumber(SINT8 Model[]);
void   GetPSInfo(SINT8 PSInfoStr[]);
void   GetCntrlLevel(SINT8 CntrlLevel[]);
SINT32 GetMaxStrokeLength(void);
void ClearPressureArray(void);
void UpdatePressureOffset(void);
void UpdateDistanceOffset(void);
BOOLEAN CheckPressure( UINT16 *TestPresFlag, UINT16 PressureValue );
void Numout(UINT32 Value, UINT8 Base, UINT8 LC, STR Ptr[], UINT8 Width);
BOOLEAN AtLeastVersion806(void);
void ConfigureAed(void);
void ConfigureAef(void);
void ConfigureActuatorBoard(UINT16 ActType, UINT16 Stroke, UINT16 Cylinder);
BOOLEAN IsConfiguredActuatorForceGauge(BOOLEAN AED_LC, BOOLEAN AEF_LC, BOOLEAN AED_SB, BOOLEAN AEF_SB);
