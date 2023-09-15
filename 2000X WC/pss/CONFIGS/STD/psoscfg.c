/* $Header:   K:/APPS/PVCS Pro/PSS68k.222/CONFIGS/STD/psoscfg.c_v   1.1   Apr 29 1999 15:11:58   lmarkure  $ */
/* @(#) pSOSystem/68K V2.2.2: configs/psoscfg.c (68k) 2.92 97/11/10 17:08:55 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  configs/std/psoscfg.c                                    */
/*   DATE:    97/11/10                                                 */
/*   PURPOSE: pSOS+ and pSOS+m configuration file                      */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1997, Integrated Systems, Inc.           */
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
/*   pSOS component.  Many configurations are possible, based on       */
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
 1.1   04/29/99 LAM     fixed per old version of psos

*/

#ifdef __cplusplus
    #if __cplusplus
extern "C" {
    #endif
#endif

#include "sys_conf.h"
/*---------------------------------------------------------------------*/
/* This flag is cleared during .bss clearing at startup time.  It is   */
/* set to 1 by the task start callout in this module.                  */
/*---------------------------------------------------------------------*/
unsigned long PsosUpFlag;

#if SC_PSOS || SC_PSOSM

#include "bsp.h"
#include <bspfuncs.h>
#include <configs.h>
#include <sysvars.h>

/*---------------------------------------------------------------------*/
/* KC_ROOTPRI should be defined in sys_conf.h.  However, the           */
/* sys_conf.h files in some of the older sample applications do not    */
/* contain this definition.  In order to maintain compatibility,       */
/* it is defined here if it has not been defined in sys_conf.h.        */
/* It is preferable that it be defined in sys_conf.h, and you should   */
/* note that this "default" definition will probably be removed from   */
/* this file in future versions of pSOSystem!                          */
/*---------------------------------------------------------------------*/
#ifndef KC_ROOTPRI
#define KC_ROOTPRI 230
#endif

#if SC_PROFILER
 
#undef KC_STARTCO
#undef KC_DELETECO
#undef KC_SWITCHCO
 
extern void __prof_tstart_callout();
extern void __prof_switch_callout();
extern void __prof_tdelete_callout();
 
#define KC_STARTCO     ((void (*)()) __prof_tstart_callout)
#define KC_DELETECO    ((void (*)()) __prof_tdelete_callout)
#define KC_SWITCHCO    ((void (*)()) __prof_switch_callout)
 
#endif

#if ((SC_PSOS != USEROM) && (SC_PSOSM != USEROM))


#if ((BSP_CPU == 68000) || (BSP_CPU == 68302))

     #if SC_PSOSM
         #define PSOS_CODE psos0m
         #define PSOS_SVC  psos0m_svc
         #define PSOS_IO   psos0m_io
         #define PSOS_IRET psos0m_iret
     #else
         #define PSOS_CODE psos0
         #define PSOS_SVC  psos0_svc
         #define PSOS_IO   psos0_io
         #define PSOS_IRET psos0_iret
     #endif /* SC_PSOSM */

#elif ((BSP_CPU == 68010) || (BSP_CPU == 68332) || (BSP_CPU == 68340) \
     || (BSP_CPU == 68070))

     #if SC_PSOSM
         #define PSOS_CODE psos1m
         #define PSOS_SVC  psos1m_svc
         #define PSOS_IO   psos1m_io
         #define PSOS_IRET psos1m_iret
     #else
         #define PSOS_CODE psos1
         #define PSOS_SVC  psos1_svc
         #define PSOS_IO   psos1_io
         #define PSOS_IRET psos1_iret
     #endif /* SC_PSOSM */

#elif ((BSP_CPU == 68020) || (BSP_CPU == 68030) || (BSP_CPU == 68040))

     #if SC_PSOSM
         #define PSOS_CODE psos2m
         #define PSOS_SVC  psos2m_svc
         #define PSOS_IO   psos2m_io
         #define PSOS_IRET psos2m_iret
     #else
         #define PSOS_CODE psos2
         #define PSOS_SVC  psos2_svc
         #define PSOS_IO   psos2_io
         #define PSOS_IRET psos2_iret
     #endif /* SC_PSOSM */

