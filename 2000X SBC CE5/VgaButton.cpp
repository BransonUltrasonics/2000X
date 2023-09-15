// VgaButton.cpp: implementation of the CVgaButton class.
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
  1.1       01/11/08    PDwivedi  Modified Constructors,MouseClick()  .
  1.2       04/04/08	   PDwivedi	 Modified Constructors,MouseClick(), Added new Functions.
  1.3       04/14/08	   PDwivedi	 Modified Constructors,MouseClick(), Added new Functions for Multi langSupport.
  1.4       04/16/08    PDwivedi  Modified Function for Horn down flag enabled.
  1.5       06/06/08    PDwivedi  Modified MouseClick() for preparing new pointer list & added new function.
  1.6       06/12/08    PDwivedi  Modifiy MouseClick() for Calling  & changing argument function.
  1.7       08/01/08    PDwivedi  Added Functions for printing & USB.
  1.8       08/04/08    PDwivedi  Modifiy HighLightColor & DefaultColor function for ColorSetup screen.
  1.9       08/08/08    PDwivedi  Final Code Clean up.
  1.10      08/26/08	   PDwivedi  Modified SetUpPrintNow() & PrintDUPSSetup for Issues.
  1.11      09/02/08    PDwivedi  Modify SendHornDown,ProcessHornSignature for BottomHalfScreen.
  1.12      09/09/08    PDwivedi  Added changes for string Debug Menu & tracker issues.
  1.13      09/12/08    PDwivedi  Added changes for Tracker issues of round 2 testing for version LangTestJ.
  1.15      09/18/08    PDwivedi  Added changes for tracker issue(Horn Scan).
  1.16      09/24/08    PDwivedi  Added changes for Sequence & Setup PrintNow.
  1.17      09/22/09    PDwivedi  Modify SetGraphObjectMember() for Graph Screen bug.
  1.18      11/06/09    PDwivedi  Added changes for showing Preset Number in USBMemory OverWritePreset Screen..
  1.19      11/18/09    PDwivedi  Added changes for updating AlarmUpdateRequired flag
                                  & Round2 Version 11.10 testing.
  1.20      10/13/10    PDwivedi  Modified to add ProcessSoftwareMismatchError function.
  1.21      12/09/10    PDwivedi  Added changes for Standard Micro Act Recal Issue.
  1.22      12/28/10    PDwivedi  Added changes for Windows popup alarm. 
*/

#include "stdafx.h"
#include "SBC.h"
#include "VgaButton.h"
#include "XmlElement.h"
#include "Variable.h"
#include "VgaRadioButton.h"
#include "HostCommand.h"
#include "Application.h"
#include "VgaScreenSetup.h"
#include "ListBox.h"
#include "WeldingHistory.h"
#include "MsgScreen.h"
#include "BottomHalf.h"
#include "LocalChoice.h"
#include "Table.h"
#include "Toggle.h"
#include "VgaBottomMenu.h"
#include "USBFolder.h"
#include "HistoryGraphs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void GetRadioInfo(unsigned char *&data);
extern CChildView::PrintingSetup PrintSetup;
POSITION RunScreenTemp_pos,HistoryTemp_pos,GraphsTemp_pos,WeldTemp_pos,HornScanTemp_pos,ScanGraphsDataTemp_pos,ScreenGraphsTemp_pos,SetupTemp_pos,DUPSTemp_pos,SequenceTemp_pos;
extern CList<CString,CString> tempGraphsList;
extern CList<CString,CString> tempHistoryList;
extern CList<CString,CString> tempWeldList;
extern CList<CString,CString> tempHornScanList;
extern CList<CString,CString> tempScanGraphDataList;
extern CList<CString,CString> tempScreenGraphsList;
extern CList<CString,CString> tempSetupList;
extern CList<CString,CString> tempDUPSList;
extern CList<CString,CString> tempSequenceList;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVgaButton::CVgaButton(CString str,int X1,int Y1,int X2,int Y2,CString Fun)
{
   text=str;
   RectShow=1;
   Rect=CRect(X1,Y1,X2,Y2);
	SetRect(Rect);
   FunName=Fun;
   MenuName="";
   argument="";
   ObjectPageNum=PAGEALL;
   ArrowType=false;
   ArrowTypeDown=false;
   ScreenArrowUp=false;
   ScreenArrowDown=false;
   LeftArrow=false;
   RightArrow=false;
}

CVgaButton::CVgaButton(CXmlElement * e)
{
   textID=e->GetAttribute("textID");
   text=CVgaMenuItem ::LinearSearch(textID);
    /*Storing Co-ordinates*/
	int X1 = _ttoi(e->GetAttribute("X1"));
	int Y1 = _ttoi(e->GetAttribute("Y1"));
	int X2 = _ttoi(e->GetAttribute("X2"));
	int Y2 = _ttoi(e->GetAttribute("Y2"));
   ArrowType= _ttoi(e->GetAttribute("ArrowType"));
   ArrowTypeDown=_ttoi(e->GetAttribute("ArrowTypeDown"));
   ScreenArrowUp=_ttoi(e->GetAttribute("ScreenArrowUp"));
   ScreenArrowDown=_ttoi(e->GetAttribute("ScreenArrowDown"));
   LeftArrow=_ttoi(e->GetAttribute("LeftArrowType"));;
   RightArrow=_ttoi(e->GetAttribute("RightArrowType"));;
	FunName=e->GetAttribute("funname");
   argument=e->GetAttribute("argumentname");
   MenuName=e->GetAttribute("menuname");
   MenuNak=e->GetAttribute("menunak");
   RectShow=_ttoi(e->GetAttribute("Rectshow"));
	Rect=CRect(X1,Y1,X2,Y2);
	SetRect(Rect);
   ObjectPageNum=PAGEALL;
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

CVgaButton::~CVgaButton()
{

}

void CVgaButton::Draw(CDC *pDC)
{
   CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;

   if(RectShow)
   {
      DrawRect(pDC, CChildView::Button_Color, rect);
      Draw_Pressed_Released_Button(pDC);
      if(ArrowType)
      {
         DrawArrow(CPoint(rect.TopLeft( ).x+17,rect.TopLeft( ).y+34), CPoint(rect.TopLeft( ).x+27,rect.TopLeft( ).y+16),CPoint(rect.TopLeft( ).x+38,rect.TopLeft( ).y+34) ,pDC);
      }
      else if(ArrowTypeDown)
      {
		   DrawArrow(CPoint(rect.TopLeft( ).x+17,rect.TopLeft( ).y+16), CPoint(rect.TopLeft( ).x+27,rect.TopLeft( ).y+34),CPoint(rect.TopLeft( ).x+38,rect.TopLeft( ).y+16) ,pDC);
      }
	   else if(ScreenArrowUp)
	   {
		   DrawArrow(CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+29), CPoint(rect.TopLeft( ).x+25,rect.TopLeft( ).y+11),CPoint(rect.TopLeft( ).x+36,rect.TopLeft( ).y+29) ,pDC);
		   DrawArrow(CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+39), CPoint(rect.TopLeft( ).x+25,rect.TopLeft( ).y+21),CPoint(rect.TopLeft( ).x+36,rect.TopLeft( ).y+39) ,pDC);
	   }
	   else if(ScreenArrowDown)
	   {
		   DrawArrow(CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+11), CPoint(rect.TopLeft( ).x+25,rect.TopLeft( ).y+29),CPoint(rect.TopLeft( ).x+36,rect.TopLeft( ).y+11) ,pDC);
		   DrawArrow(CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+21), CPoint(rect.TopLeft( ).x+25,rect.TopLeft( ).y+39),CPoint(rect.TopLeft( ).x+36,rect.TopLeft( ).y+21) ,pDC);
	   }
      else if(LeftArrow)
      {
        DrawArrow(CPoint(rect.TopLeft( ).x+35,rect.TopLeft( ).y+16), CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+25),CPoint(rect.TopLeft( ).x+35,rect.TopLeft( ).y+34) ,pDC);
      }
      else if(RightArrow)
      {
         DrawArrow(CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+16), CPoint(rect.TopLeft( ).x+35,rect.TopLeft( ).y+25),CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+34) ,pDC);
      }
      else
      {
	     DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
      }
   }
	else
   {
	   DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText+SubText,false);
   }
}

void CVgaButton::DrawArrow(CPoint Start, CPoint Middle, CPoint End,CDC *pDC)
{
		CPen *oldPen;
		CPen NewPen;
		NewPen.CreatePen(PS_SOLID,2,CChildView::Color_Array[CChildView::TextColor]);
		oldPen = pDC->SelectObject(&NewPen);
		pDC->MoveTo(Start.x+XOFFSET,Start.y+XOFFSET);
		pDC->LineTo(Middle.x+XOFFSET,Middle.y+XOFFSET);
		pDC->LineTo(End.x+XOFFSET,End.y+XOFFSET);
		pDC->MoveTo(End.x-1+XOFFSET,End.y+XOFFSET);
		pDC->LineTo(Middle.x+XOFFSET, Middle.y-1+XOFFSET);
		pDC->LineTo(Start.x+1+XOFFSET,Start.y+XOFFSET);
		pDC->SelectObject(oldPen);
		NewPen.DeleteObject();
}
/*************************************************************************************/
/*                                                                                   */
/*  This function is called when any VGAbutton object is clicked by the user            */
/* This funtion sends a host command to get the new toggled string and displays it.  */
/* If NAK is obtained as the response then the funstion justs BEEPS indicating a NAK */
/*************************************************************************************/

bool CVgaButton::MouseClick(const CPoint &p, CChildView *view)
{
   CVgaMenu * menu;
   if(MenuName!="")
   {
      if (theApp.menus.Lookup(MenuName, menu))
		{
			view->menupointers.AddTail(theApp.MenuPointer);
         view->menusname.AddTail(theApp.menuName);
         view->menus.AddTail(page_no);
         page_no=1;
         theApp.menuName = MenuName;
         theApp.MenuPointer=menu;
         CChildView::thisPtr->ModifyObjectList(menu);
      }		
	}
   if(FunName!="")
   {
      if(argument!="")
      {
         void *ptr;
         void (*rmn)(int);
         if(functionCall.Lookup(FunName,ptr))
		   {
			    rmn = (void (*)(int))ptr;
			    rmn(EnumID);
         }
      }
      else
      {
         void *ptr;
         void (*rmn)(int);
         if(functionCall.Lookup(FunName,ptr))
		   {
			   rmn = (void (*)(int))ptr;
            int Address=(int)this;
			   rmn(Address);
         }
      }
	}
   else 
   {
      if(MenuName!="")
      {
         view->Invalidate();
         return true;
      }
      theApp.menuName=view->menusname.RemoveTail();
      page_no=view->menus.RemoveTail();
      theApp.MenuPointer=view->menupointers.RemoveTail();
		{
			CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
		}
      view->Invalidate();
   }
   return true;
}

void ExitSystemProgram(int Address)
{
   theApp.ExitInstance();
   exit(1);
}


void ExitWindowProgram(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   int length =VARMAXMINLENGTH;
	unsigned char data1[2];
	union 
			{
				short i;
				char c[2];
			} u;
	u.i=ptr->EnumID;
	data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
	//Send Command if enable flag is true
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
	   if(ch == theApp.ACK)
		{
         theApp.ExitInstance();
         exit(1);
      }
      else
      {
         CChildView::thisPtr->ProcessNak(data,length,(int)ptr,0);
      }
      delete response;
      CChildView::thisPtr->Invalidate();
   }
   
}

/*****************************************************************************/
/*	 Function called from MouseClick function for Save Button to save		 */
/*	 selected radio or large radio button informationand and then go to 	 */
/*	 previous submenu screen.												 */
/*****************************************************************************/

void HandleVGASaveButton(int Address)
{
	//Here Host command to set the information will be send to 332.
	unsigned char *data= new unsigned char[IntegerLength+1];
   GetRadioInfo(data);//Getting the information about Currently selected button.
   int length=IntegerLength;
   CHostCommand * request = new CHostCommand(SetValue_FunID, data, length);
	CHostCommand * response = app->SendUiHostCommand(request);//Sending Host Command.
	if (response)
	{ 
		char ch=CHostCommand::AckNak();
		length = response->GetDataLength();//Getting Length.
		data = response->GetData();//Getting Data.
      if(ch == theApp.ACK)
		{
			if(length!=0)
			{
			   int Refresh=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
            if(Refresh)
            {
               theApp.GetSystemVariable();
            }
            int value=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
            int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
            theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
            page_no=CChildView::thisPtr->menus.RemoveTail();
            theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		      {
			      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			   }
         }
			CChildView::thisPtr->Invalidate();
		}
		else if(ch==theApp.NAK)
      {
        CChildView::thisPtr->ProcessNak(data,length,0,0);
      }
		delete response;
	}
	else
		ERRORBEEP;
}

void SendCommandForSave(int ID)
{
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   unsigned char *data= new unsigned char[IntegerLength+1];
   GetRadioInfo(data);//Getting the information about Currently selected button.
   union 
		   {
			   short i;
			   char c[2];
		   } u;
   
   u.i= ID;
   data[1]=u.c[0];
   data[0]=u.c[1];
   int length=IntegerLength;
   CHostCommand * request = new CHostCommand(SetValue_FunID, data, length);
	CHostCommand * response = app->SendUiHostCommand(request);//Sending Host Command.
	if (response)
	{ 
		char ch=CHostCommand::AckNak();
	   length = response->GetDataLength();//Getting Length.
		data = response->GetData();//Getting Data.
      if(ch == theApp.ACK)
		{
			if(length!=0)
			{
			   int value=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
            int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
            theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
            page_no=CChildView::thisPtr->menus.RemoveTail();
            theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		      {
			      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			   }
         }
			CChildView::thisPtr->Invalidate();
		}
      else if(ch==theApp.NAK)
      {
        CChildView::thisPtr->ProcessNak(data,length,0,0);
      }
		delete response;
	}
	else
		ERRORBEEP;

}

/*****************************************************************************/
/*	 Function called from MouseClick function for Save Button				 */
/*	 to get currently selected radio or large radio button information.		 */
/*****************************************************************************/
void GetRadioInfo(unsigned char *&data)
{
	CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
	CVgaMenuItem * object =0;
   int count=0;
	POSITION pos = menu1->items.GetHeadPosition();
	while (pos)
	{
		object= menu1->items.GetNext(pos);
		if((object->GetType())==(CVgaMenu::RADIO_BUTTON)
			||(object->GetType())==(CVgaMenu::RADIOLARGE))
		{
			count++;
			if(object->GetSelectedRadio())
			{
            union 
		            {
			            short i;
			            char c[2];
		            } u;
            CVgaRadioButton *ptr=(CVgaRadioButton *)object;
		      u.i= ptr->EnumID;
            data[1]=u.c[0];
				data[0]=u.c[1];
            union {
						int Radio_value;
						char y[IntegerLength];
						} v;
				v.Radio_value=ptr->value;//object->GetRadio_Value();//getting radio value to char array.
            data[2]=(char)v.y[1];
				data[3]=(char)v.y[0];
				break;
			}
		}
	}
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 on Message Screen OK Button .               */
/**********************************************************************************/
void SendCommandForVGAButtons(int ID)
{
	int length =2;
   unsigned char data1[2];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i=ID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
  
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
      if(ch==theApp.ACK)
		{
			int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);		
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		   {
			   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			}
      }
      delete response;
   }
	CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  Save,Recall,delete      */
/*  preset No.                                                                    */
/**********************************************************************************/

void SendCommandForVGAButtonsPreset(int Address)
{
	CVgaButton *ptr=(CVgaButton *)Address;
   int Temp = CChildView::CurrentPresetNum;
   if((CListBoxObject::CurrentPresetName.GetLength()<=1))
	{ 
		CChildView::ErrorBeep();
		return;
	}
   int length =IntegerLength;
   unsigned char data1[5];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i=ptr->EnumID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
   union {
			int value;
			char y[IntegerLength];
			} v;
	
   v.value=CChildView::CurrentPresetNum;//object->GetRadio_Value();//getting radio value to char array.
   data1[2]=(char)v.y[1];
	data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];
   
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
      data = response->GetData();
		length = response->GetDataLength();
      if(ch==theApp.ACK)
		{
         int Refresh=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
         if(Refresh)
         {
            theApp.GetSystemVariable();
            CChildView::thisPtr->MaxPreset=1;
            CChildView::thisPtr->SendCommandForQualityWindow(CChildView::MaxPreset);
         }
         int value=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         page_no=1;
		   {
            CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			}
      }
      else if(ch==theApp.NAK)
      {
         CChildView::thisPtr->ProcessNak(data,length,(int)ptr,0);
      }
      delete response;
   }
   
	CChildView::CurrentPresetNum =Temp;
   CChildView::thisPtr->Invalidate();
}

void SendCommandForRecallPreset(int Address)
{
	CVgaButton *ptr=(CVgaButton *)Address;
   int Temp = CChildView::CurrentPresetNum;
   if((CListBoxObject::CurrentPresetName.GetLength()<=1))
	{ 
		CChildView::ErrorBeep();
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->Invalidate();
		return;
	}
   int length =IntegerLength;
   unsigned char data1[5];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i=ptr->EnumID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
   union {
			int value;
			char y[IntegerLength];
			} v;
	
   v.value=CChildView::CurrentPresetNum;//object->GetRadio_Value();//getting radio value to char array.
   data1[2]=(char)v.y[1];
	data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];
   
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
      char ch=CHostCommand::AckNak();
      data = response->GetData();
		length = response->GetDataLength();
      if(ch==theApp.ACK)
		{
		   int Refresh=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
         if(Refresh)
         {
            theApp.GetSystemVariable();
            CChildView::thisPtr->MaxPreset=1;
            CChildView::thisPtr->SendCommandForQualityWindow(CChildView::MaxPreset);
         }
         int value=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         page_no=1;
		   {
			   CChildView::thisPtr->RunResultScreen=true;
            CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			}
      }
      else if(ch==theApp.NAK)
      {
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ProcessNak(data,length,(int)ptr,0);
         CChildView::thisPtr->Invalidate();
      }
      delete response;
   }
   
	CChildView::CurrentPresetNum =Temp;
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  verifying current       */
/*  preset No.                                                                    */
/**********************************************************************************/

void SendCommandForVerifyPreset(int ID)
{
	int Temp = CChildView::CurrentPresetNum;
	CVgaMenu * menu;
   if((CListBoxObject::CurrentPresetName.GetLength()<=1))
	{ 
		CChildView::ErrorBeep();
		theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		return;
	}
   int length =IntegerLength;
   unsigned char data1[5];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
   u.i=ID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
   union {
			int value;
			char y[IntegerLength];
			} v;

   v.value=CChildView::CurrentPresetNum;//object->GetRadio_Value();//getting radio value to char array.
   data1[2]=(char)v.y[1];
	data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];
   
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
      data = response->GetData();
		length = response->GetDataLength();
      if(ch==theApp.ACK)
		{
		   int Refresh=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
         {
            theApp.GetSystemVariable();
         }
         int value=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         int ResponseType = CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
       menu=theApp.MenuPointer;
		 CVgaMenuItem *object;
    
	    POSITION pos1=menu->items.GetHeadPosition();
	    while (pos1)
       {
		     object= menu->items.GetNext(pos1);
		     if(object->GetType()==CVgaMenu::VGAMsgScrnObject)
		     {
			     CMsgScreen *ptr=(CMsgScreen *)object;
			     if(ResponseType==ptr->ResponseType)
			     {
				     object->IsDraw=true;
				  }
			     else
			     {
				     object->IsDraw=false;	
			     }
		     }
		}	
      CChildView::CurrentPresetNum =Temp;
		CChildView::thisPtr->Invalidate();
		}
      delete response;
   }
}

void SendCommandForVGAButtonsSavePreset(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   int length =IntegerLength;
   unsigned char data1[5];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i= ptr->EnumID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
   union {
			int value;
			char y[IntegerLength];
			} v;
	
   v.value=CChildView::CurrentPresetNum;//object->GetRadio_Value();//getting radio value to char array.
   data1[2]=(char)v.y[1];
	data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];
   
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
      data = response->GetData();
		length = response->GetDataLength();
      if(ch==theApp.ACK)
		{
			int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         page_no=1;
         CChildView::thisPtr->SaveVQSData();
		   {
			   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			}
      }
      else if(ch==theApp.NAK)
      {
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ProcessNak(data,length,(int)ptr,0);
      }
      delete response;
   }
   
	CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  displaying Screen       */
/*  Setup Menu.                                                                   */
/**********************************************************************************/

