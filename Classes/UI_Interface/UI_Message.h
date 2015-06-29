#ifndef __UI_MESSAGE_H__
#define __UI_MESSAGE_H__
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC;
using namespace ui;
#include "Common/Utils.h"
#define MSG_FONT_SIZE 32
class UI_Message:public Layer
{
public:
	static UI_Message* sharedInstance();
	void showMessage(int textId,int firstNumber,int secondNumber);
	virtual ~UI_Message();
	virtual bool init();
	void removeMessage();
private:
	UI_Message();
	LabelTTF *lab_message;
	static UI_Message* instance;
	bool isFirst;

	LabelAtlas*		m_pCurWavePercentage;
};
#endif //__UI_MESSAGE_H__