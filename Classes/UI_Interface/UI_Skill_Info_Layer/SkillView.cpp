#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"
#include "Common/GameDefine.h"
#include "Network_Common/global_macros.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"

#include "TouchSkill/SkillManager.h"
#include "TouchSkill/LogicSkill.h"

#include "SkillView.h"
#include "MyImageView.h"
#include "../../ClientLogic/Utils/BaseUtils.h"
#include "../../ClientLogic/Actor/Effect.h"

using namespace ui;
using namespace cocos2d;
using namespace cocostudio;

SkillView::SkillView()
{
	_leftIndex = 0;
	_rightIndex = 0;

	_scrolView = nullptr;
	_selectedImages[0] = nullptr;
	_selectedImages[1] = nullptr;
	_selectedImages[2] = nullptr;
	_selectedImages[3] = nullptr;

	_currentSkillNameText  = nullptr;
	_currentSkillLevelText = nullptr;
	_currentSkillDescText  = nullptr;

	_nextSkillNameText	   = nullptr;
	_nextSkillLevelText    = nullptr;
	_nextSkillDescText     = nullptr;

	_arrowImage			   = nullptr;

	_roleLayer			   = nullptr;

	_frontLayer			   = nullptr;
	_midLayer			   = nullptr;
	_backLayer			   = nullptr;

	_boneArmature		   = nullptr;

}

SkillView::~SkillView()
{
	_leftIndex = 0;
	_rightIndex = 0;

	_scrolView			   = nullptr;
	_selectedImages[0]	   = nullptr;
	_selectedImages[1]     = nullptr;
	_selectedImages[2]     = nullptr;
	_selectedImages[3]	   = nullptr;

	_currentSkillNameText  = nullptr;
	_currentSkillLevelText = nullptr;
	_currentSkillDescText  = nullptr;

	_nextSkillNameText     = nullptr;
	_nextSkillLevelText    = nullptr;
	_nextSkillDescText     = nullptr;

	_arrowImage			   = nullptr;
	
	_roleLayer			   = nullptr;

	_frontLayer			   = nullptr;
	_midLayer			   = nullptr;
	_backLayer			   = nullptr;

	_boneArmature		   = nullptr;

}

bool SkillView::init()
{
	if ( !Layer::init() )
		return false;
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(SKILL_UPGRADE_DONE, CC_CALLBACK_0(SkillView::onUpgradeFromServer,this) );


	ui::Widget* pLayer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Character_Skill/Character_Skill.ExportJson");
	addChild(pLayer);
	
	_arrowImage = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Image_15"));
	_arrowImage->setVisible(false);

	auto close = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Close_Btn"));
	close->setTouchEnabled(true);
	close->addTouchEventListener(this, toucheventselector(SkillView::onCloseCallBack) );

	auto upgrade = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Skill_Upgrade_Btn"));
	upgrade->setTouchEnabled(true);
	upgrade->addTouchEventListener( this, toucheventselector(SkillView::onUpgradeCallBack) );

	_scrolView = dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(pLayer, "Can_Be_Select_Skill_ScrollView"));
	//_scrolView = dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(pLayer, "Can_Be_Select_Skill_ScrollView"));

	_selectedImages[0] = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Selected_Skill_1th_BG"));
	_selectedImages[1] = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Selected_Skill_2th_BG"));
	_selectedImages[2] = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Selected_Skill_3th_BG"));
	_selectedImages[3] = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Selected_Skill_4th_BG"));

	_scrollViewSize = SkillManager::instance()->getAllSkills().size();
	//_scrollViewSize = 6;
	SkillManager::instance()->getSelSkills();
	initScrollView();
	initMyIcon();

	_currentSkillNameText = dynamic_cast<ui::Text*>(Helper::seekWidgetByName( pLayer, "Skill_Name") );
	_currentSkillLevelText = dynamic_cast<ui::Text*>(Helper::seekWidgetByName( pLayer, "Current_Level") );
	_currentSkillDescText = dynamic_cast<ui::Text*>(Helper::seekWidgetByName( pLayer, "Current_Level_Des") );
	
	_nextSkillNameText = dynamic_cast<ui::Text*>(Helper::seekWidgetByName( pLayer, "Next_Level_Des_Title") );
	_nextSkillLevelText = dynamic_cast<ui::Text*>(Helper::seekWidgetByName( pLayer, "Next_Level") );
	_nextSkillDescText = dynamic_cast<ui::Text*>(Helper::seekWidgetByName( pLayer, "Next_Level_Des") );

	std::string path("armature/");
	std::string roleName("");
	int id = Account_Data_Mgr::instance()->get_current_role_id();
	auto player = CHARACTER_MGR::instance()->get_character(id);
	int job = player->get_job();
	switch (job)
	{
	case 1:
	{
		roleName = "jianke";
		path += "jianke";
	}
		break;
	case 2:
		roleName = "nvqiang";
		path += "nvqiang";
		break;
	case 3:
		roleName = "wdj";
		path += "wdj";
		break;
	case 4:
		roleName = "wdj";
		path += "wdj";
		break;
	case 5:
		roleName = "wdj";
		path += "wdj";
		break;
	default:
		roleName = "wdj";
		path += "wdj";
		break;
	}
	path += ".ExportJson";

    
	cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(path);
	_boneArmature = cocostudio::Armature::create(roleName);
	_boneArmature->getAnimation()->playWithIndex(0);
