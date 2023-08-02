#ifndef _S_MY_LCN_H_
#define _S_MY_LCN_H_

#include "LcnIF.h"
#include "LcnProc.h"

// 示例规约通讯报文类型码
namespace TYPECODE
{
	static const INT32 CHG_YX	=	1;				// 变化遥信数据
	static const INT32 CHG_YC	=	2;				// 变化遥测数据
	static const INT32 CHG_YM	=	3;				// 变化遥脉数据
	static const INT32 SOE		=	4;				// SOE数据
	static const INT32 ALL_YX	=	5;				// 全遥信数据
	static const INT32 ALL_YC	=	6;				// 全遥测数据
	static const INT32 ALL_YM	=	7;				// 全遥脉数据
	static const INT32 YKSIN	=   8;			// 单点遥控
	static const INT32 YKDIN	=   9;			// 双点遥控
	static const INT32 YT			=   10;			// 遥调
	static const INT32 NormalQuery	=   11;	// 总召
	static const INT32 SetTime	=   12;			// 校时
	static const INT32 CallAll	=   13;			// 总召
	static const INT32 ResetLink=	14;			// 链路复位
	static const INT32 CurveData=	15;		// 曲线数据
}

//定义本规约系统容量
const INT32 P_YX_MAX							= 10000;					// 最大遥信数
const INT32 P_YC_MAX							=  5000;					// 最大遥测数
const INT32 P_YM_MAX							=  2000;					// 最大电度数
const INT32 P_YK_MAX							=  2000;					// 最大遥控数
const INT32 P_YT_MAX							=  2000;					// 最大遥调数

class CMyLcn_S: public CLcnIF
{
	void *		pIF;			//系统数据与管理的操作接口对象指针，每个规约必须声明该变量

	const FrTransMapBase*	pFtm;			// 转发表配置，通常服务端规约都要用到转发表

	INT32		iTotalSendYxNum;				// 遥信转发数量
	INT32		iTotalSendYcNum;				// 遥测转发数量
	INT32		iTotalSendYmNum;				// 遥脉转发数量

	DEALDATAINFO DataInfo;					// 用于收发函数的返回对象

	BOOL32		isEnglishDebug;					// 调试输出信息为英文
	BOOL32		IsCallAllData;						// 总召唤
	BOOL32		IsACK;								// 肯定确认
	BOOL32		IsCallYx;							// 召唤遥信
	BOOL32		IsCallYc;							// 召唤遥测
	BOOL32		IsCallYm;							// 召唤遥测

public:
	CMyLcn_S();

	~CMyLcn_S(void);

	/**
	* @brief		 初始化规约准备运行的参数，系统在所有节点全部初始化后才开始启动多线程进行各自通讯收发处理
	* @param pFrApi1 系统数据与管理的操作接口对象指针
	**/
	virtual void V_NodeInit(void *pIF1);

	/**
	* @brief		规约结束的处理函数,主要是关闭规约处理程序分配的句柄，包括文件创建、内存分配等句柄
	**/
	virtual void V_NodeDestroy();

	/**
	* @brief			对接收报文进行处理
	* @param buf		接收数据的缓冲区
	* @param bufSize	接收数据的字节数
	* @retval			处理的结果，包括处理的接收字节数
	*/
	virtual DEALDATAINFO V_ReceiveProc(const UINT8* buf,const INT32 bytes);

	/**
	* @brief			发送报文组装
	* @param buf		发送数据的缓冲区
	* @param bufSize	发送数据的缓冲区大小
	* @retval			组装的结果，包括组装的字节数，必要时还包括指示重新链接链路等
	*/
	virtual DEALDATAINFO V_SendProc(UINT8* buf,const INT32 bufSize);

	/*
		通道复位，主要是针对TCP连接，IEC104等规约是需要额外处理的
		规约不用处理返回值为-1，正常返回值为1,
		返回为0表示原有接收的暂存数据要清除
	*/
	virtual INT32 V_ChannelReset();

	/*
		每秒执行函数,主要用于规约以秒级为单位不太精确的定时进行处理，如定时总召数据或下对时命令等
		输入参数是秒为单位的脉冲计数，该数值系统启动时从0开始，每秒加1且只会增加不会减小，与机器对时无关
		本函数不一定能保证每秒调用1次，间隔时间可能由于通信处理延迟而间隔时间大小不固定
		规约不用处理返回值为-1
		正常返回值>=0,
	*/
	virtual INT32 V_EverySecondProc(INT32 systemPlus1);

public:
	INT32 ParsePacket(const UINT8* buf, const INT32 len);
	INT32 ProcessYkSin(const UINT8* buf, const INT32 len);
	INT32 ProcessYkDin(const UINT8* buf, const INT32 len);
	INT32 ProcessYt(const UINT8* buf, const INT32 len);
	INT32 ProcessSetTime(const UINT8* buf, const INT32 len);  // 处理对时报文

	/**
	* @brief			组装准备发送变化遥信报文
	* @param buf		发送的数据缓冲区
	* @param bufSize	发送缓冲区的最大字节数
	* @retval			组装的字节数
	*/
	INT32 AssembleSendData(UINT8 *buf, const INT32 bufSize);  // 组装发送数据报文
	INT32 AssembleSendACK(UINT8 *buf, const INT32 bufSize);  // ACK报文组装
	INT32 AssembleSendAskAllReturn(UINT8 *buf, const INT32 bufSize);  // 全数据响应
	INT32 AssembleSendAllYxData(UINT8 *buf, const INT32 bufSize);  // 全遥信报文组装
	INT32 AssembleSendAllYcData(UINT8 *buf, const INT32 bufSize);  // 全遥测报文组装
	INT32 AssembleSendAllYmData(UINT8 *buf, const INT32 bufSize);  // 全遥脉报文组装
};
#endif
