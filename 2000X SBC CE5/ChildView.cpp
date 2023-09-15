/* $Header:   D:/databases/VMdb/archives/2000 RVTS/ChildView.cpp_v   1.62.1.20.1.4.1.4.1.1.2.0   Oct 23 2017 15:46:16   RCHAPA  $ */
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
/* ****************************************************************************/ 
/*
Revision #    Date      Author    Description
----------  --------  ----------  -------------------------------------
  1.7           05/19/05	Aare        Added complete revision header.
  1.8		       05/23/05	BWadia		Added DrawFirstScreen Function.
  1.9		       07/25/05	BWadia		Added SendPollingCommand And related Functions.
  1.10		    07/28/05	BWadia		Edited OnLButtonDown Function for  VGAWeldState type TextBox
  1.11		    09/19/05	BWadia		Added Functions For Printing
  1.12		    09/20/05	BWadia		Made Weld Data To Be Printed,On Print Button On Graph Screen
  1.13		    09/20/05	BWadia		Modified BuildPrintList() Function For Screen Graphs Printing
  1.14		    10/14/05	BWadia		Added Functions For USB Storage.
  1.15		    10/24/05	BWadia		Added Functions GetAveragePowerGraph() and ExitProgram() for Power 
									             Match Compare and Main menu Exit button.
  1.16		    10/28/05	BWadia		Added CurrentSequencePreset variable and modify positions of Back,Next and Exit buttons.
  1.17		    10/28/05	BWadia		Edited ReCalculateMenu() function to display max. four buttons in single coloumn menu
  1.18		    11/07/05	BWadia		Modified AnalysePollingCommand() Function for Graphs AutoRefresh 
  1.19		    11/08/05	BWadia		Added a check in OnLButtonDown() Function for USBMemory Button when USB Memory is absent
  1.20		    12/07/05	BWadia		Modified for tracker issue 4005,4030,4026,4031,4024,4009,4035,3978,3942.
  1.21		    12/20/05	BWadia		Modified for tracker issue 4029,3976,4004,4015,4034.
  1.22		    12/20/05	BWadia		Modified for tracker issue 3976.
  1.23		    01/02/06	BWadia		Modified for tracker issue 3960,3970,3986,4052.
  1.24		    01/03/06	BWadia		Modified for tracker issue 3972
  1.25		    01/13/06	BWadia		Dummy Check In.
  1.26	 	    01/13/06	BWadia		Modified for tracker issue 3957.
  1.27		    01/23/06	BWadia		Modified HandleAlarmChangeInPolling function for not to drawAlarmButton.
  1.28		    02/07/06	BWadia		Added functions GetWeldDataIdArray() and GetGraphWeldDataIdArray()
  1.29		    02/14/06	BWadia		Added USBGlobalFlag
  1.30		    02/22/06	BWadia		Added USBMutex
  1.31		    03/21/06	YGupta		Modified for Tracker issue 4094.
  1.32		    03/22/06	YGupta		Modified for Tracker issue 4099.
  1.33		    04/13/06	YGupta		Added LargeWaitingTime variable and modified BuildScreenSetupMenu function.
  1.34		    04/24/06	YGupta		Modified for  HornScan.
  1.35		    05/24/06	YGupta		Modified for OnPollingTime Variable to change polling wait time.
  1.36		    05/26/06	YGupta		MOdified AnalysePollingCommand() function for EStopOnHornDown;
  1.37		    07/03/06	YGupta		Modified for Alarm button on Graph screen and for PMC screen live update.
  1.38		    07/20/06	YGupta		Modified USBPresent function to detect empty USB stick.
  1.39		    09/18/06	BSahu		   Modified Code to Display Password keypad On ColorsetUp, History 
									         and Preset screens.
  1.40	 	    12/13/06	BSahu		   Modified GetAveragePowerGraph() For 2Graph Lock Issue.
  1.41		    12/22/06	BSahu		   Modified MouseClick() For Senser Calibration Screen PopUp.
  1.42		    01/03/07	BSahu       Modified ProcessNak() For DisplayLock.
  1.43		    01/17/07	BSahu		   Modified AnalyzePolling() For Printer Alarm.
  1.44		    01/31/07	BSahu		   Modified CheckPrinterStatus() & SendPollingCommand() for Printer Offline Changes
  1.45		    02/27/07	BSahu		   Modified BottomHalfTimer in OnTimer() for Memory-Leak Issue.
  1.50          03/08/07   LAM         Add German, Spanish, & Korean Updates 
  1.51		    03/12/07	BSahu		   Modified DrawMenu() For PMC Bands & added Defination DisplayWeldIsGoingOnMessage()
  1.52          03/27/07   BSahu       Added SendCommandForQualityWindow() & SaveVQSData() For VQS Application
                                       and Modified BuildPrintList() for VQS limits Display
  1.53          03/29/07   BSahu       Added PrintVQSLimits() to Print VQSLimits In WelsetUp Print Out.
  1.54          04/05/07   BSahu       Modified AnalyzePollingResponse() For Test , EStop On VQS Screen.
  1.55          04/12/07   BSahu       Modified AnalyzePollingResponse() For Test, VQS Issue.Modified Code
                                        For HighLight Color Button.
  1.56          04/24/07   BSahu       Modified ExitProgram() For VQS Issue.
  1.57          05/04/07   BSahu       Modified Analyzepolling For Memory Leak Issue Issue,
                                       (Tracker Issue- 4109)
  1.58          05/23/07   BSahu       Modified MouseClick(),BuildPrintList(),OnPrint() for print button on RunScreen & RecalculateMenuLayout() 
                                       for Tracker issue 4118,4119 
  1.59          05/28/07   BSahu       Modified  BuildPrintList() & PrintOnAlarmAndSample() for 
                                       Tracker Issue 4139 & OnTimer() for tracker issue 4159.
  1.60          06/05/07   BSahu       Modified OnPrint() for Graph Page Printout.
  1.61          06/11/07   BSahu       Modified Add_Back_Next_Button() for tracker issue. 
  1.62          06/12/07   YGupta      Modified Add_Back_Next_Button() for tracker issue 4172
  1.62.1.0      10/23/07   PDwivedi    Added changes for MultiLang support.
  1.62.1.1      01/11/08   PDwivedi    Modified OnPaint(),OnLButtonDown(),OnLButtonUp(),ProcessNak() for MultiLang Suopport.
  1.62.1.2	    01/11/08   PDwivedi	   Remove File "VgaColorSetup.h".	
  1.62.1.3	    04/04/08   PDwivedi    Modify OnLbuttonDown(),OnLButtonUp,OnTimer(),SendPollingData()  function MultiLang Support.
  1.62.1.4      04/14/08   PDwivedi	   Modify GetRamData(),OnTimer & GetButtonShape() for MultiLangSupport.
  1.62.1.5      04/16/08   PDwivedi    Modify DrawFirstScreen,Analyzepolling for MultiLangSupport.
  1.62.1.6      06/06/08   PDwivedi    Modify OnLButtonDown,OnLbuttonUp,OnTimer,Analyzepolling for NewPointerList Prepration & Added Alarm Changes.
  1.62.1.7      08/01/08   PDwivedi    Added Printer & USB Changes,Removed All Local Strings.
  1.62.1.8      08/04/08   PDwivedi    Modified Analyzepolling() for E-stop.
  1.62.1.9      08/08/08   PDwivedi    Final Code Clean up.
  1.62.1.10     08/26/08   PDwivedi    Added changes for display lock & modify ProcessNak.
  1.62.1.11     09/02/08   PDwivedi    Modify OnPaint() & BottomHalfTimer for BottomHalf Screen.
  1.62.1.12     09/04/08   PDwivedi    Modify OnPaint() for VQS & RecalculateMenuItemsLayoutScreen.
  1.62.1.13     09/09/08   PDwivedi    Added changes for Tracker issues.
  1.62.1.14     09/12/08   PDwivedi    Added changes for Tracker issues of round 2 testing for version LangTestJ.
  1.62.1.16     09/18/08   PDwivedi    Added changes for bottomHalf Screen size & color .
  1.62.1.17     09/24/08   PDwivedi    Added Changes for Printing for Sequencing & WeldData PrintNow.
  1.62.1.18     10/01/08   PDwivedi	   Added changes for ABS Mode value on RunScreen(checked in version Ver10.40).
  1.62.1.19     11/07/08   PDwivedi	   Added changes for Controllevel & Actuator issues.
  1.62.1.20     11/12/08   PDwivedi    Added changes for SBC Fatal Error.
  1.62.1.20.1.0 09/22/09   PDwivedi    Modify Analyzepolling() for Micro Actuator.
  1.62.1.20.1.1 10/07/09   PDwivedi    Replacing Try and catch statements with TRY and CATCH 
                                       Macro to support Exception Handling.
  1.62.1.20.1.2 10/30/09  PDwivedi     Added changes for Graph & Test Key Bug Issue for MICRO.
  1.62.1.20.1.3 11/06/09  PDwivedi     Added changes for showing String number on RunScreen .
  1.62.1.20.1.4 11/18/09  PDwivedi     Added changes for Ethernet CleanUp and faster serial communication.
  1.62.1.20.1.5 10/13/10  PDwivedi     Added new functions ReadStartUpVersionString 
                                       and ReadSystemVersionString.
  1.62.1.20.1.6 12/28/10  PDwivedi     Added new functions GetCurrentFilePath to make USB Folder according  
                                       to  Date and Time received from 332 Weld Data.
  1.62.1.20.1.7 02/28/11  PDwivedi     Added changes for USB Memory Full Alarm.
  1.62.1.21.1.8 03/03/11 PDwivedi      Added changes for USB Memory Full Alarm(Recalibrate Actuator alarm).
  1.62.1.21.1.9 03/08/11 PDwivedi      Added changes for USB Memory Full Alarm(increase minimum USB space).
  1.62.1.21.1.10 08/09/13 HsanchezZ    Added change to allow print the weld data on sample and on error 
  1.62.1.21.1.11 09/20/17 RChapa	   Added function to reload Start_Screen at E-Stop Reset
*/       

// ChildView.cpp : implementation of the CChildView class
//
#include "stdafx.h"
#include "Application.h"
#include "ChildView.h"
#include "ListBox.h"
#include "RunScreen.h"
#include "VgaMenuItem.h"
#include "EtherPort.h"
#include "CommPort.h"
#include "VgaTitle.h"
#include "shellapi.h"
#include "VgaButton.h"
#include "Mylanguage.h"
#include "Text.h"
#include "RadioMenu.h"
#include "SBC.h"
#include "VgaBottomMenu.h"
#include "VgaScreenSetup.h"
#include "VgaChoice.h"
#include "VgaSubMenu.h"
#include "VgaAlphanumeric.h"
#include "BottomHalf.h"
#include "Check.h"
#include "VgaVariable.h"
#include "MsgScreen.h"
#include "AlarmButton.h"
#include "Table.h"
#include "Toggle.h"
#include "USBFolder.h"
#include "WeldingHistory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ABSGAP			            15
#define SIZEOFVQSPRESETDATA		64
#define MAX_PRESET		         17
#define SIZEOFVQSSYSCON          8
#define VQSLIMITPAGE             11
/////////////////////////////////////////////////////////////////////////////
// CChildView

extern void GetGraphData(unsigned char RequestType);
extern CMapStringToString values;
extern bool ProcessAlarmMenu(CVgaButton *);
extern CList<CString,CString> tempHistoryList;
extern CList<CString,CString> tempWeldList;
extern CList<CString,CString> tempHornScanList;
extern CList<CString,CString> tempGraphsList;
extern CList<CString,CString> tempScreenGraphsList;
extern CList<CString,CString> tempSetupList;
extern CList<CString,CString> tempScanGraphDataList;
extern CList<CString,CString> tempRunScreenList;
extern POSITION RunScreenTemp_pos;
extern POSITION ScreenGraphsTemp_pos;
extern POSITION GraphsTemp_pos;
extern POSITION HistoryTemp_pos;
extern POSITION WeldTemp_pos;
extern POSITION HornScanTemp_pos;
extern POSITION ScanGraphsDataTemp_pos;
extern POSITION SetupTemp_pos;
extern POSITION DUPSTemp_pos;
extern POSITION SequenceTemp_pos;

extern void SetGraphObjectMember(unsigned char * &data, int & length,CVgaDrawGraph * Graph);
extern void SetHornScanObjectMember(unsigned char * &data, int & length,CVgaDrawGraph * Graph);
CChildView* CChildView::thisPtr;
CChildView::CChildView()
{
   listbuild = false;
   CBottomHalf::HornDownScreenPresent=false;
	ViewGraphWeldData=0;
	USBAlarm=false;
   USBFullAlarm = false;
	RunResultScreen=false;
	AlarmScreenOnCalibration=false;
	IsAlarmScreen=false;
	AlarmPresent=false;
	DisableFlag =false;
	thisPtr = this;
	IsLanguageMenu=false;
	page_no=1;
	AbortPrinting=false;
	GraphOneRequestValue=2;
	GraphTwoRequestValue=0;
	LowerPMCLimit=0;
	UpperPMCLimit=0;
	PMCDisable=false;
	HornScanPlzWait=false;
	CommandForAlarmButton=false;
	USBGlobalFlag=false;
	LargeWaitingTime=false;
	PollingTimeOnMsgScrn=false;
	CurrMenuList=NULL;
   MenuNameID="";
   AlarmMenuIdentifier="";
   AlarmMenuName="";
   OverWritePreset=false;
   CopyPresetNum =0;
   OverWritePSPreset=false;
   OverWritePresetNum=0;
   CopyAllFlag=false;
   BrowseUSB=false;
   MenuUSBDraw=false;
   BottomHalfScreen=false;
   StringDebugFlag=false;
   EnableUSBGraph=false;
   AlarmUpdateRequired=false;
   CurrentFilepath = "";
 //	WaitForCommand.SetEvent();
}
   CVgaMenuItem *GlobalAlarmObject;
   int CChildView::StartWeldData;
   CStringArray CChildView::WeldDataPatamStringID;   
   CString CChildView::PSName;
   CList<CString, CString>CChildView::USBPresetNames;
   int CChildView::TotalUSBPreset;
   int CChildView::SelectedUSBPreset=0;
   int CChildView::SelectedPowerPreset=CChildView::CurrentPresetNum;
   bool CChildView::LastSelectedPresetFrom;   
   bool CChildView::PMCScreen=false;
   CString CChildView::ScanString;
   int CChildView::TempCount=0;
   bool CChildView::ColdStartInProcess=false;
   CString CChildView::mainmenu_string;
   CString CChildView::WeldResult_string;
   CString CChildView::WeldSetup_string;
   CString CChildView::Graphs_string;
   int CChildView::Currentlanguage=0;
   bool CChildView::RunResultScreen=false;
   bool CChildView::PowerUpSBC=false;
	bool CChildView::PollingTimeOnMsgScrn;
	bool CChildView::LargeWaitingTime;
	bool CChildView::USBGlobalFlag;
   struct CChildView::PrintValues Setup,Welddata,WeldHistory,PowerGraph,ColDistance,VelocityGraph,
			   ForceGraph,AmplitudeGraph,FrequencyGraph,PrintSequence;

   struct CChildView::USBValues  USBWelddata,USBPowerGraph,USBColDistance,USBVelocityGraph,
			   USBForceGraph,USBAmplitudeGraph,USBFrequencyGraph;

   bool CChildView::CommandForAlarmButton;
   struct CChildView::PrintingSetup PrintSetup;
   CString CChildView::USBSelectedPresetName;
   CString CChildView::PSPresetText[MAX_PSPRESET];
   CString CChildView::LastUSBPresetFolder;

   int CChildView::ColumnPerPage;
	int CChildView::ButtonType;
	int CChildView::RowPerPage;
   int CChildView::HWconfiguration;
   int CChildView::SWconfiguration;
   int CChildView::Securitylevel;
   int CChildView::WeldMode;
   int CChildView::Actuator;
   int CChildView::ControlLevel;
   int CChildView::AccessLevelSystem;
   int CChildView:: ExitButtonFlag;
   int CChildView::SaveButtonFlag;
	int CChildView::ViewGraphGlobalCount;
	int CChildView::PMCMaxVdata;
	int CChildView::CurrentSequencePreset=0;
	bool CChildView::PMCDisable;
	int CChildView::LowerPMCLimit;
	int CChildView::UpperPMCLimit;
	bool CChildView::ISUSBPresent;
   bool CChildView::SaveRecallPresetScrn;
	bool CChildView::ContinuePrinting;
	bool CChildView::AbortPrinting=false;
	CString *CChildView::Parameter_Heading;
	CString *CChildView::Parameter_Units_Metric;
	CString *CChildView::Parameter_Units_USCS;
  	int *CChildView::Parameter_ID;
   int CChildView::TotalTextHeading;
   bool CChildView::PrinterPresent=false;
	int CChildView::BotomHalfRefreshTime=0;
	bool CChildView::ActColdStartFlag =false;
	bool CChildView::IsNewScreenPointer=false;
	bool CChildView::BottomHalfTimerOn=false;
	bool CChildView::powerup=false;
	int CChildView::TextColor=Black;
	int CChildView::Button_Color=Gray;
	int CChildView::TitleBarColor=Blue;
	int CChildView::Back_Color=White;
   int CChildView::Highlight_Color=Green;
	bool CChildView::SysInfoScreen=false;
	bool CChildView::Start_Screen=0;
	int CChildView::Language_Index=0;
	bool CChildView::IsTwoSecExpired=false;
	bool CChildView::metric=false;
   bool CChildView::PasswordFlag=false;
	bool CChildView::AutoRefreshon =false;
	bool CChildView::AmplitudeMicrons =false;
	bool CChildView::PeakPowerMicrons =false;
	int CChildView::PeakPowerWattsMax;
	int CChildView::AmplitudeMicronsMax;

	bool CChildView::ScreenSetupFlag=false;
	bool CChildView::DisableFlag=false;
	int CChildView::RAMCalibCordinate_Xa;
	int CChildView::RAMCalibCordinate_Ya;
	int CChildView::RAMCalibCordinate_Xb;
	int CChildView::RAMCalibCordinate_Yb;
	int CChildView::CurrentPresetNum=0;
	int CChildView::WeldCycleCount;
	int CChildView::PrinterStatuscheck=0;
	int CChildView::PresetNum;
	int CChildView::AlarmCount;
	int CChildView::GraphOneRequestValue=0;
	int CChildView::GraphTwoRequestValue=0;
	int CChildView::Presettrack=0;
   int CChildView::MaxPreset=0;
DWORD CChildView::Color_Array[]={
									RGB(0,0, 0),//ColorNone
									RGB(0, 0, 0),//Black
									RGB(0, 0, 255),//Blue
									RGB(255,0,0),//Red
									RGB(0,255,0),//Green
									RGB(128,42,42),//Brown
									RGB(255,0,255),//Magenta
									RGB(0,255,255),//Cyan
									RGB(88,88,88),//Dark_Gray
									RGB(127,127,127),//gray
									RGB(255,255,0),//Yellow
									RGB(255,255,255)//white	
								};


CChildView::~CChildView()
{
   //printf("\n ~CChildView");
   BottomHalfTimerOn=true;
   while (keypadList.GetCount())
	  delete keypadList.RemoveHead();

   menusname.RemoveAll();
   menus.RemoveAll();
   menupointers.RemoveAll();
  
	delete []Parameter_Heading;
	delete []Parameter_Units_Metric;
	delete []Parameter_Units_USCS;
	delete []Parameter_ID;

   while(USBPresetNames.GetCount())
		USBPresetNames.RemoveHead();  
	
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_MAINMENU, OnMainMenu)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		0,HBRUSH(COLOR_WINDOW) , NULL);
	powerup=true;
	DrawFirstScreen();//Getting First MenuScreen.
   return TRUE;
}

/*******************************************/
/*this function is for drawing the screen .*/
/*******************************************/

void CChildView::OnPaint() 
{
	CPaintDC dc1(this); // device context for painting
	CDC * pDC = &dc1;
	CDC dc;
	CDC* pDrawDC =pDC;
	
	CBitmap bitmap;
	CBitmap* pOldBitmap;
	if (!pDC->IsPrinting())
	{
		// draw to offscreen bitmap for fast looking repaints
		if (dc.CreateCompatibleDC(pDC))
		{
			if (bitmap.CreateCompatibleBitmap(pDC, MAX_VGA_X_VALUE+2*XOFFSET,
													MAX_VGA_Y_VALUE+2*XOFFSET))
			{
				pDrawDC = &dc;
				pOldBitmap = dc.SelectObject(&bitmap);
			}
		}
	}
   	
   CBrush brush;
	if(theApp.GraphsDataList.GetCount()>0)
		brush.CreateSolidBrush(Color_Array[White]);
	else
	brush.CreateSolidBrush(Color_Array[Back_Color]);
	CBrush * oldBrush;
	oldBrush = pDrawDC->SelectObject(&brush);
	pDrawDC->Rectangle(VGA_Rect);
	pDrawDC->SelectObject(oldBrush);
   
   if(OnKeypadScreen_flag==true)
	   DrawKeypad(pDrawDC);//draw keypad.
	else
	   theApp.DrawMenu(pDrawDC);
	DrawPageNumber(pDrawDC);
   if((CChildView::thisPtr->BottomHalfScreen)&&(!OnKeypadScreen_flag))
   {
     // printf("\n BottomHalfScreen");
      int TempColor=TextColor;
      POSITION pos = CBottomHalf::BottomMenuPointer->items.GetHeadPosition();
	   while(pos)
	   {
         CVgaMenuItem *Object = CBottomHalf::BottomMenuPointer->items.GetNext(pos);
         if(Object->IsDraw)
         {
		      if(CChildView::TextColor==White)
               CChildView::TextColor=Black;
            Object->Draw(pDrawDC);
         }
	   }
      TextColor=TempColor;
   }

	pDC->BitBlt(0,0,MAX_VGA_X_VALUE+2*XOFFSET,MAX_VGA_Y_VALUE+2*XOFFSET,&dc,0,0,SRCCOPY);
	dc.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	brush.DeleteObject();
   PowerUpSBC=false;
}



/*****************************************************************************/
/* Function is used to get starting information at power up.				 */
/*****************************************************************************/
void CChildView::DrawFirstScreen()
{
   CChildView::ColdStartInProcess=false;
   bool GetFirstScreen=false;
	while(!GetFirstScreen)
	GetFirstScreen=app->GetBottomMenuAddress(&Start_Screen,&WeldResults_Address,
								&mainMenuAddress,&WeldSetup_Address,
								&GraphsMenu_Address,&Language_Index,&metric);
   GetRAMData();
   theApp.PrepareStringFromUnicodeText(CurrentLanguageName,true,true);
   theApp.GetSystemVariable();
   CChildView::AccessLevelSystem=OPERATOR;
   theApp.ReadXML();

   if((ReadStartUpVersionString()==true) &&
   (ReadSystemVersionString()==true) )
   {
      GetWeldDataIdArray(false);
	   GetGraphWeldDataIdArray(false);
      while(!SendCommandForStateMachineEnable());
      WaitForPrintData.ResetEvent();
      AfxBeginThread(CChildView::PrintingThread,0);
      /* Start the USB Thread and Reset the USB Event.*/
	      WaitForUSBData.ResetEvent();
	   AfxBeginThread(WriteDataToUSB, 0  );
      WaitForEtherNetAlarmHandle.ResetEvent();
      AfxBeginThread(EtherNetAndAlarmHandle, 0  );
   }
   else
   {
      theApp.menuName = CVgaBottomMenu::MenuErrorID;//"550";
    
      CVgaMenu * menu;

      if (theApp.menus.Lookup(theApp.menuName, menu))
      {
	      theApp.MenuPointer=menu;
         ModifyObjectList(menu);   
      }
   }
}

bool CChildView::SendCommandForStateMachineEnable()
{
   CHostCommand * request = new CHostCommand(STATEMACHINE_ENABLED,0,0);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
     char ch=CHostCommand::AckNak();
     if(ch==theApp.ACK)
     {
        delete response;
        return true;
     }
     else
     {
        delete response;
        return false;
     }
   }
   return false;
}

/****************************************************************************/
/*    Function is called when user presses the left mouse button or presses */
/*    any  button on the screen.                                            */
/****************************************************************************/ 
void CChildView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
   POSITION pos = menu1->items.GetHeadPosition();
   if(ScreenSetupFlag!=true)//calibration will not apply on Screen setup screen.	
      point= CalibratePoint(point);

	CDC*pDC = GetDC();
	if(OnKeypadScreen_flag)
	{
      if(!DisableFlag)
		{
		//	printf("\n !DisableFlag keypad");
         CVgaMenuItem * object=menu1->items.GetHead();//Bottom menu or screen set up screen processed.
         POSITION pos1 = menu1->items.GetHeadPosition();
         while(pos1)
         {
           object = menu1->items.GetNext(pos1);
			   if(object->GetType() == CVgaMenu::BottomMenu_Id)
            {
               break;
            }
         }
         if (object->MouseClick(point, this))
			{
			//	printf("\n MouseClick");
            ReleaseDC(pDC);
				return;
			}
			else
			{
			//	printf("\n Screen MouseClick");
            CScreenKeypad *object=keypadList.GetTail();
				object->DrawPressedkey(point, pDC);
				ReleaseDC(pDC);
				return;
			}
		}
		else
		{
		//	printf("\n DisableFlag keypad");
         ReleaseDC(pDC);
			return;
		}
	}

	CVgaMenuItem * object;

   
		/*	If disable flag is ON then only confirm screen button */
	/*  will be processed,other will be ignored.              */
	if(DisableFlag)
	{
	//	printf("\n DisableFlag on");
      bool MessgObject=false;
      POSITION pos1 = menu1->items.GetHeadPosition();
		while (pos1)
		{
			object = menu1->items.GetNext(pos1);
         while((!object->IsDraw)&&(pos))
            {
                object = menu1->items.GetNext(pos);
            }
         if(object->GetType() == CVgaMenu::VGAMsgScrnObject)
         {
            MessgObject=true;
         }
         else if((object->GetType() == CVgaMenu::VGA_Button_OBJECT)&&(MessgObject))
				{
					if (object->GetRect().PtInRect(point))
					{
                  object->SetButtonState1(true) ;
						object->Draw(pDC);
						DisableFlag=false;
						ReleaseDC(pDC);
						return;
					}
				}
		}
	}
   pos = menu1->items.GetHeadPosition();
	while (pos)
	{
		object = menu1->items.GetNext(pos);
      if((object->GetType() == CVgaMenu::VGABottomHalfObject)&&(object->GetRect().PtInRect(point)))
      {
         CBottomHalf *obj=(CBottomHalf*)object;
       //  printf("\n inside bottom menu point");
        // CString MenuName=obj->submenu;
         if(MenuNameID!="")
         {
           // printf("\n MenuNameID!=");
            if(!theApp.menus.Lookup(MenuNameID/*MenuName*/, menu1))
            {
             //  printf("\n return from bottom");
               return;
            }
            POSITION pos1=menu1->items.GetTailPosition();
            object = menu1->items.GetPrev(pos1);
            object = menu1->items.GetPrev(pos1);
            if((object->PSType == CVgaMenu::VGA_Button_OBJECT)&&(object->RectShow))
            {
               if(object->GetRect().PtInRect(point))
               {  
                  if(!DisableFlag)
                  {
                     if(object->MouseClick(point, this))
					      {
						      object->SetButtonState1(true) ;
						      object->Draw(pDC);
                        if(object->GetButtonState1()==true)
                           object->SetButtonState1(false) ;
                     
                      }
                  }
                  ReleaseDC(pDC);
						return;
               }
            }
            pos1 = menu1->items.GetHeadPosition();
		      while (pos1)
		      {
			      object = menu1->items.GetNext(pos1);
               if((object->GetType() == CVgaMenu::VGA_Button_OBJECT)&&(object->RectShow)&&(object->IsDraw))
               {
                  if(object->GetRect().PtInRect(point))
                     if(object->MouseClick(point, this))
					      {
                        object->SetButtonState1(true) ;
						      object->Draw(pDC);
                        if(object->GetButtonState1()==true)
                           object->SetButtonState1(false) ;
                       // KillTimer(BottomHalfTimer);
						      DisableFlag=false;
                       // object->RectShow=false;
						      ReleaseDC(pDC);
						      return;
					      }
               }
            }
          //  printf("\n return after all operation");
            ReleaseDC(pDC);
            return;
         }
      }
   }


	/*	If disable flag is off then process other buttons.*/
	if(!DisableFlag)
	{
	//	printf("\n !DisableFlag");
		object=menu1->items.GetHead();//Bottom menu or screen set up screen processed.
		pos = menu1->items.GetHeadPosition();
      if (pos)
		{
			object = menu1->items.GetNext(pos);
         if(object->GetType() == CVgaMenu::VGA_Button_OBJECT)
         {
          //  printf("\n colorsetup downbutton");   
            if (object->GetRect().PtInRect(point))
					{
              //    printf("\n in rect down");
                  object->SetButtonState1(true) ;
						object->Draw(pDC);
					//	DisableFlag=false;
						ReleaseDC(pDC);
						return;
					}
				
         }
		}
      pos = menu1->items.GetHeadPosition();
      while (pos)
		{
		 // printf("\n different condition");	
		   object = menu1->items.GetNext(pos);
         while(!object->IsDraw)
         {
            object = menu1->items.GetNext(pos);
         }
		   if((object->GetType() == CVgaMenu::COLORSETUP_ID)
            ||(object->GetType() == CVgaMenu::BottomMenu_Id))
				if (object->MouseClick(point, this))
					{
					//printf("\n return from it");
                  ReleaseDC(pDC);
						return;
					}
		}
      if(AlarmUpdateRequired)
      {
         if (GlobalAlarmObject->GetRect().PtInRect(point))
		   {
			   GlobalAlarmObject->SetButtonState1(true) ;
			   GlobalAlarmObject->Draw(pDC);
			   ReleaseDC(pDC);
			   return;
		   }
      }
/* If Current screen is not keypad screen process menu button*/ 		
		if(!OnKeypadScreen_flag)
		{
		//	printf("\n !OnKeypadScreen_flag");
			int items = 0;
			pos = menu1->items.GetHeadPosition();
			object = menu1->items.GetNext(pos);
			//Counting the objects except VGA Buttons.
			int Current_page_no=page_no;///adding page no.
			while (pos)
			{
				object = menu1->items.GetNext(pos);
            while(!object->IsDraw)
            {
               object = menu1->items.GetNext(pos);
            }
				if( (object->PSType!=CVgaMenu::TITLE)&&((object->GtPageNum()== Current_page_no)
					||(object->GtPageNum()== CVgaMenuItem::PAGEALL)))
				{
               if (object->GetRect().PtInRect(point))
					{
						if((object->PSType==CVgaMenu::TITLE) || 
							(object->PSType == CVgaMenu::TEXT) ||
							(object->PSType == CVgaMenu::VGATEXT)
							||(object->PSType==CVgaMenu::VGATableObject)
                     ||(object->PSType== CVgaMenu::VGABottomHalfObject))
						{
							ReleaseDC(pDC);
							 return;								
						}
                  if((object->RectShow))
                  {
                     object->SetButtonState1(true) ;
                  }
                  
                  if((object->PSType != CVgaMenu::VGATOOLMAP))
						{
                     object->Draw(pDC);
						}	
						ReleaseDC(pDC);
						return;
					}
            }
		
			}
		
		}
		
		//process keypad.
		ReleaseDC(pDC);
	}
}

void CChildView::OnMainMenu() 
{
//	BuildMenu(GetMenuData_FunId,mainMenuAddress);
	Invalidate();
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}

/******************************************************************/
/*      Function giving the rectangle To the Back next button.    */
/******************************************************************/
void CChildView::Back_Next_Button_Layout()
{
   CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
	/*Give co-ordinates to back,next,exit and save buttons.*/
	POSITION pos = menu1->items.GetTailPosition();
	while (pos)
	{
		CVgaMenuItem * object = menu1->items.GetPrev(pos);
		int type = object->GetType();
		if (type == CVgaMenu::NEXT)
		{
         object->SetRect(NextButtonRect);
		}
      
	}
	pos = menu1->items.GetTailPosition();
	while (pos)
	{
		CVgaMenuItem * object = menu1->items.GetPrev(pos);
		int type = object->GetType();
		if (type == CVgaMenu::BACK)
		{
          object->SetRect(BackButtonRect);
		}
    }
}
/***********************************************************************************/
/*  Function adding the Back Next button in the list According to the Object Count */
/*  To be Display.																   */
/***********************************************************************************/
void CChildView::Add_Back_Next_Button()
{  
	bool next_prev=false;
   CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
   if(Total_Text_Objects<Max_Text_1_Coloum)	
	{

      CTypedPtrList<CPtrList, CVgaMenuItem *> TempDataList;
			mutex.Lock();

      while(menu1->items.GetCount()>0)
	   {
		   CVgaMenuItem *Obj = menu1->items.GetHead();
		   int type = Obj->GetType();
         if((type==CVgaMenu::NEXT)||(type==CVgaMenu::BACK))
		   {
            delete menu1->items.RemoveHead();
		   }
		   else
		   {
			   TempDataList.AddTail(Obj);
			   menu1->items.RemoveHead();

		   }
	   }
	   POSITION pos2 = TempDataList.GetHeadPosition();
	   while(pos2)
	   {
		   CVgaMenuItem *Obj = TempDataList.GetNext(pos2);
		   menu1->items.AddTail(Obj);
	   }
	   while(TempDataList.GetCount())
		   TempDataList.RemoveHead();
	   bool prev_button=false;
	   
	   if((page_no>1))
	   {
		   prev_button=true;
		   menu1->items.AddTail(CVgaMenu::CreateObjectBack_Next(CVgaMenu::BACK));
      
	   }
	   if(Total_Objects >(page_no*RowPerPage*ColumnPerPage))
      {
         menu1->items.AddTail(CVgaMenu::CreateObjectBack_Next(CVgaMenu::NEXT));
      
      }
	}
	mutex.Unlock();
}

