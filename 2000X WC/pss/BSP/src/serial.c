/* $Header:   D:/SWLab/VMdb/2000Series/BSP/src/serial.c_v   1.5.1.0   Apr 19 2005 16:24:18   atali  $ */
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/* Copyright (c) Branson Ultrasonics Corporation, 1995                      */
/* This program is the property of Branson Ultrasonics Corporation          */
/* Copying of this software is expressly forbidden, without the prior       */
/* written consent of Branson Ultrasonics Corporation.                      */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

Module name: Serial Support

Filename:    Serial.c

Function name:

Written by: Mark Lazarewicz
 Date:  02/21/96
 Language:  "C"

-------------------------------- REVISIONS ------------------------------------

 Rev #      Date          Author      Description
 =====      ========      ======      ===========
 1.0        04/06/99      LAM         Updated per new version of psos, made from
                                      ver 2.33                                  
 1.1        04/29/99      LAM         fixed m68332.h
 1.2        09/27/99      LAM         adjusted baud rate to 9747
 1.3 	    09/30/99      OFI         adjusted baud rate to faster
 1.4        12/16/99      LAM         removed unused error handling code  
 1.5        12/14/00      LAM         adjusted baud rate for system clock of 24_117Mhz
 1.5.1.0    04/19/05      Aare        increased outgoing serial buffer to 5000 bytes
                                      for VGA menu host commands

 ------------------------------- DESCRIPTION -----------------------------------

*/



#include <psos.h>
#include <m68332.h>
#include "board.h"
#include "root.h"
#include "bsp.h"
#include "menu7a.h"
#include <bspfuncs.h>
#include "names.h"
#include "serial.h"
#include "rxcharcv.h"
#include "string.h"

#ifndef XON
#define XON  0x11
#define XOFF 0x13
#endif

/*---------------------------------------------------------------------*/
/* General Definitions                                                 */
/*---------------------------------------------------------------------*/
#define NULL    0
#define TAB     ('\t')      /* tab                                 */
#define FF      ('\f')      /* form feed                           */
#define CR      ('\r')      /* carriage return                     */
#define LF      ('\n')      /* line feed                           */
#define SPC     (' ')       /* space/blank                         */
#define BEL     (0x07)      /* bell character                      */

/*---------------------------------------------------------------------*/
/* BrkRcvd indicates if a break has been received on the               */
/* channel. It is used in isr_uart() and SerialPollConsts().           */
/*---------------------------------------------------------------------*/

static BYTE BrkRcvd;        /* indicates if a break was received */
static UINT8 SaveQSMIntLevel;    /* Save SCI state while in pROBE */
static UINT16 SaveSCICtrlReg1;

static UINT8 SerialBuffer[5000];
static UINT16 SrlPut=0;
static UINT16 SrlGet=0;

void CommAsciiCharRcvd( UINT8 ByteReceived );
static void SerialTransmit(void);

static void SerialTransmit(void)
{
   if (SrlPut == SrlGet)
      SerialIntTxioff();
   else
   {
      SCI_Data_Reg = SerialBuffer[SrlGet++];
      if (SrlGet >= sizeof(SerialBuffer))
         SrlGet = 0;
   }
}

UINT16 SerialMessageQueue(UINT8 * buf, UINT16 cnt)
{
   UINT16 TempPtr;

   while (cnt--)
   {
      TempPtr = SrlPut;
      SerialBuffer[TempPtr++] = *buf++;
      if (TempPtr >= sizeof(SerialBuffer))
         TempPtr = 0;

      while (TempPtr == SrlGet)
         ;

      SrlPut = TempPtr;
   }
   SerialIntTxion();
   return(SUCCESS);
}


