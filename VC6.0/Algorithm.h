#pragma once

#include "AlgMgr.h"

class Algorithm
{
public:
	Algorithm(void);
	~Algorithm(void);
	
	//Brief �ؼ�ͼ����
	//Param pBitmapInfo ָ��ͼ����Ϣ��ָ��
	//Remark �Թؼ�ͼ����Ԥ����������ȡ�Ȳ���
	virtual void KeyImageProc(BitmapInfo *pBitmapInfo)=0;
	virtual void KeyImageProc(CString *cs)=0;
	
	//Brief ƥ��ͼ����
	//Param pBitmapInfo ָ��ͼ����Ϣ��ָ��
	//Remark ��ƥ��ͼ�����Ԥ����������ȡ�Ȳ���
	virtual void FoundImageProc(BitmapInfo *pBitmapInfo)=0;	
	virtual void FoundImageProc(CString *cs)=0;
	

	//Brief ����ͼ�����ƶ�
	//Return double �ؼ�ͼ��ƥ��ͼ������ƶ�
	virtual double ImageMatch()=0;

	//Brief �㷨��ʼ��
	//Remark ����㷨����Ҫ��ʼ������˺�����Ӧ��Ϊ��
	virtual BOOL AlgInit()=0;

	//Brief �����㷨
	//Remark ����㷨ִ�����֮����Ҫ���ڴ�����˺�����Ӧ��Ϊ��
	virtual void AlgDestroy()=0;

	//Brief �õ��µ��㷨����
	//Return Algorithm * ָ���µ��㷨�����ָ��
	//Remark ͨ���ú������õ�ָ���㷨���¶����Ա��ڶ��߳��д���
	virtual Algorithm * NewObject()=0;

public:
	//Brief �㷨����,�㷨�������Դ����ָ��㷨
	CString csAlgName;
};
