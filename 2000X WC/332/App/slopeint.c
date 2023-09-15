/* $Header:   K:\APPS\PVCS Pro\332new\App\SLOPEINT.C_V   2.9   Oct 11 1999 11:21:02   jzimny  $ */
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Slope Intercept for Calibration Table                       */
/*                                                                          */
/* Filename:    Slopeint.c                                                  */
/*                                                                          */
/* Function Name: Calibration code                                          */
/*                                                                          */
/*          Written by:   Bill Truchsess                                    */
/*                Date:   04-15-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date        Author       Description                         */
/*  =========  =========   ===========  ===========                         */
/*      1      05-15-96    BEKymer      Add proper function prototyping     */
/*      2      06-14-96    BEKymer      Eliminate multiple returns          */
/*      3      08-06-96    LAM          do calculation on error condition   */
/*      4      10-10-96    LAM          added uint32 version                */
/*      5      11-10-96    LAM          fixed divide by zero                */
/*      2.9    10-11-99    JZ           removed SlopeInterceptCalc32()      */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*----------------------------- DESCRIPTION --------------------------------*/

/*
   Inputs: y2 = 2nd point - calibration standard reading
	   y1 = 1st point - calibration standard reading
	   x2 = 2nd point - a/d reading
	   x1 = 1st point - a/d reading
	   &m = Pointer to slope variable return
	   &b = Pointer to intercept variable return
   Return: m  = slope calculation
	   b  = intercept calculation
	   return value = -1 if divide by zero error
			= -2 if input data greater than Max
			= -3 if Min > Max input data
			= 0  if calculation processed
*/

/*
   This module includes the support functions for the sensor calibration.
*/

/*----------------------------- PSEUDO CODE --------------------------------*/

/*                 m = (y2-y1)/(x2-x1)                                      */
/*                 b = y1-(x1*m)                                            */

/*---------------------------- LOCAL_EQUATES -------------------------------*/
//#define INCLUDE_UNIT_TEST

/*------------------------------ INCLUDES ----------------------------------*/
#include <prepc.h>
#include "portable.h"
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

#include "slopeint.h"


/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/


/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/


/*-------------------------------- CODE ------------------------------------*/

SINT16 SlopeInterceptCalc(UINT16 y2, UINT16 y1, UINT16 x2, UINT16 x1, DFLOAT *m, DFLOAT *b)
{
   SINT16 RetVal = 0;


/*---- Check for errors here ----*/

   if (y2 > 1000) RetVal = -2;        /* max y exceeded            */
   if (x2 > 4095) RetVal = -2;        /* max x exceeded            */
   if (y1 > y2)   RetVal = -3;        /* dy negative               */
   if (x1 > x2)   RetVal = -3;        /* dx negative               */
   if ((x2 - x1) == 0) RetVal = -1;   /* Divide by zero error      */
   if(RetVal != -1){
      *m = (DFLOAT)(y2-y1)/(DFLOAT)(x2-x1);
      *b = y1-((DFLOAT)x1*(*m));
	}
   return(RetVal);
}


/* Include for Unit test */
#ifdef INCLUDE_UNIT_TEST
#include "G:\332\ut\slopeint.ut"
#endif
/* End of include for unit test */
