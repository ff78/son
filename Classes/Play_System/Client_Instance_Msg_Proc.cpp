
#include "Client_Instance_Msg_Proc.h"
#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "Network_Common/message.h"
#include "Network_Common/message_stream.h"
#include "Network_Common/NetManager.h"
#include "Game_Interface/event_define.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_mgr.h"
#include "Game_Interface/game_event_response.h"
#include "Instance_Data_Mgr.h"
#include "Instance_Sweep_Data_Mgr.h"

/*************************************************** dely **************************************************/
#include "ClientLogic/GameScene/ResultLayer.h"
/*************************************************** dely **************************************************/
//#include "Actor_Mgr.h"

#ifdef GAME_CLIENT
#include "Player_Account/Account_Data_Mgr.h"

#include "UI_Interface/UI_MainMenu_Layer.h"
//#include "AI_System/Game_Utils.h"

//#include "Runtime.h"
//#include "Game/Monster_Wave_Cfg_Data_Mgr.h"
//#include "UI_Interface/UI_Settlement_Layer.h"
#include "UI_Interface/CocoStu_UI_Scene_Interface.h"
#endif
#include "Common/Utils.h"

#include "ClientLogic/Utils/GameReader.h"
#define INSTANCE_SCORE_FILE "instance_score.json"
#define ENDLESS_TOWER_SCORE_FILE "endless_score.json"

#include "Character_System/Player_Msg_Proc_Cl.h"

using namespace cocostudio;

Client_Instance_Msg_Proc* Client_Instance_Msg_Proc::instance_ = 0;
Client_Instance_Msg_Proc::Client_Instance_Msg_Proc()
{

}

Client_Instance_Msg_Proc::~Client_Instance_Msg_Proc()
{

}

Client_Instance_Msg_Proc* Client_Instance_Msg_Proc::instance()
{
    if( NULL == instance_ )
        instance_ = new Client_Instance_Msg_Proc;

    return instance_;
}
bool Client_Instance_Msg_Proc::on_player_enter_instance(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// ¥”∑˛ŒÒ∆˜Ω” ’Ω¯»Î∏±±æµƒœ˚œ¢
	CocoStu_UI_Scene_Interface::get_instance()->unlockScreen();
    //CCLog("-------------------->Client_Instance_Msg_Proc::on_player_enter_instance ---to game");
	// 1. ¥¶¿Ìœ˚œ¢ƒ⁄»›
//    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
//    body_ms.set_rd_ptr(sizeof(int));
    int player_id = 0;
    int instance_id = 0;
    int scene_id = 0;
    int time_limit = 0;
    int instance_first = 0;
    int monster_wave = 0;
//    body_ms >> player_id >> instance_id >> scene_id >> time_limit >> instance_first >> monster_wave;
    player_id = Account_Data_Mgr::instance()->get_current_role_id();
    vector<uint64> param;
    param = gm_interface.get_para();
    instance_id = (int)param[0];
    scene_id = (int)param[1];

    vector<uint64> para;
    para.push_back(player_id);
    para.push_back(instance_id);
    para.push_back(scene_id);
    para.push_back(time_limit);
    para.push_back(instance_first);
    para.push_back(monster_wave);

//    int wave_id;
//    for( int i = 0; i < monster_wave; i++ )
//    {
//        body_ms >> wave_id;
//        para.push_back(wave_id);
//    }

	// 2. Ω´∑˛ŒÒ∆˜∑¢π˝¿¥µƒ ˝æ›∑¢ÀÕ≥ˆ»•
    Game_Logic::Game_Content_Interface::instance()->exec_interface("procenterinstance", para);

    return true;
}


bool Client_Instance_Msg_Proc::enter_instance(Game_Logic::Game_Interface& gm_interface)
{
//CCLog("-------------------->Client_Instance_Msg_Proc::enter_instance ---to game");
    UI_MainMenu_Layer::get_instance()->buttonAreaInstance();
    
    vector<uint64> para;
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    para.push_back( player_id );
    para.push_back(1000);
//    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequirestage", para);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequireallstage", para);
    return true;
}

