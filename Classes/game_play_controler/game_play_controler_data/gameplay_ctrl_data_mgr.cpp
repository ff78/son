#include "gameplay_ctrl_data_mgr.h"
#include "gameplay_ctrl_tool.h"
#include "Game_Interface/common.h"


gameplay_ctrl_data_mgr* gameplay_ctrl_data_mgr::instance_ = 0;


gameplay_ctrl_data_mgr::gameplay_ctrl_data_mgr()
{
}
gameplay_ctrl_data_mgr::~gameplay_ctrl_data_mgr()
{
}

gameplay_ctrl_data_mgr* gameplay_ctrl_data_mgr::instance()
{
    if( !instance_ )
    {
        instance_ = new gameplay_ctrl_data_mgr();
    }
    return instance_;
}

void gameplay_ctrl_data_mgr::init(void)
{
    player_act_list_client_.clear();
}

void gameplay_ctrl_data_mgr::load_act_item(activity* p_act)
{
  ctrl_data::instance()->map_act_.insert(std::make_pair(p_act->id_, 
                                                        p_act));
}

void gameplay_ctrl_data_mgr::load_record_item(record* p_record)
{


  //find role's records
  map_record_it it = ctrl_data::instance()->map_record_.find(p_record->role_id_);
  if (it != ctrl_data::instance()->map_record_.end())
  {
    it->second->push_back(p_record);
  }
  else
  {
    vec_record* role_vec_record = new vec_record;
    role_vec_record->push_back(p_record);

    ctrl_data::instance()->map_record_.insert(std::make_pair(p_record->role_id_,
                                                             role_vec_record));
  }

}

void gameplay_ctrl_data_mgr::load_role_record(int p_role_id, vec_record* p_vec_rec)
{
#ifdef YN_LINUX
  Game_Logic::map_mutex m(&ctrl_data::instance()->record_mutex_);
#endif

   ctrl_data::instance()->map_record_.insert(std::make_pair(p_role_id,
                                                             p_vec_rec));

}

void gameplay_ctrl_data_mgr::get_all_activity(std::vector<activity*>& p_vec_act)
{
#ifdef YN_LINUX
  Game_Logic::map_mutex m(&ctrl_data::instance()->record_mutex_);
#endif
  map_act_it it;
  for(it = ctrl_data::instance()->map_act_.begin();
      it != ctrl_data::instance()->map_act_.end();
      it++)
  {
     p_vec_act.push_back(it->second);
  }
}

const activity* gameplay_ctrl_data_mgr::get_activity_by_id(uint p_act_id)
{
#ifdef YN_LINUX
  Game_Logic::map_mutex m(&ctrl_data::instance()->record_mutex_);
#endif
  map_act_it it =  ctrl_data::instance()->map_act_.find(p_act_id);
  if (it != ctrl_data::instance()->map_act_.end())
  {
    return it->second;
  }
  return NULL;
}

int gameplay_ctrl_data_mgr::get_activity_by_group(uint p_group,
                                                  std::vector<activity*>& p_vec_act)
{
#ifdef YN_LINUX
  Game_Logic::map_mutex m(&ctrl_data::instance()->record_mutex_);
#endif
  map_act_it it;
  for (it = ctrl_data::instance()->map_act_.begin();
       it != ctrl_data::instance()->map_act_.end();
       it++)
  {
    if (it->second->group_ == p_group)
      p_vec_act.push_back(it->second);
  }

  if (p_vec_act.size() > 0)
    return 0;
  else
    return -1;
}

vec_record* gameplay_ctrl_data_mgr::get_role_record(int p_role_id)
{
#ifdef YN_LINUX
  Game_Logic::map_mutex m(&ctrl_data::instance()->record_mutex_);
#endif
	vec_record *result = NULL;

	map_record_it it = ctrl_data::instance()->map_record_.find(p_role_id);
	if (it != ctrl_data::instance()->map_record_.end())
	{
		result = it->second;
	}
	return result;
}

record* gameplay_ctrl_data_mgr::add_role_record(int p_role_id, uint p_act_id)
{
#ifdef YN_LINUX
  Game_Logic::map_mutex m(&ctrl_data::instance()->record_mutex_);
#endif
  //gene the record item
  record * rec = new record;
  rec->role_id_ = p_role_id;
  rec->act_id_ = p_act_id;
  rec->repeat_count_ = 0;
#ifdef YN_WINDOWS
  rec->commit_time_ = (__time32_t)gameplay_ctrl_tool::get_sys_time();
#endif
#ifdef YN_LINUX
  rec->commit_time_ = (time_t)gameplay_ctrl_tool::get_sys_time();
#endif

