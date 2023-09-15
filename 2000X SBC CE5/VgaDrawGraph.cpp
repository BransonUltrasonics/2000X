// VgaDrawGraph.cpp: implementation of the CVgaDrawGraph class.
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
  1.1       06/12/08    PDwivedi  Modify DrawGraph for PMC SCreen.
  1.2       08/01/08	   PDwivedi  Added changes for Printing & removed all strings.
  1.3       08/08/08    PDwivedi  Final Code Clean up.
  1.4       09/12/08    PDwivedi  Added changes for Tracker issues of round 2 testing for version LangTestJ.
  1.5       09/22/09    PDwivedi  Added changes for Graph Screen bug.
  1.6       11/06/09    PDwivedi  Added changes for Moving tick Char down by 20 pixls.
  1.7		11/25/13    HSanchez  Added fix to Store_VData_HData. it to do not show unnespected values on the Graph of horn scan.
*/

#include "stdafx.h"
#include "SBC.h"
#include "VgaDrawGraph.h"
#include "Table.h"

extern CChildView::PrintValues Setup,WeldHistory,PowerGraph,ColDistance,VelocityGraph,
			ForceGraph,AmplitudeGraph,FrequencyGraph,PrintSequence,Welddata;

extern CChildView::USBValues  USBWelddata,USBPowerGraph,USBColDistance,USBVelocityGraph,
			USBForceGraph,USBAmplitudeGraph,USBFrequencyGraph;
extern CList<CString,CString> tempGraphsList;
extern CList<CString,CString> tempHornScanList;
extern POSITION HornScanTemp_pos;
extern POSITION GraphsTemp_pos;

extern CList<CString,CString> tempScanGraphDataList;
extern CList<CString,CString> tempScreenGraphsList;
extern POSITION ScreenGraphsTemp_pos;
extern POSITION ScanGraphsDataTemp_pos;

#define MAX_TICK_MARKS  6 
#define TICKTRIG		0
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
#define MAX_HS_YCORD				136	
#define MAX_VIEWGRAPH_YCORD			158	

#define GRAPH_PRESCALE 1.7
#define TICK_PRESCALE  1000

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CList<CString,CString> tempHornScanList;
extern CList<CString,CString> tempGraphsList;
extern POSITION HornScanTemp_pos,GraphsTemp_pos;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVgaDrawGraph::CVgaDrawGraph(CXmlElement * e)
{
   
	GraphData.GraphWidth=GRAPH_WIDTH;
	//GraphCount++;
	//GraphNum =GraphCount;
	GraphData.GRAPH_START_X	= _ttoi(e->GetAttribute("X1"))+XOFFSET;//	CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH)+XOFFSET;
	
	GraphData.GRAPH_START_Y =_ttoi(e->GetAttribute("Y1"))+XOFFSET-5;// CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH)+XOFFSET-5;

	GraphData.GRAPH_END_X	= _ttoi(e->GetAttribute("X2"))+XOFFSET;//CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH)+XOFFSET;

	GraphData.GRAPH_END_Y	= _ttoi(e->GetAttribute("Y2"))+XOFFSET-5;//CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH)+XOFFSET-5;

	GraphData.GRAPH_HEIGHT = GraphData.GRAPH_END_Y-GraphData.GRAPH_START_Y;
   GraphType= _ttoi(e->GetAttribute("GraphType"));
	GraphData.GraphColour= _ttoi(e->GetAttribute("Color"));//*data++;length--;
   textID=e->GetAttribute("GraphTitle");
   CycleCountID= e->GetAttribute("CycleCount");
   CString str=CVgaMenuItem ::LinearSearch(textID/*e->GetAttribute("GraphTitle")*/);
   _tcscpy(GraphData.GRAPHTITLE , str);
}


CVgaDrawGraph::CVgaDrawGraph(int ID)
{
   if(ID  == (PMC_GRAPH-1))
   {
      GraphData.GRAPH_START_X	= DEFAULT_GRAPHX_START;//	CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH)+XOFFSET;
	
	   GraphData.GRAPH_START_Y = DEFAULT_GRAPHY_START;// CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH)+XOFFSET-5;

	   GraphData.GRAPH_END_X	= DEFAULT_GRAPHX_END;//CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH)+XOFFSET;

	   GraphData.GRAPH_END_Y	= DEFAULT_GRAPHY_END;//CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH)+XOFFSET-5;
   }
   else
   {
      GraphData.GRAPH_START_X	= DEFAULT_HSGRAPHX_START;//	CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH)+XOFFSET;
	   
	   GraphData.GRAPH_START_Y = DEFAULT_HSGRAPHY_START;// CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH)+XOFFSET-5;

	   GraphData.GRAPH_END_X	= DEFAULT_HSGRAPHX_END;//CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH)+XOFFSET;

	   GraphData.GRAPH_END_Y	= DEFAULT_HSGRAPHY_END;//CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH)+XOFFSET-5;
   }

   for(int i=0;i<20;i++)
		 GraphData.GRAPHTITLE[i]='\0';
   _tcscpy(GraphData.GRAPHTITLE , CChildView::thisPtr->GraphTitle);
   GraphData.GRAPH_HEIGHT = GraphData.GRAPH_END_Y-GraphData.GRAPH_START_Y;
}

CVgaDrawGraph::CVgaDrawGraph()
{	
	
}

CVgaDrawGraph::~CVgaDrawGraph()
{

}



bool CVgaDrawGraph::PrintGraphBoundary=false;
int CVgaDrawGraph::GraphCount=0;
bool CVgaDrawGraph::GraphBoundary=false;



void CVgaDrawGraph::Draw(CDC* pDC)
/***************************************************************************/
/*Description:-                                                            */
/* Draws Graph Screen.									                   */
/***************************************************************************/
{
//	printf("\n Draw");
   if(GraphData.graph_type == PMC_GRAPH)
	{
		
		if(PMCCycleCount!=0)
			drawgraph(pDC);
		return;
	}
	//unsigned char vdata
	if(!GraphBoundary)
   {
//		printf("\n drawing graph boundary");
      DrawGraphBoundary(pDC);//Draw Graph boundary only once in case of dual graph.
//      printf("\n after DrawGraphBoundary");
   }
	else if((GraphData.graph_type<(PMC_GRAPH-1))||(GraphData.graph_type>PMC_GRAPH))//(graph_type !=CScreenObject::VGA_HORNSCANGRAPH)
		YAxis2Graduation(pDC);
	//if((graph_type ==CScreenObject::VGA_NOGRAPH)||(graph_type ==CScreenObject::VGA_NOHSGRAPH))	// No Valid Graph data 
	if(GraphData.graph_type>PMC_GRAPH)
   {
//      printf("\n GraphType>MaxGraphType");
      CVgaMenuItem::DrawText(pDC,Bigfont,2,CRect(GraphData.GRAPH_START_X,GraphData.GRAPH_START_Y ,GraphData.GRAPH_END_X	,	
										GraphData.GRAPH_END_Y),No_Graph_String,true);
//      printf("\n after");
   }
	else	
	{
		drawgraph(pDC);
		DrawTickMarks(pDC);
		DrawHLabel(pDC);
		if (GraphData.graph_type<(PMC_GRAPH-1))//(graph_type != CScreenObject::VGA_HORNSCANGRAPH)//No vertical lable in case of HornScan Graph
      {
//         printf("\n DrawVLabel");
         DrawVLabel(pDC);
      }
	}
//   printf("\n draw complete");
}


