#pragma once
#include "ResultLayer.h"

#include "cocostudio/CocoStudio.h"

#include "Common/GameDefine.h"
#include "../../Play_System/Instance_Data_Mgr.h"
#include "../../Game_Interface/event_define.h"
#include "../../Item_System/Item_Mgr_Cl.h"
#include "../../UI_Interface/UI_ModalDialogue_Layer.h"
#include "DataModule/BlackCity.h"
#include "DataModule/BattleField.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"
#include "GameScene.h"

#include "Network_Common/message.h"
#include "Network_Common/message_stream.h"

#include "Network_Common/NetManager.h"
#include "../Utils/BaseUtils.h"


USING_NS_CC;
using namespace ui;

//std::map<int, int> ResultLayer::sItemMap = new std::map<int,int>();
//std::map<int, int> ResultLayer::sCountMap;
//std::vector<int> sItemVec = new std::vector<int>();
//std::vector<int> sCountVec;
int ResultLayer::sCurInstanceId(0);

int ResultLayer::sMoney(0);
int ResultLayer::sExp(0);
int ResultLayer::sClickTimes(4);
int ResultLayer::sUpWhere(0);
int ResultLayer::sDownWhere(0);
int ResultLayer::sTemp(0);
Value ResultLayer::sWinOrLose(true);
Value ResultLayer::sName(0);
Value ResultLayer::sPower(0);
Value ResultLayer::sHP(0);
Value ResultLayer::sAtk(0);
Value ResultLayer::sGuard(0);
Value ResultLayer::sMP(0);
Value ResultLayer::sLevel(0);
Value ResultLayer::sJob(3);
Value ResultLayer::sJobStrings[5] = { Value("sword1"), Value("sword2"), Value("sword3"), Value("sword4"), Value("sword5") };

void ResultLayer::onExit()
{
	Layer::onExit();
	ResultLayer::sUpWhere = 0;
	ResultLayer::sDownWhere = 0;
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(FIGHT_RESUTLT_NETOVER);
}

bool ResultLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		//CC_BREAK_IF(!initData());
		ITEM_CONFIG_MGR::instance()->load_icon_config_data();


		CC_BREAK_IF(!initRoot());
//		CC_BREAK_IF(!initUpCards());
		Director::getInstance()->getEventDispatcher()->addCustomEventListener( "eventBackMainCity", CC_CALLBACK_0(ResultLayer::eventBackMainCity,this) );
		bRet = true;

	} while (false);

	return bRet;
}

bool ResultLayer::initRoot()
{
	bool bRet = false;
	do
	{
		root = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/finish.json");
		CC_BREAK_IF(!root);
		_adapterLayout = dynamic_cast<Layout*>(Helper::seekWidgetByName(root, "adapter_layer"));
	
		nextBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "next"));
		CC_BREAK_IF(!nextBtn);
        nextBtn->setBright(false);
        nextBtn->setEnabled(false);
        nextBtn->setTouchEnabled(false);
		nextBtn->addTouchEventListener(CC_CALLBACK_2(ResultLayer::nextCallback,this));

		backBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "town_back"));
		CC_BREAK_IF(!backBtn);
        backBtn->setBright(false);
        backBtn->setEnabled(false);
        backBtn->setTouchEnabled(false);
		backBtn->addTouchEventListener(CC_CALLBACK_2(ResultLayer::backCallback, this));

		money_icon = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, "money_icon"));
		CC_BREAK_IF(!money_icon);

		money_icon1 = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, "money_icon_1"));
		CC_BREAK_IF(!money_icon1);

		times = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "AtlasLabel_40"));
		CC_BREAK_IF(!times);

		addChild(root);

        waitLayer = LayerColor::create(Color4B(166,166,166,100));
        auto to = Sequence::createWithTwoActions(ProgressTo::create(2, 100), ProgressTo::create(0,0));
        auto pt = ProgressTimer::create(Sprite::create("img/battle/skillLinkBg.png"));
        pt->setType(ProgressTimer::Type::RADIAL);
        pt->setPosition(Vec2(YNBaseUtil::WinSize.width/2, YNBaseUtil::WinSize.height/2));
        pt->runAction(RepeatForever::create(to));
        waitLayer->setSwallowsTouches(true);
        waitLayer->addChild(pt);
        addChild(waitLayer);
        
        auto resultListener = EventListenerCustom::create(FIGHT_RESUTLT_NETOVER, CC_CALLBACK_0(ResultLayer::popResult, this));
        Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(resultListener, -1);
		bRet = true;

	} while (false);

    setSwallowsTouches(true);
	return bRet;
}

