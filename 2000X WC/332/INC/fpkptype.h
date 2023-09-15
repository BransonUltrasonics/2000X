/* $Header:   K:\APPS\PVCS Pro\332new\INC\FPKPTYPE.H_V   2.3   May 05 1999 13:44:54   lmarkure  $ */
#ifndef FP_KEY_PAD_TYPE_H
#define FP_KEY_PAD_TYPE_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: FP_KEY_PAD_TYPE

   Filename: fpkptype.h 


            Written by: Mark Lazarewicz
                  Date: 01/30/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            01/30/96      Mark L      Initial Version
	   2.2			04/19/99	  OFI		  Changed for DIAB
	   2.3          05/05/99      LAM         fixed packed for DIAB
 ------------------------------- DESCRIPTION -----------------------------------
  This file defines the interface to the executable function of the same
  name. 

 ------------------------------ INCLUDE FILES ----------------------------------
*/ 
/*
 --------------------------------- DEFINES -------------------------------------
*/          
                                    
/* define to absolute device values as read via the  */

#define KEYPAD_DEVICE_KEY_1        0xDE
#define KEYPAD_DEVICE_KEY_2        0xBE
#define KEYPAD_DEVICE_KEY_3        0x7E
#define KEYPAD_DEVICE_KEY_4        0xEF 
#define KEYPAD_DEVICE_KEY_5        0xF7
#define KEYPAD_DEVICE_KEY_6        0xEE
#define KEYPAD_DEVICE_KEY_7        0xDF
#define KEYPAD_DEVICE_KEY_8        0xFB
#define KEYPAD_DEVICE_KEY_9        0xF6
#define KEYPAD_DEVICE_KEY_UP       0x7F
#define KEYPAD_DEVICE_KEY_0        0xFD
#define KEYPAD_DEVICE_KEY_DOWN     0xFA
#define KEYPAD_DEVICE_KEY_EXIT     0xBF
#define KEYPAD_DEVICE_KEY_TOGGLE   0xFE
#define KEYPAD_DEVICE_KEY_ENTER    0xFC

                         
/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/     
/* THE FOLLOWING ENUMERATIONS SHALL BE ASSIGNED VALUES */
typedef __packed__ enum
   { 
   KEY_UNKNOWN = 0u,          
   KEY_ONE = KEYPAD_DEVICE_KEY_1 ,
   KEY_TWO = KEYPAD_DEVICE_KEY_2 ,
   KEY_THREE = KEYPAD_DEVICE_KEY_3,  
   KEY_FOUR = KEYPAD_DEVICE_KEY_4 ,
   KEY_FIVE = KEYPAD_DEVICE_KEY_5 ,
   KEY_SIX = KEYPAD_DEVICE_KEY_6 ,
   KEY_SEVEN = KEYPAD_DEVICE_KEY_7 ,
   KEY_EIGHT = KEYPAD_DEVICE_KEY_8 ,
   KEY_NINE = KEYPAD_DEVICE_KEY_9 ,
   KEY_UP   = KEYPAD_DEVICE_KEY_UP ,                     
   KEY_ZERO  = KEYPAD_DEVICE_KEY_0 ,
   KEY_DOWN = KEYPAD_DEVICE_KEY_DOWN ,
   KEY_EXIT = KEYPAD_DEVICE_KEY_EXIT ,
   KEY_TOGGLE = KEYPAD_DEVICE_KEY_TOGGLE ,
   KEY_ENTER = KEYPAD_DEVICE_KEY_ENTER 
   }FP_KEY_PAD_TYPE;

/* THE FOLLOWING ENUMERATIONS SHALL BE ASSIGNED VALUES */
typedef __packed__ enum
   {                            
   KEY_UNK = 0u,
   KEY_STN = KEYPAD_DEVICE_KEY_1,
   KEY_RX  = KEYPAD_DEVICE_KEY_2,
   KEY_TX  = KEYPAD_DEVICE_KEY_3,  
   KEY_OPT1 = KEYPAD_DEVICE_KEY_4,
   KEY_OPT2 = KEYPAD_DEVICE_KEY_5,
   KEY_ASET = KEYPAD_DEVICE_KEY_6,
   KEY_STAT = KEYPAD_DEVICE_KEY_7,
   KEY_CNFG = KEYPAD_DEVICE_KEY_8,
   KEY_ALMS = KEYPAD_DEVICE_KEY_9,
   KEY_SERV = KEYPAD_DEVICE_KEY_UP,
   KEY_DIS  = KEYPAD_DEVICE_KEY_0,
   KEY_ALGN = KEYPAD_DEVICE_KEY_DOWN,
   KEY_EXT  = KEYPAD_DEVICE_KEY_EXIT,
   KEY_TGL  = KEYPAD_DEVICE_KEY_TOGGLE,
   KEY_ENTR = KEYPAD_DEVICE_KEY_ENTER
   }FP_MENU_KEY_PAD_TYPE;             

typedef __packed__  enum
   {        
   KEY_EDIT_UNKNOWN = 0u,   
   KEY_EDIT_ONE = KEYPAD_DEVICE_KEY_1 ,
   KEY_EDIT_TWO = KEYPAD_DEVICE_KEY_2 ,
   KEY_EDIT_THREE = KEYPAD_DEVICE_KEY_3,  
   KEY_EDIT_FOUR = KEYPAD_DEVICE_KEY_4 ,
   KEY_EDIT_FIVE = KEYPAD_DEVICE_KEY_5 ,
   KEY_EDIT_SIX = KEYPAD_DEVICE_KEY_6 ,
   KEY_EDIT_SEVEN = KEYPAD_DEVICE_KEY_7 ,
   KEY_EDIT_EIGHT = KEYPAD_DEVICE_KEY_8 ,
   KEY_EDIT_NINE = KEYPAD_DEVICE_KEY_9 ,
   KEY_EDIT_PRIOR  = KEYPAD_DEVICE_KEY_UP,                     
   KEY_EDIT_ZERO  = KEYPAD_DEVICE_KEY_0 ,
   KEY_EDIT_NEXT = KEYPAD_DEVICE_KEY_DOWN,
   KEY_PAD_ENTER = KEYPAD_DEVICE_KEY_ENTER,
   KEY_EDIT_TOGGLE = KEYPAD_DEVICE_KEY_EXIT
   }FP_EDIT_KEY_PAD_TYPE;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/  
           
                         
/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/    
#endif /* FP_KEY_PAD_TYPE_H */
