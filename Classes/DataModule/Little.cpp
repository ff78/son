#include "Little.h"
#include "../ClientLogic/Utils/GameReader.h"

USING_NS_CC;

using namespace cocostudio;

std::map<int, Job> Little::jobs;
std::map<int, Tip> Little::tips;
std::map<int, Title> Little::titles;
std::map<int, Litle> Little::litles;
std::map<int, Pop> Little::pops;
std::map<int, Help> Little::helps;

void Little::readFile(std::string path)
{
	std::string fn_tips(path + "_tips.json");
	auto doc = GameReader::getDocInstance(fn_tips);
	if (doc->IsArray())
	{
		int size = doc->Size();
		for (int i = 0; i<size; i++) 
		{
			const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
			Tip tip;
			tip.id = DICTOOL->getIntValue_json(dic, "id");
			tip.name = DICTOOL->getStringValue_json(dic, "name");
			tip.content = DICTOOL->getStringValue_json(dic, "content");
			tips[tip.id] = tip;

		}

	}

	std::string title_filename(path + "_titles.json");
	auto title_doc = GameReader::getDocInstance(title_filename);
	if (title_doc->IsArray())
	{
		int size = title_doc->Size();
		for (int i = 0; i < size; i++)
		{
			const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*title_doc), i);
			Title title;
			title.id = DICTOOL->getIntValue_json(dic, "id");
			title.name = DICTOOL->getStringValue_json(dic, "name");
			titles[title.id] = title;

		}

	}

	std::string job_filename(path + "_jobs.json");
	auto job_doc = GameReader::getDocInstance(job_filename);
	if (job_doc->IsArray())
	{
		int size = job_doc->Size();
		for (int i = 0; i < size; i++)
		{
			const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*job_doc), i);
			Job job;
			job.id = DICTOOL->getIntValue_json(dic, "id");
			job.name = DICTOOL->getStringValue_json(dic, "name");
			jobs[job.id] = job;

		}

	}

	std::string litle_filename(path + "_little.json");
	auto little_doc = GameReader::getDocInstance(litle_filename);
	if (little_doc->IsArray())
	{
		int size = little_doc->Size();
		for (int i = 0; i < size; i++)
		{
			const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*little_doc), i);
			Litle litle;
			litle.id = DICTOOL->getIntValue_json(dic, "id");
			litle.name = DICTOOL->getStringValue_json(dic, "name");
			litles[litle.id] = litle;

		}

	}
	
	std::string pop_filename(path + "_pop.json");
	auto pop_doc = GameReader::getDocInstance(pop_filename);
	if (pop_doc->IsArray())
	{
		int size = pop_doc->Size();
		for (int i = 0; i < size; i++)
		{
			const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*pop_doc), i);
			Pop pop;
			pop.id = DICTOOL->getIntValue_json(dic, "id");
			pop.name = DICTOOL->getStringValue_json(dic, "name");
			pops[pop.id] = pop;

		}

	}

	std::string help_filename(path + "_helps.json");
	auto help_doc = GameReader::getDocInstance(help_filename);
	if (help_doc->IsArray())
	{
		int size = help_doc->Size();
		for (int i = 0; i < size; i++)
		{
			const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*help_doc), i);
			Help help;
			help.id = DICTOOL->getIntValue_json(dic, "id");
			help.name = DICTOOL->getStringValue_json(dic, "name");
			helps[help.id] = help;

		}

	}

}