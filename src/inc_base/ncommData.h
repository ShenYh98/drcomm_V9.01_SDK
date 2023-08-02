#ifndef _NCOMM_DATA_H_
#define _NCOMM_DATA_H_

/****************************************************************
 *          ncommData.h  
 *      Copyright (C) 2015, 
 *                  ALL RIGHTS RESERVED
 *
 * �޸ļ�¼ : 
 *      2015.12.30, �����ļ�, 
 * 
 * 
 *****************************************************************/

#include <string>
#include <fstream>
#include <memory.h>
#include "PubDef.h"

#ifdef _WINDOWS
#	ifdef NCOMMDATA_EXPORTS
#		define NCOMMDATA_API __declspec(dllexport)
#	else
#		define NCOMMDATA_API __declspec(dllimport)
#	endif

#	ifndef NCOMMDATA_EXPORTS
#		pragma comment(lib,"ncommData.lib")
#		pragma message("Automatically linking with ncommData.dll")
#	endif
#else
#	define NCOMMDATA_API
#endif

struct NcommYxData{
	INT32  iValue;		//ң������״̬��0-�֣�1-��
	INT32  flgQ;		//����Ʒ��,�����PubDef.h��QBit��ͷ�ĳ���,flgQ & QBitNotUpdate���ΪTRUE��ʾ���ݲ�ˢ�£�flgQ & QBitFault���ΪTRUE��ʾ�����쳣
	INT64  tmRefresh;	//ˢ��ʱ�䣬��1970.1.1��㿪ʼ�İ�������,���ú���NcommData::Int64ToSystemtime����ʱ��ת��
};

struct NcommAiData{
	FLOAT32 fValue;		//ģ��������ֵ
	INT32  flgQ;		//����Ʒ��,�����PubDef.h��QBit��ͷ�ĳ���,flgQ & QBitNotUpdate���ΪTRUE��ʾ���ݲ�ˢ�£�flgQ & QBitFault���ΪTRUE��ʾ�����쳣
	INT64  tmRefresh;	//ˢ��ʱ�䣬��1970.1.1��㿪ʼ�İ�������,���ú���Int64ToSystemtime����ʱ��ת��
};

class NCOMMDATA_API  NcommData {
public:
	NcommData();
	~NcommData();

public:

	/**
	* @brief	��NcommYxData��NcommAiData�е�ˢ��ʱ��ת��ΪSYSTEMTIMEʱ��
	*           �������ֱ�Ӵ�pYxData��pYcData��pYmData�ж�ȡ����
	* @param tm1	INT64��ʱ�䣬��1970.1.1��㿪ʼ�İ�������
	* @param pSt1	ת��Ϊ�ꡢ�¡��ա�ʱ���֡��롢��������ݸ�ʽ
	* @retval	����FALSE,��ʾת��ʧ��
	*/
	static BOOL32 Int64ToSystemtime(const INT64 tm1, SYSTEMTIME * pSt1);

	/**
	* @brief	��ʼ����ȡncomm���ݵĽӿڣ��ú�������tcp client ģʽ����ncomm��ncomm�����s_sample��Լ��tcp server��ʽ���ڷ�������
	* @param mode1	��ȡncomm���ݵ�ģʽ��Ŀǰֻ֧��ֵΪ0��ģʽ
	* @param szIp1	�ṩ���ݵ�ncomm��IP��ַ����ʽ�磺192.168.1.1
	* @param port1	�ṩ���ݵ�ncomm�Ķ˿ں�
	* @param numYx1	������ң������
	* @param numYc1	������ң������
	* @param numYm1	������ң��������ң�������
	*/
	void Init(INT32 mode1, const char *szIp1, UINT16 port, INT32 numYx1, INT32 numYc1, INT32 numYm1=0);

	/**
	 * @brief ��ң�أ�������˹�Լ����
	 * @param pIF1		��Լ�����ӿڶ���
	 * @param Action1	ң�����ʣ�Fr::YK_ON(��)�� Fr::YK_OFF���֣�
	 * @param ObjectNo1 ң�ض���ţ��ڵ��е�ң�ض�����ţ�
	 * @param State1	ң��״̬,YKYT_SELECT(ң��ң��ѡ��)��YK_EXE(ң��ִ��)��YK_RMV(ң�س���)
	 * @param IsDinYk1	�Ƿ�Ϊ˫��ң��
	 * @retval	����ֵ<0��ʾʧ��
	 */
	INT32  DoYk(void *pIF1, INT32 Action1, INT32 ObjectNo1, INT32 State1, BOOL32 IsDinYk1=FALSE);

	/**
	 * @brief ������ֵң����������˹�Լ����
	 * @param pIF1		��Լ�����ӿڶ���
	 * @param Action1	ң�����ʣ�Fr::YT_OUT(���)�� Fr::YT_UP�������� Fr::YT_DOWN������,YT_STOP����ֹ��
	 * @param ObjectNo1	ң������ţ��ڵ��е�ң��������ţ�
	 * @param Value1	ң��ֵ
	 * @param State1	ң��״̬,YKYT_SELECT(ң��ң��ѡ��)��YT_EXE(ң��ִ��)��YT_RMV(ң������)
	 * @retval	����ֵ<0��ʾʧ��
	 */
	INT32  DoYtInteger(void *pIF1, INT32 Action1, INT32 ObjectNo1, INT32 Value1, INT32 State1);

	/**
	 * @brief ��������ֵң����������˹�Լ����
	 * @param pIF1		��Լ�����ӿڶ���
	 * @param Action1	ң�����ʣ�Fr::YT_OUT(���)�� Fr::YT_UP�������� Fr::YT_DOWN������,YT_STOP����ֹ��
	 * @param ObjectNo1 ң������ţ��ڵ��е�ң��������ţ�
	 * @param Value1	ң��ֵ
	 * @param State1	ң��״̬,YKYT_SELECT(ң��ң��ѡ��)��YT_EXE(ң��ִ��)��YT_RMV(ң������)
	 * @retval	����ֵ<0��ʾʧ��
	 */
	INT32  DoYtFloat(void *pIF1, INT32 Action1, INT32 ObjectNo1, FLOAT32 Value1, INT32 State1);


public:
	INT32 numYx;
	INT32 numYc;
	INT32 numYm;
	NcommYxData *pYxData;
	NcommAiData *pYcData;
	NcommAiData *pYmData;

	INT32 ip;
	UINT16 port;

	void *pHandle;  //�ڲ��õ��м����
};

#endif
