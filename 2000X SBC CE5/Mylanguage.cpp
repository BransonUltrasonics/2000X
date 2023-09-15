// Mylanguage.cpp: implementation of the CMylanguage class.
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
  1.1       01/11/08       PDwivedi  Draw() function.  
  1.2		04/07/08	   PDwivedi	 Comment out Draw Function.

*/

#include "stdafx.h"
#include "SBC.h"
#include "Mylanguage.h"
#include "TextIOFile.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMylanguage::CMylanguage(int X1,int Y1,int X2,int Y2)
{
   X1_CoOrdinate =  X1;
	Y1_CoOrdinate =  Y1;
	X2_CoOrdinate =  X2;
	Y2_CoOrdinate = Y2; 
   ListBox_Color=White;
}

CMylanguage::~CMylanguage()
{

}
bool CMylanguage::MouseClick(const CPoint &p, CChildView *view)
{
	return false;
}
void CMylanguage::Draw(CDC *pDC)
{
	
	/*Draw list box rectangle with list box color* /
	DrawRect(pDC, Black, CRect(X1_CoOrdinate-1,Y1_CoOrdinate-1,
								X2_CoOrdinate+1,Y2_CoOrdinate+1));
	DrawRect(pDC, ListBox_Color, CRect(X1_CoOrdinate,Y1_CoOrdinate,
										X2_CoOrdinate,Y2_CoOrdinate));
   int Y_CoOrdinate = Y1_CoOrdinate;
   int j=0,count=0;;
	int MaxLanguageDisplay=MAX_LANGUAGE_DISPLAYED;
	if(CChildView::Currentlanguage >=(MaxLanguageDisplay))
   {
      // Update no of Strings Displayed
      count=CChildView::Currentlanguage -(MaxLanguageDisplay);
      count++;
   }
				
	for(int i=count;i<(CChildView::TotalLanguage);i++)
	{
      //Index can't br greater than Total lang.
      if(i==CChildView::TotalLanguage)
         break;
      
      // Don't Dispaly more than 11 language
      if(j>=11)
         break;
      
      int Selectfont=CTextFileIO::SstFont[i];
      int FontSize=CTextFileIO::SstFontSize[i];

      /*Draw green background and "<"	mark on current Preset.* /			
		if((CChildView::Currentlanguage == (i)))
		{
			//Drawing HighLight Background.
			DrawRect(pDC, CChildView::Highlight_Color, CRect(X1_CoOrdinate,
										Y_CoOrdinate,
										X2_CoOrdinate,
										Y_CoOrdinate+31));
		
		}
      // Draw Font Strings
      CVgaMenuItem::DrawTextFont(pDC, FontSize,Selectfont, CChildView::TextColor, 
			CRect(X1_CoOrdinate+20,Y_CoOrdinate,X1_CoOrdinate+196,Y_CoOrdinate+31),
         CTextFileIO::Sstlanguage[i],false);
		Y_CoOrdinate +=ListBox_OneLineHeight;
		j++;
	}*/
}