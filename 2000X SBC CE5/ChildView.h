/* $Header:   D:/databases/VMdb/archives/2000 RVTS/ChildView.h_v   1.36.1.14.1.3.2.0   Oct 23 2017 15:51:44   RCHAPA  $ */
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
  1.5       05/19/05	Aare        Added complete revision header.
  1.6		   05/23/05	Bwadia		Added DrawFirstScreen Function.
  1.7		   07/25/05	BWadia		Added SendPollingCommand And related Functions.
  1.8		   09/19/05	BWadia		Added Functions For Printing
  1.9		   09/20/05	BWadia		Added #defines
  1.10		10/14/05	BWadia		Added Functions For USB Storage.
  1.11		10/24/05	BWadia		Added Functions GetAveragePowerGraph() and ExitProgram() for Power 
									      Match Compare and Main menu Exit button.
  1.12		10/28/05	BWadia		Added CurrentSequencePreset variable and define Rect for Back,Next and Exit buttons.
  1.13		10/28/05	BWadia		Changed define MaxCol_1_Col_Menu value 5 to 4
  1.14		11/08/05	BWadia		Changed define PARAMWIDTH From 70 to 69 so that weld data could fit on page
  1.15		12/07/05	BWadia		Modified for Tracker issue 3978,4005,4035.
  1.16		10/20/05	BWadia		Modified for Tracker issue 4029,3976,4004,4015,4034
  1.17		01/13/06	BWadia		Dummy Check In.
  1.18		01/13/06	BWadia		Modified for tracker issue 3957.
  1.19		02/07/06	BWadia		Added functions GetWeldDataIdArray() and GetGraphWeldDataIdArray
  1.20		02/14/06	BWadia		Added USBGlobalFlag
  1.21		02/22/06	BWadia		Added USBMutex 
  1.22		03/22/06	YGupta		Modified for Tracker issue 4099.
  1.23		04/13/06	YGupta		Added LargeWaitingTime variable.
  1.24		04/24/06	YGupta		Modified for  HornScan.
  1.25		05/26/06	YGupta		Added EStopOnHornDown and PollingTimeOnMsgScrn variables.
  1.26		09/18/06	BSahu		   Changed Define values for VGAHistoryGraphObject and VGAHistoryObject.
  1.27		12/13/06	BSahu		   Added Define ALARMBUTTONRECT_RE	For Alarm Rect Redraw.
  1.28		03/12/07	BSahu		   Added Function DisplayWeldIsGoingOnMessage().
  1.29      03/27/07 BSahu       Added SendCommandForQualityWindow() & SaveVQSData() For VQS Application
  1.30      03/30/07 BSahu       Added Declaration For PrintVQSLimits().
  1.31      04/05/07 BSahu       Removed Unused varialbe Declartions.
  1.32      04/12/07 BSahu       Added Varialbe Declartions.
  1.33      04/16/07 BSahu       Modified USBPreset() to Public
  1.34      05/04/07 BSahu       Added defines(Tracker Issue- 4109).
  1.35      05/23/07 BSahu       Added defines for print button on RunScreen
  1.36      05/28/07 BSahu       Modified GRAPHTEXTSTARTYCORDINATE for Tracker issue 4139
  1.36.1.0  10/23/07 PDwivedi    Added changes for Multilang Support. 
  1.36.1.1  10/23/07 PDwivedi    Remove Header "MyCombo.h" for Multi Language Support.
  1.36.1.2  01/11/08 PDwivedi    Added Variable Declartions.  
  1.36.1.3  04/04/08 PDwivedi	   Added Variables Declarations for MultiLang Support.
  1.36.1.4  04/14/08 PDwivedi	   Added Declarations & Removed Unused Variables for MultiLang Support.
  1.36.1.5  06/06/08 PDwivedi    Added Declarations for new screen.
  1.36.1.6  08/01/08 PDwivedi    Added Declarations for USB & Printing.
  1.36.1.7  08/08/08 PDwivedi    Final Code Clean up.
  1.36.1.8  08/26/08 PDwivedi    Added new Member for Save & Exit Strings.
  1.36.1.9  09/02/08 PDwivedi    Added new Member for Series & Parallel Strings.
  1.36.1.10 09/09/08 PDwivedi    Added new Member for Tracker issues.
  1.36.1.11 09/12/08 PDwivedi    Added changes for Tracker issues of round 2 testing for version LangTestJ.
  1.36.1.12 09/24/08 PDwivedi    Added new members for SetupMenu & Sequencing Menu pointer.
  1.36.1.13 11/06/09 PDwivedi    Added changes for showing String number on RunScreen .
  1.36.1.14 11/18/09 PDwivedi    Added changes for Ethernet CleanUp and faster serial communication.
  1.36.1.15 10/13/10 PDwivedi    Added new Member like StartUpVerFileName & SystemVerFileName.
  1.36.1.16 12/28/10 PDwivedi    Added new member CurrentFilepath to store Weld Data. 
  1.62.1.17 02/28/11 PDwivedi    Added changes for USB Memory Full Alarm.
  1.62.1.18 03/08/11 PDwivedi    Added changes for USB Memory Full Alarm(increase minimum USB space).

