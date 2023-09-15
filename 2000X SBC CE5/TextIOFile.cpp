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
  1.1		   04/04/08	PDwivedi  Modify ReadLineW & destructor Function.
  1.2       04/14/08	PDwivedi  Modify CheckFileEncodingTypeW() & ReadLineW() for error check condition.
*/

#include "stdafx.h"
#include "TextIOFile.h"
#include "ChildView.h"
#include "SBC.h"

CStringArray CTextFileIO::sstID;
CStringArray CTextFileIO::sststring;
int CTextFileIO::SstFont[50];
int CTextFileIO::SstFontSize[50];
int CTextFileIO::Languagearray=0;
int CTextFileIO::fontcount=0;
int CTextFileIO::FontSizeCount=0;
int CTextFileIO::no_of_strings;
int CTextFileIO::gh;
CString CTextFileIO::CurrentFontName;
int CTextFileIO::CurrentFontChar_Set;

CTextFileIO::~CTextFileIO(void)
{
	if(sstID.GetSize()>0)
   {
      //printf("\n sstID");
      sstID.RemoveAll();
   }
  if(sststring.GetSize()>0)
   {
     // printf("\n sststring");
      sststring.RemoveAll();
   }
}

CTextFileIO::CTextFileIO(CString filename,  WCHAR *mode,bool FirstTime)
{
	indicator=' ';
   no_of_strings=0;
	gh=0;
   pos=0;
	encodingType=CTextFileIO::CheckFileEncodingTypeW(filename);
   _IsValidate=OpenW(filename,mode,FirstTime);

}



// Open file,UNICODE version
BOOL CTextFileIO::OpenW(CString  filename, WCHAR *mode,bool FirstTime)
{
	_file=_wfopen(filename,mode);
	if(_file==NULL)
   {
		AfxMessageBox(_T("Can't open file '") + filename + _T("'"));
      // Again Open the File
      filename=_T("Disk\\languages\\English.lan");
      _file=_wfopen(filename,L"rb");
   }
   // Seek  file pos
	if(wcschr(mode,L'r')!=NULL)
	{
         OmitEncodingTag(encodingType);
	}
	
	return TRUE;
}

// Read a line from file,return value is UNICODE string
wint_t CTextFileIO::_ReadLine(CString s1, wint_t eol, wint_t eof)
{
   
   int length=1;
	fgetpos( _file, &pos );
	int position=pos;
    // read one wide char at a time & Calculate Length
    while (true)
    {
      // read wide char
      wint_t c = fgetwc(_file);
      if(feof(_file))
		{
			break;
		}
		// check for EOL
      if (c == eol) 
		{
			fgetpos( _file, &pos );
			break;
		}

        length++;
    };
	int i=length;
	
	int count=0;
   // Allocate the Buffer according to length
    LPTSTR p = s.GetBuffer(i);
	fseek(_file,(position),SEEK_SET);
	while (true)
    {
      if(feof(_file))
		{
			break;
		}
		// read wide char
        wint_t c = fgetwc(_file);
       // check for EOL
      if (c == eol) 
		{
		   p[count]='\0';	
		   s.ReleaseBuffer();
		   return c;
		}
		else
		{
        // Skip lineFeed char        
		 if((c!=LF))
		 p[count++]=c;
		}
    };

	return eof;
}


// Unicode version of read line
void CTextFileIO::ReadLineW(bool FirstTime,bool skipFirstLine)
{
	bool bResult=false;
   CString ws;
   while (!feof(_file))
		{
	      //printf("\n getfile");
			indicator=_ReadLine(s);
			//Exit if EOF of file is found.
         if(indicator==EOF_FILE)
				break;
			ws=s;
         count++;
         if(count==TOTALANGINDEX)
         {
            if(ws=="")
            {
               AfxMessageBox(_T("No total No of strings found in .lan file"));
		         theApp.Clean ();
		         exit(1);
            }
            int fg=_ttoi(ws);
            //printf("\n fg=%d",fg);
            sstID.SetSize(fg);
            sststring.SetSize(fg);
			theApp.TotalLangElement=fg;
         }
         else if(count==FONTNAMEINDEX)
         {
            CurrentFontName=ws;
         }
         else if(count==CHARSETINDEX)
         {
            CurrentFontChar_Set=_ttoi(ws);
           // printf("\n CurrentFontChar_Set=%d",CurrentFontChar_Set);
         }
         else if(count>FLAGFILEINDEX)
         {
            sstID[no_of_strings++]=ws.SpanExcluding (_T(","));
            int index=ws.Find (_T(","));
			   index=ws.GetLength ()-index;
            CString str=ws.Right(index-1);
			   index=str.Find (_T(","));
				index=str.GetLength ()-index;
            str= str.Right(index-1);
            sststring[gh++]=str;
				fgetpos( _file, &pos );
				fseek(_file,pos,SEEK_SET);
         }
			
		}
   if(_file)
		fclose(_file);
}

// Check file encoding type
CTextFileIO::EncodingType CTextFileIO::CheckFileEncodingTypeW(const WCHAR* const filename)
{
	FILE* _file=_wfopen(filename,L"rb");
	// Read first 4 byte for testing
	BYTE* buf=new BYTE[4];
	size_t nRead=fread((void*)buf,sizeof(BYTE),4,_file);
   //printf("\n nRead=%d",nRead);
   if((nRead==0)||(nRead==2))
   {
      AfxMessageBox(_T("No .lan file found in SystemConfig.cfg or in /Disk Folder"));
      theApp.Clean ();
      exit(1);
   }
   // Close file
	fclose(_file);

	BYTE utf16_le[]={0xFF,0xFE};
	if(memcmp(buf,&utf16_le,2)==0)
	{
      delete []buf;
      return UTF16_LE;
	}
   delete []buf;
   return ANSI;
}


// Omit file encoding tag
int CTextFileIO::OmitEncodingTag(EncodingType type)
{
	int nResult=0;
   nResult=fseek(_file,2,SEEK_SET);
	return nResult;
}


