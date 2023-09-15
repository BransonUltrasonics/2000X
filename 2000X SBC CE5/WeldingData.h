// WeldingData.h: interface for the CWeldingData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WELDINGDATA_H__F6B130DD_D3C9_43CB_A4FF_E893D0BAE7AA__INCLUDED_)
#define AFX_WELDINGDATA_H__F6B130DD_D3C9_43CB_A4FF_E893D0BAE7AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXPARAMVALUES 25
#define MODEPRESETSTRINGRECT	CRect(100,100,250,125)
#define CYCLENUMSTRRECT			CRect(125,150,125,150)
#define TIMESTRRECT				CRect(125,175,125,175)
#define DATESTRRECT				CRect(125,200,125,200)
#define TIMEMODE	1
#define ENERGYMODE	2
#define PKPOWERMODE	3
#define COLLAPSEMODE	4
#define ABSOLUTEMODE	5	
#define GRDDETECTMODE	6
#define CONTINUOUSMODE	7
#define PARAMETERWIDTH 88
#define XCORDINC 85
#define RUN_RESULT_TBL_START_X  8
#define RUN_RESULT_TBL_START_Y  50
#define HISTORY_TBL_START_X  20
#define HISTORY_TBL_START_Y  30


#define NCALARM        0
#define OLALARM        32
#define EQALARM        64
#define CMALARM        96
#define CAALARM        128
#define WAALARM        160 
#define PRALARM        192
#define PSALARM        224

#include "VgaMenuItem.h"

#include "ChildView.h"

class CXmlElement;

class CWeldingData : public CVgaMenuItem  
{
public:
   static bool ValueFlag;
   int HistoryObjectNum;
   int PrintAlarms(int i,CDC *pDC,int YCord,CChildView *view,bool HistoryAlarms,bool GraphAlarms,CString CycleNumString);
   int GetAlarms(int  UIAlarmField, int IOffset,CDC *pDC,int YCord,CChildView *view,bool HistoryAlarms,bool GraphAlarms,CString CycleNumString);
   int *NoCycleAlarms,*OverloadAlarms,*EquipmentFailureAlarms,
   *CycleModifiedAlarms,*CalibrateAlarms,*Warnings,*RejectBitResult,*SuspectBitResult;
   void StoreAlarmInformation(unsigned char * &data, int & length,int i);
   int ReceivedUniversalCount;
   CWeldingData(int NoOfCycles, unsigned char * &data, int & length,bool SelectData);
   CString* ColumnHeading;
   int UniqueId;

   int TotalColoumn;
   void DrawHistoryData(CDC *pDC,int LeftMostParameter, int LineNo);
   CWeldingData(int TotalColoumn, unsigned char * &data, int & length);
   bool HistoryContinued;
   int PrintHistoryYCord;
   int TotalCyclesPrinted;
   int TotalCycles;
   CString GetMode_PresetString(unsigned char * &data,int & length);
   CString GetWeldDataString(unsigned char * &data,int & length);
   CWeldingData( unsigned char * &data,int & length,bool PrintData);
   int PresetNumber;
   bool Units;
   int PrintWeldData(CDC *pDC, int StartYCord, bool DrawUnits, bool DrawPresetString, int HISTORYPAGENO,CChildView *view);
   void PrintHistoryWeldData(CDC *pDC, int YCord, bool DrawUnits, bool DrawPresetString, int HISTORYPAGENO,CChildView *view);
   CString *AllParamValues;
   int *AllParamIDs;
   //CString CycleCountStr;
   void Print(CDC *pDC,CChildView *view);
   CString* Time_String;
   CString* Date_String;
   CString* Mode_PresetString;
   static int CycleCount;
   CWeldingData(unsigned char * &data, int & length);
   CWeldingData(unsigned char * &data, int & length,int TotalColoumn);
   virtual ~CWeldingData();
   virtual void Draw(CDC *pDC);
   int Parameter_ID[5];

protected:
   int Lang_Index;

   virtual bool MouseClick(const CPoint &p, CChildView *view);
public:
 
   void StoreDate_Time(unsigned char *&data, int &length, CString* Date ,CString* Time);
   int TextColour;
   CString * Parameter_Value;
   int ParamCount;


};

#endif // !defined(AFX_WELDINGDATA_H__F6B130DD_D3C9_43CB_A4FF_E893D0BAE7AA__INCLUDED_)
