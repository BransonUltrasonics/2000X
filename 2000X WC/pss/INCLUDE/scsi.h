/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\scsi.h_v   1.0   Mar 29 1999 13:51:06   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/scsi.h 1.40 97/04/18 10:27:31 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/scsi.h                                           */
/*   DATE:    97/04/18                                                 */
/*   PURPOSE: General SCSI command definitions                         */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1997, Integrated Systems, Inc.           */
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

#ifndef _SCSI_H
#define _SCSI_H

/*---------------------------------------------------------------------*/
/* Must include bsp.h before this file To determine big/little endian  */
/*---------------------------------------------------------------------*/
#ifndef _BSP_H
    #error "Must include bsp.h before scsi.h"
#endif

/***********************************************************************/
/*   HOST_ID This will be the target id of the host controler          */
/*   (on board scsi controller) it is recommended that this be set     */
/*   to 7 giving the host controller the highest priority on the bus   */
/***********************************************************************/
#define HOST_ID         7            /* Controller ID                  */

#if BSP_LITTLE_ENDIAN
#define BITFIELD_LSB_FIRST 1
#endif

/***********************************************************************/
/* Values returned by scsi commands                                    */
/***********************************************************************/
#define STAT_OK        0x0
#define STAT_CHECKCOND 0x1           /* target wants to give some info */ 
#define STAT_ERR       0x2           /* SCSI error that may be retried */
#define STAT_TIMEOUT   0x3           /* Target selection timed out     */
#define STAT_BUSY      0x4           /* target busy try again          */
#define STAT_SEMFAIL   0x5           /* semaphore call failed          */ 
#define STAT_NOMEM     0x6           /* no memory available for request*/ 
#define STAT_RETRYEXC  0x7           /* Failed after alloted retries   */  
#define STAT_RESET     0x8           /* SCSI bus reset (should retry)  */
#define STAT_BADSIZE   0x9           /* Drive shows no blocks          */
#define STAT_NOMEDIA   0xA           /* Removeable disk not in drive   */
#define STAT_BLANK     0xB           /* end of recorded data           */
#define STAT_BAD_CMD   0xC           /* Target reports Illegal Request */
#define STAT_NO_SENSE  0xD           /* request sense returned no sense*/
#define STAT_GOT_SENSE 0xE           /* sense info returned (for chip  */
                                     /* doing automatically sense).    */

/***********************************************************************/
/* Structural definition of SCSI commands and data.                    */
/***********************************************************************/

/***********************************************************************/
/* Test Unit Ready  command --  All Devices                            */
/***********************************************************************/
#define TEST_UNIT_READY 0x00
#define TEST_UNIT_READY_DLEN 4
typedef struct test_unit_ready_c
    {
    unsigned char   code;
#ifdef BITFIELD_LSB_FIRST
    unsigned :5,      lun:3;
    unsigned char   res[3];
    unsigned link:1,  flag:1,  :4,   vu1:2;
#else
    unsigned lun:3,   :5;
    unsigned char   res[3];
    unsigned vu1:2,   :4,   flag:1,   link:1;
#endif
    } TEST_UNIT_READY_STRUCT;

/*---------------------------------------------------------------------*/
/* This command does not return any data, only status.                 */
/* If unit is ready it will return GOOD status. If not the target      */
/* will return a check condition with an extended sense key of NOT     */
/* Ready.                                                              */
/*---------------------------------------------------------------------*/
/***********************************************************************/
/* Read Capacity command -- DIRECT ACCESS DEVICES                      */
/***********************************************************************/
#define READ_CAPACITY 0x25
#define READ_CAPACITY_DLEN 10
typedef struct
    {
    unsigned char   code;

#ifdef BITFIELD_LSB_FIRST
    unsigned reladr: 1, :4, lun:3; 
    unsigned char   block[4]; 
    unsigned char   res[2];
    unsigned pmi:1,  :7; 
    unsigned link:1, flag:1, :4, vu:2;
#else
    unsigned lun:3, :4,
             reladr:1;              /* address reletive to last        */

    unsigned char   block[4];       /* start block to look for next    */
                                    /* delay block (must be 0 if pmi   */
                                    /* is 0                            */
    unsigned char   res[2];

    unsigned :7,    pmi:1;          /* partial medium indicator        */
    unsigned vu:2,  :4, flag:1, link:1;
#endif
    } CAPACITY_STRUCT;


/*---------------------------------------------------------------------*/
/* For little_endian machina, swapping is needed.                      */
/*---------------------------------------------------------------------*/
typedef struct
    {                               /* Returned data structure         */
    unsigned long   blocks;         /* Number of blocks on device      */
    unsigned long   bsize;          /* Size of blocks                  */
    } CAPACITY_RET_STRUCT;

/***********************************************************************/
/* Read Block Limits command -- Sequential ACCESS DEVICES              */
/***********************************************************************/
#define READ_BLOCK_LIMITS 0x05
#define READ_BLOCK_LIMITS_DLEN 6
typedef struct
    {
    unsigned char   code;
#ifdef BITFIELD_LSB_FIRST
    unsigned :5, lun:3;
    unsigned char   res[3];
    unsigned link:1, flag:1, :4, vu:2;
#else
    unsigned lun:3, :5;
    unsigned char   res[3];
    unsigned vu:2, :4, flag:1, link:1;
#endif
    } BLOCK_LIMITS_STRUCT;

/*---------------------------------------------------------------------*/
/* For little_endian machina, swapping is needed.                      */
/*---------------------------------------------------------------------*/
typedef struct
    {                               /* Returned data structure         */
    unsigned long    max_block_limit; /* Max size of a block           */
    unsigned short   min_block_length_limit; /* Min size of blocks     */
    } BLOCK_LIMITS_RET_STRUCT;

