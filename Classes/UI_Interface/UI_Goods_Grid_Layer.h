#ifndef __UI_GOODS_GRID_LAYER__
#define __UI_GOODS_GRID_LAYER__

#include "cocos2d.h"
//#include "cocos-ext.h"
#include "Game_Interface/common.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIWidget.h"
#include "ui/UIScrollView.h"
#include "ui/UIPageView.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
//USING_NS_CC;
//USING_NS_CC_EXT;

#define ROOT_BACK_WIDTH		472		//背景宽
#define ROOT_BACK_HEIGHT	508		//背景高
#define LAYOUT_WIDTH		460		//每页宽度
#define LAYOUT_HEIGHT		360		//每页高度
#define PAGE_SUM_NUM		6		//总页数
#define EACH_PAGE_ROW_NUM	3		//每页3行
#define EACH_PAGE_COL_NUM	4		//每页4行
#define EACH_PAGE_NUM		12		//每页格子数
#define GRID_NUM		    PAGE_SUM_NUM*EACH_PAGE_NUM		//总格子数

#define STYLE_NOTHING			0	//无需显示任何风格
#define STYLE_GRID_LAB_NUM		2	//显示 物品 数量
#define STYLE_GRID_PIC_QUA		4	//显示"品"字图片
#define STYLE_GRID_PIC_EQU		8	//显示"装"字图片
#define STYLE_TIDY_BUTTON		16	//"整理" 按钮
#define STYLE_EACH_HAS_EFFECT	32  //每个格子均含有背景图
#define STYLE_BOTH_BUTTON		64	//每页下面两个按钮
#define STYLE_PAGE_LIGHT_MIDDLE	128	//设置当前页显示灯在中间
#define STYLE_PAGE_LIGHT_LEFT	256	//设置当前页显示灯在左侧

class UI_Icon_Info_Layer;
class UI_Goods_Grid_Layer : public cocos2d::Layer
{
public:
	UI_Goods_Grid_Layer(void);
	~UI_Goods_Grid_Layer(void);

	virtual bool init();
	CREATE_FUNC(UI_Goods_Grid_Layer);

public:
	cocos2d::ui::ImageView* createHorizontalGrid( int style );

private:
	void pageViewEvent(Ref *pSender, cocos2d::ui::PageViewEventType type);

	

public:
	cocos2d::ui::ImageView*		m_pImgEffect[PAGE_SUM_NUM];							//选中背景
	cocos2d::ui::ImageView*		m_pImgLight[PAGE_SUM_NUM];							//第几页效果灯显示
	cocos2d::ui::ImageView*		m_pImgAllGrid[PAGE_SUM_NUM][EACH_PAGE_NUM];			//格子总数
	cocos2d::ui::ImageView*		m_pImgTextureChild[PAGE_SUM_NUM][EACH_PAGE_NUM];	//每个格子上的图片
	cocos2d::ui::ImageView*		m_pImgEveryEffect[PAGE_SUM_NUM][EACH_PAGE_NUM];		//每个格子都有选中效果

	//风格区分内容
	cocos2d::ui::Button*			btnTidy;										//整理按钮
	cocos2d::ui::Text*			m_pLabIconNum[PAGE_SUM_NUM][EACH_PAGE_NUM];		//物品数量
	cocos2d::ui::ImageView*		m_pImgQuaMark[PAGE_SUM_NUM][EACH_PAGE_NUM];		//"品" 字标识
	cocos2d::ui::ImageView*		m_pImgEquipMark[PAGE_SUM_NUM][EACH_PAGE_NUM];	//"装" 字标识
	cocos2d::ui::Button*			btnEat;
	cocos2d::ui::Text*			btnEatFont;
	cocos2d::ui::Button*			btnReset;
	cocos2d::ui::Text*			btnResetFont;

	int					m_IntCurPage;								//记录当前所在页

};

#endif //__UI_GOODS_GRID_LAYER__