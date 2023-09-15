/* $Header:   D:/databases/VMdb/archives/2000 RVTS/SBC.h_v   1.12   Oct 23 2017 16:32:20   RCHAPA  $ */
/* ************************************************************************** */ 
/*                                                                            */
/*                                                                            */
/*      Copyright (c) Branson Ultrasonics Corporation, 2005                   */
/*     This program is the property of Branson Ultrasonics Corporation        */
/*   Copying of this software is expressly forbidden, without the prior       */
/*   written consent of Branson Ultrasonics Corporation.                      */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/* ************************************************************************** */ 
/*
Revision #    Date      Author    Description
----------  --------  ----------  -------------------------------------
  1.1       05/19/05  Aare        Added complete revision header.
  1.3       03/27/07  BSahu       Added HANDLE hProcess For VQS Application
  1.4       10/23/07  PDwivedi    Added Headers,Declarations for Multilang Support . 
  1.5       01/11/08  PDwivedi    Added Variable declartions.   
  1.6       04/14/08  PDwivedi    Added GetVQSWindow  function declartions. 
  1.7       06/06/08  PDwivedi	 Added Variable declartions. 
  1.8       08/01/08  PDwivedi    Added Functions Adding Strings in list.
  1.9       09/24/08  PDwivedi    Removing  OnLinePrintLookUpMenu Variable.
  1.10      10/07/09  PDwivedi    Added function to display MessageBox in Exception Handling.

*/

// SBC.h : main header file for the SBC application
//

#if !defined(AFX_SBC_H__89F7163D_8049_4414_B1E2_80499808B46F__INCLUDED_)
#define AFX_SBC_H__89F7163D_8049_4414_B1E2_80499808B46F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Application.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSBCApp:
// See SBC.cpp for the implementation of this class
//
void AfxMsgBox(CString x);
class CXmlElement;
#include "Variable.h"
#include "VgaMenu.h"
#include "ObjectMap.h"
#include "XmlFile.h"
#include "TextIOFile.h"
#include "VgaDrawGraph.h"

class CSBCApp : public CApplication
{
public:
//   CMapStringToString OnLinePrintLookUpMenu;
   CTypedPtrList<CPtrList, CVgaDrawGraph *> GraphsDataList;
   void GetVQSWindow();
   int TotalLangElement;
   void PrepareFunctionMapTable();
   CTextFileIO *configFile;
   CStringArray SpecialMenu;
   CVgaMenu *MenuPointer;
   int total;
   void PrepareStringFromUnicodeText(CString Str,bool FirstTime,bool skipFirstLine);
   void GetSystemVariable();
   void SetMicronsUpdate();
   void Trace(const CString & str);
   CSBCApp();
   virtual ~CSBCApp();
   static HANDLE hProcess;
   void Clean();
   CObjectMap<CVariable> variables;
   void CreateMenu(CXmlElement * element);
   void CreateBitVariable(CXmlElement * element);
   void CreateEnumVariable(CXmlElement * element);
   void CreatePrintStrings(CXmlElement * element);
   void CreateAlarmStrings(CXmlElement * element);
   void CreateAlarmEng(CXmlElement * element);
   void CreatePresetString(CXmlElement * element);
   void CreateLabelStrings(CXmlElement * element);
   void CreateManualGraph(CXmlElement * element);
   void CreateGraphPrText(CXmlElement * element);
   void CreateHSInfoText(CXmlElement *e);
   void ParseXmlTree(CXmlElement * gui);
   void CreateMonthStrings(CXmlElement *e);
   //void CreateSpecialMenu(CXmlElement * gui);
   CXmlFile file;
   CXmlElement * gui;
   CObjectMap<CVgaMenu> menus;
   CString menuName;
   CVariable * GetVariable(const CString & varName) const;
   void DrawMenu(CDC * pDC);
   bool ReadXML();
   bool ReadXML_ReloadStartScreen();   
   enum 
   {
      ACK = 0x06,
      NAK = 0x15
   };
protected:
   bool logOpen;
   CSocket log;
   CMutex logMutex;
   CStringList logData;

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CSBCApp)
   public:
   virtual BOOL InitInstance();
   virtual int ExitInstance();
   //}}AFX_VIRTUAL
   //{{AFX_MSG(CSBCApp)
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

extern CSBCApp theApp;
extern CMapStringToPtr functionCall;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SBC_H__89F7163D_8049_4414_B1E2_80499808B46F__INCLUDED_)
