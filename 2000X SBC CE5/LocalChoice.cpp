// LocalChoice.cpp: implementation of the CLocalChoice class.
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
  1.1       08/08/08    PDwivedi  Final Code Clean up.
  1.2       09/09/08    PDwivedi  Added String Debug changes.
  1.3       09/18/08    PDwivedi  Added changes for default color.

*/

#include "stdafx.h"
#include "SBC.h"
#include "LocalChoice.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLocalChoice::CLocalChoice(CXmlElement * e)
{
   rect = CRect(0, 0, 0, 0);
   RectShow=1;
   textID=e->GetAttribute("textID");
   text=CVgaMenuItem ::LinearSearch(textID);
   FunName=e->GetAttribute("FunName");
   int X1 = _ttoi(e->GetAttribute("X1"));
	int Y1 = _ttoi(e->GetAttribute("Y1"));
	int X2 = _ttoi(e->GetAttribute("X2"));
	int Y2 = _ttoi(e->GetAttribute("Y2"));
   Rect = CRect(X1,Y1,X2,Y2);
   TextColor = _ttoi(e->GetAttribute("TextColor"));//storing Text color.
   ChoiceText1=CVgaMenuItem ::LinearSearch(e->GetAttribute("ID1"));
   ChoiceText2=CVgaMenuItem ::LinearSearch(e->GetAttribute("ID2"));
   ChoiceText="";
   POSITION pos = e->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * element = e->children.GetNext(pos);
		CString tag = element->GetTag();
		if (tag == "condition")
      {
         AddCondition(element);
      }
		else
			ASSERT(FALSE);
	}
}

CLocalChoice::~CLocalChoice()
{
   
}

void CLocalChoice::Draw(CDC *pDC)
{
   CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;
   
   SetRect(Rect);
   DrawRect(pDC, CChildView::Button_Color, rect);
	Draw_Pressed_Released_Button(pDC);
   if(TextColor==White)
      TextColor=CChildView::TextColor;
	DrawText(pDC, SmallFont, TextColor, rect, TempText+ChoiceText,true);
}

bool CLocalChoice::MouseClick(const CPoint &p, CChildView *view)
{
   if(FunName!="")
   {
      void *ptr;
      void (*rmn)(int,CLocalChoice *);
      if(functionCall.Lookup(FunName,ptr))
		{
			 rmn = (void (*)(int,CLocalChoice *))ptr;
			 rmn(EnumID,this);
      }
   }
   return true;
}

