

#ifndef __ITEM_CONFIG_DATA_H__
#define __ITEM_CONFIG_DATA_H__

#include <string>
#include <map>
#include <list>
#include <vector>

#include "Network_Common/global_macros.h"
#include "Game_Interface/game_element.h"

#define EQUIPMENT_UPGRADE_BASE_COST                 80
#define EQUIPMENT_UPGRADE_COST_COEFFICIENT          100

#define TIDY_ITEM_TIME                              5

using namespace std;
namespace Game_Data
{
    // Ʒ��
    enum Quality_Type
    {
		QT_WHITE = 0,                   // ��ɫ
		QT_RED,							// ��ɫ
		QT_BLACK,						// ��ɫ
		QT_GREY,						// ��ɫ
		QT_YELLOW,						// ��ɫ
		QT_GREEN,                       // ��ɫ
		QT_BLUE,                        // ��ɫ
		QT_PURPLE,                      // ��ɫ
		QT_ORANGE,                      // ��ɫ

		QT_MAX,                         // 
    };

    // Ʒ��ģ������
    enum Quality_Module_Type
    {
        QMT_ROLE = 0,                   // ����
        QMT_EQUIPMENT,                  // װ��
        QMT_BOOK,                       // �ķ��鼮

        QMT_MAX,                        // 
    };

    // ��������
    enum Item_Type
    {
        IT_EQUIPMENT_DEPOT = 0,         // װ����
        IT_EQUIPMENT,                   // װ��
        IT_USABLE_ITEM,                 // ��ʹ��
        IT_MATERIAL_ITEM,               // ����
        IT_QUEST_ITEM,                  // ������Ʒ
        IT_BOOK,                        // �ķ��鼮
        IT_BOOK_FRAGMENT,               // �ķ���Ҷ
        IT_MATERIAL_FRAGMENT,           // ������Ƭ
        IT_GIFT_ITEM,                   // ���
        IT_GEM,                         // ��ʯ
    };

    // ���߰�״̬
    enum Item_Bind_State
    {
        IBS_NOT_BIND = 0,               // ����
        IBS_GOT_BIND,                   // ʰȡ��
        IBS_USED_BIND,                  // ʹ�ð�
    };

    // ��ʯ����
    enum Gem_Type
    {
        GT_ATK = 1,                     // ������ʯ
        GT_DEF,                         // ������ʯ
        GT_HP,                          // ��Ѫ��ʯ
        GT_DOD,                         // ���ܱ�ʯ
        GT_HIT,                         // ���б�ʯ
    };

    // �������ɷ�ʽ
    enum Item_Create_Way
    {
        ICW_DROP = 1,                   // ����
        ICW_BUY,                        // ����
        ICW_PRESENT,                    // ϵͳ����
        ICW_COMPOUND,                   // �ϳ�
        ICW_GM_COMMAND,                 // GM�������
    };

    // ���ߴݻٷ�ʽ
    enum Item_Destroy_Way
    {
        IDW_NORMAL = 0,                 // ����
        IDW_USED,                       // ʹ��
        IDW_MAKE,                       // �ϳ�
        IDW_SELL,                       // ����
        IDW_DISCARD,                    // ����
        IDW_TIME_OUT,                   // ��ʱ
        IDW_PILE,                       // �ѵ�
        IDW_QUEST,                      // ����
    };

    // װ�����λ��
    enum Equipment_Pos
    {
		EP_WEAPON= 0,                   // ����
        EP_ARMOUR,                      // �·�
        EP_BOOTS,                       // Ь��
		EP_NECKLACE,					// ����
		EP_BELT,						// ����
		EP_PANTS,						// ����
		EP_HELMET,                      // ͷ��
        EP_ORNAMENT,                    // ��Ʒ
		EP_ORNAMENT2,                   // ��Ʒ
        EP_FASHION,                     // ʱװ

        EP_MAX,                         // 
    };

    // �ķ��鼮���λ��
    enum Book_Pos
    {
        

        BP_MAX = 6,                         // 
    };

