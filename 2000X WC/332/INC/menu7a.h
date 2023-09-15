/* $Header:   D:/SWLab/VMdb/2000Series/INC/MENU7A.H_V   1.24   08 Jun 2010 14:12:34   NHahmed  $ */
#ifndef MENU7A_H
#define MENU7A_H 
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

   Filename:      menu7a.h

   

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      1            11/25/96      LAM         added missing prototypes   
      2.1.2        06/18/97      PhilJ       added enums WELDTIME_MULTIPLIER
                                             and TESTTIME_MULTIPLIER
      2.1.3        06/19/97      PhilJ       added enums LANGUAGE_TYPE and
                                             BAUDRATE_SETTING
      2.1.4        06/23/97      PhilJ       Changed enum BAUDRATE to BAUD_TYPE
      2.1.5        07/11/97      PhilJ       Added missing prototypes
      2.1.6        07/18/97      PhilJ       added enums CYLINDER_SIZE and
                                             STROKE_LEN
      2.1.8        08.29.97      JBerman     Added Prototypes:
                                                   void GetCylinderIndex(void);
                                                   void GetStrokeLenIndex(void);
      2.1.9        10.03.97      JBerman     Added: SIZE_40 - SIZE_80
                                                    LENGTH_80 - LENGTH_160
      2.1.10       07/30/98      BJB         Added prototypes of new functions.
      1.11         04/20/99      OFI         Changed for DIAB
      1.12         10-26-99      JZ          removed SetDateAndTime()
      1.13         02-23-00      JZ          merged 7.f4CHp to trunk
      1.14         02-28-00      JZ          removed tabs
      1.15         04-06-00      JZ          merged Lang to trunk
      1.17         08-15-00      AT          Added LANGUAGE_MAX to the enum
      1.18         08-16-00      AT          Added LANGUAGE_LAST to the enum
      1.19         08-18-00      LAM         Added prototype UpdateCylDefaults
                                             (Issue 3276)
      1.20         11-28-00      BEkymer     Added SIZE4_0 to CYLINDER_SIZE enum
      1.21         04-19-04      VSharma     Added WELD_DISABLE_MENU.
      1.22         07-25-05      Bwadia      LANGUAGE_TYPE enum changed for asian language
      1.23         10-20-08      NHAhmed     Replaced stroke length LENGTH_7 by LENGTH_2.
      1.24         06-08-10      PDwivedi    Replaced stroke length LENGTH_160 by LENGTH_50 
                                             for standard MICRO Actuator.
 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

#define ZERO_MASK 0x0000

enum LANGUAGE_TYPE {
   ENGLISH            = 0x0001u,
   GERMAN             = 0x0002,
   SPANISH            = 0x0004,
   ITALIAN            = 0x0008,
   FRENCH             = 0x0010,
   CHINESESIMPLIFIED  = 0x0020,
   CHINESETRADITIONAL = 0x0040,
   JAPANESE           = 0x0080,
   KOREAN             = 0x0100,
   LANGUAGE_LAST = KOREAN,
   LANGUAGE_MAX = 9,
   LANGUAGESIZER = 65535 };

 enum BAUD_TYPE {
   BAUD_4800  = 0x0001u,
   BAUD_9600  = 0x0002,
   BAUD_19200 = 0x0004,
   BAUDSIZER = 65535 };

 enum CYCLINDER_SIZE {
   CUSTOMSIZE   = 0u,
   SIZE1_5      = 0x0001,
   SIZE2_0      = 0x0002,
   SIZE2_5      = 0x0004,
   SIZE3_0      = 0x0008,
   SIZE3_25     = 0x0010,
   SIZE4_0      = 0x0200,
   
   SIZE_40      = 0x0020,
   SIZE_50      = 0x0040,
   SIZE_63      = 0x0080,
   SIZE_80      = 0x0100,
   
   CYCLINDERSIZER = 65535 };

 enum STROKE_LEN {
   CUSTOMLEN   = 0u,
   LENGTH_4    = 0x0001,
   LENGTH_5    = 0x0002,
   LENGTH_6    = 0x0004,
   LENGTH_2    = 0x0008,
   LENGTH_8    = 0x0010,
   
   LENGTH_80   = 0x0020,
   LENGTH_100  = 0x0040,
   LENGTH_125  = 0x0080,
  // LENGTH_160  = 0x0100,
   LENGTH_50   = 0x0100,
   LENGTHSIZER = 65535 };

 enum WELDTIME_MULTIPLIER {
   WELDTIMEx1 = 0x0001u,
   WELDTIMEx2 = 0x0002,
   WELDTIMEx3 = 0x0004,
   WELDTIMESIZER = 65535 };

 enum TESTTIME_MULTIPLIER {
   TESTTIMEx1 = 0x0001u,
   TESTTIMEx2 = 0x0002,
   TESTTIMEx3 = 0x0004,
   TESTTIMESIZER = 65535 };

 enum WELD_DISABLE_MENU {
   USERIO_MENU,     // Stop State Machine in User IO Menu            
   CUSTOM_MENU  };  // and Custom menu.          

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
 
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void GetBaudIndex(void);
void SetDumbTerminal(void);
void SetRemote(void);
void SetHost(void);
void GetWeldScaleIndex(void);
void GetTestScaleIndex(void);

void GetCylinderIndex(void);
void SetCylinderIndex(void);
void GetCylinderStrings(void);
void GetStrokeLenIndex(void);
void SetStrokeLenIndex(void);
void GetStrokeLenStrings(void);
void UpdateCylDefaults(void);

#endif