
#include "Skill_System/Impact/Impact_Common.h"
#include "CommonNpc_Config_Mgr.h"
#include "CommonNpc_Config_Data.h"
#include "CommonNpc.h"

namespace Game_Data
{
	CommonNpc::CommonNpc(void)
	{
		m_common_npc_config = NULL;
	}

	CommonNpc::~CommonNpc(void)
	{
		
	}

	void CommonNpc::init_attr_data(int static_id, int level)
	{
		set_static_character_id(static_id);
		m_common_npc_config = CommonNpc_Config_MGR::instance()->get_commomnpc_by_id(static_id);
	}
}