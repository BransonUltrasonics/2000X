// ExcelCvt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ExcelCvt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <objidl.h>
#include <afxole.h>

/////////////////////////////////////////////////////////////////////////////
// CSSFile class

class CSSFile
{
// Construction
public:
	CSSFile();
	virtual ~CSSFile();

// Implementation
public:
	// file-system level access:
	bool CreateSSFile(const CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	bool OpenSSFile(const CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	IStorage * Attach(IStorage* pNews);
	IStorage * Detach();

	// storage-level access:
	bool CreateStorage(const CString & name, bool enter = false, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	bool EnterStorage(const CString & name, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	bool ExitStorage();

	bool CreateStream(const CString & name, COleStreamFile &sf, DWORD mode = CFile::modeReadWrite | CFile::shareExclusive);
	bool OpenStream(const CString & name, COleStreamFile &sf, DWORD mode = CFile::modeReadWrite | CFile::shareExclusive);

	bool DestroyElement(const CString & szName);

	// status info:
	IStorage * GetRootStorage() const;
	IStorage * GetCurrentStorage() const;
	CString GetPath(const CString & SepChar = "\\") const;
	CString GetFilename() const;
	bool IsOpen() const;
	void Close();

	struct StorageData
	{
		IStorage *Stg;
		StorageData *ParentStg;

		StorageData()
		{
			Stg = NULL;
			ParentStg = NULL;
		}
	};

protected:
	bool m_bOpen;
	CString m_strFilename;
	IStorage *m_pRootStg;
	StorageData *m_pCurrentStg;
};

/////////////////////////////////////////////////////////////////////////////
// CSSFile

CSSFile::CSSFile()
{
	m_bOpen = false;
	m_strFilename = _T("");
	m_pCurrentStg = NULL;
	m_pRootStg = NULL;
}

CSSFile::~CSSFile()
{
	Close();
}

/////////////////////////////////////////////////////////////////////////////
// Opening, creating and closing storage files

bool CSSFile::OpenSSFile(const CString & filename, DWORD mode)
{
	if (m_bOpen)
		Close();

	WCHAR wcFName[MAX_PATH];
#ifndef UNICODE
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCTSTR)filename, -1, wcFName, MAX_PATH);
#else
	wcscpy(wcFName, (LPCTSTR)filename);
#endif

	HRESULT res = StgOpenStorage(wcFName, NULL, mode, NULL, 0, &m_pRootStg);
	if (res != S_OK)
		return false;

	m_bOpen = true;
	m_strFilename = filename;

	StorageData *sd = new StorageData;
	sd->Stg = m_pRootStg;
	sd->ParentStg = NULL;
	m_pCurrentStg = sd;

	return true;
}

bool CSSFile::CreateSSFile(const CString & filename, DWORD mode)
{
	if (m_bOpen)
		Close();

	WCHAR wcFName[MAX_PATH];
#ifndef UNICODE
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCTSTR)filename, -1, wcFName, MAX_PATH);
#else
	wcscpy(wcFName, (LPCTSTR)filename);
#endif

	if (StgCreateDocfile(wcFName, mode, 0, &m_pRootStg) != S_OK)
		return false;

	m_bOpen = true;
	m_strFilename = filename;

	StorageData *sd = new StorageData;
	sd->Stg = m_pRootStg;
	sd->ParentStg = NULL;
	m_pCurrentStg = sd;

	return true;
}

IStorage* CSSFile::Attach(IStorage* pNews)
{
	ASSERT(pNews != NULL);

	// store the old root storage:
	IStorage* old = m_pRootStg;
	while (ExitStorage())
		;	
	
	// set up the new one:
	m_pRootStg = pNews;
	m_pCurrentStg = new StorageData;
	m_pCurrentStg->ParentStg = NULL;
	m_pCurrentStg->Stg = pNews;

	// return the old one:
	return old;
}

void CSSFile::Close()
{
	if (m_bOpen)
	{
		// Release all pointers in the open tree:
		while (ExitStorage())
			;

		m_pCurrentStg->Stg->Release();
		delete m_pCurrentStg;

		m_pCurrentStg = NULL;
		m_pRootStg = NULL;
	}

	m_bOpen = false;
	m_strFilename = _T("");
}

