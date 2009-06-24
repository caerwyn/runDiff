// RunWinDiffDlg.cpp : implementation file
//
// Author: Chris Maunder
//
// Modified by:
//
//		Caerwyn Pearce - 3rd July 2003
//		Added support for compare using CodeWarrior IDE.
//
//      Daniel P Lyons - 20/10/98
//		added new button styles from Davide Calibro - SofTech Software
//		modified ExpandDialog() to demonstrate different method
//		replaced instruction with tooltips
//		added Klaus' suggestion re: Browse functions
//		modified general appearance
//
//      Chris Maunder - 03/11/98 (that's 3 November, guys)
//      Minor cosmetics, last file used logic cleaned, combo drop 
//      down widened.

#include "stdafx.h"
#include "RunWinDiff.h"
#include "RunWinDiffDlg.h"
#include "DirDialog.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "CCodeWarriorCompare.h"
#include "CCodeWarriorApp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRunWinDiffDlg dialog

CRunWinDiffDlg::CRunWinDiffDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRunWinDiffDlg::IDD, pParent)
	, m_strCWIDE(_T(""))
{
	//{{AFX_DATA_INIT(CRunWinDiffDlg)
	m_strFile1 = _T("");
	m_strFile2 = _T("");
	m_bOutline = FALSE;
	m_strWinDiff = _T("C:\\Program Files\\Microsoft Visual Studio\\Common\\Tools\\windiff.exe");
	m_strCWIDE = _T("C:\\Program Files\\Metrowerks\\CodeWarrior\\Bin\\IDE.exe");
	m_bReuse = TRUE;
	m_bRecursive = TRUE;
	//}}AFX_DATA_INIT
    m_nMaxFiles = 10;
}

void CRunWinDiffDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRunWinDiffDlg)
	DDX_Control(pDX, IDC_FILE1, m_Combo1);
	DDX_Control(pDX, IDC_FILE2, m_Combo2);
	DDX_Control(pDX, IDC_WINDIFF, m_DropEdit3);
	DDX_Text(pDX, IDC_FILE1, m_strFile1);
	DDX_Text(pDX, IDC_FILE2, m_strFile2);
	DDX_Text(pDX, IDC_DIR1, m_strDir1Name);
	DDX_Text(pDX, IDC_DIR2, m_strDir2Name);
	DDX_Check(pDX, IDC_OUTLINE, m_bOutline);
	DDX_Text(pDX, IDC_WINDIFF, m_strWinDiff);
	DDX_Text(pDX, IDC_CWIDE, m_strCWIDE);
	DDX_Check(pDX, IDC_REUSE, m_bReuse);
	DDX_Check(pDX, IDC_RECURSE, m_bRecursive);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_DIFF_PICKER, m_comboPicker);
}

BEGIN_MESSAGE_MAP(CRunWinDiffDlg, CDialog)
	//{{AFX_MSG_MAP(CRunWinDiffDlg)
	ON_BN_CLICKED(IDC_BROWSE1, OnBrowseFile1)
	ON_BN_CLICKED(IDC_BROWSE2, OnBrowseFile2)
	ON_BN_CLICKED(IDC_DIR1, OnBrowseDirectory1)
	ON_BN_CLICKED(IDC_DIR2, OnBrowseDirectory2)
	ON_BN_CLICKED(IDC_WINDIFF_EXE_DIR, OnBrowseWinDiff)
	ON_BN_CLICKED(IDC_EXPAND_BUTTON, OnExpandButton)
	ON_BN_CLICKED(IDC_HELPBTN, OnHelp)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CW_EXE_DIR, OnBrowseCWIDE)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRunWinDiffDlg message handlers

BOOL CRunWinDiffDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_comboPicker.SetCurSel(INDEX_CODEWARRIOR);

    m_Combo1.SetMaxFiles(m_nMaxFiles);
    m_Combo2.SetMaxFiles(m_nMaxFiles);
    
    // Get previous settings.
    GetPrevSettings();

	InitialiseButtons();

    UpdateData(FALSE);

	ExpandDialog(IDC_LANDMARK, m_bExpand);

    CreateToolTips();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRunWinDiffDlg::OnBrowseFile1() 
{
    UpdateData(TRUE);

	CString strFilter = _T("All Files (*.*) |*.*||");

	CFileDialog	dlg(TRUE, NULL, m_strFile1, OFN_HIDEREADONLY|OFN_EXPLORER, strFilter, NULL); 

	dlg.m_ofn.lpstrTitle = _T(" Select file 1");

	if (dlg.DoModal() == IDOK) 
    {
		m_strFile1 = dlg.GetPathName();
        UpdateData(FALSE);
		m_Combo1.SetEditSel(dlg.GetPathName().GetLength(), dlg.GetPathName().GetLength());
	}
}

