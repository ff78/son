#ifndef CITY_SCENE_H
#define CITY_SCENE_H
/*====================================   dely   ====================================*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"
//#include "cocostudio/CocoStudio.h"

#include "../ClientLogic/SneakyJoy/SneakyJoyStick.h"
#include "../ClientLogic/GameScene/CityLayer.h"
#include "Loading_Scene.h"
/*====================================   dely   ====================================*/

#include "UI/Loading_Scene.h"

#include "json/json_header.h"

#include "Common/Utils.h"
#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"
#include "Game_Interface/game_event_response.h"
USING_NS_CC;

class UI_MainMenu_Layer;
class Player;
class Game_Event_Response;

namespace UI
{
	class Message_Layer;
	class City_Scene : public Loading_Scene
	{
	public:
        ~City_Scene();
		bool init();
		void onExit();
		CREATE_FUNC(City_Scene);

		int static sceneId;

		virtual void update(float delta);

	private:

		void loadAudio();

		void loadData();
		void loadFrontLayer();
		void loadMidLayer();
		void loadBackLayer();
		void loadCamera();
		void loadActorLayer();

		void loadHUD();
		//void load_Message_layer();
		virtual void onLoadFinish();

		Message_Layer*		_msglayer;
		UI_MainMenu_Layer*	_hudLayer;
		CityLayer*			_sceneLayer;

	};

};

#endif /* CITY_SCENE_H */