/***********************************************************************/
/* read command                                                        */
/***********************************************************************/
#ifdef READ
#undef READ
#endif
#define READ 0x08
#define READ_DLEN 6
typedef struct
    {
#ifdef BITFIELD_LSB_FIRST
    unsigned char    code;          /* Command number.                 */
    unsigned block_b2:5, lun:3; 
    unsigned char    block_b1; 
    unsigned char    block_b0; 
    unsigned char    blocks;        /* Blocks to read.                 */
    unsigned link:1, flag:1, :4, vu:2;
#else
    unsigned char    code;          /* Command number.                 */
    unsigned lun:3, block_b2:5; 
    unsigned char    block_b1;      /* block number.                   */
    unsigned char    block_b0;      /* block number.                   */
    unsigned char    blocks;        /* Blocks to read.                 */
    unsigned vu:2,                  /* Vendor unique                   */
             :4,
             flag:1,                /* Flag command bit.               */
             link:1;                /* Linked command bit.             */
#endif
    } READ_STRUCT;

/***********************************************************************/
/* write command                                                       */
/***********************************************************************/
#ifdef WRITE
#undef WRITE
#endif
#define WRITE 0x0A
#define WRITE_DLEN 6
typedef READ_STRUCT   WRITE_STRUCT;


/***********************************************************************/
/* read/write extended command structure                               */
/***********************************************************************/
#define R_W_EXT_DLEN 10
#define WRITE_EXT 0x2A
#define READ_EXT 0x28

typedef struct
    {                               /* extended read                   */
    unsigned char       code;       /* Command number.                 */

#ifdef BITFIELD_LSB_FIRST
    unsigned :5, lun:3;             /* logical Unit Number.            */
#else
    unsigned lun:3, :5;             /* logical Unit Number.            */
#endif
    unsigned char   block_b3;       /* msb byte of block addr          */
    unsigned char   block_b2; 
    unsigned char   block_b1; 
    unsigned char   block_b0;       /* lsb byte of block addr          */ 

    unsigned char        res;       /* reserved                        */
    unsigned char blocks_msb;       /* Blocks to write                 */
    unsigned char blocks_lsb;

#ifdef BITFIELD_LSB_FIRST
    unsigned link:1, flag:1, :4, vu:2; 
#else
    unsigned vu:2, :4, flag:1, link:1;       
#endif
                                    /* vu:  Vendor unique.             */
                                    /* flag: Flag command bit.         */
                                    /* link: Linked command bit.       */
  } RW_EXT_STRUCT;

/***********************************************************************/
/* read/write sequential command structure                             */
/***********************************************************************/
#define R_W_SEQ_DLEN 6

#ifdef	MRI
typedef packed struct
#endif
#ifdef  __DIAB
#pragma pack(1,1)
typedef struct
#endif
#ifdef	GHS
#pragma pack(1)
typedef struct
#endif
#ifdef _SDS
#pragma maxalign(1)
typedef struct
#endif
#ifdef __CADUL__
#pragma align (s_rw_seq_struct = 1)
typedef struct s_rw_seq_struct
#endif
    {                               /* sequential read/write           */
    unsigned code:8;                /* Command number.                 */

#ifdef BITFIELD_LSB_FIRST
    unsigned fixed:1, sili:1, :3,  lun:3;
    unsigned char    blocks_msb;    /* 24 bits of transfer length      */
    unsigned char    blocks_mid;    /* 24 bits of transfer length      */
    unsigned char    blocks_lsb;    /* 24 bits of transfer length      */
    unsigned link:1,flag:1, :4, vu:2;
#else
    unsigned lun:3,                 /* logical Unit Number.            */
             :3,
             sili:1,                /* SILI                            */
             fixed:1;               /* Fixed                           */
    unsigned char    blocks_msb;    /* 24 bits of transfer length      */
    unsigned char    blocks_mid;    /* 24 bits of transfer length      */
    unsigned char    blocks_lsb;    /* 24 bits of transfer length      */
    unsigned vu:2,                  /* Vendor unique.                  */
             :4,
             flag:1,                /* Flag command bit.               */
             link:1;                /* Linked command bit.             */
#endif
    }RW_SEQ_STRUCT;
#ifdef  __DIAB
#pragma pack(0,0)
#endif
#ifdef	GHS
#pragma pack()
#endif
#ifdef _SDS
#pragma maxalign()
#endif

/***********************************************************************/
/* Inquiry command -- COMMON FOR ALL DEVICES                           */
/***********************************************************************/
#define INQUIRY 0x12
#define INQUIRY_DLEN 0x6
typedef struct
    {
    unsigned char code;

#ifdef BITFIELD_LSB_FIRST
    unsigned :5, lun:3;
    unsigned char  res[2];
    unsigned char  dlen;
    unsigned link:1, flag:1, :4, vu:2;
#else
    unsigned lun:3, :5;
    unsigned char  res[2];
    unsigned char  dlen;
    unsigned vu:2, :4, flag:1, link:1;
#endif
    } INQUIRY_STRUCT;


