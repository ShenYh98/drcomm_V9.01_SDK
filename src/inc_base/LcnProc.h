#ifndef _LCN_PROC_H_
#define _LCN_PROC_H_

#include "PTOTHERINFO.h"
#include "LcnStructDef.h"

#ifdef _WINDOWS
#	ifdef LCN_PROC_EXPORTS
#		define LCNPROCENTRY __declspec(dllexport)
#	else
#		define LCNPROCENTRY __declspec(dllimport)
#	endif

#	ifndef LCN_PROC_EXPORTS
#		pragma comment(lib,"lcnProc.lib")
#		pragma message("Automatically linking with lcnProc.dll")
#	endif
#else
#	define LCNPROCENTRY
#endif

/**
 @brief			�õ�ϵͳ�����������ֵ��ϵͳ������ʼ������ÿ���1
 @param pIF1	��Լ�����ӿڶ���
 @retval		��������Ч�򷵻�<0
 */
extern "C" LCNPROCENTRY INT32  LCN_GetSystemPuls(void *pIF1);

/**
 @brief			���ý��յ��ܻ�������
 @param pIF1	��Լ�����ӿڶ���
 @param num1	��������
 @retval		����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32  LCN_SetRecvBadPackage(void *pIF1, INT32 num1);

/**
 @brief			���ý��յĺð�����
 @param pIF1	��Լ�����ӿڶ���
 @param num1	�ð�����
 @retval		����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32  LCN_SetRecvGoodPackage(void *pIF1, INT32 num1);

/**
 @brief			���÷��͵İ�����
 @param pIF1	��Լ�����ӿڶ���
 @param num1	���͵İ�����
 @retval		����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32  LCN_SetSendPackage(void *pIF1, INT32 num1);

/**
 @brief			����ң��ֵ
 @param pIF1	��Լ�����ӿڶ���
 @param No		�ڵ��ң�����
 @param iValue	ң��ֵ
 @param flgQ	Ʒ�ʣ���λ�����Fr::QBit::
 @retval		����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32 LCN_SetYx(void *pIF1, INT32 No, INT32 iValue, INT32 flgQ=0);

/**
 @brief			��SYSTEMTIMEʱ���ʽ֪ͨϵͳ��SOE
 @param pIF1	��Լ�����ӿڶ���
 @param No		�ڵ��ң�����
 @param tm		SOE����ʱ��
 @param iValue	ң��ֵ
 @param flgQ	Ʒ�ʣ���λ�����Fr::QBit::
 @retval		����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32 LCN_SetSoe(void *pIF1, INT32 No, SYSTEMTIME st, INT32 iValue, INT32 flgQ=0);

/**
 @brief			��INT64ʱ���ʽ֪ͨϵͳ��SOE
 @param pIF1	��Լ�����ӿڶ���
 @param No		�ڵ��ң�����
 @param tm		SOE����ʱ��
 @param iValue	ң��ֵ
 @param flgQ	Ʒ�ʣ���λ�����Fr::QBit::
 @retval		����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32 LCN_SetSoe2(void *pIF1, INT32 No, INT64 tm, INT32 iValue, INT32 flgQ=0);

/**
 @brief			���ø�����ң��ֵ
 @param pIF1	��Լ�����ӿڶ���
 @param No		�ڵ��ң�����
 @param fValue	ң��ֵ
 @param flgQ	Ʒ�ʣ���λ�����Fr::QBit::
 @retval		����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32  LCN_SetYcFloat(void *pIF1, INT32 No, FLOAT32 fValue, INT32 flgQ=0);

/**
 @brief			��������ң��ֵ
 @param pIF1	��Լ�����ӿڶ���
 @param No		�ڵ��ң�����
 @param iValue	ң��ֵ
 @param flgQ	Ʒ�ʣ���λ�����Fr::QBit::
 @retval		����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32  LCN_SetYcInteger(void *pIF1, INT32 No, INT32 iValue, INT32 flgQ=0);

/**
 @brief			���ø���ң��ֵ
 @param No		�ڵ��ң�����
 @param fValue	ң��ֵ
 @param flgQ	Ʒ�ʣ���λ�����Fr::QBit::
 @retval		����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32  LCN_SetYmFloat(void *pIF1, INT32 No, FLOAT32 fValue, INT32 flgQ=0);

/**
 @brief			��������ң��ֵ
 @param No		�ڵ��ң�����
 @param iValue	ң��ֵ
 @param flgQ	Ʒ�ʣ���λ�����Fr::QBit::
 @retval		����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32  LCN_SetYmInteger(void *pIF1, INT32 No, UINT32 iValue, INT32 flgQ=0);

/**
 @brief				֪ͨϵͳң�ط��أ����ͻ��˹�Լ����
 @param pIF1		��Լ�����ӿڶ���
 @param Action1		ң�����ʣ�Fr::YK_ON(��)�� Fr::YK_OFF���֣�
 @param ObjectNo1	ң�ض���ţ��ڵ��е�ң�ض�����ţ�
 @param State1		ң�ط���״̬,YK_ACK(ң��ѡ��У��ȷ)��YK_NAK(ң��ѡ��У����)��YK_EXE(ң��ִ��ȷ��)��YK_RMV(ң�س���ȷ��)��
 @param IsDinYk1	�Ƿ�Ϊ˫��ң��
 @retval			����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32  LCN_SetYkReturn(void *pIF1, INT32 Action1, INT32 ObjectNo1, INT32 State1, BOOL32 IsDinYk1=FALSE);

/**
 @brief				֪ͨϵͳң�����أ����ͻ��˹�Լ����
 @param pIF1		��Լ�����ӿڶ���
 @param Action1		ң�����ʣ�Fr::YT_OUT(���)�� Fr::YT_UP�������� Fr::YT_DOWN������,YT_STOP����ֹ��
 @param ObjectNo1	ң������ţ��ڵ��е�ң��������ţ�
 @param State1		ң������״̬,YK_ACK(ң��ѡ��У��ȷ)��YK_NAK(ң��ѡ��У����)��YT_EXE(ң��ִ��ȷ��)��YT_RMV(ң������ȷ��)��
 @retval			����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32  LCN_SetYtReturn(void *pIF1, INT32 Action1, INT32 ObjectNo1, INT32 State1);


/**
 @brief				��ң�أ�������˹�Լ����
 @param pIF1		��Լ�����ӿڶ���
 @param Action1		ң�����ʣ�Fr::YK_ON(��)�� Fr::YK_OFF���֣�
 @param ObjectNo1	ң�ض���ţ��ڵ��е�ң�ض�����ţ�
 @param State1		ң��״̬,YKYT_SELECT(ң��ң��ѡ��)��YK_EXE(ң��ִ��)��YK_RMV(ң�س���)
 @param IsDinYk1	�Ƿ�Ϊ˫��ң��
 @retval			����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32  LCN_DoYk(void *pIF1, INT32 Action1, INT32 ObjectNo1, INT32 State1, BOOL32 IsDinYk1=FALSE);

/**
 @brief				������ֵң����������˹�Լ����
 @param pIF1		��Լ�����ӿڶ���
 @param Action1		ң�����ʣ�Fr::YT_OUT(���)�� Fr::YT_UP�������� Fr::YT_DOWN������,YT_STOP����ֹ��
 @param ObjectNo1	ң������ţ��ڵ��е�ң��������ţ�
 @param Value1		ң��ֵ
 @param State1		ң��״̬,YKYT_SELECT(ң��ң��ѡ��)��YT_EXE(ң��ִ��)��YT_RMV(ң������)
 @retval			����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32  LCN_DoYtInteger(void *pIF1, INT32 Action1, INT32 ObjectNo1, INT32 Value1, INT32 State1);

/**
 @brief				��������ֵң����������˹�Լ����
 @param pIF1		��Լ�����ӿڶ���
 @param Action1		ң�����ʣ�Fr::YT_OUT(���)�� Fr::YT_UP�������� Fr::YT_DOWN������,YT_STOP����ֹ��
 @param ObjectNo1	ң������ţ��ڵ��е�ң��������ţ�
 @param Value1		ң��ֵ
 @param State1		ң��״̬,YKYT_SELECT(ң��ң��ѡ��)��YT_EXE(ң��ִ��)��YT_RMV(ң������)
 @retval			����ֵ<0��ʾʧ��
 */
