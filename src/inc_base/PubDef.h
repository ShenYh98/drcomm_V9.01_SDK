#ifndef _PUB_DEF_H_
#define _PUB_DEF_H_

#include "stdio.h"
#include "stdlib.h"
#include "BaseConst.h"

/**
@file �����������ṹ����
@version v1.01
@author 
@date
*/

namespace Fr{
	const FLOAT32	SystemVersion	= 9.01f;	//ϵͳ�汾��,���ӿڲ��䣬һ��ֻ�ı�С�����ı��
	const INT32		NAME_LENGTH		= 64;		//���Ƴ���

	const CHAR	CONFIG_FILE[NAME_LENGTH]			= "cpm.nc";				//ǰ��ϵͳ�����������ļ���
	const CHAR	CONFIG_FILE_SN[NAME_LENGTH]			= "cpm_sn.txt";			//ǰ��ϵͳ�����к��ļ���
	const CHAR	CONFIG_FILE_SETTINGS[NAME_LENGTH]	= "cfg_settings.ini";	//ǰ��ϵͳ����̬�����ļ�

	const CHAR	Project[]				= "drcomm";		//��Ŀ
	const CHAR	PathLinux[]				= "/mnt/user/drcomm";	//linux·��
	const CHAR	PathExe[]				= "bin";		//ִ���ļ�·��
	const CHAR	PathConfig[]			= "config";		//�����ļ�·��
	const CHAR	PathPlug[]				= "plug";		//��Լ���·��
	const CHAR	PathProtocolUpdate[]	= "update";		//������·��
	const CHAR	PathHistory[]			= "his";		//��ʷ�����ļ�·��
	const CHAR	PathLocal[]				= "translate";	//���淭���ļ�·��

	//��ԼͨѶģʽ
	//�ͻ��˹�Լ��Ϣ���ͣ����ݣ��������󣬽��գ����������С
	//����˹�Լ��Ϣ���ͣ����������С�����գ����ݣ���������
	//����˹�Լ����ң������Ĳ��·����ͻ��˽��տ��Ʒ�У���Ĳ��ϴ�
	namespace Protocol{
		const INT32 PClient			=0;	//�ͻ��˹�Լ����Ҫ��ң�š�ң�����ݣ�����
		const INT32 APP				=1; //Ӧ�ýڵ��Լ����PClient����
		const INT32 PServer			=2; //����˹�Լ����Ҫ��ң�š�ң������
	};

	//��ʱ��ʽ
	namespace TimeCheck{
		const INT32 None			=0;	//����ʱ
		const INT32 SendTime		=1; //���Ͷ�ʱ
		const INT32 RevTime			=2; //���ն�ʱ
	};

	//�������
	namespace DataSort{
		const INT32 Yx	=1;	
		const INT32 Yc	=2;	
		const INT32 Ym	=3;	
		const INT32 Yk	=4;	
		const INT32 Yt	=5;	
	};

	namespace DataSourceType{
		const INT8 AllObject		= 0;	//��������
		const INT8 RealValue		= 1;	//ȡ������ʵ��ֵ
		const INT8 ChannelCode		= 2;	//ȡͨ����ֵ
		const INT8 FlagQ			= 3;	//ȡƷ��
		const INT8 RefreshTime		= 4;	//ȡˢ��ʱ��
		const INT8 DiffRefreshTime	= 5;	//ȡ��ǰʱ���������
	}

	namespace CFG{
		const INT32 NONE		= 0;//��Լû����̬��Ϣ
		const INT32 UserDef		= 99;  //�û��Զ���
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
		const INT32 Common		= 100;//ͨ�õ���̬����
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
		static const INT32 eFrameYx				=    0x01; //ң������֡
		static const INT32 eFrameYc				=    0x02; //ң������֡
		static const INT32 eFrameYm				=    0x04; //�������֡
		static const INT32 eFrameYk				=    0x08; //ң������֡
		static const INT32 eFrameYt				=    0x10; //ң������֡
		static const INT32 eFrameSoe			=    0x20; //SOE����֡
		static const INT32 eFrameTime			=    0x40; //��ʱ����֡
		static const INT32 eFrameRelay			=    0x80; //��������֡
		static const INT32 eFrameCurve			=   0x100; //��������֡�����ƻ�ֵ��Ԥ������
		static const INT32 eFrameReset			=   0x200; //��·��λ֡
		static const INT32 eFrameTest			=   0x400; //��·����֡
		static const INT32 eFrameQuery			=   0x800; //��·��ѯ֡
		static const INT32 eFrameReply			=  0x1000; //��·Ӧ��֡
		static const INT32 eFrameCallAll		=  0x2000; //��·����֡
		static const INT32 eFrameCallAllReply	=  0x4000; //����Ӧ��֡
		static const INT32 eFrameOther			=  0x8000; //��������֡
	};

