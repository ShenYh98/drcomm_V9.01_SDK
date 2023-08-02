#ifndef _LCN_PROC_H_
#define _LCN_PROC_H_

#include "PTOTHERINFO.h"
#include "LcnStructDef.h"

#ifdef _WINDOWS
#	ifdef LCN_PROC_EXPORTS
#		define LCNPROCENTRY __declspec(dllexport)
#	else
#		define LCNPROCENTRY __declspec(dllimport)
#	endif

#	ifndef LCN_PROC_EXPORTS
#		pragma comment(lib,"lcnProc.lib")
#		pragma message("Automatically linking with lcnProc.dll")
#	endif
#else
#	define LCNPROCENTRY
#endif

/**
 @brief			得到系统秒计数器，该值从系统启动开始计数，每秒加1
 @param pIF1	规约操作接口对象
 @retval		参数若无效则返回<0
 */
extern "C" LCNPROCENTRY INT32  LCN_GetSystemPuls(void *pIF1);

/**
 @brief			设置接收的总坏包数量
 @param pIF1	规约操作接口对象
 @param num1	坏包数量
 @retval		返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32  LCN_SetRecvBadPackage(void *pIF1, INT32 num1);

/**
 @brief			设置接收的好包数量
 @param pIF1	规约操作接口对象
 @param num1	好包数量
 @retval		返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32  LCN_SetRecvGoodPackage(void *pIF1, INT32 num1);

/**
 @brief			设置发送的包数量
 @param pIF1	规约操作接口对象
 @param num1	发送的包数量
 @retval		返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32  LCN_SetSendPackage(void *pIF1, INT32 num1);

/**
 @brief			设置遥信值
 @param pIF1	规约操作接口对象
 @param No		节点的遥信序号
 @param iValue	遥信值
 @param flgQ	品质，各位定义见Fr::QBit::
 @retval		返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32 LCN_SetYx(void *pIF1, INT32 No, INT32 iValue, INT32 flgQ=0);

/**
 @brief			按SYSTEMTIME时间格式通知系统有SOE
 @param pIF1	规约操作接口对象
 @param No		节点的遥信序号
 @param tm		SOE发生时间
 @param iValue	遥信值
 @param flgQ	品质，各位定义见Fr::QBit::
 @retval		返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32 LCN_SetSoe(void *pIF1, INT32 No, SYSTEMTIME st, INT32 iValue, INT32 flgQ=0);

/**
 @brief			按INT64时间格式通知系统有SOE
 @param pIF1	规约操作接口对象
 @param No		节点的遥信序号
 @param tm		SOE发生时间
 @param iValue	遥信值
 @param flgQ	品质，各位定义见Fr::QBit::
 @retval		返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32 LCN_SetSoe2(void *pIF1, INT32 No, INT64 tm, INT32 iValue, INT32 flgQ=0);

/**
 @brief			设置浮点数遥测值
 @param pIF1	规约操作接口对象
 @param No		节点的遥测序号
 @param fValue	遥测值
 @param flgQ	品质，各位定义见Fr::QBit::
 @retval		返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32  LCN_SetYcFloat(void *pIF1, INT32 No, FLOAT32 fValue, INT32 flgQ=0);

/**
 @brief			设置整数遥测值
 @param pIF1	规约操作接口对象
 @param No		节点的遥测序号
 @param iValue	遥测值
 @param flgQ	品质，各位定义见Fr::QBit::
 @retval		返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32  LCN_SetYcInteger(void *pIF1, INT32 No, INT32 iValue, INT32 flgQ=0);

/**
 @brief			设置浮点遥脉值
 @param No		节点的遥脉序号
 @param fValue	遥脉值
 @param flgQ	品质，各位定义见Fr::QBit::
 @retval		返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32  LCN_SetYmFloat(void *pIF1, INT32 No, FLOAT32 fValue, INT32 flgQ=0);

/**
 @brief			设置整数遥脉值
 @param No		节点的遥脉序号
 @param iValue	遥脉值
 @param flgQ	品质，各位定义见Fr::QBit::
 @retval		返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32  LCN_SetYmInteger(void *pIF1, INT32 No, UINT32 iValue, INT32 flgQ=0);

/**
 @brief				通知系统遥控返回，供客户端规约调用
 @param pIF1		规约操作接口对象
 @param Action1		遥控性质，Fr::YK_ON(合)， Fr::YK_OFF（分）
 @param ObjectNo1	遥控对象号（节点中的遥控对象序号）
 @param State1		遥控返回状态,YK_ACK(遥控选择返校正确)、YK_NAK(遥控选择返校错误)、YK_EXE(遥控执行确认)、YK_RMV(遥控撤销确认)等
 @param IsDinYk1	是否为双点遥控
 @retval			返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32  LCN_SetYkReturn(void *pIF1, INT32 Action1, INT32 ObjectNo1, INT32 State1, BOOL32 IsDinYk1=FALSE);

/**
 @brief				通知系统遥调返回，供客户端规约调用
 @param pIF1		规约操作接口对象
 @param Action1		遥调性质，Fr::YT_OUT(输出)， Fr::YT_UP（升）， Fr::YT_DOWN（降）,YT_STOP（终止）
 @param ObjectNo1	遥调对象号（节点中的遥调对象序号）
 @param State1		遥调返回状态,YK_ACK(遥调选择返校正确)、YK_NAK(遥调选择返校错误)、YT_EXE(遥调执行确认)、YT_RMV(遥调撤销确认)等
 @retval			返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32  LCN_SetYtReturn(void *pIF1, INT32 Action1, INT32 ObjectNo1, INT32 State1);


/**
 @brief				做遥控，供服务端规约调用
 @param pIF1		规约操作接口对象
 @param Action1		遥控性质，Fr::YK_ON(合)， Fr::YK_OFF（分）
 @param ObjectNo1	遥控对象号（节点中的遥控对象序号）
 @param State1		遥控状态,YKYT_SELECT(遥控遥调选择)、YK_EXE(遥控执行)、YK_RMV(遥控撤消)
 @param IsDinYk1	是否为双点遥控
 @retval			返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32  LCN_DoYk(void *pIF1, INT32 Action1, INT32 ObjectNo1, INT32 State1, BOOL32 IsDinYk1=FALSE);

/**
 @brief				做整数值遥调，供服务端规约调用
 @param pIF1		规约操作接口对象
 @param Action1		遥调性质，Fr::YT_OUT(输出)， Fr::YT_UP（升）， Fr::YT_DOWN（降）,YT_STOP（终止）
 @param ObjectNo1	遥调对象号（节点中的遥调对象序号）
 @param Value1		遥调值
 @param State1		遥调状态,YKYT_SELECT(遥控遥调选择)、YT_EXE(遥调执行)、YT_RMV(遥调撤消)
 @retval			返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32  LCN_DoYtInteger(void *pIF1, INT32 Action1, INT32 ObjectNo1, INT32 Value1, INT32 State1);

/**
 @brief				做浮点数值遥调，供服务端规约调用
 @param pIF1		规约操作接口对象
 @param Action1		遥调性质，Fr::YT_OUT(输出)， Fr::YT_UP（升）， Fr::YT_DOWN（降）,YT_STOP（终止）
 @param ObjectNo1	遥调对象号（节点中的遥调对象序号）
 @param Value1		遥调值
 @param State1		遥调状态,YKYT_SELECT(遥控遥调选择)、YT_EXE(遥调执行)、YT_RMV(遥调撤消)
 @retval			返回值<0表示失败
 */
