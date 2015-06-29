#include "gameplay_ctrl_db_proc.h"
#include <iostream>
#include <fstream>
#include "Play_System/Container_Mgr.h"
#ifdef GAME_SERVER
#include "game_play_controler/game_play_controler_data/gameplay_ctrl_tool.h"
#endif
#include <time.h>

#ifdef GAME_SERVER
#define ACTIVITY_CFG_FILE "../config/activity/activity.json"
#else
#define ACTIVITY_CFG_FILE "game_data/activity/activity.json"
#endif

gameplay_ctrl_db_proc* gameplay_ctrl_db_proc::instance_ = 0;
	
gameplay_ctrl_db_proc* gameplay_ctrl_db_proc::instance(void)
{
		if( NULL == instance_ )
		{
			instance_ = new gameplay_ctrl_db_proc;
		}
		
		return instance_;
}
int gameplay_ctrl_db_proc::load_activity_data()
{
	ctrl_data::instance()->map_act_.clear();


    Json::Value root;
    Game_Data::Container_Mgr::instance()->get_json_value_by_file_name( root, ACTIVITY_CFG_FILE);

  for (Json::Value::iterator p = root.begin();
       p != root.end();
       p++)
  {
    //load each activity
    std::string s_act_id = p.key().asCString();
    activity *act = new activity;
    act->id_ = atoi(s_act_id.c_str());
  
    if (load_act_item(act,root[s_act_id]) == 0)
      gameplay_ctrl_data_mgr::load_act_item(act);
  }

  cout << "\n load activity data over----------------" << endl;
  return 0; 
}

int gameplay_ctrl_db_proc::load_act_item(activity* p_act,
                                         Json::Value& p_act_value)
{
  Json::Value &id = p_act_value["id"];
  if (!id.empty())
    p_act->id_ = id.asInt();

  Json::Value &group = p_act_value["group"];
  if (!group.empty())
    p_act->group_ = group.asInt();

  Json::Value &repeat = p_act_value["repeat"];
  if (!repeat.empty())
    p_act->repeat_ = repeat.asInt();


  Json::Value &day_of_week = p_act_value["start_day-of-week"];
  if (!day_of_week.empty())
    p_act->start_time_.day_of_week_ = atoi(day_of_week.asString().c_str());

    Json::Value &year = p_act_value["start_date_year"];
    if (!year.empty())
      p_act->start_time_.year_ = atoi(year.asString().c_str());
    
    Json::Value &mon = p_act_value["start_date_month"];
    if (!mon.empty())
      p_act->start_time_.month_ = atoi(mon.asString().c_str());

    Json::Value &day = p_act_value["start_date_day"];
    if (!day.empty())
       p_act->start_time_.day_ = atoi(day.asString().c_str());


        Json::Value &h = p_act_value["start_time_hour"];
    if (!h.empty())
      p_act->start_time_.hour_ = atoi(h.asString().c_str());

    Json::Value &m = p_act_value["start_time_minute"];
    if (!m.empty())
      p_act->start_time_.minute_ = atoi(m.asString().c_str());

    Json::Value &s = p_act_value["start_time_second"];
    if (!s.empty())
      p_act->start_time_.second_ = atoi(s.asString().c_str());


  Json::Value &stop_day_of_week = p_act_value["stop_day-of-week"];
  if (!stop_day_of_week.empty())
    p_act->stop_time_.day_of_week_ = atoi(stop_day_of_week.asString().c_str());

    Json::Value &stop_year = p_act_value["stop_date_year"];
    if (!year.empty())
      p_act->stop_time_.year_ = atoi(stop_year.asString().c_str());
    
    Json::Value &stop_mon = p_act_value["stop_date_month"];
    if (!mon.empty())
      p_act->stop_time_.month_ = atoi(stop_mon.asString().c_str());

    Json::Value &stop_day = p_act_value["stop_date_day"];
    if (!day.empty())
       p_act->stop_time_.day_ = atoi(stop_day.asString().c_str());


    Json::Value &stop_h = p_act_value["stop_time_hour"];
    if (!h.empty())
      p_act->stop_time_.hour_ = atoi(stop_h.asString().c_str());

    Json::Value &stop_m = p_act_value["stop_time_minute"];
    if (!m.empty())
      p_act->stop_time_.minute_ = atoi(stop_m.asString().c_str());

    Json::Value &stop_s = p_act_value["stop_time_second"];
    if (!s.empty())
      p_act->stop_time_.second_ = atoi(stop_s.asString().c_str());


  Json::Value &bind = p_act_value["bind"];
  if (!bind.empty())
    p_act->bind_ = std::string(bind.asString());

  return 0;
}

