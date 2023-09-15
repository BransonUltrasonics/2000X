// VGAAdd_Back_Next_Button.h: interface for the CVGAAdd_Back_Next_Button class.
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

*/

#if !defined(AFX_VGAADD_BACK_NEXT_BUTTON_H__D9F166AA_46F4_407E_A4EF_E39A913F98ED__INCLUDED_)
#define AFX_VGAADD_BACK_NEXT_BUTTON_H__D9F166AA_46F4_407E_A4EF_E39A913F98ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"

#define NextButtonRect	CRect(X_CORDINATE_BACK_NEXT,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define BackButtonRect CRect(20,Y_CORDINATE_BACK_NEXT,BUTTON_WIDTH_BACK_NEXT+20,BUTTON_HEIGHT+Y_CORDINATE_BACK_NEXT)

class CVGAAdd_Back_Next_Button : public CVgaMenuItem  
{
public:
	CVGAAdd_Back_Next_Button(int type);
	virtual ~CVGAAdd_Back_Next_Button();

protected:
virtual bool MouseClick(const CPoint &p, CChildView *view);
virtual void Draw(CDC * pDC) ;
};

#endif // !defined(AFX_VGAADD_BACK_NEXT_BUTTON_H__D9F166AA_46F4_407E_A4EF_E39A913F98ED__INCLUDED_)
