#ifndef __SYS_PROC_H_
#define __SYS_PROC_H_

/**
@file 系统公共函数处理
@version v1.01
@author 
@date 
*/
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <string.h>
#include "PubDef.h"

#ifdef _WINDOWS
#else
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

class SYSPROC{
public:

	/**
	 * @brief 得到当前程序启动路径,最后不带'\',path[0] == 0表示取路路径失败
	 * @param path1 返回路径名
	 * @param len1   标明path的长度
	 */
	static void GetCurrRunPath(CHAR * path1, const INT32 len1) {
		#if defined(_WINDOWS)
				GetCurrentDirectoryA(len1, path1);
		#else
				getcwd(path1, len1);
		#endif
	}

	/**
	 * @brief 得到当前程序启动路径,最后不带'\',path[0] == 0表示取路路径失败
	 * @param path1 返回路径名
	 * @param len1   标明path的长度
	 */
	static void GetSysPath(CHAR * path1, const INT32 len1) {
		GetCurrRunPath(path1, len1);
		INT32 i=strlen(path1);

		for(i=strlen(path1); i>0;i--){
			if (path1[i] == SeparateChar){
				path1[i] = 0;
				return;
			}
		}
	}

	/**
	 * @brief 得到当前工程名
	 * @param pName1 返回的工程名
	 * @param len1   标明path的长度
	 */
	static void GetProjectName(CHAR * pName1, const INT32 len1) {
		CHAR strTmp[256];
		GetCurrRunPath(strTmp, 256);
		CHAR *pPos = strstr(strTmp, Fr::PathExe);
		if (NULL == pPos) {
			printf("Get project name fault!\n");
			return;
		}
		--pPos;
		*pPos = '\0';
		pPos = strrchr(strTmp, SeparateChar);

		++pPos;
		pName1[0] = 0;
		StrSafeCat(len1, pName1, pPos);
	}
	/**
	 * @brief 得到系统指定目录绝对路径 
	 * @param pSysRelativePath 系统目录相对路径,见类中常量定义
	 * @param pSysAbsolutePath   系统目录绝对路径,末尾不含"/"
	 * @param absolutePathLen   系统目录绝对路径长度
	 * @param retval   正确返回0 错误返回<0
	 */
	static INT32 GetSysAbsPath(const CHAR * pSysRelativePath, CHAR * pSysAbsolutePath,
		const INT32 absolutePathLen) {
		if (!pSysRelativePath || !pSysAbsolutePath || absolutePathLen <=0)
		{
			return -1;
		}

		pSysAbsolutePath[0] = 0;

		CHAR strTmp[512];
		#if defined(_WINDOWS)
			GetModuleFileNameA(0, strTmp, sizeof(strTmp));
		#else
			GetCurrRunPath(strTmp, sizeof(strTmp));
		#endif
			CHAR *pPos = strstr(strTmp, Fr::PathExe);

		if(NULL == pPos)
		{
			printf("Path not include ");
			printf("%s\n", Fr::PathExe);
			return -2;
		}

		if (pPos-1 < strTmp)
		{
			return -3;
		} 

		*(pPos-1) = '\0';

		if (absolutePathLen < (INT32)((INT32)strlen(strTmp) +(INT32)strlen(pSysRelativePath)+ 2))
		{
			return -4;
		}
		
		pSysAbsolutePath[0] = 0;
		StrSafeCat(absolutePathLen, pSysAbsolutePath, strTmp);
		StrSafeCat(absolutePathLen, pSysAbsolutePath, SeparateStr);
		StrSafeCat(absolutePathLen, pSysAbsolutePath, pSysRelativePath);
		return 0;
	}

	///16进制的字符串转整数
	static UINT8 GetIntFromChar(INT8 ch)
	{
		if ((ch >='a')&&(ch <= 'f')) return ((ch-'a')+10);
		else if ((ch >='A')&&(ch <= 'F')) return ((ch-'A')+10);
		else if ((ch >='0')&&(ch <= '9')) return (ch-'0');
		else return 0;
	}
	///16进制的字符串转整数
	static INT8 GetIntFromChar(INT8 ch0, INT8 ch1)
	{
		UINT8 i0 = GetIntFromChar(ch0);
		UINT8 i1 = GetIntFromChar(ch1);
		return (i1 + i0*16);
	}

	//字符串安全连接
	static void StrSafeCat(INT32 iDstSize, CHAR * szDst, const CHAR * szSrc)
	{
		if (szSrc == NULL) return;
		if (szDst == NULL) return;
		if (iDstSize <=0) return;
		INT32 ld = (INT32)strlen(szDst);
		INT32 ls = (INT32)strlen(szSrc);
		if (ld >= iDstSize){
			szDst[iDstSize-1] = 0;
			return;
		}
		if ((ld + ls)<iDstSize){
			memcpy(&szDst[ld], &szSrc[0], ls);
			szDst[ld+ls] = 0;
			return;
		}
		//szDst空间不足
		memcpy(&szDst[ld], &szSrc[0], iDstSize-ld);
		szDst[iDstSize-1] = 0;
	}

