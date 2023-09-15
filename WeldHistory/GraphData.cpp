// GraphData.cpp: implementation of the CGraphData class.
//
//////////////////////////////////////////////////////////////////////

/*
Revision #		Date		Author			Description
----------		--------	----------		-------------------------------------
1.0				04/24/06	LAM				Initial Version.
1.1				05/10/07	BSahu			Modified Code to Add View HosrnScan Graphs.
1.2				05/23/07	BSahu           Modified DrawTicksMark() For Tracker issue 4114
1.3				10/22/07	BSahu           Modified To Add Printing Feature
1.4				10/25/07	BSahu           Modified Code To Fix Overlap issues.
1.5				11/05/07	BSahu			Modified code for Col Dist VLabel Overlap issue.	
1.6				09/15/08	PDwivedi		Modified code for Tracker issue.	
1.7             09/17/08    ygupta          Modified code for Tracker issue REQ00416.
1.8				09/26/09	PDwivedi		Added changes for compatability of graph Object.

*/
#include "stdafx.h"
#include "History.h"
#include "GraphData.h"
#include "HistoryView.h"

#include "winsock2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define GRAPH_WIDTH		400 

#define DEFAULT_HSGRAPHX_START   100
#define DEFAULT_HSGRAPHY_START   50
#define DEFAULT_HSGRAPHX_END     500
#define DEFAULT_HSGRAPHY_END     394

#define CORDLENGTH 2
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/**************************************************************/
/*This constructor calls the initialize functin to			  */
/*initialize all graph datas.									  */
/**************************************************************/

int CGraphData::GraphCount;
CGraphData::CGraphData()
{
	InitilizeData();
	GraphData.GRAPH_START_X=100;
	GraphData.GRAPH_START_Y=50;
	GraphData.GRAPH_END_X=500;
	GraphData.GRAPH_END_Y=394;
	GraphData.GRAPH_HEIGHT = GraphData.GRAPH_END_Y-GraphData.GRAPH_START_Y;
}
CGraphData::CGraphData(unsigned char * &data, int & length)
{	
	/*for(int i=0;i<20;i++)
		GraphData.SystemPressure[i]='\0';
	GraphData.AlreadyPrinted=false;
	GraphData.Lang_Index=CHistoryView::Language_Index;
	GraphData.No_Graph_String=" ";
	GraphData.GraphWidth=GRAPH_WIDTH;
	data++;//VGA_GRAPH_OBJECT type.
	length--;
	GraphCount++;
	GraphData.GraphNum =GraphCount;
	
	GraphData.GRAPH_START_X	=Convert_Char_To_Integer(data,length,2);
	
	GraphData.GRAPH_START_Y = Convert_Char_To_Integer(data,length,2)-5;

	GraphData.GRAPH_END_X	= Convert_Char_To_Integer(data,length,2);

	GraphData.GRAPH_END_Y	= Convert_Char_To_Integer(data,length,2)-5;

	GraphData.GRAPH_HEIGHT = GraphData.GRAPH_END_Y-GraphData.GRAPH_START_Y;
	GraphData.GraphColour=*data++;length--;
	GraphData.GraphTypeID=Convert_Char_To_Integer(data,length,2);//(WHICHGRAPH)


	{
			GraphData.DataLength=Convert_Char_To_Integer(data,length,2);
			for(short len=0;len<(GraphData.DataLength);len++)
			{
				GraphData.graphdata[len]=(short)*data++;
				length--;
			}
			Store_VData_HData(data,length);
			StoreDate_Time(data,length);
			int g=length;

			GraphData.HSCompareGraph =false;
		}*/
    GraphData.GraphWidth=GRAPH_WIDTH;
	GraphData.GRAPH_START_X	= DEFAULT_HSGRAPHX_START;
	GraphData.GRAPH_START_Y = DEFAULT_HSGRAPHY_START;
	GraphData.GRAPH_END_X	= DEFAULT_HSGRAPHX_END;
	GraphData.GRAPH_END_Y	= DEFAULT_HSGRAPHY_END;
	GraphData.GRAPH_HEIGHT = GraphData.GRAPH_END_Y-GraphData.GRAPH_START_Y;

	GraphData.GraphTypeID=Convert_Char_To_Integer(data,length,CORDLENGTH);
	if((GraphData.GraphTypeID!=HORNSCANGRAPHID))
	{
		length -= (length+1);
		return;
	}
	GraphData.GraphColour=*data++;length--;
	//SetGraphRequestValue(GraphData.GraphTypeID);
    for(int i=0;i<20;i++)
	   GraphData.SystemPressure[i]='\0';
    AlreadyPrinted=false;
    Lang_Index=0;//CChildView::Language_Index;
    No_Graph_String=" ";
    GraphCount++;
    GraphData.GraphNum =GraphCount;
    GraphData.DataLength=Convert_Char_To_Integer(data,length,CORDLENGTH);
	if(GraphData.DataLength > GRAPH_WIDTH)
	{
		length -= (length+1);
		return;
	}
    for(short len=0;len<(GraphData.DataLength);len++)
    {
	   GraphData.graphdata[len]=(short)*data++;
	   length--;
    }
    Store_VData_HData(data,length);
    StoreDate_Time(data,length);
	HSCompareGraph =false;		
}

