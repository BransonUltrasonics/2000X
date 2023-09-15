/* $Header:   D:/databases/VMdb/2000Series/INC/PSNVRAM.H_V   1.10   13 Sep 2012 09:01:58   gbutron  $ */
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
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      novram.h


 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      1.0          11/18/96      PhilJ       Initial Version.
      1.1          07/03/97      PhilJ       Deleted prototypes StorePSNovRam
                                             and StoreActuaor.
      1.2          07-16-97      BEKymer     Added prototype for VerifyPSNovram
      1.3          07/30/98      BJB         VerifyPSNovram() returns UINT32
                                             alarm code.
      1.4          07-21-00      JLH         Added center frequency defines: CENTER15KHZ, CENTER20KHZ,
                                             CEMTER30KHZ, and CENTER40KHZ.  
      1.5          08-24-00      LAM         save 12 characters for ps ser num
      1.6          06-08-01      BEKymer     Fix bug created when increasing from 9 digit to 12 digit
                                             serial number
      1.7          05-20-02      BEKymer     Add prototype for InitializeBBR()
      1.8          03-05-04      LAM         Add InitializeBBR define
      1.9          07-28-04      JOY         Added Define CENTER60KHZ.
      1.10         09-13-12      GButron     Make the software works with 16/8bits PSNovram

 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  

/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/                            

typedef struct {
       UINT16 ControlLevel;
       UINT16 Actuator;
       UINT16 PSWatts;
       UINT16 PSFrequency;
       UINT32 PSLifeTime;
       SINT8  PSSerialNum[13];
       } PSNOVRAMDATA;

/*
 ------------------------------- DEFINES ---------------------------------------
*/

#define PSNOVRAMID          0xA000
#define BBRAM_INIT 0x55AA

// PS novram memory map addresses
/*                                       x = Start Bit must always be high */
/*                                       |xxxx = Address Bits              */
/*                                       |||||xxx = Instruction Bits       */
#define PSNOVRAMDISABLE     0x0080    /* 10000000 */
#define PSSTOREDATA         0x0081    /* 10000001 */
#define PSAUTOSTORE         0x0082    /* 10000010 */
#define PSNOVRAMENABLE      0x0084    /* 10000100 */
#define PSRECALL            0x0085    /* 10000101 */


// PS RAMTRON NOVRAM - NEW OPCODES   -Begin                                            /* G Added 11/29/2011 */
#define PSNVRAMWRDI2ND      0x0004    /* 00000100 */                                   /* G Added 11/29/2011 */
#define PSNVRAMWREN2ND      0x0006    /* 00000110 */                                   /* G Added 11/29/2011 */
#define PSNVRAMWRITE2ND     0x0002    /* 00000010 */                                   /* G Added 11/29/2011 */
#define PSNVRAMREAD2ND      0x0003    /* 00000011 */                                   /* G Added 11/29/2011 */
#define PSNVRAMWRSR2ND      0x0001    /* 00000001 */                                   /* G Added 11/29/2011 */
#define PSNVRAMRDSR2ND      0x0005    /* 00000101 */                                   /* G Added 11/29/2011 */
#define PSNVRAMBMWP2ND      0x0000    /* 00000000 */                                   /* G Added 11/29/2011 */
// PS RAMTRON NOVRAM - NEW OPCODES   -End                                              /* G Added 11/29/2011 */

/*                                       x = Start Bit must always be high */
/*                                       |xxxx = Address Bits              */
/*                                       |||||xxx = Instruction Bits       */
#define WRITEPSMODELNUM     0x0083    /* 10000011 */
#define WRITEPSACTTYPE      0x008b    /* 10001011 */
#define WRITEPSFREQ         0x0093    /* 10010011 */
#define WRITEPSLIFETIME1    0x009b    /* 10011011 */
#define WRITEPSLIFETIME2    0x00a3    /* 10100011 */
#define WRITEPSSERIALNUM1   0x00ab    /* 10101011 */
#define WRITEPSSERIALNUM2   0x00b3    /* 10110011 */
#define WRITEPSSERIALNUM3   0x00bb    /* 10111011 */
#define WRITEPSSERIALNUM4   0x00c3    /* 11000011 */
#define WRITEPSSERIALNUM5   0x00cb    /* 11001011 */
#define WRITEPSSERIALNUM6   0x00fb    /* 11111011 */
#define WRITEPSSERIALNUM7   0x00f3    /* 11110011 */
#define WRITEPSWATTAGE      0x00d3    /* 11010011 */
#define WRITEPSSWVERSION1   0x00db    /* 11011011 */
#define WRITEPSSWVERSION2   0x00e3    /* 11100011 */
#define WRITEPSSWVERSION3   0x00eb    /* 11101011 */


