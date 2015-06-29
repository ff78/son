#include "UI_SystemSetting_Layer.h"
#include "UI_MainMenu_Layer.h"
#include "Joiner_Guidance.h"
#include "Item_System/Item_Desc_Config_Mgr.h"

using namespace ui;

UI_SystemSetting_Layer::UI_SystemSetting_Layer(void)
{
}


UI_SystemSetting_Layer::~UI_SystemSetting_Layer(void)
{
}
bool UI_SystemSetting_Layer::init()
{
	bool ret=false;

	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());

																			
		m_pwidget=cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/System_Setting/System_Setting.ExportJson");
		addChild(m_pwidget);

 		m_psldmusic=dynamic_cast<cocos2d::ui::Slider*>(Helper::seekWidgetByName(m_pwidget,"sld_music"));
		m_psldmusic->addTouchEventListener(this,toucheventselector(UI_SystemSetting_Layer::sldCallBackMusic));
		m_psldmusic->addEventListenerSlider(this,sliderpercentchangedselector(UI_SystemSetting_Layer::sldCallBackMusicMoved));
 		m_psldeffect=dynamic_cast<cocos2d::ui::Slider*>(Helper::seekWidgetByName(m_pwidget,"sld_effect"));
		m_psldeffect->addEventListenerSlider(this,sliderpercentchangedselector(UI_SystemSetting_Layer::sldCallBackEffectMoved));
		m_psldeffect->addTouchEventListener(this,toucheventselector(UI_SystemSetting_Layer::sldCallBackEffect));
		//背景音乐的复选框
		m_pckbmusic=dynamic_cast<cocos2d::ui::CheckBox*>(Helper::seekWidgetByName(m_pwidget,"chb_music"));
		m_pckbmusic->addEventListenerCheckBox(this,checkboxselectedeventselector(UI_SystemSetting_Layer::ckbCallBackMusicSelect));
//		m_pckbmusic->addSelectEvent(this,toucheventselector(UI_SystemSetting_Layer::ckbCallBackMusicSelect));
//		m_pckbmusic->addUnSelectEvent(this,coco_unselectselector(UI_SystemSetting_Layer::ckbCallBackMusicUnSelect));
		//音效的复选框
 		m_pckbeffect=dynamic_cast<cocos2d::ui::CheckBox*>(Helper::seekWidgetByName(m_pwidget,"chb_effect"));
		m_pckbeffect->addEventListenerCheckBox(this,checkboxselectedeventselector(UI_SystemSetting_Layer::ckbCallBackEffectUnSelect));
//		m_pckbeffect->addUnSelectEvent(this,coco_unselectselector(UI_SystemSetting_Layer::ckbCallBackEffectUnSelect));
//		m_pckbeffect->addSelectEvent(this,toucheventselector(UI_SystemSetting_Layer::ckbCallBackEffectSelect));
		//是否屏蔽玩家模型
 		m_ckbplayermodel=dynamic_cast<cocos2d::ui::CheckBox*>(Helper::seekWidgetByName(m_pwidget,"chb_player_model"));
		m_ckbplayermodel->addEventListenerCheckBox(this,checkboxselectedeventselector(UI_SystemSetting_Layer::ckbCallBackShieldSelect));
//		m_ckbplayermodel->addSelectEvent(this,toucheventselector(UI_SystemSetting_Layer::ckbCallBackShieldSelect));
//		m_ckbplayermodel->addUnSelectEvent(this,coco_unselectselector(UI_SystemSetting_Layer::ckbCallBackShieldUnSelect));

 		m_pbtnclose=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pwidget,"btn_close_systemsetting"));
 		m_pbtnclose->addTouchEventListener(this,toucheventselector(UI_SystemSetting_Layer::btnCallBackClose));
		m_pshowmusic=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"lab_music_value"));
		m_pshoweffec=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"lab_effect_value"));

	
		int musicvalue=RecentlyServer::getBackgroundMusicValue();
		m_psldmusic->setPercent(musicvalue);
		char tempmusic[32]={0};
		SPRINTF(tempmusic,"%d",musicvalue);
		m_pshowmusic->setString(tempmusic);

		int effectvalue=RecentlyServer::getEffectValue();
		m_psldeffect->setPercent(effectvalue);
		char tempeffect[32]={0};
		SPRINTF(tempeffect,"%d",effectvalue);
		m_pshoweffec->setString(tempeffect);

		bool booleffect=RecentlyServer::getEffectState();
		
		m_psldeffect->setTouchEnabled(booleffect);
		m_pckbeffect->setSelectedState(booleffect);
		
		bool boolmusic=RecentlyServer::getBackgroundMusicState();
		
		m_psldmusic->setTouchEnabled(boolmusic);
		m_pckbmusic->setSelectedState(boolmusic);


		m_ckbplayermodel->setSelectedState(RecentlyServer::getShieldState());
		
	
		lab_name_item=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"lab_systemsetting"));
		const char * txetitem=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SYSTEM_SETTING);
		lab_name_item->setString(txetitem);


		lab_music=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"lab_music"));
		const char *textmusic=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UIMUSIC_SETTING);
		lab_music->setString(textmusic);

		lab_effect=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"lab_effect"));
		const char*	texteffect=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UIEFFECT_SETTING);
		lab_effect->setString(texteffect);

		lab_shield=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"lab_shield"));
		const char* textshield=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UISHIELD_SETTING);
		lab_shield->setString(textshield);

		ret=true;
	} while (0);
	return ret;
}