CGraphData::~CGraphData()
{

}

bool CGraphData::GraphBoundary;
bool CGraphData::PrintGraphBoundary=false;
//CString CGraphData::HZData;
/**************************************************************/
/*This function draws the total graph screen.				  */
/**************************************************************/
void CGraphData::Draw(CDC *pDC)
{
   
	drawgraph(pDC);
	if(!CHistoryView::HSFlag)
	DrawGraphBoundary(pDC);
	DrawTickMarks(pDC);
	DrawHLabel(pDC);
	if(!CHistoryView::HSFlag)
		DrawVLabel(pDC);
	
}

/*********************************************************/
/*This function converts Short to Cstring charecter	     */
/*********************************************************/
CString CGraphData::ConvertToTCHAR(short *ptr,int Length)
{
	CString Str;
	for(int Len=0;Len<Length;Len++)
	{
		union{
			char a[2];
			short s;
		}u;
		u.s=*ptr;
		if(u.s == 0)
		{
		//	Str+=" ";
			return Str;
		}
		else
			Str+=u.a[0];
		ptr++;
	}
	return Str;
}

/***********************************/
/*Initializes all Graph Datas      */
/***********************************/
void CGraphData::InitilizeData()
{
	for(int i=0;i<11;i++)
		for(int j=0;j<10;j++)
			GraphData.HData[i][j]=0;

	for(int i=0;i<4;i++)
		for(int j=0;j<8;j++)
			GraphData.VData[i][j]=0;

	for(int i=0;i<20;i++)
		GraphData.CycleCount[i]=0;

}

/***************************************************************************/
/* Plot the Particular Graph.		                                       */
/***************************************************************************/

void CGraphData::drawgraph(CDC *pDC)

