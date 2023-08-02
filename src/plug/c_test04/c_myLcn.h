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

//ͨ����̬�ı�0���ݽṹ
struct Table0DataStruct
{
	CHAR sName[Fr::NAME_LENGTH];
	INT32 DevAddr		;	//װ�õ�ַ

	void SetDefault()
	{
		memset(this, 0, sizeof(*this));
	}
};

//ͨ����̬�ı�1���ݽṹ
struct Table1DataStruct
{	
	INT32		Type;			//��������
	INT32		FunCode;		//������
	INT32		StartAddr;		//��ʼ��ַ
	INT32		QueryNum;	//��ѯ����
	INT32		Offset;			//ƫ����

	void SetDefault()
	{
		memset(this, 0, sizeof(*this));
	}
};

// �ն���������
struct TmnlDataStruct
{
	INT32		YxNum;
	INT32		YcNum;
	INT32		YmNum;
	INT32		YxOffset;
	INT32		YcOffset;
	INT32		YmOffset;

	TmnlDataStruct()
	{
		memset(this, 0, sizeof(*this));
	}
};

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

	Table0DataStruct  *	pParam0;		//ͨ����̬�Ĳ�����0������0��С���̶�����Ҫ��ָ��
	INT32			numParam1;				//ͨ����̬�Ĳ�����1���������̶�����numParam1��ʾ����
	Table1DataStruct  *	pParam1;		//ͨ����̬�Ĳ�����1������1��С���̶�����Ҫ��ָ��
	Table1DataStruct  *	pParam2;		//ͨ����̬�Ĳ�����1������1��С���̶�����Ҫ��ָ��
	INT32			numParam2;	

	INT32			nowPulsSec;	//ϵͳ�����ֵ��ϵͳ���������ֵ��0��ʼÿ���1��
	INT32			lastSetTimePulsSec;										//�ϴη��Ͷ�ʱ�����ֵ
	BOOL32			isNeedSetTime;												//��Ҫ���Ͷ�ʱ

	DEALDATAINFO	DataInfo;													//�����շ������ķ��ض���

	INT32			SendQueryNo;												// ����֡˳��
	INT32			DevNum;														// װ������
	INT32			CurrDevNo;													// ��ǰ��ѯװ�����

	TmnlDataStruct *TmnlDataList;		// �ն����ݲ�����
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
	void GetCfgData();
	UINT16 CRC16(UINT8* pDataBuf, INT32 DataLen);		// CRCУ������㹫ʽ
	/**
	* @brief			��װ׼�����ͱ���
	* @param buffer		���͵����ݻ�����
	* @param bufferSize ���ͻ�����������ֽ���
	* @retval			��װ���ֽ���
	*/
	INT32 AssembleSendData(UINT8 *buf, const INT32 bufferSize);		// ��װ���ͱ���
	INT32 AssembleNoramlQuery(UINT8 *buf, const INT32 bufferSize);  //������ѯ

	/**
	* @brief		�������յ��ı���
	* @param buf	���͵����ݻ�����
	* @param len	���ͻ�����������ֽ���
	* @retval		��ȷ�����ı���
	*/
	INT32 ParsePacket(const UINT8* buf, const INT32 len);		// �����յ�����Ч���ݰ�
	BOOL32 AddrToDevNo(const INT32 Addr, INT32 &DevNo);				// ���յ���װ�õ�ַת����װ�����
	INT32 ProcessCoil(const UINT8* buf, const INT32 len);			// ������Ȧ
	INT32 ProcessRegister(const UINT8* buf, const INT32 len);	// ����Ĵ���
	BOOL32 GetCfgNo(const INT32 Type, const INT32 Bytes, INT32 &No);	// ͨ�����ͺͲ�ѯ�����õ����õ����
};

#endif
