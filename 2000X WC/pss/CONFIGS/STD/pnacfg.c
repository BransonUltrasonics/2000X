/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\pnacfg.c_v   1.0   Mar 29 1999 13:41:00   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: configs/pnacfg.c (68k) 2.41 98/06/18 15:12:46 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  configs/std/pnacfg.c                                     */
/*   DATE:    98/06/18                                                 */
/*   PURPOSE: pNA+ configuration file                                  */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1998, Integrated Systems, Inc.           */
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
/*   pNA componet.  Many configurations are possible, based on         */
/*   these inputs:                                                     */
/*     * Options selected in "sys_conf.h"                              */
/*     * The capabilities of the board-support package being used,     */
/*       as defined in "bsp.h"                                         */
/*     * Answers given to questions in the startup configuration       */
/*       dialog, if it is enabled                                      */
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

/*---------------------------------------------------------------------*/
/* The following symbols should be defined in sys_conf.h.  However,    */
/* the sys_conf.h files in some of the older sample applications do    */
/* not contain these definitions.  In order to maintain compatibility, */
/* they are set to default values here if they have not been defined   */
/* defined in sys_conf.h.  It is preferable that these symbols be      */
/* defined in sys_conf.h, and you should note that these "default"     */
/* definitions will probably be removed from this file in future       */
/* versions of pSOSystem!                                              */
/*---------------------------------------------------------------------*/
#ifndef NC_MAX_BUFS
    #ifdef SE_MAX_GS_BUFS
    #define NC_MAX_BUFS SE_MAX_GS_BUFS
    #else
    #define NC_MAX_BUFS 4
    #endif
#endif

#ifndef NC_MBLKS
#define NC_MBLKS 300
#endif

#ifndef NC_NSOCKETS
#define NC_NSOCKETS  8
#endif

#ifndef NC_NDESCS
#define NC_NDESCS 4
#endif

#ifndef NC_SIGNAL
#define NC_SIGNAL 0
#endif

#if SC_PNA

#include "bsp.h"
#include <bspfuncs.h>
#include <configs.h>
#include <pna.h>
#include <sysvars.h>

extern void pna(void);

/*---------------------------------------------------------------------*/
/* pNA+ component configuration table.  The definitions for this is    */
/* contained in <configs.h>.                                           */
/*---------------------------------------------------------------------*/
pNA_CT PnaCfg;

struct pna_bufcfg pna_bufcfg[NC_MAX_BUFS +1];

struct ni_init PnaIft[NC_NNI + 1];

#if (SC_PX || SC_PRPC)
    pNA_SCT PnaSubCfg;
#endif

#define PNA_DATA_SIZE 0xA000

UCHAR *SetUpNI(UCHAR *);

extern const char MemErrMsg[];

extern NODE_CT *oldanchor;

