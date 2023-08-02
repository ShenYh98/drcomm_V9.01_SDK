#include "s_myLcn.h"

static CHAR dscProtocol[] = "服务端规约开发示例 \n V1.0  \n 开发人：XXX 开发时间：XXXX年XX月XX日\n客户程序可以通过调用ncommData.dll库来接收该规约用tcp server方式转发的数据";

static CHAR dscProtocol_en[] = "Example protocol, for developer V1.0";

//创建节点的规约处理对象
extern "C" LCNIFENTRY CLcnIF* Create_NodeObj()
{
	CMyLcn_S *pObj = new CMyLcn_S();

	return pObj;
}

//释放节点的规约处理对象
extern "C" LCNIFENTRY void Destroy_NodeObj(CLcnIF* p)
{
	p->V_NodeDestroy();
	delete p;
}

//得到规约类型信息，返回规约描述，主要用于组态程序调用。
extern "C" LCNIFENTRY LPSTR GetProtocolIdentify(PTOTHERINFO &PtOtherInfo)
{
	PtOtherInfo.fProtocolVersion = Fr::SystemVersion; //设置版本号
	PtOtherInfo.ProtocolType = Fr::Protocol::PServer;	//规约类型,服务端规约必须声明为Fr::Protocol::PServer

	PtOtherInfo.flgApp  = 0;
	PtOtherInfo.flgProc = 0;
	PtOtherInfo.flgProc |= PTOTHERINFO::PBitYkSelectCheck;  //规约支持遥控选择处理，
	//如果不设该标志，ncomm平台会自动对遥控选择命令进行返校，规约程序将只需处理遥控执行命令即可

	PtOtherInfo.flgProc |= PTOTHERINFO::PBitYtSelectCheck;  //规约支持遥调选择处理
	//如果不设该标志，ncomm平台会自动对遥调选择命令进行返校，规约程序将只需处理遥调执行命令即可

	PtOtherInfo.ZtType		  =  Fr::CFG::NONE; 	//规约的组态没有，如需设置，请参考c_example项目
	PtOtherInfo.pCommonCfgDef = NULL;

	PtOtherInfo.Timer = 500;  //缺省为每500ms收发一次报文，根据实际需要，通常取值5~10000ms

	PtOtherInfo.MaxYc		= P_YX_MAX;	//不同的规约有各自的数量限制
	PtOtherInfo.MaxYx		= P_YC_MAX;
	PtOtherInfo.MaxYm	= P_YM_MAX;
	PtOtherInfo.MaxYk		= P_YK_MAX;
	PtOtherInfo.MaxYt		= P_YT_MAX;

	if (PtOtherInfo.flgCfg & PTOTHERINFO::CBitEnglish)  //返回规约描述，用于ConfigTool这种显示
		return dscProtocol_en; //返回英文的规约描述，用于ConfigTool这种显示
	else return dscProtocol;   	//返回中文的规约描述，用于ConfigTool这种显示
}