	//����״̬Ʒ�ʵĶ�Ӧ��־λ,��IEC61850��׼һ��
	namespace QBit{
		const INT32 IecInvalidity		=     0x01;	//���仯��ֵ��Ч
		const INT32 IecQuestionable		=     0x02;	//������
		const INT32 IecOverFlow			=     0x04;	//���
		const INT32 IecOutOfRange		=     0x08;	//��������
		const INT32 IecBadReference		=     0x10;	//��������
		const INT32 IecOscillatory		=     0x20;	//���̶�
		const INT32 IecFailure			=     0x40;	//����
		const INT32 IecOldData			=     0x80;	//��ֵ
		const INT32 IecInconsistent		=    0x100;	//��ì��
		const INT32 IecInaccurate		=    0x200;	//����ȷ
		const INT32 IecSubstituted		=    0x400;	//�˹�����,������
		const INT32 IecTest				=    0x800;	//����
		const INT32 IecOperatorBlocked	=   0x1000;	//����������
	};
	
	namespace CommModeForDouble{
		const INT32 MainWork		=0;	//����(ͨ��)����
		const INT32 LinkRedundance	=1; //��·���࣬������(ͨ��)������·���Ӳ����ջ�������
		const INT32 DataRedundance	=2; //�������࣬������(ͨ��)����ͬʱ���ջ�������
	};

	const INT32 YkSetType_Default			=0;		//ң�����ư�ϵͳ�涨
	const INT32 YkSetType_Disable			=1;		//��ֹң��

	//Yk State
	const INT32 YK_IDLE					=0;		//����
	const INT32 YK_SELECT				=1;		//ѡ�� ,������YKYT_SELECT����
	const INT32 YK_ACK					=2;		//��У��ȷ
	const INT32 YK_NAK					=3;		//��У����
	const INT32 YK_EXE					=4;		//����Ϊִ�У�����Ϊִ��ȷ��
	const INT32 YK_RMV					=5;		//����Ϊȡ��������Ϊ��ʱȡ��

	const INT32 YKYT_SELECT				=YK_SELECT;		//���Ʋ���ѡ��
	//Yt State
	//const INT32 YT_IDLE					=100;	//����,��YK_IDLE����
	const INT32 YT_EXE					=101;	//����Ϊִ�У�����Ϊִ��ȷ��
	const INT32 YT_RMV					=102;	//����Ϊȡ��������Ϊ��ʱȡ��

	//Yk Action(command��
	const INT32 YK_ON					=11;
	const INT32 YK_OFF 					=12;
	const INT32 YK_TQH					=13;	//ͬ�ں�
	const INT32 YK_JWYH					=14;	//����ѹ��
	const INT32 YK_BJTQH				=15;	//���춨ͬ�ں�
	const INT32 YK_HHH					=16;	//�ϻ���
	const INT32 YK_WF_ON				=17;	//�����
	const INT32 YK_WF_OFF				=18;	//�����
	const INT32 YK_LOW_CURRENT_OFFON	=19;	//С����̽���Է�
	const INT32 YK_NONE					=-1;
	//Yt Action(command)
	const INT32 YT_OUT					=110;	//ң�����
	const INT32 YT_UP					=111;	//ң����
	const INT32 YT_DOWN					=112;	//ң����
	const INT32 YT_STOP					=113;	//ң����ֹ
	const INT32 YT_NONE					=-1;

	const INT32 YKYT_R_Fault			=0;		//ִ��ʧ��
	const INT32 YKYT_R_Finish			=1;		//��ִ��
	const INT32 YKYT_R_Skip				=2;		//������,���Ҫ�����ʱ�䳤��ǰĿ��ֵ����Ŀ��ֵ���趨ֵ��ͬ�����������

