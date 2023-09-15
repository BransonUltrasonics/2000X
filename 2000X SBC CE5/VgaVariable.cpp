// VgaVariable.cpp: implementation of the CVgaVariable class.
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
  1.1       01/11/08    PDwivedi  Modified Constructors & MouseClick(). 
  1.2		   04/04/08	   PDwivedi	 Added Constants.
  1.3       06/06/08    PDwivedi  Modified Constructor for Format LookUp.
  1.4       08/01/08	   PDwivedi  Modified Constructor for fuction call.
  1.5       08/08/08    PDwivedi  Final Code Clean up.
  1.6       09/09/08    PDwivedi  Added changes for string Debug Menu.
  1.7       11/06/09    PDwivedi  Added changes for showing String Number.

*/

#include "stdafx.h"
#include "SBC.h"
#include "VgaVariable.h"
#include "XmlElement.h"
#include "Variable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define PrintSelect_Rect CRect(516,2,636,38)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CMapStringToString values;

CVgaVariable::CVgaVariable(CXmlElement * e)
{
   rect = CRect(0, 0, 0, 0);
   textID=e->GetAttribute("textID");
   text=CVgaMenuItem ::LinearSearch(textID);
   Keypad_title=e->GetAttribute("Keypad_title");
   CurrentStringID=e->GetAttribute("StrID1");
   CurrentString=CVgaMenuItem ::LinearSearch(CurrentStringID);
   NewStringID= e->GetAttribute("StrID2");
   NewString=CVgaMenuItem ::LinearSearch(NewStringID);
   CString str=e->GetAttribute("format");
   CString Formatvalue;
   values.Lookup(str, Formatvalue);
   Format=_ttoi(Formatvalue);
   Digits=_ttoi((e->GetAttribute("Digits")));
   Bitmask=_ttoi((e->GetAttribute("Bitmask")));
   ID=_ttoi((e->GetAttribute("ID")));
   Disable=_ttoi((e->GetAttribute("Disable")));
   RectShow=_ttoi((e->GetAttribute("Rectshow")));
   TextType=_ttoi((e->GetAttribute("TextType")));
   Unitshow=_ttoi((e->GetAttribute("Unitshow")));
   FunName=e->GetAttribute("funname");
   POSITION pos = e->children.GetHeadPosition();
   Variable_Text="";
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

CVgaVariable::~CVgaVariable()
{

}

/**********************************************************************************/
/*                                                                                */
/*  This function Draws a Variable object When any Variable type object is        */
/*  found in menu/submenu item list for current page                              */
/**********************************************************************************/

void CVgaVariable::Draw(CDC *pDC)
{
   CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;

	CString TempStr="";
	if(RectShow)
	{
	   if(CChildView::thisPtr->RunResultScreen)
       SetRect(PrintSelect_Rect);
	   
      DrawRect(pDC, CChildView::Button_Color, rect);
	   Draw_Pressed_Released_Button(pDC);
      CString str=TempText;
      TempText=TempText.SpanExcluding(_T("("));
	   DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
	   DrawRect(pDC,CChildView::Back_Color, CRect(rect.right,rect.top,
												   (rect.right+100),rect.bottom));
	   
	   DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,rect.top,
															(rect.right+100),rect.bottom),
															Variable_Text,false);
      TempText=str;
	}
	else
	{
		TempStr =TempText+Variable_Text;
		DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempStr,false);

	}
}

/*************************************************************************************/
/*                                                                                   */
/*  This function is called when any Variable object is clicked by the user          */
/* This funtion sends a host command to get the Variable information          .      */
/* If NAK is obtained as the response then the funstion justs BEEPS indicating a NAK */
/* If an ACK is obtained then the keypad is displayed								 */	
/*************************************************************************************/

bool CVgaVariable::MouseClick(const CPoint &p, CChildView *view)
{
	OnKeypadScreen_flag=true;
   int length =VARMAXMINLENGTH;
	unsigned char data1[VARMAXMINLENGTH];
	union 
		   {
			   short i;
			   char c[VARMAXMINLENGTH];
		   } u;
		 u.i=EnumID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
   CHostCommand * request = new CHostCommand(GetVariableData_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	
	if(response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
      if(ch==ACK)
		{
         this->MinVal =CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
         this->MaxVal =CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
         unsigned char * data = (unsigned char *) &Variable_Text;
         view->BuildCompleteKeypadList(GetType(),data,&Variable_Text,EnumID,this);
	      view->Invalidate();
		}
      else if(ch==NAK)
		{
		   view->ProcessNak(data,length,0,0);
         view->Invalidate();
		}
      delete response;
   }
	return true;
}

