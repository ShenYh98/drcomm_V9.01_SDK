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

//设置表1的组态参数
void CreateTable0Def(CTable *pTable1, BOOL32 isEnglish)
{
	if ( !isEnglish )
	{
		pTable1->Init("表1", 2, 0);  //2个字段

		pTable1->pField[0].SetStringDef("名称", Fr::NAME_LENGTH);
		pTable1->pField[1].SetINT32Def("地址");
	}
	else
	{
		pTable1->Init("table 1", 2, 0);  //2个字段

		pTable1->pField[0].SetStringDef("Device Name", Fr::NAME_LENGTH);
		pTable1->pField[1].SetINT32Def("Device address");
	}
		
	pTable1->SetSizeAndOffset();
}

//设置表2的组态参数
void CreateTable1Def(CTable *pTable1, BOOL32 isEnglish)
{
	const CIntValue IntValueList0[]={{1, "遥信"}, {2, "遥测"},{3, "遥脉"}};
	const CIntValue IntValueList0_EN[]={{1, "Yx"}, {2, "Yc"},{3, "Ym"}};
	const CIntValue IntValueList1[]={{1, "0x01"}, {2, "0x02"},{3, "0x03"},{4, "0x04"}};

	if ( !isEnglish )
	{
		pTable1->Init("表2", 6, 0);  //5个字段

		pTable1->pField[0].SetINT32Def("测量类型");
		pTable1->pField[0].SetINT32ListMode(3, IntValueList0);
		pTable1->pField[1].SetINT32Def("功能码");
		pTable1->pField[1].SetINT32ListMode(4, IntValueList1);
		pTable1->pField[2].SetINT32Def("起始地址");
		pTable1->pField[3].SetINT32Def("查询数量");
		pTable1->pField[4].SetINT32Def("偏移量");
		pTable1->pField[5].SetFrDataIdxDef("其他节点参数");
	}
	else
	{
		pTable1->Init("table 2", 6, 0);  //2个字段

		pTable1->pField[0].SetINT32Def("Type");
		pTable1->pField[0].SetINT32ListMode(5, IntValueList0_EN);
		pTable1->pField[1].SetINT32Def("FunCode");
		pTable1->pField[1].SetINT32ListMode(6, IntValueList1);
		pTable1->pField[2].SetINT32Def("StartAddr");
		pTable1->pField[3].SetINT32Def("QueryNum");
		pTable1->pField[4].SetINT32Def("Offset");
		pTable1->pField[5].SetFrDataIdxDef("其他节点参数");
	}
		
	pTable1->SetSizeAndOffset();
}

//设置表2的组态参数
void CreateTable2Def(CTable *pTable1, BOOL32 isEnglish)
{
	const CIntValue IntValueList0[]={{1, "遥信"}, {2, "遥测"},{3, "遥脉"}};
	const CIntValue IntValueList0_EN[]={{1, "Yx"}, {2, "Yc"},{3, "Ym"}};
	const CIntValue IntValueList1[]={{1, "0x01"}, {2, "0x02"},{3, "0x03"},{4, "0x04"}};

	if ( !isEnglish )
	{
		pTable1->Init("表3", 5, 5);  //5个字段

		pTable1->pField[0].SetINT32Def("测量类型");
		pTable1->pField[0].SetINT32ListMode(3, IntValueList0);
		pTable1->pField[1].SetINT32Def("功能码");
		pTable1->pField[1].SetINT32ListMode(4, IntValueList1);
		pTable1->pField[2].SetINT32Def("起始地址");
		pTable1->pField[3].SetINT32Def("查询数量");
		pTable1->pField[4].SetINT32Def("偏移量");
	}
	else
	{
		pTable1->Init("table 2", 5, 5);  //2个字段

		pTable1->pField[0].SetINT32Def("Type");
		pTable1->pField[0].SetINT32ListMode(5, IntValueList0_EN);
		pTable1->pField[1].SetINT32Def("FunCode");
		pTable1->pField[1].SetINT32ListMode(6, IntValueList1);
		pTable1->pField[2].SetINT32Def("StartAddr");
		pTable1->pField[3].SetINT32Def("QueryNum");
		pTable1->pField[4].SetINT32Def("Offset");
	}

	pTable1->SetSizeAndOffset();
}

// 当ConfigTool.exe选中该lcn，就会调用此函数
void SetCfgDef(CCommonCfgDef *pCfgDef1, BOOL32 isEnglish)
{
	CreateTable0Def(&pCfgDef1->pTable[0], isEnglish);
	CreateTable1Def(&pCfgDef1->pTable[1], isEnglish);
	CreateTable2Def(&pCfgDef1->pTable[2], isEnglish);
}

