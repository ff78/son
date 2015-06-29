#include "gameplay_ctrl_fun_proc.h"
#include "Game_Interface/event_define.h"
#ifdef GAME_SERVER
#include "game_interface/game_data_exchange.h"
#endif
#include "Game_Interface/game_event_response.h"
#include "Game_Interface/game_event_mgr.h"
#include "Game_Interface/game_element.h"
#include "gameplay_ctrl_event_proc.h"


gameplay_ctrl_func_proc* gameplay_ctrl_func_proc::m_pInstance = 0;

gameplay_ctrl_func_proc::gameplay_ctrl_func_proc(void)
{
}

gameplay_ctrl_func_proc::~gameplay_ctrl_func_proc(void)
{
	if( m_pInstance )
		delete m_pInstance;
}

gameplay_ctrl_func_proc* gameplay_ctrl_func_proc::instance(void)
{
	if( NULL == m_pInstance )
	{
		m_pInstance = new gameplay_ctrl_func_proc;
	}		
	return m_pInstance;
}

bool gameplay_ctrl_func_proc::gameplayer_ctrl_fun_quest_bind( Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if(para.size() < 3 )
		return false;
	int p_role_id = (int)para[0];
	int p_quest_id = (int)para[1];
	uint p_act_id = (int)para[2];
	

    Game_Logic::Game_Event event;
	event.set_char_type( Game_Logic::Game_Event::EVENT_TYPE_PLAYER );
    event.set_char_id ( p_role_id );
    event.set_event_owner_type( Game_Logic::Game_Event::EVENT_TYPE_ACTIVITY );
    event.set_event_owner_id (p_act_id);
    event.set_event_active_type ( Game_Logic::Game_Event::EVENT_TYPE_QUEST_COMPLETE );
    event.set_event_active_id ( p_quest_id);
    
	Game_Logic::Game_Event_Mgr::instance()->reg_event("questcomplete",
                                         gameplay_ctrl_event_proc::add_rec_count,
                                         event);
	return true;
}
bool gameplay_ctrl_func_proc::gameplayer_ctrl_fun_ring_quest_bind( Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if(para.size() < 3 )
		return false;
	int p_role_id = (int)para[0];
	int p_quest_id = (int)para[1];
	uint p_act_id = (int)para[2];
	

    Game_Logic::Game_Event event;
	event.set_char_type( Game_Logic::Game_Event::EVENT_TYPE_PLAYER );
    event.set_char_id ( p_role_id );
    event.set_event_owner_type( Game_Logic::Game_Event::EVENT_TYPE_ACTIVITY );
    event.set_event_owner_id (p_act_id);
    event.set_event_active_type ( Game_Logic::Game_Event::EVENT_TYPE_RING_QUEST_COMPLETE );
    event.set_event_active_id ( p_quest_id);
    
	Game_Logic::Game_Event_Mgr::instance()->reg_event("ringquestcomplete",
                                         gameplay_ctrl_event_proc::add_rec_count,
                                         event);
	return true;
}

 bool gameplay_ctrl_func_proc::gameplayer_ctrl_fun_item_bind( Game_Logic::Game_Interface& gm_interface)
 {
	vector<uint64> para;
	gm_interface.get_para(para);
	if(para.size() < 3 )
		return false;
	int p_role_id = (int)para[0];
	int p_item_id = (int)para[1];
	uint p_act_id = (int)para[2];
	

    Game_Logic::Game_Event event;
	event.set_char_type( Game_Logic::Game_Event::EVENT_TYPE_PLAYER );
    event.set_char_id ( p_role_id );
    event.set_event_owner_type( Game_Logic::Game_Event::EVENT_TYPE_ACTIVITY );
    event.set_event_owner_id (p_act_id);
    event.set_event_active_type ( Game_Logic::Game_Event::EVENT_TYPE_RING_ITEM_USED );
    event.set_event_active_id ( p_item_id );
    
	Game_Logic::Game_Event_Mgr::instance()->reg_event("itemused",
                                         gameplay_ctrl_event_proc::add_rec_count,
                                         event);
	return true;
 }

 bool gameplay_ctrl_func_proc::gameplayer_ctrl_fun_daily_reward_bind( Game_Logic::Game_Interface& gm_interface )
 {
	 vector<uint64> para;
	 gm_interface.get_para(para);
	 if(para.size() < 3 )
		 return false;
	 int p_role_id = (int)para[0];
	 int p_award_id = (int)para[1];
	 uint p_act_id = (int)para[2];


	 Game_Logic::Game_Event event;
	 event.set_char_type( Game_Logic::Game_Event::EVENT_TYPE_PLAYER );
	 event.set_char_id ( p_role_id );
	 event.set_event_owner_type( Game_Logic::Game_Event::EVENT_TYPE_ACTIVITY );
	 event.set_event_owner_id (p_act_id);
	 event.set_event_active_type ( Game_Logic::Game_Event::EVENT_TYPE_DAILY_REWARD );
	 event.set_event_active_id ( p_award_id );

	 Game_Logic::Game_Event_Mgr::instance()->reg_event("getdailyreward", gameplay_ctrl_event_proc::add_rec_count, event);
	 return true;	
 }
