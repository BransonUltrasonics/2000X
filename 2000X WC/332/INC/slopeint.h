/* $Header:   K:\APPS\PVCS Pro\332new\INC\SLOPEINT.H_V   2.4   Oct 11 1999 11:26:56   jzimny  $ */
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Slope Intercept for Calibration Table                       */
/*                                                                          */
/* Filename:    Slopeint.h                                                  */
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
/*      2      06-14-96    BEKymer      Change return value to SINT16       */
/*      3      10-10-96    LAM          added UINT32 prototype              */
/*      2.4    10-11-99    JZ           removed SlopeInterceptCalc32()      */
/*                                                                          */
/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

SINT16 SlopeInterceptCalc(
       UINT16 y2, UINT16 y1, UINT16 x2, UINT16 x1, DFLOAT *m, DFLOAT *b);
       
