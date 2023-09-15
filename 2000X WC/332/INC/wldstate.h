/* $Header:   L:/pvcs/1000/psos332/archives/inc/wldstate.h_v   2.4   30 Jul 1997 09:49:12   BKYMER  $ */

#ifndef WELD_STATE_MSG_H
#define WELD_STATE_MSG_H
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

   Module name: WELD_STATE_MSG

   Filename: wldstate.h 

 -------------------------------- REVISIONS ------------------------------------

   Revision #  Date         Author            Description
   ==========  ========     ======            ===========
       0                    MarkL             Initial Version                   
       1        10/10/96    PaulG             Removed weld_state enum struct. 
       2        01/11/97    LAM               added end_weld_msg              
       2.4      07-24-97    BEKymer           New structure START_WELD_MSG for
                                              setup alarms


 ------------------------------- DESCRIPTION -----------------------------------


*/

/*
 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "commnmsg.h"
#include "state.h"  
#include "weld_obj.h"
/*
 ------------------------------- DEFINES ---------------------------------------
*/

								       

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/



typedef struct 
    {  
    COMMON_MSG_FIELD_TYPE common;             
    enum WELDSTATES       state;
    UINT16                weld_samples;
    WELD_OBJECT          *weld_object_ptr;
    UINT32                lword3;
    } WELD_STATE_MSG;

typedef struct 
    {  
    COMMON_MSG_FIELD_TYPE common;             
    enum WELDSTATES       state;
    UINT16                weld_samples;
    WELD_DATA             *weld_data_ptr;
    UINT32                lword3;
    } END_WELD_MSG;

typedef struct 
    {  
    COMMON_MSG_FIELD_TYPE common;             
    enum WELDSTATES       state;
    UINT16                weld_samples;
    SETUP_DATA_ALARMS     *setup_data_ptr;
    UINT32                lword3;
    } START_WELD_MSG;

#endif /*  WELD_STATE_MSG_H */
