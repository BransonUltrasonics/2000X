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

#if !defined(AFX_OBJECTLIST_H__020C5DA3_C1E6_11D7_BF52_00500406C138__INCLUDED_)
#define AFX_OBJECTLIST_H__020C5DA3_C1E6_11D7_BF52_00500406C138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * class ObjectList: Template class maintains a list of objects that are stored
 * in the list using pointers. All objects are destroyed when the list object
 * is destroyed.
 */
template <class Object>
class CObjectList : public CTypedPtrList<CPtrList, Object *>
{
public:
	/**
	 * ~CObjectList: Destroy the list object.
	 */
	~CObjectList()
	{
		DeleteAll();
	}
	/**
	 * DeleteAll: Remove and destroy all objects that were stored in this
	 * list.
	 */
	void DeleteAll()
	{
		POSITION pos = GetHeadPosition();
		while (pos)
			delete GetNext(pos);
	}
};

#endif // !defined(AFX_OBJECTLIST_H__020C5DA3_C1E6_11D7_BF52_00500406C138__INCLUDED_)