bool Client_Instance_Msg_Proc::select_instance(Game_Logic::Game_Interface& gm_interface)
{
//CCLog("-------------------->Client_Instance_Msg_Proc::select_instance ---to game");
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 1)
        return false;
    int instance_id = (int)para[0];
    int instance_type  = (int)para[1];
    int scene_id = (int)para[2];
    //send msg to server
//    char body[256] = {0};
//    message_stream body_ms(body, sizeof(body));
//    body_ms << CLIENT_INSTANCE_REQUIRE << instance_id << instance_type;
//
//    CNetManager::GetMe()->send_msg( body_ms );

    const char* loadFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MODEL_LOADING_FONT);
    CocoStu_UI_Scene_Interface::get_instance()->lockScreen("载入中","");
    Game_Logic::Game_Interface temp;
    vector<uint64> param;
    param.push_back(instance_id);
    param.push_back(scene_id);
    temp.set_para(param);
    on_player_enter_instance(temp);
    return true;

}

bool Client_Instance_Msg_Proc::on_player_instance_monster_wave(Game_Logic::Game_Interface& gm_interface)
{
//CCLog("-------------------->Client_Instance_Msg_Proc::on_player_instance_monster_wave ---to game");
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));
    int player_id = 0;
    int instance_id = 0;
    int scene_id = 0;
    int monster_wave_id = 0;
    int monster_wave_count = 0;
    body_ms >> player_id >> instance_id >> scene_id >> monster_wave_id >> monster_wave_count;
    vector<int> monster_wave_list;
    int wave_id;
    for( int i = 0; i < monster_wave_count; i++ )
    {
        body_ms >> wave_id;
        monster_wave_list.push_back( wave_id );
    }

    current_instance_data cid;
    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {
        return false;
    }

    // get monster id list and call to reg event
    map<int,int> monster_lst; monster_lst.clear();
    //Game_Utils::instance()->get_monster_prototype_map(monster_lst);
    vector<uint64> para;
    para.clear();
    para.push_back(player_id);
    para.push_back(instance_id);
    map<int,int>::iterator iti;
    Game_Data::Game_Element ge;
    for( iti = monster_lst.begin(); iti != monster_lst.end(); ++iti)
    {
        ge.reset();
        ge.set_cell_id(iti->first);
        ge.set_count_require(iti->second);
        cid.instert_monster_counter_lst(ge);
    }
    INSTANCE_DATA_MGR::instance()->modi_player_instance(player_id, cid);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("regmonsterdie",para);
    return true;
}


bool Client_Instance_Msg_Proc::send_instance_finish(Game_Logic::Game_Interface& gm_interface)
{
//CCLog("-------------------->Client_Instance_Msg_Proc::send_instance_finish ---to game");
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 3)
        return false;

    int player_id = (int)para[0];
    int instance_id = (int)para[1];
    int stage_id = (int)para[2];
    int state = (int)para[3];

    current_instance_data cid;
    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {
        return false;
    }

    int total_player_die = cid.get_total_player_die();

    //send msg to server
//    char body[256] = {0};
//    message_stream body_ms(body, sizeof(body));
//    body_ms << CLIENT_INSTANCE_FINISHI << player_id << instance_id << state << total_player_die;
//
//    CNetManager::GetMe()->send_msg( body_ms );

    Game_Logic::Game_Event event;
    event.reset();
    event.set_para(para);
    event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
    event.set_char_id( player_id );
    event.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_INSTANCE);
    event.set_event_owner_id(instance_id);

    Game_Logic::Game_Event_Mgr::instance()->remove_event(player_id, event);

//	Game_Logic::Game_Content_Interface::instance()->exec_interface("waiting", para);

//    INSTANCE_DATA_MGR::instance()->clear_stage_data();
    Game_Logic::Game_Interface temp;
    vector<uint64> param;
    param.push_back(player_id);
    param.push_back(instance_id);
    param.push_back(stage_id);
    param.push_back(state);
    temp.set_para(param);
    on_player_instance_finish_result(temp);
    return true;
}

