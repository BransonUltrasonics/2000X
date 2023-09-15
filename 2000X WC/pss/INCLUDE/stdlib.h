/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\stdlib.h_v   1.0   Mar 29 1999 13:51:06   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/stdlib.h (&U&) 2.4 97/10/30 10:44:22 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/stdlib.h                                         */
/*   DATE:    97/10/30                                                 */
/*   PURPOSE: pREPC+ STDLIB functions & other definitions              */
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
#ifndef _STDLIB_H
#define _STDLIB_H

#define RAND_MAX	32767
#define EXIT_FAILURE	1
#define EXIT_SUCCESS	0
#define MB_CUR_MAX	sizeof(wchar_t)

#ifndef NULL
	#define NULL    0
#endif

#ifndef _DIV_T_DEFINED
	#define _DIV_T_DEFINED		1
	typedef struct {
		int	quot;
		int	rem;
	} div_t;
#endif

#ifndef _LDIV_T_DEFINED
	#define _LDIV_T_DEFINED		1
	typedef struct {
		long	quot;
		long	rem;
	} ldiv_t;
#endif

#ifndef _WCHAR_T_DEFINED
	#define _WCHAR_T_DEFINED	1
        #ifndef __cplusplus
	typedef unsigned char wchar_t;
        #endif
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
int abs(int j);
double atof(const char *nptr);
int atoi(const char *nptr);
long int atol(const char *nptr);
void *bsearch(const void *key, const void *base, size_t nmemb, size_t size,
               int (*compar)(const void *, const void *));

void *calloc(size_t nmemb, size_t size);
div_t div(int numer, int denom);
void free(void *ptr);
long labs(long int j);
ldiv_t ldiv(long int numer, long int denom);

void *malloc(size_t size);
int mblen(const char *s, size_t n);
size_t mbstowcs(wchar_t *pwcs, const char *s, size_t n);
int mbtowc(wchar_t *pwc, const char *s, size_t n);
void qsort(void *base, size_t nmemb, size_t size,
             int (*compar)(const void *, const void *));

int rand(void);
void *realloc(void *ptr, size_t size);
void srand(unsigned int seed);
double strtod(const char *nptr, char **endptr);
long int strtol(const char *nptr, char **endptr, int base);

unsigned long int strtoul(const char *nptr, char **endptr, int base);
int wctomb(char *s, wchar_t wchar);
size_t wcstombs(char *s, const wchar_t *pwcs, size_t n);

/*---------------------------------------------------------------------*/
/* The following functions are not supported and set ERR_UNIMPL errno. */
/*---------------------------------------------------------------------*/
int atexit(void (*func)(void));
char *getenv(const char *name);
int system(const char *string);

#if __cplusplus
/*---------------------------------------------------------------------*/
/* exit() & abort() are defined in exit.c, under class lib directory   */
/*---------------------------------------------------------------------*/
void    exit(...);
void    abort(...);

#else
/*---------------------------------------------------------------------*/
/* exit() closes components and then terminates.  All components that  */
/* are present should be closed.  As shipped, only pREPC+ is closed.   */
/* If your system includes other components, exit() should be edited   */
/* appropriately.  Do not close absent components.                     */
/* (Use close_f(0) to close pHILE+, close(0) to close pNA+).           */
/* Finally, after closing all the components, call free((void *)-1) to */
/* release any memory allocated by pREPC+.			       */
/*---------------------------------------------------------------------*/
#define exit(status)    {                                               \
                        if (status != 0)                                \
                            fprintf(stderr,"Error code = %d\n",status); \
                        fclose(0);                                      \
                        /* close_f(0); */                               \
                        /* close(0); */                                 \
                        free((void *)-1);                               \
                        if (t_delete(0) != 0)                           \
                            t_suspend(0);                               \
                        }

#define abort() exit(0)

#endif	/* _cplusplus */

#endif  /* _STDLIB_H */

#if __cplusplus
}
#endif
