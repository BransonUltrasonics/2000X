/* $Header:   L:/pvcs/1000/psos332/archives/inc/MCNSTRUC.H_v   2.2   01 Aug 1996 14:47:06   BKYMER  $ */
#ifndef DISPLAY_MESSAGE_CONSTRUCTOR_H
#define DISPLAY_MESSAGE_CONSTRUCTOR_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: DISPLAY_MESSAGE_CONSTRUCTOR

   Filename: display_message_constructor.h 


            Written by: 
                  Date:  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
 ------------------------------- DESCRIPTION -----------------------------------
  This file defines the interface to the executable function of the same
  name. 

 ------------------------------ INCLUDE FILES ----------------------------------
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/                                   
#define MAX_CONSTRUCTED_MESSAGE_DISPLAY_SIZE 48
/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/                          
typedef packed enum
   {    
   MESSAGE_FORMATION_OK = 0u,
   MESSAGE_FORMATION_ERROR
   }CONSTRUCTION_MESSAGE_STATUS_TYPE;

typedef packed enum
   {
    CREATE_MESSAGE = 0u,  
    CREATE_MSG_WITH_PROVIDED_DATA
   }MESSAGE_CONSTRUCTION_ACTION_TYPE;

typedef packed enum
   {
   ASCII_FORMAT = 0u,
   ACTUAL_FORMAT,
   PARAMETER_VALUE_FORMAT
   }DATA_FORMAT_TYPE;

typedef enum
   {
   IN_EDIT_MODE = 0u,
   NOT_IN_EDIT_MODE
   }EDIT_MODE_TYPE;
                                 
typedef struct
   {
   MESSAGE_CONSTRUCTION_ACTION_TYPE   action;
   DATA_FORMAT_TYPE                   data_format;
   EDIT_MODE_TYPE                     edit_mode;
   } MESSAGE_CONSTRUCTION_REQUEST_TYPE;

typedef struct
   {
   char      string[MAX_CONSTRUCTED_MESSAGE_DISPLAY_SIZE];
   SINT32    option;
   SINT32    integer;
   FLOAT     float_pt;
   } PROVIDED_DATA_TYPE;

typedef char CONSTRUCTED_MESSAGE_DISPLAY_TYPE[MAX_CONSTRUCTED_MESSAGE_DISPLAY_SIZE];
/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/  
CONSTRUCTION_MESSAGE_STATUS_TYPE display_message_constructor(
                   MESSAGE_CONSTRUCTION_REQUEST_TYPE request,
                   PROVIDED_DATA_TYPE                provided_data,
                   CONSTRUCTED_MESSAGE_DISPLAY_TYPE          *constructed_message
                   );
                     
void display_message_constructor_init (void);

                     
                                                            
/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/    

     


#endif /* DISPLAY_MESSAGE_CONSTRUCTOR_H */