*/

// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__04D2A820_3DAF_4495_A8E2_35B717D209D3__INCLUDED_)
#define AFX_CHILDVIEW_H__04D2A820_3DAF_4495_A8E2_35B717D209D3__INCLUDED_

#include "ScreenKeypad.h"
#include "VgaDrawGraph.h"
#include "HostCommand.h"
#include "PrintText.h"
#include "USBFolder.h"
#include "HistoryData.h"

#ifndef _WIN32_WCE
#define ERRORBEEP Beep(5000,100) 
#else
#define ERRORBEEP 
#endif

#define COLOR_NONE		-1
#define Black_DEFAULT	0
#define Black			1
#define Blue			2
#define Red				3
#define Green			4
#define Brown			5
#define Magenta		6
#define Cyan			7	
#define Dark_Gray		8
#define Gray			9
#define Yellow			10		
#define White			11

#define MENUENTRY_PER_PAGE    3
#define CORDLENGTH            2
#define AlphaEntryTimer		   1
#define Pollingtimer		      2
#define BottomHalfTimer		   3
#define MessageScreenTimer	   4
#define PasswordTimer		   5
#define PrinterStatusTimer    6
#define ERROR_MESSAGE_TIMER	7
#define USBSTATUSTIMER		   8
#define USBSTATUSTIMER1		   11
#define USBMEMDETECTTIMER		12

#define GETPRINTINGPARAMTIMER	9
#define LanguageSelectionTimer 10  
#define PollingTime			200
#define PrinterStatusTime	1000
#define USBSTATUSTIME		1000
#define MESSAGESCRNTIME		1000
#define USBSMEMDETECTTIME  500

#define Page_No_Rect CRect(500,0,640,40)
#define VGA_Rect CRect(0 + XOFFSET, 0 + XOFFSET, 640 + XOFFSET, 480 + YOFFSET)
#define MESSAGESCRNRECT CRect(120,120,	520,360)
#define MESSAGESCRN_BLACKRECT CRect(119,119,521,361)
#define MAXSCRNButton_Height				380
#define MaxItemIn1ColMenu				   4
#define REDUCED_BUTTON_WIDTH			   170
#define MENU_BUTTON_WIDTH				   210
#define BUTTON_HEIGHT					   40
#define BUTTON_HEIGHT_Text				   30
#define MaxItems_PerPage				   8
#define left_coordinate_Radio			   100
#define left_coordinate_Not_Radio		26
#define left_coordinate_ItemIn1ColMenu	220
#define left_coordinate_2Col_Not_Radio	336
#define left_coordinate_2Col_Radio		360
#define top_coordinate_1_Button			60
#define Max_Text_1_Coloum				   10
#define BUTTON_GAP						   34
#define Y_CORDINATE_BACK_NEXT			   390
#define X_CORDINATE_BACK_NEXT			   530
#define BUTTON_WIDTH_BACK_NEXT			90
#define BUTTON_GAP_BACK_NEXT			   20
#define MAX_PSPRESET					      16
#define NextButtonRect	CRect(X_CORDINATE_BACK_NEXT,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define BackButtonRect CRect(20,Y_CORDINATE_BACK_NEXT,BUTTON_WIDTH_BACK_NEXT+20,BUTTON_HEIGHT+Y_CORDINATE_BACK_NEXT)
#define ExitButtonRect CRect(260,Y_CORDINATE_BACK_NEXT,260+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define ExitWithSaveButtonRect CRect(220,Y_CORDINATE_BACK_NEXT,220+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define SaveButtonRect CRect(330,Y_CORDINATE_BACK_NEXT,330+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)

