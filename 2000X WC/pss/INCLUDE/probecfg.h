/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\probecfg.h_v   1.0   Mar 29 1999 13:51:04   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/probecfg_ghs.h (68k) 1.9 97/11/03 09:04:25 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/probecfg.h                                       */
/*   DATE:    97/11/03                                                 */
/*   PURPOSE: Configuration table structure templates                  */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1993 - 1997, Integrated Systems, Inc.           */
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
/*   This file contains templates for pROBE+ configuration table.      */
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
#ifndef _PROBECFG_H
#define _PROBECFG_H

/********************************************************************/
/* Masks for RC_FLAGS entry (_MASK & RC_FLAGS isolates the Flag)    */
/********************************************************************/
#define RBUG_MASK    0x00000001
#define NODOTS_MASK  0x00000004
#define NOMANB_MASK  0x00000008
#define NOPAGE_MASK  0x00000010
#define PROFILE_MASK 0x00000020
#define NOTUPD_MASK  0x00000040      /* no task info update for RBUG */
#define SMODE_MASK   0x00000100      /* silent start-up mode         */

/*---------------------------------------------------------------------*/
/* Driver Interface Structure                                          */
/*---------------------------------------------------------------------*/
typedef struct callouts
    {
    long (*services)();                   /* pointer to Processor Services */
    long (*driver)();                     /* pointer to current IO driver */
    long (*disasm)(unsigned long pc_addr, /* pointer to Disassembler */
                   char *bufptr);
    long (*query)();                      /* pointer to Query Services */
    long (*urcom)();                      /* pointer to User Command */
    } CALLOUTS;

/*---------------------------------------------------------------------*/
/* Used in the Configuration Table                                     */
/*---------------------------------------------------------------------*/
void pROBE_Core(void);
long pROBE_Init(void);
void pROBE_Console(void);
void pROBE_Hld(void);
void pROBE_Disasm(void);
void pROBE_Query(void);
void pROBE_Debug(void);

/*---------------------------------------------------------------------*/
/* Application Program Interface Errors                                */
/*---------------------------------------------------------------------*/
#define SUCCESS        0
#define ERR_PARM       -1            /* can't even guess what's wrong! */
#define ERR_WIDTH      ERR_PARM-1    /* width wrong for count */
#define ERR_NO_PSOS    ERR_WIDTH-1   /* can't do it without pSOS */
#define ERR_NO_REG     ERR_NO_PSOS-1 /* invalid Register Code */
#define ERR_BUS_FAULT  ERR_NO_REG-1  /* got a Bus Error on memory move */

/*---------------------------------------------------------------------*/
/* Interface Communications Driver                                     */
/*---------------------------------------------------------------------*/
#define INIT    0x11
#define GET     0x14
#define PUT     0x12
#define STATUS  0x15

#define BREAK      2       /* return codes */
#define MORE       1
#define NO_MSG    -1
#define XMIT_ERR  -2
#define NO_IO     -3

/*---------------------------------------------------------------------*/
/*   Interface for pROBE+ change of state user callout                 */
/*---------------------------------------------------------------------*/
#define TASKING_NORM     0x1    /* Normal pSOS+ tasking is enabled     */
#define TASKING_PROBE    0x2    /* pROBE+ has disabled tasking         */
#define MEMACCESS_NORM   0x4    /* Normal system memory prot. enabled  */
#define MEMACCESS_PROBE  0x8    /* pROBE+ may access any phys address  */

/*---------------------------------------------------------------------*/
/* rw_mode for (*td_urwrite_t)()                                       */
/*---------------------------------------------------------------------*/
#define PROBE_RW_WIDE_MASK   0xF
#define PROBE_RW_BYTE_WIDE   0x1
#define PROBE_RW_WORD_WIDE   0x2
#define PROBE_RW_LONG_WIDE   0x4
#define PROBE_RW_DBL_WIDE    0x8
#define PROBE_MEM_READ       0x100
#define PROBE_MEM_WRITE      0x200
#define PROBE_MEM_FILL       0x400

/*---------------------------------------------------------------------*/
/* ANSI Prototypes for application program calls to Debugger Services  */
/*---------------------------------------------------------------------*/
void fat_err_entry(void);
void rsrv_entry(void);
void manb_entry(void);          /* manual break entry */

long config_tables(
    long            CompCode,
    unsigned char **v_ptr,
    unsigned char **ct_sptr,
    unsigned char **ct_ptr
    );

typedef long (*td_urwrite_t)(UCHAR *dst, long count, UCHAR *src,
                             ULONG rw_mode, ULONG *result);

/*=====================================================================*/
/* pROBE+ Configuration table                                          */
/*=====================================================================*/
typedef struct pROBEConfigTable
    {
    void (*td_code)(void);              /* addr of pROBE code module */
    ULONG *td_data;                     /* addr of pROBE data area */
    ULONG *td_stack;                    /* top of pROBE stack area */
    void (*td_console)(void);
    void (*td_debug)(void);
    void (*td_query)(void);                 /* pSOS component query */
    void (*td_disasm)(void);
    void (*td_reserved1[4])();          /* must be 0 (4 code pointers) */
    ULONG td_brkopc;                    /* instruction break opcode */
    ULONG td_flags;                     /* initial flag settings */
    ULONG td_dbgpri;                    /* Debugger tasks priority */
    long (*td_drv0)(ULONG,long*,char*); /* communications driver 0 */
    long (*td_drv1)(ULONG,long*,char*); /* communications driver 1 */
    void (*td_statechng)(ULONG);        /* debugger state-change callout */
    long (*td_urcom)(char *cmd_ptr);    /* user cmd processing */
    td_urwrite_t td_urwrite;            /* user HW write routine */
    ULONG td_reserved2[6];              /* must be 0 (6 words) */
    } pROBE_CT;



#endif

#if __cplusplus
}
#endif
