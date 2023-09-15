/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\diti.h_v   1.0   Mar 29 1999 13:50:56   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/diti.h 2.9 98/04/02 14:55:43 */
/***********************************************************************/
/*                                                                     */
/*   MODULE: diti.h                                                    */
/*   DATE:    98/04/02                                                 */
/*   PURPOSE: Device Independent Console Interface macros and defines  */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*        Copyright 1994 - 1998, Integrated Systems, Inc.              */
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
/* The Device Independent Terminal Interface Specification (DITI)      */
/* describes the interface between a task and the Console Driver       */
/* through the I/O switch table.The Console Driver will use the Device */
/* Independent Serial Interface (DISI) to complete the device          */
/* dependent part of the driver.                                       */
/*---------------------------------------------------------------------*/
#ifndef _DITI_H
#define _DITI_H 1

/*---------------------------------------------------------------------*/
/* Must include disi.h before this file                                */
/*---------------------------------------------------------------------*/
#ifndef _DISI_H
    #error "Must include disi.h before diti.h"
#endif

/*---------------------------------------------------------------------*/
/* Macro to retrieve desired number from major.minor - minor device 0  */
/* is an alias for the "System Console" (standard in/out/error) and    */
/* this macro maps it to the actual device number.  The variable       */
/* SysConsole contains the minor device number to map to.              */
/*---------------------------------------------------------------------*/
#define MINOR(dev_n)((dev_n & 0xFFFF) ? dev_n & 0xFFFF : SysConsole)

/*---------------------------------------------------------------------*/
/* Terminal Interface Error Codes                                      */
/*---------------------------------------------------------------------*/
#define TERM_HDWR     0x10010200     /* Hardware error */
#define TERM_MINOR    0x10010201     /* Invalid minor device */
#define TERM_BAUD     0x10010203     /* Invalid baud rate */
#define TERM_NINIT    0x10010204     /* driver not initialized */
#define TERM_DATA     0x10010205     /* Cannot allocate data area */
#define TERM_SEM      0x10010206     /* Semaphore error */
#define TERM_AINIT    0x10010210     /* Console already initialized */
#define TERM_CHARSIZE 0x10010211     /* bad character size */
#define TERM_BADFLAG  0x10010212     /* flag not defined */
#define TERM_NHWFC    0x10010213     /* Hardware flow not supported */
#define TERM_BRKINT   0x10010214     /* Terminated by a break character */
#define TERM_DCDINT   0x10010215     /* Terminated by loss of DCD */
#define TERM_NBUFF    0x10010216     /* No buffers to copy characters */
                                     /* (allocb failed) */
#define TERM_NOPEN    0x10010217     /* minor device not opened */
#define TERM_AOPEN    0x10010218     /* channel already opened */
#define TERM_ADOPEN   0x10010219     /* channel already opened by */
                                     /* another driver */
#define TERM_CFGHSUP  0x10010220     /* hardware does not support */
                                     /* channel as configured */
#define TERM_OUTSYNC  0x10010221     /* out of sync with DISI */
#define TERM_BADMIN   0x10010222     /* MinChar > RBuffSize */
#define TERM_LDERR    0x10010223     /* Lower driver error may be */
                                     /* corrupted structure */
#define TERM_QUE      0x10010224     /* que error */
#define TERM_RXERR    0x10010225     /* data receive error */
#define TERM_TIMEOUT  0x10010226     /* Timmer expired for read or */
                                     /* write */
#define TERM_ROPER    0x10010228     /* redirect operation error */
#define TERM_MARK     0x10010229     /* received a SIOCMARK */
#define TERM_FRAMING  0x10010230     /* framing error */
#define TERM_PARITY   0x10010231     /* parity error */
#define TERM_OVERRUN  0x10010232     /* overrun error */
#define TERM_NMBLK    0x10010233     /* no buffer headers */
                                     /* (esballoc failed) */
#define TERM_TXQFULL  0x10010234     /* transmit que is full (only if */
                                     /* WNWAIT set) */
#define TERM_WNWCONF  0x10010235     /* MaxWTime and WNWAIT both set */ 
#define TERM_BADCONSL 0x10010236     /* Bad default console number */ 
#define TERM_WABORT   0x10010237     /* Write was aborted */

/*---------------------------------------------------------------------*/
/* TermInit will initialize the Terminal driver and the lower level    */
/* DISI.                                                               */
/* NOTE: TermInit will be called during system initialization. It      */
/* MUST NOT be included in the I/O switch table.                       */
/*---------------------------------------------------------------------*/
void TermInit (struct ioparms *parms);

