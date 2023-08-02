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

// ACK������װ
INT32 CMyLcn_S::AssembleSendACK(UINT8 *buf, const INT32 bufSize)
{
	if ( bufSize < 1 )
	{
		return 0;
	}

	buf[0] = 0xAA;

	return 1;
}

// ȫ������Ӧ
INT32 CMyLcn_S::AssembleSendAskAllReturn(UINT8 *buf, const INT32 bufSize)
{
	if ( bufSize < 1 )
	{
		return 0;
	}

	buf[0] = 0x13;

	return 1;
}

// ȫң�ű�����װ
INT32 CMyLcn_S::AssembleSendAllYxData(UINT8 *buf, const INT32 bufSize)
{
	INT32 i = 0;
	INT32 j = 0;

	YxData yxData;		// ϵͳ��ң�Ŷ������ͷ�ļ�LcnStructDef.h
	
	buf[j++]	= TYPECODE::ALL_YX;	//��������
	buf[j++]	= LOBYTE(iTotalSendYxNum);
	buf[j++]	= HIBYTE(iTotalSendYxNum);

	// �����ݱ��ģ�����ң������������
	for ( i = 0; i < iTotalSendYxNum; ++i )
	{
		// ����ȡ1��ң������
		if ( !LCN_GetYxData(pIF, i, &yxData) )
		{
			break;
		}

		// ����ת�����������Դ����
		// ����ȡͨ����ֵ���Ǵ���������ź�ȡ������ֵ
		if ( Fr::DataSourceType::ChannelCode == pFtm->yxList[i].typeSource )
		{// ��ͨ����ֵ
			buf[j] = yxData.iCodeValue;
		}
		else
		{// ���ֵ
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

	YcData ycData;		// ϵͳ��ң�ⶨ�����ͷ�ļ�LcnStructDef.h

	buf[j++]	= TYPECODE::ALL_YC;	//��������
	buf[j++]	= LOBYTE(iTotalSendYcNum);
	buf[j++]	= HIBYTE(iTotalSendYcNum);

	// �����ݱ��ģ�����ң������������
	for ( i = 0; i < iTotalSendYcNum; ++i )
	{
		// ����ȡ1��ң������
		if ( !LCN_GetYcData(pIF, i, &ycData) )
		{
			break;
		}

		// ����ת�����������Դ����ѡȡ��Ӧ����
		if ( Fr::DataSourceType::ChannelCode == pFtm->ycList[i].typeSource )
		{// ȡͨ����ֵ
			if ( BORDER::MY_ORDER != BORDER::OrderLitEndian )
			{// �жϱ����ֽ���Ϊ�����ǰ
				assign_htol(ycData.iCodeValue);
			}

			fValue = (FLOAT32)ycData.iCodeValue;
		}
		else
		{// ȡԤ������������ݾ������Լ��㣩��ֵ
			if ( BORDER::MY_ORDER != BORDER::OrderLitEndian )
			{// �жϱ����ֽ���Ϊ�����ǰ
				assign_htol(ycData.fValue);
			}

			fValue = ycData.fValue;
		}

		memcpy(&buf[j], &fValue, sizeof(FLOAT32));		// ��������д��������
		j += sizeof(FLOAT32);
	}// End of for

	return j;
}

INT32 CMyLcn_S::AssembleSendAllYmData(UINT8 *buf, const INT32 bufSize)
{
	INT32 i = 0;
	INT32 j = 0;
	FLOAT32 fValue = 0.0f;

	YmData ymData;		// ϵͳ��ң���������ͷ�ļ�LcnStructDef.h

	buf[j++]	= TYPECODE::ALL_YM;	//��������
	buf[j++]	= LOBYTE(iTotalSendYmNum);
	buf[j++]	= HIBYTE(iTotalSendYmNum);

	// �����ݱ��ģ�����ң������������
	for ( i = 0; i < iTotalSendYmNum; ++i )
	{
		// ����ȡ1ң������
		if ( !LCN_GetYmData(pIF, i, &ymData) )
		{
			break;
		}

		// ����ת�����������Դ����ѡȡ��Ӧ����
		if ( Fr::DataSourceType::ChannelCode == pFtm->ymList[i].typeSource )
		{// ȡͨ����ֵ
			if ( BORDER::MY_ORDER != BORDER::OrderLitEndian )
			{// �жϱ����ֽ���Ϊ�����ǰ
				assign_htol(ymData.uCodeValue);
			}

			fValue = (FLOAT32)ymData.uCodeValue;
		}
		else
		{// ȡԤ������������ݾ������Լ��㣩��ֵ
			if ( BORDER::MY_ORDER != BORDER::OrderLitEndian )
			{// �жϱ����ֽ���Ϊ�����ǰ
				assign_htol(ymData.fValue);
			}

			fValue = ymData.fValue;
		}

		memcpy(&buf[j], &fValue, sizeof(FLOAT32));		// ��������д��������
		j += sizeof(FLOAT32);
	}// End of for

	return j;
}
