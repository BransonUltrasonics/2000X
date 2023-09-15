/* $Header:   K:/apps/PVCS Pro/332new/INC/screenmsg_touch.h_v   1.4   Aug 19 2003 02:21:08   BWadia  $ */
#ifndef SCREEN_MSG_H
#define SCREEN_MSG_H
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
   Filename:      screenmsg_touch.h


            Written by: Shishir Madhugiri 
                  Date: 03/05/03 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========

   1.0             03/05/03      SCM         Initial Version.
   1.1             03/20/03      SCM         Added message definition for Touch screen 
                                             handler.
   1.3             07/10/03      SCM         Added PVCS header. 
   1.4             08/06/03      JOY         Added struct type SCRN_CALIB_CORDINATE.
                                                                                        
    
 ------------------------------- DESCRIPTION -----------------------------------

Message definition for message being sent to Touch task handler from Touch Screen ISR.   

 
 ------------------------------ INCLUDE FILES ----------------------------------
*/  

#include "commnmsg.h"


/*
 ------------------------------- DEFINES ---------------------------------------
*/
#define AHL_MODE_SIZE      11
#define X_AXIS             0  
#define Y_AXIS             1 
#define MAX_QVGA_X_VALUE   320
#define MAX_QVGA_Y_VALUE   240
#define MAX_TOUCH_X_VALUE  1023
#define MAX_TOUCH_Y_VALUE  1023
/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

typedef struct
   {
   COMMON_MSG_FIELD_TYPE common;             
   UINT8                 FirstByte;
   UINT8                 spare_1;
   UINT16                spare_2;
   UINT32                spare_3;
   UINT32                spare_4;
   } TOUCH_SCRN_MSG;        
                         
/***************************************************************************/
/*                        AHL Mode  (Gunze Orginal Mode)                   */ 
/***************************************************************************/

typedef struct {
   UINT8 Header;          /*constant 'R' or 'T' */
   UINT8 X[4];            /*4 Bytes ASCII for X Co-ordinate*/
   UINT8 Comma;           /*constant ','*/
   UINT8 Y[4];            /*4 Bytes ASCII for Y Co-ordinate*/
   UINT8 Cr;
   }AHL_Mode;

/***************************************************************************/
/*                     Screen Calib Co-ordinate Struct                     */
/***************************************************************************/

typedef struct {
   SINT16 InitCode;
   SINT16 Xa;
   SINT16 Ya;
   SINT16 Xb;
   SINT16 Yb;
   }SCRN_CALIB_CORDINATE;
   
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif  
