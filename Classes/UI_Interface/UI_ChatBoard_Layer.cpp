#include "UI_ChatBoard_Layer.h"
#include "Character_System/Player_Logic_Cl.h"
#include "Chat_System/Chat_Client.h"
#include "Game_Interface/game_content_interface.h"
#include "Common/GameDefine.h"
#include "Item_System/Item_Desc_Config_Mgr.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Shield_Word/ShieldManager.h"
#include "UI_ModalDialogue_Layer.h"
#include "Character_System/Player_Config_Data.h"
#include "UI_MainMenu_Layer.h"
#include "Common/Tool.h"
#include "MyEditBox.h"

#include "cocos2d.h"


using namespace ui;
USING_NS_CC;
//USING_NS_CC_EXT;
using namespace std;

std::deque<std::string>	UI_ChatBoard_Layer::m_queWorldChat;
std::deque<std::string> UI_ChatBoard_Layer::m_queGuildChat;
std::deque<std::string> UI_ChatBoard_Layer::m_queSecretChat;
std::deque<std::string>	UI_ChatBoard_Layer::m_queTeamChat;
std::deque<std::string>	UI_ChatBoard_Layer::m_queAllChat;	//综合 队列
std::deque<int>			UI_ChatBoard_Layer::m_queAllChatColor;	//综合 队列颜色

std::deque<std::string>	UI_ChatBoard_Layer::m_queFriendChat;	//私聊 队列
std::deque<std::string>	UI_ChatBoard_Layer::m_queAreaChat;	//私聊 队列

UI_ChatBoard_Layer::UI_ChatBoard_Layer(void)
:m_pInputBox(NULL)
, m_pBtnChannel(NULL)
, m_pLabCurInfo(NULL)
, m_pImgAddFrame(NULL)
, m_friendName("")
, chat_content_str_("")
, chat_show_content_("")
, m_chatState(CHAT_CHANNEL_WORLD)
, btnOnlinePK(NULL)
, btnSecretChat(NULL)
, btnAddStranger(NULL)
, show_text_lable_(NULL)
{
}

UI_ChatBoard_Layer::~UI_ChatBoard_Layer(void)
{
}

