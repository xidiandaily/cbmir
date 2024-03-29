// CJpegAlg.h: interface for the CJpegAlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JPEGALG_H__0BC85B38_16D5_46D2_AD74_6C5BA56EA52F__INCLUDED_)
#define AFX_JPEGALG_H__0BC85B38_16D5_46D2_AD74_6C5BA56EA52F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Algorithm.h"
#include "ximage.h"

#define HEIGHT 256
#define WIDTH  256
#define BLOCK_SIZE 16
#define FEATURE_VECTOR_SIZE_JPEG 222	//特征向量大小

class CJpegAlg : public Algorithm  
{
public:
	CJpegAlg(const CString &csAlgName);
	virtual ~CJpegAlg();
public:
	void KeyImageProc(BitmapInfo *pBitmapInfo);
	void KeyImageProc(CString *cs);
	void FoundImageProc(BitmapInfo *pBitmapInfo);
	void FoundImageProc(CString *cs);
	double ImageMatch();
	BOOL AlgInit() { return TRUE; }
	void AlgDestroy() {}
	Algorithm * NewObject() { return new CJpegAlg("Jpeg"); }
private:
	CxImage keyImage;	//关键图的cximage对象
	double  dKeyFeatureVector[FEATURE_VECTOR_SIZE_JPEG];//关键图的特征向量

	CxImage foundImage; //匹配图像的cximage对象
	double	dFoundFeatureVector[FEATURE_VECTOR_SIZE_JPEG]; //匹配图像的特征向量
	
	//Brief 对图像进行特征提取
	//Param image 图像的CxImage对象
	//      pbFeatureVector 特征向量数组
	//      pbImage 图像数据
	void FeatureExtract(BitmapInfo *pBitmapInfo,double *pFeatureVecotr,int iFeatureVectorLen);
};

#endif // !defined(AFX_TESTALG_H__0BC85B38_16D5_46D2_AD74_6C5BA56EA52F__INCLUDED_)
