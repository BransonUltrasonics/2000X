/* @(#) pSOSystem/68K V2.2.2: bsps/template/src/68k/nvram.c (&U&) 2.12 98/01/14 11:30:18 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  devices/nvram.c                                          */
/*   DATE:    98/01/14                                                 */
/*   PURPOSE: Parameter storage and retrieval of non-volatile area     */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1996, Integrated Systems, Inc.           */
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
/*        StorageRead        Read from non-volatile memory             */
/*        StorageWrite       Write to non-volatile memory              */
/*                                                                     */
/***********************************************************************/
#include <types.h>
#include "board.h"

/*---------------------------------------------------------------------*/
/* The following macros are mandatory and must be defined in board.h:  */
/* BD_NVBASE                                                           */
/*   - The base address of the non-volatile RAM.                       */
/*   - [If defined  as -1, the nvram code discards writes, and zeroes  */
/*     nvram read requests.]                                           */
/*                                                                     */
/* The folowing macros are optional and may be used to alter the       */
/* functionality of the StrorageRead and StorageWrite routines:        */
/* BD_NVSTEP_SIZE                                                      */
/*   - Used to specify non adjacent bytes for nvram. 1 is every byte   */
/*     (the default). 2 is every other byte. 4 is every four byte.     */
/*                                                                     */
/* BD_NV_ALLOW_WRITE                                                   */
/*   - Turn off any write protection for the nvram.                    */
/*                                                                     */
/* BD_NV_PROTECT                                                       */
/*   - Turn on  any write protection for the nvram.                    */
/*                                                                     */
/* BD_NV_VERIFY                                                        */
/*   - Flag to signify that the previous value must be verified before */
/*     attempting to write the next. Defining BD_NV_VERIFY requires    */
/*     that BD_NV_TIMEOUT and BD_NV_WRITE_DONE are also defined.       */
/*                                                                     */
/* BD_NV_TIMEOUT                                                       */
/*   - The number of times to try verify the write before giving up.   */
/*     This prevents infinite loops caused by faulty non-volative RAM. */
/*                                                                     */
/* BD_NV_WRITE_DONE                                                    */
/*   - The test to perform to detemine if the write is complete. It    */
/*     takes two parameters the first is the destination byte address. */
/*     The second is the source byte address. The macro result in a    */
/*     boolean value. True, if the write is done. False, if not done.  */
/*     For example if a part returns the inverted value until the      */
/*     write is done the macro may be written as:                      */
/*         #define BD_NV_WRITE_DONE(x, y) (*(x) == *(y))               */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* The StorageRead and StorageWrite routines usually work on devices   */
/* which have the bytes in adjacent positions in the address space.    */
/* If working with a device which doesn't decode the lower address     */
/* lines, then BD_NVSTEP_SIZE can be defined to override the default.  */
/* For example if A0-A1 are not decoded the BD_NVSTEP_SIZE would be 4. */
/* BD_NVSTEP_SIZE is defined in board.h if used.                       */
/*---------------------------------------------------------------------*/
#ifndef BD_NVSTEP_SIZE
#define BD_NVSTEP_SIZE 1
#endif

#ifndef BD_NV_ALLOW_WRITE
#define BD_NV_ALLOW_WRITE
#endif

#ifndef BD_NV_PROTECT
#define BD_NV_PROTECT
#endif

extern void Delay100ms(void);

/***********************************************************************/
/*   StorageRead: Read from non-volatile memory                        */
/*                                                                     */
/*      INPUTS: nbytes = Number of bytes to read                       */
/*              Start  = address to read from                          */
/*              buff   = address to write to                           */
/*                                                                     */
/*     RETURNS: NONE                                                   */
/*     OUTPUTS: NONE                                                   */
/*     NOTE(S): This function copies from non-volatile memory to       */
/*              the given data buffer. The code for StorageRead that   */
/*              is shown here is a very simple function but your       */
/*              hardware may need a different approach.                */
/*              BD_NVBASE should be defined in board.h as the          */
/*              starting address of non-volatile storage area.         */
/*                                                                     */
/***********************************************************************/
void StorageRead(UINT nbytes, void *Start, void *buff)
{
volatile UCHAR *src, *dst;
 
dst = (UCHAR *)buff;
src = (UCHAR *)BD_NVBASE;

if(src == (UCHAR *)-1)
    {
    while(nbytes--)
        *dst++ = 0;
    }
else
    {
    src += (ULONG)Start * BD_NVSTEP_SIZE;

    while (nbytes--)
        {
        *dst++ = *src;
        src += BD_NVSTEP_SIZE;
        }
    }
}
 
/***********************************************************************/
/*  StorageWrite: Write to non-volatile memory                         */
/*                                                                     */
/*      INPUTS: nbytes = Number of bytes to write                      */
/*              Start  = address to read from                          */
/*              buff   = address to write to                           */
/*                                                                     */
/*     RETURNS: NONE                                                   */
/*     OUTPUTS: NONE                                                   */
/*     NOTE(S): This function copies from the given data buffer to     */
/*              non-volatile memory. The code for StorageWrite that is */
/*              shown here is a very simple function but your hardware */
/*              may need a different approach.                         */
/*              BD_NVBASE should be defined in board.h as the starting */
/*              address of non-volatile storage area.                  */
/*                                                                     */
/***********************************************************************/
void StorageWrite(UINT nbytes, void *Start, void *buff)
{
volatile UCHAR *src, *dst;

#ifdef BD_NV_VERIFY
    register int timeout;
#endif
 
dst = (UCHAR *)BD_NVBASE;
if(dst != (UCHAR *)-1)
    {
    dst += (ULONG)Start * BD_NVSTEP_SIZE;
    src = (UCHAR *)buff;
    BD_NV_ALLOW_WRITE;

    while (nbytes--)
        {
        *dst = *src;

        #ifdef BD_NV_VERIFY
             #ifndef BD_NV_WRITE_DONE
             #error BD_NV_WRITE_DONE must be specified when BD_NV_VERIFY is.
             #endif
             #if BD_NV_TIMEOUT <= 0
             #error BD_NV_TIMEOUT must be specified when BD_NV_VERIFY is.
             #endif

             timeout = BD_NV_TIMEOUT;

            /*---------------------------------------------------------*/
            /* Wait until the write is done or we time out.            */
            /*---------------------------------------------------------*/
            while (!BD_NV_WRITE_DONE(dst, src))
                {
                if (timeout < 1)
                    {
                    BD_NV_PROTECT;
                    return;
                    }
                Delay100ms();
                timeout--;
                }
        #endif

        dst += BD_NVSTEP_SIZE;
        src++;
        }
    BD_NV_PROTECT;
    }
}

