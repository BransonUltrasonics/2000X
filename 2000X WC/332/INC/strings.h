/* $Header:   L:/pvcs/1000/psos332/archives/inc/strings.h_v   2.2   04 Apr 1997 11:20:46   lmarkure  $ */
#ifndef CONVERTED_STRINGS_H
#define CONVERTED_STRINGS_H
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
                                                  

  Filename:  strings.h


           Written by: Mark Lazarewicz 
                 Date: 1/21/96 
             Language:  68000 Microtec "C" Compiler

--------------------------------- REVISIONS -----------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            01/21/96      Mark L      Initial Version
      1            04/04/97      LAM         deleted unused vars               
--------------------------------- DESCRIPTION -----------------------------------

--------------------------------- INCLUDE FILES ---------------------------------
*/
#include "portable.h"

const ERR_KIND_NAME_TYPE  error_kind_name[] =
   {
   {PSOS,                            "PSOS"},
   {SWARE,                           "SWARE"},
   {NVM,                             "NVM"},
   {OPTION_ERROR,                    "OPTION_ERROR"},
   {WELDER_ERROR,                    "WELDER_ERROR"},
   {MISC_ERROR,                      "MISC_ERROR"},
   {UNKNOWN_ERROR_KIND,              "UNKNOWN_ERROR_KIND"},
   };

