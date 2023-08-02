#ifndef _LCN_STRUCT_DEF_H_
#define _LCN_STRUCT_DEF_H_

#include "PubDef.h"
#include "LCNTIME.h"

/**
@file LCN用到的结构定义
@version v1.01
@author 
@date 
*/

//节点自描述(配置)的信息
struct NodeReadmeInfo{
	INT32	No						;	//节点号
	CHAR	Name[Fr::NAME_LENGTH]	;   //节点名
	INT32	nNodeType				;	//节点类型，Fr::Protocol定义
	UINT32	dwZzAdr					;	//装置地址
	CHAR	ProtocolFile[Fr::NAME_LENGTH];	//规约文件名,不含路径
	INT32	noTransDataSet			;	//转发表号
	INT32	numChannel				;	//通道数量,取值0～2
	INT32	CommModeForDoubleMachine;	//双机通讯模式， Fr::CommModeForDouble定义
	INT32	CommModeForDoubleChannel;	//双通道通讯模式， Fr::CommModeForDouble定义
	INT32	YkSet					;	//遥控设置类型， Fr::YkSetType_
	CHAR	NodeDeviceType[16]		;	//节点设备类型
};


//消息队列中的变化遥信~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct YxMsg
{
	INT32	no			;	//遥信点号,为消息处理对象节点所在的点号，系统在派发时会转换为接收对象节点的点号
	INT32	iCodeValue	;	//通道码值
	INT32	iValue		;	//遥信值,由转发表配置决定是否是通道码值还是处理后的值
	LCNTIME   t			;	//刷新时间
	INT32	flgQ		;	//运行品质标志
	INT8	typeSource	;	//数据来源类型 Fr::DataSourceType定义
	INT8	flgChange	;	//数据变化标志,Fm::CB::定义

	YxMsg()
	{
		no = -1;
		flgChange = 0;
	};
};

//消息队列中的SOE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct SoeMsg
{
	INT32	no			;	//遥信点号，为消息处理对象节点所在的点号，系统在派发时会转换为接收对象节点的点号
	INT32	iCodeValue	;	//通道码值
	INT32	iValue		;	//遥信值,由转发表配置决定是否是通道码值还是处理后的值
	LCNTIME   tmSoe		;	//发生时间
	INT32	flgQ		;	//运行品质标志
	INT8	typeSource	;	//数据来源类型 Fr::DataSourceType定义
	INT8	flgChange	;	//数据变化标志，无效

	SoeMsg()
	{
		no = -1;
		flgChange = 0;
	}
};

//消息队列中的变化遥测~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct YcMsg
{
	INT32	no			;	//遥测点号，为消息处理对象节点所在的点号，系统在派发时会转换为接收对象节点的点号
	INT32	iCodeValue	;	//整数型节点码值
	FLOAT32 fValue		;	//浮点型遥测值,由转发表配置决定是否是通道码值还是处理后的值
	LCNTIME   t			;	//刷新时间
	INT32	flgQ		;	//运行品质标志
	INT8	typeSource	;	//数据来源类型 Fr::DataSourceType定义
	INT8	flgChange	;	//数据变化标志 Fm::CB::定义

	YcMsg()
	{
		no = -1;
		flgChange = 0;
	}
};

//消息队列中的遥脉~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct YmMsg
{
	INT32	no			;	//遥脉点号,为消息处理对象节点所在的点号，系统在派发时会转换为接收对象节点的点号
	UINT32	uCodeValue	;	//整数型节点码值（通过PTOTHERINFO.bDataFloat决定采用哪一种类型遥测值，默认是UINT32）
	FLOAT32	fCodeValue	;	//浮点数型节点码值(fCodeValue 与uCodeValue同时存在)
	FLOAT32 fValue		;	//经处理的浮点型电度值，如果不发生翻转，fPrimaryValue = fSecondaryValue * fScaleValue
	LCNTIME   t			;	//刷新时间
	INT32	flgQ		;	//运行品质标志
	INT8	typeSource	;	//数据来源类型 Fr::DataSourceType定义
	INT8	flgChange	;	//数据变化标志,Fm::CB::定义

	YmMsg()
	{
		no = -1;
		flgChange = 0;
	}
};

struct YkYtMsg{
	LCNTIME   OperateTime;	//操作时间
	INT32   DdYk_ZzAdr;		//操作的源节点装置地址

	INT32	ObjectNo;		//本节点对应的遥控遥调对象号,系统在派发时会根据UpYk的ObjectNo和转发表换算为接收对象节点的点号
	INT32	srcOperObjectNo_ExecNodeNo;//操作的源节点的遥控遥调对象号（由系统自动填）UpYk非客户端规约有效，DownYk客户端规约有效
	//注：对于应用类节点，因为没有转发表，源节点对象号已经无效，实际上指真正出口的节点号
	INT32	srcOperNodeNo;	//数据来源节点号    （由系统自动填）(前置通讯用)  Ns3000 是DataSource
	INT32	Action;			//若是遥控，=Fr::YK_ON等，操作合、操作分、同期合、检无压合、不检定同期合、合环合、五防合、五防分、小电流探索试分等
	//若是遥调，=Fr::YT_OUT等，