void CVgaDrawGraph::drawgraph(CDC *pDC)
/***************************************************************************/
/*Description:-                                                            */
/* Plot the Particular Graph.		                                       */
/***************************************************************************/
{

	CPen pen_graph;
	CPen *oldpen;
	pen_graph.CreatePen( NULL , 1,CChildView::Color_Array[GraphData.GraphColour]);
	if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{
		int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
		if(nHorz>300)
		{
			pen_graph.DeleteObject();
			pen_graph.CreatePen( NULL , 2,CChildView::Color_Array[GraphData.GraphColour]);
		}
	}
	oldpen=pDC->SelectObject(&pen_graph);
	short *ptr =GraphData.graphdata;
	CPoint point1,point2;
	int tempVal =(GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-1);
	if ((GraphData.graph_type == (PMC_GRAPH-1)/*CScreenObject::VGA_HORNSCANGRAPH*/)&&(pDC->GetDeviceCaps(TECHNOLOGY)!=DT_RASPRINTER))
		tempVal =(GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-HEIGHT_LOWER_HSGRAPH);
     if ((GraphData.graph_type == (PMC_GRAPH-1)/*CScreenObject::VGA_HORNSCANGRAPH*/)&&(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER))
		tempVal =(GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-HEIGHT_LOWER_HSGRAPH*2);

	if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{	
		int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
	
		int Y1=0;
		if (GraphData.graph_type == (PMC_GRAPH-1)/*CScreenObject::VGA_HORNSCANGRAPH*/)
		{
			if(*ptr > MAX_HS_YCORD) 
				*ptr = MAX_HS_YCORD;
			Y1= (tempVal- (int) ((*ptr)*4));//*GRAPH_PRESCALE
		}
		else
		{
			if(*ptr > MAX_VIEWGRAPH_YCORD) 
				*ptr = MAX_VIEWGRAPH_YCORD;
			Y1= (tempVal- (int) ((*ptr)*2*GRAPH_PRESCALE));
		}

		point1=CPoint(GraphData.GRAPH_START_X,(Y1));
		point1=CalibPoint(point1, nHorz,nVert);
		pDC->MoveTo(point1);
		for(int a=1;a<GraphData.DataLength;a++)
		{
			if((*(ptr +a)) < 0)
				*(ptr+a) = 0;
	

			if (GraphData.graph_type == (PMC_GRAPH-1)/*CScreenObject::VGA_HORNSCANGRAPH*/)
			{
				if(*(ptr+a) > MAX_HS_YCORD) 
					*(ptr+a) = MAX_HS_YCORD;
				Y1= (tempVal- (int) ((*(ptr+a))*4));//*GRAPH_PRESCALE
			}
			else
			{
				if(*(ptr+a) > MAX_VIEWGRAPH_YCORD) 
					*(ptr+a) = MAX_VIEWGRAPH_YCORD;
				Y1= (tempVal- (int) ((*(ptr+a))*2*GRAPH_PRESCALE));
			}
		
			point2=CPoint((GraphData.GRAPH_START_X+(a*2)),(Y1));
			point2=CalibPoint(point2, nHorz,nVert);
			pDC->LineTo(point2);
			pDC->MoveTo(point2);
		}
		if(HSCompareGraph==true)
		{
			int a1 =(GraphData.DataLength-1)*2;

			if((GraphData.GraphColour == Blue)&&(GraphData.graph_type == (PMC_GRAPH-1)/*CScreenObject::VGA_HORNSCANGRAPH*/))
				CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,GraphData.GraphColour,CRect(GraphData.GRAPH_START_X+a1+4,
											Y1,
											GraphData.GRAPH_START_X+a1+4,
											Y1),"A",false,Lang_Index);
			if( (GraphData.GraphColour ==Red)&&(GraphData.graph_type == (PMC_GRAPH-1)/*CScreenObject::VGA_HORNSCANGRAPH*/))
				CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,GraphData.GraphColour,CRect(GraphData.GRAPH_START_X+a1+30,
											Y1,
											GraphData.GRAPH_START_X+a1+30,
											Y1),"B",false,Lang_Index);
			if((GraphData.GraphColour == Green)&&(GraphData.graph_type == (PMC_GRAPH-1)/*CScreenObject::VGA_HORNSCANGRAPH*/))
				CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,GraphData.GraphColour,CRect(GraphData.GRAPH_START_X+a1+50,
											Y1,
											GraphData.GRAPH_START_X+a1+50,
											Y1),"C",false,Lang_Index);
		}
	}
	else
	{
		int Y1 =0;
		if (GraphData.graph_type == (PMC_GRAPH-1))//CScreenObject::VGA_HORNSCANGRAPH)
		{
			if(*ptr > MAX_HS_YCORD) 
				*ptr = MAX_HS_YCORD;
			Y1= (tempVal- (int) ((*ptr)*2));//*GRAPH_PRESCALE
		}
		else
		{
			if(*ptr > MAX_VIEWGRAPH_YCORD) 
				*ptr = MAX_VIEWGRAPH_YCORD;
			Y1= (tempVal- (int) ((*ptr)*GRAPH_PRESCALE));
		}


		point1=CPoint(GraphData.GRAPH_START_X,(Y1));

		pDC->MoveTo(point1);
		for(int a=1;a<GraphData.DataLength;a++)
		{
			if(*(ptr +a) < 0)
				*(ptr+a) = 0;
	
		if (GraphData.graph_type == (PMC_GRAPH
         -1)) //CScreenObject::VGA_HORNSCANGRAPH)
		{
			if(*(ptr+a) > MAX_HS_YCORD) 
				*(ptr+a) = MAX_HS_YCORD;
			Y1= (tempVal- (int) ((*(ptr+a))*2));//*GRAPH_PRESCALE
		}
		else
		{
			if(*(ptr+a) > MAX_VIEWGRAPH_YCORD) 
				*(ptr+a) = MAX_VIEWGRAPH_YCORD;
			Y1= (tempVal- (int) ((*(ptr+a))*GRAPH_PRESCALE));
		}


			point2=CPoint((GraphData.GRAPH_START_X+a),(Y1));
		
			pDC->LineTo(point2);
			pDC->MoveTo(point2);
		}
		if(HSCompareGraph==true)
		{
			int a1 =GraphData.DataLength-1;

			if((GraphData.GraphColour == Blue) && (GraphData.graph_type ==PMC_GRAPH-1)/*(GraphData.graph_type == CScreenObject::VGA_HORNSCANGRAPH)*/)
				CVgaMenuItem::DrawText(pDC,SmallFont,GraphData.GraphColour,CRect(GraphData.GRAPH_START_X+a1+2,
											Y1,
											GraphData.GRAPH_START_X+a1+2,
											Y1),"A",false);
			if( (GraphData.GraphColour ==Red) && (GraphData.graph_type ==PMC_GRAPH-1)/*(GraphData.graph_type == CScreenObject::VGA_HORNSCANGRAPH)*/)
				CVgaMenuItem::DrawText(pDC,SmallFont,GraphData.GraphColour,CRect(GraphData.GRAPH_START_X+a1+15,
											Y1,
											GraphData.GRAPH_START_X+a1+15,
											Y1),"B",false);
			if((GraphData.GraphColour == Green) && (GraphData.graph_type ==PMC_GRAPH-1)/*(GraphData.graph_type == CScreenObject::VGA_HORNSCANGRAPH)*/)
				CVgaMenuItem::DrawText(pDC,SmallFont,GraphData.GraphColour,CRect(GraphData.GRAPH_START_X+a1+25,
											Y1,
											GraphData.GRAPH_START_X+a1+25,
											Y1),"C",false);
		}
		
		 if(CChildView::PMCScreen)
		 {
		
         CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(GraphData.GRAPH_END_X+5,GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-120,
						GraphData.GRAPH_END_X+5,GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-120),
						CChildView::thisPtr->Str_PMCGraphs/*[CChildView::Language_Index]*/,false);
			CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(GraphData.GRAPH_END_X+5,GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-80,
						GraphData.GRAPH_END_X+5,GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-80),
						CChildView::thisPtr->StrCurrent/*[CChildView::Language_Index]*/,false);
			if(GraphData.graph_type == PMC_GRAPH)//(GraphData.graph_type==CScreenObject::VGA_AVERAGEPOWERGRAPH)
			{
				CVgaMenuItem::DrawText(pDC,SmallFont,Red,CRect(GraphData.GRAPH_END_X+5,GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-100,
							GraphData.GRAPH_END_X+5,GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-100),
							CChildView::thisPtr->Str_PwrAvg/*[CChildView::Language_Index]*/,false);
			
				CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(GraphData.GRAPH_END_X+5,GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-60,
							GraphData.GRAPH_END_X+5,GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-60),
							CChildView::thisPtr->Str_PMCWeld/*[CChildView::Language_Index]*/,false);
				char buf[5];

            sprintf(buf," %d",PMCCycleCount);
				CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(GraphData.GRAPH_END_X+5,GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-40,
							GraphData.GRAPH_END_X+5,GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-40),
							CChildView::thisPtr->Str_PMCCycles/*[CChildView::Language_Index]*/+buf,false);
			}
		 }
		pDC->SelectStockObject(BLACK_PEN);
	
	}
	pDC->SelectObject(oldpen);
	pen_graph.DeleteObject( );
}



void CVgaDrawGraph::DrawGraphBoundary( CDC *pDC)
/***************************************************************************/
/*Description:-                                                            */
/* Draws Graph Boundary	with Y Axis and X Axis graduation				   */
/***************************************************************************/
{// printf("inside DrawGraphBoundary \n");
	Lang_Index=CChildView::Language_Index;
	//graph bounding rect
	GraphBoundary=true;
	CPen pen_bounding;
	CPen *oldpen;
	pen_bounding.CreatePen( NULL , 2, COLORBLACK);
	if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{
		int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
		if(nHorz>300)
		{
			pen_bounding.DeleteObject();
			pen_bounding.CreatePen( NULL , 4, COLORBLACK);
		}
	}

 
	oldpen=pDC->SelectObject(&pen_bounding);

	CPoint p1(GraphData.GRAPH_START_X-1,GraphData.GRAPH_START_Y-1);
	CPoint p2(GraphData.GRAPH_END_X+1,GraphData.GRAPH_START_Y-1);
	CPoint p3(GraphData.GRAPH_END_X+1,GraphData.GRAPH_END_Y+1);
	CPoint p4(GraphData.GRAPH_START_X-1,GraphData.GRAPH_END_Y+1);

	if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{
		int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
		p1=CalibPoint(p1, nHorz,nVert);
		p2=CalibPoint(p2, nHorz,nVert);
		p3=CalibPoint(p3, nHorz,nVert);
		p4=CalibPoint(p4, nHorz,nVert);
	}
	pDC->MoveTo(p1);
	pDC->LineTo(p2);
	pDC->LineTo(p3);
	pDC->LineTo(p4);
	pDC->LineTo(p1);

	 /*Draw Y Axis graduation*/
	int Index;
	if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{	
	
		int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
	
		if ((GraphData.graph_type == (PMC_GRAPH-1)/*CScreenObject::VGA_HORNSCANGRAPH*/)/*||(GraphData.graph_type ==(GraphData.graph_type >MaxGraphType)CScreenObject::VGA_NOHSGRAPH)*/)
		{
				for (Index = 0; Index <= 16; Index++ ) 
				{
				int Y1 = GraphData.GRAPH_START_Y + (GraphData.GRAPH_HEIGHT-HEIGHT_LOWER_HSGRAPH*2) - (int)(Index * 16*2);
				CPoint p1((GraphData.GRAPH_START_X - 6),(Y1-4));
				CPoint p2((GraphData.GRAPH_START_X + 6),(Y1-4));
				p1=CalibPoint(p1, nHorz,nVert);
				p2=CalibPoint(p2, nHorz,nVert);
      	//		pDC->MoveTo(p1);
			//	pDC->LineTo(p2);
				}
				
				if((HSCompareGraph) && (GraphData.graph_type == (PMC_GRAPH-1)/*CScreenObject::VGA_HORNSCANGRAPH*/))
				{
					/*CString HSScanStr[][9]={
						{"Current","Aktuell","Corrnte","Corrent","Actuel.",L"\x7535\x6d41\x0",L"\x96fb\x6d41\x0",
											L"\xff76\xff9a\xff84\x0",L"\xc804\xb958\x0"},
						{"Scan A","Scan A","Scan A","Scan A","Scan A",L"\x626b\x63cf\x7ed3\x679c\x0041\x0",L"\x626b\x63cf\x7ed3\x679c\x0041\x0",
											L"\xff7d\xff77\xff6c\xff9d\x0041\x0",L"\x0053\x0063\x0061\x006e\x0020\x0041\x0" },
						{"Scan B","Scan B","Scan B","Scan B","Scan B",L"\x626b\x63cf\x7ed3\x679c\x0042\x0",L"\x6383\x63cf\x7ed3\x679c\x0042\x0",
											L"\xff7d\xff77\xff6c\xff9d\x0042\x0",L"\x0053\x0063\x0061\x006e\x0020\x0042\x0"},
						{"Scan C","Scan C ","Scan C","Scan C","Scan C",L"\x626b\x63cf\x7ed3\x679c\x0043\x0",L"\x6383\x63cf\x7ed3\x679c\x0043\x0",
											L"\xff7d\xff77\xff6c\xff9d\x0043\x0",L"\x0053\x0063\x0061\x006e\x0020\x0043\x0"}
										};*/
					CString HSScanStr[4];
					for(int i=0;i<4;i++)
					{
						HSScanStr[i]=tempScanGraphDataList.GetNext(ScanGraphsDataTemp_pos);
					}
					int Y =GraphData.GRAPH_END_Y+100;
					int X = GraphData.GRAPH_START_X;
					for(i=0;i<4;i++)
					{
						CPoint LabelPoint1(X,Y);
						CPoint LabelPoint2(X+20,Y+20);
						LabelPoint1=CalibPoint(LabelPoint1,nHorz,nVert);
						LabelPoint2=CalibPoint(LabelPoint2,nHorz,nVert);
						CRect LabelRect(LabelPoint1,LabelPoint2);
						pDC->FillSolidRect(LabelRect,CChildView::Color_Array[i+1]);
						CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,Black,CRect(X+30,
											Y+10,
											X+30,
											Y+10),HSScanStr[i]/*[Lang_Index]*/,false,Lang_Index);
					X +=200;
						
					}


				}

		}
		else
		{/* y axis graduation*/
				for (Index = 1; Index <= 19; Index++ ) 
				{
					int Y1 = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT - ((int)(Index * 13.6))*2;
					if(Index==19)
						Y1=Y1+2;
					CPoint p1((GraphData.GRAPH_START_X - 6),(Y1));
					CPoint p2((GraphData.GRAPH_START_X + 6),(Y1));
					p1=CalibPoint(p1, nHorz,nVert);
					p2=CalibPoint(p2, nHorz,nVert);
      				pDC->MoveTo(p1);
					pDC->LineTo(p2);

				}
		}
		/*Draw X Axis graduation*/
		for (Index = 1; Index < INCLABEL; Index++ ) 
		{
			int X1 = GraphData.GRAPH_START_X + ((Index * GraphData.GraphWidth)/INCLABEL);
			CPoint p1(X1,(GraphData.GRAPH_HEIGHT+(GraphData.GRAPH_START_Y  - 6)));
			CPoint p2(X1,(GraphData.GRAPH_HEIGHT+(GraphData.GRAPH_START_Y  + 6)));
			p1=CalibPoint(p1, nHorz,nVert);
			p2=CalibPoint(p2, nHorz,nVert);
      		pDC->MoveTo(p1);
			pDC->LineTo(p2);

		}
		//pDC->SelectObject(&oldpen);
	}
	else
	{
		if ((GraphData.graph_type >PMC_GRAPH)||(GraphData.graph_type == (PMC_GRAPH-1)))//== CScreenObject::VGA_HORNSCANGRAPH)||(GraphData.graph_type ==CScreenObject::VGA_NOHSGRAPH))
		{
			for (Index = 0; Index <= 16; Index++ ) 
			{
				int Y1 = GraphData.GRAPH_START_Y + (GraphData.GRAPH_HEIGHT-HEIGHT_LOWER_HSGRAPH) - (int)(Index * 16);//(-72)
      	//		pDC->MoveTo(((GraphData.GRAPH_START_X - 3)),(Y1-2));
			//	pDC->LineTo(((GraphData.GRAPH_START_X + 3)),(Y1-2));
			}
		}
		else
		{
			for (Index = 1; Index <= 19; Index++ ) 
			{
				int Y1 = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT - (int)(Index * 13.6);
				if(Index==19)
					Y1=Y1+  1;
      			pDC->MoveTo(((GraphData.GRAPH_START_X - 3)),(Y1));
				pDC->LineTo(((GraphData.GRAPH_START_X + 3)),(Y1));
			}
		}
		/*Draw X Axis graduation*/
		for (Index = 1; Index < INCLABEL; Index++ ) 
		{
			 int X1 = GraphData.GRAPH_START_X + ((Index * GRAPH_WIDTH)/INCLABEL);
			 pDC->MoveTo(X1,(GraphData.GRAPH_HEIGHT+(GraphData.GRAPH_START_Y  - 3)));
			 pDC->LineTo(X1,(GraphData.GRAPH_HEIGHT+(GraphData.GRAPH_START_Y  + 3))) ;
		}
		//pDC->SelectObject(&oldpen);
	
		}
		pDC->SelectObject(oldpen);
		pen_bounding.DeleteObject( );

