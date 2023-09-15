/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/USBFolder.cpp_v   1.12   12 Nov 2008 16:02:08   nhahmed  $ */
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
 1.0		10/14/05	BWadia		Added Initial Version
 1.1		10/24/05	BWadia		Edited MouseClick() to make Presets folder
 1.2		12/07/05	BWadia		Modified for Tracker issue 4005,4016,3978.
 1.3		12/20/05	BWadia		Modified PrepareUSBHistoryList() for new format of USB Data
 1.4		09/18/06	BSahu		   Modified For Title.
 1.5		02/07/07	BSahu		   Modified GetDiaplayName() For Asian Language date Format.
 1.6     06/11/07 BSahu       Modified Str_NoValid String for translation.
 1.7     06/28/07 PDwivedi    Modified Str_NoValid String for Japanese translation.
 1.8     08/01/08 PDwivedi    Reoving All Local Strings.
 1.9     08/08/08 PDwivedi    Final Code Clean up.
 1.10    09/12/08 PDwivedi    Added changes for Tracker issues of round 2 testing for version LangTestJ.
 1.11    09/24/08 PDwivedi    Added changes for USb GraphMenu.
 1.12    11/12/08 PDwivedi    Added changes for SBC Fatal Error in function PrepareUSBHistoryList.
*/
 // USBFolder.cpp: implementation of the CUSBFolder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SBC.h"
#include "USBFolder.h"
#include "VgaTitle.h"
#include "VgaBottomMenu.h"
#include "WeldingHistory.h"
#include "HistoryGraphs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUSBFolder::CUSBFolder(CString FileName,CString FilePath,int EnumID,int Function_Id)
{
	Name=FileName;
	Path=FilePath;
	text=FileName;
	LastFolderPath=Path;
   TitleID=EnumID;
   Fun_Id=Function_Id;
}
CString CUSBFolder::ThirdHierTitle;
CString CUSBFolder::SecondHierTitle;
CString CUSBFolder::PreviousFileName;
CString CUSBFolder::LastFilePath;
CString CUSBFolder::LastFolderPath;
CString CUSBFolder::HistoryGraphPath;

CUSBFolder::~CUSBFolder()
{

}

/*****************************************************************************/
/*                                                                           */  
/*  This function Draws a USB Folder type object When any USB Folder type    */
/*  object is found in menu/submenu item list for current page.              */
/*****************************************************************************/
void CUSBFolder::Draw(CDC *pDC)
{
 	int ButtonColour=CChildView::Button_Color;
	DrawRect(pDC, ButtonColour, rect);
	Draw_Pressed_Released_Button(pDC);
	DrawText(pDC, SmallFont, CChildView::TextColor, rect, DisplayName,true);
}