//	_boneArmature->setPosition( Vec2(500,100) );
	_boneArmature->setScale(1.1);
    _boneArmature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(SkillView::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    _boneArmature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(SkillView::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	auto shadow = Sprite::create("img/scene/shadow.png");
	shadow->setAnchorPoint(Vec2(0.5, 0.5));
	shadow->setPosition(Vec2(0, -10));
//	addChild(shadow);
	auto frontEffect = Effect::create();
	auto backEffect = Effect::create();

	_roleLayer = Layer::create();

	_frontLayer = Layer::create();
	_frontLayer->addChild(frontEffect);

	_midLayer = Layer::create();
	_midLayer->addChild(_boneArmature);

	_backLayer = Layer::create();
	_backLayer->addChild(backEffect);

    _roleLayer->addChild(shadow);
	_roleLayer->addChild(_backLayer);
	_roleLayer->addChild(_midLayer);
	_roleLayer->addChild(_frontLayer);

    _roleLayer->setPosition(Vec2(YNBaseUtil::WinSize.width/2-100,100));
	addChild(_roleLayer, 999);

	return true;

}

void SkillView::onExit()
{
	Layer::onExit();
}

void SkillView::onEnter()
{
	Layer::onEnter();
}

void SkillView::onCloseCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
    SkillManager::instance()->postChanges2Server();

	this->removeFromParent();
}

void SkillView::onUpgradeCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	auto all = SkillManager::instance()->getAllSkills();
	int skillId = all[_leftIndex].getId();

	bool canUpgrade = SkillManager::instance()->canUpgrade(skillId);
	_arrowImage->setVisible(canUpgrade);
	if (canUpgrade)
	{
		int result = SkillManager::instance()->upgradeSkill(skillId);
		if (result != SKILL_UPGRADE_WAIT_RESPONSE)
			return;
		else
		{
			_arrowImage->setVisible(false);

		}

	}

}

