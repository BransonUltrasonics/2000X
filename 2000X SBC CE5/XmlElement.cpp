// XmlElement.cpp: implementation of the CXmlElement class.
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

#include "stdafx.h"
#include "SBC.h"
#include "XmlElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXmlElement::CXmlElement()
{
}

CXmlElement::~CXmlElement()
{
	while (children.GetCount() > 0)
		delete children.RemoveHead();
}

void CXmlElement::Write(const CString &fileName) const
{
	CStdioFile file;
	if (file.Open(fileName, CFile::modeWrite | CFile::modeCreate))
	{
		Write(file, 0);
	}
}

void CXmlElement::Write(CStdioFile &file, int indent) const
{
	CString line;

	Indent(file, indent);
	Write(file, "<" + tag);
	POSITION pos = attributeList.GetHeadPosition();
	while (pos)
	{
		CString param = attributeList.GetNext(pos);
		CString value;
		attributes.Lookup(param, value);
		Write(file, " " + param + "=\"" + value + "\"");
	}
	if (children.GetCount() > 0)
	{
		Write(file, ">\n");
		pos = children.GetHeadPosition();
		while (pos)
		{
			CXmlElement * e = children.GetNext(pos);
			e->Write(file, indent + 1);
		}
	}
	if (!contents.IsEmpty())
	{
		Write(file, ">" + contents + "</" + tag + ">\n");
	}
	// no text, but at least a child or attribute
	else if (children.GetCount() > 0)	// some children
	{
		Indent(file, indent);
		Write(file, "</" + tag + ">\n");
	}
	else
	{
		Write(file, "/>\n");
	}
}

void CXmlElement::Indent(CStdioFile &file, int indent) const
{
	while (indent-- > 0)
		Write(file, "        ");
}

void CXmlElement::SetAttribute(const CString & parameter, const CString & value)
{
	attributes.SetAt(parameter, value);
	attributeList.AddTail(parameter);
}

CString CXmlElement::GetAttribute(const CString & attr) const
{
	CString value;
	if (!attributes.Lookup(attr, value))
		return "";
	return value;
}

bool CXmlElement::GetBoolAttribute(const CString &attr) const
{
	CString value = GetAttribute(attr);
	return value == "true";
}