#define MAINMENU						   0
#define SCREENSETUPMENU					1
#define COLORSETUP						2
#define FOLDERHIERARCHYONE				3
#define FOLDERHIERARCHYTWO				4
#define FOLDERHIERARCHYTHREE			5
#define FOLDERHIERARCHYFOUR			6
#define VGAHistoryObject				33
#define VGAHistoryGraphObject			37
#define USBPRESETSCRN					9
#define VIEWPRESET						10
#define HISTORYGRAPHSCREEN			   11
#define USBPRESETFOLDER				   12
#define HSCOMPAREGRAPHSCRN				13
#define VGAPSHISTORY					   14
#define VIEWCURRENTPRESET				15
#define USBHISTORY                  13

#define PSNAMELENGTH					   11


#define IntegerLength					4
#define PRINTERNOTAVILABLE				0
#define PRINTERONLINE					1

/* defines for screen setup*/
#define MAX_VGA_Y_VALUE					480
#define MAX_VGA_X_VALUE					640
#define ActualCalibCordinate_Xa		45
#define ActualCalibCordinate_Ya		433
#define WELD_PROCESS_ERROR	   		0x8001	

#define SETUPID							0
#define GRAPHLISTSINGLEGRAPHID		1
#define GRAPHLISTDUALGRAPHID			2
#define GRAPHLISTTHREEGRAPHID			3
#define GRAPHLISTFOURGRAPHID			4
#define PRINTLISTGRAPHID				5
#define POWERGRAPHID					   6
#define COLDISTANCEID					7
#define VELOCITYGRAPHID					8
#define FORCEGRAPHID					   9
#define AMPLITUDEGRAPHID				10
#define FREQUENCYGRAPHID				11
#define WELDHISTORYID					12
#define WELDDATAONSAMPLEID				13
#define WELDDATAPRINTNOWID				14
#define	SCREENGRAPHS					15
#define	DUPSPRESET						16
#define	PRINTTABLEID					17
#define HORNSCANID						18
#define HSCGRAPHONE						19
#define HSCGRAPHTWO						20
#define HSCGRAPHTHREE					21
#define	HSCGRAPHFOUR					22

#define PRINTSEQUENCE					23 
#define PRINT_HISTORY_DATA          24

#define PARAMETERSTARTXCORD			75
#define PARAMETERSTARTYCORD			250
#define PRINTWELDSTARTXCORD			25
#define PRINTWELDSTARTYCORD			100
#define PARAMWIDTH						69
#define WELDHISTORYPARAMWIDTH  		60
#define GRAPHPARAMWIDTH					100
#define ONELINEGAP						25
#define TWOLINEGAP						50
#define THREELINEGAP					   75
#define FIVELINEGAP						125
#define ONEWELDLINEGAP					25
#define TWOWELDLINEGAP					40
#define THREEWELDLINEGAP				60
#define FOURWELDLINEGAP					80
#define FIVEWELDLINEGAP					100
#define SIXWELDLINEGAP					120
#define MAXXCOORDINATE					1114
#define MAXYCOORDINATE					1500
#define PAGESTARTCORDINATE				100
#define DEFAULTMINPAGE					1
#define DEFAULTMAXPAGE					2
#define WELDDATA						   1
#define FIRST25WELDDATA					25
#define LAST25WELDDATA					153
#define GRAPHTEXTSTARTXCORDINATE		100
#define GRAPHTEXTSTARTYCORDINATE		1190
#define GRAPHTEXTSPACING				50
#define HORNSCANTEXTSTARTYCORDINATE		1325
#define HORNSCANTEXTSPACING				50
#define METRIC		                  	1
#define USCS		                  	0
#define NORMALFONT	                  2
#define BOLDFONT		                  3
#define ZERO		                  	0
#define ONE				                  1
#define ZEROPOINT				   CPoint(0,0)
#define PRINTNOWGRAPHCORD		CPoint(200,550)
#define PRINTSCREENGRAPHCORD	CPoint(325,550)
#define PRINTHSGRAPHCORD		CPoint(225,200)
#define PRINTHSCGRAPHCORD		CPoint(200,600)
#define YEARMONTHFOLDERNAME 7
#define YEARSIZE  4
#define MONTHSIZE 2
#define DATESIZE 2
#define WELDINPROGRESS			1
#define PIXPERINCH				150
#define EUROPEANSMALLFONT		23
#define EUROPEANBIGFONT			23
#define EUROPEANWELDDATAFONT	18
#define EUROPEANWELDDATASMALLFONT	16
#define TRADITIONALSMALLFONT	21
#define TRADITIONALBIGFONT		21
#define TRADITIONALWELDDATAFONT	20
#define SIMPLIFIEDSMALLFONT		23
#define SIMPLIFIEDBIGFONT		23
#define SIMPLIFIEDWELDDATAFONT	19
#define JAPANESESMALLFONT		20
#define JAPANESEBIGFONT			20
#define JAPANESEWELDDATAFONT	16
#define KOREANSMALLFONT			22
#define KOREANBIGFONT			22
#define KOREANWELDDATAFONT		17
#define PRINTEROFFLINEALARM		1
#define USBOFFLINEALARM			2
#define USBFULLALARM			   4
#define ALARMBUTTONRECT			CRect(2,4,160,38)
#define ALARMBUTTONRECT_RE		CRect(0,0,160,38)

