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
  1.0       01/11/08	PDwivedi  Added Initial Version.
  1.1		04/04/08	PDwivedi  Added # Define for Multilang.	
*/

#ifndef _TEXTFILEIO_H_
#define _TEXTFILEIO_H_
#define LF 13
#define EOF_FILE   65535
#pragma once

//#include <stdio.h>
#include <string>
//using namespace std;
//#include <windows.h>
//#include <tchar.h>

#define TOTALANGINDEX   2
#define  FONTNAMEINDEX  3
#define  CHARSETINDEX   4
#define FLAGFILEINDEX   5

class CTextFileIO
{
public:
   int count;
   static int Languagearray;
   static int fontcount;
   static int FontSizeCount;
   wint_t indicator;
   static int no_of_strings;
   static int gh;
   fpos_t pos;
   static CStringArray sstID;
   static CStringArray sststring;
   static int SstFont[50];
   static int SstFontSize[50];
   static CString CurrentFontName;
   static int CurrentFontChar_Set;
public:
   ~CTextFileIO(void);
public:
   CTextFileIO(CString filename,WCHAR *mode,bool FirstTime);

public:
   // Open the file
   BOOL OpenW(CString  filename,  WCHAR *mode,bool FirstTime);

private:
   // Internale FILE object 
   FILE* _file;
   CString s;
public:

   // Read aline from a UNICODE file
   // Return value:if end of file,return value is false,else is true
   wint_t _ReadLine(CString s, wint_t eol=L'\n', wint_t eof=WEOF);
   // Unicode version of read line
   void ReadLineW(bool FirstTime,bool skipFirstLine);


public:
   // Text file encoding type enum
   enum EncodingType {ANSI,UTF16_LE,UTF16_BE,UTF32_LE,UTF32_BE,UTF_8};
private:
   // File encoding type
   EncodingType encodingType;
public:
   // Check file encoding type
   static EncodingType CheckFileEncodingTypeW(const WCHAR* const filename);

public:
   // Get current open file's encoding type
   CTextFileIO::EncodingType GetEncodingType(void)
   {
      return encodingType;
   }
   // Omit file encoding tag
   int OmitEncodingTag(EncodingType type);
   // Indicate file can be read or not
   bool _IsValidate;
public:

   // Check file is validate to read
   bool IsValidate(void)
   {
      return _IsValidate;
   }

};

#endif
