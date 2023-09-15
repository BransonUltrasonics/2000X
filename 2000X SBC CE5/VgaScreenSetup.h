// VgaScreenSetup.h: interface for the CVgaScreenSetup class.
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
  1.1		   04/04/08	PDwivedi  Added Member variables .
  1.2       11/06/09 PDwivedi  Added changes for showing String Number.
  
*/

#if !defined(AFX_VGASCREENSETUP_H__D51B287E_140B_4F98_85E4_1219CDDBAEF1__INCLUDED_)
#define AFX_VGASCREENSETUP_H__D51B287E_140B_4F98_85E4_1219CDDBAEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "VgaMenuItem.h"
#include "ChildView.h"

#define ScrnCalibButtonLabel1_rect CRect(40,384,50,394)
#define ScrnCalibButtonLabel2_rect CRect(586,87,596,97)
#define ScrnCalibButton2_rect CRect(564,16,624,76)
#define ScrnCalibDot2_rect CRect(586,40,596,50)
#define ScrnCalibButton2_BoundingRect CRect(563,15,625,77)
#define ScrnCalibButton1_rect CRect(16,404,76,464)
#define ScrnCalibDot1_rect CRect(40,428,50,438)
#define ScrnCalibButton1_BoundingRect CRect(15,403,77,465)
#define StrTouchButton2_rect CRect(0,200,640,240)/* x made to 200 instead of 160*/
#define StrTouchButton1_rect CRect(0,200,640,240)/* x made to 200 instead of 160*/
#define StrScrnAlign_rect CRect(0,160,640,200)
#define DoneButton_Rect CRect(235,200,405,240)
#define Color_Setup_Rect CRect(235,274,405,314)
#define ExitButton_Rect CRect(X_CORDINATE_BACK_NEXT,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)

class CXmlElement;

class CVgaScreenSetup : public CVgaMenuItem  
{
public:
   static float DY1;
	static float DX1;
	virtual void Draw(CDC *pDC);
   static void SetScreenMemberVariable(CXmlElement * e);
	CVgaScreenSetup();
	virtual ~CVgaScreenSetup();
	static CString Str_ScreenSetup,Str_TouchButton1,Str_TouchButton2,Str_ScrnAlign,Str_Done,Str_Exit;
   static CString Str_ScreenSetupID,Str_TouchButton1ID,Str_TouchButton2ID,
      Str_ScrnAlignID,Str_DoneID,Str_ExitID;

protected:
	virtual bool MouseClick(const CPoint &p, CChildView *view);
private:
	int lang_index;
	static struct CalibCordinate{
		int Xa;
		int Ya;
		int Xb;
		int Yb;
	};
	static bool button_1_pressed1;
	static bool button_2_released1;
	static bool Exit_pressed1;
	static bool Done_pressed1;
};

#endif // !defined(AFX_VGASCREENSETUP_H__D51B287E_140B_4F98_85E4_1219CDDBAEF1__INCLUDED_)
