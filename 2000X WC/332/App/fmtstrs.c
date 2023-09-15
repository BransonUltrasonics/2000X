/* $Header:   D:/SWLab/VMdb/2000Series/App/FMTSTRS.C_V   2.29   09 Sep 2008 20:39:56   nhahmed  $ */

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
/*************************                          **************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name: fmtstrs

   Filename: fmtstrs.c

   Function name: void FormatTitleStr();
                  void FormatStr1();
                  void FormatStr2();

 --------------------------------- REVISIONS --------------------------------

   Revision #     Date         Author     Description
   ==========     ========     ======     ===========
      0           04/29/96       PJ       Initial Version
      1.0         06/07/96       PJ       Change FormatTitleStr to display
                                          1 of xx
      2.0         06/14/96       PJ       Added function FormatBargraphStr()
      3.0         06/20/96       PJ       Added functions FormatTimeStrs and
                                          FormatDateStrs
      3.1         06/24/96       PJ       Display a zero if value = 0 in
                                          FormatStr1.
      3.2         07/01/96       PJ       Correct bug in FormatStr1 when a
                                          zero value is entered.
      3.3         07/12/96       PJ       Added function FormatValue().
      3.4         08/01/96       PJ       Changed FormatTitleStr to ad Pg.
      3.5         08/14/96       PJ       Added FormatPresetStr.
      3.6         09/04/96       PJ       Modification to FormatTimeStr
                                          and FormatdateStr.
      3.7         10/11/96       PJ       Added function FormatAlarmStr().
      3.8         10/12/96       LAM      capitalized J in joules          
      3.9         10/11/96       PJ       Added function FormatNAStr().
      4.0         12/12/96       PJ       Insert FILLCHAR in FormatStr2.
      4.1         02/18/97       PJ       Modified FormatValue.
      4.2         02/18/97       PJ       Modified FormatStr1.
      4.3         04/04/97       PJ       Added FormatDateStrs function.
      2.19        09/28/97       LAM      Added FormatFreqChg function.
      2.20        01/29/98       BJB      Added FormatSignedInt() function.
                                          Deleted FormatDateStrs(),
                                           FormatFreqChg().
                                          FormatValue() displays leading 0
                                           before decimal point.
      2.21        11/02/98       BJB      Deleted FormatPresetStr().
      2.22        05-26-00       SCM      Checked in for testing by Laura, John.
      2.23        06-14-00       SCM      Removed tabs and checked in for Ver8 build.
      2.24        06-14-00       SCM      Removed unused variable 'LangIndex'.
      2.25        06-07-00       BEKymer/DJL  fixed SETUPS                            
      2.26        12-07-03       JOY          Added one more argument 'DisplayType'
                                              to the 'FormatBargraphStr(..)', which
                                              adjusts display line length for QVGA &
                                              VFD.
      2.27        07-25-05       Bwadia   Asian Language support for Time, Date, Alarm
      2.28        01-11-08       NHAhmed  Function FormatDateStr and FormatTimeStr were
                                          replicated to be used for LangTest.
      2.29        09-09-08       NHAhmed  CleanUp for multi-language support.

 ------------------------------- DESCRIPTION ---------------------------------

   Temporary replacement for Sprintf till PSOS sprintf problem resolved. 

*/
/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include <prepc.h>
#include "portable.h"
#include "menu.h"
#include "preset.h"

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern SETUPS_Ver800 CurrentPreset;
/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                   
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/



/*
 ---------------------------------- CODE -------------------------------------
*/

void FormatStr1( SINT8 String[], SINT8 StringStart, SINT8 NumDisplayChar,
                 SINT32 Value, SINT8 Delimiter)
{
   UINT8 StringEnd = LINESIZE -1;
   UINT8 FilIndex = StringStart;
   SINT32 Temp;

   while(FilIndex < LINESIZE)
      String[FilIndex++] = FILLCHAR;

   if(Value != 0)
   {
      while(NumDisplayChar > 0 && Value != 0)
      {
           Temp = Value % 10;
         String[StringEnd--] = Temp + 0x30;
         Value /= 10;
         NumDisplayChar--;
      }
   }
   else
        String[StringEnd] = 0x30;   /* Display zero character */
   if(Delimiter != 0)
      String[StringStart] = Delimiter;

}



