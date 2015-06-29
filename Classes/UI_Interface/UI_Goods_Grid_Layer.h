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

#define ROOT_BACK_WIDTH		472		//������
#define ROOT_BACK_HEIGHT	508		//������
#define LAYOUT_WIDTH		460		//ÿҳ���
#define LAYOUT_HEIGHT		360		//ÿҳ�߶�
#define PAGE_SUM_NUM		6		//��ҳ��
#define EACH_PAGE_ROW_NUM	3		//ÿҳ3��
#define EACH_PAGE_COL_NUM	4		//ÿҳ4��
#define EACH_PAGE_NUM		12		//ÿҳ������
#define GRID_NUM		    PAGE_SUM_NUM*EACH_PAGE_NUM		//�ܸ�����

#define STYLE_NOTHING			0	//������ʾ�κη��
#define STYLE_GRID_LAB_NUM		2	//��ʾ ��Ʒ ����
#define STYLE_GRID_PIC_QUA		4	//��ʾ"Ʒ"��ͼƬ
#define STYLE_GRID_PIC_EQU		8	//��ʾ"װ"��ͼƬ
#define STYLE_TIDY_BUTTON		16	//"����" ��ť
#define STYLE_EACH_HAS_EFFECT	32  //ÿ�����Ӿ����б���ͼ
#define STYLE_BOTH_BUTTON		64	//ÿҳ����������ť
#define STYLE_PAGE_LIGHT_MIDDLE	128	//���õ�ǰҳ��ʾ�����м�
#define STYLE_PAGE_LIGHT_LEFT	256	//���õ�ǰҳ��ʾ�������

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
	cocos2d::ui::ImageView*		m_pImgEffect[PAGE_SUM_NUM];							//ѡ�б���
	cocos2d::ui::ImageView*		m_pImgLight[PAGE_SUM_NUM];							//�ڼ�ҳЧ������ʾ
	cocos2d::ui::ImageView*		m_pImgAllGrid[PAGE_SUM_NUM][EACH_PAGE_NUM];			//��������
	cocos2d::ui::ImageView*		m_pImgTextureChild[PAGE_SUM_NUM][EACH_PAGE_NUM];	//ÿ�������ϵ�ͼƬ
	cocos2d::ui::ImageView*		m_pImgEveryEffect[PAGE_SUM_NUM][EACH_PAGE_NUM];		//ÿ�����Ӷ���ѡ��Ч��

	//�����������
	cocos2d::ui::Button*			btnTidy;										//����ť
	cocos2d::ui::Text*			m_pLabIconNum[PAGE_SUM_NUM][EACH_PAGE_NUM];		//��Ʒ����
	cocos2d::ui::ImageView*		m_pImgQuaMark[PAGE_SUM_NUM][EACH_PAGE_NUM];		//"Ʒ" �ֱ�ʶ
	cocos2d::ui::ImageView*		m_pImgEquipMark[PAGE_SUM_NUM][EACH_PAGE_NUM];	//"װ" �ֱ�ʶ
	cocos2d::ui::Button*			btnEat;
	cocos2d::ui::Text*			btnEatFont;
	cocos2d::ui::Button*			btnReset;
	cocos2d::ui::Text*			btnResetFont;

	int					m_IntCurPage;								//��¼��ǰ����ҳ

};

#endif //__UI_GOODS_GRID_LAYER__