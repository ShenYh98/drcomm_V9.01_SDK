#include "c_myLcn.h"

static CHAR dscProtocol[] = "���װ壩�ͻ��˹�Լ����ʾ����\n V1.0  \n �����ˣ�XXX ����ʱ�䣺XXXX��XX��XX��";   // "\n"��ʾ�������ݻ���

static CHAR dscProtocol_en[] = "The empty client example protocol, \n for developer V1.0";  

extern void SetCfgDef(CCommonCfgDef *pCfgDef1, BOOL32 isEnglish);

//�����ڵ�Ĺ�Լ�������
extern "C" LCNIFENTRY CLcnIF* Create_NodeObj() 
{
    CMyLcn_C *pObj = new CMyLcn_C();
	return pObj;
}

//�ͷŽڵ�Ĺ�Լ�������
extern "C" LCNIFENTRY void Destroy_NodeObj(CLcnIF* p) 
{
	p->V_NodeDestroy();
    delete p;
}

//�õ���Լ������Ϣ�����ع�Լ��������Ҫ������̬������á�
extern "C" LCNIFENTRY LPSTR GetProtocolIdentify(PTOTHERINFO &PtOtherInfo)
{
	PtOtherInfo.fProtocolVersion = Fr::SystemVersion;//���ð汾��
	PtOtherInfo.ProtocolType=Fr::Protocol::PClient;		//��Լ����,�ͻ��˹�Լ��������ΪFr::Protocol::PClient
	
	PtOtherInfo.flgApp  = 0;

	PtOtherInfo.flgProc = 0;
	PtOtherInfo.flgProc |= PTOTHERINFO::PBitYkSelectCheck;  //��Լ֧��ң��ѡ����
															//�������ñ�־��ncommƽ̨���Զ���ң��ѡ��������з�У����Լ����ֻ�账��ң��ִ�������

	PtOtherInfo.flgProc |= PTOTHERINFO::PBitYtSelectCheck;  //��Լ֧��ң��ѡ����
															//�������ñ�־��ncommƽ̨���Զ���ң��ѡ��������з�У����Լ����ֻ�账��ң��ִ�������

	//PtOtherInfo.ZtType�����ù�Լ��̬���� 
	//�����Լ������̬����Ӧ���ã� PtOtherInfo.ZtType = Fr::CFG::NONE; ������43-48�д���Ҫ��ɾ�����ɲμ���Ŀs_example��GetProtocolIdentifyʹ��
	PtOtherInfo.ZtType		  =  Fr::CFG::Common;  //��Լ����̬��ʽ�����ó�Fr::CFG::Common,��ʾPtOtherInfo.pCommonCfgDef��Ч

	PtOtherInfo.pCommonCfgDef = new CCommonCfgDef(3, 1);	//��2�ű��ͨ����̬����,ÿ����̬���ݾ��Ա��ֶη�ʽ����
															//���ò����İ汾����1���汾����Ϊ���ڹ�Լ����������̬�����ṹ
	if ( PtOtherInfo.flgCfg & PTOTHERINFO::CBitEnglish )		//�ж���Ӣ�İ�
		SetCfgDef((CCommonCfgDef*)PtOtherInfo.pCommonCfgDef, TRUE); //������̬�����Ľ���������󣬸�ConfigTool.exe��
	else
		SetCfgDef((CCommonCfgDef*)PtOtherInfo.pCommonCfgDef, FALSE); //������̬�����Ľ���������󣬸�ConfigTool.exe��

	PtOtherInfo.Timer = 200;   //ȱʡΪÿ200ms�շ�һ�α��ģ�����ʵ����Ҫ��ͨ��ȡֵ5~10000ms
	PtOtherInfo.bTimerRevFun = TRUE;

	//���ù�Լ�������,������̬ʱ��������������
	PtOtherInfo.MaxYc = P_YX_MAX;
	PtOtherInfo.MaxYx = P_YC_MAX;
	PtOtherInfo.MaxYm = P_YM_MAX; 
	PtOtherInfo.MaxYk = P_YK_MAX;
	PtOtherInfo.MaxYt = P_YT_MAX;

	if (PtOtherInfo.flgCfg & PTOTHERINFO::CBitEnglish)
		 return dscProtocol_en; //����Ӣ�ĵĹ�Լ����������ConfigTool������ʾ
	else 
		 return dscProtocol;	//�������ĵĹ�Լ����������ConfigTool������ʾ
}
