// Table.cpp: implementation of the CTable class.
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
  1.1       08/01/08    PDwivedi  Remove All Local Strings.
  1.2       08/08/08    PDwivedi  Final Code Clean up.
  1.3       09/12/08    PDwivedi  Added changes for Tracker issues of round 2 testing for version LangTestJ.
*/

#include "stdafx.h"
#include "SBC.h"
#include "Table.h"
#include "XmlElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int CTable::HighLightString=-1;
//extern CList<CString,CString> tempList;
//extern POSITION Temp_pos;
extern CList<CString,CString> tempScanGraphDataList;
extern POSITION ScanGraphsDataTemp_pos;

CTable::CTable(CXmlElement * e)
{
   rect = CRect(0, 0, 0, 0);
	RectShow=1;
	for(int I=0;I<3;I++)
	for(int J=0;J<9;J++)
		CompareData[J][I]="  ";

	//Storing Co-ordinates for text.//
   X1_CoOrdinate = _ttoi(e->GetAttribute("X1"));
	Y1_CoOrdinate = _ttoi(e->GetAttribute("Y1"));
	X2_CoOrdinate = _ttoi(e->GetAttribute("X2"));
	Y2_CoOrdinate = _ttoi(e->GetAttribute("Y2"));
	
   //Storing text.//
	
	RowHeading[0] = CVgaMenuItem ::LinearSearch(e->GetAttribute("Row1ID"));
   RowHeading[1] = CVgaMenuItem ::LinearSearch(e->GetAttribute("Row2ID"));
   RowHeading[2] = CVgaMenuItem ::LinearSearch(e->GetAttribute("Row3ID"));
   RowHeading[3] = CVgaMenuItem ::LinearSearch(e->GetAttribute("Row4ID"));
   RowHeading[4] = CVgaMenuItem ::LinearSearch(e->GetAttribute("Row5ID"));
   RowHeading[5] = CVgaMenuItem ::LinearSearch(e->GetAttribute("Row6ID"));
   RowHeading[6] = CVgaMenuItem ::LinearSearch(e->GetAttribute("Row7ID"));
   RowHeading[7] = CVgaMenuItem ::LinearSearch(e->GetAttribute("Row8ID"));
   RowHeading[8] = CVgaMenuItem ::LinearSearch(e->GetAttribute("Row9ID"));
	ColoumnHeading[0] = CVgaMenuItem ::LinearSearch(e->GetAttribute("Col1ID"));
   ColoumnHeading[1] = CVgaMenuItem ::LinearSearch(e->GetAttribute("Col2ID"));
   ColoumnHeading[2] = CVgaMenuItem ::LinearSearch(e->GetAttribute("Col3ID"));
   
   POSITION pos = e->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * element = e->children.GetNext(pos);
		CString tag = element->GetTag();
		if (tag == "condition")
      {
		   AddCondition(element);
      }
		else
			ASSERT(FALSE);
	}
}

CTable::CTable()
{
}


CTable::~CTable()
{

}


/*************************************************************************************/
/*                                                                                   */
/*  This function Draws a CVGATable object When any CVGATable type object is found in  */
/*  menu/submenu item list for current page .										 */
/*																					 */
/*************************************************************************************/
void CTable::Draw(CDC *pDC)
{
	/*Drawing Coloumn Headings.*/
	int X1 = X1_CoOrdinate+130;
	int X2 = X1_CoOrdinate +260;
	for (int i=0;i<3;i++)
	{
		DrawText(pDC, SmallFont,Black, CRect(X1,Y1_CoOrdinate,X2,Y1_CoOrdinate),ColoumnHeading[i],false);//Draw textColoumnHeading[i]
		X1 =X2;
		X2 = X1+130;
	}
	GetHornScanData_for_CompareData(pDC,false);
	/*Drawing Row Headings.*/
	int Y1 = Y1_CoOrdinate+20;
	int Y2 = Y1+30;
	for(int j=0;j<9;j++)
	{
		DrawText(pDC, SmallFont,Black, CRect(X1_CoOrdinate,Y1,X1_CoOrdinate+100,Y2),RowHeading[j],false);//Draw text//RowHeading[j]
		Y1 =Y2;
		Y2 = Y1+30;
	}


}