#define CALIBX(point,HPIX) (point * HPIX)/PIXPERINCH
#define CALIBY(point,VPIX) (point * VPIX)/PIXPERINCH
#define Calib(p, HorPix,VerPix) CRect(CALIBX(p.left,HorPix),CALIBY(p.top,VerPix),CALIBX(p.right,HorPix),CALIBY(p.bottom,VerPix))
#define CalibPoint(p, HorPix,VerPix) CPoint(CALIBX(p.x,HorPix),CALIBY(p.y,VerPix))
#define Font(Font,nHorz) ((nHorz<300)? (Font) : (Font+3))


#define TOP_COORDINATE_1_BUTTON			60
#define TOP_COORDINATE_4_BUTTON			312
#define MEDIUM_BUTTON_WIDTH				170
#define LEFT_COORDINATE_1_BUTTON		20
#define LCOORDINATE_COL1_FACTOR			185
#define LCOOR_LARGEBUTTON_FACTOR		45
#define LCOOR_RADIO_FACTOR				60

#define SEQUENCESCREEN              2
#define PRESETSCREEN                1
#define POWERPRESETSCREEN           3
#define USBPRESETSCREEN             4
#define PRESETINFOSCREEN            0
#define VARMAXMINLENGTH		        2
#define DATE_LENGTH                  6
#define MAXEXESIZE                  20
#define MAXLANGNAME                 30
#define MAXSECURITYSIZE             15
#define MAXPASSSIZE                 12
#define MAXRADIOINDEX               14

#define PSPresetSelected				0
#define USBPresetSelected				1
#define VARIABLE_COORDINATE1        80
#define VARIABLE_COORDINATE2        310
#define VARIABLE_COORDINATE3        350
#define VARIABLE_COORDINATE4        380
#define VARIABLE_COORDINATE5        390
#define VARIABLE_WIDTH              225

#define Distance_RequestValue  64
#define Power_RequestValue  2
#define Velocity_RequestValue  32
#define Force_RequestValue  16
#define Amplitude_RequestValue  8
#define Frequency_RequestValue  4
#define MaxPresetNum_InListBox	16
#define MaxSequencePresetNum_InListBox 30
#define HornScan_RequestValue 128

#define SIZEOFPRESETDATA	    570
#define PRESETSIZE_WITHOUTDUPS	454
#define PresetNameStrPos				200
#define DupsPresetNameStrPos			316

#define MAXSYSFILE_LEN              10
#define MINUSBDATASIZE           51200     
#define USBFULLALARMPRESENT          4

enum LEVEL {                      /* Security level of user                */
   OPERATOR,                      /* Lowest level of security              */
   SETUP,                         /* Middle level of security              */
   MAINTAINENCE,                  /* Highest level of customer security    */
   BRANSON   };                   /* Level for Branson personnel only      */
      
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CPrintText;
#include "VgaMenuItem.h"
#include "VgaMenu.h"
class CXmlElement;
class CWeldingData;
class CVgaDrawGraph;
class CTable;
class CUSBFolder;
class CWeldingHistory;

