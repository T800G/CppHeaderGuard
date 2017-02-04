#pragma once

template <class T> class CDialogDrag
{
public:

		BEGIN_MSG_MAP(CSnapWindow<T>)
			MESSAGE_HANDLER(WM_NCHITTEST, OnNCHitTest)
		END_MSG_MAP()

	LRESULT OnNCHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT wrs=::DefWindowProcW(pT->m_hWnd, uMsg, wParam, lParam);
		if (wrs == HTCLIENT && ::GetAsyncKeyState(MK_LBUTTON) < 0) return HTCAPTION;
	return wrs;
	}
};
