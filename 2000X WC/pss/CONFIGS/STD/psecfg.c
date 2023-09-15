/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\psecfg.c_v   1.0   Mar 29 1999 13:41:02   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: configs/psecfg.c 2.19 98/06/18 15:15:52 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  configs/std/psecfg.c                                     */
/*   DATE:    98/06/18                                                 */
/*   PURPOSE: pSE+ configuration file                                  */
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
/*   pSE+ componet.  Many configurations are possible, based on        */
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

#if (SC_PSE)

#include <configs.h>
#include "bsp.h"
#include <bspfuncs.h>
#if (SC_PSKT)
#include <sys/poll.h>
#include <sys/socket.h>
#endif

extern void pse(void);
extern void ptli(void);
extern void pskt(void);
long lbolt;                 /* lbolt variable */
long HZ;                    /* clock tick interrupt frequency */

#if (SC_PSE && (SC_PSE == USEROM) && (BSP_CPUFAMILY == FAMILY_POWERPC))
#error "pSE cannot be used from ROM. It is not a PIC/PID!."
#endif

#if (SC_PTLI && (SC_PTLI == USEROM) && (BSP_CPUFAMILY == FAMILY_POWERPC))
#error "pTLI cannot be used from ROM. It is not a PIC/PID!."
#endif

#if (SC_PSKT && (SC_PSKT == USEROM) && (BSP_CPUFAMILY == FAMILY_POWERPC))
#error "pSKT cannot be used from ROM. It is not a PIC/PID!."
#endif

/*---------------------------------------------------------------------*/
/* Backward compatibility defines to allow applications with the old   */
/* buffer defines to work correctly with the new define names.         */
/*---------------------------------------------------------------------*/
#if !defined(SE_NBUFS_0) && defined(NBUFS_0)
#define SE_NBUFS_0 NBUFS_0
#endif

#if !defined(SE_NBUFS_32) && defined(NBUFS_32)
#define SE_NBUFS_32 NBUFS_32
#endif

#if !defined(SE_NBUFS_64) && defined(NBUFS_64)
#define SE_NBUFS_64 NBUFS_64
#endif

#if !defined(SE_NBUFS_128) && defined(NBUFS_128)
#define SE_NBUFS_128 NBUFS_128
#endif

#if !defined(SE_NBUFS_256) && defined(NBUFS_256)
#define SE_NBUFS_256 NBUFS_256
#endif

#if !defined(SE_NBUFS_512) && defined(NBUFS_512)
#define SE_NBUFS_512 NBUFS_512
#endif

#if !defined(SE_NBUFS_1024) && defined(NBUFS_1024)
#define SE_NBUFS_1024 NBUFS_1024
#endif

#if !defined(SE_NBUFS_2048) && defined(NBUFS_2048)
#define SE_NBUFS_2048 NBUFS_2048
#endif

#if !defined(SE_NBUFS_4096) && defined(NBUFS_4096)
#define SE_NBUFS_4096 NBUFS_4096
#endif

#if !defined(SE_MAX_BUFS) && defined(SE_MAX_PSE_STRBUFS)
#define SE_MAX_BUFS SE_MAX_PSE_STRBUFS
#endif

#if !defined(SE_MAX_MODULES) && defined(SE_MAX_PSE_MODULES)
#define SE_MAX_MODULES SE_MAX_PSE_MODULES
#endif

#if !defined(SE_SHARE_NI) && defined(SC_SHARE_NI)
#define SE_SHARE_NI SC_SHARE_NI
#endif

/*---------------------------------------------------------------------*/
/* pSE+ configuration table.  The definitions for this is              */
/* contained in <configs.h>.                                           */
/*---------------------------------------------------------------------*/
pSE_CT PseCfg;

extern NODE_CT *oldanchor;

pseappsc_t appsc_ct;
psedrvcfg_t pse_modules[SE_MAX_MODULES + 1];
psebufcfg_t pse_strbufs[SE_MAX_BUFS + 1];

