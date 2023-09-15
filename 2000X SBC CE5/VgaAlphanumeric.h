// VgaAlphanumeric.h: interface for the CVgaAlphanumeric class.
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
  1.1		   04/04/08	PDwivedi	 Added Member Variable.
  1.2       08/26/08	PDwivedi  Added function name to class.
*/
#if !defined(AFX_VGAALPHANUMERIC_H__E59CF875_A20C_4BCB_9F33_8E35978DD160__INCLUDED_)
#define AFX_VGAALPHANUMERIC_H__E59CF875_A20C_4BCB_9F33_8E35978DD160__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CVgaAlphanumeric : public CVgaMenuItem  
{
public:
   CVgaAlphanumeric(CXmlElement * e);
   virtual ~CVgaAlphanumeric();
   CString Alpha_Text;
   int CharAllowed;
   int CharHidden;
   CString TitleKeyPad;
   CString MenuNak;
   CString MenuAck;
   int ShowValue;
   CString CurrentString;
   CString NewString;
   CString CurrentAlphaValue;
   CString FunName;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC *pDC);
};

#endif // !defined(AFX_VGAALPHANUMERIC_H__E59CF875_A20C_4BCB_9F33_8E35978DD160__INCLUDED_)
