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


#define ACTRETBIT      (char)BIT0
#define UNUSEDBIT      (char)BIT1
#define SVBIT          (char)BIT2
#define REJECTBIT      (char)BIT3
#define SUSPECTBIT     (char)BIT4
#define SYSFAULTBIT    (char)BIT5
#define PWROFFBIT      (char)BIT6
#define UNUSED1BIT     (char)BIT7

#define EXTTRIGBIT     (char)BIT0
#define STARTBIT       (char)BIT1
#define DISPLAYLOCKBIT (char)BIT2
#define EXTRESETBIT    (char)BIT3
#define USERIN1BIT     (char)BIT4
#define USERIN2BIT     (char)BIT5
#define USERIN3BIT     (char)BIT6
#define CYCLEABORTBIT  (char)BIT7

#define GENALARMBIT    (char)BIT0
#define READYBIT       (char)BIT1
#define WELDONBIT      (char)BIT2
#define UNUSED2BIT     (char)BIT3
#define USEROUT1BIT    (char)BIT4
#define USEROUT2BIT    (char)BIT5
#define USEROUT3BIT    (char)BIT6
#define UNUSED3BIT     (char)BIT7



Port8255 Alarm;


