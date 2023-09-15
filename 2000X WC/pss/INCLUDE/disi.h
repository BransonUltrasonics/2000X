/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\disi.h_v   1.0   Mar 29 1999 13:50:54   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/disi.h 2.17 97/10/07 13:05:38 */
/***********************************************************************/
/*                                                                     */
/*   MODULE: disi.h Device Independent Serial Interface include file   */
/*   DATE:    97/10/07                                                 */
/*   PURPOSE: This include file defines prototypes and templates used  */
/*            in the DISI.                                             */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*        Copyright 1994 - 1996, Integrated Systems, Inc.              */
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

#ifndef _DISI_H
#define _DISI_H 1

#include <gsblk.h>
#include <pna.h>

typedef void        *Lid;
typedef void        *Uid;

/*---------------------------------------------------------------------*/
/* Data Structures                                                     */
/* Following are templates of data structures used in the following    */
/* sections.                                                           */
/*---------------------------------------------------------------------*/

typedef struct {
    unsigned char   LChar;
    unsigned char   LFlags;
} LineD;

/*---------------------------------------------------------------------*/
/* The Mode will decide which structure to use: HdlcCfg should be used */
/* for SIOCSYNC mode and UartCfg for non SIOCSYNC mode                 */
/*---------------------------------------------------------------------*/
struct HdlcCfg{
    unsigned char   TxClock;            /* Type of TxC (int/ext/dpll)*/
    unsigned char   RxClock;            /* Type of RxC (int/ext/dpll)*/
    unsigned short  MaxFrameSize;       /* largest frame to Rx */
    unsigned char   Modulation;         /* NRZ/NRZI/FM0/FM1/Manchester.*/
    unsigned char   Flags;              /* Number of interframe flags */
    unsigned short  Crc32Bits;          /* TRUE for 32 bits CRC */
    unsigned short  Address[4];         /* Addresses to recognize*/
    unsigned short  AddressMask;        /* Address Mask */
    unsigned short  padding1;           /* Padded due to Alignment problem */
    unsigned long   FrameCheckErrs;     /* frame check errors */
    unsigned long   TramsmitUnderrunErrs; /* transmit underrun errors */
    unsigned long   ReceiveOverrunErrs; /* receive overruns errors */
    unsigned long   InterruptedFrames;  /* frames that were stopped */
    unsigned long   AbortedFrames;      /* frames that were aborted */
    unsigned long   Reserve[4];         /* Reserved field */
};

struct UartCfg{
    unsigned long   CharSize;           /* # of bits in the character */
    unsigned long   Flags;              /* Various settings */
    LineD           LineD[3];           /* line delimiters */
    unsigned char   XOnCharacter;       /* XON Character (SW Flow) */
    unsigned char   XOffCharacter;      /* XOFF Character (SW Flow) */
    unsigned short  MinChar;            /* Min characters to receive */
    unsigned short  MaxTime;            /* Max time between characters */
    unsigned short  padding1;           /* Padded due to Alignment problem */
    unsigned long   ParityErrs;         /* number of parity errors */
    unsigned long   FramingErrs;        /* number of framing errors */
    unsigned long   OverrunErrs;        /* number of overrun errors */
    unsigned long   AutoBaudEnb;        /* is auto baud enabled */
    unsigned long   Reserve[4];         /* Reserved field */
};

typedef union {
    struct HdlcCfg Hdlc;
    struct UartCfg Uart;
} ModeCfg;

typedef struct {
    unsigned long   Mode;               /* Channel configuration */
    ModeCfg         Cfg;                /* mode dependent configuration*/
    unsigned long   NRBuffs;            /* Number of receiver buffers */
    unsigned long   RBuffSize;          /* Size of receive buffers */
    unsigned long   OutQLen;            /* Max # of outstanding bufs */
    unsigned long   Baud;               /* Baud Rate */
    unsigned long   LineMode;           /* line mode */
    void (*dataind)(Uid, mblk_t *,      /* Data Indication routine */
          unsigned long);
    void (*expind)(Uid,                 /* Exception indication routine*/
          unsigned long);
    void (*datacnf)(Uid, mblk_t *,      /* data confirmation routine */
          unsigned long);
    void (*ctlcnf)(Uid,                 /* control confirmation routine*/
          unsigned long);
    mblk_t *(*allocb)(int, int);        /* allocate msg block routine */
    void(*freemsg)(mblk_t *);           /* free message list routine */
    mblk_t *(*esballoc)(unsigned char *,/* attach msg block routine */
             int, int, frtn_t *);
    Uid             uid;                /* Upper level ID */
    unsigned long   Reserve[4];         /* Reserved fields */
} ChannelCfg;

