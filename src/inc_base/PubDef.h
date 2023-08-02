#ifndef _PUB_DEF_H_
#define _PUB_DEF_H_

#include "stdio.h"
#include "stdlib.h"
#include "BaseConst.h"

/**
@file 公共常量、结构定义
@version v1.01
@author 
@date
*/

namespace Fr{
	const FLOAT32	SystemVersion	= 9.01f;	//系统版本号,若接口不变，一般只改变小数点后的编号
	const INT32		NAME_LENGTH		= 64;		//名称长度

	const CHAR	CONFIG_FILE[NAME_LENGTH]			= "cpm.nc";				//前置系统的配置数据文件名
	const CHAR	CONFIG_FILE_SN[NAME_LENGTH]			= "cpm_sn.txt";			//前置系统的序列号文件名
	const CHAR	CONFIG_FILE_SETTINGS[NAME_LENGTH]	= "cfg_settings.ini";	//前置系统的组态配置文件

	const CHAR	Project[]				= "drcomm";		//项目
	const CHAR	PathLinux[]				= "/mnt/user/drcomm";	//linux路径
	const CHAR	PathExe[]				= "bin";		//执行文件路径
	const CHAR	PathConfig[]			= "config";		//配置文件路径
	const CHAR	PathPlug[]				= "plug";		//规约插件路径
	const CHAR	PathProtocolUpdate[]	= "update";		//升级包路径
	const CHAR	PathHistory[]			= "his";		//历史数据文件路径
	const CHAR	PathLocal[]				= "translate";	//界面翻译文件路径

	//规约通讯模式
	//客户端规约消息发送（数据）缓冲区大，接收（命令）缓冲区小
	//服务端规约消息发送（命令）缓冲区小，接收（数据）缓冲区大
	//服务端规约接收遥控命令报文并下发，客户端接收控制返校报文并上传
	namespace Protocol{
		const INT32 PClient			=0;	//客户端规约，主要收遥信、遥测数据，包括
		const INT32 APP				=1; //应用节点规约，与PClient类似
		const INT32 PServer			=2; //服务端规约，主要发遥信、遥测数据
	};

	//对时方式
	namespace TimeCheck{
		const INT32 None			=0;	//不对时
		const INT32 SendTime		=1; //发送对时
		const INT32 RevTime			=2; //接收对时
	};

	//数据类别
	namespace DataSort{
		const INT32 Yx	=1;	
		const INT32 Yc	=2;	
		const INT32 Ym	=3;	
		const INT32 Yk	=4;	
		const INT32 Yt	=5;	
	};

	namespace DataSourceType{
		const INT8 AllObject		= 0;	//整个对象
		const INT8 RealValue		= 1;	//取处理后的实际值
		const INT8 ChannelCode		= 2;	//取通道码值
		const INT8 FlagQ			= 3;	//取品质
		const INT8 RefreshTime		= 4;	//取刷新时间
		const INT8 DiffRefreshTime	= 5;	//取当前时间的秒数差
	}

	namespace CFG{
		const INT32 NONE		= 0;//规约没有组态信息
		const INT32 UserDef		= 99;  //用户自定义
		const INT32 C_Sample	= 1;
		const INT32 S_Sample	= 2;
		const INT32 C_Modbus	= 3;
		const INT32 S_Modbus	= 4;
		const INT32 C_IEC101	= 5;
		const INT32 S_IEC101	= 6;
		const INT32 C_IEC102	= 7;
		const INT32 S_IEC102	= 8;
		const INT32 C_IEC103	= 9;
		const INT32 S_IEC103	= 10;
		const INT32 C_IEC104	= 11;
		const INT32 S_IEC104	= 12;
		const INT32 C_CDT		= 13;
		const INT32 S_CDT		= 14;
		const INT32 C_DLT645	= 15;
		const INT32 A_SPLC		= 16;
		const INT32 A_NPLC		= 17;
		const INT32 Common		= 100;//通用的组态类型
		const INT32 S_Power		= 101;
		const INT32 S_IEC61850	= 102;
		const INT32 C_SNTP		= 103;
		const INT32 S_SNTP		= 104;
		const INT32 S_Xml		= 105;
		const INT32 S_Xml_JZNY	= 106;
		const INT32 S_FOETAL	= 107;
		const INT32 S_MQTT		= 108;
	};

	namespace FrameType{
		static const INT32 eFrameYx				=    0x01; //遥信数据帧
		static const INT32 eFrameYc				=    0x02; //遥测数据帧
		static const INT32 eFrameYm				=    0x04; //电度数据帧
		static const INT32 eFrameYk				=    0x08; //遥控命令帧
		static const INT32 eFrameYt				=    0x10; //遥调命令帧
		static const INT32 eFrameSoe			=    0x20; //SOE数据帧
		static const INT32 eFrameTime			=    0x40; //对时命令帧
		static const INT32 eFrameRelay			=    0x80; //保护数据帧
		static const INT32 eFrameCurve			=   0x100; //曲线数据帧，含计划值和预测曲线
		static const INT32 eFrameReset			=   0x200; //链路复位帧
		static const INT32 eFrameTest			=   0x400; //链路测试帧
		static const INT32 eFrameQuery			=   0x800; //链路查询帧
		static const INT32 eFrameReply			=  0x1000; //链路应答帧
		static const INT32 eFrameCallAll		=  0x2000; //链路总召帧
		static const INT32 eFrameCallAllReply	=  0x4000; //总召应答帧
		static const INT32 eFrameOther			=  0x8000; //其它数据帧
	};

