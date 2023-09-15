// RunScreen.h: implementation of the CRunScreen class.
//
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
  1.0       10/23/07	   PDwivedi  Added Initial Version.
  1.1       08/08/08    PDwivedi  Final Code Clean up.
*/

#if !defined(AFX_RUNSCREEN_H__1A7E24D2_65AD_4696_BB64_326F3E11062C__INCLUDED_)
#define AFX_RUNSCREEN_H__1A7E24D2_65AD_4696_BB64_326F3E11062C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define RUN_RESULT_TBL_START_X  8
#define RUN_RESULT_TBL_START_Y  50//100
#define LINE_GAP  30
#define ParamRect_Width	120
#define MaxCyclePerScreen	7

#include "VgaMenuItem.h"
#include "ChildView.h"
//#include "WeldData.h"
#include "WeldingData.h"

class CXmlElement;
class CRunScreen : public CVgaMenuItem  
{
public:
	CRunScreen(CXmlElement * e);
	virtual ~CRunScreen();
	int ReceivedUniversalCount;
	UpdateWeldData(unsigned char *&data,int &length,bool Constructor);
	static int Displayable_columns;
//	static int TotalColumn;
	static int *ID_Array;
	static int  *Parameter_ID;
	CTypedPtrList<CPtrList, CWeldingData *> WeldDataList;
	int TotalCycles;
	int RunID;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;

//private:
   
};

#endif // !defined(AFX_RUNSCREEN_H__1A7E24D2_65AD_4696_BB64_326F3E11062C__INCLUDED_)
