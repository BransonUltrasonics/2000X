/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\gsblkcfg.c_v   1.0   Mar 29 1999 13:40:58   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: configs/gsblkcfg.c 2.12 98/06/18 15:12:11 */
/***********************************************************************/
/*                                                                     */
/*   MODULE: gsblkcfg.c                                                */
/*   DATE:    98/06/18                                                 */
/*   PURPOSE: General Serial mblk configuration                        */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1998, Integrated Systems, Inc.           */
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


#ifdef __cplusplus
    #if __cplusplus
extern "C" {
    #endif
#endif

#include "bsp.h"
#include <pna.h>
#include <gsblk.h>
#include "sys_conf.h"

/*---------------------------------------------------------------------*/
/* Backward compatibility for older pSOSystem applications which used  */
/* SE_MAX_GS_BUFS not GS_MAX_BUFS.                                     */
/*---------------------------------------------------------------------*/
#if !defined(GS_MAX_BUFS) && defined(SE_MAX_GS_BUFS)
    #define GS_MAX_BUFS SE_MAX_GS_BUFS
#endif

#if (BSP_NEW_SERIAL|BSP_PARALLEL)
struct gsblk_bufcfg gsblk_bufcfg[GS_MAX_BUFS +1];

unsigned char *gsblk_initbuffers(unsigned char *,
                 long, struct gsblk_bufcfg *);
#endif

/***********************************************************************/
/* GSblkSetup: Setup Mblk buffer pools                                 */
/*                                                                     */
/*      INPUTS: FreeMemPtr pointer to free memory area that can be     */
/*              used to allocate memory for this componet.             */
/*                                                                     */
/*              NodeCfg pointer to the systems node configuration      */
/*              table. This will be used to set the pnact              */
/*              element in the table.                                  */
/*                                                                     */
/*     RETURNS: The new FreeMemPtr is returned.                        */
/*                                                                     */
/***********************************************************************/
unsigned char *GSblkSetup(unsigned char *FreeMemPtr, ULONG ramsize, 
                          ULONG *error)
{
ULONG gsbsize, nmblks;

#if (BSP_NEW_SERIAL|BSP_PARALLEL)
int i = 0;

/*---------------------------------------------------------------------*/
/* Set up the General Serial buffer configuration  table.              */
/*---------------------------------------------------------------------*/

#if GS_BUFS_0
    gsblk_bufcfg[i].nbuffers = GS_BUFS_0;
    gsblk_bufcfg[i].bsize = 0;
    i++;
#endif

#if GS_BUFS_32
    gsblk_bufcfg[i].nbuffers = GS_BUFS_32;
    gsblk_bufcfg[i].bsize = 32;
    i++;
#endif

#if GS_BUFS_64
    gsblk_bufcfg[i].nbuffers = GS_BUFS_64;
    gsblk_bufcfg[i].bsize = 64;
    i++;
#endif

#if GS_BUFS_128
    gsblk_bufcfg[i].nbuffers = GS_BUFS_128;
    gsblk_bufcfg[i].bsize = 128;
    i++;
#endif

#if GS_BUFS_256
    gsblk_bufcfg[i].nbuffers = GS_BUFS_256;
    gsblk_bufcfg[i].bsize = 256;
    i++;
#endif

#if GS_BUFS_512
    gsblk_bufcfg[i].nbuffers = GS_BUFS_512;
    gsblk_bufcfg[i].bsize = 512;
    i++;
#endif

#if GS_BUFS_1024
    gsblk_bufcfg[i].nbuffers = GS_BUFS_1024;
    gsblk_bufcfg[i].bsize = 1024;
    i++;
#endif

#if GS_BUFS_2048
    gsblk_bufcfg[i].nbuffers = GS_BUFS_2048;
    gsblk_bufcfg[i].bsize = 2048;
    i++;
#endif

#if GS_BUFS_4096
    gsblk_bufcfg[i].nbuffers = GS_BUFS_4096;
    gsblk_bufcfg[i].bsize = 4096;
    i++;
#endif

gsblk_bufcfg[i].nbuffers = 0;
gsblk_bufcfg[i].bsize = 0;

/*---------------------------------------------------------------------*/
/* Check to see if the Memory is sufficient for the given configuration*/
/* If it exceeds the limit of RamSize of SC_RAM_SIZE set the ERROR     */
/* Flag and initialize the GSBLKs with minimal configuration of        */
/*                                                                     */
/* 4 '0' sized MBLK's                                                  */
/* 4 32 byte MBLK's                                                    */
/*                                                                     */
/* For printing the error in sysinit.c after checking the ERROR Flag   */
/* returned by this routine.                                           */
/*---------------------------------------------------------------------*/
gsbsize = (ULONG)FreeMemPtr + gsblk_bufsize(GS_MBLKS, gsblk_bufcfg);

if (gsbsize > ramsize)
    {
    gsblk_bufcfg[0].nbuffers = 4;
    gsblk_bufcfg[0].bsize = 0;

    gsblk_bufcfg[1].nbuffers = 4;
    gsblk_bufcfg[1].bsize = 32;

    gsblk_bufcfg[2].nbuffers = 0;
    gsblk_bufcfg[2].bsize = 0;

    nmblks = 8;
    *error = 1;
    }
else
    {
    *error = 0;
    nmblks = GS_MBLKS;
    }

/*---------------------------------------------------------------------*/
/* Initialize the buffers.                                             */
/*---------------------------------------------------------------------*/
FreeMemPtr = gsblk_initbuffers(FreeMemPtr, nmblks, gsblk_bufcfg);

#endif
return(FreeMemPtr);

}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
