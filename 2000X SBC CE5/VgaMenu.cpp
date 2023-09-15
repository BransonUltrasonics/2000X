// VgaMenu.cpp: implementation of the CVgaMenu class.
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
  1.1       01/11/08    PDwivedi  Added New Object in list of Constructors.  
  1.2		   04/04/08	   PDwivedi	 Added New Functions in List.
  1.3       06/06/08    PDwivedi  Modified Draw() & Added New Functions.
  1.4       08/01/08	   PDwivedi  Modified Draw() for Graph.
  1.5       09/09/08    PDwivedi  Added changes for tracker issues.
  1.6       09/12/08    PDwivedi  Added changes for Tracker issues of round 2 testing for version LangTestJ.
  1.7       11/18/09    PDwivedi  Added changes for drawing Global Alarm button.
                                  
*/

#include "stdafx.h"
#include "SBC.h"
#include "VgaMenu.h"
#include "XmlElement.h"
#include "VgaTitle.h"
#include "VgaSubMenu.h"
#include "ChildView.h"
#include "VgaBottomMenu.h"
#include "VGAAdd_Back_Next_Button.h"
#include "VgaMenuItem.h"
#include "VgaChoice.h"
#include "Text.h"
#include "Toggle.h"
#include "RadioMenu.h"
#include "VgaVariable.h"
#include "Date.h"
#include "Time.h"
#include "VgaButton.h"
#include "VgaRadioButton.h"
#include "MsgScreen.h"
#include "ListBox.h"
#include "VgaAlphanumeric.h"
#include "BottomHalf.h"
#include "Check.h"
#include "VgaScreenSetup.h"
#include "Line.h"
#include "RunScreen.h"
#include "WeldingHistory.h"
#include "TextBox.h"
#include "VgaDrawGraph.h"
#include "Table.h"
#include "LocalChoice.h"
#include "VgaCompareGraph.h"
#include "VgaViewPreset.h"
#include "AlarmButton.h"
#include "HistoryGraphs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CVgaMenuItem *GlobalAlarmObject;
CVgaMenu::CVgaMenu()
{

}

CVgaMenu::CVgaMenu(CXmlElement * element)
{
	name = element->GetAttribute("name");
   POSITION pos = element->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * e = element->children.GetNext(pos);
		CString tag = e->GetTag();
		if (tag == "onenter")
			;
		else if (tag == "onexit")
			;
		else if (tag == "title")
         AddTitle(e);
      else if (tag == "submenu")
         AddSubmenu(e);
      else if(tag == "choice")
         AddChoicemenu(e);
      else if(tag == "textmenu")
         AddText(e);
      else if(tag == "togglemenu")
         AddTogglemenu(e);
      else if(tag == "radiomenu")
         AddRadioMenu(e);
	  else if(tag == "variablemenu")
         AddVariableMenu(e);
	  else if(tag == "Datemenu")
		 AddDateMenu(e);
	  else if(tag == "Timemenu")
		AddTimeMenu(e);
	  else if(tag == "VgaButton")
      AddVgaButtonMenu(e);
     else if(tag == "VgaRadioButton")
		  AddVgaRadioButtonMenu(e);
     else if(tag == "MsgScreen")
        AddMsgScreen(e);
     else if(tag == "ListBox") 
        AddListBox(e);
     else if(tag== "AlphaNumeric")
        AddAlphaNumeric(e);
     else if(tag=="BottomHalf")
        AddBottomHalf(e);
     else if(tag=="Check")
        AddCheck(e);
	 else if(tag=="screensetup")
	 {
		 //printf("\n screensetup");
		 AddScreenSetup(e);
	 }
	 else if(tag=="Line")
		 AddLine(e);
	 else if(tag=="RunMenu")
		 AddRunMenu(e);	
	 else if(tag=="HistoryMenu")
		 AddHistoryObject(e);
    else if(tag=="TextBox")
       AddTextBoxObject(e);
    else if(tag=="Graph")
       AddGraphObject(e);
    else if(tag=="TableObject")
       AddTableObject(e);
    else if(tag=="LocalChoiceObject")
       AddLocalChoiceObject(e);
    else if(tag=="CompareGraph")
       AddCompareGraph();
    else if(tag=="ViewPreset")
       AddViewPreset();
    else if(tag=="AlarmButton")
       AddAlarmButton(e);
    else if(tag=="HistoryGraphMenu")
       AddHistoryGraph(e);
    else
			ASSERT(FALSE);
	}
   AddBottomMenu();
}

CVgaMenu::~CVgaMenu()
{
}

