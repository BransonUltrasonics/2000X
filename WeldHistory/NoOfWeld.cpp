// NoOfWeld.cpp : implementation file
//
//////////////////////////////////////////////////////////////////////

/*
Revision #		Date		Author			Description
----------		--------	----------		-------------------------------------
1.0				10/22/06	BSahu			Initial Version.
*/
#include "stdafx.h"
#include "History.h"
#include "NoOfWeld.h"

#include "HistoryDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
int NoOfWeld::EditBoxvalue=0;
/////////////////////////////////////////////////////////////////////////////
// NoOfWeld dialog
//CHistoryView *view;

NoOfWeld::NoOfWeld(CWnd* pParent /*=NULL*/)
	: CDialog(NoOfWeld::IDD, pParent)
{
	//{{AFX_DATA_INIT(NoOfWeld)
	m_Value = 0;
	//}}AFX_DATA_INIT
	
}


void NoOfWeld::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NoOfWeld)
	DDX_Text(pDX, IDC_EDIT1, m_Value);
	DDV_MinMaxUInt(pDX, m_Value, 1, 65536);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NoOfWeld, CDialog)
	//{{AFX_MSG_MAP(NoOfWeld)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NoOfWeld message handlers

void NoOfWeld::OnOK() 
{
	EditBoxvalue=GetDlgItemInt(IDC_EDIT1);
	CDialog::OnOK();
}

void NoOfWeld::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL NoOfWeld::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char TempArray[10];
	CString Temp= _itoa(CHistoryView::TotalCycle,TempArray,10);
	GetDlgItem(IDC_STATIC_WELD)->SetWindowText("Total No Of Welds Avaiable = "+ Temp);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

