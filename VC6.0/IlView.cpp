// IlView.cpp : implementation file
//

#include "stdafx.h"
#include "CBMIR.h"
#include "IlView.h"
#include "CBMIRDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIlView

IMPLEMENT_DYNCREATE(CIlView, CFormView)

CIlView::CIlView()
	: CFormView(CIlView::IDD)
{
	//{{AFX_DATA_INIT(CIlView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CIlView::~CIlView()
{
}

void CIlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIlView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIlView, CFormView)
	//{{AFX_MSG_MAP(CIlView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIlView diagnostics

#ifdef _DEBUG
void CIlView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIlView message handlers

void CIlView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	((CCBMIRDoc *)GetDocument()	)->pIllView=this;
}
