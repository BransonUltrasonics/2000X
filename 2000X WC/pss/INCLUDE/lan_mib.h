/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\lan_mib.h_v   1.0   Mar 29 1999 13:50:58   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: bsps/template/src/lan_mib.h 2.2 96/12/12 15:45:00 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  bsps/template/src/lan_mib.h                              */
/*   DATE:    96/12/12                                                 */
/*   PURPOSE: Contains common typedef's used by lan_mib.c and lan.c    */
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
#ifndef _LAN_MIB_H
#define _LAN_MIB_H
 
/*---------------------------------------------------------------------*/
/* Common structure type for drivers collection of MIB stats and info  */
/*---------------------------------------------------------------------*/
typedef struct
    {
    /*-----------------------------------------------------------------*/
    /* ifDescr: is a pointer to interface description which should be  */
    /* a text string containing information about the interface. This  */
    /* string should include the name of the manufacture, the product  */
    /* name and the version of the hardware interface.                 */
    /* Example: "Motorola 167 82596CA LANC"                            */
    /*-----------------------------------------------------------------*/
    char   *ifDescr;

    unsigned long starttime;    /* time of last reset */

    /*-----------------------------------------------------------------*/
    /* inoctets: total octets received on the interface including      */
    /* framing characters.                                             */
    /*-----------------------------------------------------------------*/
    long   inoctets;

    /*-----------------------------------------------------------------*/
    /* inucastpkts: The numberr  of subnetwork broadcast packets       */
    /* delivered to a higher level protocol.                           */
    /*-----------------------------------------------------------------*/
    long   inucastpkts;

    /*-----------------------------------------------------------------*/
    /* innucastpkts: The numberr  of non_unicast (i.e., subnetwork     */
    /* broadcast or subnetwork-multicast) packets delivered to a       */
    /* higher level protocol.                                          */
    /*-----------------------------------------------------------------*/
    long   innucastpkts;

    /*-----------------------------------------------------------------*/
    /* indiscards: The number of inbound packets which were chosen to  */
    /* be discarded even though no errors had been detected to prevent */
    /* their being deliverable to a higher-layer protocol.  A possible */
    /* reason for discarding such a packet could be to free up buffer  */
    /* space.                                                          */
    /*-----------------------------------------------------------------*/
    long   indiscards;

    /*-----------------------------------------------------------------*/
    /* inerrors: The number of inbound packets containing errors that  */
    /* prevented them from being deliverable to a higher-layer protocol*/
    /*-----------------------------------------------------------------*/
    long   inerrors;

    /*-----------------------------------------------------------------*/
    /* inunknownprotos: The number of packets received which were      */
    /* discarded because of an unknown or unsupported protocol.        */
    /*-----------------------------------------------------------------*/
    long   inunknownprotos;

    /*-----------------------------------------------------------------*/
    /* outoctets: The total numbeer of octets transmitted out of the   */
    /* interface , including framing characters.                       */
    /*-----------------------------------------------------------------*/
    long   outoctets;

    /*-----------------------------------------------------------------*/
    /* outucastpkts: The total number of packets that a higher-level   */
    /* protocol requested be transmitted to a subnetwork-unicast       */
    /* address including those that were discarded or not sent.        */
    /*-----------------------------------------------------------------*/
    long   outucastpkts;

    /*-----------------------------------------------------------------*/
    /* outnucastpkts: The total number of packets that higher-level    */
    /* protocols request be transmitted to a non-unicast (i.e., a      */
    /* subnetwork broadcast os subnetwork-multicast) address           */
    /* including those that were discarded or not sent.                */
    /*-----------------------------------------------------------------*/
    long   outnucastpkts;

    /*-----------------------------------------------------------------*/
    /* outdiscards: The number of outbound packets which were chosen   */
    /* to be discarded even though no errors had been detected to      */
    /* prevent their being travsmitted. One possible reason for        */
    /* discarding such a packet could be to free up buffer space.      */
    /*-----------------------------------------------------------------*/
    long   outdiscards;

    /*-----------------------------------------------------------------*/
    /* outerrors: The number of output packets that could not be       */
    /* transmitted because of errors.                                  */
    /*-----------------------------------------------------------------*/
    long   outerrors;

    } mib_stat;

#endif  /* _LAN_MIB_H */

#if __cplusplus
}
#endif