void BuildLocalScreenSetupMenu(int Address)
{
	CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
   bool ShowScreenSetup =true;
	CHostCommand * request = new CHostCommand(GetWeldingStatus,0,0);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		unsigned char *data = response->GetData();
		int length = response->GetDataLength();
		if(ch==theApp.NAK)
		{
				ShowScreenSetup=false;
		}
		delete response;
	}		
  	if(!ShowScreenSetup)
	{
		theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
		page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		return;
	}
   CChildView::ScreenSetupFlag=true;
	CChildView::thisPtr->mutex.Lock();
   CVgaMenuItem * object =0;
	object = new CVgaScreenSetup();
   object->SetType(CVgaMenu::BottomMenu_Id);
   object->IsDraw=true;
	menu1->items.AddTail(object);
   POSITION pos = menu1->items.GetHeadPosition();
	object = menu1->items.GetHead();
	while(pos)
	{
      if(object->GetType()== CVgaMenu::BottomMenu_Id)			
      {
         object->IsDraw =false;
         object->RectShow=false;
      }
      object=menu1->items.GetNext(pos);
	}
	CChildView::thisPtr->Total_Objects=3;
	page_no=1;
   CChildView::thisPtr->RecalculateMenuItemsLayout(MAXSCRNButton_Height,menu1);
	CChildView::thisPtr->mutex.Unlock();
   CChildView::thisPtr->Invalidate();
}

void ExitColorMenu(int Address)
{
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();;
   CVgaMenu * menu;
   page_no=1;
	{
		menu=theApp.MenuPointer;
      POSITION pos = menu->items.GetHeadPosition();
	   CVgaMenuItem *object = menu->items.GetHead();
	   while(pos)
	   {
         if(object->GetType()== CVgaMenu::BottomMenu_Id)			
         {
            object->IsDraw =false;
            object->RectShow=false;
         }
         object=menu->items.GetNext(pos);
	   }
    }
	CChildView::thisPtr->ScreenSetupFlag=true;
   CChildView::thisPtr->Invalidate();
}

void ButtonColor(int Address)
{
   CChildView::thisPtr->Button_Color++;
	if(CChildView::thisPtr->Button_Color>11)
		CChildView::thisPtr->Button_Color=1;
	/* checking if button color is the same as backgroung color or text color
	, if found then it is incremented */
	while((CChildView::thisPtr->Button_Color== CChildView::thisPtr->TextColor) || (CChildView::thisPtr->Button_Color == CChildView::thisPtr->Back_Color) || (CChildView::thisPtr->Button_Color== CChildView::thisPtr->TitleBarColor))
	{
		CChildView::thisPtr->Button_Color++;
		if(CChildView::thisPtr->Button_Color>11)
			CChildView::thisPtr->Button_Color=1;
	}
	CChildView::thisPtr->SaveData();
   CChildView::thisPtr->Invalidate();
}

void BackgroundColor(int Address)
{
   CChildView::thisPtr->Back_Color++;
	if(CChildView::thisPtr->Back_Color>11)
		CChildView::thisPtr->Back_Color=1;
	/* checking if Back_Color color is the same as button color or text color
	, if found then it is incremented */
	while((CChildView::thisPtr->Back_Color== CChildView::thisPtr->TextColor) || (CChildView::thisPtr->Back_Color == CChildView::thisPtr->Button_Color) 
		|| (CChildView::thisPtr->Back_Color == CChildView::thisPtr->TitleBarColor) ||(CChildView::thisPtr->Back_Color == CChildView::thisPtr->Highlight_Color)
		|| (CChildView::thisPtr->Back_Color == Black) || (CChildView::thisPtr->Back_Color == Red))
	{
		CChildView::thisPtr->Back_Color++;
		if(CChildView::thisPtr->Back_Color>11)
			CChildView::thisPtr->Back_Color=1;
	}
	CChildView::thisPtr->SaveData();
   CChildView::thisPtr->Invalidate();
}

void DefaultColor(int Address)
{
   CChildView::thisPtr->TextColor = Black;
	CChildView::thisPtr->TitleBarColor = Blue;
	CChildView::thisPtr->Button_Color= Gray;
	CChildView::thisPtr->Back_Color= White;
   CChildView::thisPtr->Highlight_Color=Green;
	CChildView::thisPtr->SaveData();
 //  CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

void TextColor(int Address)
{
   CChildView::thisPtr->TextColor++;
	if(CChildView::thisPtr->TextColor>11)
		CChildView::thisPtr->TextColor=1;
	/* checking if TextColor color is the same as button color or back color
	, if found then it is incremented */
	while((CChildView::thisPtr->TextColor== CChildView::thisPtr->Back_Color) || (CChildView::thisPtr->TextColor == CChildView::thisPtr->Button_Color) || (CChildView::thisPtr->TextColor == CChildView::thisPtr->Highlight_Color))
	{
		CChildView::thisPtr->TextColor++;
		if(CChildView::thisPtr->TextColor>11)
			CChildView::thisPtr->TextColor=1;
	}
	CChildView::thisPtr->SaveData();
   CChildView::thisPtr->Invalidate();
}

void TitleColor(int Address)
{
   CChildView::thisPtr->TitleBarColor++;
	if(CChildView::thisPtr->TitleBarColor>11)
		CChildView::thisPtr->TitleBarColor=1;
	/* checking if TitleBarColor color is the same as back color  or button color*/
	while((CChildView::thisPtr->TitleBarColor==CChildView::thisPtr->Back_Color) || 
		(CChildView::thisPtr->TitleBarColor==CChildView::thisPtr->Button_Color) || 
		(CChildView::thisPtr->TitleBarColor==White))
	{
		CChildView::thisPtr->TitleBarColor++;
		if(CChildView::thisPtr->TitleBarColor>11)
			CChildView::thisPtr->TitleBarColor=1;
	}
	CChildView::thisPtr->SaveData();
   CChildView::thisPtr->Invalidate();
}

void HighLightColor(int Address)
{
   CChildView::thisPtr->Highlight_Color++;
	if(CChildView::thisPtr->Highlight_Color>11)
		CChildView::thisPtr->Highlight_Color=2;
	/* checking if Highlight_Color color is the same as Back Color or black or white or red
	, if found then it is incremented */
	while((CChildView::thisPtr->Highlight_Color==CChildView::thisPtr->Back_Color)|| 
			(CChildView::thisPtr->Highlight_Color==Black)|| 
			(CChildView::thisPtr->Highlight_Color==White)||
			(CChildView::thisPtr->Highlight_Color==Red))
		{
			CChildView::thisPtr->Highlight_Color++;
			if(CChildView::thisPtr->Highlight_Color>11)
				CChildView::thisPtr->Highlight_Color=2;
		}
	CChildView::thisPtr->SaveData();
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}


/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  Modifying current       */
/*  preset No Information in List Box.                                            */
/**********************************************************************************/

void PresetDownExecute(int ID)
{
   if(CChildView::thisPtr->CurrentPresetNum==MaxPresetNum_InListBox)
	{
		 CChildView::thisPtr->ErrorBeep();
		return ;
	}
	CChildView::thisPtr->CurrentPresetNum=CChildView::thisPtr->CurrentPresetNum+1;
   int length =IntegerLength;
   unsigned char data1[5];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i=ID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
   union {
			int value;
			char y[IntegerLength];
			} v;
	
   v.value=CChildView::CurrentPresetNum;//object->GetRadio_Value();//getting radio value to char array.
   data1[2]=(char)v.y[1];
	data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];
    
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
      data = response->GetData();
		length = response->GetDataLength();
      if(ch==theApp.ACK)
		{
			int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         page_no=1;
		   {
			   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			}
      }
      delete response;
   }
   
	CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  Modifying current       */
/*  preset No Information in List Box.                                            */
/**********************************************************************************/

void PresetUpExecute(int ID)
{
   if(CChildView::thisPtr->CurrentPresetNum<=1)
	{
		 CChildView::thisPtr->ErrorBeep();
		return ;
	}
	CChildView::thisPtr->CurrentPresetNum=CChildView::thisPtr->CurrentPresetNum-1;
  
   int length =IntegerLength;
   unsigned char data1[5];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i=ID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
   union {
			int value;
			char y[IntegerLength];
			} v;
	
   v.value=CChildView::CurrentPresetNum;//object->GetRadio_Value();//getting radio value to char array.
   data1[2]=(char)v.y[1];
	data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];
   //Send Command if enable flag is true
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
      data = response->GetData();
		length = response->GetDataLength();
      if(ch==theApp.ACK)
		{
			int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         page_no=1;
		   {
			   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			}
      }
      delete response;
   }
   
	CChildView::thisPtr->Invalidate();
}

void SequenceUpButton(int Address)
{
   if(CChildView::thisPtr->CurrentSequencePreset<=1)
	{
			CChildView::thisPtr->ErrorBeep();
		return ;
	}
   CChildView::thisPtr->CurrentSequencePreset=	CChildView::thisPtr->CurrentSequencePreset-1;
   CChildView::thisPtr->Invalidate();
}


