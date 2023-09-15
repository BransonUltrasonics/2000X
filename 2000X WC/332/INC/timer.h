/* $Header:   L:/pvcs/1000/psos332/archives/inc/timer.h_v   2.3   23 Jan 1998 13:49:28   BKYMER  $ */


/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date      Author    Description                              */
/*  =========  ========  ========  ===========                              */
/*     2.3     01-23-98  BEKymer   Add CallerID paramter to ValidateLink... */
/*                                                                          */
/*                                                                          */




#include "error.h"


enum  UPTIMERS { /* This group of timer timers will be used for counting up */
   CYCLETIMER=1,        /* Cycle time starting with clearing upper limit    */
   SONICSTIMER,         /* Sonics on time from trigger                      */
   VELOCITYTIMER,       /* Timer used to calculate downstroke velocity      */
   TRIGGERLOSTTIMER,    /* Timer used to determine if trigger really lost   */
   TIMER1,              /* Extra timer                                      */
   TIMER2,              /* Extra timer                                      */
   TIMERX };            /* Last entry in timer list                         */


/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

UINT16  GetCycleTime(void);
void    ValidateLinkedList(UINT16 CallerID);
void    InitTimer(void);
SINT16  StartTimer(UINT16 PassedTime, BOOLEAN *Flag, UINT16 Use);
BOOLEAN UpdateTimers(void);
void    StopTimer(UINT16 Id);
void    LogError(enum ERRORCODES ErrorCode);

void   IncrementUpTimer(void);
void   ResetUpTimer(enum UPTIMERS TimerID);
void   StartUpTimer(enum UPTIMERS TimerID);
void   ReStartUpTimer(enum UPTIMERS TimerID);
void   StopUpTimer(enum UPTIMERS TimerID);
SINT32 GetUpTimer(enum UPTIMERS TimerID);