extern "C" LCNPROCENTRY INT32  LCN_DoYtFloat(void *pIF1, INT32 Action1, INT32 ObjectNo1, FLOAT32 Value1, INT32 State1);

/*
 @brief				ֱ�ӷ�ң�����������Ӧ����ڵ����
 @param pIF1		��Լ�����ӿڶ���
 @param fdiYt1		ִ�е�ң��������
 @param fv1			�����ֵ
 @param action1		�������ʣ������Fr::YT_OUT��
 @param isCheck1	��鵱ǰֵ��ΪTRUEʱ�������ǰֵ���趨ֵ��ͬʱ�������������
 @return			����ֵ�����Fr::YKYT_R_
*/
extern "C" LCNPROCENTRY INT32	LCN_DoYtDirectExe(void *pIF1, FrDataIdx fdiYt1, FLOAT32 fv1, INT32 action1=Fr::YT_OUT, BOOL32 isCheck1=FALSE);

/*
 @brief				ֱ�ӷ�ң�����������Ӧ����ڵ����
 @param pIF1		��Լ�����ӿڶ���
 @param fdiYk1		ִ�е�ң�ض�����
 @param action1		�������ʣ������Fr::YK_OFF��
 @param state1		ң��״̬��ң��ִ��YK_EXE��ң�س���YK_RMV
 @param isCheck1	��鵱ǰֵ��ΪTRUEʱ�������ǰֵ���趨ֵ��ͬʱ�������������
 @return			����ֵ�����Fr::YKYT_R_
*/
extern "C" LCNPROCENTRY INT32	LCN_DoYkDirectExe(void *pIF1, FrDataIdx fdiYk1, INT32 action1, INT32 state1=Fr::YK_EXE, BOOL32 isCheck1=FALSE);

