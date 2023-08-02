#ifndef __UNICODE_MAP_H_
#define __UNICODE_MAP_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "BaseConst.h"

class Utf16Map
{
	UINT16  *index;  //����0xa1a1 �� fefe,
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
		
		//�ļ������ǰ���˱��棬�˴���Ҫ�����ֽ���ת��
		for(INT32 i=0;i<MaxUintNum;i++)
			assign_htol(index[i]);

		return TRUE;
	}

	//�����ַ���ת��������װ�����ʵ���ֽ���
	//������buf�ĳߴ�
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
			if ((pos+2) > outSize)  //��ֹ������
				break;
			if (inBuf[i] & 0x80){ 
				if (((UINT8)inBuf[i] < (UINT8)0xa1)||((UINT8)inBuf[i+1] < (UINT8)0xa1))  //������ַ���
					code = 0x20;  //ȱʡ���ո���
				else{//�Ǻ���
					no = (UINT8)inBuf[i] - (UINT8)0xa1;  //��ͨ�ַ����Ǹ���ǰ
					no *= 94;  //ÿ��94������
					no += (UINT8)inBuf[i+1] - (UINT8)0xa1;
					code = index[no];
				}

				if (BORDER::MY_ORDER != order)
					assign_htol(code);  //�����ֽ����뷢�����ַ����ֽ���ͬ����Ҫ���ֽ���

				memcpy(&outBuf[pos], &code, 2);
				i++;
				pos += 2;
				continue;
			}

			//��ascii�ַ�
			if (order == BORDER::OrderBigEndian){
				outBuf[pos] = 0;  //��0
				pos ++;
				outBuf[pos] = inBuf[i]; //����ԭ�е�ascii��
				pos ++;
			}
			else{
				outBuf[pos] = inBuf[i]; //����ԭ�е�ascii��
				pos ++;
				outBuf[pos] = 0;  //��0
				pos ++;
			}
		}
		return pos;
	}

};

#endif
