#include "c_myLcn.h"

static CHAR dscProtocol[] = "（白板）客户端规约开发示例。\n V1.0  \n 开发人：XXX 开发时间：XXXX年XX月XX日";   // "\n"表示后面内容换行

static CHAR dscProtocol_en[] = "The empty client example protocol, \n for developer V1.0";  

extern void SetCfgDef(CCommonCfgDef *pCfgDef1, BOOL32 isEnglish);

//创建节点的规约处理对象
extern "C" LCNIFENTRY CLcnIF* Create_NodeObj() 
{
    CMyLcn_C *pObj = new CMyLcn_C();
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
	PtOtherInfo.fProtocolVersion = Fr::SystemVersion;//设置版本号
	PtOtherInfo.ProtocolType=Fr::Protocol::PClient;		//规约类型,客户端规约必须声明为Fr::Protocol::PClient
	
	PtOtherInfo.flgApp  = 0;

	PtOtherInfo.flgProc = 0;
	PtOtherInfo.flgProc |= PTOTHERINFO::PBitYkSelectCheck;  //规约支持遥控选择处理，
															//如果不设该标志，ncomm平台会自动对遥控选择命令进行返校，规约程序将只需处理遥控执行命令即可

	PtOtherInfo.flgProc |= PTOTHERINFO::PBitYtSelectCheck;  //规约支持遥调选择处理
															//如果不设该标志，ncomm平台会自动对遥调选择命令进行返校，规约程序将只需处理遥调执行命令即可

	//PtOtherInfo.ZtType是设置规约组态类型 
	//如果规约无需组态，则应设置： PtOtherInfo.ZtType = Fr::CFG::NONE; 则下面43-48行代码要被删除。可参见项目s_example的GetProtocolIdentify使用
	PtOtherInfo.ZtType		  =  Fr::CFG::NONE;  // 无需组态

	/////////////////////////////////////////////////////////////////////////////////////
	// 预留读取通用组态配置数据结构的代码。
	/////////////////////////////////////////////////////////////////////////////////////

	PtOtherInfo.Timer = 200;   //缺省为每200ms收发一次报文，根据实际需要，通常取值5~10000ms

	//设置规约最大容量,便于组态时对数量进行限制
	PtOtherInfo.MaxYc = P_YX_MAX;
	PtOtherInfo.MaxYx = P_YC_MAX;
	PtOtherInfo.MaxYm = P_YM_MAX; 
	PtOtherInfo.MaxYk = P_YK_MAX;
	PtOtherInfo.MaxYt = P_YT_MAX;

	if (PtOtherInfo.flgCfg & PTOTHERINFO::CBitEnglish)
		 return dscProtocol_en; //返回英文的规约描述，用于ConfigTool这种显示
	else 
		 return dscProtocol;	//返回中文的规约描述，用于ConfigTool这种显示
}
