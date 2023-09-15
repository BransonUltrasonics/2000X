/* $Header:   D:/databases/VMdb/archives/2000 RVTS/SBC.cpp_v   1.21.1.1.1.1   Oct 23 2017 15:55:52   RCHAPA  $ */
/* ************************************************************************** */ 
/*                                                                            */
/*                                                                            */
/*      Copyright (c) Branson Ultrasonics Corporation, 2005                   */
/*     This program is the property of Branson Ultrasonics Corporation        */
/*   Copying of this software is expressly forbidden, without the prior       */
/*   written consent of Branson Ultrasonics Corporation.                      */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/* ************************************************************************** */ 
/*
Revision #    Date      Author    Description
----------  --------  ----------  -------------------------------------
  1.3       05/19/05  Aare        Added complete revision header.
  1.5       03/27/07  BSahu       Modified InitInstance() For Launching VQS Application
  1.6       04/24/07  BSahu       Modified InitInstance() For VQS Application
  1.7       10/23/07  PDwivedi    Added changes for MultiLang Support.
  1.8       01/11/08  PDwivedi    Modified Clean(),Enable VQS App. 
  1.9		   04/04/08  PDwivedi	 Modified ParseXmltree Function.	
  1.10      04/14/08  PDwivedi	 Modified InitInstance() & define new GetVQSWindow Function.	
  1.11      04/16/08  PDwivedi    Modified GetVQSWindow() function for MultiLanSupport.
  1.12      06/06/08  PDwivedi	 Added new Function in Map Table. 
  1.13      06/12/08  PDwivedi	 Modify ReadXml for selecting start screen & PrepareFunctionMapTable for changing type of function argument.
  1.14      08/01/08  PDwivedi    Added new Function in Map Table & Modify ParseXml.
  1.15      08/04/08  PDwivedi    Added new Function for color setup.
  1.16      08/08/08  PDwivedi    Final Code Clean up.
  1.17      08/26/08  PDwivedi    Added new function defination.
  1.18      09/02/08  PDwivedi    Added new function for BottomHalf Screen.
  1.19      09/12/08  PDwivedi    Added changes for Tracker issues of round 2 testing for version LangTestJ.
  1.20      09/24/08  PDwivedi    Adding Sequencing flag in startup.
  1.21      09/22/09  PDwivedi    Modify GetSysVariable() for Micro Actuator.
  1.21      10/07/09  PDwivedi    Added function to display MessageBox in Exception Handling.
  1.22      10/13/10  PDwivedi    Added new Member like AddStartUpVersion,AddSystemVersion and
                                  and GetNKBinDate in map.
  1.23      09/20/17  RChapa      Added function to Reload Start_Screen at Estop Reset                                  
*/

// SBC.cpp : Defines the class behaviors for the application.

#include "stdafx.h"
#include "SBC.h"
#include "ChildView.h"
#include "MainFrame.h"
#include "XmlElement.h"
#include "EnumVariable.h"
#include "BitmaskVariable.h"
#include "HostCommand.h"
#include "VgaMenu.h"
#include "Text.h"
//#include "ExcelCvt.h"
#include "VgaBottomMenu.h"
#include "LocalChoice.h"
#include "Toggle.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MICRONS_COLUMN_PKPWR 2
#define MICRONS_COLUMN_AMPA  10
#define MICRONS_COLUMN_AMPB  11

CList<CString,CString> tempList;
CList<CString,CString> tempWeldList;
CList<CString,CString> tempHistoryList;
CList<CString,CString> tempGraphsList;
CList<CString,CString> tempScreenGraphsList;
CList<CString,CString> tempHornScanList;
CList<CString,CString> tempScanGraphDataList;
CList<CString,CString> tempSetupList;
CList<CString,CString> tempDUPSList;
CList<CString,CString> tempSequenceList;
CList<CString,CString> tempRunScreenList;
/////////////////////////////////////////////////////////////////////////////
// CSBCApp

BEGIN_MESSAGE_MAP(CSBCApp, CApplication)
	//{{AFX_MSG_MAP(CSBCApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSBCApp construction
/////////////////////////////////////////////////////////////////////////////
CSBCApp::CSBCApp()
{
	logOpen = false;
   gui = 0;
   total=0;
   menuName = "Language Menu";
	TotalLangElement=0;
}

CSBCApp::~CSBCApp()
{
	//logOpen = false;
	if(!tempList.IsEmpty())
	{	tempList.RemoveAll();
	}

	if(!tempWeldList.IsEmpty())
	{	tempWeldList.RemoveAll();
	}

	if(!tempHistoryList.IsEmpty())
	{	tempHistoryList.RemoveAll();
	}

	if(!tempGraphsList.IsEmpty())
	{	tempGraphsList.RemoveAll();
	}
	
	if(!tempScreenGraphsList.IsEmpty())
	{	tempScreenGraphsList.RemoveAll();
	}

	if(!tempHornScanList.IsEmpty())
	{	tempHornScanList.RemoveAll();
	}

	if(!tempScanGraphDataList.IsEmpty())
	{	tempScanGraphDataList.RemoveAll();
	}

	if(!tempSetupList.IsEmpty())
	{	tempSetupList.RemoveAll();
	}

	if(!tempDUPSList.IsEmpty())
	{	tempDUPSList.RemoveAll();
	}

	if(!tempSequenceList.IsEmpty())
	{	tempSequenceList.RemoveAll();
	}

	if(!tempRunScreenList.IsEmpty())
	{	tempRunScreenList.RemoveAll();
	}

   if(gui)delete gui;
  // ExitInstance();
}

// The one and only CSBCApp object

CSBCApp theApp;
int page_no;
bool OnKeypadScreen_flag;
HANDLE CSBCApp::hProcess=NULL;
CMapStringToPtr functionCall;