/***********************************************************************/
/* isr_uart: Serial channel interrupt service routine               */
/* */
/***********************************************************************/
void isr_uart(void)
{
    UINT8 ByteReceived;
    UINT16 status = SCI_Status_Reg;
    UINT16 enable = SCI_Ctrl_Reg1;

/*---------------------------------------------------------------------*/
/* If an enabled receive interrupt has occurred, process it.           */
/*---------------------------------------------------------------------*/
    if ((enable & RECEIVER_INT_EN) && (status & RECEIVE_REG_FULL))
    {
        ByteReceived = SCI_Data_Reg;

        if (status & FRAMING_ERROR)
        {
            SCI_Data_Reg;   /* read, but throw the value away */
            BrkRcvd = 1;
        }
        CommAsciiCharRcvd( ByteReceived );
    }

/* If an enabled transmit interrupt has occurred, process it.          */
    if ((enable & TRANSMIT_INT_EN) && (status & TRANSMIT_REG_EMPTY))
        SerialTransmit();

}

/***********************************************************************/
/* Global Functions                                                    */
/***********************************************************************/

/***********************************************************************/
/* SerialSetup: Perform startup initialization of serial channels      */
/* */
/* INPUTS: baud_rate - Default baud rate to use                   */
/* */
/***********************************************************************/
SYS_STARTUP_STATUS_TYPE SerialSetup(UINT32 baud_rate)
{

    SYS_STARTUP_STATUS_TYPE SysStartupStatus = SYS_STARTUP_PASS;
    UINT32 BaudRate;


/* Clear Brk_Rcvd variable. */

    BrkRcvd = 0;

    switch (baud_rate)

    {
    case BAUD_4800:
        BaudRate = 4800;
        break;
    case BAUD_9600:
        BaudRate = 9600;
        break;
    case BAUD_19200:
        BaudRate = 19200;
        break;
    default:
        BaudRate = 9600;
        break;
    }

/*---------------------------------------------------------------------*/
/* Wait until the transmit shift register is empty.                    */
/*---------------------------------------------------------------------*/
/* while ((SCI_Status_Reg & TRANSMIT_REG_EMPTY) == 0) ;     */

/*---------------------------------------------------------------------*/
/* Should write new values to the SCI control registers only after     */
/* disabling the transmitter and receiver.                             */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 &= ~(TRANSMITTER_EN + RECEIVER_EN);

/*---------------------------------------------------------------------*/
/* Set the mode and the initial baud rate.                             */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 = PUSH_PULL_TXD + PARITY_DISABLED + EIGHT_DATA_BITS
        + TRANSMITTER_EN + RECEIVER_EN;
    SerialIntBaud(BaudRate);

/*---------------------------------------------------------------------*/
/* Set the interrupt vector and interrupt level.                       */
/*---------------------------------------------------------------------*/
    SysSetVector(V_SERIAL, isr_uart, NORMAL_WRAPPER);
    QSM_Int_Level_Reg |= BD_SER_IRQ_LEVEL;

/*---------------------------------------------------------------------*/
/* Write a one to the TXD bit in the QSM_Port_Data_Reg and configure   */
/* the TXD pin as an output in the QSM_Data_Dir_Reg so that when the   */
/* transmitter is disabled, it will still mark.                        */
/*---------------------------------------------------------------------*/
    QSM_Port_Data_Reg |= TXD_PIN_HIGH;
    QSM_Data_Dir_Reg |= TXD_PIN_OUTPUT;

    return (SysStartupStatus);

}

/***********************************************************************/
/* SerialPollOn: Turn the interrupt enables off.                       */
/* */
/* NOTE: This is called by pROBE+ when taking control from the  */
/* application, such as when a breakpoint is hit.         */
/* */
/***********************************************************************/
void SerialPollOn(void)
{
    SaveQSMIntLevel = QSM_Int_Level_Reg;
    SaveSCICtrlReg1 = SCI_Ctrl_Reg1;

    QSM_Int_Level_Reg &= ~0x07; /* Disable SCI interrupts */
    SCI_Ctrl_Reg1 = PUSH_PULL_TXD + PARITY_DISABLED + EIGHT_DATA_BITS
        + TRANSMITTER_EN + RECEIVER_EN;
}

