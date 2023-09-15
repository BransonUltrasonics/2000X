/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\psecfg.h_v   1.0   Mar 29 1999 13:51:04   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/psecfg.h 2.5 96/02/14 06:04:07 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/psecfg.h                                         */
/*   DATE:    96/02/14                                                 */
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
/*   This file contains templates for pSE+ configuration table.        */
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
#ifndef _PSECFG_H
#define _PSECFG_H

/*=====================================================================*/
/* pSE+ Configuration Table Structure                                  */
/*=====================================================================*/

#define DT_REGULAR   0x01
#define DT_CLONE     0x02
#define DT_MODULE    0x03

typedef struct pTLIConfigTable
    {
    void      *ti_code_start;  /* start of pTLI+ code */
    } pTLI_CT;

typedef struct pSKTConfigTable
    {
    void      *si_code_start;  /* start of pSKT+ code */
    void      *si_netconfig;   /* pointer to netconfig table */
    } pSKT_CT;

typedef struct {
    pTLI_CT *tli_ct;        /* address of pTLI table */
    pSKT_CT *skt_ct;        /* address of pSKT table */
    long reserved[14];      /* reserved for future use, must be 0 */
} pseappsc_t;

typedef struct {
    char   *drv_name;
    long   drv_type;                 /* type (regular/clone/module) */
    struct streamtab *drv_streamtab; /* addr of streamtab structure */
    void   *drv_private;             /* driver's private data */
    long   reserved[1];              /* reserved, must be zero */
} psedrvparam_t;

typedef struct {
    void   (*drv_init)();      /* routine to be called at init time */
    psedrvparam_t *drv_param;  /* ptr to driver/module params */
} psedrvcfg_t;

typedef struct {
    long   n_bufs;          /* # of buffers */
    long   b_size;          /* size of buffer */
} psebufcfg_t;

typedef struct pSEConfigTable {
    void   *se_code_start;   /* start of pSE code */
    char   *se_data_area;    /* start of pSE data area (must be supplied) */
    long   se_data_size;     /* size of pSE data area (must be at least 3K) */
    long   se_task_prio;     /* priority for pSE task */
    long   se_stack_size;    /* stack size for pSE task */
    long   se_def_uid;       /* default user id */
    long   se_def_gid;       /* default group id */
    long   *se_lbolt;        /* ptr to the lbolt variable */
    pseappsc_t *se_appsc_ct; /* ptr to application sub-components cfg table */
    psedrvcfg_t *se_drvcfg;  /* ptr to array of modules configurations */
    psebufcfg_t *se_bufcfg;  /* ptr to array of STREAMS buffers configuration */
    long   se_n_fds;         /* max # of system-wide stream descriptors */
    long   se_n_taskfds;     /* max # of per-task stream descriptors */
    long   se_n_links;       /* max # of multiplexing links */
    long   se_n_timeouts;    /* max # of timeout requests */
    long   se_n_bufcalls;    /* max # of bufcall requests */
    long   se_n_queues;      /* # of queues */
    long   se_n_mblks;       /* # of mblk buffers */
    long   se_monmask;       /* monitor options mask */
    void   (*se_monproc)();  /* monitor options callout address */
    long   se_reserved[2];   /* reserved for future use, must be 0 */
} pSE_CT;


#endif

#if __cplusplus
}
#endif
