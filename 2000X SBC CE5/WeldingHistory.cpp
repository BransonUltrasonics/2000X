// WeldingHistory.cpp: implementation of the CWeldingHistory class.
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
  1.1       08/01/08	   PDwivedi  Added Default constructors. 
  1.2       08/08/08    PDwivedi  Final Code Clean up.
  1.3       09/02/08    PDwivedi  Modify DrawParameterHeading for Remember WeldHistory Column.
  1.4       09/12/08    PDwivedi  Added changes for Tracker issues of round 2 testing for version LangTestJ.
*/

#include "stdafx.h"
#include "SBC.h"
#include "WeldingHistory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


int CWeldingHistory::TopMostData;
int CWeldingHistory::SelectedWeldData;
int CWeldingHistory::LeftMostParameter;
int CWeldingHistory::SelectedWeldId=1;
TCHAR CWeldingHistory::ParameterUnitUSCS[MAXPARAMVALUES][MAXPARAMUNITLENGTH];
TCHAR CWeldingHistory::ParameterUnitMetric[MAXPARAMVALUES][MAXPARAMUNITLENGTH];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWeldingHistory * CWeldingHistory::thisHisPtr;

CWeldingHistory::CWeldingHistory(CXmlElement * e)
{
	POSITION pos = e->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * element = e->children.GetNext(pos);
		CString tag = element->GetTag();
		if (tag == "condition")
	  {
		 AddCondition(element);
	  }
		else
			ASSERT(FALSE);
	}
	thisHisPtr=this;
   CWeldingHistory::LeftMostParameter=1;
}

CWeldingHistory::CWeldingHistory()
{
	USBHistory=true;
	Parameter_ID=new int[1];

}

/***********************************************************************/
/* This function is called when History data list needs to be updated. */
/*																	   */	
/***********************************************************************/
CWeldingHistory::UpdateWeldData(unsigned char *&data, int &length)
{
//	data+=9;//Co-ordinates for rectangle.
//	length-=9;
	int TotalColoumn = *data++;length--;
	
	
	for(int columns =0;columns< TotalColoumn; columns++)
	{
	//	ID_Array[columns] =*data++;
		*data++;
		length--;
	}
	int ReceivedUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	int Cycle = *data++;
	TotalCycle +=Cycle;
	length--;
	
	//storing parameters whose ID matches with displayable parameter ID 
	for(int cycle =0;cycle<Cycle;cycle++)
	{
		CWeldingData * obj = new CWeldingData(TotalColoumn,data, length);
		WeldHistoryList.AddTail(obj);
	}
}

CWeldingHistory::~CWeldingHistory()
{
	delete []Parameter_ID;
	while(WeldHistoryList.GetCount()>0)
			delete WeldHistoryList.RemoveHead();
	while(USBWeldHistoryList.GetCount()>0)
	{
		CHistoryData *obj1 = USBWeldHistoryList.RemoveHead();//delete
		free(obj1);
	}

}


/****************************************************************************************/
/*  This function draws the Weld-History screen.										*/
/*  the function checks if the button is pressed or not, if found then draws it in      */
/*  pressed state.																		*/
/*																						*/
/****************************************************************************************/
void CWeldingHistory::Draw(CDC *pDC)
{
	DrawHistoryData(pDC);
}


