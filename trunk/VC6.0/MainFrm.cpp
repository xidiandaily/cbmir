// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CBMIR.h"

#include "MainFrm.h"
#include "CBMIRView.h"
#include "ImageView.h"
#include "KeyImageView.h"
#include "IlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cx=GetSystemMetrics(SM_CXSCREEN);
	cs.cy=GetSystemMetrics(SM_CYSCREEN);

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if(!m_spliter.CreateStatic(this,1,2))
		return FALSE;
	
	if(!m_spliterLeft.CreateStatic(&m_spliter,2,1,WS_CHILD|WS_VISIBLE,m_spliter.IdFromRowCol(0,0)))
		return FALSE;

	if(!m_spliterRight.CreateStatic(&m_spliter,2,1,WS_CHILD|WS_VISIBLE,m_spliter.IdFromRowCol(0,1)))
		return FALSE;

	if(!m_spliterLeft.CreateView(0,0,RUNTIME_CLASS(CKeyImageView),CSize(0,0),pContext))
		return FALSE;

	if(!m_spliterLeft.CreateView(1,0,RUNTIME_CLASS(CIlView),CSize(0,0),pContext))
		return FALSE;

	if(!m_spliterRight.CreateView(0,0,RUNTIME_CLASS(CImageView),CSize(0,0),pContext))
		return FALSE;

	if(!m_spliterRight.CreateView(1,0,RUNTIME_CLASS(CCBMIRView),CSize(0,0),pContext))
		return FALSE;

	m_spliter.SetColumnInfo(0,THUMB_WIDTH,0);

	m_spliterLeft.SetRowInfo(0,THUMB_HEIGHT,0);
	m_spliterLeft.SetColumnInfo(0,THUMB_WIDTH,0);

	return TRUE;
//	return CFrameWnd::OnCreateClient(lpcs, pContext);
}