extern bool USBCheckFunction(CVgaButton *);
extern bool RefreshCheck(CVgaButton *);
extern void ExitSystemProgram(int Address);
extern void ExitColorMenu(int Address);
extern void ButtonColor(int Address);
extern void BackgroundColor(int Address);
extern void DefaultColor(int Address);
extern void TextColor(int Address);
extern void TitleColor(int Address);
extern void HighLightColor(int Address);
extern void ShowQualityScreen(int Address);
extern CString GetIPAddress(CString str);
extern void HandleVGASaveButton(int Address);
extern void SendCommandForVGAButtonsPreset(int Address);
extern void SendCommandForRecallPreset(int Address);
extern void BuildLocalScreenSetupMenu(int Address);
extern void HistoryLeftButton(int Address);
extern void HistoryRightButton(int Address);
extern void HistoryScreenUpButton(int Address);
extern void HistoryUpButton(int Address);
extern void SendCommandForVGAButtonsSavePreset(int Address);
extern void HistoryDownButton(int Address);
extern void ShowPowerSupplyMessageScreen(int Address);
extern void HistoryScreenDownButton(int Address);
extern void GraphRefresh(int Address);
extern void Color_DistanceGraph(int Address);
extern void Power_Graph(int Address);
extern void Frequency_Graph(int Address);
extern void ExitGraphMenu(int Address);
extern void ExitBandLimitsMenu(int Address);
extern void Amplitude_Graph(int Address);
extern void Velocity_Graph(int Address);
extern void Force_Graph(int Address);
extern void ExitAlarmMenu(int Address);
extern void AlarmErrorBeep(int Address);
extern void ProcessColorSetup(int Address);
//extern void ProcessPollingTimeMsgScrn(int Address);
extern void ExitWindowProgram(int Address);
extern void WeldHistoryPrintNow(int Address);
extern void AbortPrinting(int Address);
extern void GraphsWeldNow(int Address);
extern void WeldDataPrintNow(int Address);
extern void PrintScanGraph(int Address);
extern void PrintScanData(int Address);
extern void PrintScreenGraphs(int Address);
extern void HornScanPrint(int Address);
extern void SetUpPrintNow(int Address);
extern void PrintDUPSSetup(int Address);
extern void SequencingPrintNow(int Address);
extern void GetPrinterStatus(int Address);
extern void ForceGraphPrintSample(int Address);
extern void DistanceGraphPrintSample(int Address);
extern void AmplitudeGraphPrintSample(int Address);
extern void PowerGraphPrintSample(int Address);
extern void VelocityGraphPrintSample(int Address);
extern void WeldHistoryPrintSample(int Address);
extern void SetUpPrintSample(int Address);
extern void SequencePrintSample(int Address);
extern void FrequencyGraphPrintSample(int Address);
extern void WeldSummaryPrint(int Address);
extern void WeldPerPagePrint(int Address);
extern void PowerPresetUpPressed(int Address);
extern void PowerPresetDownPressed(int Address);
extern void USBPresetUpPressed(int Address);
extern void USBPresetDownPressed(int Address);
extern void OverWriteOkButton(int Address);
extern void CopyPowerPreset(int Address);
extern void OverWriteCancelButton(int Address);
extern void ProcessUSBMemoryScreen(int Address);
extern void CopyAllPowerPreset(int Address);
extern void DeleteUSBPreset(int Address);
extern void CopyUSBPreset(int Address);
extern void BowseUSBFolder(int Address);
extern void ViewPowerPreset(int Address);
extern void USBForceSampleGraph(int Address);
extern void USBColDistanceGraph(int Address);
extern void USBAmplitudeGraphSample(int Address);
extern void USBPowerGraphSample(int Address);
extern void USBVelocityGraphSample(int Address);
extern void USBFrequencyGraphSample(int Address);
extern void USBWeldData(int Address);
extern void USBRecall(int Address);
extern void ExitHistoryMenu(int Address);
extern void HandleFolderHierarchyExit(int Address);
extern void ProcessHistoryGraph(int Address);
extern void ProcessUSBVelocityGraph(int Address);
extern void ProcessUSBFrquencyGraph(int Address);
extern void ProcessUSBColDistanceGraph(int Address);
extern void ProcessUSBForceGraph(int Address);
extern void ProcessUSBPowerGraph(int Address);
extern void ProcessUSBAmplitudeGraph(int Address);
extern void ExitHistoryGraph(int Address);
extern void PrintRunScreenWeldData(int Address);
extern void SendVQSLimitQualityCommand(int Address);
extern void ProcessDebugMenuScreen(int Address);
extern void ModifyPowerSupplyName(int Address);
extern void ProcessDiagnosticScreen(int Address);
extern void ProcessResetAlarms(int Address);
extern void ProcessSoftwareMismatchError(int Address);
extern void CompareGraph_and_Data(int ID);
extern void SendCommandForSave(int ID);
extern void SendCommandForVGAButtons(int ID);
extern void PresetUpExecute(int ID);
extern void PresetDownExecute(int ID);
extern void ContinueSequence(int ID);
extern void InsertEditSequencePreset(int ID);
extern void ReplaceEditSequencePreset(int ID);
extern void DeleteEditSequencePreset(int ID);
extern void SendCommandForVerifyPreset(int ID);
extern void SendCommandForButton(int ID);
extern void SendCommandForButtons(int ID);
extern void StartScan(int ID);
extern void HornScanAbort(int ID);
extern void WeldRetract(int ID);
extern void SendCommandForTestingMenu(int ID);
extern void SendSpecialMenuCommand(int ID);
extern void SendMicronsUpdateCommand(int ID);
extern void SendHornDownCommand(int ID);
extern void AutoRefreshGraph(int ID);
extern void ProcessSequence(int ID);
extern void PMCScreenCheck(int ID);
extern void CheckPrinterOnline(int ID);
extern void AddToAverageCommand(int ID);
extern void SendCommandForHSCGraph(int ID);
extern void HandleSaveScanAButton(int ID);
extern void HandleSaveScanBButton(int ID);
extern void HandleSaveScanCButton(int ID);
//extern void CompareGraph_and_Data(int ID);
extern void SendAlarmMenuCommand(int ID);

extern void ForceGraphPrintOnAlarm(int ID);
extern void DistanceGraphPrintOnAlarm(int ID);
extern void AmplitudeGraphPrintOnAlarm(int ID);
extern void PowerGraphPrintOnAlarm(int ID);
extern void VelocityGraphPrintOnAlarm(int ID);
extern void WeldHistoryPrintOnAlarm(int ID);
extern void SetUpPresetPrintOnAlarm(int ID);
extern void SequencePrintOnAlarm(int ID);
extern void FrequencyGraphPrintOnAlarm(int ID);
extern void WeldSummaryPrintOnAlarm(int ID);

extern void USBForceGraphSaveAlarm(int ID);
extern void USBDistanceGraphSaveAlarm(int ID);
extern void USBAmplitudeGraphSaveAlarm(int ID);
extern void USBPowerGraphSaveAlarm(int ID);
extern void USBVelocityGraphSaveAlarm(int ID);
extern void USBFrequencyGraphSaveAlarm(int ID);
extern void USBWeldDataSaveAlarm(int ID);
extern void USBGlobalFlagOn_Off(int ID);
extern void ProcessExtPrest(int ID);
extern void UpdateSW_Config(int ID);
extern void ProcessHornSignature(int ID);
extern void HornScanA(int ID,CLocalChoice *ptr);
extern void HornScanB(int ID,CLocalChoice *ptr);
extern void HornScanC(int ID,CLocalChoice *ptr);
extern void CurrentHornScan(int ID,CLocalChoice *ptr);
extern void CopyScanData(int ID,CLocalChoice *ptr);
extern bool AddPowerGraph(CVgaButton *ptr);
extern void SequenceUpButton(int Address);
extern void SequenceDownButton(int Address);
extern bool AddAvgPowerGraph(CVgaButton *ptr);
extern bool SendCommandForViewGraphs(CVgaButton *ptr);
extern bool ScanAOnOff(CLocalChoice *ptr);
extern bool CurrentScanOnOff(CLocalChoice *ptr);
extern bool ScanBOnOff(CLocalChoice *ptr);
extern bool ScanCOnOff(CLocalChoice *ptr);
extern bool ProcessAlarmMenu(CVgaButton *ptr);
extern bool ProcessAlarmExit(CVgaButton *ptr);
extern bool GetCurrentPresetScrn(CVgaButton *ptr);
extern bool GetPSPresetScrn(CVgaButton *ptr);
extern bool GetUSBPresetScrn(CVgaButton *ptr);
extern bool DisableColdStartFlag(CVgaButton *ptr);
extern bool GetPrinterInfo(CVgaButton *ptr);
extern bool CopyPowerPresetToList(CVgaButton *ptr);
extern bool EnableColdStartFlag(CVgaButton *ptr);
extern bool ProcessColorSetupScreen(CVgaButton *ptr);
extern bool ProcessUSBGraphButtonDisplay(CVgaButton *ptr);
extern bool AddStartUpVersion(CVgaButton *ptr);
extern bool AddSystemVersion(CVgaButton *ptr);
extern bool GetNKBinDate(CVgaButton *ptr);
//extern bool ProcessDebugMenuScreen(CVgaButton *ptr);
/////////////////////////////////////////////////////////////////////////////
// CSBCApp initialization

