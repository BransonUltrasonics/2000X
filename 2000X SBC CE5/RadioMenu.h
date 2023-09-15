// RadioMenu.h: interface for the CRadioMenu class.
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
  1.0       10/23/07	   PDwivedi    Added Initial Version.
  1.1       01/11/08    PDwivedi	   Added Member Declartion  .
  1.2		   04/04/08	   PDwivedi	   Added MAXRADIOINDEX.
  1.3       04/14/08    PDwivedi	   Remove MAXRADIOINDEX.
  1.4       11/06/09    PDwivedi    Added changes for showing String Number.

*/

#if !defined(AFX_RADIOMENU_H__888BA3BF_DB3B_4191_A62E_1A1727F3DD26__INCLUDED_)
#define AFX_RADIOMENU_H__888BA3BF_DB3B_4191_A62E_1A1727F3DD26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
class CXmlElement;
//#define MAXRADIOINDEX  14

class CRadioMenu : public CVgaMenuItem  
{
public:
   CRadioMenu(CXmlElement * e);
   virtual ~CRadioMenu();
   CStringArray RadioMenuStr;
   CStringArray RadioMenuStrID;
   CString VarText;
   CString FormatString(CString text);
   CString StrtextID;
   CString submenu;
   int RadioIndex;
   bool Insertunitflag;
   int Format;
   void SetSelectedRadioIndex(CVgaMenu * CurrMenuLst);
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;

};

#endif // !defined(AFX_RADIOMENU_H__888BA3BF_DB3B_4191_A62E_1A1727F3DD26__INCLUDED_)
