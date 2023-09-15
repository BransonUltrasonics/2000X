/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\INCLUDE\apdialog.h_v   1.0   Mar 29 1999 13:48:14   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/apdialog.h 2.9 95/09/05 13:55:02 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/apdialog.h                                       */
/*   DATE:    95/09/05                                                 */
/*   PURPOSE: Function prototypes for application/dialog interface     */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1993, Integrated Systems, Inc.           */
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
#ifndef _APDIALOG_H
#define _APDIALOG_H

#include <types.h>

typedef enum parm_type
    {
    FLAG = 1, IP = 2, HEX = 3, DECIMAL = 4, CHAR = 5, STRING = 6
    } PARM_TYPE;

void AppGetdefaults(void *ParmStruct);

void AppPrint(void *ParmStruct, ULONG(*PrintRoutine)(char *format, ...));

void AppModify(void *ParmStruct,
   ULONG (*PrintRoutine)(char *format, ...),
   void (*PromptRoutine)(char *prompt, PARM_TYPE ptype, void *paramptr));

void AppUse(void *ParmStruct);

#endif

#if __cplusplus
    }
#endif
