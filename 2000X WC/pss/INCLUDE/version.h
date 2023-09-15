/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\version.h_v   1.0   Mar 29 1999 13:51:08   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/version.h (ghs) 2.46 98/04/10 09:24:37 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/version.h                                        */
/*   DATE:    98/04/10                                                 */
/*   PURPOSE: pSOSystem version and copyright strings                  */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*          Copyright 1991 - 1998, Integrated Systems, Inc.            */
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
/*   This file defines a version string which can be included          */
/*   in programs to identify which version of pSOSystem they were      */
/*   built from.                                                       */
/*                                                                     */
/***********************************************************************/
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version

*/

#ifdef __cplusplus
    #if __cplusplus
extern "C" {
    #endif
#endif

#ifndef _VERSION_H
#define _VERSION_H

/*---------------------------------------------------------------------*/
/* VERSION will be used in sysinit.c as a compile time check to        */
/* compare the BSP_VERSION to the pSOSystem VERSION                    */
/*---------------------------------------------------------------------*/
#define VERSION 222
#define VERSION_STRING "2.2.2"
#define COPYRIGHT "Copyright (c) 1991 - 1998, Integrated Systems, Inc."

#endif /* _VERSION_H */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