void gameplay_ctrl_db_proc::load_time(time_stamp& time,Json::Value& p_time)
{
  Json::Value &day_of_week = p_time["day-of-week"];
  if (!day_of_week.empty())
    time.day_of_week_ = atoi(day_of_week.asString().c_str());

  //date
  Json::Value &date = p_time["date"];
    
    Json::Value &year = date["year"];
    if (!year.empty())
      time.year_ = atoi(year.asString().c_str());
    
    Json::Value &mon = date["month"];
    if (!mon.empty())
      time.month_ = atoi(mon.asString().c_str());

    Json::Value &day = date["day"];
    if (!day.empty())
       time.day_ = atoi(day.asString().c_str());

  //time
  Json::Value &tm = p_time["time"];

    Json::Value &h = tm["hour"];
    if (!h.empty())
      time.hour_ = atoi(h.asString().c_str());

    Json::Value &m = tm["minute"];
    if (!m.empty())
      time.minute_ = atoi(m.asString().c_str());

    Json::Value &s = tm["second"];
    if (!s.empty())
      time.second_ = atoi(s.asString().c_str());

}
void gameplay_ctrl_db_proc::load_role_record(int p_role_id)
{
#ifdef GAME_SERVER
	//Game_Logic::map_mutex m(&ctrl_db_mutex_);
		//get records
  vec_record old_vec_rec;
  if (gameplay_ctrl_tool::load_role_record(p_role_id, old_vec_rec) != 0)
  	return;
  
  //mantiance the old records:
  //reset count value; delete; other logic
  //return new record and submit to data_mgr
  vec_record *new_vec_rec = new vec_record;
  maintiance_role_record(old_vec_rec, new_vec_rec);
  
  if (new_vec_rec->size() > 0)
  	//load to daga_mgr
    gameplay_ctrl_data_mgr::load_role_record(p_role_id, new_vec_rec);
  else
  	delete new_vec_rec;
#endif
}

void gameplay_ctrl_db_proc::maintiance_role_record(vec_record& p_old_vec_rec,
                                                   vec_record*& p_new_vec_rec)
{
#ifdef GAME_SERVER
	//Game_Logic::map_mutex m(&ctrl_db_mutex_);
	 vec_rec_it it = p_old_vec_rec.begin();
	 for (;it != p_old_vec_rec.end(); it++)
	 {
	 	 record *rec  = *it;
	 	 //logic here
	 	 const activity *act = gameplay_ctrl_data_mgr::get_activity_by_id(rec->act_id_);
	 	 if (act &&                                        //活动有效
	 	 	   gameplay_ctrl_tool::time_valid(act) == 0 &&   //活动时间合法
	 	 	   logic_valid(rec) == 0)                        //活动逻辑合法（日常，每周任务逻辑判定）
	 	 {
	 	 	 p_new_vec_rec->push_back(rec);
	   }
	   else
	   {
	   	 //del row from db
	     del_record_item(rec->role_id_, rec->act_id_);
	     //delete
	     delete rec;
	   }
	 }
#endif
}

int gameplay_ctrl_db_proc::logic_valid(const record* rec)
{
#ifdef GAME_SERVER
	//日常任务：提交时间与当前时间 不在1天，原有记录作废
	//每周x任务：提交时间与当前时间 不在1天，原有记录作废
	//指定日期任务：在time_valid处，已经被否定
#ifdef YN_LINUX
	Game_Logic::map_mutex m(&ctrl_db_mutex_);
#endif
  struct tm cur_tm_, commit_tm;	


#ifdef YN_LINUX
	time_t curt;
 	curt = time(NULL);
	localtime_r(&curt, &cur_tm_); 
	localtime_r(&rec->commit_time_, &commit_tm );
#endif
#ifdef YN_WINDOWS
	__time32_t curt;
 	curt = (__time32_t)time(NULL);
	 _localtime32_s(&cur_tm_, &curt ); 
	_localtime32_s( &commit_tm , &rec->commit_time_);
#endif

  if (cur_tm_.tm_year == commit_tm.tm_year &&
      cur_tm_.tm_yday == commit_tm.tm_yday)
  {
  	//同一天，有效
  	return 0;
  }	 
	return -1;
#else
    return 0;
#endif
}
#ifdef GAME_SERVER                         
int gameplay_ctrl_db_proc::add_record(int p_role_id, 
                                      uint p_act_id)
{

	//Game_Logic::map_mutex m(&ctrl_db_mutex_);
  //get the record from gameplay_ctrl_data_mgr
  record* rec = gameplay_ctrl_data_mgr::get_role_record(p_role_id, p_act_id);

  //insert a record item to db 
  if (rec)
   return gameplay_ctrl_tool::db_add_record(rec);

  return -1;

}

int gameplay_ctrl_db_proc::add_record(const record* p_rec)
{
  //insert a record item to db
  if (!p_rec) return -1;
  return gameplay_ctrl_tool::db_add_record(p_rec);
}

int gameplay_ctrl_db_proc::del_record_item(int p_role_id,
                                           uint p_act_id)
{
  return gameplay_ctrl_tool::db_del_record_item(p_role_id, p_act_id);
}

int gameplay_ctrl_db_proc::del_record_all(int p_role_id)
{
  return gameplay_ctrl_tool::db_del_record_all(p_role_id);
}

int gameplay_ctrl_db_proc::inc_record_count(int p_role_id,
                                            uint p_act_id)
{
  return gameplay_ctrl_tool::db_inc_record_count(p_role_id, p_act_id);
}
#endif





