extern "C" LCNPROCENTRY INT32  LCN_DoYtFloat(void *pIF1, INT32 Action1, INT32 ObjectNo1, FLOAT32 Value1, INT32 State1);

/*
 @brief				直接发遥调命令，仅供给应用类节点调用
 @param pIF1		规约操作接口对象
 @param fdiYt1		执行的遥调对象定义
 @param fv1			输出的值
 @param action1		操作性质，定义见Fr::YT_OUT等
 @param isCheck1	检查当前值，为TRUE时，如果当前值与设定值相同时，控制命令被忽略
 @return			返回值定义见Fr::YKYT_R_
*/
extern "C" LCNPROCENTRY INT32	LCN_DoYtDirectExe(void *pIF1, FrDataIdx fdiYt1, FLOAT32 fv1, INT32 action1=Fr::YT_OUT, BOOL32 isCheck1=FALSE);

/*
 @brief				直接发遥控命令，仅供给应用类节点调用
 @param pIF1		规约操作接口对象
 @param fdiYk1		执行的遥控对象定义
 @param action1		操作性质，定义见Fr::YK_OFF等
 @param state1		遥控状态，遥控执行YK_EXE、遥控撤消YK_RMV
 @param isCheck1	检查当前值，为TRUE时，如果当前值与设定值相同时，控制命令被忽略
 @return			返回值定义见Fr::YKYT_R_
*/
extern "C" LCNPROCENTRY INT32	LCN_DoYkDirectExe(void *pIF1, FrDataIdx fdiYk1, INT32 action1, INT32 state1=Fr::YK_EXE, BOOL32 isCheck1=FALSE);

