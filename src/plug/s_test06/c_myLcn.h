#ifndef _C_MY_LCN_H_
#define _C_MY_LCN_H_

/**
@file 客户端调试规约头文件，
@version v1.01
@author 
@date 2012-07-17
说明：本规约用作系统测试，会定期模拟一些数据变化，
	  本规约也可作为规约开发示例程序，同时给开发规约人提供一个调试服务服务端规约的途径。
*/

#include "LcnIF.h"
#include "LcnProc.h"

//定义本规约系统容量
const INT32 P_YX_MAX							= 10000;					// 最大遥信数
const INT32 P_YC_MAX							=  5000;					// 最大遥测数
const INT32 P_YM_MAX							=  2000;					// 最大电度数
const INT32 P_YK_MAX							=  2000;					// 最大遥控数
const INT32 P_YT_MAX							=  2000;					// 最大遥调数

const INT32 MAX_SEND_QUERY_NUM		= 4;							// 最多发送的查询报文数量,实际应用应该取自配置
const INT32 SetTimeIntSec						= 60;						// 对时令下发间隔时间,实际应用应该取自配置
const INT32 CallAllIntSec						= 120;						// 总召间隔时间

const INT32 MIN_DEV_ADDR					= 0;							// 地址下限
const INT32 MAX_DEV_ADDR					= 1000;					// 地址上限
const INT32 MAX_DEV_NUM					= 256;						// 装置数量上限

class CMyLcn_C: public CLcnIF
{
	void *			pIF;		//系统数据与管理的操作接口对象指针，每个规约必须声明该变量

	BOOL32			isEnglishDebug;												//是否是英文调试环境
	INT32			nowPulsSec;	//系统秒计数值。系统自启动后该值从0开始每秒加1。
	INT32			lastSetTimePulsSec;										//上次发送对时秒计数值
	BOOL32			isNeedSetTime;												//需要发送对时

	DEALDATAINFO	DataInfo;													//用于收发函数的返回对象

	INT32			SendQueryNo;												// 发送帧顺序
	INT32			DevNum;														// 装置数量
	INT32			CurrDevNo;													// 当前查询装置序号
	INT32			*pDevAddr;													// 装置地址组
public:

	CMyLcn_C(void);
	virtual ~CMyLcn_C(void);

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
	* @brief			对接收报文进行处理,NCOMM平台定时调用该函数
	* @param buf		接收数据的缓冲区
	* @param bufSize	接收数据的字节数
	* @retval			处理的结果，包括处理的接收字节数
	*/
	virtual DEALDATAINFO V_ReceiveProc(const UINT8* buf,const INT32 bytes);

	/**
	* @brief			发送报文组装,NCOMM平台定时调用该函数，一般会先调用V_ReceiveProc函数，后紧接着调用本函数
	* @param buf		发送数据的缓冲区
	* @param bufSize	发送数据的缓冲区大小
	* @retval			组装的结果，包括组装的字节数，必要时还包括指示重新链接链路等
	*/
	virtual DEALDATAINFO V_SendProc(UINT8* buf,const INT32 bufSize);

	/*
	* @brief			通道复位，NCOMM平台会在通道链路中断后又复位，将立即调用该函数,主要是针对TCP连接，通信复位后，IEC104等规约是需要额外处理
	* @retval			规约不用处理返回值为-1,正常返回值>=0
	*/
	virtual INT32 V_ChannelReset();

	/*
	* @brief			每秒执行函数,主要用于规约以秒级为单位不太精确的定时进行处理，如定时总召数据或下对时命令等
						输入参数是秒为单位的脉冲计数，该数值系统启动时从0开始，每秒加1且只会增加不会减小，与机器对时无关
						本函数不一定能绝对保证每秒调用1次，间隔时间可能由于通信处理延迟而间隔时间大小不固定
	* @retval			规约不用处理返回值为-1,正常返回值>=0
	*/
	virtual INT32 V_EverySecondProc(INT32 systemPlus1);

public:
	UINT16 CRC16(UINT8* pDataBuf, INT32 DataLen);		// CRC校验码计算公式
	/**
	* @brief			组装准备发送报文
	* @param buffer		发送的数据缓冲区
	* @param bufferSize 发送缓冲区的最大字节数
	* @retval			组装的字节数
	*/
	INT32 AssembleSendData(UINT8 *buf, const INT32 bufferSize);		// 组装发送报文
	INT32 AssembleNoramlQuery0(UINT8 *buf, const INT32 bufferSize);  //正常查询0
	INT32 AssembleNoramlQuery1(UINT8 *buf, const INT32 bufferSize);  //正常查询1
	INT32 AssembleNoramlQuery2(UINT8 *buf, const INT32 bufferSize);  //正常查询2
    INT32 AssembleNoramlQuery3(UINT8 *buf, const INT32 bufferSize);  //正常查询3

	/**
	* @brief		解析接收到的报文
	* @param buf	发送的数据缓冲区
	* @param len	发送缓冲区的最大字节数
	* @retval		正确解析的报文
	*/
	INT32 ParsePacket(const UINT8* buf, const INT32 len);		// 解析收到的有效数据包
	INT32 ProcessHoldingRegister(const UINT8* buf, const INT32 len);	// 处理保持寄存器
	INT32 ProcessInputCoil(const UINT8* buf, const INT32 len);				// 处理输入线圈
	INT32 ProcessInputRegister(const UINT8* buf, const INT32 len);		// 处理输入寄存器
};

#endif