/***********************************************************************/
/* PnaSetup: Setup pNA+ component                                       */
/*                                                                     */
/*      INPUTS: FreeMemPtr pointer to free memory area that can be     */
/*              used to allocate memory for this componet.             */
/*                                                                     */
/*              NodeCfg pointer to the systems node configuration      */
/*              table. This will be used to set the pnact              */
/*              element in the table.                                  */
/*                                                                     */
/*     RETURNS: The new FreeMemPtr is returned.                        */
/*                                                                     */
/***********************************************************************/
UCHAR *PnaSetup(UCHAR *FreeMemPtr,  NODE_CT *NodeCfg)
{
unsigned long i;

/*---------------------------------------------------------------------*/
/* Build the pNA configuration tables                                  */
/*---------------------------------------------------------------------*/
#if (SC_PNA == USEROM)

#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PNA USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

if(oldanchor && oldanchor->pnact && oldanchor->pnact->nc_pna)
    PnaCfg.nc_pna = oldanchor->pnact->nc_pna;
else
    {
    SysInitFail("ROM is missing pNA+");
    }
#else
PnaCfg.nc_pna = pna;
#endif

#if (SC_PROBE_DEBUG)
    /*-----------------------------------------------------------------*/
    /* If the pROBE remote debugger module is configured (and pNA too) */
    /* assume they will need a pNA data area.  Even if they configure  */
    /* pROBE standalone mode in the startup dialog, they can use the   */
    /* FL RBUG ON command to go into remote debug mode before pSOS is  */
    /* initialized.  Thus we *must* set aside a pNA data area.         */
    /*-----------------------------------------------------------------*/
    #if !(NC_DATA && NC_DATASIZE)
        i = 0;
        PnaCfg.nc_data = FreeMemPtr;
        PnaCfg.nc_datasize = PNA_DATA_SIZE;
        while(i<PNA_DATA_SIZE)
            FreeMemPtr[i++] = 0;
        FreeMemPtr = FreeMemPtr + PNA_DATA_SIZE;

        #if SC_RAM_SIZE
            if (FreeMemPtr >
              (UCHAR *)(SC_RAM_SIZE + BSP_RAM_BASE))
                SysInitFail(MemErrMsg);
        #else
            if (FreeMemPtr > (UCHAR *)(RamSize() + BSP_RAM_BASE))
                SysInitFail(MemErrMsg);
        #endif

    #endif
#endif


i = 0;
#if NC_BUFS_0
    pna_bufcfg[i].pna_nbuffers = NC_BUFS_0;
    pna_bufcfg[i].pna_bsize = 0;
    i++;
#endif
    
#if NC_BUFS_32
    pna_bufcfg[i].pna_nbuffers = NC_BUFS_32;
    pna_bufcfg[i].pna_bsize = 32;
    i++;
#endif

#if NC_BUFS_64
    pna_bufcfg[i].pna_nbuffers = NC_BUFS_64;
    pna_bufcfg[i].pna_bsize = 64;
    i++;
#endif

#if NC_BUFS_128
    pna_bufcfg[i].pna_nbuffers = NC_BUFS_128;
    pna_bufcfg[i].pna_bsize = 128;
    i++;
#endif

#if NC_BUFS_256
    pna_bufcfg[i].pna_nbuffers = NC_BUFS_256;
    pna_bufcfg[i].pna_bsize = 256;
    i++;
#endif

#if NC_BUFS_512
    pna_bufcfg[i].pna_nbuffers = NC_BUFS_512;
    pna_bufcfg[i].pna_bsize = 512;
    i++;
#endif

#if NC_BUFS_1024
    pna_bufcfg[i].pna_nbuffers = NC_BUFS_1024;
    pna_bufcfg[i].pna_bsize = 1024;
    i++;
#endif

#if NC_BUFS_2048
    pna_bufcfg[i].pna_nbuffers = NC_BUFS_2048;
    pna_bufcfg[i].pna_bsize = 2048;
    i++;
#endif

pna_bufcfg[i].pna_nbuffers = 0;
pna_bufcfg[i].pna_bsize = 0;
    


#if (NC_DATA && NC_DATASIZE)
    PnaCfg.nc_data = (void *)NC_DATA;
    PnaCfg.nc_datasize = NC_DATASIZE;
#endif

PnaCfg.nc_nni = NC_NNI;
PnaCfg.nc_ini = PnaIft;
PnaCfg.nc_nroute = NC_NROUTE;
PnaCfg.nc_defgn = htonl((ULONG) (SysVars.DefGtwyIP));
PnaCfg.nc_narp = NC_NARP;

PnaCfg.nc_signal = NC_SIGNAL;

PnaCfg.nc_defuid = NC_DEFUID;
PnaCfg.nc_defgid = NC_DEFGID;
PnaCfg.nc_hostname = NC_HOSTNAME;

PnaCfg.nc_nhentry = NC_NHENTRY;

#if (SC_PX || SC_PRPC)
    PnaCfg.nc_sct = &PnaSubCfg;
#endif

PnaCfg.nc_mblks = NC_MBLKS;
PnaCfg.nc_bcfg = pna_bufcfg;

PnaCfg.nc_nsockets = NC_NSOCKETS;
PnaCfg.nc_ndescs = NC_NDESCS;

/*---------------------------------------------------------------------*/
/* Added for New pNA+ MULTICASTING.                                    */
/*---------------------------------------------------------------------*/
#ifdef NC_NMCSOCS
    PnaCfg.nc_nmc_socs = NC_NMCSOCS;
#else
    PnaCfg.nc_nmc_socs = 0;
#endif

#ifdef NC_NMCMEMB
    PnaCfg.nc_nmc_memb = NC_NMCMEMB;
#else
    PnaCfg.nc_nmc_memb = 0;
#endif

/*---------------------------------------------------------------------*/
/* Added for New pNA+ Network NODE ID.                                 */
/*---------------------------------------------------------------------*/
#ifdef NC_NNODEID
    PnaCfg.nc_nnode_id = NC_NNODEID;
#else
    PnaCfg.nc_nnode_id = 0;
#endif

NodeCfg->pnact = &PnaCfg;

/*---------------------------------------------------------------------*/
/* Build the pNA initial interface table                               */
/*---------------------------------------------------------------------*/
FreeMemPtr = SetUpNI(FreeMemPtr);

return (FreeMemPtr);
}


/***********************************************************************/
/* InstallNi: Installs a Ni driver                                     */
/*                                                                     */
/*      INPUTS:                                                        */
/*              int (*entry)();        address of NI entry point       */
/*              int ipadd;             IP address                      */
/*              int mtu;               maximum transmission length     */
/*              int hwalen;            length of hardware address      */
/*              int flags;             intErface flags                 */
/*              int subnetaddr;        subnet mask                     */
/*              int dstipaddr;         destination ip address          */
/*                                                                     */
/*     RETURNS: Void                                                   */
/*                                                                     */
/***********************************************************************/
void InstallNi(int (*entry)(),
                 int ipadd,
                 int mtu,
                 int hwalen,
                 int flags,
                 int subnetaddr,
                 int dstipaddr)
{
int indx;
struct ni_init *ni_ptr;

/*---------------------------------------------------------------------*/
/* Advance ni_ptr to the first empty spot in the NI table, and ensure  */
/* that the table is not already full.                                 */
/*---------------------------------------------------------------------*/
ni_ptr = PnaIft;
indx = 0;
while (ni_ptr->entry != (int (*)())0)
    {
    ni_ptr++;
    indx++;
    }
if (indx >= NC_NNI) 
    SysInitFail("Number of network interfaces > NC_NNI");


/*---------------------------------------------------------------------*/
/* Found an empty slot.  Fill in the values for interface being        */
/* installed.                                                          */
/*---------------------------------------------------------------------*/
ni_ptr->entry = (int (*)())entry;
ni_ptr->ipadd = htonl((ULONG)ipadd);
ni_ptr->mtu = mtu;
ni_ptr->hwalen = hwalen;
ni_ptr->flags = flags;
ni_ptr->subnetaddr = htonl((ULONG)subnetaddr);
ni_ptr->dstipaddr = htonl((ULONG)dstipaddr);
ni_ptr->reserved[0] = 0;
}

#else
    static void stub(void){}
#endif

#if __cplusplus
}
#endif
