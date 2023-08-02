#include "c_myLcn.h"

// �����յ�����Ч���ݰ�
INT32 CMyLcn_C::ParsePacket(const UINT8* buf, const INT32 len)
{
	UINT8 FunCode;		// ������

	if ( NULL == buf )
	{// �βμ��
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

	return -1;  //����ʶ��ı���
}

// ������Ȧ
INT32 CMyLcn_C::ProcessCoil(const UINT8* buf, const INT32 len)
{
	INT32 i = 0;
	INT32 j = 0;
	INT32 No = 0;			// ���
	INT32 DevNo = 0;
	INT32 CfgNo = -1;		// �������
	INT32 YxValue = 0;

	Table1DataStruct *pCfg = NULL;		// ��ǰ��Ŀ�Ľṹ��ָ��

	if ( NULL == buf )
	{// �βμ��
		return -1;
	}

	if ( !AddrToDevNo(buf[0], DevNo) )
	{// �Ҳ���ƥ��Ĵ�վ
		return -1;
	}

	if ( !GetCfgNo(1, buf[2], CfgNo) )
	{// �Ҳ���ƥ���������Ŀ
		return -1;
	}

	pCfg = &pParam1[CfgNo];

	for ( j = 0; j < buf[2]; ++j )
	{
		for ( i = 0; i < 8; ++i )
		{
			if ( ( j * 8 + i ) >= pCfg->QueryNum )
			{// ��Ȧ�����Ѿ�Խ��
				return len;		// ��������������ݰ��󣬷��ش�����ֽ���
			}

			YxValue = ( buf[j + 3] >> i ) & 0x01;
			No = TmnlDataList[DevNo].YxOffset + pCfg->Offset + j * 8 + i;	// �����ң���������ڵ�ʵʱ���ݿ��е�ƫ����
			LCN_SetYx(pIF, No, YxValue);	
		}// End of for(i)
	}// End of for(j)

	return len;		// ��������������ݰ��󣬷��ش�����ֽ���
}

// ����Ĵ���
INT32 CMyLcn_C::ProcessRegister(const UINT8* buf, const INT32 len)
{
	INT32 i = 0;
	INT32 ByteNum = 0;
	INT32 Type = 0;		// ֡����
	INT32 No = 0;			// ���
	INT32 DevNo = 0;
	INT32 CfgNo = -1;		// �������
	INT16 YcValue = 0;
	UINT16 TmpL = 0x0000;
	UINT16 TmpH = 0x0000;
	UINT32 TmpValue = 0x00000000L;
	FLOAT32 fValue = 0.0f;

	Table1DataStruct *pCfg = NULL;		// ��ǰ��Ŀ�Ľṹ��ָ��

	if ( NULL == buf )
	{// �βμ��
		return -1;
	}

	if ( 0x03 == buf[1] )
	{// ң��
		Type = 2;
	}
	else if ( 0x04 == buf[1] )
	{// ң��
		Type = 3;
	}

	if ( !AddrToDevNo(buf[0], DevNo) )
	{// �Ҳ���ƥ��Ĵ�վ
		return -1;
	}

	ByteNum = buf[2];
	if ( !GetCfgNo(Type, ByteNum, CfgNo) )
	{//  �Ҳ���ƥ���������Ŀ
		return -1;
	}

	pCfg = &pParam1[CfgNo];

	if ( 2 == pCfg->Type )
	{// ����ң��
		for ( i = 0; i < pCfg->QueryNum; ++i )	
		{
			YcValue = MAKEWORD(buf[i * 2 + 4], buf[i * 2 + 3]);
			LCN_SetYcInteger(pIF, TmnlDataList[DevNo].YcOffset + pCfg->Offset + i, YcValue);		// ң���������
		}// End of for
	}
	else if ( 3 == pCfg->Type )
	{// ����ң��������ÿ��ң��ռ2���Ĵ���
		for ( i = 0; i < pCfg->QueryNum / 2; ++i )	
		{
			// �����ֽ������ȡֵ�������в��õ��ֽ�����LH LL HH HL
			TmpL = MAKEWORD(buf[i * 4 + 4], buf[i * 4 + 3]);
			TmpH = MAKEWORD(buf[i * 4 + 6], buf[i * 4 + 5]);
			TmpValue = MAKELONG(TmpL, TmpH);
			if (BORDER::MY_ORDER != BORDER::OrderLitEndian)
			{//�жϱ����ֽ����Ƿ�ΪС����ǰ
				assign_htol(TmpValue);
			}

			// �յ�������UINT32����������������ת����float
			fValue = (FLOAT32)TmpValue;

			LCN_SetYmFloat(pIF, TmnlDataList[DevNo].YmOffset + pCfg->Offset + i, fValue);		// ң���������
		}// End of for
	}// ��else

	return len;		// ��������������ݰ��󣬷��ش�����ֽ���
}

// @brief ͨ�����ͺͲ�ѯ�����õ����õ���ţ���Ŵ����No��
// @param Type	���յ�����
// @param Bytes	���յ��ֽ���
// @param &No	�ҵ������
// @retval	TRUE���ҵ���Ӧ�����
//				FALSE���Ҳ�����Ӧ�����
BOOL32 CMyLcn_C::GetCfgNo(const INT32 Type, const INT32 Bytes, INT32 &No)
{
	INT32 i = 0;
	INT32 CalcBytes = 0;

	for ( i = 0; i < numParam1; ++i )
	{
		if ( 1 == pParam1[i].FunCode || 2 == pParam1[i].FunCode )
		{// 01��02�����룬ÿ��ѯ8����Ȧ����Ӧ���ļ���1���ֽڣ������8��������1���ֽ�
			CalcBytes = pParam1[i].QueryNum / 8;
			if ( ( pParam1[i].QueryNum % 8 ) > 0 )
			{
				++CalcBytes;
			}
		}
		else if ( 3 == pParam1[i].FunCode || 4 == pParam1[i].FunCode )
		{// 03 ��04�����룬ÿ��ѯ1���Ĵ�������Ӧ���ļ���2���ֽ�
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

// ���յ���װ�õ�ַת����װ�����
// ����ֵ:	TRUE���ҵ���Ӧ����ţ���д�����ò���DevNo��
//					FALSE��û�ҵ�
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
