#ifndef __EVENT_FUNCTION_INSTANCE_H__
#define __EVENT_FUNCTION_INSTANCE_H__
namespace Game_Logic
{
	struct Game_Interface;
}
class Event_Function_Instance
{
public:
	static Event_Function_Instance* sharedInstance();
	
	//½±Àø½ðÇ®
	static bool awardgold(Game_Logic::Game_Interface& gm_interface);

#ifdef GAME_CLIENT

	static bool dropsomething(Game_Logic::Game_Interface& gm_interface);
	//½±ÀøÉúÃüÖµ
	static bool awardhp(Game_Logic::Game_Interface& gm_interface);
	//½±ÀøÅ­Æø
	static bool awardmp(Game_Logic::Game_Interface& gm_interface);
#endif
	static bool monster_die(Game_Logic::Game_Interface& gm_interface);
	static bool collided_something(Game_Logic::Game_Interface& gm_interface);
	static bool useitem(Game_Logic::Game_Interface& gm_interface);
	static bool awarditem(Game_Logic::Game_Interface& gm_interface);
	static bool randomawardone(Game_Logic::Game_Interface& gm_interface);
	static bool on_login(Game_Logic::Game_Interface& gm_interface);
	static bool on_logout(Game_Logic::Game_Interface& gm_interface);

    static bool award_gold(Game_Logic::Game_Interface& gm_interface);
    static bool award_token(Game_Logic::Game_Interface& gm_interface);
    static bool award_prestige(Game_Logic::Game_Interface& gm_interface);
    static bool award_feat(Game_Logic::Game_Interface& gm_interface);
    static bool award_energy(Game_Logic::Game_Interface& gm_interface); 
    static bool award_general_exp(Game_Logic::Game_Interface& gm_interface);
    static bool award_deputy_general(Game_Logic::Game_Interface& gm_interface);

private:
	Event_Function_Instance();
	static Event_Function_Instance* instance_;
	
};
#endif //__EVENT_FUNCTION_INSTANCE_H__