#include "c_myLcn.h"

// 解析收到的有效数据包
INT32 CMyLcn_C::ParsePacket(const UINT8* buf, const INT32 len)
{
	UINT8 FunCode;		// 功能码
	INT32 result = -1;

	if ( NULL == buf )
	{// 形参检查
		return -1;
	}

	FunCode = buf[1];
	switch ( FunCode )
	{
	    case 0x35 : 
			DataInfo.DataType |= Fr::FrameType::eFrameYx;		
			result = ProcessGetSN(buf, len);
			break;
		default :
			break;
	}

	return result;  //不能识别的报文
}

// 处理保持寄存器
INT32 CMyLcn_C::ProcessHoldingRegister(const UINT8* buf, const INT32 len)
{
	INT32 i = 0;
	INT32 ByteNum = 0;
	INT16 YcValue = 0;

	if ( NULL == buf )
	{// 形参检查
		return -1;
	}

	ByteNum = buf[2];
	if ( 34 == ByteNum )
	{
		// 处理17个遥测
		for ( i = 0; i < 17; ++i )	
		{
			YcValue = MAKEWORD(buf[i * 2 + 4], buf[i * 2 + 3]);
			LCN_SetYcInteger(pIF, i, YcValue);		// 遥测数据入库
		}// End of for
	}
	else if ( 12 == ByteNum )
	{
		// 处理6个遥测
		for ( i = 0; i < 6; ++i )	
		{
			YcValue = MAKEWORD(buf[i * 2 + 4], buf[i * 2 + 3]);
			LCN_SetYcInteger(pIF, i + 17, YcValue);		// 遥测数据入库
		}// End of for
	}// 无else

	return len;		// 处理完解析的数据包后，返回处理的字节数
}

// 处理输入寄存器
INT32 CMyLcn_C::ProcessInputRegister(const UINT8* buf, const INT32 len)
{
	INT32 i = 0;
	UINT16 TmpL = 0x0000;
	UINT16 TmpH = 0x0000;
	UINT32 TmpValue = 0x00000000L;
	FLOAT32 fValue = 0.0f;
	
	if ( NULL == buf )
	{// 形参检查
		return -1;
	}

	// 处理4个遥脉（电度量）
	for ( i = 0; i < 4; ++i )
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

		LCN_SetYmFloat(pIF, i, fValue);		// 遥脉数据入库
	}// End of for

	return len;		// 处理完解析的数据包后，返回处理的字节数
}

INT32 CMyLcn_C::ProcessGetSN(const UINT8* buf, const INT32 len) {
	DevFeature dev;

	for (int i = 0; i < 20; i++) {
		dev.sn[i] = buf[3+i];
	}
	v_devFeature.push_back(dev);

	return len;
}
