#include "a_myLcn.h"

// ���ñ�0����̬����
void CreateTable0Def(CTable *pTable1, BOOL32 isEnglish)
{
	INT32 i = 0;

	if ( !isEnglish )
	{
		pTable1->Init("��0", 4, 1);  //4���ֶΣ�1����¼

		pTable1->pField[i++].SetINT32Def("���Ƽ������", 10,1000,3);
		pTable1->pField[i++].SetFrDataIdxDef("��ǰ�¶ȵ���������");
		pTable1->pField[i++].SetFrDataIdxDef("����������״̬����������");
		pTable1->pField[i++].SetFrDataIdxDef("������Ͷ��/�˳�������");
	}
	else
	{
		pTable1->Init("table 0", 4, 1);  //4���ֶΣ�1����¼

		pTable1->pField[i++].SetINT32Def("space seconds");
		pTable1->pField[i++].SetFrDataIdxDef("index of AI");
		pTable1->pField[i++].SetFrDataIdxDef("index of DI");
		pTable1->pField[i++].SetFrDataIdxDef("index of DO");
	}

	pTable1->SetSizeAndOffset();
}

void SetCfgDef(CCommonCfgDef *pCfgDef1, BOOL32 isEnglish)
{
	CreateTable0Def(&pCfgDef1->pTable[0], isEnglish);
}

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
extern "C" LCNIFENTRY INT32 CheckConfigAndCreatePoint(void *pHandle, const NodeReadmeInfo *pNodeReadmeInfo, CCommonCfgDef * pCfgDef, INT32 lenNote=0, CHAR *szNote=NULL)
{
	//������������ʾ���������Լû����̬������ֱ�Ӳο�����Զ����ɴ���
	AppCfgDef cfg;
	pCfgDef->pTable[0].ReadStaticTable(sizeof(AppCfgDef), &cfg, 1); //������0����

	//����������ʾ����������Ϣ��szNote�з���
	if ( (cfg.secSpace < 3) || ( cfg.secSpace > 1000 ) )
	{
		SYSPROC::StrSafeCat(lenNote, szNote, "����������ò���ȷ");
		return -1;
	}

	BOOL32 isEnglish = LCN_CfgIsEnglish(pHandle);

	//�Զ�������ң������Ϣ����ʾ��
	char szText[128];

	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Yx, 2);	//����ң������
	sprintf(szText, "%s_�¿ع���Ͷ��", pNodeReadmeInfo->Name);	//����ң������
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, 0, szText);

	sprintf(szText, "%s_��ͣ", pNodeReadmeInfo->Name);
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, 1, szText);

	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Yc, 2);	//����ң������
	sprintf(szText, "%s_�¶�����",pNodeReadmeInfo->Name);	//����ң������
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, 0, szText);

	sprintf(szText, "%s_�¶�����",pNodeReadmeInfo->Name);
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, 1, szText);

	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Yk, 2);	//����ң������
	sprintf(szText, "%s_�¿ع���Ͷ��",pNodeReadmeInfo->Name);	//����ң������
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yk, 0, szText);

	sprintf(szText, "%s_��ͣ",pNodeReadmeInfo->Name);
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yk, 1, szText);

	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Yt, 2);	//����ң������
	sprintf(szText, "%s_�¶�����",pNodeReadmeInfo->Name);	//����ң������
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yt, 0, szText);

	sprintf(szText, "%s_�¶�����",pNodeReadmeInfo->Name);
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yt, 1, szText);

	return 0;
}

#endif