/**
 @brief			����INT64��ʱ����SYSTEMTIMEʱ��
 @param tm1		INT64ʱ�䣬��1970�꿪ʼ�İ�������
 @param pSt1	��õ�SYSTEMTIMEʱ��
 @retval		ת���ɹ���
 */
extern "C" LCNPROCENTRY BOOL32 LCN_Int64ToSystemtime(const INT64 tm1, SYSTEMTIME * pSt1);

/**
 @brief			����Systemtime��ʱ����INT64ʱ��
 @param st		SYSTEMTIMEʱ��
 @param pTm1	��õ�INT64ʱ��
 @retval		ת���ɹ���
 */
extern "C" LCNPROCENTRY BOOL32 LCN_SystemtimeToInt64(const SYSTEMTIME st1, INT64 *pTm1);

/**
 @brief			��õ�ǰSYSTEMTIMEʱ��
 @param pSt1	��õ�SYSTEMTIMEʱ��
 */
extern "C" LCNPROCENTRY void LCN_GetCurrSystemtime(SYSTEMTIME * pSt1);

/**
 @brief			���������Ϣ
 @param szNote1 ������Ϣ
 */
extern "C" LCNPROCENTRY void LCN_ToDebugMsg(void *pIF1, const CHAR *szNote1);

/**
 @brief					���ͨ���������Ϣ
 @param procType1		ͨ��������ͣ������DebugCodeHead::eRecv��
 @param len1			ͨ�����ֽڳ���
 @param buf1			ͨ���뻺����
 @param yourAddress1	ͨ�����Ӧ�ĶԷ���ַ,�����Լ==0��ʾ���ޣ����ڹ�Լ<0��ʾ����
 @param flgInfor1		ͨ�����Ӧ����Ϣ֡���, �����DebugCodeHead::eFrameYx��
 */
extern "C" LCNPROCENTRY void LCN_ToDebugCode(void *pIF1, INT32 procType1, INT32 len1, UINT8 *buf1, INT32 yourAddress1=0, INT32 flgInfor1=-1);

/**
 @brief			��ýڵ�Ķ�ʱ��ʽ
 @param pIF1	��Լ�����ӿڶ���
 @retval		���ض�ʱ��ʽ�������Fr::TimeCheck::
 */
