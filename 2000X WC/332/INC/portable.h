/* $Header:   K:/APPS/PVCS Pro/332new/INC/PORTABLE.H_V   2.12   May 30 2000 08:48:26   shishir  $ */
#ifndef PORTABLE_H
#define PORTABLE_H
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
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author           Description
   ==========      ========      ======           ===========
      0            12/12/95      Mark Lazarewicz  Initial release 
      1            02/23/96      Mark L           Add bit manipulations
      2            04/22/96      LAM              Add Off/ON
      3            07/01/96      LAM              removed chkbit,clrbit
      4            07/03/96      LAM              removed setbit
      4            02/22/97      PaulG            Added LARGE_MEMORY.
      4            12/02/97      PaulG            replaced DFLOAT with FLOAT.
      4            12/03/97      PaulG            Removed DFLOAT.
      2.10         05/01/98      BJB              Defines SINT8 as "char", not
                                                   "signed char".  Same result,
                                                   and "signed" bothers C++
                                                   compiler.
	  2.11         04/20/99      OFI              Changed for DIAB
	  2.12         05/30/00      SCM              Checked in for testing by Laura,John.
 ------------------------------- DESCRIPTION -----------------------------------

   This file defines language extensions for use with the Microtec "C" compiler.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/
#include  <types.h>
#define  BITSPERBYTE    (8)

#define  VOIDPTR        void *                /* "void *" is allowed       */

#define  NULL           0                     /* null value                */
#define  NULL_BYTE      ((UINT8)NULL)         /* null value                */
#define  NULL_PTR       0L                    /* null value                */
#define  NULL_FUNC_PTR  0L                    /* null value                */
#define  FOREVER        1              

#define dISABLE_INTERRUPTS      asm("       ORI     #$0700,SR   ");

#define eNABLE_INTERRUPTS       asm("       ANDI    #$F8FF,SR   ");

#define LARGE_MEMORY 1

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/* These definitions are specific to the Microtec compiler for the 68000.  */

typedef  unsigned char       UINT8;           /* 8-bit  unsigned quantity  */
typedef  UINT8               BYTE;            /* 8-bit  unsigned quantity  */
typedef  unsigned short int  UINT16;          /* 16-bit unsigned quantity  */
typedef  unsigned long int   UINT32;          /* 32-bit unsigned quantity  */
typedef  char                SINT8;           /* 8-bit  signed quantity    */
typedef  signed short int    SINT16;          /* 16-bit signed quantity    */
typedef  signed long int     SINT32;          /* 32-bit signed quantity    */
typedef  signed long int     SIZE_T;          /* signed size difference    */
typedef  unsigned long int   PTRDIFF_T;       /* unsigned size difference  */
typedef  signed int          FPOS_T;          /* signed size difference    */
typedef  float               FLOAT;           /* small float               */
typedef  float               DFLOAT;          /* medium float              */

/* Defined to standardize string definitions for the menu structures  */
/* incorporating foreign languages                                    */
typedef  char                STR;

typedef  enum boolean  
   {
   FALSE = 0,
   TRUE	 = 1
   } BOOLEAN;                                /* system boolean definition */

typedef  enum                                 
   {
   INACTIVE = 0,
   ACTIVE   = 1
   } ACT_INACT_TYPE;                          /* "active | inactive" type  */

#define FAILURE ((BYTE)1)
#define SUCCESS ((BYTE)0)


#define ON  ((BYTE)1)
#define OFF ((BYTE)0)

/*----------------------------*/
/* Bit manipulation patterns  */
/*----------------------------*/

/* BYTEWISE, WORDWISE or LONGWISE 	*/

#define BIT0    0x1
#define BIT1    0x2
#define BIT2    0x4
#define BIT3    0x8
#define BIT4    0x10
#define BIT5    0x20
#define BIT6    0x40
#define BIT7    0x80
				/* WORDWISE or LONGWISE			*/
#define BIT8    0x100
#define BIT9    0x200
#define BIT10   0x400
#define BIT11   0x800
#define BIT12   0x1000
#define BIT13   0x2000
#define BIT14   0x4000
#define BIT15   0x8000
				/* LONGWISE				*/
#define BIT16   0x10000	
#define BIT17   0x20000
#define BIT18   0x40000
#define BIT19   0x80000
#define BIT20   0x100000
#define BIT21   0x200000
#define BIT22   0x400000
#define BIT23   0x800000
#define BIT24   0x1000000
#define BIT25   0x2000000
#define BIT26   0x4000000
#define BIT27   0x8000000
#define BIT28   0x10000000
#define BIT29   0x20000000
#define BIT30   0x40000000
#define BIT31   0x80000000


/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* PORTABLE_H  */
