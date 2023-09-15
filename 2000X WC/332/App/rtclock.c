/* $Header:   D:/databases/VMdb/2000Series/App/RTCLOCK.C_V   2.17   28 Dec 2010 08:23:34   PDwivedi  $ */
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


 -------------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author            Description
   ----------   -------    ------            -----------
       0        12/4/95    Mark Lazarewicz   Initial   
       1        05-15-96   BEKymer           Add proper function prototyping
       2        12-11-96   PhilJ             Write logic 0 to Bit5 of Day
                                             Register to turn on Phantom clock.
       3.0      02-24-97   PhilJ             Rewrote functions to the Dallas
                                             DS1644 Nonvolatile Timekeeping Ram.
       3.1      03-05-97   PhilJ             Corrected bug in Start Clock.
       3.2      03-05-97   PhilJ             Clock is started in every WriteRtc.
       3.3      03-06-97   PhilJ             Corrected bug in clock start .
       4.0      04-21-97   LAM               added seconds                 
       4.1      04-21-97   PhilJ             Corrected seconds readout.                 
       2.13     09-11-97   LAM               unit test version                          
       2.14     10-25-99   JZ                Changed RtcReadDateandTime() and RtcWrite()
       2.15     10-30-00   BEKymer           Stop the OSC whenever a write is done to
                                              the RTC.  This stops the effect of time
                                              going backwards.  Tracker issue # 3651.
       2.16     06-08-10   PDwivedi          Fix japan/ RTC .
       2.17     12-28-10   PDwivedi          Revert back to original changes(before Fix japan/ RTC) .

 ------------------------------- DESCRIPTION -----------------------------------

 These functions interface to the Real-Time Clock Chip .


 ----------------------------- INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "time.h"
#include "rtclock.h"
#include "param.h"

/*----------------------------- LOCAL FUNCTIONS ----------------------------*/


/*-----------------------------EXTERNAL DATA -------------------------------*/

extern UINT32   Ticks;


/*-----------------------------GLOBAL DATA -------------------------------*/


/*
 ---------------------------------- CODE ---------------------------------------
*/


/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename: 

   Function name: 

             Written by:  
                  Date:  
              Language:  "C"


 ------------------------------- DESCRIPTION -----------------------------------

  Where the values are BINARY(hexadecimal) and NOT BCD as is required by the RTC.
  Therefore, these routines will convert the time & date to BCD.

  ------------------------------------------------------------------------------------
*/

void InitRtclock(void)
{
   UINT8 *RegisterPtr;

   RegisterPtr = (UINT8 *)RTC_CONTROL_REG;

   // Halt clock updates
   *RegisterPtr = HALT_RTCLOCK;   /* Prevents clock registers from updating */ 
}



void StartRtclock(void)
{
   UINT8 *PtrControlReg;
   UINT8 *StartClockPtr;

   PtrControlReg = (UINT8 *)RTC_CONTROL_REG;
   StartClockPtr = (UINT8 *)RTC_SECONDS_REG;

   *StartClockPtr = START_CLOCK;
   *PtrControlReg = ENABLE_RTCLOCK;   /* Loads register on Zero transition */
}


void RtcWrite(UINT16 ID, SINT32 NewDateandTime)
{
   UINT8 *ControlRegPtr;
   UINT8 *ClockPtr;
   UINT8 Scratch;

   ControlRegPtr = (UINT8 *)RTC_CONTROL_REG;

   // Halt clock updates
   *ControlRegPtr = WRITE_RTCLOCK;

   ClockPtr = (UINT8 *)RTC_SECONDS_REG;
   *ClockPtr = 0;     /* Force Clock Start */

   ClockPtr = (UINT8 *)RTC_DAY_REG;  /* Always make sure Osc is stopped */
   *ClockPtr = STOP_OSC;
   switch(ID)
   {
      // Seconds & minutes & hours
      case SECONDS:
         ClockPtr = (UINT8 *)RTC_SECONDS_REG;
           Scratch = Bin2Bcd8((BYTE)NewDateandTime);
           *ClockPtr = 0;   /* Starts clock */
         break;

      case MINUTE:
         ClockPtr = (UINT8 *)RTC_MINUTES_REG;
         Scratch = Bin2Bcd8((BYTE)NewDateandTime);
         *ClockPtr = Scratch & 0x7F;
         break;

      case HOUR:
         ClockPtr = (UINT8 *)RTC_HOUR_REG;
         Scratch = Bin2Bcd8((BYTE)NewDateandTime);
         *ClockPtr = Scratch & 0x3F;
         break;


      // Day of week (1 - 7), RTC_DAY_REG currently NOT used.


      case DAY:
         ClockPtr = (UINT8 *)RTC_DATE_REG;
         Scratch = Bin2Bcd8((BYTE)NewDateandTime);
         *ClockPtr = Scratch & 0x3F;
         break;

      case MONTH:
         ClockPtr = (UINT8 *)RTC_MONTH_REG;
         Scratch = Bin2Bcd8((BYTE)NewDateandTime);
         *ClockPtr = Scratch & 0x1F;
         break;

      case YEAR:
         ClockPtr = (UINT8 *)RTC_YEAR_REG;
         Scratch = Bin2Bcd8((BYTE)NewDateandTime);
         *ClockPtr = Scratch;
         break;
      default:
         ClockPtr = (UINT8 *)RTC_SECONDS_REG; /* default to seconds */
         Scratch = Bin2Bcd8((BYTE)NewDateandTime);
         *ClockPtr = 0;   /* Starts clock */
         break;

   }
   *ControlRegPtr = ENABLE_RTCLOCK;

}


