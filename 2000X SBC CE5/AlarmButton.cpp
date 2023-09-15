// AlarmButton.cpp: implementation of the CAlarmButton class.
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
  1.1       08/08/08	   PDwivedi  Final Code Clean up.
  1.2       09/09/08	   PDwivedi  Added Changes for String Debug.
*/

#include "stdafx.h"
#include "SBC.h"
#include "AlarmButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlarmButton::CAlarmButton(CXmlElement * e)
{
   textID=e->GetAttribute("textID");
   text=CVgaMenuItem ::LinearSearch(textID);
   Text1=CVgaMenuItem ::LinearSearch(e->GetAttribute("textID1"));;
	Text2=CVgaMenuItem ::LinearSearch(e->GetAttribute("textID2"));;
	/*Storing Co-Ordinates of Text box.*/
	int X1 = _ttoi(e->GetAttribute("X1"));
	int Y1 = _ttoi(e->GetAttribute("Y1"));
	int X2 = _ttoi(e->GetAttribute("X2"));
	int Y2 = _ttoi(e->GetAttribute("Y2"));
   Rect = CRect(X1,Y1,X2,Y2);
	MenuName= e->GetAttribute("menuname");
	TextColor = _ttoi(e->GetAttribute("TextColor"));//storing Text color.
   BoxColor = _ttoi(e->GetAttribute("BoxColor"));//Storing Fill color of text box.
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

CAlarmButton::~CAlarmButton()
{

}

/*************************************************************************************/
/*                                                                                   */
/*  This function Draws a CVGATextBox object When any CVGATextBox type object is	 */
/*  found in menu/submenu item list for current page .								 */
/*																					 */
/*************************************************************************************/
void CAlarmButton::Draw(CDC *pDC)
{
	
   CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ") + text;
   
   SetRect(Rect);
    if(BoxColor == 0)
       BoxColor=CChildView::Back_Color;

	 DrawRect(pDC, BoxColor, rect); //Draw Alarm Button.
    Draw_Pressed_Released_Button(pDC);
	 if(TextColor==0)
		TextColor=CChildView::TextColor;
	
	 /*Draw Text with Text color and Font.*/
    DrawText(pDC, SmallFont, TextColor, rect, TempText,true);
}

bool CAlarmButton::MouseClick(const CPoint &p, CChildView *view)
{
	CVgaMenu * menu;
   if (theApp.menus.Lookup(MenuName, menu))
	{
		view->menusname.AddTail(theApp.menuName);
      view->menus.AddTail(page_no);
      view->menupointers.AddTail(theApp.MenuPointer);
      page_no=1;
      theApp.menuName = MenuName;
      theApp.MenuPointer=menu;
      CChildView::thisPtr->ModifyObjectList(menu);   
   }
   view->Invalidate();
   return true;
}