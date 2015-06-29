#include "UI_UpdateLayer.h"
#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Common/GameMacro.h"
#include "Common/GameDefine.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include <string>
#include "UI_Interface/UI_LoginLayer.h"
#include "UI/Login_Scene.h"
#include "Update_Logic/UpdateManager.h"
#include "Update_Logic/MessageInfo.h"
#include "Update_Logic/UpdateHelper.h"
#include "Common/Utils.h"
using namespace ui;
bool UI_UpdateLayer::init()
{

	bool ret=false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());
		m_widget=cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Update_Layer/Update_Layer.ExportJson");
		addChild(m_widget);
		//提示信息
		m_lab_tips=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_widget,"lab_tips"));
		//m_lab_tips->setString()
		m_lab_tips->setString("");
		//进度信息
		m_lab_progress=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_widget,"lab_progress"));
		m_lab_progress->setString("");
		//进度条
		m_ldb_progress=dynamic_cast<cocos2d::ui::LoadingBar*>(Helper::seekWidgetByName(m_widget,"pgb_progress"));
		m_ldb_progress->setPercent(0);
		//退出更新按钮
		m_btn_exit_update=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_widget,"btn_exit_update"));
		//m_btn_exit_update->addTouchEventListener(this,toucheventselector(UI_UpdateLayer::userStop));
		//退出的文字
		m_lab_exit_update=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_widget,"lab_exit_update"));
		const char* txtexit=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_QUIT);
		m_lab_exit_update->setString(txtexit);


		ret=true;
	} while (0);
	return ret;
}

void UI_UpdateLayer::onProgress( int percent,int current,int all )
{
	if (percent >= 100)
	{
		return;
	}
	const char* downloadingtext=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(DOWNLODING);
	m_lab_tips->setString(downloadingtext);
	m_ldb_progress->setPercent(percent);
	float currentInM=current/1024.0f/1024.0f;
	float allInM=all/1024.0f/1024.0f;
	const char* text=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UPDATE_PROGRESS);

	char progressText[64]={0};
	SPRINTF(progressText,"%s(%.1fM/%.1fM)",text,currentInM,allInM);

	m_lab_progress->setString(progressText);
}
void UI_UpdateLayer::onSuccess( ErrorCode errorCode )
{
	if(errorCode==UpdateProtocol::kINSTALL)
	{
		const char* text=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(DOWNLOAD_SUCCEED_INSTALL);

		CCLog("--------------void DownLoading_Layer::errorCode==UpdateProtocol::kINSTALL");
		UI_ModalDialogue_Layer::DoModal("", text, UI_ModalDialogue_Layer::DT_OK, [&](){ this->installAPK(); } );

	}
	else if(errorCode==UpdateProtocol::kREBOOT)
	{
		const char* text=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(DOWNLOAD_SUCCEED_RESTART);
		CCLog("--------------void DownLoading_Layer::errorCode==UpdateProtocol::kREBOOT");
		m_lab_tips->setVisible(false);
		UI_ModalDialogue_Layer::DoModal("", text, UI_ModalDialogue_Layer::DT_OK, [&](){ this->reboot(); } );
	}
	else if(errorCode==UpdateProtocol::kGOON)
	{
		const char* text=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(DOWNLOAD_SUCCEED_RESTART);
		//Scene * sc=Director::getInstance()->getRunningScene();
		//sc->removeChildByTag(UPDATELAYERTAG);
		CCLog("--------------void DownLoading_Layer::errorCode==UpdateProtocol::kGOON");
		m_lab_tips->setVisible(false);
		UI_ModalDialogue_Layer::DoModal("", text, UI_ModalDialogue_Layer::DT_OK, [&](){ this->reboot(); } );

	}
}
void UI_UpdateLayer::stopUpdate()
{
	const char* txtexit=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SURE_TO_EXIT_GAME);
	//取消更新
	UI_ModalDialogue_Layer::DoModal("", txtexit, UI_ModalDialogue_Layer::DT_YES_NO, [&](){ this->quit(); } );
	
}
void UI_UpdateLayer::onError( ErrorCode errorcode )
{
	CCLog("---------void DownLoading_Layer::onError( ErrorCode errorcode )");
	if(errorcode==UpdateProtocol::kNetwork)
	{
		const char* text=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(NETWORK_FAILED);
		UI_ModalDialogue_Layer::DoModal("", text, UI_ModalDialogue_Layer::DT_OK, [&](){ this->quit(); } );
	}
	else if(errorcode==UpdateProtocol::kCreateFile)
	{
		const char* text=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(CREATE_FILE_FAILED);
		UI_ModalDialogue_Layer::DoModal("", text, UI_ModalDialogue_Layer::DT_OK, [&](){ this->quit(); } );
	}
}

void UI_UpdateLayer::onGettingDownloadInfo()
{
	const char* text=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(READING_RESOURCES_INFO);
	m_lab_tips->setString(text);
}

void UI_UpdateLayer::installAPK()
{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//	Dependence::installAPK();
#endif
}
void UI_UpdateLayer::quit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void UI_UpdateLayer::reboot()
{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//	Dependence::reboot();
#endif
}
void UI_UpdateLayer::onEnter()
{
	cocos2d::Layer::onEnter();
	Scene* sc=Director::getInstance()->getRunningScene();
	if(sc)
	{
		UI_LoginLayer* login=(UI_LoginLayer*)(sc->getChildByTag(Login_Scene::UI_LOGIN_LAYER));
		if(login)
		{
			login->setVisible(false);
		}
	}
	
}
/*
void UI_UpdateLayer::reDownLoad()
{
	//释放内存，
	UpdateManager* ptr=UpdateManager::instance;
	if(ptr!=0)
	{
		delete ptr;
		UpdateManager::instance=0;
	}
	CCLog("-------------11111111111-----------------");
	this->removeFromParent();
	CCLog("-------------22222222222-----------------");
	MessageInfo *msg=new MessageInfo();
	msg->what=MessageInfo::START_MESSION;
	UpdateHelper::sharedInstance()->sendMessage(msg);
	CCLog("-------------33333333333-----------------");
	
}*/
void UI_UpdateLayer::userStop(Ref* pSender,Widget::TouchEventType type)
{
	//UpdateManager::close=true;
	stopUpdate();
}
