/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/VGA.h_v   1.3   Jul 25 2005 10:19:20   bwadia  $ */
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

// VGA.h : main header file for the VGA application
//

#if !defined(AFX_VGA_H__8C4E6ACD_AEDC_4E4A_B9F0_0138E81A7B92__INCLUDED_)
#define AFX_VGA_H__8C4E6ACD_AEDC_4E4A_B9F0_0138E81A7B92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Application.h"

/////////////////////////////////////////////////////////////////////////////
// CVGAApp:
// See VGA.cpp for the implementation of this class
//

class CVGAApp : public CApplication
{
public:
	void Trace(const CString & str);
	CVGAApp();

protected:

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVGAApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CVGAApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VGA_H__8C4E6ACD_AEDC_4E4A_B9F0_0138E81A7B92__INCLUDED_)
