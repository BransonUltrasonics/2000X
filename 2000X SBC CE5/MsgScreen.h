// MsgScreen.h: interface for the CMsgScreen class.
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
  1.0       01/11/08	PDwivedi  Added Initial Version.
  1.1		   04/04/08	PDwivedi  Added Member Variables.
  1.2		   11/06/09 PDwivedi  Added changes for showing String number on MsgScreen.
*/
#if !defined(AFX_MSGSCREEN_H__FC9B3150_8285_4BF1_B7BE_B01ABF8FE1E2__INCLUDED_)
#define AFX_MSGSCREEN_H__FC9B3150_8285_4BF1_B7BE_B01ABF8FE1E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CMsgScreen : public CVgaMenuItem  
{
public:
   CMsgScreen(CXmlElement * e);
   virtual ~CMsgScreen();
   CString submenu;
   CString menunak;
   int ResponseType;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC *pDC);
public:
   int FillColor;
   int X1_CoOrdinate;
   int X2_CoOrdinate;
   int Y1_CoOrdinate;
   int Y2_CoOrdinate;
   int Time;
   int TextFont;
   int TextColor;
   CString MsgLine1,MsgLine2,MsgLine3;
   CString MsgLine1ID,MsgLine2ID,MsgLine3ID;
};

#endif // !defined(AFX_MSGSCREEN_H__FC9B3150_8285_4BF1_B7BE_B01ABF8FE1E2__INCLUDED_)
