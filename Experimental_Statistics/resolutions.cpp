#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N 1024
#define BASIC_ 10000

using namespace std;

typedef pair<int, int> one;

bool cmp(one& a, one& b) {
	return a.second > b.second;
}

typedef unordered_map<int, int> part;
typedef part::iterator iter;

int bmpwidth, bmpheight, step;
part counterBmp;

void readBmp(ofstream& output, char *bmpName) {
	FILE *fp;
	if ((fp = fopen(bmpName, "rb")) == NULL) { //以二进制的方式打开文件  
		cout << "The file " << bmpName << "was not opened" << "\n";
		return;
	}
	if (fseek(fp, sizeof(BITMAPFILEHEADER), 0)) { //跳过BITMAPFILEHEADE  
		cout << "跳转失败" << "\n";
		return;
	}
	BITMAPINFOHEADER infoHead;
	fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);   //从fp中读取BITMAPINFOHEADER信息到infoHead中,同时fp的指针移动  
	bmpwidth = infoHead.biWidth;
	bmpheight = infoHead.biHeight;
	step = bmpwidth * BASIC_ + bmpheight;
	iter stepIter = counterBmp.find(step);
	if (stepIter == counterBmp.end())
		counterBmp[step] = 1;
	else
		stepIter->second++;
	fclose(fp);   //关闭文件  
	output << bmpName << ": " << bmpwidth << " * " << bmpheight << "\n";
}

void pristine() {
	char root[] = "C:\\Users\\codinglee\\Desktop\\Semester\\Databases\\pristine_images_waterloo\\";
	char index[] = "zzz.txt";
	char rootFile[N];
	strcpy(rootFile, root);
	strcat(rootFile, index);
	ifstream input(rootFile);
	ofstream output("pristine_images_waterloo.txt");
	for (;;) {
		char file[N], pic[N];
		strcpy(file, root);
		input >> pic;
		if (strlen(pic)) {
			//cout << pic << "\n";
			strcat(file, pic);
			readBmp(output, file);
		}
		else
			break;
	}
	vector<one> total;
	iter stepIter = counterBmp.begin();
	for (; stepIter != counterBmp.end(); stepIter++)
		total.push_back(one(stepIter->first, stepIter->second));
	counterBmp.clear();
	sort(total.begin(), total.end(), cmp);
	output << "\n\n\n\n";
	int i, n = total.size();
	for (i = 0; i < n; i++) {
		step = total[i].first;
		output << step / BASIC_ << " * " << step%BASIC_ << ": " << total[i].second << "\n";
	}
	input.close();
	output.close();
}

#pragma pack(1)  
#define M_SOF0  0xc0  
#define M_DHT   0xc4  
#define M_EOI   0xd9  
#define M_SOS   0xda  
#define M_DQT   0xdb  
#define M_DRI   0xdd  
#define M_APP0  0xe0  

static int Zig_Zag[8][8] = { { 0, 1, 5, 6, 14, 15, 27, 28 },
{ 2, 4, 7, 13, 16, 26, 29, 42 },
{ 3, 8, 12, 17, 25, 30, 41, 43 },
{ 9, 11, 18, 24, 37, 40, 44, 53 },
{ 10, 19, 23, 32, 39, 45, 52, 54 },
{ 20, 22, 33, 38, 46, 51, 55, 60 },
{ 21, 34, 37, 47, 50, 56, 59, 61 },
{ 35, 36, 48, 49, 57, 58, 62, 63 }
};

#define W1 2841 /* 2048*sqrt(2)*cos(1*pi/16) */  
#define W2 2676 /* 2048*sqrt(2)*cos(2*pi/16) */  
#define W3 2408 /* 2048*sqrt(2)*cos(3*pi/16) */  
#define W5 1609 /* 2048*sqrt(2)*cos(5*pi/16) */  
#define W6 1108 /* 2048*sqrt(2)*cos(6*pi/16) */  
#define W7 565  /* 2048*sqrt(2)*cos(7*pi/16) */  

//*************************************************************************************  
typedef char CHAR;
typedef short SHORT;
typedef long LONG;

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;

