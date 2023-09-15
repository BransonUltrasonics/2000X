/* $Header:   K:\APPS\PVCS Pro\332\INC\QSM.H_V   2.4   Apr 20 1999 10:59:08   ofingere  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96              */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/

/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:  

   Filename:      qsm.h


            Written by: Laura Markure  
                  Date: 3/14/96  
              Language:  "C"

 -------------------------------- REVISIONS ---------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            4/18/96       LAM         Initial Release
      1            8/26/96       LAM         removed global variables
      2.4          4/20/99       OFI         Changed for DIAB
 ------------------------------- DESCRIPTION --------------------------------


 

 ------------------------------ INCLUDE FILES -------------------------------
*/  
#include "portable.h"

/*
 ------------------------------- DEFINES ------------------------------------
*/
 

#define MAX_SPI_LIST 6

/* This enum defines the different types of queues that are processed */

typedef enum
   {
   PS_DAC,
   PS_ADC,
   ACT_ADC,
   ACT_DAC,
   BAR_GRAPH,
   END_OF_LIST
   } SPI_LIST_TYPES;

/*
 --------------------------- TYPE DECLARATIONS ------------------------------
*/                           



/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void InitQsm(void);
void QspiInt(void);   


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/


extern struct MQMap *QsmMap;





