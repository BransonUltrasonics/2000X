/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/HistoryGraphs.cpp_v   1.6   18 Sep 2008 17:16:52   pdwivedi  $ */
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
 1.0		10/14/05	BWadia	Added Initial Version
 1.1		10/24/05	BWadia	Modified DisplayGraph() function for Graph Vertical Labels
 1.2		02/07/06	BWadia	Called function Draw_Pressed_Released_Button() instead of Invalidate()
 1.3		09/18/06	BSahu	   Modified For Title.
 1.4     08/01/08 PDwivedi Removed All Local Strings.
 1.5     09/12/08 PDwivedi Added changes for Tracker issues of round 2 testing for version LangTestJ.
 1.6     09/18/08 PDwivedi Added changes for graph screen background color. 

*/
// HistoryGraphs.cpp: implementation of the CHistoryGraphs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SBC.h"
#include "HistoryGraphs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHistoryGraphs::CHistoryGraphs()
{
	Graph1ID=0;
	Graph2ID=0;
	LastGraphDisplayed=0;
}

CString CHistoryGraphs::HistoryDataPath;
CHistoryGraphs::~CHistoryGraphs()
{
	while(HistoryGraphList.GetCount())
		free(HistoryGraphList.RemoveHead());
}

void CHistoryGraphs::Draw(CDC *pDC)
{
   CBrush brush;
	brush.CreateSolidBrush(CChildView::thisPtr->Color_Array[White]);
	CBrush * oldBrush;
	oldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(CRect(0 + XOFFSET, 40 + XOFFSET, 640 + XOFFSET, 480 + YOFFSET));
	pDC->SelectObject(oldBrush);
   brush.DeleteObject();
	DisplayGraphs(pDC);
}


/**********************************************************************************************/
/* this function handles the mouse click if it is on the Weld-History screen.                  */
/* the function is called on both LButton up and LButton down .								  */
/*																							  */	
/**********************************************************************************************/	
bool CHistoryGraphs::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}

void CHistoryGraphs::DisplayGraphs(CDC *pDC)
{
   CVgaDrawGraph::GraphBoundary=false;
	POSITION pos = HistoryGraphList.GetHeadPosition();
	while(pos)
	{	
		CVgaDrawGraph *Object = HistoryGraphList.GetNext(pos);
		if(Object->GraphData.graph_type==Graph1ID)
		{
			Object->HSCompareGraph=false;
			Object->GraphData.GraphNum=1;
			Object->DrawGraphBoundary(pDC);//Draw Graph boundary only once in case of dual graph.
			Object->drawgraph(pDC);
			Object->DrawTickMarks(pDC);
			Object->DrawHLabel(pDC);
			Object->DrawVLabel(pDC);
			CVgaDrawGraph::GraphBoundary=true;
		}
		if(Object->GraphData.graph_type==Graph2ID)
		{
			Object->HSCompareGraph=false;
			Object->GraphData.GraphNum=2;
			Object->drawgraph(pDC);
			Object->YAxis2Graduation(pDC);
			Object->DrawVLabel(pDC);
		}
	}
	CVgaDrawGraph::GraphBoundary=false;
}


