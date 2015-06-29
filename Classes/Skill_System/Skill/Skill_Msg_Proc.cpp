
#include "Network_Common/NetManager.h"
#include "Skill_System/Skill/Skill_Logic.h"
#include "Network_Common/message.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Skill_Msg_Proc.h"
#include "Item_System/Item_Desc_Config_Mgr.h"

#include "Common/GameDefine.h"

Skill_Msg_Proc* Skill_Msg_Proc::instance_ = 0;
Skill_Msg_Proc::Skill_Msg_Proc()
{

}

Skill_Msg_Proc::~Skill_Msg_Proc()
{

}

Skill_Msg_Proc* Skill_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Skill_Msg_Proc;

    return instance_;
}

bool Skill_Msg_Proc::send_load_skill(Game_Logic::Game_Interface& gm_interface)
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    if (player->get_skill_size() > 0)
    {
        return false;
    }
    
	vector<uint64> para;
	gm_interface.get_para(para);
	if( para.size() < 1)
	{
		return false;
	}

	int character_id     = (int)para[0];

    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CS_LOAD_SKILL << character_id;
    CNetManager::GetMe()->send_msg( body_ms );

    cout << "load skill request!----------------------------------"<< endl;
    return true;
}

bool Skill_Msg_Proc::send_uplevel_skill(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
    {
        return false;
    }

    int skill_id     = (int)para[0];
	int character_id = (int)para[1];

	char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
	body_ms << CS_UPLEVEL_SKILL << skill_id << character_id;

    CNetManager::GetMe()->send_msg( body_ms );
	return true;
}

bool Skill_Msg_Proc::on_load_skill(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    if (player->get_skill_size() > 0)
    {
        return false;
    }
     

	int skill_count = 0;
    body_ms >> skill_count;

    int character_id = 0;
    Character* character = NULL;
	for (int i = 0; i < skill_count; ++i)
	{
		Character_Skill skill;
        memset(&skill,0,sizeof(Character_Skill));

        body_ms >> character_id;
		body_ms >> skill.skill_id;

        Character* character = CHARACTER_MGR::instance()->get_character(character_id);
        if (character)
        {
            character->insert_skill(skill);
        }        
	}
    
	//Game_Logic::Game_Event_Response::instance()->on_update_skill(player_id);
    cout << "load skill finish!----------------------------------"<< endl;

    return true;
}

bool Skill_Msg_Proc::on_uplevel_skill(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id(); 

	int skill_id     = 0;
	int skill_level  = 0;
	int character_id = 0;
	body_ms >> skill_id;
	body_ms >> skill_level;
	body_ms >> character_id;

	Character* self = CHARACTER_MGR::instance()->get_character( character_id );
	if ( NULL == self )
		return false;

	self->set_skill_level(skill_id, skill_level);

    DICTIONARY_CONFIG_MGR::instance()->show_alert(LEVEL_UP_SUCCESS);

	return true;
}

bool Skill_Msg_Proc::on_create_skill(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id(); 

    int skill_count = 0;
    body_ms >> skill_count;

    int character_id = 0;
    Character* character = NULL;
    for (int i = 0; i < skill_count; ++i)
    {
        Character_Skill skill;
        memset(&skill,0,sizeof(Character_Skill));

        body_ms >> character_id;
        body_ms >> skill.skill_id;

        character = CHARACTER_MGR::instance()->get_character( character_id );
        if (character)
        {
            character->insert_skill(skill);
        }
    }

    return true;
}