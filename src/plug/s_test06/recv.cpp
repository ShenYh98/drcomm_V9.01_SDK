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
	case TYPECODE::YKSIN:		// �ǵ���ң�ر���
		DataInfo.DataType |= Fr::FrameType::eFrameYk;
		IsACK = TRUE;
		return ProcessYkSin(buf, len);
	case TYPECODE::YKDIN:		// ��˫��ң�ر���
		DataInfo.DataType |= Fr::FrameType::eFrameYk;
		IsACK = TRUE;
		return ProcessYkDin(buf, len);
	case TYPECODE::YT:			// ��ң������
		DataInfo.DataType |= Fr::FrameType::eFrameYt;
		IsACK = TRUE;
		return ProcessYt(buf, len);
	case TYPECODE::CallAll:		// �����ٱ���
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
		return -1;  //����ʶ��ı���
	}
}

// ������ң�ر���
INT32 CMyLcn_S::ProcessYkSin(const UINT8* buf, const INT32 len)
{
	INT32 Action = buf[1];		// 0:�����Ƿ�(1->0); 1:�����Ƿ�(0->1)
	INT32 ObjectNo = 0;			// ����ң�ض����Ϊ0

	LCN_DoYk(pIF, Action, ObjectNo, Fr::YK_EXE);		// Fr::YK_EXE������ִ��

	return len;
}

// ����˫��ң�ر���
INT32 CMyLcn_S::ProcessYkDin(const UINT8* buf, const INT32 len)
{
	INT32 Action = buf[1];		// 1:�����Ƿ�(1->0); 2:�����Ƿ�(0->1)
	INT32 ObjectNo = 1;			// ����ң�ض����Ϊ1

	LCN_DoYk(pIF, Action, ObjectNo, Fr::YK_EXE, TRUE);

	return len;
}

// ����ң������
INT32 CMyLcn_S::ProcessYt(const UINT8* buf, const INT32 len)
{
	INT32 ObjectNo = 0;		// ����ң�������Ϊ0
	INT32 iValue = MAKEWORD(buf[1], buf[2]);

	LCN_DoYtInteger(pIF, Fr::YT_OUT, ObjectNo, iValue, Fr::YT_EXE);

	return len;
}

// �����ʱ����
INT32 CMyLcn_S::ProcessSetTime(const UINT8* buf, const INT32 len)
{
	if ( len < 10 )
	{// ��ʱ�������ݳ��Ȳ���10
		return -1;
	}

	if ( LCN_GetTimeCheck(pIF) != Fr::TimeCheck::RevTime )
	{// �ڵ���̬���ò�������ն�ʱ
		return len;
	}

	SYSTEMTIME st;
	// ʱ�����:2016��1��3��15ʱ20��10��1000����
	// ʱ�걨��:E0 07 01 03 0F 14 0A E8 03
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
