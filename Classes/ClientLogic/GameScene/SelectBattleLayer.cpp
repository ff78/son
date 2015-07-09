#include "SelectBattleLayer.h"
//#include "cocostudio/CocoStudio.h"
#include "../../Player_Account/Account_Data_Mgr.h"
#include "../../Play_System/Formula_Function_Instance.h"
//#include "Item_System/Item_Desc_Config_Mgr.h"
#include "../../Character_System/Character_Mgr.h"
#include "../../Character_System/Player.h"
//#include "Item_System/Item_Config_Data.h"
//#include "Common/GameDefine.h"
//#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "../../Game_Interface/game_content_interface.h"
#include "../FightDefine.h"
#include "GameScene.h"

#include "../../UI_Interface/UI_MainMenu_Layer.h"

SelectBattleLayer::SelectBattleLayer(void):
currScore(0)
{
}

SelectBattleLayer::~SelectBattleLayer(void)
{
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(ENTER_FIGHT_NETOVER);
}

bool SelectBattleLayer::init()
{
    bool bRet = false;
    do
    {
		//_battle = BattleField::instance();
		//_battle->readFile("GameData/scene_fight.json");

        CC_BREAK_IF(!Layer::init());
		auto colorLayer = LayerColor::create();
 
        CC_BREAK_IF(!initRoot());
        
		Size visibleSize = Director::getInstance()->getVisibleSize();
		visibleSize = Director::getInstance()->getWinSize();
		pageView = MyPageView::create(Size(COIN_WIDTH*3, COIN_HEIGHT+40), this);
		//pageView->setAnchorPoint(Vec2(0.5f,0.5f));
		pageView->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);
		//pageView->setPosition(Vec2((visibleSize.width - COIN_WIDTH)* 0.5, (visibleSize.height - COIN_HEIGHT)*0.5 + 20));
		//pageView->setPosition(Vec2(visibleSize.width*0.5 - COIN_WIDTH - COIN_WIDTH*0.5 - COIN_GAP, (visibleSize.height - COIN_HEIGHT)*0.5 + 20));
		//pageView->setPosition(Vec2(visibleSize.width*0.5 - COIN_WIDTH*0.5 - COIN_GAP - 160, (visibleSize.height - COIN_HEIGHT)*0.5));
		pageView->setPosition(Vec2(780 * 0.5 - COIN_WIDTH*0.5 - COIN_GAP, (visibleSize.height - COIN_HEIGHT)*0.5));
		
		pageView->setClippingToBounds(false); 

		auto clipLayout = dynamic_cast<Layout*>(Helper::seekWidgetByName(root, "Pnl_Clip") );	
		clipLayout->addChild(pageView, 100);

        bRet = true;
        
    } while (false);
    
    auto exitListener = EventListenerCustom::create(ENTER_FIGHT_NETOVER, CC_CALLBACK_0(SelectBattleLayer::enterFight, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(exitListener, -1);

    return bRet;

}

void SelectBattleLayer::onEnter()
{
	Layer::onEnter();
	//pageView->adjustCallback(pageView);
	int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
	pageView->scrollToPage(mIndex);
	//pageView->scrollToPage(5);
	//this->setScale(0.2,0.2);
	//auto scaleTo1 = Actions::getInstance()->getActionScaleBig();
	//this->runAction( Spawn::create(scaleTo1, nullptr) );

}

void SelectBattleLayer::onExit()
{
    Layer::onExit();
	//pageView->adjustCallback(pageView);
}

bool SelectBattleLayer::initRoot()
{
    bool bRet = false;
    do
    {
		root = dynamic_cast<cocos2d::ui::Widget*>( cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/stage_select.json") );
        CC_BREAK_IF(!root);
        addChild(root);
        
        for( int i=0 ; i<3 ; ++i )
        {
            std::string itemBgStr = "item_";
            char txt[256];
            sprintf( txt, "%d", i);
            itemBgStr += txt;
            itembg[i] = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, itemBgStr));
        }
        
        for( int i=0 ; i<2 ; ++i )
        {
            std::string checkStr = "CheckBox_";
            char txt[256];
            sprintf( txt, "%d", i);
            checkStr += txt;
            difficultBox[i] = dynamic_cast<CheckBox *>(Helper::seekWidgetByName(root, checkStr));
            difficultBox[i]->addEventListener(CC_CALLBACK_2(SelectBattleLayer::selectedEvent, this));
        }
        difficultBox[0]->setSelectedState(true);
        difficultBox[1]->setSelectedState(false);
        
        
        startBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "Button_Start"));
        startBtn->addTouchEventListener(CC_CALLBACK_2(SelectBattleLayer::pressStart, this));
		//startBtn->addTouchEventListener(this, toucheventselector(SelectBattleLayer::pressStart));


		auto close = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(root, "close_0_0"));
		//closeBtn = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(root, "close_0_0"));
		CC_BREAK_IF(!close);
		//close->addTouchEventListener(this, toucheventselector(SelectBattleLayer::closeStageCallBack));
		close->addTouchEventListener(CC_CALLBACK_2(SelectBattleLayer::closeStageCallBack, this));

        bRet = true;
        
    } while (false);
    
    return bRet;
}

