#include "c_myLcn.h"

//���������
CMyLcn_C::CMyLcn_C(void){}

CMyLcn_C::~CMyLcn_C(void){}

// �ڵ��ʼ��
void CMyLcn_C::V_NodeInit(void *pIF1)
{
	pIF = pIF1;		//����ϵͳ�Ĳ����ӿ�

	PTOTHERINFO pti;
	LCN_GetProtocolIdentify(pIF, &pti); //��ù�Լ����������Ϣ

	// �ⲿ�ִ�����Ϊ�˵���ʱ��ӡ׼���ģ������������Ŀ�ͱ���ע�����
	// ������Ŀ��ʾ�������ģ�Ӣ����ʾ��û�б�Ҫ
	if (pti.flgCfg & PTOTHERINFO::CBitEnglishDebug)
		isEnglishDebug = TRUE;
	else 
		isEnglishDebug = FALSE;

	//��ʼ����������
	nowPulsSec = LCN_GetSystemPuls(pIF);
	lastSetTimePulsSec = nowPulsSec;
	SendIDTaskNo = 0;		// ��ʼ��Ϊ-1����һ�����оͻ��Լ�Ϊ0
	SendTaskNo = 0;
	IsRecv = false;
	IDtotal = 0x00;
	v_devFeature.clear();
	start_time = std::clock();

	/////////////////////////////////////////////////////////////////////////////////////
	// �������ȡͨ��������Ĳ�����������������������С�
	/////////////////////////////////////////////////////////////////////////////////////
}

// �ڵ㱻����
void CMyLcn_C::V_NodeDestroy(){}

// ���մ���
DEALDATAINFO CMyLcn_C::V_ReceiveProc(const UINT8* buf,const INT32 bytes)
{
	UINT8 *pBuf = NULL;

	DataInfo.SetDefault();

	INT32 i = 0;
	UINT8 FunCode = 0x00;
	UINT16 RChkCRC16 = 0x0000;	// ����CRC16У����
	UINT16 CChkCRC16 = 0x0000;	// ����CRC16У����
	UINT32 Len = 0;		//���ĳ���

	pBuf = (UINT8 *)&buf[i];

	FunCode = pBuf[1];
	if ( 0x80 == ( FunCode & 0x80 ) )
	{// �����쳣��
		// ������01 82 01 81 60
		RChkCRC16 = MAKEWORD(pBuf[3], pBuf[4]);		// ���յ�CRCֵ�ӹ̶�λ��ȡ���ֽ����ǰ�ߺ� L H
		CChkCRC16 = CRC16(pBuf, 3);			// �����CRCֵ
		if ( RChkCRC16 == CChkCRC16 )
		{// �ҵ�һ֡�����ı��ģ����Ƿ��ص����쳣��Ϣ
			// ���쳣����д���
			i += 5;		// ���ñ��Ĵ���ĳ���
			LCN_SetRecvGoodPackage(pIF, 1);
			DataInfo.Bytes = i + 5;			//���ñ��Ĵ���ĳ���

			return DataInfo;
		}
	}

	if ( 0x03 == FunCode || 0x04 == FunCode || 0x35 == FunCode )
	{// �����Ĳ�ѯ���ر���
		Len = pBuf[2];		// ��3���ֽ��ǽ������ݳ���
		RChkCRC16 = MAKEWORD(pBuf[Len + 3], pBuf[Len + 4]);
		CChkCRC16 = CRC16(pBuf, Len + 3);
		if ( RChkCRC16 == CChkCRC16 )
		{// �ҵ�һ֡�����ı���
			if ( ParsePacket(pBuf, Len) < 0 )  //����1���������ı���
			{
				LCN_SetRecvBadPackage(pIF, 1); //��������1
			}
			else
			{
				LCN_SetRecvGoodPackage(pIF, 1);  //�������ɹ����ð�����1
				DataInfo.Bytes = i + Len + 8;			//���ñ��Ĵ���ĳ���
				IsRecv = true;

				return DataInfo;
			}
		}
	}

	if ( 0x39 == FunCode )
	{// 0x39����id���������ɹ���ظ����ģ����ô���
		Len = pBuf[2];		// ��3���ֽ��ǽ������ݳ���
		RChkCRC16 = MAKEWORD(pBuf[6], pBuf[7]);
		CChkCRC16 = CRC16(pBuf, 6);
		if ( RChkCRC16 == CChkCRC16 )
		{
			LCN_SetRecvGoodPackage(pIF, 1);
			DataInfo.Bytes = i + 8;			//���ñ��Ĵ���ĳ���
			IsRecv = true;

			return DataInfo;
		}
	}

	DataInfo.Bytes = 0;			//���ñ��Ĵ���ĳ���

	return DataInfo;
}

// ���ʹ���
DEALDATAINFO CMyLcn_C::V_SendProc(UINT8* buffer,const INT32 bufferSize)
{
	DataInfo.SetDefault();

	std::clock_t current_time = std::clock();  // ��ȡ��ǰʱ��ʱ��
	double elapsed_seconds = (current_time - start_time) / (double)CLOCKS_PER_SEC;  // ���㾭��������

	if (elapsed_seconds >= 3.0) {
		DataInfo.Bytes = AssembleSendData(buffer, bufferSize);

		if ( DataInfo.Bytes > 0 )
		{//������ʴ�ʽ��Լ��������Ҫ����DataInfo.isSyncChar=TRUE����֪ͨϵͳ����ϴ��յ��Ļ�������
			DataInfo.isSyncChar = TRUE;
		}

		start_time = std::clock();  // ���ü�ʱ��
	}

	return DataInfo;
}

//ͨ������
INT32 CMyLcn_C::V_ChannelReset()
{
	//��ʼ����������
	nowPulsSec = LCN_GetSystemPuls(pIF);
	lastSetTimePulsSec = nowPulsSec;
	SendIDTaskNo = 0;		// ��ʼ��Ϊ-1����һ�����оͻ��Լ�Ϊ0
	SendTaskNo = 0;
	IDtotal = 0x00;
	IsRecv = false;
	v_devFeature.clear();
	start_time = std::clock();

	return 0;
}

// ÿ�봦��
INT32 CMyLcn_C::V_EverySecondProc(INT32 systemPlus1)
{
	return 0;
}

//CRCУ���빫ʽ
UINT16 CMyLcn_C::CRC16(UINT8* pDataBuf, INT32 DataLen)
{
	INT32 i = 0;
	INT32 j = 0;
	UINT16 crc = 0xFFFF;		// ����ֵ

	for ( i = 0; i < DataLen; i++ )
	{
		crc = crc ^ (UINT16)pDataBuf[i];
		for ( j = 0; j < 8; j++ )
		{
			if ( ( crc & 0x0001 ) != 0 )
			{
				crc = ( crc >> 1 ) ^ 0xA001;		// CRCУ��������ʽ
			}
			else
			{
				crc = crc >> 1;
			}
		}// End of for(j)
	}// End of for(i)

	return crc;
}