void SequenceDownButton(int Address)
{
   if(CChildView::thisPtr->CurrentSequencePreset==MaxSequencePresetNum_InListBox)
	{
		CChildView::thisPtr->ErrorBeep();
		return ;
	}


	if((CListBoxObject::CurrentSequencePresetName.GetLength()>2)||
		(CChildView::thisPtr->CurrentSequencePreset==0))
		CChildView::thisPtr->CurrentSequencePreset=CChildView::thisPtr->CurrentSequencePreset+1;
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  continue welding from   */
/*  particular preset sequence.                                                   */
/**********************************************************************************/

void ContinueSequence(int ID)
{
   if((CChildView::thisPtr->CurrentSequencePreset!=0))//&&(CVfdToggle::SequencingON))
	{
		CString temp;
		int num =0;
		CString ListBoxPreset=CListBoxObject::CurrentSequencePresetName;
		ListBoxPreset.Delete(0,ListBoxPreset.Find(L".",0)+2);
		if(ListBoxPreset.GetLength()>1)
		{
		  num = CChildView::thisPtr->CurrentSequencePreset;
		}
		if(num!=0)
		{
			int length =IntegerLength;
			unsigned char data1[5];
         union 
		   {
			   short i;
			   char c[2];
		   } u;
		   u.i=ID;
         data1[1]=u.c[0];
	      data1[0]=u.c[1];
		   
         union {
			int value;
			char y[IntegerLength];
			} v;
	      v.value=(num-1);//object->GetRadio_Value();//getting radio value to char array.
         data1[2]=(char)v.y[1];
	      data1[3]=(char)v.y[0];

			unsigned char * data = (unsigned char *) &data1[0];
			CHostCommand * request = new CHostCommand(SetValue_FunID, data, length);
			CHostCommand * response = app->SendUiHostCommand(request);
			if (response)
			{
				char ch=CHostCommand::AckNak();
				data = response->GetData();//Getting Data.
				length = response->GetDataLength();//Getting Length.
				if(ch==theApp.ACK)//If Ack.
				{	
               page_no=1;
		         {
			         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			      }
				}
				delete response;	
			}
		}
	}
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  Insert                  */
/*  particular preset sequence.                                                   */
/**********************************************************************************/

void InsertEditSequencePreset(int ID)
{
   int TotalPreset=0;
	char PresetNum[33];
   CList<int,int>PresetNumbers;
   int TotalNum=0;
   CVgaMenu * menu1;
   if((CListBoxObject::CurrentPresetName.GetLength()>1))
   {
      menu1=theApp.MenuPointer;
      POSITION pos = menu1->items.GetHeadPosition();
	   CVgaMenuItem * Object;
	   while(pos)
	   {
		   Object = menu1->items.GetNext(pos);
		   if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
		   {
			   CListBoxObject *obj=(CListBoxObject*)Object;
            if(obj->Type==SEQUENCESCREEN)
            {
			      for(int Num =0;Num<MaxSequencePresetNum_InListBox;Num++)
			      {
				      CString temp;
				      CString ListBoxPreset=obj->ListBoxText[Num];
				      ListBoxPreset.Delete(0,ListBoxPreset.Find(L".",0)+1);
				      if(ListBoxPreset.GetLength()>1)
				      {
				        for(int i=1;i<3;i++)
					      temp += (char)ListBoxPreset.GetAt(i);
				        char temp1[3];
				        for(i=0;i<temp.GetLength();i++)
					      temp1[i]=(char)temp.GetAt(i);
					      
				        PresetNumbers.AddTail(atoi(temp1));
				        TotalNum++;
				      
				      }
			      }
            }
		   }
	   }
      bool CommandSendRequired=false;
      if((PresetNumbers.GetCount()!=MaxSequencePresetNum_InListBox)&&(CChildView::thisPtr->CurrentSequencePreset))
			   {
				   pos = menu1->items.GetHeadPosition();
				   while(pos)
				   {
					   Object = menu1->items.GetNext(pos);
					   if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
					   {
						   CListBoxObject *obj=(CListBoxObject*)Object;
                     if(obj->Type==PRESETSCREEN)
                     {
						      if(CChildView::thisPtr->CurrentPresetNum>0)
						      {
							      char Temp[3];
							      for(int i=0;i<2;i++)
							      Temp[i]=(char)(obj->ListBoxText[CChildView::thisPtr->CurrentPresetNum-1]).GetAt(i);
							      int presetnum=atoi(Temp);
                           POSITION pos =PresetNumbers.FindIndex(CChildView::thisPtr->CurrentSequencePreset-1);
							      if((PresetNumbers.GetCount()==CChildView::thisPtr->CurrentSequencePreset-1)
								      &&(CChildView::thisPtr->CurrentSequencePreset!=1))
                           {
                              PresetNumbers.AddTail(presetnum);
                           }
							      else if(CChildView::thisPtr->CurrentSequencePreset!=1)
                           {
                              PresetNumbers.InsertBefore(pos,presetnum);
                           }
							      else
                           {
								      PresetNumbers.AddHead(presetnum);
                           }
						      	CommandSendRequired=true;
						      }
                     }
					   }
				   }
			   }
       
		   if(CommandSendRequired)
         {
         int length =PresetNumbers.GetCount();
         length+=2;
         union 
		   {
			   short i;
			   char c[2];
		   } u;
		   u.i=ID;
         PresetNum[1]=u.c[0];
	      PresetNum[0]=u.c[1];
         PresetNum[2]=(char)PresetNumbers.GetCount();
         for(int t=3;t<=length;t++)
		   {
			   PresetNum[t]=(char)PresetNumbers.RemoveHead();
         }
         length+=1;
         unsigned char * data = (unsigned char *) &PresetNum[0];
		   CHostCommand * request = new CHostCommand(SetValue_FunID, data, length);
		   CHostCommand * response = app->SendUiHostCommand(request);
		   if (response)
		   {
			   char ch=CHostCommand::AckNak();
			   data = response->GetData();//Getting Data.
			   length = response->GetDataLength();//Getting Length.
            if(ch==theApp.ACK)//If Ack.
			   {
				   int Temp= CChildView::thisPtr->CurrentPresetNum;
				   int temp=CChildView::thisPtr->CurrentSequencePreset;
               page_no=1;
		         {
			         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			      }
				   CChildView::thisPtr->CurrentPresetNum=Temp;
			   	CChildView::CurrentSequencePreset=temp;
				}
            
			   delete response;	
		   }
         
         }
    }
    CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  replacing               */
/*  particular preset sequence.                                                   */
/**********************************************************************************/

void ReplaceEditSequencePreset(int ID)
{
   int TotalPreset=0;
	char PresetNum[33];
   CList<int,int>PresetNumbers;
   int TotalNum=0;
   CVgaMenu * menu1;
   if((CListBoxObject::CurrentPresetName.GetLength()>1))
   {
      menu1=theApp.MenuPointer;
      POSITION pos = menu1->items.GetHeadPosition();
	   CVgaMenuItem * Object;
	   while(pos)
	   {
		   Object = menu1->items.GetNext(pos);
		   if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
		   {
			   CListBoxObject *obj=(CListBoxObject*)Object;
            if(obj->Type==SEQUENCESCREEN)
            {
			      for(int Num =0;Num<MaxSequencePresetNum_InListBox;Num++)
			      {
				      CString temp;
				      CString ListBoxPreset=obj->ListBoxText[Num];
				      ListBoxPreset.Delete(0,ListBoxPreset.Find(L".",0)+1);
				      if(ListBoxPreset.GetLength()>1)
				      {
				        for(int i=1;i<3;i++)
					     temp += (char)ListBoxPreset.GetAt(i);
				        char temp1[3];
				        for(i=0;i<temp.GetLength();i++)
					        temp1[i]=(char)temp.GetAt(i);
					      
				        PresetNumbers.AddTail(atoi(temp1));
				        TotalNum++;
				      
				      }
			      }
            }
		   }
	   }
      bool CommandSendRequired=false;
      if((!PresetNumbers.IsEmpty())&&(CChildView::thisPtr->CurrentSequencePreset)
				   &&(CListBoxObject::CurrentSequencePresetName.GetLength()>2))
			   {
				   pos = menu1->items.GetHeadPosition();
				   while(pos)
				   {
					   Object = menu1->items.GetNext(pos);
					   if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
					   {
						   CListBoxObject *obj=(CListBoxObject*)Object;
                     if(obj->Type==PRESETSCREEN)
                     {
                        if(CChildView::thisPtr->CurrentPresetNum>0)
						      {
							      char Temp[3];
							      for(int i=0;i<2;i++)
							      Temp[i]=(char)(obj->ListBoxText[CChildView::thisPtr->CurrentPresetNum-1]).GetAt(i);
							      int presetnum=atoi(Temp);
                           POSITION pos =PresetNumbers.FindIndex(CChildView::thisPtr->CurrentSequencePreset-1);
							      PresetNumbers.SetAt(pos, presetnum);
						      	CommandSendRequired=true;
						      }
                     }
					   }
				   }
			   }
      
		   if(CommandSendRequired)
         {
         int length =PresetNumbers.GetCount();
         length+=2;
         union 
		   {
			   short i;
			   char c[2];
		   } u;
		   u.i=ID;
         PresetNum[1]=u.c[0];
	      PresetNum[0]=u.c[1];
         PresetNum[2]=(char)PresetNumbers.GetCount();
         for(int t=3;t<=length;t++)
		   {
			   PresetNum[t]=(char)PresetNumbers.RemoveHead();
         }
         length+=1;
         unsigned char * data = (unsigned char *) &PresetNum[0];
		   CHostCommand * request = new CHostCommand(SetValue_FunID, data, length);
		   CHostCommand * response = app->SendUiHostCommand(request);
		   if (response)
		   {
			   char ch=CHostCommand::AckNak();
			   data = response->GetData();//Getting Data.
			   length = response->GetDataLength();//Getting Length.
			   if(ch==theApp.ACK)//If Ack.
			   {
				   int Temp= CChildView::thisPtr->CurrentPresetNum;
				   int temp=CChildView::thisPtr->CurrentSequencePreset;
               page_no=1;
		         {
			         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			      }
				   CChildView::thisPtr->CurrentPresetNum=Temp;
			   	CChildView::CurrentSequencePreset=temp;
				}
            
			   delete response;	
		   }
         
         }
   }
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  delete                  */
/*  particular preset sequence.                                                   */
/**********************************************************************************/

void DeleteEditSequencePreset(int ID)
{
   int TotalPreset=0;
	char PresetNum[33];
   CList<int,int>PresetNumbers;
   int TotalNum=0;
   CVgaMenu * menu1;
   if((CChildView::thisPtr->CurrentSequencePreset>0)&&(CListBoxObject::CurrentSequencePresetName.GetLength()>2))
   {
      menu1=theApp.MenuPointer;
      POSITION pos = menu1->items.GetHeadPosition();
	   CVgaMenuItem * Object;
	   while(pos)
	   {
		   Object = menu1->items.GetNext(pos);
		   if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
		   {
			   CListBoxObject *obj=(CListBoxObject*)Object;
            if(obj->Type==SEQUENCESCREEN)
            {
			      for(int Num =0;Num<MaxSequencePresetNum_InListBox;Num++)
			      {
				      CString temp;
				      CString ListBoxPreset=obj->ListBoxText[Num];
				      ListBoxPreset.Delete(0,ListBoxPreset.Find(L".",0)+1);
				      if(ListBoxPreset.GetLength()>1)
				      {
				        for(int i=1;i<3;i++)
					     temp += (char)ListBoxPreset.GetAt(i);
				        char temp1[3];
				        for(i=0;i<temp.GetLength();i++)
					        temp1[i]=(char)temp.GetAt(i);
					      
				        PresetNumbers.AddTail(atoi(temp1));
				        TotalNum++;
				      
				      }
			      }
            }
		   }
	   }
      bool CommandSendRequired=false;
      
     if(!PresetNumbers.IsEmpty())
			   {
				   pos = menu1->items.GetHeadPosition();
				   while(pos)
				   {
					   Object = menu1->items.GetNext(pos);
                  if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
                  {
                     CListBoxObject *obj=(CListBoxObject*)Object;
                     if(obj->Type==SEQUENCESCREEN)
                     {
                        if(CChildView::thisPtr->CurrentSequencePreset>0)
						      {
							      char Temp[3];
							      CString ListBoxPreset=obj->ListBoxText[CChildView::thisPtr->CurrentSequencePreset-1];
							      ListBoxPreset.Delete(0,ListBoxPreset.Find(L".",0)+1);
							      if(ListBoxPreset.GetLength()>1)
							      {
								      for(int i=0;i<2;i++)
									      Temp[i]=(char)ListBoxPreset.GetAt(i);
								      int presetnum=atoi(Temp);
                              POSITION pos =PresetNumbers.FindIndex(CChildView::thisPtr->CurrentSequencePreset-1);
								      PresetNumbers.RemoveAt(pos);
							      	CommandSendRequired=true;
							      }
							      
						      }
               
					      }
                  }
				   }
			   }
     
        if(CommandSendRequired)
         {
         int length =PresetNumbers.GetCount();
         length+=2;
         union 
		   {
			   short i;
			   char c[2];
		   } u;
		   u.i=ID;
         PresetNum[1]=u.c[0];
	      PresetNum[0]=u.c[1];
         PresetNum[2]=(char)PresetNumbers.GetCount();
         for(int t=3;t<=length;t++)
		   {
			   PresetNum[t]=(char)PresetNumbers.RemoveHead();
         }
         length+=1;
         unsigned char * data = (unsigned char *) &PresetNum[0];
		   CHostCommand * request = new CHostCommand(SetValue_FunID, data, length);
		   CHostCommand * response = app->SendUiHostCommand(request);
		   if (response)
		   {
			   char ch=CHostCommand::AckNak();
			   data = response->GetData();//Getting Data.
			   length = response->GetDataLength();//Getting Length.
			   if(ch==theApp.ACK)//If Ack.
			   {
				   int Temp= CChildView::thisPtr->CurrentPresetNum;
				   int temp=CChildView::thisPtr->CurrentSequencePreset;
               page_no=1;
		         {
			         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			      }
				   CChildView::thisPtr->CurrentPresetNum=Temp;
			      if((temp>1))
					   CChildView::CurrentSequencePreset=temp;
			   }
            
			   delete response;	
		   }
         
         }
    }
    CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function is responsible for displaying VQS Screen                        */
/*                                                                                */
/**********************************************************************************/

void ShowQualityScreen(int Address)
{
    CWnd *pWndPrev, *pWndChild;
    // Determine if a window with the class name exists...
    if (pWndPrev = CWnd::FindWindow(NULL,_T("VQS")))
     {
		   // If so, does it have any popups?
		   pWndChild = pWndPrev->GetLastActivePopup();
		   // Bring the application to the foreground
		   pWndPrev->SetForegroundWindow();
     }
    
}

/**********************************************************************************/
/*                                                                                */
/*  This function Sends command to 332 with Menu ID & On Ack, ErrorBeep()         */
/*  function is executed.                                                               */
/**********************************************************************************/

void SendCommandForButton(int ID)
{
	int length =2;
   unsigned char data1[2];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i=ID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
  
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
      if(ch==theApp.ACK)
		{
			CChildView::thisPtr->ErrorBeep();
      }
      else if(ch==theApp.NAK)
      {
         CChildView::thisPtr->ProcessNak(data,length,0,0);
      }
      delete response;
   }
	CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function Sends command to 332 with Menu ID & builds Menu Items.          */
/*                                                                                */
/**********************************************************************************/

void SendCommandForButtons(int ID)
{
	int length =2;
   unsigned char data1[2];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i=ID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
  
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
      if(ch==theApp.ACK)
		{
		   {
			   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			}
      }
      else if(ch==theApp.NAK)
      {
         CChildView::thisPtr->ProcessNak(data,length,0,0);
      }
      delete response;
   }
	CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function Sends command to 332 with Menu ID & starts BottomHalf Timer     */
/*  for Scan start.                                                               */
/**********************************************************************************/
void StartScan(int ID)
{
	CVgaMenu * menu1,*menu;
   menu1=theApp.MenuPointer ;
   POSITION pos = menu1->items.GetHeadPosition();
   CVgaMenuItem * object;
   int length =2;
   unsigned char data1[2];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i=ID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
  
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
      if(ch==theApp.ACK)
		{
		   CChildView::thisPtr->DisableFlag=true;
         while (pos)
	      {
		      object = menu1->items.GetNext(pos);
            if(object->GetType() == CVgaMenu::VGABottomHalfObject)
            {
               CBottomHalf *obj=(CBottomHalf*)object;
               CChildView::BotomHalfRefreshTime=obj->RefreshTime;
               if(theApp.menus.Lookup(obj->submenu, menu))
               {
                  POSITION pos1 = menu->items.GetHeadPosition();
		            while (pos1)
		            {
			            object = menu->items.GetNext(pos1);
                     if(object->GetType() == CVgaMenu::VGA_Button_OBJECT)
                     {
                        CVgaButton *ptr=(CVgaButton *)object;
                        if(ptr->argument==".")
                        {
                           ptr->text=CChildView::ScanString;
                           break;
                        }
                     }
                  }
               }
               
            }
         }
         
      }
      else if(ch==theApp.NAK)
      {
         CChildView::thisPtr->ProcessNak(data,length,0,0);
      }
      delete response;
   }
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function Sends command to 332 with Menu ID, executes some function on                    */
/*  controller side.                                                                             */
/**********************************************************************************/

void WeldRetract(int ID)
{
   int length =2;
   unsigned char data1[2];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i=ID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
  
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
      delete response;
   }
   CChildView::thisPtr->Invalidate();

}

/**********************************************************************************/
/*                                                                                */
/*  This function Sends command to 332 for Testing Menus items.                   */
/*  .                                                                             */
/**********************************************************************************/

void SendCommandForTestingMenu(int ID)
{
   int length =2;
   unsigned char data1[2];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i=ID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
  
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		CChildView::thisPtr->menusname.RemoveTail();
		CChildView::thisPtr->menus.RemoveTail();
      CChildView::thisPtr->menupointers.RemoveTail();
		delete response;
    }
   CChildView::thisPtr->Invalidate();

}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & stops horn scan, displays Message        */
/*  accordingly.                                                                  */
/**********************************************************************************/

void HornScanAbort(int ID)
{
   int length =2;
   unsigned char data1[2];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i=ID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
   CChildView::thisPtr->DisableFlag=false;
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
      delete response;
   }
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & build menu items according to type of    */
/*  actuator.                                                                     */
/**********************************************************************************/
void SendSpecialMenuCommand(int ID)
{

   /* keep it for later */
   /*
   CString MenuName="";
   CVgaMenu * menu1=theApp.MenuPointer;
   POSITION pos = menu1->items.GetHeadPosition();
   CVgaMenuItem * Object;
   while(pos)
   {
	  Object = menu1->items.GetNext(pos);
      if(Object->GetType() == CVgaMenu::VGABottomHalfObject)
      {
         CBottomHalf *obj=(CBottomHalf*)Object;
         MenuName=obj->submenu;
         CVgaMenu * menu;
         if (theApp.menus.Lookup(MenuName, menu))
		 {
            CBottomHalf::BottomMenuPointer=menu;
         }
         CChildView::thisPtr->MenuNameID=MenuName;
         CBottomHalf::BottomHalfId=obj->EnumID;
         CChildView::BotomHalfRefreshTime=obj->RefreshTime;
         break;
      }
   }
   CChildView::thisPtr->Invalidate();
   */

   int length =2;
   unsigned char data1[2];
   union 
	   {
		   short i;
		   char c[2];
	   } u;
	u.i=ID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
  
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
      char ch=CHostCommand::AckNak();
	  data = response->GetData();
	  length = response->GetDataLength();
     if(ch==theApp.ACK)
	  {
		  CChildView::thisPtr->Invalidate();
	  }
	  else if(ch==theApp.NAK)
	  {
		 theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
		 page_no=CChildView::thisPtr->menus.RemoveTail();	
       theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		 CChildView::thisPtr->ProcessNak(data,length,0,0);
	  }
	  delete response;
   }

}

/**********************************************************************************/
/*                                                                                */
/*  This function update the microns values                                       */
/*                                                                                */
/**********************************************************************************/
void SendMicronsUpdateCommand(int ID)
{
	theApp.GetSystemVariable();
	theApp.SetMicronsUpdate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & build menu items according to type of    */
/*  actuator.                                                                     */
/**********************************************************************************/
void SendHornDownCommand(int ID)
{
   int length =2;
   unsigned char data1[2];
   union 
	   {
		   short i;
		   char c[2];
	   } u;
	u.i=ID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
  
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
      char ch=CHostCommand::AckNak();
	  data = response->GetData();
	  length = response->GetDataLength();
     if(ch==theApp.ACK)
	  {
        CBottomHalf::HornDownScreenPresent=true;
        CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
        CString MenuName="";
         CVgaMenu * menu1=theApp.MenuPointer;
         POSITION pos = menu1->items.GetHeadPosition();
         CVgaMenuItem * Object;
	      while(pos)
	      {
		      Object = menu1->items.GetNext(pos);
            if(Object->GetType() == CVgaMenu::VGABottomHalfObject)
            {
               CBottomHalf *obj=(CBottomHalf*)Object;
               MenuName=obj->submenu;
               CVgaMenu * menu;
               if (theApp.menus.Lookup(MenuName, menu))
		         {
                  CBottomHalf::BottomMenuPointer=menu;
               }
               CChildView::thisPtr->MenuNameID=MenuName;
               CBottomHalf::BottomHalfId=obj->EnumID;
               CChildView::BotomHalfRefreshTime=obj->RefreshTime;
               break;
            }
         }
         CChildView::thisPtr->Invalidate();
	  }
	  else if(ch==theApp.NAK)
	  {
       theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
		 page_no=CChildView::thisPtr->menus.RemoveTail();	
       theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
       CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
		 CChildView::thisPtr->ProcessNak(data,length,0,0);
       CChildView::thisPtr->Invalidate();
	  }
	  delete response;
   }
}

void HistoryLeftButton(int Address)
{
	if(CWeldingHistory::thisHisPtr->LeftMostParameter>1)
		CWeldingHistory::thisHisPtr->LeftMostParameter--;
	else
		CChildView::ErrorBeep();
	CChildView::thisPtr->Invalidate();
}

void HistoryRightButton(int Address)
{
	if(CWeldingHistory::thisHisPtr->LeftMostParameter<(CWeldingHistory::thisHisPtr->TotalColoumn)-4)
		CWeldingHistory::thisHisPtr->LeftMostParameter++;
	else
		CChildView::ErrorBeep();
	CChildView::thisPtr->Invalidate();
}

void HistoryScreenUpButton(int Address)
{
	if(CWeldingHistory::thisHisPtr->TopMostData>MaxCyclePerScreen)
	{
		(CWeldingHistory::thisHisPtr->TopMostData)-=MaxCyclePerScreen;
		CWeldingHistory::thisHisPtr->SelectedWeldData=1;
	}
	else if(CWeldingHistory::thisHisPtr->TopMostData!=1)
	{
		CWeldingHistory::thisHisPtr->TopMostData=1;
		CWeldingHistory::thisHisPtr->SelectedWeldData=1;
	}
	else
		CChildView::ErrorBeep();
	CChildView::thisPtr->Invalidate();
}

void HistoryScreenDownButton(int Address)
{
   if(((CWeldingHistory::thisHisPtr->TotalCycle)> MaxCyclePerScreen)&&((CWeldingHistory::thisHisPtr->TopMostData)+ MaxCyclePerScreen <=(CWeldingHistory::thisHisPtr->TotalCycle)))//(TopMostData+7 !=TotalCycle-1))
	{
      (CWeldingHistory::thisHisPtr->TopMostData)+=MaxCyclePerScreen;
		CWeldingHistory::thisHisPtr->SelectedWeldData=1;

	}
	else
		CChildView::ErrorBeep();
	CChildView::thisPtr->Invalidate();
}

void HistoryUpButton(int Address)
{
   if((CWeldingHistory::thisHisPtr->SelectedWeldData)==1)
	{
		if((CWeldingHistory::thisHisPtr->TopMostData)>1)
			CWeldingHistory::thisHisPtr->TopMostData--;
		else
			CChildView::ErrorBeep();
	}
	if((CWeldingHistory::thisHisPtr->SelectedWeldData)>1)
		CWeldingHistory::thisHisPtr->SelectedWeldData--;
	CChildView::thisPtr->Invalidate();

}

void HistoryDownButton(int Address)
{
	if((CWeldingHistory::thisHisPtr->SelectedWeldData)==MaxCyclePerScreen)
	{
		if(((CWeldingHistory::thisHisPtr->TotalCycle)-(CWeldingHistory::thisHisPtr->TopMostData))>=MaxCyclePerScreen)
			CWeldingHistory::thisHisPtr->TopMostData++;
		else
			CChildView::ErrorBeep();
	}
	else
	if((((CWeldingHistory::thisHisPtr->SelectedWeldData)+(CWeldingHistory::thisHisPtr->TopMostData))<=(CWeldingHistory::thisHisPtr->TotalCycle))&&((CWeldingHistory::thisHisPtr->SelectedWeldData)!=MaxCyclePerScreen))
		CWeldingHistory::thisHisPtr->SelectedWeldData++;
	else
		CChildView::ErrorBeep();
	CChildView::thisPtr->Invalidate();
}

void ShowPowerSupplyMessageScreen(int Address)
{
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   TRY
   {
      CString Temp;
      CVgaMenuItem *object,*object1;
      CVgaButton *ptr=(CVgaButton *)Address;
      CChildView::thisPtr->EnableUSBGraph=false;
      POSITION pos1=menu->items.GetHeadPosition();
      while (pos1)
      {
        object= menu->items.GetNext(pos1);
	     if(object->GetType()==CVgaMenu::VGAMsgScrnObject)
	     {
		      CMsgScreen *ptr=(CMsgScreen *)object;
		      Temp=object->text;
		      CDC *pDC=CChildView::thisPtr->GetDc();
		      CChildView::thisPtr->EnableWindow(false);

		      /*Drawing Message Rectangle in specified color*/
		      CVgaMenuItem::DrawRect(pDC, Black,MESSAGESCRN_BLACKRECT);
		      CVgaMenuItem::DrawRect(pDC, Blue, MESSAGESCRNRECT);

		      /*Drawing Message Text*/
		      CVgaMenuItem::DrawText(pDC, Bigfont,White , MESSAGESCRNRECT,Temp,true);
		      CChildView::thisPtr->ReleaseDc(pDC);	
		      CChildView::thisPtr->DisableFlag=true;
		      CChildView::thisPtr->InitialiseTimer(ERROR_MESSAGE_TIMER,MESSAGESCRNTIME);
		      CChildView::thisPtr->EnableWindow(true);
	     }
	     else if(object->GetType()==CVgaMenu::VGAHISTORYOBJECT)
	     {
		      CWeldingHistory *Runptr=(CWeldingHistory *)object;
            while(Runptr->USBWeldHistoryList.GetCount()>0)
	         {
		         CHistoryData *obj1 = Runptr->USBWeldHistoryList.RemoveHead();//delete
		         free(obj1);
	         }
            while(Runptr->WeldHistoryList.GetCount()>0)
            {
               delete Runptr->WeldHistoryList.RemoveHead();
            }
            for(int HistoryDataNo =1;HistoryDataNo<=2;HistoryDataNo++)
		      {
			      int length =CORDLENGTH;
			      unsigned char CommandData[CORDLENGTH];
			      CommandData[ZERO]=(char)WELDDATA;
			      if(HistoryDataNo ==1)
				      CommandData[ONE]=(char)FIRST25WELDDATA;
			      else
				      CommandData[ONE]=(char)LAST25WELDDATA;

			      unsigned char * data = (unsigned char *) &CommandData[ZERO];
			      CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
			      CHostCommand * response = app->SendUiHostCommand(request);
			      if(response)
			      {	
			         char ch=CHostCommand::AckNak();
				      data = response->GetData();
				      length = response->GetDataLength();
				      if(ch==theApp.ACK)
				      {
					     if(HistoryDataNo==1)
					      {
						      Runptr->SelectedDataUnit=CChildView::metric;
						      Runptr->TopMostData=1;
						      Runptr->SelectedWeldData=1;
						      
						      Runptr->TotalColoumn=*data++;
						      length--;	
						      Runptr->Parameter_ID=new int[Runptr->TotalColoumn];

						      /*Storing parameters ID.*/
						      for(int param=0;param<Runptr->TotalColoumn;param++)	
						      {
							      Runptr->Parameter_ID[param]=*data++;
							      length--;
						      }
						      /*Numbers of cycle for which weld data is to be shown.*/
						      int ReceivedUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
						      Runptr->TotalCycle=*data++;
						      length--;
						      /*while(Runptr->WeldHistoryList.GetCount()>0)
                        {
                           delete Runptr->WeldHistoryList.RemoveHead();
                        }*/
					         
							   for(int cycle =0;cycle<Runptr->TotalCycle;cycle++)
							   {
								   CWeldingData * obj = new CWeldingData(Runptr->TotalColoumn,data, length);
								   Runptr->WeldHistoryList.AddTail(obj);
							   }
						      if(Runptr->TotalCycle==0)
						      {	
						         object1= menu->items.GetNext(pos1);
                           if(object1->GetType()==CVgaMenu::VGAMsgScrnObject)
                           {
		                        CMsgScreen *ptr=(CMsgScreen *)object1;
		                        Temp=object1->text;
		                        CDC *pDC=CChildView::thisPtr->GetDc();
		                        CChildView::thisPtr->EnableWindow(false);

		                        /*Drawing Message Rectangle in specified color*/
		                        CVgaMenuItem::DrawRect(pDC, Black,MESSAGESCRN_BLACKRECT);
		                        CVgaMenuItem::DrawRect(pDC, Blue, MESSAGESCRNRECT);

		                        /*Drawing Message Text*/
		                        CVgaMenuItem::DrawText(pDC, Bigfont,White , MESSAGESCRNRECT,Temp,true);
		                        CChildView::thisPtr->ReleaseDc(pDC);	
		                        CChildView::thisPtr->DisableFlag=true;
		                        CChildView::thisPtr->InitialiseTimer(ERROR_MESSAGE_TIMER,MESSAGESCRNTIME);
		                        CChildView::thisPtr->EnableWindow(true);
                           }
							      delete response;
                           theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
		                     page_no=CChildView::thisPtr->menus.RemoveTail();
                           theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		                     return ;
						      }
					      }
					      else
					      {
						     Runptr->UpdateWeldData(data,length);
					      }
				      }
				      else
				      {
                     theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
		               page_no=CChildView::thisPtr->menus.RemoveTail();
                     theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		               CChildView::thisPtr->ProcessNak(data,length,(int)ptr,0);
					      delete response;
                     return ;
				      }
				      delete response;
			      }
		      }
		      break;
         }
      }
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);  
      CChildView::thisPtr->Invalidate();
   }
   CATCH_ALL(E)
   {
      TCHAR  szCause[255];
      E->GetErrorMessage(szCause, 255);
      CString x;
      x = _T("The error: ");
      x += szCause;
      //AfxMsgBox(x);
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
		page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);  
      CChildView::thisPtr->Invalidate();
   }
   END_CATCH_ALL

}

void SetGraphObjectMember(unsigned char * &data, int & length,CVgaDrawGraph * Graph)
{
   Graph->GraphData.GraphColour=*data++;length--;
   for(int i=0;i<20;i++)
		Graph->GraphData.CycleCount[i]='\0';
    CString str=CChildView::thisPtr->CycleCountString;//CVgaMenuItem ::LinearSearch(Graph->CycleCountID);
    _tcscpy(Graph->GraphData.CycleCount,str);
    Graph->SetGraphRequestValue(Graph->GraphData.graph_type);
    for( i=0;i<20;i++)
		Graph->GraphData.SystemPressure[i]='\0';
	 Graph->AlreadyPrinted=false;
	 Graph->Lang_Index=0;//CChildView::Language_Index;
	 Graph->No_Graph_String=" ";
    CVgaDrawGraph::GraphCount++;
    Graph->GraphData.GraphNum=CVgaDrawGraph::GraphCount;
    Graph->GraphData.DataLength=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
	 for(short len=0;len<Graph->GraphData.DataLength;len++)
	 {
			Graph->GraphData.graphdata[len]=(short)*data++;
			length--;
    }
	 Graph->Store_VData_HData(data,length);
	 Graph->StoreTickData(data,length);
	 for(int q=0;q<7;q++)
	 {
		 Graph->GraphData.TickData[q]=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);	
	  
	 }

	 union{ 
		  int i;
		  bool ExtraByte;
	 }u;
	 u.i=*data++;
	 Graph->GraphData.ExtraText=u.ExtraByte; 
	 length--;
	 u.i=*data++;
	 Graph->GraphData.ManualStr=u.ExtraByte;
	 length--;
	 TCHAR TemproryCycle[20];
    CVgaMenuItem::GetCharString (data,length,TemproryCycle);
    i=0;
    while(Graph->GraphData.CycleCount[i]!='\0')
    {
       i++;
    }
    for(int j=0;i<19;i++,j++)
    {
       Graph->GraphData.CycleCount[i]=TemproryCycle[j];
    }
    Graph->GraphData.CycleCount[i]='\0';
    CVgaMenuItem::GetCharString (data,length,Graph->GraphData.SystemPressure);
}