bool ResultLayer::initUpCards()
{
	for (int i = 0; i < CARD_NUM; i++)
	{
		std::string cardNames("Btn_Up_");
		Value cardIdx(i);
		std::string cardIdxStrs = cardIdx.asString();
		cardNames += cardIdxStrs;
		upCards[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(root, cardNames.c_str()));
		upCards[i]->addTouchEventListener(CC_CALLBACK_2(ResultLayer::upCardsCallback2, this));
		upCards[i]->setTag(i);
        upCards[i]->setVisible(true);
		_upSprites[i] = Sprite::create();
		//_upSprites[i]->setContentSize( Size(95,125) );
		//_upSprites[i]->setScale((float)95 / 150, (float)125 / 197);
//		_upSprites[i]->setPosition(Vec2(upCards[i]->getContentSize().width/2, upCards[i]->getContentSize().height/2));
		_upSprites[i]->setPosition(upCards[i]->getPosition());
        _upSprites[i]->setVisible(true);
        upCards[i]->getParent()->addChild(_upSprites[i]);
		auto animation = cocos2d::Animation::create();
		Value preFileName("create-role/rotations/");
		Value suffFileName(".png");
		for (int j = 0; j < 5; j++)
		{
			Value midFileName(j + 1);
			Value fileName(preFileName.asString() + midFileName.asString() + suffFileName.asString());
			animation->addSpriteFrameWithFileName(fileName.asString());
		}
		animation->setDelayPerUnit(0.5 / 5);
		//animation->setRestoreOriginalFrame(true);
		//animation->setLoops(true);
		auto animate = Animate::create(animation);
		auto hide = CallFunc::create(CC_CALLBACK_0(ResultLayer::hideEffect, this,i));
		_effectUpSequences[i] = Sequence::create(animate, hide, nullptr);
		_effectUpSequences[i]->retain();
//		_adapterLayout->addChild(_upSprites[i], 1);
		if ( !ResultLayer::sWinOrLose.asBool() && i>0 )
		{
			upCards[i]->setVisible(false);
			_upSprites[i]->setVisible(false);

		}

	}
	return true;

}

void ResultLayer::upCardsCallback2(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type)
{
	auto sender = (Button*)pSender;
	int index = sender->getTag();
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
        sender->setVisible(false);
        //_upSprites[0]->runAction(_effectSequence);
        _upSprites[index]->runAction(_effectUpSequences[index]);
        sClickTimes--;
        Value tms(sClickTimes);
        if (sClickTimes >= 0)
        {
          times->setString(tms.asString());

        }
        else
        {
          sClickTimes = 0;
        }

        if (0 == sUpWhere)
        {
          money_icon->setAnchorPoint(Vec2(0.5f, 0.5f));
          money_icon->setPosition(Vec2(60, 60));
          money->setAnchorPoint(Vec2(0.5f, 0.5f));
          money->setPosition(Vec2(60, 98));
          money_icon->setParent(nullptr);
          money->setParent(nullptr);
          money_icon->setVisible(false);
          money->setVisible(false);
          _upSprites[index]->addChild(money_icon);
          _upSprites[index]->addChild(money);

        }
        else
        {
          for (int i = sUpWhere; i < itemIds.size()+1; i++)
          {
              this->itemIds[i-1];
              Game_Data::Item_Config* config = ITEM_CONFIG_MGR::instance()->get_item_config(this->itemIds[i-1]);
              if (config == NULL)
                  break;
              //const char * szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(item->config->icon);
              const char * szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(config->icon);
              std::string p("icon/");
              p+=szPath;

              //281479271678028 281479271677995 281479271677992 281479271678021
              ImageView* one = ImageView::create();
              one->loadTexture(p.c_str());
              one->setAnchorPoint(Vec2(0.5f, 0.5f));
              one->setPosition(Vec2(60, 88));
              one->setVisible(false);
              _upSprites[index]->addChild(one);
              break;
          }

        }																	
        sUpWhere++;
        if (sUpWhere > itemIds.size())
        {
          sUpWhere = itemIds.size() + 1;

        }
        sender->setTouchEnabled(false);


	}
		break;
	default:
		break;
	}
}

