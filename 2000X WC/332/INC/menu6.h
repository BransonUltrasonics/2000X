/* $Header:   K:/APPS/PVCS Pro/332new/INC/MENU6.H_V   2.7   Jun 05 2000 09:26:02   shishir  $ */
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

   Filename: menu6.h

   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #     Date            Author     Description
   ==========     ========        ======     ===========
      0                                      Initial Version
      1.0         04/29/96         PJ        First release
      1.1         11/01/96         PJ        Added Prototypes
      1.2         03/05/97         PJ        Added GetSerialNumbers Prototype
	  1.3         06/02/00         SCM       Added function prototype for
	                                         GetDUPSInfo().

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

void GetPowerSupplyInfo(void);
void LoadActuatorType(void);
void GetControlLevel(void);
void GetSerialNumbers(void);
void GetDUPSInfo(void); 