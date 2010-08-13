#if !defined(AFX_ILVIEW_H__50E1A04D_6C11_466A_B3BB_D4364899F81D__INCLUDED_)
#define AFX_ILVIEW_H__50E1A04D_6C11_466A_B3BB_D4364899F81D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IlView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIlView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CIlView : public CFormView
{
protected:
	CIlView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CIlView)

// Form Data
public:
	//{{AFX_DATA(CIlView)
	enum { IDD = IDD_DLG_ILL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIlView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CIlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CIlView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ILVIEW_H__50E1A04D_6C11_466A_B3BB_D4364899F81D__INCLUDED_)
