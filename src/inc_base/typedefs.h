#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_
#include <stdlib.h>
#include "typedef.h"

#ifdef _WINDOWS
//#include <vld.h>  //用于检查内存泄漏,需要安装Visual Leak Detector，
//Visual Leak Detector的原始安装文件：src\vld\vld-2.2.3-setup 1.0.exe文件

#endif

#ifdef _WINDOWS
const char SeparateChar = '\\';
const char SeparateStr[2] = "\\";
#else
const char SeparateChar = '/';
const char SeparateStr[2] = "/";
#endif

#ifndef _WINDOWS
#include<semaphore.h>
typedef long long	INT64;
typedef unsigned long long UINT64;
typedef char * LPSTR;
#else
typedef __int64 INT64;
typedef unsigned __int64 UINT64;
#endif

typedef char	BOOL8;
typedef int		BOOL32;
typedef char	CHAR;
typedef signed char INT8;
typedef short int INT16;
typedef int INT32;

typedef INT32 OBJPOS;

typedef INT32 TPOS;

typedef unsigned char UCHAR;
typedef unsigned char UINT8;
typedef unsigned short int UINT16;
typedef unsigned int UINT32;

typedef float FLOAT32;
typedef double FLOAT64;

#endif /* _TYPEDEFS_H_ */
