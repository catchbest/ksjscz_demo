/*
 * KSJImageHistgram.h
 *
 *  Created on: 2016-10-24
 *      Author: Mike
 */

#ifndef KSJIMAGEHISTGRAM_H_
#define KSJIMAGEHISTGRAM_H_

int KSJIMAGE_Y8_Histgram(unsigned char *pData, int nWidth, int nHeight, int nAoiX, int nAoiY, int nAoiW, int nAoiH, int nHistgram[256]);
int KSJIMAGE_Rgb_Histgram(unsigned char *pData, int nWidth, int nHeight, int nBitCount, int nAoiX, int nAoiY, int nAoiW, int nAoiH, int nHistgram[3][256]);


#endif /* KSJIMAGEHISTGRAM_H_ */
