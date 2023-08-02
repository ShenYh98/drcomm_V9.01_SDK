#ifndef _JSON_LIB_H_
#define _JSON_LIB_H_

#include <stdlib.h>
#include "typedefs.h"

#ifdef _WINDOWS
#	ifdef JSONLIB_EXPORTS
#		define JSONLIB_API __declspec(dllexport)
#	else
#		define JSONLIB_API __declspec(dllimport)
#	endif

#	ifndef JSONLIB_EXPORTS
#		pragma comment(lib,"jsonLib.lib")
#		pragma message("Automatically linking with jsonLib.dll")
#	endif
#else
#	define JSONLIB_API
#endif

/* The JNode structure: */
struct JNode {
	struct JNode* next,*prev;	/* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
	struct JNode* child;		/* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */

	int type;					/* The type of the item, as above. */

	char* valuestring;			/* The item's string, if type==DT_String */
	int valueint;				/* The item's number, if type==DT_Number */
	double valuedouble;			/* The item's number, if type==DT_Number */

	char* string;				/* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
};

class JSONLIB_API CJson{
	/* JNode Types: */
public:
	CJson(){};
	~CJson(){};

	static void  JDelete(JNode* c);
	static JNode* Parse(const char* value);  //解析完创建的对象最后要删除 delete out
	static char* Print(JNode* item, int fmt=0);  //最后要释放返回的字符串.delete[] out
	static char* PrintBuffered(JNode* item,int prebuffer,int fmt); //最后要释放返回的字符串.delete[] out

	static int	  GetArraySize(JNode* array);  //得到数组成员数量
	static JNode* GetArrayItem(JNode* array,int item);
	static JNode* GetObjectItem(JNode* object,const char* string);

	//解析错误时，返回错误的字符串
	static const char*  GetErrorPtr(void);

public:
	/* These calls create a JNode item of the appropriate type. */
	static JNode* CreateNull(void);
	static JNode* CreateTrue(void);
	static JNode* CreateFalse(void);
	static JNode* CreateBool(int b);
	static JNode* CreateNumber(double num);
	static JNode* CreateString(const char* string);
	static JNode* CreateArray(void);
	static JNode* CreateObject(void);

	static JNode* CreateIntArray(const int *numbers,int count);
	static JNode* CreateFloatArray(const float *numbers,int count);
	static JNode* CreateDoubleArray(const double *numbers,int count);
	static JNode* CreateStringArray(const char* *strings,int count);

	static void  AddItemToArray(JNode* array, JNode* item);
	static void  AddItemToObject(JNode* object,const char* string,JNode* item);
	static void  AddItemToObjectCS(JNode* object,const char* string,JNode* item);  //针对条目值的字符串是常量
	/* 添加条目项的索引*/
	static void  AddItemReferenceToArray(JNode* array, JNode* item);
	static void  AddItemReferenceToObject(JNode* object,const char* string,JNode* item);

	static JNode* DetachItemFromArray(JNode* array,int which);
	static void  DeleteItemFromArray(JNode* array,int which);
	static JNode* DetachItemFromObject(JNode* object,const char* string);
	static void  DeleteItemFromObject(JNode* object,const char* string);
		
	static void  InsertItemInArray(JNode* array,int which,JNode* newitem);	/* Shifts pre-existing items to the right. */
	static void  ReplaceItemInArray(JNode* array,int which,JNode* newitem);
	static void  ReplaceItemInObject(JNode* object,const char* string,JNode* newitem);

	static JNode* Duplicate(JNode* item,int recurse);  //复制节点，不包括这个节点的上一个和下一个对象指针

	static JNode* ParseWithOpts(const char* value,const char* *return_parse_end,int require_null_terminated);

	static void  Minify(char* json);  //精简JSON字符串，可删除不必要的字符

	static void AddNullToObject(JNode* object,const char* name);
	static void AddTrueToObject(JNode* object,const char* name);
	static void AddFalseToObject(JNode* object,const char* name);
	static void AddBoolToObject(JNode* object,const char* name,int b);
	static void AddNumberToObject(JNode* object,const char* name, double n);
	static void AddStringToObject(JNode* object,const char* name,char*  s);

	static void SetIntValue(JNode* object,int val);
	static void SetNumberValue(JNode* object,double val);

	static UINT32	GetJsonObjectItemUINT32Value(JNode* item, const char* name, const UINT32 iDefault = 0);
	static int		GetJsonObjectItemIntValue(JNode* item, const char* name, const int iDefault = 0);
	static double	GetJsonObjectItemFloatValue(JNode* item, const char* name, const double dDefault = 0);
	static char*	GetJsonObjectItemString(JNode* item, const char* name, char *szDefault=NULL);

};

#endif
