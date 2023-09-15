/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\pnacfg.h_v   1.0   Mar 29 1999 13:51:02   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/pnacfg.h (68k ghs) 2.16 98/01/23 10:48:10 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/pnacfg.h                                         */
/*   DATE:    98/01/23                                                 */
/*   PURPOSE: Configuration table structure templates                  */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*         Copyright 1993 - 1998, Integrated Systems, Inc.             */
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
/*   This file contains templates for pNA+ configuration table.        */
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
#ifndef _PNACFG_H
#define _PNACFG_H

/*=====================================================================*/
/* pNA+ sub-component configuration table                              */
/*=====================================================================*/
typedef struct
  {
  long unused;
  struct nr_cfg *nr_cfg;             /* pRPC+ Cfg. Table */
  long reserved[6];                  /* for future use */
  } pNA_SCT;

/*=====================================================================*/
/* pNA+ configuration table                                            */
/*=====================================================================*/
typedef struct pNAConfigTable
    {
    void (*nc_pna)();               /* addr of pNA code module */
    void *nc_data;                  /* addr of pNA data area */
    long nc_datasize;               /* size of pNA data area */
    long nc_nni;                    /* size of pNA NI Table */
    struct ni_init *nc_ini;         /* ptr to initial pNA NI table */
    long nc_nroute;                 /* size of pNA Routing Table */
    struct route *nc_iroute;        /* ptr to initial pNA routing table */
    long nc_defgn;                  /* addr of default gate node */
    long nc_narp;                   /* size of pNA ARP table */
    struct arp *nc_iarp;            /* ptr to initial pNA ARP table */
    void (*nc_signal)();            /* ptr to signal handling routine */
    long nc_defuid;                 /* Default User ID of a task */
    long nc_defgid;                 /* Default Group ID of a task */
    char *nc_hostname;              /* Hostname of the node */
    long nc_nhentry;                /* Number of Host table entries */
    struct htentry *nc_ihtab;       /* Pointer to initial host table */
    pNA_SCT *nc_sct;                /* addr of sub-component cfg. table*/
    long nc_mblks;                  /* Number of mblks */
    struct pna_bufcfg *nc_bcfg;     /* Buffer configuration table */
    long nc_nsockets;               /* Number of sockets  */
    long nc_ndescs;                 /* Number of descriptors per task */
    long nc_nmc_socs;               /* Number of multicast sockets */
    long nc_nmc_memb;               /* Number of multicast group memberships */
    long nc_nnode_id;               /* network node ID or Router ID */
    long reserved[3];               /* reserved for future use */
    } pNA_CT;

#endif

#if __cplusplus
}
#endif