/*---------------------------------------------------------------------*/
/* TermOpen will open a specific serial channel for use. The channel   */
/* number that is to be opened will be the minor device number.        */
/*---------------------------------------------------------------------*/
void TermOpen(struct ioparms *parms);

/*---------------------------------------------------------------------*/
/* TermOpen will do a range check on the channel number and create the */
/* necessary semaphores needed to block on reads and writes.           */
/*                                                                     */
/* TermOpen will return in parms->err zero on success or one of the    */
/* following error codes:                                              */
/*                                                                     */
/* TERM_NINIT    driver not initialized                                */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* TermRead will read from the minor device.                           */
/*---------------------------------------------------------------------*/
void TermRead (struct ioparms *parms);

/*---------------------------------------------------------------------*/
/* The in_iopb element of the ioparms structure will point to a TermIO */
/* structure:                                                          */
/*---------------------------------------------------------------------*/
typedef struct {
    unsigned long length;            /* length of read/write */
    unsigned char *buffp;            /* pointer to data buffer */
}TermIO;

/*---------------------------------------------------------------------*/
/* TermRead will fill the buffer pointed to by buffp according to the  */
/* configuration set up by the call to TermOpen or configuration       */
/* changed by TermIoctl. The read will return up to the length         */
/* requested.                                                          */
/*                                                                     */
/* TermRead will return in parms->err zero on success or one of the    */
/* following error codes:                                              */
/*                                                                     */
/* TERM_NOPEN     minor device has not been opened                     */
/* TERM_NINIT     driver not initialized                               */
/* TERM_MINOR     Invalid minor device                                 */
/* TERM_BRKINT    Terminated by a break character                      */
/* TERM_DCDINT    Terminated by loss of DCD                            */
/* TERM_RXERR     data receive error                                   */
/* TERM_TIMEOUT   Timmer expired for read or write                     */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* The number of characters read is returned in parms->out_retval.     */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* TermWrite will write to the minor device.                           */
/*---------------------------------------------------------------------*/
void TermWrite (struct ioparms *parms);

/*---------------------------------------------------------------------*/
/* The in_iopb element of the ioparms structure will point to a TermIO */
/* structure as described in the TermRead call. TermWrite will write   */
/* characters pointed to by buffp according to the configuration set   */
/* up by the call to TermOpen or configuration changed by TermIoctl.   */
/* The write will be of the length requested.                          */
/*                                                                     */
/* If WNWAIT flag is set the characters pointed to by buffp will be    */
/* copied to a new buffer before the call returns. There will be no    */
/* confirmation of the success of the write.                           */
/*                                                                     */
/* TermWrite will return in parms->err zero on success or one of the   */
/* following error codes:                                              */
/*                                                                     */
/* TERM_NOPEN  minor device has not been opened                        */
/* TERM_NINIT     driver not initialized                               */
/* TERM_MINOR     Invalid minor device                                 */
/* TERM_NMBLK     no buffer headers  (esballoc failed)                 */
/* TERM_DCDINT    Terminated by loss of DCD                            */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* The number of characters written is returned in parms->out_retval.  */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* TermIoctl will perform control functions on the minor device. In    */
/* most cases these functions are used to change the device's          */
/* configuration or get the current value of the configuration.        */
/*---------------------------------------------------------------------*/
void TermIoctl (struct ioparms *parms);

/*---------------------------------------------------------------------*/
/* The in_iopb element of the ioparms structure will point to a TermCtl*/
/* structure:                                                          */
/*---------------------------------------------------------------------*/
typedef struct {
    unsigned long function;          /* function code for the I/O */
                                     /* control call */
    void *arg;                       /* pointer to function dependent */
                                     /* information */
}TermCtl;

typedef struct 
    {
    unsigned long ParityErrs;        /* number of parity errors */
    unsigned long FramingErrs;       /* number of framing errors */
    unsigned long OverrunErrs;       /* number of overrun errors */
    unsigned long AutoBaudEnb;       /* is auto baud enabled */
    } ASYNC_STAT;

typedef struct 
    {
    unsigned long FrameCheckErrs;       /* frame check errors */
    unsigned long TransmitUnderrunErrs; /* transmit underrun errors */
    unsigned long ReceiveOverrunErrs;   /* receive overruns errors */
    unsigned long InterruptedFrames;    /* frames that were stopped */
    unsigned long AbortedFrames;        /* frames that were aborted */
    } SYNC_STAT;

