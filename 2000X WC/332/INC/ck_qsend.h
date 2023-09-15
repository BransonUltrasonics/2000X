/* $Header:   K:/APPS/PVCS Pro/332new/INC/CK_QSEND.H_V   2.4   Dec 05 2003 13:37:36   BKymer  $ */
#ifndef CK_Q_SEND_H
#define CK_Q_SEND_H
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

   Module name: Ck_Q_Send

   Filename: ck_qsend.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0             02/18/96      Mark L      Initial Version
     2.3            12/16/99      LAM         removed unused error handling code
     2.3.1.0        03/20/03      SCM         Added item for QVGA_INTERRUPT in enum
                                              ERROR_CALLER_TYPE. 
     2.3.1.2        06/10/03      bWadia      Added item for TOUCH_SCRN_MODULE in enum
                                              ERROR_CALLER_TYPE. 
     2.4            12-05-03      BEKymer     Move 2.3.1.2 to tip as 2.4 for 
                                               Ver9.00b build
                                               
                                                                                        
 
 ------------------------------- DESCRIPTION -----------------------------------

 This header contains all the information needed by ck_q_send.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include  "portable.h"                 /* general hardware defines...           */
#include  "ticks.h"                    /* for MILLS_TO_TICKS usage in interface */

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/
/* a symbol indicating the identity    */
/* of the manage error calling routine */

typedef enum
   {
   ACCESS_CONTROL_OUTPUT_PORTS = 0u, 
   ALARM_DATABASE_MANAGER,
   ALARM_MONITOR,
   ASYNC_ACTIVE_CONNECTION,
   ASCII_DIAGS_INTERFACE_MANAGER,
   ASCII_DIAGS_STATE_COORDINATOR,
   BATTRAM_DEFAULT_CHECK,
   COMM_PASSWORD,
   COMM_QUEUE_STRING,
   COMM_XMT_STRING,
   COMM_ACTIVE_SESSION,
   COMM_INBOUND_MSG_ROUTER,
   COMM_OUTBOUND_MSG_ROUTER,
   DIAGNOSTICS_MANAGER,
   DISPLAY_STARTUP_MESSAGE,
   DUAL_PORT_RAM_MGR,
   EEPROM_ACCESS,     
   EEPROM_MEMCPY,
   ERROR_LOG_HANDLER,
   EXCEPTION_HANDLER,
   FIPS_RX_HANDLER,
   FIPS_TX_HANDLER,
   FPSP_PORT_MANAGER,
   FPSP_SHELL,
   FRONT_PANEL_DISPLAY_MANAGER,
   FRONT_PANEL_KEY_PAD_MANAGER,
   FRONT_PANEL_KEY_PAD_TASK,
   FRONT_PANEL_STATE_COORDINATOR,
   INIT_PROCESS_FP_KEYPAD_INTERRUPT,
   MANAGE_TIMERS,
   MONITOR_INPUT_PORTS,
   NVM_MANAGER,
   PRINTER_MANAGER,
   PROCESS_FP_KEYPAD_INTERRUPT,
   QUEUE_PRINT,
   QVGA_INTERRUPT,
   READ_FRONT_PANEL_KEYPAD,
   REMOTE_SERIAL_COMMAND_HANDLER,
   ROOT,
   SERIAL_INTERRUPT,
   SPI_DRIVER,
   SRAM_ACCESS,
   STATE_MACHINE,
   STATION_HARDWARE_MANAGER,
   SWARE_LOG_HANDLER,                
   SYS_MANAGER,
   TRANSLATE_ASCII_TO_FP_KP,
   TOUCH_SCRN_MODULE,
   UART_RCV_BUF,
   VERIFY_PASSWORD,
   WELD_DATA_PRINT_MGR,
   WELD_MGR,
   WD_TICKLE,
   MAX_NUMBER_OF_ERROR_CALLERS,                                          
   ERROR_CALLER_SIZER = 32768
} ERROR_CALLER_TYPE;


void CkQSend(
   UINT32              psos_queue_id,
   void               *psos_msg_ptr,
   ERROR_CALLER_TYPE   caller_module_id,
   UINT32              caller_line_number,
   UINT32              psos_error_retry_time
   ); 

#endif /* CK_Q_SEND_H */
