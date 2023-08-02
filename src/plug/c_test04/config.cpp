#include "c_myLcn.h"

/**
 @brief �����̬���������Զ����ɲ������
 @param pHandle	   ��̬�ӿڶ���ָ��
 @param pNodeReadmeInfo �ڵ����������Ϣ
 @param pCfgDef	   ͨ����̬�����Ĵ������
 @param lenNote	   szNote�Ŀռ�
 @param szNote	   ���صĲ�����������ʾ
 @retval ���ز���״̬
 */
#ifdef _WINDOWS

//���ñ�1����̬����
void CreateTable0Def(CTable *pTable1, BOOL32 isEnglish)
{
	if ( !isEnglish )
	{
		pTable1->Init("��1", 2, 0);  //2���ֶ�

		pTable1->pField[0].SetStringDef("����", Fr::NAME_LENGTH);
		pTable1->pField[1].SetINT32Def("��ַ");
	}
	else
	{
		pTable1->Init("table 1", 2, 0);  //2���ֶ�

		pTable1->pField[0].SetStringDef("Device Name", Fr::NAME_LENGTH);
		pTable1->pField[1].SetINT32Def("Device address");
	}
		
	pTable1->SetSizeAndOffset();
}

//���ñ�2����̬����
void CreateTable1Def(CTable *pTable1, BOOL32 isEnglish)
{
	const CIntValue IntValueList0[]={{1, "ң��"}, {2, "ң��"},{3, "ң��"}};
	const CIntValue IntValueList0_EN[]={{1, "Yx"}, {2, "Yc"},{3, "Ym"}};
	const CIntValue IntValueList1[]={{1, "0x01"}, {2, "0x02"},{3, "0x03"},{4, "0x04"}};

	if ( !isEnglish )
	{
		pTable1->Init("��2", 6, 0);  //5���ֶ�

		pTable1->pField[0].SetINT32Def("��������");
		pTable1->pField[0].SetINT32ListMode(3, IntValueList0);
		pTable1->pField[1].SetINT32Def("������");
		pTable1->pField[1].SetINT32ListMode(4, IntValueList1);
		pTable1->pField[2].SetINT32Def("��ʼ��ַ");
		pTable1->pField[3].SetINT32Def("��ѯ����");
		pTable1->pField[4].SetINT32Def("ƫ����");
		pTable1->pField[5].SetFrDataIdxDef("�����ڵ����");
	}
	else
	{
		pTable1->Init("table 2", 6, 0);  //2���ֶ�

		pTable1->pField[0].SetINT32Def("Type");
		pTable1->pField[0].SetINT32ListMode(5, IntValueList0_EN);
		pTable1->pField[1].SetINT32Def("FunCode");
		pTable1->pField[1].SetINT32ListMode(6, IntValueList1);
		pTable1->pField[2].SetINT32Def("StartAddr");
		pTable1->pField[3].SetINT32Def("QueryNum");
		pTable1->pField[4].SetINT32Def("Offset");
		pTable1->pField[5].SetFrDataIdxDef("�����ڵ����");
	}
		
	pTable1->SetSizeAndOffset();
}

//���ñ�2����̬����
void CreateTable2Def(CTable *pTable1, BOOL32 isEnglish)
{
	const CIntValue IntValueList0[]={{1, "ң��"}, {2, "ң��"},{3, "ң��"}};
	const CIntValue IntValueList0_EN[]={{1, "Yx"}, {2, "Yc"},{3, "Ym"}};
	const CIntValue IntValueList1[]={{1, "0x01"}, {2, "0x02"},{3, "0x03"},{4, "0x04"}};

	if ( !isEnglish )
	{
		pTable1->Init("��3", 5, 5);  //5���ֶ�

		pTable1->pField[0].SetINT32Def("��������");
		pTable1->pField[0].SetINT32ListMode(3, IntValueList0);
		pTable1->pField[1].SetINT32Def("������");
		pTable1->pField[1].SetINT32ListMode(4, IntValueList1);
		pTable1->pField[2].SetINT32Def("��ʼ��ַ");
		pTable1->pField[3].SetINT32Def("��ѯ����");
		pTable1->pField[4].SetINT32Def("ƫ����");
	}
	else
	{
		pTable1->Init("table 2", 5, 5);  //2���ֶ�

		pTable1->pField[0].SetINT32Def("Type");
		pTable1->pField[0].SetINT32ListMode(5, IntValueList0_EN);
		pTable1->pField[1].SetINT32Def("FunCode");
		pTable1->pField[1].SetINT32ListMode(6, IntValueList1);
		pTable1->pField[2].SetINT32Def("StartAddr");
		pTable1->pField[3].SetINT32Def("QueryNum");
		pTable1->pField[4].SetINT32Def("Offset");
	}

	pTable1->SetSizeAndOffset();
}

