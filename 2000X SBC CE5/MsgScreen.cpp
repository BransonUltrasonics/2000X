// MsgScreen.cpp: implementation of the CMsgScreen class.
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
  1.1		   04/04/08	PDwivedi  Added Member Variables.
  1.2       11/06/09 PDwivedi  Added changes for showing String number on MsgScreen.

*/
#include "stdafx.h"
#include "SBC.h"
#include "MsgScreen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/****************************************************************************/
/*                                                                          */
/*  This function creates a CVGAMsgScreen object When any CVGAMsgScreen     */
/*  type object is found in  menu/submenu item list							*/
/*																		    */ 
/****************************************************************************/
CMsgScreen::CMsgScreen(CXmlElement * e)
{
	//Back color for Message Window.
	FillColor=_ttoi(e->GetAttribute("FillColor"));
	ResponseType=_ttoi(e->GetAttribute("Response"));
    RectShow=1;

    /*Storing Co-ordinated for message window*/
	X1_CoOrdinate = _ttoi(e->GetAttribute("X1"));
	Y1_CoOrdinate = _ttoi(e->GetAttribute("Y1"));
	X2_CoOrdinate = _ttoi(e->GetAttribute("X2"));
	Y2_CoOrdinate = _ttoi(e->GetAttribute("Y2"));
	
	/*Storing Duration to Display message screen.*/
	Time = _ttoi(e->GetAttribute("Time"));
	
	//Message text font.
	TextFont = _ttoi(e->GetAttribute("TextFont"));
	//Message text Color.
	TextColor =_ttoi(e->GetAttribute("TextColor"));
	
	/*Storing Text for message screen.*/
   MsgLine1ID=e->GetAttribute("textID1");
	MsgLine1 = CVgaMenuItem ::LinearSearch(MsgLine1ID);//First line Text.
    text=MsgLine1;
	MsgLine1.TrimRight();
	MsgLine1.TrimLeft();

	MsgLine2ID=e->GetAttribute("textID2");
   MsgLine2 = CVgaMenuItem ::LinearSearch(MsgLine2ID);//Second Line Text.
	MsgLine2.TrimRight();
	MsgLine2.TrimLeft();

	MsgLine3ID=e->GetAttribute("textID3");
   MsgLine3 = CVgaMenuItem ::LinearSearch(MsgLine3ID);//Third Line Text.
    submenu= e->GetAttribute("submenu");
    menunak= e->GetAttribute("menunak");
	MsgLine3.TrimRight();
	MsgLine3.TrimLeft();

	/*Chacking for empty Text line*/
	for(int i=0;i<2;i++)
	{
		if(MsgLine3=="\0")
		{
			MsgLine3=MsgLine2;
			MsgLine2=MsgLine1;
			MsgLine1="\0";
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

CMsgScreen::~CMsgScreen()
{

}


/**********************************************************************************/
/*                                                                                */
/*  This function Draws a CVGAMsgScreen object When any CVGAMsgScreen type object */
/*  is found in menu/submenu item list for current page .						  */
/*																		 		  */
/**********************************************************************************/
void CMsgScreen::Draw(CDC *pDC)
{
	CChildView::DisableFlag=true;
	rect=CRect(X1_CoOrdinate,Y1_CoOrdinate,X2_CoOrdinate,Y2_CoOrdinate);

	/*Drawing Message Rectangle in specified color*/
	DrawRect(pDC, Black, CRect(X1_CoOrdinate-1,
										Y1_CoOrdinate-1,
										X2_CoOrdinate+1,
										Y2_CoOrdinate+1));
	DrawRect(pDC, FillColor, CRect(X1_CoOrdinate,
										Y1_CoOrdinate,
										X2_CoOrdinate,
										Y2_CoOrdinate));

	/*Drawing Message Text*/
  if(CChildView::thisPtr->StringDebugFlag)
  {
      DrawText(pDC, Bigfont,TextColor , CRect(X1_CoOrdinate,
											     Y1_CoOrdinate+40,	
											     X2_CoOrdinate,
											     Y1_CoOrdinate+70), MsgLine1ID + MsgLine1,true);
	   DrawText(pDC, Bigfont, TextColor, CRect(X1_CoOrdinate,
											     Y1_CoOrdinate+70,	
											     X2_CoOrdinate,
											     Y1_CoOrdinate+100), MsgLine2ID + MsgLine2,true);
	   DrawText(pDC, Bigfont, TextColor, CRect(X1_CoOrdinate,
											     Y1_CoOrdinate+100,	
											     X2_CoOrdinate,
											     Y1_CoOrdinate+130), MsgLine3ID + MsgLine3,true);
  }
  else
  {
	   DrawText(pDC, Bigfont,TextColor , CRect(X1_CoOrdinate,
											     Y1_CoOrdinate+40,	
											     X2_CoOrdinate,
											     Y1_CoOrdinate+70), MsgLine1,true);
	   DrawText(pDC, Bigfont, TextColor, CRect(X1_CoOrdinate,
											     Y1_CoOrdinate+70,	
											     X2_CoOrdinate,
											     Y1_CoOrdinate+100), MsgLine2,true);
	   DrawText(pDC, Bigfont, TextColor, CRect(X1_CoOrdinate,
											     Y1_CoOrdinate+100,	
											     X2_CoOrdinate,
											     Y1_CoOrdinate+130), MsgLine3,true);
  }
	
   if(Time != 0)//if time is not equal to zero then initialise timer 4.
   {
		//printf("\n InitialiseTimer");
      CChildView::InitialiseTimer(MessageScreenTimer,Time); 
   }

	/*If time is zero but IsNewScreenPointer is true then also 
	initialise timer 4.(Actuator Cold Start).*/
	/*else if((Time == 0)&&(CChildView::IsNewScreenPointer))
	{
		CChildView::InitialiseTimer(MessageScreenTimer,0);
		CChildView::ActColdStartFlag =true;
	}*/
}

bool CMsgScreen::MouseClick(const CPoint &p, CChildView *view)
{
	return false;
}
