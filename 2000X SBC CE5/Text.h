// Text.h: interface for the CText class.
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
  1.1       01/11/08    PDwivedi  Added Member variables.

*/

#if !defined(AFX_TEXT_H__32A5A362_F631_4B5F_9AF7_D97B746B9636__INCLUDED_)
#define AFX_TEXT_H__32A5A362_F631_4B5F_9AF7_D97B746B9636__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
class CXmlElement;

class CText : public CVgaMenuItem  
{
public:
   CText(CString str,int X1,int Y1,int X2,int Y2);
	CText(CXmlElement * e);
	virtual ~CText();
	CString SubText;
   CString FunName;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;

};

#endif // !defined(AFX_TEXT_H__32A5A362_F631_4B5F_9AF7_D97B746B9636__INCLUDED_)
