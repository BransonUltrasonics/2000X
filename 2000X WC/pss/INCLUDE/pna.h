/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\pna.h_v   1.0   Mar 29 1999 13:51:02   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/pna.h (68k) 1.65 97/10/31 17:17:34 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/pna.h                                            */
/*   DATE:    97/10/31                                                 */
/*   PURPOSE: Structure definitions, function prototypes, and symbol   */
/*            definitions for pNA+                                     */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*             Copyright 1991 - 1997 Integrated Systems, Inc.          */
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

/*---------------------------------------------------------------------*/
/* Don't allow this file to be included more than once.                */
/*---------------------------------------------------------------------*/
#ifndef _PNA_H
#define _PNA_H

#ifndef _BSP_H
#include "bsp.h"    /* This is required by htonl() and htons() swap macros */
#endif
#include <types.h>

/***********************************************************************/
/* General Definitions                                                 */
/***********************************************************************/

/*---------------------------------------------------------------------*/
/*  Socket types                                                       */
/*---------------------------------------------------------------------*/
#define SOCK_STREAM     0x1         /* stream socket */
#define SOCK_DGRAM      0x2         /* datagram socket */
#define SOCK_RAW        0x3         /* raw socket */

/*---------------------------------------------------------------------*/
/* Address family supported by pNA+                                    */
/*---------------------------------------------------------------------*/
#define AF_INET         0x2         /* internetwork: UDP, TCP, etc. */
#define AF_UNSPEC       0x0         /* unspec ified */

/*---------------------------------------------------------------------*/
/* Protocols Supported by pNA+                                         */
/*---------------------------------------------------------------------*/
#define ICMP            0x1         /* ICMP protocol */
#define IGMP            0x2         /* IGMP protocol */
#define TCP             0x6         /* TCP protocol */
#define UDP             0x11        /* UDP protocol */
#define IPPROTO_IP      0x0         /* IP protocol */
#define IPPROTO_ICMP    0x1         /* ICMP protocol */
#define IPPROTO_IGMP    0x2         /* IGMP protocol */
#define IPPROTO_TCP     0x6         /* TCP protocol */
#define IPPROTO_UDP     0x11        /* UDP protocol */

/*---------------------------------------------------------------------*/
/* Options for use with [gs]etsockopt at the IP level.                 */
/*---------------------------------------------------------------------*/
#define IP_OPTIONS          1      /* set/get IP per-packet options */
#define IP_HDRINCL          2      /* int; set/get header included with data */
#define IP_MULTICAST_IF     9      /* u_char; set/get IP multicast i/f  */
#define IP_MULTICAST_TTL    10     /* u_char; set/get IP multicast ttl */
#define IP_MULTICAST_LOOP   11     /* u_char; set/get IP multicast loopback*/
#define IP_ADD_MEMBERSHIP   12     /* ip_mreq; add an IP group membership */
#define IP_DROP_MEMBERSHIP  13     /* ip_mreq; drop an IP group membership */
#define	IP_MULTICAST_INTF   14     /* u_char; set/get IP multicast i/f */
#define	IP_ADD_MEMBERSHIP_INTF  15 /* ip_mreq_intf; add an IP group */
                                   /* membership given interface number */
#define	IP_DROP_MEMBERSHIP_INTF	16 /* ip_mreq_intf; drop an IP group */
                                   /* membership given interface number */

/*---------------------------------------------------------------------*/
/* Defaults and limits for options                                     */
/*---------------------------------------------------------------------*/
#define IP_DEFAULT_MULTICAST_TTL  1    /* normally limit m'casts to 1 hop */
#define IP_DEFAULT_MULTICAST_LOOP 1    /* normally hear sends if a member */
#define IP_MAX_MEMBERSHIPS        20   /* per socket; must fit in one mbuf */

/*---------------------------------------------------------------------*/
/* Options for use with [gs]etsockopt at the TCP level.                */
/*---------------------------------------------------------------------*/
#define TCP_NODELAY         1       /* set/get tcp nodelay option */
#define TCP_KEEPALIVE_IDLE  3       /* set/get TCP Keepalive timer value */
#define TCP_KEEPALIVE_CNT   4       /* set/get TCP Keepalive probe count */
#define TCP_KEEPALIVE_INTVL 5       /* set/get TCP Keepalive probing interval*/
#define TCP_MSL             6       /* set/get TCP Maximum Segment Lifetime */
 
/*---------------------------------------------------------------------*/
/* Level number for (get/set)sockopt() to apply to socket itself.      */
/*---------------------------------------------------------------------*/
#define SOL_SOCKET      0xFFFF      /* options for socket level */

/*---------------------------------------------------------------------*/
/* Maximum queue length specifiable by listen()                        */
/*---------------------------------------------------------------------*/
#define SOMAXCONN       0x5         /* maximum queue length */

/*---------------------------------------------------------------------*/
/* Socket Options used by setsockopt() and getsockopt()                */
/*---------------------------------------------------------------------*/
#define SO_ACCEPTCONN   0x0002      /* socket has had listen() */
#define SO_REUSEADDR    0x0004      /* allow reuse of local addresses */
#define SO_KEEPALIVE    0x0008      /* keep socket connections alive */
#define SO_DONTROUTE    0x0010      /* bypass routing for outgoing */
                                    /* messages */
#define SO_BROADCAST    0x0020      /* permission to transmit broadcast */
                                    /* messages */
#define SO_LINGER       0x0080      /* linger on close if data present */
#define SO_OOBINLINE    0x0100      /* leave received OOB data in line */
#define SO_REUSEPORT    0x0800      /* allow local address & port reuse */
#define SO_SNDBUF       0x1001      /* set buffer size for output */
#define SO_RCVBUF       0x1002      /* set buffer size for input */
#define SO_SNDLOWAT     0x1003      /* send low-water mark */
#define SO_RCVLOWAT     0x1004      /* receive low-water mark */
#define SO_SNDTIMEO     0x1005      /* send timeout */
#define SO_RCVTIMEO     0x1006      /* receive timeout */
#define SO_ERROR        0x1007      /* get error status and clear */
#define SO_TYPE         0x1008      /* get socket type */

/*---------------------------------------------------------------------*/
/* Flags Used by Send/Recieve Calls                                    */
/*---------------------------------------------------------------------*/
#define MSG_OOB         0x1         /* process out-of-band data */
#define MSG_PEEK        0x2         /* peek at incoming message */
#define MSG_DONTROUTE   0x4         /* send without using routing tables */
#define MSG_RAWMEM      0x8         /* send/recv using pNA memory  */
#define MSG_INTERFACE   0x10        /* send/recv interface information */

/*---------------------------------------------------------------------*/
/* Maximum Length of the Vectors used in sendmsg() and recvmsg()       */
/*---------------------------------------------------------------------*/
#define MSG_MAXIOVLEN   0x10

