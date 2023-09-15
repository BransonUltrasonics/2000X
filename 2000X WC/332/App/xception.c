/* $Header:   K:\APPS\PVCS Pro\332new\App\XCEPTION.C_V   2.7   Dec 17 1999 10:08:26   lmarkure  $ */
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
 --------------------------------- MODULE DESCRIPTION ------------------------------------

   Module  name: EXCEPTION_HANDLER  

   Filename: xception.c  

   Function name:  exception_handler


            Written by: Mark Lazarewicz  
                  Date: 1/20/96 
              Language:  "C"

 ------------------------------------- REVISIONS -----------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            1/20/96       Mark L      Initial Version
      1            03/30/97      LAM         welddata test
      2.2.4        06/16/97      LAM         added interrupt routines
      2.6          04/26/99      OFI         Changed for Diab
      2.7          12/16/99      LAM         removed code for logging errors
 ------------------------------------ DESCRIPTION ----------------------------------------
                                                           
   This function handlers the exception by performing a reduced reset sequence.
                     
 ------------------------------------ PSEUDO CODE ----------------------------------------

   

----------------------------------- INCLUDE FILES ---------------------------------------
*/

#include <psos.h>
#include "run_task.h"
#include "332.h"
#include "battram.h"
#include "time.h"
#include "xception.h"
#include "xminint.h"


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

/*
 ----------------------------------- LOCAL DEFINES ---------------------------------------
*/

#define EXCEPTION_TIME_INTERVAL   10       /* minutes */
#define NO_EXCEPTIONS             0
#define MAX_ALLOWABLE_EXCEPTIONS  6

#define INTERRUPT_MASK            0x700
#define NEW_MODE                  0x700
#define THIS_TASK                 0


/*
 ------------------------------- LOCAL TYPE DECLARATIONS ---------------------------------
*/
typedef struct
   {                                                                          
   UINT16                warm_start;         /*\                                        */
   UINT16                ram_size;           /* \    Mucked with by hw_boot.asm         */
   UINT16                start_mode;         /*   =  i.e., must coordinate with         */ 
   UINT16                exception_count;    /* /                   */
   } PRESERVED_BATTRAM_TYPE;
 

/*
 ------------------------------- GLOBAL DATA -----------------------------------
                        (scope is global to ALL files)
*/

UINT16 AddressCount = 0;
UINT16 ReservedCount = 0;
UINT16 ZeroCount = 0;

/*
 ---------------------------- PRIVATE GLOBAL DATA ------------------------------
                        (scope is global to THIS file)
*/
static struct t_date    InitialExceptionDate;
static struct t_time    InitialExceptionTime;

static PRESERVED_BATTRAM_TYPE START_RAM;
/*
 ---------------------------------- CODE ---------------------------------------
*/
   
void exception_handler (void)
   {
   UINT32                  OldMode;
   UINT32                  OldPriority;

   struct t_date           CurrentDate;            
   struct t_time           CurrentTime;
   UINT32                  Ticks = 0;                      /* the Ticks parameter for tm_get           */
   BOOLEAN                 TimeDifference;

   /*
    * Set this task priority to the highest
    */
   t_setpri( THIS_TASK, FATAL_ERROR_PRIORITY, &OldPriority);

   /*
    * set interrupt mask level in root's mode to disable further interrupt activity
    */
   t_mode (INTERRUPT_MASK, NEW_MODE, &OldMode);


   /*
    * If we are currently running the full application then we must check to see if the
    * exceptions are occurring too frequently to continue. If too many exceptions
    * occur within the designated period then we'll force the system to run in minimal
    * mode.
    */
   if ( START_RAM.start_mode != START_MINIMAL_APP )
      {

      /*
       * Increment the number of exceptions
       */
      (START_RAM.exception_count)++;

      /*
       * If this is the first exception then reset the InitialExceptionTime
       */
      if ( START_RAM.exception_count == 1 )
         {
         InitialExceptionDate = CurrentDate;
         InitialExceptionTime = CurrentTime;
         }
      else
         {
         /*
          * check for the time difference from the InitialExceptionTime
          */
         TimeDifference = WithinXMinInterval (EXCEPTION_TIME_INTERVAL,
                                                  InitialExceptionDate,
                                                  InitialExceptionTime,
                                                  CurrentDate,
                                                  CurrentTime);
                                               
         /*
          * If the TimeDifference is greater than 10 min then start a new
          * interval
          */
         if (TimeDifference == FALSE)
            {
            START_RAM.exception_count = 1;
         
            InitialExceptionDate = CurrentDate;
            InitialExceptionTime = CurrentTime;
            }
      
         /*
          * If it is less than 10 minutes then force the system to run in minamal mode
          */
         else
            {
            if (START_RAM.exception_count > MAX_ALLOWABLE_EXCEPTIONS)
               { 
               START_RAM.start_mode = START_MINIMAL_APP;
               }
            }
         }
      }

   /*
    * Set the timeout to be a short one and then
    * wait for reset
    */


   while (FOREVER)
      {
      ;
      }

   return;
   }


void BusInt(void)
{
   AddressCount++;
}

void AddInt(void)
{
   AddressCount++;
}

void SpurInt(void)
{
   AddressCount++;
}

void IllegalInstr(void)
{
   AddressCount++;
}

void CHKCHK2(void)
{
   ReservedCount++;
}

void ZeroDivide(void)
{
   ZeroCount++;
}

void TRAPccTRAPv(void)
{
   ReservedCount++;
}

void PrivilegeVio(void)
{
   ReservedCount++;
}

void Vector10Int(void)
{
   ZeroCount++;
}

void ReservedInt(void)
{
   ReservedCount++;
}

void UserInt(void)
{
   ReservedCount++;
}

BOOLEAN IsStartModeMinMode(void)
{
 BOOLEAN flag = TRUE;

 if(START_RAM.start_mode != START_MINIMAL_APP)
   (flag = FALSE);

 return(flag);
}
  
  
  
  /* FOR UNIT TEST ONLY */
#ifdef INCLUDE_UNIT_TEST
#include "xception.ut"
#endif
/* FOR UNIT TEST ONLY */