void GraphRefresh(int Address)
{
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   POSITION POSI=menu->items.GetHeadPosition();
   if(CChildView::thisPtr->ViewGraphGlobalCount==CChildView::thisPtr->UniversalCount)
   {
      return ;//true;
   }

	CVgaDrawGraph::GraphCount=0;
	while(theApp.GraphsDataList.GetCount()>0)
		  theApp.GraphsDataList.RemoveHead();
	if(CChildView::thisPtr->ViewGraphWeldData)
	{
		delete CChildView::thisPtr->ViewGraphWeldData;
		CChildView::thisPtr->ViewGraphWeldData=0;
	}
	unsigned char RequestType = (char)126;
	int length =2;
	unsigned char data1[2];
	data1[0]=(char)RequestType;
	data1[1]=(char)0;
	unsigned char * data = (unsigned char *) &data1[0];
	CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if (response)
	{
		CChildView::thisPtr->ViewGraphGlobalCount=CChildView::thisPtr->UniversalCount;
		char ch=CHostCommand::AckNak();
		data = response->GetData();//Getting Data.
		 length = response->GetDataLength();//Getting Length.
		 if(ch==theApp.ACK)//If Ack.
		 {		//store graph data
			 while ((POSI)&&(length>0))
           {
             object= menu->items.GetNext(POSI);
	          if(object->GetType()==CVgaMenu::VGA_GRAPH_OBJECT)
             {
                CVgaDrawGraph * ptr = (CVgaDrawGraph *)object;
					 int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                if((ValueAfterParamID==ptr->GraphType)&&(ValueAfterParamID!=NO_VALID_GRAPH))
                {
                   ptr->GraphData.graph_type=ValueAfterParamID;
                   SetGraphObjectMember(data,length,ptr);
                   theApp.GraphsDataList.AddTail(ptr);
                }
                else if(ValueAfterParamID==NO_VALID_GRAPH && ValueAfterParamID==ptr->GraphType)
                {
                   ptr->GraphData.graph_type=ValueAfterParamID;
                   for(int i=0;i<20;i++)
		               ptr->GraphData.GRAPHTITLE[i]='\0';
                   for( i=0;i<20;i++)
		               ptr->GraphData.CycleCount[i]='\0';
                   for( i=0;i<20;i++)
		               ptr->GraphData.SystemPressure[i]='\0';
	                ptr->AlreadyPrinted=false;
	                ptr->Lang_Index=0;//CChildView::Language_Index;
	                ptr->No_Graph_String=" ";
                   ptr->GraphCount++;
	                ptr->GraphData.GraphNum =ptr->GraphCount;
                   ptr->No_Graph_String=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                   theApp.GraphsDataList.AddTail(ptr);
                }
                else
                {
                   *data--;length++;
                   *data--;length++;
                }
              }
          }
			 POSITION pos = theApp.GraphsDataList.GetHeadPosition();
			 while(pos)
			 {
				 CVgaDrawGraph *Graph= theApp.GraphsDataList.GetNext(pos);
				 if((CChildView::thisPtr->GraphOneRequestValue==0)&&(CChildView::thisPtr->GraphTwoRequestValue==0))
				 {
					if(Graph->GraphData.GraphRequestValue==2)
						Graph->GraphData.GraphNum=1;
					CChildView::thisPtr->GraphOneRequestValue=2;
				 }
				 else
				 {						
					if(Graph->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue)
						Graph->GraphData.GraphNum=1;
					else if(Graph->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue)
					Graph->GraphData.GraphNum=2;
				 }
				}
		 }
		 else 
			CChildView::thisPtr->ErrorBeep();
		 delete response;
		 /************************/
		 int length =CORDLENGTH;
			unsigned char data1[CORDLENGTH];
			data1[0]=(char)01;//(++TotalGraphRequestValue);
			data1[1]=(char)01;
			unsigned char * data = (unsigned char *) &data1[0];
			request = new CHostCommand(GetWeldData_FunID, data, length);
			response= app->SendUiHostCommand(request);
			if(response)
			{
				char ch=CHostCommand::AckNak();
				data = response->GetData();//Getting Data.
				length = response->GetDataLength();//Getting Length.
				
				if(ch==theApp.ACK)
				{
					//view->ViewGraphWelddataLength=length;
					CChildView::thisPtr->ViewGraphWeldData=response;
				}
				//delete view->ViewGraphWeldData;
			}
/*********************/
	}
   CChildView::thisPtr->Invalidate();
}

/******************************************************************************************/
/* This function is responsible to get graph data. the function is called when the user   */
/* clicks on any of the graph button or on the refresh button							  */
/*																						  */	
/******************************************************************************************/
void GetGraphData(unsigned char RequestType)
{
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   POSITION POSI=menu->items.GetHeadPosition();

   POSITION pos = theApp.GraphsDataList.GetHeadPosition();
	/* of 2 graphs are present  and refresh is required*/	
	int graph_num1,graph_num2;
	int GraphRequestValue1,GraphRequestValue2;
	pos = theApp.GraphsDataList.GetHeadPosition();
	CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
	graph_num1= obj->GraphData.GraphNum;
	GraphRequestValue1 = obj->GraphData.GraphRequestValue;
	if(theApp.GraphsDataList.GetCount()==2)
	{
		obj = theApp.GraphsDataList.GetNext(pos);
		graph_num2= obj->GraphData.GraphNum;
		GraphRequestValue2 = obj->GraphData.GraphRequestValue;
	}

	int length =2;
	unsigned char data1[2];
	data1[0]=(char)RequestType;
	data1[1]=(char)0;
	unsigned char * data = (unsigned char *) &data1[0];

	CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if (response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();//Getting Data.
		 length = response->GetDataLength();//Getting Length.
		 if(ch==theApp.ACK)//If Ack.
		 {		//store graph data
			 while(theApp.GraphsDataList.GetCount()>0)
				 theApp.GraphsDataList.RemoveHead();
          
          while ((POSI)&&(length>0))
          {
             object= menu->items.GetNext(POSI);
	          if(object->GetType()==CVgaMenu::VGA_GRAPH_OBJECT)
             {
                CVgaDrawGraph * ptr = (CVgaDrawGraph *)object;
					 int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                if((ValueAfterParamID==ptr->GraphType)&&(ValueAfterParamID!=NO_VALID_GRAPH))
                {
                   ptr->GraphData.graph_type=ValueAfterParamID;
                   SetGraphObjectMember(data,length,ptr);
                   theApp.GraphsDataList.AddTail(ptr);
               }
               else if(ValueAfterParamID==NO_VALID_GRAPH && ValueAfterParamID==ptr->GraphType)
               {
                  ptr->GraphData.graph_type=ValueAfterParamID;
                  for(int i=0;i<20;i++)
		               ptr->GraphData.GRAPHTITLE[i]='\0';
                  for( i=0;i<20;i++)
		               ptr->GraphData.CycleCount[i]='\0';
                  for( i=0;i<20;i++)
		               ptr->GraphData.SystemPressure[i]='\0';
	               ptr->AlreadyPrinted=false;
	               ptr->Lang_Index=0;//CChildView::Language_Index;
	               ptr->No_Graph_String=" ";
                  ptr->GraphCount++;
	               ptr->GraphData.GraphNum = ptr->GraphCount;
                  ptr->No_Graph_String=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                  theApp.GraphsDataList.AddTail(ptr);
               }
               else
               {
                  *data--;length++;
                  *data--;length++;
               }
               
            }
			 }
			pos = theApp.GraphsDataList.GetHeadPosition();
			while(pos)
			{
				CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
				if(obj->GraphData.GraphRequestValue == GraphRequestValue1)
					obj->GraphData.GraphNum =graph_num1;
				else if(obj->GraphData.GraphRequestValue == GraphRequestValue2)
					obj->GraphData.GraphNum =graph_num2;
			}

			if(theApp.GraphsDataList.GetCount()>1)
			if( (((theApp.GraphsDataList.GetHead())->GraphData.GraphNum)%2)
				== (((theApp.GraphsDataList.GetTail())->GraphData.GraphNum)%2))
			if( ((theApp.GraphsDataList.GetHead())->GraphData.GraphNum)
				> ((theApp.GraphsDataList.GetTail())->GraphData.GraphNum))
			
				((theApp.GraphsDataList.GetHead())->GraphData.GraphNum)--;
			else
				((theApp.GraphsDataList.GetTail())->GraphData.GraphNum)--;
		 }
		 else 
		 {
			 CChildView::thisPtr->ErrorBeep();
		}
		 delete response;
	}
	else
       ERRORBEEP;

}


/*****************************************************************************************/
/* This function works with getgraph data to get Graph data when user clicks on any graph */
/* button or on the refresh button.														 */
/*																						 */			
/*****************************************************************************************/
void GetData(unsigned char RequestValue)
{
	bool Is_Present=false;int temp=0;
	if(CChildView::thisPtr->AutoRefreshon)
	{
      if(theApp.GraphsDataList.GetCount()==2)
		{		
         POSITION pos = theApp.GraphsDataList.GetHeadPosition();
			CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
			if( RequestValue == obj->GraphData.GraphRequestValue)
			{
				if(RequestValue ==CChildView::thisPtr->GraphOneRequestValue)
				{
					CChildView::thisPtr->GraphOneRequestValue=CChildView::thisPtr->GraphTwoRequestValue;
					CChildView::thisPtr->GraphTwoRequestValue=0;
				}
				else if(RequestValue ==CChildView::thisPtr->GraphTwoRequestValue)
					CChildView::thisPtr->GraphTwoRequestValue=0;
				Is_Present=true;
				 theApp.GraphsDataList.RemoveHead();
			}
			obj = theApp.GraphsDataList.GetNext(pos);

         if( RequestValue == obj->GraphData.GraphRequestValue)
			{
				if(RequestValue ==CChildView::thisPtr->GraphOneRequestValue)
				{
					CChildView::thisPtr->GraphOneRequestValue=CChildView::thisPtr->GraphTwoRequestValue;
					CChildView::thisPtr->GraphTwoRequestValue=0;
				}
				else if(RequestValue ==CChildView::thisPtr->GraphTwoRequestValue)
					CChildView::thisPtr->GraphTwoRequestValue=0;
				Is_Present=true;
				theApp.GraphsDataList.RemoveTail();
			}
			
			if(Is_Present)
			{
				POSITION pos = theApp.GraphsDataList.GetHeadPosition();
				while(pos)
				{
					CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
					obj->GraphData.GraphNum=1;
					temp +=obj->GraphData.GraphRequestValue;
				}
				GetGraphData(temp);
			}
			else
			{	
            TRACE(_T("\n\n\n graph req value new %d "),RequestValue);
				int GraphNum1,GraphNum2;int Req;
				pos = theApp.GraphsDataList.GetHeadPosition();
				CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
				GraphNum1= obj->GraphData.GraphNum;Req = obj->GraphData.GraphRequestValue;
			
				obj = theApp.GraphsDataList.GetNext(pos);
				GraphNum2= obj->GraphData.GraphNum;
				if(GraphNum2 >GraphNum1)
					Req = obj->GraphData.GraphRequestValue;
				RequestValue +=Req;
				GetGraphData(RequestValue);
			}
		}
		else
		{
         POSITION pos = theApp.GraphsDataList.GetHeadPosition();
			CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
			if(( RequestValue != obj->GraphData.GraphRequestValue)/*&&(obj->GraphData.graph_type !=VGA_NOGRAPH)*/)
				RequestValue +=obj->GraphData.GraphRequestValue;
			GetGraphData(RequestValue);
		}
	}
	else
	{
		int GraphNum1=0;int GraphNum2=0;
      
		if((RequestValue==CChildView::thisPtr->GraphOneRequestValue)||(RequestValue==CChildView::thisPtr->GraphTwoRequestValue))
		{

			POSITION pos = theApp.GraphsDataList.GetHeadPosition();
			while(pos)
			{
				CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
				if((RequestValue==CChildView::thisPtr->GraphOneRequestValue)
					&&(obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue))
				{
					if(CChildView::thisPtr->GraphTwoRequestValue!=0)
					{
						obj->GraphData.GraphNum=0;
						CChildView::thisPtr->GraphOneRequestValue=0;
					}

				}
				else if((RequestValue==CChildView::thisPtr->GraphTwoRequestValue)
					&&(obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue))
				{
					if(CChildView::thisPtr->GraphOneRequestValue!=0)
					{
						obj->GraphData.GraphNum=0;
						CChildView::thisPtr->GraphTwoRequestValue=0;
					}
				}
			}
			pos = theApp.GraphsDataList.GetHeadPosition();
			while(pos)
			{
				CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
				if((obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue))
				{
					if(CChildView::thisPtr->GraphTwoRequestValue==0)
					{
						if((obj->GraphData.GraphNum%2==0))
							obj->GraphData.GraphNum--;
						if(obj->GraphData.GraphNum<0)
							obj->GraphData.GraphNum+=2;
						
					}

				}

            else if((obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue))
				{
					if(CChildView::thisPtr->GraphOneRequestValue==0)
					{
						if((obj->GraphData.GraphNum%2==0))
							obj->GraphData.GraphNum--;
						if(obj->GraphData.GraphNum<0)
							obj->GraphData.GraphNum+=2;

					}
				}
			}
			return;

		}



		POSITION pos = theApp.GraphsDataList.GetHeadPosition();
		while(pos)
		{
			CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
			if((obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue))
			{
				GraphNum1=obj->GraphData.GraphNum;
				
			}
			else if((obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue))
			{
				GraphNum2=obj->GraphData.GraphNum;
				
			}
		}
		pos = theApp.GraphsDataList.GetHeadPosition();
		while(pos)
		{
			CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
			if(obj->GraphData.GraphRequestValue==RequestValue)
			{
				if((GraphNum1>GraphNum2))
				{
					
					CChildView::thisPtr->GraphTwoRequestValue=RequestValue;
					if(GraphNum2!=0)
					obj->GraphData.GraphNum=GraphNum2+2;
					else
						obj->GraphData.GraphNum=GraphNum1+1;

				}
				else
				{	
					CChildView::thisPtr->GraphOneRequestValue=RequestValue;
						if(GraphNum1!=0)
					obj->GraphData.GraphNum=GraphNum1+2;
					else
						obj->GraphData.GraphNum=GraphNum2+1;
					
				}

			}
			if((obj->GraphData.GraphRequestValue!=CChildView::thisPtr->GraphTwoRequestValue)&&(obj->GraphData.GraphRequestValue!=CChildView::thisPtr->GraphOneRequestValue))
			obj->GraphData.GraphNum=0;
		}


	}
}

void Color_DistanceGraph(int Address)
{
   GetData(Distance_RequestValue);
   CChildView::thisPtr->Invalidate();
}

void Power_Graph(int Address)
{
   GetData(Power_RequestValue);
   CChildView::thisPtr->Invalidate();
}

void Velocity_Graph(int Address)
{
   GetData(Velocity_RequestValue);
   CChildView::thisPtr->Invalidate();
}

void Force_Graph(int Address)
{
   GetData(Force_RequestValue);
   CChildView::thisPtr->Invalidate();
}

void Amplitude_Graph(int Address)
{
   GetData(Amplitude_RequestValue);
   CChildView::thisPtr->Invalidate();
}

void Frequency_Graph(int Address)
{
   GetData(Frequency_RequestValue);
   CChildView::thisPtr->Invalidate();
}

void ExitGraphMenu(int Address)
{
   while(theApp.GraphsDataList.GetCount()>0)
		  theApp.GraphsDataList.RemoveHead();
   CChildView::thisPtr->PMCScreen=false;
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);  
   CChildView::thisPtr->Invalidate();
}

void ExitBandLimitsMenu(int Address)
{
   while(theApp.GraphsDataList.GetCount()>0)
		  theApp.GraphsDataList.RemoveHead();
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 on Message Screen OK Button .               */
/**********************************************************************************/
void AddToAverageCommand(int ID)
{
	int length =2;
   unsigned char data1[2];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i=ID;
   data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
  
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
      if(ch==theApp.ACK)
		{
			int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);		
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         while(theApp.GraphsDataList.GetCount()>0)
		      theApp.GraphsDataList.RemoveHead();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
		}
      delete response;
   }
	CChildView::thisPtr->Invalidate();
}



void SetHornScanObjectMember(unsigned char * &data, int & length,CVgaDrawGraph * Graph)
{
    Graph->GraphData.GraphColour=*data++;length--;
    Graph->SetGraphRequestValue(Graph->GraphData.graph_type);
    for(int i=0;i<20;i++)
	   Graph->GraphData.SystemPressure[i]='\0';
    Graph->AlreadyPrinted=false;
    Graph->Lang_Index=0;//CChildView::Language_Index;
    Graph->No_Graph_String=" ";
    Graph->GraphCount++;
    Graph->GraphData.GraphNum =Graph->GraphCount;
    Graph->GraphData.DataLength=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
    for(short len=0;len<(Graph->GraphData.DataLength);len++)
    {
	   Graph->GraphData.graphdata[len]=(short)*data++;
	   length--;
    }
    Graph->Store_VData_HData(data,length);
    Graph->StoreDate_Time(data,length);
}

void SendCommandForHSCGraph(int ID)
{
      CVgaMenu * menu;
      menu=theApp.MenuPointer;
      CVgaMenuItem *object;
      POSITION pos1=menu->items.GetHeadPosition();
      unsigned char RequestType = (char)(ID);
		int length =2;
		unsigned char data1[2];
		data1[0]=(char)RequestType;
		data1[1]=(char)0;
		unsigned char * data = (unsigned char *) &data1[0];

		CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
		CHostCommand * response = app->SendUiHostCommand(request);
		if (response)
		{
			char ch=CHostCommand::AckNak();
			data = response->GetData();//Getting Data.
			 length = response->GetDataLength();//Getting Length.
			 if(ch==theApp.ACK)//If Ack.
			 {		//store graph data
			    while ((pos1)&&(length>0))
             {
                object= menu->items.GetNext(pos1);
	             if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
                {
                   CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                   int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                   if(ValueAfterParamID==ptr->GraphType)
                   {
                      ptr->GraphData.graph_type=ValueAfterParamID;
                      SetHornScanObjectMember(data,length,ptr);
			             ptr->HSCompareGraph =false;
			             theApp.GraphsDataList.AddTail(ptr);
                   }
                   else if(ValueAfterParamID>PMC_GRAPH)
                   {
                      ptr->GraphData.graph_type=ValueAfterParamID;
                      for(int i=0;i<20;i++)
		                    ptr->GraphData.SystemPressure[i]='\0';
	                   ptr->AlreadyPrinted=false;
	                   ptr->Lang_Index=0;//CChildView::Language_Index;
	                   ptr->No_Graph_String=" ";
                      ptr->GraphCount++;
	                   ptr->GraphData.GraphNum =ptr->GraphCount;
                   
                      for( i=0;i<20;i++)
		                  ptr->GraphData.GRAPHTITLE[i]='\0';
                      for( i=0;i<20;i++)
		                  ptr->GraphData.CycleCount[i]='\0';
                      ptr->No_Graph_String=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                      theApp.GraphsDataList.AddTail(ptr);
                   }
                   else
                   {
                      *data--;length++;
                      *data--;length++;
                   }
                 }
             }
			}
			else 
				CChildView::thisPtr->ErrorBeep();
			delete response;
		}
   CChildView::thisPtr->Invalidate();
}

/*************************************************************************/
/* This function will check for valid Scan Graph data and store it into  */
/* appropriate text file or gives a error message screen.				 */
/*************************************************************************/
void HandleSaveScanAButton(int ID)
{
	CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   int count=0;
   POSITION pos1=menu->items.GetHeadPosition();
   int KeypadType=0;
   CString No_Valid_Graph="";
	int length =2;
   bool ValidGraphPresent=false;
	unsigned char data1[2];
	data1[0]=(char)ID;
	data1[1]=(char)0;
	unsigned char * data = (unsigned char *) &data1[0];
	CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if (response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();//Getting Data.
		 length = response->GetDataLength();//Getting Length.
		 if(ch==theApp.ACK)//If Ack.
		 {	
		   while ((pos1)&&(length>0))
         {
             object= menu->items.GetNext(pos1);
	          if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
             {
               CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                if(ValueAfterParamID==ptr->GraphType)
                {
                   ValidGraphPresent =true;
                }
                else if(ValueAfterParamID>ptr->GraphType)
                {
                   No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                }
             }
			}	
      }
		delete response;
	}
	if(ValidGraphPresent)
	{
		CString Path;
      #ifndef _WIN32_WCE
			Path = "c:\\HornScanA.txt";
		#else
			Path = _T("Disk\\HornScanA.txt");
		#endif
			KeypadType=SaveScanA;
	
      CString s1="  ";
	   CFile f;
	   CFileException e;
	   if( !f.Open( Path, CFile::modeReadWrite , &e ) )
	   {
		   #ifdef _DEBUG
		   if(e.m_cause==CFileException::generic)
			   TRACE("\n !! GENERIC");
		   else if(e.m_cause==CFileException::badPath   )
			   TRACE("\n !! bad path");
		   else if(e.m_cause==CFileException::tooManyOpenFiles    )
			   TRACE("\n !! too many files open");
		   else if(e.m_cause==CFileException::fileNotFound )
			   TRACE("\n !! file not found");
		   else if(e.m_cause==CFileException::accessDenied       )
			   TRACE("\n !! access denied");
		   else if(e.m_cause==CFileException::diskFull      )
			   TRACE("\n !! disc full");
		   else if(e.m_cause==CFileException::invalidFile   )
			   TRACE("\n !! invalid file");
		   afxDump << "File could not be opened " << e.m_cause << "\n";
		   #endif
	   }
	   else
	   {
		   unsigned char data[15];
		   int k =f.Read(data,15);
		   if(k>10)
		   {		
			   unsigned char * data1 = data;
			   int len =f.GetLength();
			   s1 =CVgaMenuItem::GetString(data1,len);
			}
		   f.Close();
	   }
	   
	   unsigned char *s=0;
      CString *p=&s1;
	   OnKeypadScreen_flag=true;
      CChildView::thisPtr->BuildCompleteKeypadList(KeypadType,s,p,ID,0);
	   CChildView::thisPtr->Invalidate();
		
	}
	else
	{	
		CChildView::thisPtr->ShowMessageScreen(No_Valid_Graph);
   }
}

