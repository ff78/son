

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
    // 品质
    enum Quality_Type
    {
		QT_WHITE = 0,                   // 白色
		QT_RED,							// 红色
		QT_BLACK,						// 黑色
		QT_GREY,						// 灰色
		QT_YELLOW,						// 黄色
		QT_GREEN,                       // 绿色
		QT_BLUE,                        // 蓝色
		QT_PURPLE,                      // 紫色
		QT_ORANGE,                      // 橙色

		QT_MAX,                         // 
    };

    // 品质模块类型
    enum Quality_Module_Type
    {
        QMT_ROLE = 0,                   // 人物
        QMT_EQUIPMENT,                  // 装备
        QMT_BOOK,                       // 心法书籍

        QMT_MAX,                        // 
    };

    // 道具类型
    enum Item_Type
    {
        IT_EQUIPMENT_DEPOT = 0,         // 装备库
        IT_EQUIPMENT,                   // 装备
        IT_USABLE_ITEM,                 // 可使用
        IT_MATERIAL_ITEM,               // 材料
        IT_QUEST_ITEM,                  // 任务物品
        IT_BOOK,                        // 心法书籍
        IT_BOOK_FRAGMENT,               // 心法残叶
        IT_MATERIAL_FRAGMENT,           // 材料碎片
        IT_GIFT_ITEM,                   // 礼包
        IT_GEM,                         // 宝石
    };

    // 道具绑定状态
    enum Item_Bind_State
    {
        IBS_NOT_BIND = 0,               // 不绑定
        IBS_GOT_BIND,                   // 拾取绑定
        IBS_USED_BIND,                  // 使用绑定
    };

    // 宝石类型
    enum Gem_Type
    {
        GT_ATK = 1,                     // 攻击宝石
        GT_DEF,                         // 防御宝石
        GT_HP,                          // 气血宝石
        GT_DOD,                         // 闪避宝石
        GT_HIT,                         // 命中宝石
    };

    // 道具生成方式
    enum Item_Create_Way
    {
        ICW_DROP = 1,                   // 掉落
        ICW_BUY,                        // 购买
        ICW_PRESENT,                    // 系统赠送
        ICW_COMPOUND,                   // 合成
        ICW_GM_COMMAND,                 // GM命令添加
    };

    // 道具摧毁方式
    enum Item_Destroy_Way
    {
        IDW_NORMAL = 0,                 // 正常
        IDW_USED,                       // 使用
        IDW_MAKE,                       // 合成
        IDW_SELL,                       // 卖店
        IDW_DISCARD,                    // 丢弃
        IDW_TIME_OUT,                   // 超时
        IDW_PILE,                       // 堆叠
        IDW_QUEST,                      // 任务
    };

    // 装备佩戴位置
    enum Equipment_Pos
    {
		EP_WEAPON= 0,                   // 武器
        EP_ARMOUR,                      // 衣服
        EP_BOOTS,                       // 鞋子
		EP_NECKLACE,					// 项链
		EP_BELT,						// 腰带
		EP_PANTS,						// 裤子
		EP_HELMET,                      // 头盔
        EP_ORNAMENT,                    // 饰品
		EP_ORNAMENT2,                   // 饰品
        EP_FASHION,                     // 时装

        EP_MAX,                         // 
    };

    // 心法书籍佩戴位置
    enum Book_Pos
    {
        

        BP_MAX = 6,                         // 
    };

    // 装备属性类型
    enum Equipment_Attr_Type
    {
        EAT_HEALTH = 0,                 // 生命
        EAT_MAGIC,                      // 罡气
        EAT_ATTACK,                     // 攻击
        EAT_DEFENSE,                    // 防御
        EAT_HIT,                        // 命中
        EAT_DODGE,                      // 闪避
        EAT_CRIT,                       // 暴击
        EAT_TENACITY,                   // 坚韧
        EAT_HURT,                       // 暴击伤害
    };

    // 装备属性类型
    enum Item_Load_Type
    {
        ILT_BAG = 0,                    // 加载背包
        ILT_BOOK_BAG,                   // 加载心法
        ILT_STORE,                      // 加载仓库
    };

    // 礼包类型
    enum Gift_Type
    {
        GT_RANDOM = 1,                  // 随机一种奖励
        GT_ALL,                         // 奖励所有物品
    };

    struct Item_Config
    {
        int                     base_id;                    // 表ID
        int                     type;                       // 类型（1：装备，2：消耗品，3：材料，4：任务物品，5：心法书籍，6：心法残页）
        int             name;                       // 名称
        int             icon;                       // 图标
        int                     quality;                    // 品质（0：白，1：绿，2：蓝，3：紫，4：橙）
        int             desc;                       // 说明
        int             drop_desc;                  // 出处说明
        int                     bind;                       // 绑定状态（0：不绑定，1：拾取绑定，2：使用绑定）
        int                     pile_count;                 // 可堆叠个数
        int                     gold_cost;                  // 金币购买花费
        int                     token_cost;                 // 代币购买花费
        int                     sell_income;                // 出售收入
        int					    can_sell;                   // 可否出售
        int					    can_auction;                // 可否寄卖
        int					    can_trade;                  // 可否交易
        int					    can_store;                  // 可否存放仓库
        int					    can_pile;                   // 可否堆叠
        int					    can_destroy;                // 可否摧毁
        int					    destroy_time;               // 道具摧毁时间(秒)
        int					    sort;                       // 排序规则
    };

    // 装备库
    struct Equipment_Depot_Config:Item_Config
    {
        int                     level;                      // 等级
        int                     item_base_id;               // 装备，心法的表ID
    };

    // 碎片
    struct Item_Fragment_Config:Item_Config
    {
        int                     need_count;                 // 合成完整道具需要的个数
        int                     compound_id;                // 合成完整道具的表ID
    };

    // 装备
    struct Equipment_Config:Item_Config
    {
        int                     occupation;                 // 匹配职业
        int                     pos;                        // 装备位置（0：武器，1：衣服，2：鞋子，3：项链，4：腰带，5：裤子, 6:头盔 ,7:饰品, 8:饰品 9:时装）
        int                     upgrade_cost_coefficient;   // 升级花费系数
        int                     base_attr[MAX_ATTR_COUNT];         // 装备基础属性
        int                     attr_level_grow[MAX_ATTR_COUNT];   // 升级属性成长
        int                     attr_quality_grow[QT_MAX];  // 升品属性成长
    };

    // 可使用道具
    struct Usable_Item_Config:Item_Config
    {
        int                     event_id;                   // 触发事件ID
    };

    // 心法书籍
    struct Book_Config:Item_Config
    {
        int                     exp;                                // 提供的经验
        int                     need_power;                         // 穿戴需求功力
        int                     upgrade_base_exp[QT_MAX];           // 品质对应的升级基础经验
        int                     base_attr[QT_MAX][MAX_ATTR_COUNT];  // 心法基础属性
        int                     max_level[QT_MAX];                  // 品质对应的最大等级
        int                     upgrade_exp_grow[QT_MAX];           // 品质对应的升级经验的成长
        int                     attr_grow[QT_MAX][MAX_ATTR_COUNT];  // 品质对应属性的成长
    };

    // 宝石
    struct Gem_Config:Item_Config
    {
        int                     gem_type;                   // 类型
        int                     level;                      // 等级
        int                     upgrade_cost;               // 合成花费
        int                     set_equipment_pos;          // 镶嵌位置
        int                     attr_type;                  // 属性类型
        int                     attr_value;                 // 属性数值
        int                     need_count;                 // 合成宝石需要的个数
        int                     compound_id;                // 合成宝石的表ID
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

