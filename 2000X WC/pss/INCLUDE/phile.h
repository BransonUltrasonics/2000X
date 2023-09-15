/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\phile.h_v   1.0   Mar 29 1999 13:51:00   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/phile.h (pnew) 1.16 96/02/02 13:13:19 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/phile.h                                          */
/*   DATE:    96/02/02                                                 */
/*   PURPOSE: Structure definitions, function prototypes, and          */
/*            symbol definitions for pHILE+                            */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*          Copyright 1991 - 1996, Integrated Systems, Inc.            */
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
#ifndef _PHILE_H
#define _PHILE_H

#include <types.h>

/***********************************************************************/
/* General Definitions                                                 */
/***********************************************************************/

/***********************************************************************/
/* pHILE+ Structure Definitions                                        */
/***********************************************************************/

/*---------------------------------------------------------------------*/
/* init_vol() Parameter Structure                                      */
/*---------------------------------------------------------------------*/
typedef struct init_vol_params
    {
    char  volume_label[12];
    ULONG volume_size;
    ULONG num_of_file_descriptors;
    ULONG starting_bitmap_block_number;
    ULONG starting_data_block_number;
    } INIT_VOL_PARAMS;

/*---------------------------------------------------------------------*/
/* verify_vol() Fault Descriptor Block Structure                       */
/*---------------------------------------------------------------------*/
typedef struct fault_desc_block
    {
    ULONG fdb_code;
    ULONG fdb_fn1;
    ULONG fdb_fn2;
    char *fdb_path1;
    char *fdb_path2;
    ULONG fdb_bn;
    ULONG fdb_fixable;
    } FAULT_DESC_BLOCK;

/*---------------------------------------------------------------------*/
/* verify_vol() Parameter Structure                                    */
/*---------------------------------------------------------------------*/
typedef struct verify_vol_params
    {
    void *pb_dataptr;
    ULONG pb_datalen;
    ULONG pb_maxdepth;
    FAULT_DESC_BLOCK *pb_fdbptr;
    ULONG (*pb_faultp)(void);
    ULONG *pb_badblkptr;
    } VERIFY_VOL_PARAMS;

/*---------------------------------------------------------------------*/
/* nfsmount_vol() Parameter Structure                                  */
/*---------------------------------------------------------------------*/
typedef struct nfsmount_vol_params
    {
    ULONG ipaddr;
    char *pathname;
    ULONG flags;
    ULONG reserved[6];
    } NFSMOUNT_VOL_PARAMS;

/*---------------------------------------------------------------------*/
/* Device Driver Buffer Header Structure                               */
/*---------------------------------------------------------------------*/
typedef struct buffer_header
    {
    ULONG b_device;
    ULONG b_blockno;
    USHORT b_flags;
    USHORT b_bcount;
    void *b_devforw;
    void *b_devback;
    void *b_avlforw;
    void *b_avlback;
    void *b_bufptr;
    void *b_bufwaitf;
    void *b_bufwaitb;
    void *b_volptr;
    USHORT b_blksize;
    USHORT b_dsktype;
    } BUFFER_HEADER;

/***********************************************************************/
/* Readdir() directory entry					       */
/***********************************************************************/
#define MAXNAMLEN       255
typedef struct XDIR {
    int   dd_fd;		/* file descriptor */
    long  dd_loc;		/* buf offset of entry from last readdir() */
    long  dd_size;		/* amount of valid data in buffer */
    long  dd_bsize;		/* amount of entries read at a time */
    long  dd_off;		/* current offset in dir */
    char  *dd_buf;		/* directory data buffer pointer */
    char  dd_buffer[300];	/* directory data buffer */
} XDIR;
 
struct dirent {
        unsigned long d_filno;
        char    d_name[MAXNAMLEN+1];
        };
 
 
typedef unsigned long mode_t;
typedef unsigned long ino_t;
typedef unsigned long dev_t;
typedef unsigned long nlink_t;
typedef unsigned long uid_t;
typedef unsigned long gid_t;
typedef unsigned long off_t;
typedef unsigned long time_t;
 
