#include "c_myLcn.h"

/**
 @brief �����̬���������Զ����ɲ������
 @param pHandle	   ��̬�ӿڶ���ָ��
 @param pNodeReadmeInfo �ڵ����������Ϣ
 @param pCfgDef	   ͨ����̬�����Ĵ������
 @param lenNote	   szNote�Ŀռ�
 @param szNote	   ���صĲ�����������ʾ
 @retval ���ز���״̬
 */
#ifdef _WINDOWS

// ��ConfigTool.exe�ڵ���̬���ѡ�С�ȷ���޸ġ����ͻ���ô˺���
extern "C" LCNIFENTRY INT32 CheckConfigAndCreatePoint(void *pHandle, const NodeReadmeInfo *pNodeReadmeInfo, CCommonCfgDef * pCfgDef, INT32 lenNote=0, CHAR *szNote=NULL)
{

	/////////////////////////////////////////////////////////////////////////////////////
	// Ԥ�����ͨ����̬�������ݽṹ�Ĵ��롣
	/////////////////////////////////////////////////////////////////////////////////////

	return 0;
}

#endif
