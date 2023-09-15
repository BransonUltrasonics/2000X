/* $Header:   D:/SWLab/VMdb/2000Series/BSP/src/qvga_uart.c_v   1.20   Nov 30 2007 11:57:42   bkymer  $ */
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

   Filename:  qvga_uart.c 

            Written by: Shishir Madhugiri 
                  Date: 03/06/03 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      1.0          03/06/03       SCM       Initial Version
      1.1          03/20/03       SCM       Added initialization routine for 68681 UART,
                                            interrupt service routine,FIFO routines and
                                            other miscellaneous routines.
      1.2          04/14/03       SCM       Added test code for India. India will replace 
                                            this code with the actual code after testing.  
      1.3          04/15/03       SCM       Added 'ticks.h' as an include to fix dependency
                                            problem during compile.
      1.4          04/15/03       SCM       Modified code to fix another compile problem.  
      1.5          05/02/03       SCM       Added code to provide XON/XOFF functionality in ISR.
      1.9          05/28/03       SCM       Fixed bug in code for 485 interface.
      1.10         07/10/03       SCM       Added PVCS Header, Detabbing, comments etc.
      1.11         07/31/03       JOY       Set 'QVGAHwAvail' flag when XON/XOFF is
                                            received from the QVGA controller.
      1.12         10/30/03       JOY       'QVGAHwPowerup' replaced by 'QVGAHwAvail' again. 
      1.13         11/14/03       SCM        Added code to check for availability of QVGA.
      1.15         05/12/05       Aare      Implemented VGA-specific interrupt handler.
      1.16         05/12/05       Aare      Corrected tabs, removed test code.
      1.17         07/25/05      Bwadia    RVTS handler message format modified
      1.18         10/11/05      Bwadia    Transmit and recieve buffer bytes modified for 
                                           VGA communication
	  1.19         05-18-06      YGupta    Edited CharReceived() if Invalid command is received 
	                                       and TransmitNak() for Displaylock.
   1.20         11-30-07      BEKymer   Remove QvgaInt - No longer needed                                     
                                        

 ------------------------------- DESCRIPTION -----------------------------------

The file contains code to initialize the 68681 UART, interrupt service routine
and other miscellanous routines. 

 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include <psos.h>
#include "names.h"                        /* psos object definitions          */
#include "opcodes.h" 
#include "qvga_uart.h" 
#include "screenmsg_touch.h" 
#include "portable.h"
#include "ck_qsend.h" 
#include "ticks.h"
#include "ascii.h"     

//Test code only
#include "touchmsg_qvga.h"



/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/
extern UINT8 VerifyLengthAndCode(SINT16 length, UINT16 code);
extern BOOLEAN QVGAHwAvail;
extern UINT32 TsrnQid;     
extern UINT32 qvgasemid;
extern UINT32 tsrnsemid;
extern UINT32 QvgaQid;
extern UINT32 qvgataskid;

RVTS_MSG RvtsMsg;
extern UINT32 RvtsQid;


/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/

/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/
static SINT8 txqvgabuf[512];    // TX buffer for channel A
static SINT8 txtsrnbuf[512];   // TX buffer for channel B

/*
 ------------------------------- GLOBAL DATA -----------------------------------
                        (scope is global to ALL files)
*/
       
UINT16 flags;
static SINT8 intmask;
//BOOLEAN QVGAHwPowerup = FALSE;
/*
 ---------------------------- PRIVATE GLOBAL DATA ------------------------------
                        (scope is global to THIS file)
*/

// maximum needed TX buffer size is defined as
// 'as much as we can send in 50 milliseconds at highest speed that we can use,
// plus some 20 bytes more'
// 50 milliseconds is an arbitrary delay inlocal FifoWrite function when Fifo
// doesn't have space to put a byte in 

#define VGABAUD 9600
#define VGADELAY 50
#define EXTRASPACE 20
#define TXABUFSIZE ((VGABAUD / 10) * 500 / VGADELAY + EXTRASPACE)