/*---------------------------------------------------------------------*/
/* Termio is the control structure for a channel                       */
/*---------------------------------------------------------------------*/
#define NCC 10
 struct termio {
    unsigned short    c_iflag;    /* input modes */
    unsigned short    c_oflag;    /* output modes */
    unsigned short    c_cflag;    /* control modes */
    unsigned short    c_lflag;    /* line discipline modes */
    unsigned char     c_cc[NCC];  /* control chars */
};

/*---------------------------------------------------------------------*/
/* Control Characters (c_cc)                                           */
/*---------------------------------------------------------------------*/
#define VERASE  2
#define VMIN    4
#define VTIME   5
#define VEOF    6
#define VEOL    7
#define VSTART  8
#define VSTOP   9

/*---------------------------------------------------------------------*/
/* Input Modes (c_iflag)                                               */
/* NOTE: The following definitions are in octal (termio specifications)*/
/*---------------------------------------------------------------------*/
#define    IGNBRK    0000001 /* Ignore break condition */
#define    BRKINT    0000002 /* interrupt on break */

#define    IPOST     0001700 /* input processing mask */
#define    INLCR     0000100 /* Map NL to CR on input */
#define    IGNCR     0000200 /* Ignore CR */
#define    ICRNL     0000400 /* Map CR to NL on input. */
#define    IUCLC     0001000 /* Map upper-case to lower-case on input */

#define    IXON      0002000 /* Enable start/stop output control */
#define    IXOFF     0010000 /* Enable start/stop input control. */
#define    IMAXBEL   0020000 /* Echo BEL on input line too long. */

/*---------------------------------------------------------------------*/
/* Output Modes (c_oflag)                                              */
/* NOTE: The following definitions are in octal (termio specifications)*/
/*---------------------------------------------------------------------*/
#define    OPOST    0000001
#define    OLCUC    0000002
#define    ONLCR    0000004
#define    OCRNL    0000010
#define    ONOCR    0000020
#define    ONLRET   0000040

/*---------------------------------------------------------------------*/
/* Control Modes (c_cflag)                                             */
/* NOTE: CBAUD definition is in octal (termio specifications)          */
/*---------------------------------------------------------------------*/
extern const ULONG baud_table[];
#define    BAUD_TABLE_SIZE   16      /* Size of baud_table[]           */

#define    CBAUD    0000017
    #define B0     0
    #define B50    1
    #define B75    2
    #define B110   3
    #define B134   4
    #define B150   5
    #define B200   6
    #define B300   7
    #define B600   8
    #define B1200  9
    #define B1800  10
    #define B2400  11
    #define B4800  12
    #define B9600  13
    #define B19200 14
    #define B38400 15

/*---------------------------------------------------------------------*/
/* NOTE: The following definitions are in octal (termio specifications)*/
/*---------------------------------------------------------------------*/

#define    CSIZE    0000060
    #define CS5    0
    #define CS6    0000020
    #define CS7    0000040
    #define CS8    0000060

#define    CSTOPB   0000100
#define    CREAD    0000200
#define    PARENB   0000400
#define    PARODD   0001000
#define    CLOCAL   0004000

/*---------------------------------------------------------------------*/
/* Line Discipline Modes (c_lflag)                                     */
/* NOTE: The following definitions are in octal (termio specifications)*/
/*---------------------------------------------------------------------*/
#define    ICANON   0000002
#define    ECHO     0000010
#define    ECHONL   0000100 /* If set, the NL character will be echoed */
                            /* even if ECHO is not set                 */

/*---------------------------------------------------------------------*/
/* I/O Control Commands                                                */
/*---------------------------------------------------------------------*/
#define    TIOC(x)    (x<<8)

#define    TCGETA      TIOC(1) /* same as TCGETS */
#define    TCSETA      TIOC(2) /* same as TCSETS */
#define    TCSETAW     TIOC(3)
#define    TCSETAF     TIOC(4)
#define    TCSBRK      TIOC(5)

#define    TCXONC      TIOC(6)
    #define TCOOFF   0  /* suspend output */
    #define TCOON    1  /* restart suspended output */
    #define TCIOFF   2  /* suspend input */
    #define TCION    3  /* restart suspended input */

#define    TCFLSH      TIOC(7)
    #define TCIFLUSH 0  /* flush data received but not read */
    #define TCOFLUSH 1  /* flush data written but not transmitted */
    #define TCIOFLUSH 2  /* flush both data both input and output queues */

#define    TCGETS      TIOC(13)
#define    TCSETS      TIOC(14)
#define    TCSETSW     TIOC(15)
#define    TCSETSF     TIOC(16)

