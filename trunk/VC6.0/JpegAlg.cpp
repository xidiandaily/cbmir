// CJpegAlg.cpp: implementation of the CJpegAlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JpegAlg.h"
#include "ximage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CJpegAlg::CJpegAlg(const CString &csAlgName)
{
	this->csAlgName=csAlgName;
}

CJpegAlg::~CJpegAlg()
{
}

void CJpegAlg::FeatureExtract(BitmapInfo *pBitmapInfo,double *pFeatureVector,int iFeatureVectorLen)
{
	;
}

void CJpegAlg::KeyImageProc(BitmapInfo *pBitmapInfo)
{
	//对关键图进行特征提取	
	;
}

void CJpegAlg::KeyImageProc(CString *cs)
{
	CString csFilePathName;
	CString csFileName;
	CString csFilePath;
	CString csFileNum;
	CString csFeatName;

	csFilePathName = *cs;
	csFileName = csFilePathName.Right(csFilePathName.GetLength()-csFilePathName.ReverseFind('\\')-1);
	csFilePath = csFilePathName.Left(csFilePathName.ReverseFind('\\'));
	csFileNum = csFileName.Left(csFileName.ReverseFind('.'));
	csFeatName = csFilePath + _T("\\Feature\\") + _T("FT_")+csFileNum+_T(".dat");
	

	CString name;
	FILE *fp;
	int i;
	char cNum[5];
	char *pChar;
	
	//对匹配图像进行特征提取
	name = csFeatName;
	if((fp=fopen(name,"r"))==NULL)
	{
 		memset(dKeyFeatureVector,0,222*sizeof(double));
	}

	pChar = cNum;
	for(i=0;i<222;)
	{		
		*pChar=(char) fgetc(fp);
		if(*pChar == ' ')
		{
			*pChar = 0;
			dKeyFeatureVector[i]=(double)atoi(cNum);
			pChar = cNum;
			i++;
		}
		else
		{
			pChar++;
		}
	}
	fclose(fp);

}

void CJpegAlg::FoundImageProc(BitmapInfo *pBitmapInfo)
{
	;
}

void CJpegAlg::FoundImageProc(CString *cs)
{
	CString name;
	FILE *fp;
	int i;
	char cNum[5];
	char *pChar;
	
	//对匹配图像进行特征提取
	name = *cs;
	if((fp=fopen(name,"r"))==NULL)
	{
 		memset(dFoundFeatureVector,0,222*sizeof(double));
	}

	pChar = cNum;
	for(i=0;i<222;)
	{		
		*pChar=(char) fgetc(fp);
		if(*pChar == ' ')
		{
			*pChar = 0;
			dFoundFeatureVector[i]=atoi(cNum);
			pChar = cNum;
			i++;
		}
		else
		{
			pChar++;
		}
	}

	fclose(fp);
}

double CJpegAlg::ImageMatch()
{
	int i;
	double dTemp = 0.0;
	double KeySum,FoundSum,MinSum,Femmu;
	double ri;

	KeySum=0;
	for(i=0;i<222;i++) KeySum=KeySum+dKeyFeatureVector[i];
	FoundSum=0;
	for(i=0;i<222;i++) FoundSum=FoundSum+dFoundFeatureVector[i];
	MinSum=0;
	for(i=0;i<222;i++)
	{
		ri=dKeyFeatureVector[i]>dFoundFeatureVector[i] ? dFoundFeatureVector[i] : dKeyFeatureVector[i];
		MinSum=MinSum+ri;
	}

	Femmu=KeySum>FoundSum? FoundSum:KeySum;
	dTemp=1-MinSum/Femmu;

	return dTemp;	

}
