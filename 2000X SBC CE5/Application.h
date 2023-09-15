/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/Application.h_v   1.9   Feb 07 2006 17:44:12   bwadia  $ */
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
  1.5       05/19/05	 Aare        Added complete revision header.
  1.6		07/25/05	BWadia		Added SendPolling,SendUI,SendEnHostCommand Functions.
  1.7		09/19/05	Bwadia		Updated GetBottomMenuAddress Function.
  1.8		02/07/06	BWadia		Made variable ether to public
*/


#if !defined(AFX_APPLICATION_H__C3A98B50_A3AB_4F4A_B9AD_E04D1E17BFB0__INCLUDED_)
#define AFX_APPLICATION_H__C3A98B50_A3AB_4F4A_B9AD_E04D1E17BFB0__INCLUDED_

#include "resource.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Application.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CApplication

class CCommPort;
class CEtherPort;
class CHostCommand;

class CApplication : public CWinApp
{
public:
	void SendWeldData(unsigned char *&data,int length);
	CHostCommand * SendEnHostCommand(CHostCommand *request);

	CHostCommand * SendUiHostCommand(CHostCommand * request);
	CHostCommand * SendPollingHostCommand(CHostCommand * request);
	virtual void Trace(const CString & str) = 0;
	bool GetBottomMenuAddress(bool *Start_Screen,int *WeldResults_Address,int *mainMenuAddress,int *WeldSetup_Address,int *GraphsMenu_Address,int *Langauage_Index,bool *metric);
	CEtherPort * ether;
protected:
	void InitTasks();
	CCommPort * com;
	

	CApplication();
	enum 
	{
		ACK = 0x06,
		NAK = 0x15
	};
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApplication)
	public:
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
	// Generated message map functions
	//{{AFX_MSG(CApplication)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CApplication * app;
extern int page_no;
extern bool OnKeypadScreen_flag;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLICATION_H__C3A98B50_A3AB_4F4A_B9AD_E04D1E17BFB0__INCLUDED_)