const ERR_CODE_NAME_TYPE  error_code_name[] =
   {
   {E_NO_ERROR,                      "E_NO_ERROR"},
   {E_TIMEOUT,                       "E_TIMEOUT"},
   {E_UNIMPL,                        "E_UNIMPL"},
   {E_SSFN,                          "E_SSFN"},
   {E_NODENO,                        "E_NODENO"},
   {E_OBJDEL,                        "E_OBJDEL"},
   {E_OBJID,                         "E_OBJID"},
   {E_OBJTYPE,                       "E_OBJTYPE"},
   {E_OBJTFULL,                      "E_OBJTFULL"},
   {E_OBJNF,                         "E_OBJNF"},
   {E_RSTFS,                         "E_RSTFS"},
   {E_NOTCB,                         "E_NOTCB"},
   {E_NOSTK,                         "E_NOSTK"},
   {E_TINYSTK,                       "E_TINYSTK"},
   {E_PRIOR,                         "E_PRIOR"},
   {E_ACTIVE,                        "E_ACTIVE"},
   {E_NACTIVE,                       "E_NACTIVE"},
   {E_SUSP,                          "E_SUSP"},
   {E_NOTSUSP,                       "E_NOTSUSP"},
   {E_SETPRI,                        "E_SETPRI"},
   {E_REGNUM,                        "E_REGNUM"},
   {E_FOPEN,                         "E_FOPEN"},
   {E_DELFS,                         "E_DELFS"},
   {E_DELLC,                         "E_DELLC"},
   {E_DELNS,                         "E_DELNS"},
   {E_RNADDR,                        "E_RNADDR"},
   {E_UNITSIZE,                      "E_UNITSIZE"},
   {E_TINYUNIT,                      "E_TINYUNIT"},
   {E_TINYRN,                        "E_TINYRN"},
   {E_SEGINUSE,                      "E_SEGINUSE"},
   {E_ZERO,                          "E_ZERO"},
   {E_TOOBIG,                        "E_TOOBIG"},
   {E_NOSEG,                         "E_NOSEG"},
   {E_NOTINRN,                       "E_NOTINRN"},
   {E_SEGADDR,                       "E_SEGADDR"},
   {E_SEGFREE,                       "E_SEGFREE"},
   {E_RNKILLD,                       "E_RNKILLD"},
   {E_TATRNDEL,                      "E_TATRNDEL"},
   {E_PTADDR,                        "E_PTADDR"},
   {E_BUFSIZE,                       "E_BUFSIZE"},
   {E_TINYPT,                        "E_TINYPT"},
   {E_BUFINUSE,                      "E_BUFINUSE"},
   {E_NOBUF,                         "E_NOBUF"},
   {E_BUFADDR,                       "E_BUFADDR"},
   {E_BUFFREE,                       "E_BUFFREE"},
   {E_NOQCB,                         "E_NOQCB"},
   {E_NOMGB,                         "E_NOMGB"},
   {E_QFULL,                         "E_QFULL"},
   {E_QKILLD,                        "E_QKILLD"},
   {E_NOMSG,                         "E_NOMSG"},
   {E_TATQDEL,                       "E_TATQDEL"},
   {E_MATQDEL,                       "E_MATQDEL"},
   {E_NOEVS,                         "E_NOEVS"},
   {E_NOTINASR,                      "E_NOTINASR"},
   {E_NOASR,                         "E_NOASR"},
   {E_NOSCB,                         "E_NOSCB"},
   {E_NOSEM,                         "E_NOSEM"},
   {E_SKILLD,                        "E_SKILLD"},
   {E_TATSDEL,                       "E_TATSDEL"},
   {E_NOTIME,                        "E_NOTIME"},
   {E_ILLDATE,                       "E_ILLDATE"},
   {E_ILLTIME,                       "E_ILLTIME"},
   {E_ILLTICKS,                      "E_ILLTICKS"},
   {E_NOTIMERS,                      "E_NOTIMERS"},
   {E_BADTMID,                       "E_BADTMID"},
   {E_TMNOTSET,                      "E_TMNOTSET"},
   {E_TOOLATE,                       "E_TOOLATE"},
   {E_ILLRPC,                        "E_ILLRPC"},
   {E_NOAGNT,                        "E_NOAGNT"},
   {E_AGTBLKD,                       "E_AGTBLKD"},
   {E_PALIGN,                        "E_PALIGN"},
   {E_LALIGN,                        "E_LALIGN"},
   {E_UNMAPPED,                      "E_UNMAPPED"},
   {E_SUPER,                         "E_SUPER"},
   {E_TOOMUCH,                       "E_TOOMUCH"},
   {E_MAPPED,                        "E_MAPPED"},
   {E_NOSECT,                        "E_NOSECT"},
   {E_ZEROMAP,                       "E_ZEROMAP"},
   {E_TOOLONG,                       "E_TOOLONG"},
   {E_SWITCH,                        "E_SWITCH"},
   {E_IODN,                          "E_IODN"},
   {E_NODR,                          "E_NODR"},
   {E_IOOP,                          "E_IOOP"},
   {E_INACTIVE_IPS_PROTOCOL,         "E_INACTIVE_IPS_PROTOCOL"},
   {E_INVALID_IPS_PORT,              "E_INVALID_IPS_PORT"},
   {E_NOT_ENOUGH_MEMORY,             "E_NOT_ENOUGH_MEMORY"},
   {E_UNABLE_ALLOCATE_MEMORY,        "E_UNABLE_ALLOCATE_MEMORY"},
   {E_NUM_OF_BUF_EXCEED_8,           "E_NUM_OF_BUF_EXCEED_8"},
   {E_RESET,                         "E_RESET"},
   {E_ROUTINE_INIT_FAILED,           "E_ROUTINE_INIT_FAILED"},
   {E_SWITCH_DEFAULT,                "E_SWITCH_DEFAULT"},
   {E_UNEXPECTED_ELSE,               "E_UNEXPECTED_ELSE"},
   {E_UNEXPECTED_OPCODE,             "E_UNEXPECTED_OPCODE"},
   {E_UNEXPECTED_MSG_RESP,           "E_UNEXPECTED_MSG_RESP"},
   {E_UNEXPECTED_TERMINATION,        "E_UNEXPECTED_TERMINATION"},
   {E_Q_RECEIVE_TIMED_OUT,           "E_Q_RECEIVE_TIMED_OUT"},
   {E_BATTRAM_WRITE_FAULT,           "E_BATTRAM_WRITE_FAULT"},
   {E_BATTRAM_READ_FAULT,            "E_BATTRAM_READ_FAULT"},
   {E_VARIABLE_OUT_OF_RANGE,         "E_VARIABLE_OUT_OF_RANGE"},
   {E_ILLEGAL_IPS_COMMAND,           "E_ILLEGAL_IPS_COMMAND"},
   {E_DETERMINE_OBJECT_ID_NOT_FOUND, "E_DETERMINE_OBJECT_ID_NOT_FOUND"},
   {E_PARAMETER_ATTRIBUTE_FAULT,     "E_PARAMETER_ATTRIBUTE_FAULT"},
   {E_PARAMETER_WRITE_OUT_OF_RANGE,  "E_PARAMETER_WRITE_OUT_OF_RANGE"},
   {E_PARAMETER_DATABASE_OUT_OF_RANGE,"E_PARAMETER_DATABASE_OUT_OF_RANGE"},
   {E_PARAMETER_UNKNOWN,             "E_PARAMETER_UNKNOWN"},
   {E_PARAMETER_UNKNOWN_ACCESS_REQUEST,"E_PARAMETER_UNKNOWN_ACCESS_REQUEST"},
   {E_PARAMETER_READ_ONLY,           "E_PARAMETER_READ_ONLY"},
   {E_SIZE_DOES_NOT_MATCH_LOCAL_VARIABLE,"E_SIZE_DOES_NOT_MATCH_LOCAL_VARIABLE"},
   {E_INVALID_ERROR_KIND,            "E_INVALID_ERROR_KIND"},
   {E_INVALID_ERROR_CODE,            "E_INVALID_ERROR_CODE"},
   {E_INVALID_ERROR_REQUEST,         "E_INVALID_ERROR_REQUEST"},
   {E_INVALID_DIAGS_REQUEST,         "E_INVALID_DIAGS_REQUEST"},
   {E_UNEXPECTED_IPS_COMMAND,        "E_UNEXPECTED_IPS_COMMAND"},
   {E_DEFAULT_PARAMETERS_WRITTEN,    "E_DEFAULT_PARAMETERS_WRITTEN"},
   {E_ILLEGAL_FPSP_MODE,             "E_ILLEGAL_FPSP_MODE"},
   {E_PASSED_PARAMETER_OUT_OF_RANGE, "E_PASSED_PARAMETER_OUT_OF_RANGE"},
   {E_ILLEGAL_PARAMETER_WRITE,       "E_ILLEGAL_PARAMETER_WRITE"},
   {E_BAD_CRC,                       "E_BAD_CRC"},
   {E_SWARE,                         "E_SWARE"},
   {E_BUFFER_LENGTH_EXCEEDED,        "E_BUFFER_LENGTH_EXCEEDED"},
   {E_EE_DATA_MODIFIED,              "E_EE_DATA_MODIFIED"},
   {E_UNABLE_TO_START_TASKS,         "E_UNABLE_TO_START_TASKS"},
    };

