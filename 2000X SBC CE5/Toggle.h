// Toggle.h: interface for the CToggle class.
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
  1.1       01/11/08    PDwivedi  Added Members Declaration.
  1.2       06/06/08    PDwivedi  Added Members Declaration for function name.
  1.3       08/01/08    PDwivedi  Added member for sequencing enable.
*/

#if !defined(AFX_TOGGLE_H__45C0132D_8514_4DD3_AE55_BDC23E01D7AC__INCLUDED_)
#define AFX_TOGGLE_H__45C0132D_8514_4DD3_AE55_BDC23E01D7AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
class CXmlElement;

class CToggle : public CVgaMenuItem  
{
public:
	CToggle(CXmlElement * e);
	virtual ~CToggle();
   static bool SequencingON;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
public:
   bool Toggle_Value;
   CString Toggle_Text1;
   CString Toggle_Text2;
   CString Toggle_Text;
   CString FunName;
};

#endif // !defined(AFX_TOGGLE_H__45C0132D_8514_4DD3_AE55_BDC23E01D7AC__INCLUDED_)
