/* $Header:   D:/databases/VMdb/2000Series/App/PSNVRAM.C_V   1.36   13 Sep 2012 08:33:38   gbutron  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*        Copyright (c) Branson Ultrasonics Corporation, 1995,96            */
/*    This program is the property of Branson Ultrasonics Corporation       */
/*   Copying of this software is expressly forbidden, without the prior     */
/*         written consent of Branson Ultrasonics Corporation.              */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: psnvram.c

 ---------------------------- REVISIONS ------------------------------------

 Rev #        Date      Author    Description
 =====        ========  ======    ===========================================
 1.0          11/22/96   PhilJ    Initial Version
 1.1          12/27/96   PhilJ    Added NvramEnable flag
 1.2          06/13/97   PhilJ    Corrected warning in RecallPSNovram
 1.3          07/03/97   PhilJ    Deleted tm_wkafter PSOS function and
                                  added SerialTimer Delay.
 1.3          07/03/97   PhilJ    Deleted tm_wkafter PSOS function and
 1.4          07/03/97   PhilJ    Added default of ControlLevel to MODEL1
 1.5          07/03/97   PhilJ    Added default for PSFrequency & PSWatt
 1.6          07/08/97   PhilJ    Changed SerialTimer to OneMilTimer
 1.7          07-17-97   BEK      New function VerifyPSNovram
 1.8          09-12-97   BEK      Removed commented out code StorePSNovram
 1.9          09-25-97   LAM      moved initbargraph from sysmangr        
 1.10         10-03-97   LAM      added delay when switching queues       
 1.11         02-02-98   LAM      added actuator check to VerifyPSNovram
 1.12         03-30-98   LAM      added release2 define                 
 1.13         04-17-98   LAM      removed release2 define                 
 1.14         06.30.98   JB       Removed EQ14 call from this file, 
                                  using it in sysmangr.c; w/ CheckValidForRecovery.
 1.15         07-30-98   BJB      Modified VerifyPSNovram() to return alarm
                                  code instead of recording alarm; will be
                                  called before alarms can be recorded.
 1.16         11-09-98   BJB      Modified VerifyPSNovram() to check settings
                                  for 15KHz, 30KHz power supplies.
                                  Fixed default for PSWatts if 0 read from Novram.
 1.17         05-26-99   LAM      Modified VerifyPSNovram() to check for the power and
                                  frequency settings individually
 1.17.1.1     07-09-99   JZ       implemented switch(PSNvRamData.PSWatts) statement
 1.19         08-13-99   LAM      fixed QSPI timing for 24.6 Mhz clock
 1.20         08-19-99   JZ       corrected VerifyPSNovram function
 1.21         06-28-00   BEKymer  Changed all MODEL to LEVEL
 1.21         06-29-00   BEKymer  changed if function pertaining to MODEL to switch 
                                  statement reffering to LEVEl.
 1.22         07-13-00   BEK/DJL  removed all tabs.
 1.23         08-25-00   LAM      increased ps ser num to 12 chars
 1.24.1.1     06-11-01   BEKymer  Put test to determine if this is first power for board.
                                  If so, then initialize IsADepot, WasADepot counters and
                                  min/max values (ColdStartPlus).
 1.24.3.1     06-15-01   BEKymer  Instead of ColdStartPlus call FixBattRam.  Also force
                                  terninator for P/S serial number even if not in novram.
 1.24.3.2     06-27-01   BEKymer  changed 4400 Watts to 4000 Watts                               
 1.24.3.3     08-06-01   BEKymer  Initialized serial port to Compuweld when a new board is detected
 1.24.3.4     04-25-02   BEKymer  Add 6000 W to VerifyPSNovram()
 1.24.3.3.1.1 05-20-02   BEKymer  Create new function InitializeBBR()
 1.27         12-19-03   BEKymer  Move 1.24.3.3.1.1 to tip as 1.27 for Ver9.00c build
 1.28         05-07-04   LAM      merged with 8.22
 1.29         07-14-04   BEKymer  Added 200W to proper case
 1.30         07-27-04   JOY      Added FREQ60HZ check in VerifyPSNovram().
 1.31         09-15-04   BEKymer  Add user I/O and system controller to 
                                  InitializeBBR function 
 1.32         09-17-04   BEKymer  Better way to select new controller board
 1.33         10-24-05   Bwadia   PS Wattage check removed from VerifyPSNovran()
 1.34         01-11-08   NHAhmed  Some functions are replicated to a none argument type, 
                                  keeping all functionality same.
 1.35         09-12-08   NHAhmed  Updated function StorePSFrequency(). 
 1.36         09-13-12   GButron  Make the software works with 16/8bits PSNovram
                                 
 ---------------------------- DESCRIPTION -----------------------------------
    
   Functions:                                                                                                                              
       1. ReadPSData
       2. WritePSData                                                         
     
   PSNovram is 32 bytes X24C45 on PCS8 
   The NovramPS Structure -
       Model Number
       Actuator Type
       PS Wattage
       PS Freq
       PS Lifetime Counters
       PS Serial Number
       SW Version
      
   Read Structure from Novram at power up read. Then copy the data into bbram
   Write Structure to Novram when powering down write, store is automatic

                                    
 --------------------------- INCLUDE FILES ----------------------------------
*/
       
#include "portable.h"
#include "string.h"
#include "332.h"
#include "qsm.h"
#include "menu.h"
#include "psnvram.h"
#include "preset.h"
#include "ticks.h"
#include "alarms.h"
#include "ready.h"
#include "spidd.h"
#include "battram.h"
#include "command.h"
#include "sysmangr.h"
#include "snsrcalb.h"
#include "menu.h"


/*
 ------------------------------- GLOBAL DATA ------------------------------
                        (scope is global to ALL files)
*/

PSNOVRAMDATA PSNvRamData;
void UpdateDUPS_MaxWeldFreqLimit(void);
UINT16 OldNovramInstalledFlag=FALSE;                                       /* G Supposing the NEW PSNovram is installed. That's the reason for assigning the FALSE value to this flag */
UINT8 ModelNumberLowByte;
UINT8 ModelNumberHighByte;                                                 /* G For helping on detecting which Novram is installed on the system controller */
                                                                           /* G The control level code is read from the PSNovram and then assigned to this variable */

/* ------------------------- EXTERNAL DATA --------------------------------*/

extern UINT16 NovramFlag;
extern DEPOT_FLAGS  *DepotFlag;
extern UINT8  NovramEnable;
extern UINT16 OneMilTimer;
extern CONFIGSETUP   CurrentSetup;

/*
 ------------------------------ LOCAL DEFINES -----------------------------
*/                                                              

#define RELEASE2 1
/*                                      
 ------------------------------- LOCAL DATA -------------------------------
*/

/*
 ---------------------------------- CODE ----------------------------------
*/

void SendPSNvramCommand(UINT16 Command)
{
   if(OldNovramInstalledFlag==TRUE){                                       /* G If Old Novram is installed.*/
     QsmMap->ContRam[13].Cont = 0;                                         /* chip select held low */
     QsmMap->ContRam[13].Bitse = 0;                                        /* 8 bits per transfer */
     QsmMap->ContRam[13].Dt = 1;                                           /* Delay after transfer */
     QsmMap->ContRam[13].Dsck = 1;                                         /* SPCR1 specifies value of delay */
     QsmMap->ContRam[13].Pcs = 8;                                          /* Peripheral Chip Select */

     QsmMap->Spcr2.Newqp = 13;
     QsmMap->Spcr2.Endqp = 13;
     QsmMap->Spcr0.Cpol = 0;
     QsmMap->Spcr0.Cpha = 0;
     QsmMap->Spcr0.Spbr = 13;                                              /* 940kHz at 24.6Mhz */
     QsmMap->Spcr1.Dtl = 7;                                                /* length of delay after transfer */
     QsmMap->Spcr1.Dsckl = 8;
     QsmMap->TxdData[13] = (UINT8) Command;
     QsmMap->Spcr1.Spe = 1;                                                /* Enable Qspi */
   }
   else{                                                                   /* If New Novram is installed */                                                                     
     NovramFlag = TRUE;
     QsmMap->ContRam[12].Cont = 0;                                         /* chip select held low */
     QsmMap->ContRam[12].Bitse = 0;                                        /* 8 bits per transfer */
     QsmMap->ContRam[12].Dt = 1;                                           /* Delay after transfer */
     QsmMap->ContRam[12].Dsck = 1;                                         /* SPCR1 specifies value of delay */
     QsmMap->ContRam[12].Pcs = 8;                                          /* Peripheral Chip Select */

     QsmMap->Spcr2.Newqp = 12;
     QsmMap->Spcr2.Endqp = 12;
     QsmMap->Spcr0.Cpol = 0;
     QsmMap->Spcr0.Cpha = 0;
     QsmMap->Spcr0.Spbr = 13;                                              /* 940kHz at 24.6Mhz */
     QsmMap->Spcr1.Dtl = 7;                                                /* length of delay after transfer */
     QsmMap->Spcr1.Dsckl = 8;
     QsmMap->TxdData[12] = (UINT8) Command;
     QsmMap->Spcr1.Spe = 1;                                                /* Enable Qspi */
   }
}



