#ifndef __CommonCfg_H_
#define __CommonCfg_H_

#include <stdlib.h>
#include <float.h>
#include "PubDef.h"
#include "SysProc.h"

#ifdef _WINDOWS
#include <Winsock2.h>
#pragma comment(lib, "wsock32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <pthread.h>
#include <dlfcn.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <malloc.h>
#include <netinet/tcp.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include <map>
#include <string>
#include <vector>
#include <algorithm>  //sort�Ķ���
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

#define SOCKET INT32
#endif

/*
�����Լ��̬�������ͨ����̬��ϵͳ���Զ�����1���Ի�����̬���棬
����̬������ȷ�ϡ�ȡ����ť��ͬʱ��һ����������ҳ���棬ÿ������ҳ��Ӧһ�������á�
ÿ������ҳ��������񣬶�ά������ά���
��ά����ͷ�ֱ�����š�������ÿ���ֶ���(����NS2000ϵͳ����)������ÿһ�ж���1����¼���壬ѡ��ĳ����¼��
��ά���ĵ�һά��ʾ�����¼�ĸ����ֶ������ڶ�ά��ʾ��Ӧ�ֶε�ֵ
��ά���ļ�¼�ɶ�ѡ������Ҽ�������ѡ�еļ�¼���Ը��ơ����ӡ�ɾ�������롢���ơ�����

���ĳ��Table�ļ�¼����>0,��ʾ��¼��Ϊ�̶�ֵ����Table��¼�������䣬��˲��ṩ�Լ�¼�����ӡ����롢ɾ������,������¼�ĸ��ơ����ơ����Ʋ���
ע������ҳ�Ľ�����Ҳ���Կ�����������ʾ���ɲμ�NS3000��̬���棬ÿ������Ҷ�Ӿ���һ�����塣

���ȷ�ϣ�����ҳ������ã�������̬����buf
��̬����buf�ṹ���壺
�ֽ�˳��1�ֽڣ����汾�ţ�1�ֽڣ���Itable������2�ֽڣ�����buf���ȣ�4�ֽڣ�����ͷ�������ȣ�--��ͷ(CCommonCfgHead),��Ϊ��������
��0��Table���壺
	0Table��CTableHead + ���м�¼����
	CTableHead����Table�ֶθ�����4�ֽڣ�,������¼���ȣ�4�ֽڣ�����¼������4�ֽڣ�,
������
��n��Table���壺
	n��Table��CTableHead + ���м�¼����


ʹ�ã�
	��Լ����ʱ�Զ����ɲ�����̬��ʽ����
	����Buf�����ɸ�����̬ʵ������
*/

struct CIntValue{
	INT32 iValue;
	char  szValueName[Fr::NAME_LENGTH];
};

namespace CDD{
	static const INT32 DT_VisibleString	= BDT::VisibleString;	//��ͨ�ַ���
//	static const INT32 DT_KERTIME		= BDT::INT_64U	;	//��KERTIME����,������32λ��ʱ��,����KERTIME
	static const INT32 DT_INT32			= BDT::INT_32	;  //��̬���ݲ�����С��4���ֽڵ�����
	static const INT32 DT_BOOL32		= BDT::BOOL_32	;
	static const INT32 DT_FLOAT32		= BDT::FLOAT_32	;
	static const INT32 DT_FLOAT64		= BDT::FLOAT_64	;
	static const INT32 DT_FrDataIdx		= BDT::KEYID	;  //��������������Ϊ4���ֽڣ����ݽṹ�����FrDataIdx

	//��������
    const INT32 eCfgNormal			=  0; //��ͨ
    const INT32 eCfgHex				=  1; //16��������
    const INT32 eCfg32BitValue		= 26; //32λ�ı�־λ����
    const INT32 eCfgIpAddress		= 12; //Ip��ַ
    const INT32 eCfgRGB				= 13; //RGB��ɫ
    const INT32 eCfgDropList		=  4; //���޶����������ݼ���
	//�ַ�������
    const INT32 eCfgPassWord		=  3; //��������
	const INT32 eCfgPrinter			= 23; //��ӡ����
    const INT32 eCfgFileSelect		= 41; //�ļ�ѡ��
};

