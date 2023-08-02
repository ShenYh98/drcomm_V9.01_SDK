#include "s_myLcn.h"
#include "LcnProc.h"

// 构造和析构
CMyLcn_S::CMyLcn_S(void){}

CMyLcn_S::~CMyLcn_S(void){}

// 节点初始化
void CMyLcn_S::V_NodeInit(void * pIF1)
{
	pIF = pIF1;		//保存系统函数的操作接口

	PTOTHERINFO pti;
	LCN_GetProtocolIdentify(pIF, &pti); //获得规约基本配置信息

	// 这部分代码是为了调试时打印准备的，如果做国外项目就必须注意这点
	// 国内项目显示都是中文，英文显示就没有必要
	if ( pti.flgCfg & PTOTHERINFO::CBitEnglishDebug )
		isEnglishDebug = TRUE;
	else 
		isEnglishDebug = FALSE;

	// 得到转发表配置，只有服务端规约需要转发表，客户端规约不需转发表
	pFtm = LCN_GetTransMap(pIF);

	// 节点实际的容量与转发表数量可能不一致
	// 转发的数据必须按转发表定义
	// 理论上节点的数量不应该小于转发表数量
	FactRtuCapacity		capacity;	// 节点容量
	LCN_GetNodeDataCapacity(pIF, &capacity);
	if (capacity.RealYx > pFtm->numYx)
		iTotalSendYxNum = pFtm->numYx;
	else iTotalSendYxNum = capacity.RealYx;
	if (capacity.RealYc > pFtm->numYc)
		iTotalSendYcNum = pFtm->numYc;
	else iTotalSendYcNum = capacity.RealYc;
	if (capacity.RealYm > pFtm->numYm)
		iTotalSendYmNum = pFtm->numYm;
	else iTotalSendYmNum = capacity.RealYm;

	//设置规约接收数据更新消息的最大缓冲区和消息通知机制，
	//Fm::MsgQueue::Max为缓冲区大小的标准值，各规约可根据自身规约的实际容量调整yxNum等值
	//通常服务端规约是转发规约，需要定义何类数据更新需通知本节点，
	//yxNotify和ycNotify分别表示遥信或遥测数据的更新消息类型，遥脉数据固定是有更新即通知
	MsgNotifyDef msgRecNotifyDef;
	msgRecNotifyDef.yxNum		= Fm::MsgQueue::MaxYxNum;	//遥信消息的最大缓冲区
	msgRecNotifyDef.ycNum		= Fm::MsgQueue::MaxYcNum;	//遥测消息的最大缓冲区
	msgRecNotifyDef.ymNum	= Fm::MsgQueue::MaxYmNum;	//遥脉消息的最大缓冲区
	msgRecNotifyDef.soeNum	= Fm::MsgQueue::MaxSoeNum;	//SOE消息的最大缓冲区
	msgRecNotifyDef.yxNotify	= Fm::Notify::ChangeValue;		//遥信值有变化需通知，品质变化不通知
	msgRecNotifyDef.ycNotify	= Fm::Notify::ChangeValue_Q;	//遥测值或品质有变化需通知
	LCN_SetMsgNotifyDef(pIF, &msgRecNotifyDef);

	IsCallAllData = FALSE;		// 初始化不发送数据
	IsACK = FALSE;					// 初始化不发送肯定确认
	IsCallYx = FALSE;
	IsCallYc = FALSE;
	IsCallYm = FALSE;

	NodeReadmeInfo nodeReadmeInfo;
	LCN_GetNodeReadmeInfo(pIF, &nodeReadmeInfo, sizeof(nodeReadmeInfo));
	printf("node %s Init\n", nodeReadmeInfo.Name);
}

// 节点被销毁
void CMyLcn_S::V_NodeDestroy(){}

// 接收处理
DEALDATAINFO CMyLcn_S::V_ReceiveProc(const UINT8* buf, const INT32 bytes)
{
	DataInfo.SetDefault();
	DataInfo.Bytes = bytes;		// 设置报文处理的长度

	if ( ParsePacket(buf, bytes) < 0 )
	{
		LCN_SetRecvBadPackage(pIF, 1);	// 坏包数加1
	}
	else
	{
		LCN_SetRecvGoodPackage(pIF, 1);  // 解析包成功，好包数加1
	}

	return DataInfo;
}

// 发送处理
DEALDATAINFO CMyLcn_S::V_SendProc(UINT8* buf, const INT32 bufSize)
{
	DataInfo.SetDefault();

	DataInfo.Bytes = AssembleSendData(buf, bufSize);

	if ( DataInfo.Bytes > 0 )
	{//如果是问答式规约，发送需要设置DataInfo.isSyncChar=TRUE，来通知系统清除上次收到的缓冲数据
		DataInfo.isSyncChar = TRUE;
	}

	return DataInfo;
}


INT32 CMyLcn_S::V_EverySecondProc(INT32 systemPlus1)
{
	return 0;
}

INT32 CMyLcn_S::V_ChannelReset()
{
	IsCallAllData = FALSE;
	IsACK = FALSE;

	return 0;
}
