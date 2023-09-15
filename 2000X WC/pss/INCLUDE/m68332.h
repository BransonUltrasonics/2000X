/* $Header:   K:/APPS/PVCS Pro/PSS68k.222/INCLUDE/m68332.h_v   1.3   Dec 13 2000 10:50:10   lmarkure  $ */
/* @(#) pSOSystem/68K V2.2.2: bsps/e332/src/m68332.h 1.5 95/10/09 12:57:32 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  bsps/e332/src/m68332.h                                   */
/*   DATE:    95/10/09                                                 */
/*   PURPOSE: Definitions for the M68332                               */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1995, Integrated Systems, Inc.           */
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
/*   This header file contains symbols and definitions of control      */
/*   registers on the M68332 that we will be reading and/or writing    */
/*   in various driver routines.  See MC68332 data book.               */
/*                                                                     */
/***********************************************************************/
/*

 ---------------------------------  REVISIONS --------------------------------

 Rev # Date     Author Description
 ===== ======== ====== ======================================================
 2.3   08.21.98 JBerman Switchd the system to 25Mhz (24.642Mhz).
 2.4   08.21.98 JBerman Redefined SYSTEM_CLOCK.
 2.5   08.27.98 JBerman Set SYSTEM_CLOCK to be 21MHz.
 1.1   05/02/99 LAM     Added SYSTEM_CLOCK define  
 1.2   05/10/99 LAM     set SYSTEM_CLOCK to 25Mhz
 1.3   12/13/00 LAM     set SYSTEM_CLOCK to 24_117Mhz


*/
#if __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------*/
/* Included to get the BSP specific location of the m68332 registers.  */
/*---------------------------------------------------------------------*/
/*#include "..\..\..\fads3board.h"*/

/*---------------------------------------------------------------------*/
/* General Definitions                                                 */
/*---------------------------------------------------------------------*/
#define REG8(addr)  *((volatile unsigned char * const) (addr))
#define REG16(addr) *((volatile unsigned short * const) (addr))
#define REG32(addr) *((volatile unsigned long * const) (addr))
/*---------------------------------------------------------------------*/
/* WFT, 12-13-95 - Added this selection for 16 or 20 Mhz parts  */
/*---------------------------------------------------------------------*/
#define _16MHZ      1
#define _20MHZ      2
#define _21MHZ      3
#define _24_642MHZ  4
#define _24_117MHZ  5
#define SYSTEM_CLOCK _24_117MHZ 
 
