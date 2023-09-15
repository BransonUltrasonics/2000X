/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/PrintText.h_v   1.10   12 Sep 2008 21:34:12   pdwivedi  $ */
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
  1.0       09/16/05	BWadia      Added complete revision header.
  1.1		   10/14/05	BWadia		Added PageNo variable for ViewPreset Screen.
  1.2		   01/13/06	BWadia		Dummy Check In.
  1.3		   01/13/06	BWadia		Modified for tracker issue 3957.
  1.4		   02/07/06	BWadia		Declared PrintGraph Strings
  1.5		   02/14/06	BWadia		Declared PrintGraph Strings
  1.6		   02/22/06	BWadia		Declared Graph Manual Strings
  1.7		   05/04/07	BSahu 		Modified Declaration Of Graph Manual Strings(Tracker 4139).
  1.7.0.1   06/06/08 PDwivedi    Added new constructor.
  1.7.0.2   08/01/08 PDwivedi    Added new Function.
  1.7.0.3   09/12/08 PDwivedi    Added changes for Tracker issues of round 2 testing for version LangTestJ.
 */


// PrintText.h: interface for the PrintText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTTEXT_H__FD6DC23C_E60C_410D_9D30_23A5FF668499__INCLUDED_)
#define AFX_PRINTTEXT_H__FD6DC23C_E60C_410D_9D30_23A5FF668499__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MaxAlarmString	256

#include "ChildView.h"
#define PRINTSPACEPAGE  35
#define PRINTSPACEPAGE2  32
#define TEXT_ONECOLOUMNWIDTH	400

class CPrintText  
{
public:
   CString textID;
   static CString Manual[9][5];
	static	CString GraphPrText[5][9];
	static	CString AlarmEng[MaxAlarmString];
	static CString AlarmGer[MaxAlarmString];
	static CString AlarmSpn[MaxAlarmString];
	static CString AlarmItl[MaxAlarmString];
	static CString AlarmFr[MaxAlarmString];
	static CString AlarmChS[MaxAlarmString];
	static CString AlarmChT[MaxAlarmString];
	static CString AlarmJpn[MaxAlarmString];
	static CString AlarmKor[MaxAlarmString];
	int PageNo;
	void Draw(CDC *pDC);
	CPoint CoOrdinate;
	int TextFont;
	CPrintText(unsigned char * &data, int &length,bool ViewPreset);
   CPrintText(unsigned char * &data, int &length,bool ViewPreset,int ID);
	CPrintText();
	virtual ~CPrintText();
	CString Text;
	int Lang_Index;
   CString VGAFormatString(CString str1,CString str2);
   CString VGAFormatString2(CString str1,CString str2);
private:
	

	CString GetString(unsigned char *&data, int &length);
	int Convert_Char_To_Integer(unsigned char *&data, int &length);
	CString RemoveNull(CString str);
};

#endif // !defined(AFX_PRINTTEXT_H__FD6DC23C_E60C_410D_9D30_23A5FF668499__INCLUDED_)
