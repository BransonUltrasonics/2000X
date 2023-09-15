// VgaDrawGraph.h: interface for the CVgaDrawGraph class.
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
/******************************************************************************/ 
/*                                                                            */
/*                                                                            */
/*      Copyright (c) Branson Ultrasonics Corporation, 2005                   */
/*     This program is the property of Branson Ultrasonics Corporation        */
/*   Copying of this software is expressly forbidden, without the prior       */
/*   written consent of Branson Ultrasonics Corporation.                      */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/******************************************************************************/ 
/*
Revision #    Date      Author    Description
----------  --------  ----------  -------------------------------------
  1.0       06/06/08	   PDwivedi  Added Initial Version.
  1.1       08/01/08	   PDwivedi  Added Member declarations.
  1.2       08/08/08    PDwivedi  Final Code Clean up.
  1.3       09/12/08    PDwivedi  Added changes for Tracker issues of round 2 testing for version LangTestJ.
  1.4       09/22/09    PDwivedi  Added changes for Graph Screen in bug.

*/

#if !defined(AFX_VGADRAWGRAPH_H__6C1B23C5_9722_489E_9767_77E91B2FC5F0__INCLUDED_)
#define AFX_VGADRAWGRAPH_H__6C1B23C5_9722_489E_9767_77E91B2FC5F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define TICKLSTRRECT			CRect(800,1225,800,1225)
#define TICKHSTRRECT			CRect(500,1225,500,1225)
#define TICKWSTRRECT			CRect(100,1225,100,1225)
#define TICKFSTRRECT			CRect(800,1175,800,1175)
#define TICKASTRRECT			CRect(500,1175,500,1175)
#define TICKTSTRRECT			CRect(100,1175,100,1175)
#define TICKLVALUERECT			CRect(1050,1225,1050,1225)
#define TICKHVALUERECT			CRect(700,1225,700,1225)
#define TICKWVALUERECT			CRect(350,1225,350,1225)
#define TICKFVALUERECT			CRect(1050,1175,1050,1175)
#define TICKAVALUERECT			CRect(700,1175,700,1175)
#define TICKTVALUERECT			CRect(350,1175,350,1175)
#define TIMESTRINGRECT			CRect(600,1125,600,1125)
#define HORNSCANPRINTRECT		CRect(100,100,100,100 )
#define DATEPRINTRECT			CRect(150,125 ,150,125 )
#define TIMEPRINTRECT			CRect(150,150 ,150,150 )
#define RESONANCEPRINTRECT		CRect(80,470 ,80,470)
#define FREQPRINTRECT			CRect(80,495,80,495 )
#define FREQHZRECT           CRect(570,925,570,925 )
#define DIGITUNEPRINTRECT		CRect(100,950,100,950 )
#define RESONANCEFREQPRINTRECT	CRect(100,975 ,100,975 )
#define RESONANCEHSCEPRINTRECT	CRect(50,850 ,50,850)
#define FREQHSCPRINTRECT		CRect(50,875,50,875 )

#define INCLABEL		10
#define GRAPH_WIDTH		400 
#define HS_GRAPH_HEIGHT 270
#define STARTXRESONANCE 100
#define STARTYRESONANCE 1025
#define HEIGHT_LOWER_HSGRAPH	72

#define DEFAULT_GRAPHX_START   100
#define DEFAULT_GRAPHY_START   50
#define DEFAULT_GRAPHX_END   500
#define DEFAULT_GRAPHY_END   394

#define DEFAULT_HSGRAPHX_START   120
#define DEFAULT_HSGRAPHY_START   65
#define DEFAULT_HSGRAPHX_END     520
#define DEFAULT_HSGRAPHY_END     335   

