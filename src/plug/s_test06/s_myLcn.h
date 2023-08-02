#ifndef _S_MY_LCN_H_
#define _S_MY_LCN_H_

#include "LcnIF.h"
#include "LcnProc.h"

// ʾ����ԼͨѶ����������
namespace TYPECODE
{
	static const INT32 CHG_YX	=	1;				// �仯ң������
	static const INT32 CHG_YC	=	2;				// �仯ң������
	static const INT32 CHG_YM	=	3;				// �仯ң������
	static const INT32 SOE		=	4;				// SOE����
	static const INT32 ALL_YX	=	5;				// ȫң������
	static const INT32 ALL_YC	=	6;				// ȫң������
	static const INT32 ALL_YM	=	7;				// ȫң������
	static const INT32 YKSIN	=   8;			// ����ң��
	static const INT32 YKDIN	=   9;			// ˫��ң��
	static const INT32 YT			=   10;			// ң��
	static const INT32 NormalQuery	=   11;	// ����
	static const INT32 SetTime	=   12;			// Уʱ
	static const INT32 CallAll	=   13;			// ����
	static const INT32 ResetLink=	14;			// ��·��λ
	static const INT32 CurveData=	15;		// ��������
}

//���屾��Լϵͳ����
const INT32 P_YX_MAX							= 10000;					// ���ң����
const INT32 P_YC_MAX							=  5000;					// ���ң����
const INT32 P_YM_MAX							=  2000;					// �������
const INT32 P_YK_MAX							=  2000;					// ���ң����
const INT32 P_YT_MAX							=  2000;					// ���ң����

class CMyLcn_S: public CLcnIF
{
	void *		pIF;			//ϵͳ���������Ĳ����ӿڶ���ָ�룬ÿ����Լ���������ñ���

	const FrTransMapBase*	pFtm;			// ת�������ã�ͨ������˹�Լ��Ҫ�õ�ת����

	INT32		iTotalSendYxNum;				// ң��ת������
	INT32		iTotalSendYcNum;				// ң��ת������
	INT32		iTotalSendYmNum;				// ң��ת������

	DEALDATAINFO DataInfo;					// �����շ������ķ��ض���

	BOOL32		isEnglishDebug;					// ���������ϢΪӢ��
	BOOL32		IsCallAllData;						// ���ٻ�
	BOOL32		IsACK;								// �϶�ȷ��
	BOOL32		IsCallYx;							// �ٻ�ң��
	BOOL32		IsCallYc;							// �ٻ�ң��
	BOOL32		IsCallYm;							// �ٻ�ң��

public:
	CMyLcn_S();

	~CMyLcn_S(void);

	/**
	* @brief		 ��ʼ����Լ׼�����еĲ�����ϵͳ�����нڵ�ȫ����ʼ����ſ�ʼ�������߳̽��и���ͨѶ�շ�����
	* @param pFrApi1 ϵͳ���������Ĳ����ӿڶ���ָ��
	**/
	virtual void V_NodeInit(void *pIF1);

	/**
	* @brief		��Լ�����Ĵ�����,��Ҫ�ǹرչ�Լ����������ľ���������ļ��������ڴ����Ⱦ��
	**/
	virtual void V_NodeDestroy();

	/**
	* @brief			�Խ��ձ��Ľ��д���
	* @param buf		�������ݵĻ�����
	* @param bufSize	�������ݵ��ֽ���
	* @retval			����Ľ������������Ľ����ֽ���
	*/
	virtual DEALDATAINFO V_ReceiveProc(const UINT8* buf,const INT32 bytes);

	/**
	* @brief			���ͱ�����װ
	* @param buf		�������ݵĻ�����
	* @param bufSize	�������ݵĻ�������С
	* @retval			��װ�Ľ����������װ���ֽ�������Ҫʱ������ָʾ����������·��
	*/
	virtual DEALDATAINFO V_SendProc(UINT8* buf,const INT32 bufSize);

	/*
		ͨ����λ����Ҫ�����TCP���ӣ�IEC104�ȹ�Լ����Ҫ���⴦���
		��Լ���ô�����ֵΪ-1����������ֵΪ1,
		����Ϊ0��ʾԭ�н��յ��ݴ�����Ҫ���
	*/
	virtual INT32 V_ChannelReset();

	/*
		ÿ��ִ�к���,��Ҫ���ڹ�Լ���뼶Ϊ��λ��̫��ȷ�Ķ�ʱ���д����綨ʱ�������ݻ��¶�ʱ�����
		�����������Ϊ��λ���������������ֵϵͳ����ʱ��0��ʼ��ÿ���1��ֻ�����Ӳ����С���������ʱ�޹�
		��������һ���ܱ�֤ÿ�����1�Σ����ʱ���������ͨ�Ŵ����ӳٶ����ʱ���С���̶�
		��Լ���ô�����ֵΪ-1
		��������ֵ>=0,
	*/
	virtual INT32 V_EverySecondProc(INT32 systemPlus1);

public:
	INT32 ParsePacket(const UINT8* buf, const INT32 len);
	INT32 ProcessYkSin(const UINT8* buf, const INT32 len);
	INT32 ProcessYkDin(const UINT8* buf, const INT32 len);
	INT32 ProcessYt(const UINT8* buf, const INT32 len);
	INT32 ProcessSetTime(const UINT8* buf, const INT32 len);  // �����ʱ����

	/**
	* @brief			��װ׼�����ͱ仯ң�ű���
	* @param buf		���͵����ݻ�����
	* @param bufSize	���ͻ�����������ֽ���
	* @retval			��װ���ֽ���
	*/
	INT32 AssembleSendData(UINT8 *buf, const INT32 bufSize);  // ��װ�������ݱ���
	INT32 AssembleSendACK(UINT8 *buf, const INT32 bufSize);  // ACK������װ
	INT32 AssembleSendAskAllReturn(UINT8 *buf, const INT32 bufSize);  // ȫ������Ӧ
	INT32 AssembleSendAllYxData(UINT8 *buf, const INT32 bufSize);  // ȫң�ű�����װ
	INT32 AssembleSendAllYcData(UINT8 *buf, const INT32 bufSize);  // ȫң�ⱨ����װ
	INT32 AssembleSendAllYmData(UINT8 *buf, const INT32 bufSize);  // ȫң��������װ
};
#endif
