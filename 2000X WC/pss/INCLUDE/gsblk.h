/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\gsblk.h_v   1.0   Mar 29 1999 13:50:56   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/gsblk.h (&U&) 2.4 97/10/21 17:15:31 */
/***********************************************************************/
/*                                                                     */
/*   MODULE: gsblk.h                                                   */
/*   DATE:    97/10/21                                                 */
/*   PURPOSE: Definitions for General Serial Message Blocks            */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1994, Integrated Systems, Inc.                  */
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

#ifndef _GSBLK_H
#define _GSBLK_H

#include <pna.h>

#define MAXBUFFERS 256
#define BPRI_LO  0
#define BPRI_MED 1
#define BPRI_HI  2

/*----------------------------------------------------------------------*/
/* Data block structure for esballoc call. It need to store all the     */
/* data blocks allocated thru' esballoc in a linked to be freed at      */
/* pSOS restart time. Esballoc can be used by the driver attach a data  */
/* buffer. This can be done before pSOS is initialized                  */
/*----------------------------------------------------------------------*/
struct esbdatab
  {
  dblk_t esb_dblk;              /* Data block */
  struct esbdatab *next;        /* Next link */
  struct esbdatab *prev;        /* Previous link */
  };
typedef struct esbdatab esbdblk_t;  

/*----------------------------------------------------------------------*/
/* Structure for holding the esballoc allocated buffers                 */
/*----------------------------------------------------------------------*/
struct dblkq
  {
  esbdblk_t *next;
  esbdblk_t *prev;
  };

/*----------------------------------------------------------------------*/
/* Definition of the buffer configuration table                         */
/*----------------------------------------------------------------------*/
struct gsblk_bufcfg
    {
    unsigned long nbuffers;   /* Number of buffers */
    unsigned long bsize;      /* Buffer size */
    unsigned long reserved[2];/* Reserved entries */
    };

typedef struct gsblk_bufcfg gsblk_bufcfg_t;  

/*---------------------------------------------------------------------*/
/* Prototypes for global functions.                                    */
/*---------------------------------------------------------------------*/
mblk_t *gs_allocb(int size, int pri);
mblk_t *gs_esballoc(unsigned char *base, int size, int pri, frtn_t *frtn);
void gs_freemsg(register mblk_t *mp);
unsigned long gsblk_bufsize(long, struct gsblk_bufcfg *);

#endif  /* _GHBLK_H */

#if __cplusplus
    }
#endif
