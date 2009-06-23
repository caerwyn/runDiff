// RunWinDiff.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RunWinDiff.h"
#include "RunWinDiffDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRunWinDiffApp

BEGIN_MESSAGE_MAP(CRunWinDiffApp, CWinApp)
	//{{AFX_MSG_MAP(CRunWinDiffApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRunWinDiffApp construction

CRunWinDiffApp::CRunWinDiffApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRunWinDiffApp object

CRunWinDiffApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRunWinDiffApp initialization

BOOL CRunWinDiffApp::InitInstance()
{
	// Initialize OLE 2.0 libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

    SetRegistryKey(_T("Codeguru samples"));

	if ( __argc == 3 )
	{
		CString strFile1 = __argv[1];
		CString strFile2 = __argv[2];

		CRunWinDiffDlg::CWCompare( strFile1, strFile2);
		return FALSE;
	}

	CRunWinDiffDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
