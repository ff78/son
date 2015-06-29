#pragma once

#include <string>
#include "Character.h"

#define  MAX_SHOP_COUNT    3      // NPC拥有商店的个数

namespace Game_Data
{
	class CommonNpcConfig;
	class CommonNpc : public Character
	{
	public:
		CommonNpc(void);
		~CommonNpc(void);
	public:
		virtual void init_attr_data(int static_id, int level);
	private:
		CommonNpcConfig* m_common_npc_config;
	};
}