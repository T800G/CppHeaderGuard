#ifndef _D23CB4C9BD14475fB5AE2F1EC54251EE_
#define _D23CB4C9BD14475fB5AE2F1EC54251EE_
#pragma once
#ifndef _UNICODE
	#error C_SplitPath is UNICODE-only class
#endif
#include <math.h>

class C_SplitPath				//path composing fcs???
{
public:
    C_SplitPath(LPCTSTR lpszPath = NULL);

    BOOL Split(LPCTSTR lpszPath );

	CString filetitle,fullpath, drive, dir, filename, ext, ext_nodot;

	errno_t SplPstatus;

private:
	void SplitPathInitialize();
    TCHAR drive0[_MAX_DRIVE];
    TCHAR dir0[_MAX_DIR];
    TCHAR fname0[_MAX_FNAME];
    TCHAR ext0[_MAX_EXT];
};
#endif
