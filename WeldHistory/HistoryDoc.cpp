// HistoryDoc.cpp : implementation of the CHistoryDoc class
//

#include "stdafx.h"
#include "History.h"

#include "HistoryDoc.h"
#include "HistoryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistoryDoc

IMPLEMENT_DYNCREATE(CHistoryDoc, CDocument)

BEGIN_MESSAGE_MAP(CHistoryDoc, CDocument)
	//{{AFX_MSG_MAP(CHistoryDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistoryDoc construction/destruction

CHistoryView* CHistoryDoc::View;

CHistoryDoc::CHistoryDoc()
{

	// TODO: add one-time construction code here

}

CHistoryDoc::~CHistoryDoc()
{
}

BOOL CHistoryDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}
//void CHistoryDoc::OnCloseDocument( )
//{
//	DeleteContents();

//}


/////////////////////////////////////////////////////////////////////////////
// CHistoryDoc serialization
void CHistoryDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		//View->ReadData(ar);
	// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHistoryDoc diagnostics

#ifdef _DEBUG
void CHistoryDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHistoryDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHistoryDoc commands