/*********************************************************/
/*    Function is called at left mouse button up.        */
/*********************************************************/
void CChildView::OnLButtonUp(UINT nFlags, CPoint point) 
{
   CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
   if(ScreenSetupFlag!=true)
      point= CalibratePoint(point);

	CDC*pDC = GetDC();
	CVgaMenuItem * object;
	POSITION pos = menu1->items.GetHeadPosition();

	/*checking if bottom menu is clicked */
   if(pos)
   {
      object = menu1->items.GetNext(pos);
      if((object->GetType() == CVgaMenu::VGA_Button_OBJECT))
      {
         if (object->GetRect().PtInRect(point))
		   {
	         if(object->MouseClick(point, this))
	         {
               object->SetButtonState1(false) ;
               ReleaseDC(pDC);		
		         return;
	         }
         }
      }
      else if(object->GetType() == CVgaMenu::BottomMenu_Id)
      {
         if(object->MouseClick(point, this))
	      {
            ReleaseDC(pDC);		
		      return;
	      }
      }
      
   }
   if(AlarmUpdateRequired)
   {
      if(GlobalAlarmObject->GetButtonState1()==true)
      {
         GlobalAlarmObject->SetButtonState1(false) ;
			GlobalAlarmObject->Draw_Pressed_Released_Button(pDC);//draw button in released condition.
			if(GlobalAlarmObject->MouseClick(point, this))
			{
				ReleaseDC(pDC);
			
				return;
			}
      }
   }
   pos = menu1->items.GetHeadPosition();
  if(!OnKeypadScreen_flag)
	{
     while (pos)
		{
			object = menu1->items.GetNext(pos);
			int Type =object->GetType();

			if(object->GetButtonState1()==true)
			{
				object->SetButtonState1(false) ;
				if((object->PSType!=CVgaMenu::VGATOOLMAP))
			      object->Draw_Pressed_Released_Button(pDC);//draw button in released condition.

            if((DisplayLockFlag &&((( object->AccessLevel > OPERATOR)&&(object->PSType== CVgaMenu::SUBMENU))
               ||(object->PSType==CVgaMenu::HHMM)||(object->PSType== CVgaMenu::DATE)
               ||(object->PSType==  CVgaMenu::CHOICE)||(object->PSType==  CVgaMenu::ALPHA)
               ||(object->PSType==  CVgaMenu::VARIABLE)||(object->PSType==  CVgaMenu::RADIO_BUTTON)
               ||(object->PSType==  CVgaMenu::RADIOMENU )||(object->PSType== CVgaMenu::TOGGLE)
               ||((object->PSType == CVgaMenu::VGA_Button_OBJECT)&&(object->AccessLevel > OPERATOR)))))/* Display Lock Active ?*/
             {
                ErrorBeep(); 
                CVgaMenu *menu;
                if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
                {
			         AccessLevelSystem=OPERATOR;
                  menusname.AddTail(theApp.menuName);
                  menus.AddTail(page_no);
                  menupointers.AddTail(theApp.MenuPointer);
                  page_no=1;
                  ModifyObjectList(menu);   
                  theApp.menuName=CVgaBottomMenu::mainMenuID;
                  theApp.MenuPointer=menu;   
                }
                ReleaseDC(pDC);
				    Invalidate();
                return;
             }
             else
             {
               if(object->MouseClick(point, this))
               {
				      ReleaseDC(pDC);
				      return;
               }
             }
			}
		}
	 }
	else if(OnKeypadScreen_flag)//process keypad
	{
      CVgaMenuItem * object=menu1->items.GetHead();//Bottom menu or screen set up screen processed.
      POSITION pos1 = menu1->items.GetHeadPosition();
      while(pos1)
      {
        object = menu1->items.GetNext(pos1);
		  if(object->GetType() == CVgaMenu::BottomMenu_Id)
        {
           break;
        }
      }
      if (object->MouseClick(point, this))
		{
			//printf("\n MouseClick");
         ReleaseDC(pDC);
			return;
		}
      else
      {
         CScreenKeypad *object=keypadList.GetTail();
		   object->MouseClick(point, this,pDC);
      }
	}
	ReleaseDC(pDC);
	//CWnd::OnLButtonUp(nFlags, point);
}

/********************************************/
/* This function will prepare keypad list.  */
/********************************************/

void CChildView::BuildCompleteKeypadList(int type,unsigned char *&data,CString* Object_Text,int ID,CVgaMenuItem *ptr)
{
   while (keypadList.GetCount())
	delete keypadList.RemoveHead();
   keypadList.AddTail(new CScreenKeypad(type,data,Object_Text,ID,ptr));
}
/*****************************************************/
/*   Function called from OnPaint to draw keypad.    */
/*****************************************************/
void CChildView::DrawKeypad(CDC*pDrawDC)
{
  CScreenKeypad *object1=keypadList.GetTail();
  object1->Draw(pDrawDC);
  CVgaMenu * menu1;
  menu1=theApp.MenuPointer;
  POSITION pos = menu1->items.GetHeadPosition();
  CVgaMenuItem * object=menu1->items.GetNext(pos);
  object->Draw(pDrawDC);
  while(pos)
	{
     object=menu1->items.GetNext(pos); 
     if(object->GetType()== CVgaMenu::BottomMenu_Id)			
      {
         object->Draw(pDrawDC);
         return;
      }
   
	}
}

/*****************************************************************************/
/*  This function will handle different timers used i.e. for keypad,		 */
/*  for Polling command,for message screen,for bottom half refresh.			 */
/*****************************************************************************/
void CChildView::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
      
      case AlphaEntryTimer:
			{
				KillTimer(AlphaEntryTimer);
				CDC * pDC=GetDC();
				IsTwoSecExpired=true;
				if(OnKeypadScreen_flag)
					CScreenKeypad::VGAAlphaEntry(pDC);
				ReleaseDC(pDC);
			}
		break;

		case Pollingtimer:
			{
				
				KillTimer(Pollingtimer);
				SendPollingCommand();
		   if(MenuUSBDraw)
               MenuUSBDraw=false;
			if(AbortPrinting)
			{
			
            while (GraphPrintList.GetCount()>0)
					delete GraphPrintList.RemoveHead();

            while(GraphWeldDataPrintList.GetCount()>0)
					delete GraphWeldDataPrintList.RemoveHead();
            
				while(PrintObjectList.GetCount()>0)
					delete PrintObjectList.RemoveHead();
				
            while(PrintSequenceObjectList.GetCount()>0)
					delete PrintSequenceObjectList.RemoveHead();

				
            while(WeldDataPrintList.GetCount()>0)
					delete WeldDataPrintList.RemoveHead();

 			
				while(PrintWeldHistoryList2.GetCount()>0)
					delete PrintWeldHistoryList2.RemoveHead();

				while(PrintGraphTextObjectList.GetCount()>0)
					delete PrintGraphTextObjectList.RemoveHead();

				while(PrintGraphWeldDataList2.GetCount()>0)
					delete PrintGraphWeldDataList2.RemoveHead();
            
            while (HSGraphPrintList.GetCount()>0)
					HSGraphPrintList.RemoveHead();

				WeldAlarmStringList.RemoveAll();
				WeldHistoryAlarmStringList.RemoveAll();
				GraphAlarmStringList.RemoveAll();

				PrintInfoList.RemoveAll();
				CChildView::AbortPrinting=false;
			}
			}
		break;

		case BottomHalfTimer:
		{
			if(OnKeypadScreen_flag)
			{
				KillTimer(BottomHalfTimer);
            BottomHalfTimerOn=false;
            CChildView::thisPtr->BottomHalfScreen=false;
				
			}
			else
			{	
		   	KillTimer(BottomHalfTimer);
            CVgaMenu * menu1=theApp.MenuPointer;
            CString MenuName=theApp.menuName;
            int type=-1;
            POSITION pos = menu1->items.GetHeadPosition();
            CVgaMenuItem * Object;
            while(pos)
				{
					Object = menu1->items.GetNext(pos);
               if(Object->GetType() == CVgaMenu::VGABottomHalfObject)
               {
                  CBottomHalf *obj=(CBottomHalf*)Object;
                  type=obj->Bottomtype;
                  break;
               }
            }
            if(type==0) 
            {
               KillTimer(BottomHalfTimer);
              	if(CBottomHalf::BottomMenuPointer!=0)
                  menu1=CBottomHalf::BottomMenuPointer;
               int length =2;
               unsigned char data1[2];
				   union 
		               {
			               short i;
			               char c[2];
		               } u;
		             u.i=CBottomHalf::BottomHalfId;
          
                
               data1[1]=u.c[0];
				   data1[0]=u.c[1];
			      unsigned char * data = (unsigned char *) &data1[0];
               CHostCommand * request = new CHostCommand(GetBottomMenuData_FunID, data, length);
				   CHostCommand * response = app->SendPollingHostCommand(request);
               if(response)
               {
                  char ch=CHostCommand::AckNak();
			         data = response->GetData();
			         length = response->GetDataLength();
                  if(ch==ACK)
			         {
                     int MenuID=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     char TempArrayfg[10];
			            CString Temp=_itoa(MenuID,TempArrayfg,10);
                     if((MenuID!=0) && (MenuNameID!=Temp))
                     {
                        if(!theApp.menus.Lookup(Temp, menu1))
                        {
                          // printf("\n return");
                          // return;
                        }
                        MenuNameID=Temp;
                        CBottomHalf::BottomMenuPointer = menu1;
                     }
                     
                     POSITION pos = menu1->items.GetHeadPosition();
						   int count =0,Temp1=0;
                     
			            CString String1,String2;
                     int NoOFText=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     int *ID=new int[NoOFText];
                     for(int i=0;i<NoOFText;i++)
                     {
                        ID[i]=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
                     }
                     int NoOFChoice=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     int *Value=new int[NoOFChoice];
                     for(int j=0;j<NoOFChoice;j++)
                     {
                        Value[j]=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     }
                     DisableFlag = false;
                     while(pos)
						   {
							   Object = menu1->items.GetNext(pos);
							   if(Object->GetType() == CVgaMenu::RADIOMENU)
								{
								   CRadioMenu * ptr= (CRadioMenu *)Object;
                           CString Temptext=ptr->VarText;
								   for(int i=0;i<=(MAXRADIOINDEX-1);i++)
									{
										if(i==ID[count])
										{
											ptr->RadioIndex = ID[count];
											ptr->VarText = ptr->RadioMenuStr[i];
										}
										
									}
                           SetDimension(ptr,count);
                           Object->IsDraw=true;
                           count++;
                        }	
							   else if(Object->GetType() == CVgaMenu::VGACheck)
                        {
                           CCheck *Checkpointer= (CCheck *)Object;
                           Checkpointer->IsSelected=Value[count];//[Temp1];
                           Object->IsDraw=true;
                           count++;
                           
                        }
                        else if(Object->GetType() == CVgaMenu::VARIABLE)
                        {
                            CVgaVariable *ptr=(CVgaVariable *)Object;
                            CString Temp;
                            char TempArray[LINESIZE+1]="                    ";
                            ID[count] = CScreenKeypad::ConvertInternalExternal( ID[count],(CScreenKeypad::FORMAT)ptr->Format);
                            ptr->Insertunitflag=false;
                            CScreenKeypad::InsertProperUnits(ptr,(CScreenKeypad::FORMAT)ptr->Format,Object->GetType());
                           // ptr->text=ptr->text.SpanExcluding(_T("("));
                            Temp=CScreenKeypad::FormatNumber(ID[count],TempArray,(CScreenKeypad::FORMAT)ptr->Format,false,ptr->Insertunitflag);
                            ptr->IsDraw=Value[count];
                            SetDimension(ptr,count);
                            ptr->Variable_Text= " = " +Temp;
                            count++;
                        }
                        else if(Object->GetType() == CVgaMenu::VGA_Button_OBJECT)
                        {
                           
                           CheckConditions(Object);
                           Object->IsDraw=Value[count];
                           if(Object->IsDraw)
                           {
                              DisableFlag = true;
                              Object->RectShow=true;
                           }
                           else
                           {
                              DisableFlag = false;   
                              Object->RectShow=false;
                           }
                          // CheckConditions(Object);
                           
                           /*else
                              Object->IsDraw=true;*/
                           //if(Object->IsDraw)
                            //  Object->Draw(pDrawDC);
                           count++;
                        }
                        else
                        {
                           Object->IsDraw=true;
                        }
                        if(Object->GetType()==CVgaMenu::BottomMenu_Id)
                           Object->IsDraw=false;

						   }

                     delete []ID;
                     if(NoOFChoice>0)
                        delete[]Value;
                     Invalidate();
                  }
                  delete response;
                  }
				 
               break;
            }
            else if(type==1)
            {
               KillTimer(BottomHalfTimer);

               if(CBottomHalf::BottomMenuPointer!=0)
                  menu1=CBottomHalf::BottomMenuPointer;

               int length =2;
               int count =0,Temp1=0;
               unsigned char data1[2];
				   union 
		               {
			               short i;
			               char c[2];
		               } u;
		             u.i=CBottomHalf::BottomHalfId;
               data1[1]=u.c[0];
				   data1[0]=u.c[1];
			      unsigned char * data = (unsigned char *) &data1[0];
               CHostCommand * request = new CHostCommand(GetBottomMenuData_FunID, data, length);
				   CHostCommand * response = app->SendPollingHostCommand(request);
               if(response)
               {
                  char ch=CHostCommand::AckNak();
			         data = response->GetData();
			         length = response->GetDataLength();
                  if(ch==ACK)
			         {
                    // printf("\n Ack in 383");
                     int NoOFVariables=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     int *val=new int[NoOFVariables];
                     for(int i=0;i<NoOFVariables;i++)
                     {
                        val[i]= CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
                     }
                     int NoOfFreqType=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     int *FreqType=new int[NoOfFreqType];
                     for(int k=0;k<NoOfFreqType;k++)
                     {
                        FreqType[k]= CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     }

                     int NoOFEnable=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     int *Enable=new int[NoOFEnable];
                     for(int j=0;j<NoOFEnable;j++)
                     {
                        Enable[j]= CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                       // printf("\n Enable[%d]=%d",j,Enable[j]);
                     }
                     
			            pos = menu1->items.GetHeadPosition();
                     while(pos)
				         {
					         Object = menu1->items.GetNext(pos);
                        if(Object->GetType() == CVgaMenu::VARIABLE)
                        {
                            CVgaVariable *ptr=(CVgaVariable *)Object;
                            CString Temp;
                            char TempArray[LINESIZE+1]="                    ";
                            val[count] = CScreenKeypad::ConvertInternalExternal( val[count],(CScreenKeypad::FORMAT)ptr->Format);
                            if(FreqType[count]!=0)
                            {
                               if(FreqType[count]==1)
                                  ptr->text=Str_Parallel;
                               else
                                  ptr->text=Str_Series;
                               
                               CScreenKeypad::InsertProperUnits(ptr,(CScreenKeypad::FORMAT)ptr->Format,Object->GetType());
                               Temp=CScreenKeypad::FormatNumber(val[count],TempArray,(CScreenKeypad::FORMAT)ptr->Format,ptr->Unitshow,ptr->Insertunitflag);
                               ptr->Variable_Text= " = " +Temp;
                               SetDimension(ptr,count);
                               ptr->IsDraw=Enable[count];
                            }
                            else
                               ptr->text="";
                            count++;
                        }
                        else if(Object->GetType() == CVgaMenu::VGA_Button_OBJECT)
                        {
                           Object->IsDraw=Enable[count];
                           if(Temp1==0)// if(count==6)
                           {
                              if(!Object->IsDraw)
                              {
                                 Object->RectShow=false;
                                 CChildView::BotomHalfRefreshTime=3000;
                              }
                              else
                              {
                                 Object->RectShow=true;
                                 CChildView::BotomHalfRefreshTime=100;
                              }
                              CheckConditions(Object);
                              Temp1++;
                           }
                           CVgaButton *ptr=(CVgaButton *)Object;
                           if(ptr->argument=="1")
                           {
                              CString TempStr=ptr->GetText();
                              if(CChildView::TempCount==0)
                              {
                                 CChildView::ScanString=ptr->GetText();
                                 CChildView::TempCount++;
                              }
                              if(TempStr.Find(_T("..............."),0)!=(-1))
											   TempStr=CChildView::ScanString;//ptr->GetText();//TxtHSScanning[Language_Index];
										   ptr->SetText(TempStr +".");
                           }
                           else if((ptr->argument=="2" && (Object->IsDraw))||
                              (ptr->argument=="3" && (Object->IsDraw)))
                               DisableFlag = false;
                           count++;

                        }
                        else if(Object->GetType()==CVgaMenu::BottomMenu_Id)
                           Object->IsDraw=false;
                        
                     }
						   delete []Enable;
                     delete []val;
                     delete []FreqType;
                     Invalidate();
                  }
                  delete response;
               }
                  break;
            }
           
           break;
			}
         BottomHalfTimerOn=false;
			KillTimer(BottomHalfTimer);

		}
		break;
	case MessageScreenTimer:
		{	
         KillTimer(MessageScreenTimer);
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			
			DisableFlag = false;
			RedrawWindow(  NULL, NULL,  RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE ); 
		}
		break;

		case PasswordTimer:
		{	
         KillTimer(PasswordTimer);
			if(CScreenKeypad::IsPassword_Accepted==1)//password matched,go to desired menu
         {
              page_no=1;  
              ModifyObjectList(theApp.MenuPointer);
              theApp.GetSystemVariable();
			   
         }
			else if(CScreenKeypad::IsPassword_Accepted==2) //password mismatched,go to previous menu.
         {
            theApp.menuName=menusname.RemoveTail();
            page_no=menus.RemoveTail();
            theApp.MenuPointer=menupointers.RemoveTail();
            ModifyObjectList(theApp.MenuPointer);
		      
         }
			
			CScreenKeypad::AlphaBuf[0] = NULL;
			DisableFlag  = false;
			OnKeypadScreen_flag=false;
			RedrawWindow(  NULL, NULL,  RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE );
		}
		break;

		case ERROR_MESSAGE_TIMER:
		{
			KillTimer(ERROR_MESSAGE_TIMER);
			DisableFlag=false;
         Invalidate();
		}
		break;

      case USBMEMDETECTTIMER:
      if(USBPresent())
		{
          	if(((!USBWelddata.USBSampleDisable)         ||   (USBWelddata.USBOnAlarmValue)
						||(!USBPowerGraph.USBSampleDisable)    ||   (USBPowerGraph.USBOnAlarmValue)
						||(!USBColDistance.USBSampleDisable)   ||   (USBColDistance.USBOnAlarmValue)
						||(!USBVelocityGraph.USBSampleDisable) ||   (USBVelocityGraph.USBOnAlarmValue)
						||(!USBForceGraph.USBSampleDisable)    ||   (USBForceGraph.USBOnAlarmValue)
						||(!USBAmplitudeGraph.USBSampleDisable)||	(USBAmplitudeGraph.USBOnAlarmValue)
						||(!USBFrequencyGraph.USBSampleDisable)||	(USBFrequencyGraph.USBOnAlarmValue))&&(USBGlobalFlag))
		    CheckUSBSpaceAvailable();
      	else
				USBFullAlarm=false;
      }
      else
      {
        USBFullAlarm = false;
      }
      break;

      case USBSTATUSTIMER1:
		{
			if(USBPresent())
			{
            USBAlarm=false;
          //  USBFullAlarm = false;
          //  CheckUSBSpaceAvailable();
				if(!ISUSBPresent)
				{
					ISUSBPresent=true;
               MenuUSBDraw=true;
					USBWelddata.BaseCount  = UniversalCount+1-USBWelddata.USBSampleValue;
					USBPowerGraph.BaseCount= UniversalCount;
					USBColDistance.BaseCount=UniversalCount;
					USBVelocityGraph.BaseCount=UniversalCount;
					USBForceGraph.BaseCount=UniversalCount;
					USBAmplitudeGraph.BaseCount=UniversalCount;
					USBFrequencyGraph.BaseCount=UniversalCount;
               if(!OnKeypadScreen_flag)
               {
					   if(MenuUSBDraw)
                  {
                     ModifyObjectList(theApp.MenuPointer);
                  }
                  Invalidate();
               }
				}
         }
         else
         {
           // USBFullAlarm = false;
            if(ISUSBPresent)
				{ 
               ISUSBPresent=false;
               MenuUSBDraw=true;
               if(!OnKeypadScreen_flag)
               {
					   if(MenuUSBDraw)
                     ModifyObjectList(theApp.MenuPointer);
                  Invalidate();
               }
               SendPollingCommand(); 
            }
            if((!USBWelddata.USBSampleDisable)         ||   (USBWelddata.USBOnAlarmValue)
					||(!USBPowerGraph.USBSampleDisable)    ||   (USBPowerGraph.USBOnAlarmValue)
					||(!USBColDistance.USBSampleDisable)   ||   (USBColDistance.USBOnAlarmValue)
					||(!USBVelocityGraph.USBSampleDisable) ||   (USBVelocityGraph.USBOnAlarmValue)
					||(!USBForceGraph.USBSampleDisable)    ||   (USBForceGraph.USBOnAlarmValue)
					||(!USBAmplitudeGraph.USBSampleDisable)||	(USBAmplitudeGraph.USBOnAlarmValue)
					||(!USBFrequencyGraph.USBSampleDisable)||	(USBFrequencyGraph.USBOnAlarmValue))
				USBAlarm=true;
				else
					USBAlarm=false;
         }
			
      }
      break;
		case USBSTATUSTIMER:
		{
			if(USBPresent())
			{
				USBAlarm=false;
				if(!ISUSBPresent)
				{
					ISUSBPresent=true;
					USBWelddata.BaseCount  = UniversalCount+1-USBWelddata.USBSampleValue;
					USBPowerGraph.BaseCount= UniversalCount;
					USBColDistance.BaseCount=UniversalCount;
					USBVelocityGraph.BaseCount=UniversalCount;
					USBForceGraph.BaseCount=UniversalCount;
					USBAmplitudeGraph.BaseCount=UniversalCount;
					USBFrequencyGraph.BaseCount=UniversalCount;
					if(!OnKeypadScreen_flag)
					Invalidate();
				}
			}
			else
			{
				if(ISUSBPresent)
				{
					ISUSBPresent=false;
					if(!OnKeypadScreen_flag)
					Invalidate();
					/*This is done because sometimes the OS does't responds
					(for abt 5 sec's when USB is pulled out. So get new Global
					count before any other action */
//					SendPollingCommand();
				}

				
				
				if((!USBWelddata.USBSampleDisable)         ||   (USBWelddata.USBOnAlarmValue)
					||(!USBPowerGraph.USBSampleDisable)    ||   (USBPowerGraph.USBOnAlarmValue)
					||(!USBColDistance.USBSampleDisable)   ||   (USBColDistance.USBOnAlarmValue)
					||(!USBVelocityGraph.USBSampleDisable) ||   (USBVelocityGraph.USBOnAlarmValue)
					||(!USBForceGraph.USBSampleDisable)    ||   (USBForceGraph.USBOnAlarmValue)
					||(!USBAmplitudeGraph.USBSampleDisable)||	(USBAmplitudeGraph.USBOnAlarmValue)
					||(!USBFrequencyGraph.USBSampleDisable)||	(USBFrequencyGraph.USBOnAlarmValue))
				USBAlarm=true;
				else
					USBAlarm=false;
				
			}
		}
		break;
		
	}
}

/*********************************************************/
/*	This Function is to initialise different timers.     */
/*********************************************************/
int CChildView::InitialiseTimer(int TimerID,int Time)
{
	
	if(TimerID == AlphaEntryTimer)
	{
		IsTwoSecExpired=false;
		return thisPtr->SetTimer(AlphaEntryTimer,Time,NULL);
	}	
	else if(TimerID == Pollingtimer)
		return	thisPtr->SetTimer(Pollingtimer,Time,NULL);
	else if(TimerID == BottomHalfTimer)
		return	thisPtr->SetTimer(BottomHalfTimer,Time,NULL);
	else if(TimerID == MessageScreenTimer)
		return	thisPtr->SetTimer(MessageScreenTimer,Time,NULL);
	else if(TimerID == PasswordTimer)
		return	thisPtr->SetTimer(PasswordTimer,Time,NULL);
	else if(TimerID == ERROR_MESSAGE_TIMER)
      return thisPtr->SetTimer(ERROR_MESSAGE_TIMER,Time,NULL);
   else if(TimerID == USBSTATUSTIMER)
		return	thisPtr->SetTimer(USBSTATUSTIMER,Time,NULL);
	else if(TimerID == GETPRINTINGPARAMTIMER)
		return	thisPtr->SetTimer(GETPRINTINGPARAMTIMER,Time,NULL);
   else if(TimerID == LanguageSelectionTimer)
		return	thisPtr->SetTimer(LanguageSelectionTimer,Time,NULL);
   else if(TimerID == USBSTATUSTIMER1)
		return	thisPtr->SetTimer(USBSTATUSTIMER1,Time,NULL);
   else if(TimerID == USBMEMDETECTTIMER)
		return	thisPtr->SetTimer(USBMEMDETECTTIMER,Time,NULL);
   return 0;
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
	switch (nChar)
	{
		case VK_ESCAPE :
			theApp.ExitInstance();
         exit(1);
     /* case VK_SPACE :
			OnMainMenu();*/
		break;
	}
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	InitialiseTimer(Pollingtimer,PollingTime);
	return 0;
}

/************************************************/
/*	Function to kill Timer of particular ID		*/
/************************************************/
void CChildView::KillTimers(int TimerID)
{
	thisPtr->KillTimer(TimerID);
	
}

/****************************************************/
/*			Function to Calibrate Screen Points.	*/
/****************************************************/
CPoint CChildView::CalibratePoint(CPoint p)
{
	// return p;// to be removed
   if((RAMCalibCordinate_Xa==0 )&&(RAMCalibCordinate_Ya==0))
		return p;
	/* code added for screen setup starts here*/
	CPoint RetCordValue = p;	//CPoint point;
	{
		float FinalCord, TempVal;
		float DX1 = CVgaScreenSetup::DX1;
		float DY1 = CVgaScreenSetup::DY1
;
		/*Calculation for the x- Coordinate:*/
		TempVal = ((float) ActualCalibCordinate_Xa +	
                            DX1*(p.x - RAMCalibCordinate_Xa));
		if(TempVal < 0)
			FinalCord = 0;
		 else if(TempVal > MAX_VGA_X_VALUE)
			 FinalCord = MAX_VGA_X_VALUE;
		 else
			FinalCord = TempVal;  
		RetCordValue.x = (int) FinalCord;
	
		/*Calculation for the y- Coordinate:*/
		TempVal = ((float) ActualCalibCordinate_Ya +
                            DY1*(p.y - RAMCalibCordinate_Ya));
		if(TempVal < 0)
			 FinalCord = 0;
		else if(TempVal > MAX_VGA_Y_VALUE)
			 FinalCord = MAX_VGA_Y_VALUE;
		else 
			FinalCord = TempVal;     
		RetCordValue.y= (int)TempVal;
          //RetCordValue.y = MAX_VGA_Y_VALUE - RetCordValue.y;      
	}
	return RetCordValue;
		/* code for screen setup ends */
}

/****************************************************************/
/*	Function to Get color setup and Calibrate point at powerup.	*/
/****************************************************************/
void CChildView::GetRAMData()
{
	CFile f;    
	CFileException e;
	TCHAR* pFileName;
	#ifndef _WIN32_WCE
	pFileName = _T("c:\\SystemConfig.cfg");
	#else
	pFileName = _T("Disk\\SystemConfig.cfg");
	#endif
	
   if( !f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
	{
		
      #ifdef _DEBUG
		if(e.m_cause==CFileException::generic)
			TRACE("\n !! GENERIC");
		else if(e.m_cause==CFileException::badPath   )
			TRACE("\n !! bad path");
		else if(e.m_cause==CFileException::tooManyOpenFiles    )
			TRACE("\n !! too many files open");
		else if(e.m_cause==CFileException::fileNotFound )
			TRACE("\n !! file not found");
		else if(e.m_cause==CFileException::accessDenied       )
			TRACE("\n !! access denied");
		else if(e.m_cause==CFileException::diskFull      )
			TRACE("\n !! disc full");
		else if(e.m_cause==CFileException::invalidFile   )
			TRACE("\n !! invalid file");
		afxDump << "File could not be opened " << e.m_cause << "\n";
		#endif
   }
	else
	{
      char Comma =',';
      int Temprorylen=0;
      int FileSize = f.GetLength();
      int SysFileSize=FileSize;
      unsigned char *data=new unsigned char[FileSize];
      f.Read(data,FileSize);
      unsigned char * data1 = data;
		int SizeOfVariable =IntegerLength;
		if(FileSize >1)
		{
		 
		 Sys_FileSize=*data1++;FileSize--;
         char temp=' ';
         while((temp!=',')&&(FileSize>=1))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               CurrentExecutable[Temprorylen]=temp;
               Temprorylen++;
            }
            
         }
         CurrentExecutable[Temprorylen]='\0';
         unsigned short * FName;
		   FName = new unsigned short[Temprorylen];
	   
		   for(int u=0;u<Temprorylen;u++)
		   {
            FName[u] = CurrentExecutable[u];
		   }

		   SHCreateShortcut(_T("\\Windows\\Desktop\\SBC.lnk"),FName/*pFileName1*/);
		   delete []FName;
         
         temp=' ';Temprorylen=0;
         while((temp!=',')&&(FileSize>=1))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               CurrentLanguageName[Temprorylen]=temp;
               Temprorylen++;
            }
         }
         CurrentLanguageName[Temprorylen]='\0';
         
         temp=' ';Temprorylen=0;
         while((temp!=',')&&(FileSize>=1))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               SecurityFile[Temprorylen]=temp;
               Temprorylen++;
            }
           
         }
         SecurityFile[Temprorylen]='\0';
        // printf("\n SecurityFile=%d",Temprorylen);
         
         if(FileSize>=1)
            PasswordRequired=*data1++;FileSize--;
        // printf("\n PasswordRequired=%d",PasswordRequired);
         if(FileSize>=1)
            *data1++;FileSize--;

         temp=' ';Temprorylen=0;
        // printf("\n FileSize in before CurrentPassword=%d",FileSize);
         while((temp!=',')&&(FileSize>=1))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               CurrentPassword[Temprorylen]=temp;
               Temprorylen++;
            }
         }
         CurrentPassword[Temprorylen]='\0';

         char TempString[20];
         temp=' ';Temprorylen=0;
         while((temp!=',')&&(FileSize>=1))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
         }
         TempString[Temprorylen]='\0';
         TextColor=atoi(TempString);
         if((TextColor<1)||(TextColor>11))
         {
            TextColor=Black;
         }

         temp=' ';Temprorylen=0;
         while((temp!=',')&&(FileSize>=1))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
         }
         TempString[Temprorylen]='\0';
         Button_Color=atoi(TempString);
         if((Button_Color<1)||(Button_Color>11))
         {
            Button_Color=Gray;
         }
         
         temp=' ';Temprorylen=0;
         while((temp!=',')&&(FileSize>=1))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
         }
         TempString[Temprorylen]='\0';
         TitleBarColor=atoi(TempString);
         if((TitleBarColor<1)||(TitleBarColor>11))
         {
            TitleBarColor=Blue;
         }
         
         temp=' ';Temprorylen=0;
         while((temp!=',')&&(FileSize>=1))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
         }
         TempString[Temprorylen]='\0';
         Back_Color=atoi(TempString);
         if((Back_Color<1)||(Back_Color>11))
         {
            Back_Color=White;
         }
         
         temp=' ';Temprorylen=0;
         while((temp!=',')&&(FileSize>=1))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
         }
         TempString[Temprorylen]='\0';
         Highlight_Color=atoi(TempString);
         if((Highlight_Color<1)||(Highlight_Color>11))
         {
            Highlight_Color=Green;
         }
         
         temp=' ';Temprorylen=0;
         while((temp!=',')&&(FileSize>=1))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
         }
         TempString[Temprorylen]='\0';
         CVgaScreenSetup::DX1=atof(TempString);
         
         temp=' ';Temprorylen=0;
         while((temp!=',')&&(FileSize>=1))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
         }
         TempString[Temprorylen]='\0';
         CVgaScreenSetup::DY1=atof(TempString);

         temp=' ';Temprorylen=0;
         while((temp!=',')&&(FileSize>=1))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
         }
         TempString[Temprorylen]='\0';
         RAMCalibCordinate_Xa=atoi(TempString);

         temp=' ';Temprorylen=0;
         while((temp!=',')&&(FileSize>=1))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
         }
         TempString[Temprorylen]='\0';
         RAMCalibCordinate_Ya=atoi(TempString);

      }
     // delete []data1;
		f.Close();
      
   }
	
}