#include <fstream>

void ResultLayer::nextCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type)
{
	/************************************************************************/
	// 点击下一关按钮方法回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 如果不可以挑战下一关
	//sendNext();//send get awards packet
	if (!INSTANCE_DATA_MGR::instance()->RequestChallengeNextInstance())
	{
		return;
		// 填出提示框提示玩家挑战下一关失败
		// ...

		// 返回主城,以后还需要添加判断阵容以及等级
		// ...
		vector<uint64> para;
		para.clear();
		para.push_back(1);
		Game_Logic::Game_Content_Interface::instance()->exec_interface("enterscene", para);
	}
}


bool ResultLayer::NextInstanceDataBeenReceived(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 下一关副本数据已经被接收
	std::vector<uint64> para;
	gm_interface.get_para(para);
	int scene_id = para[1];
	auto battle = BattleField::instance();
	battle->setSceneId(scene_id);
	auto fightScene = GameScene::create();
	Director::getInstance()->replaceScene(fightScene);
	return true;
}


void ResultLayer::backCallback(Ref*pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::ENDED:
        {
			//std::vector<uint64> para;
			//Game_Logic::Game_Content_Interface::instance()->exec_interface("send_get_player_info", para);

			int player_id = Account_Data_Mgr::instance()->get_current_role_id();
			Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
			vector<uint64> para;
			para.clear();
			para.push_back(player_id);
			para.push_back(ResultLayer::sCurInstanceId);
			Game_Logic::Game_Content_Interface::instance()->exec_interface("sendbackmaincity", para);

        }
            break;
        default:
            break;
    }
}

