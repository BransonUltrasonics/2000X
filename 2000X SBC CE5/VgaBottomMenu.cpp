// VgaBottomMenu.cpp: implementation of the CVgaBottomMenu class.
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
  1.1		   01/11/08	   PDwivedi	 Modified MouseClick().
  1.2		   04/04/08	   PDwivedi	 Modified MouseClick & Added Member function.
  1.3       04/14/08	   PDwivedi  Modified MouseClick() for MultiLangSupport.
  1.4       04/16/08    PDwivedi  Modified MouseClick() for HornDown Flag.
  1.5       06/06/08    PDwivedi  Modified MouseClick() for preparing new pointer list & updating alarm flag.
  1.6       08/01/08    PDwivedi  Modified SendCommandForBottomMenu for Handling Nak.
  1.7       08/08/08    PDwivedi  Final Code Clean up.
  1.8       08/26/08	   PDwivedi  Modified return type of SendCommandForBottomMenu().
  1.9       11/06/09    PDwivedi  Added changes for showing String Number.
  1.10      10/13/10    PDwivedi  Modified constructor to add ErrorMenuid.
*/

#include "stdafx.h"
#include "SBC.h"
#include "VgaBottomMenu.h"
#include "Application.h"
#include "VgaMenuItem.h"
#include "BottomHalf.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

bool CVgaBottomMenu::pressedbutton=false;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVgaBottomMenu::CVgaBottomMenu(int DrawRectonly)
{
   RectShow=DrawRectonly;
}

void CVgaBottomMenu::InitializeBottomMenuMembers(CXmlElement * e)
{
	
	CVgaBottomMenu::MenuErrorID = e->GetAttribute("ErrorMenuid");
   POSITION pos = e->children.GetHeadPosition();
	while (pos)
    {
		CXmlElement * element = e->children.GetNext(pos);
		CString tag = element->GetTag();
		CString name = element->GetAttribute("name");
		if (name == "main")
		{
		   mainMenuStringID=element->GetAttribute("stringId");
		   CChildView::mainmenu_string=CVgaMenuItem ::LinearSearch(mainMenuStringID);
		   mainMenuID=element->GetAttribute("menuid");
		   mainMenuCommandID=_ttoi(element->GetAttribute("commandid"));
		}
		else if(name=="weldresult")
		{
         WeldResultsStringID=element->GetAttribute("stringId");
		   CChildView::WeldResult_string=CVgaMenuItem ::LinearSearch(WeldResultsStringID);
		   WeldResults_ID=element->GetAttribute("menuid");
		   WeldResults_CommandID=_ttoi(element->GetAttribute("commandid"));
		}
		else if(name=="weldsetup")
		{
         WeldSetupStringID=element->GetAttribute("stringId");
		   CChildView::WeldSetup_string=CVgaMenuItem ::LinearSearch(WeldSetupStringID);
		   WeldSetup_ID=element->GetAttribute("menuid");
		   WeldSetup_CommandID=_ttoi(element->GetAttribute("commandid"));
		}
		else if(name=="graph")
		{
         GraphsMenuStringID=element->GetAttribute("stringId");
		   CChildView::Graphs_string=CVgaMenuItem ::LinearSearch(GraphsMenuStringID);
		   GraphsMenu_ID=element->GetAttribute("menuid");
		   GraphsMenu_CommandID=_ttoi(element->GetAttribute("commandid"));
		}
		else
			ASSERT(FALSE);
	}
}

CVgaBottomMenu::CVgaBottomMenu()
{ 
	RectShow=1;
   GraphPressed1 = false;
	MainMenuPressed1 = false;
	WeldSetupPressed1 = false;
	WeldResultPressed1 = false;
   
}
	
	 int CVgaBottomMenu::mainMenuCommandID;
	 int CVgaBottomMenu::GraphsMenu_CommandID;
	 int CVgaBottomMenu::WeldSetup_CommandID;
	 int CVgaBottomMenu::WeldResults_CommandID;

	CString CVgaBottomMenu::mainMenuID;
	CString CVgaBottomMenu::GraphsMenu_ID;
	CString CVgaBottomMenu::WeldSetup_ID;
	CString CVgaBottomMenu::WeldResults_ID;
	
   CString CVgaBottomMenu::MenuErrorID;
   CString CVgaBottomMenu::mainMenuStringID;
   CString CVgaBottomMenu::GraphsMenuStringID;
   CString CVgaBottomMenu::WeldSetupStringID;
   CString CVgaBottomMenu::WeldResultsStringID;

   bool CVgaBottomMenu::GraphPressed1;
	bool CVgaBottomMenu::MainMenuPressed1;
	bool CVgaBottomMenu::WeldSetupPressed1;
	bool CVgaBottomMenu::WeldResultPressed1;