bool UI_ChatBoard_Layer::init()
{
	if (!cocos2d::Layer::init())
		return false;
	cocos2d::ui::Widget* pWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/ChatBoard.json");
	//cocos2d::ui::Widget* pWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/ChatBoard_0/ChatBoard_0.ExportJson");
	addChild(pWidget);

	//关闭 按钮
	cocos2d::ui::Button* pBtnClose = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget, "btn_Close"));
	pBtnClose->addTouchEventListener(this, toucheventselector(UI_ChatBoard_Layer::buttonCloseCallback));

	//发送 按钮
	//cocos2d::ui::Button* pBtnSend = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget, "btn_Send"));
	cocos2d::ui::Button* pBtnSend = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget, "Btn_Send"));	
	pBtnSend->addTouchEventListener(this, toucheventselector(UI_ChatBoard_Layer::buttonSendCallback));
	cocos2d::Size sz = Director::getInstance()->getWinSize();
	//聊天layer背景及整体
	chatInputPos = this->getPosition();
	chatInputUpPos = Vec2(this->getPosition().x, this->getPosition().y + sz.height / 2);
	//输入框
	m_pInputBox = (cocos2d::ui::TextField*)cocos2d::ui::Helper::seekWidgetByName(pWidget, "edit_Input");
	CC_ASSERT(m_pInputBox);
	m_pInputBox->setTouchEnabled(true);
	m_pInputBox->setMaxLengthEnabled(true);
	m_pInputBox->setMaxLength(CHAT_CONTENT_LENGTH);
	m_pInputBox->addEventListenerTextField(this, textfieldeventselector(UI_ChatBoard_Layer::textFieldEvent));
	m_pInputBox->setVisible(false);

	Size size(640,40);
	auto box = CommonEditBox::create(size);
	box->SetPositionAndMaxLength(0, 40, 150);
	addChild(box,2,"chat_box");

	//全部 按钮
	//m_pBtnAll = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget, "btn_all"));
	m_pBtnAll = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget, "Btn_All_0"));
	m_pBtnAll->setTag(CHAT_UI_BTN_ALL_TAG);
	m_pBtnAll->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
	m_pBtnAll->addTouchEventListener(this, toucheventselector(UI_ChatBoard_Layer::chatToAllCallback));

	//世界 按钮
	//m_pBtnWorld = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget, "btn_world"));
	m_pBtnWorld = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget, "Btn_World_0"));
	m_pBtnWorld->setTag(CHAT_UI_BTN_WORLD_TAG);
	m_pBtnWorld->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pBtnWorld->addTouchEventListener(this, toucheventselector(UI_ChatBoard_Layer::chatToWorldCallback));

	//门派 按钮
	//m_pBtnUnited = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget, "btn_united"));
	m_pBtnUnited = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget, "Btn_Faction_0"));
	m_pBtnUnited->setTag(CHAT_UI_BTN_UNITED_TAG);
	m_pBtnUnited->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pBtnUnited->addTouchEventListener(this, toucheventselector(UI_ChatBoard_Layer::chatToGuildCallback));

	//私聊 按钮
	//m_pBtnSecretChat = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget, "btn_secret_chat"));
	m_pBtnSecretChat = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget, "Btn_Private_0"));
	m_pBtnSecretChat->setTag(CHAT_UI_BTN_SECRET_CHAT_TAG);
	m_pBtnSecretChat->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pBtnSecretChat->addTouchEventListener(this, toucheventselector(UI_ChatBoard_Layer::chatToSpecifiedPersonCallback));

	//系统公告 按钮
	m_pBtnSystemNotice = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget, "btn_system"));
	m_pBtnSystemNotice->setTag(CHAT_UI_BTN_GUILD_TAG);
	m_pBtnSystemNotice->addTouchEventListener(this, toucheventselector(UI_ChatBoard_Layer::chatForVisionSystemNoticeCallback));

	//滚动层
	m_pScrollPanel = dynamic_cast<cocos2d::ui::ScrollView*>(Helper::seekWidgetByName(pWidget, "ScrollView"));

	//显示 当前所在频道 按钮  （输入框 左侧 按钮）
	m_pBtnChannel = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget, "btn_channel"));
	m_pBtnChannel->setTouchEnabled(false);

	//获得 频道 字体控件
	m_pLabCurInfo = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(pWidget, "lab_channel_font"));

	//点击提示框  （内容为：人物详情  私聊  添加好友）
	m_pImgAddFrame = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(pWidget, "img_add_friend_frame"));
	this->closeAddFriendFrame();

	Pnl_Msg_Bg = dynamic_cast<cocos2d::ui::Widget*>(Helper::seekWidgetByName(pWidget, "Pnl_Msg_Bg"));

	m_pScrollPanel->jumpToTop();

	// 输入框显示层
	show_text_lable_ = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(pWidget, "input_show_label"));

	return true;
}

void UI_ChatBoard_Layer::setVisible(bool visible)
{
	cocos2d::Layer::setVisible(visible);
	if (visible)
	{
		chatToWorldCallback(NULL, Widget::TouchEventType::ENDED);
	}
}

void UI_ChatBoard_Layer::buttonCloseCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		setVisible(false);
		//	UI_MainMenu_Layer::get_instance()->showGuide();

		break;
	default:
		break;
	}
}

