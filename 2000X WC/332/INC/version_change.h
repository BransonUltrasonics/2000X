/* $Header:   D:/SWLab/VMdb/2000Series/INC/version_change.h_v   1.3   16 Dec 2008 10:25:10   BKymer  $ */
#ifndef VERSION_CHANGE_H
#define VERSION_CHANGE_H
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
              Filename: version_change.h
            Written by: 
                  Date: 06/02/04 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========

   1.0             06/02/04      SCM         Initial Version.
   1.1             06/04/04      VSharma     Added struct VER_INFO.
   1.2             06/22/04      JOY         Added defines/function prototypes.                                                                                        
   1.3             12-16-08      BEKymer     Add version 10 and 11 defines

 
 ------------------------------- DESCRIPTION -----------------------------------

  

 
 ------------------------------ INCLUDE FILES ----------------------------------
*/  
#include "statedrv.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/
#define VERMIN   0
#define VER8_21  821
#define VER8_22  822
#define VER8_23  823
#define VER9     900
#define VER10    1000
#define VER11    1100
#define VER1136  1136
#define VER12    1200
#define VERMAX   0xffff

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
typedef const struct VER_INFO{
   UINT16 VersionNum;
   void   (*VerUpdateFunc)(void);

};
   
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void UpdateToVer1136(void);
void UpdateToVer9(void);
void UpdateToVer8_21(void);
void CheckForVersionChange (void);
void SaveColdStartValues (void);
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/
/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif  
