/* $Header:   L:/pvcs/1000/psos332/archives/inc/CMDHNDLR.H_v   2.4   01 Aug 1996 14:47:48   BKYMER  $ */
#ifndef COMMAND_LINE_TABLE_H
#define COMMAND_LINE_TABLE_H
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
 ------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: command_line_table

   Filename: cmdhndlr.h 


 ----------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0            02/08/96      Mark Lazarewicz Initial release 
      1            06/19/96      LAM          protect probe reference

 --------------------------- DESCRIPTION -----------------------------------

 This header contains the command line interface table of commands needed by
 fpsp_manager.c

 --------------------------- INCLUDE FILES ----------------------------------
*/

/*
 ----------------------------- DEFINES -------------------------------------
*/

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

#include "help.h"

#include "sys_conf.h"

#if (SC_PROBE)


   extern void probe(void);           
#endif
/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef struct
   {         
   char    name[10];           /* command name */
   void    (*function)();      /* pointer to function to call for command */
   char    description[80];    /* description of command to print for "help" command */
   } COMMAND_LINE_ENTRY;

#ifdef ALLOCATE_COMMAND_LINE_TABLE
#if (SC_PROBE)   
COMMAND_LINE_ENTRY Command_Line_Table[] =
  {
    {
    /* COMMAND "help" */
    "HELP"       ,      /* command name */
     help    ,          /* command service routine */    
        /* text string to be printed by "help" command */
    "help      - list all valid commands\r\n",
    },

    {
    /* COMMAND "probe" */
    "PROBE"      ,      /* command name */
     probe       ,      /* command service routine */
        /* text string to be printed by "help" command */
    "probe     - break to pROBE+\r\n", 
    },

  };
#else

COMMAND_LINE_ENTRY Command_Line_Table[] =
  {
    {
    /* COMMAND "help" */
    "HELP"       ,      /* command name */
     help    ,          /* command service routine */    
        /* text string to be printed by "help" command */
    "help      - list all valid commands\r\n",
    },

    {
    /* COMMAND "help" */
    "HELP"       ,      /* command name */
     help    ,          /* command service routine */    
        /* text string to be printed by "help" command */
    "help      - list all valid commands\r\n",
    },

  };

#endif

#else

/* If someone just wants access to the command line table */
COMMAND_LINE_ENTRY Command_Line_Table[];

#endif  /* end of ALLOCATE_COMMAND_LINE_TABLE */
#endif /* COMMAND_LINE_TABLE_H */

UINT32 number_of_commands( void );

