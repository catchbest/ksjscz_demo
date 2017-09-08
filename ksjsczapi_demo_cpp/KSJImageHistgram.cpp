/*
 * KSJImageHistgram.c
 *
 *  Created on: 2016-10-24
 *      Author: Mike
 */
#include "KSJVisionCode.h"
#include "KSJVisionDef.h"
#include <string.h>

// nAlpha越大，背景越明显，Histgram越淡
void Y8_ShowHistgram(unsigned char *pData, int nWidth, int nHeight, int nAoiX, int nAoiY, int nAoiW, int nAoiH, int nHistgram[256], int nAlpha)
{
	int  nWidthBytes = MAKEWIDTHBYTES(nWidth, 8);

	float fRatioHInAoi = 0.25;    // 直方图占nAoiH的高度度 0.25 * nAoiH = 1/4

	float fRatioWInAoi = 1.0f;    // 直方图占AOI区域的宽度

	int   nHistgramPixelsW = nAoiW * fRatioWInAoi;    // 直方图横向像素宽度
	int   nHistgramPixelsH = nAoiH * fRatioHInAoi;    // 直方图纵向像素高度

	// 求出直方图中最大的值
	int   nHistgramMax = 0;
	int   i;
	for (i = 0; i < 256; i++)
	{
		if (nHistgram[i] > nHistgramMax)
			nHistgramMax = nHistgram[i];
	}

	// 计算值和像素的对应比例
	float fRatioHistgramY = (float)nHistgramPixelsH / (float)nHistgramMax;

	int   nHistgramPixelNum[256] = {0};
	// 值转像素值
	for (i = 0; i < 256; i++)
	{
		nHistgramPixelNum[i] = nHistgram[i] * fRatioHistgramY;
	}

	// 计算横轴缩放比例
	// float fRatioHistgramX = (float)nHistgramPixelsW / 256.0f;

	// OK, 画出nHistgramPixelNum[i]
	// pDataAoiCol指向与pDataAoiRow相同列的垂直方向的像素，此像素垂直的高度代表投影值

#ifdef MEM_FLIP
	unsigned char *pDataAoiCol = pData + nAoiY * nWidthBytes + nAoiX;
	unsigned char *pDataAoiRow = pDataAoiCol;

	int x, y;

	int Y1 = 0;
	for (x = 0; x < 256; x++)
	{
		pDataAoiRow = pDataAoiCol;
		for (y = 0; y < nHistgramPixelNum[x]; y++)
		{
			*(pDataAoiRow) = (Y1 * (100 - nAlpha) + *(pDataAoiRow)* nAlpha) / 100;
			pDataAoiRow += nWidthBytes;

		}

		pDataAoiCol++;
	}
#else
	unsigned char *pDataAoiCol = pData + (nAoiY + nAoiH) * nWidthBytes + nAoiX;
	unsigned char *pDataAoiRow = pDataAoiCol;

	int x, y;

	int Y1 = 0;
	for (x = 0; x < 256; x++)
	{
		pDataAoiRow = pDataAoiCol;
		for (y = 0; y < nHistgramPixelNum[x]; y++)
		{
			*(pDataAoiRow) = (Y1 * (100 - nAlpha) + *(pDataAoiRow)* nAlpha) / 100;
			pDataAoiRow -= nWidthBytes;

		}

		pDataAoiCol++;
	}

#endif


}

int KSJIMAGE_Y8_Histgram(unsigned char *pData, int nWidth, int nHeight, int nAoiX, int nAoiY, int nAoiW, int nAoiH, int nHistgram[256])
{
	// Map2MemAoi(nWidth, nHeight, nAoiX, nAoiY, nAoiW, nAoiH);

	memset(nHistgram, 0, 256 * sizeof(int));

	int  nWidthBytes = MAKEWIDTHBYTES(nWidth, 8);

	unsigned char *pDataRow = pData + nAoiY * nWidthBytes + nAoiX;

	int x, y;
	for ( y = 0; y < nAoiH; y++)
	{
		for ( x = 0; x < nAoiW; x++)
		{
			nHistgram[*(pDataRow + x)]++;
		}

		pDataRow += nWidthBytes;
	}

	Y8_ShowHistgram( pData, nWidth, nHeight, nAoiX, nAoiY, nAoiW, nAoiH, nHistgram, 50);

	return KSJVISION_SUCCESS;
}

void Rgb_ShowHistgram(unsigned char *pData, int nWidth, int nHeight, int nBitCount, int nAoiX, int nAoiY, int nAoiW, int nAoiH, int nHistgram[3][256])
{

}

int KSJIMAGE_Rgb_Histgram(unsigned char *pData, int nWidth, int nHeight, int nBitCount, int nAoiX, int nAoiY, int nAoiW, int nAoiH, int nHistgram[3][256])
{
	// Map2MemAoi(nWidth, nHeight, nAoiX, nAoiY, nAoiW, nAoiH);

	memset(nHistgram, 0, 3 * 256 * sizeof(int));

	int  nWidthBytes = MAKEWIDTHBYTES(nWidth, nBitCount);
	int  nPixelBytes = (nBitCount >> 3);

	unsigned char *pDataRow = pData + nAoiY * nWidthBytes + nAoiX * nPixelBytes;
	unsigned char *pDataPix;

	int x, y, i;
	for (y = 0; y < nAoiH; y++)
	{
		pDataPix = pDataRow;

		for (x = 0; x < nAoiW; x++)
		{
			for (i = 0; i < nPixelBytes; i++)
			{
				nHistgram[i][*(pDataPix + 2 - i)]++;
			}
		}

		pDataRow += nWidthBytes;
	}

	return KSJVISION_SUCCESS;

}



