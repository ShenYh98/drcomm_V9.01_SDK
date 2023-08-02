#ifndef _LCN_STRUCT_DEF_H_
#define _LCN_STRUCT_DEF_H_

#include "PubDef.h"
#include "LCNTIME.h"

/**
@file LCN�õ��Ľṹ����
@version v1.01
@author 
@date 
*/

//�ڵ�������(����)����Ϣ
struct NodeReadmeInfo{
	INT32	No						;	//�ڵ��
	CHAR	Name[Fr::NAME_LENGTH]	;   //�ڵ���
	INT32	nNodeType				;	//�ڵ����ͣ�Fr::Protocol����
	UINT32	dwZzAdr					;	//װ�õ�ַ
	CHAR	ProtocolFile[Fr::NAME_LENGTH];	//��Լ�ļ���,����·��
	INT32	noTransDataSet			;	//ת�����
	INT32	numChannel				;	//ͨ������,ȡֵ0��2
	INT32	CommModeForDoubleMachine;	//˫��ͨѶģʽ�� Fr::CommModeForDouble����
	INT32	CommModeForDoubleChannel;	//˫ͨ��ͨѶģʽ�� Fr::CommModeForDouble����
	INT32	YkSet					;	//ң���������ͣ� Fr::YkSetType_
	CHAR	NodeDeviceType[16]		;	//�ڵ��豸����
};


//��Ϣ�����еı仯ң��~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct YxMsg
{
	INT32	no			;	//ң�ŵ��,Ϊ��Ϣ�������ڵ����ڵĵ�ţ�ϵͳ���ɷ�ʱ��ת��Ϊ���ն���ڵ�ĵ��
	INT32	iCodeValue	;	//ͨ����ֵ
	INT32	iValue		;	//ң��ֵ,��ת�������þ����Ƿ���ͨ����ֵ���Ǵ�����ֵ
	LCNTIME   t			;	//ˢ��ʱ��
	INT32	flgQ		;	//����Ʒ�ʱ�־
	INT8	typeSource	;	//������Դ���� Fr::DataSourceType����
	INT8	flgChange	;	//���ݱ仯��־,Fm::CB::����

	YxMsg()
	{
		no = -1;
		flgChange = 0;
	};
};

//��Ϣ�����е�SOE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct SoeMsg
{
	INT32	no			;	//ң�ŵ�ţ�Ϊ��Ϣ�������ڵ����ڵĵ�ţ�ϵͳ���ɷ�ʱ��ת��Ϊ���ն���ڵ�ĵ��
	INT32	iCodeValue	;	//ͨ����ֵ
	INT32	iValue		;	//ң��ֵ,��ת�������þ����Ƿ���ͨ����ֵ���Ǵ�����ֵ
	LCNTIME   tmSoe		;	//����ʱ��
	INT32	flgQ		;	//����Ʒ�ʱ�־
	INT8	typeSource	;	//������Դ���� Fr::DataSourceType����
	INT8	flgChange	;	//���ݱ仯��־����Ч

	SoeMsg()
	{
		no = -1;
		flgChange = 0;
	}
};

//��Ϣ�����еı仯ң��~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct YcMsg
{
	INT32	no			;	//ң���ţ�Ϊ��Ϣ�������ڵ����ڵĵ�ţ�ϵͳ���ɷ�ʱ��ת��Ϊ���ն���ڵ�ĵ��
	INT32	iCodeValue	;	//�����ͽڵ���ֵ
	FLOAT32 fValue		;	//������ң��ֵ,��ת�������þ����Ƿ���ͨ����ֵ���Ǵ�����ֵ
	LCNTIME   t			;	//ˢ��ʱ��
	INT32	flgQ		;	//����Ʒ�ʱ�־
	INT8	typeSource	;	//������Դ���� Fr::DataSourceType����
	INT8	flgChange	;	//���ݱ仯��־ Fm::CB::����

	YcMsg()
	{
		no = -1;
		flgChange = 0;
	}
};