/**********************************************************************************/
/*Function to Store colorsetup and Screen Calibration information on Flash memory.*/
/**********************************************************************************/
void CChildView::SaveData()
{

   CFile f;
	CFileException e;
	TCHAR* pFileName;
	#ifndef _WIN32_WCE
	 pFileName = _T("c:\\SystemConfig.cfg");
	#else
	 pFileName = _T("Disk\\SystemConfig.cfg");
	#endif

	if( !f.Open( pFileName, CFile::modeReadWrite , &e ) )
	{
		#ifdef _DEBUG
		if(e.m_cause==CFileException::generic)
			TRACE("\n !! GENERIC");
		else if(e.m_cause==CFileException::badPath   )
			TRACE("\n !! bad path");
		else if(e.m_cause==CFileException::tooManyOpenFiles    )
			TRACE("\n !! too many files open");
		else if(e.m_cause==CFileException::fileNotFound )
			TRACE("\n !! file not found");
		else if(e.m_cause==CFileException::accessDenied       )
			TRACE("\n !! access denied");
		else if(e.m_cause==CFileException::diskFull      )
			TRACE("\n !! disc full");
		else if(e.m_cause==CFileException::invalidFile   )
			TRACE("\n !! invalid file");
		afxDump << "File could not be opened " << e.m_cause << "\n";
		#endif
	}
	else
	{
	   char Comma =',';
	   f.SeekToBegin();
      int length=0;
	   f.Write (&Sys_FileSize,sizeof(char));
      while(CurrentExecutable[length]!='\0')
      {
         length++;
      }
      //printf("\n CurrentExecutable=%d",length);
      f.Write(&CurrentExecutable,length);
      f.Write(&Comma,sizeof(char));
      
      length=0;
      while(CurrentLanguageName[length]!='\0')
      {
         length++;
      }
      //printf("\n CurrentLanguageName=%d",length);
      f.Write(&CurrentLanguageName,length);
      f.Write(&Comma,sizeof(char));
      
      length=0;
      while(SecurityFile[length]!='\0')
      {
         length++;
      }
     // printf("\n SecurityFile=%d",length);
      f.Write(&SecurityFile,length);
      f.Write(&Comma,sizeof(char));
      
      f.Write(&PasswordRequired,sizeof(bool));
      f.Write(&Comma,sizeof(char));

      length=0;
      while(CurrentPassword[length]!='\0')
      {
         length++;
      }
      //printf("\n CurrentPassword=%d",length);
      f.Write(&CurrentPassword,length);
      f.Write(&Comma,sizeof(char));
      
      char buffer[20];
      _itoa(TextColor, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      _itoa(Button_Color, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      _itoa(TitleBarColor, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      _itoa(Back_Color, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

       _itoa(Highlight_Color, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      sprintf(buffer,"%f",CVgaScreenSetup::DX1);
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      sprintf(buffer,"%f",CVgaScreenSetup::DY1);
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      _itoa(RAMCalibCordinate_Xa, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      _itoa(RAMCalibCordinate_Ya, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);
      f.Write(&Comma,sizeof(char));

      f.Close();
	}
}

/*****************************************************************************/
/*    Function To send Polling Command at every 200 miliseconds.			 */
/*****************************************************************************/
void CChildView::SendPollingCommand()
{	
	
	if(!HornScanPlzWait)
	{
	

		int PollingData =0;
      if(CChildView::ScreenSetupFlag)
         PollingData=2;
		PollingData+=PrinterPresent;
      if(USBFullAlarm)
         PollingData += USBFULLALARMPRESENT;
		int length = 1;//length of pointer to be send to 332.
		unsigned char * data = (unsigned char *) &PollingData;
		CCommPort::OnPollingTime=true;
		CHostCommand * request = new CHostCommand(GetPollingData_FunResponse, data,length);
		CHostCommand * response = app->SendPollingHostCommand(request);
		if (response)
		{		
			char ch=CHostCommand::AckNak();
			data = response->GetData();//Getting Data.
			length = response->GetDataLength();//Getting Length.
            //printf("\n length in polling...........=%d",length);
       	    
       
			if((ch==ACK)&&(length ==17))//If Ack.
				AnalyzePollingResponse(data,length);
			else
				InitialiseTimer(Pollingtimer,PollingTime);
			delete response;
		}
		else
		{
			InitialiseTimer(Pollingtimer,PollingTime);
		}

		int Alarms=0;
		
		if(USBAlarm)
		{
		if(((!USBWelddata.USBSampleDisable)         ||   (USBWelddata.USBOnAlarmValue)
						||(!USBPowerGraph.USBSampleDisable)    ||   (USBPowerGraph.USBOnAlarmValue)
						||(!USBColDistance.USBSampleDisable)   ||   (USBColDistance.USBOnAlarmValue)
						||(!USBVelocityGraph.USBSampleDisable) ||   (USBVelocityGraph.USBOnAlarmValue)
						||(!USBForceGraph.USBSampleDisable)    ||   (USBForceGraph.USBOnAlarmValue)
						||(!USBAmplitudeGraph.USBSampleDisable)||	(USBAmplitudeGraph.USBOnAlarmValue)
						||(!USBFrequencyGraph.USBSampleDisable)||	(USBFrequencyGraph.USBOnAlarmValue))&&(USBGlobalFlag))
				USBAlarm=true;
			else
				USBAlarm=false;
			if(USBAlarm)
				Alarms +=USBOFFLINEALARM;
			
		}
      if(USBFullAlarm)
      {
       //  USBFullAlarm = false;
         Alarms +=USBFULLALARM;
      }
		if(Alarms!=0)
			SendCommandAlarms(Alarms);
	}
	else
		InitialiseTimer(Pollingtimer,PollingTime);
		
}

/*****************************************************************************/
/*	Function To analyze polling response and to take necessary step          */
/*  according to the response.												 */
/*****************************************************************************/
void CChildView::AnalyzePollingResponse(unsigned char *&data, int &length)
{
	
	int TempWeldCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);

	int TempUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	PrinterStatuscheck = *data++;
	int TempPresetNum = *data++;
	int TempAlarmCount = CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
   TemporaryAlarmCount=TempAlarmCount;

   length -=3;
	StartWeldData =*data++;
   int TempResponseType=*data++;
	length--;

   bool ConditionVariableRequired=false;

   if((TempResponseType & 0x80))
      DisplayLockFlag=true;
   else
      DisplayLockFlag=false;

	if((TempResponseType & 0x40))
      ConditionVariableRequired=true;
   else
      ConditionVariableRequired=false;

  int ResponseType = TempResponseType & 0x3F;
//   int ResponseType = TempResponseType & 0x7F;


	int Pointer=(CVgaMenuItem::Convert_Char_To_Integer(data,length,1));
	TRACE(_T("\n pointer is %x \n"),Pointer);
	PresentAlarmCount=TempAlarmCount;
	PresentWeldCount=TempUniversalCount;
	PresentPresetNum=TempPresetNum;	

	if(powerup)
	{
		/*Store Values at power up.*/
		
		UniversalCount=TempUniversalCount;
		WeldCycleCount = TempWeldCount;
		PresetNum = TempPresetNum;
		AlarmCount =0;
		powerup=false;
		InitialiseTimer(USBSTATUSTIMER1,USBSTATUSTIME);
      InitialiseTimer(USBMEMDETECTTIMER,USBSMEMDETECTTIME);
		GetPrintingParameters(true);
		CheckPrinterStatus();
		GetPowerSupplyName();
		LastUSBPresetFolder="USBDisk\\"+PowerSupply+"\\Presets";
      PowerUpSBC=true;
	}
 	bool IsInvalidate =false;
   if(PowerUpSBC)
   {
      CWnd *pWndPrev,*pWndPrev1;
      if (pWndPrev1=CWnd::FindWindow(NULL,_T("VQS")))
         if(pWndPrev = CWnd::FindWindow(NULL,_T("SBC")))
         {
            //PowerUpSBC=false;
			   pWndPrev->SetForegroundWindow();
         }
   }
 	if(PrinterStatuscheck)
   {
		CheckPrinterStatus();
      PrinterStatuscheck=0;
   }
   if(ConditionVariableRequired)
   {
      ConditionVariableRequired=false;
      theApp.GetSystemVariable();
      GetPowerSupplyName();
   }

	
	switch(ResponseType)
   {
    case 0:
		{
			if(Pointer == 0)
				break;
			else
			{
            break;
			}
		}
		break;
		case -1:
			 if(Pointer == 0)
          {
				//PopMenu(false);
             theApp.menuName=menusname.RemoveTail();
             page_no=menus.RemoveTail();
             theApp.MenuPointer=menupointers.RemoveTail();
             ModifyObjectList(theApp.MenuPointer);   
		       Invalidate();
          }
		break;
      case 9:
         {
             CChildView::RunResultScreen=false;
             CBottomHalf::HornDownScreenPresent=true;
             ScreenSetupFlag=false;
			    OnKeypadScreen_flag=false;
			    DisableFlag=false;
             CVgaDrawGraph::GraphCount=0;
             while(theApp.GraphsDataList.GetCount()>0)
		         theApp.GraphsDataList.RemoveHead();
             CWnd *pWndPrev;
             CVgaMenu * menu;
             // Determine if a window with the class name exists...
			    if (pWndPrev = CWnd::FindWindow(NULL,_T("SBC")))
			  	      pWndPrev->SetForegroundWindow();
		       CString submenu=theApp.SpecialMenu[ResponseType];
             if (theApp.menus.Lookup(submenu, menu))
             {
			       page_no=1;
                ModifyObjectList(menu);   
			       theApp.menuName = submenu;
                theApp.MenuPointer=menu;
             }
             CString MenuName="";
            CVgaMenu * menu1=theApp.MenuPointer;
            POSITION pos = menu1->items.GetHeadPosition();
            CVgaMenuItem * Object;
	         while(pos)
	         {
		         Object = menu1->items.GetNext(pos);
               if(Object->GetType() == CVgaMenu::VGABottomHalfObject)
               {
                  CBottomHalf *obj=(CBottomHalf*)Object;
                  MenuName=obj->submenu;
                  CVgaMenu * menu;
                  if (theApp.menus.Lookup(MenuName, menu))
		            {
                     CBottomHalf::BottomMenuPointer=menu;
                  }
                  CChildView::thisPtr->MenuNameID=MenuName;
                  CBottomHalf::BottomHalfId=obj->EnumID;
                  CChildView::BotomHalfRefreshTime=obj->RefreshTime;
                  break;
               }
            }
			    Invalidate(); 
         }
         break;
      case 2:
      case 7:
         PollingTimeOnMsgScrn=true;
		case 1:
         {
          ScreenSetupFlag=false;
			 OnKeypadScreen_flag=false;
			 DisableFlag=true;
          CWnd *pWndPrev;
          CVgaMenu * menu;
          // Determine if a window with the class name exists...
			 if (pWndPrev = CWnd::FindWindow(NULL,_T("SBC")))
			  	   pWndPrev->SetForegroundWindow();
		    CString submenu=theApp.SpecialMenu[ResponseType];
          if (theApp.menus.Lookup(submenu, menu))
          {
			    page_no=1;
             ModifyObjectList(menu);   
			    theApp.menuName = submenu;
             theApp.MenuPointer=menu;
          } 
			 Invalidate();  
         }
		break;
      case 03://Show Message screen
         {
            CVgaMenu * menu;
			//printf("case 3 ");
            menu=theApp.MenuPointer;
            CVgaMenuItem * object=menu->items.GetHead();
            POSITION pos = menu->items.GetHeadPosition();
            while(pos)
            {
               object = menu->items.GetNext(pos);
			      if(object->GetType() == CVgaMenu::VGAMsgScrnObject)
               {
                  CMsgScreen *ptr=(CMsgScreen *)object;
                  if(ptr->submenu!="")
                  {
                    // printf("\n ptr->submenu................");
                     if (theApp.menus.Lookup(ptr->submenu, menu))
		               {
                        page_no=1;
                        theApp.menuName = ptr->submenu;
                        theApp.MenuPointer=menu;
                        ModifyObjectList(menu);   
			            }
                   }
                  
               }
               else
               {
                  DisableFlag=false;
               }
               Invalidate();
            }
         }
         break;
      case 04://Show Message screen nak screen
         {

            CVgaMenu * menu;
            menu=theApp.MenuPointer;
            CVgaMenuItem * object=menu->items.GetHead();
            POSITION pos = menu->items.GetHeadPosition();
            while(pos)
            {
               object = menu->items.GetNext(pos);
			      if(object->GetType() == CVgaMenu::VGAMsgScrnObject)
               {
                  CMsgScreen *ptr=(CMsgScreen *)object;
                  if(ptr->menunak!="")
                  {
                     if (theApp.menus.Lookup(ptr->menunak, menu))
		               {
                        page_no=1;
                        theApp.menuName = ptr->menunak;
                        theApp.MenuPointer=menu;
                        ModifyObjectList(menu);   
			            }
                   }
                  Invalidate();
               }
            }
         
         }
         break;
	    case 05:
		{
			CVgaMenu * menu;
         menu=theApp.MenuPointer;
         CVgaMenuItem * object=menu->items.GetHead();
			int ActTyp=0;
         POSITION pos = menu->items.GetHeadPosition();
         while(pos)
         {
            object = menu->items.GetNext(pos);
			   if((object->GetType() == CVgaMenu::VGA_Button_OBJECT))
            {
               if(Pointer==ActTyp)
               {
				     CVgaButton *ptr=(CVgaButton *)object;
				     if(ptr->MenuName!="")
				     {
					    //printf("\n ptr->MenuName................");
					    if (theApp.menus.Lookup(ptr->MenuName, menu))
						   {
						      page_no=1;
						      ModifyObjectList(menu);   
							   theApp.menuName = ptr->MenuName;
                        theApp.MenuPointer=menu;
						   }
					   }
			     }
			     ActTyp++;
            }
            else
            {
               DisableFlag=false;
            }
            Invalidate();
			}
		}
		break;
		case 06:
		{
			CVgaMenu * menu;
         menu=theApp.MenuPointer;
         CVgaMenuItem * object=menu->items.GetHead();
			int ActTyp=0;
         POSITION pos = menu->items.GetHeadPosition();
         while(pos)
         {
            object = menu->items.GetNext(pos);
			   if(object->GetType() == CVgaMenu::VGA_Button_OBJECT)
			   {
			     if(Pointer==ActTyp)
			     {
				     CVgaButton *ptr=(CVgaButton *)object;
				     if(ptr->MenuNak!="")
				     {
					    if (theApp.menus.Lookup(ptr->MenuNak, menu))
						   {
						   page_no=1;
						   ModifyObjectList(menu);   
							   theApp.menuName = ptr->MenuNak;
                        theApp.MenuPointer=menu;
						   }
					   }
			     }
			     ActTyp++;
              Invalidate();
            }
         }
		}
		break;
      case 8://Show Main Menu screen
         {
            CBottomHalf::HornDownScreenPresent=false;
            DisableFlag=false;
				CVgaDrawGraph::GraphCount=0;
            while(theApp.GraphsDataList.GetCount()>0)
		         theApp.GraphsDataList.RemoveHead();
            OnKeypadScreen_flag=false;
				PollingTimeOnMsgScrn=false;
            menusname.RemoveAll();
            menus.RemoveAll();
            menupointers.RemoveAll();
            theApp.GetSystemVariable();
		      CVgaMenu * menu;
            CVgaBottomMenu::SendCommandForBottomMenu(CVgaBottomMenu::mainMenuCommandID,(int)this);
            if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
		      {
			      AccessLevelSystem=OPERATOR;
               menusname.AddTail(theApp.menuName);
               menus.AddTail(page_no);
               menupointers.AddTail(theApp.MenuPointer);
               page_no=1;
               ModifyObjectList(menu);   
               theApp.menuName=CVgaBottomMenu::mainMenuID;
               theApp.MenuPointer=menu;   
		      }
			Reload_Start_Screen(); //Reload the Start_Screen configured
            Invalidate();
         }
         break;
         case 10:
         {
			   if(Pointer == 0)
            {
               ModifyObjectList(theApp.MenuPointer);
               Invalidate();
            }
         }
		   break;
         default:
            break;
       
	}
	
	/*Check for Current Screen i.e RunScreen or Graph Screen.*/
	bool GraphScreen = false;

	if(theApp.GraphsDataList.GetCount()>0)
		GraphScreen=true;
	

	if(TempPresetNum !=PresetNum)
	{
		if(!ExtPreset)
				GetPrintingParameters(true);
			else
				GetPrintingParameters(false);
	}

		if((GraphScreen && AutoRefreshon)&&(!CChildView::PMCScreen)&&(TempUniversalCount!=UniversalCount)) // In case of sequencing ,also check count change
		{
			int temp =0;
			POSITION pos = theApp.GraphsDataList.GetHeadPosition();
			bool GraphScrn=true;
			while(pos)
			{
				CVgaDrawGraph *obj =theApp.GraphsDataList.GetNext(pos);
				if(obj->GraphData.graph_type == NO_VALID_GRAPH)//CScreenObject::VGA_HORNSCANGRAPH)
            {
               GraphScrn=false;
               page_no=1;
               GraphOneRequestValue=2;
               while(theApp.GraphsDataList.GetCount()>0)
				      theApp.GraphsDataList.RemoveHead();
               ModifyObjectList(theApp.MenuPointer);
               Invalidate();
               break;
            }
				temp +=obj->GraphData.GraphRequestValue;

			}	
			if(GraphScrn)
			{
				GetGraphData(temp);
            Invalidate();
			}

		}
		if((GraphScreen && CChildView::PMCScreen)&&(TempUniversalCount!=UniversalCount)) // In case of sequencing ,also check count change
      {
         page_no=1;
         while(theApp.GraphsDataList.GetCount()>0)
				   theApp.GraphsDataList.RemoveHead();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
         Invalidate();
      }


	if((TempPresetNum !=PresetNum) &&RunResultScreen)
	{
		//Send host command to get the Weld State data.
		theApp.GetSystemVariable();
		int length = 0;//length of pointer to be send to 332.
		CCommPort::OnPollingTime=false;
		CVgaMenu * menu;
      menu=theApp.MenuPointer;
	   CHostCommand * request = new CHostCommand(GetWeldStateStrings_FunId, 0, 0);
		CHostCommand * response = app->SendPollingHostCommand(request);
		if (response)
		{
			char TempArray[10];
			char ch=CHostCommand::AckNak();
			unsigned char *data = response->GetData();//Getting Data.
			length = response->GetDataLength();//Getting Length.
			if(ch==ACK)//If Ack.
			{	
				if(length>0)
				{
					CDC *pDC=GetDC();
					CVgaMenuItem::DrawRect(pDC, White,CRect(0,50,620,90));
					ReleaseDC(pDC);
					CString String = CVgaMenuItem::GetString(data, length);
					int PresetNumber=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
					CString Temprory=_itoa(PresetNumber,TempArray,10);
					CString PresentPresetString =CVgaMenuItem::GetString(data, length);
					POSITION pos1=menu->items.GetHeadPosition();
					int Temp =0;
					while (pos1)
					{
						CVgaMenuItem *object= menu->items.GetNext(pos1);
						int type = object->GetType();
					
						
						if(TempPresetNum !=PresetNum)
						{
							if((type == CVgaMenu::VGA_Button_OBJECT)&&(Temp==0))//CScreenObject::VGATEXT)
							{
								PresetNum=	TempPresetNum;
								CVgaButton *ptr=(CVgaButton *)object;
								ptr->SubText="";
								ptr->SubText=Temprory;
								CDC *pDC=GetDC();
								object->Draw(pDC);
								Temp++;
								ReleaseDC(pDC);
								object= menu->items.GetNext(pos1);
								type = object->GetType();
							}
						
							if((type == CVgaMenu::VGA_Button_OBJECT)&&(Temp==1))//CScreenObject::VGA_WELDSTATE)
							{
								CVgaButton *ptr=(CVgaButton *)object;
								PresentPresetString.TrimLeft();
								PresentPresetString.TrimRight();
								ptr->SubText="";
								ptr->SubText=PresentPresetString;
								CDC *pDC=GetDC();
								object->Draw(pDC);
								Temp++;
								ReleaseDC(pDC);
								object= menu->items.GetNext(pos1);
								type = object->GetType();
							}
							if((type == CVgaMenu::VGA_Button_OBJECT))
							{
								while((object->ModeSet!=CChildView::WeldMode)&&((type == CVgaMenu::VGA_Button_OBJECT)))
								{
								//	printf("\n object->ModeSet!=CChildView::WeldMode");
									object= menu->items.GetNext(pos1);
									type = object->GetType();
								}
								if(type == CVgaMenu::VGA_Button_OBJECT)
								{
									CVgaButton *ptr=(CVgaButton *)object;
									ptr->SubText="";
									ptr->SubText=String;
									CDC *pDC=GetDC();
									object->Draw(pDC);
									Temp++;
									ReleaseDC(pDC);
								}
							}
						}
					}
				}
				
			}
			delete response;
		}
	}	
	if(TempUniversalCount!=UniversalCount)
	{
		//printf("\n TempUniversalCount!=UniversalCount");
		USBMutex.Lock();
		if(PrintOnAlarmAndSample())
			UniversalCount=TempUniversalCount;
		USBMutex.Unlock();
	}

	/**** Handling Alarms ****/
  /* if((TempAlarmCount > AlarmCount)&&(CBottomHalf::HornDownScreenPresent))
	{
		//printf("\n HornDownScreenPresent in analyzepolling");
      menusname.RemoveAll();
      menus.RemoveAll();
      menupointers.RemoveAll();
		CVgaMenu * menu;
      CVgaBottomMenu::SendCommandForBottomMenu(CVgaBottomMenu::mainMenuCommandID,(int)this);
      if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
		{
			OnKeypadScreen_flag=false;
         DisableFlag = false;
         CBottomHalf::HornDownScreenPresent=false;
         AccessLevelSystem=OPERATOR;
         menusname.AddTail(theApp.menuName);
         menus.AddTail(page_no);
         menupointers.AddTail(theApp.MenuPointer);
         page_no=1;
         ModifyObjectList(menu);   
         theApp.menuName=CVgaBottomMenu::mainMenuID;
         theApp.MenuPointer=menu;
		}
      Invalidate();
	}*/

	if(!CommandForAlarmButton && TempAlarmCount!=0)
	{
		GetAlarmButton();
      AlarmCount=TempAlarmCount;
	}
	else 
   {
      //AlarmCount=TempAlarmCount;
	//	HandleAlarmChangeInPolling(TempAlarmCount);
      WaitForEtherNetAlarmHandle.SetEvent();

   }
  
   /* Handling Weld data to be sent on Ethernet.*/
	
/*	if(StartWeldData==1)
	{
		StartWeldData=0;
		if(app->ether->clients.GetUpperBound()!= -1)
		{
		
         int length = 0;//length of pointer to be send to 332.
			CHostCommand * request = new CHostCommand(GetWeldData, 0,length);
			CHostCommand * response = app->SendEnHostCommand(request);
			if (response)
			{
				length=response->GetBufLength();
            unsigned char * buf =  response->GetBuffer();
            app->SendWeldData(buf,length);
				delete response;
			}
			
		}
		
	}*/
	
	/*Again Initialise the polling timer.*/
	
	InitialiseTimer(Pollingtimer,PollingTime);
}

/*****************************************************************************/
/*		Function to Reload Start_Screen for any Reset required.		  	     */
/*****************************************************************************/
void CChildView::Reload_Start_Screen(void)
{
	//Load Start_Screen after Reset - RChapa - 20Sep-2017
	bool GetFirstScreen=false;
	while(!GetFirstScreen)
	GetFirstScreen=app->GetBottomMenuAddress(&Start_Screen,&WeldResults_Address,
						&mainMenuAddress,&WeldSetup_Address,
						&GraphsMenu_Address,&Language_Index,&metric);		      
	theApp.ReadXML_ReloadStartScreen();
	//Load Start_Screen after Reset - RChapa - 20Sep-2017
}

/*****************************************************************************/
/*		Function to process the NAK response of any host command.			 */
/*****************************************************************************/
void CChildView::ProcessNak(unsigned char *&data, int &length,int Address,int FunID)
{
	int WeldProcessError =CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
   if(WeldProcessError == WELD_PROCESS_ERROR)
	{
		int ErrorCode=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
		switch(ErrorCode)
		{
		 case 01:
		 {
		    ErrorBeep();
          OnKeypadScreen_flag=false;
		 }
		 break;
		 case 02:
		{
			 ErrorBeep();
			 OnKeypadScreen_flag=false;
			 CVgaMenu *menu;
          if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
          {
			   AccessLevelSystem=OPERATOR;
            menusname.AddTail(theApp.menuName);
            menus.AddTail(page_no);
            menupointers.AddTail(theApp.MenuPointer);
            page_no=1;
            ModifyObjectList(menu);   
            theApp.menuName=CVgaBottomMenu::mainMenuID;
            theApp.MenuPointer=menu;   
          }
          Invalidate();

		 }
		 break;
       case 03:
       {
          ErrorBeep();
          OnKeypadScreen_flag=false;
          theApp.menuName=menusname.RemoveTail();
          page_no=menus.RemoveTail();
          theApp.MenuPointer=menupointers.RemoveTail();
          ModifyObjectList(theApp.MenuPointer);
          Invalidate();
      
       }
       break;
       case 04:
       {
          CVgaMenu * menu;
			//printf("case 3 ");
            menu=theApp.MenuPointer;
            CVgaMenuItem * object=menu->items.GetHead();
            POSITION pos = menu->items.GetHeadPosition();
            while(pos)
            {
               object = menu->items.GetNext(pos);
			      if(object->GetType() == CVgaMenu::VGAMsgScrnObject)
               {
                  CMsgScreen *ptr=(CMsgScreen *)object;
                  if(ptr->submenu!="")
                  {
                    // printf("\n ptr->submenu................");
                     if (theApp.menus.Lookup(ptr->submenu, menu))
		               {
                        page_no=1;
                        ModifyObjectList(menu);   
			               theApp.menuName = ptr->submenu;
                        theApp.MenuPointer=menu;
                        Invalidate();
		               }
                   }
                  break;
               }
          }
      }
      break;
		case 05:
		{
			OnKeypadScreen_flag=true;
		   unsigned char *s=0;
         menusname.AddTail(theApp.menuName);
         menus.AddTail(page_no);
         menupointers.AddTail(theApp.MenuPointer);
         BuildCompleteKeypadList(VGA_PASSWORD,s,0,PasswordCommand,(class CVgaMenuItem *)Address);
			Invalidate();
		}
		break;
		case 06:
		{
		//	printf("\n case 6");
         OnKeypadScreen_flag=true;
			unsigned char *s;
         BuildCompleteKeypadList(VGA_PASSWORD,s,0,PasswordCommand,0);
			Invalidate();		
		}
		break;
		case 07:
		{
//			printf("\n case 7");
         CScreenKeypad::TempPassword = CScreenKeypad::AlphaBuf;
			OnKeypadScreen_flag=true;
			unsigned char *s;
         BuildCompleteKeypadList(VGA_PASSWORD,s,0,PasswordCommand,(class CVgaMenuItem *)1);
			Invalidate();
		}
		break;
      case 11:
      {
        // printf("\n case 11");
         CString NakMenu;
         CVgaMenuItem *item=(CVgaMenuItem *)Address;
         switch(item->GetType())
		   {
			   case CVgaMenu::VGA_Button_OBJECT:
			   {
				   CVgaButton *ptr=(CVgaButton *)Address;
               NakMenu=ptr->MenuNak ;
            }
            break;
            case CVgaMenu::ALPHA:
            {
               CVgaAlphanumeric *ptr=(CVgaAlphanumeric *)Address;
               NakMenu=ptr->MenuNak ;
            }
            break;
         }
         page_no=1;
         CVgaMenu * menu;
         if (theApp.menus.Lookup(NakMenu, menu))
		   {
			   CChildView::thisPtr->menusname.AddTail(theApp.menuName);
            CChildView::thisPtr->menus.AddTail(page_no);
            CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
            CChildView::thisPtr->ModifyObjectList(menu);
            theApp.menuName = NakMenu;
            theApp.MenuPointer=menu;
		   }                              
							             
      }
         break;
      case 12:
      {
          CVgaMenu * menu;
			//printf("case 3 ");
            menu=theApp.MenuPointer;
            CVgaMenuItem * object=menu->items.GetHead();
            POSITION pos = menu->items.GetHeadPosition();
            while(pos)
            {
               object = menu->items.GetNext(pos);
			      if(object->GetType() == CVgaMenu::VGAMsgScrnObject)
               {
                  CMsgScreen *ptr=(CMsgScreen *)object;
                  if(ptr->submenu!="")
                  {
                    // printf("\n ptr->submenu................");
                     if (theApp.menus.Lookup(ptr->submenu, menu))
		               {
			               menusname.AddTail(theApp.menuName);
                        menus.AddTail(page_no);
                        menupointers.AddTail(theApp.MenuPointer);
                        page_no=1;
                        ModifyObjectList(menu);   
			               theApp.menuName = ptr->submenu;
                        theApp.MenuPointer=menu;
                        Invalidate();
		               }
                   }
                  break;
               }
          }
      }
      break;
     default:
		ErrorBeep();
		break;
		}
	}
   
}
/******************************************************************/
/*  This Function will handle Alarm change in polling command.    */
/******************************************************************/
bool CChildView::HandleAlarmChangeInPolling(int TempAlarmCount)
{
	CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *AlarmPtr=0;
   POSITION pos1 = menu->items.GetTailPosition();
   while(pos1)
	{
      CVgaMenuItem *Object = menu->items.GetPrev(pos1);
		if(Object->GetType()==/*CScreenObject*/CVgaMenu::VGA_ALARMBUTTON)
		{
		//	printf("\n Alarm Present");
         AlarmPresent=true;
			AlarmPtr=Object;
         break;
		}
		else
			AlarmPresent=false;
	}
	
	if((TempAlarmCount != AlarmCount)||((AlarmPresent==false)&&(AlarmCount!=0)))
	{		  
	   if((IsAlarmScreen ==true)&&(TempAlarmCount!=AlarmCount))//Already on Alarm Screen
		{														//and alarm count change
			//printf("\n IsAlarmScreen ==true");
         if(TempAlarmCount==0)//Alarm Count Changes to zero.
			{
				AlarmCount = TempAlarmCount;
				page_no=1;
			
            IsAlarmScreen=false;
            
            while(menus.GetCount()>=2)
            {
               if(theApp.menuName==AlarmMenuName)
               {
                   theApp.menuName=menusname.RemoveTail();
                   page_no=menus.RemoveTail();
                   theApp.MenuPointer=menupointers.RemoveTail();
                   break;
               }
               theApp.menuName=menusname.RemoveTail();
               page_no=menus.RemoveTail();
               theApp.MenuPointer=menupointers.RemoveTail();
            }
            if(theApp.menuName==CVgaBottomMenu::WeldResults_ID)
               CChildView::thisPtr->RunResultScreen=true;
            ModifyObjectList(theApp.MenuPointer); 
            Invalidate();
				return true;
			}
			else //Alarm Count Changes but not equal to zero.
			{
				AlarmCount = TempAlarmCount;
				page_no=1;
            if(theApp.menuName==CVgaBottomMenu::WeldResults_ID)
                  CChildView::thisPtr->RunResultScreen=true;
            ModifyObjectList(theApp.MenuPointer); 
            IsAlarmScreen =true;
            Invalidate();
				return true;
			}
		}
		/*Alarm count changes but  user is not on Alarm Screen.*/
		else if(IsAlarmScreen ==false)
		{
        // printf("\n IsAlarmScreen ==false");
			CDC*pDC=GetDC();
			if(AlarmPtr && TempAlarmCount==0)
			{	
            AlarmCount = TempAlarmCount;
            CTypedPtrList<CPtrList, CVgaMenuItem *> TempDataList;
				mutex.Lock();
             POSITION pos = menu->items.GetHeadPosition();
					while(pos)
					{
                  CVgaMenuItem *Object = menu->items.GetNext(pos);
                  if(Object->GetType() == CVgaMenu::VGA_ALARMBUTTON)
						{
						    menu->items.RemoveHead();
						}
						else
						{
							TempDataList.AddTail(Object);
							menu->items.RemoveHead();
						}
					}
					
					POSITION pos2 = TempDataList.GetHeadPosition();
					while(pos2)
					{
                  CVgaMenuItem *Obj = TempDataList.GetNext(pos2);
						menu->items.AddTail(Obj);
						
					}
					if(theApp.GraphsDataList.GetCount()==0)
                  CVgaMenuItem::DrawRect(pDC,CChildView::TitleBarColor, ALARMBUTTONRECT_RE);
					else
               {
                  ModifyObjectList(theApp.MenuPointer);
                  Invalidate();
               }
					while(TempDataList.GetCount())
						 TempDataList.RemoveHead();
					mutex.Unlock();
				
			}
			if(AlarmPtr && TempAlarmCount!=0)
			{	//printf("\n Set Text present");
            AlarmCount = TempAlarmCount;
            AlarmPtr->SetText(GetAlarmString(AlarmPtr));
            AlarmPtr->Draw(pDC);
         }
			else if(!AlarmPtr && TempAlarmCount!=0)
			{
			//	printf("\n !AlarmPtr && TempAlarmCount!=0");
            AlarmCount = TempAlarmCount;
				AddAlarmButtonInList();
            if(theApp.GraphsDataList.GetCount()>0)
            {
               ModifyObjectList(theApp.MenuPointer);
               Invalidate();
            }
         }
			else if(!AlarmPtr && TempAlarmCount==0)
         {
			//	printf("\n !AlarmPtr && TempAlarmCount==0");
            AlarmCount = TempAlarmCount;
         }
			ReleaseDC(pDC);
      }
	}
   return false;
}

CDC* CChildView::GetDc()
{
	return GetDC();
}

void CChildView::ReleaseDc(CDC *pDC)
{
	ReleaseDC(pDC);
}

/**********************************************************/
/*	This function draws the page number on the screen,	  */
/*	if menu has more then one page.						  */
/**********************************************************/
void CChildView::DrawPageNumber(CDC *pDC)
{
	if(Total_Text_Objects<MaxItemIn1ColMenu)
	{
		int Item_PerPage =MaxItems_PerPage;
		if((RowPerPage != 0)
			||(ColumnPerPage !=0))
			Item_PerPage=RowPerPage*ColumnPerPage;
		int Total_Pages=Total_Objects/Item_PerPage;
		int remender=Total_Objects%Item_PerPage;
		if(remender!=0)
		Total_Pages++;
	
		int Current_page_no=page_no;//menus.GetTail();///adding page no
		if(Total_Pages>1)
		{
			char Curr_buff[IntegerLength];
			sprintf(Curr_buff,"%dof%d",Current_page_no,Total_Pages);
			CString PageString=CChildView::thisPtr->StrPage;
			PageString+=Curr_buff;
			CVgaMenuItem::DrawText(pDC, Bigfont,White, Page_No_Rect, PageString,true);
		}
	}

}

/********************************************************************************************/
/* This function is used to collect all printing related data from 332. The function is		*/
/* used for following types of print list depending upon the argument passed				*/
/* 1. Weld Setup.																			*/
/* 2. Dups Preset.																			*/
/* 3. HornScan Graph and its text.															*/
/* 4. Screen Graph.																			*/
/* 5. For All six Graphs, when user presses Print Now button.								*/
/* 6. Weld History Data and its parameter ID array.											*/
/* 7. Weld Data and its ID Array.															*/
/*																							*/
/********************************************************************************************/
void CChildView::BuildPrintList(int type)
{
   CPrintDialog dlg(false);
	if(dlg.GetDefaults())
		PrinterPresent = PRINTERONLINE;
	else
	{
		ShowMessageScreen(PrinterPower_str_Offline);
		PrinterPresent = PRINTERNOTAVILABLE;
	}
	
	DeleteDC(dlg.m_pd.hdc);
	dlg.~CPrintDialog();
	if((!PrinterPresent)||(AbortPrinting))
		return;

   

	/* For Weld Setup */
	if(type == SETUPID)
	{	
      KillTimer(Pollingtimer);
      SetupTemp_pos = tempSetupList.GetHeadPosition();
	   tempSetupList.GetNext(SetupTemp_pos);
      tempSetupList.GetNext(SetupTemp_pos);
		int FUN_ID=GetWeldSetupPrint_FunID; 
		int length=ONE;
		for(int PAGE=SETUPSTARTPAGE;PAGE<SETUPENDPAGE;PAGE++)
		{	
			
			int length=ONE;
			{
				unsigned char* data = (unsigned char *) &PAGE;
				CCommPort::OnPollingTime=false;
				CHostCommand * request = new CHostCommand(FUN_ID, data, length);
				CHostCommand * response = app->SendPollingHostCommand(request);
				//CHostCommand * response = app->SendUiHostCommand(request);
				if(response)
				{	
					char ch=CHostCommand::AckNak();
					data = response->GetData();
					length = response->GetDataLength();
					if(ch==ACK)
					while (length>ZERO)
					{	
						int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
                  //printf("\n ID=%d",ID);
                  CPrintText * object = new CPrintText(data, length,false,ID);
						PrintObjectList.AddTail(object);
					}
					delete response;
				}
			
			}
			if(!(PAGE%2))
			{
				PrintInfoList.AddTail(SETUPID);
				WaitForPrintData.SetEvent();
			}
		}
		PrintVQSLimits();
		InitialiseTimer(Pollingtimer,PollingTime);
      return;
	}


	/* For Dups Setup Printout */
	if(type == DUPSPRESET)
	{
		int NoOfPages=ZERO;
		int FUN_ID=GetWeldSetupPrint_FunID; 
		int length=1;
		for(int PAGE=DUPSSTARTPAGE;PAGE<=DUPSENDPAGE;PAGE++)
		{
//			printf("\n PAGE=%d",PAGE);
         int length=ONE;
			unsigned char* data = (unsigned char *) &PAGE;
			CHostCommand * request = new CHostCommand(FUN_ID, data, length);
			CHostCommand * response = app->SendUiHostCommand(request);
			if(response)
			{		
//				printf("\n response");
            char ch=CHostCommand::AckNak();
				data = response->GetData();
				length = response->GetDataLength();
//            printf("\n length=%d",length);
				if(ch==ACK)
				{
				//	printf("\n Ack");
               NoOfPages++;
					while (length>ZERO)
					{	
						int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
                //  printf("\n ID=%d",ID);
                  CPrintText * object = new CPrintText(data, length,false,ID);
						PrintObjectList.AddTail(object);
					}
				
				}
				delete response;
			}
		}	
		if(NoOfPages)
		{
			PrintInfoList.AddTail(DUPSPRESET);
			WaitForPrintData.SetEvent();
		}
   //   printf("\n PrintObjectList=%d",PrintObjectList.GetCount());
      theApp.menuName=menusname.RemoveTail();
      page_no=menus.RemoveTail();
      theApp.MenuPointer=menupointers.RemoveTail();
      ModifyObjectList(theApp.MenuPointer);      
      Invalidate();
		return;
	}
   
   /* For sequence Setup Printout */
	if(type == PRINTSEQUENCE)
	{
      int NoOfPages=ZERO;
		int FUN_ID=GetWeldSetupPrint_FunID; 
		int length=ONE;
		int  PAGE = 10;
		unsigned char* data = (unsigned char *) &PAGE;
		CCommPort::OnPollingTime=false;
		CHostCommand * request = new CHostCommand(FUN_ID, data, length);
		CHostCommand * response = app->SendPollingHostCommand(request);
		//CHostCommand * response = app->SendUiHostCommand(request);
		if(response)
		{		
			char ch=CHostCommand::AckNak();
			data = response->GetData();
			length = response->GetDataLength();
			if(ch==ACK)
			{
				NoOfPages++;
				while (length>ZERO)
				{	
					int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
             //  printf(" ID= %d",ID);
               CPrintText * object = new CPrintText(data, length,false,ID);
					PrintSequenceObjectList.AddTail(object);
				}
			}
			delete response;
		}
		if(NoOfPages)
		{
			PrintInfoList.AddTail(PRINTSEQUENCE);
			WaitForPrintData.SetEvent();
		}
		return;
	}

   /* For All Six graphs When PrintNow is pressed */
	 switch(type)
	 {
		case POWERGRAPHID	:
		case COLDISTANCEID	:
		case VELOCITYGRAPHID:	
		case FORCEGRAPHID	:	
		case AMPLITUDEGRAPHID:	
		case FREQUENCYGRAPHID:
			{ //printf("Inside case type==any type of graph");
			int RequestType =NULL;
			switch(type)
			{
				case POWERGRAPHID	:
					RequestType = Power_RequestValue;
				break;
				case COLDISTANCEID	:
					RequestType = Distance_RequestValue;
				break;
				case VELOCITYGRAPHID:	
					RequestType =Velocity_RequestValue ;
				break;
				case FORCEGRAPHID	:	
					RequestType =Force_RequestValue ;
				break;
				case AMPLITUDEGRAPHID:	
					RequestType = Amplitude_RequestValue;
				break;
				case FREQUENCYGRAPHID:
					RequestType = Frequency_RequestValue;
				break;
			}
		
			int length =2;
			RequestType++;

			unsigned char data1[CORDLENGTH];
			data1[0]=(char)RequestType;
			data1[1]=(char)WELDDATA;

         unsigned char * data = (unsigned char *) &data1[0];
			
			CString SysPressureStr;
			bool ShowSysPressureStr=false;
		//	printf("ShowSysPressureStr = %d \n",ShowSysPressureStr);

			CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
			CHostCommand * response = app->SendUiHostCommand(request);
		
	//		printf("6 ");
	//		printf("request and response done \n");
			/**********************************/
	
			bool NoGraphData=true;
			bool NoWeldData=true;

	//		printf("NoGraphData = %d NoWeldData = %d \n",NoGraphData,NoWeldData);
		
		  if (response)
			{	
            char ch=CHostCommand::AckNak();
				data = response->GetData();//Getting Data.
				length = response->GetDataLength();//Getting Length.
				
				CWeldingData *PrintWeldDataObject;
				CVgaDrawGraph * PrintGraph;
				
				if(ch==ACK)
				while(length>0)
				{//	printf("\nlength = %d \n",length);
					//int Type= *data;
					//if(Type==CScreenObject::VGARUNSCREENOBJECT)
					{
						PrintWeldDataObject = new CWeldingData(ONE,data, length,true);
					//	printf("CWeldingData Constructor is called \n");
						NoWeldData=false;
						
					}
					int i=0;
					switch(type)
					{	
							case POWERGRAPHID :
								if(CChildView::PeakPowerMicrons)
								{
									GraphTitle = LString[9];								
								}
								else
								{
									GraphTitle = LString[0];
								}
								//GraphTitle = LString[0];
							break;
							case AMPLITUDEGRAPHID :
								if(CChildView::AmplitudeMicrons)
								{
									GraphTitle = LString[10];
								}
								else
								{
									GraphTitle = LString[1];
								}
								
							break;
							case FREQUENCYGRAPHID :
								GraphTitle = LString[2];
							break;
							case COLDISTANCEID :
								if(metric)
									GraphTitle = LString[3];
								else
									GraphTitle = LString[4];
							break;
							case VELOCITYGRAPHID :
								if(metric)
									GraphTitle= LString[5];
								else
									GraphTitle= LString[6];
								break;
							case FORCEGRAPHID :
								if(metric)
									GraphTitle= LString[7];
								else
									GraphTitle= LString[8];
								break;
						}
						while(length>0)
						{	//printf("length = %d",length);
							int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
							PrintGraph = new CVgaDrawGraph(ValueAfterParamID);
							 PrintGraph->GraphData.graph_type=ValueAfterParamID;
                     
							if(ValueAfterParamID>PMC_GRAPH)
							{	//printf("if(ValueAfterParamID>PMC_GRAPH) is Called \n");
								delete PrintGraph;
								NoGraphData=true;
							}
							else
							{ //printf("else of if(ValueAfterParamID>PMC_GRAPH) is Called \n");
								tempGraphsList.GetNext(GraphsTemp_pos);
								CVgaDrawGraph::GraphCount=0;
								SetGraphObjectMember(data,length,PrintGraph);
							
								CVgaDrawGraph::GraphCount--;
								SysPressureStr="";
								for(i=0;i<20;i++)
								{
									if(PrintGraph->GraphData.SystemPressure[i]=='\0')
										break;
									SysPressureStr+=PrintGraph->GraphData.SystemPressure[i];
									if(PrintGraph->GraphData.SystemPressure[i]!='\0')
										ShowSysPressureStr=true;
										//if(PrintGraph->SystemPressure[i]!=
								}
								NoGraphData=false;
							}							
						}
				}							
				
				if((NoGraphData==false)&&(NoWeldData==false))
				{//	printf(" inside if((NoGraphData==false)&&(NoWeldData==false)) \n");
					GraphWeldDataPrintList.AddTail(PrintWeldDataObject);
					GraphPrintList.AddTail(PrintGraph);
					PrintInfoList.AddTail(POWERGRAPHID);

					/*ADDING GRAPH TEXT STRINGS */
					int StartXCoordinate=PAGESTARTCORDINATE;
					int StartYCoordinate=GRAPHTEXTSTARTYCORDINATE;
					
					if(PrintGraph->GraphData.ManualStr)
					{//	printf("inside if(PrintGraph->ManualStr) \n");
						for(int y=0;y<5;y++)
						{//	printf("y = %d ",y);
							CPrintText * object = new CPrintText();
							object->CoOrdinate=CPoint(StartXCoordinate,StartYCoordinate);
							object->Text=Manual[y];
							object->Lang_Index=Language_Index;
							object->TextFont=NORMALFONT;
							StartYCoordinate+=ONELINEGAP;
                     PrintGraphTextObjectList.AddTail(object);
						}
                  	}
				
					StartYCoordinate-=20;
					
					for(int y=0;y<4;y++)		
					{//	printf("y = %d ",y);

						CPrintText * object = new CPrintText();
						object->CoOrdinate=CPoint(StartXCoordinate,StartYCoordinate);
						object->Text=GraphPrText[y];
						if(y==2)
						{
							if(!ShowSysPressureStr)
								object->Text +=GraphPrText[4];
							else
								object->Text +=SysPressureStr;
						}
						object->Lang_Index=Language_Index;
						object->TextFont=NORMALFONT;
						StartYCoordinate+=ONELINEGAP;//TWOLINEGAP;
						PrintGraphTextObjectList.AddTail(object);
					}


					CPrintText * object = new CPrintText();
					object->CoOrdinate=ZEROPOINT;
					PrintGraphTextObjectList.AddTail(object);
					WaitForPrintData.SetEvent();
				}
				else if(NoGraphData==false)
					delete PrintGraph;
				else if(NoWeldData==false)
					delete PrintWeldDataObject;

			delete response;
		}
		if(NoWeldData||NoGraphData)
		{ //printf("10 ");
			CString Str_NoValidGraph = tempGraphsList.GetNext(GraphsTemp_pos);
			ShowMessageScreen(Str_NoValidGraph);
      }		
    }
	  return;
   }

	/* For HornScan PrintOut */
	if(type==HORNSCANID)
	{
		int length =2;
		int RequestType=HornScan_RequestValue;
		unsigned char data1[CORDLENGTH];
		data1[ZERO]=(char)RequestType;
		data1[ONE]=(char)ZERO;
		unsigned char * data = (unsigned char *) &data1[ZERO];
		bool NoGraphData=true;
		CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
		CHostCommand * response = app->SendUiHostCommand(request);
		if(response)
		{	
			char ch=CHostCommand::AckNak();
			data = response->GetData();
			length = response->GetDataLength();
			if(ch==ACK)
			if(length>ZERO)
			{	
				//int Type= *data;
				//if(Type==CScreenObject::VGA_GRAPH_OBJECT)
				{	
				   CVgaDrawGraph * PrintGraph;
               int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
               PrintGraph =new CVgaDrawGraph(ValueAfterParamID);
               PrintGraph->GraphData.graph_type=ValueAfterParamID;
               if((PrintGraph->GraphData.graph_type!= NO_VALID_GRAPH))
					{
						SetHornScanObjectMember(data,length,PrintGraph);
			      PrintGraph->HSCompareGraph =false;
                  GraphPrintList.AddTail(PrintGraph);
						NoGraphData=false;
					}
              
				}
			}
			delete response;
			if(!NoGraphData)
			{	
				int StartXCoordinate=GRAPHTEXTSTARTXCORDINATE;//100;
				int StartYCoordinate=HORNSCANTEXTSTARTYCORDINATE;//1325;
				for(int i=0;i<PrintHSInfoText.GetSize();i++)
				{	
					CPrintText * object = new CPrintText();
               object->Text=PrintHSInfoText[i];
               object->TextFont=NORMALFONT;
					object->CoOrdinate=CPoint(StartXCoordinate,StartYCoordinate);
					PrintGraphTextObjectList.AddTail(object);
					StartYCoordinate+=HORNSCANTEXTSPACING;//50;
				}
				CPrintText * object = new CPrintText();
				object->CoOrdinate=ZEROPOINT;
				PrintGraphTextObjectList.AddTail(object);
            PrintInfoList.AddTail(HORNSCANID);
				WaitForPrintData.SetEvent();
			
			}
		}
		return;
      
      
	}
	/* For Screen Graphs*/
	if(type == SCREENGRAPHS)
	{	
		POSITION pos = theApp.GraphsDataList.GetHeadPosition();
		int TotalGraphRequestValue=ZERO;
		while(pos)
		{
			CVgaDrawGraph *obj = theApp.GraphsDataList.GetNext(pos);
			TotalGraphRequestValue ++;//=obj->GraphRequestValue;
			if((obj->GraphData.graph_type== NO_VALID_GRAPH/*CScreenObject::VGA_NOGRAPH*/)/*||(obj->graph_type==CScreenObject::VGA_NOHSGRAPH)*/)
				return;
		}	
		CString SysPressureStr;
		bool ShowSysPressureStr=false;
		if(TotalGraphRequestValue!=0)
		{
			SysPressureStr=CopyScreenGraphs();
			/* Now Send Request For The Graphs Needed And Print Them*/
			if(AutoRefreshon)
			{
				int length =CORDLENGTH;
				unsigned char data1[CORDLENGTH];
				data1[0]=(char)01;//(++TotalGraphRequestValue);
				data1[1]=(char)01;
				unsigned char * data = (unsigned char *) &data1[0];
				CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
				CHostCommand * response = app->SendUiHostCommand(request);
				if (response)
				{
					char ch=CHostCommand::AckNak();
					data = response->GetData();//Getting Data.
					length = response->GetDataLength();//Getting Length.
					
					if(ch==ACK)
					while(length>0)
					{
						//int Type= *data;
						//if(Type==CScreenObject::VGARUNSCREENOBJECT)
						{	
							CWeldingData *	obj = new CWeldingData(data, length,true);
							GraphWeldDataPrintList.AddTail(obj);
						}
					
					}
					delete response;
				}
			}
			else
			{
				
				int length=ViewGraphWeldData->GetDataLength();;
				unsigned char *data=ViewGraphWeldData->GetData();
				while(length>0)
				{
					//int Type= *data;
					//if(Type==CScreenObject::VGARUNSCREENOBJECT)
					{	
						CWeldingData *	obj = new CWeldingData(data, length,true);
						GraphWeldDataPrintList.AddTail(obj);
					}
				}
			}
		/*processing for graph ID array*/

			CVgaDrawGraph * TempObject= GraphPrintList.GetTail();
			int StartXCoordinate=PAGESTARTCORDINATE;
			int StartYCoordinate=GRAPHTEXTSTARTYCORDINATE;
			if(TempObject->GraphData.ManualStr)
			{
				for(int y=0;y<5;y++)
				{
					CPrintText * object = new CPrintText();
					object->CoOrdinate=CPoint(StartXCoordinate,StartYCoordinate);
					object->Text=Manual[y];
					object->Lang_Index=Language_Index;
					object->TextFont=NORMALFONT;
					StartYCoordinate+=ONELINEGAP;
               PrintGraphTextObjectList.AddTail(object);
				}
            
			}
         StartYCoordinate-=20;
			for(int y=0;y<4;y++)
			{
				CPrintText * object = new CPrintText();
				object->CoOrdinate=CPoint(StartXCoordinate,StartYCoordinate);
				object->Text=GraphPrText[y];
				if(y==2)
				{
					if(SysPressureStr.GetLength()==0)
						object->Text +=GraphPrText[4];
					else
						object->Text +=SysPressureStr;
				}
				object->Lang_Index=Language_Index;
				object->TextFont=NORMALFONT;
				StartYCoordinate+=ONELINEGAP;//TWOLINEGAP;
				PrintGraphTextObjectList.AddTail(object);
			}
			CPrintText * object = new CPrintText();
			object->CoOrdinate=ZEROPOINT;
			PrintGraphTextObjectList.AddTail(object);
		}
		if(!AutoRefreshon)
		{
			POSITION pos = theApp.GraphsDataList.GetHeadPosition();
			int NoOfGraphs=0;
			while (pos)
			{	
				CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
				if((obj->GraphData.GraphRequestValue==GraphOneRequestValue)||
					(obj->GraphData.GraphRequestValue==GraphTwoRequestValue))
				{
					NoOfGraphs++;
				}
				
			}
			if(NoOfGraphs==ONE)
			PrintInfoList.AddTail(GRAPHLISTSINGLEGRAPHID);
				else
			PrintInfoList.AddTail(GRAPHLISTDUALGRAPHID);
		}
		else
		{
			if(theApp.GraphsDataList.GetCount()==ONE)
				PrintInfoList.AddTail(GRAPHLISTSINGLEGRAPHID);
			else
				PrintInfoList.AddTail(GRAPHLISTDUALGRAPHID);
		}
		WaitForPrintData.SetEvent();
		return;
      
	}
	/* For WeldData On Sample And WEld Data PrintNow */
	if((type==WELDDATAONSAMPLEID)||(type==WELDDATAPRINTNOWID))
	{
		bool WeldData=false;
		int length =CORDLENGTH;
		bool PrintWeldData=false;
		unsigned char CommandData[CORDLENGTH];
		CommandData[ZERO]=(char)WELDDATA;
		CommandData[ONE]=(char)WELDDATA;
		unsigned char * data = (unsigned char *) &CommandData[ZERO];
		
		CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
		CHostCommand * response = app->SendUiHostCommand(request);
	
		if (response)
		{	char ch=CHostCommand::AckNak();
			data = response->GetData();
			length = response->GetDataLength();
		
			if(ch==0x06)
			{	
				{	
					CWeldingData * obj;
					 obj = new CWeldingData(data, length,true);
					 if(!obj->TotalCycles)
					 {
						 delete response;
						 delete obj;
						 return;
					 }
					 WeldData=true;
					if(type==WELDDATAONSAMPLEID)
					{	//printf("if type == WELDDATAONSAMPLEID");
						if(CChildView::thisPtr->WeldDataPrintList.GetCount())
						{
							CWeldingData * LastWeldObject=CChildView::thisPtr->WeldDataPrintList.GetTail();
							if(LastWeldObject->Units!=obj->Units)
							{	PrintWeldData=true;
								CChildView::thisPtr->ContinuePrinting=true;
							}
						}
						else 
							CChildView::thisPtr->ContinuePrinting=false;
							CChildView::thisPtr->WeldDataPrintList.AddTail(obj);
					}

					else if(type==WELDDATAPRINTNOWID)
					{	//printf("if type==WELDDATAPRINTNOWID \n");
						CChildView::thisPtr->PrintGraphWeldDataList2.AddTail(obj);
					//	printf("GetCount for PrintGraphWeldDataList2 =%d",PrintGraphWeldDataList2.GetCount());
					}
				}
			}
			delete response;
		}
	/*processing for weld data ID array*/

	if(WeldData)
		{
			CChildView::thisPtr->PrintInfoList.AddTail(type);
         if((type==WELDDATAONSAMPLEID)
					&&((WeldDataPrintList.GetCount()>=PrintSetup.WeldsPerPage)||(ContinuePrinting)))
				{	
					ContinuePrinting=true;
					WaitForPrintData.SetEvent();
				}
         else if((type==WELDDATAPRINTNOWID))
            WaitForPrintData.SetEvent();
		}
		return;

	}

	/* For WELDHISTORY Printing Data*/
   if((type==WELDHISTORYID) || ( type ==PRINT_HISTORY_DATA))
   { 
	  // printf("Inside if((type==WELDHISTORYID) || ( type ==PRINT_HISTORY_DATA)) \n");	
		   bool History =false;
        	if(HistoryTemp_pos!=NULL)
			{
			   HistoryTemp_pos=tempHistoryList.GetHeadPosition();
			   tempHistoryList.GetNext(HistoryTemp_pos);
			   tempHistoryList.GetNext(HistoryTemp_pos);
			}
			else
			{ 
            RunScreenTemp_pos= tempRunScreenList.GetHeadPosition();
			   tempRunScreenList.GetNext(RunScreenTemp_pos);
			   tempRunScreenList.GetNext(RunScreenTemp_pos);
			}

		for(int HistoryDataNo =1;HistoryDataNo<=2;HistoryDataNo++)
		{//	printf("HistoryDataNo = %d \n");
			
			int length =CORDLENGTH;
			bool PrintWeldData=false;
			unsigned char CommandData[CORDLENGTH];
			CommandData[ZERO]=(char)WELDDATA;

			 if( type ==PRINT_HISTORY_DATA)
				 {//printf("Insdie if( type ==PRINT_HISTORY_DATA) \n");
					   
                  CWeldingData::ValueFlag=true;					
					   if(HistoryDataNo ==1)
					   {//	printf("If 	if(HistoryDataNo ==1) \n");
						   if(CScreenKeypad::NoOfWeldresult<25)
							   CommandData[ONE]=CScreenKeypad::NoOfWeldresult;
						   else	
						       CommandData[ONE]=(char)FIRST25WELDDATA;
						}
					   else
					   {		
						  // printf("If 	if(HistoryDataNo !=1) \n");

					      if(CScreenKeypad::NoOfWeldresult<=25)
						      CommandData[ONE]=0X80;
					      else
						      CommandData[ONE]=(char)((CScreenKeypad::NoOfWeldresult-FIRST25WELDDATA) | 0X80 );
						
                  }	
				 }
				 else
				 {   
                if(HistoryDataNo ==1)
					     CommandData[ONE]=(char)FIRST25WELDDATA;							
					 else
					     CommandData[ONE]=(char)LAST25WELDDATA;
				 }

				unsigned char * data = (unsigned char *) &CommandData[ZERO];
				CCommPort::OnPollingTime=false;
				CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
				CHostCommand * response = app->SendPollingHostCommand(request);
			
				if(response)
				{ //printf("inside if(response) \n");
					char ch=CHostCommand::AckNak();
					data = response->GetData();
					length = response->GetDataLength();
					
					if(ch==ACK)
					{
					//	if(Type==CScreenObject::VGARUNSCREENOBJECT)
						{
							CWeldingData * obj;
							obj = new CWeldingData(data, length,false);
							
							if((obj->TotalCycles==0)&&(HistoryDataNo==1))
							{
								delete response;
								delete obj;
								return;
							}

							History=true;
							obj->HistoryObjectNum=HistoryDataNo;
							PrintWeldHistoryList2.AddTail(obj);
						//	printf("PrintWeldHistoryList2.GetCount = %d \n",PrintWeldHistoryList2.GetCount());

						}
					}
					else
					{
							delete response;
							History=false;
							if (PrintWeldHistoryList2.GetCount() && (HistoryDataNo ==2) )
								delete PrintWeldHistoryList2.RemoveTail();
							return;
					}
						
					delete response;
				}
				else
				{
               History=false;
					if (PrintWeldHistoryList2.GetCount() && (HistoryDataNo ==2) )
							delete PrintWeldHistoryList2.RemoveTail();
					return;
				}
		}

		if(History)
		{ //printf("Inside if(Histroy) \n");
         PrintInfoList.AddTail(type);
			WaitForPrintData.SetEvent();
		}
		return;
	}
}

BOOL CALLBACK _AfxAbortProc(HDC, bool x)
{
	if(x==1)
		return false;
	return TRUE;
}

/********************************************************************************************/
/* This function is called from the printing thread when any data is present to get printed */
/* The function calls various functions like OnPreparePrinting(), OnBeginPrinting() ,		*/
/* DoPreparePrintingand OnendPrinting(). This function also sets the start and end page for	*/
/* printing to one.																			*/
/********************************************************************************************/
void CChildView::print()
{
   // get default print info
	CPrintInfo printInfo;
	ASSERT(printInfo.m_pPD != NULL);     // must be set

	if(OnPreparePrinting(&printInfo))
	{

		// hDC must be set (did you remember to call DoPreparePrinting?)
		ASSERT(printInfo.m_pPD->m_pd.hDC != NULL);

		CDC dcPrint;
		if (WCE_IF(TRUE,!printInfo.m_bDocObject))
		{
			dcPrint.Attach(printInfo.m_pPD->m_pd.hdc);  
			dcPrint.m_bPrinting = TRUE;
		}
		
		OnBeginPrinting(&dcPrint, &printInfo);
			DOCINFO docInfo;

			memset(&docInfo, 0, sizeof(docInfo));
		docInfo.cbSize = sizeof(docInfo);

		// start document printing process
	if (WCE_IF(TRUE,!printInfo.m_bDocObject) && dcPrint.StartDoc(&docInfo) == SP_ERROR)
		{
			dcPrint.Detach();  
			return;
		}

		BOOL bError = FALSE;
		if (WCE_IF(FALSE, printInfo.m_bDocObject))
		{
			OnPrepareDC(&dcPrint, &printInfo);
			OnPrint(&dcPrint, &printInfo);
			
		}
		else
		{	CFrameWnd* pOldFrame=(CFrameWnd*)AfxGetThread()->m_pMainWnd;
			pOldFrame->ShowWindow(SW_SHOW ); 
			printInfo.SetMaxPage (2);
			UINT nStartPage=DEFAULTMINPAGE;
			UINT nEndPage=DEFAULTMAXPAGE;
		
			// begin page printing loop
			for (printInfo.m_nCurPage = nStartPage;
				printInfo.m_nCurPage !=nEndPage;
				printInfo.m_nCurPage += DEFAULTMINPAGE)//nStep)
			{
				OnPrepareDC(&dcPrint, &printInfo);
				{
				// check for end of print
				if (!printInfo.m_bContinuePrinting)
					break;
				if (dcPrint.StartPage() < ZERO)
					{
						bError = TRUE;
						break;
						
					}
				}
				ASSERT(printInfo.m_bContinuePrinting);
				pOldFrame->ShowWindow(SW_SHOW );
				
				OnPrint(&dcPrint, &printInfo);
				pOldFrame->ShowWindow(SW_SHOW );
				if (WCE_IF(TRUE,!printInfo.m_bDocObject) && 
					(dcPrint.EndPage() < ZERO || !_AfxAbortProc(dcPrint.m_hDC, 0)))
				{	
					bError = TRUE;
					break;
				}
			}
		}
		if (WCE_IF(TRUE,!printInfo.m_bDocObject))
		{
			if (!bError)
				dcPrint.EndDoc();
			else
				dcPrint.AbortDoc();
		}
		OnEndPrinting(&dcPrint, &printInfo);    
		dcPrint.Detach();   
	}
}


BOOL CChildView::OnPreparePrinting(CPrintInfo *printInfo)
{
	return DoPreparePrinting(printInfo);
}

BOOL CChildView::DoPreparePrinting(CPrintInfo *pInfo)
{
   ASSERT(pInfo != NULL);
	ASSERT(pInfo->m_pPD != NULL);

	pInfo->m_pPD->m_nFromPage = DEFAULTMINPAGE;
	pInfo->m_pPD->m_nToPage = DEFAULTMAXPAGE;

	if (!pInfo->m_pPD->GetDefaults())
		return FALSE;
	ASSERT(pInfo->m_pPD->m_pd.hDC != NULL);

	VERIFY(pInfo->m_strPageDesc.LoadString(AFX_IDS_PREVIEWPAGEDESC));
	return TRUE;
}

void CChildView::OnBeginPrinting(CDC *, CPrintInfo *)
{
}

void CChildView::OnEndPrinting(CDC *, CPrintInfo *)
{
}

void CChildView::OnPrepareDC(CDC *pDC, CPrintInfo *pInfo)
{
	ASSERT_VALID(pDC);
	UNUSED(pDC); 
	if(pInfo != NULL)
		pInfo->m_bContinuePrinting =
			(pInfo->GetMaxPage() != 0xffff || (pInfo->m_nCurPage == 1));
}

/************************************************************************************/
/* This function is called from Print() to print the data that is ready for printing*/
/* the function gets the object type(to be printed) from the printinfolist and then */
/* prints that object																*/
/************************************************************************************/
void CChildView::OnPrint(CDC *pDC, CPrintInfo * x)
{ 
	ASSERT_VALID(pDC);
	int PrintType = PrintInfoList.RemoveHead();
   
   if((PrintType==SETUPID)||(PrintType==DUPSPRESET))
	{ 
		//printf("\n PrintType=%d",PrintType);
     // printf("\n PrintObjectList=%d",PrintObjectList.GetCount());
       if(PrintObjectList.GetCount())
	   { 
			CPrintText *object = PrintObjectList.GetHead();
			int Old_Y_Cordinate = object->CoOrdinate.y;
			if(!AbortPrinting)
			{ 
				object->CoOrdinate.y-=THREELINEGAP;
           // printf("Calling Draw\n");
          //  ::Sleep(2000);
				object->Draw(pDC);
			}
			else
				return;
			delete PrintObjectList.RemoveHead();
				while(PrintObjectList.GetCount())
				{  
				//	printf("\n inside While");
			    CPrintText *object = PrintObjectList.GetHead();
					int New_Y_Cordinate = object->CoOrdinate.y;
             //  printf("New_Y_Cordinate = %d,AbortPrinting = %d",New_Y_Cordinate,AbortPrinting);
					if((New_Y_Cordinate !=PAGESTARTCORDINATE)&&(!AbortPrinting))
					{
				
					   object->CoOrdinate.y-=THREELINEGAP;
						object->Draw(pDC);
						Old_Y_Cordinate=New_Y_Cordinate;
						delete PrintObjectList.RemoveHead();
					}
					else
               {
                  break;
               }
				}
		}
      return;
	}
   
   if(PrintType==PRINTSEQUENCE)
	{ 
		//printf("\n PrintType=%d",PrintType);
     // printf("\n PrintObjectList=%d",PrintObjectList.GetCount());
       if(PrintSequenceObjectList.GetCount())
	   { 
			CPrintText *object = PrintSequenceObjectList.GetHead();
			int Old_Y_Cordinate = object->CoOrdinate.y;
			if(!AbortPrinting)
			{ 
				object->CoOrdinate.y-=THREELINEGAP;
           // printf("Calling Draw\n");
          //  ::Sleep(2000);
				object->Draw(pDC);
			}
			else
				return;
			delete PrintSequenceObjectList.RemoveHead();
				while(PrintSequenceObjectList.GetCount())
				{  
				//	printf("\n inside While");
			    CPrintText *object = PrintSequenceObjectList.GetHead();
					int New_Y_Cordinate = object->CoOrdinate.y;
					if((New_Y_Cordinate !=PAGESTARTCORDINATE)&&(!AbortPrinting))
					{
					   object->CoOrdinate.y-=THREELINEGAP;
						object->Draw(pDC);
						Old_Y_Cordinate=New_Y_Cordinate;
						delete PrintSequenceObjectList.RemoveHead();
					}
					else
               {
                  break;
               }
				}
		}
      return;
	}

	if((PrintType>=PRINTLISTGRAPHID)&&(PrintType<=FREQUENCYGRAPHID))
	{	//printf("Inside Graphs OnPrint \n");
		//printf("Inside 		if((PrintType>=PRINTLISTGRAPHID)&&(PrintType<=FREQUENCYGRAPHID)) \n");	
	
		int GraphType;
		bool ManualStr =false;
		bool ExtraGraphText =false;
		/*Printing Graph's Weld data if any*/
		if(GraphPrintList.GetCount())
		{
			CVgaDrawGraph *object1 = GraphPrintList.GetHead();
			if(object1->AlreadyPrinted)
			{//	printf("Inside if(object1->AlreadyPrinted) \n");
				int GraphYCord = PRINTWELDSTARTYCORD;
				while(GraphAlarmStringList.GetCount())
				{
					int XCord = PARAMETERSTARTXCORD;
					CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CRect(XCord-5,GraphYCord,XCord+XCORDINC-ABSGAP ,GraphYCord),GraphAlarmStringList.GetHead()  ,false,Language_Index);
					XCord +=PARAMWIDTH;
					GraphAlarmStringList.RemoveHead();
				    CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CRect(XCord,GraphYCord,XCord+XCORDINC ,GraphYCord),GraphAlarmStringList.GetHead()  ,false,Language_Index);
				   	GraphYCord+=ONEWELDLINEGAP;				
					GraphAlarmStringList.RemoveHead();
				}
				delete GraphPrintList.RemoveHead();
				delete GraphWeldDataPrintList.RemoveHead();
			}
			else
			{//	printf("Inside else block \n");
				if(GraphWeldDataPrintList.GetCount())
				{//	printf("Inside if(GraphWeldDataPrintList.GetCount()) \n");
				//	printf("GraphWeldDataPrintList.GetCount() = %d \n",GraphWeldDataPrintList.GetCount());
					CWeldingData *object = GraphWeldDataPrintList.GetHead();
				    GraphsTemp_pos = tempGraphsList.GetHeadPosition();
					tempGraphsList.GetNext(GraphsTemp_pos);
					tempGraphsList.GetNext(GraphsTemp_pos);
					if(!AbortPrinting)
						object->Print(pDC,this);
					else
               {
					    return;
               }
				}
				
				bool ExtraTextPrinted=false;
				if(GraphPrintList.GetCount())
				{
					CVgaDrawGraph *object = GraphPrintList.GetHead();
					GraphType=object->GraphData.graph_type;
					ManualStr=object->GraphData.ManualStr;
					ExtraGraphText=object->GraphData.ExtraText;
					
					/* printing manual text*/
					if(CVgaDrawGraph::PrintGraphManualStr(CPoint(0,PRINTNOWGRAPHCORD.y),pDC,GraphType,ExtraGraphText))
					{	
						CPoint TempPoint =PRINTNOWGRAPHCORD;
						TempPoint+=CPoint(0,THREEWELDLINEGAP);
						object->Print(pDC,TempPoint,PRINTLISTGRAPHID,this);
						ExtraTextPrinted=true;
					}
					else
						object->Print(pDC,PRINTNOWGRAPHCORD,PRINTLISTGRAPHID,this);				
					
				}
				
				if(PrintGraphTextObjectList.GetCount())
				{
				int AlarmCount=0;
					while(GraphAlarmStringList.GetCount())
						GraphAlarmStringList.RemoveHead();
					CWeldingData *object = GraphWeldDataPrintList.GetHead();
				   GraphsTemp_pos = tempGraphsList.GetTailPosition();
				   tempGraphsList.GetPrev(GraphsTemp_pos);
					if(ExtraTextPrinted)
						AlarmCount = object->PrintAlarms(0,pDC,1225,this,false,true," ");
					else
						AlarmCount = object->PrintAlarms(0,pDC,1175,this,false,true, " ");
					bool GraphOnNextPage=false;
					while(PrintGraphTextObjectList.GetCount())
					{
						
						CPrintText *object = PrintGraphTextObjectList.GetHead();
						if((object->CoOrdinate.y!=0)&&(!AbortPrinting))
						{
							if(ExtraTextPrinted)
								object->CoOrdinate.y+=(THREEWELDLINEGAP+AlarmCount*ONEWELDLINEGAP);
							else
								object->CoOrdinate.y+=(AlarmCount*ONEWELDLINEGAP);
							if(object->CoOrdinate.y<=MAXYCOORDINATE)
								object->Draw(pDC);
							else
							{
								GraphAlarmStringList.AddTail(" ");
								GraphAlarmStringList.AddTail(object->Text);
								GraphOnNextPage=true;
							}
							delete PrintGraphTextObjectList.RemoveHead();
						}
						else
						{
							delete PrintGraphTextObjectList.RemoveHead();
							break;
						}
					}
					if(GraphOnNextPage)
					PrintInfoList.AddHead(PrintType);
					else
					{
						delete GraphPrintList.RemoveHead();
						delete GraphWeldDataPrintList.RemoveHead();
					}
				}
			}				
		}
      return;
      
   }
   if((PrintType==GRAPHLISTSINGLEGRAPHID)||(PrintType==GRAPHLISTDUALGRAPHID))
		{ //printf("RHTDM\n");
      if(GraphPrintList.GetCount())
		{ 
			CVgaDrawGraph *object1 = GraphPrintList.GetHead();
		
			if(GraphAlarmStringList.GetCount())
			{	//	::Sleep(2000);
				int GraphYCord = PRINTWELDSTARTYCORD;
				while(GraphAlarmStringList.GetCount())
				{
					int XCord = PARAMETERSTARTXCORD;
					CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CRect(XCord-5,GraphYCord,XCord+XCORDINC-ABSGAP ,GraphYCord),GraphAlarmStringList.GetHead()  ,false,Language_Index);
					XCord +=PARAMWIDTH;
					GraphAlarmStringList.RemoveHead();
				    CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CRect(XCord,GraphYCord,XCord+XCORDINC ,GraphYCord),GraphAlarmStringList.GetHead()  ,false,Language_Index);
				   	GraphYCord+=ONEWELDLINEGAP;				
					GraphAlarmStringList.RemoveHead();
				}
			
			//	::Sleep(2000);
				delete GraphPrintList.RemoveHead();
				delete GraphWeldDataPrintList.RemoveHead();
			}
			else
			{   
            POSITION TempListPosition;
				int GraphType;
				bool ManualStr =false;
				bool ExtraGraphText =false;
				bool ExtraText =false;
				
				CVgaDrawGraph *object =GraphPrintList.GetHead();
			
				GraphType=object->GraphData.graph_type;
				ManualStr=object->GraphData.ManualStr;
				ExtraGraphText=object->GraphData.ExtraText;
				CPoint GraphCord=PRINTNOWGRAPHCORD;
				int LineInc=0;
				ScreenGraphsTemp_pos= tempScreenGraphsList.GetHeadPosition();
				tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);
				if(CVgaDrawGraph::PrintGraphManualStr(CPoint(0,PRINTNOWGRAPHCORD.y),pDC,GraphType,ExtraGraphText))
				{ 
				//::Sleep(2000);
					GraphCord.y+=THREEWELDLINEGAP;
					ExtraText=true;
					LineInc+=THREEWELDLINEGAP;
				}
			
			   if(PrintType==GRAPHLISTDUALGRAPHID)
				{			
					POSITION POS = GraphPrintList.GetHeadPosition();
					GraphPrintList.GetNext(POS);
					object= GraphPrintList.GetNext(POS);
					GraphType=object->GraphData.graph_type;
					ExtraGraphText=object->GraphData.ExtraText;
					
				   ScreenGraphsTemp_pos= tempScreenGraphsList.GetHeadPosition();
					tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);
				
					if(CVgaDrawGraph::PrintGraphManualStr(CPoint(0,PRINTNOWGRAPHCORD.y + ExtraText*THREEWELDLINEGAP),pDC,GraphType,ExtraGraphText))
					{  
						GraphCord.y+=THREEWELDLINEGAP;
						LineInc+=THREEWELDLINEGAP;
					}
				}	
			
                TempListPosition=ScreenGraphsTemp_pos;

				for(int NoOfGraphs =1;NoOfGraphs<=PrintType;NoOfGraphs++)
				{	 
					CVgaDrawGraph *object =GraphPrintList.GetHead();
					if(!AbortPrinting)
					{	
						if(PrintType==GRAPHLISTDUALGRAPHID)
							ScreenGraphsTemp_pos=TempListPosition;

						if(PrintType==GRAPHLISTSINGLEGRAPHID)
							object->Print(pDC,GraphCord,GRAPHLISTSINGLEGRAPHID,this);
						else
							object->Print(pDC,GraphCord,GRAPHLISTDUALGRAPHID,this);
						CVgaDrawGraph::PrintGraphBoundary =true;
						object->AlreadyPrinted=true;

						if((NoOfGraphs==1)&&(PrintType!=GRAPHLISTSINGLEGRAPHID))
						{ delete GraphPrintList.RemoveHead();
						}
					}
				}

				int AlarmCount=0;
				if(GraphWeldDataPrintList.GetCount())
				{
					CWeldingData *object = GraphWeldDataPrintList.GetHead();
					
					if(!AbortPrinting)
					{  
						object->Print(pDC,this);
						AlarmCount=object->PrintAlarms(0,pDC,LineInc+1175,this,false,true," ");
					}
					else
						return;
				}
			
				bool GraphOnNextPage=false;
				if(PrintGraphTextObjectList.GetCount())
				{
					LineInc+=(AlarmCount*ONEWELDLINEGAP+10);
					while(PrintGraphTextObjectList.GetCount())
					{
						CPrintText *object = PrintGraphTextObjectList.GetHead();
						if((object->CoOrdinate.y!=0)&&(!AbortPrinting))
						{
							object->CoOrdinate.y+=LineInc;
						if(object->CoOrdinate.y<=MAXYCOORDINATE)
								object->Draw(pDC);
							else
							{
								GraphAlarmStringList.AddTail(" ");
								GraphAlarmStringList.AddTail(object->Text);
								GraphOnNextPage=true;
							}

							delete PrintGraphTextObjectList.RemoveHead();
						}
						else
						{
							delete PrintGraphTextObjectList.RemoveHead();
							break;
						}
					}
				}

				if(GraphOnNextPage)
					PrintInfoList.AddHead(PrintType);
				else
				{
					delete GraphPrintList.RemoveHead();
					delete GraphWeldDataPrintList.RemoveHead();
				}
				CVgaDrawGraph::PrintGraphBoundary =false;
			
			}
		}
		return;
    }
	if(PrintType==WELDDATAPRINTNOWID)
	{
		if(PrintGraphWeldDataList2.GetCount())
		{	//printf("\n WELDDATAPRINTNOWID");
			CWeldingData *object = PrintGraphWeldDataList2.GetHead();
          WeldTemp_pos = tempWeldList.GetHeadPosition();
	      tempWeldList.GetNext(WeldTemp_pos);
			object->PrintWeldData(pDC,PRINTWELDSTARTYCORD,true,true,false,this);
			delete PrintGraphWeldDataList2.RemoveHead();
		}
      
	}
	if(PrintType==HORNSCANID)
	{
	   HornScanTemp_pos = tempHornScanList.GetHeadPosition();
	   tempHornScanList.GetNext(HornScanTemp_pos);
       CVgaDrawGraph *object = GraphPrintList.GetHead();//(CDrawGraph *)obj;
		if(!AbortPrinting)
		{	
			
			object->Print(pDC,PRINTHSGRAPHCORD,GRAPHLISTSINGLEGRAPHID,this);
			delete GraphPrintList.RemoveHead();
			
		}
		return;
   
	}

	if((PrintType==WELDHISTORYID) || ( PrintType ==PRINT_HISTORY_DATA))
		{			
			if((PrintWeldHistoryList2.GetCount())&&(!AbortPrinting))
			{ 	
				CWeldingData *object = PrintWeldHistoryList2.GetHead();

			int HistoryYCord = PRINTWELDSTARTYCORD+FOURWELDLINEGAP;
						
			while(WeldHistoryAlarmStringList.GetCount())
			{	
				if((object->TotalCyclesPrinted==0)&&(object->HistoryObjectNum==1))
					WeldHistoryAlarmStringList.RemoveHead();
				else
				{
					int XCord=PRINTWELDSTARTXCORD;
					CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-5,HistoryYCord,XCord+XCORDINC-ABSGAP ,HistoryYCord),WeldHistoryAlarmStringList.GetHead()  ,true,Language_Index);
					XCord +=(PARAMWIDTH+40);
					WeldHistoryAlarmStringList.RemoveHead();
					CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-ABSGAP,HistoryYCord,XCord-ABSGAP ,HistoryYCord),WeldHistoryAlarmStringList.GetHead()  ,false,Language_Index);
				
					HistoryYCord+=ONEWELDLINEGAP;
					WeldHistoryAlarmStringList.RemoveHead();
				}
				
			}

			//printf(" HistoryContinued = %d \n",object->HistoryContinued);

				if(!object->HistoryContinued)
				{	//printf("Inside if(!object->HistoryContinued)");
					
					if(HistoryTemp_pos!=NULL)
					{
					HistoryTemp_pos=tempHistoryList.GetHeadPosition();
					tempHistoryList.GetNext(HistoryTemp_pos);
					tempHistoryList.GetNext(HistoryTemp_pos);
					}
					else
					{ RunScreenTemp_pos= tempRunScreenList.GetHeadPosition();
					  tempRunScreenList.GetNext(RunScreenTemp_pos);
					  tempRunScreenList.GetNext(RunScreenTemp_pos);
					}

					object->PrintHistoryWeldData(pDC,HistoryYCord,true,true,1,this);
					int HistoryYCord=object->PrintHistoryYCord;
					CString LastMode ="  ";
					if(object->TotalCycles)
					LastMode = object->Mode_PresetString[object->TotalCyclesPrinted];
					
					if(object->TotalCycles==object->TotalCyclesPrinted)
					{
							delete PrintWeldHistoryList2.RemoveHead();
					}
					else
					{
						PrintInfoList.AddHead(WELDHISTORYID);
						return;
					}
				
					if(PrintWeldHistoryList2.GetCount())
						object = PrintWeldHistoryList2.GetHead();
					else
						return;
					
					//while(object->TotalCycles != object->TotalCyclesPrinted)
					{
					CString FirstMode ="  ";
					
					if(object->TotalCycles)
					 FirstMode= object->Mode_PresetString[object->TotalCycles];
					HistoryYCord-=ONEWELDLINEGAP;

					if(!AbortPrinting)
					{
							if(HistoryTemp_pos!=NULL)
							{
							HistoryTemp_pos=tempHistoryList.GetHeadPosition();
							tempHistoryList.GetNext(HistoryTemp_pos);
							tempHistoryList.GetNext(HistoryTemp_pos);
							}
							else
							{ RunScreenTemp_pos= tempRunScreenList.GetHeadPosition();
							  tempRunScreenList.GetNext(RunScreenTemp_pos);
							  tempRunScreenList.GetNext(RunScreenTemp_pos);
							}
					if(FirstMode.Compare(LastMode))
						object->PrintHistoryWeldData(pDC,HistoryYCord,false,true,2,this);
					else
						object->PrintHistoryWeldData(pDC,HistoryYCord,false,false,2,this);
					}
					if(object->TotalCycles == object->TotalCyclesPrinted){
						delete PrintWeldHistoryList2.RemoveHead();
					}
					else
						PrintInfoList.AddHead(WELDHISTORYID);
					
					}
				}
				else
				{//printf("Inside else block of if(!object->HistoryContinued)\n");
					if(!AbortPrinting)
					{
						if(HistoryTemp_pos!=NULL)
							{
							   HistoryTemp_pos=tempHistoryList.GetHeadPosition();
							   tempHistoryList.GetNext(HistoryTemp_pos);
							   tempHistoryList.GetNext(HistoryTemp_pos);
							}
							else
							{ 
                        RunScreenTemp_pos= tempRunScreenList.GetHeadPosition();
							   tempRunScreenList.GetNext(RunScreenTemp_pos);
							   tempRunScreenList.GetNext(RunScreenTemp_pos);
							}

						object->PrintHistoryWeldData(pDC,HistoryYCord,true,true,2,this);
						if(object->TotalCycles==object->TotalCyclesPrinted)
						{
							if(object->HistoryObjectNum==1)
							{
								int HistoryYCord=object->PrintHistoryYCord;
								CString LastMode ="  ";
								if(object->TotalCycles)
								LastMode = object->Mode_PresetString[object->TotalCyclesPrinted];
								delete PrintWeldHistoryList2.RemoveHead();
								object = PrintWeldHistoryList2.GetHead();
								if(object->HistoryObjectNum==2)
								{
									CString FirstMode ="  ";
									if(object->TotalCycles)
									 FirstMode= object->Mode_PresetString[object->TotalCycles];
									HistoryYCord-=ONEWELDLINEGAP;
									
									if(!AbortPrinting)
									{		if(HistoryTemp_pos!=NULL)
											{
											HistoryTemp_pos=tempHistoryList.GetHeadPosition();
											tempHistoryList.GetNext(HistoryTemp_pos);
											tempHistoryList.GetNext(HistoryTemp_pos);
											}
											else
											{ RunScreenTemp_pos= tempRunScreenList.GetHeadPosition();
											  tempRunScreenList.GetNext(RunScreenTemp_pos);
											  tempRunScreenList.GetNext(RunScreenTemp_pos);
											}
									if(FirstMode.Compare(LastMode))
										object->PrintHistoryWeldData(pDC,HistoryYCord,false,true,2,this);
									else
										object->PrintHistoryWeldData(pDC,HistoryYCord,false,false,2,this);
									}
									if(object->TotalCycles == object->TotalCyclesPrinted){
										delete PrintWeldHistoryList2.RemoveHead();
									}
									else
										PrintInfoList.AddHead(WELDHISTORYID);
								}
							}
							else
							{
								delete PrintWeldHistoryList2.RemoveHead();
							}
						}
						else
						{
							PrintInfoList.AddHead(WELDHISTORYID);
							return;
						}
					}
				}
			}
		 CWeldingData::ValueFlag=false;
			return;
		}
		
		if((PrintType==WELDDATAONSAMPLEID)&&(ContinuePrinting))
		{
			int NoOfPrintedData=PrintSetup.WeldsPerPage;
			int YCord = PRINTWELDSTARTYCORD;
			if(WeldAlarmStringList.GetCount())
				YCord = PRINTWELDSTARTYCORD+THREEWELDLINEGAP;
			while(WeldAlarmStringList.GetCount())
			{
				int XCord=PRINTWELDSTARTXCORD;
				CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-5,YCord,XCord+XCORDINC-ABSGAP ,YCord),WeldAlarmStringList.GetHead()  ,true,Language_Index);
				XCord +=(PARAMWIDTH+40);
				WeldAlarmStringList.RemoveHead();
				CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-ABSGAP,YCord,XCord-ABSGAP ,YCord),WeldAlarmStringList.GetHead()  ,false,Language_Index);
					
			   YCord+=ONEWELDLINEGAP;
			   WeldAlarmStringList.RemoveHead();
			}
			if(WeldDataPrintList.GetCount())
			{	
				CWeldingData *object = WeldDataPrintList.GetHead();
            WeldTemp_pos = tempWeldList.GetHeadPosition();
            tempWeldList.GetNext(WeldTemp_pos);
				int AlarmCount = object->PrintWeldData(pDC,YCord,true,true,false,this);
				NoOfPrintedData--;
				if(YCord==PRINTWELDSTARTYCORD)
					YCord +=(FIVEWELDLINEGAP + AlarmCount*ONEWELDLINEGAP);
				else
					YCord += (TWOWELDLINEGAP + AlarmCount*ONEWELDLINEGAP);
				bool OldUnits =object->Units;
				CString LastMode = object->Mode_PresetString[0];
				CString FirstMode ="  ";
				delete WeldDataPrintList.RemoveHead();
				
				while((WeldDataPrintList.GetCount())&&(!AbortPrinting))
				{	
					if(!PrintInfoList.IsEmpty())
					{
						if(PrintInfoList.GetHead()!=WELDDATAONSAMPLEID)
							return;
					}
					else
						return;

					if(PrintInfoList.GetHead()==WELDDATAONSAMPLEID)
					{
						CWeldingData *object = WeldDataPrintList.GetHead();
						bool PrintUnits =false;
						bool PrintPresetNum =false;
						if((object->Units!=OldUnits)||(NoOfPrintedData==0))
						{
							ContinuePrinting=false;
							return;
						}
						OldUnits=object->Units;
						FirstMode= object->Mode_PresetString[0];
						if(FirstMode.Compare(LastMode))
							PrintPresetNum=true;
						
						LastMode = FirstMode;
						NoOfPrintedData--;
                  WeldTemp_pos = tempWeldList.GetHeadPosition();
                  tempWeldList.GetNext(WeldTemp_pos);
						AlarmCount = object->PrintWeldData(pDC,YCord,PrintUnits,PrintPresetNum,false,this);
						PrintInfoList.RemoveHead();
							delete WeldDataPrintList.RemoveHead();
						if((NoOfPrintedData==0)||(!WeldDataPrintList.GetCount()))
						{
							if(WeldAlarmStringList.GetCount())
							{
								int YCord = PRINTWELDSTARTYCORD+THREELINEGAP;
								while(WeldAlarmStringList.GetCount())
								{
								
									int XCord=PRINTWELDSTARTXCORD;
									CString TempStr= WeldAlarmStringList.RemoveHead();
									CPrintText *TempObj= new CPrintText();
									TempObj->Text=TempStr;
									TempObj->Lang_Index=Language_Index;
									TempObj->TextFont=PrintWeldDataFont;
									TempObj->CoOrdinate.x=XCord;
									TempObj->CoOrdinate.y=YCord;
									PrintObjectList.AddHead(TempObj);

									XCord +=(PARAMWIDTH+40);
									TempStr= WeldAlarmStringList.RemoveHead();
									TempObj= new CPrintText();
									TempObj->Text=TempStr;
									TempObj->Lang_Index=Language_Index;
									TempObj->TextFont=PrintWeldDataFont;
									TempObj->CoOrdinate.x=XCord;
									TempObj->CoOrdinate.y=YCord;
									PrintObjectList.AddHead(TempObj);
									YCord+=ONEWELDLINEGAP;
								}
							  PrintInfoList.AddHead(SETUPID);
							}
						}
						YCord+=AlarmCount*ONEWELDLINEGAP;
						if(PrintPresetNum)
							YCord+=(TWOWELDLINEGAP);
						if(!PrintUnits && !PrintPresetNum)
							YCord+=ONEWELDLINEGAP;
						if(YCord>=MAXYCOORDINATE)
							return;
					}
				}
				return;
            
			}
	
		}


		if((PrintType>=HSCGRAPHONE)&&(PrintType<=HSCGRAPHFOUR))
		{	
          ScanGraphsDataTemp_pos = tempScanGraphDataList.GetHeadPosition();
	      tempScanGraphDataList.GetNext(ScanGraphsDataTemp_pos);
			CTable *object =TablePrintList.GetHead();//(CVGATable *)obj;
			object->Print(pDC,CPoint(100,200));
			delete TablePrintList.RemoveHead();

			int Graphs=1;
			if(PrintType==HSCGRAPHTWO)
				Graphs=2;
			if(PrintType==HSCGRAPHTHREE)
				Graphs=3;
			if(PrintType==HSCGRAPHFOUR)
				Graphs=4;
		//	printf ("count = %d",HSGraphPrintList.GetCount());

			for(int NoOfGraphs =1;NoOfGraphs<=Graphs;NoOfGraphs++)
			{ //printf("NoOfGraphs = %d \n",NoOfGraphs);
            ScanGraphsDataTemp_pos = tempScanGraphDataList.GetHeadPosition();
	        tempScanGraphDataList.GetNext(ScanGraphsDataTemp_pos);
            tempScanGraphDataList.GetNext(ScanGraphsDataTemp_pos);
            tempScanGraphDataList.GetNext(ScanGraphsDataTemp_pos);
				CVgaDrawGraph *object = HSGraphPrintList.GetHead();//(CDrawGraph *)obj;
				if(!AbortPrinting)
				{	
					if(NoOfGraphs==GRAPHLISTDUALGRAPHID)
					{
						object->Print(pDC,PRINTHSCGRAPHCORD,GRAPHLISTDUALGRAPHID,this);
					}
					else
					{
						object->Print(pDC,PRINTHSCGRAPHCORD,GRAPHLISTSINGLEGRAPHID,this);
					}
					CVgaDrawGraph::PrintGraphBoundary =true;
						 HSGraphPrintList.RemoveHead();
				}
			}
			CVgaDrawGraph::PrintGraphBoundary =false;
			return;

		}
}


