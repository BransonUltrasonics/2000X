/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\drv_intf.h_v   1.0   Mar 29 1999 13:50:56   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/drv_intf.h 1.62 97/10/24 12:25:56 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/drv_intf.h                                       */
/*   DATE:    97/10/24                                                 */
/*   PURPOSE: Definitions for application/driver interface             */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1997 Integrated Systems, Inc.            */
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
/*   This file defines the structures and constants required by the    */
/*   the de_cntrl() functions of many of pSOSystem's drivers.  It      */
/*   also defines the error codes for many of pSOSystem's drivers.     */
/*                                                                     */
/*   The origin of error codes returned to pSOSystem applications      */
/*   may be determined from the following table (error code values     */
/*   are in hex, with the apostrophe inserted for readability).        */
/*                                                                     */
/*      ERROR CODE RANGE            ORIGIN             DEFINED IN      */
/*     FROM            To                                              */
/*    =========================   ==================     ==============*/
/*    00 00 00 01 - 00 00 0F FF   pSOS+, pSOS+m          <psos.h>      */
/*    00 00 10 00 - 00 00 1F FF   (reserved)                           */
/*    00 00 20 00 - 00 00 2F FF   pHILE+                 <phile.h>     */
/*    00 00 30 00 - 00 00 3F FF   pREPC+                 <errno.h>     */
/*    00 00 40 00 - 00 00 4F FF   (reserved)                           */
/*    00 00 50 00 - 00 00 5F FF   pNA+, pRPC+, pX11+     <pna.h>       */
/*    00 00 60 00 - 00 00 FF FF   (reserved)                           */
/*    00 01 00 00 - 00 FF FF FF   (reserved)                           */
/*                                                                     */
/*    01 10 00 00 - 01 1F FF FF   Networking Libraries                 */
/*    01 20 00 00 - 01 20 00 FF   MMUlib                 <mmulib.h>    */
/*    01 20 01 00 - 01 20 01 FF   Loader                               */
/*                                                                     */
/*    01 20 02 00 - 0F FF FF FF   (reserved for pSOSystem libraries)   */
/*                                                                     */
/*    10 00 00 00 - 10 00 00 FF   NI_SMEM driver                       */
/*    10 00 01 00 - 10 00 01 FF   KI_SMEM driver                       */
/*    10 00 02 00 - 10 00 FF FF   (reserved for pSOSystem)             */
/*    10 01 00 00 - 10 01 FF FF   serial driver          <drv_intf.h>  */
/*    10 02 00 00 - 10 02 FF FF   tick timer driver      <drv_intf.h>  */
/*    10 03 00 00 - 10 03 FF FF   (reserved for pSOSystem)             */
/*    10 04 00 00 - 10 04 FF FF   RAM disk driver        <drv_intf.h>  */
/*    10 05 00 00 - 10 05 FF FF   (reserved for pSOSystem)             */
/*    10 06 00 00 - 10 06 FF FF   TFTP driver            <drv_intf.h>  */
/*    10 07 00 00 - 10 07 FF FF   SLIP driver                          */
/*    10 08 00 00 - 10 08 FF FF   (reserved for pSOSystem)             */
/*    10 09 00 00 - 10 09 FF FF   IDE driver                           */
/*    10 0A 00 00 - 10 0A FF FF   FLOPPY driver                        */
/*    10 0B 00 00 - 10 0B FF FF   IrDA driver                          */
/*    10 0C 00 00 - 10 4F FF FF   (reserved for pSOSystem)             */
/*    10 50 00 00 - 10 5F FF FF   SCSI driver            <drv_intf.h>  */
/*    10 60 00 00 - 10 6F FF FF   Parallel Port driver                 */
/*    10 70 00 00 - 1F FF FF FF   (reserved for pSOSystem)             */
/*    20 00 00 00 - FF FF FF FF   (reserved for application use)       */
/*                                                                     */
/*  * NOTE: Error codes in the range 20 00 00 00 - FF FF FF FF         */
/*          are reserved for user-added drivers.  Any custom drivers   */
/*          you add to pSOSystem should return error codes in          */
/*          this range.  Other ranges marked "(reserved)" are          */
/*          reserved for use by future additions to pSOSystem and      */
/*          should not be used by custom drivers.                      */
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
#ifndef _DRV_INTF_H
#define _DRV_INTF_H

#include <types.h>

