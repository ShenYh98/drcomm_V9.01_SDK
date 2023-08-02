#ifndef __LCNTIME_H_
#define __LCNTIME_H_

/**
@file ʱ�䴦��ṹ����
@version v1.01
@author 
@date 2019-08-14
*/

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <string.h>

#include "PubDef.h"

#ifdef _WINDOWS
#define _USE_32BIT_TIME_T
#pragma warning(disable : 4996)
#else
#include<sys/time.h>
#include<unistd.h>
#endif

#pragma pack(1)


struct LCNTIME
{
	static const INT32 F_DM4Y_HMS_M	=	0;  //dd/mm/yyyy hh:mm:ss::sm
	static const INT32 FC_4YMD_HMS	=	1;  //yyyy��mm��dd�� XX��XX��XX��
	static const INT32 F_DM2Y_HMS_M	=	2;  //dd/mm/yy hh:mm:ss::sm
	static const INT32 FC_2YMD_HMS	=	3;  //yy��mm��dd�� XX��XX��XX��
	static const INT32 F_HMS		=	4;	//"hh:mm:ss"
	static const INT32 FC_HMS		=	5;	//"hhʱmm��ss��"
	static const INT32 F_HM			=	6;	//"hh:mm"
	static const INT32 FC_HM		=	7;	//"hh:mm"
	static const INT32 F_HMS_AmPm	=	8;	//"hh:mm:ss am/pm"
	static const INT32 F_HM_AmPm	=	9;	//"hh:mm am/pm"
	static const INT32 F_4YMD		=	10;	//"yyyy-mm-dd"
	static const INT32 F_HMS_M		=	11;	//"hh:mm:ss::ms"
	static const INT32 FC_4YMD_HMS_M=	12;  //yyyy��mm��dd�� XX��XX��XX��XXX����
	static const INT32 F_DM4Y_HMS	=	13;  //dd/mm/yyyy hh:mm:ss
	static const INT32 F_4YMD_HMS	=	14;  //dd/mm/yyyy hh:mm:ss::sm

public:
	INT64 Tm;//�� 1970-01-01  ��ʼ�����뵥λ,Ŀǰ��ʱֻ֧�ֵ�UNIX��ʱ�䷶Χ
	
private:
	//�������Ӧ�ĸ���λ��ģ
	static const INT64 HudrNanSecPerSec = 10000000;//��
	static const INT64 HudrNanSecPerMilsec = 10000;//����
	static const INT64 HudrNanSecPerMicsec = 10;//΢��
public:
	LCNTIME()
	{
		Tm = 0;
	};

	LCNTIME(INT64 t)//������//���ݵĲ���������������10000000��һǧ��
	{
		Tm = t;
	};
	
	BOOL32 SetDayTime(INT32 nYear, INT32 nMonth, INT32 nDay, INT32 nHour, INT32 nMin, INT32 nSec, 
		INT32 MilSec = 0, INT32 MicSec = 0, INT32 NanSecOfHundred = 0, INT32 nDST = -1)
	{
		struct tm *tmPtr;
		time_t tmpTm;

		if(time(&tmpTm) < 0) return FALSE;
		if((tmPtr = localtime((const time_t*)&tmpTm)) == NULL) return FALSE;
		tmPtr->tm_year = nYear-1900;
		tmPtr->tm_mon = nMonth-1;
		tmPtr->tm_mday = nDay;
		tmPtr->tm_hour = nHour;
		tmPtr->tm_min = nMin;
		tmPtr->tm_sec = nSec;
		tmPtr->tm_isdst = nDST;
		if((tmpTm = mktime(tmPtr)) < 0) return FALSE;

		Tm = tmpTm * HudrNanSecPerSec + MilSec * HudrNanSecPerMilsec + MicSec * HudrNanSecPerMicsec + NanSecOfHundred;

		return TRUE;
	};

	LCNTIME(INT32 nYear, INT32 nMonth, INT32 nDay, 
	INT32 nHour, INT32 nMin, INT32 nSec, 
	INT32 MilSec = 0, INT32 MicSec = 0, INT32 NanSecOfHundred = 0, INT32 nDST = -1)
	{
		SetDayTime(nYear, nMonth, nDay, nHour, nMin, nSec, MilSec, MicSec, NanSecOfHundred, nDST);
	};

