/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/VGA.cpp_v   1.3   Jul 25 2005 10:19:20   bwadia  $ */
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
  1.2       05/19/05  Aare        Added complete revision header.
*/

// VGA.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VGA.h"
#include "MainFrame.h"
#include "HostCommand.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVGAApp

BEGIN_MESSAGE_MAP(CVGAApp, CWinApp)
	//{{AFX_MSG_MAP(CVGAApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CVGAApp::CVGAApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVGAApp object


CVGAApp theApp;
int page_no;
bool OnKeypadScreen_flag;

/////////////////////////////////////////////////////////////////////////////
// CVGAApp initialization

BOOL CVGAApp::InitInstance()
{
	if (!AfxSocketInit())
		{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
		}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	InitTasks();
/*	Sleep(1000);
	CHostCommand * req = new CHostCommand(1000, NULL, 0);
	CHostCommand * res = SendUiHostCommand(req);
	delete res;
*/
	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

// This implementation is for VGA only
void CVGAApp::Trace(const CString &str)
{
	TRACE(_T("%s\n"), str);
}