// PS RAMTRON NOVRAM - NEW WRITE ADDRESSESS   -Begin                                   /* G Added 11/29/2011 */
#define WRITEPSMODELNUM2ND     0x0000 /* 00000000 */                                   /* G Added 11/29/2011 */
#define WRITEPSACTTYPE2ND      0x0002 /* 00000010 */                                   /* G Added 11/29/2011 */
#define WRITEPSFREQ2ND         0x0004 /* 00010100 */                                   /* G Added 11/29/2011 */
#define WRITEPSLIFETIME12ND    0x0006 /* 00000110 */                                   /* G Added 11/29/2011 */
#define WRITEPSLIFETIME22ND    0x0008 /* 00001000 */                                   /* G Added 11/29/2011 */
#define WRITEPSSERIALNUM12ND   0x000A /* 00001010 */                                   /* G Added 11/29/2011 */
#define WRITEPSSERIALNUM22ND   0x000C /* 00001100 */                                   /* G Added 11/29/2011 */
#define WRITEPSSERIALNUM32ND   0x000E /* 00001110 */                                   /* G Added 11/29/2011 */
#define WRITEPSSERIALNUM42ND   0x0010 /* 00010000 */                                   /* G Added 11/29/2011 */
#define WRITEPSSERIALNUM52ND   0x0012 /* 00010010 */                                   /* G Added 11/29/2011 */
#define WRITEPSSERIALNUM62ND   0x0014 /* 00010100 */                                   /* G Added 11/29/2011 */
#define WRITEPSSERIALNUM72ND   0x0016 /* 00010110 */                                   /* G Added 11/29/2011 */
#define WRITEPSWATTAGE2ND      0x0018 /* 00011000 */                                   /* G Added 11/29/2011 */
#define WRITEPSSWVERSION12ND   0x001A /* 00011010 */                                   /* G Added 11/29/2011 */
#define WRITEPSSWVERSION22ND   0x001C /* 00011100 */                                   /* G Added 11/29/2011 */
#define WRITEPSSWVERSION32ND   0x001E /* 00011110 */                                   /* G Added 11/29/2011 */
// PS RAMTRON NOVRAM - NEW WRITE ADDRESSESS   -End                                     /* G Added 11/29/2011 */

#define READPSMODELNUM      0x0086    /* 10000110 */
#define READPSACTTYPE       0x008e    /* 10001110 */
#define READPSFREQ          0x0096    /* 10010110 */
#define READPSLIFETIME1     0x009e    /* 10011110 */
#define READPSLIFETIME2     0x00a6    /* 10100110 */
#define READPSSERIALNUM1    0x00ae    /* 10101110 */
#define READPSSERIALNUM2    0x00b6    /* 10110110 */
#define READPSSERIALNUM3    0x00be    /* 10111110 */
#define READPSSERIALNUM4    0x00c6    /* 11000110 */
#define READPSSERIALNUM5    0x00ce    /* 11001110 */
#define READPSSERIALNUM6    0x00fe    /* 11111110 */
#define READPSSERIALNUM7    0x00f6    /* 11110110 */
#define READPSWATTAGE       0x00d6    /* 11010110 */
#define READPSSWVERSION1    0x00de    /* 11011110 */
#define READPSSWVERSION2    0x00e6    /* 11100110 */
#define READPSSWVERSION3    0x00ee    /* 11101110 */
#define READPSSWVERSION4    0x00f6    /* 11110110 */