/*************************************************************************************/
/*                                                                                   */
/* This function is called when any USB Folder type object is clicked by the user    */
/* The function checks the hierarchay level of the folder and prepares new menu		 */
/* accordingly The menu items   are stored and displayed as new menu                 */
/*************************************************************************************/
bool CUSBFolder::MouseClick(const CPoint &p, CChildView *view)
{
   if(!CChildView::ISUSBPresent)
	{
      CVgaMenu * menu;
      if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
		{
         theApp.menuName=CVgaBottomMenu::mainMenuID;
         theApp.MenuPointer=menu;
         CChildView::thisPtr->ModifyObjectList(menu); 
      }
		view->Invalidate();
		return true;
	}
	 
	CString TempStr=DisplayName;

	if(Fun_Id==FOLDERHIERARCHYTWO)
			ThirdHierTitle=TempStr;
	if(Fun_Id<FOLDERHIERARCHYTHREE)
	{
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		CString argv=Path;
		CString DirSpec;  
		DirSpec=argv+_T("\\*");
		hFind = FindFirstFile(DirSpec, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) 
		{
			return true;
		} 
		else 
		{
			if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&(view->ValidFolderName(FindFileData.cFileName,Fun_Id+1)))
			{
            FindClose(hFind);
				if(Fun_Id==FOLDERHIERARCHYTWO)
						PreviousFileName=DisplayName.SpanExcluding(_T("-"));
				if(Fun_Id==FOLDERHIERARCHYONE)
					SecondHierTitle=TempStr;
				
				view->menupointers.AddTail(theApp.MenuPointer);
            view->menusname.AddTail(theApp.menuName);
            view->menus.AddTail(1);
			   view->PrepareUSBList(Path,Fun_Id+1,TitleID);
				view->Invalidate();
				return true;
			}
			while (FindNextFile(hFind, &FindFileData) != 0) 
			{
 				if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&(view->ValidFolderName(FindFileData.cFileName,Fun_Id+1)))
				{
					FindClose(hFind);
					if(Fun_Id==FOLDERHIERARCHYTWO)
						PreviousFileName=DisplayName.SpanExcluding(_T("-"));
						if(Fun_Id==FOLDERHIERARCHYONE)
					SecondHierTitle=TempStr;

					view->menupointers.AddTail(theApp.MenuPointer);
               view->menusname.AddTail(theApp.menuName);
               view->menus.AddTail(1);
					view->PrepareUSBList(Path,Fun_Id+1,TitleID);
					
					view->Invalidate();
					return true;
				}
			}
		}
	}
	else if(Fun_Id == USBPRESETFOLDER)
	{
		CChildView::LastUSBPresetFolder = Path +"\\Presets";
      theApp.menuName=view->menusname.RemoveTail();
      page_no=view->menus.RemoveTail();
      theApp.MenuPointer=view->menupointers.RemoveTail();
      view->ModifyObjectList(theApp.MenuPointer); 
      view->Invalidate();
	}
	else
	{
      CVgaMenu *menu;
      if (theApp.menus.Lookup(CChildView::thisPtr->USBGraphMenu, menu))
		{
          view->menupointers.AddTail(theApp.MenuPointer);
          view->menusname.AddTail(theApp.menuName);
          view->menus.AddTail(1);
          theApp.menuName = CChildView::thisPtr->USBGraphMenu;
          theApp.MenuPointer = menu;
      }
      /* here show history screen*/
      CChildView::thisPtr->EnableUSBGraph=true;
		PrepareUSBHistoryList(Path,view);
   }
	return true;
}

