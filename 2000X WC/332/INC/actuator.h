/* $Header:   L:/pvcs/1000/psos332/archives/inc/ACTUATOR.H_v   2.1   01 Aug 1996 14:51:48   BKYMER  $ */
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
/*                                                                          */
/*                          History of changes                              */
/*                          ------------------                              */
/*                                                                          */
/* Rev  Who Date     Description of change                                  */
/* ---- --- -------- ------------------------------------------------------ */
/*                                                                          */


#define RUNBIT         (char)BIT0
#define SEEKBIT        (char)BIT1
#define MEMSTOREBIT    (char)BIT2
#define MEMCLRBIT      (char)BIT3
#define OLINBIT        (char)BIT4
#define PWRONBIT       (char)BIT5
#define PWROFFBIT      (char)BIT6
#define MISSPARTINBIT  (char)BIT7

#define EXTSEEKBIT     (char)BIT0
#define RUNSONICBIT    (char)BIT1
#define OLRESETBIT     (char)BIT2
#define TESTBIT        (char)BIT3
#define SV1BIT         (char)BIT4
#define SV2BIT         (char)BIT5
#define SV3BIT         (char)BIT6
#define SV4BIT         (char)BIT7

#define INTLLSBIT      (char)BIT0
#define ULSBIT         (char)BIT1
#define TRIGSWBIT      (char)BIT2
#define EXTLLSBIT      (char)BIT3
#define PB1BIT         (char)BIT4
#define PB2BIT         (char)BIT5
#define ESTOPBIT       (char)BIT6
#define UNUSEDBIT      (char)BIT7


Port8255 Actuator;