// this size should be large enough to fit any host command data part
#define RXABUFSIZE 1024
#define TXBBUFSIZE 512
#define RXBBUFSIZE 512

static Fifo txAfifo;  // Channel A TX FIFO
static Fifo txBfifo;  // Channel B TX FIFO
static SINT8 txAbuf[TXABUFSIZE];	// TX buffer for channel A
static SINT8 txBbuf[TXBBUFSIZE];    // TX buffer for channel B
static SINT8 rxAbuf[RXABUFSIZE];	// RX buffer for channel A
static SINT8 rxBbuf[RXBBUFSIZE];    // RX buffer for channel B

UART_CHANNEL channelA = {
	&txAfifo,
	txAbuf, sizeof(txAbuf),
	rxAbuf, sizeof(rxAbuf),
	0x01,
	0, 0, 0, 0, 0 };

UART_CHANNEL channelB = {
	&txBfifo,
	txBbuf, sizeof(txBbuf),
	rxBbuf, sizeof(rxBbuf),
	0x10,
	0, 0, 0, 0, 0 };
   
Fifo txtsrnfifo;  //Channel A TX FIFO
Fifo txqvgafifo;  // Channel  B TX FIFO

static UINT16 SemAcquiredFlagA =FALSE;
static UINT16 SemAcquiredFlagB =FALSE;
TOUCH_SCRN_MSG  TouchMsgIsr;
static BOOLEAN QVGAtransmit;
BOOLEAN QVGAPresentFlag=FALSE;
UINT16 writeflag;
UINT16 readflag;
//Test Code only
TOUCH_HANDLER_MSG TestTouchmsg;

UINT8 TouchCount = 0;
UINT8 PrevTouch =  'R';
BOOLEAN SendToTouchScrn = FALSE;
UINT8 ValidCommand = FALSE;
                              
/*
 ---------------------------------- CODE ---------------------------------------
*/
UINT8 VerifyLengthAndCode(SINT16 length, UINT16 code);
void CharReceived(UART_CHANNEL * channel, UINT8 ch);
void ProcessCommand(UART_CHANNEL * channel);
void TransmitNAK(UART_CHANNEL * channel);

/******************************************************************************
 This function initializes the 68681 DUART.                                                   
******************************************************************************/
void Init_68681 (void)
{
    
    write68681->modeRegChanA = 0x7B;
    write68681->commandRegA = 0x1A;
    if(read68681->modeRegChanA == 0x7B)
    {       
       write68681->modeRegChanA = 0x2E;
       if(read68681->modeRegChanA == 0x2E) 
       QVGAPresentFlag=TRUE;
       
    }
    write68681->commandRegA = 0x1A;     
    
    if(!QVGAPresentFlag) QVGAHwAvail=FALSE;   
    if(QVGAPresentFlag)
    {
    Fifo_Init(&txqvgafifo, txqvgabuf, sizeof(txqvgabuf));     //Initialize QVGA transmitter FIFO.
    Fifo_Init(&txtsrnfifo, txtsrnbuf, sizeof(txtsrnbuf));     //Initialize Touch Screen transmitter FIFO.
                                                            
    write68681->aux = 0x00;          // ACR[7]=0 selects Set 2 baudrates.
    write68681->outcfg = 0x00;

    // Channel A Initialization  - Touch Screen
    write68681->commandRegA = 0x2A;  // Disable both transmitter and reciever. CRA[6:4]- Reset Channel A reciever
    write68681->commandRegA = 0x3A;  // CRA[6:4]- Reset Channel A transmitter
    write68681->commandRegA = 0x1A;  // CRA[6:4]- Reset mode register pointer to point to MR1.
    write68681->modeRegChanA = 0x13; // MR1 - Set Zero parity, 8 bits.
    write68681->modeRegChanA = 0x07; // MR2 - Set Stop bit =1
    write68681->commandRegA = 0x8A;  // Select appropriate baud rate table values for TX and RX
    write68681->commandRegA = 0xAA;
    write68681->clockRegA = 0xCC;    // Set both transmitter and reciever clock = 9600 Baud.
    write68681->commandRegA = 0x05;  // CRA[6:4]- Enable both transmitter and reciever.

    // Channel B Initialization -QVGA
    write68681->commandRegB = 0x2A;  // Disable both transmitter and reciever. CRB[6:4]- Reset Channel B reciever
    write68681->commandRegB = 0x3A;  // CRB[6:4]- Reset Channel B transmitter
    write68681->commandRegB = 0x1A;  // CRB[6:4]- Reset mode register pointer to point to MR1.
    write68681->modeRegChanB = 0x13; // MR1 - Set Zero parity, 8 bits.
    write68681->modeRegChanB = 0x07; // MR2 - Set Stop bit =1
    write68681->commandRegB = 0x8A;  // Select appropriate baud rate table values for TX and RX              
    write68681->commandRegB = 0xAA;
    write68681->clockRegB = 0x88;    // Set both transmitter and reciever clock = 57.6k Baud.
    write68681->commandRegB = 0x05;  // CRB[6:4]- Enable both transmitter and reciever.

    intmask = 0x22;
    write68681->intmask = intmask;   // Enable Channel A and B reciever interrupts. Disable Channel A and B transmitter interrupts.  
    write68681->bitset = 0x00;
    QVGAtransmit = TRUE;
    }
}



