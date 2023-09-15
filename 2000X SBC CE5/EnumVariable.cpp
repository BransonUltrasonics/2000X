// EnumVariable.cpp: implementation of the CEnumVariable class.
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
  1.1       01/11/08    PDwivedi  Modified CreateCondition function.  
  1.2       04/04/08	   PDwivedi  Added Condition in CreateCondition.
  1.3       06/06/08    PDwivedi  Added Global CMapStringToString & new Condition.
  1.4       06/12/08    PDwivedi  Modified CreateCondition function.
  1.5       10/01/08    PDwivedi	 Modified CreateCondition for calibration BUG00422.

*/

#include "stdafx.h"
#include "SBC.h"
#include "EnumVariable.h"
#include "XmlElement.h"
#include "EnumCondition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMapStringToString values;

CEnumVariable::CEnumVariable(CXmlElement * element)
{
	value = 0;
	name = element->GetAttribute("name");
	address = element->GetAttribute("address");
	POSITION pos = element->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * e = element->children.GetNext(pos);
		ASSERT(e->tag == "enum");
		CString name1 = e->GetAttribute("name");
		CString value1 = e->GetAttribute("value");
		values.SetAt(name1, value1);
	}
}

CEnumVariable::~CEnumVariable()
{

}

/*************************************************************************************/
/*                                                                                   */
/* Function to Create EnumVariables conditions like ControlLevel,Actuator,Securitylevel 
/* and Enable Flag.  
/*  							
/*************************************************************************************/
CCondition * CEnumVariable::CreateCondition(CXmlElement *element)
{
	CEnumCondition * condition = new CEnumCondition();
	condition->variable = this;
	CString attr;
	attr = element->GetAttribute("valueset");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = CONDITION0_INDEX;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}
   
   attr = element->GetAttribute("cntset");
   if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = CONDITION1_INDEX;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}

   attr = element->GetAttribute("actset");   
   if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = CONDITION2_INDEX;
      condition->EnumValue = _ttoi(bitNumber);
      return condition;
	}

   attr = element->GetAttribute("Enable");
   if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = CONDITION3_INDEX;
		condition->EnableCommand = _ttoi(bitNumber);
      condition->CalibMenuIndex=0;
      condition->CalibMenuIndexAED=0;
      condition->EnumValue=0;
      attr=element->GetAttribute("EnableId");
	   if (attr != "")
         condition->StringID=_ttoi(attr);
      
      attr=element->GetAttribute("AEDActuatorValue");
      if (attr != "")
	   {
		   CString bitNumber;
		   values.Lookup(attr, bitNumber);
         condition->EnumValue = _ttoi(bitNumber);
	   }
      if(condition->EnumValue)
      {
         attr=element->GetAttribute("CalibMenuIndex");
         if (attr != "")
            condition->CalibMenuIndex=_ttoi(attr);
         else
            condition->CalibMenuIndex=0;

         attr=element->GetAttribute("CalibMenuIndexAED");
         if (attr != "")
            condition->CalibMenuIndexAED=_ttoi(attr);
         else
            condition->CalibMenuIndexAED=0;
      }

      return condition;
	}
   attr = element->GetAttribute("CheckForFunction");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = CONDITION4_INDEX;
		condition->EnumValue = _ttoi(bitNumber);
      condition->FunName=element->GetAttribute("funname");
		return condition;
	}
	attr = element->GetAttribute("SendRunScreenColumn");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = CONDITION5_INDEX;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}	
   delete condition;
   ASSERT(FALSE);
	return 0;
}