const ERR_CALLER_NAME_TYPE  error_caller_name[] =
   {
   {ACCESS_CONTROL_OUTPUT_PORTS,     "ACCESS_CONTROL_OUTPUT_PORTS"},
   {ASYNC_ACTIVE_CONNECTION,         "ASYNC_ACTIVE_CONNECTION"},
   {COMM_ACTIVE_SESSION,             "COMM_ACTIVE_SESSION"},
   {COMM_INBOUND_MSG_ROUTER,         "COMM_INBOUND_MSG_ROUTER"},
   {COMM_OUTBOUND_MSG_ROUTER,        "COMM_OUTBOUND_MSG_ROUTER"},
   {COMM_PASSWORD,                   "COMM_PASSWORD"},
   {COMM_QUEUE_STRING,               "COMM_QUEUE_STRING"},
   {COMM_XMT_STRING,                 "COMM_XMT_STRING"},
   {EEPROM_ACCESS,                   "EEPROM_ACCESS"},
   {EEPROM_MEMCPY,                   "EEPROM_MEMCPY"},
   {ERROR_LOG_HANDLER,               "ERROR_LOG_HANDLER"},
   {EXCEPTION_HANDLER,               "EXCEPTION_HANDLER"},
   {FIPS_RX_HANDLER,                 "FIPS_RX_HANDLER"},
   {FIPS_TX_HANDLER,                 "FIPS_TX_HANDLER"},
   {FPSP_PORT_MANAGER,               "FPSP_MANAGER"},
   {FPSP_SHELL,                      "FPSP_SHELL"},
   {FRONT_PANEL_DISPLAY_MANAGER,     "FRONT_PANEL_DISPLAY_MANAGER"},
   {FRONT_PANEL_KEY_PAD_MANAGER,     "FRONT_PANEL_KEY_PAD_MANAGER"},
   {FRONT_PANEL_KEY_PAD_TASK,        "FRONT_PANEL_KEY_PAD_TASK"},
   {FRONT_PANEL_STATE_COORDINATOR,   "FRONT_PANEL_STATE_COORDINATOR"},
   {MANAGE_ERRORS_MAIN,              "MANAGE_ERRORS_MAIN"},
   {MANAGE_TIMERS,                   "MANAGE_TIMERS"},
   {MONITOR_INPUT_PORTS,             "MONITOR_INPUT_PORTS"},
   {NVM_MANAGER,                     "NVM_MANAGER"},
   {QUEUE_PRINT,                     "QUEUE_PRINT"},
   {READ_FRONT_PANEL_KEYPAD,         "READ_FRONT_PANEL_KEYPAD"},
   {REMOTE_SW_DOWNLOAD_MGR,          "REMOTE_SW_DOWNLOAD_MGR"},
   {ROOT,                            "ROOT"},
   {RSM_PROCESS_S_REC,               "RSM_PROCESS_S_REC"},
   {SEND_COMM_STRING_LONG,           "SEND_COMM_STRING_LONG"},
   {SHELL_PROTOCOL_SELECTION,        "SHELL_PROTOCOL_SELECTION"},
   {SPI_DRIVER,                      "SPI_DRIVER"},
   {SRAM_ACCESS,                     "SRAM_ACCESS"},
   {SWARE_LOG_HANDLER,               "SWARE_LOG_HANDLER"},
   {UNIT_TEST,                       "UNIT_TEST"},
   {VERIFY_PASSWORD,                 "VERIFY_PASSWORD"},
   {WD_TICKLE,                       "WD_TICKLE"},
   };

const ERR_REQ_NAME_TYPE  error_request_name[] = 
   {
   {UNRECOVERABLE,                   "UNRECOVERABLE"},
   {RESET_WELDER,                    "RESET_WELDER"},
   {LOG_ERROR,                       "LOG_ERROR"},
   {CLEAR_ERROR,                     "CLEAR_ERROR"},
   };

#endif /* CONVERTED_STRINGS_H */
