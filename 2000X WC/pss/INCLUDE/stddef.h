/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\stddef.h_v   1.0   Mar 29 1999 13:51:06   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/stddef.h (&U&) 2.6 97/10/30 10:44:02 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:   include/stddef.h                                        */
/*   DATE:    97/10/30                                                 */
/*   PURPOSE: Standard pREPC+ definitions                              */
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

/*---------------------------------------------------------------------*/
/* Don't allow this file to be included more than once.                */
/*---------------------------------------------------------------------*/
#ifndef _STDDEF_H
#define _STDDEF_H

#ifndef _WCHAR_T_DEFINED
	#define _WCHAR_T_DEFINED	1
        #ifndef __cplusplus
	typedef unsigned char wchar_t;
        #endif
#endif

#ifndef _PTRDIFF_T_DEFINED
	#define _PTRDIFF_T_DEFINED	1
	typedef int ptrdiff_t;
#endif

#ifndef _SIZE_T_DEFINED
	#define _SIZE_T_DEFINED		1
	#ifdef _SDS
		#define size_t  _size_t
	#else
		typedef unsigned int size_t;
	#endif
#endif

#ifndef offsetof
	#define offsetof(_type, _field)    ((size_t)&(((_type*)0)->_field))
#endif

#ifndef NULL
	#define NULL    0
#endif

#endif  /* _STDDEF_H */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