void FormatStr2( SINT8 String[], SINT8 StringStart, SINT8 Delimiter1,
                 SINT8 NumDisplayChar1, SINT32 Value1, SINT8 Delimiter2,
                 SINT8 NumDisplayChar2, SINT32 Value2)
{
   UINT8 StringEnd = LINESIZE -1;
   UINT8 FillIndex = StringStart;
   SINT32 Temp;

   while(FillIndex < LINESIZE)
      String[FillIndex++] = FILLCHAR;

   while(NumDisplayChar2 != 0)
   {
        Temp = Value2 % 10;
        String[StringEnd--] = Temp + 0x30;
        Value2 /= 10;
      NumDisplayChar2--;
   }

   if(Delimiter2 != 0)
    String[StringEnd--] = Delimiter2;

   if(Value1 != 0)
   {
      while(NumDisplayChar1 != 0 && Value1 != 0)
      {
           Temp = Value1 % 10;
        String[StringEnd--] = Temp + 0x30;
            Value1 /= 10;
         NumDisplayChar1--;
      }
   }
   else
        String[StringEnd--] = 0x30;

   if(Delimiter1 != 0)
    String[StringStart] = Delimiter1;

}

void FormatTimeStr1( SINT8 String[], SINT8 Delimiter1, UINT8 NumDisplayChar1,
                    SINT32 Hour, SINT8 Delimiter2, UINT8 NumDisplayChar2,
                    SINT32 Minute )
{
   SINT32 Temp;
   UINT8 StringEnd;
   
   StringEnd = LINESIZE -1;
   while(NumDisplayChar2 != 0)
   {
        Temp = Minute % 10;
        String[StringEnd--] = Temp + 0x30;
        Minute /= 10;
        NumDisplayChar2--;
   }

   if(Delimiter2 != 0)
      String[StringEnd--] = Delimiter2;
   while(NumDisplayChar1 != 0)
   {
        Temp = Hour % 10;
        String[StringEnd--] = Temp + 0x30;
        Hour /= 10;
        NumDisplayChar1--;
   }
   if(Delimiter1 != 0)
      String[StringEnd--] = Delimiter1;
}

void FormatDateStr1( SINT8 String[], SINT8 Delimiter1, UINT8 NumDisplayChar1,
                    SINT32 Month, SINT8 Delimiter2, UINT8 NumDisplayChar2,
                    SINT32 Day, SINT8 Delimiter3, UINT8 NumDisplayChar3,
                    SINT32 Year )
{
   SINT32 Temp;
   UINT8 StringEnd;

   StringEnd = LINESIZE -1;
   while(NumDisplayChar3 != 0)
   {
        Temp = Year % 10;
        String[StringEnd--] = Temp + 0x30;
        Year /= 10;
        NumDisplayChar3--;
   }

   if(Delimiter3 != 0)
      String[StringEnd--] = Delimiter3;

   while(NumDisplayChar2 != 0)
   {
        Temp = Day % 10;
           String[StringEnd--] = Temp + 0x30;
        Day /= 10;
        NumDisplayChar2--;
   }

   if(Delimiter2 != 0)
      String[StringEnd--] = Delimiter2;

   while(NumDisplayChar1 != 0)
   {
        Temp = Month % 10;
        String[StringEnd--] = Temp + 0x30;
        Month /= 10;
        NumDisplayChar1--;
   }
   
   String[StringEnd--] = ' ';   /* space character */

   if(Delimiter1 != 0)
      String[StringEnd--] = Delimiter1;
}
