/* $Header:   K:\APPS\PVCS Pro\332\INC\RXCHARCV.H_V   2.9   Apr 20 1999 11:02:36   ofingere  $ */
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

   Module name: comm_ascii_char_rcvd

   Filename:    rxcharcv.h 


 -------------------------------- REVISIONS ------------------------------------

 Revision #      Date          Author   Description
 ==========      ========      ======   ===========
    0            03/01/96      Mark L   Initial Version
    1            03/30/97      LAM      welddata test
    2            04/02/97      LAM      deleted unused prototypes
    3            04/28/97      LAM      cleanup
    2.7          12/31/97      BJB      Changed prototype of CommAsciiCharRcvd()
                                        , now is passed a byte.
    2.8          10/22/98      LAM      moved typedef from rxcharcv.c

    2.9          04/20/99      OFI      Changed for DIAB     
 ------------------------------- DESCRIPTION -----------------------------------


 ------------------------------ INCLUDE FILES ----------------------------------
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/
typedef enum
   {
   SEND_BUFFER = 0u,
   WAIT_FOR_START,
   WAIT_FOR_STX,
   GET_MESSAGE_SIZE,
   GET_MESSAGE_TYPE,
   START_TO_ACCUMULATE,
   WAIT_FOR_CHECKSUM,
   WAIT_FOR_DLE,
   WAIT_FOR_END_MESSAGE,
   CONTINUE_TO_ACCUMULATE,
   RCV_BUFFER_SIZER = 255,
   } RCV_BUFFER_STATUS_TYPE;


/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

void InitReceiveBuffer(void);
void CommAsciiCharRcvd( UINT8 ByteReceived );
