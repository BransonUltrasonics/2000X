///////////////////////////////////////
// Browse.cpp : implementation file	//
//////////////////////////////////////
/*
Revision #		Date		Author			Description
----------		--------	----------		-------------------------------------
1.0				04/24/06	LAM				Initial Version.
1.1				05/10/07	BSahu			Modified Code to Add View HosrnScan Graphs.
*/

#include "stdafx.h"
#include "History.h"
#include "Browse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CBrowse::CBrowse(CWnd* pParent /*=NULL*/)
	: CDialog(CBrowse::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBrowse)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CString CBrowse::PSPath;
/*********************************************************/
/*This Function faciliates data exchange between		 */
/*dialog window	and user								 */
/*********************************************************/
void CBrowse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBrowse)
	DDX_Control(pDX, IDOK, m_Ok);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDC_BUTTON1, m_BackButton);
	DDX_Control(pDX, IDC_LIST2, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBrowse, CDialog)
	//{{AFX_MSG_MAP(CBrowse)
	ON_LBN_DBLCLK(IDC_LIST2, OnDblclkList2)
	ON_BN_CLICKED(IDC_BUTTON1, OnBack)
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_LIST2, OnSelchangeList)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////
// CBrowse message handlers		    //
//////////////////////////////////////
/*********************************************************/
/*This Function will initialize/create Dialogwindow		 */
/*********************************************************/
BOOL CBrowse::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	CFont Font;
	Font.CreateFont(26 , 0, 0, 0, FW_NORMAL,FALSE, FALSE, FALSE, 
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FF_DONTCARE, _T("Arial"));
	m_List.SetFont(&Font,false);
	Font.DeleteObject();
	//	m_List.SetHorizontalExtent(200);
	if(CHistoryView::HSMenu)
	{
		this->SetWindowText(_T("Open HS Folder"));
		GetDlgItem(IDC_STATIC_PS)->SetWindowText(_T("Select H/S Folder and Press Open"));
	}
	AddDriveLetters();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/***********************************************************/
/*This Function will Add Drive Letters to the diagol window*/
/***********************************************************/

void CBrowse::AddDriveLetters()
{
	m_BackButton.EnableWindow(false);
	m_Ok.EnableWindow(false);
	FilePath.RemoveAll();
	FileName.RemoveAll();
	int Result =0;
	while(Result!=LB_ERR )
		Result=	m_List.DeleteString(0);

	TCHAR buffer[100];
	int Len=GetLogicalDriveStrings(100,buffer);
	int i=0;
	CString TempStr;
	while(Len)
	{
		if(buffer[i]!=NULL)
			TempStr+=buffer[i];
		else
		{
			m_List.AddString(TempStr);
			FilePath.AddTail(TempStr);
			FileName.AddTail(TempStr);
			TempStr="";
		}
		i++;
		Len--;
	}
}

/*****************************************************/
/*This function is to give functionality to double	 */
/*click event in the dialog window					 */
/*****************************************************/
void CBrowse::OnDblclkList2() 
{
	if(PrepareList())
	{
		m_BackButton.EnableWindow(true);
		m_Ok.EnableWindow(false);
	}
}

/*****************************************************/
/*This function prepare the list of folders present	 */
/*inside a folder									 */
/*****************************************************/

bool CBrowse::PrepareList()
{
	int SelectedItem , i;
	SelectedItem =m_List.GetCurSel();  /* returns Zero base index*/

	if(SelectedItem<0)
		return false;
	CString SelFilePath;
	CString SelFileName;
	POSITION POS1 = FileName.GetHeadPosition();
	POSITION POS = FilePath.GetHeadPosition();

	for(i=0;i<=SelectedItem;i++)
		SelFilePath = FilePath.GetNext(POS);

	TCHAR buf[30];
	SelFileName="";
	int StrLen = m_List.GetText( SelectedItem, buf ) ;
	for(i=0;i<StrLen;i++)
		SelFileName+=(TCHAR)buf[i];
	IsPSFolder = false;
	if(!CHistoryView::HSMenu)
		CheckPSFolder(SelFilePath,BROWSING);

	if( IsPSFolder )
	{
		CHistoryView::FileCreated=true;
		ToOpen() ;
		CHistoryView::FileCreated=false;
		return true;
	}
	else if(CheckHSFolder(SelFilePath,BROWSING))
	{
		CHistoryView::FileCreated=true;
		ToHSOpen();
		CHistoryView::FileCreated=false;
		return true;
	}
	else
		return PrepareList(SelFilePath);
}

