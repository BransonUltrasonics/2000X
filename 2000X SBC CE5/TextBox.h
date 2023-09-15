// TextBox.h: interface for the CTextBox class.
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
  1.1       08/04/08	   PDwivedi  Changed Boxcolor to public.
*/
#if !defined(AFX_TEXTBOX_H__8217EC8F_40BB_4BD7_9B90_29A5EF0C8722__INCLUDED_)
#define AFX_TEXTBOX_H__8217EC8F_40BB_4BD7_9B90_29A5EF0C8722__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CTextBox : public CVgaMenuItem  
{
public:	
   CTextBox(CXmlElement * e);
	virtual ~CTextBox();
   int BoxColor;
protected:
	virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC *pDC);
private:
	CRect Rect;
	int ID;
	int TextColor;
	int TextFont;

};

#endif // !defined(AFX_TEXTBOX_H__8217EC8F_40BB_4BD7_9B90_29A5EF0C8722__INCLUDED_)
