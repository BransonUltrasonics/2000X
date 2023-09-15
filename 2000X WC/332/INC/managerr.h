/* $Header:   K:\APPS\PVCS Pro\332\INC\MANAGERR.H_V   2.6   Apr 19 1999 16:03:42   ofingere  $ */
#ifndef MANAGE_ERRORS_H
#define MANAGE_ERRORS_H
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

	Module name:   Manage_Errors

	Filename:      managerr.h


				Written by: Mark Lazarewicz
						Date: 2/3/96 
				  Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

	Revision #      Date          Author      Description
	==========      ========      ======      ===========
		 0           02/03/96      Mark L      Initial Version
		 1           02/27/96      Mark L      Add FPSP_SHELL
		 2           03/04/96      Mark L      Add COMM_OUTBOUND_MESSAGE_ROUTER 
		 3           03/06/96      Mark L      Add IPS E_ values
		 4           03/27/96      Mark L      Add TRANSLATE_ASCII_TO_FP_KP
		 5           04/01/96      Mark L      Add E_PARAMETER_MANAGER_BAD_STATUS
		 6           04/23/96      BEK         Add STATE_MACHINE error caller type
		 7           04/29/96      LAM         add BATTRAM_DEFAULT_CHECK to error
		 8           05/01/96      MAL         Add ALARM_DATABASE_MANAGER to error caller type
                          															Also    E_MISC_ALARM,     
		 9           05/04/96      MAL         Alarm Monitor to error caller type
		10           09/04/96      PMG         Added PRINTER_MANAGER to enum (error caller type)   
        11           03/30/97      LAM         welddata test
        12           04/04/97      LAM         deleted unused vars
		2.6			 04/19/99	   OFI		   Changed for DIAB
 ------------------------------- DESCRIPTION -----------------------------------

	This file contains definitions used in calls to manage_errors_main, through
	either of the macro definitions.

	NOTE FOR ADDING NEW ERROR CODES:
	-------------------------------
	---------------------------------------------------------------------------
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ERROR CODES 0-103 ARE RESERVED FOR PSOS ERRORS.                            
																										  
	ALL ERROR CODES between 103 and E_MISC_ALARM ARE SOFTWARE ERRORS THAT WE 
	WILL  BE ABLE TO ACCESS.  THEY WILL BE LOGGED AS SWARE ERRORS 
	IN THE ERROR LOG AND LOGGED IN DETAIL IN THE SWARE ERROR LOG.                        

	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	---------------------------------------------------------------------------
	
	
	
	==============> NOTE <================
	In order to use the utility to convert
	this file to converted_strings.h, the 
	length of each of manage_errors.h can
	not exceed 128 characters.
	======================================

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/