#elif (BSP_CPU == 68060)

     #if SC_PSOSM
         #define PSOS_CODE psos6m
         #define PSOS_SVC  psos6m_svc
         #define PSOS_IO   psos6m_io
         #define PSOS_IRET psos6m_iret
     #else
         #define PSOS_CODE psos6
         #define PSOS_SVC  psos6_svc
         #define PSOS_IO   psos6_io
         #define PSOS_IRET psos6_iret
     #endif /* SC_PSOSM */

#elif (BSP_CPU == 68360)

     #if SC_PSOSM
         #define PSOS_CODE psos360m
         #define PSOS_SVC  psos360m_svc
         #define PSOS_IO   psos360m_io
         #define PSOS_IRET psos360m_iret
     #else
         #define PSOS_CODE psos360
         #define PSOS_SVC  psos360_svc
         #define PSOS_IO   psos360_io
         #define PSOS_IRET psos360_iret
     #endif /* SC_PSOSM */

#endif

#endif

#define ALIGN(addr, boundary) ((addr + boundary - 1) & ~(boundary - 1))

#define PS_ENTRY(offset) (ENTRY_START_OFFSET + ((offset) * ENTRY_LENGTH))

extern void PSOS_CODE(void),PSOS_SVC(void),PSOS_IO(void),PSOS_IRET(void);
extern void ki_call (void);

static void  TaskStartCallout(unsigned long Tid, void *TcbPtr);

/*---------------------------------------------------------------------*/
/* pSOS+ configuration table.  The definitions for this are contained  */
/* in "configs.h".                                                     */
/*---------------------------------------------------------------------*/
pSOS_CT PsosCfg;

extern NODE_CT *oldanchor;

struct pSOS_IO_Jump_Table PsosIO[SC_DEVMAX + 1];

MP_CT MultiprocCfg;

extern void root(void);

extern UCHAR *SetUpDrivers(UCHAR *);

extern const char MemErrMsg[];