void UI_ChatBoard_Layer::buttonSendCallback(Ref* pSender, Widget::TouchEventType type)
{
	const char *pContent;
	//chat_content_str_ = ChatEditBox::getInstance()->getContent();
	chat_content_str_ = ( (CommonEditBox*)this->getChildByName("chat_box") )->getContent();
	string retValue;
	int player_id;
	Game_Data::Player* player;
	std::string roleName;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		pContent = chat_content_str_.c_str();
		//pContent = ChatEditBox::getInstance()->getContent().c_str();
		retValue = ShieldManager::sharedShieldManager()->transferChatMessage(pContent);
		pContent = retValue.c_str();
		if (!pContent || strlen(pContent) <= 0)
		{
			return;
		}

		player_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
		roleName = player->get_character_name();

		////CCLOG(m_friendName.c_str());
		//if (m_chatState == CHAT_CHANNEL_PRIVATE && m_friendName != "" && roleName != m_friendName)
		if (m_chatState == CHAT_CHANNEL_PRIVATE)
		{
			CHAT_LOGIC::getInstance()->send_chat_msg_private(m_chatState, m_friendName.c_str(), pContent);
		}
		else if (m_chatState == CHAT_CHANNEL_WORLD)
		{
			//PLAYER_LOGIC::instance()->send_chat_msg_world(m_chatState, "", pContent);
			CHAT_LOGIC::getInstance()->send_chat_msg_world(m_chatState, "", pContent);
		}
		else if (m_chatState == CHAT_CHANNEL_ALL)
		{
			//PLAYER_LOGIC::instance()->send_chat_msg_all(m_chatState, "", pContent);
			CHAT_LOGIC::getInstance()->send_chat_msg_all(m_chatState, "", pContent);

		}
		else if (m_chatState == CHAT_CHANNEL_FRIEND)
		{
			PLAYER_LOGIC::instance()->send_chat_msg(m_chatState, "", pContent);
		}
		else if (m_chatState == CHAT_CHANNEL_MENPAI)
		{
			PLAYER_LOGIC::instance()->send_chat_msg_faction(m_chatState, "", pContent);
		}
		else if (m_chatState == CHAT_CHANNEL_TEAM)
		{
			PLAYER_LOGIC::instance()->send_chat_msg(m_chatState, "", pContent);
		}
		else if (m_chatState == CHAT_CHANNEL_SYSTEM)
		{
			//CHAT_LOGIC::getInstance()->send_chat_msg_area(m_chatState, "", pContent);
		}
		m_pInputBox->setText("");
		chat_content_str_ = "";
		chat_show_content_ = "";
		show_text_lable_->setString(chat_show_content_.c_str());

		break;
	default:
		break;
	}
}

void UI_ChatBoard_Layer::addChatContent(int channel, const char* sender, const char* receiver, const char* szChatContent)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	std::string roleName = player->get_character_name();

	if (CHAT_CHANNEL_WORLD == channel)
	{
		if (m_queWorldChat.size() >= MAX_HISTORY_RECORD)
			m_queWorldChat.pop_front();
		m_queWorldChat.push_back(szChatContent);

		if (m_queAllChat.size() >= MAX_HISTORY_RECORD)
			m_queAllChat.pop_front();
		m_queAllChat.push_back(szChatContent);

		if (m_queAllChatColor.size() >= MAX_HISTORY_RECORD)
			m_queAllChatColor.pop_front();
		m_queAllChatColor.push_back(CHAT_CHANNEL_WORLD);

	}
	else if (CHAT_CHANNEL_PRIVATE == channel)
	{
		if (sender == roleName)
		{
			m_pLabCurInfo->setString(receiver);
			m_friendName = receiver;
		}
		else
		{
			m_friendName = sender;
		}

		if (m_queSecretChat.size() >= MAX_HISTORY_RECORD)
			m_queSecretChat.pop_front();
		m_queSecretChat.push_back(szChatContent);

		if (m_queAllChat.size() >= MAX_HISTORY_RECORD)
			m_queAllChat.pop_front();
		m_queAllChat.push_back(szChatContent);

		if (m_queAllChatColor.size() >= MAX_HISTORY_RECORD)
			m_queAllChatColor.pop_front();
		m_queAllChatColor.push_back(CHAT_CHANNEL_PRIVATE);
	}
	else if (CHAT_CHANNEL_FRIEND == channel)
	{
	}
	else if (CHAT_CHANNEL_TEAM == channel)
	{
	}
	else if (CHAT_CHANNEL_MENPAI == channel)
	{
	}
	else if (CHAT_CHANNEL_ALL == channel)
	{
		if (m_queAllChat.size() >= MAX_HISTORY_RECORD)
			m_queAllChat.pop_front();
		m_queAllChat.push_back(szChatContent);

		if (m_queAllChatColor.size() >= MAX_HISTORY_RECORD)
			m_queAllChatColor.pop_front();
		m_queAllChatColor.push_back(CHAT_CHANNEL_ALL);
	}
	else if (CHAT_CHANNEL_SYSTEM == channel)
	{
		if (m_queAreaChat.size() >= MAX_HISTORY_RECORD)
			m_queAreaChat.pop_front();
		m_queAreaChat.push_back(szChatContent);

		if (m_queAllChat.size() >= MAX_HISTORY_RECORD)
			m_queAllChat.pop_front();
		m_queAllChat.push_back(szChatContent);

		if (m_queAllChatColor.size() >= MAX_HISTORY_RECORD)
			m_queAllChatColor.pop_front();
		m_queAllChatColor.push_back(CHAT_CHANNEL_SYSTEM);
	}

	//如果 客户端当前状态不是私聊  而频道传递过来的是私聊  闪烁提示
	if (m_chatState != CHAT_CHANNEL_PRIVATE && channel == CHAT_CHANNEL_PRIVATE)
	{
		ActionInterval* blink = CCBlink::create(1.5f, 2);
		CCAction* action = CCRepeatForever::create(blink);
		m_pBtnSecretChat->runAction(action);
	}

	if (m_chatState == CHAT_CHANNEL_WORLD)
		refreshChatContent(m_queWorldChat);
	else if (m_chatState == CHAT_CHANNEL_PRIVATE)
		refreshChatContent(m_queSecretChat);
	else if (m_chatState == CHAT_CHANNEL_FRIEND)
		refreshChatContent(m_queFriendChat);
	else if (m_chatState == CHAT_CHANNEL_TEAM)
		refreshChatContent(m_queSecretChat);
	else if (m_chatState == CHAT_CHANNEL_MENPAI)
		refreshChatContent(m_queGuildChat);
	else if (m_chatState == CHAT_CHANNEL_ALL)
		refreshChatContent(m_queAllChat);
	else if (m_chatState == CHAT_CHANNEL_SYSTEM)
		refreshChatContent(m_queAreaChat);
}