bool Client_Instance_Msg_Proc::on_player_instance_finish_result( Game_Logic::Game_Interface& gm_interface )
{
	log("<=============================== on instance result ==================================>");
//    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
//    body_ms.set_rd_ptr(sizeof(int));

    int player_id = 0 , instance_id = 0, rst = 0, item_count = 0, score = 0, time_consum = 0;
//    body_ms >> player_id >> instance_id >> rst >> score >>time_consum >>item_count;
    vector<uint64> param;
    param = gm_interface.get_para();
    player_id = (int)param[0];
    instance_id = (int)param[1];
    int stage_id = (int)param[2];
    rst = (int) param[3];
    
    if (rst == current_instance_data::INSTANCE_STATE_SUC) {
        score = 80 + abs(rand())%20;
    }else if(rst == current_instance_data::INSTANCE_STATE_FAILE){
        score= 10 + abs(rand())%10;
    }
    item_count = 1;

    current_instance_data cid; vector<uint64> para; para.clear();

    if(0 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid) )
    {
        cid.set_instance_score(score);
        cid.set_instance_state(rst);
        cid.set_time_grad(time_consum); 
		//uint64 item_id = 0;
		int item_id = 0;

		int count = 0;
        for( int i = 0; i < item_count; ++ i)
        {
//            body_ms >> item_id >> count;
            item_id = 10000+abs(rand())%10;
            count = 1;
            cid.set_item_award_list(item_id, count);
 
            cid.set_item_award_id_que(item_id);
            cid.set_item_award_count_que(count);

        }
		int money = 0;
		int exp = 0;
//		body_ms >> money >> exp;
        money = 200 + rand()%100;
        exp = 130 + abs(rand())%100;
		ResultLayer::sMoney = money;
		ResultLayer::sExp = exp;
		//cid.set_item_award_id_que(money);
        INSTANCE_DATA_MGR::instance()->modi_player_instance( player_id, cid);
    }
    
//    if (rst == current_instance_data::INSTANCE_STATE_SUC) {
//        if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid))
//        {
//            INSTANCE_DATA_MGR::instance()->add_player_instance_lst(player_id, cid);
//        }
//        else
//        {
//            INSTANCE_DATA_MGR::instance()->modi_player_instance_list(player_id, cid);
//        }
//    }
    //失败的情况不会改变什么，不需要记录
    if (rst == current_instance_data::INSTANCE_STATE_SUC) {
        cocos2d::Value key(player_id);
        rapidjson::Value dic;
        rapidjson::Document doc;
        //分开记录普通副本与无尽塔副本
        std::string scorePath;
        if (stage_id == 5000) {
            scorePath = ENDLESS_TOWER_SCORE_FILE;
        }else{
            scorePath = INSTANCE_SCORE_FILE;
        }
        //如果找不到此角色的记录，说明之前已经错了，不用再做什么
        if (GameReader::isExistInFile(scorePath, key, doc, dic, "player_id")) {
            bool needSave = false;
            int size = dic["stage_result"].Size();
            for (int i = 0; i<size; i++) {
                int tempStageId = DICTOOL->getIntValue_json(dic["stage_result"][i], "stage_id");
                if (tempStageId == stage_id) {
                    int instanceCount = dic["stage_result"][i]["instance_result"].Size();
                    bool tempPass = true;
                    
                    for (int j = 0; j<instanceCount; j++) {
                        int tempInstanceId = DICTOOL->getIntValue_json(dic["stage_result"][i]["instance_result"][j], "instance_id");
                        int tempInstanceScore = DICTOOL->getIntValue_json(dic["stage_result"][i]["instance_result"][j], "instance_score");
                        //找到本关，如果成绩更好，就记录，否则不用存。
                        if (tempInstanceId == instance_id) {
                            if (score>tempInstanceScore) {
                                dic["stage_result"][i]["instance_result"][j]["instance_score"]=score;
                                tempInstanceScore = score;
                                needSave = true;
                            }
                        }
                        //所有副本都成功过，才算本关通过
                        tempPass = tempPass && (tempInstanceScore>=0);
                        
                    }
                    dic["stage_result"][i]["pass"] = (tempPass?1:0);
                    break;
                }
            }
            
            if (needSave) {
                GameReader::saveInstanceScore(scorePath, dic, key, "player_id");
//                GameReader::saveDoc2File(scorePath, doc);
//                auto path = FileUtils::getInstance()->getWritablePath();
//                path += scorePath;
//                
//                rapidjson::StringBuffer buff;
//                rapidjson::Writer<rapidjson::StringBuffer> writer(buff);
//                doc.Accept(writer);
//                
//                
//                std::string s = StringUtils::format("%s", buff.GetString());
//                log("%s", s.c_str());
//                FILE* pFile = fopen(path.c_str(),"wb");
//                if (pFile)
//                {
//                    fputs(buff.GetString(),pFile);
//                    fclose(pFile);
//                }else
//                {
//                    CCLOG("UserManage::SaveUserToFile error! can not open %s",path.c_str());
//                }

            }
        }
    }
    
    //process instance finish
    para.clear();
    para.push_back( player_id );
    para.push_back( instance_id );
    para.push_back( score );
    para.push_back( rst );
    Game_Logic::Game_Content_Interface::instance()->exec_interface("processinstancefinish",para);//old
    /******************************************* dely *******************************************/
   
    //Game_Logic::Game_Content_Interface::instance()->exec_interface("pop_result", para);
    /******************************************* dely *******************************************/
    return true;
}

