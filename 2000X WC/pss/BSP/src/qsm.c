/* $Header:   K:/APPS/PVCS Pro/PSS68k.222/BSP/src/QSM.C_v   1.1   May 04 1999 13:21:22   lmarkure  $ */
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
/*                                                                          */
/*
 ---------------------------- MODULE DESCRIPTION --------------------------
  Name: qsm.c

 -------------------------------- REVISIONS -------------------------------

   Revision #     Date         Author       Description
   ----------     -------      ------       -----------
     0            04/20/96      LAM         Initial
     1            05/06/96      LAM         Not initializing dpot
     2            05/05/97      LAM         chged iarb = f from d
     3.2.8        07/07/97      LAM         set reg to read 10vref at powerup
     3.2.9        09/04/97      LAM         deleted DSCK from PSADC          
     2.10         09/05/97      LAM         corrected dummy write            
     2.11         09/11/97      PaulG       Unit test and cleanup
     1.1          05/04/99      LAM         added packed keyword for DIAB


 ----------------------------- INCLUDE FILES -------------------------------
*/

#include "bsp.h"
#include <bspfuncs.h>
#include "portable.h"
#include "332.h"
#include "qsm.h"
#include "spidd.h"

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/                                                              


/*
 ------------------------------- LOCAL DATA ------------------------------------
*/

__packed__ struct MQMap *QsmMap;


