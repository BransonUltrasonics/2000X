// VgaRadioButton.h: interface for the VgaRadioButton class.
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
  1.1		04/04/08	PDwivedi  Added member variable Format.	
*/

#if !defined(AFX_VGARADIOBUTTON_H__21FD686F_EB9D_44C7_9DA7_99E5A5CB02DA__INCLUDED_)
#define AFX_VGARADIOBUTTON_H__21FD686F_EB9D_44C7_9DA7_99E5A5CB02DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CVgaRadioButton : public CVgaMenuItem  
{
public:
   bool GetSelected();
   int GetRadioValue();
   void SetSelected(bool radio_state);
   CVgaRadioButton(CXmlElement * e);
   virtual ~CVgaRadioButton();
   bool Selected;
   int ID;
   int value;
   int Format;
   CString FormatString(CString text);
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;

private:
   void SetVariable_Value_radio_button(const CPoint &p,CChildView *view);
};

#endif // !defined(AFX_VGARADIOBUTTON_H__21FD686F_EB9D_44C7_9DA7_99E5A5CB02DA__INCLUDED_)
