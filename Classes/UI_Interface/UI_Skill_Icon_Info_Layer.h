#ifndef __UI_SKILL_ICON_INFO_LAYER__
#define __UI_SKILL_ICON_INFO_LAYER__

#include "cocos2d.h"
//#include "cocos-ext.h"
#include "Skill_System/Skill/Technical_Mgr.h"
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
using namespace ui;
#define  ICON_NUM   6

USING_NS_CC;
//USING_NS_CC_EXT;

class UI_Skill_Icon_Info_Layer : public cocos2d::Layer
{
private:
	UI_Skill_Icon_Info_Layer(void);
	~UI_Skill_Icon_Info_Layer(void);

public:
	virtual bool init();
	CREATE_FUNC(UI_Skill_Icon_Info_Layer);
	virtual void setVisible( bool visible );
	void showGuide();

	void update();

	void showSelectSkillInfo( int skillId = -1, int characterId = -1 );

private:
	void initComponent();		//初始化控件
	void refreshUI();			//刷新界面（重置）

	void buttonLevelUpCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonCloseCallback( Ref* pSender,Widget::TouchEventType type );
	void showSkillReleaseOrder( const Technical_Data* &pData );

private:		//控件排列顺序  从左到右 自上而下
	cocos2d::ui::Widget*				m_pWidget;
	cocos2d::ui::ImageView*			m_pImgCurSkillTextureBack;
	cocos2d::ui::ImageView*			m_pImgCurSkillTexture;
	cocos2d::ui::Text*				m_pLabSkillNameFont;			//招式名称
	cocos2d::ui::Text*				m_pLabSkillName;
	cocos2d::ui::Text*				m_pLabCurSkillLevelFont;		//当前等级
	cocos2d::ui::Text*				m_pLabCurSkillLevel;
	cocos2d::ui::Text*				m_pLabSkillDescFont;			//招式说明
	cocos2d::ui::TextField*				m_pTeaSkillDesc;
	cocos2d::ui::Text*				m_pLabReleaseSkillOrderFont;	//出招方式
	cocos2d::ui::Text*				m_pLabReleaseSkillPromptFont;	//依次点击一下按钮
	//出招方式 图示
	cocos2d::ui::Text*				m_pLabSkillLevelFont;			//等级
	cocos2d::ui::Text*				m_pLabBeforeSkillUpLevel;
	cocos2d::ui::Text*				m_pLabAfterSkillUpLebel;
	cocos2d::ui::Text*				m_pLabHarmFont;					//伤害
	cocos2d::ui::Text*				m_pBeforeHarmNum;
	cocos2d::ui::Text*				m_pAfterHarmNum;
	cocos2d::ui::Text*				m_pLabNeedLevelFont;			//所需等级:%d级
	cocos2d::ui::Text*				m_pLabNeedLevel;				//(暂不需要)
	cocos2d::ui::Text*				m_pLabNeedMoneyFont;			//金钱消耗：%d银两
	cocos2d::ui::Text*				m_pLabNeedMoney;				//(暂不需要)
	cocos2d::ui::ImageView*			m_pImgOrderPic[ICON_NUM];
	cocos2d::ui::ImageView*			m_pImgArrow[ICON_NUM-1];
	cocos2d::ui::Button*				m_pBtnLevelUp;
	cocos2d::ui::Text*				m_pBtnLevelUpFont;				//升级

	cocos2d::ui::Button*				m_pBtnClose;

	int						m_select_skill_id;
	int						m_select_character_id;

private:
	enum guide_step
	{
		GUIDE_SKILL_STEP_0 = 140,
		GUIDE_SKILL_STEP_1,
		GUIDE_SKILL_STEP_2,
		GUIDE_SKILL_STEP_3,
		GUIDE_SKILL_STEP_4,
	};
};

#endif //__UI_SKILL_ICON_INFO_LAYER__