void CRunWinDiffDlg::OnBrowseFile2() 
{
    UpdateData(TRUE);

	CString strFilter = _T("All Files (*.*) |*.*||");

	CFileDialog	dlg(TRUE, NULL, m_strFile2, OFN_HIDEREADONLY|OFN_EXPLORER, strFilter, NULL); 

	dlg.m_ofn.lpstrTitle = _T(" Select file 2");

	if (dlg.DoModal() == IDOK) 
    {
		m_strFile2 = dlg.GetPathName();
        UpdateData(FALSE);
		m_Combo2.SetEditSel(dlg.GetPathName().GetLength(), dlg.GetPathName().GetLength());
	}
}

void CRunWinDiffDlg::OnBrowseDirectory1() 
{
	CDirDialog dlg; 

	dlg.m_strTitle = _T("Choose directory 1");
	// Default previous file1; New by Klaus 981014
	dlg.m_strSelDir = m_strFile1;

	if (dlg.DoBrowse()) 
	{
		m_strFile1 = dlg.m_strPath;
		UpdateData(FALSE);
		m_Combo1.SetEditSel(m_strFile1.GetLength(), m_strFile1.GetLength());
	}
}

void CRunWinDiffDlg::OnBrowseDirectory2() 
{
	CDirDialog dlg; 

	dlg.m_strTitle = _T("Choose directory 2");
	// Default previous file2; New by Klaus 981014
	dlg.m_strSelDir = m_strFile2;

	if (dlg.DoBrowse()) 
	{
		m_strFile2 = dlg.m_strPath;
		UpdateData(FALSE);
		m_Combo2.SetEditSel(m_strFile2.GetLength(), m_strFile2.GetLength());
	}
}

void CRunWinDiffDlg::OnBrowseWinDiff() 
{
    UpdateData(TRUE);

	CString strFilter = _T("WinDiff.exe|WinDiff.exe|Executables (*.exe) |*.exe| All Files (*.*) |*.*||");

	CFileDialog	dlg(TRUE, NULL, m_strWinDiff, OFN_HIDEREADONLY|OFN_EXPLORER, strFilter, NULL); 

	dlg.m_ofn.lpstrTitle = _T(" Search for WinDiff");

	if (dlg.DoModal() == IDOK) 
    {
		m_strWinDiff = dlg.GetPathName();
        UpdateData(FALSE);
		m_DropEdit3.SetSel(dlg.GetPathName().GetLength(), dlg.GetPathName().GetLength());
	}
}


void CRunWinDiffDlg::OnBrowseCWIDE()
{
    UpdateData(TRUE);

	CString strFilter = _T("IDE.exe|IDE.exe|Executables (*.exe) |*.exe| All Files (*.*) |*.*||");

	CFileDialog	dlg(TRUE, NULL, m_strCWIDE, OFN_HIDEREADONLY|OFN_EXPLORER, strFilter, NULL); 

	dlg.m_ofn.lpstrTitle = _T(" Search for CW IDE");

	if (dlg.DoModal() == IDOK) 
    {
		m_strCWIDE = dlg.GetPathName();
        UpdateData(FALSE);
		m_DropEdit3.SetSel(dlg.GetPathName().GetLength(), dlg.GetPathName().GetLength());
	}
}




void CRunWinDiffDlg::OnOK()
{
	int nIndex = m_comboPicker.GetCurSel();
	if (nIndex != CB_ERR)
	{
		switch (nIndex)
		{
		default:
		case INDEX_CODEWARRIOR:
			OnCompareCodeWarrior();
			break;
		case INDEX_WINDIFF:
			OnCompareWinDiff();
			break;

		case INDEX_WINMERGE:
			break;

		}
	}
	else
	{
		OnCompareWinDiff();
	}

}



void CRunWinDiffDlg::OnCompareCodeWarrior()
{
	if (!OnVerifyFiles())
		return;

	if (m_strCWIDE.IsEmpty())
    {
        MessageBox(_T("Please locate CodeWarrior IDE.exe"));
        OnBrowseCWIDE();
        if (m_strCWIDE.IsEmpty())
            return;
    }

	CWCompare( m_strFile1, m_strFile2);
}