typedef enum         /* classification of errors in terms of */
	{                        /* harware or software components       */
	ERROR_KIND_BEGIN = 0u,   /* Don't use this one -- it's a placeholder */
	PSOS,
	SWARE,
	NVM,
	MISC_ERROR,
	OPTION_ERROR,
	WELDER_ERROR,
	UNKNOWN_ERROR_KIND,      /* Don't use this one - used only by Diagnostics Manager */ 
	MAX_NUMBER_OF_ERROR_KINDS,
	ERROR_KIND_SIZER = 255 
	} ERROR_KIND_TYPE;        


 
	typedef enum         /* a numeric code for representing a specific error in the system */
	{
	E_NO_ERROR= 0u,   /* Oth slot means no error */

	/* Error Codes For PSOS Error Kinds */
	/*-------------------------------------------------------------------*/ 
	/*  Common errors (across several service groups)                    */
	/*-------------------------------------------------------------------*/ 
	E_TIMEOUT = 1,        /* TASK TIMED OUT WAITING FOR RESOURCE */
	E_UNIMPL  = 2,        /* UNIMPLEMENTED SYSTEM SERVICE */
	E_SSFN    = 3,        /* ILLEGAL SYSTEM SERVICE FUNCTION NUMBER */
	E_NODENO  = 4,        /* ILLEGAL NODE NUMBER */
	E_OBJDEL  = 5,        /* OBJECT HAS BEEN DELETED */
	E_OBJID   = 6,        /* ILLEGAL/INVALID OBJECT ID */
	E_OBJTYPE = 7,        /* INCORRECT OBJECT TYPE */
	E_OBJTFULL= 8,        /* OBJECT TABLE FULL */
	E_OBJNF   = 9,        /* OBJECT NOT FOUND */

	/*-------------------------------------------------------------------*/ 
	/*  Task service group errors                                        */
	/*-------------------------------------------------------------------*/ 
	E_RSTFS   = 13,       /* INFORMATIVE ONLY - FILES MAY BE */
										/*  CORRUPTED ON RESTART */
	E_NOTCB   = 14,       /* CANNOT CREATE - OUT OF TCBs */
	E_NOSTK   = 15,       /* CANNOT CREATE - NO STACK SPACE */
	E_TINYSTK = 16,       /* CANNOT CREATE - STACK TOO SMALL */
	E_PRIOR   = 17,       /* CANNOT CREATE - PRIORITY OUT OF RANGE */
	E_ACTIVE  = 18,       /* CANNOT START - ALREADY ACTIVE */
	E_NACTIVE = 19,       /* CANNOT RESTART - NEVER STARTED */
	E_SUSP    = 20,       /* CANNOT SUSPEND - ALREADY SUSPENDED */
	E_NOTSUSP = 21,       /* CANNOT RESUME - NOT SUSPENDED */
	E_SETPRI  = 22,       /* CANNOT CHANGE PRIORITY - NEW PRIORITY */
			/* OUT OF RANGE */
	E_REGNUM  = 23,       /* ILLEGAL TASK REGISTER NUMBER */
	E_FOPEN   = 24,       /* CANNOT DELETE - FILES OPEN */ /* OLD NAME! */
	E_DELFS   = 24,       /* CANNOT DELETE - ERROR FROM PHILE */
	E_DELLC   = 25,       /* CANNOT DELETE - ERROR FROM PREPC */
	E_DELNS   = 26,       /* CANNOT DELETE - ERROR FROM PNA */

	/*-------------------------------------------------------------------*/ 
	/*  Region service group errors                                      */
	/*-------------------------------------------------------------------*/ 
	E_RNADDR  = 27,        /* CANNOT CREATE - START ADDR NOT ON LONG */
												  /*  WORD OR MMU PAGE */
	E_UNITSIZE = 28,       /* CANNOT CREATE - UNIT SIZE NOT POWER OF */
												/*2 OR LESS THAN 4 */
	E_TINYUNIT = 29,       /* CANNOT CREATE - LENGTH TOO LARGE FOR */
												  /*  GIVEN UNIT SIZE */
	E_TINYRN   = 30,       /* CANNOT CREATE - REGION LENGTH TOO */
												  /*  SMALL FOR REQ'D RNCB */
	E_SEGINUSE = 31,       /* CANNOT DELETE - ONE OR MORE SEG IN USE */
	E_ZERO     = 32,       /* CANNOT GETSEG - REQUEST SIZE IS ZERO */
	E_TOOBIG   = 33,       /* CANNOT GETSEG - REQUEST SIZE TOO BIG */
										/* FOR REGION */
	E_NOSEG    = 34,       /* CANNOT GETSEG - NOT ENOUGH MEMORY */
	E_NOTINRN  = 35,       /* CANNOT RETSEG - SEG DOESN'T BELONG TO */
										/* REGION */
	E_SEGADDR  = 36,       /* CANNOT RETSEG - INCORRECT SEG START ADDR */
	E_SEGFREE  = 37,       /* CANNOT RETSEG - SEGMENT ALREADY FREE */
	E_RNKILLD  = 38,       /* CANNOT GETSEG - REGION DELETED WHILE */
										/* WAITING */
	E_TATRNDEL = 39,       /* INFORMATIVE - TASKS WERE WAITING AT */
										/* DELETION */
 
	/*-------------------------------------------------------------------*/ 
	/*  Partition service group errors                                   */
	/*-------------------------------------------------------------------*/ 
	E_PTADDR   = 40,       /* CANNOT CREATE - START ADDR NOT ON LONG */
												  /*  PAGE WORD OR MMU */
	E_BUFSIZE  = 41,       /* CANNOT CREATE - BUF SIZE NOT POWER OF */
												  /*  2, OR LESS THAN 4 */
	E_TINYPT   = 42,       /* CANNOT CREATE - LENGTH TOO SMALL FOR */
										/* NECESSARY PTCB */
	E_BUFINUSE = 43,       /* CANNOT DELETE-ONE OR MORE BUFFS IN USE */
	E_NOBUF    = 44,       /* CANNOT GETBUF-NO FREE BUFFS AVAILABLE. */
	E_BUFADDR  = 45,       /* CANNOT RETBUF-INCORRECT BUFF START ADDR*/
	E_BUFFREE  = 47,       /* CANNOT RETBUF-BUFFER ALREADY FREE */
 
	/*-------------------------------------------------------------------*/ 
	/*  Queue/Message service group errors                               */
	/*-------------------------------------------------------------------*/ 
	E_NOQCB    = 51,       /* CANNOT CREATE - NO MORE QCB */
	E_NOMGB    = 52,       /* CANNOT CREATE OR SEND - NO MORE MESSAGE*/
										/* BUFFERS */
	E_QFULL    = 53,        /* CANNOT SEND - MESSAGE QUEUE FULL */
	E_QKILLD   = 54,       /* CANNOT RECEIVE - QUEUE DELETED WHILE */
										/* WAITING. */
	E_NOMSG    = 55,       /* CANNOT RECEIVE - NO PENDING MESSAGE */
										/* (NOWAIT ONLY) */
	E_TATQDEL  = 56,       /* INFORMATIVE - AT TIME OF DELETION */
										/* TASKS WERE WAITING */
	E_MATQDEL  = 57,       /* INFORMATIVE - AT TIME OF DELETION */
										/* MESSAGES WERE PENDING */
 
	/*-------------------------------------------------------------------*/ 
	/*  Event service group errors                                       */
	/*-------------------------------------------------------------------*/ 
	E_NOEVS    = 60,       /* NOT ALL WANTED EVENTS WERE PENDING */
										/* (NO WAIT ONLY) */

	/*-------------------------------------------------------------------*/ 
	/*  Asynch signal service group errors                               */
	/*-------------------------------------------------------------------*/ 
	E_NOTINASR = 62,       /* CANNOT RETURN - NOT IN ASR */
	E_NOASR    = 63,       /* CANNOT SEND - TASK HAS NO VALID ASR */
 
	/*-------------------------------------------------------------------*/ 
	/*  Semaphore service group errors                                   */
	/*-------------------------------------------------------------------*/ 
	E_NOSCB    = 65,       /* CANNOT CREATE - NO MORE SCB */ 
	E_NOSEM    = 66,       /* CANNOT ACQUIRE - SEMAPHORE NOT AVAIL */
										/* (NOWAIT) */
	E_SKILLD   = 67,       /* CANNOT ACQUIRE - SEMAPHORE DELETED */
										/* WHILE WAITING */
	E_TATSDEL  = 68,       /* INFORMATIVE - AT TIME OF DELETION */
										/* TASKS WERE WAITING */
 
	/*-------------------------------------------------------------------*/ 
	/*  Time service group errors                                        */
	/*-------------------------------------------------------------------*/ 
	E_NOTIME   = 71,       /* TIME OF DAY HAS NOT BEEN SET YET */
	E_ILLDATE  = 72,       /* DATE INPUT OUT OF RANGE */
	E_ILLTIME  = 73,       /* TIME OF DAY INPUT OUT OF RANGE */
	E_ILLTICKS = 74,       /* TICKS INPUT OUT OF RANGE */
	E_NOTIMERS = 75,       /* NO TIMERS LEFT */
	E_BADTMID  = 76,       /* INVALID TIMER ID SPECIFIED */
	E_TMNOTSET = 77,       /* CANNOT CANCEL - TIMER NOT SET */
	E_TOOLATE  = 78,       /* TIMING REQ TOO LATE- TIME ALREADY PAST */
 
	/*-------------------------------------------------------------------*/ 
	/*  Multiprocessor support service group errors                      */
	/*-------------------------------------------------------------------*/ 
	E_ILLRPC   = 83,       /* THIS SYSTEM SERVICE CALL NOT SUPPORTED */
										/* AS RPC */
	E_NOAGNT   = 84,       /* CANNOT WAIT ON REMOTE OBJ - NO FREE */
										/* AGENTS AT NODE */
	E_AGTBLKD  = 85,       /* AGENT BLOCKED. THIS IS NOT AN ERROR. */

	/*-------------------------------------------------------------------*/ 
	/*  MMU support group errors                                         */
	/*-------------------------------------------------------------------*/
	E_PALIGN   = 90,       /* PADDR NOT PAGE-ALIGNED */
	E_LALIGN   = 91,       /* LADDR NOT ON SECTION BOUNDARY */
	E_UNMAPPED = 92,       /* LOGICAL ADDRESS IS NOT MAPPED */
	E_SUPER    = 93,       /* CANNOT AFFECT SUPERVISOR MAP */
	E_TOOMUCH  = 94,       /* COPY TOO LONG - PAST SECTION END */
	E_MAPPED   = 95,       /* SECTION ALREADY MAPPED */
	E_NOSECT   = 96,       /* NO SECTION AVAILABLE */
	E_ZEROMAP  = 97,       /* ZERO MEMORY TO BE MAPPED */
	E_TOOLONG  = 98,       /* LENGTH GREATER THAN SECTION */
	E_SWITCH   = 99,       /* ILLEGAL MODE SWITCH */

	/*-------------------------------------------------------------------*/ 
	/*  IO service group errors                                          */
	/*-------------------------------------------------------------------*/
	E_IODN     = 101,   /* ILLEGAL DEVICE (MAJOR) NUMBER */
	E_NODR     = 102,   /* NO DRIVER PROVIDED */
	E_IOOP     = 103,   /* ILLEGAL I/O OPERATION NUMBER */

	/* Error Codes For SWARE Error Kinds */

	E_BUFFER_LENGTH_EXCEEDED,   
	E_BL_BAD_BLOCK_CRC, 
	E_BL_OUT_OF_MEMORY,
	E_BL_ILLEGAL_ADDRESS, 
	E_EE_DATA_MODIFIED, 
	E_DEFAULT_PARAMETERS_WRITTEN,
	E_NOT_ENOUGH_MEMORY,
	E_UNABLE_ALLOCATE_MEMORY,
	E_NUM_OF_BUF_EXCEED_8,
	E_RESET,
	E_ROUTINE_INIT_FAILED,
	E_UNEXPECTED_IPS_COMMAND, 
	E_UNEXPECTED_ELSE,
	E_UNEXPECTED_OPCODE,
	E_UNEXPECTED_MSG_RESP,
	E_UNEXPECTED_TERMINATION,
	E_Q_RECEIVE_TIMED_OUT,
	E_EEPROM_WRITE_FAULT,
	E_PARAMETER_MANAGER_BAD_STATUS,
	E_PARAMETER_WRITE_OUT_OF_RANGE,
	E_PARAMETER_DATABASE_OUT_OF_RANGE,
	E_PARAMETER_UNKNOWN,
	E_PARAMETER_UNKNOWN_ACCESS_REQUEST,
	E_PARAMETER_READ_ONLY,
	E_PARAMETER_ATTRIBUTE_FAULT,
	E_BATTRAM_WRITE_FAULT,
	E_BATTRAM_READ_FAULT,
	E_VARIABLE_OUT_OF_RANGE,
	E_DETERMINE_OBJECT_ID_NOT_FOUND,
	E_SIZE_DOES_NOT_MATCH_LOCAL_VARIABLE,
	E_INVALID_ERROR_KIND,       /* Don't use this one - used ONLY by the Diagnostic Manager */
	E_INVALID_ERROR_CODE,       /* Don't use this one - used ONLY by the Diagnostic Manager */
	E_INVALID_ERROR_REQUEST,       /* Don't use this one - used ONLY by the Diagnostic Manager */
	E_INVALID_DIAGS_REQUEST,         /* Don't use this one - used ONLY by the Diagnostic Manager */
	E_PASSED_PARAMETER_OUT_OF_RANGE,
	E_SWITCH_DEFAULT,
	E_SEND_ASCII_SCREEN_FAILURE,
	E_ILLEGAL_IPS_COMMAND,
	E_ILLEGAL_PARAMETER_WRITE,
	E_ILLEGAL_FPSP_MODE,
	E_INVALID_IPS_PORT,
	E_INACTIVE_IPS_PROTOCOL,
	/* Error code for Remote Software Download */
	E_BAD_CRC,

	E_SWARE = 0xF800, /*63488*/
							/* Don't use this one. It is used to log SWARE (SWARE, PSOS,NVM,SPI, ) 
							 * errors in the alarm database table.  It is also used to index into the database 
							 * table.
							 */
	E_MISC_ALARM,     /* Don't use this one.  It is used to index into the database table.
							 * This alarm is set when any error (other than the 
							 * 25 customer alarms) occurs in the welder. This is the first entry
							 * in the alarm database. 
							 */ 
	E_SYSTEM_TIMER_EXPIRED_ALARM,
	E_FAN_FAIL_ALARM, 


	/* !!!!!!!! the order of initialization errors must not change !!!!!!!!!!!!  */
	E_UNABLE_TO_START_TASKS,
	 /* !!!!!!!! the order of initialization errors must not change !!!!!!!!!!!!  */
	/* STATUS */
	S_STATION_RESET           = 0xFA80,     /*64128*/

	 /* Error Log Test Message */
	S_THIS_IS_A_TEST,

	/*-------------------------------------------------------------------------*/
	/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	/*                                                                         */
	/* ALL ERRORS THAT ARE TO BE SEEN BY THE CUSTOMER MUST BE ADDED AFTER      */
	/* E_SWARE ERROR CODE.  THESE ARE LOGGED IN THE ERROR LOG.                 */
	/*                                                                         */ 
	/* ALL ERROR CODES between 103 and E_SWARE ARE SOFTWARE ERRORS THAT THE    */
	/* ERRORS CUSTOMER WILL NOT BE ABLE TO ACCESS.  THEY WILL BE LOGGED        */ 
	/* AS SWARE IN THE ERROR LOG AND LOGGED IN DETAIL IN THE SWARE ERROR LOG.  */            
	/*                                                                         */
	/* ERROR CODES 0-103 ARE RESERVED FOR PSOS ERRORS. THESE WILL ALSO APPEAR  */
	/* IN THE SWARE LOG.                                                       */
	/*                                                                         */
	/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	/*-------------------------------------------------------------------------*/
	
	MAX_NUMBER_OF_ERROR_CODES,
	ERROR_CODE_SIZER = 65535
	} ERROR_CODE_TYPE;

	#define  MAX_NUMBER_ALARM_DATABASE_ERROR_CODES      MAX_NUMBER_OF_ERROR_CODES - E_SWARE
	#define  END_OF_SWARE_ERRORS                        E_SWARE
	#define  E_SWARE_ERROR_CODE                         0   /* used to index into the alarm db table */   