/*---------------------------------------------------------------------*/
/* Typedefs for multiplexed serial driver functions.                   */
/*---------------------------------------------------------------------*/
typedef struct
    {
    void (*Init)(void);
    long (*Open)(ULONG, ChannelCfg *, Lid *, ULONG *);
    long (*Send)(Lid, mblk_t *);
    long (*Ioctl)(Lid, ULONG, void *);
    long (*Close)(Lid);
    } SERIAL_FUNCS;

typedef struct
    {
    ULONG dnum;  /* driver number */
    ULONG pnum;  /* physical port number */
    Lid   lid;
    } SDRVCNFG;

/*---------------------------------------------------------------------*/
/* SerialInit                                                          */
/*---------------------------------------------------------------------*/
void SerialInit(void);

/*---------------------------------------------------------------------*/
/* SerialOpen                                                          */
/*---------------------------------------------------------------------*/
long SerialOpen(
    unsigned long   channel,        /* Channel to be initialized */
    ChannelCfg      *cfg,           /* Configuration table */
    Lid           *lid,         /* Lower layer reference pointer */
    unsigned long   *hdwflags       /* Various hardware flags        */
                                    /* supported by the chip */
);

/*---------------------------------------------------------------------*/
/* This call is used to open a channel for a particular mode of        */
/* operation. The parameter channel indicates the serial channel to be */
/* opened. cfg points to the configuration table that defines various  */
/* configurable parameters like baud rate and various line parameters. */
/* See the Data Structures section for more details on the             */
/* configuration table. uid is a pointer to a user defined structure */
/* The lower level will pass the uid pointer when making call-outs   */
/* that concern this channel. lid is returned by the DISI. lid is  */
/* the lower level's reference structure for this channel. All future  */
/* calls such as SerialSend, to the DISI by the upper layer will pass  */
/* lid. hdwflags is returned by the DISI to indicate the capability  */
/* of the serial chip set.                                             */
/*                                                                     */
/* hdwflags can be:                                                    */
/*---------------------------------------------------------------------*/
#define SIOCHDWHDLC         0x00000001  /* HDLC supported */
#define SIOCHDWRXPOOL       0x00000002  /* has receive buffer pool */

/*---------------------------------------------------------------------*/
/* If SIOCHDWRXPOOL is set then the lower level contains a buffer pool */
/* to receive characters into and as buffers are sent up through the   */
/* DISI these buffers will need to be replenished. See the SerialIoctl */
/* command SIOCREPLENISH and UDataInd call for more information.       */
/*                                                                     */

/*---------------------------------------------------------------------*/
/* SerialSend                                                          */
/*---------------------------------------------------------------------*/
long SerialSend(
    Lid lid,                        /* Lower layer reference */
    mblk_t* mbp                         /* Message block pointer */
);

/*---------------------------------------------------------------------*/
/* SerialSend is used by the upper level serial driver to transfer     */
/* data through the DISI. lid is the lower level reference pointer   */
/* that was acquired during SerialOpen operation for the channel this  */
/* send is directed to. mbp is a pointer to the message block that     */
/* contains the data to be transmitted on the serial interface.        */
/*                                                                     */
/*---------------------------------------------------------------------*/
/* SerialIoctl                                                         */
/*---------------------------------------------------------------------*/

long SerialIoctl(
    Lid lid,                        /* Lower layer reference */
    unsigned long cmd,                  /* Ioctl command */
    void *arg                           /* Argument pointer */
);

/*---------------------------------------------------------------------*/
/* This call is used for specify various control operations which      */
/* modify the behavior of the DISI. Not all operations need be         */
/* supported by the Lower Layer chip set code. Any non supported       */
/* operation will return with the error code SIOCOPERATIONNOTSUP.      */
/* lid is the lower level reference pointer that was acquired during */
/* SerialOpen operation for the channel that this ioctl command is     */
/* intended for. cmd specifies the type of control operation. arg      */
/* contains information which is specific to the operation.            */
/*                                                                     */