//�ֶ����ݵ�ͨ����̬����
struct CField
{
public:
	char	szName[Fr::NAME_LENGTH];	//�ֶ�����
	INT32	iDataType;		//�ֶ���������,CDD::DT_
	INT32	iDataSize;		//�ֶ����ݳ��ȣ���ʾʵ��ռ�õ��ֽ���
	INT32	iCfgType;		//�ֶ�������̬��ʽ��������ʮ���ơ�ʮ��������ʾ��,CDD::eCfg
	FLOAT32 fDefaultValue;	//ȱʡֵ
	FLOAT32 fMaxValue;		//���ֵ
	FLOAT32 fMinValue;		//��Сֵ
	INT32	lenDecimal;		//��ʾС��λ��
	INT32	intValueNum;	//����ֵ�б�����
	CIntValue *pIntValueList;//����ֵ�б�,����Ƿ�����ֵ���ɽ���ͬ�����ֵҲ������������ʾ
	INT32	iOffset;		//�ڼ�¼�е�ƫ��λ��,�Զ�����õ�

public:
	void SetDefault(){
		szName[0] = 0;
		iDataType = CDD::DT_INT32;
		iDataSize = 4;
		iCfgType  = CDD::eCfgNormal;
		fDefaultValue = 0;
		fMaxValue = FLT_MAX;
		fMinValue = FLT_MIN;
		lenDecimal = 3;
		intValueNum = 0;
		pIntValueList = NULL;
		iOffset = 0;
	}

	void FillWithDefaultValue(BYTE *buf)
	{
		if (iDataType == CDD::DT_BOOL32){
			BOOL32 bv = (BOOL32)fDefaultValue;
			memcpy(buf, &bv, sizeof(BOOL32));
		}
		else if (iDataType == CDD::DT_FLOAT32){
			memcpy(buf, &fDefaultValue, 4);
		}
		else if (iDataType == CDD::DT_FLOAT64){
			FLOAT64 dv = (FLOAT64)fDefaultValue;
			memcpy(buf, &dv, sizeof(FLOAT64));
		}
		else if (iDataType == CDD::DT_INT32){
			INT32 iv = (INT32)fDefaultValue;
			memcpy(buf, &iv, sizeof(INT32));
		}
		else if (iDataType == CDD::DT_FrDataIdx){
			INT32 iv = (INT32)fDefaultValue;
			memcpy(buf, &iv, sizeof(INT32));
		}
		else memset(buf, 0, iDataSize);
	}

	void ToDefaultValueString(INT32 size1, CHAR *text1){
		text1[0] = 0;
		switch (iDataType){
			case CDD::DT_BOOL32:
				if ((BOOL32)fDefaultValue)
					SYSPROC::StrSafeCat(size1, text1, "Y");
				return;
			case CDD::DT_FLOAT64:
			case CDD::DT_FLOAT32:
				{
					CHAR sf[32];
					sprintf(sf, "%%.%df", lenDecimal);
					sprintf(text1, sf, fDefaultValue);
				}
				return;
			case CDD::DT_INT32:
				{
					INT32 iv = (INT32)fDefaultValue;
					if (iCfgType == CDD::eCfgDropList){
						for(INT32 i=0;i<intValueNum;i++)
							if (iv == pIntValueList[i].iValue)
								return SYSPROC::StrSafeCat(size1, text1, pIntValueList[i].szValueName);
						return;
					}
					else if (iCfgType == CDD::eCfgHex)
						sprintf(text1, "%X", iv);
					else if (iCfgType == CDD::eCfgIpAddress){
						UINT32 iv1 = iv;
						if (BORDER::MY_ORDER != BORDER::OrderBigEndian)
							assign_htol(iv1);
						sprintf(text1, "%d.%d.%d.%d", (BYTE)(iv1>>24), (BYTE)((iv1>>16)%0x100), (BYTE)((iv1>>8)%0x100), (BYTE)(iv1%0x100));
					}
					else 
						sprintf(text1, "%d", iv);
				}
				return;
			case CDD::DT_FrDataIdx:
				return;
				/*
			case CDD::DT_KERTIME:
				{
					KERTIME kt = KERTIME::CurrentLocalKerTime();
					kt.ToString(text1, size1, KERTIME::F_DM4Y_HMS_M);
				}
				return;
				*/
			case CDD::DT_VisibleString:
				return;
		}
	}

