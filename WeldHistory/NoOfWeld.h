// NoOfWeld.h: interface for the CWNoOfWeld class.
//
//////////////////////////////////////////////////////////////////////

/*
Revision #		Date		Author			Description
----------		--------	----------		-------------------------------------
1.0				10/22/06	BSahu			Initial Version.
*/


#if !defined(AFX_NOOFWELD_H__FF9CE430_5522_45BD_B0BB_F43F308628BE__INCLUDED_)
#define AFX_NOOFWELD_H__FF9CE430_5522_45BD_B0BB_F43F308628BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NoOfWeld.h : header file
//
#include "HistoryView.h"
/////////////////////////////////////////////////////////////////////////////
// NoOfWeld dialog
class CHistoryView;
class NoOfWeld : public CDialog
{
// Construction
public:
	static int EditBoxvalue;
	NoOfWeld(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(NoOfWeld)
	enum { IDD = IDD_DIALOG3 };
	UINT	m_Value;
	//}}AFX_DATA
	CRect UserPage(CDC * pDC, float margin);
	int CreateFontSize(CDC *pdc, int points);
// Overrides;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NoOfWeld)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
POSITION nPrintPos;
	// Generated message map functions
	//{{AFX_MSG(NoOfWeld)
	virtual void OnOK();	
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOOFWELD_H__FF9CE430_5522_45BD_B0BB_F43F308628BE__INCLUDED_)