	//����windowsϵͳ��FILETIME����
	//BOOL32 SetTime(UINT32 dwHighDateTime1, UINT32 dwLowDateTime1)
	//{
	//	Tm =  dwHighDateTime1;
	//	Tm <<= 32;
	//	Tm |= dwLowDateTime1;
	//	return TRUE;
	//}

	BOOL32 SetTime(INT64 st)
	{
		Tm = st;
		return TRUE;
	};

	//BOOL32 SetTime(INT32 t)//Ϊ�˼��ݲ�ͬ����ϵͳ�������time_tʱ��
	//{
	//	Tm = static_cast<INT64>(t) * HudrNanSecPerSec;
	//	return TRUE;
	//};


public:

	///�õ���ǰ����ʱ��
	void GetCurrentLocalTime()
	{
		struct timeb tmptime;
		
		ftime( & tmptime);
		Tm=tmptime.time * HudrNanSecPerSec + tmptime.millitm * HudrNanSecPerMilsec;
	};

	///��ȫ��ʱ�̵õ�����ʱ��
	BOOL32 GetLocalTime(LCNTIME* kLocal)
	{
		struct tm *tmPtr = NULL;
		time_t tmpTm = static_cast<time_t>(Tm / HudrNanSecPerSec);
		
		if((tmPtr = localtime((const time_t*)&tmpTm)) == NULL) return FALSE;
		kLocal->Tm = mktime(tmPtr) * HudrNanSecPerSec + Tm% HudrNanSecPerSec;
		return TRUE;
	};

	///�ɱ���ʱ�̵õ�ȫ��ʱ��
	BOOL32 GetUniversalTime(LCNTIME* kUTC)
	{
		struct tm *tmPtr = NULL;
		time_t tmpTm = static_cast<time_t>(Tm / HudrNanSecPerSec);
		
		if((tmPtr = gmtime((const time_t*)&tmpTm)) == NULL) return FALSE;
		kUTC->Tm = mktime(tmPtr) * HudrNanSecPerSec + Tm% HudrNanSecPerSec;
		return TRUE;
	};

///��CTime��ͬ������
	/**
	 * @brief �õ����
	 * @retval ���ֵ
	 */
	INT32 GetYear() const
	{
		struct tm *tmPtr = NULL;
		time_t tmpTm = static_cast<time_t>(Tm / HudrNanSecPerSec);
		
		if((tmPtr = localtime((const time_t*)&tmpTm)) == NULL) return -1;
		return tmPtr->tm_year + 1900;		
	};

	/**
	 * @brief �õ��º�
	 * @retval �º�ֵ
	 */
	INT32 GetMonth() const
	{
		struct tm *tmPtr = NULL;
		time_t tmpTm = static_cast<time_t>(Tm / HudrNanSecPerSec);
		
		if((tmPtr = localtime((const time_t*)&tmpTm)) == NULL) return -1;
		return tmPtr->tm_mon + 1;		
	};

	/**
	 * @brief �õ��պ�
	 * @retval �պ�ֵ
	 */
	INT32 GetDay() const
	{
		struct tm *tmPtr = NULL;
		time_t tmpTm = static_cast<time_t>(Tm / HudrNanSecPerSec);
		
		if((tmPtr = localtime((const time_t*)&tmpTm)) == NULL) return -1;
		return tmPtr->tm_mday;		
	};

	/**
	 * @brief �õ�Сʱֵ
	 * @retval Сʱֵ
	 */
	INT32 GetHour() const
	{
		struct tm *tmPtr = NULL;
		time_t tmpTm = static_cast<time_t>(Tm / HudrNanSecPerSec);
		
		if((tmPtr = localtime((const time_t*)&tmpTm)) == NULL) return -1;
		return tmPtr->tm_hour;		
	};

	/**
	 * @brief �õ���ֵ
	 * @retval ��ֵ
	 */
	INT32 GetMinute() const
	{
		struct tm *tmPtr = NULL;
		time_t tmpTm = static_cast<time_t>(Tm / HudrNanSecPerSec);
		
		if((tmPtr = localtime((const time_t*)&tmpTm)) == NULL) return -1;
		return tmPtr->tm_min;		
	};

