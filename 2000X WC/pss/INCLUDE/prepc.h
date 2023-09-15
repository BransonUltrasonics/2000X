/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\prepc.h_v   1.0   Mar 29 1999 13:51:02   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/prepc.h 1.12 97/02/26 10:49:29 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/prepc.h                                          */
/*   DATE:    97/02/26                                                 */
/*   PURPOSE: Structure definitions, function prototypes, macros,      */
/*            and symbol definitions for pREPC+/68K version 2.20       */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1997, Integrated Systems, Inc.           */
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
/*                                                                     */
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
#ifndef _PREPC_H
#define _PREPC_H

#include <limits.h>     /* ANSI C defined limits */
#include <float.h>      /* ANSI C defined limits for floating point numbers */
#include <stdarg.h>     /* ANSI C variable argument definition */

#include <assert.h>     /* pREPC+ assertion macros */
#include <ctype.h>      /* pREPC+ ctype macros and functions */
#include <errno.h>      /* pREPC+ error numbers and errno definition */
#include <locale.h>     /* pREPC+ locale functions */
#include <stddef.h>     /* pREPC+ standard defintions */
#include <stdio.h>      /* pREPC+ stdio functions */
#include <stdlib.h>     /* pREPC+ miscellaneous library function */
#include <string.h>     /* pREPC+ string functions definition */

#endif	/* _PREPC_H */

#if __cplusplus
}
#endif
