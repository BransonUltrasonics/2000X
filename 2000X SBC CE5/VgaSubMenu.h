// VgaSubMenu.h: interface for the CVgaSubMenu class.
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
  1.1       01/11/08    PDwivedi  Added Member Declarations.  

*/

#if !defined(AFX_VGASUBMENU_H__F86048ED_FAF7_4939_B005_7E357A4AFA54__INCLUDED_)
#define AFX_VGASUBMENU_H__F86048ED_FAF7_4939_B005_7E357A4AFA54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CVgaSubMenu : public CVgaMenuItem  
{
public:
	CVgaSubMenu(CXmlElement * e);
	virtual ~CVgaSubMenu();
   CString submenu;
   CString menuNak;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
};

#endif // !defined(AFX_VGASUBMENU_H__F86048ED_FAF7_4939_B005_7E357A4AFA54__INCLUDED_)
