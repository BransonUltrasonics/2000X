// Date.h: interface for the CDate class.
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
  1.1       01/11/08    PDwivedi  Added Member declarations.
  1.2       04/04/08	   PDwivdi   Define Strings For KeyPad.
  1.3       11/06/09    PDwivedi  Added changes for showing String number Date KeyPad.

*/

#if !defined(AFX_DATE_H__2486C00D_741D_42F2_83F7_C8FDDE3C8348__INCLUDED_)
#define AFX_DATE_H__2486C00D_741D_42F2_83F7_C8FDDE3C8348__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;
class CDate : public CVgaMenuItem  
{
public:
   CDate(CXmlElement * e);
   virtual ~CDate();
   CString Date_Text;
   CString CurrentString,CurrentStringID;
   CString NewString,NewStringID;
   CString Str_Reenter,Str_ReenterID;
   CString StrInvalidEntry,StrInvalidEntryID;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC *pDC);
};

#endif // !defined(AFX_DATE_H__2486C00D_741D_42F2_83F7_C8FDDE3C8348__INCLUDED_)
