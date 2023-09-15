// HistoryView.cpp : implementation of the CHistoryView class
//
/*
Revision #		Date		Author			Description
----------		--------	----------		-------------------------------------
1.0				04/24/06	LAM				Initial Version.
1.1				05/10/07	BSahu			Modified Code to Add View HosrnScan Graphs.
1.2				05/23/07	BSahu           Modified DrawCompareHSgraph() for Tracker issue 4114
1.3				10/22/07	BSahu           Modified to Add printing Feature.
1.4				10/22/07	BSahu           Modified to code clean up.
1.5				10/25/07	BSahu		    Modified Code to Graph Print OverLap And Weld Cycle over lap issue.
1.6				10/29/07	BSahu		    Modified Code to Modifie WeldHistory printout data
1.7				09/15/08	PDwivedi	    Modified code for Tracker issue.
1.8             09/17/08    ygupta          Modified code for Tracker issue REQ00416.
1.9				09/26/09	PDwivedi		Added changes for compatability of graph Object.
*/

#include "stdafx.h"
#include "History.h"
#include "HistoryDoc.h"
#include "HistoryView.h"
#include "MainFrm.h"
#include "NoOfWeld.h"
//#include "GraphOldData.h"

#define MAXBUTTONSONSCREEN 8
#define ID_BN_LEFT			1
#define ID_BN_RIGHT			2
#define ID_BN_UP			3
#define ID_BN_DOWN			4
#define ID_BN_PAGEUP		5
#define ID_BN_PAGEDOWN		6
#define ID_BN_EXIT			7
#define ID_BN_GRAPH			8
#define ID_BN_GRAPHAMP		9
#define ID_BN_GRAPHCOLDIST	10
#define ID_BN_GRAPHFORCE	11
#define ID_BN_VELGRAPH		12
#define ID_BN_FREQGRAPH		13
#define ID_BN_POWERGRAPH	14
#define ID_BN_EXITGRAPH		15
#define ID_BN_PRINT			16
#define ID_BN_PRINT_GRAPH   17
#define ID_BN_PRINT_HSGRAPH   18
#define ID_BN_PRINT_HSDATA   19

#define AMPLITUDEGRAPH		4099
#define COLDISTGRAPH		4102
#define FROCEGRAPH			4111
#define FREQGRAPH			4114
#define POWERGRAPH			4124
#define VELOCITYGRAPH		4192
#define HORNSCANGRAPH	    4125
#define MENUBUTTONHIEGHT	40
#define TOPCORDINATE		60
#define FIRSTCOLOUMN_X		26
#define SECONDCOLOUMN_X		336
#define MENUBUTTONGAP		64
#define LINE_START_X		20
#define LINE_END_X			600
#define LINE_Y				130
#define DATAWIN_START_X		1
#define DATAWIN_START_Y		40
#define DATAWIN_END_X		638
#define DATAWIN_END_Y		310

#define PowerGraph_Rect CRect(10,360,170,390)
#define FreqGraph_Rect CRect(180,360,340,390)
#define AmpGraph_Rect CRect(350,360,510,390)
#define ForceGraph_Rect CRect(10,400,170,430)
#define VelGraph_Rect CRect(180,400,340,430)
#define ColDistGraph_Rect CRect(350,400,510,430)
#define Graph_Exit_Rect CRect(530,380,620,420)
#define Left_Rect CRect(45,370,95,420)
#define Right_Rect CRect(345,370,395,420)
#define Up_Rect CRect(165,370,215,420)
#define Down_Rect CRect(225,370,275,420)
#define PageUp_Rect CRect(105,370,155,420)
#define PageDown_Rect CRect(285,370,335,420)
#define Graph_Rect CRect(430,390,520,420)
#define Exit_Rect CRect(530,390,620,420)
#define Screen_Rect CRect(0,0,640,480)
#define PageNO_Rect	CRect(500,0,640,40)
#define PrintSelect_Rect CRect(516,2,636,38)

#define HS_ScanA_Rect	CRect(40,410,160,438)
#define HS_ScanB_Rect	CRect(180,410,300,438)
#define HS_ScanC_Rect	CRect(320,410,440,438)
#define CurrentHS_Scan_Rect	CRect(410,408,530,438)
#define ScanExit_Rect CRect(470,410,570,438)

#define ID_ScanA 21
#define ID_ScanB 22
#define ID_ScanC 23
#define ID_CurrentScan 24 

#define ID_NEXT				1000
#define ID_BACK				1001
#define ID_EXIT				1002

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;


#endif

/////////////////////////////////////////////////////////////////////////////
// CHistoryView

IMPLEMENT_DYNCREATE(CHistoryView, CView)

	BEGIN_MESSAGE_MAP(CHistoryView, CView)
	//{{AFX_MSG_MAP(CHistoryView)
	ON_WM_CREATE()
	ON_COMMAND(OPEN_PS, DrawFirstScreen)
	ON_WM_TIMER()
	ON_COMMAND(ID_OPEN, OnOpenPSNew)
	ON_COMMAND(ID_APP_EXIT, OnProgramExit)
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_OPEN, OnHSOpen)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_BN_CLICKED(ID_BN_RIGHT, Right)
	ON_BN_CLICKED(ID_BN_LEFT, Left)
	ON_BN_CLICKED(ID_BN_UP,Up)
	ON_BN_CLICKED(ID_BN_DOWN,Down)
	ON_BN_CLICKED(ID_BN_PAGEUP,PageUp)
	ON_BN_CLICKED(ID_BN_PAGEDOWN,PageDown)
	ON_BN_CLICKED(ID_BN_EXIT,Exit)
	ON_BN_CLICKED(ID_BN_GRAPH,Graph)
	ON_BN_CLICKED(ID_BN_GRAPHAMP,AmpGraph)
	ON_BN_CLICKED(ID_BN_GRAPHCOLDIST,ColDistGraph)
	ON_BN_CLICKED(ID_BN_GRAPHFORCE,ForceGraph)
	ON_BN_CLICKED(ID_BN_VELGRAPH,VelocityGraph)
	ON_BN_CLICKED(ID_BN_FREQGRAPH,FreqGraph)
	ON_BN_CLICKED(ID_BN_POWERGRAPH,PowerGraph)
	ON_BN_CLICKED(ID_BN_EXITGRAPH,ExitGraph)
	ON_BN_CLICKED(ID_ScanA,ScanAGraph)
	ON_BN_CLICKED(ID_ScanB,ScanBGraph)
	ON_BN_CLICKED(ID_ScanC,ScanCGraph)
	ON_BN_CLICKED(ID_BN_PRINT,PrintWeldHistoryData)
	ON_BN_CLICKED(ID_BN_PRINT_GRAPH,PrintWeldHistoryGraph)
   ON_BN_CLICKED(ID_BN_PRINT_HSGRAPH,PrintHSData)
   ON_BN_CLICKED(ID_BN_PRINT_HSDATA,PrintHSData)
	END_MESSAGE_MAP()
	//POSITION CHistoryView::position;
	bool CHistoryView::HSMenu=false;
	CString CHistoryView::ModePresetString;
	CString CHistoryView::HSFolderPath;
	int CHistoryView::HighLightString=-1;
	bool CHistoryView::HSFlag=false;
	bool CHistoryView::ScanA_On=false;
	bool CHistoryView::ScanB_On=false;
	bool CHistoryView::ScanC_On=false;
	int CHistoryView::Language_Index;
	bool CHistoryView::HS1_Present=false;
	bool CHistoryView::HS2_Present=false;
	bool CHistoryView::HS3_Present=false;
	int CHistoryView::NoOfWeldObjectPrinted=0;
	bool CHistoryView::Manual =false;
	int CHistoryView::extratextinboth=0;
	bool CHistoryView::AmpMicronsFormat=false;
	bool CHistoryView::PowerWattsFormat=false;
	//////////////////////////////////////////
	// CHistoryView construction/destruction//
	//////////////////////////////////////////
CHistoryView::CHistoryView()
{ 
	PageNum=1;
	BrowsingLevel=BRANSONLOGO;
 	//LeftMostParam =1;
	View=this;
	DisableFlag=false;
	
	SmallFont.CreateFont(20 , 0, 0, 0, FW_NORMAL,FALSE, FALSE, FALSE, 
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FF_DONTCARE, _T("Arial"));
		CFont Font;

	BigFont.CreateFont(26 , 0, 0, 0, FW_NORMAL,FALSE, FALSE, FALSE, 
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FF_DONTCARE, _T("Arial"));
				
}

CString Manualstr[5]={
	"Special Note:", 
	 "Manual Scale: This graph may show part of the cycle. To see the    ",
      "entire cycle set the x-axis to your weld time + hold time +        ",
      "afterburst if used. This change will take effect on the next cycle.",
	  "  "};

		CString GraphPrText[5]={
		
        "NOTES",
        "Downspeed               :  ____________________________________",
		"Act. Gauge Pressure     :",
		"Column Position         :  ____________________________________",
		"____________________________________"
		
	};


	CString CHistoryView::AlarmEng[] = {
      "NC0",
      "Upper Limit Timeout",
      "NC2",
      "Trigger before Pretrigger",
      "Trigger Timeout",
      "NC5",
      "LLS abort before TRS",
      "External Cycle Abort",
      "Missing Part Abort",
      "Abs Before Trg",
      "Amp Step before Trigger",
      "Force Step before Trigger",
      "Ground Detect Abort",
      "External U/S Delay Timeout",
      "External Start Signal lost before cycle complete",
      "External Start Input Timed out",
      "NC16",
      "NC17",
      "NC18",
      "NC19",
      "NC20",
      "NC21",
      "NC22",
      "NC23",
      "NC24",
      "NC25",
      "NC26",
      "NC27",
      "NC28",
      "NC29",
      "NC30",
      "NC31",
      "OL0",
      "Test Overload",
      "Pretrigger Overload",
      "Seek Overload",
      "Power Supply Overload",
      "Continuous Power Exceeded",
      "Afterburst Overload",
      "Pre-Weld Seek Overload",
      "Post Weld Seek Overload",
      "OL9",
      "Energy Brake Overload",
      "OL11",
      "OL12",
      "OL13",
      "OL14",
      "OL15",
      "OL16",
      "OL17",
      "OL18",
      "OL19",
      "OL20",
      "OL21",
      "OL22",
      "OL23",
      "OL24",
      "OL25",
      "OL26",
      "OL27",
      "OL28",
      "OL29",
      "OL30",
      "OL31",
      "EQ0",
      "Encoder Failure",
      "Upper Limit Switch Failed",
      "Upper Limit Switch Failed",
      "Door/Trigger Switch Failure",
      "Loadcell Failure",
      "Solenoid Drive Failure",
      "Thermal Overload",
      "Failure of Preset Data or Battery Backed Ram",
      "Horn Return Timeout",
      "Actuator NovRam Failed",
      "Power Supply NovRam Failed",
      "Start Switch Stagger Time Missed",
      "Multi Purpose Switch Failed",
      "Wrong Actuator AEF/AOP Cannot be used with This Level Control",
      "Ultrasonic Power Supply Not Present or Failed",
      "Printer Buffer Full",
      "Start Switch Closed Failure",
      "Pretrigger Timeout",
      "EQ19",
      "Recalibrate Actuator",
      "Actuator Clear Function Failure",
      "Failure of R/F loop",
      "Start Switches Lost",
      "The actuator type was changed since last weld cycle",
      "System Pressure Setting Incorrect",
      "EQ26",
      "EQ27",
      "EQ28",
      "EQ29",
      "EQ30",
      "EQ31",
      "CM0",
      "Trigger Lost during Hold",
      "Ground Detect Abort",
      "Max Timeout",
      "Time Value for Amplitude Step not Reached",
      "Time Value for Force Step not Reached",
      "Energy Value for Amplitude Step not Reached",
      "Energy Value for Force Step not Reached",
      "Collapse Distance for Amplitude Step not Reached",
      "Absolute Distance for Amplitude Step not Reached",
      "Power Level for Force Step not Reached",
      "Power Level for Amplitude Step not Reached",
      "External signal for Amplitude Step did not occur",
      "External signal for Force Step did not occur",
      "Trigger Lost during Weld",
      "External Cycle Abort",
      "Amplitude B was not reached because the weld was too short",
      "Memory DIP Switch on P/S may be off",
      "Amplitude A not reached because weld was too short",
      "Amplitude B was not reached because the weld was too short",
      "Amplitude exceeded because the weld was too short",
      "Energy Not Reached",
      "Trigger Force is Greater Than the End Force",
      "Collapse Distance for Force Step not Reached",
      "CM24",
      "CM25",
      "CM26",
      "CM27",
      "CM28",
      "CM29",
      "CM30",
      "CM31",
      "CA0",
      "CA1",
      "CA2",
      "CA3",
      "CA4",
      "CA5",
      "CA6",
      "CA7",
      "CA8",
      "CA9",
      "CA10",
      "CA11",
      "CA12",
      "CA13",
      "CA14",
      "CA15",
      "CA16",
      "CA17",
      "CA18",
      "CA19",
      "CA20",
      "CA21",
      "CA22",
      "CA23",
      "CA24",
      "CA25",
      "CA26",
      "CA27",
      "CA28",
      "CA29",
      "CA30",
      "CA31",
      "WA0",
      "Actuator Clear distance not reached",
      "Energy Compensation Maximum Energy Reached",
      "WA3",
      "WA4",
      "Peak Power Cutoff",
      "Absolute Distance Cutoff",
      "Weld Time was Extended for Energy Compensation",
      "For optimum performance recalibrate your actuator",
      "Collapse Cutoff",
      "WA10",
      "Ultrasonics Disabled by user input",
      "USB Memory Nearly Full",
      "WA13",
      "WA14",
      "WA15",
      "WA16",
      "WA17",
      "WA18",
      "WA19",
      "WA20",
      "WA21",
      "WA22",
      "WA23",
      "WA24",
      "WA25",
      "WA26",
      "WA27",
      "WA28",
      "WA29",
      "WA30",
      "WA31",
      "PR0",
      " -Reject Energy Limit",
      " +Reject Energy Limit",
      " -Reject Peak Power Limit",
      " +Reject Peak Power Limit",
      " -Reject Collapse Distance Limit",
      " +Reject Collapse Distance Limit",
      " -Reject Absolute Distance Limit",
      " +Reject Absolute Distance Limit",
      " -Reject Trigger Distance Limit",
      " +Reject Trigger Distance Limit",
      " -Reject Weld Force Limit",
      " +Reject Weld Force Limit",
      " -Reject Time Limit",
      " +Reject Time Limit",
      "PR15",
      "PR16",
      "PR17",
      "Lower Limit not Reached",
      "-Reject Frequency Limit",
      "+Reject Frequency Limit",
      "+Reject Power Match Curve Band Limit",
      "-Reject Power Match Curve Band Limit",
      "PR23",
      "PR24",
      "PR25",
      "PR26",
      "PR27",
      "PR28",
      "PR29",
      "PR30",
      "PR31",
      "PS0",
      " -Suspect Energy Limit",
      " +Suspect Energy Limit",
      " -Suspect Peak Power Limit",
      " +Suspect Peak Power Limit",
      " -Suspect Collapse Distance Limit",
      " +Suspect Collapse Distance Limit",
      " -Suspect Absolute Distance Limit",
      " +Suspect Absolute Distance Limit",
      " -Suspect Trigger Distance Limit",
      " +Suspect Trigger Distance Limit",
      " -Suspect Weld Force Limit",
      " +Suspect Weld Force Limit",
      " -Suspect Time Limit",
      " +Suspect Time Limit",
      "PS15",
      "PS16",
      "PS17",
      "PS18",
      "PS19",
      "PS20",
      "PS21",
      "PS22",
      "PS23",
      "PS24",
      "PS25",
      "PS26",
      "PS27",
      "PS28",
      "PS29",
      "PS30",
      "PS31"
 };
	CString CHistoryView::PrinterName;	
	bool CHistoryView::FileCreated=false;
	int CHistoryView::SelectedWeldData;
	int CHistoryView::LeftMostParameter;
	int CHistoryView::TotalCycle;
	int *CHistoryView::Parameter_ID;
	int CHistoryView::TotalColoumn;
	int CHistoryView::TopMostData;
	bool CHistoryView::SelectedDataUnit;
	int CHistoryView::SelectedWeldId;
	CFont CHistoryView::SmallFont;
	CFont CHistoryView::BigFont;
	bool CHistoryView::DisableFlag;
	CString CHistoryView::YearMonthName;
	CString CHistoryView::PSName;
	CString CHistoryView::TitleString;
	CHistoryView *CHistoryView::View;
	CString CHistoryView::PreviousFileName;
	short CHistoryView::Parameter_Units_Metric_temp[MAXPARAMVALUES+1][MAXPARAMUNITLENGTH];
	short CHistoryView::Parameter_Units_USCS_temp[MAXPARAMVALUES+1][MAXPARAMUNITLENGTH];
	CString CHistoryView::HZData[3];
	CString CHistoryView::WelddataHeadings[] = {  " ",
								"Cycle#",
								"Time",
								"Pk Pwr",
								"Energy",
								"Vel",
								"Vel",
								"Weld Abs",
								"Total Abs",
								"Weld Col",
								"Total Col",
								"Set Amp A",
								"Set Amp B",
								"Set ForceA",
								"Set ForceB",
								"Weld Force",
								"Act Press",
								"Freq Min",
								"Freq Max",
								"Freq Start",
								"Freq End",
								"Freq Chg",
								"Preset #",
								"Cycle time",
								"Trig Force"
								};
CString CHistoryView::Parameter_Units_USCS[]={  " ",
								"",
								"(S)",
								"(%)",
								"(J)",
								"(in)",
								"(in)",
								"(in)",
								"(in)",
								"(in)",
								"(in)",
								"(%)",
								"(%)",
								"(lb)",
								"(lb)",
								"(lb)",
								"(PSI)",
								"(Hz)",
								"(Hz)",
								"(Hz)",
								"(Hz)",
								"(Hz)",
								" ",
								"(S)",
								"(lb)",
								};
CString CHistoryView::Parameter_Units_Metric[]={  " ",
								"",
								"(S)",
								"(%)",
								"(J)",
								"(mm)",
								"(mm)",
								"(mm)",
								"(mm)",
								"(mm)",
								"(mm)",
								"(%)",
								"(%)",
								"(N)",
								"(N)",
								"(N)",
								"(kPa)",
								"(Hz)",
								"(Hz)",
								"(Hz)",
								"(Hz)",
								"(Hz)",
								" ",
								"(S)",
								"(N)",
								};
