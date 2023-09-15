// VgaTitle.h: interface for the CVgaTitle class.
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
  1.2       08/01/08	   PDwivedi  Added Member Declarations for default rows & columns.
  1.3       08/08/08    PDwivedi  Final Code Clean up.
  1.4       09/02/08    PDwivedi  Modify Constructor for BottomHalf Screen.
*/

#if !defined(AFX_VGATITLE_H__2D23F0E5_60ED_4343_8C39_A46F67189311__INCLUDED_)
#define AFX_VGATITLE_H__2D23F0E5_60ED_4343_8C39_A46F67189311__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define Title_Rect CRect(1+XOFFSET, 0+YOFFSET, 639+XOFFSET, 40+YOFFSET)
#define DEFAULT_NO_ROWS    4
#define DEFAULT_NO_COLUMNS    2
#define DEFAULT_BUTTONTYPE    2
#define MAXTITLE  16
#include "ChildView.h"
#include "VgaMenuItem.h"

class CXmlElement;

class CVgaTitle : public CVgaMenuItem  
{
public:
   CVgaTitle(CString Title);
	CVgaTitle(CXmlElement * element);
	virtual ~CVgaTitle();
   CStringArray TitleArray;
   int ButtonTypes;
   int rows;
   int columns;
   int ExitFlag;
   int SaveFlag;
   bool BottomHalfPresent;
protected:
   bool MouseClick(const CPoint &p, CChildView *view);
	friend void MyFunc(CVgaTitle  *);
	virtual void Draw(CDC * pDC) ;
   CString justify;
	bool pageinfo;
};

#endif // !defined(AFX_VGATITLE_H__2D23F0E5_60ED_4343_8C39_A46F67189311__INCLUDED_)
