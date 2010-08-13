// CBMIRDoc.cpp : implementation of the CCBMIRDoc class
//

#include "stdafx.h"
#include "CBMIR.h"

#include "CBMIRDoc.h"
#include "SearchSetting.h"
#include "CBMIRView.h"
#include "MainFrm.h"
#include "TestAlg.h"
#include "JpegAlg.h"
#include "KeyImageView.h"
#include "IlView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCBMIRDoc

IMPLEMENT_DYNCREATE(CCBMIRDoc, CDocument)

BEGIN_MESSAGE_MAP(CCBMIRDoc, CDocument)
	//{{AFX_MSG_MAP(CCBMIRDoc)
	ON_COMMAND(IDD_RETRIEVE_SETTING, OnRetrieveSetting)
	ON_COMMAND(IDD_RETRIEVE_START, OnRetrieveStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCBMIRDoc construction/destruction

CCBMIRDoc::CCBMIRDoc():
  pCBMIRView(NULL)
, pIllView(NULL)
, pImageView(NULL)
, pKeyImageView(NULL)
{
	m_algMgr.RegAlg(new CTestAlg("Test"));
    m_algMgr.RegAlg(new CJpegAlg("Jpeg"));
}

CCBMIRDoc::~CCBMIRDoc()
{
	m_algMgr.UnRegAlgAll();
}

BOOL CCBMIRDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCBMIRDoc serialization

void CCBMIRDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCBMIRDoc diagnostics

#ifdef _DEBUG
void CCBMIRDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCBMIRDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCBMIRDoc commands

void CCBMIRDoc::OnRetrieveSetting() 
{
	SearchSetting m_dlgSetting;

	if(m_dlgSetting.DoModal()==IDOK)
	{
		m_strImagePath=m_dlgSetting.m_strImagePath;
		m_strKeyImage=m_dlgSetting.m_strKeyImage;
		m_iImageNo=m_dlgSetting.m_ImageNum;

		if(pKeyImageView)
		{
			pKeyImageView->ShowKeyImage(m_strKeyImage);
		}

		if(pCBMIRView)
		{
			pCBMIRView->SetCell(m_iImageNo);
		}
	}
}

void CCBMIRDoc::OnRetrieveStart() 
{
	m_algMgr.RunAlg(pCBMIRView->m_hWnd,"Jpeg",m_strImagePath,m_strKeyImage,m_iImageNo);
}