CVgaBottomMenu::~CVgaBottomMenu()
{

}

/**************************************************************************/
/*  This function is called by the draw menu function of the  view class  */
/*  the function is used to draw th bottom menu buttons                   */
/**************************************************************************/
void CVgaBottomMenu::Draw(CDC *pDC)
{		
	if(!(RectShow))
   {
      DrawRect(pDC,CChildView::TitleBarColor,Bottom_Menu_Rect);
   }
   else
   {
       DrawRect(pDC,CChildView::TitleBarColor,Bottom_Menu_Rect);
	   bool TempPressed1 =pressed1;
	   
	   /*drawing weld result button */
	   pressed1=WeldResultPressed1;
	   rect = WeldResult_rect;
	   DrawRect(pDC, CChildView::Button_Color,WeldResult_rect);
	   Draw_Pressed_Released_Button(pDC);
	   
	   /*drawing Main Menu button */
	   pressed1=MainMenuPressed1;
	   rect=Bottom_MainMenu_rect;
	   DrawRect(pDC, CChildView::Button_Color,Bottom_MainMenu_rect);
	   Draw_Pressed_Released_Button(pDC);
	   
	   /*drawing Weld setup button */
	   pressed1=WeldSetupPressed1;
	   rect = Weldsetup_rect;
	   DrawRect(pDC, CChildView::Button_Color,Weldsetup_rect);
	   Draw_Pressed_Released_Button(pDC);
	   
	   /*drawing Graphs button */
	   pressed1=GraphPressed1;
	   rect = Graphs_rect;	
	   DrawRect(pDC, CChildView::Button_Color,Graphs_rect);
      Draw_Pressed_Released_Button(pDC);
	   
	   pressed1=TempPressed1;

      if(CChildView::thisPtr->StringDebugFlag)
      {
         DrawText(pDC, SmallFont, CChildView::TextColor, WeldResult_rect,WeldResultsStringID + CChildView::WeldResult_string,true );
	      DrawText(pDC, SmallFont, CChildView::TextColor, Bottom_MainMenu_rect,mainMenuStringID + CChildView::mainmenu_string,true);	
	      DrawText(pDC, SmallFont, CChildView::TextColor, Weldsetup_rect, WeldSetupStringID + CChildView::WeldSetup_string,true);
	      DrawText(pDC, SmallFont, CChildView::TextColor, Graphs_rect, GraphsMenuStringID + CChildView::Graphs_string,true);
      }
      else
      {

	      DrawText(pDC, SmallFont, CChildView::TextColor, WeldResult_rect,CChildView::WeldResult_string,true );
	      DrawText(pDC, SmallFont, CChildView::TextColor, Bottom_MainMenu_rect, CChildView::mainmenu_string,true);	
	      DrawText(pDC, SmallFont, CChildView::TextColor, Weldsetup_rect, CChildView::WeldSetup_string,true);
	      DrawText(pDC, SmallFont, CChildView::TextColor, Graphs_rect, CChildView::Graphs_string,true);
      }
   }
}

