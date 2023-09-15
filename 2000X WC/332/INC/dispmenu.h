/* $Header:   L:/pvcs/1000/psos332/archives/inc/DISPMENU.H_v   2.1   01 Aug 1996 14:50:08   BKYMER  $ */
#ifndef DISPLAY_MENU_SEQUENCER_H
#define DISPLAY_MENU_SEQUENCER_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: DISPLAY_MENU_SEQUENCER

   Filename: dispmenu.h 


            Written By: Mark Lazarewicz
                  Date: 03/22/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

  Revision #   Date       Author   Description
  ==========   ========   ======   ===========
      0        03/22/96   Mark L   Initial Version

 ------------------------------- DESCRIPTION -----------------------------------
  This file defines the interface to the executable function of the same
  name. 

 ------------------------------ INCLUDE FILES ----------------------------------
*/ 
#include "root.h"               /* system start up type  */
#include "fpmenuty.h"       /* front panel menu type */           

/*
 --------------------------------- DEFINES -------------------------------------
*/                                   
/* option text string length */    

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/ 
/* returned processing  status */
typedef packed enum
   {
   VALID_MENU_ITEM_FOUND = 0u,
   VALID_MENU_ITEM_NOT_FOUND,
   VALID_MENU_ITEM_DOES_NOT_EXIST,
   NO_UP_DOWN_MENU_ITEM,
   NO_IN_MENU_ITEM,
   NO_OUT_MENU_ITEM, 
   MENU_ITEM_IS_HIDDEN,
   NO_INITIAL_MENU_ITEM_VALUE
   }  DISPLAY_MENU_REQUEST_STATUS_TYPE;
                         
typedef packed enum
   { 
   GET_NEXT_MENU = 0u,
   GET_PRIOR_MENU,
   GET_IN_LEVEL_MENU,
   GET_OUT_LEVEL_MENU,
   GET_PRESENT_MENU,
   GET_STATION_MENU,
   GET_RECEIVE_AUDIO_MENU,
   GET_TRANSMIT_MENU,
   GET_ALARM_DISPLAY_MENU,
   GET_ALARM_SET_MENU,
   GET_ALIGNMENT_MENU,
   GET_SERVICE_MENU,
   GET_STATUS_MENU,
   GET_CONFIGURATION_MENU,
   GET_ACCESS_DISABLE_MENU,
   GET_OPTION_ONE_MENU,
   GET_OPTION_TWO_MENU,
   SET_CH_FREQS_READ_WRITE,
   SET_CH_FREQS_READ_ONLY
   } DISPLAY_MENU_REQUEST_TYPE;                                     



typedef enum
   {
   INIT_MENUS,
   INIT_MENUS_WITH_FREQS_READ_ONLY,
   INIT_MENUS_WITH_FREQS_READ_WRITE
   } MENU_INIT_REQUEST_TYPE;   



/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/  
DISPLAY_MENU_REQUEST_STATUS_TYPE 
     display_menu_sequencer(DISPLAY_MENU_REQUEST_TYPE menu_request,    
                            FP_MENU_TYPE             **menu_information); 
               

SYS_STARTUP_STATUS_TYPE 
     display_menu_sequencer_init(MENU_INIT_REQUEST_TYPE init_request);

                                   
/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/    

#endif /* DISPLAY_MENU_SEQUENCER_H */
