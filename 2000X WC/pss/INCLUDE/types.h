/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\INCLUDE\types.h_v   1.1   Apr 06 1999 13:30:02   lmarkure  $ */
/* @(#) pSOSystem/68K V2.2.2: include/types.h 2.11 97/09/08 10:49:56 */
/***********************************************************************/
/*                                                                     */
/*   MODULE: include/types.h                                           */
/*   DATE:    97/09/08                                                 */
/*   PURPOSE: standard types to be used in C files                     */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1995, Integrated Systems, Inc.           */
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
 1.1   04/06/99 LAM     deleted TRUE & FALSE, they are defined in portable.h

*/

#ifdef __cplusplus
    #if __cplusplus
    extern "C" {
    #endif
#endif
 
/*---------------------------------------------------------------------*/
/* Don't allow this file to be included more than once.                */
/*---------------------------------------------------------------------*/
#ifndef _TYPES_H
#define _TYPES_H

#ifndef _ASM_

typedef unsigned char   UCHAR;
typedef unsigned short  USHORT;
typedef unsigned int    UINT;
typedef unsigned long   ULONG;
 
#endif

#define NULL        0

#define USEROM      2
#define LIB         1
#define YES         1
#define NO          0

#define PCCON       386

/***********************************************************************/
/* BSP_CPUFAMILY definitions has the following values.                 */
/***********************************************************************/
#define    FAMILY_M68000    1
#define    FAMILY_POWERPC   2
#define    FAMILY_X86       3
#define    FAMILY_960       4
#define    FAMILY_MIPS      5
#define    FAMILY_ARM       6
#define    FAMILY_MCF       7
#define    FAMILY_RCE       8


#endif  /* _TYPES_H */
 
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
