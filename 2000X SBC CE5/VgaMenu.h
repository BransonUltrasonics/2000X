// VgaMenu.h: interface for the CVgaMenu class.
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
  1.1       01/11/08    PDwivedi  Added  Members Declartions.
  1.2       06/06/08    PDwivedi  Added  Members Declartions for new Class.
  1.3       09/09/08    PDwivedi  Added changes for tracker issues
*/

#if !defined(AFX_VGAMENU_H__2B0FD33E_4F8D_48B2_84B9_2EFE9F0D8676__INCLUDED_)
#define AFX_VGAMENU_H__2B0FD33E_4F8D_48B2_84B9_2EFE9F0D8676__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ObjectList.h"
#include "VgaMenuItem.h"
#include "Condition.h"
class CXmlElement;

class CVgaMenu  
{
public:
   CVgaMenu();
   void Draw(CDC * pDC) const;
   CVgaMenu(CXmlElement * element);
   virtual ~CVgaMenu();
   const CString & GetName() const
   {
      return name;
   }
   CObjectList<CVgaMenuItem> items;
   enum MENUS 
   {
      BottomMenu_Id=0,
      TITLE = 1,
      TEXT,
      SUBMENU,                       
      HSUBMENU,                     
      HHMM=5,
      DATE,
      CHOICE,
      ALPHA,
      VARIABLE,                           
      RADIO_BUTTON=10,
      RADIOMENU,
      TOGGLE,                      
      HVARIABLE,                  
      ALARM,
      RADIOLARGEMENU=15,                  
      RADIOLARGE,
      SCREENSETUP,
      MENU_END,
      VGATEXT = 19,
      VGATEXTBOX = 20,
      VGALINE = 21,
      VGARUNSCREENOBJECT =22,
      VGA_Button_OBJECT =23,
      VGABottomHalfObject =24,
      VGACheck,
      VGA_GRAPH_OBJECT =26,
      VGA_LISTBOX =27,
      VGAMsgScrnObject,
      VGAPointerObject,
      VGATableObject,
      VGAUSBFolder,

      VGAHISTORYOBJECT,
      COLORSETUP_ID,
      VGA_VGAEXITBUTTON,
      VGA_VGASAVEBUTTON,
      VGA_ALARMBUTTON,
      NEXT=7000,
      BACK=7001,
      VGATOOLMAP
   }MenuType;
   static CVgaMenuItem* CreateObjectBack_Next(int exit_type);
protected:
   void AddSubmenu(CXmlElement * e);
   void AddTitle(CXmlElement * e);
   void AddBottomMenu();
   void AddChoicemenu(CXmlElement * e);
   void AddText(CXmlElement * e);
   void AddTogglemenu(CXmlElement * e);
   void AddRadioMenu(CXmlElement * e);
   void AddVariableMenu(CXmlElement * e); 
   void AddDateMenu(CXmlElement * e);
   void AddTimeMenu(CXmlElement * e);
   void AddVgaButtonMenu(CXmlElement * e);
   void AddVgaRadioButtonMenu(CXmlElement * e);
   void AddMsgScreen(CXmlElement * e);
   void AddListBox(CXmlElement * e);
   void AddAlphaNumeric(CXmlElement * e);
   void AddBottomMenu(CXmlElement *e);
   void AddBottomHalf(CXmlElement * e);
   void AddCheck(CXmlElement * e);
   void AddScreenSetup(CXmlElement * e);
   void AddLine(CXmlElement * e);
   void AddRunMenu(CXmlElement * e);
   void AddHistoryObject(CXmlElement * e);
   void AddTextBoxObject(CXmlElement * e);
   void AddGraphObject(CXmlElement * e);
   void AddTableObject(CXmlElement * e);
   void AddLocalChoiceObject(CXmlElement * e);
   void AddCompareGraph();
   void AddViewPreset();
   void AddAlarmButton(CXmlElement * e);
   void AddHistoryGraph(CXmlElement * e);
   CString name;
};

#endif // !defined(AFX_VGAMENU_H__2B0FD33E_4F8D_48B2_84B9_2EFE9F0D8676__INCLUDED_)