void SetupPSComram(void)
{
                                                                           /* G Power Supply Novram read/write will be configured for 8 bits per transfer */ 
   if(OldNovramInstalledFlag==TRUE){                                       /* G If OLD Novram is installed, do the setup for transfer 3 bytes  */
     QsmMap->ContRam[13].Cont = 1;                                         /* chip select held low */
     QsmMap->ContRam[13].Bitse = 0;                                        /* 8 bits per transfer */
     QsmMap->ContRam[13].Dt = 1;                                           /* Delay after transfer */
     QsmMap->ContRam[13].Dsck = 1;                                         /* SPCR1 specifies value of delay */
                                                                           /* PCS valid to SCK */    
     QsmMap->ContRam[13].Pcs = 8;                                          /* Peripheral Chip Select */

     QsmMap->ContRam[14].Cont = 1;                                         /* return chip select high after
                                                                              transfer */
     QsmMap->ContRam[14].Bitse = 0;                                        /* 8 bits per transfer */
     QsmMap->ContRam[14].Dt = 1;                                           /* Delay after transfer */
     QsmMap->ContRam[14].Dsck = 1;                                         /* SPCR1 specifies value of delay */
                                                                           /* PCS valid to SCK */    
     QsmMap->ContRam[14].Pcs = 8;                                          /* Peripheral Chip Select */

     QsmMap->ContRam[15].Cont = 0;                                         /* return chip select high after
                                                                              transfer */
     QsmMap->ContRam[15].Bitse = 0;                                        /* 8 bits per transfer */
     QsmMap->ContRam[15].Dt = 1;                                           /* Delay after transfer */
     QsmMap->ContRam[15].Dsck = 1;                                         /* SPCR1 specifies value of delay */
                                                                           /* PCS valid to SCK */    
     QsmMap->ContRam[15].Pcs = 8;                                          /* Peripheral Chip Select */
   }
   else{                                                                   /* G If New Novram is installed, do the setup for tranfer 4 bytes */
     QsmMap->ContRam[12].Cont = 1;                                         /* G chip select held low during the 1st. byte transfer */                        
     QsmMap->ContRam[12].Bitse = 0;                                        /* G 8 bits per transfer */                                                       
     QsmMap->ContRam[12].Dt = 1;                                           /* G Delay after transfer */                                                      
     QsmMap->ContRam[12].Dsck = 1;                                         /* G SPCR1 specifies value of delay */                                            
                                                                           /* G PCS valid to SCK */                                                          
     QsmMap->ContRam[12].Pcs = 8;                                          /* G Peripheral Chip Select */                                                    
   
     QsmMap->ContRam[13].Cont = 1;                                         /* chip select still held low during the 2nd byte transfer */
     QsmMap->ContRam[13].Bitse = 0;                                        /* 8 bits per transfer */
     QsmMap->ContRam[13].Dt = 1;                                           /* Delay after transfer */
     QsmMap->ContRam[13].Dsck = 1;                                         /* SPCR1 specifies value of delay */
                                                                           /* PCS valid to SCK */    
     QsmMap->ContRam[13].Pcs = 8;                                          /* Peripheral Chip Select */
   
     QsmMap->ContRam[14].Cont = 1;                                         /* chip select still held low during the 3rd. byte transfer */
     QsmMap->ContRam[14].Bitse = 0;                                        /* 8 bits per transfer */
     QsmMap->ContRam[14].Dt = 1;                                           /* Delay after transfer */
     QsmMap->ContRam[14].Dsck = 1;                                         /* SPCR1 specifies value of delay */
                                                                           /* PCS valid to SCK */    
     QsmMap->ContRam[14].Pcs = 8;                                          /* Peripheral Chip Select */
   
     QsmMap->ContRam[15].Cont = 0;                                         /* return the chip select to high level after transfering the 4th. byte  */
     QsmMap->ContRam[15].Bitse = 0;                                        /* 8 bits per transfer */
     QsmMap->ContRam[15].Dt = 1;                                           /* Delay after transfer */
     QsmMap->ContRam[15].Dsck = 1;                                         /* SPCR1 specifies value of delay */
                                                                           /* PCS valid to SCK */    
     QsmMap->ContRam[15].Pcs = 8;                                          /* Peripheral Chip Select */
   }
}



void WritePSData(UINT16 WriteAddr, UINT16 Value)                           /* Writes the OLD Novram. It sends 3 bytes */
{
   QsmMap->Spcr2.Newqp = 13;
   QsmMap->Spcr2.Endqp = 15;
   QsmMap->Spcr0.Cpol = 0;
   QsmMap->Spcr0.Cpha = 0;
   QsmMap->Spcr1.Dtl = 7;                                                  /* length of delay after transfer */
   QsmMap->Spcr0.Spbr = 13;                                                /* 940kHz at 24.6Mhz */
   QsmMap->Spcr1.Dsckl = 8;

   QsmMap->TxdData[13] = WriteAddr; 
   QsmMap->TxdData[14] = (UINT8) Value;                                    /* Low order byte */
   Value >>= 8;                                                            /* High order byte */
   QsmMap->TxdData[15] = (UINT8) Value;                                    /* High order byte */
   QsmMap->Spcr1.Spe = 1;                                                  /* Enable Qspi */
}



void ReadPSData(UINT16 ReadAddr)                                           /* Reads the OLD Novram. Reads 2 bytes */
{
   QsmMap->Spcr2.Newqp = 13;
   QsmMap->Spcr2.Endqp = 15;
   QsmMap->Spcr0.Cpol = 0;
   QsmMap->Spcr0.Cpha = 0;
   QsmMap->Spcr1.Dtl = 7;                                                  /* length of delay after transfer */
   QsmMap->Spcr0.Spbr = 13;                                                /* 940kHz at 24.6Mhz */
   QsmMap->Spcr1.Dsckl = 8;

   QsmMap->TxdData[13] = (BYTE) ReadAddr;                                  /* read command + Address */
   QsmMap->TxdData[14] = (BYTE) ReadAddr;                                  /* read command + Address */
   QsmMap->TxdData[15] = (BYTE) ReadAddr;                                  /* read command + Address */
   QsmMap->Spcr1.Spe = 1;                                                  /* Enable Qspi */
}



