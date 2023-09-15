// VgaViewPreset.cpp: implementation of the CVgaViewPreset class.
//
//////////////////////////////////////////////////////////////////////
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
  1.0       06/06/08	   PDwivedi  Added Initial Version.
  1.1       08/01/08	   PDwivedi  Removed PageString required.
  1.2       08/08/08    PDwivedi  Final Code Clean up.
*/

#include "stdafx.h"
#include "SBC.h"
#include "VgaViewPreset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVgaViewPreset::CVgaViewPreset(CString PresetName)
{
   View_Preset_Exit_pressed=false;
	View_Preset_Next_pressed=false;
	View_Preset_Back_pressed=false;
	pressed1 =false;
	Page_No=ONE;
	ExitRect =CRect(0,0,0,0);
	NextRect=CRect(0,0,0,0);
	BackRect=CRect(0,0,0,0);
	PresetNameString=PresetName;
   ObjectPageNum=PAGEALL;
}


CVgaViewPreset::~CVgaViewPreset()
{
   /*Delete ViewPresetTextList*/
	while (ViewPresetTextList.GetCount())
		delete ViewPresetTextList.RemoveHead();
}

bool CVgaViewPreset::View_Preset_Exit_pressed=false;
bool CVgaViewPreset::View_Preset_Next_pressed=false;
bool CVgaViewPreset::View_Preset_Back_pressed=false;
/*************************************************/
/*												 */
/*  This function Draws View Preset Screen.	     */
/*												 */
/*************************************************/
void CVgaViewPreset::Draw(CDC *pDC)
{
	
	/*Draw Text Objects.*/
	DrawTextObjectsList(pDC);
	
	/*Draw Back Next Buttons.*/
	DrawNextBackExiButton(pDC);
	
	/*Draw Page No.*/
	DrawPageNumber(pDC);

}

/********************************************************************************/
/*                                                                              */
/*  This function is called when Exit,Next or Back Button on View Preset Screen */  
/*  is clicked by the user.This function will Change the Page No(if Back Next   */
/*  button pressed) or go to privious screen if Exit button pressed.            */
/********************************************************************************/
bool CVgaViewPreset::MouseClick(const CPoint &p, CChildView *view)
{
//	printf("\n on mouseclick");
   if(/*(!View_Preset_Exit_pressed)&&*/(!View_Preset_Next_pressed)&&(!View_Preset_Back_pressed))
	{
	 /* for onLbutton down processing */
	/*	if(ExitRect.PtInRect(p) && (!View_Preset_Exit_pressed))
		{
			View_Preset_Exit_pressed=true;
			pressed1=true;
			view->Invalidate();
			return true;
		}
		else */if(NextRect.PtInRect(p) && (!View_Preset_Next_pressed))
		 {
//			printf("\n Next up pressed");
          View_Preset_Next_pressed=true;
			pressed1=true;
			view->Invalidate();
			return true;
		}
		else if(BackRect.PtInRect(p) && (!View_Preset_Back_pressed))
		 {
//			printf("\n Back up pressed"); 
         View_Preset_Back_pressed=true;
			 pressed1=true;
			view->Invalidate();
			return true;
		 }
	}
	/* for onLbutton up processing */
	/*	 if(View_Preset_Exit_pressed)
		{
			View_Preset_Exit_pressed=false;
			pressed1=false;
			view->Invalidate();
			view->PopMenu(false);
			return true;
		}
	
	 else*/ if(View_Preset_Next_pressed)
		 {
//			printf("\n Next down pressed");
          View_Preset_Next_pressed=false;
			pressed1=false;
			if(Page_No<MaxPageDisplay)
         {
//			   printf("\n Page_No<MaxPageDisplay");
//            printf("\n Page_No=%d",Page_No);
//            printf("\n MaxPageDisplay=%d",MaxPageDisplay);
            Page_No++;
           // page_no++;
         }
         view->Invalidate();
			//view->RedrawWindow(NULL,NULL,RDW_INVALIDATE| RDW_UPDATENOW | RDW_ERASE );
			return true;
		 }

	else if(View_Preset_Back_pressed)
		  {
//			printf("\n Back up pressed");
         View_Preset_Back_pressed=false;
			pressed1=false;
			if(Page_No>1)
         {
//			   printf("\n Page_No>1");
//            printf("\n Page_No in back=%d",Page_No);
//            printf("\n MaxPageDisplay in back=%d",MaxPageDisplay);
            Page_No--;
            //page_no--;
         }
         view->Invalidate();
			//view->RedrawWindow(NULL,NULL,RDW_INVALIDATE| RDW_UPDATENOW | RDW_ERASE );
			return true;
		 }
	return false;
}
/****************************************************************************/
/* This function will Draw Text for view preset screen for current page no. */
/****************************************************************************/
void CVgaViewPreset::DrawTextObjectsList(CDC *pDC)
{
	POSITION pos =ViewPresetTextList.GetHeadPosition();
	while(pos)
	{
		CPrintText *object = ViewPresetTextList.GetNext(pos);
		int New_Y_Cordinate = object->CoOrdinate.y;
		if(object->PageNo==Page_No)
			object->Draw(pDC);
	}
}
/****************************************************************/
/* This function will check for page number and then draw the   */
/*  Exit ,Back or Next Buttons.									*/
/****************************************************************/
void CVgaViewPreset::DrawNextBackExiButton(CDC *pDC)
{
	NextRect=NextButtonRect;
	BackRect=BackButtonRect;
	ExitRect=ExitButtonRect;
	/*Giving Rect to Exit Back,Next Buttons.*/
	if(Page_No==1)
	BackRect=CRect(0,0,0,0);
	if(Page_No==MaxPageDisplay)
	{
		BackRect=BackButtonRect;
		ExitRect=ExitButtonRect;
		NextRect=CRect(0,0,0,0);
	}
	/*Drawing Buttons.*/
	if(Page_No<MaxPageDisplay)
	{
	/*Drawing Next Buttons.*/
	rect=NextButtonRect;
   bool TempPressed1 =pressed1;
	pressed1=View_Preset_Next_pressed;
	DrawRect(pDC, CChildView::Button_Color, rect);//Draw Button.
	Draw_Pressed_Released_Button(pDC);//Giving Released Look.
	DrawText(pDC, Bigfont, CChildView::TextColor, rect, ">>",true);
	pressed1=TempPressed1;
	}
	if(Page_No>1)
	{
		/*Drawing Back Button.*/
	rect=BackButtonRect;
	bool TempPressed1 =pressed1;
	pressed1=View_Preset_Back_pressed;
	DrawRect(pDC, CChildView::Button_Color, rect);//Draw Button.
	Draw_Pressed_Released_Button(pDC);//Giving Released Look.
	DrawText(pDC, Bigfont, CChildView::TextColor, rect, "<<",true);
	pressed1=TempPressed1;
	}
		/*Drawing Exit Button.*/
	/*rect=ExitButtonRect;
	bool TempPressed1 =pressed1;
	pressed1=View_Preset_Exit_pressed;
	DrawRect(pDC, CChildView::Button_Color, rect);//Draw Button.
	Draw_Pressed_Released_Button1(pDC);//Giving Released Look.
	DrawText(pDC, SmallFont, CChildView::TextColor, rect, CColorSetup::Str_Exit[CChildView::Language_Index],true);
	pressed1=TempPressed1;*/
}

