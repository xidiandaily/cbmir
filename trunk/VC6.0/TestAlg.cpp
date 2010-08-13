// TestAlg.cpp: implementation of the CTestAlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestAlg.h"
#include "ximage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTestAlg::CTestAlg(const CString &csAlgName)
{
	this->csAlgName=csAlgName;
}

CTestAlg::~CTestAlg()
{
}

void CTestAlg::FeatureExtract(BitmapInfo *pBitmapInfo,double *pFeatureVector,int iFeatureVectorLen)
{
//	memset(pFeatureVector,0,iFeatureVectorLen);
	//memset(pFeatureVecotr,0,iFeatureVectorLen);
	for(int k=0;k<iFeatureVectorLen;k++)
	{
		pFeatureVector[k]=0;
	}

	if(pBitmapInfo->iBitPerPixel==8)
	{
		BYTE *pByte=pBitmapInfo->pImage;
		RGBQUAD *pPalette=pBitmapInfo->pPalette;
		int iWidth=pBitmapInfo->iWidth;
		int iHeight=pBitmapInfo->iHeight;

		int iEffectWidth=((iWidth+3)/4)*4;

		for(int j=0;j<iHeight;j++)
		{
			for(int i=0;i<iEffectWidth;i++)
			{
				if(i<iWidth)
				{				
					pFeatureVector[pPalette[pByte[i]].rgbBlue]++;
				}
				else 
				{
					break;
				}
			}
		}
		
		double dTemp=0;
		for(int i=0;i<iFeatureVectorLen;i++)
		{
			dTemp+=pFeatureVector[i];
		}
		for(i=0;i<iFeatureVectorLen;i++)
		{
			pFeatureVector[i]/=dTemp;
		}
	}	
}

void CTestAlg::KeyImageProc(BitmapInfo *pBitmapInfo)
{
	//对关键图进行特征提取	
	FeatureExtract(pBitmapInfo,dKeyFeatureVector,FEATURE_VECTOR_SIZE);
}

void CTestAlg::KeyImageProc(CString *cs)
{	
	;
}
void CTestAlg::FoundImageProc(BitmapInfo *pBitmapInfo)
{
	//对匹配图像进行特征提取
	FeatureExtract(pBitmapInfo,dFoundFeatureVector,FEATURE_VECTOR_SIZE);
}

void CTestAlg::FoundImageProc(CString *cs)
{
	;
}
double CTestAlg::ImageMatch()
{
	double dTemp = 0.0;
	for(int i = 0; i < WIDTH; i++ )
	{
		double iRes=dKeyFeatureVector[i]-dFoundFeatureVector[i];
		dTemp += (double)iRes*iRes;
	}
	
	dTemp = 1-sqrt(dTemp);
	
	return dTemp;
}