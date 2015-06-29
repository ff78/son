#ifndef __UI_ICON_INFO_LAYER__
#define __UI_ICON_INFO_LAYER__

#include "cocos2d.h"
//#include "cocos-ext.h"
#include "ui/UIImageView.h"
#include "Item_System/Item_Config_Data.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIWidget.h"
#include "ui/UIScrollView.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#include "cocostudio/CocoStudio.h"
//USING_NS_CC;
//USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;
using namespace Game_Data;

#define  TOTAL_ATTR_NUM		2
#define  PARAM_NUM			3
#define	 GEM_INLAY_NUM		5

#define  TIPS_STYLE_EQUIP_EQUIPMENT			1				//装备佩戴按钮
#define  TIPS_STYLE_TAKE_OFF_EQUIPMENT      2				//卸下按钮
#define	 TIPS_STYLE_EQIP_BOOK		        4				//书籍佩戴按钮
#define  TIPS_STYLE_TAKE_OFF_BOOK	        8				//书籍卸下按钮
#define	 TIPS_STYLE_SET_ON_GEM		        16			    //镶嵌宝石
#define  TIPS_STYLE_SET_OFF_GEM	            32			    //卸下宝石
#define  TIPS_STYLE_COMBINE_GEM			    64			    //合成
#define  TIPS_STYLE_OK				        128				//确定按钮
#define  TIPS_STYLE_SELL			        256				//出售按钮
#define  TIPS_STYLE_FINDWAY			        512				//寻路按钮
#define  TIPS_STYLE_USE		                1024		    //使用按钮
#define  TIPS_STYLE_USE_ALL		            2048	        //使用全部按钮
#define  TIPS_STYLE_LEVEL			        4096		    //道具等级
#define  TIPS_STYLE_EQUIPMENT_ATTR		    8192		    //装备属性
#define  TIPS_STYLE_BOOK_ATTR		        16384		    //书籍属性
#define  TIPS_STYLE_GEM_ATTR		        32768		    //宝石属性

#define  FRAME_STYLE_INLAY					65536			//宝石信息显示窗口

#define THISLAYERZORDERE			50
#define THISLAYERTAG				88

class UI_Icon_Info_Layer : public cocos2d::Layer
{
private:
	UI_Icon_Info_Layer(void);
	~UI_Icon_Info_Layer(void);

public:
	virtual bool init();
	CREATE_FUNC(UI_Icon_Info_Layer);
	virtual void setVisible(bool visible);

	void showButton(int item_base_id, int icon, int name, int level=1, int current_quality=0, int style=0);
    void set_param(std::vector<uint64>& para);
    void set_gem_id(int* gem_id);

private:
	void initChangePart();
	void resetUI();

	void btnCloseCallback(Ref* pSender,Widget::TouchEventType type);		//关闭
	void btnEquipCallback(Ref* pSender,Widget::TouchEventType type);		//装备
	void btnTakeoffCallback(Ref* pSender,Widget::TouchEventType type);		//卸下
	void btnSellCallback(Ref* pSender,Widget::TouchEventType type);		//出售
	void btnAStarCallback(Ref* pSender,Widget::TouchEventType type);		//寻路
	void btnEquipBookCallback(Ref* pSender,Widget::TouchEventType type);	//装备书籍
	void btnTakeoffBookCallback(Ref* pSender,Widget::TouchEventType type); //卸载书籍
    void btnUseCallback(Ref* pSender,Widget::TouchEventType type);		    //使用

	//宝石按钮区
	void btnGemSetOnCallback( Ref* pSender ,Widget::TouchEventType type);
	void btnGenTakeOffCallback( Ref* pSender ,Widget::TouchEventType type);
	void btnGemCombineCallback( Ref* pSender ,Widget::TouchEventType type);

	void showIconInfo(int item_base_id, int icon, int name, int level=1, int current_quality=0);
	
	//显示界面一：《普通信息区》
	void showLayoutFirst();
	//显示界面二：《镶嵌界面 (多镶嵌信息)》
	void showLayoutSecond();

public: //控件区
	cocos2d::ui::ImageView*		m_pImgRootBack;		//大背景

	cocos2d::ui::ImageView*		m_img_first_line;	//第一条线
	cocos2d::ui::Text*			m_pLabIconLevel;	//图标等级
	cocos2d::ui::Text*			m_pLabIconName;		//图标名称
	cocos2d::ui::Button*			m_pBtnClose;		//关闭按钮
	cocos2d::ui::Text*			m_pTeaForDesc;		//图标描述

	cocos2d::ui::ImageView*		m_img_second_line;  //第二条线
	cocos2d::ui::Text*			m_pLabGemAttr[GEM_INLAY_NUM];	//镶嵌宝石属性

	cocos2d::ui::ImageView*		m_img_third_line;  //第三条线
	cocos2d::ui::Text*			m_pLabAttrArr[TOTAL_ATTR_NUM]; //属性栏

	cocos2d::ui::Button*			m_pBtnLeft;			//左侧按钮
	cocos2d::ui::Text*			m_pBtnLeftFont;		//左侧按钮字体
	cocos2d::ui::Button*			m_pBtnRight;		//右侧按钮
	cocos2d::ui::Text*			m_pBtnRightFont;	//右侧按钮字体
  cocos2d::ui::Widget* pWidget;
private:
    uint64              m_param[PARAM_NUM];
    int                 m_gem_id[SET_GEM_COUNT];

private:
	enum guide_index
	{
		BAG_GUIDE_MID_1	= 21,
		BAG_GUIDE_MID_2	= 22,
		BAG_GUIDE_MID_3 = 23,

		XF_GUIDE_MID_1 = 81,
		XF_GUIDE_MID_2 = 82,
		XF_GUIDE_MID_3 = 83,
	};
};

#endif //__UI_ICON_INFO_LAYER__

/*
class UI_Icon_Info_Layer;

//Icon 信息显示框
UI_Icon_Info_Layer*			m_pLayerIconInfo;

#include "UI_Icon_Info_Layer.h"
m_pLayerIconInfo(NULL);

//创建物品信息显示框
m_pLayerIconInfo = UI_Icon_Info_Layer::create();
this->addChild(m_pLayerIconInfo,THISLAYERZORDERE,THISLAYERTAG);
m_pLayerIconInfo->setVisible(false);


m_pLayerIconInfo->showButton(item->config->base_id,item->config->icon,item->config->name,item->level,item->current_quality,
TIPS_STYLE_SELL | TIPS_STYLE_EQUIP | TIPS_STYLE_LEVEL | TIPS_STYLE_ATTR);

*/