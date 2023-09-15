/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\pna_mib.h_v   1.0   Mar 29 1999 13:51:02   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/pna_mib.h 1.5 93/04/29 11:38:45 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/pna_mib.h                                        */
/*   DATE:    93/04/29                                                 */
/*   PURPOSE: MIB II variable definitions                              */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*            Copyright 1991-1993, Integrated Systems, Inc.            */
/*                         ALL RIGHTS RESERVED                         */
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
#ifndef _PNA_MIB_H
#define _PNA_MIB_H

#include <pna.h>

#define SMEM_NET 1
#define E_NET    2

/*----------------------------------------------------------------------*/
/* Structure to describe the MIB parameter block passed during the      */
/* MIB call interface                                                   */
/*----------------------------------------------------------------------*/
struct mib_args
    {
    long len;
    char  *buffer;
    };

/************************************************************************/
/* Defines MIB II IP, TCP, UDP, ICMP objects                            */
/************************************************************************/

/*----------------------------------------------------------------------*/
/* Structure of ifreq MIB object                                        */
/*----------------------------------------------------------------------*/
struct mib_ifreq
  {
  long   ie_iindex;             /* Interface number (mib index) */
  union
      {
      long   ieu_index;         /* Interface number */
      char   *ieu_descr;        /* description of the interface */
      long   ieu_type;          /* type of the interface */
      long   ieu_mtu;           /* Maximum transmission unit */
      long   ieu_speed;         /* speed of the interface */
      struct sockaddr ieu_physaddress; /* media-specific address */
      long   ieu_adminstatus;   /* desired interface state */
      long   ieu_operstatus;    /* current operational status */
      long   ieu_lastchange;    /* last change in the interface status */
      long   ieu_inoctets;      /* total octets received from media */
      long   ieu_inucastpkts;   /* unicast packets delivered above */
      long   ieu_innucastpkts;  /* broadcast/muticast pkts delivered above */
      long   ieu_indiscards;    /* packets discarded due to resource limit */
      long   ieu_inerrors;      /* packets discarded due to format errors */
      long   ieu_inunknownprotos; /* packets for unknown protocols */
      long   ieu_outoctets;     /* total octets sent on the media */
      long   ieu_outucastpkts;  /* unicast packets from above */
      long   ieu_outnucastpkts; /* broadcast/multicast packets from above */
      long   ieu_outdiscards;   /* packets discarded due to res. limit */
      long   ieu_outerrors;     /* packets discarded due to errors */
      long   ieu_outqlen;       /* size of output queue */
      char   *ieu_specific;     /* MIB-specific pointer */
      } ieu_ieu;
  };
#define ie_index ieu_ieu.ieu_index
#define ie_descr ieu_ieu.ieu_descr
#define ie_type ieu_ieu.ieu_type
#define ie_mtu ieu_ieu.ieu_mtu
#define ie_speed ieu_ieu.ieu_speed
#define ie_physaddress ieu_ieu.ieu_physaddress
#define ie_adminstatus ieu_ieu.ieu_adminstatus
#define ie_operstatus ieu_ieu.ieu_operstatus
#define ie_lastchange ieu_ieu.ieu_lastchange
#define ie_inoctets ieu_ieu.ieu_inoctets
#define ie_inucastpkts ieu_ieu.ieu_inucastpkts
#define ie_innucastpkts ieu_ieu.ieu_innucastpkts
#define ie_indiscards ieu_ieu.ieu_indiscards
#define ie_inerrors ieu_ieu.ieu_inerrors
#define ie_inunknownprotos ieu_ieu.ieu_inunknownprotos
#define ie_outoctets ieu_ieu.ieu_outoctets
#define ie_outucastpkts ieu_ieu.ieu_outucastpkts
#define ie_outnucastpkts ieu_ieu.ieu_outnucastpkts
#define ie_outdiscards ieu_ieu.ieu_outdiscards
#define ie_outerrors ieu_ieu.ieu_outerrors
#define ie_outqlen ieu_ieu.ieu_outqlen
#define ie_specific ieu_ieu.ieu_specific

/*----------------------------------------------------------------------*/
/* Structure of the IP routing MIB object                               */
/*----------------------------------------------------------------------*/
struct mib_iproutereq
  {
  struct in_addr ir_idest;      /* Destination of the route (mib index)*/
  union
      {
      struct in_addr iru_dest;  /* Destination of the route */
      long   iru_ifindex;       /* Interface number of the route */
      struct in_addr iru_nexthop;   /* IP address for indirect address */
      long   iru_type;          /* Type of route */
      long   iru_proto;         /* mechanism used to determine route */
      long   iru_mask;          /* subnet-mask of the route */
      } iru_iru;
  };
#define ir_dest  iru_iru.iru_dest
#define ir_ifindex iru_iru.iru_ifindex
#define ir_nexthop iru_iru.iru_nexthop
#define ir_type iru_iru.iru_type
#define ir_proto iru_iru.iru_proto
#define ir_mask iru_iru.iru_mask