void SelectBattleLayer::closeStageCallBack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;
	//this->removeFromParent();
	//auto scaleTo0_2 = Actions::getInstance()->getActionScaleSmall();
	//auto blendAndDelay = Spawn::create(FadeOut::create(0.5),ScaleTo::create(0.5,0.5),nullptr );
	auto delay = DelayTime::create(0.1);
	auto remove = CallFunc::create(CC_CALLBACK_0(SelectBattleLayer::removeFromParent,this) );
	this->runAction(Sequence::create(delay, remove, nullptr));
}

void SelectBattleLayer::removeStage()
{
	this->removeFromParent();
	UI_MainMenu_Layer::get_instance()->showGuide();

}

void SelectBattleLayer::pageViewEvent(Ref*pSender, PageView::EventType type)
{
    switch (type)
    {
        case PageView::EventType::TURNING:
        {
            auto idx = pageV->getCurPageIndex();
            
            
            auto curPage = pageV->getPage(idx);
            int instanceId = curPage->getTag();

            startBtn->setEnabled(curPage->isEnabled());
            startBtn->setBright(curPage->isEnabled());
            //startBtn->setTouchEnabled(curPage->isEnabled());

            resetInstanceDetail(instanceId);
//             curPage->setScale(1.2f);
//            auto pv = dynamic_cast<PageView*>(pSender);
//            CCLOG("now at %d",pv->getCurPageIndex());
        }
            break;
        default:
            break;
    }
    
}

void SelectBattleLayer::updateData()
{

	updateBig();

	updateSmall(_bigId);

}

void SelectBattleLayer::RefreshLayer(const int nStateID)
{

}