	void ToString(INT32 size1, CHAR *text1, void *dataBuf1){
		text1[0] = 0;
		switch (iDataType){
			case CDD::DT_BOOL32:
				if (*(BOOL32 *)dataBuf1)
					SYSPROC::StrSafeCat(size1, text1, "Y");
				return;
			case CDD::DT_FLOAT64:
				{
					CHAR sf[32];
					sprintf(sf, "%%.%df", lenDecimal);
					FLOAT64 df;
					memcpy(&df, dataBuf1, 8);
					sprintf(text1, sf, df);
				}
				return;
			case CDD::DT_FLOAT32:
				{
					CHAR sf[32];
					sprintf(sf, "%%.%df", lenDecimal);
					FLOAT32 ff;
					memcpy(&ff, dataBuf1, 4);
					sprintf(text1, sf, ff);
				}
				return;
			case CDD::DT_INT32:
				{
					INT32 iv;
					memcpy(&iv, dataBuf1, 4);
					if (iCfgType == CDD::eCfgDropList){
						for(INT32 i=0;i<intValueNum;i++)
							if (iv == pIntValueList[i].iValue)
								return SYSPROC::StrSafeCat(size1, text1, pIntValueList[i].szValueName);
						return;
					}
					else if (iCfgType == CDD::eCfgHex)
						sprintf(text1, "%X", iv);
					else if (iCfgType == CDD::eCfgIpAddress){
						UINT32 iv1 = iv;
						if (BORDER::MY_ORDER != BORDER::OrderBigEndian)
							assign_htol(iv1);
						sprintf(text1, "%d.%d.%d.%d", (BYTE)(iv1>>24), (BYTE)((iv1>>16)%0x100), (BYTE)((iv1>>8)%0x100), (BYTE)(iv1%0x100));
					}
					else 
						sprintf(text1, "%d", iv);
				}
				return;
			case CDD::DT_FrDataIdx:
				{
					FrDataIdx fdi = *(FrDataIdx *)dataBuf1;
					fdi.ToString(text1);
				}
				return;
				/*
			case CDD::DT_KERTIME:
				{
					KERTIME kt;
					memcpy(&kt.Tm, dataBuf1, sizeof(kt.Tm));
					kt.ToString(text1, size1, KERTIME::F_DM4Y_HMS_M);
				}
				return;
				*/
			case CDD::DT_VisibleString:
				SYSPROC::StrSafeCat(size1, text1, (CHAR *)dataBuf1);
				return;
		}
	}

	BOOL32 GetDataBuf(BYTE *dataBuf1, CHAR *text1){
		memset(dataBuf1, 0, iDataSize);
		if (text1[0] ==0)
			return TRUE;
		switch (iDataType){
			case CDD::DT_BOOL32:
				*(BOOL32 *)dataBuf1 = FALSE;
				if ((text1[0] == 'Y')||(text1[0] == 'y')||(text1[0] == '1'))
					*(BOOL32 *)dataBuf1 = TRUE;
				return TRUE;
			case CDD::DT_FLOAT32:
				{	FLOAT32 fv = (FLOAT32)atof(text1);
					memcpy(dataBuf1, &fv, sizeof(FLOAT32));
				}
				return TRUE;
			case CDD::DT_FLOAT64:
				{	FLOAT64 fv = (FLOAT64)atof(text1);
					memcpy(dataBuf1, &fv, sizeof(FLOAT64));
				}
				return TRUE;
			case CDD::DT_INT32:
				if (iCfgType == CDD::eCfgDropList){
					for(INT32 i=0;i<intValueNum;i++)
						if (strcmp(pIntValueList[i].szValueName, text1)==0){
							memcpy(dataBuf1, &pIntValueList[i].iValue, 4);
							return TRUE;
						}
					return FALSE;
				}
				else{
					INT32 iv;
					if ((iCfgType == CDD::eCfgHex)||(iCfgType == CDD::eCfg32BitValue))
						sscanf(text1, "%X", &iv);
					else if (iCfgType == CDD::eCfgIpAddress)
						iv = (UINT32)inet_addr(text1);
					else
						iv = atoi(text1);
					memcpy(dataBuf1, &iv, 4);
				}
				return TRUE;
			case CDD::DT_FrDataIdx:
				{
					FrDataIdx *pFdi = (FrDataIdx *)dataBuf1;
					return pFdi->SetData(text1);
				}
				/*
			case CDD::DT_KERTIME:
				{
					KERTIME kt;
					memcpy(&kt.Tm, dataBuf1, sizeof(kt.Tm));
					return kt.SetData(text1, KERTIME::F_DM4Y_HMS_M);
				}
				*/
			case CDD::DT_VisibleString:
				SYSPROC::StrSafeCat(iDataSize, (CHAR *)dataBuf1, text1);
				dataBuf1[iDataSize-1] = 0;
				return TRUE;
		};
		return FALSE;
	}
	
