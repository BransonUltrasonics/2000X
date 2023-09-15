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
  1.1	    	04/04/08	PDwivedi  Remove LocalStrings.	
  1.2       06/06/08 PDwivedi  Modified MouseClick() for preparing MenuPointerList.
  1.3       08/08/08 PDwivedi  Final Code Clean up.
  1.4       11/06/09 PDwivedi  Added changes for showing String Number.

*/

// ScreenSetup.cpp: implementation of the CScreenSetup class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "SBC.h"
#include "VgaScreenSetup.h"
#include "VgaTitle.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
// The constructor is called when the user clicks on screen set up button
//////////////////////////////////////////////////////////////////////

CVgaScreenSetup::CVgaScreenSetup()
{
	button_1_pressed1=false;
	button_2_released1=false;
	Exit_pressed1=false;
	Done_pressed1=false;
	pressed1 = false;
	
}


void CVgaScreenSetup::SetScreenMemberVariable(CXmlElement * e)
{
	POSITION pos = e->children.GetHeadPosition();
	while (pos)
    {
		CXmlElement * element = e->children.GetNext(pos);
		CString tag = element->GetTag();
		CString Temp=element->GetAttribute("stringId");
		if (tag == "screen1")
      {
			CVgaScreenSetup::Str_ScreenSetupID=Temp;
         CVgaScreenSetup::Str_ScreenSetup=CVgaMenuItem ::LinearSearch(Temp);
      }
		else if(tag=="screen2")
      {
			CVgaScreenSetup::Str_TouchButton1ID=Temp;
         CVgaScreenSetup::Str_TouchButton1=CVgaMenuItem ::LinearSearch(Temp);
      }
		else if(tag=="screen3")
      {
		   CVgaScreenSetup::Str_TouchButton2ID=Temp;
         CVgaScreenSetup::Str_TouchButton2=CVgaMenuItem ::LinearSearch(Temp);
      }
		else if(tag=="screen4")
      {
			CVgaScreenSetup::Str_ScrnAlignID=Temp;
         CVgaScreenSetup::Str_ScrnAlign=CVgaMenuItem ::LinearSearch(Temp);
      }
		else if(tag=="screen5")
      {
			CVgaScreenSetup::Str_DoneID=Temp;
         CVgaScreenSetup::Str_Done=CVgaMenuItem ::LinearSearch(Temp);
      }
		else if(tag=="screen6")
      {
         CVgaScreenSetup::Str_ExitID=Temp;
         CVgaScreenSetup::Str_Exit=CVgaMenuItem ::LinearSearch(Temp);
      }
		else
			ASSERT(FALSE);
	}
}

bool CVgaScreenSetup::Exit_pressed1;
bool CVgaScreenSetup::Done_pressed1;
bool CVgaScreenSetup::button_1_pressed1;
bool CVgaScreenSetup::button_2_released1;
static struct CVgaScreenSetup::CalibCordinate ActualCalibCordinate={45,433,591,45};
static struct CVgaScreenSetup::CalibCordinate TempCalibCordinate;
float CVgaScreenSetup::DY1;
float CVgaScreenSetup::DX1;
CString CVgaScreenSetup::Str_ScreenSetup,CVgaScreenSetup::Str_TouchButton1,CVgaScreenSetup::Str_TouchButton2,CVgaScreenSetup::Str_ScrnAlign,CVgaScreenSetup::Str_Done,CVgaScreenSetup::Str_Exit;	
CString CVgaScreenSetup::Str_ScreenSetupID,CVgaScreenSetup::Str_TouchButton1ID,
   CVgaScreenSetup::Str_TouchButton2ID,CVgaScreenSetup::Str_ScrnAlignID,
   CVgaScreenSetup::Str_DoneID,CVgaScreenSetup::Str_ExitID;

CVgaScreenSetup::~CVgaScreenSetup()
{

}