void SelectBattleLayer::resetInstanceDetail(int instanceId)
{
    INSTANCE_DATA_MGR::instance()->set_current_instance_id(instanceId);
    
    vector<uint> para;
    //副本名称字典id
    para.clear();
    Formula_Function_Instance::instance()->get_para_list_from_instance_data(instanceId, "instance_attribute","instance_name","instance_name",para);
    int name_dic_id = -1;
    if( para.size() >=1 )
    {
        name_dic_id = para[0];
    }
    else
    {
        return;
    }
    auto instanceName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(name_dic_id);
    auto stageName = dynamic_cast<Text*>(Helper::seekWidgetByName(root,"stage_name"));
    stageName->setString(instanceName);
    
    //需要体力
    Formula_Function_Instance::instance()->get_para_list_from_instance_data(instanceId, "instance_attribute","condition","energy",para);
    if ( para.size() >= 1)
    {
        char txt[256];
        sprintf( txt, "%d", para[0]);
        auto consumeEnergy = dynamic_cast<Text*>(Helper::seekWidgetByName(root,"consume_energy"));
        consumeEnergy->setString(txt);
    }
    
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return;
    }
    auto consumeEnergy = dynamic_cast<Text*>(Helper::seekWidgetByName(root,"energy_point"));
    
    char txt[256];
    sprintf( txt, "%d", player->get_energy());
    consumeEnergy->setString(txt);
    
    //设置 道具奖励 图标
    for (int i = 0; i < 3; i++) {
        itembg[i]->setVisible(false);
    }
    Game_Data::game_element_list_t ele_lst;
    Formula_Function_Instance::instance()->get_element_list_from_instance_data(instanceId, "instance_attribute","result_content","award_item",ele_lst);
    
    string comp_key = "award_item";
    Game_Data::game_element_list_t::iterator itg;
    
    int item_count = 0;
    for( itg = ele_lst.begin(); itg != ele_lst.end(); ++ itg)
    {
        if(!comp_key.compare((*itg).get_command()))
        {
            para.clear();
            (*itg).get_para_list_in_vector( para);
            if( para.size() > 2)
            {
                
                show_item_icon(para, item_count);
                ++item_count ;
            }
        }
    }
}

int SelectBattleLayer::show_item_icon(std::vector<uint>& para, int item_count )
{
    int item_id = 0;
    int item_size = 0;
    if( para.size() >= 2)
    {
        item_id = (int)para[0];
        item_size = (int)para[1];
        
        log("item_cout=%d",item_count);
        
        Game_Data::Item_Config* item_config = ITEM_CONFIG_MGR::instance()->get_item_config(item_id);
        Game_Data::Item_Config* config = NULL;
        if (item_config->type == Game_Data::IT_EQUIPMENT_DEPOT)
        {
            Game_Data::Equipment_Depot_Config* equipment_depot_config = reinterpret_cast<Game_Data::Equipment_Depot_Config*>(item_config);
            config = ITEM_CONFIG_MGR::instance()->get_item_config(equipment_depot_config->item_base_id);
        }
        else
        {
            config = item_config;
        }
        
        ITEM_CONFIG_MGR::instance()->load_icon_config_data();
        
        const char* szTexture = ITEM_CONFIG_MGR::instance()->get_icon_path(config->icon);
        std::string p("icon/");
        p+=szTexture;
        itembg[item_count]->setVisible(true);
        itembg[item_count]->loadTexture(p.c_str());
        itembg[item_count]->setTag(item_id);
    }
    
    return 0;
}

void SelectBattleLayer::selectedEvent(Ref* pSender,CheckBox::EventType type)
{
    switch (type)
    {
        case CheckBox::EventType::SELECTED:
            if (pSender == difficultBox[0]) {
                difficultBox[1]->setSelectedState(false);
            }
            if (pSender == difficultBox[1]) {
                difficultBox[0]->setSelectedState(false);
            }
            break;
            
        case CheckBox::EventType::UNSELECTED:
            if (pSender == difficultBox[0]) {
                difficultBox[1]->setSelectedState(true);
            }
            if (pSender == difficultBox[1]) {
                difficultBox[0]->setSelectedState(true);
            }
            break;
            
        default:
            break;
    }
    
}

void SelectBattleLayer::pressStart(Ref *pSender, Widget::TouchEventType type)
{
    switch(type)
    {
        case Widget::TouchEventType::ENDED:
        {
            int role_id = Account_Data_Mgr::instance()->get_current_role_id();
            auto player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
            
            if(!player) return;
            
            auto instanceId = INSTANCE_DATA_MGR::instance()->get_current_instance_id();

            vector<uint> para;
            Formula_Function_Instance::instance()->get_para_list_from_instance_data(instanceId, "instance_attribute","condition","energy",para);
            if ( para.size() > 0)
            {
                int energy = player->get_energy();
                if (energy < (int)para[0])
                {
                    DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_ENERGY);
                    return;
                }
            }
                     
            int instance_id_send = INSTANCE_DATA_MGR::instance()->get_current_instance_id();

            vector<uint64> param;
            param.push_back(instance_id_send);
            param.push_back(0);
            Game_Logic::Game_Content_Interface::instance()->exec_interface("selectinstance", param);

        }
        break;
    }

}

