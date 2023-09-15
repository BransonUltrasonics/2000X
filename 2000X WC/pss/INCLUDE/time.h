/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\INCLUDE\time.h_v   1.1   Apr 06 1999 13:26:44   lmarkure  $ */
/* @(#) pSOSystem/68K V2.2.2: include/time.h (&U&) 2.3 97/02/26 11:01:15 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/time.h                                           */
/*   DATE:    97/02/26                                                 */
/*   PURPOSE: pREPC+ provided time manipulation functions              */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1997, Integrated Systems, Inc.           */
/*                      ALL RIGHTS RESERVED                            */
/*                                                                     */
/*   Permission is hereby granted to licensees of Integrated Systems,  */
/*   Inc. products to use or abstract this computer program for the    */
/*   sole purpose of implementing a product based on Integrated        */
/*   Systems, Inc. products.   No other rights to reproduce, use,      */
/*   or disseminate this computer program, whether in part or in       */
/*   whole, are granted.                                               */
/*                                                                     */
/*   Integrated Systems, Inc. makes no representation or warranties    */
/*   with respect to the performance of this computer program, and     */
/*   specifically disclaims any responsibility for any damages,        */
/*   special or consequential, connected with the use of this program. */
/*                                                                     */
/***********************************************************************/
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version
 1.1   04/06/99 LAM     added timer structures

*/

#if __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------*/
/* Don't allow this file to be included more than once.                */
/*---------------------------------------------------------------------*/
#ifndef _TIME_H
#define _TIME_H

#ifndef _SIZE_T_DEFINED
	#define _SIZE_T_DEFINED		1
	#if _SDS
		#define size_t  _size_t
	#else
		typedef unsigned int size_t;
	#endif
#endif

#ifndef _CLOCK_T_DEFINED
	#define _CLOCK_T_DEFINED	1
	typedef long clock_t;
#endif

#ifndef _TIME_T_DEFINED
	#define _TIME_T_DEFINED		1
	typedef long time_t;
#endif

#ifndef NULL
	#define NULL    0
#endif

/*---------------------------------------------------------------------*/
/* The following macro definition depends on a pSOS+ configuration     */
/* parameter. Need to #include <configs.h> to access this parameter.   */
/*---------------------------------------------------------------------*/
extern struct NodeConfigTable *anchor;
#define CLOCKS_PER_SEC	(anchor->psosct->kc_ticks2sec)

/*********************************************************************/ 
/*  Timer structures                                                 */
/*********************************************************************/ 

struct t_date        {
        UINT16 year;  /* Year, A.D. */
        UINT8 month; /* Month, 1->12 */
        UINT8 day;   /* Day, 1->31 */
};

struct t_time        {
        UINT16 hour;    /* Hour, 0->23 */
        UINT8 minute;  /* Minute, 0->59 */
        UINT8 second;  /* Second, 0->59 */
};

struct time_ds        {
        struct t_date date;    /* Date */
        struct t_time time;    /* Time */
        UINT32 ticks;   /* Current Elapsed Ticks Between Seconds */

};

struct tm
{
	int   tm_sec;		/* seconds after the minute - [0-61] */
	int   tm_min;		/* minutes after the hour - [0-59] */
	int   tm_hour;		/* hours since midnight - [0-23] */
	int   tm_mday;		/* day of the month - [1-31] */
	int   tm_mon;		/* months since January - [0-11] */
	int   tm_year;		/* years since 1900 */
	int   tm_wday;		/* days since Sunday - [0-6] */
	int   tm_yday;		/* days since January 1st - [0-365] */
	int   tm_isdst;		/* Daylight Saving Time flag */
};

/*---------------------------------------------------------------------*/
/* Function prototypes						       */
/*---------------------------------------------------------------------*/
char *asctime(const struct tm *timeptr);
char *ctime(const time_t *timer);
double difftime(time_t time1, time_t time0);
struct tm *gmtime(const time_t *timer);
struct tm *localtime(const time_t *timer);
time_t mktime(struct tm *timeptr);
size_t strftime(char *s, size_t maxsize, const char *format,
				const struct tm *timeptr);
time_t time(time_t *timer);

char *asctime_r(const struct tm *timeptr, char *buf, int buflen);
char *ctime_r(const time_t *timer, char *buf, int buflen);
struct tm *localtime_r(const time_t *timer, struct tm *resultp);

/*---------------------------------------------------------------------*/
/* The following functions are not supported and set ERR_UNIMPL errno. */
/*---------------------------------------------------------------------*/
clock_t clock(void);

#endif  /* _TIME_H */

#if __cplusplus
}
#endif
