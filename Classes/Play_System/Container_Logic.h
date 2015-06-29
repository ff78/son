

#if !defined(EA_0AE1A1EB_1044_4fa7_9420_3E4862A520C2__INCLUDED_)
#define EA_0AE1A1EB_1044_4fa7_9420_3E4862A520C2__INCLUDED_

#include "Game_Interface/common.h"

namespace Game_Logic
{
	struct Game_Interface;
}
class Container_Logic
{

public:
	Container_Logic();
	virtual ~Container_Logic();

    static Container_Logic* instance();

	static bool create_container(Game_Logic::Game_Interface& gm_interface);
private:
    static Container_Logic* instance_;

};

#endif // !defined(EA_0AE1A1EB_1044_4fa7_9420_3E4862A520C2__INCLUDED_)

