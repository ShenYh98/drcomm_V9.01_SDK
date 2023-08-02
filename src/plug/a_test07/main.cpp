#include "a_myLcn.h"

CMyLcn_A::CMyLcn_A(void){}

CMyLcn_A::~CMyLcn_A(void){}

void CMyLcn_A::V_NodeInit(void *pIF1)
{	
	pIF = pIF1;		//保存系统的操作接口

	//通用组态参数加载示例
	PTOTHERINFO pti;
	LCN_GetProtocolIdentify(pIF, &pti); //获得规约基本配置信息

	if (pti.flgCfg & PTOTHERINFO::CBitEnglishDebug)
		isEnglishDebug = TRUE;
	else
		isEnglishDebug = FALSE;

	//通用组态参数加载
	CCommonCfgDef *pCfgDef = (CCommonCfgDef *)pti.pCommonCfgDef;  //得到通用组态的表、字段定义
	INT32 size;
	INT8 *buf = LCN_GetZtBuf(pIF, &size);
	pCfgDef->LoadCfgBuf(size, (BYTE *)buf);  //加载组态参数
	//以下代码是将通用组态参数读入到变量中
	//加载表0的组态参数
	if (  (pCfgDef->pTable[0].numRecord !=1)
		||(pCfgDef->pTable[0].numField != 4)  //4个字段
		||(pCfgDef->pTable[0].iUnitSize != sizeof(cfg)))
	{
		cfg.SetDefault();
	}
	else
	{
		pCfgDef->pTable[0].ReadStaticTable(sizeof(cfg), &cfg, 1);
	}

	nowPulsSec = LCN_GetSystemPuls(pIF);
	checkPlusSec = 0;
}

INT32 CMyLcn_A::V_EverySecondProc(INT32 systemPlus1)
{
	nowPulsSec = systemPlus1; // 记录当前的系统秒计数

	// 检查是否有遥控或遥调设置参数
	YkYtCheck();

	// 如果app的判断时间以秒为单位，可以把改函数放到自动控制调用
	AutoControlProc();

	return 0;
}

void CMyLcn_A::YkYtCheck()
{
	YkYtMsg ykMsgData;

	LCN_GetYkYtMsgData(pIF, &ykMsgData);		// 取当前遥控状态

	if( ykMsgData.State == Fr::YK_IDLE )
	{// 无控制命令
		return;
	}

	// 有控制命令
	if( !ykMsgData.IsYk )
	{// 是遥调
		if ( ykMsgData.ObjectNo != 0 && ykMsgData.ObjectNo != 1 )		return;

		if ( ykMsgData.State == Fr::YKYT_SELECT )
		{
			LCN_SetYtReturn(pIF, ykMsgData.Action, ykMsgData.ObjectNo, Fr::YK_ACK); //遥调返校
			return;
		}

		if ( ykMsgData.State != Fr::YT_EXE )		return;

		if ( ykMsgData.Action != Fr::YT_OUT )		return;

		// 是遥调执行
		FLOAT32 fSet;
		if (ykMsgData.OtherType == 1)
			fSet = ykMsgData.OtherValue;
		else if (ykMsgData.OtherType == 2)
			fSet = (FLOAT32)ykMsgData.OtherValue2;
		else
			return;

		FLOAT32 fv = fSet / 10;

		LCN_SetYcFloat(pIF, ykMsgData.ObjectNo, fSet);		// YC0是温度上限，YC1是温度下限

		//保存应用节点的数据，包括配置。为了防止管理机掉电重启，配置可能丢失，必须保存
		LCN_SaveNodeData(pIF, Fr::DataSort::Yc);
	}
	else
	{// 是遥控
		if ( ykMsgData.ObjectNo != 0 && ykMsgData.ObjectNo != 1 )		return;

		if (ykMsgData.State == Fr::YK_SELECT)
		{//遥控选择
			LCN_SetYkReturn(pIF, ykMsgData.Action, ykMsgData.ObjectNo, Fr::YK_ACK); //遥控返校
			return;
		}

		if (ykMsgData.State != Fr::YK_EXE)		return;
		
		//是遥控执行
		if ( ykMsgData.Action == Fr::YK_OFF )//遥控分
			LCN_SetYx(pIF, ykMsgData.ObjectNo, 0);
		else if ( ykMsgData.Action == Fr::YK_ON )//遥控合
			LCN_SetYx(pIF, ykMsgData.ObjectNo, 1);
	
		//保存应用节点的数据，包括配置。为了防止管理机掉电重启，配置可能丢失，必须保存
		LCN_SaveNodeData(pIF, Fr::DataSort::Yx);
	}
}

