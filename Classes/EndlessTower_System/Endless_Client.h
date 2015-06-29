#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "../Game_Interface/game_content_interface.h"

//model
namespace Game_Model
{
	class EndlessData
	{
	public:

	private:
		static EndlessData* getInstance();
	};

};
typedef Game_Model::EndlessData ENDLESSDATA_MODEL;


//view

namespace Game_View
{
	class EndlessLayer : public cocos2d::Layer
	{
	public:
		void									onGoCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
        void									onPrayCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void									onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		virtual void							onEnter() override;
		virtual void							onExit()  override;
		virtual bool							init()    override;
		CREATE_FUNC(EndlessLayer);
	private:
		cocos2d::ui::Widget*					_rootWidget;
		cocos2d::ui::Button*					_closeButton;
		cocos2d::ui::Button*					_goButton;
        cocos2d::ui::Button*                    prayButton;
	};

};
typedef Game_View::EndlessLayer ENDLESS_VIEW;

namespace Game_Net
{
	static bool send_on_load(Game_Logic::Game_Interface& gm_interface);

}