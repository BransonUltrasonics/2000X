// Condition.h: interface for the CCondition class.
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

#if !defined(AFX_CONDITION_H__197EB7EE_CA48_41B2_9FD8_EA6746D45911__INCLUDED_)
#define AFX_CONDITION_H__197EB7EE_CA48_41B2_9FD8_EA6746D45911__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CVariable;
class CVgaMenuItem;
class CCondition  
{
public:
	CCondition();
	virtual ~CCondition();
   virtual bool Evaluate(CVgaMenuItem *) const = 0;
   CVariable * variable;
};

#endif // !defined(AFX_CONDITION_H__197EB7EE_CA48_41B2_9FD8_EA6746D45911__INCLUDED_)
