// VgaAlphanumeric.cpp: implementation of the CVgaAlphanumeric class.
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
  1.1		   04/04/08	PDwivedi  Added Member Variable.	
  1.2       08/08/08 PDwivedi  Final Code Clean up.
  1.3       08/26/08	PDwivedi  Added function name to class.
  1.4       09/09/08 PDwivedi  Added changes for string Debug Menu.
*/
#include "stdafx.h"
#include "SBC.h"
#include "VgaAlphanumeric.h"
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

CVgaAlphanumeric::CVgaAlphanumeric(CXmlElement * e)
{
   rect = CRect(0, 0, 0, 0);
   RectShow=1;
   textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
   Alpha_Text="";
   TitleKeyPad=CVgaMenuItem ::LinearSearch(e->GetAttribute("TitleID"));
   CurrentString=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID1"));
   NewString=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID2"));
   CharAllowed=_ttoi(e->GetAttribute("Charallowed"));
   CharHidden=_ttoi(e->GetAttribute("Charhidden"));
   MenuNak=e->GetAttribute("menunak");
   MenuAck=e->GetAttribute("menuack");
   ShowValue=_ttoi(e->GetAttribute("ShowValue"));
   FunName=e->GetAttribute("funname");
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

CVgaAlphanumeric::~CVgaAlphanumeric()
{

}

/*************************************************************************************/
/*                                                                                   */
/*  This function Draws a Alphanumeric object When any Alphanumeric type object is   */
/*  found in menu/submenu item list for current page                                 */
/*************************************************************************************/
void CVgaAlphanumeric::Draw(CDC *pDC)
{
   CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;

	DrawRect(pDC,CChildView::Button_Color, rect);
	Draw_Pressed_Released_Button(pDC);
	DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
	DrawRect(pDC, CChildView::Back_Color, CRect(rect.right,
												rect.top,
												(rect.right+100),
												rect.bottom));
   if(ShowValue)
	   DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,
														 rect.top,
														 (rect.right+100),
														  rect.bottom), Alpha_Text,false);
}

/*************************************************************************************/
/*                                                                                   */
/*  This function is called when any Alphanumeric object is clicked by the user      */
/* This funtion sends a host command to get the Alpha string information          .  */
/* If NAK is obtained as the response then the funstion justs BEEPS indicating a NAK */
/* If an ACK is obtained then the keypad is displayed and the new alpha string       */
/* entered is send back to 332.														 */	
/*************************************************************************************/

bool CVgaAlphanumeric::MouseClick(const CPoint &p, CChildView *view)
{
	OnKeypadScreen_flag=true;
   unsigned char * data = (unsigned char *) &Alpha_Text;
   view->BuildCompleteKeypadList(GetType(),data,&Alpha_Text,EnumID,this);
	view->Invalidate();
	return true;
}