void SelectBattleLayer::enterFight()
{
	/************************************************************************/
	// 玩家点击挑战按钮方法回调
    auto fightScene = GameScene::create();
    fightScene->setFirstPass(currScore==0);
    Director::getInstance()->replaceScene(fightScene);
}

/********************************** dely **********************************/
void SelectBattleLayer::addPages()
{
	for (int i = 0; i < COIN_COUNT;i++)
	{
		auto sprite = Sprite::create("map_back.png");
		Size coinSize = sprite->getContentSize();
		sprite->setPosition(coinSize.width*0.5 , coinSize.height*0.5);
		std::string str = StringUtils::format("%d", i);
		Label* label = Label::createWithSystemFont(str, "Arial", 60);
		label->setTextColor( Color4B(0,0,0,255) );
		Size size = sprite->getContentSize();
		label->setPosition(size.width*0.5,size.height*0.5);
		sprite->addChild(label);
		pageView->addPage(sprite);
	}

}

Size SelectBattleLayer::sizeForPerPage()
{
	return Size(COIN_WIDTH+COIN_GAP,COIN_HEIGHT);
}

void SelectBattleLayer::pageViewDidScroll(MyPageView* pageView)
{
	//log("pageViewDidScroll");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float midX = visibleSize.width / 2 ;
	float offsetX = this->pageView->getContentOffset().x;
	float tmp = COIN_WIDTH / 2.0f;
	//float tmp = 0.f;

	float scale = 1.2f;
	scale = scale - 1;

	for (int i = 0; i < pageView->pageCount;i++)
	{
		Node* sprite = this->pageView->getPageAtIndex(i);
		float positionX = sprite->getPositionX();
		float endX = positionX + offsetX + midX - tmp;
		if ( 0 < endX && endX <= midX)
		{
			float x = endX / midX * scale + 1;
			sprite->setScale(x);
			x = (endX / midX * 0.7 + 0.3) * 255;
			sprite->setOpacity(x);
		}
		else if (endX > midX && endX < visibleSize.width)
		{
			float tmp2 = endX - midX;
			tmp2 = midX - tmp2;
			float x = tmp2 / midX * scale + 1;
			sprite->setScale(x);
			x = ( tmp2 / midX * 0.7 + 0.3 ) * 255;
			sprite->setOpacity(x);
		}
		else
		{
			sprite->setScale(1.0f);
			sprite->setOpacity(255 * 0.3);
		}


	}

}

void SelectBattleLayer::myPageViewTurned()
{
	log("where:%d", pageView->getCurrentIndex() );
	auto idx = pageView->getCurrentIndex();


	auto curPage = dynamic_cast<Layout*>( pageView->getPageAtIndex(idx) );
	int instanceId = curPage->getTag()/10;
    currScore = curPage->getTag()%10;
    
	bool tmp = curPage->isBright();
	//startBtn->setEnabled(curPage->isEnabled());
	startBtn->setEnabled(tmp);

	//startBtn->setBright(curPage->isEnabled());
	startBtn->setBright(tmp);

	//startBtn->setTouchEnabled(curPage->isEnabled());
	startBtn->setTouchEnabled(tmp);

	resetInstanceDetail(instanceId);
}

void SelectBattleLayer::clickStageCallBack(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	int tag = ( (Button*)pSender )->getTag();
	_bigId = tag;
	updateSmall(_bigId);
}