{
	CPen pen_graph;
	CPen *oldpen;
	int x = GraphData.GraphColour;
	pen_graph.CreatePen( NULL , 1,CHistoryView::Color_Array[GraphData.GraphColour]);
	if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{
      
		int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
		if(nHorz>300)
		{
			pen_graph.DeleteObject();
			pen_graph.CreatePen( NULL , 2,CHistoryView::Color_Array[GraphData.GraphColour]);
		}
		
	}
	oldpen=pDC->SelectObject(&pen_graph);

	short *ptr =GraphData.graphdata;
	CPoint point1,point2;
	int tempVal =(GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-1);
   	if ((CHistoryView::HSFlag)&&(pDC->GetDeviceCaps(TECHNOLOGY)!=DT_RASPRINTER))
		tempVal =(GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-HEIGHT_LOWER_HSGRAPH);
    if ((CHistoryView::HSFlag)&&(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER))
		tempVal =(GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT-HEIGHT_LOWER_HSGRAPH*2);


	if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{	
      
		int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
		
     	int Y1=0;
		if (CHistoryView::HSFlag)
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
	

			if( CHistoryView::HSFlag)
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
		if(CHistoryView::HSFlag)
		{
			int a1 =(GraphData.DataLength-1)*2;

			if(GraphData.GraphColour == Blue) 
         {
            pDC->SetTextColor(COLORBLUE);
            CHistoryView::DrawPrinterText(pDC,GraphData.GRAPH_START_X+a1+4,Y1,"A" );
			
         }
			if( GraphData.GraphColour ==Red)
         {
            pDC->SetTextColor(COLORRED);
            CHistoryView::DrawPrinterText(pDC,GraphData.GRAPH_START_X+a1+18,Y1,"B" );
         }
			if(GraphData.GraphColour == Green)
			{
            pDC->SetTextColor(COLORRED);
            CHistoryView::DrawPrinterText(pDC,GraphData.GRAPH_START_X+a1+32,Y1,"C" );
         }
         pDC->SetTextColor(COLORBLACK);
		}
	}
	else
    {
		int Y1 =0;
		if (CHistoryView::HSFlag)
		{
			if(*ptr > MAX_HS_YCORD) 
				*ptr = MAX_HS_YCORD;
			Y1= (tempVal- (int) ((*ptr)*2));
		}
		else
		{
			if(*ptr > MAX_VIEWGRAPH_YCORD) 
				*ptr = MAX_VIEWGRAPH_YCORD;
			Y1= (tempVal- (int) ((*ptr)*GRAPH_PRESCALE));
		}

		point1=CPoint(GraphData.GRAPH_START_X,(Y1));
	
		pDC->MoveTo(point1);
		int len =GraphData.DataLength;

		//////////////////////////////////////////
		for(int a=0;a<GraphData.DataLength;a++)
		{
			if(*(ptr +a) < 0)
				*(ptr+a) = 0;
					
			if (CHistoryView::HSFlag)
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
		///////////////////////////////////////////
		if(CHistoryView::HSFlag)
		{
			int a1 =(GraphData.DataLength-1);
			if((GraphData.GraphColour == 2))
				CHistoryView::DrawText(pDC,GraphData.GraphColour,false,CRect(GraphData.GRAPH_START_X+6+a1,Y1,GraphData.GRAPH_START_X+6+a1,Y1),"A",true);
			if( (GraphData.GraphColour ==3))
				CHistoryView::DrawText(pDC,GraphData.GraphColour,false,CRect(GraphData.GRAPH_START_X+16+a1,Y1,GraphData.GRAPH_START_X+16+a1,Y1),"B",true);
			if((GraphData.GraphColour == 4))
				CHistoryView::DrawText(pDC,GraphData.GraphColour,false,CRect(GraphData.GRAPH_START_X+27+a1,Y1,GraphData.GRAPH_START_X+27+a1,Y1),"C",true);
		  }
		
		pDC->SelectStockObject(BLACK_PEN);
	}
	pDC->SelectObject(oldpen);
	pen_graph.DeleteObject( );
	
}

/***************************************************************************/
/* Draws Graph Boundary	with Y Axis and X Axis graduation				   */
/***************************************************************************/
void CGraphData::DrawGraphBoundary( CDC *pDC)

{
	GraphBoundary=true;
	CPen pen_bounding;
	CPen *oldpen;
	pen_bounding.CreatePen( NULL , 2, RGB(0,0,0));
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

  // Drawing Boundary 
   pDC->MoveTo(p1);
   pDC->LineTo(p2);
   pDC->LineTo(p3);
   pDC->LineTo(p4);
   pDC->LineTo(p1);
   
	 
	int Index;
	if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{	
	
		int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
		   
		/* y axis graduation*/
     
      if((GraphData.GraphNum%2)==0)
      {
         int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		   int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
         if(!CHistoryView::HSFlag)
         {
            for (Index = 1; Index <= 19; Index++ ) 
		      {
			      int Y1 = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT - ((int)(Index * 13.6))*2;
			      if(Index==19)
				      Y1=Y1+2;
			      CPoint p1((GraphData.GRAPH_END_X - 6),(Y1));
			      CPoint p2((GraphData.GRAPH_END_X + 6),(Y1));
			      p1=CalibPoint(p1, nHorz,nVert);
			      p2=CalibPoint(p2, nHorz,nVert);
      		      pDC->MoveTo(p1);
			      pDC->LineTo(p2);
		      }
         }
         
      }
      else
      {
         if(!CHistoryView::HSFlag)
         {
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
      }
            
      
	}
	else
	{
		/*Draw X Axis graduation*/
		for (Index = 1; Index < INCLABEL; Index++ ) 
		{
			 int X1 = GraphData.GRAPH_START_X + ((Index * GRAPH_WIDTH)/INCLABEL);
			 pDC->MoveTo(X1,(GraphData.GRAPH_HEIGHT+(GraphData.GRAPH_START_Y  - 3)));
			 pDC->LineTo(X1,(GraphData.GRAPH_HEIGHT+(GraphData.GRAPH_START_Y  + 3))) ;
		}
		pDC->SelectObject(&oldpen);
	}
		pen_bounding.DeleteObject( );
      

}

/****************************************************************************/
/* Draws tick marks at the graph.											*/
/****************************************************************************/
void CGraphData::DrawTickMarks( CDC *pDC)

{
	if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{
		int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
      if (CHistoryView::HSFlag)
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
			while(LineProp_X2 <= (GraphData.GRAPH_END_X))
			{	
				CPoint p1(LineProp_X1,LineProp_Y1);
				CPoint p2(LineProp_X2,LineProp_Y1);
				p1=CalibPoint(p1, nHorz,nVert);
				p2=CalibPoint(p2, nHorz,nVert);
      			pDC->MoveTo(p1);
				pDC->LineTo(p2);
				LineProp_X1 = LineProp_X2 + (nHorz/18);
				LineProp_X2 = LineProp_X1 + (nHorz/18); 
		
			}
         //To Draw last one
         LineProp_X2 = GraphData.GRAPH_END_X;
         CPoint p1(LineProp_X1,LineProp_Y1);
         CPoint p2(LineProp_X2,LineProp_Y1);
         p1=CalibPoint(p1, nHorz,nVert);
         p2=CalibPoint(p2, nHorz,nVert);
         pDC->MoveTo(p1);
			pDC->LineTo(p2);
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
			
			
			int X1 = X_Coordinate;//Align GraphData.tick in middle
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
			{
				Y_Coordinate = ((GraphData.GRAPH_START_Y+ 100));
			}
			else
			   Y_Coordinate= ((GraphData.GRAPH_START_Y+ 60));
			CHistoryView::DrawPrinterText(pDC,X_Coordinate,Y_Coordinate,GraphData.tick[LabelCount].tick_char );
		
				
		}
		pDC->SelectObject(oldpen);
		pDC->SelectObject(oldpen1);
		pen_bounding.DeleteObject();
		pen_bounding1.DeleteObject();
      }

	}
	else
	{
		if(CHistoryView::HSFlag)
		{
			
				int LineProp_Y1 = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT -202;
				int LineProp_X1 = GraphData.GRAPH_START_X;
				int LineProp_X2 = LineProp_X1+ 8;
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
		pDC->SetTextColor(COLORRED);
		CPen pen_bounding1( NULL , 2,COLORBLACK);
		CPen pen_bounding( NULL , 1, COLORBLACK);
		for(LabelCount=0;LabelCount<GraphData.no_of_ticks;LabelCount++)
		{
			X_Coordinate=GraphData.GRAPH_START_X + GraphData.tick[LabelCount].tick_location;
			
			pDC->SelectObject(&pen_bounding1);
			int X1 = X_Coordinate;//Align GraphData.tick in middle
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
				
				pDC->SelectObject(&pen_bounding);
				while(Y2 <= (GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT))
				{
					 pDC->MoveTo(X1,Y1);
					 pDC->LineTo(X2,Y2);
					 Y1 = Y2 + 6*2;
					 Y2 = Y1 + 4*2;  
				}
			
			}
			if(LabelCount % 2)
				 Y_Coordinate = ((GraphData.GRAPH_START_Y+ 35));
			else
				Y_Coordinate= ((GraphData.GRAPH_START_Y+ 15));
			pDC->ExtTextOut(X_Coordinate,Y_Coordinate,ETO_OPAQUE,NULL,
										GraphData.tick[LabelCount].tick_char,NULL);
			
		}
		pen_bounding.DeleteObject();
		pen_bounding1.DeleteObject();
		}
	}
}

