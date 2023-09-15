* $Header:   L:/pvcs/1000/psos332/archives/app/menuhorn.c_v   2.35   07 Dec 1998 11:56:30   bbarrows  $ */
* @(#) pSOSystem/68K V2.2.2: configs/68k/cxxini.s (&U&) 2.2 97/04/30 12:23:26 *
*************************************************************************
*                                                                       *
*   MODULE:  cxxini.s                                                   *
*   DATE:    97/04/30                                                   *
*   PURPOSE: Initializes .init, .fini sections needed by C++            *
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
* --------------------------------- REVISIONS -------------------------

* Rev # Date     Author  Description
* ===== ======== ======  =============================================
* 1.0   03/26/99 OFI     Original Version

*

        section .init,2,C
        XDEF    ___init
        ALIGN   4
___init:

        section .fini,2,C
; Return from ___init
        rts
        XDEF    ___fini
___fini:

        section .eini,2,C
; Return from ___fini
        rts

	.end
