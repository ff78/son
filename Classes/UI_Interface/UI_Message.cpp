#include "UI_Message.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "UI/Loading_Scene.h"
#include "Common/GameMacro.h"
#include "Common/VisibleRect.h"
#include "Common/GameResource.h"
#include <string>
using namespace Game_Data;
using namespace std;
using namespace UI;

UI_Message* UI_Message::instance=0;
UI_Message::UI_Message()
{
	isFirst=false;
}
UI_Message::~UI_Message()
{

}
UI_Message* UI_Message::sharedInstance()
{
	if(instance==0)
	{
		instance=new UI_Message();
		if(instance&&instance->init())
		{
			return instance;
		}
		else
		{
			delete instance;
			instance=0;
		}
	}
	return instance;
}
bool UI_Message::init()
{
	bool ret=false;
	do 
	{
		CC_BREAK_IF(!Layer::init());
		Point pt=VisibleRect::center();

		cocos2d::Sprite* pCurWave = cocos2d::Sprite::create(CURRENT_ENEMY_WAVE_PIC);
		pCurWave->setPosition(Vec2(pt.x,pt.y + 300 ));
		this->addChild(pCurWave);

		m_pCurWavePercentage = LabelAtlas::create("0123456789/", CURRENT_ENEMY_WAVE_NUM, 31, 32, '0');
		m_pCurWavePercentage->setPosition(Vec2(pt.x + 20, pt.y + 280 ));
		this->addChild(m_pCurWavePercentage);

		ret=true;
	} while (0);
	return ret;
}
void UI_Message::showMessage(int textId,int firstNumber,int secondNumber)
{
	//��ӵ�ǰ�㵽����
	Scene* scene=Director::getInstance()->getRunningScene();
	if(!scene)
	{
		return;
	}

	UI_Message* child=dynamic_cast<UI_Message*>(scene->getChildByTag(TAG_MESSAGELAYER));
	if(!child)
	{
		child = this;
		scene->addChild(child, TAG_MESSAGELAYER,TAG_MESSAGELAYER);
	}

	char temp[64]={0};
	//ע�⣺������ַ���ƴ���е� �� ��ð�ţ� ��ʾ������ ����Դ������һ������ /  ("0123456789/" �����ASCII������)
	//9�����ASCII��Ӧ���ַ��ǡ�:������������Ҫ����ַ�����ʱ��ֻ��Ҫ���ַ����е� / �滻�ɡ�:�������ˡ�����1/24�滻��1:24��
	SPRINTF(temp,"%d:%d",firstNumber,secondNumber);
	m_pCurWavePercentage->setString(temp);

}
void UI_Message::removeMessage()
{
	Scene* scene=Director::getInstance()->getRunningScene();
	if(!scene)
	{
		return;
	}

	UI_Message* child=dynamic_cast<UI_Message*>(scene->getChildByTag(TAG_MESSAGELAYER));
	if(child)
	{
		scene->removeChildByTag(TAG_MESSAGELAYER);
	}
}