	//运行状态品质的对应标志位,与IEC61850标准一致
	namespace QBit{
		const INT32 IecInvalidity		=     0x01;	//不变化或值无效
		const INT32 IecQuestionable		=     0x02;	//有疑问
		const INT32 IecOverFlow			=     0x04;	//溢出
		const INT32 IecOutOfRange		=     0x08;	//超出量程
		const INT32 IecBadReference		=     0x10;	//错误索引
		const INT32 IecOscillatory		=     0x20;	//不固定
		const INT32 IecFailure			=     0x40;	//故障
		const INT32 IecOldData			=     0x80;	//旧值
		const INT32 IecInconsistent		=    0x100;	//有矛盾
		const INT32 IecInaccurate		=    0x200;	//不精确
		const INT32 IecSubstituted		=    0x400;	//人工置数,被封锁
		const INT32 IecTest				=    0x800;	//测试
		const INT32 IecOperatorBlocked	=   0x1000;	//被操作闭锁
	};
	
	namespace CommModeForDouble{
		const INT32 MainWork		=0;	//主机(通道)工作
		const INT32 LinkRedundance	=1; //链路冗余，即备机(通道)保持链路连接不接收或发送数据
		const INT32 DataRedundance	=2; //数据冗余，即备机(通道)保持同时接收或发送数据
	};

	const INT32 YkSetType_Default			=0;		//遥控限制按系统规定
	const INT32 YkSetType_Disable			=1;		//禁止遥控

	//Yk State
	const INT32 YK_IDLE					=0;		//空闲
	const INT32 YK_SELECT				=1;		//选择 ,建议用YKYT_SELECT代替
	const INT32 YK_ACK					=2;		//返校正确
	const INT32 YK_NAK					=3;		//返校错误
	const INT32 YK_EXE					=4;		//下行为执行，上行为执行确认
	const INT32 YK_RMV					=5;		//下行为取消，上行为超时取消

	const INT32 YKYT_SELECT				=YK_SELECT;		//控制操作选择
	//Yt State
	//const INT32 YT_IDLE					=100;	//空闲,用YK_IDLE代替
	const INT32 YT_EXE					=101;	//下行为执行，上行为执行确认
	const INT32 YT_RMV					=102;	//下行为取消，上行为超时取消

	//Yk Action(command）
	const INT32 YK_ON					=11;
	const INT32 YK_OFF 					=12;
	const INT32 YK_TQH					=13;	//同期合
	const INT32 YK_JWYH					=14;	//检无压合
	const INT32 YK_BJTQH				=15;	//不检定同期合
	const INT32 YK_HHH					=16;	//合环合
	const INT32 YK_WF_ON				=17;	//五防合
	const INT32 YK_WF_OFF				=18;	//五防分
	const INT32 YK_LOW_CURRENT_OFFON	=19;	//小电流探索试分
	const INT32 YK_NONE					=-1;
	//Yt Action(command)
	const INT32 YT_OUT					=110;	//遥调输出
	const INT32 YT_UP					=111;	//遥调升
	const INT32 YT_DOWN					=112;	//遥调降
	const INT32 YT_STOP					=113;	//遥调中止
	const INT32 YT_NONE					=-1;

	const INT32 YKYT_R_Fault			=0;		//执行失败
	const INT32 YKYT_R_Finish			=1;		//已执行
	const INT32 YKYT_R_Skip				=2;		//被忽略,如果要求操作时间长当前目标值，而目标值与设定值相同，该命令被忽略

	//遥控脉冲类型
	const INT32 YkPulse_No				=0;		//未定义
	const INT32 RELAYTYPE_Short			=1;		//短脉冲
	const INT32 RELAYTYPE_Long			=2;		//长脉冲
	const INT32 RELAYTYPE_Series		=3;		//持续输出
};

//规约实际处理的信息容量
struct FactRtuCapacity
{
	INT32 RealYx;
	INT32 RealYc;
	INT32 RealYm;
	INT32 RealYk;
	INT32 RealYt;

	FactRtuCapacity()
	{
		RealYx=0;
		RealYc=0;
		RealYm=0;
		RealYk=0;
		RealYt=0;
	};
};

struct REALCAPACITY
{
	INT32 RealYx	;
	INT32 RealYc	;	
	INT32 RealYm	;
	INT32 RealYk	;
	INT32 RealYt	;
	INT32 RealSoe	;
	INT32 RealChgYx	;
	INT32 RealRelay	;
	INT32 RealWf	;
	REALCAPACITY()
	{
		RealYx=0;
		RealYc=0;
		RealYm=0;
		RealYk=0;
		RealYt=0;
		RealSoe=0;
		RealChgYx=0;
		RealRelay=0;
		RealWf=0;
	};
};

