
//-------------------------------------------------------------------- 
// �ļ���:		Tool.h 
// ��  ��:		���ù��ߺ���
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


//�����������
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
	//���Ӵ���
	void Reset(const SeedType p_Seed = 0);

	//Returns an unsigned integer from 0..RandomMax
	//0~RandMax unsigned int �����
	uint64 RandUInt(void);

	//Returns a double in [0.0, 1.0]
	//����0.0~1.0֮���˫���ȸ���
	double RandDouble(void);

	static int  GetRand(int nStart, int nEnd);

	// �ٷֱȼ��ʴ��� ����percentΪ0~100������
	static bool GetRandPercent(int percent);

};

//������
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
	// windows�·�������������dump�ļ�
	//extern int Exception(EXCEPTION_POINTERS* ExceptionInfo);
#endif

#ifdef YN_WINDOWS
// ���أ�0��scale-1�����������scale���32768
extern int RandomInt(int scale);
// ���أ�0.0��scale�����������
extern float RandomFloat(float scale);
// ���أ�0��scale-1�����������scale���32768 * 32768
extern int RandomBigInt(int scale);
#endif
// ���� (nLow��nHigh), ��Χ���
extern int RandomRangeInit(int nLow, int nHigh);

// ����ת��Ϊ�ַ���
extern std::string IntAsString(int value);
// ������ת��Ϊ�ַ���
extern std::string FloatAsString(float value, int decimals = 0);

// �ַ���ת��Ϊ����
extern int StringAsInt(const char * value);
// �ַ���ת��Ϊ������
extern float StringAsFloat(const char * value);
// ȡ�ÿո�ָ���Ӵ���index��0��ʼ����ʾ�ڼ���
extern std::string Parse(const char * str, const char* parse_str, size_t index);


// �ַ���ת��Ϊ����
extern int StringAsInt(const std::string & value);
// �ַ���ת��Ϊ������
extern float StringAsFloat(const std::string & value);

// ȡ�߶εķ���
extern float LineOrient(float x1, float z1, float x2, float z2);
// ȡ����֮��ľ���
extern float Get2DotDistance(float x1, float z1, float x2, float z2);

extern int GetCurTime(int ct = 0);


#endif