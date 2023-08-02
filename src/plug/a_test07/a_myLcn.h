#ifndef _A_MY_LCN_H_
#define _A_MY_LCN_H_

/**
@file Ӧ�ù���ʾ��ͷ�ļ���
@version v1.01
@author 
@date 2016-12-21
*/

#include "LcnIF.h"
#include "LcnProc.h"

// Ӧ��������ýṹ
struct AppCfgDef
{
	INT32		secSpace;		// ÿ�����Ƶļ������
	FrDataIdx	ycFdiWarm;	// ���õ�ǰ�¶�λ��
	FrDataIdx	yxFdi;			// ����������״̬λ��
	FrDataIdx	ykFdi;			// ����������Ͷ�˵Ĳ�������λ��

	FrDataIdx	ytFdiWarm;	// ���õ�ǰ�¶�λ��

	void SetDefault()
	{
		memset(this, 0, sizeof(*this));
	}
};

class CMyLcn_A: public CLcnIF
{
	void *		pIF;
	BOOL32		isEnglishDebug;		//�Ƿ���Ӣ�ĵ��Ի���
	INT32		nowPulsSec;			//ϵͳ�����ֵ��ϵͳ���������ֵ��0��ʼÿ���1
	INT32		checkPlusSec;		//�ϴμ���ж�ʱ��

	AppCfgDef	 cfg;						//ͨ����̬�Ĳ�����0������0�̶�Ϊ1���ṹ
	DEALDATAINFO	DataInfo;		//�����շ������ķ��ض���

public:

	CMyLcn_A(void);
	virtual ~CMyLcn_A(void);

	/**
	* @brief		 ��ʼ����Լ׼�����еĲ�����ϵͳ�����нڵ�ȫ����ʼ����ſ�ʼ�������߳̽��и���ͨѶ�շ�����
	* @param pFrApi1 ϵͳ���������Ĳ����ӿڶ���ָ��
	**/
	virtual void V_NodeInit(void *pIF1);

	/*
	* @brief			ÿ��ִ�к���,��Ҫ���ڹ�Լ���뼶Ϊ��λ��̫��ȷ�Ķ�ʱ���д����綨ʱ�������ݻ��¶�ʱ�����
						�����������Ϊ��λ���������������ֵϵͳ����ʱ��0��ʼ��ÿ���1��ֻ�����Ӳ����С���������ʱ�޹�
						��������һ���ܾ��Ա�֤ÿ�����1�Σ����ʱ���������ͨ�Ŵ����ӳٶ����ʱ���С���̶�
	* @retval			��Լ���ô�����ֵΪ-1,��������ֵ>=0
	*/
	virtual INT32 V_EverySecondProc(INT32 systemPlus1);

public:
	void YkYtCheck();					// ����Ƿ���ң�ء�ң��
	void AutoControlProc();			// ��ʱִ�е��Զ����ƹ��ܺ���
};

#endif