// ��ConfigTool.exeѡ�и�lcn���ͻ���ô˺���
void SetCfgDef(CCommonCfgDef *pCfgDef1, BOOL32 isEnglish)
{
	CreateTable0Def(&pCfgDef1->pTable[0], isEnglish);
	CreateTable1Def(&pCfgDef1->pTable[1], isEnglish);
	CreateTable2Def(&pCfgDef1->pTable[2], isEnglish);
}

// ��ConfigTool.exe�ڵ���̬���ѡ�С�ȷ���޸ġ����ͻ���ô˺���
extern "C" LCNIFENTRY INT32 CheckConfigAndCreatePoint(void *pHandle, const NodeReadmeInfo *pNodeReadmeInfo, CCommonCfgDef * pCfgDef, INT32 lenNote=0, CHAR *szNote=NULL)
{
	INT32 i = 0;
	INT32 j = 0;
	INT32 TmnlNum = 0;
	INT32 QueryNum = 0;
	INT32 TmnlYxNum = 0;		// �ն�ң����������ͬ
	INT32 TmnlYcNum = 0;
	INT32 TmnlYmNum = 0;
	INT32 NodeYxNum = 0;		// �ڵ�ң����������ͬ
	INT32 NodeYcNum = 0;
	INT32 NodeYmNum = 0;
	INT32 YxOffset = 0;
	INT32 YcOffset = 0;
	INT32 YmOffset = 0;

	CHAR TmpName[Fr::NAME_LENGTH];
	CHAR SignalName[Fr::NAME_LENGTH];

	//������0����
	Table0DataStruct *pTable0 = (Table0DataStruct *)pCfgDef->pTable[0].ReadDynamicTable(sizeof(Table0DataStruct), &TmnlNum); 

	//������1����
	Table1DataStruct *pTable1 = (Table1DataStruct *)pCfgDef->pTable[1].ReadDynamicTable(sizeof(Table1DataStruct), &QueryNum); 
	
	if ( TmnlNum <=0 || QueryNum <= 0 )
	{// û��������Ŀ
		sprintf(szNote, "û��������Ŀ!");
		return -1;
	}

	for ( i = 0; i < QueryNum; ++i )
	{
		if ( 1 == pTable1[i].Type )
		{// ң��
			TmnlYxNum += pTable1[i].QueryNum;	// ����ÿ����Ȧ����һ��ң��ֵ
		}
		else if ( 2 == pTable1[i].Type )
		{// ң��
			TmnlYcNum += pTable1[i].QueryNum;	// ����ÿ���Ĵ�������һ��ң��ֵ
		}
		else if ( 3 == pTable1[i].Type )
		{// ң��
			TmnlYmNum += pTable1[i].QueryNum / 2;	// ����2���Ĵ�������һ��ң��ֵ
		}
	}// End of for

	NodeYxNum = TmnlNum * TmnlYxNum;
	NodeYcNum = TmnlNum * TmnlYcNum;
	NodeYmNum = TmnlNum * TmnlYmNum;
	
	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Yx, NodeYxNum);		//����ң������
	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Yc, NodeYcNum);		//����ң������
	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Ym, NodeYmNum);	//����ң������

	for ( i = 0; i < TmnlNum; ++i )
	{
		YxOffset = 0;		// ÿ��ѭ����ͷ����������
		YcOffset = 0;		// ÿ��ѭ����ͷ����������
		YmOffset = 0;	// ÿ��ѭ����ͷ����������

		sprintf(TmpName, "%s%s", pNodeReadmeInfo->Name, pTable0[i].sName);
		// ÿ������ֶ���������
		sprintf(SignalName, "%s%s",	TmpName, "�����̵���2��");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "�����̵���2��");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "����/���Ը���");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "������բ������1��");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "����2");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "A����ࣨ����3��");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B����ࣨ����4��");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C����ࣨ����5��");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "����6");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "����7");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "����8");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "����9");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "����10");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "����11");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "����12");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "����13");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);

		sprintf(SignalName, "%s%s",	TmpName, "A���ѹ");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B���ѹ");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C���ѹ");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "AB�ߵ�ѹ");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "BC�ߵ�ѹ");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "CA�ߵ�ѹ");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "A�����");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B�����");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C�����");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "A���й�");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B���й�");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C���й�");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "���й�");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "A���޹�");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B���޹�");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C���޹�");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "���޹�");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "A�๦������");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B�๦������");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C�๦������");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "�ܹ�������");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "Ƶ��");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "ʣ�����");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);

		sprintf(SignalName, "%s%s",	TmpName, "�ܵ���");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Ym, i * TmnlYmNum + YmOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "A�����");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Ym, i * TmnlYmNum + YmOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B�����");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Ym, i * TmnlYmNum + YmOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C�����");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Ym, i * TmnlYmNum + YmOffset++, SignalName);
	}// End of for(i)

	return 0;
}

#endif