void CRunWinDiffDlg::CWCompare(CString &strFile1, CString &strFile2)
{
	// create the CodeWarrior object that we'll drive through OLE automation
	COleException e;
	CLSID clsid;
	if (CLSIDFromProgID(OLESTR("CodeWarrior.CodeWarriorApp"), &clsid) != NOERROR)
	{
		AfxMessageBox(IDP_UNABLE_TO_CREATE);
		return;
	}

	// try to get the active CW IDE before creating a new one
	LPUNKNOWN	lpUnk;
	LPDISPATCH	lpDispatchApp;

	CCodeWarriorApp			oleCWApp;

	if (GetActiveObject(clsid, NULL, &lpUnk) == NOERROR)
	{
		HRESULT hr = lpUnk->QueryInterface(IID_IDispatch, (LPVOID*)&lpDispatchApp);
		lpUnk->Release();
		if (hr == NOERROR)
			oleCWApp.AttachDispatch(lpDispatchApp, TRUE);
	}

	// if not dispatch ptr attached yet, need to create one
	if (oleCWApp.m_lpDispatch == NULL && !oleCWApp.CreateDispatch(clsid, &e))
	{
		AfxMessageBox(IDP_UNABLE_TO_CREATE);
		return;
	}

	LPDISPATCH lpDispatchCompare = oleCWApp.get_CompareInterface();

	CCodeWarriorCompare		oleCWCompare( lpDispatchCompare );

	bool	bIgnoreCase	= false;
	bool	bIgnoreSpace = false;
	bool	bShowDifferentFiles			= true;		// true to show files that exist in one folder 
														// but not the other or false to ignore such files.
	bool	bCompareTextFileContents	= true;		// true to compare the contents of text files within
														// the two folders or false to ignore the contents of text files. 


	// Just need to work out if we're dealing with files or folders.
	if ( IsDirectory(strFile1) )
	{
		oleCWCompare.CompareFolders(strFile1, strFile2, bIgnoreCase, bIgnoreSpace, bShowDifferentFiles, bCompareTextFileContents);
	}
	else
	{
		oleCWCompare.CompareFiles(strFile1, strFile2, bIgnoreCase, bIgnoreSpace);
	}
}

void CRunWinDiffDlg::OnCompareWinDiff()
{
	if (!OnVerifyFiles())
		return;

	if (m_strWinDiff.IsEmpty())
    {
        MessageBox(_T("Please locate WinDiff.exe"));
        OnBrowseWinDiff();
        if (m_strWinDiff.IsEmpty())
            return;
    }
 
    // If reuse is on, then look for a windiff and reuse it
    if (m_bReuse)
    {
        CWnd *pWnd = FindWindow(_T("WinDiffViewerClass"), _T("WinDiff"));
        if (pWnd)
            pWnd->SendMessage(WM_CLOSE);
    }

    CString strCommandLine, strOptions;

    strOptions = _T("");
    if (m_bOutline)
        strOptions += _T("-O ");
    if (!m_bRecursive)
        strOptions += _T("-D ");

    strCommandLine.Format(_T("%s \"%s\" \"%s\""), strOptions, m_strFile1, m_strFile2);

	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb			= sizeof(si);
	si.dwFlags		= STARTF_USESHOWWINDOW;
	si.wShowWindow	= SW_SHOW;

    ZeroMemory( &pi, sizeof(pi) );

    // Start the child process. 
    if( !CreateProcess( m_strWinDiff, strCommandLine.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ) ) 
    {
		MessageBox(_T("Unable to run WinDiff"));
    }

	strCommandLine.ReleaseBuffer();

    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}



bool CRunWinDiffDlg::OnVerifyFiles() 
{
    UpdateData(TRUE);

    m_strFile1.TrimLeft();
	m_strFile1.TrimRight(); 

    m_strFile2.TrimLeft();
	m_strFile2.TrimRight(); 

    if (m_strFile1.IsEmpty() || m_strFile2.IsEmpty())
    {
        MessageBox(_T("You must specify two files or two directories"));
        return false;
    }

    if (Exist(m_strFile1))
    {
        m_Combo1.PushString(m_strFile1);
        m_Combo1.SetWindowText(m_strFile1);
    }

    if (Exist(m_strFile2))
    {
        m_Combo2.PushString(m_strFile2);
        m_Combo2.SetWindowText(m_strFile2); 
    }

	if ( IsDirectory(m_strFile1) !=  IsDirectory(m_strFile1) )
	{
        MessageBox(_T("The items to compare must be both files or both directories"));
        return false;
	}

	return true;
}