/************************************************************************************************/
/* This function is called when polling response is received. The function compares the			*/
/* base count of each of the six graphs, weld data base count, weld history base count and		*/
/* weld seup base count with the present weld cycle number. If any of these objects is to be	*/
/* printed then command is send to 332 to get its data.											*/
/*   If Ext Preset is Off and preset changes then all the objects which have print on sample	*/
/* enabled is printed.(If weld is done on changed preset)										*/
/*   If Ext Preset is On then Preset change have no effect on printing.							*/
/*																								*/
/************************************************************************************************/
bool CChildView::PrintOnAlarmAndSample()
{
	if(USBGlobalFlag)
		USBPresent();

	int diff=PresentWeldCount-UniversalCount;
	bool USBWeldData =false;
	bool WeldData=false;
	WeldOnChangedPreset=false;
	int TotalGraphRequestValue=0;
	int TotalPrintGraphRequest=0;
	bool HistoryRequired =false;
	bool SetupRequired =false;
	bool PrintSequenceRequired =false;

	if(diff>25)
	{	
		Welddata.BaseCount= PresentWeldCount-25;
		USBWelddata.BaseCount  =  PresentWeldCount-25;
		diff=25;
	}
	if(powerup)
	{ 	
		Setup.BaseCount     = UniversalCount;
		PrintSequence.BaseCount=UniversalCount;
		Welddata.BaseCount  = UniversalCount+1-Welddata.PrintSampleValue;
		WeldHistory.BaseCount=UniversalCount;
		PowerGraph.BaseCount= UniversalCount;
		ColDistance.BaseCount=UniversalCount;
		VelocityGraph.BaseCount=UniversalCount;
		ForceGraph.BaseCount=UniversalCount;
		AmplitudeGraph.BaseCount=UniversalCount;
		FrequencyGraph.BaseCount=UniversalCount;
	
		USBWelddata.BaseCount  = UniversalCount+1-USBWelddata.USBSampleValue;
		USBPowerGraph.BaseCount= UniversalCount;
		USBColDistance.BaseCount=UniversalCount;
		USBVelocityGraph.BaseCount=UniversalCount;
		USBForceGraph.BaseCount=UniversalCount;
		USBAmplitudeGraph.BaseCount=UniversalCount;
		USBFrequencyGraph.BaseCount=UniversalCount;

	}
	else if(!diff)
		return true;

	else 
	{ 
		if(((PresentPresetNum ==PresetNum)&&(!ExtPreset))//case for weld done on same preset
		   ||(ExtPreset)) /* Weld Done On Changed Preset*/
		{	
					
			if((PresentPresetNum!=PresetNum)&&(!ExtPreset))/* Weld Done On Changed Preset*/
			{
				WeldOnChangedPreset=true;
				TempPresetNum=PresentPresetNum;
						
				if(((!PrintSetup.IsPrinting)||(!PrinterPresent))&&((!ISUSBPresent)||(!USBGlobalFlag)))
					return true;
				
				if(DataForUSB(WELDDATAONSAMPLEID))
					USBWeldData=true;

				if((!WeldHistory.PrintSampleDisable)&&(CheckForPrinting()))
				{
				   HistoryRequired =true;
			   }
					

				if((!Setup.PrintSampleDisable)&&(CheckForPrinting()))
					SetupRequired =true;

				if((!PrintSequence.PrintSampleDisable)&&(CheckForPrinting()&&(CToggle::SequencingON)))
            {	
               PrintSequenceRequired =true;
            }
	
				if((!Welddata.PrintSampleDisable)&&(CheckForPrinting()))
            {
				   WeldData=true;
            }
				
			

				if(((!PowerGraph.PrintSampleDisable)&&(CheckForPrinting()))||(DataForUSB(POWERGRAPHID)))
				{
				
					TotalPrintGraphRequest++;
					TotalGraphRequestValue+=Power_RequestValue;
				}

				if(((!ColDistance.PrintSampleDisable)&&(CheckForPrinting()))||(DataForUSB(COLDISTANCEID)))
				{
				
					TotalGraphRequestValue+=Distance_RequestValue;
					TotalPrintGraphRequest++;
				}


				if(((!VelocityGraph.PrintSampleDisable)&&(CheckForPrinting()))||(DataForUSB(VELOCITYGRAPHID)))
				{
				
					TotalPrintGraphRequest++;
					TotalGraphRequestValue+=Velocity_RequestValue;
					
				}

				if(((!ForceGraph.PrintSampleDisable)&&(CheckForPrinting()))||(DataForUSB(FORCEGRAPHID)))
				{
				
					TotalPrintGraphRequest++;
					TotalGraphRequestValue+=Force_RequestValue;
				}

				if(((!AmplitudeGraph.PrintSampleDisable)&&(CheckForPrinting()))||(DataForUSB(AMPLITUDEGRAPHID)))
				{
			
					TotalGraphRequestValue+=Amplitude_RequestValue;
					TotalPrintGraphRequest++;
				}

				if(((!FrequencyGraph.PrintSampleDisable)&&(CheckForPrinting()))||(DataForUSB(FREQUENCYGRAPHID)))
				{
				
					TotalGraphRequestValue+=Frequency_RequestValue;
					TotalPrintGraphRequest++;
				}
				
			}

			else
			{	
				BaseWeldCount=TempBaseWeldCount;
				GlobalCycleCount=PresentWeldCount;
		
				if(((!PrintSetup.IsPrinting)||(!PrinterPresent))&&((!ISUSBPresent)||(!USBGlobalFlag))&&(!RunResultScreen))
					 return true;
					
				if(DataForUSB(WELDDATAONSAMPLEID))
				{ 
			
					USBWeldData=true;
				}
		
				if((PresentAlarmCount) && (Setup.PrintOnAlarmValue)&&(CheckForPrinting()))
					SetupRequired =true;
				else if((!Setup.PrintSampleDisable)&&(CheckForPrinting()))
					 if((((PresentWeldCount-Setup.BaseCount)%(Setup.PrintSampleValue))==1)
					 ||((PresentWeldCount-Setup.BaseCount)==1)||(Setup.PrintSampleValue==1))
						SetupRequired =true;

				if((PresentAlarmCount ) && (PrintSequence.PrintOnAlarmValue)&&(CheckForPrinting())&&(CToggle::SequencingON))
            {
			
               PrintSequenceRequired =true;
            }
				else if((!PrintSequence.PrintSampleDisable)&&(CheckForPrinting())&&(CToggle::SequencingON))
					 if((((PresentWeldCount-PrintSequence.BaseCount)%(PrintSequence.PrintSampleValue))==1)
					 ||((PresentWeldCount-PrintSequence.BaseCount)==1)||(PrintSequence.PrintSampleValue==1))
                {
			
                   PrintSequenceRequired =true;
                }
						

				if((PresentAlarmCount) && (Welddata.PrintOnAlarmValue)&&(CheckForPrinting()))
            {
				
               WeldData=true;
            }
				else if((!Welddata.PrintSampleDisable)&&(CheckForPrinting()))
					if((PresentWeldCount-Welddata.BaseCount)>=Welddata.PrintSampleValue)
               {
				
                  WeldData=true;
               }
					

				if((PresentAlarmCount) && (WeldHistory.PrintOnAlarmValue)&&(CheckForPrinting()))
            {
				
					HistoryRequired =true;
            }
				else if((!WeldHistory.PrintSampleDisable)&&(CheckForPrinting()))
					if((((PresentWeldCount-WeldHistory.BaseCount)%(WeldHistory.PrintSampleValue))==1)
						||(WeldHistory.PrintSampleValue==1))
					{
						HistoryRequired =true;
					}


				
				SetRequestValue(&TotalGraphRequestValue,&TotalPrintGraphRequest,POWERGRAPHID,
																Power_RequestValue,&PowerGraph);

				SetRequestValue(&TotalGraphRequestValue,&TotalPrintGraphRequest,COLDISTANCEID,
																Distance_RequestValue,&ColDistance);

				SetRequestValue(&TotalGraphRequestValue,&TotalPrintGraphRequest,VELOCITYGRAPHID,
																Velocity_RequestValue,&VelocityGraph);

		
				SetRequestValue(&TotalGraphRequestValue,&TotalPrintGraphRequest,FORCEGRAPHID,
																Force_RequestValue,&ForceGraph);

		
				SetRequestValue(&TotalGraphRequestValue,&TotalPrintGraphRequest,AMPLITUDEGRAPHID,
																Amplitude_RequestValue,&AmplitudeGraph);

				SetRequestValue(&TotalGraphRequestValue,&TotalPrintGraphRequest,FREQUENCYGRAPHID,
																Frequency_RequestValue,&FrequencyGraph);
			}
		}
		else if(PresentPresetNum !=PresetNum)
		{	
				
		   TempBaseWeldCount=BaseWeldCount;
			BaseWeldCount=PresentWeldCount;
			TempPresetNum=PresetNum;
		
			
		}
		int GraphsForPrint=0;
		CString SysPressureStr;
		bool ShowSysPressureStr=false;
		if((RunResultScreen)&&(TotalGraphRequestValue==0))
		{
			++TotalGraphRequestValue;  
		}

		if((TotalGraphRequestValue!=0)||(WeldData==true)||(USBWeldData))
		{
				
			int NoOfPrintWeldData=0;
			/* Now Send Request For The Graphs Needed And Print Them*/
			int length =CORDLENGTH;
			unsigned char data1[CORDLENGTH];

			if(TotalGraphRequestValue!=1)
         {
            data1[0]=(char)(++TotalGraphRequestValue);
         }
			else
         {	
				data1[0]=(char)(TotalGraphRequestValue);
         }

			if(RunResultScreen)
				data1[1]=(char)diff; //on run screen & for both graphs and weld data
			else if((TotalGraphRequestValue==1)&&((WeldData)||(USBWeldData)))
			{ 
				data1[1]=(char)diff;//when no graphs & only weld data
         }
			else if((TotalGraphRequestValue>1)&&((WeldData)||(USBWeldData)))
			{ 
				data1[1]=(char)diff; // for both graphs and weld data
         }
			else if((TotalGraphRequestValue>1)&&(!WeldData)&&(!USBWeldData))
         {
				data1[1]=(char)1;//when single weld data is required for graphs
         }
			else
			{
				return true;/*return if nothing is required*/
			}
		

				
			CVgaMenu * menu;
			menu=theApp.MenuPointer;
			bool RunScreenObject=false;
			POSITION pos = menu->items.GetHeadPosition();
			while(pos)
			{
				CVgaMenuItem *Object = menu->items.GetNext(pos);
				if(Object->GetType()==CVgaMenu::VGARUNSCREENOBJECT)
				{
					RunScreenObject=true;
					break;
				}
			}
			unsigned char * data = (unsigned char *) &data1[0];
			CCommPort::OnPollingTime=false;
			CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
			CHostCommand * response = app->SendPollingHostCommand(request);

			if (response)
			{	char ch=CHostCommand::AckNak();
				data = response->GetData();//Getting Data.
				length = response->GetDataLength();//Getting Length.
				bool GraphForUSB = false;
				if(ch==ACK)
				while(length>0)
				{
					int DataLength=length;
					unsigned char * DataPtr =data;
					unsigned char * RunDataPtr =data;
					int RunDataLength=length;
				//	if(RunScreenObject==true)//Type==CVgaMenu::VGARUNSCREENOBJECT)//CScreenObject::VGARUNSCREENOBJECT)
					{
						CWeldingData *TempPtr = new CWeldingData(data, length,true);
						if((TempPtr->ReceivedUniversalCount!=PresentWeldCount)&&(diff!=25))
						{
							PresentWeldCount=TempPtr->ReceivedUniversalCount;
							delete TempPtr;
							delete response;
							return false;
						}
						else
						{
                     delete TempPtr;	
						}

						if(RunResultScreen)
						{	
							CVgaMenu * menu;
							menu=theApp.MenuPointer;
							POSITION pos = menu->items.GetHeadPosition();
							while(pos)
							{
								CVgaMenuItem *Object = menu->items.GetNext(pos);
								if(Object->GetType()==CVgaMenu::VGARUNSCREENOBJECT)
								{
									CRunScreen *obj = (CRunScreen*)Object;
									obj->UpdateWeldData(RunDataPtr,RunDataLength,true);
                           if(!OnKeypadScreen_flag)
                           {
									   CDC*pDC=GetDC();
									   Object->Draw(pDC);
                              ReleaseDC(pDC);
                           }
									break;
								}
							}
							
						}
					}

					if(WeldData)
					{	
						int PrintLength=DataLength;
						unsigned char * PrintPtr =DataPtr ;
				
						if(((Welddata.BaseCount+Welddata.PrintSampleValue)<=PresentWeldCount)||Welddata.PrintOnAlarmValue)
						{
							NoOfPrintWeldData=MakePrintWeldData(PrintPtr, PrintLength,diff);
						}
				
					}

					int NoofUSBGraphs=0;
					if(TotalPrintGraphRequest)
					{

						{
                     while(length>0)
							{
								
                        unsigned char *ptr1=data;
								int len=length;
                        CVgaDrawGraph * PrintGraph;
                        
                        int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(ptr1,len,CORDLENGTH);
                        switch(ValueAfterParamID)
                        {	
                           case POWGRAPH :
							   	 if(CChildView::PeakPowerMicrons)
								 {
									GraphTitle = CChildView::thisPtr->LString[9];
								 }
								 else
								 {
									GraphTitle = CChildView::thisPtr->LString[0];
								 }
			                      //GraphTitle = CChildView::thisPtr->LString[0];
			                     break;
	                        case AMPLIGRAPH :
	                        	if (CChildView::AmplitudeMicrons)
	                        		GraphTitle = CChildView::thisPtr->LString[10];
	                        	else
	                        		GraphTitle = CChildView::thisPtr->LString[1];
			                      break;
	                        case FREQUGRAPH :
			                        GraphTitle = CChildView::thisPtr->LString[2];
			                     break;
	                        case DISTMMGRAPH :
		                        GraphTitle = CChildView::thisPtr->LString[3];
			                     break;
                           case DISTINGRAPH:
		                        GraphTitle = CChildView::thisPtr->LString[4];
		                        break;
	                        case VELMMGRAPH :
		                        GraphTitle= CChildView::thisPtr->LString[5];
                              break;
                           case VELINGRAPH:
		                        GraphTitle= CChildView::thisPtr->LString[6];
		                        break;
	                        case FORCENGRAPH :
		                       GraphTitle= CChildView::thisPtr->LString[7];
		                       break;
                           case FORCELBGRAPH:
		                        GraphTitle= CChildView::thisPtr->LString[8];
		                      break;
                        }
                        
                        CVgaDrawGraph * USBGraph = new CVgaDrawGraph(ValueAfterParamID);
                        USBGraph->GraphData.graph_type=ValueAfterParamID;

                        SetGraphObjectMember(ptr1,len,USBGraph);
                        USBGraph->GraphCount--;
								
								if(USBGraph->GraphForUSB(this))
								{
                           GraphForUSB = true;
                           SysPressureStr="";
									for(int i=0;i<20;i++)
									{
										if(USBGraph->GraphData.SystemPressure[i]=='\0')
											break;
										SysPressureStr+=USBGraph->GraphData.SystemPressure[i];
										if(USBGraph->GraphData.SystemPressure[i]!='\0')
											ShowSysPressureStr=true;
										
									}

									USBGraphsList.AddTail(USBGraph);
                           NoofUSBGraphs++;
								}	
								else
									delete USBGraph;
                        
							
                        ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                        switch(ValueAfterParamID)
                        {	
                           case POWGRAPH :
							   	 if(CChildView::PeakPowerMicrons)
								 {
									GraphTitle = CChildView::thisPtr->LString[9];
								 }
								 else
								 {
									GraphTitle = CChildView::thisPtr->LString[0];
								 }
			                      //GraphTitle = CChildView::thisPtr->LString[0];
			                     break;
	                        case AMPLIGRAPH :
			                      GraphTitle = CChildView::thisPtr->LString[1];
			                     break;
	                        case FREQUGRAPH :
			                        GraphTitle = CChildView::thisPtr->LString[2];
			                     break;
	                        case DISTMMGRAPH :
		                        GraphTitle = CChildView::thisPtr->LString[3];
			                     break;
                           case DISTINGRAPH:
		                        GraphTitle = CChildView::thisPtr->LString[4];
		                        break;
	                        case VELMMGRAPH :
		                        GraphTitle= CChildView::thisPtr->LString[5];
                              break;
                           case VELINGRAPH:
		                        GraphTitle= CChildView::thisPtr->LString[6];
		                        break;
	                        case FORCENGRAPH :
		                       GraphTitle= CChildView::thisPtr->LString[7];
		                       break;
                           case FORCELBGRAPH:
		                        GraphTitle= CChildView::thisPtr->LString[8];
		                      break;
                        }

                        
                        PrintGraph = new CVgaDrawGraph(ValueAfterParamID);
							   PrintGraph->GraphData.graph_type=ValueAfterParamID;
                  
								SetGraphObjectMember(data,length,PrintGraph);
                        PrintGraph->GraphCount--;
								if(PrintGraph->GraphForPrinting(this))
								{
                           SysPressureStr="";
									for(int i=0;i<20;i++)
									{
										if(PrintGraph->GraphData.SystemPressure[i]=='\0')
											break;
										SysPressureStr+=PrintGraph->GraphData.SystemPressure[i];
										if(PrintGraph->GraphData.SystemPressure[i]!='\0')
											ShowSysPressureStr=true;
										
									}

									GraphPrintList.AddTail(PrintGraph);
									PrintInfoList.AddTail(POWERGRAPHID);
									GraphsForPrint++;
								}	
								else
									delete PrintGraph;
                        

							}
						}
					}
					if((GraphForUSB)||(USBWeldData))
					{
                  int USBLength=DataLength;
						unsigned char * USBPtr =DataPtr ;
						CHistoryData* USBObject;
						bool LatestWelddataAdded =false;

						if(((PresentWeldCount-USBWelddata.BaseCount)>=USBWelddata.USBSampleValue)||USBWelddata.USBOnAlarmValue)
						{
							LatestWelddataAdded = MakeUSBWeldData(USBPtr, USBLength,diff);
						
						}
						if(!LatestWelddataAdded)
						{
                     USBObject = new CHistoryData(USBPtr, USBLength);   
                     USBHistoryList.AddTail(USBObject);
						}
						USBGraphCountList.AddTail(NoofUSBGraphs);
						WaitForUSBData.SetEvent();
					}

					for(int i=1;i<=GraphsForPrint;i++)
					{	
						int PrintLength=DataLength;
						unsigned char * PrintPtr =DataPtr ;
						CWeldingData *PrintWeldDataObject = new CWeldingData(ONE,PrintPtr, PrintLength,true);
						GraphWeldDataPrintList.AddTail(PrintWeldDataObject);
					}
				}
				delete response;
			}
			else
            return false;
			
			/*sending command for ID array*/
			if(WeldData)					
			{

			//	if((WeldDataPrintList.GetCount()>=PrintSetup.WeldsPerPage)||(ContinuePrinting))      HSan we  don't have to wait until fill the page to print the weld data...
				
			//	{	
					ContinuePrinting=true;
					WeldDataPrint(WELDDATAONSAMPLEID);
					WaitForPrintData.SetEvent();
			//	}
					
			}
			/*sending command for text objects and ID array for weld data */
			if(GraphsForPrint)
			{
            for(int i=1;i<=GraphsForPrint;i++)
				{

					CVgaDrawGraph * TempObj = GraphPrintList.GetTail();
					int StartXCoordinate=PAGESTARTCORDINATE;
					int StartYCoordinate=GRAPHTEXTSTARTYCORDINATE;
					if(TempObj->GraphData.ManualStr)
					{
						for(int y=0;y<5;y++)
						{
							CPrintText * object = new CPrintText();
							object->CoOrdinate=CPoint(StartXCoordinate,StartYCoordinate);
							object->Text=Manual[y];
							object->Lang_Index=Language_Index;
							object->TextFont=NORMALFONT;
							StartYCoordinate+=ONELINEGAP;
                     PrintGraphTextObjectList.AddTail(object);
						}
                  
					}
               StartYCoordinate-=20;
					for(int y=0;y<4;y++)		
					{
						CPrintText * object = new CPrintText();
						object->CoOrdinate=CPoint(StartXCoordinate,StartYCoordinate);
						object->Text=GraphPrText[y];
						if(y==2)
						{
							if(!ShowSysPressureStr)
								object->Text +=GraphPrText[4];
							else
								object->Text +=SysPressureStr;
						}
						object->Lang_Index=Language_Index;
						object->TextFont=NORMALFONT;
						StartYCoordinate+=TWOLINEGAP;
						PrintGraphTextObjectList.AddTail(object);
					}
					CPrintText * object = new CPrintText();
					object->CoOrdinate=ZEROPOINT;
					PrintGraphTextObjectList.AddTail(object);
				}
			}
		}
		if(GraphsForPrint)
      {
         GraphsWeldPrint(POWERGRAPHID);
         WaitForPrintData.SetEvent();
      }
	}

	if(HistoryRequired)
   {
      WeldHistoryPrint(WELDHISTORYID);
   }

	if(SetupRequired)
   {
	 	 SetUpPrint(SETUPID);
   }
	
	if(PrintSequenceRequired)
   {
      SequencingPrint(PRINTSEQUENCE);
   }
	
	return true;
}


