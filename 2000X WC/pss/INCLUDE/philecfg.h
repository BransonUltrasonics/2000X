/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\philecfg.h_v   1.0   Mar 29 1999 13:51:00   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/philecfg.h 2.3 95/08/22 11:32:32 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/philecfg.h                                        */
/*   DATE:    95/08/22                                                 */
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
/*   This file contains templates for pHILE+ configuration table.      */
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
#ifndef _PHILECFG_H
#define _PHILECFG_H

/*=====================================================================*/
/* pHILE+ Configuration table structure                                */
/*=====================================================================*/
typedef struct pHILEConfigTable
    {
    void (*fc_phile)();              /* Address of pHILE+ module */
    void *fc_data;                   /* Address of pHILE+ data area */
    unsigned long fc_datasize;       /* Size of pHILE+ data area */
    unsigned long fc_logbsize;       /* Block size (base-2 exponent) */
    unsigned long fc_nbuf;           /* Number of cache buffers */
    unsigned long fc_nmount;         /* Max # of mounted volumes */
    unsigned long fc_nfcb;           /* Max # of opened files per system */
    unsigned long fc_ncfile;         /* Max # of opened files per task */
    unsigned long fc_ndnlc;          /* Max # of cached directory entries */
    unsigned long fc_msdos;          /* MS-DOS volume mount flag */
    unsigned long fc_cdrom;          /* CD-ROM volume mount flag */
    unsigned long res[5];            /* Must be 0 */
    } pHILE_CT;

#endif

#if __cplusplus
}
#endif
