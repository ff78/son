#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"
#include "Common/GameDefine.h"
#include "Network_Common/global_macros.h"

#include "Relation_System/Relation_Common.h"
#include "Relation_System/Relation_Mgr.h"

#include "UI_Interface/MyEditBox.h"
#include "UI_Friend_Layer.h"
#include "UI_Add_Friend_Layer.h"

using namespace ui;
using namespace cocos2d;
using namespace cocostudio;

UI_Add_Friend_Layer::UI_Add_Friend_Layer()
{
	
}


UI_Add_Friend_Layer::~UI_Add_Friend_Layer()
{

}


bool UI_Add_Friend_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	ui::Widget* pLayer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Add_Friend/Add_Friend.ExportJson");
	addChild(pLayer);
	// 关闭按钮	
	ui::Button * pCloseBtn		= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Close"));
	pCloseBtn->setTouchEnabled(true);
	//pCloseBtn->addTouchEventListener(CC_CALLBACK_2(UI_Add_Friend_Layer::OnBtnCloseCallBack, this));
	pCloseBtn->addTouchEventListener( this, toucheventselector(UI_Add_Friend_Layer::OnBtnCloseCallBack) );

	// 提交文本
	ui::Text * pSubmitText		= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Btn_Submit"));
	pSubmitText->setTouchEnabled(true);
	//pSubmitText->addTouchEventListener(CC_CALLBACK_2(UI_Add_Friend_Layer::OnBtnSubmitCallBack, this));
	pSubmitText->addTouchEventListener( this, toucheventselector(UI_Add_Friend_Layer::OnBtnSubmitCallBack) );


	// 退出文本
	ui::Text * pQuitText		= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Btn_Quit"));
	pQuitText->setTouchEnabled(true);
	//pQuitText->addTouchEventListener(CC_CALLBACK_2(UI_Add_Friend_Layer::OnBtnCloseCallBack, this));
	pQuitText->addTouchEventListener( this, toucheventselector(UI_Add_Friend_Layer::OnBtnCloseCallBack) );

	// 输入好友名字文本框
	CommonEditBox * pEditBox = CommonEditBox::create();
	pEditBox->setTag(998);
	addChild(pEditBox);
	pEditBox->SetPositionAndMaxLength(0, 320, 20);
	return true;
}


void UI_Add_Friend_Layer::onExit()
{
	Layer::onExit();
}


void UI_Add_Friend_Layer::onEnter()
{
	Layer::onEnter();


}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 页面刷新相关逻辑

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 按钮点击方法回调	
void UI_Add_Friend_Layer::OnBtnCloseCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 点击关闭件按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 关闭当前界面
	this->removeFromParent();
}

void UI_Add_Friend_Layer::OnBtnSubmitCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 点击提交件按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 1. 判断输入框是否存在
	CommonEditBox * pEditBox = dynamic_cast<CommonEditBox *>(this->getChildByTag(998));
	if (pEditBox == NULL)
		return;

	// 2. 获取输入法的内容
	std::string strName = pEditBox->getContent();

	int nTemp = strcmp(strName.c_str(), "Input From This");
	if (nTemp <= 0)
		return;

	// 3. 通知逻辑层请求添加目标
	Relation_Manager::instance()->UIRequestAddFriend(strName);

	// 4. 关闭当前界面
	this->removeFromParent();
}
