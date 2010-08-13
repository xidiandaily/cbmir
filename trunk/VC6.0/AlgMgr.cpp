#include "StdAfx.h"
#include "AlgMgr.h"
#include "Algorithm.h"
#include "Resource.h"
#include "direct.h"
#include "process.h"

AlgMgr::AlgMgr(void)
: csKeyFileName(_T(""))
, csImagePath(_T(""))
, iImageIndex(0)
, algCur(NULL)
, hWnd(NULL)
, iImagePerThread(0)
, iThreadNum(0)
, pThreadAttrib(NULL)
{
	//��ʼ��������
	InitializeCriticalSection(&csImageIndex);
	InitializeCriticalSection(&csResultSet);
}

AlgMgr::~AlgMgr(void)
{
	//���ٻ�����
	DeleteCriticalSection(&csImageIndex);
	DeleteCriticalSection(&csResultSet);

	UnRegAlgAll();
}

BOOL AlgMgr::RegAlg(Algorithm *alg)
{
	/*
		���㷨�����������㷨�����������㷨��
		�������㷨���������㷨�����в��Ҹ��㷨��
		������ڣ��򷵻�TRUE��
		��������ڣ���ע����㷨��ע��ɹ�����TRUE��
		                          ע��ʧ�ܷ���FALSE
	 */
	list<Algorithm *>::iterator it=GetAlgorithm(alg->csAlgName);
	if(it==algList.end())
	{
		algList.push_front(alg);
	}

	return TRUE;
}

void AlgMgr::UnRegAlg(Algorithm *alg)
{
	list<Algorithm *>::iterator it=GetAlgorithm(alg->csAlgName);
	if(it!=algList.end())
	{
		delete *it;
		algList.erase(it);
	}	
}

void AlgMgr::UnRegAlgAll()
{
	list<Algorithm *>::iterator it;
	
	for(it=algList.begin();it!=algList.end();++it)
	{
		delete *it;	
	}	
	algList.clear();
}

list<Algorithm *>::iterator AlgMgr::GetAlgorithm(const CString &csAlgName)
{
	list<Algorithm *>::iterator it;

	for(it=algList.begin();it!=algList.end();++it)
	{
		if((*it)->csAlgName.CompareNoCase(csAlgName)==0)
		{
			break;
		}
	}

	return it;
}

void AlgMgr::GetAlgAllName(CStringArray &csArray)
{
	list<Algorithm *>::iterator it;

	for(it=algList.begin();it!=algList.end();++it)
	{
		csArray.Add((*it)->csAlgName);
	}
}

unsigned __stdcall AlgMgr::SearchImage(LPVOID lp)
{
	AlgMgr * pMgr=(AlgMgr *)lp;
	
	if(pMgr->m_imgKeyImage.IsValid())
	{
		//�õ�ͼ��ʼ���
		int iNo;
		int iEndNo;
		EnterCriticalSection(&(pMgr->csImageIndex));
		iNo=pMgr->iImageIndex;
		pMgr->iImageIndex+=pMgr->iImagePerThread;
		iEndNo=pMgr->iImageIndex-1;
		LeaveCriticalSection(&(pMgr->csImageIndex));

		//����Algorithm����
		Algorithm *pAlg=pMgr->algCur->NewObject();
		//�㷨��ʼ��
		pAlg->AlgInit();
			
		pAlg->KeyImageProc(&pMgr->csKeyFileName);
		//�õ�ͼ������
		int iImageTotalNum=pMgr->vecImage.size();

		int i=0;
		CxImage m_imgImage;
		for(i=iNo;i<iEndNo;i++)
		{
			CString csFeate;
			CString csFileName=(pMgr->vecImage)[i];
			CString csNum;			
			//����CS�ҳ�����ֵ��·��
			csFeate = pMgr->csImagePath+_T("\\Feature\\");
			csNum = csFileName.Left(csFileName.ReverseFind('.'));
			csFeate = csFeate + _T("FT_")+csNum+_T(".dat");
			
			//��������ֵ����ŵ�
			pAlg->FoundImageProc(&csFeate);
			
			//�ؼ�ͼ��ƥ��ͼ�����ƥ��
			(pMgr->vecImageSimilar)[i].dSimilar=pAlg->ImageMatch();
			(pMgr->vecImageSimilar)[i].iImageIndex=i;				
		}
		//�����㷨
		pAlg->AlgDestroy();
		//���巢����Ϣ
		iEndNo=i;
		
		delete pAlg;
	}

	_endthreadex(0);

	return 0;
}

bool Sort(Similar &a,Similar &b)
{
	return a.dSimilar>b.dSimilar;
}

