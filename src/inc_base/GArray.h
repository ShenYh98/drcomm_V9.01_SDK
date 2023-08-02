#ifndef _G_ARRAY_
#define _G_ARRAY_

#include "BaseConst.h"

template<class DataType>
class GArray
{ 
static const INT32 NumAtMostUnit	= 1000000;

//	INT32	MaxNumUnit;  //自动调整的数据限制,第一次setSize的5倍
	INT32	size;
	DataType *pData;
	INT32	readPos;
	INT32	writePos;

public:
	GArray(){	memset(this, 0, sizeof(*this)); pData = NULL;};
	GArray(const INT32 size1){memset(this, 0, sizeof(*this)); pData = NULL; SetSize(size1);};
	~GArray(){ 
		if (pData != NULL)
			delete[] pData; 
		pData = NULL;
	};

	void Clear(){readPos = writePos;}

	BOOL32 SetSize(const INT32 size1);
	BOOL32 ReSize(INT32 size1);
	INT32  GetSize(){return size;};

	BOOL32 AppendOne(DataType& data1);

	INT32  GetCount(){
		INT32 num = writePos - readPos; 
		if (num<0) num+= size; return num; 
	};

	INT32  GetData(DataType * pData1, const INT32 numMaxData1, BOOL32 isClear=TRUE);  //读取数据，isClear是否清除读出的数据
	INT32  ClearData(const INT32 numMaxData1);  //清除数据
	BOOL32 GetLastOneData(DataType * pData1);

};

template<class DataType>
BOOL32 GArray<DataType>::ReSize(INT32 size1)
{
	if (size1 < 10)
		size1 = 10;
	if (size1 > NumAtMostUnit)
		size1 = NumAtMostUnit;

	if (size1 <= size)
		return TRUE;

	DataType * pNewData = new DataType[size1];
	if (pNewData == NULL)
		return FALSE;
	
	INT32 numData = GetData(pNewData, size1);
	
	readPos = 0;
	writePos = numData;

	size = size1;
	if (pData != NULL)
		delete[] pData;
	
	pData = pNewData;
	return TRUE;
}

template<class DataType>
BOOL32 GArray<DataType>::SetSize(const INT32 size1)
{
	size = size1;
	if (size1 < 10)
		size = 10;
	if (size1 > NumAtMostUnit)
		size = NumAtMostUnit;

//	MaxNumUnit = size*5;
//	if (MaxNumUnit > NumAtMostUnit)
//		MaxNumUnit = NumAtMostUnit;
	if (pData != NULL)
		delete[] pData;
	if (size == 0){
		pData = NULL;
		return TRUE;
	}
	pData = new DataType[size];
	if (pData == NULL)
		return FALSE;
	
	readPos = writePos = 0;

	return TRUE;
}

template<class DataType>
BOOL32 GArray<DataType>::AppendOne(DataType& data1){
	if (pData == NULL)
		return FALSE;
	INT32 newPos = writePos+1;
	if (newPos >= size)
		newPos -= size;
	if (newPos == readPos){
//		printf("\nAppendOne<GArray> fault!");
		return FALSE;		
		/*//需考虑自动调整空间
		if (size >= MaxNumUnit)  //没有空间可增长，添加失败
			return FALSE;

		DataType *pNewData;
		INT32 newSize = size * 2;			//每次翻倍增长
		if (newSize > MaxNumUnit)
			newSize = MaxNumUnit;
		pNewData = new DataType[newSize];
		if (pNewData == NULL)
			return FALSE;

		writePos = GetData(pNewData, newSize);
		readPos = 0;
		delete[] pData;
		pData = pNewData;
		size = newSize;
		return AppendOne(data1);
		*/
	}

	memcpy(&pData[writePos], &data1, sizeof(DataType));
	writePos = newPos;
	return TRUE;
}

template<class DataType>
INT32 GArray<DataType>::GetData(DataType * pData1, const INT32 numMaxData1, BOOL32 isClear)
{
	//INT32 num,num1,num2;
	INT32 num = 0;
	INT32 num1 = 0;
	INT32 num2 = 0;
	if ((pData == NULL)||(pData1 == NULL))
		return 0;
	if (numMaxData1 ==0)
		return 0;

	INT32 wp1 = writePos;

	if (readPos == wp1)
		return 0;

	if (readPos < wp1){
		num = wp1 - readPos;
		if (num > numMaxData1)
			num = numMaxData1;
		memcpy(pData1, &pData[readPos], num * sizeof(DataType));
		if (isClear)
			readPos += num;
		return num;
	}

	//需要作循环处理
	num1 = size - readPos;
	if (num1 > numMaxData1){
		num1 = numMaxData1;
		memcpy(pData1, &pData[readPos], num1 * sizeof(DataType));
		if (isClear)
			readPos += num1;
		return num1;
	}
	else if (num1 == numMaxData1){//正好读到末尾
		memcpy(pData1, &pData[readPos], num1 * sizeof(DataType));
		if (isClear)
			readPos = 0;
		return num1;
	}

	//循环处理
	memcpy(pData1, &pData[readPos], num1 * sizeof(DataType));
	if (wp1 ==0){
		if (isClear)
			readPos = 0;
		return num1;
	}
	num2 = wp1;
	if ((num1 + num2) > numMaxData1)
		num2 = numMaxData1 - num1;

	memcpy(&pData1[num1], pData, num2 * sizeof(DataType));
	num = num1 + num2;
	if (isClear)
		readPos = num2;

	return num;
}

template<class DataType>
INT32 GArray<DataType>::ClearData(const INT32 numMaxData1)
{
	INT32 num,num1,num2;
	if (pData == NULL)
		return 0;
	if (numMaxData1 ==0)
		return 0;

	INT32 wp1 = writePos;

	if (readPos == wp1)
		return 0;

	if (readPos < wp1){
		num = wp1 - readPos;
		if (num > numMaxData1)
			num = numMaxData1;
		readPos += num;
		return num;
	}

	//需要作循环处理
	num1 = size - readPos;
	if (num1 > numMaxData1){
		num1 = numMaxData1;
		readPos += num1;
		return num1;
	}
	else if (num1 == numMaxData1){//正好读到末尾
		readPos = 0;
		return num1;
	}

	//循环处理
	if (wp1 ==0){
		readPos = 0;
		return num1;
	}
	num2 = wp1;
	if ((num1 + num2) > numMaxData1)
		num2 = numMaxData1 - num1;

	num = num1 + num2;
	readPos = num2;

	return num;
}

template<class DataType>
BOOL32 GArray<DataType>::GetLastOneData(DataType * pData1)
{
	if ((pData == NULL)||(pData1 == NULL))
		return FALSE;

	if (readPos == writePos)
		return FALSE;

	INT32 rp = readPos;
	for(INT32 i=0;i<size;i++){
		*pData1 = pData[rp];
		rp ++;
		if (rp >= size)
			rp = 0;
		if (rp == writePos)
			return TRUE;
	}
	return FALSE;
}

#endif
