/* $Header:   K:/APPS/PVCS Pro/332new/App/XMININT.C_V   2.2   Apr 28 1999 09:39:08   ofingere  $ */
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

/*
 --------------------------------- MODULE DESCRIPTION ------------------------------------


   Filename:  xminint.c

   Function name:  WithinXMinInterval


            Written by: Mark Lazarewicz 
                  Date: 1/23/96 
              Language:  "C"

 ------------------------------------- REVISIONS -----------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            1/23/96       Mark L      Initial Version
	  2.2          4/26/99       OFI         Changed for Diab
 ------------------------------------ DESCRIPTION ----------------------------------------
                                                           
   This function compares the times and dates passed in, return TRUE if they are
   10 minute apart, else return FALSE. 
                     
 ------------------------------------ PSEUDO CODE ----------------------------------------


 ----------------------------------- INCLUDE FILES ---------------------------------------
*/

#include "portable.h"
#include "psos.h"

#include "time.h"

#include "xminint.h"

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

/*
 ----------------------------------- LOCAL DEFINES ---------------------------------------
*/


/*
 ------------------------------- LOCAL TYPE DECLARATIONS ---------------------------------
*/


/*
 ------------------------------- GLOBAL DATA -----------------------------------
                        (scope is global to ALL files)
*/

/*
 ---------------------------- PRIVATE GLOBAL DATA ------------------------------
                        (scope is global to THIS file)
*/

/* function prototype */
void  SubtractXMin (UINT8 x_minutes,  
                      struct t_date *current_date, 
                      struct t_time *current_time);

BOOLEAN  IsFeb28Days(UINT16 year);

BOOLEAN CompareTime (struct t_date *first_date_ptr,
                      struct t_time *first_time_ptr,
                      struct t_date *second_date_ptr,
                      struct t_time *second_time_ptr);

/*
 ---------------------------------- CODE ---------------------------------------
*/

BOOLEAN WithinXMinInterval (UINT8          x_minutes,
                               struct t_date  last_reset_date_ptr,
                               struct t_time  last_reset_time_ptr,
                               struct t_date  reset_date_ptr,
                               struct t_time  reset_time_ptr)
   {
   BOOLEAN    ReturnStatus;
        

   SubtractXMin (x_minutes, &reset_date_ptr, &reset_time_ptr);

   ReturnStatus = CompareTime(&reset_date_ptr, 
                                &reset_time_ptr, 
                                &last_reset_date_ptr,
                                &last_reset_time_ptr);

   return ReturnStatus;
   }

void  SubtractXMin (UINT8 x_minutes,  struct t_date *current_date, struct t_time *current_time) 
   {
   if (current_time->minute >= x_minutes)
      {                        
      current_time->minute = current_time->minute - x_minutes;
      }
   else if (current_time->hour > 0)
      {
      current_time->minute = 60 - x_minutes + current_time->minute;
      current_time->hour = current_time->hour - 1;
      }
   else if (current_date->day > 1)
      {
      current_time->minute = 60 - x_minutes + current_time->minute;
      current_time->hour = 23;
      current_date->day = current_date->day - 1;
      }
   else if (current_date->month == 1)
      {
      current_time->minute = 60 - x_minutes +current_time->minute;
      current_time->hour = 23;
      current_date->day = 31;
      current_date->month = 12;
      current_date->year = current_date->year - 1;
      }
   else if (current_date->month == 2 ||
            current_date->month == 4 ||
            current_date->month == 6 ||
            current_date->month == 8 ||
            current_date->month == 9 ||
            current_date->month == 11 )
      {
      current_time->minute = 60 - x_minutes + current_time->minute;
      current_time->hour = 23;
      current_date->day = 31;
      current_date->month = current_date->month -1;
      }
   else if (current_date->month == 5 ||
            current_date->month == 7 ||
            current_date->month == 10 ||
            current_date->month == 12 ) 
      {
      current_time->minute = 60 - x_minutes + current_time->minute;
      current_time->hour = 23;
      current_date->day = 30;
      current_date->month = current_date->month - 1;
      }
   else if (current_date->month == 3 && IsFeb28Days(current_date->year))
      {
      current_time->minute = 60 - x_minutes + current_time->minute;
      current_time->hour   = 23;
      current_date->day = 28;
      current_date->month = 2;
      }
   else if (current_date->month == 3 && !IsFeb28Days(current_date->year))
      {
      current_time->minute = 60 - x_minutes + current_time->minute;
      current_time->hour   = 23;
      current_date->day = 29;
      current_date->month = 2;
      }
       
   return;
   }
       
BOOLEAN  IsFeb28Days(UINT16 year)
   {
   BOOLEAN  is_28days;
       
   if (year % 100  == 0)
      {
      if (year % 400 == 0)
         {
         is_28days = FALSE;
         }
      else
         {
         is_28days = TRUE;
         }
      }
   else
      {
      if (year % 4 == 0)
         {
         is_28days = FALSE;
         }
      else
         {
         is_28days = TRUE;
         }
      }
      
   return (is_28days);
   }
       
BOOLEAN CompareTime (struct t_date *first_date_ptr,
                      struct t_time *first_time_ptr,
                      struct t_date *second_date_ptr,
                      struct t_time *second_time_ptr)
   {
   BOOLEAN                ReturnResult;  
       
   if (first_date_ptr->year < second_date_ptr->year)
      {   
      ReturnResult = TRUE;
      }
   else if (first_date_ptr->year  > second_date_ptr->year)
      {
      ReturnResult = FALSE;
      }
   /* same year */
   else if (first_date_ptr->month  < second_date_ptr->month)
      {
      ReturnResult = TRUE;
      }
   else if (first_date_ptr->month  > second_date_ptr->month)
      {
      ReturnResult = FALSE;
      }
   /* same year and same month */
   else if (first_date_ptr->day < second_date_ptr->day)
      {
      ReturnResult = TRUE;
      }
   else if (first_date_ptr->day > second_date_ptr->day)
      {
      ReturnResult = FALSE;
      }
   /* same year, same month, and same date */
   else if (first_time_ptr->hour < second_time_ptr->hour)
      {
      ReturnResult = TRUE;
      }
   else if (first_time_ptr->hour > second_time_ptr->hour)
      {
      ReturnResult = FALSE;
      }
   /* same year, same month, same date, and same hour */
   else if (first_time_ptr->minute < second_time_ptr->minute)
      {
      ReturnResult = TRUE;
      }
   else if (first_time_ptr->minute > second_time_ptr->minute)
      {
      ReturnResult = FALSE;
      }
   /* same year, same month, same date, same hour, and same minute */
   else if (first_time_ptr->second < second_time_ptr->second)
      {
      ReturnResult = TRUE;
      }
   else if (first_time_ptr->second > second_time_ptr->second)
      {
      ReturnResult = FALSE;
      }
   /* same time */
   else 
      {
      ReturnResult = TRUE;
      }
 
   return(ReturnResult);
   }

/* FOR UNIT TEST ONLY */
#ifdef INCLUDE_UNIT_TEST
#include "xminint.ut"
#endif
/* FOR UNIT TEST ONLY */