#ifndef _WINDOWS
typedef struct _SYSTEMTIME {
	UINT16 wYear;
	UINT16 wMonth;
	UINT16 wDayOfWeek;
	UINT16 wDay;
	UINT16 wHour;
	UINT16 wMinute;
	UINT16 wSecond;
	UINT16 wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;
#else
#include <Windows.h>
#endif

//规约处理报文后，需返回的处理报文信息
struct DEALDATAINFO		
{
	INT32  Bytes;					//处理字节数

	BOOL32 isSyncChar;			//（预留）有收到同步字,问答式规约，发送前要设置该标志以通知系统清除上次接收的缓冲数据，方便找到同步头处理
	INT32 iSyncCharPos;			//（预留）同步字在recebuf的位置,如果等于-1，表示该节点不需要接收数据，这样该节点没有接收数据也不会出现停运状况
	char strDataInfo[64];		//（预留）报文信息
	DWORD DataType;				//（预留）信息帧类别的组合标志,见Fr::FrameType::, =-1或0表示无效

	BOOL32 TcpReConnect;			//是否重新连接TCP

	union{
		struct{
			WORD wMutiChn;			//（专用）是否为单通道多厂站
			WORD wNodeNo;				//（专用）厂站号
		};
		INT32 yourAddress;  //智能设备地址（对一个节点与多个设备通讯有用，如485/422挂葫芦等方式）
	};

	void SetDefault()
	{
		memset(this, 0, sizeof(*this));
		yourAddress = -1;
	}

	DEALDATAINFO()
	{
		SetDefault();
	};

};

//转发数据的映射定义
struct FrMapData{
	UINT8	noNode		;	//节点号
	INT8	typeSource	;	//数据来源类型 Fr::DataSourceType定义
	INT16	no		;	//数据点号

	FrMapData(){
		typeSource = Fr::DataSourceType::RealValue;
		noNode = -1;
		no = -1;
	}
};

//转发表定义
struct FrTransMapBase{
	static const INT32 MyVersion = 101;
	INT32 StructVersion;  //用于未来组态参数升级的版本标识
	INT32 StructSize;  //用于未来组态参数升级的版本标识

	INT32 numYx;
	INT32 numYc;
	INT32 numYm;
	INT32 numYk;
	INT32 numYt;
	FrMapData	* yxList;
	FrMapData	* ycList;
	FrMapData	* ymList;
	FrMapData	* ykList;
	FrMapData	* ytList;

	void copyTo(FrTransMapBase &tmp){
		tmp.numYx = numYx;
		tmp.numYc = numYc;
		tmp.numYm = numYm;
		tmp.numYk = numYk;
		tmp.numYt = numYt;
		if (tmp.yxList!=NULL) delete[] tmp.yxList;
		if (tmp.ycList!=NULL) delete[] tmp.ycList;
		if (tmp.ymList!=NULL) delete[] tmp.ymList;
		if (tmp.ykList!=NULL) delete[] tmp.ykList;
		if (tmp.ytList!=NULL) delete[] tmp.ytList;
		tmp.yxList = NULL;
		tmp.ycList = NULL;
		tmp.ymList = NULL;
		tmp.ykList = NULL;
		tmp.ytList = NULL;

		if (yxList!=NULL){ 
			tmp.yxList = new FrMapData[numYx];
			memcpy(tmp.yxList, yxList, sizeof(FrMapData)*numYx);
		}
		if (ycList!=NULL){
			tmp.ycList = new FrMapData[numYc];
			memcpy(tmp.ycList, ycList, sizeof(FrMapData)*numYc);
		}
		if (ymList!=NULL){
			tmp.ymList = new FrMapData[numYm];
			memcpy(tmp.ymList, ymList, sizeof(FrMapData)*numYm);
		}
		if (ykList!=NULL){
			tmp.ykList = new FrMapData[numYk];
			memcpy(tmp.ykList, ykList, sizeof(FrMapData)*numYk);
		}
		if (ytList!=NULL){
			tmp.ytList = new FrMapData[numYt];
			memcpy(tmp.ytList, ytList, sizeof(FrMapData)*numYt);
		}
	}

	void SetDefault(){
		memset(this, 0, sizeof(*this));
		StructVersion = MyVersion;
		StructSize = sizeof(*this);
	}
	FrTransMapBase()
	{
		SetDefault();	
	};
	~FrTransMapBase(){
		if (yxList != NULL) delete[] yxList;
		if (ycList != NULL) delete[] ycList;
		if (ymList != NULL) delete[] ymList;
		if (ykList != NULL) delete[] ykList;
		if (ytList != NULL) delete[] ytList;
	}
};

namespace Fm{
	//消息队列
	namespace MsgQueue{ //消息队列大小
		const INT32 DataSize		= 1024*1024;//client规约的数据发送或server的数据接收队列缓冲区长度
		const INT32 CommandSize		= 1024*128;	//client规约的命令接收或server的命令发送队列缓冲区长度
		const INT32 MaxYxNum		= 3000;
		const INT32 MaxYcNum		= 3000;
		const INT32 MaxYmNum		= 1000;
		const INT32 MaxSoeNum		= 3000;
		const INT32 MaxYkNum		= 1000;
	};

	namespace CB{  //变化标志位
		const INT8 Value	= 0x01;  //值变化
		const INT8 FlagQ	= 0x02;  //品质变化
	};

	namespace Notify{  //消息通知的定义常量
		const INT32 None			= 0x00;  //不通知
		const INT32 Refresh			= 0x01;  //数据刷新
		const INT32 ChangeValue		= 0x02;  //值变化
		const INT32 ChangeValue_Q	= 0x03;  //值或品质变化
	};
}

struct MsgNotifyDef{//实时数据消息接收缓冲区设置
	INT32	yxNum	;//最大变化遥信消息个数,为0消息通知设置无效
	INT32	ycNum	;//最大变化遥测消息个数,为0消息通知设置无效
	INT32	ymNum	;//最大变化遥脉消息个数,为0消息通知设置无效
	INT32	soeNum	;//最大SOE消息个数
	INT32	yxNotify;//遥信消息通知设置,定义见Fm::Notify
	INT32	ycNotify;//遥测消息通知设置,定义见Fm::Notify
	MsgNotifyDef(){
		memset(this, 0, sizeof(*this));
	}
};

#pragma pack(1)

struct FrDataIdx{   //前置数据索引
	BYTE	noNode	;	//节点号0~255, =255表示无效
	BYTE	dataSort;	//数据类别，定义见Fr::DataSort:
	UINT16	no		;	//数据点号, =65535表示无效
	FrDataIdx(){
		noNode = 0;
		dataSort = 0;
		no =0;
	}

	FrDataIdx(BYTE noNode1, BYTE dataSort1, UINT16 no1){ SetData(noNode1, dataSort1, no1); }

	void SetData(const BYTE noNode1, const BYTE dataSort1, const UINT16 no1){
		noNode	= noNode1;
		dataSort= dataSort1;
		no		= no1;
	}
	void SetData(const FrDataIdx& fdi){
		noNode	= fdi.noNode;
		dataSort= fdi.dataSort;
		no		= fdi.no;
	}
	void ResetOrder(BYTE order1)
	{
		if (order1 == BORDER::MY_ORDER)
			return;
		assign_htol(no);
	}

	BOOL32 IsNull(){
		if (dataSort<1) return TRUE; 
		return FALSE;
	}

	//转换为字符串(通用组态表格中的数据索引)
	void ToString(CHAR *str1){
		str1[0] = 0;
		if (dataSort == Fr::DataSort::Yx)
			sprintf(str1, "N%03d<Yx>:%d", noNode, no);
		else if (dataSort == Fr::DataSort::Yc)
			sprintf(str1, "N%03d<Yc>:%d", noNode, no);
		else if (dataSort == Fr::DataSort::Ym)
			sprintf(str1, "N%03d<Ym>:%d", noNode, no);
		else if (dataSort == Fr::DataSort::Yk)
			sprintf(str1, "N%03d<Yk>:%d", noNode, no);
		else if (dataSort == Fr::DataSort::Yt)
			sprintf(str1, "N%03d<Yt>:%d", noNode, no);
	}

	//数据转换为PLC字符串(PLC变量的数据来源索引)
	void ToPlcString(CHAR *str1){
		str1[0] = 0;
		if (dataSort == Fr::DataSort::Yx)
			sprintf(str1, "DI.%d@N%d", no, noNode);
		else if (dataSort == Fr::DataSort::Yc)
			sprintf(str1, "AI.%d@N%d", no, noNode);
		else if (dataSort == Fr::DataSort::Yk)
			sprintf(str1, "DO.%d@N%d", no, noNode);
		else if (dataSort == Fr::DataSort::Yt)
			sprintf(str1, "AO.%d@N%d", no, noNode);
	}

	//设置字符串为节点数据
	BOOL32 SetData(CHAR *text1){
		if ((text1[0]!='N')||(text1[4]!='<')||(text1[5]!='Y')||(text1[7]!='>')||(text1[8]!=':'))
			return FALSE;  //非法数据
		if (strlen(text1)<10)
			return FALSE;
		char ss[32];
		memcpy(ss, text1,sizeof(ss));
		ss[sizeof(ss)-1] = 0;

		ss[4]=0;
		for(INT32 i=1;i<4;i++){
			if (ss[i] ==0)
				break;
			if ((ss[i]<'0')||(ss[i]>'9'))
				return FALSE;
		}
		noNode = atoi(&ss[1]);

		if (text1[6]=='x')
			dataSort = Fr::DataSort::Yx;
		else if (text1[6]=='c')
			dataSort = Fr::DataSort::Yc;
		else if (text1[6]=='m')
			dataSort = Fr::DataSort::Ym;
		else if (text1[6]=='k')
			dataSort = Fr::DataSort::Yk;
		else if (text1[6]=='t')
			dataSort = Fr::DataSort::Yt;
		else
			dataSort = 0;

		for(INT32 i=9;;i++){
			if (ss[i] ==0)
				break;
			if (ss[i] ==' ')
				continue;
			if (ss[i] =='	')
				continue;
			if (ss[i] =='\r')
				break;
			if (ss[i] =='\n')
				break;
			if ((ss[i]<'0')||(ss[i]>'9'))
				return FALSE;
		}
		no = atoi(&ss[9]);
		return TRUE;
	}

	/*
	//设置PLC数据索引字符串为节点数据
	BOOL32 SetPlcData(CHAR *text1){
		CHAR name[64];
		if (strlen(text1) >= sizeof(name))
			return FALSE;
		strcpy(name, text1);

		if (name[2] != '.')
			return FALSE;
		name[2] = 0;

		CHAR *ps = strstr(&name[3], "@");
		if (!ps)
			return FALSE;
		if ((ps[1] != 'N')&&(ps[1] == 'n'))
			return FALSE;
		ps[0] = 0;

		if (strcmp(strupr_s(name), "AI")==0)
			dataSort = Fr::DataSort::Yc; 
		else if (strcmp(strupr(name), "AO")==0)
			dataSort = Fr::DataSort::Yt; 
		else if (strcmp(strupr(name), "DI")==0)
			dataSort = Fr::DataSort::Yx; 
		else if (strcmp(strupr(name), "DO")==0)
			dataSort = Fr::DataSort::Yk;
		else
			return FALSE;

		no = atoi(&name[3]);
		noNode = atoi(&ps[2]);

		return TRUE;
	}
	*/

	void  operator=(const FrDataIdx& op){
		memcpy(this, &op, sizeof(*this));
	}

	BOOL  operator==(const FrDataIdx& op){
		if ((op.noNode == noNode)&&(op.no == no)&&(op.dataSort == dataSort))
			return TRUE;
		return FALSE;
	}

	BOOL  operator!=(const FrDataIdx& op){
		if ((op.noNode != noNode)||(op.no != no)||(op.dataSort != dataSort))
			return TRUE;
		return FALSE;
	}

};

//消息头
struct FrMsgHead{
	INT32	liveTimeSysPuls	;	//消息生存有效的系统秒计数,秒计数值由前置系统提供，
	//不采用绝对时间是防止系统因对时造成计算超时出错 
	//<当前的系统秒计数表示消息失效，<=0肯定失效
	INT32	iSrcAddress		;	//消息发送者的装置地址
	INT32	srcNodeNo		;	//消息发送者的通讯节点号
	INT16	msgType			;	//消息类型,定义见Fm::MT
	INT16	lenData			;	//消息缓冲区实际数据长度，不含FrMsgHead本身
	FrMsgHead(){
		msgType = -1;
		liveTimeSysPuls = -1;
		iSrcAddress = -1;
		srcNodeNo = -1;
		lenData = 0;
	}
};

//保护~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct RelayInfoMsgData	: FrMsgHead	
{
	INT32 RelayType_Ht;			//后台保护类型		（由系统自动填）
	INT32 RelayType_Front;		//前置系统保护类型  （由系统自动填）
	INT32 DevAddr;				//保护设备地址		（由系统自动填）
	INT32 srcOperNodeNo;			//数据来源          （由系统自动填）(前置通讯用： 0 -- 128  调度操作、1000 监控后台操作)

	INT32 RelayType_Protocol;		//通讯规约保护类型  (如果规约保护部分全部采用IEC-870-5-103规约，此处数值无效，不用填)
	BOOL32 bAutoUpData;			//是否为主动上送报文（上行报文使用，默认是）
	INT32 BufLen;					//保护Buffer长度
	BYTE RelayBuffer[400];		//保护Buffer

	WORD Type;					//自定义类型 （数据转发和调度转发模式下为保护类型 Fr_DdTrans_RelayEvent、Fr_DdTrans_WaveMessage、Fr_DdTrans_WaveAnalyze）
	WORD Code;					//自定义类型
	INT32 Reserved[19];			//预留
	RelayInfoMsgData()
	{
		memset(this, 0, sizeof(*this));
		RelayType_Ht=RelayType_Front=DevAddr=-1;			//(-1 表示该结构值无效）
		srcOperNodeNo=1000;
		lenData = sizeof(*this) - sizeof(FrMsgHead);

		RelayType_Protocol=-1;
		bAutoUpData=TRUE;
	};
};

#pragma pack()

const INT32 QBitIec = 0x1fff;
//运行状态品质的IEC标准对应标志位,规约插件设置
const INT32 QBitIecInvalidity		=  Fr::QBit::IecInvalidity		;	//不变化或值无效
const INT32 QBitIecQuestionable		=  Fr::QBit::IecQuestionable	;	//有疑问
const INT32 QBitIecOverFlow			=  Fr::QBit::IecOverFlow		;	//溢出
const INT32 QBitIecOutOfRange		=  Fr::QBit::IecOutOfRange		;	//超出量程
const INT32 QBitIecBadReference		=  Fr::QBit::IecBadReference	;	//错误索引
const INT32 QBitIecOscillatory		=  Fr::QBit::IecOscillatory		;	//不固定
const INT32 QBitIecFailure			=  Fr::QBit::IecFailure			;	//故障
const INT32 QBitIecOldData			=  Fr::QBit::IecOldData			;	//旧值
const INT32 QBitIecInconsistent		=  Fr::QBit::IecInconsistent	;	//有矛盾
const INT32 QBitIecInaccurate		=  Fr::QBit::IecInaccurate		;	//不精确
const INT32 QBitIecSubstituted		=  Fr::QBit::IecSubstituted		;	//人工置数,被封锁
const INT32 QBitIecTest				=  Fr::QBit::IecTest			;	//测试
const INT32 QBitIecOperatorBlocked	=  Fr::QBit::IecOperatorBlocked	;	//被操作闭锁

//平台本身设置的品质位，与IEC品质有对应关系，通信规约使用IEC标准品质，应用节点使用平台品质
const INT32 QBitAbnormal			=   0x2000;	//异常,对应IEC品质 QBitIecFailure|QBitIecQuestionable
const INT32 QBitValueDead			=   0x4000;	//不变化或值无效，对应IEC品质 QBitIecInvalidity|QBitIecOldData
const INT32 QBitManLock				=   0x8000;	//被封锁，对应IEC品质QBitIecSubstituted
const INT32 QBitDisableAlarm		=  0x10000;	//报警被抑制
const INT32 QBitByPass				=  0x20000;	//被旁路

const INT32	QFlgIecValueDead		= QBitIecInvalidity | QBitIecOldData;
const INT32	QFlgIecAbnormal			= QBitIecFailure | QBitIecQuestionable | QBitIecInconsistent;
const INT32	QFlgIecManset			= QBitIecSubstituted;

const INT32 QBitNotUpdate	= QBitValueDead | QBitIecInvalidity | QBitIecOldData;   //值不刷新
const INT32 QBitFault		= QBitAbnormal | QBitIecQuestionable | QBitIecFailure;  //值故障
const INT32 QBitErr			= QBitFault | QBitNotUpdate;							//值错误，包括不刷新、值故障

struct NodeYxBaseData
{
	static const INT32 QBitChange				=  0x40000;	//变位
	static const INT32 QBitAccident				=  0x80000;	//事故
	static const INT32 QBitSimulateState		= 0x100000;	//仿真状态
	static const INT32 QBitWFState				= 0x200000;	//五防预演状态
	static const INT32 QBitAskRevert			= 0x400000;	//请求信号复归

	//处理标志的对应标志位
	static const INT32 PBitNoValueDeadStat	=    0x01;	//不判断值无效	
	static const INT32 PBitIec61850Flag		=	 0x02;	//IEC61850标志有效
	static const INT32 PBitReverse			=    0x04;	//状态取反
	static const INT32 PBitSOEAsCOS			=    0x08;	//SOE作为COS

	static const INT32 PBitCosAlarm			=    0x10;	//有历史记录
	static const INT32 PBitAbnormalAlarm	=    0x20;	//是异常告警,有历史记录时有效
	static const INT32 PBitFaultAlarm		=    0x40;	//是故障告警,有历史记录时有效，如果既不是异常又不是故障,则算提示告警

	CHAR	szName[Fr::NAME_LENGTH];  //名称
	INT32	flgProc		;	//处理标志

	NodeYxBaseData(){
		memset(this, 0, sizeof(*this));
	}
} ;

struct NodeYcBaseData
{
	//运行状态品质的对应标志位
	static const INT32 QBitOverHiLimit			=   0x40000;	//越上限
	static const INT32 QBitOverLoLimit			=   0x80000;	//越下限
	static const INT32 QBitOverHiHiLimit		=  0x100000;	//越上上限
	static const INT32 QBitOverLoLoLimit		=  0x200000;	//越下下限
	static const INT32 QBitOverLimit			=  0x400000;	//越限
	static const INT32 QBitValueUpBreak			=  0x800000;	//上跳变发生
	static const INT32 QBitValueDownBreak		= 0x1000000;	//下跳变发生
	static const INT32 QBitValueOverFlow		= 0x4000000;	//溢出
	static const INT32 QBitValueOutOfRange		= 0x8000000;	//超出量程

	static const INT32 QBitOverUnion			= QBitOverLimit | QBitOverLoLoLimit | QBitOverHiHiLimit | QBitOverLoLimit | QBitOverHiLimit;

	static const INT32 QBitYcSacad				= 0xffc0000;	//SCADA处理的标志位

	//处理标志的对应标志位
	static const INT32 PBitNoValueDeadStat		=      0x01;	//不判断值无效
	static const INT32 PBitIec61850Flag			=	   0x02;	//IEC61850标志有效
	static const INT32 PBitReverse				=      0x04;	//符号变反
	static const INT32 PBitAbsolute				=      0x08;	//取绝对值
	//static const INT32 PBitGrads				=      0x10;	//梯度处理
	//static const INT32 PBitJudgeOverLimit		=      0x20;	//判越限
	//static const INT32 PBitValueBreakAlarm	=      0x40;	//值突变处理
	//static const INT32 PBitSimpleValueBreakAlarm=      0x80;	//简单突变处理

	static const INT32 PBitBak1					=      0x10;	//备用
	static const INT32 PBitBak2					=      0x20;	//备用
	static const INT32 PBitBak3					=      0x40;	//备用
	static const INT32 PBitAlarmAbnormal		=      0x80;	//异常告警,如果为0，越上下限为提示告警，越超限为异常告警;如果为1，越上下限为异常告警，越超限为故障告警;
	
	static const INT32 PBitExistPlan			=     0x100;	//有计划值
	static const INT32 PBitTrendData			=     0x200;	//保留趋势曲线数据
	static const INT32 PBitCoeff				=     0x400;	//需要乘系数变换，程序自动判断系数和基值处理

	static const INT32 PBitHisSample			=     0x800;	//有历史采样，固定1分钟记录
	static const INT32 PBitHisStat				=    0x1000;	//有历史统计，包括平均、最大与最小及时间
	static const INT32 PBitEveryMinStat			=    0x2000;	//每分钟统计，缺省是每日统计
	static const INT32 PBitZeroNotStat			=    0x4000;	//零值不统计

	static const INT32 PBitStaticHisSample		=    0x8000;	//有历史采样，静态状态，防原始配置被修改，数据加载时被复制
	static const INT32 PBitStaticHisStat		=   0x10000;	//有历史统计，静态状态，防原始配置被修改，数据加载时被复制
	static const INT32 PBitStaticEveryMinStat	=   0x20000;	//每分钟统计，静态状态，防原始配置被修改，数据加载时被复制


	CHAR	szName[Fr::NAME_LENGTH];  //名称
	INT32	flgProc				;//处理标志

	FLOAT32	fBaseValue			;//基值
	FLOAT32	fCoefValue			;//系数 fCoefValue = fFactorValue * fScaleValue
	FLOAT32	fScaleValue			;//标度系数
	FLOAT32	fFactorValue		;//参比因子
//	FLOAT32	fFilterValue		;//滤波系数
	FLOAT32	fDelaySec			;//延迟时间, 单位秒,修改时间：2020.1.7,取代fFilterValue
	FLOAT32	fRemainsValue		;//残差，也是越限判断死区，大于死区立即告警，在死区范围，要判断延迟时间
	FLOAT32	fValidUpperValue	;//有效上限
	FLOAT32	fValidLowerValue	;//有效下限
	FLOAT32	fNormalUpperValue	;//合理上限
	FLOAT32	fNormalLowerValue	;//合理下限
	FLOAT32	fGradsValue			;//有效梯度
	CHAR	szUnitName[16]		;//单位

	void SetDefault()
	{
		memset(this, 0, sizeof(*this));
		fCoefValue = 1.0f;
		fScaleValue = 1.0f;
		fFactorValue = 1.0f;
		fValidUpperValue = (FLOAT32)0x7fffffff;
		fValidLowerValue = (FLOAT32)(0-0x7fffffff);
		fNormalUpperValue = (FLOAT32)0x7fffffff;
		fNormalLowerValue = (FLOAT32)(0-0x7fffffff);
	}
	NodeYcBaseData(){
		SetDefault();
	}
};

struct NodeYmBaseData
{
	//处理标志的对应标志位
	static const INT32 PBitNoValueDeadStat		=    0x01;	//不判断值无效	

	static const INT32 PBitHisSample		=    0x02;	//有历史采样，随遥测采样周期,ym的数据自动按遥测编号进行排列，如m个yc，第n个ym的历史记录数据号按遥测m+n点号来计算。
	static const INT32 PBitStaticHisSample	=    0x04;	//有历史采样，静态状态，防原始配置被修改，数据加载时被复制

	CHAR	szName[Fr::NAME_LENGTH]	;//名称
	INT32	flgProc				;//处理标志

	FLOAT32	fScaleValue			;//倍率
	INT32	iComputeType				;//计算方式(备用)
	UINT32	numPulseEveryKwh			;//每度脉冲数
	UINT32	numFullPulse				;//脉冲满码值
	UINT32	numValidPulse				;//脉冲计数有效值
	FLOAT32	fFullValue					;//电度满码值
	CHAR	szUnitName[Fr::NAME_LENGTH]	;//单位

	void SetDefault()
	{
		memset(this, 0, sizeof(*this));
		fScaleValue = 1.0f;
		numPulseEveryKwh	= 1		;//每度脉冲数
		numFullPulse		= 0xffffff;//脉冲满码值
		numValidPulse		= 30000  ;//脉冲计数有效值
		fFullValue			= 10000	;//电度满码值
	};
	NodeYmBaseData(){
		SetDefault();
	}
};

struct NodeYkBaseData
{
	static const INT32 PBitForbidControlClose	=   0x01;//遥控合被封锁
	static const INT32 PBitForbidControlOpen	=   0x02;//遥控分被封锁
	static const INT32 PBitWFForbidControlClose	=   0x04;//防误合操作被封锁
	static const INT32 PBitWFForbidControlOpen	=   0x08;//防误分操作被封锁
	static const INT32 PBitControlReverse		=   0x10;//控制令翻转,即分作合、合作分, 闭锁以翻转前为准

	CHAR	szName[Fr::NAME_LENGTH];  //名称
	INT32	iYxAddress	;	//对应遥信值的遥信节点装置地址号
	INT32	yxNo		;	//对应遥信值的遥信节点序号
	INT32	flgProc		;	//处理标志
	INT32	YkPulse		;	//遥控脉冲类型,定义见Fr::RELAYTYPE_Short等

	void SetDefault(){
		memset(this, 0, sizeof(*this));
		YkPulse=Fr::RELAYTYPE_Short;
		iYxAddress = -1;
		yxNo = -1;
	}

	NodeYkBaseData()
	{
		SetDefault();
	};

	BOOL32 IsBlocked(INT32 Action1){
		if (Action1 == Fr::YK_OFF)
//			if ((flgProc & PBitForbidControlOpen)||(flgProc & PBitWFForbidControlOpen))
			if (flgProc & PBitForbidControlOpen) //for miu
				return TRUE;
		if (Action1 == Fr::YK_ON)
//			if ((flgProc & PBitForbidControlClose)||(flgProc & PBitWFForbidControlClose))
			if (flgProc & PBitForbidControlClose) //for miu
				return TRUE;
		return FALSE;
	}
};

struct NodeYtBaseData
{
	static const INT32 PBitForbid		=   0x01;//遥调操作被封锁
	static const INT32 PBitForbidUp		=   0x02;//遥调升操作被封锁
	static const INT32 PBitForbidDown	=   0x04;//遥调降操作被封锁
	static const INT32 PBitWFForbid		=   0x08;//防误遥调操作被封锁
	static const INT32 PBitWFForbidUp	=   0x10;//防误遥调升操作被封锁
	static const INT32 PBitWFForbidDown	=   0x20;//防误遥调降操作被封锁
	static const INT32 PBitControlReverse	=   0x40;//控制令翻转,即升作降、降作合, 闭锁以翻转前为准

	CHAR	szName[Fr::NAME_LENGTH];  //名称
	INT32	iYcAddress	;	//对应遥测值的遥测节点装置地址号
	INT32	ycNo		;	//对应遥测值的遥测节点序号
	INT32	flgProc		;	//处理标志
	FLOAT32	fStepValue	;	//每次遥调固定升降的模拟量值(浮点值)

	void SetDefault()
	{
		memset(this, 0, sizeof(*this));
		iYcAddress = -1;
		ycNo = -1;
	};
	NodeYtBaseData(){
		SetDefault();
	}

	BOOL32 IsBlocked(INT32 Action1){
		if (flgProc & PBitForbid)
			return TRUE;
		if (Action1 == Fr::YT_UP)
//			if ((flgProc & PBitForbidUp)||(flgProc & PBitWFForbidUp))
			if (flgProc & PBitForbidUp)  //for miu
				return TRUE;
		if (Action1 == Fr::YT_DOWN)
//			if ((flgProc & PBitForbidDown)||(flgProc & PBitWFForbidDown))
			if (flgProc & PBitForbidDown)  //for miu
				return TRUE;
		return FALSE;
	}
};

struct COMMPARA {
	static const INT32 CommType_None	= 0;
	static const INT32 CommType_SeriPort= 1;//串口
	static const INT32 CommType_Net		= 2;//专网
	static const INT32 CommType_URL		= 3;//公网

	static const UINT8 SeriPort_RS232	=0;
	static const UINT8 SeriPort_RS485	=1;
	static const UINT8 SeriPort_RS422	=2;

	static const INT32 NetType_Udp		= 0;
	static const INT32 NetType_TcpServer= 1;
	static const INT32 NetType_TcpClient= 2;

	union{
		struct{
			CHAR	ComPort[Fr::NAME_LENGTH]		;	//串口通讯端口
			CHAR	ComSetting[Fr::NAME_LENGTH]		;	//串口通讯参数
		};
		struct{
			CHAR	noUseChar[8]					;	//w无用字符
			BOOL32	isSSL							;	//是否safe socket连接，认证文件与规约名相同，去掉c_,后缀为_ca.crt,如c_91greenpower.lcn插件的认证文件名为91greenpower_ca.crt
			UINT32	port_of_domain					;	//域主机通信服务端口号
			CHAR	domainName[Fr::NAME_LENGTH*2-16];	//域主机名
		};
	};

	UINT8	nCommType		;	//通讯口类型,COMMPARA::CommType_SeriPort等
	UINT8	NetType			;	//网络连接类型,COMMPARA::NetType_TcpServer等
	UINT16	MaxClientNum	;	//最多的客户端连接数, 为0不限制，对COMMPARA::NetType_TcpServer有效

	INT32	YouNetIp		;	//对侧机IP
	UINT32	YouNetPort		;	//对侧机端口号
	UINT32	MyNodeNetPort	;	//本机端口号
	UINT32	MyNodeNetIp		;	//本机端IP
	UINT8	SeriPortType	;	//串口类型,COMMPARA::SeriPort_RS
	CHAR	noUse[3]		;	//备用字节
	CHAR	bakBytes[20]	;	//备用字节

	void SetDefault()
	{
		memset(this, 0, sizeof(*this));
		memcpy(ComPort,"com2",4);
		memcpy(ComSetting,"1200,n,8,1",10);
		YouNetIp = 0x7f000001;
		YouNetPort=9151;
		MyNodeNetPort=9152;
	};

	BOOL32 IsTcp()
	{
		if (nCommType != COMMPARA::CommType_Net)
			return FALSE;
		if  (NetType == COMMPARA::NetType_TcpServer)
			return TRUE;
		if  (NetType == COMMPARA::NetType_TcpClient)
			return TRUE;
		return FALSE;
	}

	COMMPARA(){
		SetDefault();
	}
};

struct HardWareInfor{   //设备硬件数据信息
	FLOAT32		fCpuLoadRate	;	//CPU负载率
	FLOAT32		fCpuLoadMinute5	;	//5分钟内CPU平均负载
	FLOAT32		fRamUse			;	//内存使用量百分比
	FLOAT32		fOutMemUse		;	//外存使用量百分比
	FLOAT32		fTotalOutMemSpace;	//外存总容量,单位M
	FLOAT32		fTotalRamSpace	;	//内存总容量,单位M
	FLOAT32		fCpuLoadForMain ;	//主程序的CPU负载率
	FLOAT32		fRamUseForMain	;	//主程序的内存占用率

	HardWareInfor(){
		memset(this, 0, sizeof(*this));
	}

	void ResetMyOrder(UINT8 srcOrder1)
	{
		if (srcOrder1 == BORDER::MY_ORDER)
			return;
		assign_htol(fCpuLoadRate	);
		assign_htol(fCpuLoadMinute5	);
		assign_htol(fRamUse			);
		assign_htol(fOutMemUse		);
		assign_htol(fTotalOutMemSpace);
		assign_htol(fTotalRamSpace	);
		assign_htol(fCpuLoadForMain	);
		assign_htol(fRamUseForMain	);
	}
};

struct NodeExtraHead{ //节点扩展数据头结构  add on 2017.03.25
	static const INT32 S_Normal			=  0;	//普通
	static const INT32 S_NamePlate		=  1;	//铭牌参数,是静态信息
	static const INT32 S_Identification	=  2;	//身份标识，用于区分设备唯一性的静态信息
	static const INT32 S_Setting		=  3;	//定值
	static const INT32 S_Log			=  4;	//日志信息
	static const INT32 S_History		=  5;	//历史数据

	static const INT32 QBitInvalid	=  0x01;	//数据无效
	static const INT32 QBitError	=  0x02;	//数据无效

	static const INT32 PBitSave		=  0x01;	//需要保存

	CHAR	name[32]	;//参数描述：CHAR数组类型，参数的含义，长度为32的字符串
	INT32	size		;//有效数据分配空间
	UINT8	sort		;//数据类别,定义见：NodeExtraHead::S_
	UINT8	dataType	;//数据类型,定义见：BDT::
	UINT8	flgProc		;//处理标志,定义见：NodeExtraHead::PBit
	UINT8	flgQ		;//品质,定义见：NodeExtraHead::QBit
	INT32	dataLen		;//数据值的实际长度
	INT64	tm			;//刷新时间，数据被规约实时更新的时间

	//初始化扩展数据头定义，处理标志缺省为需要保存
	void Init(const CHAR *name1, INT32 size1, UINT8 sort1, UINT8 dataType1, UINT8 flgProc1=NodeExtraHead::PBitSave){
		memset(this, 0, sizeof(*this));
		strcpy(name, name1);
		size	= size1;
		sort	= sort1;
		dataType= dataType1;
		flgProc = flgProc1;
	}
};

#endif
