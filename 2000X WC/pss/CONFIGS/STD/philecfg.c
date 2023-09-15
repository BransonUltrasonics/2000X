/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\philecfg.c_v   1.0   Mar 29 1999 13:41:00   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: configs/philecfg.c (&U&) 2.10 96/12/05 16:32:10 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  configs/std/philecfg.c                                   */
/*   DATE:    96/12/05                                                 */
/*   PURPOSE: pHILE+ configuration file                                */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1993, Integrated Systems, Inc.           */
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
/*   pHILE+ componet.  Many configurations are possible, based on      */
/*   these inputs:                                                     */
/*     * Options selected in "sys_conf.h"                              */
/*                                                                     */
/***********************************************************************/
/* --------------------------------- REVISIONS -------------------------
 Rev # Date     Author 	Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI 	Original Version

 */
#if __cplusplus
extern "C" {
#endif

#include "sys_conf.h"

#if (SC_PHILE || SC_DEV_RAMDISK || SC_DEV_SCSI)

#include <configs.h>
#include "bsp.h"
#include <bspfuncs.h>

#if SC_PHILE
    extern void phile(void);
#endif

/*---------------------------------------------------------------------*/
/* pHILE+ configuration table.  The definitions for this is            */
/* contained in <configs.h>.                                           */
/*---------------------------------------------------------------------*/
pHILE_CT PhileCfg;
extern NODE_CT *oldanchor;

/***********************************************************************/
/* PhileSetup: Setup pHILE+ componet                                   */
/*                                                                     */
/*      INPUTS: FreeMemPtr pointer to free memory area that can be     */
/*              used to allocate memory for this componet.             */
/*                                                                     */
/*              NodeCfg pointer to the systems node configuration      */
/*              table. This will be used to set the philect            */
/*              element in the table.                                  */
/*                                                                     */
/*     RETURNS: The new FreeMemPtr is returned.                        */
/*                                                                     */
/*     NOTE: This function may also be called if SCSI_DEV or RAM_DEV   */
/*           is defined and not SC_PHILE. In those cases only the      */
/*           pHILE_CT will be set up (with out setting the fc_phile    */
/*           element).                                                 */
/*                                                                     */
/***********************************************************************/
UCHAR *PhileSetup(UCHAR *FreeMemPtr,  NODE_CT *NodeCfg)
{
/*---------------------------------------------------------------------*/
/* Build the pHILE+ configuration table.                               */
/*---------------------------------------------------------------------*/
#if SC_PHILE
#if (SC_PHILE == USEROM)
#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PHILE USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

if(oldanchor && oldanchor->philect && oldanchor->philect->fc_phile)
    PhileCfg.fc_phile = oldanchor->philect->fc_phile;
else
    {
    SysInitFail("ROM is missing pHILE+.");
    }
#else
    PhileCfg.fc_phile = phile;
#endif
#endif
PhileCfg.fc_data = 0;
PhileCfg.fc_datasize = 0;
PhileCfg.fc_logbsize = FC_LOGBSIZE;
PhileCfg.fc_nbuf = FC_NBUF;
PhileCfg.fc_nmount = FC_NMOUNT;
PhileCfg.fc_nfcb = FC_NFCB;
PhileCfg.fc_ncfile = FC_NCFILE;

#ifdef FC_MSDOS
    PhileCfg.fc_msdos = FC_MSDOS;
#else
    PhileCfg.fc_msdos = 0;
#endif

#ifdef FC_NDNLC
    PhileCfg.fc_ndnlc = FC_NDNLC;
#else
    PhileCfg.fc_ndnlc = 0;
#endif

#ifdef FC_CDROM
    PhileCfg.fc_cdrom = FC_CDROM;
#else
    PhileCfg.fc_cdrom = 0;
#endif

#if SC_PHILE
    NodeCfg->philect = &PhileCfg;
#endif
return(FreeMemPtr);
}

#else
    static void stub(void){}
#endif

#if __cplusplus
}
#endif