/*---------------------------------------------------------------------*/
/* System Integration Module (SIM) Address Definitions                 */
/*---------------------------------------------------------------------*/
#define Module_Config_Reg       REG16(0x0FFA00 + BD_REGS_BASE)
#define Clock_Syn_Ctrl_Reg      REG16(0x0FFA04 + BD_REGS_BASE)
#define Sys_Prot_Ctrl_Reg        REG8(0x0FFA21 + BD_REGS_BASE)
#define Periodic_Int_Ctrl_Reg   REG16(0x0FFA22 + BD_REGS_BASE)
#define Periodic_Int_Timing_Reg REG16(0x0FFA24 + BD_REGS_BASE)
#define CS_Pin_Assgnmt_Reg0     REG16(0x0FFA44 + BD_REGS_BASE)
#define CS_Pin_Assgnmt_Reg1     REG16(0x0FFA46 + BD_REGS_BASE)
#define Boot_Base_Addr_Reg      REG16(0x0FFA48 + BD_REGS_BASE)
#define Boot_Options_Reg        REG16(0x0FFA4A + BD_REGS_BASE)
#define CS0_Base_Addr_Reg       REG16(0x0FFA4C + BD_REGS_BASE)
#define CS0_Options_Reg         REG16(0x0FFA4E + BD_REGS_BASE)
#define CS1_Base_Addr_Reg       REG16(0x0FFA50 + BD_REGS_BASE)
#define CS1_Options_Reg         REG16(0x0FFA52 + BD_REGS_BASE)
#define CS2_Base_Addr_Reg       REG16(0x0FFA54 + BD_REGS_BASE)
#define CS2_Options_Reg         REG16(0x0FFA56 + BD_REGS_BASE)
#define CS3_Base_Addr_Reg       REG16(0x0FFA58 + BD_REGS_BASE)
#define CS3_Options_Reg         REG16(0x0FFA5A + BD_REGS_BASE)
#define CS4_Base_Addr_Reg       REG16(0x0FFA5C + BD_REGS_BASE)
#define CS4_Options_Reg         REG16(0x0FFA5E + BD_REGS_BASE)
#define CS5_Base_Addr_Reg       REG16(0x0FFA60 + BD_REGS_BASE)
#define CS5_Options_Reg         REG16(0x0FFA62 + BD_REGS_BASE)
#define CS6_Base_Addr_Reg       REG16(0x0FFA64 + BD_REGS_BASE)
#define CS6_Options_Reg         REG16(0x0FFA66 + BD_REGS_BASE)
#define CS7_Base_Addr_Reg       REG16(0x0FFA68 + BD_REGS_BASE)
#define CS7_Options_Reg         REG16(0x0FFA6A + BD_REGS_BASE)
#define CS8_Base_Addr_Reg       REG16(0x0FFA6C + BD_REGS_BASE)
#define CS8_Options_Reg         REG16(0x0FFA6E + BD_REGS_BASE)
#define CS9_Base_Addr_Reg       REG16(0x0FFA70 + BD_REGS_BASE)
#define CS9_Options_Reg         REG16(0x0FFA72 + BD_REGS_BASE)
#define CS10_Base_Addr_Reg      REG16(0x0FFA74 + BD_REGS_BASE)
#define CS10_Options_Reg        REG16(0x0FFA76 + BD_REGS_BASE)

/*---------------------------------------------------------------------*/
/* System Integration Module (SIM) Symbol Definitions                  */
/*---------------------------------------------------------------------*/

/*
** Module Configuration Register
*/
#define FREEZE_BUS_MON_EN       0x2000
#define SHOW_DIS_EXT_ARB_EN     0x0000
#define SHOW_EN_EXT_ARB_DIS     0x0100
#define SHOW_EN_EXT_ARB_EN      0x0200
#define SHOW_EN_EXT_STOPS_INT   0x0300
#define INT_ARB_LEVEL_0         0x0000
#define INT_ARB_LEVEL_1         0x0001
#define INT_ARB_LEVEL_2         0x0002
#define INT_ARB_LEVEL_3         0x0003
#define INT_ARB_LEVEL_4         0x0004
#define INT_ARB_LEVEL_5         0x0005
#define INT_ARB_LEVEL_6         0x0006
#define INT_ARB_LEVEL_7         0x0007
#define INT_ARB_LEVEL_8         0x0008
#define INT_ARB_LEVEL_9         0x0009
#define INT_ARB_LEVEL_A         0x000A
#define INT_ARB_LEVEL_B         0x000B
#define INT_ARB_LEVEL_C         0x000C
#define INT_ARB_LEVEL_D         0x000D
#define INT_ARB_LEVEL_E         0x000E
#define INT_ARB_LEVEL_F         0x000F

/*
** Sys_Prot_Ctrl_Reg
*/
#define NO_SOFTWARE_WATCHDOG  0
#define NO_HALT_MONITOR       0
#define MONITOR_EXTERNAL_BUS  0x04
#define BUS_MONITOR_TIMEOUT   0x02  /* 16 system clock periods */

/*
** Base Address Registers
*/
#define SIZE_2KB    0x00
#define SIZE_64KB   0x03
#define SIZE_128KB  0x04

