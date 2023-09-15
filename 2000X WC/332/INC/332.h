/* $Header:   K:\APPS\PVCS Pro\332new\INC\332.H_V   2.5   May 10 1999 14:51:58   lmarkure  $ */
#ifndef reg332_H
#define reg332_H
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

   Filename:      332.h


            Written by: Laura Markure 
                  Date: 12/01/95  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             5/05/96      LAM         Initial
	  1            05/04/99      LAM         Updated per DIAB
	  2            05/10/99      LAM         added packed min and max size
 
 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  


/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
 

struct MMap
{
/*       Module Configuration Register   */
   UINT16 Simcr; 
   UINT16 Simtr;
   /* Clock Synthesizer Control Register*/
   UINT16 Syncr;
   UINT16 Rsr;
   UINT16 Simtre;
   UINT16 SimResv1[3]; 
   UINT16 Porte0; 
   UINT16 Porte1; 
   UINT16 Ddre; 
   UINT16 Pepar; 
   UINT16 Portf0; 
   UINT16 Portf1; 
   UINT16 Ddrf; 
   UINT16 Pfpar;
/*       System Protection Register (BYTE) */
/* NOTE:  SYPCR is a WRITE-ONCE register!   */
   UINT16 Sypcr; 
   UINT16 Picr; 
   UINT16 Pitr; 
   UINT16 Swsr; 
   UINT16 SimResv2[4]; 
   UINT16 Tstmsra; 
   UINT16 Tstmsrb; 
   UINT16 Tstsc; 
   UINT16 Tstrc; 
   UINT16 Creg; 
   UINT16 Dreg; 
   UINT16 SimResv3[2]; 
   UINT16 Portc; 
   UINT16 SimResv4; 
   UINT16 Cspar0; 
   UINT16 Cspar1; 
   UINT16 Csbarbt; 
   UINT16 Csorbt;
   struct CS{
      UINT16 Csbar;
      UINT16 Csor;
   }ChipSel[11];
   UINT16 SimResv5[4]; 
} ;



 __packed__(4,1) struct MQMap
{
/*       QSM Module Configuration Register   */
   __packed__(4,1) struct{
      UINT16 Stop:1;  /* external clock off */
      UINT16 FRZ1:1;  /* freeze software enable */
      UINT16 FRZ0:1;  /* freeze bus monitor enable */
	    	UINT16 :5;	  								  
      UINT16 SUPV:1;  /* supervisor/unrestricted data space */
	    	UINT16 :3;	  							  
      UINT16 Iarb:4;  /* module mapping */
   }Qmcr;
   UINT16 Qtest;
   __packed__(4,1) struct{
      UINT8 :2;
      UINT8 Ilqspi:3;
      UINT8 Ilsci:3;
   }Qilr;
   UINT8 Qivr;
   UINT16 QsmResv1;
   UINT16 Sccr0;
   __packed__(4,1) struct{
      UINT8 :1;
      UINT8 Loops:1;
      UINT8 Woms:1;
      UINT8 Ilt:1;
      UINT8 Pt:1;
      UINT8 Pe:1;
      UINT8 M:1;
      UINT8 Tie:1;
      UINT8 Tcie:1;
      UINT8 Rie:1;
      UINT8 Ilie:1;
      UINT8 Te:1;
      UINT8 Re:1;
      UINT8 Rwu:1;
      UINT8 Sbk:1;
   }Sccr1;
   __packed__(4,1) struct{
      UINT8 :7;
      UINT8 Tdre:1;
      UINT8 Tc:1;
      UINT8 Rdrf:1;
      UINT8 Raf:1;
      UINT8 Idle:1;
      UINT8 Or:1;
      UINT8 Nf:1;
      UINT8 Fe:1;
      UINT8 Pf:1;
   }Scsr;
   UINT16 Scdr;
   UINT16 PortQs;
   UINT16 QsmResv2;
   UINT8 QsmResv3;
   UINT8 Qpdr;
   __packed__(4,1) struct{
      UINT8 :1;
      UINT8 Pcs:4;
      UINT8 :1;
      UINT8 Mosi:1;
      UINT8 Miso:1;
   }Qpar;
   __packed__(4,1) struct{
      UINT8 Txd:1;
      UINT8 Pcs:4;
      UINT8 Sck:1;
      UINT8 Mosi:1;
      UINT8 Miso:1;
   }Qddr;
   __packed__(4,1) struct{
      UINT8 Mstr:1;
      UINT8 Womq:1;
      UINT8 Bits:4;
      UINT8 Cpol:1;
      UINT8 Cpha:1;
      UINT8 Spbr:8;
   }Spcr0;
   __packed__(4,1) struct{
      UINT8 Spe:1;
      UINT8 Dsckl:7;
      UINT8 Dtl:8;
   }Spcr1;
   __packed__(4,1) struct{
      UINT8 Spifie:1;
      UINT8 Wren:1;
      UINT8 Wrto:1;
      UINT8 :1;
      UINT8 Endqp:4;
      UINT8 :4;
      UINT8 Newqp:4;
   }Spcr2;
   __packed__(4,1) struct{
      UINT8 :5;
      UINT8 Loopq:1;
      UINT8 Hmie:1;
      UINT8 Halt:1;
   }Spcr3;
      __packed__(4,1) struct{
         UINT8 Spif:1;
         UINT8 Modf:1;
         UINT8 Halta:1;
         UINT8 :1;
         UINT8 Cptqp:4;
      }Spsr;
      UINT8 QsmResv4[224];
      UINT16 RxdData[16];
      UINT16 TxdData[16];
   __packed__(4,1) struct ComdR{
      UINT8 Cont:1;   
      UINT8 Bitse:1;   
      UINT8 Dt:1;     
      UINT8 Dsck:1;   
      UINT8 Pcs:4;  
   }ContRam[16];
};

#endif