void CVgaMenu::AddTitle(CXmlElement *e)
{
	CVgaTitle * title = new CVgaTitle(e);
	title->PSType=TITLE;
   if (title)
		title->SetType(TITLE);
   items.AddTail(title);
}

void CVgaMenu::Draw(CDC *pDC) const
{
//	printf("\n menu draw");
   int y = 0;
   POSITION pos = items.GetHeadPosition();
	CString txt,funcname;
	while (pos)
	{
		CVgaMenuItem * item = items.GetNext(pos);
   	int type=item->GetType();
      if((item->GtPageNum()==page_no)||(item->GtPageNum()==CVgaMenuItem::PAGEALL))
      {
		   if((item->IsDraw)&&(item->GetType()!=VGA_GRAPH_OBJECT))
		      item->DrawItem(pDC);
      }
	}
   if((CChildView::thisPtr->AlarmUpdateRequired)&&(!CChildView::thisPtr->ScreenSetupFlag))
   {
//      printf("\n draw alarm mrnu");
      GlobalAlarmObject->SetText(CChildView::thisPtr->GetAlarmString(GlobalAlarmObject));
		GlobalAlarmObject->Draw(pDC);
	}
   POSITION pos1 = theApp.GraphsDataList.GetHeadPosition();
	CVgaDrawGraph::GraphBoundary=false;
	while(pos1)
	{
//		printf("\n graph draw");
		CVgaDrawGraph *obj = theApp.GraphsDataList.GetNext(pos1);
		if(CChildView::thisPtr->AutoRefreshon)
		{
		//	printf("\n Auto on type=%d",obj->GraphType);
         if((obj->GraphType==POWGRAPH)//obj->MaxGraphType)
				/*&&(menuEntryList.GetCount()>7)*/&&(!CChildView::thisPtr->PMCScreen))
         {
		//		printf("\n Auto refresh on GetAveragePowerGraph");
           // obj->GraphType=obj->MaxGraphType;
            CChildView::thisPtr->GetAveragePowerGraph(pDC,CChildView::thisPtr);
           // obj->Draw(pDC);
           // obj->GraphType=1;
         }
			if ((!CChildView::thisPtr->DisableFlag) && (!CChildView::thisPtr->PMCScreen))
				obj->Draw(pDC);
			if(CChildView::thisPtr->PMCScreen)
			{
				CChildView::thisPtr->GetAveragePowerGraph(pDC,CChildView::thisPtr);
        //   printf("\n PMCScreen");
				if(!CChildView::thisPtr->DisableFlag)
				   obj->Draw(pDC);
			}
		
		
		}
		else
		{
		//	printf("\n type Auto off=%d",obj->GraphType);
         if((obj->GraphType == 1/*obj->MaxGraphTypeobj->graph_type!=CScreenObject::VGA_HORNSCANGRAPH*/)&&(!CChildView::thisPtr->PMCScreen)
				&&((obj->GraphData.GraphRequestValue==2)&&((CChildView::thisPtr->GraphOneRequestValue==2)||(CChildView::thisPtr->GraphTwoRequestValue==2))))
         {
          //  printf("\n Auto refresh off GetAveragePowerGraph");
           // obj->GraphType=obj->MaxGraphType;
				CChildView::thisPtr->GetAveragePowerGraph(pDC,CChildView::thisPtr);
            //obj->Draw(pDC);
           // obj->GraphType=1;
         }
         if((obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue)
				||(obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue)||((obj->GraphData.graph_type)>(PMC_GRAPH))//CScreenObject::VGA_NOGRAPH)
				||/*(obj->graph_type==CScreenObject::VGA_NOHSGRAPH)||*/((obj->GraphData.graph_type == (PMC_GRAPH-1))))/*CScreenObject::VGA_HORNSCANGRAPH*///||(CVGAButtons::PMCScreen))
			if(!CChildView::thisPtr->DisableFlag)
				obj->Draw(pDC);
         
			if(CChildView::thisPtr->PMCScreen)
			{
         //   printf("\n PMCScreen");
				CChildView::thisPtr->GetAveragePowerGraph(pDC,CChildView::thisPtr);
				if(!CChildView::thisPtr->DisableFlag)
				   obj->Draw(pDC);
			}
		}
	}

}

void CVgaMenu::AddSubmenu(CXmlElement *e)
{
	CVgaSubMenu * subMenu = new CVgaSubMenu(e);
   subMenu->PSType=SUBMENU;
   if (subMenu)
		subMenu->SetType(SUBMENU);
  items.AddTail(subMenu);
}