bool Client_Instance_Msg_Proc::on_player_instance_progress( Game_Logic::Game_Interface& gm_interface )
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));
    int player_id = 0;
    int size = 0;
    body_ms >> player_id;
    body_ms >> size;

    int instance_id = 0;
    int instance_score = 0;
    current_instance_data cid;
    for( int i = 0; i < size; ++ i )
    {
        instance_id = 0; 
        instance_score = 0;

        body_ms >> instance_id;
        body_ms >> instance_score;

        cid.reset();
        cid.set_instance_id(instance_id);
        cid.set_instance_score(instance_score);
        cid.set_instance_state(current_instance_data::INSTANCE_STATE_SUC);
        if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid))
        {
            cid.set_instance_id(instance_id);
            cid.set_instance_score(instance_score);
            cid.set_instance_state(current_instance_data::INSTANCE_STATE_SUC);

            INSTANCE_DATA_MGR::instance()->add_player_instance_lst(player_id, cid);
        }
        else
        {
            cid.set_instance_id(instance_id);
            cid.set_instance_score(instance_score);
            cid.set_instance_state(current_instance_data::INSTANCE_STATE_SUC);

            INSTANCE_DATA_MGR::instance()->modi_player_instance_list(player_id, cid);
        }

    }

    return true;
}

bool Client_Instance_Msg_Proc::on_player_stage_instance_state( Game_Logic::Game_Interface& gm_interface )
{
//CCLog("-------------------->Client_Instance_Msg_Proc::on_player_stage_instance_state ---to game");
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));
    int player_id = 0, stage_id = 0, size = 0;
    body_ms >> player_id >> stage_id >> size;

    int instance_id = 0, instance_score = 0;
    current_instance_data cid;
    for( int i = 0; i < size; ++ i )
    {
        instance_id = 0; instance_score = 0;
        
        body_ms >> instance_id >> instance_score;

        cid.reset();
        cid.set_instance_id(instance_id);
        cid.set_instance_score(instance_score);
        cid.set_instance_state(current_instance_data::INSTANCE_STATE_SUC);
        if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid))
        {
            cid.set_instance_id( instance_id );
            cid.set_instance_score( instance_score );
            cid.set_instance_state(current_instance_data::INSTANCE_STATE_SUC);
            INSTANCE_DATA_MGR::instance()->add_player_instance_lst( player_id, cid );
        }
        else
        {
            cid.set_instance_id( instance_id );
            cid.set_instance_score( instance_score );
            cid.set_instance_state(current_instance_data::INSTANCE_STATE_SUC);
            INSTANCE_DATA_MGR::instance()->modi_player_instance_list( player_id, cid );
        }

    }

    Game_Logic::Game_Event_Response::instance()->on_update_instance_stage_info( player_id );

    return true;
}

