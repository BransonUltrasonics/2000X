/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\prepccfg.c_v   1.0   Mar 29 1999 13:41:00   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: configs/prepccfg.c (std) 2.13 96/12/05 16:32:34 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  configs/std/prepccfg.c                                   */
/*   DATE:    96/12/05                                                 */
/*   PURPOSE: pREPC+ configuration file                                */
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
/*   pREPC+ componet.  Many configurations are possible, based on      */
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

#if (SC_PREPC)

#include "bsp.h"
#include <bspfuncs.h>
#include <configs.h>

extern void prepc(void);

UCHAR DevStrTmpdir[10], DevStrSerial[10];

/*---------------------------------------------------------------------*/
/* pHILE+ configuration table.  The definitions for this is            */
/* contained in <configs.h>.                                           */
/*---------------------------------------------------------------------*/
pREPC_CT PrepcCfg;
extern NODE_CT *oldanchor;

/***********************************************************************/
/* MakeDeviceString: Format a device number into ASCII device name     */
/*                   string                                            */
/*                                                                     */
/*      INPUTS: DeviceNr: Device number                                */
/*              DeviceStringPtr: Pointer to buffer for string          */
/*        NOTE: Cannot handle major device # greater than 9            */
/*                                                                     */
/***********************************************************************/
#if (SC_DEV_RAMDISK || SC_DEV_SCSI || SC_DEV_IDE || \
     (SC_DEV_SERIAL && !LC_STDIN)  || \
     (SC_DEV_SERIAL && !LC_STDOUT) || \
     (SC_DEV_SERIAL && !LC_STDERR) )

void MakeDeviceString(ULONG DeviceNr, UCHAR *DeviceStringPtr)
{
if (((DeviceNr >> 16) & 0xFFFF) > 9)
   SysInitFail("MakeDeviceString in sysinit.c cannot format devs > 9");

DeviceStringPtr[0] = (DeviceNr >> 16) + '0';
DeviceStringPtr[1] = '.';
DeviceStringPtr[2] = '0';
DeviceStringPtr[3] = 0;
}

#endif

/***********************************************************************/
/* PrepcSetup: Setup pREPC+ componet                                   */
/*                                                                     */
/*      INPUTS: FreeMemPtr pointer to free memory area that can be     */
/*              used to allocate memory for this componet.             */
/*                                                                     */
/*              NodeCfg pointer to the systems node configuration      */
/*              table. This will be used to set the prepct             */
/*              element in the table.                                  */
/*                                                                     */
/*     RETURNS: The new FreeMemPtr is returned.                        */
/*                                                                     */
/***********************************************************************/
UCHAR *PrepcSetup(UCHAR *FreeMemPtr,  NODE_CT *NodeCfg)
{
/*---------------------------------------------------------------------*/
/* Build the pREPC+ configuration table                                */
/*---------------------------------------------------------------------*/
#if (SC_PREPC == USEROM)
#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PREPC USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

if(oldanchor && oldanchor->prepct && oldanchor->prepct->lc_code)
    PrepcCfg.lc_code = oldanchor->prepct->lc_code;
else
    {
    SysInitFail("ROM is missing pREPC+.");
    }
#else
PrepcCfg.lc_code = prepc;
#endif
PrepcCfg.lc_data = (char *)0;
PrepcCfg.lc_datasize = 0;
PrepcCfg.lc_bufsiz = LC_BUFSIZ;
PrepcCfg.lc_numfiles = LC_NUMFILES;
PrepcCfg.lc_waitopt = LC_WAITOPT;
PrepcCfg.lc_timeopt = LC_TIMEOPT;

#if SC_DEV_RAMDISK
    MakeDeviceString(DEV_RAMDISK, DevStrTmpdir);
#elif SC_DEV_SCSI
    MakeDeviceString(DEV_SCSI, DevStrTmpdir);
#elif SC_DEV_IDE
    MakeDeviceString(DEV_IDE, DevStrTmpdir);
#else
    DevStrTmpdir[0] = 0;
#endif

PrepcCfg.lc_tempdir = (char *)DevStrTmpdir;

#if SC_DEV_SERIAL
    MakeDeviceString(DEV_SERIAL, DevStrSerial);
#else
    DevStrTmpdir[0] = 0;
#endif

PrepcCfg.lc_stdin = (char *)DevStrSerial;
PrepcCfg.lc_stdout = (char *)DevStrSerial;
PrepcCfg.lc_stderr = (char *)DevStrSerial;

PrepcCfg.lc_ssize = LC_SSIZE;

NodeCfg->prepct = &PrepcCfg;

return(FreeMemPtr);
}

#else
    static void stub(void){}
#endif

#if __cplusplus
}
#endif
