#ifndef __UI_MISSION_DIALOGUE_LAYER__
#define __UI_MISSION_DIALOGUE_LAYER__
#include <deque>
#include <string>

#include "cocos2d.h"
//#include "cocos-ext.h"

#include "Common/GameDefine.h"
#include "Common/GameMacro.h"

#include "Game_Interface/common.h"
#include "UI_MainMenu_Layer.h"
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
#define  OPEN_NUM		5

//USING_NS_CC;
//USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;
namespace Game_Data
{
    struct quest_data;
}
#define MISSION_DIALOGUE_OPTION			3

class UI_Icon_Info_Layer;
class Joiner_Guidance;
class UI_MissionDialogue_Layer : public cocos2d::Layer
{
	enum DialogueState
	{
		DS_NpcDialogue = 0,
		DS_Mission,

		DS_Num
	};

	struct ServiceData
	{
		ServiceData(NpcServiceType Type,int ID,const char* Caption)
		:nType(Type)
		,nID(ID)
		,strCaption(Caption)
		{
		}
		NpcServiceType nType;
		int nID;
		std::string strCaption;

	};

public:
	CREATE_FUNC(UI_MissionDialogue_Layer);
	UI_MissionDialogue_Layer(void);
	~UI_MissionDialogue_Layer(void);

public:
	virtual bool init();
	virtual void setVisible( bool visible );
	void showGuide();

public:
	void showDialogueWithNpcTypeID( int nTypeID );
	void updateDetail();
	void update(int mission_id);
private:
    void btnCallback_Close( Ref* pSender,Widget::TouchEventType type );
	void btnCallback_SelectOption( Ref* pSender ,Widget::TouchEventType type);
   

    int proc_quest_select_list( void );
    int proc_quest_select(NpcServiceType Type,std::vector<uint32> vecQuest);
    int proc_quest_selected( void );
    const char* get_string( int id );

    const char* get_quest_dialog_txt( Game_Data::quest_data& qd, int type );
    int display_npc_dialog( Game_Data::quest_data& qd, const ServiceData& refData );
    int displayer_quest_award( Game_Data::quest_data& qd);
    int get_quest_name( Game_Data::quest_data& qd, char* txt );
    int get_npc_dialog_quest_state_txt(Game_Data::quest_data& qd, int type, char* txt);

	void executeTask(int index);

	void showIconInfo(Ref* pSender,Widget::TouchEventType type);

	cocos2d::ui::Widget*				m_pWidget;
	cocos2d::ui::Button*				m_pBtnClose;
	#if 0
	CCSkeletonAnimation*	m_pAvatar;
	#endif
//	cocos2d::ui::Text*				m_pTxtDialogue;
	//cocos2d::ui::Layout*				m_pAwardPanel;
	cocos2d::ui::Text*				m_pExperience;
	cocos2d::ui::Text*				m_pMoneyNum;
	
	//cocos2d::ui::ImageView*			m_pImgIconBack;
	cocos2d::ui::ImageView*			m_pImgOfAwardGoods;
	cocos2d::ui::Text*				m_pLabOfAwardGoodsNum;

	Sequence*						_effectSequence;
	Sprite*							_effectSprite;
	void hideEffectSprite();
	//int							m_nNpcID;
	//int							m_nCurrSelectID;

	DialogueState				m_State;
	std::vector<ServiceData>	m_vecServiceData;

	//滑动层 及其附属控件
	//cocos2d::ui::ScrollView*			m_pScrollView;
	//cocos2d::ui::Layout*				m_pMissionScrollPanel;
	//cocos2d::ui::Text*				m_pMissionName[NPC_DIALOGUE_OPTION];
	//cocos2d::ui::ImageView*			m_pMissionState[NPC_DIALOGUE_OPTION];
	//cocos2d::ui::Button*				m_pMissionButton[NPC_DIALOGUE_OPTION];



	//奖励物品的id
	int							awardGoodId_;
    int							awardGoodCount_;    // 个数


	Joiner_Guidance*			juniorGuide;

private:
	enum guide_step
	{
		JUNIOR_GUIDE_STEP_2 = 2,
		JUNIOR_GUIDE_STEP_3 = 3,
		JUNIOR_GUIDE_STEP_4 = 4,
		JUNIOR_GUIDE_STEP_13 = 13,
		JUNIOR_GUIDE_STEP_14 = 14,
		JUNIOR_GUIDE_STEP_15 = 15,
	};
};

#endif //__UI_NPC_DIALOGUE_LAYER__
