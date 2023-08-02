#include "c_myLcn.h"

//构造和析构
CMyLcn_C::CMyLcn_C(void){}

CMyLcn_C::~CMyLcn_C(void){}

// 节点初始化
void CMyLcn_C::V_NodeInit(void *pIF1)
{
	pIF = pIF1;		//保存系统的操作接口

	PTOTHERINFO pti;
	LCN_GetProtocolIdentify(pIF, &pti); //获得规约基本配置信息

	// 这部分代码是为了调试时打印准备的，如果做国外项目就必须注意这点
	// 国内项目显示都是中文，英文显示就没有必要
	if (pti.flgCfg & PTOTHERINFO::CBitEnglishDebug)
		isEnglishDebug = TRUE;
	else 
		isEnglishDebug = FALSE;

	//初始化运行数据
	nowPulsSec = LCN_GetSystemPuls(pIF);
	lastSetTimePulsSec = nowPulsSec;
	SendQueryNo = -1;		// 初始化为-1，第一次运行就会自加为0
	CurrDevNo = 0;
	DevNum = -1;

	// 读取通用配置里的参数
	INT32 size;
	INT8 * buf = LCN_GetZtBuf(pIF, &size);
	pti.pCommonCfgDef->LoadCfgBuf(size, (BYTE *)buf);  //加载组态参数

	//加载表0的组态参数
	pParam0 = (Table0DataStruct *)(pti.pCommonCfgDef)->pTable[0].ReadDynamicTable(sizeof(Table0DataStruct), &DevNum);

	//加载表1的组态参数
	pParam1 = (Table1DataStruct *)(pti.pCommonCfgDef)->pTable[1].ReadDynamicTable(sizeof(Table1DataStruct), &numParam1);

	////加载表1的组态参数
	//pParam2 = (Table1DataStruct *)(pti.pCommonCfgDef)->pTable[2].ReadDynamicTable(sizeof(Table1DataStruct), &numParam2);

	GetCfgData();
}

void CMyLcn_C::GetCfgData()
{
	INT32 i = 0;
	INT32 TmnlYxNum = 0;
	INT32 TmnlYcNum = 0;
	INT32 TmnlYmNum = 0;

	if ( DevNum <= 0 || numParam1 <= 0 )
	{// 终端数量或查询数量没配置
		return;
	}

	// 计算每个终端的数据数量
	for ( i = 0; i < numParam1; ++i )
	{
		if ( 1 == pParam1[i].Type )
		{// 遥信
			TmnlYxNum += pParam1[i].QueryNum;	// 假设每个线圈就是一个遥信值
		}
		else if ( 2 == pParam1[i].Type )
		{// 遥测
			TmnlYcNum += pParam1[i].QueryNum;	// 假设每个寄存器就是一个遥测值
		}
		else if ( 3 == pParam1[i].Type )
		{// 遥脉
			TmnlYmNum += pParam1[i].QueryNum / 2;	// 假设2个寄存器就是一个遥脉值
		}
	}// End of for

	TmnlDataList = new TmnlDataStruct[DevNum];

	// 第1个设备特殊处理
	TmnlDataList[0].YxNum = TmnlYxNum;
	TmnlDataList[0].YcNum = TmnlYcNum;
	TmnlDataList[0].YmNum = TmnlYmNum;
	TmnlDataList[0].YxOffset = 0;
	TmnlDataList[0].YcOffset = 0;
	TmnlDataList[0].YmOffset = 0;

	// 第1个之后的所有设备
	for ( i = 1; i < DevNum; ++i )
	{
		TmnlDataList[i].YxNum = TmnlYxNum;
		TmnlDataList[i].YcNum = TmnlYcNum;
		TmnlDataList[i].YmNum = TmnlYmNum;
		TmnlDataList[i].YxOffset = TmnlDataList[i - 1].YxOffset + TmnlDataList[i - 1].YxNum;
		TmnlDataList[i].YcOffset = TmnlDataList[i - 1].YcOffset + TmnlDataList[i - 1].YcNum;
		TmnlDataList[i].YmOffset = TmnlDataList[i - 1].YmOffset + TmnlDataList[i - 1].YmNum;
	}// End of for
}

// 节点被销毁
void CMyLcn_C::V_NodeDestroy(){}

