/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\ip_udp.h_v   1.0   Mar 29 1999 13:50:58   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/ip_udp.h 2.2 97/03/21 14:38:03 */
/************************************************************************
*                                                                    	*
*   MODULE:  ip_udp.h                                                   *
*   DATE:    97/03/21                                                   *
*   PURPOSE: IP/UDP protocol definitions				*
*                                                                    	*
*-----------------------------------------------------------------------*
*                                                                    	*
*          Copyright 1993, Software Components Group, Inc.           	*
*                  ALL RIGHTS RESERVED                               	*
*                                                                    	*
*   This computer program is the property of Software Components     	*
*   Group Inc., San Jose, Calif., U.S.A. and may not be copied       	*
*   in any form or by any means, whether in part or in whole,        	*
*   except under license expressly granted by Software Components    	*
*   Group Inc.                                                       	*
*                                                                    	*
*   All copies of this program, whether in part or in whole, and     	*
*   whether modified or not, must display this and all other         	*
*   embedded copyright and ownership notices in full.                	*
*                                                                    	*
************************************************************************/

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version

*/


#if __cplusplus
extern "C" {
#endif

#ifndef _BOOTP_IP_UDP_H
#define _BOOTP_IP_UDP_H

/*---------------------------------------------------------------------*/
/* Must include bsp.h to determine big/little endian                   */
/*---------------------------------------------------------------------*/
#include "bsp.h"
#include "types.h"

/*
 * Definitions for internet protocol version 4.
 * Per RFC 791, September 1981.
 */
#define	IPVERSION	4
#define	UDP_TTL	        30	/* deflt time to live for UDP packets */

/*
 * Structure of an internet header, naked of options.
 *
 * We declare ip_len and ip_off to be short, rather than USHORT
 * pragmatically since otherwise unsigned comparisons can result
 * against negative integers quite easily, and fail in subtle ways.
 */

struct iphdr {
#if BSP_LITTLE_ENDIAN
	UCHAR	ip_hl:4;		/* header length */
	UCHAR	ip_v:4;			/* version */
#else
	UCHAR	ip_v:4;			/* version */
	UCHAR	ip_hl:4;		/* header length */
#endif
	UCHAR	ip_tos;			/* type of service */
	USHORT	ip_len;			/* total length */
	USHORT	ip_id;			/* identification */
	USHORT	ip_off;			/* fragment offset field */
	UCHAR	ip_ttl;			/* time to live */
	UCHAR	ip_p;			/* protocol */
	USHORT	ip_sum;			/* checksum */
	ULONG   ip_src;                 /* source address */
    ULONG   ip_dst;	                /* destination address */
};

/*
 * Udp protocol header.
 * Per RFC 768, September, 1981.
 */
struct udphdr {
	USHORT	uh_sport;		/* source port */
	USHORT	uh_dport;		/* destination port */
	USHORT	uh_ulen;		/* udp length */
	USHORT	uh_sum;			/* udp checksum */
};

#define IP_TYPE             0x0800      /* IP packet */

#endif /* _BOOTP_IP_UDP_H */

#if __cplusplus
}
#endif

