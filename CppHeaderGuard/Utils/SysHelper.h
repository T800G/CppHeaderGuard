#ifndef _A0ACD23B_2706_4c54_9B9D_41118401139E_
#define _A0ACD23B_2706_4c54_9B9D_41118401139E_
#pragma once
#ifndef __ATLBASE_H__
	#error _SYS_helper800 is WTL-dependent namespace
#endif


namespace __SYS_helper800
{
	class CBusyCursor
	{
	public:
		CBusyCursor(){cur_new=::LoadCursor(NULL, IDC_WAIT); cur_old=::SetCursor(cur_new);}
		virtual ~CBusyCursor(){cur_new=::SetCursor(cur_old);}

		CCursor cur_new, cur_old;
	};


	void GetLastError_Verbose(LPTSTR lpszFunction) //global fcs must be static
		{
			CString szBuf, szBuf2; 
			LPVOID lpMsgBuf;
			DWORD dw = GetLastError(); 
			szBuf2.Append(dw);

			FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				dw,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR) &lpMsgBuf,
				0, NULL );

			szBuf=lpszFunction;
			szBuf+=_T(" failed with error code");
			szBuf+=szBuf2;
			szBuf+=_T(": ");	 
			szBuf+=(LPTSTR)lpMsgBuf; 
		 
			MessageBox(NULL, szBuf, _T("_Debug"), MB_OK); 

			LocalFree(lpMsgBuf);
		}

	/**Resolves a Shell link object (shortcut)**************************
	* Parameters:	lpszShortcutPath - string that specifies a path and file name of a shortcut
	*				lpszFilePath - string that will contain a file name
	* Returns:		S_OK on success, error code on failure
	*********************************************************************/
	//"static" - linker error LNK2005 workaround
	static HRESULT ResolveShellShortcut(/*in*/ LPCTSTR lpszShortcutPath,
							/*out*/ LPTSTR lpszFilePath)
	{
		HRESULT hRes = E_FAIL;
		CComPtr<IShellLink> ipShellLink;
		// buffer that receives the null-terminated stringfor the drive and path
		TCHAR szPath[MAX_PATH];     
		// buffer that receives the null-terminated string for the description
		TCHAR szDesc[MAX_PATH]; 
		// structure that receives the information about the shortcut
		WIN32_FIND_DATA wfd;    
		WCHAR wszTemp[MAX_PATH];

		lpszFilePath[0] = '\0';

		// Get a pointer to the IShellLink interface
		hRes = CoCreateInstance(CLSID_ShellLink,NULL,CLSCTX_INPROC_SERVER,IID_IShellLink,(void**)&ipShellLink); 

		if (SUCCEEDED(hRes)) 
		{ 
			// Get a pointer to the IPersistFile interface
			CComQIPtr<IPersistFile> ipPersistFile(ipShellLink);

// IPersistFile is using LPCOLESTR,so make sure that the string is Unicode
#if !defined _UNICODE
		#error this file requires UNICODE
#endif
			wcsncpy_s(wszTemp, MAX_PATH, lpszShortcutPath, MAX_PATH);

			// Open the shortcut file and initialize it from its contents
			hRes = ipPersistFile->Load(wszTemp, STGM_READ); 
			if (SUCCEEDED(hRes)) 
			{
				// Try to find the target of a shortcut,even if it has been moved or renamed
				hRes = ipShellLink->Resolve(NULL, SLR_UPDATE); 
				if (SUCCEEDED(hRes)) 
				{
					// Get the path to the shortcut target
					//Returns NOERROR if the operation is successful and a valid path is retrieved. 
					//If the operation is successful, but no path is retrieved, 
					//it returns S_FALSE and pszFile will be empty.
					hRes = ipShellLink->GetPath(szPath, MAX_PATH, &wfd, SLGP_RAWPATH); 
					if (hRes != NOERROR) return hRes;

					// Get the description of the target
					hRes = ipShellLink->GetDescription(szDesc,MAX_PATH); 

					 if (hRes != NOERROR) return hRes;

					lstrcpyn(lpszFilePath, szPath, MAX_PATH); 
				} 
			} 
		} 
	return hRes;
	}




}
#endif//_A0ACD23B_2706_4c54_9B9D_41118401139E_