/***********************************************************************/
/* Control Commands for ioctl() to control socket action               */
/***********************************************************************/
#define FIOGETOWN       0x4004667C  /* Get owner of the socket */
#define FIOREAD         0x4004667F  /* Get bytes in socket read buffer */
#define FIOSETOWN       0x8004667C  /* Set owner of the socket */
#define FIOASYNC        0x8004667D  /* Set/Unset socket to receive */
                                    /* Asyncronous signal */
#define FIONBIO         0x8004667E  /* Set/Unset socket non-blocking */
#define SIOCATMARK      0x40047307  /* Get out of band data mark */
#define SIOCSIPTTL      0x80047308  /* Set the socket based IP TTL */
#define SIOCGIPTTL      0xC0047308  /* Get the socket based IP TTL */
#define SIOCSSBMAX      0x80047309  /* Set send/recv socket buffer size */
#define SIOCGSBMAX      0xC0047309  /* Get send/recv socket buffer size */

/*----------------------------------------------------------------------*/
/* Definitions for Routing entries                                      */
/*----------------------------------------------------------------------*/
#define SIOCADDRT       0x8034720A  /* add route */
#define SIOCDELRT       0x8034720B  /* delete route */
#define SIOCRSTRT       0x8034720C  /* reset route */
#define SIOCMODRT       0x8034720D  /* modify route */

/*----------------------------------------------------------------------*/
/* Definitions for Network Node ID options                              */
/*----------------------------------------------------------------------*/
#define SIOCSNNODEID    0x80346E0A /* set the Network Node ID */
#define SIOCGNNODEID    0xC0346E0B /* get the Network Node ID */

/*----------------------------------------------------------------------*/
/* Definitions for NI parameters                                        */
/*----------------------------------------------------------------------*/
#define SIOCSIFADDR     0x8014690C  /* set interface ip address */
#define SIOCGIFADDR     0xC014690D  /* get interface ip address */
#define SIOCSIFDSTADDR  0x8014690E  /* set point-to-point dest. address */
#define SIOCGIFDSTADDR  0xC014690F  /* get point-to-point dest. address */
#define SIOCSIFFLAGS    0x80146910  /* set interface flags */
#define SIOCGIFFLAGS    0xC0146911  /* get interface flags */
#define SIOCGIFBRDADDR  0xC0146912  /* get interface broadcast addr */
#define SIOCSIFBRDADDR  0x80146913  /* set interface broadcast addr */
#define SIOCGIFCONF     0xC0086914  /* get interface configuration list */
#define SIOCGIFNETMASK  0xC0146915  /* get interface net addr mask */
#define SIOCSIFNETMASK  0x80146916  /* set interface net addr mask */
#define SIOCGIFMTU      0xC0146917  /* get interface MTU */
#define SIOCSIFMTU      0X80146918  /* set interface MTU */
#define SIOCPSOSINIT    0x8004730A  /* re/initialized interface */

/*----------------------------------------------------------------------*/
/* Definitions for IP Multicast Options                                 */
/*----------------------------------------------------------------------*/
#define SIOCADDMCAST    0x80346D0A  /* add m'cast addr */
#define SIOCDELMCAST    0x80346D0B  /* del m'cast addr */
#define SIOCMAPMCAST    0x80346D0C  /* map m'cast addr */

/*----------------------------------------------------------------------*/
/* Definitions for ARP entries                                          */
/*----------------------------------------------------------------------*/
#define SIOCSARP        0x8024691E  /* set arp entry */
#define SIOCGARP        0xC024691F  /* get arp entry */
#define SIOCDARP        0x80246920  /* delete arp entry */

/*----------------------------------------------------------------------*/
/* Definitions for UDP Checksum Options                                 */
/*----------------------------------------------------------------------*/
#define SIOCSUDPCHKSUM  0x8024751E  /* set udp checksumming on/off */
#define SIOCGUDPCHKSUM  0xC024751F  /* get udp checksumming mode */

/*----------------------------------------------------------------------*/
/* Definitions for Interface Group MIB variables                        */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGIFNUMBER       0x40016D01 /* get interface number */
#define SIOCGIFTABLE        0x40016D02 /* get Interface table */
#define SIOCGIFINDEX        0x40016D03 /*  get NI index */
#define SIOCGIFDESCR        0x40016D04 /* Get ni descr */
#define SIOCGIFTYPE         0x40016D05 /* Get NI type */
#define SIOCGIFMTUNIT       0x40016D06 /* Get NI mtu */
#define SIOCGIFSPEED        0x40016D07 /* Get NI speed */
#define SIOCGIFPHYSADDRESS  0x40016D08 /* Get ni Phy. Address */
#define SIOCGIFADMINSTATUS  0x40016D09 /* Get ni admin status */
#define SIOCGIFOPERSTATUS   0x40016D0A /* Get NI operatioanl status */
#define SIOCGIFLASTCHANGE   0x40016D0B /* Get last change in status */
#define SIOCGIFINOCTETS     0x40016D0C /* Get no of octets rcvd. */
#define SIOCGIFINUCASTPKTS  0x40016D0D /* Get no. of unicast pkts rcvd  */
#define SIOCGIFINNUCASTPKTS 0x40016D0E /* Get no. of multi. pkts rcvd */
#define SIOCGIFINDISCARDS   0x40016D0F /* Get no of pckts discarded */
#define SIOCGIFINERRORS     0x40016D10 /* Get no of error pckts */
#define SIOCGIFINUNKNOWNPROTOS 0x40016D11 /* No of pckts for unk. protocol */
#define SIOCGIFOUTOCTETS    0x40016D12 /* No of octets rcvd */
#define SIOCGIFOUTUCASTPKTS 0x40016D13 /* No of unicast pkts sent */
#define SIOCGIFOUTNUCASTPKTS 0x40016D14 /* No of multi. pkts sent */
#define SIOCGIFOUTDISCARDS  0x40016D15 /* No of out pkts discarded */
#define SIOCGIFOUTERRORS    0x40016D16 /* No of outbounds pkts errors */
#define SIOCGIFOUTQLEN      0x40016D17 /* Length of output Q length */
#define SIOCGIFSPECIFIC     0x40016D18 /* NI specific parameter */

/*----------------------------------------------------------------------*/
/* set command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCSIFADMINSTATUS  0x80016D09 /* set Interface admin. status */

