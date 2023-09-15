// Line.h: interface for the CLine class.
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

#if !defined(AFX_LINE_H__FF8720B7_1798_4E89_8D0B_47B5A2F31B3B__INCLUDED_)
#define AFX_LINE_H__FF8720B7_1798_4E89_8D0B_47B5A2F31B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CLine : public CVgaMenuItem  
{
public:
   CLine(CXmlElement * e);
   virtual ~CLine();

protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC *pDC);

private:
   int LineColor;
   int X1_CoOrdinate;
   int X2_CoOrdinate;
   int Y1_CoOrdinate;
   int Y2_CoOrdinate;
};

#endif // !defined(AFX_LINE_H__FF8720B7_1798_4E89_8D0B_47B5A2F31B3B__INCLUDED_)
