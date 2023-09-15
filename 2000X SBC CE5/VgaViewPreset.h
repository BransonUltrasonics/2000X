// VgaViewPreset.h: interface for the CVgaViewPreset class.
//
//////////////////////////////////////////////////////////////////////
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
  1.0       06/06/08	   PDwivedi  Added Initial Version.

*/

#if !defined(AFX_VGAVIEWPRESET_H__5A187165_BE88_45F2_BDC0_719383AA1373__INCLUDED_)
#define AFX_VGAVIEWPRESET_H__5A187165_BE88_45F2_BDC0_719383AA1373__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

#define EXIT_RECT CRect(420,380,510,420)
#define NEXT_RECT CRect(530,380,620,420)
#define BACK_RECT CRect(310,380,400,420)
#define TOTALPAGE 6
#define FIRST_XCORD_FORTEXT	60
#define TOTALHEIGHT			300

class CXmlElement;
class CPrintText;

class CVgaViewPreset : public CVgaMenuItem  
{
public:
   CString PresetNameString;
   void ArrangeCoOrdinate();
	CTypedPtrList<CPtrList, CPrintText *> ViewPresetTextList;
   //CVgaViewPreset(CXmlElement * e,CString PresetName);
   CVgaViewPreset(CString PresetName);
   virtual ~CVgaViewPreset();
   int Page_No;
protected:
   int MaxPageDisplay;
	void DrawTextObjectsList(CDC*pDC);
	void DrawNextBackExiButton(CDC*pDC);
	void DrawPageNumber(CDC *pDC);
	CRect ExitRect;
	CRect NextRect;
	CRect BackRect;
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
   static bool View_Preset_Exit_pressed;
	static bool View_Preset_Next_pressed;
	static bool View_Preset_Back_pressed;
};

#endif // !defined(AFX_VGAVIEWPRESET_H__5A187165_BE88_45F2_BDC0_719383AA1373__INCLUDED_)