/***********************************************************************/
/* SerialPollOff: Restore the interrupt enables to the state they were */
/* in before SerialPollOn() was called.                 */
/* */
/* NOTE: This is called by pROBE+ when relinquishing control to */
/* the application.                                       */
/* */
/***********************************************************************/
void SerialPollOff(void)
{
    QSM_Int_Level_Reg = SaveQSMIntLevel;   /* Restore to pre-pROBE state */
    SCI_Ctrl_Reg1 = SaveSCICtrlReg1;
}


/***********************************************************************/
/* SerialPollConsts: Check the status of the pROBE+ console            */
/* */
/* INPUTS: typecode - unused                                      */
/* */
/* RETURNS: 0 = nothing received                                   */
/* 1 = character available                                */
/* 2 = break received                                     */
/* NOTE: unused_typecode = typecode; done to avoid compiler     */
/* warning                                                */
/* */
/***********************************************************************/
UINT32 SerialPollConsts(void)
{
    BYTE status = SCI_Status_Reg;

    if (BrkRcvd != 0)
    {
        BrkRcvd = 0;
        return (2);
    }
    else if (status & FRAMING_ERROR)
    {
/*-----------------------------------------------------------------*/
/* Got a framing error most likely caused by an RS-232 "break".    */
/* These persist for a relatively long time, so wait for the       */
/* condition to clear before returning.  This prevents the break   */
/* from being reported more than once.                             */
/*-----------------------------------------------------------------*/
        do
        {
            SCI_Data_Reg;   /* read, but throw the value away */
        }
        while (SCI_Status_Reg & FRAMING_ERROR);

        return 2;   /* return "break received" */
    }
    else if (status & RECEIVE_REG_FULL)
    {
/*-----------------------------------------------------------------*/
/* Got a non-break character.  Check for errors.  If character is  */
/* bad, throw it away.  Note: Ignoring overrun errors.  They       */
/* indicate that the character after the character in the receive  */
/* data register has been lost - nothing to do about that here.    */
/*-----------------------------------------------------------------*/
        if ((status & (NOISE_ERROR | PARITY_ERROR)) == 0)
        {
            return 1;   /* return "character available" */
        }
        else
        {
            SCI_Data_Reg;   /* read, but throw the value away */
            return 0;   /* return "nothing received" */
        }
    }
    else
/*-------------------------------------------------------------*/
/* Nothing in receive data register.                           */
/*-------------------------------------------------------------*/
        return 0;   /* return "nothing received" */
}

/***********************************************************************/
/* SerialPollInit: Initialize the polled serial channels               */
/* */
/***********************************************************************/
void SerialPollInit(void)
{
/* Nothing to do here for the m68332 */
}


/***********************************************************************/
/* SerialPollConin: Get a character from the pROBE+ console            */
/* */
/* RETURNS: Character from the console                             */
/* */
/* NOTE: Only called after SerialPollConsts() returns 1.        */
/* */
/***********************************************************************/
BYTE SerialPollConin(void)
{
    BYTE status = SCI_Status_Reg;
    BYTE ch = SCI_Data_Reg;

    if ((status & OVERRUN_ERROR) && ch == XOFF)
        return XON;
    else
        return ch;
}

/***********************************************************************/
/* SerialPollConout: Send a character to the pROBE+ console            */
/* */
/* INPUTS: ch - character to send                                 */
/* */
/***********************************************************************/
void SerialPollConout(SINT8 ch)
{
    while ((SCI_Status_Reg & TRANSMIT_REG_EMPTY) == 0)
        ;

    SCI_Data_Reg = ch;
}


/***********************************************************************/
/* SerialIntInit: Initialize a serial channel for interrupt-driven     */
/* operation                                            */
/* */
/* RETURNS: NULL                                                   */
/* */
/***********************************************************************/
void *SerialIntInit(void)
{
/*---------------------------------------------------------------------*/
/* Save global pointers to high-level interrupt service routines.      */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* Turn on receive interrupts so we can buffer incoming characters.    */
/*---------------------------------------------------------------------*/

    return NULL;
}

