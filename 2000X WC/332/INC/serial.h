/* $Header:   K:\APPS\PVCS Pro\332new\INC\SERIAL.H_V   2.14   Dec 16 1999 15:42:54   lmarkure  $ */
#ifndef SERIAL_H
#define SERIAL_H
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
------------------------------ MODULE DESCRIPTION -----------------------------

------------------------------ REVISIONS --------------------------------------

   Revision #      Date          Author          Description
   ==========      ========      ======          ===========
      0            02/22/96      Mark Lazarewicz Initial release 
      1            03/30/97      LAM             welddata test
      2            04/08/97      LAM             deleted unused functions
      3            04/21/97      LAM             1line data version
      4            04/28/97      LAM             cleanup            
      5.2.10       06/17/97      LAM             deleted comparam.h
      6.2.11       06/17/97      LAM             deleted rx_buffer,reduced xmitbuf
      7.2.12       09.11.97      JBerman         Changed proto SerialPollConout(SINT8 ch);
   	  2.13         12.31.97      BJB             Deleted prototypes of functions
  	                                             removed with Ascent terminal code.
       2.14        12/16/99      LAM             removed unused error handling code
----------------------------- DESCRIPTIONS ------------------------------------

    
   

---------------------------- INCLUDE FILES ------------------------------------
*/
#include "root.h"


#define MAX_TERM_TX_MESSAGE_LENGTH 1000

#define tRANSMIT_ENABLE         SCI_Ctrl_Reg1 |= TRANSMITTER_EN;
#define tRANSMIT_DISABLE        SCI_Ctrl_Reg1 &= ~TRANSMITTER_EN;

#define rECEIVE_ENABLE          SCI_Ctrl_Reg1 |= RECEIVER_EN;
#define rECEIVE_DISABLE         SCI_Ctrl_Reg1 &= ~RECEIVER_EN;

/************************************************************************/
/* Macros to return to a selected byte of a LONG. These are useful to   */
/* rearrange addresses exchanged with a terminal  which uses Intel byte */
/* order.                                                               */
/************************************************************************/

#define bYTE4(x)                  ((BYTE) x )
#define bYTE3(x)                  ((BYTE)(x >> 8) ) 
#define bYTE2(x)                  ((BYTE)(x >> 16) ) 
#define bYTE1(x)                  ((BYTE)(x >> 24) ) 

UINT16 SerialMessageQueue(UINT8 *buf, UINT16 cnt );
void isr_uart(void);
SYS_STARTUP_STATUS_TYPE SerialSetup(UINT32 baud_rate);
void SerialPollInit(void);
void SerialPollOn(void);
void SerialPollOff(void);
UINT32 SerialPollConsts(void);
BYTE SerialPollConin(void);
void SerialPollConout(SINT8 ch);
UINT32 SerialIntBaud(UINT32 baud_rate);
void SerialIntRxion(void);
void SerialIntRxioff(void);
void SerialIntTxion(void);
void SerialIntTxioff(void);
UINT32 SerialIntWrite(BYTE ch);
#endif
