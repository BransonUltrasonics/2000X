/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\netutils.h_v   1.0   Mar 29 1999 13:51:00   ofingere  $ */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/netutils.h                                       */
/*   PURPOSE:                                                          */
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

#ifndef _NETUTILS_H
#define _NETUTILS_H

#if __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------*/
/* User list structure - used by both the FTP daemon and pSH.          */
/*---------------------------------------------------------------------*/
struct ulist_t
    {
    char  *login_name;     /* user login name */
    char  *login_passwd;   /* user login password */
    long  reserved[4];     /* reserved for future use, must be 0 */
    };
typedef struct ulist_t ulist_t;

/*---------------------------------------------------------------------*/
/* FTP daemon                                                          */
/*---------------------------------------------------------------------*/
#ifndef PHILE_TYPE
#define PHILE_TYPE 0
#define MSDOS_TYPE 1
#define NFS_TYPE   2
#define MEM_TYPE   3
#endif

struct ftpcfg_t 
    {
    long    task_prio;      /* priority for ftpd task */
    long    max_sessions;   /* max. # of concurrent sessions */
    char    *vol_name;      /* name of the login volume */
    char    **hlist;        /* ptr to the list of trusted clients */
    ulist_t *ulist;         /* ptr to the list of trusted users */
    long    reserved[2];    /* reserved for future use, must be 0 */
    };
typedef struct ftpcfg_t ftpcfg_t;
extern int ftpd_start(ftpcfg_t *CfgPtr);

/*---------------------------------------------------------------------*/
/* NFS daemon                                                          */
/*---------------------------------------------------------------------*/

/* export list structure */
struct nfselist_t 
    {
    char *dir_path;      /* volume/directory to be exported */
    char *hlist;         /* list of permitted clients */
    };
typedef struct nfselist_t nfselist_t;

/* NFS configuration table structure */
struct nfscfg_t 
    {
    long task_prio;      /* priority for nfsd task */
    long unix_auth;      /* unix authentication required flag */
    long error_opt;      /* error reporting option */
    long vol_blksize;    /* system-wide volume block size */
    char *def_vol_name;  /* name of the default volume */
    nfselist_t *elist;   /* ptr to the list of exported directories */
    long reserved[4];    /* reserved for future use, must be 0 */
    };
typedef struct nfscfg_t nfscfg_t;
extern int nfsd_start(nfscfg_t *CfgPtr);

/*---------------------------------------------------------------------*/
/* pSH                                                                 */
/*---------------------------------------------------------------------*/
#define NFS_TYPE   2
#define MEM_TYPE   3

struct appdata_t
    {
    char  *app_name;       /* application name */
    char  *app_help;       /* help string */
    void  (*app_entry)();  /* entry point */
    char  *app_tname;      /* task name */
    long  app_tprio;       /* task priority */
    long  app_sssize;      /* system stack size */
    long  app_ussize;      /* user stack size */
    short app_reentrant_flag;  /* reentrant flag */
    short app_reentrant_lock;  /* reentrant lock */
    };
typedef struct appdata_t appdata_t;

struct cmddata_t
    {
    char  *cmd_name;       /* command name */
    char  *cmd_help;       /* help string */
    void  (*cmd_entry)();  /* entry point */
    short cmd_reentrant_flag;  /* reentrant flag */
    short cmd_reentrant_lock;  /* reentrant lock */
    };
typedef struct cmddata_t cmddata_t;

struct pshcfg_t
    {
    long      flag;           /* services options */
    long      task_prio;      /* priority for pshd task */
    char      *def_vol_name;  /* name of the default login volume */
    ulist_t   *ulist;         /* ptr to the list of trusted users */
    appdata_t *app;           /* ptr to the list of applications */
    cmddata_t *cmd;           /* ptr to the list of commands */
    unsigned long console_dev;/* psh console device number */
    unsigned long pseudo_dev; /* psh pseudo device number */ 
    char      *cprompt;       /* console prompt */
    char      *tprompt;       /* telnet prompt */
    long      reserved[3];    /* reserved for future use, must be 0 */
    };
typedef struct pshcfg_t pshcfg_t;
extern int psh_start(pshcfg_t *CfgPtr);

extern char *psh_getenv(char *name, char **env);

