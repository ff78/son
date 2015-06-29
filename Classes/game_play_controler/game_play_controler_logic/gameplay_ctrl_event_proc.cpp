#include "gameplay_ctrl_event_proc.h"
#include "gameplay_ctrl_logic.h"
#include "game_play_controler/game_play_controler_data/gameplay_ctrl_tool.h"

bool gameplay_ctrl_event_proc::add_rec_count(const Game_Logic::Game_Event& gm_evt)
{
  if (gameplay_ctrl_logic::instance()->add_rec_count(gm_evt.get_char_id(),
                                         gm_evt.get_event_owner_id()) == 0)
    return true;
  else
    return false;
}


