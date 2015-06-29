
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include "Inlines.h"
#include "Tool.h"

#define RAND_MAX1 (RAND_MAX + 1)

extern RandGen g_RandGen;

RandGen g_RandGen = RandGen((unsigned)time(NULL));

#if defined(YN_WINDOWS)
//int Exception(EXCEPTION_POINTERS* ExceptionInfo)
//{
	/*WCHAR temp[128];
	char  temp1[128];
	LPCWSTR s_file_name = temp;
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	::sprintf_s(temp1, "DUMP%04d%02d%02d%02d%02d%02d%03d.dmp", 
		tm.wYear, tm.wMonth, tm.wDay, tm.wHour, 
		tm.wMinute, tm.wSecond, tm.wMilliseconds);
	mbstowcs(temp, temp1, 128);
	HANDLE hFile = ::CreateFile(temp, 
		GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		MINIDUMP_EXCEPTION_INFORMATION mei;
		mei.ThreadId = ::GetCurrentThreadId();
		mei.ExceptionPointers = ExceptionInfo;
		mei.ClientPointers = true;
		::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(),
			hFile, MiniDumpNormal, &mei, NULL, NULL);
		::CloseHandle(hFile);
	}*/
	//return EXCEPTION_CONTINUE_SEARCH;
//}
#endif
#ifdef YN_WINDOWS
int RandomInt(int scale)
{

	if ( (scale <= 0) || (scale > RAND_MAX1) )
	{
		return 0;
	}

	return int(float(::rand()) / float(RAND_MAX1) * float(scale));
 
 
}
#endif

int RandomRangeInit(int nLow, int nHigh)
{
	return RandGen::GetRand(nLow, nHigh);
}

#ifdef YN_WINDOWS
float RandomFloat(float scale)
{

	if (scale <= 0.0f)
	{
		return 0.0f;
	}

	return (float(::rand()) / float(RAND_MAX1) * scale);
 
}

int RandomBigInt(int scale)
{

	if ( (scale <= 0) || (scale > (RAND_MAX1 * RAND_MAX1)) )
	{
		return 0;
	}

	return int(float(::rand() * RAND_MAX1 + ::rand())            
		/ float(RAND_MAX1 * RAND_MAX1) * float(scale));
 

}
#endif
#ifdef YN_WINDOWS
std::string IntAsString(int value)
{
	char str[32];

	::sprintf_s(str, "%d", value);

	return std::string(str);
}

std::string FloatAsString(float value, int decimals)
{
	char str[64];

	if (0 == decimals)
	{
		::sprintf_s(str, "%f", double(value));
	}
	else
	{
		switch (decimals)
		{
		case 1:
			::sprintf_s(str, "%.01f", double(value));
			break;
		case 2:
			::sprintf_s(str, "%.02f", double(value));
			break;
		case 3:
			::sprintf_s(str, "%.03f", double(value));
			break;
		case 4:
			::sprintf_s(str, "%.04f", double(value));
			break;
		case 5:
			::sprintf_s(str, "%.05f", double(value));
			break;
		default:
			::sprintf_s(str, "%f", double(value));
			break;
		}
	}

	return std::string(str);
}

int StringAsInt(const char * value)
{
	return ::atoi(value);
}

float StringAsFloat(const char * value)
{
	return (float)::atof(value);
}

std::string Parse(const char * str, const char* parse_str, size_t index)
{
	if ( NULL == str )
	{
		return std::string();
	}

	const size_t SIZE1 = index - 1;

	if ( (SIZE1 < 0) || (SIZE1 >= 32) )
	{
		return std::string();
	}

	char data[1024] = "\0";

	::strcpy(data, str);

	size_t	count = 0;

	char *	tok = ::strtok(data, parse_str);

	while (tok != NULL)
	{
		if (count == SIZE1)
		{
			return std::string(tok);
		}
		count ++;
		tok = ::strtok(NULL, parse_str);
	}

	return std::string();
}

int StringAsInt(const std::string & value)
{
	return StringAsInt(value.c_str());
}

float StringAsFloat(const std::string & value)
{
	return StringAsFloat(value.c_str());
}

std::wstring IntAsWideStr(int value)
{
	wchar_t buf[32];

	::swprintf_s(buf, L"%d", value);

	return std::wstring(buf);
}