/*----------------------------------------------------------------------*/
/* Types of routes (other, invalid, direct, remote)                     */
/*----------------------------------------------------------------------*/
#define  RT_OTHER       1       /* Other type */
#define  RT_INVALID     2       /* Invalid route */
#define  RT_DIRECT      3       /* route to directly connected net/subnet */
#define  RT_INDIRECT    4       /* route to unconnected net/subnet */

/*----------------------------------------------------------------------*/
/* Routing protocol used (ICMP, LOCAL)                                  */
/*----------------------------------------------------------------------*/
#define  RP_LOCAL       2       /* Routing type is static */
#define  RP_ICMP        4       /* Routing protocol is ICMP */

/*----------------------------------------------------------------------*/
/* Structure of IP Addr MIB object                                      */
/*----------------------------------------------------------------------*/
struct mib_ipaddrreq
  {
  struct in_addr ia_iaddr;     /* IP address of this entry (mib index) */
  union
      {
      struct in_addr iau_addr;        /* IP address of this entry */
      long   iau_ifindex;       /* Interface number of the NI */
      long   iau_netmask;       /* subnet-mask for the IP address */
      long   iau_bcastaddr;     /* LSB of IP broadcast address */
      long   iau_reasmmaxsize;  /* Max. IP datagram reassembled */
      } iau_iau;
  };
#define ia_ipaddr iau_iau.iau_addr
#define ia_ifindex iau_iau.iau_ifindex
#define ia_netmask iau_iau.iau_netmask
#define ia_bcastaddr iau_iau.iau_bcastaddr
#define ia_reasmmaxsize iau_iau.iau_reasmmaxsize

/*----------------------------------------------------------------------*/
/* Structure of IP - Address translation MIB object                     */
/*----------------------------------------------------------------------*/
struct mib_ipnettomediareq
  {
  struct in_addr inm_iaddr;     /* IP address of the mapping (mib index)*/
  long   inm_iifindex;          /* Interface number (mib index) */
  union
      {
      long   inmu_ifindex;      /* Interface number (mib index) */
      struct sockaddr inmu_physaddress; /* media address mapping */
      struct in_addr inmu_netaddress;   /* IP address of the mapping */
      long   inmu_type;         /* procedure mapping was determined by */
      } inmu_inmu;
  };
#define inm_ifindex inmu_inmu.inmu_ifindex
#define inm_physaddress inmu_inmu.inmu_physaddress
#define inm_netaddress inmu_inmu.inmu_netaddress
#define inm_type inmu_inmu.inmu_type

/*----------------------------------------------------------------------*/
/* Definitions for type of NET-TO-MEDIA entries                         */
/*----------------------------------------------------------------------*/
#define NM_OTHER     1          /* Other type of net-media translation */
#define NM_INVALID   2          /* Invalid entry */
#define NM_DYNAMIC   3          /* Dyanmically aquired */
#define NM_STATIC    4          /* Static set of the entry */

/*----------------------------------------------------------------------*/
/* Definitions for TCP Algorithm types                                  */
/*----------------------------------------------------------------------*/
#define  TRA_OTHER        1     /* Other than specified below */
#define  TRA_CONSTANT     2     /* constant RTO */
#define  TRA_RSRE         3     /* mil-std-1778 appendix B */
#define  TRA_VANJ         4     /* Van Jocobson algorithm */

/*----------------------------------------------------------------------*/
/*  Structure of TCP connection MIB object                              */
/*----------------------------------------------------------------------*/
struct mib_tcpconnreq
  {
  struct in_addr tc_localaddress; /* local IP address */
  long  tc_localport;             /* local port */
  struct in_addr tc_remaddress;   /* remote IP address */
  long tc_remport;                /* remote port */
  union
      {
      long tcu_state;             /* state of the connection */
      } tcu_tcu;
  };
#define tc_state tcu_tcu.tcu_state

/*----------------------------------------------------------------------*/
/* Definitions for connection state of a tcp connection                 */
/*----------------------------------------------------------------------*/
#define TCPCS_CLOSED      1
#define TCPCS_LISTEN      2
#define TCPCS_SYNSENT     3
#define TCPCS_SYNRECEIVED 4
#define TCPCS_ESTABLISHED 5
#define TCPCS_FINWAIT1    6
#define TCPCS_FINWAIT2    7
#define TCPCS_CLOSEWAIT   8
#define TCPCS_LASTACK     9
#define TCPCS_CLOSING     10
#define TCPCS_TIMEWAIT    11
#define TCPCS_DELETETCB   12

/*----------------------------------------------------------------------*/
/* Structure of UDP table MIB object                                    */
/*----------------------------------------------------------------------*/
struct mib_udptabreq
    {
    struct in_addr u_localaddress; /* Local IP address */
    long u_localport;              /* Local port */
    };

#endif

#if __cplusplus
}
#endif

