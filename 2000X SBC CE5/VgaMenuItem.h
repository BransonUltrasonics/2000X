// VgaMenuItem.h: interface for the CVgaMenuItem class.
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
  1.1       01/11/08    PDwivedi  Added Member Declarations.
  1.2		   04/04/08	   PDwivedi	 Added Member Declarations.
  1.3       08/08/08    PDwivedi  Final Code Clean up.
  1.4       09/09/08    PDwivedi  Added changes for string Debug Menu.
  1.5       09/12/08    PDwivedi  Added changes for Tracker issues of round 2 testing for version LangTestJ.
  1.5.1.0   01/25/10    PDwivedi  Added changes for Japanese Font Issue.

*/

#if !defined(AFX_VGAMENUITEM_H__D7A13375_8A9D_49BD_BEE9_E2F7A59943FD__INCLUDED_)
#define AFX_VGAMENUITEM_H__D7A13375_8A9D_49BD_BEE9_E2F7A59943FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _WIN32_WCE
#define XOFFSET 5
#define YOFFSET 5
#else
#define XOFFSET 0
#define YOFFSET 0
#endif

#define VGA_PASSWORD 01
#define SaveScanA	10
#define SaveScanB	11	
#define SaveScanC	12
#define PasswordCommand 54
#define SECSTRINDEX		1

#define SmallFont	            00			/* Small Font to Display.  */
#define Bigfont	      	   01			/* Big Font to Display.    */
#define PrintSmallFont  	   02		/* Small Font for printing.*/
#define PrintBigFont	         03		/* Big Font for printing.  */
#define PrintWeldDataFont     04
#define PrintWeldDataSmallFont 05
#define EpsonPrintSmallFont   5		/* Small Font for printing.*/
#define EpsonPrintBigFont	   6		/* Big Font for printing.  */
#define EpsonPrintWeldDataFont 7

#define European			   0
#define SmplifiedChinese	01
#define TraditionalChinese	02
#define Japanese			   03
#define Korean				   04

#define Asian_Language_Start     04
#define VGA_Button_Start	      4095
#define Back_Next_Button_Start   6999

#include "ObjectList.h"
#include "Condition.h"
//#include "ChildView.h"
class CXmlElement;
class CChildView;
class CVgaMenuItem  
{
public:
   static void DrawPrinterText(CDC *pDC, int FontSize, int color,
			  const CRect &rect, const CString &text,bool Center_Text, int Lang_Index);
   static CString LinearSearch(CString Identifier);
   static void GetCharString(unsigned char *&data, int &length, TCHAR *Str);
   static int Convert_Char_To_Integer(unsigned char *&data, int &length, int Bytes);
   static CString GetString(unsigned char *&data, int &length);
   static CString RemoveNull(CString str);
   
   
   bool IsDraw;
   CVgaMenuItem();
   virtual ~CVgaMenuItem();
   static bool Japaneseflag;
   virtual void SetRect(const CRect & rect);
   virtual void Draw(CDC * pDC) = 0;
   virtual void DrawItem(CDC * pDC);
   virtual bool MouseClick(const CPoint &p, CChildView *view) = 0;
   static void DrawRect(CDC *pDC, int colour, const CRect &rect);
   static void DrawText(CDC * pDC, int FontSize, int color, const CRect &rect, const CString &text,bool Center_Text);
   static CFont fontArray[2];
   static CPen penBlack1;
   static CPen penDark_Gray1;
   static CPen penWhite1;
   void SetSelectedState(bool state);
   int GetRadio_Value();
   bool GetSelectedRadio();
   void SetType(int type);
   int ObjectPageNum;
   int objectType;
   int GetType() const;
   void SetPageNum(int PageNum);
   int GtPageNum();
   int PSType;
   	static int VGAPointer;
   enum PAGENUMBER
   {
      PAGEALL=0,
      PAGEONE=1,
      PAGETWO,
      PAGETHREE,
      PAGEFOUR,
      PAGEFIVE,
      PAGESIX
   }PageNumber;

   enum MENUS {
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

	NEXT=7000,
	BACK=7001
		}MenuType;
 
  const CRect & GetRect() const;
   
   void Draw_Pressed_Released_Button(CDC *pDC);
   void SetButtonState1(bool pressedState);
   bool GetButtonState1();
   CObjectList<CCondition> conditions;
   CString text;
   int EnumID;
   int RectShow;
   CRect rect;
   int AccessLevel;
   int ModeSet;
   enum 
   {
      ACK = 0x06,
      NAK = 0x15
   };
   CString GetText();
   void SetText(CString String);
   CString textID;
protected:
//   virtual bool CheckConditions() const;
   
   bool pressed1;
   static bool initialized;
   void AddCondition(CXmlElement * element);
 
   CString functionName;
 
};

#endif // !defined(AFX_VGAMENUITEM_H__D7A13375_8A9D_49BD_BEE9_E2F7A59943FD__INCLUDED_)
