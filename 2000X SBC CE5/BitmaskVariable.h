// BitmaskVariable.h: interface for the CBitmaskVariable class.
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

#if !defined(AFX_BITMASKVARIABLE_H__0844E3FB_01C4_488A_8FCB_C0568E988F72__INCLUDED_)
#define AFX_BITMASKVARIABLE_H__0844E3FB_01C4_488A_8FCB_C0568E988F72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Variable.h"

class CXmlElement;

class CBitmaskVariable : public CVariable  
{
public:
	CBitmaskVariable(CXmlElement * element);
	virtual ~CBitmaskVariable();

protected:
	CMapStringToString values;
	virtual CCondition * CreateCondition(CXmlElement * element);
};

#endif // !defined(AFX_BITMASKVARIABLE_H__0844E3FB_01C4_488A_8FCB_C0568E988F72__INCLUDED_)
