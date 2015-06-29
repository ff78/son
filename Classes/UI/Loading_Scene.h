
#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
#define  LOADING_BACKGROUND_PATH  "ui/Loading/pic_loading_background.png"
#define  LOADING_PATH	"ui/Loading/pic_loading.png"
#define  LOADINGPATTERN_PATH  "img/scene/tips.png"

namespace UI
{
	enum UI_TAG
	{
		TAG_BG = 0x0001000,
		TAG_FG,
		TAG_ACT,
		TAG_UI,
		TAG_OPT,
		TAG_UNS,
		TAG_BTN_UI,
		TAG_MSG,
		TAG_TIMELIMITED_UI,
		TAG_FUBENDIALG,
		TAG_MESSAGELAYER,
		TAG_TIP,
		TAG_PUBLIC_ANNOUCEMENT,
		TAG_NO_TOUCH_LAYER,
	};

	class Loading_Scene : public cocos2d::Scene
	{
	public:
		typedef void (Loading_Scene::*LoadFunc)();
		Loading_Scene();
		~Loading_Scene();

		virtual bool init();

	protected:
		void loadingUpdate(float delta);
		void addLoadFunc(LoadFunc pFunc)
		{
			m_vecLoadFunc.push_back(pFunc);
		}
		virtual void onLoadFinish();

	private:
		void updateLoadingBar();
	protected:
		int m_nStep; 
		std::vector<LoadFunc>	m_vecLoadFunc;
		cocos2d::Sprite*		m_pSprBgk;
		cocos2d::Sprite*		m_pSprLoadingBar;
		cocos2d::Sprite*		m_pSprLoadingBkg;
		cocos2d::Sprite*		loading_pattern_;
		cocos2d::LabelTTF*	comment_label_;
		cocos2d::ui::LoadingBar* m_pLoadingBar;
		cocos2d::LabelTTF*  tipsLab;
		std::string				commet_text_;
		cocos2d::Layer*		m_no_touch_layer_;

		cocos2d::Sprite*		m_pRunningEffect;
		cocos2d::Point		pt;

		cocos2d::Sprite*    _girl;
	};

}

#endif /* __LOADING_SCENE_H__ */