/*******************************************************/
/*This function gives the functionality to the OK	   */
/*button in the dialog window						   */
/*******************************************************/	
void CBrowse::OnOK() 
{	
	if(PrepareList())
	{
		m_BackButton.EnableWindow(true);
		m_Ok.EnableWindow(false);
	}
}

/*************************************************************/
/*This function is used to goback to the previous menu       */
/*************************************************************/

void CBrowse::OnBack() 
{
	CString PreviousPath = FilePath.GetHead();
	int x=0;
	while(x!=2)
	{
		if(PreviousPath.GetLength()<=3)
		{
			AddDriveLetters();
			return;
		}
		if(PreviousPath.Right(1)==("\\"))
			x++;
		PreviousPath.Delete(PreviousPath.GetLength()-1,1);
	}
	PrepareList(PreviousPath);
}

/*****************************************************/
/*This function prepare the list of folders present	 */
/*inside a folder									 */
/*****************************************************/

bool CBrowse::PrepareList(CString SelFilePath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CString DirSpec;  
	DirSpec=SelFilePath+_T("\\*");
	hFind = FindFirstFile(DirSpec, &FindFileData);
	DirSpec.Delete(DirSpec.GetLength()-1,1);
	if (hFind == INVALID_HANDLE_VALUE)  
		return false;
	bool ListCreated =false;
	if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&ValidFolder(FindFileData.cFileName))
	{
		FilePath.RemoveAll();
		FileName.RemoveAll();
		int Result =0;
		while(Result!=LB_ERR )
			Result=	m_List.DeleteString(0);

		ListCreated = true;
		m_List.AddString(FindFileData.cFileName);
		FilePath.AddTail(DirSpec+FindFileData.cFileName);
		FileName.AddTail(FindFileData.cFileName);
	}

	while(FindNextFile(hFind, &FindFileData) != 0) 
	{
		if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&ValidFolder(FindFileData.cFileName))
		{
			if(!ListCreated)
			{
				FilePath.RemoveAll();
				FileName.RemoveAll();
				ListCreated = true;
				int Result =0;
				while(Result!=LB_ERR )
					Result=	m_List.DeleteString(0);
			}
			m_List.AddString(FindFileData.cFileName);
			FilePath.AddTail(DirSpec+FindFileData.cFileName);
			FileName.AddTail(FindFileData.cFileName);
		}
	}
	return ListCreated;
}
/*****************************************************/
/* This function Gives color to Dialog window		 */
/*****************************************************/
HBRUSH CBrowse::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

/*****************************************************/
/* This function tests for a valid folder to be      */ 
/*add to the list.									 */
/*****************************************************/
bool CBrowse::ValidFolder(CString FileName)
{
	if((FileName==".")||(FileName==".."))
		return false;
	else
		return true;
}
/*****************************************************/
/* This function calld when a item is selected in	 */
/*the list of dialog window.						 */
/*****************************************************/
void CBrowse::OnSelchangeList() 
{
	m_Ok.EnableWindow(true);
}

/*****************************************************/
/* This function checks wether there is a power		 */
/*supply folder present inside the selected folder	 */ 
/*or not.											 */
/*****************************************************/

