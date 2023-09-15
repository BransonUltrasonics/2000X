* @(#) pSOSystem/68K V2.2.2: bsps/e302/src/hdwinit.s (en302 diab) 1.17 97/05/05 10:49:23 *
* $Header:   K:\APPS\PVCS Pro\PSS68K.222\BSP\SRC\init.s_v   1.0   Mar 29 1999 13:40:56   ofingere  $ */
*************************************************************************
*                                                                       *
*   MODULE:  bsps/e302/src/hdwinit.s                                    *
*   DATE:    97/05/05                                                   *
*   PURPOSE: RESET VECTOR, ENTRY POINT FOR pSOSystem bsp                *
*                                                                       *
*-----------------------------------------------------------------------*
*                                                                       *
*          COPYRIGHT 1991 - 1997, INTEGRATED SYSTEMS, INC.              *
*                       ALL RIGHTS RESERVED                             *
*                                                                       *
*    PERMISSION IS HEREBY GRANTED TO LICENSEES OF INTEGRATED SYSTEMS,   *
*    INC. PRODUCTS TO USE OR ABSTRACT THIS COMPUTER PROGRAM FOR THE     *
*    SOLE PURPOSE OF IMPLEMENTING A PRODUCT BASED ON INTEGRATED         *
*    SYSTEMS, INC. PRODUCTS.   NO OTHER RIGHTS TO REPRODUCE, USE,       *
*    OR DISSEMINATE THIS COMPUTER PROGRAM, WHETHER IN PART OR IN        *
*    WHOLE, ARE GRANTED.                                                *
*                                                                       *
*    INTEGRATED SYSTEMS, INC. MAKES NO REPRESENTATION OR WARRANTIES     *
*    WITH RESPECT TO THE PERFORMANCE OF THIS COMPUTER PROGRAM, AND      *
*    SPECIFICALLY DISCLAIMS ANY RESPONSIBILITY FOR ANY DAMAGES,         *
*    SPECIAL OR CONSEQUENTIAL, CONNECTED WITH THE USE OF THIS PROGRAM.  *
*                                                                       *
*-----------------------------------------------------------------------*
*                                                                       *
*    THE MC68xx302'S USE A 68000 CORE WHICH HAS NO VBR. THEREFORE       *
*    RAM MUST BE AT LOCATION ZERO TO CHANGE THE VECTORS IN THE          *
*    VECTOR TABLE. AFTER INITIAL POWER ON ONLY 8K BYTES ARE ACTIVE      *
*    AT LOCATION ZERO. THE BAR IS PROGRAMMED TO SET THE BASE ADDRESS    *
*    OF THE DPRAM AND 68302 REGISTERS. IF YOU CHANGE THIS ADDRESS,      *
*    YOU MUST CHANGE ALL THE ADDRESSES OF THE CHIP SELECT BASE AND      *
*    OPTION REGISTERS AND THE DPRAM ADDRESS TO MATCH. THE CODE THAT     *
*    SWAPS THE RAM AND ROM ADDRESSES MUST BE RUN FROM THE DPRAM         *
*    SINCE IT WILL NOT CHANGE LOCATION WHEN THE ROM IS MOVED.           *
*                                                                       *
*    THIS CODE MUST BE LOCATED IN THE FIRST 8K BYTES. ALL OTHER         *
*    CODE MUST BE LOCATED AT THE FINAL ROM ADDRESS (LEAVING ROOM        *
*    FOR THIS CHIP SELECT SETUP CODE).                                  *
*                                                                       *
*************************************************************************
* --------------------------------- REVISIONS -------------------------
*
* Rev # Date     Author  Description
* ===== ======== ======  =============================================
* 1.0   03/26/99 OFI     Original Version
* 1.1   04/05/99 LAM     Updated per new version of psos this file replaces
*                        hdwinit.s
* 1.2   05/26/99 LAM     changed flash from 1 wait state to zero wait state
* 1.3   12/13/00 LAM     changed system clock to 24_117Mhz
* 1.4   12/13/00 LAM     added loop on SLOCK

*

        XREF    _InitBoard
*
*------------------------------------------------------------------------
*
*                     R E S E T   V E C T O R
*
* THE VERY FIRST THING IN THE SYSTEM IS THE 68K RESET VECTOR.  IF THIS
* CODE IS PLACED IN ROM, THE CPU WILL FETCH THE INITIAL STACK POINTER
* AND PROGRAM COUNTER FROM HERE.  IF THIS CODE IS DOWNLOADED TO A
* SYSTEM VIA THE TFTP BOOTLOADER IN THE pSOSystem ROMS, THE BOOTLOADER
* ALSO USES THIS RESET VECTOR TO START THE SYSTEM RUNNING.
*------------------------------------------------------------------------
 
    .data
    ALIGN   4
	XREF	_VectorPage
	XDEF	_InitialStackPointer
_InitialStackPointer EQU $013fffe      ;SET TO ACTUAL ADDRESS

        XREF    _InitBoard,_SysInit,_SysInitVars
*     	.text

        SECTION BEGIN,,C
        XDEF _HdwInit

_HdwInit:
        LEA     _VectorPage,A0           ;INITIALIZE VBR
        MOVEC   A0,VBR


* Start Chip Select Initialization: *
*   MOVE.W #$2700,SR             * turn off interrupts

* Now let's go to 20.97 MHZ:             
* Set the value of register SYNCR 
*      Field W = 1   VCO * 4
*      Field X = 1   doubles current speed
*      Field Y = 0x13    counts down
*      Field EDIV  = 0   system clk divided by 8
*      Field RSTEN = 1   loss of refence causes system reset.
*// chged for emulator     move.w #$D305,($00FFFA04).L

   MOVE.W #$9604,$00FFFA04	

SLOCK:
   MOVE.W   $00FFFA04,D0
   ANDI.W   #$0008,D0
   CMPI.W   #$0008,D0	
   BNE      SLOCK		
   ORI.W    #$4000,$00FFFA04

* Set the value of register SIMCR 
*      Field EXOFF = 0  
*      Field FRZSW = 1 watchdog and pit are disabled  
*      Field FRZBM = 0  
*      Field MT1   = 0     
*      Field SLVEN = 0  
*      Field MT2   = 0  
*      Field SHEN  = 2  show cycles enabled & enternal arb enabled
*      Field SUPV  = 1  
*      Field MM    = 1  internal modules at $fff000-$ffffff
*      Field IARB  = 14 
*// chged for the emulator     MOVE.W #$c3Cd,($00FFFA00).L  
   MOVE.W #$42Ce,$00FFFA00  

* Set up SYSTEM PROTECTION REGISTER:  */
* Set the value of register SYPCR 
   MOVE.B   #$0C,($00FFFA21).L  ; Turn off cop,enable HME DBF: BERR=16 clocks
 
* Enable Chip Selects 0 - 10
* Set the value of register CSPAR0 
*      Field CSPA06 = 8 bit
*      Field CSPA05 = 8 bit
*      Field CSPA04 = 16 bit
*      Field CSPA03 = 16 bit
*      Field CSPA02 = 16 bit
*      Field CSPA01 = 16 bit
*      Field CSBOOT* = 16 bit
   MOVE.W #$2BFF,($00FFFA44).L  ; CSPAR0

* Set the value of register CSPAR1 
*      Field CSPA14 = 8 bit
*      Field CSPA13 = 8 bit
*      Field CSPA12 = 8 bit
*      Field CSPA11 = 16 bit
*      Field CSPA10 = alternate function
   MOVE.W #$02AD,($00FFFA46).L  ; CSPAR1
   
* FIRST SET-UP THE BASE ADDRESSES 
* Set the value of register CSBARbt
*      Field ADDR = $000000 
*      Field BLKSZ = 1MB flash 
   MOVE.W #$0007,($00FFFA48).L  
* Set the value of register CSORbt
*      Field MODE = async
*      Field BYTE = both
*      Field R/W* = both
*      Field STRB = as
*      Field DSACK = 0 wait
*      Field SPACE = s/u
*      Field IPL = all
*      Field AVEC = off
*   MOVE.W #$7870,($00FFFA4A).L  1 wait state
   MOVE.W #$7830,($00FFFA4A).L  


* Set the value of register DDRE
*      Field DDE7 = 0 */
*      Field DDE6 = 0 */
*      Field DDE5 = 0 */
*      Field DDE4 = 0 */
*      Field DDE3 = 1 SVDRIVE_LO - OUTPUT */
*      Field DDE2 = 1 N/C - OUTPUT */
*      Field DDE1 = 0 */
*      Field DDE0 = 0 */
* DDE7=0, DDE6=0 (INPUTS) DDE3=1, DDE2=1 (OUTPUTS) 
   MOVE.B   #$0c,($00FFFA15).L  
   
* PE2, PE3, enabled as Port E pins 
   MOVE.B   #$f3,($00FFFA17).L  

* OUTPUTS = 0 
   MOVE.B   #$0,($00FFFA11).L  

* Set the value of register DDRF 
*      Field MT1 = 0 
*      Field DDF7 = 0
*      Field DDF6 = 0
*      Field DDF5 = 0
*      Field DDF4 = 0
*      Field DDF3 = 0
*      Field DDF2 = 0
*      Field DDF1 = 0
*      Field DDF0 = 0 SV_ON - INPUT
   MOVE.B   #$0,($00FFFA1D).L  
   MOVE.B   #$0,($00FFFA1F).L  ; PFPAR(only controlling irq 1,2& 5)
*   MOVE.B   #$26,($00FFFA1F).L  * PFPAR(only controlling irq 1,2& 5)
   
* Set the value of register CSBAR0 
*      Field ADDR = $100000
*      Field BLKSZ = 256k ram
   MOVE.W #$1005,($00FFFA4C).L  

* Set the value of register CSBAR1
*      Field ADDR = $100000 
*      Field BLKSZ = 256k ram
   MOVE.W #$1005,($00FFFA50).L  

* since we don't have the DPRAM, let's use CS2 for interrupts instead of CS7
* we need some CS line to use for autovectoring, and now we use CS7 for flash

* Set the value of register CSBAR2 was 1401
*      Field ADDR = 140000 
*      Field BLKSZ = 8k dpram
   MOVE.W #$FFF8,($00FFFA54).L  

* Set the value of register CSBAR3 
*      Field ADDR = 140000 
*      Field BLKSZ = 8k dpram
   MOVE.W #$1401,($00FFFA58).L  

* Set the value of register CSBAR4 
*      Field ADDR = 142000
*      Field BLKSZ = 2k vf display
   MOVE.W #$1420,($00FFFA5C).L  
   
* Set the value of register CSBAR5 
*      Field ADDR = 142800 
*      Field BLKSZ = 2k printer port
   MOVE.W #$1428,($00FFFA60).L

* Set the value of register CSBAR6 
*      Field ADDR = 000000 
*      Field BLKSZ = 2K disabled a19 used
   MOVE.W #$0000,($00FFFA64).L

* we need CS7 to point to flash at 2MB now, so we use CS2 for autovectoring instead of CS7
* Set the value of register CSBAR7 was FFF8
*      Field ADDR = FFF800
*      Field BLKSZ = 2K autovector
   MOVE.W #$2007,($00FFFA68).L

* Set the value of register CSBAR8 
*      Field ADDR = 143000 
*      Field BLKSZ = 2k keypad
   MOVE.W #$1430,($00FFFA6C).L
 
* Set the value of register CSBAR9 
*      Field ADDR = 150000 
*      Field BLKSZ = 64k  $150000 - 8255 I/O  $158000 - RTC
   MOVE.W #$1503,($00FFFA70).L

* Set the value of register CSBAR10 
*      Field ADDR = 160000 
*      Field BLKSZ = 64k  $160000 - 8255 I/O  $168000 - 32K BBRAM
   MOVE.W #$1603,($00FFFA74).L
   
* Set the value of register CSOR0 
*   SimMap->ChipSel[0].Csor.mode = ASYNC; 
*   SimMap->ChipSel[0].Csor.byte = CS_UPPB; 
*   SimMap->ChipSel[0].Csor.RW = CS_RW;  
*   SimMap->ChipSel[0].Csor.Strb = CS_AS; 
*   SimMap->ChipSel[0].Csor.Dsack = 0wait;
*   SimMap->ChipSel[0].Csor.Space = 3;
*   SimMap->ChipSel[0].Csor.Ipl = 0;  
*   SimMap->ChipSel[0].Csor.Avec = 0;
*// chged for the emulator   MOVE.W #$5FB0,($00FFFA4E).L  
  MOVE.W #$5830,($00FFFA4E).L  
   
* Set the value of register CSOR1 
*   SimMap->ChipSel[1].Csor.mode = ASYNC; 
*   SimMap->ChipSel[1].Csor.byte = CS_LOWB; 
*   SimMap->ChipSel[1].Csor.RW = CS_RW;  
*   SimMap->ChipSel[1].Csor.Strb = CS_AS; 
*   SimMap->ChipSel[1].Csor.Dsack = 0waits;
*   SimMap->ChipSel[1].Csor.Space = 3;
*   SimMap->ChipSel[1].Csor.Ipl = 0;  
*   SimMap->ChipSel[1].Csor.Avec = 0;
   MOVE.W #$3830,($00FFFA52).L  

* Set the value of register CSOR2 
*   SimMap->ChipSel[2].Csor.mode = ASYNC; 
*   SimMap->ChipSel[2].Csor.byte = CS_UPPB; 
*   SimMap->ChipSel[2].Csor.RW = CS_RW;  
*   SimMap->ChipSel[2].Csor.Strb = CS_AS; 
*   SimMap->ChipSel[2].Csor.Dsack = CS_0WAIT;
*   SimMap->ChipSel[2].Csor.Space = 3;
*   SimMap->ChipSel[2].Csor.Ipl = 0;  
*   SimMap->ChipSel[2].Csor.Avec = 0;
*   MOVE.W #$5830,($00FFFA56).L  
   
* this was before, but now we need CS2 to autovectoring, use same settings we had for CSOR7
* Set the value of register CSOR2 (autovector) 
*   SimMap->ChipSel[7].Csor.mode = ASYNC; 
*   SimMap->ChipSel[7].Csor.byte = 3; 
*   SimMap->ChipSel[7].Csor.RW = CS_R;  
*   SimMap->ChipSel[7].Csor.Strb = 0; 
*   SimMap->ChipSel[7].Csor.Dsack = 0;
*   SimMap->ChipSel[7].Csor.Space = 0;
*   SimMap->ChipSel[7].Csor.Ipl = 0;  
*   SimMap->ChipSel[7].Csor.Avec = 1;
   MOVE.W #$6801,($00FFFA56).L

*  Set the value of register CSOR3 
*   SimMap->ChipSel[3].Csor.mode = ASYNC; 
*   SimMap->ChipSel[3].Csor.byte = CS_LOWB; 
*   SimMap->ChipSel[3].Csor.RW = CS_RW;  
*   SimMap->ChipSel[3].Csor.Strb = CS_AS; 
*   SimMap->ChipSel[3].Csor.Dsack = CS_0WAIT;
*   SimMap->ChipSel[3].Csor.Space = 3;
*   SimMap->ChipSel[3].Csor.Ipl = 0;  
*   SimMap->ChipSel[3].Csor.Avec = 0;
  MOVE.W #$3830,($00FFFA5A).L  
 
*  Set the value of register CSOR4  (vf)
*   SimMap->ChipSel[4].Csor.mode = ASYNC; 
*   SimMap->ChipSel[4].Csor.byte = CS_UPPB; 
*   SimMap->ChipSel[4].Csor.RW = CS_RW;  
*   SimMap->ChipSel[4].Csor.Strb = CS_AS; 
*   SimMap->ChipSel[4].Csor.Dsack = CS_3WAIT;
*   SimMap->ChipSel[4].Csor.Space = 3;
*   SimMap->ChipSel[4].Csor.Ipl = 0;  
*   SimMap->ChipSel[4].Csor.Avec = 0;
   MOVE.W #$50f0,($00FFFA5E).L
 
* Set the value of register CSOR5 
*   SimMap->ChipSel[5].Csor.mode = ASYNC; 
*   SimMap->ChipSel[5].Csor.byte = CS_UPPB; 
*   SimMap->ChipSel[5].Csor.RW = CS_RW;  
*   SimMap->ChipSel[5].Csor.Strb = CS_AS; 
*   SimMap->ChipSel[5].Csor.Dsack = CS_4WAIT;
*   SimMap->ChipSel[5].Csor.Space = 3;
*   SimMap->ChipSel[5].Csor.Ipl = 0;  
*   SimMap->ChipSel[5].Csor.Avec = 0;
    MOVE.W #$5930,($00FFFA62).L
 
   
* Set the value of register CSOR6 (not used)
*   SimMap->ChipSel[6].Csor.mode = 0; 
*   SimMap->ChipSel[6].Csor.byte = 0; 
*   SimMap->ChipSel[6].Csor.RW = 0;  
*   SimMap->ChipSel[6].Csor.Strb = 0; 
*   SimMap->ChipSel[6].Csor.Dsack = 0;
*   SimMap->ChipSel[6].Csor.Space = 0;
*   SimMap->ChipSel[6].Csor.Ipl = 0;  
*   SimMap->ChipSel[6].Csor.Avec = 0;
   MOVE.W #$0000,($00FFFA66).L
   
* Set the value of register CSOR7(autovector) 
*   SimMap->ChipSel[7].Csor.mode = ASYNC; 
*   SimMap->ChipSel[7].Csor.byte = 3; 
*   SimMap->ChipSel[7].Csor.RW = CS_R;  
*   SimMap->ChipSel[7].Csor.Strb = 0; 
*   SimMap->ChipSel[7].Csor.Dsack = 0;
*   SimMap->ChipSel[7].Csor.Space = 0;
*   SimMap->ChipSel[7].Csor.Ipl = 0;  
*   SimMap->ChipSel[7].Csor.Avec = 1;
*   MOVE.W #$6801,($00FFFA6A).L

* CS7 is used to address flash same as CSBOOT, so put same 7830 into CSOR7

   MOVE.W #$7830,($00FFFA6A).L

* Set the value of register CSOR8 
*   SimMap->ChipSel[8].Csor.mode = ASYNC; 
*   SimMap->ChipSel[8].Csor.byte = CS_UPPB; 
*   SimMap->ChipSel[8].Csor.RW = CS_RW;  
*   SimMap->ChipSel[8].Csor.Strb = CS_AS; 
*   SimMap->ChipSel[8].Csor.Dsack = CS_4WAIT;
*   SimMap->ChipSel[8].Csor.Space = 3;
*   SimMap->ChipSel[8].Csor.Ipl = 0;  
*   SimMap->ChipSel[8].Csor.Avec = 0;
   MOVE.W #$5930,($00FFFA6E).L
   
* Set the value of register CSOR9 
*   SimMap->ChipSel[9].Csor.mode = ASYNC; 
*   SimMap->ChipSel[9].Csor.byte = CS_UPPB; 
*   SimMap->ChipSel[9].Csor.RW = CS_RW;  
*   SimMap->ChipSel[9].Csor.Strb = CS_AS; 
*   SimMap->ChipSel[9].Csor.Dsack = CS_4WAIT;
*   SimMap->ChipSel[9].Csor.Space = 3;
*   SimMap->ChipSel[9].Csor.Ipl = 0;  
*   SimMap->ChipSel[9].Csor.Avec = 0;
   MOVE.W #$5930,($00FFFA72).L

* Set the value of register CSOR10 
*   SimMap->ChipSel[10].Csor.mode = ASYNC;  
*   SimMap->ChipSel[10].Csor.byte = CS_UPPB; 
*   SimMap->ChipSel[10].Csor.RW = CS_RW;  
*   SimMap->ChipSel[10].Csor.Strb = CS_AS; 
*   SimMap->ChipSel[10].Csor.Dsack = CS_4WAIT;
*   SimMap->ChipSel[10].Csor.Space = 3;
*   SimMap->ChipSel[10].Csor.Ipl = 0;  
*   SimMap->ChipSel[10].Csor.Avec = 0;
   MOVE.W #$5930,($00FFFA76).L

   MOVE.W #$0100,($00FFFB00).L
   MOVE.W #$0000,($00FFFB02).L
   MOVE.W #$1750,($00FFFB04).L
   MOVE.W #$0000,($00FFFA22).L  ; PICR
   MOVE.W #$0000,($00FFFA24).L  ; PITR
   MOVE.B   #$00,($00FFFA41).L  ; PORTC
   

   JMP     (_InitBoard).L
   
   .text

   END