void CMyLcn_A::AutoControlProc()
{
	BOOL32 isLock = FALSE;  // 闭锁状态

	LCN_SetYcFloat(pIF, 0, (FLOAT32)nowPulsSec);
	if ( (nowPulsSec - checkPlusSec) < cfg.secSpace )
	{// 定时器时间没到
		return;
	}

	checkPlusSec = nowPulsSec;

	if (!LCN_IsNodeRun(pIF, cfg.ycFdiWarm.noNode))  //检查当前温度所在节点通信是否正常
		isLock = TRUE;
	if (!LCN_IsNodeRun(pIF, cfg.yxFdi.noNode))  //检查加热器开关状态所在节点通信是否正常
		isLock = TRUE;
	if (!LCN_IsNodeRun(pIF, cfg.ykFdi.noNode))  //检查加热器开关投退所在节点通信是否正常
		isLock = TRUE;

	// 急停的优先级最高，放在开头
	YxData stEmgStopData;	// 急停状态
	LCN_GetYxData(pIF, 1, &stEmgStopData);
	if ( !isLock && ( stEmgStopData.iValue == 1 ) )
	{// 需紧急关闭加热器
		YxData st;		// 加热器状态，临时状态量
		LCN_SGetYxData(pIF, cfg.yxFdi, &st);
		if ( st.iValue == 1 )
		{// 加热器已启动
			LCN_DoYkDirectExe(pIF, cfg.ykFdi, Fr::YK_OFF);  // 关闭加热器
		}

		return;
	}

	YcData YcWarmData;  // 当前温度值
	if (!LCN_SGetYcData(pIF, cfg.ycFdiWarm, &YcWarmData))
		isLock = TRUE;

	if (YcWarmData.fValue - 100 >= 0.00001){
		printf("1111111\n");
		
	}
	
	printf("value is %.3f\n", YcWarmData.fValue);
	YcData WarmUpData;		// 温度上限值
	if (!LCN_GetYcData(pIF, 0, &WarmUpData))
		isLock = TRUE;

	YcData WarmDnData;		// 温度下限值
	if (!LCN_GetYcData(pIF, 1, &WarmDnData))
		isLock = TRUE;

	if ( WarmUpData.fValue <= WarmDnData.fValue )
	{// 温度上限值比温度下限值还要低，属于异常状态
		return;
	}

	YxData stWarmYxData;		// 加热器状态
	if (!LCN_SGetYxData(pIF, cfg.yxFdi, &stWarmYxData))
		isLock = TRUE;

	YxData stEnData;	// 温控功能投入/退出状态
	if (!LCN_GetYxData(pIF, 0, &stEnData))
		isLock = TRUE;

	LCN_SetYx(pIF, 1, isLock);  // 刷新闭锁状态
	

	if ( isLock )		
		return;	// 条件闭锁，退出控制

	if ( stEnData.iValue == 0 )		return;	// 温控功能退出

	if ( stWarmYxData.iValue == 0 )
	{// 加热器已关闭
		if ( YcWarmData.fValue <= WarmDnData.fValue )
		{
			LCN_DoYkDirectExe(pIF, cfg.ykFdi, Fr::YK_ON);  //启动加热器
		}
	}
	else
	{// 加热器已启动
		if ( YcWarmData.fValue > WarmUpData.fValue )
		{
			LCN_DoYkDirectExe(pIF, cfg.ykFdi, Fr::YK_OFF);  //关闭加热器
		}
	}
}
