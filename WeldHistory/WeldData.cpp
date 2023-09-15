// WeldData.cpp: implementation of the CWeldData class.
//
//////////////////////////////////////////////////////////////////////
/*
Revision #		Date		Author			Description
----------		--------	----------		-------------------------------------
1.0				04/24/06	LAM				Initial Version.
1.1				05/10/07	BSahu			Modified Code to Add View HosrnScan Graphs.
1.2				10/22/07	BSahu			Modified Code to Add Printing Feature.
1.3				10/25/07	BSahu		    Modified Code to Fix Weld Cycle over lap issue.
1.4				10/29/07	BSahu		    Modified Code to Modifie WeldHistory printout data
1.5				11/02/07	BSahu		    Modified Code To Fix weld data Print Out Issue.
1.6				11/02/07    BSahu           Modified Code To Fix Graph data Print Out Issue.
1.7				11/05/07    BSahu			Modified Code To print Total cycle time on Weld data Print Out.
*/
#include "stdafx.h"
#include "History.h"
#include "WeldData.h"
#include "NoOfWeld.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction											//
//////////////////////////////////////////////////////////////////////

CWeldData::CWeldData()
{
	InitilizeAllValues();
}

CWeldData::~CWeldData()
{

}
/*************************************************************/
/*This function draws the welddata in screen with			 */
/*prerequisite rows and coloumns.							 */
/*************************************************************/
void CWeldData::Draw(CDC *pDC, int ObjectNo)
{
	
	pDC->SetTextColor(CHistoryView::Color_Array[TextColour]);

	for (int MLength=CHistoryView::LeftMostParameter,j=1;MLength< CHistoryView::LeftMostParameter+4 ;j++, MLength++)
	{  		
		CString a=ConvertToTCHAR(&USBAllParamValues[0][0], MAXPARAMVALUELENGTH);
		pDC->ExtTextOut(HISTORY_TBL_START_X,(HISTORY_TBL_START_Y+(LINE_GAP*3)+(ObjectNo*LINE_GAP)),ETO_CLIPPED  ,NULL, a,NULL);
		
		CString a1=ConvertToTCHAR(&USBAllParamValues[MLength][0], MAXPARAMVALUELENGTH);
		pDC->ExtTextOut(ParamRectWidth*j,(HISTORY_TBL_START_Y+(LINE_GAP*3)+(ObjectNo*LINE_GAP)),NULL  ,NULL, a1,NULL);
		
	}	

	
	pDC->SetTextColor(COLORBLACK);
}
/*************************************************************/
/*This function initialises all values to be drwan in		 */
/*welddata screen.											 */
/*************************************************************/
void CWeldData::InitilizeAllValues()
{
	for(int len=0;len<MAXDATETIMELENGTH;len++)
	{
		USBTimeStr[len]=0;
		USBDateStr[len]=0;
	}
	for(int len=0;len<MAXMODEPRESETLENGTH;len++)
		USBMode_PresetString[len]=0;
	for(int len=0;len<MAXPARAMVALUES;len++)
	{
		USBParamIDs[len]=0;
		for(int i=0;i<MAXPARAMVALUELENGTH;i++)
			USBAllParamValues[len][i]=0;
		
	}
	
//	HistoryContinued=false;
}
/*********************************************************/
/*This function converts Short to Cstring charecter	     */
/*********************************************************/
CString CWeldData::ConvertToTCHAR(short *ptr,int Length)
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
			return Str;
		else
		{
			Str+=u.a[0];
		}
		ptr++;
	}
	return Str;
}

