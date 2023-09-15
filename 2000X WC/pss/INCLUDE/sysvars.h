/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\sysvars.h_v   1.0   Mar 29 1999 13:51:08   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/sysvars.h 2.17 97/09/22 15:00:08 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  sysvars.h                                                */
/*   DATE:    97/09/22                                                 */
/*   PURPOSE: System variables structure definition                    */
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
/***********************************************************************/
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version

*/

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#ifndef _SYSVARS_H
#define _SYSVARS_H

#include "bsp.h"

#define DBG_SA    1  /* Standalone pROBE debugging */
#define DBG_XS    2  /* talk to host debugger via RS-232 */
#define DBG_XN    3  /* talk to host debugger via network */
#define DBG_AP    4  /* Run application (w/ pROBE in standalone mode) */
 
#define STORAGE   5  /* Get SD_'s from storage area */
#define SYS_CONF  6  /* Get SD_'s from #defines set in sys_conf.h */
 
/*---------------------------------------------------------------------*/
/* These parameters correspond to the SD_ parameters in sys_conf.h     */
/* They are the parameters which may be stored and retrieved in the    */
/* board's parameter storage area.  In addition, the optional startup  */
/* configuration dialog can be used to change them.                    */
/*---------------------------------------------------------------------*/
struct SD_parms
    {
    /*-----------------------------------------------------------------*/
    /* Debug Mode determines how pROBE+ wil operate:                   */
    /*   DBG_SA - Standalone mode                                      */
    /*   DBG_XS - Communicating with host debugger via serial link     */
    /*   DBG_XN - Communicating with host debugger via network         */
    /*   DBG_AP - Start the application immediately (using "silent     */
    /*            startup").  pROBE+ should be configured to run in    */
    /*            standalone mode.                                     */
    /*-----------------------------------------------------------------*/
    unsigned char DebugMode;
    unsigned char Pad1[3];

    /*-----------------------------------------------------------------*/
    /* These variables control miscellaneous basic characteristics     */
    /* of the system:                                                  */
    /*   StartupDelay - If the startup configuration dialog is         */
    /*                  configured, it will wait this many seconds     */
    /*                  for input from the serial channel              */
    /*   DefBaud - Initial baud rate to use for the serial channels.   */
    /*             (Applications may change the baud rate via          */
    /*             de_ctrl() calls)                                    */
    /*   VmeBaseAddr - The base address of the board's dual-ported     */
    /*                 memory, as seen from the VMEbus.  Not used      */
    /*                 on non-VME boards (BSP_VME = NO)                */
    /*-----------------------------------------------------------------*/
    unsigned long StartupDelay;
    unsigned long DefBaud;
    unsigned long VmeBaseAddr;

    /*-----------------------------------------------------------------*/
    /* DefGtwyIP is used when networking is enabled to specify a       */
    /* "default gateway" node where packets should be sent in the      */
    /* absence of other routing information.                           */
    /*-----------------------------------------------------------------*/
    unsigned long DefGtwyIP;

    /*-----------------------------------------------------------------*/
    /* These variables control the LAN interface.  If SC_PNA and/or    */
    /* BSP_LAN1 is FALSE, they are ignored.                            */
    /*   Lan1 - TRUE if LAN interface should be enabled                */
    /*   Lan1IP - IP address for the LAN interface.  0 indicates that  */
    /*            RARP should be used to obtain the IP address.        */
    /*   Lan1SubnetMask - Subnet mask to use for the LAN interface     */
    /*-----------------------------------------------------------------*/
    unsigned char Lan1;
    unsigned char Pad2[3];
    unsigned long Lan1IP;
    unsigned long Lan1SubnetMask;

    /*-----------------------------------------------------------------*/
    /* If a shared memory interface is to be used (either NI or KI or  */
    /* both), it must have a node number, which is a small integer.    */
    /* SmNode holds this number.                                       */
    /*-----------------------------------------------------------------*/
    unsigned long SmNode;  

    /*-----------------------------------------------------------------*/
    /* These variables control the shared memory network interface.    */
    /*   Nism - TRUE if SMNI should be enabled                         */
    /*   NismIP - IP address to use for the interface                  */
    /*   NismSubnetMask - Subnet mask to use for the interface         */
    /*   NismDiraddr - Bus address of the system-wide "directory"      */
    /*           structure for the interface.                          */
    /* Note that SmNode, above, is also relevant to the SMNI.          */
    /*-----------------------------------------------------------------*/
    unsigned char Nism;   
    unsigned char Pad3[3];
    unsigned long NismIP;  
    unsigned long NismSubnetMask;
    unsigned long NismDiraddr;

    /*-----------------------------------------------------------------*/
    /* These variables control the shared memory kernel interface.     */
    /*   Kism - 0 if KISM should not be enabled.  A non-zero value     */
    /*          indicates that the SMKI should be enabled.  In this    */
    /*          case "Kism" should be set to the total number of nodes */
    /*          in the system.  SmNode (defined above here) is set     */
    /*          to this node's node number, which must be in the range */
    /*          1 through "Kism".                                      */
    /*   KismDiraddr - Bus address of the system-wide "directory"      */
    /*          structure for the interface                            */
    /*-----------------------------------------------------------------*/
    unsigned long Kism;
    unsigned long KismDiraddr;
    }; 

#ifndef BSP_PARMS
    # define BSP_PARMS 0
#endif
#ifndef SC_APP_PARMS
    # define SC_APP_PARMS 0
#endif
 
typedef struct NV_Parms {
    unsigned long magic;
    unsigned long SysVars_CheckSum;
    struct SD_parms SysVars;
 
#if BSP_PARMS
    unsigned long BspVars_CheckSum;
    UCHAR BspVars[BSP_PARMS];
#endif
 
#if SC_APP_PARMS
    unsigned long AppVars_CheckSum;
    UCHAR AppVars[SC_APP_PARMS];
#endif
} NV_Parms;

extern NV_Parms NVVars;
 
#define SysVars NVVars.SysVars
#define BspVars NVVars.BspVars
#define AppVars NVVars.AppVars

#endif /* _SYSVARS_H */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

