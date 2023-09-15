/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\stdarg.h_v   1.0   Mar 29 1999 13:51:06   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/std68k.h 1.5 93/11/24 13:57:33 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/stdarg.h                                         */
/*   DATE:    93/11/24                                                 */
/*   PURPOSE: macro definitions for variable argument lists            */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*          Copyright 1991 - 1993, Integrated Systems, Inc.            */
/*                      ALL RIGHTS RESERVED                            */
/*                                                                     */
/*   Permission is hereby granted to licensees of Integrated Systems,  */
/*   Inc. products to use or abstract this computer program for the    */
/*   sole purpose of implementing a product based on Integrated        */
/*   Systems, Inc. products.   No other rights to reproduce, use,      */
/*   or disseminate this computer program, whether in part or in       */
/*   whole, are granted.                                               */
/*                                                                     */
/*   Integrated Systems, Inc. makes no representation or warranties    */
/*   with respect to the performance of this computer program, and     */
/*   specifically disclaims any responsibility for any damages,        */
/*   special or consequential, connected with the use of this program. */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*   This file has been successfully tested with the Microtec Research */
/*   cross-compiler for the 68K.  If you will be using a different     */
/*   compiler you may need to change this file.  Usually the most      */
/*   expedient thing to do is just replace this file with the one      */
/*   supplied with your compiler.                                      */
/*                                                                     */
/***********************************************************************/
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version

*/

#if __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------*/
/* Don't allow this file to be included more than once.                */
/*---------------------------------------------------------------------*/
#ifndef _STDARG_H
#define _STDARG_H

/*---------------------------------------------------------------------*/
/*  type definition of va_list                                         */
/*---------------------------------------------------------------------*/
typedef char *va_list;

/*---------------------------------------------------------------------*/
/*  macro - va_start()  --  initializes arg_pt, which has been defined */
/*                          as type va_list.                           */
/*---------------------------------------------------------------------*/
#define va_start(ap,param) ((void)((ap)=(char*)(&param+1)))

/*---------------------------------------------------------------------*/
/*  macro - va_arg()    --  returns the next argument and repositions  */
/*                          arg_pt.                                    */
/*---------------------------------------------------------------------*/
#define va_arg(ap,type) (((type*)((ap)+=sizeof(type)))[-1])

/*---------------------------------------------------------------------*/
/*  macro - va_end()     --  undefined for this appliction.            */
/*---------------------------------------------------------------------*/
#define va_end(ap) ((void)0)

#endif /* _STDARG_H */

#if __cplusplus
}
#endif