/***************************************************************************/
/* Draw Horizontal Graph Labels                                            */
/***************************************************************************/
void CGraphData::DrawHLabel(CDC *pDC)

{
   int StrProp_X = GraphData.GRAPH_START_X ;
	int StrProp_Y = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT +9;
	if(CHistoryView::HSFlag)
	{
		
	   //int StrProp_Y = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT +9;
      if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
      {
        // StrProp_X = GraphData.GRAPH_START_X ;
         StrProp_Y =  GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT+9;
            //Draw the Horizontal Label 1
		   CHistoryView::DrawPrinterText(pDC,StrProp_X,StrProp_Y,CHistoryView::HZData[0]+CString("(Hz)"));
		   //Draw the Horizontal Label 2
		   StrProp_X = StrProp_X + ((5 * GraphData.GraphWidth)/INCLABEL)- 18;
         CHistoryView::DrawPrinterText(pDC,StrProp_X,StrProp_Y,CHistoryView::HZData[1]+CString("(Hz)"));

		   //Draw the Horizontal Label 3
		   StrProp_X = StrProp_X + ((5 * GraphData.GraphWidth)/INCLABEL)- 18;//((10 * GraphData.GraphWidth)/INCLABEL)- 20;
         CHistoryView::DrawPrinterText(pDC,StrProp_X,StrProp_Y,CHistoryView::HZData[2]+CString("(Hz)"));

         CHistoryView::DrawPrinterText(pDC,50,850,"Resonance");
         CHistoryView::DrawPrinterText(pDC,50,875,"Frequency");
			 
      }
      else
      {
	       /*Draw the Horizontal Label 1*/
			CHistoryView::DrawText(pDC,COLORBLACK,false,CRect(StrProp_X-20,StrProp_Y,StrProp_X-20,
											   StrProp_Y),CHistoryView::HZData[0]+" (Hz)",false);
										   
		   /*Draw the Horizontal Label 2*/
		   StrProp_X = GraphData.GRAPH_START_X + ((5 * GraphData.GraphWidth)/INCLABEL)- 20;
		   CHistoryView::DrawText(pDC,COLORBLACK,false,CRect(StrProp_X,StrProp_Y,StrProp_X,
											   StrProp_Y),CHistoryView::HZData[1]+" (Hz)",false);
											   
		   /*Draw the Horizontal Label 3*/

		   StrProp_X = GraphData.GRAPH_START_X + ((10 * GraphData.GraphWidth)/INCLABEL)- 20;
		   CHistoryView::DrawText(pDC,COLORBLACK,false,CRect(StrProp_X,StrProp_Y,StrProp_X,
										   StrProp_Y),CHistoryView::HZData[2]+" (Hz)",false);
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
			//	Y_Coordinate = ((GraphData.GRAPH_HEIGHT+PRINTGRAPHSTARTYCORD +15)) ;
				if(Index%2 ==0)
				{
				   CString s=ConvertToTCHAR(&GraphData.HData[Index][0],10);
      		   CHistoryView::DrawPrinterText(pDC,X_Coordinate,Y_Coordinate,s);
				}
				X_Coordinate += (GraphData.GraphWidth/INCLABEL);
			}
			else
			{
			CString s=ConvertToTCHAR(&GraphData.HData[Index][0],10);
			if(Index%2 ==0)
				CHistoryView::DrawText(pDC,1,false,CRect(X_Coordinate,Y_Coordinate,
												X_Coordinate,Y_Coordinate),s,false);
			X_Coordinate += (GRAPH_WIDTH/INCLABEL);
			}
		
		}
	}

}
/***************************************************************************/
/* Draw Vertical Graph Labels                                              */
/***************************************************************************/
void CGraphData::DrawVLabel(CDC *pDC)

