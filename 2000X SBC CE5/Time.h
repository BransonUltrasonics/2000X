// Time.h: interface for the CTime class.
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
  1.2		   04/04/08    PDwivedi	 Define Strings For KeyPad.
  1.3       11/06/09    PDwivedi  Added changes for showing String Number.


*/

#if !defined(AFX_TIME_H__0B012D1A_F0BA_4F99_9A02_D5608619D8AF__INCLUDED_)
#define AFX_TIME_H__0B012D1A_F0BA_4F99_9A02_D5608619D8AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
class CXmlElement;

class CVgaTime : public CVgaMenuItem  
{
public:
   CVgaTime(CXmlElement * e);
   virtual ~CVgaTime();
   CString Time_Text;
   CString CurrentString,CurrentStringID;
   CString NewString,NewStringID;
   CString Str_Reenter,Str_ReenterID;
   CString StrInvalidEntry,StrInvalidEntryID;
protected:

   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC *pDC);
};

#endif // !defined(AFX_TIME_H__0B012D1A_F0BA_4F99_9A02_D5608619D8AF__INCLUDED_)
