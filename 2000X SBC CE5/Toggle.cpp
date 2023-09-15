// Toggle.cpp: implementation of the CToggle class.
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
  1.2       04/07/08    PDwivedi  Modifiy ProcessNak() & MouseClick().
  1.3       04/14/08    PDwivedi  Modifiy MouseClick() for MultiLang support.
  1.4       06/06/08    PDwivedi  Modifiy MouseClick() for function execution.
  1.5       08/01/08    PDwivedi  Added new functions for USB functionality.
  1.6       08/08/08    PDwivedi  Final Code Clean up.
  1.7       08/26/08	   PDwivedi  Added Function for Executing On MouseClick().
  1.8       09/09/08    PDwivedi  Added changes for string Debug Menu.
*/

#include "stdafx.h"
#include "SBC.h"
#include "Toggle.h"
#include "XmlElement.h"
#include "Variable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern void ProcessSequence(int ID);
extern CChildView::PrintValues Setup,Welddata, WeldHistory,PowerGraph,ColDistance,VelocityGraph,
			ForceGraph,AmplitudeGraph,FrequencyGraph,PrintSequence;

extern CChildView::USBValues  USBWelddata,USBPowerGraph,USBColDistance,USBVelocityGraph,
			USBForceGraph,USBAmplitudeGraph,USBFrequencyGraph;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
bool CToggle::SequencingON=false;

CToggle::CToggle(CXmlElement * e)
{
   rect = CRect(0, 0, 0, 0);
   RectShow=1;
   textID=e->GetAttribute("textID");
   text=CVgaMenuItem ::LinearSearch(textID);
   FunName=e->GetAttribute("FunName");
   Toggle_Text1=CVgaMenuItem ::LinearSearch(e->GetAttribute("ID1"));
   Toggle_Text2=CVgaMenuItem ::LinearSearch(e->GetAttribute("ID2"));
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

CToggle::~CToggle()
{

}

void CToggle::Draw(CDC *pDC)
{
   CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;

   DrawRect(pDC, CChildView::Button_Color, rect);
	Draw_Pressed_Released_Button(pDC);
	DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
	DrawRect(pDC, CChildView::Back_Color, CRect(rect.right,
												rect.top,
												(rect.right+130),
												rect.bottom));
   DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,
														rect.top,
														(rect.right+100),
														rect.bottom), Toggle_Text,false);
   
   
}

/*************************************************************************************/
/*                                                                                   */
/*  This function is called when any toggle object is clicked by the user            */
/* This funtion sends a host command to get the new toggled string and displays it.  */
/* If NAK is obtained as the response then the funstion justs BEEPS indicating a NAK */
/*************************************************************************************/

bool CToggle::MouseClick(const CPoint &p, CChildView *view)
{
   int length =IntegerLength-1;
	unsigned char data[IntegerLength];
   union 
	{
		short i;
		char c[2];
	} u;
   u.i=EnumID;
   data[1]=u.c[0];
	data[0]=u.c[1];
   data[2]=(char)(!Toggle_Value);
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
         int OneByteValue=CVgaMenuItem::Convert_Char_To_Integer(data1,length,3);
         Toggle_Value=OneByteValue;
         if(FunName!="")
         {
            void *ptr;
            void (*rmn)(int);
            if(functionCall.Lookup(FunName,ptr))
		      {
			       rmn = (void (*)(int))ptr;
			       rmn(Toggle_Value);
            }
         }
     
         if(Toggle_Value)
         {
            Toggle_Text= " = " + Toggle_Text1;
         }
         else
         {
            Toggle_Text= " = " + Toggle_Text2;
         }
         int refresh=CVgaMenuItem::Convert_Char_To_Integer(data1,length,3);
         if(refresh)
         {
            theApp.GetSystemVariable();
            view->MaxPreset=1;
            view->SendCommandForQualityWindow(CChildView::MaxPreset);
           // CVgaMenu * menu;
           // if (theApp.menus.Lookup(theApp.menuName, menu))
		      {
               view->ModifyObjectList(theApp.MenuPointer);
            }
         }
         int ID=CVgaMenuItem::Convert_Char_To_Integer(data1,length,2);
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
         view->Invalidate ();
      }
      else
      {
         view->ProcessNak(data1,length,0,0);
      }
      delete response;
   }
   return true;
}

void ForceGraphPrintOnAlarm(int ID)
{
//	printf("\n ForceGraphPrintOnAlarm");
   ForceGraph.PrintOnAlarmValue=ID;
}
				
void DistanceGraphPrintOnAlarm(int ID)
{
//	printf("\n DistanceGraphPrintOnAlarm");
   ColDistance.PrintOnAlarmValue=ID;
}

void AmplitudeGraphPrintOnAlarm(int ID)
{
//	printf("\n AmplitudeGraphPrintOnAlarm");
   AmplitudeGraph.PrintOnAlarmValue=ID;
}

void PowerGraphPrintOnAlarm(int ID)
{
//	printf("\n PowerGraphPrintOnAlarm");
   PowerGraph.PrintOnAlarmValue=ID;
}

void VelocityGraphPrintOnAlarm(int ID)
{
//	printf("\n VelocityGraphPrintOnAlarm");
   VelocityGraph.PrintOnAlarmValue=ID;
}

void WeldHistoryPrintOnAlarm(int ID)
{
//	printf("\n WeldHistoryPrintOnAlarm");
   WeldHistory.PrintOnAlarmValue=ID;
}

void SetUpPresetPrintOnAlarm(int ID)
{
//	printf("\n SetUpPresetPrintOnAlarm");
   Setup.PrintOnAlarmValue=ID;
}

void SequencePrintOnAlarm(int ID)
{
//	printf("\n SequencePrintOnAlarm");
   PrintSequence.PrintOnAlarmValue=ID;
}

void FrequencyGraphPrintOnAlarm(int ID)
{
//	printf("\n FrequencyGraphPrintOnAlarm");
   FrequencyGraph.PrintOnAlarmValue=ID;
}

void WeldSummaryPrintOnAlarm(int ID)
{
//	printf("\n WeldSummaryPrintOnAlarm");
   Welddata.PrintOnAlarmValue=ID;
}

void USBForceGraphSaveAlarm(int ID)
{
   USBForceGraph.USBOnAlarmValue=ID;
}

void USBDistanceGraphSaveAlarm(int ID)
{
   USBColDistance.USBOnAlarmValue=ID;
}

void USBAmplitudeGraphSaveAlarm(int ID)
{
   USBAmplitudeGraph.USBOnAlarmValue=ID;
}

void USBPowerGraphSaveAlarm(int ID)
{
   USBPowerGraph.USBOnAlarmValue=ID;
}

void USBVelocityGraphSaveAlarm(int ID)
{
   USBVelocityGraph.USBOnAlarmValue=ID;
}

void USBFrequencyGraphSaveAlarm(int ID)
{
   USBFrequencyGraph.USBOnAlarmValue=ID;
}

void USBWeldDataSaveAlarm(int ID)
{
   USBWelddata.USBOnAlarmValue=ID;
}

void USBGlobalFlagOn_Off(int ID)
{
   CChildView::thisPtr->USBGlobalFlag=ID;
}

void ProcessExtPrest(int ID)
{
   CChildView::thisPtr->ExtPreset=ID;
   theApp.GetSystemVariable();
	CChildView::thisPtr->GetPrintingParameters(true);
}

void UpdateSW_Config(int ID)
{
   theApp.GetSystemVariable();
}