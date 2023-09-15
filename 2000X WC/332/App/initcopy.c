/* $Header:   K:/APPS/PVCS Pro/332new/App/INITCOPY.C_V   2.5   Apr 30 1999 13:32:24   lmarkure  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  initcopy

   Filename:  initcopy.c
               
            Written by: Mark Lazarewicz
                  Date:  02/15/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author    Description
   ==========   ========   ======    ===========
      0         02/15/96   Mark L    Initial Version
      1         05-15-96   BEKymer   Added void to function
      2.3       05-01-98   BJB       Added RunConstructors(), RunDestructors()
                                      for C++ support.
	  2.4       04-23-99   OFI       Changed for DIAB
      2.5       04-30-99   LAM       eliminated error

 ------------------------------- DESCRIPTION -----------------------------------

   This is an initialization routine to copy the initialized data to RAM space
   based on organized information stored in the special section assigned through
   the linker command INITDATA.

 ------------------------------- PSEUDO CODE -----------------------------------

   This routine will scan through the section ??INITDATA and copy data based on
   the special bytes indicated.  The content of each individual input section
   is specified in the INITDATA linker command.  The special bytes are:

        S  means the start of a section;
        C  means operation COPY;
        E  means the end of a section.

   The four bytes after byte 'C' indicate the size of that section; the next
   four bytes after that specify the copy destination.

 ------------------------------ LOCAL EQUATES ----------------------------------
*/
/*
 ------------------------------- EXPORT DATA -----------------------------------

 ------------------------------- IMPORT DATA -----------------------------------
*/

#include "portable.h"
#include <prepc.h>

/*
 ------------------------------- LOCAL DATA ------------------------------------
*/

/*
 ---------------------- IMPORT SUBROUTINES REFERENCED --------------------------
                              
 ---------------------------------- CODE ---------------------------------------
*/


void InitCopy(void)
   {
  /* register  char            *local;
   register  UINT32	     size, dest;

   local = (char *) ASM(" move.l #.startof.(??INITDATA),d0");
   if (*local != 'S')
      while (1);                            /* Failed -- no starting point.   */

  /* local++;
   while (*local != 'E')
      {
      switch (*local)
         {
         case 'C':
            local++;
            size = (UINT32)        ( ((UINT8) *local     << 24) |
                                     ((UINT8) *(local+1) << 16) |
                                     ((UINT8) *(local+2) <<  8) |
                                      (UINT8) *(local+3) );
            local += 4;
            dest = (UINT32) ( ((UINT8) *local     << 24) |
                                     ((UINT8) *(local+1) << 16) |
                                     ((UINT8) *(local+2) <<  8) |
                                      (UINT8) *(local+3) );
            local += 4;
            memcpy( (void *) dest, (void *) local, (size_t) size);
            local += size;
            break;
         default:
            while (1);                      // Failed -- unknown operation.   
         }
      }
   }   */
}
void RunConstructors(void)
{
  /* UINT32 ConstructCount;
	void (**ConstructFunc)(void);

	ConstructFunc = asm( void(**)(void), " move.l #.startof.(initfini),d0" );
   ConstructCount = asm( UINT32, " move.l #.sizeof.(initfini),d0" );
   ConstructCount /= 8;

	while (ConstructCount--)
	{
		(**ConstructFunc)();
		ConstructFunc += 2;
	} */
}

void RunDestructors(void)
{
 /*  UINT32 DestructCount;
   void (**DestructFunc)(void);

   DestructFunc = asm( void(**)(void), " move.l #.startof.(initfini),d0" );
   DestructFunc++;
   DestructCount = asm( UINT32, " move.l #.sizeof.(initfini),d0" );
   DestructCount /= 8;

   while (DestructCount--)
   {
      (**DestructFunc)();
      DestructFunc += 2;
   } */
}
