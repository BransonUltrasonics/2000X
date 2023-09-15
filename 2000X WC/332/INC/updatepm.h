/* $Header:   L:/pvcs/1000/psos332/archives/inc/UPDATEPM.H_v   2.1   01 Aug 1996 14:47:56   BKYMER  $ */
#ifndef UPDATE_PARAMETER_MSG_H
#define UPDATE_PARAMETER_MSG_H
       
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name: UPDATE_PARAMETER_MSG

   Filename: updatepm.h 


            Written by: Mark Lazarewicz
                  Date: 03/14/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author           Description
   ==========      ========      ===========      ==============
       0           03/14/96      Mark L           Initial Version

 ------------------------------- DESCRIPTION -----------------------------------
 This message is sent by parameter_manager to specific tasks that use a 
 parameter that has changed value.

*/

/*
 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "commnmsg.h"  
#include "parametr.h"
#include "pm2ascii.h"

//#include "paramngr.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

                                                                               

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/

typedef struct 
    {  
    COMMON_MSG_FIELD_TYPE common;             
    PARAMETER_ID_TYPE     parameter;
    PARAMETER_VALUE_TYPE  value; 
    UINT16                spare_1;
    } UPDATE_PARAMETER_MSG;

#endif /*  UPDATE_PARAMETER_MSG_H */