/*************************************************************************/
/* This function will check for valid Scan Graph data and store it into  */
/* appropriate text file or gives a error message screen.				 */
/*************************************************************************/
void HandleSaveScanBButton(int ID)
{
	CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   POSITION pos1=menu->items.GetHeadPosition();
   int KeypadType=0;
   CString No_Valid_Graph="";
	int length =2;
   bool ValidGraphPresent=false;
	unsigned char data1[2];
	data1[0]=(char)ID;
	data1[1]=(char)0;
	unsigned char * data = (unsigned char *) &data1[0];
	CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if (response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();//Getting Data.
		 length = response->GetDataLength();//Getting Length.
		 if(ch==theApp.ACK)//If Ack.
		 {	
		   while ((pos1)&&(length>0))
         {
             object= menu->items.GetNext(pos1);
	          if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
             {
                CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                if(ValueAfterParamID==ptr->GraphType)
                {
                   ValidGraphPresent =true;
                }
                else if(ValueAfterParamID>ptr->GraphType)
                {
                   No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                }
             }
			}	
      }
		delete response;
	}
	if(ValidGraphPresent)
	{
		CString Path;
      #ifndef _WIN32_WCE
			Path = "c:\\HornScanB.txt";
		#else
			Path = _T("Disk\\HornScanB.txt");
		#endif
			KeypadType=SaveScanB;
	
      CString s1="  ";
	   CFile f;
	   CFileException e;
	   if( !f.Open( Path, CFile::modeReadWrite , &e ) )
	   {
		   #ifdef _DEBUG
		   if(e.m_cause==CFileException::generic)
			   TRACE("\n !! GENERIC");
		   else if(e.m_cause==CFileException::badPath   )
			   TRACE("\n !! bad path");
		   else if(e.m_cause==CFileException::tooManyOpenFiles    )
			   TRACE("\n !! too many files open");
		   else if(e.m_cause==CFileException::fileNotFound )
			   TRACE("\n !! file not found");
		   else if(e.m_cause==CFileException::accessDenied       )
			   TRACE("\n !! access denied");
		   else if(e.m_cause==CFileException::diskFull      )
			   TRACE("\n !! disc full");
		   else if(e.m_cause==CFileException::invalidFile   )
			   TRACE("\n !! invalid file");
		   afxDump << "File could not be opened " << e.m_cause << "\n";
		   #endif
	   }
	   else
	   {
		   unsigned char data[15];
		   int k =f.Read(data,15);
		   if(k>10)
		   {		
			   unsigned char * data1 = data;
			   int len =f.GetLength();
			   s1 =CVgaMenuItem::GetString(data1,len);
			}
		   f.Close();
	   }
	   
	   unsigned char *s=0;
      CString *p=&s1;
	   OnKeypadScreen_flag=true;
      CChildView::thisPtr->BuildCompleteKeypadList(KeypadType,s,p,ID,0);
	   CChildView::thisPtr->Invalidate();
	}
	else
	{	
		CChildView::thisPtr->ShowMessageScreen(No_Valid_Graph);
   }
}

/*************************************************************************/
/* This function will check for valid Scan Graph data and store it into  */
/* appropriate text file or gives a error message screen.				 */
/*************************************************************************/
void HandleSaveScanCButton(int ID)
{
	CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   POSITION pos1=menu->items.GetHeadPosition();
   int KeypadType=0;
   CString No_Valid_Graph="";
	int length =2;
   bool ValidGraphPresent=false;
	unsigned char data1[2];
	data1[0]=(char)ID;
	data1[1]=(char)0;
	unsigned char * data = (unsigned char *) &data1[0];
	CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if (response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();//Getting Data.
		 length = response->GetDataLength();//Getting Length.
		 if(ch==theApp.ACK)//If Ack.
		 {	
		   while ((pos1)&&(length>0))
         {
             object= menu->items.GetNext(pos1);
	          if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
             {
               
                CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                if(ValueAfterParamID==ptr->GraphType)
                {
                   ValidGraphPresent =true;
                }
                else if(ValueAfterParamID>ptr->GraphType)
                {
                   No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                }
             }
			}	
      }
		delete response;
	}
	if(ValidGraphPresent)
	{
		CString Path;
      #ifndef _WIN32_WCE
			Path = "c:\\HornScanC.txt";
		#else
			Path = _T("Disk\\HornScanC.txt");
		#endif
			KeypadType=SaveScanC;
	
      CString s1="  ";
	   CFile f;
	   CFileException e;
	   if( !f.Open( Path, CFile::modeReadWrite , &e ) )
	   {
		   #ifdef _DEBUG
		   if(e.m_cause==CFileException::generic)
			   TRACE("\n !! GENERIC");
		   else if(e.m_cause==CFileException::badPath   )
			   TRACE("\n !! bad path");
		   else if(e.m_cause==CFileException::tooManyOpenFiles    )
			   TRACE("\n !! too many files open");
		   else if(e.m_cause==CFileException::fileNotFound )
			   TRACE("\n !! file not found");
		   else if(e.m_cause==CFileException::accessDenied       )
			   TRACE("\n !! access denied");
		   else if(e.m_cause==CFileException::diskFull      )
			   TRACE("\n !! disc full");
		   else if(e.m_cause==CFileException::invalidFile   )
			   TRACE("\n !! invalid file");
		   afxDump << "File could not be opened " << e.m_cause << "\n";
		   #endif
	   }
	   else
	   {
		   unsigned char data[15];
		   int k =f.Read(data,15);
		   if(k>10)
		   {	
			   unsigned char * data1 = data;
			   int len =f.GetLength();
			   s1 =CVgaMenuItem::GetString(data1,len);
			}
		   f.Close();
	   }
	   
	   unsigned char *s=0;
      CString *p=&s1;
	   OnKeypadScreen_flag=true;
      CChildView::thisPtr->BuildCompleteKeypadList(KeypadType,s,p,ID,0);
	   CChildView::thisPtr->Invalidate();
		
	}
	else
	{	
		CChildView::thisPtr->ShowMessageScreen(No_Valid_Graph);
   }
}


/********************************************************************************/
/* This function will prepare the scan graph list for Compare graph screen or   */
/* to print the compare graph according to the availability of the valid graphs.*/
/********************************************************************************/
void CompareGraph_and_Data(int ID)
{ 	CVgaMenu * menu;
   CString No_Valid_Graph="";
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   bool IsPrint=false;
   POSITION pos1=menu->items.GetHeadPosition();
   if(ID==1)
   {
	   IsPrint = true;
   }
   else
      IsPrint = false;
   CString s3,s2,s1;
   int TempCount=0;
	int NoOfGraphs=0;
	bool HS1_Present=false;
	bool HS2_Present=false;
	bool HS3_Present=false;
	bool HSCurrent_Present=false;

	CFile f1;
	CFileException e1;
	TCHAR* pFileName1;
	#ifndef _WIN32_WCE
	pFileName1 = _T("c:\\HornScanA.txt");
	#else
	pFileName1 = _T("Disk\\HornScanA.txt");
	#endif
	
	if( !f1.Open( pFileName1, CFile::modeReadWrite , &e1 ) )
	{
		#ifdef _DEBUG
		if(e1.m_cause==CFileException::generic)
			TRACE("\n !! GENERIC");
		else if(e1.m_cause==CFileException::badPath   )
			TRACE("\n !! bad path");
		else if(e1.m_cause==CFileException::tooManyOpenFiles    )
			TRACE("\n !! too many files open");
		else if(e1.m_cause==CFileException::fileNotFound )
			TRACE("\n !! file not found");
		else if(e1.m_cause==CFileException::accessDenied  )
			TRACE("\n !! access denied");
		else if(e1.m_cause==CFileException::diskFull      )
			TRACE("\n !! disc full");
		else if(e1.m_cause==CFileException::invalidFile   )
			TRACE("\n !! invalid file");
		afxDump << "File could not be opened " << e1.m_cause << "\n";
		#endif
	}
	else
	{
		unsigned char *c=new unsigned char[f1.GetLength()];
		unsigned char *c1=c;
		int k =f1.Read(c,f1.GetLength());
		if(k>20)
		{
			int length =f1.GetLength();
		   s1 =CVgaMenuItem::GetString(c,length);
		   while ((pos1))
          {
             object= menu->items.GetNext(pos1);
	          if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(TempCount==1))
             {
               
                CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(c,length,CORDLENGTH);
                if(ValueAfterParamID==ptr->GraphType)
                {
                   ptr->GraphData.graph_type=ValueAfterParamID;
                   SetHornScanObjectMember(c,length,ptr);
                   ptr->GraphData.GraphColour =Blue;
			          ptr->HSCompareGraph=true;
                   ptr->HS_CompareGraphNum =ONE;
			          if(IsPrint)
					     {	
				               CChildView::thisPtr->HSGraphPrintList.AddTail(ptr);
					     }
			           else
				            theApp.GraphsDataList.AddTail(ptr);
                   NoOfGraphs++;
			          CChildView::thisPtr->ScanA_Present=true;
                   CChildView::thisPtr->ScanA_On=true;
		          }
                else if(ValueAfterParamID>ptr->GraphType)
                {
                   No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                }
                TempCount++;
                break;
             }
             else
             {
               TempCount++;
             }
				
          }
		
		}
		f1.Close();
		delete []c1;
		
	}
	TempCount=0;
   pos1=menu->items.GetHeadPosition();
	CFile f;
	CFileException e;
	TCHAR* pFileName;
	#ifndef _WIN32_WCE
	pFileName = _T("c:\\HornScanB.txt");
	#else
	pFileName = _T("Disk\\HornScanB.txt");
	#endif
	
	if( !f.Open( pFileName, CFile::modeReadWrite , &e ) )
	{
		#ifdef _DEBUG
		if(e.m_cause==CFileException::generic)
			TRACE("\n !! GENERIC");
		else if(e.m_cause==CFileException::badPath   )
			TRACE("\n !! bad path");
		else if(e.m_cause==CFileException::tooManyOpenFiles    )
			TRACE("\n !! too many files open");
		else if(e.m_cause==CFileException::fileNotFound )
			TRACE("\n !! file not found");
		else if(e.m_cause==CFileException::accessDenied       )
			TRACE("\n !! access denied");
		else if(e.m_cause==CFileException::diskFull      )
			TRACE("\n !! disc full");
		else if(e.m_cause==CFileException::invalidFile   )
			TRACE("\n !! invalid file");
		afxDump << "File could not be opened " << e.m_cause << "\n";
		#endif
	}
	else
	{
		unsigned char *c2=new unsigned char[f.GetLength()];
		unsigned char *c1=c2;
		int j =f.Read(c2,f.GetLength());
		if(j>20)
		{
			int length =f.GetLength();
			s2 = CVgaMenuItem::GetString(c2,length);
		   while ((pos1))
          {
             object= menu->items.GetNext(pos1);
	          if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(TempCount==2))
             {
                CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(c2,length,CORDLENGTH);
                if(ValueAfterParamID==ptr->GraphType)
                {
                  ptr->GraphData.graph_type=ValueAfterParamID;
                   SetHornScanObjectMember(c2,length,ptr);
                   ptr->GraphData.GraphColour =Red;
			          ptr->HSCompareGraph=true;
                   ptr->HS_CompareGraphNum =2;
			          if(IsPrint)
					     {	
				               CChildView::thisPtr->HSGraphPrintList.AddTail(ptr);
					     }
			           else
				            theApp.GraphsDataList.AddTail(ptr);
                   NoOfGraphs++;
			          CChildView::thisPtr->ScanB_Present=true;
                   CChildView::thisPtr->ScanB_On=true;
		          }
                else if(ValueAfterParamID>ptr->GraphType)
                {
                   No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                }
                TempCount++;
             }
             else
             {
               TempCount++;
             }
			}
	   }
		f.Close();
		delete []c1;
	}
	
   TempCount=0;
   pos1=menu->items.GetHeadPosition();
	CFile f2;
	CFileException e2;
	TCHAR* pFileName2;
	#ifndef _WIN32_WCE
	pFileName2 = _T("c:\\HornScanC.txt");
	#else
	pFileName2 = _T("Disk\\HornScanC.txt");
	#endif
	
	if( !f2.Open( pFileName2, CFile::modeReadWrite , &e2 ) )
	{
		#ifdef _DEBUG
		if(e2.m_cause==CFileException::generic)
			TRACE("\n !! GENERIC");
		else if(e2.m_cause==CFileException::badPath   )
			TRACE("\n !! bad path");
		else if(e2.m_cause==CFileException::tooManyOpenFiles    )
			TRACE("\n !! too many files open");
		else if(e2.m_cause==CFileException::fileNotFound )
			TRACE("\n !! file not found");
		else if(e2.m_cause==CFileException::accessDenied       )
			TRACE("\n !! access denied");
		else if(e2.m_cause==CFileException::diskFull      )
			TRACE("\n !! disc full");
		else if(e2.m_cause==CFileException::invalidFile   )
			TRACE("\n !! invalid file");
		afxDump << "File could not be opened " << e2.m_cause << "\n";
		#endif
	}
	else
	{
		unsigned char *c1=new unsigned char[f2.GetLength()];
		unsigned char *c=c1;
		int i =f2.Read(c1,f2.GetLength());
		if(i>20)
		{
			int length =f2.GetLength();
		   s3 = CVgaMenuItem::GetString(c1,length);
		   while ((pos1))
          {
             object= menu->items.GetNext(pos1);
	         // while(length>0)
				 {
                if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(TempCount==3))
                {
                   CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                   int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(c1,length,CORDLENGTH);
                 
                   if(ValueAfterParamID==ptr->GraphType)
                   {
                      ptr->GraphData.graph_type=ValueAfterParamID;
                      SetHornScanObjectMember(c1,length,ptr);
                      ptr->GraphData.GraphColour =Green;
			             ptr->HSCompareGraph=true;
                      ptr->HS_CompareGraphNum =3;
			             if(IsPrint)
                      {	
				                  CChildView::thisPtr->HSGraphPrintList.AddTail(ptr);
					        }
			              else
				               theApp.GraphsDataList.AddTail(ptr);
                      NoOfGraphs++;
			             CChildView::thisPtr->ScanC_Present=true;
                      CChildView::thisPtr->ScanC_On=true;
		              }
                   else if(ValueAfterParamID>ptr->GraphType)
                   {
                      No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                   }
                   TempCount++;
                }
                else
                {
                   TempCount++;
                }
				}
          }
		
		}
		f2.Close();
		delete []c;
	}

	int length =2;
   TempCount=0;
   pos1=menu->items.GetHeadPosition();
	unsigned char data1[2];
	data1[0]=(char)HornScan_RequestValue;
	data1[1]=(char)0;
	unsigned char * data = (unsigned char *) &data1[0];
	bool ValidGraphPresent =false;
	CHostCommand * request = new CHostCommand(GetWeldData_FunID/*GetWeldResults_FunId*/, data, length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if (response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();//Getting Data.
		 length = response->GetDataLength();//Getting Length.
		 if(ch==theApp.ACK)//If Ack.
		 {	
			while ((pos1)&&(length>0))
          {
             object= menu->items.GetNext(pos1);
	          if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(TempCount==4))
             {
                CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                if(ValueAfterParamID==ptr->GraphType)
                {
                   ptr->GraphData.graph_type=ValueAfterParamID;
                   SetHornScanObjectMember(data,length,ptr);
                   ptr->GraphData.GraphColour =Black;
			          ptr->HSCompareGraph=true;
                   ptr->HS_CompareGraphNum =4;
			          if(IsPrint)
					     {
				               CChildView::thisPtr->HSGraphPrintList.AddTail(ptr);
					     }
			           else
				            theApp.GraphsDataList.AddTail(ptr);
                   NoOfGraphs++;
			          CChildView::thisPtr->CurrentScan_Present=true;
                   CChildView::thisPtr->CurrentScan_On=true;
		          }
                else if(ValueAfterParamID>ptr->GraphType)
                {
                   No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                }
                TempCount++;
             }
             else
             {
                TempCount++;
             }
				}
			}
		
		delete response;
	}
   if(NoOfGraphs==0 && !IsPrint)
   {
      CDC *pDC=CChildView::thisPtr->GetDc();
      /*Drawing Message Rectangle in specified color*/
      CVgaMenuItem::DrawRect(pDC, Black, MESSAGESCRN_BLACKRECT);
      CVgaMenuItem::DrawRect(pDC, Blue, MESSAGESCRNRECT);

	   /*Drawing Message Text*/
      CVgaMenuItem::DrawText(pDC, Bigfont,White , MESSAGESCRNRECT,No_Valid_Graph/*Str_NoValidGraph[CChildView::Language_Index]*/ ,true);
	   CChildView::thisPtr->ReleaseDc(pDC);	
	   CChildView::thisPtr->InitialiseTimer(ERROR_MESSAGE_TIMER,MESSAGESCRNTIME);
	   CChildView::thisPtr->DisableFlag=true;
   }

	if(!IsPrint)
	{
	
	}
	else
	{	switch(NoOfGraphs)
		{
			case 1:
				CChildView::thisPtr->PrintInfoList.AddTail(HSCGRAPHONE);
				break;
			case 2:
				CChildView::thisPtr->PrintInfoList.AddTail(HSCGRAPHTWO);
				break;
			case 3:
				CChildView::thisPtr->PrintInfoList.AddTail(HSCGRAPHTHREE);
				break;
			case 4:
				CChildView::thisPtr->PrintInfoList.AddTail(HSCGRAPHFOUR);
				break;
		}
		
	}
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}


/********************************************************************************/
/* This function will prepare Graph list to show Graphs on the screen	    	*/
/* according to "ON" Graphs Button on the screen.						        */	
/********************************************************************************/	
void EditGraphList(int ID,bool On_Off,int graphNum)
{
   if((!On_Off))
	{
		CTypedPtrList<CPtrList, CVgaDrawGraph *> HSGraphDataList;
	
		while(theApp.GraphsDataList.GetCount())
		{
			CVgaDrawGraph *obj =theApp.GraphsDataList.GetHead();
			if(obj->HS_CompareGraphNum != graphNum)
			{
				HSGraphDataList.AddTail(obj);
				theApp.GraphsDataList.RemoveHead();
			}
			else
				 theApp.GraphsDataList.RemoveHead();
		}
		POSITION pos = HSGraphDataList.GetHeadPosition();
		while(pos)
		{
			CVgaDrawGraph *obj = HSGraphDataList.GetNext(pos);
			theApp.GraphsDataList.AddTail(obj);
		}
	}
	else if(On_Off)
	{
		CVgaMenu * menu;
      CString No_Valid_Graph="";
      menu=theApp.MenuPointer;
      CVgaMenuItem *object;
      int TempCount=0;
      POSITION pos1=menu->items.GetHeadPosition();
      CString Path;
      bool GraphPresent =false;
		switch(graphNum)
		{
			case ONE:
			{
				#ifndef _WIN32_WCE
					Path = "c:\\HornScanA.txt";
				#else
					Path = _T("Disk\\HornScanA.txt");
				#endif
				if(CChildView::thisPtr->ScanA_Present)
            {
               GraphPresent =true;
               TempCount=1;
            }
		
			
			}
			break;
			case 2:
			{
				#ifndef _WIN32_WCE
					Path = "c:\\HornScanB.txt";
				#else
					Path = _T("Disk\\HornScanB.txt");
				#endif
				if(CChildView::thisPtr->ScanB_Present)
            {
					GraphPresent =true;
               TempCount=2;
            }
			}
			break;
			case 3:
			{
				#ifndef _WIN32_WCE
					Path = "c:\\HornScanC.txt";
				#else
					Path = _T("Disk\\HornScanC.txt");
				#endif
				if(CChildView::thisPtr->ScanC_Present)
            {
					GraphPresent =true;
               TempCount=3;
            }
			}
			break;
			case 4:
				{
					int length =2;
					unsigned char data1[2];
					data1[0]=(char)ID;
					data1[1]=(char)0;
					unsigned char * data = (unsigned char *) &data1[0];
					bool ValidGraphPresent =false;
					CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
					CHostCommand * response = app->SendUiHostCommand(request);
					if (response)
					{
						char ch=CHostCommand::AckNak();
						data = response->GetData();//Getting Data.
						 length = response->GetDataLength();//Getting Length.
						 if(ch==theApp.ACK)//If Ack.
						 {	
							 while ((pos1)&&(length>0))
                      {
                         object= menu->items.GetNext(pos1);
	                      if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(TempCount==4))
                         {
                            CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                            int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                            if(ValueAfterParamID==ptr->GraphType)
                            {
                               ptr->GraphData.graph_type=ValueAfterParamID;
                               SetHornScanObjectMember(data,length,ptr);
                               GraphPresent=false;
                               ptr->GraphData.GraphColour =Black;
			                      ptr->HSCompareGraph=true;
                               ptr->HS_CompareGraphNum =4;
				                   theApp.GraphsDataList.AddTail(ptr);
                            }
                            else if(ValueAfterParamID>ptr->GraphType)
                            {
                               No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                            }
                            TempCount++;
                         }
                         else
                         {
                            TempCount++;
                         }
                      }
						}
						delete response;
					}
				}
				break;
		}	
		if(GraphPresent)
		{
			CFile f;
			CFileException e;
			if( !f.Open( Path, CFile::modeReadWrite , &e ) )
			{
				#ifdef _DEBUG
				if(e.m_cause==CFileException::generic)
					TRACE("\n !! GENERIC");
				else if(e.m_cause==CFileException::badPath   )
					TRACE("\n !! bad path");
				else if(e.m_cause==CFileException::tooManyOpenFiles    )
					TRACE("\n !! too many files open");
				else if(e.m_cause==CFileException::fileNotFound )
					TRACE("\n !! file not found");
				else if(e.m_cause==CFileException::accessDenied       )
					TRACE("\n !! access denied");
				else if(e.m_cause==CFileException::diskFull      )
					TRACE("\n !! disc full");
				else if(e.m_cause==CFileException::invalidFile   )
					TRACE("\n !! invalid file");
				afxDump << "File could not be opened " << e.m_cause << "\n";
				#endif
			}
			else
			{
				unsigned char *Data=new unsigned char[f.GetLength()];
				unsigned char *Dummy = Data;
				int k =f.Read(Data,f.GetLength());
				if(k>20)
				{
					int length =f.GetLength();
               int Temp=0;
					
               CString HS_ID1 =CVgaMenuItem::GetString(Data,length);
				   while ((pos1))
                {
                   object= menu->items.GetNext(pos1);
                   if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(Temp==TempCount))
                   {
                      CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                      int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(Data,length,CORDLENGTH);
                      if(ValueAfterParamID==ptr->GraphType)
                      {
                         ptr->GraphData.graph_type=ValueAfterParamID;
                         SetHornScanObjectMember(Data,length,ptr);
                         ptr->GraphData.GraphColour =graphNum+1;
					          ptr->HSCompareGraph=true;
					          ptr->HS_CompareGraphNum = graphNum;
					          theApp.GraphsDataList.AddTail(ptr);
			             }
                      else if(ValueAfterParamID>ptr->GraphType)
                      {
                         No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                      }
                      Temp++;
                   }
                   else
                   {
                     Temp++;
                   }
					 }
				}
				delete []Dummy;
				f.Close();
			}
		}
	}
}


