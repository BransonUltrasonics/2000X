/* $Header:   D:/SWLab/VMdb/2000Series/INC/ROOT.H_V   2.4   Aug 24 2004 13:24:16   LMarkure  $ */
#ifndef ROOT_H
#define ROOT_H
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

   Module name: 

   Filename:  root.h


            Written by: Mark Lazarewicz 
                  Date: 1/6/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      2.3           7/14/04       LAM         added actuator A/D defines
      2.4           8/24/04       LAM         added more actuator A/D defines
 ------------------------------- DESCRIPTION -----------------------------------


 ------------------------------ INCLUDE FILES ----------------------------------
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/

#define FAST_CLK               5   /* Actuator A/D clk 2.41Mhz */
#define SLOW_CLK               8
#define CLOCK_PHASE            1   /* Need to invert phase because of timing error */
/* used to slow down actuator a/d clock */
#define INVERTCLK 0
#define SLOWSPEED 7 /* 1.722Mhz */
#define SLOWERSPEED 8 /* 1.51Mhz */
/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/
                                 
typedef enum
   {
   SYS_STARTUP_PASS,
   SYS_STARTUP_FAIL
   } SYS_STARTUP_STATUS_TYPE;


/*      
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* ROOT_H */
