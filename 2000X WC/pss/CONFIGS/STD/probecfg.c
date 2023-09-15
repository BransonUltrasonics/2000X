/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\probecfg.c_v   1.0   Mar 29 1999 13:41:02   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: configs/probecfg_ghs.c (68k) 1.58 98/06/18 15:14:02 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  configs/std/probecfg.c                                   */
/*   DATE:    98/06/18                                                 */
/*   PURPOSE: pROBE+ configuration file                                */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*          Copyright 1994 - 1998, Integrated Systems, Inc.            */
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
/*   pROBE+ component.  Many configurations are possible, based on     */
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

#include "sys_conf.h"
#include "bsp.h"
#include <bspfuncs.h>
#include <machine.h>

#if (SC_PROBE)

#include <bsp.h>
#include <bspfuncs.h>
#include <configs.h>
#include <sysvars.h>

/*---------------------------------------------------------------------*/
/* Backward compatibility defines to allow applications with the old   */
/* pROBE+ defines to work correctly with the new define names.         */
/*---------------------------------------------------------------------*/
#if !defined(TD_BRKOPC) && defined(RC_BRKOPC)
#define TD_BRKOPC RC_BRKOPC
#endif

#if !defined(TD_ILEV) && defined(RC_ILEV)
#define TD_ILEV RC_ILEV
#endif

#if !defined(TD_FLAGS) && defined(RC_FLAGS)
#define TD_FLAGS RC_FLAGS
#endif

#if !defined(TD_DATASTART) && defined(RC_DATASTART)
#define TD_DATASTART RC_DATASTART
#endif

#if !defined(TD_DBGPRI)
#define TD_DBGPRI 244
#endif

#define  PS_DATA    0x800             /* Processor Services Data Area */
#define  PS_STACK   0x1000            /* Processor Services Stack Area */
#define  DI_DATA    0x100             /* Dis-Assembler Data Area      */
#define  CE_DATA    0x400             /* Console Interface Executive  */
#define  REL_DATA   0x1400            /* Reliability Layer Data Area  */
#define  RD_DATA    (0x1B00+REL_DATA) /* RBUG Data Area               */

#if BSP_NEW_SERIAL
    #define SerialPollOn     ProbeEntry
    #define SerialPollOff    ProbeExit
    #define RDISerialDrv     ProbeRbugIO
    #define SerialDriver     ProbeConIO
    long    ProbeConIO(ULONG mode, long *byte_cnt, char *buf_ptr);
#else
    static long   SerialDriver(ULONG mode, long *byte_cnt, char *buf_ptr);
#endif

#define INIT    0x11      /* SerialDriver mode parameter */
#define GET     0x14
#define PUT     0x12
#define STATUS  0x15
 
#define BREAK      2       /* SerialDriver return codes */
#define MORE       1
#define NO_MSG    -1
#define XMIT_ERR  -2
#define NO_IO     -3

#define ALIGN(addr, boundary) ((addr + boundary - 1) & ~(boundary - 1))

/*---------------------------------------------------------------------*/
/* Function Prototypes                                                 */
/*---------------------------------------------------------------------*/
extern long   pna_di(ULONG, long*, char*);
#if SC_RBUG_PORT
extern long   RDISerialDrv(ULONG, long*, char*);
#endif
extern void   SysBusError (void);
static void   ProbeStateChng(ULONG flags);

#ifdef SC_MMULIB
#   if SC_MMULIB
        extern void map_reco(void), map_rxco(void);
#   endif
#endif

#if (SC_PROBE == YES)

/*---------------------------------------------------------------------*/
/* pROBE+ entry points                                                 */
/*---------------------------------------------------------------------*/
extern void pROBE_mabrk(void);
extern void pROBE_baerr(void);
extern void pROBE_trace();
extern void pROBE_exce();
extern void pROBE_ibrk();

#endif

/*---------------------------------------------------------------------*/
/* Global Variables                                                    */
/*---------------------------------------------------------------------*/
pROBE_CT ProbeCfg;
extern NODE_CT *oldanchor;

