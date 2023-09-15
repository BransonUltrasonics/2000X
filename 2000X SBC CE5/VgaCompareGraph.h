// VgaCompareGraph.h: interface for the CVgaCompareGraph class.
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

#if !defined(AFX_VGACOMPAREGRAPH_H__857615F0_61F8_4C23_B7A2_8F2C7A89BE47__INCLUDED_)
#define AFX_VGACOMPAREGRAPH_H__857615F0_61F8_4C23_B7A2_8F2C7A89BE47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
#define GRAPH_START_X_CORD	100
#define GRAPH_START_Y_CORD	45
#define GRAPH_END_X_CORD	500
#define GRAPH_END_Y_CORD	389
#define HSGRAPH_HEIGHT	344

class CXmlElement;

class CVgaCompareGraph : public CVgaMenuItem  
{
public:
	CVgaCompareGraph();
	virtual ~CVgaCompareGraph();
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
};

#endif // !defined(AFX_VGACOMPAREGRAPH_H__857615F0_61F8_4C23_B7A2_8F2C7A89BE47__INCLUDED_)
