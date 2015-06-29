
#if !defined(EA_FE2204FC_B619_462b_BD85_DF54E5A0AE72__INCLUDED_)
#define EA_FE2204FC_B619_462b_BD85_DF54E5A0AE72__INCLUDED_

#include "Game_Interface/event_define.h"
#include "Game_Interface/game_element.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
namespace Game_Logic
{
	struct Game_Interface;
}
class UI_Logic
{

public:
	UI_Logic();
	virtual ~UI_Logic();

	static UI_Logic* instance();

	int init_UI_system();

	int exec_UI_function(const char* cmd, std::vector<uint64> para/*, const char* key*/);

	static bool exec_UI(Game_Logic::Game_Interface& gm_interface);

private:
	static UI_Logic* instance_p_;
	Game_Logic::game_interface_handler_map_t UI_function_call_list_;

};
#endif // !defined(EA_FE2204FC_B619_462b_BD85_DF54E5A0AE72__INCLUDED_)