typedef struct
    {                               /* Common returned data header     */
    unsigned char device;           /* Device type code.               */

#ifdef BITFIELD_LSB_FIRST
    unsigned 
        qualifier:7,                /* Device type qualifier.          */
        rmb:1;                      /* Removeable media.               */
    unsigned 
        ansivers:3,                 /* ANSI version.                   */
        ecmavers:3,                 /* ECMA version.                   */
        isiovers:2;                 /* ISO version.                    */
    unsigned 
        format:4,                   /* Response format.                */
        :4;                         /* Reserved                        */

    unsigned char length;           /* Additional Data length.         */
    unsigned :8;                    /* Reserved                        */
    unsigned :8;                    /* Reserved                        */

    unsigned 
        stffre:1,                   /* support for soft reset alter   */
        cmdque:1,                   /* support for command queuing    */
        res:1,                      /* reserved                       */
        linked:1,                   /* support for linked commands    */
        sync:1,                     /* support for synchronous trans  */
        wbus16:1,                   /* support for 16 bit wide scsi   */
        wbus32:1,                   /* support for 32 bit wide scsi   */
        reladr:1;                   /* support for relative address   */
#else
    unsigned 
        rmb:1,                      /* Removeable media.               */
        qualifier:7;                /* Device type qualifier.          */
    unsigned 
        isiovers:2,                 /* ISO version.                    */
        ecmavers:3,                 /* ECMA version.                   */
        ansivers:3;                 /* ANSI version.                   */
    unsigned 
        :4,                         /* Reserved                        */
        format:4;                   /* Response format.                */
    unsigned char length;           /* Additional Data length.         */
    unsigned :8;                    /* Reserved                        */
    unsigned :8;                    /* Reserved                        */

    unsigned 
                  reladr:1,         /* support for relative address   */
                  wbus32:1,         /* support for 32 bit wide scsi   */
                  wbus16:1,         /* support for 16 bit wide scsi   */
                  sync:1,           /* support for synchronous trans  */
                  linked:1,         /* support for linked commands    */
                  res:1,            /* reserved                       */
                  cmdque:1,         /* support for command queuing    */
                  stffre:1;         /* support for soft reset alter   */
#endif
    unsigned char vendor[8];        /* Vendor identification.          */
    unsigned char product[16];      /* Product identification          */
    unsigned char revision[4];      /* Revision level.                 */
} INQUIRY_RET_STRUCT;


/*---------------------------------------------------------------------*/
/* Device type codes.                                                  */
/*---------------------------------------------------------------------*/

#define TYPE_DIRECT      0x00       /* direct access (disk)            */
#define TYPE_SEQUENTIAL  0x01       /* sequential access (tape)        */
#define TYPE_PRINTER     0x02       /* printer                         */
#define TYPE_PROCESSOR   0x03       /* processor board                 */
#define TYPE_WORM        0x04       /* write once (optical disk)       */
#define TYPE_CDROM       0x05       /* cd rom                          */
#define TYPE_SCANNER     0x06       /* scanner                         */
#define TYPE_OMEM        0x07       /* optical memory (some disks)     */
#define TYPE_CHANGER     0x08       /* medium changer (jukeboxes)      */
#define TYPE_COMM        0x09       /* communication device            */
#define TYPE_UNKNOWN     0x1F       /* unknown device type             */
#define TYPE_HOST        0xFF       /* target id of host system        */

/***********************************************************************/
/* Format command --                                                   */
/***********************************************************************/
#define FORMAT 0x04
#define FORMAT_DLEN 0x6
typedef struct
    {
    unsigned code:8;                /* Command number                  */

#ifdef BITFIELD_LSB_FIRST
    unsigned dfmt:3, clist:1, fmtdat:1, lun:3;
    unsigned char  pat;             /* Pattern to write to disk        */
    unsigned char  ileave[2];       /* Interleave factor               */
    unsigned link:1, flag:1, :4, vu:2;
#else
    unsigned    lun:3,             /* Logical unit number             */
                fmtdat:1,          /* Format data provided            */
                clist:1,           /* Complete list provided          */
                dfmt:3;            /* Defects provide                 */

    unsigned char  pat;             /* Pattern to write to disk        */
    unsigned char  ileave[2];       /* Interleave factor               */

    unsigned vu:2, :4,              /* Vendor unique                   */
                 flag:1,            /* Flagged command                 */
                 link:1;            /* Linked command                  */
#endif
    } FORMAT_STRUCT;

/***********************************************************************/
/* Prevent/Allow Medium Removal -- Removable devices                   */
/***********************************************************************/
#define PREVENT_ALLOW_MEDIUM_REMOVAL 0x1E
#define PREVENT_ALLOW_MEDIUM_REMOVAL_DLEN 6
 
typedef struct
    {
    unsigned char       code;
#ifdef BITFIELD_LSB_FIRST
    unsigned :5, lun :3;
    unsigned char       reserved[2];
    unsigned prevent:1, :7;
    unsigned link:1, flag:1, :4, vu:2;
#else
    unsigned lun     :3,
                     :5;
    unsigned char       reserved[2];
    unsigned :7, 
                        prevent :1;     /* 0 - allowed 1 - prevented   */
    unsigned vu      :2,
                     :4,
                     flag    :1,
                     link    :1;
#endif
    } PREVENT_ALLOW_MEDIUM_REMOVAL_STRUCT;
 
/***********************************************************************/
/* Start/Stop Unit                                                     */
/***********************************************************************/
#define START_STOP_UNIT 0x1B
#define START_STOP_DLEN 6
typedef struct
    {
    unsigned char       code;
#ifdef BITFIELD_LSB_FIRST
    unsigned immediate:1, :4, lun:3;
    unsigned char       reserved[2];
    unsigned start:1, load_eject:1, :6;
    unsigned link:1, flag:1, :4, vu:2;
#else
    unsigned lun     :3,
                     :4,
                     immediate:1;     /* 0 - wait for operation     */
                                      /* 1 - return w/o waiting     */
    unsigned char       reserved[2];
    unsigned       :6,
                   load_eject:1,     /* These two form one command  */
                   start   :1;       /* 01 - Start spindle          */
                                     /* 00 - Stop  spindle          */
                                     /* 11 - Load medium            */
                                     /* 10 - Stop and eject medium  */
    unsigned vu      :2,
                     :4,
                     flag    :1,
                     link    :1;
#endif
    } START_STOP_UNIT_STRUCT;

/***********************************************************************/
/* Mode Select command --                                              */
/***********************************************************************/
#define MODE_SELECT 0x15
#define MODE_SELECT_DLEN 0x6
typedef struct
    {
    unsigned char code;             /* Command number.                 */

#ifdef BITFIELD_LSB_FIRST
    unsigned sp:1, :3, pf:1, lun:3;  
    unsigned char res[2];         /* Reserved                        */
    unsigned char dlen;           /* Parameter List Length           */
    unsigned link:1, flag:1, :4, vu:2;
#else
    unsigned      lun:3,          /* Logical Unit Number.            */
                   pf:1,          /* Page Format.                    */
                     :3,          /* Reserved                        */
                   sp:1;          /* Save Parameters.                */

    unsigned char res[2];         /* Reserved                        */
    unsigned char dlen;           /* Parameter List Length           */

    unsigned        vu:2,          /* Vendor unique                   */
                      :4,          /* Reserved                        */
                  flag:1,          /* Flag command bit.               */
                  link:1;          /* Linked command bit.             */
#endif
    } MODE_SELECT_STRUCT;

