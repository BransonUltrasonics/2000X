// LocalChoice.h: interface for the CLocalChoice class.
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

#if !defined(AFX_LOCALCHOICE_H__88D3C4DF_8339_4C8B_808E_DD6C456A8328__INCLUDED_)
#define AFX_LOCALCHOICE_H__88D3C4DF_8339_4C8B_808E_DD6C456A8328__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
class CXmlElement;


class CLocalChoice : public CVgaMenuItem  
{
public:
	CLocalChoice(CXmlElement * e);
	virtual ~CLocalChoice();
   CString ChoiceText1;
	CString ChoiceText2;
	CString ChoiceText;
   CString FunName;
   int TextColor;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
private:
   CRect Rect;
};

#endif // !defined(AFX_LOCALCHOICE_H__88D3C4DF_8339_4C8B_808E_DD6C456A8328__INCLUDED_)
