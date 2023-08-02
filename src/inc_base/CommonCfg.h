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
#include <algorithm>  //sort的定义
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

#define SOCKET INT32
#endif

/*
点击规约组态，如果是通用组态，系统会自动弹出1个对话框组态界面，
该组态界面有确认、取消按钮，同时有一个带多属性页界面，每个属性页对应一个表配置。
每个属性页有两个表格，多维表格和两维表格。
多维表格表头分别是序号、具体表的每个字段名(对于NS2000系统的域)，表体每一行都是1个记录定义，选择某个记录，
两维表格的第一维显示这个记录的各个字段名，第二维显示对应字段的值
多维表格的记录可多选，鼠标右键操作对选中的记录可以复制、增加、删除、插入、上移、下移

如果某类Table的记录数量>0,表示记录数为固定值，因Table记录总数不变，因此不提供对记录的增加、插入、删除操作,保留记录的复制、上移、下移操作
注：属性页的界面风格也可以考虑用树来表示，可参见NS3000组态界面，每个树的叶子就是一个表定义。

点击确认，根据页面的配置，生成组态参数buf
组态参数buf结构定义：
字节顺序（1字节），版本号（1字节），Itable数量（2字节），总buf长度（4字节，不含头及本身长度）--》头(CCommonCfgHead),均为整数定义
第0号Table定义：
	0Table的CTableHead + 所有记录数据
	CTableHead包括Table字段个数（4字节）,单个记录长度（4字节），记录个数（4字节）,
。。。
第n号Table定义：
	n号Table的CTableHead + 所有记录数据


使用：
	规约加载时自动生成参数组态方式定义
	根据Buf，生成各个组态实例数据
*/

struct CIntValue{
	INT32 iValue;
	char  szValueName[Fr::NAME_LENGTH];
};

namespace CDD{
	static const INT32 DT_VisibleString	= BDT::VisibleString;	//普通字符串
//	static const INT32 DT_KERTIME		= BDT::INT_64U	;	//见KERTIME定义,不考虑32位的时间,均用KERTIME
	static const INT32 DT_INT32			= BDT::INT_32	;  //组态数据不考虑小于4个字节的整数
	static const INT32 DT_BOOL32		= BDT::BOOL_32	;
	static const INT32 DT_FLOAT32		= BDT::FLOAT_32	;
	static const INT32 DT_FLOAT64		= BDT::FLOAT_64	;
	static const INT32 DT_FrDataIdx		= BDT::KEYID	;  //数据索引，长度为4个字节，数据结构定义见FrDataIdx

	//整数配置
    const INT32 eCfgNormal			=  0; //普通
    const INT32 eCfgHex				=  1; //16进制整数
    const INT32 eCfg32BitValue		= 26; //32位的标志位设置
    const INT32 eCfgIpAddress		= 12; //Ip地址
    const INT32 eCfgRGB				= 13; //RGB颜色
    const INT32 eCfgDropList		=  4; //无限定的其它数据检索
	//字符串配置
    const INT32 eCfgPassWord		=  3; //口令配置
	const INT32 eCfgPrinter			= 23; //打印机名
    const INT32 eCfgFileSelect		= 41; //文件选择
};

//字段数据的通用组态定义
struct CField
{
public:
	char	szName[Fr::NAME_LENGTH];	//字段名称
	INT32	iDataType;		//字段数据类型,CDD::DT_
	INT32	iDataSize;		//字段数据长度，表示实际占用的字节数
	INT32	iCfgType;		//字段数据组态方式（例如以十进制、十六进制显示）,CDD::eCfg
	FLOAT32 fDefaultValue;	//缺省值
	FLOAT32 fMaxValue;		//最大值
	FLOAT32 fMinValue;		//最小值
	INT32	lenDecimal;		//显示小数位数
	INT32	intValueNum;	//整数值列表数量
	CIntValue *pIntValueList;//整数值列表,如果是非整数值，可将不同含义的值也用整数常量表示
	INT32	iOffset;		//在记录中的偏移位置,自动计算得到

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
	