void InitQsm(void)
/****************************************************************************/ 
/*                                                                          */    
/*    The PSupply 2 channel D/A will be on Channels 0 & 1 of the QSPI. 24   */
/* bit stream on PSC 0 Frequency Offset and Amplitude In.                   */                   
/*    The PSupply 7 Channel A/D will be on Channels 2 - 8. The bit stream is*/    
/* 16 bits. Amplitude on 2, Power on 3, Memory on 4, Freq. on 5, +10v ref on*/    
/*    The Actuator 2 Channel A/D will be on Channels 9 & 10. The bit stream */
/* is 16 bits. Load Cell on 9 & Pressure is on 10.                          */
/*    The Actuator D/A will be on Channel 11. The bit stream is 16 bits.    */
/* It will control the PVP.                                                 */
/*    The Bargraph will be on Channels 12 through 14. The bit stream is 8   */
/* 8bits.                                                                   */
/*    The Digital Pot will be on Channel 15.It will set the center freq.    */
/*                                                                          */    
/*                                                                          */    
/****************************************************************************/ 
{
   UINT8 Temp;


   QsmMap = (__packed__ struct MQMap *)(0x0fffc00);
   QsmMap->Spcr1.Spe = 0;  /* Disable Qspi */
/*      Field STOP = 0  */
/*      Field FRZ1 = 1  */
/*      Field FRZ0 = 0  */
/*      Field MT0  = 0  */
/*      Field SUPV = 1  */
/*      Field MT1  = 0  */
/*      Field IARB = 14  */

//      QsmMap->Qmcr = 0x408e; 
   QsmMap->Qmcr.Stop = 0;
   QsmMap->Qmcr.FRZ1 = 1;
   QsmMap->Qmcr.FRZ0 = 0;
   QsmMap->Qmcr.SUPV = 1;
   QsmMap->Qmcr.Iarb = 0x0f;
   
/* Set the value of register QILR/QIVR to 0x1970. */
/*      Field MT0    = 0     */
/*      Field ILQSPI = 4     */ 
/*      Field ILSCI  = 4     */
/*      Field INTV   = 0x40  */
// QsmMap->QilrQivr  = 0x2240;
   QsmMap->Qilr.Ilqspi = 0;  /* interrupt level     */
   QsmMap->Qilr.Ilsci  = 4;
   QsmMap->Qivr = 0x40;      /* interrupt vector    */
   Temp = QsmMap->Spsr.Spif;
   QsmMap->Spsr.Spif = 0;    /* Clear interrupt bit */

/* Set the value of register QPDR to 0x0018. */
/*      Field MT0 = 0 */
/*      Field D7  = 0 */
/*      Field D6  = 1 */
/*      Field D5  = 0 */
/*      Field D4  = 0 */
/*      Field D3  = 1 */
/*      Field D2  = 0 */
/*      Field D1  = 0 */
/*      Field D0  = 0 */
// Defaults PCS lines to unused chip select 9
   QsmMap->Qpdr = 0x0ff;  /* Qsm Port pins */
/* Set the value of register QPAR/QDDR to 0x7AFE. */
/*      Field MT0   = 0 */
/*      Field PCS30 = 1 */
/*      Field PCS20 = 1 */
/*      Field PCS10 = 1 */
/*      Field PCS0/SS*0 = 1 */
/*      Field MT1   = 0 */
/*      Field MOSI0 = 1 */
/*      Field MISO0 = 1 */
/*      Field TXD   = 1 */
/*      Field PCS31 = 1 */
/*      Field PCS21 = 1 */
/*      Field PCS11 = 1 */
/*      Field PCS0/SS*1 = 1 */
/*      Field SCK   = 1 */
/*      Field MOSI1 = 1 */
/*      Field MISO1 = 0 */
// QsmMap->QparQddr = 0x7bfe; 
   QsmMap->Qpar.Pcs = 0x0f;
   QsmMap->Qpar.Mosi= 1;
   QsmMap->Qpar.Miso= 1;
   QsmMap->Qddr.Txd = 1;
   QsmMap->Qddr.Pcs = 0x0f;
   QsmMap->Qddr.Sck = 1;
   QsmMap->Qddr.Mosi= 1;
   QsmMap->Qddr.Miso= 0;

/* Set the value of register SPCR0 to 0xBC08. */
/*      Field MSTR = 1  */
/*      Field WOMQ = 0  */
/*      Field BITS = 12 */
/*      Field CPOL = 0  */
/*      Field CPHA = 0  */
/*      Field SPBR = 10 */
// QsmMap->Spcr0   = 0xb00a; 
   QsmMap->Spcr0.Mstr = 1;
   QsmMap->Spcr0.Womq = 0;
   QsmMap->Spcr0.Cpol = 1;
   QsmMap->Spcr0.Cpha = 1;
   QsmMap->Spcr0.Bits = 12; /* was 532 bit stream */
   QsmMap->Spcr0.Spbr = 8; /* was 10????  953kHz for Novram */

/* Set the value of register SPCR1 to 0x0104. */
/*      Field SPE   = 0 */
/*      Field DSCKL = 1 */
/*      Field DTL   = 4 */
// QsmMap->Spcr1    = 0x104; 
   QsmMap->Spcr1.Dsckl = 1;/* CHGED??? 6 */
   QsmMap->Spcr1.Dtl= 1;  /* CHGED??? 6 */

/* Set the value of register SPCR2 to 0x2200. */
/*      Field SPIFIE = 0  */
/*      Field WREN   = 0  */
/*      Field WRTO   = 1  */
/*      Field MT0    = 0  */
/*      Field ENDQP  = 14 */
/*      Field MT1    = 0  */
/*      Field NEWQP  = 12 */
// QsmMap->Spcr2 = 0x2d0c; 
   QsmMap->Spcr2.Spifie = 0; /* Disable QSM Interrupt */
   QsmMap->Spcr2.Wren   = 0;
   QsmMap->Spcr2.Wrto   = 1;
   QsmMap->Spcr2.Newqp  = 13;
   QsmMap->Spcr2.Endqp  = 15; /* Bargraph Queue */

   QsmMap->Spcr3.Loopq  = 0;
   QsmMap->Spcr3.Hmie   = 0;
   QsmMap->Spcr3.Halt   = 0;
// SPIList[PSDAC]
// Maxim 532 Channel A = Frequency Offset
   QsmMap->ContRam[0].Cont  = 1;    /* chip select held low */
   QsmMap->ContRam[0].Bitse = 1;    /* number of bit set in SPCR0 reg */
   QsmMap->ContRam[0].Dt    = 0;    /* Delay after transfer */
   QsmMap->ContRam[0].Dsck  = 1;    /* SPCR1 specifies value of delay from
				       PCS valid to SCK */    
   QsmMap->ContRam[0].Pcs = 1;      /* Peripheral Chip Select */

// Maxim 532 Channel B      = Amplitude In    
   QsmMap->ContRam[1].Cont  = 0;    /* return chip select high after
				       transfer */
   QsmMap->ContRam[1].Bitse = 1;    /* number of bit set in SPCR0 reg */
   QsmMap->ContRam[1].Dt    = 1;    /* Delay after transfer */
   QsmMap->ContRam[1].Dsck  = 1;    /* SPCR1 specifies value of delay from
				       PCS valid to SCK */    
   QsmMap->ContRam[1].Pcs   = 1;    /* Peripheral Chip Select */

// SPIList[PSADC]
// 7890 PS
// The channels are sent in QsmMap->TxdData[x]. They are returned in 
// QsmMap->RxdData[x + 1]. A 16 bit value is sent back
// in the format of 0,a2,a1,a0,d11-d0.
//    
//  0x7ff = +10v
//  0x400 = +5v
//  0x001 = +0v
//  0x000 = -0v
//  0xc00 = -5v
//  0x800 = -10v
// 7890 Vin1 = Amplitude Out
  
   QsmMap->ContRam[2].Cont = 0;     /* return chip select high after
				       transfer */
   QsmMap->ContRam[2].Bitse = 1;    /* number of bit set in SPCR0 reg */
   QsmMap->ContRam[2].Dt = 1;       /* Delay after transfer */
   QsmMap->ContRam[2].Dsck = 0;     /* SPCR1 specifies value of delay from
				            				       				        PCS valid to SCK */    
   QsmMap->ContRam[2].Pcs = 0;      /* Peripheral Chip Select */

// 7890 Vin2 = Power Out
   QsmMap->ContRam[3].Cont = 0;     /* return chip select high after
				            				       						       transfer */
   QsmMap->ContRam[3].Bitse = 1;    /* number of bit set in SPCR0 reg */
   QsmMap->ContRam[3].Dt = 1;       /* Delay after transfer */
   QsmMap->ContRam[3].Dsck = 0;     /* SPCR1 specifies value of delay from
				            				       						       PCS valid to SCK */    
   QsmMap->ContRam[3].Pcs = 0;      /* Peripheral Chip Select */

// 7890 Vin3 = Frequency Memory
   QsmMap->ContRam[4].Cont = 0;     /* return chip select high after
				            				       						       transfer */
   QsmMap->ContRam[4].Bitse = 1;    /* number of bit set in SPCR0 reg */
   QsmMap->ContRam[4].Dt = 1;       /* Delay after transfer */
   QsmMap->ContRam[4].Dsck = 0;     /* SPCR1 specifies value of delay from
				            				       						       PCS valid to SCK */    
   QsmMap->ContRam[4].Pcs = 0;      /* Peripheral Chip Select */

// 7890 Vin4 = Frequency Out
   QsmMap->ContRam[5].Cont = 0;     /* return chip select high after
				            				       						       transfer */
   QsmMap->ContRam[5].Bitse = 1;    /* number of bit set in SPCR0 reg */
   QsmMap->ContRam[5].Dt = 1;       /* Delay after transfer */
   QsmMap->ContRam[5].Dsck = 0;     /* SPCR1 specifies value of delay from
				            				       						       PCS valid to SCK */    
   QsmMap->ContRam[5].Pcs = 0;      /* Peripheral Chip Select */

// 7890 Vin6 = Ext. Amp
   QsmMap->ContRam[6].Cont = 0;     /* return chip select high after
				            				       						       transfer */
   QsmMap->ContRam[6].Bitse = 1;    /* number of bit set in SPCR0 reg */
   QsmMap->ContRam[6].Dt = 1;       /* Delay after transfer */
   QsmMap->ContRam[6].Dsck = 0;     /* SPCR1 specifies value of delay from
				            				       						       PCS valid to SCK */    
   QsmMap->ContRam[6].Pcs = 0;      /* Peripheral Chip Select */

// 7890 Vin7 = Ext. Freq
   QsmMap->ContRam[7].Cont = 0;     /* return chip select high after
				            				       						       transfer */
   QsmMap->ContRam[7].Bitse = 1;    /* number of bit set in SPCR0 reg */
   QsmMap->ContRam[7].Dt = 1;       /* Delay after transfer */
   QsmMap->ContRam[7].Dsck = 0;     /* SPCR1 specifies value of delay from
				            				       						       PCS valid to SCK */    
   QsmMap->ContRam[7].Pcs = 0;      /* Peripheral Chip Select */

// 7890 Vin5 = +10v Ref. The +10v Reference will be checked at power up. The 
// value must be greater then 9.8 volts. After power up this will be used as 
// the dummy write register.

   QsmMap->ContRam[8].Cont = 0;     /* return chip select high after
				            				       						       transfer */
   QsmMap->ContRam[8].Bitse = 1;    /* number of bit set in SPCR0 reg */
   QsmMap->ContRam[8].Dt = 1;       /* Delay after transfer */
   QsmMap->ContRam[8].Dsck = 0;     /* SPCR1 specifies value of delay from
				            				       						       PCS valid to SCK */    
   QsmMap->ContRam[8].Pcs = 0;      /* Peripheral Chip Select */

// SPIList[ActADC]
// 7890 Actuator
// 7890 Vin1 = LoadCell
   QsmMap->ContRam[9].Cont = 0;     /* return chip select high after
				            				       						       transfer */
   QsmMap->ContRam[9].Bitse = 1;    /* number of bit set in SPCR0 reg */
   QsmMap->ContRam[9].Dt = 1;       /* Delay after transfer */
   QsmMap->ContRam[9].Dsck = 1;     /* SPCR1 specifies value of delay from
				            				       						       PCS valid to SCK */    
   QsmMap->ContRam[9].Pcs = 3;      /* Peripheral Chip Select */

// 7890 Vin2 = Pressure
   QsmMap->ContRam[10].Cont = 0;    /* return chip select high after
				            				       						       transfer */
   QsmMap->ContRam[10].Bitse = 1;   /* number of bit set in SPCR0 reg */
   QsmMap->ContRam[10].Dt = 1;      /* Delay after transfer */
   QsmMap->ContRam[10].Dsck = 1;    /* SPCR1 specifies value of delay from
				            				       						       PCS valid to SCK */    
   QsmMap->ContRam[10].Pcs = 3;     /* Peripheral Chip Select */

   QsmMap->ContRam[11].Cont = 0;    /* Dummy Write   */
   QsmMap->ContRam[11].Bitse = 1;
   QsmMap->ContRam[11].Dt = 1;
   QsmMap->ContRam[11].Dsck = 1;
   QsmMap->ContRam[11].Pcs = 3;

// Actuator DAC 420 PVP Control

   InitPVP();

// Digital Pot updated when needed it shares reg[12] with the PVP


// Bar Graph
   InitBarGraph();

// Configures conversion for the PS and ACT 7890
   
   QsmMap->TxdData[2] = 0x1000; /* Start conversion for Amp In(ch1) */                                                                            
   QsmMap->TxdData[3] = 0x3000; /* Start conversion for Power In(ch2)*/                                                                            
   QsmMap->TxdData[4] = 0x5000; /* Start conversion for Memory In(ch3)*/
   QsmMap->TxdData[5] = 0x7000; /* Start conversion for Freq In(ch4) */                                                                            
   QsmMap->TxdData[6] = 0xb000; /* Start conversion for Ext Amp(ch6) */


// Read once at power up to check 10v ref then switch to Ext Freq 
   QsmMap->TxdData[7] = 0x9000; /* Start conversion for dummy(ch5) */
   QsmMap->TxdData[8] = 0x9000; /* Start conversion for dummy(ch5) */
   
   QsmMap->TxdData[9]  = 0x1000; /* Start conversion for Load Cell(ch1) */                                                                            
   QsmMap->TxdData[10] = 0x3000; /* Start conversion for Press Sensor(ch2) */                                                                            
   QsmMap->TxdData[11] = 0x5000; /* Start conversion for dummy */                                                                            
}