bool Client_Instance_Msg_Proc::on_instance_sweep( Game_Logic::Game_Interface& gm_interface )
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    INSTANCE_SWEEP_DATA_MGR::instance()->set_award(body_ms);

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Logic::Game_Event_Response::instance()->on_update_instance_sweep(player_id );

    if (INSTANCE_SWEEP_DATA_MGR::instance()->is_keep_sweep() == false)
    {
        return true;
    }

    if (INSTANCE_SWEEP_DATA_MGR::instance()->is_have_enough_energy() == false)
    {
        return true;
    }

    if (INSTANCE_SWEEP_DATA_MGR::instance()->is_have_enough_bag_room() == false)
    {
        return true;
    }

    // keep sweep
    int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
    int is_elite_instance = INSTANCE_SWEEP_DATA_MGR::instance()->get_is_elite_instance();
    vector<uint64> para;
    para.push_back(instance_id);
    para.push_back(is_elite_instance);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("send_instance_sweep", para);

    return true;
}

bool Client_Instance_Msg_Proc::on_player_stage( Game_Logic::Game_Interface& gm_interface )
{
////CCLog("-------------------->Client_Instance_Msg_Proc::on_player_stage ---to game");
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));
    int player_id = 0, size = 0;
    body_ms >> player_id  >> size;

    int stage = 0; int pass = 0;
    for( int i = 0; i < size; i ++ )
    {
        stage = 0; pass = 0;
        body_ms >> stage >> pass;
        INSTANCE_DATA_MGR::instance()->add_stage_data( stage, pass );
    }

    Game_Logic::Game_Event_Response::instance()->on_update_stage( player_id );
    return true;
}

