#include <iostream>
#include <string>
#include <windows.h>	
using namespace std;

char g_CurImg_r_filePath[_MAX_PATH] = "r.bmp";
char g_CurImg_g_filePath[_MAX_PATH] = "g.bmp";
char g_CurImg_b_filePath[_MAX_PATH] = "b.bmp";

void WriteBMP24(char *fileName, UINT8 *pCurImg_r, UINT8 *pCurImg_g, UINT8 *pCurImg_b, INT32 iWidth, INT32 iHeight){
	FILE *fpDisplayImg = fopen(fileName, "wb+");
	if (fpDisplayImg == NULL){
		printf("File : %s Not Found \n", fileName);
		return;
	}
	UINT8 *pDisplayImg = new UINT8[iWidth*iHeight * 3 + 0x36];//包含文件头的长度
	memset(pDisplayImg, 0, sizeof(UINT8)*iWidth*iHeight * 3 + 0x36);//内存一定要清零初始化
	//BMP文件头
	pDisplayImg[0] = 0x42;
	pDisplayImg[1] = 0x4D;
	char FourByte[10] = { 0 };
	sprintf(FourByte, "%08X", iWidth*iHeight * 3 + 0x36);
	//printf("%c %s %d",FourByte[0],FourByte,strlen(FourByte));
	pDisplayImg[2] = (FourByte[6] > 0x39 ? (FourByte[6] - 0x37) * 16 : (FourByte[6] - 0x30) * 16) + (FourByte[7] > 0x39 ? (FourByte[7] - 0x37) : (FourByte[7] - 0x30));
	pDisplayImg[3] = (FourByte[4] > 0x39 ? (FourByte[4] - 0x37) * 16 : (FourByte[4] - 0x30) * 16) + (FourByte[5] > 0x39 ? (FourByte[5] - 0x37) : (FourByte[5] - 0x30));
	pDisplayImg[4] = (FourByte[2] > 0x39 ? (FourByte[2] - 0x37) * 16 : (FourByte[2] - 0x30) * 16) + (FourByte[3] > 0x39 ? (FourByte[3] - 0x37) : (FourByte[3] - 0x30));
	pDisplayImg[5] = (FourByte[0] > 0x39 ? (FourByte[0] - 0x37) * 16 : (FourByte[0] - 0x30) * 16) + (FourByte[1] > 0x39 ? (FourByte[1] - 0x37) : (FourByte[1] - 0x30));
	pDisplayImg[10] = 0x36;
	pDisplayImg[14] = 0x28;
	sprintf(FourByte, "%08X", iWidth);
	pDisplayImg[18] = (FourByte[6] > 0x39 ? (FourByte[6] - 0x37) * 16 : (FourByte[6] - 0x30) * 16) + (FourByte[7] > 0x39 ? (FourByte[7] - 0x37) : (FourByte[7] - 0x30));
	pDisplayImg[19] = (FourByte[4] > 0x39 ? (FourByte[4] - 0x37) * 16 : (FourByte[4] - 0x30) * 16) + (FourByte[5] > 0x39 ? (FourByte[5] - 0x37) : (FourByte[5] - 0x30));
	sprintf(FourByte, "%08X", iHeight);
	pDisplayImg[22] = (FourByte[6] > 0x39 ? (FourByte[6] - 0x37) * 16 : (FourByte[6] - 0x30) * 16) /*+ (FourByte[7] > 0x39 ? (FourByte[7] - 0x37) : (FourByte[7] - 0x30))*/;
	//printf("pDisplayImg %d :%d %d %d",(FourByte[6] - 0x30) * 16,(FourByte[6] - 0x37) * 16,FourByte[6],pDisplayImg[22]);
	pDisplayImg[23] = (FourByte[4] > 0x39 ? (FourByte[4] - 0x37) * 16 : (FourByte[4] - 0x30) * 16) + (FourByte[5] > 0x39 ? (FourByte[5] - 0x37) : (FourByte[5] - 0x30));
	pDisplayImg[26] = 0x01;
	pDisplayImg[28] = 0x18;
	sprintf(FourByte, "%08X", iWidth*iHeight);
	pDisplayImg[34] = (FourByte[6] > 0x39 ? (FourByte[6] - 0x37) * 16 : (FourByte[6] - 0x30) * 16) + (FourByte[7] > 0x39 ? (FourByte[7] - 0x37) : (FourByte[7] - 0x30));
	pDisplayImg[35] = (FourByte[4] > 0x39 ? (FourByte[4] - 0x37) * 16 : (FourByte[4] - 0x30) * 16) + (FourByte[5] > 0x39 ? (FourByte[5] - 0x37) : (FourByte[5] - 0x30));
	pDisplayImg[36] = (FourByte[2] > 0x39 ? (FourByte[2] - 0x37) * 16 : (FourByte[2] - 0x30) * 16) + (FourByte[3] > 0x39 ? (FourByte[3] - 0x37) : (FourByte[3] - 0x30));
	pDisplayImg[37] = (FourByte[0] > 0x39 ? (FourByte[0] - 0x37) * 16 : (FourByte[0] - 0x30) * 16) + (FourByte[1] > 0x39 ? (FourByte[1] - 0x37) : (FourByte[1] - 0x30));;
	INT32 index = 0;
	for (INT32 i = 0x36; i < 0x36 + iWidth*iHeight * 3; i += 3){
		pDisplayImg[i] = pCurImg_b[index];
		pDisplayImg[i + 1] = pCurImg_g[index];
		pDisplayImg[i + 2] = pCurImg_r[index++];
	}

	//printf("%d%d%d\n",iWidth,iHeight,iWidth*iHeight * 3 + 0x36);
	fwrite(pDisplayImg, iWidth*iHeight * 3 + 0x36, 1, fpDisplayImg);
	fflush(fpDisplayImg); fclose(fpDisplayImg);
	delete[]pDisplayImg;
}