	//ң����������
	const INT32 YkPulse_No				=0;		//δ����
	const INT32 RELAYTYPE_Short			=1;		//������
	const INT32 RELAYTYPE_Long			=2;		//������
	const INT32 RELAYTYPE_Series		=3;		//�������
};

//��Լʵ�ʴ������Ϣ����
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

//��Լ�����ĺ��践�صĴ�������Ϣ
struct DEALDATAINFO		
{
	INT32  Bytes;					//�����ֽ���

	BOOL32 isSyncChar;			//��Ԥ�������յ�ͬ����,�ʴ�ʽ��Լ������ǰҪ���øñ�־��֪ͨϵͳ����ϴν��յĻ������ݣ������ҵ�ͬ��ͷ����
	INT32 iSyncCharPos;			//��Ԥ����ͬ������recebuf��λ��,�������-1����ʾ�ýڵ㲻��Ҫ�������ݣ������ýڵ�û�н�������Ҳ�������ͣ��״��
	char strDataInfo[64];		//��Ԥ����������Ϣ
	DWORD DataType;				//��Ԥ������Ϣ֡������ϱ�־,��Fr::FrameType::, =-1��0��ʾ��Ч

	BOOL32 TcpReConnect;			//�Ƿ���������TCP

	union{
		struct{
			WORD wMutiChn;			//��ר�ã��Ƿ�Ϊ��ͨ���೧վ
			WORD wNodeNo;				//��ר�ã���վ��
		};
		INT32 yourAddress;  //�����豸��ַ����һ���ڵ������豸ͨѶ���ã���485/422�Һ�«�ȷ�ʽ��
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

//ת�����ݵ�ӳ�䶨��
struct FrMapData{
	UINT8	noNode		;	//�ڵ��
	INT8	typeSource	;	//������Դ���� Fr::DataSourceType����
	INT16	no		;	//���ݵ��

	FrMapData(){
		typeSource = Fr::DataSourceType::RealValue;
		noNode = -1;
		no = -1;
	}
};

//ת������
struct FrTransMapBase{
	static const INT32 MyVersion = 101;
	INT32 StructVersion;  //����δ����̬���������İ汾��ʶ
	INT32 StructSize;  //����δ����̬���������İ汾��ʶ

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
	//��Ϣ����
	namespace MsgQueue{ //��Ϣ���д�С
		const INT32 DataSize		= 1024*1024;//client��Լ�����ݷ��ͻ�server�����ݽ��ն��л���������
		const INT32 CommandSize		= 1024*128;	//client��Լ��������ջ�server������Ͷ��л���������
		const INT32 MaxYxNum		= 3000;
		const INT32 MaxYcNum		= 3000;
		const INT32 MaxYmNum		= 1000;
		const INT32 MaxSoeNum		= 3000;
		const INT32 MaxYkNum		= 1000;
	};

	namespace CB{  //�仯��־λ
		const INT8 Value	= 0x01;  //ֵ�仯
		const INT8 FlagQ	= 0x02;  //Ʒ�ʱ仯
	};

	namespace Notify{  //��Ϣ֪ͨ�Ķ��峣��
		const INT32 None			= 0x00;  //��֪ͨ
		const INT32 Refresh			= 0x01;  //����ˢ��
		const INT32 ChangeValue		= 0x02;  //ֵ�仯
		const INT32 ChangeValue_Q	= 0x03;  //ֵ��Ʒ�ʱ仯
	};
}

struct MsgNotifyDef{//ʵʱ������Ϣ���ջ���������
	INT32	yxNum	;//���仯ң����Ϣ����,Ϊ0��Ϣ֪ͨ������Ч
	INT32	ycNum	;//���仯ң����Ϣ����,Ϊ0��Ϣ֪ͨ������Ч
	INT32	ymNum	;//���仯ң����Ϣ����,Ϊ0��Ϣ֪ͨ������Ч
	INT32	soeNum	;//���SOE��Ϣ����
	INT32	yxNotify;//ң����Ϣ֪ͨ����,�����Fm::Notify
	INT32	ycNotify;//ң����Ϣ֪ͨ����,�����Fm::Notify
	MsgNotifyDef(){
		memset(this, 0, sizeof(*this));
	}
};

#pragma pack(1)

struct FrDataIdx{   //ǰ����������
	BYTE	noNode	;	//�ڵ��0~255, =255��ʾ��Ч
	BYTE	dataSort;	//������𣬶����Fr::DataSort:
	UINT16	no		;	//���ݵ��, =65535��ʾ��Ч
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

