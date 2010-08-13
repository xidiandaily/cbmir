// CBMIR.h : main header file for the CBMIR application
//

#if !defined(AFX_CBMIR_H__664DD98C_EDB1_4E27_8E77_3EF19B2209E1__INCLUDED_)
#define AFX_CBMIR_H__664DD98C_EDB1_4E27_8E77_3EF19B2209E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCBMIRApp:
// See CBMIR.cpp for the implementation of this class
//

class CCBMIRApp : public CWinApp
{
public:
	CCBMIRApp();
	
	char acCurDir[_MAX_PATH];
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCBMIRApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCBMIRApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

extern CCBMIRApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBMIR_H__664DD98C_EDB1_4E27_8E77_3EF19B2209E1__INCLUDED_)
