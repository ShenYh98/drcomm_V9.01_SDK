#include "s_myLcn.h"

static CHAR dscProtocol[] = "����˹�Լ����ʾ�� \n V1.0  \n �����ˣ�XXX ����ʱ�䣺XXXX��XX��XX��\n�ͻ��������ͨ������ncommData.dll�������ոù�Լ��tcp server��ʽת��������";

static CHAR dscProtocol_en[] = "Example protocol, for developer V1.0";

//�����ڵ�Ĺ�Լ�������
extern "C" LCNIFENTRY CLcnIF* Create_NodeObj()
{
	CMyLcn_S *pObj = new CMyLcn_S();

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
	PtOtherInfo.fProtocolVersion = Fr::SystemVersion; //���ð汾��
	PtOtherInfo.ProtocolType = Fr::Protocol::PServer;	//��Լ����,����˹�Լ��������ΪFr::Protocol::PServer

	PtOtherInfo.flgApp  = 0;
	PtOtherInfo.flgProc = 0;
	PtOtherInfo.flgProc |= PTOTHERINFO::PBitYkSelectCheck;  //��Լ֧��ң��ѡ����
	//�������ñ�־��ncommƽ̨���Զ���ң��ѡ��������з�У����Լ����ֻ�账��ң��ִ�������

	PtOtherInfo.flgProc |= PTOTHERINFO::PBitYtSelectCheck;  //��Լ֧��ң��ѡ����
	//�������ñ�־��ncommƽ̨���Զ���ң��ѡ��������з�У����Լ����ֻ�账��ң��ִ�������

	PtOtherInfo.ZtType		  =  Fr::CFG::NONE; 	//��Լ����̬û�У��������ã���ο�c_example��Ŀ
	PtOtherInfo.pCommonCfgDef = NULL;

	PtOtherInfo.Timer = 500;  //ȱʡΪÿ500ms�շ�һ�α��ģ�����ʵ����Ҫ��ͨ��ȡֵ5~10000ms

	PtOtherInfo.MaxYc		= P_YX_MAX;	//��ͬ�Ĺ�Լ�и��Ե���������
	PtOtherInfo.MaxYx		= P_YC_MAX;
	PtOtherInfo.MaxYm	= P_YM_MAX;
	PtOtherInfo.MaxYk		= P_YK_MAX;
	PtOtherInfo.MaxYt		= P_YT_MAX;

	if (PtOtherInfo.flgCfg & PTOTHERINFO::CBitEnglish)  //���ع�Լ����������ConfigTool������ʾ
		return dscProtocol_en; //����Ӣ�ĵĹ�Լ����������ConfigTool������ʾ
	else return dscProtocol;   	//�������ĵĹ�Լ����������ConfigTool������ʾ
}