/*---------------------------------------------------------------------*/
/* The SerialIoctl commands are:                                       */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* SIOCPOLL This calls is used to poll the serial device for           */
/* asynchronous events like data indication and exception indication.  */
/* It provides an ability to perform call-back functions without       */
/* interrupts or when interrupts are disabled. For example when pROBE  */
/* is in control, the processor operates with interrupts turned off.   */
/* This command will check for data received and exceptions and        */
/* trigger the call-back function for this condition as needed.        */
/*---------------------------------------------------------------------*/
#define SIOCPOLL            0x00000001

/*---------------------------------------------------------------------*/
/* SIOCGETA is used to get the channel's configuration. arg is a       */
/* pointer to a ChannelCfg structure. The current parameters are       */
/* copied to that structure. No callback is made.                      */
/*---------------------------------------------------------------------*/
#define SIOCGETA            0x00000002

/*---------------------------------------------------------------------*/
/* SIOCPUTA is used to change the channel's configuration. arg is a    */
/* pointer to a ChannelCfg structure. The current parameters are set   */
/* from the values stored in that structure. No callback is made.      */
/*---------------------------------------------------------------------*/
#define SIOCPUTA            0x00000003

/*---------------------------------------------------------------------*/
/* SIOCBREAK A break character is sent out the channel. The argument   */
/* is ignored. No callback is made.                                    */
/*---------------------------------------------------------------------*/
#define SIOCBREAK           0x00000004

/*---------------------------------------------------------------------*/
/* SIOCMQRY is use to determine the modem controls supported by the    */
/* channel. arg is a pointer to a long int. A mask representing the    */
/* modem control signals supported by the channel is written to arg. A */
/* set bit indicates that the particular control line is supported by  */
/* the channel. No callback is made. The modem control lines are       */
/* encoded as follows:                                                 */
/*---------------------------------------------------------------------*/
#define SIOCMQRY            0x00000005

#define SIOCMDTR            0x00000001    /* data terminal ready */
#define SIOCMRTS            0x00000002    /* request to send*/
#define SIOCMCTS            0x00000004    /* clear to send */
#define SIOCMDCD            0x00000008    /* data carrier detect*/
#define SIOCMRI             0x00000010    /* ring indicator*/
#define SIOCMDSR            0x00000020    /* data set ready */
#define SIOCMCLK            0x00000040    /* clock (indicates synch)*/

/*---------------------------------------------------------------------*/
/* NOTE: The interface is a DTE therefore DTR and RTS are outputs and  */
/* CTS, RI, DSR and DCD are inputs.                                    */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* SIOCMGET is used to get the settings of the modem controls. arg is  */
/* a pointer to a long int. The current state of the modem control     */
/* lines is fetched and stored at arg. SIOCMGET uses same encoding as  */
/* SIOCMQRY. Bits pertaining to control lines not supported by the     */
/* channel, and the SIOCMCLK bit, will be cleared. No callback is made.*/
/*---------------------------------------------------------------------*/
#define SIOCMGET            0x00000006

/*---------------------------------------------------------------------*/
/* SIOCMPUT is used to set the modem controls of the channel. arg is a */
/* pointer to a long int containing a new set of modem control lines.  */
/* The modem control lines are turned on or off, depending on whether  */
/* their respective bits are set or clear. SIOCMPUT uses same encoding */
/* as SIOCMQRY. Bits pertaining to control lines not supported by the  */
/* channel, and the bit, have no effect. No callback is made.          */
/*---------------------------------------------------------------------*/
#define SIOCMPUT            0x00000007

/*---------------------------------------------------------------------*/
/* SIOCFLGET Get the current state of the flags defined by the         */
/* UartCfg structure and in arg a pointer to a unsigned long. This     */
/* call will have no effect when the channel is being used in sync     */
/* (HDLC) mode.                                                        */
/*---------------------------------------------------------------------*/
#define SIOCFLGET           0x00000008

/*---------------------------------------------------------------------*/
/* SIOFLPUT arg is a pointer to a long int containing a new set of     */
/* flags (defined by the flag element in the uart_cfg structure). The  */
/* flags for the channel will be set to these new settings. This call  */
/* will have no effect when the channel is being used in sync (HDLC)   */
/* mode. The effect is immediate. No call back is made.                */
/*---------------------------------------------------------------------*/
#define SIOCFLPUT           0x00000009