#define    TIOCMBIS    TIOC(27)    /* bis modem bits */
#define    TIOCMBIC    TIOC(28)    /* bic modem bits */
#define    TIOCMGET    TIOC(29)    /* get all modem bits */
#define    TIOCMSET    TIOC(30)    /* get all modem bits */
    #define TIOCM_DTR   0x0002     /* data terminal ready */
    #define TIOCM_RTS   0x0004     /* request to send */
    #define TIOCM_ST    0x0008     /* secondary transmit */
    #define TIOCM_SR    0x0010     /* secondary receive */
    #define TIOCM_CTS   0x0020     /* clear to send */
    #define TIOCM_CAR   0x0040     /* carrier detect */
    #define TIOCM_CD    TIOCM_CAR
    #define TIOCM_RNG   0x0080     /* ring */
    #define TIOCM_RI    TIOCM_RNG
    #define TIOCM_DSR   0x0100     /* data set ready */

/*---------------------------------------------------------------------*/
/* Extended I/O Control Functions                                      */
/*---------------------------------------------------------------------*/
/* TERMGETDEFTERM will copy the current minor number of the default    */
/* console to the unsigned long pointed to by arg.                     */
/*---------------------------------------------------------------------*/
#define TERMGETDEFTERM    0x00002500

/*---------------------------------------------------------------------*/
/* TERMPUTDEFTERM will change the current value of the default console */
/* to the unsigned long pointed to by arg.                             */
/*---------------------------------------------------------------------*/
#define TERMPUTDEFTERM    0x00002600

/*---------------------------------------------------------------------*/
/* TERMHWFC will use CTS/RTS flow control. This command has not effect */
/* if the channel does not support hardware flow control.              */
/*---------------------------------------------------------------------*/
#define TERMHWFC          0x00002700

/*---------------------------------------------------------------------*/
/* TERMGETASYNCSTAT The arg is a pointer to a ASYNC_STAT structure that*/
/* will be filled in with the channels asynchronous status.            */
/*---------------------------------------------------------------------*/
#define TERMGETASYNCSTAT  0x00002800

/*---------------------------------------------------------------------*/
/* TERMGETSYNCSTAT The arg is a pointer to a SYNC_STAT structure that  */
/* will be filled in with the channels synchronous status.             */
/*---------------------------------------------------------------------*/
#define TERMGETSYNCSTAT   0x00002900

/*---------------------------------------------------------------------*/
/* TERMNUMOFCHANNELS The arg is a pointer to a unsigned long that will */
/* be filled in with the total number of serial channels.              */
/*---------------------------------------------------------------------*/
#define TERMNUMOFCHANNELS 0x00002A00

/*---------------------------------------------------------------------*/
/* TERMAUTOBAUD The channel may attempt to autobaud instead of using   */
/* the baudrate, parity and character size given. This is not          */
/* implemented currently.                                              */
/*---------------------------------------------------------------------*/
#define TERMAUTOBAUD      0x00002B00

/*---------------------------------------------------------------------*/
/* TermIoctl will return in parms->err zero on success or one of the   */
/* following error codes:                                              */
/*                                                                     */
/* TERM_NOPEN     minor device has not been opened                     */
/* TERM_NINIT     driver not initialized                               */
/* TERM_BAUD      Invalid baud rate                                    */
/* TERM_CHARSIZE  bad character size                                   */
/* TERM_BADFLAG   flag not defined                                     */
/* TERM_MINOR     Invalid minor device                                 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* TermClose will close the minor device (serial channel). This will   */
/* flush all transmit buffers, discard                                 */
/* all pending receive buffers and disable the receiver and            */
/* transmitter of the channel. All buffers associated with the channel */
/* will be released (freed) and the device will hang up the line. All  */
/* further TermRead, TermWrite or TermIoctl calls to the channel will  */
/* return with the error TERM_NOPEN.                                   */
/*---------------------------------------------------------------------*/
void TermClose (struct ioparms *parms);

/*---------------------------------------------------------------------*/
/*                                                                     */
/* TermClose will return in parms->err zero on success or one of the   */
/* following error codes:                                              */
/*                                                                     */
/* TERM_NOPEN 0x10010212  minor device has not been opened             */
/* TERM_NINIT  driver not initialized                                  */
/* TERM_MINOR  Invalid minor device                                    */
/*---------------------------------------------------------------------*/

#endif  /* _DITI_H */

#if __cplusplus
}
#endif
