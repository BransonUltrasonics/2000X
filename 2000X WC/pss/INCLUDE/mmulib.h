/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\mmulib.h_v   1.0   Mar 29 1999 13:51:00   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: sys/libc/68k/mmu68040.ghs/mmulib.h 1.3 98/03/26 11:38:10 */
/***********************************************************************/
/*                                                                     */
/*   MODULE: mmulib.h                                                  */
/*   DATE:    98/03/26                                                 */
/*   PURPOSE: Contains common defines for MMU mapping                  */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1994, Integrated Systems, Inc.           */
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
/* Don't allow this file to be included more than once.                */
/*---------------------------------------------------------------------*/
#ifndef _MMULIB_H
#define _MMULIB_H

/*---------------------------------------------------------------------*/
/* Define the size of a page of memory and an alignment mask.          */
/*---------------------------------------------------------------------*/
#define PAGE_ALIGMENT 0xFFF
#define PAGE_SIZE 0x1000

/*---------------------------------------------------------------------*/
/* Mapping tables will be created from information in a template. The  */
/* template will consist of an array of structures which describes one */
/* contiguous area of physical memory.                                 */
/*                                                                     */
/* Map Template structure, map_t:                                      */
/*---------------------------------------------------------------------*/
struct map_t
    {
    void *addr;
    unsigned long len;
    unsigned long attr;
    };

/*---------------------------------------------------------------------*/
/* Prototypes for MMU function calls                                   */
/*---------------------------------------------------------------------*/
unsigned long map_create(struct map_t *map,
           unsigned long maplen,
           void *mapmem,
           unsigned long mapmemlen,
           unsigned long *mapid,
           unsigned long *tablesize);

void map_default(unsigned long mapid);

unsigned long map_getattr(unsigned long mapid,
            void *addr,
            unsigned long *attr);

unsigned long map_getid(unsigned long tid,
          unsigned long *defmapid,
          unsigned long *taskmapid);

unsigned long map_setattr(unsigned long mapid,
            void *addr,
            unsigned long len,
            unsigned long mask,
            unsigned long attr);

unsigned long map_task(unsigned long tid,
                       unsigned long mapid);

void map_cocs(unsigned long *TCB,
              unsigned long tid);

void map_reco(void);

void map_rxco(void);

void map_cocsa(void);

void map_start(void);

long map_size(unsigned long memsize);

/*---------------------------------------------------------------------*/
/* Error return codes from MMU functions                               */
/*---------------------------------------------------------------------*/
/* EMMU_INSUFMEM if map area was too small or couldn`t allocate        */
/* enought from region zero.                                           */
/*---------------------------------------------------------------------*/
#define EMMU_INSUFMEM 0x01200001

/*---------------------------------------------------------------------*/
/* EMMU_DUP_PAGE_ENTRY if there is a duplicate page referenced in the  */
/* map_t array.                                                        */
/*---------------------------------------------------------------------*/
#define EMMU_DUP_PAGE_ENTRY 0x01200002

/*---------------------------------------------------------------------*/
/* EMMU_ADDR_NOT_ON_PAGE if the starting address of a section is not   */
/* on a page boundary.                                                 */
/*---------------------------------------------------------------------*/
#define EMMU_ADDR_NOT_ON_PAGE 0x01200003

/*---------------------------------------------------------------------*/
/* EMMU_LEN_NOT_PAGE_MULT if the length of a section is not a multiple */
/* of 4k.                                                              */
/*---------------------------------------------------------------------*/
#define EMMU_LEN_NOT_PAGE_MULT 0x01200004

/*---------------------------------------------------------------------*/
/* EMMU_PAGE_NOT_DEFINED if any page in the memory area is not defined */
/* (no entry present in map).                                          */
/*---------------------------------------------------------------------*/
#define EMMU_PAGE_NOT_DEFINED 0x01200005

/*---------------------------------------------------------------------*/
/* EMMU_TID_NOT_VALID if the task id is not valid.                     */
/*---------------------------------------------------------------------*/
#define EMMU_TID_NOT_VALID 0x01200006

/*---------------------------------------------------------------------*/
/* Page Attributes                                                     */
/*                                                                     */
/* NOTE: The default Page Attributes are:                              */
/*                                                                     */
/*     Cachable, writethrough - all data is cachable but all writes    */
/*                               will be written through to memory.    */
/*                                                                     */
/*     r/w - page is read/writable                                     */
/*                                                                     */
/*     valid - page is marked resident in memory                       */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* MAP_INVBIT will mark the page invalid. If the page is accessed      */
/* the processor will take a bus error exception.                      */
/*---------------------------------------------------------------------*/
#define MAP_INVBIT  0x01

/*---------------------------------------------------------------------*/
/* MAP_WPBIT will mark the page write protected (read only) any writes */
/* attempted to the page will cause the processor to take a bus error  */
/* exception.                                                          */
/*---------------------------------------------------------------------*/
#define MAP_WPBIT   0x02

/*---------------------------------------------------------------------*/
/* MAP_CIBIT will mark the page cache inhibited, nonserialized. If the */
/* page is accessed the cache is bypassed, and an external bus transfer*/
/* is performed. If the data to be accessed is present in the cache    */
/* and is dirty (different from memory) then it will be pushed from    */
/* the cache (written to memory) before an access is done to the data. */
/* In this nonserialized state a read may be allowed before the        */
/* completion of a writeback.                                          */
/*---------------------------------------------------------------------*/
#define MAP_CIBIT   0x04

#if BSP_CPU != 68030
/*---------------------------------------------------------------------*/
/* MAP_SERBIT will mark the page cache inhibited, serialized. If the   */
/* page is accessed the cache is bypassed, and an external bus transfer*/
/* is performed. If the data to be accessed is present in the cache    */
/* and is dirty (different from memory) then it will be pushed from    */
/* the cache (written to memory) before an access is done to the data. */
/* In this serialized state the sequence of reads and writes to the    */
/* page is guaranteed to match the sequence expected due to instruction*/
/* ordering. The serialized mode also prevents an instruction from     */
/* being interrupted after the operand fetch.                          */
/* NOTE: This is attribute is not supported on the 68030               */
/*---------------------------------------------------------------------*/
#define MAP_SERBIT  0x08

/*---------------------------------------------------------------------*/
/* MAP_CBBIT will mark the page cachable and operate in a copyback     */
/* mode. In copyback mode writes done to the page will cause the dirty */
/* bit to be set in the page's status but no write will be done to     */
/* memory (no external bus access).                                    */
/* NOTE: This is attribute is not supported on the 68030               */
/*---------------------------------------------------------------------*/
#define MAP_CBBIT   0x10

/*---------------------------------------------------------------------*/
/* MAP_SUPBIT will mark the page supervisor only so the page cannot be */
/* accessed in user mode.                                              */
/* NOTE: This is attribute is not supported on the 68030               */
/*---------------------------------------------------------------------*/
#define MAP_SUPBIT  0x20

/*---------------------------------------------------------------------*/
/* ATT_MASK is the mask of the combined attribute bits.  (68040+)      */
/*---------------------------------------------------------------------*/
#define ATT_MASK 0x3F

#else

/*---------------------------------------------------------------------*/
/* ATT_MASK is the mask of the combined attribute bits.  (68030)       */
/*---------------------------------------------------------------------*/
#define ATT_MASK 0x07

#endif

/*---------------------------------------------------------------------*/
/* #endif for mapmmu.h include                                         */
/*---------------------------------------------------------------------*/
#endif

#if __cplusplus
}
#endif

