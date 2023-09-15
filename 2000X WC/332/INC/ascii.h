/* $Header:   K:/APPS/PVCS Pro/332new/INC/ASCII.H_V   2.3   Jun 30 2000 10:07:36   ashish  $ */
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
*---------------------------- INCLUDE DESCRIPTION ------------------------------
*
*  Filename:  ascii.h
*
*
*           Written by: Mark Lazarewicz
*                 Date: 03/15/96 
*             Language: Microtec "C" Compiler
*
*--------------------------------- REVISIONS -----------------------------------
*
*   Revision #      Date          Author      Description
*   ==========      ========      ======      ===========
*      0            03/15/96      Mark L      initial
*      0            03/15/96      Mark L      initial
*      2.2          07/31/97      PaulG       Removed ESC, already defined
*      2.3          06/30/00      Ashish      Re-instated ESC as this is the right place
*--------------------------------- OVERVIEW -------------------------------------
*
* This file defines the hexadecimal equivalents of ASCII characters.
*
*--------------------------------- INCLUDES -------------------------------------
*
*   NONE
*
*-------------------------------- DEFINITIONS -----------------------------------
*/

#ifndef ASCII_H
#define ASCII_H

#define CTRL_@     0x00
#define     NUL        0x00
#define CTRL_A     0x01
#define     SOH        0x01
#define CTRL_B     0x02
#define     STX        0x02
#define CTRL_C     0x03
#define     ETX        0x03
#define CTRL_D     0x04
#define     EOT        0x04
#define CTRL_E     0x05
#define     ENQ        0x05
#define CTRL_F     0x06
#define     ACK        0x06
#define CTRL_G     0x07
#define     BEL        0x07
#define CTRL_H     0x08
#define     BS         0x08
#define CTRL_I     0x09
#define     HT         0x09
#define     TAB        0x09
#define CTRL_J     0x0A
#define     LF         0x0A
#define CTRL_K     0x0B
#define     VT         0x0B
#define CTRL_L     0x0C
#define     FF         0x0C
#define CTRL_M     0x0D
#define     CR         0x0D
#define CTRL_N     0x0E
#define     SO         0x0E
#define CTRL_O     0x0F
#define     SI         0x0F
#define CTRL_P     0x10
#define     DLE        0x10
#define CTRL_Q     0x11
#define     DC1        0x11
#define     XON        0x11
#define CTRL_R     0x12
#define     DC2        0x12
#define CTRL_S     0x13
#define     DC3        0x13
#define     XOFF       0x13
#define CTRL_T     0x14
#define     DC4        0x14
#define CTRL_U     0x15
#define     NAK        0x15
#define CTRL_V     0x16
#define     SYN        0x16
#define CTRL_W     0x17
#define     ETB        0x17
#define CTRL_X     0x18
#define     CAN        0x18
#define CTRL_Y     0x19
#define     EM         0x19
#define CTRL_Z     0x1A
#define     SUB        0x1A
#define CTRL_LEFT_BRACKET 0x1B
#define     ESC    0x1B
#define CTRL_BACKSLASH 0x1C
#define     FS         0x1C
#define CTRL_RIGHT_BRACKET 0x1D
#define     GS         0x1D
#define CTRL_CIRCUMLFEX 0x1E
#define     RS         0x1E
#define CTRL_UNDERSCORE 0x1F
#define     US         0x1F
#define SP         0x20
#define DEL        0x7f
#define LEFT_BRACKET   0x5B

#endif     /* ASCII_H */

