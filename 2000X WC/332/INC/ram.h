/* $Header:   L:/pvcs/1000/psos332/archives/inc/RAM.H_v   2.1   01 Aug 1996 14:50:50   BKYMER  $ */

#ifndef RAM_h
#define RAM_h

/*
// Include Files
*/
#include "portable.h"

/*
//*********************************************************************
*/

/* Test the RAM */
/* Supply the starting address */
/*        the length of the RAM */
BYTE testTheRAM(BYTE* startingAddress, UINT16 length);

/*
//*********************************************************************
*/

#endif