RTC RtcReadDateandTime(void)
{

   UINT8 *CntrlRegPtr;
   UINT8 *ClkPtr;
   RTC DateandTime;

   CntrlRegPtr = (UINT8 *)RTC_CONTROL_REG;

   // Halt clock updates
   *CntrlRegPtr = READ_RTCLOCK;

   ClkPtr = (UINT8 *)RTC_SECONDS_REG;

   // Seconds & minutes & hours
   DateandTime.Second = Bcd2Bin8(*ClkPtr++);
   // Increments to Minutes Register Location RTC_MINUTES_REG

   DateandTime.Minute = Bcd2Bin8(*ClkPtr++) & 0x0000007F;
   // Increments to Hour Register Location RTC_HOUR_REG

   DateandTime.Hour = Bcd2Bin8(*ClkPtr) & 0x3F;


   // Day of week (1 - 7), RTC_DAY_REG currently NOT used.


   ClkPtr = (UINT8 *)RTC_DATE_REG;
   // Date of month, month, year.
   DateandTime.Day   = Bcd2Bin8(*ClkPtr++) & 0x0000003F;
   // Increments to Month Register Location RTC_MONTH_REG

   DateandTime.Month = Bcd2Bin8(*ClkPtr++) & 0x0000001F;
   // Increments to Year Register Location RTC_YEAR_REG

   DateandTime.Year = Bcd2Bin8(*ClkPtr) & 0x000000FF;

   *CntrlRegPtr = ENABLE_RTCLOCK;
   
   return (DateandTime);
}



/*
  ------------------------------------------------------------------------------------
  The following BIN->BCD and BCD->BIN functions are tailored for use by this module.
  Limitations are as follows -

      BIN -> BCD  :  Bin2Bcd8() will convert binary values up through 99.
                     Bin2Bcd16() will convert binary values up through 9999.

      Example     :  The binary year value 0x07c9 (1,993) will be converted to
                     0x1993. The binary date value 0x1b (27) will be converted
                     to 0x27.

      BCD -> BIN  :  Bcd2Bin8() will convert BCD values up through 99 to binary.
                     Bcd2Bin16() will convert BCD values up through 9999 to binary.

  ------------------------------------------------------------------------------------
*/

BYTE Bin2Bcd8(BYTE bin_val)


{

   UINT8       bcd_val;

   bcd_val = 0x00;

   if(bin_val <= 99)
   {
      while(bin_val > 9)
      {
         bcd_val += 0x10;
         bin_val -= 10;
      }

      bcd_val += bin_val;     

   }

   return(bcd_val);

}

UINT16 Bin2Bcd16(UINT16 bin_val)


{

   UINT16        bcd_val;

   bcd_val = 0x0000;

   if(bin_val <= 9999)
   {

      while(bin_val > 999)
      {
         bcd_val += 0x1000;
         bin_val -= 1000;
      }

      while(bin_val > 99)
      {
         bcd_val += 0x100;
         bin_val -= 100;
      }

      while(bin_val > 9)
      {
         bcd_val += 0x10;
         bin_val -= 10;
      }

      bcd_val += bin_val;     

   }

   return(bcd_val);

}


UINT8 Bcd2Bin8(UINT8 bcd_val)


{

   UINT8        bin_val;

    bin_val = 0x00;

    /*
     * Check for a valid BCD formated number
     */
    if( ((bcd_val & 0xF0) <= 0x90) &&
        ((bcd_val & 0x0F) <= 0x09) )
        {
        while(bcd_val > 9)
            {
            bcd_val -= 0x10;
            bin_val += 10;
            }

        bin_val += bcd_val;     
        }

    return(bin_val);

}

/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename: 

   Function name: 

             Written by:  
                  Date:  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
    0             12/4/95     Mark Lazarewicz       Initial   

 ------------------------------- DESCRIPTION -----------------------------------


 ------------------------------- PSEUDO CODE -----------------------------------

*/


UINT16 Bcd2Bin16(UINT16 bcd_val)
{

UINT16        bin_val;

    bin_val = 0x0000;

    /*
     * Check for a valid BCD formated number
     */
    if( ((bcd_val & 0xF000) <= 0x9000) &&
        ((bcd_val & 0x0F00) <= 0x0900) &&
        ((bcd_val & 0x00F0) <= 0x0090) &&
        ((bcd_val & 0x000F) <= 0x0009) )
        {

        while(bcd_val > 0x0999)
            {
            bcd_val -= 0x1000;
            bin_val += 1000;
            }

        while(bcd_val > 0x0099)
            {
            bcd_val -= 0x0100;
            bin_val += 100;
            }

        while(bcd_val > 0x0009)
            {
            bcd_val -= 0x0010;
            bin_val += 10;
            }

        bin_val += bcd_val;     

        }

    return(bin_val);

}


/* Include for Unit test */
#ifdef INCLUDE_UNIT_TEST
#include "rtclock.ut"
#endif
/* End of include for unit test */
