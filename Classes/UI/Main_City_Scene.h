
#ifndef MAIN_CITY_SCENE_H
#define MAIN_CITY_SCENE_H
#pragma warning(disable:4251) 
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
//#include "cocos-ext.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIWidget.h"
#include "ui/UIScrollView.h"
#include "ui/UIDeprecated.h"
#include "ui/UIHelper.h"
#include "ui/UIPageView.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
//USING_NS_CC;


namespace UI
{
    struct RoleAnim
    {
        int job;
        std::string animStr;
        std::vector<std::string> actions;
        std::vector<std::vector<std::string>> frontEff;
        std::vector<std::vector<float>> frontScale;
        std::vector<std::vector<std::string>> backEff;
        std::vector<std::vector<float>> backScale;
    };
  class Main_City_Background_Layer : public Layer
  {
  public:
	virtual void update(float delta);
    virtual bool init();
    void init_bg();
	void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
    CREATE_FUNC (Main_City_Background_Layer);
	Main_City_Background_Layer():_armatureRepeat(nullptr),_armatureOnce(nullptr){};
	~Main_City_Background_Layer(){_armatureRepeat = nullptr;_armatureOnce = nullptr;};
  private:
	cocostudio::Armature* _armatureRepeat;
	cocostudio::Armature* _armatureOnce;
  };
  
  class Main_City_Actor_Layer : public Layer
  {
  public:
	  void update(float dt) override;
     virtual bool init();
	 Main_City_Actor_Layer();
      ~Main_City_Actor_Layer();
      void onExit();
      CREATE_FUNC (Main_City_Actor_Layer);
	  static Main_City_Actor_Layer * get_instance();
      cocos2d::ui::Widget* createNode(int actor_id);
	  void loadServerList();
	  void loadRoleList();
	  void roleSelectCallback(Ref* pSender,Widget::TouchEventType type);
	  void loadSelectRoleSexList();
	  void loadSelectJob();
	  void createRoleBtnBackCallback(Ref* pSender,Widget::TouchEventType type);
	  void goBackCallBack(Ref* pSender,Widget::TouchEventType type);
	  void randomRoleName(Ref* pSender,Widget::TouchEventType type);

	  void clickMaleEventCallback(Ref* pSender,Widget::TouchEventType type);
	  void clickFemaleEventCallback(Ref* pSender,Widget::TouchEventType type);
	  void refreshCurrentSelect();
	  const char* getRigisterName();
      int getRigisterSex(){return m_sex;}
	  int getJob(){ return m_job; };
	  static Text* curSv;
	  void clickAServer(Ref* pSender, Widget::TouchEventType type);
	  void clickJob1(Ref* pSender, Widget::TouchEventType type);
	  void clickJob2(Ref* pSender, Widget::TouchEventType type);
	  void clickJob3(Ref* pSender, Widget::TouchEventType type);
	  void clickJob4(Ref* pSender, Widget::TouchEventType type);
	  void clickJob5(Ref* pSender, Widget::TouchEventType type);
      void animationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);
      void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	  
	  void setUILayer(cocos2d::Layer* pUILayer){ m_pUILayer = pUILayer; }
	  cocos2d::Layer* getUILayer(){ return m_pUILayer; }
	  cocos2d::ui::Widget* getUILayerWidget(){ return m_pWidget; }
	  void setUILayerWidget(cocos2d::ui::Widget* pUIWidget){ m_pWidget = pUIWidget; }
	  
	  void hideEffectSprite();
      
      void loadAnimJson();
      void playSkill(std::vector<std::string>* actionNames);
  private:
	  static Main_City_Actor_Layer*  instance_;
	  cocos2d::Layer* m_pUILayer;
	  cocos2d::ui::Widget* m_pWidget;
	  cocos2d::ui::Text* nameTxt;
	  std::string name;
      int m_sex;
	  int m_job;
      CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, job1, Job1);
      CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, job2, Job2);
      CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, job3, Job3);
      CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, job4, Job4);
      CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, job5, Job5);
	  

	  cocos2d::Sprite*			m_pSelectState;
	  cocos2d::Sprite*			_effectSprite;
	  bool						_isChanging = false;
	  bool						_isReachMax = false;
	  cocos2d::Sequence*		_effectSequence;
	  cocos2d::Vec2				_rolePosDefault;
	  cocostudio::ActionObject* _outAction;
	  cocos2d::ui::ImageView*	_roleImg;

	  cocostudio::Armature*		_nvqiangArmature;
	  std::vector<std::string>	_nvqiangActionNames;
	  cocostudio::Armature*		_wudoujiaArmature;
	  std::vector<std::string>	_wudoujiaActionNames;
      
      cocos2d::Layer* roleLayer;
      cocos2d::Layer* frontLayer;
      cocos2d::Layer* backLayer;
      cocos2d::Sprite* shadow;
      
      cocostudio::Armature* armature;
      std::map<int, struct RoleAnim*> jobAnimMap;

      int armatureIndex;
      int animationCount;
  };



  class Main_City_Scene: public Scene
  {
  public:
    virtual bool init();
//      void onEnter();
    virtual void update( float delta);
    static Main_City_Scene* scene();
      
	void current_server( Ref* pSender,Widget::TouchEventType type );
	void clickJob1(Ref* pSender, Widget::TouchEventType type);
	void clickJob2(Ref* pSender, Widget::TouchEventType type);
	void clickJob3(Ref* pSender, Widget::TouchEventType type);
	void clickJob4(Ref* pSender, Widget::TouchEventType type);
	void clickJob5(Ref* pSender, Widget::TouchEventType type);
	static std::string getRandomName(int sex);
	Main_City_Scene():_bgLayer(nullptr){};
	~Main_City_Scene(){ _bgLayer = nullptr; };
  private:
	  Main_City_Background_Layer* _bgLayer;
  };

};

#endif /* MAIN_CITY_SCENE_H */
