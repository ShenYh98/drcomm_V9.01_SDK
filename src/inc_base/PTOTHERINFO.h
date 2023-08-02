#ifndef _PTOTHERINFO_H_
#define _PTOTHERINFO_H_

#include "CommonCfg.h"

//��Լ������Ϣ
struct PTOTHERINFO
{
	static const INT32 PBitDdRealy			= 0x01;	//����ת��ģʽר�ã�����ת����Լ�Ƿ�֧��΢������
	static const INT32 PBitYkSelectCheck	= 0x02;	//��Լ֧��ң��ѡ����
	static const INT32 PBitYtSelectCheck	= 0x04;	//��Լ֧��ң��ѡ����

	static const INT32 CBitEnglish			= 0x01;	//�ǹ��ʻ��汾����Ҫָ��Լ��������̬��Ϣ
	static const INT32 CBitEnglishDebug		= 0x02;	//������Ϣ�ǹ��ʻ��汾����Ҫ��ָʵʱ�ĵ�����Ϣ��pFrApi->toDebug������
	static const INT32 CBitHighSpeedNode	= 0x04;	//�������нڵ㣬SendSomething�������õļ��ʱ����1����,Timer������Ч

	static const INT32 PBitAppIec61850Server= 0x01;	//Iec61850�����
	static const INT32 PBitAppIec61850Client= 0x02;	//Iec61850�ͻ���
	static const INT32 PBitAppAgc			= 0x04;	//Agc
	static const INT32 PBitAppAvc			= 0x08;	//Avc
	static const INT32 PBitAppPlc			= 0x10;	//Plc
	static const INT32 PBitAppPowerEffic	= 0x20;	//��Ч����
	static const INT32 PBitAppPvWeb			= 0x40;	//�����ƶ

	INT32	ProtocolType	;	//��ԼͨѶģʽ, �����Fr::Protocol::PClient��
	INT32	ZtType			;	//��̬��������, �����Fr::CFG:: //ȡ��ԭ����ProtocolZt	;
								//>0��ʾ��Լ������̬���������Լ��������ͬ����չ����.lcn���Ӧ.pac����̬�����趯̬����.pac����ɹ�Լ��̬
	INT32	flgCfg			;	//������Ϣ��, �����PTOTHERINFO::CBitEnglish�ȣ�ȡ��ԭ����bP103bh
	INT32	flgApp			;	//���ܱ�־�������PTOTHERINFO::PBitApp��
	FLOAT32	fProtocolVersion;	//��Լ������ƽ̨�汾��
	INT32	flgProc			;	//�����־���������PTOTHERINFO::PBit
	UINT32	Timer			;	//��ֵ����̬������PTOTHERINFO������Աֵ�ɳ���ֱ��ָ������ʱ����ʱ��(50��100��150��200��500��1000����   Ĭ��200����,UDPͨѶ����С��200����,�����Ļᶪ),
	BOOL32	bSendBoData		;	//�������ʹ�á���ͨ������UDPͨѶʱ���Ƿ��Թ㲥��ʽ���͡���Ĭ�ϲ���UDP/IP��		
	BOOL32	bSendZkState	;	//�������ʹ�á�ǰ�û���˫�ܿأ����÷�����103��Լ����ÿ���ܿض�����˫ͨ����ʱ����̨���޷��õ��ܿ�����״̬����Ϊ��ֻ̨�ܿ���ǰ�û����������ܿأ�
								//������ô˲���,ǰ�ý����ܿ�״̬�͵���̨���ܿص��߼��ڵ��ַΪ��ǰ��λ������ڵ��ַ��ͬ�������Ϊ
								//������ڵ��ַ��ͬ���һλ+����ڵ��+1��

	INT32	ProtocolBhId	;	//��Լ����ID(�����Լû�б�����bP103bh=TRUEʱ,������<Ĭ��Ϊ-1>)
	BOOL32	bTimerRevFun	;	//�Ƿ�ʱ����V_ReceiveProc()������ϵͳĬ��δ�յ����ݲ�����V_ReceiveProc()����
								//��Ҫ��ʱ������Կ���ʹ��EverySecondProc�� add on 2015.09.04
	BOOL32	bMutiRtuChn		;	//�������ʹ�á��Ƿ�����Ҫ����೧վ�Ľڵ㣨���ݽ��ܽڵ㣩
	BOOL32	bDataFloat		;	//YC�������Ƿ�Ϊfloat
	BOOL32	bNoDealHtData	;	//�Ƿ��ô����̨����
	BOOL32	bNoDealRunTag	;	//���۽ڵ��Ƿ�������״̬��ϵͳ�������������ݺ����ͽڵ����ݣ�Ĭ�Ͻڵ���Ͷ��״̬ʱ���ٽ����������ݺ����ͽڵ����ݣ�
	UINT32	nSendBufLen		;	//���ͻ�������С��Ĭ��4096�ֽ�  ����Χ 2048�ֽ� - 10485760�ֽ�(10M)
	UINT32	nRevBufLen		;	//���ջ�������С��Ĭ��4096�ֽ�  ����Χ 2048�ֽ� - 10485760�ֽ�(10M)
	INT32	MaxYx			;	//���ң��
	INT32	MaxYc			;	//���ң��
	INT32	MaxYm			;	//���ң��
	INT32	MaxYk			;	//���ң��
	INT32	MaxYt			;	//���ң��
	CCommonCfgDef *pCommonCfgDef;	//ͨ�õ���̬����	

	void SetDefault(){
		memset(this, 0, sizeof(*this));
		Timer=200;
		ProtocolBhId=-1;
		nSendBufLen=nRevBufLen=4096;
		MaxYx = 10000;
		MaxYc = 10000;
		MaxYm = 10000;
		MaxYk = 5000;
		MaxYt = 5000;
		pCommonCfgDef = NULL;
		fProtocolVersion = Fr::SystemVersion;
	}

	PTOTHERINFO()
	{
		SetDefault();
	};
};

#endif