/****************************************************************************************/
/*  This function draws the Screen setup screen.										*/
/*  the function checks if the button is pressed or not, if found then draws it in      */
/*  pressed state.																		*/
/*																						*/
/****************************************************************************************/
void CVgaScreenSetup::Draw(CDC *pDC)
{	
   lang_index=CChildView::Language_Index;
	DrawRect(pDC,CChildView::Back_Color, Title_Rect);
   CString TempScreenSetup = CVgaScreenSetup::Str_ScreenSetup;
   CString TempScrnAlign = CVgaScreenSetup::Str_ScrnAlign;
   CString TempDone= CVgaScreenSetup::Str_Done;
   CString TempExit = CVgaScreenSetup::Str_Exit;
   CString TempTouchButton1=CVgaScreenSetup::Str_TouchButton1;
   CString TempTouchButton2=CVgaScreenSetup::Str_TouchButton2;

   if(CChildView::thisPtr->StringDebugFlag)
   {
      TempScreenSetup = CVgaScreenSetup::Str_ScreenSetupID + _T(" ") 
         + CVgaScreenSetup::Str_ScreenSetup;
      TempScrnAlign = CVgaScreenSetup::Str_ScrnAlignID + _T(" ") 
         + CVgaScreenSetup::Str_ScrnAlign;
      TempDone= CVgaScreenSetup::Str_DoneID + _T(" ") + CVgaScreenSetup::Str_Done;
      TempExit = CVgaScreenSetup::Str_ExitID + _T(" ") + CVgaScreenSetup::Str_Exit;
      TempTouchButton1=CVgaScreenSetup::Str_TouchButton1ID + _T(" ") 
         + CVgaScreenSetup::Str_TouchButton1;
      TempTouchButton2=CVgaScreenSetup::Str_TouchButton2ID + _T(" ") 
         + CVgaScreenSetup::Str_TouchButton2;
   }
	DrawText(pDC, Bigfont, CChildView::TextColor, Title_Rect,
						TempScreenSetup,true);

	if(! CChildView::DisableFlag)
	{
		DrawText(pDC, Bigfont, CChildView::TextColor,ScrnCalibButtonLabel1_rect,
										"1",true);

		DrawText(pDC, Bigfont, CChildView::TextColor,ScrnCalibButtonLabel2_rect,
										"2",true);

		DrawText(pDC, Bigfont, CChildView::TextColor,StrScrnAlign_rect,
										TempScrnAlign,true);
		
		DrawRect(pDC, Black, ScrnCalibButton1_BoundingRect);
		DrawRect(pDC, Black, ScrnCalibButton2_BoundingRect);

	if(!button_2_released1)
		DrawRect(pDC,White, ScrnCalibButton2_rect);
	else if(button_1_pressed1)
	{
		DrawRect(pDC,Green, ScrnCalibButton2_rect);
		/*erasing the string touch2 and release*/
		DrawText(pDC, Bigfont, CChildView::TextColor,StrTouchButton2_rect,"                                                 ",false);
		
		/*drawing done button */
		rect=DoneButton_Rect;
		bool TempPressed =pressed1;
		pressed1=Done_pressed1;
		DrawRect(pDC, CChildView::Button_Color, rect);//Draw Button.
		Draw_Pressed_Released_Button(pDC);//Giving Released Look.
		DrawText(pDC, SmallFont, CChildView::TextColor, rect,TempDone,true);
		pressed1 = TempPressed;
	
			
	}

	/*drawing exit button*/
	rect=ExitButton_Rect;
	bool TempPressed1 =pressed1;
	pressed1=Exit_pressed1;
	DrawRect(pDC, CChildView::Button_Color, rect);//Draw Button.
	Draw_Pressed_Released_Button(pDC);//Giving Released Look.
	DrawText(pDC, SmallFont, CChildView::TextColor, rect,TempExit,true);
	pressed1=TempPressed1;

   /*drawing dots and their rectangles*/
		if(!button_1_pressed1)
	{
		DrawText(pDC, Bigfont, CChildView::TextColor,StrTouchButton1_rect,
											TempTouchButton1,true);
		DrawRect(pDC,White, ScrnCalibButton1_rect);
	}
	else if(!button_2_released1)
	{
		DrawText(pDC, Bigfont, CChildView::TextColor,StrTouchButton1_rect,
						"                                              ",false);
		DrawText(pDC, Bigfont, CChildView::TextColor,StrTouchButton1_rect,
											TempTouchButton2,true);
		DrawRect(pDC,Green, ScrnCalibButton1_rect);
	}
	else if(button_2_released1)
		DrawRect(pDC,Green, ScrnCalibButton1_rect);
		DrawRect(pDC,Black, ScrnCalibDot1_rect);
		DrawRect(pDC,Black, ScrnCalibDot2_rect);
	}

}