/*---------------------------------------------------------------------*/
/* DRV_INIT_REG The driver initialization register of the IDLE task.   */
/* It is used by device drivers as a initialization done flag. This    */
/* register is cleared to 0 when the IDLE task is created.             */
/* Each device will use it major device number as the bit number it    */
/* sets when the device initialization is done.                        */
/*---------------------------------------------------------------------*/
#define DRV_INIT_REG 8

/*---------------------------------------------------------------------*/
/* SERV_INIT_REG The Service initialization register of the IDLE task. */
/* This register is used by services as an initialization done flag.   */
/* This register is cleared to 0 when the IDLE task is created.        */
/* Each service will use a defined bit number that is defined below    */
/* in this file as the bit to set in this register when the service    */
/* is done with it initialization.                                     */
/*---------------------------------------------------------------------*/
#define SERV_INIT_REG 9

#define SMKI_INIT_BIT 0
#define SMNI_INIT_BIT 1
#define LAN_INIT_BIT  2

/*---------------------------------------------------------------------*/
/* CNSL_INIT_REG The driver initialization register of the IDLE task.  */
/* It is used by Console drivers as a initialization done flag. This   */
/* register is cleared to 0 when the IDLE task is created.             */
/* Each Minor Device number will be used as the bit number.            */
/*---------------------------------------------------------------------*/
#define CNSL_INIT_REG 10

/*---------------------------------------------------------------------*/
/* PSEUDO_IO_REG in the register number of the IDLE task that is used  */
/* by the pseudo driver which is used by Net Utilities.                */
/*---------------------------------------------------------------------*/
#define PSEUDO_IO_REG  11

/*---------------------------------------------------------------------*/
/* SCSI_INIT_REG in the register number of the IDLE task that is used  */
/* by the scsi driver.                                                 */
/*---------------------------------------------------------------------*/
#define SCSI_INIT_REG  12


/*---------------------------------------------------------------------*/
/*   CC_PP_REG C++ Idle scratch register                               */
/*---------------------------------------------------------------------*/
#define CC_PP_REG 14

/*---------------------------------------------------------------------*/
/* IDE_INIT_REG in the register number of the IDLE task that is used   */
/* by the ide driver.                                                  */
/*---------------------------------------------------------------------*/
#define IDE_INIT_REG  15

/*---------------------------------------------------------------------*/
/* DMAJOR returns the major number of a device from the                */
/* ioparms->in_dev variable.                                           */
/*---------------------------------------------------------------------*/
#define DMAJOR(x) ((x & 0xFFFF0000) >> 16) 

/*---------------------------------------------------------------------*/
/* DMINOR returns the minor device number of a device from the         */
/* ioparms->in_dev variable.                                           */
/*---------------------------------------------------------------------*/
#define DMINOR(x) (x & 0x0000FFFF)

/*---------------------------------------------------------------------*/
/* IDLE_TID The IDLE task tid is used by drivers and services to get   */
/* the IDLE task system note pad registers.                            */
/*---------------------------------------------------------------------*/
#define IDLE_TID 0x00010000

/*---------------------------------------------------------------------*/
/* Functions used to manipulate Scratch pad Registers                  */
/*---------------------------------------------------------------------*/
unsigned long  ScratchPadTest(unsigned long  tid,
               unsigned long  register_number, unsigned long bit);
unsigned long  ScratchPadSet(unsigned long  tid,
               unsigned long  register_number, unsigned long bit);
unsigned long  ScratchPadUnSet(unsigned long  tid,
               unsigned long  register_number, unsigned long bit);

/*---------------------------------------------------------------------*/
/* Error codes returned by Scratch Pad functions                       */
/*---------------------------------------------------------------------*/
#define SP_OK 0
#define SP_BIT_NOT_SET 0
#define SP_BIT_SET 1
#define SP_BITNUM 3

/*---------------------------------------------------------------------*/
/* Errors which may be returned by the serial driver                   */
/*---------------------------------------------------------------------*/
#define CNSL_HDWR  0x10010100  /* Hardware error */
#define CNSL_MINOR 0x10010201  /* Invalid minor device # */
#define CNSL_CTRL  0x10010202  /* Invalid function code for Cnsl_Ctrl()*/
#define CNSL_BAUD  0x10010203  /* Invalid baud rate for Cnsl_cntrl() */
#define CNSL_NINIT 0x10010204  /* Device not initialized */
#define CNSL_DATA  0x10010205  /* Unable to allocate driver data area */
#define CNSL_SEM   0x10010206  /* Semaphore error */
#define CNSL_OSYNC 0x10010207  /* Out of sync */
#define CNSL_OPER  0x10010208  /* Operation failed */
#define CNSL_PARAM 0x10010209  /* Invalid parameter */
#define CNSL_AINIT 0x10010210  /* Console already initialized */