extern char arpman[];
extern char catman[];
extern char cdman[];
extern char cdmountman[];
extern char clearman[];
extern char consoleman[];
extern char cmpman[];
extern char cpman[];
extern char dateman[];
extern char duman[];
extern char dateman[];
extern char echoman[];
extern char setenvman[];
extern char getidman[];
extern char getpriman[];
extern char headman[];
extern char helpman[];
extern char ifconfigman[];
extern char killman[];
extern char lsman[];
extern char mkdirman[];
extern char mkfsman[];
extern char mountman[];
extern char mvman[];
extern char netstatman[];
extern char nfsmountman[];
extern char pcmkfsman[];
extern char pcmountman[];
extern char pingman[];
extern char popdman[];
extern char pushdman[];
extern char pwdman[];
extern char resumeman[];
extern char rmman[];
extern char rmdirman[];
extern char routeman[];
extern char setidman[];
extern char setpriman[];
extern char sleepman[];
extern char statusman[];
extern char suspendman[];
extern char syncman[];
extern char tailman[];
extern char touchman[];
extern char umountman[];
extern void psys_arp();
extern void psys_cat();
extern void psys_cd();
extern void psys_cdmount();
extern void psys_clear();
extern void psys_console();
extern void psys_cmp();
extern void psys_cp();
extern void psys_date();
extern void psys_du();
extern void psys_echo();
extern void psys_getid();
extern void psys_getpri();
extern void psys_head();
extern void psys_help();
extern void psys_ifconfig();
extern void psys_kill();
extern void psys_ls();
extern void psys_mkdir();
extern void psys_mkfs();
extern void psys_mount();
extern void psys_mv();
extern void psys_netstat();
extern void psys_nfsmount();
extern void psys_pcmkfs();
extern void psys_pcmount();
extern void psys_ping();
extern void psys_popd();
extern void psys_pushd();
extern void psys_pwd();
extern void psys_resume();
extern void psys_rm();
extern void psys_rmdir();
extern void psys_route();
extern void psys_setenv();
extern void psys_setid();
extern void psys_setpri();
extern void psys_sleep();
extern void psys_suspend();
extern void psys_sync();
extern void psys_tail();
extern void psys_touch();
extern void psys_umount();

extern const char *nu_getvers(void);

/*---------------------------------------------------------------------*/
/* TFTP daemon                                                         */
/*---------------------------------------------------------------------*/
struct tftpdcfg_t 
    {
    char *tftpdir;      /* default directory for files */
    long  task_prio;    /* priority for 'TFD$' task */
    long  num_servers;  /* max. # of concurrent sessions */
    long  verbose;      /* 1 - yes; 0 - no */
    long  enable_log;   /* 1 - yes; 0 - no */
    long  reserved[1];  /* reserved for future use, must be 0 */
    };
typedef struct tftpdcfg_t tftpdcfg_t;

extern unsigned long tftpd_start(tftpdcfg_t *CfgPtr);
extern unsigned long tftpd_stop(void);

/*---------------------------------------------------------------------*/
/* Telnet daemon                                                       */
/*---------------------------------------------------------------------*/
struct tnpcfg_t 
    {
    long  task_prio;    /* priority for tnpd task */
    long  max_sessions; /* max. # of concurrent sessions */
    char  **hlist;      /* ptr to the list of trusted clients */
    long  reserved[2];  /* reserved for future use, must be 0 */
    };
typedef struct tnpcfg_t tnpcfg_t;
extern int tnpd_start(tnpcfg_t *CfgPtr);

/*---------------------------------------------------------------------*/
/* Telnet and FTP clients                                              */
/*---------------------------------------------------------------------*/
extern void telnet_main(int argc, char *argv[], char *env[], 
  int exit_param);

extern void ftp_main(int argc, char **argv, void **env,
    long exit_param);

/*---------------------------------------------------------------------*/
/* Router daemon                                                       */
/*---------------------------------------------------------------------*/
#define RT_ACTIVE   1
#define RT_PASSIVE  2
#define RT_EXTERNAL 3

struct gateways
  {
  struct in_addr destination;
  struct in_addr gateway;
  int metric;
  int state;
  int type;
  };
typedef struct gateways gateways_t;

struct routedcfg_t
  {
  unsigned long priority;
  int   intergtwy;
  int   supplier;
  int   syslog;
  int   maxgates;
  struct gateways *gways;
  };
typedef struct routedcfg_t routedcfg_t;

extern int routed_start(routedcfg_t *rcp);

/*---------------------------------------------------------------------*/
/* Bootp daemon                                                        */
/*---------------------------------------------------------------------*/
struct bootpdcfg_t {
  unsigned long priority;       /* Priority of BOOTPD task */
  unsigned long flags;          /* Execution/Option flags */
  char *bootptab;               /* bootpd DB file or string */
  struct in_addr parentIP;      /* IP address of parent BOOTP server */
  unsigned long reserved[2];    /* reserved for future use */
  };  
typedef struct bootpdcfg_t bootpdcfg_t;

extern int bootpd_start(bootpdcfg_t *bcp);

/* flag definitions */

#define BOOTPD_SYSLOG          0x00000001

#if __cplusplus
}
#endif

#endif /* _NETUTILS_H */

