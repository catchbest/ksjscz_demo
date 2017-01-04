/*
 * KSJImageThreshold.c
 *
 *  Created on: 2016-10-24
 *      Author: Mike
 */
#include "KSJVisionCode.h"
#include "KSJVisionDef.h"
#include "KSJImageThreshold.h"

// 图像二值化处理
int KSJIMAGE_Y8_ThresholdSingle(unsigned char *pData, int nWidth, int nHeight, int nThreshold, int nMode)
{
	int  nWidthBytes = MAKEWIDTHBYTES(nWidth, 8);

	unsigned char *pDataRow = pData;

	unsigned char *pDataPixel;

	int x, y;
	for ( y = 0; y < nHeight; y++)
	{
		for ( x = 0; x < nWidth; x++)
		{
			pDataPixel = pDataRow + x;

			if (*pDataPixel >= nThreshold)
				*pDataPixel = ( nMode == 0 ? PIXEL_VALUE_HIG : PIXEL_VALUE_LOW );
			else
				*pDataPixel = ( nMode == 0 ? PIXEL_VALUE_LOW : PIXEL_VALUE_HIG );
		}

		pDataRow += nWidthBytes;
	}

	return KSJVISION_SUCCESS;
}

int KSJIMAGE_Y8_ThresholdSingle_AOI(unsigned char *pData, int nWidth, int nHeight, int nThreshold, int nMode, int nAoiX, int nAoiY, int nAoiW, int nAoiH)
{
	// Map2MemAoi(nWidth, nHeight, nAoiX, nAoiY, nAoiW, nAoiH);

	int  nWidthBytes = MAKEWIDTHBYTES(nWidth, 8);
	unsigned char *pDataAoiRow = pData + nWidthBytes * nAoiY + nAoiX;
	unsigned char *pDataAoiPix;

	int x, y;
	for ( y = 0; y < nAoiH; y++)
	{
		for ( x = 0; x < nAoiW; x++)
		{
			pDataAoiPix = pDataAoiRow + x;

			if (*pDataAoiPix >= nThreshold)
				*pDataAoiPix = (nMode == 0 ? PIXEL_VALUE_HIG : PIXEL_VALUE_LOW);
			else
				*pDataAoiPix = (nMode == 0 ? PIXEL_VALUE_LOW : PIXEL_VALUE_HIG);
		}

		pDataAoiRow += nWidthBytes;
	}

	return KSJVISION_SUCCESS;
}


int KSJIMAGE_Y8_ThresholdDouble(unsigned char *pData, int nWidth, int nHeight, int nThresholdLow, int nThresholdHig, int nMode)
{
	unsigned char *pDataRow = pData;
	int  nWidthBytes = MAKEWIDTHBYTES(nWidth, 8);

	unsigned char *pDataPixel;

	int x, y;
	for ( y = 0; y < nHeight; y++)
	{
		for ( x = 0; x < nWidth; x++)
		{
			pDataPixel = pDataRow + x;

			if (*pDataPixel >= nThresholdLow && *pDataPixel <= nThresholdHig)
				*pDataPixel = (nMode == 0 ? PIXEL_VALUE_HIG : PIXEL_VALUE_LOW);
			else
				*pDataPixel = (nMode == 0 ? PIXEL_VALUE_LOW : PIXEL_VALUE_HIG);
		}

		pDataRow += nWidthBytes;
	}

	return KSJVISION_SUCCESS;
}

int KSJIMAGE_Y8_ThresholdDouble_AOI(unsigned char *pData, int nWidth, int nHeight, int nThresholdLow, int nThresholdHig, int nMode, int nAoiX, int nAoiY, int nAoiW, int nAoiH)
{
	// Map2MemAoi(nWidth, nHeight, nAoiX, nAoiY, nAoiW, nAoiH);

	int  nWidthBytes = MAKEWIDTHBYTES(nWidth, 8);
	unsigned char *pDataAoiRow = pData + nWidthBytes * nAoiY + nAoiX;
	unsigned char *pDataAoiPix;

	int x, y;
	for ( y = 0; y < nAoiH; y++)
	{
		for ( x = 0; x < nAoiW; x++)
		{
			pDataAoiPix = pDataAoiRow + x;

			if (*pDataAoiPix >= nThresholdLow && *pDataAoiPix <= nThresholdHig)
				*pDataAoiPix = (nMode == 0 ? PIXEL_VALUE_HIG : PIXEL_VALUE_LOW);
			else
				*pDataAoiPix = (nMode == 0 ? PIXEL_VALUE_LOW : PIXEL_VALUE_HIG);
		}

		pDataAoiRow += nWidthBytes;
	}

	return KSJVISION_SUCCESS;
}



