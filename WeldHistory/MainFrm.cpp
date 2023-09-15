////////////////////////////////////////////////////////////
// MainFrm.cpp : implementation of the CMainFrame class	  //
////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "History.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//////////////////////////////////
// CMainFrame					//
//////////////////////////////////
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////
// CMainFrame construction/destruction//
////////////////////////////////////////
CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{

}
/****************************************************************/
/*This function is called by the framework before the creation	*/  
/*of the window. And modify the CREATESTRUCT structure before	*/
/*the window is created. 										*/
/****************************************************************/
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	
	//  the CREATESTRUCT cs
	////|WS_THICKFRAME WS_OVERLAPPED  | WS_BORDER | 
	cs.style = WS_BORDER|WS_SYSMENU |WS_MINIMIZEBOX; 
	cs.cy = 536;
    cs.cx =650;
    cs.y = (::GetSystemMetrics(SM_CYSCREEN)- cs.cy) / 2;
    cs.x = (::GetSystemMetrics(SM_CXSCREEN) - cs.cx) / 2;

	//cs.dwExStyle=WS_EX_STATICEDGE;
	//cs.style=WS_TABSTOP|WS_VISIBLE|WS_SYSMENU|WS_MINIMIZEBOX ;

	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;

	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

////////////////////////////////////////
// CMainFrame diagnostics			  //
////////////////////////////////////////
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}
/************************************************************/
/*This function Dumps the contents of your object to a		*/
/*CDumpContext object.										*/
/************************************************************/
void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
	
}

#endif //_DEBUG




























