// RunWinDiffDlg.h : header file
//

#if !defined(AFX_RunWinDiffDlg_H__7D44FA86_3880_11D2_ABF0_56CA8F000000__INCLUDED_)
#define AFX_RunWinDiffDlg_H__7D44FA86_3880_11D2_ABF0_56CA8F000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DropEdit.h"
#include "HyperLink.h"
#include "DropComboBox.h"
#include "BtnST.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CRunWinDiffDlg dialog

class CRunWinDiffDlg : public CDialog
{
// Construction
public:
	CRunWinDiffDlg(CWnd* pParent = NULL);	// standard constructor
	CToolTipCtrl m_tooltip;

// Dialog Data
	//{{AFX_DATA(CRunWinDiffDlg)
	enum { IDD = IDD_RUNWINDIFF_DIALOG };
	CDropComboBox	m_Combo1;
	CDropComboBox	m_Combo2;
	CDropEdit	m_DropEdit3;
	CString	    m_strFile1;
	CString	    m_strFile2;
	CString		m_strDir1Name;
	CString		m_strDir2Name;
	CString		m_strDirTitle;
	BOOL	    m_bOutline;
	CString     m_strWinDiff;						// Path to WinDiff.exe
	CString		m_strCWIDE;							// Path to the CodeWarrior IDE
	BOOL	    m_bReuse;
	BOOL	m_bRecursive;
	//}}AFX_DATA

    BOOL         m_bExpand;
    int          m_nMaxFiles;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRunWinDiffDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    void ExpandDialog( int nResourceID, BOOL bVisible );
    void GetPrevSettings();
    void SaveCurrentSettings();
	BOOL InitialiseButtons();
    void CreateToolTips();
    BOOL Exist(LPCTSTR szText);
	bool OnVerifyFiles();

	// Generated message map functions
	//{{AFX_MSG(CRunWinDiffDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseFile1();
	afx_msg void OnBrowseFile2();
	afx_msg void OnBrowseDirectory1();
	afx_msg void OnBrowseDirectory2();
	afx_msg void OnBrowseWinDiff();
	afx_msg void OnBrowseCWIDE();
	virtual void OnCancel();
	afx_msg void OnExpandButton();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CButtonST m_btnOk;
	CButtonST m_btnCancel;
	CButtonST m_btnDir1;
	CButtonST m_btnDir2;
	CButtonST m_btnFile1;
	CButtonST m_btnFile2;
	CButtonST m_btnBrowseWinDiff;
	CButtonST m_btnBrowseCWIDE;
	CButtonST m_btnInfo;
	CButtonST m_btnExpand;
	CComboBox m_comboPicker;

public:
	afx_msg void OnCompareCodeWarrior();
	afx_msg void OnCompareWinDiff();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk();

	static void CWCompare(CString &strFile1, CString &strFile2);
	static BOOL IsDirectory(LPCTSTR szText);


};



enum
{
	INDEX_CODEWARRIOR = 0,
	INDEX_WINDIFF,
	INDEX_FCU,
	INDEX_WINMERGE,
};




/////////////////////////////////////////////////////////////////////////////
// CInfoDlg dialog

class CInfoDlg : public CDialog
{
// Construction
public:
	CInfoDlg(CWnd* pParent = NULL);// standard constructor

// Dialog Data
	//{{AFX_DATA(CInfoDlg)
	enum { IDD = IDD_HELPBOX };
	CHyperLink	m_Hyper3;
	CHyperLink	m_Hyper2;
	CHyperLink	m_Hyper1;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CInfoDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CButtonST m_btnOk;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RunWinDiffDlg_H__7D44FA86_3880_11D2_ABF0_56CA8F000000__INCLUDED_)