void UI_ChatBoard_Layer::refreshChatContent(std::deque<string> deq)
{
	if (false == this->isVisible())
	{
		return;
	}

	for (unsigned int i = 0; i < MAX_HISTORY_RECORD; ++i)
	{


	}

	this->closeAddFriendFrame();

	int count = 0;

	deque<std::string>::iterator it = deq.begin();
	deque<int>::iterator it2 = m_queAllChatColor.begin();

	m_pScrollPanel->removeAllChildren();
	for (; it != deq.end(); ++it, ++it2)
	{
		std::string str = *it;
		int cor = *it2;
		//txtButton[count]->setVisible(true);
		//m_aMsgs[count]->setVisible(true);
		cocos2d::ui::Text* myStr = cocos2d::ui::Text::create();
		myStr->setFontSize(25);
		switch (m_chatState)
		{
		case CHAT_CHANNEL_ALL:
		{
			//myStr->setColor(Color3B::BLUE);
			if (cor == CHAT_CHANNEL_WORLD)
			{
				myStr->setColor(Color3B::YELLOW);
			}
			else if (cor == CHAT_CHANNEL_PRIVATE)
			{
				myStr->setColor(Color3B::RED);

			}
			else if (cor == CHAT_CHANNEL_SYSTEM)
			{
				myStr->setColor(Color3B::WHITE);

			}
			else
			{
				myStr->setColor(Color3B::ORANGE);

			}

		}
			break;
		case CHAT_CHANNEL_WORLD:
			myStr->setColor(Color3B::YELLOW);
			break;
		case CHAT_CHANNEL_MENPAI:
			myStr->setColor(Color3B::WHITE);

			break;
		case CHAT_CHANNEL_TEAM:
			myStr->setColor(Color3B::WHITE);

			break;
		case CHAT_CHANNEL_FRIEND:
			myStr->setColor(Color3B::WHITE);

			break;
		case CHAT_CHANNEL_PRIVATE:
			myStr->setColor(Color3B::RED);
			break;
		case CHAT_CHANNEL_SYSTEM:
			myStr->setColor(Color3B::ORANGE);
			break;
		default:
			myStr->setColor(Color3B::WHITE);
			break;
		}
		myStr->setTextHorizontalAlignment(TextHAlignment::LEFT);
		myStr->setTextVerticalAlignment(TextVAlignment::CENTER);
		myStr->setTextAreaSize( Size(460,46) );
		myStr->setString(str);
		myStr->setAnchorPoint( Vec2(0.5f,0.5f) );
		myStr->setPosition( Vec2(250, 25) );
		//m_aMsgs[count]->addChild(myStr);
		auto msgBg = Pnl_Msg_Bg->clone();
		msgBg->addChild(myStr);
		msgBg->setPosition(Vec2(0, 400 - 25 - 50 * count));
		m_pScrollPanel->addChild(msgBg);
		++count;
		if (count > 8)
		{
			float tmpY = count * 50.f;
			Size new_size(640,tmpY);
			m_pScrollPanel->setInnerContainerSize(new_size);
			m_pScrollPanel->jumpToBottom();
		}
		else
		{
			m_pScrollPanel->setInnerContainerSize(Size(640.f,400.f));
			m_pScrollPanel->jumpToTop();
		}
		continue;

		//获取名称
		cocos2d::ui::Text* texName = cocos2d::ui::Text::create();
		texName->setFontSize(25);
		texName->setContentSize( Size(100,25) );
		texName->setAnchorPoint(Vec2(0.f, 0.5f));
		//float posY = txtButton[count]->getPosition().y;
		float posY = m_aMsgs[count]->getContentSize().height;
		//float x = txtButton[count]->getPosition().x;
		//float y = txtButton[count]->getPosition().y;
		std::string roleName = parseString(str.c_str(), ":", 1);

		texName->setString(roleName.c_str());
		texName->setColor(ccc3(255, 255, 0));
		texName->setPosition(Vec2(0, posY/2));
		texName->setTag(CHAT_NAME_LABEL_TAG);
		//txtButton[count]->addChild(texName);
		m_aMsgs[count]->addChild(texName);


		//说话内容
		std::string roleSaidInfo = parseString(str.c_str(), ":", 2);
		cocos2d::ui::Text* charContentLable = cocos2d::ui::Text::create();
		charContentLable->setFontSize(25);
		texName->setContentSize(Size(300, 25));

		charContentLable->setAnchorPoint(Vec2(0.f, 0.5f));
		//charContentLable->setPosition(Vec2(texName->getPosition().x + texName->getContentSize().width, texName->getPosition().y));
		charContentLable->setString(roleSaidInfo.c_str());
		charContentLable->setTag(CHAT_CONTENT_LABEL_TAG);
		charContentLable->setPosition(Vec2(400, posY/2));
		/*txtButton[count]->addChild(charContentLable);
		txtButton[count]->addTouchEventListener(this, toucheventselector(UI_ChatBoard_Layer::addFriendForChat));*/
		m_aMsgs[count]->addChild(charContentLable);
		m_aMsgs[count]->addTouchEventListener(this, toucheventselector(UI_ChatBoard_Layer::addFriendForChat));

		++count;
	}
	Size sz = m_pScrollPanel->getInnerContainerSize();
	log("the inner sizeX:%f , sizeY:%f", sz.width, sz.height);

};