/*---------------------------------------------------------------------*/
/* Error from tick timer                                               */
/*---------------------------------------------------------------------*/
#define TIMR_TICKRATE 0x10020001 /* Unsupported rate for kc_ticks2sec */

/*---------------------------------------------------------------------*/
/* Errors which may be returned by the RAM disk driver                 */
/*---------------------------------------------------------------------*/
#define RDSK_BLOCK 0x10040001  /* Block number too large */
#define RDSK_SEM   0x10040002  /* Semaphore error */
#define RDSK_MEM   0x10040003  /* Memory error */

/*---------------------------------------------------------------------*/
/* Errors which may be returned by the SCSI driver.                    */
/*---------------------------------------------------------------------*/
#define SCSI_ERR            0x10510000 /* SCSI general error code ored */
                                       /* with actual scsi error code */
                                       /* see scsi.h "Values returned */
                                       /* by scsi commands" for more  */
                                       /* information */
#define SCSI_FSC            0x10500003 /* Failed to send SCSI command */
#define SCSI_CHP            0x10500009 /* Failed to init SCSI chip */
#define SCSI_UKC            0x1050000B /* Unknown de_ctnrl() function */
#define SCSI_ID_ERR         0x1050000C /* Bad SCSI ID de_ctnrl() */
#define SCSI_NULL_CDB       0x1050000D /* NULL SCSI Control block */
#define SCSI_PTR_CONFLICT   0x1050000E /* Both in and out data */
                                       /* length given */
#define SCSI_DATA_PTR_NULL  0x1050000F /* NULL data pointer */
#define SCSI_NOT_INIT       0x10500010 /* SCSI not initialized */

#define SCSI_ILLRECON       0x10500011 /* bad reconnection */
                                       /* (no disconnect) */
#define ESDNOTTDIR          0x10500012 /* incorrect device type for */
                                       /* operation*/
#define ESDNODEVICE         0x10500013 /* no such device on SCSI bus */
#define ESBLOCKOUTOFRANGE   0x10500014 /* block given is beyond end */
                                       /* of disk  */
#define ESODDBLOCK          0x10500015 /* Block size is less than */
                                       /* physical */
#define ESNO_CAPACITY       0x10500016 /* capacity shows 0 maybe */
                                       /* floppy not in drive? */
#define SCSI_FORMAT_FAILED  0x10500017
#define SCSI_PART_NUM_BAD   0x10500018 /* Bad partition number */
#define SCSI_NOT_PARTITION  0x10500019 /* device not partitioned */
#define SCSI_W_PROTECTED    0x1050001A /* write protected */
#define SCSI_NO_MEM         0x1050001B /* need memory to complete */
                                       /* command not available */
#define SCSI_NOT_OPEN       0x1050001C /* SCSI device not open */
#define ESDALLREADYOPEN     0x1050001D /* SCSI device is already open */
#define SCSI_END_OF_FILE    0x1050001E /* end of tape file encountered */

/*---------------------------------------------------------------------*/
/* TFTP Driver generated Errors                                        */
/*---------------------------------------------------------------------*/
#define TFTP_PROTO     0x10060001      /* protocol error detected such */
                                       /* as a non DATA packet being   */
                                       /* received or did not get      */
                                       /* expected message             */
                                       /* acknowledgment               */
#define TFTP_TMOUT     0x10060002      /* TFTP server timed out while  */
                                       /* waiting for a response from  */
                                       /* the TFTP client              */
#define TFTP_SYNC      0x10060003      /* TFTP server out of sync      */
                                       /* with TFTP client             */
#define TFTP_NOSPC     0x10060004      /* No more free socket ids      */
#define TFTP_INVAL     0x10060005      /* channel number (minor number)*/
                                       /* exceeds Maximum number of    */
                                       /* channels the driver can open */
#define TFTP_NOINIT    0x10060006      /* call failed because TFTP     */
                                       /* driver has not been          */
                                       /* initialized                  */

