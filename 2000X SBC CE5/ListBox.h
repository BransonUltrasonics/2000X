// ListBox.h: interface for the CListBox class.
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
*/
#if !defined(AFX_LISTBOX_H__DB6EB6F6_40CC_42AF_ABD7_DC91A6E635E0__INCLUDED_)
#define AFX_LISTBOX_H__DB6EB6F6_40CC_42AF_ABD7_DC91A6E635E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_PRESETS_DISPLAYED 11
#define ListBox_OneLineHeight	31

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CListBoxObject : public CVgaMenuItem  
{
public:
	CListBoxObject(CXmlElement * e);
	virtual ~CListBoxObject();
	int CurrentRunningSequencePreset;
	static bool SequencingScreen;
	int TotalText;
   int MaxPreset;
	//CString * ListBoxText;
   CStringArray ListBoxText;
   CStringArray PresetInfoText;
	static CString CurrentPresetName;
	static CString CurrentSequencePresetName;
   int Type;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;

private:
	

	int ID;
	int ListBox_Color;
	int X1_CoOrdinate;
	int X2_CoOrdinate;
	int Y1_CoOrdinate;
	int Y2_CoOrdinate;
};

#endif // !defined(AFX_LISTBOX_H__DB6EB6F6_40CC_42AF_ABD7_DC91A6E635E0__INCLUDED_)
