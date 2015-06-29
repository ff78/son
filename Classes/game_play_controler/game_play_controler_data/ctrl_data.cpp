#include "ctrl_data.h"

ctrl_data* ctrl_data::instance_ = NULL;

ctrl_data* ctrl_data::instance()
{
  if (instance_ == NULL) 
    instance_ = new ctrl_data();
  return instance_;
}

ctrl_data::ctrl_data()
{
#ifdef YN_LINUX
  pthread_mutex_init(&record_mutex_,NULL);
#endif
}

ctrl_data::~ctrl_data()
{
#ifdef LINUX_ENV				
		pthread_mutex_destroy(&record_mutex_);
#endif		
//	map_act_it ait = map_act_.begin();
 // for (; ait != map_act_.end(); ait++)
 // {
  //	delete ait->second;
 // }
  
	map_record_.clear();

}

