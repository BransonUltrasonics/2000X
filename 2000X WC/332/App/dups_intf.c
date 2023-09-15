/* $Header:   D:/databases/VMdb/2000Series/App/dups_intf.c_v   1.13.2.1   Jan 03 2018 09:09:52   RCHAPA  $ */
/* **************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/* ************************                        **************************/

/*
------------------------- MODULE DESCRIPTION -------------------------------
                                          
   Module name:   DUPS interface

   Filename:      dups_intf.c

   Function name: 

            Written by: Ashish Sharma 
                  Date: 6/7/00
              Language:  "C"                              


----------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author            Description
   ==========   ========   ======            ===========
        1       06/07/00    AS               Initial Version
        1.1     06/19/00    AS               Interface clean-up, intialization of QSPI
                                             registers as per M3100 chip requirements.
        1.2     06/23/00    AS               Debugged saving and restoring of Spcr0-3 registers
        1.3     06/26/00    AS               Defined DupsBid in this module
        1.4     06/30/00    AS               Deleted control ASCII character defines, included ascii.h
        1.5     07/07/00    AS               De-bugged Data_Xfer function
        1.6     07/21/00   SRP               New read and write fuction made tested with timeout. checked in with
                                             old read and write functions.
        1.7     07/22/00   SRP               old read and write, TBE functions removed. New read and write modified.
        1.8     07/24/00   SRP               sleeptime added in read and write operations.
        1.9     07/25/00   SRP               inbyte shifted before ACK NAK check in readP.
        1.10    09/27/00    AT               removed tm_wkafter (all 4 of them), modified readbyte(), many minor things
        1.11    09/28/00    AT               retry 3 times in DUPS_DataXfer
        1.12    10/12/00    AT               Changed SINT16 to enum DUPS_RESULTS
        1.13    10/26/00    AT               Limit DUPS_ReadP receive byte count to size of response buffer
        1.13.2.1  1/3/2018 RChapa 			 Removed DUPS validation for DUPS update at DUPS_RESULTS DUPS_ReadP
*/

/*------------------------------ DESCRIPTION -------------------------------*/


/* This file deals with DUPS interface                                      */


/*----------------------------- INCLUDE FILES ------------------------------*/

#include <psos.h>           /* general hardware defines, etc..   */
#include "dups_api.h"
#include "dups.h"
#include "332.h"
#include "portable.h"
#include "qsm.h"
#include "ascii.h"


/*---------------------------- EXTERNAL DATA -------------------------------*/

extern DUPS_CMDBUF      DUPS_CmdBuf;
extern DUPS_RESPONSEBUF DUPS_RspBuf;
extern UINT16 OneMilTimer;
extern UINT32 DupsQid;
/*----------------------------- LOCAL DEFINES ------------------------------*/

/* M3100 local defines. These are bitmaps in configuration register of M3100 */
   /* ls 4 bits for baud rate */
   #define M3100_Baud19_2k 0x0009

   /* Bit 4 - clear for 8 bits/word, set for 7 bits/word */
   #define M3100_WordLen8  0x0000
   #define M3100_WordLen7  0x0010

   /* Bit 5 - clear for parity disabled */
   #define M3100_PEen      0x0020
   #define M3100_PEdis     0x0000

   /* Bit 6 - clear for 1 stop bit, set for 2 stop bits */
   #define M3100_ST1       0x0000
   #define M3100_ST2       0x0040

   /* Bit 7 - clear for disabling IrDA timing mode */
   #define M3100_IRen      0x0080
   #define M3100_IRdis     0x0000

   /* Bit 8 - interrupt enable on transition on RX when in shutdown */
   #define M3100_RAMen     0x0100
   #define M3100_RAMdis    0x0000

   /* Bit 9 - interrupt enable on received parity 1 */
   #define M3100_PMen      0x0200
   #define M3100_PMdis     0x0000

   /* Bit 10 - interrupt enable on new data available in M3100 receive reg/FIFO */
   #define M3100_RMen      0x0400
   #define M3100_RMdis     0x0000

   /* Bit 11 - interrupt enable on transmit buffer empty  */
   #define M3100_TMen      0x0800
   #define M3100_TMdis     0x0000

   /* No interrupts enabled, bits 8-11 cleared */
   #define M3100_IntsDis   0x0000

   /* Bit 12 - set to enable software shutdown */
   #define M3100_SHDN      0x1000

   /* Bit 13 - receive FIFO enable */
   #define M3100_FEN       0x0000

   /* Bit 14 - transmit buffer empty when set */
   #define M3100_TBE       0x4000

   /* Bit 15 - new data available when set */
   #define M3100_DA        0x8000

   /* Bits 14 & 15 - define operation being performed with M3100 */
   #define M3100_WConf     0xC000 /* Set both for write config */
   #define M3100_RConf     0x4000 /* Bit 14 set for read config */
   #define M3100_WData     0x8000 /* Bit 15 set for write data */
   #define M3100_RData     0x0000 /* Clear both for read data */

