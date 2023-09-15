// Date.cpp: implementation of the CDate class.
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
  1.1       01/11/08    PDwivedi  Modified MouseClick().      
  1.2		   04/04/08	   PDwivedi  Define Strings For KeyPad.
  1.3       08/08/08    PDwivedi  Final Code Clean up.
  1.4       09/09/08    PDwivedi  Added String Debug changes.
  1.5       11/06/09    PDwivedi  Added changes for showing String number Date KeyPad.

*/

#include "stdafx.h"
#include "SBC.h"
#include "Date.h"
#include "XmlElement.h"
#include "Variable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDate::CDate(CXmlElement * e)
{
   rect = CRect(0, 0, 0, 0);
   textID=e->GetAttribute("textID");
   text=CVgaMenuItem ::LinearSearch(textID);
   RectShow=_ttoi(e->GetAttribute("RectShow"));
   CurrentStringID=e->GetAttribute("StrID1");
   CurrentString=CVgaMenuItem ::LinearSearch(CurrentStringID);
   NewStringID=e->GetAttribute("StrID2");
   NewString=CVgaMenuItem ::LinearSearch(NewStringID);
   Str_ReenterID=e->GetAttribute("ErrorString1ID");
   Str_Reenter= CVgaMenuItem ::LinearSearch(Str_ReenterID);
   StrInvalidEntryID=e->GetAttribute("ErrorString2ID");
   StrInvalidEntry= CVgaMenuItem ::LinearSearch(StrInvalidEntryID);
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

CDate::~CDate()
{

}

/**********************************************************************************/
/*                                                                                */
/*  This function Draws a Date object When any Date type object is                */
/*  found in menu/submenu item list for current page                              */
/**********************************************************************************/
void CDate::Draw(CDC *pDC)
{
   CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;

   if(RectShow)
   {
	   DrawRect(pDC, CChildView::Button_Color, rect);
	   Draw_Pressed_Released_Button(pDC);
	   DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
	   DrawRect(pDC, CChildView::Back_Color, CRect(rect.right,
									   rect.top,
									  (rect.right+100),
									   rect.bottom));
	   DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,
									   rect.top,
									  (rect.right+100),
									   rect.bottom), Date_Text,false);
   }
   else
   {
       DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,false);
       DrawRect(pDC, CChildView::Back_Color, CRect(rect.left+90,
                                   rect.top,
                                  (rect.left+90),
                                   rect.bottom));
       DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.left+90,
                                   rect.top,
                                  (rect.left+90),
                                   rect.bottom), Date_Text,false);
   }
}


/**********************************************************************************/
/*                                                                                */
/*  This function is called when any Date object is clicked by the user           */
/* If the Date is Editable then the keypad is displayed and the new Date          */
/* entered is send back to 332.													  */	
/**********************************************************************************/
bool CDate::MouseClick(const CPoint &p, CChildView *view)
{
   OnKeypadScreen_flag=true;
   unsigned char * data = (unsigned char *) &Date_Text;
   view->BuildCompleteKeypadList(GetType(),data,&Date_Text,EnumID,this);
   view->Invalidate();
   return true;
  // return false;
}