unsigned __stdcall AlgMgr::Notify(LPVOID lp)
{
	AlgMgr *pMgr=(AlgMgr *)lp;
	
	if(WaitForMultipleObjects(pMgr->iThreadNum,pMgr->pThreadAttrib,TRUE,INFINITE)==WAIT_OBJECT_0)
	{
		sort(pMgr->vecImageSimilar.begin(),pMgr->vecImageSimilar.end(),Sort);
		::SendMessage(pMgr->hWnd,WM_ALG_DONE,pMgr->vecImage.size(),0);
	}
	
	return 0;
}

void AlgMgr::SelectDirectory(const CString &m_strImagePath)
{
	CFileFind cf;
	
	chdir(m_strImagePath);
	BOOL bWork=cf.FindFile(_T("*.jpg"));
	
	while(bWork)
	{
		bWork=cf.FindNextFile();
		if(!cf.IsDirectory()&&!cf.IsDots())
		{
			vecImage.push_back(cf.GetFileName());
		}
	}
	cf.Close();
}

void AlgMgr::SaveInfo(HWND hWnd,const CString &csImagePath,const CString &csKeyImagePath)
{
	//���洰����
	this->hWnd=hWnd;
	//����ͼ�����ݿ�·��
	this->csImagePath=csImagePath;
	//����ؼ�ͼ·��
	this->csKeyFileName=csKeyImagePath;
}

void AlgMgr::DataInit()
{
	//���ͼ��������
	vecImage.clear();
	//������ƶ�����
	vecImageSimilar.clear();
	//ѡ��ͼ�����ݿ��µ�ͼ��
	SelectDirectory(csImagePath);
	
	vecImageSimilar.resize(vecImage.size());
}

void AlgMgr::ThreadProc()
{
	//����߳�����
	if(pThreadAttrib!=NULL)
	{
		if(WaitForMultipleObjects(iThreadNum,pThreadAttrib,TRUE,INFINITE)==WAIT_OBJECT_0)
		{
			for(int i=0;i<iThreadNum;i++)
			{
				CloseHandle(pThreadAttrib[i]);
			}
			delete pThreadAttrib;
			pThreadAttrib=NULL;
		}
	}
}

void AlgMgr::KeyImageProc()
{
	m_imgKeyImage.Load(csKeyFileName,CXIMAGE_FORMAT_JPG);
	
	if(m_imgKeyImage.IsValid())
	{
		bitmapInfoKeyImage.pPalette=m_imgKeyImage.GetPalette();
		bitmapInfoKeyImage.iPaletteSize=m_imgKeyImage.GetPaletteSize();
		bitmapInfoKeyImage.pImage=m_imgKeyImage.GetBits();
		bitmapInfoKeyImage.iWidth=m_imgKeyImage.GetWidth();
		bitmapInfoKeyImage.iHeight=m_imgKeyImage.GetHeight();
		bitmapInfoKeyImage.iBitPerPixel=m_imgKeyImage.GetBpp();
	}
}

void AlgMgr::ImageRetrieveProc()
{
	//����Ҫ�������߳���,
	//ͼƬ��Сʱ��ÿ���߳���ദ��10��ͼƬ
	//���������25���߳�
	int iLen=vecImage.size();
	iThreadNum=(iLen+9)/10;
	if(iThreadNum>50)
	{
		iThreadNum=50;
	}
	//����ÿ���߳�Ҫ�����ͼƬ��
	iImagePerThread=(iLen+iThreadNum-1)/iThreadNum;
	iImageIndex=0;
/*
	iThreadNum = 1;
	iImagePerThread = vecImage.size();
	iImageIndex = 0;
	*/
}

void AlgMgr::__RunAlg(const CString &csAlgName)
{
	unsigned int id;
	//�õ�ͼ�����㷨
	list<Algorithm *>::iterator it=GetAlgorithm(csAlgName);
	if(it!=algList.end())
	{
		algCur=*it;
		//�����߳�
		pThreadAttrib=new HANDLE[iThreadNum];
		for(int i=0;i<iThreadNum;i++)
		{
			pThreadAttrib[i]=(HANDLE)_beginthreadex(NULL,0,SearchImage,this,0,&id);
		///	DWORD dwThreadID;
		//	HANDLE hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)SearchImage,(LPVOID)this,0,&dwThreadID);
		//	arrThreadAttrib.Add(ThreadAttrib(dwThreadID,hThread));	
		//	SearchImage(this);
		}
	}
	//Notify(this);

	_beginthreadex(NULL,0,Notify,this,0,&id);
}

void AlgMgr::RunAlg(HWND hWnd, 
					const CString &csAlgName,
					const CString &csImagePath,
					const CString &csKeyImagePath,
					int iShowNum)
{
	//���������Ϣ
	SaveInfo(hWnd,csImagePath,csKeyImagePath);
	//�㷨�������е����ݵ�ԪԤ����
	DataInit();	
	//ͼ�����Ԥ����
	ImageRetrieveProc();
	//�ؼ�ͼ����
	KeyImageProc();
	//�߳�Ԥ����
	ThreadProc();
	//�����㷨
	__RunAlg(csAlgName);	
}
