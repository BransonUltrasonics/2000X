// HistoryView.h : interface of the CHistoryView class
//
/////////////////////////////////////////////////////////////////////////////
/*
Revision #		Date		Author			Description
----------		--------	----------		-------------------------------------
1.0				04/24/06	LAM				Initial Version.
1.1				05/10/07	BSahu			Modified Code to Add View HosrnScan Graphs.
1.2				10/22/07	BSahu			Modified Code to Add Printing Feature.
1.3				10/25/07	BSahu		    Modified Code to Fix Weld Cycle over lap issue.
1.4				10/29/07	BSahu		    Modified Code to Modifie WeldHistory printout data
1.5				09/26/09	PDwivedi		Added changes for compatability of graph Object.
*/

#if !defined(AFX_HISTORYVIEW_H__71B8B6F3_7867_4CEA_A971_BFCFF7545EE7__INCLUDED_)
#define AFX_HISTORYVIEW_H__71B8B6F3_7867_4CEA_A971_BFCFF7545EE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WeldData.h"
#include "GraphData.h"
#include "GraphOldData.h"
#include "HistoryDoc.h"
#include "Buttons.h"
#include "Browse.h"
#include "MainFrm.h"

#define COLORNONE			RGB(255,255,255)	
#define COLORBLACK			RGB(0,0,0)	
#define COLORRED			RGB(255,0,0)	
#define COLORGREEN			RGB(0,255,0)	
#define COLORBROWN			RGB(0,0,128)	
#define COLORBLUE			RGB(0,0,255)	
#define COLORMAGENTA		RGB(128,0,128)	
#define COLORCYAN			RGB(0,255,255)	
#define COLORLIGHTGREY		RGB(192,192,192)	
#define COLORGREY			RGB(128,128,128)
#define COLORYELLOW			RGB(255,255,0)	
#define COLORWHITE			RGB(255,255,255)
#define ParamRectWidth		115
#define ParamRectWidthPrint		370
#define ParamHeadingRectWidthPrint 350
#define MaxColoumnPerScreen 5
#define LINE_GAP			30
#define LINE_GAP_PRINT      50
#define LINE_GAP_HEADING    290            
#define MaxCyclePerScreen	7
#define HISTORY_TBL_START_X	20
#define HISTORY_TBL_START_Y	30
#define HISTORY_TBL_START_X_PRINT	60
#define HISTORY_TBL_START_Y_PRINT	160
#define SCREEN_START_X		0
#define SCREEN_START_Y		0
#define	SCREEN_END_X		640
#define SCREEN_END_Y		480
#define LINEGAP_Y 100
#define NEXTRECT	CRect(530,390,530+90,390+40)
#define BACKRECT CRect(20,390,90+20,40+390)
#define EXITRECT CRect(275,390,275+90,390+40)

#define MESSAGESCRN_BLACKRECT CRect(119,119,521,361)
#define MESSAGESCRNRECT CRect(120,120,	520,360)
#define TITLE_RECT CRect(1, 1, 639, 40)
#define BOTTOM_RECT CRect(1, 440, 639, 479)
#define MESSAGESCRNTIME		500
#define MESSAGE_TIMER	01

#define PRINTWELDSTARTYCORD			150
#define FOURWELDLINEGAP				80
#define MaxAlarmString				256

#define SINGLECLICK		01
#define	DOUBLECLICK		02
#define LISTBOXID		50
#define OPENPSID		51

#define GRAPH_START_X_CORD	100
#define GRAPH_START_Y_CORD	45
#define GRAPH_END_X_CORD	500
#define GRAPH_END_Y_CORD	389
#define HSGRAPH_HEIGHT		344
#define MAXYCOORDINATE		14230
#define DEFAULTMINPAGE		1
#define DEFAULTMAXPAGE		2

#define PRINTLISTGRAPHID	 5
#define POWERGRAPHID		 6
#define COLDISTANCEID		 7
#define VELOCITYGRAPHID		 8
#define FORCEGRAPHID		 9
#define AMPLITUDEGRAPHID	 10
#define FREQUENCYGRAPHID	 11
#define PRINTNOWGRAPHCORD	 200
#define Asian_Language_Start 04
#define CALIBX(point,HPIX) (point * HPIX)/PIXPERINCH
#define CALIBY(point,VPIX) (point * VPIX)/PIXPERINCH
#define Calib(p, HorPix,VerPix) CRect(CALIBX(p.left,HorPix),CALIBY(p.top,VerPix),CALIBX(p.right,HorPix),CALIBY(p.bottom,VerPix))

#define CalibPoint(p, HorPix,VerPix) CPoint(CALIBX(p.x,HorPix),CALIBY(p.y,VerPix))

#define PIXPERINCH				150
#define YEARMONTHFOLDERNAME		7
#define YEARSIZE				4
#define MONTHSIZE				2
#define DATESIZE				2
#define JAN						1
#define FEB						2
#define MAR						3
#define APR						4
#define MAY						5
#define JUN						6
#define JUL						7
#define AUG						8
#define SEP						9
#define OCT						10
#define NOV						11
#define DEC						12
#define ERRORBEEP		Beep(5000,100) 

