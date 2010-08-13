// ImageView.cpp : implementation file
//

#include "stdafx.h"
#include "CBMIR.h"
#include "ImageView.h"
#include "CBMIRDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageView

IMPLEMENT_DYNCREATE(CImageView, CScrollView)

CImageView::CImageView()
{
}

CImageView::~CImageView()
{
}


BEGIN_MESSAGE_MAP(CImageView, CScrollView)
	//{{AFX_MSG_MAP(CImageView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageView drawing

void CImageView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	((CCBMIRDoc *)GetDocument())->pImageView=this;
}

void CImageView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	ShowImage(csImageName);
}

/////////////////////////////////////////////////////////////////////////////
// CImageView diagnostics

#ifdef _DEBUG
void CImageView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageView message handlers
void CImageView::ShowImage(const CString &csImageName)
{
	if(!csImageName.IsEmpty())
	{
		if(this->csImageName.CompareNoCase(csImageName)!=0)
		{
			this->csImageName=csImageName;
			HBITMAP hBitmap=(HBITMAP)::LoadImage(NULL,csImageName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			if(hBitmap)
			{
				img.DeleteObject();
				img.Detach();
				img.Attach(hBitmap);
			}
		}
		
		if(img.m_hObject)
		{
			BITMAP bm;
			img.GetObject(sizeof(BITMAP),&bm);
			CDC *pDC=GetDC();
			HDC hDC=CreateCompatibleDC(pDC->m_hDC);
			HBITMAP hOldBitmap=(HBITMAP)SelectObject(hDC,img.GetSafeHandle());
			BitBlt(pDC->m_hDC,0,0,bm.bmWidth,bm.bmHeight,hDC,0,0,SRCCOPY);
			SelectObject(hDC,hOldBitmap);
			DeleteDC(hDC);
			ReleaseDC(pDC);		
		}
	}
}