void SkillView::initScrollView()
{
	auto all =  SkillManager::instance()->getAllSkills();
	//reverse( all.begin(), all.end() ) ;

	int nWholeWidth = _scrolView->getInnerContainerSize().width;
	int nWholeHeight = _scrolView->getInnerContainerSize().height;
	int nCellHight = 100 ;
	int nTotalHight = nCellHight * all.size();
	int nScrollviewHight = nTotalHight > nWholeHeight ? nTotalHight : nWholeHeight;
	_scrolView->setInnerContainerSize(Size(nWholeWidth, nScrollviewHight));
	_scrolView->jumpToBottom();

	std::vector<LogicSkill>::iterator it = all.begin();
	for (int nIndex = 0; it != all.end(); it++,nIndex++)
	{
		MyImageView * pCell = MyImageView::create();
		pCell->setPosition(Vec2(7, nIndex*nCellHight + 7));
		pCell->setTag(nIndex);
		_scrolView->addChild(pCell);
		std::string iconName = (*it).getIcon();

		std::string actionName = (*it).getAction();
		auto actions = YNBaseUtil::splitString(actionName, "|");
		auto actions2 = new std::vector<std::string>;
		for (auto action:actions)
		{
			actions2->push_back(action);
		}
		pCell->setUserData((void*)actions2);
        
        
        auto frontScaleStr = (*it).getFrontScale();
        if (frontScaleStr != "null") {
            auto fsStrVec = YNBaseUtil::splitString(frontScaleStr, "|");
            int i = 0, j = 0;
            for (auto fScaleSeq : fsStrVec)
            {
                std::vector<float> tmpVec;
                auto fScalePartVec = YNBaseUtil::splitString(fScaleSeq, ";");
                for (auto partStr : fScalePartVec)
                {
                    tmpVec.push_back(atof(partStr.c_str()));
                    j++;
                }
                pCell->frontScale.push_back(tmpVec);
                i++;
            }
        }
        
        auto frontEffStr = (*it).getFrontEff();
        if (frontEffStr != "null") {
            auto feStrVec = YNBaseUtil::splitString(frontEffStr, "|");
            int i = 0, j = 0;
            for (auto fEffSeq : feStrVec)
            {
                std::vector<std::string> tmpVec;
                auto fePartVec = YNBaseUtil::splitString(fEffSeq, ";");
                for (auto partStr : fePartVec)
                {
                    tmpVec.push_back(partStr);
                    j++;
                }
                pCell->frontEff.push_back(tmpVec);
                i++;
            }
        }

        auto backScaleStr = (*it).getBackScale();
        if (backScaleStr != "null") {
            auto bsStrVec = YNBaseUtil::splitString(backScaleStr, "|");
            int i = 0, j = 0;
            for (auto bScaleSeq : bsStrVec)
            {
                std::vector<float> tmpVec;
                auto bScalePartVec = YNBaseUtil::splitString(bScaleSeq, ";");
                for (auto partStr : bScalePartVec)
                {
                    tmpVec.push_back(atof(partStr.c_str()));
                    j++;
                }
                pCell->backScale.push_back(tmpVec);
                i++;
            }
        }
        
        auto backEffStr = (*it).getBackEff();
        if (backEffStr != "null") {
            auto beStrVec = YNBaseUtil::splitString(backEffStr, "|");
            int i = 0, j = 0;
            for (auto bEffSeq : beStrVec)
            {
                std::vector<std::string> tmpVec;
                auto bePartVec = YNBaseUtil::splitString(bEffSeq, ";");
                for (auto partStr : bePartVec)
                {
                    tmpVec.push_back(partStr);
                    j++;
                }
                pCell->backEff.push_back(tmpVec);
                i++;
            }
        }

		std::string iconPath = "img/joystick/" + iconName + ".png";
		pCell->loadTexture(iconPath);

		//auto pCellCursor = pCell->createCursor();
		//pCellCursor->setPosition(Vec2(7 - 12, nIndex*nCellHight + 7 - 12));
		//_scrolView->setTag(nIndex - 100);
		//_scrolView->addChild(pCellCursor);

		auto pCellBackImage = pCell->createBackImage();
		pCellBackImage->setPosition(Vec2(7, nIndex*nCellHight + 7));
		pCellBackImage->setTag(nIndex+1000);
		_scrolView->addChild(pCellBackImage);

		auto pCellClone = pCell->createClone();
		pCellClone->setPosition(Vec2(7, nIndex*nCellHight + 7));
		pCellClone->setTag(nIndex+1000000);
		_scrolView->addChild(pCellClone);
		pCellClone->loadTexture(iconPath);

	}	

}

void SkillView::initMyIcon()
{
	auto selected = SkillManager::instance()->getSelSkills();
	//reverse( selected.begin(), selected.end() );
	if (selected.size() != 4)
		return;
	
	int index = 0;
	for (auto& cell : selected)
	{
		std::string iconName = cell.getIcon();
		std::string iconPath = "img/joystick/" + iconName + ".png";
		_selectedImages[index]->loadTexture(iconPath);
		index++;
	}

}