/**
 @brief			根据INT64的时间获得SYSTEMTIME时间
 @param tm1		INT64时间，从1970年开始的百纳秒数
 @param pSt1	获得的SYSTEMTIME时间
 @retval		转换成功否
 */
extern "C" LCNPROCENTRY BOOL32 LCN_Int64ToSystemtime(const INT64 tm1, SYSTEMTIME * pSt1);

/**
 @brief			根据Systemtime的时间获得INT64时间
 @param st		SYSTEMTIME时间
 @param pTm1	获得的INT64时间
 @retval		转换成功否
 */
extern "C" LCNPROCENTRY BOOL32 LCN_SystemtimeToInt64(const SYSTEMTIME st1, INT64 *pTm1);

/**
 @brief			获得当前SYSTEMTIME时间
 @param pSt1	获得的SYSTEMTIME时间
 */
extern "C" LCNPROCENTRY void LCN_GetCurrSystemtime(SYSTEMTIME * pSt1);

/**
 @brief			输出调试信息
 @param szNote1 调试信息
 */
extern "C" LCNPROCENTRY void LCN_ToDebugMsg(void *pIF1, const CHAR *szNote1);

/**
 @brief					输出通道码调试信息
 @param procType1		通道码的类型，定义见DebugCodeHead::eRecv等
 @param len1			通道码字节长度
 @param buf1			通道码缓冲区
 @param yourAddress1	通道码对应的对方地址,网络规约==0表示不限，串口规约<0表示不限
 @param flgInfor1		通道码对应的信息帧类别, 定义见DebugCodeHead::eFrameYx等
 */
extern "C" LCNPROCENTRY void LCN_ToDebugCode(void *pIF1, INT32 procType1, INT32 len1, UINT8 *buf1, INT32 yourAddress1=0, INT32 flgInfor1=-1);

/**
 @brief			获得节点的对时方式
 @param pIF1	规约操作接口对象
 @retval		返回对时方式，定义见Fr::TimeCheck::
 */
extern "C" LCNPROCENTRY INT32 LCN_GetTimeCheck(void *pIF1);

/**
 @brief			获得节点五遥的数据容量，
 @param pIF1	规约操作接口对象
 @param pFactRtuCapacity 获得的容量结构体
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32 LCN_GetNodeDataCapacity(void *pIF1, FactRtuCapacity *pFactRtuCapacity);

/**
 @brief			设置ncomm设备时间
 @param pIF1	规约操作接口对象
 @param st1		设置的时间
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32 LCN_ModifyMachineTime(void *pIF1, SYSTEMTIME st1);

/**
 @brief			得到规约定义
 @param pIF1	规约操作接口对象
 @param pPtOtherInfo 获得的规约定义
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32 LCN_GetProtocolIdentify(void *pIF1, PTOTHERINFO *pPtOtherInfo);

/**
 @brief			得到组态参数
 @param pIF1	规约操作接口对象
 @param pSize	组态buf的长度
 @retval		返回组态的buf指针
 */
extern "C" LCNPROCENTRY INT8 *LCN_GetZtBuf(void *pIF1, INT32 *pSize);


/**
 @brief			得到转发表定义
 @param pIF1	规约操作接口对象
 @retval		返回转发表指针
 */
extern "C" LCNPROCENTRY const FrTransMapBase *LCN_GetTransMap(void *pIF1);

/**
 @brief			 得到当前遥控遥调消息
 @param pIF1	 规约操作接口对象
 @param msgData1 获得的消息数据
 @retval		 返回消息存在与否
 */
extern "C" LCNPROCENTRY BOOL32  LCN_GetYkYtMsgData(void *pIF1, YkYtMsg *pMsgData1);

