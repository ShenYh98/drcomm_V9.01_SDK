#include "c_myLcn.h"

INT32 CMyLcn_C::AssembleSendData(UINT8 *buf, const INT32 bufferSize)
{
	if ( NULL == buf )
	{// 形参检查
		return -1;
	}

	INT32 size = 0;
	INT32 step = 0;

	switch( SendTaskNo )
	{
	case 0 :
		step = AssembleAssignIDTask(buf, bufferSize, size);
		break;
	default:
		break;
	}

	return step;
}

INT32 CMyLcn_C::AssembleAssignIDTask(UINT8 *buf, const INT32 bufferSize, INT32& size) {
	// 删除所有id->查询所有设备id及sn号->根据sn号下设id->查询所有id
	switch( SendIDTaskNo )
	{
	case 0 :
		DataInfo.DataType |= Fr::FrameType::eFrameYk;
		size = AssembleDestroyID(buf, bufferSize);
		break;
	case 1 :
		DataInfo.DataType |= Fr::FrameType::eFrameYc;
		size = AssembleQueryID(buf, bufferSize);
		break;
	case 2 : 
		DataInfo.DataType |= Fr::FrameType::eFrameYk;
		size = AssembleDownloadID(buf, bufferSize);
		break;
	case 3 :
		DataInfo.DataType |= Fr::FrameType::eFrameYc;
		size = AssembleQueryID(buf, bufferSize);
		break;
	default:
		break;
	}

	if ( 2 == SendIDTaskNo && IDtotal < v_devFeature.size() ) { // 下设id，如果下设次数小于所获sn数，则再下设第二条
		SendIDTaskNo = 2;
	} else if ( 3 == SendIDTaskNo && false == IsRecv ) { // 广播查询id未回复，则无须分配id
		SendIDTaskNo = 3;
	} else if ( 3 == SendIDTaskNo && true == IsRecv ) { // 广播查询id回复，则重新分配id
		SendIDTaskNo = 0;
	} else {
		SendIDTaskNo++;
	}

	return SendIDTaskNo;
}

INT32 CMyLcn_C::AssembleDestroyID(UINT8 *buf, const INT32 bufferSize) {
	INT32 i = 0;
	UINT16 ChkCRC16 = 0x0000;

	// 删除所有逆变器id报文：00 39 0b 07 00 64 crc(L) crc(H)
	buf[i++] = 0x00;				// 从站地址
	buf[i++] = 0x39;				// 功能码
	buf[i++] = 0x0B;				// 起始地址高字节
	buf[i++] = 0x07;				// 起始地址低字节
	buf[i++] = 0x00;				// 线圈数量高字节
	buf[i++] = 0x64;				// 线圈数量低字节

	ChkCRC16 = CRC16(buf, i);

	buf[i++] = LOBYTE(ChkCRC16);		// crc校验低字节
	buf[i++] = HIBYTE(ChkCRC16);		// crc校验高字节

	return i;
}

// 有返回报文说明没有分配完全，没有返回报文说明已完成分配
INT32 CMyLcn_C::AssembleQueryID(UINT8 *buf, const INT32 bufferSize) {
	INT32 i = 0;
	UINT16 ChkCRC16 = 0x0000;

	// 查询所有逆变器id报文：00 35 0b 07 00 0b crc(L) crc(H)
	buf[i++] = 0x00;
	buf[i++] = 0x35;
	buf[i++] = 0x0B;
	buf[i++] = 0x07;
	buf[i++] = 0x00;
	buf[i++] = 0x0B;

	ChkCRC16 = CRC16(buf, i);

	buf[i++] = LOBYTE(ChkCRC16);
	buf[i++] = HIBYTE(ChkCRC16);

	return i;
}

INT32 CMyLcn_C::AssembleDownloadID(UINT8 *buf, const INT32 bufferSize) {
	DevFeature dev;
	INT32 i = 0;
	UINT16 ChkCRC16 = 0x0000;

	
	buf[i++] = 0x00;
	buf[i++] = 0x38;
	buf[i++] = 0x0B;
	buf[i++] = 0x07;
	for (int j = 0; j < 20; j++) {
		buf[i++] = v_devFeature[IDtotal].sn[j];
	}
	buf[i++] = 0x00;
	IDtotal++;
	buf[i++] = IDtotal;
	
	return i;
}