/***********************************************************************/
/* utimes() access and modification times                              */
/***********************************************************************/
struct utimbuf {
        time_t actime;
        time_t modtime;
        };
 
 
/***********************************************************************/
/* stat_f(): read status of a file;                                    */
/***********************************************************************/
struct stat {
    mode_t  st_mode;		/* ownership/protection */
    ino_t   st_ino;		/* file id */
    dev_t   st_dev;		/* file system id */
    dev_t   st_rdev;
    nlink_t st_nlink;		/* number of links */
    uid_t   st_uid;		/* user id */
    gid_t   st_gid;		/* group id */
    off_t   st_size;		/* file size in # of bytes */
    time_t  st_atime;		/* time file was last accessed */
    time_t  st_mtime;		/* time file was last modified */
    time_t  st_ctime;		/* time file status was last changed */
    unsigned long  st_blksize;	/* block size */
    unsigned long  st_blocks;	/* file size in # of blocks */
};
 
/***********************************************************************/
/* stat_vfs(): read statistics of a file system.                       */
/***********************************************************************/
typedef struct {
    long val[2];
    } fsid_t;

#define FSTYPSZ		16
#define FSSTRSZ		32
 
struct statvfs {
    unsigned long f_bsize;      /* preferred file system block size */
    unsigned long f_frsize;     /* fundamental fs block size */
    unsigned long f_blocks;     /* total blocks in the volume */
    unsigned long f_bfree;      /* free blocks */
    unsigned long f_bavail;     /* free blocks available to non-super-user */
    unsigned long f_files;      /* total file nodes in file system */
    unsigned long f_ffree;      /* free file nodes in volume */
    unsigned long f_favail;     /* free file nodes to non-super-user */
    fsid_t vol_fsid;            /* volume (file system) id */
    char f_basetype[FSTYPSZ];   /* target fs type name, null terminated */
    unsigned long f_flag;       /* bit mask of flags */
    unsigned long f_namemax;    /* maximum specific string */
    char f_fstr[FSSTRSZ];       /* file system specific string */
    unsigned long f_fstype;     /* file system type number */
    unsigned long f_filler[15]; /* reserved for future expansion */
    };
 
/*---------------------------------------------------------------------*/
/* CD-ROM Primary Volume Descriptor as read from _VOLUME.$Y$           */
/*---------------------------------------------------------------------*/
#define CDFS_NAMMAX     32      /* max node size (in bytes) */
 
/*
 * CDFS Directory Record (internal format).
 */
typedef struct dir_cdfs {
        USHORT  dr_reclen;	/* directory record length */
        USHORT  dr_xarlen;	/* extended attribute record length */
        ULONG   dr_extent;	/* number of first data block in file*/
        ULONG   dr_fsize;	/* byte size of file data space */
        ULONG   dr_cdate;	/* date when created (psos format) */
        ULONG   dr_ctime;	/* time when created (psos format) */
        USHORT  dr_flags;	/* directory flags per iso_dirrec */
        USHORT  dr_namlen;	/* byte length of name */
        char    dr_name[CDFS_NAMMAX + 1]; /* the name */
} dir_cdfs_t;
 
/*
 * CDFS Volume Descriptor template.
 *
 * Returned to user upon read of "_VOLUME.$Y$" virtual file.
 */
