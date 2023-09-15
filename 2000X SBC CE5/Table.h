// Table.h: interface for the CTable class.
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
  1.1       08/01/08    PDwivedi  Added constructor.
*/

#if !defined(AFX_TABLE_H__EE6A255E_CF6A_4C6B_A31F_61BFB65E5BA9__INCLUDED_)
#define AFX_TABLE_H__EE6A255E_CF6A_4C6B_A31F_61BFB65E5BA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CTable : public CVgaMenuItem  
{
public:
	CTable(CXmlElement * e);
	virtual ~CTable();
   static int HighLightString;
	void Print(CDC *pDC, CPoint point);
	void CopyVGATableData(CTable *object);
	void GetHornScanData_for_CompareData(CDC *pDC,bool IsPrint);
	CString RowHeading[9];
	CString ColoumnHeading[3];
	int X1_CoOrdinate;
	int X2_CoOrdinate;
	int Y1_CoOrdinate;
	int Y2_CoOrdinate;
	//int ParamID;
	CTable();
	CString CompareData[9][3];
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
};

#endif // !defined(AFX_TABLE_H__EE6A255E_CF6A_4C6B_A31F_61BFB65E5BA9__INCLUDED_)