void HornScanA(int ID,CLocalChoice *ptr)
{
   if(CChildView::thisPtr->ScanA_Present) 
   {
      CChildView::thisPtr->ScanA_On =!CChildView::thisPtr->ScanA_On;
      EditGraphList(ID,CChildView::thisPtr->ScanA_On, 1);
   }
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

void HornScanB(int ID,CLocalChoice *ptr)
{
   if(CChildView::thisPtr->ScanB_Present)
	{
		CChildView::thisPtr->ScanB_On =!CChildView::thisPtr->ScanB_On;
		EditGraphList(ID,CChildView::thisPtr->ScanB_On, 2);
	}
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

void HornScanC(int ID,CLocalChoice *ptr)
{
   if(CChildView::thisPtr->ScanC_Present)
	{
		CChildView::thisPtr->ScanC_On =!CChildView::thisPtr->ScanC_On;
		EditGraphList(ID,CChildView::thisPtr->ScanC_On, 3);
	}
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

void CurrentHornScan(int ID,CLocalChoice *ptr)
{
   if(CChildView::thisPtr->CurrentScan_Present)
	{
		CChildView::thisPtr->CurrentScan_On = !CChildView::thisPtr->CurrentScan_On;
		EditGraphList(ID,CChildView::thisPtr->CurrentScan_On, 4);
	}
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}


void CopyScanData(int ID,CLocalChoice *ptr)
{
   if(CChildView::thisPtr->USBPresent())
   {
      CChildView::thisPtr->EnableWindow(false);
      CDC *pDC=CChildView::thisPtr->GetDc();
	   /*Drawing Message Rectangle in specified color*/
	   CVgaMenuItem::DrawRect(pDC, Black,MESSAGESCRN_BLACKRECT);
	   CVgaMenuItem::DrawRect(pDC, Blue, MESSAGESCRNRECT);

	   /*Drawing Message Text*/
	   CVgaMenuItem::DrawText(pDC, Bigfont,White , MESSAGESCRNRECT,ptr->ChoiceText1/*StrM5_35[CChildView::Language_Index]*/,true);
	   CChildView::thisPtr->ReleaseDc(pDC);
      CChildView::thisPtr->CreateFolder(true);
      CString	Path="\\USBDisk\\"+CChildView::thisPtr->PowerSupply;
	   CString TempPath =   Path +"\\"+"Horn Signature";
		if(!CChildView::thisPtr->IsFolderPresent(Path,"Horn Signature"))
		  CreateDirectory(TempPath,NULL);			      
	  
      TCHAR* pFileName1= _T("\\Disk\\HornScanA.txt");
      TCHAR* pFileName2= _T("\\Disk\\HornScanB.txt");
      TCHAR* pFileName3= _T("\\Disk\\HornScanC.txt");
      bool ScanAPresent=false,ScanBPresent=false,ScanCPresent=false;
      CFileException e1,e2,e3;
      CFile f1,f2,f3;
      if( f1.Open( pFileName1, CFile::modeReadWrite , &e1 ) )
      {
         
         ScanAPresent=true;
         f1.Close();
         CopyFile(pFileName1,(TempPath+"\\"+_T("HornScanA.txt")),false);
         
      }
      if( f2.Open( pFileName2, CFile::modeReadWrite , &e2 ) )
      {
         
         ScanBPresent=true;
         f2.Close();
         CopyFile(pFileName2,(TempPath+_T("\\HornScanB.txt")),false);
      }

      if( f3.Open( pFileName3, CFile::modeReadWrite , &e3 ) )
      {
         ScanCPresent=true;
         f3.Close();
         CopyFile(pFileName3,(TempPath+_T("\\HornScanC.txt")),false);
       }
      if((!ScanAPresent) && (!ScanBPresent) && (!ScanCPresent))
         CChildView::thisPtr->ShowMessageScreen(ptr->ChoiceText2);
      CChildView::thisPtr->EnableWindow(true);
      CChildView::thisPtr->Invalidate();

   }
   else
   {
      char TempArray[10];
	   CString Temp=_itoa(ID,TempArray,10);
      Temp=CVgaMenuItem ::LinearSearch(Temp);
      CChildView::thisPtr->ShowMessageScreen(Temp);
   }

}

void ExitAlarmMenu(int Address)
{
   CChildView::thisPtr->IsAlarmScreen =false;
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   if(theApp.menuName==CVgaBottomMenu::WeldResults_ID)
      CChildView::thisPtr->RunResultScreen=true;
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   if(CChildView::thisPtr->AlarmCount!=0)
      CChildView::thisPtr->AlarmUpdateRequired=true;
   else
      CChildView::thisPtr->AlarmUpdateRequired=false;
  /* CVgaMenuItem *AlarmPtr=0;
   CVgaMenu *menu=theApp.MenuPointer;
   POSITION pos = menu->items.GetTailPosition();
   while(pos)
	{
	   CVgaMenuItem *Object = menu->items.GetPrev(pos);
		if((Object->GetType()==/*CScreenObject* /CVgaMenu::VGA_ALARMBUTTON)&&(CChildView::thisPtr->AlarmCount!=0))
		{
			AlarmPtr=Object;
         AlarmPtr->SetText(CChildView::thisPtr->GetAlarmString(AlarmPtr));
         break;
		}
   }*/
	CChildView::thisPtr->Invalidate();
}


void SendAlarmMenuCommand(int ID)
{
   int length =2;
   unsigned char data1[2];
   union 
	   {
		   short i;
		   char c[2];
	   } u;
	u.i=ID;
  
   data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
  
	CHostCommand * request = new CHostCommand(GetAlarmMenuItems_FunId,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
     char ch=CHostCommand::AckNak();
	  data = response->GetData();
	  length = response->GetDataLength();
     if(ch==theApp.ACK)
	  {
		  CChildView::thisPtr->Invalidate();
	  }
	  else if(ch==theApp.NAK)
	  {
		 //printf("\n Nak");
		 theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
		 page_no=CChildView::thisPtr->menus.RemoveTail();	
       theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		 CChildView::thisPtr->ProcessNak(data,length,0,0);
	  }
	  delete response;
   }
   CChildView::thisPtr->Invalidate();
}


void AlarmErrorBeep(int Address)
{
	CHostCommand * request = new CHostCommand(ErrorBeep_FunId, 0, 0);
	CHostCommand * response = app->SendUiHostCommand(request);
	if (response)
		delete response;
}

void ProcessColorSetup(int Address)
{
   CChildView::ScreenSetupFlag=false;
   CChildView::thisPtr->Invalidate();
}


void AbortPrinting(int Address)
{ CChildView::AbortPrinting=true;
}

void PrintScanData(int Address)
{
	CVgaMenu * menu1;
	menu1=theApp.MenuPointer;

	ScanGraphsDataTemp_pos = tempScanGraphDataList.GetHeadPosition();
	CString PrinterPower_str;
	PrinterPower_str = tempScanGraphDataList.GetNext(ScanGraphsDataTemp_pos);

	if((PrintSetup.IsPrinting)&&(CChildView::thisPtr->PrinterPresent))
	{
      POSITION pos = menu1->items.GetHeadPosition();
		CVgaMenuItem * Object;
		CompareGraph_and_Data(1);
		while(pos)
		{
		   Object = menu1->items.GetNext(pos);
			if(Object->GetType()==CVgaMenu::VGATableObject)
			{
				CTable *TableObject =new CTable();
				CTable *pointer=(CTable*)Object;
				CDC *pDC = CChildView::thisPtr->GetDc();
				pointer->GetHornScanData_for_CompareData(pDC,true);
				CChildView::thisPtr->ReleaseDc(pDC);
				pointer->CopyVGATableData(TableObject);
				CChildView::thisPtr->TablePrintList.AddTail(TableObject);
				break;
			}
		}

		CChildView::thisPtr->WaitForPrintData.SetEvent();
	}
	else if(!CChildView::thisPtr->PrinterPresent)
				CChildView::thisPtr->ShowMessageScreen(PrinterPower_str);
}

void PrintScanGraph(int Address)
{	
   CVgaMenu * menu1;
	menu1=theApp.MenuPointer;
   ScanGraphsDataTemp_pos = tempScanGraphDataList.GetHeadPosition();
	CString PrinterPower_str;
	PrinterPower_str = tempScanGraphDataList.GetNext(ScanGraphsDataTemp_pos);

	if((PrintSetup.IsPrinting)&&(CChildView::thisPtr->PrinterPresent))
	{

		POSITION pos = menu1->items.GetHeadPosition();
		CVgaMenuItem * Object;
		CChildView::thisPtr->CopyHSCScreenGraphs();
		while(pos)
		{
		    Object = menu1->items.GetNext(pos);
			if(Object->GetType()==CVgaMenu::VGATableObject)
			{
				
				CTable *TableObject =new CTable();
				CTable *pointer=(CTable*)Object;
				CDC *pDC = CChildView::thisPtr->GetDc();
				pointer->GetHornScanData_for_CompareData(pDC,true);
				CChildView::thisPtr->ReleaseDc(pDC);
				pointer->CopyVGATableData(TableObject);
				if(theApp.GraphsDataList.GetCount())
					CChildView::thisPtr->TablePrintList.AddTail(TableObject);
				break;
			}
		}
      CChildView::thisPtr->WaitForPrintData.SetEvent();
	
	}
	else if(!CChildView::thisPtr->PrinterPresent)
				CChildView::thisPtr->ShowMessageScreen(PrinterPower_str);
}

void WeldHistoryPrintNow(int Address)
{	
	
   CVgaButton *ptr=(CVgaButton *)Address;
   int type = ptr->EnumID;		//12
   HistoryTemp_pos=NULL;
	GraphsTemp_pos=NULL;
	WeldTemp_pos=NULL;
	HornScanTemp_pos=NULL;
	ScanGraphsDataTemp_pos=NULL;
	ScreenGraphsTemp_pos=NULL;
	SetupTemp_pos=NULL;
	DUPSTemp_pos=NULL;
	SequenceTemp_pos=NULL;
    
	HistoryTemp_pos = tempHistoryList.GetHeadPosition();
	CString PrinterPower_str,StrM5_35;

	PrinterPower_str = tempHistoryList.GetNext(HistoryTemp_pos);

	StrM5_35 = tempHistoryList.GetNext(HistoryTemp_pos);

	if((PrintSetup.IsPrinting)&&(CChildView::thisPtr->PrinterPresent))
	{	if(CChildView::thisPtr->PrinterPresent)
			CChildView::thisPtr->ShowMessageScreen(StrM5_35);
			CChildView::thisPtr->BuildPrintList(type);
	}
	else if(!CChildView::thisPtr->PrinterPresent)
		CChildView::thisPtr->ShowMessageScreen(PrinterPower_str);
}

void WeldDataPrintNow(int Address)
{	
   CVgaButton *ptr=(CVgaButton *)Address;
	CString Addr = ptr->MenuName;
	int type = ptr->EnumID;
   HistoryTemp_pos=NULL;
	GraphsTemp_pos=NULL;
	WeldTemp_pos=NULL;
	HornScanTemp_pos=NULL;
	ScanGraphsDataTemp_pos=NULL;
	ScreenGraphsTemp_pos=NULL;
	SetupTemp_pos=NULL;
	DUPSTemp_pos=NULL;
	SequenceTemp_pos=NULL;
  
    WeldTemp_pos = tempWeldList.GetHeadPosition();
    CString PrinterPower_str;

    PrinterPower_str = tempWeldList.GetNext(WeldTemp_pos);
  	if((PrintSetup.IsPrinting)&&(CChildView::thisPtr->PrinterPresent))
				CChildView::thisPtr->BuildPrintList(type);
	else if(!CChildView::thisPtr->PrinterPresent)
			CChildView::thisPtr->ShowMessageScreen(PrinterPower_str);

}


void GraphsWeldNow(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   int type = ptr->EnumID;
	HistoryTemp_pos=NULL;
	GraphsTemp_pos=NULL;
	WeldTemp_pos=NULL;
	HornScanTemp_pos=NULL;
	ScanGraphsDataTemp_pos=NULL;
	ScreenGraphsTemp_pos=NULL;
	SetupTemp_pos=NULL;
	DUPSTemp_pos=NULL;
	SequenceTemp_pos=NULL;
   
   GraphsTemp_pos = tempGraphsList.GetHeadPosition();
	CString PrinterPower_str;
   PrinterPower_str = tempGraphsList.GetNext(GraphsTemp_pos);

   if((PrintSetup.IsPrinting)&&(CChildView::thisPtr->PrinterPresent))
		CChildView::thisPtr->BuildPrintList(type);
	else if(!CChildView::thisPtr->PrinterPresent)
		CChildView::thisPtr->ShowMessageScreen(PrinterPower_str);
}



void PrintScreenGraphs(int Address)
{ 
	HistoryTemp_pos=NULL;
	GraphsTemp_pos=NULL;
	WeldTemp_pos=NULL;
	HornScanTemp_pos=NULL;
	ScanGraphsDataTemp_pos=NULL;
	ScreenGraphsTemp_pos=NULL;
	SetupTemp_pos=NULL;
	DUPSTemp_pos=NULL;
	SequenceTemp_pos=NULL;


	ScreenGraphsTemp_pos = tempScreenGraphsList.GetHeadPosition();
	CString PrinterPower_str;
	PrinterPower_str = tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);

	if(!CChildView::thisPtr->PrinterPresent)
	{
		CChildView::thisPtr->ShowMessageScreen(PrinterPower_str);
	}
	else
	{
	   CChildView::thisPtr->BuildPrintList(SCREENGRAPHS);
	}
}


void HornScanPrint(int Address)
{ 
   HornScanTemp_pos = tempHornScanList.GetHeadPosition();
	CString PrinterPower_str;
	PrinterPower_str = tempHornScanList.GetNext(HornScanTemp_pos);

   if(CChildView::thisPtr->PrinterPresent)
		CChildView::thisPtr->BuildPrintList(HORNSCANID);
	else
		CChildView::thisPtr->ShowMessageScreen(PrinterPower_str);
}

void SetUpPrintNow(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
	SetupTemp_pos = tempSetupList.GetHeadPosition();
	CString PrinterPower_str,StrM5_35;
	PrinterPower_str = tempSetupList.GetNext(SetupTemp_pos);
	StrM5_35 = tempSetupList.GetNext(SetupTemp_pos);

   if((PrintSetup.IsPrinting)&&(CChildView::thisPtr->PrinterPresent))
	{	
      if(CChildView::thisPtr->PrinterPresent)
			CChildView::thisPtr->ShowMessageScreen(StrM5_35);
      CPrintDialog dlg(false);
		if(dlg.GetDefaults())
			CChildView::thisPtr->PrinterPresent = PRINTERONLINE;
		else
		{
			theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
         CChildView::thisPtr->ShowMessageScreen(CChildView::thisPtr->PrinterPower_str_Offline);
			CChildView::thisPtr->PrinterPresent = PRINTERNOTAVILABLE;
		}
	
	   DeleteDC(dlg.m_pd.hdc);
	   dlg.~CPrintDialog();
	   if((!CChildView::thisPtr->PrinterPresent)||(CChildView::thisPtr->AbortPrinting))
		   return;
		CChildView::thisPtr->BuildPrintList(SETUPID);
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
      CChildView::thisPtr->Invalidate();
	}
	else if(!CChildView::thisPtr->PrinterPresent)
   {
		theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
      CChildView::thisPtr->ShowMessageScreen(PrinterPower_str);
   }
      
}

void PrintDUPSSetup(int Address)
{  

   DUPSTemp_pos = tempDUPSList.GetHeadPosition();
	CString PrinterPower_str,StrM5_35;
	PrinterPower_str = tempDUPSList.GetNext(DUPSTemp_pos);
	StrM5_35 = tempDUPSList.GetNext(DUPSTemp_pos);

   if(!CChildView::thisPtr->PrinterPresent)
	{
	   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
      CChildView::thisPtr->ShowMessageScreen(PrinterPower_str);
	}
	else
	{	
      if(CChildView::thisPtr->PrinterPresent)
			CChildView::thisPtr->ShowMessageScreen(StrM5_35);
      CPrintDialog dlg(false);
		if(dlg.GetDefaults())
			CChildView::thisPtr->PrinterPresent = PRINTERONLINE;
		else
		{
			theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
         CChildView::thisPtr->ShowMessageScreen(CChildView::thisPtr->PrinterPower_str_Offline);
			CChildView::thisPtr->PrinterPresent = PRINTERNOTAVILABLE;
		}
	
	   DeleteDC(dlg.m_pd.hdc);
	   dlg.~CPrintDialog();
	   if((!CChildView::thisPtr->PrinterPresent)||(CChildView::thisPtr->AbortPrinting))
		   return;
		CChildView::thisPtr->BuildPrintList(DUPSPRESET);
	}
}

void SequencingPrintNow(int Address)
{
   SequenceTemp_pos = tempSequenceList.GetHeadPosition();
	CString PrinterPower_str,StrM5_35;
	PrinterPower_str = tempSequenceList.GetNext(SequenceTemp_pos);
	StrM5_35 = tempSequenceList.GetNext(SequenceTemp_pos);
   if((PrintSetup.IsPrinting)&&(CChildView::thisPtr->PrinterPresent)&&(CToggle::SequencingON))
	{	
      if(CChildView::thisPtr->PrinterPresent)
			CChildView::thisPtr->ShowMessageScreen(StrM5_35);
      CPrintDialog dlg(false);
		if(dlg.GetDefaults())
			CChildView::thisPtr->PrinterPresent = PRINTERONLINE;
		else
		{
			theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
         CChildView::thisPtr->ShowMessageScreen(CChildView::thisPtr->PrinterPower_str_Offline);
			CChildView::thisPtr->PrinterPresent = PRINTERNOTAVILABLE;
		}
	
	   DeleteDC(dlg.m_pd.hdc);
	   dlg.~CPrintDialog();
	   if((!CChildView::thisPtr->PrinterPresent)||(CChildView::thisPtr->AbortPrinting))
		   return;
		CChildView::thisPtr->BuildPrintList(PRINTSEQUENCE);
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);      
      CChildView::thisPtr->Invalidate();
	}
	else if(!CChildView::thisPtr->PrinterPresent)
   {
		theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
      CChildView::thisPtr->ShowMessageScreen(PrinterPower_str);
   }
	else if(!CToggle::SequencingON)
   {
		theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);      
      CChildView::thisPtr->Invalidate();
      CChildView::thisPtr->ErrorBeep();
   }
}

