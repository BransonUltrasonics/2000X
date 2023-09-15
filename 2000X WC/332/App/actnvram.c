/* $Header:   D:/databases/VMdb/2000Series/App/ACTNVRAM.C_V   1.94.1.0.1.1   Nov 29 2017 11:33:50   hasanchez  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96, 2009        */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*                                
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: actnvram.c

 ---------------------------- REVISIONS ------------------------------------

 Rev#  Date          Author   Description
 ===== ========      =======  =============================================
 1.0   11/22/96      PhilJ    Initial version
 1.1   12/23/96      PhilJ    Added function GetActuatorType();
 1.2   12/23/96      LAM      moved strokelen to preset        
 1.3   12/23/96      PhilJ    Corrected bug in GetActuatorType();
 1.4   12/27/96      LAM      added getcountsperlb();             
 1.5   12/27/96      PhilJ    Correct bug in GetActuatorType();             
 1.6   12/30/96      LAM      commented out strokelen        
 1.7   09/11/97      PaulG    Unit test and data cleanup.        
 1.8   09-25-97      LAM      moved initbargraph from sysmangr        
 1.9   10-03-97      LAM      added delay when switching queues       
 1.10  11-17-97      LAM      deleted prepc       
 1.11  03.10.98      JBerman  Changed CurrentPreset.StrokeLen to CurrentSetup.StrokeLen 
 1.12  04.20.98      JBerman  Rewrote this file for Rel. 2.5
 1.13  04.24.98      JBerman  Modified Strk with Stroke 
 1.14  04.24.98      JBerman  Changed MaxForce to GetMaxForce
 1.15  04.24.98      JBerman  Due to some timing problems, GetDef/StrkLength
                              GetDef/CylSize, Is_AED, were tempoprarly modified
 1.16  04.28.98      JBerman  Added a delay in ReadNVR
 1.17  05.06.98      JBerman  Improved this file
 1.18  05.11.98      JBerman  Added NvrCopyDeftoNon();

 1.19  05.13.98      LAM      use NVR structure instead of currentsetup struct
 1.20  05.13.97      JBerman  Fixed the function: NvrCopyDeftoNon.
 1.21  05.14.97      LAM      chged pressure & loadcell to SINT16.
 1.22  05.18.98      JBerman  Commented out ActLifeTime; Future Rel.
 1.23  05.19.98      BJB      Modified GetMaxForce() to return PSI * 10.
                              Modified DefLoad[] to return PSI * 10.
 1.24  05.27.98      JBerman  Added the following functions:
                              void SetCalibPass(BOOLEAN);
                              BOOLEAN GetCalibPass(void);
                              void SetCalibrationDate(UINT16 *Ptr); 
 1.25  06.04.98      Jberman  In GetActId, I converted a valuex to BITx  
 1.26  06.04.98      LAM      fixed loadcell default to better values   
 1.27  06.05.98      JBerman  Enabled DedCalDate[], CalDate[], on power up.
 1.28  06.11.98      LAm      chged address of CalibPass to A4 from 104
 1.29  06-17-98      BEKymer  Changed CA1 to EQ20
 1.30  06.25.98      JBerman  Created new functions:ActRecovery, CheckValidForRecovery.        
 1.31  06.30.98      JBerman  Modified Actuator w CurrentSetup.Encoder 
 1.32  07.08.98      JBerman  In ActRecovery changed NVR.ActId w GetActId()
 1.33  07.15.98      JBerman  Expended MaxForce table for mm Cyl Size
                              F=90*.25*Pi*(d^2);  d=dmm/2.54 for lbs
 1.34  07.21.98      LAM      changed defload table to correct defaults 
 1.35  07.30.98      BJB      Moved act_nvr definition to actnvram.h.
                              Modified ActPowerUp() so it works for all actuators.
                              Beefed up serial # check in CheckNvrValid().
                              Cleaned up use of QSPI so no interference with/from
                              1ms ISR. Deleted CheckValidForRecovery(),
                              ActRecovery(), functions more or less moved
                              into InitSetupFromAct(), CheckForActChange().
                              Added ActRecover().
                              Renamed Is_AED() to ActNovramExists().
 1.36  08.03.98      BJB      ActRecover() modified to set default values
                              for calibration tables.
                              ActRecover() accepts parameter, type of
                              actuator to set up.
 1.37  09.01.98      LAM      added update default calibration procedures
 1.38  09.04.98      BJB      Doesn't write Novram on every power-up,
                              only if doesn't see valid Act ID.
                              Makes sure to set min/max values on change
                              from AE to AED.
 1.39  09.28.98      LAM      chged baud rate to 524.3kHz, disabled NVR
                              when not in use
 1.40  09.28.98      BJB      Verifies writes to Novram.
 1.41  10.05.98      LAM      added defcalibdate function,moved retry to writeactnvram,
                              check all cylinder sizes in chknvrvalid
 1.42  10.13.98      BJB      Cleaned up Act Novram writing code, esp. to fix bug
                              caused by write/verify in ActNovramExists().
 1.43  10.22.98      LAM      removed compare of two reads in actnovramexists
 1.44  10.26.98      LAM      fixed nvrcopydeftonon to copy correct number, fixed
                              serial number loops
 1.45  10.27.98      LAM      only compare 9 characters for serial number
 1.46  10.28.98      BJB      Modified SetSerNum() to take SINT8* instead of UINT16*.
 1.47  05-25-99      JZ       Modified GetActId, SetActId, ActPowerUp, SetDefForce, 
                              SetForceNVR, UpdateDefForce, GetMaxForce
                              modified if statements with NVR.ActId, added NVR_AE,
                              NVR_AED, NVR_AEF
 1.48  05-28-99      JZ       fixed switch(NVR.ActId) statement, ActRecover(void)
 1.49  06-09-99      JZ       fixed if statement in function CheckNvrValid
 1.50  06-16-99      JZ       fixed if statement in function ActNovramExists                          
 1.50.2.1 06-25-99   JHenry   Added GetDefForce function; deleted unused functions
                              GetPressure and GetLoadCell.
 1.52  08-03-99      JZ       added ERRORCODE for EQ10 alarm 
 1.53  08-06-99      LAM      added default tables for 2in and 3in cylinder.
 1.54  08-06-99      JZ       added RecordErrorCode 
 1.55  09-03-99      JZ       fixed SetActId
 1.56  09-03-99      LAM      added update cylinder factors   
 1.57  09-08-99      LAM      added cal system pressure and stroke length to NVR 
 1.58  09-09-99      JZ       modified GetMaxForce
 1.59  09-09-99      LAM      buildvelocity table at power up and estop 
 1.60  09-15-99      LAM      moved buildvelocitytable to Checkforactchanged, changed
                              2in velocity cylinder factor,saving slope and home offset
                              to NVR 
 1.61  10-01-99      LAM      added write verify to aa55 also                                                                 
 1.62  10-14-99      BEKymer  Added new functions TestWriteToNvram() and
                              TestReadFromNvram().
                              Added QsmMap->Spcrl.Dtl = DELAY_ACT_NOVRAM wherever
                              QsmMap->Spcrl.Spe was.  
 1.63  10-28-99      JZ       Cleaned GetMaxForce
 1.64  10-29-99      BEKymer  Changed MAX_ACTNVRAM_RETRIES from 10 to 2
                              Added GlobalRetryCounter
                              Remove TABS! Cleanup up spacing.
 1.65  11-04-99      JZ       changed numbers to defines in GetMaxForce()                        
 1.65.2.1  12-06-99  JZ       created AE_VERIFY_ADDR define for AE act novram address check
 1.66  01-20-00      JZ       changed CheckForActChange()                                                  
 1.67  01-21-00      JZ       fixed act type alarm in CheckForActChange()
 1.68  01-24-00      JZ       fixed CheckForActChange() for AEF act. case
 1.69  03-27-00      JZ       removed commented code
 1.71  04-17-00      JLH      Added AED Upgrade error test.
 1.72  04-20-00      JLH      Removed AED Upgrade error test; moved test to root.c.
 1.73  05-23-00      JLH      Added calls to ClearReady for Wrong Actuator alarm.  This should prevent horn down
                              from operating when a Wrong Actuator alarm is present. 
 1.74  06-28-00      BEKymer  Changed all MODEL to LEVEL
 1.75  09-03-00      LAM      ActRecover() modified to only set actuator to ae
                              when it is not an aed or aef.                        
 1.76  09-26-00      JLH      Added TermUpdateDataHeader call if Actuator has changed to rewrite terminal screen in new format.
                              Added Changed = TRUE where one was needed.  These changes satisfy tracker issue #3573.
 1.77  10-30-00      LAM      UpdateDefCalStrokeLength to copy to calibrated strokelength into the default
                              strokelength (Issue 3661)
 1.78  10-30-00      LAM      Added functions to update & reset calibration correctly.(Issue 3661)
 1.79  11-02-00      LAM      Added the check if not wrong actuator then check for recal
                              alarms(Issues 3658 & 3662)
 1.80  11-13-00      AT       Update actuator serial number at powerup
 1.81  11-14-00      LAM      removed duplicate updating of actuator serial number at powerup & estop
 1.82  11-28-00      BEKymer  Modified GetForceMax() to handle a 4" diameter cylinder (AED & AEF)
                              Modified UpdateCylinderFactor() to handle a 4" diameter cylinder
                              Modified CheckNvrValid() to handle a 4" diameter cylinder
 1.81.1.2 06-27-01   BEK      Modify GetActID to return AE when Handheld is turned on
                              and to disable Handheld when aed or aef actuator
 1.84  04-02-02      LAM      added 8.06 changes: NVR.PSVersion, SetPSVersionNVR, updated loadcell defaults                      
 1.85  04-08-02      LAM      Set NVR.PSVersion to CurrentVersion before saving to Novram                      
 1.86  05-17-02      LAM      Only use loadcell offset with AED actuator,updated defaults
                              per testing results                     
 1.87  03-29-04      BEKymer  Whenever copying actuator serial number into current
                              setup or BBR, make sure a NULL terminator is included.
                              The NOVRAM does not include the NULL.
 1.88  04-05-05      LAM      Added forcegauge type to novram structure, create sbeam default table                        
 1.89  09-04-08      YGupta   Cleanup for LangTest Project.
 1.90  10-20-08      NHAhmed  Replaced stroke length LENGTH_7 by LENGTH_2.
 1.91  09-10-09      BEkymer  Add new define MICRO where needed
 1.92  09-22-09      YGupta   Added Support & Default values for MICRO Actuator.
 1.93  06-08-10      PDwivedi Added GetEncoderType and SetEncoderType functions for
                              Standard MICRO Actuator.
 1.94  06-18-10      PDwivedi Modify CheckForActChange() function for
                              Standard MICRO Actuator.
 1.94.1.0  10-26-13  GButron  Actuator_Novram_Exist flag added
 1.94.1.0.1.1 11-23-17  HSAN  Added functions related to different encoders handling.
 ---------------------------- DESCRIPTION -----------------------------------
    
   


 --------------------------- INCLUDE FILES ----------------------------------