/* Define constants for writing config bytes to M3100 */

   #define M3100_InitConf  (M3100_Baud19_2k | M3100_WordLen8 | M3100_PEdis | M3100_ST1 | M3100_IRdis | M3100_IntsDis | M3100_FEN | M3100_WConf)
                           // Baud 19.2k,     8 bit word,      No parity,   1 stop bit, IR disabled,  Ints disabled,  Rx FIFO enabled,Write to config reg

   #define M3100_RecInt    (M3100_Baud19_2k | M3100_WordLen8 | M3100_PEdis | M3100_ST1 | M3100_IRdis | M3100_RMen | M3100_FEN | M3100_WConf)
                           // Baud 19.2k,     8 bit word,      No parity,   1 stop bit, IR disabled,  Rec Int,   Rx FIFO enabled,Write to config reg

/* Macros to test M3100 chip buffer empty/full flag when the byte is read in QSM register */
#define M3100_BufEmpty (QsmMap->RxdData[0] & M3100_TBE)
#define M3100_BufFull  (!(QsmMap->RxdData[0] & M3100_TBE))
#define QSM_NotReady   (QsmMap->Spcr1.Spe == 1)

/*----------------------- LOCAL TYPE DECLARATIONS --------------------------*/

/*----------------------------- GLOBAL DATA --------------------------------*/

UINT16 DupsBid;

/*------------------------- PRIVATE GLOBAL DATA ----------------------------*/

/* Save QSPI registers */
   UINT16          QSMRx[16];
   UINT16          QSMTx[16];
   struct ComdR    QSMCmd[16];

   UINT16          SavSpcr0;
   UINT16          SavSpcr1;
   UINT16          SavSpcr2;
   UINT16          SavSpcr3;

   UINT8     DupsCommStatus = 0;
   UINT8     BytesToReceive;

/*------------------------ EXTERNAL FUNCTIONS ------------------------------*/


/*----------------------- LOCAL FUNCTION PROTOTYPES ------------------------*/

void checktime(SINT16 *);
BOOLEAN getbyte(UINT8 *);
BOOLEAN writebyte(UINT8);
enum DUPS_RESULTS DUPS_ReadP ( UINT8* , SINT16* );
enum DUPS_RESULTS DUPS_WriteP ( UINT8* , SINT16* );
void   DUPS_WriteConfigByte(UINT16 ConfigByte);
void   DUPS_AttachQSPI(void);
void   DUPS_ReleaseQSPI(void);

/*------------------------------ CODE --------------------------------------*/

#define RETRY_COUNT 3
#define RETRY_TIMEOUT 500 /* milliseconds */

enum DUPS_RESULTS DUPS_DataXfer(void)
{  
   enum DUPS_RESULTS Status;
   SINT16 Timeout;
   UINT8 Retry;
   
   DUPS_AttachQSPI();
   for (Retry = 0; Retry < RETRY_COUNT; Retry++)
      {
      Timeout = RETRY_TIMEOUT;
      Status= DUPS_WriteP((UINT8 *) &DUPS_CmdBuf, &Timeout);
      if (Status == DUPS_SUCCESS)
         Status = DUPS_ReadP((UINT8 *) &DUPS_RspBuf, &Timeout);
      if (Status == DUPS_SUCCESS)
         break;
      }
   DUPS_ReleaseQSPI();
   return Status;
}

/*********************************************************************************/

#define DUPS_CMDHDRLEN 2

enum DUPS_RESULTS DUPS_WriteP ( UINT8 *Outbuf, SINT16 *Time)
{
   DUPS_CMDBUF *CmdBuf = (DUPS_CMDBUF *)Outbuf;
   UINT8  Checksum = 0;
   UINT16 Cnt      = 0;
   UINT16 outptr   = 0;
   enum DUPS_RESULTS status   = DUPS_SUCCESS;
   
   Cnt = CmdBuf -> Count;
   
   for(outptr = DUPS_CMDHDRLEN; outptr < (Cnt + DUPS_CMDHDRLEN); outptr++)
       Checksum ^= Outbuf[outptr];
       
   Outbuf[outptr++] = Checksum;
   Outbuf[outptr++] = DLE;
   Outbuf[outptr++] = ETX;
   Cnt    = outptr;
   outptr = 0;
   
