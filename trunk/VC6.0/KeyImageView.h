#if !defined(AFX_KEYIMAGEVIEW_H__4CA8BDD3_18D1_43BD_A8E2_FAFDDA76E1AF__INCLUDED_)
#define AFX_KEYIMAGEVIEW_H__4CA8BDD3_18D1_43BD_A8E2_FAFDDA76E1AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KeyImageView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKeyImageView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "ximage.h"

#ifndef TEXT_HEIGHT	
#define TEXT_HEIGHT 20
#endif 

class CCBMIRDoc;

class CKeyImageView : public CFormView
{
protected:
	CKeyImageView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CKeyImageView)

// Form Data
public:
	//{{AFX_DATA(CKeyImageView)
	enum { IDD = IDD_DLG_KEY_IMAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	void ShowKeyImage(const CString &csKeyImage);
// Operations
public:
	CCBMIRDoc *pDoc;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyImageView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CKeyImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CKeyImageView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString csKeyImage;
	CxImage img;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYIMAGEVIEW_H__4CA8BDD3_18D1_43BD_A8E2_FAFDDA76E1AF__INCLUDED_)
