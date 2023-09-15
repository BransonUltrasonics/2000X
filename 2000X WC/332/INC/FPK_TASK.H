/* $Header:   K:/APPS/PVCS Pro/332new/INC/FPK_TASK.H_V   1.9   Nov 07 2000 14:43:44   bkymer  $ */
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

   Filename:      fpk_task.h


            Written by: Laura Markure 
                  Date: 5/30/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             5/30/96      LAM         Initial
      1.1           9/19/97      LAM         added keymode enum
      1.4          10/14/97      LAM         added powerabortmask
      1.5          11/18/97      LAM         added digpotmask
      1.6           6/11/98      LAM         added disablesel3 mask for calibration
      1.7          08/28/00      SCM         Added HSMASK for HORNSCANABORT.
      1.8          10/04/00      LAM         Added HSSubmenuMASK ISSUE(3597).
      1.9          11-07-00      BEKymer     Added ESTOPMASK


 
 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  
enum KEYMODE {
     WELDMODEMASK,                /* Any weld sequence                      */
     CALMODEMASK,                 /* Force or distance calibration          */
     SCMODEMASK,                  /* added actuator system calibration      */
     POWERCALMODEMASK,            /* added power calibration                */
     POWERABORTMASK,              /* added power abort                      */
     HDMODEMASK,                  /* Horn down sequence                     */
     TESTMODEMASK,                /* Test Mode sequence                     */
     POWERDOWNMODEMASK,           /* Power down sequence                    */
     DIGPOTMASK,                  /* Power down sequence                    */
     DISABLESEL3,                 /* disable during calibration             */
     POWERUPMODEMASK,             /* Power up sequence                      */
     HSSUBMENUMASK,               /* Horn Scan Submenu Mask                 */
     HSMASK,                      /* Horn Scan abort                        */
     ESTOPMASK  };                /* Estop mask                             */

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
 
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void FrontPanelKeypadTask(void);
void UpdateKeyMask(UINT32 KeyMode);


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/


