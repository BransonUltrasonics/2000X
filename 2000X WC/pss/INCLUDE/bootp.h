/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\bootp.h_v   1.0   Mar 29 1999 13:50:54   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/bootp.h (&U&) 2.2 96/12/12 15:27:12 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  bootp.h                                                  */
/*   DATE:    96/12/12                                                 */
/*   PURPOSE: Definitions for BOOTP                                    */
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
/*                                                                     */
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
#ifndef _BOOTP_H
#define _BOOTP_H

/*****************************************************************************/
/* Generic types                                                             */
/*****************************************************************************/
#ifndef UCHAR
#define UCHAR unsigned char
#endif
#ifndef USHORT
#define USHORT unsigned short
#endif
#ifndef ULONG
#define ULONG unsigned long
#endif

/*****************************************************************************/
/* BOOTP Operations                                                          */
/*****************************************************************************/
#define BOOTP_REQUEST 1
#define BOOTP_REPLY   2

/*****************************************************************************/
/* BOOTP UDP ports                                                           */
/*****************************************************************************/
#define	IPPORT_BOOTPS		67
#define	IPPORT_BOOTPC		68

/*****************************************************************************/
/* BOOTP request default retries                                             */
/*****************************************************************************/
#define BOOTP_RETRIES 10

/*****************************************************************************/
/* Hardware definitions for Ethernet                                         */
/*****************************************************************************/
#define HTYPE_ETH     1
#define HTYPE_ETH_LEN 6

/*****************************************************************************/
/* BOOTP packet structure                                                    */
/*****************************************************************************/
#define VEND_SZ 64

typedef struct {
  UCHAR op;		 /* Operation type : 1 = REQ. : 2 = REPLY */
  UCHAR htype;		 /* Hardware address type e.g. 1 = ethernet */
  UCHAR hlen;		 /* Hardware address lenght e.g. ethernet = 6 */
  UCHAR hops;		 /* Used by server in cross gateway booting */
  ULONG xid;		 /* transaction ID - some random number */
  USHORT secs;		 /* Time elapsed since client started trying */
  USHORT flags;		 /* Only BROADCAST flag is used */
  struct in_addr ciaddr; /* Client IP - filled by client if known */
  struct in_addr yiaddr; /* Client IP - filled by server */
  struct in_addr siaddr; /* Server IP - filled by server */
  struct in_addr giaddr; /* Gateway IP - used during cross gateway boot */
  UCHAR chaddr[16];	 /* Client's hardware address */
  char sname[64];	 /* Boot server name, if known */
  char file[128];	 /* boot filename if known */
  UCHAR vend[VEND_SZ];	 /* Vendor extensions field */
} bootppkt_t;

/*****************************************************************************/
/* BOOTP packet size                                                         */
/*****************************************************************************/
#define BOOTP_SZ (sizeof(bootppkt_t))
#define IP_SZ    (sizeof(struct iphdr))
#define UDP_SZ   (sizeof(struct udphdr))

/*****************************************************************************/
/* BOOTP flags definition                                                    */
/*****************************************************************************/
#define BP_BROADCAST 0x8000      /* not used in this implementation          */

/*****************************************************************************/
/* Structure of the vendor extensions and the various tags                   */
/*****************************************************************************/
#define BOOTP_COOKIE 0x63825363	           /* 99.130.83.99 */
typedef struct {
  ULONG cookie;			           /* Magic cookie */
  UCHAR extensions[VEND_SZ-sizeof(ULONG)]; /* Vendor extension area */
} vendexts_t;


/*****************************************************************************/
/* Vendor extension definitions, as per RFC 1497                             */
/*                                                                           */
/* Non-data extensions :                                                     */
/*            ----------------                                               */
/*            | 1 tag octet  |                                               */
/*            ----------------                                               */
/* Fixed and Variable data extensions :                                      */
/*            ------------------------------------------------------         */
/*            | 1 tag octet  | 1 length octet | length data octets |         */
/*            ------------------------------------------------------         */
/*****************************************************************************/
#define SUBNET_MASK_TAG   1
#define GATEWAY_TAG       3
#define HOSTNAME_TAG      12
#define BOOTFILE_SIZE_TAG 13
#define BOOTP_SERVER_TAG  129	
#define END_TAG           255	/* End of extension field */

/*****************************************************************************/
/* Returned to user by get_bootp_params                                      */
/*****************************************************************************/
typedef struct {
  struct in_addr yourIP;	/* IP address of client */
  struct in_addr TFTPserverIP;	/* IP address of TFTP server */
  struct in_addr BOOTPserverIP;	/* IP address of peer BOOTP server */
  ULONG subnetmask;		/* subnetmask */
  struct in_addr gatewayIP;	/* IP address of default gateway */
  char hostname[64];		/* hostname of client */
  char bootfile_name[128];	/* name of bootfile */
  int bootfile_size;		/* size of bootfile */
} bootpparms_t;

/*****************************************************************************/
/* get_bootp_params flags                                                    */
/*****************************************************************************/
#define RAW  0x01
#define COOK 0x02
#define PSOSUP 0x04

#endif /* _BOOTP_H */

#if __cplusplus
}
#endif

