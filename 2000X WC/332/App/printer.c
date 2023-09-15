/* $Header:   D:/SWLab/VMdb/2000Series/App/PRINTER.C_V   1.64   04 Sep 2008 20:16:32   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*     Functions:                                                           */
/*       1. InitPrinter                                                     */
/* acknowledge indicates printer accepted char                              */
/* strobe tells printer char ready                                          */
/*                                                                          */
/*
  ---------------------------- MODULE DESCRIPTION --------------------------
  Name: printer.c
  
  -------------------------------- REVISIONS -------------------------------

   Revision #     Date        Author               Description
   ----------     -------     ------               -----------
   0              8/31/96     LAM                  Initial
   1.01           10/31/96    PaulG                Added check for 80% full.
   1.02           12/31/96    PaulG                Remove PrinterActiv.
   1.02           11/23/96    PaulG                Remove PrinterBufSize to printer.h.
   1.03           01/31/97    PaulG                Updated CheckPrinter in mansensr.c.
   1.04           04/16/97    PaulG                Added PrintBufferReadyFlag..
   1.05           04/17/97    PaulG                Added GraphReadyFlag..
   1.06           05/01/97    PaulG                Reset PrinterBufferReadyFlag if printer
                                                   buffer is 50% empty.
   1.07           05-01-97    BEKymer              Allow bargragh to blink
   1.08           05-09-97    PaulG                Insert test for TestLedBar()
   1.09           05-09-97    PaulG                Removed led bar test...
   1.10           05-23-97    PaulG                Reinstate led bar test... 
   1.11           05-27-97    PaulG                Added new defines... 
   1.1.24         06-20-97    PaulG                Added UILines to check LinePerPage... 
   1.1.28         07-17-97    BEKymer              Changed WA3 to W3
   1.1.29         08-08-97    PaulG                Added Printer driver
   1.1.30         08-13-97    PaulG                Modified ACTIVATELINEFEED string.
   1.1.31         08-23-97    PaulG                Modified Printer driver.
   1.32           08-27-97    PaulG                Cleanup data.
   1.33           08-29-97    PaulG                Cleanup data.
   1.34           08-30-97    LAM                  checkprintfull was dec 16 & 32
   1.35           09-04-97    PaulG                Cleanup Data.
   1.36           09-05-97    PaulG                check if printer buffer is 10% empty.
   1.38           09.11.97    JBerman              Line up
   1.39           09-19-97    PaulG                Initialize all integers
   1.40           10-15-97    PaulG                Modified CheckPrintFull from LEFT10 TO LEFT01.
   1.41           10-17-97    PaulG                Modified CheckPrintFull from LEFT10 TO LEFT01.
   1.42           10-28-97    PaulG                Modified CheckPrintFull from LEFT10 TO LEFT01.
   1.43           11-14-97    PaulG                Modified printerType from UINT8 to UINT16.
   1.44           11-18-97    LAM                  replaced prepc with string.h               
   1.45           11-19-97    LAM                  removed printfinalresults                  
   1.46           11-25-97    LAM                  deleted unused currentsetup elements
   1.47           11-30-97    PaulG                Modified PrinterInt function by adding AbortPrintingFlag. 
   1.48           11-30-97    PaulG                Added AbortPrintingFlag as extern.
   1.49           12-16-97    PaulG                Set printer buffer to Full at 98% so overflow doesn't occur.
   1.50           12-18-97    BJB                  Uses TempPrintPtr to stuff chrs in print
                                                   buffer, prevents PrintInPtr from ever
                                                   taking on illegal value, allowing
                                                   PrintOutPtr to step past it and "puke"
                                                   old buffer contents.
   1.51           12-18-97    PaulG                Removed Once80Stop flag.
   1.52           12-23-97    LAM                  moved wait to writeprintbuffer
   1.53           01-27-98    PaulG                Added AbortPrintingFlag test to abort immediately.
   1.54           02-11-98    PaulG                Modified printer escape codes.
   1.55           02-11-98    LAM                  removed divide by NUMPRINTER  
   1.56           02-18-98    LAM                  started to delete setprinter calls
   1.57           02-18-98    PaulG                Modified module that  checks for buffer full.
   1.58           03-16-98    BJB                  Fix bug in UpdatePrintBuf() that can cause 1/2 graph to
                                                    print on new cycle due to PrintInPtr not zero after
                                                    abort printing.
                                                   Added function PrinterIntDisable().
                                                   PrinterInt() checks for pointers equal BEFORE
                                                    outputting a character.
   1.59           08-06-98    PaulG                Added 2 new functions PrintMsgAvailable and
                                                   GetMsgFromPrintQueue.
   1.60           10-20-98    BJB                  Uses # of chrs left in printer buffer, rather
                                                    than lack of available print requests, to set
                                                    welder back to Ready in PrinterInt(). This
                                                    prevents q_receive() in PrinterInt() from taking
                                                    messages.
   1.61       02-23-99    JLH                     Removed printer control function from UpdatePrintBuf, and
                                                    changed string index from UINT8 to UINT16 so long strings
                                                    can be printed.
                                                   merged 7.f4CHp to trunk
   1.62           02-28-00     JZ                  removed tabs  
   1.63          10-22-07     NHAhmed              Changes done for LangTest phase 0
   1.64          09-04-08     YGupta               CleanUp for LangTest Project.

*******************************************************************************************/


/*-------------------------LOCAL GLOBAL DATA--------------------------------*/



/**-------------------------EXTERNAL DATA------------------------------------**/

