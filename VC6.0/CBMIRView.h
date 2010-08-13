// CBMIRView.h : interface of the CCBMIRView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBMIRVIEW_H__6F739DF6_7D83_4B87_94D5_974E2B440818__INCLUDED_)
#define AFX_CBMIRVIEW_H__6F739DF6_7D83_4B87_94D5_974E2B440818__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
using namespace std;
#include <vector>

#ifndef WM_ALG_DONE 
#define WM_ALG_DONE WM_USER+100
#endif 

#define THUMB_WIDTH  144
#define THUMB_HEIGHT 144

#define EDIT_HEIGHT  21
#define EDIT_WIDTH	50

#define THUMB_HEIGHT_EDIT 2
#define EDIT_WIDTH_FEEDBACK 2

#define THUMB_WIDTH_THUMB 10
#define THUMB_HEIGHT_THUMB 10

typedef struct tagCell
{
	CStatic m_Image;
	CEdit   m_Similar;
	CComboBox m_Feedback;
	CPoint  m_ImagePos;
}Cell;

class CCBMIRDoc;

class CCBMIRView : public CFormView
{
protected: // create from serialization only
	CCBMIRView();
	DECLARE_DYNCREATE(CCBMIRView)

public:
	//{{AFX_DATA(CCBMIRView)
	enum{ IDD = IDD_CBMIR_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CCBMIRDoc* GetDocument();

	void SetCell(int iCellNum);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCBMIRView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCBMIRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnAlgDone(WPARAM wParam,LPARAM lParam);
// Generated message map functions
protected:
	//{{AFX_MSG(CCBMIRView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	vector<Cell *> vecCell;

private:
	void DeleteAllCell();
	Cell *CreateCell(int iX,int iY);
	void ShowCell();
	BOOL bSearchOk;
};

#ifndef _DEBUG  // debug version in CBMIRView.cpp
inline CCBMIRDoc* CCBMIRView::GetDocument()
   { return (CCBMIRDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBMIRVIEW_H__6F739DF6_7D83_4B87_94D5_974E2B440818__INCLUDED_)