/*---------------------------------------------------------------------*/
/* Errors which may be returned by the IDE driver                      */
/*---------------------------------------------------------------------*/
#define IDE_HDWR          0x10090001  /* Hardware error                */
#define IDE_MINOR         0x10090002  /* Invalid minor device #        */
#define IDE_CTRL          0x10090003  /* Invalid func code for Ctrl()  */
#define IDE_NINIT         0x10090004  /* Device not initialized        */
#define IDE_DATA          0x10090005  /* Unable to alloc drv data area */
#define IDE_SEM           0x10090006  /* Semaphore error               */
#define IDE_BBLK          0x10090007  /* Bad Block                     */
#define IDE_UCOR          0x10090008  /* Uncorrectable Error           */
#define IDE_SNF           0x10090009  /* Sector Not Found              */
#define IDE_T0NF          0x1009000a  /* Track 0 Not Found             */
#define IDE_NDAM          0x1009000b  /* Data Address Mark Not Found   */
#define IDE_RANGE         0x1009000c  /* Block range error */
#define IDE_DRV           0x1009F000  /* Drv related err(see last byte)*/
#define IDE_WPROT         0x1009000d  /* Partition Write Protected     */
#define IDE_NO_DEVICE     0x1009000e  /* No Device Found               */
#define IDE_PART_NUM_BAD  0x1009000f  /* Bad Partition Number.         */
#define IDE_MEMORY        IDE_DATA
#define IDE_SEM4          IDE_SEM

/*---------------------------------------------------------------------*/
/* Errors which may be returned by the FLP driver                      */
/*---------------------------------------------------------------------*/
#define FLP_MINOR  0x100A0001  /* Invalid minor device # */
#define FLP_NINIT  0x100A0002  /* Device not initialized */
#define FLP_SEM    0x100A0003  /* Semaphore error */
#define FLP_QUEUE  0x100A0004  /* Can not create a message queue */
#define FLP_TASK   0x100A0005  /* Can not create the motor control task */
#define FLP_RD     0x100A0006  /* Floppy drive read failure */
#define FLP_WR     0x100A0007  /* Floppy drive write failure */
#define FLP_DATA   0x100A0008  /* Unable to allocate driver data area */
#define FLP_DSKCHG 0x100A0009  /* Floppy drive disk changed */
#define FLP_DRV    0x100AF000  /* Drive related error in the last byte */

/*=====================================================================*/
/* Interface to the serial driver de_cntrl() function - parameters     */
/* that are ON/OFF use 0 for OFF, non-zero for ON.  "Binary mode"      */
/* causes the driver to ignore the delete and end-of-record characters */
/* The "default_console" controls which minor device that minor device */
/* 0 remaps to.                                                        */
/*=====================================================================*/
struct cnsl_ci_map_parms
    {
    int (*pna_recv)(int, char *, int ,int);
    int (*pna_send)(int, char *, int ,int);
    int (*pna_select)(int, void *, void *, void *, void *);
    int (*pna_close)(int);
    unsigned long (*phile_read)(unsigned long, void *, unsigned long, unsigned long *);
    unsigned long (*phile_write)(unsigned long, void *, unsigned long);
    };

struct cnsl_tn_map_parms
    {
    unsigned short flag;
    unsigned short fd;
    unsigned long  tid;
    int   (*read)(unsigned short, unsigned long, unsigned long, unsigned char);
    int   (*write)(unsigned short, unsigned long, unsigned long, unsigned char);
    int   (*close)(void);
    };

struct cnsl_io_map_parms
    {
    unsigned char  direction;
    unsigned char  type;
    unsigned short fd;
    unsigned long  tid;
    };

struct cnsl_parms
    {
    char echo;     /* Echoing of input characters - ON or OFF */
    char delchar;  /* Delete char */
    char eorchar;  /* End-of-record character */
    char binmode;  /* Binary mode - ON or OFF */
    char nlconv;   /* Convert NL to NL/CR on output, and convert CR */
                   /*  to NL on input (ON or OFF) */
    char nonblock; /* Non-blocking read mode - ON or OFF */
    char reserved[2]; /* Reserved for future use */
    long timeout;  /* Read timeout in ticks (0 = none) */
    long baudrate; /* Baud rate */
    };