bool Client_Instance_Msg_Proc::on_player_stage_instance(Game_Logic::Game_Interface &gm_interface)
{
	/************************************************************************/
	// ¥”∑˛ŒÒ∆˜Ω” ’ÕÊº“∏±±æµƒœ‡πÿ–≈œ¢
	// 1. ªÒ»°µ±«∞’¬Ω⁄µƒÀ˘”–πÿø®µƒÕ®πÿ«Èøˆ≤¢¥Ê¥¢
//    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
//    body_ms.set_rd_ptr(sizeof(int));
    vector<uint64> para;
    gm_interface.get_para(para);
    if (para.size() < 2) {
        return false;
    }
    
    
    int player_id = 0, stage_id = 0, size = 0;
//    body_ms >> player_id  >> size;
    player_id = (int)para[0];
    stage_id = (int)para[1];
    cocos2d::Value key(player_id);
    rapidjson::Value dic;
    rapidjson::Document doc;
    //找到角色分数记录。如找不到就根据关卡设定，创建一个存在副本分数文件里，并使用默认数据填充。
    //副本分数文件的json结构应是：
    //      [{"player_id":1,
    //      "stage_result":[{"stage_id":1000,"pass":-1,
    //                      "instance_result":[{"instance_id":10000,"instance_score":39},...]},
    //                      ...]},
    //      {},...]
    //如果找到此角色的分数记录，则读取数据填充内存。
    std::string scorePath;
    if (stage_id == 5000) {
        scorePath = ENDLESS_TOWER_SCORE_FILE;
    }else{
        scorePath = INSTANCE_SCORE_FILE;
    }
    if (!GameReader::isExistInFile(scorePath, key, doc, dic, "player_id")) {
        auto defaultDoc = GameReader::getDocInstance("game_data/Play_System/scene_ui_config.json");
        //从关卡设定文件中读取stage和instance信息
        std::vector<int> areas;
        std::map<int, int> instances;
        for (int i = 0; i<defaultDoc->Size(); i++) {
            int area_id = DICTOOL->getIntValue_json((*defaultDoc)[i], "area_id");
            int instance_id = DICTOOL->getIntValue_json((*defaultDoc)[i], "instance_id");
            //5000代表无尽塔区，普通副本与无尽塔副本要分开
            if (stage_id == 5000) {
                if (area_id != 5000) {
                    continue;
                }
            }else{
                if (area_id == 5000) {
                    continue;
                }
            }
            instances[instance_id] = area_id;
            if (find(areas.begin(), areas.end(), area_id) != areas.end()) {
                continue;
            }
            areas.push_back(area_id);
        }
        
        rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
        
        rapidjson::Value areaResult;
        areaResult.SetArray();
        
        for (int i = 0; i<areas.size(); i++) {
            rapidjson::Value areaScore;
            areaScore.SetObject();
            areaScore.AddMember("stage_id", areas[i], allocator);
            areaScore.AddMember("pass", -1, allocator);
            rapidjson::Value instanceResult;
            instanceResult.SetArray();
            for (auto itr = instances.begin(); itr != instances.end(); itr++) {
                if (itr->second != areas[i]) {
                    continue;
                }
                rapidjson::Value instanceScore;
                instanceScore.SetObject();
                instanceScore.AddMember("instance_id", itr->first, allocator);
                instanceScore.AddMember("instance_score", -1, allocator);
                instanceResult.PushBack(instanceScore, allocator);
            }
            areaScore.AddMember("instance_result", instanceResult, allocator);
            areaResult.PushBack(areaScore, allocator);
        }
        
        rapidjson::Value value;
        value.SetObject();
        value.AddMember("player_id", player_id, allocator);
        value.AddMember("stage_result", areaResult, allocator);
        
        GameReader::saveInstanceScore(scorePath, value, key, "player_id");
        
        
        size = areaResult.Size();
        
        int stage; int pass;
        for( int i = 0; i < size; i ++ )
        {
            stage = 0; pass = -1;
            stage = DICTOOL->getIntValue_json(areaResult[i], "stage_id");
            pass = DICTOOL->getIntValue_json(areaResult[i], "pass");
            INSTANCE_DATA_MGR::instance()->add_stage_data( stage, pass );
            
            const rapidjson::Value& insResult = DICTOOL->getSubDictionary_json(areaResult[i], "instance_result");
            int instanceCount = insResult.Size();
            for (int j = 0; j<instanceCount; j++) {
                int instance_id = 0;
                int instance_score = 0;
                
                current_instance_data cid;
                //        body_ms >> instance_id >> instance_score;
                instance_id = DICTOOL->getIntValue_json(insResult[j], "instance_id");
                instance_score = DICTOOL->getIntValue_json(insResult[j], "instance_score");
                
                cid.reset();
                cid.set_instance_id(instance_id);
                cid.set_instance_score(instance_score);
                cid.set_instance_state(current_instance_data::INSTANCE_STATE_SUC);
                if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid))
                {
                    cid.set_instance_id( instance_id );
                    cid.set_instance_score( instance_score );
                    cid.set_instance_state(current_instance_data::INSTANCE_STATE_FAILE);
                    INSTANCE_DATA_MGR::instance()->add_player_instance_lst( player_id, cid );
                }
                else
                {
                    cid.set_instance_id( instance_id );
                    cid.set_instance_score( instance_score );
                    cid.set_instance_state(current_instance_data::INSTANCE_STATE_FAILE);
                    INSTANCE_DATA_MGR::instance()->modi_player_instance_list( player_id, cid );
                }
            }
        }
    }else{
        
        const rapidjson::Value& areaResult = DICTOOL->getSubDictionary_json(dic, "stage_result");
        size = areaResult.Size();
        
        int stage; int pass;
        for( int i = 0; i < size; i ++ )
        {
            stage = 0; pass = -1;
            stage = DICTOOL->getIntValue_json(areaResult[i], "stage_id");
            pass = DICTOOL->getIntValue_json(areaResult[i], "pass");
            INSTANCE_DATA_MGR::instance()->add_stage_data( stage, pass );
            
            const rapidjson::Value& instanceResult = DICTOOL->getSubDictionary_json(areaResult[i], "instance_result");
            int instanceCount = instanceResult.Size();
            for (int j = 0; j<instanceCount; j++) {
                int instance_id = 0;
                int instance_score = 0;
                int instance_state = current_instance_data::INSTANCE_STATE_FAILE;
                current_instance_data cid;
                //        body_ms >> instance_id >> instance_score;
                instance_id = DICTOOL->getIntValue_json(instanceResult[j], "instance_id");
                instance_score = DICTOOL->getIntValue_json(instanceResult[j], "instance_score");

                if (instance_score >= 0) {
                    instance_state = current_instance_data::INSTANCE_STATE_SUC;
                }
                cid.reset();
                cid.set_instance_id(instance_id);
                cid.set_instance_score(instance_score);
//                cid.set_instance_state(current_instance_data::INSTANCE_STATE_SUC);
                if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid))
                {
                    cid.set_instance_id( instance_id );
                    cid.set_instance_score( instance_score );
                    cid.set_instance_state(instance_state);
                    INSTANCE_DATA_MGR::instance()->add_player_instance_lst( player_id, cid );
                }
                else
                {
                    cid.set_instance_id( instance_id );
                    cid.set_instance_score( instance_score );
                    cid.set_instance_state(instance_state);
                    INSTANCE_DATA_MGR::instance()->modi_player_instance_list( player_id, cid );
                }
            }
        }

    }
    
    
	// 3. ∑¢ÀÕœ˚œ¢¥Úø™—°‘Ò’¬Ω⁄ΩÁ√Ê
	Game_Logic::Game_Event_Response::instance()->on_update_stage_all(player_id);
	Director::getInstance()->getRunningScene()->removeChildByName("waiting");

    return true;
}

