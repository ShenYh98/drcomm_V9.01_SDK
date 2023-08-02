#include "s_myLcn.h"
#include "LcnProc.h"

INT32 CMyLcn_S::AssembleSendData(UINT8* buf, const INT32 bufSize)
{
	if ( NULL == buf )
	{
		return 0;
	}

	if ( IsACK )
	{
		IsACK = FALSE;

		return AssembleSendACK(buf, bufSize);
	}

	if ( IsCallAllData )
	{
		IsCallAllData = FALSE;
		IsCallYx = TRUE;
		IsCallYc = TRUE;

		return AssembleSendAskAllReturn(buf, bufSize);
	}

	if ( IsCallYx )
	{
		IsCallYx = FALSE;
		DataInfo.DataType |= Fr::FrameType::eFrameYx;

		return AssembleSendAllYxData(buf, bufSize);
	}

	if ( IsCallYc )
	{
		IsCallYc = FALSE;
		DataInfo.DataType |= Fr::FrameType::eFrameYc;

		return AssembleSendAllYcData(buf, bufSize);
	}

	if ( IsCallYm )
	{
		IsCallYm = FALSE;
		DataInfo.DataType |= Fr::FrameType::eFrameYm;

		return AssembleSendAllYmData(buf, bufSize);
	}
}

// ACK报文组装
INT32 CMyLcn_S::AssembleSendACK(UINT8 *buf, const INT32 bufSize)
{
	if ( bufSize < 1 )
	{
		return 0;
	}

	buf[0] = 0xAA;

	return 1;
}

// 全数据响应
INT32 CMyLcn_S::AssembleSendAskAllReturn(UINT8 *buf, const INT32 bufSize)
{
	if ( bufSize < 1 )
	{
		return 0;
	}

	buf[0] = 0x13;

	return 1;
}

// 全遥信报文组装
INT32 CMyLcn_S::AssembleSendAllYxData(UINT8 *buf, const INT32 bufSize)
{
	INT32 i = 0;
	INT32 j = 0;

	YxData yxData;		// 系统的遥信定义详见头文件LcnStructDef.h
	
	buf[j++]	= TYPECODE::ALL_YX;	//报文类型
	buf[j++]	= LOBYTE(iTotalSendYxNum);
	buf[j++]	= HIBYTE(iTotalSendYxNum);

	// 填数据报文，假设遥信数量不超限
	for ( i = 0; i < iTotalSendYxNum; ++i )
	{
		// 依次取1个遥信数据
		if ( !LCN_GetYxData(pIF, i, &yxData) )
		{
			break;
		}

		// 根据转发表的数据来源配置
		// 决定取通道码值还是处理过（如信号取反）的值
		if ( Fr::DataSourceType::ChannelCode == pFtm->yxList[i].typeSource )
		{// 填通道码值
			buf[j] = yxData.iCodeValue;
		}
		else
		{// 填处理值
			buf[j] = yxData.iValue;
		}
	}// End of for

	return j;
}

INT32 CMyLcn_S::AssembleSendAllYcData(UINT8 *buf, const INT32 bufSize)
{
	INT32 i = 0;
	INT32 j = 0;
	FLOAT32 fValue = 0.0f;

	YcData ycData;		// 系统的遥测定义详见头文件LcnStructDef.h

	buf[j++]	= TYPECODE::ALL_YC;	//报文类型
	buf[j++]	= LOBYTE(iTotalSendYcNum);
	buf[j++]	= HIBYTE(iTotalSendYcNum);

	// 填数据报文，假设遥测数量不超限
	for ( i = 0; i < iTotalSendYcNum; ++i )
	{
		// 依次取1个遥测数据
		if ( !LCN_GetYcData(pIF, i, &ycData) )
		{
			break;
		}

		// 根据转发表的数据来源配置选取相应数据
		if ( Fr::DataSourceType::ChannelCode == pFtm->ycList[i].typeSource )
		{// 取通道码值
			if ( BORDER::MY_ORDER != BORDER::OrderLitEndian )
			{// 判断本机字节序为大端在前
				assign_htol(ycData.iCodeValue);
			}

			fValue = (FLOAT32)ycData.iCodeValue;
		}
		else
		{// 取预处理过（如数据经过线性计算）的值
			if ( BORDER::MY_ORDER != BORDER::OrderLitEndian )
			{// 判断本机字节序为大端在前
				assign_htol(ycData.fValue);
			}

			fValue = ycData.fValue;
		}

		memcpy(&buf[j], &fValue, sizeof(FLOAT32));		// 将数据填写到缓存中
		j += sizeof(FLOAT32);
	}// End of for

	return j;
}

INT32 CMyLcn_S::AssembleSendAllYmData(UINT8 *buf, const INT32 bufSize)
{
	INT32 i = 0;
	INT32 j = 0;
	FLOAT32 fValue = 0.0f;

	YmData ymData;		// 系统的遥脉定义详见头文件LcnStructDef.h

	buf[j++]	= TYPECODE::ALL_YM;	//报文类型
	buf[j++]	= LOBYTE(iTotalSendYmNum);
	buf[j++]	= HIBYTE(iTotalSendYmNum);

	// 填数据报文，假设遥测数量不超限
	for ( i = 0; i < iTotalSendYmNum; ++i )
	{
		// 依次取1遥脉数据
		if ( !LCN_GetYmData(pIF, i, &ymData) )
		{
			break;
		}

		// 根据转发表的数据来源配置选取相应数据
		if ( Fr::DataSourceType::ChannelCode == pFtm->ymList[i].typeSource )
		{// 取通道码值
			if ( BORDER::MY_ORDER != BORDER::OrderLitEndian )
			{// 判断本机字节序为大端在前
				assign_htol(ymData.uCodeValue);
			}

			fValue = (FLOAT32)ymData.uCodeValue;
		}
		else
		{// 取预处理过（如数据经过线性计算）的值
			if ( BORDER::MY_ORDER != BORDER::OrderLitEndian )
			{// 判断本机字节序为大端在前
				assign_htol(ymData.fValue);
			}

			fValue = ymData.fValue;
		}

		memcpy(&buf[j], &fValue, sizeof(FLOAT32));		// 将数据填写到缓存中
		j += sizeof(FLOAT32);
	}// End of for

	return j;
}
