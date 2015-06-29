

#ifndef __CommonNpc_DATA_H__
#define __CommonNpc_DATA_H__

#include <string>

#define  MAX_SHOP_COUNT    3      // NPC拥有商店的个数

namespace Game_Data
{
    class CommonNpcConfig
    {
    public:
        CommonNpcConfig(void) { reset(); }
        ~CommonNpcConfig(void) { reset(); }
    public:
        virtual int get_static_character_id( void ){return static_character_id;}
        virtual void set_static_character_id(int static_character_id){this->static_character_id = static_character_id;}

        virtual int get_face_mode_id( void ){return face_mode_id;}
        virtual void set_face_mode_id(int face_mode_id){this->face_mode_id = face_mode_id;}

        virtual int get_appear_condition( void ){return appear_condition;}
        virtual void set_appear_condition(int appear_condition){this->appear_condition = appear_condition;}

        virtual int get_npc_type( void ){return npc_type;}
        virtual void set_npc_type(int /*dialog_id*/){this->npc_type = npc_type;}

        virtual int get_dialog_id( void ){return dialog_id;}
        virtual void set_dialog_id(int dialog_id){this->dialog_id = dialog_id;}


        virtual int get_trigger_rule( void ){return trigger_rule;}
        virtual void set_trigger_rule(int trigger_rule){this->trigger_rule = trigger_rule;}

        virtual std::string get_wait_action( void ){return wait_action;}
        virtual void set_wait_action(std::string /*dialog_id*/){this->wait_action = wait_action;}

        virtual int get_shop_id(int index)
        {
            if ( index < 0 || index >= MAX_SHOP_COUNT )
            {
                return -1;
            }

            return shop_id[index];
        }
        virtual void set_shop_id(int index, int shop_id_)
        {
            if ( index < 0 || index >= MAX_SHOP_COUNT )
            {
                return;
            }

            shop_id[index] = shop_id_;
        }

        int reset()
        {
            appear_condition = 0;
            npc_type		 = 0;
            dialog_id		 = 0;
            trigger_rule	 = 0;
            wait_action.clear();
            for (int i = 0; i < MAX_SHOP_COUNT; i++)
            {
                shop_id[i] = 0;
            }
            return 0;
        }

    private:
        int             static_character_id;            // 静态id
        int             face_mode_id;                   // 头像icon
        int             appear_condition;				// 出现条件
        int	            npc_type;						// 类型 (1对话NPC、2任务NPC、3商店NPC)
        int	            dialog_id;					    // 对话字典ID
        int	            trigger_rule;					// NPC触发规则
        std::string	    wait_action;			        // 待机动作
        int             shop_id[MAX_SHOP_COUNT];		// 商店id
    };
}


#endif /* __CommonNpc_DATA_H__ */

