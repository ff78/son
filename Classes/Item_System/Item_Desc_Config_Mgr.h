
#ifndef __Item_Desc_Config_Mgr_H__
#define __Item_Desc_Config_Mgr_H__

#include <map>

#include "Item_Config_Data.h"
#include "Acupoint_System/Acupoint_Config_Data.h"

namespace Game_Data
{
    enum Role_Attr_Type
    {
        RAT_HEALTH = 0,                 // ����
        RAT_MAGIC,                      // ���
        RAT_ATTACK,                     // ����
        RAT_DEFENSE,                    // ����
        RAT_HIT,                        // ����
        RAT_DODGE,                      // ����
        RAT_CRIT,                       // ����
        RAT_TENACITY,                   // ����
        RAT_HURT,                       // �����˺�
        RAT_HP_RECOBER,                 // �����ָ�
        RAT_MP_RECOBER,                 // ����ָ�
        RAT_MAGIC_SUB,                  // �������
        RAT_MAGIC_SPEED,                // ������
        RAT_POW,                        // �ķ�����

        RAT_MAX,                        //
    };

	class Item_Desc_Config_Mgr
	{
	public:
		Item_Desc_Config_Mgr();
		virtual ~Item_Desc_Config_Mgr();

        static Item_Desc_Config_Mgr* instance();

		int initialize(void);
	public:
		const char* get_string_by_id(int id);
        void show_alert(int desc_id);
		void show_alert(const char* desc);

        const char* get_quality_icon(int quality);
		const char* get_charactor_quality_circle_icon(int quality);
		const char* get_skill_circle_icon( int quality );
		const char* get_skill_square_icon( int quality);
        const char* get_quality_string(int quality);
        const char* get_attr_string(int attr_type);

        const char* get_vein_level_icon(int level);
        const char* get_vein_level_string(int level);

        const char* get_gem_inlay_string(int cur_item_quality,int need_item_quality);

	private:
        void init_quality_icon_data();
        void init_quality_desc_data();
        void init_attr_desc_data();
        void init_vein_level_icon_data();
        void init_vein_level_desc_data();
		int load_item_desc_data();

	private:
        static Item_Desc_Config_Mgr*            instance_;
		map<int, string>			            m_map_dictionary;

        int                                     m_quality_icon_id[QT_MAX+1];
		int										m_charactor_quality_circle_icon_id[QT_MAX + 1];
		int                                     m_skill_square_icon_id[QT_MAX+1];
		int                                     m_skill_circle_icon_id[QT_MAX+1];

        int                                     m_quality_desc_id[QT_MAX];
        int                                     m_attr_desc_id[RAT_MAX];
        
        int                                     m_vein_level_icon_id[VEIN_LEVEL_MAX];
        int                                     m_vein_level_desc_id[VEIN_LEVEL_MAX];
	};
}


typedef Game_Data::Item_Desc_Config_Mgr DICTIONARY_CONFIG_MGR;


#endif /* __Item_Desc_Config_Mgr_H__ */