enum WHICHGRAPH {       
     AMPLIGRAPH,
     POWGRAPH,
     FREQUGRAPH,
     DISTINGRAPH,
     FORCELBGRAPH,
     VELINGRAPH,
     DISTMMGRAPH,
     FORCENGRAPH,
     VELMMGRAPH,
     ABSINGRAPH,
     ABSMMGRAPH,
     CURRENTGRAPH,
     POW_DISTMMGRAPH,
     POW_DISTINGRAPH,
     POW_FORCENGRAPH,
     POW_FORCELBGRAPH,
     FORCEN_DISTMMGRAPH,
     FORCELB_DISTINGRAPH,
     PHASEGRAPH,
     PMC_GRAPH,
     NO_VALID_GRAPH
};    

#include "VgaMenuItem.h"
#include "ChildView.h"	
#include "PrintText.h"

class CXmlElement;

class CVgaDrawGraph : public CVgaMenuItem  
{
public:
  /* CString Str_PMCGraphs;
   CString StrCurrent;
   CString Str_PwrAvg;
   CString Str_PMCWeld;
   CString Str_PMCCycles;*/

   CString CycleCountID;
	static bool GraphBoundary;
	static bool PrintGraphBoundary;
	static int GraphCount;
	
	bool AlreadyPrinted;
	int PMCCycleCount;
	int Lang_Index;
	CString DateString;
	CString TimeString;
	bool HSCompareGraph;
	CString DigitalTuneSetting;
   int GraphType;
	

	int HS_CompareGraphNum;
	CString FreqString[6];
   CString No_Graph_String;
   int  TotalStrings;
	int No_Graph_String_Color;

   struct GraphStruct{

	int graph_type; 
   int GraphRequestValue;
   int GraphNum;
	int GraphColour;
   TCHAR CycleCount[20];
   TCHAR GRAPHTITLE[20];
   int GraphWidth;
   int no_of_ticks;
	int GRAPH_HEIGHT;
	
	int GRAPH_START_X;
	int GRAPH_START_Y;
	int GRAPH_END_X	;  
	int GRAPH_END_Y	;
	short DataLength;
	short graphdata[GRAPH_WIDTH];
   struct tick_str
	{
		char tick_char;
		short tick_location;
	}tick[6];
   int TickData[7];
   TCHAR HData[11][10];
	TCHAR VData[4][8];
   TCHAR SystemPressure[20];
	bool ManualStr;
	bool ExtraText;
   }GraphData;
   
   virtual void Draw(CDC* pDC);
   CVgaDrawGraph(CXmlElement * e);
	CVgaDrawGraph(int ID);
   CVgaDrawGraph();
	virtual ~CVgaDrawGraph();
   void CopyGraph(CVgaDrawGraph *Graph);
  	void StoreDate_Time(unsigned char *&data,int &length);
	void Print(CDC *pDC, CPoint TopLeft,int GraphType,CChildView *view);
   bool GraphForUSB(CChildView *view);
	bool GraphForPrinting(CChildView *view);
	void PrintHSText(CChildView *View,CDC *pDC);
   void DrawAvgPowerGraph(CDC *pDC,CChildView*view);
   void RecalculateAverageGraph(CChildView* view);

public:
   float atofloat(CString value);
	void PrintGraphData(CDC *pDC,bool Manual);
	virtual bool MouseClick(const CPoint &p, CChildView *view);
   static bool PrintGraphManualStr(CPoint p, CDC* pDC,int Type, bool ExtraText);
	void DrawAveragePowerGraph(CDC*pDC);
	void YAxis2Graduation(CDC* pDC);
	void StoreTickData(unsigned char* &data, int &length);
	void Store_VData_HData(unsigned char * &data, int & length);
	void drawgraph(CDC *pDC);
	void SetGraphRequestValue(int Graph_Type);
	void DrawTickMarks( CDC *pDC);
	void DrawGraphBoundary( CDC *pDC);
	void DrawVLabel(CDC *pDC);
	void DrawHLabel(CDC *pDC);
};

#endif // !defined(AFX_VGADRAWGRAPH_H__6C1B23C5_9722_489E_9767_77E91B2FC5F0__INCLUDED_)
