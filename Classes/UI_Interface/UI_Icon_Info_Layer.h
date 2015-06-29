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

#define  TIPS_STYLE_EQUIP_EQUIPMENT			1				//װ�������ť
#define  TIPS_STYLE_TAKE_OFF_EQUIPMENT      2				//ж�°�ť
#define	 TIPS_STYLE_EQIP_BOOK		        4				//�鼮�����ť
#define  TIPS_STYLE_TAKE_OFF_BOOK	        8				//�鼮ж�°�ť
#define	 TIPS_STYLE_SET_ON_GEM		        16			    //��Ƕ��ʯ
#define  TIPS_STYLE_SET_OFF_GEM	            32			    //ж�±�ʯ
#define  TIPS_STYLE_COMBINE_GEM			    64			    //�ϳ�
#define  TIPS_STYLE_OK				        128				//ȷ����ť
#define  TIPS_STYLE_SELL			        256				//���۰�ť
#define  TIPS_STYLE_FINDWAY			        512				//Ѱ·��ť
#define  TIPS_STYLE_USE		                1024		    //ʹ�ð�ť
#define  TIPS_STYLE_USE_ALL		            2048	        //ʹ��ȫ����ť
#define  TIPS_STYLE_LEVEL			        4096		    //���ߵȼ�
#define  TIPS_STYLE_EQUIPMENT_ATTR		    8192		    //װ������
#define  TIPS_STYLE_BOOK_ATTR		        16384		    //�鼮����
#define  TIPS_STYLE_GEM_ATTR		        32768		    //��ʯ����

#define  FRAME_STYLE_INLAY					65536			//��ʯ��Ϣ��ʾ����

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

	void btnCloseCallback(Ref* pSender,Widget::TouchEventType type);		//�ر�
	void btnEquipCallback(Ref* pSender,Widget::TouchEventType type);		//װ��
	void btnTakeoffCallback(Ref* pSender,Widget::TouchEventType type);		//ж��
	void btnSellCallback(Ref* pSender,Widget::TouchEventType type);		//����
	void btnAStarCallback(Ref* pSender,Widget::TouchEventType type);		//Ѱ·
	void btnEquipBookCallback(Ref* pSender,Widget::TouchEventType type);	//װ���鼮
	void btnTakeoffBookCallback(Ref* pSender,Widget::TouchEventType type); //ж���鼮
    void btnUseCallback(Ref* pSender,Widget::TouchEventType type);		    //ʹ��

	//��ʯ��ť��
	void btnGemSetOnCallback( Ref* pSender ,Widget::TouchEventType type);
	void btnGenTakeOffCallback( Ref* pSender ,Widget::TouchEventType type);
	void btnGemCombineCallback( Ref* pSender ,Widget::TouchEventType type);

	void showIconInfo(int item_base_id, int icon, int name, int level=1, int current_quality=0);
	
	//��ʾ����һ������ͨ��Ϣ����
	void showLayoutFirst();
	//��ʾ�����������Ƕ���� (����Ƕ��Ϣ)��
	void showLayoutSecond();

public: //�ؼ���
	cocos2d::ui::ImageView*		m_pImgRootBack;		//�󱳾�

	cocos2d::ui::ImageView*		m_img_first_line;	//��һ����
	cocos2d::ui::Text*			m_pLabIconLevel;	//ͼ��ȼ�
	cocos2d::ui::Text*			m_pLabIconName;		//ͼ������
	cocos2d::ui::Button*			m_pBtnClose;		//�رհ�ť
	cocos2d::ui::Text*			m_pTeaForDesc;		//ͼ������

	cocos2d::ui::ImageView*		m_img_second_line;  //�ڶ�����
	cocos2d::ui::Text*			m_pLabGemAttr[GEM_INLAY_NUM];	//��Ƕ��ʯ����

	cocos2d::ui::ImageView*		m_img_third_line;  //��������
	cocos2d::ui::Text*			m_pLabAttrArr[TOTAL_ATTR_NUM]; //������

	cocos2d::ui::Button*			m_pBtnLeft;			//��ఴť
	cocos2d::ui::Text*			m_pBtnLeftFont;		//��ఴť����
	cocos2d::ui::Button*			m_pBtnRight;		//�Ҳఴť
	cocos2d::ui::Text*			m_pBtnRightFont;	//�Ҳఴť����
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

//Icon ��Ϣ��ʾ��
UI_Icon_Info_Layer*			m_pLayerIconInfo;

#include "UI_Icon_Info_Layer.h"
m_pLayerIconInfo(NULL);

//������Ʒ��Ϣ��ʾ��
m_pLayerIconInfo = UI_Icon_Info_Layer::create();
this->addChild(m_pLayerIconInfo,THISLAYERZORDERE,THISLAYERTAG);
m_pLayerIconInfo->setVisible(false);


m_pLayerIconInfo->showButton(item->config->base_id,item->config->icon,item->config->name,item->level,item->current_quality,
TIPS_STYLE_SELL | TIPS_STYLE_EQUIP | TIPS_STYLE_LEVEL | TIPS_STYLE_ATTR);

*/