/**
 @brief			得到当前变化遥信数量
 @param pIF1	规约操作接口对象
 @retval		返回变化遥信数量
 */
extern "C" LCNPROCENTRY INT32  LCN_GetYxMsgNum(void *pIF1);

/**
 @brief			得到当前变化遥信，参数num1为0以及pMsg1为NULL,表示清除该类消息,转发规约在发送全数据前应该清除所有消息
 @param pIF1	规约操作接口对象
 @param num1	消息的返回缓冲区最大可保存的数量
 @param pMsg1	返回消息的缓冲区
 @retval		返回实际获得的变化遥信数量
 */
extern "C" LCNPROCENTRY INT32  LCN_GetYxMsg(void *pIF1, const INT32 num1, YxMsg *pMsg1);

/**
 @brief			得到当前SOE数量
 @param pIF1	 规约操作接口对象
 @retval		返回变化SOE数量
 */
extern "C" LCNPROCENTRY INT32  LCN_GetSoeNum(void *pIF1);

/**
 @brief			得到当前SOE，参数num1为0以及pMsg1为NULL,表示清除该类消息,转发规约在发送全数据前应该清除所有消息
 @param pIF1	规约操作接口对象
 @param num1	消息的返回缓冲区最大可保存的数量
 @param pMsg1	返回消息的缓冲区
 @retval		返回实际获得的变化SOE数量
 */
extern "C" LCNPROCENTRY INT32  LCN_GetSoe(void *pIF1, const INT32 num1, SoeMsg *pMsg1);

/**
 @brief			得到当前变化遥测数量
 @param pIF1	规约操作接口对象
 @retval		返回变化遥测数量
 */
extern "C" LCNPROCENTRY INT32  LCN_GetYcMsgNum(void *pIF1);

/**
 @brief			得到当前变化遥测，参数num1为0以及pMsg1为NULL,表示清除该类消息,转发规约在发送全数据前应该清除所有消息
 @param pIF1	规约操作接口对象
 @param num1	消息的返回缓冲区最大可保存的数量
 @param pMsg1	返回消息的缓冲区
 @retval		返回实际获得的变化遥测数量
 */
extern "C" LCNPROCENTRY INT32  LCN_GetYcMsg(void *pIF1, const INT32 num1, YcMsg *pMsg1);

/**
 @brief			得到当前变化遥脉数量
 @param pIF1	规约操作接口对象
 @retval		返回变化遥脉数量
 */
extern "C" LCNPROCENTRY INT32  LCN_GetYmMsgNum(void *pIF1);

/**
 @brief			得到当前变化遥脉，参数num1为0以及pMsg1为NULL,表示清除该类消息,转发规约在发送全数据前应该清除所有消息
 @param pIF1	规约操作接口对象
 @param num1	消息的返回缓冲区最大可保存的数量
 @param pMsg1	返回消息的缓冲区
 @retval		返回实际获得的变化遥脉数量
 */
extern "C" LCNPROCENTRY INT32  LCN_GetYmMsg(void *pIF1, const INT32 num1, YmMsg *pMsg1);

