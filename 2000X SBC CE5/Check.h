// Check.h: interface for the CCheck class.
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
  1.1       08/26/08	   PDwivedi  Modify Constructor for making members Public.
*/

#if !defined(AFX_CHECK_H__698727CC_8AE7_4482_8BF8_0CA8A9D38A51__INCLUDED_)
#define AFX_CHECK_H__698727CC_8AE7_4482_8BF8_0CA8A9D38A51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CCheck : public CVgaMenuItem  
{
public:
   CCheck(CXmlElement * e);
   virtual ~CCheck();
   int IsSelected;
   int X_CoOrdinate;
   int Y_CoOrdinate;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;

private:
   int Font;
   int TextColor;
   
};

#endif // !defined(AFX_CHECK_H__698727CC_8AE7_4482_8BF8_0CA8A9D38A51__INCLUDED_)
