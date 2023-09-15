/* @(#) pSOSystem/68K V2.2.2: bsps/template/bsp.h (fads302) 2.237 98/05/18 13:38:10 */
/* $Header:   K:/APPS/PVCS Pro/332new/INC/BSP.H_V   2.9   Dec 05 2003 13:29:10   BKymer  $ */

/***********************************************************************/
/*                                                                     */
/*   MODULE:  bsp.h                                                    */
/*   DATE:    98/05/18                                                 */
/*   PURPOSE: Defining characteristics of a board-support package      */
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
/*   This file contains two sets of definitions:                       */
/*                                                                     */
/*     * The characteristics and capabilities of the board and its     */
/*       BSP, such as processor type, peripheral devices available,    */
/*       etc.                                                          */
/*                                                                     */
/*     * The vector numbers for the various interrupts and exceptions  */
/*       which can occur on the board.                                 */
/*                                                                     */
/***********************************************************************/

/* --------------------------------- REVISIONS -------------------------

 Rev #        Date     Author  Description
 =====        ======== ======  =============================================
 1.0          03/26/99 OFI     Original Version
 2.7          04/05/99 LAM     Updated for our application
 2.8          06/21/00 AS      Added vector for IRQ3 connected to M3100
 2.8.1.0      03/20/03 SCM     Added vector definition for Qvga interrupt (Vector #29)
 2.9          12-05-03 BEKymer Move 2.8.1.0 to tip as 2.9 for Ver9.00b build
 
 
*/