void GetPrinterStatus(int Address)
{
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
    CChildView::thisPtr->Invalidate();

}

void PowerPresetUpPressed(int Address)
{
   CChildView::thisPtr->LastSelectedPresetFrom=PSPresetSelected;
	if(CChildView::thisPtr->SelectedPowerPreset<=1)
	{
		CChildView::ErrorBeep();
		return ;
	}
	CChildView::thisPtr->SelectedPowerPreset=CChildView::thisPtr->SelectedPowerPreset-1;
   CChildView::thisPtr->Invalidate();
}

void PowerPresetDownPressed(int Address)
{
   CChildView::thisPtr->LastSelectedPresetFrom=PSPresetSelected;
	if(CChildView::thisPtr->SelectedPowerPreset==MaxPresetNum_InListBox)
	{
		CChildView::ErrorBeep();
		return ;
	}
	CChildView::thisPtr->SelectedPowerPreset=CChildView::thisPtr->SelectedPowerPreset+1;
   CChildView::thisPtr->Invalidate();
}

void USBPresetUpPressed(int Address)
{
   if(CChildView::thisPtr->SelectedUSBPreset<=1)
	{
		if(CChildView::thisPtr->SelectedUSBPreset==1)
			CChildView::thisPtr->LastSelectedPresetFrom=USBPresetSelected;
		CChildView::ErrorBeep();
		
		return ;
	}
	CChildView::thisPtr->LastSelectedPresetFrom=USBPresetSelected;
	CChildView::thisPtr->SelectedUSBPreset=CChildView::thisPtr->SelectedUSBPreset-1;
   CChildView::thisPtr->Invalidate();
}

void USBPresetDownPressed(int Address)
{
   CChildView::thisPtr->LastSelectedPresetFrom=USBPresetSelected;
	if(CChildView::thisPtr->SelectedUSBPreset==CChildView::thisPtr->TotalUSBPreset)
	{
		CChildView::ErrorBeep();
		return ;
	}
	CChildView::thisPtr->SelectedUSBPreset=CChildView::thisPtr->SelectedUSBPreset+1;
   CChildView::thisPtr->Invalidate();
}

bool CopyPresetToPowerSupply(CChildView *view)
{
	CString	pFileName=CChildView::thisPtr->LastUSBPresetFolder + "\\Preset"+ CChildView::thisPtr->USBPresetNames.GetAt(CChildView::thisPtr->USBPresetNames.FindIndex(CChildView::thisPtr->SelectedUSBPreset-1))+".log";
	CFile f;
	CFileException e;
	char ch1=0;
	if( f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
	{
		int  size= SIZEOFPRESETDATA;
		int ObjectSize = sizeof(bool)+ sizeof(char)+ size + sizeof(char);
		int StartingPointer =sizeof(bool)+ sizeof(char);//(SelectedUSBPreset-1)*ObjectSize+
		char ch[SIZEOFPRESETDATA+2] ;
		ch[0]=(char)CChildView::thisPtr->SelectedPowerPreset;
		f.SeekToBegin();
		int length =(f.GetLength());
		if(length> ObjectSize)
		{
			f.Close();
			CChildView::ErrorBeep();
			return false;
		}
		{
			f.Seek(StartingPointer, CFile::begin );
			int t=f.Read(&ch[1],length-3);
		
		}
		
		//length = SIZEOFPRESETDATA+1;//length of pointer to be send to 332.
		length = length-2;
		f.Close();
		unsigned char * data = (unsigned char *) &ch[0];
		CHostCommand * request = new CHostCommand(DownLoadPresetFun_Id, data,length);
		CHostCommand * response = app->SendUiHostCommand(request);
		if (response)
		{
			ch1=CHostCommand::AckNak();
			data = response->GetData();//Getting Data.
			length = response->GetDataLength();//Getting Length.
			if(ch1==theApp.ACK)//If Ack.
			{
				CString Temp2 = CChildView::thisPtr->PSPresetText[CChildView::thisPtr->SelectedPowerPreset-1];
				if(Temp2.GetLength()>2)
				Temp2.Delete(2,(CChildView::thisPtr->PSPresetText[CChildView::thisPtr->SelectedPowerPreset-1]).GetLength()-2);
				CChildView::thisPtr->PSPresetText[CChildView::thisPtr->SelectedPowerPreset-1]= Temp2+" "+ CChildView::thisPtr->USBPresetNames.GetAt(CChildView::thisPtr->USBPresetNames.FindIndex(CChildView::thisPtr->SelectedUSBPreset-1));
				delete response;
			}
			else
			{
				delete response;
			
			}
		
		}
		
	}
	else
		CChildView::ErrorBeep();
	if(ch1==theApp.ACK)
		return true;
	return false;
}

bool OverwritePreset(int PSPreset, int USBPreset,CChildView *view,int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   CVgaMenu *menu;
	if(USBPreset)
	{
      for(int i =0;i<CChildView::thisPtr->TotalUSBPreset;i++)
		{
			CString S=CChildView::thisPtr->PSPresetText[PSPreset-1];
         S.Delete(0,3);

         CString USBPressetName=CChildView::thisPtr->USBPresetNames.GetAt(CChildView::thisPtr->USBPresetNames.FindIndex(i));
         USBPressetName.TrimLeft();
         USBPressetName.TrimRight();

         if(S==USBPressetName)
			{
            CChildView::thisPtr->OverWritePresetNum=i+1;
			   CChildView::thisPtr->OverWritePreset=true;
				CChildView::thisPtr->CopyPresetNum = PSPreset;
            if(ptr->MenuNak!="")
            {
               if (theApp.menus.Lookup(ptr->MenuNak, menu))
		         {
			         view->menupointers.AddTail(theApp.MenuPointer);
                  view->menusname.AddTail(theApp.menuName);
                  view->menus.AddTail(page_no);
                  page_no=1;
                  theApp.menuName = ptr->MenuNak;
                  theApp.MenuPointer=menu;
                  CChildView::thisPtr->ModifyObjectList(menu);
                  char buf[5];
				      sprintf(buf,"%d ",CChildView::thisPtr->OverWritePresetNum);
                  CVgaMenuItem * Object;
                  POSITION pos = menu->items.GetHeadPosition();
                  while(pos)
                  {
                     Object = menu->items.GetNext(pos);
                     if(Object->GetType() == CVgaMenu::VGAMsgScrnObject)
                     {
                        CMsgScreen *obj=(CMsgScreen*)Object;
                        obj->MsgLine1="";
                        obj->MsgLine3="";
                        obj->MsgLine2=obj->text + " "+ buf + CChildView::thisPtr->USBPresetNames.GetAt(CChildView::thisPtr->USBPresetNames.FindIndex(i))+" ?";
                        break;
                     }
                  }
               }		
	         }
            CChildView::thisPtr->Invalidate();
				return true;
			}
		}
		return false;
	}
	else
	{
		if(CChildView::thisPtr->PSPresetText[PSPreset-1].GetLength()>2)
		{
         CChildView::thisPtr->OverWritePresetNum++;
			   CChildView::thisPtr->OverWritePSPreset=true;
				CChildView::thisPtr->OverWritePreset=true;
				CChildView::thisPtr->CopyPresetNum = PSPreset;
            if(ptr->MenuNak!="")
            {
               if (theApp.menus.Lookup(ptr->MenuNak, menu))
		         {
			         view->menupointers.AddTail(theApp.MenuPointer);
                  view->menusname.AddTail(theApp.menuName);
                  view->menus.AddTail(page_no);
                  page_no=1;
                  theApp.menuName = ptr->MenuNak;
                  theApp.MenuPointer=menu;
                  CChildView::thisPtr->ModifyObjectList(menu);
                  CVgaMenuItem * Object;
                  POSITION pos = menu->items.GetHeadPosition();
                  while(pos)
                  {
                     Object = menu->items.GetNext(pos);
                     if(Object->GetType() == CVgaMenu::VGAMsgScrnObject)
                     {
                        CMsgScreen *obj=(CMsgScreen*)Object;
                        obj->MsgLine1="";
                        obj->MsgLine3="";
                        obj->MsgLine2=obj->text + CChildView::thisPtr->PSPresetText[PSPreset-1]+" ?";
                        break;
                     }
                  }
               }		
	         }
            CChildView::thisPtr->Invalidate();
				return true;
		}
		return false;
	}
}

void WriteDataToUSBFile(CChildView *view,unsigned char * &data, int & length)
{
	/*Getting Preset name from the data.*/
	unsigned char * ch ;
	unsigned char *CH = data;
	CString S;
	if(length==SIZEOFPRESETDATA)
		CH +=DupsPresetNameStrPos;
	else
		CH +=PresetNameStrPos;

	ch=CH;
	if(*ch ==0)
	S += ' ';
	while(*ch !=0)
		S +=(char) *ch++;


	CChildView::thisPtr->PSName =view->PowerSupply;
	CString	pFileName=CChildView::LastUSBPresetFolder + "\\Preset"+S+".log";
	CFile f;
	CFileException e;
	if(f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
	{
		int Temp =f.GetLength();
		if(Temp>length)
		{
			f.Close();
			CFile::Remove(pFileName);
		}
		else
			f.Close();
	}
	
	if( !f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
	{
		#ifdef _DEBUG
		if(e.m_cause==CFileException::generic)
			TRACE("\n !! GENERIC");
		else if(e.m_cause==CFileException::badPath)
			TRACE("\n !! bad path");
		else if(e.m_cause==CFileException::tooManyOpenFiles )
			TRACE("\n !! too many files open");
		else if(e.m_cause==CFileException::fileNotFound )
			TRACE("\n !! file not found");
		else if(e.m_cause==CFileException::accessDenied )
			TRACE("\n !! access denied");
		else if(e.m_cause==CFileException::diskFull)
			TRACE("\n !! disc full");
		else if(e.m_cause==CFileException::invalidFile)
			TRACE("\n !! invalid file");
		afxDump << "File could not be opened " << e.m_cause << "\n";
		#endif
	}
	else
	{	
		char Comma =',';
		f.Write(&CChildView::metric,sizeof(bool));
		f.Write(&Comma,sizeof(char));
		char dataarray[SIZEOFPRESETDATA+1];
		int i=0;
		while(length>0)
		{
			dataarray[i] =*data++;
			length--;
			i++;
		}
		f.Write(&dataarray,i);
		f.Write(&Comma,sizeof(char));
		f.Close();
	}

}

void CopyPresetToUSB(CChildView *view,int PresetNumber)
{
	if((PresetNumber<1)||((CChildView::thisPtr->PSPresetText[PresetNumber-1]).GetLength() < 4))
	{
		CChildView::ErrorBeep();
		return;
	}
	else
	{
		/*Send Command To get Preset Data.*/
		int length = ONE;
		unsigned char * data = (unsigned char *) &PresetNumber;
		CHostCommand * request = new CHostCommand(UpLoadPreset_FunId, data,length);
		CHostCommand * response = app->SendUiHostCommand(request);
		if (response)
		{
			char ch=CHostCommand::AckNak();
			data = response->GetData();//Getting Data.
			length = response->GetDataLength();//Getting Length.
			if(ch==theApp.ACK)//If Ack.
			{
            WriteDataToUSBFile(view,data,length);
			}
			delete response;

		}
	}

}

void CopyPowerPreset(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   char TempArray[10];
	CString StrM5_35=_itoa(ptr->EnumID,TempArray,10);
   StrM5_35=CVgaMenuItem ::LinearSearch(StrM5_35);
   CChildView *view=CChildView::thisPtr;
   if((CChildView::thisPtr->SelectedPowerPreset>0) )//&& (SelectedUSBPreset))
	{
      CString S=CChildView::thisPtr->PSPresetText[CChildView::thisPtr->SelectedPowerPreset-1];
		if(S.GetLength()>3)
		{
         if(!OverwritePreset(CChildView::thisPtr->SelectedPowerPreset, 1,view,Address))
			{
				view->ShowMessageScreen(StrM5_35);
				CopyPresetToUSB(view,CChildView::thisPtr->SelectedPowerPreset);
            CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
            CChildView::thisPtr->Invalidate();
			}
		}
		else
			CChildView::ErrorBeep();
		return ;
	}
	else if(!CChildView::thisPtr->TotalUSBPreset)
	{
      CString S =(CChildView::thisPtr->PSPresetText[CChildView::thisPtr->SelectedPowerPreset-1]);
		S.Delete(0,3);
		if(S.GetLength()>0)
		{	
         CopyPresetToUSB(view,CChildView::thisPtr->SelectedPowerPreset);
			CChildView::thisPtr->SelectedUSBPreset=1;
			CChildView::thisPtr->USBPresetNames.AddTail(S);
			CChildView::thisPtr->TotalUSBPreset++;
			CChildView::thisPtr->Invalidate();
		}
		else
			CChildView::thisPtr->ErrorBeep();
	}
	else
		CChildView::thisPtr->ErrorBeep();
}

void OverWriteOkButton(int Address)
{
   CChildView *view=CChildView::thisPtr;
   CVgaButton *ptr=(CVgaButton *)Address;
   char TempArray[10];
	CString StrM5_35=_itoa(ptr->EnumID,TempArray,10);
   StrM5_35=CVgaMenuItem ::LinearSearch(StrM5_35);
   if(CChildView::thisPtr->OverWritePSPreset)
	{
	
		CopyPresetToPowerSupply(view);
		CChildView::thisPtr->OverWritePreset=false;
		CChildView::thisPtr->OverWritePSPreset=false;
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
		view->Invalidate();
		return ;
	}

	view->ShowMessageScreen(StrM5_35);
	CopyPresetToUSB(view,CChildView::thisPtr->CopyPresetNum);
	
	if(CChildView::thisPtr->CopyPresetNum==MaxPresetNum_InListBox)
		CChildView::thisPtr->CopyPresetNum++;
	if(CChildView::thisPtr->CopyAllFlag)
	{
		int temp = CChildView::thisPtr->CopyPresetNum+1;
		for(int Num =temp;Num <=MaxPresetNum_InListBox;Num++)
		{

			if((CChildView::thisPtr->PSPresetText[Num-1]).GetLength() > 2)
			{	
				if(!OverwritePreset(Num, 1,view,Address))
					CopyPresetToUSB(view,Num);
				else
					break;
			}
			CChildView::thisPtr->CopyPresetNum++;
		}
	}
	if(CChildView::thisPtr->CopyPresetNum==MaxPresetNum_InListBox)
		CChildView::thisPtr->CopyPresetNum++;
	if(!CChildView::thisPtr->CopyAllFlag  ||CChildView::thisPtr->CopyPresetNum >MaxPresetNum_InListBox )//||OverwritePreset(CopyPresetNum, 1,view))
	{
		CChildView::thisPtr->CopyPresetNum=0;
		CChildView::thisPtr->CopyAllFlag=false;
		CChildView::thisPtr->OverWritePreset=false;
	}
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);      
   CChildView::thisPtr->Invalidate();
}

void OverWriteCancelButton(int Address)
{
   CChildView *view=CChildView::thisPtr;
   CVgaButton *ptr=(CVgaButton *)Address;
   char TempArray[10];
	CString StrM5_35=_itoa(ptr->EnumID,TempArray,10);
   StrM5_35=CVgaMenuItem ::LinearSearch(StrM5_35);
   if(CChildView::thisPtr->OverWritePSPreset)
	{
		CChildView::thisPtr->OverWritePreset=false;
		CChildView::thisPtr->OverWritePSPreset=false;
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
		CChildView::thisPtr->Invalidate();
		return ;
	}
    CChildView::thisPtr->ShowMessageScreen(StrM5_35);
	if(CChildView::thisPtr->CopyAllFlag)
	{
		int temp = CChildView::thisPtr->CopyPresetNum+1;
		for(int Num =temp;Num <=MaxPresetNum_InListBox;Num++)
		{

			if((CChildView::thisPtr->PSPresetText[Num-1]).GetLength() > 2)
			{	
				if(!OverwritePreset(Num, 1,view,Address))
					CopyPresetToUSB(view,Num);
				else
					break;
			}
			CChildView::thisPtr->CopyPresetNum++;
		}
	}
	if(CChildView::thisPtr->CopyPresetNum==MaxPresetNum_InListBox)
		CChildView::thisPtr->CopyPresetNum++;
	if(!CChildView::thisPtr->CopyAllFlag  ||(CChildView::thisPtr->CopyPresetNum) >MaxPresetNum_InListBox )//||OverwritePreset(CopyPresetNum, 1,view))
	{
		CChildView::thisPtr->CopyPresetNum=0;
		CChildView::thisPtr->CopyAllFlag=false;
		CChildView::thisPtr->OverWritePreset=false;
	}
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);      
   CChildView::thisPtr->Invalidate();
}

void ProcessUSBMemoryScreen(int Address)
{
   CChildView::thisPtr->SelectedPowerPreset=CChildView::thisPtr->CurrentPresetNum;
   CChildView::thisPtr->LastSelectedPresetFrom=PSPresetSelected;
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

void CopyAllPresetToUSB(CChildView *view,int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   char TempArray[10];
	CString StrM5_35=_itoa(ptr->EnumID,TempArray,10);
   StrM5_35=CVgaMenuItem ::LinearSearch(StrM5_35);
	CChildView::thisPtr->ShowMessageScreen(StrM5_35);
	CChildView::DisableFlag=true;
	CChildView::InitialiseTimer(ERROR_MESSAGE_TIMER,200);

	bool Found =false;
	view->CopyAllFlag = true;
	for(int Num =0;Num <MaxPresetNum_InListBox;Num++)
	{
		if((CChildView::PSPresetText[Num]).GetLength() > 2)
		{
			view->CopyPresetNum++;
			if(!OverwritePreset(Num+1, 1,view,Address))
			{	
				Found =true;
				/*Send Command To get Preset Data.*/
				int PresetNumber =Num+1;
				int length = ONE;//length of pointer to be send to 332.
				unsigned char * data = (unsigned char *) &PresetNumber;
				CHostCommand * request = new CHostCommand(UpLoadPreset_FunId, data,length);
				CHostCommand * response = app->SendUiHostCommand(request);
				if (response)
				{
					char ch=CHostCommand::AckNak();
					data = response->GetData();//Getting Data.
					length = response->GetDataLength();//Getting Length.
					if(ch==theApp.ACK)//If Ack.
					{
						WriteDataToUSBFile(view,data,length);
					}
					delete response;
				}
			}
			else 
			{
				view->Invalidate();
				return;
			}
		}
	}
	if(Found)
   {
	   view->ModifyObjectList(theApp.MenuPointer);
      view->Invalidate();
   }
}

void CopyAllPowerPreset(int Address)
{
   bool Found =false;
	for(int Num =0;Num <MaxPresetNum_InListBox;Num++)
	{
		if((CChildView::thisPtr->PSPresetText[Num]).GetLength() > 2)
		Found=true;
	}
	if(Found)
		CopyAllPresetToUSB(CChildView::thisPtr,Address);
	else
		CChildView::ErrorBeep();
}

void DeleteSelectedUSBPreset(CChildView *view,int Address)
{
	CVgaButton *ptr=(CVgaButton *)Address;
   char TempArray[10];
	CString StrM5_35=_itoa(ptr->EnumID,TempArray,10);
   StrM5_35=CVgaMenuItem ::LinearSearch(StrM5_35);
   /* Showing message screen.*/
	CDC *pDC=view->GetDc();

   view->ShowMessageScreen(StrM5_35);
	CChildView::DisableFlag=true;
	CChildView::InitialiseTimer(ERROR_MESSAGE_TIMER,200);
 
   CChildView::PSName =view->PowerSupply;
   CString	pFileName=CChildView::LastUSBPresetFolder + "\\Preset"+ CChildView::USBPresetNames.GetAt(CChildView::USBPresetNames.FindIndex(CChildView::SelectedUSBPreset-1))+".log";

	CFile f;
	CFileException e;
	bool FileFound=false;
	if( f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
	{
		FileFound=true;
		f.Close();		
	}
	if(FileFound)
		CFile::Remove(pFileName);
	else
		CChildView::ErrorBeep();
}

void DeleteUSBPreset(int Address)
{
   if(CChildView::thisPtr->SelectedUSBPreset>0)
	{
		DeleteSelectedUSBPreset(CChildView::thisPtr,Address);
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
      int Temp=	CChildView::thisPtr->SelectedUSBPreset;
		int Temp1 =CChildView::thisPtr->SelectedPowerPreset;
      if(CChildView::thisPtr->USBPresetNames.GetCount()>=Temp)
      {
         CChildView::thisPtr->SelectedUSBPreset=Temp;
      }
		else if(CChildView::thisPtr->USBPresetNames.GetCount()>0)
      {
         CChildView::thisPtr->SelectedUSBPreset=1;
      }
      else if(CChildView::thisPtr->USBPresetNames.GetCount()==0)
         CChildView::thisPtr->SelectedUSBPreset=0;
		CChildView::thisPtr->SelectedPowerPreset=Temp1;
      CChildView::thisPtr->Invalidate();
	}  
	else
		CChildView::ErrorBeep();
}

void CopyUSBPreset(int Address)
{
   CVgaMenu *menu1=theApp.MenuPointer;
   if((CChildView::thisPtr->SelectedPowerPreset>0) && (CChildView::thisPtr->SelectedUSBPreset))
	{
	
		if(!OverwritePreset(CChildView::thisPtr->SelectedPowerPreset, 0,CChildView::thisPtr,Address))
		{
			if(CopyPresetToPowerSupply(CChildView::thisPtr))
         {
            CVgaMenuItem * Object;
            POSITION pos = menu1->items.GetHeadPosition();
            while(pos)
            {
               Object = menu1->items.GetNext(pos);
               if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
               {
                  CListBoxObject *obj=(CListBoxObject*)Object;
                  for(int i =0;i<obj->MaxPreset;i++)
				         obj->ListBoxText[i]=CChildView::thisPtr->PSPresetText[i];
                  break;
               }
            }
            CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
            CChildView::thisPtr->Invalidate();
         }
			else
				CChildView::thisPtr->Invalidate();
		}
	}
	else
		CChildView::ErrorBeep();
}

/******************************************************************************/
/* This Function will Browes the USB Memory and prepare the USB memory screen.*/
/******************************************************************************/
void BrowesUSBFolder(CChildView *view,int Address)
{
	CVgaButton *ptr=(CVgaButton *)Address;
   CVgaMenu *menu;
   menu=theApp.MenuPointer;
   WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CString argv=_T("USBDisk\\");
	CString DirSpec;  
   DirSpec=argv+_T("\\*");
   hFind = FindFirstFile(DirSpec, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		FindClose(hFind);
		return ;
	} 
	else 
   {
	 if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&(view->ValidFolderName(FindFileData.cFileName,FOLDERHIERARCHYONE)))
	  {
		 FindClose(hFind);
		view->PrepareUSBList("USBDisk",USBPRESETFOLDER,ptr->EnumID);
      view->Invalidate();
		return ;
	  }
      while (FindNextFile(hFind, &FindFileData) != 0) 
      {
         
	if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&(view->ValidFolderName(FindFileData.cFileName,FOLDERHIERARCHYONE)))
	  {
			FindClose(hFind);
			view->PrepareUSBList("USBDisk",USBPRESETFOLDER,ptr->EnumID);
         view->Invalidate();
			return ;
		}
     }
   }

}

void BowseUSBFolder(int Address)
{
   BrowesUSBFolder(CChildView::thisPtr,Address);
}

void ViewPowerPreset(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   CVgaMenu *menu=theApp.MenuPointer;
   if(CChildView::thisPtr->SelectedUSBPreset>=1)
		CChildView::thisPtr->USBSelectedPresetName=CChildView::thisPtr->USBPresetNames.GetAt(CChildView::thisPtr->USBPresetNames.FindIndex(CChildView::thisPtr->SelectedUSBPreset-1));
   
   CVgaMenuItem * Object;
   CString Menuname,MenuNak;
   POSITION pos = menu->items.GetHeadPosition();
   while(pos)
   {
      Object = menu->items.GetNext(pos);
      if(Object->GetType() == CVgaMenu::VGAMsgScrnObject)
      {
         CMsgScreen * MsgScreen=(CMsgScreen *)Object;
         Menuname=MsgScreen->submenu;
         MenuNak=MsgScreen->menunak;
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         break;
      }
   }
   switch(CChildView::thisPtr->LastSelectedPresetFrom)
	{
		case PSPresetSelected:
		{
			if((CChildView::thisPtr->PSPresetText[CChildView::thisPtr->SelectedPowerPreset-1]).GetLength()>3)
			{
				if (theApp.menus.Lookup(Menuname, menu))
            {
               CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
               CChildView::thisPtr->menusname.AddTail(theApp.menuName);
               CChildView::thisPtr->menus.AddTail(page_no);
               page_no=1;
               theApp.menuName = Menuname;
               theApp.MenuPointer=menu;
               CChildView::thisPtr->ModifyObjectList(menu);
            }
			}
			else
			{
				CChildView::ErrorBeep();
				return;
			}
		}
		break;
		case USBPresetSelected:
		{
			if(CChildView::thisPtr->SelectedUSBPreset>=1)
			{
				if (theApp.menus.Lookup(MenuNak, menu))
            {
               CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
               CChildView::thisPtr->menusname.AddTail(theApp.menuName);
               CChildView::thisPtr->menus.AddTail(page_no);
               page_no=1;
               theApp.menuName = MenuNak;
               theApp.MenuPointer=menu;
               CChildView::thisPtr->ModifyObjectList(menu);
            }
			}
			else
			{
				CChildView::ErrorBeep();
				return;
			}			
		}
		break;
	}
   CChildView::thisPtr->Invalidate();
}

void USBRecall(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   if(!CChildView::ISUSBPresent)
	{
		CChildView::ErrorBeep();
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
      CChildView::thisPtr->Invalidate();
		return ;
	}				
	/* For USB */
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CString argv=_T("USBDisk\\");
	CString DirSpec;  
	DirSpec=argv+_T("\\*");
	hFind = FindFirstFile(DirSpec, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		FindClose(hFind);
		return ;
	} 
	else 
	{
		if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&(CChildView::thisPtr->ValidFolderName(FindFileData.cFileName,FOLDERHIERARCHYONE)))
		{
			FindClose(hFind);
			CChildView::thisPtr->PrepareUSBList("USBDisk",FOLDERHIERARCHYONE,ptr->EnumID);
			CChildView::thisPtr->Invalidate();
			return ;
		}
		while (FindNextFile(hFind, &FindFileData) != 0) 
		{

			if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&(CChildView::thisPtr->ValidFolderName(FindFileData.cFileName,FOLDERHIERARCHYONE)))
			{
				FindClose(hFind);
				CChildView::thisPtr->PrepareUSBList("USBDisk",FOLDERHIERARCHYONE,ptr->EnumID);
				CChildView::thisPtr->Invalidate();
				return ;
			}
		}
	}
	/*USB code ends here*/
	return ;
}