typedef int HFILE;
typedef CHAR *LPSTR, *PSTR;

#define FALSE 0  
#define TRUE 1  

/* constants for the biCompression field */
#define BI_RGB        0L  
#define BI_RLE8       1L  
#define BI_RLE4       2L  
#define BI_BITFIELDS  3L  

//---yk--- add  
//macro definition  
#define WIDTHBYTES(i)    ((i+31)/32*4)//??????????  
#define PI 3.1415926535  
//define return value of function  
#define FUNC_OK 0  
#define FUNC_MEMORY_ERROR 1  
#define FUNC_FILE_ERROR 2  
#define FUNC_FORMAT_ERROR 3  

//global variable declaration  
BITMAPFILEHEADER   bf;
BITMAPINFOHEADER   bi;
//HPALETTE           hPalette=NULL;  
//HBITMAP            hBitmap=NULL;  
char *            hImgData = NULL;
DWORD              NumColors;
DWORD              LineBytes;
DWORD              ImgWidth = 0, ImgHeight = 0;
char*             lpPtr;
//////////////////////////////////////////////////  
//variables used in jpeg function  
short   SampRate_Y_H, SampRate_Y_V;
short   SampRate_U_H, SampRate_U_V;
short   SampRate_V_H, SampRate_V_V;
short   H_YtoU, V_YtoU, H_YtoV, V_YtoV;
short   Y_in_MCU, U_in_MCU, V_in_MCU;
unsigned char   *lpJpegBuf;
unsigned char   *lp;
short   qt_table[3][64];
short   comp_num;
BYTE   comp_index[3];
BYTE      YDcIndex, YAcIndex, UVDcIndex, UVAcIndex;
BYTE   HufTabIndex;
short      *YQtTable, *UQtTable, *VQtTable;
BYTE   And[9] = { 0, 1, 3, 7, 0xf, 0x1f, 0x3f, 0x7f, 0xff };
short      code_pos_table[4][16], code_len_table[4][16];
unsigned short code_value_table[4][256];
unsigned short huf_max_value[4][16], huf_min_value[4][16];
short   BitPos, CurByte;
short   rrun, vvalue;
short   MCUBuffer[10 * 64];
int    QtZzMCUBuffer[10 * 64];
short   BlockBuffer[64];
short   ycoef, ucoef, vcoef;
BOOL   IntervalFlag;
short   interval = 0;
int    Y[4 * 64], U[4 * 64], V[4 * 64];
DWORD      sizei, sizej;
short    restart;
static  long iclip[1024];
static  long *iclp;


void showerror(int funcret) {
	switch (funcret) {
	case FUNC_MEMORY_ERROR:
		printf("Error alloc memory\n!");
		break;
	case FUNC_FILE_ERROR:
		printf("File not found!\n");
		break;
	case FUNC_FORMAT_ERROR:
		printf("File format error!\n");
		break;
	}
}