bool CTable::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}

void CTable::GetHornScanData_for_CompareData(CDC *pDC,bool IsPrint)
{
	CVgaMenu * menu;
   int TempCount=0;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   POSITION pos1=menu->items.GetHeadPosition();
   CString HS_ID1,HS_ID2,HS_ID3;
	CTypedPtrList<CPtrList, CVgaDrawGraph *> HSGraphDataList;
	bool HS1_Present=false;
	bool HS2_Present=false;
	bool HS3_Present=false;
	int HighLight[3]={-1,-1,-1};
	int TempLangIndex =CChildView::Language_Index;
	CFile f1;
	CFileException e1;
	TCHAR* pFileName1;
	#ifndef _WIN32_WCE
	pFileName1 = _T("c:\\HornScanA.txt");
	#else
	pFileName1 = _T("Disk\\HornScanA.txt");
	#endif
	
	if( !f1.Open( pFileName1, CFile::modeReadWrite , &e1 ) )
	{
		#ifdef _DEBUG
		if(e1.m_cause==CFileException::generic)
			TRACE("\n !! GENERIC");
		else if(e1.m_cause==CFileException::badPath   )
			TRACE("\n !! bad path");
		else if(e1.m_cause==CFileException::tooManyOpenFiles    )
			TRACE("\n !! too many files open");
		else if(e1.m_cause==CFileException::fileNotFound )
			TRACE("\n !! file not found");
		else if(e1.m_cause==CFileException::accessDenied       )
			TRACE("\n !! access denied");
		else if(e1.m_cause==CFileException::diskFull      )
			TRACE("\n !! disc full");
		else if(e1.m_cause==CFileException::invalidFile   )
			TRACE("\n !! invalid file");
		afxDump << "File could not be opened " << e1.m_cause << "\n";
		#endif
	}
	else
	{
		unsigned char *Data=new unsigned char[f1.GetLength()];
		unsigned char *Dummy = Data;
		int k =f1.Read(Data,f1.GetLength());
		if(k>20)
		{
			HS1_Present=true;
			int length =f1.GetLength();
			//int temp = (int)*Data++;len--;
			//CChildView::Language_Index =0; 
         HS_ID1 =CVgaMenuItem::GetString(Data,length);
			//CChildView::Language_Index =temp;
			//CVgaDrawGraph *graph =new CVgaDrawGraph(Data,len);
         while ((pos1))
          {
             object= menu->items.GetNext(pos1);
	         // while(length>0)
				 {
                if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(TempCount==1))
                {
                  //CVgaDrawGraph * object = new CVgaDrawGraph(data,length);
                   CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                   
                   //ptr->graph_type=CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH);//(WHICHGRAPH)
                   int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(Data,length,CORDLENGTH);
              //     printf("\n ValueAfterParamID=%d",ValueAfterParamID);
                   
                   if(ValueAfterParamID==ptr->GraphType)
                   {
                  //    printf("\n inside");
                      ptr->GraphData.graph_type=ValueAfterParamID;
                      ptr->GraphData.GraphColour=*Data++;length--;
                      ptr->SetGraphRequestValue(ValueAfterParamID);
                      for(int i=0;i<20;i++)
		                  ptr->GraphData.SystemPressure[i]='\0';
	                   ptr->AlreadyPrinted=false;
	                   ptr->Lang_Index=0;//CChildView::Language_Index;
	                   ptr->No_Graph_String=" ";
                      ptr->GraphCount++;
	                   ptr->GraphData.GraphNum =ptr->GraphCount;
                      ptr->GraphData.DataLength=CVgaMenuItem::Convert_Char_To_Integer(Data,length,CORDLENGTH);
			             for(short len=0;len<(ptr->GraphData.DataLength);len++)
                      {
				            ptr->GraphData.graphdata[len]=(short)*Data++;
				            length--;
			             }
			             ptr->Store_VData_HData(Data,length);
			             ptr->StoreDate_Time(Data,length);
			             ptr->GraphData.GraphColour =2;
			             ptr->HSCompareGraph=true;
			             HSGraphDataList.AddTail(ptr);
		               //	CChildView::Language_Index = TempLangIndex;
			             HighLight[0] =HighLightString;
                   }
                   TempCount++;
                }
                else
                {
                  TempCount++;
                }
					//TRACE(_T(" Remaining length: %d "),length);
					
				 }
          }
			
		}
		delete []Dummy;
		f1.Close();
	}

   pos1=menu->items.GetHeadPosition();
   TempCount=0;
	CFile f;
	CFileException e;
	TCHAR* pFileName;
	#ifndef _WIN32_WCE
	pFileName = _T("c:\\HornScanB.txt");
	#else
	pFileName = _T("Disk\\HornScanB.txt");
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
		unsigned char *Data=new unsigned char[f.GetLength()];
		unsigned char *Dummy = Data;
		int j =f.Read(Data,f.GetLength());
		if(j>20)
		{
			HS2_Present=true;
			int length =f.GetLength();
			//int temp = (int)*Data++;len--;
			//CChildView::Language_Index = 0;
         HS_ID2 = CVgaMenuItem::GetString(Data,length);
			//CChildView::Language_Index =temp ;
			//CVgaDrawGraph *graph1 =new CVgaDrawGraph(Data,len);
         while ((pos1))
          {
             object= menu->items.GetNext(pos1);
	         // while(length>0)
				 {
                if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(TempCount==2))
                {
                  //CVgaDrawGraph * object = new CVgaDrawGraph(data,length);
                   CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                   
                   //ptr->graph_type=CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH);//(WHICHGRAPH)
                   int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(Data,length,CORDLENGTH);
                 //  printf("\n ValueAfterParamID=%d",ValueAfterParamID);
                   
                   if(ValueAfterParamID==ptr->GraphType)
                   {
                  //    printf("\n inside");
                      ptr->GraphData.graph_type=ValueAfterParamID;
                      ptr->GraphData.GraphColour=*Data++;length--;
                      ptr->SetGraphRequestValue(ValueAfterParamID);
                      for(int i=0;i<20;i++)
		                  ptr->GraphData.SystemPressure[i]='\0';
	                   ptr->AlreadyPrinted=false;
	                   ptr->Lang_Index=0;//CChildView::Language_Index;
	                   ptr->No_Graph_String=" ";
                      ptr->GraphCount++;
	                   ptr->GraphData.GraphNum =ptr->GraphCount;
                      ptr->GraphData.DataLength=CVgaMenuItem::Convert_Char_To_Integer(Data,length,CORDLENGTH);
			             for(short len=0;len<(ptr->GraphData.DataLength);len++)
                      {
				            ptr->GraphData.graphdata[len]=(short)*Data++;
				            length--;
			             }
			             ptr->Store_VData_HData(Data,length);
			             ptr->StoreDate_Time(Data,length);
			             ptr->GraphData.GraphColour =3;
			             ptr->HSCompareGraph=true;
			             HSGraphDataList.AddTail(ptr);
		               //	CChildView::Language_Index = TempLangIndex;
			             HighLight[1] =HighLightString;
                   }
                   TempCount++;
                }
                else
                {
                   TempCount++;
                }
					//TRACE(_T(" Remaining length: %d "),length);
					
				 }
          }
		}
		delete []Dummy;
		f.Close();
	}
   pos1=menu->items.GetHeadPosition();
   TempCount=0;
	CFile f2;
	CFileException e2;
	TCHAR* pFileName2;
	#ifndef _WIN32_WCE
	pFileName2 = _T("c:\\HornScanC.txt");
	#else
	pFileName2 = _T("Disk\\HornScanC.txt");
	#endif
	
	if( !f2.Open( pFileName2, CFile::modeReadWrite , &e2 ) )
	{
		#ifdef _DEBUG
		if(e2.m_cause==CFileException::generic)
			TRACE("\n !! GENERIC");
		else if(e2.m_cause==CFileException::badPath   )
			TRACE("\n !! bad path");
		else if(e2.m_cause==CFileException::tooManyOpenFiles    )
			TRACE("\n !! too many files open");
		else if(e2.m_cause==CFileException::fileNotFound )
			TRACE("\n !! file not found");
		else if(e2.m_cause==CFileException::accessDenied       )
			TRACE("\n !! access denied");
		else if(e2.m_cause==CFileException::diskFull      )
			TRACE("\n !! disc full");
		else if(e2.m_cause==CFileException::invalidFile   )
			TRACE("\n !! invalid file");
		afxDump << "File could not be opened " << e2.m_cause << "\n";
		#endif
	}
	else
	{
		unsigned char *Data=new unsigned char[f2.GetLength()];
		unsigned char *Dummy = Data;
		int i =f2.Read(Data,f2.GetLength());
		if(i>20)
		{
			HS3_Present=true;
			int length =f2.GetLength();
		//	int temp = (int)*Data++;len--;
		//	CChildView::Language_Index = 0;
         HS_ID3 = CVgaMenuItem::GetString(Data,length);
		//	CChildView::Language_Index = temp;
			//CVgaDrawGraph *graph2 =new CVgaDrawGraph(Data,len);
         while ((pos1))
          {
             object= menu->items.GetNext(pos1);
	         // while(length>0)
				 {
                if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(TempCount==3))
                {
                  //CVgaDrawGraph * object = new CVgaDrawGraph(data,length);
                   CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                   
                   //ptr->graph_type=CScreenObject::Convert_Char_To_Integer(data,length,CORDLENGTH);//(WHICHGRAPH)
                   int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(Data,length,CORDLENGTH);
                //   printf("\n ValueAfterParamID=%d",ValueAfterParamID);
                   
                   if(ValueAfterParamID==ptr->GraphType)
                   {
                    //  printf("\n inside");
                      ptr->GraphData.graph_type=ValueAfterParamID;
                      ptr->GraphData.GraphColour=*Data++;length--;
                      ptr->SetGraphRequestValue(ValueAfterParamID);
                      for(int i=0;i<20;i++)
		                  ptr->GraphData.SystemPressure[i]='\0';
	                   ptr->AlreadyPrinted=false;
	                   ptr->Lang_Index=0;//CChildView::Language_Index;
	                   ptr->No_Graph_String=" ";
                      ptr->GraphCount++;
	                   ptr->GraphData.GraphNum =ptr->GraphCount;
                      ptr->GraphData.DataLength=CVgaMenuItem::Convert_Char_To_Integer(Data,length,CORDLENGTH);
			             for(short len=0;len<(ptr->GraphData.DataLength);len++)
                      {
				            ptr->GraphData.graphdata[len]=(short)*Data++;
				            length--;
			             }
			             ptr->Store_VData_HData(Data,length);
			             ptr->StoreDate_Time(Data,length);
			             ptr->GraphData.GraphColour =4;
			             ptr->HSCompareGraph=true;
			             HSGraphDataList.AddTail(ptr);
		               //	CChildView::Language_Index = TempLangIndex;
			             HighLight[2] =HighLightString;
                   }
                   TempCount++;
                }
                else
                {
                   TempCount++;
                }
					//TRACE(_T(" Remaining length: %d "),length);
					
				 }
          }
		}
		delete []Dummy;
		f2.Close();
	}
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
			CVgaDrawGraph *graph =HSGraphDataList.GetNext(pos);
			CompareData[q++][j] =graph->TimeString;
			CompareData[q++][j] =  graph->DateString;
			for(int k=0;k<6;k++)
				CompareData[q++][j] = graph->FreqString[k];
		}
		j++;
		
	}
	if(!IsPrint)
	{
	int x = X1_CoOrdinate+130;
	int y=100;
	for(int i=0;i<3;i++)
	{
		
		for(int j =0;j<9;j++)
		{
			if((HighLight[i]+3) == j)
				DrawText(pDC, SmallFont, Blue, CRect(x,y,x+130,y+30),CompareData[j][i],false);
			else
				DrawText(pDC, SmallFont, Black, CRect(x,y,x+130,y+30),CompareData[j][i],false);
			y+=30;
		}
		x+=130;
		y=100;
	}
	}
	while(HSGraphDataList.GetCount())
		 HSGraphDataList.RemoveHead();
}

