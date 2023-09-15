// RadioMenu.cpp: implementation of the CRadioMenu class.
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
  1.1       01/11/08    PDwivedi  Modified Draw() & Constructor for proper functioning. 
  1.2		   04/04/08	   PDwivedi	 Define Constant for Total RadioMenu Items.
  1.3       06/06/08    PDwivedi	 Modified CRadioMenu for format LookUp. 
  1.4       08/08/08    PDwivedi  Final Code Clean up.
  1.5       11/06/09    PDwivedi  Added changes for showing String Number.

*/

#include "stdafx.h"
#include "SBC.h"
#include "RadioMenu.h"
#include "XmlElement.h"
#include "Variable.h"
#include "VgaRadioButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CMapStringToString values;

CRadioMenu::CRadioMenu(CXmlElement * e)
{
   rect = CRect(0, 0, 0, 0);
   StrtextID=e->GetAttribute("textID");
   text=CVgaMenuItem ::LinearSearch(e->GetAttribute("textID"));
  // GetUnit_Value(this,EnumID);
   Insertunitflag=false;
   VarText="";
   RadioMenuStr.SetSize(MAXRADIOINDEX);
   RadioMenuStrID.SetSize(MAXRADIOINDEX);
	RadioIndex=0;
   RadioMenuStrID[0]=e->GetAttribute("StrID1");
   RadioMenuStr[0]= CVgaMenuItem ::LinearSearch(RadioMenuStrID[0]);

   RadioMenuStrID[1]=e->GetAttribute("StrID2");
   RadioMenuStr[1]= CVgaMenuItem ::LinearSearch(RadioMenuStrID[1]);

   RadioMenuStrID[2]=e->GetAttribute("StrID3");
   RadioMenuStr[2]= CVgaMenuItem ::LinearSearch(RadioMenuStrID[2]);

   RadioMenuStrID[3]=e->GetAttribute("StrID4");
   RadioMenuStr[3]= CVgaMenuItem ::LinearSearch(RadioMenuStrID[3]);

   RadioMenuStrID[4]=e->GetAttribute("StrID5");
   RadioMenuStr[4]= CVgaMenuItem ::LinearSearch(RadioMenuStrID[4]);

   RadioMenuStrID[5]=e->GetAttribute("StrID6");
   RadioMenuStr[5]= CVgaMenuItem ::LinearSearch(RadioMenuStrID[5]);

   RadioMenuStrID[6]=e->GetAttribute("StrID7");
   RadioMenuStr[6]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[6]);

   RadioMenuStrID[7]=e->GetAttribute("StrID8");
   RadioMenuStr[7]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[7]);

   RadioMenuStrID[8]=e->GetAttribute("StrID9");
   RadioMenuStr[8]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[8]);

   RadioMenuStrID[9]=e->GetAttribute("StrID10");
   RadioMenuStr[9]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[9]);

   RadioMenuStrID[10]=e->GetAttribute("StrID11");
   RadioMenuStr[10]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[10]);

   RadioMenuStrID[11]=e->GetAttribute("StrID12");
   RadioMenuStr[11]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[11]);

   RadioMenuStrID[12]=e->GetAttribute("StrID13");
   RadioMenuStr[12]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[12]);

   RadioMenuStrID[13]=e->GetAttribute("StrID14");
   RadioMenuStr[13]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[13]);

   RectShow=_ttoi(e->GetAttribute("Rectshow"));
   submenu = e->GetAttribute("menu");
   CString str=e->GetAttribute("format");
   CString Formatvalue;
   values.Lookup(str, Formatvalue);
   Format=_ttoi(Formatvalue);
   //Format=_ttoi((e->GetAttribute("format")));
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