int InitTag() {
	BOOL finish = FALSE;
	BYTE id;
	short  llength;
	short  i, j, k;
	short  huftab1, huftab2;
	short  huftabindex;
	BYTE hf_table_index;
	BYTE qt_table_index;
	BYTE comnum;

	unsigned char  *lptemp;
	short  ccount;

	lp = lpJpegBuf + 2;

	while (!finish) {
		id = *(lp + 1);
		lp += 2;
		switch (id) {
		case M_APP0:
			llength = MAKEWORD(*(lp + 1), *lp);
			lp += llength;
			break;
		case M_DQT:
			llength = MAKEWORD(*(lp + 1), *lp);
			qt_table_index = (*(lp + 2)) & 0x0f;
			lptemp = lp + 3;
			if (llength<80) {
				for (i = 0; i<64; i++)
					qt_table[qt_table_index][i] = (short)*(lptemp++);
			}
			else {
				for (i = 0; i<64; i++)
					qt_table[qt_table_index][i] = (short)*(lptemp++);
				qt_table_index = (*(lptemp++)) & 0x0f;
				for (i = 0; i<64; i++)
					qt_table[qt_table_index][i] = (short)*(lptemp++);
			}
			lp += llength;
			break;
		case M_SOF0:
			llength = MAKEWORD(*(lp + 1), *lp);
			ImgHeight = MAKEWORD(*(lp + 4), *(lp + 3));
			ImgWidth = MAKEWORD(*(lp + 6), *(lp + 5));
			comp_num = *(lp + 7);
			if ((comp_num != 1) && (comp_num != 3))
				return FUNC_FORMAT_ERROR;
			if (comp_num == 3) {
				comp_index[0] = *(lp + 8);
				SampRate_Y_H = (*(lp + 9)) >> 4;
				SampRate_Y_V = (*(lp + 9)) & 0x0f;
				YQtTable = (short *)qt_table[*(lp + 10)];

				comp_index[1] = *(lp + 11);
				SampRate_U_H = (*(lp + 12)) >> 4;
				SampRate_U_V = (*(lp + 12)) & 0x0f;
				UQtTable = (short *)qt_table[*(lp + 13)];

				comp_index[2] = *(lp + 14);
				SampRate_V_H = (*(lp + 15)) >> 4;
				SampRate_V_V = (*(lp + 15)) & 0x0f;
				VQtTable = (short *)qt_table[*(lp + 16)];
			}
			else {
				comp_index[0] = *(lp + 8);
				SampRate_Y_H = (*(lp + 9)) >> 4;
				SampRate_Y_V = (*(lp + 9)) & 0x0f;
				YQtTable = (short *)qt_table[*(lp + 10)];

				comp_index[1] = *(lp + 8);
				SampRate_U_H = 1;
				SampRate_U_V = 1;
				UQtTable = (short *)qt_table[*(lp + 10)];

				comp_index[2] = *(lp + 8);
				SampRate_V_H = 1;
				SampRate_V_V = 1;
				VQtTable = (short *)qt_table[*(lp + 10)];
			}
			lp += llength;
			break;
		case M_DHT:
			llength = MAKEWORD(*(lp + 1), *lp);
			if (llength<0xd0) {
				huftab1 = (short)(*(lp + 2)) >> 4;     //huftab1=0,1  
				huftab2 = (short)(*(lp + 2)) & 0x0f;   //huftab2=0,1  
				huftabindex = huftab1 * 2 + huftab2;
				lptemp = lp + 3;
				for (i = 0; i<16; i++)
					code_len_table[huftabindex][i] = (short)(*(lptemp++));
				j = 0;
				for (i = 0; i<16; i++)
					if (code_len_table[huftabindex][i] != 0) {
						k = 0;
						while (k<code_len_table[huftabindex][i]) {
							code_value_table[huftabindex][k + j] = (short)(*(lptemp++));
							k++;
						}
						j += k;
					}
				i = 0;
				while (code_len_table[huftabindex][i] == 0)
					i++;
				for (j = 0; j<i; j++) {
					huf_min_value[huftabindex][j] = 0;
					huf_max_value[huftabindex][j] = 0;
				}
				huf_min_value[huftabindex][i] = 0;
				huf_max_value[huftabindex][i] = code_len_table[huftabindex][i] - 1;
				for (j = i + 1; j<16; j++) {
					huf_min_value[huftabindex][j] = (huf_max_value[huftabindex][j - 1] + 1) << 1;
					huf_max_value[huftabindex][j] = huf_min_value[huftabindex][j] + code_len_table[huftabindex][j] - 1;
				}
				code_pos_table[huftabindex][0] = 0;
				for (j = 1; j<16; j++)
					code_pos_table[huftabindex][j] = code_len_table[huftabindex][j - 1] + code_pos_table[huftabindex][j - 1];
				lp += llength;
			}  //if  
			else {
				hf_table_index = *(lp + 2);
				lp += 2;
				while (hf_table_index != 0xff) {
					huftab1 = (short)hf_table_index >> 4;     //huftab1=0,1  
					huftab2 = (short)hf_table_index & 0x0f;   //huftab2=0,1  
					huftabindex = huftab1 * 2 + huftab2;
					lptemp = lp + 1;
					ccount = 0;
					for (i = 0; i<16; i++) {
						code_len_table[huftabindex][i] = (short)(*(lptemp++));
						ccount += code_len_table[huftabindex][i];
					}
					ccount += 17;
					j = 0;
					for (i = 0; i<16; i++)
						if (code_len_table[huftabindex][i] != 0) {
							k = 0;
							while (k<code_len_table[huftabindex][i])
							{
								code_value_table[huftabindex][k + j] = (short)(*(lptemp++));
								k++;
							}
							j += k;
						}
					i = 0;
					while (code_len_table[huftabindex][i] == 0)
						i++;
					for (j = 0; j<i; j++) {
						huf_min_value[huftabindex][j] = 0;
						huf_max_value[huftabindex][j] = 0;
					}
					huf_min_value[huftabindex][i] = 0;
					huf_max_value[huftabindex][i] = code_len_table[huftabindex][i] - 1;
					for (j = i + 1; j<16; j++) {
						huf_min_value[huftabindex][j] = (huf_max_value[huftabindex][j - 1] + 1) << 1;
						huf_max_value[huftabindex][j] = huf_min_value[huftabindex][j] + code_len_table[huftabindex][j] - 1;
					}
					code_pos_table[huftabindex][0] = 0;
					for (j = 1; j<16; j++)
						code_pos_table[huftabindex][j] = code_len_table[huftabindex][j - 1] + code_pos_table[huftabindex][j - 1];
					lp += ccount;
					hf_table_index = *lp;
				}  //while  
			}  //else  
			break;
		case M_DRI:
			llength = MAKEWORD(*(lp + 1), *lp);
			restart = MAKEWORD(*(lp + 3), *(lp + 2));
			lp += llength;
			break;
		case M_SOS:
			llength = MAKEWORD(*(lp + 1), *lp);
			comnum = *(lp + 2);
			if (comnum != comp_num)
				return FUNC_FORMAT_ERROR;
			lptemp = lp + 3;
			for (i = 0; i<comp_num; i++) {
				if (*lptemp == comp_index[0]) {
					YDcIndex = (*(lptemp + 1)) >> 4;   //Y  
					YAcIndex = ((*(lptemp + 1)) & 0x0f) + 2;
				}
				else {
					UVDcIndex = (*(lptemp + 1)) >> 4;   //U,V  
					UVAcIndex = ((*(lptemp + 1)) & 0x0f) + 2;
				}
				lptemp += 2;
			}
			lp += llength;
			finish = TRUE;
			break;
		case M_EOI:
			return FUNC_FORMAT_ERROR;
			break;
		default:
			if ((id & 0xf0) != 0xd0) {
				llength = MAKEWORD(*(lp + 1), *lp);
				lp += llength;
			}
			else lp += 2;
			break;
		}  //switch  
	} //while  
	return FUNC_OK;
}