bool Client_Instance_Msg_Proc::send_monster_kill( Game_Logic::Game_Interface& gm_interface )
{
//CCLog("-------------------->Client_Instance_Msg_Proc::send_monster_kill ---to game");
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 2)
        return false;

    int player_id = (int)para[0];
    int monster_count = (int)para[1];

    //send msg to server
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CLIENT_MONSTER_KILL << player_id << monster_count;


    if( (int)para.size() < 2 + monster_count * 2)
        return false;

    int monster_id = 0, kill_count = 0;
    for(int i = 0; i < monster_count; ++ i )
    {
        monster_id = (int)para[2 + i * 2];
        kill_count = (int)para[2 + i * 2 + 1];

        body_ms << monster_id << kill_count;
    }


    CNetManager::GetMe()->send_msg( body_ms );

    return true;
}

bool Client_Instance_Msg_Proc::send_require_stage_instance_list( Game_Logic::Game_Interface& gm_interface )
{
////CCLog("-------------------->Client_Instance_Msg_Proc::send_require_stage_instance_list ---to game");
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 2)
        return false;

    int player_id = (int)para[0];
    int stage = (int)para[1];

    //send msg to server
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CLIENT_REQUIRE_STAGE_INSTANCE_STATE << player_id << stage;


    CNetManager::GetMe()->send_msg( body_ms );

    return true;
}

bool Client_Instance_Msg_Proc::send_reuqire_stage( Game_Logic::Game_Interface& gm_interface )
{
	//CCLog("-------------------->Client_Instance_Msg_Proc::send_reuqire_stage ---to game");
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 1)
        return false;

    int player_id = (int)para[0];

    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CLIENT_REQUIRE_STAGE << player_id;

    CNetManager::GetMe()->send_msg( body_ms );

    return true;
}

bool Client_Instance_Msg_Proc::send_require_all_stage(Game_Logic::Game_Interface &gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
//    if(para.size() < 2)
//        return false;
//    
    int player_id = (int)para[0];
    int stage = (int)para[1];

	INSTANCE_DATA_MGR::instance()->set_current_instance_stage_id(stage);

//    //send msg to server
//    char body[256] = {0};
//    message_stream body_ms(body, sizeof(body));
//    body_ms << CLIENT_REQUIRE_STAGE_ALL << player_id << stage;
//    
//    
//    CNetManager::GetMe()->send_msg( body_ms );
    

	Game_Logic::Game_Content_Interface::instance()->exec_interface("waiting", para);
    
    Game_Logic::Game_Interface temp;
    vector<uint64> param;
    param.push_back(player_id);
    param.push_back(stage);
    temp.set_para(param);
    on_player_stage_instance(temp);

    return true;
}