// PS RAMTRON NOVRAM - NEW READ ADDRESSESS   -Begin                                    /* G Added 11/29/2011 */
#define READPSMODELNUM2ND     0x0000  /* 00000000 */                                   /* G Added 11/29/2011 */
#define READPSACTTYPE2ND      0x0002  /* 00000010 */                                   /* G Added 11/29/2011 */
#define READPSFREQ2ND         0x0004  /* 00010100 */                                   /* G Added 11/29/2011 */
#define READPSLIFETIME12ND    0x0006  /* 00000110 */                                   /* G Added 11/29/2011 */
#define READPSLIFETIME22ND    0x0008  /* 00001000 */                                   /* G Added 11/29/2011 */
#define READPSSERIALNUM12ND   0x000A  /* 00001010 */                                   /* G Added 11/29/2011 */
#define READPSSERIALNUM22ND   0x000C  /* 00001100 */                                   /* G Added 11/29/2011 */
#define READPSSERIALNUM32ND   0x000E  /* 00001110 */                                   /* G Added 11/29/2011 */
#define READPSSERIALNUM42ND   0x0010  /* 00010000 */                                   /* G Added 11/29/2011 */
#define READPSSERIALNUM52ND   0x0012  /* 00010010 */                                   /* G Added 11/29/2011 */
#define READPSSERIALNUM62ND   0x0014  /* 00010100 */                                   /* G Added 11/29/2011 */
#define READPSSERIALNUM72ND   0x0016  /* 00010110 */                                   /* G Added 11/29/2011 */
#define READPSWATTAGE2ND      0x0018  /* 00011000 */                                   /* G Added 11/29/2011 */
#define READPSSWVERSION12ND   0x001A  /* 00011010 */                                   /* G Added 11/29/2011 */
#define READPSSWVERSION22ND   0x001C  /* 00011100 */                                   /* G Added 11/29/2011 */
#define READPSSWVERSION32ND   0x001E  /* 00011110 */                                   /* G Added 11/29/2011 */
// PS RAMTRON NOVRAM - NEW READ ADDRESSESS   -End                                      /* G Added 11/29/2011 */


// Center Frequencies for the various power supply frequency types.
#define CENTER15KHZ         15000
#define CENTER20KHZ         19950
#define CENTER30KHZ         30000
#define CENTER40KHZ         39900 
#define CENTER60KHZ         60000

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
 
/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

void SendPSNvramCommand(UINT16 Command);                                               /* G This function did not change */  
void SetupPSComram(void);                                                              /* G Setup before transfer 4 bytes */
void WritePSData(UINT16 WriteAddr, UINT16 Value);                                      /* G Current */
void WritePSData2nd(UINT16 WriteOpCode, UINT16 WriteAddr,  UINT16 Value);              /* G It sends Write Operational code, Address and writes byte1 and byte2 to the Novram */
void ReadPSData(UINT16 ReadAddr);                                                      /* G Current */
void ReadPSData2nd(UINT16 ReadOpCode, UINT16 ReadAddr);                                /* G It sends Read OpCode, Address, and read 2 bytes */ 
void StorePSLifeTimeCount(void);                                                       /* G Modified for Ramtron Novram */
void StorePSControlLevel(void);                                                        /* G Modified for Ramtron Novram */
void StorePSWattage(void);                                                             /* G Modified for Ramtron Novram */
void StorePSFrequency(void);                                                           /* G Modified for Ramtron Novram */
void StorePSSerialNumber(void);                                                        /* G Modified for Ramtron Novram */
void ReCallPSNovram(void);                                                             /* G Modified for Ramtron Novram */
UINT32 VerifyPSNovram(void);                                                           /* G Did not change */
void InitializeBBR(void);                                                              /* G Did not change */
void OperatePSNvramStatusRegister(UINT16 OprCode, UINT16 Value);                       /* G It writes the Status register - No block memory write protection */
void Setup2PSComram(void);                                                             /* G Setup before transfer 2 bytes for writing the Status register */
void IsOldNovramInstalled(void);                                                       /* G Function for knowing which Novram is installed */