void CRunWinDiffDlg::OnCancel() 
{
	SaveCurrentSettings();
	CDialog::OnCancel();
}

void CRunWinDiffDlg::OnExpandButton() 
{
    m_bExpand = !m_bExpand;
    ExpandDialog (IDC_LANDMARK, m_bExpand);
}

void CRunWinDiffDlg::OnHelp() 
{
	CInfoDlg infoDlg;
	infoDlg.DoModal();

	return;
}

/////////////////////////////////////////////////////////////////////////////
// CRunWinDiffDlg overrides

BOOL CRunWinDiffDlg::PreTranslateMessage(MSG* pMsg) 
{
    // Let the ToolTip process this message.
	m_tooltip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// CRunWinDiffDlg implementation

void CRunWinDiffDlg::CreateToolTips()
{
    // Create the ToolTip control.
    m_tooltip.Create(this);
    
    m_tooltip.AddTool(GetDlgItem(IDC_FILE1), IDS_CBOX_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_FILE2), IDS_CBOX_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_OUTLINE), IDS_OUTLINE_TOOLTIP);		
    m_tooltip.AddTool(GetDlgItem(IDC_WINDIFF), IDS_WINDIFF_DIR_TOOLTIP);		
    m_tooltip.AddTool(GetDlgItem(IDC_DIR1), IDS_DIR_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_DIR2), IDS_DIR_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_WINDIFF_EXE_DIR), IDS_WINDIFF_BROWSE_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_CW_EXE_DIR), IDS_CW_BROWSE_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_BROWSE1), IDS_FILE_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_BROWSE2), IDS_FILE_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDOK), IDS_COMPARE_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_REUSE), IDS_CHECK_REUSE);
    m_tooltip.AddTool(GetDlgItem(IDC_EXPAND_BUTTON), IDS_EXPAND_BUTTON);
    m_tooltip.AddTool(GetDlgItem(IDCANCEL), IDS_EXIT_TOOLTIP);
    m_tooltip.AddTool(GetDlgItem(IDC_HELPBTN), IDS_HELPBTN);
    
    m_tooltip.Activate(TRUE);
}

BOOL CRunWinDiffDlg::InitialiseButtons()
{
	// Create IDOK button
	m_btnOk.SubclassDlgItem(IDOK, this);
	m_btnOk.SetIcon( IDI_COMPARE16 );
	m_btnOk.SetActiveFgColor(RGB(0,0,200));
//	m_btnOk.SetInactiveFgColor(RGB(0,0,200));
//	m_btnOk.SetActiveBgColor(RGB(220,220,220));

	// Create IDCANCEL button
	m_btnCancel.SubclassDlgItem(IDCANCEL, this);
	m_btnCancel.SetIcon( IDI_CANCEL256 );
	m_btnCancel.SetActiveFgColor(RGB(0,0,200));

	// Create BROWSE button for Input Directory
	m_btnBrowseWinDiff.SubclassDlgItem(IDC_WINDIFF_EXE_DIR, this);
	m_btnBrowseWinDiff.SetIcon( IDI_BROWSE256 );

	// Create BROWSE button for Input Directory
	m_btnBrowseCWIDE.SubclassDlgItem(IDC_CW_EXE_DIR, this);
	m_btnBrowseCWIDE.SetIcon( IDI_BROWSE256 );

	// Create IDC_HELPBTN button
	m_btnInfo.SubclassDlgItem(IDC_HELPBTN, this);
	m_btnInfo.SetIcon(IDI_HELP_ON, IDI_HELP_OFF); 
	//m_btnInfo.DrawBorder(FALSE);

	// Create IDC_DIR1 button
	m_btnDir1.SubclassDlgItem(IDC_DIR1, this);
	m_btnDir1.SetIcon( IDI_BROWSE256 );
	
	// Create IDC_DIR2 button
	m_btnDir2.SubclassDlgItem(IDC_DIR2, this);
	m_btnDir2.SetIcon( IDI_BROWSE256 );

	// Create IDC_BROWSE1 button
	m_btnFile1.SubclassDlgItem(IDC_BROWSE1, this);
	m_btnFile1.SetIcon( IDI_FILE_OPEN );
	m_btnFile1.SetActiveFgColor(RGB(0,0,200));

	// Create IDC_BROWSE2 button
	m_btnFile2.SubclassDlgItem(IDC_BROWSE2, this);
	m_btnFile2.SetIcon( IDI_FILE_OPEN );
	m_btnFile2.SetActiveFgColor(RGB(0,0,200));

	// Create IDC_EXPAND_BUTTON button
	m_btnExpand.SubclassDlgItem(IDC_EXPAND_BUTTON, this);
	m_btnExpand.SetIcon( IDI_OPEN );
	m_btnExpand.SetActiveFgColor(RGB(0,0,200));

	return 0;
}

