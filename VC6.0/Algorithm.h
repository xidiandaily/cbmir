#pragma once

#include "AlgMgr.h"

class Algorithm
{
public:
	Algorithm(void);
	~Algorithm(void);
	
	//Brief 关键图处理
	//Param pBitmapInfo 指向图像信息的指针
	//Remark 对关键图进行预处理，特征提取等操作
	virtual void KeyImageProc(BitmapInfo *pBitmapInfo)=0;
	virtual void KeyImageProc(CString *cs)=0;
	
	//Brief 匹配图像处理
	//Param pBitmapInfo 指向图像信息的指针
	//Remark 对匹配图像进行预处理，特征提取等操作
	virtual void FoundImageProc(BitmapInfo *pBitmapInfo)=0;	
	virtual void FoundImageProc(CString *cs)=0;
	

	//Brief 计算图像相似度
	//Return double 关键图和匹配图像的相似度
	virtual double ImageMatch()=0;

	//Brief 算法初始化
	//Remark 如果算法不需要初始化，则此函数体应该为空
	virtual BOOL AlgInit()=0;

	//Brief 销毁算法
	//Remark 如果算法执行完成之后不需要后期处理，则此函数体应该为空
	virtual void AlgDestroy()=0;

	//Brief 得到新的算法对象
	//Return Algorithm * 指向新的算法对象的指针
	//Remark 通过该函数，得到指定算法的新对象，以便在多线程中处理
	virtual Algorithm * NewObject()=0;

public:
	//Brief 算法名称,算法管理器以此区分各算法
	CString csAlgName;
};