void InitTable() {
	short i, j;
	sizei = sizej = 0;
	ImgWidth = ImgHeight = 0;
	rrun = vvalue = 0;
	BitPos = 0;
	CurByte = 0;
	IntervalFlag = FALSE;
	restart = 0;
	for (i = 0; i<3; i++)
		for (j = 0; j<64; j++)
			qt_table[i][j] = 0;
	comp_num = 0;
	HufTabIndex = 0;
	for (i = 0; i<3; i++)
		comp_index[i] = 0;
	for (i = 0; i<4; i++)
		for (j = 0; j<16; j++) {
			code_len_table[i][j] = 0;
			code_pos_table[i][j] = 0;
			huf_max_value[i][j] = 0;
			huf_min_value[i][j] = 0;
		}
	for (i = 0; i<4; i++)
		for (j = 0; j<256; j++)
			code_value_table[i][j] = 0;

	for (i = 0; i<10 * 64; i++) {
		MCUBuffer[i] = 0;
		QtZzMCUBuffer[i] = 0;
	}
	for (i = 0; i<64; i++) {
		Y[i] = 0;
		U[i] = 0;
		V[i] = 0;
		BlockBuffer[i] = 0;
	}
	ycoef = ucoef = vcoef = 0;
}

bool insertPart(part& ct) {
	iter stepIter = ct.find(step);
	if (stepIter == ct.end()) {
		ct[step] = 1;
		return false;
	}
	stepIter->second++;
	return true;
}

