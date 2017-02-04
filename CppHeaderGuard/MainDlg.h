// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include "IncludeGen.h"

#define INCLHG_DLG_BKGCOLOR RGB(198,209,223)

class CMainDlg : public CDialogImpl<CMainDlg>, public CSnapWindow<CMainDlg>, public CDialogDrag<CMainDlg>,
	public CDropFileTarget<CMainDlg>

{
public:
	enum { IDD = IDD_MAINDLG };

	CIncludeGen m_inclgen;

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG,	OnInitDialog)
		MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColor)
		MESSAGE_HANDLER(WM_CTLCOLORDLG, OnMainDialogColor)
		COMMAND_ID_HANDLER(IDOK,		OnOK)
		COMMAND_ID_HANDLER(IDCANCEL,	OnCancel)
		COMMAND_ID_HANDLER(IDC_NEWINCLG, OnNewIncludeGuard)
		COMMAND_ID_HANDLER(IDC_COPY, OnCopy)
		COMMAND_ID_HANDLER(IDC_HELP1, OnHelp)
	CHAIN_MSG_MAP(CSnapWindow<CMainDlg>)
	CHAIN_MSG_MAP(CDialogDrag<CMainDlg>)
	CHAIN_MSG_MAP(CDropFileTarget<CMainDlg>)
	END_MSG_MAP()

	CMainDlg();
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCtlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMainDialogColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnNewIncludeGuard(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCopy(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnHelp(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	bool ProcessDropFile(LPCTSTR dropfile);
	bool parseCmd();
	bool IsClearTypeEnabled();
	bool createEditCtlFont();

	CBrush m_dialogbrush;
	CFont m_editCtlFont;
	CString m_resfile;
	bool m_showhelp;

};