BOOL CSBCApp::InitInstance()
{
	if (!AfxSocketInit())
		{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
		}
#if 0
	if (!log.Create())
		{
		AfxMessageBox(L"Socket: open error");
		return FALSE;
		}
	if (!log.Connect(L"10.0.1.141", 5000))
		{
		AfxMessageBox(L"Socket: connect error");
		return FALSE;
		}
	logOpen = true;
	Trace("Starting log...");
	Trace("Adding a dummy entry");
#endif
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
   InitTasks();
   GetVQSWindow();
  // CChildView::MaxPreset= MAX_PSPRESET+1;
  // CChildView::SendCommandForQualityWindow(CChildView::MaxPreset);
  /*  SHELLEXECUTEINFO ShExecInfo = {0};
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = _T("Disk\\BransonUSWMonitor.exe");		
	ShExecInfo.lpParameters = _T("");	
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    hProcess = ShExecInfo.hProcess;*/

   // To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.
  // Sstlanguage.SetSize(50);
    PrepareFunctionMapTable();
	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

  // create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();
   
   return TRUE;
}

void CSBCApp::Trace(const CString &str)
{
#if 0
	static bool forceTrace = false;

	if (!logOpen)
		{
		logData.AddTail(str);
		return;
		}
	if (!forceTrace)
		{
		forceTrace = true;
		while (logData.GetCount() > 0)
			Trace(logData.RemoveHead());
		}
	logMutex.Lock();
	char buf[200];
	for (int i = 0; i < str.GetLength(); i++)
		buf[i] = (char) (str[i] & 0xFF);
	buf[i++] = '\n';
	int l = i;
	int s = log.Send(buf, l);
	if (s != l)
		{
		CString str;
		str.Format(L"Sent %d out of %d, error %d", s, l, GetLastError());
		AfxMessageBox(str);
		}
	logMutex.Unlock();
#endif
}

int CSBCApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
   Clean();
   return CApplication::ExitInstance();
}

/**********************************************************************************/
/*                                                                                */
/* This function Reads whole XML document in CArchive Class & draws first menu screen.  */
/**********************************************************************************/

bool CSBCApp::ReadXML()
{
   CFile F;
   
   if( !F.Open(_T("Disk\\Main.gui"), CFile::modeRead)) 
	{	
      return false;
	}
   CArchive arc(&F,CArchive::load);
   if (gui)
	   delete gui;
   
   gui = file.Read(arc);
   if (gui)
   {
    //  printf("\n parsing "); 
      ParseXmlTree(gui);
     // printf("\n menulook entry");
   }
   else
   {
      AfxMessageBox(_T("Parsing can'not be done."));
      exit(1); 
   }
   if(CChildView::thisPtr->Start_Screen==MAINMENU)//if main menu
      menuName = CVgaBottomMenu::mainMenuID;
   else
   {
      CChildView::thisPtr->RunResultScreen=true;
      menuName = CVgaBottomMenu::WeldResults_ID;
   }

   CVgaMenu * menu;
   
   if (menus.Lookup(menuName, menu))
   {
	//	printf("\n menulook");
      CChildView::thisPtr->menusname.AddTail(menuName);
      CChildView::thisPtr->menus.AddTail(1);
      CChildView::thisPtr->menupointers.AddTail(menu);
      MenuPointer=menu;
      CChildView::thisPtr->ModifyObjectList(menu);   
   }
   return true;

}

/**********************************************************************************/
/*                                                                                */
/* This function Verify Start_Screen & draws menu screen after a reset	  		  */
/**********************************************************************************/

bool CSBCApp::ReadXML_ReloadStartScreen()
{
   if(CChildView::thisPtr->Start_Screen==MAINMENU)//if main menu
      menuName = CVgaBottomMenu::mainMenuID;
   else
   {
      CChildView::thisPtr->RunResultScreen=true;
      menuName = CVgaBottomMenu::WeldResults_ID;
   }

   CVgaMenu * menu;
   
   if (menus.Lookup(menuName, menu))
   {
	//	printf("\n menulook");
      CChildView::thisPtr->menusname.AddTail(menuName);
      CChildView::thisPtr->menus.AddTail(1);
      CChildView::thisPtr->menupointers.AddTail(menu);
      MenuPointer=menu;
      CChildView::thisPtr->ModifyObjectList(menu);   
   }
   return true;

}

/**********************************************************************************/
/*                                                                                */
/*  This function Parse whole XML document & calls constructor of menu items one  */
/*   by one.	                                                                  */
/**********************************************************************************/

