#include "VersionInfo.h"
VersionInfo::VersionInfo()
{
	this->fileLength=0;
}
long VersionInfo::getFileLength()
{
	return this->fileLength;
}
void VersionInfo::setFileLength(long fileLength)
{
	this->fileLength=fileLength;
}
const char* VersionInfo::getName()
{
	return this->name.data();
}
void VersionInfo::setName(const char* name)
{
	this->name=name;
}
const char* VersionInfo::getPath()
{
    return this->path.data();
	
}
void VersionInfo::setPath(const char* path)
{
	this->path = path;
}
void VersionInfo::setMd5(string md5)
{
	this->md5=md5;
}
string VersionInfo::getMd5()
{
	return this->md5;
}
void VersionInfo::setResPath(string respath)
{
	this->respath=respath;
}
string VersionInfo::getRespath()
{
	return this->respath;
}
void VersionInfo::setFullpath(string fullpath)
{
	this->fullpath=fullpath;
}
string VersionInfo::getFullpath()
{
	return this->fullpath;
}
	
