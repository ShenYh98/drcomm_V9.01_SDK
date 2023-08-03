#include "c_myLcn.h"

INT32 CMyLcn_C::AssembleSendData(UINT8 *buf, const INT32 bufferSize)
{
	if ( NULL == buf )
	{// �βμ��
		return -1;
	}

	INT32 size = 0;
	INT32 step = 0;

	switch( SendTaskNo )
	{
	case 0 :
		step = AssembleAssignIDTask(buf, bufferSize, size);
		break;
	default:
		break;
	}

	return step;
}

INT32 CMyLcn_C::AssembleAssignIDTask(UINT8 *buf, const INT32 bufferSize, INT32& size) {
	// ɾ������id->��ѯ�����豸id��sn��->����sn������id->��ѯ����id
	switch( SendIDTaskNo )
	{
	case 0 :
		DataInfo.DataType |= Fr::FrameType::eFrameYk;
		size = AssembleDestroyID(buf, bufferSize);
		break;
	case 1 :
		DataInfo.DataType |= Fr::FrameType::eFrameYc;
		size = AssembleQueryID(buf, bufferSize);
		break;
	case 2 : 
		DataInfo.DataType |= Fr::FrameType::eFrameYk;
		size = AssembleDownloadID(buf, bufferSize);
		break;
	case 3 :
		DataInfo.DataType |= Fr::FrameType::eFrameYc;
		size = AssembleQueryID(buf, bufferSize);
		break;
	default:
		break;
	}

	if ( 2 == SendIDTaskNo && IDtotal < v_devFeature.size() ) { // ����id������������С������sn������������ڶ���
		SendIDTaskNo = 2;
	} else if ( 3 == SendIDTaskNo && false == IsRecv ) { // �㲥��ѯidδ�ظ������������id
		SendIDTaskNo = 3;
	} else if ( 3 == SendIDTaskNo && true == IsRecv ) { // �㲥��ѯid�ظ��������·���id
		SendIDTaskNo = 0;
	} else {
		SendIDTaskNo++;
	}

	return SendIDTaskNo;
}

INT32 CMyLcn_C::AssembleDestroyID(UINT8 *buf, const INT32 bufferSize) {
	INT32 i = 0;
	UINT16 ChkCRC16 = 0x0000;

	// ɾ�����������id���ģ�00 39 0b 07 00 64 crc(L) crc(H)
	buf[i++] = 0x00;				// ��վ��ַ
	buf[i++] = 0x39;				// ������
	buf[i++] = 0x0B;				// ��ʼ��ַ���ֽ�
	buf[i++] = 0x07;				// ��ʼ��ַ���ֽ�
	buf[i++] = 0x00;				// ��Ȧ�������ֽ�
	buf[i++] = 0x64;				// ��Ȧ�������ֽ�

	ChkCRC16 = CRC16(buf, i);

	buf[i++] = LOBYTE(ChkCRC16);		// crcУ����ֽ�
	buf[i++] = HIBYTE(ChkCRC16);		// crcУ����ֽ�

	return i;
}

// �з��ر���˵��û�з�����ȫ��û�з��ر���˵������ɷ���
INT32 CMyLcn_C::AssembleQueryID(UINT8 *buf, const INT32 bufferSize) {
	INT32 i = 0;
	UINT16 ChkCRC16 = 0x0000;

	// ��ѯ���������id���ģ�00 35 0b 07 00 0b crc(L) crc(H)
	buf[i++] = 0x00;
	buf[i++] = 0x35;
	buf[i++] = 0x0B;
	buf[i++] = 0x07;
	buf[i++] = 0x00;
	buf[i++] = 0x0B;

	ChkCRC16 = CRC16(buf, i);

	buf[i++] = LOBYTE(ChkCRC16);
	buf[i++] = HIBYTE(ChkCRC16);

	return i;
}

INT32 CMyLcn_C::AssembleDownloadID(UINT8 *buf, const INT32 bufferSize) {
	DevFeature dev;
	INT32 i = 0;
	UINT16 ChkCRC16 = 0x0000;

	
	buf[i++] = 0x00;
	buf[i++] = 0x38;
	buf[i++] = 0x0B;
	buf[i++] = 0x07;
	for (int j = 0; j < 20; j++) {
		buf[i++] = v_devFeature[IDtotal].sn[j];
	}
	buf[i++] = 0x00;
	IDtotal++;
	buf[i++] = IDtotal;
	
	return i;
}