void ResultLayer::popResult()
{
    removeChild(waitLayer);
    current_instance_data cid;
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    INSTANCE_DATA_MGR::instance()->get_player_instance(player_id, cid);
    if(cid.get_instance_state() == current_instance_data::INSTANCE_STATE_SUC)
    {
        auto title = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, "Image_result"));
        title->setVisible(true);
        
        expAts = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "exp"));
        Value expV(ResultLayer::sExp);
        expAts->setVisible(true);
        expAts->setString(expV.asString());
        
        auto clearTime = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "clear_time"));
        int clearSecond = cid.get_time_grad();
        time_t tt = clearSecond;
        struct tm *n;
        n = gmtime(&tt);
        std::string timeStr(Convert2String(n->tm_min)+":"+Convert2String(n->tm_sec));
        clearTime->setString(timeStr);
        clearTime->setVisible(true);
        
        auto scoreImg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, "Img_Score"));
        int score = cid.get_instance_score();
        std::string scoreImgName("review_c_big");
        if (score >= 85) {
            scoreImgName = "review_s_big";
            auto scoreback =  dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, "black_review"));
            scoreback->setVisible(true);
        }else if (score >= 65) {
            scoreImgName = "review_a_big";
        }else if (score >= 35) {
            scoreImgName = "review_b_big";
        }
        scoreImg->loadTexture("img/scene/"+scoreImgName+".png");
        scoreImg->setVisible(true);
        scoreImg->setScale(0.2);
        auto scaleBig = ScaleTo::create(0.5f, 1.8);
        auto scaleSmall = ScaleTo::create(0.5, 1.0);
        auto seq = Sequence::create(scaleBig, scaleSmall,nullptr);
        scoreImg->runAction(seq);
        
        money = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "money"));
        Value moneyV(ResultLayer::sMoney);
        money->setString(moneyV.asString());

        map<int, int> cardIds;
        cardIds.clear();
        cardIds.insert(make_pair(0, 0));
        cardIds.insert(make_pair(1, 1));
        cardIds.insert(make_pair(2, 2));
        cardIds.insert(make_pair(3, 3));
    
        itemIds.clear();
    
        for (int i = 0; i < CARD_NUM; i++)
        {
            uint64 item_id = cid.get_item_award_id_que();
            if (item_id == 0)
                break;
            itemIds.push_back(item_id);
            if (item_id == 0)
                break;
            if (0 == cardIds.size())
            {
                break;
            }
    
        }
        initUpCards();
        times->setString(Convert2String(CARD_NUM));
        times->setVisible(true);
    }else{
        auto title = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, "Image_7"));
        title->setVisible(true);
        expAts = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "exp"));
        Value expV(ResultLayer::sExp);
        expAts->setString(expV.asString());
        
        auto clearTime = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "clear_time"));
        int clearSecond = cid.get_time_grad();
        time_t tt = clearSecond;
        struct tm *n;
        n = gmtime(&tt);
        std::string timeStr(Convert2String(n->tm_min)+":"+Convert2String(n->tm_sec));
        clearTime->setString(timeStr);
        
        times->setString("0");
        times->setVisible(true);
    }
    
    backBtn->setBright(true);
    backBtn->setEnabled(true);
    backBtn->setTouchEnabled(true);

//	bool bWinOrLose = ResultLayer::sWinOrLose.asBool();
//	ResultLayer* ly = create();
	int nTemp = INSTANCE_DATA_MGR::instance()->get_current_instance_stage_id();
	int nCurrentInstanceID = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
	if (nTemp == ENDLESS_TOWER_STATE_ID && (cid.get_instance_state() == current_instance_data::INSTANCE_STATE_SUC) && nCurrentInstanceID != ENDLESS_TOWER_LAST_FLOOR)
	{
        nextBtn->setBright(true);
        nextBtn->setEnabled(true);
        nextBtn->setTouchEnabled(true);
		nextBtn->setVisible(true);
	}
	else
	{
		nextBtn->setVisible(false);
	}
}

bool ResultLayer::waiting(Game_Logic::Game_Interface& gm_interface)
{
	auto s = Director::getInstance()->getWinSize();
	auto scene = Director::getInstance()->getRunningScene();

	auto to = Sequence::createWithTwoActions(ProgressTo::create(2, 100), ProgressTo::create(0,0));

	auto pt = ProgressTimer::create(Sprite::create("img/battle/skillLinkBg.png"));
	pt->setType(ProgressTimer::Type::RADIAL);
	pt->setPosition(Vec2(s.width/2,s.height/2));
	pt->runAction(RepeatForever::create(to));
	scene->addChild(pt,100,"waiting");
	return true;
}

void ResultLayer::hideEffect(int index)
{
	auto upVec = _upSprites[index]->getChildren();
	for (auto child : upVec)
	{
		child->setVisible(true);
	}
	
	//auto downsVec = _downSprites[index]->getChildren();
	//for (auto child : downsVec)
	//{
	//	child->setVisible(true);
	//}

}

void ResultLayer::eventBackMainCity()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    auto battle = BattleField::instance();

	vector<uint64> para;
	para.clear();
	para.push_back(player_id);
	para.push_back(battle->getSceneId());
	Game_Logic::Game_Content_Interface::instance()->exec_interface("sendbackmaincity", para);
}
