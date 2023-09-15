#if !defined(AFX_BUTTONS_H__47D6868D_1709_47EB_95B6_0EC84C3176AF__INCLUDED_)
#define AFX_BUTTONS_H__47D6868D_1709_47EB_95B6_0EC84C3176AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Buttons.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButtons window
/*
Revision #		Date		Author			Description
----------		--------	----------		-------------------------------------
1.0				04/24/06	LAM				Initial Version.
1.1				05/10/07	BSahu			Modified Code to Add View HosrnScan Graphs.
*/

class CButtons : public CButton
{
// Construction
public:
	CButtons();
	int ID;
	
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtons)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CButtons();

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtons)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONS_H__47D6868D_1709_47EB_95B6_0EC84C3176AF__INCLUDED_)