//	printf("Retruning \n");

}

void CVgaDrawGraph::DrawTickMarks( CDC *pDC)
/****************************************************************************/
/*Description:-                                                             */
/* Draws tick marks at the graph.											*/
/****************************************************************************/
{ //printf("Inside DrawTickMarks \n");
		if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{
		int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		int nVert = pDC->GetDeviceCaps(LOGPIXELSY);

		if (GraphData.graph_type ==( PMC_GRAPH-1))
		{
			CPen *oldpen;
			CPen pen_bounding;
			if(nHorz>300)
				pen_bounding.CreatePen( NULL , 2, COLORBLACK);
			else
				pen_bounding.CreatePen( NULL , 1, COLORBLACK);
			oldpen=pDC->SelectObject(&pen_bounding);
			int LineProp_Y1 = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT -404;
			int LineProp_X1 = GraphData.GRAPH_START_X;
			int LineProp_X2 = LineProp_X1+ 16;
			while(LineProp_X2 <= (GraphData.GRAPH_START_X + GraphData.GraphWidth))
			{	
				CPoint p1(LineProp_X1,LineProp_Y1);
				CPoint p2(LineProp_X2,LineProp_Y1);
				p1=CalibPoint(p1, nHorz,nVert);
				p2=CalibPoint(p2, nHorz,nVert);
      			pDC->MoveTo(p1);
				pDC->LineTo(p2);
				LineProp_X1 = LineProp_X2 + (nHorz/18);
				LineProp_X2 = LineProp_X1 + (nHorz/10); 
		
			}
			pDC->SelectObject(oldpen);
			pen_bounding.DeleteObject( );
		}
		else
		{
  
			int LabelCount ;
			int Y_Coordinate;
			int X_Coordinate;
			pDC->SetTextColor(COLORRED);
			CPen *oldpen;
			CPen *oldpen1;
			CPen pen_bounding1( NULL , 2,COLORBLACK);
			CPen pen_bounding( NULL , 1, COLORBLACK);
			oldpen1=pDC->SelectObject(&pen_bounding1);
			for(LabelCount=0;LabelCount<GraphData.no_of_ticks;LabelCount++)
			{
				X_Coordinate=GraphData.GRAPH_START_X + ((GraphData.tick[LabelCount].tick_location)*2);
				
				
				int X1 = X_Coordinate;//Align tick in middle
				int X2 =X_Coordinate;//of the Particular time
				int Y1 = (GraphData.GRAPH_START_Y);
				int Y2 = (GraphData.GRAPH_START_Y+ 12);

				CPoint p1(X1,Y1);
				CPoint p2(X2,Y2);
				p1=CalibPoint(p1, nHorz,nVert);
				p2=CalibPoint(p2, nHorz,nVert);
      			pDC->MoveTo(p1);
				pDC->LineTo(p2);

				Y1 =  (GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT - 12);
				Y2 =  (GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT);

				p1=CPoint(X1,Y1);
				p2=CPoint(X2,Y2);
				p1=CalibPoint(p1, nHorz,nVert);
				p2=CalibPoint(p2, nHorz,nVert);
      			pDC->MoveTo(p1);
				pDC->LineTo(p2);

				if(LabelCount == TICKTRIG)
				{
					Y1 =  (GraphData.GRAPH_START_Y + 20);
					Y2 =  (GraphData.GRAPH_START_Y + 24);
				
					oldpen=pDC->SelectObject(&pen_bounding);
					while(Y2 <= (GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT))
					{	
						CPoint p1(X1,Y1);
						CPoint p2(X2,Y2);
						p1=CalibPoint(p1, nHorz,nVert);
						p2=CalibPoint(p2, nHorz,nVert);
      					pDC->MoveTo(p1);
						pDC->LineTo(p2);
						 Y1 = Y2 + 12*2;
						Y2 = Y1 + 4*2;  
					}
				
					
				}
				if(LabelCount % 2)
					 Y_Coordinate = ((GraphData.GRAPH_START_Y+ 100));
				else
					Y_Coordinate= ((GraphData.GRAPH_START_Y+ 60));
					CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,Red,CRect(X_Coordinate,Y_Coordinate,X_Coordinate,
											Y_Coordinate),GraphData.tick[LabelCount].tick_char,false,Lang_Index);
			
					
			}
			pDC->SelectObject(oldpen);
			pDC->SelectObject(oldpen1);
			pen_bounding.DeleteObject();
			pen_bounding1.DeleteObject();
		}

	}
	else
	{

		if ((GraphData.graph_type ==( PMC_GRAPH-1)))
		{
			int LineProp_Y1 = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT -202;
			int LineProp_X1 = GraphData.GRAPH_START_X;
			int LineProp_X2 = LineProp_X1+ 8;
			/*if((HSCompareGraph))
			CScreenObject::DrawText(pDC,SmallFont,Black,CRect(LineProp_X1-20,LineProp_Y1,LineProp_X1-20,LineProp_Y1),"Fr",false);*/
			CPen *oldpen2;
			CPen pen_bounding2;
			pen_bounding2.CreatePen( NULL , 2, COLORBLACK);
			oldpen2=pDC->SelectObject(&pen_bounding2);
			while(LineProp_X2 <= (GraphData.GRAPH_START_X + GRAPH_WIDTH))
			{
				pDC->MoveTo(LineProp_X1,LineProp_Y1);
				pDC->LineTo(LineProp_X2,LineProp_Y1);
				 LineProp_X1 = LineProp_X2 + 4;
				LineProp_X2 = LineProp_X1 + 8;  
			}
			pDC->SelectObject(oldpen2);
			pen_bounding2.DeleteObject();
		}
		else
		{
  			int LabelCount ;
			int Y_Coordinate;
			int X_Coordinate;
			pDC->SetTextColor(CChildView::Color_Array[Red]);
			CPen *oldpen;
			CPen *oldpen1;
			CPen pen_bounding1( NULL , 2,CChildView::Color_Array[Black]);
			CPen pen_bounding( NULL , 1, CChildView::Color_Array[Black]);
			oldpen1=pDC->SelectObject(&pen_bounding1);
			for(LabelCount=0;LabelCount<GraphData.no_of_ticks;LabelCount++)
			{
				X_Coordinate=GraphData.GRAPH_START_X + GraphData.tick[LabelCount].tick_location;
				
				
				int X1 = X_Coordinate;//Align tick in middle
				int X2 =X_Coordinate;//of the Particular time
				int Y1 = (GraphData.GRAPH_START_Y);
				int Y2 = (GraphData.GRAPH_START_Y+ 6);
				pDC->MoveTo(X1,Y1);
				pDC->LineTo(X2,Y2);
				Y1 =  (GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT - 6);
				Y2 =  (GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT);
				pDC->MoveTo(X1,Y1);
				pDC->LineTo(X2,Y2);
				if(LabelCount == TICKTRIG)
				{
					Y1 =  (GraphData.GRAPH_START_Y + 10);
					Y2 =  (GraphData.GRAPH_START_Y + 12);
					
					oldpen=pDC->SelectObject(&pen_bounding);
					while(Y2 <= (GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT))
					{
						 pDC->MoveTo(X1,Y1);
						 pDC->LineTo(X2,Y2);
						 Y1 = Y2 + 6*2;
						 Y2 = Y1 + 4*2;  
					}
				
				}
				if(LabelCount % 2)
					 Y_Coordinate = ((GraphData.GRAPH_START_Y+ 55));
				else
					Y_Coordinate= ((GraphData.GRAPH_START_Y+ 35));
				pDC->ExtTextOut(X_Coordinate,Y_Coordinate,ETO_OPAQUE,NULL,
											GraphData.tick[LabelCount].tick_char,NULL);
				
			}
			pDC->SelectObject(oldpen);
			pDC->SelectObject(oldpen1);
			pen_bounding.DeleteObject();
			pen_bounding1.DeleteObject();

		}
	}
//	printf("Returning \n");
}


void CVgaDrawGraph::DrawHLabel(CDC *pDC)
/***************************************************************************/
/*Description:-                                                            */
/* Draw Horizontal Graph Labels                                            */
/***************************************************************************/
	
