#include "c_myLcn.h"

INT32 CMyLcn_C::AssembleSendData(UINT8 *buf, const INT32 bufferSize)
{
	if ( NULL == buf )
	{// 形参检查
		return -1;
	}

	if ( DevNum <= 0 || numParam1 <= 0 )
	{// 配置条目数检查
		return -1;
	}

	// 普通查询
	if ( ++SendQueryNo >= numParam1 )
	{//numParam1为表1的记录条数，也就是最大帧数
		SendQueryNo = 0;
	
		if ( ++CurrDevNo >= DevNum )
		{
			CurrDevNo = 0;
		}
	}

	return AssembleNoramlQuery(buf, bufferSize);
}

// 查询报文    
INT32 CMyLcn_C::AssembleNoramlQuery(UINT8 *buf, const INT32 bufferSize)
{
	INT32 i = 0;
	UINT16 ChkCRC16	= 0x0000;
	UINT16 StartAddr	= LOWORD(pParam1[SendQueryNo].StartAddr);
	UINT16 QueryNum	= LOWORD(pParam1[SendQueryNo].QueryNum);
	UINT8 FunCode = (UINT8)pParam1[SendQueryNo].FunCode;

	switch ( pParam1[SendQueryNo].Type )
	{
	case 1 :
		DataInfo.DataType |= Fr::FrameType::eFrameYx;
		break;
	case 2 :
		DataInfo.DataType |= Fr::FrameType::eFrameYc;
		break;
	case 3 :
		DataInfo.DataType |= Fr::FrameType::eFrameYm;
		break;
	default:
		return 0;		// 类型不匹配
		break;
	}// End of switch

	buf[i++] = (UINT8)pParam0[CurrDevNo].DevAddr;			// 从站地址
	buf[i++] = FunCode;					// 功能码
	buf[i++] = HIBYTE(StartAddr);	// 起始地址高字节
	buf[i++] = LOBYTE(StartAddr);	// 起始地址低字节
	buf[i++] = HIBYTE(QueryNum);	// 查询数量高字节
	buf[i++] = LOBYTE(QueryNum);	// 查询数量低字节

	ChkCRC16 = CRC16(buf, i);

	buf[i++] = LOBYTE(ChkCRC16);	// crc校验低字节
	buf[i++] = HIBYTE(ChkCRC16);	// crc校验高字节

	return i;
}
