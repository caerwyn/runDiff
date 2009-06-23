// RunWinDiff.h : main header file for the RUNWINDIFF application
//

#if !defined(AFX_RUNWINDIFF_H__33D0B056_597F_11D2_97AD_C4490A000000__INCLUDED_)
#define AFX_RUNWINDIFF_H__33D0B056_597F_11D2_97AD_C4490A000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRunWinDiffApp:
// See RunWinDiff.cpp for the implementation of this class
//

class CRunWinDiffApp : public CWinApp
{
public:
	CRunWinDiffApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRunWinDiffApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRunWinDiffApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUNWINDIFF_H__33D0B056_597F_11D2_97AD_C4490A000000__INCLUDED_)