/*----------------------------------------------------------------------*/
/* Definitions for IP Group MIB variables                               */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGIPFORWARDING   0x40026D01 /* IP forwarding var.   */
#define SIOCGIPDEFAULTTTL   0x40026D02 /* IP def. Time-to-Live var */
#define SIOCGIPINRECEIVES   0x40026D03 /* IP dgrams rec. from below */
#define SIOCGIPINHDRERRORS  0x40026D04 /* IP dgrams format errs drops */
#define SIOCGIPINADDRERRORS 0x40026D05 /* IP dgrams misdelivery drops */
#define SIOCGIPFORWDATAGRAMS 0x40026D06 /* IP dgrams forwarded */
#define SIOCGIPINUNKNOWNPROTOS 0x40026D07 /* IP unknown proto. dgrams */
#define SIOCGIPINDISCARDS   0x40026D08 /* IP disc. dgrms for resources */
#define SIOCGIPINDELIVERS   0x40026D09 /* IP dgrams delivered above */
#define SIOCGIPOUTREQUESTS  0x40026D0A /* IP dgrams sent out */
#define SIOCGIPOUTDISCARDS  0x40026D0B /* IP out dgrams discarded */
#define SIOCGIPOUTNOROUTES  0x40026D0C /* IP dgrams drops for no routes */
#define SIOCGIPREASMTIMEOUT 0x40026D0D /* IP retrans. queue timeout */
#define SIOCGIPREASMREQDS   0x40026D0E /* IP frags. needing reass. */
#define SIOCGIPREASMOKS     0x40026D0F /* IP frags. reassembled */
#define SIOCGIPREASMFAILS   0x40026D10 /* IP frag reassembly fails */
#define SIOCGIPFRAGOKS      0x40026D11 /* IP dgrams fragmented */
#define SIOCGIPFRAGFAILS    0x40026D12 /* IP dgrams fragmentation fails */
#define SIOCGIPFRAGCREATES  0x40026D13 /* IP frags. created */
#define SIOCGIPROUTINGDISCARDS 0x40026D14 /* IP Routing ent. discarded */

/*----------------------------------------------------------------------*/
/* SET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCSIPFORWARDING   0x80026D01 /* IP forwarding variable */
#define SIOCSIPDEFAULTTTL   0x80026D02 /* IP Defautl time-to-live */
#define SIOCSIPREASMTIMEOUT 0x80026D0D /*  IP retrans. queue timeout */

/*----------------------------------------------------------------------*/
/* Definitions for IP NI address table                                  */
/* GET commands definitions                                             */
/*----------------------------------------------------------------------*/
#define SIOCGIPADDRTABLE    0x40036D01 /* IP Address table */
#define SIOCGIPADDRENTADDR  0x40036D03 /* IP Address of the addr entry */
#define SIOCGIPADDRENTIFINDEX 0x40036D04 /* NI number of the interface */
#define SIOCGIPADDRENTNETMASK 0x40036D05 /* Netmask of the NI */
#define SIOCGIPADDRENTBCASTADDR 0x40036D06 /* IP Broadcast Address of the NI*/
#define SIOCGIPADDRENTREASMMAXSIZE 0x40036D07 /* IP max. reassm. size */

/*----------------------------------------------------------------------*/
/* Definitions for IP route table                                       */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGIPROUTETABLE   0x40046D01 /* IP routing table */
#define SIOCGIPROUTEDEST    0x40046D03 /* Route destination */
#define SIOCGIPROUTEIFINDEX 0x40046D04 /* Interface Index of the route */
#define SIOCGIPROUTENEXTHOP 0x40046D05 /* Next hop of the route */
#define SIOCGIPROUTETYPE    0x40046D06 /* Type of the route */
#define SIOCGIPROUTEPROTO   0x40046D07 /* Protocol used by the route */
#define SIOCGIPROUTEAGE     0x40046D08 /* Age of the Route  */
#define SIOCGIPROUTEMASK    0x40046D09 /* Mask used by the route */

/*----------------------------------------------------------------------*/
/* SET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCSIPROUTEDEST    0x80046D03 /* Route destination */
#define SIOCSIPROUTENEXTHOP 0x80046D05 /* Next hop of the route */
#define SIOCSIPROUTETYPE    0x80046D06 /* Type of the route */

/*----------------------------------------------------------------------*/
/* Definitions for IP NET-TO-MEDIA table                                */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGIPNETTOMEDIATABLE 0x40056D01 /* IP Net-to-Media table */
#define SIOCGIPNETTOMEDIAIFINDEX 0x40056D03 /* Index of the Entry */
#define SIOCGIPNETTOMEDIAPHYSADDRESS 0x40056D04 /* Physical add. of entry */
#define SIOCGIPNETTOMEDIANETADDRESS 0x40056D05 /* IP address of entry   */
#define SIOCGIPNETTOMEDIATYPE 0x40056D06 /* Type of the entry     */

/*----------------------------------------------------------------------*/
/* SET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCSIPNETTOMEDIAPHYSADDRESS 0x80056D04 /* Physical add. of entry */
#define SIOCSIPNETTOMEDIANETADDRESS 0x80056D05 /* IP address of entry   */
#define SIOCSIPNETTOMEDIATYPE 0x80056D06

/*----------------------------------------------------------------------*/
/* Definitions for ICMP Group MIB variables                             */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGICMPINMSGS     0x40066D01 /* ICMP msgs. received */
#define SIOCGICMPINERRORS   0x40066D02 /* ICMP msgs. with format errs */
#define SIOCGICMPINDESTUNREACHS 0x40066D03 /* ICMP dest. Unreach. msgs rcvd*/
#define SIOCGICMPINTIMEEXCDS 0x40066D04 /* ICMP time excds. msgs. rcvd. */
#define SIOCGICMPINPARAMPROBS 0x40066D05 /* ICMP param. prob. msgs rcvd */
#define SIOCGICMPINSRCQUENCHS 0x40066D06 /*ICMP src. quench msgs rcvd */
#define SIOCGICMPINREDIRECTS 0x40066D07 /* ICMP src quenchs rcvd */
#define SIOCGICMPINECHOS    0x40066D08 /* ICMP echo msgs rcvd */
#define SIOCGICMPINECHOREPS 0x40066D09 /* ICMP echo reply msgs rcvd */
#define SIOCGICMPINTIMESTAMPS 0x40066D0A /* ICMP time stamp msgs rcvd */
#define SIOCGICMPINTIMESTAMPREPS 0x40066D0B /* ICMP time stp rep msgs rcvd */
#define SIOCGICMPINADDRMASKS 0x40066D0C /* ICMP address masks msgs rcvd */
#define SIOCGICMPINADDRMASKREPS 0x40066D0D /*ICMP addr masks reps msgs rcvd */
#define SIOCGICMPOUTMSGS    0x40066D0E /* ICMP messages sent */
#define SIOCGICMPOUTERRORS  0x40066D0F /* ICMP out error msgs. */
#define SIOCGICMPOUTDESTUNREACHS 0x40066D10 /* ICMP dest unreach msgs sent */
#define SIOCGICMPOUTTIMEEXCDS 0x40066D11 /* ICMP time exceed msgs sent */
#define SIOCGICMPOUTPARAMPROBS 0x40066D12 /* ICMP param prob. msgs sent */
#define SIOCGICMPOUTSRCQUENCHS 0x40066D13 /* ICMP src quench msgs sent */
#define SIOCGICMPOUTREDIRECTS 0x40066D14 /* ICMP redirect msgs sent */
#define SIOCGICMPOUTECHOS   0x40066D15 /* ICMP echo msgs sent */
#define SIOCGICMPOUTECHOREPS 0x40066D16 /* ICMP echo reply msgs sent */
#define SIOCGICMPOUTTIMESTAMPS 0x40066D17 /* ICMP time stamps msgs sent */
#define SIOCGICMPOUTTIMESTAMPREPS 0x40066D18 /* ICMP time stps reps sent */
#define SIOCGICMPOUTADDRMASKS 0x40066D19 /* ICMP addr mask msgs sent */
#define SIOCGICMPOUTADDRMASKREPS 0x40066D1A /* ICMP addr mask rep msgs sent */