IStorage * CSSFile::Detach()
{
	while (ExitStorage())
		;

	IStorage* rtn = m_pRootStg;
	m_bOpen = false;
	m_pCurrentStg = NULL;
	m_pRootStg = NULL;
	m_strFilename = _T("");

	return rtn;
}

/////////////////////////////////////////////////////////////////////////////
// General storage manipulation functions:

bool CSSFile::DestroyElement(const CString & szName)
{
	ASSERT(m_pCurrentStg && m_bOpen);

	WCHAR wcFName[MAX_PATH];
#ifndef UNICODE
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCTSTR)szName, -1, wcFName, MAX_PATH);
#else
	wcscpy(wcFName, (LPCTSTR)szName);
#endif

	return (m_pCurrentStg->Stg->DestroyElement(wcFName) == S_OK);
}

/////////////////////////////////////////////////////////////////////////////
// Inter-storage functions:

bool CSSFile::CreateStorage(const CString & name, bool enter, DWORD mode)
{
	ASSERT(m_pCurrentStg && m_bOpen);

	WCHAR wcFName[MAX_PATH];
#ifndef UNICODE
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCTSTR)name, -1, wcFName, MAX_PATH);
#else
	wcscpy(wcFName, (LPCTSTR)name);
#endif

	IStorage* pNewStorage;
	if (m_pCurrentStg->Stg->CreateStorage(wcFName, mode, 0, 0, &pNewStorage) != S_OK)
		return false;

	if (!enter)
		pNewStorage->Release();
	else
	{
		StorageData* pSD = new StorageData;
		pSD->ParentStg = m_pCurrentStg;
		pSD->Stg = pNewStorage;
		m_pCurrentStg = pSD;
	}
	
	return true;
}

bool CSSFile::EnterStorage(const CString & name, DWORD mode)
{
	ASSERT(m_pCurrentStg && m_bOpen);

	WCHAR wcFName[MAX_PATH];
#ifndef UNICODE
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCTSTR)name, -1, wcFName, MAX_PATH);
#else
	wcscpy(wcFName, (LPCTSTR)name);
#endif

	IStorage* pStg;
	if (m_pCurrentStg->Stg->OpenStorage(wcFName, NULL, mode, NULL, 0, &pStg) == S_OK)
	{
		StorageData* pSD = new StorageData;
		pSD->ParentStg = m_pCurrentStg;
		pSD->Stg = pStg;

		m_pCurrentStg = pSD;
		
		return true;
	}
	else
		return false;
}

bool CSSFile::ExitStorage()
{
	ASSERT(m_pCurrentStg && m_bOpen);

	if (m_pCurrentStg->ParentStg)
	{
		m_pCurrentStg->Stg->Release();
		StorageData* pSD = m_pCurrentStg->ParentStg;
		delete m_pCurrentStg;
		m_pCurrentStg = pSD;

		return true;
	}
	else
		return false; // no storage to exit out of without closing the file
}

/////////////////////////////////////////////////////////////////////////////
// Stream functions:

bool CSSFile::CreateStream(const CString & name, COleStreamFile & sf, DWORD mode)
{
	// note the BOOL return type being converted to bool;
	return (sf.CreateStream(m_pCurrentStg->Stg, (LPCTSTR)name, mode) == TRUE);
}

