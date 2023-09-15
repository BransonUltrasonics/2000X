/* $Header:   L:/pvcs/1000/psos332/archives/inc/FPMENUTY.H_v   2.1   01 Aug 1996 14:49:52   BKYMER  $ */
#ifndef FP_MENU_TYPE_H
#define FP_MENU_TYPE_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name:fp_menu_type 

   Filename: fpmenuty.h 


            Written by: Mark Lazarewicz
                  Date: 01/31/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
        0           01/31/96      Mark L      Initial Version

 ------------------------------- DESCRIPTION -----------------------------------
   This file contains the structure of the a single fp menu item.

 ------------------------------ INCLUDE FILES ----------------------------------
*/
                                                                          
#include "parametr.h"            /* parameter id type*/

/*
 --------------------------------- DEFINES -------------------------------------
*/                                       
#define MAX_ITEM_NAME_LENGTH      26
#define MAX_OPTION_TEXT_CHARS     26

#define FIRST_DISPLAY_ATTRIBUTES  0
#define MAX_DISPLAY_ATTRIBUTES    8
/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/                    

typedef packed enum
   {
   MENU_TYPE = 0u,
   OPTION_TYPE,
   INTEGER_TYPE,
   FLOAT_TYPE,
   STRING_TYPE,
   ALARM_TYPE,
   MAIN_MENU_TYPE
   } MENU_ITEM_TYPE;     

typedef char ITEM_NAME_STRING_TYPE[MAX_ITEM_NAME_LENGTH];

typedef packed struct
   {
   UINT8 wedlck : 1,
         c_net  : 1,
         drc    : 1,
         trc    : 1,
         lcod   : 1,
         local  : 1,
         spare  : 2;
   } STATION_CONFIGURATION_INCLUSION_TYPE;

typedef packed enum
   {
   DISPLAY_ITEM_NAME = 0u,
   DISPLAY_COMMON_WORD,
   DISPLAY_DATA_VALUE,
   END_OF_DISPLAY_ATTRIBUTES
   } DISPLAY_OBJECT_TYPE;

typedef packed enum
   {
   DISPLAY_ALWAYS = 0u,
   DO_NOT_DISPLAY_DURING_EDIT
   } DISPLAY_DURING_EDIT_TYPE;

typedef packed enum
   {
RANGE = 0u,
DISABLED,
ENABLED,
ALM,
INVALID,
HZ,
KHZ,
MHZ,
VOLTS,
WATTS,
AMPS,
OHM,
DB,
MS,                         
PERCENT1,
MAX_NUM_COMMON_WORD
   } COMMON_WORD_TYPE;
        
typedef packed enum
   {
   FP_READ_WRITE = 0u,
   FP_READ_ONLY  
   } FP_ACCESS_TYPE;

typedef struct
   {
   DISPLAY_OBJECT_TYPE      object;
   DISPLAY_DURING_EDIT_TYPE during_edit;
   COMMON_WORD_TYPE         common_word;
   } DISPLAY_ATTRIBUTE_TYPE;
                                                                                   
/* contains information to build a display message for a menu item */
typedef DISPLAY_ATTRIBUTE_TYPE DISPLAY_ATTRIBUTE_LIST_TYPE[MAX_DISPLAY_ATTRIBUTES];
       
/* **** OPTION TYPES ***** */
/* indication of the number of states for an option type */
typedef UINT8 NUMBER_OF_OPTIONS_TYPE;                      
               
/* assume an option has no more than 65K size values */
typedef SINT32 OPTION_VALUE_TYPE;            
                                                     
/* this type shall be sized with the number of values for an option */
typedef OPTION_VALUE_TYPE OPTION_VALUE_LIST_TYPE[];                 

typedef char OPTION_TEXT_TYPE[MAX_OPTION_TEXT_CHARS];

/* this type shall be sized with the number of values for an option */
typedef OPTION_TEXT_TYPE OPTION_TEXT_LIST_TYPE[];
/* **** END OPTION TYPES ***** */

typedef packed enum
   {
   ONE_SIG_DIGITS   = 1u,
   TWO_SIG_DIGITS   = 2,
   THREE_SIG_DIGITS = 3,
   FOUR_SIG_DIGITS  = 4,
   FIVE_SIG_DIGITS  = 5,
   SIX_SIG_DIGITS   = 6,
   SEVEN_SIG_DIGITS = 7,
   EIGHT_SIG_DIGITS = 8
   } SIGNIFICANT_DIGITS_TYPE;

typedef packed enum
   {
   DISPLAY_SIGNED   = 0u,
   DISPLAY_UNSIGNED = 1
   } SIGN_INDICATOR_TYPE;
                     
typedef struct
   {
   NUMBER_OF_OPTIONS_TYPE  number_of_options;
   void                    *value_list;
   void                    *text_list;
   } OPTION_MENU_TYPE;

typedef struct
   {
   SIGNIFICANT_DIGITS_TYPE sig_digits;
   SIGN_INDICATOR_TYPE     sign;
   } FLOAT_MENU_TYPE;

typedef struct
   {
   SIGN_INDICATOR_TYPE     sign;
   UINT32                  divided_by_value;
   SIGNIFICANT_DIGITS_TYPE sig_digits;
   } INTEGER_MENU_TYPE;
         
typedef struct
   {                       
   /* this value should be lt or eq to parameter string size minus 1 (7) */
   /* this value does not include a string terminator */
   UINT8 num_of_chars;
   }STRING_MENU_TYPE;                                                  

typedef union
   {  
   OPTION_MENU_TYPE  option_type;
   INTEGER_MENU_TYPE integer_type;
   FLOAT_MENU_TYPE   float_type;
   STRING_MENU_TYPE  string_type;
   } MENU_SPECIFIC_DISPLAY_TYPE;

typedef struct
   {  
   MENU_ITEM_TYPE                       menu_item_type;
   ITEM_NAME_STRING_TYPE                item_name;  
   PARAMETER_ID_TYPE                    parameter_id;
   FP_ACCESS_TYPE                       access;
   STATION_CONFIGURATION_INCLUSION_TYPE config_inclusion;
   DISPLAY_ATTRIBUTE_LIST_TYPE          display_attributes;
   MENU_SPECIFIC_DISPLAY_TYPE           type_specifics;
   } FP_MENU_TYPE;   

typedef struct
      {
      void   *next_menu_ptr;        /* points to next item (=down arrow key) */
      void   *prior_menu_ptr;       /* points to last item (=up arrow key)   */
      void   *in_menu_ptr;          /* points to current item (=enter key)   */
      void   *out_menu_ptr;         /* points to last option menu (=exit key)*/
      } NAVIGATION_POINTER_TYPE;   

typedef  struct
       {
       FP_MENU_TYPE           menu_information;  /* menu item information        */
       NAVIGATION_POINTER_TYPE   navigation;     /* traversal navigation pointer */
       }  MENU_DATABASE_ITEM_TYPE;  


#endif /* FP_MENU_TYPE_H */