struct cnsl_ctl_iopb
    {
    long function;     /* Function code - values defined below */
    union
        {
        struct cnsl_ci_map_parms ci_parms;
        struct cnsl_tn_map_parms tn_parms;
        struct cnsl_io_map_parms io_parms;
        struct cnsl_parms parms;
        unsigned short default_console;
        } u;
    };

/*---------------------------------------------------------------------*/
/* Values for io-type code                                             */
/*---------------------------------------------------------------------*/
#define CNSL_IO_SOCKET    0
#define CNSL_IO_FILE      1
#define CNSL_IO_REG       15
#define CNSL_RAW          0x01
#define CNSL_NOECHO       0x02
#define CNSL_NOMAPLF      0x04

/*---------------------------------------------------------------------*/
/* Values for function code                                            */
/*---------------------------------------------------------------------*/
#define CNSL_GET_PARMS      1  /* Get current parameter values */
#define CNSL_SET_PARMS      2  /* Set the parameter values */
#define CNSL_GET_DEFCNSL    3  /* Get minor # of default console */
#define CNSL_SET_DEFCNSL    4  /* Set minor # of default console */

#define CNSL_TN_MAPALLIO    5  /* Redirect all I/O to a telnet session */
#define CNSL_TN_MAPTASKIO   6  /* Redirect per task I/O to a telnet */
                               /* session */
#define CNSL_IO_MAP         7  /* Redirect per task I/O */
#define CNSL_CI_MAP         8  /* Entry points for pna, OpEN & phile */

/*=====================================================================*/
/* Interface to the SCSI de_cntrl() function                           */
/*=====================================================================*/

#define SCSI_VENDOR_SIZE 9
#define SCSI_PRODUCT_SIZE 17

/*---------------------------------------------------------------------*/
/* Number of partitions allowed per drive (must be set to 4 if the     */
/* device drive,  is also used on a PC                                 */
/*---------------------------------------------------------------------*/
#define SCSI_PART_TABLE_SIZE 4

/*---------------------------------------------------------------------*/
/* SCSI_MAX_PART is the total number of DOS partitions allowed per     */
/* drive. This total is a combination of primary and extended DOS      */
/* partitions.                                                         */
/*---------------------------------------------------------------------*/
#define SCSI_MAX_PART 8

typedef struct
    {
    int begin;                      /* beginning logical block */
    int size;                       /* size in blocks */
    unsigned char partition_wp;     /* write protected */
    } PARTITION_INFO;

struct scsi_info
   {
   unsigned char devtype;           /* Type of device */
   unsigned char scsi_id;           /* Device address on the SCSI bus */
   unsigned char lun;               /* Device's LUN */
   unsigned char removeable;        /* Removeable media */
   unsigned char loaded;            /* set to 1 if loaded */
   char vendor[SCSI_VENDOR_SIZE];   /* Device's manufacturer */
   char product[SCSI_PRODUCT_SIZE]; /* Model name */
   long blocks;                     /* Capacity in blocks */
   long blocksize;                  /* Size of each block in bytes */
   PARTITION_INFO partition_info[SCSI_MAX_PART]; /* Partition table */
   };

struct scsi_cmd
   {
   int target_id;             /* target id of SCSI device      */
   unsigned char *data_ptr;   /* pointer to in/out data area   */
   unsigned int data_in_len;  /* max data to take in           */
   unsigned int data_out_len; /* actual ammount of data to send*/
   unsigned int command_len;  /* length of SCSI CDB            */
   unsigned char *cdb;        /* pointer to SCSI CDB           */
   };

typedef struct
    {
    int begin;                      /* beginning logical block */
    int size;                       /* size in blocks */
    } PARTITION_ENTRY;              /* used with SCSI_CTL_PARTITION */

struct scsi_ctl_iopb
    {
    long function;      /* Function code - values defined below */
    union
        {
        void *arg;
        struct scsi_info info;
        struct scsi_cmd cmd;
        } u;
    };

struct scsi_open_iopb
    {
    unsigned char  exclusive;  /* set to 1 if open for only 1 task */
    unsigned char  rewind;     /* set to 1 if rewind to be done at close */
    };

typedef struct scsi_rw_iopb
    {
    unsigned long b_device;        /* device number */
    unsigned long b_bcount;        /* data length in characters */
    void *b_bufptr;                /* data area     */
    } TAPE_BUFFER_HEADER;