	static char* StrUpper(char *str)   
	{   
		if(str == NULL)
			return NULL;
		char *p = str;   
		while(*str){   
			*str = toupper(*str);   
			str++;   
		}   
		return p;   
	} 

	static CHAR * IecStrStr(char * ps, char *pd)
	{
		if (pd == NULL) return NULL;
		if (ps == NULL) return NULL;

		INT32 l = (INT32)strlen(pd);
		if (l>256) return NULL;
		char *p = strstr(ps, pd);
		if (p==NULL) return NULL;

		if (p[l] == 0) return p;

		if ((p[l] >= 'a')&&(p[l] <= 'z')) return NULL;
		if ((p[l] >= 'A')&&(p[l] <= 'Z')) return NULL;
		if ((p[l] >= '0')&&(p[l] <= '9')) return NULL;

		return p;
	}

	static UINT16 MakeWord(UINT8 loByte, UINT8 hiByte)
	{
		UINT16 u16;
		u16 = hiByte;
		u16 *= 256;
		u16 += loByte;
		return u16;
	}

	static BOOL32 IecMemcmp(char * ps, char *pd, INT32 len)
	{
		if (pd == NULL) return FALSE;
		if (ps == NULL) return FALSE;

		if (strlen(ps) != strlen(pd)) return FALSE;

		if (memcmp(ps, pd, len) !=0) return FALSE;

		if (ps[len] == 0) return TRUE;

		if ((ps[len] >= 'a')&&(ps[len] <= 'z')) return FALSE;
		if ((ps[len] >= 'A')&&(ps[len] <= 'Z')) return FALSE;
		if ((ps[len] >= '0')&&(ps[len] <= '9')) return FALSE;

		return TRUE;
	}

	static UINT32 GetPrime(int maxValue){  //得到哈希因子，是质数
		static UINT32 prime[25]={5,13,19,29,47,113,241,431,613,719,823,977,1153,1669,
					2161,3221,4297,5237,6491,8243, 11243, 16477, 23041, 32749, 49999};
		UINT32 v,i;
		if (maxValue<=0) v = 1000;
		else v = maxValue;

		for (i=0;i<24;i++)
			if (v<prime[i]) return prime[i];
		return prime[24];
	}

	//给出源文件指针和备份的文件名，进行文件备份,备份后，源文件指针被移至最后
	//返回值>=0,表示备份成功
	static INT32 FileCopy(FILE * &fSrc, char * dstFilePath1){
		if (fSrc == NULL)
			return -1;
		FILE *f = fopen(dstFilePath1, "wb" );
		if (f == NULL){
			fseek(fSrc, 0, SEEK_END); 
			return -1;
		}
		fseek(fSrc, 0, SEEK_SET);
		unsigned char buf[2000];
		for(;;){
			int len = fread(buf, 1, 2000, fSrc);
			if (len<0){
				fclose(f);
				fseek(fSrc, 0, SEEK_END); 
				return -1;
			}
			if (len==0)
				break;
			fwrite(buf, 1, len, f);
			if (len <2000)
				break;
		}
		fclose(f);
		fseek(fSrc, 0, SEEK_END); 
		return 0;
	}

	static INT32 SplitString(CHAR *srcStr, CHAR **ss)
	{
		INT32 num;
		if (srcStr[0] == 0)
			return 0;
		INT32 len = strlen(srcStr);
		num = 1;
		ss[0] = srcStr;

		for(INT32 i=1;i<len;i++){
			if (srcStr[i] == ','){
				srcStr[i] = 0;
				ss[num] = &srcStr[i+1];
				num ++;
				if (num >=128)
					return 0;
			}
		}

		for(INT32 i=0;i<num;i++){
			INT32 j;
			CHAR *ps = ss[i];
			len = strlen(ps);
			for(j=len-1;j>=0;j--){//删除结尾的无效字符
				if ((ps[j]!=' ')&&(ps[j]!='\t')&&(ps[j]!='\r')&&(ps[j]!='\n'))
					break;
				ps[j] = 0;
			}

			len = strlen(ps);
			for(j=0;j<len;j++){
				if ((ps[j]!=' ')&&(ps[j]!='\t')&&(ps[j]!='\r')&&(ps[j]!='\n'))
					break;
			}
			if (j <len)
				ss[i] = &ps[j];
		}
		return num;
	}

};

#endif

