#pragma once

#include <vector>
#include <list>
#include <algorithm>
using namespace std;

#ifndef WM_ALG_DONE
#define WM_ALG_DONE WM_USER+100
#endif 

#include "ximage.h"

typedef struct tagBitmapInfo
{
	int iWidth;		//图像宽度
	int iHeight;	//图像高度
	int iPaletteSize;//调色板大小
	int iBitPerPixel;//每个像素bit数
	RGBQUAD *pPalette;	//调色板数据
	BYTE *pImage;	//图像数据
}BitmapInfo;

typedef struct tagSimilar
{
	int iImageIndex;	
	double dSimilar;
}Similar;

/*线程属性结构定义*/
typedef struct tagThreadAttrib
{
	DWORD dThreadID;	//线程ID号
	HANDLE hThread;		//线程句柄
}ThreadAttrib;

class Algorithm;

class AlgMgr
{
public:	
	AlgMgr(void);
	~AlgMgr(void);

	//Brief 运行算法
	//Param hWnd 窗体句柄
	//      csAlgName 算法名称
	//      csImagePath 图像数据库路径
	//      csKeyImagePath 关键图绝对路径
	void RunAlg(HWND hWnd,
				const CString &csAlgName,
		        const CString &csImagePath,
				const CString &csKeyImagePath,
				int iShowNum);
	
	//Brief 向算法管理器注册算法
	//Param alg为新算法指针
	//Remark 如果注册成功，则返回TRUE
	//       如果注册失败，则返回FALSE
	//       该算法管理器以算法的名字来区分各个算法
	BOOL RegAlg(Algorithm *alg);
	
	//Brief 从算法链表中注销一个算法
	//Param alg 指定的算法指针
	void UnRegAlg(Algorithm *alg);

	//Brief 删除算法链表中的所有算法
	void UnRegAlgAll(); 
	
	//Brief 得到算法管理器中的所有算法名称
	//Param OUT csArray 字符串数组，将算法管理器中的算法名称填入其中
	void GetAlgAllName(CStringArray &csArray);

	//Brief 设置检索出的图像数量
	//Param m_iImageNo 图像数量
	void SetResultNum(int iImageNum);
	
	CString &GetImageName(int iIndex) { return vecImage[iIndex]; }

private:
	//Brief 对图像进行匹配的线程
	//Param lp 指向AlgMgr的指针
	//Remark 系统采用多个线程进行图像匹配，
	//       每个线程中声明一个Algorithm对象
	static unsigned __stdcall SearchImage(LPVOID lp);
	
	static unsigned __stdcall Notify(LPVOID lp);
	//Brief 得到图像处理算法
	//Param csAlgName 算法的名字
	//Return Algorithm * 图像处理算法指针
	//Remark 算法链表中搜索指定的算法，并返回其指针
	list<Algorithm *>::iterator GetAlgorithm(const CString &csAlgName);
	
	//Brief 将图像数据库中的图片名放入容器
	//Param m_strImagePath 图像数据库路径
	void SelectDirectory(const CString &m_strImagePath);
	
	void AlgMgr::SaveInfo(HWND hWnd,const CString &csImagePath,const CString &csKeyImagePath);
	void AlgMgr::DataInit();
	void AlgMgr::ThreadProc();
	void AlgMgr::KeyImageProc();
	void AlgMgr::ImageRetrieveProc();
	void AlgMgr::__RunAlg(const CString &csAlgName);

public:
	list<Algorithm *> algList;	//存储算法指针的链表
	Algorithm *algCur;
	
	CxImage m_imgKeyImage;
	BitmapInfo bitmapInfoKeyImage;

	vector<CString> vecImage;	//存放图像名的向量容器
	vector<Similar> vecImageSimilar; //图像相似度容器容器

	HWND hWnd;	//窗体句柄，算法的一个线程执行完成以后，向该窗体发送消息
	CString csKeyFileName;	//关键图名称
	CString csImagePath;	//图像数据库所在路径
	
	int iImageIndex;	//标示线程处理的图像在图像容器中的索引
	int iImagePerThread;	//每个线程处理的图片数

	int iThreadNum;

	CRITICAL_SECTION csImageIndex; //因为多个线程要访问iImageIndex变量，所以要互斥
	CRITICAL_SECTION csResultSet;	

	HANDLE *pThreadAttrib;
};