// ExpandDialog expands the dialog to full size if m_bExpand is TRUE. 
// Otherwise it's contracted, with the bottom of the new rectangle 
// set to the bottom of the landmark control passed in as nResourceID
//
void CRunWinDiffDlg::ExpandDialog(int nResourceID, BOOL m_bExpand)
{
	static  CRect rcLarge;
    static  CRect rcSmall;
    CString sExpand;

	// First time through, save the dialog's large and small sizes
    if (rcLarge.IsRectNull())
    {                
    	CRect rcLandmark;
	    CWnd* pWndLandmark = GetDlgItem (nResourceID);
	    ASSERT(pWndLandmark);	
    
    	GetWindowRect (rcLarge);
    	pWndLandmark->GetWindowRect (rcLandmark);
    	
		rcSmall = rcLarge;
    	rcSmall.bottom = rcLandmark.top;
    }

    if (m_bExpand)
    {
		// Expand the dialog: resize the dialog
        // to its original size (rcLarge)
        SetWindowPos(NULL, 0, 0, rcLarge.Width(), rcLarge.Height(),
        	SWP_NOMOVE | SWP_NOZORDER);

        sExpand = _T("Less");
		m_btnExpand.SetIcon(IDI_CLOSE);
    }
    else
    {
    	// Contract the dialog to the small size
        SetWindowPos(NULL, 0, 0, rcSmall.Width(), rcSmall.Height(),
        	SWP_NOMOVE | SWP_NOZORDER);

        sExpand = _T("More");
		m_btnExpand.SetIcon(IDI_OPEN);
    }    
    SetDlgItemText( IDC_EXPAND_BUTTON, sExpand );
}

void CRunWinDiffDlg::GetPrevSettings()
{
    int nNumSaved = AfxGetApp()->GetProfileInt(_T("Settings"), _T("File 1 Count"), 0);
    for (int i = 0; i < nNumSaved; i++)
    {
        CString strEntry, strFile;
        strEntry.Format(_T("File 1:%d"), i);

        strFile = AfxGetApp()->GetProfileString(_T("Settings"), strEntry, _T(""));
        if (!i)
            m_strFile1 = strFile;
        if (Exist(strFile))
            m_Combo1.AddString(strFile);
    }

	// restore the last selection
	int nSelection = AfxGetApp()->GetProfileInt(_T("Settings"), _T("Selection 1"), -1);
	if (nSelection >= 0 && nSelection < m_Combo1.GetCount())
    {
        m_Combo1.SetCurSel(nSelection);
        m_Combo1.GetLBText(nSelection, m_strFile1);
    }

    nNumSaved = AfxGetApp()->GetProfileInt(_T("Settings"), _T("File 2 Count"), 0);
    for (int i = 0; i < nNumSaved; i++)
    {
        CString strEntry, strFile;
        strEntry.Format(_T("File 2:%d"), i);

        strFile = AfxGetApp()->GetProfileString(_T("Settings"), strEntry, _T(""));
        if (!i)
            m_strFile2 = strFile;
        if (Exist(strFile))
            m_Combo2.AddString(strFile);
    }

	// restore the last selection
	nSelection = AfxGetApp()->GetProfileInt(_T("Settings"), _T("Selection 2"), -1);
	if (nSelection >= 0 && nSelection < m_Combo2.GetCount())
    {
        m_Combo2.SetCurSel(nSelection);
        m_Combo2.GetLBText(nSelection, m_strFile2);
    }

    m_bOutline   = AfxGetApp()->GetProfileInt(_T("Settings"), _T("Outline"), 0);
    m_bReuse     = AfxGetApp()->GetProfileInt(_T("Settings"), _T("Reuse"),   1);
    m_bRecursive = AfxGetApp()->GetProfileInt(_T("Settings"), _T("Recurse"), 1);

	m_strWinDiff = AfxGetApp()->GetProfileString(_T("Settings"), _T("WinDiff Location"), m_strWinDiff);

	m_strCWIDE = AfxGetApp()->GetProfileString(_T("Settings"), _T("CWIDE Location"), m_strCWIDE);

    m_bExpand = AfxGetApp()->GetProfileInt(_T("Settings"), _T("Expanded"), 1);

    int x = AfxGetApp()->GetProfileInt(_T("Settings"), _T("x"), -1);
    int y = AfxGetApp()->GetProfileInt(_T("Settings"), _T("y"), -1);
    if (x >= 0 && x < GetSystemMetrics(SM_CXSCREEN) &&
        y >= 0 && y < GetSystemMetrics(SM_CYSCREEN))
    {
        CRect rect;
        GetWindowRect(rect);
        rect.OffsetRect(x - rect.left, y - rect.top);
        MoveWindow(rect);
    }
}