/*----------------------------------------------------------------------*/
/* Definitions for TCP Group MIB variables                              */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGTCPRTOALGORITHM 0x40076D01 /* TCP retransmission algorithm */
#define SIOCGTCPRTOMIN      0x40076D02 /* TCP min. retrans. timeout */
#define SIOCGTCPRTOMAX      0x40076D03 /* TCP max. retrans. timeout */
#define SIOCGTCPMAXCONN     0x40076D04 /* TCP max. simul. connections */
#define SIOCGTCPACTIVEOPENS 0x40076D05 /* TCP active opens */
#define SIOCGTCPPASSIVEOPENS 0x40076D06 /* TCP number of passive opens */
#define SIOCGTCPATTEMPTFAILS 0x40076D07 /* TCP no. of failed conn. attempts*/
#define SIOCGTCPESTABRESETS 0x40076D08 /* TCP no. connections reset */
#define SIOCGTCPCURRESTAB   0x40076D09 /* TCP no. of curr. connections */
#define SIOCGTCPINSEGS      0x40076D0A /* TCP no. of segs. received */
#define SIOCGTCPOUTSEGS     0x40076D0B /* TCP no. of segs. sent */
#define SIOCGTCPRETRANSSEGS 0x40076D0C /* TCP no. of segs retransmitted */
#define SIOCGTCPCONNTABLE   0x40076D0D /* TCP connection table */
#define SIOCGTCPCONNSTATE   0x40076D0E /* TCP connection entry */
#define SIOCGTCPINERRS      0x40076D0F /* TCP no. of segs. disc. due to errs*/
#define SIOCGTCPOUTRSTS     0x40076D10 /* TCP no. of reset segs. sent */

/*----------------------------------------------------------------------*/
/* SET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCSTCPCONNSTATE  0x80076D0E  /* TCP connection entry */

/*----------------------------------------------------------------------*/
/* Definitions for UDP MIB variables                                    */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGUDPINDATAGRAMS 0x40086D01 /* UDP dgrams delivered */
#define SIOCGUDPNOPORTS    0x40086D02 /* UDP dgrams rcvd for unkown ports*/
#define SIOCGUDPINERRORS   0x40086D03 /* UDP dgrams dropped to format errs*/
#define SIOCGUDPOUTDATAGRAMS 0x40086D04 /* UDP dgrms sent from appls. */
#define SIOCGUDPTABLE      0x40086D05 /* UDP table */
/*----------------------------------------------------------------------*/
/* Definitions for MBUF statistics                                      */
/*----------------------------------------------------------------------*/
#define SIOCGMBSTAT        0x40FF7301 /* Mblks statistics */
#define SIOCGDBSTAT        0x40ff7302 /* Data Block statistics */

/*---------------------------------------------------------------------*/
/* Control Commands for shutdown() to control socket action            */
/*---------------------------------------------------------------------*/
#define FREAD           0x00        /* Shutdown read buffer */
#define FWRITE          0x01        /* Shutdown write buffer */

/*---------------------------------------------------------------------*/
/* Asynchronous signals generated by pNA                               */
/*---------------------------------------------------------------------*/
#define SIGIO           0x40000000  /* Signal I/O on socket */
#define SIGPIPE         0x20000000  /* Signal PIPE on socket */
#define SIGURG          0x10000000  /* Signal Urgent data on socket */
#define SIGINTF         0x08000000  /* Signal change in Interface Status */

/*---------------------------------------------------------------------*/
/* Definitions for type of route                                       */
/*---------------------------------------------------------------------*/
#define RT_NETWORK      0x0         /* Network Route */
#define RT_HOST         0x1         /* Host Route */
#define RT_MASK         0x2         /* Subnet Route with mask */


/***********************************************************************/
/* Definitions of bits in internet address integers.                   */
/***********************************************************************/
/*---------------------------------------------------------------------*/
/* Class A Network                                                     */
/*---------------------------------------------------------------------*/
#define IN_CLASSA(i)     (((long)(i) & 0x80000000) == 0)
#define IN_CLASSA_NET    0xFF000000
#define IN_CLASSA_NSHIFT 0x18
#define IN_CLASSA_HOST   0x00FFFFFF
#define IN_CLASSA_MAX    0x80

/*---------------------------------------------------------------------*/
/* Class B Network                                                     */
/*---------------------------------------------------------------------*/
#define IN_CLASSB(i)     (((long)(i) & 0xc0000000) == 0x80000000)
#define IN_CLASSB_NET    0xFFFF0000
#define IN_CLASSB_NSHIFT 0x10
#define IN_CLASSB_HOST   0x0000FFFF
#define IN_CLASSB_MAX    0x10000

/*---------------------------------------------------------------------*/
/* Class C Network                                                     */
/*---------------------------------------------------------------------*/
#define IN_CLASSC(i)     (((long)(i) & 0xe0000000) == 0xc0000000)
#define IN_CLASSC_NET    0xFFFFFF00
#define IN_CLASSC_NSHIFT 0x8
#define IN_CLASSC_HOST   0x000000FF

/*---------------------------------------------------------------------*/
/* Broadcast and Default Address Definitions                           */
/*---------------------------------------------------------------------*/
#define INADDR_ANY       (unsigned long)0x00000000
#define INADDR_BROADCAST (unsigned long)0xFFFFFFFF

/*----------------------------------------------------------------------*/
/* Generic Socket address                                               */
/*----------------------------------------------------------------------*/
struct sockaddr
  {
  unsigned short sa_family;
  char  sa_data[14];
  };

/*---------------------------------------------------------------------*/
/* Berkeley Internet address                                           */
/*---------------------------------------------------------------------*/
struct in_addr
    {
    unsigned long s_addr;       /* IP address of the socket */
    };