void SkillView::loadScrollView()
{
	_scrolView->getInnerContainer()->removeAllChildren();

	//_scrolView->removeAllChildren();
	auto delay = DelayTime::create(0.2);
	auto fun = CallFunc::create( CC_CALLBACK_0(SkillView::initScrollView,this) );
	auto seq = Sequence::create(delay, fun, nullptr);
	_scrolView->runAction(seq);
	//initScrollView();
	return;
	auto all = SkillManager::instance()->getAllSkills();

	std::vector<LogicSkill>::iterator it = all.begin();
	for (int nIndex = 0; it != all.end(); it++, nIndex++)
	{
		auto cell = (MyImageView*)_scrolView->getChildByTag(nIndex);
		
		std::string iconName = (*it).getIcon();
		std::string iconPath = "img/joystick/" + iconName + ".png";
		cell->loadTexture(iconPath);

		auto clone = (ImageView*)_scrolView->getChildByTag(nIndex + 1000000);
		clone->loadTexture(iconPath);
	}

}

void SkillView::loadMyIcon()
{
	auto selected = SkillManager::instance()->getSelSkills();
	if (selected.size() != 4)
		return;
	int index = 0;
	for (auto& cell : selected)
	{
		std::string iconName = cell.getIcon();
		std::string iconPath = "img/joystick/" + iconName + ".png";
		_selectedImages[index]->loadTexture(iconPath);
		index++;
	}

}

void SkillView::playSkill(std::vector<std::string>* actionNames)
{
    armatureIndex = 0;
    animationCount = actionNames->size();
	_boneArmature->getAnimation()->playWithNames(*actionNames);
    _frontLayer->removeAllChildren();
    _backLayer->removeAllChildren();
}

void SkillView::changeSkill(int leftIndex, int rightIndex)
{
	auto all = SkillManager::instance()->getAllSkills();
	auto left = all[leftIndex];
	int leftSkillId = left.getId();

	bool isUsed = false;
	auto sel = SkillManager::instance()->getSelSkills();

	int leftCloneIndex;
	for (int i = 0; i< 4;i++)
	{
		auto cell = sel[i];
		int rightSkillId = cell.getId();
		if (rightSkillId == leftSkillId)
		{
			isUsed = true;
			leftCloneIndex = i;
		}
	}
	
	if (isUsed)
	{
		bool isSwapSuccess = SkillManager::instance()->swapSelSkill(leftCloneIndex, rightIndex);
		if (isSwapSuccess)
			loadMyIcon();
		return;
	}

	bool isChangeSuccess = SkillManager::instance()->changeSkill(rightIndex, leftSkillId);
	if (isChangeSuccess)
		loadMyIcon();

}

void SkillView::moveCursor()
{
	auto all = SkillManager::instance()->getAllSkills();

	int index = 0;

	for (auto &cell:all)
	{
		auto one = (MyImageView*)_scrolView->getChildByTag(index);
		bool isSelected = one->isSelected();
		one->setCursor(isSelected);

		index++;
	}
	
}

void SkillView::hideAllCursor()
{
	auto all = SkillManager::instance()->getAllSkills();
	int index = 0;

	for (auto &cell : all)
	{
		auto one = (MyImageView*)_scrolView->getChildByTag(index);
		one->setCursor(false);
		index++;
	}

}

void SkillView::setCurrentLevelSkillText()
{
	auto all = SkillManager::instance()->getAllSkills();
	std::string name = all[_leftIndex].getName();
	int level  = all[_leftIndex].getLevel();
	std::string desc = all[_leftIndex].getDescript();
	Value levelStr(level);
	_currentSkillNameText->setString(name);
	_currentSkillLevelText->setString( levelStr.asString() );
	_currentSkillDescText->setString(desc);

}

void SkillView::setNextLevelSkillText()
{
	std::string name("");
	int level = 0;
	std::string desc("");
	Value levelStr(level);

	auto all = SkillManager::instance()->getAllSkills();
	//int upgradeId = all[_leftIndex].getUpgradeId();

	auto next = all[_leftIndex].getNextSkill();
	if (next!=nullptr)
	{
		name = next->getName();
		level = next->getLevel();
		levelStr = level;
		desc = next->getDescript();
	}
	_nextSkillNameText->setString(name);
	_nextSkillLevelText->setString(levelStr.asString());
	_nextSkillDescText->setString(desc);



}

