

#ifndef __FightNpc_LOGIC_H__
#define __FightNpc_LOGIC_H__

namespace Game_Logic
{
	struct Game_Interface;
}

class FightNpc_Logic
{
public:
    FightNpc_Logic();
    virtual ~FightNpc_Logic();

    static FightNpc_Logic* instance();

    static bool create_FightNpc(Game_Logic::Game_Interface& gm_interface);

private:
    static FightNpc_Logic*         instance_;

};

typedef FightNpc_Logic FightNpc_LOGIC;

#endif /* __FightNpc_LOGIC_H__ */