{	
   if (GraphData.graph_type  == (PMC_GRAPH-1))//CScreenObject::VGA_HORNSCANGRAPH))//&&(!HSCompareGraph))
	{
		
		int StrProp_X = GraphData.GRAPH_START_X ;
		int StrProp_Y = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT +9;
		
		if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
		{
			if(HSCompareGraph)
         {
            /*Draw the Horizontal Label 1*/
			CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,Black,CRect(StrProp_X-18,StrProp_Y+5,StrProp_X-18,
												StrProp_Y+5),GraphData.HData[0]+CString("(Hz)"),false,Lang_Index);
			/*Draw the Horizontal Label 2*/
			StrProp_X = GraphData.GRAPH_START_X + ((5 * GraphData.GraphWidth)/INCLABEL)- 18;
			CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,Black,CRect(StrProp_X,StrProp_Y+5,StrProp_X,
												StrProp_Y+5),GraphData.HData[1]+CString("(Hz)"),false,Lang_Index);
			/*Draw the Horizontal Label 3*/
			StrProp_X = GraphData.GRAPH_START_X + ((10 * GraphData.GraphWidth)/INCLABEL)- 20;
				CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,Black,CRect(StrProp_X,StrProp_Y+5,StrProp_X,
												StrProp_Y+5),GraphData.HData[2]+CString("(Hz)"),false,Lang_Index);
         }
         else
         {
         /*Draw the Horizontal Label 1*/
			CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,Black,CRect(StrProp_X-18,StrProp_Y+5,StrProp_X-18,
												StrProp_Y+5),GraphData.HData[0],false,Lang_Index);
			/*Draw the Horizontal Label 2*/
			StrProp_X = GraphData.GRAPH_START_X + ((5 * GraphData.GraphWidth)/INCLABEL)- 18;
			CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,Black,CRect(StrProp_X,StrProp_Y+5,StrProp_X,
												StrProp_Y+5),GraphData.HData[1],false,Lang_Index);
			/*Draw the Horizontal Label 3*/
			StrProp_X = GraphData.GRAPH_START_X + ((10 * GraphData.GraphWidth)/INCLABEL)- 20;
				CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,Black,CRect(StrProp_X,StrProp_Y+5,StrProp_X,
												StrProp_Y+5),GraphData.HData[2],false,Lang_Index);
         }
		}
		else
		{
         if(HSCompareGraph){
            
			   /*Draw the Horizontal Label 1*/
			   CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(StrProp_X-20,StrProp_Y,StrProp_X-20,
												   StrProp_Y),GraphData.HData[0]+CString("(Hz)"),false);
			   /*Draw the Horizontal Label 2*/
			   StrProp_X = GraphData.GRAPH_START_X + ((5 * GraphData.GraphWidth)/INCLABEL)- 20;
			   CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(StrProp_X,StrProp_Y,StrProp_X,
												   StrProp_Y),GraphData.HData[1] +CString("(Hz)"),false);
            
            /*Draw the Horizontal Label 3*/
			   StrProp_X = GraphData.GRAPH_START_X + ((10 * GraphData.GraphWidth)/INCLABEL)- 20;
				   CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(StrProp_X,StrProp_Y,StrProp_X,
												   StrProp_Y),GraphData.HData[2]+CString("(Hz)"),false);
         }
         else{
            /*Draw the Horizontal Label 1*/
            CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(StrProp_X-20,StrProp_Y,StrProp_X-20,
												   StrProp_Y),GraphData.HData[0],false);
			   /*Draw the Horizontal Label 2*/
			   StrProp_X = GraphData.GRAPH_START_X + ((5 * GraphData.GraphWidth)/INCLABEL)- 20;
            CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(StrProp_X,StrProp_Y,StrProp_X,
												   StrProp_Y),GraphData.HData[1],false);

            CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(StrProp_X-17,StrProp_Y+15,StrProp_X-17,
												   StrProp_Y+15),CChildView::thisPtr->Str_Frequency/*Str_Frequency[Lang_Index]+="(Hz)"*/,false);
			   
            /*Draw the Horizontal Label 3*/
			   StrProp_X = GraphData.GRAPH_START_X + ((10 * GraphData.GraphWidth)/INCLABEL)- 20;
            CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(StrProp_X,StrProp_Y,StrProp_X,
												   StrProp_Y),GraphData.HData[2],false);
         }
         
		}
      
      
		CString DigitalTuneStr =CChildView::thisPtr->Str_DigitalTuneSett/*Str_DigitalTuneSett[Lang_Index]Str_PMCWeld */+ DigitalTuneSetting;

		if((!HSCompareGraph)&&(pDC->GetDeviceCaps(TECHNOLOGY)!=DT_RASPRINTER))
		{
		StrProp_X = GraphData.GRAPH_START_X + 25;
		StrProp_Y = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT -60;
		for(int i =0;i<6;i++)
		{
			//pDC->ExtTextOut(StrProp_X,StrProp_Y,ETO_OPAQUE,NULL,FreqString[i],NULL);
         CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(StrProp_X,StrProp_Y,StrProp_X,
												   StrProp_Y),FreqString[i],false);
			StrProp_X +=125;
			if(i==2)
			{
				StrProp_X = GraphData.GRAPH_START_X + 25;
				StrProp_Y = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT -30;
			}
		}
		//pDC->ExtTextOut(GraphData.GRAPH_START_X+20,GraphData.GRAPH_START_Y+10,ETO_OPAQUE,NULL,DigitalTuneStr,NULL);
      CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(GraphData.GRAPH_START_X+20,GraphData.GRAPH_START_Y+10,GraphData.GRAPH_START_X+20,
												   GraphData.GRAPH_START_Y+10),DigitalTuneStr,false);
		}

		if((pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)&&(HSCompareGraph))
		{
	
	     CString Str_Resonance=tempScanGraphDataList.GetNext(ScanGraphsDataTemp_pos);
		 CString Str_Frequency=tempScanGraphDataList.GetNext(ScanGraphsDataTemp_pos);
		 

		CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,RESONANCEHSCEPRINTRECT,  Str_Resonance/*[Lang_Index]*/,false,Lang_Index);
		CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,FREQHSCPRINTRECT,  Str_Frequency/*[Lang_Index]*/,false,Lang_Index);
		}

		if((pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)&&(!HSCompareGraph))
		{
		  HornScanTemp_pos = tempHornScanList.GetHeadPosition();
	      tempHornScanList.GetNext(HornScanTemp_pos);
          CString ResonanceFreq= tempHornScanList.GetNext(HornScanTemp_pos);
          CString StrFreqSeries= tempHornScanList.GetNext(HornScanTemp_pos);
          CString StrFreqParallel= tempHornScanList.GetNext(HornScanTemp_pos);
          CString Date_Str = tempHornScanList.GetNext(HornScanTemp_pos);
          CString Time_Str = tempHornScanList.GetNext(HornScanTemp_pos);
          CString HornScan_Str = tempHornScanList.GetNext(HornScanTemp_pos);
          CString Str_Frequency = tempHornScanList.GetNext(HornScanTemp_pos);
          CString DigitalTuneStr = tempHornScanList.GetNext(HornScanTemp_pos);
			

			CString Date=Date_Str+DateString;
			CString Time=Time_Str+TimeString;
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,HORNSCANPRINTRECT, HornScan_Str,false,Lang_Index);
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,DATEPRINTRECT,  Date,false,Lang_Index);
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TIMEPRINTRECT, Time,false,Lang_Index);
			//CScreenObject::DrawPrinterText(pDC, PrintSmallFont, Black,RESONANCEPRINTRECT,  Str_Resonance[Lang_Index],false,Lang_Index);
			//CScreenObject::DrawPrinterText(pDC, PrintSmallFont, Black,FREQPRINTRECT,  Str_Frequency[Lang_Index],false,Lang_Index);
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,FREQHZRECT, Str_Frequency+="(Hz)",false,Lang_Index);
         CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,DIGITUNEPRINTRECT, DigitalTuneStr + DigitalTuneSetting,false,Lang_Index);
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,RESONANCEFREQPRINTRECT,ResonanceFreq,false,Lang_Index);

			int StartXResonance=STARTXRESONANCE;
			int StartYResonance=STARTYRESONANCE;
			for(int Strings =0;Strings<TotalStrings;Strings++)
			{
				CString STR;
				if(FreqString[Strings].Find(_T(" Hz(S)"),0)==(-1))
				{	
					int StrLen=FreqString[Strings].GetLength();
					STR= FreqString[Strings].Left(StrLen-5);
					STR = StrFreqParallel+ STR;
				}
				else
				{
					int StrLen=FreqString[Strings].GetLength();
					STR= FreqString[Strings].Left(StrLen-5);
					STR = StrFreqSeries+ STR;
				}
					CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CRect(StartXResonance,StartYResonance ,StartXResonance,StartYResonance ),STR,false,Lang_Index);
					StartYResonance+=ONELINEGAP;
			}
		}
	}
	else
	{
		int Y_Coordinate = ((GraphData.GRAPH_HEIGHT+GraphData.GRAPH_START_Y +15)) ;
		pDC->SetTextColor(RGB(0,0,0));
		int X_Coordinate = ((GraphData.GRAPH_START_X-15 ));
		for (int Index = 0; Index <=INCLABEL; Index++ ) 
		{
			
		if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
		{
			if(Index%2 ==0)
			CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,Black,CRect(X_Coordinate,Y_Coordinate,
											X_Coordinate,Y_Coordinate),GraphData.HData[Index],false,Lang_Index);
		X_Coordinate += (GraphData.GraphWidth/INCLABEL);
		}
		else 
		{
			if(Index%2 ==0)
			CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(X_Coordinate,Y_Coordinate,
												X_Coordinate,Y_Coordinate),GraphData.HData[Index],false);
			X_Coordinate += (GRAPH_WIDTH/INCLABEL);
		}
		}
	}
}

void CVgaDrawGraph::DrawVLabel(CDC *pDC)
/***************************************************************************/
/*Description:-                                                            */
/* Draw Vertical Graph Labels                                              */
/***************************************************************************/
{	/* printf("DrawVLabel\n\n");
    printf("\nGraphNum = %d",GraphNum);
	::Sleep(500);*/
	int X_Coordinate,Y_Coordinate;
	if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{
		if((GraphData.GraphNum%2)==0)
			X_Coordinate = (GraphData.GRAPH_END_X+10);
		else 
			X_Coordinate = GraphData.GRAPH_START_X - 80;
		int  Start_Y = (int)(GraphData.GRAPH_END_Y - 8);
		
		for (int Index = 3; Index >= 0; Index--) 
		{
			Y_Coordinate = Start_Y - (int)((Index+1)* 67*2);
		
			CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,GraphData.GraphColour,CRect(X_Coordinate,	Y_Coordinate,
											X_Coordinate,Y_Coordinate),GraphData.VData[Index],false,Lang_Index);
 		}
	
		if((GraphData.GraphNum%2)==0)
		CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,GraphData.GraphColour,CRect(X_Coordinate+33,
							GraphData.GRAPH_START_Y-40,X_Coordinate+33,GraphData.GRAPH_START_Y-40),GraphData.GRAPHTITLE,true,Lang_Index);
		else
	
		CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,GraphData.GraphColour,CRect(X_Coordinate-30,GraphData.GRAPH_START_Y-40,
											X_Coordinate+20,GraphData.GRAPH_START_Y-40),GraphData.GRAPHTITLE,false,Lang_Index);
	
		CVgaMenuItem::DrawPrinterText(pDC,PrintSmallFont,Black,CRect(GraphData.GRAPH_END_X-400,GraphData.GRAPH_START_Y+50,
											GraphData.GRAPH_END_X-400,GraphData.GRAPH_START_Y+50),"                     ",false,Lang_Index);
	
	}
	else
	{
		if((GraphData.GraphNum%2)==0)
		{
			X_Coordinate = GraphData.GRAPH_END_X+ 5;
			if(!CChildView::PMCScreen)
				CChildView::GraphTwoRequestValue=GraphData.GraphRequestValue;

		}
		else 
		{
			X_Coordinate = GraphData.GRAPH_START_X - 55;
			if(!CChildView::PMCScreen)
				CChildView::GraphOneRequestValue=GraphData.GraphRequestValue;
		}

		int  Start_Y = (int)(GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT - YOFFSET);
	
		for (int Index = 3; Index >= 0; Index--) 
		{
			Y_Coordinate = Start_Y - (int)((Index+1)* 67);
			Y_Coordinate=(Y_Coordinate);
			CVgaMenuItem::DrawText(pDC,SmallFont,GraphData.GraphColour,CRect(X_Coordinate,Y_Coordinate-20,
											X_Coordinate+50,Y_Coordinate+20),GraphData.VData[Index],false);
		}
	
		CRect Rect;

		if(GraphData.graph_type==POWGRAPH)
		{
			CString str;
			for(int i=0;i<20;i++)GraphData.GRAPHTITLE[i]='\0';
			if(CChildView::PeakPowerMicrons)
			{
				str=CVgaMenuItem::LinearSearch(_T("2693"));
			}
			else
			{
				str=CVgaMenuItem::LinearSearch(_T("1863"));
			}
			_tcscpy(GraphData.GRAPHTITLE , str);
		}

		if(GraphData.graph_type==AMPLIGRAPH)
		{
			CString str;
			for(int i=0;i<20;i++)GraphData.GRAPHTITLE[i]='\0';
			if(CChildView::AmplitudeMicrons)
			{
				str=CVgaMenuItem::LinearSearch(_T("2694"));
			}
			else
			{
				str=CVgaMenuItem::LinearSearch(_T("1592"));
			}
			_tcscpy(GraphData.GRAPHTITLE , str);
		}

      CString TempText=GraphData.GRAPHTITLE;
      if(CChildView::thisPtr->StringDebugFlag)
         TempText = textID + _T(" ")+ GraphData.GRAPHTITLE;

		if((GraphData.GraphNum%2)==0)
		{
			Rect=CRect(X_Coordinate+25+XOFFSET,	GraphData.GRAPH_START_Y-12-YOFFSET,
					X_Coordinate+105+XOFFSET,GraphData.GRAPH_START_Y-12-YOFFSET);

			CVgaMenuItem::DrawText(pDC,SmallFont,GraphData.GraphColour,Rect,TempText,true);
	
		}
		else
		{
			Rect=CRect(X_Coordinate-20,GraphData.GRAPH_START_Y-12-YOFFSET,
						X_Coordinate-20+BUTTON_WIDTH_BACK_NEXT,GraphData.GRAPH_START_Y-12-YOFFSET);
			CVgaMenuItem::DrawText(pDC,SmallFont,GraphData.GraphColour,Rect,TempText,false);
		}
		if(!CChildView::PMCScreen)
		{
			CString TempCycleText=GraphData.CycleCount;
         if(CChildView::thisPtr->StringDebugFlag)
            TempCycleText = CycleCountID + _T(" ")+ GraphData.CycleCount;

         CVgaMenuItem::DrawRect(pDC,White,CRect(370,GraphData.GRAPH_START_Y+10-XOFFSET,
									370,GraphData.GRAPH_START_Y+30-XOFFSET));
			CVgaMenuItem::DrawText(pDC,SmallFont,Black,CRect(340,GraphData.GRAPH_START_Y+10-XOFFSET,
											340+BUTTON_WIDTH_BACK_NEXT,GraphData.GRAPH_START_Y+30-XOFFSET),
											TempCycleText,false);
		}
	}
}

