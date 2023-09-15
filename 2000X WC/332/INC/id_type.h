/* $Header:   K:\APPS\PVCS Pro\332\INC\ID_TYPE.H_V   2.2   Apr 19 1999 15:37:58   ofingere  $ */
#ifndef IPS_ACTION_ID_TYPE_H
#define IPS_ACTION_ID_TYPE_H
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

   Module name: 

   Filename: id_type.h   

  -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
        0           03/13/96      Mark L      Initial
		2.2			04/19/99	  OFI		  Changed For DIAB
 ------------------------------- DESCRIPTION -----------------------------------


 ------------------------------ INCLUDE FILES ----------------------------------
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/

#define   NO_ACTION_ARG   0u
 
/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/ 


typedef enum
   {                    
   READ_SWARE_LOG_ENTRIES,
   CLEAR_SWARE_LOG_ENTRIES 
    }ACTION_ID_TYPE;
                                                           
                                                           
                                                           
/*                                                         
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/                                                         
                                                           
#endif /* IPS_ACTION_ID_TYPE_H */