void UI_SystemSetting_Layer::btnCallBackClose(Ref* pSender,Widget::TouchEventType type)
{
	this->setVisible(false);
}
void UI_SystemSetting_Layer::sldCallBackMusic(Ref* pSender,Widget::TouchEventType type)
{
	cocos2d::ui::Slider* s;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	s=dynamic_cast<cocos2d::ui::Slider*>(pSender);
	////CCLog("pos is %d",s->getPercent());
	RecentlyServer::setBackgroundMusicValue(s->getPercent());

	break;
    default:
	break;
}
}
void UI_SystemSetting_Layer::sldCallBackEffect(Ref* pSender,Widget::TouchEventType type)
{
	cocos2d::ui::Slider* s;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	s=dynamic_cast<cocos2d::ui::Slider*>(pSender);
	//CCLog("pos is %d",s->getPercent());
	RecentlyServer::setEffectValue(s->getPercent());

	break;
    default:
	break;
}
}
void UI_SystemSetting_Layer::sldCallBackMusicMoved(Ref* pSender,cocos2d::ui::SliderEventType type)
{
	if (type == SLIDER_PERCENTCHANGED)
	{
		cocos2d::ui::Slider* s=dynamic_cast<cocos2d::ui::Slider*>(pSender);
		int persent=s->getPercent();
		char tempmusic[32]={0};
		SPRINTF(tempmusic,"%d",persent);
		m_pshowmusic->setString(tempmusic);
	}
}
void UI_SystemSetting_Layer::sldCallBackEffectMoved(Ref* pSender,cocos2d::ui::SliderEventType type)
{
	cocos2d::ui::Slider* s=dynamic_cast<cocos2d::ui::Slider*>(pSender);
	int persent=s->getPercent();
	char tempeffect[32]={0};
	SPRINTF(tempeffect,"%d",persent);
	m_pshoweffec->setString(tempeffect);
}
void UI_SystemSetting_Layer::ckbCallBackMusicUnSelect(Ref* pSender,CheckBoxEventType  type)
{
	RecentlyServer::setBackgroundMusicStateAndBehavior(false);
	
	m_psldmusic->setTouchEnabled(false);
	


	
}
void UI_SystemSetting_Layer::ckbCallBackMusicSelect(Ref* pSender,CheckBoxEventType type)
{

	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
	    RecentlyServer::setBackgroundMusicStateAndBehavior(true);
		break;

	case CHECKBOX_STATE_EVENT_UNSELECTED:
		RecentlyServer::setBackgroundMusicStateAndBehavior(false);
		break;

	default:
		break;
	}

	
	
	m_psldmusic->setTouchEnabled(true);
	
	
	
}
void UI_SystemSetting_Layer::ckbCallBackEffectSelect(Ref* pSender,CheckBoxEventType  type)
{
	RecentlyServer::setEffectStateAndBehavior(true);
	m_psldeffect->setTouchEnabled(true);
	

}
void UI_SystemSetting_Layer::ckbCallBackEffectUnSelect(Ref* pSender,CheckBoxEventType  type)
{
	RecentlyServer::setEffectStateAndBehavior(false);
	m_psldeffect->setTouchEnabled(false);
	
	
}
void UI_SystemSetting_Layer::ckbCallBackShieldSelect(Ref* pSender,CheckBoxEventType  type)
{


	DICTIONARY_CONFIG_MGR::instance()->show_alert(FUNCTION_WITHOUT);

	RecentlyServer::setShieldState(true);
}
void UI_SystemSetting_Layer::ckbCallBackShieldUnSelect(Ref* pSender,CheckBoxEventType  type)
{
	RecentlyServer::setShieldState(false);
}
