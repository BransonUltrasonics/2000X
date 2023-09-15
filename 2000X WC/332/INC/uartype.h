/* $Header:   L:/pvcs/1000/psos332/archives/inc/UARTYPE.H_v   2.1   01 Aug 1996 14:52:12   BKYMER  $ */
#ifndef UART_PORT_TYPE_H
#define UART_PORT_TYPE_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: uart_port_type.h


   Filename:  uartype.h
  

            Written by:  
                  Date: 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========

 ------------------------------- DESCRIPTION -----------------------------------

  UART port designations

 ------------------------------ INCLUDE FILES ----------------------------------
*/


/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/*
 * UART Port designators
 * NOTE: These values are used as indices
 *       DO NOT CHANGE THESE VALUES!!!
 */
typedef enum
   {
   UART_A          = 0,
   UART_B          = 1,
   UART_UNASSIGNED = 0xFF,
   } UART_PORT_TYPE;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* UART_PORT_TYPE_H */