void CVgaDrawGraph::Store_VData_HData(unsigned char *&data, int &length)
/***************************************************************************/
/*Description:-                                                            */
/* Store Horizontal and Vertical Graph Labels                              */
/***************************************************************************/
{
	CTable::HighLightString= -1;
	int TempFreqString[6] ;
	int MaxNumberOfFreq=6 ;				   						// the limit of frequencuencies is 6.
	if (GraphData.graph_type == (PMC_GRAPH-1))//CScreenObject::VGA_HORNSCANGRAPH)
	{
		for(int  x=0;x<3;x++)
			CVgaMenuItem::GetCharString(data,length,GraphData.HData[x]);


			/********************************/
		/*Storing Frequencies for Horn scan graph.*/
		for(int Strings =0;Strings<MaxNumberOfFreq;Strings++)   // HSanchez: this fix clean the vector to do not show unespected values.
		{
			FreqString[Strings]="";
		}
		
		TotalStrings = *data++;length--;
		for( Strings =0;Strings<TotalStrings;Strings++)
		{
			
			int TempFreq = 	CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
			TempFreqString[Strings]=TempFreq;
			char freq[10];
			FreqString[Strings] = _itoa(TempFreq,freq,10);
			int P_or_S = *data++;length--;
			if(P_or_S == 1)
				FreqString[Strings] += " Hz(S)";
			else
				FreqString[Strings] += " Hz(P)";
		}
		char Temp[10];
		int TempDigitalTuneSetting = CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
		for(Strings =0;Strings<TotalStrings;Strings++)
		{
			if(TempFreqString[Strings] == TempDigitalTuneSetting)
				CTable::HighLightString= Strings;
		}

		DigitalTuneSetting = _itoa(TempDigitalTuneSetting,Temp,10);
		DigitalTuneSetting +=" (Hz)";
	
	}
	else
	{
  	

		for(int q=0;q<4;q++)
			CVgaMenuItem::GetCharString(data,length,GraphData.VData[q]);

		for(int  z=0;z<11;z++)
			CVgaMenuItem::GetCharString(data,length,GraphData.HData[z]);

	}
	
}

void CVgaDrawGraph::StoreTickData(unsigned char *&data, int &length)
/***************************************************************************/
/*Description:-                                                            */
/* Store Tick Data								                           */
/***************************************************************************/
{
	GraphData.no_of_ticks=*data++;
 //  printf("\n GraphData.no_of_ticks=%d \n",GraphData.no_of_ticks);
	length--;
	for(int  x=0;x<GraphData.no_of_ticks;x++)
	{
		GraphData.tick[x].tick_char=*data++;length--;
		GraphData.tick[x].tick_location=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);

	}
	
}

bool CVgaDrawGraph::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}


void CVgaDrawGraph::SetGraphRequestValue(int Graph_Type)
/***************************************************************************/
/*Description:-                                                            */
/* Set graph request value acording to the Graph_Type.                     */
/***************************************************************************/
{
	
  	switch(Graph_Type)
	{
	case DISTINGRAPH:
      GraphData.GraphRequestValue=Distance_RequestValue;
	break;

   case DISTMMGRAPH:
      GraphData.GraphRequestValue=Distance_RequestValue;
	break;

	case POWGRAPH:
		GraphData.GraphRequestValue=Power_RequestValue;
	break;

	case VELINGRAPH:
      GraphData.GraphRequestValue=Velocity_RequestValue;
	break;

   case VELMMGRAPH:
      GraphData.GraphRequestValue=Velocity_RequestValue;
	break;

	case FORCELBGRAPH:
      GraphData.GraphRequestValue=Force_RequestValue;
   break;

   case FORCENGRAPH:
      GraphData.GraphRequestValue=Force_RequestValue;
   break;

	case AMPLIGRAPH:
			GraphData.GraphRequestValue=Amplitude_RequestValue;
	break;

	case FREQUGRAPH:
		GraphData.GraphRequestValue=Frequency_RequestValue;
	break;

	default:
		GraphData.GraphRequestValue =Power_RequestValue;
		break;
	
	}	
}

/********************************************************************************************/
/* This Function Sets The Graph Co-ordinate For Printing. After The Printing Is Over the    */
/* Function Returns The Orignal Graph Setting To The Graph Objects So That It Does Not      */
/* Make Any Effect On The Graph.															*/
/*																							*/
/********************************************************************************************/
void CVgaDrawGraph::Print(CDC *pDC,CPoint TopLeft,int GraphType,CChildView *view)
{ 	
	
	int TEMP_GRAPH_START_X,TEMP_GRAPH_START_Y,TEMP_GRAPH_END_X,TEMP_GRAPH_END_Y,
		TEMP_GRAPH_WIDTH,TEMP_GraphNum;

	TEMP_GRAPH_START_X = GraphData.GRAPH_START_X;
	TEMP_GRAPH_START_Y = GraphData.GRAPH_START_Y;
	TEMP_GRAPH_END_X = GraphData.GRAPH_END_X;
	TEMP_GRAPH_END_Y = GraphData.GRAPH_END_Y;
	TEMP_GRAPH_WIDTH = GraphData.GraphWidth;
	TEMP_GraphNum = GraphData.GraphNum;

	bool Manual =false;
	if(GraphType==PRINTLISTGRAPHID)
	{
		if((GraphData.graph_type == AMPLIGRAPH/*CScreenObject::VGA_AMPLITUDEGRAPH*/)&&GraphData.ExtraText)
			Manual =true;
		else if(((GraphData.graph_type ==FORCELBGRAPH/*CScreenObject::VGA_FORCEGRAPH*/)||(GraphData.graph_type ==FORCENGRAPH))&&GraphData.ExtraText)
			Manual =true;
	}
/*	GraphNum=2;
		else
	GraphNum=1;*/
	GraphData.GRAPH_START_X =	TopLeft.x;
	GraphData.GRAPH_START_Y = TopLeft.y-30;
	GraphData.GraphWidth=GRAPH_WIDTH*2;
	GraphData.GRAPH_HEIGHT *=2;
	GraphData.GRAPH_HEIGHT-=2;
	GraphData.GRAPH_END_X= GraphData.GRAPH_START_X + GraphData.GraphWidth;	
	GraphData.GRAPH_END_Y = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT;//HS_GRAPH_HEIGHT;
	if(GraphData.graph_type<(PMC_GRAPH-1)/*(GraphData.graph_type != CScreenObject::VGA_HORNSCANGRAPH)*/)//(GraphType==PRINTLISTGRAPHID)&& 
		PrintGraphData(pDC,Manual);
	
	if(!PrintGraphBoundary)
	{
	DrawGraphBoundary(pDC);
	DrawTickMarks(pDC);
	DrawHLabel(pDC);
	}
	else if(GraphData.graph_type<(PMC_GRAPH-1)/*GraphData.graph_type !=CScreenObject::VGA_HORNSCANGRAPH*/)
		YAxis2Graduation(pDC);

	drawgraph(pDC);
		
		
		if(GraphData.graph_type<(PMC_GRAPH-1)/*GraphData.graph_type != CScreenObject::VGA_HORNSCANGRAPH*/)//No vertical lable in case of HornScan Graph
			DrawVLabel(pDC);
	
	
if (GraphData.graph_type == (PMC_GRAPH-1)/*(GraphData.graph_type == CScreenObject::VGA_HORNSCANGRAPH)*/&&(!HSCompareGraph))
	PrintHSText(view,pDC);




	GraphData.GRAPH_START_X=TEMP_GRAPH_START_X;
	GraphData.GRAPH_START_Y=TEMP_GRAPH_START_Y;
	GraphData.GRAPH_END_X=TEMP_GRAPH_END_X;
	GraphData.GRAPH_END_Y=TEMP_GRAPH_END_Y;
	GraphData.GraphWidth=TEMP_GRAPH_WIDTH;
	GraphData.GRAPH_HEIGHT+=2;
	GraphData.GRAPH_HEIGHT /=2;
	GraphData.GraphNum=TEMP_GraphNum;

}