void SkillView::onUpgradeFromServer()
{
	loadScrollView();
	loadMyIcon();
	setCurrentLevelSkillText();
	setNextLevelSkillText();
	_arrowImage->setVisible(true);

}
void SkillView::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (movementType == MovementEventType::COMPLETE && movementID != "stand") {
        armatureIndex++;
        if (armatureIndex >= animationCount) {
            armatureIndex = animationCount = 0;
            armature->getAnimation()->play("stand");
        }

    }
}

void SkillView::onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	auto result = YNBaseUtil::splitString(evt, ",");

	int i = 0;
	for (auto cell:result)
	{
		if (strncmp(result[i].c_str(), "frontEffect", strlen("frontEffect")) == 0) {
			size_t tagLen = strlen("frontEffect");
			size_t sLen = result[i].length();
			int effTag = atoi(result[i].substr(tagLen, sLen - tagLen).c_str()) - 1;
            auto one = (MyImageView*)_scrolView->getChildByTag(_leftIndex);
            auto effStr = one->frontEff[armatureIndex][effTag];
            if (effStr != "") {
                std::string resPath = ARM_DIR + effStr + ".ExportJson";
                ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
                
                auto eff1 = Effect::create();
                eff1->initWithArmatureAR(effStr, 1.1 * one->frontScale[armatureIndex][effTag]);
                _frontLayer->addChild(eff1);
            }
//			if (currSkill != nullptr) {
//				if ((strcmp(currSkill->getFrontEffectStr()[effTag].c_str(), "") != 0 && (strcmp(currSkill->getFrontEffectStr()[effTag].c_str(), "null") != 0))) {
//					//初始化和资源载入
//					std::string resPath = ARM_DIR + currSkill->getFrontEffectStr()[effTag] + ".ExportJson";
//					ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
//
//					auto eff1 = Effect::create();
//					eff1->initWithArmature(currSkill->getFrontEffectStr()[effTag], currSkill->getFrontScale()[effTag]);
//					eff1->setFollowY(currSkill->getEffectFollowY());
//					_frontLayer->addChild(eff1);
//				}
//			}
		}
		//if (strncmp(result[i].c_str(), "screenFrontEffect", strlen("screenFrontEffect")) == 0) {
		//	size_t tagLen = strlen("screenFrontEffect");
		//	size_t sLen = result[i].length();
		//	int effTag = atoi(result[i].substr(tagLen, sLen - tagLen).c_str()) - 1;
		//	if (currSkill != nullptr) {
		//		if ((strcmp(currSkill->getFrontEffectStr()[effTag].c_str(), "") != 0 && (strcmp(currSkill->getFrontEffectStr()[effTag].c_str(), "null") != 0))) {
		//			//初始化和资源载入
		//			auto hurtEffect = Effect::create();
		//			hurtEffect->initWithRes(currSkill->getFrontEffectStr()[effTag], currSkill->getFrontScale()[effTag]);

		//			auto arm = hurtEffect->getArmature();
		//			arm->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(FightActor::effAnimEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

		//			auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
		//			scene->getscrFrtLayer()->addChild(hurtEffect);
		//		}
		//	}
		//}
		//if (strncmp(result[i].c_str(), "backEffect", strlen("backEffect")) == 0) {
		//	size_t tagLen = strlen("backEffect");
		//	size_t sLen = result[i].length();
		//	int effTag = atoi(result[i].substr(tagLen, sLen - tagLen).c_str()) - 1;
		//	if (currSkill != nullptr) {
		//		if ((strcmp(currSkill->getBackEffectStr()[effTag].c_str(), "") != 0 && (strcmp(currSkill->getBackEffectStr()[effTag].c_str(), "null") != 0))) {
		//			//初始化和资源载入
		//			std::string resPath = ARM_DIR + currSkill->getBackEffectStr()[effTag] + ".ExportJson";
		//			ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);

		//			auto eff1 = Effect::create();
		//			eff1->initWithArmature(currSkill->getBackEffectStr()[effTag], currSkill->getBackScale()[effTag]);
		//			eff1->setFollowY(currSkill->getEffectFollowY());
		//			backEffectLayer->addChild(eff1);

		//		}
		//	}
		//}
		i++;
	}
	
}