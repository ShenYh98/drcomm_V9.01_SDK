#ifndef _PTOTHERINFO_H_
#define _PTOTHERINFO_H_

#include "CommonCfg.h"

//规约基本信息
struct PTOTHERINFO
{
	static const INT32 PBitDdRealy			= 0x01;	//调度转发模式专用：调度转发规约是否支持微机保护
	static const INT32 PBitYkSelectCheck	= 0x02;	//规约支持遥控选择处理
	static const INT32 PBitYtSelectCheck	= 0x04;	//规约支持遥调选择处理

	static const INT32 CBitEnglish			= 0x01;	//是国际化版本，主要指规约描述、组态信息
	static const INT32 CBitEnglishDebug		= 0x02;	//调试信息是国际化版本，主要是指实时的调试信息，pFrApi->toDebug函数等
	static const INT32 CBitHighSpeedNode	= 0x04;	//高速运行节点，SendSomething函数调用的间隔时间是1豪秒,Timer设置无效

	static const INT32 PBitAppIec61850Server= 0x01;	//Iec61850服务端
	static const INT32 PBitAppIec61850Client= 0x02;	//Iec61850客户端
	static const INT32 PBitAppAgc			= 0x04;	//Agc
	static const INT32 PBitAppAvc			= 0x08;	//Avc
	static const INT32 PBitAppPlc			= 0x10;	//Plc
	static const INT32 PBitAppPowerEffic	= 0x20;	//能效管理
	static const INT32 PBitAppPvWeb			= 0x40;	//光伏扶贫

	INT32	ProtocolType	;	//规约通讯模式, 定义见Fr::Protocol::PClient等
	INT32	ZtType			;	//组态参数类型, 定义见Fr::CFG:: //取代原来的ProtocolZt	;
								//>0表示规约如需组态，程序与规约程序名相同，扩展名与.lcn相对应.pac，组态程序需动态调用.pac来完成规约组态
	INT32	flgCfg			;	//配置信息，, 定义见PTOTHERINFO::CBitEnglish等，取代原来的bP103bh
	INT32	flgApp			;	//功能标志，定义见PTOTHERINFO::PBitApp等
	FLOAT32	fProtocolVersion;	//规约发布的平台版本号
	INT32	flgProc			;	//处理标志，定义见：PTOTHERINFO::PBit
	UINT32	Timer			;	//该值由组态决定，PTOTHERINFO其它成员值由程序直接指定。定时起器时间(50、100、150、200、500、1000毫秒   默认200毫秒,UDP通讯不能小于200毫秒,否则报文会丢),
	BOOL32	bSendBoData		;	//特殊情况使用。与通道进行UDP通讯时，是否以广播方式发送。（默认采用UDP/IP）		
	BOOL32	bSendZkState	;	//特殊情况使用。前置机接双总控（采用非网络103规约，且每个总控都采用双通道）时，后台机无法得到总控运行状态，因为后台只能看到前置机而看不到总控，
								//如果设置此参数,前置将把总控状态送到后台，总控的逻辑节点地址为，前三位与所配节点地址相同，最后以为
								//是所配节点地址相同最后一位+所配节点号+1。

	INT32	ProtocolBhId	;	//规约保护ID(如果规约没有保护或bP103bh=TRUE时,不用填<默认为-1>)
	BOOL32	bTimerRevFun	;	//是否定时调用V_ReceiveProc()函数，系统默认未收到数据不调用V_ReceiveProc()函数
								//需要定时处理可以考虑使用EverySecondProc， add on 2015.09.04
	BOOL32	bMutiRtuChn		;	//特殊情况使用。是否是需要虚拟多厂站的节点（数据接受节点）
	BOOL32	bDataFloat		;	//YC等数据是否为float
	BOOL32	bNoDealHtData	;	//是否不用处理后台数据
	BOOL32	bNoDealRunTag	;	//无论节点是否在运行状态，系统都接收下行数据和上送节点数据（默认节点在投运状态时，再接收下行数据和上送节点数据）
	UINT32	nSendBufLen		;	//发送缓冲区大小，默认4096字节  ，范围 2048字节 - 10485760字节(10M)
	UINT32	nRevBufLen		;	//接收缓冲区大小，默认4096字节  ，范围 2048字节 - 10485760字节(10M)
	INT32	MaxYx			;	//最大遥信
	INT32	MaxYc			;	//最大遥测
	INT32	MaxYm			;	//最大遥脉
	INT32	MaxYk			;	//最大遥控
	INT32	MaxYt			;	//最大遥调
	CCommonCfgDef *pCommonCfgDef;	//通用的组态定义	

	void SetDefault(){
		memset(this, 0, sizeof(*this));
		Timer=200;
		ProtocolBhId=-1;
		nSendBufLen=nRevBufLen=4096;
		MaxYx = 10000;
		MaxYc = 10000;
		MaxYm = 10000;
		MaxYk = 5000;
		MaxYt = 5000;
		pCommonCfgDef = NULL;
		fProtocolVersion = Fr::SystemVersion;
	}

	PTOTHERINFO()
	{
		SetDefault();
	};
};

#endif
