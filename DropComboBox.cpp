// DropComboBox.cpp : implementation file
//
// Autocompleting combo-box (like the URL edit box in netscape)
// that accepts dropped files
//
// Written by Chris Maunder (chrismaunder@codeguru.com)
// Copyright (c) 1998.
//
//	Drop edit stuff taken from "CDropEdit"
//	Copyright 1997 Chris Losinger
//
//	shortcut expansion code modified from :
//	CShortcut, 1996 Rob Warner
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file 
// (in whatever form you wish).
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage whatsoever.
//
// Expect bugs.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 
//
// Modified: 12 Sep 1998 Setting correct cursor position after 
//                       auto-complete: Petr Stejskal and Ryan Schneider
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DropComboBox.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <afxdisp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropComboBox

CDropComboBox::CDropComboBox()
{
	m_bAutoComplete = TRUE;
	m_bAllowFiles   = TRUE;
    m_bAllowDirs    = TRUE;
    m_nMaxFiles     = 10;
    m_bNoRepeats    = TRUE;

    // Initialize OLE libraries
	m_bMustUninitOLE = FALSE;
    _AFX_THREAD_STATE* pState = AfxGetThreadState();
    if (!pState->m_bNeedTerm)
	{
		SCODE sc = ::OleInitialize(NULL);
		if (FAILED(sc))
            AfxMessageBox(_T("OLE initialization failed. Make sure that the OLE libraries are the correct version"));
		else
			m_bMustUninitOLE = TRUE;
	}
}

CDropComboBox::~CDropComboBox()
{
	// Uninitialize OLE support
	if (m_bMustUninitOLE)
		::OleUninitialize();
}


BEGIN_MESSAGE_MAP(CDropComboBox, CComboBox)
	//{{AFX_MSG_MAP(CDropComboBox)
	ON_CONTROL_REFLECT(CBN_EDITUPDATE, OnEditUpdate)
    ON_MESSAGE(CB_ADDSTRING, OnAddString)
    ON_MESSAGE(CB_INSERTSTRING, OnInsertString)
	ON_WM_CREATE()
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropComboBox message handlers

BOOL CDropComboBox::PreTranslateMessage(MSG* pMsg)
{
	// Need to check for backspace/delete. These will modify the text in
	// the edit box, causing the auto complete to just add back the text
	// the user has just tried to delete. 

	if (pMsg->message == WM_KEYDOWN)
	{
		m_bAutoComplete = TRUE;

		int nVirtKey = (int) pMsg->wParam;
		if (nVirtKey == VK_DELETE || nVirtKey == VK_BACK)
			m_bAutoComplete = FALSE;
	}

	return CComboBox::PreTranslateMessage(pMsg);
}

LONG CDropComboBox::OnAddString(UINT /*wParam*/, LONG lParam)
{
    LPCTSTR lpszText = (LPCTSTR)lParam;

    int nIndex = CheckRepeats(lpszText);
    if (nIndex != CB_ERR)
        return nIndex;

    CheckOverflow();

    LONG lResult = Default();

    RecalcDropWidth();

    return lResult;
}

LONG CDropComboBox::OnInsertString(UINT /*wParam*/, LONG lParam)
{
    LPCTSTR lpszText = (LPCTSTR)lParam;

    int nIndex = CheckRepeats(lpszText);
    if (nIndex != CB_ERR)
        return nIndex;

    CheckOverflow();

    LONG lResult = Default();

    RecalcDropWidth();

    return lResult;
}

void CDropComboBox::OnEditUpdate() 
{
  // if we are not to auto update the text, get outta here
  if (!m_bAutoComplete) 
      return;

  // Get the text in the edit box
  CString str;
  GetWindowText(str);
  int nLength = str.GetLength();
  
  // Currently selected range
  DWORD dwCurSel = GetEditSel();
  WORD dStart = LOWORD(dwCurSel);
  WORD dEnd   = HIWORD(dwCurSel);

  // Search for, and select in, and string in the combo box that is prefixed
  // by the text in the edit box
  if (SelectString(-1, str) == CB_ERR)
  {
      SetWindowText(str);		// No text selected, so restore what was there before
      if (dwCurSel != CB_ERR)
        SetEditSel(dStart, dEnd);	//restore cursor postion
  }

  // Set the text selection as the additional text that we have added
  if (dEnd < nLength && dwCurSel != CB_ERR)
      SetEditSel(dStart, dEnd);
  else
      SetEditSel(nLength, -1);
}

int CDropComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	DragAcceptFiles(TRUE);
	
	return 0;
}


//	handle WM_DROPFILES
//