    // װ����������
    enum Equipment_Attr_Type
    {
        EAT_HEALTH = 0,                 // ����
        EAT_MAGIC,                      // ���
        EAT_ATTACK,                     // ����
        EAT_DEFENSE,                    // ����
        EAT_HIT,                        // ����
        EAT_DODGE,                      // ����
        EAT_CRIT,                       // ����
        EAT_TENACITY,                   // ����
        EAT_HURT,                       // �����˺�
    };

    // װ����������
    enum Item_Load_Type
    {
        ILT_BAG = 0,                    // ���ر���
        ILT_BOOK_BAG,                   // �����ķ�
        ILT_STORE,                      // ���زֿ�
    };

    // �������
    enum Gift_Type
    {
        GT_RANDOM = 1,                  // ���һ�ֽ���
        GT_ALL,                         // ����������Ʒ
    };

    struct Item_Config
    {
        int                     base_id;                    // ��ID
        int                     type;                       // ���ͣ�1��װ����2������Ʒ��3�����ϣ�4��������Ʒ��5���ķ��鼮��6���ķ���ҳ��
        int                     name;                       // ����
        int                     icon;                       // ͼ��
        int                     quality;                    // Ʒ�ʣ�0���ף�1���̣�2������3���ϣ�4���ȣ�
        int                     desc;                       // ˵��
        int                     drop_desc;                  // ����˵��
        int                     bind;                       // ��״̬��0�����󶨣�1��ʰȡ�󶨣�2��ʹ�ð󶨣�
        int                     pile_count;                 // �ɶѵ�����
        int                     gold_cost;                  // ��ҹ��򻨷�
        int                     token_cost;                 // ���ҹ��򻨷�
        int                     sell_income;                // ��������
        int					    can_sell;                   // �ɷ����
        int					    can_auction;                // �ɷ����
        int					    can_trade;                  // �ɷ���
        int					    can_store;                  // �ɷ��Ųֿ�
        int					    can_pile;                   // �ɷ�ѵ�
        int					    can_destroy;                // �ɷ�ݻ�
        int					    destroy_time;               // ���ߴݻ�ʱ��(��)
        int					    sort;                       // �������
    };

    // װ����
    struct Equipment_Depot_Config:Item_Config
    {
        int                     level;                      // �ȼ�
        int                     item_base_id;               // װ�����ķ��ı�ID
    };

    // ��Ƭ
    struct Item_Fragment_Config:Item_Config
    {
        int                     need_count;                 // �ϳ�����������Ҫ�ĸ���
        int                     compound_id;                // �ϳ��������ߵı�ID
    };

    // װ��
    struct Equipment_Config:Item_Config
    {
        int                     occupation;                 // ƥ��ְҵ
        int                     pos;                        // װ��λ�ã�0��������1���·���2��Ь�ӣ�3��������4��������5������, 6:ͷ�� ,7:��Ʒ, 8:��Ʒ 9:ʱװ��
        int                     upgrade_cost_coefficient;   // ��������ϵ��
        int                     base_attr[MAX_ATTR_COUNT];         // װ����������
        int                     attr_level_grow[MAX_ATTR_COUNT];   // �������Գɳ�
        int                     attr_quality_grow[QT_MAX];  // ��Ʒ���Գɳ�
    };

    // ��ʹ�õ���
    struct Usable_Item_Config:Item_Config
    {
        int                     event_id;                   // �����¼�ID
    };

    // �ķ��鼮
    struct Book_Config:Item_Config
    {
        int                     exp;                                // �ṩ�ľ���
        int                     need_power;                         // ����������
        int                     upgrade_base_exp[QT_MAX];           // Ʒ�ʶ�Ӧ��������������
        int                     base_attr[QT_MAX][MAX_ATTR_COUNT];  // �ķ���������
        int                     max_level[QT_MAX];                  // Ʒ�ʶ�Ӧ�����ȼ�
        int                     upgrade_exp_grow[QT_MAX];           // Ʒ�ʶ�Ӧ����������ĳɳ�
        int                     attr_grow[QT_MAX][MAX_ATTR_COUNT];  // Ʒ�ʶ�Ӧ���Եĳɳ�
    };