	//���������ֽ�˳��������̬buf�Ķ�д֮ǰ��Ҫ���øú���
	INT32 ResetOrder(BYTE order1, BYTE* pBuffer1)
	{
		if (order1 == BORDER::MY_ORDER)
			return iDataSize;
		if (iDataType == CDD::DT_VisibleString)
			return iDataSize;
/*		if (iDataType == CDD::DT_KERTIME){
			INT64 value;
			memcpy(&value, pBuffer1, 8);
			assign_htol(value);
			memcpy(pBuffer1, &value, 8);
			return iDataSize;
		}
		*/
		if (iDataType == CDD::DT_FLOAT64){
			INT64 value;
			memcpy(&value, pBuffer1, 8);
			assign_htol(value);
			memcpy(pBuffer1, &value, 8);
			return iDataSize;
		}

		if (iDataSize ==2){
			INT16 value;
			memcpy(&value, pBuffer1, 2);
			assign_htol(value);
			memcpy(pBuffer1, &value, 2);
		}
		else if (iDataSize ==4)
			if (iCfgType == CDD::eCfgIpAddress){  //IPaddress�Ѿ�����̬����ת��Ϊ�����ֽڴ�ŵĸ�ʽ��������ת���ֽ�˳��
			}
			else if (iDataType == CDD::DT_FrDataIdx){  //IPaddress�Ѿ�����̬����ת��Ϊ�����ֽڴ�ŵĸ�ʽ��������ת���ֽ�˳��
				FrDataIdx *pFdi = (FrDataIdx *)pBuffer1;
				pFdi->ResetOrder(order1);
			}
			else{
				INT32 value;
				memcpy(&value, pBuffer1, 4);
				assign_htol(value);
				memcpy(pBuffer1, &value, 4);
			}

		return iDataSize;
	};
public:
	BOOL32 SetINT32Def(const CHAR *szName1, FLOAT32 fDefaultValue1 = 0.0f, INT32 iCfgType1=CDD::eCfgNormal, FLOAT32 fMaxValue1 = (FLOAT32)2147483647, FLOAT32 fMinValue1 = (FLOAT32)-2147483647){
		szName[0] = 0;
		SYSPROC::StrSafeCat(sizeof(szName), szName, szName1);
		szName[sizeof(szName)-1] = 0;
		iDataType		= CDD::DT_INT32	;
		fDefaultValue	= fDefaultValue1;
		iCfgType		= iCfgType1		;
		fMaxValue		= fMaxValue1	;
		fMinValue		= fMinValue1	;
		return TRUE;
	}

	BOOL32 SetINT32ListMode(INT32 intValueNum1=0, CIntValue const *pIntValueList1=NULL){
		iCfgType = CDD::eCfgDropList;
		intValueNum	= intValueNum1		;
		if((intValueNum1 ==0)||(pIntValueList1==NULL)){
			intValueNum	= 0;
			pIntValueList = NULL;
			return TRUE;
		}
		pIntValueList = new CIntValue[intValueNum];
		memcpy(pIntValueList, pIntValueList1, sizeof(CIntValue)*intValueNum);
		return TRUE;
	}

	BOOL32 SetFLOAT32Def(const CHAR *szName1, FLOAT32 fDefaultValue1 = 0.0f, FLOAT32 fMaxValue1 = FLT_MAX, FLOAT32 fMinValue1 = FLT_MIN, INT32 lenDecimal1 = 3){
		szName[0] = 0;
		SYSPROC::StrSafeCat(sizeof(szName), szName, szName1);
		iDataType		= CDD::DT_FLOAT32	;
		fDefaultValue	= fDefaultValue1	;
		fMaxValue		= fMaxValue1		;
		fMinValue		= fMinValue1		;
		lenDecimal		= lenDecimal1		;
		return TRUE;
	}
	BOOL32 SetFLOAT64Def(const CHAR *szName1, FLOAT32 fDefaultValue1 = 0.0f, FLOAT32 fMaxValue1 = FLT_MAX, FLOAT32 fMinValue1 = FLT_MIN, INT32 lenDecimal1 = 3){
		szName[0] = 0;
		SYSPROC::StrSafeCat(sizeof(szName), szName, szName1);
		iDataType		= CDD::DT_FLOAT64	;
		iDataSize		= 8;
		fDefaultValue	= fDefaultValue1	;
		fMaxValue		= fMaxValue1		;
		fMinValue		= fMinValue1		;
		lenDecimal		= lenDecimal1		;
		return TRUE;
	}

	BOOL32 SetFrDataIdxDef(const CHAR *szName1, INT32 iCfgType1=CDD::eCfgNormal){
		szName[0] = 0;
		SYSPROC::StrSafeCat(sizeof(szName), szName, szName1);
		iDataType = CDD::DT_FrDataIdx;
		iDataSize = sizeof(FrDataIdx);
		iCfgType  = iCfgType1		;
		return TRUE;
	}