/**********************************************************************************************/
/* this function handles the mouse click if it is on the screen setup screen.                 */
/* the function is called on both LButton up and LButton down .								  */
/*																							  */	
/**********************************************************************************************/	
bool CVgaScreenSetup:: MouseClick(const CPoint &p, CChildView *view)
{	
	if(ScrnCalibButton1_rect.PtInRect(p) && (button_2_released1 ==false) 
		/*&& !Color_Setup_pressed1*/ && !Done_pressed1 && !Exit_pressed1)
	{
		button_1_pressed1 =true;
		TempCalibCordinate.Xa=p.x;//storing in tempcalib
		TempCalibCordinate.Ya=p.y;
		view->Invalidate();
		return true;
	}
	
	else if(ScrnCalibButton2_rect.PtInRect(p) && (button_1_pressed1 ==true)
		/*&& !Color_Setup_pressed1*/ && !Done_pressed1 && !Exit_pressed1)
	{
		button_2_released1 =true;
		TempCalibCordinate.Xb=p.x;
		TempCalibCordinate.Yb=p.y;//storing in tempcalib
		view->Invalidate();
		return true;
	}


	/*on LButton down processing */
	if(!pressed1)
	
   if(DoneButton_Rect.PtInRect(p) && button_2_released1  && !Done_pressed1)
	{
		Done_pressed1=true;
		pressed1=true;
		view->Invalidate();
		return true;
	}

	else if(ExitButton_Rect.PtInRect(p) && !Exit_pressed1)
	{
		Exit_pressed1=true;
		pressed1=true;
		view->Invalidate();
		return true;
	}


	/* processing on OnLButton Up */
   if(Done_pressed1  && button_2_released1)
	{	
		pressed1=false;
		Done_pressed1=false;
		view->RedrawWindow(NULL,NULL,RDW_INVALIDATE| RDW_UPDATENOW | RDW_ERASE );
		CChildView::ScreenSetupFlag=false;

		/*storing values of TempCalibCordinates to RamCalibCordinate */
		CChildView::RAMCalibCordinate_Xa = TempCalibCordinate.Xa;
		CChildView::RAMCalibCordinate_Xb = TempCalibCordinate.Xb;
		CChildView::RAMCalibCordinate_Ya = TempCalibCordinate.Ya;
		CChildView::RAMCalibCordinate_Yb = TempCalibCordinate.Yb;

		/*the following values of DX1 & DY1 will be used to calibrate the touch screen
		co-ordinates in On-LbuttonUp() and OnLButtonDown() functions (in view class) */
		DX1 = (float)( ActualCalibCordinate.Xb - ActualCalibCordinate.Xa)/
            (float)( CChildView::RAMCalibCordinate_Xb - CChildView::RAMCalibCordinate_Xa);
		DY1 = (float)( ActualCalibCordinate.Yb - ActualCalibCordinate.Ya)/
             (float)( CChildView::RAMCalibCordinate_Yb - CChildView::RAMCalibCordinate_Ya);
		view->SaveData();
      theApp.menuName=view->menusname.RemoveTail();
      page_no=view->menus.RemoveTail();
      theApp.MenuPointer=view->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
      view->Invalidate();
		return true;
	}

	else if(Exit_pressed1)
	{		
		pressed1=false;
		Exit_pressed1=false;
		view->RedrawWindow(NULL,NULL,RDW_INVALIDATE| RDW_UPDATENOW | RDW_ERASE );
		CChildView::ScreenSetupFlag=false;
      theApp.menuName=view->menusname.RemoveTail();
      page_no=view->menus.RemoveTail();
      theApp.MenuPointer=view->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
      view->Invalidate();
		return true;
	}
	return true;
}