/*---------------------------------------------------------------------*/
/* SIOCXFGET The current XOFF character is written to the long int     */
/* pointed to by arg. No callback is made.                             */
/*---------------------------------------------------------------------*/
#define SIOCXFGET           0x0000000A

/*---------------------------------------------------------------------*/
/* SIOCXFPUT arg is a pointer to a long int containing a new XOFF      */
/* character to be used. The effect is immediate. No callback is made. */
/*---------------------------------------------------------------------*/
#define SIOCXFPUT           0x0000000B

/*---------------------------------------------------------------------*/
/* SIOCXNGET The current XON character is written to the long int      */
/* pointed to by arg. No callback is made.                             */
/*---------------------------------------------------------------------*/
#define SIOCXNGET           0x0000000C

/*---------------------------------------------------------------------*/
/* SIOCXNPUT arg is a pointer to a long int containing a new XON       */
/* character to be used. The effect is immediate. No callback is made. */
/*---------------------------------------------------------------------*/
#define SIOCXNPUT           0x0000000D

/*---------------------------------------------------------------------*/
/* SIOCREPLENISH This command will cause the receive buffer pool       */
/* (if any) to be replenished. Note: this call need only be used if    */
/* the hdwflags passed in the SerialOpen call had the SIOCHDWRXPOOL    */
/* bit set.                                                            */
/*---------------------------------------------------------------------*/
#define SIOCREPLENISH       0x0000000E

/*---------------------------------------------------------------------*/
/* SIOCGBAUD The baud rate of the channel is written to the long int   */
/* pointed to by arg.                                                  */
/*---------------------------------------------------------------------*/
#define SIOCGBAUD           0x0000000F

/*---------------------------------------------------------------------*/
/* SIOCSBAUD arg is a pointer to a long int containing a new baud rate */
/* of the channel. The effect is immediate. No call back is made.      */
/* Baud is set to the actual desired baud rate. If that baud rate      */
/* cannot be supported by the lower level device dependent code then   */
/* an error will be returned and the open or Ioctl will fail.          */
/* Error code is SIOCBADBAUD.                                          */
/*---------------------------------------------------------------------*/
#define SIOCSBAUD           0x00000010

/*---------------------------------------------------------------------*/
/* SIOCGCSIZE The character size in bits is written to the long int    */
/* pointed to by arg.                                                  */
/*---------------------------------------------------------------------*/
#define SIOCGCSIZE          0x00000011

/*---------------------------------------------------------------------*/
/* SIOCSCSIZE arg is a pointer to a long int containing a new          */
/* character size in bits. The effect is immediate. No call back is    */
/* made.                                                               */
/*---------------------------------------------------------------------*/
#define SIOCSCSIZE          0x00000012

/*---------------------------------------------------------------------*/
/* SIOCSACTIVATE Activate the channel. This used to enable data        */
/* transfer. A call-back is made when the channel becomes active       */
/* (begins to receive data).                                           */
/*---------------------------------------------------------------------*/
#define SIOCSACTIVATE       0x00000013

/*---------------------------------------------------------------------*/
/* SIOCSDEACTIVATE Deactivate the channel. Sets the signals to         */
/* deactivate it.                                                      */
/*---------------------------------------------------------------------*/
#define SIOCSDEACTIVATE     0x00000014

/*---------------------------------------------------------------------*/
/* SIOCTXFLUSH Flush all characters in the transmit and receive queues */
/* for the channel. A call-back will be made when all characters are   */
/* discarded.                                                          */
/*---------------------------------------------------------------------*/
#define SIOCTXFLUSH         0x00000015

/*---------------------------------------------------------------------*/
/* SIOCRXFLUSH Flush all characters from the receiver. A call back will*/
/* be made when the flush is complete.                                 */
/*---------------------------------------------------------------------*/
#define SIOCRXFLUSH         0x00000016

/*---------------------------------------------------------------------*/
/* SIOCRXSTOP This will be used when the Upper Level                   */
/* Serial Driver needs to stop the flow of characters received.        */
/*---------------------------------------------------------------------*/
#define SIOCRXSTOP          0x00000017