/*---------------------------------------------------------------------*/
/* Socket address, internet style.                                     */
/*---------------------------------------------------------------------*/
struct sockaddr_in
    {
    short sin_family;           /* must be AF_INET */
    unsigned short sin_port;    /* 16-bit port number */
    struct in_addr sin_addr;    /* 32-bit IP address */
    char sin_zero[8];           /* must be 0 */
    };

/*---------------------------------------------------------------------*/
/* Socket address with interface information                           */
/*---------------------------------------------------------------------*/
struct sockaddr_intf {
    short sin_family;         /* must be AF_INET */
    unsigned short sin_port;  /* 16-bit port number */ 
    struct in_addr sin_addr;  /* 32-bit IP address */
    long sin_ifno;            /* 32-bit interface number */
    char sin_zero[4];         /* must be 0 */
};

/*---------------------------------------------------------------------*/
/* Structure used for manipulating linger option.                      */
/*---------------------------------------------------------------------*/
struct linger
    {
    int l_onoff;        /* option on/off */
    int l_linger;       /* linger time */
    };

/***********************************************************************/
/* Structures for sendmsg() and recvmsg()                              */
/***********************************************************************/

/*---------------------------------------------------------------------*/
/* IO vector structure for sendmsg() and recvmsg()                     */
/*---------------------------------------------------------------------*/
struct iovec
    {
    char *iov_base;     /* base address */
    int iov_len;        /* buffer length */
    };

/*---------------------------------------------------------------------*/
/* Message header for sendmsg() and recvmsg()                          */
/*---------------------------------------------------------------------*/
struct msghdr
    {
    char *msg_name;             /* optional address */
    int msg_namelen;            /* size of address */
    struct iovec *msg_iov;      /* scatter/gather array */
    int msg_iovlen;             /* # elements in msg_iov */
    char *msg_accrights;        /* access rights */
    int msg_accrightslen;       /* length of the rights buffer */
    };

/***********************************************************************/
/* Definitions for select().  Select uses bit masks of file descrip-   */
/* tors in longs.  These macros manipulate such bit fields.            */
/***********************************************************************/
#define FD_SETSIZE      0x100
#define NFDBITS         0x20        /* bits per mask */

/*---------------------------------------------------------------------*/
/* Definition for fd_set structure used in select().                   */
/*---------------------------------------------------------------------*/
typedef struct fd_set
    {
    long fds_bits[8];
    } fd_set;

/***********************************************************************/
/* Macros for Select fd_sets                                           */
/***********************************************************************/

/*---------------------------------------------------------------------*/
/* Sets bit 'n' in the bitmask.                                        */
/*---------------------------------------------------------------------*/
#define FD_SET(n, p)    ((p)->fds_bits[(n)/NFDBITS] |= \
                        (((unsigned long) 0x80000000) >> ((n) % NFDBITS)))

/*---------------------------------------------------------------------*/
/* Clears bit 'n' in the bitmask.                                      */
/*---------------------------------------------------------------------*/
#define FD_CLR(n, p)    ((p)->fds_bits[(n)/NFDBITS] &= \
                       ~(((unsigned long) 0x80000000) >> ((n) % NFDBITS)))

/*---------------------------------------------------------------------*/
/* Checks to see if bit 'n' is set.                                    */
/*---------------------------------------------------------------------*/
#define FD_ISSET(n, p)  ((p)->fds_bits[(n)/NFDBITS] & \
                        (((unsigned long) 0x80000000) >> ((n) % NFDBITS)))

/*---------------------------------------------------------------------*/
/* Zeroes out the fd_set.                                              */
/*---------------------------------------------------------------------*/
#define FD_ZERO(p)   {                        \
                        (p)->fds_bits[0] = 0; \
                        (p)->fds_bits[1] = 0; \
                        (p)->fds_bits[2] = 0; \
                        (p)->fds_bits[3] = 0; \
                        (p)->fds_bits[4] = 0; \
                        (p)->fds_bits[5] = 0; \
                        (p)->fds_bits[6] = 0; \
                        (p)->fds_bits[7] = 0; \
                     }

/*---------------------------------------------------------------------*/
/* Timeval structure used in select()                                  */
/*---------------------------------------------------------------------*/
struct timeval
    {
    long  tv_sec;       /* no. of seconds */
    long  tv_usec;      /* no. of micro seconds */
    };

/*----------------------------------------------------------------------*/
/* Message block statistics                                             */
/*----------------------------------------------------------------------*/
struct mbstat
    {
    long mb_bufclasses;           /* Number of buffer classes */
    long mb_mblks;                /* Number of  mblks configured */
    long mb_free;                 /* Number of available mblks */
    long mb_wait;                 /* Number of times waited for mblk */
    long mb_drops;                /* Number of times failed to get mblk */
    };
/*----------------------------------------------------------------------*/
/* Data blocks statistics                                               */
/*----------------------------------------------------------------------*/
struct dbstat
    {
    long db_size;                 /* Size of data block */
    long db_dblks;                /* Number of data blocks */
    long db_free;                 /* number of free data blocks */
    long db_wait;                 /* Number of times waited to get dblk */
    long db_drops;                /* Number of times failed to get dblk */
    long db_reserved[2];          /* Reserved entries */
    };
/*----------------------------------------------------------------------*/
/*  Structure to request data block statistics using ioctl call         */
/*----------------------------------------------------------------------*/
struct dbreq
    {
    long size;
    struct dbstat *dsp;
    };

/*----------------------------------------------------------------------*/
/* rtentry structure used in ioctl() call to communicate routes to      */
/* pNA routing table. rt_netmask is ignored unless the RTF_MASK is      */
/* set in the rt_flags entry. If rt_netmask is not filled in then pNA+  */
/* will compute a mask based on the class of the address. Optionally    */
/* rt_ifno may be used to specify the outgoing interface of a route.    */
/* This is helpful with unnumbered links where the outgoing interface   */
/* cannot be defined by just the interface IP address.                  */
/*----------------------------------------------------------------------*/
struct rtentry
    {
    struct sockaddr rt_dst;       /* key to access the route*/
    struct sockaddr rt_gateway;   /* route gateway */
    unsigned short rt_flags;      /* host/net */
    unsigned short rt_reserved;   /* reserved */
    unsigned long rt_netmask;     /* netmask of route - ignored unless */
                                  /* RTF_MASK is set in rt_flags */
    long rt_ifno;                 /* intf num for local interface - ignored */
                                  /* unless RTF_INTF is set in rt_flags */
    unsigned long rt_reserved2[2];/* reserved */
    };


#define RTF_HOST     0x1           /* host entry (net otherwise) */
#define RTF_GATEWAY  0x2           /* destination is a gateway */
#define RTF_UP       0x4           /* route is usable */
#define RTF_DYNAMIC  0x10          /* created dynamically (by redirect) */
#define RTF_MODIFIED 0x20          /* modified dynamically (by redirect) */
#define RTF_INTF     0x40          /* route via a given intf */
#define RTF_MASK     0x80          /* Uses Subnet version */

