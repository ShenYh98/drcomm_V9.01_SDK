#ifndef _NCOMM_DATA_H_
#define _NCOMM_DATA_H_

/****************************************************************
 *          ncommData.h  
 *      Copyright (C) 2015, 
 *                  ALL RIGHTS RESERVED
 *
 * 修改记录 : 
 *      2015.12.30, 创建文件, 
 * 
 * 
 *****************************************************************/

#include <string>
#include <fstream>
#include <memory.h>
#include "PubDef.h"

#ifdef _WINDOWS
#	ifdef NCOMMDATA_EXPORTS
#		define NCOMMDATA_API __declspec(dllexport)
#	else
#		define NCOMMDATA_API __declspec(dllimport)
#	endif

#	ifndef NCOMMDATA_EXPORTS
#		pragma comment(lib,"ncommData.lib")
#		pragma message("Automatically linking with ncommData.dll")
#	endif
#else
#	define NCOMMDATA_API
#endif

struct NcommYxData{
	INT32  iValue;		//遥信数据状态，0-分，1-合
	INT32  flgQ;		//数据品质,定义见PubDef.h的QBit开头的常量,flgQ & QBitNotUpdate结果为TRUE表示数据不刷新，flgQ & QBitFault结果为TRUE表示数据异常
	INT64  tmRefresh;	//刷新时间，从1970.1.1零点开始的百纳秒数,可用函数NcommData::Int64ToSystemtime进行时间转换
};

struct NcommAiData{
	FLOAT32 fValue;		//模拟量数据值
	INT32  flgQ;		//数据品质,定义见PubDef.h的QBit开头的常量,flgQ & QBitNotUpdate结果为TRUE表示数据不刷新，flgQ & QBitFault结果为TRUE表示数据异常
	INT64  tmRefresh;	//刷新时间，从1970.1.1零点开始的百纳秒数,可用函数Int64ToSystemtime进行时间转换
};

class NCOMMDATA_API  NcommData {
public:
	NcommData();
	~NcommData();

public:

	/**
	* @brief	将NcommYxData或NcommAiData中的刷新时间转化为SYSTEMTIME时间
	*           程序可以直接从pYxData、pYcData、pYmData中读取数据
	* @param tm1	INT64的时间，从1970.1.1零点开始的百纳秒数
	* @param pSt1	转化为年、月、日、时、分、秒、毫秒的数据格式
	* @retval	返回FALSE,表示转化失败
	*/
	static BOOL32 Int64ToSystemtime(const INT64 tm1, SYSTEMTIME * pSt1);

	/**
	* @brief	初始化读取ncomm数据的接口，该函数是以tcp client 模式访问ncomm，ncomm则采用s_sample规约以tcp server方式定期发送数据
	* @param mode1	读取ncomm数据的模式，目前只支持值为0的模式
	* @param szIp1	提供数据的ncomm的IP地址，格式如：192.168.1.1
	* @param port1	提供数据的ncomm的端口号
	* @param numYx1	读出的遥信数量
	* @param numYc1	读出的遥测数量
	* @param numYm1	读出的遥脉数量，遥脉即电度
	*/
	void Init(INT32 mode1, const char *szIp1, UINT16 port, INT32 numYx1, INT32 numYc1, INT32 numYm1=0);

	/**
	 * @brief 做遥控，供服务端规约调用
	 * @param pIF1		规约操作接口对象
	 * @param Action1	遥控性质，Fr::YK_ON(合)， Fr::YK_OFF（分）
	 * @param ObjectNo1 遥控对象号（节点中的遥控对象序号）
	 * @param State1	遥控状态,YKYT_SELECT(遥控遥调选择)、YK_EXE(遥控执行)、YK_RMV(遥控撤消)
	 * @param IsDinYk1	是否为双点遥控
	 * @retval	返回值<0表示失败
	 */
	INT32  DoYk(void *pIF1, INT32 Action1, INT32 ObjectNo1, INT32 State1, BOOL32 IsDinYk1=FALSE);

	/**
	 * @brief 做整数值遥调，供服务端规约调用
	 * @param pIF1		规约操作接口对象
	 * @param Action1	遥调性质，Fr::YT_OUT(输出)， Fr::YT_UP（升）， Fr::YT_DOWN（降）,YT_STOP（终止）
	 * @param ObjectNo1	遥调对象号（节点中的遥调对象序号）
	 * @param Value1	遥调值
	 * @param State1	遥调状态,YKYT_SELECT(遥控遥调选择)、YT_EXE(遥调执行)、YT_RMV(遥调撤消)
	 * @retval	返回值<0表示失败
	 */
	INT32  DoYtInteger(void *pIF1, INT32 Action1, INT32 ObjectNo1, INT32 Value1, INT32 State1);

	/**
	 * @brief 做浮点数值遥调，供服务端规约调用
	 * @param pIF1		规约操作接口对象
	 * @param Action1	遥调性质，Fr::YT_OUT(输出)， Fr::YT_UP（升）， Fr::YT_DOWN（降）,YT_STOP（终止）
	 * @param ObjectNo1 遥调对象号（节点中的遥调对象序号）
	 * @param Value1	遥调值
	 * @param State1	遥调状态,YKYT_SELECT(遥控遥调选择)、YT_EXE(遥调执行)、YT_RMV(遥调撤消)
	 * @retval	返回值<0表示失败
	 */
	INT32  DoYtFloat(void *pIF1, INT32 Action1, INT32 ObjectNo1, FLOAT32 Value1, INT32 State1);


public:
	INT32 numYx;
	INT32 numYc;
	INT32 numYm;
	NcommYxData *pYxData;
	NcommAiData *pYcData;
	NcommAiData *pYmData;

	INT32 ip;
	UINT16 port;

	void *pHandle;  //内部用的中间变量
};

#endif