   while((*Time>0) && (outptr < Cnt ))
   {
      if(writebyte(Outbuf[outptr]))
      {
         outptr++;
      }
      checktime(Time); 
   }  // while time left and data remains
   if(*Time >0)
      status = DUPS_SUCCESS;
   else
      status = DUPS_TIMEOUT;
   return status;
}  // end of DUPS_WRITE
        

BOOLEAN writebyte(UINT8 obyte)
{
   BOOLEAN status = FALSE;
   DUPS_WriteConfigByte(M3100_RConf);

   if (QsmMap->RxdData[0] & M3100_TBE)
      {
      DUPS_WriteConfigByte(obyte | M3100_WData);
      status = TRUE;
      }
   else
      status = FALSE;
   return status;
}

/***********************************************************************************************/

#define DUPS_RESPHDR 5  /* ACK/NAK DLE STX Cnt Cnt */
#define DUPS_RESPCRC 3  /* CRC bytes start from 3rd */
#define DUPS_RESPTAIL 3 /* CRC DLE ETX - not counted in count field */

enum DUPS_RESULTS DUPS_ReadP(UINT8 *InBuf, SINT16 *time)
{
   DUPS_RESPONSEBUF *RespBuf = (DUPS_RESPONSEBUF *)InBuf;
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT16 inptr = 0;
   UINT8 inbyte;
   UINT8 chksum = 0;
   UINT16 cnt = 0;
   BOOLEAN BadLength = FALSE;
   
   RespBuf -> Count = 0;
   InBuf[0] = 0;
   
   while ((inptr < DUPS_RESPHDR) && (*time > 0))
      {   
      if(getbyte(&inbyte))
         {
         InBuf[inptr] = inbyte;
         if( (InBuf[0] == ACK) || (InBuf[0] == NAK))  //discard bytes till ACK/NACK received
            inptr++;
         }
      checktime(time);
      }

   /* limit maximum receive count to what's left in the receive buffer */
   /* ignore 3 first bytes that are not included in CRC */
   /* ignore 3 last bytes - CRC and trailer */
   RespBuf->Count &= 0xFFF;   /* just mask off some bits that don't make sense at all */
   if (RespBuf->Count > (sizeof(DUPS_RESPONSEBUF) - DUPS_RESPCRC - DUPS_RESPTAIL))
      {
      RespBuf->Count = sizeof(DUPS_RESPONSEBUF) - DUPS_RESPCRC - DUPS_RESPTAIL;
      BadLength = TRUE;
      }
   cnt = RespBuf->Count + DUPS_RESPTAIL - sizeof(RespBuf->Count);
   while ((*time > 0) && (cnt > 0))         
      {
      if(getbyte(&inbyte))
         {
         InBuf[inptr++] = inbyte;
         cnt--;
         } 
      checktime(time);
      }
   /* calculate CRC only if not bad data and no timeout */
   if ((BadLength == FALSE) && (*time > 0))
      {
      for (inptr = DUPS_RESPCRC; inptr < DUPS_RESPCRC + RespBuf->Count; inptr++)
         chksum ^= InBuf[inptr];
      }
   if (*time <= 0)
      status = DUPS_TIMEOUT;
   else if (RespBuf->ACK_NACK == NAK)
           status = DUPS_NACK;
   else if ((chksum != InBuf[DUPS_RESPCRC + RespBuf->Count]) || (BadLength == TRUE))
        status = DUPS_CHECKSUM;   
   return status;
}  // end of readP

void checktime(SINT16 *inval)
{
   static UINT16 lasttime = 0;
   if(lasttime != OneMilTimer)
      (*inval)--;
   lasttime =  OneMilTimer;
}// end of checktime

BOOLEAN getbyte(UINT8 *indata)
{
   BOOLEAN status = TRUE;

   DUPS_WriteConfigByte(M3100_RConf);
   if (QsmMap->RxdData[0] & M3100_DA)
      {
      DUPS_WriteConfigByte(M3100_RData);
      *indata =  QsmMap->RxdData[0] & 0xff;
      status = TRUE;
      }
   else
      status = FALSE;
   return status;
}