void Setup2PSComram(void)                                                  /* G Added for writing 0x00h to the Status Register in the New Novram.[No block Memory write protection] */ 
{                                                                                                                                                                        
                                                                           /* G Power Supply Novram read/write will be configured for 8 bits per transfer */           
   QsmMap->ContRam[14].Cont = 1;                                           /* G chip select held "low" during the 1st. byte transfer */                                
   QsmMap->ContRam[14].Bitse = 0;                                          /* G 8 bits per transfer */                                                                 
   QsmMap->ContRam[14].Dt = 1;                                             /* G Delay after transfer */                                                                
   QsmMap->ContRam[14].Dsck = 1;                                           /* G SPCR1 specifies value of delay */                                                      
                                                                           /* G PCS valid to SCK */                                                                    
   QsmMap->ContRam[14].Pcs = 8;                                            /* G Peripheral Chip Select */                                                              
   QsmMap->ContRam[15].Cont = 0;                                           /* G return the chip select signal to high level After transfering the  2nd byte */         
   QsmMap->ContRam[15].Bitse = 0;                                          /* G 8 bits per transfer */                                                                 
   QsmMap->ContRam[15].Dt = 1;                                             /* G Delay after transfer */                                                                
   QsmMap->ContRam[15].Dsck = 1;                                           /* G SPCR1 specifies value of delay */                                                      
                                                                           /* G PCS valid to SCK */                                                                    
   QsmMap->ContRam[15].Pcs = 8;                                            /* G Peripheral Chip Select */                                                              
}



//void WritePSData(UINT16 WriteAddr, UINT16 Value)                         /* G Current */
void WritePSData2nd(UINT16 WriteOpCode, UINT16 WriteAddr,  UINT16 Value)   /* G Function for writing the New Novram. Write OpCode + Address + 16bits data (these 16 bits are splitted in 2 bytes) */ 
                                                                           /* G Before: "WriteAddr" included: 1 Startbit + 4addr bits + 3opcode bits [same variable] */
                                                                           /* G Now   :  The opcode and the address need to be separated, that's the reason for "WriteOpCode" and "WriteAddr" */
{
   // QsmMap->Spcr2.Newqp = 13;                                            /* G Current */                                                      
   NovramFlag = TRUE;
   QsmMap->Spcr2.Newqp = 12;                                               /* G Added */                                                      
                                                                           /* G This is the new Queue pointer value */
                                                                           /* G This field contains the 1st QSPI Queue address */
                                                                           /* G I Added it because of the additional "UINT16 WriteOpCode" in this function */
   QsmMap->Spcr2.Endqp = 15;                                               /* G Ending Queue pointer, Last QSPI Queue address */                        
   QsmMap->Spcr0.Cpol = 0;
   QsmMap->Spcr0.Cpha = 0;
   QsmMap->Spcr1.Dtl = 7;                                                  /* G length of delay after transfer */
   QsmMap->Spcr0.Spbr = 13;                                                /* G 940kHz at 24.6Mhz */
   QsmMap->Spcr1.Dsckl = 8;
   QsmMap->TxdData[12] = WriteOpCode;                                      /* G Added for transmitting the "OpCode",taking Only the LSB Byte */ 
   QsmMap->TxdData[13] = WriteAddr;                                        /* G Added for transmitting the "Address",taking Only the LSB Byte */ 
   QsmMap->TxdData[14] = (UINT8) Value;                                    /* G Low order byte */
   Value >>= 8;                                                            /* G High order byte */
   QsmMap->TxdData[15] = (UINT8) Value;                                    /* G High order byte */
   QsmMap->Spcr1.Spe = 1;                                                  /* G Enable Qspi */
}



// void ReadPSData(UINT16 ReadAddr)                                        /* G Current */ 
   void ReadPSData2nd(UINT16 ReadOpCode, UINT16 ReadAddr)                  /* G Function for Reading the New Novram. Read OpCode + Address */ 
{
   // QsmMap->Spcr2.Newqp = 13;                                            /* G Current */
   NovramFlag = TRUE;
   QsmMap->Spcr2.Newqp = 12;                                               /* G Addedd */
   QsmMap->Spcr2.Endqp = 15;
   QsmMap->Spcr0.Cpol = 0;
   QsmMap->Spcr0.Cpha = 0;
   QsmMap->Spcr1.Dtl = 7;                                                  /* G length of delay after transfer */
   QsmMap->Spcr0.Spbr = 13;                                                /* G 940kHz at 24.6Mhz */
   QsmMap->Spcr1.Dsckl = 8;
   QsmMap->TxdData[12] = (BYTE) ReadOpCode;                                /* G Read Operational Code */  
   QsmMap->TxdData[13] = (BYTE) ReadAddr;                                  /* G Read Address */              
   QsmMap->TxdData[14] = (BYTE) ReadOpCode;                                /* G Read Operational Code */  
   QsmMap->TxdData[15] = (BYTE) ReadAddr;                                  /* G Read Address */           
   QsmMap->Spcr1.Spe = 1;                                                  /* G Enable Qspi */
}



void OperatePSNvramStatusRegister(UINT16 OprCode, UINT16 Value)            /* G Function for writing the Status Register in the New Novram. It will write 0x00 for No Block memory write protection */
{ 
   NovramFlag = TRUE;
                                                                           /* G For Configuring the NovRam with No Block Memory Write Protection */  
   QsmMap->Spcr2.Newqp = 14;                                               /* G New Queue pointer value */                                                                                                            
   QsmMap->Spcr2.Endqp = 15;                                               /* G End Queue pointer value */                                           
   QsmMap->Spcr0.Cpol = 0;                                                                                                                           
   QsmMap->Spcr0.Cpha = 0;                                                                                                                           
   QsmMap->Spcr1.Dtl = 7;                                                  /* G length of delay after transfer */                                    
   QsmMap->Spcr0.Spbr = 13;                                                /* G 940kHz at 24.6Mhz */                                                 
   QsmMap->Spcr1.Dsckl = 8;                                                /* G Added */                                                  
   QsmMap->TxdData[14] = (UINT8) OprCode;                                  /* G Added for transmitting the "Address",taking Only the LSB Byte */ 
   QsmMap->TxdData[15] = (UINT8) Value;                                    /* G Low order byte */                                                    
   QsmMap->Spcr1.Spe = 1;                                                  /* G Enable Qspi */                                                       
}



void StorePSLifeTimeCount(void)
{
   union {
      UINT32 NvLongData;

      struct {
         UINT16 NvWordData1;
         UINT16 NvWordData2;
      } NvWordData;
      struct {
         UINT8 NvByteData1;
         UINT8 NvByteData2;
         UINT8 NvByteData3;
         UINT8 NvByteData4;
      } NvByteData;
   } NvRamData;

   NovramEnable = TRUE;  
   
   /* make sure 1ms queues are done */
   OneMilTimer = 0;
   while(OneMilTimer < 5) { };

   if(OldNovramInstalledFlag==TRUE){                                       /* G If OLD Novram is installed */
     SendPSNvramCommand(PSNOVRAMENABLE);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     SetupPSComram();

     /* Send Power Supply LifeTime Counter 1st word*/
     NvRamData.NvLongData = CurrentSetup.PSLifetime;
     WritePSData(WRITEPSLIFETIME1, NvRamData.NvWordData.NvWordData2);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     /* Send Power Supply LifeTime Counter 2nd word*/
     WritePSData(WRITEPSLIFETIME2, NvRamData.NvWordData.NvWordData1);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     /* Store Ram Data in E2PROM */
     SendPSNvramCommand(PSSTOREDATA);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     /* Reset Write Enable Latch (Disables Writed and Stores) */
     SendPSNvramCommand(PSNOVRAMDISABLE);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     InitBarGraph();

     NovramEnable = FALSE;
   }
   else{                                                                   /* G If New Novram is installed */
     // SendPSNvramCommand(PSNOVRAMENABLE);                                /* G Current */
     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Sets the Write enable latch. Before we attempt to write to the novram, we have to send the WREN opcode */     
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */
     Setup2PSComram();                                                     /* G Call the Setup2PSComram funtion for configuring for transfering 2 bytes: */
                                                                           /* G The opcode for writing the Status register and the data "0x0000h" for No Block memory write protection */      
     OperatePSNvramStatusRegister(PSNVRAMWRSR2ND, PSNVRAMBMWP2ND);         /* G Here they go */
     NovramFlag = FALSE;


     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Every time we Write the Novram, the write enable latch is cleared. Consequently, we have to Enable it again */     
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     SetupPSComram();                                                      /* G Call the SetupPSComram function for "Updating" the current configuration for Transfering 4 bytes  */
     /* Send Power Supply LifeTime Counter 1st word*/
     NvRamData.NvLongData = CurrentSetup.PSLifetime;
   
     // WritePSData(WRITEPSLIFETIME1, NvRamData.NvWordData.NvWordData2);   /* G Current */
     WritePSData2nd(PSNVRAMWRITE2ND, WRITEPSLIFETIME12ND, NvRamData.NvWordData.NvWordData2); /* G Here the 4 bytes go */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */


     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G After writing the novram, needed to set the write enable latch again */              
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */
   
     SetupPSComram();                                                      /* G Call the SetupPSComram function for "Updating" the current configuration for Transfering 4 bytes  */                                    
                                                                                

     /* Send Power Supply LifeTime Counter 2nd word*/
     // WritePSData(WRITEPSLIFETIME2, NvRamData.NvWordData.NvWordData1);   /* G Current */
     WritePSData2nd(PSNVRAMWRITE2ND, WRITEPSLIFETIME22ND, NvRamData.NvWordData.NvWordData1); /* G Here the 4 bytes go */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */


     /* Store Ram Data in E2PROM */                                         
     //  SendPSNvramCommand(PSSTOREDATA);                                  /* G Eliminated */
     //  OneMilTimer = 0;                                                  /* G Eliminated */ 
     //  while(OneMilTimer < 20) { };                                      /* G Eliminated */ 

     /* Reset Write Enable Latch (Disables Writed and Stores) */
     // SendPSNvramCommand(PSNOVRAMDISABLE);                               /* G Current */
     SendPSNvramCommand(PSNVRAMWRDI2ND);                                   /* G Write disable */
     OneMilTimer = 0;                                                       
     while(OneMilTimer < 20) { };                                           
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     InitBarGraph();                                                        
     NovramEnable = FALSE;                                                   
   }
}