int CHistoryView::Parameter_Formats[]={ 
								INTEGER,
								INTEGER,
								TIME,
								WATTS,
								ENERGY,
								VELOCITY,
								VELOCITY,
								DISTANCE,
								DISTANCE,
								DISTANCE,
								DISTANCE,
								AMPLITUDE,
								AMPLITUDE,
								FORCE,
								FORCE,
								FORCE,
								PRESSURE,
								FREQUENCY,
								FREQUENCY,
								FREQUENCY,
								FREQUENCY,
								FREQUENCY,
								INTEGER,
								TIME,
								FORCE,
								};
CString CHistoryView::Parameter_Units_Formats[]=	{  " ",
								"",
								"",
								"(W)",
								"",
								"",
								"",
								"",
								"",
								"",
								"",
								"(um)",
								"(um)",
								"",
								"",
								"",
								"",
								"",
								"",
								"",
								"",
								"",
								"",
								"",
								"",
								};
	int CHistoryView::ExitParam;
	int CHistoryView::FileOpenParam;
	int CHistoryView::GraphParam;
	int CHistoryView::GraphSelect;
	int CHistoryView::GraphPrintSelect=0;
	int CHistoryView::ExitGraphParam;
	int CHistoryView::GraphFileSelect=1;
	int CHistoryView::Graph1ID;
	int CHistoryView::Graph2ID;
	bool CHistoryView::NoValidGraph;
	bool CHistoryView::GraphFound=false;

	DWORD CHistoryView::Color_Array[]={
									RGB(0,0, 0),		//ColorNone
									RGB(0, 0, 0),		//Black
									RGB(0, 0, 255),		//Blue
									RGB(255,0,0),		//Red
									RGB(0,255,0),		//Green
									RGB(128,42,42),		//Brown
									RGB(255,0,255),		//Magenta
									RGB(0,255,255),		//Cyan
									RGB(192,192,192),	//gray
									RGB(127,127,127),	//Dark_Gray
									RGB(255,255,0),		//Yellow
									RGB(255,255,255)	//white	
};

CHistoryView::~CHistoryView()
{
	
}

BOOL CHistoryView::PreCreateWindow(CREATESTRUCT& cs)
{
	CHistoryDoc::View=this;
	return CView::PreCreateWindow(cs);
}

/************************************************/
/*This function  Draws the Device Context.		*/
/************************************************/
void CHistoryView::OnDraw(CDC* pDC)
{
	CHistoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC* pDrawDC;
	CDC dc;
	CBitmap bitmap;
	CBitmap* pOldBitmap;
	 if (!pDC->IsPrinting())
	{
		if (dc.CreateCompatibleDC(pDC))
		{
			if (bitmap.CreateCompatibleBitmap(pDC,SCREEN_END_X,SCREEN_END_Y))
			{
				pDrawDC = &dc;
				pOldBitmap = dc.SelectObject(&bitmap);
			}
		}
	}

	CPen *OldPen;
	CPen pen1(NULL, 1, COLORBLACK);
	OldPen=pDrawDC->SelectObject(&pen1);
	pDrawDC->SetBkMode(TRANSPARENT);

	if(BrowsingLevel==BRANSONLOGO)
	{
		CBitmap obj;
		CDC dc;
		dc.CreateCompatibleDC(pDrawDC);
		obj.LoadBitmap (IDB_BITMAP1); 
		dc.SelectObject(&obj);
		pDrawDC->BitBlt(SCREEN_START_X+1,SCREEN_START_Y+1,SCREEN_END_X-1,SCREEN_END_Y-1,&dc,0,0,SRCCOPY);
		obj.DeleteObject();
	}
	else
	{
		if(BrowsingLevel!=GRAPHS)
		pDrawDC->FillSolidRect(1,40,SCREEN_END_X-2,SCREEN_END_Y-80,COLORWHITE);
		pDrawDC->SelectObject(OldPen);
		pDrawDC->FillSolidRect(TITLE_RECT,COLORBLUE);
		pDrawDC->FillSolidRect(BOTTOM_RECT,COLORBLUE);

		if(BrowsingLevel==HIERARCHYYEARMONTH)
			TitleString=PSName;

		if(BrowsingLevel==HIERARCHYDAY)
			TitleString=YearMonthName;
				
		if(BrowsingLevel==WELDDATA)
			TitleString="Weld Data";
							
		if(BrowsingLevel==GRAPHS)
			TitleString="Graphs";
		if(BrowsingLevel== HIERARCHYHSFOLDER)
			TitleString="Horn Signature";
		if(BrowsingLevel== HIERARCHYHSDATA)
			TitleString="Horn Scan Compare Data";
		if(BrowsingLevel== HIERARCHYHSGRAPH)
		{
			CPen *OldPen;
			CPen pen1(NULL, 1, COLORBLACK);
			OldPen=pDrawDC->SelectObject(&pen1);
			pDrawDC->Rectangle(SCREEN_START_X,SCREEN_START_Y,SCREEN_END_X,SCREEN_END_Y);
			pDrawDC->SelectObject(OldPen);
			pDrawDC->SelectObject(OldPen);
			pDrawDC->FillSolidRect(SCREEN_START_X+1,SCREEN_START_Y+1,SCREEN_END_X-2,SCREEN_END_Y-2,COLORWHITE);
			pDrawDC->FillSolidRect(TITLE_RECT,COLORBLUE);
			pDrawDC->FillSolidRect(BOTTOM_RECT,COLORBLUE);
			TitleString="Horn Scan Compare Graph";
		}
		DrawText(pDrawDC, 11,true, TITLE_RECT, TitleString,true);
		DrawPageNumber(pDrawDC);
	}

	if(BrowsingLevel==WELDDATA)
		DrawWeldData(pDrawDC);

	if(BrowsingLevel== HIERARCHYHSDATA)
	{
		DrawCompareHSData(pDrawDC);

	}
	if(BrowsingLevel==HIERARCHYHSGRAPH)
	{
		DrawCompareHSgraph(pDrawDC);
		DrawHSGraphs(pDrawDC);
	}
	if(BrowsingLevel==GRAPHS)
	{
		CPen *OldPen;
		CPen pen1(NULL, 1, COLORBLACK);
		OldPen=pDrawDC->SelectObject(&pen1);
		pDrawDC->Rectangle(SCREEN_START_X,SCREEN_START_Y,SCREEN_END_X,SCREEN_END_Y);
		pDrawDC->SelectObject(OldPen);
		pDrawDC->SelectObject(OldPen);
		pDrawDC->FillSolidRect(SCREEN_START_X+1,SCREEN_START_Y+1,SCREEN_END_X-2,SCREEN_END_Y-2,COLORWHITE);
		pDrawDC->FillSolidRect(TITLE_RECT,COLORBLUE);
		pDrawDC->FillSolidRect(BOTTOM_RECT,COLORBLUE);
		DrawText(pDrawDC, 11, true,TITLE_RECT, TitleString,true);
		DrawGraphs(pDrawDC);
	}

	pDC->BitBlt(SCREEN_START_X,SCREEN_START_Y,SCREEN_END_X,SCREEN_END_Y,pDrawDC,0,0,SRCCOPY);
		pDC->SelectObject(pOldBitmap);
		ReleaseDC(pDrawDC);
}
/////////////////////////////////////////////////////////////////////////////
// CHistoryView printing

BOOL CHistoryView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CHistoryView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	nPrintPos = NULL;
	pInfo->SetMaxPage (2);
	
}

void CHistoryView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
	//	WeldObjectsList.RemoveAll();
	PrintGraphWeldDataList.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
// CHistoryView diagnostics

#ifdef _DEBUG
void CHistoryView::AssertValid() const
{
	CView::AssertValid();
}

void CHistoryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHistoryDoc* CHistoryView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHistoryDoc)));
	return (CHistoryDoc*)m_pDocument;
}
#endif //_DEBUG

