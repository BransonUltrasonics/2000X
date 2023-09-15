// BottomHalf.h: interface for the BottomHalf class.
//
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
  1.1       04/16/08    PDwivedi  Added New # define. 
  1.2       06/06/08    PDwivedi  Remove New # define for cold Start.
  1.2       09/02/08    PDwivedi  Modify Constructor for BottomHalf Screen.
*/

#if !defined(AFX_BOTTOMHALF_H__C8E60D5F_E125_4426_A679_D59D1A861457__INCLUDED_)
#define AFX_BOTTOMHALF_H__C8E60D5F_E125_4426_A679_D59D1A861457__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

//#define HORNDOWN_ID  401

class CXmlElement;

class CBottomHalf : public CVgaMenuItem  
{
public:
   CBottomHalf(CXmlElement * e);
   virtual ~CBottomHalf();
   static CRect BottomHalfRect;
   CString submenu;
   int Refresh;
   static int BottomHalfId;
   static CVgaMenu *BottomMenuPointer;
   int RefreshTime;
   int Bottomtype;
   static bool HornDownScreenPresent;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;

private:
   int X1_CoOrdinate;
   int Y1_CoOrdinate;
   int X2_CoOrdinate;
   int Y2_CoOrdinate;
   int FillColor;
};

#endif // !defined(AFX_BOTTOMHALF_H__C8E60D5F_E125_4426_A679_D59D1A861457__INCLUDED_)
