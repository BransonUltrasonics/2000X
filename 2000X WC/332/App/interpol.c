/* $Header:   K:\APPS\PVCS Pro\332new\App\INTERPOL.C_V   2.15   Nov 04 1999 14:43:10   jzimny  $ */
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Table Interpolation                                         */
/*                                                                          */
/* Filename:    Interpol.c                                                  */
/*                                                                          */
/* Function Name: Calibration code                                          */
/*                                                                          */
/*          Written by:   Bill Truchsess                                    */
/*                Date:   04-15-96                                          */
/*            Language:   "C/ASM"                                           */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#     Date           Author       Description                   */
/*  =========     =========      ===========  ===========                   */
/*     1           7/30/96       LAM          added signed table            */
/*     2           8/26/96       LAM          clean up warnings             */
/*     3           8/29/96       LAM          added warnings                */
/*     4           10/08/96      LAM          added uint32 table            */
/*     2.7         09/08/97      LAM          cleanup warnings              */
/*     2.8         09/09/97      LAM          moved temp vars off stack     */
/*     2.9         04/23/99      OFI          changed for DIAB              */                                                  
/*     2.10        05/10/99      LAM          changed A7 to A6              */
/*     2.10.1.1    06-23-99      JZ           added GetInterpolatedSINT32   */
/*     2.10.1.2    07-14-99      JZ           changed GetInerpolated to UINT16 */
/*     2.12        08-06-99      LAM          return 0 if value is neg for  */
/*                                            GetInterpolatedSINT32         */ 
/*     2.13        08-11-99      LAM          pass in the offset value to SINT32 interpolate */
/*     2.14        08-12-99      LAM          fixed offset of third parameter */
/*     2.15        11-04-99      JZ           added comments for GetInterpolatedSINT32 */
/*                                                                          */
/*----------------------------- DESCRIPTION --------------------------------*/

/*

   This module includes a support function for the sensor calibration.

*/

/*----------------------------- PSEUDO CODE --------------------------------*/


/*---------------------------- LOCAL_EQUATES -------------------------------*/
//#define INCLUDE_UNIT_TEST   

/*------------------------------ INCLUDES ----------------------------------*/
#include "portable.h"
#include "interpol.h"

/*
---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/



/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

static SINT32 ReturnValue;


/*-------------------------------- CODE ------------------------------------*/

SINT16 GetInterpolatedSINT16(SINT16 table_vals[], UINT16 data_in)
{
   asm(" MOVEA.L   $8(A6),A0 "); /* Get the 1st parameter */
   asm(" MOVE.W    $E(A6),D0 "); /* Get the 2nd paramater */
   asm(" TBLS.W      (A0),D0   ");
}

UINT16 GetInterpolatedUINT16(UINT16 table_vals[], UINT16 data_in)
{
   asm(" MOVEA.L   $8(A6),A0 "); /* Get the 1st parameter */
   asm(" MOVE.W    $E(A6),D0 "); /* Get the 2nd paramater */
   asm(" TBLU.W      (A0),D0   ");
}

UINT16 GetInterpolatedUINT32(UINT32 table_vals[], UINT16 data_in)
{
   asm(" MOVEA.L   $8(A6),A0 "); /* Get the 1st parameter */
   asm(" MOVE.W    $E(A6),D0 "); /* Get the 2nd paramater */
   asm(" TBLU.L      (A0),D0   ");
}



UINT16 GetInterpolatedSINT32(SINT32 table_vals[], UINT16 data_in, SINT16 Offset)
/****************************************************************************/
/*  This function takes arguments of force or velocity and its offset, and  */
/*  returns D/A counts for the PV                                           */
/****************************************************************************/
{
   
   asm(" MOVEA.L   $8(A6),A0 "); /* Get the 1st parameter */
   asm(" MOVE.W    $E(A6),D0 "); /* Get the 2nd paramater */   
   asm(" MOVE.W    $12(A6),D1 ");
   asm(" TBLS.L      (A0),D0   ");
   asm(" ADD.L       d1,d0 " ); 
   asm(" move.l    d0,_ReturnValue");
   if (ReturnValue < 0) ReturnValue = 0;
   return((UINT16)ReturnValue);
   
}

/* Include for Unit test */
#ifdef INCLUDE_UNIT_TEST
#include "g:\332\ut\interpol.ut"
#endif
/* End of include for unit test */