/******************************************************************************
 This routine initializes the transmitter FIFO's.
******************************************************************************/
void Fifo_Init(Fifo * fifo, SINT8 * buffer, UINT16 size)
{
   fifo->buffer = buffer;
   fifo->size = size;
   fifo->read = 0;
   fifo->write = 0;
   fifo->count = 0;
}


/******************************************************************************
 This routine writes data into the buffer. This function is called by the 
 application to write data into the transmitter buffer for use by the ISR                                              
******************************************************************************/
UINT16 Fifo_Write(Fifo * fifo, SINT8 ch)
{

   if (fifo->count >= fifo->size)
   return 0;
    
   asm(" move sr,d0"); /**********   Store status register(SR) contents. ***/
   asm(" move.l d0,-(a7)");   
   asm(" ori #$0700,SR"); /**************  Clear 332 interrupt. *****/
    
   fifo->buffer[fifo->write++] = ch;
   if (fifo->write >= fifo->size)
   fifo->write = 0;
    
   fifo->count++;
   asm(" move.l (a7)+,d0"); /**** Restore status register(SR) contents ***/
   asm(" move d0,sr");
   return 1;
}

// writes a byte into FIFO, waits 50ms if busy (that time should be
// sufficient to free up some space in the FIFO).
void FifoWriteWait(UART_CHANNEL * channel, SINT8 byte)
{
	UINT16 write;

	for (;;)
		{
		write = Fifo_Write(channel->txfifo, byte);
		if (write)
			break;
		else
			tm_wkafter(MS_TO_TICKS(50));
		}
	intmask |= channel->txintmask;
	write68681->intmask = intmask;
}

/******************************************************************************
 This routine reads data from the buffer. This function is called by the 
 ISR to copy data from the transmitter buffer for use by the ISR                                              
******************************************************************************/
UINT16 Fifo_Read(Fifo * fifo, SINT8 * ch)
{

   if (fifo->count <= 0)
   return 0;
    
   asm(" move sr,d0"); /**********   Store status register(SR) contents. ***/
   asm(" move.l d0,-(a7)");
   asm(" ori #$0700,SR"); /************** Clear 332 interrupt. *****/
   
   *ch = fifo->buffer [fifo->read++];
   if (fifo->read >= fifo->size)
   fifo->read = 0;    
   
   fifo->count--;
   asm(" move.l (a7)+,d0");  /**** Restore status register(SR) contents ***/
   asm(" move d0,sr");
   return 1;
}


