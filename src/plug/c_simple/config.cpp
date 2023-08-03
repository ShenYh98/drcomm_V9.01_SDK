#include "c_myLcn.h"

/**
 @brief 检查组态参数，并自动生成测点名称
 @param pHandle	   组态接口对象指针
 @param pNodeReadmeInfo 节点基本配置信息
 @param pCfgDef	   通用组态参数的处理对象
 @param lenNote	   szNote的空间
 @param szNote	   返回的参数检查出错提示
 @retval 返回操作状态
 */
#ifdef _WINDOWS

// 当ConfigTool.exe节点组态完毕选中“确认修改”，就会调用此函数
extern "C" LCNIFENTRY INT32 CheckConfigAndCreatePoint(void *pHandle, const NodeReadmeInfo *pNodeReadmeInfo, CCommonCfgDef * pCfgDef, INT32 lenNote=0, CHAR *szNote=NULL)
{

	/////////////////////////////////////////////////////////////////////////////////////
	// 预留设计通用组态配置数据结构的代码。
	/////////////////////////////////////////////////////////////////////////////////////

	return 0;
}

#endif