void StorePSControlLevel(void)
{
   NovramEnable = TRUE;
   /* make sure 1ms queues are done */
   OneMilTimer = 0;
   while(OneMilTimer < 5) { };



   if(OldNovramInstalledFlag==TRUE){                                       /* G If OLD Novram is installed */
     SendPSNvramCommand(PSNOVRAMENABLE);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     SetupPSComram();

     /* Send Power Supply Model Number */
     WritePSData(WRITEPSMODELNUM, CurrentSetup.ControlLevel);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     /* Store Ram Data in E2PROM */
     SendPSNvramCommand(PSSTOREDATA);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     /* Reset Write Enable Latch (Disables Writed and Stores) */
     SendPSNvramCommand(PSNOVRAMDISABLE);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     InitBarGraph();

     NovramEnable = FALSE;
   }
   else{                                                                   /* G If New Novram is installed */
     // SendPSNvramCommand(PSNOVRAMENABLE);                                /* G Current */
     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Sets the write enable latch */

     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     Setup2PSComram();                                                     /* G Configures for transfer 2 bytes */
     OperatePSNvramStatusRegister(PSNVRAMWRSR2ND, PSNVRAMBMWP2ND);         /* G Here they go */
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */


     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* After writing the novram, needed to set the write enable latch again */     
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */
     SetupPSComram();  /* G Added today */                                 /* G Configure for transfering 4 bytes */  

     /* Send Power Supply Model Number */
     // WritePSData(WRITEPSMODELNUM, CurrentSetup.ControlLevel);           /* G Current */
     WritePSData2nd(PSNVRAMWRITE2ND, WRITEPSMODELNUM2ND, CurrentSetup.ControlLevel); /* G Here they go */

     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */


     /* Store Ram Data in E2PROM */
     //  SendPSNvramCommand(PSSTOREDATA);                                  /* G Eliminated */
     //  OneMilTimer = 0;                                                  /* G Eliminated */
     //  while(OneMilTimer < 20) { };                                      /* G Eliminated */

     /* Reset Write Enable Latch (Disables Writed and Stores) */
     // SendPSNvramCommand(PSNOVRAMDISABLE);                               /* G Current */
     SendPSNvramCommand(PSNVRAMWRDI2ND);                                   /* G Added Write disable */
     OneMilTimer = 0;                                                        
     while(OneMilTimer < 20) { };                                            

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */
     InitBarGraph();                                                         
     NovramEnable = FALSE;                                                   
   }
}



void StorePSWattage(void)
{
   NovramEnable = TRUE;
   /* make sure 1ms queues are done */
   OneMilTimer = 0;
   while(OneMilTimer < 5) { };

   if(OldNovramInstalledFlag==TRUE){                                       /* G If OLD Novram is installed */
     SendPSNvramCommand(PSNOVRAMENABLE);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     SetupPSComram();

     /* Send Power Supply Wattage */
     WritePSData(WRITEPSWATTAGE, CurrentSetup.PSWatt);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     /* Store Ram Data in E2PROM */
     SendPSNvramCommand(PSSTOREDATA);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     /* Reset Write Enable Latch (Disables Writed and Stores) */
     SendPSNvramCommand(PSNOVRAMDISABLE);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     InitBarGraph();
     NovramEnable = FALSE;
   }
   else{                                                                   /* G If New Novram is installed */                                                                
     // SendPSNvramCommand(PSNOVRAMENABLE);                                /* G Current */
     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Sets the write enable latch */  /* G Added 29/11/2011 */                                  
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */


     Setup2PSComram();                                                     /* G Configure for transfering 2 bytes */
     OperatePSNvramStatusRegister(PSNVRAMWRSR2ND, PSNVRAMBMWP2ND);         /* G Here they go */
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */


     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Set the write enable latch again */   /* G Added 06/12/2011 */  
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */
     SetupPSComram();  /* G Added today */                                 /* G Configure for transfering 4 bytes */    


     /* Send Power Supply Wattage */
     // WritePSData(WRITEPSWATTAGE, CurrentSetup.PSWatt);                  /* G Current */
     WritePSData2nd(PSNVRAMWRITE2ND, WRITEPSWATTAGE2ND, CurrentSetup.PSWatt);/* G Here they go */  
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */


     /* Store Ram Data in E2PROM */                                             
     //   SendPSNvramCommand(PSSTOREDATA);                                 /* G Eliminated */
     //   OneMilTimer = 0;                                                 /* G Eliminated */
     //   while(OneMilTimer < 20) { };                                     /* G Eliminated */

     /* Reset Write Enable Latch (Disables Writed and Stores) */
     // SendPSNvramCommand(PSNOVRAMDISABLE);                               /* G Current */
     SendPSNvramCommand(PSNVRAMWRDI2ND);                                   /* G Added Write disable */
     OneMilTimer = 0;                                                       
     while(OneMilTimer < 20) { };           
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */
                                  
     InitBarGraph();                                                        
     NovramEnable = FALSE;                                                    
   }
}



