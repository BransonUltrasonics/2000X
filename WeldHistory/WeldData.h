// WeldData.h: interface for the CWeldData class.
//
//////////////////////////////////////////////////////////////////////

/*
Revision #		Date		Author			Description
----------		--------	----------		-------------------------------------
1.0				04/24/06	LAM				Initial Version.
1.1				10/22/07	BSahu			Modified To Enable Printing Feature.

*/
#if !defined(AFX_WELDDATA_H__712236A6_1DAB_4358_A35B_475F6F80DD26__INCLUDED_)
#define AFX_WELDDATA_H__712236A6_1DAB_4358_A35B_475F6F80DD26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MAXPARAMVALUES		 25
#define MAXDATETIMELENGTH	 10
#define MAXMODEPRESETLENGTH  50
#define MAXPARAMUNITLENGTH	 6
#define MAXPARAMVALUELENGTH	 9

#define PRINTWELDSTARTXCORD			300
#define PRINTGRAPHSTARTXCORD		75
#define PRINTGRAPHSTARTYCORD		500
#define	MAXXCOORDINATE				50000
#define ONEWELDLINEGAP				270
#define ABSGAP			            400
#define ONEHEADINGGAP				17
#define PARAMWIDTH					840
#define PARAMWIDTHX					400
#define TWOHEADINGGAP				500
#define ONELINEGAP					25
#define TWOLINEGAP					50
#define THREELINEGAP				75

#define GRAPHPARAMWIDTH				100
#define PARAMETERSTARTYCORD			250
#define NCALARM						0
#define OLALARM						32
#define EQALARM						64
#define CMALARM						96
#define CAALARM						128
#define WAALARM						160 
#define PRALARM						192
#define PSALARM						224
#define MODEPRESETSTRINGRECT	CRect(100,100,250,125)
#include "HistoryView.h"
class CHistoryView;
class CWeldData 
{
public:
	short USBTimeStr[MAXDATETIMELENGTH];
	short USBDateStr[MAXDATETIMELENGTH];
	short USBParamIDs[MAXPARAMVALUES];
	short USBAllParamValues[MAXPARAMVALUES][MAXPARAMVALUELENGTH];
	short USBMode_PresetString[MAXMODEPRESETLENGTH];
	short Lang_Index;
	short TextColour;
	int UniqueId;
	short TotalColoumn;
	bool Units;
	void InitilizeAllValues();
	int PrintHistoryWeldData(CDC *pDC, CPrintInfo* pInfo,int YCord, bool DrawUnits, bool DrawPresetString, bool PrintParamvalues);
	CWeldData();
	virtual ~CWeldData();
	void Draw(CDC *pDC, int ObjectNo);
	CString ConvertToTCHAR(short* Ptr,int Length);
	int Print(CDC *pDC);
	
//virtual void Serialize(CArchive &ar);
protected:
//	DECLARE_SERIAL(CWeldData)
};

#endif // !defined(AFX_WELDDATA_H__712236A6_1DAB_4358_A35B_475F6F80DD26__INCLUDED_)



