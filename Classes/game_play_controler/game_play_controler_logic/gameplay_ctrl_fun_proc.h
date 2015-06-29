#ifndef _GAME_PLAYE_CTRL_FUNC_PROC_H
#define	_GAME_PLAYE_CTRL_FUNC_PROC_H
#include "Game_Interface/common.h"

namespace Game_Logic {
	struct Game_Interface;
}
class gameplay_ctrl_func_proc
{
public:
	gameplay_ctrl_func_proc(void);
	~gameplay_ctrl_func_proc(void);

	static bool gameplayer_ctrl_fun_quest_bind		( Game_Logic::Game_Interface& gm_interface);
	static bool gameplayer_ctrl_fun_ring_quest_bind	( Game_Logic::Game_Interface& gm_interface);
	static bool gameplayer_ctrl_fun_item_bind		( Game_Logic::Game_Interface& gm_interface);
	static bool gameplayer_ctrl_fun_daily_reward_bind( Game_Logic::Game_Interface& gm_interface );
private:
	static gameplay_ctrl_func_proc* m_pInstance;
	static gameplay_ctrl_func_proc* instance(void);
};


#endif

