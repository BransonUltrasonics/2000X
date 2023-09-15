// Variable.h: interface for the CVariable class.
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

#if !defined(AFX_VARIABLE_H__5AC7208D_ADC2_4515_8860_5DE714FB3BAB__INCLUDED_)
#define AFX_VARIABLE_H__5AC7208D_ADC2_4515_8860_5DE714FB3BAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Condition.h"
#include "XmlElement.h"

class CVariable  
{

public:
	CVariable();
	virtual ~CVariable();
   virtual CCondition * CreateCondition(CXmlElement * element) = 0;
   CString name;
protected:
	
	CString address;
	int value;
};

#endif // !defined(AFX_VARIABLE_H__5AC7208D_ADC2_4515_8860_5DE714FB3BAB__INCLUDED_)