//��Ϣ�����е�ң��~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct YmMsg
{
	INT32	no			;	//ң�����,Ϊ��Ϣ�������ڵ����ڵĵ�ţ�ϵͳ���ɷ�ʱ��ת��Ϊ���ն���ڵ�ĵ��
	UINT32	uCodeValue	;	//�����ͽڵ���ֵ��ͨ��PTOTHERINFO.bDataFloat����������һ������ң��ֵ��Ĭ����UINT32��
	FLOAT32	fCodeValue	;	//�������ͽڵ���ֵ(fCodeValue ��uCodeValueͬʱ����)
	FLOAT32 fValue		;	//������ĸ����͵��ֵ�������������ת��fPrimaryValue = fSecondaryValue * fScaleValue
	LCNTIME   t			;	//ˢ��ʱ��
	INT32	flgQ		;	//����Ʒ�ʱ�־
	INT8	typeSource	;	//������Դ���� Fr::DataSourceType����
	INT8	flgChange	;	//���ݱ仯��־,Fm::CB::����

	YmMsg()
	{
		no = -1;
		flgChange = 0;
	}
};

struct YkYtMsg{
	LCNTIME   OperateTime;	//����ʱ��
	INT32   DdYk_ZzAdr;		//������Դ�ڵ�װ�õ�ַ

	INT32	ObjectNo;		//���ڵ��Ӧ��ң��ң�������,ϵͳ���ɷ�ʱ�����UpYk��ObjectNo��ת������Ϊ���ն���ڵ�ĵ��
	INT32	srcOperObjectNo_ExecNodeNo;//������Դ�ڵ��ң��ң������ţ���ϵͳ�Զ��UpYk�ǿͻ��˹�Լ��Ч��DownYk�ͻ��˹�Լ��Ч
	//ע������Ӧ����ڵ㣬��Ϊû��ת����Դ�ڵ������Ѿ���Ч��ʵ����ָ�������ڵĽڵ��
	INT32	srcOperNodeNo;	//������Դ�ڵ��    ����ϵͳ�Զ��(ǰ��ͨѶ��)  Ns3000 ��DataSource
	INT32	Action;			//����ң�أ�=Fr::YK_ON�ȣ������ϡ������֡�ͬ�ںϡ�����ѹ�ϡ����춨ͬ�ںϡ��ϻ��ϡ�����ϡ�����֡�С����̽���Էֵ�
	//����ң����=Fr::YT_OUT�ȣ�

	INT32	State;			//����ң�أ�=Fr::YK_IDLE�ȣ�����״̬��û��ң��:����YK_IDLE��
	BOOL32	IsYk;			//ң�� or ң��

	BOOL32	IsDinYk;		//�Ƿ�˫��ң��

	INT32	CaliInfo;		//ң�� or ң�� ������, �����NS::YkErrExplain::e, ��Է���YK_NAK�Ĵ������

	INT32    OtherType;		//OtherType=0 ����ң�ء�OtherType=1  ģ����(����ֵ)�����OtherType=2  ģ����(����ֵ)���������ֵ��Ч��

	FLOAT32 OtherValue;		//ģ����(����ֵ)  OtherType=1
	INT32	OtherValue2;	//ģ����(����ֵ)  OtherType=2
	INT32	srcState;		//Դң��״̬�����ڿ��Ʒ�Уʱ����ԭʼ״̬
};


struct YxData : NodeYxBaseData{
	LCNTIME	t			;	//ˢ��ʱ��
	INT32	iCodeValue	;	//ң��ͨ����
	INT32	iValue		;	//ң��ֵ��������
	INT32	flgQ		;	//����Ʒ�ʱ�־
	YxData(){
		memset(this, 0, sizeof(*this));
	}
};

struct YcData : NodeYcBaseData{
	LCNTIME	t					;//ˢ��ʱ�䣨��ϵͳ�Զ��
	INT32	iCodeValue			;//������ͨ����ֵ��ͨ��PTOTHERINFO.bDataFloat����������һ������ң��ֵ��Ĭ����INT32��
	FLOAT32 fCodeValue			;//������ͨ����ֵ(fCodeValue ��iCodeValueͬʱ����)
	FLOAT32 fValue				;//������ң��ֵ�������� = fCodeValue * fCoefValue + fBaseValue
	INT32	flgQ				;//����Ʒ�ʱ�־

	YcData(){
		memset(this, 0, sizeof(*this));
	}
};