bool CSSFile::OpenStream(const CString & name, COleStreamFile & sf, DWORD mode)
{
	ASSERT(m_pCurrentStg && m_bOpen);

	return (sf.OpenStream(m_pCurrentStg->Stg, (LPCTSTR)name, mode) == TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// Status functions

bool CSSFile::IsOpen() const
{
	return m_bOpen;
}

CString CSSFile::GetFilename() const
{
	return m_strFilename;
}

CString CSSFile::GetPath(const CString & SepChar) const
{
	ASSERT(m_pCurrentStg && m_bOpen);

	StorageData* pSD = m_pCurrentStg;

	// loop through each storage in the tree and concatenate names along with the
	// separator character:
	CString strPath;
	while (pSD->ParentStg)
	{
		STATSTG sg;
		pSD->Stg->Stat(&sg, STATFLAG_DEFAULT);

		CString strTemp = sg.pwcsName;
		CoTaskMemFree((void *)sg.pwcsName);

		strPath = strTemp + SepChar + strPath;

		pSD = pSD->ParentStg; // up a level for next interation
	}

	strPath = m_strFilename + SepChar + strPath;
	return strPath;
}

IStorage * CSSFile::GetCurrentStorage() const
{
	ASSERT(m_pCurrentStg && m_bOpen);

	return m_pCurrentStg->Stg;
}

IStorage * CSSFile::GetRootStorage() const
{
	ASSERT(m_pCurrentStg && m_bOpen);

	return m_pRootStg;
}

class CLogFile : public CStdioFile
	{
public:
	bool write;
	void WriteString(const CString & string)
		{
		if (write)
			CStdioFile::WriteString(string);
		}
	void Close()
		{
		if (write)
			CStdioFile::Close();
		}
	};

void Error(const CString & message)
{
	TRACE(message + _T("\n"));
	for (int i = 0; i < message.GetLength(); i++)
		printf("%c", message[i]);
	printf("\n");
	exit(1);
}

CStringArray sst;
int sheet[2000][10];
int total;
int diff;
CLogFile dump;
int sstindex = 0;

void ExtractSSTString(int & i, unsigned short & len, char * & buf, CFile & file, int & available);

void CreateSST(unsigned short len, char * & buf, CFile & file, int & available)
{
	int i = 0;
	sstindex = 0;
	total = buf[i++] & 0xFF;
	total |= (buf[i++] & 0xFF) << 8;
	total |= (buf[i++] & 0xFF) << 16;
	total |= (buf[i++] & 0xFF) << 24;
	diff = buf[i++] & 0xFF;
	diff |= (buf[i++] & 0xFF) << 8;
	diff |= (buf[i++] & 0xFF) << 16;
	diff |= (buf[i++] & 0xFF) << 24;
TRACE(_T("Total %d, diff %d\n"), total, diff);
sst.SetSize(total);
for (int x = 0; x < total; x++)
{
  CString f;
  f.Format(_T("String %d"), x);
  sst[x] = f;
}
	while (diff-- > 0)
		{
		ExtractSSTString(i, len, buf, file, available);
		}
TRACE(_T("Strings: %d\n"), sst.GetSize());
}

void ExtractSSTString(int & i, unsigned short & len, char * & buf, CFile & file, int & available)
{
	if (i > len)
		Error("Read past block");
	if (i == len)
		{
		short id;
		file.Read(&id, sizeof(id));
		if (id != 0x003C)
			Error("CONTINUE record expected");
		file.Read(&len, sizeof(len));
		delete buf;
		buf = new char[len];
		if (file.Read(buf, len) != len)
			Error("Incomplete read");
		available -= 4;
		available -= len;
		i = 0;
		}
	int strlen = buf[i++] & 0xFF;
		strlen |= (buf[i++] & 0xFF) << 8;
		int option = buf[i++] & 0xFF;
		bool decompress = (option & 1) != 0;
		int rt = 0;
		if ((option & 8) != 0)	// rich text
			{
			rt = buf[i++] & 0xFF;
			rt |= (buf[i++] & 0xFF) << 8;
			}
		int ph = 0;
		if ((option & 4) != 0)	// phonetic
			{
			ph = buf[i++] & 0xFF;
			ph |= (buf[i++] & 0xFF) << 8;
			ph |= (buf[i++] & 0xFF) << 16;
			ph |= (buf[i++] & 0xFF) << 24;
			}
		TCHAR s[1024];
		int si = 0;
		while ((i < len) && (strlen > 0))
			{
			TCHAR ch;
			if (decompress)
				{
				int c = buf[i++] & 0xFF;
				c |= (buf[i++] & 0xFF) << 8;
				ch = c & 0xFFFF;
				}
			else
				ch = buf[i++] & 0xFF;
			s[si++] = ch;
			s[si] = 0;
			strlen--;
			}
		// check if we ran out of data
		if (strlen > 0)
			{
			short id;
			file.Read(&id, sizeof(id));
			if (id != 0x003C)
				Error("CONTINUE record expected");
			file.Read(&len, sizeof(len));
			delete buf;
			buf = new char[len];
			if (file.Read(buf, len) != len)
				Error("Incomplete read");
			available -= 4;
			available -= len;
{
CString fmt;
fmt.Format(_T("Record %04X, length %d\n"), id, len);
dump.WriteString(fmt);
for (int x = 0; x < len; x++)
	{
	if ((x != 0) && ((x & 0x1F) == 0))
		dump.WriteString(_T("\n"));
	fmt.Format(_T("%02X "), buf[x] & 0xFF);
	dump.WriteString(fmt);
	}
if ((x & 0x1F) != 0)
	dump.WriteString(_T("\n"));
dump.WriteString(_T("\n"));
}
			i = 0;
			option = buf[i++] & 0xFF;
			decompress = (option & 1) != 0;
			while ((i < len) && (strlen > 0))
				{
				short ch;
				if (decompress)
					{
					int c = buf[i++] & 0xFF;
					c |= (buf[i++] & 0xFF) << 8;
					ch = c & 0xFFFF;
					}
				else
					ch = buf[i++] & 0xFF;
				s[si++] = ch;
				s[si] = 0;
				strlen--;
				}
			}
		if (sstindex == 234)
			total++;
		i += 4 * rt;
		// out of rich text data?
		if (i > len)
			{
//			dump.Close();
			i -= len;
			short id;
			file.Read(&id, sizeof(id));
			if (id != 0x003C)
				Error("CONTINUE record expected");
			file.Read(&len, sizeof(len));
			delete buf;
			buf = new char[len];
			if (file.Read(buf, len) != len)
				Error("Incomplete read");
			available -= 4;
			available -= len;
{
CString fmt;
fmt.Format(_T("Record %04X, length %d\n"), id, len);
dump.WriteString(fmt);
for (int x = 0; x < len; x++)
	{
	if ((x != 0) && ((x & 0x1F) == 0))
		dump.WriteString(_T("\n"));
	fmt.Format(_T("%02X "), buf[x] & 0xFF);
	dump.WriteString(fmt);
	}
if ((x & 0x1F) != 0)
	dump.WriteString(_T("\n"));
dump.WriteString(_T("\n"));
}
			}
		i += ph;
		if (i > len)
			{
			i -= len;
			short id;
			file.Read(&id, sizeof(id));
			if (id != 0x003C)
				Error("CONTINUE record expected");
			file.Read(&len, sizeof(len));
			delete buf;
			buf = new char[len];
			if (file.Read(buf, len) != len)
				Error("Incomplete read");
			available -= 4;
			available -= len;
{
CString fmt;
fmt.Format(_T("Record %04X, length %d\n"), id, len);
dump.WriteString(fmt);
for (int x = 0; x < len; x++)
	{
	if ((x != 0) && ((x & 0x1F) == 0))
		dump.WriteString(_T("\n"));
	fmt.Format(_T("%02X "), buf[x] & 0xFF);
	dump.WriteString(fmt);
	}
if ((x & 0x1F) != 0)
	dump.WriteString(_T("\n"));
dump.WriteString(_T("\n"));
}
			}
{
CString fmt;
fmt.Format(_T("Assigning SST %5d, old value %s\n"), sstindex, sst[sstindex]);
dump.WriteString(fmt);
}
	sst[sstindex++] = s;
{
for (int i = 0; s[i] != 0; i++)
	{
	CString f;
	f.Format(_T("%04X "), s[i] & 0xFFFF);
	dump.WriteString(f);
	}
dump.WriteString("\n");
}
}

void CreateLabelSST(int len, char buf[])
{
	int i = 0;
	int row = buf[i++] & 0xFF;
	row |= (buf[i++] & 0xFF) << 8;
	int col = buf[i++] & 0xFF;
	col |= (buf[i++] & 0xFF) << 8;
	int xfi = buf[i++] & 0xFF;
	xfi |= (buf[i++] & 0xFF) << 8;
	int ssti = buf[i++] & 0xFF;
	ssti |= (buf[i++] & 0xFF) << 8;
	ssti |= (buf[i++] & 0xFF) << 16;
	ssti |= (buf[i++] & 0xFF) << 24;
	sheet[row][col] = ssti;
CString fmt;
fmt.Format(_T("LABELSST (row %4d, col %2d), "), row, col);
dump.WriteString(fmt);
{
CString s = sst[ssti];
for (int i = 0; i < s.GetLength(); i++)
	{
	CString f;
	f.Format(_T("%04X "), s[i] & 0xFFFF);
	dump.WriteString(f);
	}
dump.WriteString("\n");
}
}

void PrintByteString(CStdioFile & file, int idx)
{
	file.WriteString(_T("\""));
	if (idx != -1)
		{
		CString & s = sst[idx];
		for (int i = 0; i < s.GetLength(); i++)
			{
			TCHAR ch = s[i];
			if (ch == '"')
				file.WriteString(_T("\\\""));
			else if (ch == '\\')
				file.WriteString(_T("\\"));
			else
				file.WriteString(CString((char) ch));
			}
		}
	file.WriteString(_T("\""));
}

void PrintWordString(CStdioFile & file, int idx)
{
	file.WriteString(_T("\""));
	if (idx != -1)
		{
		CString & s = sst[idx];
		for (int i = 0; i < s.GetLength(); i++)
			{
			TCHAR ch = s[i];
			int u = ((int) ch) >> 8;
			int l = ((int) ch) & 0xFF;
			CString f;
			f.Format(_T("\\x%x\\x%x"), u & 0xFF, l & 0xFF);
			file.WriteString(f);
			}
		}
	file.WriteString(_T("\\x0\""));
}

void PrintString(CStdioFile & file, int row)
{
	CString & s = sst[sheet[row][0]];
	file.WriteString(_T("const STR * const ") + s + _T("[] = {\n"));
	for (int col = 1; col < 10; col++)
		{
		if (col > 1)
			file.WriteString(_T(",\n"));
		file.WriteString(_T("         "));
		if (col <= 5)
			PrintByteString(file, sheet[row][col]);
		else
			PrintWordString(file, sheet[row][col]);
		}
	file.WriteString(_T(" };\n\n"));
}

void ProcessAlarmPage(CString & xls, CString & out)
{
	CStdioFile file;
	if (!file.Open(out, CFile::modeCreate | CFile::modeWrite))
		Error("Can't create output file '" + out + "'");
	file.WriteString(_T("// Automatically generated from ") + xls + _T("\n"));
	file.WriteString(_T("#include \"portable.h\"\n"));
	file.WriteString(_T("\n"));
	file.WriteString(_T("#pragma section CONST  \".lang\"\n"));
	file.WriteString(_T("#pragma section STRING \".lang\"\n"));
	file.WriteString(_T("#pragma section CODE   \".lang\"\n"));
	file.WriteString(_T("\n"));
	// ignore top line with language names
	for (int row = 1; sheet[row][0] != -1; row++)
		PrintString(file, row);
	file.Close();
}

bool FilesEqual(CString & newFile, CString & oldFile)
{
	CFile n;
	if (!n.Open(newFile, CFile::modeRead))
		Error("Can't reopen new file");
	CFile o;
	if (!o.Open(oldFile, CFile::modeRead))
		return false;
	// cheap shortcut to detect changes
	if (n.GetLength() != o.GetLength())
		return false;
	char nbuf[16384];
	char obuf[sizeof(nbuf)];
	int available = n.GetLength();
	while (available > 0)
		{
		int len = sizeof(nbuf);
		if (available < len)
			len = available;
		available -= len;
		n.Read(nbuf, len);
		o.Read(obuf, len);
		if (memcmp(nbuf, obuf, len) != 0)
			return false;
		}
	return true;
}

void CompareReplaceFiles(CString & newFile, CString & oldFile)
{
	try
		{
		if (FilesEqual(newFile, oldFile))
			CFile::Remove(newFile);
		else
			{
			try
				{
				CFile::Remove(oldFile);
				}
			catch (CFileException *)
				{
//can't!				delete e;
				}
			CFile::Rename(newFile, oldFile);
			}
		}
	catch (CFileException *)
		{
		TRACE(_T("Catch 2\n"));
		}
}

void ProcessMenuPage(CString & xls, CString & out)
{
	CStdioFile file;
	if (!file.Open(out, CFile::modeCreate | CFile::modeWrite))
		Error("Can't create output file '" + out + "'");
	file.WriteString(_T("// Automatically generated from ") + xls + _T("\n"));
	file.WriteString(_T("#include \"portable.h\"\n"));
	file.WriteString(_T("#include \"menu.h\"\n"));
	file.WriteString(_T("\n"));
	file.WriteString(_T("#define LANGSIZETEXT 9\n"));
	file.WriteString(_T("\n"));
	file.WriteString(_T("#pragma section CONST  \".lang\"\n"));
	file.WriteString(_T("#pragma section STRING \".lang\"\n"));
	file.WriteString(_T("#pragma section CODE   \".lang\"\n"));
	file.WriteString(_T("\n"));
	// ignore top line with language names
	int row;
	for (row = 1; sheet[row][0] != -1; row++)
		{
		CString & s = sst[sheet[row][0]];
		if (s == CString("WeldDataStrPtr0"))
			break;
		PrintString(file, row);
		}
	// 'row' points to the horizontal variable row
	file.WriteString(CString("const STR * const WeldDataStrPtr[RMAXPARAMETERS][LANGSIZETEXT] = {"));
	bool first = true;
	CString & s = sst[sheet[row][0]];
	while (s.Left(14) == CString("WeldDataStrPtr"))
		{
		if (first)
			first = false;
		else
			file.WriteString(CString(","));
		for (int col = 1; col < 10; col++)
			{
			if (col == 1)
				file.WriteString(_T("\n      {  "));
			else
				file.WriteString(_T(",\n         "));
			if (col <= 5)
				PrintByteString(file, sheet[row][col]);
			else
				PrintWordString(file, sheet[row][col]);
			}
		file.WriteString(_T(" }"));
		row++;
		s = sst[sheet[row][0]];
		}
	file.WriteString(_T(" };\n\n"));
	while (sheet[row][0] != -1)
		{
		PrintString(file, row);
		row++;
		}
	file.Close();
}

void PrintLanguageArray(CStdioFile & file, int row, int rows, int col, CString & prefix, CString lang)
{
	file.WriteString("const STR * const " + prefix + lang + "[] = {\n");
	for (int r = 0; r < rows; r++)
		{
		file.WriteString(_T("      "));
		if (col <= 5)
			PrintByteString(file, sheet[row + r][col]);
		else
			PrintWordString(file, sheet[row + r][col]);
		file.WriteString(_T(",\n"));
		}
	file.WriteString(_T(" };\n\n"));
}

int ProcessPrintArray(int row, CStdioFile & file, CString prefix)
{
	int rows = 0;
	CString s = sst[sheet[row + rows][0]];
	while (s.Left(prefix.GetLength()) == prefix)
		{
		CString p = sst[sheet[row + rows][0]];
		int ch = p[prefix.GetLength()];
		if (!isdigit(ch))
			break;
		rows++;
		s = sst[sheet[row + rows][0]];
		}
	PrintLanguageArray(file, row, rows, 1, prefix, _T("Eng"));
	PrintLanguageArray(file, row, rows, 2, prefix, _T("Ger"));
	PrintLanguageArray(file, row, rows, 3, prefix, _T("Spn"));
	PrintLanguageArray(file, row, rows, 4, prefix, _T("Itl"));
	PrintLanguageArray(file, row, rows, 5, prefix, _T("Fr"));
	PrintLanguageArray(file, row, rows, 6, prefix, _T("ChS"));
	PrintLanguageArray(file, row, rows, 7, prefix, _T("ChT"));
	PrintLanguageArray(file, row, rows, 8, prefix, _T("Jpn"));
	PrintLanguageArray(file, row, rows, 9, prefix, _T("Kor"));
	file.WriteString("const STR ** " + prefix + "[] = { " +
					prefix + "Eng, " +
					prefix + "Ger, " +
					prefix + "Spn, " +
					prefix + "Itl, " +
					prefix + "Fr, " +
					prefix + "ChS, " +
					prefix + "ChT, " +
					prefix + "Jpn, " +
					prefix + "Kor };\n\n");
	return row + rows;
}

bool IsValidIdentifier(const CString & id)
{
	if (id.GetLength() == 0)
		return false;
	if (id[0] > 0x7E)
		return false;
	if (!isalpha(id[0]) && (id[0] != '_'))
		return false;
	for (int i = 1; i < id.GetLength(); i++)
		{
		if (id[i] == '_')
			continue;
		if (!isalnum(id[i]))
			return false;
		}
	return true;
}

void ProcessPrintPage(CString & xls, CString & out)
{
	CStdioFile file;
	if (!file.Open(out, CFile::modeCreate | CFile::modeWrite))
		Error("Can't create output file '" + out + "'");
	file.WriteString(_T("// Automatically generated from ") + xls + _T("\n"));
	file.WriteString(_T("#include \"portable.h\"\n"));
	file.WriteString(_T("\n"));
	file.WriteString(_T("#pragma section CONST  \".lang\"\n"));
	file.WriteString(_T("#pragma section STRING \".lang\"\n"));
	file.WriteString(_T("#pragma section CODE   \".lang\"\n"));
	file.WriteString(_T("\n"));

	// ignore top line with language names
	int row = 1;
	row = ProcessPrintArray(row, file, _T("Mess"));
	row = ProcessPrintArray(row, file, _T("PrintMess"));
	row = ProcessPrintArray(row, file, _T("Alarm"));
	row = ProcessPrintArray(row, file, _T("AlarmMess"));
	row = ProcessPrintArray(row, file, _T("Alarm_"));
	// and all the rest
	while (sheet[row][0] != -1)
		{
		CString id = sst[sheet[row][0]];
		if (!IsValidIdentifier(id))
			{
			row++;
			continue;
			}
CString f;
f.Format(_T("row %d, title %d - %s\n"), row, sheet[row][0], sst[sheet[row][0]]);
dump.WriteString(f);
		PrintString(file, row);
		row++;
		}
	file.Close();
}

void ProcessEOF(int pass, CString & xls)
{
	switch (pass)
		{
	case 0 :	// string table processed OK
		break;
	case 1 :	// Alarms page
		ProcessAlarmPage(xls, CString("alarmtxt1.txt"));
		CompareReplaceFiles(CString("alarmtxt1.txt"), CString("alarmtxt1.c"));
		break;
	case 2 :	// Menus page
		ProcessMenuPage(xls, CString("menutxt1.txt"));
		CompareReplaceFiles(CString("menutxt1.txt"), CString("menutext1.c"));
		break;
	case 3 :	// Print page
		ProcessPrintPage(xls, CString("pr_txt1.txt"));
		CompareReplaceFiles(CString("pr_txt1.txt"), CString("pr_text1.c"));
		break;
		}
	// reinitialize the map, safe even after print page
	memset(sheet, -1, sizeof(sheet));
}

short id_old;

int main(int argc, char * argv[])
{
	CString name = argv[1];
	CSSFile ssf;
	if (!ssf.OpenSSFile(name, STGM_DIRECT | STGM_READ | STGM_SHARE_DENY_WRITE))
		Error("Can't open file '" + name + "'");
	COleStreamFile file;
	if (!ssf.OpenStream("Workbook", file, STGM_READ | STGM_SHARE_EXCLUSIVE))
		Error("Error opening workbook");
	int available = file.GetLength();
	memset(&sheet, 0xFF, sizeof(sheet));
	int eof = 0;

	if (argc >= 3)
		{
		if (!dump.Open(CString(argv[2]), CFile::modeWrite | CFile::modeCreate))
			Error("Log create error");
		dump.write = true;
		}
	else
		dump.write = false;
dump.WriteString("Yoohoo!\n");
	while (available > 0)
		{
		short id;
		file.Read(&id, sizeof(id));
		unsigned short len;
		file.Read(&len, sizeof(len));
		available -= 4;
		char * buf = 0;
		if (len > 0)
			{
			buf = new char[len];
			if (file.Read(buf, len) != len)
				Error("Incomplete read");
			}
		available -= len;

if (id == 0x003C)
	dump.WriteString(_T("\nThis is the unexpected 'Continue':\n"));
CString fmt;
fmt.Format(_T("Record %04X, length %d\n"), id, len);
dump.WriteString(fmt);
for (int x = 0; x < len; x++)
	{
	if ((x != 0) && ((x & 0x1F) == 0))
		dump.WriteString(_T("\n"));
	CString s;
	s.Format(_T("%02X "), buf[x] & 0xFF);
	dump.WriteString(s);
	}
if ((x & 0x1F) != 0)
	dump.WriteString(_T("\n"));
dump.WriteString(_T("\n"));
		switch (id)
			{
		case 0x00FC :	// SST
			CreateSST(len, buf, file, available);
			break;
		case 0x003C :	// CONTINUE
			Error("Unexpected CONTINUE record");
			break;
		case 0x00FD :	// LABELSST
			CreateLabelSST(len, buf);
			break;
		case 0x000A :	// EOF
			ProcessEOF(eof++, CString(argv[1]));
			break;
			}
		id_old = id;
		if (len > 0)
			delete buf;
		}
	dump.Close();

	return 0;
}
