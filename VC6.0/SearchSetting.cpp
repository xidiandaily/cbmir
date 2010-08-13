// SearchSetting.cpp : implementation file
//

#include "stdafx.h"
#include "CBMIR.h"
#include "SearchSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SearchSetting dialog


SearchSetting::SearchSetting(CWnd* pParent /*=NULL*/)
	: CDialog(SearchSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(SearchSetting)
	m_strKeyImage = _T("");
	m_ImageNum = 10;
	//}}AFX_DATA_INIT
}


void SearchSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SearchSetting)
	DDX_Text(pDX, IDC_EDIT_KEYIMAGE_PATH, m_strKeyImage);
	DDX_Text(pDX, IDC_EDIT_IMAGE_NUM, m_ImageNum);
	DDV_MinMaxInt(pDX, m_ImageNum, 0, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SearchSetting, CDialog)
	//{{AFX_MSG_MAP(SearchSetting)
	ON_BN_CLICKED(IDC_BTN_GLANCE, OnBtnGlance)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SearchSetting message handlers

BOOL SearchSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	((CComboBox *)GetDlgItem(IDC_CMB_SEARCH_PART))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_CMB_SEARCH_TYPE))->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SearchSetting::OnBtnGlance() 
{
	CFileDialog m_cfDlg(TRUE);

	m_cfDlg.m_ofn.lpstrTitle=_T("选择关键图");
	m_cfDlg.m_ofn.lpstrFilter=_T("*.bmp | *.jpg");

	if(m_cfDlg.DoModal()==IDOK)
	{
		CString m_strFileName=m_cfDlg.GetPathName();
		CString m_strExt=m_strFileName.Right(3);
		if(m_strExt.CompareNoCase("bmp") || m_strExt.CompareNoCase("jpg")==0)
		{
			m_strKeyImage=m_cfDlg.GetPathName();				
			m_strImagePath = m_strKeyImage.Left(m_strKeyImage.ReverseFind('\\')+1);
		}
		else 
		{
			MessageBox("请选择BMP图像","提示",MB_ICONQUESTION);
			m_strKeyImage=_T("");			
			m_strImagePath =_T("");
		}
		
		UpdateData(FALSE);
	}
}

void SearchSetting::OnOK() 
{
	UpdateData(TRUE);
	
	if(m_strKeyImage.IsEmpty())
	{
		MessageBox(_T("请选择关键图"),_T("提示"),MB_ICONQUESTION);
		return ;
	}

	CString m_strType;
	GetDlgItem(IDC_CMB_SEARCH_TYPE)->GetWindowText(m_strType);
	if(m_strType.Compare(_T("在线数据库"))==0)
	{
		MessageBox("本版本尚未支持在线数据库模式","抱歉",MB_ICONQUESTION);
		m_strKeyImage=_T("");			
		m_strImagePath =_T("");
	}
	
	CString m_strPart;
	GetDlgItem(IDC_CMB_SEARCH_PART)->GetWindowText(m_strPart);
	if(m_strPart.Compare(_T("jpg"))!=0)
	{
		MessageBox("本系统尚未支持bmp/png格式图像","抱歉",MB_ICONQUESTION);
		m_strKeyImage=_T("");			
		m_strImagePath =_T("");
	}	

	if(m_strPart.Compare(_T("jpg"))!=0 || m_strType.Compare(_T("在线数据库"))==0)
		return;
	

	//m_strImagePath=_T("Image\\")+m_strType+_T("\\")+m_strPart;. by chiyulong 2010-7-17 8:34:15 

	CDialog::OnOK();
}