{	
	int X_Coordinate,Y_Coordinate;
	int Index;
  
	if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{
      
		if((GraphData.GraphNum%2)==0)
			X_Coordinate = (GraphData.GRAPH_END_X+10);
		else 
			X_Coordinate = GraphData.GRAPH_START_X - 80;
		int  Start_Y = (int)(GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT - 8);
		
      
		for (int Index = 3; Index >= 0; Index--) 
		{
			Y_Coordinate = Start_Y - ((Index+1)* 67*2);
			CString s= ConvertToTCHAR(&GraphData.VData[Index][0],8);
			CHistoryView::DrawPrinterText(pDC,X_Coordinate,Y_Coordinate,s);
 		}
	
		if((GraphData.GraphNum%2)==0)
		{
			
			CString s= ConvertToTCHAR(&GraphData.GRAPHTITLE[0],15);
			CHistoryView::DrawPrinterText(pDC,X_Coordinate,GraphData.GRAPH_START_Y-40,s);
		}
		else
		{
		
		   CString s= ConvertToTCHAR(&GraphData.GRAPHTITLE[0],15);
		   CHistoryView::DrawPrinterText(pDC,X_Coordinate-30,GraphData.GRAPH_START_Y-40,s);
		}

	
	}
	else
	{
	/*Drawing Y-axis Graduation*/
	

		if ((GraphData.GraphNum %2)!=0)
			for (Index = 1; Index <= 20; Index++ ) 
			{
				
				int Y1 = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT - (int)(Index * 13);
      			pDC->MoveTo(((GraphData.GRAPH_START_X - 3)),(Y1-2));
				pDC->LineTo(((GraphData.GRAPH_START_X + 3)),(Y1-2));
					pDC->SetBkColor(CHistoryView::Color_Array[GraphData.GraphColour]);
			}
		if ((GraphData.GraphNum%2) == 0)
			for (Index = 1; Index <= 20; Index++ ) 
			{
				
				int Y1 = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT - (int)(Index * 13);
      			pDC->MoveTo(((GraphData.GRAPH_END_X - 3)),(Y1-2));
				pDC->LineTo(((GraphData.GRAPH_END_X + 3)),(Y1-2));
			}
	
	{
		if((GraphData.GraphNum%2)==0)
			X_Coordinate = GraphData.GRAPH_END_X+ 5;
		else 
			X_Coordinate = GraphData.GRAPH_START_X - 55;
		

		int  Start_Y = (int)(GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT);
	
		for (int Index = 3; Index >= 0; Index--) 
		{
			Y_Coordinate = Start_Y - (int)((Index+1)* 65);
			Y_Coordinate=(Y_Coordinate);
			CString s= ConvertToTCHAR(&GraphData.VData[Index][0],8);
			CHistoryView::DrawText(pDC,GraphData.GraphColour,false,CRect(X_Coordinate,Y_Coordinate-20,
											X_Coordinate+50,Y_Coordinate+20),s,false);
		}
	
		CRect Rect;
		if((GraphData.GraphNum%2)==0)
		{
			Rect=CRect(X_Coordinate+25,	GraphData.GRAPH_START_Y-12,
					X_Coordinate+55,GraphData.GRAPH_START_Y-12);
			CString s= ConvertToTCHAR(&GraphData.GRAPHTITLE[0],15);
			CHistoryView::DrawText(pDC,GraphData.GraphColour,false,Rect,s,true);
	
		}
		else
		{
			Rect=CRect(X_Coordinate-20,GraphData.GRAPH_START_Y-12,
						X_Coordinate-20,GraphData.GRAPH_START_Y-12);
			CString s= ConvertToTCHAR(&GraphData.GRAPHTITLE[0],15);
			CHistoryView::DrawText(pDC,GraphData.GraphColour,false,Rect,s,false);
		}
		
			CRect rect(370,GraphData.GRAPH_START_Y+10,370,GraphData.GRAPH_START_Y+30);
			pDC->FillSolidRect(rect.left,rect.top,rect.right-rect.left,
									rect.bottom-rect.top,RGB(0,0,0));
			CString s= ConvertToTCHAR(&GraphData.CycleCount[0],20);
			CHistoryView::DrawText(pDC,1,false,CRect(340,GraphData.GRAPH_START_Y+10,
											340,GraphData.GRAPH_START_Y+30),s,false);
		
	}
	}
}


