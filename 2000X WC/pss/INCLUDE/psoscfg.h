/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\psoscfg.h_v   1.0   Mar 29 1999 13:51:06   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/psoscfg.h (std) 2.23 97/11/10 15:52:17 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/psoscfg.h                                        */
/*   DATE:    97/11/10                                                 */
/*   PURPOSE: Configuration table structure templates                  */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*         Copyright 1993 - 1996, Integrated Systems, Inc.             */
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
/*   This file contains templates for pSOS+ configuration table.       */
/*                                                                     */
/***********************************************************************/
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version

*/

#ifdef __cplusplus
    #if __cplusplus
extern "C" {
    #endif
#endif

/*---------------------------------------------------------------------*/
/* Don't allow this file to be included more than once.                */
/*---------------------------------------------------------------------*/
#ifndef _PSOSCFG_H
#define _PSOSCFG_H

/*=====================================================================*/
/* Multiprocessor Configuration Table Structure                        */
/*=====================================================================*/
typedef struct MultiProcConfigTable
    {
    unsigned long mc_nodenum;   /* this node's node number */
    void     (*mc_kicode)();    /* addr of this node's kernel interface */
    unsigned long mc_nnode;     /* max number of nodes in system */
    unsigned long mc_nglbobj;   /* size of global obj table in each node */
    unsigned long mc_nagent;    /* number of RPC agents in this node */
    unsigned long mc_flags;     /* operating mode flags */
    void     (*mc_roster)();    /* address of user roster change callout */
    void *        mc_dprext;    /* dual-port RAM external starting address */
    void *        mc_dprint;    /* dual-port RAM internal starting address */
    unsigned long mc_dprlen;    /* dual-port RAM length in bytes */
    unsigned long mc_kimaxbuf;  /* maximum KI packet buffer length */
    void     (*mc_asyncerr)();  /* asynchronous calls error callout */
    unsigned long mc_reserved[6]; /* unused, set to 0 */
    } MP_CT;

/*=====================================================================*/
/* pSOS+ Configuration information                                     */
/*=====================================================================*/

/*---------------------------------------------------------------------*/
/* pSOS+ I/O switch table entry - the table is an array of these       */
/* structures                                                          */
/*---------------------------------------------------------------------*/
struct pSOS_IO_Jump_Table
    {
    void (*dev_init)(struct ioparms *); /* device init procedure */
    void (*dev_open)(struct ioparms *); /* device open procedure */
    void (*dev_close)(struct ioparms *);/* device close procedure */
    void (*dev_read)(struct ioparms *); /* device read procedure */
    void (*dev_write)(struct ioparms *);/* device write procedure */
    void (*dev_ioctl)(struct ioparms *);/* device control procedure */
    unsigned long rsvd1;                /* reserved, set to 0 */
    unsigned short rsvd2;               /* reserved, set to 0 */
    unsigned short flags;               /* If set to IO_AUTOINIT pSOS */
                                        /* will automatically call the */
                                        /* devices initialization */
                                        /* function */
    };

/*---------------------------------------------------------------------*/
/* pSOS+ configuration table                                           */
/*---------------------------------------------------------------------*/
typedef struct pSOSConfigTable
    {
    void (*kc_psoscode)();        /* start address of pSOS+ */
    void *kc_rn0sadr;             /* region 0 start address */
    unsigned long kc_rn0len;      /* region 0 length */
    unsigned long kc_rn0usize;    /* region 0 unit size */
    unsigned long kc_ntask;       /* max number of tasks */
    unsigned long kc_nqueue;      /* max number of message queues */
    unsigned long kc_nsema4;      /* max number of semaphores */
    unsigned long kc_nmsgbuf;     /* max number of message buffers */
    unsigned long kc_ntimer;      /* max number of timers */
    unsigned long kc_nlocobj;     /* max number of local objects */
    unsigned long kc_ticks2sec;   /* clock tick interrupt frequency */
    unsigned long kc_ticks2slice; /* time slice quantum, in ticks */
    unsigned long kc_nio;         /* num of I/O devices in system */
    struct pSOS_IO_Jump_Table *kc_iojtable;   /* addr of I/O switch table */
    unsigned long kc_sysstk;      /* pSOS+ system stack size (bytes) */
    void (*kc_rootsadr)();        /* ROOT start address */
    unsigned long kc_rootsstk;    /* ROOT supervisor stack size */
    unsigned long kc_rootustk;    /* ROOT user stack size */
    unsigned long kc_rootmode;    /* ROOT initial mode */
    void (*kc_startco)();         /* callout at task activation */
    void (*kc_deleteco)();        /* callout at task deletion */
    void (*kc_switchco)();        /* callout at task switch */
    void (*kc_fatal)();           /* fatal error handler address */
#if defined ARM || defined (__mips)
    unsigned long kc_reserved3[2];/* reserved */
#else
    void (*kc_idleco)();          /* idle task callout - 68360 only */
    void (*kc_rtcinit)();         /* real-time clock init callout */
                                  /* - 68360 only */
#endif
    unsigned long kc_reserved1;   /* reserved */
    unsigned long kc_rootpri;     /* ROOT task priority */
    unsigned long kc_reserved2[5];/* reserved for future use */
    } pSOS_CT;

/*---------------------------------------------------------------------*/
/* Prototype for call to InstallDriver that will setup driver in       */
/* the switch table.                                                   */
/*---------------------------------------------------------------------*/
void InstallDriver(
    unsigned short major_number,
    void (*dev_init)(struct ioparms *),
    void (*dev_open)(struct ioparms *),
    void (*dev_close)(struct ioparms *),
    void (*dev_read)(struct ioparms *),
    void (*dev_write)(struct ioparms *),
    void (*dev_ioctl)(struct ioparms *),
    unsigned long rsvd1,
    unsigned short rsvd2,
    unsigned short  flags);

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