/*---------------------------------------------------------------------*/
/* SIOCRXSTART This will be used when the Upper Level Serial           */
/* Driver wants to continue to receive characters.                     */
/*---------------------------------------------------------------------*/
#define SIOCRXSTART         0x00000018

/*---------------------------------------------------------------------*/
/* SIOCNUMBER Used to get the number of channels the driver controls.  */
/*---------------------------------------------------------------------*/
#define SIOCNUMBER          0x00000019

/*---------------------------------------------------------------------*/
/* SIOCBREAKCHK Used to check for break received                       */
/*---------------------------------------------------------------------*/
#define SIOCBREAKCHK        0x0000001A

/*---------------------------------------------------------------------*/
/* SIOCPROBEENTRY Used to inform the low level driver that pROBE+      */
/* is now has control of the channel untill a SIOCPROBEEXIT is gotten  */
/*---------------------------------------------------------------------*/
#define SIOCPROBEENTRY      0x0000001B

/*---------------------------------------------------------------------*/
/* SIOCPROBEEXIT Used to inform the low level driver that pROBE+       */
/* no longer wants control of the channel                              */
/*---------------------------------------------------------------------*/
#define SIOCPROBEEXIT       0x0000001C

/*---------------------------------------------------------------------*/
/* SIOCCLOSENOFREE Used to close a DISI channel without dereferencing  */
/* private data in any pending mblk_t's.  This is needed because there */
/* are separate buffer pools used for X.25 (and streams) I/O.          */
/*---------------------------------------------------------------------*/
#define SIOCCLOSENOFREE     0x0000001D

/*---------------------------------------------------------------------*/
/* SerialClose                                                         */
/*---------------------------------------------------------------------*/
long SerialClose(
    Lid lid                         /* Lower layer reference */
);

/*---------------------------------------------------------------------*/
/* This call is used to terminate a connection on a serial channel.    */
/* The SerialClose call will return the channel to its default state.  */
/* lid is the lower level reference pointer that was acquired during */
/* SerialOpen operation for the channel that is to be closed.          */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* User Call-back functions                                            */
/*                                                                     */
/* Following are the prototypes of the call-back functions that should */
/* be provided by the user of the driver. Pointers to these functions  */
/* are passed in the ChannelCfg structure during the SerialOpen of the */
/* channel to the device dependent lower level code. Note: these calls */
/* must be callable from an interrupt so it is important that they do  */
/* not block within the call. The prototypes for these calls are       */
/* supplied here a comments because the user may name these calls as   */
/* what ever they would like. (address to the functions are passed in  */
/* the SerialOpen call.                                                */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/*                                                                     */
/* static void UDataInd(                                               */
/*     Uid uid;                    Upper layer reference           */
/*     mblk_t * mbp;                   Message block pointer           */
/*     unsigned long b_flags;          status pertaining to this block */
/* );                                                                  */
/*                                                                     */
/* UDataInd is called during an interrupt by the device dependent      */
/* lower level code to indicate reception of data to the upper level   */
/* serial driver. uid is the upper level serial driver's reference   */
/* pointer passed to the serial driver during the SerialOpen of the    */
/* channel the data is being received on. mbp is pointer to message    */
/* block that will contain the data received by the channel. b_flags   */
/* are the status flags associated with this message block.            */
/*                                                                     */
/* UDataInd should unblock any function that is waiting for data from  */
/* this channel. If the SerialOpen call argument hdwflags had the      */
/* SIOCHDWRXPOOL bit set then the lower level code has a receive buffer*/
/* pool. This pool will need replenishing through the use of a call to */
/* SerialIoctl with the command SIOCREPLENISH. It is the               */
/* responsibility of the user supplied functions in the upper layer    */
/* serial driver code to make the SerialIoctl to do this.              */
/*                                                                     */
/* It is also the responsibility of the upper level serial driver to   */
/* free the message block (pointed to by mbp) when it is emptied.      */
/*                                                                     */
/* b_flags can be one of the following:                                */
/*---------------------------------------------------------------------*/
#define SIOCOK       0x00000000      /* Rx received with out error */
#define SIOCLGFRAME  0x00000001      /* Frame with exceeding length */
#define SIOCCONTROL  0x00000002      /* Control Character Received */
#define SIOCMARK     0x00000004      /* Idle Line Condition */
#define SIOCBREAKR   0x00000008      /* Break Received */
#define SIOCFRAMING  0x00000010      /* Framing Error */
#define SIOCPARITY   0x00000020      /* Parity Error */
#define SIOCOVERRUN  0x00000040      /* Overrun of buffers */
#define SIOCCDLOST   0x00000080      /* Carrier Detect Lost */
#define SIOCDSRLOST  0x00020000      /* Data Set Ready Lost */

