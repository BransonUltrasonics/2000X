// Buttons.cpp : implementation file
//
/*
Revision #		Date		Author			Description
----------		--------	----------		-------------------------------------
1.0				04/24/06	LAM				Initial Version.
1.1				05/10/07	BSahu			Modified Code to Add View HosrnScan Graphs.
1.2				09/26/09	PDwivedi		Set Default Color text color.
*/

#include "stdafx.h"
#include "History.h"
#include "Buttons.h"
#include "HistoryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_ScanA 21
#define ID_ScanB 22
#define ID_ScanC 23
#define BUTTONCOLOR RGB(236, 233, 216)
/////////////////////////////////////////////////////////////////////////////
// CButtons

CButtons::CButtons()
{
}

CButtons::~CButtons()
{
}


BEGIN_MESSAGE_MAP(CButtons, CButton)
	//{{AFX_MSG_MAP(CButtons)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtons message handlers

/************************************************************/
/*This function is used to change the visual aspect of a	*/
/*ownerdrawn button.										*/
/************************************************************/
void CButtons::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);			//Get device context object
	CRect rt;
	rt = lpDrawItemStruct->rcItem;				//Get button rect
	dc.FillSolidRect(rt, BUTTONCOLOR);	
	UINT state = lpDrawItemStruct->itemState; //Get state of the button

	if ( (state & ODS_SELECTED) )				// If it is pressed
	{
		dc.DrawEdge(rt,EDGE_SUNKEN,BF_RECT);    // Draw a sunken face
	}
	else
	{
		dc.DrawEdge(rt,EDGE_RAISED,BF_RECT);    // Draw a raised face
	}

	dc.SetTextColor(RGB(0,0,0));
	if(ID==ID_ScanA)
		dc.SetTextColor(RGB(0,0,255));
	else if(ID==ID_ScanB)
		dc.SetTextColor(RGB(255,0,0));
	else if(ID==ID_ScanC)
		dc.SetTextColor(RGB(0,255,0));
	else
		dc.SetTextColor(RGB(0,0,0));
	CString strTemp;
	GetWindowText(strTemp);						// Get the caption which have been set
	CFont *OldFont;
	OldFont=dc.SelectObject(&CHistoryView::SmallFont);
	dc.DrawText(strTemp,rt,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	dc.SelectObject(OldFont);
	if ( (state & ODS_FOCUS ) )				// If the button is focused
	{
		int iChange = 3;
		rt.top += iChange;
		rt.left += iChange;
		rt.right -= iChange;
		rt.bottom -= iChange;
		dc.DrawFocusRect(rt);
	}
	dc.Detach();
}