bool Client_Instance_Msg_Proc::send_begin_instance_timer( Game_Logic::Game_Interface& gm_interface )
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 2)
        return false;

    int player_id = (int)para[0];
    int instance_id = (int)para[1];

    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CLIENT_BEGIN_INSTANCE_TIMER << player_id << instance_id;

    CNetManager::GetMe()->send_msg( body_ms );

    return true;
}

bool Client_Instance_Msg_Proc::send_instance_player_die( Game_Logic::Game_Interface& gm_interface )
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 2)
        return false;

    int player_id = (int)para[0];
    int instance_id = (int)para[1];

    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CLIENT_INSTANCE_PLAYER_DIE << player_id << instance_id;

    CNetManager::GetMe()->send_msg( body_ms );

    return true;
}

bool Client_Instance_Msg_Proc::send_instance_sweep(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 2)
        return false;

    int instance_id = (int)para[0];
    int is_elite_instance = (int)para[1];

    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CLIENT_INSTANCE_SWEEP;
    body_ms << instance_id;
    body_ms << is_elite_instance;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}
/******************************************* dely *****************************************/

bool Client_Instance_Msg_Proc::send_back_main_city(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	int player_id = para[0];
	int instance_id = para[1];
    
//	char body[256] = { 0 };
//	message_stream body_ms(body, sizeof(body));
//	body_ms << C2S_PLAYER_INTO_MAIN_CITY;
//	body_ms << player_id;
//	body_ms << instance_id;
//	body_ms << ResultLayer::sUpWhere;
//	body_ms << ResultLayer::sDownWhere;
//	CNetManager::GetMe()->send_msg(body_ms);
    
	CCLOG("back main city");
    
    Game_Logic::Game_Interface temp;
    vector<uint64> param;
    param.push_back(ResultLayer::sExp);
    param.push_back(ResultLayer::sMoney);
    temp.set_para(param);
    Player_Msg_Proc::on_player_into_main_city(temp);
	return true;
}
/******************************************* dely *****************************************/

bool Client_Instance_Msg_Proc::send_require_challenge_next_instance(Game_Logic::Game_Interface &gm_interface)
{
	/************************************************************************/
	// ∑¢ÀÕœ˚œ¢«Î«ÛÃÙ’Ωœ¬“ªπÿ
	vector<uint64> para;
	gm_interface.get_para(para);
	if (para.size() < 2)
		return false;

	int nPlayerid			= (int)para[0];
	int nCurrentInstanceID	= (int)para[1];

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	body_ms << CLIENT_INSTANCE_NEXT;
	body_ms << nPlayerid;
	body_ms << nCurrentInstanceID;
	body_ms << ResultLayer::sUpWhere;
	body_ms << ResultLayer::sDownWhere;
	CNetManager::GetMe()->send_msg(body_ms);
	return true;
}

bool Client_Instance_Msg_Proc::on_player_next_instance(Game_Logic::Game_Interface &gm_interface)
{
	/************************************************************************/
	// ∑˛ŒÒ∆˜∑µªÿœ˚œ¢ÃÙ’Ωœ¬“ªπÿ
	// 1. ∏¸∏ƒµ±«∞πÿø®µƒID
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int nPlayerID		= 0;
	int nNextInstanceID = 0;
	body_ms >> nPlayerID >> nNextInstanceID;
	INSTANCE_DATA_MGR::instance()->set_current_instance_id(nNextInstanceID);

	// 2. Õ®÷™GameScene«–ªª≥°æ∞
	vector<uint64> para;
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	para.push_back(player_id);
	para.push_back(nNextInstanceID);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("next_instance_msg_been_received", para);
	return true;
}
