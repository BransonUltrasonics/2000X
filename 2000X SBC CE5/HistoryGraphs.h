/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/HistoryGraphs.h_v   1.2   18 Sep 2008 17:16:54   pdwivedi  $ */
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
 1.0		10/14/05	   PDwivedi	   Added Initial Version
 1.1     08/01/08    PDwivedi    Changed Base Class.
 1.2     09/18/08    PDwivedi    Added changes for graph screen background color. 

*/
// HistoryGraphs.h: interface for the CHistoryGraphs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTORYGRAPHS_H__0D7907A3_195F_4F40_9343_EA8AC563F972__INCLUDED_)
#define AFX_HISTORYGRAPHS_H__0D7907A3_195F_4F40_9343_EA8AC563F972__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "VfdObject.h"
#include "ChildView.h"
//#include "DrawGraph.h"
#include "VgaMenuItem.h"


//class CDrawGraph;
class CXmlElement;
class CVgaDrawGraph;
class CHistoryGraphs  : public CVgaMenuItem//CVfdObject  
{
public:
	static CString HistoryDataPath;
	int LastGraphDisplayed;
	int Graph1ID;
	int Graph2ID;
	void DisplayGraphs(CDC *pDC);
	CHistoryGraphs();
	virtual ~CHistoryGraphs();
	
	int lang_index;
	virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC *pDC);
	CTypedPtrList<CPtrList, CVgaDrawGraph *> HistoryGraphList;
};

#endif // !defined(AFX_HISTORYGRAPHS_H__0D7907A3_195F_4F40_9343_EA8AC563F972__INCLUDED_)