/***********************************************************************/
/* SerialIntBaud: Set a new baud rate for the device                   */
/* baud_rate - rate to be set                             */
/* RETURNS: always returns zero                                    */
/* NOTE: unused_channel = channel; + unused_hdp = hdp;          */
/* done to avoid compiler warning                         */
/* */
/***********************************************************************/
UINT32 SerialIntBaud(UINT32 baud_rate)
{
    int i;

/*---------------------------------------------------------------------*/
/* Constants for the Baudrate generator                                */
/*---------------------------------------------------------------------*/
#if SYSTEM_CLOCK ==_16MHZ
    const static UINT32 baudtable[9][2] =
    {           /* baud-rate, SCBR value */
        {300, 1748},
        {600, 874},
        {1200, 437},
        {2400, 218},
        {4800, 109},
        {9600, 55},
        {19200, 27},
        {38400, 14},
        {0, 55}     /* table ends with default of 9600 baud */
    };


#elif SYSTEM_CLOCK ==_21MHZ
    const static UINT32 baudtable[9][2] =
    {           /* baud-rate, SCBR value */
        {300, 2184},
        {600, 1092},
        {1200, 546},
        {2400, 273},
        {4800, 136},
        {9600,  68},
        {19200, 34},
        {38400, 17},
        {0,     68}     /* table ends with default of 9600 baud */
    };
#elif SYSTEM_CLOCK ==_24_117MHZ
    const static UINT32 baudtable[9][2] =
    {           /* baud-rate, SCBR value */
        {300, 2512},
        {600, 1256},
        {1200, 628},
        {2400, 314},
        {4800, 157},
        {9600,  78},     /* actual = 24117000/(32*78) = 9662 */
        {19200, 39},
        {38400, 20},
        {0,     78}     /* table ends with default of 9600 baud */
    };


#elif SYSTEM_CLOCK ==_24_642MHZ
    const static UINT32 baudtable[9][2] =
    {           /* baud-rate, SCBR value */
        {300, 2567},
        {600, 1283},
        {1200, 642},
        {2400, 321},
        {4800, 160},
        {9600,  78},
        {19200, 40},
        {38400, 20},
        {0,     78}     /* table ends with default of 9600 baud */
    };

#endif



/*---------------------------------------------------------------------*/
/* Look up the time constant for the desired baud rate in the table.   */
/*---------------------------------------------------------------------*/
    for (i = 0; baudtable[i][0] && (baudtable[i][0] != baud_rate); i++)
        ;

/*---------------------------------------------------------------------*/
/* Wait until the transmit shift register is empty.                    */
/*---------------------------------------------------------------------*/
    while ((SCI_Status_Reg & TRANSMIT_REG_EMPTY) == 0)
        ;

/*---------------------------------------------------------------------*/
/* Should write new values to the SCI control registers only after     */
/* disabling the transmitter and receiver.                             */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 &= ~(TRANSMITTER_EN + RECEIVER_EN);

/*---------------------------------------------------------------------*/
/* Now do what we wanted to do, set the baud rate.                     */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg0 = baudtable[i][1];

/*---------------------------------------------------------------------*/
/* Finally, re-enable the transmitter and receiver.                    */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 |= TRANSMITTER_EN + RECEIVER_EN;
    return 0;
}

/***********************************************************************/
/* SerialIntRxion: Turn on receive interrupts                          */
/* */
/***********************************************************************/
void SerialIntRxion(void)
{

/*---------------------------------------------------------------------*/
/* Wait until the transmit shift register is empty.                    */
/*---------------------------------------------------------------------*/
    while ((SCI_Status_Reg & TRANSMIT_REG_EMPTY) == 0)
        ;

/*---------------------------------------------------------------------*/
/* Should write new values to the SCI control registers only after     */
/* disabling the transmitter and receiver.                             */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 &= ~(TRANSMITTER_EN + RECEIVER_EN);

/*---------------------------------------------------------------------*/
/* Enable receive interrupts, re-enable the transmitter and receiver.  */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 |= (RECEIVER_INT_EN + TRANSMITTER_EN + RECEIVER_EN);
}