	/**
	 * @brief �õ���ֵ
	 * @retval ��ֵ
	 */
	INT32 GetSecond() const
	{
		struct tm *tmPtr = NULL;
		time_t tmpTm = static_cast<time_t>(Tm / HudrNanSecPerSec);
		
		if((tmPtr = localtime((const time_t*)&tmpTm)) == NULL) return -1;
		return tmPtr->tm_sec;		
	};
	
	/**
	 * @brief �õ�����ֵ
	 * @retval ����ֵ
	 */
	INT32 GetMilSecond() const
	{
		return static_cast<INT32>(((Tm+5000)%HudrNanSecPerSec)/HudrNanSecPerMilsec);//Ҫע����������
	};
	
	/**
	 * @brief �õ�΢��ֵ
	 * @retval ΢��ֵ
	 */
	INT32 GetMicSecond() const
	{
		return static_cast<INT32>((Tm%HudrNanSecPerMilsec)/HudrNanSecPerMicsec);
	};

	/**
	 * @brief �õ�������ֵ
	 * @retval ������ֵ
	 */
	INT32 GetNanSecOfHundred() const
	{
		return static_cast<INT32>(Tm%HudrNanSecPerMicsec);
	};


	/**
	 * @brief ��΢��Ϊ��λ����ʱ��
	 * @param micSecond ΢��ֵ������Ϊ��ֵ
	 */
	void AdjustMicSec(const INT32 micSecond){
		UINT32 dms;
		if (micSecond <0){
			dms = 0- micSecond;
			dms *= 10;
			Tm -= dms;
		}
		else{
			dms = micSecond;
			dms *= 10;
			Tm += dms;
		}
	}

	//��SYSTEMTIME��ʽʱ�����LCNTIME����ʱ��
	BOOL32 GetSystemTime(SYSTEMTIME *pst)
	{
		struct tm *tmPtr = NULL;
		time_t tmpTm = static_cast<time_t>(Tm / HudrNanSecPerSec);
		if((tmPtr = localtime((const time_t*)&tmpTm)) == NULL) return FALSE;
		pst->wYear = tmPtr->tm_year + 1900;
		pst->wMonth = tmPtr->tm_mon + 1;
		pst->wDayOfWeek = tmPtr->tm_wday;  //0-6
		pst->wDay = tmPtr->tm_mday;
		pst->wHour = tmPtr->tm_hour;
		pst->wMinute = tmPtr->tm_min;
		pst->wSecond = tmPtr->tm_sec;
		pst->wMilliseconds = GetMilSecond();
		return TRUE;
	}

	//��SYSTEMTIME��ʽ��ʱ������LCNTIME����ʱ��
	BOOL32 SetSystemTime(const SYSTEMTIME* pst)
	{
		struct tm *tmPtr = NULL;
		time_t tmpTm;

		if(time(&tmpTm) < 0)
			return FALSE;

		if((tmPtr = localtime((const time_t*)&tmpTm)) == NULL)
			return FALSE;

		tmPtr->tm_year = pst->wYear-1900;
		tmPtr->tm_mon = pst->wMonth-1;
		tmPtr->tm_mday = pst->wDay;
		tmPtr->tm_hour = pst->wHour;
		tmPtr->tm_min = pst->wMinute;
		tmPtr->tm_sec = pst->wSecond;
		if((Tm = static_cast<INT64>(mktime(tmPtr) * HudrNanSecPerSec)) < 0)
			return FALSE;
	
		AdjustMicSec(pst->wMilliseconds*1000);
		return TRUE;
	}

	///�õ������ʱ��,��λ�Ǻ���,������ֵ
	INT64 GetSpaceTime(const LCNTIME b)
	{
		return (Tm >= b.Tm?((Tm-b.Tm)/HudrNanSecPerMilsec):((b.Tm-Tm)/HudrNanSecPerMilsec));
	};
	