void UI_ChatBoard_Layer::addFriendForChat(Ref* pSender, Widget::TouchEventType type)
{
	int player_id;
	Game_Data::Player* player;
	std::string roleName;
	cocos2d::ui::Button* curImg;
	cocos2d::ui::Text* chil;
	const char* str;
	cocos2d::Size size;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		player_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
		roleName = player->get_character_name();

		//CCLOG("this is UI_ChatBoard_Layer::addFriendForChat");
		curImg = dynamic_cast<cocos2d::ui::Button*>(pSender);

		chil = dynamic_cast<cocos2d::ui::Text*>(curImg->getChildByTag(CHAT_NAME_LABEL_TAG));
		if (!chil) return;

		str = chil->getStringValue().c_str();
		if (!str) return;
		m_friendName = parseName(str, "[", "]");

		//CCLOG(str);

		if (m_friendName != roleName)
		{
			this->openAddFriendFrame();
			size = Director::getInstance()->getWinSize();
			m_pImgAddFrame->setPosition(CCPointZero);
		}
		break;
	default:
		break;
	}

}

//左侧 所有人 按钮
void UI_ChatBoard_Layer::chatToAllCallback(Ref* pSender, Widget::TouchEventType type)
{
	cocos2d::ui::Button* pCurBtn;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		pCurBtn = dynamic_cast<cocos2d::ui::Button*>(pSender);
		m_pLabCurInfo->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(CHAT_UI_BTN_ALL_TAG));
		m_chatState = CHAT_CHANNEL_ALL;
		refreshChatContent(m_queAllChat);
		m_pBtnAll->setBrightStyle(BrightStyle::HIGHLIGHT);
		m_pBtnSecretChat->setBrightStyle(Widget::BrightStyle::NORMAL);
		m_pBtnUnited->setBrightStyle(BrightStyle::NORMAL);
		m_pBtnWorld->setBrightStyle(BrightStyle::NORMAL);
	}
		break;
	default:
		break;
	}
}