void ReadBMPFile(char *fileName, UINT8 *pFileBuf, INT32 iWidth, INT32 iHeight){
	FILE*fp = fopen(fileName, "rb+");//BMP文件名
	if (fp == NULL){
		printf("File : %s Not Found \n", fileName);
		return;
	}
	fseek(fp, 0, SEEK_SET);
	fseek(fp, 0L, SEEK_END);
	INT32 iFileLen = ftell(fp);//文件的长度
	UINT8 *pBMPBuffer = new UINT8[iFileLen + 1];//申请空间存储BMP文件
	fseek(fp, 0, SEEK_SET);
	fread(pBMPBuffer, iFileLen, 1, fp);//读取BMP文件数据
	//8位BMP从文件起始位置偏移0x436后，是真实数据起始位置
	//memcpy(pFileBuf,pBMPBuffer+0x436,sizeof(UINT8)*iWidth*iHeight);
	for (INT32 i = 0; i < iWidth; i++){
		for (INT32 j = 0; j < iHeight; j++){
			pFileBuf[j*iWidth + i] = (pBMPBuffer + 0x436)[(iHeight - j - 1)*iWidth + i];
		}
	}
	delete[]pBMPBuffer;	fclose(fp);
}

int main(int argc, char* argv[])
{
	//开始读取图像..
	int iWidth = 0, iHeight = 0;
	if (argc <= 1){
		cout << " Too few parameters" << endl; return 0;
	}
	try	{
		iWidth = atoi(argv[1]);		//参数三是宽度
		iHeight = atoi(argv[2]);	//参数4是高度
	}
	catch (...)	{
		iWidth = 0;iHeight = 0;
	}
	
	if (iWidth != 0 && iHeight != 0)
	{
		UINT8 *pCurImg_r = (UINT8 *)malloc(iWidth * iHeight * sizeof(UINT8)); memset(pCurImg_r, 0, iWidth * iHeight);
		UINT8 *pCurImg_g = (UINT8 *)malloc(iWidth * iHeight * sizeof(UINT8)); memset(pCurImg_g, 0, iWidth * iHeight);
		UINT8 *pCurImg_b = (UINT8 *)malloc(iWidth * iHeight * sizeof(UINT8)); memset(pCurImg_b, 0, iWidth * iHeight);

		ReadBMPFile(g_CurImg_r_filePath, pCurImg_r, iWidth, iHeight);
		ReadBMPFile(g_CurImg_g_filePath, pCurImg_g, iWidth, iHeight);
		ReadBMPFile(g_CurImg_b_filePath, pCurImg_b, iWidth, iHeight);

		WriteBMP24("CombRGB_New.bmp", pCurImg_r, pCurImg_g, pCurImg_b, iWidth, iHeight);
		cout << "bmp Comb Successful!" << endl;
	}
	else
	{
		cout << "iw or ih == zero" << endl;
	}
	return 0;
}