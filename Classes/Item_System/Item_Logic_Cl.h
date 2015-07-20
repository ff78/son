
#ifndef __ITEM_LOGIC_H__
#define __ITEM_LOGIC_H__

#include <list>

#include "Item_Data.h"

using namespace std;
namespace Game_Data
{
    class Item_Logic
    {
    public:
        Item_Logic();
        virtual ~Item_Logic();

        static Item_Logic* instance();

    public:
        void load_item();
        void load_material_fragment();
        void load_book_fragment();
        void tidy_item();
        bool equip_equipment(int character_id,uint64 container_id);
        Game_Data::Item* can_change_equip(uint64 container_id); //ff
        void take_off_equipmen(int character_id,uint64 item_id);
        bool equip_book(int character_id,uint64 container_id);
        void take_off_book(int character_id,uint64 item_id);
        bool equipment_level_up(uint64 item_id);
        void equipment_quality_up(uint64 item_id);
        bool book_level_up(uint64 item_id,std::list<uint64>* list_item_id);
        void book_quality_up(uint64 item_id);
        void sell_item(uint64 container_id,int count);
        void use_item(uint64 container_id);
        void compound_material_fragment(int item_base_id,int compound_count);
        void compound_book_fragment(int item_base_id,int compound_count);
        void set_on_gem(int character_id,uint64 container_id);
        void set_off_gem(uint64 item_id,int gem_pos);
        void gem_level_up(int gem_id,int time);

        void buy_item(int goods_id,int count);

		int GetTargetGemEquipPos(const int nCharacterID, const uint64 container_id);					// 获取目标宝石的镶嵌位置

		bool JudgeMaterialIsExist(const int nCharacterID, const uint64 container_id);					// 判断目标材料是否存在
		bool JudgeTargetItemIsGem(const int nCharacterID, const uint64 container_id);					// 判断目标物品是否为宝石
		bool JudgeTargetPosIsOnEquip(const int nCharacterID , const int nEquipPos);						// 判断位置是否有穿戴装备
		bool JudgeTargetPosEquipCanFillInGem(const int nCharacterID, const int nEquipPos);				// 判断目标位置的装备是否可以镶嵌宝石

		bool JudgeTargetGemCanCompound(const int nCharacterID, const uint64 nContainerID);				// 判断目标宝石是够可以合成

		// 判断目标材料是否可以镶嵌到指定装备上
		bool JudgeMaterialCanFillInTargetEquip(const int nCharacterID , const uint64 container_id, const int nEquipPos);		


		uint64 GetTargetPosEquipItemID(const int nCharacterID, const int nEquipPos);					// 获取目标角色的目标位置的ContainerID
    private:
        static Item_Logic*         instance_;

    };
}

typedef Game_Data::Item_Logic ITEM_LOGIC;


#endif /* __ITEM_LOGIC_H__ */