/*---------------------------------------------------------------------*/
/* Values for function code                                            */
/*---------------------------------------------------------------------*/
#define SCSI_CTL_FORMAT          1 /* Format the disk */
#define SCSI_CTL_INFO            2 /* Get information about a device */
#define SCSI_CTL_CMD             3 /* Issue a scsi command */
#define SCSI_CTL_TEST_UNIT_READY 4 /* Test for ready */
#define SCSI_CTL_PARTITION       5 /* Partition drive */
#define SCSI_CTL_READ_ONLY_P     6 /* Write Protect a Partition */
#define SCSI_CTL_READ_WRITE_P    7 /* Read and Write a Partition */
#define SCSI_CTL_START_DEVICE    8 /* Start the drive */
#define SCSI_CTL_STOP_DEVICE     9 /* Stop the drive */
#define SCSI_CTL_STOP_COMMANDS  10 /* Stop Commands being sent to bus */
#define SCSI_CTL_START_COMMANDS 11 /* Start Commands being sent to bus */
#define SCSI_CTL_SKIP           12 /* Skip to next file mark */
#define SCSI_CTL_REWIND         13 /* Rewind tape */
#define SCSI_CTL_UNLOAD         14 /* Unload tape */
#define SCSI_CTL_ERASE          15 /* Erase tape */
#define SCSI_CTL_WRITE_FILE_MARK 16 /* Write file mark on tape */
#define SCSI_CTL_SET_BLOCK_MODE 17 /* Set block mode and size */

/*---------------------------------------------------------------------*/
/* Values for info.devtype                                             */
/*---------------------------------------------------------------------*/
#define SCSI_TYPE_DIRECT      0x00   /* direct access (disk)           */
#define SCSI_TYPE_SEQUENTIAL  0x01   /* sequential access (tape)       */
#define SCSI_TYPE_PRINTER     0x02   /* printer                        */
#define SCSI_TYPE_PROCESSOR   0x03   /* processor board                */
#define SCSI_TYPE_WORM        0x04   /* write once (optical disk)      */
#define SCSI_TYPE_CDROM       0x05   /* cd rom                         */
#define SCSI_TYPE_SCANNER     0x06   /* scanner                        */
#define SCSI_TYPE_OMEM        0x07   /* optical memory (some disks)    */
#define SCSI_TYPE_CHANGER     0x08   /* medium changer (jukeboxes)     */
#define SCSI_TYPE_COMM        0x09   /* communication device           */
#define SCSI_TYPE_UNKNOWN     0x1F   /* unknown device type            */
#define SCSI_TYPE_HOST        0xFF   /* ID is of HOST system           */

/*=====================================================================*/
/* Interface to the IDE  de_cntrl() function                           */
/*=====================================================================*/

#define IDE_MAX_PART           8
#define IDE_MAX_HEADS         16
#define IDE_MAX_BIOS_CYL    1023

typedef struct ide_disk_geom
        {
        ULONG   cylinders;      /* Cylinders on Disk            */
        ULONG   heads;          /* # of Heads                   */
        ULONG   spt;            /* Sectors/Track                */
        ULONG   sectors;        /* Sectors/Track                */
        } IDE_DISK_GEOM;

typedef struct
    {
    ULONG       s_cylinder;
    ULONG       s_sector;
    ULONG       s_head;
    ULONG       e_cylinder;
    ULONG       e_sector;
    ULONG       e_head;
    ULONG       begin;          /* beginning logical block */
    ULONG       size;           /* size in blocks */
    ULONG       partition_wp;   /* write protected */
    } IDE_PARTITION_INFO;

typedef struct ext_ide
        {
        ULONG   drvnum;
        ULONG   base_addr;
        ULONG   irq_lev;
        ULONG   drives;
        ULONG  *activeptr;
        } EXT_IDE;

typedef struct ide_info
        {
        ULONG   ide_id;         /* Device address on the IDE    */
        char    *model;         /* Model Number                 */
        char    *serial;        /* Serial Number                */
        char    *rev_no;        /* Controller Rev. #            */
 
        IDE_DISK_GEOM   logical_info; /* Logical Geometry       */
        IDE_DISK_GEOM   physical_info;/* Physical Geo.          */
                                /* Partition table              */
        IDE_PARTITION_INFO  partition_info[IDE_MAX_PART];
        } IDE_INFO;
 
typedef struct ide_cmd
        {
        ULONG    un_used;
        } IDE_CMD;
 
