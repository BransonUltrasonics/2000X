/* $Header:   K:\APPS\PVCS Pro\332new\INC\INTERPOL.H_V   2.5   Aug 11 1999 14:41:28   lmarkure  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96              */
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

   Filename:      interpol.h


            Written by: Laura Markure 
                  Date: 5/15/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             5/15/96      LAM         Initial
      1             7/27/96      LAM         chged declaration
      2             10/08/96     LAM         added prototype UINT32
	  2.3.1.1		06-23-99     JZ          added prototype UINT32
 	  2.3.1.2       07-14-99     JZ          changed to UINT16
	  2.5           08-11-99     LAM         added 3rd parameter for forcetableoffset

 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  


/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
 
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

SINT16 GetInterpolatedSINT16(SINT16 table_vals[], UINT16 data_in);
UINT16 GetInterpolatedUINT16(UINT16 table_vals[], UINT16 data_in);
UINT16 GetInterpolatedUINT32(UINT32 table_vals[], UINT16 data_in);
UINT16 GetInterpolatedSINT32(SINT32 table_vals[], UINT16 data_in, SINT16 Offset);

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/