/***********************************************************************/
/* PsosSetup: Setup pSOS+ or pSOS+m componet                           */
/*                                                                     */
/*      INPUTS: FreeMemPtr pointer to free memory area that can be     */
/*              used to allocate memory for this componet. In the case */
/*              of pSOS+ and pSOS+m all remaining memory will be       */
/*              allocated to region 0.                                 */
/*                                                                     */
/*              NodeCfg pointer to the systems node configuration      */
/*              table. This will be used to set the psosct and mp_ct   */
/*              elements in the table.                                 */
/*                                                                     */
/*     RETURNS: The new FreeMemPtr is returned.                        */
/*                                                                     */
/*        NOTE: This function should be the last function called in    */
/*              the components initialization because it will use all  */
/*              of the remaining memory to allocate pSOS region 0.     */
/*                                                                     */
/***********************************************************************/
UCHAR *PsosSetup(UCHAR *FreeMemPtr,  NODE_CT *NodeCfg)
{
ULONG rsize, rn0max, tmp;
int i;

void *pSOS_tmp;


#if ((SC_PSOS == USEROM) || (SC_PSOSM == USEROM))
#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PSOS or SC_PSOSM USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

pSOS_tmp = (void *)0;
if(oldanchor && oldanchor->psosct && oldanchor->psosct->kc_psoscode)
    pSOS_tmp = (void *) (oldanchor->psosct->kc_psoscode);
else
    {
    SysInitFail("ROM is missing pSOS+.");
    }

#else

pSOS_tmp = (void *)PSOS_CODE;

#endif


/*---------------------------------------------------------------------*/
/* Set pSOS component trap vectors.                                    */
/*---------------------------------------------------------------------*/

SysSetVector(V_TRAP11, PSOS_SVC, NO_WRAPPER);
SysSetVector(V_TRAP12, PSOS_IO, NO_WRAPPER);
SysSetVector(V_TRAP13, PSOS_IRET, NO_WRAPPER);


/*---------------------------------------------------------------------*/
/* Initializethe pSOS I/O driver table to all "illegal" drivers.       */
/*---------------------------------------------------------------------*/
for (i = 0; i <= SC_DEVMAX; i++)
    {
    PsosIO[i].dev_init  = (void (*)(struct ioparms *))-1;
    PsosIO[i].dev_open  = (void (*)(struct ioparms *))-1;
    PsosIO[i].dev_close = (void (*)(struct ioparms *))-1;
    PsosIO[i].dev_read  = (void (*)(struct ioparms *))-1;
    PsosIO[i].dev_write = (void (*)(struct ioparms *))-1;
    PsosIO[i].dev_ioctl = (void (*)(struct ioparms *))-1;
    }

/*---------------------------------------------------------------------*/
/* Set up the pSOS I/O driver table for drivers supplied.              */
/* NOTE: This must be done before kc_rn0sadr is set because some of    */
/*       the drivers may need to allocate memory for their use.        */
/*---------------------------------------------------------------------*/
FreeMemPtr = SetUpDrivers(FreeMemPtr);

/*---------------------------------------------------------------------*/
/* Build the pSOS+ configuration tables.  Note that we hand over       */
/* all remaining memory to region 0.                                   */
/* XRAY tries to read 48 bytes from the stack for updating the display.*/
/* The idle task is allocated its stack space from the highest         */
/* addresses in region 0. If one tries to scope the idle task and      */
/* region 0 extends to the highest DRAM address on the board a bus     */
/* error occurs because XRAY tries to read 48 bytes of memory where    */
/* none is avilable. To avoid this problem the length of region 0 has  */
/* been truncated by 64 bytes.                                         */
/*---------------------------------------------------------------------*/
#if ((SC_PSOS == USEROM) || (SC_PSOSM == USEROM))
if(oldanchor && oldanchor->psosct && oldanchor->psosct->kc_psoscode)
    PsosCfg.kc_psoscode = oldanchor->psosct->kc_psoscode;
else
    {
    SysInitFail("ROM is missing pSOS+.");
    }
#else
PsosCfg.kc_psoscode = (void (*)())pSOS_tmp;
#endif
tmp = (ULONG)FreeMemPtr;
tmp = ALIGN(tmp, 4);         /* Align to long-word boundary */

PsosCfg.kc_rn0sadr = (void *)tmp;

#if SC_RAM_SIZE
    if (tmp > SC_RAM_SIZE + BSP_RAM_BASE)
        SysInitFail(MemErrMsg);
    rsize = (SC_RAM_SIZE + BSP_RAM_BASE) - (tmp + 64);
#else
    if (tmp > RamSize() + BSP_RAM_BASE)
        SysInitFail(MemErrMsg);
    rsize = (RamSize() + (ULONG)BSP_RAM_BASE) - (tmp + 64);
#endif  /* SC_RAM_SIZE */

/*---------------------------------------------------------------------*/
/* Since region 0 size cannot be greather than 32,767 times the unit   */
/* size calculate the max unit size then choose the lesser of the max  */
/* unit size or the rest of memory.                                    */
/*---------------------------------------------------------------------*/
rn0max = KC_RN0USIZE * ((1 << 15) -1);
PsosCfg.kc_rn0len = (rsize > rn0max) ? rn0max : rsize;

PsosCfg.kc_rn0usize = KC_RN0USIZE;
PsosCfg.kc_ntask = KC_NTASK;
PsosCfg.kc_nqueue = KC_NQUEUE;
PsosCfg.kc_nsema4 = KC_NSEMA4;
PsosCfg.kc_nmsgbuf = KC_NMSGBUF;
PsosCfg.kc_ntimer = KC_NTIMER;
PsosCfg.kc_nlocobj = KC_NLOCOBJ;
PsosCfg.kc_ticks2sec = KC_TICKS2SEC;
PsosCfg.kc_ticks2slice = KC_TICKS2SLICE;
PsosCfg.kc_nio = SC_DEVMAX + 1;
PsosCfg.kc_iojtable = PsosIO;
PsosCfg.kc_sysstk   = KC_SYSSTK;
PsosCfg.kc_rootsadr = root;
PsosCfg.kc_rootsstk = KC_ROOTSSTK;
PsosCfg.kc_rootustk = KC_ROOTUSTK;
PsosCfg.kc_rootmode = KC_ROOTMODE;
PsosCfg.kc_startco = TaskStartCallout;
PsosCfg.kc_deleteco = KC_DELETECO;
PsosCfg.kc_switchco = KC_SWITCHCO;
PsosCfg.kc_fatal = KC_FATAL;
#if (BSP_CPU == 68360)
    PsosCfg.kc_idleco = Idle360;
    PsosCfg.kc_rtcinit = Rtc360Init;
#endif
PsosCfg.kc_rootpri = KC_ROOTPRI;

NodeCfg->psosct = &PsosCfg;

#if SC_PSOSM
    if (SysVars.Kism)
        {
        /*-------------------------------------------------------------*/
        /* Set up the multi-processor configuration table.             */
        /*-------------------------------------------------------------*/
        MultiprocCfg.mc_nodenum = SysVars.SmNode;
        MultiprocCfg.mc_kicode  = ((void (*)()) ki_call);
        MultiprocCfg.mc_nnode   = SysVars.Kism;

        MultiprocCfg.mc_nglbobj = MC_NGLBOBJ;
        MultiprocCfg.mc_nagent  = MC_NAGENT;
        MultiprocCfg.mc_flags   = MC_FLAGS;
        MultiprocCfg.mc_roster  = MC_ROSTER;

        MultiprocCfg.mc_dprext =
            (void *) SmemLocal2Bus ((void *) BSP_RAM_BASE);
        MultiprocCfg.mc_dprint = (void *)(BSP_RAM_BASE);
        MultiprocCfg.mc_dprlen = RamSize();
        MultiprocCfg.mc_kimaxbuf = MC_KIMAXBUF; /* size not # of buffs! */
        MultiprocCfg.mc_asyncerr = MC_ASYNCERR;

        NodeCfg->mp_ct = &MultiprocCfg;
        }
#endif /* SC_PSOSM */
return(FreeMemPtr);
}