typedef struct ide_ctl_iopb
        {
        ULONG    function;      /* Function code - values defined below */
        union
            {
            void      *arg;
            IDE_INFO   info;
            EXT_IDE    ext_ide;
            } u;
        } IDE_CTL_IOPB;

/*---------------------------------------------------------------------*/
/* Values for function code                                            */
/*---------------------------------------------------------------------*/
#define IDE_INIT_DONE     0x10090010  /* drive was already initialized */
#define IDE_CTL_INFO          1
#define IDE_CTL_READ_ONLY_P   2
#define IDE_CTL_READ_WRITE_P  3
#define IDE_CTL_CLOSE         4
#define IDE_OPEN_DEVICE       4
#define IDE_CLOSE_DEVICE      5

/*---------------------------------------------------------------------*/
/* Values for info.devtype                                             */
/*---------------------------------------------------------------------*/
#define IDE_TYPE_DIRECT       0x00   /* direct access (disk)           */
#define IDE_TYPE_SEQUENTIAL   0x01   /* sequential access (tape)       */
#define IDE_TYPE_PRINTER      0x02   /* printer                        */
#define IDE_TYPE_PROCESSOR    0x03   /* processor board                */
#define IDE_TYPE_WORM         0x04   /* write once (optical disk)      */
#define IDE_TYPE_CDROM        0x05   /* cd rom                         */
#define IDE_TYPE_SCANNER      0x06   /* scanner                        */
#define IDE_TYPE_OMEM         0x07   /* optical memory (some disks)    */
#define IDE_TYPE_CHANGER      0x08   /* medium changer (jukeboxes)     */
#define IDE_TYPE_COMM         0x09   /* communication device           */
#define IDE_TYPE_UNKNOWN      0x1F   /* unknown device type            */

/*=====================================================================*/
/* Interface to the TFTP                                               */
/*=====================================================================*/
/* The TFTP driver provides the capability to handle up to eight       */
/* simultaneous open channels transferring data over network from a    */
/* remote host using TFTP protocol.  The channel numbers are coded     */
/* in the minor part of the device number.  There are four entry       */
/* points to the driver - init, open, close and read.  The user shall  */
/* initialize pNA+ (by calling pna_init()) in the application code     */
/* before accessing the device driver.  A call to de_open() shall be   */
/* made before de_read().  The de_open() shall be called with an IOPB  */
/* of the following:                                                   */
/*---------------------------------------------------------------------*/
typedef struct
    {
    unsigned long   ip_addr;     /* IP Address of the host */
    char           *filename;    /* Filename to transfer */
    } TFTP_IOPB;

/*---------------------------------------------------------------------*/
/* The data can be read by calling de_read() with the following IOPB:  */
/*---------------------------------------------------------------------*/
typedef struct
    {
    unsigned long    count;
    void        *address;
    } TFTP_READ_IOPB;

/*---------------------------------------------------------------------*/
/* Error codes returned by the Shared memory Network Interface         */
/* (ni_smem)                                                           */
/*---------------------------------------------------------------------*/
#define NISMEM_FAT_IPA       0x10000001    /* Invalid IP address */

/*---------------------------------------------------------------------*/
/* Error codes returned by the Shared memory Kernel Interface          */
/* (ki_smem)                                                           */
/*---------------------------------------------------------------------*/
#define KISMEM_FAT_NOPB      0x10000101    /* no packet buffers        */
#define KISMEM_FAT_NOQ       0x10000102    /* no queue                 */
#define KISMEM_FAT_NOTSUPP   0x10000103    /* Service not supported    */
#define KISMEM_FAT_BINSTALL  0x10000104    /* Can't install bus error  */
                                           /* handler                  */
#define KISMEM_FAT_NOD       0x10000105    /* Number of nodes > max    */
                                           /* nodes                    */

/*=====================================================================*/
/* Interface to Parallel Driver                                        */
/*=====================================================================*/
/* Errors returned by the parallel driver to the application           */
/*---------------------------------------------------------------------*/
#define   PAR_NINIT      0x10600400 /* Channel not initialized         */
#define   PAR_MINOR      0x10600401 /* Invalid minor number            */
#define   PAR_ADOPEN     0x10600402 /* Channel already opened          */
#define   PAR_OUTSYNC    0x10600403 /* Dependent and independent parts */
                                    /* of the driver out of sync       */
