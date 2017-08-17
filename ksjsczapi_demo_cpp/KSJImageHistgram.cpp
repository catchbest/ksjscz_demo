/*
 * KSJImageHistgram.c
 *
 *  Created on: 2016-10-24
 *      Author: Mike
 */
#include "KSJVisionCode.h"
#include "KSJVisionDef.h"
#include <string.h>

// nAlphaԽ�󣬱���Խ���ԣ�HistgramԽ��
void Y8_ShowHistgram(unsigned char *pData, int nWidth, int nHeight, int nAoiX, int nAoiY, int nAoiW, int nAoiH, int nHistgram[256], int nAlpha)
{
	int  nWidthBytes = MAKEWIDTHBYTES(nWidth, 8);

	float fRatioHInAoi = 0.25;    // ֱ��ͼռnAoiH�ĸ߶ȶ� 0.25 * nAoiH = 1/4

	float fRatioWInAoi = 1.0f;    // ֱ��ͼռAOI����Ŀ��

	int   nHistgramPixelsW = nAoiW * fRatioWInAoi;    // ֱ��ͼ�������ؿ��
	int   nHistgramPixelsH = nAoiH * fRatioHInAoi;    // ֱ��ͼ�������ظ߶�

	// ���ֱ��ͼ������ֵ
	int   nHistgramMax = 0;
	int   i;
	for (i = 0; i < 256; i++)
	{
		if (nHistgram[i] > nHistgramMax)
			nHistgramMax = nHistgram[i];
	}

	// ����ֵ�����صĶ�Ӧ����
	float fRatioHistgramY = (float)nHistgramPixelsH / (float)nHistgramMax;

	int   nHistgramPixelNum[256] = {0};
	// ֵת����ֵ
	for (i = 0; i < 256; i++)
	{
		nHistgramPixelNum[i] = nHistgram[i] * fRatioHistgramY;
	}

	// ����������ű���
	// float fRatioHistgramX = (float)nHistgramPixelsW / 256.0f;

	// OK, ����nHistgramPixelNum[i]
	// pDataAoiColָ����pDataAoiRow��ͬ�еĴ�ֱ��������أ������ش�ֱ�ĸ߶ȴ���ͶӰֵ

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



