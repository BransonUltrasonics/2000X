/* $Header:   D:/databases/VMdb/2000Series/INC/RTCLOCK.H_V   2.11   28 Dec 2010 08:24:04   PDwivedi  $ */
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

 -------------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author          Description
   ==========   ========   ======          ===========
      0         12/12/94   Mark Lazarewicz Initial release 
      1         05-15-96   BEKymer         Add proper function prototyping
      2         10-19-96   LAM             chged function prototyping
      3         10-22-96   PhilJ           No code changes
      4         03-05-97   PhilJ           Modified to new TimeKeeper ram.
      5         03-05-97   PhilJ           Changed READ_WRITE to HALT.
      2.8       10-25-99   JZ              changed RtcReadDateandTime(), RtcWrite()
                                           and added typedef RTC
      2.9       10-30-00   BEKymer         Create defines for contolling OSC bit to
                                            fix time going backwards (issue #3651)
      2.10      06-08-10   PDwivedi        Fix Japan / RTC fix.
      2.11      12-28-10   PDwivedi        Revert back to original changes(before Fix japan/ RTC) .

 ------------------------------- DESCRIPTION -----------------------------------

   This file defines prototypes for the real time clock
 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"


#ifndef RTC_ALREADY_DEFINED
#define RTC_ALREADY_DEFINED
typedef struct {
                 SINT32   Day;
                 SINT32   Month;
                 SINT32   Year;
                 SINT32   Minute;
                 SINT32   Second;
                 SINT32   Hour;
               } RTC;
#endif               

/*--------------------------- Function Prototyping -------------------------*/

void   InitRtclock(void);
void   StartRtclock(void);
void   RtcWrite(UINT16 ID, SINT32 NewDateandTime);
RTC    RtcReadDateandTime(void);
BYTE   Bin2Bcd8(BYTE bin_val);
UINT16 Bin2Bcd16(UINT16 bin_val);
UINT8  Bcd2Bin8(UINT8 bcd_val);
UINT16 Bcd2Bin16(UINT16 bcd_val);


/*--------------------------------- DEFINES --------------------------------*/

#define CLOCK_SUNDAY                 0x01    /* Day of week, not used in this implementation */
#define CLOCK_MONDAY                 0x02
#define CLOCK_TUESDAY                0x03
#define CLOCK_WEDNESDAY              0x04
#define CLOCK_THURSDAY               0x05
#define CLOCK_FRIDAY                 0x06
#define CLOCK_SATURDAY               0x07

#define CLOCK_24HR                   0x00
#define CLOCK_12HR                   0x80
#define CLOCK_PM                     0x20

#define ENABLE_RTCLOCK               0x00   /* Allows Normal Operation to continue */
#define HALT_RTCLOCK                 0xC0   /* Halts updates to registers */
#define WRITE_RTCLOCK                0x80
#define READ_RTCLOCK                 0x40
#define START_CLOCK                  0x7F
#define START_OSC                    0x40   /* For test only, don't want this running normally */
#define STOP_OSC                     0x00   /* This is normal condition */

#define RTC_CONTROL_REG              0x16FFF8
#define RTC_SECONDS_REG              0x16FFF9
#define RTC_MINUTES_REG              0x16FFFA
#define RTC_HOUR_REG                 0x16FFFB
#define RTC_DAY_REG                  0x16FFFC
#define RTC_DATE_REG                 0x16FFFD
#define RTC_MONTH_REG                0x16FFFE
#define RTC_YEAR_REG                 0x16FFFF