typedef struct desc_cdfs {
        UCHAR           cd_type;                /* volume descriptor type */
        UCHAR           cd_id[5+1];             /* standard identifier */
        UCHAR           cd_vers;                /* volume descriptor version */
        UCHAR           cd_flags;               /* volume flags (supp) */
        UCHAR           cd_sysid[32+1];         /* system identifier */
        UCHAR           cd_volid[32+1];         /* volume idenfifier */
        ULONG           cd_volsize;             /* volume space size */
        UCHAR           cd_escseq[32];          /* escape sequences (supp) */
        USHORT          cd_volsetsize;          /* volume set size */
        USHORT          cd_volseqnum;           /* volume sequence number */
        USHORT          cd_logblksize;          /* logical block size */
        ULONG           cd_pathtabsize;         /* path table byte size */
        ULONG           cd_pathtab;             /* path table logical block */
        ULONG           cd_pathtabopt;          /* opt path table log block */
        struct dir_cdfs cd_rootdir;             /* root directory */
        UCHAR           cd_volsetid[128+1];     /* volume set identifier */
        UCHAR           cd_pubid[128+1];        /* publisher identifier */
        UCHAR           cd_prepid[128+1];       /* data preparer identifier */
        UCHAR           cd_appid[128+1];        /* application identifier */
        UCHAR           cd_cpyrid[37+1];        /* copyright file identifier */
        UCHAR           cd_absfid[37+1];        /* abstract file identifier */
        UCHAR           cd_bibfid[37+1];        /* bibliographic identifier */
        ULONG           cd_cdate;               /* volume create date (psos) */
        ULONG           cd_ctime;               /* volume create time (psos) */
        ULONG           cd_mdate;               /* modification date (psos) */
        ULONG           cd_mtime;               /* modification time (psos) */
        ULONG           cd_xdate;               /* expiration date (psos) */
        ULONG           cd_xtime;               /* expiration time (psos) */
        ULONG           cd_edate;               /* effective date (psos) */
        ULONG           cd_etime;               /* effective time (psos) */
        UCHAR           cd_svers;               /* file structure version */
        UCHAR           cd_appdata[512];        /* application private */
} desc_cdfs_t;

/***********************************************************************/
/* pHILE+ System Calls (defined in fim.s)                              */
/***********************************************************************/
ULONG access_f(char *name, int mode);
ULONG annex_f(ULONG fid, ULONG alloc_size, ULONG *blkcount);
ULONG cdmount_vol(char *device, ULONG sync_mode);
ULONG change_dir(char *name);
ULONG chmod_f(char *name, int mode);
ULONG chown_f(char *name, int owner, int group);
ULONG close_dir(XDIR *dir);
ULONG close_f(ULONG fid);
ULONG create_f(char *name, ULONG expand_unit, ULONG mode);
ULONG fchmod_f(ULONG fid, int mode);
ULONG fchown_f(ULONG fid, int owner, int group);
ULONG fstat_f(ULONG fid, struct stat *buf);
ULONG fstat_vfs(ULONG fid, struct statvfs *buf);
ULONG ftruncate_f(ULONG fid, ULONG length);
ULONG get_fn(char *name, ULONG *fn);
ULONG init_vol(char *dev, INIT_VOL_PARAMS *parameters, void *scratchbuf);
ULONG link_f(char *name1, char *name2);
ULONG lock_f(ULONG fid, ULONG startpos, ULONG bcount);
ULONG lseek_f(ULONG fid, ULONG position, long offset, ULONG *old_ptr);
ULONG lstat_f(char *name, struct stat *buf);
ULONG make_dir(char *name, ULONG mode);

ULONG mount_vol(char *device, ULONG sync_mode);
ULONG move_f(char *oldname, char *newname);
ULONG nfsmount_vol(char *device, NFSMOUNT_VOL_PARAMS *nfs_parms);
ULONG open_dir(char *dirname, XDIR *dir);
ULONG open_f(ULONG *fid, char *name, ULONG mode);
ULONG open_fn(ULONG *fid, char *device, ULONG fn, ULONG mode);

ULONG pcinit_vol(char *device, void *scratch_buf, ULONG dktype);
ULONG pcmount_vol(char *device, ULONG sync_mode);
ULONG read_dir(XDIR *dir, struct dirent *buf);
ULONG read_f(ULONG fid, void *buffer, ULONG bcount, ULONG *tcount);
ULONG read_link(char *name, char *buf, ULONG *bufsize);
ULONG read_vol(char *device, ULONG block, ULONG index, ULONG bcount,
               void *buffer);
ULONG remove_f(char *name);

ULONG stat_f(char *name, struct stat *buf);
ULONG stat_vfs(char *name, struct statvfs *buf);
ULONG symlink_f(char *name1, char *name2);
ULONG sync_vol(char *device);
ULONG truncate_f(char *name, ULONG length);
ULONG unmount_vol(char *device);
ULONG utime_f(char *name, struct utimbuf *times);
ULONG verify_vol(char *device, VERIFY_VOL_PARAMS *parameters);
ULONG write_f(ULONG fid, void *buffer, ULONG bcount);

