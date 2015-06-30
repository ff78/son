#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "../Game_Interface/game_content_interface.h"

//model
#define EVENT_CHANGE_DATA "event_change_data"
namespace Game_Model
{
	struct PetConfig
	{
		int id;
		int star;
		int quality;
		int consume;
		std::string name;
		int attrId;
        std::string armName;
        std::string iconName;
	};

	struct PetAttr
	{
		int id;
		int health;
		int magic;
		int attack;
		int defense;
		int hit;
		int dodge;
		int crit;
		int tenacity;
		
	};

	struct Pet
	{
		uint64 guid;
		int id;

		bool isEquiped;
	};

	class PetData
	{
	public:
		void eventChangeData();

		inline static PetData*	getInstance(){ static PetData instance_; return &instance_; }
		inline int getCurrentPetId(){return _currentPetId;}
		inline void setCurrentPetId(int id){_currentPetId=id;}
		inline int getSelectedPetId(){ return _selectedPetId; }
		inline void setSelectedPetId(int id){ _selectedPetId=id; }
		CC_SYNTHESIZE(std::vector<Pet>*, _pets, Pets);
		std::map<int, PetConfig*> _petConfigMap;
		std::map<int, PetAttr*> _petAttrMap;

		void load();


	private:
		PetData()
		{
			_pets=new std::vector<Pet>;
			cocos2d::Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_CHANGE_DATA, CC_CALLBACK_0(Game_Model::PetData::eventChangeData,this) );
		}
		~PetData()
		{
			_pets->clear();
		}
		int		_currentPetId;
		int		_selectedPetId;

	};

};
typedef Game_Model::PetData PET_MODEL;

//view
#define EVENT_REFRESH "event_refresh_Pet"
#define QUALITY_NUM 9
#define STAR_NUM 5
namespace Game_View
{
	class PetLayer : public cocos2d::Layer
	{
	public:
		void									refresh();
		void									loadScrollView();
		void									onClickCellCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void									onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void									onUpgradeCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void									onGoCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		virtual void							onEnter() override;
		virtual void							onExit()  override;
		virtual bool							init()    override;
		CREATE_FUNC(PetLayer);
		PetLayer() :_petsScrollView(nullptr), _rootWidget(nullptr), _closeButton(nullptr), _upgradeButton(nullptr), _goButton(nullptr){}
		~PetLayer()
		{
			_petsScrollView = nullptr; 
			_rootWidget = nullptr; 
			_closeButton = nullptr; 
			_upgradeButton = nullptr; 
			_goButton = nullptr;
		}
	private:
		cocos2d::ui::ScrollView*				_petsScrollView;
		cocos2d::ui::Widget*					_rootWidget;
		cocos2d::ui::Button*					_closeButton;
		cocos2d::ui::Button*					_upgradeButton;
		cocos2d::ui::Button*					_goButton;

		cocos2d::ui::Text*						_petName;
		cocos2d::ui::Text*						_petConsume;
		cocos2d::ui::Text*						_petPower;
		cocos2d::ui::Text*						_mePower;
        cocos2d::ui::Text*						_quality;
		cocos2d::ui::ImageView*					_stars[STAR_NUM];
        cocos2d::ui::ImageView*                 fightFlag;
        std::string qualityStr[QUALITY_NUM] ={
          "黑铁","青铜","白银","黄金","暗金","红玉","灵器","宝器","仙器"
        };

        cocos2d::LayerColor* waitLayer;
        cocostudio::Armature* model;
	};

};
typedef Game_View::PetLayer PET_VIEW;


#define EVENT_PET_SEND_LOAD "event_pet_send_load"
#define EVENT_PET_SEND_UPGRADE "event_pet_send_upgrade"
#define EVENT_PET_SEND_CHANGE "event_pet_send_change"
namespace Game_Net
{
	class Pet_Msg
	{
	public:
		static bool on_load(Game_Logic::Game_Interface& gm_interface);

		static bool send_upgrade(Game_Logic::Game_Interface& gm_interface);
		static bool on_upgrade(Game_Logic::Game_Interface& gm_interface);

		static bool send_change_state(Game_Logic::Game_Interface& gm_interface);
		static bool on_change_state(Game_Logic::Game_Interface& gm_interface);
	private:
		Pet_Msg(){};
		~Pet_Msg(){};

	};

};
typedef Game_Net::Pet_Msg PET_NET;