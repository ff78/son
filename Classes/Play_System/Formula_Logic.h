

#if !defined(EA_E13DF125_552D_4f16_AEFA_C84D6CFE504B__INCLUDED_)
#define EA_E13DF125_552D_4f16_AEFA_C84D6CFE504B__INCLUDED_

#include "Game_Interface/event_define.h"
#include "Game_Interface/game_element.h"

namespace Game_Logic
{
	struct Game_Interface;
}
class Formula_Logic
{

public:
	Formula_Logic();
	virtual ~Formula_Logic();
	int init_formula_system( void );
	static bool load_formula_data(Game_Logic::Game_Interface& gm_interface);

	static bool exec_formula(Game_Logic::Game_Interface& gm_interface);

	int exec_formula_function_list(int player_id, list<Game_Data::Game_Element>& ge_lst );

	int exec_formula_function(const char* cmd, std::vector<uint64> para, const char* key);

    static Formula_Logic* instance();
private:
    int exec_element_function_list( int player_id, std::list<Game_Data::Game_Element>& ge_lst, const char* key );

    int exec_formula_interface(const char* cmd, std::vector<uint64> para, const char* key);

	Game_Logic::game_interface_handler_map_t formula_function_call_list_;
    static Formula_Logic* instance_;
};

#endif // !defined(EA_E13DF125_552D_4f16_AEFA_C84D6CFE504B__INCLUDED_)

typedef Formula_Logic FORMULA_LOGIC;