bool CBrowse::CheckPSFolder(CString SelFilePath,enum Hier TempHierarchy)
{
	if(TempHierarchy==HIERARCHYDAY)
	{
		CString Path=SelFilePath + "\\WeldData.log";
		CFile fp;
		CFileException e;
		if( fp.Open( Path, CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
		{
			if(fp.GetLength())
				fp.Close();
			IsPSFolder=true;
			return true;
		}
		else
			return false;
	}

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CString DirSpec;  
	DirSpec=SelFilePath+_T("\\*");
	hFind = FindFirstFile(DirSpec, &FindFileData);
	DirSpec.Delete(DirSpec.GetLength()-1,1);
	if (hFind == INVALID_HANDLE_VALUE)  
		return false;
	enum Hier TempHierarchy2;
	if(TempHierarchy==BROWSING)
		TempHierarchy2=HIERARCHYYEARMONTH;
	else if (TempHierarchy==HIERARCHYYEARMONTH)
		TempHierarchy2=HIERARCHYDAY;

	if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&ValidFolder(FindFileData.cFileName,TempHierarchy2))
	{
		CString Path =SelFilePath+"\\"+FindFileData.cFileName;
		CheckPSFolder(Path,TempHierarchy2);
	}

	while(FindNextFile(hFind, &FindFileData) != 0) 
	{
		if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&ValidFolder(FindFileData.cFileName,TempHierarchy2))
		{
			CString Path =SelFilePath+"\\"+FindFileData.cFileName;
			CheckPSFolder(Path,TempHierarchy2);	
		}
	}
	return false;
}

/*****************************************************/
/* This function checks wether the selected folder 	 */
/*cointain a power supply folder or not.			 */
/*****************************************************/

bool CBrowse::ValidFolder(CString FileName,enum Hier TempHierarchy1)
{
	if((FileName==".") ||(FileName==".."))
	return false;

	switch(TempHierarchy1)
	{
	case BROWSING:
		{
			return true;
			break;
		}
	case HIERARCHYYEARMONTH:
		{
			if(FileName.GetLength()!=YEARMONTHFOLDERNAME)
				return false;
			for(int i=0;i<YEARMONTHFOLDERNAME;i++)
			{	
				if(i!=4)
				{
					if(!((FileName.Mid(i,1)[0]<=0x39) && (FileName.Mid(i,1)[0]>=0x30)))
						return false;
				}
			}
			if(FileName.Mid(4,1)!="_")
				return false;
			else
				return true;
			break;
		}
	case HIERARCHYDAY:
		{
			if(FileName.GetLength()!=DATESIZE)
				return false;
			char TempCh0 = FileName.Mid(0,1)[0];
			char TempCh1 = FileName.Mid(1,1)[0];
			if(!((TempCh0<=0x33) && (TempCh0>=0x30)))
				return false;
			if(((TempCh0==0x33) && (TempCh1>=0x32)))
				return false;
			if(!((TempCh1<=0x39) && (TempCh1>=0x30)))
				if(!((TempCh0<0x33)))
					return false;
			return true;
			break;
		}
	}
	return false;
}

/*****************************************************/
/* This function called when the selected folder is a*/
/*power supply folder to open that.					 */
/*****************************************************/

void CBrowse::ToOpen()
{	
	int SelectedItem, i ;
	SelectedItem =m_List.GetCurSel();  /* returns Zero base index*/
	if(SelectedItem<0)
		return ;
	CString SelFilePath;
	CString SelFileName;
	POSITION POS1 = FileName.GetHeadPosition();
	POSITION POS = FilePath.GetHeadPosition();

	for(i=0;i<=SelectedItem;i++)
		SelFilePath = FilePath.GetNext(POS);

	TCHAR buf[30];
	SelFileName="";
	int StrLen = m_List.GetText( SelectedItem, buf ) ;
	for(i=0;i<StrLen;i++)
		SelFileName+=(TCHAR)buf[i];   

	CHistoryView::PreviousFileName=SelFileName.SpanExcluding(_T("-"));
	CHistoryView::View->BrowsingLevel = CHistoryView::HIERARCHYYEARMONTH;

	if(CHistoryView::View->BrowsingLevel == CHistoryView::HIERARCHYYEARMONTH)
		CHistoryView::PSName=CHistoryView::PreviousFileName;

	if(!CHistoryView::PreparePSList(SelFilePath))
	{
		CHistoryView::View->BrowsingLevel=CHistoryView::BRANSONLOGO;
		return;
	}
	CDialog::OnOK();
}

