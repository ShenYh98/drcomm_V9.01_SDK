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
	SendIDTaskNo = 0;		// 初始化为-1，第一次运行就会自加为0
	SendTaskNo = 0;
	IsRecv = false;
	IDtotal = 0x00;
	v_devFeature.clear();
	start_time = std::clock();

	/////////////////////////////////////////////////////////////////////////////////////
	// 在这里读取通用配置里的参数，将参数带入程序中运行。
	/////////////////////////////////////////////////////////////////////////////////////
}

// 节点被销毁
void CMyLcn_C::V_NodeDestroy(){}

// 接收处理
DEALDATAINFO CMyLcn_C::V_ReceiveProc(const UINT8* buf,const INT32 bytes)
{
	UINT8 *pBuf = NULL;

	DataInfo.SetDefault();

	INT32 i = 0;
	UINT8 FunCode = 0x00;
	UINT16 RChkCRC16 = 0x0000;	// 接收CRC16校验码
	UINT16 CChkCRC16 = 0x0000;	// 计算CRC16校验码
	UINT32 Len = 0;		//报文长度

	pBuf = (UINT8 *)&buf[i];

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

	if ( 0x03 == FunCode || 0x04 == FunCode || 0x35 == FunCode )
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
				IsRecv = true;

				return DataInfo;
			}
		}
	}

	if ( 0x39 == FunCode )
	{// 0x39分配id，如果分配成功则回复报文，不用处理
		Len = pBuf[2];		// 第3个字节是接收数据长度
		RChkCRC16 = MAKEWORD(pBuf[6], pBuf[7]);
		CChkCRC16 = CRC16(pBuf, 6);
		if ( RChkCRC16 == CChkCRC16 )
		{
			LCN_SetRecvGoodPackage(pIF, 1);
			DataInfo.Bytes = i + 8;			//设置报文处理的长度
			IsRecv = true;

			return DataInfo;
		}
	}

	DataInfo.Bytes = 0;			//设置报文处理的长度

	return DataInfo;
}

// 发送处理
DEALDATAINFO CMyLcn_C::V_SendProc(UINT8* buffer,const INT32 bufferSize)
{
	DataInfo.SetDefault();

	std::clock_t current_time = std::clock();  // 获取当前时钟时间
	double elapsed_seconds = (current_time - start_time) / (double)CLOCKS_PER_SEC;  // 计算经过的秒数

	if (elapsed_seconds >= 3.0) {
		DataInfo.Bytes = AssembleSendData(buffer, bufferSize);

		if ( DataInfo.Bytes > 0 )
		{//如果是问答式规约，发送需要设置DataInfo.isSyncChar=TRUE，来通知系统清除上次收到的缓冲数据
			DataInfo.isSyncChar = TRUE;
		}

		start_time = std::clock();  // 重置计时器
	}

	return DataInfo;
}

//通道重置
INT32 CMyLcn_C::V_ChannelReset()
{
	//初始化运行数据
	nowPulsSec = LCN_GetSystemPuls(pIF);
	lastSetTimePulsSec = nowPulsSec;
	SendIDTaskNo = 0;		// 初始化为-1，第一次运行就会自加为0
	SendTaskNo = 0;
	IDtotal = 0x00;
	IsRecv = false;
	v_devFeature.clear();
	start_time = std::clock();

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
