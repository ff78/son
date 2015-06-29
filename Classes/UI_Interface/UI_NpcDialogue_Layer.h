#ifndef __UI_NPC_DIALOGUE_LAYER__
#define __UI_NPC_DIALOGUE_LAYER__
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

namespace Game_Data
{
    struct quest_data;
}


enum DialogueState
{
	DS_NpcDialogue = 0,
	DS_Mission,

	DS_Num
};


enum guide_step
{
	JUNIOR_GUIDE_STEP_2 = 2,
	JUNIOR_GUIDE_STEP_3 = 3,
	JUNIOR_GUIDE_STEP_4 = 4,
	JUNIOR_GUIDE_STEP_13 = 13,
	JUNIOR_GUIDE_STEP_14 = 14,
	JUNIOR_GUIDE_STEP_15 = 15,
};


struct ServiceData
{
	ServiceData(NpcServiceType Type, int ID, const char* Caption)
	:nType(Type)
	, nID(ID)
	, strCaption(Caption)
	{
	}
	NpcServiceType nType;
	int nID;
	std::string strCaption;

};


struct Compare
{
	bool operator ()(const ServiceData& a, const ServiceData& b)
	{
		return a.nType<b.nType;
	}
};

USING_NS_CC;
using namespace ui;

class UI_Icon_Info_Layer;
class Joiner_Guidance;

class UI_NpcDialogue_Layer : public cocos2d::Layer
{
public:
	CREATE_FUNC(UI_NpcDialogue_Layer);
	UI_NpcDialogue_Layer(void);
	~UI_NpcDialogue_Layer(void);

public:
	virtual bool init();
	virtual void setVisible( bool visible );
	void showGuide();

private:
	//---成员变量---//
	int									m_nNpcID;
	int									m_nCurrSelectID;
	int									awardGoodId_;		// 奖励物品的id
	int									awardGoodCount_;    // 个数

	DialogueState						m_State;
	std::vector<ServiceData>			m_vecServiceData;

	Joiner_Guidance*					juniorGuide;
	UI_Icon_Info_Layer*					m_pLayerIconInfo;	//Icon 信息显示框

public:
	void								showDialogueWithNpcTypeID( int nTypeID );
	void								updateDetail();

private:

	int									proc_quest_select_list(void);
	int									proc_quest_select(NpcServiceType Type, std::vector<uint32> vecQuest);
	int									proc_quest_selected(void);

	int									display_npc_dialog(Game_Data::quest_data& qd, const ServiceData& refData);
	int									displayer_quest_award(Game_Data::quest_data& qd);
	int									get_quest_name(Game_Data::quest_data& qd, char* txt);
	int									get_npc_dialog_quest_state_txt(Game_Data::quest_data& qd, int type, char* txt);

	void								executeTask(int index);
	void								showIconInfo(Ref* pSender,Widget::TouchEventType type);

	const char*							get_string(int id);
	const char*							get_quest_dialog_txt(Game_Data::quest_data& qd, int type);
private:
	//---按钮方法回调---//
	void								btnCallback_Close(Ref* pSender, Widget::TouchEventType type);
	void								btnCallback_SelectOption(Ref* pSender, Widget::TouchEventType type);

private:
	//---Cocostudio文件---//
	cocos2d::ui::Widget*				m_pWidget;
	cocos2d::ui::Button*				m_pBtnClose;

	cocos2d::ui::Text*					m_pTxtDialogue;				// 任务描述
	cocos2d::ui::Layout*				m_pAwardPanel;
	cocos2d::ui::Text*					m_pExperience;
	cocos2d::ui::Text*					m_pMoneyNum;
	
	cocos2d::ui::ImageView*				m_pImgIconBack;
	cocos2d::ui::ImageView*				m_pImgOfAwardGoods;
	cocos2d::ui::Text*					m_pLabOfAwardGoodsNum;

	cocos2d::ui::ScrollView*			m_pScrollView;
	cocos2d::ui::Text*					m_pMissionName[NPC_DIALOGUE_OPTION];
	cocos2d::ui::ImageView*				m_pMissionState[NPC_DIALOGUE_OPTION];
	cocos2d::ui::Button*				m_pMissionButton[NPC_DIALOGUE_OPTION];
};

#endif //__UI_NPC_DIALOGUE_LAYER__
