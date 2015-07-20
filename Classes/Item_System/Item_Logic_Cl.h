
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

		int GetTargetGemEquipPos(const int nCharacterID, const uint64 container_id);					// ��ȡĿ�걦ʯ����Ƕλ��

		bool JudgeMaterialIsExist(const int nCharacterID, const uint64 container_id);					// �ж�Ŀ������Ƿ����
		bool JudgeTargetItemIsGem(const int nCharacterID, const uint64 container_id);					// �ж�Ŀ����Ʒ�Ƿ�Ϊ��ʯ
		bool JudgeTargetPosIsOnEquip(const int nCharacterID , const int nEquipPos);						// �ж�λ���Ƿ��д���װ��
		bool JudgeTargetPosEquipCanFillInGem(const int nCharacterID, const int nEquipPos);				// �ж�Ŀ��λ�õ�װ���Ƿ������Ƕ��ʯ

		bool JudgeTargetGemCanCompound(const int nCharacterID, const uint64 nContainerID);				// �ж�Ŀ�걦ʯ�ǹ����Ժϳ�

		// �ж�Ŀ������Ƿ������Ƕ��ָ��װ����
		bool JudgeMaterialCanFillInTargetEquip(const int nCharacterID , const uint64 container_id, const int nEquipPos);		


		uint64 GetTargetPosEquipItemID(const int nCharacterID, const int nEquipPos);					// ��ȡĿ���ɫ��Ŀ��λ�õ�ContainerID
    private:
        static Item_Logic*         instance_;

    };
}

typedef Game_Data::Item_Logic ITEM_LOGIC;


#endif /* __ITEM_LOGIC_H__ */
