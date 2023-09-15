/* $Header:   L:/pvcs/1000/psos332/archives/inc/ADMENUTY.H_v   2.2   01 Aug 1996 14:52:22   BKYMER  $ */
#ifndef  ASCII_DIAGS_MENU_TYPE_H
#define  ASCII_DIAGS_MENU_TYPE_H  1
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
-------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: N/A

   Filename:  admenuty.h


            Written by: Mark Lazarewicz 
                  Date: 03/23/96 
              Language:  "C"

 ---------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            03/23/96      Mark L      Initial
       1            07/03/96      LAM         cleanup

 ---------------------------- DESCRIPTION -----------------------------------

   This routine defines all special "ESC-Bracket" keys for the VT-100 terminal
to control the cursor and screen displaying.

 --------------------------- INCLUDE FILES ----------------------------------

*/


/*
 ------------------------------ DEFINES -------------------------------------
*/    

/*  Define terminal respose key string */  
#define  ESC          "\x1B"            /* Esc in hex 0x1b */
#define  BRACKET      "["               /* Bracket character */
#define  KEY_CR       "\x1B0M"          /* VT100 <Enter> key */
#define  KEY_EXIT     "\x11"            /* VT100 <Esc> Ctrl+Q key   */
#define  KEY_UP       "\x1B[A"          /* VT100 <Arrow Up> key */
#define  KEY_DOWN     "\x1B[B"          /* VT100 <Arrow Down> key */


#define  IDENT_TERMINAL "\x1B[0c"     /* "Esc[c":     Identify the terminal type */ 
#define  SET_SCROLL_REG "\x1B[0;24r"  /* "Esc[0;24r": Set scroll region for 24 lines screen   */
#define  SET_REGION_ON  "\x1B[?6h"    /* "Esc[?6h":   Turn on region: Origine mode  */
#define  SET_REGION_OFF "\x1B[?6l"    /* "Esc[?6l":   Turn off region: full screen mode */
                                    
#define  ERASE_SCREEN   "\x1B[2J"     /* "Esc[2J":    Erase entire screen-cursor doesn't move */
#define  ERASE_EOL      "\x1B[0K"     /* "Esc[0K":    Erase to the end of line */
#define  ERASE_LINE     "\x1B[2K"     /* "Esc[2K":    Erase entire line-cursor doesn't move*/
                                  
#define  NORMAL_VIDEO   "\x1B[0m"     /* "Esc[0m":    Reset attributes: normal video          */
#define  INVERSE_VIDEO  "\x1B[7m"     /* "Esc[7m":    Reverse video text & background         */ 
#define  HIGH_LIGHT     "\x1B[1m"     /* "Esc[1m":    Display text in higher intensity        */
#define  BLINKING_MODE  "\x1B[5m"     /* "Esc[5m":    Display text in blinking mode           */
#define  UNDERLINE_MODE "\x1B[4m"     /* "Esc[4m":    Turn on underline mode                  */
                            
#define  CURSOR_HOME    "\x1B[H"      /* "Esc[H":     Send cursor home-Top of the window       */ 
#define  NEW_LINE       "\x1BE"       /* "EscE":     Go to beginning of the next line = CR-LF */
#define  CURSOR_UP      "\x1B[1A"     /* "Esc[1A":    Cursor up one: scroll screen at top      */
#define  CURSOR_DOWN    "\x1B[1B"     /* "Esc[1B":    Cursor down one: scroll screen at bottom */
#define  CURSOR_RIGHT   "\x1B[1C"     /* "Esc[1C":    Put cursor right number of column        */
#define  CURSOR_LEFT    "\x1B[1D"     /* "Esc[1D":    Put cursor to the far left of the screen */

#define  CURSOR_DOWN_3     "\x1B[3B"     /* "Esc[3B":    Cursor down three: scroll screen at bottom */
#define  CURSOR_DOWN_6     "\x1B[6B"     /* "Esc[3B":    Cursor down three: scroll screen at bottom */
#define  CURSOR_UP_3       "\x1B[3A"     /* "Esc[4A":    Cursor up four line: scroll screen at top  */
#define  CURSOR_FARLEFT    "\x1B[80D"    /* "Esc[80D":   Put cursor to the far left of the screen */
#define  CURSOR_RIGHT_10   "\x1B[10C"    /* "Esc[10C":   Put cursor right number of column        */
#define  GOTO_X10_Y7       "\x1B[7;10f"  /* "Esc[pl;pcf:" Set cursor at line and column number */

#define  SAVE_CURSOR_POS   "\x1B[7"       /* Save the current cursor location    */
#define  REST_CURSOR_POS   "\x1B[8"       /* restore previous cursor locations   */
                                                                
#define  NUMBER_OF_BUFFERS         128     /* number of screen to display in terminal */
#define  ASCII_DIAGS_BUFFER_SIZE  1024     /* 2 bytes/character for 24rows*80columns characters */
#define  ASCII_DIAGS_ALLOC_SIZE    ASCII_DIAGS_BUFFER_SIZE * NUMBER_OF_BUFFERS
#define  STR_SIZE          40

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
typedef
*/    

/*  Define type for control character displayed */ 
typedef packed enum 
       { 
          NORMAL_VIDEO_ATTRIBUTE    = 0u,
          REVERSE_VIDEO_ATTRIBUTE   = 1,
          HILIGHT_VIDEO_ATTRIBUTE   = 2,
          UNDERLINE_VIDEO_ATTRIBUTE = 3,
          MAX_VIDEO_ATTRIBUTE_LIMIT
       }    VIDEO_ATTRIBUTE_TYPE;
                                   
typedef packed enum 
       {
          CURSOR_STANDING_POSITION   = 0u,
          UP_DIRECTION_POSITION      = 1,
          DOWN_DIRECTION_POSITION    = 2,
          MAX_CURSOR_POSITION_LIMIT
       }    CURSOR_POSITION_TYPE;    

typedef packed enum 
      {
         START_ASCII_MENU_WINDOW      = 0u,
         MAIN_ASCII_MENU_WINDOW       = 1,
         SUB_ASCII_MENU_WINDOW        = 2,
         MAX_ASCII_MENU_WINDOW_LIMIT
      } ASCII_MENU_STATE_TYPE;



/*identify terminal/set scroll region/ident origine/set cursor home/erase screen*/
                          
/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* ASCII_DIAGS_MENU_TYPE_H */