void CDropComboBox::OnDropFiles(HDROP dropInfo)
{
	// Get the number of pathnames that have been dropped
	WORD wNumFilesDropped = DragQueryFile(dropInfo, -1, NULL, 0);

	CString firstFile="";

	// get all file names. but we'll only need the first one.
	for (WORD x = 0 ; x < wNumFilesDropped; x++) {

		// Get the number of bytes required by the file's full pathname
		WORD wPathnameSize = DragQueryFile(dropInfo, x, NULL, 0);

		// Allocate memory to contain full pathname & zero byte
		char * npszFile = (char *) LocalAlloc(LPTR, wPathnameSize += 1);

		// If not enough memory, skip this one
		if (npszFile == NULL) continue;

		// Copy the pathname into the buffer
		DragQueryFile(dropInfo, x, npszFile, wPathnameSize);

		// we only care about the first
		if (firstFile=="")
			firstFile=npszFile;

		// clean up
		LocalFree(npszFile);
	}

	// Free the memory block containing the dropped-file information
	DragFinish(dropInfo);

	// if this was a shortcut, we need to expand it to the target path
	CString expandedFile = ExpandShortcut(firstFile);

	// if that worked, we should have a real file name
	if (expandedFile!="") 
		firstFile=expandedFile;

	
	struct _stat buf;
	// get some info about that file
	int result = _stat( firstFile, &buf );
	if( result == 0 ) {

		// verify that we have a dir (if we want dirs)
		if ((buf.st_mode & _S_IFDIR) == _S_IFDIR) 
        {
			if (m_bAllowDirs)
				SetWindowText(firstFile);
            SetEditSel(firstFile.GetLength(), firstFile.GetLength());
		} 
		// verify that we have a file (if we want files)
        else if ((buf.st_mode & _S_IFREG) == _S_IFREG) 
        {
			if (m_bAllowFiles)
				SetWindowText(firstFile);
            SetEditSel(firstFile.GetLength(), firstFile.GetLength());
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDropComboBox public functions

// inserts string at the top of the list of strings
void CDropComboBox::PushString(LPCTSTR szText)
{
    CString str;
    CStringArray aStrings;
    aStrings.Add(szText);

    int nNumStrings = GetCount();
    for (int i = 0; i < nNumStrings; i++)
    {
        GetLBText(i, str);
        if (m_bNoRepeats && str != szText)
            aStrings.Add(str);
    }
    ResetContent();
    nNumStrings = min(aStrings.GetSize(), m_nMaxFiles);

    for (int i = 0; i < nNumStrings; i++)
    {
        AddString(aStrings[i]);
    }
}


/////////////////////////////////////////////////////////////////////////////
// CDropComboBox implementation

//////////////////////////////////////////////////////////////////
//	use IShellLink to expand the shortcut
//	returns the expanded file, or "" on error
//
//	original code was part of CShortcut 
//	1996 by Rob Warner
//	rhwarner@southeast.net
//	http://users.southeast.net/~rhwarner

CString CDropComboBox::ExpandShortcut(CString &inFile)
{
	CString outFile = "";

    // Make sure we have a path
    ASSERT(inFile != _T(""));

    IShellLink* psl;
    HRESULT hres;
    LPTSTR lpsz = inFile.GetBuffer(MAX_PATH);

    // Create instance for shell link
    hres = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
        IID_IShellLink, (LPVOID*) &psl);
    if (SUCCEEDED(hres))
    {
        // Get a pointer to the persist file interface
        IPersistFile* ppf;
        hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*) &ppf);
        if (SUCCEEDED(hres))
        {
            // Make sure it's ANSI
            WCHAR wsz[MAX_PATH];
            ::MultiByteToWideChar(CP_ACP, 0, lpsz, -1, wsz, MAX_PATH);

            // Load shortcut
            hres = ppf->Load(wsz, STGM_READ);
            if (SUCCEEDED(hres)) {
				WIN32_FIND_DATA wfd;
				// find the path from that
				HRESULT hres = psl->GetPath(outFile.GetBuffer(MAX_PATH), 
								MAX_PATH,
								&wfd, 
								SLGP_UNCPRIORITY);

				outFile.ReleaseBuffer();
            }
            ppf->Release();
        }
        psl->Release();
    }

	inFile.ReleaseBuffer();

	// if this fails, outFile == ""
    return outFile;
}

LONG CDropComboBox::CheckRepeats(LPCTSTR lpszText)
{
    if (!m_bNoRepeats)
        return CB_ERR;

    return FindString(-1, lpszText);
}

void CDropComboBox::CheckOverflow()
{
    if (m_nMaxFiles > 0 && GetCount() >= m_nMaxFiles)
        DeleteString(m_nMaxFiles-1);
}

void CDropComboBox::RecalcDropWidth()
{
    // Reset the dropped width
    int nNumEntries = GetCount();
    int nWidth = 0;
    CString str;

    CClientDC dc(this);
    int nSave = dc.SaveDC();
    dc.SelectObject(GetFont());

    int nScrollWidth = ::GetSystemMetrics(SM_CXVSCROLL);
    for (int i = 0; i < nNumEntries; i++)
    {
        GetLBText(i, str);
        int nLength = dc.GetTextExtent(str).cx + nScrollWidth;
        nWidth = max(nWidth, nLength);
    }

    dc.RestoreDC(nSave);
    SetDroppedWidth(nWidth);
}