	BOOL32 SetBOOL32Def(const CHAR *szName1, INT32 iCfgType1=CDD::eCfgNormal){
		szName[0] = 0;
		SYSPROC::StrSafeCat(sizeof(szName), szName, szName1);
		iDataType = CDD::DT_BOOL32;
		iDataSize = sizeof(BOOL32);
		iCfgType  = iCfgType1		;
		fDefaultValue	= 0.0f;
		return TRUE;
	}

	BOOL32 SetStringDef(const CHAR *szName1, INT32 iDataSize1, INT32 iCfgType1=CDD::eCfgNormal){
		szName[0] = 0;
		SYSPROC::StrSafeCat(sizeof(szName), szName, szName1);
		iDataType = CDD::DT_VisibleString;
		iDataSize = iDataSize1;
		iCfgType  = iCfgType1		;
		return TRUE;
	}
/*
	BOOL32 SetKertimeDef(const CHAR *szName1, INT32 iCfgType1=CDD::eCfgNormal){
		szName[0] = 0;
		SYSPROC::StrSafeCat(sizeof(szName), szName, szName1);
		iDataType = CDD::DT_KERTIME;
		iDataSize = sizeof(KERTIME);
		iCfgType  = iCfgType1		;
		return TRUE;
	}
	*/
};

class CCommonCfgHead{
public:
	BYTE order;			//�ֽ�˳��1�ֽڣ�
	BYTE version;		//�汾�ţ�1�ֽڣ�
	UINT16 numTable;	//��������2�ֽڣ���
	INT32 size;			//��buf���ȣ�4�ֽڣ�����ͷ�������ȣ�
	void ResetOrder(){
		if (order == BORDER::MY_ORDER)
			return;
		assign_htol(numTable);
		assign_htol(size);
	}
};

class CTableHead{
public:
	char  szName[Fr::NAME_LENGTH];	//������
	INT32 numField;		//��¼�ֶθ�����4�ֽڣ�
	INT32 iUnitSize;	//������¼���ȣ�4�ֽڣ�
	INT32 numRecord;		//��¼������4�ֽڣ�
public:
	void ResetOrder(BYTE order1){
		if (order1 == BORDER::MY_ORDER)
			return;
		assign_htol(numField);
		assign_htol(iUnitSize);
		assign_htol(numRecord);
	}
};


//����
class CTable{
public:
	char	szName[Fr::NAME_LENGTH];	//������
	INT32	numField;	//�ֶε�����
	CField *pField;//ÿ�����ݵ�ͨ����̬����
	INT32	iUnitSize;   //����¼��С������õ�
	INT32	numFixRecord;  //�̶���¼���������Ϊ0����ʾ��¼��������
	INT32	numRecord;

	BYTE *  cfgDataBuf;  //ԭ��̬���õĲ���������ͷ,ֻ��һ��ָ�벻����ռ�
	BYTE *  cfgTmpBuf;	//ԭ��¼�뱣���¼��С��һ��ʱ��������������ʱ����ռ�
	INT32	cfgUnitSize;   //ԭ��̬���õĵ���¼��С
	BYTE *  dataBuf;  //��̬�ã�����̬���ɵ�buf������ͷ,����ռ�

public:
	//numFixRecord1==0��ʾ��¼������
	void Init(const char *szName1, INT32 numField1, INT32 numFixRecord1=0){
		memset(this, 0, sizeof(*this));
		SYSPROC::StrSafeCat(sizeof(szName), szName, szName1);
		numField = numField1;
		if (numField>0)
			pField = new CField[numField];
		if (pField==NULL)
			numField = 0;
		INT32 i;
		for(i=0;i<numField;i++)
			pField[i].SetDefault();

		numFixRecord = numFixRecord1;
	}

	CTable(){ SetDefaultValue();}

	~CTable(){
		if (pField != NULL)
			delete[] pField;
		if (dataBuf != NULL)
			delete[] dataBuf;
		if ((cfgUnitSize>0)&&(numRecord>0)&&(cfgUnitSize != iUnitSize)&&(cfgTmpBuf!=NULL))
			delete[] cfgTmpBuf;
	}

	void SetDefaultValue(){
		numRecord = 0;
		cfgDataBuf = NULL;
		cfgTmpBuf = NULL;
		dataBuf = NULL;
	}

