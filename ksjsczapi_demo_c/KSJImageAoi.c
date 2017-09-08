/*
 * KSJImageAoi.c
 *
 *  Created on: 2016-10-24
 *      Author: Mike
 */

#include "KSJVisionCode.h"
#include "KSJVisionDef.h"
#include <string.h>

int KSJIMAGE_ShowAoi(unsigned char *pData, int nWidth, int nHeight, int nBitCount, int nAoiX, int nAoiY, int nAoiW, int nAoiH)
{
	int nWidthBytes = MAKEWIDTHBYTES(nWidth, nBitCount);
	int nPixelBytes = (nBitCount >> 3);

	// Map2MemAoi(nWidth, nHeight, nAoiX, nAoiY, nAoiW, nAoiH);

	unsigned char *pDataPixelHeader = pData + nWidthBytes * nAoiY + nPixelBytes * nAoiX;
	unsigned char *pDataPixelTailer = pData + nWidthBytes * nAoiY + nPixelBytes * (nAoiX + nAoiW - 1);

	int nAoiWidthBytes = nAoiW * nPixelBytes;

	memset(pDataPixelHeader, PIXEL_VALUE_HIG, nAoiWidthBytes);
	pDataPixelHeader += nWidthBytes;

	int x, y;
	int i;
	for (y = 1; y < nAoiH - 1; y++)
	{
		i = nPixelBytes;
		while (i--)
		{
			*(pDataPixelHeader + i) = PIXEL_VALUE_HIG;
			*(pDataPixelTailer + i) = PIXEL_VALUE_HIG;
		}

		pDataPixelHeader += nWidthBytes;
		pDataPixelTailer += nWidthBytes;
	}

	memset(pDataPixelHeader, PIXEL_VALUE_HIG, nAoiWidthBytes);

	return KSJVISION_SUCCESS;
}

