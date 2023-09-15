/* $Header:   L:/pvcs/1000/psos332/archives/inc/commxmit.h_v   2.3   30 Mar 1997 19:35:34   lmarkure  $ */
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

   Module name:   Comm_XMT_String

   Filename:      commxmit.c

   Written by:  Mark Lazarewicz
         Date:  02/29/96
     Language:  Microtec "C"


 -------------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author   Description
   ==========   ========   ======   ===========
      0         02/29/96   Mark L   Initial Version
      1         05-15-96   BEKymer  Add proper function prototyping
      2         11/10/96   LAM      cleanup warnings
      1             3/30/97      LAM         welddata test
*/

/*
--------------------------- Function Prototypes --------------------------
*/

void CommXmtStringInit(void);

void CommXmtString(
   CIB_INTERFACE_TYPE_TYPE           comm_port,                     /* Designates which SCC port         */
   char                              *str_ptr );     /* Pointer to null terminated string */

void CommQueueString(
   UINT32                            qid,            /* Queue ID to send to               */
   CIB_INTERFACE_TYPE_TYPE           comm_port,                     /* Comm port designator              */
   char                              *str_ptr );     /* Pointer to null terminated string */

void SendCommStringLong(
    char                             *string_ptr,    /* String to transmit            */
    UINT32                           partition_id,   /* partition id of buffer        */
    UINT32                           qid );          /* Protocol Manager Queue ID     */

void SendCommStrWithLength(
    char                             *string_ptr,    /* String to transmit            */
    UINT32                           partition_id,   /* partition id of buffer        */
    UINT32                           qid,            /* Protocol Manager Queue ID     */
    UINT16                           buf_length );   /* NUmber of bytes to transmit   */

void CommXmtBuf(
   CIB_INTERFACE_TYPE_TYPE           comm_port,                     /* Designates which SCC port         */
   UINT32                            partition_id,   /* Partition Id of buffer to send    */
   UINT8                             *buf_ptr,       /* Pointer to buffer                 */
   UINT16                            buf_length );   /* Number of bytes to transmit       */