extern "C" LCNPROCENTRY INT32 LCN_GetTimeCheck(void *pIF1);

/**
 @brief			��ýڵ���ң������������
 @param pIF1	��Լ�����ӿڶ���
 @param pFactRtuCapacity ��õ������ṹ��
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32 LCN_GetNodeDataCapacity(void *pIF1, FactRtuCapacity *pFactRtuCapacity);

/**
 @brief			����ncomm�豸ʱ��
 @param pIF1	��Լ�����ӿڶ���
 @param st1		���õ�ʱ��
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32 LCN_ModifyMachineTime(void *pIF1, SYSTEMTIME st1);

/**
 @brief			�õ���Լ����
 @param pIF1	��Լ�����ӿڶ���
 @param pPtOtherInfo ��õĹ�Լ����
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32 LCN_GetProtocolIdentify(void *pIF1, PTOTHERINFO *pPtOtherInfo);

/**
 @brief			�õ���̬����
 @param pIF1	��Լ�����ӿڶ���
 @param pSize	��̬buf�ĳ���
 @retval		������̬��bufָ��
 */
extern "C" LCNPROCENTRY INT8 *LCN_GetZtBuf(void *pIF1, INT32 *pSize);


/**
 @brief			�õ�ת������
 @param pIF1	��Լ�����ӿڶ���
 @retval		����ת����ָ��
 */
extern "C" LCNPROCENTRY const FrTransMapBase *LCN_GetTransMap(void *pIF1);

/**
 @brief			 �õ���ǰң��ң����Ϣ
 @param pIF1	 ��Լ�����ӿڶ���
 @param msgData1 ��õ���Ϣ����
 @retval		 ������Ϣ�������
 */
extern "C" LCNPROCENTRY BOOL32  LCN_GetYkYtMsgData(void *pIF1, YkYtMsg *pMsgData1);

/**
 @brief			�õ���ǰ�仯ң������
 @param pIF1	��Լ�����ӿڶ���
 @retval		���ر仯ң������
 */
extern "C" LCNPROCENTRY INT32  LCN_GetYxMsgNum(void *pIF1);

/**
 @brief			�õ���ǰ�仯ң�ţ�����num1Ϊ0�Լ�pMsg1ΪNULL,��ʾ���������Ϣ,ת����Լ�ڷ���ȫ����ǰӦ�����������Ϣ
 @param pIF1	��Լ�����ӿڶ���
 @param num1	��Ϣ�ķ��ػ��������ɱ��������
 @param pMsg1	������Ϣ�Ļ�����
 @retval		����ʵ�ʻ�õı仯ң������
 */
extern "C" LCNPROCENTRY INT32  LCN_GetYxMsg(void *pIF1, const INT32 num1, YxMsg *pMsg1);

/**
 @brief			�õ���ǰSOE����
 @param pIF1	 ��Լ�����ӿڶ���
 @retval		���ر仯SOE����
 */
extern "C" LCNPROCENTRY INT32  LCN_GetSoeNum(void *pIF1);

/**
 @brief			�õ���ǰSOE������num1Ϊ0�Լ�pMsg1ΪNULL,��ʾ���������Ϣ,ת����Լ�ڷ���ȫ����ǰӦ�����������Ϣ
 @param pIF1	��Լ�����ӿڶ���
 @param num1	��Ϣ�ķ��ػ��������ɱ��������
 @param pMsg1	������Ϣ�Ļ�����
 @retval		����ʵ�ʻ�õı仯SOE����
 */
extern "C" LCNPROCENTRY INT32  LCN_GetSoe(void *pIF1, const INT32 num1, SoeMsg *pMsg1);

/**
 @brief			�õ���ǰ�仯ң������
 @param pIF1	��Լ�����ӿڶ���
 @retval		���ر仯ң������
 */
extern "C" LCNPROCENTRY INT32  LCN_GetYcMsgNum(void *pIF1);

/**
 @brief			�õ���ǰ�仯ң�⣬����num1Ϊ0�Լ�pMsg1ΪNULL,��ʾ���������Ϣ,ת����Լ�ڷ���ȫ����ǰӦ�����������Ϣ
 @param pIF1	��Լ�����ӿڶ���
 @param num1	��Ϣ�ķ��ػ��������ɱ��������
 @param pMsg1	������Ϣ�Ļ�����
 @retval		����ʵ�ʻ�õı仯ң������
 */