void CTable::CopyVGATableData(CTable *object)
{	for(int i=0;i<3;i++)
	object->ColoumnHeading[i]=ColoumnHeading[i];

	for(i=0;i<9;i++)
	object->RowHeading[i]=RowHeading[i];

	for(i=0;i<9;i++)
	for(int j =0;j<3;j++)
		object->CompareData[i][j]=CompareData[i][j];

	object->X1_CoOrdinate=X1_CoOrdinate;
	object->X2_CoOrdinate=X2_CoOrdinate;
	object->Y1_CoOrdinate=Y1_CoOrdinate;
	object->Y2_CoOrdinate=Y2_CoOrdinate;
}

void CTable::Print(CDC *pDC, CPoint point)
{//	printf("Inside CTable Print \n");

	CString Str_CmpData=tempScanGraphDataList.GetNext(ScanGraphsDataTemp_pos);
	CString Str_CmpGraph=tempScanGraphDataList.GetNext(ScanGraphsDataTemp_pos);
/*CString Str_CmpData[] = {
         "Compare Data",
         "Vergleiche Daten",
         "Comparar datos",
         "Confronta Dati",
         "Comparer donnees",
         L"\x6570\x636e\x6bd4\x8f83\x0",
         L"\x8cc7\x6599\x6bd4\x8f03\x0",
         L"\xff83\xff9e\xff70\xff80\x6bd4\x8f03\x0",
         L"\xb370\xc774\xd130\x020\xbe44\xad50\x0" };

		 
CString  Str_CmpGraph[] = {
         "Compare Graphs",
         "Vergleiche Graphen",
         "Comparar grficos",
         "Confronta Grafici",
         "Comparer graphes",
         L"\x66f2\x7ebf\x56fe\x6bd4\x8f83\x0",
         L"\x66f2\x7dda\x5716\x6bd4\x8f3\x0",
         L"\xff78\xff9e\xff97\xff8c\x6bd4\x8f03\x0",
         L"\xadf8\xb798\xd54\x020\xbe44\xad50\x0" };*/

	X2_CoOrdinate=(X2_CoOrdinate-X1_CoOrdinate)*2 +point.x;
	Y2_CoOrdinate=(Y2_CoOrdinate-Y1_CoOrdinate)*2 +point.y;
	X1_CoOrdinate= point.x;
	Y1_CoOrdinate=point.y;
	
   CVgaMenuItem::DrawPrinterText(pDC,PrintBigFont,Black, CRect(X1_CoOrdinate,Y1_CoOrdinate-100,X2_CoOrdinate,Y1_CoOrdinate-100),Str_CmpData,true,CChildView::Language_Index);//Dra
   CVgaMenuItem::DrawPrinterText(pDC,PrintBigFont,Black, CRect(X1_CoOrdinate,550,X2_CoOrdinate,550),Str_CmpGraph,true,CChildView::Language_Index);
	/*Drawing Coloumn Headings.*/
	int X1 = X1_CoOrdinate+260;
	int X2 = X1_CoOrdinate +520;
	for (int i=0;i<3;i++)
	{
      CVgaMenuItem::DrawPrinterText(pDC,	PrintSmallFont,Black, CRect(X1,Y1_CoOrdinate-50,X2,Y1_CoOrdinate-50),ColoumnHeading[i],false,CChildView::Language_Index);
		X1 =X2;
		X2 = X1+260;
	}
	int x = X1_CoOrdinate+260;
	int y=Y1_CoOrdinate+10;
	for(i=0;i<3;i++)
	{
		
		for(int j =0;j<9;j++)
		{
         CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black, CRect(x,y,x+260,y+60),CompareData[j][i],false,CChildView::Language_Index);
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
      CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont,Black, CRect(X1_CoOrdinate+50,Y1,X1_CoOrdinate+200,Y1+60),RowHeading[j],false,CChildView::Language_Index);
		
		Y1 = Y1+30;
	}

	CPen penLine;
	CPen *OldPen;
	penLine.CreatePen(PS_SOLID, 2, CChildView::Color_Array[1]);
	OldPen = pDC->SelectObject(&penLine);
	CPoint p1(X1_CoOrdinate+50,Y1_CoOrdinate);
	CPoint p2(X2_CoOrdinate,Y1_CoOrdinate);
	int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
	int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
	p1=CalibPoint(p1, nHorz,nVert);
	p2=CalibPoint(p2, nHorz,nVert);
	pDC->MoveTo(p1);
	pDC->LineTo(p2);
	pDC->SelectObject(OldPen);
	penLine.DeleteObject();

}
