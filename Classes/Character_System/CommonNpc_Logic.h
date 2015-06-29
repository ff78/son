

#ifndef __CommonNpc_LOGIC_H__
#define __CommonNpc_LOGIC_H__

namespace Game_Logic
{
	struct Game_Interface;
}

class CommonNpc_Logic
{
public:
    CommonNpc_Logic();
    virtual ~CommonNpc_Logic();

    static CommonNpc_Logic* instance();

    static bool create_CommonNpc(Game_Logic::Game_Interface& gm_interface);

private:
    static CommonNpc_Logic*         instance_;

};

typedef CommonNpc_Logic CommonNpc_LOGIC;

#endif /* __CommonNpc_LOGIC_H__ */

