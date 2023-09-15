// VgaChoice.cpp: implementation of the CVgaChoice class.
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
  1.2       06/06/08    PDwivedi  Modified Constructors & MouseClick() for Function Execution.
  1.3       08/01/08	   PDwivedi  Added functions for printing.
  1.4       08/08/08    PDwivedi  Final Code Clean up.
  1.5       09/09/08    PDwivedi  Added changes for string Debug Menu.
  1.6       09/24/08    PDwivedi  Added changes for Sequence List Deletion.
*/

#include "stdafx.h"
#include "SBC.h"
#include "VgaChoice.h"
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
extern CChildView::PrintingSetup PrintSetup;

CVgaChoice::CVgaChoice(CXmlElement * e)
{
   rect = CRect(0, 0, 0, 0);
   RectShow=1;
   textID=e->GetAttribute("textID");
   text=CVgaMenuItem ::LinearSearch(textID);
   FunName=e->GetAttribute("FunName");
   ChoiceText1=CVgaMenuItem ::LinearSearch(e->GetAttribute("ID1"));
   ChoiceText2=CVgaMenuItem ::LinearSearch(e->GetAttribute("ID2"));
   ChoiceText="";
   submenu=e->GetAttribute("menu");
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

CVgaChoice::~CVgaChoice()
{

}
/**********************************************************************************/
/*                                                                                */
/*  This function Draws a Choice object When any Choice type object is found in   */
/*  menu/submenu item list for current page                                       */
/**********************************************************************************/
void CVgaChoice::Draw(CDC *pDC)
{
	CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;

   DrawRect(pDC, CChildView::Button_Color, rect);
	Draw_Pressed_Released_Button(pDC);
	DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
	DrawRect(pDC, CChildView::Back_Color, CRect(rect.right,
												rect.top,
												(rect.right+90),
												 rect.bottom));
	DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,
														 rect.top,
														 (rect.right+100),
														 rect.bottom), ChoiceText,false);
}

bool CVgaChoice::MouseClick(const CPoint &p, CChildView *view)
{
   int length =IntegerLength;
	unsigned char data[IntegerLength + 1];
   union 
	{
		short i;
		char c[2];
	} u;
   u.i=EnumID;
   data[1]=u.c[0];
	data[0]=u.c[1];
   union {
			int choice_value;
			char y[IntegerLength];
			} v;
   int tempvalue = Choice_value;
	if((Choice_value & 1) == 1)
   {
      Choice_value &= ~(1);
   }
   else
   {
      Choice_value |= 1;
   }
   v.choice_value=Choice_value;//object->GetRadio_Value();//getting radio value to char array.
   data[2]=(char)v.y[1];
	data[3]=(char)v.y[0];
   unsigned char * data1 = (unsigned char *) &data[0];
	CHostCommand * request = new CHostCommand(SetValue_FunID, data1, length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if (response)
	{
		char ch=CHostCommand::AckNak();
		data1 = response->GetData();
		length = response->GetDataLength();
      if(ch==ACK)
		{
        int refresh=CVgaMenuItem::Convert_Char_To_Integer(data1,length,3);
        if(refresh)
        {
           theApp.GetSystemVariable();   
        }
        Choice_value=CVgaMenuItem::Convert_Char_To_Integer(data1,length,2);
        if(FunName!="")
         {
            void *ptr;
            void (*rmn)(int);
            if(functionCall.Lookup(FunName,ptr))
		      {
			       rmn = (void (*)(int))ptr;
			       rmn(Choice_value);
            }
         }
        if(Choice_value)
			{
			  if(submenu!="")
            {
              CVgaMenu * menu;
               if (theApp.menus.Lookup(submenu, menu))
		         {
			         view->menupointers.AddTail(theApp.MenuPointer);
                  view->menusname.AddTail(theApp.menuName);
                  view->menus.AddTail(page_no);
                  page_no=1;   
			         theApp.menuName = submenu;
                  theApp.MenuPointer=menu;
		         }		
	         }
            
           ChoiceText = "=" + ChoiceText2;
			}
			else
			{
				ChoiceText = "=" + ChoiceText1;
			}
		   {
            CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
         }
         int ID=CVgaMenuItem::Convert_Char_To_Integer(data1,length,2);
         view->Invalidate ();
      }
      else
      {
          Choice_value=tempvalue;
         view->ProcessNak(data1,length,(int)this,0);
      }
      delete response;
   }
   return true;
}


void PMCScreenCheck(int Choice_value)
{
   if(Choice_value)
   {
      CChildView::thisPtr->PMCScreen=true;
      CChildView::thisPtr->PMCDisable=true;
    }
   else
   {
      CChildView::thisPtr->PMCScreen=false;
      CChildView::thisPtr->PMCDisable=!CChildView::thisPtr->PMCDisable;
   }
}

void CheckPrinterOnline(int Choice_value)
{ 
   PrintSetup.IsPrinting=Choice_value;
	if(!PrintSetup.IsPrinting)
	{
		while (CChildView::thisPtr->GraphPrintList.GetCount()>0)
		delete CChildView::thisPtr->GraphPrintList.RemoveHead();

		while(CChildView::thisPtr->GraphWeldDataPrintList.GetCount()>0)
			delete CChildView::thisPtr->GraphWeldDataPrintList.RemoveHead();

		while(CChildView::thisPtr->PrintObjectList.GetCount()>0)
			delete CChildView::thisPtr->PrintObjectList.RemoveHead();
		
      while(CChildView::thisPtr->PrintSequenceObjectList.GetCount()>0)
			delete CChildView::thisPtr->PrintSequenceObjectList.RemoveHead();

	
 		while(CChildView::thisPtr->PrintWeldHistoryList2.GetCount()>0)
			delete CChildView::thisPtr->PrintWeldHistoryList2.RemoveHead();

		while(CChildView::thisPtr->PrintGraphTextObjectList.GetCount()>0)
			delete CChildView::thisPtr->PrintGraphTextObjectList.RemoveHead();

		while(CChildView::thisPtr->TablePrintList.GetCount()>0)
			delete CChildView::thisPtr->TablePrintList.RemoveHead();

		CChildView::thisPtr->WeldAlarmStringList.RemoveAll();
		CChildView::thisPtr->WeldHistoryAlarmStringList.RemoveAll();
		CChildView::thisPtr->GraphAlarmStringList.RemoveAll();

		CChildView::thisPtr->PrintGraphIDList.RemoveAll();
		CChildView::thisPtr->PrintWeldDataIDList.RemoveAll();
 		CChildView::thisPtr->PrintInfoList.RemoveAll();
	}
  if(PrintSetup.IsPrinting)
	 {
       CPrintDialog dlg1(false);
		 dlg1.m_pd.hdc=NULL;
		 dlg1.GetDefaults();
		 if((dlg1.m_pd.hdc))
       {
          CChildView::thisPtr->PrinterPresent = PRINTERONLINE;
       }
		 else 
       {
          CChildView::thisPtr->PrinterPresent = PRINTERNOTAVILABLE;
       }
		 DeleteDC(dlg1.m_pd.hdc);
		 
		 dlg1.~CPrintDialog();
	 }
	 else
		 CChildView::thisPtr->PrinterPresent = PRINTERNOTAVILABLE;

    CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);

}