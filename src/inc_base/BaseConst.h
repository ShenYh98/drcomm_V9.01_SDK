#ifndef	_BASECONST_H
#define	_BASECONST_H

/**
@file 基本常量定义
@version v1.01
@author 
@date
*/
#include <stdlib.h>
#include "typedefs.h"

/**
  基本数据类型
*/
namespace BDT
{
	/**
	  应用自定数据，等同void
	*/
	const INT32 Void			= -1;

	const INT32 AppObject	= 0;


	/**
	  与SYBAS类型兼容
	*/
	const INT32 VisibleString	= 2;

	const INT32 INT_8			= 3;

	const INT32 INT_16			= 4;

	const INT32 INT_32			= 5;

	const INT32 FLOAT_32		= 6;

	const INT32 FLOAT_64		= 7;

	const INT32 BOOL_32			= 8;

	const INT32 TIME_32	= 9;

	const INT32 KEYID	= 10;


	const INT32 INT_24			= 15;
	/**
	* 注意：61850不支持
	*/
	const INT32 INT_64			= 16;

	const INT32 INT_128			= 17;

	const INT32 INT_8U			= 18;

	const INT32 INT_16U			= 19;

	const INT32 INT_24U			= 20;

	const INT32 INT_32U			= 21;

	const INT32 INT_64U			= 22;

	const INT32 UTF8_String		= 23;

	const INT32 UTF16_String	= 24;


	//应用的数据类型
	const INT32 aBitString		= (100<<16) + AppObject;  //61850中的BitString

	const INT32 aBvString		= (101<<16) + AppObject;  //MMS中的BvString

	const INT32 aTime64			= (102<<16) + INT_64U;	//KERTIME时间,1970.1.1为开始的百纳秒数

	const INT32 aTime32			= (103<<16) + INT_64U;	//time_t时间,1970.1.1为开始的秒数
	
	const INT32 aTime24			= (104<<16) + INT_24U;	//61850的24位时间

	const INT32 aRGB			= (105<<16) + INT_32;	//RGB颜色

	const INT32 aIPAddress		= (106<<16) + INT_32;	//IP地址

	const INT32 aIndexRecord	= (107<<16) + INT_32;	//记录索引

	const INT32 aIndexConst		= (108<<16) + INT_32;	//常量索引

	const INT32 aFilePath		= (109<<16) + VisibleString;	//文件路径名

	const INT32 aPasswordString	= (110<<16) + VisibleString;	//口令

	const INT32 aPrinterName	= (111<<16) + VisibleString;	//打印机名

	const INT32 aComport		= (112<<16) + VisibleString;	//通讯口  com1
}

/**
  数据显示类型
*/
namespace VIEWTYPE
{
	const INT32 CHAR				=	1;
	const INT32 UCHAR				=	2;
	const INT32 SHORT				=	3;
	const INT32 INT				=	4;
	const INT32 LONG				=	5;
	const INT32 FLOAT				=	6;
	const INT32 DOUBLE			=	7;
	const INT32 SINGLEMENU		=	8;
	const INT32 MUTIMENU			=	9;
	const INT32 STRING			=	10;
	const INT32 DATE				=	11;
	const INT32 TIME				=	12;
	const INT32 DATETIME			=	13;
	const INT32 FORMULASTRING	=	14;
	const INT32 KEYID				=	15;
	const INT32 FIELD_NAME_STRING		=	16;
	const INT32 BINARY			=	17;
	const INT32 IP_ADDRESS		=	18;
	const INT32 ALIAS				=	19;
}

namespace BORDER
{
	/**
	 * 低字节在前
	 */
	const INT8 OrderLitEndian = 0;
	
	/**
	 * 高字节在前
	 */
	const INT8 OrderBigEndian = 1;

	const INT32 IntOneValue = 1;

	const INT8 MY_ORDER = 1 - ((*(char *)(&IntOneValue)) & ((char)1)) ;

	/**
	 * 没有指定编码顺序 (不做转换)
	 */
	const INT8 OrderNoEndian = (INT8)-1;
}

#endif
