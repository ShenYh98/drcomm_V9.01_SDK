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
	SendQueryNo = -1;		// ��ʼ��Ϊ-1����һ�����оͻ��Լ�Ϊ0
	CurrDevNo = 0;
	DevNum = -1;

	// ��ȡͨ��������Ĳ���
	INT32 size;
	INT8 * buf = LCN_GetZtBuf(pIF, &size);
	pti.pCommonCfgDef->LoadCfgBuf(size, (BYTE *)buf);  //������̬����

	//���ر�0����̬����
	pParam0 = (Table0DataStruct *)(pti.pCommonCfgDef)->pTable[0].ReadDynamicTable(sizeof(Table0DataStruct), &DevNum);

	//���ر�1����̬����
	pParam1 = (Table1DataStruct *)(pti.pCommonCfgDef)->pTable[1].ReadDynamicTable(sizeof(Table1DataStruct), &numParam1);

	////���ر�1����̬����
	//pParam2 = (Table1DataStruct *)(pti.pCommonCfgDef)->pTable[2].ReadDynamicTable(sizeof(Table1DataStruct), &numParam2);

	GetCfgData();
}

void CMyLcn_C::GetCfgData()
{
	INT32 i = 0;
	INT32 TmnlYxNum = 0;
	INT32 TmnlYcNum = 0;
	INT32 TmnlYmNum = 0;

	if ( DevNum <= 0 || numParam1 <= 0 )
	{// �ն��������ѯ����û����
		return;
	}

	// ����ÿ���ն˵���������
	for ( i = 0; i < numParam1; ++i )
	{
		if ( 1 == pParam1[i].Type )
		{// ң��
			TmnlYxNum += pParam1[i].QueryNum;	// ����ÿ����Ȧ����һ��ң��ֵ
		}
		else if ( 2 == pParam1[i].Type )
		{// ң��
			TmnlYcNum += pParam1[i].QueryNum;	// ����ÿ���Ĵ�������һ��ң��ֵ
		}
		else if ( 3 == pParam1[i].Type )
		{// ң��
			TmnlYmNum += pParam1[i].QueryNum / 2;	// ����2���Ĵ�������һ��ң��ֵ
		}
	}// End of for

	TmnlDataList = new TmnlDataStruct[DevNum];

	// ��1���豸���⴦��
	TmnlDataList[0].YxNum = TmnlYxNum;
	TmnlDataList[0].YcNum = TmnlYcNum;
	TmnlDataList[0].YmNum = TmnlYmNum;
	TmnlDataList[0].YxOffset = 0;
	TmnlDataList[0].YcOffset = 0;
	TmnlDataList[0].YmOffset = 0;

	// ��1��֮��������豸
	for ( i = 1; i < DevNum; ++i )
	{
		TmnlDataList[i].YxNum = TmnlYxNum;
		TmnlDataList[i].YcNum = TmnlYcNum;
		TmnlDataList[i].YmNum = TmnlYmNum;
		TmnlDataList[i].YxOffset = TmnlDataList[i - 1].YxOffset + TmnlDataList[i - 1].YxNum;
		TmnlDataList[i].YcOffset = TmnlDataList[i - 1].YcOffset + TmnlDataList[i - 1].YcNum;
		TmnlDataList[i].YmOffset = TmnlDataList[i - 1].YmOffset + TmnlDataList[i - 1].YmNum;
	}// End of for
}

// �ڵ㱻����
void CMyLcn_C::V_NodeDestroy(){}

// ���մ���
DEALDATAINFO CMyLcn_C::V_ReceiveProc(const UINT8* buf,const INT32 bytes)
{
	UINT8 *pBuf = NULL;

	printf("V_ReceiveProc\n");
	DataInfo.SetDefault();

	INT32 i = 0;
	UINT8 FunCode = 0x00;
	UINT16 RChkCRC16 = 0x0000;	// ����CRC16У����
	UINT16 CChkCRC16 = 0x0000;	// ����CRC16У����
	UINT32 Len = 0;		//���ĳ���

	for ( i = 0; i < bytes; ++i )
	{
		pBuf = (UINT8 *)&buf[i];
		if ( pBuf[0] != 0x01 )// ��1���ֽ��Ǵ�վ��ַ
		{
			continue;
		}

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

		if ( 01 == FunCode || 02 == FunCode || 03 == FunCode || 04 == FunCode )
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

					return DataInfo;
				}
			}
		}
	}// End of for

	DataInfo.Bytes = 0;			//���ñ��Ĵ���ĳ���

	return DataInfo;
}


// ���ʹ���
DEALDATAINFO CMyLcn_C::V_SendProc(UINT8* buffer,const INT32 bufferSize)
{
	DataInfo.SetDefault();

	printf("V_SendProc\n");
	//printf("Hello, world!\n");
	DataInfo.Bytes = AssembleSendData(buffer, bufferSize);

	if ( DataInfo.Bytes > 0 )
	{//������ʴ�ʽ��Լ��������Ҫ����DataInfo.isSyncChar=TRUE����֪ͨϵͳ����ϴ��յ��Ļ�������
		DataInfo.isSyncChar = TRUE;
	}

	return DataInfo;
}

//ͨ������
INT32 CMyLcn_C::V_ChannelReset()
{
	//��ʼ����������
	nowPulsSec = LCN_GetSystemPuls(pIF);
	lastSetTimePulsSec = nowPulsSec;
	SendQueryNo = -1;		// ��ʼ��Ϊ-1����һ�����оͻ��Լ�Ϊ0

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