extern "C" LCNPROCENTRY INT32  LCN_GetYcMsg(void *pIF1, const INT32 num1, YcMsg *pMsg1);

/**
 @brief			�õ���ǰ�仯ң������
 @param pIF1	��Լ�����ӿڶ���
 @retval		���ر仯ң������
 */
extern "C" LCNPROCENTRY INT32  LCN_GetYmMsgNum(void *pIF1);

/**
 @brief			�õ���ǰ�仯ң��������num1Ϊ0�Լ�pMsg1ΪNULL,��ʾ���������Ϣ,ת����Լ�ڷ���ȫ����ǰӦ�����������Ϣ
 @param pIF1	��Լ�����ӿڶ���
 @param num1	��Ϣ�ķ��ػ��������ɱ��������
 @param pMsg1	������Ϣ�Ļ�����
 @retval		����ʵ�ʻ�õı仯ң������
 */
extern "C" LCNPROCENTRY INT32  LCN_GetYmMsg(void *pIF1, const INT32 num1, YmMsg *pMsg1);

/**
 @brief			���ý�����Ϣ֪ͨ״̬
 @param pIF1	��Լ�����ӿڶ���
 @param pMsgNotifyDef	 ��Ϣ����
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32  LCN_SetMsgNotifyDef(void *pIF1, MsgNotifyDef *pMsgNotifyDef);

/**
 @brief			�õ����ڵ��ң������
 @param pIF1	��Լ�����ӿڶ���
 @param no1		ң�����ݵ��
 @param pData1	ң������
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32  LCN_GetYxData(void *pIF1, INT32 no1, YxData *pData1);

/**
 @brief			�õ����ڵ��ң������
 @param pIF1	��Լ�����ӿڶ���
 @param no1		ң�����ݵ��
 @param pData1	ң������
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32  LCN_GetYcData(void *pIF1, INT32 no1, YcData *pData1);

/**
 @brief			�õ����ڵ��ң������
 @param pIF1	��Լ�����ӿڶ���
 @param no1		ң�����ݵ��
 @param pData1	ң������
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32  LCN_GetYmData(void *pIF1, INT32 no1, YmData *pData1);

/**
 @brief			�õ����ڵ��ң������
 @param pIF1	��Լ�����ӿڶ���
 @param no1		ң�����ݵ��
 @param pData1	ң������
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32  LCN_GetYkData(void *pIF1, INT32 no1, YkData *pData1);

/**
 @brief			�õ����ڵ��ң������
 @param pIF1	��Լ�����ӿڶ���
 @param no1		ң�����ݵ��
 @param pData1	ң������
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32  LCN_GetYtData(void *pIF1, INT32 no1, YtData *pData1);


/**
 @brief			�õ�ָ���ڵ��ң������
 @param pIF1	��Լ�����ӿڶ���
 @param fdi1	ң�����ݶ���
 @param pData1	ң������
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32  LCN_SGetYxData(void *pIF1, FrDataIdx fdi1, YxData *pData1);

/**
 @brief			�õ�ָ���ڵ��ң������
 @param pIF1	��Լ�����ӿڶ���
 @param fdi1	ң�����ݶ���
 @param pData1	ң������
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32  LCN_SGetYcData(void *pIF1, FrDataIdx fdi1, YcData *pData1);

/**
 @brief			�õ�ָ���ڵ��ң������
 @param pIF1	��Լ�����ӿڶ���
 @param fdi1	ң�����ݶ���
 @param pData1	ң������
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32  LCN_SGetYmData(void *pIF1, FrDataIdx fdi1, YmData *pData1);

/**
 @brief			�õ�ָ���ڵ��ң������
 @param pIF1	��Լ�����ӿڶ���
 @param fdi1	ң�����ݶ���
 @param pData1	ң������
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32  LCN_SGetYkData(void *pIF1, FrDataIdx fdi1, YkData *pData1);

/**
 @brief			�õ�ָ���ڵ��ң������
 @param pIF1	��Լ�����ӿڶ���
 @param fdi1	ң�����ݶ���
 @param pData1	ң������
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32  LCN_SGetYtData(void *pIF1, FrDataIdx fdi1, YtData *pData1);

/**
 @brief ������������,����1024�ֽڳ������ƣ����Դ��������ʾ1000�ֽڵ���Ϣ���������ú��ӳ�10ms��
		�ýӿ����ã�������������ε���ʱ��ע�Ᵽ���㹻�����ӳ٣��ӳٲ������������ݷ������ʧ��
		�����Լ����ȴ�V_SendProc���������÷��͵�����,V_SendProc�����ļ��ʱ������̬���ƣ���������Ϊ1024�ֽ�
 @param pIF1		��Լ�����ӿڶ���
 @param bytes1		���͵����ݳ���
 @param dataBuf1	���͵����ݻ�����
 @param iDataType	���͵�����֡���ͣ�ÿλ�����Fr::FrameType
 @param iChannel1	==0��ͨ������, ==1��ͨ��1���ͣ� ==2��ͨ��2���ͣ� == 3ͨ��1��2ͬʱ����
 @retval			����ʵ�ʷ��͵��ֽ�����<0 ʧ��
 */
