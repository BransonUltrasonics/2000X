// BitCondition.h: interface for the CBitCondition class.
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
  1.1       08/26/08	   PDwivedi  Added members to check SW & HW Configutation.
*/

#if !defined(AFX_BITCONDITION_H__467EF3E5_DD15_4763_8C20_8E5FFCE033D6__INCLUDED_)
#define AFX_BITCONDITION_H__467EF3E5_DD15_4763_8C20_8E5FFCE033D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Condition.h"
class CVgaMenuItem;
class CBitCondition : public CCondition  
{
public:
	CBitCondition();
	virtual ~CBitCondition();
bool bitState;
	int bitValue;
   int Mask1;
   int Cond1;
   int Mask2;
   int Cond2;
   int CaseValue;
protected:
	virtual bool Evaluate(CVgaMenuItem *) const;
};

#endif // !defined(AFX_BITCONDITION_H__467EF3E5_DD15_4763_8C20_8E5FFCE033D6__INCLUDED_)
