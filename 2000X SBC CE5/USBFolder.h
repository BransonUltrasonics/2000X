/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/USBFolder.h_v   1.1   01 Aug 2008 19:31:04   pdwivedi  $ */
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
 1.0		  10/14/05	  BWadia	   Added Initial Version
 1.1       08/01/08    PDwivedi  Modified Base class.
*/
// USBFolder.h: interface for the CUSBFolder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USBFOLDER_H__60024736_DC41_49B6_BA8D_7B1B82BC5AC1__INCLUDED_)
#define AFX_USBFOLDER_H__60024736_DC41_49B6_BA8D_7B1B82BC5AC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "VfdObject.h"
#include "ChildView.h"
#include "VgaMenuItem.h"


#define JAN 1
#define FEB 2
#define MAR 3
#define APR 4
#define MAY 5
#define JUN 6
#define JUL 7
#define AUG 8
#define SEP 9
#define OCT 10
#define NOV 11
#define DEC 12

class CUSBFolder  : public CVgaMenuItem//CVfdObject
{
public:
	static CString ThirdHierTitle;
	static CString SecondHierTitle;

	static CString LastFolderPath;
	static CString HistoryGraphPath;
	static CString LastFilePath;
	static CString PreviousFileName;
	//static int FolderHierchy;
	CString GetDiaplayName(int HierarchyLevel);
	bool PrepareUSBHistoryList(CString Path,CChildView *view);
	CUSBFolder(CString FileName,CString FilePath,int Address,int Function_Id);
	virtual ~CUSBFolder();
	CString Name;
	CString Path;
	CString DisplayName;
   int TitleID;
   int Fun_Id;
protected:
	void ClearAllFiles();
//	void PrepareUSBList(CChildView *view);
	virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC *pDC);

private:

	
};

#endif // !defined(AFX_USBFOLDER_H__60024736_DC41_49B6_BA8D_7B1B82BC5AC1__INCLUDED_)