#if (!SC_PROBE && SC_PROBE_DISASM)
#error "pROBE+ disassembly module may not exist without pROBE+ core.\n"
#endif
#if (!SC_PROBE && SC_PROBE_CIE)
#error "pROBE+ console module may not exist without pROBE+ core.\n"
#endif
#if (!SC_PROBE && SC_PROBE_QUERY)
#error "pROBE+ query module may not exist without pROBE+ core.\n"
#endif
#if (!SC_PROBE && SC_PROBE_DEBUG)
#error "pROBE+ debug module may not exist without pROBE+ core.\n"
#endif
#if (SC_PROBE && !SC_PROBE_CIE && !SC_PROBE_DEBUG)
#error "Either SC_PROBE_CIE or SC_PROBE_DEBUG should be present!"
#endif
#if (SC_PROBE_CIE && !SC_PROBE_CONSOLE)
#error "SC_PROBE_CIE requires SC_PROBE_CONSOLE to be set to some port# !"
#endif
#if (SC_PROBE_DEBUG && !SC_PNA && !SC_RBUG_PORT)
#error "If RBUG is Enabled, then set either of SC_PNA or SC_RBUG_PORT !"
#endif

/***********************************************************************/
/*  ProbeSetup: Setup the pROBE+ component                             */
/*                                                                     */
/*      INPUTS: FreeMem = pointer to free memory                       */
/*              node_ct_ptr = pointer to node configuration table      */
/*                                                                     */
/*     RETURNS: The new value of FreeMemPtr.                           */
/*        NOTE: This function should be called first if pROBE+ is      */
/*              used because it initializes all the interrupt vectors. */
/*                                                                     */
/***********************************************************************/
UCHAR *ProbeSetup(UCHAR *FreeMemPtr, NODE_CT *node_ct_ptr)
{
int vect_nr;
unsigned long tmp;
#if (SC_PNA)
    #if (SC_RBUG_PORT)
        unsigned long cnsl_present=1;
    #else
        unsigned long cnsl_present=0;
    #endif /* SC_RBUG_PORT */
#endif /* SC_PNA */

#if (SC_PROBE == USEROM)
        void *pROBE_tmp;
#endif

/*---------------------------------------------------------------------*/
/* If the user has supplied a starting point for pROBE+ data areas and */
/* stack (TD_DATASTART != 0) then use it as a starting point. If       */
/* TD_DATASTART == 0 then assume the user wants pROBE+ data and stack  */
/* to start at the current FreeMemPtr                                  */
/*---------------------------------------------------------------------*/
#if TD_DATASTART
    tmp = (ULONG)TD_DATASTART;
#else
    tmp = (ULONG) FreeMemPtr;
    tmp  = ALIGN(tmp, 4);
#endif

/*---------------------------------------------------------------------*/
/* Build the pROBE+ configuration table.                               */
/*---------------------------------------------------------------------*/
#if (SC_PROBE == USEROM)
#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PROBE USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

if(oldanchor && oldanchor->probect && oldanchor->probect->td_code)
    pROBE_tmp = ProbeCfg.td_code = oldanchor->probect->td_code;
else
    {
    SysInitFail("ROM is missing pROBE+ core.");
    }
#else
ProbeCfg.td_code = pROBE_Core;
#endif

ProbeCfg.td_brkopc = TD_BRKOPC;
ProbeCfg.td_flags = TD_FLAGS;

ProbeCfg.td_data = (ULONG *) tmp;
tmp += PS_DATA;

#if SC_PROBE_DISASM
#if (SC_PROBE_DISASM == USEROM)
#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PROBE_DISASM USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

if((ProbeCfg.td_disasm = oldanchor->probect->td_disasm) == (void *)0)
    {
    SysInitFail("ROM is missing pROBE+ disassembly module.");
    }
#else
    ProbeCfg.td_disasm = pROBE_Disasm;
#endif
    tmp += DI_DATA;
#else
    ProbeCfg.td_disasm = 0;
#endif

#if ((BSP_SERIAL || BSP_NEW_SERIAL) && SC_PROBE_CONSOLE && SC_PROBE_CIE) 
#if (SC_PROBE_CIE == USEROM)
#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PROBE_CIE USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

if((ProbeCfg.td_console = oldanchor->probect->td_console) == (void *)0)
    {
    SysInitFail("ROM is missing pROBE+ console module.");
    }
#else
    ProbeCfg.td_console = &pROBE_Console;   
#endif

ProbeCfg.td_drv0 = SerialDriver;
tmp += CE_DATA;

#else
    ProbeCfg.td_console = (void *)0;
    ProbeCfg.td_drv0 = (void *)0;
#endif

#if SC_PROBE_DEBUG
#if (SC_PROBE_DEBUG == USEROM)
#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PROBE_DEBUG USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

if((ProbeCfg.td_debug = oldanchor->probect->td_debug) == (void *)0)
    {
    SysInitFail("ROM is missing pROBE+ debug module.");
    }
#else
    ProbeCfg.td_debug = pROBE_Debug;
#endif

    ProbeCfg.td_drv1 = 0;
    tmp += RD_DATA;

#if (SC_PNA)

        if ((SysVars.DebugMode == DBG_XS) && !cnsl_present)
                SysInitFail("SC_RBUG_PORT should be set for DBG_XS mode");
        else if (SysVars.DebugMode != DBG_XS)

#if (SC_PNA == USEROM)
            {
            if(oldanchor && oldanchor->pnact && oldanchor->pnact->nc_pna)
                ProbeCfg.td_drv1 = (long (*)(ULONG,long*,char*))
                  ((ULONG)(oldanchor->pnact->nc_pna) +
                   (ENTRY_START_OFFSET + (PNA_DI_OFFSET * ENTRY_LENGTH)));
            else
                {
                SysInitFail("ROM Network Debugger is missing pNA+");
                }
            }
#else /* SC_PNA == USEROM */

            ProbeCfg.td_drv1 = pna_di;

#endif /* SC_PNA == USEROM */

#endif /* SC_PNA */

    #if (SC_RBUG_PORT)
        if (SysVars.DebugMode != DBG_XN)
            ProbeCfg.td_drv1 = RDISerialDrv;
    #endif

    if (ProbeCfg.td_drv1 == 0)
        SysInitFail("If SC_PROBE_DEBUG is set, then set either of SC_PNA or"
                    " SC_RBUG_PORT. Otherwise Set SC_PROBE_DEBUG to NO in"
                    "sys_conf.h!!!!");

    if( (!SC_PROBE_CIE) ||
        (SysVars.DebugMode == DBG_XS) || (SysVars.DebugMode == DBG_XN) ) 
        ProbeCfg.td_flags |= RBUG_MASK;    /* Turn on RBUG bit */

#else
    ProbeCfg.td_debug = 0;
    ProbeCfg.td_drv1 = 0;
#endif

#if SC_PROBE_QUERY
#if (SC_PROBE_QUERY == USEROM)
#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PROBE_QUERY USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

if((ProbeCfg.td_query = oldanchor->probect->td_query) == (void *)0)
    {
    SysInitFail("ROM is missing pROBE+ query module.");
    }
#else
    ProbeCfg.td_query = pROBE_Query;
#endif

#else
    ProbeCfg.td_query = 0;
#endif

tmp += PS_STACK;
ProbeCfg.td_stack = (ULONG *)tmp;

if (SysVars.DebugMode == DBG_AP)
    ProbeCfg.td_flags |= SMODE_MASK;

ProbeCfg.td_statechng = ProbeStateChng;

ProbeCfg.td_urcom = 0;
ProbeCfg.td_urwrite = 0;
ProbeCfg.td_reserved1[0] = 0;
ProbeCfg.td_reserved1[1] = 0;
ProbeCfg.td_reserved1[2] = 0;
ProbeCfg.td_reserved1[3] = 0;
ProbeCfg.td_reserved2[0] = 0;
ProbeCfg.td_reserved2[1] = 0;
ProbeCfg.td_reserved2[2] = 0;
ProbeCfg.td_reserved2[3] = 0;
ProbeCfg.td_reserved2[4] = 0;

/*---------------------------------------------------------------------*/
/* Install pROBE configuration table address in node config table.     */
/*---------------------------------------------------------------------*/
node_ct_ptr->probect = &ProbeCfg;

/*---------------------------------------------------------------------*/
/* Now set the pROBE exception vectors.  Start off by initializing all */
/* of them to point to the pROBE "reserved" entry                      */
/*---------------------------------------------------------------------*/

#if (SC_PROBE == USEROM)

if(pROBE_tmp)
    {

    /*-----------------------------------------------------------------*/
    /* Note here we exclude vector number 18, as that is the ROM       */
    /* updated address of the ROM's configuration table.               */
    /*-----------------------------------------------------------------*/
    for (vect_nr = 0; vect_nr < 256; vect_nr++)
        {
        if(vect_nr == (0x48 >> 2))
            continue;
        SysSetVector(vect_nr, (void *)((ULONG)pROBE_tmp + 0xe8), NO_WRAPPER);
        }
    SysSetVector(V_TRACE, (void *)((ULONG)pROBE_tmp + 0xf0), NO_WRAPPER);
    SysSetVector(V_TRAP1, (void *)((ULONG)pROBE_tmp + 0xa4), NO_WRAPPER);
    SysSetVector(V_BUSERR, SysBusError, NO_WRAPPER);
    SysSetVector(V_ADDRERR, (void *)((ULONG)pROBE_tmp + 0xec), NO_WRAPPER);
#if (BSP_CPU == 68360)
    SysSetVector(V_HDWBKPT, (void *)((ULONG)pROBE_tmp + 0xa8), NO_WRAPPER);
#endif
    }

#else

/*---------------------------------------------------------------------*/
/* Note here we exclude vector number 18, as that is the ROM updated   */
/* address of the ROM's configuration table, which must be preserved.  */
/*---------------------------------------------------------------------*/
for (vect_nr = 0; vect_nr < 256; vect_nr++)
    {
    if(vect_nr == (0x48 >> 2))
        continue;
    SysSetVector(vect_nr, pROBE_exce, NO_WRAPPER);
    }
SysSetVector(V_TRACE, pROBE_trace, NO_WRAPPER);
SysSetVector(V_TRAP1, pROBE_ibrk, NO_WRAPPER);
SysSetVector(V_BUSERR, SysBusError, NO_WRAPPER);
SysSetVector(V_ADDRERR, pROBE_baerr, NO_WRAPPER);
#if (BSP_CPU == 68360)
SysSetVector(V_HDWBKPT, pROBE_mabrk, NO_WRAPPER);
#endif

#endif

#if BSP_ABORTSW
    SysSetVector(V_ABORT, ClrAbortInt, MBRK_WRAPPER);
#endif


/*---------------------------------------------------------------------*/
/* If the user supplied TD_DATASTART then no memory from FreeMemPtr    */
/* was used so just return what we started with.                       */
/* If the user did not supply TD_DATASTART then memory from FreeMemPtr */
/* was used so the tmp variable is the new FreeMemPtr and return it.   */
/*---------------------------------------------------------------------*/
#if TD_DATASTART
    return (UCHAR *) FreeMemPtr;
#else
    return (UCHAR *) tmp;
#endif
}