int CGraphData::Convert_Char_To_Integer(unsigned char * &data, int & length, int Byte)
{
	union {
			int i;
			char c[4];
			} u;
	if(Byte!=0)
		for (int k = 0; k < Byte; k++)
		{
			u.c[k] = 0;
		}
	for (int j = Byte; j < 4; j++)
	{
		u.c[j] =*data++;
		length--;
	}
//	TRACE(_T("\n **Co-ordinates are** %d \n "),ntohl(u.i));	
	union {
			int i2;
			char c2[4];
			} u2;
	int g=3;
	for(int b=0;b<4;b++)
	{
		u2.c2[b]=u.c[g];
		g--;
	}
	return ((u2.i2));
}
void CGraphData::GetCharString(unsigned char * &data, int & length, CString *Str)
{

	CString result = "";
	int count= *data++;
	int strlen;
	strlen=count;

	for (int i = 0; i < (strlen); i++)
	{
		union {
			unsigned char ch[2];
			TCHAR character;
			}u;

			u.ch[1]=NULL;
			u.ch[0]= *data++;
		*(Str+i)= (u.character);
	}
	length -= count+1;

		union {
			unsigned char ch[2];
			TCHAR character;
			}u;
		u.ch[1]=NULL;
			u.ch[0]=NULL;
	*(Str+strlen)=(u.character);
	
}
void CGraphData::Store_VData_HData(unsigned char *&data, int &length)
/***************************************************************************/
/*Description:-                                                            */
/* Store Horizontal and Vertical Graph Labels                              */
/***************************************************************************/
{
	CHistoryView::HighLightString= -1;
	int TempFreqString[6];
	{
		
		for(int  x=0;x<3;x++)
		{
			 CHistoryView::HZData[x]=CHistoryView::GetString(data,length);
		}

	
		
			/********************************/
		/*Storing Frequencies for Horn scan graph.*/
		TotalStrings = *data++;length--;
		int ts = TotalStrings;

		for(int Strings =0;Strings<TotalStrings;Strings++)
		{
			
			int TempFreq = 	Convert_Char_To_Integer(data,length,0);
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
		int TempDigitalTuneSetting = Convert_Char_To_Integer(data,length,0);
		for(int Strings =0;Strings<TotalStrings;Strings++)
		{
			if(TempFreqString[Strings] == TempDigitalTuneSetting)
				CHistoryView::HighLightString= Strings;
		}

		DigitalTuneSetting = _itoa(TempDigitalTuneSetting,Temp,10);
		DigitalTuneSetting +=" (Hz)";
	
	}
	
	
}

void CGraphData::StoreTickData(unsigned char *&data, int &length)
/***************************************************************************/
/*Description:-                                                            */
/* Store Tick Data								                           */
/***************************************************************************/
{
	GraphData.no_of_ticks=*data++;

	length--;
	for(int  x=0;x<GraphData.no_of_ticks;x++)
	{
		GraphData.tick[x].tick_char=*data++;length--;
	
		GraphData.tick[x].tick_location=Convert_Char_To_Integer(data,length,4);
	}
	
}
void CGraphData::StoreDate_Time(unsigned char *&data, int &length)
{
		/*Storing Date.*/
		int Year = Convert_Char_To_Integer(data,length,0);
		Year += 2000;
		int Month = Convert_Char_To_Integer(data,length,0);
		int Day = Convert_Char_To_Integer(data,length,0);
		COleDateTime Date(Year,Month,Day,10,10,10);
		DateString = Date.Format(VAR_DATEVALUEONLY|DTS_SHORTDATEFORMAT );

		/* Storing Time.*/
		char Temp[10];
		CString TempHour = _itoa(Convert_Char_To_Integer(data,length,0),Temp,10);
		if(TempHour.GetLength() ==1)
			TempHour = "0"+TempHour;
		TempHour +=":";
		CString TempMinute = _itoa(Convert_Char_To_Integer(data,length,0),Temp,10);
		if(TempMinute.GetLength() ==1)
			TempMinute = "0"+TempMinute;

		TimeString =TempHour+TempMinute;
}

void CGraphData::Print(CDC *pDC,int XCoordinate,int YCoordinate,int GraphType)
{	
	
	int TEMP_GRAPH_START_X,TEMP_GRAPH_START_Y,TEMP_GRAPH_END_X,TEMP_GRAPH_END_Y,
		TEMP_GRAPH_WIDTH,TEMP_GraphNum;

	TEMP_GRAPH_START_X = GraphData.GRAPH_START_X;
	TEMP_GRAPH_START_Y = GraphData.GRAPH_START_Y;
	TEMP_GRAPH_END_X = GraphData.GRAPH_END_X;
	TEMP_GRAPH_END_Y = GraphData.GRAPH_END_Y;
	TEMP_GRAPH_WIDTH = GraphData.GraphWidth;
	TEMP_GraphNum = GraphData.GraphNum;
	

/*	if(GraphType==PRINTLISTGRAPHID)
	{
		if((GraphData.GraphTypeID ==AMPLITUDEGRAPH)&& GraphData.ExtraTest)
			CHistoryView::Manual =true;
		else if((GraphData.GraphTypeID ==FORCEGRAPH)&& GraphData.ExtraTest)
			CHistoryView::Manual =true;
	}*/

	GraphData.GRAPH_START_X =	XCoordinate;
   if(!CHistoryView::Manual)
   {
   	GraphData.GRAPH_START_Y = YCoordinate - (3*ONELINEGAP);
   }
   else 
      GraphData.GRAPH_START_Y = YCoordinate ;

	GraphData.GraphWidth=GRAPH_WIDTH*2;
	GraphData.GRAPH_HEIGHT *=2;
	GraphData.GRAPH_HEIGHT-=2;
	GraphData.GRAPH_END_X= GraphData.GRAPH_START_X + GraphData.GraphWidth;	
	GraphData.GRAPH_END_Y = GraphData.GRAPH_START_Y + GraphData.GRAPH_HEIGHT;

   if((HS_CompareGraphNum==1)
      || (HS_CompareGraphNum==2)
      || (HS_CompareGraphNum==3))
   {
      	
         CHistoryView::HSFlag=true;
      	DrawGraphBoundary(pDC);
         GraphData.GRAPH_END_Y = GraphData.GRAPH_START_Y +270;
	      DrawTickMarks(pDC);
         drawgraph(pDC);
	      DrawHLabel(pDC);
         
   }
   else
   {
		

      if((GraphData.GraphTypeID == CHistoryView::Graph1ID) && CHistoryView::GraphSelect)
	   {
		   GraphData.GraphNum=1;
		   DrawGraphBoundary(pDC);		//Draw Graph boundary only once in case of dual graph.
		   drawgraph(pDC);
		   DrawTickMarks(pDC);
		   DrawHLabel(pDC);
		   DrawVLabel(pDC);
		   PrintGraphData(pDC,CHistoryView::Manual);
	   }
	   
      if(GraphData.GraphTypeID== CHistoryView::Graph2ID)
	   {
		   GraphData.GraphNum=2;
		   drawgraph(pDC);
		   DrawGraphBoundary(pDC);
		   DrawVLabel(pDC);
	   }
      
   }
  

	
	GraphData.GRAPH_START_X=TEMP_GRAPH_START_X;
	GraphData.GRAPH_START_Y=TEMP_GRAPH_START_Y;
	GraphData.GRAPH_END_X=TEMP_GRAPH_END_X;
	GraphData.GRAPH_END_Y=TEMP_GRAPH_END_Y;
	GraphData.GraphWidth=TEMP_GRAPH_WIDTH;
	GraphData.GRAPH_HEIGHT+=2;
	GraphData.GRAPH_HEIGHT /=2;
	GraphData.GraphNum=TEMP_GraphNum;
}

void CGraphData::PrintGraphData(CDC *pDC,bool Manual)
{
	AlreadyPrinted=true;
	CString line1[3]={"Trigger (----)   :",        "Amp. Step At :",         "Force Step At    :"};
						
 
	CString line2[3]={"End of Sonics At :" ,        "End of Hold  :"  ,      "End of Weld Seek :"};
							
	CString TimeStr= "Time (sec)";
						
	CRect TempRect=TIMESTRINGRECT;
	int LineGap =GraphData.GRAPH_END_Y-100;
	if(Manual)
		TempRect+=CPoint(0,3*ONELINEGAP);
   if(CHistoryView::extratextinboth == 2)
      TempRect+=CPoint(0,4*ONELINEGAP);

	
   CHistoryView::DrawPrinterText(pDC,TempRect.left,TempRect.bottom,TimeStr);

	float TickT=0;float TickF=0;float TickW=0;float TickH=0;float TickL=0;
	float TickA=0;
	bool T,A,F,W,H,L;
	A=false;H=false;L=false;
	T=false;F=false;W=false;
	char buf[10]="   ";
	CRect rect;
	/*printing GraphData.tick values*/
	CString StrOff = "Off";
						
	CString AlarmStr = "Alarm";
		 
	if(GraphData.TickData[1]!=0xFFFF)
	{	
		TempRect=TICKASTRRECT;
       // LineGap =GraphData.GRAPH_END_Y-100;
		if(Manual)
			TempRect+=CPoint(0,3*ONELINEGAP);
      if(CHistoryView::extratextinboth == 2)
         TempRect+=CPoint(0,4*ONELINEGAP);

		CRect TempValueRect=TICKAVALUERECT;
		if(Manual)
				TempValueRect+=CPoint(0,3*ONELINEGAP);
      if(CHistoryView::extratextinboth == 2)
         TempValueRect+=CPoint(0,4*ONELINEGAP);
		CHistoryView::DrawPrinterText(pDC,TempRect.left,TempRect.bottom,line1[1]);

      if(GraphData.TickData[1] == 0xFFFE)
		{
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,StrOff);
		}
		else if(GraphData.TickData[1] == 0xFFFD)
		{
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,AlarmStr);
		}
		else
		{
		
			char buffer[10];
			sprintf(buffer,"%5.3f",((float)GraphData.TickData[1]/TICK_PRESCALE));
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,buffer);
		}  
	}

	if(GraphData.TickData[0] !=0xFFFF)
	{
		TempRect=TICKTSTRRECT;
		if(Manual)
			TempRect+=CPoint(0,3*ONELINEGAP);
      if(CHistoryView::extratextinboth == 2)
         TempRect+=CPoint(0,4*ONELINEGAP);

		CRect TempValueRect=TICKTVALUERECT;
		if(Manual)
				TempValueRect+=CPoint(0,3*ONELINEGAP);
      if(CHistoryView::extratextinboth == 2)
         TempValueRect+=CPoint(0,4*ONELINEGAP);

		CHistoryView::DrawPrinterText(pDC,TempRect.left,TempRect.bottom,line1[0]);
		if(GraphData.TickData[0] == 0xFFFE)
		{
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,StrOff);
		}
		else if(GraphData.TickData[0] == 0xFFFD)
		{
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,AlarmStr);
		}
		else
		{
		
			char buffer[10];
			sprintf(buffer,"%5.3f",((float)GraphData.TickData[0]/TICK_PRESCALE));
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,buffer);
		}
	}

	if(GraphData.TickData[2] !=0xFFFF)
	{
		TempRect=TICKFSTRRECT;
     // LineGap =GraphData.GRAPH_END_Y-100;
		if(Manual)
			TempRect+=CPoint(0,3*ONELINEGAP);
      if(CHistoryView::extratextinboth == 2)
         TempRect+=CPoint(0,4*ONELINEGAP);

		CRect TempValueRect=TICKFVALUERECT;
		if(Manual)
				TempValueRect+=CPoint(0,3*ONELINEGAP);
      if(CHistoryView::extratextinboth == 2)
         TempValueRect+=CPoint(0,4*ONELINEGAP);

		CHistoryView::DrawPrinterText(pDC,TempRect.left,TempRect.bottom,line1[2]);
		if(GraphData.TickData[2] == 0xFFFE)
		{
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,StrOff);
		}
		else if(GraphData.TickData[2] == 0xFFFD)
		{
   		CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,AlarmStr);
		}
		else
		{
		
			char buffer[10];
			sprintf(buffer,"%5.3f",((float)GraphData.TickData[2]/TICK_PRESCALE));
   		CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,buffer);
		}
	}

	if(GraphData.TickData[3] !=0xFFFF)
	{
		TempRect=TICKWSTRRECT;
	if(Manual)
			TempRect+=CPoint(0,3*ONELINEGAP);
      if(CHistoryView::extratextinboth == 2)
         TempRect+=CPoint(0,4*ONELINEGAP);

		CRect TempValueRect=TICKWVALUERECT;
		if(Manual)
				TempValueRect+=CPoint(0,3*ONELINEGAP);
      if(CHistoryView::extratextinboth == 2)
         TempValueRect+=CPoint(0,4*ONELINEGAP);
		CHistoryView::DrawPrinterText(pDC,TempRect.left,TempRect.bottom,line2[0]);

      if(GraphData.TickData[3] == 0xFFFE)
		{
   		CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,StrOff);
		}
		else if(GraphData.TickData[3] ==0xFFFD)
		{
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,AlarmStr);
		}
		else
		{
			char buffer[10];
			sprintf(buffer,"%5.3f",((float)GraphData.TickData[3]/TICK_PRESCALE));
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,buffer);
		}
	}

	if(GraphData.TickData[4] !=0xFFFF)
	{
		TempRect=TICKHSTRRECT;
		if(Manual)
			TempRect+=CPoint(0,3*ONELINEGAP);
      if(CHistoryView::extratextinboth == 2)
         TempRect+=CPoint(0,4*ONELINEGAP);

		CRect TempValueRect=TICKHVALUERECT;
		if(Manual)
				TempValueRect+=CPoint(0,3*ONELINEGAP);
      if(CHistoryView::extratextinboth == 2)
         TempValueRect+=CPoint(0,4*ONELINEGAP);;

			char buffer[10];
		CHistoryView::DrawPrinterText(pDC,TempRect.left,TempRect.bottom,line2[1]);
		if(GraphData.TickData[4] == 0xFFFE)
		{
			pDC->ExtTextOut(TempValueRect.left ,(TempValueRect.bottom ),ETO_OPAQUE   ,NULL, StrOff,NULL);
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,StrOff);
		}
		else if(GraphData.TickData[4] == 0xFFFD)
		{
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,AlarmStr);
		}
		else
		{
		
			sprintf(buffer,"%5.3f",((float)GraphData.TickData[4]/TICK_PRESCALE));
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,buffer);
		}
	}

	if(GraphData.TickData[5] !=0xFFFF)
	{
		TempRect=TICKLSTRRECT;
	   if(Manual)
			TempRect+=CPoint(0,3*ONELINEGAP);
      if(CHistoryView::extratextinboth == 2)
         TempRect+=CPoint(0,4*ONELINEGAP);

		CRect TempValueRect=TICKLVALUERECT;
		if(Manual)
				TempValueRect+=CPoint(0,3*ONELINEGAP);
      if(CHistoryView::extratextinboth == 2)
         TempValueRect+=CPoint(0,4*ONELINEGAP);
		CHistoryView::DrawPrinterText(pDC,TempRect.left,TempRect.bottom,line2[2]);
		if(GraphData.TickData[5] == 0xFFFE)
		{
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,StrOff);
		}
		else if(GraphData.TickData[5] == 0xFFFD)
		{
			pDC->ExtTextOut(TempValueRect.left ,(TempValueRect.bottom  ),ETO_OPAQUE   ,NULL, AlarmStr,NULL);
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,AlarmStr);
		}
		else
		{
			
			char buffer[10];
			sprintf(buffer,"%5.3f",((float)GraphData.TickData[5]/TICK_PRESCALE));
			pDC->ExtTextOut(TempValueRect.left ,(TempValueRect.bottom  ),ETO_OPAQUE   ,NULL, buffer,NULL);	
			CHistoryView::DrawPrinterText(pDC,TempValueRect.left,TempValueRect.bottom,buffer);
		}
	}
	

}

bool CGraphData::PrintGraphManualStr(CDC *pDC,int Type, bool ExtraText,int YCoordinate)
{
	CString ForceString[2]={
	"Set Force values may not be reached due to short weld times, force steps",
	 "near the start or finish of the weld or starting ramp of the system."};
    CString AmpString[2]={
	 "Set Amp. values may not be reached due to short weld times, amplitude steps",
		 "near the start or finish of the weld or starting ramp of the system."};

	if(Type==AMPLITUDEGRAPH)
	{
		
		int XCord =PRINTGRAPHSTARTXCORD;
		for(int i=0;i<2;i++)
		{
			YCoordinate+=ONELINEGAP;
			CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate,AmpString[i]);
		}
		return true;
	}
	if(Type==FORCEGRAPH)
	{
		int XCord =PRINTGRAPHSTARTXCORD;
		for(int i=0;i<2;i++)
		{
			YCoordinate+=ONELINEGAP;
			CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate,ForceString[i] );
		}
		return true;
	}
	return false;
}