    // ��ʯ
    struct Gem_Config:Item_Config
    {
        int                     gem_type;                   // ����
        int                     level;                      // �ȼ�
        int                     upgrade_cost;               // �ϳɻ���
        int                     set_equipment_pos;          // ��Ƕλ��
        int                     attr_type;                  // ��������
        int                     attr_value;                 // ������ֵ
        int                     need_count;                 // �ϳɱ�ʯ��Ҫ�ĸ���
        int                     compound_id;                // �ϳɱ�ʯ�ı�ID
    };

    struct item_content
    {		
        item_content() 
        {
            item_element_vec_.clear();
        }

        ~item_content() {}

        void reset()
        {
            item_element_vec_.clear();
        }

        item_content(const item_content& ic) 
        {
            item_element_vec_.clear();
            item_element_vec_ = ic.get_element();
        }

        item_content & operator = (const item_content& ic)
        {
            item_element_vec_.clear();
            item_element_vec_ = ic.get_element();
            return *this;
        }	
        void set_element(const game_element_list_t& gev) {item_element_vec_.clear(); item_element_vec_ = gev;}
        void get_element(game_element_list_t& gev) {gev.clear(); gev = item_element_vec_;}
        const game_element_list_t get_element() const {return item_element_vec_;}

    private:
        game_element_list_t item_element_vec_;
    };

    struct quality_upgrade_config
    {
        quality_upgrade_config()
            :module_type_(-1),
            quality_(-1),
            token_(0)
        {
            material_.reset();
        }

        ~quality_upgrade_config() {}

        void reset()
        {
            module_type_ = -1;
            quality_ = -1;
            token_ = 0;
            material_.reset();
        }

        quality_upgrade_config & operator = (const quality_upgrade_config& quc)
        {
            module_type_ = quc.get_module_type();
            quality_ = quc.get_quality();
            token_ = quc.get_token();
            material_ = quc.get_material();
            
            return *this;
        }
        
        void set_module_type(int module_type){module_type_ = module_type;}
        int get_module_type() const { return module_type_; }

        void set_quality(int quality){quality_ = quality;}
        int get_quality() const { return quality_; }

        void set_token(int token){token_ = token;}
        int get_token() const { return token_; }

        void set_material(const item_content& ic){material_ = ic;}
        void get_material(item_content& ic){ic = material_;}
        const item_content get_material() const {return material_;}

    private:
        int module_type_;
        int quality_;
        int token_;
        item_content material_;
    };

    typedef map<int, Item_Config*>                      Item_Config_Map;
    typedef Item_Config_Map::iterator		            Item_Config_Map_Iter;

    typedef map<int, Equipment_Depot_Config*>           Equipment_Depot_Config_Map;
    typedef Equipment_Depot_Config_Map::iterator		Equipment_Depot_Config_Map_Iter;

    typedef map<int, Item_Fragment_Config*>             Item_Fragment_Config_Map;
    typedef Item_Fragment_Config_Map::iterator		    Item_Fragment_Config_Map_Iter;

    typedef map<int, Equipment_Config*>                 Equipment_Config_Map;
    typedef Equipment_Config_Map::iterator		        Equipment_Config_Map_Iter;

    typedef map<int, Usable_Item_Config*>               Usable_Item_Config_Map;
    typedef Usable_Item_Config_Map::iterator		    Usable_Item_Config_Map_Iter;

    typedef map<int, Book_Config*>                      Book_Config_Map;
    typedef Book_Config_Map::iterator		            Book_Config_Map_Iter;

    typedef map<int, Gem_Config*>                       Gem_Config_Map;
    typedef Gem_Config_Map::iterator		            Gem_Config_Map_Iter;

	typedef map<int,std::string>						Icon_Map;
	typedef Icon_Map::iterator							Icon_Map_Iter;
}

#endif /* __ITEM_CONFIG_DATA_H__ */

