/* $Header:   D:/databases/VMdb/2000Series/INCLUDE/bspfuncs.h_v   1.3   12 Nov 2010 10:02:02   bkymer  $ */
/* @(#) pSOSystem/68K V2.2.2: include/bspfuncs.h (68k) 2.106 97/10/31 16:59:46 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  bspfuncs.h                                               */
/*   DATE:    97/10/31                                                 */
/*   PURPOSE: Function prototypes for pSOSystem Board Support Packages */
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
/***********************************************************************/
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version
 1.1   04/06/99 LAM     Deleted prototypes that are defined in serial.h
 1.3   11-12-10 BEK     Move version 1.1 to tip

*/
#if __cplusplus
    extern "C" {
#endif

/*---------------------------------------------------------------------*/
/* Don't allow this file to be included more than once.                */
/*---------------------------------------------------------------------*/
#ifndef _BSPFUNCS_H
#define _BSPFUNCS_H

#include "bsp.h"
#include "types.h"

/*---------------------------------------------------------------------*/
/* General Definitions                                                 */
/*---------------------------------------------------------------------*/

#define MAX_ILEV 7

ULONG splx(ULONG mask);

/***********************************************************************/
/*                                                                     */
/* CPU-Related Functions                                               */
/*                                                                     */
/***********************************************************************/
typedef enum wrapper_type
    {
    NO_WRAPPER = 0,          /* Handler is written in assembler */
    NORMAL_WRAPPER = 1,      /* Use normal C-compatible wrapper */
    NI_WRAPPER = 2,  /* Use special "network interface" wrapper */
    MBRK_WRAPPER = 3,        /* Use "manual break" wrapper */
    BRK_CHK_WRAPPER = 4
    } WRAPPER_TYPE;

void SysSetVector(int vector, void (*handler)(), WRAPPER_TYPE wt);

#define SYS_DCACHE_FLUSH_DISABLE
#define SYS_ICACHE_DISABLE
#define	SYS_SYNCUP_CACHES

/***********************************************************************/
/*                                                                     */
/* Startup Routines                                                    */
/*                                                                     */
/***********************************************************************/
void HdwInit(void);
#if BSP_VME
    void SetVmeAddress(ULONG BaseAddress);
#endif

ULONG RamSize(void);
void SysInitFail(const char *string);

/***********************************************************************/
/*                                                                     */
/* Miscellaneous Routines                                              */
/*                                                                     */
/***********************************************************************/
void StorageRead(UINT nbytes, void *StartOffset, void *buff);
void StorageWrite(UINT nbytes, void *StartOffset, void *buff);
void root(void);

#if (BSP_CPU == 68360)
    void Idle360(void);
#endif

#if BSP_PARMS
    #include <apdialog.h>
    void BspGetdefaults(void *ParmStruct);

    void BspPrint(void *ParmStruct,
        void(*PrintRoutine)(char *format, ...));

    void BspModify(void *ParmStruct,
        void(*PrintRoutine)(char *format, ...),
        void(*PromptRoutine)(char *prompt, PARM_TYPE ptype, void *paramptr));

    void BspUse(void *ParmStruct);
#endif

#if BSP_ABORTSW
void ClrAbortInt(void);
#endif

/***********************************************************************/
/*                                                                     */
/* Serial Driver Routines                                              */
/*                                                                     */
/***********************************************************************/
struct ioparms;   /* incomplete definition (avoids compiler warning) */
    #if BSP_NEW_SERIAL
        void ProbeIOInit (void);
        ULONG ProbeConsts (unsigned long);
        UCHAR ProbeConin (void);
        void ProbeConout (unsigned char);
        ULONG ProbeHststs (void);
        UCHAR ProbeHstin (void);
        void ProbeHstout (unsigned char);
        void ProbeEntry (void);
        void ProbeExit (void);
        void ProbeIOClose (void);
    #endif
/***********************************************************************/
/*                                                                     */
/* PC Console Driver                                                   */
/*                                                                     */
/***********************************************************************/
#if BSP_CONSOLE
 
void ConsolePollInit(void);
unsigned long ConsolePollConsts(unsigned long typecode);
unsigned char ConsolePollConin(void);
void  ConsolePollConout(unsigned char c);
 
#endif /* BSP_CONSOLE */

/***********************************************************************/
/*                                                                     */
/* Tick Timer Routines                                                 */
/*                                                                     */
/***********************************************************************/
#define BSP_TIMER 1

#if BSP_TIMER
void RtcInit(struct ioparms *p);
void Delay100ms(void);
#if (BSP_CPU == 68360)
void Rtc360Init(void(*)());
#endif
#endif /* BSP_TIMER */

/***********************************************************************/
/*                                                                     */
/* Realtime Clock routines                                             */
/*                                                                     */
/***********************************************************************/
#if BSP_CLOCK
void CmcRead(struct ioparms *p);
void CmcWrite(struct ioparms *p);
#endif

/***********************************************************************/
/*                                                                     */
/* Parallel Port routines                                              */
/*                                                                     */
/***********************************************************************/
#if BSP_PARALLEL
void ParInit(struct ioparms *p);
void ParOpen(struct ioparms *p);
void ParClose(struct ioparms *p);
void ParWrite(struct ioparms *p);
void ParRead(struct ioparms *p);
void ParCntrl(struct ioparms *p);
UCHAR *ParSetup(UCHAR *FreeMemPtr);
#endif

/***********************************************************************/
/*                                                                     */
/* IDE routines                                                        */
/*                                                                     */
/***********************************************************************/
#if BSP_IDE
void IDEInit(struct ioparms *p);
void IDERead(struct ioparms *p);
void IDEWrite(struct ioparms *p);
void IDECntrl(struct ioparms *p);
#endif

/***********************************************************************/
/*                                                                     */
/* Floppy routines                                                     */
/*                                                                     */
/***********************************************************************/
#if BSP_FLOPPY
void FlpInit(struct ioparms *p);
void FlpRead(struct ioparms *p);
void FlpWrite(struct ioparms *p);
#endif

/***********************************************************************/
/*                                                                     */
/* LAN Interface Routines                                              */
/*                                                                     */
/***********************************************************************/
#if BSP_LAN1
    union nientry;
    long BSP_LAN1_ENTRY(ULONG function, union nientry *p);
    UCHAR *NiLanSetup(int Nbufs, UCHAR *FreeMem);
#endif
ULONG GetRarpServerIP(void);
void LanStop(void);

/***********************************************************************/
/*                                                                     */
/* Shared Memory Interface Routines                                    */
/*                                                                     */
/***********************************************************************/
ULONG MemAccessible(volatile void *address);
ULONG SafeLongRead(volatile void *address);

#if BSP_SMEM
    /*-----------------------------------------------------------------*/
    /* Interrupt Method Data Structure - "method" specifies how a      */
    /* board should be interrupted to signal the arrival of a shared   */
    /* memory packet:                                                  */
    /*   0 : Do not interrupt (board will poll for packets)            */
    /*   1 : Read a byte from location m1.address in the VMEbus short  */
    /*       I/O space                                                 */
    /*   2 : Write byte "m2.value" to location m2.address in the       */
    /*       VMEbus short I/O space                                    */
    /* 3-127: Reserved - DO NOT USE                                    */
    /* 128 - 255: User-defined                                         */
    /*-----------------------------------------------------------------*/
#ifdef SMEM_PACKED
#pragma pack(1)
    typedef struct intr_method
        {
        UCHAR method;
        UCHAR fill1;
        union
            {
            struct { USHORT address; } m1;
            struct { USHORT address; UCHAR value; UCHAR fill2;} m2;
            } intr;
        } INTR_METHOD;
#pragma pack()
#else
    typedef struct intr_method
        {
        ULONG method;
        union
            {
            struct { ULONG address; } m1;
            struct { ULONG address; ULONG value; } m2;
            struct { ULONG  address; ULONG value; } m3;
            } intr;
        } INTR_METHOD;
#endif

    void SmemIntInit(INTR_METHOD *meth_ptr, ULONG NodeNumber,
                     ULONG (*Isr)(void));
    int SmemIntNode(INTR_METHOD *meth_ptr, ULONG TargetNode);
    void SmemIntClear(void);
    void *SmemBus2Local(void *BusAddress);
    void *SmemLocal2Bus(void *LocalAddress);

    #define SMEM_MAXNODES 8
#endif

/***********************************************************************/
/*                                                                     */
/* SCSI Routines                                                       */
/*                                                                     */
/***********************************************************************/
#if BSP_SCSI
    void SdrvInit(struct ioparms *t);
    void SdrvCntrl(struct ioparms *t);
    void SdskWrite(struct ioparms *t);
    void SdskRead(struct ioparms *t);
    void SdrvSetup(void);
    void StapeRead(struct ioparms *);
    void StapeWrite(struct ioparms *);
    void StapeOpen(struct ioparms *);
    void StapeClose(struct ioparms *);
#endif

/***********************************************************************/
/*                                                                     */
/* Watchdog Timer routines                                             */
/*                                                                     */
/***********************************************************************/
#if BSP_WATCHDOG
 
void WdtInit(struct ioparms *t);
 
#endif

/***********************************************************************/
/*                                                                     */
/*  High-Level Driver Routines                                         */
/*                                                                     */
/***********************************************************************/
#if BSP_SERIAL
    UCHAR *CnslSetup(UCHAR *FreeMem, ULONG defbaud, USHORT defcons);
    void   CnslInit(struct ioparms *t);
    void   CnslRead(struct ioparms *t);
    void   CnslWrite(struct ioparms *t);
    void   CnslCntrl(struct ioparms *t);
#endif

#if BSP_CONSOLE
    void PcCnslInit(struct ioparms *t);
    void PcCnslRead(struct ioparms *t);
    void PcCnslWrite(struct ioparms *t);
    void PcCnslCntrl(struct ioparms *t);
#endif

#if BSP_LAN1
    union nientry;   /* incomplete definition (avoids compiler warning) */
    ULONG RarpEth(long (*NiLanPtr)(ULONG fn_code, union nientry *p));
#endif

#if BSP_SMEM
    #define NISM_MTU 560
    union nientry;   /* incomplete definition (avoids compiler warning) */
    long   NiSmem(ULONG function, union nientry *p);
    UCHAR *NiSmemSetup(int Nbufs, UCHAR *FreeMem, int key);
#endif

/*---------------------------------------------------------------------*/
/* Routines not dependent on hardware                                  */
/*---------------------------------------------------------------------*/
void RdskInit(struct ioparms *t);
void RdskWrite(struct ioparms *t);
void RdskRead(struct ioparms *t);

void TftpInit(struct ioparms *iop);
void TftpOpen(struct ioparms *iop);
void TftpClose(struct ioparms *iop);
void TftpRead(struct ioparms *iop);
void TftpCntl(struct ioparms *iop);


/*---------------------------------------------------------------------*/
/* pSOS Component callouts                                             */
/*---------------------------------------------------------------------*/
#define  ENTRY_START_OFFSET       0x40
#define  PSOS_SVC_OFFSET          1
#define  PSOS_I_ENTER_OFFSET      4
#define  PSOS_I_RETURN_OFFSET     3
#define  PROBE_INIT_OFFSET        0x15
#define  PNA_DI_OFFSET            4

/*---------------------------------------------------------------------*/
/* pMont Component callouts                                            */
/*---------------------------------------------------------------------*/
void BspPmontCallout(void (*pMIEnter)(), void (*pMIExit)());

#define  PMONT_I_ENTER_OFFSET     5
#define  PMONT_I_RETURN_OFFSET    6

#define  ENTRY_LENGTH             4

/*---------------------------------------------------------------------*/
/* Pseudo driver functions                                             */
/*---------------------------------------------------------------------*/
void PseudoIOInit(struct ioparms *t);
void PseudoIORead(struct ioparms *t);
void PseudoIOWrite(struct ioparms *t);
void PseudoIOCntrl(struct ioparms *t);

#endif /* _BSPFUNCS_H */

#if __cplusplus
}
#endif
