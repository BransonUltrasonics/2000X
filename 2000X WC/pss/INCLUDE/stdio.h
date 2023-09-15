/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\stdio.h_v   1.0   Mar 29 1999 13:51:06   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/stdio.h (&U&) 1.15 97/04/21 12:56:08 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/stdio.h                                          */
/*   DATE:    97/04/21                                                 */
/*   PURPOSE: Standard input/output declarations and definitions       */
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
#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>

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
/* fopen() returns a pointer to a FILE structure. The structure is     */
/* used to store information about the stream. However, the definition */
/* of the FILE structure is not exported by pREPC+. The following      */
/* definition should work fine since the applications are not expected */
/* to access this structure directly.				       */
/*---------------------------------------------------------------------*/
#define FILE long

/*---------------------------------------------------------------------*/
/* Macro definitions of three standard devices.  _lc_f_addr() is an    */
/* internal pREPC+ function that returns a pointer to FILE.            */
/*---------------------------------------------------------------------*/
extern FILE     *_lc_f_addr(int);
#define stdin   (_lc_f_addr(0))
#define stdout  (_lc_f_addr(1))
#define stderr  (_lc_f_addr(2))

/*---------------------------------------------------------------------*/
/* Definition of buffering types that can be used in setvbuf()         */
/*---------------------------------------------------------------------*/
#define _IOFBF          0x04000  /* full buffering */
#define _IOLBF          0x08000  /* line buffering */
#define _IONBF          0x10000  /* no buffering */

/*---------------------------------------------------------------------*/
/* The following definitions remain to maintain backward compatibility */
/*---------------------------------------------------------------------*/
#define _IO_FBF         0x04000  /* full buffering */
#define _IO_LBF         0x08000  /* line buffering */
#define _IO_NBF         0x10000  /* no buffering */

/*---------------------------------------------------------------------*/
/* Definition of fseek() parameters                                    */
/*---------------------------------------------------------------------*/
#define SEEK_SET        0        /* seek from begining of file */
#define SEEK_CUR        1        /* seek from current location */
#define SEEK_END        2        /* seek from end of file */

/*---------------------------------------------------------------------*/
/* Type definition for parameter used in fgetpos() and fsetpos()       */
/*---------------------------------------------------------------------*/
typedef long fpos_t;

/*---------------------------------------------------------------------*/
/* Macro definitions that depend on pREPC+ configuration parameters.   */
/* Need to #include <configs.h> to access these parameters.	       */
/*---------------------------------------------------------------------*/
extern struct NodeConfigTable *anchor;

#define BUFSIZ		(anchor->prepct->lc_bufsiz)
#define FOPEN_MAX	(anchor->prepct->lc_numfiles)

/*---------------------------------------------------------------------*/
/* Some other constants and macros needed by stdio functions           */
/*---------------------------------------------------------------------*/
#define EOF		(-1)
#define L_tmpnam	64
#define TMP_MAX		1000
#define FILENAME_MAX	128	/* This is the worst case value to support   */
				/* MSDOS files; longer names may be accepted */
				/* by other filesystems supported by pHILE+  */

/*---------------------------------------------------------------------*/
/* Function prototypes						       */
/*---------------------------------------------------------------------*/
void   clearerr(FILE *stream);
int    fclose(FILE *stream);
int    feof(FILE *stream);
int    ferror(FILE *stream);
int    fflush(FILE *stream);
int    fgetc(FILE *stream);
int    fgetpos(FILE *stream, fpos_t *pos);
char  *fgets(char *s, int n, FILE *stream);
FILE  *fopen(const char *filename, const char *mode);
int    fprintf(FILE *stream, const char *format, ...);
int    fputc(int c, FILE *stream);
int    fputs(const char *s, FILE *stream);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
FILE  *freopen(const char *filename, const char *mode, FILE *stream);
int    fscanf(FILE *stream, const char *format, ...);
int    fseek(FILE *stream, long int offset, int whence);
int    fsetpos(FILE *stream, const fpos_t *pos);
long int ftell(FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
int    getc(FILE *stream);
int    getchar(void);
char  *gets(char *str);
void   perror(const char *str);
int    printf(const char *format, ...);
int    putc(int c, FILE *stream);
int    putchar(int c);
int    puts(const char *s);
int    remove(const char *filename);
int    rename(const char *oldfile, const char *newfile);
void   rewind(FILE *stream);
int    scanf(const char *format, ...);
void   setbuf(FILE *stream, char *buf);
int    setvbuf(FILE *stream, char *buf, int mode, size_t size);
int    sprintf(char *s, const char *format, ...);
int    sscanf(const char *s, const char *format, ...);
FILE  *tmpfile(void);
char  *tmpnam(char *s);       /* ANSI C version */
char  *tmpname(char *s);      /* ISI version */
int    ungetc(int c, FILE *stream);
int    vfprintf(FILE *stream, const char *format, va_list arg);
int    vprintf(const char *format, va_list arg);
int    vsprintf(char *s, const char *format, va_list arg);

#endif  /* _STDIO_H */

#if __cplusplus
}
#endif