/********************************************************************************************/
/* This function is used to prepare history list. the function checks for the file			*/
/*	WeldData.log in the path passed as argument. If file is found then it reads the file	*/
/*	and prepares the list																	*/
/********************************************************************************************/
bool CUSBFolder::PrepareUSBHistoryList(CString Path,CChildView *view)
{
   while(CWeldingHistory::thisHisPtr->USBWeldHistoryList.GetCount()>0)
	{
		CHistoryData *obj1 = CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveHead();//delete
		free(obj1);
	}
   while(CWeldingHistory::thisHisPtr->WeldHistoryList.GetCount()>0)
	      delete CWeldingHistory::thisHisPtr->WeldHistoryList.RemoveHead();
 
   CVgaMenu *menu=theApp.MenuPointer;
	LastFilePath=Path;
	HistoryGraphPath=Path;
	int x=0;
	while(x!=1)
	{
		if(LastFilePath.Right(1)==("\\"))
		x++;
		LastFilePath.Delete(LastFilePath.GetLength()-1,1);
	}
	CHistoryGraphs::HistoryDataPath=Path;
	Path=Path+"\\WeldData.log";
	CFile f;
	CFileException e;
	
	if( !f.Open( Path, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
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
		if(f.GetLength()==0)
		{
         POSITION pos = menu->items.GetHeadPosition();
         CVgaMenuItem *object= 0;
         int count=0;
         while (pos)
         {
            object= menu->items.GetNext(pos);
            if((object->GetType()==CVgaMenu::VGAMsgScrnObject))
            {
		         count++;
               if(count==2)
               {
                  CMsgScreen *ptr=(CMsgScreen *)object;
                  view->ShowMessageScreen(object->text);
                  break;
               }
               
            }
         }
		                     
			f.Close();
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->PrepareUSBList(CUSBFolder::LastFilePath,FOLDERHIERARCHYTHREE,TitleID);
         CChildView::thisPtr->Invalidate();
			return false;
		}
		
		int ObjectSize = sizeof(int)+ 4*sizeof(char)+ sizeof(CHistoryData());
      POSITION pos1 = menu->items.GetHeadPosition();
      CVgaMenuItem *Object= 0;
      int count=0;
      while (pos1)
      {
         Object= menu->items.GetNext(pos1);
         if((Object->GetType()==CVgaMenu::VGAMsgScrnObject))
         {
		      count++;
            if(count==1)
            {
               CMsgScreen *ptr=(CMsgScreen *)Object;
               view->ShowMessageScreen(Object->text);
               break;
            }
            
         }
      }
		f.SeekToBegin();
		
	   unsigned int NoOfBytesRead=0;
      CVgaMenuItem *ScreenObj=0;
		POSITION pos = menu->items.GetHeadPosition();
		while(pos)
		{
			ScreenObj = menu->items.GetNext(pos);
			if(ScreenObj->GetType()==CVgaMenu::VGAHISTORYOBJECT)
				break;
		}
		CWeldingHistory * HistoryObj =(CWeldingHistory *)ScreenObj;
		HistoryObj->TotalCycle=0;
      if(HistoryObj->Parameter_ID>0)
    	   delete [](HistoryObj->Parameter_ID);

		CHistoryData* object; 
		int  size= sizeof(CHistoryData());
		bool FirstObject = true;
		bool OldUnits;
		bool USBMetric;

		bool newformat = false, PowerWattsFormat = false, AmpMicronsFormat = false;

		//Read first two bytes, if valid value then we have new format, if not then we have the old format
		int amp = 0, power = 0;
		NoOfBytesRead += f.Read(&amp, sizeof(int));
		NoOfBytesRead += f.Read(&power, sizeof(int));
		if (amp == 2000000000 || amp == 1000000001 || power == 2000000000 || power == 1000000001)
			newformat = true;
		//Read only first value of the file and apply that format to all welds
		if (amp == 2000000000)
			AmpMicronsFormat = true;
		else
			AmpMicronsFormat = false;

		if (power == 2000000000)
			PowerWattsFormat = true;
		else
			PowerWattsFormat = false;
		NoOfBytesRead =0;
		f.SeekToBegin();
		while(NoOfBytesRead!=f.GetLength())
		{	
			int ID;
			char Comma;	
			object =new CHistoryData();

			if (newformat == true)
			{
				NoOfBytesRead += f.Read(&amp, sizeof(int));
				NoOfBytesRead += f.Read(&power, sizeof(int));
			}
			NoOfBytesRead+=f.Read(&ID,sizeof(int));
			NoOfBytesRead+=f.Read(&Comma,sizeof(char));
			NoOfBytesRead+=f.Read(&USBMetric,sizeof(bool));

			if(FirstObject)
			{
				FirstObject = false;
				if(USBMetric)
					NoOfBytesRead+=f.Read(&CWeldingHistory::ParameterUnitMetric[0][0],MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR));
				else
					NoOfBytesRead+=f.Read(&CWeldingHistory::ParameterUnitUSCS[0][0],MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR));
				OldUnits=USBMetric;
			}

			if(OldUnits!=USBMetric)
			{
				if(USBMetric)
					NoOfBytesRead+=f.Read(&CWeldingHistory::ParameterUnitMetric[0][0],MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR));
				else
					NoOfBytesRead+=f.Read(&CWeldingHistory::ParameterUnitUSCS[0][0],MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR));
				OldUnits=USBMetric;
			
			}
			NoOfBytesRead+=f.Read(&Comma,sizeof(char));
			NoOfBytesRead+=f.Read(object,size);
			NoOfBytesRead+=f.Read(&Comma,sizeof(char));
			object->Units=USBMetric;
			object->UniqueId=ID;
			HistoryObj->USBWeldHistoryList.AddHead(object);
			HistoryObj->TotalCycle++;
			OldUnits=USBMetric;
		}
		HistoryObj->TotalColoumn=object->TotalColoumn;
		HistoryObj->Parameter_ID=new int[object->TotalColoumn];
		for(int param=0;param<object->TotalColoumn;param++)	//Storing parameters ID.
		HistoryObj->Parameter_ID[param]=object->USBParamIDs[param];
		f.Close();
      view->ModifyObjectList(theApp.MenuPointer); 
      view->Invalidate();
	}
	return true;
}

