// VgaSubMenu.cpp: implementation of the CVgaSubMenu class.
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
  1.1       01/11/08    PDwivedi  Added Changes for Password Check.
  1.2       04/04/08	   PDwivedi	 Modify MouseClick().
  1.3       06/06/08    PDwivedi  Modified MouseClick() for preparing MenuPointerList.
  1.4       08/08/08    PDwivedi  Final Code Clean up.
  1.5       09/09/08    PDwivedi  Added changes for string Debug Menu.
*/

#include "stdafx.h"
#include "SBC.h"
//#include "GUIDoc.h"
#include "VgaSubMenu.h"
#include "XmlElement.h"
#include "Variable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVgaSubMenu::CVgaSubMenu(CXmlElement * e)
{
	rect = CRect(0, 0, 0, 0);
	RectShow=1;
   textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	submenu = e->GetAttribute("menu");
	menuNak = e->GetAttribute("menunak");
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

CVgaSubMenu::~CVgaSubMenu()
{
}

void CVgaSubMenu::Draw(CDC *pDC) 
{
   CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;

   int ButtonColour=CChildView::Button_Color;
	DrawRect(pDC, ButtonColour, rect);
	Draw_Pressed_Released_Button(pDC);
   CVgaMenuItem::DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
}

bool CVgaSubMenu::MouseClick(const CPoint &p, CChildView *view)
{
// printf("\n AccessLevel=%d",this->AccessLevel);
// printf("\n CChildView::Securitylevel=%d",CChildView::AccessLevelSystem);
   if(submenu!="")
   {
      if((this->AccessLevel > CChildView::AccessLevelSystem)&&(CChildView::PasswordFlag))
      {
         unsigned char *s=0;
         view->menusname.AddTail(theApp.menuName);
         view->menus.AddTail(page_no);
         view->menupointers.AddTail(theApp.MenuPointer);
   //    printf("\n this->AccessLevel > CChildView::AccessLevelSystem");
         OnKeypadScreen_flag=true;
		   view->BuildCompleteKeypadList(VGA_PASSWORD,s,0,PasswordCommand,this);
         view->Invalidate();
         //theApp.menuName = submenu;
      }
      else 
      {
         CVgaMenu * menu;
         if (theApp.menus.Lookup(submenu, menu))
		   {
			   view->menusname.AddTail(theApp.menuName);
            view->menus.AddTail(page_no);
            view->menupointers.AddTail(theApp.MenuPointer);
            page_no=1;
            CChildView::thisPtr->ModifyObjectList(menu);   
            theApp.menuName = submenu;
            theApp.MenuPointer=menu;
            
		   }
         view->Invalidate();
	   }
   }
   
   return true;
}