/*---------------------------------------------------------------------*/
/* Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.    */
/*---------------------------------------------------------------------*/
struct ip_mreq {
    struct  in_addr imr_mcastaddr;  /* IP multicast address of group */
    struct  in_addr imr_interface;  /* local IP address of interface */
};

/*--------------------------------------------------------------------------*/
/* Argument structure for IP_ADD_MEMBERSHIP_INTF and IP_DROP_MEMBERSHIP_INTF*/
/*--------------------------------------------------------------------------*/
struct ip_mreq_intf {
    struct  in_addr imrif_mcastaddr; /* IP multicast address of group */
    long imrif_ifno;                 /* local interface number */
};

/*----------------------------------------------------------------------*/
/* ifreq structure used in ioctl() call for getting NI characteristics  */
/*----------------------------------------------------------------------*/
struct ifreq
    {
    long ifr_ifno;
    union
        {
        struct sockaddr ifru_addr;
        struct sockaddr ifru_dstaddr;
        struct sockaddr ifru_broadaddr;
        unsigned long   ifru_flags;
        int             ifru_mtu;
        char            *ifru_data;
        } ifr_ifru;
#define ifr_addr        ifr_ifru.ifru_addr      /* address */
#define ifr_dstaddr     ifr_ifru.ifru_dstaddr   /* other end of p-to-p link */
#define ifr_broadaddr   ifr_ifru.ifru_broadaddr /* broadcast address */
#define ifr_flags       ifr_ifru.ifru_flags     /* flags */
#define ifr_mtu         ifr_ifru.ifru_mtu       /* mtu */
#define ifr_data        ifr_ifru.ifru_data      /* for use by interface */
    };

/*----------------------------------------------------------------------*/
/* ifconf structure used in ioctl() call for getting NI configuration   */
/* using SIOCGIFCONF command                                            */
/*----------------------------------------------------------------------*/
struct ifconf
    {
    int  ifc_len;         /* size of associated buffer */
    union
        {
        char *ifcu_buf;
        struct ifreq *ifcu_req;
        } ifc_ifcu;
#define ifc_buf ifc_ifcu.ifcu_buf       /* buffer address */
#define ifc_req ifc_ifcu.ifcu_req       /* array of structures returned */
    };

/*----------------------------------------------------------------------*/
/* Definitions of the flags for the Network Interfaces                  */
/*----------------------------------------------------------------------*/
#define IFF_BROADCAST      0x1     /* broadcast flag of the NI */
#define IFF_NOARP          0x2     /* no address resolution protocol */
#define IFF_POINTTOPOINT   0x10    /* interface is point-to-point link */
#define IFF_POINTOPOINT IFF_POINTTOPOINT  /* to conform to UNIX */
#define IFF_UP             0x80    /* interface is up */
#define IFF_MULTICAST      0x800   /* supports multicast */
#define IFF_UNNUMBERED     0x1000  /* unnumbered interface */
#define IFF_RAWMEM         0x2000  /* driver will accept mblk link list */
#define IFF_EXTLOOPBACK    0x4000  /* Loopback externally */
#define IFF_POLL           0x8000  /* interface is a polling type */
#define IFF_INITDOWN       0x10000 /* interface must initialize in down state*/
 
/*----------------------------------------------------------------------*/
/* arpreq structure used in ioctl() call to get ARP entries             */
/*----------------------------------------------------------------------*/
struct arpreq
    {
    struct sockaddr arp_pa;     /* protocol address */
    struct sockaddr arp_ha;     /* hardware address */
    int arp_flags;              /* flags */
    };
#define ATF_INUSE  0x01         /* Entry is in use */
#define ATF_COM    0x02         /* Entry is complete */
#define ATF_PERM   0x04         /* permanent entry */
#define ATF_PUBL   0x08         /* publish entry */

/*---------------------------------------------------------------------*/
/* NI table entry.  Used by pNA configuration table and by add_ni().   */
/*---------------------------------------------------------------------*/
struct ni_init
    {
    int (*entry)();     /* address of NI entry point */
    int ipadd;          /* IP address */
    int mtu;            /* maximum transmission length */
    int hwalen;         /* length of hardware address */
    int flags;          /* interface flags */
    int subnetaddr;     /* subnet mask */
    int dstipaddr;      /* destination ip address */
    int reserved[1];    /* reserved for future use */
    };

/*---------------------------------------------------------------------*/
/* Routing table entry.  Used by pNA configuration table               */
/*---------------------------------------------------------------------*/
struct route
    {
    ULONG nwipadd;      /* network address */
    ULONG gwipadd;      /* gateway IP address */
    ULONG flags;        /* add to Network/host */
    ULONG netmask;      /* subnet mask - ignored unless RT_MASK flag */
                        /* is set */
    };

/*---------------------------------------------------------------------*/
/* Arp table entry.  Used by pNA configuration table.                  */
/*---------------------------------------------------------------------*/
struct arp
    {
    long arp_ipadd;     /* IP address of the NI */
    char *arp_hadd;     /* NI (hardware) address */
    long reserved[2];   /* reserved for future use */
    };

/*---------------------------------------------------------------------*/
/* Host table entry. Used by pNA configuration table                   */
/*---------------------------------------------------------------------*/
struct htentry
    {
    unsigned long ht_ipadd;       /* IP address of the host */
    char *ht_name;                /* Name of the host */
    long reserved[2];             /* reserved for future use */
    };

/*----------------------------------------------------------------------*/
/* Definition of the buffer configuration table                         */
/*----------------------------------------------------------------------*/
struct pna_bufcfg
    {
    unsigned long pna_nbuffers;   /* Number of buffers */
    unsigned long pna_bsize;      /* Buffer size */
    unsigned long reserved[2];    /* Reserved entries */
    };

/*---------------------------------------------------------------------*/
/* Definitions for Network Order Conversions Routines                  */
/*---------------------------------------------------------------------*/
#if BSP_LITTLE_ENDIAN
    /*-----------------------------------------------------------------*/
    /* Change byte order so the least significant byte is stored at    */
    /* the lowest address. Unsigned to prevent integer overflow on     */
    /* i960. Big endian cast unsigned for constant handling of vars.   */
    /*-----------------------------------------------------------------*/
    #define htonl(addr)     ( (((ULONG)(addr) & 0x000000FF)<<24) | \
                             (((ULONG)(addr) & 0x0000FF00)<<8)  | \
                             (((ULONG)(addr) & 0x00FF0000)>>8)  | \
                             (((ULONG)(addr) & 0xFF000000)>>24))
 
    #define ntohl(addr)     htonl(addr)
 
    #define htons(addr)     ( (((USHORT)(addr) & 0x000000FF)<<8)  | \
                             (((USHORT)(addr) & 0x0000FF00)>>8))
 
    #define ntohs(addr)     htons(addr)
