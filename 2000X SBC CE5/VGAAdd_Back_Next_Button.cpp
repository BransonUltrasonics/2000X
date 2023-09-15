// VGAAdd_Back_Next_Button.cpp: implementation of the CVGAAdd_Back_Next_Button class.
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
  1.1       08/04/08	   PDwivedi  Modified MouseClick for boundary condition check.
  1.2       08/08/08    PDwivedi  Final Code Clean up.
*/

#include "stdafx.h"
#include "SBC.h"
#include "VGAAdd_Back_Next_Button.h"
#include "Application.h"
#include "ChildView.h"
#include "VgaMenuItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVGAAdd_Back_Next_Button::CVGAAdd_Back_Next_Button(int type)
{
	SetType(type);
	pressed1=false;
   ObjectPageNum=PAGEALL;
   RectShow=1;
}

CVGAAdd_Back_Next_Button::~CVGAAdd_Back_Next_Button()
{

}

/****************************************************************************/
/* this function is used to draw next or previous button when called.		*/
/****************************************************************************/
void CVGAAdd_Back_Next_Button::Draw(CDC *pDC)
{
	DrawRect(pDC, CChildView::Button_Color, rect);
	Draw_Pressed_Released_Button(pDC);
	int type=GetType();
	if(type == CVgaMenu::NEXT)
		DrawText(pDC, Bigfont, CChildView::TextColor, rect, " >> ",true);
	else if(type ==CVgaMenu::BACK)
		DrawText(pDC, Bigfont, CChildView::TextColor, rect, " << ",true);
}
/*********************************************************************************/
/* This function is called when the user clicks on next/previous button.		 */
/* The function accordingly increments or decrements the page number and draws	 */	
/* the new screen																 */
/*********************************************************************************/

bool CVGAAdd_Back_Next_Button::MouseClick(const CPoint &p, CChildView *view)
{	
   int type=GetType();
	pressed1=false;
	CDC*pDC=view->GetDc();
	Draw_Pressed_Released_Button(pDC);
	view->ReleaseDc(pDC);
	
	/* for OnLButtonUp*/
	if(type== CVgaMenu::NEXT)//next
	{
		/*releasing button*/
      int Total_Pages=(view->Total_Objects)/(MaxItems_PerPage);
      int remender=(view->Total_Objects)%(MaxItems_PerPage);
		if(remender!=0)
		   Total_Pages++;
      if(page_no<Total_Pages)
         page_no++;
      else
         page_no=Total_Pages;
	   view->Invalidate();
	   //return true;
		
	}
	else if(type==CVgaMenu::BACK)//prev
	{
	  	/*releasing button*/
	   if(page_no>0)
		   page_no--;
      else
         page_no=1;
      view->Invalidate();
	}
	return true;
}
