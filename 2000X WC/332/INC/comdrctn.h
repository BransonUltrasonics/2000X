/* $Header:   L:/pvcs/1000/psos332/archives/inc/comdrctn.h_v   2.2   13 Nov 1996 11:35:18   lmarkure  $ */
#ifndef COMM_DIRECTION_TYPE_H
#define COMM_DIRECTION_TYPE_H
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

   Module name:  n/a

   Filename:     comm_direction_type.h


            Written by: Mark Lazarewicz 
                  Date: 02/08/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0            02/08/96      Mark Lazarewicz Initial release 

 ------------------------------- DESCRIPTION -----------------------------------

 Defines the direction of a message; either to the port or from the port.


 ------------------------------ INCLUDE FILES ----------------------------------
*/



/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef packed enum
   {
   TO_PORT              = 0,
   FROM_PORT            = 1,
   COMM_DIRECTION_SIZER = 255u
   } COMM_DIRECTION_TYPE;


/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* COMM_DIRECTION_TYPE_H */


