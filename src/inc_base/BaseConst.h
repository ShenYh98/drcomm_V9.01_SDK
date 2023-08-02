#ifndef	_BASECONST_H
#define	_BASECONST_H

/**
@file ������������
@version v1.01
@author 
@date
*/
#include <stdlib.h>
#include "typedefs.h"

/**
  ������������
*/
namespace BDT
{
	/**
	  Ӧ���Զ����ݣ���ͬvoid
	*/
	const INT32 Void			= -1;

	const INT32 AppObject	= 0;


	/**
	  ��SYBAS���ͼ���
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
	* ע�⣺61850��֧��
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


	//Ӧ�õ���������
	const INT32 aBitString		= (100<<16) + AppObject;  //61850�е�BitString

	const INT32 aBvString		= (101<<16) + AppObject;  //MMS�е�BvString

	const INT32 aTime64			= (102<<16) + INT_64U;	//KERTIMEʱ��,1970.1.1Ϊ��ʼ�İ�������

	const INT32 aTime32			= (103<<16) + INT_64U;	//time_tʱ��,1970.1.1Ϊ��ʼ������
	
	const INT32 aTime24			= (104<<16) + INT_24U;	//61850��24λʱ��

	const INT32 aRGB			= (105<<16) + INT_32;	//RGB��ɫ

	const INT32 aIPAddress		= (106<<16) + INT_32;	//IP��ַ

	const INT32 aIndexRecord	= (107<<16) + INT_32;	//��¼����

	const INT32 aIndexConst		= (108<<16) + INT_32;	//��������

	const INT32 aFilePath		= (109<<16) + VisibleString;	//�ļ�·����

	const INT32 aPasswordString	= (110<<16) + VisibleString;	//����

	const INT32 aPrinterName	= (111<<16) + VisibleString;	//��ӡ����

	const INT32 aComport		= (112<<16) + VisibleString;	//ͨѶ��  com1
}

/**
  ������ʾ����
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
	 * ���ֽ���ǰ
	 */
	const INT8 OrderLitEndian = 0;
	
	/**
	 * ���ֽ���ǰ
	 */
	const INT8 OrderBigEndian = 1;

	const INT32 IntOneValue = 1;

	const INT8 MY_ORDER = 1 - ((*(char *)(&IntOneValue)) & ((char)1)) ;

	/**
	 * û��ָ������˳�� (����ת��)
	 */
	const INT8 OrderNoEndian = (INT8)-1;
}

#endif
