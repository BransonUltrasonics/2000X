// HistoryDoc.h : interface of the CHistoryDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTORYDOC_H__CA366B66_7C24_46B8_9DE7_290ACB7D4B27__INCLUDED_)
#define AFX_HISTORYDOC_H__CA366B66_7C24_46B8_9DE7_290ACB7D4B27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "HistoryView.h"

class CHistoryView;
class CHistoryDoc : public CDocument
{
protected: // create from serialization only
	CHistoryDoc();
	DECLARE_DYNCREATE(CHistoryDoc)

// Attributes
public:

// Operations
public:
	static CHistoryView* View;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistoryDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	//virtual void OnCloseDocument( );
	virtual ~CHistoryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	

// Generated message map functions
protected:
	//{{AFX_MSG(CHistoryDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORYDOC_H__CA366B66_7C24_46B8_9DE7_290ACB7D4B27__INCLUDED_)
