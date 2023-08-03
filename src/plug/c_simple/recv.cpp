#include "c_myLcn.h"

// �����յ�����Ч���ݰ�
INT32 CMyLcn_C::ParsePacket(const UINT8* buf, const INT32 len)
{
	UINT8 FunCode;		// ������
	INT32 result = -1;

	if ( NULL == buf )
	{// �βμ��
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

	return result;  //����ʶ��ı���
}

// �����ּĴ���
INT32 CMyLcn_C::ProcessHoldingRegister(const UINT8* buf, const INT32 len)
{
	INT32 i = 0;
	INT32 ByteNum = 0;
	INT16 YcValue = 0;

	if ( NULL == buf )
	{// �βμ��
		return -1;
	}

	ByteNum = buf[2];
	if ( 34 == ByteNum )
	{
		// ����17��ң��
		for ( i = 0; i < 17; ++i )	
		{
			YcValue = MAKEWORD(buf[i * 2 + 4], buf[i * 2 + 3]);
			LCN_SetYcInteger(pIF, i, YcValue);		// ң���������
		}// End of for
	}
	else if ( 12 == ByteNum )
	{
		// ����6��ң��
		for ( i = 0; i < 6; ++i )	
		{
			YcValue = MAKEWORD(buf[i * 2 + 4], buf[i * 2 + 3]);
			LCN_SetYcInteger(pIF, i + 17, YcValue);		// ң���������
		}// End of for
	}// ��else

	return len;		// ��������������ݰ��󣬷��ش�����ֽ���
}

// ��������Ĵ���
INT32 CMyLcn_C::ProcessInputRegister(const UINT8* buf, const INT32 len)
{
	INT32 i = 0;
	UINT16 TmpL = 0x0000;
	UINT16 TmpH = 0x0000;
	UINT32 TmpValue = 0x00000000L;
	FLOAT32 fValue = 0.0f;
	
	if ( NULL == buf )
	{// �βμ��
		return -1;
	}

	// ����4��ң�����������
	for ( i = 0; i < 4; ++i )
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

		LCN_SetYmFloat(pIF, i, fValue);		// ң���������
	}// End of for

	return len;		// ��������������ݰ��󣬷��ش�����ֽ���
}

INT32 CMyLcn_C::ProcessGetSN(const UINT8* buf, const INT32 len) {
	DevFeature dev;

	for (int i = 0; i < 20; i++) {
		dev.sn[i] = buf[3+i];
	}
	v_devFeature.push_back(dev);

	return len;
}