/***********************************************************************/
/* SerialIntRxioff: Turn off receive interrupts                        */
/* */
/***********************************************************************/
void SerialIntRxioff(void)
{

/*---------------------------------------------------------------------*/
/* Wait until the transmit shift register is empty.                    */
/*---------------------------------------------------------------------*/
    while ((SCI_Status_Reg & TRANSMIT_REG_EMPTY) == 0)
        ;

/*---------------------------------------------------------------------*/
/* Should write new values to the SCI control registers only after     */
/* disabling the transmitter and receiver.                             */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 &= ~(TRANSMITTER_EN + RECEIVER_EN);

/*---------------------------------------------------------------------*/
/* Now do what we wanted to do, turn receive interrupts off.           */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 &= ~RECEIVER_INT_EN;

/*---------------------------------------------------------------------*/
/* Finally, re-enable the transmitter and receiver.                    */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 |= TRANSMITTER_EN + RECEIVER_EN;
}

/***********************************************************************/
/* SerialIntTxion: Turn on transmit interrupts                         */
/* */
/***********************************************************************/
void SerialIntTxion(void)
{

/*---------------------------------------------------------------------*/
/* Wait until the transmit shift register is empty.                    */
/*---------------------------------------------------------------------*/
    while ((SCI_Status_Reg & TRANSMIT_REG_EMPTY) == 0)
        ;

/*---------------------------------------------------------------------*/
/* Should write new values to the SCI control registers only after     */
/* disabling the transmitter and receiver.                             */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 &= ~(TRANSMITTER_EN + RECEIVER_EN);

/*---------------------------------------------------------------------*/
/* Enable transmit interrupts, re-enable the transmitter and receiver. */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 |= (TRANSMIT_INT_EN + TRANSMITTER_EN + RECEIVER_EN);
}

/***********************************************************************/
/* SerialIntTxioff: Turn off transmit interrupts                       */
/* */
/***********************************************************************/
void SerialIntTxioff(void)
{

/*---------------------------------------------------------------------*/
/* Wait until the transmit shift register is empty.                    */
/*---------------------------------------------------------------------*/
    while ((SCI_Status_Reg & TRANSMIT_REG_EMPTY) == 0)
        ;

/*---------------------------------------------------------------------*/
/* Should write new values to the SCI control registers only after     */
/* disabling the transmitter and receiver.                             */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 &= ~(TRANSMITTER_EN + RECEIVER_EN);

/*---------------------------------------------------------------------*/
/* Now do what we wanted to do, turn transmit interrupts off.          */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 &= ~TRANSMIT_INT_EN;
    SCI_Ctrl_Reg1 &= ~TRANSMIT_COMPLETE_INT_EN;

/*---------------------------------------------------------------------*/
/* Finally, re-enable the transmitter and receiver.                    */
/*---------------------------------------------------------------------*/
    SCI_Ctrl_Reg1 |= TRANSMITTER_EN + RECEIVER_EN;
}

/***********************************************************************/
/* SerialIntRead: Read a character from a serial channel               */
/* */
/* */
/***********************************************************************/
UINT32 SerialIntRead(UINT8 * ch_ptr)
{

    UINT16 status = SCI_Status_Reg;


    if (status & FRAMING_ERROR)
    {
        SCI_Data_Reg;   /* Clear framing error flag */
        return 3;
    }
    else if (status & PARITY_ERROR)
    {
        SCI_Data_Reg;   /* Clear parity error flag */
        return 2;
    }
    else
    {
        *ch_ptr = SCI_Data_Reg;
        if ((status & OVERRUN_ERROR) && *ch_ptr == XOFF)
            return 4;
        return 0;
    }
}

/***********************************************************************/
/* SerialIntWrite: Write a character to the UART                       */
/* */
/***********************************************************************/
UINT32 SerialIntWrite(UINT8 ch)
{

    SCI_Data_Reg = ch;
    return 0;
}
