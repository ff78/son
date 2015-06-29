#include "msg_manager.h"

#ifdef GAME_CLIENT
#include "cocos2d.h"
#endif
Msg_Manager* Msg_Manager::instance_ = 0;


 Msg_Manager::Msg_Manager():nosync_send_(-1)
{

}
Msg_Manager::~Msg_Manager()
{
    if( instance_ )
        delete instance_;
}

Msg_Manager* Msg_Manager::instance(void)
{
     if( NULL == instance_ )
          instance_ = new Msg_Manager();

     return instance_;
}

int Msg_Manager::init( void )
{
	nosync_send_ = -1;
    return 0;
}

int Msg_Manager::push_msg_to_list( Msg_Data& md )
{
    msg_list_.push(md);
    return 0;
}
int Msg_Manager::pop_msg_list( Msg_Data& md )
{
    if( msg_list_.empty())
        return -1;
    md = msg_list_.front();
    msg_list_.pop();
    return 0;
}

int Msg_Manager::is_empty( void )
{
    return msg_list_.empty() ? 0 : -1;
}

int Msg_Manager::is_engine_empty( void )
{
    return engine_msg_list_.empty() ? 0 : -1;
}

int Msg_Manager::push_engine_msg_to_list( Msg_Data& md )
{
    engine_msg_list_.push(md);
    return 0;
}
int Msg_Manager::pop_engine_msg_list( Msg_Data& md )
{
    if( engine_msg_list_.empty())
        return -1;
    md = engine_msg_list_.front();
    engine_msg_list_.pop();
    return 0;
}

int Msg_Manager::is_engine_msg_empty( void )
{
    return engine_msg_list_.empty() ? 0 : -1;
}

int Msg_Manager::push_send_msg_to_list( Msg_Data& md )
{
#ifdef GAME_CLIENT
	//CCLOG("Msg_Manager::push_send_msg_to_list");
#endif
	send_msg_list_.push(md);
	return 0;
}
int Msg_Manager::pop_send_msg_list( Msg_Data& md )
{

	if( send_msg_list_.empty())
		return -1;
#ifdef GAME_CLIENT
	//CCLOG("Msg_Manager::pop_send_msg_list");
#endif
	md = send_msg_list_.front();
	send_msg_list_.pop();
	return 0;
}
int Msg_Manager::is_send_msg_empty( void )
{
    return send_msg_list_.empty() ? 0 : -1;
}

void Msg_Manager::set_nosync_send( int state )
{
#ifdef GAME_CLIENT
	//CCLOG("Msg_Manager::set_nosync_send %d", state);
#endif
	nosync_send_ = state;

}
int Msg_Manager::get_nosync_send(void )
{
#ifdef GAME_CLIENT
	//CCLOG("Msg_Manager::get_nosync_send %d", nosync_send_);
#endif
	return nosync_send_;
}

