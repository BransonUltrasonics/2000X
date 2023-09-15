// Mylanguage.h: interface for the CMylanguage class.
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

*/

#if !defined(AFX_MYLANGUAGE_H__37D80165_8017_4447_B393_395D928029BB__INCLUDED_)
#define AFX_MYLANGUAGE_H__37D80165_8017_4447_B393_395D928029BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
#define ListBox_OneLineHeight	31
#define MAX_LANGUAGE_DISPLAYED 11

class CMylanguage : public CVgaMenuItem  
{
public:
	CMylanguage(int X1,int Y1,int X2,int Y2);
	virtual ~CMylanguage();
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
private:
   int ListBox_Color;
	int X1_CoOrdinate;
	int X2_CoOrdinate;
	int Y1_CoOrdinate;
	int Y2_CoOrdinate;
};

#endif // !defined(AFX_MYLANGUAGE_H__37D80165_8017_4447_B393_395D928029BB__INCLUDED_)