/***********************************************************************/
/* Mode Sense Command -- COMMON TO MOST DEVICES                        */
/***********************************************************************/
#define MODE_SENSE 0x1A
#define MODE_SENSE_DLEN 0x06
typedef struct
    {
    unsigned char code;             /* Command number.                 */

#ifdef BITFIELD_LSB_FIRST
    unsigned :5, lun:3;            /* Logical Unit Number.            */
    unsigned page:6, pcf:2;        /* Page code & control field.      */
    unsigned char  rsv1; 
    unsigned char  dlen;           /* Bytes alloc. for data.          */
    unsigned link:1, flag:1, :4, vu:2;
#else
    unsigned lun    :3,            /* Logical Unit Number.            */
                    :5;            /* Reserved                        */
    unsigned pcf:2,                /* Page control field.             */
                   page:6;         /* Page code.                      */
    unsigned char  rsv1; 
    unsigned char  dlen;           /* Bytes alloc. for data.          */
    unsigned vu:2, :4, flag:1, link:1;
#endif
    } MODE_SENSE_STRUCT;

/*---------------------------------------------------------------------*/
/* Mode sense page control field options.                              */
/*---------------------------------------------------------------------*/

#define CURRENT    0
#define CHANGEABLE 1
#define DEFAULT    2
#define SAVED      3

/***********************************************************************/
/* Mode Sense/Select page formats                                      */
/***********************************************************************/

#ifdef	MRI
typedef packed struct
#endif
#ifdef  __DIAB
#pragma pack(1,1)
typedef struct
#endif
#ifdef	GHS
#pragma pack(1)
typedef struct
#endif
#ifdef _SDS
#pragma maxalign(1)
typedef struct
#endif
#ifdef __CADUL__
#pragma align (s_tape_mode_select_hd = 1)
typedef struct s_tape_mode_select_hd
#endif
    {
    unsigned char res[2]; 

#ifdef BITFIELD_LSB_FIRST
    unsigned speed:4, buffered_mode:3, RSVD:1;
#else
    unsigned RSVD:1, buffered_mode:3, speed:4;
#endif
    unsigned char bdl;             /* Block Descriptor Length always 8*/
    unsigned char density_code;    /* 0x00 default no error checking  */
    unsigned char number_of_blocks[3]; /* not used in select */
    unsigned char res2;
    unsigned char block_length[3];    /* 0 variable or # of fixed bytes  */
    } TAPE_MODE_SELECT_HD;
#ifdef  __DIAB
#pragma pack(0,0)
#endif
#ifdef	GHS
#pragma pack()
#endif
#ifdef _SDS
#pragma maxalign()
#endif

/*---------------------------------------------------------------------*/
/* Mode Header used for Sequential access devices (Tape Drives)        */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* modeheader used for vendor specific floppy type for teac FC1        */
/*---------------------------------------------------------------------*/
struct header_descriptor
{
    unsigned char reserved0;
    unsigned char medium_type;
    unsigned char reserved1;
    unsigned char blk_descriptor_len;
    unsigned char density_code;
    unsigned char msb_blocks;        /* # of logical blocks 0x00 - all */
    unsigned char midsb_blocks;
    unsigned char lsb_blocks;
    unsigned char reserved2;
    unsigned char msb_blklen;        /* block lenght for medium        */
    unsigned char midsb_blklen;
    unsigned char lsb_blklen;
};

/*---------------------------------------------------------------------*/
/* Read-Write Error Recovery Page                                      */
/*   recovery_time has to be swpped if little endian machine.          */
/*---------------------------------------------------------------------*/
#define RW_ERROR_RECOVERY_PC 0x01
#define RW_ERROR_RECOVERY_DLEN 12
typedef struct
    {
#ifdef BITFIELD_LSB_FIRST
    unsigned page_code:6, :1, ps:1;
    unsigned char page_length; 
    unsigned dcr:1, dte:1,  per:1,  err:1, 
             rc:1,  tb:1,   arre:1, awre:1;

#else
    unsigned        ps:1,           /* Page saveable mode sense only   */
                     :1,            /* Reserved                        */
             page_code:6;           /* Page code (0x01)                */
    unsigned char page_length;      /* Additional page length          */
    unsigned awre:1,                /* Auto write reallocation enable  */
          arre:1,                   /* Auto read reallocation enable   */
            tb:1,                   /* Transfer Block (on error)       */
            rc:1,                   /* Read continuous                 */
           err:1,                   /* Enable early recovery           */
           per:1,                   /* Post error (of recovered err)   */
           dte:1,                   /* disable transfer on error       */
           dcr:1;                   /* disable correction              */
#endif
    unsigned char retry_count;      /* times to retry operation        */
    unsigned char correction_span;  /* max size of correction area     */
    unsigned char head_offset;      /* head position after err rec     */
    unsigned char data_strobe_offset; /* data strobe position after err*/
    unsigned :8;                    /* Reserved                        */
    unsigned char write_retry_count;/* Max retries to write data       */
    unsigned :8;                    /* Reserved                        */
    unsigned short recovery_time;   /* milliseconds max recovery time  */
    } RW_ERROR_RECOVERY_STRUCT;

