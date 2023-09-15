/* $Header:   K:/APPS/PVCS Pro/332new/INC/FMTSTRS.H_V   2.14   Jul 14 2003 06:55:20   BWadia  $ */
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
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menu.h

   Function name:

 --------------------------------- REVISIONS --------------------------------

   Revision #      Date       Author      Description
   ==========     ========    ======      ===========
   0                            PJ        Initial Version                   
   1.0            06/07/96      PJ        Deleted sending Stringstart to
                                          FormatTitleStr()
   2.0            06/20/96      PJ        Added FormatTimeStr and FormatDateStr
                                          Prototypes.
   3.0            10/11/96      PJ        Added FormatAlarmStr Prototype.
   3.1            11/27/96      PJ        Added FormatNAStr Prototype.
   3.2            04/04/97      PJ        Added FormatDateStrs Prototype.
   2.10           09/28/97      LAM       Added FormatFreqChg prototype
   2.11           01/29/98      BJB       Added prototype FormatSignedInt(),
                                           deleted FormatDateStrs(),
                                           FormatFreqChg().
   2.12           11/02/98      BJB       Deleted prototype FormatPresetStr().

   2.13           05/30/00      SCM       Checked in for testing by Laura,John.
   2.14           12/07/03      JOY       Added one more argument 'DisplayType'
                                          to the 'FormatBargraphStr(..)', which
                                          adjusts display line length for QVGA &
                                          VFD. 

*/  

/*
 ------------------------------- DESCRIPTION ---------------------------------
*/ 


/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/

void FormatTitleStr( SINT8 String[], SINT8 NumDisplayChar1, SINT32 Value1,
                     SINT8 NumDisplayChar2, SINT32 Value2);

void FormatStr1( SINT8 String[], SINT8 StringStart, SINT8 NumDisplayChar,
                 SINT32 Value, SINT8 Delimiter);

void FormatStr2( SINT8 String[], SINT8 StringStart, SINT8 Delimiter1,
                 SINT8 NumDisplayChar1, SINT32 Value1, SINT8 Delimiter2,
                 SINT8 NumDisplayChar2, SINT32 Value2);

void FormatBargraphStr(SINT8 String1[], SINT8 String2[], UINT8 DisplayType);

void FormatTimeStr( SINT8 String[], SINT8 Delimiter1, UINT8 NumDisplayChar1,
                    SINT32 Hour, SINT8 Delimiter2, UINT8 NumDisplayChar2,
                    SINT32 Minute );

void FormatDateStr( SINT8 String[], SINT8 Delimiter1, UINT8 NumDisplayChar1,
                    SINT32 Month, SINT8 Delimiter2, UINT8 NumDisplayChar2,
                    SINT32 Day, SINT8 Delimiter3, UINT8 NumDisplayChar3,
                    SINT32 Year );

void FormatValue( SINT8 String[], UINT8 TotalChar, UINT8 NumDisplayChar1, SINT32 Value,
                  SINT8 Delimiter, UINT8 NumDisplayChar2);

void FormatAlarmStr( SINT8 *String, SINT8 NumDisplayChar, SINT32 Value);

void FormatNAStr( SINT8 String[] );

void FormatSignedInt( SINT8 String[], UINT8 LastChar, UINT8 NumDisplayChar,
 SINT32 Value );