/**
 @brief			设置接收消息通知状态
 @param pIF1	规约操作接口对象
 @param pMsgNotifyDef	 消息设置
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32  LCN_SetMsgNotifyDef(void *pIF1, MsgNotifyDef *pMsgNotifyDef);

/**
 @brief			得到本节点的遥信数据
 @param pIF1	规约操作接口对象
 @param no1		遥信数据点号
 @param pData1	遥信数据
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32  LCN_GetYxData(void *pIF1, INT32 no1, YxData *pData1);

/**
 @brief			得到本节点的遥测数据
 @param pIF1	规约操作接口对象
 @param no1		遥测数据点号
 @param pData1	遥测数据
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32  LCN_GetYcData(void *pIF1, INT32 no1, YcData *pData1);

/**
 @brief			得到本节点的遥脉数据
 @param pIF1	规约操作接口对象
 @param no1		遥脉数据点号
 @param pData1	遥脉数据
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32  LCN_GetYmData(void *pIF1, INT32 no1, YmData *pData1);

/**
 @brief			得到本节点的遥控数据
 @param pIF1	规约操作接口对象
 @param no1		遥控数据点号
 @param pData1	遥控数据
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32  LCN_GetYkData(void *pIF1, INT32 no1, YkData *pData1);

/**
 @brief			得到本节点的遥调数据
 @param pIF1	规约操作接口对象
 @param no1		遥调数据点号
 @param pData1	遥调数据
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32  LCN_GetYtData(void *pIF1, INT32 no1, YtData *pData1);


/**
 @brief			得到指定节点的遥信数据
 @param pIF1	规约操作接口对象
 @param fdi1	遥信数据对象
 @param pData1	遥信数据
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32  LCN_SGetYxData(void *pIF1, FrDataIdx fdi1, YxData *pData1);

/**
 @brief			得到指定节点的遥测数据
 @param pIF1	规约操作接口对象
 @param fdi1	遥测数据对象
 @param pData1	遥测数据
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32  LCN_SGetYcData(void *pIF1, FrDataIdx fdi1, YcData *pData1);

/**
 @brief			得到指定节点的遥脉数据
 @param pIF1	规约操作接口对象
 @param fdi1	遥脉数据对象
 @param pData1	遥脉数据
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32  LCN_SGetYmData(void *pIF1, FrDataIdx fdi1, YmData *pData1);

/**
 @brief			得到指定节点的遥控数据
 @param pIF1	规约操作接口对象
 @param fdi1	遥控数据对象
 @param pData1	遥控数据
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32  LCN_SGetYkData(void *pIF1, FrDataIdx fdi1, YkData *pData1);

/**
 @brief			得到指定节点的遥调数据
 @param pIF1	规约操作接口对象
 @param fdi1	遥调数据对象
 @param pData1	遥调数据
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32  LCN_SGetYtData(void *pIF1, FrDataIdx fdi1, YtData *pData1);

/**
 @brief 立即发送数据,不受1024字节长度限制，调试串口最多显示1000字节的信息，函数调用后将延迟10ms，
		该接口慎用，函数在连续多次调用时，注意保持足够长的延迟，延迟不足可能造成数据发送溢出失败
		建议规约程序等待V_SendProc调用中设置发送的数据,V_SendProc函数的间隔时间由组态控制，长度限制为1024字节
 @param pIF1		规约操作接口对象
 @param bytes1		发送的数据长度
 @param dataBuf1	发送的数据缓冲区
 @param iDataType	发送的数据帧类型，每位定义见Fr::FrameType
 @param iChannel1	==0主通道发送, ==1用通道1发送， ==2用通道2发送， == 3通道1、2同时发送
 @retval			返回实际发送的字节数，<0 失败
 */
extern "C" LCNPROCENTRY INT32 LCN_SendDataImmediate(void *pIF1, INT32 bytes1, UINT8 *dataBuf1, INT32 iDataType=0, INT32 iChannel1 = 0);

/**
 @brief			双通道切换
 @param pIF1	规约操作接口对象
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32	LCN_SwitchChannel(void *pIF1);

/**
 @brief			得到节点定义信息
 @param pIF1	规约操作接口对象
 @param pNodeReadmeInfo		节点定义数据对象指针
 @param pData1	节点定义数据对象尺寸，主要是考虑NodeReadmeInfo结构可能版本升级
 @retval		返回成功否
 */
extern "C" LCNPROCENTRY BOOL32	LCN_GetNodeReadmeInfo(void *pIF1, NodeReadmeInfo *pNodeReadmeInfo, INT32 size1);

/**
 @brief			 设置测点数量,规约组态时用
 @param pHandle	 组态接口对象指针
 @param dataSort 数据类别，定义见：Fr::DataSort:
 @param num		 测点数量
 */
extern "C" LCNPROCENTRY void	LCN_CfgSetNodeDataNum(void *pHandle, const INT32 dataSort, const INT32 num);

/**
 @brief			 设置测点名称,规约组态时用
 @param pHandle	 组态接口对象指针
 @param dataSort 数据类别，定义见：Fr::DataSort:
 @param no		 测点序号
 @param name 	 测点名称
 */
extern "C" LCNPROCENTRY void	LCN_CfgSetNodeDataName(void *pHandle, const INT32 dataSort, const INT32 no, const char *name);

/**
 @brief			判断组态是否为英文
 @param pHandle	组态接口对象指针
 @retval		返回是与否
 */
extern "C" LCNPROCENTRY BOOL32	LCN_CfgIsEnglish(void *pHandle);