void CChildView::WeldHistoryPrint(int ID)
{	
	HistoryTemp_pos=NULL;
	GraphsTemp_pos=NULL;
	WeldTemp_pos=NULL;
	HornScanTemp_pos=NULL;
	ScanGraphsDataTemp_pos=NULL;
	ScreenGraphsTemp_pos=NULL;
	SetupTemp_pos=NULL;
	DUPSTemp_pos=NULL;
	SequenceTemp_pos=NULL;

	HistoryTemp_pos = tempHistoryList.GetHeadPosition();
   tempHistoryList.GetNext(HistoryTemp_pos);
   tempHistoryList.GetNext(HistoryTemp_pos);

   CChildView::thisPtr->BuildPrintList(ID);
}


void CChildView::WeldDataPrint(int ID)
{	
	
   HistoryTemp_pos=NULL;
	GraphsTemp_pos=NULL;
	WeldTemp_pos=NULL;
	HornScanTemp_pos=NULL;
	ScanGraphsDataTemp_pos=NULL;
	ScreenGraphsTemp_pos=NULL;
	SetupTemp_pos=NULL;
	DUPSTemp_pos=NULL;
	SequenceTemp_pos=NULL;

   WeldTemp_pos = tempWeldList.GetHeadPosition();
   tempWeldList.GetNext(WeldTemp_pos);

}


