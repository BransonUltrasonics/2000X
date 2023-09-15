// BitmaskVariable.cpp: implementation of the CBitmaskVariable class.
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
  1.1       08/26/08	   PDwivedi  Modify CreateCondition() to store SW & HW Configutation.
 */

#include "stdafx.h"
#include "SBC.h"
#include "BitmaskVariable.h"
#include "XmlElement.h"
#include "BitCondition.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CBitmaskVariable::CBitmaskVariable(CXmlElement * element)
{
	value = 0;
	name = element->GetAttribute("name");
	address = element->GetAttribute("address");
	POSITION pos = element->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * bit = element->children.GetNext(pos);
		ASSERT(bit->tag == "bit");
		CString bitname = bit->GetAttribute("name");
		CString value = bit->GetAttribute("value");
		values.SetAt(bitname, value);

	}
}

CBitmaskVariable::~CBitmaskVariable()
{
}

CCondition * CBitmaskVariable::CreateCondition(CXmlElement *element)
{
	CBitCondition * condition = new CBitCondition();
	condition->variable = this;
	CString attr;
	attr = element->GetAttribute("Mask1bitset");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->Mask1= _ttoi(bitNumber);
		condition->Cond1 = _ttoi(bitNumber);
		condition->CaseValue=0;
		return condition;
	}

	attr = element->GetAttribute("Mask1bitclear");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->Mask1= _ttoi(bitNumber);
		condition->CaseValue=0;
		condition->Cond1 = ~(_ttoi(bitNumber));
		return condition;
	}

	attr = element->GetAttribute("Mask2bitset");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->Mask2= _ttoi(bitNumber);
		condition->Cond2 = _ttoi(bitNumber);
		condition->CaseValue=0;
		return condition;
	}

	attr = element->GetAttribute("Mask2bitclear");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->Mask2= _ttoi(bitNumber);
		condition->CaseValue=0;
		condition->Cond2 = ~(_ttoi(bitNumber));
		return condition;
	}


	attr = element->GetAttribute("Modeset");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->bitValue =_ttoi(bitNumber);
		condition->CaseValue=1;
		return condition;
	}
	delete condition;
	ASSERT(0);
	return 0;
}
