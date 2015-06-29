#include "Dialogue_Client.h"

DIALOGUE_MODEL* DIALOGUE_MODEL::getInstance()
{
	static DIALOGUE_MODEL _instance;
	return &_instance;
}

bool DIALOGUE_MODEL::initWithId(int id)
{

	cocos2d::Value nId(id);
	std::string path("GameData/little/dialog" + nId.asString()+ ".json");
	std::string contentStr = cocos2d::FileUtils::getInstance()->getStringFromFile(path);

	rapidjson::Document document;
	document.Parse <0>( contentStr.c_str() );
	if ( document.HasParseError()||!document.IsArray() )return false;

	loadData(document);

	return true;

}

using namespace cocos2d;

void DIALOGUE_MODEL::loadData(const rapidjson::Document& domt)
{
	int size = domt.Size();
	for (unsigned int i = 0; i < size;i++)
	{
		Line cell;
		const rapidjson::Value &v = domt[i];
		if (v.HasMember("dialogueId") && v.HasMember("dialogName")&& v.HasMember("direct") && v.HasMember("segId") && v.HasMember("content") )
		{
			cell.dialogueId = v["dialogueId"].GetInt();
			cell.roleName = v["dialogName"].GetInt();
			cell.content = v["content"].GetString();
			cell.isFaceLeft = (v["direct"].GetInt()==1);

			cell.segmentId = v["segId"].GetInt();
		}
		_lines.push_back(cell);
//		CCLOGWARN("dialogueId_%d,segId_%d,content_%s",cell.dialogueId,cell.segmentId,cell.content);
	}
	
}

Game_Model::Line& Game_Model::DialogueData::getLineByLevel(int level)
{
	return _lines[level];
}

bool Game_View::DialogueLayer::init()
{
	if( !Layer::init() )return false;

	_rootWidget = dynamic_cast<cocos2d::ui::Widget*>( cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Dialogue/Dialogue.ExportJson") );
	addChild(_rootWidget);

    return true;
}

// void Game_View::DialogueLayer::onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
// {
// 	if(type!=cocos2d::ui::Widget::TouchEventType::ENDED)return;
// 
// 	auto spawnAction = cocos2d::Spawn::createWithTwoActions(cocos2d::DelayTime::create(0.1), cocos2d::CallFunc::create(CC_CALLBACK_0(Game_View::DialogueLayer::removeFromParent, this)));
// 	this->runAction(spawnAction);
// 
// }

void Game_View::DialogueLayer::addListner(cocos2d::ui::Widget::ccWidgetTouchCallback callback)
{
	this->_touchCallback = callback;
	_rootWidget->addTouchEventListener(this->_touchCallback);

}

void Game_View::DialogueLayer::setContentById(int id)
{
	auto contnt = DIALOGUE_MODEL::getInstance()->getLineByLevel(id).content;
	auto face = DIALOGUE_MODEL::getInstance()->getLineByLevel(id).isFaceLeft;
	auto txt = dynamic_cast<cocos2d::ui::Text*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget,"Txt_Content") );
	txt->setString(contnt);
	if (face)
	{
		auto left = dynamic_cast<cocos2d::ui::ImageView*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Img_Head_0"));
		left->loadTexture("img/Dialogue_Role_Img/Role_1.png");
		auto right = dynamic_cast<cocos2d::ui::ImageView*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Img_Head_1"));
		right->setVisible(false);
	}
	else
	{
		auto left = dynamic_cast<cocos2d::ui::ImageView*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Img_Head_0"));
		left->setVisible(false);
		auto right = dynamic_cast<cocos2d::ui::ImageView*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Img_Head_1"));
		right->loadTexture("img/Dialogue_Role_Img/Role_2.png");

	}

}