void CChildView::GraphsWeldPrint(int ID)
{	
   HistoryTemp_pos=NULL;
	GraphsTemp_pos=NULL;
	WeldTemp_pos=NULL;
	HornScanTemp_pos=NULL;
	ScanGraphsDataTemp_pos=NULL;
	ScreenGraphsTemp_pos=NULL;
	SetupTemp_pos=NULL;
	DUPSTemp_pos=NULL;
	SequenceTemp_pos=NULL;

   GraphsTemp_pos = tempGraphsList.GetHeadPosition();
   tempGraphsList.GetNext(GraphsTemp_pos);
   tempGraphsList.GetNext(GraphsTemp_pos);
}

void CChildView::SetUpPrint(int ID)
{
   CVgaMenu *menu=theApp.MenuPointer;
   theApp.MenuPointer=SetupMenuPointer;
   BuildPrintList(SETUPID);
   theApp.MenuPointer=menu;
}

void CChildView::SequencingPrint(int ID)
{
   CVgaMenu *menu=theApp.MenuPointer;
   theApp.MenuPointer=SequenceMenuPointer;
   BuildPrintList(PRINTSEQUENCE);
   theApp.MenuPointer=menu;
}

/************************************************************************************************/
/* This Printing thread is responsible to send the data to printer buffer. The function waits	*/
/* for any data in the printing queue. If any data is present in the queue then this thread just*/
/* calls the function Print() which does all the printing.										*/
/* This thread also checks wether the printer is present or not.								*/
/* 1.If the printer is present and Print List have data to get printed then it calls Print().	*/
/* 2.If the printer is not present then this function deletes all the data from the list to		*/
/* free the buffer.																				*/
/*																								*/
/************************************************************************************************/
UINT CChildView::PrintingThread(LPVOID)
{	
	while(1)
	{	
		HANDLE handle;
		handle = thisPtr->WaitForPrintData;
		WaitForSingleObject(handle, INFINITE);
		while(((thisPtr->HSGraphPrintList.GetCount())||(thisPtr->GraphPrintList.GetCount())
				||(thisPtr->PrintObjectList.GetCount())||(thisPtr->PrintSequenceObjectList.GetCount())
            ||(thisPtr->PrintWeldHistoryList2.GetCount()||(thisPtr->GraphWeldDataPrintList.GetCount()))
				||(thisPtr->TablePrintList.GetCount())||(thisPtr->PrintGraphWeldDataList2.GetCount())
				||((thisPtr->WeldDataPrintList.GetCount())&&(thisPtr->ContinuePrinting) )
				||(thisPtr->GraphAlarmStringList.GetCount())))
		{
			if(PrinterPresent)
			{
				if( ((thisPtr->HSGraphPrintList.GetCount())||(thisPtr->GraphWeldDataPrintList.GetCount())
					||(thisPtr->PrintObjectList.GetCount())||(thisPtr->PrintSequenceObjectList.GetCount())
               ||(thisPtr->GraphPrintList.GetCount())
					||(thisPtr->PrintWeldHistoryList2.GetCount()) ||(thisPtr->PrintGraphWeldDataList2.GetCount()))
					||(thisPtr->TablePrintList.GetCount())
					&&((thisPtr->WeldDataPrintList.GetCount())))
				{
					if(thisPtr->PrintInfoList.GetHead()==WELDDATAONSAMPLEID)
						thisPtr->ContinuePrinting=true;
					thisPtr->print();
				
					if(thisPtr->ContinuePrinting==true)
						thisPtr->ContinuePrinting=false;

				}
				else
					thisPtr->print();
			}
			else if(!PrinterPresent)
			{
						
                  while (thisPtr->HSGraphPrintList.GetCount()>0)
							 thisPtr->HSGraphPrintList.RemoveHead();

						while(thisPtr->PrintObjectList.GetCount()>0)
							delete thisPtr->PrintObjectList.RemoveHead();
						
                  while(thisPtr->PrintSequenceObjectList.GetCount()>0)
							delete thisPtr->PrintSequenceObjectList.RemoveHead();

                  while(thisPtr->GraphPrintList.GetCount()>0)
							delete thisPtr->GraphPrintList.RemoveHead();

						while(thisPtr->PrintWeldHistoryList2.GetCount()>0)
						{ 
						//	printf("\nDeleting %d",thisPtr->PrintWeldHistoryList2.GetCount());
							delete thisPtr->PrintWeldHistoryList2.RemoveHead();
						}
											
						while(thisPtr->PrintGraphTextObjectList.GetCount()>0)
							delete thisPtr->PrintGraphTextObjectList.RemoveHead();

                  while(thisPtr->GraphWeldDataPrintList.GetCount()>0)
							delete thisPtr->GraphWeldDataPrintList.RemoveHead();

						while(thisPtr->TablePrintList.GetCount()>0)
							delete thisPtr->TablePrintList.RemoveHead();

                  while(thisPtr->WeldDataPrintList.GetCount()>0)
							delete thisPtr->WeldDataPrintList.RemoveHead();

						while(thisPtr->PrintGraphWeldDataList2.GetCount()>0)
							delete thisPtr->PrintGraphWeldDataList2.RemoveHead();

						thisPtr->PrintInfoList.RemoveAll();
			}
			//Sleep(20000);
		}
		thisPtr->WaitForPrintData.ResetEvent();
	}
	return 0;

}

/****************************************************************************************/
/* This funcion is used To get the Weld data parameters heading i.e. Parameter name		*/
/* and their units. This function is called												*/
/* 1. On Power Up.																		*/
/* 2. On change of Language.															*/
/* 3. On change of Units.																*/
/****************************************************************************************/

void CChildView::GetAllWeldDataHeading(CXmlElement * e)
{
	int format;
	int i=0;
	if(!powerup)
	{
		delete []Parameter_ID;
	}
	Parameter_Heading = new CString[TotalTextHeading];
    WeldDataPatamStringID.SetSize(TotalTextHeading);
//	if(!metric)
	{	
		if(!powerup)
		delete []Parameter_Units_USCS;
      Parameter_Units_USCS = new CString[TotalTextHeading];
	}
//	else
	{
		if(!powerup)
		delete []Parameter_Units_Metric;
		Parameter_Units_Metric = new CString[TotalTextHeading];
	}
	Parameter_ID = new int[TotalTextHeading];
	POSITION pos = e->children.GetHeadPosition();
	while (pos)
    {
		CXmlElement * element = e->children.GetNext(pos);
        WeldDataPatamStringID[i]=element->GetAttribute("textID");
		int Temp=_ttoi(WeldDataPatamStringID[i]);
	    CString str=CVgaMenuItem ::LinearSearch(element->GetAttribute("textID"));
	    Parameter_Heading[i]=str.SpanExcluding (_T("("));
		Parameter_ID[i] = _ttoi(element->GetAttribute("Value"));
        CString Formatvalue;
        CString FormatString=element->GetAttribute("format");
        values.Lookup(FormatString, Formatvalue);

		if(Formatvalue!="")
		{
			format=_ttoi(Formatvalue);
            CString StrUSCS;
		    //	if(!metric)
			{
				StrUSCS=CScreenKeypad::InsertWeldParamUnitsString(false,(CScreenKeypad::FORMAT)format);
				StrUSCS.TrimLeft ();
				StrUSCS.TrimRight ();
				Parameter_Units_USCS[i] = _T("(")+ StrUSCS +_T(")");
			}
		    //	else
			{
				CString StrMetric=CScreenKeypad::InsertWeldParamUnitsString(true,(CScreenKeypad::FORMAT)format);
				StrMetric.TrimLeft ();
				StrMetric.TrimRight ();
				Parameter_Units_Metric[i] = _T("(")+StrMetric+_T(")");
			}

		}
		i++;
	}


	theApp.SetMicronsUpdate();
}

/********************************************************************************************/
/* This function is called when the user clicks on the print button on compare graph screen	*/
/* The function makes a copy of the graphs displyed on the screen. This copy of the graphs	*/
/*is used for printing.																		*/
/********************************************************************************************/
void CChildView::CopyHSCScreenGraphs()
{ 	
	POSITION pos = theApp.GraphsDataList.GetHeadPosition();
	int NoOfGraphs=0;
	while (pos)
	{	CVgaDrawGraph *GraphA= new CVgaDrawGraph();
		CVgaDrawGraph::GraphCount--;
		CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
		obj->CopyGraph(GraphA);
		HSGraphPrintList.AddTail(GraphA);
		NoOfGraphs++;
	}
	switch(NoOfGraphs)
		{
			case 1:
				PrintInfoList.AddTail(HSCGRAPHONE);
				break;
			case 2:
				PrintInfoList.AddTail(HSCGRAPHTWO);
				break;
			case 3:
				PrintInfoList.AddTail(HSCGRAPHTHREE);
				break;
			case 4:
				PrintInfoList.AddTail(HSCGRAPHFOUR);
				break;
		}
}

/************************************************************************************************/
/* This function sends the host command to 332 to get all the values of the printing			*/
/* parameters. The function then stores these values to local variables so that they can be		*/
/* utilized.																					*/
/*1. The function is called on Power Up.														*/
/*2. The function is also called when Ext Preset is Off and Preset is changed.					*/
/*																								*/
/************************************************************************************************/
void CChildView::GetPrintingParameters(bool InilitilizeBaseCount)
{
	int length=0;
	unsigned char * data = (unsigned char *) &WeldSetup_Address;
	CHostCommand * request = new CHostCommand(PrintingParameter_FunId,0,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
		if(ch==ACK)
		{	
			union {
				unsigned char CharData;
				bool BoolData;
					}u;
			if(InilitilizeBaseCount)
			{
				u.CharData=*data++;
				ExtPreset =u.BoolData;
				u.CharData=*data++;
				PrintSetup.IsPrinting=u.BoolData;  
				u.CharData=*data++;
				PrintSetup.IsPageSizeA4=u.BoolData;
				PrintSetup.WeldsPerPage=(int)*data++;
            /*storing Setup print parameters*/
				Setup.PrintSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!Setup.PrintSampleValue)
				Setup.PrintSampleDisable=true;
				else
				Setup.PrintSampleDisable=false;
				u.CharData=*data++;
				Setup.PrintOnAlarmValue=u.BoolData;
			
				/*storing Welddata print parameters*/
				Welddata.PrintSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!Welddata.PrintSampleValue)
				Welddata.PrintSampleDisable=true;
				else
				Welddata.PrintSampleDisable=false;
				u.CharData=*data++;
				Welddata.PrintOnAlarmValue=u.BoolData;
			

				/*storing WeldHistory print parameters*/
				WeldHistory.PrintSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!WeldHistory.PrintSampleValue)
				WeldHistory.PrintSampleDisable=true;
				else
				WeldHistory.PrintSampleDisable=false;
				u.CharData=*data++;
				WeldHistory.PrintOnAlarmValue=u.BoolData;
				
				//storing  PrintSequence print parameters
				PrintSequence.PrintSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!PrintSequence.PrintSampleValue)
				PrintSequence.PrintSampleDisable=true;
				else
				PrintSequence.PrintSampleDisable=false;
				u.CharData=*data++;
				PrintSequence.PrintOnAlarmValue=u.BoolData;

				/*storing PowerGraph print parameters*/
				PowerGraph.PrintSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!PowerGraph.PrintSampleValue)
				PowerGraph.PrintSampleDisable=true;
				else
				PowerGraph.PrintSampleDisable=false;
				u.CharData=*data++;
				PowerGraph.PrintOnAlarmValue=u.BoolData;

				/*storing ColDistance print parameters*/
				ColDistance.PrintSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!ColDistance.PrintSampleValue)
				ColDistance.PrintSampleDisable	=true;
				else
				ColDistance.PrintSampleDisable=false;
				u.CharData=*data++;
				ColDistance.PrintOnAlarmValue=u.BoolData;

				/*storing VelocityGraph print parameters*/
				VelocityGraph.PrintSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!VelocityGraph.PrintSampleValue)
				VelocityGraph.PrintSampleDisable=true;	
				else
				VelocityGraph.PrintSampleDisable=false;
				u.CharData=*data++;
				VelocityGraph.PrintOnAlarmValue=u.BoolData;
			
				/*storing ForceGraph print parameters*/
				ForceGraph.PrintSampleValue	=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!ForceGraph.PrintSampleValue)
				ForceGraph.PrintSampleDisable=true;
				else	
				ForceGraph.PrintSampleDisable=false;
				u.CharData=*data++;
				ForceGraph.PrintOnAlarmValue=u.BoolData;

				/*storing AmplitudeGraph print parameters*/
				AmplitudeGraph.PrintSampleValue	=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);	
				if(!AmplitudeGraph.PrintSampleValue)
				AmplitudeGraph.PrintSampleDisable=true;
				else	
				AmplitudeGraph.PrintSampleDisable=false;
				u.CharData=*data++;
				AmplitudeGraph.PrintOnAlarmValue=u.BoolData;
		
				/*storing FrequencyGraph print parameters*/
				FrequencyGraph.PrintSampleValue	=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!FrequencyGraph.PrintSampleValue)
				FrequencyGraph.PrintSampleDisable=true;
				else	
				FrequencyGraph.PrintSampleDisable=false;
				u.CharData=*data++;
				FrequencyGraph.PrintOnAlarmValue=u.BoolData;
				

				/* storing USB parameters*/

				u.CharData=*data++;
				USBGlobalFlag=u.BoolData;  


				USBWelddata.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!USBWelddata.USBSampleValue)
				USBWelddata.USBSampleDisable=true;
				else	
				USBWelddata.USBSampleDisable=false;
				u.CharData=*data++;
				USBWelddata.USBOnAlarmValue=u.BoolData;

				USBPowerGraph.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!USBPowerGraph.USBSampleValue)
				USBPowerGraph.USBSampleDisable=true;
				else	
				USBPowerGraph.USBSampleDisable=false;
				u.CharData=*data++;
				USBPowerGraph.USBOnAlarmValue=u.BoolData;

				USBColDistance.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!USBColDistance.USBSampleValue)
				USBColDistance.USBSampleDisable=true;
				else	
				USBColDistance.USBSampleDisable=false;
				u.CharData=*data++;
				USBColDistance.USBOnAlarmValue=	u.BoolData;

				USBVelocityGraph.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!USBVelocityGraph.USBSampleValue)
				USBVelocityGraph.USBSampleDisable=true;
				else	
				USBVelocityGraph.USBSampleDisable=false;
				u.CharData=*data++;
				USBVelocityGraph.USBOnAlarmValue=u.BoolData;

				USBForceGraph.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!USBForceGraph.USBSampleValue)
				USBForceGraph.USBSampleDisable=true;
				else	
				USBForceGraph.USBSampleDisable=false;
				u.CharData=*data++;
				USBForceGraph.USBOnAlarmValue=u.BoolData;

				USBAmplitudeGraph.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!USBAmplitudeGraph.USBSampleValue)
				USBAmplitudeGraph.USBSampleDisable=true;
				else	
				USBAmplitudeGraph.USBSampleDisable=false;
				u.CharData=*data++;
				USBAmplitudeGraph.USBOnAlarmValue=u.BoolData;

				USBFrequencyGraph.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
				if(!USBFrequencyGraph.USBSampleValue)
				USBFrequencyGraph.USBSampleDisable=true;
				else	
				USBFrequencyGraph.USBSampleDisable=false;
				u.CharData=*data++;
				USBFrequencyGraph.USBOnAlarmValue=u.BoolData;
			
		
				Setup.BaseCount=UniversalCount;
				PrintSequence.BaseCount=UniversalCount;
				Welddata.BaseCount=UniversalCount+1-Welddata.PrintSampleValue;
				WeldHistory.BaseCount=UniversalCount;
				PowerGraph.BaseCount=UniversalCount;
				ColDistance.BaseCount=UniversalCount;
				VelocityGraph.BaseCount=UniversalCount;
				ForceGraph.BaseCount=UniversalCount;
				AmplitudeGraph.BaseCount=UniversalCount;
				FrequencyGraph.BaseCount=UniversalCount;

				USBWelddata.BaseCount  = UniversalCount+1-USBWelddata.USBSampleValue;
				USBPowerGraph.BaseCount= UniversalCount;
				USBColDistance.BaseCount=UniversalCount;
				USBVelocityGraph.BaseCount=UniversalCount;
				USBForceGraph.BaseCount=UniversalCount;
				USBAmplitudeGraph.BaseCount=UniversalCount;
				USBFrequencyGraph.BaseCount=UniversalCount;
			}
			else
			{
				data+=84;
				length-=84;
			}

		}
		delete response;
	}
	else
		GetPrintingParameters(InilitilizeBaseCount);
}

/************************************************************************************/
/* The followinf function is used prepare USB Folders List based on their hierarchy	*/
/* arg 1: Path of the USB folder													*/
/* arg 2: Hierarchy Level															*/
/************************************************************************************/
bool CChildView::PrepareUSBList(CString FilePath, int Fun_Id,int TitleID)
{
   char TempArray[10];
	CString Str_USBMemory=_itoa(TitleID,TempArray,10);
   Str_USBMemory=CVgaMenuItem ::LinearSearch(Str_USBMemory);
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CWeldingHistory::SelectedWeldData=1;
	CWeldingHistory::TopMostData=1;

   WIN32_FIND_DATA FindFileData;
   HANDLE hFind = INVALID_HANDLE_VALUE;
  
   CString DirSpec;  
   DirSpec=FilePath+_T("\\*");
   hFind = FindFirstFile(DirSpec, &FindFileData);

   CTypedPtrList<CPtrList, CVgaMenuItem *> TempDataList;
	while(menu->items.GetCount()>0)
	{
		CVgaMenuItem *Obj = menu->items.GetHead();
		int type = Obj->GetType();
      if((type==CVgaMenu::VGA_VGAEXITBUTTON)||(type==CVgaMenu::VGA_ALARMBUTTON)
         ||(type==CVgaMenu::BottomMenu_Id))
		{
         Obj->IsDraw=true;
         TempDataList.AddTail(Obj);
         menu->items.RemoveHead();
		}
		else
		{
		    delete menu->items.RemoveHead();
      }
	}

   CVgaMenuItem * object =0;
	CString Title ;
		
	if((Fun_Id==FOLDERHIERARCHYONE)||(Fun_Id==USBPRESETFOLDER))
   {
		//printf("\n FOLDERHIERARCHYONE");
      Title =	Str_USBMemory/*[Language_Index]*/;
      object = new CVgaTitle(Title);
      object->SetType(CVgaMenu::TITLE);
      object->IsDraw=true;
	   menu->items.AddTail(object);
   }

	else if(Fun_Id==FOLDERHIERARCHYTWO)
   {
	//	printf("\n FOLDERHIERARCHY2");
      Title=CUSBFolder::SecondHierTitle;
      object = new CVgaTitle(Title);
      object->SetType(CVgaMenu::TITLE);
      object->IsDraw=true;
	   menu->items.AddTail(object);
   }

	else if(Fun_Id==FOLDERHIERARCHYTHREE)
   {
	//	printf("\n FOLDERHIERARCHY3");
      Title=CUSBFolder::ThirdHierTitle;
      object = new CVgaTitle(Title);
      object->SetType(CVgaMenu::TITLE);
      object->IsDraw=true;
	   menu->items.AddTail(object);
   }

   page_no=ONE;
		
	if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&ValidFolderName(FindFileData.cFileName, Fun_Id))
	{
      CUSBFolder  * object =0;
    //  printf("\n Fun_Id=%d",Fun_Id);
		object = new CUSBFolder(FindFileData.cFileName, FilePath+_T("\\")+FindFileData.cFileName,TitleID,Fun_Id);
      object->SetType(CVgaMenu::SUBMENU);
      object->IsDraw=true;
      object->RectShow=true;
      ((CUSBFolder*)object)->GetDiaplayName(Fun_Id);
      menu->items.AddTail(object);
	}
	while (FindNextFile(hFind, &FindFileData) != 0) 
    {
      if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&ValidFolderName(FindFileData.cFileName, Fun_Id))
		{
         CUSBFolder  * object =0;
		   object = new CUSBFolder(FindFileData.cFileName, FilePath+_T("\\")+FindFileData.cFileName,TitleID,Fun_Id);
         object->SetType(CVgaMenu::SUBMENU);
         object->IsDraw=true;
         object->RectShow=true;
         ((CUSBFolder*)object)->GetDiaplayName(Fun_Id);
         menu->items.AddTail(object);
		}
	}
   POSITION pos2 = TempDataList.GetHeadPosition();
	while(pos2)
	{
		CVgaMenuItem *Obj = TempDataList.GetNext(pos2);
		menu->items.AddTail(Obj);
	}
	while(TempDataList.GetCount())
		TempDataList.RemoveHead();
   
  /* object = 0;
	object = new CVgaBottomMenu();
   object->PSType=CVgaMenu::BottomMenu_Id;
   if (object)
      object->SetType(CVgaMenu::BottomMenu_Id);
   object->IsDraw = true;
   menu->items.AddTail(object);*/
   RecalculateMenuItemsLayout(MAXSCRNButton_Height,menu);
   return true;
}

/************************************************************************************/
/* The following function is used to Check whether the passed File name is valid	*/
/* for the respectine hierarchy level.												*/
/* arg 1: File name to be checked													*/
/* arg 2: Hierarchy Level															*/
/************************************************************************************/
bool CChildView::ValidFolderName(CString FileName, int Fun_Id)
{
	switch(Fun_Id)
	{
		case FOLDERHIERARCHYONE:
		{
			return true;
			break;
		}

		case FOLDERHIERARCHYTWO:
		{
			if(FileName.GetLength()!=YEARMONTHFOLDERNAME)
				return false;
			
			for(int i=0;i<YEARMONTHFOLDERNAME;i++)
			{	
				if(i!=4)
				if(!((FileName.Mid(i,1)<=0x39) && (FileName.Mid(i,1)>=0x30)))
					return false;
			}
			if(FileName.Mid(4,1)!="_")
				return false;
			else
				return true;
			break;
		}
		case FOLDERHIERARCHYTHREE:
		{
			if(FileName.GetLength()!=DATESIZE)
				return false;
			
				if(!((FileName.Mid(0,1)<=0x33) && (FileName.Mid(0,1)>=0x30)))
					return false;
				
				if(((FileName.Mid(0,1)==0x33) && (FileName.Mid(1,1)>=0x32)))
					return false;
				
				if(!((FileName.Mid(1,1)<=0x39) && (FileName.Mid(1,1)>=0x30)))
					if(!((FileName.Mid(0,1)<0x33)))
					return false;

		
				return true;
		
			break;
		}
		case FOLDERHIERARCHYFOUR:
		{
			
			break;
		}
		case USBPRESETFOLDER:
		{
			return true;
			break;
		}
		case USBPRESETSCRN:
		{
			
			if(FileName.Find(_T("Preset"),0)!=(-1))
			{
				if(FileName.GetLength()>10)
				{
					
				   int t =FileName.Find(L".log",0);
					if(t!=(-1))
						return true;
				}
			}
		}
		break;
	}
	return false;
}

