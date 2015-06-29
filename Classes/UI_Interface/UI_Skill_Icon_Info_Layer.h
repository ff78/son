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
	void initComponent();		//��ʼ���ؼ�
	void refreshUI();			//ˢ�½��棨���ã�

	void buttonLevelUpCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonCloseCallback( Ref* pSender,Widget::TouchEventType type );
	void showSkillReleaseOrder( const Technical_Data* &pData );

private:		//�ؼ�����˳��  ������ ���϶���
	cocos2d::ui::Widget*				m_pWidget;
	cocos2d::ui::ImageView*			m_pImgCurSkillTextureBack;
	cocos2d::ui::ImageView*			m_pImgCurSkillTexture;
	cocos2d::ui::Text*				m_pLabSkillNameFont;			//��ʽ����
	cocos2d::ui::Text*				m_pLabSkillName;
	cocos2d::ui::Text*				m_pLabCurSkillLevelFont;		//��ǰ�ȼ�
	cocos2d::ui::Text*				m_pLabCurSkillLevel;
	cocos2d::ui::Text*				m_pLabSkillDescFont;			//��ʽ˵��
	cocos2d::ui::TextField*				m_pTeaSkillDesc;
	cocos2d::ui::Text*				m_pLabReleaseSkillOrderFont;	//���з�ʽ
	cocos2d::ui::Text*				m_pLabReleaseSkillPromptFont;	//���ε��һ�°�ť
	//���з�ʽ ͼʾ
	cocos2d::ui::Text*				m_pLabSkillLevelFont;			//�ȼ�
	cocos2d::ui::Text*				m_pLabBeforeSkillUpLevel;
	cocos2d::ui::Text*				m_pLabAfterSkillUpLebel;
	cocos2d::ui::Text*				m_pLabHarmFont;					//�˺�
	cocos2d::ui::Text*				m_pBeforeHarmNum;
	cocos2d::ui::Text*				m_pAfterHarmNum;
	cocos2d::ui::Text*				m_pLabNeedLevelFont;			//����ȼ�:%d��
	cocos2d::ui::Text*				m_pLabNeedLevel;				//(�ݲ���Ҫ)
	cocos2d::ui::Text*				m_pLabNeedMoneyFont;			//��Ǯ���ģ�%d����
	cocos2d::ui::Text*				m_pLabNeedMoney;				//(�ݲ���Ҫ)
	cocos2d::ui::ImageView*			m_pImgOrderPic[ICON_NUM];
	cocos2d::ui::ImageView*			m_pImgArrow[ICON_NUM-1];
	cocos2d::ui::Button*				m_pBtnLevelUp;
	cocos2d::ui::Text*				m_pBtnLevelUpFont;				//����

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