#else

    #define htonl(a)       ((ULONG)(a))
    #define ntohl(a)       ((ULONG)(a))
    #define htons(a)       ((USHORT)(a))
    #define ntohs(a)       ((USHORT)(a))
#endif

/*----------------------------------------------------------------------*/
/* class 0 data buffer freeing structure definition (SVR4 feature )     */
/*----------------------------------------------------------------------*/
#ifndef _FREE_RTN
#define _FREE_RTN
struct free_rtn
    {
    void   (*free_func)(void *);
    void   *free_arg;
    };
typedef struct free_rtn frtn_t;
#endif /* _FREE_RTN */

/*----------------------------------------------------------------------*/
/* msgb structure definition                                            */
/*----------------------------------------------------------------------*/
#ifndef _MSGB
#define _MSGB
struct msgb
    {
    struct msgb    *b_next;    /* next msg on queue */
    struct msgb    *b_prev;    /* previous msg on queue */
    struct msgb    *b_cont;    /* next msg block of msg */
    unsigned char  *b_rptr;    /* first unread data byte in buffer */
    unsigned char  *b_wptr;    /* first unwritten data byte in buffer */
    struct datab   *b_datap;   /* data block */
    };
typedef struct msgb mblk_t;
#endif /* _MSGB */

/*----------------------------------------------------------------------*/
/* datab structure definition                                           */
/*----------------------------------------------------------------------*/
#ifndef _DATAB
#define _DATAB
struct datab
    {
    struct datab   *db_freep;  /* used internally */
    unsigned char  *db_base;   /* first byte of buffer */
    unsigned char  *db_lim;    /* last byte+1 of buffer */
    unsigned char  db_ref;     /* count of msgs pointing to this block */
    unsigned char  db_type;    /* msg type */
    unsigned char  db_class;   /* used internally */
    unsigned char  db_debug;   /* debug */
    frtn_t         db_frtn;
    };
typedef struct datab dblk_t;
#endif /* _DATAB */

/*----------------------------------------------------------------------*/
/* STREAMS utilities declarations                                       */
/*----------------------------------------------------------------------*/
#define datamsg(type) (type == M_DATA || type == M_PROTO \
 || type == M_PCPROTO)
#define b_size(bp)     ((bp)->b_datap->db_lim - (bp)->b_datap->db_base)
#define b_len(bp)      ((bp)->b_wptr - (bp)->b_rptr)
#define b_off(bp)      ((bp)->b_rptr - (bp)->b_datap->db_base)
#define mtod(bp, t) ((t) (bp)->b_rptr)

/***********************************************************************/
/* Network Interface (NI) related constants and structures.            */
/***********************************************************************/
/*---------------------------------------------------------------------*/
/* Function number for NI services                                     */
/*---------------------------------------------------------------------*/
#define NI_INIT        0x01         /* NI init call */
#define NI_GETPKB      0x02         /* NI get buffer call */
#define NI_RETPKB      0x03         /* NI return buffer call */
#define NI_SEND        0x04         /* NI send packet call */
#define NI_BROADCAST   0x05         /* NI broadcast call */
#define NI_POLL        0x06         /* NI poll call */
#define NI_IOCTL       0x07         /* NI ioctl call */

/*---------------------------------------------------------------------*/
/* Structure of pna functions passed to NI during ni_init              */
/*---------------------------------------------------------------------*/
struct ni_funcs
    {
    mblk_t *(*allocb)(long, long); /* Allocate pNA buffer */
    void   (*freeb)(mblk_t *);     /* Free Message block */
    void   (*freemsg)(mblk_t *);   /* Free message */
    mblk_t *(*esballoc)(UCHAR *, int, int, frtn_t *);
                                   /* Attach message block */
    void   (*intf_cb)(int, char*, int, long);    
                                /* pNA callback for interface operations */
    };

/*---------------------------------------------------------------------*/
/* NI paramter block structure. A pointer to this structure is passed  */
/* to the NI on each NI service call.                                  */
/*---------------------------------------------------------------------*/
union nientry
    {
    struct niinit
        {                           /* NI_INIT */
        long (*ap_addr)(ULONG, char *, ULONG, ULONG, char *, char *);
                                    /* pNA entry to receive packet */
        long if_num;                /* NI interface number */
        long ip_addr;               /* NI interface IP address */
        struct ni_funcs *funcs;     /* PNA functions (memory)  */
        } niinit;

    struct nigetpkb
        {                           /* NI_GETPBK */
        long count;                 /* size of the buffer */
        char *hwa_ptr;              /* Ptr to dest hardware address */
        long if_num;                /* NI interface number */
        } nigetpkb;

    struct niretpkb
        {                           /* NI_RETPBK */
        char *buff_addr;            /* Address of the buffer */
        long if_num;                /* NI interface number */
        } niretpkb;

    struct nisend
        {                           /* NI_SEND */
        char *hwa_ptr;              /* Ptr to dest hardware address */
        char *buff_addr;            /* Address of the packet buffer */
        long count;                 /* Size of the packet */
        long type;                  /* Type of the packet (IP/ARP) */
        long if_num;                /* NI interface number */
        } nisend;

    struct nibrdcast
        {                           /* NI_BRDCAST */
        char *buff_addr;            /* Address of the packet buffer */
        long count;                 /* Size of the packet */
        long type;                  /* Type of the packet (ARP/IP) */
        long if_num;                /* NI interface number */
        } nibrdcast;

    struct nipoll
        {
        long if_num;                /* NI interface number */
        } nipoll;

    struct niioctl
        {
        long cmd;                   /* ioctl command */
        long *arg;                  /* Pointer to ioctl argument */
        long if_num;
        } niioctl;
    };

/*---------------------------------------------------------------------*/
/* NI map multicast structure. A pointer to this structure is passed   */
/* to the NI to map a protocol specific multicast address to a hardware*/
/* specific multicast address. E.g .to map an IP multicast address to  */
/* ethernet multicast.                                                 */
/*---------------------------------------------------------------------*/
struct ni_map_mcast
    {
    int type;                   /* Protocol Type */
    char  prtladdr[14];         /* Protocol Address */
    char  hdwraddr[14];         /* Hardware address */
    };

/***********************************************************************/
/* pNA+ Fatal Error Codes                                              */
/***********************************************************************/
#define FAT_INSUFFMEM   0x5F01    /* Insufficient memory allocated by */
                                  /* NC_DATASIZE or REGION 0 too small */
#define FAT_NRT         0x5F02    /* The number of initial routing table */
                                  /* entries specified exceeds NC_NROUTE */
#define FAT_NNI         0x5F03    /* The number of initial NI table */
                                  /* entries specified exceeds NC_NNI */
