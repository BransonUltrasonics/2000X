/* $Header:   K:\APPS\PVCS Pro\332new\INC\WELD_MSG.H_V   2.3   May 10 1999 15:18:44   lmarkure  $ */

#ifndef WELD_DATA_MSG_H
#define WELD_DATA_MSG_H
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
    Revision#  Date      Author       Description
    =========  ========  ===========  ===========
       1       07/23/96  Lam          deleted unused functions    
       2.1     08/06/98  PaulG        Added include of weld_obj.h
	   2.2     05/10/99  LAM          added packed for DIAB


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



typedef __packed__(4,2) struct 
    {  
    COMMON_MSG_FIELD_TYPE common;             
    UINT16                word1;
    UINT16                word2;
    WELD_DATA             *weld_data_ptr;
    UINT32                lword3;
    } WELD_DATA_MSG;

#endif /*  WELD_STATE_MSG_H */