#if (SC_PTLI)
    pTLI_CT ptli_ct;
    extern void TIRW_modinit();
    extern struct streamtab tirwinfo;
    const psedrvparam_t tirw_mod  = {"tirw",  DT_MODULE, &tirwinfo,  0, 0};
    extern void TIMOD_modinit();
    extern struct streamtab timodinfo;
    const psedrvparam_t timod_mod = {"timod", DT_MODULE, &timodinfo, 0, 0};
#endif

#if (SC_PSKT)
    pSKT_CT pskt_ct;
    extern void SOMOD_modinit();
    extern struct streamtab somodinfo;
    const psedrvparam_t somod_mod = {"sockmod",  DT_MODULE, &somodinfo,  0, 0};
    const struct netconfig pskt_netconfig[] = {
#if (SC_DEV_OTCP)
#include <sys/spna_nc.h>
#endif
#if (SC_DEV_SOSI)
#include <sys/sosi_nc.h>
#endif
        {0, 0, 0, 0, 0}
    };
#endif

#if (!SC_PSE && SC_PSKT)
#error "pSKT+ component may not exist without the pSE+ component.");
#endif
#if (!SC_PSE && SC_PTLI)
#error "pTLI+ component may not exist without the pSE+ component.");
#endif

/***********************************************************************/
/* PseSetup: Setup pSE+ componet                                       */
/*                                                                     */
/*      INPUTS: FreeMemPtr pointer to free memory area that can be     */
/*              used to allocate memory for this componet.             */
/*                                                                     */
/*              NodeCfg pointer to the systems node configuration      */
/*              table. This will be used to set the psect              */
/*              element in the table.                                  */
/*                                                                     */
/*     RETURNS: The new FreeMemPtr is returned.                        */
/*                                                                     */
/***********************************************************************/
UCHAR *PseSetup(UCHAR *FreeMemPtr,  NODE_CT *NodeCfg)
{
int i;

HZ = KC_TICKS2SEC;

/*---------------------------------------------------------------------*/
/* Build the pSE configuration table                                   */
/*---------------------------------------------------------------------*/

    /*-----------------------------------------------------------------*/
    /* setup TLI, if installed                                         */
    /*-----------------------------------------------------------------*/

i = 0;
#if SC_PTLI
#if (SC_PTLI == USEROM)
#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PTLI USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

if(oldanchor
  && oldanchor->psect
  && oldanchor->psect->se_appsc_ct
  && oldanchor->psect->se_appsc_ct->tli_ct
  && oldanchor->psect->se_appsc_ct->tli_ct->ti_code_start)
   ptli_ct.ti_code_start = oldanchor->psect->se_appsc_ct->tli_ct->ti_code_start;
else
    {
    SysInitFail("ROM is missing pTLI+ module.");
    }
#else
ptli_ct.ti_code_start = (void *)ptli;   /* start of the code */
#endif
appsc_ct.tli_ct = &ptli_ct;             /* address of pTLI table */

pse_modules[i].drv_init = TIMOD_modinit;
pse_modules[i].drv_param = (psedrvparam_t *)&timod_mod;
i++;

pse_modules[i].drv_init = TIRW_modinit;
pse_modules[i].drv_param = (psedrvparam_t *)&tirw_mod;
i++;
#endif

    /*-----------------------------------------------------------------*/
    /* setup SOCKET, if installed                                      */
    /*-----------------------------------------------------------------*/
#if SC_PSKT
#if (SC_PSKT == USEROM)
#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PSKT USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

if(oldanchor
  && oldanchor->psect
  && oldanchor->psect->se_appsc_ct
  && oldanchor->psect->se_appsc_ct->skt_ct
  && oldanchor->psect->se_appsc_ct->skt_ct->si_code_start)
   pskt_ct.si_code_start = oldanchor->psect->se_appsc_ct->skt_ct->si_code_start;
else
    {
    SysInitFail("ROM is missing pSKT+ module.");
    }
#else
pskt_ct.si_code_start = (void *)pskt;   /* start of the code */
#endif
pskt_ct.si_netconfig = (void *)pskt_netconfig; /* socket netconfig */
appsc_ct.skt_ct = &pskt_ct;             /* address of pSKT table */

pse_modules[i].drv_init = SOMOD_modinit;
pse_modules[i].drv_param = (psedrvparam_t *)&somod_mod;
i++;
#endif

    /*-----------------------------------------------------------------*/
    /* end of STREAMS modules                                          */
    /*-----------------------------------------------------------------*/
    pse_modules[i].drv_init = 0;
    pse_modules[i].drv_param = 0;

    /*-----------------------------------------------------------------*/
    /* setup STREAMS buffers configuration                             */
    /*-----------------------------------------------------------------*/
    i = 0;
#if SE_NBUFS_0
    pse_strbufs[i].n_bufs = SE_NBUFS_0;
    pse_strbufs[i].b_size = 0;
    i++;
#endif

#if SE_NBUFS_32
    pse_strbufs[i].n_bufs = SE_NBUFS_32;
    pse_strbufs[i].b_size = 32;
    i++;
#endif

#if SE_NBUFS_64
    pse_strbufs[i].n_bufs = SE_NBUFS_64;
    pse_strbufs[i].b_size = 64;
    i++;
#endif

#if SE_NBUFS_128
    pse_strbufs[i].n_bufs = SE_NBUFS_128;
    pse_strbufs[i].b_size = 128;
    i++;
#endif

#if SE_NBUFS_256
    pse_strbufs[i].n_bufs = SE_NBUFS_256;
    pse_strbufs[i].b_size = 256;
    i++;
#endif

#if SE_NBUFS_512
    pse_strbufs[i].n_bufs = SE_NBUFS_512;
    pse_strbufs[i].b_size = 512;
    i++;
#endif

#if SE_NBUFS_1024
    pse_strbufs[i].n_bufs = SE_NBUFS_1024;
    pse_strbufs[i].b_size = 1024;
    i++;
#endif

#if SE_NBUFS_2048
    pse_strbufs[i].n_bufs = SE_NBUFS_2048;
    pse_strbufs[i].b_size = 2048;
    i++;
#endif

#if SE_NBUFS_4096
    pse_strbufs[i].n_bufs = SE_NBUFS_4096;
    pse_strbufs[i].b_size = 4096;
    i++;
#endif

pse_strbufs[i].n_bufs = 0;
pse_strbufs[i].b_size = 0;

    /*-----------------------------------------------------------------*/
    /* initialize the main configuration structure of pSE              */
    /*-----------------------------------------------------------------*/
PseCfg.se_data_area = (char *)FreeMemPtr;
PseCfg.se_data_size = SE_DATA_SIZE;
FreeMemPtr = FreeMemPtr + SE_DATA_SIZE;

PseCfg.se_task_prio = SE_TASK_PRIO;
PseCfg.se_stack_size = SE_STACK_SIZE;
PseCfg.se_def_uid = SE_DEF_UID;
PseCfg.se_def_gid = SE_DEF_GID;
PseCfg.se_lbolt = &lbolt;
PseCfg.se_appsc_ct = &appsc_ct;
PseCfg.se_drvcfg = pse_modules;
PseCfg.se_bufcfg = pse_strbufs;
PseCfg.se_n_fds = SE_N_FDS;
PseCfg.se_n_taskfds = SE_N_TASKFDS;
PseCfg.se_n_links = SE_N_LINKS;
PseCfg.se_n_timeouts = SE_N_TIMEOUTS;
PseCfg.se_n_bufcalls = SE_N_BUFCALLS;
PseCfg.se_n_queues = SE_N_QUEUES;
PseCfg.se_n_mblks = SE_N_MBLKS;
PseCfg.se_monmask = 0;
PseCfg.se_monproc = (void (*)())0;
PseCfg.se_reserved[0] = 0;
PseCfg.se_reserved[1] = 0;

#if (SC_PSE == USEROM)
#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PSE USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

if(oldanchor && oldanchor->psect && oldanchor->psect->se_code_start)
    PseCfg.se_code_start = oldanchor->psect->se_code_start;
else
    {
    SysInitFail("ROM is missing pSE+ module.");
    }
#else
PseCfg.se_code_start = (void *)pse;
#endif

    /*-----------------------------------------------------------------*/
    /* place pSE into the Node Configuration Table                     */
    /*-----------------------------------------------------------------*/
NodeCfg->psect = &PseCfg;

return(FreeMemPtr);
}

#else
    static void stub(void){}
#endif

#if __cplusplus
}
#endif
