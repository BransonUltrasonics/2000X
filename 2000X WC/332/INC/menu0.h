/* $Header:   D:/SWLab/VMdb/2000Series/INC/MENU0.H_V   2.6   Aug 25 2004 04:55:32   BWadia  $ */
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

   Filename: menu0.h

   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #     Date            Author     Description
   ==========     ========        ======     ===========
      0                                      Initial Version
      1.00        4/29/96         PJ         First release
      2.00        7/26/96         PJ         Deleted extern data strings.
                                             Prototypes only
      2.10        08/21/96        PJ         Changed name of Prototype function.
      2.20        09/19/96        PJ         Deleted Prototype function.
      2.30        11/01/96        PJ         Added Prototype function.
      2.6         08/24/04        JOY        Added function prototype;
      

*/
/*
 ----------------------------- DEFINES------------------------------------
*/
#define USERIO       BIT1
#define ACTUATOR     BIT2
#define BBR          BIT3
#define PRINTING     BIT4
#define TOUCHSCREEN  BIT5
#define GLOBAL       BIT6

/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/
void RestoreDefaultConfirmScrn(UINT32 Default);
void SelectProperDefault(UINT32 Default);