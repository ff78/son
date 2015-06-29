// -*- C++ -*-

#ifndef CTRL_DATA_H_
#define CTRL_DATA_H_

#include <string>
#include <map>
#include <vector>

#ifdef YN_LINUX
#include <pthread.h>
#endif
/**
 * @data structures of game play controller
 * 
 * @time_stamp, activity, record,ctrler_data
 */


typedef unsigned short ushort;
typedef unsigned int uint;

struct time_stamp
{
 ushort year_;
 ushort month_;
 ushort day_;
 ushort hour_;
 ushort minute_;
 ushort second_;
 ushort day_of_week_; 
};

struct record
{
  int role_id_;
  uint act_id_;
  uint repeat_count_;
#ifdef YN_LINUX
	time_t commit_time_;
#endif
#ifdef YN_WINDOWS
    __time32_t commit_time_;
#endif
};

struct activity
{
  uint id_;
  uint group_;
  uint repeat_;
  uint icon_;
  time_stamp start_time_;
  time_stamp stop_time_;
  std::string bind_;
};

typedef std::map<uint/*act_id*/,activity*> map_act;
typedef std::map<uint,activity*>::iterator map_act_it;

typedef std::vector<record*> vec_record;
typedef std::vector<record*>::iterator vec_rec_it;

typedef std::map<int/*role id*/,vec_record*> map_record;
typedef std::map<int,vec_record*>::iterator map_record_it;

class ctrl_data
{
public:
  ~ctrl_data();
  static ctrl_data* instance();
private:
  ctrl_data();
  static ctrl_data* instance_;
  
  class garb
  {
  	public:
  		~garb()
  		{
  			if(ctrl_data::instance_)
  				delete ctrl_data::instance_;
  		}
  };
  static garb garb_;
  
public:
  map_act          map_act_;            //all acitvities
  map_record       map_record_;         //all role-activity records
#ifdef YN_LINUX
  pthread_mutex_t  record_mutex_;       //mutex for records read/write
#endif
};



#endif // CTRL_DATA_H_

