#include "a_myLcn.h"

// 设置表0的组态参数
void CreateTable0Def(CTable *pTable1, BOOL32 isEnglish)
{
	INT32 i = 0;

	if ( !isEnglish )
	{
		pTable1->Init("表0", 4, 1);  //4个字段，1个记录

		pTable1->pField[i++].SetINT32Def("控制间隔秒数", 10,1000,3);
		pTable1->pField[i++].SetFrDataIdxDef("当前温度的数据索引");
		pTable1->pField[i++].SetFrDataIdxDef("加热器运行状态的数据索引");
		pTable1->pField[i++].SetFrDataIdxDef("加热器投入/退出的索引");
	}
	else
	{
		pTable1->Init("table 0", 4, 1);  //4个字段，1个记录

		pTable1->pField[i++].SetINT32Def("space seconds");
		pTable1->pField[i++].SetFrDataIdxDef("index of AI");
		pTable1->pField[i++].SetFrDataIdxDef("index of DI");
		pTable1->pField[i++].SetFrDataIdxDef("index of DO");
	}

	pTable1->SetSizeAndOffset();
}

void SetCfgDef(CCommonCfgDef *pCfgDef1, BOOL32 isEnglish)
{
	CreateTable0Def(&pCfgDef1->pTable[0], isEnglish);
}

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
extern "C" LCNIFENTRY INT32 CheckConfigAndCreatePoint(void *pHandle, const NodeReadmeInfo *pNodeReadmeInfo, CCommonCfgDef * pCfgDef, INT32 lenNote=0, CHAR *szNote=NULL)
{
	//解析参数代码示例，如果规约没有组态参数，直接参考测点自动生成代码
	AppCfgDef cfg;
	pCfgDef->pTable[0].ReadStaticTable(sizeof(AppCfgDef), &cfg, 1); //解析表0数据

	//检查参数代码示例，错误信息在szNote中返回
	if ( (cfg.secSpace < 3) || ( cfg.secSpace > 1000 ) )
	{
		SYSPROC::StrSafeCat(lenNote, szNote, "间隔秒数配置不正确");
		return -1;
	}

	BOOL32 isEnglish = LCN_CfgIsEnglish(pHandle);

	//自动生成四遥配置信息代码示例
	char szText[128];

	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Yx, 2);	//设置遥信数量
	sprintf(szText, "%s_温控功能投入", pNodeReadmeInfo->Name);	//设置遥信名称
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, 0, szText);

	sprintf(szText, "%s_急停", pNodeReadmeInfo->Name);
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, 1, szText);

	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Yc, 2);	//设置遥测数量
	sprintf(szText, "%s_温度上限",pNodeReadmeInfo->Name);	//设置遥测名称
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, 0, szText);

	sprintf(szText, "%s_温度下限",pNodeReadmeInfo->Name);
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, 1, szText);

	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Yk, 2);	//设置遥控数量
	sprintf(szText, "%s_温控功能投入",pNodeReadmeInfo->Name);	//设置遥控名称
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yk, 0, szText);

	sprintf(szText, "%s_急停",pNodeReadmeInfo->Name);
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yk, 1, szText);

	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Yt, 2);	//设置遥调数量
	sprintf(szText, "%s_温度上限",pNodeReadmeInfo->Name);	//设置遥调名称
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yt, 0, szText);

	sprintf(szText, "%s_温度下限",pNodeReadmeInfo->Name);
	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yt, 1, szText);

	return 0;
}

#endif
