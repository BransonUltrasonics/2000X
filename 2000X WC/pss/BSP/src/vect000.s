* @(#) pSOSystem/68K V2.2.2: bsps/template/src/68k/vector.s (diab) 2.15 97/06/20 11:47:51 *
* $Header:   K:\APPS\PVCS Pro\PSS68k.222\Configs\std\config.mkv   1.2   Apr 05 1999 13:38:52   lmarkure  $
*************************************************************************
*                                                                       *
*   MODULE:  bsps/devices/68k/vect0x0.s                                 *
*   DATE:    97/06/20                                                   *
*   PURPOSE: Common 68k BSP assembly language routines                  *
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
*************************************************************************
*
*
* -------------------------------- REVISIONS ---------------------------
*
*   Revision #     Date        Author   Description
*   ----------     -------     ------   -----------
*    0             4/30/99     LAM      Initial
*


        XDEF _ExceptionHandlers,_Vectors
        XDEF _pMontIEnter,_pMontIReturn
 
        .data
        ALIGN 4
_pMontIEnter:
        DC.L 0
_pMontIReturn:
        DC.L 0

        .sdata
        ALIGN 4
_Vectors:
        DS.B 1024
_ExceptionHandlers:
        DS.B 1024
 
        .text

        XREF    _VectorPage,_ExcludedVectors
        XREF    _anchor

*************************************************************************
*  SysSetVector                                                         *
*                                                                       *
*       SYNTAX: SysSetVector(vector number, (void (*)())isr,            *
*                            wrapper number);                           *
*       INPUTS:                                                         *
*               vector number is the index into the vector table        *
*                   to install this handler.                            *
*               isr is the address of the Interrupt Service Routine     *
*                   that will service this interrupt                    *
*               wrapper number This is the number of the assemble code  *
*                   wrapper that will receive the interrupt and         *
*                   transfer control to a C coded fuction after         *
*                                                                       *
*      RETURNS: NONE                                                    *
*      OUTPUTS: NONE                                                    *
*      NOTE(S): SysSetVector first searches the list of                 *
*               Excluded Vectors. The ExcludedVectors array is set in   *
*               the configs/std/sysinit.c. It uses a #define called     *
*               EXCLUDED_VECTORS found in ../bsp.h. This is a list of   *
*               vectors which should be left alone by pSOSystem.        *
*               Vectors in the "excluded" list will not be initialized. *
*                                                                       *
*                                                                       *
*************************************************************************

        XDEF    _SysSetVector
_SysSetVector:
        MOVE.W  6(SP),D0                 ;get the vector number off the 
*                                        ;stack and store it in D0
*
*------------------------------------------------------------------------
* SEE IF VECTOR IS in the "EXCLUDED" list
*------------------------------------------------------------------------
        LEA     _ExcludedVectors,A0
CHK_LOOP:
        MOVE.W  (A0)+,D1                 ;Move vector off excluded list to
*                                        ;D0 and increment to next vector
*                                        ;in excluded list
        BEQ.S    NOT_EXCLUDED            ;0 INDICATES END OF LIST
        CMP.W    D0,D1                   ;Check for match
        BNE.S    CHK_LOOP                ;branch to top of loop if no
*                                        ;match
        RTS                              ;VECTOR IS "EXCLUDED" - JUST RETURN
NOT_EXCLUDED:
        LSL.W   #2,D0                    ;multiply vector number by 4
        MOVEA.L #_ExceptionHandlers,A0   ;move address of indirect handler
*                                        ;table to A0
        MOVE.L  8(SP),(A0,D0.W)          ;move ISR address to indirect
*                                        ;handler table using vector
*                                        ;number as offset into table
        TST.L   12(SP)                   ;check for wrapper type
        BNE.S   L1                       ;if not 0 branch to wrapper code
        MOVE.L  4(SP),D0                 ;wrapper type was 0 no wrapper
*                                        ;needed
        LSL.L   #2,D0                    ;multiply vector number by 4
        MOVEC   VBR,A0                   ;get vector base address
        MOVE.L  8(SP),(A0,D0.L)          ;move ISR address to vector table
*                                        ;using vector as an offset
        RTS                              ;done
L1:
        MOVEQ   #1,D0                    ;move NORMAL_WRAPPER # to D0
        CMP.L   12(SP),D0                ;check wrapper argument with D0
        BNE.S   L3                       ;branch if argument not
*                                        ;NORMAL_WRAPPER
        MOVE.L  4(SP),D0                 ;move vector number to D0
        LSL.L   #2,D0                    ;multiply vector number by 4
        MOVEA.L #_VectorPage,A0          ;move vector table address to A
*
*        MOVEA.L #_pMontIReturn,A1         
*        MOVE.L  (A1),D1
*        BEQ.S   L1A
*
*        MOVE.L  #_pMontNormalWrapper,(A0,D0.L)
*        RTS

*L1A:
        MOVE.L  #_NormalWrapper,(A0,D0.L) ;move address of NORMAL_WRAPPER
*                                        ;code to vector table using
*                                        ;vector number as an offset
        RTS                              ;Done
L3:
        MOVEQ   #2,D0                    ;move NI_WRAPPER # to D0
        CMP.L   12(SP),D0                ;check wrapper argument with D0
        BNE.S   L5                       ;branch if argument not
*                                        ;NI_WRAPPER
        MOVE.L  4(SP),D0                 ;move vector number to D0
        LSL.L   #2,D0                    ;multiply vector number by 4
        MOVEA.L #_VectorPage,A0          ;move vector table address to A
*
*        MOVEA.L #_pMontIReturn,A1
*        MOVE.L  (A1),D1
*        BEQ.S   L3A
*
*        MOVE.L  #_pMontNiWrapper,(A0,D0.L)
*        RTS
*L3A:
        MOVE.L  #_NiWrapper,(A0,D0.L)    ;move address of NiWrapper
*                                        ;code to vector table using
*                                        ;vector number as an offset
        RTS                              ;Done
L5:
        MOVEQ   #3,D0                    ;move MBRK_WRAPPER # to D0
        CMP.L   12(SP),D0                ;check wrapper argument with D0
        BNE.S   L6                       ;branch if argument not
*                                        ;MBRK_WRAPPER
        MOVE.L  4(SP),D0                 ;move vector number to D0
        LSL.L   #2,D0                    ;multiply vector number by 4
        MOVEA.L #_VectorPage,A0          ;move vector table address to A0
        MOVE.L  #_MbrkWrapper,(A0,D0.L)  ;move address of MBRK_WRAPPER
*                                        ;code to vector table using
*                                        ;vector number as an offset
L6:
        MOVEQ   #4,D0
        CMP.L   12(SP),D0
        BNE.S   L2
        MOVE.L  4(SP),D0
        LSL.L   #2,D0
        MOVEA.L #_VectorPage,A0
*
        MOVE.L  #_pMontIReturn,A1
        MOVE.L  (A1),D1
        BEQ.S   L6A
*
        MOVE.L  #_pMontBreakChkWrapper,(A0,D0.L)
L6A:
L2:
        RTS

*
*------------------------------------------------------------------------
* DEFINE THE TRAP NUMBER USED FOR THE pSOS+ "RETURN FROM INTERRUPT"
* ENTRY POINT.
*------------------------------------------------------------------------
I_RETURN    EQU      13                  ;TRAP # FOR pSOS+ I_RETURN CALL


*************************************************************************
* NormalWrapper: GENERAL-PURPOSE INTERRUPT HANDLER WRAPPER              *
*                                                                       *
*        NOTES: CALLS THE APPROPRIATE HANDLER FOR THE INTERRUPT OR      *
*               EXCEPTION THAT OCCURRED.  THE HANDLER MAY BE WRITTEN    *
*               IN C BECAUSE THIS "WRAPPER" CODE SAVES & RESTORES THE   *
*               SCRATCH REGISTERS.                                      *
*                                                                       *
*************************************************************************
_NormalWrapper:
        MOVEM.L  A0/A1/D0/D1,-(SP)   ;SAVE MICROTEC "C" SCRATCH REGS
        MOVE.W   22(SP),D0           ;D0: FORMAT/OFFSET WORD
        ANDI.L   #$FFF,D0            ;D0: VECTOR OFFSET
        LEA      _ExceptionHandlers,A0 ;A0-> INDIRECT HANDLER TABLE
        MOVEA.L  0(A0,D0),A0         ;A0-> HANDLER
        JSR      (A0)                ;CALL THE HANDLER
        MOVEM.L  (SP)+,A0/A1/D0/D1   ;RESTORE SAVED REGISTERS
        TRAP     #I_RETURN           ;LET pSOS CHECK FOR DISPATCH

*************************************************************************
* pMontNormalWrapper: GENERAL-PURPOSE INTERRUPT HANDLER WRAPPER         *
*                                                                       *
*        NOTES: CALLS THE APPROPRIATE HANDLER FOR THE INTERRUPT OR      *
*               EXCEPTION THAT OCCURRED.  THE HANDLER MAY BE WRITTEN    *
*               IN C BECAUSE THIS "WRAPPER" CODE SAVES & RESTORES THE   *
*               SCRATCH REGISTERS.                                      *
*                                                                       *
*************************************************************************
_pMontNormalWrapper:
        MOVEM.L  A0/A1/D0/D1,-(SP)   ;SAVE "C" SCRATCH REGS
        MOVE.W   22(SP),D0           ;D0: FORMAT/OFFSET WORD
        ANDI.L   #$FFF,D0            ;D0: VECTOR OFFSET
        LEA      _ExceptionHandlers,A0 ;A0-> INDIRECT HANDLER TABLE
        MOVEA.L  0(A0,D0),A0         ;A0-> HANDLER
        JSR      (A0)                ;CALL THE HANDLER
        MOVE.L   _pMontIReturn,A0    ;CALL pMONT I_RETURN Entry.
        JSR      (A0)                ;CALL THE HANDLER
        MOVEM.L  (SP)+,A0/A1/D0/D1   ;RESTORE SAVED REGISTERS
        TRAP     #I_RETURN           ;LET pSOS CHECK FOR DISPATCH

*************************************************************************
* pMontBreakChkWrapper: Same as _NormalWrapper however it will check the*
*                  return value in D0. If that value is non zero        *
*                  a jump to pROBE's manual break function will be      *
*                  done instead of a trap to pSOS's I_RETURN.           *
*                                                                       *
*        NOTES: CALLS THE APPROPRIATE HANDLER FOR THE INTERRUPT OR      *
*               EXCEPTION THAT OCCURRED.  THE HANDLER MAY BE WRITTEN    *
*               IN C BECAUSE THIS "WRAPPER" CODE SAVES & RESTORES THE   *
*               SCRATCH REGISTERS.                                      *
*                                                                       *
*************************************************************************
_pMontBreakChkWrapper:
        MOVEM.L  A0/A1/D0/D1,-(SP)   ;SAVE "C" SCRATCH REGS
        MOVE.W   22(SP),D0           ;D0: FORMAT/OFFSET WORD
        ANDI.L   #$FFF,D0            ;D0: VECTOR OFFSET
        LEA      _ExceptionHandlers,A0 ;A0-> INDIRECT HANDLER TABLE
        MOVEA.L  0(A0,D0),A0         ;A0-> HANDLER
        JSR      (A0)                ;CALL THE HANDLER
        TST.W    D0                  ;IF D0 != 0
        BNE.S    PB_x                ;BRANCH TO RETURN THROUGH PROBE
        MOVE.L   _pMontIReturn,A0    ;pMONT I_RETURN Entry
        JSR      (A0)                ;CALL THE HANDLER
        MOVEM.L  (SP)+,A0/A1/D0/D1   ;RESTORE SAVED REGISTERS
        TRAP     #I_RETURN           ;LET pSOS CHECK FOR DISPATCH
PB_x:   MOVEM.L  (SP)+,A0/A1/D0/D1   ;RESTORE SAVED REGISTERS
        MOVE.L   _anchor,A0         ;A0-> node config table
        MOVE.L   12(A0),A0           ;A0-> pROBE config table
        MOVE.L   (A0),A0             ;A0-> pROBE code
        ADDA.L   #$A0,A0             ;A0-> pROBE mbrk entry
        MOVE.L   A0,16(SP)           ;PUT pROBE mbrk entry on stack
 
        MOVEM.L  (SP)+,A0/A1/D0/D1   ;RESTORE SCRATCH REGS
        RTS

*************************************************************************
*    NiWrapper: "NETWORK INTERFACE" INTERRUPT HANDLER WRAPPER           *
*                                                                       *
*        NOTES: CALLS THE APPROPRIATE HANDLER FOR THE INTERRUPT OR      *
*               EXCEPTION THAT OCCURRED.  THE HANDLER MAY BE WRITTEN    *
*               IN C BECAUSE THIS "WRAPPER" CODE SAVES & RESTORES THE   *
*               SCRATCH REGISTERS.  THE WRAPPER TERMINATES WITH AN RTE  *
*               INSTRUCTION IF THE HANDLER RETURNS 0.  OTHERWISE IT     *
*               TERMINATES BY TRAPPING TO pSOS+.  THIS WRAPPER SHOULD   *
*               BE USED AROUND ISR'S FOR NETWORK INTERFACE DRIVERS.     *
*                                                                       *
*************************************************************************
_NiWrapper:
        MOVEM.L  A0/A1/D0/D1,-(SP)   ;SAVE MICROTEC "C" SCRATCH REGS
        MOVE.W   22(SP),D0           ;D0: FORMAT/OFFSET WORD
        ANDI.L   #$FFF,D0            ;D0: VECTOR OFFSET
        LEA      _ExceptionHandlers,A0 ;A0-> INDIRECT HANDLER TABLE
        MOVEA.L  0(A0,D0),A0         ;A0-> HANDLER
        JSR      (A0)                ;CALL THE HANDLER
        TST.B    D0                  ;IS pSOS INITIALIZED?
        MOVEM.L  (SP)+,A0/A1/D0/D1   ;RESTORE SCRATCH REGS (LEAVES
        BEQ.S    DORTE               ;  CONDITION CODES ALONE)
        TRAP     #I_RETURN           ;USE I_RET IF pSOS INIT
DORTE:
        RTE                          ;OTHERWISE JUST USE RTE

*************************************************************************
*pMontNiWrapper:"NETWORK INTERFACE" INTERRUPT HANDLER WRAPPER           *
*                                                                       *
*        NOTES: CALLS THE APPROPRIATE HANDLER FOR THE INTERRUPT OR      *
*               EXCEPTION THAT OCCURRED.  THE HANDLER MAY BE WRITTEN    *
*               IN C BECAUSE THIS "WRAPPER" CODE SAVES & RESTORES THE   *
*               SCRATCH REGISTERS.  THE WRAPPER TERMINATES WITH AN RTE  *
*               INSTRUCTION IF THE HANDLER RETURNS 0.  OTHERWISE IT     *
*               TERMINATES BY TRAPPING TO pSOS+.  THIS WRAPPER SHOULD   *
*               BE USED AROUND ISR'S FOR NETWORK INTERFACE DRIVERS.     *
*                                                                       *
*************************************************************************
_pMontNiWrapper:
        MOVEM.L  A0/A1/D0/D1,-(SP)   ;SAVE MICROTEC "C" SCRATCH REGS
        MOVE.W   22(SP),D0           ;D0: FORMAT/OFFSET WORD
        ANDI.L   #$FFF,D0            ;D0: VECTOR OFFSET
        LEA      _ExceptionHandlers,A0 ;A0-> INDIRECT HANDLER TABLE
        MOVEA.L  0(A0,D0),A0         ;A0-> HANDLER
        JSR      (A0)                ;CALL THE HANDLER
        TST.B    D0                  ;IS pSOS INITIALIZED?
        BEQ.S    DORTEX              ;  CONDITION CODES ALONE)
        MOVE.L   _pMontIReturn,A0
        JSR      (A0)                ;CALL THE pMONT I_RETURN Entry
        MOVEM.L  (SP)+,A0/A1/D0/D1   ;RESTORE SCRATCH REGS (LEAVES
        TRAP     #I_RETURN           ;USE I_RET IF pSOS INIT
DORTEX:
        MOVEM.L  (SP)+,A0/A1/D0/D1   ;RESTORE SCRATCH REGS (LEAVES
        RTE                          ;OTHERWISE JUST USE RTE

*************************************************************************
*  MbrkWrapper: "MANUAL BREAK" INTERRUPT HANDLER WRAPPER                *
*                                                                       *
*        NOTES: CALLS THE APPROPRIATE HANDLER FOR THE INTERRUPT, AND    *
*               THEN TRANSFERS CONTROL TO THE "MANUAL BREAK" ENTRY OF   *
*               pROBE+.  THE HANDLER MAY BE WRITTEN IN C BECAUSE THIS   *
*               WRAPPER SAVES AND RESTORES THE SCRATCH REGISTERS.       *
*                                                                       *
*************************************************************************
_MbrkWrapper:
        SUBQ.L   #4,SP               ;ALLOCATE A SPACE ON STACK
        MOVEM.L  A0/A1/D0/D1,-(SP)   ;SAVE MICROTEC "C" SCRATCH REGS
        MOVE.W   26(SP),D0           ;D0: FORMAT/OFFSET WORD
        ANDI.L   #$FFF,D0            ;D0: VECTOR OFFSET
        LEA      _ExceptionHandlers,A0 ;A0-> INDIRECT HANDLER TABLE
        MOVEA.L  0(A0,D0),A0         ;A0-> HANDLER
        JSR      (A0)                ;CALL THE HANDLER
        MOVE.L   _anchor,A0          ;A0-> node config table
        MOVE.L   12(A0),A0           ;A0-> pROBE config table
        MOVE.L   (A0),A0             ;A0-> pROBE code
        ADDA.L   #$A0,A0             ;A0-> pROBE mbrk entry
        MOVE.L   A0,16(SP)           ;PUT pROBE mbrk entry on stack

        MOVEM.L  (SP)+,A0/A1/D0/D1   ;RESTORE SCRATCH REGS
        RTS


        END