/**
 @brief			 保存本节点的数据值，主要给应用类节点调用
 @param pIF1	 规约操作接口对象
 @param dataSort 数据类别，定义见：Fr::DataSort:
 @retval		 失败返回-1，正常返回0
 */
extern "C" LCNPROCENTRY INT32	LCN_SaveNodeData(void *pIF1, INT32 dataSort1);

/**
 @brief			判断节点是否运行
 @param pIF1	规约操作接口对象
 @param noNode1 判断的节点号
 @retval		节点运行返回TRUE， 节点停运返回FALSE
 */
extern "C" LCNPROCENTRY BOOL32	LCN_IsNodeRun(void *pIF1, INT32 noNode1);

/**
 @brief			保存扩展数据
 @param pIF1	规约操作接口对象
 @retval		运行返回0， 失败返回-1
 */
extern "C" LCNPROCENTRY INT32	LCN_SaveNodeExtraData(void *pIF1);

/**
 @brief			设置指定节点的扩展数据头定义
 @param pIF1	规约操作接口对象
 @param numNe	节点扩展数据数量
 @param pNeh	节点扩展数据头定义
 @retval		成功返回TRUE， 失败返回FALSE
 */
extern "C" LCNPROCENTRY BOOL32	LCN_SetNodeExtraDataDefine(void *pIF1, INT32 numNe, NodeExtraHead* pNeh);

/**
 @brief			设置本节点扩展数据的值
 @param pIF1	规约操作接口对象
 @param No		节点扩展数据号
 @param tm		节点扩展数据刷新时间
 @param len		节点扩展数据值长度
 @param pData	节点扩展数据值
 @param flgQ	节点扩展数据品质
 @retval		成功返回TRUE， 失败返回FALSE
 */
extern "C" LCNPROCENTRY BOOL32	LCN_SetMyNodeExtraDataValue(void *pIF1, INT32 No, INT64 tm, INT32 len, void *pData, UINT8 flgQ=0);

/**
 @brief			设置指定节点扩展数据的值
 @param pIF1	规约操作接口对象
 @param node	指定的节点号
 @param No		节点扩展数据号
 @param tm		节点扩展数据刷新时间
 @param len		节点扩展数据值长度
 @param pData	节点扩展数据值
 @param flgQ	节点扩展数据品质
 @retval		成功返回TRUE， 失败返回FALSE
 */
extern "C" LCNPROCENTRY BOOL32	LCN_SetNodeExtraDataValue(void *pIF1, INT32 node, INT32 No, INT64 tm, INT32 len, void *pData, UINT8 flgQ=0);

/**
 @brief			获得指定节点和类别的扩展数据数量
 @param pIF1	规约操作接口对象
 @param node	指定的节点号
 @retval		运行返回数量， 失败返回-1
 */
extern "C" LCNPROCENTRY INT32	LCN_GetNodeExtraDataNum(void *pIF1, INT32 node);

/**
 @brief			根据扩展数据名，获得指定节点的扩展数据号
 @param pIF1	规约操作接口对象
 @param node	指定的节点号
 @param nameExtra 扩展数据名
 @retval		返回扩展数据号， 失败返回-1
 */
extern "C" LCNPROCENTRY INT32	LCN_GetNodeExtraNo(void *pIF1, INT32 node, CHAR *nameExtra);

/**
 @brief			获得指定节点的扩展数据头定义
 @param pIF1	规约操作接口对象
 @param node	指定的节点号
 @param No		节点扩展数据头的数量
 @param pNeh	读出的节点扩展数据头定义
 @retval		成功返回TRUE， 失败返回FALSE
 */
extern "C" LCNPROCENTRY BOOL32	LCN_GetNodeExtraDataDefine(void *pIF1, INT32 node, INT32 num, NodeExtraHead* pNeh);

/**
 @brief			读扩展数据的值
 @param pIF1	规约操作接口对象
 @param node	指定的节点号
 @param No		节点扩展数据号
 @param readLen	读值的最大尺寸
 @param pData	读值的存储空间
 @retval		返回值为读出值长度，<0表示读错误
 */
extern "C" LCNPROCENTRY INT32	LCN_GetNodeExtraDataValue(void *pIF1, INT32 node, INT32 No, INT32 readLen, void *pData, INT64 *pTm=NULL, UINT8 *pFlgQ=NULL);

#endif