  //add
  map_record_it it = ctrl_data::instance()->map_record_.find(p_role_id);
  if (it != ctrl_data::instance()->map_record_.end())
  {
    it->second->push_back(rec);
  }
  else
  {
    vec_record *vrec = new vec_record;
    vrec->push_back(rec);
    ctrl_data::instance()->map_record_.insert(std::make_pair(p_role_id, vrec));
  }
  //unlock

  return rec;
}

record* gameplay_ctrl_data_mgr::get_role_record(int p_role_id,
                                                uint p_act_id)
{
#ifdef YN_LINUX
  Game_Logic::map_mutex m(&ctrl_data::instance()->record_mutex_);
#endif

  record *result = NULL;
  //find
  map_record_it it = ctrl_data::instance()->map_record_.find(p_role_id);
  if (it != ctrl_data::instance()->map_record_.end())
  {
    vec_record::iterator vit = it->second->begin();
    for (;vit != it->second->end(); vit++)
    {
      if ((*vit)->act_id_ == p_act_id)
      {
        result = *vit;
        break;
      }
    }
  }
  
  return result;
}

int gameplay_ctrl_data_mgr::del_role_record_item(int p_role_id,
                                                 uint p_act_id)
{
  int flag = -1;
  //lock
#ifdef YN_LINUX
  Game_Logic::map_mutex m(&ctrl_data::instance()->record_mutex_);
#endif
  //find
  map_record_it it = ctrl_data::instance()->map_record_.find(p_role_id);
  if (it != ctrl_data::instance()->map_record_.end())
  {
    vec_record::iterator vit = it->second->begin();
    for (;vit != it->second->end(); vit++)
    {
      if ((*vit)->act_id_ == p_act_id)
      {
        record *r = *vit;
        it->second->erase(vit);
        delete r;
        flag = 0;
        break;
      }
    }
  }

  return flag;
}

int gameplay_ctrl_data_mgr::del_role_record_all(int p_role_id)
{
  int flag = -1;
 
   //lock
#ifdef YN_LINUX
  Game_Logic::map_mutex m(&ctrl_data::instance()->record_mutex_);
#endif
  //find
  map_record_it it = ctrl_data::instance()->map_record_.find(p_role_id);
  if (it != ctrl_data::instance()->map_record_.end())
  {
    vec_record* vrec = it->second;
    vec_record::iterator vit = vrec->begin();
    for (;vit != it->second->end(); vit++)
    {
        record *r = *vit;
        delete r;
    }
    vrec->clear();
    delete vrec;

    ctrl_data::instance()->map_record_.erase(it);
  }

  return flag;
}

int gameplay_ctrl_data_mgr::inc_record_count(int p_role_id,
                                             uint p_act_id)
{
#ifdef YN_LINUX
  Game_Logic::map_mutex m(&ctrl_data::instance()->record_mutex_);
#endif
  record* rec = get_role_record(p_role_id, p_act_id);
  if (rec)
  {
    rec->repeat_count_++;
    return 0;
  }

  return -1;
}


int gameplay_ctrl_data_mgr::add_player_act_data_client( int player_id, int act_id, int count, int total_count)
{
    act_data_client adc;
    adc.set_act_id( act_id );
    adc.set_act_count( count );
    adc.set_act_total_count( total_count );
    std::map<int, std::vector< act_data_client > >::iterator ita;
    ita = player_act_list_client_.find( player_id );
    if( ita == player_act_list_client_.end() )
    {

        std::vector< act_data_client > adc_vec;
        adc_vec.clear();
        adc_vec.push_back( adc );
        player_act_list_client_.insert( make_pair( player_id, adc_vec));
        return 0;
    }
    else
    {

        std::vector< act_data_client >::iterator itv;
        itv = find_if( ita->second.begin(), ita->second.end(), bind2nd( equal_to<act_data_client>(),adc ));
        if( itv == ita->second.end() )
        {
            ita->second.push_back(adc);
            return 0;
        }
        else
        {
            (*itv).set_act_count(count);
            return 0;
        }

    }
    return -1;
}
int gameplay_ctrl_data_mgr::get_player_act_data_client( int player_id, int act_id, act_data_client& adc )
{

    adc.set_act_id( act_id );

    std::map<int, std::vector< act_data_client > >::iterator ita;
    ita = player_act_list_client_.find( player_id );
    if( ita != player_act_list_client_.end() )
    {
        std::vector< act_data_client >::iterator itv;
        itv = find_if( ita->second.begin(), ita->second.end(), bind2nd( equal_to<act_data_client>(),adc ));
        if( itv != ita->second.end() )
        {
            adc = *itv;
            return 0;
        }
    }
    return -1;
}
int gameplay_ctrl_data_mgr::remove_all_player_act_data( int player_id )
{
    std::map<int, std::vector< act_data_client > >::iterator ita;
    ita = player_act_list_client_.find( player_id );
    if( ita != player_act_list_client_.end() )
    {
        player_act_list_client_.erase(ita);
        return 0;

    }

    return -1;
}
  