int  CWeldData::PrintHistoryWeldData(CDC *pDC,CPrintInfo* pInfo, int YCord, bool DrawUnits, bool DrawPresetString, bool PrintParamvalues)
{	
CString TimeString="Time ";
	CString DateString="Date ";
   int ArrParamNum[MAXPARAMVALUES];
   memset(ArrParamNum,0,sizeof(ArrParamNum));
   for (int Index=1,h=0 ; Index < MAXPARAMVALUES ;Index++)
   {
      bool contFlag=false;
      if(h >= 12)
         break;
       int	ParamNum=USBParamIDs[Index];
      if(( ParamNum != 13) && (ParamNum != 23))
      {
		   if(ParamNum == 11)
			 ParamNum = 15;
		   else if(ParamNum == 12)
			 ParamNum = 21;
		   else if(ParamNum == 14)
			 ParamNum = 24;
		  for (int Index1=0 ; Index1 <= h ;Index1++)
		  {
			 if(ArrParamNum[Index1] == ParamNum )
				contFlag = true;

		  }
		  if(!contFlag)
			 ArrParamNum[h++] = ParamNum;
		  if(h == 10)
			 ArrParamNum[h++] = 23;
	  }

   }
   /*Printing Weld History.*/
	{
      
		int XCord=PRINTWELDSTARTXCORD ;
		int YCoordinate = YCord+ONEWELDLINEGAP; 
		char TempArray[10];
		CString Temp= _itoa(NoOfWeld::EditBoxvalue,TempArray,10);
		CString CycleNumString=" ";
		int TotalCyclesPrinted=0;
		if(DrawUnits)
		{	
			CString Last50_Str="** ------------------------------------- Last " + Temp +" Weld History Data ---------------------------------------- **";
			pDC->ExtTextOut(PRINTWELDSTARTXCORD,-PRINTWELDSTARTYCORD,ETO_OPAQUE,NULL, Last50_Str,NULL);	
			/*drawing cycle count, date and time strings*/
			CString Str = CHistoryView::WelddataHeadings[1];
			CString ParameterString1 = Str.SpanExcluding(_T(" "));
			CString ParameterString2 = Str.Right(Str.GetLength()-(1+ParameterString1.GetLength()));
			pDC->ExtTextOut(XCord-70,-(PRINTWELDSTARTYCORD+ONEWELDLINEGAP),ETO_OPAQUE,NULL, ParameterString1,NULL);	
			pDC->ExtTextOut(XCord,-(PRINTWELDSTARTYCORD+ONEWELDLINEGAP+ONEHEADINGGAP),ETO_OPAQUE,NULL, ParameterString2,NULL);	
			if(PrintParamvalues)
			{
			CString ParamValue =ConvertToTCHAR(&USBAllParamValues[0][0], MAXPARAMVALUELENGTH);
			CycleNumString=ParamValue;
			pDC->ExtTextOut(XCord-70,-(YCoordinate+4*ONEWELDLINEGAP),ETO_OPAQUE,NULL, ParamValue,NULL);	
			}
         XCord+=PARAMWIDTH ;
			XCord+=220;
			pDC->ExtTextOut(XCord-ABSGAP,-(PRINTWELDSTARTYCORD+ONEWELDLINEGAP+ONEWELDLINEGAP),ETO_OPAQUE,NULL, TimeString,NULL);	
			
			if(PrintParamvalues)
			{
			YCoordinate+=ONEWELDLINEGAP;
			CString TimeStringValue=ConvertToTCHAR(&USBTimeStr[0], MAXPARAMVALUELENGTH);
			pDC->ExtTextOut(XCord-ABSGAP,-(YCoordinate+3*ONEWELDLINEGAP),ETO_OPAQUE,NULL, TimeStringValue,NULL);	
			}
			XCord+=PARAMWIDTH ;
        
			pDC->ExtTextOut(XCord-ABSGAP,-(PRINTWELDSTARTYCORD+ONEWELDLINEGAP+ONEWELDLINEGAP),ETO_OPAQUE,NULL, DateString,NULL);	
			if(Units)
				pDC->ExtTextOut(XCord-ABSGAP,-(PRINTWELDSTARTYCORD+ONEWELDLINEGAP+TWOHEADINGGAP),ETO_OPAQUE,NULL, "(d/m/y)",NULL);	
			else
				pDC->ExtTextOut(XCord-ABSGAP,-(PRINTWELDSTARTYCORD+ONEWELDLINEGAP+TWOHEADINGGAP),ETO_OPAQUE,NULL, "(m/d/y)",NULL);	
			if(PrintParamvalues)
			{
			YCoordinate+=ONEWELDLINEGAP;
			CString DateStringValue=ConvertToTCHAR(&USBDateStr[0], MAXPARAMVALUELENGTH);
			pDC->ExtTextOut(XCord-ABSGAP,-(YCoordinate+2*ONEWELDLINEGAP),ETO_OPAQUE,NULL, DateStringValue,NULL);	
			YCoordinate-=ONEWELDLINEGAP;
			}
			XCord+=PARAMWIDTH ;

         	
			for (int MLength=1,j=1 ; MLength < 12 ;MLength++,j++)
			{
			//	YCoordinate-=ONEWELDLINEGAP;
				CString b;
            
				pDC->SetBkMode(TRANSPARENT);
            int	ParamNum=ArrParamNum[MLength-1];
				if(DrawUnits)
				{
				
             int tempMLength;
             for(int k=0; k<MAXPARAMVALUES;k++)
             {
                if(USBParamIDs[k] == ParamNum)
                   tempMLength = k;

             }
				CString str=CHistoryView::WelddataHeadings[ParamNum];
				CString ParameterString1 = str.SpanExcluding(_T(" "));
				CString ParameterString2 = str.Right(str.GetLength()-(1+ParameterString1.GetLength()));
				pDC->ExtTextOut(XCord-ABSGAP,-(PRINTWELDSTARTYCORD+ONEWELDLINEGAP),ETO_OPAQUE   ,NULL, ParameterString1,NULL);
				pDC->ExtTextOut(XCord-ABSGAP,-(PRINTWELDSTARTYCORD+ONEWELDLINEGAP+ONEWELDLINEGAP),ETO_OPAQUE   ,NULL, ParameterString2,NULL);
				
				CString b;
				if(Units)
				b = CHistoryView::Parameter_Units_Metric[ParamNum];
					else
				b = CHistoryView::Parameter_Units_USCS[ParamNum];

				if (CHistoryView::AmpMicronsFormat && CHistoryView::Parameter_Formats[ParamNum]==AMPLITUDE)
					b=CHistoryView::Parameter_Units_Formats[ParamNum];
				if (CHistoryView::PowerWattsFormat && CHistoryView::Parameter_Formats[ParamNum]==WATTS)
					b=CHistoryView::Parameter_Units_Formats[ParamNum];
				
				pDC->ExtTextOut(XCord-ABSGAP,-(PRINTWELDSTARTYCORD+ONEWELDLINEGAP+TWOHEADINGGAP),ETO_OPAQUE   ,NULL, b,NULL);
				
				if(PrintParamvalues)
				{
				
				YCoordinate+=ONEWELDLINEGAP;
            CString ParamValue;
            
               ParamValue=ConvertToTCHAR(&USBAllParamValues[tempMLength][0], MAXPARAMVALUELENGTH);
				if(ParamValue.Find(_T("---"))>=0)
						ParamValue="n/a";
				pDC->ExtTextOut(XCord-ABSGAP,-(YCoordinate+2*ONEWELDLINEGAP),ETO_OPAQUE   ,NULL, ParamValue,NULL);
				YCoordinate-=ONEWELDLINEGAP;
				}
            XCord+=(PARAMWIDTH-30) ;
				}
				
				if(DrawPresetString)
				{
					DrawPresetString=false;
					CString ModeStringValue=ConvertToTCHAR(&USBMode_PresetString[0], MAXMODEPRESETLENGTH);
					CHistoryView::ModePresetString=ModeStringValue;
					pDC->ExtTextOut(XCord-4*PARAMWIDTH-TWOLINEGAP,-(YCoordinate+2*ONEWELDLINEGAP),ETO_OPAQUE   ,NULL, ModeStringValue,NULL);
				}
			}
			PrintParamvalues=false;
			TotalCyclesPrinted++;
			YCoordinate=YCoordinate+3*ONEWELDLINEGAP;
		}
		
	if(PrintParamvalues)
	 {
//	for(int i=StartPos;i<3;i++)
	{	
		int XCord=PRINTWELDSTARTXCORD;
		CString ModeStringValue=ConvertToTCHAR(&USBMode_PresetString[0], MAXMODEPRESETLENGTH);
		CString ModeStringValuePrevious=CHistoryView::ModePresetString;
		if((ModeStringValue).Compare(ModeStringValuePrevious))
		{
		   pDC->ExtTextOut(PRINTWELDSTARTXCORD,-(YCoordinate),ETO_OPAQUE   ,NULL, ModeStringValue,NULL);
		   YCoordinate+=ONEWELDLINEGAP;
		   CHistoryView::ModePresetString=ModeStringValue;
		}
						
		CString ParamValue =ConvertToTCHAR(&USBAllParamValues[TotalCyclesPrinted][0], MAXPARAMVALUELENGTH);
		pDC->ExtTextOut(XCord-70,-(YCoordinate),ETO_OPAQUE,NULL, ParamValue,NULL);
		XCord+=PARAMWIDTH ;
		XCord+=220;
		
		CString TimeStringValue=ConvertToTCHAR(&USBTimeStr[TotalCyclesPrinted], MAXPARAMVALUELENGTH);
		pDC->ExtTextOut(XCord-ABSGAP,-(YCoordinate),ETO_OPAQUE,NULL, TimeStringValue,NULL);
		XCord+=PARAMWIDTH ;

		CString DateStringValue=ConvertToTCHAR(&USBDateStr[TotalCyclesPrinted], MAXPARAMVALUELENGTH);
		pDC->ExtTextOut(XCord-ABSGAP,-(YCoordinate),ETO_OPAQUE,NULL, DateStringValue,NULL);
		XCord+=PARAMWIDTH ;

		for (int MLength=1,j=1 ; MLength < 12 ;MLength++,j++)
		{
			if(XCord+PARAMWIDTH>MAXXCOORDINATE)
				break;
          int	ParamNum=ArrParamNum[MLength-1];
          int tempMLength;
             for(int k=0; k<MAXPARAMVALUES;k++)
             {
                if(USBParamIDs[k] == ParamNum)
                   tempMLength = k;

             }
			
               ParamValue=ConvertToTCHAR(&USBAllParamValues[tempMLength][0], MAXPARAMVALUELENGTH);
				
			if(ParamValue.Find(_T("---"))>=0)
					ParamValue="n/a";
			pDC->ExtTextOut(XCord-ABSGAP,-(YCoordinate),ETO_OPAQUE   ,NULL, ParamValue,NULL);
			XCord+=(PARAMWIDTH-30 );
		}
	}
	}
	return YCoordinate;
  }
}

