// WeldingHistory.h: implementation of the CWeldingHistory class.
//
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
/******************************************************************************/ 
/*                                                                            */
/*                                                                            */
/*      Copyright (c) Branson Ultrasonics Corporation, 2005                   */
/*     This program is the property of Branson Ultrasonics Corporation        */
/*   Copying of this software is expressly forbidden, without the prior       */
/*   written consent of Branson Ultrasonics Corporation.                      */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/******************************************************************************/ 
/*
Revision #    Date      Author    Description
----------  --------  ----------  -------------------------------------
  1.0       04/04/07	   PDwivedi  Added Initial Version.
  1.1       09/02/08    PDwivedi  Modify MAXPARAMUNITLENGTH for WeldHistoryScreen.
  1.2       09/12/08    PDwivedi  Added changes for Tracker issues of round 2 testing for version LangTestJ.

*/

#if !defined(AFX_WELDINGHISTORY_H__7869CA3B_A6C6_4444_A3DD_AFF3C58B13CA__INCLUDED_)
#define AFX_WELDINGHISTORY_H__7869CA3B_A6C6_4444_A3DD_AFF3C58B13CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "VgaMenuItem.h"
#include "ChildView.h"
#include "RunScreen.h"
#include "WeldingData.h"

#define LeftButton_Rect CRect(45,370,95,420)
#define ScreenUpButton_Rect CRect(105,370,155,420)
#define UpButton_Rect CRect(165,370,215,420)
#define DownButton_Rect CRect(225,370,275,420)
#define ScreenDownButton_Rect CRect(285,370,335,420)
#define RightButton_Rect CRect(345,370,395,420)
#define GraphsButton_Rect CRect(X_CORDINATE_BACK_NEXT-100,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT-100,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define ExitButton_Rect CRect(X_CORDINATE_BACK_NEXT,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define UpArrowRect CPoint(180,404), CPoint(190, 386),CPoint(201,404)
#define DownArrowRect CPoint(240,386), CPoint(250,404),CPoint(261,386) 
#define LeftArrowRect CPoint(80,386), CPoint(60,395),CPoint(80,404)
#define RightArrowRect CPoint(360,386), CPoint(380,395),CPoint(360,404)
#define ScreenUpArrow1Rect CPoint(120,398), CPoint(130, 382),CPoint(141,398) 
#define ScreenUpArrow2Rect CPoint(120,408), CPoint(130, 392),CPoint(141,408) 
#define ScreenDownArrow1Rect CPoint(300,382), CPoint(310,398 ),CPoint(321,382) 
#define ScreenDownArrow2Rect CPoint(300,392), CPoint(310, 408),CPoint(321,392) 
#define MAXPARAMUNITLENGTH	 7

class CXmlElement;

class CWeldingHistory : public CVgaMenuItem  
{
public:
   CWeldingHistory(CXmlElement * e);
   virtual ~CWeldingHistory();
   static TCHAR ParameterUnitUSCS[MAXPARAMVALUES][MAXPARAMUNITLENGTH];
   static TCHAR ParameterUnitMetric[MAXPARAMVALUES][MAXPARAMUNITLENGTH];
   static int SelectedWeldId;
   bool SelectedDataUnit;
   void DrawParameterHeadings(CDC * pDC);
   bool USBHistory;
   int *Parameter_ID;
   int TotalColoumn;
   static int TopMostData;
   void DrawHistoryData(CDC *pDC);
   int TotalCycle;
   UpdateWeldData(unsigned char *&data, int &length);
   CWeldingHistory(unsigned char * &data, int & length);
   CWeldingHistory();
   CTypedPtrList<CPtrList, CWeldingData *> WeldHistoryList;
   CTypedPtrList<CPtrList, CHistoryData *> USBWeldHistoryList;

   static int SelectedWeldData;
   static int LeftMostParameter;
   static CWeldingHistory * thisHisPtr;	
protected:
   bool UpButtonPressed;
   bool DownButtonPressed;
   bool LeftButtonPressed;
   bool RightButtonPressed;
   bool ScreenUpButtonPressed;
   bool ScreenDownButtonPresssed;
   bool GraphsButtonPressed;
   bool ExitButtonPressed;
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;
   private:
   int lang_index;
};

#endif // !defined(AFX_WELDINGHISTORY_H__7869CA3B_A6C6_4444_A3DD_AFF3C58B13CA__INCLUDED_)
