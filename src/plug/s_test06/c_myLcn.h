#ifndef _C_MY_LCN_H_
#define _C_MY_LCN_H_

/**
@file �ͻ��˵��Թ�Լͷ�ļ���
@version v1.01
@author 
@date 2012-07-17
˵��������Լ����ϵͳ���ԣ��ᶨ��ģ��һЩ���ݱ仯��
	  ����ԼҲ����Ϊ��Լ����ʾ������ͬʱ��������Լ���ṩһ�����Է������˹�Լ��;����
*/

#include "LcnIF.h"
#include "LcnProc.h"

//���屾��Լϵͳ����
const INT32 P_YX_MAX							= 10000;					// ���ң����
const INT32 P_YC_MAX							=  5000;					// ���ң����
const INT32 P_YM_MAX							=  2000;					// �������
const INT32 P_YK_MAX							=  2000;					// ���ң����
const INT32 P_YT_MAX							=  2000;					// ���ң����

const INT32 MAX_SEND_QUERY_NUM		= 4;							// ��෢�͵Ĳ�ѯ��������,ʵ��Ӧ��Ӧ��ȡ������
const INT32 SetTimeIntSec						= 60;						// ��ʱ���·����ʱ��,ʵ��Ӧ��Ӧ��ȡ������
const INT32 CallAllIntSec						= 120;						// ���ټ��ʱ��

const INT32 MIN_DEV_ADDR					= 0;							// ��ַ����
const INT32 MAX_DEV_ADDR					= 1000;					// ��ַ����
const INT32 MAX_DEV_NUM					= 256;						// װ����������

class CMyLcn_C: public CLcnIF
{
	void *			pIF;		//ϵͳ���������Ĳ����ӿڶ���ָ�룬ÿ����Լ���������ñ���

	BOOL32			isEnglishDebug;												//�Ƿ���Ӣ�ĵ��Ի���
	INT32			nowPulsSec;	//ϵͳ�����ֵ��ϵͳ���������ֵ��0��ʼÿ���1��
	INT32			lastSetTimePulsSec;										//�ϴη��Ͷ�ʱ�����ֵ
	BOOL32			isNeedSetTime;												//��Ҫ���Ͷ�ʱ

	DEALDATAINFO	DataInfo;													//�����շ������ķ��ض���

	INT32			SendQueryNo;												// ����֡˳��
	INT32			DevNum;														// װ������
	INT32			CurrDevNo;													// ��ǰ��ѯװ�����
	INT32			*pDevAddr;													// װ�õ�ַ��
public:

	CMyLcn_C(void);
	virtual ~CMyLcn_C(void);

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
	* @brief			�Խ��ձ��Ľ��д���,NCOMMƽ̨��ʱ���øú���
	* @param buf		�������ݵĻ�����
	* @param bufSize	�������ݵ��ֽ���
	* @retval			����Ľ������������Ľ����ֽ���
	*/
	virtual DEALDATAINFO V_ReceiveProc(const UINT8* buf,const INT32 bytes);

	/**
	* @brief			���ͱ�����װ,NCOMMƽ̨��ʱ���øú�����һ����ȵ���V_ReceiveProc������������ŵ��ñ�����
	* @param buf		�������ݵĻ�����
	* @param bufSize	�������ݵĻ�������С
	* @retval			��װ�Ľ����������װ���ֽ�������Ҫʱ������ָʾ����������·��
	*/
	virtual DEALDATAINFO V_SendProc(UINT8* buf,const INT32 bufSize);

	/*
	* @brief			ͨ����λ��NCOMMƽ̨����ͨ����·�жϺ��ָ�λ�����������øú���,��Ҫ�����TCP���ӣ�ͨ�Ÿ�λ��IEC104�ȹ�Լ����Ҫ���⴦��
	* @retval			��Լ���ô�����ֵΪ-1,��������ֵ>=0
	*/
	virtual INT32 V_ChannelReset();

	/*
	* @brief			ÿ��ִ�к���,��Ҫ���ڹ�Լ���뼶Ϊ��λ��̫��ȷ�Ķ�ʱ���д����綨ʱ�������ݻ��¶�ʱ�����
						�����������Ϊ��λ���������������ֵϵͳ����ʱ��0��ʼ��ÿ���1��ֻ�����Ӳ����С���������ʱ�޹�
						��������һ���ܾ��Ա�֤ÿ�����1�Σ����ʱ���������ͨ�Ŵ����ӳٶ����ʱ���С���̶�
	* @retval			��Լ���ô�����ֵΪ-1,��������ֵ>=0
	*/
	virtual INT32 V_EverySecondProc(INT32 systemPlus1);

public:
	UINT16 CRC16(UINT8* pDataBuf, INT32 DataLen);		// CRCУ������㹫ʽ
	/**
	* @brief			��װ׼�����ͱ���
	* @param buffer		���͵����ݻ�����
	* @param bufferSize ���ͻ�����������ֽ���
	* @retval			��װ���ֽ���
	*/
	INT32 AssembleSendData(UINT8 *buf, const INT32 bufferSize);		// ��װ���ͱ���
	INT32 AssembleNoramlQuery0(UINT8 *buf, const INT32 bufferSize);  //������ѯ0
	INT32 AssembleNoramlQuery1(UINT8 *buf, const INT32 bufferSize);  //������ѯ1
	INT32 AssembleNoramlQuery2(UINT8 *buf, const INT32 bufferSize);  //������ѯ2
    INT32 AssembleNoramlQuery3(UINT8 *buf, const INT32 bufferSize);  //������ѯ3

	/**
	* @brief		�������յ��ı���
	* @param buf	���͵����ݻ�����
	* @param len	���ͻ�����������ֽ���
	* @retval		��ȷ�����ı���
	*/
	INT32 ParsePacket(const UINT8* buf, const INT32 len);		// �����յ�����Ч���ݰ�
	INT32 ProcessHoldingRegister(const UINT8* buf, const INT32 len);	// �����ּĴ���
	INT32 ProcessInputCoil(const UINT8* buf, const INT32 len);				// ����������Ȧ
	INT32 ProcessInputRegister(const UINT8* buf, const INT32 len);		// ��������Ĵ���
};

#endif
