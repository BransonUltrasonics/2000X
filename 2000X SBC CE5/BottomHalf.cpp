// BottomHalf.cpp: implementation of the BottomHalf class.
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
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
  1.0       04/07/08	   PDwivedi  Added Initial Version.
  1.1       04/16/08    PDwivedi  Modify Constructor for MultiLangSupport.  
  1.2       09/02/08    PDwivedi  Modify Constructor & Draw for BottomHalf Screen.
*/

#include "stdafx.h"
#include "SBC.h"
#include "BottomHalf.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRect CBottomHalf::BottomHalfRect;
int CBottomHalf::BottomHalfId;
bool CBottomHalf::HornDownScreenPresent;
CVgaMenu * CBottomHalf::BottomMenuPointer;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBottomHalf::CBottomHalf(CXmlElement * e)
{

   //int Cord_Len =2;
//	BottomHalfId=Convert_Char_To_Integer(data,length,Cord_Len);
	text = CVgaMenuItem ::LinearSearch(e->GetAttribute("textID"));//Storing Text
	FillColor = _ttoi(e->GetAttribute("FillColor"));//Fill color for bottom half segment.
	if(FillColor == Black_DEFAULT)
		FillColor = White;
	Bottomtype= _ttoi(e->GetAttribute("type"));
	Refresh = _ttoi(e->GetAttribute("Refresh"));//Refresh required or not.
	//length -=2;


	RefreshTime = _ttoi(e->GetAttribute("RefreshTime"));//Refresh Time.
	CChildView::BotomHalfRefreshTime=RefreshTime;
	//RefreshTime=100;

	/*Storing Co-ordinates for Bottom half segment.*/
    X1_CoOrdinate = _ttoi(e->GetAttribute("X1"));
	 Y1_CoOrdinate = _ttoi(e->GetAttribute("Y1"));
	 X2_CoOrdinate = _ttoi(e->GetAttribute("X2"));
	 Y2_CoOrdinate = _ttoi(e->GetAttribute("Y2"));
    
    submenu=e->GetAttribute("menu");
    BottomHalfId=this->EnumID ;
    RectShow=0;
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
  // HornDownScreenPresent=true;
/*	Pointer = GetInteger(data,length);//Pointer to get Bottom Half segment.
	if((BottomHalfId==CScreenObject::VGA_BHHORNDOWN)
	  ||(BottomHalfId==CScreenObject::VGA_BHTEST))
		HornDownScreen=true;
   if(BottomHalfId==CScreenObject::VGA_BHTEST)
      TestScreen=true;*/

}

CBottomHalf::~CBottomHalf()
{
   HornDownScreenPresent=false;
   if(!CChildView::BottomHalfTimerOn)
	CChildView::KillTimers(3);
	CChildView::BottomHalfTimerOn=false;
}

/*************************************************************************************/
/*                                                                                   */
/*  This function Draws a CVGABottomHalf object When any CVGABottomHalf type object  */
/*  is found in menu/submenu item list for current page .							 */			 /*
/*************************************************************************************/
void CBottomHalf:: Draw(CDC *pDC)
{
	rect = CRect(X1_CoOrdinate-1, Y1_CoOrdinate,X2_CoOrdinate-2, Y2_CoOrdinate);
	BottomHalfRect=rect;
	DrawRect(pDC, FillColor,rect ); //Draw Button.
	DrawText(pDC, SmallFont, 1, CRect(X1_CoOrdinate,
									 Y1_CoOrdinate,
									 X2_CoOrdinate,
									 Y1_CoOrdinate+20),text,true);//Draw text 
	if(Refresh ==1)
   {
      if(CChildView::BotomHalfRefreshTime !=3000)
         CChildView::BotomHalfRefreshTime=RefreshTime;
    //  printf("\n refresh.........................=%d",Refresh);
      CChildView::InitialiseTimer(BottomHalfTimer,CChildView::BotomHalfRefreshTime); 
   }
}



/*************************************************************************************/
/*                                                                                   */
/* This function is called when any CVGABottomHalf object is clicked by the user     */
/* 																					 */
/*************************************************************************************/
bool CBottomHalf::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}