enum FORMAT	 {						  /*  US Format (units)  SI Format (units) */
	   PERCENT,                       /*        xxx     %          xxx     %   */
	   FORCE,                         /*       xxxx    lb         xxxx     N   */
	   FORCEDIV10,                    /*     xxxx.x    lb         xxxx     N   */
	   TIME,                          /*     xx.xxx     S       xx.xxx     S   */
	   PRESSURE,                      /*        xxx    PSI         xxx   KPA   */
	   DISTANCE,                      /*     x.xxxx    in      xxx.xxx    mm   */
	   DISTANCE3,                     /*     x.xxxx    in       xx.xxx    mm   */
	   FREQUENCY,                     /*      xxxxx    Hz        xxxxx    Hz   */
	   FREQOFFSET,                    /*       Sxxx    Hz         Sxxx    Hz   */
	   ENERGY,                        /*     xxxxxx     j       xxxxxx     j   */
	   COUNTER,                       /*  xxxxxxxxx          xxxxxxxxx         */
	   VELOCITY,                      /*      xx.xx  in/s        xxx.x  mm/s   */
	   WATTS,                         /*      xxxx   W            xxxx  W      */
	   BARGRAPH,                      /* [____|____]        [____|____]        */
	   TIMEDATE,                      /* xx:xx xx/xx/xx                        */
	   PERCENTX10,
	   ENERGYDIV10,
	   INTEGER,
	   LONGTIME,
	   MICRONS
	};

class CWeldData;
class CHistoryView : public CView
{
protected: // create from serialization only

	
	DECLARE_DYNCREATE(CHistoryView)
	CBitmapButton *ButtonLeft;
	CBitmapButton *ButtonRight;
	CBitmapButton *ButtonUp;
	CBitmapButton *ButtonDown;
	CBitmapButton *ButtonPageUp;
	CBitmapButton *ButtonPageDown;
	CButtons *ButtonExit;
	CButtons *ButtonGraph;
	CButtons *ButtonGraphAmp;
	CButtons *ButtonGraphColDist;
	CButtons *ButtonGraphForce;
	CButtons *ButtonGraphVelocity;
	CButtons *ButtonGraphFreq;
	CButtons *ButtonGraphPower;
	CButtons *ButtonGraphExit;
	CButtons *Buttonprint;
	CButtons *ButtonScanA;
	CButtons *ButtonScanB;
	CButtons *ButtonScanC;
	CButtons *ButtonScanExit;
	CButtons *ButtonprintGraph;
   CButtons *ButtonprintHSGraph;
   CButtons *ButtonprintHSData;
static 	CString HSFolderPath;
static bool HSMenu;	
static	int SelectedWeldData;
static int LeftMostParameter;
static	int TotalCycle;
static	int *Parameter_ID;
static	int TotalColoumn;
static	int TopMostData;
static	bool SelectedDataUnit;
static	int SelectedWeldId;
static int FileOpenParam;
static int GraphParam;
static int GraphSelect;
static int GraphPrintSelect;
static int ExitGraphParam;
static int GraphFileSelect;
static bool GraphFound;
static bool NoValidGraph;
static DWORD Color_Array[12];
static int ExitParam;
static int extratextinboth;


	// Attributes
public:
   CHistoryView();
	static void DrawPrinterText(CDC *pDC,int X,int Y,const CString &text);
	static int NoOfWeldObjectPrinted;
	static CString ModePresetString;
	POSITION nPrintPos;
	CList<CString, CString>WeldHistoryAlarmStringList;
	static	CString AlarmEng[MaxAlarmString];
	int CreateFontSize(CDC *pdc, int points);
	CRect UserPage(CDC * pDC, float margin);
	void PrintString(char *p, DWORD pSize);
	CRect m_rcPrintRect;
	static CString PrinterName;
	static CString HZData[3];
	static int Language_Index;
	static int HighLightString;
   static bool Manual ;
	static short Parameter_Units_Metric_temp[MAXPARAMVALUES + 1][MAXPARAMUNITLENGTH];
	static short Parameter_Units_USCS_temp[MAXPARAMVALUES + 1][MAXPARAMUNITLENGTH];
	static CString WelddataHeadings[MAXPARAMVALUES + 1] ;
   static CString Parameter_Units_USCS[MAXPARAMVALUES + 1];
   static CString Parameter_Units_Metric[MAXPARAMVALUES + 1];
	
   /*----------------------------CATL----------------------------*/
   static int Parameter_Formats[MAXPARAMVALUES + 1];
   static CString Parameter_Units_Formats[MAXPARAMVALUES + 1];
	static  bool AmpMicronsFormat, PowerWattsFormat;
   /*----------------------------CATL----------------------------*/