//左侧 世界频道 按钮
void UI_ChatBoard_Layer::chatToWorldCallback(Ref* pSender, Widget::TouchEventType type)
{
	cocos2d::ui::Button* pCurBtn;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		pCurBtn = dynamic_cast<cocos2d::ui::Button*>(pSender);
		m_pLabCurInfo->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(CHAT_UI_BTN_WORLD_TAG));

		m_chatState = CHAT_CHANNEL_WORLD;

		refreshChatContent(m_queWorldChat);
		m_pBtnAll->setBrightStyle(BrightStyle::NORMAL);
		m_pBtnSecretChat->setBrightStyle(Widget::BrightStyle::NORMAL);
		m_pBtnUnited->setBrightStyle(BrightStyle::NORMAL);
		m_pBtnWorld->setBrightStyle(BrightStyle::HIGHLIGHT);
		break;
	default:
		break;
	}
}

//左侧 门派 按钮
void UI_ChatBoard_Layer::chatToGuildCallback(Ref* pSender, Widget::TouchEventType type)
{
	cocos2d::ui::Button* pCurBtn;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		pCurBtn = dynamic_cast<cocos2d::ui::Button*>(pSender);
		m_pLabCurInfo->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(CHAT_UI_BTN_UNITED_TAG));	
		m_chatState = CHAT_CHANNEL_MENPAI;
		refreshChatContent(m_queGuildChat);
		m_pBtnAll->setBrightStyle(BrightStyle::NORMAL);
		m_pBtnSecretChat->setBrightStyle(Widget::BrightStyle::NORMAL);
		m_pBtnUnited->setBrightStyle(BrightStyle::HIGHLIGHT);
		m_pBtnWorld->setBrightStyle(BrightStyle::NORMAL);
		break;
	default:
		break;
	}
}

//左侧 私聊 按钮
void UI_ChatBoard_Layer::chatToSpecifiedPersonCallback(Ref* pSender, Widget::TouchEventType type)
{
	cocos2d::ui::Button* pCurBtn;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		pCurBtn = dynamic_cast<cocos2d::ui::Button*>(pSender);
		m_pBtnSecretChat->stopAllActions();
		m_pBtnSecretChat->setVisible(true);
		//“秘语”  字体显示
		m_chatState = CHAT_CHANNEL_PRIVATE;
		if (m_friendName != "")
		{
			m_pLabCurInfo->setString(m_friendName.c_str());
		}
		else
		{
			m_pLabCurInfo->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(CHAT_UI_BTN_SECRET_CHAT_TAG));
		}


		refreshChatContent(m_queSecretChat);
		m_pBtnAll->setBrightStyle(BrightStyle::NORMAL);
		m_pBtnSecretChat->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
		m_pBtnUnited->setBrightStyle(BrightStyle::NORMAL);
		m_pBtnWorld->setBrightStyle(BrightStyle::NORMAL);
		break;
	default:
		break;
	}
}

//左侧 系统公告 按钮
void UI_ChatBoard_Layer::chatForVisionSystemNoticeCallback(Ref* pSender, Widget::TouchEventType type)
{
	cocos2d::ui::Button* pCurBtn;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		pCurBtn = dynamic_cast<cocos2d::ui::Button*>(pSender);
		m_pLabCurInfo->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(CHAT_UI_BTN_GUILD_TAG));

		m_chatState = CHAT_CHANNEL_SYSTEM;
		refreshChatContent(m_queAreaChat);
		break;
	default:
		break;
	}
}

void UI_ChatBoard_Layer::addFriendForChatCallback(Ref* pSender, Widget::TouchEventType type)
{
	CCString* note_text;
	const char* szString;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//CCLOG("UI_ChatBoard_Layer::addFriendForChatCallback");
		this->closeAddFriendFrame();

		note_text = NULL;
		szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ADD_FRIEND_CONFIRM);
		note_text = CCString::createWithFormat(szString, m_friendName.c_str());
		UI_ModalDialogue_Layer::DoModal("", note_text->getCString(), UI_ModalDialogue_Layer::DT_YES_NO, [&](){ this->btnStrangerAddCallback(); });

		break;
	default:
		break;
	}
}

