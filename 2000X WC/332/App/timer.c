/* $Header:   L:/pvcs/1000/psos332/archives/app/timer.c_v   2.9   23 Jan 1998 13:44:42   BKYMER  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Timer                                                       */
/*                                                                          */
/* Filename:    Timer.c                                                     */
/*                                                                          */
/* Function Name: Timer functions for inside the 1 ms interrupt             */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   03-22-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date      Author    Description                              */
/*  =========  ========  ========  ===========                              */
/*     0       03-22-96  BEKymer   Convert to run under pSOS                */
/*     1       05-13-96  BEKymer   Add proper function prototyping          */
/*     2       07-15-96  BEKymer   Add timers to count up                   */
/*     3.2.4   06-06-97  BEKymer   Created a SystemTimer for everyones use  */
/*     2.6     09-15-97  BEKymer   Modify ValidateLinkedList                */
/*                                 Remove call to ValidateLinkList in       */
/*                                 InitTimer                                */
/*                                 Code add in al up timer routines to      */
/*                                 check for array bounds                   */
/*     2.61    01-21-98  BEKymer   Remove stack checking code               */
/*     2.9     01-23-98  BEKymer   Add CallerID to ValidateLinkedList call  */
/*                                 Fix code so ValidateLinkedList doesn't   */
/*                                 fail every cycle                         */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*----------------------------- DESCRIPTION --------------------------------*/

/* This module contains the timer functions to be used from within the 1 ms */
/* interrupt only.  It has a resolution of 1 ms.                            */



/*----------------------------- PSEUDO CODE --------------------------------*/



/*---------------------------- LOCAL_EQUATES -------------------------------*/

#define NMBR_TIMERS  25          /* Number of timers is one less  */
#define AVAILABLE    256
#define ENDLIST      -1



/*------------------------------ INCLUDES ----------------------------------*/

#include "portable.h"
#include "error.h"
#include "state.h"



/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

#include "timer.h"



/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

typedef struct timers {
   UINT16  Junk1;                 /* Take up space so exactly 16.. */
   UINT16  time;                  /* Timer value                   */
   BOOLEAN *flag;                 /* Pointer to user defined flag  */
   SINT16  Nptr;                  /* Pointer to next item in list  */
   SINT16  Pptr;                  /* Pointer to previous item      */
   UINT16  Junk2;                 /* ...bytes are used so the EST  */
   UINT16  Junk3;                 /* memory command can be used.   */
   } TIMER;


typedef struct uptimers {
   SINT32  Time;
   BOOLEAN State;                 /* FALSE:timer stop   TRUE:timer running */
   } UPTIMER;


TIMER   TimerStruct[NMBR_TIMERS];  /* An array of timer things      */
UPTIMER UpTimerStruct[TIMERX];     /* An array of count up timers   */


UINT16  TimerCount;
UINT16  TimerIntProblem = 0;
UINT16  _5msCounter;

BOOLEAN TimerLock = FALSE;
BOOLEAN _5msFlag;

UINT16  CycleTimer, TimerCount;

UINT32  SystemTimer;

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/



/*-------------------------------- CODE ------------------------------------*/


UINT16 GetCycleTime(void)
{
   return(CycleTimer);
}




void ValidateLinkedList(UINT16 CallerID)
/***************************************************************************/
/*                                                                         */
/*  This function will validate the time linked list.  The function will   */
/*  start at the top of the list and work its way through the list.  If    */
/*  the Nptr is invalid an attempt to fix is done.                         */
/*                                                                         */
/***************************************************************************/
{
   UINT16  TestPtr = 0;
   BOOLEAN ExitLoop = FALSE, OkayFlag = TRUE;

   if (CallerID > NMBR_TIMERS) while(1);
   while (ExitLoop == FALSE) {
      if (TestPtr >= NMBR_TIMERS) {             /* This should never happen */
         ExitLoop = TRUE;
         OkayFlag = FALSE;
      }
      if (TimerStruct[TestPtr].Nptr == ENDLIST) {      /* This would be okay*/
         ExitLoop = TRUE;
      }
      else {
         if (TimerStruct[TestPtr].Nptr == AVAILABLE) {      /* Not good     */
            OkayFlag = FALSE;
            ExitLoop = TRUE;
         }
         else {
            TestPtr = TimerStruct[TestPtr].Nptr;
         }
      }
   }
   if (OkayFlag == FALSE) {          /* Well did everything pass our tests */
      InitTimer();                   /* Attempt to fix                     */
   }
}



