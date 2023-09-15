// EnumCondition.h: interface for the CEnumCondition class.
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
  1.1       01/11/08    PDwivedi  Added Constants.     
  1.2		   04/04/08	   PDwivedi	 Added Declarations.	
  1.3       04/14/08    PDwivedi	 Added #define for MultiLangSupport.
  1.4       06/06/08    PDwivedi  Added Declarations for function.
  1.5       08/08/08    PDwivedi  Final Code Clean up.
  1.6       10/01/08    PDwivedi	 Added Members for calibration BUG00422.
*/

#if !defined(AFX_ENUMCONDITION_H__929C9419_9559_49DA_8312_E6CD6FB9B9C8__INCLUDED_)
#define AFX_ENUMCONDITION_H__929C9419_9559_49DA_8312_E6CD6FB9B9C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Text.h"
#include "Condition.h"
#define MAXRADIOITEMS  13
#define SETUP_ALARM           7
#define SETUP_ALARM_END       10

 
class CVgaMenuItem;
class CEnumCondition : public CCondition  
{
public:
	CEnumCondition();
	virtual ~CEnumCondition();
	int enumflagvalue;
	int EnumValue;
   int StringID;
   CString FunName;
   int CalibMenuIndex;
   bool EnableCommand;
   int CalibMenuIndexAED;
   int AEDActuatorValue;
protected:
	virtual bool Evaluate(CVgaMenuItem *) const;

};

#endif // !defined(AFX_ENUMCONDITION_H__929C9419_9559_49DA_8312_E6CD6FB9B9C8__INCLUDED_)
