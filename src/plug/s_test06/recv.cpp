#include "s_myLcn.h"
#include "LcnProc.h"

INT32 CMyLcn_S::ParsePacket(const UINT8* buf, const INT32 len)
{
	if ( NULL == buf )
	{
		return -1;
	}

	switch ( buf[0] )
	{
	case TYPECODE::YKSIN:		// 是单点遥控报文
		DataInfo.DataType |= Fr::FrameType::eFrameYk;
		IsACK = TRUE;
		return ProcessYkSin(buf, len);
	case TYPECODE::YKDIN:		// 是双点遥控报文
		DataInfo.DataType |= Fr::FrameType::eFrameYk;
		IsACK = TRUE;
		return ProcessYkDin(buf, len);
	case TYPECODE::YT:			// 是遥调报文
		DataInfo.DataType |= Fr::FrameType::eFrameYt;
		IsACK = TRUE;
		return ProcessYt(buf, len);
	case TYPECODE::CallAll:		// 是总召报文
		IsCallAllData = TRUE;
		DataInfo.DataType |= Fr::FrameType::eFrameCallAllReply;
		return len;
	case TYPECODE::ALL_YX :
		DataInfo.DataType |= Fr::FrameType::eFrameYx;
		IsCallYx = TRUE;
		return len;
	case TYPECODE::ALL_YC :
		DataInfo.DataType |= Fr::FrameType::eFrameYc;
		IsCallYc = TRUE;
		return len;
	case TYPECODE::ALL_YM :
		DataInfo.DataType |= Fr::FrameType::eFrameYm;
		IsCallYm = TRUE;
		return len;
	case TYPECODE::SetTime :
		DataInfo.DataType |= Fr::FrameType::eFrameTime;
		return ProcessSetTime(buf, len);
	default :
		return -1;  //不能识别的报文
	}
}

// 处理单点遥控报文
INT32 CMyLcn_S::ProcessYkSin(const UINT8* buf, const INT32 len)
{
	INT32 Action = buf[1];		// 0:动作是分(1->0); 1:动作是分(0->1)
	INT32 ObjectNo = 0;			// 假设遥控对象号为0

	LCN_DoYk(pIF, Action, ObjectNo, Fr::YK_EXE);		// Fr::YK_EXE是立即执行

	return len;
}

// 处理双点遥控报文
INT32 CMyLcn_S::ProcessYkDin(const UINT8* buf, const INT32 len)
{
	INT32 Action = buf[1];		// 1:动作是分(1->0); 2:动作是分(0->1)
	INT32 ObjectNo = 1;			// 假设遥控对象号为1

	LCN_DoYk(pIF, Action, ObjectNo, Fr::YK_EXE, TRUE);

	return len;
}

// 处理遥调报文
INT32 CMyLcn_S::ProcessYt(const UINT8* buf, const INT32 len)
{
	INT32 ObjectNo = 0;		// 假设遥调对象号为0
	INT32 iValue = MAKEWORD(buf[1], buf[2]);

	LCN_DoYtInteger(pIF, Fr::YT_OUT, ObjectNo, iValue, Fr::YT_EXE);

	return len;
}

// 处理对时报文
INT32 CMyLcn_S::ProcessSetTime(const UINT8* buf, const INT32 len)
{
	if ( len < 10 )
	{// 对时报文数据长度不足10
		return -1;
	}

	if ( LCN_GetTimeCheck(pIF) != Fr::TimeCheck::RevTime )
	{// 节点组态配置不允许接收对时
		return len;
	}

	SYSTEMTIME st;
	// 时标举例:2016年1月3日15时20分10秒1000毫秒
	// 时标报文:E0 07 01 03 0F 14 0A E8 03
	st.wYear		= buf[2] << 8;
	st.wYear		+= buf[1];
	st.wMonth		= buf[3]; 
	st.wDay			= buf[4]; 
	st.wHour		= buf[5];
	st.wMinute		= buf[6];
	st.wSecond	= buf[7];
	st.wMilliseconds = buf[9] << 8;
	st.wMilliseconds += buf[8];

	LCN_ModifyMachineTime(pIF, st);

	return len;
}