int  CWeldData::Print(CDC *pDC)
{	
   int VelocityOn=0;
	CString CycleNumber="Cycle# = ";
							 
	int Position=0;				
	CString DateString="  Date          : ";
						

	CString TimeString="  Time          : ";
	int XCord=PRINTGRAPHSTARTXCORD ;
	int YCoordinate = ONELINEGAP;
	
	/*Print Mode Preset String.*/
	CString ModeStringValue=ConvertToTCHAR(&USBMode_PresetString[0], MAXMODEPRESETLENGTH);
	CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate,ModeStringValue );
	CString CycleNumber_str,Date_str,Time_str;
	YCoordinate+=ONELINEGAP;
	/* Prepare Cycle number,Date and Time strings to be printed.*/
	CString ParamValue =ConvertToTCHAR(&USBAllParamValues[0][0], MAXPARAMVALUELENGTH);
	CycleNumber_str=CycleNumber+ParamValue;
   CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate,CycleNumber_str );
	
	YCoordinate+=ONELINEGAP;		
	/*Print Cycle Number,Date and Time string.*/
	CString TimeStringValue=ConvertToTCHAR(&USBTimeStr[0], MAXPARAMVALUELENGTH);
	Time_str=TimeString+TimeStringValue;
	CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate,Time_str );
		
			
	YCoordinate+=ONELINEGAP;
	CString DateStringValue=ConvertToTCHAR(&USBDateStr[0], MAXPARAMVALUELENGTH);
	Date_str=DateString+DateStringValue;
	CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate,Date_str );
	
	
	YCoordinate+=ONELINEGAP;		
	/*Printing weld data headings and weld data.*/
	for (int MLength=1,j=1 ; MLength < 15 ;MLength++,j++)
	{
	//	YCoordinate-=ONEWELDLINEGAP;
		CString b;
		pDC->SetBkMode(TRANSPARENT);
	//	if(Units)
		{
		int	ParamNum=USBParamIDs[MLength];
      
      CString str=CHistoryView::WelddataHeadings[ParamNum];
		str.TrimLeft();
		str.TrimRight();
		CString ParameterString2;
		/*Break heading string in to two strings.*/
		CString ParameterString1 = str.SpanExcluding(_T(" "));
		if(ParameterString1.GetLength()<str.GetLength())
			ParameterString2 = str.Right(str.GetLength()-(1+ParameterString1.GetLength()));
		else
		{
			ParameterString1 = str.SpanExcluding(_T("."));
			ParameterString2 = str.Right(str.GetLength()-(1+ParameterString1.GetLength()));
		}
		CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate,ParameterString1 );
		CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate+ONELINEGAP,ParameterString2 );
		
		if(Units)
			CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate+TWOLINEGAP,CHistoryView::Parameter_Units_Metric[ParamNum] );
		else
			CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate+TWOLINEGAP,CHistoryView::Parameter_Units_USCS[ParamNum] );
		YCoordinate+=THREELINEGAP;
		CString ParamValue=ConvertToTCHAR(&USBAllParamValues[MLength][0], MAXPARAMVALUELENGTH);
		if(ParamValue.Find(_T("---"))>=0)
				ParamValue="n/a";
		CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate+ONELINEGAP,ParamValue );
		YCoordinate-=THREELINEGAP;
		XCord+=GRAPHPARAMWIDTH ;
		
		}
		if(XCord==1175)
		{
			Position=MLength+1;
			YCoordinate+=6*ONELINEGAP;
			XCord=PRINTGRAPHSTARTXCORD ;
			break;
		}
	}
	for (int MLength=Position; MLength < 16 ;MLength++)
	{
	//	YCoordinate-=ONEWELDLINEGAP;
		CString b;
		pDC->SetBkMode(TRANSPARENT);
	//	if(Units)
		{
		int	ParamNum=USBParamIDs[MLength];
		  if(MLength == 15)
			 ParamNum = 23;
      
		  int tempMLength = 0;
			tempMLength = MLength;
		   for(int k=0; k<MAXPARAMVALUES;k++)
		   {
			  if(USBParamIDs[k] == ParamNum)
				 tempMLength = k;

		   }

      
		CString str=CHistoryView::WelddataHeadings[ParamNum];
		str.TrimLeft();
		str.TrimRight();
		CString ParameterString2;
		/*Break heading string in to two strings.*/
		CString ParameterString1 = str.SpanExcluding(_T(" "));
		if(ParameterString1.GetLength()<str.GetLength())
			ParameterString2 = str.Right(str.GetLength()-(1+ParameterString1.GetLength()));
		else
		{
			ParameterString1 = str.SpanExcluding(_T("."));
			ParameterString2 = str.Right(str.GetLength()-(1+ParameterString1.GetLength()));
		}
		CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate,ParameterString1 );
		CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate+ONELINEGAP,ParameterString2 );
		
		
		if(Units)
			CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate+TWOLINEGAP,CHistoryView::Parameter_Units_Metric[ParamNum]);
		else
			CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate+TWOLINEGAP,CHistoryView::Parameter_Units_USCS[ParamNum]);
		YCoordinate+=THREELINEGAP;
		CString ParamValue=ConvertToTCHAR(&USBAllParamValues[tempMLength][0], MAXPARAMVALUELENGTH);
		if(ParamValue.Find(_T("---"))>=0)
				ParamValue="n/a";
		CHistoryView::DrawPrinterText(pDC,XCord,YCoordinate+ONELINEGAP,ParamValue );
		YCoordinate-=THREELINEGAP;
		XCord+=GRAPHPARAMWIDTH ;
		}
	}
	YCoordinate+=4*ONELINEGAP;
	return YCoordinate;
	
}
