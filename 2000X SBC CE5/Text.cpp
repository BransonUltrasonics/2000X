// Text.cpp: implementation of the CText class.
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
  1.1       01/11/08    PDwivedi  Modified Constructor.   
  1.2       08/01/08    PDwivedi  Removed function.
  1.3       09/09/08    PDwivedi  Added changes for string Debug Menu.
*/

#include "stdafx.h"
#include "SBC.h"
#include "Text.h"
#include "XmlElement.h"
#include "Variable.h"
#include <WinSock.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CText::CText(CString str,int X1,int Y1,int X2,int Y2)
{
   RectShow=0;
   text=str;
   SubText=CChildView::thisPtr->CurrentLanguageName;
   SubText=SubText.SpanExcluding(_T("."));
   rect.SetRect(X1,Y1,X2,Y2);
}
CText::CText(CXmlElement * e)
{
   rect = CRect(0, 0, 0, 0);
   RectShow=0;
   textID=e->GetAttribute("textID");
   text=CVgaMenuItem ::LinearSearch(textID);
   FunName=e->GetAttribute("funname");
   if(FunName!="")
   {
      void *ptr;
      CString (*rmn)(CString);
		if(functionCall.Lookup(FunName,ptr))
		{
			rmn = (CString (*)(CString))ptr;
			SubText=rmn(SubText);
		}
   }
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

CText::~CText()
{

}
/**********************************************************************************/
/*                                                                                */
/*  This function Draws a Text object When any Text type object is                */
/*  found in menu/submenu item list for current page                              */
/**********************************************************************************/
void CText::Draw(CDC *pDC)
{
   CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;

   DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText + SubText,false);
}

bool CText::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}

CString GetIPAddress(CString str)
{
  WORD wversion;
  WSADATA wsData;
  char name[255];
  PHOSTENT hostinfo;
  wversion=MAKEWORD(1,1);
  char *ip;
  CString IPAdd;
  if(WSAStartup(wversion,&wsData)==0)
   if(gethostname(name,sizeof(name))==0)
    if((hostinfo=gethostbyname(name))!=NULL)
      {
         int count=0;
         while(hostinfo->h_addr_list[count])
         {
           ip=inet_ntoa(*(struct in_addr*)hostinfo->h_addr_list[count]);
           IPAdd=ip;
           ++count;
         }
       }
    str= " = " + IPAdd;
     return str;
}
/*
CString GetPrinterInfo(CString str)
{
   printf("\n GetPrinterInfo");
   /*CString PrinterPower_str ="Printer is   Offline";
								
   CString Printer_Online = "Printer is    Online";
								
   
   CPrintDialog dlg(false);
		if(dlg.GetDefaults())
         str=Printer_Online;
		else
		   str=PrinterPower_str;
		
	
	DeleteDC(dlg.m_pd.hdc);
	dlg.~CPrintDialog(); * /
    CString PrinterPower_str[]={
		"Printer is   Offline",
	   "Printer is    Online"
	 };
   if(CChildView::thisPtr->PrinterPresent== PRINTERONLINE)
   {
      printf("\n inside print");
      str=PrinterPower_str[PRINTERONLINE];
   }
	else
   {
		 printf("\n not inside print");
      str=PrinterPower_str[PRINTERNOTAVILABLE];
   }
   return str;
}*/