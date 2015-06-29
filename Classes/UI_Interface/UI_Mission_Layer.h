#ifndef _UI_MISSIOM_LAYER_
#define _UI_MISSIOM_LAYER_

#include "cocos2d.h"
//#include "cocos-ext.h"
//#include "UI/NPC.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIWidget.h"
#include "ui/UIScrollView.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
//USING_NS_CC_EXT;
//USING_NS_CC;
using namespace ui;
namespace Game_Data {
    struct game_quest_content;
    struct quest_data;
    struct Game_Element;
}

class UI_Icon_Info_Layer;
class UI_Mission_Layer : public cocos2d::Layer
{
public:
	enum
	{
		Page_Up = 0,
		Page_Down,
	};

	enum 
	{
		STATE_DALIY,
		STATE_CAN_ACCEPT,
		STATE_ALREADY_ACCEPT,
	};
	int			m_nMissionState;

	enum
	{
		MISSION_NUM_PER_PAGE = 2,	//每页只显示2个
	};
	UI_Mission_Layer(void);
	~UI_Mission_Layer(void);

	static UI_Mission_Layer* instance_;
public:
	CREATE_FUNC(UI_Mission_Layer);
	virtual bool init();
	virtual void setVisible( bool visible );

	static UI_Mission_Layer* get_instance();
public:
	void refreshUI();
	void refreshAcceptableMissionUI();
	void commonUIPart(Game_Data::quest_data* qd,int index);
	void buttonMissionAlreadyAccept( Ref* pSender ,Widget::TouchEventType type);
	void buttonMissionAbleAccept( Ref* pSender ,Widget::TouchEventType type);

private:
	void buttonCloseCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonDailyMission( Ref* pSender ,Widget::TouchEventType type);

	void btnCallback_Page( Ref* pSender ,Widget::TouchEventType type);
	void buttonGoNowCallback( Ref* pSender ,Widget::TouchEventType type);
	void btnAcceptMissionCallback( Ref* pSender ,Widget::TouchEventType type);
	void showInfoCallback( Ref* pSender ,Widget::TouchEventType type);
//	UI::NPC* getNPCByIndex(int index);

private:
	const char* get_npc_name    ( Game_Data::game_quest_content& ele_cont, const char* key_name );
	int get_monster_name        (Game_Data::Game_Element& ele_cont, const char* key_name, char* txt);
	int get_item_name           (Game_Data::Game_Element& ele_cont, const char* key_name, char* txt);
	int get_skill_name          (Game_Data::Game_Element& ele_cont, const char* key_name, char* txt);
	int get_instance_name       (Game_Data::Game_Element& ele_cont, const char* key_name, char* txt);
	int get_counter_name        (Game_Data::Game_Element& ele_cont,  char* txt);

private:
	cocos2d::ui::Widget*				m_pMissionWidget;

	struct
	{
		cocos2d::ui::ImageView*		m_pImgBkg;
		cocos2d::ui::Button*		m_pBtnGoNow;
		cocos2d::ui::Button*		m_pBtnAcceptMission;
		cocos2d::ui::TextField*			m_pLabMissionName;
		cocos2d::ui::Text*			m_pLabMissionInfo;

		cocos2d::ui::Text*			m_pLabPublishNPCName;
		cocos2d::ui::Text*			m_pLabSubmitNpcName;
		cocos2d::ui::Text*			m_pLabExperience;
		cocos2d::ui::Text*			m_pLabGoldCoin;
		cocos2d::ui::ImageView*		m_pImgAwardIconBack;
		cocos2d::ui::ImageView*		m_pImgAwardIcon;
		cocos2d::ui::Text*			m_pLabAwardIconNum;

        cocos2d::ui::Text*			m_pMissionMark;
        cocos2d::ui::Text*			m_pMissionName;
		//从字典里读取汉字
		cocos2d::ui::Text*			m_plab_mission_introducetext;
		cocos2d::ui::Text*			m_plab_mission_publish_npctext;
		cocos2d::ui::Text*			m_plab_mission_over_npctext;
		cocos2d::ui::Text*			m_plab_mission_rewordtext;
		cocos2d::ui::Text*			m_plab_mission_experiencetext;
		cocos2d::ui::Text*			m_plab_mission_goldtext;

	} m_UI[MISSION_NUM_PER_PAGE];
	
	cocos2d::ui::Button*		m_pBtnPageUp;
	cocos2d::ui::Button*		m_pBtnPageDown;

	cocos2d::ui::Text*			m_pLabTitle;

	int					m_nCurrentPage;

	cocos2d::ui::Button*			mission_already_accept;
	cocos2d::ui::Button*			mission_able_accept;
	cocos2d::ui::Button*			daily_mission;

	//Icon 信息显示框
	UI_Icon_Info_Layer*	m_pLayerIconInfo;
};


#endif //_UI_MISSIOM_LAYER_
