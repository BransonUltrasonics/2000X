/* $Header:   L:/pvcs/1000/psos332/archives/inc/MAKEMENU.H_v   2.2   01 Aug 1996 14:49:14   BKYMER  $ */
#ifndef ASCII_MENU_CREATOR_H
#define ASCII_MENU_CREATOR_H

/*
------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: ASCII_MENU_CREATOR 

   Filename: ascii_menu_creator.h 


            Written by: 
                  Date:  
              Language:  "C"

------------------------------ REVISIONS ------------------------------------

  Revision #   Date       Author   Description
  ==========   ========   ======   ===========

----------------------------- DESCRIPTION -----------------------------------
  This file defines the interface to the executable function of the same
  name. 

---------------------------- INCLUDE FILES ----------------------------------
*/ 

#include "menutabl.h"           /* defines internal_menu_table structure */           

/*
----------------------------- DEFINES -------------------------------------
*/                                   

/*
------------------------ TYPE DECLARATIONS --------------------------------
*/ 
/* returned processing  status */
typedef packed enum
   {
   MENU_CREATE_OK = 0u,
   ASCII_SESSION_TERMINATED,
   DATA_EDIT_ERROR,
   MENU_ITEM_NOT_FOUND
   }  MENU_CREATION_STATUS_TYPE;
                         
typedef packed enum
   { 
   INITIALIZE_MENUS = 0u,
   CREATE_LEVEL1_MENU,
   CREATE_LEVEL2_MENU,
   CREATE_LEVEL3_MENU,
   CREATE_LEVEL4_MENU,
   CREATE_DATA_EDIT_MENU,
   CREATE_EXIT_DATA_EDIT_LEVEL2,
   CREATE_EXIT_DATA_EDIT_LEVEL3,
   CREATE_EXIT_DATA_EDIT_LEVEL4,
   GET_LEVEL1_MENU,
   GET_LEVEL2_MENU,
   GET_LEVEL3_MENU,
   REQUEST_MENU_NOT_FOUND = 0xff
   } REQUEST_MENU_LEVEL_TYPE;                                     

#endif /* ASCII_MENU_CREATOR_H */

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/  
MENU_CREATION_STATUS_TYPE 
     ascii_menu_creator(REQUEST_MENU_LEVEL_TYPE request_menu_level,    
                        INTERNAL_MENU_TABLE_TYPE *internal_menu_table); 
               
void ascii_menu_creator_init(void);
/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/    

