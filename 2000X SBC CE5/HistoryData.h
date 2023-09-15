/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/HistoryData.h_v   1.3   08 Aug 2008 17:22:50   pdwivedi  $ */
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
 1.2		12/20/05	BWadia		Removed Units from HistoryData member variables.
 1.3     08/08/08 PDwivedi    Final Code Clean up.
*/
// HistoryData.h: interface for the CHistoryData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTORYDATA_H__CF9F213E_F74B_4805_9859_31558156CA24__INCLUDED_)
#define AFX_HISTORYDATA_H__CF9F213E_F74B_4805_9859_31558156CA24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChildView.h"
#include "WeldingData.h"
//#include "WeldHistory.h"

#define HISTORY_TBL_START_X  20
#define HISTORY_TBL_START_Y  30

#define MAXDATETIMELENGTH	 10
#define MAXMODEPRESETLENGTH  50
//#define MAXPARAMUNITLENGTH	 6
#define MAXPARAMVALUELENGTH	 9
class CHistoryData  //: public CVfdObject 
{
public:
//	TCHAR ParameterUnit[MAXPARAMVALUES][MAXPARAMUNITLENGTH];
	TCHAR USBTimeStr[MAXDATETIMELENGTH];
	TCHAR USBDateStr[MAXDATETIMELENGTH];
	short USBParamIDs[MAXPARAMVALUES];
	TCHAR USBAllParamValues[MAXPARAMVALUES][MAXPARAMVALUELENGTH];
	TCHAR USBMode_PresetString[MAXMODEPRESETLENGTH];
	short Lang_Index;
	short TextColour;
	int UniqueId;
	short TotalColoumn;
	bool Units;

	void InitilizeAllValues();
	CHistoryData();
	void CopyToUSB(CString Str1, TCHAR* Str2);
	CHistoryData(int Difference,unsigned char * &data, int & length);
	CHistoryData(unsigned char * &data, int & length);
	virtual ~CHistoryData();
	void StoreDate_Time(unsigned char *&data, int &length);
	void DrawUSBHistory(CDC *pDC,int LeftMostParameter, int LineNo);
	CString GetMode_PresetString(unsigned char * &data,int & length);
	CString GetWeldDataString(unsigned char * &data,int & length);
	virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC *pDC);

};

#endif // !defined(AFX_HISTORYDATA_H__CF9F213E_F74B_4805_9859_31558156CA24__INCLUDED_)

