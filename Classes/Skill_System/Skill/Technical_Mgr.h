/* -------------------------------------------------------------------------
//	文件名		：	TechnicalMgr.h
//	功能描述	：	招式静态数据管理类
// -----------------------------------------------------------------------*/

#pragma once

#include <map>
#include <string>
#include <list>
#include <vector>
#include "Item_System/Item_Config_Data.h"

using namespace Game_Data;
namespace Game_Mgr
{
	struct Game_Interface;
}

struct Technical_Data
{
	int				technical_id;
	int             quality;
	int             icon_index;
	int             name_index;
	int				desc_index;
	int             charater_type;
	int				learn_base_money;
	int				learn_level_money;
	int				levelup_max;
	int				skill_base;
	int				upgrade_skill_grow;
	int             skill_percent;
	int				upgrade_skill_percent;

	Technical_Data()
	{
		reset();
	}

	~Technical_Data()
	{
		reset();
	}
	
	void reset()
	{
		technical_id = 0;
		quality = 0;
		icon_index = 0;
		name_index = 0;
		desc_index = 0;
		charater_type = 0;
		learn_base_money = 0;
		learn_level_money = 0;
		levelup_max = 0;
		skill_base = 0;
		upgrade_skill_grow = 0;
		skill_percent = 0;
		upgrade_skill_percent = 0;
	}

	void set_skill_list(const item_content& ic){ skill_list = ic; }
	void get_skill_list(item_content& ic){ ic = skill_list; }
	const item_content get_content() const { return skill_list; }

private:
	item_content			skill_list;
};

class Technical_Mgr
{
public:
	Technical_Mgr(void);
	~Technical_Mgr(void);
	int  initialize();
	void cleanup();
public:
	int  load_technical_data();
	void get_character_technical_list(int charater_type, std::list<int> * list);

    static Technical_Mgr* instance();
public:
	Technical_Data* GetTechnicalData(int technical_id);

	void proc_string(const string& content_str, item_content &ic);
private:
	std::map<int, Technical_Data*>			m_mapTechnical;
    static Technical_Mgr* instance_;
};

typedef Technical_Mgr TECHNICAL_MGR;
