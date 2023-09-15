/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\pmontcfg.h_v   1.0   Mar 29 1999 13:51:00   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/pmontcfg.h 1.3 94/08/09 15:23:08 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/pmontcfg.h                                       */
/*   DATE:    94/08/09                                                 */
/*   PURPOSE: Configuration table structure templates                  */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*         Copyright 1993 - 1994, Integrated Systems, Inc.             */
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
/*   This file contains templates for pMONT+ configuration table.      */
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
#ifndef _PMONTCFG_H
#define _PMONTCFG_H

typedef struct
    {
    void (*code)();     /* Address of pMONT+ module */
    long data;          /* start of pMONT data */
    long dataSize;      /* start of pMONT data */
    long cmode;         /* comm. mode: NETWORK_TYPE_CONN, PSOSDEV_.. */
    long dev;           /* IO dev. maj.minor # in format pSOS expects */
    char *traceBuff;    /* Buffer for logging trace events */
    long traceBuffSize; /* trace events buffer size */
    unsigned long (*tmFreq)(); /* returns 2nd timer frequency */
    void (*tmReset)();          /* resets 2nd timer */
    unsigned long (*tmRead)();  /* reads counter value of 2nd timer */
    long res1;
    long res2;
    long res3;
    long res4;
    }
    pMONT_CT;
 
#endif /* _PMONTCFG_H */

#if __cplusplus
}
#endif
