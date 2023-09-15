/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/HistoryData.cpp_v   1.8   08 Aug 2008 17:22:50   pdwivedi  $ */
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
 1.1		12/07/05	BWadia		Modified for Tracker issue 4030,4026.
 1.2		12/20/05	BWadia		Changed the Data Format for USB Weld Data.
 1.3		01/13/06	BWadia		Dummy Check In.
 1.4		01/13/06	BWadia		Modified for tracker issue 3957,3960.
 1.5		02/07/07	BSahu		   Modified StoreDate_Time( ) For Japanese Date Format.
 1.6		02/07/07	BSahu		   Modified StoreDate_Time( ) After Review For Japanese Date Format.
 1.7     08/01/08 PDwivedi    Removed All Local Strings.
 1.8     08/08/08 PDwivedi    Final Code Clean up.
									
*/
// HistoryData.cpp: implementation of the CHistoryData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SBC.h"
#include "HistoryData.h"
#include "WeldingHistory.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHistoryData::CHistoryData()
{}

/************************************************************************/
/* The conctructor is used to make history data object wen the data		*/
/* is read from USB														*/
/************************************************************************/
CHistoryData::CHistoryData(unsigned char * &data, int & length)
{	
	InitilizeAllValues();
	Lang_Index=CChildView::Language_Index;
	/*Type and Co_Ordinates for VGARunScreen Object	*/
	//data+=9;		
//	length-=9;
   //printf("\n CHistoryData HistoryData");
	TotalColoumn = *data++;
	length--;
    
 //  printf("\n TotalColoumn=%d",TotalColoumn);
	/* Storing Total Coloumn Ids.*/

	for(int j =0;j<TotalColoumn;j++)
	{
		USBParamIDs[j]=*data++;
		length--;
	}
	int ReceivedUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	int TotalCycles=*data++;length--;/* must be one */
  // printf("\n TotalCycles HistoryData=%d",TotalCycles);

	Units=CChildView::metric;
	/*Storing data of all cycles.*/

	//if(TotalCycles==1)
	for(int i=0;i<TotalCycles;i++)
	{
		TextColour = *data++;	//Storing text colour for each cycle.
		length--;
		
		/*Storing Weld Data.*/
		for(j =0;j<TotalColoumn;j++)
		{
			CString result =GetWeldDataString(data, length);	
			CopyToUSB(result,(TCHAR*)&USBAllParamValues[j][0]);
		}
			
		
		/*Storing Mode Preset String for each cycle.*/
		CString Mode_PresetString =GetMode_PresetString(data, length);
		
		/*Storing Date and Time String for each cycle.*/
		
		StoreDate_Time(data,length);
		data+=33;		
		length-=33;
		CopyToUSB(Mode_PresetString,(TCHAR*)&USBMode_PresetString[0]);
		
	}

	CString Unit;
	for(j =0;j<TotalColoumn;j++)
	{
		for(int k=0;k<CChildView::TotalTextHeading;k++)
		{
			if(USBParamIDs[j]==CChildView::Parameter_ID[k])
			{
				if(Units)
					Unit =CChildView::Parameter_Units_Metric[k];
				else
					Unit =CChildView::Parameter_Units_USCS[k];

				for(int i=0;i<Unit.GetLength();i++)
				{
					if(Units)
					{
						CWeldingHistory::ParameterUnitMetric[j][i] = Unit.GetAt(i);
						CWeldingHistory::ParameterUnitMetric[j][i+1]='\0';
					}
					else
					{
						CWeldingHistory::ParameterUnitUSCS[j][i] = Unit.GetAt(i);
						CWeldingHistory::ParameterUnitUSCS[j][i+1]='\0';
					}
				}
			}
		}
		
	
	}

	
}

CHistoryData::~CHistoryData()
{

}

/*****************************************************************************/
/* this function is used to get weld data string form the data comming from	 */
/* welder. This is required because Weld data comes in syngle bye in all	 */
/* languages																 */
/*****************************************************************************/
CString CHistoryData::GetWeldDataString(unsigned char * &data,int & length)
{
	CString result = "";
	int count= *data++;
	int strlen;
	strlen=count;
	for (int i = 0; i < strlen; i++)
	{
		union {
			unsigned char ch[2];
			TCHAR character;
			}u;
		u.ch[1]=NULL;
		u.ch[0]= *data++;
		result += (u.character);
	}
	length -= count+1;
	result.TrimRight();
	result.TrimLeft();
	
	return result;
}

