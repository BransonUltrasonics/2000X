/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\prepccfg.h_v   1.0   Mar 29 1999 13:51:02   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/prepccfg.h 2.1 93/10/21 10:05:07 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/prepccfg.h                                        */
/*   DATE:    93/10/21                                                 */
/*   PURPOSE: Configuration table structure templates                  */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1993, Integrated Systems, Inc.                  */
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
/*   This file contains templates for pREPC+ configuration table.      */
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
#ifndef _PREPCCFG_H
#define _PREPCCFG_H

/*=====================================================================*/
/* pREPC+ Configuration table structure                                */
/*=====================================================================*/
typedef struct pREPCConfigTable
    {
    void (*lc_code)();               /* Start address of pREPC+ code */
    void *lc_data;                   /* Start address of pREPC+ data area */
    unsigned long lc_datasize;       /* Size of pREPC+ data area */
    unsigned long lc_bufsiz;         /* I/O buffer size */
    unsigned long reserved1;         /* Reserved, must be 0 */
    unsigned long lc_numfiles;       /* Max number of open files per task */
    unsigned long lc_waitopt;        /* Wait option for memory allocation */
    unsigned long lc_timeopt;        /* Timeout option for memory allocation */
    char *lc_tempdir;                /* Pointer to temporary file directory */
    char *lc_stdin;                  /* Pointer to stdin */
    char *lc_stdout;                 /* Pointer to stdout */
    char *lc_stderr;                 /* Pointer to stderr */
    unsigned long lc_ssize;          /* Size of print buffer */
    unsigned long reserved[3];       /* Reserved, must be zero */
    } pREPC_CT;

#endif

#if __cplusplus
}
#endif
