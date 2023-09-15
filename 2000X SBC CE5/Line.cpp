// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////
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
  1.0       04/07/08	   PDwivedi  Added Initial Version.

*/

#include "stdafx.h"
#include "SBC.h"
#include "Line.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**********************************************************************************/
/*                                                                                */
/*  This function creates a CVGALine object When any CVGALine type object is      */
/*  found in  menu/submenu item list.											  */
/**********************************************************************************/
CLine::CLine(CXmlElement * e)
{
	/*Storing Co-ordinates for Line.*/
	 X1_CoOrdinate = _ttoi(e->GetAttribute("X1"));
	 Y1_CoOrdinate = _ttoi(e->GetAttribute("Y1"));
	 X2_CoOrdinate = _ttoi(e->GetAttribute("X2"));
	 Y2_CoOrdinate = _ttoi(e->GetAttribute("Y2"));
	 
	 LineColor=_ttoi(e->GetAttribute("LineColor"));//Line Color.
//	length--;
}

CLine::~CLine()
{
}

/*******************************************************************************/
/*                                                                             */
/*  This function Draws a CVGALine object When any CVGALine type object        */
/*  is found in menu/submenu item list for current page .					   */
/*																			   */
/*******************************************************************************/
void CLine::Draw(CDC *pDC)
{
	rect=CRect(X1_CoOrdinate,Y1_CoOrdinate,X2_CoOrdinate,Y2_CoOrdinate);
	
	/*Drawing Line.*/
	CPen penLine;
	CPen *OldPen;
	penLine.CreatePen(PS_SOLID, 2, CChildView::Color_Array[LineColor]);
	OldPen = pDC->SelectObject(&penLine);
	pDC->MoveTo(X1_CoOrdinate,Y1_CoOrdinate);
	pDC->LineTo(X2_CoOrdinate,Y2_CoOrdinate);
	pDC->SelectObject(OldPen);
	penLine.DeleteObject();
}

bool CLine::MouseClick(const CPoint &p, CChildView *view)
{
	return false;
}
