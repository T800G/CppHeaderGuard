#include "stdafx.h"
#include "PathSplitter.h"

C_SplitPath::C_SplitPath(LPCTSTR lpszPath){	SplitPathInitialize();if (lpszPath) Split(lpszPath);}

BOOL C_SplitPath::Split(LPCTSTR lpszPath)
{
	SplitPathInitialize();
	if (lpszPath == NULL) return FALSE;
	SplPstatus=_wsplitpath_s(lpszPath, drive0, _MAX_DRIVE, dir0, _MAX_DIR, fname0, _MAX_FNAME, ext0, _MAX_EXT);
	fullpath=lpszPath;
    drive=drive0;
    dir=dir0;
    filename=fname0;
    ext_nodot=ext=ext0;
	ext_nodot.Delete(0,1);

	filetitle+=filename;
	filetitle+=ext;
return ((SplPstatus!=EINVAL) && (SplPstatus!=ERANGE));
}

void C_SplitPath::SplitPathInitialize()
{
    wmemset(drive0, 0, _MAX_DRIVE);//init
    wmemset(dir0, 0, _MAX_DIR);
    wmemset(fname0, 0, _MAX_FNAME);
    wmemset(ext0, 0, _MAX_EXT);
	SplPstatus=NULL;
	fullpath.Empty();
    drive.Empty();
    dir.Empty();
    filename.Empty();
    ext.Empty();
	ext_nodot.Empty();
	filetitle.Empty();
}
