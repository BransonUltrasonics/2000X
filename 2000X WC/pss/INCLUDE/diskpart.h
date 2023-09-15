/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\diskpart.h_v   1.0   Mar 29 1999 13:50:56   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/disk_part.h (&U&) 2.2 96/12/12 15:33:01 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  disk_part.h                                              */
/*   DATE:    96/12/12                                                 */
/*   PURPOSE: provides the structure of a disk partitation table.      */
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
/*   NOTE: This table conforms to MS_DOS systems and should not be     */
/*         changed.                                                    */
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
#ifndef _DISKPART_H
#define _DISKPART_H
 
struct  ide_part {
        unsigned char   boot_ind;       /* Boot indication, 80h=active  */
        unsigned char   start_head;     /* Starting head number         */
        unsigned char   start_sect;     /* Starting sector and cyl (hi) */
        unsigned char   start_cyl;      /* Starting cylinder (low)      */
        unsigned char   sys_ind;        /* System Indicator             */
        unsigned char   end_head;       /* Ending head                  */
        unsigned char   end_sect;       /* Ending sector and cyl (high) */
        unsigned char   end_cyl;        /* Ending cylinder (low)        */
        unsigned long   start_rsect;    /* Starting relative sector     */
        unsigned long   nsects;         /* Number of sectors in partit. */
};

#endif   /* _DISKPART_H */
 
#if __cplusplus
    }
#endif