/************************************************************************************************/
/* This function takes care of the graph data that is printed with the graph. Following are the */
/* strings that are printed thru this function													*/
/* 1.All Tick mark strings and its values.														*/
/* 2.Date string.																				*/
/* 3. Time String.																				*/
/************************************************************************************************/
void CVgaDrawGraph::PrintGraphData(CDC *pDC,bool Manual)
{ // printf("Inside PrintGraph Data \n");
	AlreadyPrinted=true;
   CString line1[3],line2[3];
	
   for(int i=0;i<3;i++)
	{ 
      if(GraphsTemp_pos!=NULL)
		   line1[i]=tempGraphsList.GetNext(GraphsTemp_pos);
		else
			line1[i]=tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);
   }
   for( i=0;i<3;i++)
   { 
      if(GraphsTemp_pos!=NULL)
         line2[i]=tempGraphsList.GetNext(GraphsTemp_pos);
	  	else
			line2[i]=tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);
   }
   

   CString TimeStr,StrOff,AlarmStr;

   if(GraphsTemp_pos!=NULL) 
      TimeStr=tempGraphsList.GetNext(GraphsTemp_pos);
   else
      TimeStr=tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);
   

	CRect TempRect=TIMESTRINGRECT;
	int LineGap =GraphData.GRAPH_END_Y-1088;
	//if(Manual)
		TempRect+=CPoint(0,LineGap);

	CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempRect, TimeStr/*[Lang_Index]*/ ,false,Lang_Index);	
	
	float TickT=0;float TickF=0;float TickW=0;float TickH=0;float TickL=0;
	float TickA=0;
	bool T,A,F,W,H,L;
	A=false;H=false;L=false;
	T=false;F=false;W=false;
	float LastLabel=atofloat(GraphData.HData[INCLABEL]);
	float FirstLabel=atofloat(GraphData.HData[0]);
	char buf[10]="   ";
	CRect rect;
	float Graphwid=GRAPH_WIDTH;

	/*printing GraphData.tick values*/

	if(GraphsTemp_pos!=NULL)
	{ 
      StrOff=tempGraphsList.GetNext(GraphsTemp_pos);
      AlarmStr=tempGraphsList.GetNext(GraphsTemp_pos);
	}
	else
	{ 
      StrOff=tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);
      AlarmStr=tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);
	}

   if(GraphData.TickData[1]!=0xFFFF)
	{	
		TempRect=TICKASTRRECT;
      LineGap =GraphData.GRAPH_END_Y-1108;
	//	if(Manual)
			TempRect+=CPoint(0,LineGap);

		CRect TempValueRect=TICKAVALUERECT;
		//if(Manual)
				TempValueRect+=CPoint(0,LineGap);

		CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempRect , line1/*[Lang_Index]*/[1],false,Lang_Index);
		if(GraphData.TickData[1] == 0xFFFE)
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , StrOff/*[Lang_Index]*/,false,Lang_Index);
		else if(GraphData.TickData[1] == 0xFFFD)
				CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , AlarmStr/*[Lang_Index]*/,false,Lang_Index);
		else
		{
		
			char buffer[10];
			sprintf(buffer,"%5.3f",((float)GraphData.TickData[1]/TICK_PRESCALE));
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , buffer,false,Lang_Index);
		}  
	}

	if(GraphData.TickData[0] !=0xFFFF)
	{
		TempRect=TICKTSTRRECT;
	//	if(Manual)
      LineGap =GraphData.GRAPH_END_Y-1108;
			TempRect+=CPoint(0,LineGap);
		
		CRect TempValueRect=TICKTVALUERECT;
	//	if(Manual)
			TempValueRect+=CPoint(0,LineGap);

		CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempRect , line1/*[Lang_Index]*/[0],false,Lang_Index);
		if(GraphData.TickData[0] == 0xFFFE)
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , StrOff/*[Lang_Index]*/,false,Lang_Index);
		else if(GraphData.TickData[0] == 0xFFFD)
				CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , AlarmStr/*[Lang_Index]*/,false,Lang_Index);
		else
		{
		
			char buffer[10];
			sprintf(buffer,"%5.3f",((float)GraphData.TickData[0]/TICK_PRESCALE));
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black, TempValueRect, buffer,false,Lang_Index);
		}
	}

	if(GraphData.TickData[2] !=0xFFFF)
	{
		TempRect=TICKFSTRRECT;
      LineGap =GraphData.GRAPH_END_Y-1108;
		//if(Manual)
			TempRect+=CPoint(0,LineGap);
		
		CRect TempValueRect=TICKFVALUERECT;
		//if(Manual)
			TempValueRect+=CPoint(0,LineGap);

		CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempRect , line1/*[Lang_Index]*/[2],false,Lang_Index);
		if(GraphData.TickData[2] == 0xFFFE)
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , StrOff/*[Lang_Index]*/,false,Lang_Index);
		else if(GraphData.TickData[2] == 0xFFFD)
				CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , AlarmStr/*[Lang_Index]*/,false,Lang_Index);
		else
		{
		
			char buffer[10];
			sprintf(buffer,"%5.3f",((float)GraphData.TickData[2]/TICK_PRESCALE));
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , buffer,false,Lang_Index);
		}
	}

	if(GraphData.TickData[3] !=0xFFFF)
	{
		TempRect=TICKWSTRRECT;
	//	if(Manual)
      LineGap =GraphData.GRAPH_END_Y-1118;
			TempRect+=CPoint(0,LineGap);

		CRect TempValueRect=TICKWVALUERECT;
		//if(Manual)
			TempValueRect+=CPoint(0,LineGap);

		CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempRect , line2/*[Lang_Index]*/[0],false,Lang_Index);
		if(GraphData.TickData[3] == 0xFFFE)
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , StrOff/*[Lang_Index]*/,false,Lang_Index);
		else if(GraphData.TickData[3] ==0xFFFD)
				CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , AlarmStr/*[Lang_Index]*/,false,Lang_Index);
		else
		{
			char buffer[10];
			sprintf(buffer,"%5.3f",((float)GraphData.TickData[3]/TICK_PRESCALE));
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , buffer,false,Lang_Index);
		}
	}

	if(GraphData.TickData[4] !=0xFFFF)
	{
		TempRect=TICKHSTRRECT;
		//if(Manual)
      LineGap =GraphData.GRAPH_END_Y-1118;
			TempRect+=CPoint(0,LineGap);
		
		CRect TempValueRect=TICKHVALUERECT;
	//	if(Manual)
			TempValueRect+=CPoint(0,LineGap);

			char buffer[10];
		CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempRect , line2/*[Lang_Index]*/[1],false,Lang_Index);
		if(GraphData.TickData[4] == 0xFFFE)
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , StrOff/*[Lang_Index]*/,false,Lang_Index);
		else if(GraphData.TickData[4] == 0xFFFD)
				CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , AlarmStr/*[Lang_Index]*/,false,Lang_Index);
		else
		{
		
			sprintf(buffer,"%5.3f",((float)GraphData.TickData[4]/TICK_PRESCALE));
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black, TempValueRect, buffer,false,Lang_Index);
		}
	}

	if(GraphData.TickData[5] !=0xFFFF)
	{
		TempRect=TICKLSTRRECT;
	//	if(Manual)
      LineGap =GraphData.GRAPH_END_Y-1118;
			TempRect+=CPoint(0,LineGap);
		
		CRect TempValueRect=TICKLVALUERECT;
		//if(Manual)
			TempValueRect+=CPoint(0,LineGap);

		CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempRect , line2/*[Lang_Index]*/[2],false,Lang_Index);
		if(GraphData.TickData[5] == 0xFFFE)
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , StrOff/*[Lang_Index]*/,false,Lang_Index);
		else if(GraphData.TickData[5] == 0xFFFD)
				CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , AlarmStr/*[Lang_Index]*/,false,Lang_Index);
		else
		{
			
			char buffer[10];
			sprintf(buffer,"%5.3f",((float)GraphData.TickData[5]/TICK_PRESCALE));
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TempValueRect , buffer,false,Lang_Index);
		}
	}

//	printf("Returning \n");
}


/*********************************************************/
/* This function converts the passed string to its       */
/* equivilent float value and returns it.				 */
/*********************************************************/
float CVgaDrawGraph::atofloat(CString value)
{	
	char buffer[IntegerLength]="   ";
	for(int Length =0;Length<value.GetLength();Length++)
		buffer[Length]=(char)value.GetAt(Length);
	return (float)atof(buffer);
}

void CVgaDrawGraph::StoreDate_Time(unsigned char *&data, int &length)
{
		/*Storing Date.*/
	char Temp[10];
		CString TempYear = 	_itoa(CVgaMenuItem::Convert_Char_To_Integer(data,length,0),Temp,10);
		if(TempYear.GetLength() ==1)
			TempYear = "0"+TempYear;
		//TempYear +="/";
		CString TempMonth = 	_itoa(CVgaMenuItem::Convert_Char_To_Integer(data,length,0),Temp,10);
		if(TempMonth.GetLength() ==1)
			TempMonth = "0"+TempMonth;
		TempMonth +="/";
		char Temp1[10];
		CString TempDay =	_itoa(CVgaMenuItem::Convert_Char_To_Integer(data,length,0),Temp1,10);
		if(TempDay.GetLength() ==1)
			 "0"+TempDay;
		if(CChildView::Language_Index <= Asian_Language_Start)
		TempDay +="/";
		if(CChildView::Language_Index>Asian_Language_Start)
		DateString ="20"+TempYear+"/"+TempMonth+TempDay;
		else if(CChildView::metric)
		DateString =TempDay+TempMonth+TempYear;
		else
		DateString =TempMonth+TempDay+TempYear;
		/* Storing Time.*/
		CString TempHour = _itoa(CVgaMenuItem::Convert_Char_To_Integer(data,length,0),Temp,10);
		if(TempHour.GetLength() ==1)
			TempHour = "0"+TempHour;
		TempHour +=":";
		CString TempMinute = _itoa(CVgaMenuItem::Convert_Char_To_Integer(data,length,0),Temp,10);
		if(TempMinute.GetLength() ==1)
			TempMinute = "0"+TempMinute;

		TimeString =TempHour+TempMinute;
}

void CVgaDrawGraph::CopyGraph(CVgaDrawGraph *Graph)
{	
	Graph->Lang_Index=CChildView::Language_Index;
	for(int j=0;j<20;j++)
		Graph->GraphData.CycleCount[j]=GraphData.CycleCount[j];
//	Graph->CycleCountText=CycleCountText;
	Graph->GraphData.DataLength=GraphData.DataLength;
	Graph->DateString=DateString;
	for(int i=0;i<GraphData.DataLength;i++)
	Graph->GraphData.graphdata[i]=GraphData.graphdata[i];

	for(i=0;i<20;i++)
		Graph->GraphData.SystemPressure[i]=GraphData.SystemPressure[i];

   //Graph->MaxGraphType=MaxGraphType;
	for(int x=0;x<20;x++)
	Graph->GraphData.GRAPHTITLE[x]=GraphData.GRAPHTITLE[x];
	Graph->GraphData.GraphColour=GraphData.GraphColour;
	Graph->HS_CompareGraphNum=HS_CompareGraphNum;
	Graph->HSCompareGraph=HSCompareGraph;
	Graph->GraphData.GRAPH_HEIGHT=GraphData.GRAPH_HEIGHT;
	Graph->GraphData.graph_type=GraphData.graph_type;
	Graph->AlreadyPrinted=false;
	for(i=0;i<11;i++)
		for(int y=0;y<10;y++)
	Graph->GraphData.HData[i][y]=GraphData.HData[i][y];

	if(GraphData.graph_type<(PMC_GRAPH-1)/*graph_type != CScreenObject::VGA_HORNSCANGRAPH*/)
	{
		for(i=0;i<4;i++)
			for(int y=0;y<8;y++)
			Graph->GraphData.VData[i][y]=GraphData.VData[i][y];

		Graph->GraphData.no_of_ticks=GraphData.no_of_ticks;
		for(i=0;i<GraphData.no_of_ticks;i++)
		{
			Graph->GraphData.tick[i].tick_char=GraphData.tick[i].tick_char;
			Graph->GraphData.tick[i].tick_location=GraphData.tick[i].tick_location;
		}
		Graph->GraphData.GraphNum=GraphData.GraphNum;
		for(i=0;i<7;i++)
		Graph->GraphData.TickData[i]=GraphData.TickData[i];
		
		Graph->GraphData.ExtraText=GraphData.ExtraText;
		
			Graph->GraphData.ManualStr=GraphData.ManualStr;
	}

}

void CVgaDrawGraph::PrintHSText(CChildView *View,CDC *pDC)
{
	int StartX=100;
	int StartY=1050 +TotalStrings*25 ;
	if(View->PrintGraphTextObjectList.GetCount())
	{
		while(View->PrintGraphTextObjectList.GetCount())
		{
			CPrintText *object = View->PrintGraphTextObjectList.GetHead();
			if((object->CoOrdinate.y!=0)&&(!CChildView::AbortPrinting))
			{
				object->CoOrdinate.y=StartY;
				object->CoOrdinate.x=StartX;
				object->Draw(pDC);
				StartY+=50;
				delete View->PrintGraphTextObjectList.RemoveHead();
			}
			else
			{
				delete View->PrintGraphTextObjectList.RemoveHead();
				break;
			}
		}
	}
	return;
}

