/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\loader.h_v   1.0   Mar 29 1999 13:50:58   ofingere  $ */
/* @(#) $Id: loader.h,v 1.5 1996/01/17 00:20:28 aakash Exp $ */
/* @(#) pSOSystem/68K V2.2.1: include/loader.h */
/**********************************************************************/
/*                                                                    */
/*   MODULE:  $RCSfile: loader.h,v $                                  */
/*   DATE:    $Date:   Mar 29 1999 13:50:58  $                            */
/*   PURPOSE: Structure typedefs, function prototypes, macros, and    */
/*            symbol definitions for pSOS loader version 1.0          */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*                 Copyright 1993, Integrated Systems, Inc.           */
/*                         ALL RIGHTS RESERVED                        */
/*                                                                    */
/*   Permission is hereby granted to licensees of Integrated Systems, */
/*   Inc. products to use or abstract this computer program for the   */
/*   sole purpose of implementing a product based on Integrated       */
/*   Systems, Inc. products.  No other rights to reproduce, use,      */
/*   or disseminate this program, whether in part or in whole, are    */
/*   granted.                                                         */
/*                                                                    */
/*   Integrated Systems, Inc. makes no representation or warranties   */
/*   with respect to the performance of this computer program, and    */
/*   specifically disclaims any responsibility for any damages,       */
/*   special or consequential, connected with its use.                */
/*                                                                    */
/**********************************************************************/
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version

*/

#if __cplusplus
extern "C" {
#endif

/**********************************************************************/
/* Don't allow this file to be included more than once.               */
/**********************************************************************/
#ifndef _LOADER_H
#define _LOADER_H

#include <psos.h>

#ifndef NULL
#define NULL 0
#endif

/***********************************************************************/
/* Defines Typedefs and Structures used by the loader                  */
/***********************************************************************/

typedef struct ofm_ctrl {
        char  *name;        /* Symbolic Name of the OFM */
        ULONG (*init)();    /* Pointer to OFM initialization routine */
        ULONG (*gethdr)();  /* Pointer to routine for reading header */
        ULONG (*load)();    /* Pointer to the load routine */
        ULONG (*unload)();  /* Pointer to the unload routine */
        ULONG (*release)(); /* Pointer to the release routine */
} OFM_CTRL;

typedef struct task_info {
        char   name[4];        /* Name of the task to be created */
        ULONG  priority;       /* Task priority */
        ULONG  sstack_sz;      /* Supervisor stack size */
        ULONG  ustack_sz;      /* User stack size */
        ULONG  create_flags;   /* Flags used by t_create */
        ULONG  start_mode;     /* Mode used by t_start */
        void   (*entry)();     /* Task entry point */
} TASK_INFO;

#define LD_SECNAMELEN        16

typedef struct secn_info {
        char   name[LD_SECNAMELEN]; /* Section Name */
        ULONG  type;                /* Section Type */
        ULONG  size;                /* Section Size */
        ULONG  base;                /* Load address in memory */
} SECN_INFO;

/*
 * of_info_t structure is used by load() to pass various information regarding
 * the object file to the user.
 */
typedef struct of_info {
        int   desc;             /* Descriptor identifies loaded file */
        char  format[5];        /* Object File Format */
        char  code_type;        /* Type of code -  ABS/RELOC/PIC */
        char  filler[2];        /* Reserved, Don't use */
        int   nsecns;           /* # of sections */
        SECN_INFO *secn_info;   /* Detailed info about each section */
        TASK_INFO task_info;    /* Info needed to create and start the task */
} OF_INFO;

/*
 * code_type values:
 */
#define LD_ABSOLUTE        'A'	/* Absolute and Position Dependent code */
#define LD_RELOCATABLE     'R'	/* Relocatable or Position Independent code */
#define LD_PIC             'P'	/* Position-Independent code */

/*
 * Definitions of flags passed to load()
 */
#define LD_DESC_PHILE      0x0000	/* fd is a pHILE+ file descriptor */
#define LD_DESC_DEV        0x0001	/* fd is a device number */

#define LD_LOAD_DEF        0x0000	/* Load using the defaults */
#define LD_GET_INFO        0x0002	/* Load just the object file info */
#define LD_LOAD_MOD        0x0004	/* Load using the modified of_info */

#define LD_DESC_MASK       0x0001	/* Mask for finding DESC type */
#define LD_TYPE_MASK       0x0006	/* Mask for finding LOAD type */

/***********************************************************************/
/* Loader Function Calls                                               */
/***********************************************************************/

extern ULONG load(unsigned long fd, unsigned long flags, OF_INFO **of_info);
extern ULONG unload(OF_INFO *of_info);
extern ULONG release(OF_INFO *of_info);

/***********************************************************************/
/* Errors returned by loader calls                                     */
/***********************************************************************/

#define ERR_LD           0x01200100

#define ERR_NO_OFM       (ERR_LD | 0x01)
#define ERR_OFM_FULL     (ERR_LD | 0x02)
#define ERR_BADOP        (ERR_LD | 0x03)
#define ERR_INVALID      (ERR_LD | 0x04)
#define ERR_INTERNAL     (ERR_LD | 0x05)
#define ERR_SYNTAX       (ERR_LD | 0x06)
#define ERR_UNSUPP       (ERR_LD | 0x07)
#define ERR_NOT_EXEC     (ERR_LD | 0x08)
#define ERR_UNKWNSZ      (ERR_LD | 0x09)
#define ERR_NOSYMTAB     (ERR_LD | 0x0A)
#define ERR_UNDEFSYM     (ERR_LD | 0x0B)
#define ERR_RELOC        (ERR_LD | 0x0C)

#endif /* _LOADER_H */

#if __cplusplus
}
#endif