/*---------------------------------------------------------------------*/
/* Disconnect-Reconnect page                                           */
/*  all SHORT-results have to be swapped if little endian machine.     */
/*---------------------------------------------------------------------*/
#define DISCONNECT_RECONNECT_PC 0x02
#define DISCONNECT_RECONNECT_DLEN 16
typedef struct
    {
#ifdef BITFIELD_LSB_FIRST
    unsigned page_code:6, :1,  ps:1;
#else
    unsigned           ps:1,        /* Page saveable mode sense only   */
                         :1,        /* Reserved                        */
                page_code:6;        /* Page code (0x02)                */
#endif
    unsigned char page_length;      /* Additional page length          */
    unsigned char buf_full_ratio;   /* min in buf before reselection   */
                                    /* on read operation               */
    unsigned char buf_empty_ratio;  /* min in buf before reselection   */
                                    /* on write operation              */
    unsigned short bus_inactive_lim;/* disconnect after no activity    */
    unsigned short disconnect_time_lim;/* min time to wait to reselect */
                                    /* after disconnect                */
    unsigned short connect_time_lim;/* max time bus may be used        */
                                    /* before target must disconnect   */
    unsigned short max_burst_size;  /* max data transfered by target   */
                                    /* before target must disconnect   */
#ifdef BITFIELD_LSB_FIRST
    unsigned dtdc:2, :6;
#else
    unsigned      :6,  dtdc:2;      /* Data transfer disconnect cont   */
#endif
    unsigned char res[3];           /* Reserved                        */
    } DISCONNECT_RECONNECT_STRUCT;

#define DTDC_OFF 0x00               /* dtdc not used used other        */
                                    /* fields in this page as control  */
#define DTDC_ON_DATA 0x01           /* disconnect only after all       */
                                    /* data is sent                    */
#define DTDC_ON_CMD 0x03            /* disconnect only command         */
                                    /* complete                        */
/*---------------------------------------------------------------------*/
/* Format Device page                                                  */
/*  all SHORT-results have to be swapped if little endian machine.     */
/*---------------------------------------------------------------------*/
#define FORMAT_DEVICE_PC 0x03
#define FORMAT_DEVICE_DLEN 24
typedef struct
    {
#ifdef BITFIELD_LSB_FIRST
    unsigned page_code:6, :1,  ps:1;
#else
    unsigned           ps:1,        /* Page saveable mode sense only   */
                         :1,        /* Reserved                        */
                page_code:6;        /* Page code (0x03)                */
#endif
    unsigned char  page_length;     /* Additional page length          */
    unsigned short tracks_per_zone;
    unsigned short alternate_sec_per_zone;
    unsigned short alternate_tracks_per_zone;
    unsigned short alternate_tracks_per_lun;
    unsigned short sec_per_track;
    unsigned short bytes_per_sec;
    unsigned short interleave;
    unsigned short track_skew;
    unsigned short cylinder_skew;
#ifdef BITFIELD_LSB_FIRST
    unsigned :4, surf:1, rmb:1, hsec:1, ssec:1;
#else
    unsigned ssec:1,                /* soft sector format              */
          hsec:1,                   /* hard sector format              */
           rmb:1,                   /* removable media                 */
          surf:1,                   /* serface block allocation        */
              :4;                   /* Reserved                        */
#endif
    unsigned short res;
    } FORMAT_DEVICE_STRUCT;

/*---------------------------------------------------------------------*/
/* Rigid disk drive geometry page                                      */
/*---------------------------------------------------------------------*/
#define RDD_GEOMETRY_PC 0x04
#define RDD_GEOMETRY_DLEN 24
typedef struct
    {
#ifdef BITFIELD_LSB_FIRST
    unsigned page_code:6, :1, ps:1;
#else
    unsigned           ps:1,        /* Page saveable mode sense only   */
                         :1,        /* Reserved                        */
                page_code:6;        /* Page code (0x04)                */
#endif
    unsigned char page_length;      /* Additional page length          */
    unsigned short cylinders;
    unsigned char heads;
    unsigned short scwp;
    unsigned short scrwc;
    unsigned short drive_step_rate;
    unsigned short landing_zone_cyl;
#ifdef BITFIELD_LSB_FIRST
    unsigned rpl:2, :6;
#else
    unsigned :6, rpl:2;
#endif
    unsigned char rotational_offset;
    unsigned :8;
    unsigned char medium_rotation_rate;
    unsigned :8;
    unsigned :8;
    } RDD_GEOMETRY_STRUCT;

/*---------------------------------------------------------------------*/
/* Flexible disk page                                                  */
/*---------------------------------------------------------------------*/
#define FLEX_DISK_PC 0x05
#define FLEX_DISK_DLEN 32
typedef struct
    {
#ifdef BITFIELD_LSB_FIRST
    unsigned page_code:6, :1, ps:1;
#else
    unsigned           ps:1,        /* Page saveable mode sense only   */
                         :1,        /* Reserved                        */
                page_code:6;        /* Page code (0x05)                */
#endif
    unsigned char page_length;      /* Additional page length          */
    unsigned short transfer_rate;
    unsigned char heads;
    unsigned char sec_per_track;
    unsigned short bytes_per_sec;
    unsigned short cylinders;
    unsigned short scwp;
    unsigned short scrwc;
    unsigned short drive_step_rate;
    unsigned char drive_step_pulse_width;
    unsigned short head_settle_delay;
    unsigned char motor_on_delay;
    unsigned char motor_off_delay;
#ifdef BITFIELD_LSB_FIRST
    unsigned :5, mo:1, ssn:1, trdy:1;
    unsigned :4, spc:4; 
    unsigned char write_compensation;
    unsigned char head_load_delay;
    unsigned char head_unload_delay;
    unsigned pin2:4, pin34:4;
    unsigned pin1:4, pin4:4;
#else
    unsigned trdy:1,
           ssn:1,
            mo:1,
              :5;
    unsigned :4,
           spc:4;
    unsigned char write_compensation;
    unsigned char head_load_delay;
    unsigned char head_unload_delay;
    unsigned pin34:4, pin2:4;
    unsigned pin4:4,  pin1:4;
#endif
    unsigned short min_rotatinal_rate;
    unsigned short res;
    } FLEX_DISK_STRUCT;


