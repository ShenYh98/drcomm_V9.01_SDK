#include "a_myLcn.h"

CMyLcn_A::CMyLcn_A(void){}

CMyLcn_A::~CMyLcn_A(void){}

void CMyLcn_A::V_NodeInit(void *pIF1)
{	
	pIF = pIF1;		//����ϵͳ�Ĳ����ӿ�

	//ͨ����̬��������ʾ��
	PTOTHERINFO pti;
	LCN_GetProtocolIdentify(pIF, &pti); //��ù�Լ����������Ϣ

	if (pti.flgCfg & PTOTHERINFO::CBitEnglishDebug)
		isEnglishDebug = TRUE;
	else
		isEnglishDebug = FALSE;

	//ͨ����̬��������
	CCommonCfgDef *pCfgDef = (CCommonCfgDef *)pti.pCommonCfgDef;  //�õ�ͨ����̬�ı��ֶζ���
	INT32 size;
	INT8 *buf = LCN_GetZtBuf(pIF, &size);
	pCfgDef->LoadCfgBuf(size, (BYTE *)buf);  //������̬����
	//���´����ǽ�ͨ����̬�������뵽������
	//���ر�0����̬����
	if (  (pCfgDef->pTable[0].numRecord !=1)
		||(pCfgDef->pTable[0].numField != 4)  //4���ֶ�
		||(pCfgDef->pTable[0].iUnitSize != sizeof(cfg)))
	{
		cfg.SetDefault();
	}
	else
	{
		pCfgDef->pTable[0].ReadStaticTable(sizeof(cfg), &cfg, 1);
	}

	nowPulsSec = LCN_GetSystemPuls(pIF);
	checkPlusSec = 0;
}

INT32 CMyLcn_A::V_EverySecondProc(INT32 systemPlus1)
{
	nowPulsSec = systemPlus1; // ��¼��ǰ��ϵͳ�����

	// ����Ƿ���ң�ػ�ң�����ò���
	YkYtCheck();

	// ���app���ж�ʱ������Ϊ��λ�����԰Ѹĺ����ŵ��Զ����Ƶ���
	AutoControlProc();

	return 0;
}

void CMyLcn_A::YkYtCheck()
{
	YkYtMsg ykMsgData;

	LCN_GetYkYtMsgData(pIF, &ykMsgData);		// ȡ��ǰң��״̬

	if( ykMsgData.State == Fr::YK_IDLE )
	{// �޿�������
		return;
	}

	// �п�������
	if( !ykMsgData.IsYk )
	{// ��ң��
		if ( ykMsgData.ObjectNo != 0 && ykMsgData.ObjectNo != 1 )		return;

		if ( ykMsgData.State == Fr::YKYT_SELECT )
		{
			LCN_SetYtReturn(pIF, ykMsgData.Action, ykMsgData.ObjectNo, Fr::YK_ACK); //ң����У
			return;
		}

		if ( ykMsgData.State != Fr::YT_EXE )		return;

		if ( ykMsgData.Action != Fr::YT_OUT )		return;

		// ��ң��ִ��
		FLOAT32 fSet;
		if (ykMsgData.OtherType == 1)
			fSet = ykMsgData.OtherValue;
		else if (ykMsgData.OtherType == 2)
			fSet = (FLOAT32)ykMsgData.OtherValue2;
		else
			return;

		FLOAT32 fv = fSet / 10;

		LCN_SetYcFloat(pIF, ykMsgData.ObjectNo, fSet);		// YC0���¶����ޣ�YC1���¶�����

		//����Ӧ�ýڵ�����ݣ��������á�Ϊ�˷�ֹ������������������ÿ��ܶ�ʧ�����뱣��
		LCN_SaveNodeData(pIF, Fr::DataSort::Yc);
	}
	else
	{// ��ң��
		if ( ykMsgData.ObjectNo != 0 && ykMsgData.ObjectNo != 1 )		return;

		if (ykMsgData.State == Fr::YK_SELECT)
		{//ң��ѡ��
			LCN_SetYkReturn(pIF, ykMsgData.Action, ykMsgData.ObjectNo, Fr::YK_ACK); //ң�ط�У
			return;
		}

		if (ykMsgData.State != Fr::YK_EXE)		return;
		
		//��ң��ִ��
		if ( ykMsgData.Action == Fr::YK_OFF )//ң�ط�
			LCN_SetYx(pIF, ykMsgData.ObjectNo, 0);
		else if ( ykMsgData.Action == Fr::YK_ON )//ң�غ�
			LCN_SetYx(pIF, ykMsgData.ObjectNo, 1);
	
		//����Ӧ�ýڵ�����ݣ��������á�Ϊ�˷�ֹ������������������ÿ��ܶ�ʧ�����뱣��
		LCN_SaveNodeData(pIF, Fr::DataSort::Yx);
	}
}

