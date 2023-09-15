/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\pmontcfg.c_v   1.0   Mar 29 1999 13:41:00   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: configs/pmontcfg.c (std) 1.37 97/11/12 10:36:10 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  configs/std/pmontcfg.c                                   */
/*   DATE:    97/11/12                                                 */
/*   PURPOSE: pMONT+ configuration file                                */
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
/*   pMONT+ component.                                                 */
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

#ifndef SC_PMONT
#define SC_PMONT 0
#endif


#if SC_PMONT

#include <configs.h>
#include "bsp.h"
#include <bspfuncs.h>
#include <disi.h>
#include <diti.h>
#include <drv_intf.h>

extern void pmont(void);

unsigned long PmontBaudRate;
extern unsigned long SysBaud;
extern const ULONG baud_table[];

/*---------------------------------------------------------------------*/
/* pmont+ configuration table.  The definitions for this is            */
/* contained in <configs.h>.                                           */
/*---------------------------------------------------------------------*/
pMONT_CT pmontCfg;
extern NODE_CT *oldanchor;

/*---------------------------------------------------------------------*/
/* This variable specifies the baud rate to be used for the pMONT      */
/* serial channel.  It is used by drivers/console.c.  This method of   */
/* communicating the pMONT serial baud rate will be changed in V2.1.   */
/*---------------------------------------------------------------------*/

/***********************************************************************/
/* PmontSetup: Setup pmont+ component                                  */
/*                                                                     */
/*      INPUTS: FreeMemPtr pointer to free memory area that can be     */
/*              used to allocate memory for this component.            */
/*                                                                     */
/*              NodeCfg pointer to the systems node configuration      */
/*              table. This will be used to set the pmontct            */
/*              element in the table.                                  */
/*                                                                     */
/*     RETURNS: The new FreeMemPtr is returned.                        */
/*                                                                     */
/***********************************************************************/
UCHAR *PmontSetup(UCHAR *FreeMemPtr,  NODE_CT *NodeCfg)
{
#ifndef BSP_TIMER2
#define BSP_TIMER2 0
#endif
#ifndef PM_TIMER
#define PM_TIMER 0
#endif
/*---------------------------------------------------------------------*/
/* Build the pMONT+ configuration table.                               */
/*---------------------------------------------------------------------*/
#if ((BSP_TIMER2==YES) && (PM_TIMER==YES))
extern unsigned long tmFreq();
extern void tmReset();
extern unsigned long tmRead();
#endif

#if (SC_PMONT == USEROM)
#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PMONT USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

if(oldanchor && oldanchor->pmct && oldanchor->pmct->code)
    pmontCfg.code = oldanchor->pmct->code;
else
    {
    SysInitFail("ROM is missing pMONT+.");
    }
#else
  pmontCfg.code = pmont;
#endif

#if (PM_CMODE==1) && (SC_PNA==NO)
#error "You need to set SC_PNA to YES or PM_CMODE to 2."
#endif

#if ((PM_CMODE==2) && (PM_DEV==0))
#error "PM_DEV should be (>=1) or (<=BSP_SERIAL)"
#endif

#if (PM_CMODE==2) && ((DEV_SERIAL | PM_DEV) > (BSP_SERIAL | DEV_SERIAL))
#error "PM_DEV should not be greater than BSP_SERIAL.\
 Board has insufficient Serial Ports."
#endif

pmontCfg.data = 0;
pmontCfg.dataSize = 0;
pmontCfg.cmode = PM_CMODE;
#if (PM_CMODE==2)
    pmontCfg.dev = DEV_SERIAL | PM_DEV;
#endif

#if (!PM_TRACE_BUFF)
pmontCfg.traceBuff = (char *)FreeMemPtr;
pmontCfg.traceBuffSize = PM_TRACE_SIZE;
FreeMemPtr += PM_TRACE_SIZE;
#else
pmontCfg.traceBuff = (char *) PM_TRACE_BUFF;
pmontCfg.traceBuffSize = PM_TRACE_SIZE;
#endif

NodeCfg->pmct = &pmontCfg;

/*---------------------------------------------------------------------*/
/* Set the pMONT serial channel baud rate. (SC_PMONT_BAUD replaces     */
/* PM_BAUD in newer versions of sys_conf.h.)                           */
/*---------------------------------------------------------------------*/
#ifdef SC_PMONT_BAUD
PmontBaudRate = SC_PMONT_BAUD;
#else
PmontBaudRate = PM_BAUD;
#endif

/*---------------------------------------------------------------------*/
/* Set up second timer only if user wants it AND board supports it     */
/*---------------------------------------------------------------------*/
#if ((BSP_TIMER2==YES) && (PM_TIMER==YES))

pmontCfg.tmFreq = tmFreq;
pmontCfg.tmReset = tmReset;
pmontCfg.tmRead = tmRead;

#else

pmontCfg.tmFreq = 0;
pmontCfg.tmReset = 0;
pmontCfg.tmRead = 0;

#endif

/*---------------------------------------------------------------------*/
/* Setup Pmont entry and exit callouts                                 */
/* pMont_I_ENTER  address = pMONT Code Starting + ENTRY_START_OFFSET + */
/*                          (ENTRY_LENGTH * I_ENTER_ENTRY_OFFSET)      */
/* pMont_I_RETURN address = pMONT Code Starting + ENTRY_START_OFFSET + */
/*                          (ENTRY_LENGTH * I_RETURN_ENTRY_OFFSET)     */
/*---------------------------------------------------------------------*/
BspPmontCallout((void (*)()) (((ULONG) pmont) + ENTRY_START_OFFSET +
                              (ENTRY_LENGTH * PMONT_I_ENTER_OFFSET)),
                (void (*)()) (((ULONG) pmont) + ENTRY_START_OFFSET +
                              (ENTRY_LENGTH * PMONT_I_RETURN_OFFSET)));

return(FreeMemPtr);
}