	//重置数据字节顺序，数据组态buf的读写之前都要调用该函数
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
			if (iCfgType == CDD::eCfgIpAddress){  //IPaddress已经被组态程序转化为按高字节存放的格式，不用再转换字节顺序
			}
			else if (iDataType == CDD::DT_FrDataIdx){  //IPaddress已经被组态程序转化为按高字节存放的格式，不用再转换字节顺序
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
	BYTE order;			//字节顺序（1字节）
	BYTE version;		//版本号（1字节）
	UINT16 numTable;	//表数量（2字节），
	INT32 size;			//总buf长度（4字节，不含头及本身长度）
	void ResetOrder(){
		if (order == BORDER::MY_ORDER)
			return;
		assign_htol(numTable);
		assign_htol(size);
	}
};

class CTableHead{
public:
	char  szName[Fr::NAME_LENGTH];	//表名称
	INT32 numField;		//记录字段个数（4字节）
	INT32 iUnitSize;	//单个记录长度（4字节）
	INT32 numRecord;		//记录个数（4字节）
public:
	void ResetOrder(BYTE order1){
		if (order1 == BORDER::MY_ORDER)
			return;
		assign_htol(numField);
		assign_htol(iUnitSize);
		assign_htol(numRecord);
	}
};


//表定义
class CTable{
public:
	char	szName[Fr::NAME_LENGTH];	//表名称
	INT32	numField;	//字段的数量
	CField *pField;//每个数据的通用组态定义
	INT32	iUnitSize;   //单记录大小，计算得到
	INT32	numFixRecord;  //固定记录数量，如果为0，表示记录数不限制
	INT32	numRecord;

	BYTE *  cfgDataBuf;  //原组态配置的参数，含表头,只是一个指针不分配空间
	BYTE *  cfgTmpBuf;	//原纪录与保存纪录大小不一致时，用于升级的临时分配空间
	INT32	cfgUnitSize;   //原组态配置的单记录大小
	BYTE *  dataBuf;  //组态用，新组态生成的buf，含表头,分配空间

public:
	//numFixRecord1==0表示记录数不限
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

public:  //设置数据定义的函数
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

	//重置数据字节顺序，数据组态buf的读之前都要调用该函数,组态buf结构可能比现有的小
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

public://组态、规约用
	INT32 GetRecordNum(){ //从cfgDataBuf获取数据,规约用
		if (cfgDataBuf == NULL)
			return 0;
		CTableHead *pHead = (CTableHead *)cfgDataBuf;
		return pHead->numRecord; 
	}

	//返回记录数量
	//GetDynamicTable 与 ReadDynamicTable区别在于，ReadDynamicTable是重新分配空间，
	//GetDynamicTable是使用原有的配置空间，如果单元大小不一致，则仍重新分配空间，即等同ReadDynamicTable
	//GetDynamicTable函数可以帮助CreateNodeRealTimeData函数修改关联配置信息
	BYTE * GetDynamicTable(INT32 iUnitSize1, INT32 * pRecordNum1){ //从cfgDataBuf获取数据,规约用
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

	//返回记录数量
	BYTE * ReadDynamicTable(INT32 iUnitSize1, INT32 * pRecordNum1){ //从cfgDataBuf获取数据,规约用
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
	//读静态表数据
	//返回读出记录数量
	INT32 ReadStaticTable(INT32 iUnitSize1, void * buffer1, INT32 recordNum1){ //从cfgDataBuf获取数据,规约用
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
	void ReadData(INT32 noRecord1, INT32 noField1, INT32 sizeData1, BYTE *buffer1){  //从cfgDataBuf获取数据,组态用
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

public:  //仅组态用
	INT32 OutputCfgBuf(BYTE * buffer1){  //输出组态buf
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
	BOOL32 WriteData(INT32 noRecord1, INT32 noField1, void * value1){ //设置数据,对于整数列表数据，传递的是列表中的名称,实际存储的仍是整数
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
	INT32 numTable;	//表数量，
	INT32  version;  //BYTE --> INT32     modi 0n 2013.10.29
	CTable *pTable;

public: //构造和解析函数

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
	//缓冲区加载处理,组态、规约加载参数时调用,程序会对buffer1作字节顺序处理
	//将每个表的数据与组态buf进行关联
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
			CTableHead *pCfgTableHead = (CTableHead *)&cfgBuf1[pos];  //配置数据中的表头定义
			pCfgTableHead->ResetOrder(pCfgHead->order);
			if ((pCfgTableHead->iUnitSize<0)||(pCfgTableHead->numRecord<0))
				return FALSE;
			
			len = pCfgTableHead->iUnitSize * pCfgTableHead->numRecord;

			if ((pos+(INT32)sizeof(CTableHead)+len) > cfgDataSize1)
				return FALSE;
	
			INT32 j;
			//找到相同的表名，根据表名加载相关数据,否则按表号加载
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

public://缓冲区处理,组态
	INT32 GetCfgBufOutputSize(){  //取组态输出尺寸,便于分配buf空间。包括CCommonCfgHead长度+CTableHead长度+所有记录的每个字段数据长度
		INT32 size = sizeof(CCommonCfgHead);
		for(INT32 i=0;i<numTable;i++){
			size += sizeof(CTableHead);
			if (pTable[i].dataBuf == NULL)
				continue;
			size += pTable[i].iUnitSize * pTable[i].numRecord;
		}
		return size;
	}
	INT32 OutputCfgBuf(INT32 &size1, BYTE * buffer1){  //输出组态buf
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