   	CHistoryDoc* GetDocument();
	virtual afx_msg void Right();
	virtual afx_msg void Left();
	virtual afx_msg void Up();
	virtual afx_msg void Down();
	virtual afx_msg void Graph();
	virtual afx_msg void PageUp();
	virtual afx_msg void PageDown();
	virtual afx_msg void Exit();
	virtual afx_msg void AmpGraph();
	virtual afx_msg void ColDistGraph();
	virtual afx_msg void ForceGraph();
	virtual afx_msg void VelocityGraph();
	virtual afx_msg void FreqGraph();
	virtual afx_msg void ExitGraph();
	virtual afx_msg void PowerGraph();
	virtual afx_msg void ScanAGraph();
	virtual afx_msg void ScanBGraph();
	virtual afx_msg void ScanCGraph();
	virtual afx_msg void PrintWeldHistoryData();
	virtual afx_msg void PrintWeldHistoryGraph();
   virtual afx_msg void PrintHSData();
	 static int Graph1ID;
	static int Graph2ID;
	bool OldVersionPresent;
// Operations
public:
	CList<int ,int>PageNumList;
	CTypedPtrList<CPtrList, CWeldData *> WeldObjects;
	CTypedPtrList<CPtrList, CWeldData *> WeldObjectsList;
	CTypedPtrList<CPtrList, CGraphData *> GraphObjects;
	CTypedPtrList<CPtrList, CGraphOldData *> GraphOldObjects;

	CTypedPtrList<CPtrList, CButtons *> ScreenObjects;
//	CTypedPtrList<CPtrList, CGraphData *> PrintGraphList;
	CTypedPtrList<CPtrList, CWeldData *> PrintGraphWeldDataList;
	static void DrawText(CDC * pDC, int color,bool LargeFont, const CRect &rect, const CString &text,bool Center_Text);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistoryView)
	public:
//		virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void PrintHSCompareData(CDC *pDC, CPoint point);
   static 	bool present;
   int HighLight[3];
   CString CompareData[9][3];
	CString RowHeading[9];
	CString ColoumnHeading[3];

	void EditGraphList(bool On_Off,int graphNum);
    static bool ScanA_On;
	static bool ScanB_On;
	static bool ScanC_On;
	bool CurrentScan_On;

	bool ScanA_Present;
	bool ScanB_Present;
	bool ScanC_Present;
	bool CurrentScan_Present;

	static bool HS1_Present;
	static bool HS2_Present;
	static bool HS3_Present;
	static bool HSFlag;
	int HS_CompareGraphNum;
	CTypedPtrList<CPtrList, CGraphData *> GraphDataList;
	CTypedPtrList<CPtrList, CGraphOldData *> GraphOldDataList;

static 	CString GetString(unsigned char *&data, int &length);
	bool CompareGraph_and_Data();
	bool DrawCompareHSData(CDC *pDC);
	void DrawCompareHSgraph(CDC *pDC);
	static bool FileCreated;
	void DrawParameterHeadings(CDC *pDC);
	void PaintWindow();
	static CFont SmallFont,BigFont,WeldDataPrint;
	static bool DisableFlag;
	static CString YearMonthName;
	static CString PSName;
   void DrawGraphs(CDC *pDC);
	void DrawHSGraphs(CDC *pDC);
	void DrawWeldData(CDC *pDC);
//	void PrintWeldData(CDC *pDC,int XCoOrdinate,int YCoOrdinate,CPrintInfo* pInfo);
	void PrintParameterHeadings(CDC *pDC,int XCoOrdinate,int YCoOrdinate);
	static CString TitleString;
	static CHistoryView* View;
	static CString PreviousFileName;
	static bool PreparePSList(CString SelFilePath);
	static bool PrepareHSList(CString SelFilePath);
	void RecalculateMenu();
	static void ShowMessageScreen(CString Message);
	enum {
			BRANSONLOGO,
			BROWSING,
			HIERARCHYYEARMONTH,
			HIERARCHYDAY,				
			WELDDATA,
			GRAPHS,
			HIERARCHYHSFOLDER,
			HIERARCHYHSDATA,
			HIERARCHYHSGRAPH
		}BrowsingLevel;

	void DrawPageNumber(CDC *pDC);
	void CreateScreenButton();
	void GraphIfPresent(int GraphTypeID);
	static int LastGraphDisplyaed;
	int LastGraphDisplayed;
	CString WeldDataPath;
	bool ReadData();
	bool ReadGraph();
	virtual ~CHistoryView();
//	void OnPrint(CDC* pDC, CPrintInfo* pInfo);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int PageNum;
	
	CListBox *ListBox;
	CButton *OpenPS;
	CStringList FilePath;
	CStringList FileName;
	CString DataFolder;

	CString GetFolderPath();
	static CString GetDiaplayName(CString Name);
	static bool ValidFolder(CString FileName);
	// void AddDriveLetters();
//	bool PrepareList();

// Generated message map functions
protected:
	//{{AFX_MSG(CHistoryView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void DrawFirstScreen();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOpenPSNew();
	afx_msg void OnProgramExit();
	afx_msg void OnDestroy();
	afx_msg void OnHSOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HistoryView.cpp
inline CHistoryDoc* CHistoryView::GetDocument()
   { return (CHistoryDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORYVIEW_H__71B8B6F3_7867_4CEA_A971_BFCFF7545EE7__INCLUDED_)
