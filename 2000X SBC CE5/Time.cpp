// Time.cpp: implementation of the CTime class.
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
  1.0       10/23/07	PDwivedi  Added Initial Version.
  1.1       01/11/08 PDwivedi  Modified MouseClick() for Multilang.  
  1.2		   01/11/08	PDwivedi  Modified MouseClick() for Multilang(Check in New file.)
  1.3		   04/04/08	PDwivedi  Define Strings For KeyPad.
  1.4       08/08/08 PDwivedi  Final Code Clean up.
  1.5       09/09/08 PDwivedi  Added changes for string Debug Menu.
  1.6       11/06/09 PDwivedi  Added changes for showing String Number.

*/

#include "stdafx.h"
#include "SBC.h"
#include "Time.h"
#include "XmlElement.h"
#include "Variable.h"
#include "VgaMenuItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVgaTime::CVgaTime(CXmlElement * e)
{
   rect = CRect(0, 0, 0, 0);
   RectShow=1;
   textID=e->GetAttribute("textID");
   text=CVgaMenuItem ::LinearSearch(textID);
   CurrentStringID=e->GetAttribute("StrID1");
   CurrentString=CVgaMenuItem ::LinearSearch(CurrentStringID);
   NewStringID = e->GetAttribute("StrID2");
   NewString= CVgaMenuItem ::LinearSearch(NewStringID);
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

CVgaTime::~CVgaTime()
{

}
/***********************************************************************************/
/*                                                                                 */
/*  This function Draws a Time object When any Time type object is                 */
/*  found in menu/submenu item list for current page                               */
/***********************************************************************************/
void CVgaTime::Draw(CDC *pDC)
{
	CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;

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
														rect.bottom), Time_Text,false);
}


/**********************************************************************************/
/*                                                                                */
/*  This function is called when any Time object is clicked by the user           */
/* If the Time is Editable then the keypad is displayed and the new Time          */
/* entered is send back to 332.													  */	
/**********************************************************************************/

bool CVgaTime::MouseClick(const CPoint &p, CChildView *view)
{
   OnKeypadScreen_flag=true;
	unsigned char * data = (unsigned char *) &Time_Text;
   view->BuildCompleteKeypadList(GetType(),data,&Time_Text,EnumID,this);
	view->Invalidate();
	return true;
   //return true;
}

