#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "../Game_Interface/game_content_interface.h"
#include "God_Weapon_Config_Data.h"
#include "cocostudio/CocoStudio.h"
#include "../DataModule/ClsSkill.h"
#include "../DataModule/BlackColossus.h"
//model
namespace Game_Model
{
	class GodData
	{
		CC_SYNTHESIZE(int, _currentGodId, CurrentGodId);
	public:
		static GodData*	getInstance(){ static GodData instance_; return &instance_; }
		void load();
		std::map<int, ClsSkill>& getSkills();
        BlackColossus* blackColossus;

	private:
        GodData(){    blackColossus = new BlackColossus();}
		~GodData(){}
	};

};
typedef Game_Model::GodData GOD_MODEL;

//view
#define EVENT_ON_UPDATE_SUCCESS "event_on_update_success"
namespace Game_View
{
	class GodLayer : public cocos2d::Layer
	{
	public:
		void									onClickSkillCell(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void									eventOnUpdate();
		void									loadData(int level,int consume);
		void									onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void									onUpgradeCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
        void                                    animationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);
		virtual void							onEnter() override;
		virtual void							onExit()  override;
		virtual bool							init()    override;
		virtual void							update(float dt) override;

		GodLayer() :_rootWidget(nullptr), _closeButton(nullptr), _upgradeButton(nullptr), _levelText(nullptr)
			, _consumeText(nullptr), _level(0), _consume(0), _armatureRepeat(nullptr){}
		~GodLayer(){ _rootWidget = nullptr; _closeButton = nullptr; _upgradeButton = nullptr; 
					 _levelText = nullptr; _consumeText = nullptr; _armatureRepeat = nullptr;}
		CREATE_FUNC(GodLayer);
	private:
		cocos2d::ui::Widget*					_rootWidget;
		cocos2d::ui::Button*					_closeButton;
		cocos2d::ui::Button*					_upgradeButton;

		cocos2d::ui::Text*						_levelText;
		cocos2d::ui::Text*						_consumeText;
		int										_level;
		int										_consume;
		//std::string								_path;

		cocostudio::Armature*					_armatureRepeat;
        cocos2d::ui::ScrollView*                _skillScroll;
		cocos2d::ui::Button*					_skillButton1;
		cocos2d::ui::Button*					_skillButton2;
		cocos2d::ui::Button*					_skillButton3;
		cocos2d::ui::Button*					_skillButton4;
		cocos2d::ui::Text*						_descText;
        
	};

};
typedef Game_View::GodLayer GOD_VIEW;

#define EVENT_GOD_SEND_UPGRADE "event_god_send_upgrade"
namespace Game_Net
{
	class God_Msg
	{
	public:
		//static bool send_load(Game_Logic::Game_Interface& gm_interface);
		static bool on_load(Game_Logic::Game_Interface& gm_interface);
		static bool send_upgrade(Game_Logic::Game_Interface& gm_interface);
		static bool on_upgrade(Game_Logic::Game_Interface& gm_interface);
	private:
		God_Msg() :_forBeauty(0){};
		~God_Msg(){ _forBeauty = 0; };
		int _forBeauty;
	};

};
typedef Game_Net::God_Msg GOD_NET;