/********************************************************************************************/	
/*  This function checks the hierarchy level of the USB Folder and creates the string to be	*/
/* displayed. If Hierarchy level is one, it displayes the name as it is.					*/
/* If Level is two it checks for the month in the string and will add appropriate string	*/
/* to get display name.																		*/
/* If hierarchy level is three it then combines the day stringwith its month string to		*/
/* get the display name																		*/
/*********************************************************************************************/
CString CUSBFolder::GetDiaplayName(int HierarchyLevel)
{
 	switch(HierarchyLevel)
	{
		case FOLDERHIERARCHYONE:
		{
			DisplayName=Name;
			break;
		}

		case FOLDERHIERARCHYTWO:
		{
			char Month[3];
			Month[0]= (char)Name.GetAt(5);
			Month[1]=(char)Name.GetAt(6);
			Month[2]='\0';	
			int MONTH = atoi(&Month[0]);
			CString Year = Name.Left(4);
			if(CChildView::Language_Index>Asian_Language_Start)
				Year =Year+" "+CChildView::thisPtr->AllMonthStrings[0]/*Year_String[CChildView::Language_Index]*/;
			switch(MONTH)
			{
				case JAN:
					DisplayName=CChildView::thisPtr->AllMonthStrings[JAN] /*Str_Jan[CChildView::Language_Index] */+ "-"+Year+">";
				break;

				case FEB:
					DisplayName= CChildView::thisPtr->AllMonthStrings[FEB]/*Str_Feb[CChildView::Language_Index]*/ + "-"+Year+">";
				break;
			
				case MAR:
					DisplayName= CChildView::thisPtr->AllMonthStrings[MAR] /*Str_March[CChildView::Language_Index]*/ + "-"+Year+">";
				break;
			
				case APR:
					DisplayName= CChildView::thisPtr->AllMonthStrings[APR]/*Str_April[CChildView::Language_Index]*/ + "-"+Year+">";
				break;
			
				case MAY:
					DisplayName= CChildView::thisPtr->AllMonthStrings[MAY]/*Str_May[CChildView::Language_Index]*/ + "-"+Year+">";
				break;
			
				case JUN:
					DisplayName= CChildView::thisPtr->AllMonthStrings[JUN]/*Str_June[CChildView::Language_Index]*/ + "-"+Year+">";
				break;
			
				case JUL:
					DisplayName= CChildView::thisPtr->AllMonthStrings[JUL]/*Str_July[CChildView::Language_Index]*/ + "-"+Year+">";
				break;
			
				case AUG:
					DisplayName= CChildView::thisPtr->AllMonthStrings[AUG]/*Str_Aug[CChildView::Language_Index]*/ + "-"+Year+">";
				break;
			
				case SEP:
					DisplayName= CChildView::thisPtr->AllMonthStrings[SEP]/*Str_Sept[CChildView::Language_Index]*/ + "-"+Year+">";
				break;
			
				case OCT:
					DisplayName= CChildView::thisPtr->AllMonthStrings[OCT]/*Str_Oct[CChildView::Language_Index] */+ "-"+Year+">";
				break;
			
				case NOV:
					DisplayName= CChildView::thisPtr->AllMonthStrings[NOV]/*Str_Nov[CChildView::Language_Index]*/ + "-"+Year+">";
				break;
			
				case DEC:
					DisplayName= CChildView::thisPtr->AllMonthStrings[DEC]/*Str_Dec[CChildView::Language_Index]*/ + "-"+Year+">";
				
				break;
			}
			break;
		}
		
		case FOLDERHIERARCHYTHREE:
		{
			if(CChildView::Language_Index>Asian_Language_Start)
				DisplayName= PreviousFileName + " " + Name+ " "+ CChildView::thisPtr->AllMonthStrings[DEC+1]/*Day_String[CChildView::Language_Index]*/;
			else
				DisplayName= PreviousFileName + " " + Name;
			break;
		}
	
		default:
		{
			DisplayName=Name;
			return DisplayName;
			break;
		}
	}return DisplayName;
}


/****************************************************************************************/
/* This function is used to make new files if the files are not created or if Weld		*/
/*data file is found corrupted															*/
/****************************************************************************************/
void CUSBFolder::ClearAllFiles()
{
	CFile f;
	CFileException e;

	CString Path = HistoryGraphPath+"\\";
	CString FileName="PowerGraph.log";
	CString GraphPath=	Path+FileName;
	f.Remove(GraphPath);

	FileName="ColDistGraph.log";
	GraphPath=	Path+FileName;
	f.Remove(GraphPath);
	
	
	FileName="VelocityGraph.log";
	GraphPath=	Path+FileName;
	f.Remove(GraphPath);
	
	FileName="ForceGraph.log";
	GraphPath=	Path+FileName;
	f.Remove(GraphPath);
	

	
	FileName="AmpGraph.log";
	GraphPath=	Path+FileName;
	f.Remove(GraphPath);
	
	FileName="FreqGraph.log";
	GraphPath=	Path+FileName;
	f.Remove(GraphPath);
}

