#if !defined(AFX_BROWSE_H__10EB8ECF_35D8_46FD_8A31_55A796B68EB8__INCLUDED_)
#define AFX_BROWSE_H__10EB8ECF_35D8_46FD_8A31_55A796B68EB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Browse.h : header file
//
#include "Buttons.h"
#include "HistoryView.h"
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CBrowse dialog
/*
Revision #		Date		Author			Description
----------		--------	----------		-------------------------------------
1.0				04/24/06	LAM				Initial Version.
1.1				05/10/07	BSahu			Modified Code to Add View HosrnScan Graphs.
*/
class CBrowse : public CDialog
{
// Construction
public:
	void ToHSOpen();
	
	void ToOpen();
	bool IsPSFolder;
		enum Hier{
			BRANSONLOGO,
			BROWSING,
			HIERARCHYYEARMONTH,
			HIERARCHYDAY,				
			WELDDATA,
			GRAPHS,
			HIERARCHYHSFOLDER,
			HIERARCHYHSDATA,
			HIERARCHYHSGRAPH
		}TempLevel;
	bool CheckHSFolder(CString SelFilePath,enum Hier TempHierarchy);
	bool CheckPSFolder(CString SelFilePath,enum Hier TempHierarchy);
	bool ValidFolder(CString FileName,enum Hier TempHierarchy1);
	bool ValidFolder(CString FileName);
	bool PrepareList(CString SelFilePath);
	bool IsScanA,IsScanB,IsScanC;
	CBrowse(CWnd* pParent = NULL);   // standard constructor
	

// Dialog Data
	//{{AFX_DATA(CBrowse)
	enum { IDD = IDD_DIALOG1 };
	CButtons	m_Ok;
	CButtons	m_Cancel;
	CButtons	m_BackButton;
	CListBox	m_List;
	//}}AFX_DATA
	CStringList FilePath;
	CStringList FileName;
	static CString PSPath;
	bool PrepareList();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowse)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void AddDriveLetters();
	// Generated message map functions
	//{{AFX_MSG(CBrowse)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList2();
	virtual void OnOK();
	afx_msg void OnBack();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSE_H__10EB8ECF_35D8_46FD_8A31_55A796B68EB8__INCLUDED_)