void CVgaMenu::AddBottomMenu()
{
	CVgaBottomMenu * object = 0;
	object = new CVgaBottomMenu();
	object->PSType=BottomMenu_Id;
   if (object)
		object->SetType(BottomMenu_Id);
   object->IsDraw = true;
    items.AddTail(object);
}

CVgaMenuItem* CVgaMenu::CreateObjectBack_Next(int exit_type)
{
	CVGAAdd_Back_Next_Button * object = 0;
	object = new CVGAAdd_Back_Next_Button(exit_type);
   object->PSType=exit_type;
   if (object)
		object->SetType(exit_type);
   object->IsDraw = true;
   return(object);
}
void CVgaMenu::AddChoicemenu(CXmlElement * e)
{
   CVgaChoice * ChoiceMenu = new CVgaChoice(e);
   ChoiceMenu->PSType=CHOICE;
   if (ChoiceMenu)
		ChoiceMenu->SetType(CHOICE);
   items.AddTail(ChoiceMenu);
}
void CVgaMenu::AddText(CXmlElement * e)
{
   CText * TextMenu = new CText(e);
   TextMenu->PSType=TEXT;
   if (TextMenu)
		TextMenu->SetType(TEXT);
   items.AddTail(TextMenu);
}

void CVgaMenu::AddTogglemenu(CXmlElement * e)
{
   CToggle * ToggleMenu = new CToggle(e);
   ToggleMenu->PSType=TOGGLE;
   if (ToggleMenu)
		ToggleMenu->SetType(TOGGLE);
   items.AddTail(ToggleMenu);
}

void CVgaMenu::AddRadioMenu(CXmlElement * e)
{
   CRadioMenu * RadioMenu = new CRadioMenu(e);
   RadioMenu->PSType=RADIOMENU;
   if (RadioMenu)
		RadioMenu->SetType(RADIOMENU);
   items.AddTail(RadioMenu);
}
void CVgaMenu::AddVariableMenu(CXmlElement * e)
{
   CVgaVariable * VariableMenu = new CVgaVariable(e);
   VariableMenu->PSType=VARIABLE;
   if (VariableMenu)
		VariableMenu->SetType(VARIABLE);
   items.AddTail(VariableMenu);
}
void CVgaMenu::AddDateMenu(CXmlElement * e)
{
   CDate * DateMenu = new CDate(e);
   DateMenu->PSType=DATE;
   if (DateMenu)
		DateMenu->SetType(DATE);
   items.AddTail(DateMenu);
}
void CVgaMenu::AddTimeMenu(CXmlElement * e)
{
	CVgaTime * TimeMenu = new CVgaTime(e);
   TimeMenu->PSType=HHMM;
   if (TimeMenu)
		TimeMenu->SetType(HHMM);
   items.AddTail(TimeMenu);
}
void CVgaMenu::AddVgaButtonMenu(CXmlElement * e)
{
	CVgaButton * VgaButtonMenu = new CVgaButton(e);
   VgaButtonMenu->PSType=VGA_Button_OBJECT;
   if (VgaButtonMenu)
		VgaButtonMenu->SetType(VGA_Button_OBJECT);
   items.AddTail(VgaButtonMenu);
}

void CVgaMenu::AddVgaRadioButtonMenu(CXmlElement * e)
{
	CVgaRadioButton * VgaRadioButtonMenu = new CVgaRadioButton(e);
   VgaRadioButtonMenu->PSType=RADIO_BUTTON;
   if (VgaRadioButtonMenu)
		VgaRadioButtonMenu->SetType(RADIO_BUTTON);
   items.AddTail(VgaRadioButtonMenu);
}

void CVgaMenu::AddMsgScreen(CXmlElement * e)
{
   CMsgScreen * MsgScreen = new CMsgScreen(e);
   MsgScreen->PSType=VGAMsgScrnObject;
   if (MsgScreen)
		MsgScreen->SetType(VGAMsgScrnObject);
   items.AddTail(MsgScreen);
}

void CVgaMenu::AddListBox(CXmlElement * e)
{
   CListBoxObject * ListBoxScreen = new CListBoxObject(e);
   ListBoxScreen->PSType=VGA_LISTBOX;
   if (ListBoxScreen)
		ListBoxScreen->SetType(VGA_LISTBOX);
   items.AddTail(ListBoxScreen);
}
void CVgaMenu::AddAlphaNumeric(CXmlElement * e)
{
   CVgaAlphanumeric * AlphaPointer = new CVgaAlphanumeric(e);
   AlphaPointer->PSType=ALPHA;
   if (AlphaPointer)
		AlphaPointer->SetType(ALPHA);
   items.AddTail(AlphaPointer);
}