part counterJpeg;
////////////////////////////////////////////////////////////////  
void LoadJpegFile(int& counter, part& store, ofstream& output, char *JpegFileName) {
	FILE*		hfjpg;
	DWORD		JpegBufSize;
	void *      hJpegBuf;
	int			funcret;

	fopen_s(&hfjpg, JpegFileName, "rb");

	//get jpg file length  
	fseek(hfjpg, 0L, SEEK_END);
	JpegBufSize = ftell(hfjpg);
	//rewind to the beginning of the file  
	fseek(hfjpg, 0L, SEEK_SET);

	if ((hJpegBuf = malloc(JpegBufSize)) == NULL) {
		fclose(hfjpg);
		showerror(FUNC_MEMORY_ERROR);
		return;
	}
	lpJpegBuf = (unsigned char  *)hJpegBuf;
	fread((unsigned char  *)hJpegBuf, sizeof(char), JpegBufSize, hfjpg);
	fclose(hfjpg);

	InitTable();

	if ((funcret = InitTag()) != FUNC_OK) {
		free(hJpegBuf);
		showerror(funcret);
		return;
	}
	memset((char *)&bf, 0, sizeof(BITMAPFILEHEADER));
	memset((char *)&bi, 0, sizeof(BITMAPINFOHEADER));

	bi.biSize = (DWORD)sizeof(BITMAPINFOHEADER);
	bi.biWidth = (LONG)(ImgWidth);
	bi.biHeight = (LONG)(ImgHeight);
	step = bi.biWidth * BASIC_ + bi.biHeight;
	insertPart(counterJpeg);
	if (!insertPart(store))
		counter++;
	output << JpegFileName << ": " << bi.biWidth << " * " << bi.biHeight << "\n";
	free(hJpegBuf);
	free(hImgData);
}

void getEach(part& ct, ofstream& output) {
	vector<one> total;
	iter stepIter = ct.begin();
	for (; stepIter != ct.end(); stepIter++)
		total.push_back(one(stepIter->first, stepIter->second));
	ct.clear();
	sort(total.begin(), total.end(), cmp);
	output << "\n";
	int i, n = total.size();
	for (i = 0; i < n; i++) {
		step = total[i].first;
		output << step / BASIC_ << " * " << step%BASIC_ << ": " << total[i].second << "\n";
	}
}

void labelme() {
	char root[] = "C:\\Users\\codinglee\\Desktop\\Semester\\Databases\\LabelMe\\";
	char index[] = "zzz.txt";
	char gap[] = "\\";
	char rootFile[N];
	strcpy(rootFile, root);
	strcat(rootFile, index);
	ifstream inputR(rootFile);
	ofstream output("labelme.txt");
	for (;;) {
		char subFile[N], sub[N];
		inputR >> sub;
		if (strlen(sub)) {
			//cout << sub << "\n";
			strcpy(subFile, root);
			strcat(subFile, sub);
			strcat(subFile, gap);
			//cout << subFile << "\n";
			char subIndex[N];
			strcpy(subIndex, subFile);
			strcat(subIndex, gap);
			strcat(subIndex, index);
			//cout << subIndex << "\n";
			int counter = 0;
			ifstream input(subIndex);
			output << subIndex << "\n";
			part store;
			for (;;) {
				char file[N], pic[N];
				strcpy(file, subFile);
				input >> pic;
				if (strlen(pic)) {
					//cout << pic << "\n";
					strcat(file, pic);
					LoadJpegFile(counter, store, output, file);
				}
				else
					break;
			}
			getEach(store, output);
			if (counter > 1)
				cout << subFile << ": " << counter << "\n";
			output << "The total type is: " << counter << "\n\n";
			input.close();
		}
		else
			break;
	}
	getEach(counterJpeg, output);
	inputR.close();
	output.close();
}

int main() {
	pristine();
	labelme();
	return 0;
}