class CChildView : public CWnd
{
public:
	CString GraphTitle;
    static int StartWeldData;
    int TemporaryAlarmCount;
    bool AlarmUpdateRequired;
    static CStringArray WeldDataPatamStringID;
    CVgaMenu *SetupMenuPointer,*SequenceMenuPointer;
    CString USBGraphMenu;
    CString Str_PMCGraphs,StrCurrent,Str_PwrAvg,Str_PMCWeld,Str_PMCCycles,Str_NoValidGraph,Str_Frequency,Str_DigitalTuneSett;
    bool StringDebugFlag,EnableUSBGraph;
    bool BottomHalfScreen; 
    CString Str_Save,Str_Exit,Str_PassAccp,Str_PassRej,Str_Secret,Str_Series,Str_Parallel;
    bool DisplayLockFlag;
    bool MenuUSBDraw;
    bool BrowseUSB;
    int CopyPresetNum;
    bool CopyAllFlag;
    bool OverWritePreset;
    bool OverWritePSPreset;
    int OverWritePresetNum;
    static CString PSName;
    static CList<CString, CString>USBPresetNames;
    static int TotalUSBPreset;
    static int SelectedUSBPreset;
	 static int SelectedPowerPreset;
    static bool LastSelectedPresetFrom;
    CString AlarmMenuIdentifier;
    CString AlarmMenuName,CycleCountString;
    static bool ContinuePrinting;
    bool ScanA_Present;
	 bool ScanB_Present;
	 bool ScanC_Present;
	 bool CurrentScan_Present;
    bool ScanA_On;
	 bool ScanB_On;
	 bool ScanC_On;
	 bool CurrentScan_On;
    static bool PMCScreen;
    static bool ColdStartInProcess;
    static CString mainmenu_string,WeldResult_string,WeldSetup_string,Graphs_string;
    CString PrinterPower_str_Online,PrinterPower_str_Offline;
    void SetDimension(CVgaMenuItem *ptr,int count);
    CString MenuNameID;
    int Convert_Char_To_Int(unsigned char *&data, int &length, int Bytes);
    float Convert_Char_To_Float(unsigned char *&data, int &length, int Bytes);
    char Sys_FileSize;
    char CurrentExecutable[MAXEXESIZE];
    char CurrentLanguageName[MAXLANGNAME];
    char SecurityFile[MAXSECURITYSIZE];
    bool PasswordRequired;
    char CurrentPassword[MAXPASSSIZE];
    CString StartUpVerFileName;
    CString SystemVerFileName;
    static CString ScanString;
    static int TempCount;
    CList<CString, CString> menusname;
    static int Currentlanguage;
    bool listbuild;
    CVgaMenu * CurrMenuList;
    void ModifyObjectList(CVgaMenu *);
    bool CheckConditions(CVgaMenuItem *) const;
    enum BUTTONTYPE{SMALL,NORMAL,LARGE,TEXTTYPE,RADIOTYPE,DEFAULT};
    static int ButtonType;
    static int RowPerPage;
    static int ColumnPerPage;
    static int ControlLevel;
    static int Actuator;
    static int WeldMode;
    static int Securitylevel;
    static int AccessLevelSystem;
    static int SWconfiguration;
    static int HWconfiguration;
    static int ExitButtonFlag;
    static int SaveButtonFlag;
    bool SendCommandForStateMachineEnable();
    void GetButtonShape(int &Hgap,int &Vgap,int &Width,int &Height);
    void RecalculateMenuItemsLayout(int height,CVgaMenu * CurrMenuLst);
	static bool PollingTimeOnMsgScrn;
	static bool LargeWaitingTime;
	static bool USBGlobalFlag;
	CMutex USBMutex;
	CMutex mutex;
	int * GraphWeldDataIdArray;
	int * WeldDataIdArray;
	void GetWeldDataIdArray(bool DeletePrevious);
	void GetGraphWeldDataIdArray(bool DeletePrevious);
	CString GetAlarmString(CVgaMenuItem *ptr);
	void AddAlarmButtonInList();
	bool GetAlarmButton();
	static bool CommandForAlarmButton;
	static CString USBSelectedPresetName;
	CList<CString, CString>WeldAlarmStringList;
	CList<CString, CString>WeldHistoryAlarmStringList;
	CList<CString, CString>GraphAlarmStringList;
	CTypedPtrList<CPtrList, CPrintText *> PrintObjectList;
	CTypedPtrList<CPtrList, CPrintText *> PrintSequenceObjectList;

