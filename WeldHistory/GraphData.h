// GraphData.h: interface for the CGraphData class.
//
//////////////////////////////////////////////////////////////////////

/*
Revision #		Date		Author			Description
----------		--------	----------		-------------------------------------
1.0				04/24/06	LAM				Initial Version.
1.1				05/10/07	BSahu			   Modified Code to Add View HosrnScan Graphs.
1.2				05/23/07	BSahu          Modified CGraphData object for Tracker issue 4140
1.3				10/22/07	BSahu          Modified to Add Printing Feature
1.4				10/25/07	BSahu          Modified Fix Overlap Issue.
*/
#if !defined(AFX_GRAPHDATA_H__27259361_66A9_4E31_A93E_5D6ACF0F03F3__INCLUDED_)
#define AFX_GRAPHDATA_H__27259361_66A9_4E31_A93E_5D6ACF0F03F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define GRAPH_WIDTH		400 
#define MAX_VIEWGRAPH_YCORD			158	
//#define MAX_TICK_MARKS  6 
#define TICKTRIG		0
#define GRAPH_PRESCALE 1.7
#define INCLABEL		10
#define AMPLITUDEGRAPH  4099
#define COLDISTGRAPH    4102
#define FORCEGRAPH		4111
#define FREQUENCYGRAPH  4114
#define POWERGRAPH		4124
#define VELOCITYGRAPH	4192
#define HORNSCANGRAPH	4125
#define MAX_HS_YCORD				136	
#define MAX_VIEWGRAPH_YCORD			158
#define HEIGHT_LOWER_HSGRAPH	72

#define TICKLSTRRECT			CRect(800,1125,800,1125)
#define TICKHSTRRECT			CRect(500,1125,500,1125)
#define TICKWSTRRECT			CRect(100,1125,100,1125)
#define TICKFSTRRECT			CRect(800,1075,800,1075)
#define TICKASTRRECT			CRect(500,1075,500,1075)
#define TICKTSTRRECT			CRect(100,1075,100,1075)
#define TICKLVALUERECT			CRect(1050,1125,1050,1125)
#define TICKHVALUERECT			CRect(700,1125,700,1125)
#define TICKWVALUERECT			CRect(350,1125,350,1125)
#define TICKFVALUERECT			CRect(1050,1075,1050,1075)
#define TICKAVALUERECT			CRect(700,1075,700,1075)
#define TICKTVALUERECT			CRect(350,1075,350,1075)
#define TIMESTRINGRECT			CRect(600,1025,600,1025)

#define TICK_PRESCALE			1000


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
class CGraphData  
{
public:
	short SystemPressure[20];
	bool AlreadyPrinted;
	bool ManualStr;//ExtraStrIfForceGraph;
	bool ExtraTest;//ExtraStrIfAmpGraph;
	int TickData[7];
	void InitilizeData();
	CGraphData();
	
	virtual ~CGraphData();

	int PMCCycleCount;
	int Lang_Index;
	short HData[11][10];
	short VData[4][8];
	CString DateString;
	CString TimeString;
	bool HSCompareGraph;
	int GraphRequestValue;
	int GraphNum;
	int GraphTypeID;
	int HS_CompareGraphNum;
	static bool GraphBoundary;
	static bool PrintGraphBoundary;
	static int GraphCount;
	int GraphColour;
	CString FreqString[6];
	int  TotalStrings;
	int GraphWidth;
	short CycleCount[20];
	CString No_Graph_String;

	short GRAPHTITLE[20];
	int no_of_ticks;
	int GRAPH_HEIGHT;
	
	int GRAPH_START_X;
	int GRAPH_START_Y;
	int GRAPH_END_X	;
	int GRAPH_END_Y	;
	int No_Graph_String_Color;
	short DataLength;
	short graphdata[GRAPH_WIDTH];
	struct tick_str
	{
		char tick_char;
		short tick_location;
	}tick[6];
	CString DigitalTuneSetting;

	CString ConvertToTCHAR(short* Ptr,int Length);
	void Draw(CDC* pDC);
	void drawgraph(CDC *pDC);
	void DrawGraphBoundary( CDC *pDC);
	void DrawHLabel(CDC *pDC);
	void StoreTickData(unsigned char* &data, int &length);
	void DrawTickMarks( CDC *pDC);
	void DrawVLabel(CDC *pDC);
	void GetCharString(unsigned char *&data, int &length,CString *Str);
	int Convert_Char_To_Integer(unsigned char *&data,int &length,int  len);
	CGraphData(unsigned char * &data, int & length);
//	void YAxis2Graduation(CDC* pDC);
	void Store_VData_HData(unsigned char * &data, int & length);
	//void SetGraphRequestValue(int Graph_Type);
	void PrintGraphData(CDC *pDC,bool Manual);
	void Print(CDC *pDC,int XCoordinate,int YCoordinate,int GraphType);
	static bool PrintGraphManualStr(CDC *pDC,int Type, bool ExtraText,int YCoordinate);
	void StoreDate_Time(unsigned char *&data, int &length);

	};

#endif // !defined(AFX_GRAPHDATA_H__27259361_66A9_4E31_A93E_5D6ACF0F03F3__INCLUDED_)
