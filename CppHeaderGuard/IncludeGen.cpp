#include "StdAfx.h"
#include "IncludeGen.h"


CIncludeGen::CIncludeGen(void)
{
	m_text="test";
}
void CIncludeGen::generate(LPCTSTR headerfile)//new
{
	CString inclh;

	if (headerfile!=NULL)
	{
	pathsplitter.Split(headerfile);
	pathsplitter.filename.MakeUpper();
	pathsplitter.filename.Replace(_T("."),_T("_"));
	}

	if (!pathsplitter.filename.IsEmpty()) inclh+=pathsplitter.filename+_T("_");
	inclh+=CreateGuid();
	m_text.Empty();
	m_text+=_T("#ifndef _")+inclh+_T("_\r\n#define _")+inclh+_T("_\r\n\r\n\r\n\r\n#endif//_")+inclh+_T("_\r\n");

}

CString CIncludeGen::CreateGuid()
{
	TCHAR fmtGuid[] = _T("%08lx_%04x_%04x_%02x%02x_%02x%02x%02x%02x%02x%02x");
	GUID guid;
	CoCreateGuid(&guid);
	CString str;
	str.Format(fmtGuid, guid.Data1,guid.Data2,guid.Data3,
						guid.Data4[0],	guid.Data4[1], guid.Data4[2], guid.Data4[3],
						guid.Data4[4],	guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	str.MakeUpper();
return str;
}

bool CIncludeGen::copy2clipboard(HWND clipbrdowner)
{
	if (m_text.IsEmpty()) return false;

	bool retVal=true;
	if(::OpenClipboard(clipbrdowner))
	{

		LPTSTR  lptstrCopy;
		LPCTSTR txt=m_text;
		HGLOBAL hglbCopy;

		::EmptyClipboard();

		hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (m_text.GetLength() + 1) * sizeof(TCHAR));
		if (hglbCopy != NULL)
		{
			lptstrCopy = (LPTSTR)GlobalLock(hglbCopy);

	        memcpy(lptstrCopy, txt, (m_text.GetLength() * sizeof(TCHAR))); 
			lptstrCopy[m_text.GetLength()] = (TCHAR) 0;    // null character 
			GlobalUnlock(hglbCopy); 


			if (NULL==::SetClipboardData(CF_UNICODETEXT, hglbCopy)) MessageBeep(-1);
		}
		else retVal=false;

	::CloseClipboard();
	}
	else retVal=false;
return retVal;
}