/*
** Option Registers
*/
#define ASYNC            0x0000
#define SYNC             0x8000
#define LOWER_BYTE       0x2000
#define UPPER_BYTE       0x4000
#define WORD             0x6000
#define READ_ONLY        0x0800
#define WRITE_ONLY       0x1000
#define READ_AND_WRITE   0x1800
#define AS_SYNC          0x0000
#define DS_SYNC          0x0400
#define WAIT_0_STATES    (0 << 6)
#define WAIT_1_STATES    (1 << 6)
#define WAIT_2_STATES    (2 << 6)
#define WAIT_3_STATES    (3 << 6)
#define WAIT_4_STATES    (4 << 6)
#define WAIT_5_STATES    (5 << 6)
#define WAIT_6_STATES    (6 << 6)
#define FAST_TERMINATION (14 << 6)
#define EXTERN_DSACK     (15 << 6)
#define USER_SPACE       0x0010
#define SUPR_SPACE       0x0020
#define UNRESTRICTED     0x0030
#define AVEC_OFF         0x0000
#define AVEC_ON          0x0001

/*---------------------------------------------------------------------*/
/* Queued Serial Module (QSM) Address Definitions                      */
/*---------------------------------------------------------------------*/
#define QSM_Config_Reg          REG16(0x0FFC00 + BD_REGS_BASE)
#define QSM_Int_Level_Reg        REG8(0x0FFC04 + BD_REGS_BASE)
#define QSM_Int_Vect_Reg         REG8(0x0FFC05 + BD_REGS_BASE)
#define QSM_Port_Data_Reg        REG8(0x0FFC15 + BD_REGS_BASE)
#define QSM_Data_Dir_Reg         REG8(0x0FFC17 + BD_REGS_BASE)
#define SCI_Ctrl_Reg0           REG16(0x0FFC08 + BD_REGS_BASE)
#define SCI_Ctrl_Reg1           REG16(0x0FFC0A + BD_REGS_BASE)
#define SCI_Status_Reg          REG16(0x0FFC0C + BD_REGS_BASE)
#define SCI_Data_Reg             REG8(0x0FFC0F + BD_REGS_BASE)

/*---------------------------------------------------------------------*/
/* Queued Serial Module (QSM) Symbol Definitions                       */
/*---------------------------------------------------------------------*/

/*
** QSM Configuration Register
*/
#define STOP_THE_QSM_CLOCK      0x8000
#define FREEZE_HALTS_THE_QSM    0x4000
#define SUP_QSM_ACCESS_ONLY     0x0080
#define UNRESTRICTED_ACCESS     0x0000

/*
** QSM Port Data Register
*/
#define TXD_PIN_HIGH            0x80

/*
** QSM Data Direction Register
*/
#define TXD_PIN_OUTPUT          0x80

/*
** SCI Control Register 1
*/
#define LOOP_MODE               0x4000
#define PUSH_PULL_TXD           0x0000
#define OPEN_DRAIN_TXD          0x2000
#define SHORT_IDLE_DETECT       0x0000
#define LONG_IDLE_DETECT        0x1000
#define EVEN_PARITY             0x0000
#define ODD_PARITY              0x0800
#define PARITY_DISABLED         0x0000
#define PARITY_ENABLED          0x0400
#define EIGHT_DATA_BITS         0x0000
#define NINE_DATA_BITS          0x0200
#define IDLE_LINE_WAKEUP        0x0000
#define ADDR_MARK_WAKEUP        0x0100
#define TRANSMIT_INT_EN         0x0080
#define TRANSMIT_COMPLETE_INT_EN 0x0040
#define RECEIVER_INT_EN         0x0020
#define IDLE_LINE_INT_EN        0x0010
#define TRANSMITTER_EN          0x0008
#define RECEIVER_EN             0x0004
#define WAKEUP_MODE             0x0002
#define SEND_BREAK              0x0001

/*
** SCI Status Register
*/
#define TRANSMIT_REG_EMPTY      0x0100
#define TRANSMIT_COMPLETE       0x0080
#define RECEIVE_REG_FULL        0x0040
#define RECEIVER_ACTIVE         0x0020
#define IDLE_LINE_DETECTED      0x0010
#define OVERRUN_ERROR           0x0008
#define NOISE_ERROR             0x0004
#define FRAMING_ERROR           0x0002
#define PARITY_ERROR            0x0001

#if __cplusplus
}
#endif
