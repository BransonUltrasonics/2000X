// VgaBottomMenu.h: interface for the CVgaBottomMenu class.
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
  1.1		   04/04/08	   PDwivedi	 Added Member function
  1.2       04/16/08    PDwivedi  Modify Access specifier for Data Member in MultiLang support.
  1.3       08/01/08    PDwivedi  Added Member for storing menuname.
  1.4       08/26/08	   PDwivedi  Modified return type of SendCommandForBottomMenu().
  1.5       11/06/09    PDwivedi  Added changes for showing String Number.
  1.6       10/13/10    PDwivedi  Modified to add ErrorMenuid.
*/

#if !defined(AFX_VGABOTTOMMENU_H__F77EF087_2BF5_43EC_A539_E6D97B828C4B__INCLUDED_)
#define AFX_VGABOTTOMMENU_H__F77EF087_2BF5_43EC_A539_E6D97B828C4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WeldResult_rect CRect(8+XOFFSET,444+YOFFSET,156+XOFFSET,476+YOFFSET)
#define Weldsetup_rect CRect(326+XOFFSET,444+YOFFSET,472+XOFFSET,476+YOFFSET)
#define Graphs_rect CRect(484+XOFFSET,444+YOFFSET,630+XOFFSET,476+YOFFSET)
#define Bottom_MainMenu_rect CRect(168+XOFFSET,444+YOFFSET,314+XOFFSET,476+YOFFSET)
#define Bottom_Menu_Rect CRect(1+XOFFSET,440+YOFFSET,639+XOFFSET,480+YOFFSET)
#include "ChildView.h"
#include "VgaMenuItem.h"
class CXmlElement;

class CVgaBottomMenu : public CVgaMenuItem  
{
public:
   CVgaBottomMenu(int DrawRectonly);
   CVgaBottomMenu();
   virtual ~CVgaBottomMenu();
   static bool pressedbutton;
   static bool SendCommandForBottomMenu(int ID,int Address);
   static void InitializeBottomMenuMembers(CXmlElement * element);
   static CString mainMenuID;
   static CString GraphsMenu_ID;
   static CString WeldSetup_ID;
   static CString WeldResults_ID;
  // CString submenu;
   static int mainMenuCommandID;
   static int GraphsMenu_CommandID;
   static int WeldSetup_CommandID;
   static int WeldResults_CommandID;
   static CString MenuErrorID;
   CString BottomSubmenu;
   static CString mainMenuStringID,GraphsMenuStringID,WeldSetupStringID,WeldResultsStringID;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;
private:

   static bool GraphPressed1;
   static bool MainMenuPressed1;
   static bool WeldSetupPressed1;
   static bool WeldResultPressed1;
};

#endif // !defined(AFX_VGABOTTOMMENU_H__F77EF087_2BF5_43EC_A539_E6D97B828C4B__INCLUDED_)
