/* $Header:   D:/SWLab/VMdb/2000Series/INC/SPIDD.H_V   2.30   May 19 2004 13:56:22   LMarkure  $ */
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

   Filename:      spidd.h


            Written by: Laura Markure 
                  Date: 4/01/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             5/05/96      LAM         Initial
      1             6/13/96      LAM         added disabledigpot
      2             6/30/96      LAM         added getspringforce
      3             7/12/96      LAM         added updatefreqbargraph
      4             10/09/96     LAM         chged uint16table to uin32table
      5             11/10/96     LAM         chged calibtable prototype    
      6             12/17/96     LAM         deleted initnovram
      7             01/11/97     LAM         deleted getcurrentactuator
      8             02/10/97     LAM         deleted updatefreqbargraph
      9.2.13        06/23/97     LAM         added checkforencoder      
     10.2.14        08/14/97     LAM         added enabledigpot         
     10.2.16        08.20.97     JBerman     Added 3 digital Filters prototype
     2.17           08/26/97     LAM         added setdigpot         
     2.18           09/08/97     LAM         deleted spielement      
     2.19           10/15/97     LAM         added updatediagscreen prototype
     2.20/21        10.27.97     JBerman     inline before Dig Filter Proto's.
      2.22          11.11.97    JBerman     Added UINT32 PwrTestFilter(UINT32);
      2.23          04.23.98    LAM         deleted unused checkforencoder
     2.24           05.20.98     BJB         Added "Offset" parameter to
                                              UpdateCalibratedTable() so force
                                              and pressure can have different
                                              offsets.
     2.25           06.04.98     BJB         Deleted prototypes for UpPot(),
                                              DecPot().
     2.27           10.11.99    LAM         deleted unused updatecalbuint32table
     2.28           12-20-99    JZ          deleted UpdateCalibratedTable
     2.29           08-15-00    AT          Moved UpdateDiagScreen to menutest.[ch]
     2.30           05-18-04    LAM  Created CheckforHornChange, this is called at power up and after an EStop
 
 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  


/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
 
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void InitBarGraph(void);
void InitDigitalPot(void);
void WritePVP(UINT16 PVPValue);    
void InitPVP(void);
void WritePSDAC(UINT16 Freq, UINT16 Amp);
void WriteBarGraph(void);
void ReadPSADC(void);
void ReadACTADC(void);
void CenterDigPot(void);
void EnableDigPot(void);
void DisableDigPot(void);
void SetDigPot(void);

UINT16 GetSpringForce(void);
void CheckForHornChange(void);

UINT32 DigFilterAmp(UINT16);
UINT32 DigFilterPower(UINT16);
UINT32 DigFilterFreq(UINT16);
UINT32 PwrTestFilter(UINT32);

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/