/******************************************************************/
/* This function is used to create Date and Time string using the */
/* information comming from 332.								  */
/******************************************************************/	
void CHistoryData::StoreDate_Time(unsigned char *&data, int &length)
{
	/*Storing Date.*/
	CString Date;
	CString Time;
	char TempArray[MAXDATETIMELENGTH];
	
	int Temp =*data++;length--;
	CString TempDay =	_itoa(Temp,TempArray,10);
	if(TempDay.GetLength() ==1)
		TempDay = "0"+TempDay;
	if(CChildView::Language_Index <= Asian_Language_Start)
	TempDay +="/";

	Temp =*data++;length--;
	CString TempMonth = 	_itoa(Temp,TempArray,10);
	if(TempMonth.GetLength() ==1)
		TempMonth = "0"+TempMonth;
	TempMonth +="/";
	
	Temp =*data++;length--;
	CString TempYear = 	_itoa(Temp,TempArray,10);
	if(TempYear.GetLength() ==1)
		TempYear = "0"+TempYear;

	if(CChildView::Language_Index>Asian_Language_Start)
	Date ="20"+TempYear+"/"+TempMonth+TempDay;
	else if(Units)
	Date =TempDay+TempMonth+TempYear;
	else
	Date =TempMonth+TempDay+TempYear;
	
	
	/* Storing Time.*/
	Temp =*data++;length--;
	CString TempHour = _itoa(Temp,TempArray,10);
	if(TempHour.GetLength() ==1)
		TempHour = "0"+TempHour;
	TempHour +=":";
	Temp =*data++;length--;
	CString TempMinute = _itoa(Temp,TempArray,10);
	if(TempMinute.GetLength() ==1)
		TempMinute = "0"+TempMinute;
	TempMinute +=":";
	Temp =*data++;length--;
	CString TempSecond = _itoa(Temp,TempArray,10);
	if(TempSecond.GetLength() ==1)
		TempSecond = "0"+TempSecond;
	Time =TempHour+TempMinute+TempSecond;
	CopyToUSB(Date,(TCHAR*)&USBDateStr[0]);
	CopyToUSB(Time,(TCHAR*)&USBTimeStr[0]);
}