ULONG write_vol(char *device, ULONG block, ULONG index, ULONG bcount,
                void *buffer);

/***********************************************************************/
/* pHILE+ Symbol Definitions                                           */
/***********************************************************************/
/***********************************************************************/
/* stat_f(): read status of a file;				       */
/* stat_vfs(): read statistics of a file system.		       */
/***********************************************************************/
#define _IFMT   	0170000 /* type of file */
#define         _IFDIR  0040000 /* directory */
#define         _IFCHR  0020000 /* character special */
#define         _IFBLK  0060000 /* block special */
#define         _IFREG  0100000 /* regular */
#define         _IFLNK  0120000 /* symbolic link */
#define         _IFSOCK 0140000 /* named socket */
#define         _IFIFO	0010000 /* fifo */
 
#define S_ISBLK(m)  (((m)&_IFMT) == _IFBLK)
#define S_ISCHR(m)  (((m)&_IFMT) == _IFCHR)
#define S_ISDIR(m)  (((m)&_IFMT) == _IFDIR)
#define S_ISFIFO(m) (((m)&_IFMT) == _IFIFO)
#define S_ISREG(m)  (((m)&_IFMT) == _IFREG)
#define S_ISLNK(m)  (((m)&_IFMT) == _IFLNK)
#define S_ISSOCK(m) (((m)&_IFMT) == _IFSOCK)
 
#define S_ISUID   0004000	/* set user id on execution */
#define S_ISGID   0002000	/* set group id on execution */
#define S_ISVTX   0001000	/* save swapped text even after use */
 
#define S_IRWXU 0000700 /* rwx for owner */
#define S_IRUSR 0000400 /* read permission for owner */
#define S_IWUSR 0000200 /* write permission for owner */
#define S_IXUSR 0000100 /* execute/search permission for owner */
#define S_IRWXG 0000070 /* rwx for group */
#define S_IRGRP 0000040 /* read permission for group */
#define S_IWGRP 0000020 /* write permission for grougroup */
#define S_IXGRP 0000010 /* execute/search permission for group */
#define S_IRWXO 0000007 /* rwx for other */
#define S_IROTH 0000004 /* read permission for other */
#define S_IWOTH 0000002 /* write permission for other */
#define S_IXOTH 0000001 /* execute/search permission for other */
 
/*---------------------------------------------------------------------*/
/* Possible values of struct statvfs member f_fstype                   */
/*---------------------------------------------------------------------*/
#define FSTYPE_PHILE	0	/* pHILE+ formatted volumes */
#define FSTYPE_PCDOS	1	/* PC/DOS formatted volumes */
#define FSTYPE_CDROM	2	/* ISO-9660 formatted volumes */
#define FSTYPE_NFS	3	/* Client-side NFS "volumes" */

#define NUM_FSTYPE	4	/* Count of file system types */

/*---------------------------------------------------------------------*/
/* access_f(): test accessibility				       */
/*---------------------------------------------------------------------*/
#define R_OK	4		/* read permission */
#define	W_OK	2		/* write permission */
#define	X_OK	1		/* execute permission */
#define	F_OK	0		/* presence of file */

/*---------------------------------------------------------------------*/
/* create_f() and make_dir() mode Definitions                          */
/*---------------------------------------------------------------------*/
#define S_IREAD       0000400   /* read permission, owner */
#define S_IWRITE      0000200   /* write permission, owner */
#define S_IEXEC       0000100   /* execute/search permission, owner */

#define S_IRUSR       0000400   /* read permission, owner */
#define S_IWUSR       0000200   /* write permission, owner */
#define S_IXUSR       0000100   /* execute/search permission, owner */
#define S_IRGRP       0000040   /* read permission, group */
#define S_IWGRP       0000020   /* write permission, group */

#define S_IXGRP       0000010   /* execute/search permission, group */
#define S_IROTH       0000004   /* read permission, other */
#define S_IWOTH       0000002   /* write permission, other */
#define S_IXOTH       0000001   /* execute/search permission, other */