/**********************************************************************************************/
/* this function handles the mouse click if it is on the Weld-History screen.                  */
/* the function is called on both LButton up and LButton down .								  */
/*																							  */	
/**********************************************************************************************/	
bool CWeldingHistory::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}
/****************************************************************************************/
/*																						*/
/* The following function is used to Draw history data. The function checksthe Top most	*/
/* Data and the Left Most PArameter on the screen and displays next seven weld data		*/
/* from the Top most weld data.															*/
/****************************************************************************************/
void CWeldingHistory::DrawHistoryData(CDC *pDC)
{	
	CRunScreen::Displayable_columns=5;
	int LineNo=1;
	int TotalCyclesDrawn=0;
	if(WeldHistoryList.GetCount())
	{
		POSITION pos = WeldHistoryList.GetHeadPosition();
		for(int CurrentPos=1;CurrentPos<TopMostData;CurrentPos++)
			WeldHistoryList.GetNext(pos);
		DrawRect(pDC, CChildView::Highlight_Color, CRect(8,(HISTORY_TBL_START_Y+LINE_GAP*(SelectedWeldData+3)),
							  (HISTORY_TBL_START_X + 5 * ParamRect_Width - 12),
							  (HISTORY_TBL_START_Y+LINE_GAP*(SelectedWeldData+4))));
		while(pos)
		{	
			if(TotalCyclesDrawn==MaxCyclePerScreen)
				break;
			CWeldingData * Obj = WeldHistoryList.GetNext(pos);
			Obj->DrawHistoryData(pDC,LeftMostParameter, LineNo);
			TotalCyclesDrawn++;
			LineNo++;
		}
	}
	else if(USBWeldHistoryList.GetCount())
	{
		POSITION pos = USBWeldHistoryList.GetHeadPosition();
		LineNo=1;
		for(int CurrentPos=1;CurrentPos<TopMostData;CurrentPos++)
			USBWeldHistoryList.GetNext(pos);
		DrawRect(pDC, CChildView::Highlight_Color, CRect(8,(HISTORY_TBL_START_Y+LINE_GAP*(SelectedWeldData+3)),
							  (HISTORY_TBL_START_X + 5 * ParamRect_Width - 12),
							  (HISTORY_TBL_START_Y+LINE_GAP*(SelectedWeldData+4))));
		while(pos)
		{	
			if(TotalCyclesDrawn==MaxCyclePerScreen)
				break;
			CHistoryData * Obj = USBWeldHistoryList.GetNext(pos);
			if(LineNo==SelectedWeldData)
			{
				SelectedDataUnit=Obj->Units;
				SelectedWeldId=Obj->UniqueId;
			}
			Obj->DrawUSBHistory(pDC,LeftMostParameter, LineNo);
			TotalCyclesDrawn++;
			LineNo++;
		}
	}
	DrawParameterHeadings(pDC);
}
/********************************************************************************************/	
/* The following function is used to draw parameter headings on the Weld history screen.	*/
/* The function checks for the unit of the selected weld data and draws the unit accordingly*/
/*																							*/
/********************************************************************************************/
void CWeldingHistory::DrawParameterHeadings(CDC *pDC)
{
   if(LeftMostParameter>(TotalColoumn-4))
      LeftMostParameter=1;
	CHistoryData * Obj ;
	if(USBWeldHistoryList.GetCount())
	{
		POSITION pos = USBWeldHistoryList.GetHeadPosition();
		for(int i=0;i<TopMostData+SelectedWeldData-1;i++)
		Obj = USBWeldHistoryList.GetNext(pos);
	}
	int X1 = 20;
	int Y1 =60;
	int Width =120;
	int Height = 30;
	    CRect TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
		CRect UnitRect= CRect(X1,Y1+Height,X1+Width,Y1+Height+Height);
	DrawText(pDC, SmallFont, Black, TextRect, CChildView::Parameter_Heading[0],false);
	X1 +=Width;

	for(int index =LeftMostParameter; index<LeftMostParameter+4;index++)
	{
		TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
		 UnitRect= CRect(X1,Y1+Height,X1+Width,Y1+Height+Height);

		if(USBWeldHistoryList.GetCount())
		{
			if(Obj->Units)
				DrawText(pDC, SmallFont, Black, UnitRect,ParameterUnitMetric[index],false);
			else
				DrawText(pDC, SmallFont, Black, UnitRect,ParameterUnitUSCS[index],false);
		}
		for(int index1 =1;index1<CChildView::TotalTextHeading;index1++)
		{
			bool found =false;
			int ID;
			if(USBWeldHistoryList.GetCount())
				ID=(Obj->USBParamIDs[index]);
			else
				ID=Parameter_ID[index];
			if(ID == CChildView::Parameter_ID[index1])
			{
				found =true;
				DrawText(pDC, SmallFont, Black, TextRect, CChildView::Parameter_Heading[index1],false);
			
				if(!USBWeldHistoryList.GetCount())
				{
					if(SelectedDataUnit)
						DrawText(pDC, SmallFont, Black, UnitRect, CChildView::Parameter_Units_Metric[index1],false);
					else
						DrawText(pDC, SmallFont, Black, UnitRect, CChildView::Parameter_Units_USCS[index1],false);
				}
			}	

			if(Parameter_ID[index] ==0)
					DrawText(pDC, SmallFont, Black, TextRect, "****",false);
		}
		X1 +=Width;
	}
		CPen *oldPen;
		CPen NewPen;
		NewPen.CreatePen(PS_SOLID,2,CChildView::Color_Array[Black]);
		oldPen = pDC->SelectObject(&NewPen);
		pDC->MoveTo(20,Y1+2*Height+10);
		pDC->LineTo(X1,Y1+2*Height+10);
		pDC->SelectObject(oldPen);
		NewPen.DeleteObject();
}