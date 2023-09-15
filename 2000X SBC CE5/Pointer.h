// Pointer.h: interface for the CPointer class.
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

#if !defined(AFX_POINTER_H__7510F886_C14F_11D7_BF52_00500406C138__INCLUDED_)
#define AFX_POINTER_H__7510F886_C14F_11D7_BF52_00500406C138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class Object>
class CPointer
{
public:
	CPointer(Object * obj)
	{
		object = obj;
	}
	~CPointer()
	{
		if (object)
			delete object;
	}
	void Done()
	{
		object = 0;
	}

private:
	Object * object;
};

#endif // !defined(AFX_POINTER_H__7510F886_C14F_11D7_BF52_00500406C138__INCLUDED_)