// 接收处理
DEALDATAINFO CMyLcn_C::V_ReceiveProc(const UINT8* buf,const INT32 bytes)
{
	UINT8 *pBuf = NULL;

	printf("V_ReceiveProc\n");
	DataInfo.SetDefault();

	INT32 i = 0;
	UINT8 FunCode = 0x00;
	UINT16 RChkCRC16 = 0x0000;	// 接收CRC16校验码
	UINT16 CChkCRC16 = 0x0000;	// 计算CRC16校验码
	UINT32 Len = 0;		//报文长度

	for ( i = 0; i < bytes; ++i )
	{
		pBuf = (UINT8 *)&buf[i];
		if ( pBuf[0] != 0x01 )// 第1个字节是从站地址
		{
			continue;
		}

		FunCode = pBuf[1];
		if ( 0x80 == ( FunCode & 0x80 ) )
		{// 返回异常码
			// 举例：01 82 01 81 60
			RChkCRC16 = MAKEWORD(pBuf[3], pBuf[4]);		// 接收的CRC值从固定位置取，字节序低前高后 L H
			CChkCRC16 = CRC16(pBuf, 3);			// 计算的CRC值
			if ( RChkCRC16 == CChkCRC16 )
			{// 找到一帧完整的报文，但是返回的是异常信息
				// 对异常码进行处理
				i += 5;		// 设置报文处理的长度
				LCN_SetRecvGoodPackage(pIF, 1);
				DataInfo.Bytes = i + 5;			//设置报文处理的长度

				return DataInfo;
			}
		}

		if ( 01 == FunCode || 02 == FunCode || 03 == FunCode || 04 == FunCode )
		{// 正常的查询返回报文
			Len = pBuf[2];		// 第3个字节是接收数据长度
			RChkCRC16 = MAKEWORD(pBuf[Len + 3], pBuf[Len + 4]);
			CChkCRC16 = CRC16(pBuf, Len + 3);
			if ( RChkCRC16 == CChkCRC16 )
			{// 找到一帧完整的报文
				if ( ParsePacket(pBuf, Len) < 0 )  //解析1个完整包的报文
				{
					LCN_SetRecvBadPackage(pIF, 1); //坏包数加1
				}
				else
				{
					LCN_SetRecvGoodPackage(pIF, 1);  //解析包成功，好包数加1
					DataInfo.Bytes = i + Len + 8;			//设置报文处理的长度

					return DataInfo;
				}
			}
		}
	}// End of for

	DataInfo.Bytes = 0;			//设置报文处理的长度

	return DataInfo;
}


// 发送处理
DEALDATAINFO CMyLcn_C::V_SendProc(UINT8* buffer,const INT32 bufferSize)
{
	DataInfo.SetDefault();

	printf("V_SendProc\n");
	//printf("Hello, world!\n");
	DataInfo.Bytes = AssembleSendData(buffer, bufferSize);

	if ( DataInfo.Bytes > 0 )
	{//如果是问答式规约，发送需要设置DataInfo.isSyncChar=TRUE，来通知系统清除上次收到的缓冲数据
		DataInfo.isSyncChar = TRUE;
	}

	return DataInfo;
}

//通道重置
INT32 CMyLcn_C::V_ChannelReset()
{
	//初始化运行数据
	nowPulsSec = LCN_GetSystemPuls(pIF);
	lastSetTimePulsSec = nowPulsSec;
	SendQueryNo = -1;		// 初始化为-1，第一次运行就会自加为0

	return 0;
}

// 每秒处理
INT32 CMyLcn_C::V_EverySecondProc(INT32 systemPlus1)
{
	return 0;
}

//CRC校验码公式
UINT16 CMyLcn_C::CRC16(UINT8* pDataBuf, INT32 DataLen)
{
	INT32 i = 0;
	INT32 j = 0;
	UINT16 crc = 0xFFFF;		// 赋初值

	for ( i = 0; i < DataLen; i++ )
	{
		crc = crc ^ (UINT16)pDataBuf[i];
		for ( j = 0; j < 8; j++ )
		{
			if ( ( crc & 0x0001 ) != 0 )
			{
				crc = ( crc >> 1 ) ^ 0xA001;		// CRC校验特征公式
			}
			else
			{
				crc = crc >> 1;
			}
		}// End of for(j)
	}// End of for(i)

	return crc;
}
