#if !defined(AFX_IMAGEVIEW_H__D80A1F8C_3F9D_4916_A5C4_82F9B7648A77__INCLUDED_)
#define AFX_IMAGEVIEW_H__D80A1F8C_3F9D_4916_A5C4_82F9B7648A77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageView view

class CImageView : public CScrollView
{
protected:
	CImageView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CImageView)

// Attributes
public:
	void ShowImage(const CString &csImageName);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CImageView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString csImageName;
	CBitmap img;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEVIEW_H__D80A1F8C_3F9D_4916_A5C4_82F9B7648A77__INCLUDED_)