void InitTimer(void)
/***************************************************************************/
/*                                                                         */
/* Flag will point to a location which will be TRUE while the timer is     */
/* still counting and will go to FALSE when the timer has timed out.  If   */
/* the time passed is zero then the flag location will be set TRUE all the */
/* time.                                                                   */
/*                                                                         */
/***************************************************************************/
{
   UINT16 x;

   for (x = 1; x < NMBR_TIMERS; x++) {
      TimerStruct[x].Junk1 = x;             /* Set to index # (debugging)  */
      TimerStruct[x].time = 0;              /* Set all time values to 0    */
      TimerStruct[x].flag = 0;              /* Set pointers to flag to null*/
      TimerStruct[x].Nptr = AVAILABLE;      /* Make index available        */
      TimerStruct[x].Pptr = AVAILABLE;      /* Make index available        */
      TimerStruct[x].Junk2 = 0;             /* Set to zero for now         */
   }
   TimerStruct[0].Nptr = ENDLIST;           /* Set DelayHead to ENDLIST    */
   ValidateLinkedList(1);
   SystemTimer = 0;
}



SINT16 StartTimer(UINT16 PassedTime, BOOLEAN *Flag, UINT16 Use)
/***************************************************************************/
/*                                                                         */
/* Flag will point to a location which will be TRUE while the timer is     */
/* still counting and will go to FALSE when the timer has timed out.  If   */
/* the time passed is zero then the flag location will be set FALSE all    */
/* the time.                                                               */
/*                                                                         */
/* TimerLock will be set TRUE while inside this function.  The UpdateTimer */
/* function should not mess around with the time structure while this flag */
/* is set TRUE.                                                            */
/*                                                                         */
/* The return value will be the index of which timer will be used or the   */
/* value FAILED if no timers are available or if the time required is 0.   */
/*                                                                         */
/*                                                                         */
/* How this function works:                                                */
/*                                                                         */
/*     The first while loop cycles through the entire time structure until */
/* an available element is found.  An element is available when the member */
/* .Nptr is set to AVAILABLE.  When an element is found the argument flag  */
/* is put into the member flag, the flag is set TRUE and the RetVal is set */
/* to the index value selected.  The value index will be used in the next  */
/* loop.  If no members are AVAILABLE then the RetVal is set to FAILED and */
/* no further action is taken.                                             */
/*                                                                         */
/*     The variable Difference is set equal to the passed time value.      */
/* Ptr0 is set equal to the delay head (which is time[0].time).  Ptr1 is   */
/* set to 0.  The while loop executes until ptr0 equals ENDLIST or         */
/* Difference is less then zero.  The proper place to insert a new time    */
/* is either at the end of the list or when the sum of the previous times  */
/* do not exceed the new time value.  The while loop has ptr0, ptr1,       */
/* OldDifference and Difference keeping track of where the procedure is    */
/* in the loop, while searching for the proper place to insert the new     */
/* time.  The existing times are sequentially subtracted from the remains  */
/* of the new time according in the link-listed order until the end of the */
/* list or a negative result is encountered indicating that the proper     */
/* insertion point has been reached.  At this point ptr0 contains the      */
/* element number to be assigned to TimerStruct[index].Nptr.  Ptr1 con-    */
/* tains the element number immediately preceding the new time.  If ptr0   */
/* equals ENDLIST it means that the new time is larger than any of the     */
/* other times and therefore should go at the end of the list and          */
/* TimerStruct[index].  Time is set equal to the Difference.  If ptr0 is   */
/* not ENDLIST then if ptr0 equals ptr1 (indicating that there were not    */
/* any times previously listed).  Then TimerStruct[ptr1].Nptr is set to    */
/* ENDLIST.  Time[index].time is set equal to the OldDifference and        */
/* TimerStruct[ptr0].time is set equal to the negative of Difference       */
/* which at this point is negative, resulting in a positive number.        */
/*                                                                         */
/***************************************************************************/
{
   BOOLEAN ExitFlag = FALSE;
   UINT16  NewIndex;
   SINT16  RetVal = FAILED1;
   SINT16  ptr0, ptr1;
   SINT16  Difference, OldDifference;
   UINT16  SafetyCounter = 0;

   if (TimerLock == FALSE) {   /* If already TRUE then we were interrupted */
      TimerLock = TRUE;
      if (PassedTime == 0) {   /* Damn, time requested is 0, what is that  */
         RetVal = FAILED2;     /* programmer thinking                      */
         *Flag = FALSE;
      }
      else {
         NewIndex = 1;
         while (ExitFlag == FALSE) {
//            if (TimerStruct[NewIndex].Nptr == AVAILABLE) {
            if (TimerStruct[NewIndex].Pptr == AVAILABLE) {
               TimerStruct[NewIndex].flag = Flag;
               TimerStruct[NewIndex].Junk2 = Use;
        	      ExitFlag = TRUE;
               RetVal = NewIndex;
               *Flag = TRUE;
            }
            else if (++NewIndex >= NMBR_TIMERS) {
               ExitFlag = TRUE;
               *Flag = FALSE;
            }
         }
         if (RetVal != FAILED1) {
            Difference = PassedTime;
            ptr0 = TimerStruct[0].Nptr;
            ptr1 = 0;
            while ((ptr0 != ENDLIST) && (Difference > 0)) {
               if (++SafetyCounter > NMBR_TIMERS) break;
               OldDifference = Difference;
               Difference -= TimerStruct[ptr0].time;
               if (Difference > 0) {
                  ptr1 = ptr0;
                  ptr0 = TimerStruct[ptr1].Nptr;
               }
            }
            TimerStruct[NewIndex].Nptr = ptr0;
            TimerStruct[ptr1].Nptr = NewIndex;
            TimerStruct[NewIndex].Pptr = ptr1;
            if (ptr0 == ENDLIST) {
               TimerStruct[NewIndex].time = Difference;
            }
            else {
               TimerStruct[ptr0].Pptr = NewIndex;
               if (ptr0 == ptr1) TimerStruct[ptr1].Nptr = ENDLIST;
               TimerStruct[NewIndex].time = OldDifference;
               TimerStruct[ptr0].time = -Difference;
            }
         }
      }
      TimerLock = FALSE;
   }
   ValidateLinkedList(2);
   return(RetVal);
}



