/* $Header:   D:/SWLab/VMdb/2000Series/INC/qvga_uart.h_v   1.7   Jul 25 2005 13:47:12   bwadia  $ */
#ifndef QVGA_UART_H
#define QVGA_UART_H
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

   Module name:   
   Filename:      qvga_uart.h


            Written by: Shishir Madhugiri 
                  Date: 03/06/03   
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========

   1.0             03/06/03      SCM         Initial Version.
   1.1             03/20/03      SCM         Added function prototypes, structure definitions
                                             for qvga_uart.c
   1.3             05/28/03      SCM         Added prototype for QVGA_Transmit().  
   1.4             07/10/03      SCM         Added PVCS Header.  
   1.5             08/22/03      SCM         Converted tabs to spaces.
   1.6             05/12/05      Aare        Added structures for VGA interrupt handler.
   1.7             07/25/05      Bwadia      RVTS_MSG and UART_CHANNEL structure modified        
    
 ------------------------------- DESCRIPTION -----------------------------------
        
 
 ------------------------------ INCLUDE FILES ----------------------------------
*/  

#include "portable.h"
#include "genrlmsg.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

#define read68681 ((read68681addr *) 0x142810)     // Memory location of the 68681 UART.
#define write68681 ((write68681addr *) 0x142810)


/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

// The following represents the register map for the 68681 UART in the READ mode
typedef __packed__ struct {
    SINT8 modeRegChanA;
    SINT8 statusRegChanA;
    SINT8 test;
    SINT8 recHoldA;
    SINT8 inputchange;
    SINT8 isr;
    SINT8 counterMSB;
    SINT8 counterLSB;
    SINT8 modeRegChanB;
    SINT8 statusRegChanB;
    SINT8 test0A;
    SINT8 recHoldB; 
    SINT8 intvect;
    SINT8 inputs;
    SINT8 startcounter;
    SINT8 stopcounter;
    } read68681addr;


// The following represents the register map for the 68681 UART in the WRITE mode
typedef __packed__ struct {
    SINT8 modeRegChanA; 
    SINT8 clockRegA;    
    SINT8 commandRegA;  
    SINT8 sendHoldA;    
    SINT8 aux;  
    SINT8 intmask;  
    SINT8 ctur;
    SINT8 ctlr; 
    SINT8 modeRegChanB;   
    SINT8 clockRegB;
    SINT8 commandRegB;
    SINT8 sendHoldB;
    SINT8 intvect;
    SINT8 outcfg;
    SINT8 bitset;
    SINT8 bitreset; 
    } write68681addr;


// Structure of the FIFO buffer
typedef struct {
    SINT8 * buffer;
    UINT16 size;
    UINT16 read;
    UINT16 write;
    UINT16 count;
    } Fifo;
           
typedef enum {
   STATE_WAIT_FIRST_DLE,	// waiting for first DLE
   STATE_WAIT_STX,		// waiting for STX after DLE
   STATE_WAIT_LENGTH1,	// waiting for upper byte of length
   STATE_WAIT_LENGTH2,	// waiting for lower byte of length
   STATE_WAIT_CODE1,	// waiting for upper byte of command code
   STATE_WAIT_CODE2,	// waiting for lower byte of command code
   STATE_WAIT_DATA,
   STATE_WAIT_CRC,
   STATE_WAIT_SECOND_DLE,	// waiting for second DLE
   STATE_WAIT_ETX,		// waiting for ETX after DLE
   } CHANNEL_STATE;

typedef struct {
   Fifo * txfifo;               // transmitter FIFO
   SINT8 * txbuf;               // FIFO ring buffer data
   UINT16 txbufsize;            // FIFO ring buffer size
   SINT8 * rxbuf;               // receiver buffer data (for data part of command)
   UINT16 rxbufsize;            // receiver buffer size
   UINT8 txintmask;             // bit to set to enable transmitter
   CHANNEL_STATE state;         // receiver state machine
   SINT16 length;               // host command length
   UINT16 code;                 // host command code
   UINT16 rxindex;              // pointer into receiver buffer
   UINT8 checksum;              // host command checksum
   } UART_CHANNEL;

typedef struct {
   COMMON_MSG_FIELD_TYPE  common;
   UART_CHANNEL * channel;
   } RVTS_MSG;

/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void Init_68681 (void);
void QvgaInt(void);
void Fifo_Init(Fifo * fifo, SINT8 * buffer, UINT16 size);
UINT16 Fifo_Write(Fifo * fifo, SINT8 ch);
UINT16 Fifo_Read(Fifo * fifo, SINT8 * ch);
UINT16 Fifo_Free(const Fifo * fifo);
UINT16 Serial_Transmit(BOOLEAN port, SINT8 ch);
void QVGA_Transmit(SINT8 * ch);
void cl332int(void);    
void  getstatus(void);
void  setstatus(void);
//BOOLEAN DisableTXInt(void);   
//void EnableTXInt(void);

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif  