/************************************************************************************/
/* The following function is used to write the Graph data to the USB Disk.			*/
/* the function checks the graph type and writes that graph in its respective file	*/
/*																					*/
/************************************************************************************/
bool CChildView::SendUSBGraphData()
{
//	printf("\n SendUSBGraphData");
   if(!USBGraphsList.GetCount())
		return false;

	if(!USBPresent() || USBFullAlarm)
	{
	   if(USBGraphsList.GetCount())
         delete USBGraphsList.RemoveHead();
      
		return false;
	}

	CVgaDrawGraph *object = USBGraphsList.GetHead();

	//CString Path =GetCurrentFilePath();
   CString Path = CurrentFilepath;

   CString FileName;
	int GraphType= object->GraphData.graph_type;
	switch(GraphType)
	{
   case DISTINGRAPH:
		FileName="ColDistGraph.log";
	break;
   
   case DISTMMGRAPH:
      FileName="ColDistGraph.log";
	break;

   case POWGRAPH:
		FileName="PowerGraph.log";
	break;

   case VELINGRAPH:
		FileName="VelocityGraph.log";
	break;
   
   case VELMMGRAPH:
		FileName="VelocityGraph.log";
	break;

   case FORCELBGRAPH:
		FileName="ForceGraph.log";
	break;
   
   case FORCENGRAPH:
		FileName="ForceGraph.log";
	break;

   case AMPLIGRAPH:
		FileName="AmpGraph.log";
	break;

   case FREQUGRAPH:
		FileName="FreqGraph.log";
	break;
	}	
	CString GraphPath=	Path+FileName;

	CFile f;
	CFileException e;
	TRY
	{     
         CVgaDrawGraph * tempGraph= new CVgaDrawGraph();
		   int  size= sizeof(tempGraph->GraphData);
//         printf("\n size in write=%d",size);
         delete tempGraph;
			//int  size= sizeof(CVgaDrawGraph());
			char Comma=',';
			int TotalSize=sizeof(int)+sizeof(char)+size+sizeof(char);
			char *TempBuf =  new char[TotalSize];
			char *BufPtr = TempBuf;
		
			memcpy(BufPtr,&UniqueID,sizeof(int));
			BufPtr+=sizeof(int);
			memcpy(BufPtr,&Comma,sizeof(char));
			BufPtr+=sizeof(char);
			memcpy(BufPtr,&(object->GraphData),size);
			BufPtr+=size;
			memcpy(BufPtr,&Comma,sizeof(char));
			BufPtr+=sizeof(char);

		if( !f.Open( GraphPath, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
		{
      //   printf("\n deleting USBGraphsList with file no t open");
         if(USBGraphsList.GetCount())
            delete USBGraphsList.RemoveHead();
         
         free(TempBuf);
         return false;
		}
		else
		{
			f.SeekToEnd();
     //    printf("\n write complete graph data");
			f.Write(TempBuf,TotalSize);
			f.Close();
			free(TempBuf);
     //    printf("\n deleting USBGraphsList with write");
         if(USBGraphsList.GetCount())
            delete USBGraphsList.RemoveHead(); 
			return true;
		}
		
	}
   CATCH_ALL(E)
	{
		ISUSBPresent=false;
      TCHAR  szCause[255];
      E->GetErrorMessage(szCause, 255);
      CString x;
      x = _T("The data file could not be opened because of this error: ");
      x += szCause;
		ISUSBPresent=USBPresent();
      AfxMsgBox(x);
	}
   END_CATCH_ALL

   if(USBGraphsList.GetCount())
      delete USBGraphsList.RemoveHead();
   return false;
}

/************************************************************************************/
/* The following function is used when any graph on view Graph screen is to be		*/
/* printed. The function makes the copy of the graph object to be send for printing	*/
/*																					*/
/************************************************************************************/
CString CChildView::CopyScreenGraphs()
{ 	
	CString SysPressureStr="";
	
	POSITION pos = theApp.GraphsDataList.GetHeadPosition();
	while (pos)
	{	
		CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
		if((obj->GraphData.GraphRequestValue==GraphOneRequestValue)||
			(obj->GraphData.GraphRequestValue==GraphTwoRequestValue)||AutoRefreshon)
		{
			CVgaDrawGraph *GraphA= new CVgaDrawGraph();
			CVgaDrawGraph::GraphCount--;
			obj->CopyGraph(GraphA);

			GraphPrintList.AddTail(GraphA);
			SysPressureStr="";
			for(int i=0;i<20;i++)
			{
				if(GraphA->GraphData.SystemPressure[i]=='\0')
					break;
				SysPressureStr+=GraphA->GraphData.SystemPressure[i];
			}
		}
		
	}
	return SysPressureStr;
}

/************************************************************************************/
/* The following function is used to write Weld data to USB Disk. The function gets	*/
/* the path of the file by calling function GetCurrentFilePath() and writes the weld*/
/* data in Weld Data.log. the file is created if not already present.				*/
/*																					*/
/************************************************************************************/

bool CChildView::SendUSBWeldData()
{	
//	printf("\n SendUSBWeldData");
   if(!USBHistoryList.GetCount())
		return false;

	if(!USBPresent() || USBFullAlarm)
	{
		if(USBHistoryList.GetCount())
         delete USBHistoryList.RemoveHead();
     
		return false;
	}
   
	CHistoryData *object1 = USBHistoryList.GetHead();
	CHistoryData *object = new CHistoryData();

	memcpy(object,object1,sizeof(CHistoryData()));
//	CString FilePath = GetCurrentFilePath();
   CurrentFilepath = GetCurrentFilePath(object);
   
	CString	pFileName=/*FilePath*/CurrentFilepath + "WeldData.log";
	
	//this piece of code sends an integer to be saved to the usb before we start recording the usual welddata
	int AmpUnitsTemp = 0, PowerUnitsTemp = 0;

	if(AmplitudeMicrons==true)
		AmpUnitsTemp=2000000000;
	else
		AmpUnitsTemp=1000000001;
	if(PeakPowerMicrons)
		PowerUnitsTemp=2000000000;
	else
		PowerUnitsTemp=1000000001;

	CreateFolder(false);
	CFile f;
	bool flag =false;
	CFileException e;
	TRY
	{
		if( !f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
		{
			
			#ifdef _DEBUG
			if(e.m_cause==CFileException::generic)
				TRACE("\n !! GENERIC");
			else if(e.m_cause==CFileException::badPath)
				TRACE("\n !! bad path");
			else if(e.m_cause==CFileException::tooManyOpenFiles )
				TRACE("\n !! too many files open");
			else if(e.m_cause==CFileException::fileNotFound )
				TRACE("\n !! file not found");
			else if(e.m_cause==CFileException::accessDenied )
				TRACE("\n !! access denied");
			else if(e.m_cause==CFileException::diskFull)
				TRACE("\n !! disc full");
			else if(e.m_cause==CFileException::invalidFile)
				TRACE("\n !! invalid file");
			afxDump << "File could not be opened " << e.m_cause << "\n";
			#endif
		}
		else
		{
			
			   char Comma =',';
				bool OldUnits;
				bool USBMetric=metric;
         //   printf("\n USBMetric=%d",USBMetric);
				if(f.GetLength()==0)
				{
					UniqueID =1;
					OldUnits=!metric;
				}
				else 
				{
					
					CHistoryData *TempObj = new CHistoryData();
					int ObjectSize =sizeof(CHistoryData()) +sizeof(Comma);
					ObjectSize=(-ObjectSize);
					f.Seek(ObjectSize,CFile::end);
					f.Read(TempObj,sizeof(CHistoryData()));
					
					UniqueID=TempObj->UniqueId;
					UniqueID++;
					OldUnits= TempObj->Units;
					free(TempObj);
					
				}
				f.Close();
				object->UniqueId=UniqueID;
			
				int  size= sizeof(CHistoryData());
				int TotalSize = sizeof(int)+sizeof(char)+sizeof(bool)+size+sizeof(char)+sizeof(char);
				TotalSize+=sizeof(int)+sizeof(int);
				if(OldUnits!=metric)
					 TotalSize += (MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR));

				char *TempBuf =  new char[TotalSize];
				char *BufPtr = TempBuf;
		
				memcpy(BufPtr,&AmpUnitsTemp,sizeof(int));
				BufPtr+=sizeof(int);

				memcpy(BufPtr,&PowerUnitsTemp,sizeof(int));
				BufPtr+=sizeof(int);
				memcpy(BufPtr,&UniqueID,sizeof(int));
				BufPtr+=sizeof(int);
				memcpy(BufPtr,&Comma,sizeof(char));
				BufPtr+=sizeof(char);
				memcpy(BufPtr,&metric,sizeof(bool));
				BufPtr+=sizeof(bool);
				
				if(OldUnits!=metric)
				{
					if(metric)
               {
					   memcpy(BufPtr,&CWeldingHistory::ParameterUnitMetric[0][0],MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR));
               }
					else
               {
						memcpy(BufPtr,&CWeldingHistory::ParameterUnitUSCS[0][0],MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR));
               }
			
					BufPtr+=MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR);
				}
			
				memcpy(BufPtr,&Comma,sizeof(char));
				BufPtr+=sizeof(char);
			
				memcpy(BufPtr,object,size);
				BufPtr+=size;
		
				memcpy(BufPtr,&Comma,sizeof(char));
				BufPtr+=sizeof(char);
			
				delete object;
					if( f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
					{
						f.SeekToEnd();
//                  printf("\n write whole data");
						f.Write(TempBuf,TotalSize);
						f.Close();
						
					}
					delete TempBuf;
					
      }
	}
   CATCH_ALL(E)
	{
	   TCHAR  szCause[255];
      E->GetErrorMessage(szCause, 255);
      CString x;
      x = _T("The data file could not be opened because of this error: ");
      x += szCause;
      ISUSBPresent=false;
      flag =true;
		ISUSBPresent=USBPresent();
      AfxMsgBox(x);
   }
   END_CATCH_ALL
   
   if(flag)
	{	
		if(USBHistoryList.GetCount())
      {
		 //  printf("\n deleting USBHistoryList with flag");
         USBHistoryList.RemoveHead();
      }
		return false;
	}
	else
	{
		if(USBHistoryList.GetCount())
      {
		//	printf("\n deleting USBHistoryList with count");
         delete USBHistoryList.RemoveHead();
      }
		//delete object;
		return true;
	}
}

/********************************************************************************/
/* The following function is called to check whether the passed DataID( can be	*/
/* weld data, any graph data) is required for any particular weld cycle. The	*/
/* function  returns true if data is required and false if not.					*/
/********************************************************************************/
bool CChildView::DataForUSB(int DataId)
{	
	if((!ISUSBPresent)||(!USBGlobalFlag))
	{
   //   printf("\n (!ISUSBPresent)||(!USBGlobalFlag)");
		return false;
	}
	switch(DataId)
	{
		case WELDDATAONSAMPLEID:
		{
		//	printf("\n WELDDATAONSAMPLEID");	
			if((PresentAlarmCount) && (USBWelddata.USBOnAlarmValue))
			{
			//	printf("\n (PresentAlarmCount) && (USBWelddata.USBOnAlarmValue)");
            return true;
			}
			if(!USBWelddata.USBSampleDisable)
				if((PresentWeldCount-USBWelddata.BaseCount)>=USBWelddata.USBSampleValue)
            {
				//	printf("\n (PresentWeldCount-USBWelddata.BaseCount)>=USBWelddata.USBSampleValue");
               return true;
            }
		}
		break;
		case COLDISTANCEID:
		{
		//	printf("\n COLDISTANCEID");	
         if((PresentAlarmCount) && (USBColDistance.USBOnAlarmValue))
				return true;
			else if(!USBColDistance.USBSampleDisable)
				if((((PresentWeldCount-USBColDistance.BaseCount)%(USBColDistance.USBSampleValue))==1)
						||((PresentWeldCount-USBColDistance.BaseCount)==1)||(USBColDistance.USBSampleValue==1))
				return true;
		
		}
		break;
		case VELOCITYGRAPHID:
		{	
//			printf("\n VELOCITYGRAPHID");
         if((PresentAlarmCount) && (USBVelocityGraph.USBOnAlarmValue))
				return true;
			else if(!USBVelocityGraph.USBSampleDisable)
				if((((PresentWeldCount-USBVelocityGraph.BaseCount)%(USBVelocityGraph.USBSampleValue))==1)
						||((PresentWeldCount-USBVelocityGraph.BaseCount)==1)||(USBVelocityGraph.USBSampleValue==1))
				return true;
			
		}
		break;
		case FORCEGRAPHID:
		{
//			printf("\n FORCEGRAPHID");
         if((PresentAlarmCount) && (USBForceGraph.USBOnAlarmValue))
				return true;
			else if(!USBForceGraph.USBSampleDisable)
				if((((PresentWeldCount-USBForceGraph.BaseCount)%(USBForceGraph.USBSampleValue))==1)
						||((PresentWeldCount-USBForceGraph.BaseCount)==1)||(USBForceGraph.USBSampleValue==1))
					return true;
		}
		break;
		case AMPLITUDEGRAPHID:
		{
//			printf("\n AMPLITUDEGRAPHID");
         if((PresentAlarmCount) && (USBAmplitudeGraph.USBOnAlarmValue))
				return true;
			else if(!USBAmplitudeGraph.USBSampleDisable)
				if((((PresentWeldCount-USBAmplitudeGraph.BaseCount)%(USBAmplitudeGraph.USBSampleValue))==1)
						||((PresentWeldCount-USBAmplitudeGraph.BaseCount)==1)||(USBAmplitudeGraph.USBSampleValue==1))
					return true;	
		}
		break;
		case POWERGRAPHID:
		{
//			printf("\n POWERGRAPHID");
         if((PresentAlarmCount) && (USBPowerGraph.USBOnAlarmValue))
				return true;
			else if(!USBPowerGraph.USBSampleDisable)
				if((((PresentWeldCount-USBPowerGraph.BaseCount)%(USBPowerGraph.USBSampleValue))==1)
						||((PresentWeldCount-USBPowerGraph.BaseCount)==1)||(USBPowerGraph.USBSampleValue==1))
					return true;		
		}
		break;
		case FREQUENCYGRAPHID:
		{
//			printf("\n FREQUENCYGRAPHID");
         if((PresentAlarmCount) && (USBFrequencyGraph.USBOnAlarmValue))
				return true;
			else if(!USBFrequencyGraph.USBSampleDisable)
				if((((PresentWeldCount-USBFrequencyGraph.BaseCount)%(USBFrequencyGraph.USBSampleValue))==1)
						||((PresentWeldCount-USBFrequencyGraph.BaseCount)==1)||(USBFrequencyGraph.USBSampleValue==1))
					return true;		
		}
		break;
	}
return false;
}

/************************************************************************/
/* The function is called when data for USB is ready to be written		*/
/* to USB Disk. The function calls SendUSBWeldData(),SendUSBGraphData()	*/
/* for writing wEld data and Graph data respectively.					*/
/************************************************************************/
UINT CChildView::WriteDataToUSB(LPVOID)
{
	while(1)
	{	
//		try
		{
			HANDLE handle;
			handle = thisPtr->WaitForUSBData;
			WaitForSingleObject(handle, INFINITE);
         
         if(thisPtr->USBFullAlarm)
         {
            thisPtr->USBMutex.Lock();
				while (thisPtr->USBHistoryList.GetCount())
					delete thisPtr->USBHistoryList.RemoveHead();
            
            while(thisPtr->USBGraphsList.GetCount())
					delete thisPtr->USBGraphsList.RemoveHead();

				thisPtr->USBGraphCountList.RemoveAll();
				thisPtr->USBMutex.Unlock();
         }
			int NoOfWeldData = thisPtr->USBHistoryList.GetCount();
			if(thisPtr->USBPresent())
			{
				for(int WeldData=0;WeldData<NoOfWeldData;WeldData++)
				{
					//thisPtr->USBMutex.Lock();
					thisPtr->SendUSBWeldData();
				
					int NoOfGraphs=thisPtr->USBGraphCountList.RemoveHead();
             //  printf("\n NoOfGraphs in write=%d",NoOfGraphs);
					for(int i=0;i<NoOfGraphs;i++)
					{				
						thisPtr->SendUSBGraphData();
					}
					
				}
				if(!thisPtr->USBHistoryList.GetCount()) 
				{
					thisPtr->WaitForUSBData.ResetEvent();
				}
			}
			else /*case USB not present:: deleting USB graph list and weld data list*/
			{				
				thisPtr->USBMutex.Lock();
				while (thisPtr->USBHistoryList.GetCount())
					delete thisPtr->USBHistoryList.RemoveHead();
            
            while(thisPtr->USBGraphsList.GetCount())
					delete thisPtr->USBGraphsList.RemoveHead();

				thisPtr->USBGraphCountList.RemoveAll();
				thisPtr->USBMutex.Unlock();
					
			}
		}/*
		catch(CException *E)
		{
			CString x;
			x.Format(_T("File not found: Exception code is %d,error code is %d, and file name is %s"));
			AfxMessageBox(x);
			E->Delete();
			thisPtr->USBPresent();
		}*/
	}
}

/******************************************************************/
/*  This Function will handle Alarm change in polling command.    */
/******************************************************************/
bool CChildView::HandleAlarmChange()
{
  if((TemporaryAlarmCount != AlarmCount)||((AlarmUpdateRequired==false)&&(AlarmCount!=0)))
  {		  
	   if((IsAlarmScreen ==true)&&(TemporaryAlarmCount!=AlarmCount))//Already on Alarm Screen
		{														//and alarm count change
		//	printf("\n IsAlarmScreen ==true");
         if(TemporaryAlarmCount==0)//Alarm Count Changes to zero.
			{
				AlarmCount = TemporaryAlarmCount;
				page_no=1;
			
            IsAlarmScreen=false;
            while(menus.GetCount()>=2)
            {
               if(theApp.menuName==AlarmMenuName)
               {
                   theApp.menuName=menusname.RemoveTail();
                   page_no=menus.RemoveTail();
                   theApp.MenuPointer=menupointers.RemoveTail();
                   break;
               }
               AlarmUpdateRequired=false;               
               theApp.menuName=menusname.RemoveTail();
               page_no=menus.RemoveTail();
               theApp.MenuPointer=menupointers.RemoveTail();
            }
            if(theApp.menuName==CVgaBottomMenu::WeldResults_ID)
               CChildView::thisPtr->RunResultScreen=true;
            ModifyObjectList(theApp.MenuPointer); 
            Invalidate();
				return true;
			}
			else //Alarm Count Changes but not equal to zero.
			{
				AlarmCount = TemporaryAlarmCount;
				page_no=1;
            if(theApp.menuName==CVgaBottomMenu::WeldResults_ID)
                  CChildView::thisPtr->RunResultScreen=true;
            ModifyObjectList(theApp.MenuPointer); 
            IsAlarmScreen =true;
            AlarmUpdateRequired=false;
            Invalidate();
				return true;
			}
		}
		/*Alarm count changes but  user is not on Alarm Screen.*/
		else if(IsAlarmScreen ==false)
		{
 //        printf("\n IsAlarmScreen ==false");
			CDC*pDC=GetDC();
         AlarmCount = TemporaryAlarmCount;
         if(TemporaryAlarmCount!=0)
         {
 //           printf("\n TempAlarmCount!=0");
            if(AlarmUpdateRequired==false)
            {
               if(ScreenSetupFlag)
		            return false;
            }
            AlarmUpdateRequired=true;
            GlobalAlarmObject->SetText(GetAlarmString(GlobalAlarmObject));
		      GlobalAlarmObject->Draw(pDC);
         }
         else
         {
 //           printf("\n TempAlarmCount==0");
            AlarmUpdateRequired=false;
            if(ScreenSetupFlag)
               return false;
            if((theApp.GraphsDataList.GetCount()==0))
						CVgaMenuItem::DrawRect(pDC,CChildView::TitleBarColor, ALARMBUTTONRECT_RE);
				else
            {
					//ModifyObjectList(theApp.MenuPointer);
               Invalidate();
            }
         }
		   ReleaseDC(pDC);
      }
	}
   return false;
}

UINT CChildView::EtherNetAndAlarmHandle(LPVOID)
{
	while(1)
	{	
		HANDLE handle;
		handle = thisPtr->WaitForEtherNetAlarmHandle;
		WaitForSingleObject(handle, INFINITE);
      if(thisPtr->StartWeldData==1)
	      {
		      thisPtr->StartWeldData=0;
            

		      if(app->ether->clients.GetUpperBound() != -1)//>0
		      {
			      int length = 0;//length of pointer to be send to 332.
			      CHostCommand * request = new CHostCommand(GetWeldData, 0,length);
			      CHostCommand * response = app->SendEnHostCommand(request);
			      if (response)
			      {
				      length=response->GetBufLength();
				      unsigned char * buf =  response->GetBuffer();
                //  printf("\n send ether");
                 // printf(" Start%d*",CChildView::WeldCycleCount);
                  app->SendWeldData(buf,length);
				      delete response;
			      }
			      
		      }
		      
	      }
      thisPtr->HandleAlarmChange();
      thisPtr->WaitForEtherNetAlarmHandle.ResetEvent();
   }
   return 0;
}

/************************************************************************/
/* The followinf function checks for all the conditions that should be	*/
/* true for printing data.they are:										*/
/* 1. Printing On/Off													*/
/* 2. Printer present/not												*/
/* 3. Weld count !=0													*/
/* 4. Abort printing not pressed										*/
/************************************************************************/
bool CChildView::CheckForPrinting()
{
	if((PrintSetup.IsPrinting)&&(PrinterPresent)&&(PresentWeldCount)&&(!AbortPrinting))
		return true;
	else
		return false;

}
/************************************************************************/
/* The following function is used to Set The request value for Graphs	*/
/* and weld data that is needed to get the data from 332.				*/
/* arg 1: Pointer to TotalGraphRequestValue								*/
/* arg 2: Total no. of graphs rewuired for present weld cycle			*/
/* arg 3: Graph ID														*/
/* arg 4: Graph request value for this Graph ID							*/
/* arg 5: Pointer to the structure for this Graph Printing Parameters	*/
/************************************************************************/
void CChildView::SetRequestValue(int *TotalGraphRequestValue, int *TotalGraph, int ID,int CurrentGraphRequestValue, PrintValues *CurrentGraph)
{
	if(((PresentAlarmCount) && (CurrentGraph->PrintOnAlarmValue)&&(CheckForPrinting())) ||(DataForUSB(ID)))
	{
		(*TotalGraphRequestValue)+=CurrentGraphRequestValue;
		(*TotalGraph)++;
	}
	else if((!CurrentGraph->PrintSampleDisable)&&(CheckForPrinting()))
		if((((PresentWeldCount-CurrentGraph->BaseCount)%(CurrentGraph->PrintSampleValue))==1)
			||((PresentWeldCount-CurrentGraph->BaseCount)==1)||(CurrentGraph->PrintSampleValue==1))
	{	
		(*TotalGraphRequestValue)+=CurrentGraphRequestValue;
		(*TotalGraph)++;
	}
}

/****************************************************************************/
/* The following function returns the current working directory For the		*/	
/* USB Disk. the function checks for the current date, year and power supply*/
/* name and creates the path accordingly.									*/
/****************************************************************************/
CString CChildView::GetCurrentFilePath()
{
 	CString PathStr = "\\USBDisk\\" + PowerSupply + "\\";
	/* getting current date, month and year*/
	char YYYY_MM[YEARMONTHFOLDERNAME];
	char DD[2];
	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	_itoa(SysTime.wYear,YYYY_MM,10);
	YYYY_MM[4]='_';
	if(SysTime.wMonth<10)
	{
		YYYY_MM[5]='0';
		_itoa(SysTime.wMonth,YYYY_MM+6,10);
	}
	else
		_itoa(SysTime.wMonth,YYYY_MM+5,10);
	YYYY_MM[7]='\0';

		

	if(SysTime.wDay<10)
	{
		DD[0]='0';
		_itoa(SysTime.wDay,DD+1,10);
	}
	else
		_itoa(SysTime.wDay,DD,10);
	DD[2]='\0';
	
   printf("\n YYYY_MM = ");
   for(int j=0;j<YEARMONTHFOLDERNAME;j++)
      printf("%c",YYYY_MM[j]);
   
   printf("\n DD = ");
   for(j=0;j<DATESIZE;j++)
      printf("%c",DD[j]);

	YearMonthName="";
	Date="";
	for(int i=0;i<YEARMONTHFOLDERNAME;i++)
	{
		YearMonthName += YYYY_MM[i];
		PathStr+= YYYY_MM[i];
	}

	PathStr+="\\";

	for(i=0;i<DATESIZE;i++)
	{
		PathStr+= DD[i];
		Date+= DD[i];
	}
	PathStr+="\\";
	return PathStr;
}

CString CChildView::GetCurrentFilePath(CHistoryData *object)
{
 	CString PathStr = "\\USBDisk\\" + PowerSupply + "\\";
   CString TempDate = object->USBDateStr;
   
	CString Year = TempDate.Right(2);
   CString Day,Month;

   if(CChildView::metric)
   {
      Day = TempDate.Left(2);
      Month= TempDate.Mid(3,2);
   }
   else
   {
      Month = TempDate.Left(2);
      Day = TempDate.Mid(3,2);
   }
   
   /* getting current date, month and year*/
	char YYYY_MM[YEARMONTHFOLDERNAME];
	char DD[2];
   int count = 0;
   
   YYYY_MM[count]='2';
   count++;
   YYYY_MM[count]='0';
   count++;

	for(int j=0;j<Year.GetLength();j++)
   {
      YYYY_MM[count]= Year.GetAt(j);
      count++;
   }
   
   YYYY_MM[count]='_';
   count++;
   for(j=0;j<Month.GetLength();j++)
   {
      YYYY_MM[count]= Month.GetAt(j);
      count++;
   }
   
   YYYY_MM[count]='\0';

   for(j=0;j<Day.GetLength();j++)
   {
      DD[j] = Day.GetAt(j);
   }
	DD[2]='\0';

   YearMonthName="";
	Date="";
	for(int i=0;i<YEARMONTHFOLDERNAME;i++)
	{
		YearMonthName += YYYY_MM[i];
		PathStr+= YYYY_MM[i];
	}

	PathStr+="\\";

	for(i=0;i<DATESIZE;i++)
	{
		PathStr+= DD[i];
		Date+= DD[i];
	}
	PathStr+="\\";
	return PathStr;
}

/************************************************************************/	
/* The following functio is used to Get the Power Suply name from 332.	*/
/* the function is called at the Power up and when power supply name	*/
/* is changed.															*/
/************************************************************************/
void CChildView::GetPowerSupplyName()
{
	PowerSupply="";
	int length=0;
	unsigned char * data = (unsigned char *) &WeldSetup_Address;
	CHostCommand * request = new CHostCommand(PowerSupply_FunId,0,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		data--;
		length = response->GetDataLength();
		if(ch==ACK)
		{	
			for(int	i=0;i<PSNAMELENGTH;i++)
			{
				TCHAR TempChar = *data++;
				if(TempChar==0x00)
					break;
				PowerSupply += TempChar;
			}
		}
		delete response;
	}
	else
		GetPowerSupplyName();
}

/************************************************************************/
/* The functio is used to create folders. The function firsk checks for	*/
/* the presence of the folder in USB Disk for curren working directory	*/
/* and if it is not found then a ner folder is created.					*/
/************************************************************************/
void CChildView::CreateFolder(bool CheckForPreset)
{
	CString	Path="\\USBDisk";
	CString TempPath;
	if(!CheckForPreset)
	{
		
		if(!IsFolderPresent(Path,PowerSupply))
		{
			Path="\\USBDisk\\"+ PowerSupply;
			CreateDirectory(Path,NULL);
			TempPath = Path +"\\"+YearMonthName;
			CreateDirectory(TempPath,NULL);
			TempPath += "\\"+ Date;
			CreateDirectory(TempPath,NULL);
			TempPath =Path+ "\\"+"Presets";
			CreateDirectory(TempPath,NULL);
		}
		else 
		{
			
			TempPath= "\\USBDisk\\"+ PowerSupply;
			if(!IsFolderPresent(TempPath,YearMonthName))
			{
			
				TempPath= TempPath+"\\"+YearMonthName;
				CreateDirectory(TempPath,NULL);	
				TempPath += "\\"+ Date;
				CreateDirectory(TempPath,NULL);
			}
			else
			{
			
				TempPath= "\\USBDisk\\"+ PowerSupply+"\\"+YearMonthName;
				if(!IsFolderPresent(TempPath,Date))
				{	
					TempPath= TempPath+"\\"+Date;
					CreateDirectory(TempPath,NULL);
				}
			}
			TempPath= "\\USBDisk\\"+ PowerSupply;
			if(!IsFolderPresent(TempPath,"Presets"))
			{
				TempPath= TempPath+"\\Presets";
				CreateDirectory(TempPath,NULL);	
			}
		}
	}
	else
	{
		if(!IsFolderPresent(Path,PowerSupply))
		{
			Path="\\USBDisk\\"+ PowerSupply;
			CreateDirectory(Path,NULL);
			TempPath = Path +"\\"+YearMonthName;
			CreateDirectory(TempPath,NULL);
			TempPath += "\\"+ Date;
			CreateDirectory(TempPath,NULL);
			TempPath =Path+ "\\"+"Presets";
			CreateDirectory(TempPath,NULL);
		}
	}
}

/*********************************************************************/
/* The following function is used check the presence of File at a	   */
/* specific path.													               */
/* arg 1: Path for the file.										            */
/* arg 2: File name to be searched								         	*/
/* A true is returned is folder is present else a false is returned. */
/*********************************************************************/
bool CChildView::IsFolderPresent(CString Path, CString FileName)
{

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CString argv=Path;
	CString DirSpec;  
    DirSpec=argv+_T("\\*");
    hFind = FindFirstFile(DirSpec, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		FindClose(hFind);
		return false;
	} 
	else 
	{
	if(FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )
		{
			if(FileName==FindFileData.cFileName)
			{
				FindClose(hFind);
				return true;
			}
		}
		 while (FindNextFile(hFind, &FindFileData) != 0) 
		{
         
			if(FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )
			{
				if(FileName==FindFileData.cFileName)
				{
					FindClose(hFind);
					return true;
				}
			}
		}
	}
	return false;
}

 /****************************************************************/
/* This function is called to show message screen when required	*/
/* arg 1: Message to be shown.									*/
/****************************************************************/
void CChildView::ShowMessageScreen(CString Message)
{
	CDC *pDC=GetDc();
	EnableWindow(false);

	/*Drawing Message Rectangle in specified color*/
	CVgaMenuItem::DrawRect(pDC, Black,MESSAGESCRN_BLACKRECT);
	CVgaMenuItem::DrawRect(pDC, Blue, MESSAGESCRNRECT);

	/*Drawing Message Text*/
	CVgaMenuItem::DrawText(pDC, Bigfont,White , MESSAGESCRNRECT,Message,true);
	ReleaseDc(pDC);	
	DisableFlag=true;
   InitialiseTimer(ERROR_MESSAGE_TIMER,MESSAGESCRNTIME);
	EnableWindow(true);
}

/********************************************************************/	
/* The following function isused to skeck the presence of USB Disk	*/
/* The function returns true if USB is present else a false is		*/
/* returned.														*/
/********************************************************************/
bool CChildView::USBPresent()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	CString DirSpec="USBDisk\\";  
    hFind = FindFirstFile(DirSpec, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		FindClose(hFind);
		return false;
	} 
	else 
	{
		FindClose(hFind);
		return true;
	}
}

void CChildView::GetAveragePowerGraph(CDC *pDC, CChildView * view)
{
	CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   POSITION POSI=menu->items.GetHeadPosition(); 
   int length =1;
	unsigned char data1=(char)04;
	unsigned char * data = (unsigned char *) &data1;

	CHostCommand * request = new CHostCommand(PowerMatchCurve_FunctionId, data, length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if (response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();//Getting Data.
		 length = response->GetDataLength();//Getting Length.
		 if(ch==theApp.ACK)//If Ack.
		 {	   //store graph data

			 while ((POSI)&&(length>0))
          {
             object= menu->items.GetNext(POSI);
	          if(object->GetType()==CVgaMenu::VGA_GRAPH_OBJECT)
             {
                   CVgaDrawGraph * ptr = (CVgaDrawGraph *)object;
						 int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                   if(ValueAfterParamID==NO_VALID_GRAPH)
                   {
                      delete response;
                      return;
                   }
                   if(ValueAfterParamID==ptr->GraphType)
                   {
                     ptr->GraphData.graph_type=ValueAfterParamID;
                     int TempVar =*data++;
	                  if(TempVar>0)
		                  CChildView::thisPtr->PMCDisable =true;
	                  else
		                  CChildView::thisPtr->PMCDisable =false;
	                  length--;
	                  ptr->PMCCycleCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
	                  int TimeCount =CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
	                  CChildView::thisPtr->LowerPMCLimit=*data++;
	                  length--;
	                  CChildView::thisPtr->UpperPMCLimit=*data++;
                     length--;
	                  ptr->GraphData.DataLength=0;

	                  if(ptr->PMCCycleCount !=0)
	                  {
		                  short graphdatalength=0;
		                  for(short len=0;len<400;len++)
		                  {
			                  if(*data!=0xFF)
			                  {
				                  ptr->GraphData.graphdata[len]=(short)*data++;
				                  graphdatalength++;
			                  }
			                  else
				                  *data++;
			                  length--;
		                  }
		                  ptr->GraphData.DataLength=graphdatalength;
		               }
	                  if(ptr->GraphData.DataLength==0)
	                  {
		                  CChildView::thisPtr->LowerPMCLimit=0;
		                  CChildView::thisPtr->UpperPMCLimit=0;
	                  
	                  }
	                  CChildView::thisPtr->PMCMaxVdata=*data++;

	                  length--;length--;
                     if(PMCDisable)
                     {
                        ptr->RecalculateAverageGraph(CChildView::thisPtr);
                        ptr->DrawAvgPowerGraph(pDC,CChildView::thisPtr);
                     }
                  }
                  else
                  {
                     *data--;length++;
                     *data--;length++;
                  }
             }
			 }	
       }
       else
       {
           GetAveragePowerGraph(pDC,view);
       }
       delete response;
   }
}
   
void CChildView::ExitProgram()
{
	/*CloseHandle(CChildView::hChildWnd);// Closing Handle of VQS Application
   CWnd *pWndPrev;
   if (pWndPrev = CWnd::FindWindow(NULL,_T("VQS")))
   	   pWndPrev->PostMessage(WM_CLOSE,0,0);*/
	

   BottomHalfTimerOn=true;
	while (keypadList.GetCount())
		delete keypadList.RemoveHead();

	while (menuEntryList.GetCount()>0)
		delete menuEntryList.RemoveHead();

   while(PrintObjectList.GetCount()>0)
		delete PrintObjectList.RemoveHead();
   
   while(PrintSequenceObjectList.GetCount()>0)
		delete PrintSequenceObjectList.RemoveHead();

	while(PrintGraphTextObjectList.GetCount()>0)
		delete PrintGraphTextObjectList.RemoveHead();

   WeldAlarmStringList.RemoveAll();
	WeldHistoryAlarmStringList.RemoveAll();
	GraphAlarmStringList.RemoveAll();
   
   PrintInfoList.RemoveAll();
	
	delete []Parameter_Heading;
	delete []Parameter_Units_Metric;
	delete []Parameter_Units_USCS;
	delete []Parameter_ID;
	delete []GraphWeldDataIdArray;
	delete []WeldDataIdArray;
	exit(1);
}

void CChildView::ErrorBeep()
{
	CHostCommand * request = new CHostCommand(ErrorBeep_FunId, 0, 0);
	CHostCommand * response = app->SendUiHostCommand(request);
	if (response)
		delete response;
}

void CChildView::SendCommandAlarms(int AlarmType)
{

	unsigned char  *data = (unsigned char *) &AlarmType;
	int length = 1;//length of pointer to be send to 332.
	CHostCommand * request = new CHostCommand(GenerateAlarm_FunId, data,length);
	CHostCommand * response = app->SendPollingHostCommand(request);
	if(response)
	{		
		char ch=CHostCommand::AckNak();
		delete response;
	}
}

void CChildView::CheckPrinterStatus()
{//printf("\n ChildView :: CheckPrinterStatus ");
   if(PrintSetup.IsPrinting)
			{
				CPrintDialog dlg(false);
				if(!dlg.GetDefaults())//printer offline
				{

					if(PrinterPresent != PRINTERNOTAVILABLE)
					{	
						PrinterPresent = PRINTERNOTAVILABLE;
						while(PrintObjectList.GetCount()>0)
							delete PrintObjectList.RemoveHead();
						
                  while(PrintSequenceObjectList.GetCount()>0)
							delete PrintSequenceObjectList.RemoveHead();

                  while(PrintGraphTextObjectList.GetCount()>0)
							delete PrintGraphTextObjectList.RemoveHead();
                  
                  WeldAlarmStringList.RemoveAll();
						WeldHistoryAlarmStringList.RemoveAll();
						GraphAlarmStringList.RemoveAll();

 						PrintInfoList.RemoveAll();
						if(!OnKeypadScreen_flag)
							Invalidate();
					}
					/*if(!CVGAButtons::ColdStartInProcess)
						SendCommandAlarms(PRINTEROFFLINEALARM);*/
				}
				else  //printer online
				{
				
					if(PrinterPresent != PRINTERONLINE)
					{
						PrinterPresent = PRINTERONLINE;
						Setup.BaseCount     = UniversalCount;
						PrintSequence.BaseCount=UniversalCount;
						Welddata.BaseCount  = UniversalCount+1-Welddata.PrintSampleValue;
						WeldHistory.BaseCount=UniversalCount;
						PowerGraph.BaseCount= UniversalCount;
						ColDistance.BaseCount=UniversalCount;
						VelocityGraph.BaseCount=UniversalCount;
						ForceGraph.BaseCount=UniversalCount;
						AmplitudeGraph.BaseCount=UniversalCount;
						FrequencyGraph.BaseCount=UniversalCount;
						if(!OnKeypadScreen_flag)
							Invalidate();
					}

				}
			
				DeleteDC(dlg.m_pd.hdc);
				dlg.~CPrintDialog();
				
			}
			else if(PrinterPresent != PRINTERNOTAVILABLE)
			{	
				PrinterPresent = PRINTERNOTAVILABLE;
				if(!OnKeypadScreen_flag)
					Invalidate();
			}
}



int CChildView::MakePrintWeldData(unsigned char *&data,int & length,int Difference)
{
	int NoOfPrintWeldData=0;
	/*Here check for all weld datas and add the one which is required */
	for(int i=Difference;i>=1;i--)
	{
		unsigned char *Tempdata=data;
		int TempLength=length;
		CWeldingData *TempPtr = new CWeldingData(i,Tempdata, TempLength,true);
		int CycleReceived = TempPtr->ReceivedUniversalCount+1-i;//= atoi(TempArray);
		if((CycleReceived==(Welddata.BaseCount+Welddata.PrintSampleValue))||((Welddata.PrintOnAlarmValue)&&(TempPtr->TextColour==Red)))
		{  
		   WeldDataPrintList.AddTail(TempPtr);
			if(CycleReceived==(Welddata.BaseCount+Welddata.PrintSampleValue))
			Welddata.BaseCount+=Welddata.PrintSampleValue;
			PrintInfoList.AddTail(WELDDATAONSAMPLEID);
			NoOfPrintWeldData++;
				if(WeldDataPrintList.GetCount()/*PrintWeldDataList.GetCount()*/)
				{
					CWeldingData * LastWeldObject=WeldDataPrintList.GetTail();/*PrintWeldDataList.GetTail()*/;
					if(LastWeldObject->Units!=TempPtr->Units)
               {
					 //  printf("\n ContinuePrinting true");
                  ContinuePrinting=true;
               }
				}
				else
            {
					//printf("\n ContinuePrinting false");
               ContinuePrinting=false;
            }
		
		}
		else
			delete TempPtr;
		
	}
	return NoOfPrintWeldData;
}


bool CChildView::MakeUSBWeldData(unsigned char *&data,int & length,int Difference)
{
	bool LatestObjectAdded =false;

	for(int i=Difference;i>=1;i--)
	{
		unsigned char *Tempdata=data;
		int TempLength=length;
		CHistoryData* USBObject;
		CWeldingData *TempPtr = new CWeldingData(i,Tempdata, TempLength,true);
		int CycleReceived = TempPtr->ReceivedUniversalCount+1-i;
		if((CycleReceived==(USBWelddata.BaseCount+USBWelddata.USBSampleValue))||((USBWelddata.USBOnAlarmValue)&&(TempPtr->TextColour==Red)))
		{ 
			unsigned char *Tempdata1=data;
			int TempLength1=length;
			USBObject = new CHistoryData(i,Tempdata1, TempLength1);

			if(CycleReceived==(USBWelddata.BaseCount+USBWelddata.USBSampleValue))
				USBWelddata.BaseCount+=USBWelddata.USBSampleValue;
			USBHistoryList.AddTail(USBObject);
			
			if(i==1)
         {
			//	printf("\n LatestObjectAdded true");
            LatestObjectAdded=true;
         }
			else
				USBGraphCountList.AddTail(0);
		}
		delete TempPtr;
	}
	
	return LatestObjectAdded;
}
		

bool CChildView::GetAlarmButton()
{
	CVgaMenu * menu,*AlarmPtr;
   menu=theApp.MenuPointer;
 
	if(AlarmCount)
	{	
	   CVgaMenuItem *AlarmObject=0;
		bool AlarmOnCalibration=false;
      if(AlarmMenuIdentifier!="")
      {
         if(theApp.menus.Lookup(AlarmMenuIdentifier, AlarmPtr))
         {
            AlarmObject = AlarmPtr->items.GetHead();
            CAlarmButton *ptr=(CAlarmButton*)AlarmObject;
            AlarmMenuName=ptr->MenuName;
            GlobalAlarmObject=AlarmObject;
            AlarmUpdateRequired=true;
          //  AlarmObject->SetText(GetAlarmString(AlarmObject));
          //  menu->items.AddTail(AlarmObject);
            CommandForAlarmButton=true;
				Invalidate();
            return true;	
         }
      }
	 
	}
	return false;
}

void CChildView::AddAlarmButtonInList()
{
   CVgaMenu * menu,*AlarmPtr;
   menu=theApp.MenuPointer;
	if(IsAlarmScreen||ScreenSetupFlag)
		return;
   
	CTypedPtrList<CPtrList, CVgaMenuItem *> TempDataList;
	POSITION pos = menu->items.GetHeadPosition();
	while(pos)
	{
	   CVgaMenuItem *Object = menu->items.GetNext(pos);
      if(Object->GetType() ==CVgaMenu::VGA_ALARMBUTTON)
		{
		   menu->items.RemoveHead();
      }
		else
		{
			TempDataList.AddTail(Object);
			menu->items.RemoveHead();
		}
	}
	
	POSITION pos2 = TempDataList.GetHeadPosition();
	while(pos2)
	{
		CVgaMenuItem *Obj = TempDataList.GetNext(pos2);
		menu->items.AddTail(Obj);
		
	}
	while(TempDataList.GetCount()) 
		 TempDataList.RemoveHead();
  
	
	CVgaMenuItem *AlarmObject=0;
   if(AlarmMenuIdentifier!="")
   {
      if(theApp.menus.Lookup(AlarmMenuIdentifier, AlarmPtr))
      {
       //  printf("\n Lokkup");
         AlarmObject = AlarmPtr->items.GetHead();
         CAlarmButton *ptr=(CAlarmButton*)AlarmObject;
         AlarmMenuName=ptr->MenuName;
         AlarmObject->SetText(GetAlarmString(AlarmObject));
         menu->items.AddTail(AlarmObject);
         CDC *pDC =GetDC();
		   AlarmObject->Draw(pDC);
		   ReleaseDC(pDC);
     }
   }
}

CString CChildView::GetAlarmString(CVgaMenuItem *ptr)
{
	 CAlarmButton *AlarmPtr=(CAlarmButton *)ptr;
    CString AlarmString= "** ";
	 
	 if(AlarmCount >9)
	 {
		 AlarmString+=(TCHAR)((AlarmCount/10)+48);
		 AlarmString+=(TCHAR)((AlarmCount%10)+48);
	 }
	 else
		 AlarmString+=(TCHAR)((AlarmCount)+48);

	if(AlarmCount==1)
	AlarmString+=AlarmPtr->Text1;/*StrAlarmMsg[Language_Index]*/
	else
	AlarmString+=AlarmPtr->Text2;/*StrAlarmMsgS[Language_Index]*/
	return AlarmString;
}

void CChildView::GetWeldDataIdArray(bool DeletePrevious)
{
	int length =ONE;
	unsigned char data1 = (char)WELDDATAID;
	unsigned char *data;// = (unsigned char *) &data2;
	CHostCommand* request = new CHostCommand(GetWeldSetupPrint_FunID, &data1, length);
	CHostCommand* response = app->SendPollingHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
		if(ch==ACK)
		{	
			int Counts=*data++;
        // printf("\n Counts=%d",Counts);
			length--;
			if(Counts>0)
			{
				if(DeletePrevious)
					delete []WeldDataIdArray;
				
				WeldDataIdArray = new int[Counts+1];
				WeldDataIdArray[0]=Counts;
				for(int ID=1;ID<=Counts;ID++)
				{
					WeldDataIdArray[ID]=*data++;
            //   printf("\n WeldDataIdArray[ID]=%d",WeldDataIdArray[ID]);
					length--;
				}
			}
		}
		delete response;
	}
}