#define TR250 0x00FA                /* transfer rates                  */
#define TR300 0x012C
#define TR500 0x01F4
#define TR1MEG 0x03E8
#define TR2MEG 0x07D0
#define TR5MEG 0x1388
/*---------------------------------------------------------------------*/
/* Verify error recovery page                                          */
/*---------------------------------------------------------------------*/
#define VERIFY_RECOVERY_PC 0x07
#define VERIFY_RECOVERY_DLEN 12
typedef struct
    {
#ifdef BITFIELD_LSB_FIRST
    unsigned page_code:6, :1, ps:1;
    unsigned char page_length;      /* Additional page length          */
    unsigned dcr:1, dte:1, per:1, err:1, :4;
#else
    unsigned ps:1,                  /* Page saveable mode sense only   */
                         :1,        /* Reserved                        */
                page_code:6;        /* Page code (0x07)                */
    unsigned char page_length;      /* Additional page length          */
    unsigned :4,
          err:1,
          per:1,
          dte:1,
          dcr:1;
#endif
    unsigned char retry_count;
    unsigned char correction_span;
    unsigned char res[5];
    unsigned short recovery_time;
    } VERIFY_RECOVERY_STRUCT;

/*---------------------------------------------------------------------*/
/* Control Mode Page   (SCSI 2)                                        */
/*---------------------------------------------------------------------*/
#define CONTROL_MODE_PC 0x0A
#define CONTROL_MODE_DLEN 8
typedef struct
    {
#ifdef BITFIELD_LSB_FIRST
    unsigned page_code:6, :1, ps:1;
    unsigned char page_length;      /* Additional page length          */
    unsigned relc:2, :6;            /* Reserved                        */
    unsigned disable_que:1, qem:1, :2, qam:4;
    unsigned eaenp:1, uaaenp:1, raenp:1, :4, eeca:1;

#else
    unsigned           ps:1,        /* Page saveable mode sense only   */
                         :1,        /* Reserved                        */
                page_code:6;        /* Page code (0x0A)                */
    unsigned char page_length;      /* Additional page length          */
    unsigned :6,                    /* Reserved                        */
                  relc:2;           /* report log exception condition  */
    unsigned      qam:4,            /* queue algorirhm modifier        */
                     :2,            /* Reserved                        */
                  qem:1,            /* queue error management          */
          disable_que:1;
    unsigned       eeca:1,          /* enable extended contingent      */
                                    /* allegiance                      */
                       :4,          /* Reserved                        */
                  raenp:1,          /* asynchronous event              */
                                    /* notification                    */
                 uaaenp:1,          /* unit attention permission       */
                  eaenp:1;          /* report defered error condition  */
#endif
    unsigned :8;                    /* Reserved                        */
    unsigned short ready_holdoff;
    } CONTROL_MODE_STRUCT;

/***********************************************************************/
/* Request Sense command -- COMMON TO ALL DEVICES                      */
/***********************************************************************/
#define REQUEST_SENSE 0x03
#define REQUEST_SENSE_DLEN 0x06
typedef struct
    {
    unsigned char code;             /* Command number                  */
#ifdef BITFIELD_LSB_FIRST
    unsigned :5, lun:3;             /* Logical unit number             */
    unsigned char res[2];           /* Reserved                        */
    unsigned char dlen;             /* Data length to return           */
    unsigned link:1, flag:1, :4, vu:2; 
#else
    unsigned lun:3,                 /* Logical unit number             */
               :5;                  /* Reserved                        */
    unsigned char res[2];           /* Reserved                        */
    unsigned char dlen;             /* Data length to return           */
    unsigned vu:2,                  /* Vendor unique.                  */
               :4,                  /* Reserved                        */
           flag:1,                  /* Flagged command.                */
           link:1;                  /* Linked command.                 */
#endif
    } REQUEST_SENSE_STRUCT;


typedef struct {

#ifdef BITFIELD_LSB_FIRST
    unsigned code:4, sclass:3, valid:1;
    unsigned char segment;
    unsigned sensekey:4, :1, ili:1, eom:1, fmark:1;
#else
    unsigned 
        valid:1,
        sclass:3,
        code:4;
    unsigned char segment;
    unsigned fmark:1, eom:1, ili:1, :1, sensekey:4;
#endif

    unsigned char info[4];
    unsigned char more;
    unsigned char res1[4];
    unsigned char sensecode;        /* additional sense code           */
    unsigned char sensequalifer;    /* additional semse code qualifier*/
    unsigned char fru;

#ifdef BITFIELD_LSB_FIRST
    unsigned bptr:3, bpv:1, :2, cd:1, fpv:1;
#else
    unsigned fpv:1, cd:1, :2, bpv:1, bptr:3;
#endif

    }REQUEST_SENSE_RET_STRUCT;


/***********************************************************************/
/* Write Filemarks                                                     */
/***********************************************************************/
#define WRITE_FILEMARKS 0x10
#define WRITE_FILEMARKS_DLEN 6
 
#ifdef	MRI
typedef packed struct
#endif
#ifdef  __DIAB
#pragma pack(1,1)
typedef struct
#endif
#ifdef	GHS
#pragma pack(1)
typedef struct
#endif
#ifdef _SDS
#pragma maxalign(1)
typedef struct
#endif
#ifdef __CADUL__
#pragma align (s_write_filemarks_struct = 1)
typedef struct s_write_filemarks_struct
#endif
    {
    unsigned char       code;

#ifdef BITFIELD_LSB_FIRST
    unsigned immed:1, wsmk:1, :3, lun:3;
    unsigned char       marks_msb;
    unsigned char       marks_mid;
    unsigned char       marks_lsb;
    unsigned link:1, flag:1, :4, vu:2;
#else
    unsigned lun:3, :3, wsmk:1, immed:1;
    unsigned char       marks_msb;
    unsigned char       marks_mid;
    unsigned char       marks_lsb;
    unsigned vu:2, :4, flag:1, link:1;
#endif
    } WRITE_FILEMARKS_STRUCT;
#ifdef  __DIAB
#pragma pack(0,0)
#endif
#ifdef	GHS
#pragma pack()
#endif
#ifdef _SDS
#pragma maxalign()
#endif

