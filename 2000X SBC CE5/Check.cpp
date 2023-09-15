// Check.cpp: implementation of the CCheck class.
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
  1.1       09/09/08	   PDwivedi  Added Changes for String Debug.

*/

#include "stdafx.h"
#include "SBC.h"
#include "Check.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheck::CCheck(CXmlElement * e)
{
   textID=e->GetAttribute("textID");
   text = CVgaMenuItem ::LinearSearch(textID);
   X_CoOrdinate = _ttoi(e->GetAttribute("X"));
   Y_CoOrdinate = _ttoi(e->GetAttribute("Y"));
   TextColor = _ttoi(e->GetAttribute("TextColor"));
   Font = _ttoi(e->GetAttribute("Font"));
   IsSelected = 0;
}

CCheck::~CCheck()
{

}

/*************************************************************************************/
/*                                                                                   */
/*  This function Draws a CCheck object When any CCheck type object is found   */
/*  in menu/submenu item list for current page .this function draws an empty		 */
/*  rectangle if the CCheck is not selected and a filled rectengle if the		 */
/*  CCheck is selected.														     */								 /*			 
/*************************************************************************************/
void CCheck::Draw(CDC *pDC)
{
   
   CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;
   
   rect = CRect(X_CoOrdinate-10,Y_CoOrdinate,X_CoOrdinate+230,Y_CoOrdinate+40);
      CRect Rect =CRect(X_CoOrdinate-25,
                        Y_CoOrdinate+5,
                        X_CoOrdinate-15,
                        Y_CoOrdinate+15);
	
   
   DrawText(pDC, SmallFont, CChildView::TextColor, CRect(X_CoOrdinate,
                                           Y_CoOrdinate,	
                                           X_CoOrdinate+140,
                                           Y_CoOrdinate+20), TempText,false);
   if(!IsSelected)
   {
      pDC->SelectObject(&penBlack1);
      pDC->Rectangle(X_CoOrdinate-25,
                     Y_CoOrdinate+5,
                     X_CoOrdinate-15,
                     Y_CoOrdinate+15);
   }
   else
      DrawRect(pDC, Black,Rect);
}

bool CCheck::MouseClick(const CPoint &p, CChildView *view)
{
   return false;
}