void DUPS_AttachQSPI (void)     // UINT16 * AttachFlag )
{  UINT8   i;
   UINT16  *ptrSPCregs;

   DupsBid = 1;
   while(QSM_NotReady)  /* wait for QSPI finished */
      ;

//(*AttachFlag) = TRUE;         /* set attach flag */

   for(i=0; i<16; i++)
   {  QSMRx[i] = QsmMap->RxdData[i];/* save RxdData */
      QSMTx[i] = QsmMap->TxdData[i];/* save TxdData */
      QSMCmd[i] = QsmMap->ContRam[i];/* save Command Data */
   }

   /* save QSPI control registers */    
   ptrSPCregs = (UINT16 *) &QsmMap->Spcr0;
   SavSpcr0 = *ptrSPCregs;           /* save QSPI control reg 0 */
   ptrSPCregs = (UINT16 *) &QsmMap->Spcr1;
   SavSpcr1 = *ptrSPCregs;           /* save QSPI control reg 1 */
   ptrSPCregs = (UINT16 *) &QsmMap->Spcr2;
   SavSpcr2 = *ptrSPCregs;           /* save QSPI control reg 2 */
   ptrSPCregs = (UINT16 *) &QsmMap->Spcr3;
   SavSpcr3 = *ptrSPCregs;           /* save QSPI control reg 3 */

   /* setup for transmit */
   QsmMap->Spcr2.Newqp = 0;      /* start xfer at 0 offset */
   QsmMap->Spcr2.Endqp = 0;      /* end transfer after 1 word */
   QsmMap->Spcr2.Wren  = 0;      /* disable wraparound mode */
   QsmMap->Spcr2.Spifie = 0;     /* QSPI interrupts disabled */
   
   QsmMap->Spcr0.Mstr  = 1;      /* QSPI in master mode */
   QsmMap->Spcr0.Womq  = 0;      /* disable wired-OR mode for QSPI pins */
   QsmMap->Spcr0.Bits  = 0;      /* make 16-bit transfers */
   QsmMap->Spcr0.Cpha  = 0;      /* capture data on following edge of SCK */
   QsmMap->Spcr0.Cpol  = 0;      /* the inactive state of SCK is logic level 0 */
   QsmMap->Spcr0.Spbr  = 5;      /* exchange data @2.4Mhz between QSPI and M3100 */
   
   QsmMap->Spcr1.Dsckl = 3;      /* Delay between CS and SCK, allow 120ns @24.642Mhz*/
   QsmMap->ContRam[0].Dsck = 1;  /* enable delay between CS and SCK */
      
   QsmMap->Spcr1.Dtl = 0;        /* Delay after transfer */
   QsmMap->ContRam[0].Dt = 0;    /* disable delay after transfer */    

   QsmMap->ContRam[0].Bitse = 1; /* enable bits per transfer */
   QsmMap->ContRam[0].Pcs   = 9; /* use chip select of 9 */
   QsmMap->ContRam[0].Cont  = 0; /* drop chip select after transfer */
   
   /* Do transmit of configuration command */
   DUPS_WriteConfigByte(M3100_InitConf);
} // end DUPS_ATTACHQSPI


void DUPS_ReleaseQSPI (void)
{  UINT8   i = 0;
   UINT16  *ptrSPCregs;

/* restore QSPI RAM as we are about to re-enable normal scanning of digitizers */
   for(i=0; i<16; i++)
   {  QsmMap->RxdData[i] = QSMRx[i];   /* restore RxdData */
      QsmMap->TxdData[i] = QSMTx[i];   /* restore TxdData */
      QsmMap->ContRam[i] = QSMCmd[i];  /* restore Command Data */
   }

   /* restore QSPI control registers */
   ptrSPCregs = (UINT16 *) &QsmMap->Spcr0;
   *ptrSPCregs = SavSpcr0;      /* restore QSPI control register 0 */
   ptrSPCregs = (UINT16 *) &QsmMap->Spcr1;
   *ptrSPCregs = SavSpcr1;      /* restore QSPI control register 1 */
   ptrSPCregs = (UINT16 *) &QsmMap->Spcr2;
   *ptrSPCregs = SavSpcr2;      /* restore QSPI control register 2 */
   ptrSPCregs = (UINT16 *) &QsmMap->Spcr3;
   *ptrSPCregs = SavSpcr3;      /* restore QSPI control register 3 */

   DupsBid = 0;                 /* clear attach flag */
}  // end DUPS_ReleaseQSPI

/* This function writes config byte to M3100. Assumes QSPI is attached to */
void DUPS_WriteConfigByte (UINT16 ConfigByte)
{
    /* do transmit of configuration command */
   QsmMap->RxdData[0] = 0;
   QsmMap->TxdData[0] = ConfigByte;/* store write configuration command */
   QsmMap->Spcr1.Spe  = 1;         /* transmit */                        
   while(QSM_NotReady)    /* wait for QSPI finished */
      ;
} // end DUPS_WriteConfigByte (UINT16 ConfigByte)
