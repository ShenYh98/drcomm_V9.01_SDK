#include "c_myLcn.h"

INT32 CMyLcn_C::AssembleSendData(UINT8 *buf, const INT32 bufferSize)
{
	if ( NULL == buf )
	{// �βμ��
		return -1;
	}

	if ( DevNum <= 0 || numParam1 <= 0 )
	{// ������Ŀ�����
		return -1;
	}

	// ��ͨ��ѯ
	if ( ++SendQueryNo >= numParam1 )
	{//numParam1Ϊ��1�ļ�¼������Ҳ�������֡��
		SendQueryNo = 0;
	
		if ( ++CurrDevNo >= DevNum )
		{
			CurrDevNo = 0;
		}
	}

	return AssembleNoramlQuery(buf, bufferSize);
}

// ��ѯ����    
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
		return 0;		// ���Ͳ�ƥ��
		break;
	}// End of switch

	buf[i++] = (UINT8)pParam0[CurrDevNo].DevAddr;			// ��վ��ַ
	buf[i++] = FunCode;					// ������
	buf[i++] = HIBYTE(StartAddr);	// ��ʼ��ַ���ֽ�
	buf[i++] = LOBYTE(StartAddr);	// ��ʼ��ַ���ֽ�
	buf[i++] = HIBYTE(QueryNum);	// ��ѯ�������ֽ�
	buf[i++] = LOBYTE(QueryNum);	// ��ѯ�������ֽ�

	ChkCRC16 = CRC16(buf, i);

	buf[i++] = LOBYTE(ChkCRC16);	// crcУ����ֽ�
	buf[i++] = HIBYTE(ChkCRC16);	// crcУ����ֽ�

	return i;
}