void StorePSFrequency(void)
{
   NovramEnable = TRUE;
   /* make sure 1ms queues are done */
   OneMilTimer = 0;
   while(OneMilTimer < 5) { };



   if(OldNovramInstalledFlag==TRUE){                                       /* G If OLD Novram is installed */                                         
     SendPSNvramCommand(PSNOVRAMENABLE);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     SetupPSComram();

     /* Send Power Supply Frequency */
     WritePSData(WRITEPSFREQ, CurrentSetup.PSFreq);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     /* Store Ram Data in E2PROM */
     SendPSNvramCommand(PSSTOREDATA);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     /* Reset Write Enable Latch (Disables Writed and Stores) */
     SendPSNvramCommand(PSNOVRAMDISABLE);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     InitBarGraph();

     NovramEnable = FALSE;
     UpdateDUPS_MaxWeldFreqLimit();
   }
   else{                                                                   /* G If New Novram is installed */
     // SendPSNvramCommand(PSNOVRAMENABLE);                                /* G Current */ 
     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Added Set the write enable latch */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     Setup2PSComram();                                                     /* G Configure for transfering 2 bytes */
     OperatePSNvramStatusRegister(PSNVRAMWRSR2ND, PSNVRAMBMWP2ND);         /* G Here they go */
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */


     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Added Set the write enable latch */
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */
  
     SetupPSComram();  /* G Added today */                                 /* G Configure for transfering 4 bytes */

     /* Send Power Supply Frequency */
     // WritePSData(WRITEPSFREQ, CurrentSetup.PSFreq);                     /* G Current */
     WritePSData2nd(PSNVRAMWRITE2ND, WRITEPSFREQ2ND, CurrentSetup.PSFreq); /* G Added Here they go */ 
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     /* Store Ram Data in E2PROM */
     //  SendPSNvramCommand(PSSTOREDATA);                                  /* G Eliminated */
     //  OneMilTimer = 0;                                                  /* G Eliminated */
     //  while(OneMilTimer < 20) { };                                      /* G Eliminated */


     /* Reset Write Enable Latch (Disables Writed and Stores) */
     // SendPSNvramCommand(PSNOVRAMDISABLE);                               /* G Current */ 
     SendPSNvramCommand(PSNVRAMWRDI2ND);                                   /* G Added Write disable */
     OneMilTimer = 0;                                                      
     while(OneMilTimer < 20) { }; 
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */
   
                                            
     InitBarGraph();                                                       
     NovramEnable = FALSE;                                                    
     UpdateDUPS_MaxWeldFreqLimit();                                        
   }
}



void StorePSSerialNumber(void)
{
   union {
      UINT32 NvLongData;

      struct {
         UINT16 NvWordData1;
         UINT16 NvWordData2;
      } NvWordData;
      struct {
         UINT8 NvByteData1;
         UINT8 NvByteData2;
         UINT8 NvByteData3;
         UINT8 NvByteData4;
      } NvByteData;
   } NvRamData;

   NovramEnable = TRUE;
   /* make sure 1ms queues are done */
   OneMilTimer = 0;
   while(OneMilTimer < 5) { };

   if(OldNovramInstalledFlag==TRUE){                                       /* G If OLD Novram is installed */
     SendPSNvramCommand(PSNOVRAMENABLE);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     SetupPSComram();

                                                                           /* Send Power Supply Serial Number */
     NvRamData.NvByteData.NvByteData2 = 0;                                 /* NULL terminate the string */
     NvRamData.NvByteData.NvByteData1 = 0;                                 /* NULL terminate the string */
     WritePSData(WRITEPSSERIALNUM7, NvRamData.NvWordData.NvWordData1);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2 = CurrentSetup.PSSerialNumber[11];
     NvRamData.NvByteData.NvByteData1 = CurrentSetup.PSSerialNumber[10];
     WritePSData(WRITEPSSERIALNUM6, NvRamData.NvWordData.NvWordData1);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2 = CurrentSetup.PSSerialNumber[9];
     NvRamData.NvByteData.NvByteData1 = CurrentSetup.PSSerialNumber[8];
     WritePSData(WRITEPSSERIALNUM5, NvRamData.NvWordData.NvWordData1);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2 = CurrentSetup.PSSerialNumber[7];
     NvRamData.NvByteData.NvByteData1 = CurrentSetup.PSSerialNumber[6];
     WritePSData(WRITEPSSERIALNUM4, NvRamData.NvWordData.NvWordData1);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2 = CurrentSetup.PSSerialNumber[5];
     NvRamData.NvByteData.NvByteData1 = CurrentSetup.PSSerialNumber[4];
     WritePSData(WRITEPSSERIALNUM3, NvRamData.NvWordData.NvWordData1);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2 = CurrentSetup.PSSerialNumber[3];
     NvRamData.NvByteData.NvByteData1 = CurrentSetup.PSSerialNumber[2];
     WritePSData(WRITEPSSERIALNUM2, NvRamData.NvWordData.NvWordData1);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2 = CurrentSetup.PSSerialNumber[1];
     NvRamData.NvByteData.NvByteData1 = CurrentSetup.PSSerialNumber[0];
     WritePSData(WRITEPSSERIALNUM1, NvRamData.NvWordData.NvWordData1);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

                                                                           /* Store Ram Data in E2PROM */
     SendPSNvramCommand(PSSTOREDATA);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

                                                                           /* Reset Write Enable Latch (Disables Writed and Stores) */
     SendPSNvramCommand(PSNOVRAMDISABLE);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     InitBarGraph();

     NovramEnable = FALSE;
   }
   else{                                                                   /* G If New Novram is installed */
     // SendPSNvramCommand(PSNOVRAMENABLE);                                /* G Current */
     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Set the write enable latch  */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */


     Setup2PSComram();                                                     /* Configure for transfering 2 bytes */
     OperatePSNvramStatusRegister(PSNVRAMWRSR2ND, PSNVRAMBMWP2ND);         /* G Here they go */
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */


     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Set the write enable latch */     
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */


     SetupPSComram();                                                      /* G Configure for transfering 4 bytes */
     /* Send Power Supply Serial Number */
     NvRamData.NvByteData.NvByteData2 = 0;                                 /* NULL terminate the string */
     NvRamData.NvByteData.NvByteData1 = 0;                                 /* NULL terminate the string */

     // WritePSData(WRITEPSSERIALNUM7, NvRamData.NvWordData.NvWordData1);  /* G Current */
     WritePSData2nd(PSNVRAMWRITE2ND, WRITEPSSERIALNUM72ND, NvRamData.NvWordData.NvWordData1);  /* Here the 4 bytes go */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Set the write enable latch */
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     SetupPSComram();                                                      /* G Configure for transfering 4 bytes */               

                                                  
     NvRamData.NvByteData.NvByteData2 = CurrentSetup.PSSerialNumber[11];
     NvRamData.NvByteData.NvByteData1 = CurrentSetup.PSSerialNumber[10];

     // WritePSData(WRITEPSSERIALNUM6, NvRamData.NvWordData.NvWordData1);  /* G Current */
     WritePSData2nd(PSNVRAMWRITE2ND, WRITEPSSERIALNUM62ND, NvRamData.NvWordData.NvWordData1);/* Here the 4 bytes go */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Set the write enable latch */
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     SetupPSComram();                                                      /* G Configure for transfering 4 bytes */
                                                                               
     NvRamData.NvByteData.NvByteData2 = CurrentSetup.PSSerialNumber[9];
     NvRamData.NvByteData.NvByteData1 = CurrentSetup.PSSerialNumber[8];

     // WritePSData(WRITEPSSERIALNUM5, NvRamData.NvWordData.NvWordData1);  /* G Current */
     WritePSData2nd(PSNVRAMWRITE2ND, WRITEPSSERIALNUM52ND, NvRamData.NvWordData.NvWordData1);/* Here the 4 bytes go */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Set the write enable latch */
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     SetupPSComram();                                                      /* G Configure for transfering 4 bytes */
                                                 
     NvRamData.NvByteData.NvByteData2 = CurrentSetup.PSSerialNumber[7];
     NvRamData.NvByteData.NvByteData1 = CurrentSetup.PSSerialNumber[6];
     // WritePSData(WRITEPSSERIALNUM4, NvRamData.NvWordData.NvWordData1);  /* G Current */

     WritePSData2nd(PSNVRAMWRITE2ND, WRITEPSSERIALNUM42ND, NvRamData.NvWordData.NvWordData1); /* G Here the 4 bytes go */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Set the write enable latch */ 
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     SetupPSComram();                                                      /* G Configure for transfering 4 bytes */
   
     NvRamData.NvByteData.NvByteData2 = CurrentSetup.PSSerialNumber[5];
     NvRamData.NvByteData.NvByteData1 = CurrentSetup.PSSerialNumber[4];

     // WritePSData(WRITEPSSERIALNUM3, NvRamData.NvWordData.NvWordData1);  /* G Current */
     WritePSData2nd(PSNVRAMWRITE2ND, WRITEPSSERIALNUM32ND, NvRamData.NvWordData.NvWordData1); /* Here the 4 bytes go */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Set the write enable latch */
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     SetupPSComram();                                                      /* G Configure for transfering 4 bytes */ 
   
     NvRamData.NvByteData.NvByteData2 = CurrentSetup.PSSerialNumber[3];
     NvRamData.NvByteData.NvByteData1 = CurrentSetup.PSSerialNumber[2];
   
     // WritePSData(WRITEPSSERIALNUM2, NvRamData.NvWordData.NvWordData1);  /* G Current */
     WritePSData2nd(PSNVRAMWRITE2ND, WRITEPSSERIALNUM22ND, NvRamData.NvWordData.NvWordData1); /* Here the 4 bytes go */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Set the write enable latch */
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     SetupPSComram();                                                      /* G Configure for transfering 4 bytes */
   
     NvRamData.NvByteData.NvByteData2 = CurrentSetup.PSSerialNumber[1];
     NvRamData.NvByteData.NvByteData1 = CurrentSetup.PSSerialNumber[0];

     // WritePSData(WRITEPSSERIALNUM1, NvRamData.NvWordData.NvWordData1);  /* G Current */
     WritePSData2nd(PSNVRAMWRITE2ND, WRITEPSSERIALNUM12ND, NvRamData.NvWordData.NvWordData1); /* G Here the 4 bytes go */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     /* Store Ram Data in E2PROM */
     // SendPSNvramCommand(PSSTOREDATA);                                   /* G Eliminated */
     // OneMilTimer = 0;                                                   /* G Eliminated */
     // while(OneMilTimer < 20) { };                                       /* G Eliminated */


     /* Reset Write Enable Latch (Disables Writed and Stores) */
     // SendPSNvramCommand(PSNOVRAMDISABLE);                               /* G Current */
     SendPSNvramCommand(PSNVRAMWRDI2ND);                                   /* G Write disable */ 
     OneMilTimer = 0;                                                       
     while(OneMilTimer < 20) { };        

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     InitBarGraph();                                                       
     NovramEnable = FALSE;
   }
}