struct YmData : NodeYmBaseData{
	LCNTIME	t					;//ˢ��ʱ�䣨��ϵͳ�Զ��
	UINT32	uCodeValue			;//������ͨ����ֵ��ͨ��PTOTHERINFO.bDataFloat����������һ������ң��ֵ��Ĭ����UINT32��
	FLOAT32 fCodeValue			;//������ͨ����ֵ(fCodeValue ��uCodeValueͬʱ����)
	FLOAT32 fValue				;//�����͵��ֵ��������,�����������ת��fPrimaryValue = fSecondaryValue * fScaleValue
	INT32	flgQ				;//����Ʒ�ʱ�־
	FLOAT32	fSecondaryValue		;//���ε��ֵ

	YmData(){
		memset(this, 0, sizeof(*this));
	}
};


struct YkData : NodeYkBaseData{
	LCNTIME	OperateTime		;	//�������ʱ��
	LCNTIME	ReturnTime		;	//�����ʱ��
	UINT32	dwOperateZzAdr	;	//�����������ڵ��װ�õ�ַ,���ڷ����Լ��Ϊʵ���·����ƵĽڵ㣬���ڿͻ���Լ����Ϊ�����������Դ�ڵ�
	INT32	srcOperObjectNo	;	//�����������ڵ�ң�ض����,���ڷ����Լ��Ϊʵ���·����ƵĽڵ����ţ����ڿͻ���Լ����Ϊ�����������Դ�ڵ�Ķ����
	INT32	Action			;	//�����ϡ������֡�ͬ�ںϡ�����ѹ�ϡ����춨ͬ�ںϡ��ϻ��ϡ�����ϡ�����֡�С����̽���Էֵ�
	INT32	srcOperNodeNo	;	//�����������ڵ�ţ���ϵͳ�Զ��,���ڷ����Լ��Ϊʵ���·����ƵĽڵ㣬���ڿͻ���Լ����Ϊ�����������Դ�ڵ�
	INT32	State			;	//����״̬��û��ң��:���С�����:ң��ѡ��ң��ִ�С�ң�س���������:��У��ȷ����У����ȣ�(-1 ��ʾ�ýṹֵ��Ч��
	INT32	iReturnInfo		;	//ң�ط����� Ns2000��ΪCaliInfo
	UINT32	DdYk_RtuNo		;	//����ת��ģʽר�ã�ͨѶ�ӿڲ��� - ��վ��					��DdYk_Type=0��

	YkData(){
		memset(this, 0, sizeof(*this));
	}
};

struct YtData : NodeYtBaseData{
	LCNTIME	OperateTime		;	//�������ʱ��
	LCNTIME	ReturnTime		;	//�����ʱ��
	UINT32	dwOperateZzAdr	;	//�����������ڵ��װ�õ�ַ,���ڷ����Լ��Ϊʵ���·����ƵĽڵ㣬���ڿͻ���Լ����Ϊ�����������Դ�ڵ�,debugtool��������Ӧ��ң�ػ�ң��ֵ
	INT32	srcOperObjectNo	;	//�����������ڵ�ң�ض����,���ڷ����Լ��Ϊʵ���·����ƵĽڵ㣬���ڿͻ���Լ����Ϊ�����������Դ�ڵ�
	INT32	Action			;	//ң��ģ���������ң����ִ�С�ң����ִ�С�ң��������
	INT32	srcOperNodeNo	;	//�����������ڵ�ţ���ϵͳ�Զ��,���ڷ����Լ��Ϊʵ���·����ƵĽڵ㣬���ڿͻ���Լ����Ϊ�����������Դ�ڵ�
	INT32	State			;	//����״̬��û��ң��:���С�����:ң��ִ�С�ң������������:��У��ȷ����У����ȣ�(-1 ��ʾ�ýṹֵ��Ч��
	INT32	iReturnInfo		;	//ң��������
	INT32	iOutType		;	//������ͣ� ==1 ��ʾ����ֵ�����==2��ʾ����ֵ���
	INT32	iOutValue		;	//ģ����(����ֵ)
	FLOAT32	fOutValue		;	//ģ����(����ֵ)

	YtData(){
		memset(this, 0, sizeof(*this));
	}
};

#endif
