* @(#) pSOSystem/68K V2.2.2: bsps/devices/68k/cpu000.s (diab) 2.3 97/04/30 19:26:45 *
*************************************************************************
*                                                                       *
*   MODULE:  cpu000.s                                                    *
*   DATE:    97/04/30                                                   *
*   PURPOSE: provides the GET_VBR function for the 68000 and 68008      *
*            processors.                                                *
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
*************************************************************************
        .text

*************************************************************************
*      GET_VBR: Moves the the vector base (0) into A0.                  *
*                                                                       *
*       SYNTAX: NONE not C callable.                                    *
*                                                                       *
*************************************************************************
        XDEF    GET_VBR
GET_VBR:
        MOVE.L  #0,A0
        RTS

        END