void UI_ChatBoard_Layer::btnOnlinePkCallback(Ref* pSender, Widget::TouchEventType type)
{
	int player_id;
	vector<uint64> para;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//CCLOG("This is UI_ChatBoard_Layer::btnGetRoleInfoCallback");
		player_id = 1000012;
		para.push_back(player_id);
		Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_online_fight", para, m_friendName.c_str());

		break;
	default:
		break;
	}
}

//私聊 按钮 （次级界面）
void UI_ChatBoard_Layer::btnSecretChatCallback(Ref* pSender, Widget::TouchEventType type)
{
	const char* szName;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//CCLOG("This is UI_ChatBoard_Layer::btnSecretChatCallback");
		this->closeAddFriendFrame();
		szName = m_friendName.c_str();
		m_pLabCurInfo->setString(szName);
		m_chatState = CHAT_CHANNEL_PRIVATE;

		refreshChatContent(m_queSecretChat);

		break;
	default:
		break;
	}
}

//添加好友 按钮
void UI_ChatBoard_Layer::btnStrangerAddCallback(){
	//CCLOG("this is UI_ChatBoard_Layer::btnStrangerAddCallback");
	int player_id = 1000012;
	vector<uint64> para;
	para.push_back(player_id);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_add_friend", para, m_friendName.c_str());
	m_friendName = "";
}


void UI_ChatBoard_Layer::btnAddFrameCloseCallback(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//CCLOG("this is UI_ChatBoard_Layer::btnAddFrameCloseCallback");
		this->closeAddFriendFrame();

		break;
	default:
		break;
	}
}


//解析第一个：的前后内容 
std::string UI_ChatBoard_Layer::parseString(const char* str, const char* prase_str, size_t index)
{
	if (str == NULL || prase_str == NULL || index <= 0)
		return NULL;
	const char* str1 = strstr(str, prase_str);
	if (str1 == NULL)
		return str;

	char cop[1024] = { 0 };
	if (1 == index)
	{
		memcpy(cop, str, str1 - str);
		return cop;
	}
	else
		return str1;
}

std::string UI_ChatBoard_Layer::parseName(const char* str, const char* left, const char* right)
{
	if (str == NULL)
		return NULL;

	const char* str1 = strstr(str, left);
	const char* str2 = strstr(str, right);
	char name[64] = { 0 };

	memcpy(name, ++str1, str2 - str1);

	return name;
}

void UI_ChatBoard_Layer::openPrivateChat(const char* receiver)
{
	m_friendName = receiver;
	m_pBtnSecretChat->setVisible(true);
	m_pLabCurInfo->setString(receiver);
	m_chatState = CHAT_CHANNEL_PRIVATE;
	refreshChatContent(m_queSecretChat);
}
#if 1
void UI_ChatBoard_Layer::textFieldEvent(Ref* pSender, TextFiledEventType type)
{

	switch (type)
	{
	case TEXTFIELD_EVENT_ATTACH_WITH_IME:
	{
#if(CC_PLATFORM_IOS==CC_TARGET_PLATFORM)
											ActionInterval* moveup=CCMoveTo::create(0.05f,chatInputUpPos);
											this->runAction(moveup);
#endif
	}
		break;

	case TEXTFIELD_EVENT_DETACH_WITH_IME:
	{
#if(CC_PLATFORM_IOS==CC_TARGET_PLATFORM)
											ActionInterval* movedown=CCMoveTo::create(0.05f,chatInputPos);
											this->runAction(movedown);
#endif
	}
		break;
	case TEXTFIELD_EVENT_INSERT_TEXT:
	{
										//CCLOG("TEXTFIELD_EVENT_INDERT_TEXT");
										cocos2d::ui::TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
										chat_show_content_ = textField->getStringValue();
										const char *text = NULL;
										text = chat_show_content_.c_str();

										chat_content_str_ = text;

										int chat_content_length = 0;
										int i = 0;
										while ('\0' != text[i])
										{
											int multiple = 1;
											char value = text[i];
											if (value < 0 || value > 127)
											{
												multiple = 3;
											}

											chat_content_length += multiple;
											i += multiple;
										}

										if (CHAT_CONTENT_SHOW_LENGTH < chat_content_length)
										{
											chat_show_content_ = chat_show_content_.substr(0, CHAT_CONTENT_SHOW_LENGTH);
											chat_show_content_ += SPILT;
										}
										show_text_lable_->setString(chat_show_content_.c_str());
	}
		break;

	default:
		break;
	}
}
#endif
void UI_ChatBoard_Layer::closeAddFriendFrame(void)
{
	if (NULL != m_pImgAddFrame)
	{
		m_pImgAddFrame->setVisible(false);
		m_pImgAddFrame->setTouchEnabled(false);

		if (btnOnlinePK)
		{
			btnOnlinePK->setTouchEnabled(false);
		}

		if (btnSecretChat)
		{
			btnSecretChat->setTouchEnabled(false);
		}

		if (btnAddStranger)
		{
			btnAddStranger->setTouchEnabled(false);
		}



	}
}