void CVgaMenu::AddBottomHalf(CXmlElement * e)
{
   CBottomHalf *BottomHalf= new CBottomHalf(e);
   BottomHalf->PSType = VGABottomHalfObject;
   if(BottomHalf)
      BottomHalf->SetType(VGABottomHalfObject);
   items.AddTail(BottomHalf);
}

void CVgaMenu::AddCheck(CXmlElement * e)
{
   CCheck *Checkpointer= new CCheck(e);
   Checkpointer->PSType = VGACheck;
   if(Checkpointer)
      Checkpointer->SetType(VGACheck);
   items.AddTail(Checkpointer);
}

void CVgaMenu::AddScreenSetup(CXmlElement * e)
{
	CVgaScreenSetup::SetScreenMemberVariable(e);
}

void CVgaMenu::AddLine(CXmlElement * e)
{
   CLine *Linepointer= new CLine(e);
   Linepointer->PSType = VGALINE;
   if(Linepointer)
      Linepointer->SetType(VGALINE);
   items.AddTail(Linepointer);
}

void CVgaMenu::AddRunMenu(CXmlElement * e)
{
	CRunScreen *Runptr=new CRunScreen(e);
	Runptr->PSType =VGARUNSCREENOBJECT;
	if(Runptr)
		Runptr->SetType (VGARUNSCREENOBJECT);
	items.AddTail(Runptr);
}

void CVgaMenu::AddHistoryObject(CXmlElement * e)
{
	CWeldingHistory *Runptr=new CWeldingHistory(e);
	Runptr->PSType =VGAHISTORYOBJECT;
	if(Runptr)
		Runptr->SetType (VGAHISTORYOBJECT);
	items.AddTail(Runptr);
}

void CVgaMenu::AddTextBoxObject(CXmlElement * e)
{
   CTextBox *Textptr=new CTextBox(e);
	Textptr->PSType =VGATEXTBOX;
	if(Textptr)
		Textptr->SetType (VGATEXTBOX);
	items.AddTail(Textptr);
}

void CVgaMenu::AddGraphObject(CXmlElement * e)
{
   CVgaDrawGraph *Graphptr=new CVgaDrawGraph(e);
	Graphptr->PSType =VGA_GRAPH_OBJECT;
	if(Graphptr)
		Graphptr->SetType (VGA_GRAPH_OBJECT);
	items.AddTail(Graphptr);
} 
 

void CVgaMenu::AddTableObject(CXmlElement * e)
{
   CTable *TablePtr=new CTable(e);
	TablePtr->PSType =VGATableObject;
	if(TablePtr)
		TablePtr->SetType (VGATableObject);
	items.AddTail(TablePtr);
} 

void CVgaMenu::AddLocalChoiceObject(CXmlElement * e)
{
   CLocalChoice * LocalChoicePtr = new CLocalChoice(e);
   LocalChoicePtr->PSType=CHOICE;
   if (LocalChoicePtr)
		LocalChoicePtr->SetType(CHOICE);
   items.AddTail(LocalChoicePtr);
}

void CVgaMenu::AddCompareGraph()
{
	CVgaCompareGraph * object = 0;
	object = new CVgaCompareGraph();
	object->PSType=CHOICE;
   if (object)
		object->SetType(CHOICE);
   object->IsDraw = true;
    items.AddTail(object);
}

void CVgaMenu::AddViewPreset()
{
   CVgaViewPreset * ViewPtr = new CVgaViewPreset("");
   ViewPtr->PSType=COLORSETUP_ID;
   if (ViewPtr)
		ViewPtr->SetType(COLORSETUP_ID);
   items.AddTail(ViewPtr);
}

void CVgaMenu::AddAlarmButton(CXmlElement * e)
{
   CAlarmButton * AlarmButton = new CAlarmButton(e);
   AlarmButton->PSType=VGA_Button_OBJECT;
   if (AlarmButton)
		AlarmButton->SetType(VGA_ALARMBUTTON);
   items.AddTail(AlarmButton);
   AlarmButton->IsDraw =true;
   AlarmButton->RectShow=true;
   AlarmButton->SetPageNum(CVgaMenuItem::PAGEALL);
}

void CVgaMenu::AddHistoryGraph(CXmlElement * e)
{
   CHistoryGraphs *HisGraph=new CHistoryGraphs();
	HisGraph->PSType=VGAHistoryGraphObject;
   HisGraph->SetType(VGAHistoryGraphObject);
   HisGraph->IsDraw=true;
   HisGraph->RectShow=true;
	items.AddTail(HisGraph);
   HisGraph->SetPageNum(CVgaMenuItem::PAGEALL);
}