BOOLEAN UpdateTimers(void)
/***************************************************************************/
/*                                                                         */
/* This function will decrement all timers when called.  If any timers     */
/* expire, then the proper flag will be set to FALSE.  This function       */
/* should be called from within the 1 ms timer interrupt.                  */
/*                                                                         */
/* The flag _5msFlag will be set TRUE every five calls (should be every    */
/* 5 ms).                                                                  */
/*                                                                         */
/* If the TimerLock flag is set then the timers will not be decremented    */
/* this time through (because someone is in the middle of rearranging the  */
/* linked-list).  The variable TimerCount will keep tack of this fact and  */
/* subtract an extra count the next time in.                               */
/*                                                                         */
/* The return value will indicate TRUE if the timers were updated this     */
/* time through (TimerLock == FALSE) and FALSE if the timers were not      */
/* updated (TimerLock == TRUE).                                            */
/*                                                                         */
/***************************************************************************/
{
   SINT16  OldPtr;
   BOOLEAN RetVal = TRUE;

   CycleTimer++;
   IncrementUpTimer();
   SystemTimer++;
   TimerCount++;

   if (TimerLock == FALSE) {
      if (TimerStruct[0].Nptr != ENDLIST) {    /* Make sure at least 1 timer running */
         if (TimerStruct[TimerStruct[0].Nptr].time > TimerCount) {
            TimerStruct[TimerStruct[0].Nptr].time -= TimerCount;
         }
         else {
            TimerStruct[TimerStruct[0].Nptr].time = 0;
         }
         TimerCount = 0;
         while ((TimerStruct[0].Nptr != ENDLIST) && (TimerStruct[TimerStruct[0].Nptr].time <= 0)) {
           OldPtr = TimerStruct[0].Nptr;                   /* Old Delay Head */
           *TimerStruct[OldPtr].flag = FALSE;
           TimerStruct[OldPtr].flag = 0;
           TimerStruct[0].Nptr = TimerStruct[OldPtr].Nptr; /* New Delay Head */

/*--  If Old Delay Head is pointing to ENDLIST, timer list is empty  --*/

           if (TimerStruct[OldPtr].Nptr == ENDLIST) {
              TimerStruct[0].Nptr = ENDLIST;
           }
           if (OldPtr != ENDLIST) {
              if ((OldPtr < 0) || (OldPtr > NMBR_TIMERS)) {
                 LogError(IDXRANGE);        /* Index out of range !! */
              }
              else {
                 TimerStruct[OldPtr].Nptr = AVAILABLE;
                 TimerStruct[OldPtr].Pptr = AVAILABLE;
                 ValidateLinkedList(3);
              }
            }
         }
      }
   }
   else RetVal = FALSE;
   return(RetVal);
}



