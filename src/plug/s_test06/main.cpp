#include "s_myLcn.h"
#include "LcnProc.h"

// ���������
CMyLcn_S::CMyLcn_S(void){}

CMyLcn_S::~CMyLcn_S(void){}

// �ڵ��ʼ��
void CMyLcn_S::V_NodeInit(void * pIF1)
{
	pIF = pIF1;		//����ϵͳ�����Ĳ����ӿ�

	PTOTHERINFO pti;
	LCN_GetProtocolIdentify(pIF, &pti); //��ù�Լ����������Ϣ

	// �ⲿ�ִ�����Ϊ�˵���ʱ��ӡ׼���ģ������������Ŀ�ͱ���ע�����
	// ������Ŀ��ʾ�������ģ�Ӣ����ʾ��û�б�Ҫ
	if ( pti.flgCfg & PTOTHERINFO::CBitEnglishDebug )
		isEnglishDebug = TRUE;
	else 
		isEnglishDebug = FALSE;

	// �õ�ת�������ã�ֻ�з���˹�Լ��Ҫת�����ͻ��˹�Լ����ת����
	pFtm = LCN_GetTransMap(pIF);

	// �ڵ�ʵ�ʵ�������ת�����������ܲ�һ��
	// ת�������ݱ��밴ת������
	// �����Ͻڵ��������Ӧ��С��ת��������
	FactRtuCapacity		capacity;	// �ڵ�����
	LCN_GetNodeDataCapacity(pIF, &capacity);
	if (capacity.RealYx > pFtm->numYx)
		iTotalSendYxNum = pFtm->numYx;
	else iTotalSendYxNum = capacity.RealYx;
	if (capacity.RealYc > pFtm->numYc)
		iTotalSendYcNum = pFtm->numYc;
	else iTotalSendYcNum = capacity.RealYc;
	if (capacity.RealYm > pFtm->numYm)
		iTotalSendYmNum = pFtm->numYm;
	else iTotalSendYmNum = capacity.RealYm;

	//���ù�Լ�������ݸ�����Ϣ����󻺳�������Ϣ֪ͨ���ƣ�
	//Fm::MsgQueue::MaxΪ��������С�ı�׼ֵ������Լ�ɸ��������Լ��ʵ����������yxNum��ֵ
	//ͨ������˹�Լ��ת����Լ����Ҫ����������ݸ�����֪ͨ���ڵ㣬
	//yxNotify��ycNotify�ֱ��ʾң�Ż�ң�����ݵĸ�����Ϣ���ͣ�ң�����ݹ̶����и��¼�֪ͨ
	MsgNotifyDef msgRecNotifyDef;
	msgRecNotifyDef.yxNum		= Fm::MsgQueue::MaxYxNum;	//ң����Ϣ����󻺳���
	msgRecNotifyDef.ycNum		= Fm::MsgQueue::MaxYcNum;	//ң����Ϣ����󻺳���
	msgRecNotifyDef.ymNum	= Fm::MsgQueue::MaxYmNum;	//ң����Ϣ����󻺳���
	msgRecNotifyDef.soeNum	= Fm::MsgQueue::MaxSoeNum;	//SOE��Ϣ����󻺳���
	msgRecNotifyDef.yxNotify	= Fm::Notify::ChangeValue;		//ң��ֵ�б仯��֪ͨ��Ʒ�ʱ仯��֪ͨ
	msgRecNotifyDef.ycNotify	= Fm::Notify::ChangeValue_Q;	//ң��ֵ��Ʒ���б仯��֪ͨ
	LCN_SetMsgNotifyDef(pIF, &msgRecNotifyDef);

	IsCallAllData = FALSE;		// ��ʼ������������
	IsACK = FALSE;					// ��ʼ�������Ϳ϶�ȷ��
	IsCallYx = FALSE;
	IsCallYc = FALSE;
	IsCallYm = FALSE;

	NodeReadmeInfo nodeReadmeInfo;
	LCN_GetNodeReadmeInfo(pIF, &nodeReadmeInfo, sizeof(nodeReadmeInfo));
	printf("node %s Init\n", nodeReadmeInfo.Name);
}

// �ڵ㱻����
void CMyLcn_S::V_NodeDestroy(){}

// ���մ���
DEALDATAINFO CMyLcn_S::V_ReceiveProc(const UINT8* buf, const INT32 bytes)
{
	DataInfo.SetDefault();
	DataInfo.Bytes = bytes;		// ���ñ��Ĵ���ĳ���

	if ( ParsePacket(buf, bytes) < 0 )
	{
		LCN_SetRecvBadPackage(pIF, 1);	// ��������1
	}
	else
	{
		LCN_SetRecvGoodPackage(pIF, 1);  // �������ɹ����ð�����1
	}

	return DataInfo;
}

// ���ʹ���
DEALDATAINFO CMyLcn_S::V_SendProc(UINT8* buf, const INT32 bufSize)
{
	DataInfo.SetDefault();

	DataInfo.Bytes = AssembleSendData(buf, bufSize);

	if ( DataInfo.Bytes > 0 )
	{//������ʴ�ʽ��Լ��������Ҫ����DataInfo.isSyncChar=TRUE����֪ͨϵͳ����ϴ��յ��Ļ�������
		DataInfo.isSyncChar = TRUE;
	}

	return DataInfo;
}


INT32 CMyLcn_S::V_EverySecondProc(INT32 systemPlus1)
{
	return 0;
}

INT32 CMyLcn_S::V_ChannelReset()
{
	IsCallAllData = FALSE;
	IsACK = FALSE;

	return 0;
}
