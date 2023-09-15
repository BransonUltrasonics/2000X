/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\machine.h_v   1.0   Mar 29 1999 13:50:58   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/machine.h 1.22 97/11/10 18:11:39 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  machine.h                                                */
/*   DATE:    97/11/10                                                 */
/*   PURPOSE: Machine (PPC/68k/960/MIPS/386/88k/SH) dependent defines  */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1997, Integrated Systems, Inc.           */
/*                  Copyright 1997, Motorola, Inc.                     */
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
/***********************************************************************/
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version

*/

#if __cplusplus
    extern "C" {
#endif

#include <types.h>

/*---------------------------------------------------------------------*/
/* Don't allow this file to be included more than once.                */
/*---------------------------------------------------------------------*/
#ifndef _MACHINE_H
#define _MACHINE_H

/***********************************************************************/
/* CPU Related Definitions                                             */
/***********************************************************************/
#if (BSP_CPUFAMILY == FAMILY_POWERPC)  /* PowerPC Specific Definitions */

/*---------------------------------------------------------------------*/
/* Vector offsets - these vary somewhat among members of the           */
/* processor family:                                                   */
/*                                                                     */
/*                                                  Processors         */
/*                                                 601 603 403GA 821   */
/*     Label       Offset      Explanation             604       860   */
/*     =========   ======      =================   === === ===   ===   */
#define V_RESET     0x0100   /* System reset         x   x         x   */
#define V_CRITINT   0x0100   /* Critical interrupt           x         */
#define V_MACH_CK   0x0200   /* Machine check        x   x   x     x   */
#define V_DA        0x0300   /* Data access          x   x             */
#define V_PROTECT   0x0300   /* Prot. violation              x         */
#define V_IA        0x0400   /* Instruction access   x   x             */
#define V_INTRPT    0x0500   /* External interrupt   x   x   x     x   */
#define V_ALIGN     0x0600   /* Alignment            x   x   x     x   */
#define V_PROGRAM   0x0700   /* Program              x   x   x     x   */
#define V_FLOAT     0x0800   /* Fltg-pt unavail      x   x             */
#define V_DCRMNTR   0x0900   /* Decrementer          x   x         x   */
#define V_IOERROR   0x0A00   /* I/O ctrlr intfc err  x                 */
#define V_SYSCALL   0x0C00   /* System call          x   x   x     x   */
#define V_TRACE     0x0D00   /* Trace exception          x         x   */
#define V_TIMERS    0x1000   /* On-chip timers               x         */
#define V_FIT_403   0x1010   /* On-chip timers (FIT)         x         */
#define V_WATCHDG   0x1020   /* watch dog timer              x         */
#define V_IA_BP     0x1300   /* Instr addr bkpt          x             */
#define V_ITLB      0x1000   /* Instruction TLB Miss x    x            */
#define V_DLTLB     0x1100   /* Data Load TLB miss   x    x            */
#define V_DSTLB     0x1200   /* Data Store TLB miss  x    x            */
#define V_RUNMODE   0x2000   /* Run mode exception   x                 */
#define V_DEBUG     0x2000   /* 403 debug exception          x         */
#define V_SEI821    0x1000   /* 821 Ileagle Instr                   x  */
#define V_IA_BP821  0x1D00   /* 821 Instruction access breakpoint   x  */
#define V_DA_BP821  0x1C00   /* 821 memory access breakpoint        x  */
                             /*----------------------------------------*/

/*---------------------------------------------------------------------*/
/* Vector type definitions - one of these must be passed as the third  */
/* argument to SysSetVector().                                         */
/*---------------------------------------------------------------------*/
#define VT_DIRECT  0  /* actual vector code is being passed as "handler" */
#define VT_REG     1  /* use vector code w/ register-oriented interface */
#define VT_STACK   2  /* use vector code w/ stack-based interface */
#define VT_STACK3  3  /* use vector code w/ stack based interface,  */
                      /* 3 entry points */
#define VT_SC      4  /* use vector code w/ stack-based interface, */
                      /* customized for system call exceptions */
#define VT_CRITICAL 5 /* critical interrupt/exception (403 only) */
#define	VT_RESET8xx 6 /* Special wrapper to handle Software reset and */
                      /* manual breaks on the MPC8xx based boards. */

/*---------------------------------------------------------------------*/
/* Processor type definitions.  A match to one of these can be         */
/* obtained with (BspCpuType() & 0xFF).  Note that these values are    */
/* NOT the same values obtained by reading the PVR (Processor Version  */
/* Register).  BspCpuType() reads the PVR and then maps the value      */
/* obtained to one of these.                                           */
/*---------------------------------------------------------------------*/
#define PPC601      0
#define PPC603      1
#define PPC604      2
#define PPC603e     3
#define PPC403GA    4
#define PPC821      5
#define PPC604e     6
#define PPC604p     6   	/* For now make 604e = 604p */
#define PPC603p     7
#define PPC860      8
#define PPC604r     9
#define PPC740      10  
#define MPC740      PPC740  
#define PPC750      11 
#define MPC750      PPC750 
#define PPC505      12 
#define MPC505      PPC505 

/*---------------------------------------------------------------------*/
/* Machine State Register definitions - Common Definitions             */
/*---------------------------------------------------------------------*/
#define  MSR_DR        0x00000010      /* Data Translation             */
#define  MSR_IR        0x00000020      /* Instruction Translation      */
#define  MSR_BE        0x00000200      /* Branch Trace Enable          */
#define  MSR_ME        0x00001000      /* Machine Check Enable         */
#define  MSR_PR        0x00004000      /* Priviledge Level             */
#define  MSR_EE        0x00008000      /* External Interrupt Enable    */

/*---------------------------------------------------------------------*/
/* Machine State Register - PowerPC 60x series-specific definitions    */
/*---------------------------------------------------------------------*/
#define  MSR_RSRV6     0xFFF8008C      /* Reserved Bits                */
#define  MSR_FE1       0x00000100      /* Floating Point Exception Md 1*/
#define  MSR_SE        0x00000400      /* Single Step Trace Enable     */
#define  MSR_FE0       0x00000800      /* Floating Point Exception Md 0*/
#define  MSR_FP        0x00002000      /* Floating Point Available     */
#define  MSR_TGPR      0x00020000      /* Temp GPR remapping           */

/*---------------------------------------------------------------------*/
/* Machine State Register - PowerPC 4 series specific definitions      */
/*---------------------------------------------------------------------*/
#define  MSR_RSRV4     0xFFF92DFC      /* Reserved Bits                */
#define  MSR_PX        0x00000004      /* Protection Exclusive Mode    */
#define  MSR_PE        0x00000008      /* Protection Enable            */
#define  MSR_DE        0x00000200      /* Debug Exception Enable       */
#define  MSR_PR        0x00004000      /* Problem Stat                 */
#define  MSR_CE        0x00020000      /* Critical Interrupt Enable    */
#define  MSR_WE        0x00040000      /* Wait State Enable            */
#define  MSR_PX_E      MSR_PX
#define  MSR_PX_I      0

#endif                                 /* BSP_CPUFAMILY==FAMILY_POWERPC*/

/*---------------------------------------------------------------------*/
/* Hardware Implementation Register Definitions                        */
/*---------------------------------------------------------------------*/
#define  HID0_RSRV4    0x00FE037B      /* Reserved Bits                */
#define  HID0_BTACEN   0x00000002      /* 604r- BTAC enable            */
#define  HID0_SRLEXC   0x00000080      /* 604- serial access inhibit   */
#define  HID0_DCE      0x00004000      /* Data Cache Enable            */
#define  HID0_ICE      0x00008000      /* Instruction Cache Enable     */
#define  HID0_MACHEN   0x80000000      /* 604- machine check enable    */

#endif                                 /* _MACHINE_H */

#if __cplusplus
}
#endif
