#include "a_myLcn.h"

static CHAR dscProtocol[] = "Ӧ�ù��ܿ���ʾ����\n V1.0  ���ܣ��ü������������£�ά���������¶����޺��¶�����֮�䡣\n�¶Ȳ���������̬�����ã�\n �����ˣ�XXX ����ʱ�䣺XXXX��XX��XX��";   // "\n"��ʾ�������ݻ���

static CHAR dscProtocol_en[] = "application example, \n for developer V1.0";  

extern void SetCfgDef(CCommonCfgDef *pCfgDef1, BOOL32 isEnglish);

//�����ڵ�Ĺ�Լ�������
extern "C" LCNIFENTRY CLcnIF* Create_NodeObj() 
{
    CMyLcn_A *pObj = new CMyLcn_A();
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
	PtOtherInfo.ProtocolType=Fr::Protocol::APP;		//Ӧ�ù��ܹ�Լ���ͱ�������ΪFr::Protocol::APP

	PtOtherInfo.flgApp  = 0;
	PtOtherInfo.flgProc = 0;

	//PtOtherInfo.ZtType�����ù�Լ��̬���ͣ� 
	//�����Լ��̬��������ΪFr::CFG::Common����ConfigTool.exe�ڽ��иù�Լ��̬ʱ�����ͨ�õ���̬���棬������̬����ķ�ʽ����pCfgDef����
	//�����Լ������̬����Ӧ���ã� PtOtherInfo.ZtType = Fr::CFG::NONE; ������43-48�д���Ҫ��ɾ�����ɲμ���Ŀs_example��GetProtocolIdentifyʹ��
	PtOtherInfo.ZtType		  =  Fr::CFG::Common;  //��Լ����̬��ʽ�����ó�Fr::CFG::Common,��ʾPtOtherInfo.pCommonCfgDef��Ч
	PtOtherInfo.pCommonCfgDef = new CCommonCfgDef(1, 1);	//��1��ͨ�õ���̬����,ÿ����̬���ݾ��Ա��ֶη�ʽ����
															//���ò����İ汾����1���汾����Ϊ���ڹ�Լ����������̬�����ṹ
	if (PtOtherInfo.flgCfg & PTOTHERINFO::CBitEnglish)		//�ж���Ӣ�İ�
		SetCfgDef((CCommonCfgDef*)PtOtherInfo.pCommonCfgDef, TRUE); //������̬�����Ľ���������󣬸�ConfigTool.exe��
	else
		SetCfgDef((CCommonCfgDef*)PtOtherInfo.pCommonCfgDef, FALSE); //������̬�����Ľ���������󣬸�ConfigTool.exe��

	PtOtherInfo.Timer = 200;   //ȱʡΪÿ200ms�շ�һ�α��ģ�����ʵ����Ҫ��ͨ��ȡֵ5~10000ms

	//���ù�Լ�������,������̬ʱ�������������ƣ���������ʵ����Ҫ
	PtOtherInfo.MaxYc = 1000;
	PtOtherInfo.MaxYx = 1000;
	PtOtherInfo.MaxYm = 1000; 
	PtOtherInfo.MaxYk = 1000;
	PtOtherInfo.MaxYt = 1000;

	if (PtOtherInfo.flgCfg & PTOTHERINFO::CBitEnglish)
		return dscProtocol_en; //����Ӣ�ĵĹ�Լ����������ConfigTool������ʾ
	else
		return dscProtocol;	//�������ĵĹ�Լ����������ConfigTool������ʾ
}