	INT32	State;			//若是遥控，=Fr::YK_IDLE等，运行状态（没有遥控:空闲YK_IDLE。
	BOOL32	IsYk;			//遥控 or 遥调

	BOOL32	IsDinYk;		//是否双点遥控

	INT32	CaliInfo;		//遥控 or 遥调 返回码, 定义见NS::YkErrExplain::e, 针对返回YK_NAK的错误解释

	INT32    OtherType;		//OtherType=0 正常遥控、OtherType=1  模拟量(浮点值)输出，OtherType=2  模拟量(整数值)输出。其它值无效。

	FLOAT32 OtherValue;		//模拟量(浮点值)  OtherType=1
	INT32	OtherValue2;	//模拟量(整数值)  OtherType=2
	INT32	srcState;		//源遥控状态，用于控制返校时保留原始状态
};


struct YxData : NodeYxBaseData{
	LCNTIME	t			;	//刷新时间
	INT32	iCodeValue	;	//遥信通道码
	INT32	iValue		;	//遥信值，经处理
	INT32	flgQ		;	//运行品质标志
	YxData(){
		memset(this, 0, sizeof(*this));
	}
};

struct YcData : NodeYcBaseData{
	LCNTIME	t					;//刷新时间（由系统自动填）
	INT32	iCodeValue			;//整数型通道码值（通过PTOTHERINFO.bDataFloat决定采用哪一种类型遥测值，默认是INT32）
	FLOAT32 fCodeValue			;//浮点型通道码值(fCodeValue 与iCodeValue同时存在)
	FLOAT32 fValue				;//浮点型遥测值，经处理 = fCodeValue * fCoefValue + fBaseValue
	INT32	flgQ				;//运行品质标志

	YcData(){
		memset(this, 0, sizeof(*this));
	}
};

struct YmData : NodeYmBaseData{
	LCNTIME	t					;//刷新时间（由系统自动填）
	UINT32	uCodeValue			;//整数型通道码值（通过PTOTHERINFO.bDataFloat决定采用哪一种类型遥测值，默认是UINT32）
	FLOAT32 fCodeValue			;//浮点型通道码值(fCodeValue 与uCodeValue同时存在)
	FLOAT32 fValue				;//浮点型电度值，经处理,如果不发生翻转，fPrimaryValue = fSecondaryValue * fScaleValue
	INT32	flgQ				;//运行品质标志
	FLOAT32	fSecondaryValue		;//二次电度值

	YmData(){
		memset(this, 0, sizeof(*this));
	}
};


struct YkData : NodeYkBaseData{
	LCNTIME	OperateTime		;	//最近操作时间
	LCNTIME	ReturnTime		;	//命令返回时间
	UINT32	dwOperateZzAdr	;	//最近操作命令节点的装置地址,对于服务规约，为实际下发控制的节点，对于客户规约，则为控制命令的来源节点
	INT32	srcOperObjectNo	;	//最近操作命令节点遥控对象号,对于服务规约，为实际下发控制的节点对象号，对于客户规约，则为控制命令的来源节点的对象号
	INT32	Action			;	//操作合、操作分、同期合、检无压合、不检定同期合、合环合、五防合、五防分、小电流探索试分等
	INT32	srcOperNodeNo	;	//最近操作命令节点号（由系统自动填）,对于服务规约，为实际下发控制的节点，对于客户规约，则为控制命令的来源节点
	INT32	State			;	//运行状态（没有遥控:空闲。下行:遥控选择、遥控执行、遥控撤消。上行:返校正确、返校错误等）(-1 表示该结构值无效）
	INT32	iReturnInfo		;	//遥控返回码 Ns2000中为CaliInfo
	UINT32	DdYk_RtuNo		;	//调度转发模式专用：通讯接口参数 - 厂站号					（DdYk_Type=0）

	YkData(){
		memset(this, 0, sizeof(*this));
	}
};

struct YtData : NodeYtBaseData{
	LCNTIME	OperateTime		;	//最近操作时间
	LCNTIME	ReturnTime		;	//命令返回时间
	UINT32	dwOperateZzAdr	;	//最近操作命令节点的装置地址,对于服务规约，为实际下发控制的节点，对于客户规约，则为控制命令的来源节点,debugtool中用作对应的遥控或遥调值
	INT32	srcOperObjectNo	;	//最近操作命令节点遥控对象号,对于服务规约，为实际下发控制的节点，对于客户规约，则为控制命令的来源节点
	INT32	Action			;	//遥调模拟量输出、遥调升执行、遥调降执行、遥调撤消等
	INT32	srcOperNodeNo	;	//最近操作命令节点号（由系统自动填）,对于服务规约，为实际下发控制的节点，对于客户规约，则为控制命令的来源节点
	INT32	State			;	//运行状态（没有遥调:空闲。下行:遥调执行、遥调撤消。上行:返校正确、返校错误等）(-1 表示该结构值无效）
	INT32	iReturnInfo		;	//遥调返回码
	INT32	iOutType		;	//输出类型， ==1 表示浮点值输出，==2表示整数值输出
	INT32	iOutValue		;	//模拟量(整数值)
	FLOAT32	fOutValue		;	//模拟量(浮点值)

	YtData(){
		memset(this, 0, sizeof(*this));
	}
};

#endif
