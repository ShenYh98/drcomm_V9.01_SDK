#include "c_myLcn.h"

// 解析收到的有效数据包
INT32 CMyLcn_C::ParsePacket(const UINT8* buf, const INT32 len)
{
	UINT8 FunCode;		// 功能码

	if ( NULL == buf )
	{// 形参检查
		return -1;
	}

	FunCode = buf[1];
	switch ( FunCode )
	{
	    case 0x01 : 
	    case 0x02 : 
			return ProcessCoil(buf, len);
			break;
	    case 0x03 :
	    case 0x04 :
			return ProcessRegister(buf, len);
			break;
		default :
			break;
	}

	return -1;  //不能识别的报文
}

// 处理线圈
INT32 CMyLcn_C::ProcessCoil(const UINT8* buf, const INT32 len)
{
	INT32 i = 0;
	INT32 j = 0;
	INT32 No = 0;			// 点号
	INT32 DevNo = 0;
	INT32 CfgNo = -1;		// 配置序号
	INT32 YxValue = 0;

	Table1DataStruct *pCfg = NULL;		// 当前条目的结构体指针

	if ( NULL == buf )
	{// 形参检查
		return -1;
	}

	if ( !AddrToDevNo(buf[0], DevNo) )
	{// 找不到匹配的从站
		return -1;
	}

	if ( !GetCfgNo(1, buf[2], CfgNo) )
	{// 找不到匹配的配置条目
		return -1;
	}

	pCfg = &pParam1[CfgNo];

	for ( j = 0; j < buf[2]; ++j )
	{
		for ( i = 0; i < 8; ++i )
		{
			if ( ( j * 8 + i ) >= pCfg->QueryNum )
			{// 线圈数量已经越限
				return len;		// 处理完解析的数据包后，返回处理的字节数
			}

			YxValue = ( buf[j + 3] >> i ) & 0x01;
			No = TmnlDataList[DevNo].YxOffset + pCfg->Offset + j * 8 + i;	// 计算该遥信在整个节点实时数据库中的偏移量
			LCN_SetYx(pIF, No, YxValue);	
		}// End of for(i)
	}// End of for(j)

	return len;		// 处理完解析的数据包后，返回处理的字节数
}

// 处理寄存器
INT32 CMyLcn_C::ProcessRegister(const UINT8* buf, const INT32 len)
{
	INT32 i = 0;
	INT32 ByteNum = 0;
	INT32 Type = 0;		// 帧类型
	INT32 No = 0;			// 点号
	INT32 DevNo = 0;
	INT32 CfgNo = -1;		// 配置序号
	INT16 YcValue = 0;
	UINT16 TmpL = 0x0000;
	UINT16 TmpH = 0x0000;
	UINT32 TmpValue = 0x00000000L;
	FLOAT32 fValue = 0.0f;

	Table1DataStruct *pCfg = NULL;		// 当前条目的结构体指针

	if ( NULL == buf )
	{// 形参检查
		return -1;
	}

	if ( 0x03 == buf[1] )
	{// 遥测
		Type = 2;
	}
	else if ( 0x04 == buf[1] )
	{// 遥脉
		Type = 3;
	}

	if ( !AddrToDevNo(buf[0], DevNo) )
	{// 找不到匹配的从站
		return -1;
	}

	ByteNum = buf[2];
	if ( !GetCfgNo(Type, ByteNum, CfgNo) )
	{//  找不到匹配的配置条目
		return -1;
	}

	pCfg = &pParam1[CfgNo];

	if ( 2 == pCfg->Type )
	{// 处理遥测
		for ( i = 0; i < pCfg->QueryNum; ++i )	
		{
			YcValue = MAKEWORD(buf[i * 2 + 4], buf[i * 2 + 3]);
			LCN_SetYcInteger(pIF, TmnlDataList[DevNo].YcOffset + pCfg->Offset + i, YcValue);		// 遥测数据入库
		}// End of for
	}
	else if ( 3 == pCfg->Type )
	{// 处理遥脉，假设每个遥脉占2个寄存器
		for ( i = 0; i < pCfg->QueryNum / 2; ++i )	
		{
			// 根据字节序合理取值，本例中采用的字节序是LH LL HH HL
			TmpL = MAKEWORD(buf[i * 4 + 4], buf[i * 4 + 3]);
			TmpH = MAKEWORD(buf[i * 4 + 6], buf[i * 4 + 5]);
			TmpValue = MAKELONG(TmpL, TmpH);
			if (BORDER::MY_ORDER != BORDER::OrderLitEndian)
			{//判断本机字节序是否为小端在前
				assign_htol(TmpValue);
			}

			// 收到的数是UINT32，但是入库的数必须转换成float
			fValue = (FLOAT32)TmpValue;

			LCN_SetYmFloat(pIF, TmnlDataList[DevNo].YmOffset + pCfg->Offset + i, fValue);		// 遥脉数据入库
		}// End of for
	}// 无else

	return len;		// 处理完解析的数据包后，返回处理的字节数
}

// @brief 通过类型和查询数量得到配置的序号，序号存放在No里
// @param Type	接收的类型
// @param Bytes	接收的字节数
// @param &No	找到的序号
// @retval	TRUE：找到对应的序号
//				FALSE：找不到对应的序号
BOOL32 CMyLcn_C::GetCfgNo(const INT32 Type, const INT32 Bytes, INT32 &No)
{
	INT32 i = 0;
	INT32 CalcBytes = 0;

	for ( i = 0; i < numParam1; ++i )
	{
		if ( 1 == pParam1[i].FunCode || 2 == pParam1[i].FunCode )
		{// 01和02功能码，每查询8个线圈，响应报文计算1个字节，最后不足8个，增加1个字节
			CalcBytes = pParam1[i].QueryNum / 8;
			if ( ( pParam1[i].QueryNum % 8 ) > 0 )
			{
				++CalcBytes;
			}
		}
		else if ( 3 == pParam1[i].FunCode || 4 == pParam1[i].FunCode )
		{// 03 和04功能码，每查询1个寄存器，响应报文计算2个字节
			CalcBytes = pParam1[i].QueryNum * 2;
		}

		if ( pParam1[i].Type == Type && CalcBytes == Bytes )
		{
			No = i;
			return TRUE;
		}
	}// End of for

	return FALSE;
}

// 将收到的装置地址转换成装置序号
// 返回值:	TRUE：找到对应的序号，填写在引用参数DevNo里
//					FALSE：没找到
BOOL32 CMyLcn_C::AddrToDevNo(const INT32 Addr, INT32 &DevNo)
{
	INT32 i = 0;

	for ( i = 0; i < DevNum; ++i )
	{
		if ( Addr == pParam0[i].DevAddr )
		{
			DevNo = i;
			return TRUE;
		}
	}// End of for

	return FALSE;
}
