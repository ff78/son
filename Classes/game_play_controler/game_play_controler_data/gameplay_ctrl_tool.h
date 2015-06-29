// -*- C++ -*-


#ifndef TOOL_H_
#define TOOL_H_

#include "ctrl_data.h"
#ifdef YN_LINUX
//#include "player_manager.h"
//#include "logger.h"
//#include "role_act_rec.h"
#endif
#include <time.h>
/**
 * @class tool
 * 
 * @brief
 */
class gameplay_ctrl_tool
{
public:
  static time_stamp get_time_stamp();
 
  static time_t get_sys_time();
  static int db_add_record(const record* p_rec);

  static int db_del_record_item(int p_role_id,
                                uint p_act_id);

  static int db_del_record_all(int p_role_id);

  static int db_inc_record_count(int p_role_id,
                                 uint p_act_id);
  /*
   * check if the current server time is in the period of atcivity
   */
  static int time_valid(const activity* p_act);

  /*
   * ltime equal/later than rtime : return 0, else return -1
   * flag=0: compare time
   * flag=1: compare day_of_week + time
   * flag=2: compare date + time
   */
  static bool time_equal_late_than(const time_stamp& ltime,
                                   const time_stamp& rtime,
                                   int flag =2);
  
  /*
   *if p_vec_rec.size() > 0, return 0
   *else return -1
   */
  static int load_role_record(int p_role_id,
                              vec_record& p_vec_rec);

  static int analysis_act_bind(const std::string& p_bind,
                                std::string& p_type,
                                int& p_quest_id);
};

#endif // TOOL_H_

