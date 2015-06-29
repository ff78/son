
#if !defined(EA_E8ED8DD1_783E_4d6e_8A9F_1144C5E70753__INCLUDED_)
#define EA_E8ED8DD1_783E_4d6e_8A9F_1144C5E70753__INCLUDED_

#include "Game_Interface/common.h"
namespace Game_Logic
{
    struct Game_Interface;
    struct Game_Event;
}
class Account_Logic
{

public:
	Account_Logic();
	virtual ~Account_Logic();

    static Account_Logic* instance();

    static bool connect_to_gate_server(Game_Logic::Game_Interface& gm_interface);
    static bool on_finish_load_scene( const Game_Logic::Game_Event& gm_evt );

    static void releaseData( void );
private:
    static Account_Logic* instance_;
};
#endif // !defined(EA_E8ED8DD1_783E_4d6e_8A9F_1144C5E70753__INCLUDED_)
