

#ifndef __FUNCTION_OPEN_LOGIC_H__
#define __FUNCTION_OPEN_LOGIC_H__

#include "Function_Open_System/Function_Open_Config_Data.h"

using namespace std;

namespace Game_Data
{
    class Function_Open_Logic
    {
    public:
        Function_Open_Logic();
        virtual ~Function_Open_Logic();
        static Function_Open_Logic* instance();

		void submit_quest_open(int player_id,int quest_id);
		void accept_quest_open(int player_id,int quest_id);

    private:
        static Function_Open_Logic*         instance_;

	public:
        int							        open_icon_array[Game_Data::ICON_SUM];
    };
}

typedef Game_Data::Function_Open_Logic FUNCTION_OPEN_LOGIC;


#endif /* __FUNCTION_OPEN_LOGIC_H__ */
