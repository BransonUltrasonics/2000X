// TextBox.cpp: implementation of the CTextBox class.
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
  1.0       06/06/08	   PDwivedi  Added Initial Version.
  1.1       09/09/08    PDwivedi  Added changes for string Debug Menu.

*/
#include "stdafx.h"
#include "SBC.h"
#include "TextBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/*************************************************************************************/
/*                                                                                   */
/*  This function creates a CVGATextBox object When any CVGATextBox type object is	 */
/*  found in  menu/submenu item list                                                 */
/*************************************************************************************/
CTextBox::CTextBox(CXmlElement * e)
{
   textID=e->GetAttribute("textID");
   text=CVgaMenuItem ::LinearSearch(textID);
	/*Storing Co-Ordinates of Text box.*/
	int X1 = _ttoi(e->GetAttribute("X1"));
	int Y1 = _ttoi(e->GetAttribute("Y1"));
	int X2 = _ttoi(e->GetAttribute("X2"));
	int Y2 = _ttoi(e->GetAttribute("Y2"));
   Rect = CRect(X1,Y1,X2,Y2);
	TextFont = _ttoi(e->GetAttribute("TextFont"));//Storing Font of the text.	
	BoxColor = _ttoi(e->GetAttribute("BoxColor"));//Storing Fill color of text box.
	TextColor = _ttoi(e->GetAttribute("TextColor"));//storing Text color.

	if(BoxColor == 0)
       BoxColor=CChildView::Back_Color;
   if(TextFont > SmallFont)
         TextFont = Bigfont;

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

CTextBox::~CTextBox()
{
	 
}

/*************************************************************************************/
/*                                                                                   */
/*  This function Draws a CVGATextBox object When any CVGATextBox type object is	 */
/*  found in menu/submenu item list for current page .								 */
/*																					 */
/*************************************************************************************/
void CTextBox::Draw(CDC *pDC)
{ 
   CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;
	 
    SetRect(Rect);
	 DrawRect(pDC, BoxColor, rect);//Draw Text box rectangle with box color.
	 if(TextColor==0)
		TextColor=CChildView::TextColor;
	
	 /*Draw Text with Text color and Font.*/
	 DrawText(pDC, TextFont, TextColor, rect, TempText,true);
	 

}
bool CTextBox::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}