void CMyLcn_A::AutoControlProc()
{
	BOOL32 isLock = FALSE;  // ����״̬

	LCN_SetYcFloat(pIF, 0, (FLOAT32)nowPulsSec);
	if ( (nowPulsSec - checkPlusSec) < cfg.secSpace )
	{// ��ʱ��ʱ��û��
		return;
	}

	checkPlusSec = nowPulsSec;

	if (!LCN_IsNodeRun(pIF, cfg.ycFdiWarm.noNode))  //��鵱ǰ�¶����ڽڵ�ͨ���Ƿ�����
		isLock = TRUE;
	if (!LCN_IsNodeRun(pIF, cfg.yxFdi.noNode))  //������������״̬���ڽڵ�ͨ���Ƿ�����
		isLock = TRUE;
	if (!LCN_IsNodeRun(pIF, cfg.ykFdi.noNode))  //������������Ͷ�����ڽڵ�ͨ���Ƿ�����
		isLock = TRUE;

	// ��ͣ�����ȼ���ߣ����ڿ�ͷ
	YxData stEmgStopData;	// ��ͣ״̬
	LCN_GetYxData(pIF, 1, &stEmgStopData);
	if ( !isLock && ( stEmgStopData.iValue == 1 ) )
	{// ������رռ�����
		YxData st;		// ������״̬����ʱ״̬��
		LCN_SGetYxData(pIF, cfg.yxFdi, &st);
		if ( st.iValue == 1 )
		{// ������������
			LCN_DoYkDirectExe(pIF, cfg.ykFdi, Fr::YK_OFF);  // �رռ�����
		}

		return;
	}

	YcData YcWarmData;  // ��ǰ�¶�ֵ
	if (!LCN_SGetYcData(pIF, cfg.ycFdiWarm, &YcWarmData))
		isLock = TRUE;

	if (YcWarmData.fValue - 100 >= 0.00001){
		printf("1111111\n");
		
	}
	
	printf("value is %.3f\n", YcWarmData.fValue);
	YcData WarmUpData;		// �¶�����ֵ
	if (!LCN_GetYcData(pIF, 0, &WarmUpData))
		isLock = TRUE;

	YcData WarmDnData;		// �¶�����ֵ
	if (!LCN_GetYcData(pIF, 1, &WarmDnData))
		isLock = TRUE;

	if ( WarmUpData.fValue <= WarmDnData.fValue )
	{// �¶�����ֵ���¶�����ֵ��Ҫ�ͣ������쳣״̬
		return;
	}

	YxData stWarmYxData;		// ������״̬
	if (!LCN_SGetYxData(pIF, cfg.yxFdi, &stWarmYxData))
		isLock = TRUE;

	YxData stEnData;	// �¿ع���Ͷ��/�˳�״̬
	if (!LCN_GetYxData(pIF, 0, &stEnData))
		isLock = TRUE;

	LCN_SetYx(pIF, 1, isLock);  // ˢ�±���״̬
	

	if ( isLock )		
		return;	// �����������˳�����

	if ( stEnData.iValue == 0 )		return;	// �¿ع����˳�

	if ( stWarmYxData.iValue == 0 )
	{// �������ѹر�
		if ( YcWarmData.fValue <= WarmDnData.fValue )
		{
			LCN_DoYkDirectExe(pIF, cfg.ykFdi, Fr::YK_ON);  //����������
		}
	}
	else
	{// ������������
		if ( YcWarmData.fValue > WarmUpData.fValue )
		{
			LCN_DoYkDirectExe(pIF, cfg.ykFdi, Fr::YK_OFF);  //�رռ�����
		}
	}
}