/*---------------------------------------------------------------------*/
/* cdmount_vol(), mount_vol(), and pcmount_vol() sync_mode Definitions */
/*---------------------------------------------------------------------*/
#define SM_IMMED_WRITE      0
#define SM_CONTROL_WRITE    1
#define SM_DELAYED_WRITE    2
#define SM_READ_ONLY        3

/*---------------------------------------------------------------------*/
/* BUFFER_HEADER Structure b_flags Definitions                         */
/*---------------------------------------------------------------------*/
#define BT_UNKNOWN    0x00
#define BT_DATA       0x01
#define BT_CONTROL    0x02

/*---------------------------------------------------------------------*/
/* pcinit_vol() dktype MS-DOS Volume Type Definitions                  */
/*---------------------------------------------------------------------*/
#define DK_HARD     0		/* Hard disk */
#define DK_360      1           /*    360K: 5 1/4" DD double density */
#define DK_12       2           /*   1.2M : 5 1/4" DH high density */
#define DK_720      3           /*    720K: 3 1/2" DD double density */
#define DK_144      4           /*   1.44M: 3 1/2" DH high density */
#define DK_288      5           /*   2.88M: 3 1/2" DQ high density */
#define DK_NEC      6           /*   1.2M : 5 1/4" NEC */
#define DK_OPT      7           /* 124.4M : Fuji M2511A OMEM optical disk */

/***********************************************************************/
/* pHILE+ Error Codes                                                  */
/***********************************************************************/

/*---------------------------------------------------------------------*/
/* Fatal pHILE+ Error Codes                                            */
/*---------------------------------------------------------------------*/
#define FAT_NORAM     0x2F01    /* Insufficient data area */
#define FAT_PHCSUM    0x2F0E    /* Check sum in pHILE+ */

/*---------------------------------------------------------------------*/
/* General pHILE+ Error Codes                                          */
/*---------------------------------------------------------------------*/
#define E_FUNC        0x2001    /* Invalid function number */
#define E_FAIL        0x2002    /* pHILE+ failure */
#define E_BADVOL      0x2003    /* Inconsistent structure on volume */
#define E_VINITPAR    0x2005    /* Illegal parameters to init_vol() */
#define E_MNTFULL     0x2006    /* Attempt to mount too many volumes */

#define E_VALIEN      0x2007    /* Wrong volume format */
#define E_MNTED       0x2008    /* Volume already mounted */
#define E_MNTOPEN     0x2009    /* Cannot unmount - there are files open */
#define E_DMOUNT      0x200A    /* Volume not mounted */
#define E_FNAME       0x200B    /* Filename not found */

#define E_IFN         0x200C    /* Illegal pathname */
#define E_NDD         0x200D    /* No default directory */
#define E_FORD        0x200E    /* Directory file expected */
#define E_ASIZE       0x200F    /* Illegal expansion unit */
#define E_NODE        0x2010    /* Null pathname */

#define E_FEXIST      0x2011    /* File already exists */
#define E_FLIST       0x2012    /* Too many files on volume */
#define E_FOPEN       0x2013    /* Cannot remove an open file */
#define E_DNE         0x2014    /* Directory not empty */
#define E_RO          0x2015    /* Illegal on system or directory file */

#define E_DIFDEV      0x2016    /* Operation must be on the same volume */
#define E_NOTREE      0x2017    /* MOVE_F would destroy directory tree */
#define E_OFULL       0x2018    /* Too many files open for task */
#define E_NOFCB       0x2019    /* Too many files open in system */
#define E_FIDBIG      0x201A    /* Invalid FID, exceeds maximum */

#define E_FIDOFF      0x201B    /* Invalid FID, file closed */
#define E_ININFULL    0x201C    /* Index block full */
#define E_VFULL       0x201D    /* Volume full */
#define E_BADPOS      0x201E    /* Bad position to lseek */
#define E_EOF         0x201F    /* Seek past end of file */

#define E_ILLDEV      0x2021    /* Illegal device (exceeded maximum) */
#define E_LOCKED      0x2022    /* Data locked */
#define E_BADFN       0x2023    /* Illegal or unused filename */
#define E_FMODE       0x2024    /* Illegal synchronization mode */

