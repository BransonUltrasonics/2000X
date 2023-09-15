// VgaCompareGraph.cpp: implementation of the CVgaCompareGraph class.
//
//////////////////////////////////////////////////////////////////////
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
  1.0       06/06/08	   PDwivedi  Added Initial Version.

*/

#include "stdafx.h"
#include "SBC.h"
#include "VgaCompareGraph.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVgaCompareGraph::CVgaCompareGraph()
{

}

CVgaCompareGraph::~CVgaCompareGraph()
{

}

/************************************************/
/*                                              */
/*  This function Draws Compare graph screen.   */                                        
/************************************************/
void CVgaCompareGraph::Draw(CDC *pDC)
{
	/*Draw Graph Boundray if no graph is present or on.*/
	if(	!CChildView::thisPtr->ScanA_On && !CChildView::thisPtr->ScanB_On && !CChildView::thisPtr->ScanC_On && !CChildView::thisPtr->CurrentScan_On)
   {
		CPen pen_bounding;
		CPen *oldpen;
		pen_bounding.CreatePen( NULL , 2, CChildView::Color_Array[Black]);
		oldpen=pDC->SelectObject(&pen_bounding);
		pDC->MoveTo(GRAPH_START_X_CORD,GRAPH_START_Y_CORD);
		pDC->LineTo(GRAPH_END_X_CORD,GRAPH_START_Y_CORD);
		pDC->LineTo(GRAPH_END_X_CORD,GRAPH_END_Y_CORD);
		pDC->LineTo(GRAPH_START_X_CORD,GRAPH_END_Y_CORD);
		pDC->LineTo(GRAPH_START_X_CORD ,GRAPH_START_Y_CORD);
		/*Draw Y Axis graduation*/
		int Index;
		for (Index = 0; Index <= 16; Index++ ) 
		{
			int Y1 = GRAPH_START_Y_CORD + (HSGRAPH_HEIGHT-72) - (int)(Index * 16);//(-72)
      		pDC->MoveTo(((GRAPH_START_X_CORD - 3)),(Y1-2));
			pDC->LineTo(((GRAPH_START_X_CORD + 3)),(Y1-2));
		}
		/*Draw X Axis graduation*/
		for (Index = 1; Index < INCLABEL; Index++ ) 
		{
			int X1 = GRAPH_START_X_CORD+ ((Index * GRAPH_WIDTH)/INCLABEL);
			pDC->MoveTo(X1,(HSGRAPH_HEIGHT+(GRAPH_START_Y_CORD  - 3)));
			pDC->LineTo(X1,(HSGRAPH_HEIGHT+(GRAPH_START_Y_CORD  + 3))) ;
		}
		pDC->SelectObject(&oldpen);
		pen_bounding.DeleteObject( );
		pen_bounding.CreatePen( NULL , 1, CChildView::Color_Array[Black]);
		oldpen=pDC->SelectObject(&pen_bounding);
		int LineProp_Y1 = GRAPH_START_Y_CORD + HSGRAPH_HEIGHT -202;
		int LineProp_X1 = GRAPH_START_X_CORD;
		int LineProp_X2 = LineProp_X1+ 8;
		while(LineProp_X2 <= (GRAPH_START_X_CORD + GRAPH_WIDTH))
		{
			pDC->MoveTo(LineProp_X1,LineProp_Y1);
			pDC->LineTo(LineProp_X2,LineProp_Y1);
			LineProp_X1 = LineProp_X2 + 4;
			LineProp_X2 = LineProp_X1 + 8;  
		}
		pDC->SelectObject(&oldpen);
		pen_bounding.DeleteObject( );
	}
	
}

/********************************************************************************/
/* this function handles the mouse click if it is on the Buttons on the screen.	*/
/*																		        */	
/********************************************************************************/	
bool CVgaCompareGraph::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}