bool CVgaDrawGraph::GraphForPrinting(CChildView *view)
{
	if(!view->CheckForPrinting())
		return false;
   
   

	if(view->WeldOnChangedPreset)/* Weld Done On Changed Preset*/
	{
		if((!PowerGraph.PrintSampleDisable)&&(GraphData.graph_type==POWGRAPH/*CScreenObject::VGA_POWERGRAPH*/))
			return true;

		if((!ColDistance.PrintSampleDisable)&&((GraphData.graph_type==DISTINGRAPH)||(GraphData.graph_type==DISTMMGRAPH))/*(graph_type==CScreenObject::VGA_COLDISTGRAPH)*/)
			return true;

		if((!VelocityGraph.PrintSampleDisable)&&((GraphData.graph_type==VELINGRAPH)||(GraphData.graph_type==VELMMGRAPH))/*(graph_type==CScreenObject::VGA_VELOCITYGRAPH)*/)
			return true;

		if((!ForceGraph.PrintSampleDisable)&&((GraphData.graph_type==FORCELBGRAPH)||(GraphData.graph_type==FORCENGRAPH))/*(graph_type==CScreenObject::VGA_FORCEGRAPH)*/)
			return true;

		if((!AmplitudeGraph.PrintSampleDisable)&&(GraphData.graph_type==AMPLIGRAPH/*CScreenObject::VGA_AMPLITUDEGRAPH*/))
			return true;

		if((!FrequencyGraph.PrintSampleDisable)&&(GraphData.graph_type==FREQUGRAPH/*CScreenObject::VGA_FREQUENCYGRAPH*/))
			return true;
	}
	else
	{
		int PresentAlarmCount= view->PresentAlarmCount;
		int AlarmCount= CChildView::AlarmCount;
		int PresentWeldCount= view->PresentWeldCount;

		if(GraphData.graph_type==POWGRAPH/*CScreenObject::VGA_POWERGRAPH*/)
		{
			if((PresentAlarmCount) && (PowerGraph.PrintOnAlarmValue))
				return true;
			else if(!PowerGraph.PrintSampleDisable)
				if((((PresentWeldCount-PowerGraph.BaseCount)%(PowerGraph.PrintSampleValue))==1)
					||((PresentWeldCount-PowerGraph.BaseCount)==1)||(PowerGraph.PrintSampleValue==1))
				return true;
		}
			
		if((GraphData.graph_type==DISTINGRAPH/*CScreenObject::VGA_COLDISTGRAPH*/)||(GraphData.graph_type==DISTMMGRAPH))
		{
			if((PresentAlarmCount) && (ColDistance.PrintOnAlarmValue))
				return true;
			else if(!ColDistance.PrintSampleDisable)
				if((((PresentWeldCount-ColDistance.BaseCount)%(ColDistance.PrintSampleValue))==1)
					||((PresentWeldCount-ColDistance.BaseCount)==1)||(ColDistance.PrintSampleValue==1))
			return true;
		}

		if((GraphData.graph_type==VELINGRAPH/*CScreenObject::VGA_VELOCITYGRAPH*/)||(GraphData.graph_type==VELMMGRAPH))
		{
			if((PresentAlarmCount) && (VelocityGraph.PrintOnAlarmValue))
				return true;
			else if(!VelocityGraph.PrintSampleDisable)
				if((((PresentWeldCount-VelocityGraph.BaseCount)%(VelocityGraph.PrintSampleValue))==1)
					||((PresentWeldCount-VelocityGraph.BaseCount)==1)||(VelocityGraph.PrintSampleValue==1))
				return true;
		}

		if((GraphData.graph_type==FORCELBGRAPH/*CScreenObject::VGA_FORCEGRAPH*/)||(GraphData.graph_type==FORCENGRAPH))
		{
			if((PresentAlarmCount) && (ForceGraph.PrintOnAlarmValue))
				return true;
			else if(!ForceGraph.PrintSampleDisable)
				if((((PresentWeldCount-ForceGraph.BaseCount)%(ForceGraph.PrintSampleValue))==1)
					||((PresentWeldCount-ForceGraph.BaseCount)==1)||(ForceGraph.PrintSampleValue==1))
				return true;
		}

		if(GraphData.graph_type==AMPLIGRAPH/*CScreenObject::VGA_AMPLITUDEGRAPH*/)
		{
			if((PresentAlarmCount) && (AmplitudeGraph.PrintOnAlarmValue))
				return true;
			else if(!AmplitudeGraph.PrintSampleDisable)
				if((((PresentWeldCount-AmplitudeGraph.BaseCount)%(AmplitudeGraph.PrintSampleValue))==1)
					||((PresentWeldCount-AmplitudeGraph.BaseCount)==1)||(AmplitudeGraph.PrintSampleValue==1))
				return true;
		}

		if(GraphData.graph_type==FREQUGRAPH/*CScreenObject::VGA_FREQUENCYGRAPH*/)
		{
			if((PresentAlarmCount) && (FrequencyGraph.PrintOnAlarmValue))
				return true;
			else if(!FrequencyGraph.PrintSampleDisable)
				if((((PresentWeldCount-FrequencyGraph.BaseCount)%(FrequencyGraph.PrintSampleValue))==1)
					||((PresentWeldCount-FrequencyGraph.BaseCount)==1)||(FrequencyGraph.PrintSampleValue==1))
				return true;
		}
	}
	return false;
}


bool CVgaDrawGraph::GraphForUSB(CChildView *view)
{
	if(!view->ISUSBPresent)
		return false;

		/*replace all the printing parameters with USB parameters*/
	if(view->WeldOnChangedPreset)/* Weld Done On Changed Preset*/
	{
		if((!USBPowerGraph.USBSampleDisable)&&(GraphData.graph_type==POWGRAPH/*graph_type==CScreenObject::VGA_POWERGRAPH*/))
			return true;

		if((!USBColDistance.USBSampleDisable)&&((GraphData.graph_type==DISTINGRAPH)||(GraphData.graph_type==DISTMMGRAPH))/*(graph_type==CScreenObject::VGA_COLDISTGRAPH)*/)
			return true;

		if((!USBVelocityGraph.USBSampleDisable)&&((GraphData.graph_type==VELINGRAPH)||(GraphData.graph_type==VELMMGRAPH))/*(graph_type==CScreenObject::VGA_VELOCITYGRAPH)*/)
			return true;

		if((!USBForceGraph.USBSampleDisable)&&((GraphData.graph_type==FORCELBGRAPH)||(GraphData.graph_type==FORCENGRAPH))/*(graph_type==CScreenObject::VGA_FORCEGRAPH)*/)
			return true;

		if((!USBAmplitudeGraph.USBSampleDisable)&&(GraphData.graph_type==AMPLIGRAPH)/*CScreenObject::VGA_AMPLITUDEGRAPH*/)
			return true;

		if((!USBFrequencyGraph.USBSampleDisable)&&(GraphData.graph_type==FREQUGRAPH)/*CScreenObject::VGA_FREQUENCYGRAPH*/)
			return true;
	}
	else
	{
		int PresentAlarmCount= view->PresentAlarmCount;
		int AlarmCount= CChildView::AlarmCount;
	
		if(GraphData.graph_type==POWGRAPH/*CScreenObject::VGA_POWERGRAPH*/)
		{
//			printf("\n graph_type==POWGRAPH");
         if((PresentAlarmCount) && (USBPowerGraph.USBOnAlarmValue))
				return true;
			else if(!USBPowerGraph.USBSampleDisable)
				if((((view->PresentWeldCount-USBPowerGraph.BaseCount)%(USBPowerGraph.USBSampleValue))==1)
					||((view->PresentWeldCount-USBPowerGraph.BaseCount)==1)||(USBPowerGraph.USBSampleValue==1))
				return true;
		}
		
		if((GraphData.graph_type==DISTINGRAPH/*CScreenObject::VGA_COLDISTGRAPH*/)||(GraphData.graph_type==DISTMMGRAPH))
		{
//			printf("\n graph_type==DISTINGRAPH");
         if((PresentAlarmCount) && (USBColDistance.USBOnAlarmValue))
				return true;
			else if(!USBColDistance.USBSampleDisable)
				if((((view->PresentWeldCount-USBColDistance.BaseCount)%(USBColDistance.USBSampleValue))==1)
					||((view->PresentWeldCount-USBColDistance.BaseCount)==1)||(USBColDistance.USBSampleValue==1))
				return true;
		}

		if((GraphData.graph_type==VELINGRAPH/*CScreenObject::VGA_VELOCITYGRAPH*/)||(GraphData.graph_type==VELMMGRAPH))
		{
//			printf("\n VELINGRAPH");
         if((PresentAlarmCount) && (USBVelocityGraph.USBOnAlarmValue))
				return true;
			else if(!USBVelocityGraph.USBSampleDisable)
			if((((view->PresentWeldCount-USBVelocityGraph.BaseCount)%(USBVelocityGraph.USBSampleValue))==1)
				||((view->PresentWeldCount-USBVelocityGraph.BaseCount)==1)||(USBVelocityGraph.USBSampleValue==1))
			return true;
		}

		if((GraphData.graph_type==FORCELBGRAPH/*CScreenObject::VGA_FORCEGRAPH*/)||(GraphData.graph_type==FORCENGRAPH))
		{
//			printf("\n FORCELBGRAPH");
         if((PresentAlarmCount) && (USBForceGraph.USBOnAlarmValue))
				return true;
			else if(!USBForceGraph.USBSampleDisable)
				if((((view->PresentWeldCount-USBForceGraph.BaseCount)%(USBForceGraph.USBSampleValue))==1)
					||((view->PresentWeldCount-USBForceGraph.BaseCount)==1)||(USBForceGraph.USBSampleValue==1))
				return true;
		}

		if(GraphData.graph_type==AMPLIGRAPH/*CScreenObject::VGA_AMPLITUDEGRAPH*/)
		{
//			printf("\n AMPLIGRAPH");
         if((PresentAlarmCount) && (USBAmplitudeGraph.USBOnAlarmValue))
				return true;
			else if(!USBAmplitudeGraph.USBSampleDisable)
				if((((view->PresentWeldCount-USBAmplitudeGraph.BaseCount)%(USBAmplitudeGraph.USBSampleValue))==1)
					||((view->PresentWeldCount-USBAmplitudeGraph.BaseCount)==1)||(USBAmplitudeGraph.USBSampleValue==1))
				return true;
		}

		if(GraphData.graph_type==FREQUGRAPH/*CScreenObject::VGA_FREQUENCYGRAPH*/)
		{
//			printf("\n graph_type==FREQUGRAPH");
         if((PresentAlarmCount) && (USBFrequencyGraph.USBOnAlarmValue))
				return true;
			else if(!USBFrequencyGraph.USBSampleDisable)
				if((((view->PresentWeldCount-USBFrequencyGraph.BaseCount)%(USBFrequencyGraph.USBSampleValue))==1)
					||((view->PresentWeldCount-USBFrequencyGraph.BaseCount)==1)||(USBFrequencyGraph.USBSampleValue==1))
				return true;
		}
	}
	return false;
}

