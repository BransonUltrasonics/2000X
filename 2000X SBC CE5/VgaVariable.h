// VgaVariable.h: interface for the CVgaVariable class.
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
  1.2       08/01/08	   PDwivedi  Added Function Member.
  1.3       11/06/09    PDwivedi  Added changes for showing String Number.

*/

#if !defined(AFX_VGAVARIABLE_H__482403E8_6776_4BB9_812B_5C17F569B447__INCLUDED_)
#define AFX_VGAVARIABLE_H__482403E8_6776_4BB9_812B_5C17F569B447__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CVgaVariable : public CVgaMenuItem  
{
public:
	CVgaVariable(CXmlElement * element);
	virtual ~CVgaVariable();
	CString Variable_Text;
	int IDVariable;
	CString Keypad_title;			
	int		Format;			
	int		Digits;			
	int		Value;				
	int		MinVal;			
	int		MaxVal;			
	int		Disable;			
	int		Bitmask;			
	int		NewVal;
	int		ID;				//	Variable ID
   int TextType;
   int DisableFlag;
   bool Insertunitflag;
   int  Unitshow; 
   CString CurrentString,CurrentStringID;
   CString NewString,NewStringID;
   CString FunName;
protected:
   bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
	
};

#endif // !defined(AFX_VGAVARIABLE_H__482403E8_6776_4BB9_812B_5C17F569B447__INCLUDED_)
