/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\ctype.h_v   1.0   Mar 29 1999 13:50:54   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/ctype.h 1.13 97/02/26 10:55:24 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/ctype.h                                          */
/*   DATE:    97/02/26                                                 */
/*   PURPOSE: Character manipulation macro definitions                 */
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
/*   This file contains definitions used in character manipulation     */
/*   and should be included with applications that require these       */
/*   capabilities.                                                     */
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
#ifndef _CTYPE_H
#define _CTYPE_H

extern const char _lc_ctype[];
/*---------------------------------------------------------------------*/
/* Function prototypes						       */
/*---------------------------------------------------------------------*/
int isalnum(int c);
int isalpha(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);
int tolower(int c);
int toupper(int c);

/*---------------------------------------------------------------------*/
/* CTYPE functions defined as macros for faster access		       */
/*---------------------------------------------------------------------*/
#define _U	0x01
#define _L	0x02
#define _N	0x04
#define _S	0x08
#define _P	0x10
#define _C	0x20
#define _X	0x40

#define isalnum(ch)  ((_lc_ctype+1)[ch] & (_U | _L | _N))
#define isalpha(ch)  ((_lc_ctype+1)[ch] & (_U | _L))
#define iscntrl(ch)  ((_lc_ctype+1)[ch] & (_C))
#define isdigit(ch)  ((_lc_ctype+1)[ch] & (_N))
#define isgraph(ch)  ((_lc_ctype+1)[ch] & (_U | _L | _N | _P))
#define islower(ch)  ((_lc_ctype+1)[ch] & (_L))
#define isprint(ch)  ((ch != -1 && !((_lc_ctype+1)[ch] & (_C))))
#define ispunct(ch)  ((_lc_ctype+1)[ch] & (_P))
#define isspace(ch)  ((_lc_ctype+1)[ch] & (_S))
#define isupper(ch)  ((_lc_ctype+1)[ch] & (_U))
#define isxdigit(ch) ((_lc_ctype+1)[ch] & (_N | _X))

#define tolower(ch)  ((isupper(ch)) ? ((ch) - 'A' + 'a') : (ch))
#define toupper(ch)  ((islower(ch)) ? ((ch) - 'a' + 'A') : (ch))

#endif  /* _CTYPE_H */

#if __cplusplus
}
#endif