	bool USBAlarm;
   bool USBFullAlarm;
	bool HornScanPlzWait;
	static int ViewGraphGlobalCount;
	CHostCommand * ViewGraphWeldData;
	int UniversalCount;
	bool MakeUSBWeldData(unsigned char *&data,int & length,int Difference);
	int MakePrintWeldData(unsigned char *&data,int & length,int Difference);
	void CheckPrinterStatus();
	void SendCommandAlarms(int AlarmType);
	static bool RunResultScreen;
	static int PMCMaxVdata;
	static void ErrorBeep();
	static int CurrentSequencePreset;
	static bool PMCDisable;
	static int LowerPMCLimit;
	static int UpperPMCLimit;
	static int GraphTwoRequestValue;
	static int GraphOneRequestValue;
	void ExitProgram();
	static CString LastUSBPresetFolder;
	static bool ISUSBPresent;
   static bool SaveRecallPresetScrn;
	void ShowMessageScreen(CString Message);
	void GetPowerSupplyName();
	static CString 	PSPresetText[MAX_PSPRESET];
	CString StrPage,Str_HornId;//StrPage[9];
	void CreateFolder(bool CheckForPreset);
	CString PowerSupply;
	CString Date;
	bool CheckForPrinting();
	bool DataForUSB(int DataId);
	int UniqueID;
	static int AlarmCount;
	bool WeldOnChangedPreset;
	bool ValidFolderName(CString FileName, int Fun_Id);
	bool PrepareUSBList(CString FilePath, int Fun_Id,int Address);
	bool IsPageSizeMenu;
	int GlobalCycleCount;
	bool ExtPreset;
	void GetPrintingParameters(bool InilitilizeBaseCount);
   void PrintVQSLimits();
   bool USBPresent();
	void CopyHSCScreenGraphs();
	static bool AbortPrinting;
	static CString *Parameter_Heading;
	static CString *Parameter_Units_USCS;
	static CString *Parameter_Units_Metric;
  	static int *Parameter_ID;
	static int TotalTextHeading;
	void GetAllWeldDataHeading(CXmlElement * e);
	static bool PrinterPresent;
	CEvent WaitForPrintData;
   static UINT PrintingThread(LPVOID);

	CEvent WaitForUSBData;
	static UINT WriteDataToUSB(LPVOID);

   CEvent WaitForEtherNetAlarmHandle;
   static UINT EtherNetAndAlarmHandle(LPVOID);
	bool HandleAlarmChange();

	void OnEndPrinting(CDC *, CPrintInfo *);
	void BuildPrintList(int type);
	static struct PrintValues{
							bool PrintSampleDisable;
							int PrintSampleValue;
							bool PrintOnAlarmValue;
							int BaseCount;
							};

	static struct USBValues{
							bool USBSampleDisable;
							int USBSampleValue;
							bool USBOnAlarmValue;
							int BaseCount;
							};
	static	struct PrintingSetup
	{
		bool IsPrinting;
		bool IsPageSizeA4;
		int WeldsPerPage;
   };
	
	int PresentWeldCount; 
	int PresentAlarmCount;
	static int WeldCycleCount;
	void ReleaseDc(CDC *pDC);
	CDC* CChildView::GetDc();
	static int BotomHalfRefreshTime;
	CChildView();
	virtual ~CChildView();

	bool IsLanguageMenu;
	bool AlarmScreenOnCalibration;
	bool IsAlarmScreen;
	static bool metric;
   static bool PasswordFlag;
	static bool IsTwoSecExpired;
	static bool ScreenSetupFlag;
	static bool Start_Screen;
	static bool ActColdStartFlag;
	static bool BottomHalfTimerOn;
	static bool IsNewScreenPointer;
	static bool SysInfoScreen;
	static bool DisableFlag;
	static bool AutoRefreshon;
	static bool AmplitudeMicrons;
	static bool PeakPowerMicrons;
	static int PeakPowerWattsMax;
	static int AmplitudeMicronsMax;
	static int Language_Index;
	static int CurrentPresetNum;
	static int RAMCalibCordinate_Xa;
	static int RAMCalibCordinate_Ya;
	static int RAMCalibCordinate_Xb;
	static int RAMCalibCordinate_Yb;
	static int TextColor;
	static int 	TitleBarColor;
	static int Button_Color;
	static int Back_Color;
   static int Highlight_Color;
	static DWORD Color_Array[12];
	
	int mainMenuAddress;
	int GraphsMenu_Address;
	int WeldSetup_Address;
	int WeldResults_Address;
	