CRadioMenu::~CRadioMenu()
{
   if(RadioMenuStr.GetSize()>0)
      RadioMenuStr.RemoveAll();
}
/**********************************************************************************/
/*                                                                                */
/*  This function Draws a RadioMenu object When any RadioMenu type object is	  */
/*  found in menu/submenu item list for current page.							  */
/**********************************************************************************/
void CRadioMenu::Draw(CDC *pDC)
{
   if(RectShow)
	{
		
      if((text == "")&&(StrtextID==""))
		{
			
			 if((VarText.GetAt(0)=='>')||((VarText.GetAt(0)=='=')))
					text=text;
				else
					text=VarText.SpanExcluding(_T(">="));
			 CString str=text;
			 bool Insertunitflag1=CScreenKeypad::InsertProperUnits(this, (CScreenKeypad::FORMAT)this->Format,CVgaMenu::RADIOMENU);
			 VarText=FormatString(VarText);
			 DrawRect(pDC, CChildView::Button_Color, rect);
			 Draw_Pressed_Released_Button(pDC);

          CString TempText = text;
          if(CChildView::thisPtr->StringDebugFlag)
            TempText = RadioMenuStrID[RadioIndex] + _T(" ")+ text;

			 DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
			 DrawRect(pDC, CChildView::Back_Color, CRect(rect.right,
															rect.top,
															(rect.right+100),
															rect.bottom));
			 DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,
																 rect.top,
																 (rect.right+100),
																 rect.bottom), VarText,false);
			 this->text=str;
		}
		else
		{
			 CString str=text;
			 bool Insertunitflag1=CScreenKeypad::InsertProperUnits(this, (CScreenKeypad::FORMAT)this->Format,CVgaMenu::RADIOMENU);
			 VarText=FormatString(VarText);
			 DrawRect(pDC, CChildView::Button_Color, rect);
			 Draw_Pressed_Released_Button(pDC);

          CString TempText = text;
          if(CChildView::thisPtr->StringDebugFlag)
            TempText = RadioMenuStrID[RadioIndex] + _T(" ")+ text;

			 DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
			 DrawRect(pDC, CChildView::Back_Color, CRect(rect.right,
														   rect.top,
														   (rect.right+100),
														   rect.bottom));
			 DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,
																 rect.top,
																 (rect.right+100),
																 rect.bottom), VarText,false);
			 this->text=str;
		}
	}
	else
	{
	   CString TempText = text;
      if(CChildView::thisPtr->StringDebugFlag)
         TempText = RadioMenuStrID[RadioIndex] + _T(" ")+ text;
      //bool Insertunitflag1=CScreenKeypad::InsertProperUnits(this, (CScreenKeypad::FORMAT)this->Format,CVgaMenu::RADIOMENU);
      DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText+VarText,false);
   }
}

/*************************************************************************************/
/*                                                                                   */
/*  This function is called when any RadioMenu object is clicked by the user         */
/*  The  menu items are stored and displayed as new menu.                            */
/*************************************************************************************/
bool CRadioMenu::MouseClick(const CPoint &p, CChildView *view)
{
	
   if(submenu!="")
   {
     // page_no=1;
      CVgaMenu * menu;
      if (theApp.menus.Lookup(submenu, menu))
		{
			view->menusname.AddTail(theApp.menuName);
         view->menus.AddTail(page_no);
         view->menupointers.AddTail(theApp.MenuPointer);
         SetSelectedRadioIndex(menu);
         page_no=1;
         CChildView::thisPtr->ModifyObjectList(menu);
         theApp.menuName = submenu;
         theApp.MenuPointer=menu;
		}		
	}
   view->Invalidate();
   return true;
}


CString CRadioMenu::FormatString(CString text)
{
   int t=0;
   int noofchar=0;
   CString str=_T("");
   for(int b=0;b<text.GetLength();b++)
   {
      if(text.GetAt (b)== '>'|| text.GetAt(b) == '=')
      {
         t=b;
         noofchar=(text.GetLength())-t;
      }
   }
   if(noofchar>0)
   {
      return (text.Right (noofchar));
   }
   else
   {
      return str;
   }
}

/*************************************************************************************/
/*                                                                                   */
/*  This function is called when any RadioMenu object is clicked by the user         */
/*  & it selects currently  Radio Item.                                          */
/*************************************************************************************/
void CRadioMenu::SetSelectedRadioIndex(CVgaMenu * CurrMenuLst)
{ 
   if(CurrMenuLst !=NULL)
	{
      if(CurrMenuLst->items.GetCount()>0)
		{
			POSITION pos = CurrMenuLst->items.GetHeadPosition();
			CVgaMenuItem * object = CurrMenuLst->items.GetHead();
			while(pos)
			{
				if(object->GetType()==CVgaMenu::RADIO_BUTTON)
				{
				   CVgaRadioButton *ptr=(CVgaRadioButton *)object;
				   ptr->EnumID=EnumID;
				   if(RadioIndex==ptr->GetRadioValue())
				   {
					  ptr->Selected = true;
				   }
				   else
				   {
					  ptr->Selected =false;
				   }
				}
				object=CurrMenuLst->items.GetNext(pos);
			}
		}
	}
}
 