void SelectBattleLayer::updateBig()
{
	/************************************************************************/
	// 刷新选择关卡界面

	// 1.获得大区章节开启列表,并确定章节
	// 1_1. 获得大区章节开启列表
	std::map<int, int> stage_lst;
	INSTANCE_DATA_MGR::instance()->get_stage_data(stage_lst);

	// 1_2. 确定章节（注:第一章一关未过，须手动打开第一章。第一章所有关卡通过后，第二章会自动开启）
	_bigId = 0;
	int nTemp = INSTANCE_DATA_MGR::instance()->get_current_instance_stage_id();
	if (nTemp != ENDLESS_TOWER_STATE_ID)
	{
		int stageId = 0;
		for (auto s : stage_lst)
		{
			if (s.first == ENDLESS_TOWER_STATE_ID)
				continue;

			if (s.second >= 0)
			{
				stageId = s.first;
			}
		}
		if (stageId == 0)
		{
			stageId = stage_lst.begin()->first;
		}
		_bigId = stageId;
	}
	else
	{
		_bigId = ENDLESS_TOWER_STATE_ID;
	}
	INSTANCE_DATA_MGR::instance()->set_current_instance_stage_id(_bigId);

	/************************************************************************/
	// 修改显示层
	// 1. 添加章节的标题（地之章、天之章等）

	auto stageScroll = dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(root, "Scr_Top"));
	stageScroll->getInnerContainer()->removeAllChildren();
	stageScroll->getInnerContainer()->setAnchorPoint(Vec2(0, 0));

	float x = 0;
	for (auto s : stage_lst)
	{
		auto config = INSTANCE_DATA_MGR::instance()->get_area_ui_config(s.first);
		std::string resPath("img/stageIcon/");
		resPath += config->iconName;
		auto stageButton = Button::create(resPath + ".png", resPath + "_down.png", resPath + "_dis.png", TextureResType::LOCAL);
		stageButton->setEnabled(true);

		auto btnSize = stageButton->getContentSize();
		stageButton->setAnchorPoint(Vec2(0, 0.5));
		stageButton->setPosition(Vec2(x, stageScroll->getInnerContainer()->getContentSize().height / 2));
		x += 150;
		stageButton->setTag(s.first);
		stageButton->addTouchEventListener(CC_CALLBACK_2(SelectBattleLayer::clickStageCallBack, this));
		stageScroll->getInnerContainer()->addChild(stageButton);

		if (_bigId != ENDLESS_TOWER_STATE_ID)
		{
			if (s.second < 0 && _bigId != s.first)
			{
				stageButton->setEnabled(false);
				stageButton->setBright(false);
				stageButton->setTouchEnabled(false);
			}
			if (s.first == ENDLESS_TOWER_STATE_ID)
			{
				stageButton->setVisible(false);
			}
		}
		else
		{
			stageButton->setPosition(Vec2(stageScroll->getInnerContainer()->getContentSize().width / 2 - 250, stageScroll->getInnerContainer()->getContentSize().height / 2));
			break;
		}
	}

}