/******************************************************************************
 This routine returns the number of free locations remaining in the buffer.                                             
******************************************************************************/
UINT16 Fifo_Free(const Fifo * fifo)
{
   return fifo->size - fifo->count;
}



/******************************************************************************
 This routine transmits a character to the designated port(buffer).                                              
******************************************************************************/
UINT16 Serial_Transmit(BOOLEAN port, SINT8 ch)
{
   UINT16 ret;

   // Transmit character to the touch screen transmit buffer.
   if (port==TRUE)
   {
      ret = Fifo_Write (&txtsrnfifo, ch);
      if (ret)
      {
         intmask |= 0x01;  // Enable touch screen Tx interrupt.
         write68681->intmask = intmask;
      }   
   }
   else
   // Transmit character to the QVGA transmit buffer.
   {
      ret = Fifo_Write (&txqvgafifo, ch);
      if (QVGAtransmit)
      {
         intmask |= 0x10;  // Enable QVGA Tx interrupt.
         write68681->intmask = intmask;
      }           
   }
    
   return ret;
}
  
   
/******************************************************************************
 This routine transmits a character to the designated port(buffer).                                              
******************************************************************************/
void QVGA_Transmit(SINT8 * ptr)
{
   UINT16 free;
   if(QVGAPresentFlag)
   {
   while (*ptr) 
   {     
      free = Fifo_Free(&txqvgafifo);
      if (free < ((txqvgafifo.size * 10) / 100))
         t_suspend(0);
      Serial_Transmit(FALSE, *ptr);
      ptr++;
   }
   }
}

/******************************************************************************
 Interrupt Service routine to handle VGA interrupts.
 IRQ5 is used for VGA interrupt.                                              
******************************************************************************/
void VgaInt(void)
{
   SINT8 ch, isr,qvgaRxdata;
   UINT16 free;
   for (;;)
   {
      isr = read68681->isr & intmask;   //Read the ISR register
      if (!isr)
         break;

      // If RxRDY occurs on channel A, get the character and process it
      if (isr & 0x02)
      {
         ch = read68681->recHoldA;
         CharReceived(&channelA, ch);
      }
      // If TxRDY occurs on channel A, send the byte or disable interrupt
      if (isr & 0x01)
      {
         if (Fifo_Read(&txAfifo, &ch))
            write68681->sendHoldA = ch;
         else
         {
            intmask &= 0xFE;  // Disable Tx interrupt for channel A.
            write68681->intmask = intmask;
         }
      }
      // If RxRDY INT occurs on channel B, get the character and process it
      if (isr & 0x20)
      {
         ch = read68681->recHoldB;
         CharReceived(&channelB, ch);
      }
      // If TxRDY occurs on channel B, send the byte or disable interrupt
      if (isr & 0x10)
      {
         if (Fifo_Read(&txBfifo, &ch))
            write68681->sendHoldB = ch;
         else
         {
            intmask &= 0xEF; // Disable Tx interrupt for channel B.
            write68681->intmask = intmask;
         }
      }
   }
}

/******************************************************************************
 This function initializes the 68681 CHANNEL structure for each receiver channel
 in the DUART for VGA.
******************************************************************************/
void InitChannel(UART_CHANNEL * channel)
{
   Fifo_Init(channel->txfifo, channel->txbuf, channel->txbufsize);
   channel->state = STATE_WAIT_FIRST_DLE;
}

