/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\string.h_v   1.0   Mar 29 1999 13:51:08   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/string.h (&U&) 2.4 97/02/26 11:00:25 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/string.h                                         */
/*   DATE:    97/02/26                                                 */
/*   PURPOSE: pREPC+ string manipulation functions                     */
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
#ifndef _STRING_H
#define _STRING_H

#ifndef NULL
	#define NULL    0
#endif

#ifndef _SIZE_T_DEFINED
	#define _SIZE_T_DEFINED		1
	#if _SDS
		#define size_t  _size_t
	#else
		typedef unsigned int size_t;
	#endif
#endif

/*---------------------------------------------------------------------*/
/* Function prototypes						       */
/*---------------------------------------------------------------------*/
void  *memchr(const void *s, int c, size_t n);
int    memcmp(const void *s1, const void *s2, size_t n);
void  *memcpy(void *s1, const void *s2, size_t n);
void  *memmove(void *s1, const void *s2, size_t n);
void  *memset(void *s, int c, size_t n);

char  *strcat(char *s1, const char *s2);
char  *strchr(const char *s, int c);
int    strcmp(const char *s1, const char *s2);
int    strcoll(const char *s1, const char *s2);
char  *strcpy(char *s1, const char *s2);

size_t strcspn(const char *s1, const char *s2);
char  *strerror(int errnum);
size_t strlen(const char *s);
char  *strncat(char *s1, const char *s2, size_t n);
int    strncmp(const char *s1, const char *s2, size_t n);

char  *strncpy(char *s1, const char *s2, size_t n);
char  *strpbrk(const char *s1, const char *s2);
char  *strrchr(const char *s, int c);
size_t strspn(const char *s1, const char *s2);
char  *strstr(const char *s1, const char *s2);

char  *strtok(char *s1, const char *s2);
size_t strxfrm(char *s1, const char *s2, size_t n);

#endif  /* _STRING_H */

#if __cplusplus
}
#endif
