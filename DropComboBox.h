#if !defined(AFX_DROPCOMBOBOX_H__115F422E_5CD5_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_DROPCOMBOBOX_H__115F422E_5CD5_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// DropComboBox.h : header file
//
// Autocompleting combo-box (like the URL edit box in netscape)
//
// Written by Chris Maunder (chrismaunder@codeguru.com)
// Copyright (c) 1998.
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
// The author accepts no liability if it causes any damage to your
// computer, causes your pet cat to fall ill, increases baldness or
// makes you car start emitting strange noises when you start it up.
//
// Expect bugs.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 
//
//	Drop edit stuff taken from "CDropEdit"
//	Copyright 1997 Chris Losinger
//
//	shortcut expansion code modified from :
//	CShortcut, 1996 Rob Warner
/////////////////////////////////////////////////////////////////////////////

#include <shlobj.h>

/////////////////////////////////////////////////////////////////////////////
// CDropComboBox window

class CDropComboBox : public CComboBox
{
// Construction
public:
	CDropComboBox();

// Attributes
public:
    void AllowFileDrop(BOOL bAllow = TRUE)      { m_bAllowFiles = bAllow;  }
    BOOL AllowingFileDrop()                     { return m_bAllowFiles;    }
    void AllowDirDrop(BOOL bAllow = TRUE)       { m_bAllowDirs = bAllow;   }
    BOOL AllowingDirDrop()                      { return m_bAllowDirs;     }
    void SetMaxFiles(int nMaxFiles)             { m_nMaxFiles = nMaxFiles; }
    int  GetMaxFiles()                          { return m_nMaxFiles;      }
    void SetNoRepeats(BOOL bNoRep)              { m_bNoRepeats = bNoRep;   }
    BOOL GetNoRepeats()                         { return m_bNoRepeats;     }

    void PushString(LPCTSTR szText);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropComboBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDropComboBox();

protected:
	CString ExpandShortcut(CString &inFile);
    LONG CheckRepeats(LPCTSTR lpszText);
    void CheckOverflow();
    void RecalcDropWidth();

    int  m_nMaxFiles;
    BOOL m_bNoRepeats;
	BOOL m_bAutoComplete;
	BOOL m_bAllowFiles, m_bAllowDirs;
    BOOL m_bMustUninitOLE;

	// Generated message map functions
protected:
	//{{AFX_MSG(CDropComboBox)
	afx_msg void OnEditUpdate();
    afx_msg LONG OnAddString(UINT wParam, LONG lParam);
    afx_msg LONG OnInsertString(UINT wParam, LONG lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDropFiles(HDROP dropInfo);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPCOMBOBOX_H__115F422E_5CD5_11D1_ABBA_00A0243D1382__INCLUDED_)
