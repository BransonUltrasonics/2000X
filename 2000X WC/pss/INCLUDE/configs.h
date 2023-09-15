/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\configs.h_v   1.0   Mar 29 1999 13:50:54   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/configs.h (ghs) 1.33 98/01/23 10:31:46 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/configs.h                                        */
/*   DATE:    98/01/23                                                 */
/*   PURPOSE: Configuration table structure templates                  */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*          Copyright 1991 - 1998, Integrated Systems, Inc.            */
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
/*   This file contains includes for templates for all of the          */
/*   component configuration tables.                                   */
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
#ifndef _CONFIGS_H
#define _CONFIGS_H

#include <psos.h>
#include <psoscfg.h>
#include <probecfg.h>
#include <philecfg.h>
#include <prepccfg.h>
#include <prpccfg.h>
#include <pnacfg.h>
#include <psecfg.h>
#include <pmontcfg.h>


/*---------------------------------------------------------------------*/
/* Node Configuration Table Structure                                  */
/*---------------------------------------------------------------------*/
typedef struct NodeConfigTable
    {
    unsigned long cputype;      /* CPU type */
    MP_CT         *mp_ct;       /* pointer to Multi-proc config table */
    pSOS_CT       *psosct;      /* pointer to pSOS+ config table */
    pROBE_CT      *probect;     /* pointer to pROBE+ config table */
    pHILE_CT      *philect;     /* pointer to pHILE+ config table */
    pREPC_CT      *prepct;      /* pointer to pREPC+ config table */
    unsigned long rsvd1;        /* Unused entry */
    pNA_CT        *pnact;       /* pointer to pNA+ config table */
    pSE_CT        *psect;       /* pointer to pSE+ config table */
    pMONT_CT      *pmct;        /* pointer to pMONT+ config table */
    unsigned long rsvd2[2];     /* Unused entries */
    } NODE_CT;

#endif  /* _CONFIGS_H */

#if __cplusplus
}
#endif
