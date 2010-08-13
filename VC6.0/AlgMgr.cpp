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
	//初始化互斥量
	InitializeCriticalSection(&csImageIndex);
	InitializeCriticalSection(&csResultSet);
}

AlgMgr::~AlgMgr(void)
{
	//销毁互斥量
	DeleteCriticalSection(&csImageIndex);
	DeleteCriticalSection(&csResultSet);

	UnRegAlgAll();
}

BOOL AlgMgr::RegAlg(Algorithm *alg)
{
	/*
		本算法管理器依据算法的名字区分算法。
		首先在算法管理器的算法链表中查找该算法，
		如果存在，则返回TRUE；
		如果不存在，则注册该算法，注册成功返回TRUE，
		                          注册失败返回FALSE
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
		//得到图像开始序号
		int iNo;
		int iEndNo;
		EnterCriticalSection(&(pMgr->csImageIndex));
		iNo=pMgr->iImageIndex;
		pMgr->iImageIndex+=pMgr->iImagePerThread;
		iEndNo=pMgr->iImageIndex-1;
		LeaveCriticalSection(&(pMgr->csImageIndex));

		//声明Algorithm对象
		Algorithm *pAlg=pMgr->algCur->NewObject();
		//算法初始化
		pAlg->AlgInit();
			
		pAlg->KeyImageProc(&pMgr->csKeyFileName);
		//得到图像总数
		int iImageTotalNum=pMgr->vecImage.size();

		int i=0;
		CxImage m_imgImage;
		for(i=iNo;i<iEndNo;i++)
		{
			CString csFeate;
			CString csFileName=(pMgr->vecImage)[i];
			CString csNum;			
			//根据CS找出特征值的路径
			csFeate = pMgr->csImagePath+_T("\\Feature\\");
			csNum = csFileName.Left(csFileName.ReverseFind('.'));
			csFeate = csFeate + _T("FT_")+csNum+_T(".dat");
			
			//计算特征值并存放到
			pAlg->FoundImageProc(&csFeate);
			
			//关键图和匹配图像进行匹配
			(pMgr->vecImageSimilar)[i].dSimilar=pAlg->ImageMatch();
			(pMgr->vecImageSimilar)[i].iImageIndex=i;				
		}
		//销毁算法
		pAlg->AlgDestroy();
		//向窗体发送消息
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
	//保存窗体句柄
	this->hWnd=hWnd;
	//保存图像数据库路径
	this->csImagePath=csImagePath;
	//保存关键图路径
	this->csKeyFileName=csKeyImagePath;
}

void AlgMgr::DataInit()
{
	//清空图像名容器
	vecImage.clear();
	//清空相似度容器
	vecImageSimilar.clear();
	//选择图像数据库下的图像
	SelectDirectory(csImagePath);
	
	vecImageSimilar.resize(vecImage.size());
}

void AlgMgr::ThreadProc()
{
	//清空线程数组
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
	//计算要启动的线程数,
	//图片量小时，每个线程最多处理10副图片
	//而最多启动25个线程
	int iLen=vecImage.size();
	iThreadNum=(iLen+9)/10;
	if(iThreadNum>50)
	{
		iThreadNum=50;
	}
	//计算每个线程要处理的图片数
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
	//得到图像处理算法
	list<Algorithm *>::iterator it=GetAlgorithm(csAlgName);
	if(it!=algList.end())
	{
		algCur=*it;
		//启动线程
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
	//保存基本信息
	SaveInfo(hWnd,csImagePath,csKeyImagePath);
	//算法管理器中的数据单元预处理
	DataInit();	
	//图像检索预处理
	ImageRetrieveProc();
	//关键图处理
	KeyImageProc();
	//线程预处理
	ThreadProc();
	//运行算法
	__RunAlg(csAlgName);	
}