/******************************************************************************/
/* This function checks the co-ordinates of all text object to be shown on    */ 
/* view preset screen,and then it gives them page number & new co-ordinates   */
/* according to the page no.												  */
/******************************************************************************/
void CVgaViewPreset::ArrangeCoOrdinate()
{
 for(int page =1;page<=TOTALPAGE;page++)
	{
		POSITION pos =ViewPresetTextList.GetHeadPosition();
		while(pos)
		{
			CPrintText *object = ViewPresetTextList.GetNext(pos);
			int New_Y_Cordinate = object->CoOrdinate.y;
			if(((object->CoOrdinate.y>(FIRST_XCORD_FORTEXT+TOTALHEIGHT*(page-1)))
				&&(object->CoOrdinate.y<=(FIRST_XCORD_FORTEXT+TOTALHEIGHT*(page))))
				&&( object->CoOrdinate.x<TOTALHEIGHT ))
			{
				if(page!=1)
				object->CoOrdinate.y=(object->CoOrdinate.y-((TOTALHEIGHT)*(page-1)+ONELINEGAP));
				//else
					//object->CoOrdinate.y=object->CoOrdinate.y+ONELINEGAP;
				object->PageNo = page;
				MaxPageDisplay= page;
			}
			else if(((object->CoOrdinate.y>(FIRST_XCORD_FORTEXT+TOTALHEIGHT*(page-1)))
				&&(object->CoOrdinate.y<=(FIRST_XCORD_FORTEXT+TOTALHEIGHT*(page))))
				&&( object->CoOrdinate.x>TOTALHEIGHT ))
			{
				if(page!=1)
				object->CoOrdinate.y=object->CoOrdinate.y-((TOTALHEIGHT)*(page-1)+ONELINEGAP);
			//	else
				//	object->CoOrdinate.y=object->CoOrdinate.y+ONELINEGAP;
				object->PageNo = page;
				MaxPageDisplay= page;
			}
		}
	}
}
/*************************************************/
/* This function draws the Page no on the screen.*/
/*************************************************/
void CVgaViewPreset::DrawPageNumber(CDC *pDC)
{
	char Curr_buff[IntegerLength];
	sprintf(Curr_buff,"%dof%d",Page_No,MaxPageDisplay);
	CString PageString=CChildView::thisPtr->StrPage;//CChildView::StrPage[CChildView::Language_Index];
	PageString+=Curr_buff;
	CVgaMenuItem::DrawText(pDC, Bigfont,White, Page_No_Rect, PageString,true);
}