#include "a_myLcn.h"

static CHAR dscProtocol[] = "应用功能开发示例。\n V1.0  功能：用加热器控制室温，维持室温在温度上限和温度下限之间。\n温度参数是在组态中设置，\n 开发人：XXX 开发时间：XXXX年XX月XX日";   // "\n"表示后面内容换行

static CHAR dscProtocol_en[] = "application example, \n for developer V1.0";  

extern void SetCfgDef(CCommonCfgDef *pCfgDef1, BOOL32 isEnglish);

//创建节点的规约处理对象
extern "C" LCNIFENTRY CLcnIF* Create_NodeObj() 
{
    CMyLcn_A *pObj = new CMyLcn_A();
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
	PtOtherInfo.ProtocolType=Fr::Protocol::APP;		//应用功能规约类型必须声明为Fr::Protocol::APP

	PtOtherInfo.flgApp  = 0;
	PtOtherInfo.flgProc = 0;

	//PtOtherInfo.ZtType是设置规约组态类型， 
	//如果规约组态类型设置为Fr::CFG::Common，则ConfigTool.exe在进行该规约组态时会出现通用的组态界面，具体组态界面的方式根据pCfgDef定义
	//如果规约无需组态，则应设置： PtOtherInfo.ZtType = Fr::CFG::NONE; 则下面43-48行代码要被删除。可参见项目s_example的GetProtocolIdentify使用
	PtOtherInfo.ZtType		  =  Fr::CFG::Common;  //规约的组态方式被设置成Fr::CFG::Common,表示PtOtherInfo.pCommonCfgDef有效
	PtOtherInfo.pCommonCfgDef = new CCommonCfgDef(1, 1);	//有1种通用的组态数据,每种组态数据均以表、字段方式存在
															//配置参数的版本号是1，版本号是为便于规约将来升级组态参数结构
	if (PtOtherInfo.flgCfg & PTOTHERINFO::CBitEnglish)		//判断是英文版
		SetCfgDef((CCommonCfgDef*)PtOtherInfo.pCommonCfgDef, TRUE); //定义组态参数的界面操作对象，给ConfigTool.exe用
	else
		SetCfgDef((CCommonCfgDef*)PtOtherInfo.pCommonCfgDef, FALSE); //定义组态参数的界面操作对象，给ConfigTool.exe用

	PtOtherInfo.Timer = 200;   //缺省为每200ms收发一次报文，根据实际需要，通常取值5~10000ms

	//设置规约最大容量,便于组态时对数量进行限制，数量根据实际需要
	PtOtherInfo.MaxYc = 1000;
	PtOtherInfo.MaxYx = 1000;
	PtOtherInfo.MaxYm = 1000; 
	PtOtherInfo.MaxYk = 1000;
	PtOtherInfo.MaxYt = 1000;

	if (PtOtherInfo.flgCfg & PTOTHERINFO::CBitEnglish)
		return dscProtocol_en; //返回英文的规约描述，用于ConfigTool这种显示
	else
		return dscProtocol;	//返回中文的规约描述，用于ConfigTool这种显示
}