/*---------------------------------------------------------------------*/
/*                                                                     */
/* static void UExpInd(                                                */
/*     Uid uid;                    Upper layer reference           */
/*     unsigned long exp;              Exception type                  */
/*     char *arg;                      Argument pointer                */
/* );                                                                  */
/*                                                                     */
/* UExpInd is called by the device dependent lower level code to       */
/* indicate an exception condition to the upper level serial driver.   */
/* uid is upper level serial driver's reference pointer passed to    */
/* the driver during the SerialOpen of the channel. exp is type of     */
/* exception and arg points to information that can be passed for      */
/* exception condition.                                                */
/*                                                                     */
/* Exceptions can be one of the following:                             */
/* SIOCBREAK   Break Received                                          */
/* SIOCFRAMING Framing Error no stop bit                               */
/* SIOCPARITY  Parity Error                                            */
/* SIOCOVERRUN Overrun of buffers                                      */
/* SIOCCDLOST  Carrier Detect Lost                                     */
/* SIOCMARK    Idle Line Condition                                     */
/*                                                                     */
/* And additional codes:                                               */
/*---------------------------------------------------------------------*/
#define SIOCCTSLOST    0x00000100   /* Clear To Send has been lost */
#define SIOCNAFRAME    0x00000200   /* Frame not divisible by 8 */
#define SIOCABFRAME    0x00000400   /* Frame aborted */
#define SIOCCRCERR     0x00000800   /* CRC error */
#define SIOCCTS        0x00001000   /* Clear To Send has been found */
#define SIOCCD         0x00002000   /* Carrier Detect has been detected*/
#define SIOCFLAGS      0x00004000   /* Non Idle Line Condition detected*/
#define SIOCDSR        0x00040000   /* Data Set Ready Detected */

/*---------------------------------------------------------------------*/
/*                                                                     */
/* static void UDataCnf(                                               */
/*    Uid uid;                    Upper layer reference            */
/*    mblk_t * mbp;                   Message block pointer            */
/*    unsigned long b_flags;)         Bitwise info associated to buf   */
/* );                                                                  */
/*                                                                     */
/* UDataCnf is called by the device dependent lower level code to      */
/* confirm to the upper level serial driver that the data sent using   */
/* SerialSend call has been transmitted. uid is upper level serial   */
/* driver's reference pointer passed to the driver during the          */
/* SerialOpen of the channel, mbp points to the message block sent     */
/* using SerialSend call. b_flags are the status flags associated with */
/* this message block. This function should unblock any function that  */
/* was waiting for data to be sent and that function should do what    */
/* ever maintenance is necessary on the message block (free it or      */
/* reuse it).                                                          */
/* SIOCCTSLOST Clear To Send has been lost                             */
/*                                                                     */
/* b_flags can be one of the following:                                */
/*---------------------------------------------------------------------*/
#define SIOCUNDERRUN 0x00008000      /* Tx underrun */
#define SIOCABORT    0x00010000      /* Tx aborted */

