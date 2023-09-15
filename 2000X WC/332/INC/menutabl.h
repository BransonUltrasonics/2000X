/* $Header:   L:/pvcs/1000/psos332/archives/inc/MENUTABL.H_v   2.2   01 Aug 1996 14:51:10   BKYMER  $ */
#ifndef INTERNAL_MENU_TABLE_TYPE_H
#define INTERNAL_MENU_TABLE_TYPE_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name:  Internal_Menu_Table_Type

   Filename: internal_menu_table_type.h 


            Written by: 
                  Date:  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========

 ------------------------------- DESCRIPTION -----------------------------------
   This file contains the structure of the internal_menu_table and the external_ascii_display
   that is used by the Ascii_Diagnostics_State_Coordinator and the Ascii_menu_Creator modules.

 ------------------------------ INCLUDE FILES ----------------------------------
*/
                                                                          
#include "fpmenuty.h"            	         /* defines for title and menu_item_type */
#include "mcnstruc.h"                      /* define for menu_item     */

/*
 --------------------------------- DEFINES -------------------------------------
*/
                                       
#define MAX_NUM_MENU_ITEMS      34

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/                    

typedef struct
   {  
   CONSTRUCTED_MESSAGE_DISPLAY_TYPE 	menu_item[MAX_NUM_MENU_ITEMS];
   CONSTRUCTED_MESSAGE_DISPLAY_TYPE 	title;  
   MENU_ITEM_TYPE               menu_item_type;
   UINT8                        num_menu_items;
   UINT8                      	 present_menu_item;
   } INTERNAL_MENU_TABLE_TYPE;   

#endif /* INTERNAL_MENU_TABLE_TYPE_H */