std::wstring FloatAsWideStr(float value, int decimals)
{
	wchar_t buf[64];

	if (0 == decimals)
	{
		::swprintf_s(buf, L"%f", double(value));
	}
	else
	{
		switch (decimals)
		{
		case 1:
			::swprintf_s(buf, L"%.01f", double(value));
			break;
		case 2:
			::swprintf_s(buf, L"%.02f", double(value));
			break;
		case 3:
			::swprintf_s(buf, L"%.03f", double(value));
			break;
		case 4:
			::swprintf_s(buf, L"%.04f", double(value));
			break;
		case 5:
			::swprintf_s(buf, L"%.05f", double(value));
			break;
		default:
			::swprintf_s(buf, L"%f", double(value));
			break;
		}
	}

	return std::wstring(buf);
}
#endif
std::string Substr(const char * str, size_t pos, size_t len)
{
	assert(str != NULL);

	if (len == 0)
	{
		return std::string();
	}

	size_t i = pos + len;

	if (i > ::strlen(str))
	{
		return std::string();
	}

	std::string s(str);

	return s.substr(pos, len);
}

std::wstring SubstrW(const wchar_t * str, size_t pos, size_t len)
{
	assert(str != NULL);

	if (len == 0)
	{
		return std::wstring();
	}

	size_t i = pos + len;

	if (i > ::wcslen(str))
	{
		return std::wstring();
	}

	std::wstring s(str);

	return s.substr(pos, len);
}

float LineOrient(float x1, float z1, float x2, float z2)
{
	float sx = x2 - x1;
	float sz = z2 - z1;

	float orient = ::acosf(sz / ::sqrtf(sx * sx + sz * sz));
#ifdef YN_WINDOWS
	if (::_isnan(orient))		
	{
		return 0.0f;
	}
#endif
	if (sx < 0.0f)
	{
		orient = -orient;
	}

	if (orient < 0.0f)
	{
		orient += 2 * 3.141592654f;
	}

	return orient;
}

float Get2DotDistance(float x1, float z1, float x2, float z2)
{
	float sx = x1 - x2;
	float sz = z1 - z2;

	return ::sqrtf(sx * sx + sz * sz);
}

RandGen::RandGen(const SeedType p_Seed /* = 0*/)
{
	Reset(p_Seed);
}

void RandGen::Reset(const SeedType p_Seed /* = 0*/)
{  
	m_Seed[0] = (p_Seed ^ 0xFEA09B9DLU) & 0xFFFFFFFELU;
	m_Seed[0] ^= (((m_Seed[0] << 7) & Max32BitLong) ^ m_Seed[0]) >> 31;
	m_Seed[1] = (p_Seed ^ 0x9C129511LU) & 0xFFFFFFF8LU;
	m_Seed[1] ^= (((m_Seed[1] << 2) & Max32BitLong) ^ m_Seed[1]) >> 29;
	m_Seed[2] = (p_Seed ^ 0x2512CFB8LU) & 0xFFFFFFF0LU;
	m_Seed[2] ^= (((m_Seed[2] << 9) & Max32BitLong) ^ m_Seed[2]) >> 28;
	RandUInt();
}

uint64 RandGen::RandUInt(void)
{
	m_Seed[0] = (((m_Seed[0] & 0xFFFFFFFELU) << 24) & Max32BitLong)
		^ ((m_Seed[0] ^ ((m_Seed[0] << 7) & Max32BitLong)) >> 7);
	m_Seed[1] = (((m_Seed[1] & 0xFFFFFFF8LU) << 7) & Max32BitLong)
		^ ((m_Seed[1] ^ ((m_Seed[1] << 2) & Max32BitLong)) >> 22);
	m_Seed[2] = (((m_Seed[2] & 0xFFFFFFF0LU) << 11) & Max32BitLong)
		^ ((m_Seed[2] ^ ((m_Seed[2] << 9) & Max32BitLong)) >> 17);
	return (m_Seed[0] ^ m_Seed[1] ^ m_Seed[2]);
}

double RandGen::RandDouble(void)
{
	return static_cast<double>(RandUInt())
		/ (static_cast<double>(RandomMax) );
}

int RandGen::GetRand(int nStart, int nEnd)
{
	return (int)((nEnd-nStart)*g_RandGen.RandDouble()) + nStart;
}

bool RandGen::GetRandPercent(int percent)
{
	bool trigger = false;
	if (percent >= 100)
	{
		trigger = true;
	} 
	else if (percent > 0)
	{
		int num = GetRand(0,100);
		if (num < percent)
		{
			trigger = true;
		} 
	}
	
	return trigger;
}


int GetCurTime(int ct)
{
	time_t tt = (time_t)ct;
	return (int)time(&tt);
}