	void FillRecWithDefaultValue(BYTE *buf){
		for(INT32 i=0;i<numField;i++)
			pField[i].FillWithDefaultValue(&buf[pField[i].iOffset]);
	}

public:  //�������ݶ���ĺ���
	void SetSizeAndOffset(){
		INT32 pos = 0;
		for (INT32 i=0;i<numField;i++){
			pField[i].iOffset = pos;
			pos += pField[i].iDataSize;
		}
		iUnitSize = pos;
	}

public:
	BOOL32 SetRecordNum(INT32 numRecord1){
		numRecord = numRecord1;
		INT32 len =  iUnitSize * numRecord1;
		if (dataBuf != NULL)
			delete[] dataBuf;
		dataBuf = new BYTE[len];
		if (dataBuf == NULL)
			return FALSE;
		return TRUE;
	}

	//���������ֽ�˳��������̬buf�Ķ�֮ǰ��Ҫ���øú���,��̬buf�ṹ���ܱ����е�С
	void ResetDataOrder(BYTE order1)
	{
		if (order1 == BORDER::MY_ORDER)
			return;
		CTableHead *pHead = (CTableHead *)cfgDataBuf;
		INT32 pos = sizeof(CTableHead);
		INT32 len = pos + pHead->iUnitSize * pHead->numRecord;
		INT32 fieldPos;
		for(INT32 i=0;i<pHead->numRecord;i++)
		{
			fieldPos = 0;
			for(INT32 j=0;j<pHead->numField;j++){
				if ((fieldPos + pField[j].iDataSize)>cfgUnitSize)
					break;
				if ((pos + fieldPos + pField[j].iDataSize) > len)
					return;
				pField[j].ResetOrder(order1, &cfgDataBuf[pos+fieldPos]);
				fieldPos += pField[j].iDataSize;
			}
			pos += cfgUnitSize;
			}
	};

public://��̬����Լ��
	INT32 GetRecordNum(){ //��cfgDataBuf��ȡ����,��Լ��
		if (cfgDataBuf == NULL)
			return 0;
		CTableHead *pHead = (CTableHead *)cfgDataBuf;
		return pHead->numRecord; 
	}

	//���ؼ�¼����
	//GetDynamicTable �� ReadDynamicTable�������ڣ�ReadDynamicTable�����·���ռ䣬
	//GetDynamicTable��ʹ��ԭ�е����ÿռ䣬�����Ԫ��С��һ�£��������·���ռ䣬����ͬReadDynamicTable
	//GetDynamicTable�������԰���CreateNodeRealTimeData�����޸Ĺ���������Ϣ
	BYTE * GetDynamicTable(INT32 iUnitSize1, INT32 * pRecordNum1){ //��cfgDataBuf��ȡ����,��Լ��
		if (pRecordNum1 == NULL)
			return NULL;
		*pRecordNum1 =0;

		if (cfgDataBuf == NULL)
			return NULL;

		CTableHead *pHead = (CTableHead *)cfgDataBuf;

		INT32 size = pHead->iUnitSize;
		if (size != iUnitSize1)
			return ReadDynamicTable(iUnitSize1, pRecordNum1);

		INT32 numRec = pHead->numRecord;
		if (pHead->numRecord <=0)
			return NULL;

		*pRecordNum1 = numRec;

		INT32 pos = sizeof(CTableHead);

		return &cfgDataBuf[pos];
	} 

