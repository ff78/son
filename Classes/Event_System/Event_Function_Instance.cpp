#include "Event_Function_Instance.h"
#include "Game_Interface/event_define.h"
#include "event_system_logic.h"

#include "Game_Interface/game_event_mgr.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Common/Tool.h"
#include "Character_System/Character.h"
#include "Character_System/Character_Mgr.h"
using namespace Game_Data;
#ifdef GAME_CLIENT
//#include "UI/Actor.h"
//#include "UI/Trigger_Sprite.h"
//#include "AI_System/Game_Utils.h"
#include "cocos2d.h"
//#include "UI/GameUI_Layer.h"
//#include "AI_System/Game_Utils.h"
//#include "UI/Unique_Skill.h"
//using namespace UI;
USING_NS_CC;
#endif
#ifdef GAME_SERVER
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Item_System/Item_Mgr_Sv.h"
#include "game_interface/game_data_exchange.h"
#endif


#include "Game_Interface/game_content_interface.h"

Event_Function_Instance::Event_Function_Instance()
{

}
Event_Function_Instance* Event_Function_Instance::instance_=0;
Event_Function_Instance* Event_Function_Instance::sharedInstance()
{
    if(instance_==0)
    {
        instance_=new Event_Function_Instance();
    }
    return instance_;
}

#ifdef GAME_CLIENT
bool Event_Function_Instance::dropsomething(Game_Logic::Game_Interface& gm_interface)
{



    //掉落宝箱
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 8)
        return false;
    int event_id=(int)para[0];
    int item_id = (int)para[1];
    int rate = (int)para[2];
    float posX=(float)para[6];
    float posY=(float)para[7];
    /*if(RandGen::GetRandPercent(rate))
    {
        int id;
        Game_Utils::instance()->create_trigger_sprite(item_id,id,posX,posY);//2901箱子2902团子2903篮子
        UI::Trigger_Sprite* ts=Game_Utils::instance()->get_trigger_sprite(id);
        ts->set_static_id(item_id);
    }*/

    return true;
}
#endif
bool Event_Function_Instance::awardgold(Game_Logic::Game_Interface& gm_interface)
{
#ifdef GAME_SERVER

    /*
    马军(马军) 19:37:10//通过id获得副本的等级
    Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute","condition","level",para);
    if ( para.size() >= 1)
    {
    char txt[256];
    sprintf( txt, "%d", para[0]);
    m_pLabSuggestLevel->setText(txt);
    }
    马军(马军) 19:47:55
    INSTANCE_DATA_MGR::instance()->get_current_instance_id();//获得副本的ID
    */
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 5)
        return false;
    //int goldcount=(int)para[1];
    //int factor=(int)para[2];
    int player_id=(int)para[5];
    //there need instance level
    //int instancelevel=6;
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if(player)
    {
        //这里待确定
        //int addgold=(instancelevel*25+150)*factor;
        // player->change_gold(goldcount);
    }

#endif
    /*
    #ifdef GAME_CLIENT
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2)
    return false;
    int gold_count=(int)para[1];
    //发送加钱的消息
    std::vector<uint64> paras;
    para.push_back(gold_count);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("send_player_instance_obtain_gold", paras);
    #endif
    */
    return true;
}
//奖励生命值
#ifdef GAME_CLIENT
bool Event_Function_Instance::awardhp(Game_Logic::Game_Interface& gm_interface)
{
    /*
    #ifdef GAME_SERVER
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 5)
    return false;
    int lifepercent=(int)para[1];
    int player_id=(int)para[4];
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if(player)
    {

    //添加血量
    int maxhp=player->get_character_max_hp();
    int addcount=maxhp*lifepercent/100;
    int currenthp=player->get_character_cur_hp();
    if(addcount+currenthp>=maxhp)
    {
    player->set_character_cur_hp(maxhp);
    }
    else
    {
    player->set_character_cur_hp(addcount+currenthp);
    }

    }

    #endif
    */

    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 5)
        return false;
    int lifepercent=(int)para[1];


    /*Actor * ac=Game_Utils::instance()->get_primary_actor();
    Character * player=Character_Mgr::instance()->get_character(ac->sprite_id());
    if(player)
    {

        //添加血量
        int maxhp=player->get_character_max_hp();
        int addcount=maxhp*lifepercent/100;
        int currenthp=player->get_character_cur_hp();
        if(addcount+currenthp>=maxhp)
        {
            player->set_character_cur_hp(maxhp);
        }
        else
        {
            player->set_character_cur_hp(addcount+currenthp);
        }
        //更新血量
        int percent=player->get_character_cur_hp()*100/maxhp;
        Game_Utils::instance()->update_actor_hp(ac->sprite_id(),percent);
    }*/



    return true;
}