void SelectBattleLayer::updateSmall(int bigId)
{
	pageView->removeAllPage();
	//pageView->removeAllChildren();
	//获得章节内场景得分, 确定默认场景选择
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Area_UI_Config* auc = INSTANCE_DATA_MGR::instance()->get_area_ui_config(bigId);;
	list<int> instance_lst = auc->list_instance_id;

	current_instance_data cid;
	int instanceId = 0;
	int instanceScore = 0;
	int focusStage = -1;
	bool first_instance = true;
	for (auto incId : instance_lst)
	{
		cid.reset();
		cid.set_instance_id(incId);

		// 判断当前关卡是不是玩家已经通关的关卡
		if ((Account_Data_Mgr::instance()->get_is_show_all_stage() == 0) && (-1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid)))
		{
			if (first_instance)
			{
				instanceId = cid.get_instance_id();
				instanceScore = cid.get_instance_score();
				first_instance = false;
				focusStage++;
			}
			continue;
		}
		instanceId = cid.get_instance_id();
		instanceScore = cid.get_instance_score();
		focusStage++;
//        if ((Account_Data_Mgr::instance()->get_is_show_all_stage() == 0) && cid.get_instance_state() != current_instance_data::INSTANCE_STATE_SUC)
//        {
//            if (first_instance)
//            {
//                instanceId = cid.get_instance_id();
//                instanceScore = cid.get_instance_score();
//                first_instance = false;
//                focusStage++;
//            }
//            //continue;
//        }
//        else
//        {
//            instanceId = cid.get_instance_id();
//            instanceScore = cid.get_instance_score();
//            focusStage++;
//        }
	}

	if (instanceId == 0)
	{
		cid.reset();
		cid.set_instance_id(instance_lst.begin().operator*());
		instanceId = cid.get_instance_id();
		instanceScore = cid.get_instance_score();
		focusStage = 0;
	}

	mIndex = instanceId < 50000 ? (instanceId - 10000) : (instanceId - 50000);

	INSTANCE_DATA_MGR::instance()->set_current_instance_id(instanceId);

	//int condition = _battle->getCondition();

	for (auto incId : instance_lst)
	{
		cid.reset();
		cid.set_instance_id(incId);
		auto stageRoot = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/stage.json"));
		auto tmp = dynamic_cast<Layout*>(Helper::seekWidgetByName(stageRoot, "cell0_0_0"));
		//auto tmp2 = dynamic_cast<Layout*>(Helper::seekWidgetByName(stageRoot, "cell0_0_0"));
		//if (condition>0&&condition<6)

		//auto typeTxt = dynamic_cast<Text*>(Helper::seekWidgetByName(stageRoot, "Txt_Type"));
		//typeTxt->setString();
		
		auto config = INSTANCE_DATA_MGR::instance()->get_instance_ui_config(incId);
		std::string resPath("img/stageIcon/");
		resPath += config->iconName;
		resPath += ".png";

		auto cell = tmp->clone();
		cell->setTag(incId*10);
		cell->setEnabled(false);
		if (incId > instanceId) {
			cell->setColor(Color3B(45, 45, 45));
			//cell->setEnabled(false);
			cell->setBright(false);
		}

		auto tmp2 = dynamic_cast<ImageView*>(Helper::seekWidgetByName(cell, "map_temp0"));
		tmp2->loadTexture(resPath);
		Size coinSize = cell->getContentSize();
		cell->setAnchorPoint(Vec2(0.5f, 0.5f));
		cell->setPosition(Vec2(coinSize.width*0.5, coinSize.height*0.5));
		pageView->addPage(cell);


		if ((Account_Data_Mgr::instance()->get_is_show_all_stage() == 0) &&
			(-1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid)))
		{
			continue;
		}
        
		instanceScore = cid.get_instance_score();
        int pass = (instanceScore>0?1:0);
        cell->setTag(cell->getTag()+pass);
        
		std::string rankName("");
		int visibelStarsNum = 0;
		if (instanceScore >= 85)
		{
			rankName = "review_s";
		}
		else if (instanceScore < 85 && instanceScore >= 60)
		{
			rankName = "review_a";
		}
		else if (instanceScore > 35)
		{
			rankName = "review_b";
        }else if (instanceScore > 0) {
            rankName = "review_c";
		}
        if (rankName == "") {
            continue;
        }
		auto rank = dynamic_cast<ImageView*>(cell->getChildByName(rankName));
		if (rank == NULL)
			continue;

		rank->setVisible(true);
		rank->setLocalZOrder(128);
	}
	pageView->scrollToPage(mIndex);
    auto curPage = dynamic_cast<Layout*>( pageView->getPageAtIndex(mIndex) );
    currScore = curPage->getTag()%10;

	// 3. 添加当前关卡的详细信息
	resetInstanceDetail(instanceId);

}