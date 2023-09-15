// XmlFile.cpp: implementation of the CXmlFile class.
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
  1.2       10/07/09	   PDwivedi  Replacing Try and catch statements with TRY and CATCH 
                                  Macro to support Exception Handling.
*/

#include "stdafx.h"
#include "SBC.h"
#include "XmlFile.h"
#include "XmlElement.h"
#include "Pointer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXmlFile::CXmlFile()
{  Comment = false;
}

CXmlFile::~CXmlFile()
{
}

CXmlElement * CXmlFile::Read(CArchive & ar)
{
	CXmlElement * xml = 0;
	TRY
	{
		lineNumber = 1;
		archive = &ar;
		lastch = ' ';
		ReadChar();
		Expect('<');
      CheckStartComment();

      if(lastch=='!')
      {   while(lastch == '!')
         { CheckComment();
         }
      }

      //if(Comment==true)
		//   ReadChar();	// skip past first '<'

		xml = ReadElement();
	}

   CATCH_ALL(E)
	{
		TCHAR  szCause[255];
      E->GetErrorMessage(szCause, 255);
      CString x;
      x = _T("The error: ");
      x += szCause;
      if (xml)
			delete xml;
      AfxMessageBox(x);
   }
   END_CATCH_ALL
	return xml;
}

void CXmlFile::ReadChar(bool skipBlanks)
{// printf("inside readchar  lastchar = %c ",lastch);
	TRY
	{
		if (archive->Read(&lastch, 1) != 1)
			lastch = -1;
		if (skipBlanks)
			SkipBlanks();
	}
   CATCH(CArchiveException,e)
	{
		lastch = -1;
		AfxMessageBox(_T("Error reading archive"));
	}
   AND_CATCH(CFileException,e)
	{
		lastch = -1;
		AfxMessageBox(_T("Error reading file"));
	}
   END_CATCH
}

void CXmlFile::SkipBlanks()
{  //printf("Inside Skipblank()");
	while (isspace(lastch))
	{ // printf("Processing ReadChar(false)");
		ReadChar(false);
	}
}

void CXmlFile::Expect(char ch)
{ //printf("inside Expect (expecting %c),lastch = %c \n",ch,lastch);
	if (lastch != ch)
	{
		CString err;
		err.Format(_T("Expected '%c', read '%c'"), ch, lastch);
      AfxMessageBox(err);
	}
}

CXmlElement * CXmlFile::ReadElement()
{ // printf("\nReadElement begins\n\n");
	CXmlElement * element = new CXmlElement();
	CPointer<CXmlElement> p(element);
	CString tag = ReadIdentifier();
  	element->SetTag(tag);
	SkipBlanks();
	while (isalnum(lastch))		// extract attributes
	{  CString param = ReadIdentifier();
		SkipBlanks();
		Expect('=');
		ReadChar();
		CString value = ReadString();
		element->SetAttribute(param, value);
	}

  	if (lastch == '>')		// children first, then '</...>'
	{ ReadChar();
		   bool cont;
         cont = true;
      while (lastch == '<')
		{  
         CheckStartComment();
        
      // printf("look here /////////////////////// lastch %c",lastch);
		//	ReadChar();
        
         if(lastch == '!')
         {  while(lastch == '!')
               { CheckComment();}
         }

			if (lastch == '/')
				break;
			CXmlElement * e = ReadElement();
			element->AddChild(e);
		}
		if (lastch != '/')	// this should be free text
		{  CString text;
			while (lastch != '<')
			{ 	text += lastch;
				ReadChar(false);
			}
			element->SetContents(text);
			ReadChar();	// skip the '<'
			Expect('/');
		}
		ReadChar();
		CString tag1 = ReadIdentifier();
		if (tag != tag1)
			AfxMessageBox(_T("<Tag> and </Tag> mismatch"));
		Expect('>');
		ReadChar();
	}
	else if (lastch == '/')
	{ 	ReadChar();
		Expect('>');
		ReadChar();
	}
	else
		AfxMessageBox(_T("'>' or '/>' expected"));

	p.Done();
  
  	return element;
}

CString CXmlFile::ReadIdentifier()
{
	CString result;
	while (isalnum(lastch) || (lastch == '_'))
	{ result += lastch;
		ReadChar(false);
	}
  	return result;
}

CString CXmlFile::ReadString()
{
	Expect('"');
	ReadChar(false);
	CString value;
	while (lastch != '"')
	{  value += lastch;
		ReadChar(false);
	}
  	ReadChar();		// skip last '"'
	return value;
}


void CXmlFile::CheckStartComment()
{
   if(lastch=='<')
   { 
      ReadChar(false);
      if(lastch =='!')
      {  
         ReadChar(false);
         if(lastch == '-')
         {  
            ReadChar(false);
            if(lastch == '-')
            {  
               ReadChar(false);
               Comment = true;
            }
         }
      }
   }

   if(Comment == true)
   { 
      while(1)
      {  
         if(lastch == '-')
         {  
            ReadChar(false);
            if(lastch == '-')
            {  
               ReadChar(false);
               if(lastch == '>')
               {   ReadChar();
                  Expect('<');
                  ReadChar();
                  break;
               }
            }   
          }
          ReadChar(false);
       }
      Comment = false;
    }
}

void CXmlFile::CheckComment()
{
   if(lastch =='!')
   {  
      ReadChar(false);
      if(lastch == '-')
      {  ReadChar(false);
         if(lastch == '-')
         {  
            ReadChar(false);
            Comment = true;
         }
      }
   }
   
   if(Comment == true)
   { 
      while(1)
      {  
         if(lastch == '-')
         { 
            ReadChar(false);
            if(lastch == '-')
            {   
               ReadChar(false);
               if(lastch == '>')
               {  ReadChar();
                  Expect('<');
                  ReadChar();
                  break;
               }
            }   
          }
         ReadChar(false);
       }
      Comment = false;
   }
}