	//ת��Ϊ�ַ���(ͨ����̬����е���������)
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

	//����ת��ΪPLC�ַ���(PLC������������Դ����)
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

	//�����ַ���Ϊ�ڵ�����
	BOOL32 SetData(CHAR *text1){
		if ((text1[0]!='N')||(text1[4]!='<')||(text1[5]!='Y')||(text1[7]!='>')||(text1[8]!=':'))
			return FALSE;  //�Ƿ�����
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
	//����PLC���������ַ���Ϊ�ڵ�����
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

//��Ϣͷ
struct FrMsgHead{
	INT32	liveTimeSysPuls	;	//��Ϣ������Ч��ϵͳ�����,�����ֵ��ǰ��ϵͳ�ṩ��
	//�����þ���ʱ���Ƿ�ֹϵͳ���ʱ��ɼ��㳬ʱ���� 
	//<��ǰ��ϵͳ�������ʾ��ϢʧЧ��<=0�϶�ʧЧ
	INT32	iSrcAddress		;	//��Ϣ�����ߵ�װ�õ�ַ
	INT32	srcNodeNo		;	//��Ϣ�����ߵ�ͨѶ�ڵ��
	INT16	msgType			;	//��Ϣ����,�����Fm::MT
	INT16	lenData			;	//��Ϣ������ʵ�����ݳ��ȣ�����FrMsgHead����
	FrMsgHead(){
		msgType = -1;
		liveTimeSysPuls = -1;
		iSrcAddress = -1;
		srcNodeNo = -1;
		lenData = 0;
	}
};

//����~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct RelayInfoMsgData	: FrMsgHead	
{
	INT32 RelayType_Ht;			//��̨��������		����ϵͳ�Զ��
	INT32 RelayType_Front;		//ǰ��ϵͳ��������  ����ϵͳ�Զ��
	INT32 DevAddr;				//�����豸��ַ		����ϵͳ�Զ��
	INT32 srcOperNodeNo;			//������Դ          ����ϵͳ�Զ��(ǰ��ͨѶ�ã� 0 -- 128  ���Ȳ�����1000 ��غ�̨����)

	INT32 RelayType_Protocol;		//ͨѶ��Լ��������  (�����Լ��������ȫ������IEC-870-5-103��Լ���˴���ֵ��Ч��������)
	BOOL32 bAutoUpData;			//�Ƿ�Ϊ�������ͱ��ģ����б���ʹ�ã�Ĭ���ǣ�
	INT32 BufLen;					//����Buffer����
	BYTE RelayBuffer[400];		//����Buffer

	WORD Type;					//�Զ������� ������ת���͵���ת��ģʽ��Ϊ�������� Fr_DdTrans_RelayEvent��Fr_DdTrans_WaveMessage��Fr_DdTrans_WaveAnalyze��
	WORD Code;					//�Զ�������
	INT32 Reserved[19];			//Ԥ��
	RelayInfoMsgData()
	{
		memset(this, 0, sizeof(*this));
		RelayType_Ht=RelayType_Front=DevAddr=-1;			//(-1 ��ʾ�ýṹֵ��Ч��
		srcOperNodeNo=1000;
		lenData = sizeof(*this) - sizeof(FrMsgHead);

		RelayType_Protocol=-1;
		bAutoUpData=TRUE;
	};
};

#pragma pack()

const INT32 QBitIec = 0x1fff;
//����״̬Ʒ�ʵ�IEC��׼��Ӧ��־λ,��Լ�������
const INT32 QBitIecInvalidity		=  Fr::QBit::IecInvalidity		;	//���仯��ֵ��Ч
const INT32 QBitIecQuestionable		=  Fr::QBit::IecQuestionable	;	//������
const INT32 QBitIecOverFlow			=  Fr::QBit::IecOverFlow		;	//���
const INT32 QBitIecOutOfRange		=  Fr::QBit::IecOutOfRange		;	//��������
const INT32 QBitIecBadReference		=  Fr::QBit::IecBadReference	;	//��������
const INT32 QBitIecOscillatory		=  Fr::QBit::IecOscillatory		;	//���̶�
const INT32 QBitIecFailure			=  Fr::QBit::IecFailure			;	//����
const INT32 QBitIecOldData			=  Fr::QBit::IecOldData			;	//��ֵ
const INT32 QBitIecInconsistent		=  Fr::QBit::IecInconsistent	;	//��ì��
const INT32 QBitIecInaccurate		=  Fr::QBit::IecInaccurate		;	//����ȷ
const INT32 QBitIecSubstituted		=  Fr::QBit::IecSubstituted		;	//�˹�����,������
const INT32 QBitIecTest				=  Fr::QBit::IecTest			;	//����
const INT32 QBitIecOperatorBlocked	=  Fr::QBit::IecOperatorBlocked	;	//����������

//ƽ̨�������õ�Ʒ��λ����IECƷ���ж�Ӧ��ϵ��ͨ�Ź�Լʹ��IEC��׼Ʒ�ʣ�Ӧ�ýڵ�ʹ��ƽ̨Ʒ��
const INT32 QBitAbnormal			=   0x2000;	//�쳣,��ӦIECƷ�� QBitIecFailure|QBitIecQuestionable
const INT32 QBitValueDead			=   0x4000;	//���仯��ֵ��Ч����ӦIECƷ�� QBitIecInvalidity|QBitIecOldData
const INT32 QBitManLock				=   0x8000;	//����������ӦIECƷ��QBitIecSubstituted
const INT32 QBitDisableAlarm		=  0x10000;	//����������
const INT32 QBitByPass				=  0x20000;	//����·

const INT32	QFlgIecValueDead		= QBitIecInvalidity | QBitIecOldData;
const INT32	QFlgIecAbnormal			= QBitIecFailure | QBitIecQuestionable | QBitIecInconsistent;
const INT32	QFlgIecManset			= QBitIecSubstituted;

const INT32 QBitNotUpdate	= QBitValueDead | QBitIecInvalidity | QBitIecOldData;   //ֵ��ˢ��
const INT32 QBitFault		= QBitAbnormal | QBitIecQuestionable | QBitIecFailure;  //ֵ����
const INT32 QBitErr			= QBitFault | QBitNotUpdate;							//ֵ���󣬰�����ˢ�¡�ֵ����

struct NodeYxBaseData
{
	static const INT32 QBitChange				=  0x40000;	//��λ
	static const INT32 QBitAccident				=  0x80000;	//�¹�
	static const INT32 QBitSimulateState		= 0x100000;	//����״̬
	static const INT32 QBitWFState				= 0x200000;	//���Ԥ��״̬
	static const INT32 QBitAskRevert			= 0x400000;	//�����źŸ���

	//�����־�Ķ�Ӧ��־λ
	static const INT32 PBitNoValueDeadStat	=    0x01;	//���ж�ֵ��Ч	
	static const INT32 PBitIec61850Flag		=	 0x02;	//IEC61850��־��Ч
	static const INT32 PBitReverse			=    0x04;	//״̬ȡ��
	static const INT32 PBitSOEAsCOS			=    0x08;	//SOE��ΪCOS

	static const INT32 PBitCosAlarm			=    0x10;	//����ʷ��¼
	static const INT32 PBitAbnormalAlarm	=    0x20;	//���쳣�澯,����ʷ��¼ʱ��Ч
	static const INT32 PBitFaultAlarm		=    0x40;	//�ǹ��ϸ澯,����ʷ��¼ʱ��Ч������Ȳ����쳣�ֲ��ǹ���,������ʾ�澯

	CHAR	szName[Fr::NAME_LENGTH];  //����
	INT32	flgProc		;	//�����־

	NodeYxBaseData(){
		memset(this, 0, sizeof(*this));
	}
} ;

struct NodeYcBaseData
{
	//����״̬Ʒ�ʵĶ�Ӧ��־λ
	static const INT32 QBitOverHiLimit			=   0x40000;	//Խ����
	static const INT32 QBitOverLoLimit			=   0x80000;	//Խ����
	static const INT32 QBitOverHiHiLimit		=  0x100000;	//Խ������
	static const INT32 QBitOverLoLoLimit		=  0x200000;	//Խ������
	static const INT32 QBitOverLimit			=  0x400000;	//Խ��
	static const INT32 QBitValueUpBreak			=  0x800000;	//�����䷢��
	static const INT32 QBitValueDownBreak		= 0x1000000;	//�����䷢��
	static const INT32 QBitValueOverFlow		= 0x4000000;	//���
	static const INT32 QBitValueOutOfRange		= 0x8000000;	//��������

	static const INT32 QBitOverUnion			= QBitOverLimit | QBitOverLoLoLimit | QBitOverHiHiLimit | QBitOverLoLimit | QBitOverHiLimit;

	static const INT32 QBitYcSacad				= 0xffc0000;	//SCADA����ı�־λ

	//�����־�Ķ�Ӧ��־λ
	static const INT32 PBitNoValueDeadStat		=      0x01;	//���ж�ֵ��Ч
	static const INT32 PBitIec61850Flag			=	   0x02;	//IEC61850��־��Ч
	static const INT32 PBitReverse				=      0x04;	//���ű䷴
	static const INT32 PBitAbsolute				=      0x08;	//ȡ����ֵ
	//static const INT32 PBitGrads				=      0x10;	//�ݶȴ���
	//static const INT32 PBitJudgeOverLimit		=      0x20;	//��Խ��
	//static const INT32 PBitValueBreakAlarm	=      0x40;	//ֵͻ�䴦��
	//static const INT32 PBitSimpleValueBreakAlarm=      0x80;	//��ͻ�䴦��

	static const INT32 PBitBak1					=      0x10;	//����
	static const INT32 PBitBak2					=      0x20;	//����
	static const INT32 PBitBak3					=      0x40;	//����
	static const INT32 PBitAlarmAbnormal		=      0x80;	//�쳣�澯,���Ϊ0��Խ������Ϊ��ʾ�澯��Խ����Ϊ�쳣�澯;���Ϊ1��Խ������Ϊ�쳣�澯��Խ����Ϊ���ϸ澯;
	
	static const INT32 PBitExistPlan			=     0x100;	//�мƻ�ֵ
	static const INT32 PBitTrendData			=     0x200;	//����������������
	static const INT32 PBitCoeff				=     0x400;	//��Ҫ��ϵ���任�������Զ��ж�ϵ���ͻ�ֵ����

	static const INT32 PBitHisSample			=     0x800;	//����ʷ�������̶�1���Ӽ�¼
	static const INT32 PBitHisStat				=    0x1000;	//����ʷͳ�ƣ�����ƽ�����������С��ʱ��
	static const INT32 PBitEveryMinStat			=    0x2000;	//ÿ����ͳ�ƣ�ȱʡ��ÿ��ͳ��
	static const INT32 PBitZeroNotStat			=    0x4000;	//��ֵ��ͳ��

	static const INT32 PBitStaticHisSample		=    0x8000;	//����ʷ��������̬״̬����ԭʼ���ñ��޸ģ����ݼ���ʱ������
	static const INT32 PBitStaticHisStat		=   0x10000;	//����ʷͳ�ƣ���̬״̬����ԭʼ���ñ��޸ģ����ݼ���ʱ������
	static const INT32 PBitStaticEveryMinStat	=   0x20000;	//ÿ����ͳ�ƣ���̬״̬����ԭʼ���ñ��޸ģ����ݼ���ʱ������


	CHAR	szName[Fr::NAME_LENGTH];  //����
	INT32	flgProc				;//�����־

	FLOAT32	fBaseValue			;//��ֵ
	FLOAT32	fCoefValue			;//ϵ�� fCoefValue = fFactorValue * fScaleValue
	FLOAT32	fScaleValue			;//���ϵ��
	FLOAT32	fFactorValue		;//�α�����
//	FLOAT32	fFilterValue		;//�˲�ϵ��
	FLOAT32	fDelaySec			;//�ӳ�ʱ��, ��λ��,�޸�ʱ�䣺2020.1.7,ȡ��fFilterValue
	FLOAT32	fRemainsValue		;//�вҲ��Խ���ж��������������������澯����������Χ��Ҫ�ж��ӳ�ʱ��
	FLOAT32	fValidUpperValue	;//��Ч����
	FLOAT32	fValidLowerValue	;//��Ч����
	FLOAT32	fNormalUpperValue	;//��������
	FLOAT32	fNormalLowerValue	;//��������
	FLOAT32	fGradsValue			;//��Ч�ݶ�
	CHAR	szUnitName[16]		;//��λ

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
	//�����־�Ķ�Ӧ��־λ
	static const INT32 PBitNoValueDeadStat		=    0x01;	//���ж�ֵ��Ч	

	static const INT32 PBitHisSample		=    0x02;	//����ʷ��������ң���������,ym�������Զ���ң���Ž������У���m��yc����n��ym����ʷ��¼���ݺŰ�ң��m+n��������㡣
	static const INT32 PBitStaticHisSample	=    0x04;	//����ʷ��������̬״̬����ԭʼ���ñ��޸ģ����ݼ���ʱ������

	CHAR	szName[Fr::NAME_LENGTH]	;//����
	INT32	flgProc				;//�����־

	FLOAT32	fScaleValue			;//����
	INT32	iComputeType				;//���㷽ʽ(����)
	UINT32	numPulseEveryKwh			;//ÿ��������
	UINT32	numFullPulse				;//��������ֵ
	UINT32	numValidPulse				;//���������Чֵ
	FLOAT32	fFullValue					;//�������ֵ
	CHAR	szUnitName[Fr::NAME_LENGTH]	;//��λ

	void SetDefault()
	{
		memset(this, 0, sizeof(*this));
		fScaleValue = 1.0f;
		numPulseEveryKwh	= 1		;//ÿ��������
		numFullPulse		= 0xffffff;//��������ֵ
		numValidPulse		= 30000  ;//���������Чֵ
		fFullValue			= 10000	;//�������ֵ
	};
	NodeYmBaseData(){
		SetDefault();
	}
};

struct NodeYkBaseData
{
	static const INT32 PBitForbidControlClose	=   0x01;//ң�غϱ�����
	static const INT32 PBitForbidControlOpen	=   0x02;//ң�طֱ�����
	static const INT32 PBitWFForbidControlClose	=   0x04;//����ϲ���������
	static const INT32 PBitWFForbidControlOpen	=   0x08;//����ֲ���������
	static const INT32 PBitControlReverse		=   0x10;//�����ת,�������ϡ�������, �����Է�תǰΪ׼

	CHAR	szName[Fr::NAME_LENGTH];  //����
	INT32	iYxAddress	;	//��Ӧң��ֵ��ң�Žڵ�װ�õ�ַ��
	INT32	yxNo		;	//��Ӧң��ֵ��ң�Žڵ����
	INT32	flgProc		;	//�����־
	INT32	YkPulse		;	//ң����������,�����Fr::RELAYTYPE_Short��

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
	static const INT32 PBitForbid		=   0x01;//ң������������
	static const INT32 PBitForbidUp		=   0x02;//ң��������������
	static const INT32 PBitForbidDown	=   0x04;//ң��������������
	static const INT32 PBitWFForbid		=   0x08;//����ң������������
	static const INT32 PBitWFForbidUp	=   0x10;//����ң��������������
	static const INT32 PBitWFForbidDown	=   0x20;//����ң��������������
	static const INT32 PBitControlReverse	=   0x40;//�����ת,����������������, �����Է�תǰΪ׼

	CHAR	szName[Fr::NAME_LENGTH];  //����
	INT32	iYcAddress	;	//��Ӧң��ֵ��ң��ڵ�װ�õ�ַ��
	INT32	ycNo		;	//��Ӧң��ֵ��ң��ڵ����
	INT32	flgProc		;	//�����־
	FLOAT32	fStepValue	;	//ÿ��ң���̶�������ģ����ֵ(����ֵ)

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
	static const INT32 CommType_SeriPort= 1;//����
	static const INT32 CommType_Net		= 2;//ר��
	static const INT32 CommType_URL		= 3;//����

	static const UINT8 SeriPort_RS232	=0;
	static const UINT8 SeriPort_RS485	=1;
	static const UINT8 SeriPort_RS422	=2;

	static const INT32 NetType_Udp		= 0;
	static const INT32 NetType_TcpServer= 1;
	static const INT32 NetType_TcpClient= 2;

	union{
		struct{
			CHAR	ComPort[Fr::NAME_LENGTH]		;	//����ͨѶ�˿�
			CHAR	ComSetting[Fr::NAME_LENGTH]		;	//����ͨѶ����
		};
		struct{
			CHAR	noUseChar[8]					;	//w�����ַ�
			BOOL32	isSSL							;	//�Ƿ�safe socket���ӣ���֤�ļ����Լ����ͬ��ȥ��c_,��׺Ϊ_ca.crt,��c_91greenpower.lcn�������֤�ļ���Ϊ91greenpower_ca.crt
			UINT32	port_of_domain					;	//������ͨ�ŷ���˿ں�
			CHAR	domainName[Fr::NAME_LENGTH*2-16];	//��������
		};
	};

	UINT8	nCommType		;	//ͨѶ������,COMMPARA::CommType_SeriPort��
	UINT8	NetType			;	//������������,COMMPARA::NetType_TcpServer��
	UINT16	MaxClientNum	;	//���Ŀͻ���������, Ϊ0�����ƣ���COMMPARA::NetType_TcpServer��Ч

	INT32	YouNetIp		;	//�Բ��IP
	UINT32	YouNetPort		;	//�Բ���˿ں�
	UINT32	MyNodeNetPort	;	//�����˿ں�
	UINT32	MyNodeNetIp		;	//������IP
	UINT8	SeriPortType	;	//��������,COMMPARA::SeriPort_RS
	CHAR	noUse[3]		;	//�����ֽ�
	CHAR	bakBytes[20]	;	//�����ֽ�

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

struct HardWareInfor{   //�豸Ӳ��������Ϣ
	FLOAT32		fCpuLoadRate	;	//CPU������
	FLOAT32		fCpuLoadMinute5	;	//5������CPUƽ������
	FLOAT32		fRamUse			;	//�ڴ�ʹ�����ٷֱ�
	FLOAT32		fOutMemUse		;	//���ʹ�����ٷֱ�
	FLOAT32		fTotalOutMemSpace;	//���������,��λM
	FLOAT32		fTotalRamSpace	;	//�ڴ�������,��λM
	FLOAT32		fCpuLoadForMain ;	//�������CPU������
	FLOAT32		fRamUseForMain	;	//��������ڴ�ռ����

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

struct NodeExtraHead{ //�ڵ���չ����ͷ�ṹ  add on 2017.03.25
	static const INT32 S_Normal			=  0;	//��ͨ
	static const INT32 S_NamePlate		=  1;	//���Ʋ���,�Ǿ�̬��Ϣ
	static const INT32 S_Identification	=  2;	//��ݱ�ʶ�����������豸Ψһ�Եľ�̬��Ϣ
	static const INT32 S_Setting		=  3;	//��ֵ
	static const INT32 S_Log			=  4;	//��־��Ϣ
	static const INT32 S_History		=  5;	//��ʷ����

	static const INT32 QBitInvalid	=  0x01;	//������Ч
	static const INT32 QBitError	=  0x02;	//������Ч

	static const INT32 PBitSave		=  0x01;	//��Ҫ����

	CHAR	name[32]	;//����������CHAR�������ͣ������ĺ��壬����Ϊ32���ַ���
	INT32	size		;//��Ч���ݷ���ռ�
	UINT8	sort		;//�������,�������NodeExtraHead::S_
	UINT8	dataType	;//��������,�������BDT::
	UINT8	flgProc		;//�����־,�������NodeExtraHead::PBit
	UINT8	flgQ		;//Ʒ��,�������NodeExtraHead::QBit
	INT32	dataLen		;//����ֵ��ʵ�ʳ���
	INT64	tm			;//ˢ��ʱ�䣬���ݱ���Լʵʱ���µ�ʱ��

	//��ʼ����չ����ͷ���壬�����־ȱʡΪ��Ҫ����
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