bool CVgaBottomMenu::MouseClick(const CPoint &p, CChildView *view)
{	
   if(!(RectShow))
   { 
     // printf("\n cond3");
      return false;  
   }
   if(!Bottom_Menu_Rect.PtInRect(p) && (pressedbutton == false)) 
   {
      //printf("\n cond1"); 
      return false;
   }
   
   //if(!view->DisableFlag)
	{
      if(pressedbutton == false )
	   {	
         //printf("\n cond2");
       if(Bottom_MainMenu_rect.PtInRect(p) && !MainMenuPressed1)
		   {
            MainMenuPressed1 = true;
		      pressedbutton=true;
            pressed1=true;
            CDC *pDC = view->GetDc();
		      rect=Bottom_MainMenu_rect;
		      Draw_Pressed_Released_Button(pDC);
		      view->ReleaseDc(pDC);
		      return true;
		   }
		   else if(Weldsetup_rect.PtInRect(p) && !WeldSetupPressed1)
		   {
            WeldSetupPressed1 = true;
		      pressedbutton=true;
            pressed1=true;
            CDC *pDC = view->GetDc();
		      rect = Weldsetup_rect;
		      Draw_Pressed_Released_Button(pDC);
		      view->ReleaseDc(pDC);
		      return true;
		   }
		   else if(Graphs_rect.PtInRect(p) && !GraphPressed1)
		   {
            GraphPressed1 = true;
		      pressedbutton=true;
            pressed1=true;
            CDC *pDC = view->GetDc();
		      rect = Graphs_rect;	
		      Draw_Pressed_Released_Button(pDC);
		      view->ReleaseDc(pDC);
		      return true;
		   }
		   else if(WeldResult_rect.PtInRect(p) && !WeldResultPressed1) 
		   {
            WeldResultPressed1 = true;
		      pressedbutton=true;
            pressed1=true;
            CDC *pDC = view->GetDc();
		      rect = WeldResult_rect;
		      Draw_Pressed_Released_Button(pDC);
		      view->ReleaseDc(pDC);
		      return true;
		   }
	   }
     if(!CChildView::thisPtr->BottomHalfTimerOn)
	      CChildView::thisPtr->KillTimers(BottomHalfTimer);
     if(pressedbutton == true)
	   {
         /* for OnLButtonUp*/
	      if(MainMenuPressed1)
	      {	
            /*releasing button*/
            MainMenuPressed1=false;
            pressedbutton =false;
            pressed1=false;
		      CDC *pDC = view->GetDc();
		      rect=Bottom_MainMenu_rect;
		      Draw_Pressed_Released_Button(pDC);
		      
		      view->ReleaseDc(pDC);
            if(theApp.menuName !=mainMenuID )
            {
               view->menusname.RemoveAll();
               view->menus.RemoveAll();
               view->menupointers.RemoveAll();
               while(theApp.GraphsDataList.GetCount()>0)
                  theApp.GraphsDataList.RemoveHead();
               CVgaMenu * menu;
               BottomSubmenu=mainMenuID;
               
               if(SendCommandForBottomMenu(mainMenuCommandID,(int)this))
			      {
                  if (theApp.menus.Lookup(mainMenuID, menu))
		            {
			            OnKeypadScreen_flag=false;
                     CChildView::thisPtr->IsAlarmScreen =false;
					      CChildView::RunResultScreen=false;
                     CBottomHalf::HornDownScreenPresent=false;
                     CChildView::thisPtr->PMCScreen=false;
                     CChildView::AccessLevelSystem=OPERATOR;
                     view->menusname.AddTail(theApp.menuName);
                     view->menus.AddTail(page_no);
                     view->menupointers.AddTail(theApp.MenuPointer);
                     page_no=1;
                     CChildView::thisPtr->ModifyObjectList(menu); 
                     theApp.menuName=mainMenuID;
                     theApp.MenuPointer=menu;
		            }		
               }
               else 
                  ERRORBEEP;
	            view->Invalidate();
            }
            else
            {
               CChildView::ErrorBeep();
            }
	         return true;
		   }
	      else if(WeldSetupPressed1)
	      {
            /*releasing button*/
            WeldSetupPressed1=false;
            pressedbutton =false;
            pressed1=false;
		      CDC *pDC = view->GetDc();
		      rect=Weldsetup_rect;
            Draw_Pressed_Released_Button(pDC);
            
		      view->ReleaseDc(pDC);
            if(theApp.menuName !=WeldSetup_ID)
            {
               view->menusname.RemoveAll();
               view->menus.RemoveAll();
               view->menupointers.RemoveAll();
               while(theApp.GraphsDataList.GetCount()>0)
                  theApp.GraphsDataList.RemoveHead();
		         CVgaMenu * menu;
               BottomSubmenu=WeldSetup_ID;
               
               
			      if(SendCommandForBottomMenu(WeldSetup_CommandID,(int)this))
			      {
                  if (theApp.menus.Lookup(WeldSetup_ID, menu))
		            {
			            OnKeypadScreen_flag=false;
                     CChildView::thisPtr->IsAlarmScreen =false;
					      CChildView::RunResultScreen=false;
                     CBottomHalf::HornDownScreenPresent=false;
                     CChildView::thisPtr->PMCScreen=false;
                     view->menusname.AddTail(theApp.menuName);
                     view->menus.AddTail(page_no);
                     view->menupointers.AddTail(theApp.MenuPointer);
                     page_no=1;
                     CChildView::thisPtr->ModifyObjectList(menu); 
                     theApp.menuName=WeldSetup_ID;
                     theApp.MenuPointer=menu;
		            }		
               }
               else 
                  ERRORBEEP;
		         view->Invalidate();
            }
            else
            {
               CChildView::ErrorBeep();
            }
		     return true;
	      }
	      else if(GraphPressed1)
	      {
             /*releasing button*/
            GraphPressed1=false;
	         pressedbutton =false;
            pressed1=false;
		      CDC *pDC = view->GetDc();
		      rect=Graphs_rect;
            Draw_Pressed_Released_Button(pDC);
           
		      view->ReleaseDc(pDC);
            if(theApp.menuName !=GraphsMenu_ID)
            {
               view->menusname.RemoveAll();
               view->menupointers.RemoveAll();
               view->menus.RemoveAll();
               while(theApp.GraphsDataList.GetCount()>0)
                  theApp.GraphsDataList.RemoveHead();
		         CVgaMenu * menu;
               BottomSubmenu=GraphsMenu_ID;
               
               if(SendCommandForBottomMenu(GraphsMenu_CommandID,(int)this))
			      {
                  if (theApp.menus.Lookup(GraphsMenu_ID, menu))
		            {
			            OnKeypadScreen_flag=false;
                     CChildView::thisPtr->IsAlarmScreen =false;
					      CChildView::RunResultScreen=false;
                     CBottomHalf::HornDownScreenPresent=false;
                     CChildView::thisPtr->PMCScreen=false;
                     CChildView::AccessLevelSystem=OPERATOR;
                     view->menusname.AddTail(theApp.menuName);
                     view->menus.AddTail(page_no);
                     view->menupointers.AddTail(theApp.MenuPointer);
                     page_no=1;
                     CChildView::thisPtr->ModifyObjectList(menu);  
                     theApp.menuName=GraphsMenu_ID;
                     theApp.MenuPointer=menu;
		            }		
               }
               else 
                  ERRORBEEP;
		         view->Invalidate();
            }
            else
            {
               CChildView::ErrorBeep();
            }
	         return true;
	      }

	      else if(WeldResultPressed1)
	      {
            /*releasing button*/
	         pressed1=false;
            WeldResultPressed1=false;
            pressedbutton =false;
		      CDC *pDC = view->GetDc();
		      rect=WeldResult_rect;
			   Draw_Pressed_Released_Button(pDC);
			   view->ReleaseDc(pDC);
            if(theApp.menuName !=WeldResults_ID)
            {
               view->menusname.RemoveAll();
               view->menupointers.RemoveAll();
               view->menus.RemoveAll();
               while(theApp.GraphsDataList.GetCount()>0)
                  theApp.GraphsDataList.RemoveHead();
			      CVgaMenu * menu;
               BottomSubmenu=WeldResults_ID;
               
			      if(SendCommandForBottomMenu(WeldResults_CommandID,(int)this))
			      {
                   if (theApp.menus.Lookup(WeldResults_ID, menu))
			          {
				           OnKeypadScreen_flag=false;
                       CChildView::thisPtr->IsAlarmScreen =false;
                       CChildView::RunResultScreen=true;
                       CBottomHalf::HornDownScreenPresent=false;
                       CChildView::thisPtr->PMCScreen=false;
                       CChildView::AccessLevelSystem=OPERATOR;
				           view->menusname.AddTail(theApp.menuName);
                       view->menus.AddTail(page_no);
                       view->menupointers.AddTail(theApp.MenuPointer);
                       page_no=1;
                       CChildView::thisPtr->ModifyObjectList(menu);
                       theApp.menuName=WeldResults_ID;
                       theApp.MenuPointer=menu;
			          }
			      }
			      else 
			      ERRORBEEP;
		         view->Invalidate();
            }
            else
            {
               CChildView::ErrorBeep();
            }
	         return true;
         }
      }
        
   }
   return false;
}

bool CVgaBottomMenu::SendCommandForBottomMenu(int ID,int Address)
{
	int length =2;
   unsigned char data1[2];
	union 
		   {
			   short i;
			   char c[2];
		   } u;
		 u.i=ID;
    //   printf("\n ID send in SendCommandForBottom=%d",ID);
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
      if(ch==theApp.NAK)
      {
        // printf("\n Nak");
         CChildView::thisPtr->ProcessNak(data,length,Address,0);
         delete response;
         return false;
      }
      delete response;
      return true;
   }
   return false;
}