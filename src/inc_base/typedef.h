#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _WINDOWS
#include <unistd.h>

	typedef unsigned long ULONG;
	typedef ULONG *PULONG;
	typedef unsigned short USHORT;
	typedef USHORT *PUSHORT;
	typedef unsigned char UCHAR;
	typedef UCHAR *PUCHAR;
	typedef char *PSZ;

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef UNULL
#ifdef __cplusplus
#define UNULL    (~0)
#else
#define UNULL    ((void *)(~0))
#endif
#endif
#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

	typedef long                LONG;
	typedef unsigned int        DWORD;
	typedef unsigned char       BYTE;
	typedef unsigned short      WORD;
	typedef int		    BOOL;
	typedef float               FLOAT;
	typedef FLOAT               *PFLOAT;

	typedef int                 INT;
	typedef unsigned int        UINT;
	typedef unsigned int        *PUINT;


	typedef void * HANDLE;
	typedef const void * LPVOID;
	typedef const char * LPCSTR;
	typedef const char * LPCTSTR;

	typedef int	shm_t;

#else

#ifdef DNET_NT  
	//0 for dnet compile
#ifndef _WINSOCKAPI_           // 没有包含winsock.h
#define _WINSOCKAPI_           // 避免再包含winsock.h
#ifndef _WINSOCK2API_      // 没有包含winsock2.h
#define _WINSOCK2API_      // 避免再包含winsock2.h
#include <winsock2.h>
	//#pragma comment(lib, "ws32_2.lib")
#endif

#endif


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else 

#include <winsock2.h>
#include <windows.h>

#endif

	//typedef unsigned int   pid_t;
	typedef int		key_t;
	typedef HANDLE	sem_t;
	typedef HANDLE	shm_t;

#endif

#ifdef _ALPHA
	typedef int	socklen_t;
#endif

#ifdef MINMAX

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#endif  /* MINMAX */

#ifndef _WINDOWS
#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))
#endif


	enum { NS_LOW_ENDIAN, NS_HIGH_ENDIAN };

	static int get_byte_endian()
	{
		int i = 1;
		if(*(BYTE *)&i == 1)
			return NS_LOW_ENDIAN;
		else
			return NS_HIGH_ENDIAN;
	}

	const int NS_BYTE_ENDIAN = get_byte_endian();


#ifdef __cplusplus
}
#endif

#ifndef ASSIGN_MISALIGN
template<class T>
inline void assign_misalign(T& a, T& b) {memcpy(&(a), &(b), sizeof(T));}

template<class T>
inline void assign_misalign(T& a, T* b) {memcpy(&(a), b, sizeof(T));}

template<class T>
inline void assign_misalign(T* a, T& b) {memcpy(a, &(b), sizeof(T));}

template<class T>
inline void assign_misalign(T* a, T* b) {memcpy(a, b, sizeof(T));}
#define ASSIGN_MISALIGN
#endif


#ifndef ASSIGN_HTOL
template<class T>
inline void assign_htol(T& a, T& b) {for(int i = 0; i < sizeof(T); i++){((BYTE *)&a)[i] = ((BYTE *)&b)[sizeof(T)-i-1];};}

template<class T>
inline void assign_htol(T& a, T* b) {for(int i = 0; i < sizeof(T); i++){((BYTE *)&a)[i] = ((BYTE *)b)[sizeof(T)-i-1];};}

template<class T>
inline void assign_htol(T* a, T& b) {for(int i = 0; i < sizeof(T); i++){((BYTE *)a)[i] = ((BYTE *)&b)[sizeof(T)-i-1];};}

template<class T>
inline void assign_htol(T* a, T* b) {for(int i = 0; i < sizeof(T); i++){((BYTE *)a)[i] = ((BYTE *)b)[sizeof(T)-i-1];};}

template<class T>
inline void assign_htol(T& a) {\
BYTE k;\
for(int i = 0; i < sizeof(T)/2; i++){\
k = ((BYTE *)&a)[i];\
((BYTE *)&a)[i] = ((BYTE *)&a)[sizeof(T)-i-1];\
((BYTE *)&a)[sizeof(T)-i-1] = k;\
};\
}

template<class T>
inline void assign_htol(T* a) {\
BYTE k;\
for(int i = 0; i < sizeof(T)/2; i++){\
k = ((BYTE *)a)[i];\
((BYTE *)a)[i] = ((BYTE *)a)[sizeof(T)-i-1];\
((BYTE *)a)[sizeof(T)-i-1] = k;\
};\
}

inline void assign_htol(void* a, int len) {\
BYTE k;\
for(int i = 0; i < len/2; i++){\
k = ((BYTE *)a)[i];\
((BYTE *)a)[i] = ((BYTE *)a)[len-i-1];\
((BYTE *)a)[len-i-1] = k;\
};\
}
#define ASSIGN_HTOL
#endif

#ifndef ASSIGN_LOW_ENDIAN
#define assign_l(a, b) {if(NS_BYTE_ENDIAN == NS_LOW_ENDIAN) assign_misalign(a, b); else assign_htol(a, b);}
#define ASSIGN_LOW_ENDIAN
#endif

#ifndef ASSIGN_HIGH_ENDIAN
#define assign_h(a, b) {if(NS_BYTE_ENDIAN == NS_HIGH_ENDIAN) assign_misalign(a, b); else assign_htol(a, b);}
#define ASSIGN_HIGH_ENDIAN
#endif


#ifndef STRING_COPY
inline BOOL string_copy(char *dest, const char *src, int len){
	if(!dest || !src || len <= 0)
		return FALSE;

#ifndef _WINDOWS
	strncpy(dest, src, len-1);
#else

#if _MSC_VER < 1300 // for vc6 no strncpy_s
	strncpy(dest, src, len-1);

#else
	strncpy_s(dest, len-1, src, len-1);

#endif

#endif

	dest[len-1] = 0;
	return TRUE;
}
#define STRING_COPY
#endif

#ifndef _WINDOWS
inline void Sleep(int secs)
{
	usleep(secs*1000);
}

inline char * strupr(char * str)
{
	if(str == NULL)
		return NULL;
	char *p = str;   
	while(*str){
		if ((*str >= 'a')&&(*str <= 'z'))
			*str -= ('a' - 'A');
		//*str = toupper(*str); 
		str++;   
	}   
	return p;  
}

#endif

#endif /* _TYPEDEF_H_ */