/****************************************************************/
/* This function is used to create the mode preset screen from	*/
/* mode numer and preset number									*/
/****************************************************************/
CString CHistoryData::GetMode_PresetString(unsigned char * &data,int & length)
{
	/*CString TimeModeStr[] = {
         "Time Mode",
         "Zeit Modus",
         "Modo Tiem",
         "Modal Time",
         "Mode Temps",
         L"\x65f6\x95f4\x6a21\x5f0f\x0",
         L"\x6642\x9593\x6a21\x5f0f\x0",
         L"\x6642\x9593\xff93\xff70\xff84\xff9e\x0",
         L"\xc2dc\xac04\x0020\xbaa8\xb4dc\x0" };

CString EnergyModeStr[] = {
         "Energy Mode",
         "Energie Modus",
         "Modo Energi",
         "Modal Energi",
         "Mode Energie",
         L"\x80fd\x91cf\x6a21\x5f0f\x0",
         L"\x80fd\x91cf\x6a21\x5f0f\x0",
         L"\xff74\xff88\xff99\xff77\xff9e\xff70\xff93\xff70\xff84\xff9e\x0",
         L"\xc5d0\xb108\xc9c0\x0020\xbaa8\xb4dc\x0" };

CString PkPowerModeStr[] = {
         "PeakPower Mode",
         "Sp.Leistung Modus",
         "Modo Pico Poten",
         "Modal Picco Pot.",
         "Mode Pui.-Crete",
         L"\x5cf0\x503c\x529f\x7387\x6a21\x5f0f\x0",
         L"\x529f\x7387\x5cf0\x503c\x6a21\x5f0f\x0",
         L"\xff8b\xff9f\xff70\xff78\xff8a\xff9f\xff9c\xff70\xff93\xff70\xff84\xff9e\x0",
         L"\xcd5c\xb300\x0020\xcd9c\xb825\x0020\xbaa8\xb4dc\x0" };

CString CollapseModeStr[] = {
         "Collapse Mode",
         "Weg relativ Modus",
         "Modo Colapso  ",
         "Modal Collasso",
         "Mode D. Relat",
         L"\x76f8\x5bf9\x6df1\x5ea6\x6a21\x5f0f\x0",
         L"\x5d29\x9677\x8ddd\x96e2\x6a21\x5f0f\x0",
         L"\xff7a\xff97\xff8c\xff9f\xff7d\xff93\xff70\xff84\xff9e\x0",
         L"\xae4a\xc774\x0020\xbaa8\xb4dc\x0" };

CString AbsoluteModeStr[] = {
         "Absolute Mode",
         "Weg absolut Modus",
         "Modo Absoluto ",
         "Modal Assoluta",
         "Mode D.Abs",
         L"\x7edd\x5bf9\x6df1\x5ea6\x6a21\x5f0f\x0",
         L"\x7d55\x5c0d\x8ddd\x96e2\x6a21\x5f0f\x0",
         L"\xff71\xff8c\xff9e\xff7f\xff98\xff6d\xff70\xff84\xff93\xff70\xff84\xff9e\x0",
         L"\xc808\xb300\xac70\xb9ac\x0020\xbaa8\xb4dc\x0" };

CString GroundDetectModeStr[] = {
         "Ground Detect Mode",
         "Metallkont. Modus",
         "Modo Detecc Tierra",
         "Modal Ground Detect",
         "Mode Detec.Masse",
         L"\x63a5\x5730\x4fdd\x62a4\x6a21\x5f0f\x0",
         L"\x63a5\x5730\x5075\x6e2c\x6a21\x5f0f\x0",
         L"\xff78\xff9e\xff97\xff9d\xff84\xff9e\xff83\xff9e\xff68\xff83\xff78\xff84\xff93\xff70\xff84\xff9e\x0",
         L"\xc9c0\xba74\x020\xac10\xc9c0\x020\xbaa8\xb4dc\x0" };

CString ContinuousModeStr[] = {
         "Continuous Mode",
         "Kontinuier Modus",
         "Modo Continuo",
         "Modal Continua",
         "Mode Continu",
         L"\x8d85\x58f0\x6301\x7eed\x65f6\x95f4\x6a21\x5f0f\x0",
         L"\x6301\x7e8c\x767c\x632f\x6a21\x5f0f\x0",
         L"\x9023\x7d9a\x767a\x632f\xff93\xff70\xff84\xff9e\x0",
         L"\xc5f0\xc18d\x020\xbaa8\xb4dc\x0" };
CString PresetStr[] = {
         "Preset#",
         "Parameter#",
         "Presel#",
         "Preset#",
         "Preset#",
         L"\x9884\x8bbe\x7f6e\x003d\x005b\x0023\x0",
         L"\x9810\x8a2d\x0023\x0",
         L"\xff8c\xff9f\xff98\xff7e\xff6f\xff84\x0023\x0",
         L"\xc6a9\xcc29\xc870\xac74\x0023\x0" };

	int LangIndex = Lang_Index;
	/*Getting Mode * /
	int Mode_Num =*data++;
	length--;

	/*Getting Preset Number.* /
	int Preset_Num = *data++;
	length--;

	/*Getting PresetName.* /
	CString PresetName = GetWeldDataString(data, length);
	
	/*Preparing Mode Preset String.* /
	CString FinalString;
 switch(Mode_Num)
   {  /* Get the weld mode string.  * /
      case TIMEMODE:
         FinalString = TimeModeStr[LangIndex];
         break;
         
      case ENERGYMODE:
         FinalString = EnergyModeStr[LangIndex];
         break;
         
      case PKPOWERMODE:
         FinalString = PkPowerModeStr[LangIndex];
         break;
         
      case COLLAPSEMODE:
         FinalString = CollapseModeStr[LangIndex];
         break;
         
      case ABSOLUTEMODE:
         FinalString = AbsoluteModeStr[LangIndex];
         break;
         
      case GRDDETECTMODE:
         FinalString = GroundDetectModeStr[LangIndex];
         break;
         
      case CONTINUOUSMODE:
         FinalString = ContinuousModeStr[LangIndex];
         break;
         
      default:
         FinalString = TimeModeStr[LangIndex];
         break;   
   }
	FinalString +=", "+PresetStr[LangIndex];
	char pr[5];
	sprintf(pr,"%d",Preset_Num);
	FinalString +=pr;
	FinalString +=" - " +PresetName;

	return FinalString;*/
   int LangIndex = Lang_Index;
	/*Getting Mode */
	int Mode_Num =*data++;
	length--;

	/*Getting Preset Number.*/
	int Preset_Num = *data++;
	length--;

	/*Getting PresetName.*/
	CString PresetName = GetWeldDataString(data,length);
	
   /*Preparing Mode Preset String.*/

 /////////////////////////////////////////
	CString str1 = CChildView::thisPtr->PString[0];
	CString str2 = CChildView::thisPtr->PString[1];
	CString str3 = CChildView::thisPtr->PString[2];
	CString str4 = CChildView::thisPtr->PString[3];
	CString str5 = CChildView::thisPtr->PString[4];
	CString str6 = CChildView::thisPtr->PString[5];
	CString str7 = CChildView::thisPtr->PString[6];
	CString str8 = CChildView::thisPtr->PString[7];

	CString FinalString;
	
	switch(Mode_Num)
    {  /* Get the weld mode string.  */
      case TIMEMODE:
		 FinalString = str1;
		 break;
         
      case ENERGYMODE:
          FinalString = str2;
		  break;
         
      case PKPOWERMODE:
		  FinalString = str3;
		  break;
         
      case COLLAPSEMODE:
			FinalString = str4;
			break;
         
      case ABSOLUTEMODE:
			FinalString = str5;
			break;
         
      case GRDDETECTMODE:
			FinalString = str6;
			break;
         
      case CONTINUOUSMODE:
			FinalString = str7;
			break;
         
      default:
			FinalString = str1;
			break;   
	}

	FinalString +=", "+ str8;
	char pr[5];
	sprintf(pr,"%d",Preset_Num);
	FinalString +=pr;
	FinalString +=" - " +PresetName;

/*	for(int i=0;i<FinalString.GetLength();i++)
		printf("%c",FinalString.GetAt(i));
	printf("\n");*/

	FinalString.ReleaseBuffer();

	return FinalString;
}