/***********************************************************************/
/* init_pmont_serial: initialize the pmont serial channel called       */
/*                    from console initialization                      */
/*                                                                     */
/*      INPUTS: struct ioparms *in_parms                               */
/*                                                                     */
/*     RETURNS: NONE                                                   */
/*     OUTPUTS: NONE                                                   */
/*     NOTE(S): call only after TermInit has been done                 */
/*                                                                     */
/***********************************************************************/
void init_pmont_serial(struct ioparms *in_parms)
{
struct ioparms parms;
TermCtl CtrlIopb;
struct termio termio;
unsigned long baud;
int i;

/*---------------------------------------------------------------------*/
/* If pMONT is not communicating over the serial port, don't touch it. */
/*---------------------------------------------------------------------*/
#if (PM_CMODE!=2)
    return;
#endif

/*---------------------------------------------------------------------*/
/* Set the major/minor number to dev entry in the pMONT configuration  */
/* table                                                               */
/*---------------------------------------------------------------------*/
if (!pmontCfg.dev)
    return;         /* only if we are using Serial */

parms.in_dev = pmontCfg.dev;

/*---------------------------------------------------------------------*/
/* Call TermOpen to open the serial channel for pMONT                  */
/*---------------------------------------------------------------------*/
TermOpen(&parms);
if(parms.err)
    {
    in_parms->err = parms.err;
    return;
    }

/*---------------------------------------------------------------------*/
/* Get settings                                                        */
/*---------------------------------------------------------------------*/
parms.in_iopb = (ULONG *) &CtrlIopb;
CtrlIopb.function = TCGETS;
CtrlIopb.arg = &termio;
TermIoctl(&parms);
if(parms.err)
    {
    in_parms->err = parms.err;
    return;
    }

/*---------------------------------------------------------------------*/
/* change settings and update.                                         */
/*---------------------------------------------------------------------*/

termio.c_iflag &= ~IPOST;
termio.c_oflag = 0;
termio.c_lflag = ICANON;
termio.c_cc[VEOL] = 0x0D;

baud = PmontBaudRate ? PmontBaudRate : SysBaud;

for (i = 1; i < BAUD_TABLE_SIZE; i++)
    if(baud_table[i] == baud)
        break;
if(i != BAUD_TABLE_SIZE)
    termio.c_cflag = termio.c_cflag & ~CBAUD | (i & CBAUD);
else
    {
    in_parms->err = CNSL_BAUD;
    return;
    }

CtrlIopb.function = TCSETSW;
CtrlIopb.arg = &termio;
TermIoctl(&parms);
if(parms.err)
    {
    in_parms->err = parms.err;
    return;
    }
}
#else
    void init_pmont_serial(struct ioparms *in_parms){}
#endif
#if __cplusplus
}
#endif
