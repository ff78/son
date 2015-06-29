
#if !defined(EA_A780461F_5000_4422_9E4B_E248CB5C22E6__INCLUDED_)
#define EA_A780461F_5000_4422_9E4B_E248CB5C22E6__INCLUDED_

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"

class quest_logic_client
{

public:
	quest_logic_client();
	virtual ~quest_logic_client();

    static quest_logic_client* instance();

    static bool proc_update_quest(Game_Logic::Game_Interface& gm_interface);

    static bool is_quest_done(Game_Logic::Game_Interface& gm_interface);

private:

    int proc_remove_complete_quest( int player_id, int quest_id );
    static quest_logic_client* instance_;

};
#endif // !defined(EA_A780461F_5000_4422_9E4B_E248CB5C22E6__INCLUDED_)
