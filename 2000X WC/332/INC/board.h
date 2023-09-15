/* @(#) pSOSystem/68K V2.2.2: bsps/e302/src/board.h (fads) 2.14 97/03/31 13:34:27 */
/* $Header:   K:/APPS/PVCS Pro/332new/INC/BOARD.H_V   2.4   Apr 28 1999 15:29:48   lmarkure  $ */

/***********************************************************************/
/*                                                                     */
/*   MODULE:  bsps/e302/src/board.h                                    */
/*   DATE:    97/03/31                                                 */
/*   PURPOSE: Board dependant definitions for portable drivers         */
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
/***********************************************************************/
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version
 2.4   04/05/99 LAM     Updated to new version of psos on 332 board

*/

#if __cplusplus
extern "C" {
#endif

#ifndef _BOARD_H
#define _BOARD_H

/*---------------------------------------------------------------------*/
/* Needed definitions in other include files.                          */
/*---------------------------------------------------------------------*/
#include <m68332.h>


#define BD_REGS_BASE 0x0f00000
#define BD_M68332_HZ 0x17801d0
#define BD_SER_IRQ_LEVEL 0x04





/*---------------------------------------------------------------------*/
/* Base of non-volitale RAM.                                           */
/*---------------------------------------------------------------------*/
#define BD_NVBASE       (0x168000)
#define BD_NVSTEP_SIZE  1 
#define BD_NV_ALLOW_WRITE
#define BD_NV_PROTECT  
/* #define BD_NV_VERIFY  */
#define BD_NV_WRITE_DONE(x, y) 
#define BD_NV_TIMEOUT 


#endif /* _BOARD_H */

#if __cplusplus
}
#endif
