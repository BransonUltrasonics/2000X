/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\proflib.h_v   1.0   Mar 29 1999 13:51:04   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/proflib.h 3.1 97/10/07 13:18:23 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/proflib.h                                        */
/*   DATE:    97/10/07                                                 */
/*   PURPOSE: DIAB Profiler Support Header file.                       */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1997, Integrated Systems, Inc.           */
/*	          Copyright 1997 Diab Data, Inc.                       */
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
/*	Description :                                                  */
/*	Library module for compiler profiling. Header file.            */
/*                                                                     */
/*   Note : Include <stdio.h> before this file. Need it for recognizing*/
/*          FILE macro in declaration of __prof_fprint()               */
/***********************************************************************/
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version

*/

#ifndef D_proflib
#define D_proflib
/**************	Imports to declare exports **********************/

#undef EXTERN
#ifdef M_proflib
#define EXTERN extern
#else
#define EXTERN extern
#endif /* M_proflib */

#ifndef	M_profutil

/*
 *	Profile data structure used by target.
 */

typedef void (*prof_func_ptr)();
typedef unsigned long prof_count;
typedef unsigned long prof_time;
typedef unsigned long prof_val;

struct prof_info {
	struct prof_memory	*pi_mhead;
	struct prof_memory	*pi_mtail;
	struct prof_func	*pi_funcbase;
	struct prof_stack	*pi_stack;
	struct prof_pair	*pi_pairfree;
	struct prof_pair	*pi_pairlast;
	prof_val		pi_nfunc;
};

struct prof_memory {
	struct prof_memory	*pm_next;
	prof_val		pm_size;
};

struct prof_data {
	prof_count		pd_recur;
	prof_count		pd_count;
	prof_time		pd_functime;
	prof_time		pd_totaltime;
};

struct prof_func {
	struct prof_data	pf_data;
	struct prof_pair	*pf_pair;
	struct prof_pair	*pf_last;
};

struct prof_pair {
	struct prof_data	pp_data;
	struct prof_pair	*pp_next;
	struct prof_func	*pp_caller;
	struct prof_func	*pp_callee;
};

struct prof_stack {
	struct prof_stack	*ps_prev;
	struct prof_func	*ps_func;
	struct prof_pair	*ps_pair;
	volatile prof_time	ps_toptime;
	volatile prof_time	ps_subtime;
};

EXTERN struct prof_info *__PROF_INFO_PTR;

extern void __prof_fprint(FILE *);
extern void __prof_reset(void);
extern void __prof_init(void);
extern void __prof_finish(struct prof_info *);
extern void __prof_enter(prof_func_ptr *, struct prof_stack *);
extern void __prof_exit(void);

#else  /* M_profutil */

/*
 *	Profile data structure used by host.  Must be identical
 *	to the above in size and order.
 */

struct prof_info {
	prof_addr		pi_mhead;
	prof_addr		pi_mtail;
	prof_addr		pi_funcbase;
	prof_addr		pi_stack;
	prof_addr		pi_pairfree;
	prof_addr		pi_pairlast;
	prof_val		pi_nfunc;
};

struct prof_memory {
	prof_addr		pm_next;
	prof_val		pm_size;
};

struct prof_data {
	prof_count		pd_recur;
	prof_count		pd_count;
	prof_time		pd_functime;
	prof_time		pd_totaltime;
};

struct prof_func {
	struct prof_data	pf_data;
	prof_addr		pf_pair;
	prof_addr		pf_last;
};

struct prof_pair {
	struct prof_data	pp_data;
	prof_addr		pp_next;
	prof_addr		pp_caller;
	prof_addr		pp_callee;
};

struct prof_stack {
	prof_addr		ps_prev;
	prof_addr		ps_func;
	prof_addr		ps_pair;
	prof_time		ps_toptime;
	prof_time		ps_subtime;
};

#endif /* M_profutil */
#endif /* D_proflib */

/* Local variables:	*/
/* Mode: c-mode		*/
/* c-basic-offset: 8	*/
/* c-indent-level: 8	*/
/* c-argdecl-indent:0	*/
/* c-label-offset: -8	*/
/* comment-column: 40	*/
/* End:			*/