/***********************************************************************/
/* Rewind                                                              */
/***********************************************************************/
#define REWIND 0x01
#define REWIND_DLEN 6
 
#ifdef	MRI
typedef packed struct
#endif
#ifdef  __DIAB
#pragma pack(1,1)
typedef struct
#endif
#ifdef	GHS
#pragma pack(1)
typedef struct
#endif
#ifdef _SDS
#pragma maxalign(1)
typedef struct
#endif
#ifdef __CADUL__
#pragma align (s_rewind_struct = 1)
typedef struct s_rewind_struct
#endif
    {
    unsigned char       code;
#ifdef BITFIELD_LSB_FIRST
    unsigned immed:1, :4, lun:3;
    unsigned char       reserved[3];
    unsigned link:1,  flag:1,  :4,  vu:2; 
#else
    unsigned lun:3, :4, immed:1;
    unsigned char       reserved[3];
    unsigned vu:2, :4, flag:1, link:1;
#endif
    } REWIND_STRUCT;
#ifdef  __DIAB
#pragma pack(0,0)
#endif
#ifdef	GHS
#pragma pack()
#endif
#ifdef _SDS
#pragma maxalign()
#endif

/***********************************************************************/
/* Unload                                                              */
/***********************************************************************/
#define UNLOAD 0x1B
#define UNLOAD_DLEN 6
 
#ifdef	MRI
typedef packed struct
#endif
#ifdef  __DIAB
#pragma pack(1,1)
typedef struct
#endif
#ifdef	GHS
#pragma pack(1)
typedef struct
#endif
#ifdef _SDS
#pragma maxalign(1)
typedef struct
#endif
#ifdef __CADUL__
#pragma align (s_unload_struct = 1)
typedef struct s_unload_struct
#endif
    {
    unsigned char       code;
#ifdef BITFIELD_LSB_FIRST
    unsigned immed:1, :4,  lun:3;
    unsigned char       reserved[2];
    unsigned load:1, reten:1, eot:1, :5;
    unsigned link:1, flag:1,  :4,  vu:2;
#else
    unsigned lun:3, :4, immed:1;
     unsigned char      reserved[2];
    unsigned :5,
                             eot:1,
                           reten:1,
                            load:1;   
    unsigned vu:2, :4, flag:1, link:1;
#endif
    } UNLOAD_STRUCT;
#ifdef  __DIAB
#pragma pack(0,0)
#endif
#ifdef	GHS
#pragma pack()
#endif
#ifdef _SDS
#pragma maxalign()
#endif


/***********************************************************************/
/* Erase                                                               */
/***********************************************************************/
#define ERASE 0x19
#define ERASE_DLEN 6
 
typedef struct
    {
    unsigned char       code;
#ifdef BITFIELD_LSB_FIRST
    unsigned elong:1, immed:1, :3,  lun:3;
    unsigned char       reserved[3];
    unsigned link:1, flag:1,  :4,  vu:2;
#else
    unsigned lun     :3,
                                :3,
                        immed   :1,
                        elong   :1;
    unsigned char       reserved[3];
    unsigned vu:2, :4, flag:1, link:1;
#endif
    } ERASE_STRUCT;

/***********************************************************************/
/* SPACE                                                               */
/***********************************************************************/
#define SPACE 0x11
#define SPACE_DLEN 6

#ifdef	MRI
typedef packed struct
#endif
#ifdef  __DIAB
#pragma pack(1,1)
typedef struct
#endif
#ifdef	GHS
#pragma pack(1)
typedef struct
#endif
#ifdef _SDS
#pragma maxalign(1)
typedef struct
#endif
#ifdef __CADUL__
#pragma align (s_space_struct = 1)
typedef struct s_space_struct
#endif
    {
    unsigned char       code;
#ifdef BITFIELD_LSB_FIRST
    unsigned space:3,  :2,  lun  :3;
    unsigned char       count_msb; 
    unsigned char       count_mid; 
    unsigned char       count_lsb; 
    unsigned link:1, flag:1,  :4,  vu:2;
#else
    unsigned lun     :3,
                                :2,
                        space   :3;
    unsigned char       count_msb; 
    unsigned char       count_mid; 
    unsigned char       count_lsb; 
    unsigned vu:2, :4, flag:1, link:1;
#endif
    } SPACE_STRUCT;
#ifdef  __DIAB
#pragma pack(0,0)
#endif
#ifdef	GHS
#pragma pack()
#endif
#ifdef _SDS
#pragma maxalign()
#endif



/***********************************************************************/
/* Message codes.                                                      */
/***********************************************************************/

#define MSG_COMPLETE     0x00
#define MSG_EXTENDED     0x01
#define MSG_SAVE_DPTR    0x02
#define MSG_RESTORE_PTRS 0x03
#define MSG_DISCONNECT   0x04
#define MSG_ERROR        0x05
#define MSG_ABORT        0x06
#define MSG_REJECT       0x07
#define MSG_NOP          0x08
#define MSG_PARITY       0x09
#define MSG_LINK         0x0a
#define MSG_FLAG         0x0b
#define MSG_RESET        0x0c
#define MSG_SQTAG        0x20
#define MSG_IDENTIFY     0x80
#define MSG_IDENTIFY_D   0xC0        /* IDENTIFY + allow disconnect    */

/***********************************************************************/
/* Extended message codes.                                             */
/***********************************************************************/

#define EMSG_MODIFY  0x00            /* Modify data pointer            */
#define EMSG_SYNCH   0x01            /* Syncronous data transfer req   */
#define EMSG_IDENT   0x02            /* Extended idenify SCSI 1        */
#define EMSG_WDTR    0x03            /* Wide Data Transfer req         */