void ExitHistoryMenu(int Address)
{
   TRY
   {
      CVgaButton *ptr=(CVgaButton *)Address;
      if(CWeldingHistory::thisHisPtr->WeldHistoryList.GetCount())
	   {
         while(CWeldingHistory::thisHisPtr->WeldHistoryList.GetCount()>0)
	         delete CWeldingHistory::thisHisPtr->WeldHistoryList.RemoveHead();
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
         CChildView::thisPtr->Invalidate();
		   return ;
	   }
 
	   if(!CChildView::ISUSBPresent)
	   {
         CVgaMenu * menu;
         if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
		   {
            theApp.menuName=CVgaBottomMenu::mainMenuID;
            theApp.MenuPointer=menu;
            CChildView::thisPtr->ModifyObjectList(menu); 
            CChildView::thisPtr->Invalidate();
         }
		   return ;
	   }
	   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
	   CChildView::thisPtr->PrepareUSBList(CUSBFolder::LastFilePath,FOLDERHIERARCHYTHREE,ptr->EnumID);
	   CChildView::thisPtr->Invalidate();
   }
   CATCH_ALL(E)
   {
      TCHAR  szCause[255];
      E->GetErrorMessage(szCause, 255);
      CString x;
      x = _T("The error: ");
      x += szCause;
      AfxMsgBox(x);
      CVgaMenu * menu;
      if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
		{
         theApp.menuName=CVgaBottomMenu::mainMenuID;
         theApp.MenuPointer=menu;
         CChildView::thisPtr->ModifyObjectList(menu); 
         CChildView::thisPtr->Invalidate();
      }
   }
   END_CATCH_ALL
}

void HandleFolderHierarchyExit(int Address)
{
   CVgaMenu *menu;
   menu=theApp.MenuPointer;
   bool flag=false;
   int Fun_Id,TitleID;
   POSITION pos =menu->items.GetHeadPosition();
	CVgaMenuItem *Obj;// =view->menuEntryList.GetNext(pos);
	while(pos)
	{
		Obj =menu->items.GetNext(pos);
		if(Obj->GetType()==CVgaMenu::SUBMENU)
		{
			CUSBFolder *ptr=(CUSBFolder *)Obj;
         flag=true;
         Fun_Id=ptr->Fun_Id;
         TitleID=ptr->TitleID;
			break;
		}
	}
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   if((Fun_Id >FOLDERHIERARCHYONE)&&(Fun_Id<=FOLDERHIERARCHYFOUR))
   {
	   if(flag == true)
	   {
         CUSBFolder *object =(CUSBFolder*)Obj;
		   CString PreviousPath = object->Path;
		   int x=0;
		   while(x!=2)
		   {
		   if(PreviousPath.Right(1)==("\\"))
			   x++;
		   PreviousPath.Delete(PreviousPath.GetLength()-1,1);
		   }
		   CChildView::thisPtr->PrepareUSBList(PreviousPath,Fun_Id-1,TitleID);
         CChildView::thisPtr->Invalidate();
	   }
	   else
	   {
         if(!CChildView::ISUSBPresent)
	      {
            CVgaMenu * menu;
            if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
		      {
               theApp.menuName=CVgaBottomMenu::mainMenuID;
               theApp.MenuPointer=menu;
               CChildView::thisPtr->ModifyObjectList(menu); 
               CChildView::thisPtr->Invalidate();
               return;
            }
         }

		   int x=0;
		   while(x!=1)
		   {
			   if(CUSBFolder::LastFolderPath.Right(1)==("\\"))
			   x++;
			   CUSBFolder::LastFolderPath.Delete(CUSBFolder::LastFolderPath.GetLength()-1,1);
		   }
		   CChildView::thisPtr->PrepareUSBList(CUSBFolder::LastFolderPath,Fun_Id,TitleID);
         CChildView::thisPtr->Invalidate();
	   }
   }
   else
   {
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
      CChildView::thisPtr->Invalidate();
   }
}

bool AddGraphIfFound(CString GraphPath, CChildView *view)
{
   CVgaMenu *menu=theApp.MenuPointer;
  	CFile f;
	CFileException e;
	
	if( f.Open( GraphPath, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
	{	
		if(!f.GetLength())
		{
         f.Close();
			return false;
		}
		f.SeekToBegin();
      CVgaDrawGraph * tempGraph= new CVgaDrawGraph();
		int  size= sizeof(tempGraph->GraphData);
      delete tempGraph;
		char Comma;

		int ObjectSize = sizeof(int)+ sizeof(Comma)+ size + sizeof(Comma);
		int NoOfGraphObjects = (f.GetLength())/ObjectSize;
	
		int ID;
		for(int GraphNum =0;GraphNum<NoOfGraphObjects;GraphNum++)
		{
			f.SeekToBegin();
			f.Seek( (ObjectSize*GraphNum),CFile::begin);
			f.Read(&ID,sizeof(int));
			if(ID==CWeldingHistory::thisHisPtr->SelectedWeldId)
			{	
            CVgaDrawGraph * Graph= new CVgaDrawGraph();
				CVgaDrawGraph::GraphCount--;
				f.Read(&Comma,sizeof(char));
            f.Read(&(Graph->GraphData),size);
				bool HistoryGraphPresent=false;
				POSITION pos = menu->items.GetHeadPosition();
				while (pos)
				{
					CVgaMenuItem * object = menu->items.GetNext(pos);
					int type = object->GetType();
					if(type ==VGAHistoryGraphObject)
					{ 
                  CHistoryGraphs *obj = (CHistoryGraphs *)object;
                  HistoryGraphPresent=true;
						obj->HistoryGraphList.AddTail(Graph);
                  if(obj->HistoryGraphList.GetCount()==1)
				      {
					      obj->Graph1ID=Graph->GraphData.graph_type;
                     obj->LastGraphDisplayed=Graph->GraphData.graph_type;
					      obj->Graph2ID=-1;
                  }

						break;
                   
					}
				}
				  
         }
		}
		f.Close();
	}
   return false;
}


bool PrepareHistoryGraphList(CChildView *view)
{
      CVgaMenu *menu=theApp.MenuPointer;
      CString Path = CUSBFolder::HistoryGraphPath+"\\";

		CString FileName="PowerGraph.log";
		CString GraphPath=	Path+FileName;
		AddGraphIfFound(GraphPath,view);

		FileName="ColDistGraph.log";
		 GraphPath=	Path+FileName;
		AddGraphIfFound(GraphPath,view);
	
	
		FileName="VelocityGraph.log";
		GraphPath=	Path+FileName;
		AddGraphIfFound(GraphPath,view);
	
		FileName="ForceGraph.log";
		GraphPath=	Path+FileName;
		AddGraphIfFound(GraphPath,view);
	

	
		FileName="AmpGraph.log";
		GraphPath=	Path+FileName;
		AddGraphIfFound(GraphPath,view);
	
		FileName="FreqGraph.log";
		GraphPath=	Path+FileName;
		AddGraphIfFound(GraphPath,view);
		
		POSITION pos = menu->items.GetHeadPosition();
		CVgaMenuItem * object;
		while (pos)
		{
			object = menu->items.GetNext(pos);
			int type = object->GetType();
			if(type ==VGAHistoryGraphObject)
			{
			   CHistoryGraphs *obj = (CHistoryGraphs *)object;
            if(obj->HistoryGraphList.GetCount()>0)
               return true;
            else
               return false;
				break;
			}
		}
		return false;
}

void ProcessHistoryGraph(int Address)
{  
   CVgaMenu *menu=theApp.MenuPointer;
   CString StrM5_35,Str_NoValidGraph;
   POSITION pos1 = menu->items.GetHeadPosition();
   CVgaMenuItem *Object= 0;
   int count=0;
   while (pos1)
   {
      Object= menu->items.GetNext(pos1);
      if((Object->GetType()==CVgaMenu::VGAMsgScrnObject))
      {
		   count++;
         CMsgScreen *ptr=(CMsgScreen *)Object;
         if(count==1)
         {
            StrM5_35=Object->text;
         }
         else
         {
            Str_NoValidGraph=Object->text;
         }
         
      }
      else if(Object->GetType()==VGAHistoryGraphObject)
      {
         while(((CHistoryGraphs *)Object)->HistoryGraphList.GetCount())
		            free(((CHistoryGraphs *)Object)->HistoryGraphList.RemoveHead()); 				
      }
   }
	CChildView::thisPtr->ShowMessageScreen(StrM5_35);
	if(CWeldingHistory::thisHisPtr->WeldHistoryList.GetCount())
	{
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
      CChildView::thisPtr->ShowMessageScreen(Str_NoValidGraph);
		return ;
	}

	if(!CChildView::ISUSBPresent)
	{	
      CVgaMenu * menu;
      if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
		{
         theApp.menuName=CVgaBottomMenu::mainMenuID;
         theApp.MenuPointer=menu;
         CChildView::thisPtr->ModifyObjectList(menu); 
         CChildView::thisPtr->Invalidate();
         return;
      }
	}


	if(!PrepareHistoryGraphList(CChildView::thisPtr))
   {
      CChildView::thisPtr->ShowMessageScreen(Str_NoValidGraph);
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
      CChildView::thisPtr->Invalidate();
   }
	else
   {		
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
      CChildView::thisPtr->Invalidate();
   }
}

void UpdateScreenGraphs(int Type)
{
	CVgaMenu *menu=theApp.MenuPointer;
   CVgaMenuItem *object= 0;
   POSITION pos = menu->items.GetHeadPosition();
   while (pos)
	{
		object = menu->items.GetNext(pos);
		int type = object->GetType();
		if(type ==VGAHistoryGraphObject)
		{
			CHistoryGraphs *ptr=(CHistoryGraphs *)object;
         if(ptr->Graph1ID == Type)
	      {
		      if(ptr->Graph2ID !=-1)
		      {
			      ptr->Graph1ID=ptr->Graph2ID;
			      ptr->LastGraphDisplayed=ptr->Graph2ID;
			      ptr->Graph2ID=-1;
		      }
	      }
	      else if(ptr->Graph2ID == Type)
	      {
		      ptr->Graph2ID=-1;
		      ptr->LastGraphDisplayed=ptr->Graph1ID;
	      }
	      else
	      {
		      POSITION pos = ptr->HistoryGraphList.GetHeadPosition();
		      while(pos)
		      {	
			      CVgaDrawGraph *Object = ptr->HistoryGraphList.GetNext(pos);
			      if(Object->GraphData.graph_type==Type)
			      {
				      if(ptr->Graph2ID!=ptr->LastGraphDisplayed)
					      ptr->Graph2ID = Type;
				      else
					      ptr->Graph1ID = Type;

				      ptr->LastGraphDisplayed=Type;
				      break;
			      }
		      }
	      }
			break;
		}
	}
   
}

void ProcessUSBVelocityGraph(int Address)
{
   int type;
   if(CChildView::thisPtr->metric)
      type=VELMMGRAPH;
   else
      type=VELINGRAPH;
   UpdateScreenGraphs(type);
   CChildView::thisPtr->Invalidate();
}

void ProcessUSBFrquencyGraph(int Address)
{
   UpdateScreenGraphs(FREQUGRAPH);
   CChildView::thisPtr->Invalidate();
}

void ProcessUSBColDistanceGraph(int Address)
{
   int type;
   if(CChildView::thisPtr->metric)
      type=DISTMMGRAPH;
   else
      type=DISTINGRAPH;
   UpdateScreenGraphs(type);
   CChildView::thisPtr->Invalidate();
}

void ProcessUSBForceGraph(int Address)
{
   int type;
   if(CChildView::thisPtr->metric)
      type=FORCENGRAPH;
   else
      type=FORCELBGRAPH;
   UpdateScreenGraphs(type);
   CChildView::thisPtr->Invalidate();
}

void ProcessUSBPowerGraph(int Address)
{
   UpdateScreenGraphs(POWGRAPH);
   CChildView::thisPtr->Invalidate();
}

void ProcessUSBAmplitudeGraph(int Address)
{
   UpdateScreenGraphs(AMPLIGRAPH);
   CChildView::thisPtr->Invalidate();
}

void ExitHistoryGraph(int Address)
{
   if(!CChildView::ISUSBPresent)
	{	
      CVgaMenu * menu;
      if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
		{
         page_no=1;
         theApp.menuName=CVgaBottomMenu::mainMenuID;
         theApp.MenuPointer=menu;
         CChildView::thisPtr->ModifyObjectList(menu); 
         CChildView::thisPtr->Invalidate();
         return;
      }
	}
   CUSBFolder * USBPtr=0;
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
   CChildView::thisPtr->Invalidate();
}

void ProcessDiagnosticScreen(int Address)
{
   CString MenuName="";
   CVgaMenu * menu1=theApp.MenuPointer;
   POSITION pos = menu1->items.GetHeadPosition();
   CVgaMenuItem * Object;

   //CString str;
   //str.Format(_T("%d"),Address);
   //AfxMessageBox(str);

   while(pos)
   {
	  Object = menu1->items.GetNext(pos);
      if(Object->GetType() == CVgaMenu::VGABottomHalfObject)
      {
         CBottomHalf *obj=(CBottomHalf*)Object;
         MenuName=obj->submenu;
         CVgaMenu * menu;
         if (theApp.menus.Lookup(MenuName, menu))
		 {
            CBottomHalf::BottomMenuPointer=menu;
			//AfxMessageBox(MenuName);
         }
         CChildView::thisPtr->MenuNameID=MenuName;
         CBottomHalf::BottomHalfId=obj->EnumID;
         CChildView::BotomHalfRefreshTime=obj->RefreshTime;
         break;
      }
   }
   CChildView::thisPtr->Invalidate();
}

void ProcessHornSignature(int ID)
{
    int length =2;
    unsigned char data1[2];
    union 
	   {
		   short i;
		   char c[2];
	   } u;
	u.i=ID;
    data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];

	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
      char ch=CHostCommand::AckNak();
	  data = response->GetData();
	  length = response->GetDataLength();
     if(ch==theApp.ACK)
	  {
		 CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
         CString MenuName="";
         CVgaMenu * menu1=theApp.MenuPointer;
         POSITION pos = menu1->items.GetHeadPosition();
         CVgaMenuItem * Object;
	      while(pos)
	      {
		      Object = menu1->items.GetNext(pos);
            if(Object->GetType() == CVgaMenu::VGABottomHalfObject)
            {
               CBottomHalf *obj=(CBottomHalf*)Object;
               MenuName=obj->submenu;
               CVgaMenu * menu;
               if (theApp.menus.Lookup(MenuName, menu))
		       {
                  CBottomHalf::BottomMenuPointer=menu;
               }
               CChildView::thisPtr->MenuNameID=MenuName;
               CBottomHalf::BottomHalfId=obj->EnumID;
               CChildView::thisPtr->BottomHalfScreen=true;
               CChildView::BotomHalfRefreshTime=obj->RefreshTime;
               break;
            }
         } 
        CChildView::thisPtr->Invalidate();
	  }
	  else if(ch==theApp.NAK)
	  {
		 theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
		 page_no=CChildView::thisPtr->menus.RemoveTail();	
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		 CChildView::thisPtr->ProcessNak(data,length,0,0);
	  }
	  delete response;
   }
}

void ProcessResetAlarms(int Address)
{			
  CHostCommand * request = new CHostCommand(RESETALARMS_FUNID,0,0);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
     delete response;
   }
}

void ProcessSoftwareMismatchError(int Address)
{			
  theApp.Clean ();
   exit(1);
}