/*---------------------------------------------------------------------*/
/*                                                                     */
/* static void UCtlCnf(                                                */
/*     Uid uid;                    Upper layer reference           */
/*     unsigned long cmd;              Control command                 */
/* );                                                                  */
/*                                                                     */
/* UCtlCnf is used to confirm the completion of the control command    */
/* sent via SerialIoctl call. uid is upper level serial driver's     */
/* pointer reference passed to the driver during the SerialOpen of the */
/* channel. cmd refers to the command being confirmed.                 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/*                                                                     */
/* static mblk_t * UEsballoc(                                          */
/*    char *bp;                       Pointer to buffer                */
/*    long len;                       Length of the buffer             */
/*    long pri;                       Priority                         */
/*    frtn_t *frtn;                   Free routine structure           */
/* );                                                                  */
/*                                                                     */
/*                                                                     */
/*    typedef struct {                                                 */
/*        void (*free_func)();                                         */
/*        void *free_arg;                                              */
/*    } frtn_t;                                                        */
/*                                                                     */
/* UEsballoc returns a message block triplet by attaching the          */
/* externally supplied buffer to a message block and data block (See   */
/* Streams or pNA for more details). bp points to the externally       */
/* supplied buffer and len specifies the number of bytes in the buffer.*/
/* pri specifies the priority for message block allocation. frtn is a  */
/* pointer to the free structure of type frtn_t:                       */
/*                                                                     */
/* The function pointed to by free_func will be called when the        */
/* caller supplied buffer needs to be freed with the argument          */
/* pointed to by free_arg. (free_arg in most cases will be the pointer */
/* to the externally supplied buffer.) The function pointed to by      */
/* free_func must be supplied by the caller.                           */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/*                                                                     */
/* static mblk_t * UAllocb(                                            */
/*     long size;                      Size of the buffer              */
/*     long pri;                       Priority                        */
/* );                                                                  */
/*                                                                     */
/* UAllocb returns a message block triplet of size and at priority pri */
/* or a NULL if no buffer or message block could be found.             */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/*                                                                     */
/* static void UFreemsg(                                               */
/*     mblk_t *mbp;                    Pointer to message block        */
/* );                                                                  */
/*                                                                     */
/* UFreemsg call is used by the function pointed to by frnt to free a  */
/* message block triplet list specified by the parameter mbp for this  */
/* specific message block pool.                                        */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* The Mode can be:                                                    */
/*---------------------------------------------------------------------*/
#define SIOCASYNC    0x00000000     /* async mode */
#define SIOCSYNC     0x00000001     /* sync HDLC - asyn if not set */
#define SIOCPOLLED   0x00000002     /* poll - interrupt if not set */
#define SIOCLOOPBACK 0x00000004     /* local loop back */
#define SIOCPROBEMODE 0x00000008    /* pROBE+ mode  */
#define SIOCISDN     0x00000010     /* ISDN   mode  */

/*---------------------------------------------------------------------*/
/* The LineMode can be (MULTIDROP can be OR'ed with HALFD or FULLD):   */
/*---------------------------------------------------------------------*/
#define HALFD        0x01           /* Half-Duplex */
#define FULLD        0x02           /* Full-Duplex */
#define MULTIDROP    0x04           /* Multi-Drop lines*/

/*---------------------------------------------------------------------*/
/* The CharSize can be:                                                */
/*---------------------------------------------------------------------*/
#define SCS5         0x05            /* 5 bits per character */
#define SCS6         0x06            /* 6 bits per character */
#define SCS7         0x07            /* 7 bits per character */
#define SCS8         0x08            /* 8 bits per character */

/*---------------------------------------------------------------------*/
/* The Flags can be:                                                   */
/*---------------------------------------------------------------------*/
#define CANON      0x00000001       /* Canonical mode */
#define C2STOPB    0x00000002       /* Send two stop bits, else one.*/
#define SPARENB    0x00000004       /* Parity enable.*/
#define SPARODD    0x00000008       /* Odd parity, else even.*/
#define HWFC       0x00000010       /* Hardware flow control on.*/
#define SWFC       0x00000020       /* Software flow control on.*/
#define SWDCD      0x00000040       /* Software data carrier detect */
#define LECHO      0x00000080       /* Enable local echo */
#define SBRKINT    0x00000100       /* Interrupt on reception of Break*/
#define DCDINT     0x00000200       /* Interrupt on loss of DCD */

#define FLAGS_MASK 0x000003FF       /* Mask of valid flag bits */

/*---------------------------------------------------------------------*/
/* LChar can be any 8 bit value that the user wants to use as a        */
/* character that when received will cause an interrupt that will      */
/* cause the UDataInd function to be called                            */
/*                                                                     */
/* LFlags is a bit field that will control the characters use.as       */
/* ENDOFTABLE will mark an entry not valid and should be the last entry*/
/* in the table. If table has 2 entries none will have this bit set.   */
/* If REJECTCHAR is set the character does not become part of the      */
/* buffer, an interrupt will be generated but the buffer will not be   */
/* closed (characters will still be received) If REJECTCHAR is not set */
/* then an interrupt will be generated, the character will be the last */
/* character in the buffer and the buffer will be closed then another  */
/* buffer will be used to receive data                                 */
/*---------------------------------------------------------------------*/
#define ENDOFTABLE  0x80            /* non valid last entry in table */
#define REJECTCHAR  0x40            /* character is rejected */

