// -*- C++ -*-


#ifndef GAMEPLAY_CTRL_LOGIC_H_
#define GAMEPLAY_CTRL_LOGIC_H_

#include "game_play_controler/game_play_controler_data/ctrl_data.h"
#include "Game_Interface/event_define.h"
/**
 * @class gameplay_ctrl_logic
 * 
 * @brief
 */
class gameplay_ctrl_logic
{
public:

	gameplay_ctrl_logic();
	~gameplay_ctrl_logic();
  /*
   * when start game, this method should be invoked to initialize
   * the ctrl_logic module
   */
	
	int ctrl_init();
 
  /*
   * when a player login
   * invok this method first
   */
  static gameplay_ctrl_logic* instance ( void );
  int player_login(int p_role_id);
  
  int player_logout(int p_role_id);

  int can_accept_act(int p_role_id,
                            uint p_act_id);
                        
  int do_accept_act(int p_role_id,
                           uint p_act_id);

  int add_rec_count(int p_role_id,
                           uint p_act_id);
                           
  int giveup_act(int p_role_id,
                        uint p_act_id); 
  
  /*
   * 活动不存在: current_count = 0; total_count = 0;
   */
  void get_role_act_status(const int p_role_id, 
                                const int p_act_id,
                                int& current_count, //参加该活动的次数
                                int& total_count);  //该活动的总次数                
private:
  void register_event(int p_role_id,
                             const activity* p_act);

  bool reg_act_function_callback ( const char* cmd, Game_Logic::game_interface_handler_t handle );

	Game_Logic::game_interface_handler_map_t game_player_ctrl_handle_;

	  static gameplay_ctrl_logic* instance_p_;
                              
//test methods===================================
/*public:
  
  static void test_act_data();
  static void test_role_record(int role_id);*/
//end of test methods============================

};

#endif // GAMEPLAY_CTRL_LOGIC_H_

