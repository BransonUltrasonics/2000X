/* $Header:   K:/APPS/PVCS Pro/PSS68k.222/BSP/src/tpu.c_v   1.2   Dec 13 2000 10:47:32   lmarkure  $ */
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
 ---------------------------- MODULE DESCRIPTION ---------------------------
  Name: tpu.c Initializes the tpu registers

 -------------------------------- REVISIONS ---------------------------------

   Rev #     Date         Author      Description
   -----     --------     ------      -----------
   1.0       04/06/99     LAM         Initial Release under new ver of psos,
                                      created from tpu.c rev 2.19
   1.1       04/29/99     LAM         fixed m68332.h
   1.2       12/13/00     LAM         update timing for the 24.117Mhz


--------------------------- INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "332.h"
#include "bsp.h"
#include <bspfuncs.h>
#include "wc_isr.h"
#include "inports.h"
#include <m68332.h>

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/                                                              

/*
 ----------------------------- LOCAL FUNCTIONS ----------------------------------
*/                                                           

/*
 ------------------------------- LOCAL DATA ------------------------------------
*/


void InitTPU(void)
{
/****************************************************************************/ 
/*                                                                          */    
/* All 16 Channels will be used except for Channel 6. Channels 4 & 15       */
/* will generate interrupts. The interrupt vector # is 50H + the            */
/* Channel #. The Interrupt level is 6 and the interrupt arbitration is set */
/* to 0eH.                                                                  */     
/*    TPUCH#      DESCRIPTION      FUNCTION         IRQ                     */
/*      0         1 ms tick         #9 Pwm           Yes                    */
/*      1         L.E. Index        #A Itc           Not used in level 1    */
/*      2         L.E. A(primary)   #6 Qdec          No                     */
/*      3         L.E. B            #6 Qdec          No                     */
/*      4         P.B. 1            #A Itc           Not used in level 1    */
/*      5         P.B. 2            #A Itc           Not used in level 1    */
/*      7         Keyboard CLK      #9 Pwm           No                     */
/*      8         VF Busy           #8 Dio(Input)    No                     */
/*      9         Beeper            #9 Pwm           No                     */
/*      10        Dig Pot U/D       #8 Dio(output)   No                     */
/*      11        memstoreoutput    #8 Dio(output)   No                     */
/*      12        Drenable(485)     #8 Dio(output)   Not used               */
/*      13        ULS               #8 Dio(input)    NOt used in level 1    */
/*      14        TRS               #8 Dio(input)    NOt used in level 1    */
/*      15        memstoreinput     #A Itc(input)    Yes                    */
/*                                                                          */    
/****************************************************************************/ 
	/* CHGGEDD !!!! Set the value of register TPUMCR to 0x008D. */
	/*      Field STOP = 0 */
	/*      Field TCR1P = 0 */
	/*      Field TCR2P = 0 */
	/*      Field EMU = 0 */
	/*      Field T2CG = 0 */
	/*      Field STF = 0 */
	/*      Field SUPV = 1 */
	/*      Field PSCK = 0 */
	/*      Field MT0 = 0 */
	/*      Field IARB = 13 */

   SysSetVector(V_MSINT, MinMsInt, NORMAL_WRAPPER);
   SysSetVector(V_STOREINT, StoreInt, NORMAL_WRAPPER);

   asm(" move.w #0,$fffe1c");    /* TpuMap->Cpr0 = 0;  Disable all Int */ 
   asm(" move.w #0,$fffe1e");    /* TpuMap->Cpr1 = 0;  Disable all int */
   asm(" move.w #0,$fffe0a");    /* TpuMap->Cier = 0;  Disable all interrupts */
   asm(" move.w $fffe20,d0");    /* read interrupt status */ 
   asm(" move.w #0,$fffe20");    /* clear interrupt status */

   asm(" move.w #$0d,$fffe00");  /* set iarb = d */

   asm(" move.w #$0680,$fffe08");/* set irq6 vector 80 */

/* Set up Channel Functions   */
   asm(" move.w #$a000,$fffe0c"); /* Chs 12-15 */
   asm(" move.w #$8898,$fffe0e"); /* Chs 8-11 */
   asm(" move.w #$90aa,$fffe10"); /* Chs 4-7 */
   asm(" move.w #$6609,$fffe12"); /* Chs 0-3 Chan 1 not used*/


/* Channel Priority Register 
   Ch8 = L,Ch9 = OFF, Ch10 = L, ch11 = L , Ch13 = off, Ch14 = off, Ch15 = M */
   asm(" move.w #$8051,$fffe1c");
/* Ch0 = H, Ch2 = H, Ch3 = H, Ch4 = off, Ch5 = off, Ch6 = off, Ch7 = L */
   asm(" move.w #$40F3,$fffe1e");

/* Host Sequence Bits 
   Ch0 = 0, Ch2 = 0, Ch3 = 1, Ch4 = 1, Ch5 = 1, Ch7 = 0  */
   asm(" move.w #$510,$fffe16"); 
/* Ch8 = 0,Ch9 = 0, Ch10 = 0, Ch11 = 0, Ch12 = 0, Ch13 = 0, Ch14 = 0, Ch15 = 1 */
   asm(" move.w #$4000,$fffe14");

   asm(" move.w #$093,$ffff00");  /* force pin high */
   
   #if SYSTEM_CLOCK ==_21MHZ         /* 1ms Tick */
      asm(" move.w #$147,$ffff04");  /* hightime */
      asm(" move.w #$28f,$ffff06");  /* period  */

   #elif SYSTEM_CLOCK ==_24_642MHZ     
      asm(" move.w #$181,$ffff04");  /* hightime */
      asm(" move.w #$302,$ffff06");  /* period  */
   #elif SYSTEM_CLOCK ==_24_117MHZ     
      asm(" move.w #$179,$ffff04");  /* hightime */
      asm(" move.w #$2F2,$ffff06");  /* period  */
   #endif


   asm(" move.w #$26,$ffff38");   /* TpuMap->TpuPram2[3] = 0x36; Primary Ch */
   asm(" move.w #$21,$ffff3a");   /* TpuMap->TpuPram2[4] = 31;edge time lsb*/
   asm(" move.w #$0,$ffff22");    /* TpuMap->TpuPram3[2] position count */
   asm(" move.w #$36,$ffff28");   /* TpuMap->TpuPram3[3] = 0x26;Secondary CH */
   asm(" move.w #$21,$ffff2a");   /* TpuMap->TpuPram3[4] = 31 */
 
   asm(" move.w #$0b,$ffff40");   /* TpuMap->TpuPram0[0] = 0x0f; Input,either edge */
   asm(" move.w #$e,$ffff42");    /* TpuMap->TpuPram0[1] = 0x2e; bank addr */
   asm(" move.w #$0,$ffff44");    /* TpuMap->TpuPram0[2] = 0x2;  max count */

   asm(" move.w #$0b,$ffff50");   /* TpuMap->TpuPram0[0] = 0x0f; Input,rising edge */
   asm(" move.w #$e,$ffff52");    /* TpuMap->TpuPram0[1] = 0x2e; bank addr */
   asm(" move.w #$0,$ffff54");    /* TpuMap->TpuPram0[2] = 0x2;  max count */

/* 6.25 ms */
   asm(" move.w #$093,$ffff70");  /* 0[0] = 0x0f; Input,either edge */
   
   #if SYSTEM_CLOCK ==_21MHZ         /* Keyboard Controller */
      asm(" move.w #$0800,$ffff74"); 
      asm(" move.w #$1000,$ffff76"); 
  
   #elif SYSTEM_CLOCK ==_24_642MHZ   
      asm(" move.w #$0966,$ffff74"); 
      asm(" move.w #$12CC,$ffff76"); 
   #elif SYSTEM_CLOCK ==_24_117MHZ   
      asm(" move.w #$0933,$ffff74"); 
      asm(" move.w #$1266,$ffff76"); 
   #endif


   asm(" move.w #$10f,$ffff80");  /* TpuMap->TpuPram0[0] = Input,either edge */
   asm(" move.w #$0,$ffff82");    /* TpuMap->TpuPram0[1] = input reg. */

   asm(" move.w #$093,$ffff90");  /* TpuMap->TpuPram0[0] = 0x0f; Input,either edge */

   #if SYSTEM_CLOCK ==_21MHZ        /* Beeper */
      asm(" move.w #$100,$ffff94"); 
      asm(" move.w #$200,$ffff96"); 

   #elif SYSTEM_CLOCK ==_24_642MHZ  
      asm(" move.w #$12D,$ffff94"); 
      asm(" move.w #$25A,$ffff96"); 
   #elif SYSTEM_CLOCK ==_24_117MHZ  
      asm(" move.w #$126,$ffff94"); 
      asm(" move.w #$24D,$ffff96"); 
   #endif


   asm(" move.w #$03,$ffffa0");   /* Output Do Not Force */

   asm(" move.w #$03,$ffffb0");   /* Output Do Not Force */
   
/* Channel 15 */
   asm(" move.w #$48,$fffff0");   /* Input,falling edge */
   asm(" move.w #$be,$fffff2"); /* bank addr */
   asm(" move.w #$1,$fffff4");    /* max count = 1*/

/* Host Service Request Bits */
/* Ch8 = 3,Ch9 = 2, Ch10 = 2, Ch11 = 1, Ch12 = 0, Ch13 = 0, Ch14 = 0, Ch15 = 1*/
   asm(" move.w #$40ab,$fffe18");

/* Ch0 = 2,Ch1 = 1, Ch2 = 3, Ch3 = 3, Ch4 = 1, Ch5 = 1, Ch7 = 2  */
   asm(" move.w #$85f6,$fffe1a");

   asm(" move.w #$08001,$fffe0a");    

}
