// RunScreen.cpp: implementation of the CRunScreen class.
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
  1.0       10/23/07	   PDwivedi  Added Initial Version.
  1.1       08/08/08    PDwivedi  Final Code Clean up.
  1.2       11/06/09    PDwivedi  Added changes for showing String Number.

*/
#include "stdafx.h"
#include "SBC.h"
#include "RunScreen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRunScreen::CRunScreen(CXmlElement * e)
{
	rect = CRect(_ttoi(e->GetAttribute("X1"))+XOFFSET,
				 _ttoi(e->GetAttribute("Y1"))+YOFFSET,
				 _ttoi(e->GetAttribute("X2"))+XOFFSET,
				 _ttoi(e->GetAttribute("Y2"))+YOFFSET);

	RunID=	_ttoi(e->GetAttribute("StructID"));	
	
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
}

int CRunScreen::Displayable_columns=0;
int* CRunScreen::ID_Array;
int  *CRunScreen::Parameter_ID;
CRunScreen::~CRunScreen()
{
	delete []Parameter_ID;
	while (WeldDataList.GetCount()>0)
		delete WeldDataList.RemoveHead();
}

/*************************************************************************************/
/*                                                                                   */
/*  This function Draws a Weld Data When any Weld Data is found in menu/submenu item */
/*  list for current page .															 */
/*																					 */		 
/*************************************************************************************/
void CRunScreen::Draw(CDC *pDC)
{
	int X1 = 8;
	int Y1 =100;
	int Width =120;
	int Height = 30;
	    CRect TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
		CRect UnitRect= CRect(X1,Y1+Height,X1+Width,Y1+Height+Height);
	for(int index =0; index<5;index++)
	{
		TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
		 UnitRect= CRect(X1,Y1+Height,X1+Width,Y1+Height+Height);
		for(int index1 =0;index1<CChildView::TotalTextHeading;index1++)
		{
			bool found =false;
			if(Parameter_ID[index] == CChildView::Parameter_ID[index1])
			{
				found =true;

            CString TempParamHeading = CChildView::Parameter_Heading[index1];
            if(CChildView::thisPtr->StringDebugFlag)
               TempParamHeading = CChildView::WeldDataPatamStringID[index1] + _T(" ")+ CChildView::Parameter_Heading[index1];

				DrawText(pDC, SmallFont, Black, TextRect, TempParamHeading,false);
				if(CChildView::metric)
					DrawText(pDC, SmallFont, Black, UnitRect, CChildView::Parameter_Units_Metric[index1],false);
				else
					DrawText(pDC, SmallFont, Black, UnitRect, CChildView::Parameter_Units_USCS[index1],false);
			}
			if(Parameter_ID[index] ==0)
					DrawText(pDC, SmallFont, Black, TextRect, "****",false);
		}
		X1 +=Width;
	}
 

	POSITION pos = WeldDataList.GetHeadPosition();
	CWeldingData::CycleCount=0;
	while(pos)
	{
		CWeldingData * Obj = WeldDataList.GetNext(pos);
		Obj->Draw(pDC);
	}
}

bool CRunScreen::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}


CRunScreen::UpdateWeldData(unsigned char *&data, int &length, bool Constructor)
{
	int TotalColoumn = *data++;length--;
	ID_Array=new int[TotalColoumn];
	for(int columns =0;columns< TotalColoumn; columns++)
	{
		ID_Array[columns] =*data++;
		length--;
	}
	ReceivedUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	int TotalCycle =*data++;length--;
	CTypedPtrList<CPtrList, CWeldingData *> TempWeldDataList;
		for(int cycle =0;cycle<TotalCycle;cycle++)
		{
			CWeldingData * obj = new CWeldingData(data, length,TotalColoumn);
			TempWeldDataList.AddHead(obj);
		}
		while(TempWeldDataList.GetCount()>0)
		{
			CWeldingData * obj = TempWeldDataList.RemoveHead();
			WeldDataList.AddHead(obj);
		}
		delete []  ID_Array;
	while(WeldDataList.GetCount()>7)
		delete WeldDataList.RemoveTail();
}