void UI_ChatBoard_Layer::openAddFriendFrame(void)
{
	if (NULL != m_pImgAddFrame)
	{
		m_pImgAddFrame->setVisible(true);
		m_pImgAddFrame->setTouchEnabled(true);

		if (btnOnlinePK)
		{
			btnOnlinePK->setTouchEnabled(true);
		}

		if (btnSecretChat)
		{
			btnSecretChat->setTouchEnabled(true);
		}

		if (btnAddStranger)
		{
			btnAddStranger->setTouchEnabled(true);
		}

	}
}

void UI_ChatBoard_Layer::update()
{
	int character_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(character_id));
	if (!player)
		return;
	//int nCh = player->get_channel();
	int nCh = CHAT_LOGIC::getInstance()->get_channel();
	if (nCh == 1)//world
	{
		//m_queWorldChat.push_back(player->get_chat_received());
		std::string tmp = CHAT_LOGIC::getInstance()->get_msg_received();

		if (m_queWorldChat.size() >= MAX_HISTORY_RECORD)
			m_queWorldChat.pop_front();
		m_queWorldChat.push_back(CHAT_LOGIC::getInstance()->get_msg_received());

		if (m_queAllChat.size() >= MAX_HISTORY_RECORD)
			m_queAllChat.pop_front();
		m_queAllChat.push_back(CHAT_LOGIC::getInstance()->get_msg_received());	

		if (m_queAllChatColor.size() >= MAX_HISTORY_RECORD)
			m_queAllChatColor.pop_front();
		m_queAllChatColor.push_back(CHAT_CHANNEL_WORLD);

		refreshChatContent(m_queWorldChat);
	}
	else if (nCh == 2)//area
	{
		std::string tmp = CHAT_LOGIC::getInstance()->get_msg_received();

		//if (m_queAreaChat.size() >= MAX_HISTORY_RECORD)
		//	m_queAreaChat.pop_front();
		//m_queAreaChat.push_back(CHAT_LOGIC::getInstance()->get_msg_received());

		if (m_queAllChat.size() >= MAX_HISTORY_RECORD)
			m_queAllChat.pop_front();
		m_queAllChat.push_back(CHAT_LOGIC::getInstance()->get_msg_received());

		if (m_queAllChatColor.size() >= MAX_HISTORY_RECORD)
			m_queAllChatColor.pop_front();
		m_queAllChatColor.push_back(CHAT_CHANNEL_ALL);

		refreshChatContent(m_queAllChat);
	}
	else if (nCh == 3)//private
	{
		std::string tmp = CHAT_LOGIC::getInstance()->get_msg_received();

		if (m_queSecretChat.size() >= MAX_HISTORY_RECORD)
			m_queSecretChat.pop_front();
		m_queSecretChat.push_back(CHAT_LOGIC::getInstance()->get_msg_received());

		if (m_queAllChat.size() >= MAX_HISTORY_RECORD)
			m_queAllChat.pop_front();
		m_queAllChat.push_back(CHAT_LOGIC::getInstance()->get_msg_received());

		if (m_queAllChatColor.size() >= MAX_HISTORY_RECORD)
			m_queAllChatColor.pop_front();
		m_queAllChatColor.push_back(CHAT_CHANNEL_PRIVATE);

		refreshChatContent(m_queSecretChat);
	}
	else if (nCh == 4)
	{

	}
	else if (nCh == 5)
	{

	}

}