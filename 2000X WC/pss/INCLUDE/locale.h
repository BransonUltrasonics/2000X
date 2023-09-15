/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\locale.h_v   1.0   Mar 29 1999 13:50:58   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/locale.h (&U&) 2.4 97/02/26 10:56:46 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/locale.h                                         */
/*   DATE:    97/02/26                                                 */
/*   PURPOSE: pREPC+ provided locale functions and related definitions */
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
#ifndef _LOCALE_H
#define _LOCALE_H

#ifndef NULL
	#define NULL    0
#endif

#define LC_ALL		0
#define LC_COLLATE	1
#define LC_CTYPE	2
#define LC_MONETARY	3
#define LC_NUMERIC	4
#define LC_TIME		5

/*---------------------------------------------------------------------*/
/* NOTE: This implementation only supports the C locale. It also       */
/*       assumes that the "char" is signed.                            */
/*---------------------------------------------------------------------*/
struct lconv {
	char	*decimal_point;		/* "." */
	char	*thousands_sep;		/* "" */
	char	*grouping;		/* "" */
	char	*int_curr_symbol;	/* "" */
	char	*currency_symbol;	/* "" */
	char	*mon_decimal_point;	/* "" */
	char	*mon_thousands_sep;	/* "" */
	char	*mon_grouping;		/* "" */
	char	*positive_sign;		/* "" */
	char	*negative_sign;		/* "" */
	char	int_frac_digits;	/* CHAR_MAX (=0x7F) */
	char	frac_digits;		/* CHAR_MAX (=0x7F) */
	char	p_cs_precedes;		/* CHAR_MAX (=0x7F) */
	char	p_sep_by_space;		/* CHAR_MAX (=0x7F) */
	char	n_cs_precedes;		/* CHAR_MAX (=0x7F) */
	char	n_sep_by_space;		/* CHAR_MAX (=0x7F) */
	char	p_sign_posn;		/* CHAR_MAX (=0x7F) */
	char	n_sign_posn;		/* CHAR_MAX (=0x7F) */
};

/*---------------------------------------------------------------------*/
/* Function prototypes						       */
/*---------------------------------------------------------------------*/
char *setlocale(int catagory, const char *locale);
struct lconv *localeconv(void);

#endif  /* _LOCALE_H */

#if __cplusplus
}
#endif