void CChildView::GetGraphWeldDataIdArray(bool DeletePrevious)
{
	int length =ONE;
	unsigned char data1 = (char)GRAPHID;
	unsigned char *data;// = (unsigned char *) &data2;
	CHostCommand* request = new CHostCommand(GetWeldSetupPrint_FunID, &data1, length);
	CHostCommand* response = app->SendPollingHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
		if(ch==ACK)
		{
			int Counts=*data++; 
        // printf("\n Counts=%d",Counts);
			length--;
			if(Counts)
			{
				if(DeletePrevious)
					delete []GraphWeldDataIdArray;
				
				GraphWeldDataIdArray = new int[Counts+1];
				GraphWeldDataIdArray[0]=Counts;
				for(int ID=1;ID<=Counts;ID++)
				{
					GraphWeldDataIdArray[ID]=*data++;
			//		printf("\n GraphWeldDataIdArray[ID]=%d",GraphWeldDataIdArray[ID]);
               length--;
				}
			}
		}
		delete response;
	}
}

void CChildView::SendCommandForQualityWindow(int NoOfPreset)
{
   Presettrack=0;
   int NoOfTimes=0;
   int File_Size=0;
   ULARGE_INTEGER FreeBytesAvailable,TotalBytes,FreeBytes;
	CString str=(L"\\Disk");
	int  present =GetDiskFreeSpaceEx(str,&FreeBytesAvailable,&TotalBytes,&FreeBytes);//Check For Disk free Space 
	__int64 Available=FreeBytesAvailable.HighPart; 
	Available= FreeBytesAvailable.LowPart |(Available<<32) ;
   if(NoOfPreset==MAX_PRESET)
       File_Size=((MAX_PRESET)*(SIZEOFVQSPRESETDATA) +(SIZEOFVQSSYSCON));//Size of File Need To Be Written to Disk
   else 
       File_Size=(SIZEOFVQSPRESETDATA) +(SIZEOFVQSSYSCON);
      	   
   if(Available>File_Size)
   {
      CString Path;
		#ifndef _WIN32_WCE
			Path = "c:\\VQSData.bin";
		#else
			Path = _T("Disk\\VQSData.bin");
		#endif
      CFile f;
      CFileException e;
     
	   for(int Num =0;Num <(NoOfPreset);Num++)
	   {
		   int length=1;//length of pointer to be send to 332
		   unsigned char data1=(char)Num;//Sending preset number
		   unsigned char * data = (unsigned char *) &data1;
		   
		   CHostCommand * request = new CHostCommand(GetQualityLimits_FunId,data,length);
		   CHostCommand * response = app->SendUiHostCommand(request);
		   if(response)
		   {
			   char ch=CHostCommand::AckNak();
			   unsigned char *data = response->GetData();
			   length = response->GetDataLength();
            if(ch==ACK)
			   {
               
               if( f.Open( Path,CFile::modeCreate | CFile::modeNoTruncate|CFile::modeReadWrite , &e ) )
				   {
					   f.SeekToBegin();
					   if(NoOfTimes>=1)
                  {
                     int j=SIZEOFVQSSYSCON;
                     while(j--)
                     {
                        *data++;     // Ignoring Systen Config. Bytes While Write Preset greater than 0
                     }
                     length-=(SIZEOFVQSSYSCON);
                  }
                  unsigned char *c =new unsigned char[length];
						f.Seek(Presettrack, CFile::begin);
						for(int k=0;k<length;k++)
                  {
                     c[k]=*data++;
                  }
						
						f.Write(c,length);
						Presettrack+=length;
                  NoOfTimes++;
						delete []c;
					   f.Close();
					}
				   delete response; 
			   }
			   else
			   {
               free(response);
			      SendCommandForQualityWindow(MaxPreset);
               return;
               //CChildView::ErrorBeep();	
			   }
		   }
		   else
		   {
			   free(response);
			   SendCommandForQualityWindow(MaxPreset);
		   }
	   }
   }
  

}

void CChildView::SaveVQSData()   // Copy Preset 0 VQS Limits Data to Preset Position being Saved
{
	CFile f;
	CString Path;
	CFileException e;
	#ifndef _WIN32_WCE
	Path = "c:\\VQSData.bin";
	#else
	Path = _T("Disk\\VQSData.bin");
	#endif
	if( f.Open( Path,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite , &e ) )
	{
		int  size= SIZEOFVQSPRESETDATA;
		int StartingPointer =0;
		static char ch[SIZEOFVQSPRESETDATA] ;
		f.SeekToBegin();
		int FileSize = f.GetLength();
		StartingPointer =SIZEOFVQSSYSCON;
		f.Seek(StartingPointer, CFile::begin );
		int t=f.Read(&ch[0],SIZEOFVQSPRESETDATA); //Read Preset 0 VQS Limits Data
		for(int PresetNum=1;PresetNum<(MAX_PRESET);PresetNum++)
		{
			if(PresetNum==CurrentPresetNum)
			{
				StartingPointer =((PresetNum)* SIZEOFVQSPRESETDATA + (SIZEOFVQSSYSCON));
				f.Seek(StartingPointer, CFile::begin );
				f.Write(&ch[0],SIZEOFVQSPRESETDATA);// Write to Preset Position being Saved
			}
			
		}
		f.Close();
	}
}
void CChildView::PrintVQSLimits()
{
  		int FUN_ID=GetWeldSetupPrint_FunID; 
		int length=ONE;
	   int PAGE=VQSLIMITPAGE;
		unsigned char* data = (unsigned char *) &PAGE;
		CCommPort::OnPollingTime=false;
		CHostCommand * request = new CHostCommand(FUN_ID, data, length);
		CHostCommand * response = app->SendPollingHostCommand(request);
		if(response)
		{	
			char ch=CHostCommand::AckNak();
			data = response->GetData();
			length = response->GetDataLength();
			if(ch==ACK)
			while (length>ZERO)
			{	
				int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
           // printf("\n ID=%d",ID);
            CPrintText * object = new CPrintText(data, length,false,ID);
				PrintObjectList.AddTail(object);
			}
			delete response;
		}
	
		PrintInfoList.AddTail(SETUPID);
		WaitForPrintData.SetEvent();
}

/*****************************************************************************/
/*  Function Set the Rectangle for button according to the type and count.   */
/*****************************************************************************/

void CChildView::RecalculateMenuItemsLayout(int height,CVgaMenu * CurrMenuLst)
{
	CurrMenuList=CurrMenuLst;
	int VGAButtonPageNo = 1;
	int items = 0;
   Total_Objects=0;
	int left_coordinate;
   int TotalObjectDraw=0;
	bool radiomenu=false;
	int	Button_Gap=0;
	int ButtonHeight=BUTTON_HEIGHT;
	int BUTTON_WIDTH= MENU_BUTTON_WIDTH;
	Total_Text_Objects=0;
	SysInfoScreen=false;
	
   if(listbuild == false)
		return;
   
   POSITION pos = CurrMenuList->items.GetHeadPosition();
	CVgaMenuItem * object = CurrMenuList->items.GetNext(pos);
	CurrMenuList->items.GetNext(pos);
	
	
   pos = CurrMenuList->items.GetHeadPosition();
	object = CurrMenuList->items.GetNext(pos);
	left_coordinate=LEFT_COORDINATE_1_BUTTON;
	int top_coordinate = TOP_COORDINATE_1_BUTTON;
	int count=0;
	int customButtonHgap = 0;
	int customButtonVgap = 0;
	int customButtonWidth = 0;
	int customButtonHeight = 0;
   if(object->GetType()==CVgaMenu::TITLE)
   {
      CVgaTitle *title=(CVgaTitle *)object; 
      CChildView::RowPerPage=title->rows;
    //  printf("\n CChildView::RowPerPage=%d",CChildView::RowPerPage);
      CChildView::ColumnPerPage=title->columns;
     // printf("\n CChildView::ColumnPerPage=%d",CChildView::ColumnPerPage);
      CChildView::ButtonType=title->ButtonTypes;
      CChildView::ExitButtonFlag=title->ExitFlag;
      CChildView::SaveButtonFlag=title->SaveFlag;
   }
  
   AddSaveExit(CurrMenuList);
   POSITION pos1 = CurrMenuList->items.GetHeadPosition();
   while(pos1)
	{
		object = CurrMenuList->items.GetNext(pos1);
	   if(object->IsDraw == true)
		{
		   int type = object->GetType();
         if(type ==VGAHistoryGraphObject)
            return;
         if (((type > CVgaMenu::TITLE) && (type < CVgaMenu::MENU_END))||
            ((type==CVgaMenu::VGA_Button_OBJECT)||((type>CVgaMenu::MENU_END)
            &&(type<=CVgaMenu::COLORSETUP_ID))))
			   TotalObjectDraw++;
		}
   }
//   printf("\n TotalObjectDraw=%d",TotalObjectDraw);
   if(TotalObjectDraw<=MaxItemIn1ColMenu)
   {
      CChildView::RowPerPage=MaxItemIn1ColMenu;
      CChildView::ColumnPerPage=1;
   }
	GetButtonShape(customButtonHgap,customButtonVgap,customButtonWidth,customButtonHeight);
	
   int TempPageNum=1;
	while(pos)
	{
		object = CurrMenuList->items.GetNext(pos);
		if(object->IsDraw == true)
		{
         int type = object->GetType();
         if(type!=CVgaMenu::TITLE)
         {
            if(type==CVgaMenu::TEXT)
			      Total_Text_Objects++;
            if (((type > CVgaMenu::TITLE) && (type < CVgaMenu::MENU_END))||((type==CVgaMenu::VGA_Button_OBJECT)
               /*&&(object->GetRect().BottomRight().y==0)*/))
			      //	||((type >VGA_BUTTON_START )&&(object->GetRect().BottomRight().y==0)))
			      items++;

		      Total_Objects=items;
	         if (CChildView::ColumnPerPage ==1 )
		         left_coordinate+=LCOORDINATE_COL1_FACTOR;
	         
	         if(CChildView::ButtonType == RADIOTYPE)
               left_coordinate+=LCOOR_RADIO_FACTOR;
	         
            if((type==0)||(type==1)||((type==CVgaMenu::VGA_VGAEXITBUTTON)||(type==CVgaMenu::VGA_VGASAVEBUTTON)||(type==CVgaMenu::VGA_ALARMBUTTON)/*(object->PSType == CVgaMenu::VGA_Button_OBJECT)*/
	         &&(object->GetRect().BottomRight().y!=0)))
	         {
		         count++;
		         object->SetPageNum(CVgaMenuItem::PAGEALL);
	         }
	         else if(type == CVgaMenu::VGATableObject)
	         {
		         count++;
		         object->SetPageNum(CVgaMenuItem::PAGEALL);
	         }
            else
	         {
      
               if((object->PSType != CVgaMenu::VGA_Button_OBJECT))
               {
                  object->SetRect(CRect(left_coordinate+XOFFSET,
									         top_coordinate+YOFFSET, 
									         left_coordinate +customButtonWidth+XOFFSET , 
									         top_coordinate + customButtonHeight+YOFFSET));
               }
               else if((object->PSType == CVgaMenu::VGA_Button_OBJECT))//&&(object->GetRect().BottomRight().y==0))
               {
                   CVgaButton *ptr=(CVgaButton *)object;
		          if(ptr->Rect.BottomRight().y==0 )
			         object->SetRect(CRect(left_coordinate+XOFFSET,
									         top_coordinate+YOFFSET, 
									         left_coordinate +customButtonWidth+XOFFSET , 
									         top_coordinate + customButtonHeight+YOFFSET));
               }
               count++;
		         if(count!=(RowPerPage*ColumnPerPage*TempPageNum))
		         {
	         
			         if(count%ColumnPerPage !=0)
			         {
				         left_coordinate+=(customButtonWidth+customButtonHgap);

			         }
			         else
			         {
				         left_coordinate=LEFT_COORDINATE_1_BUTTON;
				         top_coordinate += (customButtonHeight+customButtonVgap);
			         }
			         object->SetPageNum(TempPageNum);
		         }
		         else
		         {
			         object->SetPageNum(TempPageNum);
			         left_coordinate=LEFT_COORDINATE_1_BUTTON;
			         top_coordinate = TOP_COORDINATE_1_BUTTON;
			         TempPageNum++;
		         }
	         }
	      }
      }
   }
}

/**************************************************************/
/*This Function Checks The row and coloumn Number and Gives   */
/*Buttos Size Acorrdings to it.								  */
/**************************************************************/
void CChildView::GetButtonShape(int &Hgap, int &Vgap, int &Width, int &Height)
{	
   int rows=CChildView::RowPerPage;
	int coloumns=CChildView::ColumnPerPage;
	int buttontype=CChildView::ButtonType;
  	switch(rows)
	{
	case 1: Vgap = BUTTON_GAP;
			Height = BUTTON_HEIGHT;
			break;
	case 2: Vgap = BUTTON_GAP;
			Height = BUTTON_HEIGHT;
			break;
	case 3: Vgap = BUTTON_GAP;
			Height = BUTTON_HEIGHT;
			break;
	case 4: Vgap = BUTTON_GAP;
			Height = BUTTON_HEIGHT;
			break;
	case 5: Vgap = BUTTON_GAP;
			Height = BUTTON_HEIGHT;
			break;
	case 6: Vgap = BUTTON_GAP-14;
			Height = BUTTON_HEIGHT;
			break;
	case 7: Vgap = BUTTON_GAP-14;
			Height = BUTTON_HEIGHT-10;
			break;
	case 8: Vgap = BUTTON_GAP-14;
			Height = BUTTON_HEIGHT-18;
			break;
	case 9: Vgap = BUTTON_GAP-25;
			Height = BUTTON_HEIGHT-25;
			break;
	case 10: Vgap = BUTTON_GAP-25;
			Height = BUTTON_HEIGHT-25;
			break;
	default : ;
	}
	switch(coloumns)
	{
	case 1:
		Hgap = 70;
		Width = MENU_BUTTON_WIDTH+90;
		break;
	case 2:
		Hgap = 135;
		Width = MENU_BUTTON_WIDTH;
		break;
	case 3:
		Hgap = 25;
		Width = MEDIUM_BUTTON_WIDTH-10;
		break;
	case 4: Hgap = 40;
		    Width = MEDIUM_BUTTON_WIDTH-60;//120;
		break;
	case 5: Hgap = 20;
			Width = MEDIUM_BUTTON_WIDTH-80;//100;
		break;
	case 6: Hgap = 25;
			Width = MEDIUM_BUTTON_WIDTH-110;//70;
		break;
	default : ;
	}
	if(buttontype !=DEFAULT)
	switch(buttontype)
	{
	case LARGE:
		Height=BUTTON_HEIGHT;
		Width =  MENU_BUTTON_WIDTH; 
		break;
	case NORMAL:
		Height = BUTTON_HEIGHT;
		 Width = MEDIUM_BUTTON_WIDTH;
		 break;
	case SMALL:
		Height = BUTTON_HEIGHT;
		Width = 70;
		if(coloumns ==5)
		Hgap=55;
		break;
	case TEXTTYPE:
		Height = BUTTON_HEIGHT-15;
		 Width = MEDIUM_BUTTON_WIDTH-20;
       break;
   case RADIOTYPE:
      Height = BUTTON_HEIGHT;
		 Width = MEDIUM_BUTTON_WIDTH;
       Hgap = 70;
		 break;
	default : ;
	}


}

bool CChildView::CheckConditions(CVgaMenuItem *item) const 
{
   POSITION pos = item->conditions.GetHeadPosition();
	while (pos)
	{
		CCondition * condition = item->conditions.GetNext(pos);
		if (!condition->Evaluate(item))
      {
         return false;
      }
	}
   return true;
}

void CChildView::ModifyObjectList(CVgaMenu * CurrMenuLst)
{ 
//   printf("\n ModifyObjectList");
	listbuild = false;
   CVgaMenuItem *AlarmPtr=0;
	CurrMenuList = CurrMenuLst;
   if(CurrMenuList !=NULL)
	{
      if(CurrMenuLst->items.GetCount()>0)
		{
			POSITION pos = CurrMenuList->items.GetHeadPosition();
			CVgaMenuItem * object = CurrMenuList->items.GetHead();
         //int type=object->GetType();
			while(pos)
			{
           // type=object->GetType();
				if(CheckConditions(object)  == true)
				{
				   //printf("\n true");
               object->IsDraw = true;
            }
				else
				{
				   //printf("\n false"); 
               object->IsDraw = false;
              //  object->rect.SetRectEmpty();
            }	
            /*if(type ==VGAHistoryGraphObject)
                object->IsDraw = true;*/
            object=CurrMenuList->items.GetNext(pos);
			}
		}
	}
   listbuild = true;
   if((AlarmCount==0))
   {
      CTypedPtrList<CPtrList, CVgaMenuItem *> TempDataList;
	   POSITION pos = CurrMenuList->items.GetHeadPosition();
		while(pos)
		{
		
         CVgaMenuItem *Object = CurrMenuList->items.GetNext(pos);
         if(Object->GetType() == /*CScreenObject::*/CVgaMenu::VGA_ALARMBUTTON)
			{
				 CurrMenuList->items.RemoveHead();
         }
			else
			{
				TempDataList.AddTail(Object);
				CurrMenuList->items.RemoveHead();
			}
		}
		
		POSITION pos2 = TempDataList.GetHeadPosition();
		while(pos2)
		{
			CVgaMenuItem *Obj = TempDataList.GetNext(pos2);
			CurrMenuList->items.AddTail(Obj);
			
		}
	
		while(TempDataList.GetCount()) 
			 TempDataList.RemoveHead();
   }
//   printf("\n ModifyObjectList End");
   RecalculateMenuItemsLayout(MAXSCRNButton_Height,CurrMenuList);
 //  printf("\n After RecalculateMenuItemsLayout");
}


/**************************************************************/
/*This Function Checks Save and/or Exit Button Flag from Title*/
/*Object and sets rect for Those Buttons.					  */
/**************************************************************/
void CChildView::AddSaveExit(CVgaMenu * CurrMenuLst)
{
	if(ExitButtonFlag)
	{
		CVgaMenuItem *object;
	//	object = new CVGAButtons(exit);
      object=new CVgaButton(Str_Exit,220,390,310,430,"");
      if(SaveButtonFlag)
      {
         object->SetRect(ExitWithSaveButtonRect);
      }
		else
      {
         object->SetRect(ExitButtonRect);
      }
      object->IsDraw=true;
		object->SetType(CVgaMenu::VGA_VGAEXITBUTTON);
      object->PSType=CVgaMenu::VGA_Button_OBJECT;
		CurrMenuLst->items.AddTail(object);
	}
	if(SaveButtonFlag)
	{
			CVgaMenuItem *object;
			object=new CVgaButton(Str_Save,330,390,420,430,"HandleVGASaveButton");
           object->IsDraw=true;
			object->SetType(CVgaMenu::VGA_VGASAVEBUTTON);
         object->PSType=CVgaMenu::VGA_Button_OBJECT;
			object->SetRect(SaveButtonRect);
         object->AccessLevel=MAINTAINENCE;
			CurrMenuLst->items.AddTail(object);
	}
}

int CChildView::Convert_Char_To_Int(unsigned char *&data, int &length, int Bytes)
{
	union {
			int i;
			char c[IntegerLength];
			} u;
	if(Bytes!=0)
	for (int k = 0; k < Bytes; k++)
	{
		u.c[k] = 0;
	}
	for (int j = Bytes; j < IntegerLength; j++)
	{
		u.c[j] =*data++;
		length--;
	}
   //TRACE(_T("\n **Co-ordinates are** %d \n "),ntohl(u.i ));	
	return ((u.i ));
}

float CChildView::Convert_Char_To_Float(unsigned char *&data, int &length, int Bytes)
{
	union {
			float i;
			char c[IntegerLength];
			} u;
	if(Bytes!=0)
	for (int k = 0; k < Bytes; k++)
	{
		u.c[k] = 0;
	}
	for (int j = Bytes; j < IntegerLength; j++)
	{
		u.c[j] =*data++;
		length--;
	}
   //TRACE(_T("\n **Co-ordinates are** %d \n "),ntohl(u.i ));	
	return ((u.i ));
}

void CChildView::SetDimension(CVgaMenuItem *item,int count)
{
   CVgaVariable *ptr1;
   /*CText*/CRadioMenu *ptr2;
   if(item->GetType() == CVgaMenu::VARIABLE)
      ptr1=(CVgaVariable *)item;
   else 
      ptr2= (CRadioMenu *)item;
   int X1=0,Y1=0,X2=0,Y2=0;
   switch(count)
   {
   case 0:
      {
         X1=VARIABLE_COORDINATE1;
         Y1=VARIABLE_COORDINATE2;
         X2=VARIABLE_COORDINATE1+VARIABLE_WIDTH;//VARIABLE_COORDINATE1;
         Y2=VARIABLE_COORDINATE2+LEFT_COORDINATE_1_BUTTON;//VARIABLE_COORDINATE2;
      }
      break;
   case 1:
      {
         X1=VARIABLE_COORDINATE4;
         Y1=VARIABLE_COORDINATE2;
         X2=VARIABLE_COORDINATE4+VARIABLE_WIDTH;//VARIABLE_COORDINATE4;
         Y2=VARIABLE_COORDINATE2+LEFT_COORDINATE_1_BUTTON;//VARIABLE_COORDINATE2;
      }
      break;
   case 2:
      {
         X1=VARIABLE_COORDINATE1;
         Y1=VARIABLE_COORDINATE3;
         X2=VARIABLE_COORDINATE1+VARIABLE_WIDTH;//VARIABLE_COORDINATE1;
         Y2=VARIABLE_COORDINATE3+LEFT_COORDINATE_1_BUTTON;//VARIABLE_COORDINATE3;
      }
      break;
   case 3:
      {
         X1=VARIABLE_COORDINATE4;
         Y1=VARIABLE_COORDINATE3;
         X2=VARIABLE_COORDINATE4+VARIABLE_WIDTH;//VARIABLE_COORDINATE4;
         Y2=VARIABLE_COORDINATE3+LEFT_COORDINATE_1_BUTTON;//VARIABLE_COORDINATE3;
      }
      break;
   case 4:
      {
         X1=VARIABLE_COORDINATE1;
         Y1=VARIABLE_COORDINATE5;
         X2=VARIABLE_COORDINATE1+VARIABLE_WIDTH;//VARIABLE_COORDINATE1;
         Y2=VARIABLE_COORDINATE5+LEFT_COORDINATE_1_BUTTON;//VARIABLE_COORDINATE5;
      }
      break;
   case 5:
      {
         X1=VARIABLE_COORDINATE4;
         Y1=VARIABLE_COORDINATE5;
         X2=VARIABLE_COORDINATE4+VARIABLE_WIDTH;//VARIABLE_COORDINATE4;
         Y2=VARIABLE_COORDINATE5+LEFT_COORDINATE_1_BUTTON;//VARIABLE_COORDINATE5;
      }
      break;
   }
   if(item->GetType() == CVgaMenu::VARIABLE)
      ptr1->SetRect (CRect(X1,Y1,X2,Y2));
   else 
      ptr2->SetRect (CRect(X1,Y1,X2,Y2));      
}

bool CChildView::ReadStartUpVersionString()
{
   bool success=true;
   CFile f;    
	CFileException e;
	TCHAR* pFileName;
	#ifndef _WIN32_WCE
	pFileName = _T("c:\\Startup.txt");
	#else
	pFileName = _T("Disk\\Startup.txt");
	#endif
	
   if( !f.Open( pFileName,CFile::modeRead , &e ) )
	{
		#ifdef _DEBUG
		if(e.m_cause==CFileException::generic)
			TRACE("\n !! GENERIC");
		else if(e.m_cause==CFileException::badPath   )
			TRACE("\n !! bad path");
		else if(e.m_cause==CFileException::tooManyOpenFiles    )
			TRACE("\n !! too many files open");
		else if(e.m_cause==CFileException::fileNotFound )
			TRACE("\n !! file not found");
		else if(e.m_cause==CFileException::accessDenied       )
			TRACE("\n !! access denied");
		else if(e.m_cause==CFileException::diskFull      )
			TRACE("\n !! disc full");
		else if(e.m_cause==CFileException::invalidFile   )
			TRACE("\n !! invalid file");
		afxDump << "File could not be opened " << e.m_cause << "\n";
		#endif

     success=false;
   }
	else
	{
      char Comma =',';
      int Temprorylen=0;
      int FileSize = f.GetLength();
      int SysFileSize=FileSize;
      unsigned char *data=new unsigned char[FileSize];
      f.Read(data,FileSize);
      
      LPTSTR p = StartUpVerFileName.GetBuffer(FileSize);
      for(int count=0;count<FileSize;count++)
      {
         p[count]=data[count];
      }
      StartUpVerFileName.ReleaseBuffer( );
      int index = StartUpVerFileName.Find('=');
      StartUpVerFileName=StartUpVerFileName.Right((FileSize-index)-1);
      if((StartUpVerFileName.Find( '.' ) == -1) 
         || (StartUpVerFileName.GetLength()>MAXSYSFILE_LEN))
      {
         delete []data;
		   f.Close();
         success=false;
      }
      else
      {
         delete []data;
		   f.Close();
         success=true;
      }
   }
   return success;
}

bool CChildView::ReadSystemVersionString()
{
   bool success=true;
   CFile f;    
	CFileException e;
	TCHAR* pFileName;
	#ifndef _WIN32_WCE
	pFileName = _T("c:\\ReleaseVersion.txt");
	#else
	pFileName = _T("Disk\\ReleaseVersion.txt");
	#endif
	
   if( !f.Open( pFileName,CFile::modeRead , &e ) )
	{
		
      #ifdef _DEBUG
		if(e.m_cause==CFileException::generic)
			TRACE("\n !! GENERIC");
		else if(e.m_cause==CFileException::badPath   )
			TRACE("\n !! bad path");
		else if(e.m_cause==CFileException::tooManyOpenFiles    )
			TRACE("\n !! too many files open");
		else if(e.m_cause==CFileException::fileNotFound )
			TRACE("\n !! file not found");
		else if(e.m_cause==CFileException::accessDenied       )
			TRACE("\n !! access denied");
		else if(e.m_cause==CFileException::diskFull      )
			TRACE("\n !! disc full");
		else if(e.m_cause==CFileException::invalidFile   )
			TRACE("\n !! invalid file");
		afxDump << "File could not be opened " << e.m_cause << "\n";
		#endif

      success=false;
   }
	else
	{
      char Comma =',';
      int Temprorylen=0;
      int FileSize = f.GetLength();
      int SysFileSize=FileSize;
      unsigned char *data=new unsigned char[FileSize];
      f.Read(data,FileSize);
      LPTSTR p = SystemVerFileName.GetBuffer(FileSize);
      for(int count=0;count<FileSize;count++)
      {
         p[count]=data[count];
      }

      SystemVerFileName.ReleaseBuffer( );
      int index = SystemVerFileName.Find('=');
      SystemVerFileName=SystemVerFileName.Right((FileSize-index)-1);
      if((SystemVerFileName.Find( '.' ) == -1)
         || (SystemVerFileName.GetLength()>MAXSYSFILE_LEN))
      {
         delete []data;
		   f.Close();
         success=false;
      }
      else
      {
         delete []data;
		   f.Close();
         success=true;
      }
   }
   return success;
}

void CChildView::CheckUSBSpaceAvailable()
{
   int File_Size=0;
   ULARGE_INTEGER FreeBytesAvailable,TotalBytes,FreeBytes;
	CString str=(L"\\USBDisk");
	int  present = GetDiskFreeSpaceEx(str,&FreeBytesAvailable,&TotalBytes,&FreeBytes);//Check For Disk free Space 
	__int64 AvailableUSBSize=FreeBytesAvailable.HighPart; 
	AvailableUSBSize= FreeBytesAvailable.LowPart |(AvailableUSBSize<<32) ;

   if(AvailableUSBSize < MINUSBDATASIZE)
   {
      USBFullAlarm = true;
   }
   else
   {
      USBFullAlarm = false;
   }
}