#define E_IDN         0x2025    /* Illegal device name */

/*----------------------------------------------------------------------*/
/*  Errors Returned PCDOS FS related activity                           */
/*----------------------------------------------------------------------*/
#define E_BADMS       0x2026    /* bad MS/DOS call */
#define E_ILLMSTYP    0x2027    /* Illegal DOS disk type */
#define E_MULMSDSK    0x2028    /* Format conflicts with mounted volumes */
#define E_NMSVOL      0x2029    /* Cannot mount MS-DOS volume */

/*----------------------------------------------------------------------*/
/*  Errors Returned from FS Common activity  (0x204?)                   */
/*----------------------------------------------------------------------*/
#define E_BUFSIZE     0x2041	/* buffers not available for block size */

/*----------------------------------------------------------------------*/
/*  Errors Returned NFS related activity (0x205?)                       */
/*----------------------------------------------------------------------*/
#define E_BADNFS      0x2050    /* NFS volume - illegal operation */
#define E_MAXLOOP     0x2051    /* Symbolic links nested too deeply */
#define E_EREMOTE     0x2052	/* Too many levels of remote in path */
#define E_PERM        0x2053    /* Task does not have ownership */
#define E_EIO         0x2054    /* Hard error happened at remote site */

#define E_EACCES      0x2055    /* Task does not have access permisssions */
#define E_EISDIR      0x2056    /* Illegal operation on a directory */
#define E_EQUOT       0x2057    /* Quota exceeded */
#define E_ESTALE      0x2058    /* Stale NFS file handle */
#define E_XLINK	      0x2059	/* Can't crose link */

#define E_NAMETOOLONG 0x205A	/* directory/file name too long */
#define	E_ENXIO	      0x205B	/* No such device or address */
#define	E_ENODEV      0x205C	/* No such device */

/*----------------------------------------------------------------------*/
/*  Errors Returned CDFS related activity (0x206?)                      */
/*----------------------------------------------------------------------*/
#define  E_BADCD      0x2060    /* Error for unsupported CDFS call */
#define  E_NCDVOL     0x2061	/* Not configured for CD-ROM volumes. */
#define  E_CDMVOL     0x2062	/* Can't support multi-volume CD_ROM. */
#define  E_CDBSIZE    0x2063	/* Volume not made with 2k block size. */
#define  E_CDFMT      0x2064	/* CD-ROM not ISO-9660 compliant. */

/*----------------------------------------------------------------------*/
/*  Set RPC to pHILE mapping (0x207?)                                   */
/*----------------------------------------------------------------------*/
#define E_EAUTH       0x2070    /* RPC authorization is not available */
#define E_ENFS        0x2071    /* NFS Error */
#define E_ETIMEDOUT   0x2072    /* NFS call timed out */
#define E_ENOAUTHBLK  0x2074    /* No RPC auth blocks available */

#define E_ECANTSEND   0x2075	/* Failure in sending call     */
#define	E_ECANTRECV   0x2076	/* Failure in receiving result */
#define	E_EPROGUNAVAIL 0x2077	/* Program not available       */
#define E_EPROGVERSMISMATCH 0x2078 /* Program version mismatched */
#define	E_ECANTDECODEARGS 0x2079 /* Decode arguments error     */

#define	E_EUNKNOWNHOST 0x207A	/* Unknown host name	       */
#define	E_EPROGNOTREGISTERED 0x207B /* Remote program is not registered */
#define E_EUNKNOWNPROTO	0x207C	/* Unknown protocol	       */
#define	E_EINTR	      0x207D	/* Call interrupted */
#define E_ERPC	      0x207E    /* All other RPC errors */

/*---------------------------------------------------------------------*/
/* verify_vol() Error Codes                                            */
/*---------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/ 
/* ROOT BLOCK FAULTS                                                 */
/*-------------------------------------------------------------------*/ 
#define VF_BMOFL      0x2101    /* Bitmap and FLIST overlap */
#define VF_BMSIZ      0x2102    /* Bitmap wrong size */
#define VF_FLSIZ      0x2103    /* FLIST wrong size */
#define VF_BMOVL      0x2104    /* Bitmap overflows volume */
#define VF_FLOVL      0x2105    /* FLIST overflows volume */

