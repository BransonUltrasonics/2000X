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

#if !defined(AFX_OBJECTMAP_H__7510F883_C14F_11D7_BF52_00500406C138__INCLUDED_)
#define AFX_OBJECTMAP_H__7510F883_C14F_11D7_BF52_00500406C138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * class CObjectMap: Template class provides storage for objects indexed by a
 * string. All objects are destroyed when the list object is destroyed.
 */
template <class Object>
class CObjectMap : public CTypedPtrMap<CMapStringToPtr, CString, Object *>
{
public:
	/**
	 * ~CObjectMap: Destroy the map object.
	 */
	~CObjectMap()
	{
		DeleteAll();
	}
	/**
	 * DeleteAll: Remove and destroy all objects that were stored in this
	 * map.
	 */
	void DeleteAll()
	{
		POSITION pos = GetStartPosition();
		while (pos)
		{
			CString key;
			Object * obj;
			GetNextAssoc(pos, key, obj);
			delete obj;
		}
		CMapStringToPtr::RemoveAll();
	}
};

#endif // !defined(AFX_OBJECTMAP_H__7510F883_C14F_11D7_BF52_00500406C138__INCLUDED_)
