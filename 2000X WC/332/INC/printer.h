/* $Header:   D:/SWLab/VMdb/2000Series/INC/PRINTER.H_V   2.36   04 Sep 2008 20:17:34   ygupta  $ */
#ifndef PRINTER_H
#define PRINTER_H
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

/*---------------------------- MODULE DESCRIPTION ---------------------------

   Module name:  

   Filename:      printer.h


            Written by: Laura Markure  
                  Date: 9/03/96  
              Language:  "C"

 -------------------------------- REVISIONS ---------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            9/03/96       LAM         Initial Release
      1.00         9/10/96       PAULG       Add enum for Graphs
      2.00         10/08/96      PAULG       Added FINALRESULTS to enum. 
      3.00         01/06/97      PAULG       Modified UpdatePrintBuf parameter
                                             from UINT8 to UINT16. 
      4.00         01/31/97      PAULG       Increased PrintBufSize to 15000. 
      4.01         02/21/97      PAULG       Increased PrintBufSize to 20000. 
      4.02         02/22/97      PAULG       Increased PrintBufSize to 15000. 
      4.03         02/26/97      PAULG       Added Header. 
      4.04         04/04/97      PAULG       Increased PrintBufSize to 36000. 
      5.00         04/07/97      LAM         chged PrintBufSize to 24000. 
      5.01         04/16/97      PaulG       Added LEFT05 - LEFT100 
      5.02         05/01/97      PaulG       Increased PrintBufSize to 27000.  
      5.03         05/02/97      PaulG       Decreased PrintBufSize to 20000.  
      5.04         05/15/97      PaulG       Increased PrintBufSize to 24000.  
      6.00         05/16/97      PaulG       decreased PrintBufSize to 20000.  
      6.01         05/27/97      PaulG       Added defines for Print Buffer size.  
      6.2.23       06/19/97      PaulG       Added defines for Printer status.  
      6.2.24       06/22/97      PaulG       Removed printer status.
      6.2.25       12/12/97      PaulG       Added LEFT99 and LEFT98.
      6.2.28       03/16/98      BJB         Added prototype for PrinterIntDisable().
      6.2.29       05/18/98      PaulG       Added ABSDISTGRAPH for Abs Graph.
      6.2.30       08/06/98      PaulG       Added function prototype PrintMsgAvailable and
                                             GetMsgFromPrintQueue.
      2.31         04-28-00      JLH         Added HORNSCAN to MSG_GRAPH_TYPE enum.
      2.32         05-02-00      JLH         Added DUPSPRESET to MSG_GRAPH_TYPE enum. 
      2.33         05-13-05      Aare        Reduced PRINTBUFSIZE from 20000 to 10000.
      2.34         12-20-05      Bwadia      Added SEQUENCEPRESET in MSG_GRAPH_TYPE enum
                                             Modified for tracker issue 3976
      2.35         10-22-07      NHAhmed     Changes done for LangTest phase 0
	  2.36         09-04-08		 ygupta     Cleanup for Multilanguage project.


------------------------------- DESCRIPTION --------------------------------*/


 

/*----------------------------- INCLUDE FILES ------------------------------*/  


/*--------------------------- TYPE DECLARATIONS ----------------------------*/
                           

#endif    /* end of PRINTER.H */
