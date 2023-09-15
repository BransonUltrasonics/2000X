/* @(#) pSOSystem/68K V2.2.2: bsps/devices/serial/ser332.h 2.1 96/01/18 13:27:45 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  bsps/devices/serial/ser332.h                             */
/*   DATE:    96/01/18                                                 */
/*   PURPOSE: Definitions for the 68332 SCI serial port.               */
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
#if __cplusplus
extern "C" {
#endif

#ifndef _SER332_H
#define _SER332_H

/*---------------------------------------------------------------------*/
/* Declarations for the multiplexed serial entry points.               */
/*---------------------------------------------------------------------*/


void ser332_Init(void);
long ser332_Open(ULONG, ChannelCfg *, Lid *, ULONG *);
long ser332_Send(Lid, mblk_t *);
long ser332_Ioctl(Lid, ULONG, void *);
long ser332_Close(Lid);

#endif /* _SER332_H */

#if __cplusplus
}
#endif
