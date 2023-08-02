#ifndef _A_MY_LCN_H_
#define _A_MY_LCN_H_

/**
@file 应用功能示例头文件，
@version v1.01
@author 
@date 2016-12-21
*/

#include "LcnIF.h"
#include "LcnProc.h"

// 应用类的配置结构
struct AppCfgDef
{
	INT32		secSpace;		// 每个控制的间隔秒数
	FrDataIdx	ycFdiWarm;	// 配置当前温度位置
	FrDataIdx	yxFdi;			// 加热器开关状态位置
	FrDataIdx	ykFdi;			// 加热器开关投退的操作对象位置

	FrDataIdx	ytFdiWarm;	// 配置当前温度位置

	void SetDefault()
	{
		memset(this, 0, sizeof(*this));
	}
};

class CMyLcn_A: public CLcnIF
{
	void *		pIF;
	BOOL32		isEnglishDebug;		//是否是英文调试环境
	INT32		nowPulsSec;			//系统秒计数值。系统自启动后该值从0开始每秒加1
	INT32		checkPlusSec;		//上次检查判断时间

	AppCfgDef	 cfg;						//通用组态的参数表0，参数0固定为1个结构
	DEALDATAINFO	DataInfo;		//用于收发函数的返回对象

public:

	CMyLcn_A(void);
	virtual ~CMyLcn_A(void);

	/**
	* @brief		 初始化规约准备运行的参数，系统在所有节点全部初始化后才开始启动多线程进行各自通讯收发处理
	* @param pFrApi1 系统数据与管理的操作接口对象指针
	**/
	virtual void V_NodeInit(void *pIF1);

	/*
	* @brief			每秒执行函数,主要用于规约以秒级为单位不太精确的定时进行处理，如定时总召数据或下对时命令等
						输入参数是秒为单位的脉冲计数，该数值系统启动时从0开始，每秒加1且只会增加不会减小，与机器对时无关
						本函数不一定能绝对保证每秒调用1次，间隔时间可能由于通信处理延迟而间隔时间大小不固定
	* @retval			规约不用处理返回值为-1,正常返回值>=0
	*/
	virtual INT32 V_EverySecondProc(INT32 systemPlus1);

public:
	void YkYtCheck();					// 检查是否有遥控、遥调
	void AutoControlProc();			// 定时执行的自动控制功能函数
};

#endif