/***********************************************************************/
/* ProbeStateChng: Change modes, etc, to match pROBE state changes     */
/*                                                                     */
/*      INPUTS: flags: bit-encoded flags indicating state changes      */
/*                                                                     */
/*                                                                     */
/***********************************************************************/
static void ProbeStateChng(unsigned long flags)
{
#if BSP_SERIAL && (SC_PROBE_CIE || SC_RBUG_PORT)
    if (flags & TASKING_PROBE)
        SerialPollOn();
    if (flags & TASKING_NORM)
        SerialPollOff();
#endif
#ifdef SC_MMULIB
#   if SC_MMULIB
        if (flags & MEMACCESS_PROBE)
           map_reco();

        if (flags & MEMACCESS_NORM)
           map_rxco();
#   endif
#endif
}

#if !BSP_NEW_SERIAL
/***********************************************************************/
/* SerialDriver: The serial interface for nuProbe                      */
/*                                                                     */
/*      INPUTS: mode     = INIT, PUT, GET, or STATUS                   */
/*              byte_cnt = byte count for PUT and GET                  */
/*              buf_ptr  = buffer pointer for PUT and GET              */
/*                                                                     */
/*     RETURNS:                                                        */
/*                                                                     */
/***********************************************************************/
static long SerialDriver(ULONG mode, long *byte_cnt, char *buf_ptr)
{
ULONG i;
int bc = *byte_cnt;
 
if (mode == INIT)
   {
   SerialPollInit();
   SerialPollOn();
   }
else
   {
   if (mode == PUT)
      {
      while (bc--)
            SerialPollConout(*buf_ptr++);
      }
   else
      {
      if (mode == GET)
         {
         if ((i = SerialPollConsts(0)) == 1)
            {
           *buf_ptr++ = SerialPollConin();
           *byte_cnt = 1;
            }
         else
            {
            if (i == 2)
               return (BREAK);
            else
               return (NO_MSG);
            }
         }
      else
         {
         if (mode == STATUS)
            {
            if ((i = SerialPollConsts(0)) == 2)
               return (BREAK);
            else
               return (NO_MSG);
            }
         }
      }
   }
 
return (SUCCESS);
}
#endif /* !BSP_NEW_SERIAL */

#else
    static int dummy;
#endif
