#ifndef _LCN_InterFace_H_
#define _LCN_InterFace_H_

/**
@file ��Լ����ӿ�
@version v1.01
@author 
@date
*/

#include <iostream>
#include "PTOTHERINFO.h"

#ifdef _WINDOWS
#	define LCNIFENTRY __declspec(dllexport)
#else
#	define LCNIFENTRY
#endif

class CLcnIF{
public:
	virtual ~CLcnIF(){};
	
	/*
		ͨ����Լ��ʼ��
	*/
	virtual void	V_NodeInit(void *pIF1)=0;

	/*
		�ر�ͨ����Լ����
	*/
	virtual void	V_NodeDestroy(){};

	//������Ϣ��Ϣ����
	virtual void V_MessageProc(const RelayInfoMsgData *pMsg1){if (pMsg1==NULL) return;};
	
	//������Ϣ����
	virtual void V_MessageProc(const void * pMsg1){if (pMsg1==NULL) return;};

	/*
		�Ը����յ����ݽ��д���
		���ص�DEALDATAINFO.bytes ��ʾʵ���Ѵ�����ֽ���
	*/
	virtual DEALDATAINFO V_ReceiveProc(const UINT8* buffer, const INT32 bytes){DEALDATAINFO Ddi; Ddi.SetDefault(); Ddi.Bytes = bytes; return Ddi;};

	/*
		��װ׼�����ͱ���
		������װ�ֽ����������־����־����ͨѶ����Ҫ���½�����·���ӵ�
		���ص�DEALDATAINFO.bytes ��ʾ������ʵ����Ҫ���͵��ֽ���
	*/
	virtual DEALDATAINFO V_SendProc(UINT8* buffer, const INT32 bufferSize){DEALDATAINFO Ddi; Ddi.SetDefault(); return Ddi;};

	/*
		ͨ����λ��ͨ�����´����µ����ӳɹ������ô˺�������Ҫ�����TCP���ӣ���IEC104�ȹ�Լ����Ҫ���⴦���
		��Լ���ô�����ֵΪ-1����������ֵΪ1,
		����Ϊ0��ʾԭ�н��յ��ݴ�����Ҫ���
	*/
	virtual INT32 V_ChannelReset(){return -1;};

	/*
		ÿ��ִ�к���,��Ҫ���ڹ�Լ���뼶Ϊ��λ��̫��ȷ�Ķ�ʱ���д����綨ʱ�������ݻ��¶�ʱ�����
		�����������Ϊ��λ���������������ֵϵͳ����ʱ��0��ʼ��ÿ���1��ֻ�����Ӳ����С���������ʱ�޹�
		��������һ���ܱ�֤ÿ�����1�Σ����ʱ���������ͨ�Ŵ����ӳٶ����ʱ���С���̶�
		����ֵ����������
	*/
	virtual INT32 V_EverySecondProc(INT32 systemPlus1){return systemPlus1;};
};

//������Լ��������ʵ����
typedef CLcnIF* (*Create_node)();

//�ͷŹ�Լ��������ʵ����
typedef void (*Destroy_node)(CLcnIF*);

//�õ���Լ����˵����
typedef LPSTR (*GetIdentify_t)(PTOTHERINFO &);

#endif