/*---------------------------------------------------------------------*/
/* If PARENB is set, parity generation and detection is enabled and a  */
/* parity bit is added to each character. If parity is enabled, the    */
/* PARODD flag specifies odd parity if set, otherwise even parity is   */
/* used.                                                               */
/*                                                                     */
/* If HWFC is set, the channel will use CTS/RTS flow control. This bit */
/* has no effect if the channel does not support hardware flow control.*/
/*                                                                     */
/* If the SWFC bit is set, XON/XOFF flow control is enabled.           */
/*                                                                     */
/* If SWDCD is set, the channel behaves as if the hardware data        */
/* carrier detect (DCD) signal is always asserted. If SWDCD is clear,  */
/* the channel is enabled and disabled by DCD.                         */
/*                                                                     */
/* If BRKINT is set, the channel will make an exception callback if a  */
/* break character is received. If DCDINT is set, the channel will     */
/* make an exception callback upon loss of the DCD signal.             */
/*---------------------------------------------------------------------*/


/*---------------------------------------------------------------------*/
/* HDLC Address filtering:                                             */
/*  There must always be 4 values in the Address[4] field of the HDLC  */
/*  configuration structure because HDLC is transparent so no single   */
/*  character can serve as an end of list there.  The AddressMask      */
/*  field determines which of the possible 16 bits (of each Address[i])*/
/*  are used to filter the addresses of the received frames.  0 means  */
/*  no filtering, 0x00FF means 8 bits addresses, 0xFFFF means 16 bits  */
/*  addresses. Other masks are allowed to filter on fewer than 8 or 16 */
/*  bits: for example the mask 0x00F0 with Address[i] set to 0x00C0    */
/*  will cause the driver to receive only frames that have their first */
/*  byte starting with 0xC0 to 0xCF.                                   */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* TxClock and RxClock can be:                                         */
/*---------------------------------------------------------------------*/
#define CLK_INTERNAL    0x01         /* internal clock (transmit only) */
#define CLK_EXTERNAL    0x02         /* external supplied clock */
#define CLK_DPLL        0x04         /* Digital Phase Lock Loop used */
#define CLK_INVERT      0x08         /* transmit DPLL invert data */

/*---------------------------------------------------------------------*/
/* Modulation can be:                                                  */
/*---------------------------------------------------------------------*/
#define MOD_NRZ           0x01
#define MOD_NRZI_MARK     0x02
#define MOD_NRZI_SPACE    0x03
#define MOD_FM0           0x04
#define MOD_FM1           0x05
#define MOD_MANCHESTER    0x06
#define MOD_DMANCHESTER   0x07

/*---------------------------------------------------------------------*/
/* Crc32Bits can be:                                                   */
/*---------------------------------------------------------------------*/
#define CRC32    0x01    /* 32 bit CRC else 16 bit CRC */

/*---------------------------------------------------------------------*/
/* error codes returned:                                               */
/*---------------------------------------------------------------------*/
#define SIOCAOPEN           0x10010401  /* channel already open */
#define SIOCBADCHANNELNUM   0x10010402  /* channel does not exist. */
#define SIOCCFGNOTSUPPORTED 0x10010403  /* config not supported */
#define SIOCNOTOPEN         0x10010404  /* channel is not open */
#define SIOCINVALID         0x10010405  /* cmd is not valid */
#define SIOCBADARG          0x10010406  /* argument is not valid */
#define SIOCOPERATIONNOTSUP 0x10010407  /* operation is not supported */
#define SIOCOQFULL          0x10010408  /* output que is full failed */
#define SIOCBADBAUD         0x10010409  /* baud rate not supported */
#define SIOCBADMINCHAR      0x1001040A  /* MinChar > RBuffSize */
#define SIOCWAITING         0x1001040B  /* still waiting for previous */
                                        /* command to complete */
#define SIOCNOTINIT         0x1001040C  /* driver not initialized */
#define SIOCINITFAILED      0x1001040D

#endif

#if __cplusplus
}
#endif