//奖励怒气

bool Event_Function_Instance::awardmp(Game_Logic::Game_Interface& gm_interface)
{
    /*
    #ifdef GAME_SERVER
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 5)
    return false;
    int mppercent=(int)para[1];
    int player_id=(int)para[4];
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if(player)
    {

    //添加怒气
    int maxmp=player->get_character_max_mp();
    int currentmp=player->get_character_cur_mp();
    int addcount=maxmp*mppercent/100;
    if(currentmp+addcount>=maxmp)
    {
    player->set_character_cur_mp(maxmp);
    }
    else
    {
    player->set_character_cur_mp(currentmp+addcount);
    }
    }

    #endif
    */


    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 5)
        return false;
    int mppercent=(int)para[1];
    /*Actor * ac=Game_Utils::instance()->get_primary_actor();
    Character * player=Character_Mgr::instance()->get_character(ac->sprite_id());
    if(player)
    {
        //添加怒气
        int maxmp=player->get_character_max_mp();
        int addcount=maxmp*mppercent/100;
        Unique_Skill::get_instance()->calculateAngryNum(Unique_Skill::GAIN_BY_DROP,player->get_database_character_id(),addcount);
    }*/

    return true;
}
#endif
bool Event_Function_Instance::collided_something(Game_Logic::Game_Interface& gm_interface)
{

    vector<uint64>  para;
    gm_interface.get_para(para);
    if( para.size() < 3)
        return false;

    int event_id = (int)para[0];
    int itemid = (int)para[1];
    int player_id=(int)para[2];

    Game_Logic::Game_Event event;
    event.reset();
    event.set_para(para);
    event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
    event.set_char_id( player_id );
    event.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_EVENT_SYSTEM);
    event.set_event_owner_id(event_id);
    event.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_COLLIDED_SOMETHING);
    event.set_event_active_id(itemid);

    Game_Logic::Game_Event_Mgr::instance()->reg_event("collided_something", event_system_logic::proc_monster_die_envent, event);

    return true;
}
bool Event_Function_Instance::useitem(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64>  para;
    gm_interface.get_para(para);
    if( para.size() < 3)
        return false;

    int event_id = (int)para[0];
    int itemid = (int)para[1];//这里是道具的表ID
    int player_id=(int)para[2];

    Game_Logic::Game_Event event;
    event.reset();
    event.set_para(para);
    event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
    event.set_char_id( player_id );
    event.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_EVENT_SYSTEM);
    event.set_event_owner_id(event_id);
    event.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_USEITEM);
    event.set_event_active_id(itemid);

    Game_Logic::Game_Event_Mgr::instance()->reg_event("useitem", event_system_logic::proc_useitem_event, event);

    return true;
}
bool Event_Function_Instance::randomawardone(Game_Logic::Game_Interface& gm_interface)
{
    //do something
#ifdef GAME_CLIENT
    //cocos2d::CCLog("bool Event_Function_Instance::awarditem");
#endif

#ifdef GAME_SERVER
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 7)
        return false;

    int itemCount= (para.size()-4)/2;
    int randitem=RandGen::GetRand(0,itemCount);


    //
    int itemid=(int)para[randitem*2+1];
    int itemcount = (int)para[randitem*2+1+1];
    //int gift_id=(int)para[itemCount*2+2];
    int player_id=(int)para[itemCount*2+2+1];

    //在这里奖励礼包的道具
    ITEM_MGR::instance()->create_item(player_id,itemid,itemcount,1,true);

    return true;
#endif
    return true;
}
bool Event_Function_Instance::awarditem(Game_Logic::Game_Interface& gm_interface)
{
    //do something
#ifdef GAME_CLIENT
    //cocos2d::CCLog("bool Event_Function_Instance::awarditem");
#endif

#ifdef GAME_SERVER
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 7)
        return false;

    int event_id = (int)para[0];
    int reward_base_id = (int)para[1];
    int item_count = (int)para[2];
    int rate = (int)para[3];
    event_id = (int)para[4];
    //int gift_base_id = (int)para[5];
    int player_id = (int)para[6];

    if(RandGen::GetRandPercent(rate))
    {
        //在这里奖励礼包的道具
        ITEM_MGR::instance()->create_item(player_id,reward_base_id,item_count,1);
    }
    return true;
