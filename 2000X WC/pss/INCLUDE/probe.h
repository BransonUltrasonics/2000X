/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\probe.h_v   1.0   Mar 29 1999 13:51:02   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/probe.h (ghs) 1.9 97/05/20 16:40:58 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/probe.h                                          */
/*   DATE:    97/05/20                                                 */
/*   PURPOSE: Service call function prototypes for pROBE+              */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*             Copyright 1991 - 1995 Integrated Systems, Inc.          */
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

/*---------------------------------------------------------------------*/
/* Don't allow this file to be included more than once.                */
/*---------------------------------------------------------------------*/
#ifndef _PROBE_H
#define _PROBE_H

/*---------------------------------------------------------------------*/
/* db_output sends output to remote debugger                           */
/*---------------------------------------------------------------------*/
    long db_output(char *outbuff, unsigned long nbytes);

/*---------------------------------------------------------------------*/
/* db_input gets input from remote debugger                            */
/*---------------------------------------------------------------------*/
    long db_input(char *inbuff, unsigned long nbytes, char *prompt, 
      unsigned long pbytes, unsigned long *recvbytes);

/***********************************************************************/
/* pROBE+ Fatal Error Codes, returned by pROBE_init if pROBE           */
/* initialization fails.                                               */ 
/***********************************************************************/
#define PROBE_FAT_INSUFFMEM   0x1F01  /* Insufficient memory allocated */
                                      /* by TD_DATASIZE or REGION 0 too*/
                                      /* small                         */
#define PROBE_FAT_PROBETSK    0x1F02  /* DBG task creation error       */
#define PROBE_FAT_NO_IEXEC    0x1F03  /* pROBE+ Interface Executive not*/
                                      /* not installed                 */
#define PROBE_FAT_DRV_INIT_CE 0x1F04  /* failed to init Console IO     */
                                      /* driver                        */
#define PROBE_FAT_DRV_INIT_RD 0x1F05  /* failed to init Rbug IO driver */
#define PROBE_FAT_CHKSUM      0x1F0E  /* pROBE+ Checksum error         */

#endif /* _PROBE_H */

#if __cplusplus
}
#endif