void ReCallPSNovram(void)
{
   union {
      struct {
         UINT32 NvLongData1;
         UINT32 NvLongData2;
         UINT32 NvLongData3;
      } NvLongData;
      struct {
         UINT16 NvWordData1;
         UINT16 NvWordData2;
         UINT16 NvWordData3;
         UINT16 NvWordData4;
         UINT16 NvWordData5;
         UINT16 NvWordData6;
         UINT16 NvWordData7;
      } NvWordData;
      struct {
         UINT8 NvByteData1;
         UINT8 NvByteData2;
         UINT8 NvByteData3;
         UINT8 NvByteData4;
         UINT8 NvByteData5;
         UINT8 NvByteData6;
         UINT8 NvByteData7;
         UINT8 NvByteData8;
         UINT8 NvByteData9;
         UINT8 NvByteData10;
         UINT8 NvByteData11;
         UINT8 NvByteData12;
         UINT8 NvByteData13;
         UINT8 NvByteData14;
      } NvByteData;
      SINT8 NvByteArray[14];
   } NvRamData;


   if(OldNovramInstalledFlag==FALSE){                                      /* G If NEW PSNvram is installed */
     NovramEnable = TRUE;
                                                                           /* make sure 1ms queues are done */
     OneMilTimer = 0;
     while(OneMilTimer < 5) { };
     
     
     SendPSNvramCommand(PSNVRAMWREN2ND);                                   /* G Set the write enable latch */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     
     NovramFlag = FALSE;                                                   /* G NovramFlag set to FALSE */
  
     SetupPSComram();                                                      /* G Configure for transfering 4 bytes */

     // ReadPSData(READPSMODELNUM);                                        /* G Current */
     ReadPSData2nd(PSNVRAMREAD2ND, READPSMODELNUM2ND);                     /* G When reads the novram, we need to transfer the "read opcode" and the address */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2= QsmMap->RxdData[14];                /* G Here is the 1st read data */
     NvRamData.NvByteData.NvByteData1= QsmMap->RxdData[15];                /* G Here is the 2nd read data */ 
     PSNvRamData.ControlLevel = NvRamData.NvWordData.NvWordData1;

  
     NovramFlag = FALSE;
   
     switch (PSNvRamData.ControlLevel)
	 {
       case LEVEL_t:
       case LEVEL_e:
       case LEVEL_ea:
       case LEVEL_a:
       case LEVEL_d:
       case LEVEL_f:
       case LEVEL_TEST:
       case MODEL1:
       case MODEL2:
       case MODEL3:
       case MODEL4:
       case MODEL5:
         break;
       default: 
         PSNvRamData.ControlLevel= LEVEL_t;
         RecordAlarm(EQ11);
	 }

     // ReadPSData(READPSACTTYPE);                                         /* G Current */
     ReadPSData2nd(PSNVRAMREAD2ND, READPSACTTYPE2ND);                      /* G Send the "read opcode" and the address  */ 
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2= QsmMap->RxdData[14];                /* G 1st. read data */
     NvRamData.NvByteData.NvByteData1= QsmMap->RxdData[15];                /* G 2nd. read data */  
     PSNvRamData.Actuator = NvRamData.NvWordData.NvWordData1;

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */ 

     // ReadPSData(READPSWATTAGE);                                         /* G Current */
     ReadPSData2nd(PSNVRAMREAD2ND, READPSWATTAGE2ND);                      /* G Send the "read opcode" and the address  */                                            
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2= QsmMap->RxdData[14];                /* G 1st. read data */
     NvRamData.NvByteData.NvByteData1= QsmMap->RxdData[15];                /* G 2nd. read data */   
     PSNvRamData.PSWatts = NvRamData.NvWordData.NvWordData1;

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     if(PSNvRamData.PSWatts == 0)
       PSNvRamData.PSWatts = 2200;

     // ReadPSData(READPSFREQ);                                            /* G Current */
     ReadPSData2nd(PSNVRAMREAD2ND, READPSFREQ2ND);                         /* G Send the "read opcode" and the address  */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2= QsmMap->RxdData[14];                /* G 1st. read data */    
     NvRamData.NvByteData.NvByteData1= QsmMap->RxdData[15];                /* G 2nd. read data */ 
     PSNvRamData.PSFrequency = NvRamData.NvWordData.NvWordData1;

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     if(PSNvRamData.PSFrequency == 0)
       PSNvRamData.PSFrequency = FREQ20KHZ;


     // ReadPSData(READPSLIFETIME1);                                       /* G Current */
     ReadPSData2nd(PSNVRAMREAD2ND, READPSLIFETIME12ND);                    /* G Send the "read opcode" and the address  */
   
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData4= QsmMap->RxdData[14];                /* G 1st. read data */        
     NvRamData.NvByteData.NvByteData3= QsmMap->RxdData[15];                /* G 2nd. read data */ 

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */
   
     // ReadPSData(READPSLIFETIME2);                                       /* G Current */                 
     ReadPSData2nd(PSNVRAMREAD2ND, READPSLIFETIME22ND);                    /* G Send the "read opcode" and the address  */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2= QsmMap->RxdData[14];                /* G 1st. read data */
     NvRamData.NvByteData.NvByteData1= QsmMap->RxdData[15];                /* G 2nd. read data */     
     PSNvRamData.PSLifeTime = NvRamData.NvLongData.NvLongData1;

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     // ReadPSData(READPSSERIALNUM1);                                      /* G Current */
     ReadPSData2nd(PSNVRAMREAD2ND, READPSSERIALNUM12ND);                   /* G Send the "read opcode" and the address  */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteArray[1] = QsmMap->RxdData[14];                       /* G 1st. read data */
     NvRamData.NvByteArray[0] = QsmMap->RxdData[15];                       /* G 2nd. read data */ 
 
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     // ReadPSData(READPSSERIALNUM2);                                      /* G Current */                 
     ReadPSData2nd(PSNVRAMREAD2ND, READPSSERIALNUM22ND);                   /* G Send the "read opcode" and the address  */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteArray[3] = QsmMap->RxdData[14];                       /* G 1st. read data*/
     NvRamData.NvByteArray[2] = QsmMap->RxdData[15];                       /* G 2nd. read data */   

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     // ReadPSData(READPSSERIALNUM3);                                      /* G Current */
     ReadPSData2nd(PSNVRAMREAD2ND, READPSSERIALNUM32ND);                   /* G Send the "read opcode" and the address  */


     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteArray[5] = QsmMap->RxdData[14];                       /* G 1st. read data */
     NvRamData.NvByteArray[4] = QsmMap->RxdData[15];                       /* G 2nd. read data */


     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     // ReadPSData(READPSSERIALNUM4);                                      /* G Current */
     ReadPSData2nd(PSNVRAMREAD2ND, READPSSERIALNUM42ND);                   /* G Send the "read opcode" and the address  */


     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteArray[7] = QsmMap->RxdData[14];                       /* G 1st. read data */  
     NvRamData.NvByteArray[6] = QsmMap->RxdData[15];                       /* G 2nd. read data */

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

   
     // ReadPSData(READPSSERIALNUM5);                                      /* G Current */
     ReadPSData2nd(PSNVRAMREAD2ND, READPSSERIALNUM52ND);                   /* G Send the "read opcode" and the address  */
 
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteArray[9] = QsmMap->RxdData[14];                       /* G 1st. read data */
     NvRamData.NvByteArray[8] = QsmMap->RxdData[15];                       /* G 2nd. read data */  

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */


     // ReadPSData(READPSSERIALNUM6);                                      /* G Current */
     ReadPSData2nd(PSNVRAMREAD2ND, READPSSERIALNUM62ND);                   /* G Send the "read opcode" and the address  */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteArray[11] = QsmMap->RxdData[14];                      /* G 1st. read data */
     NvRamData.NvByteArray[10] = QsmMap->RxdData[15];                      /* G 2nd. read data */

     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     // ReadPSData(READPSSERIALNUM7);                                      /* G Current */
     ReadPSData2nd(PSNVRAMREAD2ND, READPSSERIALNUM72ND);                   /* G Send the "read opcode" and the address  */
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     // NvRamData.NvByteArray[13] = QsmMap->RxdData[14];
     // NvRamData.NvByteArray[12] = QsmMap->RxdData[15];

     NvRamData.NvByteArray[13] = 0;                                        /* Make damn sure there is a terminater */
     NvRamData.NvByteArray[12] = 0;


     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */

     strcpy(PSNvRamData.PSSerialNum, NvRamData.NvByteArray);

     // SendPSNvramCommand(PSNOVRAMDISABLE);                               /* G Current */  
     SendPSNvramCommand(PSNVRAMWRDI2ND);                                   /* G Write disable */ 
   
     OneMilTimer = 0;                                                     
     while(OneMilTimer < 20) { };                                         
     NovramFlag = FALSE;                                                   /* G Set to FALSE after reading */
     InitBarGraph();                                                      


     NovramEnable = FALSE;                                                
                                                                           /** Here a test to try and determine if this is the first time the board has **/
                                                                           /** been powered up.  If so, then set IsADepot and WasADepot flags to FALSE. **/
                                                                           /** Also call ColdStartPlus() to set all min/max and factory default values. **/
      if ( (PSNvRamData.PSWatts == 0x0ffff) &&
           (PSNvRamData.PSFrequency == 0x0ffff) &&
           (NvRamData.NvByteArray[7] == -1) &&                             /* A random location in S/N */
           (PSNvRamData.ControlLevel == LEVEL_TEST) ) {
         InitializeBBR();
	  }
   }


   IsOldNovramInstalled();                                                 /* G Go and find which Novram is installed */


   if(OldNovramInstalledFlag==TRUE){                                       /* G If OLD PSNvram is installed */

     NovramEnable = TRUE;
     /* make sure 1ms queues are done */
     OneMilTimer = 0;
     while(OneMilTimer < 5) { };

     SendPSNvramCommand(PSRECALL);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     SetupPSComram();

     ReadPSData(READPSMODELNUM);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2= QsmMap->RxdData[14];
     NvRamData.NvByteData.NvByteData1= QsmMap->RxdData[15];
     PSNvRamData.ControlLevel = NvRamData.NvWordData.NvWordData1;
     switch (PSNvRamData.ControlLevel)
     {
       case LEVEL_t:
       case LEVEL_e:
       case LEVEL_ea:
       case LEVEL_a:
       case LEVEL_d:
       case LEVEL_f:
       case LEVEL_TEST:
       case MODEL1:
       case MODEL2:
       case MODEL3:
       case MODEL4:
       case MODEL5:
         break;
       default: 
         PSNvRamData.ControlLevel= LEVEL_t;
         RecordAlarm(EQ11);
     }

     ReadPSData(READPSACTTYPE);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2= QsmMap->RxdData[14];
     NvRamData.NvByteData.NvByteData1= QsmMap->RxdData[15];
     PSNvRamData.Actuator = NvRamData.NvWordData.NvWordData1;

     ReadPSData(READPSWATTAGE);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2= QsmMap->RxdData[14];
     NvRamData.NvByteData.NvByteData1= QsmMap->RxdData[15];
     PSNvRamData.PSWatts = NvRamData.NvWordData.NvWordData1;
     if(PSNvRamData.PSWatts == 0)
       PSNvRamData.PSWatts = 2200;


     ReadPSData(READPSFREQ);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2= QsmMap->RxdData[14];
     NvRamData.NvByteData.NvByteData1= QsmMap->RxdData[15]; 
     PSNvRamData.PSFrequency = NvRamData.NvWordData.NvWordData1;
     if(PSNvRamData.PSFrequency == 0)
       PSNvRamData.PSFrequency = FREQ20KHZ;

     ReadPSData(READPSLIFETIME1);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData4= QsmMap->RxdData[14];
     NvRamData.NvByteData.NvByteData3= QsmMap->RxdData[15];
     ReadPSData(READPSLIFETIME2);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteData.NvByteData2= QsmMap->RxdData[14];
     NvRamData.NvByteData.NvByteData1= QsmMap->RxdData[15];
     PSNvRamData.PSLifeTime = NvRamData.NvLongData.NvLongData1;

     ReadPSData(READPSSERIALNUM1);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteArray[1] = QsmMap->RxdData[14];
     NvRamData.NvByteArray[0] = QsmMap->RxdData[15];
 
     ReadPSData(READPSSERIALNUM2);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteArray[3] = QsmMap->RxdData[14];
     NvRamData.NvByteArray[2] = QsmMap->RxdData[15];

     ReadPSData(READPSSERIALNUM3);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteArray[5] = QsmMap->RxdData[14];
     NvRamData.NvByteArray[4] = QsmMap->RxdData[15];

     ReadPSData(READPSSERIALNUM4);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteArray[7] = QsmMap->RxdData[14];
     NvRamData.NvByteArray[6] = QsmMap->RxdData[15];

     ReadPSData(READPSSERIALNUM5);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteArray[9] = QsmMap->RxdData[14];
     NvRamData.NvByteArray[8] = QsmMap->RxdData[15];

     ReadPSData(READPSSERIALNUM6);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     NvRamData.NvByteArray[11] = QsmMap->RxdData[14];
     NvRamData.NvByteArray[10] = QsmMap->RxdData[15];

     ReadPSData(READPSSERIALNUM7);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };

     // NvRamData.NvByteArray[13] = QsmMap->RxdData[14];
     // NvRamData.NvByteArray[12] = QsmMap->RxdData[15];

     NvRamData.NvByteArray[13] = 0;                                        /* Make damn sure there is a terminater */
     NvRamData.NvByteArray[12] = 0;

     strcpy(PSNvRamData.PSSerialNum, NvRamData.NvByteArray);

     SendPSNvramCommand(PSNOVRAMDISABLE);
     OneMilTimer = 0;
     while(OneMilTimer < 20) { };
     InitBarGraph();

     NovramEnable = FALSE;

                                                                           /** Here a test to try and determine if this is the first time the board has **/
                                                                           /** been powered up.  If so, then set IsADepot and WasADepot flags to FALSE. **/
                                                                           /** Also call ColdStartPlus() to set all min/max and factory default values. **/

      if ( (PSNvRamData.PSWatts == 0x0ffff) &&
           (PSNvRamData.PSFrequency == 0x0ffff) &&
           (NvRamData.NvByteArray[7] == -1) &&                             /* A random location in S/N */
           (PSNvRamData.ControlLevel == LEVEL_TEST) ) {
         InitializeBBR();
      }
   }
}