#define VF_BMDA       0x2106    /* Bitmap overlaps data area */
#define VF_FLDA       0x2107    /* FLIST overlaps data area */
  
/*-------------------------------------------------------------------*/ 
/* CONTROL STRUCTURE FAULTS.                                         */
/*-------------------------------------------------------------------*/ 
#define VF_BMEXT      0x2108    /* Bitmap extent map wrong */
#define VF_FLEXT      0x2109    /* FLIST extent map wrong */
#define VF_NDRFD      0x210A    /* ROOT dir FD not marked as directory */

#define VF_FDMU       0x210B    /* FD in use by more than 1 file */
#define VF_FDFRE      0x210C    /* FD in use marked free */
#define VF_FDUSE      0x210D    /* Unused FD marked in use */
  
/*------------------------------------------------------------------*/
/* FILE DESCRIPTOR FAULTS                                           */
/*------------------------------------------------------------------*/
#define VF_NSSFD      0x2110    /* Non-system file marked system in FD */
#define VF_SNSFD      0x2111    /* System file marked non-system in FD */

#define VF_PARFD      0x2112    /* Wrong parent FN in FD */
#define VF_FCFD       0x2113    /* Wrong file count in directory FD */
#define VF_SIZFD      0x2114    /* Physical size < logical size in FD */
#define VF_ANXFD      0x2115    /* Extension unit = 0 in FD */
  
/*-------------------------------------------------------------------*/ 
/* EXTENT MAP FAULTS.                                                */
/*-------------------------------------------------------------------*/ 
#define VF_EXTFD      0x2118    /* Illegal extent in FD */

#define VF_INFD       0x2119    /* Illegal indirect block in FD */
#define VF_IXFD       0x211A    /* Illegal index block in FD */
#define VF_TBCFD      0x211B    /* Wrong block count in FD */
#define VF_LLBFD      0x211C    /* Wrong LLB in FD */
#define VF_LLBIN      0x211D    /* Wrong LLB in FD indirect blk descriptor */

#define VF_EXTIN      0x211E    /* Illegal extent in indirect block */
#define VF_INIX       0x211F    /* Illegal indirect block in index block */
#define VF_LLBIX      0x2120    /* Wrong LLB in indirect blk descriptor */
#define VF_DBDA       0x2121    /* Directory block in data area */
#define VF_INDA       0x2122    /* Indirect block in data area */

#define VF_IXDA       0x2123    /* Index block in data area */
  
/*-------------------------------------------------------------------*/ 
/* DIRECTORY FAULTS                                                  */
/*-------------------------------------------------------------------*/ 
#define VF_DFDIR      0x2124    /* Duplicate filename in directory */
#define VF_IFDIR      0x2125    /* Illegal filename in directory */
#define VF_FNDIR      0x2126    /* Illegal FN in directory */
  
/*-------------------------------------------------------------------*/ 
/* BITMAP/BLOCK FAULTS.                                              */
/*-------------------------------------------------------------------*/ 
#define VF_BKMU       0x2128    /* Block is multiply used */

#define VF_BBUSE      0x2129    /* Bad BLOCK in use */
#define VF_BKFRE      0x212A    /* BLOCK in use is marked free */
#define VF_BBFRE      0x212B    /* Bad BLOCK is marked free */
#define VF_BKUSE      0x212C    /* Unused block marked in use */
  
/*-------------------------------------------------------------------*/ 
/* FATAL ERROR CODES.                                                */
/*-------------------------------------------------------------------*/ 
#define VF_INSUFF     0x2200    /* Work area too small */

#define VF_MAXDEPTH   0x2201    /* Directory depth exceeds maximum */
#define VF_ABORT      0x2202    /* Verify routine aborted by user */
  
/*---------------------------------------------------------------------*/
/* #endif for phile.h include                                          */
/*---------------------------------------------------------------------*/
#endif

#if __cplusplus
}
#endif