	//���ؼ�¼����
	BYTE * ReadDynamicTable(INT32 iUnitSize1, INT32 * pRecordNum1){ //��cfgDataBuf��ȡ����,��Լ��
		if (pRecordNum1 == NULL)
			return NULL;
		*pRecordNum1 =0;

		if (cfgDataBuf == NULL)
			return NULL;

		CTableHead *pHead = (CTableHead *)cfgDataBuf;

		INT32 size = pHead->iUnitSize;
		if (size >iUnitSize1)
			size = iUnitSize1;
		
		INT32 numRec = pHead->numRecord;
		if (pHead->numRecord <=0)
			return NULL;

		cfgTmpBuf = new BYTE[iUnitSize1 * numRec];
		if (cfgTmpBuf == NULL)
			return NULL;
		memset(cfgTmpBuf, 0, iUnitSize1 * numRec);
		
		*pRecordNum1 = numRec;

		INT32 pos = sizeof(CTableHead);
		BYTE *ptr = (BYTE *)cfgTmpBuf;
		for(INT32 i=0;i<numRec;i++){
			FillRecWithDefaultValue(ptr);
			memcpy(ptr, &cfgDataBuf[pos], size);
			ptr += iUnitSize1;
			pos += pHead->iUnitSize;
		}
		return cfgTmpBuf;
	} 
	//����̬������
	//���ض�����¼����
	INT32 ReadStaticTable(INT32 iUnitSize1, void * buffer1, INT32 recordNum1){ //��cfgDataBuf��ȡ����,��Լ��
		if (cfgDataBuf == NULL)
			return 0;

		if ((buffer1 == NULL)||(recordNum1 <=0))
			return 0;
		
		CTableHead *pHead = (CTableHead *)cfgDataBuf;

		INT32 size = pHead->iUnitSize;
		if (size >iUnitSize1)
			size = iUnitSize1;
		
		INT32 numRec = pHead->numRecord;
		if (pHead->numRecord <=0)
			return 0;

		if (numRec > recordNum1){
			printf("RecordNum too small!");
			numRec = recordNum1;
		}
		
		memset(buffer1, 0, iUnitSize1 * numRec);
		
		INT32 pos = sizeof(CTableHead);
		BYTE *ptr = (BYTE *)buffer1;
		for(INT32 i=0;i<numRec;i++){
			FillRecWithDefaultValue(ptr);
			memcpy(ptr, &cfgDataBuf[pos], size);
			ptr += iUnitSize;
			pos += pHead->iUnitSize;
		}
		return numRec;
	} 
	void ReadData(INT32 noRecord1, INT32 noField1, INT32 sizeData1, BYTE *buffer1){  //��cfgDataBuf��ȡ����,��̬��
		memset(buffer1, 0, sizeData1);
		if (cfgDataBuf == NULL){
			if (pField[noField1].iDataType == CDD::DT_BOOL32){
				FLOAT32 fv;
				memcpy(&fv, &pField[noField1].fDefaultValue, sizeof(FLOAT32));
				BOOL32 bv = (BOOL32)fv;
				memcpy(buffer1, &bv, sizeof(BOOL32));
			}
			else if (pField[noField1].iDataType == CDD::DT_INT32){
				FLOAT32 fv;
				memcpy(&fv, &pField[noField1].fDefaultValue, sizeof(FLOAT32));
				INT32 iv = (INT32)fv;
				memcpy(buffer1, &iv, sizeof(INT32));
			}
			else if (pField[noField1].iDataType == CDD::DT_FLOAT32)
				memcpy(buffer1, &pField[noField1].fDefaultValue, sizeof(FLOAT32));
			else if (pField[noField1].iDataType == CDD::DT_FLOAT64){
				memcpy(buffer1, &pField[noField1].fDefaultValue, sizeof(FLOAT64));
			}
			return;
		}

		CTableHead *pHead = (CTableHead *)cfgDataBuf;

		if ((noField1<0)||(noField1 >= pHead->numField))
			return;

		if ((noRecord1<0)||(noRecord1 >= pHead->numRecord))
			return;

		INT32 size = pField[noField1].iDataSize;
		if (size > sizeData1)
			return;

		INT32 pos = sizeof(CTableHead) + pHead->iUnitSize * noRecord1 + pField[noField1].iOffset;
		memcpy(buffer1, &cfgDataBuf[pos], size);
	}

public:  //����̬��
	INT32 OutputCfgBuf(BYTE * buffer1){  //�����̬buf
		CTableHead *pTableHead;
		pTableHead = (CTableHead *)buffer1;
		memcpy(pTableHead->szName, szName, sizeof(pTableHead->szName));
		pTableHead->iUnitSize	= iUnitSize;
		pTableHead->numField	= numField;
		pTableHead->numRecord	= numRecord;
		if (dataBuf == NULL)
			return sizeof(CTableHead);

		INT32 len = iUnitSize * numRecord;
		memcpy(&buffer1[sizeof(CTableHead)], dataBuf, len);
		return (sizeof(CTableHead) + len);
	};
	BOOL32 WriteData(INT32 noRecord1, INT32 noField1, void * value1){ //��������,���������б����ݣ����ݵ����б��е�����,ʵ�ʴ洢����������
		if ((noField1<0)||(noField1 >= numField))
			return FALSE;
		if ((noRecord1<0)||(noRecord1 >= numRecord))
			return FALSE;
		if (value1 == NULL)
			return FALSE;
		if (dataBuf == NULL)
			return FALSE;
		INT32 pos = iUnitSize * noRecord1 + pField[noField1].iOffset;
		switch(pField[noField1].iDataType){
			case CDD::DT_BOOL32:
			case CDD::DT_INT32:
			case CDD::DT_FrDataIdx:
			case CDD::DT_FLOAT32:
			case CDD::DT_FLOAT64:
		//	case CDD::DT_KERTIME:
				memcpy(&dataBuf[pos], value1, pField[noField1].iDataSize);
				return TRUE;
			case CDD::DT_VisibleString:
				dataBuf[pos] = 0;
				SYSPROC::StrSafeCat(pField[noField1].iDataSize,  (CHAR *)&dataBuf[pos], (CHAR *)value1);
				return TRUE;
		}
		return FALSE;
	}
};

