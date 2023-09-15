/* $Header:   K:\APPS\PVCS Pro\332\INC\WELD.H_V   2.9   Apr 20 1999 11:29:34   ofingere  $ */
#ifndef WELD_H
#define WELD_H
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
 ------------------------ MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      weld.h


            Written by: Laura Markure  
                  Date: 3/18/96  
              Language:  "C"

 ---------------------------- REVISIONS ------------------------------------

   Revision # Date     Author Description
   ========== ======== ====== ===========
      0       4/28/96  LAM    Moved externs from weldmngr.h
      1       5/01/96  LAM    chged encoder,currentforce to sint
      2       5/10/96  LAM    deleted global variables
      3       7/03/96  LAM    removed unused vars 
      4       08-01-96        Changed CurrentPressure from UINT32 to SINT32
      5       12-28-96 LAM    Changed extfreqoffset to SINT16
      6       01-10-97 PhilJ  Changed CurrentFreqIn from UINT32 to SINT32.
      7       01-28-97 LAM    removed unused vars 
     2.8      08-24-98 LAM    added HomePressure
 	 2.9      04-20-99 OFI    Changed for DIAB


 ------------------------------- DESCRIPTION -----------------------------------


 Current values of welder ADC and DAC 

 ------------------------------ INCLUDE FILES ----------------------------------
*/  
#include "portable.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*****     *****     General purpose variables     *****     *****/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           


// Inputs to the 332

extern UINT32 CurrentPowerIn;         /* Value being read by 7890          */
extern UINT32 CurrentAmpIn;           /* Value being read by 7890          */
extern UINT32 CurrentMemIn;           /* Value being read by 7890          */
extern SINT32 CurrentFreqIn;          /* Value being read by 7890          */
extern SINT32 CurrentPressure;        /* Current pressure                  */
extern SINT32 HomePressure;           /* Home pressure                  */
extern SINT32 CurrentForce;           /* Current pressure                  */
extern SINT16 ExtFreqOffset;          /* external frequency offset         */
extern UINT16 ExtAmp;                 /* external amplitude control        */





/*=======================================*/                            
/* INPUT PORT 0 BIT STRUCTURE DEFINITION */
/*=======================================*/                            

struct
 {
   UINT8      missing_part_signal     : 1,  
              power_off_signal        : 1,  
              power_on_signal         : 1, 
              overload_input_signal   : 1,  
              mem_clear_signal        : 1,  
              mem_store_signal        : 1,  
              seek_signal             : 1,  
              run_signal              : 1;  
 } Port0;
                              

#define  MISSPARTINBIT (Port0.b7)
#define  PWROFFBIT     (Port0.b6)
#define  PWRONBIT      (Port0.b5)
#define  OLINBIT       (Port0.b4)
#define  MEMCLRBIT     (Port0.b3)
#define  MEMSTORBIT    (Port0.b2)
#define  SEEKBIT       (Port0.b1)
#define  RUNBIT        (Port0.b0)

               
/*=======================================*/                            
/* INPUT PORT 1 BIT STRUCTURE DEFINITION */                            
/*=======================================*/                            

struct
 {
   UINT8      spar_bite         : 1,  /* bit 7,  */
              e_stop_signal     : 1,  /* bit 6,  */
              pb2_signal        : 1,  /* bit 5,  */
              pb1_signal        : 1,  /* bit 4,  */
              ext_ls_signal     : 1,  /* bit 1,  */
              trig_sw_signal    : 1,  /* bit 0,  */
              uls_signal        : 1,  /* bit 2,  */
              int_ls_signal     : 1;  /* bit 3,  */
 } Port1;
                              
#define  SV4BIT        (PortB1.b7)
#define  SV3BIT        (PortB1.b6)
#define  SV2BIT        (PortB1.b5)
#define  SV1BIT        (PortB1.b4)
#define  TESTBIT       (PortB1.b3)
#define  OLRESETBIT    (PortB1.b2)
#define  RUNSONICBIT   (PortB1.b1)
#define  EXTSEEKBIT    (PortB1.b0)



/*=======================================*/                            
/* INPUT PORT 2 BIT STRUCTURE DEFINITION */                            
/*=======================================*/                            

struct
 {
    UINT8     cycle_abort_signal    : 1,  /* bit 7,  */
              user_input3_signal    : 1,  /* bit 6,  */
              user_input2_signal    : 1,  /* bit 5,  */
              user_input1_signal    : 1,  /* bit 4,  */
              external_reset_signal : 1,  /* bit 3,  */
              display_lock_signal   : 1,  /* bit 2,  */
              start_signal          : 1,  /* bit 1,  */
              ext_profile_tag_signal: 1;  /* bit 0,  */
 } Port2;
                              

#define  UNUSEDBIT     (Port2.b7)
#define  ESTOPBIT      (Port2.b6)
#define  PB2BIT        (Port2.b5)
#define  PB1BIT        (Port2.b4)
#define  EXTLLSBIT     (Port2.b3)
#define  TRIGSWBIT     (Port2.b2)
#define  ULSBIT        (Port2.b1)
#define  INTLLSBIT     (Port2.b0)



/*-----  Frequency  -----*/

SINT32  ActualFreqEnd;
#endif

/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/



/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/






