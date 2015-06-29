
#ifndef __DOWNLOADING_LAYER_H__
#define __DOWNLOADING_LAYER_H__

#include "cocos2d.h"
#include "Update_Logic/UpdateProtocol.h"
#define UPDATELAYERTAG  789345
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
namespace UI
{


class DownLoading_Layer : public cocos2d::Layer, public UpdateProtocol
{
public:
	DownLoading_Layer();
	~DownLoading_Layer();
	CREATE_FUNC (DownLoading_Layer);
	virtual bool init();

//协议方法，供下载管理类使用
public:
	void beforeProgress( void );

	void onProgress( int percent );
	void onSuccess( ErrorCode errorCode );
	void onError( ErrorCode errorcode );
	void onDecompressing( void );
	virtual void onGettingDownloadInfo();

private:
	void reboot(void);
	 void installAPK();
	 void quit();

protected:
	cocos2d::Sprite* m_pSprBgk;
	cocos2d::Sprite* m_pSprLoadingBar;
	cocos2d::Sprite* m_pSprLoadingBkg;
	cocos2d::LabelTTF* m_status_label;
};

}

#endif //__DOWNLOADING_LAYER_H__
