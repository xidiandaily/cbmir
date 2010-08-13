// CBMIRDoc.h : interface of the CCBMIRDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBMIRDOC_H__A59991CC_A727_4400_A51F_C89887F0408A__INCLUDED_)
#define AFX_CBMIRDOC_H__A59991CC_A727_4400_A51F_C89887F0408A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AlgMgr.h"
#include <vector>

class CCBMIRView;
class CIlView;
class CImageView;
class CKeyImageView;

class CCBMIRDoc : public CDocument
{
protected: // create from serialization only
	CCBMIRDoc();
	DECLARE_DYNCREATE(CCBMIRDoc)

// Attributes
public:
	CCBMIRView *pCBMIRView;
	CIlView *pIllView;
	CImageView *pImageView;
	CKeyImageView *pKeyImageView;

	AlgMgr m_algMgr;
// Operations
public:
	void SetDocumentSize(CSize size) 
	{
		this->size=size;
	}
	CSize GetDocumentSize()
	{
		return size;
	}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCBMIRDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCBMIRDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CCBMIRDoc)
	afx_msg void OnRetrieveSetting();
	afx_msg void OnRetrieveStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_strKeyImage;	
	CString m_strImagePath;
	int		m_iImageNo;

	CSize size;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBMIRDOC_H__A59991CC_A727_4400_A51F_C89887F0408A__INCLUDED_)