void StopTimer(UINT16 Id)
/***************************************************************************/
/*                                                                         */
/* This function will remove a timer from the timer linked list.  The arg- */
/* ument is the index of the timer to remove.  If the timer already        */
/* expired, or is not running, or is not part of the linked list then NO   */
/* action will be taken.                                                   */
/*                                                                         */
/* This function should not be called if TimerLock is set to TRUE.         */
/*                                                                         */
/***************************************************************************/
{
   TimerStruct[0].Junk1 = Id;          /* Save ID in element 0 (debugging) */
   if (TimerLock == FALSE) {
      TimerLock = TRUE;
      if ((Id > 0) && ( Id < NMBR_TIMERS)) {
         if (TimerStruct[Id].Nptr != AVAILABLE) {       /* Make sure its valid*/
            if (TimerStruct[Id].Nptr == ENDLIST) {      /* Last one in list ? */
               TimerStruct[TimerStruct[Id].Pptr].Nptr = ENDLIST;
            }
            else {                                      /* No, in middle      */
               TimerStruct[TimerStruct[Id].Nptr].Pptr = TimerStruct[Id].Pptr;
               TimerStruct[TimerStruct[Id].Pptr].Nptr = TimerStruct[Id].Nptr;
               TimerStruct[TimerStruct[Id].Nptr].time += TimerStruct[Id].time;
            }
            TimerStruct[Id].Pptr = AVAILABLE;
            TimerStruct[Id].Nptr = AVAILABLE;
            *TimerStruct[Id].flag = FALSE;
            TimerStruct[Id].flag = 0;
            if (TimerStruct[0].Nptr == Id) {    /* If this is TRUE, then we */
               TimerStruct[0].Nptr = ENDLIST;   /* have nothing left in list*/
            }
         }
      }
      ValidateLinkedList(4);
      TimerLock = FALSE;
   }
}


void  LogError(enum ERRORCODES ErrorCode)
{
   ErrorCode++;  /* Used just to eliminate compiler warning */
}



/*-----  This section below will deal with up timers  -----*/

void IncrementUpTimer(void)
/****************************************************************************/
/*                                                                          */
/*  This function will do the incrementing of all the up timers.            */
/*                                                                          */
/****************************************************************************/
{
   UINT16   Index;

   for (Index = 0; Index < TIMERX; Index++) {
      if (UpTimerStruct[Index].State == TRUE) {
         UpTimerStruct[Index].Time++;
      }
   }
}



void ResetUpTimer(enum UPTIMERS TimerID)
/****************************************************************************/
/*                                                                          */
/*  This function will set the passed timer to 0 and stop the timer.        */
/*                                                                          */
/****************************************************************************/
{
   if (TimerID < TIMERX) {
      UpTimerStruct[TimerID].Time = 0;
      UpTimerStruct[TimerID].State = FALSE;
   }
}



void StartUpTimer(enum UPTIMERS TimerID)
/****************************************************************************/
/*                                                                          */
/*  This function will start the passed timer and reset it to 0.            */
/*                                                                          */
/****************************************************************************/
{
   if (TimerID < TIMERX) {
      UpTimerStruct[TimerID].Time = 0;
      UpTimerStruct[TimerID].State = TRUE;
   }
}



void ReStartUpTimer(enum UPTIMERS TimerID)
/****************************************************************************/
/*                                                                          */
/*  This function will restart the passed timer from where it is.           */
/*                                                                          */
/****************************************************************************/
{
   if (TimerID < TIMERX) {
      UpTimerStruct[TimerID].State = TRUE;
   }
}



void StopUpTimer(enum UPTIMERS TimerID)
/****************************************************************************/
/*                                                                          */
/*  This function will stop the passed timer.                               */
/*                                                                          */
/****************************************************************************/
{
   if (TimerID < TIMERX) {
      UpTimerStruct[TimerID].State = FALSE;
   }
}



SINT32 GetUpTimer(enum UPTIMERS TimerID)
/****************************************************************************/
/*                                                                          */
/*  This function will return the value of the passed timer.                */
/*                                                                          */
/****************************************************************************/
{
   SINT32 Retval = 0;

   if (TimerID < TIMERX) {
      Retval = (UpTimerStruct[TimerID].Time);
   }
   return(Retval);
}
