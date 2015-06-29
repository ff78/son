#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "../Game_Interface/game_content_interface.h"

//model
namespace Game_Model
{
	class StarData
	{
	public:

	private:
		static StarData* getInstance();
	};

};
typedef Game_Model::StarData STAR_MODEL;


//view

namespace Game_View
{
	class StarLayer : public cocos2d::Layer
	{
	public:
		void									onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		virtual void							onEnter() override;
		virtual void							onExit()  override;
		virtual bool							init()    override;
		CREATE_FUNC(StarLayer);
	private:
		cocos2d::ui::Widget*					_rootWidget;
		cocos2d::ui::Button*					_closeButton;

	};

};
typedef Game_View::StarLayer STAR_VIEW;

namespace Game_Net
{
	static bool send_on_load(Game_Logic::Game_Interface& gm_interface);

}