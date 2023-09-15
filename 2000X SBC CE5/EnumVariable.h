// EnumVariable.h: interface for the CEnumVariable class.
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
  1.1       06/06/08    PDwivedi  Remove Member CMapStringToString.
  1.2       06/12/08    PDwivedi  Added Enum for different Condition Index.
*/

#if !defined(AFX_ENUMVARIABLE_H__E42A1622_4133_4CED_8CD5_8BB8334699B3__INCLUDED_)
#define AFX_ENUMVARIABLE_H__E42A1622_4133_4CED_8CD5_8BB8334699B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Variable.h"

class CXmlElement;

enum CONDITION
{
    CONDITION0_INDEX,
    CONDITION1_INDEX,
    CONDITION2_INDEX,
    CONDITION3_INDEX,
    CONDITION4_INDEX,
    CONDITION5_INDEX
};

class CEnumVariable : public CVariable  
{
public:
	CEnumVariable(CXmlElement * element);
	virtual ~CEnumVariable();
  // CMapStringToString values;
	CComboBox * combo;
protected:
	virtual CCondition * CreateCondition(CXmlElement *element);

};

#endif // !defined(AFX_ENUMVARIABLE_H__E42A1622_4133_4CED_8CD5_8BB8334699B3__INCLUDED_)