bool CBrowse::CheckHSFolder(CString SelFilePath, enum Hier TempHierarchy)
{
	if(TempHierarchy==HIERARCHYHSFOLDER)
	{
		CString Path=SelFilePath + "\\Horn Signature";
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		CString DirSpec;  
		DirSpec=Path+_T("\\*");
		hFind = FindFirstFile(DirSpec, &FindFileData);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			CHistoryView::HSFolderPath =Path;
			return true;
		}
	}


	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	CString DirSpec;  

	DirSpec=SelFilePath+_T("\\*");
	hFind = FindFirstFile(DirSpec, &FindFileData);
	DirSpec.Delete(DirSpec.GetLength()-1,1);
	if (hFind == INVALID_HANDLE_VALUE)  
		return false;
	if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&(CHistoryView::HSMenu))
	{
		CFile fp;
		CFileException e;
		CFile fp1;
		CFileException e1;
		CFile fp2;
		CFileException e2;
		CString Path=SelFilePath + "\\Horn Signature";
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		CString DirSpec;
		DirSpec=Path+_T("\\*");
		hFind = FindFirstFile(DirSpec, &FindFileData);
		if ((hFind == INVALID_HANDLE_VALUE))
			CheckHSFolder(Path,BROWSING);
		else
		{
			CHistoryView::HSFolderPath =Path;
			CString Path1=Path + "\\HornScanA.txt";
			if( fp.Open( Path1, CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
			{
				if(fp.GetLength())
					fp.Close();
				IsScanA=true;
			}
			CString Path2=Path + "\\HornScanB.txt";
			if( fp1.Open( Path2, CFile::modeNoTruncate |CFile::modeReadWrite , &e1 ) )
			{
				if(fp1.GetLength())
					fp1.Close();
				IsScanB=true;
			}
			CString Path3=Path + "\\HornScanC.txt";
			if( fp2.Open( Path3, CFile::modeNoTruncate |CFile::modeReadWrite , &e2 ) )
			{
				if(fp2.GetLength())
					fp2.Close();
				IsScanC=true;
			}
			if((IsScanA)||(IsScanB)||(IsScanC))
				return true;
			else
				return false;
		}
	}
	return false;
}

void CBrowse::ToHSOpen()
{
	int SelectedItem , i;
	SelectedItem =m_List.GetCurSel();  /* returns Zero base index*/
	if(SelectedItem<0)
		return ;

	CString SelFilePath;
	CString SelFileName;
	POSITION POS1 = FileName.GetHeadPosition();
	POSITION POS = FilePath.GetHeadPosition();
	for(i=0;i<=SelectedItem;i++)
		SelFilePath = FilePath.GetNext(POS);
	TCHAR buf[30];
	SelFileName="";
	int StrLen = m_List.GetText( SelectedItem, buf ) ;
	for(i=0;i<StrLen;i++)
		SelFileName+=(TCHAR)buf[i];   
	CHistoryView::PreviousFileName=SelFileName.SpanExcluding(_T("-"));
	CHistoryView::View->BrowsingLevel = CHistoryView::HIERARCHYHSFOLDER;
	if(CHistoryView::View->BrowsingLevel == CHistoryView::HIERARCHYHSFOLDER)
		CHistoryView::PSName=CHistoryView::PreviousFileName;
	if(!CHistoryView::PrepareHSList(SelFilePath))
	{
		CHistoryView::View->BrowsingLevel=CHistoryView::BRANSONLOGO;
		return;
	}
	CDialog::OnOK();
}