	void ToString(CHAR *string, const INT32 len, const INT32 DateFormat = F_DM4Y_HMS_M)
	{
		string[0] = 0;
		struct tm *tmPtr = NULL;
		CHAR tmpString[256];
		time_t tmpTm = static_cast<time_t>(Tm / HudrNanSecPerSec);
		
		INT32 Year,Month,Day;
		INT32 Hour,Minute,Second;
		INT32 MilSec;

		if((tmPtr = localtime(reinterpret_cast<const time_t*>(&tmpTm))) == NULL) 
			return;

		Year = tmPtr->tm_year+1900;
		Month = tmPtr->tm_mon+1;
		Day = tmPtr->tm_mday;
		Hour = tmPtr->tm_hour;
		Minute = tmPtr->tm_min;
		Second =  tmPtr->tm_sec;
//	#if 0
//		MilSec = static_cast<INT32>((Tm%HudrNanSecPerSec)/HudrNanSecPerMilsec);
//	#else
// 		MilSec = static_cast<INT32>(((Tm+5000)%HudrNanSecPerSec)/HudrNanSecPerMilsec);//Ҫע����������
		MilSec = GetMilSecond();
//	#endif
		
		memset(tmpString, '\0', sizeof(tmpString));
		switch(DateFormat)
		{
		case F_DM4Y_HMS:  //Ӣ��ʱ���ʾ��,4λ������
			sprintf(tmpString,"%02d/%02d/%04d %02d:%02d:%02d", Day, Month, Year, Hour, Minute, Second);
			break;

		case F_DM4Y_HMS_M:  //Ӣ��ʱ���ʾ��,4λ������
			sprintf(tmpString,"%02d/%02d/%04d %02d:%02d:%02d.%03d", Day, Month, Year, Hour, Minute, Second, MilSec);
			break;

		case FC_4YMD_HMS:  //����ϰ�߱�ʾ��,4λ������
			sprintf(tmpString,"%04d��%02d��%02d�� %02dʱ%02d��%02d��", Year, Month, Day, Hour, Minute, Second);
			break;

		case FC_4YMD_HMS_M:  //����ϰ�߱�ʾ��,4λ������
			sprintf(tmpString,"%04d��%02d��%02d�� %02dʱ%02d��%02d��%03d����", Year, Month, Day, Hour, Minute, Second, MilSec);
			break;

		case F_DM2Y_HMS_M:  //Ӣ��ʱ���ʾ��,2λ������
			sprintf(tmpString,"%02d/%02d/%04d %02d:%02d:%02d.%03d", Day, Month, Year, Hour, Minute, Second, MilSec);
			break;

		case FC_2YMD_HMS:  //����ϰ�߱�ʾ��,2λ������
			sprintf(tmpString,"%02d��%02d��%02d�� %02dʱ%02d��%02d��", Year, Month, Day, Hour, Minute, Second);
			break;

		case F_HMS://	"hh:mm:ss"
			sprintf(tmpString,"%02d:%02d:%02d", Hour, Minute, Second);
			break;
			
		case F_HMS_M://	"hh:mm:ss::ms"
			sprintf(tmpString,"%02d:%02d:%02d::%03d", Hour, Minute, Second, MilSec);
			break;
			
		case FC_HMS://	"hhʱmm��ss��"
			sprintf(tmpString,"%02dʱ%02d��%02d��", Hour, Minute, Second);
			break;
			
		case F_HM://	"hh:mm"
			sprintf(tmpString,"%02d:%02d", Hour , Minute);
			break;
			
		case FC_HM://	"hh:mm"
			sprintf(tmpString,"%02dʱ%02d��", Hour , Minute);
			break;
			
		case F_HMS_AmPm://	"hh:mm:ss am/pm"
			if(Hour <= 12)
				sprintf(tmpString,"%02d:%02d:%02d am", Hour , Minute, Second);
			else
				sprintf(tmpString,"%02d:%02d:%02d pm", Hour - 12, Minute, Second);
			break;
			
		case F_HM_AmPm://	"hh:mm am/pm"
			if(Hour <= 12)
				sprintf(tmpString,"%02d:%02d am", Hour , Minute);
			else
				sprintf(tmpString,"%02d:%02d pm", Hour - 12, Minute);
			break;

		case F_4YMD://	"yyyy-mm-dd"
			sprintf(tmpString,"%04d-%02d-%02d", Year, Month, Day);
			break;

		case F_4YMD_HMS://yyyy-mm-dd hh:mm:ss
			sprintf(tmpString,"%04d-%02d-%02d %02d:%02d:%02d", Year, Month, Day, Hour , Minute, Second);
			break;

		default:
			break;
		}
		
		if (len > (INT32)strlen(tmpString)){
			memcpy(string,tmpString,strlen(tmpString)+1);
		}
		else{
			memcpy(string,tmpString,len);
			string[len-1] = 0;
		}
	};

