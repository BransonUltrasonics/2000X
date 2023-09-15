// AlarmButton.h: interface for the CAlarmButton class.
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

#if !defined(AFX_ALARMBUTTON_H__CC4BC1B5_9A42_41F5_BB9E_58944F49C944__INCLUDED_)
#define AFX_ALARMBUTTON_H__CC4BC1B5_9A42_41F5_BB9E_58944F49C944__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CAlarmButton : public CVgaMenuItem  
{
public:
	CAlarmButton(CXmlElement * e);
	virtual ~CAlarmButton();
   CString Text1;
	CString Text2;
   CString MenuName;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC *pDC);
private:
	CRect Rect;
   int TextColor;
   int BoxColor;
};

#endif // !defined(AFX_ALARMBUTTON_H__CC4BC1B5_9A42_41F5_BB9E_58944F49C944__INCLUDED_)
