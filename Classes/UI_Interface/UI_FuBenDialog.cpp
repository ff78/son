#include "UI_FuBenDialog.h"
#include "Game_Interface/game_content_interface.h"
//#include "UI/GameUI_Layer.h"
#include "Common/VisibleRect.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
using namespace ui;
using namespace Game_Data;

UI_FuBenDialog::UI_FuBenDialog()
{
	this->is_first_=true;
    m_is_show = false;
}
bool UI_FuBenDialog::init()
{
	bool ret=false;
	do 
	{

		CC_BREAK_IF(!cocos2d::Layer::init());
		m_pwidget=cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/FuBen_Dialog/FuBen_Dialog.ExportJson");
		m_pwidget->setZOrder(888);
		addChild(m_pwidget);
		m_ppnl_root=dynamic_cast<cocos2d::ui::Layout*>(Helper::seekWidgetByName(m_pwidget,"pnl_root"));
		m_ppnl_root->addTouchEventListener(this,toucheventselector(UI_FuBenDialog::pnlCallBack));
		m_pimg_left=dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pwidget,"img_left")); 
		m_pimg_left->setPosition(Vec2(m_pimg_left->getPosition().x+VisibleRect::cutLength(),m_pimg_left->getPosition().y));
		m_pimg_left->setVisible(false);
		m_pimg_right=dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pwidget,"img_right"));
		m_pimg_right->setPosition(Vec2(m_pimg_right->getPosition().x-VisibleRect::cutLength(),m_pimg_right->getPosition().y));
		m_pimg_right->setVisible(false);
		m_ptea_left=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"tea_left"));
		m_ptea_left->setVisible(false);
		m_ptea_right=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"tea_right"));
		m_ptea_right->setVisible(false);

		ret=true;
	} while (0);
	return ret;
}
void UI_FuBenDialog::pnlCallBack(Ref* pSender,Widget::TouchEventType type)
{
vector<uint64> para;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	CCLog("click fuben panel");
	
	Game_Logic::Game_Content_Interface::instance()->exec_interface("showinstancedialog", para);

	break;
    default:
	break;
}
}
UI_FuBenDialog* UI_FuBenDialog::instance=NULL;
UI_FuBenDialog* UI_FuBenDialog::sharedUI_FuBenDialog()
{
	if(instance==NULL)
	{
		instance=new UI_FuBenDialog();
		if(instance&&instance->init())
		{
			return instance;
		}
		else
		{
			delete instance;
			instance=NULL;
		}
	}
	return instance;
}
void UI_FuBenDialog::showDialogMessage(bool isLeft,int imageId,int messageId)
{
	if(is_first_)
	{
		this->is_first_=false;
		
		this->scheduleOnce(schedule_selector(UI_FuBenDialog::setLayerVisible),1.2f);
	}

	//schedule(schedule_selector(GameUI_Layer::do_Button_Settlement), SETTLEMENT_DELAY_TIME);

	Scene* scene=Director::getInstance()->getRunningScene();
	if(!scene)
	{
		return;
	}

	UI_FuBenDialog* child=dynamic_cast<UI_FuBenDialog*>(scene->getChildByTag(TAG_FUBENDIALG));
	if(!child)
	{

		child = UI_FuBenDialog::sharedUI_FuBenDialog();
		scene->addChild(child, TAG_FUBENDIALG,TAG_FUBENDIALG);
	}

	setVisibleAndMessage(isLeft,imageId,messageId);


}
void UI_FuBenDialog::setVisibleAndMessage(bool isLeft,int imageId,int messageId)
{
//	GameUI_Layer::get_instance()->setVisible(false);
	m_pimg_left->setVisible(isLeft);
	m_pimg_right->setVisible(!isLeft);
	if(imageId==0)
	{
		m_pimg_left->setVisible(false);
		m_pimg_right->setVisible(false);
	}



	m_ptea_left->setVisible(isLeft);


	m_ptea_right->setVisible(!isLeft);

	if(isLeft)
	{
		const char* iconname=ITEM_CONFIG_MGR::instance()->get_icon_path(imageId);
        std::string p("icon/");
        p+=iconname;
		m_pimg_left->loadTexture(p.c_str());
		//m_pimg_left->setAnchorPoint(Vec2(0,0));
		//m_pimg_left->setPosition(Vec2(0.f,0.f));
		m_pimg_left->setFlipX(false);
		//showRoleSpeakInfo(messageId,m_ptea_left);
	}
	else
	{
		const char* iconname=ITEM_CONFIG_MGR::instance()->get_icon_path(imageId);
        std::string p("icon/");
        p+=iconname;
		m_pimg_right->loadTexture(p.c_str());
		//m_pimg_right->setAnchorPoint(Vec2(1,0));
		//float parentWidth = m_pimg_right->getParent()->getContentSize().width;
		//m_pimg_right->setPosition(Vec2(parentWidth, 0.f));
		m_pimg_right->setFlipX(true);
		//showRoleSpeakInfo(messageId,m_ptea_right);
	}
}
void UI_FuBenDialog::removeDialog()
{
	Scene* scene=Director::getInstance()->getRunningScene();
	if(!scene)
	{
		return;
	}

	UI_FuBenDialog* child=dynamic_cast<UI_FuBenDialog*>(scene->getChildByTag(TAG_FUBENDIALG));
	if(child)
	{
		scene->removeChildByTag(TAG_FUBENDIALG);
//		GameUI_Layer::get_instance()->setVisible(true);
	}
}
void UI_FuBenDialog::setLayerVisible(float dt)
{
//	GameUI_Layer::get_instance()->setVisible(true);
}

void UI_FuBenDialog::showRoleSpeakInfo(int messageId,cocos2d::ui::TextField* tea)
{
	const char* message=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(messageId);
	std::string strMessage(message);
	int n = strMessage.find("%s");
	CCLog("%d",n);
	if( -1 != n )
	{
		int role_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character( role_id ));
		const char* roleName = player->get_character_name();
		tea->setText(CCString::createWithFormat(message,roleName)->getCString());
	}
	else
	{
		tea->setText(message);
		CCLog("dialog is ---%s",message);	 
	}

}

void UI_FuBenDialog::onEnterTransitionDidFinish()
{
	cocos2d::Layer::onEnterTransitionDidFinish();
//	GameUI_Layer::get_instance()->setVisible(false);
}