// 当ConfigTool.exe节点组态完毕选中“确认修改”，就会调用此函数
extern "C" LCNIFENTRY INT32 CheckConfigAndCreatePoint(void *pHandle, const NodeReadmeInfo *pNodeReadmeInfo, CCommonCfgDef * pCfgDef, INT32 lenNote=0, CHAR *szNote=NULL)
{
	INT32 i = 0;
	INT32 j = 0;
	INT32 TmnlNum = 0;
	INT32 QueryNum = 0;
	INT32 TmnlYxNum = 0;		// 终端遥信数量，下同
	INT32 TmnlYcNum = 0;
	INT32 TmnlYmNum = 0;
	INT32 NodeYxNum = 0;		// 节点遥信数量，下同
	INT32 NodeYcNum = 0;
	INT32 NodeYmNum = 0;
	INT32 YxOffset = 0;
	INT32 YcOffset = 0;
	INT32 YmOffset = 0;

	CHAR TmpName[Fr::NAME_LENGTH];
	CHAR SignalName[Fr::NAME_LENGTH];

	//解析表0数据
	Table0DataStruct *pTable0 = (Table0DataStruct *)pCfgDef->pTable[0].ReadDynamicTable(sizeof(Table0DataStruct), &TmnlNum); 

	//解析表1数据
	Table1DataStruct *pTable1 = (Table1DataStruct *)pCfgDef->pTable[1].ReadDynamicTable(sizeof(Table1DataStruct), &QueryNum); 
	
	if ( TmnlNum <=0 || QueryNum <= 0 )
	{// 没有配置条目
		sprintf(szNote, "没有配置条目!");
		return -1;
	}

	for ( i = 0; i < QueryNum; ++i )
	{
		if ( 1 == pTable1[i].Type )
		{// 遥信
			TmnlYxNum += pTable1[i].QueryNum;	// 假设每个线圈就是一个遥信值
		}
		else if ( 2 == pTable1[i].Type )
		{// 遥测
			TmnlYcNum += pTable1[i].QueryNum;	// 假设每个寄存器就是一个遥测值
		}
		else if ( 3 == pTable1[i].Type )
		{// 遥脉
			TmnlYmNum += pTable1[i].QueryNum / 2;	// 假设2个寄存器就是一个遥脉值
		}
	}// End of for

	NodeYxNum = TmnlNum * TmnlYxNum;
	NodeYcNum = TmnlNum * TmnlYcNum;
	NodeYmNum = TmnlNum * TmnlYmNum;
	
	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Yx, NodeYxNum);		//设置遥信数量
	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Yc, NodeYcNum);		//设置遥测数量
	LCN_CfgSetNodeDataNum(pHandle, Fr::DataSort::Ym, NodeYmNum);	//设置遥脉数量

	for ( i = 0; i < TmnlNum; ++i )
	{
		YxOffset = 0;		// 每次循环开头都必须清零
		YcOffset = 0;		// 每次循环开头都必须清零
		YmOffset = 0;	// 每次循环开头都必须清零

		sprintf(TmpName, "%s%s", pNodeReadmeInfo->Name, pTable0[i].sName);
		// 每个测点手动输入名称
		sprintf(SignalName, "%s%s",	TmpName, "操作继电器2合");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "操作继电器2分");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "感性/容性负载");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "火灾跳闸（开入1）");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "开入2");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "A相断相（开入3）");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B相断相（开入4）");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C相断相（开入5）");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "开入6");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "开入7");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "开入8");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "开入9");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "开入10");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "开入11");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "开入12");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "开入13");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yx, i * TmnlYxNum + YxOffset++, SignalName);

		sprintf(SignalName, "%s%s",	TmpName, "A相电压");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B相电压");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C相电压");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "AB线电压");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "BC线电压");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "CA线电压");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "A相电流");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B相电流");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C相电流");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "A相有功");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B相有功");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C相有功");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "总有功");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "A相无功");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B相无功");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C相无功");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "总无功");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "A相功率因数");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B相功率因数");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C相功率因数");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "总功率因数");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "频率");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "剩余电流");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Yc, i * TmnlYcNum + YcOffset++, SignalName);

		sprintf(SignalName, "%s%s",	TmpName, "总电能");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Ym, i * TmnlYmNum + YmOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "A相电能");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Ym, i * TmnlYmNum + YmOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "B相电能");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Ym, i * TmnlYmNum + YmOffset++, SignalName);
		sprintf(SignalName, "%s%s",	TmpName, "C相电能");	LCN_CfgSetNodeDataName(pHandle, Fr::DataSort::Ym, i * TmnlYmNum + YmOffset++, SignalName);
	}// End of for(i)

	return 0;
}

#endif
