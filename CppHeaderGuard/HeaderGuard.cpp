// HeaderGuard.cpp : main source file for HeaderGuard.exe
//

#include "stdafx.h"
#include "SingleInstance.h"
#include "resource.h"

#include "MainDlg.h"

CAppModule _Module;

CLimitSingleInstance g_SingleInstanceObj(TEXT("Global\\{D8BAD0D1-A42D-4a77-B7BE-33A9D989E6F6}"));

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{

	//limit app to single instance
	if (g_SingleInstanceObj.IsAnotherInstanceRunning()) return FALSE;

	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = 0;
	// BLOCK: Run application
	{
		CMainDlg dlgMain;
		nRet = dlgMain.DoModal();
	}

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
