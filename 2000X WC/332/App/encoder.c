/* $Header:   D:/databases/VMdb/2000Series/App/ENCODER.C_V   2.10.1.3   Jan 11 2018 17:57:38   RCHAPA  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1996                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*   The Encoder is read by the TPU. The channels are initialized in        */
/*   InitTPU.                                                               */
/*                                                                          */
/*     Functions:                                                           */                                                                 
/*       1. ReadEncoder                                                     */
/*                                                                          */
/*                          History of changes                              */
/*                          ------------------                              */
/*                                                                          */
/* Rev    Who Date     Description of change                                */
/* ----   --- -------- ---------------------------------------------------- */
/*  0     LAM 3/14/96  Initial Release                                      */
/*  1     BEK 09-25-96 Change return value to UINT16 from SINT16            */
/*  2.4   OFI 04-23-99 Changed for DIAB                                     */                               
/*  2.5   LAM 05-02-99 moved tempposition out of function                   */                               
/*  2.7   LAM 01-06-06 Updated for the metric encoder                       */                               
/*  2.8   LAM 01-06-06 Return Temp not Tempposition in ReadEncoder          */                               
/*  2.9   LAM 02-11-06 Read Tempposition when at ULS                        */                               
/*  2.10  BEK 02-20-07 Rewrite metric encoder handler to fix act clr bug    */
/*2.10.1.1 HSAN 11-23-17  Added Functions related to the encoder Celera Motion*/
/*2.10.1.2 HSAN 12-26-17  Update the function to improve calculation of encoder*/
/*2.10.1.3 RCHAPA 01-11-18  Update ReadEncoder Function, AbsolutePositionmm
 *                          to read TempPosition when at ULS				*/ 
/*                                                                          */
/*                                                                          */

/*
----------------------------- DESCRIPTION -----------------------------------

 This function read the TPU quadrature decode channels and returns the 
 distance.

-------------------------- INCLUDE FILES ------------------------------------
*/
/* System include files */
#include "portable.h"
#include "preset.h"
#include "state.h"
#include "actnvram.h"


//#define MIN_PULSES_ALTERNATE_ENCODER        0          
#define MAX_PULSES_ALTERNATE_ENCODER        20320    
//#define MIN_PULSES_CURRENT_ENCODER          0        
#define MAX_PULSES_CURRENT_ENCODER          20000    
//#define SLOPE                               ((MAX_PULSES_CURRENT_ENCODER-MIN_PULSES_CURRENT_ENCODER)/(MAX_PULSES_ALTERNATE_ENCODER-MIN_PULSES_ALTERNATE_ENCODER))

/* Function include files */

/*
---------------------------- LOCAL DEFINES  -----------------------------------
*/   

//#define INCLUDE_UNIT_TEST
#define MAX_MOVEMENT        300       // 30mm / second max allowed
#define OVERFLOW_VALUE      65535 - MAX_MOVEMENT
#define UNDERFLOW_VALUE     MAX_MOVEMENT



/*
--------------------------LOCAL TYPE DECLARATIONS -----------------------------
*/

extern CONFIGSETUP CurrentSetup;
extern INBITS Inp;

/*
---------------------------- PRIVATE GLOBAL DATA ---------------------------
*/
static UINT32 VelBuffer[9] = {10000,10000,10000,10000,10000,0,0,0,0};
static UINT32 LastReading = 0;
static SINT32 AbsolutePositionmm;
static UINT16 ReadTempPosition;


/*
--------------------------------- CODE ----------------------------------------
*/



