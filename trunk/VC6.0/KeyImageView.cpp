// KeyImageView.cpp : implementation file
//

#include "stdafx.h"
#include "CBMIR.h"
#include "KeyImageView.h"
#include "CBMIRDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeyImageView

IMPLEMENT_DYNCREATE(CKeyImageView, CFormView)

CKeyImageView::CKeyImageView()
	: CFormView(CKeyImageView::IDD)
{
	//{{AFX_DATA_INIT(CKeyImageView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CKeyImageView::~CKeyImageView()
{
}

void CKeyImageView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyImageView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKeyImageView, CFormView)
	//{{AFX_MSG_MAP(CKeyImageView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyImageView diagnostics

#ifdef _DEBUG
void CKeyImageView::AssertValid() const
{
	CFormView::AssertValid();
}

void CKeyImageView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKeyImageView message handlers
void CKeyImageView::ShowKeyImage(const CString &csKeyImage)
{
	CDC *pDC=GetDC();
	pDC->TextOut(0,0,"¹Ø¼üÍ¼:");
	
	if(!csKeyImage.IsEmpty())
	{
		if(this->csKeyImage.CompareNoCase(csKeyImage)!=0)
		{
			this->csKeyImage=csKeyImage;
			img.Load(csKeyImage,CXIMAGE_FORMAT_JPG);
		}
		if(img.IsValid())
		{
			int iWidth=img.GetWidth();
			int iHeight=img.GetHeight();
			double dTrueRatio=(double)iWidth/iHeight;

			CRect rect;			
			GetClientRect(&rect);		
			double dEffectRatio=(double)rect.Width()/(rect.Height()-TEXT_HEIGHT);
			
			int x,y,cx,cy;
			if(dEffectRatio>dTrueRatio)
			{
				cy=rect.Height()-TEXT_HEIGHT;
				cx=cy*dTrueRatio;
				x=0;
				y=TEXT_HEIGHT;
			}
			else 
			{
				cx=rect.Width();
				cy=cx/dTrueRatio;
				x=0;
				y=TEXT_HEIGHT;
			}

			img.Draw(pDC->m_hDC,CRect(x,y,cx,cy));
		}		
	}

	ReleaseDC(pDC);
}

void CKeyImageView::OnDraw(CDC* pDC) 
{
	ShowKeyImage(((CCBMIRDoc *)GetDocument())->m_strKeyImage);	
}

void CKeyImageView::OnInitialUpdate() 
{
	((CCBMIRDoc *)GetDocument())->pKeyImageView=this;

	CFormView::OnInitialUpdate();		
}
