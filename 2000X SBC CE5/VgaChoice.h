// VgaChoice.h: interface for the CVgaChoice class.
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
  1.2       06/06/08    PDwivedi  Added Members Declarationn for function Name.
*/

#if !defined(AFX_VGACHOICE_H__785627E6_1006_4D1B_8B50_D4BCB05F8845__INCLUDED_)
#define AFX_VGACHOICE_H__785627E6_1006_4D1B_8B50_D4BCB05F8845__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
class CXmlElement;

class CVgaChoice : public CVgaMenuItem  
{
public:
	CVgaChoice(CXmlElement * e);
	virtual ~CVgaChoice();
	CString ChoiceText1;
	CString ChoiceText2;
	CString ChoiceText;
   int Choice_value;
   CString submenu;
   CString FunName;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;

};

#endif // !defined(AFX_VGACHOICE_H__785627E6_1006_4D1B_8B50_D4BCB05F8845__INCLUDED_)
