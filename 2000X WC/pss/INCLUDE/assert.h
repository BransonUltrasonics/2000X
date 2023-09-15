/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\assert.h_v   1.0   Mar 29 1999 13:50:54   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/assert.h (&U&) 2.1 95/12/08 13:36:54 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/assert.h                                         */
/*   DATE:    95/12/08                                                 */
/*   PURPOSE: pREPC+ defined assertion macros                          */
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

*/

#if __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------*/
/* Don't allow this file to be included more than once.                */
/*---------------------------------------------------------------------*/
#ifndef _ASSERT_H
#define _ASSERT_H

#ifdef NDEBUG

	#define assert(expr)    ((void)0)

#else	/* NDEBUG */

	#define assert(expression)    ((void)((expression) || \
	    (fprintf(stderr, "Assertion: \"%s\" failed, in file %s, line %d\n",\
	    #expression, __FILE__, __LINE__), 0)))

#endif	/* NDEBUG */

#endif  /* _ASSERT_H */

#if __cplusplus
}
#endif