	void ToDebug(const CHAR *string=NULL, const INT32 DateFormat = F_DM4Y_HMS_M){
		printf("\n");
		char str[64];
		ToString(str, sizeof(str), DateFormat);
		printf("%s ",str);
		if (string != NULL)
			printf("%s",string);
	}

public:
	LCNTIME& operator=(const INT64& t)
	{
		SetTime(t);
		return *this;		
	};

	LCNTIME& operator=(const INT32& t)//Ϊ�˼��ݲ�ͬ����ϵͳ�������time_tʱ��
	{
		SetTime(t);
		return *this;		
	};

	LCNTIME& operator=(const LCNTIME& s)
	{
		SetTime(s.Tm);

		return *this;		
	};

	///������������,��������������
	INT32 operator-(const LCNTIME b)
	{
		INT32  T1, T2;
		INT32 deltT;
		
		T1 = static_cast<INT32>(Tm/HudrNanSecPerSec);
		T2 = static_cast<INT32>(b.Tm/HudrNanSecPerSec);

		if (T1 >= T2)
		{
			deltT = T1-T2;
			return deltT;
		}
		else
		{
			deltT = T2-T1;
			return 0-deltT;
		}
		
	};

	/// dtlen means seconds
	LCNTIME operator-(const INT32 dtlen)
	{
		LCNTIME temTime;
		INT64 deltT= dtlen * HudrNanSecPerSec;
		INT64 T1 = Tm;
		INT64 T2 = 0;
		
		if (deltT>=0)
		{
			T2 = deltT;
			if (T1 <= T2) return temTime;
			T2 = T1 - T2;
			temTime.Tm= T2;
			return temTime;
		}
		else
		{
			T2 = (0 - deltT);
			T2 += T1;
			if (T2 < T1) 
			{
				temTime.Tm = 0x80000000;
				return temTime;
			}
			temTime.Tm = T2;
			return temTime;
		}
	};

/// dtlen means seconds
	LCNTIME operator+(const INT32 dtlen)
	{
		LCNTIME temTime;
		INT64 deltT= dtlen * HudrNanSecPerSec;
		INT64 T1 = Tm;
		INT64 T2 = 0;
		
		if (deltT < 0)
		{
			T2 = 0 - deltT;
			if (T1 <= T2) return temTime;
			T2 = T1 - T2;
			temTime.Tm = T2;
			return temTime;
		}
		else
		{
			T2 = deltT;
			T2 += T1;
			if (T2 < T1) 
			{
				temTime.Tm = 0x80000000;
				return temTime;
			}
			temTime.Tm = T2;
			return temTime;
		}
	};

	LCNTIME operator+=(const INT32 dtlen)
	{
		INT64 deltT= dtlen * HudrNanSecPerSec;
		Tm += deltT;
		return Tm;
	};

	LCNTIME operator-=(const INT32 dtlen)
	{
		INT64 deltT= dtlen * HudrNanSecPerSec;
		Tm -= deltT;
		return Tm;
	};
	
	BOOL32 operator==(const LCNTIME b)
	{
		return (Tm == b.Tm ? TRUE:FALSE);
	};
	
	BOOL32 operator!=(const LCNTIME b)
	{
		return (Tm != b.Tm ? TRUE:FALSE);
	};
	
	BOOL32 operator>(const LCNTIME b)
	{
		return (Tm > b.Tm ? TRUE:FALSE);
	};
	
	BOOL32 operator>=(const LCNTIME b)
	{
		return (Tm >= b.Tm ? TRUE:FALSE);
	};
	
	BOOL32 operator<(const LCNTIME b)
	{
		return (Tm < b.Tm ? TRUE:FALSE);
	};
	
	BOOL32 operator<=(const LCNTIME b)
	{
		return (Tm <= b.Tm ? TRUE:FALSE);
	};
};

#pragma pack()

const LCNTIME LcnHisStart = LCNTIME(2010,1,1,0,0,0);  //ʹ��UINT32ʱ�����ʼʱ��

#endif

