// -*- C++ -*-



#ifndef MSG_MANAGER_H_
#define MSG_MANAGER_H_

#include "Game_Interface/common.h"

#include <queue>
struct Msg_Data
{
    Msg_Data():size_(0) {}
    ~Msg_Data() {}
    void reset()
    {
        size_ = 0;
        memset(buff_,0x00, _MAX_MSGSIZE -1 );
    }
    typedef std::queue<Msg_Data> Msg_Data_lst_t;
    void  set_buff(const char* buff, const int len){memcpy(buff_,buff,len); size_ = len;}
    const char* get_buff(void) {return buff_;}
    void set_size( const int size ) { size_ = size; }
    int get_size( void ) { return size_; }

	void set_buff2(const char* buff, const int len){
		if ( len <= 0 )
		{
			return;
		}
		
		memcpy(buff_ + sizeof(int), buff, len); 
		size_ = len + sizeof(int);
		*((int*)(buff_)) = size_;
	}
	int get_size2() { return size_ - sizeof(int); };
	const char* get_content() { return buff_ + sizeof(int); };

private:
    char buff_[_MAX_MSGSIZE];
    int size_;
};

class Msg_Manager 
{
public:
    Msg_Manager();
    ~Msg_Manager();

    int init( void );

    static Msg_Manager* instance();
    int push_msg_to_list( Msg_Data& md );
    int pop_msg_list( Msg_Data& md );
    int is_empty( void );
    int is_engine_empty( void );
    int push_engine_msg_to_list( Msg_Data& md );
    int pop_engine_msg_list( Msg_Data& md );
    int is_engine_msg_empty( void );

	int push_send_msg_to_list( Msg_Data& md );
	int pop_send_msg_list( Msg_Data& md );
	int is_send_msg_empty( void );
	void set_nosync_send( int state );
	int get_nosync_send(void );
private:
    static Msg_Manager* instance_;
    Msg_Data::Msg_Data_lst_t msg_list_;
    Msg_Data::Msg_Data_lst_t engine_msg_list_;
	Msg_Data::Msg_Data_lst_t send_msg_list_;
	int nosync_send_;
};

#endif // GATE_SVC_H_

