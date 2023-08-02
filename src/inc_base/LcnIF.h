#ifndef _LCN_InterFace_H_
#define _LCN_InterFace_H_

/**
@file 规约处理接口
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
		通道规约初始化
	*/
	virtual void	V_NodeInit(void *pIF1)=0;

	/*
		关闭通道规约处理
	*/
	virtual void	V_NodeDestroy(){};

	//保护信息消息处理
	virtual void V_MessageProc(const RelayInfoMsgData *pMsg1){if (pMsg1==NULL) return;};
	
	//其它消息处理
	virtual void V_MessageProc(const void * pMsg1){if (pMsg1==NULL) return;};

	/*
		对给接收的数据进行处理
		返回的DEALDATAINFO.bytes 表示实际已处理的字节数
	*/
	virtual DEALDATAINFO V_ReceiveProc(const UINT8* buffer, const INT32 bytes){DEALDATAINFO Ddi; Ddi.SetDefault(); Ddi.Bytes = bytes; return Ddi;};

	/*
		组装准备发送报文
		返回组装字节数及处理标志，标志包括通讯口需要重新进行链路连接等
		返回的DEALDATAINFO.bytes 表示缓冲区实际需要发送的字节数
	*/
	virtual DEALDATAINFO V_SendProc(UINT8* buffer, const INT32 bufferSize){DEALDATAINFO Ddi; Ddi.SetDefault(); return Ddi;};

	/*
		通道复位，通道重新创建新的连接成功将调用此函数。主要是针对TCP连接，如IEC104等规约是需要额外处理的
		规约不用处理返回值为-1，正常返回值为1,
		返回为0表示原有接收的暂存数据要清除
	*/
	virtual INT32 V_ChannelReset(){return -1;};

	/*
		每秒执行函数,主要用于规约以秒级为单位不太精确的定时进行处理，如定时总召数据或下对时命令等
		输入参数是秒为单位的脉冲计数，该数值系统启动时从0开始，每秒加1且只会增加不会减小，与机器对时无关
		本函数不一定能保证每秒调用1次，间隔时间可能由于通信处理延迟而间隔时间大小不固定
		返回值无特殊意义
	*/
	virtual INT32 V_EverySecondProc(INT32 systemPlus1){return systemPlus1;};
};

//创建规约处理对象的实例。
typedef CLcnIF* (*Create_node)();

//释放规约处理对象的实例。
typedef void (*Destroy_node)(CLcnIF*);

//得到规约定义说明。
typedef LPSTR (*GetIdentify_t)(PTOTHERINFO &);

#endif