/* -------------------------------------------------------------------------- */

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
	MANAGE_ERRORS_MAIN,
	MANAGE_TIMERS,
	MONITOR_INPUT_PORTS,
	NVM_MANAGER,
	PARAMETER_MANAGER,
	PRINTER_MANAGER,
	PROCESS_FP_KEYPAD_INTERRUPT,
	QUEUE_PRINT,
	READ_FRONT_PANEL_KEYPAD,
	REMOTE_SW_DOWNLOAD_MGR,   
	REMOTE_SERIAL_COMMAND_HANDLER,
	RSM_PROCESS_S_REC,
	RSDM_MANAGER,
	ROOT,
	SERIAL_INTERRUPT,
	SEND_COMM_STRING_LONG,
	SEND_SCREEN_DATA,
	SHELL_PROTOCOL_SELECTION,
	SPI_DRIVER,
	SRAM_ACCESS,
	STATE_MACHINE,
	STATION_HARDWARE_MANAGER,
	SWARE_LOG_HANDLER,                
	SYS_MANAGER,
	TRANSLATE_ASCII_TO_FP_KP,
	UNIT_TEST,
	UART_RCV_BUF,
	VERIFY_PASSWORD,
	WELD_DATA_PRINT_MGR,
	WELD_MGR,
        WISP_TX_HANDLER,
        WISP_RX_HANDLER,
	WD_TICKLE,
	MAX_NUMBER_OF_ERROR_CALLERS,                                          
	ERROR_CALLER_SIZER = 32768
	} ERROR_CALLER_TYPE;

