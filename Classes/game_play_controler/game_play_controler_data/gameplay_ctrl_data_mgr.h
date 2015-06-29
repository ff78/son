// -*- C++ -*-


#ifndef GAMEPLAY_CTRL_DATA_MGR_H_
#define GAMEPLAY_CTRL_DATA_MGR_H_

#include "ctrl_data.h"
#include <map>
#include <vector>

/**
 * @class gameplay_ctrl_data_mgr
 * 
 * @gameplay_ctrl_data_mgr used to manage the activity data
 * and the role-activity record data.
 */
struct act_data_client
{
    act_data_client():act_id_(0),
        act_count_(0),
        act_total_count_(0)
    {
    }

    ~act_data_client() {}

    void reset()
    {
        act_id_ = 0;
        act_count_ = 0;
        act_total_count_ = 0;
    }

     bool operator==(const act_data_client& adc) const
    {
			return (adc.get_act_id() == get_act_id() );
    }

    void set_act_id( int id ) { act_id_ = id; };
    int get_act_id( void )const { return act_id_; }

    void set_act_count( int count ) { act_count_ = count; };
    int get_act_count( void ) const{ return act_count_; }

    void set_act_total_count( int count ) { act_total_count_ = count; };
    int get_act_total_count( void ) const { return act_total_count_; }

private:
    int act_id_;
    int act_count_;
    int act_total_count_;
};

class gameplay_ctrl_data_mgr
{
public:

    gameplay_ctrl_data_mgr();
    ~gameplay_ctrl_data_mgr();

  static void load_act_item(activity* p_act);
  
  static void get_all_activity(std::vector<activity*>& p_vec_act);

  static const activity* get_activity_by_id(uint act_id);
  
  static int get_activity_by_group(uint p_group,
                                   std::vector<activity*>& p_vec_act);
  static gameplay_ctrl_data_mgr* instance();
public:
  static void load_record_item(record* p_record);
  
  static void load_role_record(int p_role_id, vec_record* p_vec_rec);
  
  static vec_record* get_role_record(int p_role_id);
  
  static record* get_role_record(int p_rolel_id,
                                 uint p_act_id);
  
  static record* add_role_record(int p_role_id,
                                 uint p_act_id);

  static int del_role_record_item(int p_role_id,
                                  uint p_act_id);

  static int del_role_record_all(int p_role_id);

  static int inc_record_count(int p_role_id,
                              uint p_act_id);

  void init(void);
  int add_player_act_data_client( int player_id, int act_id, int count, int total_count);
  int get_player_act_data_client( int player_id, int act_id, act_data_client& adc );
  int remove_all_player_act_data( int player_id );

private:

    
  static gameplay_ctrl_data_mgr* instance_;
  std::map< int, std::vector < act_data_client > > player_act_list_client_;

};

#endif // GAMEPLAY_CTRL_DATA_MGR_H_

