/* $Header:   L:/pvcs/1000/psos332/archives/inc/TESTTYPE.H_v   2.1   01 Aug 1996 14:51:58   BKYMER  $ */
#ifndef TEST_TYPE_H
#define TEST_TYPE_H
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

   Revision #      Date          Author          Description
   ==========      ========      ======          ===========
      0            12/12/94      Mark Lazarewicz Initial release 


 ------------------------------- DESCRIPTION -----------------------------------

  This is the diagnostic test result type

 ------------------------------ INCLUDE FILES ----------------------------------
*/


/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef enum
   {
   TEST_PASSED,
   TEST_FAILED
   } TEST_RESULT_TYPE;


#endif /* TEST_TYPE_H */
