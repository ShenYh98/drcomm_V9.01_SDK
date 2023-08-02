#ifndef __UNICODE_MAP_H_
#define __UNICODE_MAP_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "BaseConst.h"

class Utf16Map
{
	UINT16  *index;  //编码0xa1a1 ～ fefe,
	UINT8	order;

public:
	static const UINT32 MaxUintNum = 94 * 94;

	Utf16Map(){index = NULL;}

	~Utf16Map(){
		if (!index){
			delete[] index;
			index = NULL;
		}
	}

	BOOL Init(UINT8	order1){
		order = order1;
		index = new UINT16[MaxUintNum];
		if (!index)
			return FALSE;
		memset(index, 0, MaxUintNum * sizeof(UINT16));

		FILE *f;
		f = fopen("utf16Map.dat", "rb");
		if (f == NULL){
			delete[] index;
			index = NULL;
			return FALSE;
		}
		fread(index, 2, MaxUintNum, f);
		fclose(f);

		if (order != BORDER::OrderLitEndian)
			return TRUE;
		
		//文件内容是按大端保存，此处是要进行字节序转化
		for(INT32 i=0;i<MaxUintNum;i++)
			assign_htol(index[i]);

		return TRUE;
	}

	//进行字符串转换，返回装换后的实际字节数
	//最大输出buf的尺寸
	UINT16 StringToUtf16(char * inBuf, INT32 inSize, UINT8 * outBuf, INT32 outSize)
	{
		if (order == BORDER::OrderLitEndian){
			outBuf[0] = 0xff;
			outBuf[1] = 0xfe;
		}
		else{
			outBuf[0] = 0xfe;
			outBuf[1] = 0xff;
		}
		INT32 pos = 2;

		UINT16 no, code;
		for(INT32 i=0; i<inSize; i++){
			if ((pos+2) > outSize)  //防止打包溢出
				break;
			if (inBuf[i] & 0x80){ 
				if (((UINT8)inBuf[i] < (UINT8)0xa1)||((UINT8)inBuf[i+1] < (UINT8)0xa1))  //错误的字符串
					code = 0x20;  //缺省按空格填
				else{//是汉字
					no = (UINT8)inBuf[i] - (UINT8)0xa1;  //普通字符串是高在前
					no *= 94;  //每区94个汉字
					no += (UINT8)inBuf[i+1] - (UINT8)0xa1;
					code = index[no];
				}

				if (BORDER::MY_ORDER != order)
					assign_htol(code);  //本机字节序与发出的字符串字节序不同，需要倒字节序

				memcpy(&outBuf[pos], &code, 2);
				i++;
				pos += 2;
				continue;
			}

			//是ascii字符
			if (order == BORDER::OrderBigEndian){
				outBuf[pos] = 0;  //补0
				pos ++;
				outBuf[pos] = inBuf[i]; //保留原有的ascii码
				pos ++;
			}
			else{
				outBuf[pos] = inBuf[i]; //保留原有的ascii码
				pos ++;
				outBuf[pos] = 0;  //补0
				pos ++;
			}
		}
		return pos;
	}

};

#endif