void CSBCApp::ParseXmlTree(CXmlElement *gui)
{
   ASSERT(gui->tag == "gui");
   POSITION pos = gui->children.GetHeadPosition();
	while (pos)
	{
      CXmlElement * element = gui->children.GetNext(pos);
		CString tag = element->tag;
		if (tag == "enumvariable")
      {
        // printf("\n enumvariable");
         CreateEnumVariable(element);
      }
		else if (tag == "bitvariable")
      {
        // printf("\n bitvariable");
         CreateBitVariable(element);
      }
		else if (tag == "menu")
      {
         //printf("\n menu");
        // printf("\n menu=%d",_ttoi(element->GetAttribute("name")));
         CreateMenu(element);
      }
      else if(tag=="special")
      {
         int gh=_ttoi(element->GetAttribute("name"));
         //printf("\n gh=%d",gh);
         SpecialMenu.SetSize(gh);
      }
      else if(tag=="Key")
      {
        // printf("\n Key");
         //CreateSpecialMenu(element);
         CString Temp=element->GetAttribute("name");
         SpecialMenu[total++]= element->GetAttribute("name");
         /*printf("\n");
         for(int i=0;i<Temp.GetLength ();i++)
         {
            printf(" %c",Temp.GetAt (i));
         }*/
      }
	  else if(tag=="bottomMenu")
	  {
		 //printf("\n bottomMenu");
		 CVgaBottomMenu::InitializeBottomMenuMembers(element);
	  }
	  else if(tag=="variableinfo")
	  {
		 //printf("\n variableinfo");
		 CScreenKeypad::SetVariableStrings(element);
	  }
	  else if(tag=="WeldDataHeading")
	  {
		  CChildView::thisPtr->TotalTextHeading =_ttoi(element->GetAttribute("TotalParam"));	
		  //printf("\n CChildView::thisPtr->TotalTextHeading=%d",CChildView::thisPtr->TotalTextHeading);
	     CChildView::thisPtr->GetAllWeldDataHeading(element);
	  }
     else if(tag=="AlarmButtonmenu")
     {
         CChildView::thisPtr->AlarmMenuIdentifier=element->GetAttribute("name");
         /*for(int i=0;i<(CChildView::thisPtr->AlarmMenuIdentifier.GetLength ());i++)
         {
            printf(" %c",CChildView::thisPtr->AlarmMenuIdentifier.GetAt (i));
         }*/
     }
    else if(tag=="PrintStrings")
	    CreatePrintStrings(element);	
	 else if(tag=="AlarmsStrings")
	   CreateAlarmStrings(element);	
	 else if(tag=="AlarmEng")
	 {	
		 int TotalStrings=_ttoi(element->GetAttribute("TotalString"));
				 
		 CChildView::thisPtr->AlarmEng.SetSize(TotalStrings);
		 CreateAlarmEng(element);	
	 }
    else if(tag=="ManualGraphStringsList")
    {
       int TotalStrings=_ttoi(element->GetAttribute("TotalString"));
       CChildView::thisPtr->Manual.SetSize(TotalStrings);
		 CreateManualGraph(element);	
    }
    else if(tag=="GraphPrText")
    {
       int TotalStrings=_ttoi(element->GetAttribute("TotalString"));
       CChildView::thisPtr->GraphPrText.SetSize(TotalStrings);
		 CreateGraphPrText(element);
    }
	 else if(tag=="PresetStrings")
	 {	 int gh=_ttoi(element->GetAttribute("TotalString"));
				 
		 CChildView::thisPtr->PString.SetSize(gh);
	//	 CChildView::thisPtr->PString.FreeExtra();
		 CreatePresetString(element);	
	 }
	 else if(tag=="LabelStrings")
	 {	int gh=_ttoi(element->GetAttribute("TotalString"));
		 CChildView::thisPtr->LString.SetSize(gh);
		 CreateLabelStrings(element);
	 }
    else if(tag=="PrintHSInfoText")
    {
       int TotalStrings=_ttoi(element->GetAttribute("TotalString"));
       CChildView::thisPtr->PrintHSInfoText.SetSize(TotalStrings);
		 CreateHSInfoText(element);
    }
    else if(tag=="OnLinePrint")
    {
       int Count=0;
       POSITION pos = element->children.GetHeadPosition();
	    while (pos)
       {
		  // printf("\n OnLinePrint");
         CXmlElement * e = element->children.GetNext(pos);
		   ASSERT(e->tag == "PrintMenu");
		   CString name = e->GetAttribute("name");
		   CString value = e->GetAttribute("value");
         CVgaMenu *ptr;
         if(value!="")
            menus.Lookup(value, ptr);
         if(Count==0)
         {
            CChildView::thisPtr->SetupMenuPointer=ptr;
            CChildView::thisPtr->ModifyObjectList(ptr);
         }
         else if(Count==1)
         {
            CChildView::thisPtr->SequenceMenuPointer=ptr;
            CChildView::thisPtr->ModifyObjectList(ptr);
         }
         else if(Count==2)
            CChildView::thisPtr->USBGraphMenu=value;
         Count++;
		  // OnLinePrintLookUpMenu.SetAt(name1, value1);
       }
    }
    else if(tag=="MonthStrings")
    {
       int TotalStrings=_ttoi(element->GetAttribute("TotalString"));
       CChildView::thisPtr->AllMonthStrings.SetSize(TotalStrings);
		 CreateMonthStrings(element);
    }
	 else
		ASSERT(FALSE);
	}
}