#if __cplusplus
extern "C" {
#endif

#ifndef _BSP_H
#define _BSP_H

#include <types.h>

/***********************************************************************/
/*                                                                     */
/*                                                                     */
/*      B O A R D - S U P P O R T   P A C K A G E   P R O F I L E      */
/*                                                                     */
/*                                                                     */
/***********************************************************************/

/*=====================================================================*/
/*                                                                     */
/*              B A S I C   C H A R A C T E R I S T I C S              */
/*                                                                     */
/*   * BSP_VERSION         - specifies revision level of pSOSystem     */
/*                           which this BSP was written to support     */
/*   * BSP_CPUFAMILY       - CPU processor FAMILY (68000, 88000,       */
/*                           i960, or x86)                             */
/*   * BSP_CPU             - Specific processor within family (68000,  */
/*                           68008, 68010, 68020, 68302, 68332, 68360  */
/*                           etc)                                      */
/*   * BSP_FPU             - Floating-point unit (YES/NO)              */
/*   * BSP_MMU             - Memory Management Unit (YES/NO)           */
/*   * BSP_RAM_BASE        - Starting address of RAM as seen by CPU    */
/*   * BSP_VME             - YES if this is a VME board                */
/*   * BSP_LITTLE_ENDIAN   - YES if board is "little-endian"           */
/*                                                                     */
/*=====================================================================*/
#define BSP_VERSION            222
#define BSP_CPUFAMILY          FAMILY_M68000
#define BSP_CPU                68332
#define BSP_FPU                NO
#define BSP_MMU                NO
#define BSP_RAM_BASE           0x100000
#define BSP_VME                NO
#define BSP_LITTLE_ENDIAN      NO


/*=====================================================================*/
/*                                                                     */
/*            M I S C E L L A N E O U S   F E A T U R E S              */
/*                                                                     */
/*   * BSP_PARMS     - size in bytes of board-specific parameters      */
/*                     which should be stored in non-volatile RAM and  */
/*                     modified via the optional startup dialog.       */
/*                     0 = none.                                       */
/*   * BSP_ABORTSW   - Front panel "abort" button (YES/NO)             */
/*                                                                     */
/*=====================================================================*/
#define BSP_PARMS              0
#define BSP_ABORTSW            NO

/*=====================================================================*/
/*                                                                     */
/*                   S E R I A L   C H A N N E L S                     */
/*                                                                     */
/*   * BSP_SERIAL indicates the number of serial channels supported    */
/*     (0 = none)                                                      */
/*   * BSP_SERIAL_MINBAUD - lowest supported baud rate                 */
/*   * BSP_SERIAL_MAXBAUD - highest supported baud rate                */
/*                                                                     */
/*=====================================================================*/
#define BSP_SERIAL             0
#define BSP_NEW_SERIAL         NO
#define BSP_NUM_SER_DRVRS      1
#define BSP_SERIAL_MINBAUD     300
#define BSP_SERIAL_MAXBAUD     384000

/*=====================================================================*/
/*                                                                     */
/*                    L A N   I N T E R F A C E S                      */
/*                                                                     */
/*   * BSP_LAN1            - YES if LAN is supported                   */
/*   * BSP_LAN1_ENTRY      - Function name of LAN entry point          */
/*   * BSP_LAN1_MTU        - Maximum transmission unit (bytes)         */
/*   * BSP_LAN1_HWALEN     - Length of hardware address in bytes       */
/*   * BSP_LAN1_FLAGS      - Interface flags (per pNA manual)          */
/*        IFF_POLL             0x8000   interface is a polling type    */
/*        IFF_BROADCAST        0x0001   NI supports broadcasts         */
/*        IFF_RAWMEM           0x2000   driver uses "mblk" interface   */
/*        IFF_MULTICAST        0x0800   driver suports multicast       */
/*                                                                     */
/*=====================================================================*/
#define BSP_LAN1               NO
#define BSP_LAN1_ENTRY         NiLan
#define BSP_LAN1_MTU           1500
#define BSP_LAN1_HWALEN        6
#define BSP_LAN1_FLAGS         0x8001

/*=====================================================================*/
/*                                                                     */
/*    S H A R E D   M E M O R Y   C O M M U N I C A T I O N            */
/*                                                                     */
/*   * BSP_SMEM            - Yes if shared memory communication is     */
/*                           supported                                 */
/*                                                                     */
/*=====================================================================*/
#define BSP_SMEM               NO

/*=====================================================================*/
/*                                                                     */
/*                         I D E                                       */
/*                                                                     */
/*=====================================================================*/
#define BSP_IDE                NO

/*=====================================================================*/
/*                                                                     */
/*                       F L O P P Y                                   */
/*                                                                     */
/*=====================================================================*/
#define BSP_FLOPPY             NO

/*=====================================================================*/
/*                                                                     */
/*                         S C S I                                     */
/*                                                                     */
/*=====================================================================*/
#define BSP_SCSI               NO
#define BSP_SCSI_TAPE          NO

/*=====================================================================*/
/*                                                                     */
/*              2 N D   T I M E R    F O R    p M O N T                */
/*                                                                     */
/*=====================================================================*/
#define BSP_TIMER2             NO

 
/***********************************************************************/
/*                                                                     */
/*                                                                     */
/*                V E C T O R   D E F I N I T I O N S                  */
/*                                                                     */
/*                                                                     */
/***********************************************************************/
#define V_BUSERR    2    /* Bus error */
#define V_ADDRERR   3    /* Address error */
#define V_TRACE     9    /* Trace exception */
#define V_TRAP0     32   /* Trap 0 - pROBE breakpoint */
#define V_TRAP1     33   /* Trap 1 - pSOSystem ROM monitor breakpoint */
#define V_TRAP11    43   /* Trap 11 - pSOS service call */
#define V_TRAP12    44   /* Trap 12 - pSOS I/O call */
#define V_TRAP13    45   /* Trap 13 - pSOS return from interrupt */
#define V_BUSERR        2     /* Bus error                              */                           
#define V_ADDRERR       3     /* Address error                          */
#define V_ILLEGALINSTR  4     /* Illegal Instruction                    */
#define V_ZERODIVIDE    5     /* Zero division                          */
#define V_CHKCHK2       6     /* CHK, CHK2 instructions                 */
#define V_TRAPCCTRAPV   7     /* TRAPcc, TRAPV instructions             */
#define V_PRIVILEGEVIO  8     /* Privilege Violation                    */
#define V_TRACE         9     /* Trace exception                        */   
#define V_SPURIOUS      24    /* Spurious Interrupt                     */
#define V_PRINTERINT    25    /* LEVEL 1 AUTOVECTOR - Printer           */
#define V_KEYINT        26    /* LEVEL 2 AUTOVECTOR - Keypad            */     
#define V_M3100         27    /* LEVEL 3, IRQ3 connected to M3100       */
#define V_QVGAINT       29    /* LEVEL 5- QVGA 68681 UART               */
#define V_ABORT         31    /* LEVEL 7 AUTOVECTOR - ESTOP             */
#define V_TRAP0         32    /* Trap 0 - pROBE breakpoint              */
#define V_TRAP1         33    /* Trap 1 - pSOSystem ROM monitor brkpt   */
#define V_TRAP11        43    /* Trap 11 - pSOS service call            */
#define V_TRAP12        44    /* Trap 12 - pSOS I/O call                */
#define V_TRAP13        45    /* Trap 13 - pSOS return from interrupt   */
#define V_SERIAL        64    /* Serial channel (must be even)          */
#define V_QSPI          65    /* SPI Channels                           */
#define V_TICK          66    /* pSOS clock interrupt                   */
#define V_VFBUSYINT1    89    /*                     */
#define V_MSINT         128   /* 1 ms Interrupt-TPUCH0                  */
#define V_VFBUSYINT2    136   /* VF Display Busy-TPUCH8                 */
#define V_STOREINT      143   /* memstore input isr-TPUCH15             */


/*---------------------------------------------------------------------*/
/* EXCLUDED_VECTORS can optionally define a list of vectors which      */
/* should be left alone by pSOSystem.  Vectors in the "excluded"       */
/* list will not be initialized.  The list should contain the vectors, */
/* separated by commas.   The most common use of this is to allow      */
/* debugging of the pSOSystem with a ROM monitor.  For example,        */
/* if your ROM monitor uses TRAP #1 to implement instruction           */
/* breakpoints, you could let the monitor maintain control by defining */
/* EXCLUDED_VECTORS as follows:                                        */
/*                                                                     */
/*   #define EXCLUDED_VECTORS V_BUSERR,V_ADDRERR,V_TRACE,V_TRAP1,17    */
/*                                                                     */
/* In this case, the downloaded pSOSystem would not modify any of      */
/* these vectors, so bus and address errors would be fielded by the    */
/* ROM monitor.  Software monitors usually make use of the trace       */
/* exception as well. The 17 is the anchor slot in the vector table    */
/* ie. if the anchor is set in rom.lnk to 0x44 divide 0x44 by 4 =      */
/* 17 decimal.  This will keep the rom anchor from getting overwritten.*/
/* The anchor address must be different for the ram code used. A good  */
/* address would be 0x48 (change made in ram.lnk).                     */
/*                                                                     */
/*=====================================================================*/
//#define EXCLUDED_VECTORS 59,60,61,62,63



#endif /* _BSP_H */

#if __cplusplus
}
#endif
