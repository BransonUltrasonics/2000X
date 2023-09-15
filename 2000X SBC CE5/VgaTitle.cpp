// VgaTitle.cpp: implementation of the CVgaTitle class.
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
  1.1       01/11/08    PDwivedi  Modified Constructor.
  1.2       08/01/08	   PDwivedi  Added Default Constructor.
  1.3       08/08/08    PDwivedi  Final Code Clean up.
  1.4       09/02/08    PDwivedi  Modify Draw for BottomHalf Screen.
  1.5       09/09/08    PDwivedi  Added changes for string Debug Menu.
  1.6       11/12/08    PDwivedi  Added changes for SBC Fatal Error.
*/

#include "stdafx.h"
#include "SBC.h"
#include "VgaTitle.h"
#include "XmlElement.h"
#include "Variable.h"

//#include "GUIDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVgaTitle::CVgaTitle(CString Title)
{
	text = Title;
   RectShow=1;
   rows = DEFAULT_NO_ROWS;
   columns = DEFAULT_NO_COLUMNS;
	ButtonTypes = DEFAULT_BUTTONTYPE;
   ExitFlag = 0;
   SaveFlag = 0;
	ObjectPageNum=PAGEALL;
   BottomHalfPresent=false;
}

CVgaTitle::CVgaTitle(CXmlElement * element)
{
	textID=element->GetAttribute("textID");
   text=CVgaMenuItem ::LinearSearch(textID);
   TitleArray.SetSize(MAXTITLE);
	RectShow=1;
	text.MakeUpper();
	justify = element->GetAttribute("justify");
	pageinfo = element->GetBoolAttribute("pageinfo");
	rows = _ttoi(element->GetAttribute("RowPerPage"));
   columns = _ttoi(element->GetAttribute("ColumnPerPage"));
	ButtonTypes = _ttoi(element->GetAttribute("Buttontype"));
   ExitFlag=_ttoi(element->GetAttribute("ExitFlag"));
   SaveFlag=_ttoi(element->GetAttribute("SaveFlag"));
   CString MenuPresent=element->GetAttribute("BottomHalfPresent");
   if(MenuPresent!="")
      BottomHalfPresent=_ttoi(MenuPresent);
   else
      BottomHalfPresent=false;
	ObjectPageNum=PAGEALL;
	POSITION pos = element->children.GetHeadPosition();
   int i=0;
	while (pos)
	{
		CXmlElement * e = element->children.GetNext(pos);
		CString tag = e->GetTag();
		if (tag == "condition")
			AddCondition(e);
      else if(tag=="titles")
      {
         CString TitleString = e->GetAttribute("TitleID");
         TitleArray[i]= CVgaMenuItem ::LinearSearch(TitleString);
         i++;
      }
		else
			ASSERT(FALSE);
	}
}

CVgaTitle::~CVgaTitle()
{
	
}

void CVgaTitle::Draw(CDC *pDC) 
{
   CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;

   if(BottomHalfPresent==true)
   {
      CChildView::thisPtr->BottomHalfScreen=true;
   }
   else
      CChildView::thisPtr->BottomHalfScreen=false;
   rect=Title_Rect;
	DrawRect(pDC,CChildView::TitleBarColor, Title_Rect);
   CVgaMenuItem::DrawText(pDC, Bigfont, White, Title_Rect,TempText,true);

}

bool CVgaTitle::MouseClick(const CPoint &p, CChildView *view)
{
	// do nothing, no clicking on menu title
	return false;
}
