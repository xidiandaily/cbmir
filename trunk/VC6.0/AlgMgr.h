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
	int iWidth;		//ͼ����
	int iHeight;	//ͼ��߶�
	int iPaletteSize;//��ɫ���С
	int iBitPerPixel;//ÿ������bit��
	RGBQUAD *pPalette;	//��ɫ������
	BYTE *pImage;	//ͼ������
}BitmapInfo;

typedef struct tagSimilar
{
	int iImageIndex;	
	double dSimilar;
}Similar;

/*�߳����Խṹ����*/
typedef struct tagThreadAttrib
{
	DWORD dThreadID;	//�߳�ID��
	HANDLE hThread;		//�߳̾��
}ThreadAttrib;

class Algorithm;

class AlgMgr
{
public:	
	AlgMgr(void);
	~AlgMgr(void);

	//Brief �����㷨
	//Param hWnd ������
	//      csAlgName �㷨����
	//      csImagePath ͼ�����ݿ�·��
	//      csKeyImagePath �ؼ�ͼ����·��
	void RunAlg(HWND hWnd,
				const CString &csAlgName,
		        const CString &csImagePath,
				const CString &csKeyImagePath,
				int iShowNum);
	
	//Brief ���㷨������ע���㷨
	//Param algΪ���㷨ָ��
	//Remark ���ע��ɹ����򷵻�TRUE
	//       ���ע��ʧ�ܣ��򷵻�FALSE
	//       ���㷨���������㷨�����������ָ����㷨
	BOOL RegAlg(Algorithm *alg);
	
	//Brief ���㷨������ע��һ���㷨
	//Param alg ָ�����㷨ָ��
	void UnRegAlg(Algorithm *alg);

	//Brief ɾ���㷨�����е������㷨
	void UnRegAlgAll(); 
	
	//Brief �õ��㷨�������е������㷨����
	//Param OUT csArray �ַ������飬���㷨�������е��㷨������������
	void GetAlgAllName(CStringArray &csArray);

	//Brief ���ü�������ͼ������
	//Param m_iImageNo ͼ������
	void SetResultNum(int iImageNum);
	
	CString &GetImageName(int iIndex) { return vecImage[iIndex]; }

private:
	//Brief ��ͼ�����ƥ����߳�
	//Param lp ָ��AlgMgr��ָ��
	//Remark ϵͳ���ö���߳̽���ͼ��ƥ�䣬
	//       ÿ���߳�������һ��Algorithm����
	static unsigned __stdcall SearchImage(LPVOID lp);
	
	static unsigned __stdcall Notify(LPVOID lp);
	//Brief �õ�ͼ�����㷨
	//Param csAlgName �㷨������
	//Return Algorithm * ͼ�����㷨ָ��
	//Remark �㷨����������ָ�����㷨����������ָ��
	list<Algorithm *>::iterator GetAlgorithm(const CString &csAlgName);
	
	//Brief ��ͼ�����ݿ��е�ͼƬ����������
	//Param m_strImagePath ͼ�����ݿ�·��
	void SelectDirectory(const CString &m_strImagePath);
	
	void AlgMgr::SaveInfo(HWND hWnd,const CString &csImagePath,const CString &csKeyImagePath);
	void AlgMgr::DataInit();
	void AlgMgr::ThreadProc();
	void AlgMgr::KeyImageProc();
	void AlgMgr::ImageRetrieveProc();
	void AlgMgr::__RunAlg(const CString &csAlgName);

public:
	list<Algorithm *> algList;	//�洢�㷨ָ�������
	Algorithm *algCur;
	
	CxImage m_imgKeyImage;
	BitmapInfo bitmapInfoKeyImage;

	vector<CString> vecImage;	//���ͼ��������������
	vector<Similar> vecImageSimilar; //ͼ�����ƶ���������

	HWND hWnd;	//���������㷨��һ���߳�ִ������Ժ���ô��巢����Ϣ
	CString csKeyFileName;	//�ؼ�ͼ����
	CString csImagePath;	//ͼ�����ݿ�����·��
	
	int iImageIndex;	//��ʾ�̴߳����ͼ����ͼ�������е�����
	int iImagePerThread;	//ÿ���̴߳����ͼƬ��

	int iThreadNum;

	CRITICAL_SECTION csImageIndex; //��Ϊ����߳�Ҫ����iImageIndex����������Ҫ����
	CRITICAL_SECTION csResultSet;	

	HANDLE *pThreadAttrib;
};