/******************************************************************************
 This function initializes the 68681 DUART for VGA. The QVGA init routine had
 too much stuff in it. Assume that this UART is always present
 (pretty obvious, huh?)
******************************************************************************/
void Init_68681_VGA(void)
{
   write68681->modeRegChanA = 0x7B;
   write68681->commandRegA = 0x1A;
   write68681->modeRegChanA = 0x2E;
   write68681->commandRegA = 0x1A;     

   InitChannel(&channelA);
   InitChannel(&channelB);

   write68681->aux = 0x80;          // ACR[7]=1 selects Set 2 baudrates.
//write68681->aux = 0x00;          // ACR[7]=0 selects Set 2 baudrates.
   write68681->outcfg = 0x00;

   // Channel A Initialization - 9600
   write68681->commandRegA = 0x2A;  // Disable both transmitter and reciever. CRA[6:4]- Reset Channel A reciever
   write68681->commandRegA = 0x3A;  // CRA[6:4]- Reset Channel A transmitter
   write68681->commandRegA = 0x1A;  // CRA[6:4]- Reset mode register pointer to point to MR1.
   write68681->modeRegChanA = 0x13; // MR1 - Set Zero parity, 8 bits.
   write68681->modeRegChanA = 0x07; // MR2 - Set Stop bit =1
   write68681->commandRegA = 0x8A;  // Select appropriate baud rate table values for TX and RX
   write68681->commandRegA = 0xAA;
   write68681->clockRegA = 0xCC;    // Set both transmitter and reciever clock = 9600 Baud.
   write68681->commandRegA = 0x05;  // CRA[6:4]- Enable both transmitter and reciever.

   // Channel B Initialization - 57600
   write68681->commandRegB = 0x2A;  // Disable both transmitter and reciever. CRB[6:4]- Reset Channel B reciever
   write68681->commandRegB = 0x3A;  // CRB[6:4]- Reset Channel B transmitter
   write68681->commandRegB = 0x1A;  // CRB[6:4]- Reset mode register pointer to point to MR1.
   write68681->modeRegChanB = 0x13; // MR1 - Set Zero parity, 8 bits.
   write68681->modeRegChanB = 0x07; // MR2 - Set Stop bit =1
   write68681->commandRegB = 0x8A;  // Select appropriate baud rate table values for TX and RX
   write68681->commandRegB = 0xAA;
   write68681->clockRegB = 0xCC;    // Set both transmitter and reciever clock = 9.6k Baud.
//   write68681->clockRegB = 0x88;    // Set both transmitter and reciever clock = 57.6k Baud.
   write68681->commandRegB = 0x05;  // CRB[6:4]- Enable both transmitter and reciever.

   intmask = 0x22;
   write68681->intmask = intmask;   // Enable Channel A and B reciever interrupts. Disable Channel A and B transmitter interrupts.
   write68681->bitset = 0x00;
}

