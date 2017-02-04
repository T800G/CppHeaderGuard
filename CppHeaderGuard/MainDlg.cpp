// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "HelpData.h"
#include "MainDlg.h"

#pragma comment(lib, "user32.lib")

bool CMainDlg::IsClearTypeEnabled()
{
	BOOL check=0;
	if (!SystemParametersInfo(SPI_GETFONTSMOOTHING, 0, &check,0)) return false;
	if (!check) return false;
	UINT check2=0;
	if (!SystemParametersInfo(SPI_GETFONTSMOOTHINGTYPE, 0, &check2,0)) return false;
return (check2==FE_FONTSMOOTHINGCLEARTYPE);
}

bool CMainDlg::createEditCtlFont()
{
	m_editCtlFont=(HFONT)GetStockObject(DEFAULT_GUI_FONT);
	if (m_editCtlFont.IsNull()) return false;

	LOGFONT lfont={0};
	if (0==GetObject(m_editCtlFont,sizeof(LOGFONT), &lfont)) return false;

	if (IsClearTypeEnabled())
	 lfont.lfQuality=CLEARTYPE_QUALITY;
	lfont.lfPitchAndFamily=FIXED_PITCH | FF_MODERN;
	WCHAR fn[32]=L"Courier New";
	lfont.lfHeight=(LONG)(lfont.lfHeight*1.15);//increase size a bit
	memcpy(lfont.lfFaceName, fn, _countof(fn));

	m_editCtlFont.DeleteObject();
	if (NULL==m_editCtlFont.CreateFontIndirect(&lfont)) return false;
return true;
}

CMainDlg::CMainDlg()
{
	m_dialogbrush.CreateSolidBrush(INCLHG_DLG_BKGCOLOR);
	m_showhelp=false;
}
LRESULT CMainDlg::OnHelp(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (!m_showhelp)
	{
		::SetWindowTextW(GetDlgItem(IDC_EDIT1), helptext);
		m_showhelp=true;
	}
	else
	{
		::SetWindowTextW(GetDlgItem(IDC_EDIT1), m_inclgen.GetIncludeGuardText());
		m_showhelp=false;
	}
return 0;
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	//temporary CRect
	CenterWindow();
	RegisterDropTarget();

	if (!parseCmd()) {BOOL dummy; OnNewIncludeGuard(0,0,0,dummy);}

	if (createEditCtlFont())
	 ::SendMessage(GetDlgItem(IDC_EDIT1), WM_SETFONT, (WPARAM)m_editCtlFont.m_hFont, TRUE);
	//set txt inner margin
	::SendMessage(GetDlgItem(IDC_EDIT1), (UINT)EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, (LPARAM)6);

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
								IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
								IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

	//{CRect rct; SetWindowPos(HWND_TOPMOST,rct, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE );}

	GotoDlgCtrl(GetDlgItem(IDOK));
return FALSE;//leave TRUE if we let the dialog to set focus
}
LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/){m_inclgen.copy2clipboard(m_hWnd);EndDialog(wID);return 0;}
LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/){EndDialog(wID);return 0;}
LRESULT CMainDlg::OnCopy(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/){m_inclgen.copy2clipboard(m_hWnd);return 0;}

bool CMainDlg::parseCmd()
{
	bool ret=false;
	LPWSTR *szArglist;
	int argc;

	szArglist = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (NULL != szArglist)
	 {
		if (argc>1) ret=ProcessDropFile(szArglist[1]);
	 }
	else MessageBox(_T("Command line parsing failed"),_T("Fatal Error"),MB_OK | MB_TASKMODAL | MB_ICONERROR);

	LocalFree(szArglist);
return ret;
}

bool CMainDlg::ProcessDropFile(LPCTSTR dropfile)
{

	C_SplitPath pathSplitter(dropfile);
	pathSplitter.ext_nodot.MakeLower();
	if (pathSplitter.ext_nodot==_T("lnk"))//resolve shell shortcuts
	{
	TCHAR resolvedPath[MAX_PATH];
	if (S_OK!=__SYS_helper800::ResolveShellShortcut(dropfile,resolvedPath)) return false;
	dropfile=resolvedPath;
	}

	m_inclgen.generate(dropfile);
	::SetWindowTextW(GetDlgItem(IDC_EDIT1), m_inclgen.GetIncludeGuardText());
	m_showhelp=false;
return true;
}

LRESULT CMainDlg::OnCtlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if ( ((HWND)lParam)==GetDlgItem(IDC_EDIT1) ) 
		return (LRESULT)GetStockObject( WHITE_BRUSH );

return ::DefWindowProc(m_hWnd, wParam, lParam, bHandled);
}
LRESULT CMainDlg::OnMainDialogColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
return (LRESULT)m_dialogbrush.m_hBrush;
}

LRESULT CMainDlg::OnNewIncludeGuard(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_inclgen.generate();
	::SetWindowTextW(GetDlgItem(IDC_EDIT1), m_inclgen.GetIncludeGuardText());
	m_showhelp=false;
return 0;
}


//LRESULT CMainDlg::OnTopWindow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//{
//	AppCfg.alwaysOntop=!AppCfg.alwaysOntop;
//	CRect rct;
//	SetWindowPos((AppCfg.alwaysOntop ? HWND_TOPMOST : HWND_NOTOPMOST),
//						rct, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE );
//
////UpdateLayout();//???
//return 0;
//}
