/* @(#) pSOSystem/68K V2.2.2: bsps/e302/src/board.c (e302) 1.31 97/03/21 16:40:07 */
/* $Header:   K:/APPS/PVCS Pro/PSS68k.222/BSP/src/board.c_v   1.4   Apr 28 1999 16:09:20   ofingere  $ */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  /src/board.c                                             */
/*   DATE:    97/03/21                                                 */
/*   PURPOSE: Board-level code                                         */
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
/*---------------------------------------------------------------------*/
/*                                                                     */
/*   The routines in this module perform board-level functions.        */
/*                                                                     */

/*
 ---------------------------- MODULE DESCRIPTION ----------------------
  Name: board.c

 --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version
 1.1   04/05/99 LAM     Updated per 2.6 from the old project
 1.2   04/05/99 LAM     Updated file to run on our hardware and the
                        new version of pSOS.
 1.3   04/27/99 LAM     fixed includes
 1.4   04/28\99 OFI		fixed sysinit.h
*/


#include <types.h>
#include <bspfuncs.h>
#include <psos.h>
#include <disi.h>
#include "sysinit.h"
#include <ser332.h>
#include "serial.h"
#include "bsp.h"
#include "board.h"


/*---------------------------------------------------------------------*/
/* Global variables.                                                   */
/*---------------------------------------------------------------------*/

ULONG CPU_MHz;      /* The CPU clock speed in MHz */



/***********************************************************************/
/* InitBoard: Initialize the board specific hardware                   */
/*                                                                     */
/*      INPUTS: NONE                                                   */
/*                                                                     */
/*     RETURNS: NONE                                                   */
/*     OUTPUTS: NONE                                                   */
/*                                                                     */
/*     NOTE(S): This function is called from the assembly language     */
/*              file init.s                                            */
/*                                                                     */
/*              The following is a list of functionality that might be */
/*              needed:                                                */
/*                                                                     */
/*              Ram set up  - may included setting of base registers,  */
/*              ram speed, parity enable, ram enable and               */
/*              initialization of...  parity memory.                   */
/*                                                                     */
/*              CPU caches  - set to a default state, You may need to  */
/*              write data in the data cache out to memory and turn    */
/*              instruction and data cache off and invalidate both     */
/*              caches.                                                */
/*                                                                     */
/*              CPU control registers - set all CPU control registers  */
/*              to a default state.                                    */
/*                                                                     */
/***********************************************************************/
void InitBoard(void)
{

   QSM_Int_Vect_Reg = V_SERIAL;            /* Sets V_QSPI also */

/*---------------------------------------------------------------------*/
/* Set the CPU_MHz variable. This variable may be used in the timer,   */
/* lan and scsi drivers.                                               */
/* If none of the drivers in your board suport package need it the     */
/* CPU_MHz variable should be omitted.                                 */
/*---------------------------------------------------------------------*/
   CPU_MHz = 25;


/*---------------------------------------------------------------------*/
/* Clear the zerovars section.                                         */
/*---------------------------------------------------------------------*/
   SysInitVars();

/*---------------------------------------------------------------------*/
/* Call SysInit to configure the components then                       */
/* transfer control to pSOS/pROBE/Application. DOES NOT RETURN.        */
/*---------------------------------------------------------------------*/
   SysInit();

}

/***********************************************************************/
/* ClrAbortInt: Clear interrupt caused by front panel "abort" switch   */
/*                                                                     */
/*      INPUTS: NONE                                                   */
/*                                                                     */
/*     RETURNS: NONE                                                   */
/*     OUTPUTS: NONE                                                   */
/*     NOTE(S):                                                        */
/*              This function is used as an interrupt function in      */
/*              probecfg.c to set the interrupt vector for the abort   */
/*              interrupt. All it needs to do is clear the interrupt.  */
/*                                                                     */
/***********************************************************************/
void ClrAbortInt(void)
{

}

/***********************************************************************/
/* RamSize: Get the size of onboard DRAM                               */
/*                                                                     */
/*      INPUTS: NONE                                                   */
/*                                                                     */
/*     RETURNS: A unsigned long containing DRAM size in bytes          */
/*     OUTPUTS: NONE                                                   */
/*     NOTE(S): This function could also be hardcoded as a #define     */
/*              It maybe used by any functon that needs to know how    */
/*              much DRAM the system contains. It is used to configure */
/*              the system by the files sysinit.c, psoscfg.c,          */
/*              and pnacfg.c in the configs/std directory.             */
/*                                                                     */
/***********************************************************************/
ULONG RamSize(void)
{
   return 0x40000;
}

/***********************************************************************/
/* SysInitFail: Report a system initalization failure                  */
/*                                                                     */
/*      INPUTS: pointer to a character string that contains error      */
/*              string.                                                */
/*                                                                     */
/*     RETURNS: NEVER RETURNS                                          */
/*     OUTPUTS: continually prints a error string                      */
/*     NOTE(S):                                                        */
/*              This function is called during system startup from     */
/*              files in the configs/std directory when an             */
/*              unrecoverable error occurs.                            */
/*                                                                     */
/***********************************************************************/
void SysInitFail(const char *string)      
{
   
   const char *ptr;
   int i;

   Delay100ms();
   Delay100ms();
   for (;;)
   {
      ptr = string;
      while (*ptr)  
         SerialPollConout(*ptr++);
      SerialPollConout('\n');
      SerialPollConout('\r');
      for (i = 1; i <= 10; i++)
        Delay100ms();
   }
}

void Delay100ms(void)
{
  int i;

for (i = 0; i < 32000; i++)
    ;
}