extern "C" LCNPROCENTRY INT32 LCN_SendDataImmediate(void *pIF1, INT32 bytes1, UINT8 *dataBuf1, INT32 iDataType=0, INT32 iChannel1 = 0);

/**
 @brief			˫ͨ���л�
 @param pIF1	��Լ�����ӿڶ���
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32	LCN_SwitchChannel(void *pIF1);

/**
 @brief			�õ��ڵ㶨����Ϣ
 @param pIF1	��Լ�����ӿڶ���
 @param pNodeReadmeInfo		�ڵ㶨�����ݶ���ָ��
 @param pData1	�ڵ㶨�����ݶ���ߴ磬��Ҫ�ǿ���NodeReadmeInfo�ṹ���ܰ汾����
 @retval		���سɹ���
 */
extern "C" LCNPROCENTRY BOOL32	LCN_GetNodeReadmeInfo(void *pIF1, NodeReadmeInfo *pNodeReadmeInfo, INT32 size1);

/**
 @brief			 ���ò������,��Լ��̬ʱ��
 @param pHandle	 ��̬�ӿڶ���ָ��
 @param dataSort ������𣬶������Fr::DataSort:
 @param num		 �������
 */
extern "C" LCNPROCENTRY void	LCN_CfgSetNodeDataNum(void *pHandle, const INT32 dataSort, const INT32 num);

/**
 @brief			 ���ò������,��Լ��̬ʱ��
 @param pHandle	 ��̬�ӿڶ���ָ��
 @param dataSort ������𣬶������Fr::DataSort:
 @param no		 ������
 @param name 	 �������
 */
extern "C" LCNPROCENTRY void	LCN_CfgSetNodeDataName(void *pHandle, const INT32 dataSort, const INT32 no, const char *name);

/**
 @brief			�ж���̬�Ƿ�ΪӢ��
 @param pHandle	��̬�ӿڶ���ָ��
 @retval		���������
 */
extern "C" LCNPROCENTRY BOOL32	LCN_CfgIsEnglish(void *pHandle);

/**
 @brief			 ���汾�ڵ������ֵ����Ҫ��Ӧ����ڵ����
 @param pIF1	 ��Լ�����ӿڶ���
 @param dataSort ������𣬶������Fr::DataSort:
 @retval		 ʧ�ܷ���-1����������0
 */
extern "C" LCNPROCENTRY INT32	LCN_SaveNodeData(void *pIF1, INT32 dataSort1);

/**
 @brief			�жϽڵ��Ƿ�����
 @param pIF1	��Լ�����ӿڶ���
 @param noNode1 �жϵĽڵ��
 @retval		�ڵ����з���TRUE�� �ڵ�ͣ�˷���FALSE
 */
extern "C" LCNPROCENTRY BOOL32	LCN_IsNodeRun(void *pIF1, INT32 noNode1);

/**
 @brief			������չ����
 @param pIF1	��Լ�����ӿڶ���
 @retval		���з���0�� ʧ�ܷ���-1
 */