/************************************************************/
/* This function is used to convert CString type object		*/
/* to char array. this is done so that data could be written*/ 
/* in USB													*/
/************************************************************/
void CHistoryData::CopyToUSB(CString Str1, TCHAR *Str2)
{
	int length = Str1.GetLength();
	for(int i=0;i<length;i++)
		*(Str2+i)= Str1.GetAt(i);
	*(Str2+length)='\0';
}

/************************************************************************************/
/* This function is used to draw one USB History weld data. Line Number is			*/	
/* passed to tell the line number of the history data on screen. Left most parameter*/
/* tells the weld data left most parameter on the screen							*/
/************************************************************************************/	
void CHistoryData::DrawUSBHistory(CDC *pDC,int LeftMostParameter, int LineNo)
{
	CRect ParamValueRect;
	/*Drawing parameter Values.*/
	int ColumnNo=0;
	ParamValueRect =CRect((HISTORY_TBL_START_X + ColumnNo * ParamRect_Width),
							  (HISTORY_TBL_START_Y+LINE_GAP*(LineNo+3)),
							  (HISTORY_TBL_START_X + (ColumnNo+1) * ParamRect_Width),
							  (HISTORY_TBL_START_Y+LINE_GAP*(LineNo+4)));
	
	CVgaMenuItem::DrawText(pDC, SmallFont, TextColour, ParamValueRect, USBAllParamValues[0],false);
		ColumnNo++;

	for (int Index = LeftMostParameter; Index <(LeftMostParameter+4) ; Index++)
	{
		ParamValueRect =CRect((HISTORY_TBL_START_X + ColumnNo * ParamRect_Width),
							  (HISTORY_TBL_START_Y+LINE_GAP*(LineNo+3)),
							  (HISTORY_TBL_START_X + (ColumnNo+1) * ParamRect_Width),
							  (HISTORY_TBL_START_Y+LINE_GAP*(LineNo+4)));

		CVgaMenuItem::DrawText(pDC, SmallFont, TextColour, ParamValueRect, USBAllParamValues[Index],false);
		ColumnNo++;
	}
}