/* -------------------------------------------------------------------------- */

typedef enum
	{
	UNRECOVERABLE = 0u,
	RESET_WELDER,
	LOG_ERROR,
	CLEAR_ERROR,
	MAX_NUMBER_OF_ERROR_REQUESTS,
	ERROR_REQUEST_SIZER = 255
	} ERROR_REQUEST_TYPE;


typedef UINT16 C_LINE_NUMBER_TYPE;

typedef UINT32 PSOS_TASK_ID_TYPE;

/*
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void ManageErrorsMain(
	ERROR_KIND_TYPE    error_kind,
	ERROR_CODE_TYPE    error_code,
	ERROR_CALLER_TYPE  caller_name,
	ERROR_REQUEST_TYPE error_request,
	C_LINE_NUMBER_TYPE line_number
	);                 

/*
 ------------------------------- MACRO DEFINTIONS ------------------------------
*/

/* MACRO definitions for easy use of manage_errors */
/* It is assumed that the macros calls are ended with a ';' */

/* the 'else' is to make sure this 'if' doesn't steal another 'ifs' 'else' */
/* The CHECK_ERROR macro should only be used to report PSOS errors for 1 */
/*  2.  code should use the CHECK_PSOS_ERROR macro to report PSOS */ 
/*errors. */

#define CHECK_ERROR(ekind, ecode, cname)   if ( ecode != 0 )   ManageErrorsMain (ekind, ecode, cname, RESET_WELDER, __LINE__); else{}

#define MANAGE_ERRORS(ekind, ecode, cname, type)  ManageErrorsMain (ekind, ecode, cname, type, __LINE__)

#define CHECK_PSOS_ERROR(error_code, error_caller) if (error_code != 0) ManageErrorsMain (PSOS, error_code,error_caller, RESET_WELDER, __LINE__); else{}

#define COMM_CHECK_PSOS_ERROR(error_code, error_caller) if (error_code != 0) ManageErrorsMain (PSOS, error_code,error_caller, RESET_WELDER, __LINE__); else{}

#endif /* MANAGE_ERRORS_H */