#define   PAR_SEM        0x10600404 /* Semaphore error                 */
#define   PAR_NBUFF      0x10600405 /* No buffers                      */
#define   PAR_NOPEN      0x10600406 /* Channel not opened              */
#define   PAR_NCONNECTED 0x10600407 /* Channel not connected           */
#define   PAR_TIMEOUT    0x10600408 /* Timer expired for read/write    */
#define   PAR_CFGERROR   0x10600409 /* Configuration error             */
#define   PAR_TXERROR    0x10600410 /* Transmission error              */
#define   PAR_NMBLK      0x10600411 /* No buffer headers               */
#define   PAR_MODEERR    0x10600412 /* Port mode error                 */
#define   PAR_CMDERR     0x10600413 /* Undefined command issued        */
#define   PAR_QUE        0x10600414 /* Could not create queue          */
#define   PAR_TXQFULL    0x10600415 /* Transmit queue is full          */
 
/*---------------------------------------------------------------------*/
/* Modes of operation of the port                                      */
/* COMPATIBLE_MODE is a forward direction mode. Data can be transferred*/
/* to peripheral only. BYTE_MODE is a reverse direction mode. Data can */
/* be transferred from the peripheral only. BLOCKING and NON_BLOCKING  */
/* decide whether write/read operation is blocking or non-blocking.    */
/* If BLOCKING/NON_BLOCKING is selected, the driver operates in        */
/* interrupt mode. POLLING can be selected if interrupts should not be */
/* used.                                                               */
/* If the application gives wrong data or 0, the port is opened in     */
/* COMPATIBLE_MODE, NON_BLOCKING.                                      */
/*---------------------------------------------------------------------*/
#define  COMPATIBLE_MODE         0x01
#define  BYTE_MODE               0x02
#define  BLOCKING                0x10
#define  NON_BLOCKING            0x20
#define  POLLING                 0x40
 
/*---------------------------------------------------------------------*/
/* Status information returned by driver to application (bit wise op)  */
/*---------------------------------------------------------------------*/
#define   DEVBUSY             0x00000001  /* Device busy               */
#define   DEVPAPEND           0x00000002  /* Paper end                 */
#define   DEVSLCT             0x00000004  /* Select signal             */

#define   DEVERR              0x00000008  /* Device error              */
 
/*---------------------------------------------------------------------*/
/* Function code values. These are the commands that the application   */
/* requests the driver to perform                                      */
/*---------------------------------------------------------------------*/
#define   PAUSE         0x00000001  /* Pause transmission              */
#define   RESUME        0x00000002  /* Resume transmission             */
#define   FLUSH         0x00000003  /* Flush the transmission queue    */
#define   GETSTATUS     0x00000004  /* Get status of the device        */
 
/*---------------------------------------------------------------------*/
/* Parallel driver configuration parameters                            */
/*---------------------------------------------------------------------*/
#define  RBUFFSIZE      32          /* Receive buffer size             */
#define  OUTQLEN         8          /* This indicates the number of    */
                                    /* frames that can be waiting for  */
                                    /* transmission. PAR_TXFULL error  */
                                    /* is returned to the application  */
                                    /* when this limit exceeds.        */
 
/*---------------------------------------------------------------------*/
/* Interface to parallel driver and application                        */
/*---------------------------------------------------------------------*/
typedef struct {
 
    /*-----------------------------------------------------------------*/
    /* Interface to de_open()                                          */
    /* mode - Mode in which the port is opened. The user can select    */
    /*        between COMPATIBLE_MODE or BYTE_MODE of operation and    */
    /*        whether write can be BLOCKING or NON_BLOCKING            */
    /*-----------------------------------------------------------------*/
    unsigned long mode;
 
    /*-----------------------------------------------------------------*/
    /* Interface to de_write()                                         */
    /* length - Number of bytes to be transmitted                      */
    /* buffp  - Pointer to the buffer containing data                  */
    /*-----------------------------------------------------------------*/
    unsigned long length;
    unsigned char *buffp;
 
    /*-----------------------------------------------------------------*/
    /* Interface to de_cntrl()                                         */
    /* function - The command which has to be executed by the driver   */
    /*            like, RESUME, FLUSH etc                              */
    /*-----------------------------------------------------------------*/
    unsigned long function;
 
}ParIopb;
 
#endif /* _DRV_INTF_H */

#if __cplusplus
}
#endif