   void WeldHistoryPrint(int ID);
   void WeldDataPrint(int ID);
   void GraphsWeldPrint(int ID);
   void SetUpPrint(int Address);
   void SequencingPrint(int Address);
	void AddSaveExit(CVgaMenu * CurrMenuLst);
	void ProcessNak(unsigned char *&data,int & length,int Address,int FunID);
	void SaveData();
	void Reload_Start_Screen();
   void BuildCompleteKeypadList(int type,unsigned char *&data,CString* Object_Text,int ID,CVgaMenuItem *ptr);
	static void KillTimers(int TimerID);
	static CChildView * thisPtr;
	static int InitialiseTimer(int TimerID,int Time);
	void SaveVQSData();
	static void SendCommandForQualityWindow(int NoOfPreset);

	CTypedPtrList<CPtrList, CVgaMenuItem *> menuEntryList;
	CList<int, int> menus;
   CList<CVgaMenu *,CVgaMenu *> menupointers;
	bool IsFolderPresent(CString Path, CString FileName);
	CTypedPtrList<CPtrList, CScreenKeypad *> keypadList;

	/* Graph Related Lists */
	CList<int, int> PrintInfoList;
   CTypedPtrList<CPtrList, CVgaDrawGraph *> GraphPrintList;
   CTypedPtrList<CPtrList, CVgaDrawGraph *> HSGraphPrintList;
	CMapStringToString StringMap;
	CMapStringToString AlarmMap;
	CStringArray AlarmEng,PString,Manual,GraphPrText,LString,PrintHSInfoText,AllMonthStrings;
	CList<int, int> PrintGraphIDList;
	CList<int, int> PrintWeldDataIDList;
	CTypedPtrList<CPtrList, CPrintText *> PrintGraphTextObjectList;
   CTypedPtrList<CPtrList, CTable *> TablePrintList;

	CTypedPtrList<CPtrList,CWeldingData *> PrintGraphWeldDataList2;
   CTypedPtrList<CPtrList, CWeldingData *> GraphWeldDataPrintList;
   CTypedPtrList<CPtrList, CWeldingData *> WeldDataPrintList;
   CTypedPtrList<CPtrList, CWeldingData *>PrintWeldHistoryList2;
	int Total_Objects;
	static int PresetNum;
	static int Presettrack;
   static int MaxPreset;
   static bool PowerUpSBC;
   void GetRAMData();
   bool ReadStartUpVersionString();
   bool ReadSystemVersionString();
   void Add_Back_Next_Button();
   void Back_Next_Button_Layout();
   void GetAveragePowerGraph(CDC *pDC, CChildView * view);
   CString CurrentFilepath;
   void CheckUSBSpaceAvailable();
   // ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMainMenu();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
	void OnPrint(CDC *pDC, CPrintInfo *);
	void OnPrepareDC(CDC *pDC, CPrintInfo *pInfo);
	void OnBeginPrinting(CDC *, CPrintInfo *);
	BOOL DoPreparePrinting(CPrintInfo *pInfo);
	BOOL OnPreparePrinting(CPrintInfo *printInfo);
		/* USB Related Lists */
	CTypedPtrList<CPtrList, CHistoryData *> USBHistoryList;
   CTypedPtrList<CPtrList, CVgaDrawGraph *> USBGraphsList;
	CList<int,int>USBGraphCountList;

	
	bool PrintOnAlarmAndSample();
	int BaseWeldCount;
	int TempBaseWeldCount;
	void print();
	 
	 int PresentPresetNum;
	int TempPresetNum;
	
	CString GetCurrentFilePath();
	CString GetCurrentFilePath(CHistoryData *object);
	CString CopyScreenGraphs();
	bool SendUSBWeldData();
	bool SendUSBGraphData();

	
	void DrawPageNumber(CDC*pDC);
	CString YearMonthName;
	enum 
	{
		ACK = 0x06,
		NAK = 0x15
	};
	static bool powerup;
	bool HandleAlarmChangeInPolling(int TempAlarmCount);
	bool AlarmPresent;
	static int PrinterStatuscheck;
	int Total_Text_Objects;
	void SetRequestValue(int *TotalGraphRequestValue, int *TotalGraph, int ID,int CurrentGraphRequestValue, PrintValues *CurrentGraph);
	void DrawKeypad(CDC*pDrawDC);
	void AnalyzePollingResponse(unsigned char *&data,int &length);
	void SendPollingCommand();
	void DrawFirstScreen();
	CPoint CalibratePoint(CPoint p);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__04D2A820_3DAF_4495_A8E2_35B717D209D3__INCLUDED_)
