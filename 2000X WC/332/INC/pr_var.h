/* $Header:   D:/SWLab/VMdb/2000Series/INC/PR_VAR.H_V   1.22   Dec 20 2005 15:25:52   bwadia  $ */
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
------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename: pr_var.h
 

            Written by: Gert Reitmayer  
                  Date: 9/14/96  
              Language:  "C"

----------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            09/14/96       GR         Initial Release
      1.01         09/17/96       PaulG      Added header 
      1.02         02/26/97       PaulG      Added header for PVCS. 
      1.03         02/28/97       PaulG      Removed variable val. 
      1.04         03/07/97       PaulG      Added ESC sequence for non-Graph. 
      1.05         03/20/97       PaulG      Clean up file.
      1.06         04/28/97       PaulG      Removed PMess[] and PAlarmsMess[].
      1.07         08/08/97       PaulG      Added printer strings.
      1.08         08/13/97       PaulG      Added printer strings for graphic printing.
      1.09         08/23/97       PaulG      Modified printer strings for graphic printing.
      1.10         10/15/97       PaulG      Added string PUCPageSize.
      1.11         11/11/97       PaulG      Added Init text for IBM and Epson.
      1.15         11/14/97       PaulG      Added Init text for IBM and Epson.
      1.16         07/29/98       PaulG      Removed member b_which_graph from GraphicInfo struct.
      1.17.4.1     08/28/99       JLH        Various updates for use of IBM Pro mode of printer.
      1.17.4.2     09/08/99       JLH        Correct error in 1/6 inch line feed for Epson mode.
      1.17.4.3     09/16/99       JLH        Removed PUCGraph, PUCNonGraphics, PUCCancel, UCInitFX,
                                             and UCInitIBM arrays.
      1.18.1.1     12-16-99       JLH        Removed all remaining printer control arrays.  All
                                              printer control is done by subroutines in pr_print.
      1.19         02-23-00       JLH        merged 7.f4CHp (1.18.1.1) to trunk 
      1.20         02-28-00       JZ         removed tabs
      1.21         05-01-00       JLH        Removed unused variable UINPoints.  Replaced order
                                              declaration with declarations for order1 and order2.
      1.22         12-20-05       Bwadia     Dummy check in                                        
      
----------------------------- DESCRIPTION -----------------------------------

*/

#ifndef PR_VAR
#define PR_VAR

/* Info from the system*/

SINT8 **PPCMess;    /* pointer to the text array*/
UINT32 UIVmaxlabel, UIVminlabel, UIHmaxlabel;
UINT32 UIGraphPoints;
struct STRComp order1[400];
struct STRComp order2[400];
UINT32 UIWeldtime;
struct SummaryStruct SummaryInfo  = {1,0,1,4};
struct GraphicStruct GraphicInfo  = {0,0};
struct BottomStruct  BottomInfo   = {0};
struct HistoryStruct HistoryInfo  = {0,0};
struct GeneralStruct GeneralInfo  = {1,0,18};

#endif

