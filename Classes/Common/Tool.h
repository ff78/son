
//-------------------------------------------------------------------- 
// 文件名:		Tool.h 
// 内  容:		常用工具函数
//--------------------------------------------------------------------

#ifndef _TOOL_H
#define _TOOL_H

#include "Game_Interface/common.h"

#include <string>

#if defined(YN_WINDOWS)
	#pragma warning ( disable : 4786 )
	//#include <Windows.h>
    //#include <dbghelp.h>
    //#pragma comment(lib, "dbghelp.lib")
#elif defined(YN_LINUX)
#endif

using namespace std;

#if defined(YN_WINDOWS)
	#define CATCHER_BEGIN __try {
    #define CATCHER_END  } __except (Exception(GetExceptionInformation())) {}
#endif


//随机数生成类
class RandGen
{
public:
	typedef unsigned long SeedType;
private:
	SeedType m_Seed[3];
	static const SeedType Max32BitLong = 0xFFFFFFFFLU;
public:
	static const SeedType RandomMax = Max32BitLong;
	RandGen(const SeedType p_Seed = 0);

	//ReSeed the random number generator
	//种子处理
	void Reset(const SeedType p_Seed = 0);

	//Returns an unsigned integer from 0..RandomMax
	//0~RandMax unsigned int 随机数
	uint64 RandUInt(void);

	//Returns a double in [0.0, 1.0]
	//返回0.0~1.0之间的双精度浮点
	double RandDouble(void);

	static int  GetRand(int nStart, int nEnd);

	// 百分比几率触发 参数percent为0~100的整型
	static bool GetRandPercent(int percent);

};

//共享锁
#if defined(YN_WINDOWS)
class MyLock
{
	//CRITICAL_SECTION m_Lock ;
public :
	//MyLock( ){ InitializeCriticalSection(&m_Lock); } ;
	//~MyLock( ){ DeleteCriticalSection(&m_Lock); } ;
	//VOID	Lock( ){ EnterCriticalSection(&m_Lock); } ;
	//VOID	Unlock( ){ LeaveCriticalSection(&m_Lock); } ;
};
#elif defined(YN_LINUX)
class MyLock
{
	pthread_mutex_t 	m_Mutex; 
public :
	MyLock( ){ pthread_mutex_init( &m_Mutex , NULL );} ;
	~MyLock( ){ pthread_mutex_destroy( &m_Mutex) ; } ;
	VOID	Lock( ){ pthread_mutex_lock(&m_Mutex); } ;
	VOID	Unlock( ){ pthread_mutex_unlock(&m_Mutex); } ;
};
#endif

#if defined(YN_WINDOWS)
	// windows下服务器崩溃产生dump文件
	//extern int Exception(EXCEPTION_POINTERS* ExceptionInfo);
#endif

#ifdef YN_WINDOWS
// 返回（0到scale-1）随机整数，scale最大32768
extern int RandomInt(int scale);
// 返回（0.0到scale）随机浮点数
extern float RandomFloat(float scale);
// 返回（0到scale-1）随机整数，scale最大32768 * 32768
extern int RandomBigInt(int scale);
#endif
// 返回 (nLow到nHigh), 范围随机
extern int RandomRangeInit(int nLow, int nHigh);

// 整数转换为字符串
extern std::string IntAsString(int value);
// 浮点数转换为字符串
extern std::string FloatAsString(float value, int decimals = 0);

// 字符串转换为整数
extern int StringAsInt(const char * value);
// 字符串转换为浮点数
extern float StringAsFloat(const char * value);
// 取用空格分割的子串，index从0开始，表示第几个
extern std::string Parse(const char * str, const char* parse_str, size_t index);


// 字符串转换为整数
extern int StringAsInt(const std::string & value);
// 字符串转换为浮点数
extern float StringAsFloat(const std::string & value);

// 取线段的方向
extern float LineOrient(float x1, float z1, float x2, float z2);
// 取两点之间的距离
extern float Get2DotDistance(float x1, float z1, float x2, float z2);

extern int GetCurTime(int ct = 0);


#endif