/*******************************************************/
/*This Function will Read data from welddata log.	   */
/*******************************************************/
bool CHistoryView::ReadData()
{
	CString Path=DataFolder + "\\WeldData.log";
	TopMostData=1;
	SelectedWeldData=1;
	LeftMostParameter=1;
	CFile fp;
	CFileException e;

	if( !fp.Open( Path,CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
		 {
			return false;
		}
	

	int  Size= sizeof(CWeldData);
	if(ExitParam)
	{
		fp.Close();
		return true;
	}
	
	
	if(!fp.GetLength())
	{
		fp.Close();
		return false;
	}
	fp.SeekToBegin();	
	int sz = fp.GetLength();
	int ObjectSize = sizeof(int)+ 4*sizeof(char)+ sizeof(CWeldData);
	int NoOfObj = (fp.GetLength())/ObjectSize;
	float NoOfObjects =(float)(fp.GetLength())/ObjectSize;
	FileOpenParam=1;
	WeldDataPath = Path;
	CWeldData * object;
	unsigned int NoOfBytesRead=0;
	int x=0;
	int  size= sizeof(CWeldData);
	bool FirstObject = true;
	bool OldUnits;
	bool USBMetric;
	bool newformat=false;
	
	//Read first two bytes, if valid value then we have new format, if not then we have the old format
	int amp=0,power=0;
	NoOfBytesRead+=fp.Read(&amp,sizeof(int));
	NoOfBytesRead+=fp.Read(&power,sizeof(int));
	if(amp==2000000000||amp==1000000001||power==2000000000||power==1000000001)
		newformat=true;
	//Read only first value of the file and apply that format to all welds
	if (amp==2000000000)
		AmpMicronsFormat=true;
	else
		AmpMicronsFormat=false;
			
	if (power==2000000000)
		PowerWattsFormat=true;
	else
		PowerWattsFormat=false;
	fp.SeekToBegin();	
	NoOfBytesRead=0;
	
			
		while(NoOfBytesRead!=fp.GetLength())
		{	
			int ID;
			char Comma;	
			object =new CWeldData();

			if(newformat==true)
			{
				NoOfBytesRead+=fp.Read(&amp,sizeof(int));
				NoOfBytesRead+=fp.Read(&power,sizeof(int));
			}
			NoOfBytesRead+=fp.Read(&ID,sizeof(int));
			NoOfBytesRead+=fp.Read(&Comma,sizeof(char));
			if(Comma!=',')
			{
				while(WeldObjects.GetCount())
					free(WeldObjects.RemoveHead());
				while(WeldObjectsList.GetCount())
					WeldObjectsList.RemoveHead();
				return false;

			}
			NoOfBytesRead+=fp.Read(&USBMetric,sizeof(bool));
			if(FirstObject)
			{
				FirstObject = false;
				if(USBMetric)
					NoOfBytesRead+=fp.Read(&Parameter_Units_Metric_temp[0][0],MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(short));
				else
					NoOfBytesRead+=fp.Read(&Parameter_Units_USCS_temp[0][0],MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(short));
				OldUnits=USBMetric;
			}

			if(OldUnits!=USBMetric)
			{
				if(USBMetric)
					NoOfBytesRead+=fp.Read(&Parameter_Units_Metric_temp[0][0],MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(short));
				else
					NoOfBytesRead+=fp.Read(&Parameter_Units_USCS_temp[0][0],MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(short));
				OldUnits=USBMetric;
			
			}
			NoOfBytesRead+=fp.Read(&Comma,sizeof(char));
			if(Comma!=',')
			{
				fp.SeekToBegin();
				NoOfBytesRead=0;
				FirstObject=true;
			
				NoOfBytesRead+=fp.Read(&ID,sizeof(int));
				NoOfBytesRead+=fp.Read(&Comma,sizeof(char));
				if(Comma!=',')
				{
					while(WeldObjects.GetCount())
						free(WeldObjects.RemoveHead());
					while(WeldObjectsList.GetCount())
						WeldObjectsList.RemoveHead();
					return false;

				}
				NoOfBytesRead+=fp.Read(&USBMetric,sizeof(bool));
				if(FirstObject)
				{
					FirstObject = false;
					if(USBMetric)
						NoOfBytesRead+=fp.Read(&Parameter_Units_Metric_temp[0][0],MAXPARAMVALUES*6*sizeof(short));
					else
						NoOfBytesRead+=fp.Read(&Parameter_Units_USCS_temp[0][0],MAXPARAMVALUES*6*sizeof(short));
					OldUnits=USBMetric;
				}

				if(OldUnits!=USBMetric)
				{
					if(USBMetric)
						NoOfBytesRead+=fp.Read(&Parameter_Units_Metric_temp[0][0],MAXPARAMVALUES*6*sizeof(short));
					else
						NoOfBytesRead+=fp.Read(&Parameter_Units_USCS_temp[0][0],MAXPARAMVALUES*6*sizeof(short));
					OldUnits=USBMetric;
				
				}
				NoOfBytesRead+=fp.Read(&Comma,sizeof(char));
			}
			NoOfBytesRead+=fp.Read(object,size);
			NoOfBytesRead+=fp.Read(&Comma,sizeof(char));
			object->Units=USBMetric;
			object->UniqueId=ID;
			TotalColoumn=object->TotalColoumn;
			WeldObjects.AddHead(object);
			WeldObjectsList.AddHead(object);
			OldUnits=USBMetric;

		}
	CreateScreenButton();
	fp.Close();
	TotalCycle=WeldObjects.GetCount();
	Invalidate(false);
	return true;
}

/*************************************************************/
/*This Function will Read data from Graphdata log file.		 */
/*************************************************************/
bool CHistoryView::ReadGraph()
{

	CFile f;
	CFileException e;
	for(int GraphNum =1; GraphNum<=6;GraphNum++)
	{
		CString PathGraph;
		switch (GraphNum)
		{
			case 1 : PathGraph = DataFolder + "\\AmpGraph.log";
				break;
			case 2 : PathGraph = DataFolder + "\\ColDistGraph.log";
				break;
			case 3 : PathGraph = DataFolder + "\\ForceGraph.log";
				break;
			case 4 : PathGraph = DataFolder + "\\PowerGraph.log";
				break;
			case 5 : PathGraph = DataFolder + "\\FreqGraph.log";
				break;
			case 6 : PathGraph = DataFolder + "\\VelocityGraph.log";
				break;
		}
		if(f.Open(PathGraph,CFile::modeRead, &e))
		{
			
			if(f.GetLength())
			{
				f.SeekToBegin();
				CGraphData * Graph= new CGraphData();
				int  size= sizeof(Graph->GraphData);
				delete Graph;
				char Comma;
				int ObjectSize = sizeof(int)+ sizeof(Comma)+ size + sizeof(Comma);
				int NoOfGraphObjects = (f.GetLength())/ObjectSize;
				float NoOfGraph =(float)(f.GetLength())/ObjectSize;
				int reminder = (f.GetLength())%ObjectSize ;
				OldVersionPresent=false;
				if(reminder!=0)
				{
				    size= sizeof(CGraphOldData);
					ObjectSize = sizeof(int)+ sizeof(Comma)+ size + sizeof(Comma);
					NoOfGraphObjects = (f.GetLength())/ObjectSize;
					OldVersionPresent=true;
					//f.Close();
					//return false;
				}
				int y=f.GetLength();
				int ID;
				
				for (int GraphNum1 =0;GraphNum1<NoOfGraphObjects;GraphNum1++)
				{
					f.Seek( (ObjectSize*GraphNum1),CFile::begin);
					f.Read(&ID,sizeof(int));
 					if(ID == SelectedWeldId)
					{	
						CGraphData * Graph;CGraphOldData *OldGraph;
						if(!OldVersionPresent)
							Graph= new CGraphData();
						else
							OldGraph= new CGraphOldData();
						f.Read(&Comma,sizeof(char));
						if(!OldVersionPresent)
							f.Read(&Graph->GraphData,size);
						else
							f.Read(OldGraph,size);
						if(!OldVersionPresent)
						{
							switch (GraphNum)
							{
									case 1 : Graph->GraphData.GraphTypeID= AMPLITUDEGRAPH;
										break;
									case 2 : Graph->GraphData.GraphTypeID=COLDISTGRAPH;
										break;
									case 3 : Graph->GraphData.GraphTypeID= FROCEGRAPH;
										break;
									case 4 : Graph->GraphData.GraphTypeID=POWERGRAPH;
										break;
									case 5 : Graph->GraphData.GraphTypeID=FREQGRAPH;
										break;
									case 6 : Graph->GraphData.GraphTypeID = VELOCITYGRAPH;
										break;
							}
							GraphObjects.AddTail(Graph);
	//PrintGraphList.AddTail(Graph);
							break;
						}
						else
						{
							switch (GraphNum)
							{
									case 1 : OldGraph->GraphTypeID= AMPLITUDEGRAPH;
										break;
									case 2 : OldGraph->GraphTypeID=COLDISTGRAPH;
										break;
									case 3 : OldGraph->GraphTypeID= FROCEGRAPH;
										break;
									case 4 : OldGraph->GraphTypeID=POWERGRAPH;
										break;
									case 5 : OldGraph->GraphTypeID=FREQGRAPH;
										break;
									case 6 : OldGraph->GraphTypeID = VELOCITYGRAPH;
										break;
							}
							GraphOldObjects.AddTail(OldGraph);
	//						PrintGraphList.AddTail(Graph);
							break;
						}
					}
				}
			}
			
			f.Close();
		}

	}
	if((GraphObjects.GetCount())||(GraphOldObjects.GetCount()))
		return true;
	else
		return false;

}
/*******************************************************/
/*This Function will Check wether graphs for a		   */
/*selected weld data is present or not.				   */
/*******************************************************/
void CHistoryView::GraphIfPresent(int GraphSelect)
{
	
	CGraphData *object;CGraphOldData *Oldobject;
	if(!OldVersionPresent)
	{
		POSITION pos = GraphObjects.GetHeadPosition();
		while (pos)
		{
			object=GraphObjects.GetNext(pos);
			if (object->GraphData.GraphTypeID == GraphSelect)
			{
				GraphFound=true;
				break;
			}
		}
	}
	else
	{
		POSITION pos = GraphOldObjects.GetHeadPosition();
		while (pos)
		{
			Oldobject=GraphOldObjects.GetNext(pos);
			if (Oldobject->GraphTypeID == GraphSelect)
			{
				GraphFound=true;
				break;
			}
		}
	}
	if (!GraphFound)
		return;

	if(Graph1ID == GraphSelect)
	{
		if(Graph2ID !=0)
		{
			Graph1ID=Graph2ID;
			LastGraphDisplayed=Graph2ID;
			Graph2ID=0;
		}
	}
	else if ((Graph2ID == GraphSelect) )
	{
		
			if(LastGraphDisplayed  != Graph2ID)
			{
				Graph2ID=0;
				return;
			}
		LastGraphDisplayed=Graph1ID;
		Graph2ID=0;
	
	}
		
	else
	{
     if(Graph2ID != 0)
        Graph1ID=Graph2ID;
     Graph2ID=GraphSelect;
     LastGraphDisplayed = Graph2ID;
					
	}
	
}
/***************************************************************/
/*This Function is called by the frame work when the		   */
/* frame window is created.									   */
/***************************************************************/
int CHistoryView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: Add your specialized creation code here
	return 0;
}

/***************************************************************/
/*This Function is called when right button is pressed.		   */
/***************************************************************/
void CHistoryView::Right()
{
	
		if(LeftMostParameter<TotalColoumn-4)
			LeftMostParameter++;
		else
			ERRORBEEP;
   	 	PaintWindow();

}
/***************************************************************/
/*This Function is called when left button is pressed.		   */
/***************************************************************/
void CHistoryView::Left()
{
	if(LeftMostParameter>1)
		LeftMostParameter--;
	else
		ERRORBEEP;
	PaintWindow();
   
}
/***************************************************************/
/*This Function is called when up button is pressed.		   */
/***************************************************************/

void CHistoryView::Up()
{
	if(SelectedWeldData==1)
	{
		if(TopMostData>1)
			TopMostData--;
		else
			ERRORBEEP;
	}

	if(SelectedWeldData>1)
		SelectedWeldData--;
	PaintWindow();
}
/***************************************************************/
/*This Function is called when down button is pressed.	       */
/***************************************************************/
void CHistoryView::Down()
{
	if(SelectedWeldData==MaxCyclePerScreen)
	{
		if((TotalCycle-TopMostData)>=MaxCyclePerScreen)
			TopMostData++;
		else
			ERRORBEEP;
	}
	else if(((SelectedWeldData+TopMostData)<=TotalCycle)&&(SelectedWeldData!=MaxCyclePerScreen))
		SelectedWeldData++;
	else
		ERRORBEEP;
	PaintWindow();
}

/***************************************************************/
/*This Function is called when pageup button is pressed.	   */
/***************************************************************/
void CHistoryView::PageUp()
{
	if(TopMostData>MaxCyclePerScreen)
	{
		TopMostData-=MaxCyclePerScreen;
		SelectedWeldData=1;
	}
		else if(TopMostData!=1)
	{
		TopMostData=1;
		SelectedWeldData=1;
	}
	else
		ERRORBEEP;
	PaintWindow();

}
/***************************************************************/
/*This Function is called when pagedown button is pressed.     */
/***************************************************************/
void CHistoryView::PageDown()
{
	if((TotalCycle>MaxCyclePerScreen)&&(TopMostData+MaxCyclePerScreen <=TotalCycle))
	{
		TopMostData+=MaxCyclePerScreen;
		SelectedWeldData=1;
	}
	else 
		ERRORBEEP;
	PaintWindow();

}
/***************************************************************/
/*This Function is called when exit button is pressed.	       */
/***************************************************************/
void CHistoryView::Exit()
{
	ExitParam=1;
	HSMenu=false;
	HSFlag=false;
	CreateScreenButton();
	BrowsingLevel=	HIERARCHYDAY;	
	CString PreviousPath = FilePath.GetHead();
	int x=0;

	while(x!=2)
	{
		if(PreviousPath.Right(1)==("\\"))
			x++;
		PreviousPath.Delete(PreviousPath.GetLength()-1,1);
	}

	while (GraphObjects.GetCount())
		free(GraphObjects.RemoveHead());

	while (GraphOldObjects.GetCount())
		free(GraphOldObjects.RemoveHead());
		
	while(WeldObjects.GetCount())
		free(WeldObjects.RemoveHead());
	while(WeldObjectsList.GetCount())
		WeldObjectsList.RemoveHead();

	Manual =false;
	BrowsingLevel=HIERARCHYDAY;
	PreparePSList(PreviousPath);
	PageNum =1;
	RecalculateMenu();
	Invalidate(false);
	return ;
			
}
/***************************************************************/
/*This Function is called when graph button is pressed.	       */
/***************************************************************/
void CHistoryView::Graph()
{
	if(ExitParam)
		return;
		
	if(!ReadGraph())
	{
		NoValidGraph=true;
		ShowMessageScreen("No Valid Graph Data");
		return;
	}
	else
	{
		BrowsingLevel=GRAPHS;
		GraphParam=1;
		CreateScreenButton();
		delete ButtonGraph;
		delete Buttonprint;
		GraphFileSelect=1;
		Invalidate(false);
	}

}
/***************************************************************/
/*This Function is called when AmpGraph button is pressed.	   */
/***************************************************************/
void CHistoryView::AmpGraph()
{
	GraphSelect=AMPLITUDEGRAPH;
	GraphIfPresent(GraphSelect);
	if (!GraphFound)
	{
		ERRORBEEP;
		return;
	}
	GraphFound=false;
	PaintWindow();
}
/***************************************************************/
/*This Function is called when ColdistGraph button is pressed.  */
/***************************************************************/
void CHistoryView::ColDistGraph()
{	
	
	GraphSelect=COLDISTGRAPH;
	GraphIfPresent(GraphSelect);
	if (!GraphFound)
	{
		ERRORBEEP;
		return;
	}
	GraphFound=false;
	PaintWindow();
}
/***************************************************************/
/*This Function is called when forcegraph button is pressed.   */
/***************************************************************/
void CHistoryView::ForceGraph()
{
	GraphSelect=FROCEGRAPH;
	GraphIfPresent(GraphSelect);
	if (!GraphFound)
	{
		ERRORBEEP;
		return;
	}
	GraphFound=false;
	PaintWindow();
}
/***************************************************************/
/*This Function is called when VelocityGraph button is pressed.*/
/***************************************************************/
void CHistoryView::VelocityGraph()
{
	
	GraphSelect=VELOCITYGRAPH;
	GraphIfPresent(GraphSelect);
	if (!GraphFound)
		{
		ERRORBEEP;
		return;
	}
	GraphFound=false;
	PaintWindow();
}
/***************************************************************/
/*This Function is called when FreqGraph button is pressed.	   */
/***************************************************************/
void CHistoryView::FreqGraph()
{
	GraphSelect=FREQGRAPH;
	GraphIfPresent(GraphSelect);
	if (!GraphFound)
	{
		ERRORBEEP;
		return;
	}
	GraphFound=false;
	PaintWindow();
}
/***************************************************************/
/*This Function is called when PowerGraph button is pressed.   */
/***************************************************************/
void CHistoryView::PowerGraph()
{
	GraphSelect=POWERGRAPH;
	GraphIfPresent(GraphSelect);
	if (!GraphFound)
	{
		ERRORBEEP;
		return;
	}
	GraphFound=false;
	PaintWindow();
}
/***************************************************************/
/*This Function is called when exitgraph button is pressed.	   */
/***************************************************************/
void CHistoryView::ExitGraph()
{
	ExitGraphParam=1;
	GraphParam = 0;
	ExitParam=0;
	BrowsingLevel=WELDDATA;
	CreateScreenButton();
	Invalidate(false);
	GraphSelect=0;
}
/*******************************************************************/
/*This function will draw text with apropriate color and texture . */
/*******************************************************************/
void CHistoryView::DrawText(CDC *pDC, int color,bool LargeFont,
							 const CRect &rect, const CString &text,bool Center_Text)
{	

	CFont *OldFont;//font,

	if(LargeFont)
		OldFont=pDC->SelectObject(&BigFont);
	else
		OldFont=pDC->SelectObject(&SmallFont);

	pDC->SetTextColor(Color_Array[color]);
	pDC->SetBkMode(TRANSPARENT);
	CSize size = pDC->GetTextExtent(text);

	if(Center_Text==true)
		size.cx = rect.left + (rect.Width() - size.cx) / 2;
	else
		size.cx = rect.left;

	size.cy = rect.top + (rect.Height() - size.cy) / 2;
	pDC->ExtTextOut(size.cx, size.cy,ETO_OPAQUE   ,NULL, text,NULL);
	pDC->SelectObject(OldFont);
}

/***************************************************************/
/*This Function draws all the screen buttons.			       */
/***************************************************************/
void CHistoryView::CreateScreenButton()
{
	 if(BrowsingLevel==GRAPHS)
	 {
		  delete ButtonLeft;
		  delete ButtonRight;
		  delete ButtonUp;
		  delete ButtonDown;
		  delete ButtonPageUp;
		  delete ButtonPageDown;
		  delete ButtonExit;
	 }
	
	if(ExitParam)
	{
		 while(WeldObjects.GetCount())
			free(WeldObjects.RemoveHead());
		 while(WeldObjectsList.GetCount())
			WeldObjectsList.RemoveHead();

		 delete ButtonLeft;
		 delete ButtonRight;
		 delete ButtonUp;
		 delete ButtonDown;
		 delete ButtonPageUp;
		 delete ButtonPageDown;
		 delete ButtonExit;

		 if(!GraphParam)
		 {
			 delete ButtonGraph;
			 delete Buttonprint;
		 }

		 ExitParam=0;
		 FileOpenParam=0;
		
	 }
	if (ExitGraphParam)
	{
		while (GraphObjects.GetCount())
			free(GraphObjects.RemoveHead());
		while (GraphOldObjects.GetCount())
			free(GraphOldObjects.RemoveHead());
		Manual =false;
		delete ButtonGraphAmp;
		delete ButtonGraphColDist;
		delete ButtonGraphForce;
		delete ButtonGraphVelocity;
		delete ButtonGraphFreq;
		delete ButtonGraphPower;
		delete ButtonGraphExit;
		delete ButtonprintGraph;
		ExitGraphParam = 0;
		Invalidate(false);
		
	}
	

	if(FileOpenParam && (!GraphParam))
	{
		     
	ButtonLeft =new CBitmapButton();
	ButtonLeft->Create(NULL,BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP | BS_OWNERDRAW   
		,Left_Rect,this,ID_BN_LEFT);
	ButtonLeft->LoadBitmaps(IDB_Left1,IDB_Left2, 0, 0);

	ButtonRight =new CBitmapButton();
	ButtonRight->Create(NULL,BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP | BS_OWNERDRAW   
		,Right_Rect,this,ID_BN_RIGHT);
	ButtonRight->LoadBitmaps(IDB_Right1,IDB_Right2, 0, 0);

	ButtonUp =new CBitmapButton();
	ButtonUp->Create(NULL,BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP  | BS_OWNERDRAW 
		,Up_Rect ,this,ID_BN_UP);
	ButtonUp->LoadBitmaps(IDB_Up1,IDB_Up2, 0, 0); 

	ButtonDown =new CBitmapButton();
	ButtonDown->Create(NULL,BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP | BS_OWNERDRAW    
		,Down_Rect ,this,ID_BN_DOWN);
	ButtonDown->LoadBitmaps(IDB_Down1,IDB_Down2, 0, 0); 

	ButtonPageUp =new CBitmapButton();
	ButtonPageUp->Create(NULL,BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP  | BS_OWNERDRAW 
		,PageUp_Rect ,this,ID_BN_PAGEUP);
	ButtonPageUp->LoadBitmaps(IDB_PageUp1,IDB_PageUp2, 0, 0); 

	ButtonPageDown =new CBitmapButton();
	ButtonPageDown->Create(NULL,BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP | BS_OWNERDRAW    
		,PageDown_Rect ,this,ID_BN_PAGEDOWN);
	ButtonPageDown->LoadBitmaps(IDB_PageDown1,IDB_PageDown2, 0, 0);

	ButtonExit =new CButtons();
	ButtonExit->Create(_T("Exit"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP   
		,Exit_Rect,this,ID_BN_EXIT);
	ButtonExit->SetButtonStyle(BS_OWNERDRAW );

	ButtonGraph =new CButtons();
	ButtonGraph->Create(_T("Graph"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP   
		,Graph_Rect,this,ID_BN_GRAPH);
	ButtonGraph->SetButtonStyle(BS_OWNERDRAW );

	Buttonprint=new CButtons();
	Buttonprint->Create(_T("Print"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP   
		,PrintSelect_Rect,this,ID_BN_PRINT);
	Buttonprint->SetButtonStyle(BS_OWNERDRAW );
	}
	
	if(BrowsingLevel==GRAPHS)
	{

		ButtonGraphAmp =new CButtons();
		ButtonGraphAmp->Create(_T("Amplitude"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP   
			,AmpGraph_Rect,this,ID_BN_GRAPHAMP);
		ButtonGraphAmp->SetButtonStyle(BS_OWNERDRAW );
	
		ButtonGraphColDist =new CButtons();
		ButtonGraphColDist->Create(_T("Col Distance"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP   
			,ColDistGraph_Rect,this,ID_BN_GRAPHCOLDIST);
		ButtonGraphColDist->SetButtonStyle(BS_OWNERDRAW );

		ButtonGraphForce=new CButtons();
		ButtonGraphForce->Create(_T("Force"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP   
			,ForceGraph_Rect,this,ID_BN_GRAPHFORCE);
		ButtonGraphForce->SetButtonStyle(BS_OWNERDRAW );

		ButtonGraphVelocity =new CButtons();
		ButtonGraphVelocity->Create(_T("Velocity"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP   
			,VelGraph_Rect,this,ID_BN_VELGRAPH);
		ButtonGraphVelocity->SetButtonStyle(BS_OWNERDRAW );

		ButtonGraphFreq =new CButtons();
		ButtonGraphFreq->Create(_T("Frequency"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP   
			,FreqGraph_Rect,this,ID_BN_FREQGRAPH);
		ButtonGraphFreq->SetButtonStyle(BS_OWNERDRAW );

		ButtonGraphPower =new CButtons();
		ButtonGraphPower->Create(_T("Power"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP   
			,PowerGraph_Rect,this,ID_BN_POWERGRAPH);
		ButtonGraphPower->SetButtonStyle(BS_OWNERDRAW );

		ButtonGraphExit =new CButtons();
		ButtonGraphExit->Create(_T("Exit"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP   
			,Graph_Exit_Rect,this,ID_BN_EXITGRAPH);
		ButtonGraphExit->SetButtonStyle(BS_OWNERDRAW );

		ButtonprintGraph=new CButtons();
		ButtonprintGraph->Create(_T("Print"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP   
			,PrintSelect_Rect,this,ID_BN_PRINT_GRAPH);
		ButtonprintGraph->SetButtonStyle(BS_OWNERDRAW );
		

	}
	if((BrowsingLevel== HIERARCHYHSDATA))
	{
		
		CButtons * TempPtr =new  CButtons();
		ScreenObjects.AddTail(TempPtr);
		TempPtr->Create(_T("Exit"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP ,
			EXITRECT,this,ID_EXIT);
		TempPtr->SetButtonStyle(BS_OWNERDRAW );
		TempPtr->ID=ID_EXIT;

      ButtonprintHSData=new CButtons();
		ButtonprintHSData->Create(_T("Print"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP   
			,PrintSelect_Rect,this,ID_BN_PRINT_HSDATA);
		ButtonprintHSData->SetButtonStyle(BS_OWNERDRAW );
	}
	if(BrowsingLevel==HIERARCHYHSGRAPH)
	{
		ScanA_Present=HS1_Present;
		ScanB_Present=HS2_Present;
		ScanC_Present=HS3_Present;
		CString text;
		
		if(ScanA_On)
		text="Scan A->on";
		else
		text="Scan A->off";
		ButtonScanA= new CButtons();
		ButtonScanA->Create(text,BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP ,HS_ScanA_Rect,this,ID_ScanA);
		ButtonScanA->SetButtonStyle(BS_OWNERDRAW );
		ButtonScanA->ID=ID_ScanA;
		
		
		if(ScanB_On)
		text="Scan B->on";
		else
		text="Scan B->off";
		ButtonScanB =new CButtons();
		ButtonScanB->Create(text,BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP ,HS_ScanB_Rect,this,ID_ScanB);
		ButtonScanB->SetButtonStyle(BS_OWNERDRAW );
		ButtonScanB->ID=ID_ScanB;
		
		if(ScanC_On)
		text="Scan C->on";
		else
		text="Scan C->off";
		ButtonScanC  =new CButtons();
		ButtonScanC->Create(text,BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP ,HS_ScanC_Rect,this,ID_ScanC);
		ButtonScanC->SetButtonStyle(BS_OWNERDRAW );
		ButtonScanC->ID=ID_ScanC;
		
		ButtonScanExit  =new CButtons();
		ScreenObjects.AddTail(ButtonScanExit);
		ButtonScanExit->Create(_T("Exit"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP ,ScanExit_Rect,this,ID_EXIT);
		ButtonScanExit->SetButtonStyle(BS_OWNERDRAW );
		ButtonScanExit->ID=ID_EXIT;

      ButtonprintHSGraph=new CButtons();
		ButtonprintHSGraph->Create(_T("Print"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP   
			,PrintSelect_Rect,this,ID_BN_PRINT_HSGRAPH);
		ButtonprintHSGraph->SetButtonStyle(BS_OWNERDRAW );
		
	}
	
	
}
/***************************************************************/
/*The framework calls this member function when the user	   */
/*clicks on any menu item.								       */
/***************************************************************/
BOOL CHistoryView::OnCommand(WPARAM wParam, LPARAM lParam) 
{

	union {
			short Word[2];
			int ParamValue;
		}u;

	u.ParamValue=wParam;
	short ObjectId = u.Word[0];
	short Message = u.Word[1];



	if(ScreenObjects.GetCount())
	{
		/* Check Click On Next, Back and Exit Button */
		if(ObjectId ==ID_NEXT)
		{
			PageNum++;
			PageNumList.AddHead(PageNum);
			RecalculateMenu();
			Invalidate(false);
			return 0;
		}

		if(ObjectId ==ID_BACK)
		{
			PageNum--;
			PageNumList.RemoveHead();
			RecalculateMenu();
			Invalidate(false);
			return 0;
		}

		if(ObjectId ==ID_EXIT)
		{
			CString PreviousPath = FilePath.GetHead();
			int x=0;
			
			while(x!=2)
			{
				if(PreviousPath.Right(1)==("\\"))
					x++;
				PreviousPath.Delete(PreviousPath.GetLength()-1,1);
				
			}
			
			if(BrowsingLevel==HIERARCHYDAY)
			{
				BrowsingLevel=HIERARCHYYEARMONTH;
				PreparePSList(PreviousPath);
				/* Getting Previous page number */
				PageNum =PageNumList.GetHead();//PageNumList.RemoveHead();
				RecalculateMenu();
				Invalidate(false);
				return 0;
			}
			if(BrowsingLevel==HIERARCHYYEARMONTH)
			{
				DrawFirstScreen();
				return 0;
			}
			if(BrowsingLevel==HIERARCHYHSDATA)
			{
            while(GraphDataList.GetCount())
		         delete GraphDataList.RemoveHead();
			while(GraphOldDataList.GetCount())
		         delete GraphOldDataList.RemoveHead();
            delete ButtonprintHSData;
				BrowsingLevel=HIERARCHYHSFOLDER;
				PrepareHSList(PreviousPath);
				HS1_Present=false,HS2_Present=false,HS3_Present=false;
				/* Getting Previous page number */
				PageNum =PageNumList.GetHead();//PageNumList.RemoveHead();
				RecalculateMenu();
				Invalidate(false);
				return 0;
			}
			if(BrowsingLevel==HIERARCHYHSFOLDER)
			{
				DrawFirstScreen();
				HSMenu=false;
				return 0;
			}
			if(BrowsingLevel==HIERARCHYHSGRAPH)
			{
				BrowsingLevel=HIERARCHYHSFOLDER;
				delete ButtonScanA;
				delete ButtonScanB;
				delete ButtonScanC;
				delete ButtonprintHSGraph;
				while(GraphDataList.GetCount())
		         delete GraphDataList.RemoveHead();
				while(GraphOldDataList.GetCount())
		         delete GraphOldDataList.RemoveHead();
				while(ScreenObjects.GetCount()>0)
					delete ScreenObjects.RemoveHead();
				HS1_Present=false,HS2_Present=false,HS3_Present=false;
				HSFlag=false;
				PrepareHSList(PreviousPath);
				/* Getting Previous page number */
				PageNum =PageNumList.GetHead();//PageNumList.RemoveHead();
				RecalculateMenu();
				Invalidate(false);
				return 0;
			}

		}
		POSITION POS = ScreenObjects.GetHeadPosition();
		int i=ScreenObjects.GetCount();
		while(POS)
		{
			CButtons *ScrButton = ScreenObjects.GetNext(POS);
			/* Processing the clicked button */
			if(ObjectId==ScrButton->ID)
			{	
				if(BrowsingLevel==HIERARCHYHSFOLDER)
				{
					if(ObjectId== (0 + 1))
					{
						BrowsingLevel= HIERARCHYHSDATA;
						while(ScreenObjects.GetCount()>0)
							delete ScreenObjects.RemoveHead();
						CreateScreenButton();

					}
					else if(ObjectId == (1 + 1))
					{
						ScanA_On =true;
						ScanB_On =true;
						ScanC_On =true;
						if(!CompareGraph_and_Data())
						{
						//	DrawFirstScreen();
							return 0;
						}
						HSFlag=true;
						while(ScreenObjects.GetCount()>0)
							delete ScreenObjects.RemoveHead();
						BrowsingLevel= HIERARCHYHSGRAPH;
						
						CreateScreenButton();
					}
					
					Invalidate(false);
					return 0;

				}
				
				CString SelFilePath= FilePath.GetAt(FilePath.FindIndex((ObjectId - 1)+((PageNum-1)*8)));
				CString SelFileName= FilePath.GetAt(FileName.FindIndex((ObjectId - 1)+((PageNum-1)*8)));
				if(BrowsingLevel==HIERARCHYYEARMONTH)
				{
					BrowsingLevel=HIERARCHYDAY;

					if(BrowsingLevel == HIERARCHYDAY)
						YearMonthName=SelFileName;

					PreviousFileName=SelFileName.SpanExcluding(_T("-"));
				
				
					if(PreparePSList(SelFilePath))
					{
						PageNum =1;
						PageNumList.AddHead(PageNum);
						RecalculateMenu();
						Invalidate(false);
						return 0;
					}
					else
					{
						BrowsingLevel=HIERARCHYYEARMONTH;
						/*show message screen*/
						ShowMessageScreen("No Day Folder Present");
						return 0;
					}
				}
				else if(BrowsingLevel==HIERARCHYDAY)
				{
					BrowsingLevel=WELDDATA;

					DataFolder=SelFilePath;//GetFolderPath();

					if(!ReadData())
					{
						ShowMessageScreen("No Valid Weld Data");
						BrowsingLevel=HIERARCHYDAY;
						return 0;
					}
					else
					{	
						/*delete all buttons*/
						while(ScreenObjects.GetCount())
							delete ScreenObjects.RemoveHead();
						return 0;

					}
				}
				
			}

		}
	}
	return CView::OnCommand(wParam, lParam);

}
/***************************************************************/
/*This function takes the folder name as argument and tests	   */
///*wether that folder contains powersupply folder or not.	   */								       */
/***************************************************************/
bool CHistoryView::ValidFolder(CString FileName)
{
	if((FileName==".") ||(FileName==".."))
		return false;

	switch(View->BrowsingLevel)
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
					if(!((FileName.Mid(i,1)[0]<=0x39) && (FileName.Mid(i,1)[0]>=0x30)))
						return false;
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

/********************************************************************************************/	
/*  This function checks the hierarchy level of the USB Folder and creates the string to be	*/
/* displayed. If Hierarchy level is one, it displayes the name as it is.					*/
/* If Level is two it checks for the month in the string and will add appropriate string	*/
/* to get display name.																		*/
/* If hierarchy level is three it then combines the day stringwith its month string to		*/
/* get the display name																		*/
/*********************************************************************************************/
CString CHistoryView::GetDiaplayName(CString Name)
{

	CString DisplayName=Name;

	CString Str_Jan[] = {
			 "January",
			 "Januar",
			 "Enero",
			 "Gennaio",
			 "Janvier",
			 L"\x4e00\x6708\x00",
			 L"\x4e00\x6708\x00",
			 L"\xff11\x6708\x00",
			 L"\x0031\xc6d4\x00" };

	CString Str_Feb[] = {
			 "February",
			 "Februar",
			 "Febrero",
			 "Febbraio",
			 "Fevrier",
			 L"\x4e8c\x6708\x0",
			 L"\x4e8c\x6708\x0",
			 L"\xff12\x6708\x0",
			 L"\x0032\xc6d4\x0" };

	CString Str_March[] = {
			 "March",
			 "Maerz",
			 "Marzo",
			 "Marzo",
			 "Mars",
			 L"\x4e09\x6708\x0",
			 L"\x4e09\x6708\x0",
			 L"\xff13\x6708\x0",
			 L"\x0033\xc6d4\x0" };

	CString Str_April[] = {
			 "April",
			 "April",
			 "Abril",
			 "Aprile",
			 "Avril",
			 L"\x56db\x6708\x0",
			 L"\x56db\x6708\x0",
			 L"\xff14\x6708\x0",
			 L"\x0034\xc6d4\x0" };

	CString Str_May[] = {
			 "May",
			 "Mai",
			 "Mayo",
			 "Maggio",
			 "Mai",
			 L"\x4e94\x6708\x0",
			 L"\x4e94\x6708\x0",
			 L"\xff15\x6708\x0",
			 L"\x0035\xc6d4\x0" };

	CString Str_June[] = {
			 "June",
			 "Juni",
			 "Junio",
			 "Giugno",
			 "Juin",
			 L"\x516d\x6708\x0",
			 L"\x516d\x6708\x0",
			 L"\xff16\x6708\x0",
			 L"\x0036\xc6d4\x0" };

	CString  Str_July[] = {
			 "July",
			 "Juli",
			 "Julio",
			 "Luglio",
			 "Juillet",
			 L"\x4e03\x6708\x0",
			 L"\x4e03\x6708\x0",
			 L"\xff17\x6708\x0",
			 L"\x0037\xc6d4\x0" };

	CString Str_Aug[] = {
			 "August",
			 "August",
			 "Agosto",
			 "Agosto",
			 "Aout",
			 L"\x516b\x6708\x0",
			 L"\x516b\x6708\x0",
			 L"\xff18\x6708\x0",
			 L"\x0038\xc6d4\x0" };

	 CString Str_Sept[] = {
			 "September",
			 "September",
			 "Septiembre",
			 "Settembre",
			 "Septembre",
			 L"\x4e5d\x6708\x0",
			 L"\x4e5d\x6708\x0",
			 L"\xff19\x6708\x0",
			 L"\x0039\xc6d4\x0" };

	CString Str_Oct[] = {
			 "October",
			 "Oktober",
			 "Octubre",
			 "Ottobre",
			 "Octobre",
			 L"\x5341\x6708\x0",
			 L"\x5341\x6708\x0",
			 L"\xff11\xff10\x6708\x0",
			 L"\x0031\x0030\xc6d4\x0" };

	 CString Str_Nov[] = {
			 "November",
			 "November",
			 "Noviembre",
			 "Novembre",
			 "Novembre",
			 L"\x5341\x4e00\x6708\x0",
			 L"\x5341\x4e00\x6708\x0",
			 L"\xff11\xff11\x6708\x0",
			 L"\x0031\x0031\xc6d4\x0" };

	CString Str_Dec[] = {
			 "December",
			 "Dezember",
			 "Diciembre",
			 "Dicembre",
			 "Decembre",
			 L"\x5341\x4e8c\x6708\x0",
			 L"\x5341\x4e8c\x6708\x0",
			 L"\xff11\xff12\x6708\x0",
			 L"\x0031\x0032\xc6d4\x0" };

	
	switch(View->BrowsingLevel)
	{
		case BROWSING:
		{
			DisplayName=Name;
			break;
		}

		case HIERARCHYYEARMONTH:
		{
			char Month[3];
			Month[0]= (char)Name.GetAt(5);
			Month[1]=(char)Name.GetAt(6);
			Month[2]='\0';	
			int MONTH = atoi(&Month[0]);
			CString Year = Name.Left(4);
			switch(MONTH)
			{
				case JAN:
					DisplayName= Str_Jan[0] + "-"+Year+">";
				break;

				case FEB:
					DisplayName= Str_Feb[0] + "-"+Year+">";
				break;
			
				case MAR:
					DisplayName= Str_March[0] + "-"+Year+">";
				break;
			
				case APR:
					DisplayName= Str_April[0] + "-"+Year+">";
				break;
			
				case MAY:
					DisplayName= Str_May[0] + "-"+Year+">";
				break;
			
				case JUN:
					DisplayName= Str_June[0] + "-"+Year+">";
				break;
			
				case JUL:
 					DisplayName= Str_July[0] + "-"+Year+">";
				break;
			
				case AUG:
					DisplayName= Str_Aug[0] + "-"+Year+">";
				break;
			
				case SEP:
					DisplayName= Str_Sept[0] + "-"+Year+">";
				break;
			
				case OCT:
					DisplayName= Str_Oct[0] + "-"+Year+">";
				break;
			
				case NOV:
					DisplayName= Str_Nov[0] + "-"+Year+">";
				break;
			
				case DEC:
					DisplayName= Str_Dec[0] + "-"+Year+">";
				
				break;
			}
			break;
		}
		
		case HIERARCHYDAY:
		{
			DisplayName= PreviousFileName + " " + Name;
			break;
		}
		case HIERARCHYHSDATA:
		{
			DisplayName=Name;
			break;
		}
		default:
		{
			//DisplayName=Name;
			return Name;//DisplayName;
			break;
		}
	}return DisplayName;
}

/****************************************************************/
/* This function useed to retrieve the folder path of the       */
/*selected folder.												*/
/****************************************************************/

CString CHistoryView::GetFolderPath()
{
	int SelectedItem ;
	SelectedItem =ListBox->GetCurSel();  /* returns Zero base index*/
	CString SelFilePath;
	POSITION POS = FilePath.GetHeadPosition();

	for(int i=0;i<=SelectedItem;i++)
		SelFilePath = FilePath.GetNext(POS);

	return SelFilePath;
}

/****************************************************************/
/* This function draws the first screen with branson logo.		*/
/****************************************************************/
void CHistoryView::DrawFirstScreen() 
{ 	
	FilePath.RemoveAll();
	FileName.RemoveAll();

	while (GraphObjects.GetCount())
		free(GraphObjects.RemoveHead());

	while (GraphOldObjects.GetCount())
		free(GraphOldObjects.RemoveHead());
		
	while(WeldObjects.GetCount())
		free(WeldObjects.RemoveHead());

	while(WeldObjectsList.GetCount())
			WeldObjectsList.RemoveHead();

	while(ScreenObjects.GetCount())
			delete ScreenObjects.RemoveHead();


	if(BrowsingLevel==HIERARCHYYEARMONTH)
	{
		FilePath.RemoveAll();
		FileName.RemoveAll();

			while(ScreenObjects.GetCount())
				delete ScreenObjects.RemoveHead();

		BrowsingLevel=BRANSONLOGO;
	}
	if(BrowsingLevel==HIERARCHYHSFOLDER)
	{
		FilePath.RemoveAll();
		FileName.RemoveAll();

		while(ScreenObjects.GetCount())
			delete ScreenObjects.RemoveHead();
	
		BrowsingLevel=BRANSONLOGO;
	}
	if(BrowsingLevel==HIERARCHYHSGRAPH)
	{
		delete ButtonScanA;
		delete ButtonScanB;
		delete ButtonScanC;
      delete ButtonprintHSGraph;
		HSFlag=false;
	}
	if(BrowsingLevel==WELDDATA)
	{
		FilePath.RemoveAll();
		FileName.RemoveAll();

			 while(WeldObjects.GetCount())
				free(WeldObjects.RemoveHead());
			 while(WeldObjectsList.GetCount())
				WeldObjectsList.RemoveHead();
			 delete ButtonLeft;
			 delete ButtonRight;
			 delete ButtonUp;
			 delete ButtonDown;
			 delete ButtonPageUp;
			 delete ButtonPageDown;
			 delete ButtonExit;

			 if(!GraphParam)
			 {
				 delete Buttonprint;
				 delete ButtonGraph;
			 }

			 ExitParam=0;
			 FileOpenParam=0;
	 }

	if(BrowsingLevel==GRAPHS)
	{
						
		FilePath.RemoveAll();
		FileName.RemoveAll();
		Manual =false;
		while (GraphObjects.GetCount())
			free(GraphObjects.RemoveHead());
		
		while (GraphOldObjects.GetCount())
			free(GraphOldObjects.RemoveHead());

		while(WeldObjects.GetCount())
			free(WeldObjects.RemoveHead());
		while(WeldObjectsList.GetCount())
			WeldObjectsList.RemoveHead();
		delete ButtonGraphAmp;
		delete ButtonGraphColDist;
		delete ButtonGraphForce;
		delete ButtonGraphVelocity;
		delete ButtonGraphFreq;
		delete ButtonGraphPower;
		delete ButtonGraphExit;
		delete ButtonprintGraph;
		GraphParam=0;
		FileOpenParam=0;
		ExitGraphParam = 0;
		
	}
	if(BrowsingLevel==HIERARCHYHSDATA)
	{
		delete ButtonprintHSData;
	}
	BrowsingLevel=BRANSONLOGO;
	Invalidate(false);
}
/****************************************************************/
/* This function is called to manage timer.						*/
/****************************************************************/
void CHistoryView::OnTimer(UINT nIDEvent) 
{

	KillTimer(MESSAGE_TIMER);
	View->EnableWindow(TRUE);
	Invalidate(false);
	DisableFlag=false;
	CView::OnTimer(nIDEvent);
}

/****************************************************************/
/* This function is called to show message screen when required	*/
/* arg 1: Message to be shown.									*/
/****************************************************************/
void CHistoryView::ShowMessageScreen(CString Message)
{
	CDC *pDC=View->GetDC();
	DisableFlag=true;
	/*Drawing Message Rectangle in specified color*/
	CRect rect(MESSAGESCRN_BLACKRECT);
	pDC->FillSolidRect(rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,COLORBLACK);
	rect=MESSAGESCRNRECT;
	pDC->FillSolidRect(rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,COLORBLUE);

	/*Drawing Message Text*/
	DrawText(pDC,11 ,true, MESSAGESCRNRECT,Message,true);
	View->ReleaseDC(pDC);
	View->EnableWindow(FALSE);
	View->SetTimer(MESSAGE_TIMER,MESSAGESCRNTIME,NULL);
}
/****************************************************************/
/* This function Draws the menu according to the				*/
/*folders presents present inside a powersupply folder.			*/
/****************************************************************/

void CHistoryView::RecalculateMenu()
{
	
	while(ScreenObjects.GetCount())
		delete ScreenObjects.RemoveHead();
	
	int NoOfButtons =0, x , i;
	CRect rect;
	POSITION POS = FileName.GetHeadPosition();
	int FirstCol_left_coordinate=FIRSTCOLOUMN_X;
	int SecCol_left_coordinate=SECONDCOLOUMN_X;
	int top_coordinate=TOPCORDINATE;
	int ButtonHeight=MENUBUTTONHIEGHT;

	for(x=1;x<PageNum;x++)
		for(i=0;i<8;i++)
			FileName.GetNext(POS);


	bool SingleColumn =false;

		if(FileName.GetCount()<=4)
			SingleColumn =true;
	if(HSMenu)
	{
		FileName.GetNext(POS);
	}

	for(i=0;i<8;i++)
	{	
		if(!HSMenu)
		{
			if(!POS)
				break;
		}
		else if(i >=2)
			break;
		CString TempStr;
		NoOfButtons++;
		if(!HSMenu)
			TempStr= FileName.GetNext(POS);
		else
		{
			if(i == 0)
				TempStr= "Compare Data";
			else
				TempStr ="Compare Graph";

		}

		CButtons * TempPtr =new  CButtons();
	
		ScreenObjects.AddTail(TempPtr);
		if(!SingleColumn)
		{
			if((i%2)!=0)
			{
				rect = CRect(SecCol_left_coordinate,top_coordinate, SecCol_left_coordinate + 220, 
										top_coordinate + ButtonHeight);
				top_coordinate+=MENUBUTTONGAP;
			}
			else
				rect = CRect(FirstCol_left_coordinate,top_coordinate, FirstCol_left_coordinate + 220, 
										top_coordinate + ButtonHeight);
		}
		else
		{
			rect = CRect(220,top_coordinate, 220 + 220, 
										top_coordinate + ButtonHeight);
				top_coordinate+=MENUBUTTONGAP;
		}

		TempPtr->Create(TempStr,BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP ,
			rect,this,(i + 1));//0 is not working with vs2010 and 2012
			TempPtr->SetButtonStyle(BS_OWNERDRAW );
		TempPtr->ID= (i + 1);//MyTempId;
	
	}
	if(POS) /* Add Next Button to the menu*/
	{
		CButtons * TempPtr =new  CButtons();
		ScreenObjects.AddTail(TempPtr);
		TempPtr->Create(_T(">>"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP ,
			NEXTRECT,this,ID_NEXT);
		TempPtr->SetButtonStyle(BS_OWNERDRAW );
		TempPtr->ID=ID_NEXT;
	}
	
		
	if(PageNum>1) /* Add Back Button*/
	{
		CButtons * TempPtr =new  CButtons();
		ScreenObjects.AddTail(TempPtr);
		TempPtr->Create(_T("<<"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP ,
			BACKRECT,this,ID_BACK);
		TempPtr->SetButtonStyle(BS_OWNERDRAW );
		TempPtr->ID=ID_BACK;
	}

		/* Adding Exit Button*/
		CButtons * TempPtr =new  CButtons();
		ScreenObjects.AddTail(TempPtr);
		TempPtr->Create(_T("Exit"),BS_DEFPUSHBUTTON |WS_VISIBLE|WS_CHILD|WS_GROUP|WS_TABSTOP ,
			EXITRECT,this,ID_EXIT);
		TempPtr->SetButtonStyle(BS_OWNERDRAW );
		TempPtr->ID=ID_EXIT;
}

/****************************************************************/
/* This function prepare list of folders present in	PowerSupply */
/*folder.														*/
/****************************************************************/
bool CHistoryView::PreparePSList(CString SelFilePath)
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
		View->FilePath.RemoveAll();
		View->FileName.RemoveAll();
		ListCreated = true;
		View->FilePath.AddTail(DirSpec+FindFileData.cFileName);
		View->FileName.AddTail(GetDiaplayName(FindFileData.cFileName));
	}

	while(FindNextFile(hFind, &FindFileData) != 0) 
    {
        if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&ValidFolder(FindFileData.cFileName))
		{
			if(!ListCreated)
			{
				View->FilePath.RemoveAll();
				View->FileName.RemoveAll();
				ListCreated = true;
			}
			
			View->FilePath.AddTail(DirSpec+FindFileData.cFileName);
			View->FileName.AddTail(GetDiaplayName(FindFileData.cFileName));
			
		}
	}
	
	return ListCreated;
}

/****************************************************************/
/* This function prepare list of folders present in	Horn Scan */
/*folder.														             */
/****************************************************************/
bool CHistoryView::PrepareHSList(CString SelFilePath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
  
	CString DirSpec;  
	DirSpec=SelFilePath+_T("\\Horn Signature");
	hFind = FindFirstFile(DirSpec, &FindFileData);
	DirSpec.Delete(DirSpec.GetLength()-1,1);

	if (hFind == INVALID_HANDLE_VALUE)  
		return false;

	bool ListCreated =false;

	if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY ))//&&ValidFolder(FindFileData.cFileName))
	{
		View->FilePath.RemoveAll();
		View->FileName.RemoveAll();
		ListCreated = true;
		View->FilePath.AddTail(DirSpec+FindFileData.cFileName);
		View->FileName.AddTail(GetDiaplayName(FindFileData.cFileName));
	}

	while(FindNextFile(hFind, &FindFileData) != 0) 
    {
        if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY ))//&&ValidFolder(FindFileData.cFileName))
		{
			if(!ListCreated)
			{
				View->FilePath.RemoveAll();
				View->FileName.RemoveAll();
				ListCreated = true;
			}
			
			View->FilePath.AddTail(DirSpec+FindFileData.cFileName);
			View->FileName.AddTail(GetDiaplayName(FindFileData.cFileName));
			
		}
	}
	
	return ListCreated;
}



/****************************************************************/
/* This function opens powersupply folder and shows is content. */
/****************************************************************/
void CHistoryView::OnOpenPSNew() 
{
	HSMenu=false;

	DrawFirstScreen() ;
	int y;

	if(!FileCreated)
	{
		CBrowse Dialog;
		FileCreated = false;
		y=	Dialog.DoModal();
	}
	
	if(y==1)        //ok button
	{
		PageNum=1; // coz first page is to be displayed at the first time
		PageNumList.AddHead(PageNum);
		RecalculateMenu();
		Invalidate(false);
	}

}
/****************************************************************/
/* This function draws the welddata in device context.			*/
/****************************************************************/
void CHistoryView::DrawWeldData(CDC *pDC)
{
	CFont *OldFont;
	OldFont=pDC->SelectObject(&SmallFont);

	int X1 = LINE_END_X;
	int Y1 =LINE_Y;
	int Width =ParamRectWidth;
	int Height = LINE_GAP;
	CPen *oldPen;
	CPen NewPen;
	NewPen.CreatePen(PS_SOLID,2,COLORBLACK);
	oldPen = pDC->SelectObject(&NewPen);

	pDC->MoveTo(LINE_START_X,Y1);
	pDC->LineTo(X1,Y1);
	pDC->SelectObject(oldPen);
	NewPen.DeleteObject();

	pDC->SetTextColor(COLORBLACK);

	if(WeldObjects.GetCount())
	{
		POSITION pos = WeldObjects.GetHeadPosition();
		int LineNo=1;
		int TotalCyclesDrawn=0;
		for(int CurrentPos=1;CurrentPos<TopMostData;CurrentPos++)
			WeldObjects.GetNext(pos);

	 pDC->FillSolidRect(8,(HISTORY_TBL_START_Y-8+LINE_GAP*(SelectedWeldData+3)),
							  (HISTORY_TBL_START_X + 5 * ParamRectWidth - 12),
							  LINE_GAP,COLORGREEN);
		while(pos)
		{	
			if(TotalCyclesDrawn==MaxCyclePerScreen)
				break;
			CWeldData * Obj = WeldObjects.GetNext(pos);
			if(LineNo==SelectedWeldData)
			{
				SelectedDataUnit=Obj->Units;
				SelectedWeldId=Obj->UniqueId;
				
				if (PrintGraphWeldDataList.GetCount()>0)
							 PrintGraphWeldDataList.RemoveHead();
				PrintGraphWeldDataList.AddTail(Obj);
			}
			Obj->Draw(pDC, LineNo);
			TotalCyclesDrawn++;
			LineNo++;
		}
	}
	DrawParameterHeadings(pDC);
	
	pDC->SelectObject(OldFont);

}

/****************************************************************/
/* This function draws the graph of selectedwelddata.			*/
/****************************************************************/
void CHistoryView::DrawGraphs(CDC *pDC)
{
	if(!OldVersionPresent)
	{
		POSITION pos1 = GraphObjects.GetTailPosition();
		if(GraphParam)
		{
			CGraphData *object;

			if(GraphSelect == 0)
			{
				object = GraphObjects.GetAt(pos1);
				object->Draw(pDC);
				Graph1ID = object->GraphData.GraphTypeID;
				Graph2ID=0;
				GraphSelect = object->GraphData.GraphTypeID;
				return;
				
			}
			else 
			{	
				while (pos1)	
				{
					object =GraphObjects.GetPrev(pos1);
					if((object->GraphData.GraphTypeID == Graph1ID) && GraphSelect)
					{
						object->GraphData.GraphNum=1;
						object->DrawGraphBoundary(pDC);		//Draw Graph boundary only once in case of dual graph.
						object->drawgraph(pDC);
						object->DrawTickMarks(pDC);
						object->DrawHLabel(pDC);
						object->DrawVLabel(pDC);
					}
					
					if(object->GraphData.GraphTypeID== Graph2ID)
					{
						object->GraphData.GraphNum=2;
						object->drawgraph(pDC);
						object->DrawVLabel(pDC);
					}
	 			}
			}
		}
	}
	else
	{
		POSITION pos1 = GraphOldObjects.GetTailPosition();
		if(GraphParam)
		{
			CGraphOldData *object;

			if(GraphSelect == 0)
			{
				object = GraphOldObjects.GetAt(pos1);
				object->Draw(pDC);
				Graph1ID = object->GraphTypeID;
				Graph2ID=0;
				GraphSelect = object->GraphTypeID;
				return;
				
			}
			else 
			{	
				while (pos1)	
				{
					object =GraphOldObjects.GetPrev(pos1);
					if((object->GraphTypeID == Graph1ID) && GraphSelect)
					{
						object->GraphNum=1;
						object->DrawGraphBoundary(pDC);		//Draw Graph boundary only once in case of dual graph.
						object->drawgraph(pDC);
						object->DrawTickMarks(pDC);
						object->DrawHLabel(pDC);
						object->DrawVLabel(pDC);
					}
					
					if(object->GraphTypeID== Graph2ID)
					{
						object->GraphNum=2;
						object->drawgraph(pDC);
						object->DrawVLabel(pDC);
					}
	 			}
			}
		}
	}
}

/****************************************************************/
/* This function draws the page number in the menu screen.		*/
/****************************************************************/
void CHistoryView::DrawPageNumber(CDC *pDC)
{
	if((BrowsingLevel==HIERARCHYYEARMONTH)||(BrowsingLevel==HIERARCHYDAY)|| (BrowsingLevel==HIERARCHYHSFOLDER))
	{
		int NoOfObjects = FileName.GetCount();
		int MaxPageDisplay=NoOfObjects/8;

		if(MaxPageDisplay!=(NoOfObjects*8))
			MaxPageDisplay++;
		
		if(MaxPageDisplay==1)
			return;

		char Curr_buff[4];
		sprintf(Curr_buff,"%dof%d",PageNum,MaxPageDisplay);
		CString PageString="Pg";
		PageString+=Curr_buff;
		pDC->SetBkColor(TRANSPARENT);
		DrawText(pDC, 11, true, PageNO_Rect, PageString,true);
	}
}
/****************************************************************/
/* This function refreshes data or graph display after			 */
/*different different selections.								       */
/****************************************************************/
void CHistoryView::PaintWindow()
{
	CDC *pDrawDC=GetDC();
	pDrawDC->SetBkMode(TRANSPARENT);

	if(BrowsingLevel==WELDDATA)
	{
		pDrawDC->FillSolidRect(DATAWIN_START_X,DATAWIN_START_Y+10,DATAWIN_END_X,DATAWIN_END_Y,COLORWHITE);
		DrawWeldData(pDrawDC);
	}

	if(BrowsingLevel==GRAPHS)
	{	
		pDrawDC->FillSolidRect(DATAWIN_START_X,DATAWIN_START_Y,DATAWIN_END_X,DATAWIN_END_Y,COLORWHITE);
		DrawGraphs(pDrawDC);
	}
	ReleaseDC(pDrawDC);

}

/****************************************************************/
/* This function draws parameter headings of welddata screen.	*/
/****************************************************************/
void CHistoryView::DrawParameterHeadings(CDC *pDC)
{
	pDC->ExtTextOut(10,HISTORY_TBL_START_Y+LINE_GAP,ETO_OPAQUE   ,NULL, WelddataHeadings[1],NULL);
	CWeldData * Obj ;
	if(WeldObjects.GetCount())
	{
		POSITION pos = WeldObjects.GetHeadPosition();
		for(int i=0;i<TopMostData+SelectedWeldData-1;i++)
		Obj = WeldObjects.GetNext(pos);
	}
	
		for (int MLength=LeftMostParameter,j=1 ; MLength < LeftMostParameter+4 ;MLength++,j++)
		{
			CString b;
			pDC->SetBkMode(TRANSPARENT);

			int	ParamNum=Obj->USBParamIDs[MLength];
       
			if(Obj->Units)
				b = Parameter_Units_Metric[ParamNum];
			else
				b = Parameter_Units_USCS[ParamNum];
			/*----------------------------CATL----------------------------*/
			if (AmpMicronsFormat && Parameter_Formats[ParamNum]==MICRONS)
				b=Parameter_Units_Formats[ParamNum];
			if (PowerWattsFormat && Parameter_Formats[ParamNum]==WATTS)
				b=Parameter_Units_Formats[ParamNum];
			/*----------------------------CATL----------------------------*/

			pDC->ExtTextOut(ParamRectWidth*j,HISTORY_TBL_START_Y+LINE_GAP,ETO_OPAQUE   ,NULL, WelddataHeadings[ParamNum],NULL);
			pDC->ExtTextOut(ParamRectWidth*j,HISTORY_TBL_START_Y+LINE_GAP*2,ETO_OPAQUE   ,NULL, b,NULL);
			SelectedWeldId = Obj->UniqueId;
		}
	
}
/****************************************************************/
/* This function does final clean up when user click exit		 */
/*button in main window.										          */
/****************************************************************/
void CHistoryView::OnProgramExit() 
{
	DestroyWindow();

	if(WeldObjects.GetCount() && (!GraphObjects.GetCount() && !GraphOldObjects.GetCount()))
	{
	  delete ButtonLeft;
	  delete ButtonRight;
	  delete ButtonUp;
	  delete ButtonDown;
	  delete ButtonPageUp;
	  delete ButtonPageDown;
	  delete ButtonGraph;
	  delete ButtonExit;
	  delete Buttonprint;
	}
	if((GraphObjects.GetCount())||(GraphOldObjects.GetCount()))
	{
	  delete ButtonGraphAmp;
	  delete ButtonGraphColDist;
	  delete ButtonGraphForce;
	  delete ButtonGraphVelocity;
	  delete ButtonGraphFreq;
	  delete ButtonGraphPower;
	  delete ButtonGraphExit;
	  delete ButtonprintGraph;
	}

	while(ScreenObjects.GetCount())
		delete ScreenObjects.RemoveHead();

	while (GraphObjects.GetCount())
		free(GraphObjects.RemoveHead());

	while (GraphOldObjects.GetCount())
		free(GraphOldObjects.RemoveHead());

	while(WeldObjects.GetCount())
		free(WeldObjects.RemoveHead());
	
	while(WeldObjectsList.GetCount())
		WeldObjectsList.RemoveHead();
	delete this;
			
	exit(1);
}

/****************************************************************/
/* This function does final clean up when user click cross tab	 */
/*or Alt+F4 in main window.										       */
/****************************************************************/
void CHistoryView::OnDestroy() 
{
	CWnd::OnDestroy();
	OnProgramExit() ;
	
}

void CHistoryView::OnHSOpen() 
{
	HSMenu=true;
	DrawFirstScreen() ;
	int y;
	if(!FileCreated)
	{
		CBrowse Dialog;
		FileCreated = false;
		y= Dialog.DoModal();
	}
	
	if(y==1)        //ok button
	{
		PageNum=1; // coz first page is to be displayed at the first time
		PageNumList.AddHead(PageNum);
		RecalculateMenu();
		Invalidate(false);
	}
	
}

/****************************************************************/
/* This function Draw HS Compare data                    		 */
/****************************************************************/

bool CHistoryView::DrawCompareHSData(CDC *pDC)
{
   	ScanA_On =true;
		ScanB_On =true;
		ScanC_On =true;
	
	ColoumnHeading[0]="Scan A",ColoumnHeading[1]="Scan B",ColoumnHeading[2]="Scan C";
	RowHeading[0]="Horn ID",RowHeading[1]="Time",RowHeading[2]="Date",RowHeading[3]="Freq1",RowHeading[4]="Freq2",
		RowHeading[5]="Freq3",RowHeading[6]="Freq4",RowHeading[7]="Freq5",RowHeading[8]="Freq6";
	/*Drawing Coloumn Headings.*/
	int X1 = 160;
	int X2 = 110;
	int Y1_CoOrdinate=65;
	for (int t=0;t<3;t++)
	{
		X1 =X2;
		X2 = X1+150;
       DrawText(pDC,COLORBLACK,false, CRect(X1,Y1_CoOrdinate,X2,Y1_CoOrdinate),ColoumnHeading[t],true);//Draw textColoumnHeading[i]
	}
	/*Drawing Row Headings.*/
	int Y1 = 20;
	int Y2 = 90;
	int X1_CoOrdinate=5;
	for(int r=0;r<9;r++)
	{
		Y1 =Y2;
		Y2 = Y1+30;
        DrawText(pDC,COLORBLACK,false, CRect(X1_CoOrdinate,Y1,X1_CoOrdinate+100,Y2),RowHeading[r],true);//Draw text//RowHeading[j]
	}

	/*Drawing Line.*/
	CPen penLine;
	CPen *OldPen;
	penLine.CreatePen(PS_SOLID, 2, COLORBLACK);
	OldPen = pDC->SelectObject(&penLine);
	pDC->MoveTo(20,85);
	pDC->LineTo(570,85);
	pDC->SelectObject(OldPen);
	penLine.DeleteObject();

	
	for(int I=0;I<3;I++)
	for(int J=0;J<9;J++)
		CompareData[J][I]="  ";
	CString HS_ID1,HS_ID2,HS_ID3;
	
    HighLight[0]=-1;	
    HighLight[1]=-1;
    HighLight[2]=-1;
    CTypedPtrList<CPtrList, CGraphData *> HSGraphDataList;
    CTypedPtrList<CPtrList, CGraphOldData *> HSGraphOldDataList;

	CFile f1;
	CFileException e1;
	CString  pFileName1=(HSFolderPath)+("\\HornScanA.txt");

	
	if(f1.Open( pFileName1, CFile::modeReadWrite, &e1 ) )
	
	{
		int p=f1.GetLength();
		unsigned char *Data=new unsigned char[p];
		unsigned char *Dummy = Data;
		int k =f1.Read(Data,p);
		if(k>20)
		{
			HS1_Present=true;
			int len =f1.GetLength();
		//	int temp = (int)*Data++;len--;
			CHistoryView::Language_Index =0;
			HS_ID1 =GetString(Data,len);
		//	CHistoryView::Language_Index =temp;
			OldVersionPresent=false;
			CGraphData *graph =new CGraphData(Data,len);
			if(len!=-1)
			{
				//f1.Read(graph,len);
			    OldVersionPresent=false;
				graph->GraphData.GraphColour =2;
				graph->HSCompareGraph=true;
				HSGraphDataList.AddTail(graph);
				HighLight[0] =HighLightString;
			}
			else
			{
				delete graph;
				OldVersionPresent=true;
				f1.Close();
			}
			if(OldVersionPresent)
			{
				f1.Open( pFileName1, CFile::modeReadWrite, &e1 );
				int len=f1.GetLength();
				unsigned char *Data1=new unsigned char[len];
				unsigned char *Dummy = Data1;
				int k =f1.Read(Data1,len);
				int temp = (int)*Data1++;len--;
				CHistoryView::Language_Index =0;
				HS_ID1 =GetString(Data1,len);
				CHistoryView::Language_Index =temp;
				CGraphOldData *graph =new CGraphOldData(Data1,len);
				graph->GraphColour =2;
				graph->HSCompareGraph=true;
				HSGraphOldDataList.AddTail(graph);
				HighLight[0] =HighLightString;
				delete []Dummy;
			}
		}
		delete []Dummy;
		f1.Close();
	}
	int TempLangIndex=CHistoryView::Language_Index;
	CFile f;
	CFileException e;
	CString pFileName=(HSFolderPath)+("\\HornScanB.txt");
	
	if( f.Open( pFileName, CFile::modeReadWrite , &e ) )
	{
		unsigned char *Data=new unsigned char[f.GetLength()];
		unsigned char *Dummy = Data;
		int j =f.Read(Data,f.GetLength());
		if(j>20)
		{
			HS2_Present=true;
			int len =f.GetLength();
		//	int temp = (int)*Data++;len--;
			CHistoryView::Language_Index =0;
			HS_ID2 = GetString(Data,len);
		//	CHistoryView::Language_Index =temp;
			OldVersionPresent=false;
			CGraphData *graph1 =new CGraphData(Data,len);
			if(len!=-1)
			{
				//f.Read(graph1,len);
				OldVersionPresent=false;
				graph1->GraphData.GraphColour =3;
				graph1->HSCompareGraph=true;
				HSGraphDataList.AddTail(graph1);
				CHistoryView::Language_Index=TempLangIndex;
				HighLight[1] =HighLightString;
			}
			else
			{
				delete graph1;
				OldVersionPresent=true;
					f.Close();
			}
			if(OldVersionPresent)
			{
				f.Open( pFileName, CFile::modeReadWrite , &e );
				int len =f.GetLength();
				unsigned char *Data=new unsigned char[f.GetLength()];
				unsigned char *Dummy = Data;
				f.Read(Data,f.GetLength());
				int temp = (int)*Data++;len--;
				CHistoryView::Language_Index =0;
				HS_ID2 = GetString(Data,len);
				CHistoryView::Language_Index =temp;
				CGraphOldData *graph =new CGraphOldData(Data,len);
				graph->GraphColour =3;
				graph->HSCompareGraph=true;
				HSGraphOldDataList.AddTail(graph);
				CHistoryView::Language_Index=TempLangIndex;
				HighLight[1] =HighLightString;
				delete []Dummy;
			}
		}	
		delete []Dummy;
		f.Close();
	}
	CFile f2;
	CFileException e2;
	CString pFileName2=(HSFolderPath)+"\\HornScanC.txt";
	

	if( f2.Open( pFileName2, CFile::modeReadWrite , &e2 ) )
	{
		unsigned char *Data=new unsigned char[f2.GetLength()];
		unsigned char *Dummy = Data;
		int i =f2.Read(Data,f2.GetLength());
		if(i>20)
		{
			HS3_Present=true;
			int len =f2.GetLength();
			//int temp = (int)*Data++;len--;
	//		CHistoryView::Language_Index = 0;
			HS_ID3 = GetString(Data,len);
		//	CHistoryView::Language_Index = temp;
			OldVersionPresent=false;
			CGraphData *graph2 =new CGraphData(Data,len);
			if(len!=-1)
			{
				//f2.Read(graph2,len);
				OldVersionPresent=false;
				graph2->GraphData.GraphColour =4;
				graph2->HSCompareGraph=true;
				HSGraphDataList.AddTail(graph2);
				CHistoryView::Language_Index = TempLangIndex;
				HighLight[2] =HighLightString;
			}
			else
			{
				delete graph2;
				OldVersionPresent=true;
				f2.Close();
			}
			if(OldVersionPresent)
			{
				f2.Open( pFileName2, CFile::modeReadWrite , &e2 ) ;
				int len =f2.GetLength();
				unsigned char *Data=new unsigned char[f2.GetLength()];
				unsigned char *Dummy = Data;
				f2.Read(Data,f2.GetLength());
				int temp = (int)*Data++;len--;
				CHistoryView::Language_Index = 0;
				HS_ID3 = GetString(Data,len);
				CHistoryView::Language_Index = temp;

				CGraphOldData *graph =new CGraphOldData(Data,len);
				graph->GraphColour =4;
				graph->HSCompareGraph=true;
				HSGraphOldDataList.AddTail(graph);
				CHistoryView::Language_Index = TempLangIndex;
				HighLight[2] =HighLightString;
				delete []Dummy;
			}
		}
		delete []Dummy;
		f2.Close();
	}

	if(!OldVersionPresent)
	{
		POSITION pos =HSGraphDataList.GetHeadPosition();
		int j=0;
		CompareData[0][0]=HS_ID1;CompareData[0][1]=HS_ID2;CompareData[0][2]=HS_ID3;
		while (pos)
		{	
			int q=1;
			if(j==0 && !HS1_Present)
				j++;
			if(j==1 && !HS2_Present)
				j++;
			{
				CGraphData *graph =HSGraphDataList.GetNext(pos);
				CompareData[q++][j] =graph->TimeString;
				CompareData[q++][j] =  graph->DateString;
				for(int k=0;k<6;k++)
					CompareData[q++][j] = graph->FreqString[k];
			}
			j++;
			
		}
	
	}
	else
	{
		POSITION pos =HSGraphOldDataList.GetHeadPosition();
		int j=0;
		CompareData[0][0]=HS_ID1;CompareData[0][1]=HS_ID2;CompareData[0][2]=HS_ID3;
		while (pos)
		{	
			int q=1;
			if(j==0 && !HS1_Present)
				j++;
			if(j==1 && !HS2_Present)
				j++;
			{
				CGraphOldData *graph =HSGraphOldDataList.GetNext(pos);
				CompareData[q++][j] =graph->TimeString;
				CompareData[q++][j] =  graph->DateString;
				for(int k=0;k<6;k++)
					CompareData[q++][j] = graph->FreqString[k];
			}
			j++;
			
		}
	}
	int x = 150;
	int y=96;
	CFont *OldFont;
	OldFont=pDC->SelectObject(&SmallFont);
	
	CPen *oldPen;
	CPen NewPen;
	NewPen.CreatePen(PS_SOLID,2,COLORBLACK);
	oldPen = pDC->SelectObject(&NewPen);

	pDC->SetTextColor(COLORBLACK);

	for(int i=0;i<3;i++)
	{
		
		for(int j =0;j<9;j++)
		{
			if(((HighLight[i]+3) == j)&&(HighLight[i] != -1))
			{
				pDC->SetTextColor(COLORBLUE);
            pDC->ExtTextOut(x,y ,ETO_OPAQUE  ,NULL,CompareData[j][i],NULL);//DrawText(pDC, SmallFont, COLORBLUE, CRect(x,y,x+130,y+30),CompareData[j][i],false);
			}
			else
			{
				pDC->SetTextColor(COLORBLACK);
            pDC->ExtTextOut(x,y ,ETO_OPAQUE  ,NULL,CompareData[j][i],NULL);//DrawText(pDC, SmallFont, COLORBLACK, CRect(x,y,x+130,y+30),CompareData[j][i],false);
			}
				
			y+=30;
		}
		x+=150;
		y=100;
	}
	pDC->SetTextColor(COLORBLACK);
	pDC->SelectObject(oldPen);
	NewPen.DeleteObject();	
		
	while(HSGraphOldDataList.GetCount())
   		delete HSGraphOldDataList.RemoveHead();
	while(HSGraphDataList.GetCount())
   		delete HSGraphDataList.RemoveHead();
	return false;
}


CString CHistoryView::GetString(unsigned char *&data, int &length)
{
	CString result = "";
	int count= *data++;
	int strlen;
	if(CHistoryView::Language_Index>Asian_Language_Start)
		strlen=count/2;
	else
		strlen=count;
	for (int i = 0; i < strlen; i++)
	{
		union {
			unsigned char ch[2];
			TCHAR character;
			}u;
		if(CHistoryView::Language_Index>Asian_Language_Start)
			u.ch[1]= *data++;
		else
			u.ch[1]=NULL;
			u.ch[0]= *data++;
		
		result += (u.character);
	}
	length -= count+1;
	result.TrimRight();
	result.TrimLeft();
	return result;

}


/****************************************************************/
/* This function draws Horn Compare Graph                		 */
/****************************************************************/

void CHistoryView::DrawCompareHSgraph(CDC *pDC)
{
   
   if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
   {
      CPen pen_bounding;
		CPen *oldpen;
	
   int GRAPH_START_X,GRAPH_START_Y,GRAPH_END_X,GRAPH_END_Y;
   
	   
      GRAPH_START_X =200;
      GRAPH_START_Y =600;
      GRAPH_END_X= GRAPH_START_X + GRAPH_WIDTH*2;;	
	   GRAPH_END_Y = GRAPH_START_Y +( HSGRAPH_HEIGHT*2);
 
      int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		int nVert = pDC->GetDeviceCaps(LOGPIXELSY);

	   	{
			CString HSScanStr[][9]={
				{"Current","Aktuell","Corrnte","Corrent","Actuel.",L"\x7535\x6d41\x0",L"\x96fb\x6d41\x0",
									L"\xff76\xff9a\xff84\x0",L"\xc804\xb958\x0"},
				{"Scan A","Scan A","Scan A","Scan A","Scan A",L"\x626b\x63cf\x7ed3\x679c\x0041\x0",L"\x626b\x63cf\x7ed3\x679c\x0041\x0",
									L"\xff7d\xff77\xff6c\xff9d\x0041\x0",L"\x0053\x0063\x0061\x006e\x0020\x0041\x0" },
				{"Scan B","Scan B","Scan B","Scan B","Scan B",L"\x626b\x63cf\x7ed3\x679c\x0042\x0",L"\x6383\x63cf\x7ed3\x679c\x0042\x0",
									L"\xff7d\xff77\xff6c\xff9d\x0042\x0",L"\x0053\x0063\x0061\x006e\x0020\x0042\x0"},
				{"Scan C","Scan C ","Scan C","Scan C","Scan C",L"\x626b\x63cf\x7ed3\x679c\x0043\x0",L"\x6383\x63cf\x7ed3\x679c\x0043\x0",
									L"\xff7d\xff77\xff6c\xff9d\x0043\x0",L"\x0053\x0063\x0061\x006e\x0020\x0043\x0"}
								};
			int Y =GRAPH_END_Y+100;
			int X = GRAPH_START_X;
			for(int i=0;i<3;i++)
			{
            CPoint LabelPoint1(X,Y);
				CPoint LabelPoint2(X+20,Y+20);
				LabelPoint1=CalibPoint(LabelPoint1,nHorz,nVert);
				LabelPoint2=CalibPoint(LabelPoint2,nHorz,nVert);
				CRect LabelRect(LabelPoint1,LabelPoint2);
				pDC->FillSolidRect(LabelRect,CHistoryView::Color_Array[i+1]);
            pDC->SetBkColor(CHistoryView::Color_Array[White]);
				CHistoryView::DrawPrinterText(pDC,X+30,Y,HSScanStr[i+1][0]);
			X +=200;
				
			}

		}
      pDC->SelectObject(&oldpen);
		pen_bounding.DeleteObject( );

		}
   else
   {
		
		CPen pen_bounding;
		CPen *oldpen;
		pen_bounding.CreatePen( NULL , 2, CHistoryView::Color_Array[COLORBLACK]);
		oldpen=pDC->SelectObject(&pen_bounding);
		pDC->MoveTo(GRAPH_START_X_CORD,GRAPH_START_Y_CORD);
		pDC->LineTo(GRAPH_END_X_CORD,GRAPH_START_Y_CORD);
		pDC->LineTo(GRAPH_END_X_CORD,GRAPH_END_Y_CORD);
		pDC->LineTo(GRAPH_START_X_CORD,GRAPH_END_Y_CORD);
		pDC->LineTo(GRAPH_START_X_CORD ,GRAPH_START_Y_CORD);
		/*Draw Y Axis graduation*/
		int Index;
		
		/*Draw X Axis graduation*/
		for (Index = 1; Index < INCLABEL; Index++ ) 
		{
			int X1 = GRAPH_START_X_CORD+ ((Index * GRAPH_WIDTH)/INCLABEL);
			pDC->MoveTo(X1,(HSGRAPH_HEIGHT+(GRAPH_START_Y_CORD  - 3)));
			pDC->LineTo(X1,(HSGRAPH_HEIGHT+(GRAPH_START_Y_CORD  + 3))) ;
		}
		pDC->SelectObject(&oldpen);
		pen_bounding.DeleteObject( );
		pen_bounding.CreatePen( NULL , 1, CHistoryView::Color_Array[COLORBLACK]);
		oldpen=pDC->SelectObject(&pen_bounding);
		int LineProp_Y1 = GRAPH_START_Y_CORD + HSGRAPH_HEIGHT -202;
		int LineProp_X1 = GRAPH_START_X_CORD;
		int LineProp_X2 = LineProp_X1+ 8;
	
		pDC->SelectObject(&oldpen);
		pen_bounding.DeleteObject( );
   }
		
	
}

/*******************************************************************/
/* This function Read 3 Horn Scan Files And calculate compare Data */
/*******************************************************************/

bool CHistoryView::CompareGraph_and_Data()
{
   	ColoumnHeading[0]="Scan A",ColoumnHeading[1]="Scan B",ColoumnHeading[2]="Scan C";
	RowHeading[0]="Horn ID",RowHeading[1]="Time",RowHeading[2]="Date",RowHeading[3]="Freq1",RowHeading[4]="Freq2",
		RowHeading[5]="Freq3",RowHeading[6]="Freq4",RowHeading[7]="Freq5",RowHeading[8]="Freq6";
	while(GraphDataList.GetCount())
		delete GraphDataList.RemoveHead();
	while(GraphOldDataList.GetCount())
		delete GraphOldDataList.RemoveHead();
	CString s3,s2,s1;
	int NoOfGraphs=0;
	
	int TempLangIndex =CHistoryView::Language_Index;
	CFile f1;
	CFileException e1;
   HighLight[0]=-1;	
   HighLight[1]=-1;
   HighLight[2]=-1;

	CString pFileName1 = (HSFolderPath)+("\\HornScanA.txt");
	if( f1.Open( pFileName1, CFile::modeReadWrite , &e1 ) )
	{
		unsigned char *c=new unsigned char[f1.GetLength()];
		unsigned char *c1=c;
		int k =f1.Read(c,f1.GetLength());
		if((k>20) && (ScanA_On))
		{
         HS1_Present=true;
			int len =f1.GetLength();
		//	int langIndex = (int)*c++;len--;
			CHistoryView::Language_Index =0;
			s1 =GetString(c,len);
		//	CHistoryView::Language_Index =langIndex;
			OldVersionPresent=false;
			CGraphData *graph =new CGraphData(c,len);
			if(len!=-1)
			{
				OldVersionPresent=false;
				graph->GraphData.GraphColour =COLORBLUE;
				graph->HSCompareGraph=true;
				graph->HS_CompareGraphNum =1;
				GraphDataList.AddTail(graph);
				NoOfGraphs++;
				CHistoryView::Language_Index =TempLangIndex;
				HighLight[0] =HighLightString;
			}
			else
			{
				delete graph;
				OldVersionPresent=true;
				f1.Close();
			}
			if(OldVersionPresent)
			{
				f1.Open( pFileName1, CFile::modeReadWrite, &e1 );
				int len=f1.GetLength();
				unsigned char *Data1=new unsigned char[len];
				unsigned char *Dummy = Data1;
				int k =f1.Read(Data1,len);
				int temp = (int)*Data1++;len--;
				CHistoryView::Language_Index =0;
				s1 =GetString(Data1,len);
				CHistoryView::Language_Index =temp;
				CGraphOldData *graph =new CGraphOldData(Data1,len);
				graph->GraphColour =COLORBLUE;
				graph->HSCompareGraph=true;
				graph->HS_CompareGraphNum =1;
				GraphOldDataList.AddTail(graph);
				NoOfGraphs++;
				CHistoryView::Language_Index =TempLangIndex;
				HighLight[0] =HighLightString;
				delete []Dummy;
			}
		}
		f1.Close();
		delete []c1;
		
	}
	
	CFile f;
	CFileException e;
	CString pFileName = (HSFolderPath)+("\\HornScanB.txt");
	if(f.Open( pFileName, CFile::modeReadWrite , &e ) )
	{
		
		unsigned char *c2=new unsigned char[f.GetLength()];
		unsigned char *c1=c2;
		int j =f.Read(c2,f.GetLength());
		if((j>20)  && (ScanB_On))
		{
			HS2_Present=true;
			int len =f.GetLength();
		//	int langIndex = (int)*c2++;len--;
			CHistoryView::Language_Index =0;
			s2 = GetString(c2,len);
			OldVersionPresent=false;
	//			CHistoryView::Language_Index =langIndex;
			CGraphData *graph1 =new CGraphData(c2,len);
			if(len!=-1)
			{
				OldVersionPresent=false;
				graph1->GraphData.GraphColour =COLORRED;
				graph1->HSCompareGraph=true;
				graph1->HS_CompareGraphNum =2;
				GraphDataList.AddTail(graph1);
				NoOfGraphs++;
				CHistoryView::Language_Index =TempLangIndex;
				HighLight[1] =HighLightString;
			}
			else
			{
				delete graph1;
				OldVersionPresent=true;
					f.Close();
			}
			if(OldVersionPresent)
			{
				f.Open( pFileName, CFile::modeReadWrite , &e );
				int len =f.GetLength();
				unsigned char *Data=new unsigned char[f.GetLength()];
				unsigned char *Dummy = Data;
				f.Read(Data,f.GetLength());
				int temp = (int)*Data++;len--;
				CHistoryView::Language_Index =0;
				s2 = GetString(Data,len);
				CHistoryView::Language_Index =temp;
				CGraphOldData *graph =new CGraphOldData(Data,len);
				graph->GraphColour =COLORRED;
				graph->HSCompareGraph=true;
				graph->HS_CompareGraphNum =2;
				GraphOldDataList.AddTail(graph);
				NoOfGraphs++;
				CHistoryView::Language_Index =TempLangIndex;
				HighLight[1] =HighLightString;
				delete []Dummy;
			}
		}
		f.Close();
		delete []c1;
	}
	

	CFile f2;
	CFileException e2;
	CString pFileName2 =(HSFolderPath)+("\\HornScanC.txt");
	if( f2.Open( pFileName2, CFile::modeReadWrite , &e2 ) )
	{
		unsigned char *c1=new unsigned char[f2.GetLength()];
		unsigned char *c=c1;
		int i =f2.Read(c1,f2.GetLength());
		if((i>20)  && (ScanC_On))
		{
            HS3_Present=true;
			int len =f2.GetLength();
		//	int langIndex = (int)*c1++;len--;
			CHistoryView::Language_Index = 0;
			s3 = GetString(c1,len);
			OldVersionPresent=false;
		//	CHistoryView::Language_Index =langIndex;
			CGraphData *graph2 =new CGraphData(c1,len);
			if(len!=-1)
			{
				OldVersionPresent=false;
				graph2->GraphData.GraphColour =COLORGREEN;
				graph2->HSCompareGraph=true;
				graph2->HS_CompareGraphNum =3;
				GraphDataList.AddTail(graph2);
				NoOfGraphs++;
				CHistoryView::Language_Index = TempLangIndex;
				HighLight[2] =HighLightString;
			}
			else
			{
				delete graph2;
				OldVersionPresent=true;
				f2.Close();
			}
			if(OldVersionPresent)
			{
				f2.Open( pFileName2, CFile::modeReadWrite , &e2 ) ;
				int len =f2.GetLength();
				unsigned char *Data=new unsigned char[f2.GetLength()];
				unsigned char *Dummy = Data;
				f2.Read(Data,f2.GetLength());
				int temp = (int)*Data++;len--;
				CHistoryView::Language_Index = 0;
				s3 = GetString(Data,len);
				CHistoryView::Language_Index = temp;

				CGraphOldData *graph =new CGraphOldData(Data,len);
				graph->GraphColour =COLORGREEN;
				graph->HSCompareGraph=true;
				graph->HS_CompareGraphNum =3;
				GraphOldDataList.AddTail(graph);
				NoOfGraphs++;
				CHistoryView::Language_Index = TempLangIndex;
				HighLight[2] =HighLightString;
				delete []Dummy;
			}
		}
		f2.Close();
		delete []c;
	}
	if(!OldVersionPresent)
	{
   		POSITION pos =GraphDataList.GetHeadPosition();
		int j=0;
		CompareData[0][0]=s1;CompareData[0][1]=s2;CompareData[0][2]=s3;
		while (pos)
		{	
			int q=1;
			if(j==0 && !HS1_Present)
				j++;
			if(j==1 && !HS2_Present)
				j++;
			{
				CGraphData *graph =GraphDataList.GetNext(pos);
				CompareData[q++][j] =graph->TimeString;
				CompareData[q++][j] =  graph->DateString;
				for(int k=0;k<6;k++)
					CompareData[q++][j] = graph->FreqString[k];
			}
			j++;
			
		}
	}
	else
	{
		POSITION pos =GraphOldDataList.GetHeadPosition();
		int j=0;
		CompareData[0][0]=s1;CompareData[0][1]=s2;CompareData[0][2]=s3;
		while (pos)
		{	
			int q=1;
			if(j==0 && !HS1_Present)
				j++;
			if(j==1 && !HS2_Present)
				j++;
			{
				CGraphOldData *graph =GraphOldDataList.GetNext(pos);
				CompareData[q++][j] =graph->TimeString;
				CompareData[q++][j] =  graph->DateString;
				for(int k=0;k<6;k++)
					CompareData[q++][j] = graph->FreqString[k];
			}
			j++;
			
		}
	}
	if(NoOfGraphs==0)
	{
		ShowMessageScreen("No Valid Graph Data");
		DisableFlag=true;
		return false;
	}

	return true;

}


/****************************************************************/
/* This function draws Horn Compare Graph                		 */
/****************************************************************/

void CHistoryView::DrawHSGraphs(CDC *pDC)
{
	if(!OldVersionPresent)
	{
		POSITION pos1 = GraphDataList.GetHeadPosition();
		int num=GraphDataList.GetCount();
		while(pos1)
		{
			CGraphData *object= 0;
			object =GraphDataList.GetNext(pos1);
			if(object->HS_CompareGraphNum==1)
			{
				object->GraphData.GraphColour=2; 
				object->Draw(pDC);
			}
		
			if(object->HS_CompareGraphNum==2)
			{
				object->GraphData.GraphColour=3; 
				object->Draw(pDC);
			}
		
		
			if(object->HS_CompareGraphNum==3)
			{
				object->GraphData.GraphColour=4; 
				object->Draw(pDC);
			}
		
		}
	}
	else
	{
		POSITION pos1 = GraphOldDataList.GetHeadPosition();
		int num=GraphOldDataList.GetCount();
		while(pos1)
		{
			CGraphOldData *object= 0;
			object =GraphOldDataList.GetNext(pos1);
			if(object->HS_CompareGraphNum==1)
			{
				object->GraphColour=2; 
				object->Draw(pDC);
			}
		
			if(object->HS_CompareGraphNum==2)
			{
				object->GraphColour=3; 
				object->Draw(pDC);
			}
		
		
			if(object->HS_CompareGraphNum==3)
			{
				object->GraphColour=4; 
				object->Draw(pDC);
			}
		
		}
	}
	
}

void CHistoryView::ScanAGraph()
{
	if(ScanA_Present)
		{
			delete ButtonScanA;
			delete ButtonScanB;
			delete ButtonScanC;
         delete ButtonprintHSGraph;
			ScanA_On =!ScanA_On;
			CreateScreenButton();
			EditGraphList(ScanA_On, 1);
			Invalidate(false);
		}
	
}
void CHistoryView::ScanBGraph()
{
		

	if(ScanB_Present)
		{
			delete ButtonScanA;
			delete ButtonScanB;
			delete ButtonScanC;
         delete ButtonprintHSGraph;
			ScanB_On =!ScanB_On;
			CreateScreenButton();
			EditGraphList(ScanB_On, 2);
			Invalidate(false);
		}
		
}
void CHistoryView::ScanCGraph()
{
	
	
	if(ScanC_Present)
		{
			delete ButtonScanA;
			delete ButtonScanB;
			delete ButtonScanC;
         delete ButtonprintHSGraph;
			ScanC_On =!ScanC_On;
			CreateScreenButton();
			EditGraphList(ScanC_On, 3);
			Invalidate(false);
		}
		
}

void CHistoryView::EditGraphList(bool On_Off, int graphNum)
{
	if(!OldVersionPresent)
	{
		if((!On_Off))
		{
			CTypedPtrList<CPtrList, CGraphData *> HSGraphDataList;
		
			while(GraphDataList.GetCount())
			{
				CGraphData *obj =GraphDataList.GetHead();
				if(obj->HS_CompareGraphNum != graphNum)
				{
					HSGraphDataList.AddTail(obj);
					GraphDataList.RemoveHead();
				}
				else
					delete GraphDataList.RemoveHead();
			}
			POSITION pos = HSGraphDataList.GetHeadPosition();
			while(pos)
			{
				CGraphData *obj = HSGraphDataList.GetNext(pos);
				GraphDataList.AddTail(obj);
			}
		}
		else if(On_Off)
		{
			CString Path;
			bool GraphPresent =false;
			switch(graphNum)
			{
				case 1:
				{
					Path = (HSFolderPath)+("\\HornScanA.txt");
					if(ScanA_Present)
						GraphPresent =true;
				}
				break;
				case 2:
				{
					Path = (HSFolderPath)+("\\HornScanB.txt");
					if(ScanB_Present)
						GraphPresent =true;
				}
				break;
				case 3:
				{
				
					Path = (HSFolderPath)+("\\HornScanC.txt");
					if(ScanC_Present)
						GraphPresent =true;	
				}
				break;
			}	
			if(GraphPresent)
			{
				CFile f;
				CFileException e;
				if( f.Open( Path, CFile::modeReadWrite , &e ) )
				{
					unsigned char *Data=new unsigned char[f.GetLength()];
					unsigned char *Dummy = Data;
					int k =f.Read(Data,f.GetLength());
					if(k>20)
					{
						int len =f.GetLength();
					/*	int StoredLangIndex = *Data++;
						len--;*/
						int temp = 	CHistoryView::Language_Index;
						CHistoryView::Language_Index =0;
						CString HS_ID1 =GetString(Data,len);
					//	CHistoryView::Language_Index =StoredLangIndex;
						CGraphData *graph =new CGraphData(Data,len);
						graph->GraphData.GraphColour =graphNum+1;
						graph->HSCompareGraph=true;
						graph->HS_CompareGraphNum = graphNum;
						GraphDataList.AddTail(graph);
						CHistoryView::Language_Index =temp;
					}
					delete []Dummy;
					f.Close();
				
				}
		

			}
		}
	}
	else
	{
		if((!On_Off))
		{
			CTypedPtrList<CPtrList, CGraphOldData *> HSGraphDataList;
		
			while(GraphOldDataList.GetCount())
			{
				CGraphOldData *obj =GraphOldDataList.GetHead();
				if(obj->HS_CompareGraphNum != graphNum)
				{
					HSGraphDataList.AddTail(obj);
					GraphOldDataList.RemoveHead();
				}
				else
					delete GraphOldDataList.RemoveHead();
			}
			POSITION pos = HSGraphDataList.GetHeadPosition();
			while(pos)
			{
				CGraphOldData *obj = HSGraphDataList.GetNext(pos);
				GraphOldDataList.AddTail(obj);
			}
		}
		else if(On_Off)
		{
			CString Path;
			bool GraphPresent =false;
			switch(graphNum)
			{
				case 1:
				{
					Path = (HSFolderPath)+("\\HornScanA.txt");
					if(ScanA_Present)
						GraphPresent =true;
				}
				break;
				case 2:
				{
					Path = (HSFolderPath)+("\\HornScanB.txt");
					if(ScanB_Present)
						GraphPresent =true;
				}
				break;
				case 3:
				{
				
					Path = (HSFolderPath)+("\\HornScanC.txt");
					if(ScanC_Present)
						GraphPresent =true;	
				}
				break;
			}	
			if(GraphPresent)
			{
				CFile f;
				CFileException e;
				if( f.Open( Path, CFile::modeReadWrite , &e ) )
				{
					unsigned char *Data=new unsigned char[f.GetLength()];
					unsigned char *Dummy = Data;
					int k =f.Read(Data,f.GetLength());
					if(k>20)
					{
						int len =f.GetLength();
						int StoredLangIndex = *Data++;
						len--;
						int temp = 	CHistoryView::Language_Index;
						CHistoryView::Language_Index =0;
						CString HS_ID1 =GetString(Data,len);
						CHistoryView::Language_Index =StoredLangIndex;
						CGraphOldData *graph =new CGraphOldData(Data,len);
						graph->GraphColour =graphNum+1;
						graph->HSCompareGraph=true;
						graph->HS_CompareGraphNum = graphNum;
						GraphOldDataList.AddTail(graph);
						CHistoryView::Language_Index =temp;
					}
					delete []Dummy;
					f.Close();
				
				}
		

			}
		}
	}
}

CRect CHistoryView::UserPage(CDC * pDC, float margin)
{
    // This function returns the area in device units to be used to
    // prints a page with a true boarder of "margin".
    //
    // You could use individual margins for each edge
    // and apply below as needed.
    //
    // Set Map Mode - We do not want device units
    // due to lack of consistency.
    // If you do not use TWIPS you will have to change
    // the scaling factor below.
    int OriginalMapMode = pDC->SetMapMode(MM_TWIPS);

    // Variable needed to store printer info.
    CSize PrintOffset,Physical,Printable;

    // This gets the Physical size of the page in Device Units
    Physical.cx = pDC->GetDeviceCaps(PHYSICALWIDTH);
    Physical.cy = pDC->GetDeviceCaps(PHYSICALHEIGHT);
    // convert to logical
    pDC->DPtoLP(&Physical);

    // This gets the offset of the printable area from the
    // top corner of the page in Device Units
    PrintOffset.cx = pDC->GetDeviceCaps(PHYSICALOFFSETX);
    PrintOffset.cy = pDC->GetDeviceCaps(PHYSICALOFFSETY);
    // convert to logical
    pDC->DPtoLP(&PrintOffset);

    // Set Page scale to TWIPS, Which is 1440 per inch,
    // Zero/Zero is the upper left corner
    // Get Printable Page Size (This is in MM!) so convert to twips.
    Printable.cx =  (int)((float)pDC->GetDeviceCaps(HORZSIZE)*56.69);
    Printable.cy = (int)((float)pDC->GetDeviceCaps(VERTSIZE)*56.69);

    // Positive X -> RIGHT
    // Positive Y -> UP
    // Ref Zero is upper left corner
    int inch = 1440; // Scaling Factor Inches to TWIPS
    int Dx1, Dx2, Dy1, Dy2; // Distance printable area is from edge of paper
    Dx1 = PrintOffset.cx;
    Dy1 = PrintOffset.cy;
    // calculate remaining borders
    Dy2 = Physical.cy-Printable.cy-Dy1;
    Dx2 = Physical.cx-Printable.cx-Dx1;
    //
    // Define the User Area's location
    CRect PageArea;
    PageArea.left = (long)(margin*inch-Dx1);
    PageArea.right = (long)(Printable.cx-margin*inch+Dx2);
    PageArea.top = (int)-(margin*inch-Dy1); // My scale is inverted for y
    PageArea.bottom = (int)-(Printable.cy-margin*inch+Dy2);
    // now put back to device units to return to the program.
    pDC->LPtoDP(&PageArea);
    //
    // return
    return PageArea;
}

int CHistoryView::CreateFontSize(CDC *pdc, int points)
{
    // This will calculate the font size for the printer that is specified
    // by a point size.
    //
    // if points is:
    //  (-) negative uses height as value for Net Font Height
    //                                         (ie. point size)
    //  (+) positive height is Total Height plus Leading Height!
    pdc->SetMapMode(MM_TWIPS);
	 CSize size;
    int perinch = pdc->GetDeviceCaps(LOGPIXELSY);
    size.cx = size.cy=(perinch * points)/72;
	 pdc->DPtoLP(&size);
    return size.cy;
}

void CHistoryView::PrintWeldHistoryData()
{
	NoOfWeld dlg;
	if(dlg.DoModal ()==IDCANCEL)
	{
		return;
	}
	else
	{

      char TempArray[10];
		CString Temp= _itoa(CHistoryView::TotalCycle,TempArray,10);
	
      if(NoOfWeld::EditBoxvalue>(CHistoryView::TotalCycle))
		{
		if((CHistoryView::TotalCycle)==1)
			MessageBox(_T("Please enter only one Weld"));
		else
			MessageBox("Please enter value between 1 and "+ Temp);
		if(dlg.DoModal ()==IDCANCEL)
			return;
		}
		if(NoOfWeld::EditBoxvalue>(CHistoryView::TotalCycle))
		{
		if((CHistoryView::TotalCycle)==1)
			MessageBox(_T("Please enter only one Weld"));
		else
			MessageBox(_T("Please enter value between 1 and ")+ Temp);
		return;
		}
		CDC             dc;
		CPrintDialog    printDlg(FALSE);
		CRect           r;
		if (printDlg.DoModal() == IDCANCEL)
			return;
		
		// Attach a printer DC
		dc.Attach(printDlg.GetPrinterDC());
		dc.m_bPrinting = TRUE;
		CFont *OldFont; 
		CFont BaseFont;
		BaseFont.CreateFont( -CreateFontSize(&dc,8), 0, 0, 0, FW_MEDIUM,
			FALSE, FALSE, 0, ANSI_CHARSET, 
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH , _T("Courier New") );
		OldFont=(CFont*)dc.SelectObject(&BaseFont);
		CString strTitle;
		strTitle.LoadString(AFX_IDS_APP_TITLE);

		// Initialise print document details

		DOCINFO di;
		::ZeroMemory (&di, sizeof (DOCINFO));
		di.cbSize = sizeof (DOCINFO);
		// application title appears in the spooler view
		di.lpszDocName = strTitle;

		// Begin a new print job
		BOOL bPrintingOK = dc.StartDoc( &di );
		CRect MyArea;
		// fixed margin in inches (you can change this)
		MyArea = UserPage(&dc, 2);
		CPrintInfo Info;
		Info.m_rectDraw.SetRect(MyArea.left, 
				MyArea.top,MyArea.right,MyArea.bottom);
		
		
		if(WeldObjectsList.GetCount())
		{
			
			int HistoryYCord = PRINTWELDSTARTYCORD+FOURWELDLINEGAP;
			nPrintPos = WeldObjects.GetHeadPosition();
			int totalDone = 0;
			char TempArray[10];
			CString Temp= _itoa(NoOfWeld::EditBoxvalue,TempArray,10);
			POSITION pos = WeldObjects.GetTailPosition();
			for (UINT page = Info.GetMinPage();bPrintingOK && nPrintPos!=pos,nPrintPos!=NULL ; page++)
			{
		
				// begin new page
				dc.StartPage();
				Info.m_nCurPage = page;
				
				if(page==1)
				{
					CWeldData *object = WeldObjectsList.GetHead();
					HistoryYCord=object->PrintHistoryWeldData(&dc,&Info,HistoryYCord,true,true,true);
					WeldObjectsList.GetNext(nPrintPos);
					NoOfWeldObjectPrinted++;
				}
				else
				{
					CWeldData *object = WeldObjectsList.GetHead();
					HistoryYCord=object->PrintHistoryWeldData(&dc,&Info,HistoryYCord,true,false,false);
				}
				int uio = NoOfWeld::EditBoxvalue;
				bool PrintedEnd = false;
				while ((HistoryYCord < MAXYCOORDINATE)&&(nPrintPos!=NULL))
					{	int uo = NoOfWeld::EditBoxvalue;
					if(NoOfWeld::EditBoxvalue==NoOfWeldObjectPrinted)
					{
						dc.ExtTextOut(PRINTWELDSTARTXCORD,-(HistoryYCord+ONEWELDLINEGAP),ETO_OPAQUE   ,NULL, "**-------------------------------------End of Last "+ Temp  +" Weld History Data ------------------------------------ **",NULL);
						nPrintPos=NULL;
						PrintedEnd = true;
						break;
					}
					HistoryYCord+=50;	
					CWeldData * Obj = WeldObjectsList.GetNext(nPrintPos);
					HistoryYCord=Obj->PrintHistoryWeldData(&dc,&Info,HistoryYCord,false,true,true);
					NoOfWeldObjectPrinted++;
					}
			//	}
				
				if((HistoryYCord > MAXYCOORDINATE))
				{
					dc.ExtTextOut(PRINTWELDSTARTXCORD,-(HistoryYCord+ONEWELDLINEGAP),ETO_OPAQUE   ,NULL, "**  -------------------------------------Last "+ Temp  +" Weld History Data (contd.) ------------------------------------ **",NULL);
					HistoryYCord = PRINTWELDSTARTYCORD+FOURWELDLINEGAP;
				}
				if((NoOfWeld::EditBoxvalue==NoOfWeldObjectPrinted)&&(!PrintedEnd))
					{
						dc.ExtTextOut(PRINTWELDSTARTXCORD,-(HistoryYCord+ONEWELDLINEGAP),ETO_OPAQUE   ,NULL, "**-------------------------------------End of Last "+ Temp  +" Weld History Data ------------------------------------ **",NULL);
						nPrintPos=NULL;
						PrintedEnd = true;				
					}
				
				bPrintingOK = (dc.EndPage() > 0);
				
			}
			
			if (bPrintingOK)
				dc.EndDoc();
			 else
			// abort job.
				dc.AbortDoc();
			dc.SelectObject(OldFont);
			// detach the printer DC
			dc.Detach();

		}
	}
	NoOfWeldObjectPrinted=0;
	NoOfWeld::EditBoxvalue=0;
}

void CHistoryView::PrintHSData()
{
   	
      CDC             dc;
		CPrintDialog    printDlg(FALSE);
		CRect           r;
		if (printDlg.DoModal() == IDCANCEL)
			return;
		// Attach a printer DC
		dc.Attach(printDlg.GetPrinterDC());
		dc.m_bPrinting = TRUE;
		CFont *OldFont; 
		CFont BaseFont;
		Manual=false;
      int nHorz;
		int nVert;
		if(dc.GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
		{
			nHorz = dc.GetDeviceCaps(LOGPIXELSX);
			nVert = dc.GetDeviceCaps(LOGPIXELSY);
		//	nHorz=600;
		}
		int FontPrinterWeldData = (25*nHorz)/PIXPERINCH;
		BaseFont.CreateFont(FontPrinterWeldData , 0, 0, 0, FW_NORMAL ,
		FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FF_DONTCARE, _T("Courier New"));
		
		OldFont=(CFont*)dc.SelectObject(&BaseFont);
		CString strTitle;
		strTitle.LoadString(AFX_IDS_APP_TITLE);
		// Initialise print document details
		DOCINFO di;
		::ZeroMemory (&di, sizeof (DOCINFO));
		di.cbSize = sizeof (DOCINFO);
		// application title appears in the spooler view
		di.lpszDocName = strTitle;
		// Begin a new print job
		BOOL bPrintingOK = dc.StartDoc( &di );
		CRect MyArea;
		CPrintInfo Info;     
      for (UINT page = Info.GetMinPage();bPrintingOK ; page++)
		{
				dc.StartPage();
				Info.m_nCurPage = page;
            int YCoordinate=660;////////////////////////////////////////////////
			   int XCoordinate=200;
           
            PrintHSCompareData(&dc,CPoint(100,200));
            CompareGraph_and_Data();
			 if(!OldVersionPresent)
			 {
				 POSITION pos1 = GraphDataList.GetHeadPosition();
				 int num=GraphDataList.GetCount();
			  
				 while(pos1)
				 {
					 CGraphData *object= 0;
					 object =GraphDataList.GetNext(pos1);
					 if((object->HS_CompareGraphNum==1) && (ScanA_On))
					 {
						 object->GraphData.GraphColour=2; 
						 object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);
					 }
					if((object->HS_CompareGraphNum==2)  && (ScanB_On))
					 {
						 object->GraphData.GraphColour=3; 
						 object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);
					 }				 			 
					 if((object->HS_CompareGraphNum==3)  && (ScanC_On))
					 {
						 object->GraphData.GraphColour=4; 
						 object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);
					 }
				 }
			 }
			 else
			 {
				POSITION pos1 = GraphOldDataList.GetHeadPosition();
				 int num=GraphOldDataList.GetCount();			  
				 while(pos1)
				 {
					 CGraphOldData *object= 0;
					 object =GraphOldDataList.GetNext(pos1);
					 if((object->HS_CompareGraphNum==1) && (ScanA_On))
					 {
						 object->GraphColour=2; 
						 object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);
					 }
					if((object->HS_CompareGraphNum==2)  && (ScanB_On))
					 {
						 object->GraphColour=3; 
						 object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);
					 }
					 if((object->HS_CompareGraphNum==3)  && (ScanC_On))
					 {
						 object->GraphColour=4; 
						 object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);
					 }				 
				 }
			 }
            DrawCompareHSgraph(&dc);
            
            bPrintingOK = (dc.EndPage() > 0);
            if (bPrintingOK)
				      dc.EndDoc();
			    else	// abort job.
				   dc.AbortDoc();
			   dc.SelectObject(OldFont);
			   // detach the printer DC
            dc.Detach();
            bPrintingOK=false;
      }
}

void CHistoryView::PrintWeldHistoryGraph()
{
      extratextinboth=0;
		CDC             dc;
		CPrintDialog    printDlg(FALSE);
		CRect           r;
		if (printDlg.DoModal() == IDCANCEL)
			return;
		// Attach a printer DC
		dc.Attach(printDlg.GetPrinterDC());
		dc.m_bPrinting = TRUE;
		CFont *OldFont; 
		CFont BaseFont;        
		int nHorz;
		int nVert;
		if(dc.GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
		{
			nHorz = dc.GetDeviceCaps(LOGPIXELSX);
			nVert = dc.GetDeviceCaps(LOGPIXELSY);
		//	nHorz=600;
		}
		int FontPrinterWeldData = (25*nHorz)/PIXPERINCH;
		BaseFont.CreateFont(FontPrinterWeldData , 0, 0, 0, FW_NORMAL ,
		FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FF_DONTCARE, _T("Courier New"));
		
		OldFont=(CFont*)dc.SelectObject(&BaseFont);
		CString strTitle;
		strTitle.LoadString(AFX_IDS_APP_TITLE);
		// Initialise print document details
		DOCINFO di;
		::ZeroMemory (&di, sizeof (DOCINFO));
		di.cbSize = sizeof (DOCINFO);
		// application title appears in the spooler view
		di.lpszDocName = strTitle;
		// Begin a new print job
		BOOL bPrintingOK = dc.StartDoc( &di );
		CPrintInfo Info;
      Manual =false;
	//	if(PrintGraphList.GetCount())
		{
			int GraphType;
		   bool ManualStr =false;
			bool ExtraGraphText =false;
		   int YCoordinate=ONEWELDLINEGAP;
         int temp,firstprinted=0;
			POSITION pos=PrintGraphWeldDataList.GetHeadPosition();
			for (UINT page = Info.GetMinPage();bPrintingOK && pos!=NULL; page++)
			{
				dc.StartPage();
				Info.m_nCurPage = page;
				//	if(PrintGraphWeldDataList.GetCount())
				{
					// begin new page
					CWeldData *object = PrintGraphWeldDataList.GetHead();
					temp=object->Print(&dc);
				}
				POSITION pos1;
				if(!OldVersionPresent)
				{
				    pos1= GraphObjects.GetHeadPosition();
					while(pos1)
					{
               		  CGraphData * object=GraphObjects.GetNext(pos1);
					  GraphType=object->GraphData.GraphTypeID;
					  if((GraphType==Graph1ID) || (GraphType==Graph2ID))
					  {
						 if((GraphType ==AMPLITUDEGRAPH) || (GraphType == FROCEGRAPH))
						 {
							ExtraGraphText=object->GraphData.ExtraTest;
							if(ExtraGraphText)
								CHistoryView::Manual =true;
							ManualStr=object->GraphData.ManualStr;
						 }
                      
						  if(((object->GraphData.GraphTypeID == AMPLITUDEGRAPH) && (object->GraphData.ExtraTest)) 
							 ||( (object->GraphData.GraphTypeID == FROCEGRAPH) && (object->GraphData.ExtraTest)))
							   {
							 extratextinboth++;
                     
						  }						 
					  }
					}
				}
				else
				{
					pos1 = GraphOldObjects.GetHeadPosition();
					while(pos1)
					{
               		  CGraphOldData * object=GraphOldObjects.GetNext(pos1);
					  GraphType=object->GraphTypeID;
					  if((GraphType==Graph1ID) || (GraphType==Graph2ID))
					  {
						 if((GraphType ==AMPLITUDEGRAPH) || (GraphType == FROCEGRAPH))
						 {
							ExtraGraphText=object->ExtraTest;
							if(ExtraGraphText)
								CHistoryView::Manual =true;
							ManualStr=object->ManualStr;
						 }
                      
						  if(((object->GraphTypeID ==AMPLITUDEGRAPH) && (object->ExtraTest)) 
							 ||( (object->GraphTypeID == FROCEGRAPH) && (object->ExtraTest)))
							   {
							 extratextinboth++;
                     
						  }
							 
					  }
					}
				}
				bool ExtraTextPrinted=false;
				if(!OldVersionPresent)
				{
					pos1 = GraphObjects.GetHeadPosition();
					while(pos1)
					{
              		YCoordinate=temp;
					  int XCoordinate=PRINTNOWGRAPHCORD; 
				   CGraphData * object=GraphObjects.GetNext(pos1);
						GraphType=object->GraphData.GraphTypeID;							
						if((GraphType==Graph1ID) || (GraphType==Graph2ID))
						{
							  YCoordinate+=ONELINEGAP;
							//printing manual text
							  if(firstprinted >0)
							  {
								 if(ExtraGraphText )
									  {
										  CGraphData::PrintGraphManualStr(&dc,GraphType,ExtraGraphText,
																	 YCoordinate+((3*ONELINEGAP*(extratextinboth-1))));
										  YCoordinate+=((4*ONELINEGAP*extratextinboth)+ONELINEGAP);
										  object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);
										  ExtraTextPrinted=true;
									  }
									  else
									  {
										  YCoordinate+=(5*ONELINEGAP);
										  object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);				
									  }
									break;
							   }
              
							   if(ExtraGraphText )
							   {                                            
							CGraphData::PrintGraphManualStr(&dc,GraphType,ExtraGraphText,YCoordinate-1);                        
								   YCoordinate+=((4*ONELINEGAP*extratextinboth)+ONELINEGAP);
								   object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);
								   ExtraTextPrinted=true;
							   }
							   else
							   {
								   YCoordinate+=(5*ONELINEGAP);
								   object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);				
							   }
							   if(ExtraTextPrinted)
							   {
								   YCoordinate=1125+(4*ONELINEGAP* extratextinboth);
								   ExtraTextPrinted=false;
							   }
						else
							YCoordinate=1125+ONELINEGAP;
							   if(ManualStr)
							   {

								   XCoordinate=PRINTGRAPHSTARTXCORD;
								   for(int y=0;y<5;y++)
								   {
									   YCoordinate+=ONELINEGAP;
									   DrawPrinterText(&dc,XCoordinate,YCoordinate,Manualstr[y]);
								   }
							   }
							   for(int z=0;z<4;z++)
							   {
								   YCoordinate+=(ONELINEGAP);
								   if(z==2)
								   {
									   CString s=object->ConvertToTCHAR(&object->GraphData.SystemPressure[0],20);
									   CString str=GraphPrText[z] + s;
									   DrawPrinterText(&dc,PRINTGRAPHSTARTXCORD,YCoordinate,str);
								   }
								   else
								   	   DrawPrinterText(&dc,PRINTGRAPHSTARTXCORD,YCoordinate,GraphPrText[z]);								   	
							   }
					  firstprinted++;
						}
				//	dc.StartPage();	
					}
				}
				else
				{
					pos1 = GraphOldObjects.GetHeadPosition();
					while(pos1)
					{
              		YCoordinate=temp;
					  int XCoordinate=PRINTNOWGRAPHCORD; 
				   CGraphOldData * object=GraphOldObjects.GetNext(pos1);
						GraphType=object->GraphTypeID;
						
						
						if((GraphType==Graph1ID) || (GraphType==Graph2ID))
						{
							  YCoordinate+=ONELINEGAP;
							//printing manual text
							  if(firstprinted >0)
							  {
								 if(ExtraGraphText )
									  {
										  CGraphOldData::PrintGraphManualStr(&dc,GraphType,ExtraGraphText,
																	 YCoordinate+((3*ONELINEGAP*(extratextinboth-1))));
										  YCoordinate+=((4*ONELINEGAP*extratextinboth)+ONELINEGAP);
										  object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);
										  ExtraTextPrinted=true;
									  }
									  else
									  {
										  YCoordinate+=(5*ONELINEGAP);
										  object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);				
									  }
									break;
							   }
              
							   if(ExtraGraphText )
							   {
                                            
							CGraphOldData::PrintGraphManualStr(&dc,GraphType,ExtraGraphText,YCoordinate-1);                        
								   YCoordinate+=((4*ONELINEGAP*extratextinboth)+ONELINEGAP);
								   object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);
								   ExtraTextPrinted=true;
							   }
							   else
							   {
								   YCoordinate+=(5*ONELINEGAP);
								   object->Print(&dc,XCoordinate,YCoordinate,PRINTLISTGRAPHID);				
							   }
							   if(ExtraTextPrinted)
							   {
								   YCoordinate=1125+(4*ONELINEGAP* extratextinboth);
								   ExtraTextPrinted=false;
							   }
							   else
							   {
								   YCoordinate=1125+ONELINEGAP;
							   }
							   if(ManualStr)
							   {

								   XCoordinate=PRINTGRAPHSTARTXCORD;
								   for(int y=0;y<5;y++)
								   {
									   YCoordinate+=ONELINEGAP;
									   DrawPrinterText(&dc,XCoordinate,YCoordinate,Manualstr[y]);
								   }
							   }
							   for(int z=0;z<4;z++)
							   {
								   YCoordinate+=(ONELINEGAP);
								   if(z==2)
								   {
									   CString s=object->ConvertToTCHAR(&object->SystemPressure[0],20);
									   CString str=GraphPrText[z] + s;
									   DrawPrinterText(&dc,PRINTGRAPHSTARTXCORD,YCoordinate,str);
								   }
								   else
								   {
									   DrawPrinterText(&dc,PRINTGRAPHSTARTXCORD,YCoordinate,GraphPrText[z]);
								   }
								
								
							   }
					  firstprinted++;
						}
				//	dc.StartPage();
				}		   
			}
			pos=NULL;
			bPrintingOK = (dc.EndPage() > 0);
			if (bPrintingOK)
				dc.EndDoc();
			 else	// abort job.
				dc.AbortDoc();
			dc.SelectObject(OldFont);
			// detach the printer DC
			dc.Detach();
		}
	}
}
void CHistoryView::DrawPrinterText(CDC *pDC,int X,int Y,
							 const CString &text)
{
	int nHorz;
	int nVert;
	CPoint p(X,Y);
	nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
	nVert = pDC->GetDeviceCaps(LOGPIXELSY);
	p =CalibPoint(p,nHorz,nVert);
	pDC->ExtTextOut(p.x, p.y,ETO_OPAQUE   ,NULL, text,NULL);
}

void CHistoryView::PrintHSCompareData(CDC *pDC, CPoint point)
{
   CString Str_CmpData[] = {"Compare Data"};
	CString  Str_CmpGraph[] = {"Compare Graphs"};
     int X2_CoOrdinate=110;
   int Y2_CoOrdinate=360;
   int X1_CoOrdinate=160;
   int Y1_CoOrdinate=65;
   X2_CoOrdinate=(X2_CoOrdinate-X1_CoOrdinate)*2 +point.x;
	Y2_CoOrdinate=(Y2_CoOrdinate-Y1_CoOrdinate)*2 +point.y;
	X1_CoOrdinate= point.x;
	Y1_CoOrdinate=point.y;
	CHistoryView::DrawPrinterText(pDC,X1_CoOrdinate+400,Y1_CoOrdinate-100,Str_CmpData[0] );
   CHistoryView::DrawPrinterText(pDC,X1_CoOrdinate+400,550,Str_CmpGraph[0] );
	//DrawPrinterText(pDC,PrintBigFont,Black, CRect(X1_CoOrdinate,Y1_CoOrdinate-100,X2_CoOrdinate,Y1_CoOrdinate-100),Str_CmpData[CChildView::Language_Index],true,CChildView::Language_Index);//Dra
	//DrawPrinterText(pDC,PrintBigFont,Black, CRect(X1_CoOrdinate,550,X2_CoOrdinate,550),Str_CmpGraph[CChildView::Language_Index],true,CChildView::Language_Index);
	/*Drawing Coloumn Headings.*/
	int X1 = X1_CoOrdinate+260;
	int X2 = X1_CoOrdinate +520;
	int i;
	for (i=0;i<3;i++)
	{
      CHistoryView::DrawPrinterText(pDC,X1,Y1_CoOrdinate-50,ColoumnHeading[i] );
	//	DrawPrinterText(pDC,	PrintSmallFont,Black, CRect(X1,Y1_CoOrdinate-50,X2,Y1_CoOrdinate-50),ColoumnHeading[i],false,CChildView::Language_Index);
		X1 =X2;
		X2 = X1+260;
	}
	int x = X1_CoOrdinate+260;
	int y=Y1_CoOrdinate+10;
	for(i=0;i<3;i++)
	{		
		for(int j =0;j<9;j++)
		{
         if((HighLight[i]+3) == j)
			{
				pDC->SetTextColor(COLORBLUE);
            CHistoryView::DrawPrinterText(pDC,x,y,CompareData[j][i] );
			}
			else
			{
				pDC->SetTextColor(COLORBLACK);
            CHistoryView::DrawPrinterText(pDC,x,y,CompareData[j][i] );
			}      
			//DrawPrinterText(pDC, PrintSmallFont, Black, CRect(x,y,x+260,y+60),CompareData[j][i],false,CChildView::Language_Index);
			y+=30;
		}
		x+=260;
		y=Y1_CoOrdinate+10;
	}
	/*Drawing Row Headings.*/
	int Y1 = Y1_CoOrdinate+10;
	int Y2 = Y1+60;
	for(int j=0;j<9;j++)
	{
      CHistoryView::DrawPrinterText(pDC,X1_CoOrdinate+50,Y1,RowHeading[j] );
		//DrawPrinterText(pDC, PrintSmallFont,Black, CRect(X1_CoOrdinate+50,Y1,X1_CoOrdinate+200,Y1+60),RowHeading[j],false,CChildView::Language_Index);
				Y1 = Y1+30;
	}

	CPen penLine;
	CPen *OldPen;
	penLine.CreatePen(PS_SOLID, 2, CHistoryView::Color_Array[1]);
	OldPen = pDC->SelectObject(&penLine);
	CPoint p1(X1_CoOrdinate+50,Y1_CoOrdinate);
	CPoint p2(X1_CoOrdinate+950,Y1_CoOrdinate);
	int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
	int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
	p1=CalibPoint(p1, nHorz,nVert);
	p2=CalibPoint(p2, nHorz,nVert);
	pDC->MoveTo(p1);
	pDC->LineTo(p2);
	pDC->SelectObject(OldPen);
	penLine.DeleteObject();
}
