/*
 * qrencode - QR Code encoder
 *
 * Micro QR Code specification in convenient format. 
 * Copyright (C) 2006-2011 Kentaro Fukuchi <kentaro@fukuchi.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __QRENCODE_H
#define __QRENCODE_H

#ifndef FALSE			/* in case these macros already exist */
#define FALSE	0		/* values of boolean */
#endif
#ifndef TRUE
#define TRUE	1
#endif

//typedef enum {FALSE = 0, TRUE = !FALSE} bool;
#define qr_min(a,b)	(((a) < (b)) ? (a) : (b))

#define QR_LEVEL_L	0	
#define QR_LEVEL_M	1	
#define QR_LEVEL_Q	2	
#define QR_LEVEL_H	3	

#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3
#define QR_MODE_CHINESE		4

//Number of bits per length field
//Numeric		10			12			14
//Alphanumeric	9			11			13
//Byte			8			16			16
//Kanji			8			10			12 
//Chinese		

#define QR_VRESION_S	0 
#define QR_VRESION_M	1 
#define QR_VRESION_L	2 

#define QR_MARGIN	4
#define	QR_VER1_SIZE	21

#define MAX_ALLCODEWORD		400 
#define MAX_DATACODEWORD	 400 
#define MAX_CODEBLOCK		153	
#define MAX_MODULESIZE		21  // 21:Version=1
								// 25:Version=2
								// 29:Version=3
								// 33:Version=4
								// 37:Version=5
								// 41:Version=6
							 	// 45:Version=7
							 	// 49:Version=8
								// 53:
//#define	MAX_MODULESIZE	177 //

extern int m_nSymbleSize;
extern unsigned char m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE];
/////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	unsigned short ncRSBlock;		
	unsigned short ncAllCodeWord;	
	unsigned short ncDataCodeWord;	
}RS_BLOCKINFO;
typedef struct 
{
	unsigned short nVersionNo;			//ver 1~40
	unsigned short ncAllCodeWord; 		

	unsigned short ncDataCodeWord[4];	
	unsigned short ncAlignPoint;		
	unsigned short nAlignPoint[6];		
	//(0=L,1=M,2=Q,3=H)
	RS_BLOCKINFO RS_BlockInfo1[4];	
	RS_BLOCKINFO RS_BlockInfo2[4];	
}QR_VERSIONINFO;

#if defined(__cplusplus)
extern "C" {
#endif

bool EncodeData(char *lpsSource);

int GetEncodeVersion(int nVersion, char *lpsSource, int ncLength);
//bool EncodeSourceData(char *lpsSource, int ncLength, int nVerGroup);
int EncodeSourceData(char *lpsSource, int ncLength, int nVerGroup);

int GetBitLength(unsigned char nMode, int ncData, int nVerGroup);

int SetBitStream(int nIndex, unsigned short wData, int ncData);

bool IsNumeralData(unsigned char c);
bool IsAlphabetData(unsigned char c);
bool IsKanjiData(unsigned char c1, unsigned char c2);
bool IsChineseData(unsigned char c1, unsigned char c2);
	
unsigned char AlphabetToBinaly(unsigned char c);
unsigned short KanjiToBinaly(unsigned short wc);
unsigned short ChineseToBinaly(unsigned short wc);
void GetRSCodeWord(unsigned char *lpbyRSWork, int ncDataCodeWord, int ncRSCodeWord);

void FormatModule(void);

void SetFunctionModule(void);
void SetFinderPattern(int x, int y);
void SetAlignmentPattern(int x, int y);
void SetVersionPattern(void);
void SetCodeWordPattern(void);
void SetMaskingPattern(int nPatternNo);
void SetFormatInfoPattern(int nPatternNo);
int CountPenalty(void);
void Print_2DCode(void);
#if defined(__cplusplus)
}
#endif

#endif