void CVgaDrawGraph::YAxis2Graduation(CDC* pDC)
{
	CPen pen_bounding;
	CPen *oldpen;
	pen_bounding.CreatePen( NULL , 2, COLORBLACK);
	oldpen=pDC->SelectObject(&pen_bounding);
	CPoint P1,P2;
	if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{
		int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
		for (int Index = 1; Index <= 19; Index++ ) 
		{
			int Y1 = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT - ((int)(Index * 13.6))*2;
			if(Index==19)
				Y1=Y1+2;
			P1= CPoint((GraphData.GRAPH_START_X+800-6),(Y1));
			P2= CPoint((GraphData.GRAPH_START_X+800+6),(Y1));
			P1=CalibPoint(P1, nHorz,nVert);
			P2=CalibPoint(P2, nHorz,nVert);
      		pDC->MoveTo(P1);
			pDC->LineTo(P2);

		}
	}
	else
	{
		for (int Index = 1; Index <= 19; Index++ ) 
		{
			int Y1 = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT - (int)(Index * 13.6);
			if(Index==19)
				Y1=Y1+1;
      		pDC->MoveTo(((GraphData.GRAPH_END_X - 3)),(Y1));
			pDC->LineTo(((GraphData.GRAPH_END_X + 3)),(Y1));
		}
	}
	pDC->SelectObject(oldpen);
	pen_bounding.DeleteObject();
}

void CVgaDrawGraph::DrawAvgPowerGraph(CDC *pDC,CChildView*view)
{
	if(GraphData.DataLength>0)
	{
		CVgaDrawGraph *obj ;
		int MaxVLabelValue=0;
		obj = /*view->*/theApp.GraphsDataList.GetHead();
		MaxVLabelValue = (int)obj->atofloat(obj->GraphData.VData[3]);

		CPen pen_graph;
		CPen *oldpen;
		pen_graph.CreatePen( NULL , 1,CChildView::Color_Array[Gray]);
		oldpen=pDC->SelectObject(&pen_graph);
		short *ptr =GraphData.graphdata;
		CPoint point1,point2;
		int tempVal =(GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-1);
		int Y1 =0;
	
		if (GraphData.graph_type == (PMC_GRAPH-1))//CScreenObject::VGA_HORNSCANGRAPH)
		{
			if(*ptr > MAX_HS_YCORD) 
				*ptr = MAX_HS_YCORD;
			Y1= (tempVal- (int) ((*ptr)*2));//*GRAPH_PRESCALE
		}
		else
		{
			if(*ptr > MAX_VIEWGRAPH_YCORD) 
				*ptr = MAX_VIEWGRAPH_YCORD;
			Y1= (tempVal- (int) ((*ptr)*GRAPH_PRESCALE));
		}


		if(view->UpperPMCLimit!=0)
		{

			Y1-=((view->UpperPMCLimit*270)/MaxVLabelValue);
			if(Y1<GraphData.GRAPH_START_Y)
				Y1=GraphData.GRAPH_START_Y;
			point1=CPoint(GraphData.GRAPH_START_X,(Y1));

			pDC->MoveTo(point1);
			for(int a=1;a<GraphData.DataLength;a++)
			{
				if(*(ptr +a) < 0)
					*(ptr+a) = 0;
		
			if (GraphData.graph_type == (PMC_GRAPH-1))//CScreenObject::VGA_HORNSCANGRAPH)
			{
				if(*(ptr+a) > MAX_HS_YCORD) 
					*(ptr+a) = MAX_HS_YCORD;
				Y1= (tempVal- (int) ((*(ptr+a))*2));//*GRAPH_PRESCALE
			}
			else
			{
				if(*(ptr+a) > MAX_VIEWGRAPH_YCORD) 
					*(ptr+a) = MAX_VIEWGRAPH_YCORD;
				Y1= (tempVal- (int) ((*(ptr+a))*GRAPH_PRESCALE));
			}



				Y1-=((view->UpperPMCLimit*270)/MaxVLabelValue);
				if(Y1<GraphData.GRAPH_START_Y)
					Y1=GraphData.GRAPH_START_Y;
				point2=CPoint((GraphData.GRAPH_START_X+a),(Y1));
			
				pDC->LineTo(point2);
				pDC->MoveTo(point2);
			}

			 tempVal =(GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-1);
				Y1 =0;
		
			if (GraphData.graph_type  == (PMC_GRAPH-1))//CScreenObject::VGA_HORNSCANGRAPH)
			{
				if(*ptr > MAX_HS_YCORD) 
					*ptr = MAX_HS_YCORD;
				Y1= (tempVal- (int) ((*ptr)*2));//*GRAPH_PRESCALE
			}
			else
			{
				if(*ptr > MAX_VIEWGRAPH_YCORD) 
					*ptr = MAX_VIEWGRAPH_YCORD;
				Y1= (tempVal- (int) ((*ptr)*GRAPH_PRESCALE));
			}


		}

		if(view->LowerPMCLimit)
		{


			Y1+=((view->LowerPMCLimit*270)/MaxVLabelValue);
			if(Y1>GraphData.GRAPH_END_Y)
				Y1=GraphData.GRAPH_END_Y;
			point1=CPoint(GraphData.GRAPH_START_X,(Y1));

			pDC->MoveTo(point1);
			for(int a=1;a<GraphData.DataLength;a++)
			{
				if(*(ptr +a) < 0)
					*(ptr+a) = 0;
		
				if (GraphData.graph_type == (PMC_GRAPH-1))//CScreenObject::VGA_HORNSCANGRAPH)
				{
					if(*(ptr+a) > MAX_HS_YCORD) 
						*(ptr+a) = MAX_HS_YCORD;
					Y1= (tempVal- (int) ((*(ptr+a))*2));//*GRAPH_PRESCALE
				}
				else
				{
					if(*(ptr+a) > MAX_VIEWGRAPH_YCORD) 
						*(ptr+a) = MAX_VIEWGRAPH_YCORD;
					Y1= (tempVal- (int) ((*(ptr+a))*GRAPH_PRESCALE));
				}


					Y1+=((view->LowerPMCLimit*270)/MaxVLabelValue);
			if(Y1>GraphData.GRAPH_END_Y)
				Y1=GraphData.GRAPH_END_Y;
				point2=CPoint((GraphData.GRAPH_START_X+a),(Y1));
			
				pDC->LineTo(point2);
				pDC->MoveTo(point2);
			}
			pDC->SelectStockObject(BLACK_PEN);
		}
	
		pDC->SelectObject(oldpen);
		pen_graph.DeleteObject( );
	}
	
}

void CVgaDrawGraph::DrawAveragePowerGraph(CDC *pDC)
{

}


void CVgaDrawGraph::RecalculateAverageGraph(CChildView* view)
{

	if(GraphData.DataLength==0)
		return;
	/*Getting Highest %age Point in Average graph*/
	int HighestAveragePoint=this->GraphData.graphdata[0];
	for(int GraphDataPoint =1; GraphDataPoint<this->GraphData.DataLength;GraphDataPoint++)
	{
		if(GraphData.graphdata[GraphDataPoint]>HighestAveragePoint)
			HighestAveragePoint=this->GraphData.graphdata[GraphDataPoint];
	}
	/*if(CVGAButtons::PMCScreen)
		HighestAveragePoint=CChildView::PMCMaxVdata;//(HighestAveragePoint*CChildView::PMCMaxVdata)/160;
	if(!CVGAButtons::PMCScreen)*/
	{
		HighestAveragePoint=((HighestAveragePoint*CChildView::PMCMaxVdata)/160);
		if(!HighestAveragePoint)
			HighestAveragePoint++;
		HighestAveragePoint+=CChildView::UpperPMCLimit;
	}

	/*Getting Highest Point for Power Graph*/
	CVgaDrawGraph *obj ;
	int HighestPowerPoint=0;
	obj = /*view->*/theApp.GraphsDataList.GetHead();
	HighestPowerPoint = (int)obj->atofloat(obj->GraphData.VData[3]);
	
	
	/*Case 1: If Highest %age Point in Average graph is Greater then
			Highest Point for Power Graph*/
	if(HighestAveragePoint>HighestPowerPoint)
	{
		
		/* Choose Vdata Label Accordingly*/
		int MaxVLabelValue;
		if(HighestAveragePoint<=10)
			MaxVLabelValue= 10;
		else if(HighestAveragePoint<=20)
			MaxVLabelValue= 20;
		else if(HighestAveragePoint<=40)
			MaxVLabelValue= 40;
		else if(HighestAveragePoint<=80)
			MaxVLabelValue= 80;
		else
			MaxVLabelValue= 100;
		
		/* Giving graph labels to power graph*/
		for(int GraphVdata=1;GraphVdata<=4;GraphVdata++)
		{
			float GraphLabel = (((float)MaxVLabelValue/4))*GraphVdata;
			char c[8]="       ";
			sprintf(&c[0],"%5.1f",GraphLabel);
			for(int VDataLen =0;VDataLen<8;VDataLen++)
				obj->GraphData.VData[GraphVdata-1][VDataLen]=(TCHAR)c[VDataLen];
		}
	
		/*Convert Power Graph data to fit Average graph scale */
		for(int GraphDataPoint =0; GraphDataPoint<obj->GraphData.DataLength;GraphDataPoint++)
		{
			obj->GraphData.graphdata[GraphDataPoint]=((obj->GraphData.graphdata[GraphDataPoint]*HighestPowerPoint)/MaxVLabelValue);
		}

		for(GraphDataPoint =0; GraphDataPoint<this->GraphData.DataLength;GraphDataPoint++)
		{
			GraphData.graphdata[GraphDataPoint]=(GraphData.graphdata[GraphDataPoint]*CChildView::PMCMaxVdata)
				/MaxVLabelValue;
		}

	}
	else if(HighestAveragePoint<HighestPowerPoint)
	{
		/*if((CChildView::PMCMaxVdata>=HighestAveragePoint))//&&(!CVGAButtons::PMCScreen))
		return;*/
		
		/* highest power point is greater than Average Graph Power*/
		/* In this Case No Need to convert Power graph.			*/
		/* So converting only Average Graph						*/
		/* Here The VLabel wil remain same as they were			*/
		/*Prepare Average graph DATA to Pixcels					*/
		
		for(int GraphDataPoint =0; GraphDataPoint<this->GraphData.DataLength;GraphDataPoint++)
		{
			GraphData.graphdata[GraphDataPoint]=(GraphData.graphdata[GraphDataPoint]*CChildView::PMCMaxVdata)
				/HighestPowerPoint;
		}
	}
}

bool CVgaDrawGraph::PrintGraphManualStr(CPoint p, CDC *pDC,int Type, bool ExtraText)
{ //printf("Inside PrintGraphManualStr \n");
	p.x=PARAMETERSTARTXCORD+25;
	//AmpStr=true;ForceStr=true;
	CString ForceString[2],AmpString[2];
	for(int i=0;i<2;i++)
	{	if(GraphsTemp_pos!=NULL)
			ForceString[i]=tempGraphsList.GetNext(GraphsTemp_pos);
			 else
				 ForceString[i]=tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);
	}

	for( i=0;i<2;i++)
	{	if(GraphsTemp_pos!=NULL)
			AmpString[i]=tempGraphsList.GetNext(GraphsTemp_pos);
				else
					AmpString[i]=tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);

	}

	if((Type == AMPLIGRAPH/*CScreenObject::VGA_AMPLITUDEGRAPH*/)&&ExtraText)
	{
		
		int XCord =p.x;
		int YCoordinate =p.y-90;
		for(int i=0;i<2;i++)
		{
			YCoordinate+=25;
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CRect(XCord,YCoordinate,XCord ,YCoordinate),AmpString/*[CChildView::Language_Index]*/[i]  ,false,CChildView::Language_Index);
			
		}
		return true;
	}
	if((Type ==FORCELBGRAPH/*CScreenObject::VGA_FORCEGRAPH*/)||(Type ==FORCENGRAPH)&&ExtraText)
	{
		int XCord =p.x;
		int YCoordinate =p.y-90;
		for(int i=0;i<2;i++)
		{
			YCoordinate+=25;
			CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CRect(XCord,YCoordinate,XCord ,YCoordinate),ForceString/*[CChildView::Language_Index]*/[i]  ,false,CChildView::Language_Index);
			
		}
		return true;
	}
	return false;
}
