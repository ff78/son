#ifndef __VERSIONINFO_H__
#define __VERSIONINFO_H__
#include <string>
using namespace std;
class VersionInfo
{
public:
	VersionInfo();
	long getFileLength();
	void setFileLength(long fileLength);
	const char* getName();
	void setName(const char*name);
	const char* getPath();
	void setPath(const char* path);
	void setMd5(string md5);
	string getMd5();
	void setResPath(string respath);
	string getRespath();
	void setFullpath(string fullpath);
	string getFullpath();
private:
	long fileLength;
	string name;
	string path;
	string md5;
	string respath;
	string fullpath;
};
#endif //__VERSIONINFO_H__