/***********************************************************************/
/* TaskStartCallout: Called whenever a task is started                 */
/*                                                                     */
/*      INPUTS: Tid: TID of task being started                         */
/*              TcbPtr: Address of task's TCB (Task Control Block)     */
/*        NOTE: Sets PsosUpFlag, and calls user handler if supplied    */
/*                                                                     */
/***********************************************************************/
static void TaskStartCallout(unsigned long Tid, void *TcbPtr)
{
static void (*callout)(ULONG, void *) = (void (*)(ULONG, void *)) KC_STARTCO;
PsosUpFlag = 1;

if (callout)
    (*callout)(Tid, TcbPtr);
}

/***********************************************************************/
/* InstallDriver: Adds a device driver to PsosIO table                 */
/*                                                                     */
/*  INPUTS:                                                            */
/*  unsigned short major_number    device major number                 */
/*  void (*dev_init)(),            device init procedure               */
/*  void (*dev_open)(),            device open procedure               */
/*  void (*dev_close)(),           device close procedure              */
/*  void (*dev_read)(),            device read procedure               */
/*  void (*dev_write)(),           device write procedure              */
/*  void (*dev_ioctl)(),           device control procedure            */
/*  unsigned long rsvd1,           reserved                            */
/*  unsigned short rsvd2)          reserved                            */
/*  unsigned short  flags;         Set to auto initialize the device   */
/*                                                                     */
/*     RETURNS: 0 if successfull 1 if major number out of range        */
/*     NOTE(S): assumes SC_DEVMAX defined in sys_conf.h                */
/*              This function is only useful before pSOS+ has been     */
/*              initialized.                                           */
/*                                                                     */
/***********************************************************************/
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
    unsigned short  flags)
{
if ((major_number == 0) || (major_number > SC_DEVMAX))
    {
    SysInitFail("Cannot install driver; major number out of range");
    }
else if (PsosIO[major_number].dev_init != (void (*)())-1)
    {
    SysInitFail("Duplicate major device numbers encountered");
    }
else
    {
    PsosIO[major_number].dev_init = dev_init;
    PsosIO[major_number].dev_open = dev_open;
    PsosIO[major_number].dev_close = dev_close;
    PsosIO[major_number].dev_read = dev_read;
    PsosIO[major_number].dev_write = dev_write;
    PsosIO[major_number].dev_ioctl = dev_ioctl;
    PsosIO[major_number].rsvd1 = rsvd1;
    PsosIO[major_number].rsvd2 = rsvd2;
    PsosIO[major_number].flags = flags;
    return;
    }
}

#else
    static void stub(void){}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