class CCommonCfgDef
{
public:
	INT32 numTable;	//��������
	INT32  version;  //BYTE --> INT32     modi 0n 2013.10.29
	CTable *pTable;

public: //����ͽ�������

	CCommonCfgDef(INT32 numTable1, BYTE version1=1){
		numTable = numTable1;
		version = version1;
		pTable = new CTable[numTable];
		for(INT32 i=0;i<numTable;i++)
			pTable->SetDefaultValue();
	}

	~CCommonCfgDef(){
		if (pTable != NULL)
			delete[] pTable;		
	};

public:
	//���������ش���,��̬����Լ���ز���ʱ����,������buffer1���ֽ�˳����
	//��ÿ�������������̬buf���й���
	BOOL32 LoadCfgBuf(INT32 cfgDataSize1, BYTE * cfgBuf1){
		INT32 pos=0;
		INT32 len=0;
		if (cfgDataSize1 < sizeof(CCommonCfgHead))
			return FALSE;
		CCommonCfgHead *pCfgHead = (CCommonCfgHead *)cfgBuf1;
		pCfgHead->ResetOrder();

		pos += (sizeof(CCommonCfgHead));
		if ((pos + pCfgHead->size) != cfgDataSize1){
			printf("\nCCommonCfgDef : LoadCfgBuf %x != %x", pos + pCfgHead->size, cfgDataSize1);
			return FALSE;
		}

		for(INT32 i=0;i<pCfgHead->numTable;i++){
			CTableHead *pCfgTableHead = (CTableHead *)&cfgBuf1[pos];  //���������еı�ͷ����
			pCfgTableHead->ResetOrder(pCfgHead->order);
			if ((pCfgTableHead->iUnitSize<0)||(pCfgTableHead->numRecord<0))
				return FALSE;
			
			len = pCfgTableHead->iUnitSize * pCfgTableHead->numRecord;

			if ((pos+(INT32)sizeof(CTableHead)+len) > cfgDataSize1)
				return FALSE;
	
			INT32 j;
			//�ҵ���ͬ�ı��������ݱ��������������,���򰴱�ż���
			for (j=0;j<numTable;j++)
			{
				if (strcmp(pTable[j].szName, pCfgTableHead->szName) ==0)
					break;
			}
			if (j >= numTable)
				j = i; 

			pTable[j].numRecord = pCfgTableHead->numRecord;
			pTable[j].cfgUnitSize = pCfgTableHead->iUnitSize;
			if ((pCfgTableHead->numRecord<=0)||(pCfgTableHead->iUnitSize<=0))
			{
				pTable[j].numRecord = 0;
				pTable[j].cfgDataBuf = NULL;
			}
			else{
				pTable[j].cfgDataBuf = &cfgBuf1[pos];
				pTable[j].ResetDataOrder(pCfgHead->order);
			}

			pos += sizeof(CTableHead) + len;
		}
		return TRUE;
	};

public://����������,��̬
	INT32 GetCfgBufOutputSize(){  //ȡ��̬����ߴ�,���ڷ���buf�ռ䡣����CCommonCfgHead����+CTableHead����+���м�¼��ÿ���ֶ����ݳ���
		INT32 size = sizeof(CCommonCfgHead);
		for(INT32 i=0;i<numTable;i++){
			size += sizeof(CTableHead);
			if (pTable[i].dataBuf == NULL)
				continue;
			size += pTable[i].iUnitSize * pTable[i].numRecord;
		}
		return size;
	}
	INT32 OutputCfgBuf(INT32 &size1, BYTE * buffer1){  //�����̬buf
		INT32 size = GetCfgBufOutputSize();
		if (size > size1)
			return 0;
		CCommonCfgHead *pHead = (CCommonCfgHead *)buffer1;
		pHead->order = BORDER::MY_ORDER;
		pHead->version = version;
		pHead->numTable = numTable;
		pHead->size = size - sizeof(CCommonCfgHead);

		INT32 pos = sizeof(CCommonCfgHead);
		for (INT32 i=0;i<numTable;i++)
			pos += pTable[i].OutputCfgBuf(&buffer1[pos]);
		return pos;
	};
};

#endif