#define FAT_NIHSIZE     0x5F04    /* Invalid NI address */
#define FAT_NIMTU       0x5F05    /* Invalid MTU for NI */
#define FAT_PNAMEM      0x5F06    /* pNA+ memory error */
#define FAT_PNATASK     0x5F07    /* PNAD task creation error */
#define FAT_PNAINIT     0x5F08    /* pNA+ initialization error */
#define FAT_NIINIT      0x5F09    /* NI initialization error */
#define FAT_RTINIT      0x5F0A    /* Routing table initialization error */
#define FAT_ARPINIT     0x5F0B    /* ARP table initialization error */
#define FAT_TIMERINIT   0x5F0C    /* PNAD timer initialization error */
#define FAT_EVENT       0x5F0D    /* PNAD event error */
#ifndef FAT_CHKSUM  /* To avoid collision with psos.h */
#define FAT_CHKSUM      0x5F0E    /* pNA+ Checksum error */
#endif
#define FAT_INTERNAL    0x5F0F    /* Internal error occurred in pNA+ */
#define FAT_NHT         0x5F10    /* The number of initial host table */
                                  /* entries specified exceeds NC_NHENTRY */
#define FAT_FUNC        0x5F11    /* Invalid pNA+/Subcomponent func call */
 
/***********************************************************************/
/* pNA+ Error Codes returned via errno                                 */
/***********************************************************************/
#define EINTR           0x5004    /* Interrupted system call */
#define EIO             0x5005    /* I/O error */
#define ENXIO           0x5006    /* No such address */
#define EBADS           0x5009    /* The socket descriptor is invalid */
#define ENOMEM          0x500C    /* Not enough memory */
#define E_ACCESS        0x500D    /* Permission denied */
#define EEXIST          0x5011    /* Entry exists */
#define EINVALID        0x5016    /* An argument is invalid */
#define ENFILE          0x5017    /* An internal table has run out of */
                                  /* space */
#define EPIPE           0x5020    /* The connection is broken */
#define EWOULDBLOCK     0x5023    /* This operation would block and */
                                  /* the socket is non-blocking */
#define EINPROGRESS     0x5024    /* The socket is non-blocking and the */
                                  /* connection cannot be completed */
                                  /* immediately */
#define EALREADY        0x5025    /* The socket is non-blocking and a */
                                  /* previous connection attempt has */
                                  /* not yet completed */
#define ENOTSOCK        0x5026    /* Socket operation on a non-socket */
#define EDESTADDRREQ    0x5027    /* The destination address is invalid */
#define EMSGSIZE        0x5028    /* Message too long */
#define EPROTOTYPE      0x5029    /* Protocol wrong type for socket */
#define ENOPROTOOPT     0x502A    /* Protocol option not available */
#define EPROTONOSUPPORT 0x502B    /* Protocol not supported */
#define ESOCKTNOSUPPORT 0x502C    /* Socket type not supported */
#define EOPNOTSUPP      0x502D    /* Operation not supported on socket */
#define EPFNOSUPPORT    0x502E    /* Protocol family not supported */
#define EAFNOSUPPORT    0x502F    /* Address family not supported */
#define EADDRINUSE      0x5030    /* Address is already in use */
#define EADDRNOTAVAIL   0x5031    /* Address not available */
#define ENETDOWN        0x5032    /* Network is down */
#define ENETUNREACH     0x5033    /* Network is unreachable */
#define ENETRESET       0x5034    /* Network dropped connection on reset */
#define ECONNABORTED    0x5035    /* The connection has been aborted */
                                  /* by the peer */
#define ECONNRESET      0x5036    /* The connection has been reset */
                                  /* by the peer */
#define ENOBUFS         0x5037    /* An internal buffer is required, */
                                  /* but cannot be allocated */
#define EISCONN         0x5038    /* The socket is already connected */
#define ENOTCONN        0x5039    /* The socket is not connected */
#define ESHUTDOWN       0x503A    /* Can't send after socket shutdown */
#define ETOOMANYREFS    0x503B    /* Too many references: can't splice */
#define ETIMEDOUT       0x503C    /* Connection timed out */
#define ECONNREFUSED    0x503D    /* The attempt to connect was refused */
#define EHOSTDOWN       0x5040    /* Host is down */
#define EHOSTUNREACH    0x5041    /* The destination host could not be */
                                  /* reached from this node */
#define ENOTEMPTY       0x5042    /* Directory not empty */
#define ENIDOWN         0x5046    /* NI_INIT returned -1 */
#define ENMTU           0x5047    /* The MTU is invalid */
#define ENHWL           0x5048    /* The hardware length is invalid */
#define ENNOFIND        0x5049    /* The route specified cannot be found */
#define ECOLL           0x504A    /* Collision in select call; these */
                                  /* conditions have already been */
                                  /* selected by another task */
#define ETID            0x504B    /* The task id is invalid */


/***********************************************************************/
/* pNA+ System Calls (defined in pna.s)                                */
/***********************************************************************/
long accept(int s, struct sockaddr_in *addr, int *addrlen);
long add_ni(struct ni_init *ni);
long bind(int s, struct sockaddr_in *addr, int addrlen);
long close(int s);
long connect(int s, struct sockaddr_in *addr, int addrlen);
long get_id(long *userid, long *groupid, long *groups);
long getpeername(int s, struct sockaddr_in *addr, int *addrlen);
long getsockname(int s, struct sockaddr_in *addr, int *addrlen);
long getsockopt(int s, int level, int optname, char *optval, int *optlen);
 
long ioctl(int s, int cmd, char *arg);
long listen(int s, int backlog);
 
mblk_t *pna_allocb(int size, int pri);
mblk_t *pna_esballoc(unsigned char *base, int size, int pri,
              frtn_t *frtn);
void pna_freeb(mblk_t *bp);
void pna_freemsg(mblk_t *mp);
 
long recv(int s, char *buf, int len, int flags);
long recvfrom(int s, char *buf, int len, int flags,
              struct sockaddr_in *from, int *fromlen);
long recvmsg(int s, struct msghdr *msg, int flags);
 
long select(int width, struct fd_set *readset, struct fd_set *writeset,
            struct fd_set *exceptset, struct timeval *timeout);
long send(int s, char *buf, int len, int flags);
long sendmsg(int s, struct msghdr *msg, int flags);
long sendto(int s, char *buf, int len, int flags,
            struct sockaddr_in *to, int tolen);
 
long set_id(long userid, long groupid, long *groups);
long setsockopt(int s, int level, int optname, char *optval, int optlen);
int shr_socket(int s, unsigned long tid);
long shutdown(int s, int how);
int socket(int domain, int type, int protocol);
 
#endif  /* _PNA_H */

void InstallNi( int (*)(), int, int, int, int, int, int );

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