UINT32 ReadEncoder(void)
/****************************************************************************/
/*                                                                          */
/*  This function will read the encoder.  Because the encoder can be metric,*/
/*  we actually need 18 bits to handle the largest number.  The TPU channel */
/*  only gives us 16 bits.  Therefore, a test will be down to determine if  */
/*  we are about to underflow or overflow the 16-bit value.  If so, special */
/*  precautions will be taken to insure accuracy.                           */
/*                                                                          */
/****************************************************************************/
{

   UINT32 Retval, Difference;
   UINT16 PossibleOverFlowFlag = 0, PossibleUnderFlowFlag = 0;
   static UINT32 TempPosition = 0;

   asm(" move.w $ffff22,d0");
   asm(" move.w d0,_ReadTempPosition");        /* Get new reading - 16 bits */
   TempPosition = (UINT32)(ReadTempPosition);  /* Put into 32 bit variable  */
   
   if (CurrentSetup.USEncoder == TRUE)
   {
      if(NVR.Manufacturer==ENCODER_MICROE){ // to calculate at 20000 conts
		  
		 //The prototype function including the slope calculation 
		 //is described as the next formula:
		 // Retval = MIN_PULSES_CURRENT_ENCODER + (TempPosition - MIN_PULSES_ALTERNATE_ENCODER) *  (MAX_PULSES_CURRENT_ENCODER-MIN_PULSES_CURRENT_ENCODER)/(MAX_PULSES_ALTERNATE_ENCODER-MIN_PULSES_ALTERNATE_ENCODER);

		// that was changed to the next formula and reduced to calc  Retval
		// Retval = ((TempPosition ) * 20000) / 20320;
	     Retval = ((TempPosition) * MAX_PULSES_CURRENT_ENCODER) / MAX_PULSES_ALTERNATE_ENCODER ;
      }
      else{
	     Retval=TempPosition;
      }   
   }           /* US encoder, no games to play */
   else if (Inp.uls == TRUE) {
      AbsolutePositionmm = TempPosition;    /* At ULS record distance as is */
      LastReading = TempPosition;
      Retval = TempPosition;
   }
   else {                                   /* Metric encoder, not at ULS   */
                                            /* Let the games begin...       */
/*-------  See if in danger of overflowing  -------*/

      if (LastReading > OVERFLOW_VALUE) {
         PossibleOverFlowFlag = TRUE;
      }

/*-------  See if in danger of underflowing  -------*/

      else if (LastReading < UNDERFLOW_VALUE) {
         PossibleUnderFlowFlag = TRUE;
      }
      
/*-------  Now find the relative difference in last vs current reading  -------*/

      if (TempPosition > LastReading) 
         Difference = TempPosition - LastReading;
      else
         Difference = LastReading - TempPosition;
      
      if (Difference > 0x8000) {
         if (PossibleOverFlowFlag == TRUE) {           /* Overflowed, so find */
            Difference = 65536-LastReading+TempPosition;  /* real difference  */
            AbsolutePositionmm += Difference;             /* and add it in    */
         }   
         else if (PossibleUnderFlowFlag == TRUE) {     /* Underflowed, so find*/
            Difference = 65536-TempPosition+LastReading;  /* real difference  */
            AbsolutePositionmm -= Difference;             /* and subtract it  */
         }
      }      
      else {
      
/*-------  No under or over flowing, so just determine direction  -------*/
      
         if (TempPosition > LastReading) 
            AbsolutePositionmm += Difference;    /* now extending add in diff */
         else
            AbsolutePositionmm -= Difference;    /* now retracting so subtract*/
      }
      Retval = (UINT32) (AbsolutePositionmm / 2.54);  /* Use 32 bit variable for conversion */
      LastReading = TempPosition;
   }
   return (Retval);
}



void ZeroEncoder(void)
/****************************************************************************/
/*                                                                          */
/*   This function will set the encoder to report a distance of zero.  This */
/*   is done by setting the LastReading = 0.                                */
/*                                                                          */
/****************************************************************************/
{
   asm(" move.w #$0,$ffff22");   /* TpuMap->TpuPram3[2] position count  */
   LastReading = 0;              /* Preload with above value            */
   AbsolutePositionmm = 0;       /* Real position in mm's               */
}



UINT16 GetCycleDist(void)
{
   return(0);
}


UINT32 VelocityEstimator(UINT32 NewEncoderPosition)
/***************************************************************************/
/* Estimate velocity during horn downstroke from encoder position readings */
/* taken at 1ms intervals.  The velocity estimator is called from ready.c. */
/* The filter coefficients are [-1/16,-1/4,-3/8,-1/4,0,1/4,3/8,1/4,1/16]/4.*/
/***************************************************************************/
{
UINT32 Temp,Out;
   
   VelBuffer[0] = VelBuffer[1];
   VelBuffer[1] = VelBuffer[2];
   VelBuffer[2] = VelBuffer[3];
   VelBuffer[3] = VelBuffer[4];
   VelBuffer[4] = VelBuffer[5];
   VelBuffer[5] = VelBuffer[6];
   VelBuffer[6] = VelBuffer[7];
   VelBuffer[7] = VelBuffer[8];
   VelBuffer[8] = NewEncoderPosition;
   Out = (VelBuffer[8] - VelBuffer[0]) >>2;
   Out = (Out + VelBuffer[7] + VelBuffer[5] - VelBuffer[3] - VelBuffer[1]) >>2;
   Temp = VelBuffer[6] - VelBuffer[2];
   return ( Out + (Temp>>1) - (Temp>>3) ) >>2;
      
}

/* Include for Unit test */
#ifdef INCLUDE_UNIT_TEST
#include "..\ut\encoder.ut"
#endif
/* End of include for unit test */