void CSBCApp::CreatePrintStrings(CXmlElement *e)
{ 	
   POSITION pos = e->children.GetHeadPosition();
	while (pos)
   {
		CXmlElement * element = e->children.GetNext(pos);
		CString tag = element->GetTag();

		CString Temp=element->GetAttribute("textID");
		
		if (tag == _T("WeldDataString"))
		{	
         CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
			   temp1 = Temp.SpanExcluding(_T(" "));
			   len = temp1.GetLength();
			   temp1=CVgaMenuItem ::LinearSearch(temp1);
			   tempWeldList.AddTail(temp1);
			   len1 = len1-len-1;
			   Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("HistoryWeldDataString"))
		{ //printf("tag==Historywelddatastring \n");
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
			   temp1 = Temp.SpanExcluding(_T(" "));
			   len = temp1.GetLength();
			   temp1=CVgaMenuItem ::LinearSearch(temp1);
			   tempHistoryList.AddTail(temp1);
			   len1 = len1-len-1;
			   Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("GraphsString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
			   temp1 = Temp.SpanExcluding(_T(" "));
			   len = temp1.GetLength();
			   temp1=CVgaMenuItem ::LinearSearch(temp1);
			   tempGraphsList.AddTail(temp1);
			   len1 = len1-len-1;
			   Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("ScreenGraphsString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
			   temp1 = Temp.SpanExcluding(_T(" "));
			   len = temp1.GetLength();
			   temp1=CVgaMenuItem ::LinearSearch(temp1);
			   tempScreenGraphsList.AddTail(temp1);
			   len1 = len1-len-1;
			   Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("HornScanString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
			   temp1 = Temp.SpanExcluding(_T(" "));
			   len = temp1.GetLength();
			   temp1=CVgaMenuItem ::LinearSearch(temp1);
			   tempHornScanList.AddTail(temp1);
			   len1 = len1-len-1;
			   Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("PrintScanGraphsString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
			   temp1 = Temp.SpanExcluding(_T(" "));
			   len = temp1.GetLength();
			   temp1=CVgaMenuItem ::LinearSearch(temp1);
			   tempScanGraphDataList.AddTail(temp1);
			   len1 = len1-len-1;
			   Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("PrintSetupString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
			   temp1 = Temp.SpanExcluding(_T(" "));
			   len = temp1.GetLength();
			   temp1=CVgaMenuItem ::LinearSearch(temp1);
			   tempSetupList.AddTail(temp1);
			   len1 = len1-len-1;
			   Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("PrintDUPSString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
			   temp1 = Temp.SpanExcluding(_T(" "));
			   len = temp1.GetLength();
			   temp1=CVgaMenuItem ::LinearSearch(temp1);
			   tempDUPSList.AddTail(temp1);
			   len1 = len1-len-1;
			   Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("PrintSequenceString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
			   temp1 = Temp.SpanExcluding(_T(" "));
			   len = temp1.GetLength();
			   temp1=CVgaMenuItem ::LinearSearch(temp1);
			   tempSequenceList.AddTail(temp1);
			   len1 = len1-len-1;
			   Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("RunScreenPrintString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
			   temp1 = Temp.SpanExcluding(_T(" "));
			   len = temp1.GetLength();
			   temp1=CVgaMenuItem ::LinearSearch(temp1);
			   tempRunScreenList.AddTail(temp1);
			   len1 = len1-len-1;
			   Temp = Temp.Right(len1);
			}
		}
		else
			ASSERT(FALSE);
	}

}

void CSBCApp::CreateAlarmStrings(CXmlElement *e)
{		POSITION pos = e->children.GetHeadPosition();

	while (pos)
    {
		CXmlElement * element = e->children.GetNext(pos);
		CString Temp = element->GetAttribute("StringID");
		CString name = element->GetAttribute("TextID");
		CChildView::thisPtr->AlarmMap.SetAt(Temp,name);
	}
}

void CSBCApp::CreateAlarmEng(CXmlElement *e)
{	POSITION pos = e->children.GetHeadPosition();
	int k=0;
	while (pos)
    {
		CXmlElement * element = e->children.GetNext(pos);
		CString name = element->GetAttribute("textID");
		name=CVgaMenuItem ::LinearSearch(name);
		CChildView::thisPtr->AlarmEng.SetAt(k++,name);
	}
}

void CSBCApp::CreatePresetString(CXmlElement *e)
{	POSITION pos = e->children.GetHeadPosition();
	int k=0;

	while (pos)
    {
		CXmlElement * element = e->children.GetNext(pos);
		CString name = element->GetAttribute("textID");
		name=CVgaMenuItem ::LinearSearch(name);
		CChildView::thisPtr->PString.SetAt(k++,name);
		//CChildView::thisPtr->PString.Add(name);
	}	
}

void CSBCApp::CreateLabelStrings(CXmlElement *e)
{	POSITION pos = e->children.GetHeadPosition();
	int k=0;

	while (pos)
    {
		CXmlElement * element = e->children.GetNext(pos);
		CString name = element->GetAttribute("textID");
		name=CVgaMenuItem ::LinearSearch(name);
		CChildView::thisPtr->LString.SetAt(k++,name);
		//CChildView::thisPtr->PString.Add(name);
	}	
}


void CSBCApp::CreateHSInfoText(CXmlElement *e)
{	POSITION pos = e->children.GetHeadPosition();
	int k=0;
	while (pos)
    {
		CXmlElement * element = e->children.GetNext(pos);
		CString name = element->GetAttribute("textID");
		name=CVgaMenuItem ::LinearSearch(name);
		CChildView::thisPtr->PrintHSInfoText.SetAt(k++,name);
	}
}

void CSBCApp::CreateManualGraph(CXmlElement *e)
{	POSITION pos = e->children.GetHeadPosition();
	int k=0;
	while (pos)
    {
		CXmlElement * element = e->children.GetNext(pos);
		CString name = element->GetAttribute("textID");
		name=CVgaMenuItem ::LinearSearch(name);
		CChildView::thisPtr->Manual.SetAt(k++,name);
	}
}

void CSBCApp::CreateGraphPrText(CXmlElement *e)
{	POSITION pos = e->children.GetHeadPosition();
	int k=0;
	while (pos)
    {
		CXmlElement * element = e->children.GetNext(pos);
		CString name = element->GetAttribute("textID");
		name=CVgaMenuItem ::LinearSearch(name);
		CChildView::thisPtr->GraphPrText.SetAt(k++,name);
	}
}

void CSBCApp::CreateMonthStrings(CXmlElement *e)
{	POSITION pos = e->children.GetHeadPosition();
	int k=0;
	while (pos)
    {
		CXmlElement * element = e->children.GetNext(pos);
		CString name = element->GetAttribute("textID");
		name=CVgaMenuItem ::LinearSearch(name);
		CChildView::thisPtr->AllMonthStrings.SetAt(k++,name);
	}
}

void CSBCApp::CreateEnumVariable(CXmlElement *element)
{
	CEnumVariable * var = new CEnumVariable(element);
	variables.SetAt(var->name, var);
}

void CSBCApp::CreateBitVariable(CXmlElement *element)
{
	
	CBitmaskVariable * var = new CBitmaskVariable(element);
	variables.SetAt(var->name, var);
}

void CSBCApp::CreateMenu(CXmlElement *element)
{
	CVgaMenu * menu = new CVgaMenu(element);
	menus.SetAt(menu->GetName(), menu);
}

void CSBCApp::DrawMenu(CDC *pDC)
{
 //  CVgaMenu * menu;
//   if (menus.Lookup(menuName, menu))
   if(MenuPointer!=NULL)
   {	
      //if(menuName != "Language Menu")
      {
      
         CChildView::thisPtr->Add_Back_Next_Button();
      }
      CChildView::thisPtr->Back_Next_Button_Layout();
     // printf("\n menu draw");
      MenuPointer->Draw(pDC);      
   }
   else
   {
      return;
   }
   
}

CVariable * CSBCApp::GetVariable(const CString &varName) const
{
   CVariable * var;
   if (variables.Lookup(varName, var))
   {
     return var;
   }
   return 0;
}


void CSBCApp::Clean()
{
	menuName = CVgaBottomMenu::mainMenuID;
	CChildView::BottomHalfTimerOn=true;
	if (gui)
	{
	//	printf("\n gui");
		delete gui;
		gui = 0;
	}
	if(!functionCall.IsEmpty())
	{
	   //printf("\n functionCall");
	   functionCall.RemoveAll();
	}
	//printf("\n menus");
	menus.DeleteAll();
	//printf("\n variables");
	variables.DeleteAll();
	//printf("\n before");
	
   while(GraphsDataList.GetCount()>0)
      delete GraphsDataList.RemoveHead();

  /* while(CChildView::thisPtr->PrintWeldHistoryList2.GetCount()>0)
	   delete CChildView::thisPtr->PrintWeldHistoryList2.RemoveHead();*/

	CWnd *pWndPrev;
	if (pWndPrev = CWnd::FindWindow(NULL,_T("VQS")))
	{
	   //printf("\n PostMessage");
	   CloseHandle(hProcess);// Closing Handle of VQS Application
	   pWndPrev->PostMessage(WM_CLOSE,0,0);
	}
}

/**********************************************************************************/
/*                                                                                */
/*  This function will send Host Command to 332 & gets all variables at Start up  */
/*   	                                                                          */
/**********************************************************************************/

void CSBCApp::GetSystemVariable()
{
   CHostCommand * request = new CHostCommand(GetSysVariable_FunId,0,0);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		unsigned char *data = response->GetData();
		int length = response->GetDataLength();
      if(ch==ACK)
		{
			// printf("\n ACK in GetSysVariable_FunId");
			 CChildView::ControlLevel=*data++;length--;
			 CChildView::Actuator=*data++;length--;
			 CChildView::WeldMode=*data++;length--;
			 CChildView::Securitylevel=*data++;length--;
			 CChildView::AccessLevelSystem=*data++;length--;
			 CChildView::SWconfiguration=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
			 CChildView::HWconfiguration=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
			/* union 
			   {
				   bool i;
				   char c;
			   } u;
			 u.c = *data++;length--;
			 CChildView::metric=u.i;*/
         unsigned char temp = *data++;
         length--;
         if((temp & 0x01) == 0x01 )
            CChildView::metric = true;
         else
            CChildView::metric = false;

         if((temp & 0x10) == 0x10 )
            CChildView::AutoRefreshon = true;
         else
            CChildView::AutoRefreshon = false;
			 union 
			  {
				  bool i;
				  char c;
			  } u1;
			  u1.c = *data++;length--;
			  CChildView::PasswordFlag=u1.i; 
           CToggle::SequencingON= *data++;length--;
		   
		   CChildView::AmplitudeMicrons = *data++;length--;
		   CChildView::PeakPowerMicrons = *data++;length--;


		   CChildView::PeakPowerWattsMax = CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
		   CChildView::AmplitudeMicronsMax = *data++;length--;
		   }
   }
   
}

void CSBCApp::SetMicronsUpdate()
{
	CString StrMetric;
	CString StrUSCS;

	if(CChildView::AmplitudeMicrons)
	{
		StrMetric=CScreenKeypad::InsertWeldParamUnitsString(true,CScreenKeypad::FORMAT::MICRONS);
		StrUSCS=CScreenKeypad::InsertWeldParamUnitsString(false,CScreenKeypad::FORMAT::MICRONS);
	}
	else
	{
		StrMetric=CScreenKeypad::InsertWeldParamUnitsString(true,CScreenKeypad::FORMAT::PERCENT);
		StrUSCS=CScreenKeypad::InsertWeldParamUnitsString(false,CScreenKeypad::FORMAT::PERCENT);
	}

	StrMetric.TrimLeft();
	StrMetric.TrimRight();
	StrUSCS.TrimLeft();
	StrUSCS.TrimRight();
	CChildView::thisPtr->Parameter_Units_Metric[MICRONS_COLUMN_AMPA] = _T("(")+StrMetric+_T(")");
	CChildView::thisPtr->Parameter_Units_USCS[MICRONS_COLUMN_AMPA] = _T("(")+ StrUSCS +_T(")");
	CChildView::thisPtr->Parameter_Units_Metric[MICRONS_COLUMN_AMPB] = _T("(")+StrMetric+_T(")");
	CChildView::thisPtr->Parameter_Units_USCS[MICRONS_COLUMN_AMPB] = _T("(")+ StrUSCS +_T(")");

	if(CChildView::PeakPowerMicrons)
	{
		StrMetric=CScreenKeypad::InsertWeldParamUnitsString(true,CScreenKeypad::FORMAT::WATTS);
		StrUSCS=CScreenKeypad::InsertWeldParamUnitsString(false,CScreenKeypad::FORMAT::WATTS);
		CChildView::thisPtr->GraphTitle=CVgaMenuItem ::LinearSearch(_T("2693"));
	}
	else
	{
		StrMetric=CScreenKeypad::InsertWeldParamUnitsString(true,CScreenKeypad::FORMAT::PERCENT);
		StrUSCS=CScreenKeypad::InsertWeldParamUnitsString(false,CScreenKeypad::FORMAT::PERCENT);
		CChildView::thisPtr->GraphTitle=CVgaMenuItem ::LinearSearch(_T("1863"));
	}

	StrMetric.TrimLeft();
	StrMetric.TrimRight();
	StrUSCS.TrimLeft();
	StrUSCS.TrimRight();
	CChildView::thisPtr->Parameter_Units_Metric[MICRONS_COLUMN_PKPWR] = _T("(")+StrMetric+_T(")");
	CChildView::thisPtr->Parameter_Units_USCS[MICRONS_COLUMN_PKPWR] = _T("(")+ StrUSCS +_T(")");
}

void CSBCApp::PrepareStringFromUnicodeText(CString Str,bool FirstTime,bool skipFirstLine)
{
	CString name=_T("Disk")/*+\\languages\\")*/+Str;
	configFile=new CTextFileIO(name,L"rb",FirstTime);
	configFile->ReadLineW(FirstTime,skipFirstLine);
}

void CSBCApp::PrepareFunctionMapTable()
{
   void (*Pointer)(int)=ExitSystemProgram;
	void *ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitSystemProgram"),ptr);

	Pointer=ExitColorMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitColorMenu"),ptr);

   Pointer=ButtonColor;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ButtonColor"),ptr);

	Pointer=BackgroundColor;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("BackgroundColor"),ptr);

	Pointer=DefaultColor;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DefaultColor"),ptr);

	Pointer=TextColor;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("TextColor"),ptr);

	Pointer=TitleColor;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("TitleColor"),ptr);

	Pointer=HighLightColor;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HighLightColor"),ptr);

	Pointer=BuildLocalScreenSetupMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("BuildLocalScreenSetupMenu"),ptr);

	Pointer=HandleVGASaveButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HandleVGASaveButton"),ptr);

   Pointer=SendCommandForVGAButtonsPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForVGAButtonsPreset"),ptr);

   Pointer=SendCommandForRecallPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForRecallPreset"),ptr);

	Pointer=HistoryLeftButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HistoryLeftButton"),ptr);
	
	Pointer=HistoryRightButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HistoryRightButton"),ptr);

	Pointer=HistoryScreenUpButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HistoryScreenUpButton"),ptr);

	Pointer=HistoryScreenDownButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HistoryScreenDownButton"),ptr);

	Pointer=HistoryUpButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HistoryUpButton"),ptr);

	Pointer=HistoryDownButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HistoryDownButton"),ptr);

	Pointer=ShowPowerSupplyMessageScreen;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ShowPowerSupplyMessageScreen"),ptr);

	Pointer=SequenceUpButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SequenceUpButton"),ptr);

	Pointer=SequenceDownButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SequenceDownButton"),ptr);

	Pointer=ShowQualityScreen;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ShowQualityScreen"),ptr);

	Pointer=GraphRefresh;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("GraphRefresh"),ptr);

   Pointer=SendCommandForVGAButtonsSavePreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForVGAButtonsSavePreset"),ptr);

   Pointer=Color_DistanceGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("Color_DistanceGraph"),ptr);

   Pointer=Power_Graph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("Power_Graph"),ptr);

   Pointer=Velocity_Graph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("Velocity_Graph"),ptr);

   Pointer=Force_Graph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("Force_Graph"),ptr);

   Pointer=Amplitude_Graph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("Amplitude_Graph"),ptr);

   Pointer=Frequency_Graph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("Frequency_Graph"),ptr);

   Pointer=ExitGraphMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitGraphMenu"),ptr);

   Pointer=ExitBandLimitsMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitBandLimitsMenu"),ptr);

   Pointer=ExitAlarmMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitAlarmMenu"),ptr);
   
   Pointer=AlarmErrorBeep;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("AlarmErrorBeep"),ptr);
  
   Pointer=ProcessColorSetup;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessColorSetup"),ptr);

   /*Pointer=ProcessPollingTimeMsgScrn;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessPollingTimeMsgScrn"),ptr);*/

   Pointer=PresetDownExecute;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PresetDownExecute"),ptr);

	Pointer=PresetUpExecute;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PresetUpExecute"),ptr);

	Pointer=ContinueSequence;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ContinueSequence"),ptr);

	Pointer=InsertEditSequencePreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("InsertEditSequencePreset"),ptr);  

	Pointer=ReplaceEditSequencePreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ReplaceEditSequencePreset"),ptr);

	Pointer=DeleteEditSequencePreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DeleteEditSequencePreset"),ptr);

	Pointer=SendCommandForSave;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForSave"),ptr);

	Pointer=SendCommandForVerifyPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForVerifyPreset"),ptr);

	Pointer=SendCommandForButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForButton"),ptr);

	Pointer=SendCommandForButtons;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForButtons"),ptr);

	Pointer=StartScan;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("StartScan"),ptr);

	Pointer=HornScanAbort;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HornScanAbort"),ptr);

   Pointer=WeldRetract;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("WeldRetract"),ptr);

	Pointer=SendCommandForTestingMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForTestingMenu"),ptr);

	Pointer=SendSpecialMenuCommand;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendSpecialMenuCommand"),ptr);

	Pointer=SendMicronsUpdateCommand;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendMicronsUpdateCommand"),ptr);

    Pointer=SendHornDownCommand;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendHornDownCommand"),ptr);

	Pointer=SendCommandForVGAButtons;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForVGAButtons"),ptr);

   Pointer=AutoRefreshGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("AutoRefreshGraph"),ptr);
   
   Pointer=ProcessSequence;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessSequence"),ptr);

   Pointer=PMCScreenCheck;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PMCScreenCheck"),ptr);

   Pointer=AddToAverageCommand;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("AddToAverageCommand"),ptr);

   Pointer=SendCommandForHSCGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForHSCGraph"),ptr);

   Pointer=HandleSaveScanAButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HandleSaveScanAButton"),ptr);

   Pointer=HandleSaveScanBButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HandleSaveScanBButton"),ptr);

   Pointer=HandleSaveScanCButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HandleSaveScanCButton"),ptr);

   Pointer=CompareGraph_and_Data;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("CompareGraph_and_Data"),ptr);

   Pointer=SendAlarmMenuCommand;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendAlarmMenuCommand"),ptr);

   Pointer=ForceGraphPrintOnAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ForceGraphPrintOnAlarm"),ptr);

   Pointer=DistanceGraphPrintOnAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DistanceGraphPrintOnAlarm"),ptr);

   Pointer=AmplitudeGraphPrintOnAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("AmplitudeGraphPrintOnAlarm"),ptr);

   Pointer=PowerGraphPrintOnAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PowerGraphPrintOnAlarm"),ptr);

   Pointer=VelocityGraphPrintOnAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("VelocityGraphPrintOnAlarm"),ptr);

   Pointer=WeldHistoryPrintOnAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("WeldHistoryPrintOnAlarm"),ptr);

   Pointer=SetUpPresetPrintOnAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SetUpPresetPrintOnAlarm"),ptr);

   Pointer=SequencePrintOnAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SequencePrintOnAlarm"),ptr);

   Pointer=FrequencyGraphPrintOnAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("FrequencyGraphPrintOnAlarm"),ptr);

   Pointer=WeldSummaryPrintOnAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("WeldSummaryPrintOnAlarm"),ptr);

   Pointer=USBForceGraphSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBForceGraphSaveAlarm"),ptr);

   Pointer=USBDistanceGraphSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBDistanceGraphSaveAlarm"),ptr);

   Pointer=USBAmplitudeGraphSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBAmplitudeGraphSaveAlarm"),ptr);

   Pointer=USBPowerGraphSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBPowerGraphSaveAlarm"),ptr);

   Pointer=USBVelocityGraphSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBVelocityGraphSaveAlarm"),ptr);

   Pointer=USBFrequencyGraphSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBFrequencyGraphSaveAlarm"),ptr);

   Pointer=USBWeldDataSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBWeldDataSaveAlarm"),ptr);

   Pointer=USBGlobalFlagOn_Off;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBGlobalFlagOn_Off"),ptr);

   Pointer=ProcessExtPrest;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessExtPrest"),ptr);

   Pointer=UpdateSW_Config;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("UpdateSW_Config"),ptr);

   Pointer=ExitWindowProgram;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitWindowProgram"),ptr);

   Pointer=PrintScanGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PrintScanGraph"),ptr);

	Pointer=PrintScanData;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PrintScanData"),ptr);

	Pointer=WeldDataPrintNow;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("WeldDataPrintNow"),ptr);

	Pointer=WeldHistoryPrintNow;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("WeldHistoryPrintNow"),ptr);

	Pointer=AbortPrinting;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("AbortPrinting"),ptr);

	Pointer=GraphsWeldNow;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("GraphsWeldNow"),ptr);

   Pointer=PrintScreenGraphs;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PrintScreenGraphs"),ptr);

   Pointer=HornScanPrint;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HornScanPrint"),ptr);

   Pointer=SetUpPrintNow;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SetUpPrintNow"),ptr);

   Pointer=PrintDUPSSetup;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PrintDUPSSetup"),ptr);

   Pointer=CheckPrinterOnline;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("CheckPrinterOnline"),ptr);

   Pointer=SequencingPrintNow;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SequencingPrintNow"),ptr);

   Pointer=GetPrinterStatus;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("GetPrinterStatus"),ptr);

   Pointer=ForceGraphPrintSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ForceGraphPrintSample"),ptr);

   Pointer=DistanceGraphPrintSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DistanceGraphPrintSample"),ptr);

   Pointer=AmplitudeGraphPrintSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("AmplitudeGraphPrintSample"),ptr);

   Pointer=PowerGraphPrintSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PowerGraphPrintSample"),ptr);

   Pointer=VelocityGraphPrintSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("VelocityGraphPrintSample"),ptr);

   Pointer=WeldHistoryPrintSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("WeldHistoryPrintSample"),ptr);

   Pointer=SetUpPrintSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SetUpPrintSample"),ptr);
   
   Pointer=SequencePrintSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SequencePrintSample"),ptr);

   Pointer=FrequencyGraphPrintSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("FrequencyGraphPrintSample"),ptr);
   
   Pointer=WeldSummaryPrint;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("WeldSummaryPrint"),ptr);

   Pointer=WeldPerPagePrint;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("WeldPerPagePrint"),ptr);

   Pointer=PowerPresetUpPressed;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PowerPresetUpPressed"),ptr);

   Pointer=PowerPresetDownPressed;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PowerPresetDownPressed"),ptr);

   Pointer=USBPresetUpPressed;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBPresetUpPressed"),ptr);

   Pointer=USBPresetDownPressed;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBPresetDownPressed"),ptr);

   Pointer=OverWriteOkButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("OverWriteOkButton"),ptr);

   Pointer=CopyPowerPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("CopyPowerPreset"),ptr);

   Pointer=OverWriteCancelButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("OverWriteCancelButton"),ptr);

   Pointer=ProcessUSBMemoryScreen;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBMemoryScreen"),ptr);

   Pointer=CopyAllPowerPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("CopyAllPowerPreset"),ptr);

   Pointer=DeleteUSBPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DeleteUSBPreset"),ptr);

   Pointer=CopyUSBPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("CopyUSBPreset"),ptr);

   Pointer=BowseUSBFolder;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("BowseUSBFolder"),ptr);

   Pointer=ViewPowerPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ViewPowerPreset"),ptr);

   Pointer=USBForceSampleGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBForceSampleGraph"),ptr);

   Pointer=USBColDistanceGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBColDistanceGraph"),ptr);

   Pointer=USBAmplitudeGraphSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBAmplitudeGraphSample"),ptr);

   Pointer=USBPowerGraphSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBPowerGraphSample"),ptr);

   Pointer=USBVelocityGraphSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBVelocityGraphSample"),ptr);

   Pointer=USBFrequencyGraphSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBFrequencyGraphSample"),ptr);

   Pointer=USBWeldData;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBWeldData"),ptr);

   Pointer=ModifyPowerSupplyName;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ModifyPowerSupplyName"),ptr);

   Pointer=USBRecall;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBRecall"),ptr);

   Pointer=ExitHistoryMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitHistoryMenu"),ptr);

   Pointer=HandleFolderHierarchyExit;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HandleFolderHierarchyExit"),ptr);

   Pointer=ProcessHistoryGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessHistoryGraph"),ptr);

   Pointer=ProcessUSBVelocityGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBVelocityGraph"),ptr);

   Pointer=ProcessUSBFrquencyGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBFrquencyGraph"),ptr);

   Pointer=ProcessResetAlarms;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessResetAlarms"),ptr);

   Pointer=ProcessUSBColDistanceGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBColDistanceGraph"),ptr);

   Pointer=ProcessUSBForceGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBForceGraph"),ptr);

   Pointer=ProcessUSBPowerGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBPowerGraph"),ptr);

   Pointer=ProcessUSBAmplitudeGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBAmplitudeGraph"),ptr);

   Pointer=ExitHistoryGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitHistoryGraph"),ptr);

   Pointer=ProcessDiagnosticScreen;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessDiagnosticScreen"),ptr);

   Pointer=ProcessHornSignature;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessHornSignature"),ptr);

   Pointer=PrintRunScreenWeldData;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PrintRunScreenWeldData"),ptr);

   Pointer=SendVQSLimitQualityCommand;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendVQSLimitQualityCommand"),ptr);

   Pointer=ProcessDebugMenuScreen;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessDebugMenuScreen"),ptr);
   
   Pointer=ProcessSoftwareMismatchError;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessSoftwareMismatchError"),ptr);

   CString (*Pointer1)(CString)=GetIPAddress;
	ptr = (void*)Pointer1;        
	functionCall.SetAt (_T("GetIPAddress"),ptr);

	bool (*Pointer3)(CVgaButton *)=RefreshCheck;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("RefreshCheck"),ptr);

   Pointer3=AddPowerGraph;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("AddPowerGraph"),ptr);

   Pointer3=AddAvgPowerGraph;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("AddAvgPowerGraph"),ptr);

   Pointer3=ProcessAlarmMenu;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("ProcessAlarmMenu"),ptr);

   Pointer3=SendCommandForViewGraphs;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("SendCommandForViewGraphs"),ptr);

   Pointer3=ProcessAlarmExit;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("ProcessAlarmExit"),ptr);

   Pointer3=GetCurrentPresetScrn;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("GetCurrentPresetScrn"),ptr);

   Pointer3=GetPSPresetScrn;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("GetPSPresetScrn"),ptr);

   Pointer3=GetUSBPresetScrn;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("GetUSBPresetScrn"),ptr);

   Pointer3=DisableColdStartFlag;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("DisableColdStartFlag"),ptr);

   Pointer3=GetPrinterInfo;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("GetPrinterInfo"),ptr);

   Pointer3=EnableColdStartFlag;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("EnableColdStartFlag"),ptr);

   Pointer3=USBCheckFunction;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("USBCheckFunction"),ptr);

   Pointer3=CopyPowerPresetToList;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("CopyPowerPresetToList"),ptr);

