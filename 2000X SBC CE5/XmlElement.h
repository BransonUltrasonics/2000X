// XmlElement.h: interface for the CXmlElement class.
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
  1.0       10/23/07    PDwivedi  Added Initial Version.
  1.1       01/11/08    PDwivedi  Modified Constructor.
  1.2		04/04/08	PDwivedi  Modified Constructor.	

*/

#if !defined(AFX_XMLELEMENT_H__3C4D3E7C_5E50_40ED_978D_A923EC4A3EA2__INCLUDED_)
#define AFX_XMLELEMENT_H__3C4D3E7C_5E50_40ED_978D_A923EC4A3EA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXmlElement  
{
   friend class CSBCApp;
   friend class CEnumVariable;
   friend class CBitmaskVariable;
   friend class CVgaMenu;
   friend class CVgaTitle;
   friend class CVgaSubMenu;
   friend class CVgaChoice;
   friend class CText;
   friend class CToggle;
   friend class CRadioMenu;
   friend class CVgaVariable;
   friend class CDate;
   friend class CVgaTime;
   friend class CVgaButton;
   friend class CVgaRadioButton;
   friend class CMsgScreen;
   friend class CListBoxObject;
   friend class CVgaAlphanumeric;
   friend class CBottomHalf;
   friend class CCheck;
   friend class CLine;
   friend class CRunScreen;
   friend class CWeldingHistory;
public:
   bool GetBoolAttribute(const CString & attr) const;
   CString GetAttribute(const CString & attr) const;
   const CString & GetTag() const
   {
      return tag;
   }
   void Write(const CString & fileName) const;
   void SetTag(const CString & t)
   {
      tag = t;
   }
   void SetContents(const CString & c)
   {
      contents = c;
   }
   void SetAttribute(const CString & parameter, const CString & value);
   void AddChild(CXmlElement * e)
   {
      children.AddTail(e);
   }
   CXmlElement();
   virtual ~CXmlElement();


   void Indent(CStdioFile & file, int indent) const;
   void Write(CStdioFile & file, int indent) const;
   void Write(CStdioFile &file, const CString & string) const
   {
		//file.WriteString(string);
		//TRACE(string);
   }
   CString tag;
   CString contents;
   CMapStringToString attributes;
   CStringList attributeList;
   CTypedPtrList<CPtrList, CXmlElement *> children;
};

#endif // !defined(AFX_XMLELEMENT_H__3C4D3E7C_5E50_40ED_978D_A923EC4A3EA2__INCLUDED_)
