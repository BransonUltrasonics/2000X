/* $Header:   K:\APPS\PVCS Pro\332new\App\OUTPORTS.C_V   2.5   Aug 13 1999 09:39:12   jzimny  $ */
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

 -------------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author       Description
   ==========   ========   ======       ===========
      0         12/22/95   M Lazarewicz Initial driver
      1          3/28/96   LAM          Added initialization defaults
      2         05-15-96   BEKymer      Comment out unused variables
    2.3         08.15.97   JBerman      1) Eliminated the function:
                                           "AccessControlOutputPorts"
                                        2) Defined new Registers:PortRegisterA;
                                                                 PortRegisterB;
                                                                 PortRegisterC;
                                        3) Modified the function:
                                           "InitializeOutputPorts"
    2.4         09/11/97   LAM          unit test version
    2.5         08-13-99   JZ           deleted OutPortOn and chngd to void type            
 										function InitializeOutputPorts

   ------------------------------- DESCRIPTION -----------------------------------

    This routine will write given value to the requested output port and also to
    the shadow register.

 ------------------------------- PSEUDO CODE -----------------------------------

   

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include <psos.h>
#include "outports.h"                      /* defs and function prototype for write/read */

/*  
 ------------------------------- LOCAL DEFINES ---------------------------------
*/

#define SYS_STARTUP_PASS 0
#define SYS_STARTUP_FAIL 1
#define NUM_CTRL_PORTS 3


/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/


UINT8 PortRegisterA;
UINT8 PortRegisterB;
UINT8 PortRegisterC;



/*
 ---------------------------- PRIVATE GLOBAL DATA ------------------------------
*/



/*
------------------------------------ CODE ---------------------------------------
*/

 
/*
 ------------------------------- DESCRIPTION -----------------------------------

     This routine will initialize the write-only memory registers and set up 
     the semaphore for use with the read and write routines.  Also the remote
     processors will be brought out of reset.

*/

void InitializeOutputPorts(void)
   {

   *Input8255CntrolPtr1 = ACTUATOR_8255_CONTROL_WORD;
   *Input8255CntrolPtr2 = ALARM_8255_CONTROL_WORD;

   /* Setup port_info variable containing port addresses and their current settings */
   
   
   
   PortRegisterA = CTRL_PORT_0_DEFAULT;
   PortRegisterB = CTRL_PORT_1_DEFAULT;
   PortRegisterC = CTRL_PORT_2_DEFAULT;

 
   /* put assigned initialized value into hardware registers */

   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;    
   *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
   *(UINT8 *)CONTROL_OUTPUT_PORT_2 = PortRegisterC;
                                                                                       
  
   }

/* FOR UNIT TEST ONLY */
#ifdef INCLUDE_UNIT_TEST
#include "outports.ut"
#endif
/* FOR UNIT TEST ONLY */