void CharReceived(UART_CHANNEL * channel, UINT8 ch)
{

	//if(ch ==ETX)
	//SPrintf(Buffer, "%02d \n\r", ch&0xFF);

   switch (channel->state)
      {
   case STATE_WAIT_FIRST_DLE :
      if (ch == DLE)
         channel->state = STATE_WAIT_STX;
	  else if(ValidCommand)
		{
			ValidCommand=FALSE;
			TransmitNAK(channel);
		}
	  break;


   case STATE_WAIT_STX :
      if (ch == STX)
         channel->state = STATE_WAIT_LENGTH1;
      else 
	  {
         channel->state = STATE_WAIT_FIRST_DLE;
		 if(ValidCommand)
		{
			ValidCommand=FALSE;
			TransmitNAK(channel);
		}
		break;
	  }
      channel->checksum = 0;
      break;

   case STATE_WAIT_LENGTH1 :
      channel->length = ch << 8;
      channel->checksum ^= ch;
      channel->state = STATE_WAIT_LENGTH2;
      break;

   // here we ignore the command that has more than RX buffer size
   // worth of data, nowhere to store it so might just throw it away...
   case STATE_WAIT_LENGTH2 :
      channel->length |= ch;
      channel->checksum ^= ch;
      if (channel->length > channel->rxbufsize + 4)
         channel->state = STATE_WAIT_FIRST_DLE;
      else
         channel->state = STATE_WAIT_CODE1;
      break;

   case STATE_WAIT_CODE1 :
      channel->code = ch << 8;
      channel->checksum ^= ch;
      channel->state = STATE_WAIT_CODE2;
      break;

   case STATE_WAIT_CODE2 :
      channel->code |= ch;
      channel->checksum ^= ch;
      channel->rxindex = 0;
      channel->length -= 4;
	  if(!VerifyLengthAndCode(channel->length,channel->code))
	  {
		 

		  channel->state = STATE_WAIT_FIRST_DLE;
		  if(ValidCommand)
		  {
			  ValidCommand=FALSE;
			  TransmitNAK(channel);
		  }
		  break;
	  }
      if (channel->length == 0)	// no data, just length and code
         channel->state = STATE_WAIT_CRC;
      else
         channel->state = STATE_WAIT_DATA;
      break;

   case STATE_WAIT_DATA :
      channel->rxbuf[channel->rxindex++] = ch;
      channel->checksum ^= ch;
      if (channel->rxindex >= channel->length)
         channel->state = STATE_WAIT_CRC;
      break;

   case STATE_WAIT_CRC :
      channel->checksum ^= ch;
      channel->state = STATE_WAIT_SECOND_DLE;
      break;

   case STATE_WAIT_SECOND_DLE :
      if (ch == DLE)
         channel->state = STATE_WAIT_ETX;
      else
	  {
         channel->state = STATE_WAIT_FIRST_DLE;
		 if(ValidCommand)
		{
			ValidCommand=FALSE;
			TransmitNAK(channel);
		}
		
	  }
      break;

   case STATE_WAIT_ETX :
      if (ch == ETX)
         ProcessCommand(channel);
	  else if(ValidCommand)
		{
			ValidCommand=FALSE;
			TransmitNAK(channel);
		}
		
	 
      channel->state = STATE_WAIT_FIRST_DLE;
      break;

   default :
      channel->state = STATE_WAIT_FIRST_DLE;
      }
}
// The assumption here is that the welder receives next request only after
// this one is processed, so as long as we guarantee that on the other end
// we don't go into transmitter FIFO buffer overruns and we won't get stuck
// in the interrupt handler.

void ProcessCommand(UART_CHANNEL * channel)
{
   if (channel->checksum == 0)	// good checksum
   {
	  ValidCommand= TRUE;
      RvtsMsg.common.source_task = SERIAL_INTERRUPT;
      RvtsMsg.channel = channel;
      RvtsMsg.common.opcode = OP_TOUCH_SCRN_MSG_READY;
      q_send(RvtsQid, &RvtsMsg);
   }
   else
   {
      TransmitNAK(channel);
   }
}

// This function is called from interrupt handler. It assumes that there
// is always enough space in the transmitter Fifo to store a NAK host command
// response. We don't want to delay anything in interrupt handler to wait for
// transmitter buffer to free up...
// Basant! I'm quite sure this is not the NAK we should send...

void TransmitNAK(UART_CHANNEL * channel)
{
   UINT8 ch;
   UINT8 checksum = 0x00;

   Fifo_Write(channel->txfifo, NAK);
   Fifo_Write(channel->txfifo, DLE);
   Fifo_Write(channel->txfifo, STX);

   ch = 0x00;
   checksum ^= ch;
   Fifo_Write(channel->txfifo, ch);

   ch = 0x05;
   checksum ^= ch;
   Fifo_Write(channel->txfifo, ch);

   ch = channel->code >> 8;
   checksum ^= ch;
   Fifo_Write(channel->txfifo, ch);

   ch = channel->code & 0xFF;
   checksum ^= ch;
   Fifo_Write(channel->txfifo, ch);

   ch = 0x00;
   checksum ^= ch;
   Fifo_Write(channel->txfifo, ch);

   Fifo_Write(channel->txfifo, checksum);
   Fifo_Write(channel->txfifo, DLE);
   Fifo_Write(channel->txfifo, ETX);

   intmask |= channel->txintmask;
   write68681->intmask = intmask;
}