/****************************************************************************/
/* This function is called when user clicks on History data. Nothing has	*/
/* to be done here.															*/
/****************************************************************************/
bool CHistoryData::MouseClick(const CPoint &p, CChildView *view)
{
return true;
}

/****************************************************************************/
/* History data is drawn in function Draw USBHistory(), so no use of this 	*/
/* function. Definition is requires because it is derived from an abstract	*/
/*  class.																	*/
/****************************************************************************/
void CHistoryData::Draw(CDC *pDC)
{
}

/********************************************************************************/
/* The following function is used to Initilize all the Parameters. This is done */
/* so that no garbage value is written in USB									*/
/********************************************************************************/
void CHistoryData::InitilizeAllValues()
{
	for(int len=0;len<MAXDATETIMELENGTH;len++)
	{
		USBTimeStr[len]='\0';
		USBDateStr[len]='\0';
	}
	for(len=0;len<MAXMODEPRESETLENGTH;len++)
		USBMode_PresetString[len]='\0';
	for(len=0;len<MAXPARAMVALUES;len++)
	{
		USBParamIDs[len]='\0';
		for(int i=0;i<MAXPARAMVALUELENGTH;i++)
			USBAllParamValues[len][i]='\0';
	/*	for(int j=0;j<MAXPARAMUNITLENGTH;j++)
			ParameterUnit[len][j]='\0';*/
	}
}

CHistoryData::CHistoryData(int Difference,unsigned char * &data, int & length)
{	
	InitilizeAllValues();
	Lang_Index=CChildView::Language_Index;
	/*Type and Co_Ordinates for VGARunScreen Object	*/
//	data+=9;		
//	length-=9;

	TotalColoumn = *data++;
	length--;

	/* Storing Total Coloumn Ids.*/

	for(int j =0;j<TotalColoumn;j++)
	{
		USBParamIDs[j]=*data++;
		length--;
	}
int ReceivedUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	int TotalCycles=*data++;length--;/* must be one */

	Units=CChildView::metric;
	/*Storing data of all cycles.*/

	//if(TotalCycles==1)
	for(int i=0;i<Difference;i++)
	{
		TextColour = *data++;	//Storing text colour for each cycle.
		length--;
		
		/*Storing Weld Data.*/
		for(j =0;j<TotalColoumn;j++)
		{
			CString result =GetWeldDataString(data, length);	
			CopyToUSB(result,(TCHAR*)&USBAllParamValues[j][0]);
		}
			
		
		/*Storing Mode Preset String for each cycle.*/
		CString Mode_PresetString =GetMode_PresetString(data, length);
		
		/*Storing Date and Time String for each cycle.*/
		
		StoreDate_Time(data,length);
		data+=33;		
		length-=33;
		CopyToUSB(Mode_PresetString,(TCHAR*)&USBMode_PresetString[0]);
		
	}

	CString Unit;
	for(j =0;j<TotalColoumn;j++)
	{
		for(int k=0;k<CChildView::TotalTextHeading;k++)
		{
			if(USBParamIDs[j]==CChildView::Parameter_ID[k])
			{
				if(Units)
					Unit =CChildView::Parameter_Units_Metric[k];
				else
					Unit =CChildView::Parameter_Units_USCS[k];

				for(int i=0;i<Unit.GetLength();i++)
				{
					if(Units)
					{
						CWeldingHistory::ParameterUnitMetric[j][i] = Unit.GetAt(i);
						CWeldingHistory::ParameterUnitMetric[j][i+1]='\0';
					}
					else
					{
						CWeldingHistory::ParameterUnitUSCS[j][i] = Unit.GetAt(i);
						CWeldingHistory::ParameterUnitUSCS[j][i+1]='\0';
					}
					
				}
			}
		}
		
	
	}

	
}