extern "C" LCNPROCENTRY INT32	LCN_SaveNodeExtraData(void *pIF1);

/**
 @brief			����ָ���ڵ����չ����ͷ����
 @param pIF1	��Լ�����ӿڶ���
 @param numNe	�ڵ���չ��������
 @param pNeh	�ڵ���չ����ͷ����
 @retval		�ɹ�����TRUE�� ʧ�ܷ���FALSE
 */
extern "C" LCNPROCENTRY BOOL32	LCN_SetNodeExtraDataDefine(void *pIF1, INT32 numNe, NodeExtraHead* pNeh);

/**
 @brief			���ñ��ڵ���չ���ݵ�ֵ
 @param pIF1	��Լ�����ӿڶ���
 @param No		�ڵ���չ���ݺ�
 @param tm		�ڵ���չ����ˢ��ʱ��
 @param len		�ڵ���չ����ֵ����
 @param pData	�ڵ���չ����ֵ
 @param flgQ	�ڵ���չ����Ʒ��
 @retval		�ɹ�����TRUE�� ʧ�ܷ���FALSE
 */
extern "C" LCNPROCENTRY BOOL32	LCN_SetMyNodeExtraDataValue(void *pIF1, INT32 No, INT64 tm, INT32 len, void *pData, UINT8 flgQ=0);

/**
 @brief			����ָ���ڵ���չ���ݵ�ֵ
 @param pIF1	��Լ�����ӿڶ���
 @param node	ָ���Ľڵ��
 @param No		�ڵ���չ���ݺ�
 @param tm		�ڵ���չ����ˢ��ʱ��
 @param len		�ڵ���չ����ֵ����
 @param pData	�ڵ���չ����ֵ
 @param flgQ	�ڵ���չ����Ʒ��
 @retval		�ɹ�����TRUE�� ʧ�ܷ���FALSE
 */
extern "C" LCNPROCENTRY BOOL32	LCN_SetNodeExtraDataValue(void *pIF1, INT32 node, INT32 No, INT64 tm, INT32 len, void *pData, UINT8 flgQ=0);

/**
 @brief			���ָ���ڵ��������չ��������
 @param pIF1	��Լ�����ӿڶ���
 @param node	ָ���Ľڵ��
 @retval		���з��������� ʧ�ܷ���-1
 */
extern "C" LCNPROCENTRY INT32	LCN_GetNodeExtraDataNum(void *pIF1, INT32 node);

/**
 @brief			������չ�����������ָ���ڵ����չ���ݺ�
 @param pIF1	��Լ�����ӿڶ���
 @param node	ָ���Ľڵ��
 @param nameExtra ��չ������
 @retval		������չ���ݺţ� ʧ�ܷ���-1
 */
extern "C" LCNPROCENTRY INT32	LCN_GetNodeExtraNo(void *pIF1, INT32 node, CHAR *nameExtra);

/**
 @brief			���ָ���ڵ����չ����ͷ����
 @param pIF1	��Լ�����ӿڶ���
 @param node	ָ���Ľڵ��
 @param No		�ڵ���չ����ͷ������
 @param pNeh	�����Ľڵ���չ����ͷ����
 @retval		�ɹ�����TRUE�� ʧ�ܷ���FALSE
 */
extern "C" LCNPROCENTRY BOOL32	LCN_GetNodeExtraDataDefine(void *pIF1, INT32 node, INT32 num, NodeExtraHead* pNeh);

/**
 @brief			����չ���ݵ�ֵ
 @param pIF1	��Լ�����ӿڶ���
 @param node	ָ���Ľڵ��
 @param No		�ڵ���չ���ݺ�
 @param readLen	��ֵ�����ߴ�
 @param pData	��ֵ�Ĵ洢�ռ�
 @retval		����ֵΪ����ֵ���ȣ�<0��ʾ������
 */
extern "C" LCNPROCENTRY INT32	LCN_GetNodeExtraDataValue(void *pIF1, INT32 node, INT32 No, INT32 readLen, void *pData, INT64 *pTm=NULL, UINT8 *pFlgQ=NULL);

#endif

