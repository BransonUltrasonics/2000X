/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\prpccfg.c_v   1.0   Mar 29 1999 13:41:02   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: configs/prpccfg.c 2.8 97/09/17 08:53:15 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  configs/std/prpccfg.c                                    */
/*   DATE:    97/09/17                                                 */
/*   PURPOSE: pRPC+ configuration file                                 */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1996, Integrated Systems, Inc.           */
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
/*   This code in this module controls the configuration of the        */
/*   pRPC+ componet.  Many configurations are possible, based on       */
/*   these inputs:                                                     */
/*     * Options selected in "sys_conf.h"                              */
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

#include "sys_conf.h"

#if (SC_PRPC)

#include <configs.h>
#include "bsp.h"
#include <bspfuncs.h>

extern void prpc(void);

/*---------------------------------------------------------------------*/
/* pRPC+ configuration table.  The definitions for this is             */
/* contained in <configs.h>.                                           */
/*---------------------------------------------------------------------*/
pRPC_CT PrpcCfg;

extern pNA_SCT PnaSubCfg;

extern NODE_CT *oldanchor;

#if (SC_PREPC == NO)
#error "pREP/C is required in order to use pRPC"
#endif
#if (SC_PNA == NO)
#error "pRPC+ component may not exist without the pNA+ component."
#endif

#if (SC_PRPC && (SC_PRPC == USEROM) && (BSP_CPUFAMILY == FAMILY_POWERPC))
#error "pRPC cannot be used from ROM. It is not a PIC/PID!."
#endif

/***********************************************************************/
/* PrpcSetup: Setup pNA+ componet                                      */
/*                                                                     */
/*      INPUTS: FreeMemPtr pointer to free memory area that can be     */
/*              used to allocate memory for this componet.             */
/*                                                                     */
/*              NodeCfg pointer to the systems node configuration      */
/*              table. This will not be used.                          */
/*                                                                     */
/*     RETURNS: The new FreeMemPtr is returned.                        */
/*                                                                     */
/***********************************************************************/
UCHAR *PrpcSetup(UCHAR *FreeMemPtr,  NODE_CT *NodeCfg)
{
static NODE_CT *unused_NodeCfg;
unused_NodeCfg = NodeCfg;

/*---------------------------------------------------------------------*/
/* Build the pRPC configuration table                                  */
/*---------------------------------------------------------------------*/
#if (NR_DATA && NR_DATASIZE)
    PrpcCfg.nr_data = (char *)NR_DATA;
    PrpcCfg.nr_datasize = NR_DATASIZE;
#elif NR_DATASIZE
    PrpcCfg.nr_data = (char *)FreeMemPtr;
    PrpcCfg.nr_datasize = NR_DATASIZE;
    FreeMemPtr = FreeMemPtr + NR_DATASIZE;
#endif

#if (SC_PRPC == USEROM)
#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PRPC USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

if(oldanchor
  && oldanchor->pnact
  && oldanchor->pnact->nc_sct
  && oldanchor->pnact->nc_sct->nr_cfg->nr_code)
    PrpcCfg.nr_code = oldanchor->pnact->nc_sct->nr_cfg->nr_code;
else
    {
    SysInitFail("ROM is missing pRPC+.");
    }
#else
PrpcCfg.nr_code = prpc;
#endif

PnaSubCfg.nr_cfg = &PrpcCfg;

return(FreeMemPtr);
}

#else
    static void stub(void){}
#endif

#if __cplusplus
}
#endif