UINT32 VerifyPSNovram(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check most of the data read from the power supply    */
/*  novram and make sure each value is valid for the particular parameter.  */
/*                                                                          */
/****************************************************************************/
{
   UINT32 AlarmCode;

   AlarmCode = 0;
   switch (PSNvRamData.ControlLevel)
    {
      case LEVEL_t:
        break;
      case LEVEL_e:
        break;
      case LEVEL_ea:
        break;
      case LEVEL_a:
        break;
      case LEVEL_d:
        break;
      case LEVEL_f:
        break;
      case LEVEL_TEST:
        break;
      default:
        AlarmCode = EQ11;
 
    }
    
   if ((PSNvRamData.PSFrequency != FREQ15KHZ) && (PSNvRamData.PSFrequency != FREQ20KHZ) &&
        (PSNvRamData.PSFrequency != FREQ30KHZ) && (PSNvRamData.PSFrequency != FREQ40KHZ) &&
        (PSNvRamData.PSFrequency != FREQ60KHZ))
   {
      AlarmCode = EQ11;
   }           
   
   return( AlarmCode );
}



void IsOldNovramInstalled(void)                                            
/*****************************************************************************/
/*                                                                           */
/*  This function it will check which PSNovram is installed in the system    */
/*  controller. It will read the control level (location 0) from the old     */
/*  PSNovram. As a confirmation test, it will write to location 1 (no longer */
/*  used) and read it back. We should be able to read what we wrote.         */
/*                                                                           */
/*****************************************************************************/
{

   OldNovramInstalledFlag=TRUE;                                            /* Set to TRUE for using the Correct/Right configuration to the OLD PSNovram */
                                                                           /* when visiting SetupPSComram() function */ 
   /* make sure 1ms queues are done */
   OneMilTimer = 0;
   while(OneMilTimer < 5) { };

   NovramEnable = TRUE;                                                    /* Set to TRUE because the SPI will be used by the PSNovram */   
   /* make sure 1ms queues are done */
   OneMilTimer = 0;
   while(OneMilTimer < 5) { };

   // SendPSNvramCommand(PSNOVRAMENABLE);
   // OneMilTimer = 0;
   // while(OneMilTimer < 20) { };

   // SendPSNvramCommand(PSRECALL);                                        /* G Tansfer data from EEPROM to ram */
   // OneMilTimer = 0;
   // while(OneMilTimer < 20) { };

   // SetupPSComram();                                                     /* G Setup used by the OLD PSNovram (transfering 3 bytes): (1.-) For transfering the complete instruction (Startbit + Address + ReadOpCode) + (2.-) Read byte1 + (3.-) Read byte2 */
   // ReadPSData(READPSMODELNUM);                                          /* G This is the "OpCode" for Reading location 0x0000 in the OLD PSNovram (It includes the Startbit, Address and Read OpCode) */
   // OneMilTimer = 0;
   // while(OneMilTimer < 20) { };

   // ModelNumberHighByte = QsmMap->RxdData[14];                           /* G Here is the Control level code. It's assigned to "ModelNumberHighByte" variable */
   // ModelNumberLowByte = QsmMap->RxdData[15];                               
                                                                           /* Existing Power Supply Control levels */  
                                                                           /* 0x0001 = depot */
                                                                           /* 0x0010 = t     */
                                                                           /* 0x0020 = e     */
                                                                           /* 0x0030 = a     */
                                                                           /* 0x0040 = ea    */
                                                                           /* 0x0050 = d     */
                                                                           /* 0x0060 = f     */
                                                                           /* 0xFFFF = test  */
   //  switch (ModelNumberHighByte)
   //  {
   //    case (UINT8) LEVEL_t:
   //    case (UINT8) LEVEL_e:
   //    case (UINT8) LEVEL_ea:
   //    case (UINT8) LEVEL_a:
   //    case (UINT8) LEVEL_d:
   //    case (UINT8) LEVEL_f:
   //    case (UINT8) LEVEL_TEST:
   //    case (UINT8) MODEL1:
   //    case (UINT8) MODEL2:
   //    case (UINT8) MODEL3:
   //    case (UINT8) MODEL4:
   //    case (UINT8) MODEL5:
         
   //    OneMilTimer = 0;                                                  /* G make sure 1ms queues are done */
   //    while(OneMilTimer < 5) { };
                                                                           /* G Start WRITING location 0x0001 */ 
   SendPSNvramCommand(PSNOVRAMENABLE);                                     /* G Enable PSNovram */
   OneMilTimer = 0;
   while(OneMilTimer < 20) { };

   SetupPSComram();                                                        /* G Configures for transfering 3 bytes */
   WritePSData(WRITEPSACTTYPE, 0x00aa);                                    /* G Write 0x00aa value to the OLD PSNovram, Do not store it in EEPROM */     
   OneMilTimer = 0;
   while(OneMilTimer < 20) { };  	
 	                                                                       /* G Start READING back from location 0x0001 */
                                                                           /* G make sure 1ms queues are done */
   OneMilTimer = 0;   
   while(OneMilTimer < 5) { };

   SetupPSComram();                                                        /* G Setup used by the OLD PSNovram (transfering 3 bytes): (1.-) For transfering the complete instruction (Startbit + Address + ReadOpCode) + (2.-) Read byte1 + (3.-) Read byte2 */
   ReadPSData(READPSACTTYPE);                                              /* G This is the "OpCode" for Reading back location 0x0001 in the OLD PSNovram (It includes the Startbit, Address and Read OpCode) */
   OneMilTimer = 0;
   while(OneMilTimer < 20) { };

   ModelNumberHighByte = QsmMap->RxdData[14];                              /* G Here is the data we just wrote. It's assigned to "ModelNumberHighByte" */
   ModelNumberLowByte = QsmMap->RxdData[15];                               

   if(ModelNumberHighByte==0xaa){
     OldNovramInstalledFlag=TRUE;                                          /* G We're sure the OLD PSNovram is installed */   	
   }
   else{
     OldNovramInstalledFlag=FALSE;                                         /* G We were Not able to Read back what we wrote. Switch to New PSNovram */
   }
   //      break;
           
   //    default: 
   //      OldNovramInstalledFlag=FALSE;                                   
   //  }

   NovramEnable = FALSE;                                                   /* Set to FALSE. The PSNovram finished using the SPI communication at this time */
}



void InitializeBBR(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will first clear out BBR then install the proper defaults  */
/*  for system configuration.  It will also insure that the system does not  */
/*  think its a Depot unit.  The serial port is enabled and set to COMPUWELD.*/
/*  The system controller is set to 102-242-594 and all user I/O is set to   */
/*  factory defaults.                                                        */
/*                                                                           */
/*****************************************************************************/
{
   ClearOutBattRam();
   FixBattRam();
   DepotFlag->IsADepot = FALSE;
   DepotFlag->WasADepot = FALSE;
   CurrentSetup.SerialPort = COMPUWELD;
   CurrentSetup.PSLifetime = 0;
   StorePSLifeTimeCount();
   CurrentSetup.Overload = 0;
   CurrentSetup.GenAlarmCount = 0;
   CurrentSetup.BBRInitialized = BBRAM_INIT;
   BuildDefaultSpringRate();
   BackupCurrentSetupChange();
   SelectNewBoard();                                                       /* Assume from now on its a new */
   SetUserIOToFactoryDefault();                                            /* 102-242-594 system controller*/
}

/* Include for Unit test */
#ifdef INCLUDE_UNIT_TEST
#include "..\ut\novram.ut"
#endif
/* End of include for unit test */




