/* $Header:   D:/SWLab/VMdb/2000Series/App/PRNMANGR.C_V   2.97   04 Sep 2008 20:16:32   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96,97           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*************************                         **************************/
/*
---------------------------- MODULE DESCRIPTION ----------------------------

    Module name:   

    Filename:      

    Function Name: WeldDataPrintManager
  
                Written by:   Mark Lazarewicz
                        Date:   02/11/96
                  Language:   "C"

---------------------------------- REVISIONS ------------------------------------

Revision#     Date      Author   Description
=========     ========  =======  ===========
   0          02-11-96  Mark L   Initial Shell
   1.00       08-10-96  PaulG    Added SWITCH for printer   
                                 opcode.
   1.01       09-10-96  PaulG    Added switch for Graphs..
   1.02       10-22-96  PaulG    Added 1 ms data case...
                                 Added functions for OP_PRINT_ABORT
                                 OP_PRINTER_OFFLINE.
   1.03       11-11-96  PaulG    Removed LastSample extern.
   1.04       11-13-96  PaulG    Added function to print graphs, preset,
                                 or weldsummary.
   1.05       11-20-96  PaulG    Added GlobalSampleFlag and GlobalAlarmFlag.   
   1.06       12-03-96  PaulG    Added automatic printing of graphs.    
   1.07       12-10-96  PaulG    Added PrintAnyway flag.    
   1.08       01-09-97  PaulG    Added flag to check for CONTINUOUSMODE.    
   1.09       01-23-97  PaulG    Modified global flag check.    
   1.10       01-31-97  PaulG    Modified OP_PRINT_ABORT section.
   1.11       02-21-97  PaulG    Added test counter.
   2.00       02-25-97  LAM      deleted unused vars
   2.01       03-06-97  PaulG    Check for printer powered off.
   2.02       03-11-97  PaulG    Added PrintWeldResults for final data.
   3.00       03-27-97  LAM      deleted final data.
   3.01       04-04-97  PaulG    Added UILine to PRINT NOW.
   3.02       04-16-97  PaulG    Modified  ABORT printing.
   3.03       04-17-97  PaulG    Added GraphReadyFlag.
   3.04       05-01-97  PaulG    Removed GraphReadyFlag and update Power bars.
   4.00       05-09-97  LAM      added psosreadyflag
   5.00       05-09-97  LAM      added printinggraphflag
   6.00       05-15-97  LAM      added timedelays        
   7.00       05-15-97  LAM      chged timedelays        
   7.01       05-23-97  PaulG    chged timedelays to checking printer buffer.        
   7.02       05-30-97  PaulG    Removed GlobalSampleFlag and GlobalAlarmFlag.        
   8.00       06-02-97  LAM      added printerreadyflag                               
   8.00       06-06-97  LAM      added testcode                               
   8.2.46     06-27-97  PaulG    Removed UILine = 0.                               
   8.2.47     07-07-97  LAM      deleted psos_tbl.h                     
   8.2.48     08-23-97  PaulG    Cleanup data.
   2.49       08-27-97  PaulG    Changed time2 to WaitForPrinter also changed time from 20 to 30ms
   2.50       09-04-97  PaulG    Cleanup Data.
   2.51       09-09-97  PaulG    Cleanup Data.
   2.52       09-11-97  PaulG    Print new header when Print Now is pressed for weld data.
   2.53       09-16-97  PaulG    Cleanup Data.
   2.54       09-24-97  PaulG    If printer is offline generate alarm.
   2.55       09-30-97  PaulG    Modified PrintOnSample printout.
   2.56       10-03-97  PaulG    Modified PrintingGraph Flag and WaitForPrinter from 30 to 5.
   2.57       10-16-97  PaulG    Added GraphActive flag to check when printing is occuring.
   2.58       10-23-97  PaulG    Removed PrinterNotReady flag.
   2.59       10-28-97  PaulG    Added CheckPrintingStatus() to printer offline check.
   2.60       10-31-97  PaulG    Added  OfflineCheckFunc() to printer offline check.
   2.61       11-06-97  LAM      added stop at end of cycle             
   2.62       11-10-97  LAM      moved stop at end of cycle to weldmanager
   2.63       11-11-97  LAM      moved memcpy to weldmanager
   2.64       11-14-97  PaulG    Modified to RecordAlarm if offline or disconnected.
   2.65       11-14-97  LAM      Made sure statemachine is restarted                 
   2.66       11-19-97  PaulG    Cleanup commented code
   2.67       11-19-97  LAM      Chged printfinalresults to finalresults                    
   2.68       11-20-97  PaulG    Removed the PrinterEnabled flag.
   2.69       11-25-97  LAM      only check printeroffline when print now
   2.70       12-02-97  LAM      added encoder test                       
   2.71       12-05-97  LAM      reduced waitprinter to 3, tried checkfull > left20
                                 it did not work
   2.72       12-10-97  PaulG    Change WaitForPrinter (printer delay) from 3 to 30 msec
   2.73       12-16-97  PaulG    Removed GraphActive flag and decrease WaitForPrinter from 30 to 3.
   2.74       12-19-97  PaulG    Added offline or powered off check for sample data.
   2.75       12-22-97  LAM      moved waitprinter to printer.c                   

  2.76       01-20-98  PaulG    Combined OfflineCheckFunc and PoweredOffCheckFunc.
   2.77       01-28-98  PaulG    Check if we were on the continue screen before setting
                                 AbortPrinting flag to FALSE.
   2.78       03-16-98  PaulG    Removed OfflineCheckFunc from OP_FINAL_WELD_DATA.
   2.79       05-15-98  PaulG    Enabled Force Graph.
   2.80       05-18-98  PaulG    Added CASE for Abs dist. graph.
   2.81       05-27-98  PaulG    Reset cycle check variable if cold start was done.
   2.82       08-06-98  PaulG    Added function GetMsgFromPrintQueue() to check if message is in print queue.
   2.83       08-25-98  PaulG    Rearrange graph printout in order corresponding to menu order.
   2.84       10-01-98  PaulG    Added flag IsThereDataPrinting to check if printing is going on.
   2.85       12/16/99  LAM      removed unused errorhandling code, fixed IsThereDataPrinting flag                   
   2.87       04-28-00  JLH      Added horn scan graph to switch(GetGraphMsg).  Ignore 2.86 -- 
                                  operator error.
   2.88       05-02-00  JLH      Added Dups Preset printout to switch(GetGraphMsg).
   2.89       07-07-00  BEKymer/DJL  fixed SETUPS
   2.90       10-19-00  BEKymer  Remove possibility of printing ABS graph by removing
                                  all code related to absolute graph
   2.91       10-20-00  JLH      Do not print force graph on sample or alarm for AE actuator. 
   2.92       06-04-04  VSharma  Passed global Sample and Alarm flag for each graph in 
                                 SampleAlarmCheckFunc().
   2.93       06-22-04  JOY      Removed commented code for ABSOLUTE GRAPH from PrintWeldManager().
   2.94       12-20-05  Bwadia   Added Sequence Printing for VFD. Modified for Tracker issue 3976
   2.95       02-22-06  LAM      Added 9.04 fix.
   2.96       10-22-07  NHAhmed  Changes done for LangTest phase 0
   2.97       09-04-08  YGupta   CleanUp for LangTest Project.


-------------------------------- LOCAL_EQUATES ----------------------------------
*/

#include "graphs.h"
#include "names.h"               /* psos object defines                 */
#include "opcodes.h"             /* incoming message opcodes            */
#include "genrlmsg.h"            /* define generic message              */
#include "names.h"
#include "prnmangr.h"
#include "weld_obj.h"
#include "weld_msg.h"
#include "statedrv.h"
#include "menu4.h"
#include "ck_qsend.h"
#include "alarms.h"
#include "ready.h"

/*------------------------ LOCAL_TYPE_DECLARATIONS -------------------------*/

/*--------------------------------------------------------------------------*
 * this union is comprised of the expected messages that will be sent       *
 *  to this task.                                                           *
 *--------------------------------------------------------------------------*/


/*-------------------------- EXTERN DATA -----------------------------------*/

/*---------------------------- GLOBAL DATA ---------------------------------*/

UINT16             PrintAnyway = FALSE;
UINT16             AbortPrintingFlag = FALSE;  /*-- TRUE: Abort printing pressed in print menu --*/
BOOLEAN            IsThereDataPrinting = FALSE;/*-- TRUE: Printing is active, FALSE: no printing is in progress --*/

/*-------------------------------- CODE ------------------------------------*/
