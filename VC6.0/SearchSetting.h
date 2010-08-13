#if !defined(AFX_SEARCHSETTING_H__3316211B_5D51_41DA_B1F8_5F3C99A3ECFB__INCLUDED_)
#define AFX_SEARCHSETTING_H__3316211B_5D51_41DA_B1F8_5F3C99A3ECFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SearchSetting dialog

class SearchSetting : public CDialog
{
// Construction
public:
	SearchSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SearchSetting)
	enum { IDD = IDD_DLG_SETTING };
	CString	m_strKeyImage;
	int		m_ImageNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SearchSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SearchSetting)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGlance();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_strImagePath;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHSETTING_H__3316211B_5D51_41DA_B1F8_5F3C99A3ECFB__INCLUDED_)