void CRunWinDiffDlg::SaveCurrentSettings()
{    
    UpdateData(TRUE);

    CRect rect;
    GetWindowRect(rect);

    int nNumSaved = m_Combo1.GetCount();
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("File 1 Count"), nNumSaved);
    for (int i = 0; i < nNumSaved; i++)
    {
        CString strEntry, strFile;
        strEntry.Format(_T("File 1:%d"), i);
        m_Combo1.GetLBText(i, strFile);
        AfxGetApp()->WriteProfileString(_T("Settings"), strEntry, strFile);
    }

	// save the last selection position
	int nSelection = m_Combo1.GetCurSel();
	if (nSelection != -1)
	    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Selection 1"), nSelection);
	else
	{
		nSelection = m_Combo1.FindString(0, m_strFile1);
		AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Selection 1"), nSelection);
	}

    nNumSaved = m_Combo2.GetCount();
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("File 2 Count"), nNumSaved);
    for (int i = 0; i < nNumSaved; i++)
    {
        CString strEntry, strFile;
        strEntry.Format(_T("File 2:%d"), i);
        m_Combo2.GetLBText(i, strFile);
        AfxGetApp()->WriteProfileString(_T("Settings"), strEntry, strFile);
    }

	// save the last selection position
	nSelection = m_Combo2.GetCurSel();
	if (nSelection != -1)
	    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Selection 2"), nSelection);
	else
	{
		nSelection = m_Combo2.FindString(0, m_strFile2);
		AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Selection 2"), nSelection);
	}

    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Outline"), m_bOutline);
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Reuse"),   m_bReuse);
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Recurse"), m_bRecursive);

	AfxGetApp()->WriteProfileString(_T("Settings"), _T("WinDiff Location"), m_strWinDiff);
	AfxGetApp()->WriteProfileString(_T("Settings"), _T("CWIDE Location"), m_strCWIDE);
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Expanded"), m_bExpand);
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("x"), rect.left);
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("y"), rect.top);
}


BOOL CRunWinDiffDlg::Exist(LPCTSTR szText)
{
	struct _stat buf;
	return (_stat(szText, &buf) == 0);
}



BOOL CRunWinDiffDlg::IsDirectory(LPCTSTR szText)
{
	BOOL	bIsDirectory	= false;

	struct _stat buf;
	if (_stat(szText, &buf) == 0)
	{
		// st_mode - Bit mask for file-mode information.
		// The _S_IFDIR bit is set if path specifies a directory;
		if (buf.st_mode & _S_IFDIR )
		{
			bIsDirectory = true;
		}
	}
	return bIsDirectory;
}




/////////////////////////////////////////////////////////////////////////////
// CInfoDlg 
//

BEGIN_MESSAGE_MAP(CInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoDlg)
	//}}AFX_DATA_INIT
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoDlg)
	DDX_Control(pDX, IDC_HYPER3, m_Hyper3);
	DDX_Control(pDX, IDC_HYPER2, m_Hyper2);
	DDX_Control(pDX, IDC_HYPER1, m_Hyper1);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg message handlers
//
BOOL CInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Create IDOK button
	m_btnOk.SubclassDlgItem(IDOK, this);
	m_btnOk.SetIcon(IDI_OK256);

    // All praise and angst to us...
    m_Hyper1.SetURL(_T("mailto:cmaunder@mail.com?Subject=WinDiff front end"));
    m_Hyper2.SetURL(_T("mailto:YPBLAZE@aol.com?Subject=WinDiff front end"));
    m_Hyper3.SetURL(_T("mailto:caerwyn@tectryx.com?Subject=CodeWarrior Compare GUI"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInfoDlg::OnOK() 
{
	CDialog::OnOK();
}