#endif
    return true;
}
bool Event_Function_Instance::monster_die(Game_Logic::Game_Interface& gm_interface)
{

    vector<uint64>  para;
    gm_interface.get_para(para);
    if( para.size() < 3)
        return false;

    int event_id = (int)para[0];
    int monster_id = (int)para[1];
    int player_id=(int)para[2];

    Game_Logic::Game_Event event;
    event.reset();
    event.set_para(para);
    event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
    event.set_char_id( player_id );
    event.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_EVENT_SYSTEM);
    event.set_event_owner_id(event_id);
    event.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_KILLMONSTER);
    event.set_event_active_id(monster_id);

    Game_Logic::Game_Event_Mgr::instance()->reg_event("monster", event_system_logic::proc_monster_die_envent, event);

    return true;

}

bool Event_Function_Instance::on_login(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64>  para;
    gm_interface.get_para(para);
    if( para.size() < 1)
        return false;
    uint player_id = (uint)para[0];
    event_system_logic::sharedInstance()->init_event_system(player_id);
    return true;
}

bool Event_Function_Instance::on_logout(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64>  para;
    gm_interface.get_para(para);
    if( para.size() < 1)
        return false;
    //uint player_id = (uint)para[0];

    return true;
}

bool Event_Function_Instance::award_gold(Game_Logic::Game_Interface& gm_interface)
{

#ifdef GAME_SERVER
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 5)
    {
        return false;
    }

    int event_id = (int)para[0];
    int value = (int)para[1];
    //event_id = (int)para[2];
    //int usable_base_id = (int)para[3];
    int player_id = (int)para[4];
    Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (player)
    {
        player->change_gold(value);
        // save db
        para.clear();
        para.push_back(player_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_gold",para);
    }
    
#endif
    return true;
}

bool Event_Function_Instance::award_token(Game_Logic::Game_Interface& gm_interface)
{

#ifdef GAME_SERVER
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 5)
    {
        return false;
    }

    int event_id = (int)para[0];
    int value = (int)para[1];
    //event_id = (int)para[2];
    //int usable_base_id = (int)para[3];
    int player_id = (int)para[4];
    Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (player)
    {
        player->change_token(value);
        // save db
        para.clear();
        para.push_back(player_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_token",para);
    }

#endif
    return true;
}

bool Event_Function_Instance::award_prestige(Game_Logic::Game_Interface& gm_interface)
{

#ifdef GAME_SERVER
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 5)
    {
        return false;
    }

    int event_id = (int)para[0];
    int value = (int)para[1];
    //event_id = (int)para[2];
    //int usable_base_id = (int)para[3];
    int player_id = (int)para[4];
    Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (player)
    {
        player->change_prestige(value);
        // save db
        para.clear();
        para.push_back(player_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_prestige",para);
    }

#endif
    return true;
}

bool Event_Function_Instance::award_feat(Game_Logic::Game_Interface& gm_interface)
{

#ifdef GAME_SERVER
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 5)
    {
        return false;
    }

    int event_id = (int)para[0];
    //int value = (int)para[1];
    //event_id = (int)para[2];
    //int usable_base_id = (int)para[3];
    int player_id = (int)para[4];
    Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (player)
    {
        //player->change_feat(value);
    }

#endif
    return true;
}

bool Event_Function_Instance::award_energy(Game_Logic::Game_Interface& gm_interface)
{

#ifdef GAME_SERVER
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 5)
    {
        return false;
    }

    int event_id = (int)para[0];
    int value = (int)para[1];
    //event_id = (int)para[2];
    //int usable_base_id = (int)para[3];
    int player_id = (int)para[4];
    Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (player)
    {
        player->change_energy(value);
        // save db
        para.clear();
        para.push_back(player_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_energy",para);
    }

#endif
    return true;
}

bool Event_Function_Instance::award_general_exp(Game_Logic::Game_Interface& gm_interface)
{

#ifdef GAME_SERVER
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 5)
    {
        return false;
    }

    int event_id = (int)para[0];
    int value = (int)para[1];
    //event_id = (int)para[2];
    //int usable_base_id = (int)para[3];
    int player_id = (int)para[4];
    Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (player)
    {
        DeputyGeneral* general = player->get_fight_general();
        if (general)
        {
            general->change_exp(value);
        }
    }

#endif
    return true;
}

bool Event_Function_Instance::award_deputy_general(Game_Logic::Game_Interface& gm_interface)
{

#ifdef GAME_SERVER
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 5)
    {
        return false;
    }

    int event_id = (int)para[0];
    int value = (int)para[1];
    //event_id = (int)para[2];
    //int usable_base_id = (int)para[3];
    int player_id = (int)para[4];
    Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (player)
    {
        Game_Logic::game_data_exchange::instance()->add_deputy_general(player->get_database_character_id(), value);
    }

#endif
    return true;
}