#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Game_Interface/common.h"
#include "../Item_System/Item_Mgr_Cl.h"
#include "../Item_System/Item_Desc_Config_Mgr.h"
#include "../Item_System/Item_Logic_Cl.h"
#include "../Item_Container_System/Item_Container_Mgr_Cl.h"

#define ROW_NUM 5
#define COL_NUM 4

#define BAR_NUM 8 //װ��������

#define INDEX_0 1
#define INDEX_1 2
#define INDEX_2 4

// ��ҳ���ҳ��״̬
enum Child_Layer_State
{
	Layer_State_Gem,					  // ��ʯ��Ƕ����
	Layer_State_Strengthen,				  // ��ʯǿ������
	Layer_State_StarUp,					  // ��ʯ���ǽ���
	Layer_State_Wash,					  // ��ʯϴ������

	Layer_State_Max
};


USING_NS_CC;
class UI_Bag_Gem_Layer;
class UI_Equipment_Gem_Layer;

class UI_Bag_Info_Layer : public cocos2d::Layer
{
public:
	/** ==================================== Datas ==================================== */
	static Value sIsProperty;
	static Value sCurPageIdx;
	static Value sGold;
	static Value sToken;
	static Value sName;
	static Value sPower;
	static Value sExp;
	static Value sHP;
	static Value sAtk;
	static Value sGuard;
	static Value sMP;
	static Value sLevel;
	static Value sJob;
	static Value sJobStrings[];
	bool initData();
	
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, curPageNum, CurPageNum);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Text*, goldAtlas, GoldAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Text*, tokenAtlas, TokenAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Text*, nameTxt, NameTxt);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, powerAtlas, PowerAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, hpAtlas, HpAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, atkAtlas, AtkAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, guardAtlas, GuardAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, mpAtlas, MpAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, levelAtlas, LevelAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Text*, jobTxt, JobTxt);
	/** ==================================== Datas ==================================== */

	//int                 m_gem_id[SET_GEM_COUNT];
	void update();
	void updateBag();
	void updateBar();
	void updateFoldable(Game_Data::Item_Container* con);
	void updateUnfoldable(Game_Data::Item_Container* con);

	void removeAll(Game_Data::Item_Container* con);
	void updateEquips(int index,int type,/* int count,*/ int quality, int icon, bool isBag);
	void removeEquips(int index, bool isBag);
	void updateEntities(int index, int type,/* int count,*/ /*int quality,*/ int icon, bool isBag);
	void removeEntities(int index, bool isBag);
	void updateMaterials(int index, int type,/*int count,*/ /*int quality,*/ int icon, int count,bool isBag);
	void removeMaterials(int index, bool isBag);

	void OpenBagInfoLayer(const bool bValue = false);														// �򿪱�����Ϣ����
	void RequestCharacterTargetPosEquipInfo(const int nCharacterID, const int nEquipPos);					// ����Ŀ���ɫ��Ŀ��λ��װ����Ϣ��ֻ����������ϵģ�
	void RequestTargetEquipInfo(const uint64 nItemId, const int nEquipPos, const Child_Layer_State eType);	// �����Ŀ��װ����Ϣ���棨����������������ϵģ�
	void RefreshGemLayer();																					// ˢ�±�ʯ����
	void ChangeLayerState(const Child_Layer_State eType);													// �л�ҳ��״̬

	/** ==================================== members ==================================== */
	int m_nCurrentEquipTag;

	std::vector<uint64> mPara;

	uint64 m_bag_container_id[ROW_NUM*COL_NUM];
	uint64 m_bag_equip_id[ROW_NUM*COL_NUM];

	void initBagGrid();
	void initBarGrid();
	//���� ͷ�� ��Ϣ ��ˢ��ʱӦ�õ��ô˺�����

	void setTypeIndex(int index);

	cocos2d::ui::ImageView*	 equips[ROW_NUM][COL_NUM];	//����������װ��
	cocos2d::ui::ImageView*	 entities[ROW_NUM][COL_NUM];	//������������Ʒ
	cocos2d::ui::ImageView*	 materials[ROW_NUM][COL_NUM];	//���������в���

	cocos2d::ui::ImageView*  m_img_equipment_bar[BAR_NUM];//װ����
	uint64 m_bar_ids[BAR_NUM];
	uint64 mCurItemId;
	int    mCurIndex;


	CC_SYNTHESIZE_READONLY(cocos2d::ui::Widget*,root,Root);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, closeBtn, CloseBtn);

	CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, equBtn, EquBtn);          //ҳ��
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, entityBtn, EntityBtn);    //ҳ��
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, materialBtn, MaterialBtn);//ҳ��

	CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, wearBtn, WearBtn);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, unwearBtn, UnwearBtn);

	CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, refine, Refine);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, refineLeft, RefineLeft);

	CC_SYNTHESIZE(cocos2d::ui::ScrollView*, rightScroll, RightScroll);

	CC_SYNTHESIZE(int,rowNum,RowNum);
	CC_SYNTHESIZE(int, colNum, ColNum);
	/** ==================================== members ==================================== */

	/** ==================================== Callbacks ==================================== */
	void tidyCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void sellEquipCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void headCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);

	void closeCompareCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void closePropertyCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void closeUseCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void closeBagCallBack(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);

	void equipmentCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void entityCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void materialCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void cellEquCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void cellEntityCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void cellMaterialCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void cellBarCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	
	void wearCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void unwearCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void refineCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	/** ==================================== Callbacks ==================================== */

	virtual void setVisible(bool visible);

	bool initRoot();

	virtual bool init();

	CREATE_FUNC(UI_Bag_Info_Layer);

	UI_Bag_Info_Layer(void);

};