*/
       
#include <psos.h>
#include <prepc.h>
#include "332.h"
#include "qsm.h"
#include "menu.h"
#include "actnvram.h"
#include "preset.h"
#include "snsrcalb.h"
#include "ticks.h"
#include "spidd.h"
#include "alarms.h"
#include "ready.h"
#include "menu7a.h"
#include "digout.h"
#include "rdyweld1.h"

/*---------------------------------- GLOBAL DATA ---------------------------*/
/*                          (scope is global to ALL files)                  */


const UINT16 DefPress[]={20,165,311,457,602,748,894,1039,1185,1331,1476};

/* 1000 count offset built in for AED only*/
const UINT16 AEDDefLoad[]=  {1041,2124,3207,4289,5372,6454,7537,8619,9701,10787,11887}; 
const UINT16 AEFDefLoad[]=  {  41,1124,2207,3289,4372,5454,6537,7619,8701, 9787,10887};  


const UINT16 MICRODefLoad[]={999,1432,1866,2299,2733,3167,3601,4034,4468,4902,5336}; 

const SINT32 DefForce3in[] = {46603, 18473, -9657, 0, 0, 0, 0, 0, 0, 0, 0};
const SINT32 DefForce2in[] = {20712, -7418, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* 1000 count offset built in for AED and AEF SBEAM*/
const UINT16 DefSBeam[]={950,1880,2810,3740,4670,5600,6530,7460,8390,9320,10250}; 
        
UINT8 NovramEnable = FALSE;
struct act_nvr NVR;
SINT16 ForceTableCylFactor,VelocityTableCylFactor;

BOOLEAN Actuator_Novram_Exist = FALSE;

/*------------------------- EXTERNAL DATA ----------------------------------*/


extern CONFIGSETUP CurrentSetup;
extern SETUPS_Ver800      CurrentPreset;
extern UINT16      OneMilTimer;
extern UINT16      ChecksumRet;
extern UINT32      GlobalRetryCounter;
extern const UINT16  CurrentVersion;    /* Current version/revision in binary, no decimal */


/*---------------------------- LOCAL_EQUATES -------------------------------*/
                                                             
#define ACTBAUDRATE           23    // 24.6.../(2*20) = 524.3kHz
#define MAX_ACTNVRAM_RETRIES  2
#define DEFCALDATE            0x19
#define DELAY_ACT_NOVRAM      7
#define MANUFACTURER_ADDRESS  0xa0

#define PSI2DAC               65535.0/90.0
/* The force factor = (cyl*cyl/(cyl*cyl -shaft * shaft))*PSI2DAC */
/* divide by 10 so that pressure can be kept in 1/10 PSI, multiply by 256 to keep accuracy */

#define FORCEFACTORSIZE1_5        (SINT16)(((1.5*1.5/(1.5*1.5 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE2_0        (SINT16)(((2.0*2.0/(2.0*2.0 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE2_5        (SINT16)(((2.5*2.5/(2.5*2.5 - 0.625 * 0.625))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE3_0        (SINT16)(((3.0*3.0/(3.0*3.0 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE3_25       (SINT16)(((3.25*3.25/(3.25*3.25 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE4_0        (SINT16)(((4.0*4.0/(4.0*4.0 - 0.75 * 0.75))*PSI2DAC)/10)<<8

#define FORCEFACTORSIZE_40        (SINT16)(((1.57*1.57/(1.57*1.57 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE_50        (SINT16)(((1.97*1.97/(1.97*1.97 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE_63        (SINT16)(((2.48*2.48/(2.48*2.48 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE_80        (SINT16)(((3.15*3.15/(3.15*3.15 - 0.75 * 0.75))*PSI2DAC)/10)<<8

#define VELFACTORSIZE1_5           FORCEFACTORSIZE1_5
#define VELFACTORSIZE2_0           20500 /* set using AEF # 6 */
#define VELFACTORSIZE2_5           FORCEFACTORSIZE2_0
#define VELFACTORSIZE3_0           18455
#define VELFACTORSIZE3_25          FORCEFACTORSIZE3_25
#define VELFACTORSIZE4_0           FORCEFACTORSIZE4_0

#define VELFACTORSIZE_40           FORCEFACTORSIZE_40
#define VELFACTORSIZE_50           FORCEFACTORSIZE_50
#define VELFACTORSIZE_63           FORCEFACTORSIZE_63
#define VELFACTORSIZE_80           FORCEFACTORSIZE_80

#define AE_VERIFY_ADDR    0x00ff        /* Novram address used to verify AE actuator being present */


//-------------------------- LOCAL DATA ------------------------------------


enum ACTUATOR Actuator;



//----------------------------- CODE ---------------------------------------


void ActPowerUp(void)
{
   UINT16 i=0;
   UINT16 j=0;
   UINT32 temp1=0;
   UINT32 temp2=0;

   NovramEnable=TRUE;
/* make sure 1ms queues are done */
   OneMilTimer = 0;
   while(OneMilTimer<5){};

   Init3();

   if (ActNovramExists())
   {

      Actuator_Novram_Exist = TRUE;
      NVR.ActId=ReadNVR(0);

      // temp2=ReadNVR(2);  MSB
      // temp2=temp2<<16;                            Future Rel.
      // temp1=ReadNVR(1);  LSB
      // NVR.ActualLifeTime=temp1|temp2;
      NVR.DefStrokeLength=ReadNVR(3);
      NVR.StrokeLength=ReadNVR(0x53);
      NVR.DefCylSize=ReadNVR(4);
      NVR.CylSize=ReadNVR(0x54);
      NVR.CalibDefPass=ReadNVR(0xA3);
      NVR.CalibPass=ReadNVR(0xA4);
      NVR.EncoderType=ReadNVR(ENCODER_ADDR);
      /*
      for(i=0; i<10; i++){
         NVR.DefCalUseName[i]=ReadNVR(i+0x0F);       Future Rel.
         NVR.CalUseName[i]=ReadNVR(i+0x5F);
      }
      */
      for(i=0; i<MAXSERIALNUM; i++){
         NVR.DefSerNum[i]=ReadNVR(i+5);
         NVR.SerNum[i]=ReadNVR(i+0x55);
      }
      for(i=0; i<11; i++){
        NVR.DefLoadCell[i]=ReadNVR(i+0x1C);
        NVR.LoadCell[i]=ReadNVR(i+0x6C);
        NVR.DefPressure[i]=ReadNVR(i+0x27);
        NVR.Pressure[i]=ReadNVR(i+0x77);
        // NVR.DefDeflection[i]=ReadNVR(i+0x48);    Future Rel.
        // NVR.Deflection[i]=ReadNVR(i+0x98);
      }

     for(i=0, j=0; i< FORCE_TABLE_SIZE; i++, j+=2){                       
        temp2=ReadNVR(j+0x33); // MSB
        temp2=temp2<<16;       // Default Force Table
        temp1=ReadNVR(j+0x32); // LSB
        NVR.DefForce[i]=temp1|temp2;                      
        temp2=ReadNVR(j+0x83); // MSB
        temp2=temp2<<16;       // Force Table
        temp1=ReadNVR(j+0x82); // LSB
        NVR.Force[i]=temp1|temp2;
      }
      
      temp2=ReadNVR(0x3F); // MSB
      temp2=temp2<<16;       // Default Calibrated Stroke Length
      temp1=ReadNVR(0x3E); // LSB
      NVR.DefCalStrokeLen =temp1|temp2;                      
      temp2=ReadNVR(0x8F); // MSB
      temp2=temp2<<16;       // Calibrated Stroke Length
      temp1=ReadNVR(0x8E); // LSB
      NVR.CalStrokeLen =temp1|temp2;

      NVR.DefCalSysPressure=ReadNVR(0x40);
      NVR.CalSysPressure=ReadNVR(0x90);
      
      NVR.DefSpringRateSlope=ReadNVR(0x42);
      NVR.SpringRateSlope=ReadNVR(0x92);
      NVR.DefCalHomeOffset =ReadNVR(0x41);
      NVR.CalHomeOffset =ReadNVR(0x91);
     
      NVR.PSVersion = ReadNVR(0xa5);  
      NVR.ForceGauge = ReadNVR(0xa6);
      
      NVR.Manufacturer = ReadNVR(MANUFACTURER_ADDRESS);  
      
      if ((NVR.Manufacturer != 1) && (NVR.Manufacturer != 2)) // to avoid undesire values on the manufaturer, specially the first check.
	  {
		  SetManufacturer( ENCODER_OLD );
	  }
      
      if((NVR.ForceGauge < LOAD_CELL) || (NVR.ForceGauge > SBEAM))
      {
         NVR.ForceGauge = LOAD_CELL;        /* Load cell is the default */ 
         SetForceGauge(NVR.ForceGauge);
      }
      for(i=0; i<3; i++){
        NVR.DefCalDate[i]=ReadNVR(i+0x19);
        NVR.CalDate[i]=ReadNVR(i+0x69);
      }
      UpdateCylinderFactor();
   }
   else
      ActRecover();

   InitBarGraph();
   NovramEnable=FALSE;
}     



UINT16 GetActId(void){  
   UINT16 Convert;
   switch(NVR.ActId){
      case NVR_AE: 
         Convert=AE; // ae
         break;
      case NVR_AED: 
         Convert=AED; // aed
         CurrentSetup.HandHeld = FALSE;     /* Force handheld off */
         DealWithHandHeldChange();          /* Pretend menu turned it off */
         break;
      case NVR_MICRO: 
         Convert=MICRO; // micro
         CurrentSetup.HandHeld = FALSE;     /* Force handheld off */
         DealWithHandHeldChange();          /* Pretend menu turned it off */
         break;
      case NVR_AEF: 
         Convert=AEF; // aef
         CurrentSetup.HandHeld = FALSE;     /* Force handheld off */
         DealWithHandHeldChange();          /* Pretend menu turned it off */
         break;      
      default:
         Convert=AE; // ae
         break;
   }
   return (Convert); 
}



UINT32 GetActLifeTime(void){
   return NVR.ActualLifeTime;
}



UINT16 GetDefStrokeLength(void){
   return (NVR.DefStrokeLength);
}



UINT16 GetStrokeLength(void){
   return (NVR.StrokeLength);
}



UINT16 GetDefCylSize(void){
   return (NVR.DefCylSize);
}



UINT16 GetCylSize(void){
   return (NVR.CylSize);
}

enum ENCODER GetEncoderType (void)
{
   return (NVR.EncoderType);
}

void SetActId(UINT16 Data)
{
   if((Data==NVR_AED)||(Data==NVR_AEF)||(Data==NVR_MICRO)) // 3,5  aed, aef, micro
   {
      NVRWriteSetup();
      NVRWriteVerify(Data, 0);
      NVR.ActId=Data;
      NVRCommandEWDS();  
   }
   else
   {  
      NVR.ActId=NVR_AE;      /* 1 default ae */
   }
}


//-----------------------------------------------------------------------
// This function will reset the Actuator Life Time counter.
// It's recommanded to call it only once, say serial num initializaiton.
//------------------------------------------------------------------------

/*
void ResetActLifeTime(void)
{
   NVRWriteSetup();
   NVRWriteVerify(0, 2);  // Send 0x00010000
   NVRWriteVerify(0, 1);  // Gaining 65 Million counting more
   NVRCommandEWDS();  
}      


void SetActLifeTime(void)
{
   NVRWriteSetup();

   if (NVR.ActualLifeTime==0x0000FFFF)
   {  
      NVRWriteVerify(1, 2);  // Send 0x00010000
      NVRWriteVerify(0, 1);  // Gaining 65 Million counting more
      NVR.ActualLifeTime++;
   }
   else
   {
        NVRWriteVerify(++NVR.ActualLifeTime, 1); // 2 birds in one shot
   }

   NVRCommandEWDS();  
}
*/


/****************************************************************************/ 
/*                                                                          */
/* This function was created to update the parameter of the manufacturer    */
/* Parameters:  Data   The new value                                        */
/* Returns: Nothing                                                         */
/*                                                                          */
/****************************************************************************/ 
void SetManufacturer(UINT16 Data)
{
   NVRWriteSetup();
   NVRWriteVerify(Data, MANUFACTURER_ADDRESS);
   NVR.Manufacturer=Data;
   NVRCommandEWDS();  
}



void SetDefStrokeLength(UINT16 Data)
{
   NVRWriteSetup();
   NVRWriteVerify(Data, 3);
   NVR.DefStrokeLength=Data;
   NVRCommandEWDS();  
}



void SetStrokeLength(UINT16 Data)
{
   NVRWriteSetup();
   NVRWriteVerify(Data, 0x53);
   NVR.StrokeLength=Data;
   NVRCommandEWDS();  
}



void SetDefCylSize(UINT16 Data)
{
   NVRWriteSetup();
   NVRWriteVerify(Data, 4);
   NVR.DefCylSize=Data;
   NVRCommandEWDS();  
}



void SetCylSize(UINT16 Data)
{
   NVRWriteSetup();
   NVRWriteVerify(Data, 0x54);
   NVR.CylSize=Data;
   NVRCommandEWDS();  
}



void SetDefCalStrokeLength(UINT32 Data)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from DoColdStartPlus.                            */
/*                                                                          */
/****************************************************************************/ 
{
   UINT32 temp=0;                                          
   UINT16 LsbData=0;
   UINT16 MsbData=0;
   
   UINT16 Address=0x3E;                                             
      
   NVRWriteSetup();      // enable write

   temp=Data; // 32 bits
   LsbData= (UINT16)(temp & 0x0FFFF); // Isolated the LSB part
     
   temp= (temp & 0x0FFFF0000); // Isolated the MSB part
   MsbData= (UINT16)(temp >> 16);
        
   NVRWriteVerify(LsbData, Address);  // Data, Address
   NVRWriteVerify(MsbData, Address+1);  // Data, Address
   NVRCommandEWDS();  
}                        



void SetDefCalSysPressure(SINT16 Data)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from DoColdStartPlus. Default pressure = 60PSI   */
/*                                                                          */
/****************************************************************************/ 
{
   NVRWriteSetup();
   NVRWriteVerify((UINT16)Data, 0x40);
   NVR.DefCalSysPressure=Data;
   NVRCommandEWDS();  
}



void SetCalStrokeLength(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from DoColdStartPlus and Cal Sensors.            */
/*                                                                          */
/****************************************************************************/ 
{
   UINT32 temp=0;                                          
   UINT16 LsbData=0;
   UINT16 MsbData=0;
   
   UINT16 Address=0x8E;                                             
      
   NVRWriteSetup();      // enable write

   temp=NVR.CalStrokeLen; // 32 bits
   LsbData= (UINT16)(temp & 0x0FFFF); // Isolated the LSB part
     
   temp= (temp & 0x0FFFF0000); // Isolated the MSB part
   MsbData= (UINT16)(temp >> 16);
        
   NVRWriteVerify(LsbData, Address);  // Data, Address
   NVRWriteVerify(MsbData, Address+1);  // Data, Address
   NVRCommandEWDS();  
}



void SetCalSysPressure(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from DoColdStartPlus and Cal Sensors.            */
/*                                                                          */
/****************************************************************************/ 
{
   NVRWriteSetup();
   NVRWriteVerify(NVR.CalSysPressure, 0x90);
   NVRCommandEWDS();  
}


void SetPSVersionNVR(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when the Power Supply Version Number needs to be */
/* saved to the Novram.  This function is called after a successful         */
/* Calibrate Sensors, when the "checksum" is done, or at power up when a    */
/* Version 6 actuator is detected.                                          */
/*                                                                          */
/****************************************************************************/ 
{
   NVRWriteSetup();
   NVR.PSVersion = CurrentVersion;
   NVRWriteVerify(NVR.PSVersion, 0xa5);
   NVRCommandEWDS();  
}


void UpdateDefCalStrokeLength(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from the Branson menu after Calibration is run   */
/*                                                                          */
/****************************************************************************/ 
{
   UINT32 temp=0;                                          
   UINT16 LsbData=0;
   UINT16 MsbData=0;
   
   UINT16 Address=0x3E;                                             
      
   NVRWriteSetup();      // enable write

   temp=NVR.CalStrokeLen; // 32 bits
   LsbData= (UINT16)(temp & 0x0FFFF); // Isolated the LSB part
     
   temp= (temp & 0x0FFFF0000); // Isolated the MSB part
   MsbData= (UINT16)(temp >> 16);
        
   NVRWriteVerify(LsbData, Address);  // Data, Address
   NVRWriteVerify(MsbData, Address+1);  // Data, Address
   NVR.DefCalStrokeLen = NVR.CalStrokeLen;  

   NVRCommandEWDS();  
}



void UpdateDefCalSysPressure(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from the Branson menu after Calibration is run   */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Address=0x0040;
   
   NVRWriteSetup();
   NVRWriteVerify(NVR.CalSysPressure, Address);
   NVR.DefCalSysPressure=NVR.CalSysPressure;
   NVRCommandEWDS();  

}


void UpdateDefCalHomeOffset(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from the Branson menu after Calibration is run   */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Address=0x0041;
   
   NVRWriteSetup();
   NVRWriteVerify(NVR.CalHomeOffset, Address);
   NVR.DefCalHomeOffset=NVR.CalHomeOffset;
   NVRCommandEWDS();  

}


void SetDefSerNum(UINT8 *Ptr)
{ 
   UINT16 i=0;
   
   NVRWriteSetup();
  
   for(i=0; i<MAXSERIALNUM; i++)
   {
      NVRWriteVerify(((UINT16) Ptr[i]), i+5);  // Data, Address
      NVR.DefSerNum[i]=Ptr[i];
   }
   NVRCommandEWDS();  
}



void SetSerNum(SINT8 *Ptr)
{
   UINT16 i=0;

   NVRWriteSetup();

   for(i=0; i<MAXSERIALNUM; i++)
   {
      NVRWriteVerify((UINT16)*Ptr, i+0x55);  // Data, Address
      NVR.SerNum[i]=*Ptr++;
   }

   NVRCommandEWDS();  
}



void SetLoadCell(void)   // You want to update CurrentSetup, first
{
   UINT16 i=0;
   UINT16 Address=0x006C;

   NVRWriteSetup();

   for(i=0; i<11; i++)
   {
      NVRWriteVerify(NVR.LoadCell[i], Address++);  // Data, Address
   }
         NVRCommandEWDS();  
}



/*   Future Rel.
void SetDefDeflection(UINT16 *Ptr)
{
   UINT16 i=0;

   NVRWriteSetup();

   for(i=0; i<11; i++)
   {
     NVRWriteVerify(*Ptr, i+0x48);  // Data, Address
     NVR.DefDeflection[i]=*Ptr++;
   }

   NVRCommandEWDS();  
}



void SetDeflection(UINT16 *Ptr)
{
   UINT16 i=0;

   NVRWriteSetup();

   for(i=0; i<11; i++)
   {
     NVRWriteVerify(*Ptr, i+0x98);  // Data, Address
     NVR.Deflection[i]=*Ptr++;
   }
   NVRCommandEWDS();  
}

*/



void UpdateDefForce(void)
{
   UINT32 temp=0;                                          
   UINT16 LsbData=0;
   UINT16 MsbData=0;
   UINT16 i=0;
   UINT16 j=0;
   
   UINT16 Address=0x32;                                             
      
   NVRWriteSetup();      // enable write

   for(i=0, j=0; i< FORCE_TABLE_SIZE; i++, j+=2)
   {
      temp=NVR.Force[i]; // 32 bits
      LsbData= (UINT16)(temp & 0x0FFFF); // Isolated the LSB part
      NVR.DefForce[i]=temp;
     
      temp= (temp & 0x0FFFF0000); // Isolated the MSB part
      MsbData= (UINT16)(temp >> 16);
        
      NVRWriteVerify(LsbData, j+Address);  // Data, Address
      NVRWriteVerify(MsbData, j+Address+1);  // Data, Address
   }

   NVRCommandEWDS();  // disable novram
}



void SetDefForce(void)
{
/* Load the default table based on cylinder type */

   UINT32 temp=0;                                          
   UINT16 LsbData=0;
   UINT16 MsbData=0;
   UINT16 i=0;
   UINT16 j=0;
   
   UINT16 Address=0x32;                                             
      
   NVRWriteSetup();      // enable write

   for(i=0, j=0; i< FORCE_TABLE_SIZE; i++, j+=2)
   {
      if(NVR.CylSize == SIZE2_0)            // 
         temp=DefForce2in[i]; // 32 bits
      else           /* default to 3in cylinder */ 
         temp=DefForce3in[i]; // 32 bits
      LsbData= (UINT16)(temp & 0x0FFFF); // Isolated the LSB part
      NVR.DefForce[i]=temp;
     
      temp= (temp & 0x0FFFF0000); // Isolated the MSB part
      MsbData= (UINT16)(temp >> 16);
        
      NVRWriteVerify(LsbData, j+Address);  // Data, Address
      NVRWriteVerify(MsbData, j+Address+1);  // Data, Address
   }

   NVRCommandEWDS();  // disable novram
}



void SetForceNVR(void)
{                                         
   UINT32 temp=0;                                          
   UINT16 LsbData=0;
   UINT16 MsbData=0;
   UINT16 i=0;
   UINT16 j=0;

   UINT16 Address=0x82;
      
   NVRWriteSetup();

   for(i=0, j=0; i< FORCE_TABLE_SIZE; i++, j+=2)
   {
      temp=NVR.Force[i]; // 32 bits
      LsbData= (UINT16)(temp & 0x0FFFF); // Isolated the LSB part
     
      temp= (temp & 0x0FFFF0000); // Isolated the MSB part
      MsbData= (UINT16)(temp >> 16);
   
      NVRWriteVerify(LsbData, j+Address);  // Data, Address
      NVRWriteVerify(MsbData, j+Address+1);  // Data, Address
   }

   NVRCommandEWDS();  
}



void NVRWriteEWEN(void)
//------------------------------------------------------------------------
// Performs actual write of EWEN bit, assuming QSPI configuration is
// already correct.
//------------------------------------------------------------------------
{
   QsmMap->TxdData[13] = EWEN;       // Enable/Disable a  write 
   QsmMap->Spcr1.Dtl   = DELAY_ACT_NOVRAM;
   QsmMap->Spcr1.Spe   = 1;          // "Send"
   OneMilTimer = 0;
   while(OneMilTimer<20){};          // write time delay
}



//------------------------------------------------------------------------ 
// NVRCommandEWDS: This function disables a write to the NovRam
//------------------------------------------------------------------------
void NVRCommandEWDS(void)
{
   Init1();
   QsmMap->TxdData[13] = ACTRAMDISABLE;    /* Disable a  write */
   QsmMap->Spcr1.Dtl   = DELAY_ACT_NOVRAM;
   QsmMap->Spcr1.Spe   = 1;       // "Send"
   OneMilTimer = 0;
   while(OneMilTimer < 20) { };
   InitBarGraph();

   NovramEnable = FALSE;
}



void NVRWriteSetup(void)
/****************************************************************************/
/*                                                                          */
/* Configures the QSPI for writes to the Novram. Also enables writes to the */
/* Novram. This function should be called before NVRWriteVerify() and       */
/* WriteNovram(). Note that NVRCommandEWDS() should be called after writes  */
/* are finished to reset to QSPI configuration.                             */
/*                                                                          */
/****************************************************************************/
{
   NovramEnable=TRUE;
   OneMilTimer = 0;
   while(OneMilTimer<5){};

   Init1();          /* Enable writes to the Novram */
   NVRWriteEWEN();
   Init3();          /* Configure QSPI for future writes */
}



void NVRWriteVerify( UINT16 Data, UINT16 Address)
/****************************************************************************/
/*                                                                          */
/* Writes the Data to the indicated Address of the Novram, reads the data   */
/* back and verifies that it was written correctly. Writes multiple times   */
/* until MAX_ACTNVRAM_RETRIES attempted or until data is read back          */
/* properly.                                                                */
/*                                                                          */
/****************************************************************************/
{
   UINT8  RetryCount;
   UINT16 ReadBack;

   RetryCount = 0;

   do
   {
      NVRWriteNovram( Data, Address );
      ReadBack = ReadNVR( Address );
      RetryCount++;
      GlobalRetryCounter++;
   } while ((Data != ReadBack) && (RetryCount < MAX_ACTNVRAM_RETRIES));

   if ((Data != ReadBack)&&(Address != AE_VERIFY_ADDR)){
      RecordErrorCode( ERRORCODE60_EQ10 );
      RecordAlarm( EQ10 );    /* Actuator Novram alarm, couldn't write */
   }
}



void NVRWriteNovram( UINT16 Data, UINT16 Address)
/****************************************************************************/
/*                                                                          */
/* Performs a three-word write to actuator Novram.  Use this function only  */
/* if configuration of QSPI already set up, as in the middle of a series of */
/* transfers.                                                               */
/*                                                                          */
/****************************************************************************/
{
   QsmMap->TxdData[13] = PREWRITE | Address;  // Write 3* 12bits
   QsmMap->TxdData[14] = (Data >> 4);
   QsmMap->TxdData[15] = (Data << 8);
   QsmMap->Spcr1.Dtl   = DELAY_ACT_NOVRAM;
   QsmMap->Spcr1.Spe = 1;                     // Send 
   OneMilTimer = 0;
   while(OneMilTimer<20){};
}



UINT16 ReadNVR(UINT16 Address)
//------------------------------------------------------------------------
//  ReadNVR: This function returns a 16 bit data from a given address
//
//  NOTE: Assumes QSPI configuration is already set up
//------------------------------------------------------------------------
{
   UINT16 Readtemp1;
   UINT16 Readtemp2;

   QsmMap->TxdData[13] = Address|PREREAD;
   QsmMap->TxdData[14] = 0;
   QsmMap->TxdData[15] = 0;
   QsmMap->Spcr1.Dtl   = DELAY_ACT_NOVRAM;
   QsmMap->Spcr1.Spe   = 1;       // "Send"
   OneMilTimer = 0;
   while(OneMilTimer < 20) {};
   Readtemp1=((QsmMap->RxdData[14]) << 5); 
   Readtemp2=((QsmMap->RxdData[15]) >> 7); 
   return(Readtemp1|Readtemp2);
}



void Init1(void){
  
   QsmMap->ContRam[13].Cont = 0;  // chip select held low 
   QsmMap->ContRam[13].Bitse= 1;  // 12 bits per transfer 
   QsmMap->ContRam[13].Dt   = 1;  // Delay after transfer 
   QsmMap->ContRam[13].Dsck = 1;  // SPCR1 specifies value of delay 
   QsmMap->ContRam[13].Pcs  = 5;  // Peripheral Chip Select 
   QsmMap->Spcr0.Cpol  =  0;      // Rising/Falling
   QsmMap->Spcr0.Cpha  =  0;
   QsmMap->Spcr0.Spbr  = ACTBAUDRATE;      
   QsmMap->Spcr0.Bits  = 12;      // Number of bits per transfer 
   QsmMap->Spcr1.Dsckl =  5;
   QsmMap->Spcr2.Newqp = 13;
   QsmMap->Spcr2.Endqp = 13;
}



void Init3(void){

   QsmMap->ContRam[13].Cont  = 1; // chip select held low
   QsmMap->ContRam[13].Bitse = 1; // User Defined bits per transfer 
   QsmMap->ContRam[13].Dt    = 1; // Delay after transfer 
   QsmMap->ContRam[13].Dsck  = 1; // SPCR1 specifies value of delay PCS valid to SCK     
   QsmMap->ContRam[13].Pcs   = 5; // Peripheral Chip Select 
   QsmMap->ContRam[14].Cont  = 1; // return chip select high after transfer
   QsmMap->ContRam[14].Bitse = 1; // User Defined bits per transfer 
   QsmMap->ContRam[14].Dt    = 1; // Delay after transfer 
   QsmMap->ContRam[14].Dsck  = 1; // SPCR1 specifies value of delay PCS valid to SCK     
   QsmMap->ContRam[14].Pcs   = 5; // Peripheral Chip Select 
   QsmMap->ContRam[15].Cont  = 0; // chip select held low 
   QsmMap->ContRam[15].Bitse = 1; // 12 bits per transfer 
   QsmMap->ContRam[15].Dt    = 1; // Delay after transfer 
   QsmMap->ContRam[15].Dsck  = 1; // SPCR1 specifies value of delay 
   QsmMap->ContRam[15].Pcs   = 5; // Peripheral Chip Select 
   QsmMap->Spcr0.Cpol  =  0;
   QsmMap->Spcr0.Cpha  =  0;
   QsmMap->Spcr0.Spbr  = ACTBAUDRATE;
   QsmMap->Spcr0.Bits  = 12;      // Number of bits per transfer 
   QsmMap->Spcr1.Dsckl =  5;
   QsmMap->Spcr2.Newqp = 13;      // 36 bit transfer
   QsmMap->Spcr2.Endqp = 15;
}


// ------------------------------------------------------------------------
// This function copys the Current pressure table, which is in the 
// CurrentSetup, to the NovRam.  
// ------------------------------------------------------------------------

void SetPressure(void)        // You want to update CurrentSetup first
{
   UINT16 Address=0x77;       // with the a new pressure table, before you 
   UINT16 i=0;                // call to this function.

   NVRWriteSetup();

   for(i=0; i<11; i++){
      NVRWriteVerify(NVR.Pressure[i], Address++);
   }

   NVRCommandEWDS();
}


//------------------------------------------------------------------------
//
// This function sets the default pressure
//
//------------------------------------------------------------------------

void SetDefPressure(void)
{
   UINT16 Address=0x0027;
   UINT16 i=0;

   NVRWriteSetup();

   for(i=0; i<11; i++)
   {
      NVRWriteVerify(DefPress[i], Address++); // (Data, Address)
      NVR.DefPressure[i]=DefPress[i];  
   }

   NVRCommandEWDS();  
}  



void SetDefLoadCell(void)
/* Load the flash defaults into the Actuator novram, check if SBEAM or Loadcell */
{
   UINT16 Address=0x001C;
   UINT16 i=0;

   NVRWriteSetup();

   for(i=0; i<11; i++)
   {
      if(NVR.ForceGauge == LOAD_CELL)
      {
         switch (NVR.ActId) {
            case NVR_AED:
               NVRWriteVerify(AEDDefLoad[i], Address++); // (Data, Address)
               NVR.DefLoadCell[i]=AEDDefLoad[i];  
            break;   

            case NVR_AEF:
               NVRWriteVerify(AEFDefLoad[i], Address++); // (Data, Address)
               NVR.DefLoadCell[i]=AEFDefLoad[i];  
            break;   
         }  
      }
      else /* SBeam */
      {
			switch (NVR.ActId) {
            case NVR_MICRO:
               if(GetEncoderType()== ENCODER_ENGLISH)//2000X micro std prod
               {
                  NVRWriteVerify(DefSBeam[i], Address++); // (Data, Address)
					   NVR.DefLoadCell[i]=DefSBeam[i];
               }
               else//2000X micro special
               {
                  NVRWriteVerify(MICRODefLoad[i], Address++); // (Data, Address)
                  NVR.DefLoadCell[i]=MICRODefLoad[i]; 
               }
            break;
				
				default:
					NVRWriteVerify(DefSBeam[i], Address++); // (Data, Address)
					NVR.DefLoadCell[i]=DefSBeam[i];
				break;
			}
      }   
                                   
   }

   NVRCommandEWDS();  
}



/********************************************************************/
void GetDefPressure(void)
{
   int i;
   
   for(i=0; i<11; i++)
      NVR.Pressure[i]=NVR.DefPressure[i];
}      


           
void GetDefLoadCell(void)
{
   int i;
   
   for(i=0; i<11; i++)
      NVR.LoadCell[i]=NVR.DefLoadCell[i];
}      



void GetDefForce(void)
{
   int i;
   
   for(i=0; i< FORCE_TABLE_SIZE; i++)
      NVR.Force[i]=NVR.DefForce[i];
}


void GetDefCalStrokeLen(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when resetting Calibration                       */
/*                                                                          */
/****************************************************************************/ 
{
   NVR.CalStrokeLen = NVR.DefCalStrokeLen;
}   

void GetDefHomeOffset(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when resetting Calibration                       */
/*                                                                          */
/****************************************************************************/ 
{
   NVR.CalHomeOffset = NVR.DefCalHomeOffset;
}   



void UpdateDefPressure(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from the Branson menu after Calibration is run   */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Address=0x0027;
   UINT16 i;

   NVRWriteSetup();

   for(i=0; i<11; i++)
   {
      NVRWriteVerify(NVR.Pressure[i], Address++); // (Data, Address)
      NVR.DefPressure[i]=NVR.Pressure[i];  
   }

   NVRCommandEWDS();  
}



void UpdateDefLoadCell(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from the Branson menu after Calibration is run   */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Address=0x001C;
   UINT16 i;

   NVRWriteSetup();

   for(i=0; i<11; i++)
   {
      NVRWriteVerify(NVR.LoadCell[i], Address++); // (Data, Address)
      NVR.DefLoadCell[i]=NVR.LoadCell[i];  
   }

   NVRCommandEWDS();  
}



SINT32 GetMaxForce(void)
/****************************************************************************/
/* This function returns max. weld force for given actuator type and size   */
/* at appropriate pressure applied                                          */
/*                                                                          */
/****************************************************************************/
{
   SINT32 TempMax=0;
   
   if (NVR.ActId==NVR_MICRO)
   {
      TempMax=AED_MAXFORCE_40MM;/* Force micro to 40 mm cylinder */    
   }
   else if (NVR.ActId==NVR_AED)
   {
      switch(NVR.CylSize)
      {            
         case SIZE1_5:  
            TempMax=AED_MAXFORCE_1_5IN;    
            break;
                 
         case SIZE2_0:
            TempMax=AED_MAXFORCE_2_0IN;    
            break;
              
         case SIZE2_5:
            TempMax=AED_MAXFORCE_2_5IN;   
            break;
                      
         case SIZE3_0:
            TempMax=AED_MAXFORCE_3_0IN;   
            break;
                 
         case SIZE3_25:
            TempMax=AED_MAXFORCE_3_25IN;   
            break;
              
         case SIZE4_0:
            TempMax=AED_MAXFORCE_4_0IN;   
            break;
              
         case SIZE_40:
            TempMax=AED_MAXFORCE_40MM;     
            break;
              
         case SIZE_50:
            TempMax=AED_MAXFORCE_50MM;     
            break;
              
         case SIZE_63:
            TempMax=AED_MAXFORCE_63MM;     
            break;
              
         case SIZE_80:
            TempMax=AED_MAXFORCE_80MM;     
            break;
              
         default:                               /* In case of an Error */
            TempMax=AED_MAXFORCE_CUSTOM;        /* For MAX Custom  */
            break;   
      }
   }
   else if (NVR.ActId==NVR_AEF)
   {
      if (CurrentPreset.SetPressure)
      {                                        /* 80psi case */
         switch(NVR.CylSize){             
            case SIZE1_5:
            case SIZE_40:
               TempMax=AEF_MAXFORCE_1_5IN_80PSI;    
               break;
                  
            case SIZE2_0:
            case SIZE_50:
               TempMax=AEF_MAXFORCE_2_0IN_80PSI;    
               break;
               
            case SIZE2_5:
            case SIZE_63:
               TempMax=AEF_MAXFORCE_2_5IN_80PSI;    
               break;
                       
            case SIZE3_0:
               TempMax=AEF_MAXFORCE_3_0IN_80PSI;    
               break;
                  
            case SIZE3_25:
            case SIZE_80:
               TempMax=AEF_MAXFORCE_3_25IN_80PSI;    
               break;
               
            case SIZE4_0:
               TempMax=AEF_MAXFORCE_4_0IN_80PSI;    
               break;
               
            default:                                       /* In case of an Error */
               TempMax=AEF_MAXFORCE_CUSTOM_80PSI;          /* For MAX Custom      */
               break;   
         }
      }                   
      else
      {                                                    /* 60psi case */
         switch(NVR.CylSize)
         {             
            case SIZE1_5:  
            case SIZE_40:
               TempMax=AEF_MAXFORCE_1_5IN_60PSI;    
               break; 
                 
            case SIZE2_0:
            case SIZE_50:
               TempMax=AEF_MAXFORCE_2_0IN_60PSI;    
               break;
               
            case SIZE2_5:
            case SIZE_63:
               TempMax=AEF_MAXFORCE_2_5IN_60PSI;    
               break;        
               
            case SIZE3_0:
               TempMax=AEF_MAXFORCE_3_0IN_60PSI;    
               break;   
               
            case SIZE3_25:
            case SIZE_80:
               TempMax=AEF_MAXFORCE_3_25IN_60PSI;    
               break;
               
            case SIZE4_0:
               TempMax=AEF_MAXFORCE_4_0IN_60PSI;    
               break;
               
            default:                                       /* In case of an Error   */
               TempMax=AEF_MAXFORCE_CUSTOM_60PSI;          /* For MAX Custom        */
               break;   
         }
      }
   }
   return (TempMax);
}



//------------------------------------------------------------------------
// This Function returnes a TRUE if the data in NVRAM is valid
// IT CHECKS if: Actuator Id, StrokeLength, CylSize have valid values.
//               For AED, also checks serial #, LoadCell table.
//
// Note: For AE there is no Novram, so NVR structure should have been
//       manually filled in with something reasonable before calling this
//       function.
//
//------------------------------------------------------------------------

BOOLEAN CheckNvrValid(void)
{
   BOOLEAN Valid=FALSE;
   UINT16 i=0;
   
   if( (NVR.ActId==NVR_AED)||(NVR.ActId==NVR_AEF)||(NVR.ActId==NVR_MICRO))  // Testing Actuator Id
   {
      Valid=TRUE;
   }
   switch(NVR.StrokeLength)
   {
      case LENGTH_4:
         break;
      case LENGTH_5:
         break;
      case LENGTH_6:
         break;
      case LENGTH_2:
         break;
      case LENGTH_8:
         break;
      case LENGTH_80:
         break;
      case LENGTH_100:
         break;
      case LENGTH_125:
         break;
      /*case LENGTH_160:
         break;*/
      case LENGTH_50:
         break;
      case CUSTOMLEN:
         break;
      default:
         RecordErrorCode( ERRORCODE30_EQ10 );
         Valid=FALSE;
         break;
   }
   switch(NVR.CylSize)
   {
      case CUSTOMSIZE:
         break;
      case SIZE1_5:
         break;
      case SIZE2_0:
         break;
      case SIZE2_5:
         break;
      case SIZE3_0:
         break;
      case SIZE3_25:
         break;
      case SIZE4_0:
         break;
      case SIZE_40:
         break;
      case SIZE_50:
         break;
      case SIZE_63:
         break;
      case SIZE_80:
         break;
      default:
         RecordErrorCode( ERRORCODE20_EQ10 );
         Valid=FALSE;
         break;
   }
   if ((NVR.ActId == NVR_AED)||(NVR.ActId == NVR_AEF)||(NVR.ActId == NVR_MICRO))
   {
      for(i=0; i< (MAXSERIALNUM - 1); i++)  // Ascii can't be more than 128; Testing Serial Number
      {
         if((NVR.SerNum[i] > 127) || (NVR.SerNum[i] < ' '))
         {
            RecordErrorCode( ERRORCODE10_EQ10 );
            Valid=FALSE;
         }
      }
      for(i=1; i<11; i++)  // Each next element has to be larger than its previous
      {
         if(NVR.LoadCell[i] <= NVR.LoadCell[i-1])
         {
            RecordErrorCode( ERRORCODE50_EQ10 );
            Valid=FALSE;
         }
         if(NVR.Pressure[i] <= NVR.Pressure[i-1])
         {
            RecordErrorCode( ERRORCODE40_EQ10 );
            Valid=FALSE;
         }
      }                                   
   }
   return(Valid);
}



BOOLEAN CheckForActChange(void)
// -------------------------------------------------------------------------
// Compares current actuator type, as read from EEPROM on actuator, to
// contents of CurrentSetup, which should contain type of previous actuator.
// If actuator has changed, records appropriate alarms.
// -------------------------------------------------------------------------
{
   BOOLEAN Changed=FALSE;
   UINT16 i=0;

   if(CurrentSetup.Actuator!=GetActId())   /* See if type has changed */
   {
      Changed = TRUE;
      CurrentSetup.Actuator = GetActId();

      if ( (CurrentSetup.Actuator == AED)||(CurrentSetup.Actuator == MICRO) )
      {
         if (CurrentSetup.ControlLevel < LEVEL_d)
         {
            RecordAlarm(EQ14);   /* Wrong Actuator */
            ClearReady();
         }
         else
         {
            RecordAlarm(EQ24);   /* Actuator Type */
            RecordErrorCode( ERRORCODE600_EQ20 );
            RecordAlarm(EQ20);   /* Recalibrate Actuator */
         }
      }
      else if (CurrentSetup.Actuator == AEF)
      {
         if (CurrentSetup.ControlLevel < LEVEL_f)
         {
            RecordAlarm(EQ14);   /* Wrong Actuator */
            ClearReady();
         }
         else 
         {  
            RecordAlarm(EQ24);      /* Actuator Type */
            RecordErrorCode( ERRORCODE600_EQ20 );
            RecordAlarm(EQ20);   /* Recalibrate Actuator */
         }
      } 
      else 
         RecordAlarm(EQ24);   /* Actuator Type */
          
      /* Changing from non-AE to AE, set stroke length & cyl size to */
      /* defaults for AE. Changing AE to non-AE, set up min/max. */

      CurrentSetup.StrokeLen =  GetStrokeLength();
      CurrentSetup.CylinDiameter = GetCylSize();
      SetMaxMinValues();

   }
   else if (CurrentSetup.Actuator != AE)  /* Same type, but check serial #s */
   {
      if (((CurrentSetup.Actuator == AED) && (CurrentSetup.ControlLevel < LEVEL_d))||
          ((CurrentSetup.Actuator == MICRO) && (CurrentSetup.ControlLevel < LEVEL_d))||
          ((CurrentSetup.Actuator == AEF) && (CurrentSetup.ControlLevel < LEVEL_f)))
      {   
         RecordAlarm(EQ14);   /* Wrong Actuator */
         ClearReady();
      }
      else
         {
         for(i=0; i<MAXSERIALNUM && !Changed; i++)
         {
            if(NVR.SerNum[i] != (UINT16)CurrentSetup.ActSerialNumber[i])
               Changed=TRUE;
         }

         if (Changed)
         {
            RecordErrorCode( ERRORCODE100_EQ20 );
            RecordAlarm(EQ20);   /* Recalibrate Actuator */
         }
      }   
   }
   else     /* was AE before, is AE now */
   {
      /* NVR structure was filled in with defaults for AE, since AE has no */
      /* Novram.  Here we just make sure NVR matches CurrentSetup, in case */
      /* anybody looks at NVR. */

      NVR.StrokeLength = CurrentSetup.StrokeLen;
      NVR.CylSize = CurrentSetup.CylinDiameter;
   }

   if ( (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == AED) ||    /* Set up these all the time, just */
        (CurrentSetup.Actuator == MICRO) )
   {
      
      /* If stroke length or cylinder size changed with this actuator, */
      /* update CurrentSetup and adjust max/min settings. */

      if (CurrentSetup.StrokeLen != GetStrokeLength() ||
       CurrentSetup.CylinDiameter != GetCylSize())
      {
         CurrentSetup.StrokeLen =  GetStrokeLength();
         CurrentSetup.CylinDiameter = GetCylSize();
         SetMaxMinValues();
      }
      // Update Encoder Settings
     /* if(CurrentSetup.Actuator == MICRO)
      {
         if(CurrentSetup.USEncoder!=TRUE) 
            EnableUSEncoder();
      }*/
   }
   if (CurrentSetup.Actuator == AEF)
   {
      BuildVelocityTable();
   }
   if(Changed==TRUE)
   {
      // Update Encoder Settings 
      if ( (CurrentSetup.Actuator == AEF) ||
          (CurrentSetup.Actuator == AED))
       {
          EnableMetricEncoder();
       }
       else if(CurrentSetup.Actuator == MICRO)
       {
          if(CurrentSetup.USEncoder!=TRUE) 
            EnableUSEncoder();
       }
   }
   switch (CurrentSetup.Actuator) {
      case AE :
         for(i = 0; i < MAXSERIALNUM; i++) {
            CurrentSetup.ActSerialNumber[i] = ' ';
         }   
         CurrentSetup.ActSerialNumber[i] = NULL;  /* CurrentSetup is bigger than */
         break;                                   /* MAXSERNUM, so room for NULL */

      case AED :
      case MICRO :
      case AEF :
         for(i = 0; i < MAXSERIALNUM; i++) {
            CurrentSetup.ActSerialNumber[i] = NVR.SerNum[i];
         }   
         CurrentSetup.ActSerialNumber[i] = NULL;  /* CurrentSetup is bigger than */
         break;                                   /* MAXSERNUM, so room for NULL */

      default :
         for(i = 0; i < MAXSERIALNUM; i++) {
            CurrentSetup.ActSerialNumber[i] = "Bad act.  "[i];
         }
         CurrentSetup.ActSerialNumber[i] = NULL;  /* CurrentSetup is bigger than */
                                                  /* MAXSERNUM, so room for NULL */
   }
   return (Changed);
}



void InitSetupFromAct(void)
// -------------------------------------------------------------------------
// To Recover in case of a problem in the BBR, the following code copies
// ActuatorId, StrokeLength, CylinderSize, and SerialNumber from act Novram.
// -------------------------------------------------------------------------
{
   UINT16 i=0;

   CurrentSetup.Actuator = GetActId();
   CurrentSetup.StrokeLen = NVR.StrokeLength;
   CurrentSetup.CylinDiameter = NVR.CylSize;
   for(i=0; i< MAXSERIALNUM; i++) {
      CurrentSetup.ActSerialNumber[i]=NVR.SerNum[i];
   }
   CurrentSetup.ActSerialNumber[i] = NULL;  /* CurrentSetup is bigger than */
                                            /* MAXSERNUM, so room for NULL */
}



void ActRecover(void)
//------------------------------------------------------------------------
//    Sets NVR structure to known, reasonable values in the event that
//    actuator Novram either doesn't exist or has invalid information.
//    Note that since these "reasonable" values are not written to EEPROM,
//    they will be lost at power-off.
//
//
//------------------------------------------------------------------------
{
   if ((NVR.ActId!=NVR_AED)&&(NVR.ActId!=NVR_AEF)&&(NVR.ActId!=NVR_MICRO))
      NVR.ActId = NVR_AE;
   
   if(NVR.ActId==NVR_MICRO)
   {
      if(GetEncoderType()==ENCODER_ENGLISH)//2000X micro std prod
         NVR.StrokeLength = LENGTH_50;
      else
         NVR.StrokeLength = LENGTH_2;//2000X micro special
      
      NVR.CylSize=SIZE_40;

   }
   else
   {
      NVR.StrokeLength = LENGTH_4;
      NVR.CylSize = SIZE3_0;
   }

}



UINT16 ActNovramExists(void)
/****************************************************************************/
/*                                                                          */
/* This function returns 1 if it's an AED/F actuator, 0 for an AE. First,   */
/* it attempts to read the actuator ID from Novram. If a valid ID comes     */
/* back, then we assume the Novram exists. If not, then we might have a     */
/* blank Novram, so we try to write to it. If we get back what we wrote,    */
/* then we have Novram, otherwise we don't.                                 */
/*                                                                          */
/* NOTE: QSPI configuration must already be set up (for 3-word xfers),      */
/*       though Novram writes need not be enabled. Function exits with the  */
/*       same configuration as on entry, but Novram writes will be turned   */
/*       off.                                                               */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Val=0;   
   UINT16 TestValue = 0x55AA;

   NVR.ActId=ReadNVR(0);       // First, see if this looks valid
   NVR.ActId=ReadNVR(0);       // Read twice in case first read no good

   if((NVR.ActId!=NVR_AED)&&(NVR.ActId!=NVR_AEF)&&(NVR.ActId!=NVR_MICRO)) 
   {
      NVRWriteSetup();
      NVRWriteVerify(TestValue, AE_VERIFY_ADDR);

      
      Val=ReadNVR(AE_VERIFY_ADDR);

      if(Val==TestValue) // It's an AED; there is a chunk of memory to write to.
         Val=1;
      else
         Val=0;

      Init1();          /* Disable writes again */
      QsmMap->TxdData[13] = ACTRAMDISABLE;
      QsmMap->Spcr1.Dtl   = DELAY_ACT_NOVRAM;
      QsmMap->Spcr1.Spe   = 1;
      OneMilTimer = 0;
      while(OneMilTimer < 20) { };
      Init3();          /* Back to original configuration */
   }
   else
      Val=1;   // Got valid act ID, assume we have Novram.

   return (Val);
}



/***---  Test functions  ---***/

void TestWriteToNvram(void)
/***************************************************************************/
/*                                                                         */
/*  This function will write an incrementing number into the actuator      */
/*  novram.  This will wipe out the novram completely.                     */
/*                                                                         */
/***************************************************************************/
{
   UINT16 i;
   UINT16 Val=0;

   NVRWriteSetup();

   for(i=0; i< 0xff; i++)
   {
      NVRWriteVerify(i,i);
   }
}



void TestReadFromNvram(void)
/***************************************************************************/
/*                                                                         */
/*  This function will read from the novram.  It expects to read the       */
/*  incrementing number that TestWriteToNvram() wrote.  If an error is     */
/*  discovered the variable ChecksumRet will contain the last address      */
/*  that was in error.                                                     */
/*                                                                         */
/***************************************************************************/
{
   UINT16 i;
   UINT16 Val=0;
   
   ChecksumRet = 0;
   for(i=0; i< 0xff; i++)
   {
      Val=ReadNVR(i);
      if (Val != i) {
        ChecksumRet = i;                   /* A place to put a breakpoint */
      }  
   }
}

/***---  End of Test functions  ---***/


// ----------------------------------------------------------------------
// This function Copys the default side of the NovRam to its non. 
// You want to use it, probably, only once on serial # initialization.
// ex: Default Cylinder Size --> Cylinder Size.
// ----------------------------------------------------------------------

void NvrCopyDeftoNon(void)
{
   UINT16 i;
   UINT16 Val=0;

   NVRWriteSetup();

   for(i=3; i< 0x53; i++)
   {
      Val=ReadNVR(i);
      NVRWriteVerify(Val, (i+0x50));
   }

   NVRCommandEWDS();
}



void SetCalibPass(UINT16 Val)
{
   UINT16 Address=0xA4;

   NVRWriteSetup();
   NVRWriteVerify(Val, Address);
   NVR.CalibPass=Val;
   NVRCommandEWDS();
}



UINT16 GetCalibPass(void)
{
   return(NVR.CalibPass);
}



void SetCalibrationDate(UINT16 *Ptr)
{                                          // 0 Month
   UINT16 Address=0x69;                    // 1 Day
   UINT16 i=0;                             // 2 Year

   NVRWriteSetup();

   for(i=0; i<3; i++)
   {
      NVRWriteVerify(Ptr[i], i+Address);
      NVR.CalDate[i]=Ptr[i];
   }

   NVRCommandEWDS();
}



void SetDefCalibDate(UINT16 *Ptr)          
/****************************************************************************/ 
/*                                                                          */
/* This function is called form the system information screen, when update  */
/* calibrate tables is selected                                             */
/*                                                                          */
/* Outputs : NVR.DefCalDate 0 = Month, 1 = Day, 2 = Year                    */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Address= DEFCALDATE;                    
   UINT16 i=0;                             

   NVRWriteSetup();

   for(i=0; i<3; i++)
   {
      NVRWriteVerify(Ptr[i], i+Address);
      NVR.DefCalDate[i]=Ptr[i];
   }
   NVRCommandEWDS();
}



void UpdateCylinderFactor(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called at power up and EStop. It updates the cylinder   */
/* and velocity table                                                       */
/* Outputs : CylinderFactor                                                 */
/*                                                                          */
/****************************************************************************/ 
{
   switch(NVR.CylSize)
   {
      case SIZE1_5:
         ForceTableCylFactor = FORCEFACTORSIZE1_5;
         VelocityTableCylFactor = VELFACTORSIZE1_5;
         break;
      case SIZE2_0:                                                       
         ForceTableCylFactor = FORCEFACTORSIZE2_0;
         VelocityTableCylFactor = VELFACTORSIZE2_0;
         break;                                                      
      case SIZE2_5:                                                  
         ForceTableCylFactor = FORCEFACTORSIZE2_5;
         VelocityTableCylFactor = VELFACTORSIZE2_5;
         break;                                                      
      case SIZE3_0:                                                  
         ForceTableCylFactor = FORCEFACTORSIZE3_0;
         VelocityTableCylFactor = VELFACTORSIZE3_0;
         break;                                                      
      case SIZE3_25:                                                 
         ForceTableCylFactor = FORCEFACTORSIZE3_25;
         VelocityTableCylFactor = VELFACTORSIZE3_25;
         break;                                                      
      case SIZE4_0:                                                 
         ForceTableCylFactor = FORCEFACTORSIZE4_0;
         VelocityTableCylFactor = VELFACTORSIZE4_0;
         break;                                                      
      case SIZE_40:
         ForceTableCylFactor = FORCEFACTORSIZE_40;
         VelocityTableCylFactor = VELFACTORSIZE_40;
         break;                                                      
      case SIZE_50:                                                  
         ForceTableCylFactor = FORCEFACTORSIZE_50;
         VelocityTableCylFactor = VELFACTORSIZE_50;
         break;
      case SIZE_63:
         ForceTableCylFactor = FORCEFACTORSIZE_63;
         VelocityTableCylFactor = VELFACTORSIZE_63;
         break;
      case SIZE_80:
         ForceTableCylFactor = FORCEFACTORSIZE_80;
         VelocityTableCylFactor = VELFACTORSIZE_80;
         break;
      default:
         ForceTableCylFactor = FORCEFACTORSIZE3_0;
         VelocityTableCylFactor = VELFACTORSIZE3_0;
         break;
   }  
}



UINT16 GetDefSpringRateSlope(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from UpdateNVRDefSpringRate.                     */
/*                                                                          */
/* Outputs: NVR.DefSpringRateSlope used before sensor calibration is done,  */
/*          during a checksum,  or when resetting calibration tables        */
/****************************************************************************/ 
{
   
   NVR.SpringRateSlope = NVR.DefSpringRateSlope;
   return(NVR.SpringRateSlope);
}



void GetDefCalSysPressure(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when resetting calibration tables                */
/*                                                                          */
/****************************************************************************/ 
{
   
   NVR.CalSysPressure = NVR.DefCalSysPressure;
}



void SetDefSpringRateSlope(UINT16 Data)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from UpdateNVRDefSpringRate.                      */
/*                                                                          */
/* Outputs: NVR.DefSpringRateSlope used before sensor calibration is done or*/
/*          when resetting calibration tables                               */
/****************************************************************************/ 
{
   NVRWriteSetup();
   NVRWriteVerify((UINT16)Data, 0x42);
   NVR.DefSpringRateSlope = Data;
   NVRCommandEWDS();  
}



void SetCalSpringRateSlope(UINT16 Data)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from Sensor Calibration.                         */
/*                                                                          */
/* Outputs: NVR.SpringRateSlope - used in sensor calibration and actuator   */
/*          calibration.                                                    */
/*                                                                          */
/****************************************************************************/ 
{
   NVRWriteSetup();
   NVRWriteVerify((UINT16)Data, 0x92);
   NVR.SpringRateSlope = Data;
   NVRCommandEWDS();  
}



void SetDefCalHomeOffset(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from UpdateNVRDefSpringRate.                     */
/*                                                                          */
/****************************************************************************/ 
{
   NVRWriteSetup();
   NVRWriteVerify(NVR.DefCalHomeOffset, 0x41);
   NVRCommandEWDS();  
}



void SetCalHomeOffset(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from Sensor Calibration.                         */
/*                                                                          */
/* Outputs: NVR.SpringRateSlope - used in sensor calibration and actuator   */
/*          calibration.                                                    */
/*                                                                          */
/****************************************************************************/ 
{
   NVRWriteSetup();
   NVRWriteVerify(NVR.CalHomeOffset, 0x91);
   NVRCommandEWDS();  
}

void SetForceGauge(UINT16 Type)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from the Branson menu.                           */
/*                                                                          */
/* Outputs: NVR.ForceGauge - Loadcell or SBeam.                             */
/*                                                                          */
/****************************************************************************/ 
{

   NVRWriteSetup();
   NVRWriteVerify(Type, 0xa6);
   NVR.ForceGauge = Type;
   NVRCommandEWDS();  
}


void UpdateDefSpringRateSlope(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from the Branson menu after Calibration is run   */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Address=0x042;
   
   NVRWriteSetup();
   NVRWriteVerify(NVR.SpringRateSlope, Address);
   NVR.DefSpringRateSlope=NVR.SpringRateSlope;
   NVRCommandEWDS();  
}

void SetEncoderType (enum ENCODER Data)
{
   NVRWriteSetup ();
   NVRWriteVerify (Data, ENCODER_ADDR);
   NVR.EncoderType=Data;
   NVRCommandEWDS (); 

}
