/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\prpccfg.h_v   1.0   Mar 29 1999 13:51:04   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/prpccfg.h 2.1 93/10/21 10:05:28 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/prpccfg.h                                        */
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
/*   This file contains templates for pRPC+ configuration table.       */
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
#ifndef _PRPCCFG_H
#define _PRPCCFG_H

/*=====================================================================*/
/* pRPC+ Configuration table                                           */
/*=====================================================================*/
typedef struct nr_cfg
    {
    void (*nr_code)();               /* pRPC+ code address */
    char *nr_data;                   /* Address of pRPC+ data area */
    long nr_datasize;                /* Length of pRPC+ data area */
    long reserved[10];               /* Reserved entries of pRPC+ */
    } pRPC_CT;

#endif

#if __cplusplus
}
#endif
