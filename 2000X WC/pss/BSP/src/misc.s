* @(#) pSOSystem/68K V2.2.2: bsps/template/src/68k/misc.s (diab) 2.14 97/04/30 19:37:46 *
*************************************************************************
*                                                                       *
*   MODULE:  devices/misc.s                                             *
*   DATE:    97/04/30                                                   *
*   PURPOSE: miscellaneous common functions                             *
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
*                                                                       *
*-----------------------------------------------------------------------*
*                                                                       *
*                                                                       *
*                                                                       *
*************************************************************************
        XREF    _ExceptionHandlers

        .text

        XREF    GET_VBR

*************************************************************************
* MemAccessible: CHECK WHETHER A MEMORY LOCATION IS ACCESSIBLE          *
*                                                                       *
*       SYNTAX: ULONG MemAccessible(volatile void *address);            *
*      RETURNS: 1 IF MEMORY IS ACCESSIBLE, 0 IF NOT                     *
*                                                                       *
*         NOTE: THIS USES THE VBR RATHER THAN _VectorPage TO LOCATE     *
*               THE VECTOR PAGE.                                        *
*                                                                       *
*************************************************************************
        XDEF    _MemAccessible
_MemAccessible:
*
*------------------------------------------------------------------------
* DISABLE INTERRUPTS FOR THIS
*------------------------------------------------------------------------
        MOVE.L  #7,-(SP)        ;NEW MASK LEVEL WILL BE 7
        JSR     _splx
        ADDQ.L  #4,SP           ;CLEAN UP STACK
        MOVE.L  D0,D1           ;D1: OLD MASK
*
*------------------------------------------------------------------------
* TEMPORARILY REPLACE THE BUS ERROR VECTOR
*------------------------------------------------------------------------
        JSR     GET_VBR         ;A0->VECTOR PAGE
        MOVE.L  8(A0),-(SP)     ;SAVE EXISTING BUS ERROR VECTOR
        MOVE.L  #MEM_BERR,8(A0) ;INSTALL NEW VECTOR
*
*------------------------------------------------------------------------
* NOW DO THE TEST BY PROBING THE LOCATION IN QUESTION
*------------------------------------------------------------------------
        MOVE.L  SP,A1           ;SAVE STACK POINTER
        MOVE.L  8(SP),A0        ;A0: ADDRESS TO ACCESS
        MOVEQ.L #1,D0           ;PRESET RESULT TO "ACCESSIBLE"
        TST.B   (A0)            ;PROBE THE BYTE
        BRA.S   MEM_OK          ;IT'S ACCESSIBLE IF WE GOT HERE!
MEM_BERR:
        CLR.L   D0              ;SET RESULT TO "INACCESSIBLE"
MEM_OK:
        MOVEA.L A1,SP           ;RESTORE ORIGINAL STACK POINTER
*
*------------------------------------------------------------------------
* RESTORE THE ORIGINAL BUS ERROR VECTOR
*------------------------------------------------------------------------
        JSR     GET_VBR         ;A0->VECTOR PAGE
        MOVE.L  (SP)+,8(A0)     ;RESTORE BUS ERROR VECTOR
*
*------------------------------------------------------------------------
* RESTORE ORIGINAL INTERRUPT LEVEL
*------------------------------------------------------------------------
        MOVE.L  D0,-(SP)        ;SAVE VALUE TO RETURN
        MOVE.L  D1,-(SP)        ;OLD MASK LEVEL
        JSR     _splx           ;CHANGE THE LEVEL
        ADDQ.L  #4,SP           ;CLEAN UP STACK
        MOVE.L  (SP)+,D0        ;VALUE TO RETURN TO CALLER
*
        RTS                     ;RETURN

*************************************************************************
* SafeLongRead: READS LONG IF ADDRESS IS ACCESSIBLE, RETURNS 0 IF NOT.  *
*                                                                       *
*       SYNTAX: ULONG SafeLongRead(volatile void *address);             *
*      RETURNS: LONG VALUE IF MEMORY IS ACCESSIBLE, 0 IF NOT.           *
*                                                                       *
*         NOTE: THIS CALL IS USED WHEN READING AN ADDRESS MIGHT RESULT  *
*               IN A BUS ERROR.                                         *
*                                                                       *
*************************************************************************
        XDEF    _SafeLongRead
_SafeLongRead:
*
*------------------------------------------------------------------------
* DISABLE INTERRUPTS FOR THIS.
*------------------------------------------------------------------------
        MOVE.L  #7,-(SP)        ;NEW MASK LEVEL WILL BE 7
        JSR     _splx
        ADDQ.L  #4,SP           ;CLEAN UP STACK
        MOVE.L  D0,D1           ;D1: OLD MASK
*
*------------------------------------------------------------------------
* TEMPORARILY REPLACE THE BUS ERROR VECTOR.
*------------------------------------------------------------------------
        JSR     GET_VBR         ;A0->VECTOR PAGE
        MOVE.L  8(A0),-(SP)     ;SAVE EXISTING BUS ERROR VECTOR
        MOVE.L  #READ_BERR,8(A0) ;INSTALL NEW VECTOR
*
*------------------------------------------------------------------------
* NOW DO THE TEST BY READING THE LOCATION IN QUESTION.
*------------------------------------------------------------------------
        MOVE.L  SP,A1           ;SAVE STACK POINTER
        MOVE.L  8(SP),A0        ;A0: ADDRESS TO ACCESS
        MOVE.L  (A0),D0         ;READ THE LONG WORD
        BRA.S   READ_OK         ;IT'S ACCESSIBLE IF WE GOT HERE!
READ_BERR:
        CLR.L   D0              ;SET RESULT TO "INACCESSIBLE"
READ_OK:
        MOVEA.L A1,SP           ;RESTORE ORIGINAL STACK POINTER
*
*------------------------------------------------------------------------
* RESTORE THE ORIGINAL BUS ERROR VECTOR
*------------------------------------------------------------------------
        JSR     GET_VBR         ;A0->VECTOR PAGE
        MOVE.L  (SP)+,8(A0)     ;RESTORE BUS ERROR VECTOR
*
*------------------------------------------------------------------------
* RESTORE ORIGINAL INTERRUPT LEVEL
*------------------------------------------------------------------------
        MOVE.L  D0,-(SP)        ;SAVE VALUE TO RETURN
        MOVE.L  D1,-(SP)        ;OLD MASK LEVEL
        JSR     _splx           ;CHANGE THE LEVEL
        ADDQ.L  #4,SP           ;CLEAN UP STACK
        MOVE.L  (SP)+,D0        ;VALUE TO RETURN TO CALLER
*
        RTS                     ;RETURN


*************************************************************************
* MemMirrorTest: Test if one memory location is the mirror of the other.*
*                                                                       *
*       SYNTAX: ULONG MemMirrorTest(volatile void *Lower,               *
*                                   volatile void *Upper);              *
*       INPUTS: Lower = the lower address to test                       *
*               Upper = the upper address to test                       *
*      RETURNS: 1 = Addresses point to different physical RAM locations.*
*               0 = Upper address is just a mirror of the lower address.*
*              -1 = Lower address is not accessible.                    *
*              -2 = Upper address is not accessible.                    *
*      NOTE(S): This routine preserves the contents of memory being     *
*               tested. If either address generates a bus error, it is  *
*               detected and reported back to the calling routine.      *
*                                                                       *
*************************************************************************
        XDEF    _MemMirrorTest
_MemMirrorTest:
*
*------------------------------------------------------------------------
* SAVE THE REGISTERS ON THE STACK.
*------------------------------------------------------------------------
        MOVEM.L D1-D5/A0-A2,-(SP)
*
*------------------------------------------------------------------------
* DISABLE INTERRUPTS FOR THIS.
*------------------------------------------------------------------------
        MOVE.L  #7,-(SP)        ;NEW MASK LEVEL WILL BE 7
        JSR     _splx
        ADDQ.L  #4,SP           ;CLEAN UP STACK
        MOVE.L  D0,D1           ;D1: OLD MASK
*
*------------------------------------------------------------------------
* TEMPORARILY REPLACE THE BUS ERROR VECTOR.
*------------------------------------------------------------------------
        JSR     GET_VBR         ;A0->VECTOR PAGE
        MOVE.L  8(A0),-(SP)     ;SAVE EXISTING BUS ERROR VECTOR
        MOVE.L  #LOWER_BERR,8(A0) ;INSTALL NEW VECTOR
*
*------------------------------------------------------------------------
* SAVE THE VALUE AT THE LOWER ADDRESS LOCATION.
*------------------------------------------------------------------------
        MOVE.L  SP,A2           ;SAVE STACK POINTER
        MOVE.L  40(SP),A0       ;A0: ADDRESS TO ACCESS
        MOVE.L  (A0),D2         ;READ THE LONG WORD
        BRA.S   LOWER_OK        ;IT'S ACCESSIBLE IF WE GOT HERE!
LOWER_BERR:
        MOVEQ.L #-1,D0          ;SET RESULT TO "INACCESSIBLE"
        BRA.S   CLEAN_UP
LOWER_OK:
        MOVEA.L A2,SP           ;RESTORE ORIGINAL STACK POINTER
*
*------------------------------------------------------------------------
* SAVE THE VALUE AT THE UPPER ADDRESS LOCATION.
*------------------------------------------------------------------------
        MOVE.L  #UPPER_BERR,8(A0) ;INSTALL NEW VECTOR
        MOVE.L  SP,A2           ;SAVE STACK POINTER
        MOVE.L  44(SP),A1       ;A0: ADDRESS TO ACCESS
        MOVE.L  (A1),D3         ;READ THE LONG WORD
        BRA.S   UPPER_OK        ;IT'S ACCESSIBLE IF WE GOT HERE!
UPPER_BERR:
        MOVEQ.L #-2,D0          ;SET RESULT TO "INACCESSIBLE"
        MOVE.L  D2,(A0)         ;RESTORE LOWER ADDRESS VALUE
        BRA.S   CLEAN_UP
UPPER_OK:
        MOVEA.L A2,SP           ;RESTORE ORIGINAL STACK POINTER
*
*------------------------------------------------------------------------
* NOW TEST THE ADDRESSES FOR MIRRORING.
*------------------------------------------------------------------------
        CLR.L   D0              ;SET RESULT TO MIRRORED
        MOVE.L  D0,(A0)         ;CLEAR LOWER ADDRESS VALUE
        MOVE.L  D0,(A1)         ;CLEAR UPPER ADDRESS VALUE

        MOVE.L  (A1),D4
        CMP.L   D0,D4           ;SEE IF THE WRITE WORKED
        BNE.S   MIRRORED
 
        MOVE.L  #$A5A5A5A5,D4   ;TEST PATTERN
        MOVE.L  D4,(A0)         ;WRITE TEST PATTERN TO LOWER ADDRESS
        MOVE.L  (A1),D5         ;READ UPPER ADDRESS
        CMP.L   D4,D5           ;IF ADDRESS MATCH, UPPER MIRRORS LOWER
        BEQ.S   MIRRORED
        MOVEQ.L #1,D0           ;SET RESULT TO UNIQUE ADDRESSES
MIRRORED:
        MOVE.L  D3,(A1)         ;RESTORE ORIGINAL VALUES
        MOVE.L  D2,(A0)
*
*------------------------------------------------------------------------
* RESTORE THE ORIGINAL BUS ERROR VECTOR
*------------------------------------------------------------------------
CLEAN_UP:
        JSR     GET_VBR         ;A0->VECTOR PAGE
        MOVE.L  (SP)+,8(A0)     ;RESTORE BUS ERROR VECTOR
*
*------------------------------------------------------------------------
* RESTORE ORIGINAL INTERRUPT LEVEL
*------------------------------------------------------------------------
        MOVE.L  D0,-(SP)        ;SAVE VALUE TO RETURN
        MOVE.L  D1,-(SP)        ;OLD MASK LEVEL
        JSR     _splx           ;CHANGE THE LEVEL
        ADDQ.L  #4,SP           ;CLEAN UP STACK
*
        MOVE.L  (SP)+,D0        ;VALUE TO RETURN TO CALLER
*
*------------------------------------------------------------------------
* RESTORE THE REGISTERS FROM THE STACK.
*------------------------------------------------------------------------
        MOVEM.L (SP)+,D1-D5/A0-A2
*
        RTS                     ;RETURN


*************************************************************************
*         splx: CHANGE THE PROCESSOR'S INTERRUPT MASK                   *
*                                                                       *
*       SYNTAX: ULONG splx(ULONG newmask);                              *
*       INPUTS: newmask = NEW PRIORITY LEVEL (0 - 7)                    *
*      RETURNS: PREVIOUS PRIORITY LEVEL                                 *
*                                                                       *
*         NOTE: SETTING THE INTERRUPT MASK TO ANYTHING OTHER THAN 7 OR  *
*               THE TASK'S INTERRUPT LEVEL IS STRONGLY DISCOURAGED,     *
*               AS IT CAN CAUSE THE pSOS+ SCHEDULER TO FUNCTION         *
*               IMPROPERLY. The tasks interrupt level is set by the     *
*               t_start and t_mode pSOS+ calls. These call may set      *
*               a tasks interrupt level to a value other then 0 so      *
*               changing the interrupt level to a level below the       *
*               tasks interrupt level can cause the task to be          *
*               interrupted when it should not be interrupted.          *
*                                                                       *
*************************************************************************
        XDEF     _splx
_splx:
        MOVE.W   SR,D1               ;GET CURRENT SR
        ROR.L    #8,D1               ;PUT MASK IN LEAST-SIGNFCNT NBL
        MOVE.L   D1,D0               ;SAVE IT IN D0 TO RETURN
        ANDI.L   #7,D0               ;JUST RETURN MASK VALUE

        ANDI.L   #-8,D1              ;CLEAR OUT CURRENT VALUE
        OR.L     4(SP),D1            ;NEW MASK IN
        ROL.L    #8,D1               ;AND RESTORE TO GOOD LOOKING
        MOVE.W   D1,SR               ;NOW ACTUALLY CHANGE INTRPT LEV
        RTS

***********************************************************************
* BspPmontCallout: Callout called by the PmontSetup to pass addresses *
*                  of functions to be called for interrupts on entry  *
*                  and exit.                                          *
*                                                                     *
* INPUTS:  void (*pMIEnter)(): Func Ptr to pMONT I_ENTER callout      *
*          void (*pMIExit)():  Func Ptr to pMONT I_RETURN callout     *
*                                                                     *
***********************************************************************

        XREF  _pMontIEnter,_pMontIReturn
        XDEF  _BspPmontCallout

_BspPmontCallout:
        CLR.L    _pMontIEnter        ;pMONT IENTER is not required for 68K.
        MOVE.L   8(A7),_pMontIReturn ;pMONT IRETURN Entry Point.
        RTS

        END