/*   Pointer3=ProcessDebugMenuScreen;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("ProcessDebugMenuScreen"),ptr);*/
   
   Pointer3=ProcessColorSetupScreen;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("ProcessColorSetupScreen"),ptr);

   Pointer3=ProcessUSBGraphButtonDisplay;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("ProcessUSBGraphButtonDisplay"),ptr);

   Pointer3=AddStartUpVersion;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("AddStartUpVersion"),ptr);

   Pointer3=AddSystemVersion;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("AddSystemVersion"),ptr);

   Pointer3=GetNKBinDate;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("GetNKBinDate"),ptr);

   bool (*Pointer4)(CLocalChoice *)=ScanAOnOff;
	ptr = (void*)Pointer4;        
	functionCall.SetAt (_T("ScanAOnOff"),ptr);

   Pointer4=ScanBOnOff;
	ptr = (void*)Pointer4;        
	functionCall.SetAt (_T("ScanBOnOff"),ptr);

   Pointer4=ScanCOnOff;
	ptr = (void*)Pointer4;        
	functionCall.SetAt (_T("ScanCOnOff"),ptr);

   Pointer4=CurrentScanOnOff;
	ptr = (void*)Pointer4;        
	functionCall.SetAt (_T("CurrentScanOnOff"),ptr);

   void (*Pointer5)(int,CLocalChoice *)=HornScanA;
	ptr = (void*)Pointer5;        
	functionCall.SetAt (_T("HornScanA"),ptr);

   Pointer5=HornScanB;
	ptr = (void*)Pointer5;        
	functionCall.SetAt (_T("HornScanB"),ptr);

   Pointer5=HornScanC;
	ptr = (void*)Pointer5;        
	functionCall.SetAt (_T("HornScanC"),ptr);

   Pointer5=CurrentHornScan;
	ptr = (void*)Pointer5;        
	functionCall.SetAt (_T("CurrentHornScan"),ptr);

   Pointer5=CopyScanData;
	ptr = (void*)Pointer5;        
	functionCall.SetAt (_T("CopyScanData"),ptr);

}

void CSBCApp::GetVQSWindow()
{
   CChildView::MaxPreset= MAX_PSPRESET+1;
   CChildView::SendCommandForQualityWindow(CChildView::MaxPreset);
   SHELLEXECUTEINFO ShExecInfo = {0};
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = _T("Disk\\BransonUSWMonitor.exe");		
	ShExecInfo.lpParameters = _T("");	
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;
   ShellExecuteEx(&ShExecInfo);
   hProcess = ShExecInfo.hProcess;
}


void AfxMsgBox(CString x)
{
   int Returnvalue = AfxMessageBox(x,MB_SETFOREGROUND | MB_OK);
   if(Returnvalue==IDOK)
   {
      CWnd *pWndPrev;
      // Determine if a window with the class name exists...
		if (pWndPrev = CWnd::FindWindow(NULL,_T("SBC")))
			pWndPrev->SetForegroundWindow();
   }
}
