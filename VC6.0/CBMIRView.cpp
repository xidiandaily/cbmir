// CBMIRView.cpp : implementation of the CCBMIRView class
//

#include "stdafx.h"
#include "CBMIR.h"

#include "CBMIRDoc.h"
#include "CBMIRView.h"
//#include "ximage.h"
#include "ImageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCBMIRView

IMPLEMENT_DYNCREATE(CCBMIRView, CFormView)

BEGIN_MESSAGE_MAP(CCBMIRView, CFormView)
	//{{AFX_MSG_MAP(CCBMIRView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_MESSAGE(WM_ALG_DONE,OnAlgDone)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCBMIRView construction/destruction

CCBMIRView::CCBMIRView()
	: CFormView(CCBMIRView::IDD)
	, 	bSearchOk(FALSE)
{
	//{{AFX_DATA_INIT(CCBMIRView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCBMIRView::~CCBMIRView()
{
}

void CCBMIRView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCBMIRView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CCBMIRView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

void CCBMIRView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
	GetDocument()->pCBMIRView=this;
}

/////////////////////////////////////////////////////////////////////////////
// CCBMIRView printing

BOOL CCBMIRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCBMIRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CCBMIRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CCBMIRView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CCBMIRView diagnostics

#ifdef _DEBUG
void CCBMIRView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCBMIRView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCBMIRDoc* CCBMIRView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCBMIRDoc)));
	return (CCBMIRDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCBMIRView message handlers
void CCBMIRView::DeleteAllCell()
{
	vector<Cell *>::iterator it;
	for(it=vecCell.begin();it!=vecCell.end();++it)
	{
		(*it)->m_Feedback.DestroyWindow();
		(*it)->m_Image.DestroyWindow();
		(*it)->m_Similar.DestroyWindow();
		delete (*it);
	}
	vecCell.clear();
}

Cell * CCBMIRView::CreateCell(int iX,int iY)
{
	Cell *pCell=new Cell();

	RECT rectImage;
	rectImage.left=iX;
	rectImage.right=iX+THUMB_WIDTH;
	rectImage.top=iY;
	rectImage.bottom=iY+THUMB_HEIGHT;
	pCell->m_Image.Create(NULL,WS_VISIBLE|WS_CHILD|SS_BLACKFRAME,rectImage,this);
	pCell->m_ImagePos.x=iX;
	pCell->m_ImagePos.y=iY;

	RECT rectSimilar;
	rectSimilar.left=rectImage.left;
	rectSimilar.right=rectSimilar.left+EDIT_WIDTH;
	rectSimilar.top=rectImage.bottom+THUMB_HEIGHT_EDIT;
	rectSimilar.bottom=rectSimilar.top+EDIT_HEIGHT;
	pCell->m_Similar.Create(ES_READONLY|WS_BORDER|ES_AUTOHSCROLL|WS_VISIBLE|WS_CHILD,rectSimilar,this,IDD_EDIT_SIMILAR);

	RECT rectFeedBack;
	rectFeedBack.left=rectSimilar.right+EDIT_WIDTH_FEEDBACK;
	rectFeedBack.right=rectImage.right;
	rectFeedBack.top=rectSimilar.top;
	rectFeedBack.bottom=rectSimilar.bottom;
	pCell->m_Feedback.Create(CBS_DROPDOWNLIST|WS_VISIBLE|WS_CHILD,rectFeedBack,this,IDD_CMB_FEEDBACK);
	pCell->m_Feedback.AddString("很相似");
	pCell->m_Feedback.AddString("相似");
	pCell->m_Feedback.AddString("一般");
	pCell->m_Feedback.AddString("不相似");
	pCell->m_Feedback.AddString("极不相似");
	pCell->m_Feedback.SetCurSel(0);
	
	return pCell;
}

void CCBMIRView::SetCell(int iCellNum)
{
	DeleteAllCell();
	
	bSearchOk=FALSE;

	RECT rect;
	GetClientRect(&rect);
	
	int iHeight=0;
	int iWidth=rect.right-rect.left;
	
	if(iWidth>THUMB_WIDTH)
	{
		int iCol=iWidth/(THUMB_WIDTH+THUMB_WIDTH_THUMB);
		int iRow=(iCellNum+iCol-1)/iCol;
		iHeight=iRow*(THUMB_HEIGHT+EDIT_HEIGHT+THUMB_HEIGHT_EDIT+THUMB_HEIGHT_THUMB);

		int iCnt=0;
		int iX=rect.left;
		int iY=rect.top;

		for(int i=0;i<iRow;i++)
		{
			for(int j=0;j<iCol&&iCnt<iCellNum;j++,iCnt++)
			{
				Cell *pCell=CreateCell(iX,iY);
				vecCell.push_back(pCell);
				iX+=THUMB_WIDTH+THUMB_WIDTH_THUMB;
			}
			iX=0;
			iY+=THUMB_HEIGHT+EDIT_HEIGHT+THUMB_HEIGHT_EDIT+THUMB_HEIGHT_THUMB;
		}
		GetDocument()->SetDocumentSize(CSize(iWidth,iHeight));
		SetScrollSizes(MM_TEXT,CSize(iWidth,iHeight));
	}
}

void CCBMIRView::ShowCell()
{	
	AlgMgr *pMgr=&(GetDocument()->m_algMgr);

	if(bSearchOk)
	{
		int iSize=0;
		if(pMgr->vecImage.size()>vecCell.size())
		{
			iSize=vecCell.size();
		}
		else 
		{
			iSize=pMgr->vecImage.size();
		}		
		for(int i=0;i<iSize;i++)
		{
			int iImageIndex=pMgr->vecImageSimilar[i].iImageIndex;
			if(iImageIndex!=-1)
			{
				CString csSimilar;
				csSimilar.Format("%.4f",pMgr->vecImageSimilar[i].dSimilar);
				(vecCell[i]->m_Similar).SetWindowText(csSimilar);

				CString csImageName=pMgr->vecImage[iImageIndex];
				CxImage img(csImageName,CXIMAGE_FORMAT_JPG);
				if(img.IsValid())
				{
					RECT rect;
					CWnd *pWnd=(CWnd *)(&(vecCell[i]->m_Image));
					pWnd->GetClientRect(&rect);
					CDC *pDC=pWnd->GetDC();
					img.Draw(pDC->m_hDC,rect);

					pWnd->ReleaseDC(pDC);
				}
			}		
		}	
	}
}

void CCBMIRView::OnAlgDone(WPARAM wParam,LPARAM lParam)
{
	bSearchOk=TRUE;
	ShowCell();	
}

void CCBMIRView::OnDraw(CDC* pDC) 
{		
	ShowCell();
}

void CCBMIRView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	AlgMgr *pMgr=&(GetDocument()->m_algMgr);
	
	if(bSearchOk)
	{
		int iCellSize=vecCell.size();
		int iSimilarSize=pMgr->vecImage.size();
		int iSize=((iCellSize>iSimilarSize)?iSimilarSize:iCellSize);

		for(int i=0;i<iSize;i++)
		{
			int iX=vecCell[i]->m_ImagePos.x;
			int iY=vecCell[i]->m_ImagePos.y;
			
			if(point.x>iX && point.x<iX+THUMB_WIDTH&&point.y>iY&&point.y<iY+THUMB_HEIGHT)
			{
				int iImageIndex=pMgr->vecImageSimilar[i].iImageIndex;
				if(iImageIndex!=-1)
				{
					CString csImageName=pMgr->vecImage[iImageIndex];
					GetDocument()->pImageView->ShowImage(csImageName);
				}
				break;
			}
		}
	}

	CFormView::OnLButtonDown(nFlags, point);
}
