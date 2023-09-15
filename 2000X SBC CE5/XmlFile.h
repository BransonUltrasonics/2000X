// XmlFile.h: interface for the CXmlFile class.
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
  1.1       08/01/08	   PDwivedi  Added function for Comment.
*/

#if !defined(AFX_XMLFILE_H__5E640096_3AF2_432D_9F54_D0383F069D54__INCLUDED_)
#define AFX_XMLFILE_H__5E640096_3AF2_432D_9F54_D0383F069D54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXmlElement;

class CXmlFile  
{
public:
   bool Comment;
	CXmlElement * Read(CArchive & ar);
	CXmlFile();
	virtual ~CXmlFile();

protected:
	CString ReadString();
	CString ReadIdentifier();
   void CheckStartComment();
   void CheckComment();
	CXmlElement * ReadElement();
	void Expect(char ch);
	void SkipBlanks();
	void Error(const CString &message)
	{
		throw message;
	}
	void ReadChar(bool skipBlanks = true);
	CArchive * archive;
	int lineNumber;
	char lastch;
   bool flag1;
};

#endif // !defined(AFX_XMLFILE_H__5E640096_3AF2_432D_9F54_D0383F069D54__INCLUDED_)
