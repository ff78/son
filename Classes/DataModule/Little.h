#ifndef __ssoul__Little__
#define __ssoul__Little__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

struct Job
{
	int id;
	std::string name;

};

struct Tip
{
	int id;
	std::string name;
	std::string content;

};

struct Title
{
	int id;
	std::string name;
};

struct Litle
{
	int id;
	std::string name;
};

struct Pop
{
	int id;
	std::string name;
};

struct Help
{
	int id;
	std::string name;
};

class Little
{
private:

	//CC_SYNTHESIZE(int, id, Id);
	//CC_SYNTHESIZE(std::string, name, Name);
	//CC_SYNTHESIZE(std::string, content, Content);


public:
	static std::map<int, Job> jobs;
	static std::map<int, Tip> tips;
	static std::map<int, Title>titles;
	static std::map<int, Litle>litles;
	static std::map<int, Pop>pops;
	static std::map<int, Help>helps;

	static void readFile(std::string path);

};

#endif /* defined(__Little__) */