/***********************************************************************/
/* extended message offset values                                      */
/***********************************************************************/
#define EOFF_XMSG       0x00         /* "extended message" message     */
#define EOFF_LENGTH     0x01         /* # of bytes remaining in msg    */
#define EOFF_CODE       0x02         /* extended message code i.e. SDTR*/
#define EOFF_WIDTH      0x03         /* WDTR transfer width            */
#define EOFF_PERIOD     0x03         /* SDTR transfer period           */
#define EOFF_OFFSET     0x04         /* SDTR req/ack offset            */

/***********************************************************************/
/* Sense Key codes.                                                    */
/***********************************************************************/
#define NO_SENSE         0x00
#define RECOVERED_ERROR  0x01
#define NOT_READY        0x02
#define MEDIUM_ERROR     0x03
#define HARDWARE_ERROR   0x04
#define ILLEGAL_REQUEST  0x05
#define UNIT_ATTENTION   0x06
#define DATA_PROTECT     0x07
#define BLANK_CHECK      0x08
#define VENDOR_CODE      0x09
#define COPY_ABORTED     0x0A
#define ABORTED_COMMAND  0x0B
#define EQUAL            0x0C
#define VOLUME_OVERFLOW  0x0D
#define MISCOMPARE       0x0E
/***********************************************************************/
/* Device interface structure                                          */
/***********************************************************************/
#define STATLEN 4                   /* allow 4 bytes of status         */
#define MAXMSG 8                    /* max size of a message           */
#define capacity sizes.cap
#define limits   sizes.lim

typedef struct
    {
    volatile unsigned int flags;    /* status flags                    */
    volatile unsigned int state;    /* state of target                 */
    unsigned char open;             /* count of number of users.       */
    unsigned char loaded;           /* medium is loaded flag.          */
    unsigned char rewind;           /* opened with rewind.             */
    unsigned char exclusive;        /* opened exclusively for 1 user.  */
    unsigned long st_access_id;     /* command access semaphore ID     */
    unsigned long st_cont_id;       /* command continue semaphore ID   */
    unsigned char id;               /* device ID                       */
    unsigned char lun;              /* logical unit number             */
    unsigned char bus_width;        /* SCSI bus width                  */
    unsigned char resev0;           /* reserved  (make long alignment) */
    unsigned long block_size;       /* Tape block size                 */
    char *trans_blk;                /* pointer to transaction block    */
    union
        {
        CAPACITY_RET_STRUCT cap;    /* capacity of disk drive          */
        BLOCK_LIMITS_RET_STRUCT lim;/* limits of tape device           */
        } sizes;
    INQUIRY_RET_STRUCT  inquiry;    /* inquiry information             */
    REQUEST_SENSE_RET_STRUCT sense; /* sense info valid on error only  */
    PARTITION_INFO partition[SCSI_MAX_PART]; /* MSDOS partition info.  */
    } TARGET_DEV;

/*---------------------------------------------------------------------*/
/* TARGET_DEV flag bits                                                */
/*---------------------------------------------------------------------*/
#define ABORT_OPERATION 0x000001    /* Operation to be aborted         */
#define RESET_DEVICE    0x000002    /* Device to be reset              */
#define WIDE_SUPPORT    0x000004    /* Device supports wide xfers      */
#define WIDE_INITIATE   0x000008    /* Tells low level to request wide */
#define WIDE_DISABLE    0x000010    /* Low level disable WIDE because  */
                                    /* of PARITY error.                */
#define SYNC_REJECT     0x000020    /* Target rejected sync request    */
#define WIDE_REJECT     0x000040    /* Target rejected wide request    */
#define DISC_SUPPORT    0x000100    /* Device disconnect support       */
#define SYNC_SUPPORT    0x000200    /* Device supports sync xfers      */
#define SYNC_INITIATE   0x000400    /* Tells low level to request sync */
#define IDENT_SUPPORT   0x000800    /* Identify msg supported          */
#define ERROR           0x001000    /* Device Error occured            */
#define DISCONNECT      0x002000    /* Device disconnect received      */
#define WRITE_PROTECT   0x004000    /* Device is write protected       */
#define TAPE_BLOCK_MODE 0x008000    /* Mode for tape transfer          */
#define IN_USE          0x010000    /* Command block is in use         */
#define INQUIRED        0x020000    /* Inquiry completed               */
#define CAPACITY        0x040000    /* Capacity completed              */
#define LIMITS          0x040000    /* Limits completed                */
#define CONTROLLER      0x080000    /* SCSI bus controller             */
#define REQSENSE        0x100000    /* Request Sense being performed   */
#define NO_DEVICE       0x200000    /* No device at this target        */
#define PARTITIONED     0x400000    /* DOS partitioning flag           */
#define GETDEVINFO      0x800000    /* getdevinfo being performed      */

/*---------------------------------------------------------------------*/
/* TARGET_DEV state bits                                               */
/*---------------------------------------------------------------------*/
/* NOTE lower byte, bits 0 - 7 are  reserved for initurrpt bits.       */
/* example: target_dev->state |= CMD_COMPLETE;                         */
/*---------------------------------------------------------------------*/
#define DMA_TRANSFER    0x00000100  /* dma transfer in progress        */
#define PGM_TRANSFER    0x00000200  /* program transfer in progress    */
#define PHASE_CHG       0x00000400  /* phase change during transfer    */
#define DISCONNECTED    0x00000800  /* target disconnected from bus    */
#define RESTART         0x00001000  /* target disconnected from bus    */

#define DISCONNECT_MSG  0x00010000  /* disconnect message received     */
#define SAVE_DPTR_MSG   0x00020000  /* save data pointer message       */
#define RESTORE_PTR_MSG 0x00040000  /* restore data pointer message    */
#define REJECT_MSG      0x00080000  /* reject last message received    */
#define LINK_MSG        0x00100000  /* linked command complete         */
#define FLAG_MSG        0x00200000  /* linked command complete flag    */
#define IDENTIFY_MSG    0x00400000  /* establish nexus                 */

#define CLEAR_MESSAGE_FLAGS 0xFF0000 /* &= ~ will clear message flags  */

#endif /* _SCSI_H */

#if __cplusplus
}
#endif
