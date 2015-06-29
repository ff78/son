#ifndef LOGIN_SCENE_H__
#define LOGIN_SCENE_H__
#include "cocos2d.h"
#include <list>
#include "UI_Interface/UI_LoginLayer.h"
#include <pthread.h>
#include "ui/CocosGUI.h"
#include "Common/Utils.h"

#include "Loading_Scene.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class Login_Scene:public UI::Loading_Scene
{
public:
	enum TAG_LAYER_LOGIN
	{
		UI_LOGO_LAYER,
		UI_LOGIN_LAYER,
	};
	enum EVENTTYPE
	{
		EVENT_TYPE_LOGIN_SUCCEED,
		EVENT_TYPE_NO_UPDATE,
		EVENT_TYPE_HAVE_UPDATE,
		EVENT_TYPE_OBTAIN_SERVER,
		EVENT_TYPE_GOT_SERVER_FAILED,
	};
	void sendMessage(EVENTTYPE eventType);

	virtual bool init();

	CREATE_FUNC(Login_Scene);

	static Login_Scene* sharedInstance();
	virtual void update(float dt);

private:
	void removeLogo(float dt);
	void showLogin(float dt);
	list<int> messageQueue;
	pthread_mutex_t messageQueueMutex;
	static Login_Scene* instance_;
	Login_Scene();
	~Login_Scene();
#if 1
	void onLoadFinish();
	void loadOne();
	void loadTwo();
	void loadThree();
	void loadFour();
	void loadFive();
	void loadSix();
	void loadSeven();
	void loadEight();
	void loadNine();
	void loadTen();
	void LoadEleven();
#endif
};
#endif //LOGIN_SCENE_H__

